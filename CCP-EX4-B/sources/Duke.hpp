#include <iostream>
#include "Player.hpp"


namespace coup
{
    class Duke:public Player
    {
    private:

    public:
        Duke(Game &game, const std::string &name);
        void tax();
        static void block(Player &player);
    };
}