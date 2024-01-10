struct Solution {}

// #[cfg(clang)]
impl Solution {
    pub fn count_asterisks(s: String) -> i32 {
        let mut ret_val = 0;

        // println!("clang");

        let mut vertical_bars = 0;
        for c in s.chars() {
            if c == '|' {
                vertical_bars += 1;
                continue;
            }

            if vertical_bars % 2 == 1 {
                continue;
            }

            if c == '*' {
                ret_val += 1;
            }
        }

        return ret_val;
    }
}
// https://leetcode.com/problems/count-asterisks/solutions/2895643/rust-one-liner-on-iterators/
// #[cfg(not(clang))]
#[cfg(rust1)]
impl Solution {
    pub fn count_asterisks(s: String) -> i32 {
        println!("rust1");

        s.split("|")
            .step_by(2)
            .map(|str| str.chars().filter(|c| c == &'*').count() as i32)
            .sum::<i32>()
    }
}
// https://leetcode.com/problems/count-asterisks/solutions/2200493/rust-one-liner/
// #[cfg(not(clang))]
#[cfg(rust2)]
impl Solution {
    pub fn count_asterisks(s: String) -> i32 {
        println!("rust2");

        s.split('|')
            .enumerate()
            .filter_map(|(i, s)| if i % 2 == 0 { Some(s.chars()) } else { None })
            .flatten()
            .filter(|&c| c == '*')
            .count() as _
    }
}

fn main() {
    struct Subject {
        s: String,
    }
    let test_data = vec![
        Subject {
            s: "l|*e*et|c**o|*de|".to_string(),
        },
        Subject {
            s: "iamprogrammer".to_string(),
        },
        Subject {
            s: "yo|uar|e**|b|e***au|tifu|l".to_string(),
        },
    ];
    for p in &test_data {
        println!("Input: s = \"{}\"", p.s);

        let answer = Solution::count_asterisks(p.s.to_string());
        println!("Output: {}", answer);

        println!();
    }
}
