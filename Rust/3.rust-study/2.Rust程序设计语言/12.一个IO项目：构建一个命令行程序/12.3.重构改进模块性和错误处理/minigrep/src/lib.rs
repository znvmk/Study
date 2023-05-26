use std::error::Error;
use std::fs;

//使用参数配置
fn parse_config(args: &[String]) -> (&str, &str) {
    let query = &args[1];
    let filename = &args[2];

    (query, filename)
}

//参数配置改进
pub struct Config {
    pub query: String,
    pub filename: String,
}

//fn parse_config1(args:&[String])->Config{
//let query =&args[1].clone();
//let filename=&args[2].clone();

//Config{query,filename}
//}

//impl Config{
//fn new(args:&[String])->Config{
//if args.len()<3{
//panic!("not enough arguments");
//}
//let query =args[1].clone();
//let filename=args[2].clone();

//Config{query,filename}
//}
//}

impl Config {
    pub fn new(args: &[String]) -> Result<Config, &'static str> {
        if args.len() < 3 {
            return Err("not enough arguments");
        }
        let query = args[1].clone();
        let filename = args[2].clone();

        Ok(Config { query, filename })
    }
}

fn run(config: Config) {
    let contents =
        fs::read_to_string(config.filename).expect("Something weng wrong reading the file");

    println!("With text:\n{}", contents);
}

pub fn run1(config: Config) -> Result<(), Box<dyn Error>> {
    let contents = fs::read_to_string(config.filename)?;

    println!("With text:\n{}", contents);

    Ok(())
}
