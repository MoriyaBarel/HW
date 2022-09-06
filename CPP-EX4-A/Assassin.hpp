#include <iostream>
#include "Player.hpp"


namespace coup
{
    class Assassin:public Player
    {
    private:
        std::string name;
    public:
        Assassin(Game game, std::string name);
        void coup(Player player);
    };
}