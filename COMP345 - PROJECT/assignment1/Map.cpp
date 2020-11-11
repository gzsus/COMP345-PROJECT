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
		t = NULL;
	for (Continent* c : continents) {
		delete c;
		c = NULL;
	}
}




/////////////////////////////////// Sets and gets /////////////////////////////////////
std::string Map::get_name() { return name; }
void Map::set_name(std::string given_name) { name = given_name; }
std::vector<Territory*> Map::get_territories() { return territories; }
std::vector<Territory*> Map::get_territories(Player* p) {
	vector <Territory*> owned_terrritories;
	for (Territory* t : territories)
		if (p == t->get_owner())
			owned_terrritories.push_back(t);
	return owned_terrritories;
}
std::vector<Territory*> Map::get_neighbour_territories(Player* p) {
	vector<Territory*>owned_terrritories = get_territories(p);
	vector<Territory*> neighbouring_terrritories;
	// Get neighbour territories ( territories to attack )
	for (Territory* owned : owned_terrritories) {
		vector<Territory*> tNeighbours = owned->get_neighbours();
		for (Territory* neighbour : tNeighbours) {
			if (!(std::find(neighbouring_terrritories.begin(), neighbouring_terrritories.end(), neighbour) != neighbouring_terrritories.end()))
				if (neighbour->get_owner() != p)
					neighbouring_terrritories.push_back(neighbour);
				else continue;
		}
	}
	return neighbouring_terrritories;
}
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
		continent_output.append("  " + c->get_name());
	if (continent_output == "\n\tContinents:")
		continent_output = "";

	string territory_output = "\n\tTerritories: ";
	for (Territory* t : given_map.territories)
		territory_output.append("  " + t->get_name());
	if (territory_output == "\n\tTerritories: ")
		territory_output = "";

	string output;

	if (continent_output == "" && territory_output == "")
		output = "Empty map";
	else
		output = continent_output + territory_output;

	return ostream << "[Map] " << given_map.name + " " << output << std::endl;
}

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


//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//								Continent.cpp - Adrian Marquez
//
// Continents are subgraphs of the map containing territories.
//////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////// Constructors/Destructor /////////////////////////////////////
Continent::Continent()
{
	continent_name = "unnamed";
	owner = NULL;
	bonus = NULL;
	container = NULL;
	cout << "[CREATED]  " << *this;
}
Continent::Continent(string given_name)
{
	continent_name = given_name;
	owner = NULL;
	bonus = NULL;
	container = NULL;
	cout << "[CREATED]  " << *this;
}
Continent::Continent(string given_name, Bonus* given_bonus)
{
	continent_name = given_name;
	bonus = given_bonus;
	bonus = NULL;
	container = NULL;
	cout << "[CREATED]  " << *this;
}
Continent::Continent(const Continent& given_continent)
{
	continent_name = given_continent.continent_name;
	territories = given_continent.territories;
	owner = given_continent.owner;
	bonus = given_continent.bonus;
	container = given_continent.container;
	cout << "[COPIED]  " << *this;
}
Continent::~Continent()
{
	for (Territory* t : territories) {
		delete t;
		t = NULL;
	}
	bonus = NULL;
	owner = NULL;
	container = NULL;
}



/////////////////////////////////// Sets and gets /////////////////////////////////////
void Continent::set_territories(std::vector<Territory*> given_vector) { territories = given_vector; }
std::vector<Territory*> Continent::get_territories() { return territories; }
void Continent::set_name(string given_name) { continent_name = given_name; }
string Continent::get_name() { return continent_name; }
void Continent::set_owner(Player* given_owner) { owner = given_owner; }
Player* Continent::get_owner() { return owner; }
void Continent::set_bonus(Bonus* given_bonus) { bonus = given_bonus; }
Bonus* Continent::get_bonus() { return bonus; }
void Continent::set_map(Map* given_map) { container = given_map; }
Map* Continent::get_map() { return container; }



