#include <iostream>
#include <vector>
#include "Game.hpp"

namespace ex6
{
    class League
    {
    private:
        std::vector<Team*> all_teams;

    public:
        League(const std::vector<Team*> &teams);
        League();
        ~League();
        static void check_for_errors(const std::vector<Team *> &teams);
        void insert_new_teams();
        static float generate_random_skills();
        std::vector<Team*>& league_teams();
        friend std::ostream &operator<<(std::ostream &s_out, const League& league);
        League &operator=(League &&other) noexcept = default;
        League(const League &other) = default;
        League(League &&other) noexcept = default;
        League &operator=(const League &other) = default;
    };
}