#include <iostream>
#include <stdexcept>
#include <vector>
#include "Ambassador.hpp"

using namespace coup;

Ambassador::Ambassador(Game &game, const std::string &name) : Player(game, name)
{
    this->my_role = "Ambassador";
}

void Ambassador::transfer(Player &taken, Player &getting)
{
    check_erros();
    if (taken.money_amount < 1)
    {
        throw std::logic_error("there is not enough money to transfer.");
    } 
    taken.money_amount-=1;
    getting.money_amount+=1;
    this->move_turn("transfer");
}

void Ambassador::block(Player &player)
{
    if (player.my_role != "Captain")
    {
        throw std::logic_error("Ambassador can only block captain");
    }
    if (!player.isAlive)
    {
        throw std::logic_error("The player you're trying to block isn't in the game");
    }
    if (player.last_action != "steal")
    {
        throw std::logic_error("last action is not steal");
    }
    player.got_blocked();
}