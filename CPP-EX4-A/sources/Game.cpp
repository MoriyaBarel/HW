#include <iostream>
#include <stdexcept>
#include <vector>
#include "Game.hpp"

using namespace coup;


Game::Game()
{
    this->turn_index = 0;
    this->is_game_started = false;
}

void Game::add_new_player(Player &player)
{
    const uint max_players = 6;
    if (this->all_players.size() == max_players)
    {
        throw std::logic_error("Max amount of players is 6.");
    }
    if (this->is_game_started)
    {
        throw std::runtime_error("It's impossible to add players after the game has started.");
    }
    this->all_players.push_back(&player);
}

void Game::next_turn()
{
    do
    {
        this->turn_index = (this->turn_index + 1) % this->all_players.size();
    } while (!(this->all_players[this->turn_index]->isAlive));
}

std::string Game::turn()
{
    return this->all_players[this->turn_index]->name;
}

std::vector<std::string> Game::players()
{
    std::vector<std::string> active_players;
    for (size_t i = 0; i < this->all_players.size(); i++)
    {
        if (this->all_players[i]->isAlive)
        {
            active_players.push_back(this->all_players[i]->name);
        }
    }
    return active_players;
}

std::string Game::winner()
{
    if (players().size() == 1 && this->is_game_started)
    {
        return players()[0];
    }
    throw std::runtime_error("Game hasn't started yet/there is no winner- the game still runing");
}