#pragma once
#include "afxwin.h"
#include"resource.h"

// CDialogControl 对话框

class CDialogControlBoard : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogControlBoard)

public:
	CDialogControlBoard(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogControlBoard();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CONTROL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()




protected:
	CStatic m_StaticDrawMessage;

protected:
	void ShowDrawMessage();



public:
	int m_nNumber;
	CString m_sNubmer;
	CEdit m_EditNumber;
	bool m_bShow;



public:



public:
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonMinus();
	afx_msg void OnBnClickedOk();
	
	afx_msg void OnBnClickedCancel();
	
	
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
