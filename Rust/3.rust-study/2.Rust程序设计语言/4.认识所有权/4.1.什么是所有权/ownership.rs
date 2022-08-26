fn main(){
    let s="hello whole";
    println!("s = {}",s);
    let sg=s;
    println!("sg=s= {}",sg);
    println!("此时，s不可在使用，rust认为s再没有作用，已经销毁");
    let sc=sg.clone();
    println!("如果还要使赋值后的原变量起作用，则需要使用克隆");
    println!("sc=sg.clone()= {}",sc);
    println!("sg= {}",sg);


    //作用域为整个文件
    {
        let s="hello inner s";
        println!("s = {}",s);
        //作用域到当前“}”结束
    }
    let s2=String::from("hello");
    println!("from s2= {}",s2);

    let mut s3=String::from("hello");
    s3.push_str(",world!");//追加字符
    println!("after add s3= {}",s3);

}

