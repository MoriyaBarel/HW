#include "Schedule.hpp"
#include <algorithm>

using namespace ex6;

const uint ROUNDS_NUM = 38;

Round::Round()
{
}

void Round::add_game(Game *game)
{
    this->games.push_back(game);
}

std::vector<Game*>& Round::get_games()
{
    return this->games;
}

std::vector<Round>& Schedule::get_rounds()
{
    return this->all_rounds;
}

Schedule::Schedule(League *league)
{
    this->league = league;
    this->all_rounds.resize(ROUNDS_NUM);
    std::vector<Team *> all_teams(league->league_teams());
    int round_index = 0;
    while (round_index != ROUNDS_NUM)
    {
        if (round_index != 0)
        {
            shift(all_teams);
        }
        for (uint i = 0; i < all_teams.size() / 2; i++)
        {
            Game *game = new Game(all_teams[i], all_teams[all_teams.size() - 1 - i]);
            Game *inverse_game = new Game(all_teams[all_teams.size() - 1 - i], all_teams[i]);
            this->all_rounds[(uint)round_index].add_game(game);
            this->all_rounds[(uint)round_index + 1].add_game(inverse_game);
        }
        round_index += 2;
    }
}

Schedule::~Schedule()
{   
    this->league->~League(); 
    for (Round &round : this->all_rounds)
    {
        for (Game *game : round.get_games())
        {
            delete game;
        }
    }
}

void Schedule::shift(std::vector<Team *> &all_teams)
{
    std::vector<Team *> temp(all_teams);
    all_teams[0] = temp[0];
    all_teams[1] = temp[all_teams.size() - 1];
    for (uint i = 2; i < temp.size(); i++)
    {
        all_teams[i] = temp[i - 1];
    }
}

bool compare(Team *a, Team *b) 
{ 
    if (a->get_total_wins() > b->get_total_wins())
    {   
        return true;
    }
    if(a->get_total_wins() == b->get_total_wins())
    {
        if (a->points_diff() >= b->points_diff())
        {
            return true;
        }       
    }
    return false;
}

void Schedule::print_statistics()
{
    std::vector<Team *> table(this->league->league_teams());
    std::sort(table.begin(), table.end(), compare);
    for (uint i = 0; i < table.size(); i++)
    {
        std::cout << *table[i] << std::endl;
    }
}

namespace ex6
{
    std::ostream &operator<<(std::ostream &s_out, const Schedule &schedule)
    {
        int i = 0;
        for (Round const& round : schedule.all_rounds)
        {
            s_out << "------------------------------------------------------------------------" << std::endl;
            s_out << "Round number " << std::to_string(i) << std::endl;
            s_out << round;
            i++;
        }
        return s_out;
    }

    std::ostream &operator<<(std::ostream &s_out, const Round &round)
    {
        for (Game *game : round.games)
        {
            s_out << *(game);
        }
        return s_out;
    }

}