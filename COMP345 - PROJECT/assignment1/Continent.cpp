//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//								Continent.cpp - Adrian Marquez
//
//////////////////////////////////////////////////////////////////////////////////////////////////////


#include "Continent.h"
#include "Territory.h"
#include "Map.h"


using namespace std;


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
	bonus = NULL;
	owner = NULL;
	//container = NULL;
	continent_name.clear();
	for (Territory* t : territories)
		t->set_continent(NULL);
	territories.clear();
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
	if ( !(this->index_territory(given_territory) > -1 )) {
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
		if ( !(this->index_territory(given_territories[i]) > -1 )) {
			// Add on this vector 
			this->territories.push_back(given_territories[i]);
			// Add pointer to this continent in the territory given
			given_territories[i]->set_continent(this);
		}
		else {
			cout << "[info] "+ given_territories[i]->get_name()+" already in this continent." << endl;
		}
	}
}
bool Continent::remove_territory(Territory* given_territory)
{
	int index = (this->index_territory(given_territory));
	if ( index >= 0 ) {
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
			if ( neighbour_t->get_continent() != this || neighbour_t->get_continent() != NULL )	// if neighbour territory is not part of this conntinent
				return true;	// this continent is connected to other continent
	return false;
}



/////////////////////////////////// Other methods /////////////////////////////////////

/////////////////// Stream insertion operator
ostream& operator<<(ostream& ostream, const Continent& given_continent)
{
	string territ = "\n\tTerritories: ";

	for ( Territory* t : given_continent.territories)
		territ.append("  "+t->get_name());

	if (territ == "\n\tTerritories: ")
		territ = ", 0 territories";

	return ostream << "[Continent] " << given_continent.continent_name << territ << endl ;
}

/////////////////// Assignment operator
void Continent::operator=(Continent* c)
{
	territories = c->territories;
	continent_name = c->continent_name;
	owner = c->owner;
	bonus = c->bonus;
}