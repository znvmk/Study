fn main()
{
    use std::collections::HashMap;
    
    let mut scores = HashMap::new();

    scores.insert(String::from("Blue"),10);
    scores.insert(String::from("Yellow"),50);

    println!("scores:{:?}",scores);

    //vector转HashMap
    let teams = vec![String::from("Blue"),String::from("Yellow")];
    let initial_scores = vec![20,30];
    let scores:HashMap<_,_>=
        teams.iter().zip(initial_scores.iter()).collect();
    
    println!("scores:{:?}",scores);
    

    let mut scores = HashMap::new();

    for i in 0..10 //for i in (0..10).rev(),反转区间
    {
        println!("i:{}",i);
        let data = "data".to_owned() + &i.to_string();
        scores.insert(String::from(data),i);
    }

    println!("scores:{:?}",scores);

    let team_name = String::from("data2");
    let score = scores.get(&team_name);
    //let score = scores.get(&"data2".to_owned());
    //let score = scores.get(&"data2".to_string());
    println!("score:{:?}",score);

    println!("HashMap遍历");
    for (key,value) in &scores
    {
        println!("{}:{}",key,value);
    }

    //HashMap
    //条件插入,如果存在value“data11”则不作任何操作，如果不存在value”data11“，则插将该值key设置为50后插入集合
    scores.entry(String::from("data11")).or_insert(50);
    
    println!("HashMap遍历");
    for (key,value) in &scores
    {
        println!("{}:{}",key,value);
    }

   // scores.sort_by(|a,b| b.1.cmp(a.1));
   


}
