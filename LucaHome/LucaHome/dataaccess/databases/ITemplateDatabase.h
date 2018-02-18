#include <stdio.h>
#include "../../external/sqlite3.h"
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef ITEMPLATE_DATABASE_H
#define ITEMPLATE_DATABASE_H

template<class T> class ITemplateDatabase
{
protected:
	virtual char open();
	virtual char create();
	virtual char close();

public:
	virtual char Dispose();

	virtual vector<T> GetList();

	virtual char Insert(int, T);
	virtual char Update(T);
	virtual char Delete(T);
};

#endif
