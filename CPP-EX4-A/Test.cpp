#include "doctest.h"
#include "Player.hpp"
#include "Duke.hpp"
#include "Assassin.hpp"
#include "Ambassador.hpp"
#include "Captain.hpp"
#include "Contessa.hpp"
#include "Game.hpp"
#include <exception>
#include <iostream>
#include <vector>

using namespace coup;

TEST_CASE("Good & Bad Input")
{
    Game game1;
    Duke duke{game1, "Shani"};
	Assassin assassin{game1, "Ben"};
	Ambassador ambassador{game1, "Moriya"};
	Captain captain{game1, "Netanel"};
	Contessa contessa{game1, "Tehila"};

    CHECK(game1.players().size() == 5);

    CHECK(duke.role() == "Duke");
    CHECK(contessa.role() == "Contessa");

    CHECK_THROWS(duke.coup(assassin));
    CHECK_THROWS(captain.coup(contessa));
    CHECK_THROWS(ambassador.coup(duke));
    CHECK_THROWS(game1.winner());
    
    for (size_t i = 0; i < 7; i++)
    {
        duke.income();
        assassin.income();
        ambassador.income();
        captain.income();
        contessa.income();
    }

    CHECK_EQ(duke.coins(), 7);
    CHECK_EQ(assassin.coins(), 7);
    CHECK_EQ(ambassador.coins(), 7);
    CHECK_EQ(captain.coins(), 7);
    CHECK_EQ(contessa.coins(), 7);
    

    contessa.foreign_aid();
    duke.block(contessa);
    CHECK_EQ(contessa.coins(), 7);

    ambassador.transfer(duke, contessa);
    CHECK_EQ(duke.coins(), 6);
    CHECK_EQ(contessa.coins(), 8);
    
    duke.tax();
    CHECK_EQ(duke.coins(), 9);
    duke.tax();
    CHECK_EQ(duke.coins(), 11);

    captain.steal(contessa);
    CHECK_EQ(contessa.coins(), 6);

    assassin.coup(captain);
    contessa.block(assassin);
    CHECK_EQ(game1.players().size(), 5);
    
    assassin.coup(ambassador);
    CHECK(game1.players().size() == 4);

    
}