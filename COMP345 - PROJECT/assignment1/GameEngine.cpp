#include "GameEngine.h"
#include "GameEngine.h"
#include "MapLoader.h"
#include "Player.h"
#include <fstream>
#include<iostream>
#include<filesystem>



/////////////////////////////////// Constructors/Destructor /////////////////////////////////////
GameEngine::GameEngine() : game_map(), deck(), neutralPlayer(0)
{}
GameEngine::~GameEngine()
{
	delete game_map;
	delete deck;
	delete neutralPlayer;
	game_map = NULL;
	deck = NULL;
	neutralPlayer = NULL;
}
GameEngine::GameEngine(const GameEngine& old_copy)
{
	this->game_map = new Map(*(old_copy.game_map));
	this->deck = new Deck(*(old_copy.deck));
	this->neutralPlayer = new Player(*(old_copy.neutralPlayer));
}



/////////////////////////////////// Sets and gets /////////////////////////////////////
//used to pick a map
std::string GameEngine::getmap()
{
	std::vector<std::string> maps;
	std::cout << "Let's Pick a map!\n\n";
	try {
		for (auto& p : std::filesystem::directory_iterator("map_dir"))
			maps.push_back(p.path().string());
	}
	catch (int e) {std::cout << "I/O error";}

	//need to remove the first 8 characters to show only map and not path when asking for choice
	for (int i = 0; i < maps.size(); i++)
	{
		std::cout << "Map #"<<i<<" -> "<<maps[i].substr(8)<<"\n";
	}
	std::cout << "Please Enter the number of the map which you would like to select: ";
	int map_number;
	std::cin>> map_number;
	std::string selected_map = maps[map_number];

	//empty vectors to avoid memory leak
	maps.clear();

	return selected_map;
}
Map* GameEngine::loadmap(std::string map)
{
	std::string map_name = map.substr(8);
	map.append("\\");
	map.append(map_name);
	map.append(".map");
	std::cout << map;
	try
	{
		MapLoader* loader = new MapLoader(map);
		//for efficiency drop the loader and keep only a pointer to the map
		Map *loaded_map = new Map(*(loader->getmap()));
		//then dereference the map for the loader since it is now kept by the pointer above
		loader->setmap(NULL);
		//now we delete the loader without deleting the map
		delete loader;
		return loaded_map;
	}
	catch (int e) { std::cout << "error"; }

	
}

GameEngine& GameEngine::operator=(const GameEngine& oldengine)
{
	this->game_map = new Map(*(oldengine.game_map));
	this->deck = new Deck(*(oldengine.deck));
	this->neutralPlayer = new Player(*(neutralPlayer));
	return *this;
}


std::ostream& operator<<(std::ostream& ostrm, const GameEngine& game_engine)
{
	return ostrm << "Game Engine Map: \n (" << game_engine.game_map << ")";
}

