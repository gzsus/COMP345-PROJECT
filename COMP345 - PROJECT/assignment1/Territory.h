//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//								Territory.h - Adrian Marquez
//
//////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <iostream>


class Territory {

private:
	std::string name;
	int armies;

public:
	Territory();
	Territory(std::string given_name);
	std::string get_name();
	int get_armies();
	void increment_armies(int num_armies);
	void derement_armies(int num_armies);
	void log();
	~Territory();

};
