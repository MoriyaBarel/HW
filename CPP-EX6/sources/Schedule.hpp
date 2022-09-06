#include <iostream>
#include "League.hpp"

namespace ex6
{
    class Round
    {
    private:
        std::vector<Game *> games;

    public:
        Round();
        void add_game(Game *game);
        std::vector<Game*>& get_games();
        friend std::ostream &operator<<(std::ostream &s_out, const Round &round);
    };

    class Schedule
    {
    private:
        League *league;
        std::vector<Round> all_rounds;
    public:
        Schedule(League *league);
        ~Schedule();
        static void shift(std::vector<Team *> &all_teams);
        friend std::ostream &operator<<(std::ostream &s_out, const Schedule &schedule);
        void print_statistics();
        std::vector<Round>& get_rounds(); 
        Schedule &operator=(Schedule &&other) noexcept = default;
        Schedule(const Schedule &other) = default;
        Schedule(Schedule &&other) noexcept = default;
        Schedule &operator=(const Schedule &other) = default;

    };
}