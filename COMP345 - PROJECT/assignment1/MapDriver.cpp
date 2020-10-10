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

int main()
{
	// Pointers to new territories (Name,armies)
	Territory* can = new Territory("Canada",0);
	Territory* usa = new Territory("USA", 0);
	Territory* mex = new Territory("Mexico", 0);

	Continent* na = new Continent("NorthAmerica");
	Continent* ca = new Continent("CentralAmerica");

	Territory* gua = new Territory("Guatemala", 0);
	Territory* sal = new Territory("ElSalvador", 0);
	Territory* hon = new Territory("Honduras", 0);

	usa->connet_to(can);
	usa->connet_to(mex);
	mex->connet_to(gua);
	gua->connet_to(sal);
	gua->connet_to(hon);

	Territory* nortA[] = {can,usa,mex};
	Territory* centA[] = {gua,sal,hon};


	na->add_territory(nortA,3);
	ca->add_territory(centA,3);

	Map* America = new Map("America");

	America->add_continent(na);
	America->add_continent(ca);

	std::cout << "\n" << *America;


	std::cout << *usa << "\n";
	std::cout << *mex << "\n";
	std::cout << *gua << "\n";

	//Territory* chi = new Territory(*usa); // Copy constructor use
	//Territory* chi = new Territory();
	//*chi = *usa;							// Assignment Operator use
	//chi->set_name("Japan");
	//std::cout << *usa << std::endl;
	//std::cout << *chi;


	std::cout << "\nPress any key to close the screen...\n";
	std::cin.get();
	return 0;
}