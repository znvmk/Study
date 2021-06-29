#include "pch.h"
//#include "framework.h"
#include "AdoRecord.h"
//*
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


void dump_com_error(_com_error& e, CString strCue)
{
	if (strCue.IsEmpty())
		strCue = _T("SQLError");

#ifdef _DEBUG
	CString ErrorStr;
	_bstr_t bstrSource(e.Source());
	_bstr_t bstrDescription(e.Description());
	ErrorStr.Format(_T("CADORecordset Error\n\tCode = %08lx\n\tCode meaning = %s\n\tSource = %s\n\tDescription = %s\n"),
		e.Error(), e.ErrorMessage(), (LPCSTR)bstrSource, (LPCSTR)bstrDescription);

	::MessageBox(NULL, ErrorStr, strCue, MB_OK | MB_ICONWARNING);
#else
	::MessageBox(NULL, e.Description(), strCue, MB_OK | MB_ICONWARNING);
#endif
}
//*/

CAdoRecord::CAdoRecord()
{
	AfxOleInit();//初始化OLE/COM库环境
	//::CoInitialize(NULL);
	m_pConnection.CreateInstance(__uuidof(Connection));
}

CAdoRecord::~CAdoRecord()
{
	CloseDb();
}
//*

BOOL CAdoRecord::ConnectDb(CString strSQL)
{
	TRY_DBG
		if (m_pConnection->State)
			m_pConnection->Close();

	HRESULT hr;
	//CString strSQL;
	//两种都可以
	//strSQL = _T("Provider=SQLOLEDB;Server=(local);Database=udb;UID=sa;PWD=pw123");
	//strSQL = _T("Provider=SQLOLEDB;Server=CHEN-PC;Database=udb;UID=sa;PWD=pw123");
	//m_pConnection->ConnectionTimeout = 8;
	try
	{

		hr = m_pConnection->Open(_bstr_t(strSQL.GetBuffer(strSQL.GetLength())), _T(""), _T(""), adModeUnknown);
		if (FAILED(hr))
		{
			AfxMessageBox(_T("不能连接数据库!"));
			//return;
		}
		//else
			//AfxMessageBox(_T("连接数据库成功!"));
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());

		//return;
	}
	CATCH_DBG("CAdoRecord::ContentDataBase")
		return m_pConnection->State;
}

