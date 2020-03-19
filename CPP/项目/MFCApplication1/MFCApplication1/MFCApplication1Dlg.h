
// MFCApplication1Dlg.h : 头文件
//

#pragma once

#include"resource.h"
#include "afxwin.h"


// CMFCApplication1Dlg 对话框
class CMFCApplication1Dlg : public CDialogEx
{
	// 构造
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// 标准构造函数
	/*记录日志函数声明*/
	void WriteLog(CString message, CString title);

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
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

	/*改变编辑框内容函数声明*/
	afx_msg void OnChangeEditText();
	/*擦除编辑框内容函数声明*/
	afx_msg void OnErrspaceEditText();
	/*编辑框失去焦点函数声明*/
	afx_msg void OnKillfocusEditText();
	/*编辑框中内容达到最大值函数声明*/
	afx_msg void OnMaxtextEditText();
	/*设置编辑框焦点函数声明*/
	afx_msg void OnSetfocusEditText();
	/*更新编辑框函数声明*/
	afx_msg void OnUpdateEditText();
	/*水平滚动事件函数声明*/
	afx_msg void OnHscrollEditTestScroll();
	/*垂直滚动事件函数声明*/
	afx_msg void OnVscrollEditTestScroll();
	/*获取文本内容事件函数声明*/
	afx_msg void OnButtonGetEditText();
	/*设置文本内容事件函数声明*/
	afx_msg void OnButtonSetEditText();
	/*获取选择文本事件函数声明*/
	afx_msg void OnButtonGetLine();
	/*获取选择的文本内容事件函数声明*/
	afx_msg void OnButtonGetSel();
	/*设置选择的文本内容事件函数声明*/
	afx_msg void OnButtonSetSel();
	/*替换选择的文本内容事件函数声明*/
	afx_msg void OnButtonReplaceSel();
	/*静态控件测试事件函数声明*/
	afx_msg void OnStaticText();



	DECLARE_MESSAGE_MAP()
public:


	CEdit m_EditTest;
	CStatic m_staticLog;
	CEdit m_EditTestScroll;
};

/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/