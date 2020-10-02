//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//								MapLoader.cpp Samuel Renaud
//
//////////////////////////////////////////////////////////////////////////////////////////////////////


#include "MapLoader.h"
#include "Map.h"
#include <string>
#include <fstream>

std::string file;

MapLoader::MapLoader() {}

MapLoader::MapLoader(const MapLoader& a) {file = a.file;}

MapLoader::MapLoader(std::string mapfile)
{
	file = mapfile;
	std::ifstream input(mapfile);
	while (!input.eof())
	{
		
	}

	input.close();
}

void MapLoader::setfile(std::string newfile) {file = newfile;}

std::string MapLoader::getfile(){return file;}

std::ostream& operator<<(std::ostream &ostrm, const MapLoader &maploader)
{	return ostrm << "Maploader Loading: (" << maploader.file << ")"; }


