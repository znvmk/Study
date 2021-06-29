#pragma once
//#include "ServerSocket.h"

class CDataProcess
{
public:
	CDataProcess();
	virtual ~CDataProcess();

public:
	// 端口号
	UINT m_uiPort;
	// 用户数量
	UINT m_uiUserCount;
	
	//CServerSocket* listenSocket;     // 用于打开服务器

	CPtrList m_clientList;                 // 链表用于存储用户

	//bool m_connect;                       // 用于标记服务器状态
	// 广播
	//CString m_edit_csSend;

public:

    void AddClient();                       // 增加用户，响应用户请求

	//void RemoveClient(CServerSocket* pSocket);          // 移除下线的用户

//	void RecvData(CServerSocket* pSocket);                 // 获取数据

	void UpdateEvent(CString str);  // 更新事件日志
	void Broadcast();		//广播

	//字符转换
	BOOL WChar2MByte(LPCWSTR srcBuff, LPSTR destBuff, int nlen);        

	void SendMSG(CString str);       // 发送消息给各个客户端
	void ControlPC(CString AndroidControl);  // 手机控制PC的响应函数
	BOOL PreTranslateMessage(MSG* pMsg);

};

