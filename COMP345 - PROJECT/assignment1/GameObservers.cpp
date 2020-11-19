#include "MainGameLoop.h"
#include "Player.h"
#include "Orders.h"
#include "Cards.h"
#include "Map.h"
#include "GameObservers.h"

void GameObservers::reinforcementPhaseView() {
	cout << "In this phase, the number of elements in the players reinforcement pool is displayed" << endl;
}

void GameObservers::issueOrderPhaseView() {
	cout << "In this phase, players issue orders and place them in their order list.\n" << endl;
}

void GameObservers::executeOrderPhaseView() {
	cout << "In this phase, orders at the top order on the list of orders of each player are executed in a round - robin fashion\n" << endl;
}

void GameObservers::statisticsView(int territories_owned, int total_territories, int player_id) {
	int total = (territories_owned * 100) / total_territories;
	if (territories_owned != 0) {
		cout << "Player " << player_id << "\t" << territories_owned << "\t\t\t" << total << "\n";
	}
}

// int main() {
// 	cout << "Welcome to WARZONE!\n\n";

// 	//	Intialize Number of Players
// 	int numberOfPlayers = 0;
// 	while (true) {
// 		cout << "Enter the number of people playing today: ";

// 		try {
// 			cin >> numberOfPlayers;
// 			if (!(numberOfPlayers > 1 && numberOfPlayers < 8)) {
// 				throw numberOfPlayers;
// 			}
// 			break;
// 		}
// 		catch (int x) {
// 			cout << "[ERROR]: Invalid amount of players. Try a number between 2 and 7." << endl;
// 			cin.clear();
// 			cin.ignore(1000, '\n');
// 		}
// 	}

// 	//	Intializes Players vector
// 	vector <Player*> allPlayers;

// 	for (int i = 0; i < numberOfPlayers; i++) {
// 		Player* pPlayer = new Player(numberOfPlayers);
// 		allPlayers.push_back(pPlayer);
// 	}

// 	char P_obs, S_obs;
// 	do
// 	{
// 		std::cout << "-----PHASE OBSERVER ON?----- [y/n]: ";
// 		std::cin >> P_obs;
// 		std::cout << "-----GAME STATISTICS OBSERVER ON?----- [y/n]: ";
// 		std::cin >> S_obs;
// 	} while ((P_obs != 'y' && P_obs != 'n') || (S_obs != 'y' && S_obs != 'n'));

// 	bool phaseMode;
// 	bool statisticsMode;
// 	if (P_obs == 'y') {
// 		phaseMode = true;
// 	}
// 	else {
// 		phaseMode = false;
// 	}

// 	if (S_obs == 'y') {
// 		statisticsMode = true;
// 	}
// 	else {
// 		statisticsMode = false;
// 	}

// 	// Initialize a map
// 	Map* america = new Map();

// 	// Pointers to new continents (Name)
// 	Continent* na = new Continent("NorthAmerica");
// 	Continent* ca = new Continent("CentralAmerica");

// 	// Pointers to new territories (Name,armies,continent)
// 	Territory* can = new Territory("Canada", 2, na);
// 	Territory* usa = new Territory("USA", 2, na);
// 	Territory* mex = new Territory("Mexico", 2, na);
// 	Territory* gua = new Territory("Guatemala", 2, ca);
// 	Territory* sal = new Territory("ElSalvador", 2, ca);
// 	Territory* hon = new Territory("Honduras", 2, ca);

// 	// Establishing connections between territories (both sides)
// 	usa->connet_to(can);
// 	usa->connet_to(mex);
// 	mex->connet_to(gua);
// 	gua->connet_to(sal);
// 	gua->connet_to(hon);
// 	hon->connet_to(sal);

// 	// Give continents to players
// 	can->set_owner(allPlayers[0]);
// 	usa->set_owner(allPlayers[0]);
// 	mex->set_owner(allPlayers[0]);
// 	gua->set_owner(allPlayers[1]);
// 	sal->set_owner(allPlayers[0]);
// 	hon->set_owner(allPlayers[0]);

// 	// Add continents to map
// 	america->add_continent(na);
// 	america->add_continent(ca);

// 	cout << "\n\n============== Game loop ==============\n";
// 	MainGameLoop* loop = new MainGameLoop();
// 	loop->mainGameLoop(allPlayers, america, phaseMode, statisticsMode);

// 	delete loop;
// 	loop = nullptr;

// 	delete america;

// 	for (size_t i = 0; i < allPlayers.size(); i++)
// 	{
// 		delete allPlayers[i];
// 		allPlayers[i] = nullptr;
// 	}

// 	// End of game
// 	cout << "\nGame finished\n";
// 	system("pause");
// }