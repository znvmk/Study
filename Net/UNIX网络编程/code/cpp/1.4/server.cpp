#include "../unp/unp.h"

int main(int argc, char* argv[])
{
    //创建套接字
    int listenfd,connectfd;
    socklen_t len;
    char buffer[MAXLINE];
    time_t ticks;

    listenfd = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);

    //将套接字和IP、端口绑定
    struct sockaddr_in6 serv_addr,cli_addr;
    //memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    bzero(&serv_addr,sizeof(serv_addr));
    
    serv_addr.sin6_family = AF_INET6;  //使用IPv6地址
    // serv_addr.sin_addr.s_addr = inet_addr("10.0.2.15");  //具体的IP地址
    // 获取当前主机IP地址
    serv_addr.sin6_addr = in6addr_any;
    //serv_addr.sin6_addr = inet_addr("206.168.112.219");  
    //具体的IP地址
    //ffff:ff00:ff:1001:ff11:fff:a0a:10a
    // serv_addr.sin6_addr.__in6_u.__u6_addr8[0] = 255;
    // serv_addr.sin6_addr.__in6_u.__u6_addr8[1] = 255;
    // serv_addr.sin6_addr.__in6_u.__u6_addr8[2] = 255;
    // serv_addr.sin6_addr.__in6_u.__u6_addr8[3] = 0;
    // serv_addr.sin6_addr.__in6_u.__u6_addr8[4] = 0;
    // serv_addr.sin6_addr.__in6_u.__u6_addr8[5] = 255;
    // serv_addr.sin6_addr.__in6_u.__u6_addr8[6] = 16;
    // serv_addr.sin6_addr.__in6_u.__u6_addr8[7] = 1;
    // serv_addr.sin6_addr.__in6_u.__u6_addr8[8] = 255;
    // serv_addr.sin6_addr.__in6_u.__u6_addr8[9] = 17;
    // serv_addr.sin6_addr.__in6_u.__u6_addr8[10] = 15;
    // serv_addr.sin6_addr.__in6_u.__u6_addr8[11] = 255;
    // serv_addr.sin6_addr.__in6_u.__u6_addr8[12] = 10;
    // serv_addr.sin6_addr.__in6_u.__u6_addr8[13] = 10;
    // serv_addr.sin6_addr.__in6_u.__u6_addr8[14] = 1;
    // serv_addr.sin6_addr.__in6_u.__u6_addr8[15] = 10;
    serv_addr.sin6_port = htons(1234);  //端口
    //bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    Bind(listenfd,(SA *)&serv_addr,sizeof(serv_addr));

    //进入监听状态，等待用户发起请求
    Listen(listenfd,LISTENQ);

    for(;;)
    {
        len =sizeof(cli_addr);

        //接收客户端请求
        connectfd =accept(listenfd,(SA *)&cli_addr,&len);
        printf("connection form %s,port %d\n",
               Inet_ntop(AF_INET6,&cli_addr.sin6_addr,buffer,sizeof(buffer))),
               ntohs(cli_addr.sin6_port);

        ticks = time(NULL);

        printf("connectfd : %d\n%.24s\r\n",connectfd,ctime(&ticks));
        char str[]="Hello world !\n";
        //int snprintf(char* str,size_t size,const char* format,...)
        //将可变参数"..."按照format的格式格式化为字符串，然后将其拷贝至str中
        snprintf(buffer,sizeof(buffer),"%s%.24s\r\n",str,ctime(&ticks));

        //向客户端发送准备好的数据
        write(connectfd,buffer,strlen(buffer));

        //关闭套接字
        close(connectfd);
    }

    return 0;
}
