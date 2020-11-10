//Juyoung Park #150155182
//jpark214@myseneca.ca
//date: 11/10/2020
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.


#pragma once

#include <string>
#include <vector>
using namespace std;

namespace sdds
{
	struct Song
	{
		string artist;
		string title;
		string album;
		double price;
		int release_year;
		int length; //sec
	};

	class SongCollection
	{
		vector<Song>songs;
	public:
		SongCollection(const char*); //custom constr
		void display(ostream& out) const;
	};

	std::ostream& operator<<(std::ostream& out, const Song& theSong); //free helper
}