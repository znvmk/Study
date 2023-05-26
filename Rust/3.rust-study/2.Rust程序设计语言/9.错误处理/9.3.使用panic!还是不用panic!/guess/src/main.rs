#[derive(Debug)]
pub struct Guess{
    value:i32,
}

impl Guess{
    pub fn new(value:i32)->Guess{
        if value <1||value>100{
            panic!("Guess value must be between 1 and 100,got {}.",value);
        }

        Guess{
            value
        }
    }

    pub fn value(&self)->i32{
        self.value}
}

fn main() {
    println!("Hello, world!");

    let g1=Guess{value:101,};
    println!("{:?}",g1);

    let g2=Guess{value:10,};
    println!("{:?}",g2);

    let g3=Guess::new(111);
    println!("{:?}",g3);

}
