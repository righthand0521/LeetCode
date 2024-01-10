struct Solution {}

impl Solution {
    pub fn check_x_matrix(grid: Vec<Vec<i32>>) -> bool {
        let len = grid.len();
        for row in 0..len {
            for col in 0..len {
                if (row == col) || (row + col + 1 == len) {
                    if grid[row][col] == 0 {
                        return false;
                    }
                } else {
                    if grid[row][col] != 0 {
                        return false;
                    }
                }
            }
        }

        return true;
    }
}

fn main() {
    struct Subject {
        grid: Vec<Vec<i32>>,
    }
    let test_data = vec![
        Subject {
            grid: vec![
                vec![2, 0, 0, 1],
                vec![0, 3, 1, 0],
                vec![0, 5, 2, 0],
                vec![4, 0, 0, 2],
            ],
        },
        Subject {
            grid: vec![vec![5, 7, 0], vec![0, 3, 1], vec![0, 5, 0]],
        },
        Subject {
            grid: vec![
                vec![5, 0, 0, 1],
                vec![0, 4, 1, 5],
                vec![0, 5, 2, 0],
                vec![4, 1, 0, 2],
            ],
        },
    ];

    for p in test_data {
        println!("Input: grid = {:?}", p.grid);

        let answer = Solution::check_x_matrix(p.grid);
        println!("Output: {}", answer);

        println!();
    }
}
