#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <vector>
#include <string>

#include "Player.h"
#include "Map.h"


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
		cout << "-1" << endl;
	}
}


//	Read an integer from the user only
static int get_integer_option() {
	int option = -1;

	while (!(cin >> option)) {
		cin.clear();              //to clear the buffer memory
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Please enter a valid number";
	}
	return option;
}


//	Players are given a number of armies
int* reinforcementPhase(vector<Player*> allPlayers, int num_players, Map* map) {

	static int reinforcements[MAX_PLAYERS];	//	7 players is the max
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
		cout << "Player" << i << " reinforcements: " << reinforcements[i] << endl;
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
list<Territory*> toAttack(Player* player, Map* map) {
	vector<Territory*> territories_toAttack = map->get_neighbour_territories(player);

	list<Territory*> territories_list;

	if (territories_toAttack.size() > 0){
		//	Show possible attack
		cout << " Territories to attack:";
		for (int i = 0; i < territories_toAttack.size(); i++)
			cout << "  (" << i << ")" + territories_toAttack[i]->get_name() + "-" << territories_toAttack[i]->get_armies();
		cout << endl;

		cout << "Choose the territory to attack or any other number to finish: ";

		int option = get_integer_option();
		while ( true ) {
			//	Show chosen option
			if (option > -1 && option < territories_toAttack.size()){

				// Check if element is already chosen
				list<Territory*>::iterator it;
				it = find(territories_list.begin(), territories_list.end(), territories_toAttack[option]);

				if (it != territories_list.end())
					cout << "(already chosen)";
				else{
					cout << territories_toAttack[option]->get_name();
					territories_list.push_back(territories_toAttack[option]);
				}
			}
			else {
				cout << "none\n";
				break;
			}
			cout << "\n Which other? ";
			option = get_integer_option();
		}
	}
	cout << endl;
	return territories_list;
}


//	Territories in the map to be defended by the player
list<Territory*> toDefend(Player* player, Map* map) {

	vector<Territory*> territories_owned = map->get_territories(player);

	list<Territory*> territories_toDefend ;

	if (territories_owned.size() > 0) {
		//	Show possible defend
		cout << " Territories to defend-armies:";
		for (int i = 0; i < territories_owned.size(); i++)
			cout << "  (" << i << ")" + territories_owned[i]->get_name() + "-" << territories_owned[i]->get_armies();
		cout << endl;
	}
	else {
		cout << " You own 0 territories" << endl;
		return territories_toDefend;
	}

	cout << "Choose the territory number to defend or any other number to finish: ";

	int option = get_integer_option();
	while (true) {
		//	Show chosen option
		if (option > -1 && option < territories_owned.size()) {

			// Check if element is already chosen
			list<Territory*>::iterator it;
			it = find(territories_toDefend.begin(), territories_toDefend.end(), territories_owned[option]);

			if (it != territories_toDefend.end())
				cout << "(already chosen)";
			else{
				cout << territories_owned[option]->get_name();
				territories_toDefend.push_back(territories_owned[option]);
			}
		}
		else {
			cout << "none\n";
			break;
		}
		cout << "\n Which other? ";
		option = get_integer_option();
	}
	cout << endl;
	return territories_toDefend;
}


//	A player chooses his orders
int issueOrder(Player* player, int player_id, Map* map, int* reinforcements) {

	cout << "\t--- Player " << player_id << " Orders ---\n";

	list<Territory*> territories_toAttack = toAttack(player, map);
	list<Territory*> territories_toDefend = toDefend(player, map);

	int territories_toAttack_number = territories_toAttack.size();
	int territories_toDefend_number = territories_toDefend.size();

	int deployments_available = *(reinforcements+ player_id);

	//	For every choice made on the territories to defend
	int count = 1;

	if( territories_toDefend_number > 0 ){

		cout << " Deployment Orders: \n";
		for (auto t : territories_toDefend) {

			if (deployments_available > 0) {
				cout << "  (" << count << ")  " << *t;
				cout << "You have " << deployments_available << " available. How many would you like to deploy in " << t->get_name() << "? ";

				//	Choose the amount of armies to deploy in that 
				int armies = get_integer_option();
				if (armies < 0 || armies > deployments_available) {
					while (true) {
						cout << "Please choose a valid option...";
						armies = get_integer_option();
						if (armies > 0 && armies <= deployments_available)
							break;
					}
				}

				//	Create specific deploy order
				t->increment_armies(armies);
				deployments_available -= armies;
				cout << " Deploy Order Issued!";

				if (deployments_available <= 0)
					break;
			}
			else {
				cout << "You have 0 armies available to deploy";
				break;
			}

			count++;
		}
	}

	count = 1;


	vector<Territory*> territories_owned = map->get_territories(player);

	if ( territories_owned.size() > 0 ) {


		for (auto t : territories_owned) {
			

		}

		//for (auto t : territories_toAttack) {
		//	cout << "\n  (" << count << ")  " << *t;
		//	count++;
		//}

	}
	cout << endl;
	

	return 0;
}


//
int issueOrderPhase(vector<Player*> allPlayers, int num_players, Map* map, int* reinforcements) {

	for (int i = 0; i < num_players; i++) {
		issueOrder(allPlayers[i], i, map, reinforcements);
		cout << endl;
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

	cout << "\n\n\tReinforcement Phase\n\n";
	int* reinforcements = reinforcementPhase(allPlayers, num_players, map);


	cout << "Reinforcement Pool: " << *(reinforcements);
	for (int i = 1; i < num_players; i++) {
		cout << ", " << *(reinforcements + i);
	}

	cout << "\n\n\tOrder Issuing Phase\n\n";
	issueOrderPhase(allPlayers, num_players, map, reinforcements);

	cout << "\n\n\tOrder Execution Phase\n\n";
	executeOrdersPhase();

	//}
	return allPlayers[0];
}


int main() {
	cout << "\tWelcome to WARZONE!\n\n";

	//	Intialize Number of Players
	int numberOfPlayers = 0;
	while (true) {
		cout << "Enter the number of people playing today: ";

		try {
			cin >> numberOfPlayers;
			if (!(numberOfPlayers > 1 && numberOfPlayers < 8)) {
				throw numberOfPlayers;
			}
			break;
		}
		catch (int x) {
			cout << "[ERROR]: Invalid amount of players. Try a number between 2 and 7" << endl;
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
	can->set_owner(allPlayers[0]);
	usa->set_owner(allPlayers[0]);
	mex->set_owner(allPlayers[0]);
	gua->set_owner(allPlayers[1]);
	sal->set_owner(allPlayers[0]);
	hon->set_owner(allPlayers[0]);

	// Add continents to map
	america->add_continent(na);
	america->add_continent(ca);

	cout << "\n\n============== Game loop ==============\n";
	mainGameLoop(allPlayers, america);

	// End of game
	cout << "\n\t\tGame finished\n";
	system("pause");
}