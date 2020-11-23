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

		MapLoader& operator =(const MapLoader& oldloader);// assignment operator
		void setfile(std::string newfile); 
		void setmap(Map* new_map){this->created_map = new_map;}
		Map* getmap() { return this->created_map; }
		std::string getfile();

		virtual void FileReader(std::string mapfile);
		Map LoadMap(std::vector<std::vector<std::string>>continents, std::vector<std::vector<std::string>> territories, std::vector<std::vector<std::string>>borders);
		~MapLoader();

	private:
		Map* created_map; //this will store the map objects once they are created
		std::string file;

		//lists used to store informaion taken from .map files
		std::vector<std::vector<std::string>> continent_list;
		std::vector<std::vector<std::string>> country_list;
		std::vector<std::vector<std::string>> border_list;

		friend std::ostream& operator<<(std::ostream&, const MapLoader&); //stream insertion operator
};

class ConquestFileReader
{
public:

	ConquestFileReader();
	ConquestFileReader(const ConquestFileReader&a); //copy constructer
	ConquestFileReader(std::string mapfile);

	void setfile(std::string newfile) { file = newfile; };
	void setmap(Map* new_map) { this->created_map = new_map; }
	Map* getmap() { return this->created_map; }
	std::string getfile() { return file; };

	void FileReader(std::string mapfile);
	Map LoadMap(std::vector<std::vector<std::string>>continents, std::vector<std::vector<std::string>> territories, std::vector<std::vector<std::string>>borders);

	ConquestFileReader& operator=(const ConquestFileReader& oldloader);// assignment operator
	~ConquestFileReader();

private:
	Map* created_map; //this will store the map objects once they are created
	std::string file;

	//lists used to store informaion taken from .map files
	std::vector<std::vector<std::string>> continent_list;
	std::vector<std::vector<std::string>> country_list;
	std::vector<std::vector<std::string>> border_list;

	friend std::ostream& operator<<(std::ostream&, const MapLoader&); //stream insertion operator

};

class ConquestFileReaderAdapter : MapLoader
{
private:
	ConquestFileReader *conquest_map;
public:
	ConquestFileReaderAdapter(ConquestFileReader conquest_file_reader);
	void FileReader(std::string mapfile);


};