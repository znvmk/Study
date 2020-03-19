
// MFCApplication1Dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"


// CMFCApplication1Dlg 对话框
class CMFCApplication1Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// 标准构造函数

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

	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR , LRESULT *pResult);
	afx_msg void OnTvnGetInfoTipTree1(NMHDR *pNMHDR , LRESULT *pResult);

	DECLARE_MESSAGE_MAP()

public:
	CTreeCtrl m_tcTestTree;
	CImageList m_imageList;
	CListCtrl m_lcTestList;

public:
	void InitTreeCtrl();
	void InitListCtrl();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR , LRESULT *pResult);
};
