//
// Created by riebers on 19.12.2024.
//

#pragma once
#include "States.hpp"
#include "gamer/Configuration.hpp"
#include "state/BaseState.hpp"

namespace game {
    using BaseStatePtr = std::unique_ptr<BaseState>;
    using StateId = States;

    class StateManager {
    private:
        std::vector<std::pair<StateId, BaseStatePtr> > m_states;
        std::vector<StateId> m_to_be_removed;

        void kill_states();

    public:
        StateManager() = default;

        void activate_state(StateId const &state);

        void add_state(StateId id, BaseStatePtr state);

        void remove_state(StateId);

        bool has_state(StateId const &state);


        void handle_events(SDL_Event const &event) const;

        void update(Registry const &, std::chrono::milliseconds const &dt);

        void render(Registry const &) const;

        void process_states();
    };
} // namespace game
