#pragma once
#include "sqlite3.h"

class Query
{
public:

	Query();
	~Query();

private:

	sqlite3* m_database;			// 数据库
public:
	CString csTableClassify;
public:
	void CreateDatabase();
	void SaveDate(int count);
	void SetData();
	CString GetAllData();
	void Insert(int id, CString encode, CString entry, int sort, int settop);
	CString Search(int id);
	BOOL Delete(int id);

};
