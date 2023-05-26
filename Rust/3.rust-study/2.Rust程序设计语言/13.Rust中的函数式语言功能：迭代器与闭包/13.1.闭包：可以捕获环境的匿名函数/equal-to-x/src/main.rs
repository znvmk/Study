fn main() {
    println!("Hello, world!");

    let x = 4;
    // let equal_to_x=|z| z==x;
    // 不能通过编译，
    //fn equal_to_x(z:i32)->bool{ z==x}

    let y = 4;

    let x = vec![1, 2, 3];
    let equal_to_x = move |z| z == x;
    //闭包函数move获取了'x'的所有权，下面println函数无法再使用
    //println!("cant't use x here:{:?}",x);

    let y = vec![1, 2, 3];

    assert!(equal_to_x(y));
}
