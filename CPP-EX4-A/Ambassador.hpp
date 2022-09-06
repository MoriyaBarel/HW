#include <iostream>
#include "Player.hpp"


namespace coup
{
    class Ambassador:public Player
    {
    private:
        std::string name;
    public:
        Ambassador(Game game, std::string name);
        void transfer(Player taken, Player getting);
        void block(Player player);
    };
}