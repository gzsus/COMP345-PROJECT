//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//								MapLoader.cpp Samuel Renaud
//
//
//
//		
//////////////////////////////////////////////////////////////////////////////////////////////////////


#include "MapLoader.h"
#include "Map.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

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
	bool error = false; //if there is an error at one point this is set to true and the program breaks
	file = mapfile;
	//std::cout << mapfile;
	std::ifstream input(mapfile);
	std::string line;
	getline(input, line, '\n');
	std::cout << line;
	while (!input.eof())
	{
		//these are temporary
		std::string temp; //used to store each line from the file
		int index = 0; //used to get size of data or variable to store in vector
		int counter = 0; //keeps the count of the number of countries to determine number of borders

		////////////////////////////CONTINENTS FROM .MAP/////////////////////////////////////////////////
		getline(input, temp, '\n');
		std::cout << temp << "\n";
		if (temp.find("[continents]") != -1) //store all the continents
		{
			counter = 0;  //will allow storage location management for 2d-vector
			while (temp.find("[countries]") == -1)
			{
				continent_list.push_back(std::vector<std::string>()); //allocate new space in top vector
				getline(input, temp, '\n');
				for (int i = 0; i < 3; i++)
				{
					if (index == -1 && i != 0) //missing values
					{
						index = -3;
						break;
					}
					index = temp.find(" "); // store the length of the name of the continent in index
					continent_list[counter].push_back(temp.substr(0, index));
					temp.erase(0, index + 1);
					if (index == -1 && i != 0) { continue; } //no color for continent
					if (index == -1) // no more continents to store
					{
						index = -2;
						break;
					}
				}
				if (index == -2 || index == -3)
				{
					continent_list.erase(continent_list.begin() + (continent_list.size() - 1)); //gets rid of extra country added
					break;
				}
				std::cout << "VECTOR continent #" << counter << " :" << continent_list[counter][0] << " " << continent_list[counter][1] << " " << continent_list[counter][2] << "\n";
				counter++;
			}
		}
		counter = 0; //reset for use in other file reading code

		////////////////////////////COUNTRIES FROM .MAP/////////////////////////////////////////////////
		if (temp.find("[countries]") != -1)
		{
			while (temp.find("[borders]") == -1)
			{
				getline(input, temp, '\n');
				if (temp.find(';') != -1) { continue; }//found a map that has comments after the countries declaration...
				country_list.push_back(std::vector<std::string>()); //allocate vector space for top vector
				for (int i = 0; i < 5; i++)
				{
					if (index == -1 && i != 0) //one of the inputs is missing! 
					{
						index = -3; //use the index as a error indicator -3 means country formatting was problematic
						break;
					}
					index = temp.find(" "); // store the index of the current variable to be stored

					if (i == 0 && index == -1) //this is an empty line and we are done with this section
					{
						index = -2; //needed a way to break out the other loop too 
						break;
					}
					country_list[counter / 5].push_back(temp.substr(0, index));
					temp.erase(0, index + 1);
					counter++;
				}
				if (index == -2 || index == -3) {
					country_list.erase(country_list.begin() + (country_list.size() - 1)); //gets rid of extra country added
					break;
				} //we are done so break out of this too
				std::cout << "VECTOR country #" << (counter / 5) - 1 << " :" << country_list[(counter / 5) - 1][0] <<" "<< country_list[(counter / 5) - 1][1] << " " << country_list[(counter / 5) - 1][2] << " " << country_list[(counter / 5) - 1][3] << " " << country_list[(counter / 5) - 1][4] << "\n";
			}

		}

		////////////////////////////ERROR CHECKING/////////////////////////////////////////////////
		//check continent count and parameters ERROR CHECKING
		//to check continents you need to read all countries and make sure that the 3rd element in the index, the continent to which the country belongs
		//adds up properly to the number of continents read
		if (index == -3)
		{
			std::cout << " error in .map file";
			error = true;
			break;
		}
		if (continent_list.size() == 0 && country_list.size() != 0 || continent_list.size() != 0 && country_list.size() == 0)
		{
			if (continent_list.size() == 0)
			{
				std::cout << "no continents stored, error in .map file";
				error = true;
				break;
			}
		}
		if (continent_list.size() != 0 && country_list.size() != 0 && border_list.size() == 0)
		{
			std::vector<int> number_of_countries;
			for (int i = 0; i < country_list.size(); i++) { number_of_countries.push_back(stoi(country_list[i][2])); }
			auto maximum = std::max_element(number_of_countries.begin(), number_of_countries.end());
			if (continent_list.size() == (*maximum))
			{
				std::cout << "contninent number has been confirmed with countries at:" << continent_list.size() << " continents" << "\n";
			}
			else
			{
				std::cout << "number of continents and countries do not match !";
				std::cout << "number of continents: " << continent_list.size() << " number of countries: " << (*maximum);
				error = true;
				break;
			}
		}

		////////////////////////////BORDERS FROM .MAP/////////////////////////////////////////////////
		if (temp.find("[borders]") != -1)
		{
			for (int j = 0; j < (country_list.size()); j++) //go through the "j" number of countries and document border info
			{
				getline(input, temp, '\n');
				if (temp.rfind(" ") >= temp.size() - 1) { temp=temp.substr(0, temp.size() - 1); }
				if (temp.empty() == true) //not enough borders given
				{
					std::cout << "Not enough borders given!";
					error = true;
					break;
				}
				if (temp.at(0) == ';') //found a map that has comments after the continent declaration...
				{
					j = j - 1;
					continue;
				}
				border_list.push_back(std::vector<std::string>()); //allocate vector space for top vector
				do //in order to get the last value save first then check condition
				{
					index = temp.find(" "); // store the index of the current variable to be stored
					border_list[j].push_back(temp.substr(0, index)); //store into border item list
					temp.erase(0, index + 1);
				} while (index != -1);
				for (int k = 0; k < border_list[j].size(); k++)
				{
					std::cout << border_list[j][k] << " ";
				}
				std::cout << "\n";
			}
			getline(input, temp, '\n');
			if (temp.empty() == false) //make sure the last border line was read
			{
				std::cout << "error in reading file more borders than countries given";
				error = true;
				break;
			}
		}

	}
	input.close();

	std::cout << "\n";

	if (error == false) //if there were no errors in reading the file build the map
	{
		//now build the map using the extracted information and store it into a pointer
		created_map = new Map(LoadMap(continent_list, country_list, border_list));
	}

	else
	{
		//adressing memory leak
		continent_list.clear();
		country_list.clear();
		border_list.clear();
	}

}

