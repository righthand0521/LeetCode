struct Solution {}

const COUNT_SIZE: usize = 26; // s and p consist of lowercase English letters.
impl Solution {
    pub fn find_anagrams(s: String, p: String) -> Vec<i32> {
        let mut ret_val = vec![];

        let len_s = s.len();
        let len_p = p.len();
        if len_s < len_p {
            return ret_val;
        }

        let mut count_s: [usize; COUNT_SIZE] = [0; COUNT_SIZE];
        let mut count_p: [usize; COUNT_SIZE] = [0; COUNT_SIZE];

        for i in 0..len_p {
            count_s[(s.chars().nth(i).unwrap() as u8 - b'a') as usize] += 1;
            count_p[(p.chars().nth(i).unwrap() as u8 - b'a') as usize] += 1;
        }
        if count_s == count_p {
            ret_val.push(0);
        }

        for i in len_p..len_s {
            count_s[(s.chars().nth(i).unwrap() as u8 - b'a') as usize] += 1;
            count_s[(s.chars().nth(i - len_p).unwrap() as u8 - b'a') as usize] -= 1;
            if count_s == count_p {
                ret_val.push(i as i32 - len_p as i32 + 1);
            }
        }

        return ret_val;
    }
}

fn main() {
    struct Subject {
        s: String,
        p: String,
    }
    let test_data = vec![
        Subject {
            s: "cbaebabacd".to_string(),
            p: "abc".to_string(),
        },
        Subject {
            s: "abab".to_string(),
            p: "ab".to_string(),
        },
    ];

    for p in test_data {
        println!("Input: s = \"{}\", p = \"{}\"", p.s, p.p);

        let answer = Solution::find_anagrams(p.s, p.p);
        println!("Output: \"{:?}\"", answer);

        println!();
    }
}
