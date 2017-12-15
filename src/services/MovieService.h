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

#include "../common/dto/MovieDto.h"
#include "../common/utils/Tools.h"
#include "../common/Constants.h"
#include "../controller/FileController.h"
#include "../controller/PathController.h"
#include "RemoteService.h"

#ifndef MOVIESERVICE_H
#define MOVIESERVICE_H

class MovieService {
private:
	std::vector<MovieDto> _movieList;

	FileController _fileController;
	PathController _pathController;

	void saveMovieNFO(MovieDto, std::string);

	int getCount();

	std::string getJsonString(int, int, bool);

	bool updateMovieData(std::vector<std::string>, std::string);

public:
	MovieService();
	~MovieService();

	void Initialize(FileController, PathController);
	std::string PerformAction(std::vector<std::string>, std::string, RemoteService);
	void LoadData();
};

#endif
