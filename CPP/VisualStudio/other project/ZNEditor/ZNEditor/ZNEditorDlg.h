
// ZNEditorDlg.h: 头文件
//

#pragma once


// CZNEditorDlg 对话框
class CZNEditorDlg : public CDialogEx
{
// 构造
public:
	CZNEditorDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ZNEDITOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	CMenu m_Menu;
	CToolBar m_wndToolBar;
	CStatusBar m_Statusbar;

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
	afx_msg void OnHelpAbout();
	CEdit m_edit;
	afx_msg void OnMenuExit();
	CTreeCtrl m_tree;
	CFont m_editFont;
	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
