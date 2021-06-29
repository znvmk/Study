
// GODlg.h : 头文件
//

#pragma once
#include"Resource.h"

#include"GOProcess.h"


// CGODlg 对话框
class CGODlg : public CDialogEx
{
// 构造
public:
	CGODlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//开始游戏
	afx_msg void OnBnClickedGamestart();
	afx_msg void OnBnClickedButtonResigns();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonPause();
public:
	CGOProcess m_gop;
	CPoint m_mlcp;

public:
	//画棋盘
	void DrawGOBoard(CDC* pDC);

	//画信息
	void DrawGOInformation(CDC* pDC);

	//落子
	void DropChessPieces(CPoint p);


	
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
