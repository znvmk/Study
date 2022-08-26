#include "DbQuery.h"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstring>

DbQuery::DbQuery()
{
	//初始化数据库目录
	//const char *转char * 
	//const char *expr = "goodidea";
	char *buf=new char[strlen(dbDirectory)+1];
	strcpy(buf,dbDirectory);
	DirectoryInit(buf);
	delete[]buf;

	//初始化数据库缓存
	dbDataSet();

	//获取数据库路径	
	//数据库名
	const char *dbName="znsql.zdb";
	//路径
	int dbPathStrlen=std::strlen(dbDirectory)+std::strlen(dbName)+1;
	char *dbPath=(char*)malloc(sizeof(char)*dbPathStrlen);
	//合并两个char *字符串
	ConnectTwoCharStarStr(dbDirectory,dbName,dbPath);
	std::string dbData=fileGet(dbPath);
	createDbCache(dbData);
	

	
}
DbQuery::~DbQuery()
{
	saveToDb();
}
void DbQuery::ConnectTwoCharStarStr(const char *src1, const char *src2, char *dest)
{
    while(*src1 != '\0')
    {
        *dest = *src1;
        src1++;
        dest++;
    }
    while(*src2 != '\0')
    {
        *dest = *src2;
        src2++;
        dest++;
    }
    *dest = '\0';
}
	
void DbQuery::DirectoryInit(char *dir)
{
	//权限分配
	//mode方式： 　　
	//S_IRWXU 00700权限，代表该文件所有者拥有读，写和执行操作的权限
	//S_IRUSR(S_IREAD) 00400权限，代表该文件所有者拥有可读的权限
	//S_IWUSR(S_IWRITE) 00200权限，代表该文件所有者拥有可写的权限
	//S_IXUSR(S_IEXEC) 00100权限，代表该文件所有者拥有执行的权限
	//S_IRWXG 00070权限，代表该文件用户组拥有读，写和执行操作的权限
	//S_IRGRP 00040权限，代表该文件用户组拥有可读的权限
	//S_IWGRP 00020权限，代表该文件用户组拥有可写的权限
	//S_IXGRP 00010权限，代表该文件用户组拥有执行的权限
	//S_IRWXO 00007权限，代表其他用户拥有读，写和执行操作的权限
	//S_IROTH 00004权限，代表其他用户拥有可读的权限
	//S_IWOTH 00002权限，代表其他用户拥有可写的权限
	//S_IXOTH 00001权限，代表其他用户拥有执行的权限
	

	if((access(dir, 0)) != -1)
	{
		std::cout<<"Dir "<<dir<<" exists !"<<std::endl;
	}
	else
	{
		std::cout<<"Dir "<<dir<<" not exists"<<std::endl;
		mkdir(dir,S_IRWXU|S_IRWXG|S_IRWXO);//要给予所有者、用户组、其他成员的读写执行权限
	}
}

void DbQuery::dbDataSet()
{
	const char *dbData=dbDataCreate();
	dbDataWrite("znsql.zdb",dbData);
	
}
void DbQuery::fileDataWrite(char* path , const char *data)
{
	// 以写模式打开文件
	std::ofstream outfile;
   	//outfile.open(dbPath,std::ofstream::binary|std::ofstream::app);
   	outfile.open(path,std::ofstream::binary);
	
	//从终端交互获取数据
	//std::cout << "Writing to the file" << std::endl;
   	//std::cout << "Enter your name: ";
   	//std::cin.getline(data, 100);
   	// 向文件写入用户输入的数据
   	//outfile << data << std::endl;

	outfile << data << std::endl;
	// 关闭打开的文件
   	outfile.close();
}
void DbQuery::dbDataWrite(const char *dbName,const char* dbData)
{
	//数据库名
	//const char *dbName="znsql.zdb";
	//路径
	//如果要使用strlen，必须包含头文件cstring
	int dbPathStrlen=std::strlen(dbDirectory)+std::strlen(dbName)+1;
	char *dbPath=(char*)malloc(sizeof(char)*dbPathStrlen);
	//合并两个char *字符串
	ConnectTwoCharStarStr(dbDirectory,dbName,dbPath);
	
	//创建对应数据库缓存文件夹
	const char *dbTempAdd=".cache";
	int dbTempPathStrlen=std::strlen(dbPath)+std::strlen(dbTempAdd)+1;
	char *dbTempPath=(char*)malloc(sizeof(char)*dbTempPathStrlen);
	ConnectTwoCharStarStr(dbPath,dbTempAdd,dbTempPath);
	
	DirectoryInit(dbTempPath);

	//std::cout<<dbTempPath<<std::endl;

	fileDataWrite(dbPath,dbData);
	
}

