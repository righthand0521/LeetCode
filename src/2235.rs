struct Solution {}

impl Solution {
    pub fn sum(num1: i32, num2: i32) -> i32 {
        let ret_val = num1 + num2;

        return ret_val;
    }
}

fn main() {
    struct Subject {
        num1: i32,
        num2: i32,
    }
    let test_data = vec![
        Subject { num1: 12, num2: 5 },
        Subject { num1: -10, num2: 4 },
    ];
    for p in &test_data {
        println!("Input: num1 = {}, num2 = {}", p.num1, p.num2);

        let answer = Solution::sum(p.num1, p.num2);
        println!("Output: {}", answer);

        println!();
    }
}
