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
#include<iostream>

int main() 
{
	std::string mapfiles[1] = { "C:\\Users\\samue\\Downloads\\comp345\\maps\\canada.map" };

	for (int i = 0; i < 1; i++)
	{
		std::cout << "loop"<<i<<"\n";
		try {
			MapLoader* loader = new MapLoader(mapfiles[i]); //create a pointer that points to the maploader object
			//std::cout << "\n"<<*loader;


			//delete loader; //take care of memory leak
			//loader = NULL;
			std::cout << "all done \n";
			}
		catch (int e)
		{
			std::cout << "error";
		}
	}

}