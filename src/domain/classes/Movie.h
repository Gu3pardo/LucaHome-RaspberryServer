#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef MOVIE_H
#define MOVIE_H

class Movie {

private:
	string _uuid;
	string _title;
	string _genre;
	string _description;
	int _rating;
	int _watched;

public:
	Movie();
	Movie(string, string, string, string, int, int);
	~Movie();

	void SetUuid(string);
	string GetUuid();

	void SetTitle(string);
	string GetTitle();

	void SetGenre(string);
	string GetGenre();

	void SetDescription(string);
	string GetDescription();

	void SetRating(int);
	int GetRating();

	void SetWatched(int);
	void IncreaseWatched();
	int GetWatched();

	string SaveString();
	string JsonString();
	string ToString();
};

#endif
