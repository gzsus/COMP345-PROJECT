

# include<iostream>
# include <string>

#include "GameEngine.h"


int main()
{
	std::cout << "-----Welcom To Risk!-----\n\n";
	GameEngine game;
	game.getmap();
	
	game.~GameEngine();

	return 0;
}