//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//								MapDriver.cpp - Adrian Marquez
//
//	The Map class is implemented as a connected graph.
//	The graph’s nodes represents a territory(implemented as a Territory class).
//	Edges between nodes represent adjacency between territories.
//	Continents are connected subgraphs.Each territory belongs to oneand only one continent.
//	A territory is owned by a playerand contain a number of armies.
//	The Map class can be used to represent any map graph configuration.
//	The Map class includes a validate() method that makes the following checks : 
//		1) the map is a connected graph, 
//		2) continents are connected subgraphs and 
//		3) each country belongs to oneand only one continent.
//	Driver that creates different Map objectsand checks whether they are valid or not.
//
//////////////////////////////////////////////////////////////////////////////////////////////////////


//#include "Map.h"
//#include "Continent.h"
#include "Territory.h"

int main() {

	Territory can("Canada",0);
	Territory usa("USA", 0);
	Territory mex("Mexico", 0);
	Territory cub("Cuba", 0);
	Territory chi("China", 0);

	usa.show_neighbours();

	std::cout << "add return value = " << usa.connet_to(&can) << std::endl;
	std::cout << "add return value = " << usa.connet_to(&mex) << std::endl;
	std::cout << "add return value = " << usa.connet_to(&cub) << std::endl << std::endl;

	usa.show_neighbours();

	std::cout << "del return value = " << usa.disconnect(&cub) << std::endl << std::endl;

	usa.show_neighbours();
	
	can.~Territory();
	usa.~Territory();
	mex.~Territory();
	cub.~Territory();
	chi.~Territory();

	std::cout << "\nPress any key to close the screen...\n";
	std::cin.get();
	return 0;
}