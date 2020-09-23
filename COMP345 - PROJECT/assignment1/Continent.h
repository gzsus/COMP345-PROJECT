//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//								Continent.cpp - Adrian Marquez
//
//////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once


#include "Territory.h"

class Continent{

private:
	Territory territories;
	std::string continent_name;
	std::string continent_owner;
	// Bonus continent_bonus;

public:
	Continent();
	Continent(std::string given_name);
	std::string get_name();
	std::string get_owner();

	void log();
	~Continent();


};