/////////////////////////////////// Territories manipulation /////////////////////////////////////

int Continent::index_territory(Territory* given_territory)
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
bool Continent::add_territory(Territory* given_territory)
{
	//	If it is not already set
	if (!(this->index_territory(given_territory) > -1)) {
		// Add on this vector 
		this->territories.push_back(given_territory);
		// Add pointer to this continent in the territory given
		given_territory->set_continent(this);
		return true;
	}
	return false;
}
void Continent::add_territory(Territory* given_territories[], int arr_size)
{
	for (int i = 0; i < arr_size; i++) {
		//	If it is not already set
		if (!(this->index_territory(given_territories[i]) > -1)) {
			// Add on this vector 
			this->territories.push_back(given_territories[i]);
			// Add pointer to this continent in the territory given
			given_territories[i]->set_continent(this);
		}
		else {
			cout << "[info] " + given_territories[i]->get_name() + " already in this continent." << endl;
		}
	}
}
bool Continent::remove_territory(Territory* given_territory)
{
	int index = (this->index_territory(given_territory));
	if (index >= 0) {
		// remove from continent vector
		territories.erase(remove(territories.begin(), territories.end(), given_territory), territories.end());
		return true;
	}
	return false;
}
bool Continent::is_connected()
{
	for (Territory* contained_t : this->territories)	// territories in this continent
		for (Territory* neighbour_t : contained_t->get_neighbours()) // neighbour territories to each of the contained territories
			if (neighbour_t->get_continent() != this || neighbour_t->get_continent() != NULL)	// if neighbour territory is not part of this conntinent
				return true;	// this continent is connected to other continent
	return false;
}



/////////////////////////////////// Other methods /////////////////////////////////////

/////////////////// Stream insertion operator
ostream& operator<<(ostream& ostream, const Continent& given_continent)
{
	string territ = "\n\tTerritories: ";

	for (Territory* t : given_continent.territories)
		territ.append("  " + t->get_name());

	if (territ == "\n\tTerritories: ")
		territ = ", 0 territories";

	return ostream << "[Continent] " << given_continent.continent_name << territ << endl;
}

