//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//								Map.h - Adrian Marquez
//
//////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
#include <iostream>


//	Declaration of the Map
class map {


	//	A map has several Continents
	class Continents {
		//	Continents are sections of the maps and they are composed of different countries
		//	Continents have a name, list of countries in it, adjacent countries


		//	A map has multiple Countries inside each map
		class Country {
			//	A country acts as a node (Vertex) in a graph data structure.
			//	Countries must have a name, owner and number of armies in it.
			std::string name;
			int armies;
		};

	};

};