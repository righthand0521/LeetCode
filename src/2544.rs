struct Solution {}

impl Solution {
    pub fn alternate_digit_sum(n: i32) -> i32 {
        let mut ret_val: i32 = 0;

        let mut n: i32 = n;
        let mut reverse: i32 = 0;
        while n > 0 {
            reverse = reverse * 10 + n % 10;
            n = n / 10;
        }
        #[cfg(string_reverse)]
        {
            let n: String = format!("{:?}", n);
            let reverse: String = n.chars().rev().collect::<String>();
            let mut reverse: i32 = reverse.parse().unwrap();
        }

        let mut sign: i32 = 1;
        while reverse > 0 {
            ret_val = ret_val + (sign * (reverse % 10));
            sign = sign * (-1);
            reverse = reverse / 10;
        }

        return ret_val;
    }
}

fn main() {
    struct Subject {
        n: i32,
    }
    let test_data: Vec<Subject> = vec![
        Subject { n: 521 },
        Subject { n: 111 },
        Subject { n: 886996 },
        Subject { n: 10 },
    ];

    for p in test_data {
        println!("Input: n = {}", p.n);

        let answer: i32 = Solution::alternate_digit_sum(p.n);
        println!("Output: {}", answer);

        println!();
    }
}
