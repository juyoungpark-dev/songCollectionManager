//Juyoung Park #150155182
//jpark214@myseneca.ca
//date: 11/10/2020
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <functional>
#include <numeric>
#include <algorithm>
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
				getline(file, record, '\n');

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
				try
				{
					song.m_price = stod(temp);
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
		//temporary vector to store each length of songs
		vector<int> lengthList(songs.size());
		for (auto x : songs)
			lengthList.push_back(x.length);

		//accumulate total listening time
		auto totalLength = accumulate(lengthList.begin(), lengthList.end(), (int)0);

		//divide into h:m:s
		auto hours = totalLength / 3600;
		auto seconds = totalLength % 3600;
		auto minutes = seconds / 60;
		seconds %= 60;

		//printing out each song
		for (auto x : songs)
		{
			out << x << endl;
		}
		//printing out total listening time
		cout << "----------------------------------------------------------------------------------------" << endl;
		cout << "| " << right << setw(77) << setfill(' ') << "Total Listening Time: " << hours << ":" << minutes << ":" << seconds << " |" << endl;
	}


	//sort in ascending order by title/album/length
	void SongCollection::sort(string s)
	{
		if (s == "title")
			std::sort(songs.begin(), songs.end(), [](const Song& s1, const Song& s2) { return s1.title < s2.title; });
		else if (s == "album")
			std::sort(songs.begin(), songs.end(), [](const Song& s1, const Song& s2) { return s1.album < s2.album; });
		else if (s == "length")
			std::sort(songs.begin(), songs.end(), [](const Song& s1, const Song& s2) { return s1.length < s2.length; });
	}

	//removes the token [None] from the album field
	void SongCollection::cleanAlbum()
	{
		for_each(songs.begin(), songs.end(), [](Song& s) { return s.album == "[None]" ? s.album = "" : s.album; });
	}
	//if the collection has any song by the given artist
	bool SongCollection::inCollection(string artist) const
	{
		return any_of(songs.begin(), songs.end(), [=](const Song& s) { return s.artist == artist; });
	}
	std::list<Song> SongCollection::getSongsForArtist(string artist)const
	{
		list<Song> songList(songs.size());

		auto size = 0;

		copy_if(songs.begin(), songs.end(), songList.begin(), [&](const Song& s) { return s.artist == artist ? ++size : false; });

		songList.resize(size);


		return songList;
	}


	//free helper
	std::ostream& operator<<(std::ostream& out, const Song& theSong)
	{

		out << "| " << left << setfill(' ') << setw(20) << theSong.title
			<< " | " << setw(15) << theSong.artist
			<< " | " << setw(20) << theSong.album
			<< " | ";
		if (theSong.release_year == 0)
		{
			out << right << setw(6) << "";
		}
		else 
		{
			out << right << setw(6) << theSong.release_year;
		}
		out << " | " << theSong.length / 60 << ":" << setw(2) << setfill('0') << theSong.length % 60
			<< " | " << theSong.m_price << " |";

		return out;
	}
}