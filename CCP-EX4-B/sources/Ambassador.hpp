#include <iostream>
#include "Player.hpp"


namespace coup
{
    class Ambassador:public Player
    {
    public:
        Ambassador(Game &game, const std::string &name);
        void transfer(Player &taken, Player &getting);
        static void block(Player &player);
    };
}