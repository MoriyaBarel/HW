#include <iostream>
#include "Player.hpp"


namespace coup
{
    class Captain:public Player
    {
    private:
        std::string name;
    public:
        Captain(Game game, std::string name);
        void block(Player player);
        void steal(Player player);  
    };
}