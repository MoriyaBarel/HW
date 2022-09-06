#include <iostream>
#include "Player.hpp"


namespace coup
{
    class Duke:public Player
    {
    private:
        std::string name;
    public:
        Duke(Game game, std::string name);
        void tax();
        void block(Player player);
    };
}