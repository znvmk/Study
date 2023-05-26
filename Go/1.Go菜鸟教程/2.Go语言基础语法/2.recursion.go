package main 

import "fmt"

func Factorial(n uint64)uint64{
	if(n>0){
		return n * Factorial(n-1)
		}
	return 1
}

func fibonacci(n int)int{
	if n<2{
		return n
 	}	
	return fibonacci(n-2)+fibonacci(n-1)
}

func main(){
	var i int = 15
	fmt.Printf("%d 的阶乘是 %d\n",i,Factorial(uint64(i)))

	for i=0;i<10;i++{
		fmt.Printf("%d\t",fibonacci(i))
	}
}
