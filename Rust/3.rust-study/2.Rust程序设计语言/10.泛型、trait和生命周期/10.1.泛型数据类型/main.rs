//寻找队列中最大值

fn largest_i32(list:&[i32])->i32
{
    let mut largest = list[0];

    for &item in list
    {
        if item > largest
        {
            largest = item;
        }
    }
    
    largest
}

fn largest_char(list:&[char])->char
{
    let mut largest = list[0];

    for &item in list
    {
        if item > largest
        {
            largest = item;
        }
    }
    
    largest
}

//fn largest<T>(list:&[T])->T
//{
    //let mut largest = list[0];

    //for &item in list
 //   {
        //if item > largest
  //      {
     //       largest = item;
   //     }
    //}
    
    //largest
//}

//结构体中定义泛型
struct Point<T>
{
    x:T,
    y:T,
}

//方法中使用泛型数据
impl<T>Point<T>
{
    fn x(&self) ->&T
    {
        &self.x
    }
}

impl Point<f32>//单独为f32类型的Point定义一种方法，其他类型不可使用
{
    fn distance_from_origin(&self)->f32
    {
        (self.x.powi(2)+self.y.powi(2)).sqrt()
    }
}

struct Pointx<T,U>
{
    x:T,
    y:U,
}

impl<T,U>Pointx<T,U>
{
    fn mixup<V,W>(self,other:Pointx<V,W>)->Pointx<T,U>
    {
        Pointx
        {
            x:self.x,
            y:self.y,
        }
    }
}

fn main()
{
    let number_list = vec![34,50,25,100,65];
    let largest = largest_i32(&number_list);
    println!("The largest number in vector is {}",largest);
    
    let char_list = vec!['y','m','a','q'];
    let largest = largest_char(&char_list);
    println!("The largest char in vector is {}",largest);

    //let largest = largest(&number_list);
    //println!("The largest number in vector is {}",largest);
    //

    let p=Point{x:5,y:10};
    println!("p.x={}",p.x());
 
    let p1=Pointx{x:5,y:10.4};
    let p2=Pointx{x:"Hello",y:'c'};

    let p3=p1.mixup(p2);
    println!("p3.x={},p3.y={}",p3.x,p3.y);
}
