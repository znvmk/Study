#include "pch.h"
#include "resource.h"
#include <MMSystem.h>
#include "Query.h"
#include "Const.h"

/**
 * 构造方法。
 */
Query::Query() :
	m_database(NULL)
{
	// 创建数据库
	this->CreateDatabase();
	csTableClassify = _T("系统词库");
	//AfxMessageBox(csTableClassify);
}

/**
 * 析构方法。
 */
Query::~Query()
{
	// 关闭数据库
	sqlite3_close_v2(m_database);
}

/**
 * 创建数据库。
 */
void Query::CreateDatabase()
{
	sqlite3_stmt* stmt;	// 数据库查询
	CString csDBPath;	// 数据库文件路径
	CString csSQL;		// 查询语句

	// 如果数据库文件不存在则创建，存在则连接它
	GetCurrentDirectory(_MAX_PATH, csDBPath.GetBufferSetLength(_MAX_PATH));
	csDBPath.ReleaseBuffer();
	csDBPath += Const::DATABASE_FILE;
	sqlite3_open16(csDBPath, &m_database);

	// 如果表不存在，创建数据表
	//csSQL.Format(_T("CREATE TABLE IF NOT EXISTS %s(%s INTEGER PRIMARY KEY,%s VARCHAR(%d),%s INTEGER)"),
	//	_T("Sys"), _T("nId"), _T("encode"), Const::MAX_SysNAME_LEN, _T("uScore"));
	/*csSQL.Format(_T("create table if not exists Sys(\
		nId int primary key not null,\
		encode char(10) not null,\
		entry char(100) not null,\
		classify char(20) not null,\
		sort int not null,\
		settop int)\
		"), _T("Sys"),_T("nId"), _T("encode"), _T("entry"), _T("classify"), _T("sort"), _T("settop"));*/
	csSQL.Format(_T("create table if not exists %s(\
		%s int primary key not null,\
		%s char(10) not null,\
		%s char(100) not null,\
		%s char(20) not null,\
		%s int not null,\
		%s int)\
		"), _T("Sys"), _T("nId"), _T("encode"), _T("entry"), _T("classify"), _T("sort"), _T("settop"));
	sqlite3_prepare16_v2(m_database, csSQL, -1, &stmt, NULL);
	sqlite3_step(stmt);

	// 结束查询
	sqlite3_finalize(stmt);
	//AfxMessageBox(_T("create databases successed"));
}


void Query::SetData()
{
	for (int i = 0; i < 10000; i++)
	{
		SaveDate(i);
	}
	//AfxMessageBox(_T("SetData success."));
	/*
	sqlite3_stmt* stmt = NULL;
	sqlite3_exec(m_database, "begin; ", 0, 0, 0);
	const char* sql = "insert into Sys values(? , ? , ? , ? , ? , ? , ?)";
	sqlite3_prepare_v2(m_database, sql, strlen(sql), &stmt, 0);
	
	CString csSQL;
	for (int count = 0; count < 10000; count++)
	{
		int id, sort, settop;
		id = sort = settop = count;

		CString csEncode, csEntry, csCount;
		csEncode = _T("aabb");
		csCount.Format(_T("%d"), count);
		csEntry = "na";
		csEntry += csCount;
		//csTableClassify = _T("系统词库");
		

		
		sqlite3_reset(stmt);
		sqlite3_bind_int(stmt, 1, count);
		//转换**
		const size_t Encodesize = (csEncode.GetLength() + 1) * 2; // 宽字符的长度;
		char* pEncode = new char[Encodesize]; //分配空间;
		size_t sz = 0;
		wcstombs_s(&sz, pEncode, Encodesize, csEncode, _TRUNCATE);
		////转换**
		sqlite3_bind_text(stmt, 2, pEncode, Encodesize,NULL);

		//转换**
		const size_t Entrysize = (csEntry.GetLength() + 1) * 2; // 宽字符的长度;
		char* pEntry = new char[Entrysize]; //分配空间;
		sz = 0;
		wcstombs_s(&sz, pEntry, Entrysize, csEntry, _TRUNCATE);
		////转换**
		sqlite3_bind_text(stmt, 3, pEntry, Entrysize, NULL);

		//转换**
		const size_t TableClassifysize = (csTableClassify.GetLength() + 1) * 2; // 宽字符的长度;
		char* pTableClassify = new char[TableClassifysize]; //分配空间;
		sz = 0;
		wcstombs_s(&sz, pTableClassify, TableClassifysize, csTableClassify, _TRUNCATE);
		////转换**
		sqlite3_bind_text(stmt, 4, pTableClassify, TableClassifysize, NULL);

		sqlite3_bind_int(stmt, 5, count);
		sqlite3_bind_int(stmt, 6, count);
		
		//csSQL.Format(_T("INSERT INTO %s VALUES('%d','%s','%s','%s','%d','%d')"),
		//	_T("Sys"), id, csEncode, csEntry, csTableClassify, sort, settop);
		sqlite3_prepare16_v2(m_database, csSQL, -1, &stmt, NULL);
		sqlite3_step(stmt);
	}
	sqlite3_finalize(stmt);
	sqlite3_exec(m_database, "commit;", 0, 0, 0);
	*/
}


