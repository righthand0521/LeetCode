# Dynamic Programming

## [2140. Solving Questions With Brainpower](https://leetcode.com/problems/solving-questions-with-brainpower/)  1709

- [Official](https://leetcode.com/problems/solving-questions-with-brainpower/editorial/)
- [Official](https://leetcode.cn/problems/solving-questions-with-brainpower/solutions/1233147/jie-jue-zhi-li-wen-ti-by-leetcode-soluti-ieuq/)

<details><summary>Description</summary>

```text
You are given a 0-indexed 2D integer array questions where questions[i] = [pointsi, brainpoweri].

The array describes the questions of an exam, where you have to process the questions
in order (i.e., starting from question 0) and make a decision whether to solve or skip each question.
Solving question i will earn you pointsi points but you will be unable to solve each of the next brainpoweri questions.
If you skip question i, you get to make the decision on the next question.

For example, given questions = [[3, 2], [4, 3], [4, 4], [2, 5]]:
- If question 0 is solved, you will earn 3 points but you will be unable to solve questions 1 and 2.
- If instead, question 0 is skipped and question 1 is solved,
  you will earn 4 points but you will be unable to solve questions 2 and 3.
Return the maximum points you can earn for the exam.

Example 1:
Input: questions = [[3,2],[4,3],[4,4],[2,5]]
Output: 5
Explanation: The maximum points can be earned by solving questions 0 and 3.
- Solve question 0: Earn 3 points, will be unable to solve the next 2 questions
- Unable to solve questions 1 and 2
- Solve question 3: Earn 2 points
Total points earned: 3 + 2 = 5. There is no other way to earn 5 or more points.

Example 2:
Input: questions = [[1,1],[2,2],[3,3],[4,4],[5,5]]
Output: 7
Explanation: The maximum points can be earned by solving questions 1 and 4.
- Skip question 0
- Solve question 1: Earn 2 points, will be unable to solve the next 2 questions
- Unable to solve questions 2 and 3
- Solve question 4: Earn 5 points
Total points earned: 2 + 5 = 7. There is no other way to earn 7 or more points.

Constraints:
1 <= questions.length <= 10^5
questions[i].length == 2
1 <= pointsi, brainpoweri <= 10^5
```

<details><summary>Hint</summary>

```text
1. For each question, we can either solve it or skip it.
   How can we use Dynamic Programming to decide the most optimal option for each problem?
2. We store for each question the maximum points we can earn if we started the exam on that question.
3. If we skip a question, then the answer for it will be the same as the answer for the next question.
4. If we solve a question, then the answer for
   it will be the points of the current question plus the answer for the next solvable question.
5. The maximum of these two values will be the answer to the current question.
```

</details>

</details>

<details><summary>C</summary>

```c
long long mostPoints(int** questions, int questionsSize, int* questionsColSize) {
    long long retVal = 0;

    long long dp[questionsSize];
    memset(dp, 0, sizeof(dp));
    dp[questionsSize - 1] = questions[questionsSize - 1][0];
    int skip;
    int i;
    for (i = questionsSize - 2; i >= 0; --i) {
        dp[i] = questions[i][0];
        skip = questions[i][1];
        if (i + skip + 1 < questionsSize) {
            dp[i] += dp[i + skip + 1];
        }
        dp[i] = fmax(dp[i], dp[i + 1]);
    }
    retVal = dp[0];

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long mostPoints(vector<vector<int>>& questions) {
        long long retVal = 0;

        int questionsSize = questions.size();
        vector<long long> dp(questionsSize, 0);
        dp[questionsSize - 1] = questions[questionsSize - 1][0];
        for (int i = questionsSize - 2; i >= 0; --i) {
            dp[i] = questions[i][0];
            int skip = questions[i][1];
            if (i + skip + 1 < questionsSize) {
                dp[i] += dp[i + skip + 1];
            }
            dp[i] = max(dp[i], dp[i + 1]);
        }
        retVal = dp[0];

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def mostPoints(self, questions: List[List[int]]) -> int:
        retVal = 0

        questionsSize = len(questions)
        dp = [0] * questionsSize
        dp[-1] = questions[-1][0]
        for i in range(questionsSize-2, -1, -1):
            dp[i] = questions[i][0]
            skip = questions[i][1]
            if i + skip + 1 < questionsSize:
                dp[i] += dp[i + skip + 1]
            dp[i] = max(dp[i], dp[i + 1])
        retVal = dp[0]

        return retVal
```

</details>

## [2218. Maximum Value of K Coins From Piles](https://leetcode.com/problems/maximum-value-of-k-coins-from-piles/)  2157

<details><summary>Description</summary>

```text
There are n piles of coins on a table. Each pile consists of a positive number of coins of assorted denominations.

In one move, you can choose any coin on top of any pile, remove it, and add it to your wallet.

Given a list piles, where piles[i] is a list of integers denoting the composition of the ith pile from top to bottom,
and a positive integer k,
return the maximum total value of coins you can have in your wallet if you choose exactly k coins optimally.

Example 1:
Input: piles = [[1,100,3],[7,8,9]], k = 2
Output: 101
Explanation:
The above diagram shows the different ways we can choose k coins.
The maximum total we can obtain is 101.

Example 2:
Input: piles = [[100],[100],[100],[100],[100],[100],[1,1,1,1,1,1,700]], k = 7
Output: 706
Explanation:
The maximum total can be obtained if we choose all coins from the last pile.

Constraints:
n == piles.length
1 <= n <= 1000
1 <= piles[i][j] <= 10^5
1 <= k <= sum(piles[i].length) <= 2000
```

<details><summary>Hint</summary>

```text
1. For each pile i, what will be the total value of coins we can collect if we choose the first j coins?
2. How can we use dynamic programming to combine the results from different piles to find the most optimal answer?
```

</details>

</details>

<details><summary>C</summary>

```c
int maxValueOfCoins(int** piles, int pilesSize, int* pilesColSize, int k) {
    int retVal = 0;

    int i, j;

    int** prefixSum = (int**)malloc(pilesSize * sizeof(int*));
    if (prefixSum == NULL) {
        perror("malloc");
        return retVal;
    }
    int len;
    for (i = 0; i < pilesSize; ++i) {
        len = pilesColSize[i] + 1;
        prefixSum[i] = (int*)malloc(len * sizeof(int));
        if (prefixSum[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(prefixSum[j]);
                prefixSum[j] = NULL;
            }
            free(prefixSum);
            prefixSum = NULL;
            return retVal;
        }
        memset(prefixSum[i], 0, (len * sizeof(int)));
    }
    for (i = 0; i < pilesSize; ++i) {
        for (j = 1; j <= pilesColSize[i]; ++j) {
            prefixSum[i][j] = prefixSum[i][j - 1] + piles[i][j - 1];
        }
    }

    int dp[k + 1];
    memset(dp, 0, sizeof(dp));
    int sum_;
    int select;
    for (i = 0; i < pilesSize; ++i) {
        for (j = k; j >= 0; --j) {
            len = pilesColSize[i] + 1;
            for (select = 0; select < len; ++select) {
                sum_ = prefixSum[i][select];
                if (j - select >= 0) {
                    dp[j] = fmax(dp[j], dp[j - select] + sum_);
                }
            }
        }
    }
    retVal = dp[k];

    for (i = 0; i < pilesSize; ++i) {
        free(prefixSum[i]);
        prefixSum[i] = NULL;
    }
    free(prefixSum);
    prefixSum = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxValueOfCoins(vector<vector<int>>& piles, int k) {
        int retVal = 0;

        int pilesSize = piles.size();
        vector<vector<int>> prefixSum(pilesSize);
        for (int i = 0; i < pilesSize; ++i) {
            prefixSum[i].push_back(0);
            for (long unsigned int j = 0; j < piles[i].size(); ++j) {
                prefixSum[i].push_back(prefixSum[i][j] + piles[i][j]);
            }
        }

        vector<int> dp(k + 1, 0);
        for (int i = 0; i < pilesSize; ++i) {
            for (int j = k; j >= 0; --j) {
                int len = piles[i].size() + 1;
                for (int select = 0; select < len; ++select) {
                    int sum_ = prefixSum[i][select];
                    if (j - select >= 0) {
                        dp[j] = max(dp[j], dp[j - select] + sum_);
                    }
                }
            }
        }
        retVal = dp[k];

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxValueOfCoins(self, piles: List[List[int]], k: int) -> int:
        retVal = 0

        prefixSum = [[0] + list(accumulate(pile)) for pile in piles]
        dp = [0] * (k+1)
        for i in range(len(piles)):
            for j in range(k, -1, -1):
                for select in range(len(piles[i]) + 1):
                    sum_ = prefixSum[i][select]
                    if j - select >= 0:
                        dp[j] = max(dp[j], dp[j - select] + sum_)
        retVal = dp[-1]

        return retVal
```

</details>

## [2272. Substring With Largest Variance](https://leetcode.com/problems/substring-with-largest-variance/)  2515

- [Official](https://leetcode.com/problems/substring-with-largest-variance/editorial/)
- [Official](https://leetcode.cn/problems/substring-with-largest-variance/solutions/1501524/zui-da-bo-dong-de-zi-zi-fu-chuan-by-leet-xsnp/)

<details><summary>Description</summary>

```text
The variance of a string is defined as the largest difference between
the number of occurrences of any 2 characters present in the string.
Note the two characters may or may not be the same.

Given a string s consisting of lowercase English letters only,
return the largest variance possible among all substrings of s.

A substring is a contiguous sequence of characters within a string.

Example 1:
Input: s = "aababbb"
Output: 3
Explanation:
All possible variances along with their respective substrings are listed below:
- Variance 0 for substrings "a", "aa", "ab", "abab", "aababb", "ba", "b", "bb", and "bbb".
- Variance 1 for substrings "aab", "aba", "abb", "aabab", "ababb", "aababbb", and "bab".
- Variance 2 for substrings "aaba", "ababbb", "abbb", and "babb".
- Variance 3 for substring "babbb".
Since the largest possible variance is 3, we return it.

Example 2:
Input: s = "abcde"
Output: 0
Explanation:
No letter occurs more than once in s, so the variance of every substring is 0.

Constraints:
1 <= s.length <= 10^4
s consists of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Think about how to solve the problem if the string had only two distinct characters.
2. If we replace all occurrences of the first character by +1 and those of the second character by -1,
   can we efficiently calculate the largest possible variance of a string with only two distinct characters?
3. Now, try finding the optimal answer by taking all possible pairs of characters into consideration.
```

</details>

</details>

<details><summary>C</summary>

```c
int largestVariance(char *s) {
    int retVal = 0;

    int i;

#define MAX_LETTERS (26)  // s consists of lowercase English letters.
    int counter[MAX_LETTERS];
    memset(counter, 0, sizeof(counter));
    for (i = 0; i < strlen(s); ++i) {
        counter[s[i] - 'a']++;
    }

    char major, minor;
    int majorCount, minorCount;
    int restMinor;
    int c1, c2;
    for (c1 = 0; c1 < MAX_LETTERS; ++c1) {
        for (c2 = 0; c2 < MAX_LETTERS; ++c2) {
            // major and minor cannot be the same, and both must appear in s.
            if ((c1 == c2) || (counter[c1] == 0) || (counter[c2] == 0)) {
                continue;
            }

            // Find the maximum variance of major - minor.
            major = 'a' + c1;
            minor = 'a' + c2;
            majorCount = 0;
            minorCount = 0;

            // The remaining minor in the rest of s.
            restMinor = counter[c2];

            for (i = 0; i < strlen(s); ++i) {
                if (s[i] == major) {
                    majorCount++;
                }
                if (s[i] == minor) {
                    minorCount++;
                    restMinor--;
                }

                // Only update the variance (local_max) if there is at least one minor.
                if (minorCount > 0) {
                    retVal = fmax(retVal, majorCount - minorCount);
                }

                // We can discard the previous string if there is at least one remaining minor
                if ((majorCount < minorCount) && (restMinor > 0)) {
                    majorCount = 0;
                    minorCount = 0;
                }
            }
        }
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int largestVariance(string s) {
        int retVal = 0;

        int sSize = s.size();
        unordered_map<char, vector<int>> pos;
        for (int i = 0; i < sSize; ++i) {
            pos[s[i]].push_back(i);
        }

        for (auto&& [c0, pos0] : pos) {
            for (auto&& [c1, pos1] : pos) {
                if (c0 == c1) {
                    continue;
                }

                int i = 0;
                int j = 0;
                int f = 0;
                int g = numeric_limits<int>::min();
                int pos0Size = pos0.size();
                int pos1Size = pos1.size();
                while (i < pos0Size || j < pos1Size) {
                    if (j == pos1Size || (i < pos0Size && pos0[i] < pos1[j])) {
                        tie(f, g) = tuple{max(f, 0) + 1, g + 1};
                        ++i;
                    } else {
                        tie(f, g) = tuple{max(f, 0) - 1, max({f, g, 0}) - 1};
                        ++j;
                    }

                    retVal = max(retVal, g);
                }
            }
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def largestVariance(self, s: str) -> int:
        retVal = 0

        pos = defaultdict(list)
        for i, ch in enumerate(s):
            pos[ch].append(i)

        for c0, pos0 in pos.items():
            for c1, pos1 in pos.items():
                if c0 == c1:
                    continue

                i = 0
                j = 0
                f = 0
                g = float("-inf")
                while i < len(pos0) or j < len(pos1):
                    if (j == len(pos1)) or (i < len(pos0) and pos0[i] < pos1[j]):
                        f = max(f, 0) + 1
                        g += 1
                        i += 1
                    else:
                        g = max(f, g, 0) - 1
                        f = max(f, 0) - 1
                        j += 1
                    retVal = max(retVal, g)

        return retVal
```

</details>

## [2328. Number of Increasing Paths in a Grid](https://leetcode.com/problems/number-of-increasing-paths-in-a-grid/)  2001

- [Official](https://leetcode.com/problems/number-of-increasing-paths-in-a-grid/editorial/)

<details><summary>Description</summary>

```text
You are given an m x n integer matrix grid, where you can move from a cell to any adjacent cell in all 4 directions.

Return the number of strictly increasing paths in the grid such that you can start from any cell and end at any cell.
Since the answer may be very large, return it modulo 109 + 7.

Two paths are considered different if they do not have exactly the same sequence of visited cells.

Example 1:
Input: grid = [[1,1],[3,4]]
Output: 8
Explanation: The strictly increasing paths are:
- Paths with length 1: [1], [1], [3], [4].
- Paths with length 2: [1 -> 3], [1 -> 4], [3 -> 4].
- Paths with length 3: [1 -> 3 -> 4].
The total number of paths is 4 + 3 + 1 = 8.

Example 2:
Input: grid = [[1],[2]]
Output: 3
Explanation: The strictly increasing paths are:
- Paths with length 1: [1], [2].
- Paths with length 2: [1 -> 2].
The total number of paths is 2 + 1 = 3.

Constraints:
m == grid.length
n == grid[i].length
1 <= m, n <= 1000
1 <= m * n <= 10^5
1 <= grid[i][j] <= 10^5
```

<details><summary>Hint</summary>

```text
1. How can you calculate the number of increasing paths that start from a cell (i, j)?
   Think about dynamic programming.
2. Define f(i, j) as the number of increasing paths starting from cell (i, j).
   Try to find how f(i, j) is related to each of f(i, j+1), f(i, j-1), f(i+1, j) and f(i-1, j).
```

</details>

</details>

<details><summary>C</summary>

```c
#define MODULO (int)(1e9 + 7)
int dfs(int** grid, int gridSize, int gridColSize, int** dp, int i, int j) {
    int retVal = 1;

    if (dp[i][j] != 0) {
        retVal = dp[i][j];
        return retVal;
    }

    const int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int prev_i, prev_j;
    int dir;
    for (dir = 0; dir < 4; ++dir) {
        prev_i = i + directions[dir][0];
        prev_j = j + directions[dir][1];

        if ((prev_i < 0) || (prev_i >= gridSize)) {
            continue;
        } else if ((prev_j < 0) || (prev_j >= gridColSize)) {
            continue;
        } else if (grid[prev_i][prev_j] >= grid[i][j]) {
            continue;
        }
        retVal = (retVal + dfs(grid, gridSize, gridColSize, dp, prev_i, prev_j)) % MODULO;
    }
    dp[i][j] = retVal;

    return retVal;
}
int countPaths(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int i, j;

    //
    int** dp = (int**)malloc(gridSize * sizeof(int*));
    if (dp == NULL) {
        perror("malloc");
        return retVal;
    }
    for (i = 0; i < gridSize; ++i) {
        dp[i] = (int*)malloc(gridColSize[i] * sizeof(int));
        if (dp[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(dp[j]);
                dp[j] = NULL;
            }
            free(dp);
            dp = NULL;
            return retVal;
        }
        memset(dp[i], 0, (gridColSize[i] * sizeof(int)));
    }

    //
    for (i = 0; i < gridSize; ++i) {
        for (j = 0; j < gridColSize[0]; ++j) {
            retVal = (retVal + dfs(grid, gridSize, gridColSize[0], dp, i, j)) % MODULO;
        }
    }

    //
    for (i = 0; i < gridSize; ++i) {
        free(dp[i]);
        dp[i] = NULL;
    }
    free(dp);
    dp = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define MODULO (int)(1e9 + 7)
   public:
    const int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int dfs(vector<vector<int>>& grid, vector<vector<int>>& dp, int i, int j) {
        int retVal = 1;

        if (dp[i][j] != 0) {
            retVal = dp[i][j];
            return retVal;
        }

        int gridSize = grid.size();
        int gridColSize = grid[0].size();  // 1 <= m, n <= 1000
        for (auto& direction : directions) {
            int prev_i = i + direction[0];
            int prev_j = j + direction[1];

            if ((prev_i < 0) || (prev_i >= gridSize)) {
                continue;
            } else if ((prev_j < 0) || (prev_j >= gridColSize)) {
                continue;
            } else if (grid[prev_i][prev_j] >= grid[i][j]) {
                continue;
            }
            retVal = (retVal + dfs(grid, dp, prev_i, prev_j)) % MODULO;
        }
        dp[i][j] = retVal;

        return retVal;
    }
    int countPaths(vector<vector<int>>& grid) {
        int retVal = 0;

        int gridSize = grid.size();
        int gridColSize = grid[0].size();  // 1 <= m, n <= 1000
        vector<vector<int>> dp(gridSize, vector<int>(gridColSize, 0));
        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridColSize; ++j) {
                retVal = (retVal + dfs(grid, dp, i, j)) % MODULO;
            }
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def __init__(self):
        self.MODULO = 10 ** 9 + 7
        self.directions = [[0, 1], [0, -1], [1, 0], [-1, 0]]

    def dfs(self, grid: List[List[int]], dp: List[List[int]], i, j):
        retVal = 1

        if dp[i][j] != 0:
            retVal = dp[i][j]
            return retVal

        gridSize = len(grid)
        gridColSize = len(grid[0])  # 1 <= m, n <= 1000
        for di, dj in self.directions:
            prev_i = i + di
            prev_j = j + dj
            if (0 <= prev_i < gridSize) and (0 <= prev_j < gridColSize) and (grid[prev_i][prev_j] < grid[i][j]):
                retVal += self.dfs(grid, dp, prev_i, prev_j) % self.MODULO

        dp[i][j] = retVal

        return retVal

    def countPaths(self, grid: List[List[int]]) -> int:
        retVal = 0

        gridSize = len(grid)
        gridColSize = len(grid[0])  # 1 <= m, n <= 1000
        dp = [[0] * gridColSize for _ in range(gridSize)]
        retVal = sum(self.dfs(grid, dp, i, j) for i in range(gridSize) for j in range(gridColSize)) % self.MODULO

        return retVal
```

</details>

## [2369. Check if There is a Valid Partition For The Array](https://leetcode.com/problems/check-if-there-is-a-valid-partition-for-the-array/)  1779

- [Official](https://leetcode.cn/problems/check-if-there-is-a-valid-partition-for-the-array/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array nums. You have to partition the array into one or more contiguous subarrays.

We call a partition of the array valid if each of the obtained subarrays satisfies one of the following conditions:
1. The subarray consists of exactly 2 equal elements. For example, the subarray [2,2] is good.
2. The subarray consists of exactly 3 equal elements. For example, the subarray [4,4,4] is good.
3, The subarray consists of exactly 3 consecutive increasing elements,
   that is, the difference between adjacent elements is 1.
   For example, the subarray [3,4,5] is good, but the subarray [1,3,5] is not.
Return true if the array has at least one valid partition. Otherwise, return false.

Example 1:
Input: nums = [4,4,4,5,6]
Output: true
Explanation: The array can be partitioned into the subarrays [4,4] and [4,5,6].
This partition is valid, so we return true.

Example 2:
Input: nums = [1,1,1,2]
Output: false
Explanation: There is no valid partition for this array.

Constraints:
2 <= nums.length <= 10^5
1 <= nums[i] <= 10^6
```

<details><summary>Hint</summary>

```text
1. How can you reduce the problem to checking if there is a valid partition for a smaller array?
2. Use dynamic programming to reduce the problem until you have an empty array.
```

</details>

</details>

<details><summary>C</summary>

```c
bool validPartition(int* nums, int numsSize) {
    bool retVal = false;

    bool dp[numsSize + 1];
    memset(dp, false, sizeof(dp));
    dp[0] = true;
    // dp[i] represents if the prefix of length i can form a valid partition
    //  dp[index] : dp[index - 2] && (nums[i - 1] == nums[i])
    //  dp[index] : dp[index - 3] && (nums[i - 2] == nums[i - 1] == nums[i])
    //  dp[index] : dp[index - 3] && (nums[i - 2] + 2 == nums[i - 1] + 1 == nums[i])
    int index;
    int i;
    for (i = 0; i < numsSize; ++i) {
        index = i + 1;
        if ((i > 0) && (nums[i - 1] == nums[i])) {
            dp[index] = dp[index] | dp[index - 2];
        }
        if ((i > 1) && (nums[i - 2] == nums[i]) && (nums[i - 1] == nums[i])) {
            dp[index] = dp[index] | dp[index - 3];
        }
        if ((i > 1) && (nums[i - 2] + 2 == nums[i]) && (nums[i - 1] + 1 == nums[i])) {
            dp[index] = dp[index] | dp[index - 3];
        }
    }
    retVal = dp[numsSize];

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    bool validPartition(vector<int>& nums) {
        bool retVal = false;

        int numsSize = nums.size();
        vector<bool> dp(numsSize + 1, false);
        dp[0] = true;
        // dp[i] represents if the prefix of length i can form a valid partition
        //  dp[index] : dp[index - 2] && (nums[i - 1] == nums[i])
        //  dp[index] : dp[index - 3] && (nums[i - 2] == nums[i - 1] == nums[i])
        //  dp[index] : dp[index - 3] && (nums[i - 2] + 2 == nums[i - 1] + 1 == nums[i])
        for (int i = 0; i < numsSize; ++i) {
            int index = i + 1;
            if ((i > 0) && (nums[i - 1] == nums[i])) {
                dp[index] = dp[index] | dp[index - 2];
            }
            if ((i > 1) && (nums[i - 2] == nums[i]) && (nums[i - 1] == nums[i])) {
                dp[index] = dp[index] | dp[index - 3];
            }
            if ((i > 1) && (nums[i - 2] + 2 == nums[i]) && (nums[i - 1] + 1 == nums[i])) {
                dp[index] = dp[index] | dp[index - 3];
            }
        }
        retVal = dp[numsSize];

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def validPartition(self, nums: List[int]) -> bool:
        retVal = False

        numsSize = len(nums)
        dp = [True] + [False] * numsSize
        # dp[i] represents if the prefix of length i can form a valid partition
        #   dp[index]: dp[index - 2] && (nums[i - 1] == nums[i])
        #   dp[index]: dp[index - 3] && (nums[i - 2] == nums[i -1 ] == nums[i])
        #   dp[index]: dp[index - 3] && (nums[i - 2] + 2 == nums[i - 1] + 1 == nums[i])
        for i in range(numsSize):
            index = i + 1
            if (i > 0) and (nums[i-1] == nums[i]):
                dp[index] |= dp[index - 2]
            if (i > 1) and (nums[i-2] == nums[i - 1] == nums[i]):
                dp[index] |= dp[index - 3]
            if (i > 1) and (nums[i-2]+2 == nums[i - 1] + 1 == nums[i]):
                dp[index] |= dp[index - 3]
        retVal = dp[numsSize]

        return retVal
```

</details>

## [2370. Longest Ideal Subsequence](https://leetcode.com/problems/longest-ideal-subsequence/)  1834

- [Official](https://leetcode.com/problems/longest-ideal-subsequence/editorial/)

<details><summary>Description</summary>

```text
You are given a string s consisting of lowercase letters and an integer k.
We call a string t ideal if the following conditions are satisfied:
- t is a subsequence of the string s.
- The absolute difference in the alphabet order of every two adjacent letters in t is less than or equal to k.

Return the length of the longest ideal string.

A subsequence is a string that can be derived from another string by deleting some
or no characters without changing the order of the remaining characters.

Note that the alphabet order is not cyclic.
For example, the absolute difference in the alphabet order of 'a' and 'z' is 25, not 1.

Example 1:
Input: s = "acfgbd", k = 2
Output: 4
Explanation: The longest ideal string is "acbd". The length of this string is 4, so 4 is returned.
Note that "acfgbd" is not ideal because 'c' and 'f' have a difference of 3 in alphabet order.

Example 2:
Input: s = "abcd", k = 3
Output: 4
Explanation: The longest ideal string is "abcd". The length of this string is 4, so 4 is returned.

Constraints:
1 <= s.length <= 10^5
0 <= k <= 25
s consists of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. How can you calculate the longest ideal subsequence that ends at a specific index i?
2. Can you calculate it for all positions i?
   How can you use previously calculated answers to calculate the answer for the next position?
```

</details>

</details>

<details><summary>C</summary>

```c
#define LETTERS (26)  // s consists of lowercase English letters.
int longestIdealString(char* s, int k) {
    int retVal = 0;

    int sSize = strlen(s);

    int dp[LETTERS];
    memset(dp, 0, sizeof(dp));

    int current, best;
    int i, j;
    for (i = 0; i < sSize; ++i) {
        current = s[i] - 'a';
        best = 0;
        for (j = 0; j < LETTERS; ++j) {
            if (abs(j - current) <= k) {
                best = fmax(best, dp[j]);
            }
        }

        dp[current] = fmax(dp[current], best + 1);
        retVal = fmax(retVal, dp[current]);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    int letters = 26;  // s consists of lowercase English letters.

   public:
    int longestIdealString(string s, int k) {
        int retVal = 0;

        int sSize = s.size();

        vector<int> dp(letters, 0);
        for (int i = 0; i < sSize; ++i) {
            int current = s[i] - 'a';
            int best = 0;
            for (int j = 0; j < letters; ++j) {
                if (abs(j - current) <= k) {
                    best = max(best, dp[j]);
                }
            }

            dp[current] = max(dp[current], best + 1);
            retVal = max(retVal, dp[current]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def __init__(self) -> None:
        self.letters = 26  # s consists of lowercase English letters.

    def longestIdealString(self, s: str, k: int) -> int:
        retVal = 0

        sSize = len(s)

        dp = [0] * self.letters
        for i in range(sSize):
            current = ord(s[i]) - ord('a')
            best = 0
            for i in range(self.letters):
                if abs(i - current) <= k:
                    best = max(best, dp[i])

            dp[current] = max(dp[current], best + 1)
            retVal = max(retVal, dp[current])

        return retVal
```

</details>

## [2463. Minimum Total Distance Traveled](https://leetcode.com/problems/minimum-total-distance-traveled/)  2453

- [Official](https://leetcode.com/problems/minimum-total-distance-traveled/editorial/)

<details><summary>Description</summary>

```text
There are some robots and factories on the X-axis.
You are given an integer array robot where robot[i] is the position of the ith robot.
You are also given a 2D integer array factory where factory[j] = [positionj, limitj] indicates
that positionj is the position of the jth factory and that the jth factory can repair at most limitj robots.

The positions of each robot are unique. The positions of each factory are also unique.
Note that a robot can be in the same position as a factory initially.

All the robots are initially broken; they keep moving in one direction.
The direction could be the negative or the positive direction of the X-axis.
When a robot reaches a factory that did not reach its limit, the factory repairs the robot, and it stops moving.

At any moment, you can set the initial direction of moving for some robot.
Your target is to minimize the total distance traveled by all the robots.

Return the minimum total distance traveled by all the robots.
The test cases are generated such that all the robots can be repaired.

Note that
- All robots move at the same speed.
- If two robots move in the same direction, they will never collide.
- If two robots move in opposite directions and they meet at some point, they do not collide. They cross each other.
- If a robot passes by a factory that reached its limits, it crosses it as if it does not exist.
- If the robot moved from a position x to a position y, the distance it moved is |y - x|.

Example 1:
Input: robot = [0,4,6], factory = [[2,2],[6,2]]
Output: 4
Explanation: As shown in the figure:
- The first robot at position 0 moves in the positive direction. It will be repaired at the first factory.
- The second robot at position 4 moves in the negative direction. It will be repaired at the first factory.
- The third robot at position 6 will be repaired at the second factory. It does not need to move.
The limit of the first factory is 2, and it fixed 2 robots.
The limit of the second factory is 2, and it fixed 1 robot.
The total distance is |2 - 0| + |2 - 4| + |6 - 6| = 4.
It can be shown that we cannot achieve a better total distance than 4.

Example 2:
Input: robot = [1,-1], factory = [[-2,1],[2,1]]
Output: 2
Explanation: As shown in the figure:
- The first robot at position 1 moves in the positive direction. It will be repaired at the second factory.
- The second robot at position -1 moves in the negative direction. It will be repaired at the first factory.
The limit of the first factory is 1, and it fixed 1 robot.
The limit of the second factory is 1, and it fixed 1 robot.
The total distance is |2 - 1| + |(-2) - (-1)| = 2.
It can be shown that we cannot achieve a better total distance than 2.

Constraints:
1 <= robot.length, factory.length <= 100
factory[j].length == 2
-10^9 <= robot[i], positionj <= 10^9
0 <= limitj <= robot.length
The input will be generated such that it is always possible to repair every robot.
```

<details><summary>Hint</summary>

```text
1. Sort robots and factories by their positions.
2. After sorting, notice that each factory should repair some subsegment of robots.
3. Find the minimum total distance to repair first i robots with first j factories.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareIntArray(const void* a1, const void* a2) {
    const int* p1 = *(const int**)a1;
    const int* p2 = *(const int**)a2;

    // ascending order
    if (p1[0] == p2[0]) {
        return (p1[1] > p2[1]);
    }

    return (p1[0] > p2[0]);
}
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
long long minimumTotalDistance(int* robot, int robotSize, int** factory, int factorySize, int* factoryColSize) {
    long long retVal = 0;

    // Sort robots and factories by position
    qsort(robot, robotSize, sizeof(int), compareInteger);
    qsort(factory, factorySize, sizeof(factory[0]), compareIntArray);

    // Flatten factory positions according to their capacities
    int factoryPositionsSize = 0;
    for (int i = 0; i < factorySize; ++i) {
        factoryPositionsSize += factory[i][1];
    }
    int factoryPositions[factoryPositionsSize];
    memset(factoryPositions, 0, sizeof(factoryPositions));
    int factoryPositionsIndex = 0;
    for (int i = 0; i < factorySize; ++i) {
        for (int j = 0; j < factory[i][1]; ++j) {
            factoryPositions[factoryPositionsIndex++] = factory[i][0];
        }
    }

    long long dp[robotSize + 1][factoryPositionsSize + 1];
    memset(dp, 0, sizeof(dp));

    // Initialize base cases
    for (int i = 0; i < robotSize; ++i) {
        dp[i][factoryPositionsSize] = 1e12;  // No factories left
    }

    // Fill DP table bottom-up
    long long assign, skip;
    for (int i = robotSize - 1; i >= 0; --i) {
        for (int j = factoryPositionsSize - 1; j >= 0; --j) {
            // Option 1: Assign current robot to current factory
            assign = abs(robot[i] - factoryPositions[j]) + dp[i + 1][j + 1];

            // Option 2: Skip current factory for the current robot
            skip = dp[i][j + 1];

            dp[i][j] = fmin(assign, skip);  // Take the minimum option
        }
    }
    retVal = dp[0][0];  // Minimum distance starting from first robot and factory

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        long long retVal = 0;

        // Sort robots and factories by position
        sort(robot.begin(), robot.end());
        sort(factory.begin(), factory.end());

        // Flatten factory positions according to their capacities
        vector<int> factoryPositions;
        for (auto& f : factory) {
            for (int i = 0; i < f[1]; i++) {
                factoryPositions.push_back(f[0]);
            }
        }

        int robotSize = robot.size();
        int factoryPositionsSize = factoryPositions.size();
        vector<vector<long long>> dp(robotSize + 1, vector<long long>(factoryPositionsSize + 1, 0));

        // Initialize base cases
        for (int i = 0; i < robotSize; i++) {
            dp[i][factoryPositionsSize] = 1e12;  // No factories left
        }

        // Fill DP table bottom-up
        for (int i = robotSize - 1; i >= 0; i--) {
            for (int j = factoryPositionsSize - 1; j >= 0; j--) {
                // Option 1: Assign current robot to current factory
                long long assign = abs(robot[i] - factoryPositions[j]) + dp[i + 1][j + 1];

                // Option 2: Skip current factory for the current robot
                long long skip = dp[i][j + 1];

                dp[i][j] = min(assign, skip);  // Take the minimum option
            }
        }
        retVal = dp[0][0];  // Minimum distance starting from first robot and factory

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minimumTotalDistance(self, robot: List[int], factory: List[List[int]]) -> int:
        retVal = 0

        # Sort robots and factories by position
        robot.sort()
        factory.sort(key=lambda x: x[0])

        # Flatten factory positions according to their capacities
        factoryPositions = []
        for f in factory:
            for _ in range(f[1]):
                factoryPositions.append(f[0])

        robotSize = len(robot)
        factoryPositionsSize = len(factoryPositions)
        dp = [[0] * (factoryPositionsSize + 1) for _ in range(robotSize + 1)]

        # Initialize base cases
        for i in range(robotSize):
            dp[i][factoryPositionsSize] = 1e12  # No factories left

        # Fill DP table bottom-up
        for i in range(robotSize - 1, -1, -1):
            for j in range(factoryPositionsSize - 1, -1, -1):
                # Option 1: Assign current robot to current factory
                assign = abs(robot[i] - factoryPositions[j]) + dp[i + 1][j + 1]

                # Option 2: Skip current factory for the current robot
                skip = dp[i][j + 1]

                dp[i][j] = min(assign, skip)  # Take the minimum option

        # Minimum distance starting from first robot and factory
        retVal = dp[0][0]

        return retVal
```

</details>

## [2466. Count Ways To Build Good Strings](https://leetcode.com/problems/count-ways-to-build-good-strings/)  1694

- [Official](https://leetcode.com/problems/count-ways-to-build-good-strings/editorial/)

<details><summary>Description</summary>

```text
Given the integers zero, one, low, and high, we can construct a string by starting with an empty string,
and then at each step perform either of the following:
- Append the character '0' zero times.
- Append the character '1' one times.
This can be performed any number of times.

A good string is a string constructed by the above process having a length between low and high (inclusive).

Return the number of different good strings that can be constructed satisfying these properties.
Since the answer can be large, return it modulo 109 + 7.

Example 1:
Input: low = 3, high = 3, zero = 1, one = 1
Output: 8
Explanation:
One possible valid good string is "011".
It can be constructed as follows: "" -> "0" -> "01" -> "011".
All binary strings from "000" to "111" are good strings in this example.

Example 2:
Input: low = 2, high = 3, zero = 1, one = 2
Output: 5
Explanation: The good strings are "00", "11", "000", "110", and "011".

Constraints:
1 <= low <= high <= 10^5
1 <= zero, one <= low
```

<details><summary>Hint</summary>

```text
1. Calculate the number of good strings with length less or equal to some constant x.
2. Apply dynamic programming using the group size of consecutive zeros and ones.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MODULO (int)(1e9 + 7)
int countGoodStrings(int low, int high, int zero, int one) {
    int retVal = 0;

    int dp[high + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    int i;
    for (i = 1; i <= high; ++i) {
        if (i >= zero) {
            dp[i] += dp[i - zero];
            dp[i] %= MODULO;
        }

        if (i >= one) {
            dp[i] += dp[i - one];
            dp[i] %= MODULO;
        }
    }

    for (i = low; i <= high; ++i) {
        retVal += dp[i];
        retVal %= MODULO;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
#define MODULO (int)(1e9 + 7)
class Solution {
   public:
    int countGoodStrings(int low, int high, int zero, int one) {
        int retVal = 0;

        vector<int> dp(high + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= high; ++i) {
            if (i >= zero) {
                dp[i] += dp[i - zero];
                dp[i] %= MODULO;
            }

            if (i >= one) {
                dp[i] += dp[i - one];
                dp[i] %= MODULO;
            }
        }

        for (int i = low; i <= high; ++i) {
            retVal += dp[i];
            retVal %= MODULO;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def __init__(self):
        self.MODULO = 10 ** 9 + 7

    def countGoodStrings(self, low: int, high: int, zero: int, one: int) -> int:
        retVal = 0

        dp = [1] + [0] * high
        for i in range(1, high+1):
            if i >= zero:
                dp[i] += dp[i - zero]
                dp[i] %= self.MODULO

            if i >= one:
                dp[i] += dp[i - one]
                dp[i] %= self.MODULO

        retVal = sum(dp[low:high+1]) % self.MODULO

        return retVal
```

</details>

## [2597. The Number of Beautiful Subsets](https://leetcode.com/problems/the-number-of-beautiful-subsets/)  2023

- [Official](https://leetcode.com/problems/the-number-of-beautiful-subsets/editorial/)

<details><summary>Description</summary>

```text
You are given an array nums of positive integers and a positive integer k.

A subset of nums is beautiful if it does not contain two integers with an absolute difference equal to k.

Return the number of non-empty beautiful subsets of the array nums.

A subset of nums is an array that can be obtained by deleting some (possibly none) elements from nums.
Two subsets are different if and only if the chosen indices to delete are different.

Example 1:
Input: nums = [2,4,6], k = 2
Output: 4
Explanation: The beautiful subsets of the array nums are: [2], [4], [6], [2, 6].
It can be proved that there are only 4 beautiful subsets in the array [2,4,6].

Example 2:
Input: nums = [1], k = 1
Output: 1
Explanation: The beautiful subset of the array nums is [1].
It can be proved that there is only 1 beautiful subset in the array [1].

Constraints:
1 <= nums.length <= 20
1 <= nums[i], k <= 1000
```

<details><summary>Hint</summary>

```text
1. Sort the array nums and create another array cnt of size nums[i].
2. Use backtracking to generate all the beautiful subsets.
   If cnt[nums[i] - k] is positive, then it is impossible to add nums[i] in the subset,
   and we just move to the next index.
   Otherwise, it is also possible to add nums[i] in the subset,
   in this case, increase cnt[nums[i]], and move to the next index.
3. Bonus: Can you solve the problem in O(n log n)?
```

</details>

</details>

<details><summary>C</summary>

```c
int beautifulSubsets(int *nums, int numsSize, int k) {
    int retVal = 0;

    if ((numsSize == 0) || (numsSize == 1)) {
        retVal = numsSize;
        return retVal;
    }

    int dp[numsSize];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    if ((nums[1] - nums[0] == k) || (nums[0] - nums[1] == k)) {
        dp[1] = 2;
    } else {
        dp[1] = 3;
    }

    int *pTemp = (int *)malloc(numsSize * sizeof(int));
    if (pTemp == NULL) {
        perror("malloc");
        return retVal;
    }
    memset(pTemp, 0, (numsSize * sizeof(int)));

    int t = 0;
    int q = 0;
    int i, j;
    for (i = 2; i < numsSize; i++) {
        for (j = 0; j < i; j++) {
            if (nums[i] - nums[j] == k || nums[j] - nums[i] == k) {
                t++;
            } else {
                pTemp[q] = nums[j];
                q++;
            }
        }

        if (t == 0) {
            dp[i] = 2 * dp[i - 1] + 1;
        } else {
            dp[i] = dp[i - 1] + 1 + beautifulSubsets(pTemp, q, k);
        }

        t = 0;
        q = 0;
    }
    retVal = dp[numsSize - 1];

    free(pTemp);
    pTemp = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int beautifulSubsets(vector<int>& nums, int k) {
        int retVal = 1;

        // Calculate frequencies based on remainder
        map<int, map<int, int>> freqMap;
        for (int& num : nums) {
            freqMap[num % k][num]++;
        }

        // Iterate through each remainder group
        for (auto& fr : freqMap) {
            int prevNum = -k;
            int prev1 = 1;
            int prev2 = 1;
            int curr = 1;

            // Iterate through each number in the current remainder group
            for (auto& [num, freq] : fr.second) {
                // Count of subsets skipping the current number
                int skip = prev1;

                // Count of subsets including the current number
                // Check if the current number and the previous number form a beautiful pair
                int take;
                if (num - prevNum == k) {
                    take = ((1 << freq) - 1) * prev2;
                } else {
                    take = ((1 << freq) - 1) * prev1;
                }

                // Store the total count for the current number
                curr = skip + take;
                prev2 = prev1;
                prev1 = curr;
                prevNum = num;
            }
            retVal *= curr;
        }
        retVal = retVal - 1;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def beautifulSubsets(self, nums: List[int], k: int) -> int:
        retVal = 1

        # Calculate frequencies based on remainder
        freq_map = defaultdict(dict)
        for num in nums:
            freq_map[num % k][num] = freq_map[num % k].get(num, 0) + 1

        # Iterate through each remainder group
        for fr in freq_map.values():
            prev_num = -k
            curr = 1
            prev1 = 1
            prev2 = 0

            # Iterate through each number in the current remainder group
            for num, freq in sorted(fr.items()):
                # Count of subsets skipping the current number
                skip = prev1

                # Count of subsets including the current number
                # Check if the current number and the previous number form a beautiful pair
                if num - prev_num == k:
                    take = ((1 << freq) - 1) * prev2
                else:
                    take = ((1 << freq) - 1) * prev1

                # Store the total count for the current number
                curr = skip + take
                prev2, prev1 = prev1, curr
                prev_num = num

            retVal *= curr

        retVal = retVal - 1

        return retVal
```

</details>

## [2684. Maximum Number of Moves in a Grid](https://leetcode.com/problems/maximum-number-of-moves-in-a-grid/)  1625

- [Official](https://leetcode.com/problems/maximum-number-of-moves-in-a-grid/editorial/)
- [Official](https://leetcode.cn/problems/maximum-number-of-moves-in-a-grid/solutions/2684036/ju-zhen-zhong-yi-dong-de-zui-da-ci-shu-b-b7jx/)

<details><summary>Description</summary>

```text
You are given a 0-indexed m x n matrix grid consisting of positive integers.

You can start at any cell in the first column of the matrix, and traverse the grid in the following way:
- From a cell (row, col), you can move to any of the cells:
  (row - 1, col + 1), (row, col + 1) and (row + 1, col + 1) such that the value of the cell you move to,
  should be strictly bigger than the value of the current cell.

Return the maximum number of moves that you can perform.

Example 1:
Input: grid = [[2,4,3,5],[5,4,9,3],[3,4,2,11],[10,9,13,15]]
Output: 3
Explanation: We can start at the cell (0, 0) and make the following moves:
- (0, 0) -> (0, 1).
- (0, 1) -> (1, 2).
- (1, 2) -> (2, 3).
It can be shown that it is the maximum number of moves that can be made.

Example 2:
Input: grid = [[3,2,4],[2,1,9],[1,1,7]]
Output: 0
Explanation: Starting from any cell in the first column we cannot perform any moves.

Constraints:
m == grid.length
n == grid[i].length
2 <= m, n <= 1000
4 <= m * n <= 10^5
1 <= grid[i][j] <= 10^6
```

<details><summary>Hint</summary>

```text
1. Consider using dynamic programming to find the maximum number of moves that can be made from each cell.
2. The final answer will be the maximum value in cells of the first column.
```

</details>

</details>

<details><summary>C</summary>

```c
int maxMoves(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int x, y;

    int row = gridSize;
    int col = gridColSize[0];
    int dp[row][col];
    memset(dp, 0, sizeof(dp));
    for (x = 0; x < row; ++x) {  // Initialize the first column with moves as 1.
        dp[x][0] = 1;
    }

    // Check all three possible previous cells: (x, y-1), (x-1, y-1), (x+1, y-1)
    for (y = 1; y < col; ++y) {
        for (x = 0; x < row; ++x) {
            if ((grid[x][y] > grid[x][y - 1]) && (dp[x][y - 1] > 0)) {
                dp[x][y] = fmax(dp[x][y], dp[x][y - 1] + 1);
            }

            if ((x - 1 >= 0) && (grid[x][y] > grid[x - 1][y - 1]) && (dp[x - 1][y - 1] > 0)) {
                dp[x][y] = fmax(dp[x][y], dp[x - 1][y - 1] + 1);
            }

            if ((x + 1 < row) && (grid[x][y] > grid[x + 1][y - 1]) && (dp[x + 1][y - 1] > 0)) {
                dp[x][y] = fmax(dp[x][y], dp[x + 1][y - 1] + 1);
            }

            retVal = fmax(retVal, dp[x][y] - 1);
        }
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxMoves(vector<vector<int>>& grid) {
        int retVal = 0;

        int row = grid.size();
        int col = grid[0].size();
        vector<vector<int>> dp(row, vector<int>(col, 0));
        for (int x = 0; x < row; ++x) {  // Initialize the first column with moves as 1.
            dp[x][0] = 1;
        }

        // Check all three possible previous cells: (x, y-1), (x-1, y-1), (x+1, y-1)
        for (int y = 1; y < col; ++y) {
            for (int x = 0; x < row; ++x) {
                if ((grid[x][y] > grid[x][y - 1]) && (dp[x][y - 1] > 0)) {
                    dp[x][y] = max(dp[x][y], dp[x][y - 1] + 1);
                }

                if ((x - 1 >= 0) && (grid[x][y] > grid[x - 1][y - 1]) && (dp[x - 1][y - 1] > 0)) {
                    dp[x][y] = max(dp[x][y], dp[x - 1][y - 1] + 1);
                }

                if ((x + 1 < row) && (grid[x][y] > grid[x + 1][y - 1]) && (dp[x + 1][y - 1] > 0)) {
                    dp[x][y] = max(dp[x][y], dp[x + 1][y - 1] + 1);
                }

                retVal = max(retVal, dp[x][y] - 1);
            }
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxMoves(self, grid: List[List[int]]) -> int:
        retVal = 0

        row = len(grid)
        col = len(grid[0])
        dp = [[0] * col for _ in range(row)]
        for x in range(row):  # Initialize the first column with moves as 1.
            dp[x][0] = 1

        # Check all three possible previous cells: (x, y-1), (x-1, y-1), (x+1, y-1)
        for y in range(1, col):
            for x in range(row):
                if (grid[x][y] > grid[x][y-1]) and (dp[x][y-1] > 0):
                    dp[x][y] = max(dp[x][y], dp[x][y-1] + 1)

                if ((x - 1 >= 0) and (grid[x][y] > grid[x-1][y-1]) and (dp[x-1][y-1] > 0)):
                    dp[x][y] = max(dp[x][y], dp[x-1][y-1] + 1)

                if ((x + 1 < row) and (grid[x][y] > grid[x+1][y-1]) and (dp[x+1][y-1] > 0)):
                    dp[x][y] = max(dp[x][y], dp[x+1][y-1] + 1)

                retVal = max(retVal, dp[x][y] - 1)

        return retVal
```

</details>

## [2707. Extra Characters in a String](https://leetcode.com/problems/extra-characters-in-a-string/)  1735

- [Official](https://leetcode.com/problems/extra-characters-in-a-string/editorial/)
- [Official](https://leetcode.cn/problems/extra-characters-in-a-string/solutions/2590667/zi-fu-chuan-zhong-de-e-wai-zi-fu-by-leet-f0lu/)

<details><summary>Description</summary>

```text
You are given a 0-indexed string s and a dictionary of words dictionary.
You have to break s into one or more non-overlapping substrings such that each substring is present in dictionary.
There may be some extra characters in s which are not present in any of the substrings.

Return the minimum number of extra characters left over if you break up s optimally.

Example 1:
Input: s = "leetscode", dictionary = ["leet","code","leetcode"]
Output: 1
Explanation: We can break s in two substrings: "leet" from index 0 to 3 and "code" from index 5 to 8.
There is only 1 unused character (at index 4), so we return 1.

Example 2:
Input: s = "sayhelloworld", dictionary = ["hello","world"]
Output: 3
Explanation: We can break s in two substrings: "hello" from index 3 to 7 and "world" from index 8 to 12.
The characters at indices 0, 1, 2 are not used in any substring and thus are considered as extra characters.
Hence, we return 3.

Constraints:
1 <= s.length <= 50
1 <= dictionary.length <= 50
1 <= dictionary[i].length <= 50
dictionary[i] and s consists of only lowercase English letters
dictionary contains distinct words
```

<details><summary>Hint</summary>

```text
1. Can we use Dynamic Programming here?
2. Define DP[i] as the min extra character if breaking up s[0:i] optimally.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MAX_WORDS_LENGTH (50 + 2)  // 1 <= dictionary[i].length <= 50
struct hash_struct {
    char words[MAX_WORDS_LENGTH];
    UT_hash_handle hh;
};
void freeAll(struct hash_struct* pFree) {
    struct hash_struct* pCurrent;
    struct hash_struct* pTmp;
    HASH_ITER(hh, pFree, pCurrent, pTmp) {
        HASH_DEL(pFree, pCurrent);
        free(pCurrent);
    }
}
int minExtraChar(char* s, char** dictionary, int dictionarySize) {
    int retVal = 0;

    struct hash_struct* pDictionarySet = NULL;
    struct hash_struct* pTmp;
    int i;
    for (i = 0; i < dictionarySize; ++i) {
        pTmp = NULL;
        HASH_FIND_STR(pDictionarySet, dictionary[i], pTmp);
        if (pTmp == NULL) {
            pTmp = (struct hash_struct*)malloc(sizeof(struct hash_struct));
            if (pTmp == NULL) {
                perror("malloc");
                freeAll(pDictionarySet);
                pDictionarySet = NULL;
                return retVal;
            }
            snprintf(pTmp->words, MAX_WORDS_LENGTH, "%s", dictionary[i]);
            HASH_ADD_STR(pDictionarySet, words, pTmp);
        }
    }

    int sSize = strlen(s);
    int dp[sSize + 1];
    memset(dp, 0, sizeof(dp));
    char buf[sSize + 1];
    int start, end;
    for (start = sSize - 1; start >= 0; start--) {
        dp[start] = dp[start + 1] + 1;
        for (end = start; end < sSize; end++) {
            memset(buf, 0, sizeof(buf));
            memcpy(buf, s + start, end - start + 1);

            pTmp = NULL;
            HASH_FIND_STR(pDictionarySet, buf, pTmp);
            if (pTmp != NULL) {
                dp[start] = fmin(dp[start], dp[end + 1]);
            }
        }
    }
    retVal = dp[0];

    freeAll(pDictionarySet);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minExtraChar(string s, vector<string>& dictionary) {
        int retVal = 0;

        unordered_set<string> dictionarySet(dictionary.begin(), dictionary.end());

        int sSize = s.length();
        vector<int> dp(sSize + 1, 0);
        for (int start = sSize - 1; start >= 0; start--) {
            dp[start] = dp[start + 1] + 1;
            for (int end = start; end < sSize; end++) {
                auto curr = s.substr(start, end - start + 1);
                if (dictionarySet.count(curr)) {
                    dp[start] = min(dp[start], dp[end + 1]);
                }
            }
        }
        retVal = dp[0];

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minExtraChar(self, s: str, dictionary: List[str]) -> int:
        retVal = 0

        dictionary_set = set(dictionary)

        sSize = len(s)
        dp = [0] * (sSize + 1)
        for start in range(sSize - 1, -1, -1):
            dp[start] = 1 + dp[start + 1]
            for end in range(start, sSize):
                curr = s[start: end + 1]
                if curr in dictionary_set:
                    dp[start] = min(dp[start], dp[end + 1])
        retVal = dp[0]

        return retVal
```

</details>

## [2742. Painting the Walls](https://leetcode.com/problems/painting-the-walls/description/)  2424

- [Official](https://leetcode.com/problems/painting-the-walls/editorial/)

<details><summary>Description</summary>

```text
You are given two 0-indexed integer arrays, cost and time,
of size n representing the costs and the time taken to paint n different walls respectively.
There are two painters available:
- A paid painter that paints the ith wall in time[i] units of time and takes cost[i] units of money.
- A free painter that paints any wall in 1 unit of time at a cost of 0.
  But the free painter can only be used if the paid painter is already occupied.

Return the minimum amount of money required to paint the n walls.

Example 1:
Input: cost = [1,2,3,2], time = [1,2,3,2]
Output: 3
Explanation: The walls at index 0 and 1 will be painted by the paid painter, and it will take 3 units of time;
meanwhile, the free painter will paint the walls at index 2 and 3, free of cost in 2 units of time.
Thus, the total cost is 1 + 2 = 3.

Example 2:
Input: cost = [2,3,4,2], time = [1,1,1,1]
Output: 4
Explanation: The walls at index 0 and 3 will be painted by the paid painter, and it will take 2 units of time;
meanwhile, the free painter will paint the walls at index 1 and 2, free of cost in 2 units of time.
Thus, the total cost is 2 + 2 = 4.

Constraints:
1 <= cost.length <= 500
cost.length == time.length
1 <= cost[i] <= 10^6
1 <= time[i] <= 500
```

<details><summary>Hint</summary>

```text
1. Can we break the problem down into smaller subproblems and use DP?
2. Paid painters will be used for a maximum of N/2 units of time.
   There is no need to use paid painter for a time greater than this.
```

</details>

</details>

<details><summary>C</summary>

```c
int paintWalls(int* cost, int costSize, int* time, int timeSize) {
    int retVal = 0;

    const int INF = 1e9;  // 1 <= cost.length <= 500, 1 <= cost[i] <= 10^6.
    int i, j;

    int dp[costSize + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 0;
    for (i = 1; i <= costSize; i++) {
        dp[i] = INF;
    }

    int idx;
    for (i = 0; i < costSize; i++) {
        for (j = costSize; j >= 0; j--) {
            idx = fmax(j - time[i] - 1, 0);
            dp[j] = fmin(dp[j], dp[idx] + cost[i]);
        }
    }
    retVal = dp[costSize];

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int paintWalls(vector<int>& cost, vector<int>& time) {
        int retVal = 0;

        int costSize = cost.size();
        const int INF = 1e9;  // 1 <= cost.length <= 500, 1 <= cost[i] <= 10^6.

        vector<int> dp(costSize + 1, INF);
        dp[0] = 0;
        for (int i = 0; i < costSize; i++) {
            for (int j = costSize; j >= 0; j--) {
                dp[j] = min(dp[j], dp[max(j - time[i] - 1, 0)] + cost[i]);
            }
        }
        retVal = dp[costSize];

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def paintWalls(self, cost: List[int], time: List[int]) -> int:
        retVal = 0

        costSize = len(cost)

        # 1 <= cost.length <= 500, 1 <= cost[i] <= 10^6.
        dp = [0] + [float("inf")] * costSize
        for i in range(costSize):
            for j in range(costSize, -1, -1):
                dp[j] = min(dp[j], dp[max(j - time[i] - 1, 0)] + cost[i])
        retVal = dp[costSize]

        return retVal
```

</details>

## [2999. Count the Number of Powerful Integers](https://leetcode.com/problems/count-the-number-of-powerful-integers/)  2351

- [Official](https://leetcode.com/problems/count-the-number-of-powerful-integers/editorial/)
- [Official](https://leetcode.cn/problems/count-the-number-of-powerful-integers/solutions/3636119/tong-ji-qiang-da-zheng-shu-de-shu-mu-by-pozr1/)

<details><summary>Description</summary>

```text
You are given three integers start, finish, and limit.
You are also given a 0-indexed string s representing a positive integer.

A positive integer x is called powerful if it ends with s (in other words, s is a suffix of x)
and each digit in x is at most limit.

Return the total number of powerful integers in the range [start..finish].

A string x is a suffix of a string y if and only if x is a substring of y
that starts from some index (including 0) in y and extends to the index y.length - 1.
For example, 25 is a suffix of 5125 whereas 512 is not.

Example 1:
Input: start = 1, finish = 6000, limit = 4, s = "124"
Output: 5
Explanation: The powerful integers in the range [1..6000] are 124, 1124, 2124, 3124, and, 4124.
All these integers have each digit <= 4, and "124" as a suffix.
Note that 5124 is not a powerful integer because the first digit is 5 which is greater than 4.
It can be shown that there are only 5 powerful integers in this range.

Example 2:
Input: start = 15, finish = 215, limit = 6, s = "10"
Output: 2
Explanation: The powerful integers in the range [15..215] are 110 and 210.
All these integers have each digit <= 6, and "10" as a suffix.
It can be shown that there are only 2 powerful integers in this range.

Example 3:
Input: start = 1000, finish = 2000, limit = 4, s = "3000"
Output: 0
Explanation: All integers in the range [1000..2000] are smaller than 3000,
hence "3000" cannot be a suffix of any integer in this range.

Constraints:
1 <= start <= finish <= 10^15
1 <= limit <= 9
1 <= s.length <= floor(log10(finish)) + 1
s only consists of numeric digits which are at most limit.
s does not have leading zeros.
```

<details><summary>Hint</summary>

```text
1. We can use digit DP to count powerful integers in the range [1, x].
2. Let dp[i][j] be the number of integers that have i digits (with allowed leading 0s)
   and j refers to the comparison between the current number and the prefix of x, j == 0
   if the i-digit number formed currently is identical to the leftmost i digits of x,
   else if j ==1 it means the i-digit number is smaller than the leftmost i digits of x.
3. The answer is count[finish] - count[start - 1],
   where count[i] refers to the number of powerful integers in the range [1..i].
```

</details>

</details>

<details><summary>C</summary>

```c
long long calculate(const char* x, const char* s, int limit) {
    long long retVal = 0;

    int xSize = strlen(x);
    int sSize = strlen(s);
    if (xSize < sSize) {
        return retVal;
    } else if (xSize == sSize) {
        if (strcmp(x, s) >= 0) {
            retVal = 1;
        }
        return retVal;
    }

    char* suffix = (char*)malloc(sSize + 1);
    strncpy(suffix, x + xSize - sSize, sSize);
    suffix[sSize] = '\0';

    int preLen = xSize - sSize;
    for (int i = 0; i < preLen; i++) {
        int digit = x[i] - '0';
        if (limit < digit) {
            retVal += (long long)pow(limit + 1, preLen - i);
            free(suffix);
            return retVal;
        }
        retVal += (long long)digit * (long long)pow(limit + 1, preLen - 1 - i);
    }

    if (strcmp(suffix, s) >= 0) {
        retVal++;
    }
    free(suffix);

    return retVal;
}
long long numberOfPowerfulInt(long long start, long long finish, int limit, char* s) {
    long long retVal = 0;

#define MAX_LONGLONG_STRING_SIZE (32)

    char startString[MAX_LONGLONG_STRING_SIZE];
    memset(startString, 0, sizeof(startString));
    sprintf(startString, "%lld", start - 1);

    char finishString[MAX_LONGLONG_STRING_SIZE];
    memset(finishString, 0, sizeof(finishString));
    sprintf(finishString, "%lld", finish);

    retVal = calculate(finishString, s, limit) - calculate(startString, s, limit);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    long long calculate(string x, string s, int limit) {
        long long retVal = 0;

        int xSize = x.size();
        int sSize = s.size();
        if (xSize < sSize) {
            return retVal;
        } else if (xSize == sSize) {
            if (x >= s) {
                retVal = 1;
            }
            return retVal;
        }

        string suffix = x.substr(xSize - sSize, sSize);

        int preLen = xSize - sSize;
        for (int i = 0; i < preLen; i++) {
            if (limit < (x[i] - '0')) {
                retVal += (long)pow(limit + 1, preLen - i);
                return retVal;
            }
            retVal += (long)(x[i] - '0') * (long)pow(limit + 1, preLen - 1 - i);
        }

        if (suffix >= s) {
            retVal++;
        }

        return retVal;
    }

   public:
    long long numberOfPowerfulInt(long long start, long long finish, int limit, string s) {
        long long retVal = 0;

        string startString = to_string(start - 1);
        string finishString = to_string(finish);
        retVal = calculate(finishString, s, limit) - calculate(startString, s, limit);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def calculate(self, x: str, s: str, limit: int) -> int:
        retVal = 0

        xSize = len(x)
        sSize = len(s)

        if xSize < sSize:
            return retVal
        elif xSize == sSize:
            if x >= s:
                retVal = 1
            return retVal

        suffix = x[xSize - sSize:]

        preLen = xSize - sSize
        for i in range(preLen):
            if limit < int(x[i]):
                retVal += (limit + 1) ** (preLen - i)
                return retVal
            retVal += int(x[i]) * (limit + 1) ** (preLen - 1 - i)

        if suffix >= s:
            retVal += 1

        return retVal

    def numberOfPowerfulInt(self, start: int, finish: int, limit: int, s: str) -> int:
        retVal = 0

        startString = str(start - 1)
        finishString = str(finish)
        retVal = self.calculate(finishString, s, limit) - self.calculate(startString, s, limit)

        return retVal
```

</details>
