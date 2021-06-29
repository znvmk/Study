
// AdoEgDlg.h: 头文件
//

#pragma once
#include "AdoRecord.h"


// CAdoEgDlg 对话框
class CAdoEgDlg : public CDialogEx
{
// 构造
public:
	CAdoEgDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADOEG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

public:
	CAdoRecord m_AdoR;

public:
	CString m_strnId;
	CString m_strName;
	CString m_strScore;
	CListCtrl m_StuList;

public:
	void QureyGet(CString strSQL);

public:
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonQurey();
	afx_msg void OnBnClickedButtonModify();
	
	
	afx_msg void OnBnClickedButtonShowall();
};
