#include <iostream>

#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")  //���� ws2_32.dll
#pragma warning(disable : 4996)

#define BUF_SIZE 100

int main() {
    //��ʼ��DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    //�����׽���
    SOCKET sock = socket(PF_INET, SOCK_DGRAM, 0);

    //��������ַ��Ϣ
    sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));  //ÿ���ֽڶ���0���
    servAddr.sin_family = PF_INET;
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //servAddr.sin_addr.s_addr = inet_addr("196.168.0.12");
    //servAddr.sin_addr.s_addr = htons1(INADDR_ANY);
    servAddr.sin_port = htons(8000);

    //���ϻ�ȡ�û����벢���͸���������Ȼ����ܷ���������
    sockaddr fromAddr;
    int addrLen = sizeof(fromAddr);
    while (1)
    {
        char buff[BUF_SIZE] = { 0 };
        printf("Input a string: ");
        gets_s(buff);
        sendto(sock, buff, strlen(buff), 0, (struct sockaddr*)&servAddr, sizeof(servAddr));
     }
    closesocket(sock);
    WSACleanup();
    return 0;
}

