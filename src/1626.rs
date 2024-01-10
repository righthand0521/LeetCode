struct Solution {}

// https://leetcode.com/problems/best-team-with-no-conflicts/solutions/3120917/rust-dp-solution/
use std::cmp;
impl Solution {
    pub fn best_team_score(scores: Vec<i32>, ages: Vec<i32>) -> i32 {
        let mut ret_val = 0;

        let len = scores.len();

        let mut player: Vec<(i32, i32)> = ages.into_iter().zip(scores.into_iter()).collect();
        player.sort_by(|a, b| {
            if a.0 == b.0 {
                a.1.cmp(&b.1)
            } else {
                a.0.cmp(&b.0)
            }
        });

        let mut dp = vec![0; len];
        for i in 0..len {
            dp[i] = player[i].1;
            for j in 0..i {
                if player[j].1 <= player[i].1 {
                    dp[i] = cmp::max(dp[i], dp[j] + player[i].1);
                }
            }
            ret_val = cmp::max(ret_val, dp[i]);
        }

        return ret_val;
    }
}

fn main() {
    struct Subject {
        scores: Vec<i32>,
        ages: Vec<i32>,
    }
    let test_data = vec![
        Subject {
            scores: vec![1, 3, 5, 10, 15],
            ages: vec![1, 2, 3, 4, 5],
        },
        Subject {
            scores: vec![4, 5, 6, 5],
            ages: vec![2, 1, 2, 1],
        },
        Subject {
            scores: vec![1, 2, 3, 5],
            ages: vec![8, 9, 10, 1],
        },
    ];

    for p in test_data {
        println!("Input: scores = {:?}, ages = {:?}", p.scores, p.ages);

        let answer = Solution::best_team_score(p.scores, p.ages);
        println!("Output: {}", answer);

        println!();
    }
}
