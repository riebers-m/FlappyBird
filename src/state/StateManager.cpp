//
// Created by riebers on 19.12.2024.
//

#include "StateManager.hpp"

namespace game {
    void StateManager::activate_state(StateId const &state) {
        if (!m_states.empty()) {
            if (m_states.back().first == state) {
                return;
            }

            m_states.back().second->exit();
        }

        auto const ret = std::ranges::find_if(m_states, [&state](auto const &other) {
            return other.first == state;
        });
        if (ret != m_states.end()) {
            auto current_state = std::move(*ret);
            m_states.erase(ret);
            m_states.emplace_back(std::move(current_state));
        } else {
            m_states.emplace_back(std::move(*ret));
        }
        m_states.back().second->enter();
    }


    void StateManager::kill_states() {
        for (auto const &state: m_to_be_removed) {
            auto ret = std::ranges::remove_if(m_states, [&state](auto const &other_state) {
                return state == other_state.first;
            });
            m_states.erase(ret.begin(), ret.end());
        }
        m_to_be_removed.clear();
    }

    void StateManager::add_state(StateId id, BaseStatePtr state) {
        if (!m_states.empty()) {
            m_states.back().second->exit();
        }

        auto const ret = std::ranges::find_if(m_states, [&id](auto const &other_state) {
            return id == other_state.first;
        });
        if (ret == m_states.end()) {
            m_states.emplace_back(id, std::move(state));
        }
        m_states.back().second->enter();
    }

    void StateManager::remove_state(StateId id) {
        auto const ret = std::ranges::find_if(m_to_be_removed, [&id](StateId const &state_id) {
            return id == state_id;
        });
        if (ret == m_to_be_removed.end()) {
            m_to_be_removed.emplace_back(id);
        }
    }

    bool StateManager::has_state(StateId const &state) {
        return std::ranges::any_of(m_states, [&state](auto const &other) {
            return other.first == state;
        });
    }

    void StateManager::handle_events(SDL_Event const &event) const {
        if (m_states.empty()) {
            throw std::runtime_error("No states to handle events");
        }
        m_states.back().second->handle_events(event);
    }

    void StateManager::update(entt::registry const &state,
                              std::chrono::milliseconds const &dt) {
        if (m_states.empty()) {
            throw std::runtime_error("No states to update");
        }

        m_states.back().second->update(state, dt);
    }

    void StateManager::render(entt::registry const &state) const {
        if (m_states.empty()) {
            throw std::runtime_error("No states to render");
        }

        auto first_transparent_state = m_states.end() - 1;
        for (; first_transparent_state != m_states.begin(); --first_transparent_state) {
            if (!first_transparent_state->second->is_transparent()) {
                break;
            }
        }

        for (; first_transparent_state != m_states.end(); ++first_transparent_state) {
            first_transparent_state->second->render(state);
        }
    }

    void StateManager::process_states() {
        kill_states();
    }
} // namespace game
