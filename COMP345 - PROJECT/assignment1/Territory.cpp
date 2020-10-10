//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//								Territory.cpp - Adrian Marquez
//
//	Territories are the basic units of the Map.
//	They have a name, a container continent, armies occupying it and a list of neighbour territories.
//
//////////////////////////////////////////////////////////////////////////////////////////////////////


#include "Territory.h"
#include "Continent.h"


using namespace std;

/////////////////// Necessary classes
class Player;
class Bonus;



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
	owner = NULL;
	continent = NULL;
	territory_name.erase();
	for (Territory* n : neighbours)
		delete n;
	neighbours.clear();
};



///////////////////////////////////	Sets and Gets /////////////////////////////////////

string Territory::get_name() { return territory_name; };
void Territory::set_name(string given_name) { territory_name = given_name ; };

std::vector<Territory*> Territory::get_neighbours() {return neighbours;};
void Territory::set_neighbours(std::vector<Territory*> neighbours) { neighbours = neighbours; };

Continent* Territory::get_continent() { return this->continent; };
void Territory::set_continent(Continent* continent) { this->continent = continent;  };

Player* Territory::get_owner() { return this->owner; };
void Territory::set_owner(Player* new_owner) { this->owner = new_owner;  };

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
	
	cout << "[info] This connection already exists  " << territory_name+" - "+ given_territory->territory_name << endl;
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
	if ( index >= 0 ) {
		//	Delete on this vector
		neighbours.erase(remove(neighbours.begin(), neighbours.end(), given_t), neighbours.end());
		//	Should also delete on other end
		given_t->neighbours.erase(remove(given_t->neighbours.begin(),given_t->neighbours.end(), this), given_t->neighbours.end());
		// After deletion on both ends
		return true;
	}
	// If not found
	return false;
}
void Territory::disconnect_all()
{
}
;

/////////////////// Disconnect all neighbours
// Remove neighbour territory from neighbours vector
//void Territory::disconnect_all()
//{
//	// loop through neighbours
//	for (Territory* t : neighbours ) {
//		//	Delete on other end
//		t->neighbours.erase(remove(t->neighbours.begin(),t->neighbours.end(), this), t->neighbours.end());
//		//	Delete on this vector
//		neighbours.erase(remove(neighbours.begin(), neighbours.end(), t), neighbours.end());
//	}
//}



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
		cont = "belongs to " + given_territory.continent->get_name()+", ";

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