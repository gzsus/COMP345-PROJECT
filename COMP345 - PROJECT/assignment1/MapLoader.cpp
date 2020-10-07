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
		//these are temporary
		std::string temp; //used to store each line from the file
		int index; //used to get size of data or variable to store in vector
		int counter = 0; //keeps the count of the number of countries to determine number of borders

		getline(input, temp, '\n');
		std::cout << temp<<"\n";
		if (temp.find("[continents]") != -1) //store all the continents
		{
			counter = 0;  //will allow storage location management for 2d-vector
			while (temp.find("[countries]") == -1)
			{
				continent_list.push_back(std::vector<std::string>()); //allocate new space in top vector
				getline(input, temp, '\n');
				index = temp.find(" "); // store the length of the name of the continent in index
				if (index == -1) { break; } // no more continents to store
				continent_list[counter].push_back(temp.substr(0, index));

				temp.erase(0, index+1);
				index = temp.find(" ") ;
				continent_list[counter].push_back(temp.substr(0, index));

				if (index == -1) { break; } //no color for continent
				temp.erase(0, index+1);
				index = temp.find(" ");
				continent_list[counter].push_back(temp.substr(0, index));

				std::cout <<"VECTOR continent #"<<counter<<" :"<< continent_list[counter][0] << continent_list[counter][1] << continent_list[counter][2] <<"\n";
				counter++;  //switch to next continent storage place
			}
			
		}

		//check continent count and parameters with a method

		counter = 0; //reset for use in other file reading code

		if (temp.find("[countries]") != -1)
		{
			while (temp.find("[borders]") == -1)
			{
				getline(input, temp, '\n');
				if (temp.find(';')!= -1) { continue; }//found a map that has comments after the countries declaration...
				country_list.push_back(std::vector<std::string>()); //allocate vector space for top vector
				for (int i = 0; i < 5; i++)
				{
					index = temp.find(" "); // store the index of the current variable to be stored
					if (i == 0 && index == -1) { break; }//this is an empty line and we are done with this section
					country_list[counter/5].push_back(temp.substr(0, index));
					temp.erase(0, index + 1);
					counter++;
				}
				std::cout << "VECTOR country #" << (counter/5)-1 << " :" << country_list[(counter / 5) - 1][0] << country_list[(counter / 5) - 1][1] << country_list[(counter/5)-1][2] << country_list[(counter / 5) - 1][3] << country_list[(counter / 5) - 1][4]<< "\n";
			}

		}
		//check country count and parameters with a method

		
		if (temp.find("[borders]") != -1)
		{
			for (int j = 0; j < (counter/5); j++) //go through the "j" number of countries and document border info
			{
				getline(input, temp, '\n');
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
				} 
				while (index != -1);
				std::cout <<"VECTOR Border #"<<j<<" :"<< border_list[j][0]<<" "<< border_list[j][1]<< "... \n" ;
			}
		}
		//check country count and parameters with a method

	}

	//now build the map using the extracted information





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


