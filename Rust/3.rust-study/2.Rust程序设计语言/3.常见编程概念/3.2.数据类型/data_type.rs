fn main() {
    let x = 2.0;
    let y: f32 = 3.0;
    let sum = 5 + 10;
    let difference = 95.5 - 4.3;
    let product = 4 * 30;
    let quotient = 56.7 / 32.2;
    let floored = 2 / 3;
    let femainder = 43 % 5;

    println!(
        "result:{},{},{},{},{},{},{},{}",
        x, y, sum, difference, product, quotient, floored, femainder
    );

    let t = true;
    let f: bool = false;
    let c = 'z';
    let z = 'z';

    println!("result:{},{},{},{}", t, f, c, z);

    let tup = (500, 6.4, 1);
    let (x, y, z) = tup;
    println!("y:{}", y);

    let x: (i32, f64, u8) = (500, 6.4, 1);
    let five_hundred = x.0;
    let six_point_four = x.1;
    let one = x.2;
    println!(
        "five_hundred:{},six_point_four:{},one:{}",
        five_hundred, six_point_four, one
    );
}
