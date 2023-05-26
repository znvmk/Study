use std::rc::Rc;

//enum List{
//Cons(i32,Box<List>),
//Nil,
//}

enum List {
    Cons(i32, Rc<List>),
    Nil,
}

use crate::List::{Cons, Nil};

fn main() {
    println!("Hello, world!");

    // let a = Cons(5,
    //Box::new(Cons(10,
    //Box::new(Nil))));

    //let b =Cons(3,Box::new(a));
    //a的权限在创建b的时候已经被移动到了b，不能c再次使用
    //let c= Cons(4,Box::new(a));

    let a = Rc::new(Cons(5, Rc::new(Cons(10, Rc::new(Nil)))));

    let b = Cons(3, Rc::clone(&a));
    //a的权限在创建b的时候已经被移动到了b，不能c再次使用
    let c = Cons(4, Rc::clone(&a));
}
