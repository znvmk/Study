#include "../unp/unp.h"
#include <string.h>

int main(int argc,char* argv[])
{
    //创建套接字
    int sockfd,n;
    char recvline[MAXLINE + 1];
    

    if(argc !=2)
        err_quit("usage:client.out <IP address>");
    if((sockfd = socket(AF_INET6, SOCK_STREAM, 0)) <0)
    {
        err_sys("socket error");
    }


    
    //向服务器（特定的IP和端口）发起请求
    struct sockaddr_in6 serv_addr;
    //bzero:设置字符串的前n个元素为0
    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin6_family = AF_INET6;  //使用IPv4地址
    serv_addr.sin6_port = htons(1234);  //端口


    //serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    //从输入的参数（argv[]数组第二个元素）获取IP地址，病判断是否为本地IP
    if(inet_pton(AF_INET6,argv[1],&serv_addr.sin6_addr) <=0)
        err_quit("inet_pton error for %s",argv[1]);

    
    while(1)
    {
        //sleep()秒级，usleep()微秒级
        //#include <iostream>
        //using namespace std;
        //#include<unistd.h>
        //int main(){
        //  while(1){
        //      cout<<"hello"<<endl;
        //      //sleep(1);
        //      usleep(100000);
        //  }
        //}
        
        //sleep(1);
        break;
    }
    //connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(connect(sockfd,(SA *)&serv_addr,sizeof(serv_addr)) <0)
        err_sys("connect error");

    //读取服务器传回的数据
    //char buffer[40];
    //read(sockfd, buffer, sizeof(buffer)-1);
    while((n=read(sockfd,recvline,MAXLINE)) >0)
    {
        recvline[n]=0;
        //fputs:将字符串写入到指定的stream流中
        if(fputs(recvline,stdout)==EOF)
            err_sys("fputs error");
    }
    if(n<0)
        err_sys("read error");
    
    //printf("来自服务器的消息: %s\n", buffer);
  
    //关闭套接字
    close(sockfd);
    

    return 0;
}
