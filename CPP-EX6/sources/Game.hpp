#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>

#include "Team.hpp"

namespace ex6
{
    class Game
    {
    private:
        Team *home_team;
        Team *away_team;
        Team *winner;
        int home_points;
        int away_points;  
        void set_winner();

    public:  
        Game(Team *home_team, Team *away_team);
        void results();
        Team* get_winner() const;
        Team* get_home_team() const;
        Team* get_away_team() const;
        int get_home_points() const;
        int get_away_points() const;
        friend std::ostream &operator<<(std::ostream &s_out, const Game& game);
    };
}