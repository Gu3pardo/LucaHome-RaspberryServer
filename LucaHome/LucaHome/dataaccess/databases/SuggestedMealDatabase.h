#include "ITemplateDatabase.h"
#include "../../domain/classes/SuggestedMeal.h";

using namespace std;

#ifndef SUGGESTED_MEAL_DATABASE_H
#define SUGGESTED_MEAL_DATABASE_H

class SuggestedMealDatabase : public ITemplateDatabase<SuggestedMeal>
{
protected:
	string _databaseName;
	string _tableName = "DatabaseSuggestedMealListTable";
	string _keyRowId = "_rowId";
	string _keyUuid = "_uuid";
	string _keyTitle = "_title";
	string _keyDescription = "_description";
	string _keyRating = "_rating";
	string _keyUseCounter = "_useCounter";
	string _keyShoppingItemUuidList = "_shoppingItemUuidList";

	sqlite3 *database;

	virtual char create();
	virtual char open();
	virtual char close();

public:
	SuggestedMealDatabase();
	SuggestedMealDatabase(string);
	~SuggestedMealDatabase();

	virtual char Dispose();

	virtual vector<SuggestedMeal> GetList();

	virtual char Insert(int, SuggestedMeal);
	virtual char Update(SuggestedMeal);
	virtual char Delete(string);
};

#endif
