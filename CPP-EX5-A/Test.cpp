#include "doctest.h"
#include <exception>
#include <iostream>
#include <vector>
#include "sources/OrgChart.hpp"

using namespace ariel;

/*
MyOrganization:
                                    Uri
                                    |
                        ------------------------------
                        |                            |
                        Alon                       Galya
                        |                            |
                    ----------              -------------------
                    |        |              |         |        |
                    Ben      Netanel        Shani   Liat    Tehila
                    |                         |       |
                    -----                   ------  ------
                    |                         |       |
                    Vico                     Ron    Mirit
                                              |
                                            -------
                                            |     |
                                            Ziv  Fanun
*/

TEST_CASE("Family Oraganization")
{
    OrgChart family_org;
    // check not throw add root and sub
    CHECK_NOTHROW(family_org.add_root("Uri"));
    CHECK_NOTHROW(family_org.add_sub("Uri", "Alon"));
    CHECK_NOTHROW(family_org.add_sub("Uri", "Galya"));
    CHECK_NOTHROW(family_org.add_sub("Alon", "Ben"));
    CHECK_NOTHROW(family_org.add_sub("Alon", "Netanel"));
    CHECK_NOTHROW(family_org.add_sub("Galya", "Shani"));
    CHECK_NOTHROW(family_org.add_sub("Galya", "Liat"));
    CHECK_NOTHROW(family_org.add_sub("Galya", "Tehila"));
    CHECK_NOTHROW(family_org.add_sub("Ben", "Vico"));
    CHECK_NOTHROW(family_org.add_sub("Shani", "Ron"));
    CHECK_NOTHROW(family_org.add_sub("Ron", "Ziv"));
    CHECK_NOTHROW(family_org.add_sub("Ron", "Fanun"));
    CHECK_NOTHROW(family_org.add_sub("Liat", "Mirit"));

    // check throw add root and sub
    CHECK_THROWS(family_org.add_sub("Pitbull", "Justin")); // Pitbull doesnt exists
    CHECK_THROWS(family_org.add_sub("Justin", "Hailey"));  // Justin doesnt exists
    CHECK_THROWS(family_org.add_sub("Shirly", "Noya"));    // shirly doesnt exists
    CHECK_THROWS(family_org.add_sub("Efrat", "Michal"));   // Efrat doesnt exists
    CHECK_THROWS(family_org.add_sub("Talya", "Noa"));      // Talya doesnt exists

    // check root
    CHECK_EQ(*(family_org.begin()), "Uri");

    // check level order
    std::vector<std::string> LevelOrderAns = {"Ziv", "Fanun", "Vico", "Ron", "Mirit", "Ben", "Netanel", "Shani", "Liat",
                                              "Tehila", "Alon", "Galya", "Uri"};

    OrgChart::Iterator it = family_org.begin_level_order();
    for (unsigned int i = 0; i < LevelOrderAns.size(); i++)
    {
        CHECK(*it == LevelOrderAns[i]);
        it++;
    }

    // check reverse order
    std::vector<std::string> ReverseOrderAns = {"Uri", "Alon", "Galya", "Ben", "Netanel", "Shani", "Liat",
                                                "Tehila", "Vico", "Ron", "Mirit", "Ziv", "Fanun"};

    it = family_org.begin_reverse_order();
    for (unsigned int i = 0; i < ReverseOrderAns.size(); i++)
    {
        CHECK(*it == ReverseOrderAns[i]);
        it++;
    }

    // check pre order
    std::vector<std::string> PreOrderAns = {"Uri", "Alon", "Ben", "Vico", "Netanel", "Galya", "Shani",
                                            "Ron", "Ziv", "Fanun", "Liat", "Mirit", "Tehila"};

    it = family_org.begin_preorder();
    for (unsigned int i = 0; i < PreOrderAns.size(); i++)
    {
        CHECK(*it == PreOrderAns[i]);
        it++;
    }
}
