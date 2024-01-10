struct Solution {}

impl Solution {
    pub fn get_maximum_consecutive(coins: Vec<i32>) -> i32 {
        let mut ret_val = 1;

        let mut copy_coins = coins;
        copy_coins.sort();
        for coin in copy_coins {
            // Return the maximum number of consecutive integer values
            // that you can make with your coins starting from and including 0.
            if coin > ret_val {
                break;
            }
            ret_val += coin;
        }

        return ret_val;
    }
}

fn main() {
    struct Subject {
        coins: Vec<i32>,
    }
    let test_data = vec![
        Subject { coins: vec![1, 3] },
        Subject {
            coins: vec![1, 1, 1, 4],
        },
        Subject {
            coins: vec![1, 4, 10, 3, 1],
        },
        Subject {
            coins: vec![
                1, 89, 8, 1, 47, 34, 99, 1, 1, 1, 55, 89, 1, 52, 36, 1, 62, 1, 1, 1, 4, 27, 1, 45,
                1, 1, 48, 1, 94, 1, 63,
            ],
        },
        Subject {
            coins: vec![2, 3, 4],
        },
    ];

    for p in test_data {
        println!("Input: coins = {:?}", p.coins);

        let answer = Solution::get_maximum_consecutive(p.coins);
        println!("Output: {}", answer);

        println!();
    }
}
