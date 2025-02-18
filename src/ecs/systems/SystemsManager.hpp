//
// Created by Riebers on 18.02.2025.
//

#pragma once
#include <memory>
#include <typeindex>
#include <unordered_map>

#include "BaseSystem.hpp"

namespace systems {
    class SystemsManager {
    private:
        std::unordered_map<std::type_index, std::unique_ptr<BaseSystem> > m_systems;

    public:
        SystemsManager() = default;

        template<typename TSystem, typename... TArgs>
        void add_system(TArgs &&... args) {
            static_assert(std::is_base_of_v<BaseSystem, TSystem>, "System have to be derived from BaseSystem.");
            if (auto const result = m_systems.try_emplace(typeid(TSystem),
                                                          std::make_unique<TSystem>(std::forward<TArgs>(args)...));
                !result.second) {
                throw std::runtime_error(std::format("could not add system: {}", typeid(TSystem).name()));
            }
        }

        template<typename TSystem>
        [[nodiscard]] bool has_system() const {
            if (auto const itr = m_systems.find(typeid(TSystem)); itr != m_systems.end()) {
                return true;
            }
            return false;
        }

        template<typename TSystem>
        TSystem &get_system() {
            if (auto const itr = m_systems.find(typeid(TSystem)); itr != m_systems.end()) {
                return static_cast<TSystem &>(*itr->second);
            }
            throw std::runtime_error(std::format("could not get_system: {}", typeid(TSystem).name()));
        }
    };
}
