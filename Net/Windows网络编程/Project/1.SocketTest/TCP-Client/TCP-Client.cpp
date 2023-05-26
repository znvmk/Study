#pragma comment(lib, "WS2_32")

#include <iostream>
#include <WinSock2.h>
#include <stdio.h>
#include <assert.h>

#define MAX_PACKET_SIZE		10240			// ���ݰ�����󳤶�,��λ��sizeof(char)
#define	MAXFILEDIRLENGTH	256				// ����ļ�·������󳤶�
#define	PORT				4096			// �˿ں�
//#define SERVER_IP			"192.168.0.101"	// server�˵�IP��ַ
#define SERVER_IP			"127.0.0.1"	// server�˵�IP��ַ
SOCKET	g_sClient;
char	g_szBuff[MAX_PACKET_SIZE + 1];

// ��ʼ��socket��
bool InitSocket()
{
	printf("InitSocket() invoke begin\n");

	// ��ʼ��socket dll
	WSADATA wsaData;
	WORD socketVersion = MAKEWORD(2, 2);
	if (::WSAStartup(socketVersion, &wsaData) != 0)
	{
		printf("Init socket dll error\n");
		exit(-1);
	}
	printf("InitSocket() invoke end return true \n");
	return true;
}

// ��server�����ӽ��д���
bool ConectToServer()
{
	// ��ʼ��socket�׽���
	if (SOCKET_ERROR == (g_sClient = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)))
	{
		printf("Init Socket Error!\n");
		exit(-1);
	}
	sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(PORT);
	servAddr.sin_addr.S_un.S_addr = ::inet_addr(SERVER_IP);
	if (INVALID_SOCKET == (::connect(g_sClient, (sockaddr*)&servAddr, sizeof(sockaddr_in))))
	{
		printf("Connect to Server Error!\n");
		exit(-1);
	}
	// �������ݴ��䵽server��
	while (true == SendDataToServer())
	{
	}

	// ����server�˴���������Ϣ,ֱ�������ļ��ɹ�Ϊֹ
	while (true == ProcessMsg())
	{
	}

	return true;
}
// �ر�socket��
bool CloseSocket()
{
	// �ر��׽���
	::closesocket(g_sClient);
	// �ͷ�winsock��
	::WSACleanup();

	return true;
}
// ���û���������ݴ��͵�server��
bool SendDataToServer()
{
	char Data[MAXFILEDIRLENGTH];
	printf("Input the Data: \n");

	fgets(Data, MAXFILEDIRLENGTH, stdin);

	for (int i = 0; i < MAXFILEDIRLENGTH; i++)
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
// ����server�˴��͹�������Ϣ
bool ProcessMsg()
{
	int nRecv = ::recv(g_sClient, g_szBuff, MAX_PACKET_SIZE + 1, 0);

	for (int i = 0; i < 64; i++)
	{
		printf("%d ", g_szBuff[i]);
	}
	printf("\n");

	return true;
}


int main()
{
	InitSocket();

	while (1)
	{
		ConectToServer();
	}

	CloseSocket();

	return 0;
}

