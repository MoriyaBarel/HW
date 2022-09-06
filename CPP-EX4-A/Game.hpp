#pragma once
#include <iostream>
#include <vector>

namespace coup
{
    class Game
    {
    private:

    public:
        Game();
        std::string turn();
        std::vector<std::string> players();
        std::string winner();
    };
}