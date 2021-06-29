#pragma once
#include "framework.h"


#if !defined(AFX_ADORECORD_H__A50CA0C3_68F2_4B71_B055_D7A9E1AADDA2__INCLUDED_)
#define AFX_ADORECORD_H__A50CA0C3_68F2_4B71_B055_D7A9E1AADDA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


void dump_com_error(_com_error& e, CString strCue);

#define TRY_DBG	try {
#define CATCH_DBG(sCaption) }\
	catch(_com_error e) { \
	AfxMessageBox(e.Description());\
}



class CAdoRecord
{
public:
	CAdoRecord();
	virtual~CAdoRecord();

public:
	_ConnectionPtr m_pConnection;//连接access数据库的链接对象  
	_RecordsetPtr m_pRecordset;//结果集对象

public:
	BOOL    ConnectDb(CString strAllinOne);
	BOOL	ConnectDb(CString strIP, int nPort, CString strDbName);
	BOOL	ConnectDb(CString strIP, int nPort, CString strDbName, CString severSA);
	BOOL	IsConnectDb();
	_RecordsetPtr Execute(CString strSql);
	void	CloseDb();


	
public:
	void test();
};


#endif // !defined(AFX_ADORECORD_H__A50CA0C3_68F2_4B71_B055_D7A9E1AADDA2__INCLUDED_)