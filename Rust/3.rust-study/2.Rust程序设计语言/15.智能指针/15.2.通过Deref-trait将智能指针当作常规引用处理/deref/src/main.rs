use std::ops::Deref;

//自定义智能指针box
struct MyBox<T>(T);

impl<T> Deref for MyBox<T> {
    type Target = T;

    fn deref(&self) -> &T {
        &self.0
    }
}

fn hello(name: &str) {
    println!("Hello,{}!", name);
}

fn main() {
    println!("Hello, world!");

    let x = 5;
    let y = &x;

    assert_eq!(5, x);
    //assert_eq!(5,y);//错误，数字的引用与数字是不同类型，不不能比较
    assert_eq!(5, *y);

    let z = Box::new(x); //像引用一样使用Box

    assert_eq!(5, x);
    assert_eq!(5, *z);

    let a = MyBox::new(String::from("Rust"));
    hello(&a);
}