/**
 * 获取数据库中所有用户信息。
 * @param SysInfoList  所有用户信息
 */
CString Query::GetAllData()
{
	sqlite3_stmt* stmt = NULL;
	CString csSQL;
	CString csRecord;
	CStringArray csArrRecord;
	csRecord = _T("");

	// 从数据库中查询所有用户信息
	csSQL.Format(_T("SELECT * FROM %s ORDER BY %s DESC"),
		_T("Sys"), _T("nId"));
	sqlite3_prepare16_v2(m_database, csSQL, -1, &stmt, NULL);

	// 将所有用户信息添加到列表中
	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		csRecord = (LPCTSTR)sqlite3_column_text16(stmt, 5) + csRecord;
		csRecord = _T(" ") + csRecord;
		csRecord = (LPCTSTR)sqlite3_column_text16(stmt, 4) + csRecord;
		csRecord = _T(" ") + csRecord;
		csRecord = (LPCTSTR)sqlite3_column_text16(stmt, 3) + csRecord;
		csRecord = _T(" ") + csRecord;
		csRecord = (LPCTSTR)sqlite3_column_text16(stmt, 2) + csRecord;
		csRecord = _T(" ") + csRecord;
		csRecord = (LPCTSTR)sqlite3_column_text16(stmt, 1) + csRecord;
		csRecord = _T(" ") + csRecord;
		csRecord = (LPCTSTR)sqlite3_column_text16(stmt, 0) + csRecord;
		csRecord = _T(" ") + csRecord;


		//tmp = sqlite3_column_int(stmt, 1);

	}

	// 结束查询
	sqlite3_finalize(stmt);
	//AfxMessageBox(csRecord);
	return csRecord;
}



void Query::Insert(int id, CString encode, CString entry, int sort, int settop)
{
	// 检查该用户是否在数据库中
	sqlite3_stmt* stmt = NULL;
	CString csSQL;
	csSQL.Format(_T("SELECT * FROM %s WHERE %s='%d'"),
		_T("Sys"), _T("nId"), id);
	sqlite3_prepare16_v2(m_database, csSQL, -1, &stmt, NULL);
	if (sqlite3_step(stmt) != SQLITE_DONE)	// 在数据库中
	{
		//if (m_nScore > sqlite3_column_int(stmt, 1))
		{
			csSQL.Format(_T("UPDATE %s set %s='%s',%s='%s',%s='%s',%s='%d',%s='%d' WHERE %s='%d'"),
				_T("Sys"), _T("encode"), encode, _T("entry"), entry, _T("classify"), csTableClassify,
				_T("sort"), sort, _T("settop"), settop, _T("nId"), id);
			sqlite3_prepare16_v2(m_database, csSQL, -1, &stmt, NULL);
			sqlite3_step(stmt);
		}
	}
	else										// 不在数据库中
	{
		csSQL.Format(_T("INSERT INTO %s VALUES('%d','%s','%s','%s','%d','%d')"),
			_T("Sys"), id, encode, entry, csTableClassify, sort, settop);
		sqlite3_prepare16_v2(m_database, csSQL, -1, &stmt, NULL);
		sqlite3_step(stmt);
	}
	sqlite3_finalize(stmt);
}

