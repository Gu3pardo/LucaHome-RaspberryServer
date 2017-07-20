#include "ShoppingListService.h"

/*===============PUBLIC==============*/

ShoppingListService::ShoppingListService()
{
}

ShoppingListService::~ShoppingListService()
{
}

void ShoppingListService::Initialize(FileController fileController)
{
	_fileController = fileController;
	_shoppingListFile = "/etc/default/lucahome/shoppinglist";
	loadShoppingList();
}

std::string ShoppingListService::PerformAction(std::string action, std::vector<std::string> data, ChangeService changeService, std::string username)
{
	if (action == GET)
	{
		if (data.size() == 5) {
			if (data[4] == WEBSITE) {
				return getReducedString();
			}
			else if (data[4] == ALL) {
				return getShoppingList();
			}
			else
			{
				return "Error 155:Parameter not found for shopping entry";
			}
		}
		else
		{
			return "Error 151:Wrong word size for shopping entry";
		}
	}
	else if (action == ADD)
	{
		if (data.size() == SHOPPING_ENTRY_DATA_SIZE)
		{
			if (addShoppingEntry(data, changeService, username))
			{
				return "addEntry:1";
			}
			else
			{
				return "Error 150:Could not add shopping entry";
			}
		}
		else
		{
			return "Error 151:Wrong word size for shopping entry";
		}
	}
	else if (action == UPDATE)
	{
		if (data.size() == SHOPPING_ENTRY_DATA_SIZE)
		{
			if (updateShoppingEntry(data, changeService, username))
			{
				return "updateEntry:1";
			}
			else
			{
				return "Error 152:Could not update shopping entry";
			}
		}
		else
		{
			return "Error 151:Wrong word size for shopping entry";
		}
	}
	else if (action == DELETE)
	{
		if (deleteShoppingEntry(atoi(data[4].c_str()), changeService, username))
		{
			return "deleteEntry:1";
		}
		else
		{
			return "Error 153:Could not delete shopping entry";
		}
	}
	else
	{
		return "Error 154:Action not found action for shopping entry";
	}
}

void ShoppingListService::ReloadData()
{
	syslog(LOG_INFO, "Reloading shopping list!");
	loadShoppingList();
}

/*==============PRIVATE==============*/

void ShoppingListService::loadShoppingList()
{
	std::string shoppingListFileContent = _fileController.ReadFile(_shoppingListFile);
	_shoppingList = _xmlService.GetShoppingList(shoppingListFileContent);
}

void ShoppingListService::saveShoppingList(ChangeService changeService, std::string username)
{
	std::string xmldata = _xmlService.GenerateShoppingListXml(_shoppingList);
	_fileController.SaveFile(_shoppingListFile, xmldata);
	changeService.UpdateChange("ShoppingList", username);
}

std::string ShoppingListService::getShoppingList()
{
	std::stringstream out;

	for (int index = 0; index < _shoppingList.size(); index++)
	{
		out << "{shopping_entry:"
			<< "{id:" << Tools::ConvertIntToStr(_shoppingList[index].GetId()) << "};"
			<< "{name:" << _shoppingList[index].GetName() << "};"
			<< "{group:" << _shoppingList[index].GetGroup() << "};"
			<< "{quantity:" << Tools::ConvertIntToStr(_shoppingList[index].GetQuantity()) << "};"
			<< "};";
	}

	out << "\x00" << std::endl;

	return out.str();
}

std::string ShoppingListService::getReducedString()
{
	std::stringstream out;

	for (int index = 0; index < _shoppingList.size(); index++)
	{
		out << "{shopping_entry:"
			<< Tools::ConvertIntToStr(_shoppingList[index].GetId()) << ":"
			<< _shoppingList[index].GetName() << ":"
			<< _shoppingList[index].GetGroup() << ":"
			<< Tools::ConvertIntToStr(_shoppingList[index].GetQuantity()) << "};";
	}

	out << "\x00" << std::endl;

	return out.str();
}

bool ShoppingListService::addShoppingEntry(std::vector<std::string> newEntryData, ChangeService changeService, std::string username)
{
	ShoppingEntryDto newEntry(atoi(newEntryData[4].c_str()), newEntryData[5], newEntryData[6], atoi(newEntryData[7].c_str()));
	_shoppingList.push_back(newEntry);

	saveShoppingList(changeService, username);
	loadShoppingList();

	syslog(LOG_INFO, "Added shopping entry %d", atoi(newEntryData[3].c_str()));

	return true;
}

bool ShoppingListService::updateShoppingEntry(std::vector<std::string> updateEntryData, ChangeService changeService, std::string username)
{
	ShoppingEntryDto updateEntry(atoi(updateEntryData[4].c_str()), updateEntryData[5], updateEntryData[6], atoi(updateEntryData[7].c_str()));

	for (int index = 0; index < _shoppingList.size(); index++)
	{
		if (_shoppingList[index].GetId() == updateEntry.GetId())
		{
			_shoppingList[index] = updateEntry;

			saveShoppingList(changeService, username);
			loadShoppingList();

			syslog(LOG_INFO, "Updated shopping entry %d", atoi(updateEntryData[3].c_str()));

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
			loadShoppingList();

			syslog(LOG_INFO, "Deleted shopping entry %d", id);

			return true;
		}
		else
		{
			++it;
		}
	}
	return false;
}
