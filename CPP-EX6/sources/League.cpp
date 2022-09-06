#include "League.hpp"

const int TEAMS_NUM = 20;
const int FLOAT_MIN = 0;
const int FLOAT_MAX = 1;

using namespace ex6;

League::League(const std::vector<Team *> &teams)
{
    check_for_errors(teams);
    for (Team *team : teams)
    {
        this->all_teams.push_back(team);
    }
    if (this->all_teams.size() < TEAMS_NUM)
    {
        insert_new_teams();
    }
}

League::~League()
{
    for (uint i = 0; i < this->all_teams.size(); i++)
    {
        delete this->all_teams[i];
    }
}

League::League()
{
    insert_new_teams();
}

void League::insert_new_teams()
{
    const int teams_to_add = TEAMS_NUM - (int)this->all_teams.size();
    for (uint i = 0; i < teams_to_add; i++)
    {
        std::string name = "Team_" + std::to_string(i + 1);
        Team *team = new Team(name, generate_random_skills());
        this->all_teams.push_back(team);
    }
}

float League::generate_random_skills()
{
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> distr(FLOAT_MIN, FLOAT_MAX);
    return distr(eng);
}

std::vector<Team *>& League::league_teams()
{
    return this->all_teams;
}

void League::check_for_errors(const std::vector<Team *> &teams)
{
    if (teams.size() > TEAMS_NUM)
    {
        throw std::invalid_argument("Max teams number is 20.");
    }

    for (uint i = 0; i < teams.size(); i++)
    {
        for (uint j = 0; j < teams.size(); j++)
        {
            if (i == j)
            {
                continue;
            }
            if (teams[i] == teams[j])
            {
                throw std::invalid_argument("A team cannot be in the league more than one time");
            }
            if (teams[i]->get_name() == teams[j]->get_name())
            {
                throw std::invalid_argument("It's impossible for two teams to have the same name");
            }
        }
    }
}

namespace ex6
{
    std::ostream &operator<<(std::ostream &s_out, const League &league)
    {
        for (Team *team : league.all_teams)
        {
            s_out << (*team) << std::endl;
        }
        return s_out;
    }
}
