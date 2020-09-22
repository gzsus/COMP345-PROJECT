//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//								Map.cpp - Adrian Marquez
//
//
//	-The map must be implemented as a connected graph, where each node represents
//		a territory.
//
//	-Edges between nodes represent adjacency between territories.
//
//	-Each territory can have any number of territories.
//
//	-Continents must also be connected subgraphs, where each territory belongs to oneand only
//		one continent.
//
//	-Each territory is owned by a playerand contain a number of armies.
//
//	-The Map class can be used to represent any map configuration.
//
//	-All the classes / functions that you implement for this component must all reside
//		in a single.cpp / .h file duo named Map.cpp / Map.h.
//
//	-You must deliver a file named MapDriver.cpp file that contains a main function that 
//		creates a map and demonstrates that the map class implements the following verifications:
//			1) the map is a connected graph
//			2) continents are connected subgraphs and 
//			3) each country belongs to oneand only one continent.The driver must provide 
//				test cases for various valid / invalid maps.
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////


#include "map.h"

class Map {

	class Continent {

		class Country {
			//	Country definition

			std::string name;
			int armies;
			//Player owner;

			Country() {
				name = "unnamed";
				armies = 0;
			};

			/*Country(const std::string name, int& armies) {
				this.name = name;
				this.armies = 0;
			};*/
		};


		//	Continent Definition

		std::string name;
		int bonus_armies;
		Country countries[];
		// Card bonus_card;
	};


	//	Map definition

	std::string name;
	//Continent continents[];

};
