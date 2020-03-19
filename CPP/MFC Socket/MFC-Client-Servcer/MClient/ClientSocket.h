#pragma once
#include<afxsock.h>

class CClientSocket:public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();

public:
	void OnRecevie(int nErrorCode);
	//·µ»Ø´íÎó´úÂë
	int SendMSG(LPSTR lpBuffer, int nLen);
};

