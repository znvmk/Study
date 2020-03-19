#include <winsock.h>
#include <iostream>
#include <string>
#include <mysql.h>
using namespace std;

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "libmysql.lib")

//单步执行，不想单步执行就注释掉
#define STEPBYSTEP

int main() {
	cout << "****************************************" << endl;

#ifdef STEPBYSTEP
	system("pause");
#endif

	//必备的一个数据结构
	MYSQL mydata;

	//初始化数据库
	if (0 == mysql_library_init(0, NULL, NULL)) {
		cout << "mysql_library_init() succeed" << endl;
	}
	else {
		cout << "mysql_library_init() failed" << endl;
		return -1;
	}

#ifdef STEPBYSTEP
	system("pause");
#endif

	//初始化数据结构
	if (NULL != mysql_init(&mydata)) {
		cout << "mysql_init() succeed" << endl;
	}
	else {
		cout << "mysql_init() failed" << endl;
		return -1;
	}

#ifdef STEPBYSTEP
	system("pause");
#endif

	//在连接数据库之前，设置额外的连接选项
	//可以设置的选项很多，这里设置字符集，否则无法处理中文
	if (0 == mysql_options(&mydata, MYSQL_SET_CHARSET_NAME, "gbk")) {
		cout << "mysql_options() succeed" << endl;
	}
	else {
		cout << "mysql_options() failed" << endl;
		return -1;
	}

#ifdef STEPBYSTEP
	system("pause");
#endif

	//连接数据库
	if (NULL
		!= mysql_real_connect(&mydata, "localhost", "root", "123456", "udb", 3306, NULL, 0))
		//这里的地址，用户名，密码，端口可以根据自己本地的情况更改
	{
		cout << "mysql_real_connect() succeed" << endl;
	}
	else {
		cout << "mysql_real_connect() failed" << endl;
		return -1;
	}

#ifdef STEPBYSTEP
	system("pause");
#endif

	//sql字符串
	string sqlstr;

	//创建一个表
	sqlstr = "CREATE TABLE IF NOT EXISTS user_info";
	sqlstr += "(";
	sqlstr +=
		"user_id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY COMMENT 'Unique User ID',";
	sqlstr +=
		"user_name VARCHAR(100) CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL COMMENT 'Name Of User',";
	sqlstr +=
		"user_second_sum INT UNSIGNED NOT NULL DEFAULT 0 COMMENT 'The Summation Of Using Time'";
	sqlstr += ");";
	if (0 == mysql_query(&mydata, sqlstr.c_str())) {
		cout << "mysql_query() create table succeed" << endl;
	}
	else {
		cout << "mysql_query() create table failed" << endl;
		mysql_close(&mydata);
		return -1;
	}

#ifdef STEPBYSTEP
	system("pause");
#endif

	//向表中插入数据
	sqlstr =
		"INSERT INTO user_info(user_name) VALUES('公司名称'),('一级部门'),('二级部门'),('开发小组'),('姓名');";
	if (0 == mysql_query(&mydata, sqlstr.c_str())) {
		cout << "mysql_query() insert data succeed" << endl;
	}
	else {
		cout << "mysql_query() insert data failed" << endl;
		mysql_close(&mydata);
		return -1;
	}

#ifdef STEPBYSTEP
	system("pause");
#endif

	//显示刚才插入的数据
	sqlstr = "SELECT user_id,user_name,user_second_sum FROM user_info";
	MYSQL_RES *result = NULL;
	if (0 == mysql_query(&mydata, sqlstr.c_str())) {
		cout << "mysql_query() select data succeed" << endl;

		//一次性取得数据集
		result = mysql_store_result(&mydata);
		//取得并打印行数
		int rowcount = mysql_num_rows(result);
		cout << "row count: " << rowcount << endl;

		//取得并打印各字段的名称
		unsigned int fieldcount = mysql_num_fields(result);
		MYSQL_FIELD *field = NULL;
		for (unsigned int i = 0; i < fieldcount; i++) {
			field = mysql_fetch_field_direct(result, i);
			cout << field->name << "\t\t";
		}
		cout << endl;

		//打印各行
		MYSQL_ROW row = NULL;
		row = mysql_fetch_row(result);
		while (NULL != row) {
			for (int i = 0; i < fieldcount; i++) {
				cout << row[i] << "\t\t";
			}
			cout << endl;
			row = mysql_fetch_row(result);
		}

	}
	else {
		cout << "mysql_query() select data failed" << endl;
		mysql_close(&mydata);
		return -1;
	}

#ifdef STEPBYSTEP
	system("pause");
#endif

	//删除刚才建的表
	/*
	sqlstr = "DROP TABLE user_info";
	if (0 == mysql_query(&mydata, sqlstr.c_str())) {
		cout << "mysql_query() drop table succeed" << endl;
	}
	else {
		cout << "mysql_query() drop table failed" << endl;
		mysql_close(&mydata);
		return -1;
	}
	*/
	mysql_free_result(result);
	mysql_close(&mydata);
	mysql_server_end();

	system("pause");
	return 0;
}