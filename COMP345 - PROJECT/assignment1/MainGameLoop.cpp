#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <vector>
#include <string>

#include "Player.h"
#include "Map.h"
#include "MapLoader.h"

#define MAX_PLAYERS 7
#define MAX_TERRITORIES 6

using namespace std;


//	Get index of a player in a vector
static int get_player_id(Player* p, vector <Player*> v) {
	auto it = find(v.begin(), v.end(), p);
	if (it != v.end()) {
		int index = it - v.begin();
		return index;
	}
	else {
		std::cout << "-1" << endl;
	}
}


//	Players are given a number of armies
static int* reinforcementPhase(vector<Player*> allPlayers, int num_players, Map* map) {

	int reinforcements[MAX_PLAYERS];	//	7 players is the max
	int territories_owned[MAX_PLAYERS] = { 0,0,0,0,0,0,0 };

	/**************************** Count each player's territories ****************************/

	for (Territory* territory : map->get_territories()) {
		Player* owner = territory->get_owner();
		if (owner == NULL)
			continue;

		int owner_id = get_player_id(owner, allPlayers);
		if (owner_id > -1)
			territories_owned[owner_id] += 1;

	}

	for (int i = 0; i < num_players; i++) {	// Reinforcement per player calculation
		reinforcements[i] = territories_owned[i] / 3;
		std::cout << "Player" << i << " reinforcements: " << reinforcements[i] << endl;
	}

	/**************************** Add each player continent's bonus ****************************/
	/*for (Continent* continent : map->get_continents()) {
		if (continent->get_owner() == NULL)
			continue;

		for (int i = 0; i < num_players; i++) {
			if (continent->get_owner() == allPlayers[i])
				territories_owned[i] += continent->get_bonus();
		}
	}*/

	return reinforcements;
}


//	Territories in the map to be defended by the player
vector<Territory*> toDefend(Player* player, Map* map) {
	return map->get_territories(player);
}


//	Territories in the map to be defended by the player
vector<Territory*> toAttack(Player* player, vector<Territory*>owned_terrritories) {

	vector<Territory*> neighbouring_terrritories;

	// Get neighbour territories ( territories to attack )
	for (Territory* owned : owned_terrritories) {
		vector<Territory*> tNeighbours = owned->get_neighbours();
		for (Territory* neighbour : tNeighbours) {
			if (!(std::find(neighbouring_terrritories.begin(), neighbouring_terrritories.end(), neighbour) != neighbouring_terrritories.end()))
				if (neighbour->get_owner() != player)
					neighbouring_terrritories.push_back(neighbour);
				else continue;
		}
	}
	return neighbouring_terrritories;
}


// A player chooses his orders
int issueOrder(Player* player, int player_id, Map* map) {

	cout << " Player " << player_id << " Orders \n";

	vector<Territory*> owned_terrritories = toDefend(player, map);
	vector<Territory*> territories_toAttack = toAttack(player, owned_terrritories);

	//
	cout << " Territories to attack:";
	for (int i = 0; i < territories_toAttack.size(); i++)
		cout << "  (" << i << ")" + territories_toAttack[i]->get_name() + "-" << territories_toAttack[i]->get_armies();
	cout << endl;

	return 0;
}


//
int issueOrderPhase(vector<Player*> allPlayers, int num_players, Map* map) {

	for (int i = 0; i < num_players; i++) {
		issueOrder(allPlayers[i], i, map);
	}
	return 0;
}


//
int executeOrdersPhase() {

	return 0;
}



// Main loop of the game
static Player* mainGameLoop(vector<Player*> allPlayers, Map* map) {

	//	Amount of players
	int num_players = allPlayers.size();
	//	Array of vectors containing terrritories owned by each player
	vector<Territory*> territories_owned[MAX_PLAYERS];

	//	Main loop of game
	//while (1) {

	std::cout << "\n Reinforcement Phase\n";
	int* reinforcements = reinforcementPhase(allPlayers, num_players, map);

	std::cout << "\n Order Issuing Phase\n";
	issueOrderPhase(allPlayers, num_players, map);

	std::cout << "\n Order Execution Phase\n";
	executeOrdersPhase();

	//}
	return allPlayers[0];
}


int main() {
	std::cout << "\tWelcome to WARZONE!" << endl;

	//	Intialize Number of Players
	int numberOfPlayers = 0;
	while (true) {
		std::cout << "Enter the number of people playing today: ";

		try {
			cin >> numberOfPlayers;
			if (!(numberOfPlayers > 1 && numberOfPlayers < 8)) {
				throw numberOfPlayers;
			}
			break;
		}
		catch (int x) {
			std::cout << "[ERROR]: Invalid amount of players. Try a number between 2 and 7" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
	}


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
	Territory* can = new Territory("Canada", 2, na);
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
	can->set_owner(allPlayers[1]);
	usa->set_owner(allPlayers[1]);
	mex->set_owner(allPlayers[1]);
	gua->set_owner(allPlayers[0]);
	sal->set_owner(allPlayers[1]);
	hon->set_owner(allPlayers[1]);

	// Add continents to map
	america->add_continent(na);
	america->add_continent(ca);

	std::cout << "\n\tGame loop\n";
	mainGameLoop(allPlayers, america);

	// End of game
	std::cout << "\n\tGame finished\n";
	system("pause");
}