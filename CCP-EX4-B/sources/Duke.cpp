#include <iostream>
#include <stdexcept>
#include <vector>
#include "Duke.hpp"

using namespace coup;

Duke::Duke(Game &game, const std::string &name) : Player(game, name)
{
    this->my_role = "Duke";
}

void Duke::tax()
{
    check_erros();
    this->money_amount += 3;
    this->move_turn("tax");
}

void Duke::block(Player &player)
{
    if (player.last_action != "foreign_aid")
    {
        throw std::runtime_error("Duke can block only foreign aid action.");
    }
    player.got_blocked();
}