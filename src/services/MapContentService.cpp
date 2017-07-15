#include "MapContentService.h"

/*===============PUBLIC==============*/

MapContentService::MapContentService()
{
}

MapContentService::~MapContentService()
{
}

void MapContentService::Initialize(FileController fileController)
{
	_fileController = fileController;
	_mapContentFile = "/etc/default/lucahome/mapcontent";

	load();
}

std::string MapContentService::PerformAction(std::string action, std::vector<std::string> data, ChangeService changeService, std::string username)
{
	if (action == GET)
	{
		if (data[4] == ALL)
		{
			if (data.size() == 6) {
				if (data[5] == WEBSITE) {
					return getReducedString();
				}
			}
			else {
				return getRestString();
			}
		}
	}
	else if (action == ADD)
	{
		if (data.size() == MAP_CONTENT_DATA_SIZE)
		{
			if (add(data, changeService, username))
			{
				return "addmapcontent:1";
			}
			else
			{
				return "Error 140:Could not add mapcontent";
			}
		}
		else
		{
			return "Error 141:Wrong word size for mapcontent";
		}
	}
	else if (action == UPDATE)
	{
		if (data.size() == MAP_CONTENT_DATA_SIZE)
		{
			if (update(data, changeService, username))
			{
				return "updatemapcontent:1";
			}
			else
			{
				return "Error 142:Could not update mapcontent";
			}
		}
		else
		{
			return "Error 141:Wrong word size for mapcontent";
		}
	}
	else if (action == DELETE)
	{
		if (deleteEntry(atoi(data[4].c_str()), changeService, username))
		{
			return "deletemapcontent:1";
		}
		else
		{
			return "Error 143:Could not delete mapcontent";
		}
	}
	else
	{
		return "Error 144:Action not found for mapcontent";
	}
}

void MapContentService::ReloadMapContent()
{
	syslog(LOG_INFO, "Reloading map content!");
	load();
}

/*==============PRIVATE==============*/

void MapContentService::load()
{
	std::string _mapcontentFileContent = _fileController.ReadFile(_mapContentFile);
	_mapContentList = _xmlService.GetMapContentList(_mapcontentFileContent);
}

void MapContentService::save(ChangeService changeService, std::string username)
{
	std::string xmldata = _xmlService.GenerateMapContentsXml(_mapContentList);
	_fileController.SaveFile(_mapContentFile, xmldata);
	changeService.UpdateChange("MapContent", username);
}

std::string MapContentService::getReducedString()
{
	std::stringstream out;

	for (int index = 0; index < _mapContentList.size(); index++)
	{
		out << "mapcontent:"
			<< Tools::ConvertIntToStr(_mapContentList[index].GetId()) << ":"
			<< _mapContentList[index].GetPosition().GetString() << ":"
			<< Tools::ConvertIntToStr(_mapContentList[index].GetType()) << ":"
			<< _mapContentList[index].GetSchedulesString() << ":"
			<< _mapContentList[index].GetSocketsString() << ":"
			<< _mapContentList[index].GetTemperatureArea() << ":"
			<< Tools::ConvertIntToStr(_mapContentList[index].GetVisibility()) << ";";
	}

	out << "\x00" << std::endl;

	return out.str();
}

std::string MapContentService::getRestString()
{
	std::stringstream out;

	for (int index = 0; index < _mapContentList.size(); index++)
	{
		out << _mapContentList[index].GetRestString();
	}
	out << "\x00" << std::endl;

	return out.str();
}

bool MapContentService::add(std::vector<std::string> words, ChangeService changeService, std::string username)
{

	MapContentDto newEntry = createMapContent(words);
	_mapContentList.push_back(newEntry);

	save(changeService, username);
	load();

	syslog(LOG_INFO, "Added mapcontent %s", newEntry.ToString().c_str());

	return true;
}

bool MapContentService::update(std::vector<std::string> words, ChangeService changeService, std::string username)
{

	MapContentDto updatedEntry = createMapContent(words);

	for (int index = 0; index < _mapContentList.size(); index++)
	{
		if (_mapContentList[index].GetId() == updatedEntry.GetId())
		{
			_mapContentList[index] = updatedEntry;

			save(changeService, username);
			load();

			syslog(LOG_INFO, "Updated mapcontent %s", updatedEntry.ToString().c_str());

			return true;
		}
	}

	return false;
}

bool MapContentService::deleteEntry(int id, ChangeService changeService,
	std::string username)
{
	std::vector<MapContentDto>::iterator it = _mapContentList.begin();
	while (it != _mapContentList.end())
	{
		if ((*it).GetId() == id)
		{
			it = _mapContentList.erase(it);

			save(changeService, username);
			load();

			syslog(LOG_INFO, "Deleted mapcontent %d", id);

			return true;
		}
		else
		{
			++it;
		}
	}
	return false;
}

MapContentDto MapContentService::createMapContent(std::vector<std::string> words)
{
	int id = -1;
	int x = -1;
	int y = -1;
	int type = -1;
	std::vector<std::string> schedules;
	std::vector<std::string> sockets;
	std::string temperatureArea = "";
	int visibility = -1;

	if (typeid(words.at(0)) == typeid(std::string))
	{
		id = atoi(words[0].c_str());
	}
	if (typeid(words.at(1)) == typeid(std::string))
	{
		std::vector<std::string> coordinates = Tools::Explode("|", words[1]);
		if (typeid(coordinates.at(0)) == typeid(std::string) && typeid(coordinates.at(1)) == typeid(std::string))
		{
			x = atoi(coordinates[0].c_str());
			y = atoi(coordinates[1].c_str());
		}
	}
	if (typeid(words.at(2)) == typeid(std::string))
	{
		type = atoi(words[2].c_str());
	}
	if (typeid(words.at(3)) == typeid(std::string))
	{
		schedules = Tools::Explode("|", words[3]);
	}
	if (typeid(words.at(4)) == typeid(std::string))
	{
		sockets = Tools::Explode("|", words[4]);
	}
	if (typeid(words.at(5)) == typeid(std::string))
	{
		temperatureArea = words[5].c_str();
	}
	if (typeid(words.at(6)) == typeid(std::string))
	{
		visibility = atoi(words[6].c_str());
	}

	PointDto position = PointDto(x, y);
	MapContentDto mapContent = MapContentDto(id, position, type, schedules, sockets, temperatureArea, visibility);

	return mapContent;
}
