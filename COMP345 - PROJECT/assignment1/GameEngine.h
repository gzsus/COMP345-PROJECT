#pragma once
#include "Map.h"
#include "MapLoader.h"
#include "Cards.h"
#include "Player.h"
#include <string>

class GameEngine
{

private:
	//needs to be a pointer
	Map *game_map;
	Player *neutralPlayer;
	Deck *deck;


public:
	/////////////////////////////////// Constructors/Destructor /////////////////////////////////////
	GameEngine();
	GameEngine(const GameEngine& old_copy);
	~GameEngine();

	/////////////////////////////////// Sets and gets /////////////////////////////////////
	std::string getmap();
	Map* loadmap(std::string map);
	GameEngine& operator =(const GameEngine& oldengine);// assignment operator

	friend std::ostream& operator<<(std::ostream&, const GameEngine&); //stream insertion operator
	
	/////////////////////////////////// Startup Phase ///////////////////////////////////
	void startupPhase(Map* mapfile, std::vector<Player*>* players);



	/////////////////////////////////// Loop Phase ///////////////////////////////////

	int get_player_id(Player* p, std::vector <Player*> v);

	Player* mainGameLoop(std::vector<Player*> allPlayers, Map* map, bool phaseMode);
	int* reinforcementPhase(std::vector<Player*> allPlayers, int num_players, Map* map);
	int issueOrderPhase(std::vector<Player*> allPlayers, int num_players, Map* map, int* reinforcements, bool phaseMode);
	int executeOrdersPhase();


};