MapLoader::~MapLoader()
{
	std::cout << "Deleting Map \n";
	delete created_map;
	created_map = NULL;
}

// this will load the map from the store vectors 
 Map MapLoader::LoadMap(std::vector<std::vector<std::string>>continents, std::vector<std::vector<std::string>> territories, std::vector<std::vector<std::string>>borders)
{
	 //create a new *territory list for each index in the territories vector and store the name
	 std::vector<Territory*> territory_list;
	 std::vector<Continent*> cont_list;
	 for (int i = 0; i < territories.size();i++)
	 {
		 territory_list.push_back(new Territory(territories[i][1], 0));
	 }
	 //need to connect all the territories now using the border list
	 for (int i = 0; i < territories.size(); i++)
	 {
		 //need to loop through all border indices to get all neighbours, annoyingly the first index is just that of the same country so reduce accordingly
		 for (int j = 1; j < borders[i].size(); j++)
		 {
			territory_list[i]->connet_to(territory_list[stoi(borders[i][j])-1]);
			//std::cout << "connected:" << *territory_list[i] << " , TO: " << *territory_list[stoi(borders[i][j]) - 1] << "\n";
		 }
	 }

	 //now that all the territories are created and linked create continents and link them to countries
	 for (int i = 0; i < continents.size(); i++)
	 {
		 //this should also implement bonus but for now it doesnt cause the class is not available
		 cont_list.push_back(new Continent(continents[i][0]));
	 }
	 //go through continents
	 //int j=0; // once we complete a series of countries counted by j we dont want j=0 again it should just keep going from where it was before
	 for (int i = 0; i < cont_list.size(); i++)
	 {
		 for (int j = 0; j < territories.size(); j++)
		 {
			 if (i + 1 == stoi(territories[j][2]))
			 {
				 cont_list[i]->add_territory(territory_list[j]);
			 }
		 }
	 }

	 //Finally create a new map and add the continents to it
	 Map* created_map = new Map("created_map");
	 for (int i = 0; i < cont_list.size(); i++)
	 {
		  created_map->add_continent(cont_list[i]);
	 }

	 if (false == created_map->validate())
	{
		 std::cout << "validation of the map has failed! \n";
	}
	 else
	 {
		 std::cout << "map validation succesful! \n";
	 }


	 return *created_map;
}

//assingment operator
 MapLoader& MapLoader::operator=(const MapLoader& oldloader)
 {
	 file = oldloader.file;
	 return *this;
 }

 
 //set the file for the maploader object
void MapLoader::setfile(std::string newfile) {file = newfile;}
//get the file for this object
std::string MapLoader::getfile(){return file;}
//tostring overload
std::ostream& operator<<(std::ostream &ostrm, const MapLoader &maploader)
{	return ostrm << "Maploader Loading: (" << maploader.file << ")"; }


