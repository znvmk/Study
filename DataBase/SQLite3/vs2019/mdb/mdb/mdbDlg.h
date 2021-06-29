
// mdbDlg.h: 头文件
//

#pragma once
#include "Query.h"
#include "CFileRW.h"

// CmdbDlg 对话框
class CmdbDlg : public CDialogEx
{
	// 构造
public:
	CmdbDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MDB_DIALOG };
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
	afx_msg void OnBnClickedDisplay();
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedReset();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedSearch();

	DECLARE_MESSAGE_MAP()

public:
	CMenu m_Menu;
	// 显示查询表
	CListCtrl m_lcTable;


	Query Query;
	// 编号
	CString m_editID;
	// 编码
	CString m_editEncode;
	// 词条
	CString m_editEntry;
	//排序
	CString m_editSort;
	// 固顶
	CString m_editSetTop;
	// 词条所属数据表类别
	CComboBox m_comboClassify;

	CFileRW frw;

public:
	void ConnectDb();
	int ShowListContrl(CString tabledata);
	void SetStaticContrlText(int idc, CString text, int line = 0);


	afx_msg void OnBnClickedExport();
};
