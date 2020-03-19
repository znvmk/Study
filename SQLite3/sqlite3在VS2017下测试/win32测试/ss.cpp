#include <iostream>
#include <string>
#include "sqlite3.h"
#pragma comment(lib,"sqlite3.lib")
using namespace std;


int main()
{
	sqlite3 * db;
	int nResult = sqlite3_open("test.db", &db);
	if (nResult != SQLITE_OK)
	{
		cout << "open db failed" << sqlite3_errmsg(db) << endl;
		system("pause");
	}
	else
	{
		cout << "open db successed" << endl;
	}
	char* errmsg;
	nResult = sqlite3_exec(db, "create table test.a(\
			id int primary key not null,\
			name varchar(255) not null,\
			); ", NULL, NULL, &errmsg);
	if (nResult != SQLITE_OK)
	{
		sqlite3_close(db);
		cout << "create table failed" << sqlite3_errmsg(db) << endl;
		system("pause");
	}
	string strSql,stmpi;
	for (int i = 0; i < 100; i++)
	{

		strSql += "insert into a(id,name) \
			values(";
		stmpi = to_string(i);
		strSql += stmpi;
		strSql += ",'heh');";
	}
	cout << strSql << endl;
	nResult = sqlite3_exec(db, strSql.c_str(), NULL, NULL, &errmsg);
	if (nResult != SQLITE_OK)
	{
		sqlite3_close(db);
		cout << "insert failed" << sqlite3_errmsg(db)<<endl;
		system("pause");
	}
	system("pause");
	return 0;
}
