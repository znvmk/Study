fn main()
{
    let data="initial contents";

    let s = data.to_string();
    //let s = "initial contents".to_string();
    println!("to_string s:{}",s);
    
    let s1 = String::from(data);
    //let s1=String:;from("initial contents");
    println!("String::from s1:{}",s1);

    let s2 = String::from("UTF-8 编码测试");
    println!("utf-8 s2:{}",s2);

    let mut s3 =String::from("foo ");
    s3.push_str(&s);
    //追加字符串
    println!("s3 is:{}",s3);

    let s4 = s1 + &s2;//两个字符串相加只能使用String+&str，
                      //注意，此时s1被移动了，不能继续使用
    println!("{}",s4);

    let s10 =String::from("tic");
    let s20 =String::from("tac");
    let s30 =String::from("toe");

    let s5 = s10 + "-" + &s20 + "-" + &s30;
    println!("{}",s5);

    let s40 =String::from("tic");
    let s50 =String::from("tac");
    let s60 =String::from("toe");

    let s6 = format!("{}-{}-{}",s40,s50,s60);
    println!("{}",s6);

    //rust 字符串不支持索引，以下使用会报错
    //let s7 = s6[0];
    //println!("{}",s7);

    let hello = "你好";
    //let answer = &hello[0];//访问出错
    let answer = &hello.chars();
    let ano = &hello.chars().nth(0);//访问转化为字符串数组后的第零个元素
    let len = hello.len();
    println!("hello 0 is:{:?},length is:{},nth() is:{:?}",answer,len,ano);

    for c in "遍历字符串".chars()
    {
        println!("{}",c);
    }

    //输出原始字节
    //一个汉字三个字节
     for b in "遍历字符串".bytes()
    {
        println!("{}",b);
    }

}
