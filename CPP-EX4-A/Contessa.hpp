#include <iostream>
#include "Player.hpp"


namespace coup
{
    class Contessa:public Player
    {
    private:
        std::string name;
    public:
        Contessa(Game game, std::string name);        
        void block(Player player);
    };
}