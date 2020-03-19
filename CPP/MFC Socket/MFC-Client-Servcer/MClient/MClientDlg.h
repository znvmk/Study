
// MClientDlg.h: 头文件
//

#pragma once
#include "ClientSocket.h"
#define port 8000

// CMClientDlg 对话框
class CMClientDlg : public CDialogEx
{
// 构造
public:
	CMClientDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MCLIENT_DIALOG };
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
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonSendMessage();

	DECLARE_MESSAGE_MAP()
public:

	// 发送数据
	CString m_strSend;
	bool m_connect;
	CClientSocket* pSock;                        // 客户端套接字指针对象
	// 连接服务器
	CButton m_btnConSer;


public:
	BOOL WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen);

	//字符转换函数
	//virtual BOOL PreTranslateMessage(MSG* pMsg);

};
