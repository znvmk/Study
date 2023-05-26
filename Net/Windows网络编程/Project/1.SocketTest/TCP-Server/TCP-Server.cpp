#pragma comment(lib, "WS2_32")

#include <iostream>
#include <WinSock2.h>
#include <stdio.h>
#include <assert.h>

#define	PORT				4096			// �˿ں�
#define MAX_PACKET_SIZE		10240			// ���ݰ�����󳤶�,��λ��sizeof(char)
char	g_szBuff[MAX_PACKET_SIZE + 1];

// ��ʼ��socket��
bool InitSocket();
// ����Client����Ϣ
void ListenToClient();
// ������Ϣ������Ӧ�Ĵ���
bool ProcessMsg(SOCKET sClient);
// �ر�socket��
bool CloseSocket();

int main()
{
	InitSocket();
	while (1) {
		ListenToClient();
	}
	CloseSocket();

	return 0;
}

bool InitSocket()
{
	// ��ʼ��socket dll
	WSADATA wsaData;
	WORD socketVersion = MAKEWORD(2, 2);
	if (::WSAStartup(socketVersion, &wsaData) != 0)
	{
		printf("Init socket dll error\n");
		return false;
	}

	return true;
}

void ListenToClient()
{
	// ����socket�׽���
	SOCKET sListen = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == sListen)
	{
		printf("Init Socket Error!\n");
		return;
	}
	// ��socket��һ�����ص�ַ
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (::bind(sListen, (LPSOCKADDR)&sin, sizeof(sockaddr_in)) == SOCKET_ERROR)
	{
		printf("Bind Error!\n");
		return;
	}

	// ����socket�������״̬
	if (::listen(sListen, 10) == SOCKET_ERROR)
	{
		printf("Listen Error!\n");
		return;
	}
	printf("Listening To Client...\n");

	// ѭ������client�˵���������
	sockaddr_in ClientAddr;
	int nAddrLen = sizeof(sockaddr_in);
	SOCKET sClient;

	while (INVALID_SOCKET == (sClient = ::accept(sListen, (sockaddr*)&ClientAddr, &nAddrLen)))
	{
	}

	while (true == ProcessMsg(sClient))
	{
	}

	// �ر�ͬ�ͻ��˵�����
	::closesocket(sClient);
	::closesocket(sListen);
}

bool ProcessMsg(SOCKET sClient)
{
	int nRecv = ::recv(sClient, g_szBuff, MAX_PACKET_SIZE + 1, 0);
	printf("Receive Data :\n");
	for (int i = 0; i < 64; i++)
	{
		printf("%x ",g_szBuff[i]);
	}
	return true;
}

bool CloseSocket()
{
	// �ͷ�winsock��
	::WSACleanup();

	return true;
}

// ���û���������ݴ��͵�client��
bool SendDataToClient()
{
	SOCKET	g_sClient;
	char Data[64];
	printf("Input the Data: \n");

	fgets(Data, 64, stdin);

	for (int i = 0; i < 64; i++)
	{
		Data[i] = Data[i] - 48;
	}

	if (SOCKET_ERROR == ::send(g_sClient, (char*)(&Data), 256, 0))
	{
		printf("Send Data Error!\n");
		exit(-1);
	}

	return true;
}
