#include "ITemplateDatabase.h"
#include "../../domain/classes/Meal.h"

using namespace std;

#ifndef MEAL_DATABASE_H
#define MEAL_DATABASE_H

class MealDatabase : public ITemplateDatabase<Meal>
{
protected:
	string _databaseName;
	string _tableName = "DatabaseMealListTable";
	string _keyRowId = "_rowId";
	string _keyUuid = "_uuid";
	string _keyTitle = "_title";
	string _keyDescription = "_description";
	string _keyWeekday = "_weekday";
	string _keyDay = "_day";
	string _keyMonth = "_month";
	string _keyYear = "_year";
	string _keyShoppingItemUuidList = "_shoppingItemUuidList";

	sqlite3 *database;

	virtual char create();
	virtual char open();
	virtual char close();

public:
	MealDatabase();
	MealDatabase(string);
	~MealDatabase();

	virtual char Dispose();

	virtual vector<Meal> GetList();

	virtual char Insert(Meal);
	virtual char Update(Meal);
	virtual char Delete(string);
};

#endif
