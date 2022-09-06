#pragma once
#include <iostream>
#include <vector>
#include "Player.hpp"

namespace coup
{
    class Player;
    class Game
    {
    private:
        std::vector<Player*> all_players;
    public:
        Game();
        bool is_game_started;
        uint turn_index;
        void add_new_player(Player &player);
        std::string turn();
        void next_turn();
        std::vector<std::string> players();
        std::string winner();
    };
}