//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//								MapLoaderDriver.cpp Samuel Renaud
//
//
//
//	Read maps from multiple .map files and use map class to build them if possible.
//	Read all maps and only create properly formatted or correct ones.
//
//////////////////////////////////////////////////////////////////////////////////////////////////////


#include "MapLoader.h"
#include <string>
#include <fstream>

int main() 
{
	std::string mapfiles[5] = { "a.map","b.map", "c.map", "d.map", "e.map" };


	for (int i = 0; i < 5; i++)
	{
		try {
			std::ifstream input(mapfiles[i]);
			MapLoader* loader = new MapLoader(mapfiles[i]); //create a pointer that points to the maploader object


			delete(loader); //take care of memory leak
			loader = NULL;
			}
		catch (int e)
		{

		}
	}

}