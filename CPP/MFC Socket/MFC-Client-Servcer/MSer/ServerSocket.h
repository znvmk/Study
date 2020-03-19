#pragma once
#include <afxsock.h>

#include "MSerDlg.h"

class CMSerDlg;                                      //别忘了加上   

class CServerSocket :
	public CSocket
{
public:
	CServerSocket();
	virtual ~CServerSocket();

public:

	CMSerDlg* m_pMSDlg;
public:
	virtual void OnReceive(int nErrorCode);

	virtual void OnClose(int nErrorCode);

	virtual void OnAccept(int nErrorCode);
};

