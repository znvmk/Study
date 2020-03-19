#pragma once

#include <mysql.h> 

#pragma comment(lib, "ws2_32.lib")  
#pragma comment(lib, "libmysql.lib") 





class CMySQLOperate
{
public:
	CMySQLOperate();
	~CMySQLOperate();


public:
	//必备的一个数据结构  
	MYSQL mydata;

	CString c;

	//sql字符串  
	char querry[500];

public:
	bool ConnectMySQL();
	bool Querry();
	CString login(CString user);
};

