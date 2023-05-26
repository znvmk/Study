#include <iostream>

#include <stdio.h>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll
#pragma warning(disable : 4996)

#define BUF_SIZE 100

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    //创建套接字，SOCK_DGRAM指明使用 UDP 协议
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);

    //绑定套接字
    sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));  //每个字节都用0填充
    servAddr.sin_family = PF_INET;  //使用IPv4地址
    //servAddr.sin_addr.s_addr = htonl(INADDR_ANY); //自动获取IP地址
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servAddr.sin_port = htons(8000);  //端口
    bind(sock, (SOCKADDR*)&servAddr, sizeof(SOCKADDR));

    //接收客户端请求
    SOCKADDR cliAddr;  //客户端地址信息
    int nSize = sizeof(SOCKADDR);
    char buff[BUF_SIZE];  //缓冲区
    while (1) {
        int strLen = recvfrom(sock, buff, BUF_SIZE, 0, &cliAddr, &nSize);
        //sendto(sock, buff, strLen, 0, &cliAddr, nSize);
        printf("\n receive data: \n");
        for (int i = 0; i < strLen; i++)
        {
            printf("%d ",buff[i]);
        }
        
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
