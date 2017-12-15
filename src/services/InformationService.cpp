#include "InformationService.h"

/*===============PUBLIC==============*/

InformationService::InformationService()
{
}

InformationService::~InformationService()
{
}

void InformationService::Initialize(FileController fileController, std::string informationFile)
{
	_fileController = fileController;
	_informationFile = informationFile;

	LoadData();
}

std::string InformationService::PerformAction(std::vector<std::string> data)
{
	std::string action = data[ACTION_INDEX];
	std::string actionParameter = data[ACTION_PARAMETER_INDEX];

	if (action == GET)
	{
		if (actionParameter == ALL) {
			return _informationList.JsonString();
		}
		else if (actionParameter == PHP) {
			return _informationList.PhpString();
		}
		return  INFORMATION_ERROR_NR_111;
	}

	return INFORMATION_ERROR_NR_110;
}

void InformationService::LoadData()
{
	std::string informationFileContent = _fileController.ReadFile(_informationFile);
	_informationList = _xmlService.GetInformation(informationFileContent);
}