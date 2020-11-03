#pragma once
#include "Map.h"
#include<string>

class GameEngine
{

private:
	//needs to be a pointer
	Map *game_map;


public:
	//default constructor
	GameEngine();
	//destructor
	~GameEngine();

	std::string getmap();



};

