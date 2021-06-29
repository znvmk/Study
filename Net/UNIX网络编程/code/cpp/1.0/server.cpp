#include "../unp/unp.h"

int main(int argc, char* argv[])
{
    //创建套接字
    int listenfd,connectfd;
    char buffer[MAXLINE];
    time_t ticks;

    listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //将套接字和IP、端口绑定
    struct sockaddr_in serv_addr;
    //memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    bzero(&serv_addr,sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    // serv_addr.sin_addr.s_addr = inet_addr("10.0.2.15");  //具体的IP地址
    // 获取当前主机IP地址
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port = htons(1234);  //端口
    //bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    Bind(listenfd,(SA *)&serv_addr,sizeof(serv_addr));

    //进入监听状态，等待用户发起请求
    Listen(listenfd,LISTENQ);

    for(;;)
    {
        ticks = time(NULL);

        //接收客户端请求
        connectfd =accept(listenfd,(SA *)NULL,NULL);
        printf("connectfd:%d\n%.24s\r\n",connectfd,ctime(&ticks));


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