CString Query::Search(int id)
{
	sqlite3_stmt* stmt = NULL;
	CString csSQL;
	CString csRecord;
	CStringArray csArrRecord;
	csRecord = _T("");

	// 从数据库中查询所有用户信息
	csSQL.Format(_T("SELECT * FROM %s WHERE %s='%d' ORDER BY %s DESC"),
		_T("Sys"), _T("nId"), id, _T("nId"));
	sqlite3_prepare16_v2(m_database, csSQL, -1, &stmt, NULL);

	// 将所有用户信息添加到列表中
	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		csRecord = (LPCTSTR)sqlite3_column_text16(stmt, 5) + csRecord;
		csRecord = _T(" ") + csRecord;
		csRecord = (LPCTSTR)sqlite3_column_text16(stmt, 4) + csRecord;
		csRecord = _T(" ") + csRecord;
		csRecord = (LPCTSTR)sqlite3_column_text16(stmt, 3) + csRecord;
		csRecord = _T(" ") + csRecord;
		csRecord = (LPCTSTR)sqlite3_column_text16(stmt, 2) + csRecord;
		csRecord = _T(" ") + csRecord;
		csRecord = (LPCTSTR)sqlite3_column_text16(stmt, 1) + csRecord;
		csRecord = _T(" ") + csRecord;
		csRecord = (LPCTSTR)sqlite3_column_text16(stmt, 0) + csRecord;
		csRecord = _T(" ") + csRecord;


		//tmp = sqlite3_column_int(stmt, 1);

	}

	// 结束查询
	sqlite3_finalize(stmt);
	//AfxMessageBox(csRecord);
	return csRecord;
}

BOOL Query::Delete(int id)
{
	// 检查该用户是否在数据库中
	sqlite3_stmt* stmt = NULL;
	CString csSQL;
	csSQL.Format(_T("SELECT * FROM %s WHERE %s='%d'"),
		_T("Sys"), _T("nId"), id);
	sqlite3_prepare16_v2(m_database, csSQL, -1, &stmt, NULL);
	if (sqlite3_step(stmt) != SQLITE_DONE)	// 在数据库中
	{
		//if (m_nScore > sqlite3_column_int(stmt, 1))
		{
			csSQL.Format(_T("DELETE FROM %s WHERE %s='%d'"),
				_T("Sys"), _T("nId"), id);
			sqlite3_prepare16_v2(m_database, csSQL, -1, &stmt, NULL);
			sqlite3_step(stmt);
		}
		sqlite3_finalize(stmt);
		return true;
	}
	else										// 不在数据库中	
		return false;
}

/**
 * 将得分保存到数据库中。
 */
void Query::SaveDate(int count)
{
	int id, sort, settop;
	id = sort = settop = count;

	CString csEncode, csEntry, csCount;
	csEncode = _T("aabb");
	csCount.Format(_T("%d"), count);
	csEntry = "na";
	csEntry += csCount;
	//csTableClassify = _T("系统词库");

	sqlite3_stmt* stmt = NULL;
	CString csSQL;
	
	csSQL.Format(_T("INSERT INTO %s VALUES('%d','%s','%s','%s','%d','%d')"),
		_T("Sys"), id, csEncode, csEntry, csTableClassify, sort, settop);
	sqlite3_prepare16_v2(m_database, csSQL, -1, &stmt, NULL);
	sqlite3_step(stmt);
}
