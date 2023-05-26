pub fn add(left: usize, right: usize) -> usize {
    left + right
}

struct Rectangle {
    width: u32,
    height: u32,
}

impl Rectangle {
    fn can_hold(&self, other: &Rectangle) -> bool {
        self.width > other.width && self.height > other.height
    }
}

pub fn greeting(name: &str) -> String {
    format!("Hello {}", name)
}

pub struct Guess {
    value: i32,
}

impl Guess {
    pub fn new(value: i32) -> Guess {
        if value < 1 || value > 100 {
            panic!("Guess value must be between 1 and 100,got {}.", value);
        }

        Guess { value }
    }
}

//显示函数输出
fn prints_and_returns_10(a: i32) -> i32 {
    println!("I got the value {}", a);
    10
}

#[cfg(test)]
mod tests {
    use super::*; //global全局导入，以便在tests模块中使用所有在外部模块定义的内容

    #[test]
    fn it_works() {
        let result = add(2, 2);
        assert_eq!(result, 4);
    }
    #[test] //增加一个测试
    fn exploration() {
        let result = add(2, 2);
        assert_eq!(result, 4);
    }
    #[test] //增加一个失败的测试
    fn wrong_test() {
        let result = add(2, 2);
        assert_eq!(result, 5);
    }

    #[test] //另一个失败的测试
    fn another_wront_test() {
        panic!("Make thist test fail");
    }

    #[test]
    fn larger_can_hold_smaller() {
        let larger = Rectangle {
            width: 8,
            height: 7,
        };
        let smaller = Rectangle {
            width: 5,
            height: 1,
        };

        //使用assert!宏来检查结果
        assert!(larger.can_hold(&smaller));
    }
    #[test]
    fn larger_can_hold_smaller1() {
        let larger = Rectangle {
            width: 8,
            height: 7,
        };
        let smaller = Rectangle {
            width: 9,
            height: 1,
        };

        //使用assert!宏来检查结果
        assert!(larger.can_hold(&smaller));
    }

    #[test]
    fn greeting_contains_name() {
        let result = greeting("Caro1"); //结果是否包含单词“Carol"，不包含测试不通过
                                        //assert!(result.contains("Carol"));
        assert!(
            result.contains("Carol"),
            "Greeting did not contain name,value was '{}'",
            result
        );
    }

    //should_panic测试
    #[test]
    #[should_panic(expected = "Guess value must be less than or equal to 100")]
    fn gteater_than_100() {
        Guess::new(200);
    }

    //将Result<T,E>用于测试
    #[test]
    fn it_works1() -> Result<(), String> {
        let result = add(2, 2);
        if result == 4 {
            Ok(())
        } else {
            Err(String::from("two plus two does not equl four"))
        }
    }

    #[test]
    fn this_test_will_pass() {
        let value = prints_and_returns_10(4);
        assert_eq!(10, value);
    }
    #[test]
    fn this_test_will_fail() {
        let value = prints_and_returns_10(8);
        assert_eq!(5, value);
    }
}

//不同模块测试
#[cfg(test)]
mod tests1 {
    use super::*; //global全局导入，以便在tests模块中使用所有在外部模块定义的内容

    #[test]
    fn this_test_will_pass() {
        let value = prints_and_returns_10(4);
        assert_eq!(10, value);
    }
    #[test]
    fn this_test_will_fail() {
        let value = prints_and_returns_10(8);
        assert_eq!(5, value);
    }
}
