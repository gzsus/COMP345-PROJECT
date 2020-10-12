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
//	-Each Territory can have any number of territories.
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


#include "Map.h"
#include "Continent.h"
#include "Territory.h"


using namespace std;


/////////////////////////////////// Constructors/Destructor /////////////////////////////////////
Map::Map()
{
	name = "";
	cout << "[CREATED]  " << *this;
}
Map::Map(std::string given_name)
{
	name = given_name;
	cout << "[CREATED]  " << *this;
}
Map::Map(const Map& t)
{
	name = t.name;
	continents = t.continents;
	territories = t.territories;
	cout << "[CREATED]  " << *this;
}
Map::~Map()
{
	for (Territory* t : territories)
		delete t;
	for (Continent* c : continents)
		delete c;
}




/////////////////////////////////// Sets and gets /////////////////////////////////////
std::string Map::get_name() { return name; }
void Map::set_name(std::string given_name) { name = given_name; }

std::vector<Territory*> Map::get_territories() { return territories; }
void Map::set_territories(std::vector<Territory*> given_territories) { territories = given_territories; }

std::vector<Continent*> Map::get_continents() { return continents; }
void Map::set_continents(std::vector<Continent*> given_continents) { continents = given_continents; }



/////////////////////////////////// Continent manipulation /////////////////////////////////////
/////////////////// Index of a continent in the map
int Map::index_continent(Continent* given_continent)
{
	if (continents.empty())
		return -1;

	for (unsigned int i = 0; i < continents.size(); i++)
		if (continents[i] == given_continent)
			//	Return index of found element
			return i;	// [0,length) = (true)

	// If not found:
	return -1;	// = false
}
/////////////////// Add continent to the map and it's territories
bool Map::add_continent(Continent* given_continent)
{
	//	If it is not already set
	if ((this->index_continent(given_continent) == -1)) {
		// Map pointer is pointed to container map
		given_continent->set_map(this);
		// Add on this vector 
		this->continents.push_back(given_continent);
		for (Territory* t : given_continent->get_territories())
			territories.push_back(t);
		return true;
	}
	else {
		for (Territory* t : given_continent->get_territories()) {
			if (this->index_territory(t) == -1) {
				territories.push_back(t);
				return true;
			}
		}
	}
	return false;
}
bool Map::remove_continent(Continent* given_continent)
{
	int index = (this->index_continent(given_continent));
	if (index >= 0) {
		// remove from continent vector
		continents.erase(remove(continents.begin(), continents.end(), given_continent), continents.end());
		return true;
	}
	return false;
}


/////////////////////////////////// Territory manipulation /////////////////////////////////////
int Map::index_territory(Territory* given_territory)
{
	if (territories.empty())
		return -1;

	for (unsigned int i = 0; i < territories.size(); i++)
		if (territories[i] == given_territory)
			//	Return index of found element
			return i;	// [0,length) = (true)

	// If not found:
	return -1;	// = false
}

bool Map::add_territory(Territory* given_territory)
{
	//	If it is not already set
	if ((this->index_territory(given_territory) == -1)) {
		// Add on this vector 
		this->territories.push_back(given_territory);
		return true;
	}
	return false;
}


/////////////////////////////////// Other methods /////////////////////////////////////

/////////////////// Stream insertion operator
ostream& operator<<(ostream& ostream, const Map& given_map) 
{
	string continent_output = "\n\tContinents:";
	for (Continent* c : given_map.continents)
		continent_output.append( "  " + c->get_name() );
	if (continent_output == "\n\tContinents:")
		continent_output = "";

	string territory_output = "\n\tTerritories: ";
	for (Territory* t : given_map.territories)
		territory_output.append( "  " + t->get_name() );
	if (territory_output == "\n\tTerritories: ")
		territory_output = "";

	string output;

	if (continent_output == "" && territory_output == "")
		output = "Empty map";
	else
		output = continent_output + territory_output;

	return ostream << "[Map] " << given_map.name+" " << output << std::endl;
}

/////////////////// Map update
//bool Map::update()
//{
//	bool change_flag = false;
//	for (Continent* c : continents) {
//		for(Territory* t : c->get_territories())
//			if (this->index_territory(t) == -1) {
//				territories.push_back(t);
//				change_flag = true;
//			}
//	}
//	for (Territory* t : territories) {
//		if (this->index_continent(t->get_continent()) == -1) {
//			continents.push_back(t->get_continent());
//			change_flag = true;
//		}
//	}
//	return change_flag;
//}

/////////////////// Map validator
bool Map::validate()
{
	// Check you have at least 1 continent and at least 2 territories
	if (territories.size() < 2 || continents.size() < 1)
		return false;
	for (Territory* t : territories) {
		// Check all territories are connected to at least 1 territory
		if (t->get_neighbours().size() < 1)
			return false;
		// Check all territories are assigned to 1 continent
		if (t->get_continent() == NULL)
			return false;
	}

	// Check all continents are connected to at least 1 continent
	for (Continent* c : continents)
		if (!(c->is_connected()))
			return false;
	return true;
}