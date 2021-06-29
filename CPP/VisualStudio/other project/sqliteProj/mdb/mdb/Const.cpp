#include "pch.h"
#include "Const.h"

LPCTSTR Const::DATABASE_FILE = _T("\\FlyCode.db");
//LPCTSTR Const::TABLE_USER = _T("User");
//LPCTSTR Const::FIELD_USERNAME = _T("UserName");
//LPCTSTR Const::FIELD_SCORE = _T("Score");
/****
 .\sqlite3 FlyCodeTable.db
SQLite version 3.26.0 2018-12-01 12:34:55
Enter ".help" for usage hints.

sqlite> .databases
main: **\SQLlite\sqlite-tools-win32-x86-3260000\FlyCodeTable.db

//编号 编码 词条 词库分类 排序 固顶
sqlite> create table TableFlyCode(
   ...> nId int primary key not null,
   ...> encode char(10) not null,
   ...> entry char(100) not null,
   ...> classify char(20) not null,
   ...> sort int not null,
   ...> settop int
   ...> );

sqlite> .schema TableFlyCode
CREATE TABLE TableFlyCode(
nId int primary key not null,
encode char(10) not null,
entry char(100) not null,
classify char(20) not null,
sort int not null,
settop int
);
**/
