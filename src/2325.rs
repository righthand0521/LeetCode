struct Solution {}

use std::collections::HashMap;
impl Solution {
    pub fn decode_message(key: String, message: String) -> String {
        let mut ret_val = String::new();

        let mut hash_map = HashMap::new();
        let mut hash_map_use = 0;
        for c in key.chars() {
            if hash_map_use == 26 {
                break;
            }

            if c == ' ' || hash_map.contains_key(&c) == true {
                continue;
            }

            hash_map.insert(c, (b'a' + hash_map_use) as char);
            hash_map_use += 1;
        }

        for c in message.chars() {
            if c == ' ' {
                ret_val.push(c);
                continue;
            }

            if hash_map.contains_key(&c) {
                ret_val.push(hash_map[&c]);
            }
        }

        return ret_val;
    }
}

fn main() {
    struct Subject {
        key: String,
        message: String,
    }
    let test_data = vec![
        Subject {
            key: "the quick brown fox jumps over the lazy dog".to_string(),
            message: "vkbs bs t suepuv".to_string(),
        },
        Subject {
            key: "eljuxhpwnyrdgtqkviszcfmabo".to_string(),
            message: "zwx hnfx lqantp mnoeius ycgk vcnjrdb".to_string(),
        },
    ];

    for p in test_data {
        println!("Input: key = \"{}\", message = \"{}\"", p.key, p.message);

        let answer = Solution::decode_message(p.key, p.message);
        println!("Output: \"{}\"", answer);

        println!();
    }
}
