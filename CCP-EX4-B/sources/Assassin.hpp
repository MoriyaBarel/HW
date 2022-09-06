#include <iostream>
#include "Player.hpp"


namespace coup
{
    class Assassin:public Player
    {
    private:
        Player *assassination_target;
    public:
        Assassin(Game &game, const std::string &name);
        void coup(Player &player);
        void got_blocked();
    };
}