#include "GameEngine.h"
#include "MapLoader.h"
#include <fstream>
#include<iostream>
#include<filesystem>



//default constructor
GameEngine::GameEngine() :  game_map()
{}

GameEngine::~GameEngine()
{
	delete game_map;
	game_map = NULL;
}

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
		std::cout << "PASED";
	}
	catch (int e) { std::cout << "error"; }
	/*MapLoader* loader = new MapLoader(map);
	Map* loaded_map = loader->getmap();
	std::cout << loader;
	delete loader;
	std::cout << loaded_map;
	return loader->getmap();*/
	return new Map();
}


int main()
{
	std::cout << "-----Welcom To Risk!-----\n\n";
	GameEngine game;
	std::string mapfile;
	mapfile = game.getmap();
	Map *loaded_map = game.loadmap(mapfile);


	//taking care of memory leak
	delete loaded_map;
	loaded_map = NULL;

	game.~GameEngine();

	return 0;
}