#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h> //通用套接字地址结构
#include <netinet/in.h> //IPv4套接字地址结构
#include <arpa/inet.h> //IP地址转换函数
#include <string.h>
#include <stdlib.h>

#define PORT 1234 //客户端与服务器的端口要对应
#define BACKLOG 1//listen函数中的参数，此参数规定了请求队列中的最大连接个数，由于本例不是并发服务器，所以最大允许连接的数量BACKLOG定义为1

main()
{
    int listenfd, connectfd/*已连接套接字描述符*/;
    struct sockaddr_in server;//套接字地址结构
    struct sockaddr_in client;
    socklen_t addrlen; 

    /*Create TCP socket*/
    if ((listenfd=socket(AF_INET, SOCK_STREAM, 0)) == -1) 
    //创建TCP套接字,socket()函数第二个参数为字节流接口。如果出错打印错误信息。
    {
        perror("socket() error.");
        exit(-1);
    }

    int opt = SO_REUSEADDR;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    //以上两行设置套接字选项SO_REUSEADDR，即地址重用选项。
    //由于系统默认是只允许一个套接字绑定一个特定的协议地址上，并且当该套接字关闭后，系统仍不允许在该地址上绑定其他套接字。
    //如果去掉这两行，程序运行时产生的错误信息为:"Bind() error:Address already in use"

    bzero(&server, sizeof(server));//初始化server套接字地址结构，初始值为0
    server.sin_family = AF_INET;//为套接字地址结构中的成员赋值
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(listenfd, (struct sockaddr *)&server, sizeof(server)) == -1)
    //调用bind()函数将套接字描述符与server套接字地址结构中的协议地址绑定
    {
        perror("bind() eror");
        exit(1);
    }

    if (listen(listenfd, BACKLOG) == -1) //listen()函数将listenfd描述符设置为监听套接字，等待客户连接
    {
        perror("listen() error.\n");
        exit(1);
    }

    addrlen = sizeof(client);//得到client当前的长度
    if ((connectfd = accept(listenfd, (struct sockaddr *)&client, &addrlen)) == -1)
    //接受客户端连接，将客户的地址信息存放在client地址结构中，&addrlen为内核写入client结构体中的准确字节数
    {
        perror("accept() error\n");
        exit(1);
    }
    printf("You got a connection from client's ip is %s, port is %d\n", inet_ntoa(client.sin_addr), htons(client.sin_port));
    //显示客户的IP地址和端口号，通过inet_ntoa()函数将IP地址转换成可显示的ASCII串，通过htons()函数将端口号转换成网络字节序
    send(connectfd, "Welcome\n",8,0);//发送Welcome字符串给客户端
    close(connectfd);//先关闭已连接套接字，再关闭监听套接字
    close(listenfd);
    return 0;
}