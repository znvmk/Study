//寻找队列中最大值
fn main()
{
    let number_list = vec![34,50,25,100,65];

    let mut largest =number_list[0];

    for number in number_list
    {
        if number >largest
        {
            largest = number;
        }
    }

    println!("The largest number in vector is {}",largest);

}
