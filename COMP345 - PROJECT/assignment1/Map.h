//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//								Map.h - Adrian Marquez
//
//////////////////////////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "Continent.h"

class Map {

private:
	std::string name;
	std::vector<Territory*> territories;
	std::vector<Continent*> continents;
	static int num_territories;

public:
	Map();
	Map(std::string given_name);
	Map(const Map& t);
	~Map();


	int index_continent(Continent* given_continent);
	bool add_continent(Continent* given_continent);
	bool remove_continent(Continent* given_continent);

	std::string get_name();
	void set_name(std::string given_name);
	std::vector<Territory*> get_territories();
	void set_territories(std::vector<Territory*> neighbours);
	std::vector<Continent*> get_continents();
	void set_continents(std::vector<Continent*> neighbours);

	bool validate(Map* given_map);

	friend std::ostream& operator<<(std::ostream&, const Map& given_map);
	
};