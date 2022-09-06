#include <iostream>
#include <stdexcept>
#include <vector>
#include "Player.hpp"

using namespace coup;
const uint money_to_kill = 7;
const uint must_kill = 10;

Player::Player(Game &game, const std::string &name)
{
    this->game = &game;
    this->money_amount = 0;
    this->isAlive = true;
    this->name = name;
    this->last_action = "";
    this->game->add_new_player(*this);
}

void Player::income()
{
    check_erros();
    if (this->money_amount >= must_kill)
    {
        throw std::logic_error("has to do coup.");
    }
    this->money_amount++;
    this->move_turn("income");
}

void Player::foreign_aid()
{
    check_erros();
    if (this->money_amount >= must_kill)
    {
        throw std::logic_error("has to do coup.");
    }
    this->money_amount = this->money_amount + 2;
    this->move_turn("foreign_aid");
}

void Player::coup(Player &player)
{
    check_erros();
    if (this->money_amount < money_to_kill)
    {
        throw std::logic_error("You must have at least 7 coins to coup.");
    }
    if (!player.isAlive)
    {
        throw std::logic_error("The player you're trying to coup isn't in the game");
    }
    player.isAlive = false;
    this->money_amount -= money_to_kill;
    this->move_turn("coup");
}

int Player::coins() const
{
    return this->money_amount;
}

std::string Player::role() const
{
    return this->my_role;
}

void Player::check_erros()
{
    if (!this->isAlive)
    {
        throw std::runtime_error("Player is not in the game.");
    }

    if (this->game->players().size() < 2)
    {
        throw std::runtime_error("at least 2 players required to start the game.");
    }

    if (this->name != this->game->turn())
    {
        throw std::runtime_error(this->name + " it's not your turn please be patient.");
    }
    
    this->game->is_game_started = true;
}

void Player::move_turn(std::string action_preformed)
{
    this->game->next_turn();
    this->last_action = std::move(action_preformed);
}

void Player::got_blocked()
{
    if (this->last_action == "foreign_aid")
    {
        this->money_amount -= 2;
    }
    this->last_action = "";
}