//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//									Map.h - Adrian Marquez
//
//////////////////////////////////////////////////////////////////////////////////////////////////////


#pragma once
#include <string>
#include <vector>
#include <iostream>


/////////////////// Necessary classes
class Territory;
class Continent;
class Player;
class Bonus;
class Map;

class Map
{
private:
	/////////////////////////////////// Member atributes /////////////////////////////////////
	std::string name;
	std::vector<Territory*> territories;
	std::vector<Continent*> continents;
	static int num_territories;
public:
	/////////////////////////////////// Constructors/Destructor /////////////////////////////////////
	Map();
	Map(std::string given_name);
	Map(const Map& t);
	~Map();

	/////////////////////////////////// Manipulation /////////////////////////////////////
	int index_continent(Continent* given_continent);
	bool add_continent(Continent* given_continent);
	bool remove_continent(Continent* given_continent);
	int index_territory(Territory* given_territory);
	bool add_territory(Territory* given_territory);

	/////////////////////////////////// Sets and gets /////////////////////////////////////
	std::string get_name();
	void set_name(std::string given_name);
	std::vector<Territory*> get_territories();
	std::vector<Territory*> get_territories(Player* p);
	std::vector<Territory*> get_neighbour_territories(Player* p);
	void set_territories(std::vector<Territory*> neighbours);
	std::vector<Continent*> get_continents();
	void set_continents(std::vector<Continent*> neighbours);
	bool validate();
	friend std::ostream& operator<<(std::ostream&, const Map& given_map);
};



//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//											Continent
//
// Continents are subgraphs of the map containing territories.
//////////////////////////////////////////////////////////////////////////////////////////////////////
class Continent
{
private:
	/////////////////////////////////// Member atributes /////////////////////////////////////
	std::vector<Territory*> territories;
	std::string continent_name;
	Player* owner;
	Bonus* bonus;
	Map* container;
public:
	/////////////////////////////////// Constructors/Destructor /////////////////////////////////////
	Continent();
	Continent(std::string given_name);
	Continent(std::string given_name, Bonus* given_bonus);
	Continent(const Continent& given_continent);
	~Continent();

	/////////////////////////////////// Sets and gets /////////////////////////////////////
	void set_territories(std::vector<Territory*> given_vector);
	std::vector<Territory*> get_territories();
	void set_name(std::string given_name);
	std::string get_name();
	void set_owner(Player* given_owner);
	Player* get_owner();
	void set_bonus(Bonus* given_bonus);
	Bonus* get_bonus();
	void set_map(Map* given_map);
	Map* get_map();

	/////////////////////////////////// Territories manipulation /////////////////////////////////////
	int index_territory(Territory* given_territory);
	bool add_territory(Territory* given_territory);
	void add_territory(Territory* given_territories[], int arr_size);
	bool remove_territory(Territory* given_territory);
	bool is_connected();

	/////////////////////////////////// Other methods /////////////////////////////////////
	friend std::ostream& operator<<(std::ostream&, const Continent&);
	void operator=(Continent* c);
};



//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//											Territory
//
//	Territories are the basic units of the Map.
//	They have a name, a container continent, armies occupying it and a list of neighbour territories.
//
//////////////////////////////////////////////////////////////////////////////////////////////////////

class Territory
{
private:
	/////////////////////////////////// Member atributes /////////////////////////////////////
	std::string territory_name;
	std::vector<Territory*> neighbours;
	Continent* continent;
	Player* owner;
	int armies;
public:
	/////////////////////////////////// Constructors/Destructors /////////////////////////////////////
	Territory();
	Territory(std::string given_name, int num_armies);
	Territory(std::string given_name, int num_armies, Continent* continent);
	Territory(const Territory& t);
	~Territory();

	///////////////////////////////////	Sets and Gets /////////////////////////////////////
	std::string get_name();
	void set_name(std::string given_name);
	std::vector<Territory*> get_neighbours();
	void set_neighbours(std::vector<Territory*> neighbours);
	Continent* get_continent();
	void set_continent(Continent* continent);
	Player* get_owner();
	void set_owner(Player* new_owner);
	int get_armies();
	void set_armies(int given_armies);

	/////////////////////////////////// Manipulation /////////////////////////////////////
	void increment_armies(int num_armies);
	void decrement_armies(int num_armies);
	int index_neighbour(Territory* given_territory);
	bool connet_to(Territory* given_territory);
	bool disconnect(Territory* given_t);
	void disconnect_all();

	///////////////////////////////////	Other methods /////////////////////////////////////
	void show_neighbours();
	friend std::ostream& operator<<(std::ostream&, const Territory&);
	void operator=(Territory* t);
};