const char *DbQuery::dbDataCreate()
{
	//数据库结构
	//数据库信息
	std::string dbInfo="zndb";
	//数据表目录
	std::string dbTableCatalogue="girls:0:test:1";
	//数据表结构:
	//字段属性(FieldProperty):NULL(可能包含NULL),NOT NULL(不允许包含NULL),DEFULT(默认值),PRIMARY KEY(主键),AUTO_INCREMENT(自增),UNSIGNED(无符号),CHARACTER SET NAME(指定一个字符集)
	//字段属性做N位二进制编码（1111111),转换为10进制表示
	std::string dbTableStruct="girls:Id:int:5:1:Name:varchar:10:1:expenditure:double:10 test:Id:int:5:1:Project:varchar:50:2";
	//写入数据库属性信息
	std::string db=dbInfo;
	db +="\n";
	db += dbTableCatalogue;
	db +="\n";
	db +=dbTableStruct;
	db +="\n";
	

	//utf-8中一个汉字占3个字节
	std::string tableData=" 名字  100.00";
	//const char *ch="sakdjflasjkd";
	//std::string s(ch);
	// std::cout<<s<<std::endl;
	for(int i=0;i<500;i++)
	{
		if(i<9)
		{
			db += std::to_string(i+1)+"    "+tableData;
		}
		else if(i>=9&&i<99)
		{
			db += std::to_string(i+1)+"   "+tableData;
		}
		else if(i>=99&&i<999)
		{
			db += std::to_string(i+1)+"  "+tableData;
		}
		else if(i>=999&&i<9999)
		{
			db += std::to_string(i+1)+" "+tableData;
		}
		else if(i>=9999&&i<99999)
		{
			db += std::to_string(i+1)+""+tableData;
		}
	}
   
	db +="\n" ;
   return db.c_str();

}

std::string DbQuery::fileGet(char *filePath)
{
	// 以读模式打开文件
	std::ifstream infile;
	infile.open(filePath,std::ifstream::binary);

	std::cout << "Reading from the file:" << std::endl;

 	infile.seekg(0,infile.end);
 	int length =infile.tellg();
 	infile.seekg(0,infile.beg);
 	std::cout<<"文件大小："<<length<<std::endl;

	//char *buf=(char *)malloc(length);
	char *buf=new char[length+1];
	infile.read(buf,length);

	//防止文件乱码
	//申请分配空间时多申请一个作为结尾，在赋值后，将多申请的一个字符设为'\0'，防止乱码
	buf[length]='\0';
	
	std::string s(buf);

	//free(buf);
	delete[] buf;

	dataShow(s);

 	// 关闭打开的文件
 	infile.close();

	return s;

}

void DbQuery::dataShow(std::string data)
{

}

void DbQuery::dataSpliteByEnter(std::string data)
{
	//std::cout.write(buf,5000);
	//std::cout<<data<<std::endl;
	
	std::string strSplitTemp="";

	int dataStructPos=data.find("\n");
	strSplitTemp=data.substr(0,dataStructPos);
	std::cout<<strSplitTemp<<std::endl;

	std::cout<<"第一组数据开始位置："<<std::endl;
	int pos=0;
	pos=++dataStructPos;
	int strlen=data.length();
	int flag=pos;
	//pos=data.find("\n",dataStructPos);
	while(pos<strlen)
	{
		//std::cout<<pos<<std::endl;
		pos=data.find("\n",flag);
		strSplitTemp=data.substr(flag,pos-flag);
		pos++;
		flag=pos;
		//std::cout<<strSplitTemp<<std::endl;
	}

}

