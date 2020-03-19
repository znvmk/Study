func tex(){
	resp, err := http.Get(
		"http://www.zhenai.com/zhenghun")
	// 对错误的处理，go就是这么处理的不像其他的语言应try
	if err != nil{
		panic(err)
	}
	// 请求完成以后我们需要把这个流关上
	defer resp.Body.Close()
	// 如果请求不是200我们把状态码打出来
	if resp.StatusCode != http.StatusOK{
		fmt.Println("Error: Status code",
			resp.StatusCode)
		return
	}
	//将网页的utf-8转为gbk,解决乱码
	resbody :=mahonia.NewDecoder("gbk").NewReader(resp.Body)

	all, err := ioutil.ReadAll(resbody)
	if err != nil{
		panic(err)
	}
	fmt.Printf("%s\n", all)
}