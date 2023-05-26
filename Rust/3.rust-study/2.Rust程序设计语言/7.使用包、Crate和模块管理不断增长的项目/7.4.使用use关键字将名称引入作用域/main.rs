use rand:Rng;
use std::{cmp::Ordering,io}//嵌套路径来消除大量得use行

fn main()
{
    let secret_number =rand::thread_rng().gen_range(1...101);
    println!("{}",secret_number);
}
