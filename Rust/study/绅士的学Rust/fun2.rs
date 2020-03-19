fn ref1(x:&i32)->i32{
    x+1
}

fn main(){
    let i=10;
    let res1=ref1(&i);
    let res2=ref1(&41);
    println!("{} {}",res1,res2);
}
