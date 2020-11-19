#include "MainGameLoop.h"


using namespace std;


//	Get index of a player in a vector
int MainGameLoop::get_player_id(Player* p, vector <Player*> v) {
	auto it = find(v.begin(), v.end(), p);
	if (it != v.end()) {
		int index = it - v.begin();
		return index;
	}
	else {
		cout << "-1" << endl;
	}
}

void MainGameLoop::setPhaseObserver(bool phaseMode) {
	phase = phaseMode;
}

bool MainGameLoop::getPhaseObserver() {
	return phase;
}

void MainGameLoop::setStatisticsObserver(bool statisticsMode) {
	statistics = statisticsMode;
}

bool MainGameLoop::getStatisticsObserver() {
	return statistics;
}

//	Players are given a number of armies
int* MainGameLoop::reinforcementPhase(vector<Player*> allPlayers, int num_players, Map* map) {

	static int reinforcements[MAX_PLAYERS];	//	5 players is the max
	int territories_owned[MAX_PLAYERS] = { 0,0,0,0,0 };

	/**************************** Count each player's territories ****************************/

	for (Territory* territory : map->get_territories()) {
		Player* owner = territory->get_owner();
		if (owner == NULL)
			continue;

		int owner_id = get_player_id(owner, allPlayers);
		if (owner_id > -1)
			territories_owned[owner_id] += 1;

	}

	int total_territories = map->get_territories().size();

	if (getStatisticsObserver()) {
		cout << "\nGame Statistics\n" << endl;
		cout << "Player ID" << "\t" << "Territories Owned" << "\t" << "Percentage of Map Owned" << "\n";
		for (int i = 0; i < num_players; i++) {
			GameObservers* go = new GameObservers();
			go->statisticsView(territories_owned[i], total_territories, (i + 1));
			delete go;
			go = NULL; 
		}
	}

	for (int i = 0; i < num_players; i++) {	// Reinforcement per player calculation
		reinforcements[i] = (territories_owned[i] / 3) + MIN_REINFORCEMENT;

		if (getPhaseObserver()) {
			cout << "\nPlayer " << (i + 1) << ": Reinforcement Phase" << endl;
			GameObservers* go = new GameObservers(); 
			go->reinforcementPhaseView();
			delete go;
			go = NULL; 
		}
		cout << "Reinforcements: " << reinforcements[i] << endl;
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



// Part of the loop reserved to issuing orders
int MainGameLoop::issueOrderPhase(vector<Player*> allPlayers, int num_players, Map* map, int* reinforcements) {

	for (Player* p : allPlayers) {
		int id = get_player_id(p, allPlayers);
		p->issueOrder(id, map, *(reinforcements + id), getPhaseObserver());
		cout << "\n";



	}
	return 0;
}


int MainGameLoop::executeOrdersPhase(vector<Player*> allPlayers) {
	for (Player* p : allPlayers) {
		int id = get_player_id(p, allPlayers);
		if (getPhaseObserver()) {
			cout << "\nPlayer " << (id + 1) << ": Order Execution Phase" << endl;
			GameObservers* go = new GameObservers();
			go->executeOrderPhaseView();
			delete go;
			go = NULL;
		}
	}

	return 0;
}



// Main loop of the game
Player* MainGameLoop::mainGameLoop(vector<Player*> allPlayers, Map* map, bool phaseMode, bool statisticsMode) {

	setPhaseObserver(phaseMode);
	setStatisticsObserver(statisticsMode);

	//	Amount of players
	int num_players = allPlayers.size();
	//	Array of vectors containing terrritories owned by each player
	vector<Territory*> territories_owned[MAX_PLAYERS];

	//	Main loop of game
	//while (1) {

	int* reinforcements = reinforcementPhase(allPlayers, num_players, map);


	/*cout << "Reinforcement Pool: " << *(reinforcements);
	for (int i = 1; i < num_players; i++) {
		cout << ", " << *(reinforcements + i);
	}*/

	issueOrderPhase(allPlayers, num_players, map, reinforcements);

	executeOrdersPhase(allPlayers);

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
			if (!(numberOfPlayers > 1 && numberOfPlayers < 6)) {
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
	MainGameLoop* loop = new MainGameLoop();

	// Temporary for the demo
	bool phaseMode = false;
	bool statisticsMode = false; 

	loop->mainGameLoop(allPlayers, america, phaseMode, statisticsMode);

	delete loop;
	// End of game
	cout << "\n\t\tGame finished\n";
	system("pause");
}