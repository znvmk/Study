
// MSerDlg.h: 头文件
//

#pragma once
#include "ServerSocket.h"
#include "DataProcess.h"

const int MAX_MESSAGE_DATA_RECIVE = 10240;

class CServerSocket;

// CMSerDlg 对话框
class CMSerDlg : public CDialogEx
{
// 构造
public:
	CMSerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MSER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

public:
	//数据处理中心
	CDataProcess m_DP;
	// 端口号
	UINT m_uiPort;
	CEdit m_edit_log;
	// 用户数量
	UINT m_uiUserCount;
	
	CServerSocket* listenSocket;     // 用于打开服务器

	//CPtrList m_clientList;                 // 链表用于存储用户

	bool m_connect;                       // 用于标记服务器状态
	// 广播
	CString m_edit_csSend;

	CString csConnectCode = _T("ConnectCode:000000");
	CString csSendCode= _T("SendCode:000000");


public:

    void AddClient();                       // 增加用户，响应用户请求

	void RemoveClient(CServerSocket* pSocket);          // 移除下线的用户

	void RecvData(CServerSocket* pSocket);                 // 获取数据

	void UpdateEvent(CString str);  // 更新事件日志
	void Broadcast();		//广播


	void SendMSG(CString str);       // 发送消息给各个客户端
	void ControlPC(CString AndroidControl);  // 手机控制PC的响应函数
	BOOL PreTranslateMessage(MSG* pMsg);
public:
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	DECLARE_MESSAGE_MAP()
	

	
	
};
