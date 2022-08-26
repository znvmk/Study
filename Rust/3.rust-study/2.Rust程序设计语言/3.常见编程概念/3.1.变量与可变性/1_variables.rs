fn main() {
    let x = 5;
    println!("The value of x is:{}", x);
    let x = x + 1;
    println!("The value of x after let x=x+1 is:{}", x);
    {
        let x = x * 2;
        println!("在花括号内局部使用 let x=x*2 is:{}", x);
    }
    println!(
        "花括号内局部使用 let x=x*2 后，在外部重新打印x,结果恢复到操作前:{}",
        x
    );

    println!("x=6;该语句报错，使用let单独声名变量，可以改变数值但不可再次赋值");
    let mut y = 6; //声明可变
    println!("The value of y is:{}", y);
    y = 7; //let mut可变
    println!("The value of y after changed is:{}", y);

    const THREE_HOURS_IN_SECONDS: u32 = 60 * 60 * 3;
    let tosec: u32 = THREE_HOURS_IN_SECONDS;

    println!("输出const 常量 THREE_HOURS_IN_SECONDS:{}", tosec);
}
