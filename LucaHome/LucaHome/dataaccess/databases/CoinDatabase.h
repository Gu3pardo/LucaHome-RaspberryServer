#include "ITemplateDatabase.h"
#include "../../domain/classes/Coin.h";

using namespace std;

#ifndef COIN_DATABASE_H
#define COIN_DATABASE_H

class CoinDatabase : public ITemplateDatabase<Coin>
{
protected:
	string _databaseName;
	string _tableName = "DatabaseCoinListTable";
	string _keyRowId = "_rowId";
	string _keyUuid = "_uuid";
	string _keyUserUuid = "_userUuid";
	string _keyType = "_type";
	string _keyAmount = "_amount";

	sqlite3 *database;

	virtual char create();
	virtual char open();
	virtual char close();

public:
	CoinDatabase();
	CoinDatabase(string);
	~CoinDatabase();

	virtual char Dispose();

	virtual vector<Coin> GetList();
	virtual vector<Coin> GetUserList(string);

	virtual char Insert(int, Coin);
	virtual char Update(Coin);
	virtual char Delete(string);
};

#endif
