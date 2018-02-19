#include "ITemplateDatabase.h"
#include "../../domain/classes/SuggestedShoppingItem.h"

using namespace std;

#ifndef SUGGESTED_SHOPPING_ITEM_DATABASE_H
#define SUGGESTED_SHOPPING_ITEM_DATABASE_H

class SuggestedShoppingItemDatabase : public ITemplateDatabase<SuggestedShoppingItem>
{
protected:
	string _databaseName;
	string _tableName = "DatabaseSuggestedShoppingItemListTable";
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
	SuggestedShoppingItemDatabase();
	SuggestedShoppingItemDatabase(string);
	~SuggestedShoppingItemDatabase();

	virtual char Dispose();

	virtual vector<SuggestedShoppingItem> GetList();

	virtual char Insert(int, SuggestedShoppingItem);
	virtual char Update(SuggestedShoppingItem);
	virtual char Delete(string);
};

#endif
