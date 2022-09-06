#include <iostream>
#include "Player.hpp"


namespace coup
{
    class Captain:public Player
    {
    private:
        Player *stolen_player;
        bool stole_one_coin;
    public:
        Captain(Game &game, const std::string &name);
        static void block(Player &splayer);
        void steal(Player &player);
        void got_blocked();
    };
}