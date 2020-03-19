// db001Dlg.h : header file
//

#if !defined(AFX_DB001DLG_H__7A9E7F60_6F55_40DE_8D6E_53A525D623A3__INCLUDED_)
#define AFX_DB001DLG_H__7A9E7F60_6F55_40DE_8D6E_53A525D623A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once

#include <afxdao.h>

#endif // _MSC_VER > 1000

#import "C:\Program Files\Common Files\System\ado\msado15.dll" rename_namespace("ADO") rename("EOF","adoEOF")
//#import "C:\Program Files\Common Files\System\ado\msadox.dll" //no_namespace("ADOX01") //rename("EOF","adoEOF")

/////////////////////////////////////////////////////////////////////////////
// CDb001Dlg dialog

class CDb001Dlg : public CDialog
{
// Construction
public:
	CDb001Dlg(CWnd* pParent = NULL);	// standard constructor

	CDaoDatabase m_db;//数据库


// Dialog Data
	//{{AFX_DATA(CDb001Dlg)
	enum { IDD = IDD_DB001_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDb001Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDb001Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonCratedb();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DB001DLG_H__7A9E7F60_6F55_40DE_8D6E_53A525D623A3__INCLUDED_)
