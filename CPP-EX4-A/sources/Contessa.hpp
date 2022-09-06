#include <iostream>
#include "Player.hpp"


namespace coup
{
    class Contessa:public Player
    {
    private:

    public:
        Contessa(Game &game, const std::string &name);        
        void block(Player &player);
    };
}