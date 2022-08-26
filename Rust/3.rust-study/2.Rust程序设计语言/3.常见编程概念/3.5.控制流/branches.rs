fn main() {
    //if,else if
    println!("\n if,else if.\n");

    let condition = true;
    let number = if condition { 6 } else { 5 }; //赋值语句 let中使用条件语句if

    if number < 5 {
        //此处条件必须是一个bool值，否则会报错
        println!("condition was true");
    } else {
        println!("condition was false");
    }

    if number % 4 == 0 {
        println!("number is divisible by 4");
    } else if number % 3 == 0 {
        println!("number is divisible by 3");
    } else if number % 2 == 0 {
        println!("number is divisible by 2");
    } else {
        println!("number is not divisible by 4,3 of 2");
    }

    //loop
    println!("\n loop.\n");

    let mut count = 0;
    'counting_up: loop {
        //循环标签
        println!("count={}", count);
        let mut remaining = 10;

        let resu = loop {
            //无循环标签
            println!("remaining={}", remaining);
            if remaining == 9 {
                break count;
            }
            if count == 2 {
                break 'counting_up;
            }
            remaining -= 1;
        }; //花括号不能表示语句结束，需要加“;”

        println!("The end result = {}", resu);
        count += 1;
    }
    println!("End count = {}", count);

    //while
    println!("\n while.\n");

    let mut wnumber = 3;

    while wnumber != 0 {
        println!("{}!", wnumber);
        wnumber -= 1;
    }
    println!("LIFTOFF!!!");

    println!("\n while 遍历集合中元素。");
    let a = [10, 20, 30, 40, 50];
    let mut index = 0;

    while index < 5 {
        println!("the value of array is:{},{}", index, a[index]);
        index += 1;
    }

    //for
    println!("\n for.\n");
    println!("for遍历集合中元素。");
    for element in a {
        println!("the value  of array is:{}", element);
    }

    println!("\n for循环倒计时");
    for count in (1..4).rev() {
        //区间左闭右开[)
        println!("{}!", count);
    }
    println!("LIFTOFF!!!");
}
