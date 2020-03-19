package main

import "fmt"

func main() {
	x,y,z :=sort(15,9,24)
	fmt.Print(x,">",y,">",z)
}
func sort(x,y,z int )(int,int,int){
	if x<y{
		swap(&x,&y)
	}
	if x<z{
		swap(&x,&z)
	}
	if y<z{
		swap(&y,&z)
	}
	return x,y,z
}
func swap(x,y *int){
	temp :=0;
	temp=*x
	*x=*y
	*y=temp

}