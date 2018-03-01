#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>

#include "../../crosscutting/Constants.h"
#include "../../crosscutting/controller/FileController.h"
#include "../../crosscutting/controller/PathController.h"
#include "../../domain/classes/Movie.h"

using namespace std;

#ifndef MOVIE_SERVICE_H
#define MOVIE_SERVICE_H

class MovieService
{
private:
	vector<Movie> _movieList;

	void saveMovieNFO(Movie);
	bool updateMovieData(vector<string>);

	int getMovieCount();
	string getJsonString(int, int, bool);

public:
	MovieService();
	~MovieService();

	void Initialize();
	string PerformAction(vector<string>);
	void LoadData();
};

#endif
