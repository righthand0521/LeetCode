struct Solution {}

const COUNT_SIZE: usize = 26; // s1 and s2 consist of lowercase English letters.
impl Solution {
    pub fn check_inclusion(s1: String, s2: String) -> bool {
        let mut ret_val = false;

        let len1 = s1.len();
        let len2 = s2.len();
        if len2 < len1 {
            return ret_val;
        }

        let mut count1: [usize; COUNT_SIZE] = [0; COUNT_SIZE];
        let mut count2: [usize; COUNT_SIZE] = [0; COUNT_SIZE];

        for i in 0..len1 {
            count1[(s1.chars().nth(i).unwrap() as u8 - b'a') as usize] += 1;
            count2[(s2.chars().nth(i).unwrap() as u8 - b'a') as usize] += 1;
        }
        if count1 == count2 {
            ret_val = true;
            return ret_val;
        }

        for i in len1..len2 {
            count2[(s2.chars().nth(i).unwrap() as u8 - b'a') as usize] += 1;
            count2[(s2.chars().nth(i - len1).unwrap() as u8 - b'a') as usize] -= 1;
            if count1 == count2 {
                ret_val = true;
                break;
            }
        }

        return ret_val;
    }
}

fn main() {
    struct Subject {
        s1: String,
        s2: String,
    }
    let test_data = vec![
        Subject {
            s1: "ab".to_string(),
            s2: "eidbaooo".to_string(),
        },
        Subject {
            s1: "ab".to_string(),
            s2: "eidboaoo".to_string(),
        },
    ];

    for p in test_data {
        println!("Input: s1 = \"{}\", s2 = \"{}\"", p.s1, p.s2);

        let answer = Solution::check_inclusion(p.s1, p.s2);
        println!("Output: \"{}\"", answer);

        println!();
    }
}
