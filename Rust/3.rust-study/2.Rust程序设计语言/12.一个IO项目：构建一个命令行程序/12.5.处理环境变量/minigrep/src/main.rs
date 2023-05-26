use minigrep::Config;
use std::env;
use std::process;

fn main() {
    println!("Hello, world!");

    let args: Vec<String> = env::args().collect();
    println!("{:?}", args);

    //trait
    //run with command: cargo run the poem.txt

    //Config::new调用并处理错误
    let config = Config::new(&args).unwrap_or_else(|err| {
        println!("Problem parsing arugment:{}", err);
        process::exit(1);
    });

    println!("Searching for {}", config.query);
    println!("In file {}", config.filename);

    //错误检查
    if let Err(e) = minigrep::run(config) {
        println!("Application error:{}", e);

        process::exit(1);
    }
}
