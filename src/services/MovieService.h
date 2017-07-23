#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>

#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <syslog.h>

#include "../common/dto/MovieDto.h"
#include "../common/utils/Tools.h"
#include "../controller/FileController.h"
#include "../controller/PathController.h"
#include "RemoteService.h"

#define GET "GET"
#define UPDATE "UPDATE"
#define LOAD "LOAD"
#define COUNT "COUNT"
#define ALL "ALL"
#define INDEX "INDEX"

#define MOVIE_DATA_SIZE 10
#define REDUCED "REDUCED"

#define NFO_LUCA_FILE "NFO.luca"

#ifndef MOVIESERVICE_H
#define MOVIESERVICE_H

class MovieService {
private:
	std::vector<MovieDto> _movieList;

	FileController _fileController;
	PathController _pathController;

	void loadAllMovies();
	void saveMovieNFO(MovieDto, std::string);

	std::string generateRestEntry(MovieDto);
	std::string generateReducedEntry(MovieDto);
	int getCount();

	std::string getRestString(int, int);
	std::string getReducedString(int, int);

	bool updateMovieData(std::vector<std::string>, std::string);

public:
	MovieService();
	~MovieService();

	void Initialize(FileController, PathController);
	std::string PerformAction(std::string, std::vector<std::string>, std::string, RemoteService);
	void ReloadData();
};

#endif
