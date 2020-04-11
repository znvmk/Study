#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORT 1234 //定义端口号
#define MAXDATASIZE 100 //定义接收缓冲区大小
main()
{
    int sockfd;
    struct sockaddr_in server;
    struct sockaddr_in client;
    socklen_t len;
    int num;
    char buf[MAXDATASIZE];
    /*creating UDP socket*/
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {//调用socket函数，产生UDP套接字。如果出错打印错误信息。
        perror("Creating socket failed.");
        exit(1);
    }
    bzero(&server, sizeof(server));//初始化server套接字地址结构，并对地址结构中的成员赋值
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {//将套接字和指定的协议地址绑定
        perror("Bind() error.");
        exit(1);
    }
    len = sizeof(client);
    while(1)
    {
        num = recvfrom(sockfd, buf, MAXDATASIZE, 0, (struct sockaddr *)&client, &len);
        //接收客户端的信息，并存放在buf中，客户端的地址信息存放在client地址结构中。如果成功num返回接收的字符串的长度。
        if (num < 0)
        {
            perror("recvfrom() error\n");
            exit(1);
        }
        buf[num]='\0';
        printf("You got a message <%s> from client.\nIt's ip is %s, port is %d.\n", buf, inet_ntoa(client.sin_addr), htons(client.sin_port));
        //显示接收到的客户信息、客户的IP地址和端口号。通过inet_ntoa()函数将IP地址转换成可显示的ASCII串，通过htons()函数将端口号转换成网络字节序
        sendto(sockfd, "Welcome\n", 8, 0, (struct sockaddr *)&client, len);//发送Welcome字符串给客户端
        if (!strcmp(buf, "bye")) //如果客户端发来的字符串是"bye"，则退出循环
        {
            break;
        }
    }
    close(sockfd);
}