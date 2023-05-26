struct User
{
    active:bool,
    username:String,
    email:String,
    sign_in_count:u64,
}

struct Color(i32,i32,i32);
struct Point(i32,i32,i32);

fn main()
{
    let user1 = User{
        email:String::from("someone@example.com"),
        username:String::from("someonename123"),
        active:true,
        sign_in_count:1,
    };
    println!("{}",user1.email);
    
    
    let mut user2 = User{
        email:user1.email,
        username:String::from("someonename123"),
        active:true,
        sign_in_count:1,
    };
    println!("{}",user2.email);

    user2.email = String::from("another@example.com");
    println!("{}",user2.email);

    //let user3=user1;//报错，
    let user3=user2;


    let black = Color(0,0,0);
    let origin = Point(0,0,0);

    //println!("{},{}",black,origin);
}
