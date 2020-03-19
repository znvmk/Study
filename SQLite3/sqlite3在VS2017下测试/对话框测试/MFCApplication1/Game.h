#pragma once
#include "sqlite3.h"

class Game
{
public:

	Game();
	~Game();
	
	
	

public:
	
	void CreateDatabase();
	void SaveScore();

public:
	void GetAllUsers();

private:
	
	int			m_nScore;			// 得分
	
	sqlite3*	m_database;			// 数据库
};
