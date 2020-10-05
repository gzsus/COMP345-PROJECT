//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//								Continent.cpp - Adrian Marquez
//
//////////////////////////////////////////////////////////////////////////////////////////////////////


#include "Continent.h"


/////////////////////////////////// Constructors/Destructor /////////////////////////////////////

Continent::Continent()
{
	continent_name = "unnamed";
	owner = NULL;
	bonus = NULL;
	//std::cout << "Continent created: " << std::endl;
	//this->log();
}

Continent::Continent(std::string given_name)
{
	continent_name = given_name;
	owner = NULL;
	bonus = NULL;
	//std::cout << "Continent created: " << std::endl;
	//this->log();
}

Continent::Continent(std::string given_name, Bonus* given_bonus)
{
	continent_name = given_name;
	bonus = given_bonus;
	//std::cout << "Continent created: " << std::endl;
	//this->log();
}

Continent::~Continent()
{
	territories.clear();
	delete bonus;
	delete owner;
}


/////////////////////////////////// Sets and gets /////////////////////////////////////

void Continent::set_name(std::string given_name) { continent_name = given_name; }
std::string Continent::get_name() { return continent_name; }

void Continent::set_owner(Player* given_owner) { owner = given_owner; }
Player* Continent::get_owner() { return owner; }

void Continent::set_bonus(Bonus* given_bonus) {  }
Bonus* Continent::get_bonus() { return bonus; }


/////////////////////////////////// Territories manipulation /////////////////////////////////////

int Continent::has_territory(Territory* given_territory)
{
	if (territories.empty())
		return -1;
	std::vector<Territory*>::iterator cont = territories.begin();
	// Iterate through vector of Territory pointers until found given_territory or end
	std::find(territories.begin(), territories.end(), given_territory);

	if (cont != end(territories)) {
		// Return index of iterator
		return cont - territories.begin();
	}
	// If not found:
	return -1;
}
bool Continent::add_territory(Territory* given_territory)
{
	//	If it is not already set
	if (!(this->has_territory(given_territory)) + 1) {
		// Add on this vector 
		this->territories.push_back(given_territory);
		// Add pointer to this continent in the territory given
		given_territory->set_continent(this);
		return true;
	}
	return false;
}
bool Continent::remove_territory(Territory* given_territory)
{
	if ((this->has_territory(given_territory)) + 1) {
		// Disconnect from all the neighbours
		// Delete from the list of territories in continent
		// Call destructor on territory
		return true;
	}
	return false;
}


/////////////////////////////////// Other methods /////////////////////////////////////

