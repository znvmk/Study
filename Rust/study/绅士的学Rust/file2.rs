//use std::env;
use std::fs::File;
use std::io::Read;
use std::io;

fn read_to_string(filename:&str)-> Result<String,io::Error>{
    let mut file=match File::open(&filename){
        Ok(f)=>f,
        Err(e)=>return Err(e),
    };
    let mut text=String::new();
    match file.read_to_string(&mut text){
        Ok(_)=>Ok(text),
        Err(e)=>Err(e),
    }
}

fn main(){
    //let file=env::args().nth(1).expect("Plase supply a filename");
    let file="file1.rs";
    let text=read_to_string(&file).expect("bad file man!");
    
    println!("file had{} bytes",text.len());
    println!("file:{}",text);
}
