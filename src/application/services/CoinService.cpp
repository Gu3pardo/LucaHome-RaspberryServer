#include "CoinService.h"

/*===============PUBLIC==============*/

CoinService::CoinService()
{
}

CoinService::~CoinService()
{
}

void CoinService::Initialize(string databaseName)
{
	_coinDatabase = CoinDatabase(databaseName);
}

string CoinService::PerformAction(vector<string> data)
{
	string username = data[USER_NAME_INDEX];
	string action = data[ACTION_INDEX];
	string actionParameter = data[ACTION_PARAMETER_INDEX];

	if (action == GET)
	{
		if (actionParameter == ALL)
		{
			return getAllJsonString();
		}
		else if (actionParameter == FOR_USER)
		{
			return getUserJsonString(username);
		}
		return COMMAND_ERROR_NO_ACTION;
	}

	else if (action == ADD)
	{
		if (data.size() == COIN_DATA_SIZE)
		{
			char error = addCoin(data);
			if (!error)
			{
				return COIN_ADD_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return COIN_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == UPDATE)
	{
		if (data.size() == COIN_DATA_SIZE)
		{
			char error = updateCoin(data);
			if (!error)
			{
				return COIN_UPDATE_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return COIN_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == DELETE)
	{
		if (data.size() == COIN_DATA_SIZE)
		{
			char error = deleteCoin(data);
			if (!error)
			{
				return COIN_DELETE_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return COIN_ERROR_WRONG_WORD_SIZE;
	}

	return COMMAND_ERROR_NO_ACTION_FOUND;
}

void CoinService::Dispose() {
	_coinDatabase.Dispose();
}

/*==============PRIVATE==============*/

string CoinService::getAllJsonString()
{
	vector<Coin> coinList = _coinDatabase.GetList();

	stringstream data;
	for (int index = 0; index < coinList.size(); index++)
	{
		data << coinList[index].JsonString() << ",";
	}

	stringstream out;
	out << "{\"Data\":[" << data.str().substr(0, data.str().size() - 1) << "]}" << "\x00" << endl;
	return out.str();
}

string CoinService::getUserJsonString(string userName)
{
	vector<Coin> coinList = _coinDatabase.GetUserList(userName);

	stringstream data;
	for (int index = 0; index < coinList.size(); index++)
	{
		data << coinList[index].JsonString() << ",";
	}

	stringstream out;
	out << "{\"Data\":[" << data.str().substr(0, data.str().size() - 1) << "]}" << "\x00" << endl;
	return out.str();
}

char CoinService::addCoin(vector<string> newCoinData)
{
	Coin newCoin(
		newCoinData[COIN_UUID_INDEX].c_str(),
		newCoinData[COIN_USER_INDEX].c_str(),
		newCoinData[COIN_TYPE_INDEX].c_str(),
		Tools::ConvertStrToDouble(newCoinData[COIN_AMOUNT_INDEX].c_str()));
	return _coinDatabase.Insert(_coinDatabase.GetList().size(), newCoin);
}

char CoinService::updateCoin(vector<string> updateCoinData)
{
	Coin updateCoin(
		updateCoinData[COIN_UUID_INDEX].c_str(),
		updateCoinData[COIN_USER_INDEX].c_str(),
		updateCoinData[COIN_TYPE_INDEX].c_str(),
		Tools::ConvertStrToDouble(updateCoinData[COIN_AMOUNT_INDEX].c_str()));
	return _coinDatabase.Update(updateCoin);
}

char CoinService::deleteCoin(vector<string> deleteCoinData)
{
	Coin deleteCoin(
		deleteCoinData[COIN_UUID_INDEX].c_str(),
		deleteCoinData[COIN_USER_INDEX].c_str(),
		deleteCoinData[COIN_TYPE_INDEX].c_str(),
		Tools::ConvertStrToDouble(deleteCoinData[COIN_AMOUNT_INDEX].c_str()));
	return _coinDatabase.Delete(deleteCoin);
}
