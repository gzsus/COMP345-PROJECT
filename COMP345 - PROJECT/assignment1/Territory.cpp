//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//								Territory.cpp - Adrian Marquez
//
//////////////////////////////////////////////////////////////////////////////////////////////////////


#include "Territory.h"


//	Empty constructor
Territory::Territory() {
	name = "unnamed";
	armies = 0;
	std::cout << "Territory created: " << name << std::endl;
};

//	Overloaded constructor
Territory::Territory(std::string given_name) {
	name = given_name;
	armies = 2;
	std::cout << "Territory created: " << name << std::endl;
};


//	Sets and Gets
std::string Territory::get_name() { return name; };

int Territory::get_armies() { return armies; };


//	Other methods

//	Number of armies increment
void Territory::increment_armies(int num_armies) { armies += num_armies; };
//	Number of armies decrement
void Territory::derement_armies(int num_armies) {
	if (armies - num_armies >= 0)
		armies -= num_armies;
	else armies = 0;
};

//	Show information of this Territory
void Territory::log() {
	std::cout << name << ": " << armies << std::endl;
};

//	Destructor
Territory::~Territory() = default;
