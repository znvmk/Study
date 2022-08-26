fn dump(s: &str) {
    println!("str '{}'", s);
}

fn main() {
    let text = "hello dolly";
    let s = text.to_string();

    dump(text);
    dump(&s);
}
