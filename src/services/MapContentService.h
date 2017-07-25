#include <string>
#include <cstring>
#include <iostream>

#include "../common/dto/MapContentDto.h"
#include "../common/utils/Tools.h"
#include "../controller/FileController.h"
#include "shared/ChangeService.h"

#define GET "GET"
#define ADD "ADD"
#define UPDATE "UPDATE"
#define DELETE "DELETE"
#define ALL "ALL"
#define MAP_CONTENT_DATA_SIZE 7
#define REDUCED "REDUCED"

#ifndef MAPCONTENTSERVICE_H
#define MAPCONTENTSERVICE_H

class MapContentService {

private:
	std::string _mapContentFile;
	std::vector<MapContentDto> _mapContentList;

	FileController _fileController;
	XmlService _xmlService;

	void load();
	void save(ChangeService, std::string);

	std::string getReducedString();
	std::string getRestString();

	bool add(std::vector<std::string>, ChangeService, std::string);
	bool update(std::vector<std::string>, ChangeService, std::string);
	bool deleteEntry(int, ChangeService, std::string);

	MapContentDto createMapContent(std::vector<std::string>);

public:
	MapContentService();
	~MapContentService();

	void Initialize(FileController, std::string);
	std::string PerformAction(std::string, std::vector<std::string>, ChangeService, std::string);
	void ReloadData();
};

#endif
