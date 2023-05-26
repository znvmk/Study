//pub trait Summary
//{
    //fn summarize(&self) ->String;
//}

 
//带默认实现
pub trait Summary
{
    fn summarize_author(&self) ->String
    {

        format!("(Learn more ...)")
    }


    fn summarize(&self) ->String
    {
        format!("(Read more {}...)",self.summarize_author())
    }
}


pub struct NewsArticle
{
    pub headline:String,
    pub location:String,
    pub author:String,
    pub content:String,
}

impl Summary for NewsArticle
{
    fn summarize_author(&self)->String
    {
        format!("@{}",self.author)
    }
    fn summarize(&self)->String
    {
        format!("{},by {} ({})",self.headline,self.author,self.location)
    }
}

pub struct NewsArticle1
{
    pub headline:String,
    pub location:String,
    pub author:String,
    pub content:String,
}

impl Summary for NewsArticle1
{
   
}


pub struct Tweet
{
    pub username:String,
    pub content:String,
    pub reply:bool,
    pub retweet:bool,
}

impl Summary for Tweet
{
    fn summarize_author(&self)->String
    {
        format!("@{}",self.username)
    }

    fn summarize(&self)->String
    {
        format!("{}:{}",self.username,self.content)
    }
}

fn main()
{
    let tweet =Tweet{
        username:String::from("horse_ebooks"),
        content:String::from("of course,as you probaly already know,people"),
        reply:false,
        retweet:false,
    };
    
    println!("1 new tweet:{}",tweet.summarize());


    let article = NewsArticle
    {
        headline:String::from("Penguins win the Stanley cup Championship!"),
        location:String::from("Pittsburgh,PA,USA"),
        author:String::from("Iceburgh"),
        content:String::from("The Pittsubgh Penguins once agin are the best hockey team in the NHL."),
    };
    println!("New article availabel!{}",article.summarize());
    
    let article1 = NewsArticle1
    {
        headline:String::from("Penguins win the Stanley cup Championship!"),
        location:String::from("Pittsburgh,PA,USA"),
        author:String::from("Iceburgh"),
     content:String::from("The Pittsubgh Penguins once agin are the best hockey team in the NHL."),
    };
    println!("New article availabel!{}",article1.summarize());

}
