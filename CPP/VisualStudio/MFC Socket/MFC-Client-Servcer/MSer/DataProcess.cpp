#include "pch.h"
#include "DataProcess.h"

CDataProcess::CDataProcess()
{
	
	m_uiPort = 8000;
	m_uiUserCount = 0;
}

CDataProcess::~CDataProcess()
{
}

void CDataProcess::AddClient()
{
}

//void CDataProcess::RemoveClient(CServerSocket* pSocket)



//void CDataProcess::RecvData(CServerSocket* pSocket)



void CDataProcess::UpdateEvent(CString str)
{
}

void CDataProcess::Broadcast()
{
}

BOOL CDataProcess::WChar2MByte(LPCWSTR srcBuff, LPSTR destBuff, int nlen)

{	int n = 0;
	n = WideCharToMultiByte(CP_OEMCP, 0, srcBuff, -1, destBuff, 0, 0, FALSE);
	if (n < nlen)return FALSE;
	WideCharToMultiByte(CP_OEMCP, 0, srcBuff, -1, destBuff, nlen, 0, FALSE);
	return TRUE;
}

void CDataProcess::SendMSG(CString str)
{
}

void CDataProcess::ControlPC(CString AndroidControl)
{
}

BOOL CDataProcess::PreTranslateMessage(MSG* pMsg)
{
	return 0;
}
