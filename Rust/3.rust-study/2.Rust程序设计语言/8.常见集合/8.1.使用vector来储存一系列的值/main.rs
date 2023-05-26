fn main()
{

    let v:Vec<i32> = Vec::new();

    let v=vec![1,2,3,4];
    println!("v is {:?}",v);
    
    let mut v1=Vec::new();
    v1.push(5);
    v1.push(6);
    v1.push(7);
    v1.push(8);

    println!("v1 is {:?}",v1);

    let third: &i32=&v[2];
    println!("third is {}",third);
    //第二种访问方法
    match v.get(2)
    {
        Some(third1) => println!("The third1 is {}",third1),
        None =>println!("Threr is no third1."),
    }
    let first = &v[0];
    println!("first of v is {}",first);

    //遍历vector中的元素

    println!("runt of v1 is:");
    //遍历打印
    for i in &v1
    {
        println!("{}",i);
    }

    //遍历改变
    for i in &mut v1
    {
        *i +=10;
    }

    println!("v1 after changed:");
    //遍历打印
    for i in &v1
    {
        println!("{}",i);
    }
}
