//
// Created by Riebers on 09.02.2025.
//

#pragma once
#include <functional>
#include <algorithm>

template<typename... TArgs>
class Delegate {
public:
    using Callback = std::function<void(TArgs &&... args)>;
    using ValidPredicate = std::function<bool()>;

private:
    struct Delegator {
        // check if function is valid
        ValidPredicate predicate;
        Callback callback;
    };

    void remove_invalid_delegator() {
        auto const result = std::ranges::remove_if(m_delegators, [](Delegator const &delegator) {
            return !delegator.predicate();
        });
        m_delegators.erase(result.begin(), result.end());
    }

public:
    void bind(ValidPredicate const &predicate, Callback const &callback) {
        m_delegators.emplace_back({predicate, callback});
    }

    void broadcast(TArgs &&... args) {
        remove_invalid_delegator();
        for (auto const delegator: m_delegators) {
            delegator.callback(std::forward<TArgs>(args)...);
        }
    }

    void clear() {
        m_delegators.clear();
    }

private:
    std::vector<Delegator> m_delegators;
};
