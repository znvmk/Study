#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>

#define PORT 1234 //服务器的端口与客户端的端口对等
#define MAXDATASIZE 100 //这里的缓冲区采用静态方式分配

int main(int argc, char *argv[])
{
    int sockfd, num;
    char buf[MAXDATASIZE];
    struct hostent *he;
    struct sockaddr_in server;
    if (argc != 2) //检查用户的输入。如果用户输入不正确，提示用户正确的输入方式
    {
        printf("Usage:%s <IP Address>\n", argv[0]);
        exit(1);
    }

    //通过用户输入的点分十进制形式的IP地址，获得服务器的相关地址信息
    if ((he = gethostbyname(argv[1])) == NULL)
    {
        printf("gethostbyname() error\n");
        exit(1);
    }

    //调用socket()函数产生套接字描述符
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("socket() error\n");
        exit(1);
    }

    //初始化服务器的地址结构，并为地址结构的成员赋值
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr = *((struct in_addr *)he->h_addr);

    //调用connect()函数连接到服务器server
    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        printf("connect() error\n");
        exit(1);
    }

    //接受服务器发过来的字符串，并保存在buf中。接收的真正字节数被存储在num中
    if ((num = recv(sockfd, buf, MAXDATASIZE,0)) == -1)
    {
        printf("recv() error\n");
        exit(1);
    }
    buf[num-1] = '\0'; //以\0标志字符串的结束
    printf("server message: %s\n", buf);//显示从服务器接收到的buf中的信息
    close(sockfd); //关闭套接字
}