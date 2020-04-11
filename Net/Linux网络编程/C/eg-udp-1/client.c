#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define PORT 1234 //这里的端口号要和服务器的端口号一样
#define MAXDATASIZE 100
int main(int argc, char const *argv[])
{
    int sockfd, num;
    char buf[MAXDATASIZE];
    struct hostent *he;
    struct sockaddr_in server, peer;
    socklen_t len;
    if (argc != 3) //检查用户的输入
    {
        printf("Usage: %s <IP Address><message>\n", argv[0]);
        exit(1);
    }
    if ((he = gethostbyname(argv[1])) == NULL)
    {
        printf("gethostbyname() error\n");
        exit(1);
    }
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
        //调用socket()函数产生套接字描述符
        printf("socket() error\n");
        exit(1);
    }
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr = *((struct in_addr *)he->h_addr); /*he->h_addr the first ip*/
    sendto(sockfd, argv[2], strlen(argv[2]), 0, (struct sockaddr *)&server, sizeof(server));
    //将用户从命令行输入的消息发送给服务器server
    len = sizeof(server);
    while(1)
    {
        if ((num = recvfrom(sockfd, buf, MAXDATASIZE, 0, (struct sockaddr *)&peer, &len)) == -1)
        //接收服务器发过来的字符串，并保存在buf中。接收的真正字节数被存储在num中，同时peer返回接收服务器的地址
        {
            printf("recvfrom() error\n");
            exit(1);
        }
        if (len!= sizeof(server) || memcmp((const void *)&server, (const void *)&peer, len) != 0)
        //由于UDP套接字是无连接的，它可能接收到其他服务器发来的信息，所以应判断信息是否来自于相应的服务器。
        //首先，比较recvfrom()函数调用后返回的地址长度len是否等于结构体server的长度。如果不是，则说明消息来自于其它服务器。
        //然后判断server和peer变量中的内容是否一致。如果一致，则说明收到的消息来自于相应的服务器。
        //注意，server和peer使用memcmp函数进行比较时，首先应转换成常量指针才能使用。
        {
            printf("Receive message from other server.\n");
            continue;
        }
        buf[num] = '\0';
        printf("Server Message: %s.\n", buf);//显示来自于服务器的信息
        break;
    }
    close(sockfd);
}