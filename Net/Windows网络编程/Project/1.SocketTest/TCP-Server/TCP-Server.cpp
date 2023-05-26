#pragma comment(lib, "WS2_32")

#include <iostream>
#include <WinSock2.h>
#include <stdio.h>
#include <assert.h>

#define	PORT				4096			// 端口号
#define MAX_PACKET_SIZE		10240			// 数据包的最大长度,单位是sizeof(char)
char	g_szBuff[MAX_PACKET_SIZE + 1];

// 初始化socket库
bool InitSocket();
// 监听Client的消息
void ListenToClient();
// 解析消息进行相应的处理
bool ProcessMsg(SOCKET sClient);
// 关闭socket库
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
	// 初始化socket dll
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
	// 创建socket套接字
	SOCKET sListen = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == sListen)
	{
		printf("Init Socket Error!\n");
		return;
	}
	// 绑定socket到一个本地地址
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (::bind(sListen, (LPSOCKADDR)&sin, sizeof(sockaddr_in)) == SOCKET_ERROR)
	{
		printf("Bind Error!\n");
		return;
	}

	// 设置socket进入监听状态
	if (::listen(sListen, 10) == SOCKET_ERROR)
	{
		printf("Listen Error!\n");
		return;
	}
	printf("Listening To Client...\n");

	// 循环接收client端的连接请求
	sockaddr_in ClientAddr;
	int nAddrLen = sizeof(sockaddr_in);
	SOCKET sClient;

	while (INVALID_SOCKET == (sClient = ::accept(sListen, (sockaddr*)&ClientAddr, &nAddrLen)))
	{
	}

	while (true == ProcessMsg(sClient))
	{
	}

	// 关闭同客户端的连接
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
	// 释放winsock库
	::WSACleanup();

	return true;
}

// 把用户输入的数据传送到client端
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
