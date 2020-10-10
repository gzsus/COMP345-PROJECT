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

	// Pointers to new continents (Name)
	Continent* na = new Continent("NorthAmerica");
	Continent* ca = new Continent("CentralAmerica");
	Continent* as = new Continent("Asia");

	// Pointers to new territories (Name,armies,continent)
	Territory* gua = new Territory("Guatemala", 0, ca);
	Territory* sal = new Territory("ElSalvador", 0, ca);
	Territory* hon = new Territory("Honduras", 0, ca);
	Territory* chi = new Territory("China", 0);

	// Establishing connections between territories (both sides)
	usa->connet_to(can);
	usa->connet_to(mex);
	mex->connet_to(gua);
	gua->connet_to(sal);
	gua->connet_to(hon);
	hon->connet_to(sal);
	//sal->connet_to(hon); // Existing connection adding test

	Territory* nortA[] = {can,usa,mex};	// Array of countries to add to NA
	na->add_territory(nortA,3);

	Map* America = new Map();

	// validate map and show map information
	std::string result = America->validate() ? "true" : "false";
	std::cout << "\n"+America->get_name() + " valid map? " + result + "\n" << std::endl;

	// add continents to map
	America->add_continent(na);
	America->add_continent(ca);

	std::cout << *America << "\n";

	// validate map and show map information
	result = America->validate() ? "true" : "false";
	std::cout << America->get_name() + " valid map? " + result + "\n" << std::endl;


	Territory* nortA2[] = { chi }; // Array of countries to add to NA
	na->add_territory(nortA2,1);
	America->add_continent(na);

	std::cout << *na << "\n";
	std::cout << *America << "\n";

	// validate map and show map information
	result = America->validate() ? "true" : "false";
	std::cout << America->get_name() + " valid map? " + result + "\n" << std::endl;

	//// Show territory information
	//std::cout << *usa << "\n";
	//std::cout << *mex << "\n";
	//std::cout << *gua << "\n";


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