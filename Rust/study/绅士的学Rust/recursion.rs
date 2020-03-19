fn rec(n: u64) -> u64 {    
    println!("{}",n);
    if n == 0 {
        1
    } else {
        n *  rec(n-1)
    }
//    println!("{}",n);
}

fn main(){
    let res=rec(10);
    println!("{}",res);
}
