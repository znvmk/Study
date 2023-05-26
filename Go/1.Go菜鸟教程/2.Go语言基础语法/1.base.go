package main

import(
	"fmt"
)

func main(){
	var stockcode=123
	var enddate="2020-12-13"
	var url="Code=%d&endDate=%s \n"
	fmt.Printf(url,stockcode,enddate)

	var a string ="Runoob"
	fmt.Println(a);

	var b,c int =1,2
	fmt.Println(b,c)
	
	var intVal int
//	intVal :=1 //这时候会产生编译错误，因为有声明新的变量，“:="是一个声明语句

	fmt.Println(intVal)

var countryCapitalMap map[string]string /*创建集合 */
    countryCapitalMap = make(map[string]string)

    /* map插入key - value对,各个国家对应的首都 */
    countryCapitalMap [ "France" ] = "巴黎"
    countryCapitalMap [ "Italy" ] = "罗马"
    countryCapitalMap [ "Japan" ] = "东京"
    countryCapitalMap [ "India" ] = "新德里"

    /*使用键输出地图值 */
    for country := range countryCapitalMap {
        fmt.Println(country, "首都是", countryCapitalMap [country])
    }

    /*查看元素在集合中是否存在 */
    capital, ok := countryCapitalMap [ "American" ] /*如果确定是真实的,则存在,否则不存在 */
    /*fmt.Println(capital) */
    /*fmt.Println(ok) */
    if (ok) {
        fmt.Println("American 的首都是", capital)
    } else {
        fmt.Println("American 的首都不存在")
    }

	/*删除元素*/
	delete(countryCapitalMap,"France")
	fmt.Println("法国条目被删除")
	fmt.Println("删除后地图")

	    /*使用键输出地图值 */
    	for country := range countryCapitalMap {
       		 fmt.Println(country, "首都是", countryCapitalMap [country])
    	}


	


}
