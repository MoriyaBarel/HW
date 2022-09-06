#include "Team.hpp"

using namespace ex6;

Team::Team(std::string name, float skills)
{
    if (skills < 0 || skills > 1)
    {
        throw std::invalid_argument("skills level should be a number between 0-1");
    }
    this->name = std::move(name);
    this->skills = skills;
    this->total_wins = 0;
    this->total_loses = 0;
    this->good_points = 0;
    this->bad_points = 0;
    this->best_loses_streak = 0;
    this->best_wins_streak = 0;
    this->loses_streak = 0;
    this->wins_streak = 0;
}

std::string Team::get_name() const
{
    return this->name;
}

float Team::get_skills() const
{
    return this->skills;
}

int Team::get_best_wins_streak() const
{
    return this->best_wins_streak;
}

int Team::get_best_loses_streak() const
{
    return this->best_loses_streak;
}

int Team::points_diff() const
{
    return this->good_points - this->bad_points;
}

int Team::get_total_wins() const
{
    return this->total_wins;
}

int Team::get_total_loses() const
{
    return this->total_loses;
}

int Team::get_good_points() const
{
    return this->good_points;
}

int Team::get_bad_points() const
{
    return this->bad_points;
}

void Team::inc_total_wins()
{
    this->total_wins++;
}

void Team::inc_total_loses()
{
    this->total_loses++;
}

void Team::set_good_points(int points)
{
    this->good_points += points;
}

void Team::set_bad_points(int points)
{
    this->bad_points += points;
}

void Team::inc_loses_streak()
{
    this->loses_streak++;
    if (this->loses_streak > this->best_loses_streak)
    {
        this->best_loses_streak = this->loses_streak;
    }
}

void Team::inc_wins_streak()
{
    this->wins_streak++;
    if (this->wins_streak > this->best_wins_streak)
    {
        this->best_wins_streak = this->wins_streak;
    }
}
void Team::reset_wins_streak()
{
    this->wins_streak = 0;
}

void Team::reset_loses_streak()
{
    this->loses_streak = 0;
}

namespace ex6
{
    std::ostream &operator<<(std::ostream &s_out, const Team &team)
    {
        s_out << "Name: " << team.get_name() << " | Skills: " << team.get_skills() << " | Wins: " << team.get_total_wins()
              << " | Loses: " << team.get_total_loses() << " | Good points: " << team.good_points
              << " | Bad points: " << team.bad_points << " | Wins streak: "
              << team.get_best_wins_streak() << " | Loses streak: " << team.get_best_loses_streak();
        return s_out;
    }
}
