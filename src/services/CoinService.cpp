#include "CoinService.h"

/*===============PUBLIC==============*/

CoinService::CoinService()
{
}

CoinService::~CoinService()
{
}

void CoinService::Initialize(FileController fileController, std::string coinFile)
{
	_fileController = fileController;
	_coinFile = coinFile;

	LoadData();
}

void CoinService::LoadData()
{
	std::string coinFileContent = _fileController.ReadFile(_coinFile);
	_coinList = _xmlService.GetCoinList(coinFileContent);
}

std::string CoinService::PerformAction(std::vector<std::string> data, AuthentificationService authentificationService, ChangeService changeService, std::string username)
{
	std::string action = data[ACTION_INDEX];
	std::string actionParameter = data[ACTION_PARAMETER_INDEX];

	if (action == GET)
	{
		if (actionParameter == ALL)
		{
			if (!authentificationService.IsUserAdmin(username)) {
				return COIN_ERROR_NR_207;
			}

			return getJsonStringAll();
		}
		else if (actionParameter == FOR_USER)
		{
			return getJsonStringUser(username);
		}
		return COIN_ERROR_NR_202;
	}

	else if (action == ADD)
	{
		if (data.size() == COIN_DATA_SIZE)
		{
			if (addCoin(data, changeService, username))
			{
				return COIN_ADD_SUCCESS;
			}
			return COIN_ERROR_NR_203;
		}
		return COIN_ERROR_NR_201;
	}

	else if (action == UPDATE)
	{
		if (data.size() == COIN_DATA_SIZE)
		{
			if (updateCoin(data, changeService, username))
			{
				return COIN_UPDATE_SUCCESS;
			}
			return COIN_ERROR_NR_204;
		}
		return COIN_ERROR_NR_201;
	}

	else if (action == DELETE)
	{
		if (deleteCoin(atoi(data[COIN_ID_INDEX].c_str()), changeService, username))
		{
			return COIN_DELETE_SUCCESS;
		}
		return COIN_ERROR_NR_205;
	}

	return COIN_ERROR_NR_200;
}

/*==============PRIVATE==============*/

void CoinService::saveCoins(ChangeService changeService, std::string username)
{
	std::string xmldata = _xmlService.GenerateCoinsXml(_coinList);
	_fileController.SaveFile(_coinFile, xmldata);

	changeService.UpdateChange("Coins", username);
}

std::string CoinService::getJsonStringAll()
{
	std::stringstream out;
	out << "[";

	std::stringstream data;
	for (int index = 0; index < _coinList.size(); index++)
	{
		CoinDto coin = _coinList[index];
		data << coin.JsonString() << ",";
	}

	out << data.str().substr(0, data.str().size() - 1) << "]" << "\x00" << std::endl;

	return out.str();
}

std::string CoinService::getJsonStringUser(std::string username)
{
	std::stringstream out;
	out << "{\"Data\":[";

	std::stringstream data;
	for (int index = 0; index < _coinList.size(); index++)
	{
		CoinDto coin = _coinList[index];

		if (coin.GetUser() == username)
		{
			data << coin.JsonString() << ",";
		}
	}

	out << data.str().substr(0, data.str().size() - 1) << "]}" << "\x00" << std::endl;

	return out.str();
}

bool CoinService::addCoin(std::vector<std::string> newCoinData, ChangeService changeService, std::string username)
{
	CoinDto newCoin(
		atoi(newCoinData[COIN_ID_INDEX].c_str()),
		newCoinData[COIN_NAME_INDEX].c_str(),
		newCoinData[COIN_TYPE_INDEX].c_str(),
		Tools::ConvertStrToDouble(newCoinData[COIN_AMOUNT_INDEX].c_str()));

	_coinList.push_back(newCoin);

	saveCoins(changeService, username);
	LoadData();

	return true;
}

bool CoinService::updateCoin(std::vector<std::string> updateCoinData, ChangeService changeService, std::string username)
{
	int id = atoi(updateCoinData[COIN_ID_INDEX].c_str());

	for (int index = 0; index < _coinList.size(); index++)
	{
		if (_coinList[index].GetId() == id)
		{
			_coinList[index].SetUser(updateCoinData[COIN_NAME_INDEX].c_str());
			_coinList[index].SetType(updateCoinData[COIN_TYPE_INDEX].c_str());
			_coinList[index].SetAmount(Tools::ConvertStrToDouble(updateCoinData[COIN_AMOUNT_INDEX].c_str()));

			saveCoins(changeService, username);
			LoadData();

			return true;
		}
	}
	return false;
}

bool CoinService::deleteCoin(int id, ChangeService changeService, std::string username)
{
	std::vector<CoinDto>::iterator it = _coinList.begin();

	while (it != _coinList.end())
	{
		if ((*it).GetId() == id)
		{
			it = _coinList.erase(it);

			saveCoins(changeService, username);
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
