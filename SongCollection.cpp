//Juyoung Park #150155182
//jpark214@myseneca.ca
//date: 11/10/2020
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "SongCollection.h"
using namespace std;

namespace sdds
{
	void trim(string& str)
	{
		str.erase(str.find_last_not_of(' ') + 1);
		str.erase(0, str.find_first_not_of(' '));
	}

	//custom constructor
	SongCollection::SongCollection(const char* filename)
	{
		ifstream file(filename);
		if (file)
		{
			while (file)
			{
				string record;
				Song song;
				//each record: TITLE(25) ARTIST(25) ALBUM(25) YEAR(5) LENGTH(5)-sec PRICE(5)
				getline(file, record,'\n');

				song.title = record.substr(0, 25);
				trim(song.title);
				record.erase(0, 25);

				song.artist = record.substr(0, 25);
				trim(song.artist);
				record.erase(0, 25);

				song.album = record.substr(0, 25);
				trim(song.album);
				record.erase(0, 25);
				
				string temp = record.substr(0, 5);
				trim(temp);
				try 
				{
					song.release_year = stoi(temp);
				}
				catch (...) 
				{
					song.release_year = 0;
				}
				record.erase(0, 5);

				temp = record.substr(0, 5);
				trim(temp);
				try 
				{
					song.length = stoi(temp);
				}
				catch (...) {}
				record.erase(0, 5);

				temp = record.substr(0, 5);
				trim(temp);
				try {
				song.price = stod(temp);
				}
				catch (...) {}
				record.erase(0, 5);

				songs.push_back(song);
			}
			songs.pop_back();
		}
		else
		{
			throw "Filename is incorrect!";
		}
	}
	//display the content of the collection
	void SongCollection::display(ostream& out) const 
	{
		for (auto i = songs.begin(); i != songs.end();i++)
		{
			out << *i;
		}
	}


	//free helper
	std::ostream& operator<<(std::ostream& out, const Song& theSong) 
	{

		out << "| " << left << setfill(' ') << setw(20) << theSong.title
			<< " | " << setw(15) << theSong.artist
			<< " | " << setw(20) << theSong.album 
			<< " | ";

		if (theSong.release_year == 0)
			out << right << setw(6) << "";
		else
			out << right << setw(6) << theSong.release_year;
		out	<< " | " << theSong.length / 60 << ":" << setw(2) << setfill('0') << theSong.length % 60
			<< " | " << theSong.price << " |" << endl;

		return out;
	}
}