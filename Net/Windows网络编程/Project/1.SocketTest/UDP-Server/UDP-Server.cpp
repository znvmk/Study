#include <iostream>

#include <stdio.h>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")  //���� ws2_32.dll
#pragma warning(disable : 4996)

#define BUF_SIZE 100

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    //�����׽��֣�SOCK_DGRAMָ��ʹ�� UDP Э��
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);

    //���׽���
    sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));  //ÿ���ֽڶ���0���
    servAddr.sin_family = PF_INET;  //ʹ��IPv4��ַ
    //servAddr.sin_addr.s_addr = htonl(INADDR_ANY); //�Զ���ȡIP��ַ
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servAddr.sin_port = htons(8000);  //�˿�
    bind(sock, (SOCKADDR*)&servAddr, sizeof(SOCKADDR));

    //���տͻ�������
    SOCKADDR cliAddr;  //�ͻ��˵�ַ��Ϣ
    int nSize = sizeof(SOCKADDR);
    char buff[BUF_SIZE];  //������
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
