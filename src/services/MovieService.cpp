#include "MovieService.h"

/*===============PUBLIC==============*/

MovieService::MovieService()
{
}

MovieService::~MovieService()
{
}

void MovieService::Initialize(FileController fileController, PathController pathController)
{
	_fileController = fileController;
	_pathController = pathController;
	loadAllMovies();
}

std::string MovieService::PerformAction(std::string action, std::vector<std::string> data, std::string username, RemoteService remoteService)
{
	if (action == GET)
	{
		if (data[4] == COUNT)
		{
			return Tools::ConvertIntToStr(getCount());
		}
		else if (data[4] == ALL)
		{
			if (data[5] == REDUCED) {
				return getReducedString(0, getCount() - 1);
			}
			else {
				return getRestString(0, getCount() - 1);
			}
		}
		else if (data[4] == INDEX)
		{
			if (data[5] == REDUCED) {
				if (data.size() == 8)
				{
					return getReducedString(atoi(data[5].c_str()), atoi(data[6].c_str()));
				}
				else
				{
					return "Error 47:Wrong word size for movie";
				}
			}
			else {
				if (data.size() == 7)
				{
					return getRestString(atoi(data[5].c_str()), atoi(data[6].c_str()));
				}
				else
				{
					return "Error 47:Wrong word size for movie";
				}
			}
		}
	}
	else if (action == UPDATE)
	{
		if (data.size() == MOVIE_DATA_SIZE)
		{
			if (updateMovieData(data, username))
			{
				return "updatemovie:1";
			}
			else
			{
				return "Error 42:Could not update movie";
			}
		}
		else
		{
			return "Error 47:Wrong word size for movie";
		}
	}
	else if (action == LOAD)
	{
		if (data[4] == ALL)
		{
			loadAllMovies();
			return "loadAllMovies:1";
		}
		else
		{
			return "Error 400:Parameter not found for movie";
		}
	}
	else
	{
		return "Error 48:Action not found for movie";
	}
}

void MovieService::ReloadData()
{
	syslog(LOG_INFO, "Reloading movies!");
	loadAllMovies();
}

/*==============PRIVATE==============*/

void MovieService::loadAllMovies()
{
	std::vector<MovieDto> movieList;

	std::vector<std::string> movieDirectories = _pathController.ScanMovieFolder();
	// Start at index 2, cause first two entries are not valid
	for (int movieIndex = 2; movieIndex < movieDirectories.size(); movieIndex++) {
		std::string currentMovieDir = movieDirectories.at(movieIndex);

		std::ostringstream nfoFilePathStringStream;
		nfoFilePathStringStream << MOVIE_PATH << currentMovieDir << "/" << NFO_LUCA_FILE;
		std::string nfoFilePath = nfoFilePathStringStream.str();

		MovieDto newMovie = MovieDto();
		newMovie.SetTitle(currentMovieDir);

		std::vector<std::string> nfoFileContent = _fileController.ReadFileList(nfoFilePath);

		for (int contentIndex = 0; contentIndex < nfoFileContent.size(); contentIndex++) {
			std::string currentLine = nfoFileContent.at(contentIndex);
			Tools::ReplaceString(currentLine, "};", "");

			if (currentLine.find("Description") != std::string::npos) {
				Tools::ReplaceString(currentLine, "{Description: ", "");
				newMovie.SetDescription(currentLine);
				continue;
			}
			else if (currentLine.find("Genre") != std::string::npos) {
				Tools::ReplaceString(currentLine, "{Genre: ", "");
				newMovie.SetGenre(currentLine);
				continue;
			}
			else if (currentLine.find("Rating") != std::string::npos) {
				Tools::ReplaceString(currentLine, "{Rating: ", "");
				newMovie.SetRating(Tools::ConvertStrToInt(currentLine));
				continue;
			}
			else if (currentLine.find("Watched") != std::string::npos) {
				Tools::ReplaceString(currentLine, "{Watched: ", "");
				newMovie.SetWatched(Tools::ConvertStrToInt(currentLine));
				continue;
			}
		}

		movieList.push_back(newMovie);
	}

	_movieList = movieList;
}

void MovieService::saveMovieNFO(MovieDto movie, std::string username)
{
	std::ostringstream nfoFilePathStringStream;
	nfoFilePathStringStream << MOVIE_PATH << movie.GetTitle() << "/" << NFO_LUCA_FILE;
	std::string nfoFilePath = nfoFilePathStringStream.str();

	std::stringstream fileContent;
	fileContent
		<< "{Description: " << movie.GetDescription() << "};" << std::endl
		<< "{Genre: " << movie.GetGenre() << "};" << std::endl
		<< "{Rating: " << Tools::ConvertIntToStr(movie.GetRating()) << "};" << std::endl
		<< "{Watched: " << Tools::ConvertIntToStr(movie.GetWatched()) << "};";

	_fileController.SaveFile(nfoFilePath, fileContent.str());
}

std::string MovieService::generateRestEntry(MovieDto movie)
{
	std::stringstream out;
	out << "{movie:"
		<< "{Title:" << movie.GetTitle() << "};"
		<< "{Genre:" << movie.GetGenre() << "};"
		<< "{Description:" << movie.GetDescription() << "};"
		<< "{Rating:" << Tools::ConvertIntToStr(movie.GetRating()) << "};"
		<< "{Watched:" << Tools::ConvertIntToStr(movie.GetWatched()) << "};"
		<< "};";
	return out.str();
}

std::string MovieService::generateReducedEntry(MovieDto movie)
{
	std::stringstream out;
	out << "movie:"
		<< movie.GetTitle() << ":"
		<< movie.GetGenre() << ":"
		<< movie.GetDescription() << ":"
		<< Tools::ConvertIntToStr(movie.GetRating()) << ":"
		<< Tools::ConvertIntToStr(movie.GetWatched()) << ";";
	return out.str();
}

int MovieService::getCount()
{
	return _movieList.size();
}

std::string MovieService::getRestString(int start, int end)
{
	if (start > _movieList.size() - 1)
	{
		return "Error 45:Start index higher then last index value";
	}

	if (end > _movieList.size() - 1)
	{
		syslog(LOG_INFO, "Error 46:End index higher then last index value");
		end = _movieList.size() - 1;
	}

	std::stringstream out;

	for (int index = start; index < end; index++)
	{
		out << generateRestEntry(_movieList[index]);
	}
	out << "\x00" << std::endl;

	return out.str();
}

std::string MovieService::getReducedString(int start, int end)
{
	if (start > _movieList.size() - 1)
	{
		return "Error 45:Start index higher then last index value";
	}

	if (end > _movieList.size() - 1)
	{
		syslog(LOG_INFO, "Error 46:End index higher then last index value");
		end = _movieList.size() - 1;
	}

	std::stringstream out;

	for (int index = start; index < end; index++)
	{
		out << generateReducedEntry(_movieList[index]);
	}
	out << "\x00" << std::endl;

	return out.str();
}

bool MovieService::updateMovieData(std::vector<std::string> movieData, std::string username)
{
	std::vector<std::string> socketList = Tools::Explode("|", movieData[9]);

	for (int index = 0; index < _movieList.size(); index++)
	{
		if (_movieList[index].GetTitle() == movieData[4])
		{
			MovieDto updateMovie(
				movieData[4],
				movieData[5],
				movieData[6],
				atoi(movieData[7].c_str()),
				atoi(movieData[8].c_str()));

			_movieList[index] = updateMovie;
			saveMovieNFO(updateMovie, username);

			syslog(LOG_INFO, "Updated movie %s", movieData[4].c_str());

			return true;
		}
	}

	return false;
}
