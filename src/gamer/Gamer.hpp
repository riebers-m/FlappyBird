//
// Created by riebers on 14.12.2024.
//

#pragma once
#include "Game.hpp"


namespace game {

class Gamer final {
private:
    Gamer();
    ~Gamer();
    static Gamer const& instance();
public:
    Gamer(Gamer const&) = delete;
    Gamer(Gamer&&) = delete;
    Gamer& operator=(Gamer const&) = delete;
    Gamer& operator=(Gamer&&) = delete;

    static Game create_game(LoggerPtr logger, Gamer const & = instance());
};

} // game
