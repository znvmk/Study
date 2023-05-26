#pragma comment(lib, "WS2_32")

#include <iostream>
#include <WinSock2.h>
#include <stdio.h>
#include <assert.h>

#define MAX_PACKET_SIZE		10240			// 数据包的最大长度,单位是sizeof(char)
#define	MAXFILEDIRLENGTH	256				// 存放文件路径的最大长度
#define	PORT				4096			// 端口号
//#define SERVER_IP			"192.168.0.101"	// server端的IP地址
#define SERVER_IP			"127.0.0.1"	// server端的IP地址
SOCKET	g_sClient;
char	g_szBuff[MAX_PACKET_SIZE + 1];

// 初始化socket库
bool InitSocket()
{
	printf("InitSocket() invoke begin\n");

	// 初始化socket dll
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

// 与server端连接进行传输
bool ConectToServer()
{
	// 初始化socket套接字
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
	// 输入数据传输到server端
	while (true == SendDataToServer())
	{
	}

	// 接收server端传过来的信息,直到保存文件成功为止
	while (true == ProcessMsg())
	{
	}

	return true;
}
// 关闭socket库
bool CloseSocket()
{
	// 关闭套接字
	::closesocket(g_sClient);
	// 释放winsock库
	::WSACleanup();

	return true;
}
// 把用户输入的数据传送到server端
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
// 处理server端传送过来的消息
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

