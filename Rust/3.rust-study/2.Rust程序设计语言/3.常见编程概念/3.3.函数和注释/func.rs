fn main() {
    println!("Hello,world!");

    another_function();
    //another_function(12);
    another_function_with_pqrameter(12, 'h');

    let y = {
        let x = 3;
        x + 1 //此处不可加“;”号，加了后会将花括号内的数值变成语句，导致y赋值失败，程序报错
    }; //注：此处必须加“;“号，花括号不能代替，分号表示结束
    println!("y:{:?}", y); //此处不可使用默认的格式化输出

    let f = five();
    println!("The return  value of function five() is:{}", f);
    let p = plus_one(5);
    println!("The return  value of function plus_one() is:{}", p);
}

fn another_function() {
    println!("Another function.");
}

//fn another_function(x: i32) {
//   println!("The value of parameter x is:{}", x);
//}
fn another_function_with_pqrameter(value: i32, unit_label: char) {
    println!("The value of parameter is:{},{}", value, unit_label);
}

//带有返回值的函数
fn five() -> i32 {
    5
}
fn plus_one(x: i32) -> i32 {
    x + 1 //注意：此处不可以加“;”，表示花括号内最终结果为一个数值，而不是一个语句，用来作返回值
          //单行注释
}
