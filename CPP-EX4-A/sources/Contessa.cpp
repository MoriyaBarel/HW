#include <iostream>
#include <stdexcept>
#include <vector>
#include "Contessa.hpp"
#include "Assassin.hpp"

using namespace coup;

Contessa::Contessa(Game &game, const std::string &name) : Player(game, name)
{
    this->my_role = "Contessa";
}
void Contessa::block(Player &player)
{
    if (player.my_role != "Assassin")
    {
        throw std::logic_error("contessa can only block assassin");
    }
    if (!player.isAlive || !this->isAlive)
    {
        throw std::logic_error("The player you're trying to block isn't in the game");
    }
    if (player.last_action != "assassination")
    {
        throw std::logic_error("last action is not coup");
    }
    player.got_blocked();
}
