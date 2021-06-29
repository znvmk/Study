
// MClientDlg.h: 头文件
//

#pragma once
#include "ClientSocket.h"
//#define port 8000

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
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	DECLARE_MESSAGE_MAP()
public:
	// 服务端端口号
	UINT port;
	// 消息日志
	CEdit m_edit_log;

	// 发送数据
	CString m_strSend;
	//接收消息
	CString m_strReceive;
	bool m_connect;
	CClientSocket* pSock;                        // 客户端套接字指针对象
	// 连接服务器
	CButton m_btnConSer;
	CString csConnectCode = _T("ConnectCode:000000");
	CString csSendCode= _T("SendCode:000000");


public:
	void UpdateEvent(CString str);
	BOOL WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen);
	int nSendMessage(CString message);
	void setReceiveMessage(int nErrorCode);
	//字符转换函数
	//virtual BOOL PreTranslateMessage(MSG* pMsg);

	
};
