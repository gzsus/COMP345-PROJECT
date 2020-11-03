#include "GameEngine.h"
#include <fstream>
#include<iostream>
#include<filesystem>



//default constructor
GameEngine::GameEngine()
{}

GameEngine::~GameEngine()
{
	delete game_map;
	game_map = NULL;
}

//used to pick a map
std::string GameEngine::getmap()
{

	std::cout << "Let's Pick a map!\n";
	try {
		
		for (auto& p : std::filesystem::directory_iterator("map_dir"))
			std::cout << p.path() << '\n';
	}

	catch (int e) {std::cout << "I/O error";}
	

	return std::string();
}