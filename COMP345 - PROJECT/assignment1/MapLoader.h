//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//								MapLoader.h Samuel Renaud
//
//////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include<string>

class MapLoader
{
	public:
		MapLoader();
		MapLoader(const MapLoader& a); //copy constructor
		MapLoader(std::string mapfile);
		void setfile(std::string newfile); // assignment operator
		std::string getfile();
		void LoadMap();

	private:
		friend std::ostream& operator<<(std::ostream&, const MapLoader&); //stream insertion operator
		std::string file;


};


