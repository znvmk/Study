fn main()
{
    let mut s=String::from("hello world");
    
    let word_position= first_word_position(&s);//world的值为5
    
    println!("The first word end position of '{}' is : {}",s,word_position);

    let first_word = first_word(&s);

    println!("The first word of '{}' is : {}",s,first_word);

    let hello = &s[0..5];
    let world= &s[6..11];
    println!("{}",hello);
    println!("{}",world);

    let len=s.len();
    let slice = &s[3..len];
    let slice1 =&s[3..];
    let slice2 = &s[0..len];
    let slice3 = &s[..];
    println!("{},{},{},{}",slice,slice1,slice2,slice3);
    

    
    s.clear();
}

fn first_word_position(s:&String)->usize
{
    let bytes=s.as_bytes();
    for (i,&item) in bytes.iter().enumerate()
         {
             if item == b' '
             {
                 return i;
             }
         }
         s.len()
}

fn first_word(s:&String)->&str
{
    let bytes=s.as_bytes();
    for (i,&item) in bytes.iter().enumerate()
         {
             if item == b' '
             {
                 return &s[0..i];
             }
         }
    &s[..]
}
