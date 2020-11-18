#pragma once
#include "Map.h"
#include "MapLoader.h"
#include "Cards.h"
#include<string>

class GameEngine
{

private:
	//needs to be a pointer
	Map *game_map;
	Deck* game_deck;



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
};

