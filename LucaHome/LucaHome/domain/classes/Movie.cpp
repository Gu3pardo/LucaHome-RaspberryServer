#include "Movie.h"

Movie::Movie()
{
	Movie("", "", "", "", 0, 0);
}

Movie::Movie(string uuid, string title, string genre, string description, int rating, int watched)
{
	_uuid = uuid;
	_title = title;
	_genre = genre;
	_description = description;
	_rating = rating;
	_watched = watched;
}

Movie::~Movie()
{
}

void Movie::SetUuid(string uuid)
{
	_uuid = uuid;
}

string Movie::GetUuid()
{
	return _uuid;
}

void Movie::SetTitle(string title)
{
	_title = title;
}

string Movie::GetTitle()
{
	return _title;
}

void Movie::SetGenre(string genre)
{
	_genre = genre;
}

string Movie::GetGenre()
{
	return _genre;
}

void Movie::SetDescription(string description)
{
	_description = description;
}

string Movie::GetDescription()
{
	return _description;
}

void Movie::SetRating(int rating)
{
	_rating = rating;
}

int Movie::GetRating()
{
	return _rating;
}

void Movie::SetWatched(int watched)
{
	_watched = watched;
}

void Movie::IncreaseWatched()
{
	_watched++;
}

int Movie::GetWatched()
{
	return _watched;
}

string Movie::SaveString()
{
	stringstream streamString;

	streamString
		<< "{Uuid: " << _uuid << "};" << endl
		<< "{Description: " << _description << "};" << endl
		<< "{Genre: " << _genre << "};" << endl
		<< "{Rating: " << Tools::ConvertIntToStr(_rating) << "};" << endl
		<< "{Watched: " << Tools::ConvertIntToStr(_watched) << "};";

	return streamString.str();
}

string Movie::JsonString()
{
	string str =
		string("{")
		+ string("\"Movie\":")
		+ string("{")
		+ string("\"Uuid\":\"") + _uuid + string("\",")
		+ string("\"Title\":\"") + _title + string("\",")
		+ string("\"Genre\":\"") + _genre + string("\",")
		+ string("\"Description\":\"") + _description + string("\",")
		+ string("\"Rating\":") + Tools::ConvertIntToStr(_rating) + string(",")
		+ string("\"Watched\":") + Tools::ConvertIntToStr(_watched)
		+ string("}")
		+ string("}");
	return str;
}

string Movie::ToString()
{
	string str =
		string("Movie { uuid: ") + _uuid
		+ string("; title: ") + _title
		+ string("; genre: ") + _genre
		+ string("; description: ") + _description
		+ string("; rating: ") + Tools::ConvertIntToStr(_rating)
		+ string("; watched: ") + Tools::ConvertIntToStr(_watched)
		+ string(" }");
	return str;
}
