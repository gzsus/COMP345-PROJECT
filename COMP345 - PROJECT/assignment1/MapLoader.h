//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//								MapLoader.h Samuel Renaud
//
//////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include<string>
#include<vector>
#include "Map.h"

class MapLoader
{

	public:
		MapLoader();
		MapLoader(const MapLoader& a); //copy constructor
		MapLoader(std::string mapfile);
		//fix this
		MapLoader& operator =(const MapLoader& oldloader);// assignment operator
		void setfile(std::string newfile); 
		std::string getfile();
		Map LoadMap(std::vector<std::vector<std::string>>continents, std::vector<std::vector<std::string>> territories, std::vector<std::vector<std::string>>borders);
		
		~MapLoader();

	private:
		Map* created_map; //this will store the map objects once they are created
		friend std::ostream& operator<<(std::ostream&, const MapLoader&); //stream insertion operator
		std::string file;
		//lists used to store informaion taken from .map files
		std::vector<std::vector<std::string>> continent_list;
		std::vector<std::vector<std::string>> country_list;
		std::vector<std::vector<std::string>> border_list;


};

