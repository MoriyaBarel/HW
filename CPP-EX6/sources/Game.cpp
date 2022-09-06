#include "Game.hpp"

const int EXP = 75;
const int VAR = 7;
const int MAX_POINTS = 100;
const int MIN_HOME_POINTS = 55;
const int MIN_AWAY_POINTS = 50;
const int BOUNUS = 10;

using namespace ex6;

Game::Game(Team *home, Team *away)
{
   if (home->get_name() == away->get_name())
   {
      throw std::logic_error("A team cannot play against itself");
   }
   this->home_team = home;
   this->away_team = away;
   this->winner = nullptr;
   this->home_points = 0;
   this->away_points = 0;
   results();
   set_winner();
}

Team *Game::get_winner() const
{
   if (this->winner == nullptr)
   {
      throw std::logic_error("There is no winner yet");
   }
   return this->winner;
}

Team *Game::get_home_team() const
{
   return this->home_team;
}

Team *Game::get_away_team() const
{
   return this->away_team;
}

int Game::get_home_points() const
{
   return this->home_points;
}

int Game::get_away_points() const
{
   return this->away_points;
}

void Game::set_winner()
{
   if (this->home_points > this->away_points)
   {
      this->winner = this->home_team;
      this->home_team->inc_wins_streak();
      this->away_team->inc_loses_streak();
      this->away_team->reset_wins_streak();
      this->home_team->reset_loses_streak();
      this->home_team->inc_total_wins();
      this->away_team->inc_total_loses();
   }
   else
   {
      this->winner = this->away_team;
      this->away_team->inc_wins_streak();
      this->home_team->inc_loses_streak();
      this->away_team->reset_loses_streak();
      this->home_team->reset_wins_streak();
      this->away_team->inc_total_wins();
      this->home_team->inc_total_loses();
   }
}

void Game::results()
{
   std::normal_distribution<> normal_d{EXP, VAR};
   std::random_device rd{};
   std::mt19937 gen{rd()};

   while (this->home_points < MIN_HOME_POINTS || this->home_points > MAX_POINTS)
   {
      this->home_points = normal_d(gen);
   }

   while (this->away_points < MIN_AWAY_POINTS || this->away_points > MAX_POINTS)
   {
      this->away_points = normal_d(gen);
   }

   this->home_points = this->home_points + (BOUNUS * (int)this->home_team->get_skills());
   this->away_points = this->away_points + (BOUNUS * (int)this->away_team->get_skills());

   if (this->home_points == this->away_points)
   {
      if (this->home_team->get_skills() > this->away_team->get_skills())
      {
         this->home_points += 1;
      }
      else if (this->home_team->get_skills() == this->away_team->get_skills())
      {
         std::srand(time(NULL));
         int random = std::rand() % 2;
         if (random == 0)
         {
            this->home_points += 1;
         }
         else
         {
            this->away_points += 1;
         }
      }
      else
      {
         this->away_points += 1;
      }
   }

   this->home_team->set_bad_points(this->away_points);
   this->home_team->set_good_points(this->home_points);

   this->away_team->set_bad_points(this->home_points);
   this->away_team->set_good_points(this->away_points); 
}

namespace ex6
{
   std::ostream &operator<<(std::ostream &s_out, const Game &game)
   {
      s_out << "Home_team: " << game.get_home_team()->get_name() << ", Points: " << game.get_home_points();
      s_out << " | Away_team: " << game.get_away_team()->get_name() << ", Points: " << game.get_away_points();
      s_out << " | Winner: " << game.get_winner()->get_name() << std::endl;
      return s_out;
   }
}