void DbQuery::createDbCache(std::string data)
{
	//获取数据库路径	
	//数据库名
	const char *dbName="znsql.zdb";
	//路径
	//如果要使用strlen，必须包含头文件cstring
	int dbPathStrlen=std::strlen(dbDirectory)+std::strlen(dbName)+1;
	char *dbPath=(char*)malloc(sizeof(char)*dbPathStrlen);
	//合并两个char *字符串
	ConnectTwoCharStarStr(dbDirectory,dbName,dbPath);

	//获取数据库缓存路径
	const char *dbCachePathName=".cache/";
	int dbCachePathStrlen=std::strlen(dbPath)+std::strlen(dbCachePathName)+1;
	char *dbCachePath=(char*)malloc(sizeof(char)*dbCachePathStrlen);
	//合并两个char *字符串
	ConnectTwoCharStarStr(dbPath,dbCachePathName,dbCachePath);

	//std::cout.write(buf,5000);
	//std::cout<<data<<std::endl;
	//数据库结构
	//数据库信息
	std::string dbInfo;
	//数据表目录
	std::string dbTableCatalogue;
	//数据表结构:
	//字段属性(FieldProperty):NULL(可能包含NULL),NOT NULL(不允许包含NULL),DEFULT(默认值),PRIMARY KEY(主键),AUTO_INCREMENT(自增),UNSIGNED(无符号),CHARACTER SET NAME(指定一个字符集)
	//字段属性做N位二进制编码（1111111),转换为10进制表示
	std::string dbTableStruct;
	std::string dbTableData;

	
	int dbInfoEndPos=data.find("\n");
	dbInfo=data.substr(0,dbInfoEndPos);
	std::cout<<"dbInfoEndPos:"<<dbInfoEndPos<<std::endl;
	std::cout<<"dbInfo:"<<dbInfo<<std::endl;

	int dbTableCatalogueEndPos=data.find("\n",++dbInfoEndPos);
	dbTableCatalogue=data.substr(dbInfoEndPos,dbTableCatalogueEndPos-dbInfoEndPos);
	std::cout<<"dbTableCatalogueEndPos:"<<dbTableCatalogueEndPos<<std::endl;
	std::cout<<"dbTableCatalogue:"<<dbTableCatalogue<<std::endl;

	int dbTableStructEndPos=data.find("\n",++dbTableCatalogueEndPos);
	dbTableStruct=data.substr(dbTableCatalogueEndPos,dbTableStructEndPos-dbTableCatalogueEndPos);
	std::cout<<"dbTableStructEndPos:"<<dbTableStructEndPos<<std::endl;
	std::cout<<"dbTableStruct:"<<dbTableStruct<<std::endl;

	int dbTableDataEndPos=data.find("\n",++dbTableStructEndPos);
	dbTableData=data.substr(dbTableStructEndPos,dbTableDataEndPos-dbTableStructEndPos);
	std::cout<<"dbTableDataEndPos:"<<dbTableDataEndPos<<std::endl;
	//std::cout<<"dbTableData:"<<dbTableData<<std::endl;

	//创建对应数据库解析文件
	const char *dbInfoPathAdd="dbInfo";
	int dbInfoPathStrlen=std::strlen(dbCachePath)+std::strlen(dbInfoPathAdd)+1;
	char *dbInfoPath=(char*)malloc(sizeof(char)*dbInfoPathStrlen);
	ConnectTwoCharStarStr(dbCachePath,dbInfoPathAdd,dbInfoPath);

	const char *dbTableCataloguePathAdd="dbTableCatalogue";
	int dbTableCataloguePathStrlen=std::strlen(dbCachePath)+std::strlen(dbTableCataloguePathAdd)+1;
	char *dbTableCataloguePath=(char*)malloc(sizeof(char)*dbTableCataloguePathStrlen);
	ConnectTwoCharStarStr(dbCachePath,dbTableCataloguePathAdd,dbTableCataloguePath);

	const char *dbTableStructPathAdd="dbTableStruct";
	int dbTableStructPathStrlen=std::strlen(dbCachePath)+std::strlen(dbTableStructPathAdd)+1;
	char *dbTableStructPath=(char*)malloc(sizeof(char)*dbTableStructPathStrlen);
	ConnectTwoCharStarStr(dbCachePath,dbTableStructPathAdd,dbTableStructPath);

	const char *dbTableDataPathAdd="dbTableData";
	int dbTableDataPathStrlen=std::strlen(dbCachePath)+std::strlen(dbTableDataPathAdd)+1;
	char *dbTableDataPath=(char*)malloc(sizeof(char)*dbTableDataPathStrlen);
	ConnectTwoCharStarStr(dbCachePath,dbTableDataPathAdd,dbTableDataPath);

	const char *bufDbInfo=dbInfo.c_str();
	fileDataWrite(dbInfoPath,bufDbInfo) ;
	const char *bufDbTableCatalogue=dbTableCatalogue.c_str();
	fileDataWrite(dbTableCataloguePath,bufDbTableCatalogue) ;
	const char *bufDbTableStruct=dbTableStruct.c_str();
	fileDataWrite(dbTableStructPath,bufDbTableStruct) ;
	const char *bufDbTableData=dbTableData.c_str();
	fileDataWrite(dbTableDataPath,bufDbTableData) ;


	int pos=0;
	std::string strSplitTemp="";
	pos=dbTableStructEndPos;
	std::cout<<"第一组数据开始位置："<<std::endl;
	int strlen=data.length();
	int group=20; 
	//pos=data.find("\n",dataStructPos);
	while(pos<strlen)
	{
		//std::cout<<pos<<std::endl;
		strSplitTemp=data.substr(pos,group);
		pos +=group;
		//std::cout<<strSplitTemp<<std::endl;
	}

}
void DbQuery::saveToDb()
{
	//数据库结构
	//数据库信息
	std::string dbInfo;
	//数据表目录
	std::string dbTableCatalogue;
	//数据表结构:
	//字段属性(FieldProperty):NULL(可能包含NULL),NOT NULL(不允许包含NULL),DEFULT(默认值),PRIMARY KEY(主键),AUTO_INCREMENT(自增),UNSIGNED(无符号),CHARACTER SET NAME(指定一个字符集)
	//字段属性做N位二进制编码（1111111),转换为10进制表示
	std::string dbTableStruct;
	std::string dbTableData;



	//文件路径
	const char *dbInfoCurrentPath="znsql.zdb.cache/dbInfo";
	const char *dbTableCatalogueCurrentPath="znsql.zdb.cache/dbTableCatalogue";
	const char *dbTableStructCurrentPath="znsql.zdb.cache/dbTableStruct";
	const char *dbTableDataCurrentPath="znsql.zdb.cache/dbTableData";
	//路径
	//如果要使用strlen，必须包含头文件cstring
	int dbInfoPathStrlen=std::strlen(dbDirectory)+std::strlen(dbInfoCurrentPath)+1;
	char *dbInfoPath=(char*)malloc(sizeof(char)*dbInfoPathStrlen);
	//合并两个char *字符串
	ConnectTwoCharStarStr(dbDirectory,dbInfoCurrentPath,dbInfoPath);
	
	int dbTableCataloguePathStrlen=std::strlen(dbDirectory)+std::strlen(dbTableCatalogueCurrentPath)+1;
	char *dbTableCataloguePath=(char*)malloc(sizeof(char)*dbTableCataloguePathStrlen);
	//合并两个char *字符串
	ConnectTwoCharStarStr(dbDirectory,dbTableCatalogueCurrentPath,dbTableCataloguePath);
	
	int dbTableStructPathStrlen=std::strlen(dbDirectory)+std::strlen(dbTableStructCurrentPath)+1;
	char *dbTableStructPath=(char*)malloc(sizeof(char)*dbTableStructPathStrlen);
	//合并两个char *字符串
	ConnectTwoCharStarStr(dbDirectory,dbTableStructCurrentPath,dbTableStructPath);

	int dbTableDataPathStrlen=std::strlen(dbDirectory)+std::strlen(dbTableDataCurrentPath)+1;
	char *dbTableDataPath=(char*)malloc(sizeof(char)*dbTableDataPathStrlen);
	//合并两个char *字符串
	ConnectTwoCharStarStr(dbDirectory,dbTableDataCurrentPath,dbTableDataPath);
	
	dbInfo=fileGet(dbInfoPath);
	dbTableCatalogue=fileGet(dbTableCataloguePath);
	dbTableStruct=fileGet(dbTableStructPath);
	dbTableData=fileGet(dbTableDataPath);

	//std::cout<<"dbTableData:"<<std::endl<<dbTableData;
	
	//写入数据库属性信息
	std::string strDbData=dbInfo;
	strDbData += dbTableCatalogue;
	strDbData += dbTableStruct;
	strDbData += dbTableData;
	
	const char *chDbData=strDbData.c_str();

	//保存数据库当前路径	
	const char *dbCurrentPath="znsql.zdb.save";
	int dbPathStrlen=std::strlen(dbDirectory)+std::strlen(dbCurrentPath)+1;
	char *dbPath=(char*)malloc(sizeof(char)*dbPathStrlen);
	//合并两个char *字符串
	ConnectTwoCharStarStr(dbDirectory,dbCurrentPath,dbPath);
	
	fileDataWrite(dbPath,chDbData);
}
