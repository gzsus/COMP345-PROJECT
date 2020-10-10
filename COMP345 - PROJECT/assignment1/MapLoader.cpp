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
		int index = 0; //used to get size of data or variable to store in vector
		int counter = 0; //keeps the count of the number of countries to determine number of borders

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
					//std::cout <<"find"<< (temp.find(" ")==-1)<<" index:"<<i<<"\n";
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
				std::cout << "VECTOR country #" << (counter / 5) - 1 << " :" << country_list[(counter / 5) - 1][0] << country_list[(counter / 5) - 1][1] << country_list[(counter / 5) - 1][2] << country_list[(counter / 5) - 1][3] << country_list[(counter / 5) - 1][4] << "\n";
			}

		}

		//check continent count and parameters ERROR CHECKING
		//to check continents you need to read all countries and make sure that the 3rd element in the index, the contninent to which the country belongs
		//adds up properly to the number of continents read
		if (index == -3)
		{
			std::cout << " error in .map file";
			break;
		}
		if (continent_list.size() == 0 && country_list.size() != 0 || continent_list.size() != 0 && country_list.size() == 0)
		{
			if (continent_list.size() == 0)
			{
				std::cout << "no continents stored, error in .map file";
				break;
			}
		}
		if (continent_list.size() != 0 && country_list.size() != 0 && border_list.size() == 0)
		{
			if (continent_list.size() == (stoi(country_list[country_list.size() - 1][2])))
			{
				std::cout << "contninent number has been confirmed with countries at:" << continent_list.size() << " continents" << "\n";
			}
			else
			{
				std::cout << "number of continents and countries do not match !";
			}
		}


		if (temp.find("[borders]") != -1)
		{
			for (int j = 0; j < (country_list.size()); j++) //go through the "j" number of countries and document border info
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
				} while (index != -1);
				for (int k = 0; k < border_list[j].size(); k++)
				{
					std::cout << border_list[j][k] << " ";
				}
				std::cout << "\n";
				//std::cout <<"VECTOR Border #"<<j<<" :"<< border_list[j][0]<<" "<< border_list[j][1]<< "... \n" ;
			}
			getline(input, temp, '\n');
		}

		if (temp.empty() == false) {std::cout << "error in reading file more borders than countries given";}
		//FINAL ERRROR FIX MAKE SURE THERE ARE ENOUGH BORDERS FOR ALL COUNTRIES
		/*
		*
		*
		*/
		
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

//assinment operator

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


