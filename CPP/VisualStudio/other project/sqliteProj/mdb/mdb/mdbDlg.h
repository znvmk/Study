
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
	afx_msg void OnBnClickedExport();

	DECLARE_MESSAGE_MAP()

public:
	CMenu m_Menu;
	// 显示查询表
	CListCtrl m_lcTable;


	Query Query;
	// 编号
	CEdit m_editID;
	// 编码
	CEdit m_editEncode;
	// 词条
	CEdit m_editEntry;
	//排序
	CEdit m_editSort;
	// 固顶
	CEdit m_editSetTop;
	// 词条所属数据表类别
	CComboBox m_comboClassify;

	//获取词条内容
	CString  m_csId, m_csEncode, m_csEntry, m_csSort, m_csSetTop, m_csClassify;
	
	//转换为int类型
	int  m_iId, m_iSort, m_iSetTop, m_iClassify;

	//词库查询结果集
	CString m_csRecordSet;

	CFileRW frw;

public:
	void ConnectDb();
	int ShowListContrl(CString tabledata);
	void SetStaticContrlText(int idc, CString text, int line = 0);
	void getEditText();

	
	
};
