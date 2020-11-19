#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

#include "Player.h"
#include "Map.h"
#include "Orders.h"
#include "Cards.h"

using std::endl;
using std::cout;
using std::string;
using std::ostream;
using std::vector;
using std::find;



int main() {
	//NEEDED FOR Advance order
	srand(time(0));
	Deck* deck = new Deck();



	//FILLER CODE FROM MAINGAMELOOP
	int numberOfPlayers = 2;
	//	Intializes Players vector
	vector <Player*> allPlayers;

	for (int i = 0; i < numberOfPlayers; i++) {
		Player* pPlayer = new Player(numberOfPlayers);
		allPlayers.push_back(pPlayer);
	}


	

	// Initialize a map
	Map* america = new Map();

	// Pointers to new continents (Name)
	Continent* na = new Continent("NorthAmerica");
	Continent* ca = new Continent("CentralAmerica");

	// Pointers to new territories (Name,armies,continent)
	Territory* can = new Territory("Canada", 4, na);
	Territory* usa = new Territory("USA", 2, na);
	Territory* mex = new Territory("Mexico", 2, na);
	Territory* gua = new Territory("Guatemala", 2, ca);
	Territory* sal = new Territory("ElSalvador", 2, ca);
	Territory* hon = new Territory("Honduras", 2, ca);

	// Establishing connections between territories (both sides)
	usa->connet_to(can);
	usa->connet_to(mex);
	mex->connet_to(gua);
	gua->connet_to(sal);
	gua->connet_to(hon);
	hon->connet_to(sal);

	// Give continents to players
	can->set_owner(allPlayers[0]);
	usa->set_owner(allPlayers[1]);
	mex->set_owner(allPlayers[0]);
	gua->set_owner(allPlayers[1]);
	sal->set_owner(allPlayers[0]);
	hon->set_owner(allPlayers[0]);

	// Add continents to map
	america->add_continent(na);
	america->add_continent(ca);

	//std::cout << typeid(*allPlayers[0]).name() << std::endl;

//-------------------------------------------------------------------------
	//DEPLOY WORKS FOR DUMMY VALUE

	//std::cout << can->get_armies() << std::endl;

	//Deploy* deploy = new Deploy();

	//deploy->execute(allPlayers[0], usa, 2);

	//std::cout << can->get_armies() << std::endl;

	//-------------------------------------------------------------------------

		//ADVANCE MISSING CARD METHOD

		//std::cout << "source:" <<can->get_armies() << std::endl;
		//std::cout << "target:" <<usa->get_armies() << std::endl;

		//Advance* advance = new Advance();
		//advance->execute(allPlayers[0],can,usa,2);

		//std::cout << "source:" << can->get_armies() << std::endl;
		//std::cout << "target:" << usa->get_armies() << std::endl;

	//-------------------------------------------------------------------------


		//AIRLIFT NOT MAKING SENSE

	//cout << "source:" << can->get_armies() << endl;
	//cout << "target:" << hon->get_armies() << endl;

	//Airlift* airlift = new Airlift();
	//airlift->execute(allPlayers[0], can, hon, 2);
	
	//airlift(allPlayers[0],can,hon,2);

	//cout << "source:" << can->get_armies() << endl;
	//cout << "target:" << hon->get_armies() << endl;

	//-------------------------------------------------------------------------

		//BOMB MUST HAVE CARD FROM PLAYER
		//std::cout << "target:" << usa->get_armies() << std::endl;

		//Bomb* bomb = new Bomb();
		//bomb->execute(allPlayers[0],usa);

		//std::cout << "target:" << usa->get_armies() << std::endl;

	//-------------------------------------------------------------------------


		//BLOCKADE NEEDS TO CALL THE CARD AND NEUTRAL TERRITORY
		std::cout << "target:" << usa->get_armies() << std::endl;

		//NEUTRAL PLAYER MUST BE IMPLEMENTED HERE
		allPlayers[1]->getHand()->add("blockade");
		Blockade* blockade = new Blockade(deck);
		blockade->execute(allPlayers[1], usa);

		std::cout << "target:" << usa->get_armies() << std::endl;


	//-------------------------------------------------------------------------

		//NEGOTIATE
	//allPlayers[0]->getHand()->add("diplomacy");
	//Negotiate* negotiate = new Negotiate(deck);
	//negotiate->execute(allPlayers[0], allPlayers[1]);

	//allPlayers[0]->getHand()->add("bomb");
	//std::cout << "target:" << gua->get_armies() << std::endl;
	//Bomb* bomb = new Bomb(deck);
	//bomb->execute(allPlayers[0], gua);
	//std::cout << "target:" << gua->get_armies() << std::endl;
	//

	//Advance* advance = new Advance(deck);
	//advance->execute(allPlayers[0], can, usa, 2);


	//allPlayers[0]->getHand()->add("airlift");
	//Airlift* airlift = new Airlift(deck);
	//airlift->execute(allPlayers[0], can, usa, 2);

}