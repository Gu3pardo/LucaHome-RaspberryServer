#include "ShoppingListService.h"

/*===============PUBLIC==============*/

ShoppingListService::ShoppingListService()
{
}

ShoppingListService::~ShoppingListService()
{
}

void ShoppingListService::Initialize(FileController fileController, std::string shoppingListFile)
{
	_fileController = fileController;
	_shoppingListFile = shoppingListFile;
	LoadData();
}

std::string ShoppingListService::PerformAction(std::vector<std::string> data, ChangeService changeService, std::string username)
{
	std::string action = data[ACTION_INDEX];
	std::string actionParameter = data[ACTION_PARAMETER_INDEX];

	if (action == GET)
	{
		if (actionParameter == ALL) {
			return getJsonString();
		}
		else if (actionParameter == PHP) {
			return getPhpString();
		}
		return  SHOPPING_ERROR_NR_156;
	}

	else if (action == ADD)
	{
		if (data.size() == SHOPPING_ENTRY_DATA_SIZE)
		{
			if (addShoppingEntry(data, changeService, username))
			{
				return SHOPPING_ADD_SUCCESS;
			}
			return SHOPPING_ERROR_NR_150;
		}
		return SHOPPING_ERROR_NR_151;
	}

	else if (action == UPDATE)
	{
		if (data.size() == SHOPPING_ENTRY_DATA_SIZE)
		{
			if (updateShoppingEntry(data, changeService, username))
			{
				return SHOPPING_UPDATE_SUCCESS;
			}
			return SHOPPING_ERROR_NR_152;
		}
		return SHOPPING_ERROR_NR_151;
	}

	else if (action == DELETE)
	{
		if (deleteShoppingEntry(atoi(data[4].c_str()), changeService, username))
		{
			return SHOPPING_DELETE_SUCCESS;
		}
		return SHOPPING_ERROR_NR_153;
	}

	return SHOPPING_ERROR_NR_154;
}

void ShoppingListService::LoadData()
{
	std::string shoppingListFileContent = _fileController.ReadFile(_shoppingListFile);
	_shoppingList = _xmlService.GetShoppingList(shoppingListFileContent);
}

/*==============PRIVATE==============*/

void ShoppingListService::saveShoppingList(ChangeService changeService, std::string username)
{
	std::string xmldata = _xmlService.GenerateShoppingListXml(_shoppingList);
	_fileController.SaveFile(_shoppingListFile, xmldata);
	changeService.UpdateChange("ShoppingList", username);
}

std::string ShoppingListService::getJsonString()
{
	std::stringstream out;
	out << "\"Data\":[";

	std::stringstream data;
	for (int index = 0; index < _shoppingList.size(); index++)
	{
		ShoppingEntryDto shoppingEntry = _shoppingList[index];
		data << shoppingEntry.JsonString() << ",";
	}

	out << data.str().substr(0, data.str().size() - 1) << "]" << "\x00" << std::endl;

	return out.str();
}

std::string ShoppingListService::getPhpString()
{
	std::stringstream out;

	for (int index = 0; index < _shoppingList.size(); index++)
	{
		out << "shopping_entry::"
			<< Tools::ConvertIntToStr(_shoppingList[index].GetId()) << "::"
			<< _shoppingList[index].GetName() << "::"
			<< _shoppingList[index].GetGroup() << "::"
			<< Tools::ConvertIntToStr(_shoppingList[index].GetQuantity()) << ";";
	}

	out << "\x00" << std::endl;

	return out.str();
}

bool ShoppingListService::addShoppingEntry(std::vector<std::string> newEntryData, ChangeService changeService, std::string username)
{
	ShoppingEntryDto newEntry(
		atoi(newEntryData[SHOPPING_ENTRY_ID_INDEX].c_str()),
		newEntryData[SHOPPING_ENTRY_NAME_INDEX],
		newEntryData[SHOPPING_ENTRY_GROUP_INDEX],
		atoi(newEntryData[SHOPPING_ENTRY_QUANTITY_INDEX].c_str()));

	_shoppingList.push_back(newEntry);

	saveShoppingList(changeService, username);
	LoadData();

	return true;
}

bool ShoppingListService::updateShoppingEntry(std::vector<std::string> updateEntryData, ChangeService changeService, std::string username)
{
	int id = atoi(updateEntryData[SHOPPING_ENTRY_ID_INDEX].c_str());

	for (int index = 0; index < _shoppingList.size(); index++)
	{
		if (_shoppingList[index].GetId() == id)
		{
			_shoppingList[index].SetName(updateEntryData[SHOPPING_ENTRY_NAME_INDEX]);
			_shoppingList[index].SetGroup(updateEntryData[SHOPPING_ENTRY_GROUP_INDEX]);
			_shoppingList[index].SetQuantity(atoi(updateEntryData[SHOPPING_ENTRY_QUANTITY_INDEX].c_str()));

			saveShoppingList(changeService, username);
			LoadData();

			return true;
		}
	}
	return false;
}

bool ShoppingListService::deleteShoppingEntry(int id, ChangeService changeService, std::string username)
{
	std::vector<ShoppingEntryDto>::iterator it = _shoppingList.begin();
	while (it != _shoppingList.end())
	{
		if ((*it).GetId() == id)
		{
			it = _shoppingList.erase(it);

			saveShoppingList(changeService, username);
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
