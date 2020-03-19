#pragma once
#include "pch.h"
#include "ServerSocket.h"
CServerSocket::CServerSocket()
{

}
CServerSocket::~CServerSocket()
{

}

void CServerSocket::OnReceive(int nErrorCode)

{

    m_pMSDlg->RecvData(this);                           // 接收数据

    CSocket::OnReceive(nErrorCode);

}

void CServerSocket::OnClose(int nErrorCode)

{

    m_pMSDlg->RemoveClient(this);                   // 删除下线用户

    CSocket::OnClose(nErrorCode);

}

void CServerSocket::OnAccept(int nErrorCode)

{

    m_pMSDlg->AddClient();                                  //添加上线用户

    CSocket::OnAccept(nErrorCode);

}
