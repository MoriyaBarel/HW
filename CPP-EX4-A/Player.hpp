#pragma once
#include <iostream>
#include "Game.hpp"

namespace coup
{
    class Player
    {
    private:

    public:
        Player();
        void income();
        void foreign_aid();
        void coup(Player player);
        std::string role();
        int coins();

    };
}