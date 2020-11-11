//Juyoung Park #150155182
//jpark214@myseneca.ca
//date: 11/10/2020
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.


#pragma once

#include <vector>
#include <list>
using namespace std;

namespace sdds
{
	struct Song
	{
		string artist;
		string title;
		string album;
		double m_price;
		int release_year;
		int length; //sec
	};

	class SongCollection
	{
		vector<Song>songs;
	public:
		//part1
		SongCollection(const char*); //custom constr
		void display(ostream& out) const;
		//part2
		void sort(string);
		void cleanAlbum();
		bool inCollection(string s) const;
		std::list<Song> getSongsForArtist(string)const;
	};

	std::ostream& operator<<(std::ostream& out, const Song& theSong); //free helper
}