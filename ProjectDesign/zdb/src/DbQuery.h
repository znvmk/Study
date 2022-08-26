#include <iostream>
#include <cstring>

class DbQuery
{
public:
	DbQuery();//9
	~DbQuery();//35
public:
	const char *dbDirectory="out/db/";
public:
	//连接char*两个字符串//39
	void ConnectTwoCharStarStr(const char *src1, const char *src2, char *dest);

	//函数路径配置//56
	void DirectoryInit(char *dir);

	//设置测试数据库数据//85
	void dbDataSet();

	//写文件//91
	void fileDataWrite(char *path,const char *data);

	//写数据库文件//109
	void dbDataWrite(const char *dbName,const char *dbData);

	//数据库测试数据创造//134
	const char *dbDataCreate();

	//读文件//189
	std::string fileGet(char *filePath);	

	//终端打印文件//216
	void dataShow(std::string data);

	//"\n"字符分割字符串//221
	void dataSpliteByEnter(std::string data);

	//创建数据库缓冲，按照表结构定义字符分割字符串//250
	void createDbCache(std::string data);
	
	//操作缓存结束后，存入数据库//350
	void saveToDb();
};
