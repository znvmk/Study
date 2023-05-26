package main

import(
	"fmt"
	"time"
)

func say(s string){
	for i :=0;i<5;i++{
		time.Sleep(1000 * time.Millisecond)
		fmt.Println(s)
	}
}

func sum(s []int,c chan int){ //通道
	sum :=0
	for _,v := range s{
		sum +=v
	}
	c <-sum //把sum发送到通道c
	//关闭通道：close(c)
}

func main(){
	go say("word")
	say("hello")
	
	s :=[]int{7,2,8,-9,4,0}
	c :=make(chan int)
	go sum(s[:len(s)/2],c)
	go sum(s[len(s)/2:],c)
	x,y :=<-c,<-c //从通道c中接收
	
	fmt.Println(x,y,x+y)

	//因为ch是带缓冲的通道，可以同时发送两个数据，而不用立刻使用
	ch :=make(chan int,2)

	ch<-1
	ch<-2
	
	fmt.Println(<-ch)
	fmt.Println(<-ch)

}
