fn main ()
{
    let s=String::from("hello");
    let len =calculate_length(&s);

    println!("The length of '{}' is {}.",s,len);

    //change(&s);//修改不可变引用的变量，出错无法修改。


    let mut s1=String::from("hello");

    println!("{}.",s1);

    change1(&mut s1);//可修改可边引用的变量

    println!("{}.",s1);

    let r1=&s1;
    let r2=&s1;
   // let r3=&mut s1;//不可同时时间创建一个变量的可变引用和不可变引用
   // let r3=&mut s1;//不可同一时间多次引用一个可变变量，只能创建一个
    
    println!("{},{}",r1,r2);
}

fn calculate_length(s:&String)->usize
{
    s.len()
}

//出错无法定义修改不可变引用函数
//fn change(some_string:&String)
//{
 //   some_string.push_str(",world");
//}

fn change1(some_string:&mut String)
{
    some_string.push_str(",world");
}
