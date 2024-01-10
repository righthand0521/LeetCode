struct Solution {}

impl Solution {
    pub fn is_anagram(s: String, t: String) -> bool {
        let mut ret_val = false;

        let mut s_vector: Vec<char> = s.chars().collect();
        s_vector.sort_by(|a, b| b.cmp(a));

        let mut t_vector: Vec<char> = t.chars().collect();
        t_vector.sort_by(|a, b| b.cmp(a));

        if s_vector == t_vector {
            ret_val = true;
        }

        return ret_val;
    }
}

fn main() {
    struct Subject {
        s: String,
        t: String,
    }
    let test_data = vec![
        Subject {
            s: "anagram".to_string(),
            t: "nagaram".to_string(),
        },
        Subject {
            s: "rat".to_string(),
            t: "car".to_string(),
        },
    ];

    for p in test_data {
        println!("Input: s = \"{}\", t = \"{}\"", p.s, p.t);

        let answer = Solution::is_anagram(p.s, p.t);
        println!("Output: {}", answer);

        println!();
    }
}
