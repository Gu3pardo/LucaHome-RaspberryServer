#include "CoinService.h"

/*===============PUBLIC==============*/

CoinService::CoinService()
{
}

CoinService::~CoinService()
{
}

void CoinService::Initialize(FileController fileController)
{
	_fileController = fileController;
	_coinFile = "/etc/default/lucahome/coins";

	loadCoins();
}

void CoinService::ReloadData()
{
	syslog(LOG_INFO, "Reloading coins!");
	loadCoins();
}

std::string CoinService::PerformAction(std::string action, std::vector<std::string> data, ChangeService changeService, std::string username)
{
	if (action == GET)
	{
		std::string parameter = data[4];
		if (parameter == ALL)
		{
			return getRestStringAll();
		}
		else if (parameter == FOR_USER)
		{
			return getRestStringUser(username);
		}
		else
		{
			return "Error 202:Wrong action parameter for coin";
		}
	}
	else if (action == ADD) {
		if (data.size() == COIN_DATA_SIZE)
		{
			if (addCoin(data, changeService, username))
			{
				return "addCoin:1";
			}
			else
			{
				return "Error 203:Could not add coin";
			}
		}
		else
		{
			return "Error 201:Wrong data size for birthday";
		}
	}
	else if (action == UPDATE) {
		if (data.size() == COIN_DATA_SIZE)
		{
			if (updateCoin(data, changeService, username))
			{
				return "updateCoin:1";
			}
			else
			{
				return "Error 204:Could not update coin";
			}
		}
		else
		{
			return "Error 201:Wrong data size for birthday";
		}
	}
	else if (action == DELETE) {
		if (deleteCoin(atoi(data[ID_INDEX].c_str()), changeService, username))
		{
			return "deleteCoin:1";
		}
		else
		{
			return "Error 205:Could not delete coin";
		}
	}
	else
	{
		return "Error 200:Action not found for coin";
	}
}

/*==============PRIVATE==============*/

void CoinService::loadCoins()
{
	std::string coinFileContent = _fileController.ReadFile(_coinFile);
	_coinList = _xmlService.GetCoinList(coinFileContent);
}

void CoinService::saveCoins(ChangeService changeService, std::string username)
{
	std::string xmldata = _xmlService.GenerateCoinsXml(_coinList);
	_fileController.SaveFile(_coinFile, xmldata);

	changeService.UpdateChange("Coins", username);
}

std::string CoinService::getRestStringAll()
{
	std::stringstream out;

	for (int index = 0; index < _coinList.size(); index++)
	{
		CoinDto coin = _coinList[index];

		out << "{coin:"
			<< "{Id:" << Tools::ConvertIntToStr(coin.GetId()) << "};"
			<< "{User:" << coin.GetUser() << "};"
			<< "{Type:" << coin.GetType() << "};"
			<< "{Amount:" << Tools::ConvertDoubleToStr(coin.GetAmount()) << "};"
			<< "};";
	}

	out << "\x00" << std::endl;

	return out.str();
}

std::string CoinService::getRestStringUser(std::string username)
{
	std::stringstream out;

	for (int index = 0; index < _coinList.size(); index++)
	{
		CoinDto coin = _coinList[index];

		if (coin.GetUser == username) {
			out << "{coin:"
				<< "{Id:" << Tools::ConvertIntToStr(coin.GetId()) << "};"
				<< "{User:" << coin.GetUser() << "};"
				<< "{Type:" << coin.GetType() << "};"
				<< "{Amount:" << Tools::ConvertDoubleToStr(coin.GetAmount()) << "};"
				<< "};";
		}
	}

	out << "\x00" << std::endl;

	return out.str();
}

bool CoinService::addCoin(std::vector<std::string> newCoinData, ChangeService changeService, std::string username)
{
	CoinDto newCoin(
		atoi(newCoinData[ID_INDEX].c_str()),
		newCoinData[NAME_INDEX].c_str(),
		newCoinData[TYPE_INDEX].c_str(),
		Tools::ConvertStrToDouble(newCoinData[AMOUNT_INDEX].c_str()));

	_coinList.push_back(newCoin);

	saveCoins(changeService, username);
	loadCoins();

	syslog(LOG_INFO, "Added coin %d", atoi(newCoinData[ID_INDEX].c_str()));

	return true;
}

bool CoinService::updateCoin(std::vector<std::string> updateCoinData, ChangeService changeService, std::string username)
{
	CoinDto updateCoin(
		atoi(updateCoinData[ID_INDEX].c_str()),
		updateCoinData[NAME_INDEX].c_str(),
		updateCoinData[TYPE_INDEX].c_str(),
		Tools::ConvertStrToDouble(updateCoinData[AMOUNT_INDEX].c_str()));

	for (int index = 0; index < _coinList.size(); index++)
	{
		if (_coinList[index].GetId() == updateCoin.GetId())
		{
			_coinList[index] = updateCoin;

			saveCoins(changeService, username);
			loadCoins();

			syslog(LOG_INFO, "Updated coin %d", atoi(updateCoinData[ID_INDEX].c_str()));

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
			loadCoins();

			syslog(LOG_INFO, "Deleted coin %d", id);

			return true;
		}
		else
		{
			++it;
		}
	}

	return false;
}
