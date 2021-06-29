#include "../unp/unp.h"

int main(int argc, char* argv[])
{
    //创建套接字
    int listenfd,connectfd,i;
    char buffer[MAXLINE];
    time_t ticks;

    listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //将套接字和IP、端口绑定
    struct sockaddr_in serv_addr;
    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    // serv_addr.sin_addr.s_addr = inet_addr("10.0.2.15");  //具体的IP地址
    // 获取当前主机IP地址
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port = htons(1234);  //端口
    Bind(listenfd,(SA *)&serv_addr,sizeof(serv_addr));

    //进入监听状态，等待用户发起请求
    Listen(listenfd,LISTENQ);

    for(;;)
    {
        //接收客户端请求
        connectfd =accept(listenfd,(SA *)NULL,NULL);
        
        ticks = time(NULL);

        printf("connectfd : %d\n%.24s\r\n",connectfd,ctime(&ticks));
        char str[]="Hello world !\n";
        //int snprintf(char* str,size_t size,const char* format,...)
        //将可变参数"..."按照format的格式格式化为字符串，然后将其拷贝至str中
        snprintf(buffer,sizeof(buffer),"%s%.24s\r\n",str,ctime(&ticks));

        //向客户端发送准备好的数据
        //按每一个字符单独发送
        for(i=0;i<strlen(buffer);i++)
            write(connectfd,&buffer[i],1);

        //关闭套接字
        close(connectfd);
    }

    return 0;
}
