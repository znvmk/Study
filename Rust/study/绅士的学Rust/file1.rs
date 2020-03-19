use std::env;
use std::fs::File;
use std::io::Read;

fn main(){
//    let first=env::args().nth(2).expect("please supply a filenae");
    let first="string2.rs";
    let mut file=File::open(&first).expect("can't open the file");
    let mut text=String::new();
    file.read_to_string(&mut text).expect("can not read the file");
    println!("file had {} bytes", text.len());
}
