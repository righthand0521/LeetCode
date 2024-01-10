struct Solution {}

// #[cfg(clang)]
impl Solution {
    pub fn tribonacci(n: i32) -> i32 {
        let ret_val;

        // println!("clang");

        let mut vec = Vec::new();
        vec.push(0);
        vec.push(1);
        vec.push(1);
        for i in 3..n + 1 {
            vec.push(vec[(i - 1) as usize] + vec[(i - 2) as usize] + vec[(i - 3) as usize]);
        }

        ret_val = vec[n as usize];

        return ret_val;
    }
}
// https://leetcode.com/problems/n-th-tribonacci-number/solutions/1994145/
#[cfg(rust)]
impl Solution {
    pub fn tribonacci(n: i32) -> i32 {
        println!("rust");

        match n {
            0 => 0,
            1 | 2 => 1,
            _ => {
                let (_, _, c) = (3..=n).fold((0, 1, 1), |(a, b, c), _| (b, c, c + b + a));
                c
            }
        }
    }
}

fn main() {
    struct Subject {
        n: i32,
    }
    let test_data = vec![
        Subject { n: 4 },
        Subject { n: 25 },
        Subject { n: 5 },
        Subject { n: 6 },
        Subject { n: 7 },
        Subject { n: 8 },
        Subject { n: 9 },
        Subject { n: 0 },
        Subject { n: 1 },
        Subject { n: 2 },
        Subject { n: 37 },
    ];
    /* Example
     *  Input: n = 4
     *  Output: 4
     *
     *  Input: n = 25
     *  Output: 1389537
     */
    for p in &test_data {
        println!("Input: n = {}", p.n);

        let answer = Solution::tribonacci(p.n);
        println!("Output: {}", answer);

        println!();
    }
}
