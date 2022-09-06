#include <iostream>
#include <vector>
#include <exception>
#include "sources/Player.hpp"
#include "sources/Duke.hpp"
#include "sources/Assassin.hpp"
#include "sources/Ambassador.hpp"
#include "sources/Captain.hpp"
#include "sources/Contessa.hpp"
#include "sources/Game.hpp"

using namespace coup;
using namespace std;

int main()
{
    // Game scenario1{};
    // Duke PlayerONE{scenario1, "Player ONE"};
	// Assassin PlayerTWO{scenario1, "Player TWO"};
	// Duke PlayerTHREE{scenario1, "Player THREE"};
	// Contessa PlayerFOUR{scenario1, "Player FOUR"};

    // for (size_t i = 0; i < 3; i++)
    // {
    //     PlayerONE.income();
    //     PlayerTWO.income();
    //     PlayerTHREE.income();
    //     PlayerFOUR.income();
    // }
    // cout<<scenario1.turn_index<<endl;
    // cout<<scenario1.turn()<<endl;
    // PlayerONE.tax();
    // cout<<scenario1.turn_index<<endl;
    // cout << scenario1.turn() <<endl;
    // PlayerTWO.coup(PlayerONE); // Player TWO is an assassin and can coup with 3 coins
    // cout<<scenario1.turn_index<<endl;
    // cout << scenario1.turn();
    // PlayerTHREE.tax();
    // PlayerFOUR.block(PlayerTWO);
    // cout << PlayerONE.isAlive;
    // cout << scenario1.players().size();

    // Game scenario4{};
    // Assassin assassin{scenario4, "Player ONE"};
    // Contessa contessa{scenario4, "Player TWO"};
    // Duke duke{scenario4, "Player THREE"};

    // std::vector<Player*> Players = {&assassin, &contessa, &duke};
    // for (size_t j = 0; j < 5; j++)
    // {
    //     for (size_t i = 0; i < Players.size(); i++)
    //     {
    //        Players.at(i)->income();
    //     }
    // }
    // assassin.coup(duke); // Assassin can coup with 3 coins
    // cout<<assassin.coins()<<endl; // The coup cost the assassin only 3 coins.
    // cout <<scenario4.players().size()<<endl; // Player THREE is out of the game=2
    // contessa.block(assassin); // Player THREE is back in the game
    // cout<<scenario4.players().size()<<endl;//3
    // cout<<assassin.coins()<<endl; //=2 The block of the contessa DID NOT refund the assassin.
    // contessa.income(); 
    // duke.income();
    // for (size_t j = 0; j < 3; j++)
    // {
    //     for (size_t i = 0; i < Players.size(); i++)
    //     {
    //         if (i==0) {
    //             Players.at(i)->foreign_aid();
    //         } else {
    //             Players.at(i)->income();
    //         }
    //     }
    // }
    // cout<<assassin.coins()<<endl; // Assassin has now 8 coins, so he can coup without being blocked by contessa.
    // cout<<scenario4.players().size()<<endl;//=3
    // cout<<duke.isAlive<<endl;
    // assassin.coup(duke); // Player THREE is out of the game
    // cout<<duke.isAlive<<endl;
    // cout<<assassin.coins()<<endl; //=1 The coup cost the assassin 7 coins and is unblockable.
    // cout<<scenario4.players().size()<<endl;//=2
    // try {
    //     contessa.block(assassin); // Read explanation at lines 158-160
    // }
    // catch (exception &ex)
    // {
    //     cout << "caught exception: " << ex.what() << endl;
    // }
    // cout << scenario4.players().size() <<endl; //=2 Player THREE is still out of the game, the contessa couldn't block the assassin
    // cout << assassin.coins()<<endl; //=1

//     Game scenario3{};
//     Ambassador PlayerONE{scenario3, "Player ONE"};
// 	Contessa PlayerTWO{scenario3, "Player TWO"};
//     Duke PlayerTHREE{scenario3, "Player THREE"};
//     vector<Player*> Players = {&PlayerONE, &PlayerTWO, &PlayerTHREE};

//     for (size_t j = 0; j < 8; j++)
//     {
//         for (size_t i = 0; i < Players.size(); i++)
//         {
//             Players.at(i)->income();
//         }
//     }

// try{
//     PlayerONE.transfer(PlayerTWO, PlayerTHREE);
//     cout<<PlayerTWO.coins()<<endl; //7
//     cout<<PlayerTHREE.coins()<<endl; //9
//     PlayerTWO.coup(PlayerTHREE);
//     // PlayerONE.coup(PlayerTHREE); // player three already dead
//     PlayerONE.coup(PlayerTWO);
//     cout<<scenario3.winner();
// }
// catch (exception &ex) {
//     cout<< ex.what();

// }



    // Game game{};
    // Duke duke(game, "first");
    // Contessa contessa(game, "second");
    // cout<< game.players()[0]<<endl;
    // cout<<game.players()[1]<<endl;
    // for (uint i = 0; i < 5; i++)
    // {
    //     duke.foreign_aid();
    //     contessa.foreign_aid();
    // }
    // duke.coup(contessa);
    // cout<<contessa.isAlive<< "alive"<<endl;
    // cout<<game.turn()<<endl;
    
    Game game_11{}; // build game . add players
	Assassin assassin{game_11, "Yossi2"};
	Duke duke{game_11, "Moshe"};
	Assassin assassin2{game_11, "Yossi"};
	Ambassador ambassador{game_11, "Meirav"};
	Captain captain{game_11, "Reut"};
	Contessa contessa{game_11, "Gilad"};

	for (int i=0 ; i<6 ; i++){
		assassin.income();
		duke.income();
		assassin2.income();
		ambassador.income();
		captain.income();
		contessa.income();
	}
	// each one has 6 coins
	assassin.coup(ambassador); // assassin 3
	contessa.block(assassin);
	duke.tax(); //duke 9
	assassin2.foreign_aid(); // assassin2 8
	duke.block(assassin2); // assassin2 6
	ambassador.transfer(assassin,contessa); // assassin 2, contessa 7
	captain.steal(contessa); // contessa 5, captain 8
	ambassador.block(captain); // contessa 7, captain 6
    cout<<contessa.coins()<<endl;
    cout<<captain.coins()<<endl;
	contessa.coup(duke); // contessa 0

	cout<<assassin.coins()<<" ?is 2"<<endl;
	cout<<ambassador.coins()<<" ?is 6"<<endl;
	cout<<captain.coins()<<" ?is 6"<<endl;
	cout<<contessa.coins()<<" ?is 0"<<endl;
}