/////////////////// Assignment operator
void Continent::operator=(Continent* c)
{
	territories = c->territories;
	continent_name = c->continent_name;
	owner = c->owner;
	bonus = c->bonus;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//											Territory
//
//	Territories are the basic units of the Map.
//	They have a name, a container continent, armies occupying it and a list of neighbour territories.
//
//////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////	Constructors/Destructors /////////////////////////////////////

///////////////////	Empty constructor
Territory::Territory()
{
	territory_name = "unnamed";
	continent = NULL;
	owner = NULL;
	armies = 0;
	cout << "[CREATED] " << *this;
};

/////////////////// Overloaded constructor
Territory::Territory(string given_name, int num_armies)
{
	territory_name = given_name;
	continent = NULL;
	owner = NULL;
	armies = num_armies;
	cout << "[CREATED]  " << *this;
};

/////////////////// Another overloaded constructor
Territory::Territory(string given_name, int num_armies, Continent* given_continent)
{
	territory_name = given_name;
	continent = given_continent;
	given_continent->add_territory(this);
	owner = NULL;
	armies = num_armies;
	cout << "[CREATED]  " << *this;
}

/////////////////// Copy constructor
Territory::Territory(const Territory& t)
{
	territory_name = t.territory_name;
	neighbours = t.neighbours;
	/*for (Territory* t : t.neighbours)
		neighbours.push_back(t);*/
	continent = t.continent;
	owner = t.owner;
	armies = t.armies;
	cout << "[COPIED] " << *this;
}
;

/////////////////// Destructor
Territory::~Territory()
{
	for (Territory* t : neighbours) {
		t = NULL;
	}
	continent = NULL;
	owner = NULL;
};



///////////////////////////////////	Sets and Gets /////////////////////////////////////

string Territory::get_name() { return territory_name; };
void Territory::set_name(string given_name) { territory_name = given_name; };
std::vector<Territory*> Territory::get_neighbours() { return neighbours; };
void Territory::set_neighbours(std::vector<Territory*> neighbours) { neighbours = neighbours; };
Continent* Territory::get_continent() { return this->continent; };
void Territory::set_continent(Continent* continent) { this->continent = continent; };
Player* Territory::get_owner() { return this->owner; };
void Territory::set_owner(Player* new_owner) { this->owner = new_owner; };
int Territory::get_armies() { return armies; };
void Territory::set_armies(int given_armies) { armies = given_armies; };



///////////////////////////////////	Armies Manipulation /////////////////////////////////////
/////////////////// Number of armies increment
void Territory::increment_armies(int num_armies) { armies += num_armies; };

/////////////////// Number of armies decrement
void Territory::decrement_armies(int num_armies)
{
	if (armies - num_armies >= 0)
		armies -= num_armies;
	else armies = 0;
};


///////////////////////////////////	Neighbours Manipulation /////////////////////////////////////

/////////////////// Index of neighbour
//	Find index of neighbour if it's in the neighbours vector else -1
int Territory::index_neighbour(Territory* given_territory)
{
	// Return false if vector is empty
	if (neighbours.empty())
		return -1;

	for (unsigned int i = 0; i < neighbours.size(); i++)
		if (neighbours[i] == given_territory)
			//	Return index of found element
			return i;	// [0,length) = (true)

	// If not found:
	return -1;	// = false
};

/////////////////// Connet neighbours
//	Connect neighbour territories by adding the pointers to each respective neighbours vector
bool Territory::connet_to(Territory* given_territory)
{
	// Check if it is already connected
	if (this->index_neighbour(given_territory) == -1) {
		//	Add on both sides the connection if its not already in it
		neighbours.push_back(given_territory);
		given_territory->neighbours.push_back(this);
		return true;
	}

	cout << "[info] This connection already exists  " << territory_name + " - " + given_territory->territory_name << endl;
	return false;
};

/////////////////// Delete a neighbour
// Remove neighbour territory from neighbours vector
bool Territory::disconnect(Territory* given_t)
{
	// Return false if vector is empty
	if (neighbours.empty())
		return false;
	// Search on vector the given territory
	int index = this->index_neighbour(given_t);
	// If found
	if (index >= 0) {
		//	Delete on this vector
		neighbours.erase(remove(neighbours.begin(), neighbours.end(), given_t), neighbours.end());
		//	Should also delete on other end
		given_t->neighbours.erase(remove(given_t->neighbours.begin(), given_t->neighbours.end(), this), given_t->neighbours.end());
		// After deletion on both ends
		return true;
	}
	// If not found
	return false;
}

///////////////////////////////////	Other methods /////////////////////////////////////

/////////////////// Get information of neighbour territories
void Territory::show_neighbours() {
	if (neighbours.empty())
		cout << "This Territory has no neighbours";
	else
		for (Territory* t : neighbours)
			cout << t->get_name() << ", ";

	cout << "\n\n";
	return;
}

/////////////////// Stream insertion operator
std::ostream& operator<<(std::ostream& ostream, const Territory& given_territory)
{
	string cont = " belongs to NULL, ";
	if (given_territory.continent != NULL)
		cont = "belongs to " + given_territory.continent->get_name() + ", ";

	string neighb = "\n\tNeighbours: ";
	for (Territory* t : given_territory.neighbours)
		neighb.append("  " + t->get_name());

	if (neighb == "\n\tNeighbours: ")
		neighb = "0 neighbours";

	return ostream << "[Territory] " + given_territory.territory_name + ", " << given_territory.armies << " Armies, " + cont + neighb << std::endl;
}


/////////////////// Assignment operator
void Territory::operator=(Territory* t) {
	neighbours = t->neighbours;
	territory_name = t->get_name();
	continent = t->continent;
	owner = t->owner;
	armies = t->armies;
}