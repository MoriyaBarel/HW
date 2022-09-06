#include <iostream>
#include <stdexcept>
#include <vector>
#include "Assassin.hpp"

using namespace coup;
const uint three = 3;
const uint seven = 7;

Assassin::Assassin(Game &game, const std::string &name) : Player(game, name)
{
    this->my_role = "Assassin";
    this->assassination_target = NULL;
}

void Assassin::coup(Player &player)
{
    check_erros();
    if (!player.isAlive)
    {
        throw std::logic_error("The player you're trying to coup isn't in the game");
    }
    if (this->money_amount < three)
    {
        throw std::runtime_error("assassination require at least 3 coins.");
    }
    player.isAlive = false;
    this->assassination_target = &player;
    if (this->money_amount >= three && this->money_amount < seven)
    {
        this->money_amount -= three;
        move_turn("assassination");
    }
    else
    {
        this->money_amount -= seven;
        this->move_turn("coup");
    }
}

void Assassin::got_blocked()
{
    if (this->last_action == "assassination")
    {
        this->assassination_target->isAlive = true;
        this->assassination_target = NULL;
    }
    if (this->last_action == "foreign_aid")
    {
        this->money_amount -= 2;
    }
    this->last_action = "";
}
