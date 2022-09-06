#pragma once
#include <iostream>
#include "Game.hpp"

namespace coup
{
    class Game;
    class Player
    {
    private:
        Game *game;
    public:
        bool isAlive;
        std::string name;
        std::string my_role;
        std::string last_action;
        int money_amount;
        Player(Game &game, const std::string &name);
        void income();
        void foreign_aid();
        void coup(Player &player);
        int coins() const;
        std::string role() const;
        void check_erros();       
        void move_turn(std::string action_preformed); 
        virtual void got_blocked();
    };
}