#include <string>
#include <cstring>
#include <iostream>

#include "../common/dto/MapContentDto.h"
#include "../common/utils/Tools.h"
#include "../common/Constants.h"
#include "../controller/FileController.h"
#include "shared/ChangeService.h"

#ifndef MAPCONTENTSERVICE_H
#define MAPCONTENTSERVICE_H

class MapContentService {

private:
	std::string _mapContentFile;
	std::vector<MapContentDto> _mapContentList;

	FileController _fileController;
	XmlService _xmlService;

	void save(ChangeService, std::string);

	std::string getJsonString();
	std::string getPhpString();

	bool add(std::vector<std::string>, ChangeService, std::string);
	bool update(std::vector<std::string>, ChangeService, std::string);
	bool deleteEntry(int, ChangeService, std::string);

	MapContentDto createMapContent(std::vector<std::string>);

public:
	MapContentService();
	~MapContentService();

	void Initialize(FileController, std::string);
	std::string PerformAction(std::vector<std::string>, ChangeService, std::string);
	void LoadData();
};

#endif
