#include <iostream>
#include <stdexcept>
#include <vector>
#include "Captain.hpp"

using namespace coup;

Captain::Captain(Game &game, const std::string &name) : Player(game, name)
{
    this->my_role = "Captain";
    this->stolen_player = NULL;
    this->stole_one_coin = false;
}

void Captain::block(Player &player)
{
    if (player.my_role != "Captain")
    {
        throw std::logic_error("CAptain can only block captain");
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

void Captain::steal(Player &player)
{
    check_erros();
    if (player.money_amount < 2)
    {
        player.money_amount -= 1;
        this->money_amount += 1;
        this->stole_one_coin = true;
    }
    else
    {
        player.money_amount -= 2;
        this->money_amount += 2;
    }
    this->stolen_player = &player;
    move_turn("steal");
}

void Captain::got_blocked()
{
    if (this->last_action == "steal")
    {
        if (stole_one_coin)
        {
            this->money_amount -= 1;
            this->stolen_player->money_amount += 1;
        }
        else
        {
            this->money_amount -= 2;
            this->stolen_player->money_amount += 2;
        }
        this->stole_one_coin = false;
    }
    if (this->last_action == "foreign_aid")
    {
        this->money_amount -= 2;
    }
    this->last_action = "";
}