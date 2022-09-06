#include <iostream>
#include <stdexcept>
#include <vector>
#include "Game.hpp"

using namespace coup;

Game::Game()
{
}
std::string Game::turn()
{
    return "turn";
}
std::vector<std::string> Game::players()
{
    std::vector<std::string> players;
    return players;
}
std::string Game::winner()
{
    return "Moriya";
}