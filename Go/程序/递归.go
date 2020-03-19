import "fmt"

func main() {
	var i int=15
	fmt.Printf("%d 的阶乘是：%d \n",i,Factorial(uint64 (i)))

	var j int
	for j=0;j<10;j++{
		fmt.Printf("%d\t",fibonacci(j))
	}

}
func Factorial(n uint64)(result uint64){
	if n>0{
		result=n *Factorial(n-1)
		return result
	}
	return 1
}
func fibonacci(n int)int{
	if n<2{
		return n
	}
	return  fibonacci(n-2)+fibonacci(n-1)
}