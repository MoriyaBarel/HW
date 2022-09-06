#include <iostream>

namespace ex6
{
    class Team
    {
    private:
        std::string name;
        float skills;
        int total_wins;
        int total_loses;
        int good_points;
        int bad_points;
        int wins_streak;
        int loses_streak;
        int best_wins_streak;
        int best_loses_streak;

    public:
        Team(std::string name, float skills);
        std::string get_name() const;
        float get_skills() const;
        int get_best_wins_streak() const;
        int get_best_loses_streak() const;
        int points_diff() const;
        int get_total_wins() const;
        int get_total_loses() const;
        int get_good_points() const;
        int get_bad_points() const;
        void inc_total_wins();
        void inc_total_loses();
        void set_good_points(int points);
        void set_bad_points(int points);
        void inc_loses_streak();
        void inc_wins_streak();
        void reset_wins_streak();
        void reset_loses_streak();
        friend std::ostream &operator<<(std::ostream &s_out, const Team& team);
    };
}