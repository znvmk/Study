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
	CString csTable, csTableClassify;
	
public:
	void CreateDatabase();
	
	void SetData();

	void Insert(int id, CString encode, CString entry, int sort, int settop, CString classify);
	
	BOOL Delete(int id);
	//清空数据表
	BOOL Truncate();

	void SaveDate(int count);

	CString Search(int id);
	CString SearchClassify(CString classify);
	CString SearchAllData();

	


};