BOOL CAdoRecord::ConnectDb(CString strIP, int nPort, CString strDbName)
{
	CString strSQL;

	try
	{
		if (m_pConnection->State)
			m_pConnection->Close();


		switch (nPort)
		{

		case 1:strSQL.Format(_T("driver={MySQL ODBC 3.51 Driver};Server=%s;Port=%d;DATABASE=%s;"), strIP, nPort, strDbName);
			break;

		case 2:strSQL.Format(_T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;jet OleDB:Database Password=gzlongmakj"), strDbName);
			break;

		case 3:strSQL.Format(_T("Provider=OraOLEDB.Oracle.1;Password=longma;Persist Security Info=True;User ID=system;Data Source= '(DESCRIPTION =(ADDRESS_LIST =(ADDRESS = (PROTOCOL = TCP)(HOST =%s)(PORT = 1521)))(CONNECT_DATA  = (SID = chinaivf)))' "), strIP);
			break;

		case 4:strSQL.Format(_T("DRIVER={SQL Server};SERVER=%s;UID=sa;PWD=longma;DATABASE=ivfjinyangshijian"), strIP);
			break;
		default:
			break;
		}
		m_pConnection->Open(_bstr_t(strSQL.GetBuffer(strSQL.GetLength())), _T(""), _T(""), adModeUnknown);

	}
	catch (_com_error e)
	{

		strSQL.Format(_T("连接数据库失败:%s   错误代码: %d"), e.ErrorMessage(), e.HelpContext());
		AfxMessageBox(strSQL);
	}
	return m_pConnection->State;
}

BOOL CAdoRecord::ConnectDb(CString strIP, int nPort, CString strDbName, CString severSA)
{
	CString strSQL;

	try
	{
		if (m_pConnection->State)
			m_pConnection->Close();


		switch (nPort)
		{

		case 1:strSQL.Format(_T("driver={MySQL ODBC 3.51 Driver};Server=%s;Port=%d;DATABASE=%s;"), strIP, nPort, strDbName);
			break;

		case 2:strSQL.Format(_T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;jet OleDB:Database Password=gzlongmakj"), strDbName);
			break;

		case 3:strSQL.Format(_T("Provider=OraOLEDB.Oracle.1;Password=longma;Persist Security Info=True;User ID=system;Data Source= '(DESCRIPTION =(ADDRESS_LIST =(ADDRESS = (PROTOCOL = TCP)(HOST =%s)(PORT = 1521)))(CONNECT_DATA  = (SID = chinaivf)))' "), strIP);
			break;

		case 4:
			strSQL.Format(_T("DRIVER={SQL Server};SERVER=%s;UID=sa;PWD=longma%s;DATABASE=ivfjinyangshijian"), strIP, severSA.Left(14).Right(8));//1433.com
			break;

		default:
			break;
		}
		m_pConnection->Open(_bstr_t(strSQL.GetBuffer(strSQL.GetLength())), _T(""), _T(""), adModeUnknown);

	}
	catch (_com_error e)
	{

		strSQL.Format(_T("连接数据库失败:%s   错误代码: %d"), e.ErrorMessage(), e.HelpContext());
		AfxMessageBox(strSQL);
	}
	return m_pConnection->State;
}

BOOL CAdoRecord::IsConnectDb()
{
	int n = 0;
	if (m_pConnection)
	{
		if (m_pConnection->State)
		{
			return TRUE;
		}
	}
	return FALSE;
}

_RecordsetPtr CAdoRecord::Execute(CString strSQL)
{
	TRY_DBG

		ASSERT(!strSQL.IsEmpty());

	AfxGetApp()->BeginWaitCursor();
	return m_pConnection->Execute(_bstr_t(strSQL), NULL, adCmdText);
	AfxGetApp()->EndWaitCursor();

	CATCH_DBG("CAdoRecord::Execute")

		return NULL;
}

void CAdoRecord::CloseDb()
{
	TRY_DBG

		if (m_pConnection)
		{
			if (m_pConnection->State)
			{
				m_pConnection->Close();
			}

			m_pConnection.Release();
		}

	CATCH_DBG("CAdoRecord::CloseDb")
}

//*/

void CAdoRecord::test()
{
	//AfxOleInit();
	HRESULT hr;
	
	CString strSQL;
	//两种都可以
	//strSQL = _T("Provider=SQLOLEDB;Server=(local);Database=udb;UID=sa;PWD=pw123");
	strSQL = _T("Provider=SQLOLEDB;Server=CHEN-PC;Database=udb;UID=sa;PWD=pw123");
	//m_pConnection->ConnectionTimeout = 8;
	try
	{

		hr = m_pConnection->Open(_bstr_t(strSQL.GetBuffer(strSQL.GetLength())), _T(""), _T(""), adModeUnknown);
		if (FAILED(hr))
		{
			AfxMessageBox(_T("不能连接数据库!"));
			return;
		}
		else
			AfxMessageBox(_T("连接数据库成功!"));
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.ErrorMessage());

		return;
	}
}


/*
///////////////////根据配置文件信息进行选择使用连接数据库

	m_biao.fangan = "IVF";
	m_biao.ivfzhou = "IVF";
	m_pAdo = new CAdoRecord;
	CFileFind m_find;
	CString m_strmdb = m_strCurPath+"\\ivf.mdb";

	if (!m_find.FindFile(m_strmdb))
	{
		m_strmdb = "..//chinaivf//ivf.mdb";
	}
	int n_database;
	if (database == "access")
	{
		n_database = 2;
	}
	else if (database == "oracle")
	{
		n_database = 3;
	}
	else if (database == "SQLServer")
	{
		n_database = 4;
	}
	else
	{
		AfxMessageBox("未选择数据库");
		return FALSE;
	}

	if (!m_pAdo->ConnectDb(m_serverName, n_database, m_strmdb,severSA))
	{
		CFileDialog dlg1(TRUE, "", "*.mdb");
		if (dlg1.DoModal() != IDOK)
		{
			return FALSE;
		}
		CString strname = dlg1.GetPathName();
		if (!m_pAdo->ConnectDb(m_serverName, 2, strname))
		{
			return FALSE;
		}
	}
*/