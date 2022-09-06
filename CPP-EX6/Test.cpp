#include "doctest.h"
#include "sources/Schedule.hpp"

using namespace ex6;

TEST_CASE("Game")
{
    Team *home_t = new Team("Barel", 0.9);
    Team *away_t = new Team("Amiga", 0.1);
    Game *game1 = new Game(home_t, away_t);
    CHECK(home_t->get_good_points() == game1->get_home_points());
    CHECK(away_t->get_good_points() == game1->get_away_points());
    CHECK(game1->get_home_points() > 50);
    CHECK(game1->get_away_points() > 55);
    CHECK(game1->get_home_points() < 100);
    CHECK(game1->get_away_points() < 100);
    if (game1->get_home_points() >= game1->get_away_points())
    {
        CHECK_EQ(home_t->get_total_wins(), 1);
    }
    else
    {
        CHECK_EQ(away_t->get_total_wins(), 1);
    }

    CHECK_THROWS(Game *game2 = new Game(home_t, home_t));
    delete home_t;
    delete away_t;
    delete game1;
}

TEST_CASE("Team")
{
    CHECK_THROWS(Team *t = new Team("Barel", -1));
    CHECK_THROWS(Team *t = new Team("Barel", 2));
    Team team3{"Barel", 0.8};
    team3.inc_total_wins();
    CHECK_EQ(team3.get_total_wins(), 1);
}

TEST_CASE("Schedule")
{
    League *l = new League();
    Schedule s{l};
    for (uint i = 0; i < s.get_rounds().size(); i++)
    {
        for (uint j = 0; j < s.get_rounds()[i].get_games().size(); j++)
        {
            CHECK(s.get_rounds()[i].get_games()[j]->get_home_points() <= 110);
            CHECK(s.get_rounds()[i].get_games()[j]->get_home_points() >= 55);
            CHECK(s.get_rounds()[i].get_games()[j]->get_home_points() <= 110);
            CHECK(s.get_rounds()[i].get_games()[j]->get_home_points() >= 50);
        }
    }
}