/////////////////////////////////// Startup Phase ///////////////////////////////////
void GameEngine::startupPhase(Map* mapfile, std::vector<Player*>* players) {
	std::vector<Player*>playerstemp;
	std::vector<int> nums;
	int found = 0;
	int random = 0;

	//Generate the order of players. Creates a vector containing unique integers of 0 - number of players.
	while (nums.size() != players->size()) {
		found = 0;
		random = rand() % players->size();
		for (int i = 0; i < nums.size(); i++) {
			if (random == nums[i])
				found = 1;
		}
		if (found == 0)
			nums.push_back(random);
	}

	//Use each of the unique integers as the position of the player in the play order
	for (int i = 0; i < players->size(); i++) {
		playerstemp.push_back((*players)[nums[i]]);
	}

	//Assign the new vector contents to the old one.
	for (int i = 0; i < players->size(); i++) {
		(*players)[i] = playerstemp[i];
	}

	//Re-using nums for randomly assigning territories
	nums.clear();

	while (nums.size() != mapfile->get_territories().size()) {
		found = 0;
		random = rand() % mapfile->get_territories().size();
		for (int i = 0; i < nums.size(); i++) {
			if (random == nums[i])
				found = 1;
		}
		if (found == 0)
			nums.push_back(random);
	}

	//Assigning territories to each player in round robin fashion
	for (int i = 0, j = 0; i < mapfile->get_territories().size(); i++) {
			mapfile->get_territories().at(nums[i])->set_owner((*players)[j]);
			j = ++j % 5;
	}

	//Setting reinforcement pools for all players
	int playersize = players->size();
	switch (playersize) {
	case 2:
		for (int i = 0; i < playersize; i++)
			(*players)[i]->setReinforcementPool(40);
		break;
	case 3:
		for (int i = 0; i < playersize; i++)
			(*players)[i]->setReinforcementPool(35);
		break;
	case 4:
		for (int i = 0; i < playersize; i++)
			(*players)[i]->setReinforcementPool(30);
		break;
	case 5:
		for (int i = 0; i < playersize; i++)
			(*players)[i]->setReinforcementPool(25);
		break;
	}

	for (int i = 0; i < players->size(); i++) {
		// Needs deck and neutralPlayer to be initialized to run!!
		(*players)[i]->getOrders()->push_back(new Deploy(this->deck));
		(*players)[i]->getOrders()->push_back(new Bomb(this->deck));
		(*players)[i]->getOrders()->push_back(new Advance(this->deck));
		//(*players)[i]->getOrders()->push_back(new Blockade(this->deck, this->neutralPlayer));
		(*players)[i]->getOrders()->push_back(new Airlift(this->deck));
		(*players)[i]->getOrders()->push_back(new Negotiate(this->deck));
	}
}

int main()
{
	std::cout << "-----Welcom To Risk!-----\n\n";
	GameEngine game;
	std::string mapfile;
	mapfile = game.getmap();
	Map* loaded_map = game.loadmap(mapfile);

	std::cout << "\n\n";
	int num_players = 0;
	do
	{
		std::cout << "-----Please type the number of players that will play----- [2-5]: ";
		std::cin >> num_players;
	} while (num_players < 2 || num_players > 5);
	//create the appropriate number of players.
	std::vector<Player*>players;
	for (int i = 0; i < num_players; i++) { players.push_back(new Player(0)); } 
	


	std::cout << "\n\n";
	char P_obs, S_obs;
	do
	{
		std::cout << "-----PHASE OBSERVER ON?----- [y/n]: ";
		std::cin >> P_obs;
		std::cout << "-----GAME STATISTICS OBSERVER ON?----- [y/n]: ";
		std::cin >> S_obs;
	} while ((P_obs!='y' && P_obs!='n' ) || (S_obs != 'y' && S_obs != 'n'));

	////////////////////////////////////////////////Donovan Driver Start////////////////////////////////////////////////
	
	//Showing all territories are unowned before the startup phase
	for (Territory* t : loaded_map->get_territories()) {
		cout << t->get_name() << " is owned by:" << t->get_owner() << "\n";
	}

	//Showing the state of the players before the startup phase
	for (Player* p : players) {
		cout << *p<<"\n";
	}

	cout << "\n===Commencing Startup Phase===\n\n";

	game.startupPhase(loaded_map, &players);

	cout << "\n===End of Startup Phase===\n\n";

	//Showing all territories are now owned after the startup phase
	for (Territory* t : loaded_map->get_territories()) {
		cout << t->get_name() << " is owned by:" << t->get_owner() << "\n";
	}

	//Showing the state of the players after the startup phase
	for (Player* p : players) {
		cout << *p<<"\n";
	}

	////////////////////////////////////////////////Donovan Driver End////////////////////////////////////////////////

	//taking care of memory leak
	delete loaded_map;
	loaded_map = NULL;
	
	for (int i = 0; i < num_players; i++) { delete players[i]; }
	for (int i = 0; i < num_players; i++) { players[i] = NULL; }

	game.~GameEngine();

	return 0;
}
