use minigrep::Config;
use std::env;
use std::process;

fn main() {
    println!("Hello, world!");

    let args: Vec<String> = env::args().collect();
    println!("{:?}", args);

    //run with command: cargo run test sample.txt
    //    let query = &args[1];
    //    let filename = &args[2];

    //使用参数配置
    //    let (query,filename)=parse_config(&args);
    //println!("Searching for {}", query);
    //println!("In file {}", filename);

    //参数配置改进
    //引用出错，
    //let config =parse_config1(&args);

    //trait
    //run with command: cargo run the poem.txt
    //let config=Config::new(&args);

    //Config::new调用并处理错误
    let config = Config::new(&args).unwrap_or_else(|err| {
        println!("Problem parsing arugment:{}", err);
        process::exit(1);
    });

    println!("Searching for {}", config.query);
    println!("In file {}", config.filename);

    //    let contents = fs::read_to_string(config.filename).expect("Something went wrong reading the file.");
    //   println!("With text:\n{}", contents);
    //改用函数
    //      run(config);

    //错误检查
    if let Err(e) = minigrep::run1(config) {
        println!("Application error:{}", e);

        process::exit(1);
    }
}
