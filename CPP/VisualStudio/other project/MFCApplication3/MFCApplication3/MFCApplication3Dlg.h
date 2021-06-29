
// MFCApplication3Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "MySQLOperate.h"
#include "DlgLogin.h"



// CMFCApplication3Dlg 对话框
class CMFCApplication3Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication3Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;




public:
	CMySQLOperate sql;
	CDlgLogin lg;
	


public:
	CEdit m_EditOutPut;
	CListBox m_ListBox;
	CListCtrl m_ListCtrl;
	CEdit m_EditLableName;





	/*自定义的函数*/
public:
	bool login();

	
	
	
	// 生成的消息映射函数
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()






};
