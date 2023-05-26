use std::fmt::Display;

//&'a i32，带有显示生命周期得引用
//此处不声明显示生命周期会报错
//x和y必须同时用显示生命周期修饰，否则会有悬垂引用返回错误
fn longest<'a>(x: &'a str, y: &'a str) -> &'a str {
    if x.len() > y.len() {
        x
    } else {
        y
    }
}
#[derive(Debug)]
struct ImportantExcerpt<'a> {
    part: &'a str,
}

fn first_word(s: &str) -> &str {
    let bytes = s.as_bytes();

    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return &s[0..i];
        }
    }

    &s[..]
}

//结合泛型类型参数、trait bounds和生命周期
fn longest_with_an_announcement<'a, T>(x: &'a str, y: &'a str, ann: T) -> &'a str
where
    T: Display,
{
    println!("Announcement! {}", ann);
    if x.len() > y.len() {
        x
    } else {
        y
    }
}

fn main() {
    let mut r;
    {
        let x = 5;
        r = &x;
    }
    //    println!("r:{}", r);//x的生命周期只能在花括号内结束，此处运行报错
    //
    let x = 5;
    r = &x;
    println!("r:{}", r);
    //
    let string1 = String::from("abcd");
    let string2 = "xyz";

    let result = longest(string1.as_str(), string2);
    println!("The longest string is {}", result);
    //
    let novel = String::from("Call me Ishmael.Some years ago...");
    let first_sentence = novel.split('.').next().expect("Could not find a '.'");
    let i = ImportantExcerpt {
        part: first_sentence,
    };
    println!("{:?}", i);

    //静态生命周期
    //静态生命周期在二进制文件中总是可用的
    let s: &'static str = "I have a static lifetime.";
    println!("{}", s);
}
