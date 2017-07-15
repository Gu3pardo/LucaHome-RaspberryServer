#include "MovieDto.h"

MovieDto::MovieDto()
{
	_title = "N.A.";
	_genre = "N.A.";
	_description = "N.A.";
	_rating = 0;
	_watched = 0;
}

MovieDto::MovieDto(std::string title, std::string genre, std::string description, int rating, int watched)
{
	_title = title;
	_genre = genre;
	_description = description;
	_rating = rating;
	_watched = watched;
}

MovieDto::~MovieDto()
{
}

void MovieDto::SetTitle(std::string title)
{
	_title = title;
}

std::string MovieDto::GetTitle()
{
	return _title;
}

void MovieDto::SetGenre(std::string genre)
{
	_genre = genre;
}

std::string MovieDto::GetGenre()
{
	return _genre;
}

void MovieDto::SetDescription(std::string description)
{
	_description = description;
}

std::string MovieDto::GetDescription()
{
	return _description;
}

void MovieDto::SetRating(int rating)
{
	_rating = rating;
}

int MovieDto::GetRating()
{
	return _rating;
}

void MovieDto::SetWatched(int watched)
{
	_watched = watched;
}

void MovieDto::IncreaseWatched()
{
	_watched++;
}

int MovieDto::GetWatched()
{
	return _watched;
}

std::string MovieDto::ToString()
{
	std::string str =
		std::string("MovieDto { title: ") + _title
		+ std::string("; genre: ") + _genre
		+ std::string("; description: ") + _description
		+ std::string("; rating: ") + Tools::ConvertIntToStr(_rating)
		+ std::string("; watched: ") + Tools::ConvertIntToStr(_watched)
		+ std::string(" }");
	return str;
}
