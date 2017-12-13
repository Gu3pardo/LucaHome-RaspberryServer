#include "MapContentService.h"

/*===============PUBLIC==============*/

MapContentService::MapContentService()
{
}

MapContentService::~MapContentService()
{
}

void MapContentService::Initialize(FileController fileController, std::string mapContentFile)
{
	_fileController = fileController;
	_mapContentFile = mapContentFile;

	LoadData();
}

std::string MapContentService::PerformAction(std::vector<std::string> data, ChangeService changeService, std::string username)
{
	std::string action = data[ACTION_INDEX];
	std::string actionParameter = data[ACTION_PARAMETER_INDEX];

	if (action == GET)
	{
		if (actionParameter == ALL)
		{
			return getJsonString();
		}
		else if (actionParameter == PHP)
		{
			return getPhpString();
		}
		return MAP_CONTENT_ERROR_NR_146;
	}

	else if (action == ADD)
	{
		if (data.size() == MAP_CONTENT_DATA_SIZE)
		{
			if (add(data, changeService, username))
			{
				return MAP_CONTENT_ADD_SUCCESS;
			}
			return MAP_CONTENT_ERROR_NR_140;
		}
		return MAP_CONTENT_ERROR_NR_141;
	}

	else if (action == UPDATE)
	{
		if (data.size() == MAP_CONTENT_DATA_SIZE)
		{
			if (update(data, changeService, username))
			{
				return MAP_CONTENT_UPDATE_SUCCESS;
			}
			return MAP_CONTENT_ERROR_NR_142;
		}
		return MAP_CONTENT_ERROR_NR_141;
	}

	else if (action == DELETE)
	{
		if (deleteEntry(atoi(actionParameter.c_str()), changeService, username))
		{
			return MAP_CONTENT_DELETE_SUCCESS;
		}
		return MAP_CONTENT_ERROR_NR_143;
	}

	return MAP_CONTENT_ERROR_NR_144;
}

void MapContentService::LoadData()
{
	std::string _mapcontentFileContent = _fileController.ReadFile(_mapContentFile);
	_mapContentList = _xmlService.GetMapContentList(_mapcontentFileContent);
}

/*==============PRIVATE==============*/

void MapContentService::save(ChangeService changeService, std::string username)
{
	std::string xmldata = _xmlService.GenerateMapContentsXml(_mapContentList);
	_fileController.SaveFile(_mapContentFile, xmldata);
	changeService.UpdateChange("MapContent", username);
}

std::string MapContentService::getJsonString()
{
	std::stringstream out;
	out << "\"Data\":[";

	std::stringstream data;
	for (int index = 0; index < _mapContentList.size(); index++)
	{
		MapContentDto mapContent = _mapContentList[index];
		data << mapContent.JsonString() << ",";
	}

	out << data.str().substr(0, data.str().size() - 1) << "]" << "\x00" << std::endl;

	return out.str();
}

std::string MapContentService::getPhpString()
{
	std::stringstream out;

	for (int index = 0; index < _mapContentList.size(); index++)
	{
		out << "mapcontent::"
			<< Tools::ConvertIntToStr(_mapContentList[index].GetId()) << "::"
			<< _mapContentList[index].GetType() << "::"
			<< Tools::ConvertIntToStr(_mapContentList[index].GetTypeId()) << "::"
			<< _mapContentList[index].GetPosition().SaveString() << "::"
			<< _mapContentList[index].GetName() << "::"
			<< _mapContentList[index].GetShortName() << "::"
			<< _mapContentList[index].GetArea() << ".:"
			<< Tools::ConvertBoolToStr(_mapContentList[index].GetVisibility()) << ";";
	}

	out << "\x00" << std::endl;

	return out.str();
}

bool MapContentService::add(std::vector<std::string> words, ChangeService changeService, std::string username)
{

	MapContentDto newEntry = createMapContent(words);
	_mapContentList.push_back(newEntry);

	save(changeService, username);
	LoadData();

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
			LoadData();

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
			LoadData();

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
	std::string type = "";
	int typeId = -1;
	int x = -1;
	int y = -1;
	std::string name = "";
	std::string shortName = "";
	std::string area = "";
	bool visibility = true;

	if (typeid(words.at(MAP_CONTENT_ID_INDEX)) == typeid(std::string))
	{
		id = atoi(words[MAP_CONTENT_ID_INDEX].c_str());
	}
	if (typeid(words.at(MAP_CONTENT_TYPE_INDEX)) == typeid(std::string))
	{
		type = words[MAP_CONTENT_TYPE_INDEX].c_str();
	}
	if (typeid(words.at(MAP_CONTENT_TYPE_ID_INDEX)) == typeid(std::string))
	{
		typeId = atoi(words[MAP_CONTENT_TYPE_ID_INDEX].c_str());
	}
	if (typeid(words.at(MAP_CONTENT_COORDINATES_INDEX)) == typeid(std::string))
	{
		std::vector<std::string> coordinates = Tools::Explode("|", words[MAP_CONTENT_COORDINATES_INDEX]);
		if (typeid(coordinates.at(MAP_CONTENT_COORDINATES_X_INDEX)) == typeid(std::string)
			&& typeid(coordinates.at(MAP_CONTENT_COORDINATES_Y_INDEX)) == typeid(std::string))
		{
			x = atoi(coordinates[MAP_CONTENT_COORDINATES_X_INDEX].c_str());
			y = atoi(coordinates[MAP_CONTENT_COORDINATES_Y_INDEX].c_str());
		}
	}
	if (typeid(words.at(MAP_CONTENT_NAME_INDEX)) == typeid(std::string))
	{
		name = words[MAP_CONTENT_NAME_INDEX].c_str();
	}
	if (typeid(words.at(MAP_CONTENT_SHORT_NAME_INDEX)) == typeid(std::string))
	{
		shortName = words[MAP_CONTENT_SHORT_NAME_INDEX].c_str();
	}
	if (typeid(words.at(MAP_CONTENT_AREA_INDEX)) == typeid(std::string))
	{
		area = words[MAP_CONTENT_AREA_INDEX].c_str();
	}
	if (typeid(words.at(MAP_CONTENT_VISIBILITY_INDEX)) == typeid(std::string))
	{
		visibility = Tools::ConvertStrToBool(words[MAP_CONTENT_VISIBILITY_INDEX].c_str());
	}

	PointDto position = PointDto(x, y);
	MapContentDto mapContent = MapContentDto(id, type, typeId, position, name, shortName, area, visibility);

	return mapContent;
}
