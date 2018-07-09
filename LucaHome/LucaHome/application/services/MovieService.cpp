#include "MovieService.h"

/*===============PUBLIC==============*/

MovieService::MovieService()
{
}

MovieService::~MovieService()
{
}

void MovieService::Initialize()
{
	LoadData();
}

string MovieService::PerformAction(vector<string> data)
{
	string action = data[ACTION_INDEX];
	string actionParameter = data[ACTION_PARAMETER_INDEX];

	if (action == GET)
	{
		if (actionParameter == COUNT)
		{
			return Tools::ConvertIntToStr(getMovieCount());
		}
		else if (actionParameter == ALL)
		{
			return getJsonString(0, getMovieCount() - 1, false);
		}
		else if (actionParameter == INDEX)
		{
			if (data.size() == MOVIE_INDEX_DATA_SIZE)
			{
				string additionalParameter = data[MOVIE_ADDITIONAL_INDEX];
				return getJsonString(atoi(data[MOVIE_LOW_INDEX].c_str()), atoi(data[MOVIE_HIGH_INDEX].c_str()), (additionalParameter == ALL));
			}
			return MOVIE_ERROR_WRONG_WORD_SIZE;
		}
	}

	else if (action == UPDATE)
	{
		if (data.size() == MOVIE_DATA_SIZE)
		{
			if (updateMovieData(data))
			{
				return MOVIE_UPDATE_SUCCESS;
			}
			return MOVIE_ERROR_UPDATE;
		}
		return MOVIE_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == LOAD)
	{
		if (actionParameter == ALL)
		{
			LoadData();
			return MOVIE_LOAD_SUCCESS;
		}
		return COMMAND_ERROR_NO_PARAMETER_FOUND;
	}

	return COMMAND_ERROR_NO_ACTION_FOUND;
}

void MovieService::LoadData()
{
	vector<Movie> movieList;
	vector<string> movieDirectories = PathController::ScanMovieFolder();

	for (int movieIndex = 0; movieIndex < movieDirectories.size(); movieIndex++) {
		string currentMovieDir = movieDirectories.at(movieIndex);

		if (currentMovieDir.find(".") == 0) {
			// Invalid folder
			continue;
		}

		ostringstream nfoFilePathStringStream;
		nfoFilePathStringStream << NAS_PATH_MOVIE << currentMovieDir << "/" << NFO_LUCA_FILE;
		string nfoFilePath = nfoFilePathStringStream.str();

		Movie newMovie = Movie();
		newMovie.SetTitle(currentMovieDir);

		vector<string> nfoFileContent = FileController::ReadFileList(nfoFilePath);

		for (int contentIndex = 0; contentIndex < nfoFileContent.size(); contentIndex++) {
			string currentLine = nfoFileContent.at(contentIndex);
			Tools::ReplaceString(currentLine, "};", "");

			if (currentLine.find("Uuid") != string::npos) {
				Tools::ReplaceString(currentLine, "{Uuid: ", "");
				newMovie.SetUuid(currentLine);
				continue;
			}
			else if (currentLine.find("Description") != string::npos) {
				Tools::ReplaceString(currentLine, "{Description: ", "");
				newMovie.SetDescription(currentLine);
				continue;
			}
			else if (currentLine.find("Genre") != string::npos) {
				Tools::ReplaceString(currentLine, "{Genre: ", "");
				newMovie.SetGenre(currentLine);
				continue;
			}
			else if (currentLine.find("Rating") != string::npos) {
				Tools::ReplaceString(currentLine, "{Rating: ", "");
				newMovie.SetRating(Tools::ConvertStrToInt(currentLine));
				continue;
			}
			else if (currentLine.find("Watched") != string::npos) {
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

void MovieService::saveMovieNFO(Movie movie)
{
	ostringstream nfoFilePathStringStream;
	nfoFilePathStringStream << NAS_PATH_MOVIE << movie.GetTitle() << "/" << NFO_LUCA_FILE;
	string nfoFilePath = nfoFilePathStringStream.str();
	FileController::SaveFile(nfoFilePath, movie.SaveString());
}

int MovieService::getMovieCount()
{
	return _movieList.size();
}

string MovieService::getJsonString(int start, int end, bool stepByStepAllMovies)
{
	int maxIndex = getMovieCount() - 1;

	if (start > maxIndex)
	{
		return MOVIE_ERROR_INVALID_INDEX;
	}

	if (end > maxIndex)
	{
		end = maxIndex;
	}

	stringstream out;
	if ((stepByStepAllMovies && start == 0) || !stepByStepAllMovies) {
		out << "{\"Category\":\"Movie\","
			<< "\"Action\":\"Get\","
			<< "\"Error\":0,"
			<< "\"Success\":true,"
			<< "\"Data\":[";
	}

	stringstream data;
	for (int index = start; index <= end; index++)
	{
		data << _movieList[index].JsonString() << ",";
	}

	if ((stepByStepAllMovies && end == maxIndex) || !stepByStepAllMovies) {
		out << data.str().substr(0, data.str().size() - 1) << "]}";
	}
	else {
		out << data.str();
	}

	out << "\x00" << endl;

	return out.str();
}

bool MovieService::updateMovieData(vector<string> movieData)
{
	string uuid = movieData[MOVIE_UUID_INDEX].c_str();

	for (int index = 0; index < _movieList.size(); index++)
	{
		if (_movieList[index].GetUuid() == uuid)
		{
			_movieList[index].SetTitle(movieData[MOVIE_TITLE_INDEX]);
			_movieList[index].SetGenre(movieData[MOVIE_GENRE_INDEX]);
			_movieList[index].SetDescription(movieData[MOVIE_DESCRIPTION_INDEX]);
			_movieList[index].SetRating(atoi(movieData[MOVIE_RATING_INDEX].c_str()));
			_movieList[index].SetWatched(atoi(movieData[MOVIE_WATCH_COUNT_INDEX].c_str()));

			saveMovieNFO(_movieList[index]);

			return true;
		}
	}

	return false;
}
