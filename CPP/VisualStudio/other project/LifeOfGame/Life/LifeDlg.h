
// LifeDlg.h: 头文件
//

#pragma once
#include"DataProcessor.h"

// CLifeDlg 对话框
class CLifeDlg : public CDialogEx
{
// 构造
public:
	CLifeDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIFE_DIALOG };
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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonSetting();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonPause();
	afx_msg void OnBnClickedButtonOver();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonMinus();
	afx_msg void OnBnClickedButtonQuit();
	DECLARE_MESSAGE_MAP()


	

public:
	//CPoint m_plbt;
	bool m_bset;
	bool m_bpause;
	//负速度
	int m_ispeed,tempSpeed;

public:
	CDataProcessor m_dp;


public:
	void DrawBoard(CDC* pDC);

	//画信息
	void DrawInformation(CDC* pDC);
	
	//画方块
	void DrawDiamonds(CDC* pDC);

	//设置life
	void SettingPut(CPoint p);
	//设置life
	void SettingCancel(CPoint p);
public:
};
