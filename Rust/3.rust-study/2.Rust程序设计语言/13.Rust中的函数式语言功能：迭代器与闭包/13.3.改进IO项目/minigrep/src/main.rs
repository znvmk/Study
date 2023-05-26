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
    let config = Config::new(env::args()).unwrap_or_else(|err| {
        println!("Problem parsing arugment:{}", err);
        process::exit(1);
    });

    println!("Searching for {}", config.query);
    println!("In file {}", config.filename);

    //错误检查
    if let Err(e) = minigrep::run(config) {
        eprintln!("Application error:{}", e);

        process::exit(1);
    }
}

//cargo run >output.txt
//报错:Problem parsing arguments:not enough arguments
//参数不够
//cargo run to poem.txt > output.txt
//在output.txt中输出程序运行结果
//结果不会显示在终端中
