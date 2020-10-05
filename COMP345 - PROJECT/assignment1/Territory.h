//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//								Territory.h - Adrian Marquez
//
//////////////////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <iterator>

/////////////////// Necessary classes
class Player;
class Continent;

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


	/////////////////////////////////// Armies manipulation /////////////////////////////////////
	void increment_armies(int num_armies);
	void decrement_armies(int num_armies);


	/////////////////////////////////// Neighbours manipulation /////////////////////////////////////
	bool has_neighbour(Territory* given_territory);
	int index_neighbour(Territory* given_territory);
	bool connet_to(Territory* given_territory);
	bool disconnect(Territory* given_t);


	///////////////////////////////////	Other methods /////////////////////////////////////
	void show_neighbours();
	//void copy();
	void log();

};
