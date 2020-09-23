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


#include "Map.h"
#include "Continent.h"
#include "Territory.h"


void main() {

	Territory t0;
	Territory t1;
	Territory t2("Canada");
	Territory t3("US");
	Territory t4("Mexico");
	Territory t5("China");

	Territory m1[] = { t0,t1,t2,t3,t4,t5 };
	

	std::cout << "\n\nPress any key to close the screen..." << std::endl;
	std::cin.get();

}