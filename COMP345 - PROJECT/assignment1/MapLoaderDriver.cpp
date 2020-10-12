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
	std::string mapfiles[3] = { "C:\\Users\\samue\\Downloads\\comp345\\maps\\canada.map","C:\\Users\\samue\\Downloads\\comp345\\maps\\artic_bad.map","C:\\Users\\samue\\Downloads\\comp345\\maps\\europe.map" };
	MapLoader* loader[3];

	for (int i = 0; i < 3; i++)
	{
		std::cout << "loop"<<i<<"\n";
		try {
			loader[i] = new MapLoader(mapfiles[i]); //create a pointer that points to the maploader object

			//delete loader; //take care of memory leak
			//loader = NULL;
			std::cout << "\nEnd of Program \n\n";
			}
		catch (int e)
		{
			std::cout << "I/O error";
		}
	}

}