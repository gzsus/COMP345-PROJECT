//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//								MapLoader.h Samuel Renaud
//
//////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include<string>
#include<vector>

class MapLoader
{

	public:
		MapLoader();
		MapLoader(const MapLoader& a); //copy constructor
		MapLoader(std::string mapfile);
		//fix this
		MapLoader& operator =(const MapLoader& oldloader);
		void setfile(std::string newfile); // assignment operator
		std::string getfile();
		void LoadMap();

	private:
		friend std::ostream& operator<<(std::ostream&, const MapLoader&); //stream insertion operator
		std::string file;
		//lists used to store informaion taken from .map files
		std::vector<std::vector<std::string>> continent_list;
		std::vector<std::vector<std::string>> country_list;
		std::vector<std::vector<std::string>> border_list;


};

