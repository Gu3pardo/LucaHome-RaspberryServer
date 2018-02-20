#include <stdio.h>
#include <sqlite3.h>
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef ITEMPLATE_DATABASE_H
#define ITEMPLATE_DATABASE_H

template<class T> class ITemplateDatabase
{
protected:
	virtual char open() { return -69; }
	virtual char create() { return -69; }
	virtual char close() { return -69; }

public:
	virtual char Dispose() {}

	virtual vector<T> GetList() { return vector<T>(); }

	virtual char Insert(int rowId, T entry) { return -69; }
	virtual char Update(T entry) { return -69; }
	virtual char Delete(T entry) { return -69; }
};

#endif
