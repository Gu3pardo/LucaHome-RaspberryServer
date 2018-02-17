#include "ITemplateDatabase.h"
#include "../../domain/classes/ShoppingItem.h";

using namespace std;

#ifndef SHOPPING_ITEM_DATABASE_H
#define SHOPPING_ITEM_DATABASE_H

class ShoppingItemDatabase : public ITemplateDatabase<ShoppingItem>
{
protected:
	string _databaseName;
	string _tableName = "DatabaseShoppingItemListTable";
	string _keyRowId = "_rowId";
	string _keyUuid = "_uuid";
	string _keyName = "_name";
	string _keyType = "_type";
	string _keyQuantity = "_quantity";
	string _keyUnit = "_unit";

	sqlite3 *database;

	virtual char create();
	virtual char open();
	virtual char close();

public:
	ShoppingItemDatabase(string);
	~ShoppingItemDatabase();

	virtual char Dispose();

	virtual vector<ShoppingItem> GetList();

	virtual char Insert(int, ShoppingItem);
	virtual char Update(ShoppingItem);
	virtual char Delete(ShoppingItem);
};

#endif
