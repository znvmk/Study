#include "stdafx.h"
#include "resource.h"
#include <MMSystem.h>
#include "Game.h"
#include "Const.h"

/**
 * 构造方法。
 */
Game::Game() : 
	m_nScore(0), 
	m_database(NULL)
{

	// 创建数据库
	this->CreateDatabase();
}

/**
 * 析构方法。
 */
Game::~Game()
{
	// 关闭数据库
	sqlite3_close_v2(m_database);
}

/**
 * 创建数据库。
 */
void Game::CreateDatabase()
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
	csSQL.Format(_T("CREATE TABLE IF NOT EXISTS %s(%s VARCHAR(%d) PRIMARY KEY,%s INTEGER)"),
		Const::TABLE_USER, Const::FIELD_USERNAME, Const::MAX_USERNAME_LEN, Const::FIELD_SCORE);
	sqlite3_prepare16_v2(m_database, csSQL, -1, &stmt, NULL);
	sqlite3_step(stmt);

	// 结束查询
	sqlite3_finalize(stmt);
	AfxMessageBox(_T("create databases successed"));
}



/**
 * 获取数据库中所有用户信息。
 * @param userInfoList  所有用户信息
 */
void Game::GetAllUsers()
{
	sqlite3_stmt* stmt = NULL;
	CString csSQL;
	CString a, b;
	a = "";
	int tmp = 0;
	// 从数据库中查询所有用户信息
	csSQL.Format( _T("SELECT * FROM %s ORDER BY %s DESC"), 
		Const::TABLE_USER, Const::FIELD_SCORE );
	sqlite3_prepare16_v2(m_database, csSQL, -1, &stmt, NULL);

	// 将所有用户信息添加到列表中
	while( sqlite3_step(stmt) == SQLITE_ROW )
	{
		a +=(LPCTSTR)sqlite3_column_text16(stmt, 0);
		tmp=sqlite3_column_int(stmt, 1);
		b.Format(_T("%d"), tmp);
		a += "   space   ";
		a += b;
		a += " ";
	}

	// 结束查询
	sqlite3_finalize(stmt);
	AfxMessageBox(a);
}





/**
 * 将得分保存到数据库中。
 */
void Game::SaveScore()
{
	

	// 获取用户总数
	int nUserCount;
	nUserCount = 2;

	CString csUserName;
	CString csTipText;
	csUserName = "dff";
	m_nScore = 32;

	// 如果数据库中的用户数未超过上限，则保存当前用户的得分
	if (nUserCount < Const::USER_MAX_COUNT)
	{
		

		// 检查该用户是否在数据库中
		sqlite3_stmt* stmt = NULL;
		CString csSQL;
		csSQL.Format( _T("SELECT * FROM %s WHERE %s='%s'"),
			Const::TABLE_USER, Const::FIELD_USERNAME, csUserName );
		sqlite3_prepare16_v2(m_database, csSQL, -1, &stmt, NULL);
		if ( sqlite3_step(stmt) != SQLITE_DONE )	// 在数据库中
		{
			if ( m_nScore > sqlite3_column_int(stmt, 1) )
			{
				csSQL.Format( _T("UPDATE %s set %s='%d' WHERE %s='%s'"),
					Const::TABLE_USER, Const::FIELD_SCORE, m_nScore, 
					Const::FIELD_USERNAME, csUserName );
				sqlite3_prepare16_v2(m_database, csSQL, -1, &stmt, NULL);
				sqlite3_step(stmt);
			}
		}
		else										// 不在数据库中
		{
			csSQL.Format( _T("INSERT INTO %s VALUES('%s','%d')"),
				Const::TABLE_USER, csUserName, m_nScore );
			sqlite3_prepare16_v2(m_database, csSQL, -1, &stmt, NULL);
			sqlite3_step(stmt);
		}
		sqlite3_finalize(stmt);
	}
	else
	{
		// 如果当前用户的得分大于数据库中的最低得分，则删除最低得分并保存当前用户的得分
		sqlite3_stmt* stmt = NULL;
		
			CString csSQL;
			csSQL.Format( _T("UPDATE %s SET %s='%s',%s='%d' WHERE %s='%s'"),
				Const::TABLE_USER, Const::FIELD_USERNAME, csUserName, Const::FIELD_SCORE, 
				m_nScore, Const::FIELD_USERNAME, csUserName);
			sqlite3_prepare16_v2(m_database, csSQL, -1, &stmt, NULL);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
		}
	}

