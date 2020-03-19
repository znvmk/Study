use std::thread;

fn main(){
    let t =thread::spawn(||{
        println!("hello");
    });

    println!("wait{:?}",t.join());
}
