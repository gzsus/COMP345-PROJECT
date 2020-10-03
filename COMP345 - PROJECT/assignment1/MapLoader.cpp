//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//								MapLoader.cpp Samuel Renaud
//
//////////////////////////////////////////////////////////////////////////////////////////////////////


#include "MapLoader.h"
#include "Map.h"
#include <string>
#include <fstream>
#include <iostream>

std::string file;
//empty constructor
MapLoader::MapLoader()
{
	file = "";
}
//copy constructor
MapLoader::MapLoader(const MapLoader& a) {file = a.file;}
//constructor that takes in a file string and creates a map right away
MapLoader::MapLoader(std::string mapfile)
{
	file = mapfile;
	std::ifstream input(mapfile);
	while (!input.eof())
	{
		std::string temp;
		getline(input, temp);
		std::cout << temp;
	}

	input.close();
}
// maploader for non directly constructed maploader object
 void MapLoader::LoadMap()
{
	 if(file=="")
	 {
		 std::cout<< "No file to load";
	 }
	 else
	 {
		 std::ifstream input(file);
		 while (!input.eof())
		 {

		 }

		 input.close();
	 }
}

//set the file for the maploader object
void MapLoader::setfile(std::string newfile) {file = newfile;}
//get the file for this object
std::string MapLoader::getfile(){return file;}
//tostring overload
std::ostream& operator<<(std::ostream &ostrm, const MapLoader &maploader)
{	return ostrm << "Maploader Loading: (" << maploader.file << ")"; }


