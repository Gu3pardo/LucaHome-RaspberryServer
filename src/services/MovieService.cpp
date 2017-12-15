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
	LoadData();
}

std::string MovieService::PerformAction(std::vector<std::string> data, std::string username, RemoteService remoteService)
{
	std::string action = data[ACTION_INDEX];
	std::string actionParameter = data[ACTION_PARAMETER_INDEX];

	if (action == GET)
	{
		if (actionParameter == COUNT)
		{
			return Tools::ConvertIntToStr(getCount());
		}
		else if (actionParameter == ALL)
		{
			return getJsonString(0, getCount() - 1, false);
		}
		else if (actionParameter == INDEX)
		{
			if (data.size() == MOVIE_DATA_INDEX_SIZE)
			{
				std::string additionalParameter = data[MOVIE_DATA_ADDITIONAL_INDEX];
				return getJsonString(atoi(data[MOVIE_DATA_LOW_INDEX].c_str()), atoi(data[MOVIE_DATA_HIGH_INDEX].c_str()), (additionalParameter == ALL));
			}
			return MOVIE_ERROR_NR_47;
		}
	}

	else if (action == UPDATE)
	{
		if (data.size() == MOVIE_DATA_SIZE)
		{
			if (updateMovieData(data, username))
			{
				return MOVIE_UPDATE_SUCCESS;
			}
			return MOVIE_ERROR_NR_42;
		}
		return MOVIE_ERROR_NR_47;
	}

	else if (action == LOAD)
	{
		if (actionParameter == ALL)
		{
			LoadData();
			return MOVIE_LOAD_SUCCESS;
		}
		return MOVIE_ERROR_NR_400;
	}

	return MOVIE_ERROR_NR_48;
}

void MovieService::LoadData()
{
	std::vector<MovieDto> movieList;
	std::vector<std::string> movieDirectories = _pathController.ScanMovieFolder();

	for (int movieIndex = 0; movieIndex < movieDirectories.size(); movieIndex++) {
		std::string currentMovieDir = movieDirectories.at(movieIndex);

		if (currentMovieDir.find(".") == 0) {
			// Invalid folder
			continue;
		}

		std::ostringstream nfoFilePathStringStream;
		nfoFilePathStringStream << NAS_PAH_MOVIE << currentMovieDir << "/" << NFO_LUCA_FILE;
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

/*==============PRIVATE==============*/

void MovieService::saveMovieNFO(MovieDto movie, std::string username)
{
	std::ostringstream nfoFilePathStringStream;
	nfoFilePathStringStream << NAS_PAH_MOVIE << movie.GetTitle() << "/" << NFO_LUCA_FILE;
	std::string nfoFilePath = nfoFilePathStringStream.str();
	_fileController.SaveFile(nfoFilePath, movie.SaveString());
}

int MovieService::getCount()
{
	return _movieList.size();
}

std::string MovieService::getJsonString(int start, int end, bool stepByStepAllMovies)
{
	int maxIndex = getCount() - 1;

	if (start > maxIndex)
	{
		return MOVIE_ERROR_NR_45;
	}

	if (end > maxIndex)
	{
		end = maxIndex;
	}

	std::stringstream out;
	if ((stepByStepAllMovies && start == 0) || !stepByStepAllMovies) {
		out << "[";
	}

	std::stringstream data;
	for (int index = start; index <= end; index++)
	{
		data << _movieList[index].JsonString() << ",";
	}

	if ((stepByStepAllMovies && end == maxIndex) || !stepByStepAllMovies) {
		out << data.str().substr(0, data.str().size() - 1) << "]";
	}
	else {
		out << data.str();
	}

	out << "\x00" << std::endl;

	return out.str();
}

bool MovieService::updateMovieData(std::vector<std::string> movieData, std::string username)
{
	std::string title = movieData[MOVIE_DATA_TITLE_INDEX];

	for (int index = 0; index < _movieList.size(); index++)
	{
		if (_movieList[index].GetTitle() == title)
		{
			_movieList[index].SetDescription(movieData[MOVIE_DATA_DESCRIPTION_INDEX]);
			_movieList[index].SetGenre(movieData[MOVIE_DATA_GENRE_INDEX]);
			_movieList[index].SetRating(atoi(movieData[MOVIE_DATA_RATING_INDEX].c_str()));
			_movieList[index].SetWatched(atoi(movieData[MOVIE_DATA_WATCHED_INDEX].c_str()));

			saveMovieNFO(_movieList[index], username);

			return true;
		}
	}

	return false;
}
