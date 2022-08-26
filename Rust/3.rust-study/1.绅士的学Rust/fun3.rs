fn modi(x: &mut f64) {
    *x = 1.0;
}

fn main() {
    let mut res = 0.0;
    modi(&mut res);
    println!("res is {}", res);
}
