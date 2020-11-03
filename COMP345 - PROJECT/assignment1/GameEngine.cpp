#include "GameEngine.h"
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
	std::cout << "Please Enter the number of the map which you would like to select: \n";
	int map_number;
	std::cin>> map_number;




	return std::string();
}




int main()
{
	std::cout << "-----Welcom To Risk!-----\n\n";
	GameEngine game;
	game.getmap();

	game.~GameEngine();

	return 0;
}