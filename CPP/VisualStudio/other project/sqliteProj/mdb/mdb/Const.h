#pragma once

class Const
{
public:

	// 字符串
	static const int STRING_MAX_LEN = 20;					// 字符串最大长度

	// 数据库
	static LPCTSTR DATABASE_FILE;							// 数据库文件名

	// 数据库表
	//static LPCTSTR TABLE_USER;								// 用户表名

	// 数据库字段

	static const int MAX_USERNAME_LEN = 10;					// 用户名最大长度（单位：字符）


	// 用户
	static const int USER_MAX_COUNT = 10;					// 最大用户数
};
