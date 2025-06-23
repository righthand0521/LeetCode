# Math

## [2028. Find Missing Observations](https://leetcode.com/problems/find-missing-observations/)  1444

- [Official](https://leetcode.com/problems/find-missing-observations/editorial/)
- [Official](https://leetcode.cn/problems/find-missing-observations/solutions/1368819/zhao-chu-que-shi-de-guan-ce-shu-ju-by-le-0z7j/)

<details><summary>Description</summary>

```text
You have observations of n + m 6-sided dice rolls with each face numbered from 1 to 6.
n of the observations went missing, and you only have the observations of m rolls.
Fortunately, you have also calculated the average value of the n + m rolls.

You are given an integer array rolls of length m where rolls[i] is the value of the ith observation.
You are also given the two integers mean and n.

Return an array of length n containing the missing observations
such that the average value of the n + m rolls is exactly mean.
If there are multiple valid answers, return any of them. If no such array exists, return an empty array.

The average value of a set of k numbers is the sum of the numbers divided by k.

Note that mean is an integer, so the sum of the n + m rolls should be divisible by n + m.

Example 1:
Input: rolls = [3,2,4,3], mean = 4, n = 2
Output: [6,6]
Explanation: The mean of all n + m rolls is (3 + 2 + 4 + 3 + 6 + 6) / 6 = 4.

Example 2:
Input: rolls = [1,5,6], mean = 3, n = 4
Output: [2,3,2,2]
Explanation: The mean of all n + m rolls is (1 + 5 + 6 + 2 + 3 + 2 + 2) / 7 = 3.

Example 3:
Input: rolls = [1,2,3,4], mean = 6, n = 4
Output: []
Explanation: It is impossible for the mean to be 6 no matter what the 4 missing rolls are.

Constraints:
m == rolls.length
1 <= n, m <= 10^5
1 <= rolls[i], mean <= 6
```

<details><summary>Hint</summary>

```text
1. What should the sum of the n rolls be?
2. Could you generate an array of size n such that each element is between 1 and 6?
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *missingRolls(int *rolls, int rollsSize, int mean, int n, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;

    int total = mean * (rollsSize + n);
    int i;
    for (i = 0; i < rollsSize; ++i) {
        total -= rolls[i];
    }
    if ((total > (6 * n)) || (total < n)) {
        return pRetVal;
    }

    int average = total / n;
    int index = total % n;

    pRetVal = (int *)malloc(n * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (n * sizeof(int)));
    for (i = 0; i < n; ++i) {
        pRetVal[i] = average;
        if (i < index) {
            pRetVal[i] += 1;
        }
    }
    (*returnSize) = n;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> missingRolls(vector<int>& rolls, int mean, int n) {
        vector<int> retVal;

        int rollsSize = rolls.size();
        int total = mean * (rollsSize + n);
        for (int roll : rolls) {
            total -= roll;
        }
        if ((total > (6 * n)) || (total < n)) {
            return retVal;
        }

        int average = total / n;
        int index = total % n;

        retVal.resize(n, average);
        for (int i = 0; i < index; ++i) {
            retVal[i] += 1;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def missingRolls(self, rolls: List[int], mean: int, n: int) -> List[int]:
        retVal = []

        rollsSize = len(rolls)
        total = mean * (rollsSize + n)
        for roll in rolls:
            total -= roll
        if (total > (6 * n)) or (total < n):
            return retVal

        average = total // n
        index = total % n

        retVal = [average] * n
        for i in range(index):
            retVal[i] += 1

        return retVal
```

</details>

## [2081. Sum of k-Mirror Numbers](https://leetcode.com/problems/sum-of-k-mirror-numbers/)  2209

- [Official](https://leetcode.com/problems/sum-of-k-mirror-numbers/editorial/)
- [Official](https://leetcode.cn/problems/sum-of-k-mirror-numbers/solutions/1115277/k-jing-xiang-shu-zi-de-he-by-leetcode-so-nyos/)

<details><summary>Description</summary>

```text
A k-mirror number is a positive integer without leading zeros
that reads the same both forward and backward in base-10 as well as in base-k.
- For example, 9 is a 2-mirror number.
  The representation of 9 in base-10 and base-2 are 9 and 1001 respectively,
  which read the same both forward and backward.
- On the contrary, 4 is not a 2-mirror number.
  The representation of 4 in base-2 is 100,
  which does not read the same both forward and backward.

Given the base k and the number n, return the sum of the n smallest k-mirror numbers.

Example 1:
Input: k = 2, n = 5
Output: 25
Explanation:
The 5 smallest 2-mirror numbers and their representations in base-2 are listed as follows:
  base-10    base-2
    1          1
    3          11
    5          101
    7          111
    9          1001
Their sum = 1 + 3 + 5 + 7 + 9 = 25.

Example 2:
Input: k = 3, n = 7
Output: 499
Explanation:
The 7 smallest 3-mirror numbers are and their representations in base-3 are listed as follows:
  base-10    base-3
    1          1
    2          2
    4          11
    8          22
    121        11111
    151        12121
    212        21212
Their sum = 1 + 2 + 4 + 8 + 121 + 151 + 212 = 499.

Example 3:
Input: k = 7, n = 17
Output: 20379000
Explanation: The 17 smallest 7-mirror numbers are:
1, 2, 3, 4, 5, 6, 8, 121, 171, 242, 292, 16561, 65656, 2137312, 4602064, 6597956, 6958596

Constraints:
2 <= k <= 9
1 <= n <= 30
```

<details><summary>Hint</summary>

```text
1. Since we need to reduce search space,
   instead of checking if every number is a palindrome in base-10, can we try to "generate" the palindromic numbers?
2. If you are provided with a d digit number, how can you generate a palindrome with 2*d or 2*d - 1 digit?
3. Try brute-forcing and checking if the palindrome you generated is a "k-Mirror" number.
```

</details>

</details>

<details><summary>C</summary>

```c
#if 0
// 2 <= k <= 9, 1 <= n <= 30
static const long answer[8][30] = {
    {1,       3,       5,       7,       9,       33,      99,       313,       585,       717,
     7447,    9009,    15351,   32223,   39993,   53235,   53835,    73737,     585585,    1758571,
     1934391, 1979791, 3129213, 5071705, 5259525, 5841485, 13500531, 719848917, 910373019, 939474939},
    {1,       2,       4,       8,       121,     151,     212,     242,     484,      656,
     757,     29092,   48884,   74647,   75457,   76267,   92929,   93739,   848848,   1521251,
     2985892, 4022204, 4219124, 4251524, 4287824, 5737375, 7875787, 7949497, 27711772, 83155138},
    {1,       2,       3,       5,       55,      373,     393,      666,       787,       939,
     7997,    53235,   55255,   55655,   57675,   506605,  1801081,  2215122,   3826283,   3866683,
     5051505, 5226225, 5259525, 5297925, 5614165, 5679765, 53822835, 623010326, 954656459, 51717171715},
    {1,          2,          3,          4,          6,           88,         252,       282,
     626,        676,        1221,       15751,      18881,       10088001,   10400401,  27711772,
     30322303,   47633674,   65977956,   808656808,  831333138,   831868138,  836131638, 836181638,
     2512882152, 2596886952, 2893553982, 6761551676, 12114741121, 12185058121},
    {1,      2,      3,      4,       5,       7,       55,      111,     141,     191,
     343,    434,    777,    868,     1441,    7667,    7777,    22022,   39893,   74647,
     168861, 808808, 909909, 1867681, 3097903, 4232324, 4265624, 4298924, 4516154, 4565654},
    {1,         2,           3,           4,           5,           6,          8,         121,
     171,       242,         292,         16561,       65656,       2137312,    4602064,   6597956,
     6958596,   9470749,     61255216,    230474032,   466828664,   485494584,  638828836, 657494756,
     858474858, 25699499652, 40130703104, 45862226854, 61454945416, 64454545446},
    {1,     2,     3,      4,      5,      6,       7,       9,       121,     292,
     333,   373,   414,    585,    3663,   8778,    13131,   13331,   26462,   26662,
     30103, 30303, 207702, 628826, 660066, 1496941, 1935391, 1970791, 4198914, 55366355},
    {1,      2,       3,       4,       5,       6,       7,       8,       191,     282,
     373,    464,     555,     646,     656,     6886,    25752,   27472,   42324,   50605,
     626626, 1540451, 1713171, 1721271, 1828281, 1877781, 1885881, 2401042, 2434342, 2442442}};
#endif
bool isPalindrome(int64_t x, int k, int* digit) {
    bool retVal = true;

    int length = -1;
    while (x > 0) {
        ++length;
        digit[length] = x % k;
        x /= k;
    }

    for (int i = 0, j = length; i < j; ++i, --j) {
        if (digit[i] != digit[j]) {
            retVal = false;
            break;
        }
    }

    return retVal;
}
long long kMirror(int k, int n) {
    long long retVal = 0;

    int digit[100];
    memset(digit, 0, sizeof(digit));
    int left = 1;
    int count = 0;
    while (count < n) {
        int right = left * 10;

        // op = 0 indicates enumerating odd-length palindromes
        // op = 1 indicates enumerating even-length palindromes
        for (int op = 0; op < 2; ++op) {
            for (int i = left; i < right && count < n; ++i) {
                int64_t combined = i;

                int x = (op == 0 ? i / 10 : i);
                while (x > 0) {
                    combined = combined * 10 + x % 10;
                    x /= 10;
                }

                if (isPalindrome(combined, k, digit)) {
                    ++count;
                    retVal += combined;
                }
            }
        }

        left = right;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    // 2 <= k <= 9, 1 <= n <= 30
    static constexpr long long answer[][30] = {
        {1,       3,       5,       7,       9,       33,      99,       313,       585,       717,
         7447,    9009,    15351,   32223,   39993,   53235,   53835,    73737,     585585,    1758571,
         1934391, 1979791, 3129213, 5071705, 5259525, 5841485, 13500531, 719848917, 910373019, 939474939},
        {1,       2,       4,       8,       121,     151,     212,     242,     484,      656,
         757,     29092,   48884,   74647,   75457,   76267,   92929,   93739,   848848,   1521251,
         2985892, 4022204, 4219124, 4251524, 4287824, 5737375, 7875787, 7949497, 27711772, 83155138},
        {1,       2,       3,       5,       55,      373,     393,      666,       787,       939,
         7997,    53235,   55255,   55655,   57675,   506605,  1801081,  2215122,   3826283,   3866683,
         5051505, 5226225, 5259525, 5297925, 5614165, 5679765, 53822835, 623010326, 954656459, 51717171715},
        {1,          2,          3,          4,          6,           88,         252,       282,
         626,        676,        1221,       15751,      18881,       10088001,   10400401,  27711772,
         30322303,   47633674,   65977956,   808656808,  831333138,   831868138,  836131638, 836181638,
         2512882152, 2596886952, 2893553982, 6761551676, 12114741121, 12185058121},
        {1,      2,      3,      4,       5,       7,       55,      111,     141,     191,
         343,    434,    777,    868,     1441,    7667,    7777,    22022,   39893,   74647,
         168861, 808808, 909909, 1867681, 3097903, 4232324, 4265624, 4298924, 4516154, 4565654},
        {1,         2,           3,           4,           5,           6,          8,         121,
         171,       242,         292,         16561,       65656,       2137312,    4602064,   6597956,
         6958596,   9470749,     61255216,    230474032,   466828664,   485494584,  638828836, 657494756,
         858474858, 25699499652, 40130703104, 45862226854, 61454945416, 64454545446},
        {1,     2,     3,      4,      5,      6,       7,       9,       121,     292,
         333,   373,   414,    585,    3663,   8778,    13131,   13331,   26462,   26662,
         30103, 30303, 207702, 628826, 660066, 1496941, 1935391, 1970791, 4198914, 55366355},
        {1,      2,       3,       4,       5,       6,       7,       8,       191,     282,
         373,    464,     555,     646,     656,     6886,    25752,   27472,   42324,   50605,
         626626, 1540451, 1713171, 1721271, 1828281, 1877781, 1885881, 2401042, 2434342, 2442442}};
    int digit[100];

    bool isPalindrome(long long x, int k, int digit[]) {
        bool retVal = true;

        int length = -1;
        while (x) {
            ++length;
            digit[length] = x % k;
            x /= k;
        }

        for (int i = 0, j = length; i < j; ++i, --j) {
            if (digit[i] != digit[j]) {
                retVal = false;
                break;
            }
        }

        return retVal;
    }

   public:
    long long kMirror(int k, int n) {
        long long retVal = 0;

        int left = 1;
        int count = 0;
        while (count < n) {
            int right = left * 10;

            // op = 0 indicates enumerating odd-length palindromes
            // op = 1 indicates enumerating even-length palindromes
            for (int op = 0; op < 2; ++op) {
                for (int i = left; i < right && count < n; ++i) {
                    long long combined = i;

                    int x = (op == 0 ? i / 10 : i);
                    while (x) {
                        combined = combined * 10 + x % 10;
                        x /= 10;
                    }

                    if (isPalindrome(combined, k, digit) == true) {
                        ++count;
                        retVal += combined;
                    }
                }
            }

            left = right;
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
        # 2 <= k <= 9, 1 <= n <= 30
        self.answer = [
            [
                1, 3, 5, 7, 9, 33, 99, 313, 585, 717,
                7447, 9009, 15351, 32223, 39993, 53235, 53835, 73737, 585585, 1758571,
                1934391, 1979791, 3129213, 5071705, 5259525, 5841485, 13500531, 719848917, 910373019, 939474939,],
            [
                1, 2, 4, 8, 121, 151, 212, 242, 484, 656,
                757, 29092, 48884, 74647, 75457, 76267, 92929, 93739, 848848, 1521251,
                2985892, 4022204, 4219124, 4251524, 4287824, 5737375, 7875787, 7949497, 27711772, 83155138,
            ],
            [
                1, 2, 3, 5, 55, 373, 393, 666, 787, 939,
                7997, 53235, 55255, 55655, 57675, 506605, 1801081, 2215122, 3826283, 3866683,
                5051505, 5226225, 5259525, 5297925, 5614165, 5679765, 53822835, 623010326, 954656459, 51717171715,
            ],
            [
                1, 2, 3, 4, 6, 88, 252, 282, 626, 676,
                1221, 15751, 18881, 10088001, 10400401, 27711772, 30322303, 47633674, 65977956, 808656808,
                831333138, 831868138, 836131638, 836181638, 2512882152, 2596886952, 2893553982, 6761551676, 12114741121, 12185058121,
            ],
            [
                1, 2, 3, 4, 5, 7, 55, 111, 141, 191,
                343, 434, 777, 868, 1441, 7667, 7777, 22022, 39893, 74647,
                168861, 808808, 909909, 1867681, 3097903, 4232324, 4265624, 4298924, 4516154, 4565654,
            ],
            [
                1, 2, 3, 4, 5, 6, 8, 121, 171, 242,
                292, 16561, 65656, 2137312, 4602064, 6597956, 6958596, 9470749, 61255216, 230474032,
                466828664, 485494584, 638828836, 657494756, 858474858, 25699499652, 40130703104, 45862226854, 61454945416, 64454545446,
            ],
            [
                1, 2, 3, 4, 5, 6, 7, 9, 121, 292,
                333, 373, 414, 585, 3663, 8778, 13131, 13331, 26462, 26662,
                30103, 30303, 207702, 628826, 660066, 1496941, 1935391, 1970791, 4198914, 55366355,
            ],
            [
                1, 2, 3, 4, 5, 6, 7, 8, 191, 282,
                373, 464, 555, 646, 656, 6886, 25752, 27472, 42324, 50605,
                626626, 1540451, 1713171, 1721271, 1828281, 1877781, 1885881, 2401042, 2434342, 2442442,
            ],
        ]

    def isPalindrome(self, k: int, x: int) -> bool:
        retVal = False

        digit = list()
        while x:
            digit.append(x % k)
            x //= k
        retVal = (digit == digit[::-1])

        return retVal

    def kMirror(self, k: int, n: int) -> int:
        retVal = 0

        left = 1
        cnt = 0
        while cnt < n:
            right = left * 10

            # op = 0 indicates enumerating odd-length palindromes
            # op = 1 indicates enumerating even-length palindromes
            for op in [0, 1]:
                for i in range(left, right):
                    if cnt == n:
                        break
                    combined = i

                    x = i
                    if op == 0:
                        x = i // 10
                    while x:
                        combined = combined * 10 + x % 10
                        x //= 10

                    if self.isPalindrome(k, combined) == True:
                        cnt += 1
                        retVal += combined

            left = right

        return retVal
```

</details>

## [2125. Number of Laser Beams in a Bank](https://leetcode.com/problems/number-of-laser-beams-in-a-bank/)  1280

- [Official](https://leetcode.com/problems/number-of-laser-beams-in-a-bank/editorial)

<details><summary>Description</summary>

```text
Anti-theft security devices are activated inside a bank.
You are given a 0-indexed binary string array bank representing the floor plan of the bank, which is an m x n 2D matrix.
bank[i] represents the ith row, consisting of '0's and '1's.
'0' means the cell is empty, while'1' means the cell has a security device.

There is one laser beam between any two security devices if both conditions are met:
- The two devices are located on two different rows: r1 and r2, where r1 < r2.
- For each row i where r1 < i < r2, there are no security devices in the ith row.

Laser beams are independent, i.e., one beam does not interfere nor join with another.

Return the total number of laser beams in the bank.

Example 1:
Input: bank = ["011001","000000","010100","001000"]
Output: 8
Explanation: Between each of the following device pairs, there is one beam. In total, there are 8 beams:
 * bank[0][1] -- bank[2][1]
 * bank[0][1] -- bank[2][3]
 * bank[0][2] -- bank[2][1]
 * bank[0][2] -- bank[2][3]
 * bank[0][5] -- bank[2][1]
 * bank[0][5] -- bank[2][3]
 * bank[2][1] -- bank[3][2]
 * bank[2][3] -- bank[3][2]
Note that there is no beam between any device on the 0th row with any on the 3rd row.
This is because the 2nd row contains security devices, which breaks the second condition.

Example 2:
Input: bank = ["000","111","000"]
Output: 0
Explanation: There does not exist two devices located on two different rows.

Constraints:
m == bank.length
n == bank[i].length
1 <= m, n <= 500
bank[i][j] is either '0' or '1'.
```

<details><summary>Hint</summary>

```text
1. What is the commonality between security devices on the same row?
2. Each device on the same row has the same number of beams pointing towards the devices on the next row with devices.
3. If you were given an integer array where each element is the number of security devices on each row, can you solve it?
4. Convert the input to such an array, skip any row with no security device,
   then find the sum of the product between adjacent elements.
```

</details>

</details>

<details><summary>C</summary>

```c
int numberOfBeams(char** bank, int bankSize) {
    int retVal = 0;

    int previous = 0;
    int count, len;
    int i, j;
    for (i = 0; i < bankSize; ++i) {
        count = 0;
        len = strlen(bank[i]);
        for (j = 0; j < len; ++j) {
            if (bank[i][j] == '1') {
                count++;
            }
        }

        if (count != 0) {
            retVal += (previous * count);
            previous = count;
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
    int numberOfBeams(vector<string>& bank) {
        int retVal = 0;

        int previous = 0;
        for (string row : bank) {
            int count = 0;
            for (char c : row) {
                if (c == '1') {
                    count++;
                }
            }

            if (count != 0) {
                retVal += (previous * count);
                previous = count;
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
    def numberOfBeams(self, bank: List[str]) -> int:
        retVal = 0

        previous = 0
        for row in bank:
            count1 = Counter(row)['1']
            if count1 != 0:
                retVal += (previous * count1)
                previous = count1

        return retVal
```

</details>

## [2147. Number of Ways to Divide a Long Corridor](https://leetcode.com/problems/number-of-ways-to-divide-a-long-corridor/)  1914

- [Official](https://leetcode.com/problems/number-of-ways-to-divide-a-long-corridor/editorial/)
- [Official](https://leetcode.cn/problems/number-of-ways-to-divide-a-long-corridor/solutions/1231280/fen-ge-chang-lang-de-fang-an-shu-by-leet-p9wr/)

<details><summary>Description</summary>

```text
Along a long library corridor, there is a line of seats and decorative plants.
You are given a 0-indexed string corridor of length n consisting of letters 'S' and 'P'
where each 'S' represents a seat and each 'P' represents a plant.

One room divider has already been installed to the left of index 0, and another to the right of index n - 1.
Additional room dividers can be installed.
For each position between indices i - 1 and i (1 <= i <= n - 1), at most one divider can be installed.

Divide the corridor into non-overlapping sections, where each section has exactly two seats with any number of plants.
There may be multiple ways to perform the division.
Two ways are different if there is a position with a room divider installed in the first way but not in the second way.

Return the number of ways to divide the corridor. Since the answer may be very large, return it modulo 109 + 7.
If there is no way, return 0.

Example 1:
Input: corridor = "SSPPSPS"
Output: 3
Explanation: There are 3 different ways to divide the corridor.
The black bars in the above image indicate the two room dividers already installed.
Note that in each of the ways, each section has exactly two seats.

Example 2:
Input: corridor = "PPSPSP"
Output: 1
Explanation: There is only 1 way to divide the corridor, by not installing any additional dividers.
Installing any would create some section that does not have exactly two seats.

Example 3:
Input: corridor = "S"
Output: 0
Explanation: There is no way to divide the corridor
because there will always be a section that does not have exactly two seats.

Constraints:
n == corridor.length
1 <= n <= 10^5
corridor[i] is either 'S' or 'P'.
```

<details><summary>Hint</summary>

```text
1. Divide the corridor into segments.
   Each segment has two seats, starts precisely with one seat, and ends precisely with the other seat.
2. How many dividers can you install between two adjacent segments?
   You must install precisely one. Otherwise, you would have created a section with not exactly two seats.
3. If there are k plants between two adjacent segments,
   there are k + 1 positions (ways) you could install the divider you must install.
4. The problem now becomes: Find the product of all possible positions between every two adjacent segments.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MODULO (int)(1e9 + 7)
int numberOfWays(char* corridor) {
    int retVal = 0;

    int corridorSize = strlen(corridor);

    long answer = 1;
    int count = 0;
    int previous = -1;
    for (int i = 0; i < corridorSize; ++i) {
        if (corridor[i] == 'S') {
            count++;

            if ((count >= 3) && (count % 2 == 1)) {
                answer = (answer * (i - previous)) % MODULO;
            }

            previous = i;
        }
    }

    if ((count < 2) || (count % 2 == 1)) {
        answer = 0;
    }
    retVal = answer;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define MODULO (int)(1e9 + 7)
   public:
    int numberOfWays(string corridor) {
        int retVal = 0;

        int corridorSize = corridor.size();

        long answer = 1;
        int count = 0;
        int previous = -1;
        for (int i = 0; i < corridorSize; ++i) {
            if (corridor[i] == 'S') {
                count++;

                if ((count >= 3) && (count % 2 == 1)) {
                    answer = (answer * (i - previous)) % MODULO;
                }

                previous = i;
            }
        }

        if ((count < 2) || (count % 2 == 1)) {
            answer = 0;
        }
        retVal = answer;

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

    def numberOfWays(self, corridor: str) -> int:
        retVal = 1

        count = 0
        previous = -1
        for index, value in enumerate(corridor):
            if value == "S":
                count += 1

                if (count >= 3) and (count % 2 == 1):
                    retVal = (retVal * (index - previous)) % self.MODULO

                previous = index

        if (count < 2) or (count % 2 == 1):
            retVal = 0

        return retVal
```

</details>

## [2180. Count Integers With Even Digit Sum](https://leetcode.com/problems/count-integers-with-even-digit-sum/)  1257

- [Official](https://leetcode.cn/problems/count-integers-with-even-digit-sum/solutions/2045888/tong-ji-ge-wei-shu-zi-zhi-he-wei-ou-shu-rvqol/)

<details><summary>Description</summary>

```text
Given a positive integer num, return the number of positive integers less than or equal to num whose digit sums are even.

The digit sum of a positive integer is the sum of all its digits.

Example 1:
Input: num = 4
Output: 2
Explanation:
The only integers less than or equal to 4 whose digit sums are even are 2 and 4.

Example 2:
Input: num = 30
Output: 14
Explanation:
The 14 integers less than or equal to 30 whose digit sums are even are
2, 4, 6, 8, 11, 13, 15, 17, 19, 20, 22, 24, 26, and 28.

Constraints:
1 <= num <= 1000
```

</details>

<details><summary>C</summary>

```c
#define MATH (1)
#define BRUTE_FORCE (1)
int countEven(int num) {
    int retVal = 0;

#if (MATH)
    printf("MATH\n");

    /* Math
     *  nums = xyz, sum of digits = x + y + z.
     *  if x + y + z is even, the even digit sums is nums / 2.
     *  if x + y + z is odd, the even digit sums is (nums - 1) / 2.
     */
    int sum = 0;
    int tmp = num;
    while (tmp > 0) {
        sum += (tmp % 10);
        tmp /= 10;
    }

    if (sum % 2 == 0) {
        retVal = num / 2;
    } else {
        retVal = (num - 1) / 2;
    }
#elif (BRUTE_FORCE)
    printf("BRUTE_FORCE\n");

    int tmp;
    int sum;
    int i;
    for (i = 2; i <= num; ++i) {
        sum = 0;
        tmp = i;
        while (tmp > 0) {
            sum += (tmp % 10);
            tmp /= 10;
        }
        if (sum % 2 == 0) {
            ++retVal;
        }
    }
#endif

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define MATH (1)
#define BRUTE_FORCE (1)
   public:
    int countEven(int num) {
        int retVal = 0;

#if (MATH)
        cout << "MATH\n";

        /* Math
         *  nums = xyz, sum of digits = x + y + z.
         *  if x + y + z is even, the even digit sums is nums / 2.
         *  if x + y + z is odd, the even digit sums is (nums - 1) / 2.
         */
        int sum = 0;
        int tmp = num;
        while (tmp > 0) {
            sum += (tmp % 10);
            tmp /= 10;
        }

        if (sum % 2 == 0) {
            retVal = num / 2;
        } else {
            retVal = (num - 1) / 2;
        }
#elif (BRUTE_FORCE)
        cout << "BRUTE_FORCE\n";

        for (int i = 2; i <= num; ++i) {
            int sum = 0;
            int tmp = i;
            while (tmp > 0) {
                sum += (tmp % 10);
                tmp /= 10;
            }
            if (sum % 2 == 0) {
                ++retVal;
            }
        }
#endif

        return retVal;
    }
};
```

</details>

## [2235. Add Two Integers](https://leetcode.com/problems/add-two-integers/)

<details><summary>Description</summary>

```text
Given two integers num1 and num2, return the sum of the two integers.

Example 1:
Input: num1 = 12, num2 = 5
Output: 17
Explanation: num1 is 12, num2 is 5, and their sum is 12 + 5 = 17, so 17 is returned.

Example 2:
Input: num1 = -10, num2 = 4
Output: -6
Explanation: num1 + num2 = -6, so -6 is returned.

Constraints:
-100 <= num1, num2 <= 100
```

</details>

<details><summary>C</summary>

```c
int sum(int num1, int num2){
    int retVal = num1 + num2;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int sum(int num1, int num2) {
        int retVal = num1 + num2;

        return retVal;
    }
};
```

</details>

<details><summary>Rust</summary>

```rust
impl Solution {
    pub fn sum(num1: i32, num2: i32) -> i32 {
        let retVal = num1 + num2;

        return retVal;
    }
}
```

</details>

## [2338. Count the Number of Ideal Arrays](https://leetcode.com/problems/count-the-number-of-ideal-arrays/)  2615

- [Official](https://leetcode.com/problems/count-the-number-of-ideal-arrays/editorial/)
- [Official](https://leetcode.cn/problems/count-the-number-of-ideal-arrays/solutions/3650511/tong-ji-li-xiang-shu-zu-de-shu-mu-by-lee-usvr/)

<details><summary>Description</summary>

```text
You are given two integers n and maxValue, which are used to describe an ideal array.

A 0-indexed integer array arr of length n is considered ideal if the following conditions hold:
- Every arr[i] is a value from 1 to maxValue, for 0 <= i < n.
- Every arr[i] is divisible by arr[i - 1], for 0 < i < n.

Return the number of distinct ideal arrays of length n. Since the answer may be very large, return it modulo 10^9 + 7.

Example 1:
Input: n = 2, maxValue = 5
Output: 10
Explanation: The following are the possible ideal arrays:
- Arrays starting with the value 1 (5 arrays): [1,1], [1,2], [1,3], [1,4], [1,5]
- Arrays starting with the value 2 (2 arrays): [2,2], [2,4]
- Arrays starting with the value 3 (1 array): [3,3]
- Arrays starting with the value 4 (1 array): [4,4]
- Arrays starting with the value 5 (1 array): [5,5]
There are a total of 5 + 2 + 1 + 1 + 1 = 10 distinct ideal arrays

Example 2:
Input: n = 5, maxValue = 3
Output: 11
Explanation: The following are the possible ideal arrays:
- Arrays starting with the value 1 (9 arrays):
   - With no other distinct values (1 array): [1,1,1,1,1]
   - With 2nd distinct value 2 (4 arrays): [1,1,1,1,2], [1,1,1,2,2], [1,1,2,2,2], [1,2,2,2,2]
   - With 2nd distinct value 3 (4 arrays): [1,1,1,1,3], [1,1,1,3,3], [1,1,3,3,3], [1,3,3,3,3]
- Arrays starting with the value 2 (1 array): [2,2,2,2,2]
- Arrays starting with the value 3 (1 array): [3,3,3,3,3]
There are a total of 9 + 1 + 1 = 11 distinct ideal arrays.

Constraints:
2 <= n <= 10^4
1 <= maxValue <= 10^4
```

<details><summary>Hint</summary>

```text
1. Notice that an ideal array is non-decreasing.
2. Consider an alternative problem: where an ideal array must also be strictly increasing. Can you use DP to solve it?
3. Will combinatorics help to get an answer from the alternative problem to the actual problem?
```

</details>

</details>

<details><summary>C</summary>

```c
#define MODULO (int)(1e9 + 7)
#define MAX_N (10010)
#define MAX_P (15)  // There are up to 15 prime factors
int c[MAX_N + MAX_P][MAX_P + 1];
int sieve[MAX_N];                    // Minimum prime factor
int ps[MAX_N][MAX_P], psLen[MAX_N];  // List of prime factor counts
void init() {
    if (c[0][0]) {
        return;
    }

    for (int i = 2; i < MAX_N; i++) {
        if (sieve[i] != 0) {
            continue;
        }
        for (int j = i; j < MAX_N; j += i) {
            if (sieve[j] == 0) {
                sieve[j] = i;
            }
        }
    }

    for (int i = 2; i < MAX_N; i++) {
        int x = i;
        psLen[i] = 0;
        while (x > 1) {
            int p = sieve[x];
            int cnt = 0;
            while (x % p == 0) {
                x /= p;
                cnt++;
            }
            ps[i][psLen[i]++] = cnt;
        }
    }

    c[0][0] = 1;
    for (int i = 1; i < MAX_N + MAX_P; i++) {
        c[i][0] = 1;
        for (int j = 1; j <= MAX_P && j <= i; j++) {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MODULO;
        }
    }
}
int idealArrays(int n, int maxValue) {
    int retVal = 0;

    init();
    long long ans = 0;
    for (int x = 1; x <= maxValue; x++) {
        long long mul = 1;
        for (int i = 0; i < psLen[x]; i++) {
            mul = mul * c[n + ps[x][i] - 1][ps[x][i]] % MODULO;
        }
        ans = (ans + mul) % MODULO;
    }
    retVal = ans;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
#define MODULO (int)(1e9 + 7)
#define MAX_N (int)(1e4 + 10)
#define MAX_P (15)      // There are up to 15 prime factors
int sieve[MAX_N];       // Minimum prime factor
vector<int> ps[MAX_N];  // List of prime factor counts
int c[MAX_N + MAX_P][MAX_P + 1];
class Solution {
   public:
    Solution() {
        if (c[0][0]) {
            return;
        }

        for (int i = 2; i < MAX_N; i++) {
            if (sieve[i] != 0) {
                continue;
            }
            for (int j = i; j < MAX_N; j += i) {
                sieve[j] = i;
            }
        }

        for (int i = 2; i < MAX_N; i++) {
            int x = i;
            while (x > 1) {
                int p = sieve[x];
                int cnt = 0;
                while (x % p == 0) {
                    x /= p;
                    cnt++;
                }
                ps[i].push_back(cnt);
            }
        }

        c[0][0] = 1;
        for (int i = 1; i < MAX_N + MAX_P; i++) {
            c[i][0] = 1;
            for (int j = 1; j <= min(i, MAX_P); j++) {
                c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MODULO;
            }
        }
    }
    int idealArrays(int n, int maxValue) {
        int retVal = 0;

        long long ans = 0;
        for (int x = 1; x <= maxValue; x++) {
            long long mul = 1;
            for (int p : ps[x]) {
                mul = mul * c[n + p - 1][p] % MODULO;
            }
            ans = (ans + mul) % MODULO;
        }
        retVal = ans;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def __init__(self) -> None:
        self.MODULO = 10 ** 9 + 7
        self.MAX_N = 10**4 + 10
        self.MAX_P = 15  # There are up to 15 prime factors

        self.sieve = [0] * self.MAX_N  # // Minimum prime factor
        for i in range(2, self.MAX_N):
            if self.sieve[i] != 0:
                continue
            for j in range(i, self.MAX_N, i):
                self.sieve[j] = i

        self.ps = [[] for _ in range(self.MAX_N)]
        for i in range(2, self.MAX_N):
            x = i
            while x > 1:
                p = self.sieve[x]
                cnt = 0
                while x % p == 0:
                    x //= p
                    cnt += 1
                self.ps[i].append(cnt)

        self.c = [[0] * (self.MAX_P + 1) for _ in range(self.MAX_N + self.MAX_P)]
        self.c[0][0] = 1
        for i in range(1, self.MAX_N + self.MAX_P):
            self.c[i][0] = 1
            for j in range(1, min(i, self.MAX_P) + 1):
                self.c[i][j] = (self.c[i - 1][j] + self.c[i - 1][j - 1]) % self.MODULO

    def idealArrays(self, n: int, maxValue: int) -> int:
        retVal = 0

        for x in range(1, maxValue + 1):
            mul = 1
            for p in self.ps[x]:
                mul = mul * self.c[n + p - 1][p] % self.MODULO
            retVal = (retVal + mul) % self.MODULO

        return retVal
```

</details>

## [2413. Smallest Even Multiple](https://leetcode.com/problems/smallest-even-multiple/)  1144

- [Official](https://leetcode.cn/problems/smallest-even-multiple/solutions/2236371/zui-xiao-ou-bei-shu-by-leetcode-solution-vy2o/)

<details><summary>Description</summary>

```text
Given a positive integer n, return the smallest positive integer that is a multiple of both 2 and n.

Example 1:
Input: n = 5
Output: 10
Explanation: The smallest multiple of both 5 and 2 is 10.

Example 2:
Input: n = 6
Output: 6
Explanation: The smallest multiple of both 6 and 2 is 6. Note that a number is a multiple of itself.

Constraints:
1 <= n <= 150
```

<details><summary>Hint</summary>

```text
1. A guaranteed way to find a multiple of 2 and n is to multiply them together.
   When is this the answer, and when is there a smaller answer?
2. There is a smaller answer when n is even.
```

</details>

</details>

<details><summary>C</summary>

```c
int smallestEvenMultiple(int n) {
    int retVal = 0;

#if (1)
    retVal = n << (n & 1);
#else
    retVal = n;
    if (n % 2 == 1) {
        retVal = n * 2;
    }
#endif

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int smallestEvenMultiple(int n) {
        int retVal = 0;

#if (1)
        retVal = n << (n & 1);
#else
        retVal = n;
        if (n % 2 == 1) {
            retVal = n * 2;
        }
#endif

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def smallestEvenMultiple(self, n: int) -> int:
        retVal = 0

        retVal = n << (n & 1)
        # retVal = n
        # if n % 2 == 1:
        #     retVal = n * 2

        return retVal
```

</details>

## [2485. Find the Pivot Integer](https://leetcode.com/problems/find-the-pivot-integer/)  1207

- [Official](https://leetcode.com/problems/find-the-pivot-integer/editorial/)
- [Official](https://leetcode.cn/problems/find-the-pivot-integer/solutions/2306030/zhao-chu-zhong-shu-zheng-shu-by-leetcode-t7gn/)

<details><summary>Description</summary>

```text
Given a positive integer n, find the pivot integer x such that:
- The sum of all elements between 1 and x inclusively equals the sum of all elements between x and n inclusively.
Return the pivot integer x. If no such integer exists, return -1.
It is guaranteed that there will be at most one pivot index for the given input.

Example 1:
Input: n = 8
Output: 6
Explanation: 6 is the pivot integer since: 1 + 2 + 3 + 4 + 5 + 6 = 6 + 7 + 8 = 21.

Example 2:
Input: n = 1
Output: 1
Explanation: 1 is the pivot integer since: 1 = 1.

Example 3:
Input: n = 4
Output: -1
Explanation: It can be proved that no such integer exist.

Constraints:
1 <= n <= 1000
```

<details><summary>Hint</summary>

```text
1. Can you use brute force to check every number from 1 to n if any of them is the pivot integer?
2. If you know the sum of [1: pivot], how can you efficiently calculate the sum of the other parts?
```

</details>

</details>

<details><summary>C</summary>

```c
int pivotInteger(int n) {
    int retVal = -1;

    /* 1 + 2 + ... + x = x + ... + n
     * => x * (x+1) / 2 = (n-x+1) * (n+x) / 2
     * => 2 * x^2 = n^2 + n
     * => x = ((n^2 + n) / 2)^(1/2)
     * => x = ((n * (n+1) / 2))^(1/2)
     */
    int sum = n * (n + 1) / 2;
    int x = sqrt(sum);
    if (x * x == sum) {
        retVal = x;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int pivotInteger(int n) {
        int retVal = -1;

        /* 1 + 2 + ... + x = x + ... + n
         * => x * (x+1) / 2 = (n-x+1) * (n+x) / 2
         * => 2 * x^2 = n^2 + n
         * => x = ((n^2 + n) / 2)^(1/2)
         * => x = ((n * (n+1) / 2))^(1/2)
         */
        int sum = n * (n + 1) / 2;
        int x = sqrt(sum);
        if (x * x == sum) {
            retVal = x;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def pivotInteger(self, n: int) -> int:
        retVal = -1

        # 1 + 2 + ... + x = x + ... + n
        # => x * (x+1) / 2 = (n-x+1) * (n+x) / 2
        # => 2 * x^2 = n^2 + n
        # => x = ((n^2 + n) / 2)^(1/2)
        # => x = ((n * (n+1) / 2))^(1/2)
        sum = n * (n + 1) // 2
        x = int(sqrt(sum))
        if x * x == sum:
            retVal = x

        return retVal
```

</details>

## [2523. Closest Prime Numbers in Range](https://leetcode.com/problems/closest-prime-numbers-in-range/)  1649

- [Official](https://leetcode.com/problems/closest-prime-numbers-in-range/editorial/)

<details><summary>Description</summary>

```text
Given two positive integers left and right, find the two integers num1 and num2 such that:
- left <= num1 < num2 <= right .
- Both num1 and num2 are prime numbers.
- num2 - num1 is the minimum amongst all other pairs satisfying the above conditions.

Return the positive integer array ans = [num1, num2]. If there are multiple pairs satisfying these conditions,
return the one with the smallest num1 value. If no such numbers exist, return [-1, -1].

Example 1:
Input: left = 10, right = 19
Output: [11,13]
Explanation: The prime numbers between 10 and 19 are 11, 13, 17, and 19.
The closest gap between any pair is 2, which can be achieved by [11,13] or [17,19].
Since 11 is smaller than 17, we return the first pair.

Example 2:
Input: left = 4, right = 6
Output: [-1,-1]
Explanation: There exists only one prime number in the given range, so the conditions cannot be satisfied.

Constraints:
1 <= left <= right <= 10^6
```

<details><summary>Hint</summary>

```text
1. Use Sieve of Eratosthenes to mark numbers that are primes.
2. Iterate from right to left and find pair with the minimum distance between marked numbers.
```

</details>

</details>

<details><summary>C</summary>

```c
#define NOT_PRIME (1)
void sieve(int upperLimit, int* sieveArray) {
    // 0 and 1 are not prime
    sieveArray[0] = NOT_PRIME;
    sieveArray[1] = NOT_PRIME;

    for (int number = 2; number * number <= upperLimit; number++) {
        if (sieveArray[number] == NOT_PRIME) {
            continue;
        }

        // Mark all multiples of 'number' as non-prime
        for (int multiple = number * number; multiple <= upperLimit; multiple += number) {
            sieveArray[multiple] = NOT_PRIME;
        }
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* closestPrimes(int left, int right, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int*)calloc(2, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }
    pRetVal[0] = -1;
    pRetVal[1] = -1;
    (*returnSize) = 2;

    // Step 1: Get all prime numbers up to 'right' using sieve
    int upperLimit = right;
    int* sieveArray = (int*)calloc((upperLimit + 1), sizeof(int));
    if (sieveArray == NULL) {
        perror("calloc");
        return pRetVal;
    }
    sieve(upperLimit, sieveArray);

    int primeNumbersSize = 0;
    int primeNumbers[right - left + 1];  // Store all primes in the range [left, right]
    memset(primeNumbers, 0, sizeof(primeNumbers));
    for (int num = left; num <= right; num++) {
        // If number is prime add to the primeNumbers list
        if (sieveArray[num] != NOT_PRIME) {
            primeNumbers[primeNumbersSize++] = num;
        }
    }

    // Step 2: Find the closest prime pair
    if (primeNumbersSize < 2) {
        free(sieveArray);
        sieveArray = NULL;
        return pRetVal;
    }

    int minDifference = INT_MAX;
    for (int index = 1; index < primeNumbersSize; index++) {
        int difference = primeNumbers[index] - primeNumbers[index - 1];
        if (difference < minDifference) {
            minDifference = difference;
            pRetVal[0] = primeNumbers[index - 1];
            pRetVal[1] = primeNumbers[index];
        }
    }

    //
    free(sieveArray);
    sieveArray = NULL;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    vector<int> sieve(int upperLimit) {
        vector<int> retVal(upperLimit + 1, 1);  // Initiate an int array to mark prime numbers

        // 0 and 1 are not prime
        retVal[0] = 0;
        retVal[1] = 0;
        for (int number = 2; number * number <= upperLimit; number++) {
            if (retVal[number] == 0) {
                continue;
            }

            // Mark all multiples of 'number' as non-prime
            for (int multiple = number * number; multiple <= upperLimit; multiple += number) {
                retVal[multiple] = 0;
            }
        }

        return retVal;
    }

   public:
    vector<int> closestPrimes(int left, int right) {
        vector<int> retVal(2, -1);

        // Step 1: Get all prime numbers up to 'right' using sieve
        int upperLimit = right;
        vector<int> sieveArray = sieve(upperLimit);

        vector<int> primeNumbers;  // Store all primes in the range [left, right]
        for (int num = left; num <= right; num++) {
            // If number is prime add to the primeNumbers list
            if (sieveArray[num] == 1) {
                primeNumbers.push_back(num);
            }
        }
        int primeNumbersSize = primeNumbers.size();

        // Step 2: Find the closest prime pair
        if (primeNumbersSize < 2) {
            return retVal;
        }

        int minDifference = numeric_limits<int>::max();
        for (int index = 1; index < primeNumbersSize; index++) {
            int difference = primeNumbers[index] - primeNumbers[index - 1];
            if (difference < minDifference) {
                minDifference = difference;
                retVal[0] = primeNumbers[index - 1];
                retVal[1] = primeNumbers[index];
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
    def sieve(self, upperLimit):
        retVal = [True] * (upperLimit + 1)  # True = prime, False = not prime

        # 0 and 1 are not prime
        retVal[0] = False
        retVal[1] = False

        for number in range(2, int(upperLimit**0.5) + 1):
            if retVal[number] == False:
                continue
            for multiple in range(number * number, upperLimit + 1, number):
                retVal[multiple] = False  # Mark all multiples of 'number' as non-prime

        return retVal

    def closestPrimes(self, left: int, right: int) -> List[int]:
        retVal = [-1] * 2

        # Step 1: Get all prime numbers up to 'right' using sieve
        sieveArray = self.sieve(right)
        primeNumbers = []
        for num in range(left, right + 1):
            if sieveArray[num] == True:
                primeNumbers.append(num)

        # Step 2: Find the closest prime pair
        primeNumbersSize = len(primeNumbers)
        if primeNumbersSize < 2:
            return retVal  # Less than two primes

        minDifference = float("inf")
        for index in range(1, primeNumbersSize):
            difference = primeNumbers[index] - primeNumbers[index - 1]
            if difference < minDifference:
                minDifference = difference
                retVal[0] = primeNumbers[index - 1]
                retVal[1] = primeNumbers[index]

        return retVal
```

</details>

## [2544. Alternating Digit Sum](https://leetcode.com/problems/alternating-digit-sum/)  1184

<details><summary>Description</summary>

```text
You are given a positive integer n. Each digit of n has a sign according to the following rules:
- The most significant digit is assigned a positive sign.
- Each other digit has an opposite sign to its adjacent digits.

Return the sum of all digits with their corresponding sign.

Example 1:
Input: n = 521
Output: 4
Explanation: (+5) + (-2) + (+1) = 4.

Example 2:
Input: n = 111
Output: 1
Explanation: (+1) + (-1) + (+1) = 1.

Example 3:
Input: n = 886996
Output: 0
Explanation: (+8) + (-8) + (+6) + (-9) + (+9) + (-6) = 0.

Constraints:
1 <= n <= 10^9
```

</details>

<details><summary>C</summary>

```c
#define REVERSE (1)
#define MATH (1)
int alternateDigitSum(int n) {
    int retVal = 0;

#if (REVERSE)
    printf("REVERSE\n");

    int reverse = 0;
    while (n > 0) {
        reverse = reverse * 10 + (n % 10);
        n /= 10;
    }

    int round = 0;
    while (reverse > 0) {
        if (round % 2 == 0) {
            retVal += (reverse % 10);
        } else {
            retVal -= (reverse % 10);
        }
        ++round;
        reverse /= 10;
    }
#elif (MATH)
    printf("MATH\n");

    /* Alternating Digit Sum
     *  n has odd digit: n = abcde, a - b + c - d + e = (e - d + c - b + a) * (1)
     *  n has even digit: n = abcd, a - b + c - d = (d - c + b - a) * (-1)
     */
    int sign = -1;
    while (n > 0) {
        sign *= (-1);
        retVal += (sign * (n % 10));
        n /= 10;
    }
    retVal *= sign;
#endif

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define REVERSE (1)
#define MATH (1)
   public:
    int alternateDigitSum(int n) {
        int retVal = 0;

        vector<int> nums;
#if (REVERSE)
        cout << "REVERSE\n";

        while (n > 0) {
            nums.push_back(n % 10);
            n /= 10;
        }
        reverse(nums.begin(), nums.end());

        int sign = 1;
        for (auto num : nums) {
            retVal += (sign * num);
            sign *= (-1);
        }
#elif (MATH)
        cout << "MATH\n";

        /* Alternating Digit Sum
         *  n has odd digit: n = abcde, a - b + c - d + e = (e - d + c - b + a) * (1)
         *  n has even digit: n = abcd, a - b + c - d = (d - c + b - a) * (-1)
         */
        int sign = -1;
        while (n > 0) {
            sign *= (-1);
            retVal += (sign * (n % 10));
            n /= 10;
        }
        retVal *= sign;
#endif

        return retVal;
    }
};
```

</details>

<details><summary>Rust</summary>

```rust
impl Solution {
    pub fn alternate_digit_sum(n: i32) -> i32 {
        let mut ret_val: i32 = 0;

        let mut n: i32 = n;
        let mut reverse: i32 = 0;
        while n > 0 {
            reverse = reverse * 10 + n % 10;
            n = n / 10;
        }
        #[cfg(string_reverse)]
        {
            let n: String = format!("{:?}", n);
            let reverse: String = n.chars().rev().collect::<String>();
            let mut reverse: i32 = reverse.parse().unwrap();
        }

        let mut sign: i32 = 1;
        while reverse > 0 {
            ret_val = ret_val + (sign * (reverse % 10));
            sign = sign * (-1);
            reverse = reverse / 10;
        }

        return ret_val;
    }
}
```

</details>

## [2579. Count Total Number of Colored Cells](https://leetcode.com/problems/count-total-number-of-colored-cells/)  1356

- [Official](https://leetcode.com/problems/count-total-number-of-colored-cells/editorial/)

<details><summary>Description</summary>

```text
There exists an infinitely large two-dimensional grid of uncolored unit cells.
You are given a positive integer n, indicating that you must do the following routine for n minutes:
- At the first minute, color any arbitrary unit cell blue.
- Every minute thereafter, color blue every uncolored cell that touches a blue cell.

Below is a pictorial representation of the state of the grid after minutes 1, 2, and 3.
                  3
       2        3 2 3
1 -> 2 1 2 -> 3 2 1 2 3
       2        3 2 3
                  3
Return the number of colored cells at the end of n minutes.

Example 1:
Input: n = 1
Output: 1
Explanation: After 1 minute, there is only 1 blue cell, so we return 1.

Example 2:
Input: n = 2
Output: 5
Explanation: After 2 minutes, there are 4 colored cells on the boundary and 1 in the center, so we return 5.

Constraints:
1 <= n <= 10^5
```

<details><summary>Hint</summary>

```text
1. Derive a mathematical relation between total number of colored cells and the time elapsed in minutes.
```

</details>

</details>

<details><summary>C</summary>

```c
long long coloredCells(int n) {
    long long retVal = 0;

    /*    1 + (4×1) + (4×2) + ... + (4×(n−1))
     *  = 1 + 4 x (1 + 2 + ... + (n-1))
     *  = 1 + 4 x (n x (n-1) / 2)
     *  = 1 + 2 x n x (n-1)
     */
    retVal = 1 + (long long)(2) * (long long)(n) * (long long)(n - 1);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long coloredCells(int n) {
        long long retVal = 0;

        /*    1 + (4×1) + (4×2) + ... + (4×(n−1))
         *  = 1 + 4 x (1 + 2 + ... + (n-1))
         *  = 1 + 4 x (n x (n-1) / 2)
         *  = 1 + 2 x n x (n-1)
         */
        retVal = 1 + (long long)(2) * (long long)(n) * (long long)(n - 1);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def coloredCells(self, n: int) -> int:
        retVal = 0

        # /*    1 + (4×1) + (4×2) + ... + (4×(n−1))
        #  *  = 1 + 4 x (1 + 2 + ... + (n-1))
        #  *  = 1 + 4 x (n x (n-1) / 2)
        #  *  = 1 + 2 x n x (n-1)
        #  */
        retVal = 1 + 2 * n * (n - 1)

        return retVal
```

</details>

## [2582. Pass the Pillow](https://leetcode.com/problems/pass-the-pillow/)  1278

- [Official](https://leetcode.com/problems/pass-the-pillow/editorial/)
- [Official](https://leetcode.cn/problems/pass-the-pillow/solutions/2451117/di-zhen-tou-by-leetcode-solution-kl5e/)

<details><summary>Description</summary>

```text
There are n people standing in a line labeled from 1 to n. The first person in the line is holding a pillow initially.
Every second, the person holding the pillow passes it to the next person standing in the line.
Once the pillow reaches the end of the line, the direction changes,
and people continue passing the pillow in the opposite direction.
- For example, once the pillow reaches the nth person they pass it to the n - 1th person,
  then to the n - 2th person and so on.

Given the two positive integers n and time, return the index of the person holding the pillow after time seconds.

Example 1:
Input: n = 4, time = 5
Output: 2
Explanation: People pass the pillow in the following way: 1 -> 2 -> 3 -> 4 -> 3 -> 2.
After five seconds, the 2nd person is holding the pillow.

Example 2:
Input: n = 3, time = 2
Output: 3
Explanation: People pass the pillow in the following way: 1 -> 2 -> 3.
After two seconds, the 3rd person is holding the pillow.

Constraints:
2 <= n <= 1000
1 <= time <= 1000
```

<details><summary>Hint</summary>

```text
1. Maintain two integer variables, direction and i,
   where direction denotes the current direction in which the pillow should pass,
   and i denotes an index of the person holding the pillow.
2. While time is positive, update the current index with the current direction.
   If the index reaches the end of the line, multiply direction by - 1.
```

</details>

</details>

<details><summary>C</summary>

```c
int passThePillow(int n, int time) {
    int retVal = 0;

    int direction = time / (n - 1);
    int index = time % (n - 1);
    if (direction % 2 == 0) {
        retVal = index + 1;
    } else if (direction % 2 == 1) {
        retVal = n - index;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int passThePillow(int n, int time) {
        int retVal = 0;

        int direction = time / (n - 1);
        int index = time % (n - 1);
        if (direction % 2 == 0) {
            retVal = index + 1;
        } else if (direction % 2 == 1) {
            retVal = n - index;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def passThePillow(self, n: int, time: int) -> int:
        retVal = 0

        direction = time // (n-1)
        index = time % (n-1)
        if direction % 2 == 0:
            retVal = index + 1
        elif direction % 2 == 1:
            retVal = n - index

        return retVal
```

</details>

## [2601. Prime Subtraction Operation](https://leetcode.com/problems/prime-subtraction-operation/)  1779

- [Official](https://leetcode.com/problems/prime-subtraction-operation/editorial/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array nums of length n.

You can perform the following operation as many times as you want:
- Pick an index i that you haven’t picked before,
  and pick a prime p strictly less than nums[i], then subtract p from nums[i].

Return true if you can make nums a strictly increasing array using the above operation and false otherwise.

A strictly increasing array is an array whose each element is strictly greater than its preceding element.

Example 1:
Input: nums = [4,9,6,10]
Output: true
Explanation:
In the first operation: Pick i = 0 and p = 3, and then subtract 3 from nums[0], so that nums becomes [1,9,6,10].
In the second operation: i = 1, p = 7, subtract 7 from nums[1], so nums becomes equal to [1,2,6,10].
After the second operation, nums is sorted in strictly increasing order, so the answer is true.

Example 2:
Input: nums = [6,8,11,12]
Output: true
Explanation: Initially nums is sorted in strictly increasing order, so we don't need to make any operations.

Example 3:
Input: nums = [5,8,3]
Output: false
Explanation:
It can be proven that there is no way to perform operations to make nums sorted in strictly increasing order,
so the answer is false.

Constraints:
1 <= nums.length <= 1000
1 <= nums[i] <= 1000
nums.length == n
```

<details><summary>Hint</summary>

```text
1. Think about if we have many primes to subtract from nums[i]. Which prime is more optimal?
2. The most optimal prime to subtract from nums[i] is the one
   that makes nums[i] the smallest as possible and greater than nums[i-1].
```

</details>

</details>

<details><summary>C</summary>

```c
bool primeSubOperation(int* nums, int numsSize) {
    bool retVal = false;

    int i, j;

    // Store the sieve array.
    int maxElement = nums[0];
    for (i = 1; i < numsSize; ++i) {
        maxElement = fmax(maxElement, nums[i]);
    }

    int sieve[maxElement + 1];
    for (i = 0; i < maxElement + 1; ++i) {
        sieve[i] = 1;
    }

    sieve[1] = 0;
    for (i = 2; i <= sqrt(maxElement + 1); i++) {
        if (sieve[i] == 1) {
            for (j = i * i; j <= maxElement; j += i) {
                sieve[j] = 0;
            }
        }
    }

    // Start by storing the currValue as 1, and the initial index as 0.
    int currValue = 1;
    int difference;
    i = 0;
    while (i < numsSize) {
        // Store the difference needed to make nums[i] equal to currValue.
        difference = nums[i] - currValue;
        // If difference is less than 0, then nums[i] is already less than currValue. Return false in this case.
        if (difference < 0) {
            return retVal;
        }

        // If the difference is prime or zero, then nums[i] can be made equal to currValue.
        // Otherwise, try for the next currValue.
        if ((sieve[difference] == 1) || (difference == 0)) {
            i++;
            currValue++;
        } else {
            currValue++;
        }
    }
    retVal = true;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    bool primeSubOperation(vector<int>& nums) {
        bool retVal = false;

        // Store the sieve array.
        int maxElement = *max_element(nums.begin(), nums.end());
        vector<int> sieve(maxElement + 1, 1);
        sieve[1] = 0;
        for (int i = 2; i <= sqrt(maxElement + 1); i++) {
            if (sieve[i] == 1) {
                for (int j = i * i; j <= maxElement; j += i) {
                    sieve[j] = 0;
                }
            }
        }

        // Start by storing the currValue as 1, and the initial index as 0.
        int currValue = 1;
        int numsSize = nums.size();
        int i = 0;
        while (i < numsSize) {
            // Store the difference needed to make nums[i] equal to currValue.
            int difference = nums[i] - currValue;
            // If difference is less than 0, then nums[i] is already less than currValue. Return false in this case.
            if (difference < 0) {
                return retVal;
            }

            // If the difference is prime or zero, then nums[i] can be made equal to currValue.
            // Otherwise, try for the next currValue.
            if ((sieve[difference] == 1) || (difference == 0)) {
                i++;
                currValue++;
            } else {
                currValue++;
            }
        }
        retVal = true;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def primeSubOperation(self, nums: List[int]) -> bool:
        retVal = False

        # Store the sieve array.
        maxElement = max(nums)
        sieve = [1] * (maxElement + 1)
        sieve[1] = 0
        for i in range(2, int(sqrt(maxElement + 1)) + 1):
            if sieve[i] == 1:
                for j in range(i * i, maxElement + 1, i):
                    sieve[j] = 0

        # Start by storing the currValue as 1, and the initial index as 0.
        currValue = 1

        numsSize = len(nums)
        i = 0
        while i < numsSize:
            # Store the difference needed to make nums[i] equal to currValue.
            difference = nums[i] - currValue
            # If difference is less than 0, then nums[i] is already less than currValue. Return false in this case.
            if difference < 0:
                return retVal

            # If the difference is prime or zero, then nums[i] can be made equal to currValue.
            # Otherwise, try for the next currValue.
            if sieve[difference] or difference == 0:
                i += 1
                currValue += 1
            else:
                currValue += 1

        retVal = True

        return retVal
```

</details>

## [2843. Count Symmetric Integers](https://leetcode.com/problems/count-symmetric-integers/)  1269

- [Official](https://leetcode.com/problems/count-symmetric-integers/editorial/)
- [Official](https://leetcode.cn/problems/count-symmetric-integers/solutions/3636168/tong-ji-dui-cheng-zheng-shu-de-shu-mu-by-layo/)

<details><summary>Description</summary>

```text
You are given two positive integers low and high.

An integer x consisting of 2 * n digits is symmetric
if the sum of the first n digits of x is equal to the sum of the last n digits of x.
Numbers with an odd number of digits are never symmetric.

Return the number of symmetric integers in the range [low, high].

Example 1:
Input: low = 1, high = 100
Output: 9
Explanation: There are 9 symmetric integers between 1 and 100: 11, 22, 33, 44, 55, 66, 77, 88, and 99.

Example 2:
Input: low = 1200, high = 1230
Output: 4
Explanation: There are 4 symmetric integers between 1200 and 1230: 1203, 1212, 1221, and 1230.

Constraints:
1 <= low <= high <= 10^4
```

<details><summary>Hint</summary>

```text
1. Iterate over all numbers from low to high
2. Convert each number to a string and compare the sum of the first half with that of the second.
```

</details>

</details>

<details><summary>C</summary>

```c
int countSymmetricIntegers(int low, int high) {
    int retVal = 0;

    // 1 <= low <= high <= 10^4
    for (int num = low; num <= high; ++num) {
        if (num < 100) {
            if (num % 11 == 0) {
                retVal++;
            }
        } else if ((1000 <= num) && (num < 10000)) {
            int left = num / 1000 + (num % 1000) / 100;
            int right = (num % 100) / 10 + num % 10;
            if (left == right) {
                retVal++;
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
    int countSymmetricIntegers(int low, int high) {
        int retVal = 0;

        // 1 <= low <= high <= 10^4
        for (int num = low; num <= high; ++num) {
            if (num < 100) {
                if (num % 11 == 0) {
                    retVal++;
                }
            } else if ((1000 <= num) && (num < 10000)) {
                int left = num / 1000 + (num % 1000) / 100;
                int right = (num % 100) / 10 + num % 10;
                if (left == right) {
                    retVal++;
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
    def countSymmetricIntegers(self, low: int, high: int) -> int:
        retVal = 0

        # 1 <= low <= high <= 10^4
        for num in range(low, high + 1):
            if num < 100:
                if num % 11 == 0:
                    retVal += 1
            elif 1000 <= num < 10000:
                left = num // 1000 + num % 1000 // 100
                right = num % 100 // 10 + num % 10
                if left == right:
                    retVal += 1

        return retVal
```

</details>

## [2849. Determine if a Cell Is Reachable at a Given Time](https://leetcode.com/problems/determine-if-a-cell-is-reachable-at-a-given-time/)  1515

- [Official](https://leetcode.com/problems/determine-if-a-cell-is-reachable-at-a-given-time/editorial/)

<details><summary>Description</summary>

```text
You are given four integers sx, sy, fx, fy, and a non-negative integer t.

In an infinite 2D grid, you start at the cell (sx, sy). Each second, you must move to any of its adjacent cells.

Return true if you can reach cell (fx, fy) after exactly t seconds, or false otherwise.

A cell's adjacent cells are the 8 cells around it that share at least one corner with it.
You can visit the same cell several times.

Example 1:
Input: sx = 2, sy = 4, fx = 7, fy = 7, t = 6
Output: true
Explanation: Starting at cell (2, 4),
we can reach cell (7, 7) in exactly 6 seconds by going through the cells depicted in the picture above.

Example 2:
Input: sx = 3, sy = 1, fx = 7, fy = 3, t = 3
Output: false
Explanation: Starting at cell (3, 1),
it takes at least 4 seconds to reach cell (7, 3) by going through the cells depicted in the picture above.
Hence, we cannot reach cell (7, 3) at the third second.

Constraints:
1 <= sx, sy, fx, fy <= 10^9
0 <= t <= 10^9
```

<details><summary>Hint</summary>

```text
1. Minimum time to reach the cell should be less than or equal to given time.
2. The answer is true if t is greater or equal than the Chebyshev distance from (sx, sy) to (fx, fy).
   However, there is one more edge case to be considered.
3. The answer is false If sx == fx and sy == fy
```

</details>

</details>

<details><summary>C</summary>

```c
bool isReachableAtTime(int sx, int sy, int fx, int fy, int t) {
    bool retVal = false;

    int diffX = abs(fx - sx);
    int diffY = abs(fy - sy);

    if ((diffX == 0) && (diffY == 0)) {
        if (t != 1) {
            retVal = true;
        }
    } else {
        if ((t - fmin(diffX, diffY)) >= (fmax(diffX, diffY) - fmin(diffX, diffY))) {
            retVal = true;
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
    bool isReachableAtTime(int sx, int sy, int fx, int fy, int t) {
        bool retVal = false;

        int diffX = abs(fx - sx);
        int diffY = abs(fy - sy);

        if ((diffX == 0) && (diffY == 0)) {
            if (t != 1) {
                retVal = true;
            }
        } else {
            if ((t - min(diffX, diffY)) >= (max(diffX, diffY) - min(diffX, diffY))) {
                retVal = true;
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
    def isReachableAtTime(self, sx: int, sy: int, fx: int, fy: int, t: int) -> bool:
        retVal = False

        diffX = abs(fx - sx)
        diffY = abs(fy - sy)

        if (diffX == 0) and (diffY == 0):
            if t != 1:
                retVal = True
        else:
            if (t - min(diffX, diffY)) >= (max(diffX, diffY) - min(diffX, diffY)):
                retVal = True

        return retVal
```

</details>

## [2864. Maximum Odd Binary Number](https://leetcode.com/problems/maximum-odd-binary-number/)  1237

- [Official](https://leetcode.com/problems/maximum-odd-binary-number/editorial/)

<details><summary>Description</summary>

```text
You are given a binary string s that contains at least one '1'.

You have to rearrange the bits in such a way
that the resulting binary number is the maximum odd binary number that can be created from this combination.

Return a string representing the maximum odd binary number that can be created from the given combination.

Note that the resulting string can have leading zeros.

Example 1:
Input: s = "010"
Output: "001"
Explanation: Because there is just one '1', it must be in the last position. So the answer is "001".

Example 2:
Input: s = "0101"
Output: "1001"
Explanation: One of the '1's must be in the last position.
The maximum number that can be made with the remaining digits is "100". So the answer is "1001".

Constraints:
1 <= s.length <= 100
s consists only of '0' and '1'.
s contains at least one '1'.
```

<details><summary>Hint</summary>

```text
1. The binary representation of an odd number contains '1' in the least significant place.
```

</details>

</details>

<details><summary>C</summary>

```c
char* maximumOddBinaryNumber(char* s) {
    char* pRetVal = s;

    int sSize = strlen(s);

    int count1 = 0;
    int i;
    for (i = 0; i < sSize; ++i) {
        if (s[i] == '1') {
            count1++;
        }
    }

    for (i = 0; i < (count1 - 1); ++i) {
        pRetVal[i] = '1';
    }
    for (i = (count1 - 1); i < (sSize - 1); ++i) {
        pRetVal[i] = '0';
    }
    pRetVal[sSize - 1] = '1';

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string maximumOddBinaryNumber(string s) {
        string retVal = "";

        int count1 = 0;
        int count0 = 0;
        for (auto c : s) {
            if (c == '1') {
                count1++;
            } else {
                count0++;
            }
        }

        for (int i = 1; i < count1; ++i) {
            retVal += "1";
        }
        for (int i = 0; i < count0; ++i) {
            retVal += "0";
        }
        retVal += "1";

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maximumOddBinaryNumber(self, s: str) -> str:
        retVal = ""

        sSize = len(s)

        count1 = s.count('1')
        retVal = '1' * (count1 - 1) + '0' * (sSize - count1) + '1'

        return retVal
```

</details>

## [2894. Divisible and Non-divisible Sums Difference](https://leetcode.com/problems/divisible-and-non-divisible-sums-difference/)  1140

- [Official](https://leetcode.com/problems/divisible-and-non-divisible-sums-difference/editorial/)
- [Official](https://leetcode.cn/problems/divisible-and-non-divisible-sums-difference/solutions/3676585/fen-lei-qiu-he-bing-zuo-chai-by-leetcode-xok4/)

<details><summary>Description</summary>

```text
You are given positive integers n and m.

Define two integers as follows:
- num1: The sum of all integers in the range [1, n] (both inclusive) that are not divisible by m.
- num2: The sum of all integers in the range [1, n] (both inclusive) that are divisible by m.

Return the integer num1 - num2.

Example 1:
Input: n = 10, m = 3
Output: 19
Explanation: In the given example:
- Integers in the range [1, 10] that are not divisible by 3 are [1,2,4,5,7,8,10], num1 is the sum of those integers = 37.
- Integers in the range [1, 10] that are divisible by 3 are [3,6,9], num2 is the sum of those integers = 18.
We return 37 - 18 = 19 as the answer.

Example 2:
Input: n = 5, m = 6
Output: 15
Explanation: In the given example:
- Integers in the range [1, 5] that are not divisible by 6 are [1,2,3,4,5], num1 is the sum of those integers = 15.
- Integers in the range [1, 5] that are divisible by 6 are [], num2 is the sum of those integers = 0.
We return 15 - 0 = 15 as the answer.

Example 3:
Input: n = 5, m = 1
Output: -15
Explanation: In the given example:
- Integers in the range [1, 5] that are not divisible by 1 are [], num1 is the sum of those integers = 0.
- Integers in the range [1, 5] that are divisible by 1 are [1,2,3,4,5], num2 is the sum of those integers = 15.
We return 0 - 15 = -15 as the answer.

Constraints:
1 <= n, m <= 1000
```

<details><summary>Hint</summary>

```text
1. With arithmetic progression we know that the sum of integers in the range [1, n] is n * (n + 1) / 2 .
```

</details>

</details>

<details><summary>C</summary>

```c
int differenceOfSums(int n, int m) {
    int retVal = 0;

    for (int i = 1; i <= n; ++i) {
        if (i % m == 0) {
            retVal -= i;
        } else {
            retVal += i;
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
    int differenceOfSums(int n, int m) {
        int retVal = 0;

        for (int i = 1; i <= n; ++i) {
            if (i % m == 0) {
                retVal -= i;
            } else {
                retVal += i;
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
    def differenceOfSums(self, n: int, m: int) -> int:
        retVal = 0

        for i in range(1, n+1):
            if i % m == 0:
                retVal -= i
            else:
                retVal += i

        return retVal
```

</details>

## [2928. Distribute Candies Among Children I](https://leetcode.com/problems/distribute-candies-among-children-ii/)  1393

- [Official](https://leetcode.cn/problems/distribute-candies-among-children-i/solutions/2791755/gei-xiao-peng-you-men-fen-tang-guo-i-by-9cgew/)

<details><summary>Description</summary>

```text
You are given two positive integers n and limit.

Return the total number of ways to distribute n candies among 3 children such that no child gets more than limit candies.

Example 1:
Input: n = 5, limit = 2
Output: 3
Explanation: There are 3 ways to distribute 5 candies such that no child gets more than 2 candies:
(1, 2, 2), (2, 1, 2) and (2, 2, 1).

Example 2:
Input: n = 3, limit = 3
Output: 10
Explanation: There are 10 ways to distribute 3 candies such that no child gets more than 3 candies:
(0, 0, 3), (0, 1, 2), (0, 2, 1), (0, 3, 0), (1, 0, 2), (1, 1, 1), (1, 2, 0), (2, 0, 1), (2, 1, 0) and (3, 0, 0).

Constraints:
1 <= n <= 50
1 <= limit <= 50
```

<details><summary>Hint</summary>

```text
1. Use three nested for loops to check all the triplets.
```

</details>

</details>

<details><summary>C</summary>

```c
int distributeCandies(int n, int limit) {
    int retVal = 0;

    int minLimit = fmin(limit, n);
    for (int i = 0; i <= minLimit; i++) {
        if ((n - i) > (2 * limit)) {
            continue;
        }
        retVal += (fmin(n - i, limit) - fmax(0, n - i - limit) + 1);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int distributeCandies(int n, int limit) {
        int retVal = 0;

        int minLimit = min(limit, n);
        for (int i = 0; i <= minLimit; i++) {
            if ((n - i) > (2 * limit)) {
                continue;
            }
            retVal += (min(n - i, limit) - max(0, n - i - limit) + 1);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def distributeCandies(self, n: int, limit: int) -> int:
        retVal = 0

        minLimit = min(limit, n)
        for i in range(minLimit + 1):
            if (n - i) > (2 * limit):
                continue
            retVal += (min(n - i, limit) - max(0, n - i - limit) + 1)

        return retVal
```

</details>

## [2929. Distribute Candies Among Children II](https://leetcode.com/problems/distribute-candies-among-children-ii/)  1701

- [Official](https://leetcode.com/problems/distribute-candies-among-children-ii/editorial/)
- [Official](https://leetcode.cn/problems/distribute-candies-among-children-ii/solutions/2791756/gei-xiao-peng-you-men-fen-tang-guo-ii-by-1jj9/)

<details><summary>Description</summary>

```text
You are given two positive integers n and limit.

Return the total number of ways to distribute n candies among 3 children such that no child gets more than limit candies.

Example 1:
Input: n = 5, limit = 2
Output: 3
Explanation: There are 3 ways to distribute 5 candies such that no child gets more than 2 candies:
(1, 2, 2), (2, 1, 2) and (2, 2, 1).

Example 2:
Input: n = 3, limit = 3
Output: 10
Explanation: There are 10 ways to distribute 3 candies such that no child gets more than 3 candies:
(0, 0, 3), (0, 1, 2), (0, 2, 1), (0, 3, 0), (1, 0, 2), (1, 1, 1), (1, 2, 0), (2, 0, 1), (2, 1, 0) and (3, 0, 0).

Constraints:
1 <= n <= 10^6
1 <= limit <= 10^6
```

<details><summary>Hint</summary>

```text
1. We can enumerate the number of candies of one particular child, let it be i which means 0 <= i <= min(limit, n).
2. Suppose the 2nd child gets j candies. Then 0 <= j <= limit and i + j <= n.
3. The 3rd child will hence get n - i - j candies and we should have 0 <= n - i - j <= limit.
4. After some transformations, for each i, we have max(0, n - i - limit) <= j <= min(limit, n - i),
   each j corresponding to a solution.
   So the number of solutions for some i is max(min(limit, n - i) - max(0, n - i - limit) + 1, 0).
   Sum the expression for every i in [0, min(n, limit)].
```

</details>

</details>

<details><summary>C</summary>

```c
long long distributeCandies(int n, int limit) {
    long long retVal = 0;

    int minLimit = fmin(limit, n);
    for (int i = 0; i <= minLimit; i++) {
        if ((n - i) > (2 * limit)) {
            continue;
        }
        retVal += (fmin(n - i, limit) - fmax(0, n - i - limit) + 1);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long distributeCandies(int n, int limit) {
        long long retVal = 0;

        int minLimit = min(limit, n);
        for (int i = 0; i <= minLimit; i++) {
            if ((n - i) > (2 * limit)) {
                continue;
            }
            retVal += (min(n - i, limit) - max(0, n - i - limit) + 1);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def distributeCandies(self, n: int, limit: int) -> int:
        retVal = 0

        minLimit = min(limit, n)
        for i in range(minLimit + 1):
            if (n - i) > (2 * limit):
                continue
            retVal += (min(n - i, limit) - max(0, n - i - limit) + 1)

        return retVal
```

</details>

## [3024. Type of Triangle](https://leetcode.com/problems/type-of-triangle/)  1134

- [Official](https://leetcode.com/problems/type-of-triangle/editorial/)
- [Official](https://leetcode.cn/problems/type-of-triangle/solutions/3670439/san-jiao-xing-lei-xing-by-leetcode-solut-we7x/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array nums of size 3 which can form the sides of a triangle.
- A triangle is called equilateral if it has all sides of equal length.
- A triangle is called isosceles if it has exactly two sides of equal length.
- A triangle is called scalene if all its sides are of different lengths.

Return a string representing the type of triangle that can be formed or "none" if it cannot form a triangle.

Example 1:
Input: nums = [3,3,3]
Output: "equilateral"
Explanation: Since all the sides are of equal length, therefore, it will form an equilateral triangle.

Example 2:
Input: nums = [3,4,5]
Output: "scalene"
Explanation:
nums[0] + nums[1] = 3 + 4 = 7, which is greater than nums[2] = 5.
nums[0] + nums[2] = 3 + 5 = 8, which is greater than nums[1] = 4.
nums[1] + nums[2] = 4 + 5 = 9, which is greater than nums[0] = 3.
Since the sum of the two sides is greater than the third side for all three cases, therefore, it can form a triangle.
As all the sides are of different lengths, it will form a scalene triangle.

Constraints:
nums.length == 3
1 <= nums[i] <= 100
```

<details><summary>Hint</summary>

```text
1. The condition for a valid triangle is that for any two sides,
   the sum of their lengths must be greater than the third side.
2. Simply count the number of unique edge lengths after checking it’s a valid triangle.
```

</details>

</details>

<details><summary>C</summary>

```c
#define NONE_STR "none"
#define EQUILATERAL_STR "equilateral"
#define ISOSCELES_STR "isosceles"
#define SCALENE_STR "scalene"
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
char* triangleType(int* nums, int numsSize) {
    char* pRetVal;

    qsort(nums, numsSize, sizeof(int), compareInteger);
    if (nums[0] + nums[1] <= nums[2]) {
        pRetVal = NONE_STR;
    } else if (nums[0] == nums[2]) {
        pRetVal = EQUILATERAL_STR;
    } else if ((nums[0] == nums[1]) || (nums[1] == nums[2])) {
        pRetVal = ISOSCELES_STR;
    } else {
        pRetVal = SCALENE_STR;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    string none = "none";
    string equilateral = "equilateral";
    string isosceles = "isosceles";
    string scalene = "scalene";

   public:
    string triangleType(vector<int>& nums) {
        string retVal;

        sort(nums.begin(), nums.end());
        if (nums[0] + nums[1] <= nums[2]) {
            retVal = none;
        } else if (nums[0] == nums[2]) {
            retVal = equilateral;
        } else if ((nums[0] == nums[1]) || (nums[1] == nums[2])) {
            retVal = isosceles;
        } else {
            retVal = scalene;
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
        self.none = "none"
        self.equilateral = "equilateral"
        self.isosceles = "isosceles"
        self.scalene = "scalene"

    def triangleType(self, nums: List[int]) -> str:
        retVal = ""

        nums.sort()
        if nums[0] + nums[1] <= nums[2]:
            retVal = self.none
        elif nums[0] == nums[2]:
            retVal = self.equilateral
        elif (nums[0] == nums[1]) or (nums[1] == nums[2]):
            retVal = self.isosceles
        else:
            retVal = self.scalene

        return retVal
```

</details>

## [3272. Find the Count of Good Integers](https://leetcode.com/problems/find-the-count-of-good-integers/)  2382

- [Official](https://leetcode.com/problems/find-the-count-of-good-integers/editorial/)
- [Official](https://leetcode.cn/problems/find-the-count-of-good-integers/solutions/3637602/tong-ji-hao-zheng-shu-de-shu-mu-by-leetc-m5l4/)

<details><summary>Description</summary>

```text
You are given two positive integers n and k.

An integer x is called k-palindromic if:
- x is a palindrome.
- x is divisible by k.

An integer is called good if its digits can be rearranged to form a k-palindromic integer.
For example, for k = 2, 2020 can be rearranged to form the k-palindromic integer 2002,
whereas 1010 cannot be rearranged to form a k-palindromic integer.

Return the count of good integers containing n digits.

Note that any integer must not have leading zeros, neither before nor after rearrangement.
For example, 1010 cannot be rearranged to form 101.

Example 1:
Input: n = 3, k = 5
Output: 27
Explanation:
Some of the good integers are:
551 because it can be rearranged to form 515.
525 because it is already k-palindromic.

Example 2:
Input: n = 1, k = 4
Output: 2
Explanation:
The two good integers are 4 and 8.

Example 3:
Input: n = 5, k = 6
Output: 2468

Constraints:
1 <= n <= 10
1 <= k <= 9
```

<details><summary>Hint</summary>

```text
1. How to generate all K-palindromic strings of length n? Do we need to go through all n digits?
2. Use permutations to calculate the number of possible rearrangements.
```

</details>

</details>

<details><summary>C</summary>

```c
struct hashTable {
    char *key;
    UT_hash_handle hh;
};
void freeAll(struct hashTable *pFree) {
    struct hashTable *current;
    struct hashTable *tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%s\n", pFree->key);
        HASH_DEL(pFree, current);
        free(current->key);
        free(current);
    }
}
int compareChar(const void *c1, const void *c2) {
    // ascending order
    return (*(char *)c1 > *(char *)c2);
}
long long countGoodIntegers(int n, int k) {
    long long retVal = 0;

    // Enumerate the number of palindrome numbers of n digits
    int base = (int)pow(10, (n - 1) / 2);
    int skip = n & 1;
    char s[16];
    int sSize;
    long long palindromicInteger;
    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    for (int i = base; i < base * 10; i++) {
        memset(s, 0, sizeof(s));
        sprintf(s, "%d", i);
        sSize = strlen(s);
        for (int j = sSize - 1 - skip; j >= 0; j--) {
            s[sSize + (sSize - skip - 1 - j)] = s[j];
        }
        s[2 * sSize - skip] = '\0';
        palindromicInteger = atoll(s);

        // If the current palindrome number is a k-palindromic integer
        if (palindromicInteger % k == 0) {
            sSize = strlen(s);
            qsort(s, sSize, sizeof(char), compareChar);

            pTemp = NULL;
            HASH_FIND_STR(pHashTable, s, pTemp);
            if (pTemp != NULL) {
                continue;
            }
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                return retVal;
            }
            pTemp->key = strdup(s);
            HASH_ADD_STR(pHashTable, key, pTemp);
        }
    }

    long long *factorial = malloc((n + 1) * sizeof(long long));
    if (factorial == NULL) {
        perror("malloc");
        freeAll(pHashTable);
        return retVal;
    }
    factorial[0] = 1;
    for (int i = 1; i <= n; i++) {
        factorial[i] = factorial[i - 1] * i;
    }

    pTemp = NULL;
    int cnt[10];
    long long tot;
    for (pTemp = pHashTable; pTemp; pTemp = pTemp->hh.next) {
        memset(cnt, 0, sizeof(cnt));
        for (int j = 0; pTemp->key[j] != '\0'; j++) {
            cnt[pTemp->key[j] - '0']++;
        }

        // Calculate permutations and combinations
        tot = (n - cnt[0]) * factorial[n - 1];
        for (int j = 0; j < 10; j++) {
            tot /= factorial[cnt[j]];
        }
        retVal += tot;
    }

    //
    free(factorial);
    freeAll(pHashTable);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long countGoodIntegers(int n, int k) {
        long long retVal = 0;

        // Enumerate the number of palindrome numbers of n digits
        int base = pow(10, (n - 1) / 2);
        int skip = n & 1;
        unordered_set<string> dict;
        for (int i = base; i < base * 10; i++) {
            string s = to_string(i);
            s += string(s.rbegin() + skip, s.rend());
            long long palindromicInteger = stoll(s);

            // If the current palindrome number is a k-palindromic integer
            if (palindromicInteger % k == 0) {
                sort(s.begin(), s.end());
                dict.emplace(s);
            }
        }

        vector<long long> factorial(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            factorial[i] = factorial[i - 1] * i;
        }
        for (const string& s : dict) {
            vector<int> cnt(10);
            for (char c : s) {
                cnt[c - '0']++;
            }

            // Calculate permutations and combinations
            long long tot = (n - cnt[0]) * factorial[n - 1];
            for (int x : cnt) {
                tot /= factorial[x];
            }
            retVal += tot;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def countGoodIntegers(self, n: int, k: int) -> int:
        retVal = 0

        # Enumerate the number of palindrome numbers of n digits
        base = 10 ** ((n - 1) // 2)
        skip = n & 1
        dictionary = set()
        for i in range(base, base * 10):
            s = str(i)
            s += s[::-1][skip:]
            palindromicInteger = int(s)

            # If the current palindrome number is a k-palindromic integer
            if palindromicInteger % k == 0:
                sorted_s = "".join(sorted(s))
                dictionary.add(sorted_s)

        fac = [factorial(i) for i in range(n + 1)]
        for s in dictionary:
            cnt = [0] * 10
            for c in s:
                cnt[int(c)] += 1

            # Calculate permutations and combinations
            tot = (n - cnt[0]) * fac[n - 1]
            for x in cnt:
                tot //= fac[x]
            retVal += tot

        return retVal
```

</details>

## [3405. Count the Number of Arrays with K Matching Adjacent Elements](https://leetcode.com/problems/count-the-number-of-arrays-with-k-matching-adjacent-elements/)  2309

- [Official](https://leetcode.com/problems/count-the-number-of-arrays-with-k-matching-adjacent-elements/editorial/)
- [Official](https://leetcode.cn/problems/count-the-number-of-arrays-with-k-matching-adjacent-elements/solutions/3693518/tong-ji-qia-hao-you-k-ge-xiang-deng-xian-uxt4/)

<details><summary>Description</summary>

```text
You are given three integers n, m, k. A good array arr of size n is defined as follows:
- Each element in arr is in the inclusive range [1, m].
- Exactly k indices i (where 1 <= i < n) satisfy the condition arr[i - 1] == arr[i].

Return the number of good arrays that can be formed.

Since the answer may be very large, return it modulo 109 + 7.

Example 1:
Input: n = 3, m = 2, k = 1
Output: 4
Explanation:
There are 4 good arrays. They are [1, 1, 2], [1, 2, 2], [2, 1, 1] and [2, 2, 1].
Hence, the answer is 4.

Example 2:
Input: n = 4, m = 2, k = 2
Output: 6
Explanation:
The good arrays are [1, 1, 1, 2], [1, 1, 2, 2], [1, 2, 2, 2], [2, 1, 1, 1], [2, 2, 1, 1] and [2, 2, 2, 1].
Hence, the answer is 6.

Example 3:
Input: n = 5, m = 2, k = 0
Output: 2
Explanation:
The good arrays are [1, 2, 1, 2, 1] and [2, 1, 2, 1, 2]. Hence, the answer is 2.

Constraints:
1 <= n <= 10^5
1 <= m <= 10^5
0 <= k <= n - 1
```

<details><summary>Hint</summary>

```text
1. The first position arr[0] has m choices.
2. For each of the remaining n - 1 indices, 0 < i < n, select k positions from left to right and set arr[i] = arr[i - 1].
3. For all other indices, set arr[i] != arr[i - 1] with (m - 1) choices for each of the n - 1 - k positions.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MODULO (int)(1e9 + 7)
#define MAX_NUMBER (int)(1e5)  // 1 <= n <= 10^5, 1 <= m <= 10^5
long long factory[MAX_NUMBER];
long long incertFactory[MAX_NUMBER];
long long qpower(long long x, int n) {
    long long retVal = 1;

    while (n) {
        if (n & 1) {
            retVal = retVal * x % MODULO;
        }
        x = x * x % MODULO;
        n >>= 1;
    }

    return retVal;
}
long long combine(int n, int m) {
    long long retVal = factory[n] * incertFactory[m] % MODULO * incertFactory[n - m] % MODULO;

    return retVal;
}
int countGoodArrays(int n, int m, int k) {
    int retVal = 0;

    if (factory[0] == 0) {
        factory[0] = 1;
        for (int i = 1; i < MAX_NUMBER; i++) {
            factory[i] = factory[i - 1] * i % MODULO;
        }

        incertFactory[MAX_NUMBER - 1] = qpower(factory[MAX_NUMBER - 1], MODULO - 2);
        for (int i = MAX_NUMBER - 1; i > 0; i--) {
            incertFactory[i - 1] = incertFactory[i] * i % MODULO;
        }
    }
    retVal = combine(n - 1, k) * m % MODULO * qpower(m - 1, n - k - 1) % MODULO;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
static const int maxNumber = 1e5;  // // 1 <= n <= 10^5, 1 <= m <= 10^5
vector<long long> factory(maxNumber);
vector<long long> incertFactory(maxNumber);
class Solution {
   private:
    static constexpr int MODULO = 1e9 + 7;

    long long qpower(long long x, int n) {
        long long retVal = 1;

        while (n) {
            if (n & 1) {
                retVal = retVal * x % MODULO;
            }
            x = x * x % MODULO;
            n >>= 1;
        }

        return retVal;
    }
    long long combine(int n, int m) {
        long long retVal = factory[n] * incertFactory[m] % MODULO * incertFactory[n - m] % MODULO;

        return retVal;
    }

   public:
    int countGoodArrays(int n, int m, int k) {
        int retVal = 0;

        if (factory[0] == 0) {
            factory[0] = 1;
            for (int i = 1; i < maxNumber; i++) {
                factory[i] = factory[i - 1] * i % MODULO;
            }

            incertFactory[maxNumber - 1] = qpower(factory[maxNumber - 1], MODULO - 2);
            for (int i = maxNumber - 1; i; i--) {
                incertFactory[i - 1] = incertFactory[i] * i % MODULO;
            }
        }
        retVal = combine(n - 1, k) * m % MODULO * qpower(m - 1, n - k - 1) % MODULO;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
maxNumber = 10**5  # 1 <= n <= 10^5, 1 <= m <= 10^5
factory = [0] * maxNumber
incertFactory = [0] * maxNumber


class Solution:
    def __init__(self):
        self.MODULO = 10 ** 9 + 7

    def qpower(self, x, n):
        retVal = 1

        while n:
            if n & 1:
                retVal = retVal * x % self.MODULO
            x = x * x % self.MODULO
            n >>= 1

        return retVal

    def combine(self, n, m):
        retVal = factory[n] * incertFactory[m] % self.MODULO * incertFactory[n - m] % self.MODULO

        return retVal

    def countGoodArrays(self, n: int, m: int, k: int) -> int:
        retVal = 0

        if factory[0] == 0:
            factory[0] = 1
            for i in range(1, maxNumber):
                factory[i] = factory[i - 1] * i % self.MODULO

            incertFactory[maxNumber - 1] = self.qpower(factory[maxNumber - 1], self.MODULO - 2)
            for i in range(maxNumber - 1, 0, -1):
                incertFactory[i - 1] = incertFactory[i] * i % self.MODULO

        retVal = self.combine(n - 1, k) * m % self.MODULO * self.qpower(m - 1, n - k - 1) % self.MODULO

        return retVal
```

</details>

## [3443. Maximum Manhattan Distance After K Changes](https://leetcode.com/problems/maximum-manhattan-distance-after-k-changes/)  1855

- [Official](https://leetcode.com/problems/maximum-manhattan-distance-after-k-changes/editorial/)
- [Official](https://leetcode.cn/problems/maximum-manhattan-distance-after-k-changes/solutions/3688589/kci-xiu-gai-hou-de-zui-da-man-ha-dun-ju-q5twm/)

<details><summary>Description</summary>

```text
You are given a string s consisting of the characters 'N', 'S', 'E', and 'W',
where s[i] indicates movements in an infinite grid:
- 'N' : Move north by 1 unit.
- 'S' : Move south by 1 unit.
- 'E' : Move east by 1 unit.
- 'W' : Move west by 1 unit.

Initially, you are at the origin (0, 0). You can change at most k characters to any of the four directions.

Find the maximum Manhattan distance from the origin
that can be achieved at any time while performing the movements in order.

The Manhattan Distance between two cells (xi, yi) and (xj, yj) is |xi - xj| + |yi - yj|.

Example 1:
Input: s = "NWSE", k = 1
Output: 3
Explanation:
Change s[2] from 'S' to 'N'. The string s becomes "NWNE".
Movement Position (x, y) Manhattan Distance Maximum
s[0] == 'N' (0, 1) 0 + 1 = 1 1
s[1] == 'W' (-1, 1) 1 + 1 = 2 2
s[2] == 'N' (-1, 2) 1 + 2 = 3 3
s[3] == 'E' (0, 2) 0 + 2 = 2 3
The maximum Manhattan distance from the origin that can be achieved is 3. Hence, 3 is the output.

Example 2:
Input: s = "NSWWEW", k = 3
Output: 6
Explanation:
Change s[1] from 'S' to 'N', and s[4] from 'E' to 'W'. The string s becomes "NNWWWW".
The maximum Manhattan distance from the origin that can be achieved is 6. Hence, 6 is the output.

Constraints:
1 <= s.length <= 10^5
0 <= k <= s.length
s consists of only 'N', 'S', 'E', and 'W'.
```

<details><summary>Hint</summary>

```text
1. We can brute force all the possible directions (NE, NW, SE, SW).
2. Change up to k characters to maximize the distance in the chosen direction.
```

</details>

</details>

<details><summary>C</summary>

```c
int maxDistance(char* s, int k) {
    int retVal = 0;

    int latitude = 0;
    int longitude = 0;
    int sSize = strlen(s);
    for (int i = 0; i < sSize; i++) {
        switch (s[i]) {
            case 'N':
                latitude++;
                break;
            case 'S':
                latitude--;
                break;
            case 'E':
                longitude++;
                break;
            case 'W':
                longitude--;
                break;
        }
        retVal = fmax(retVal, fmin(abs(latitude) + abs(longitude) + k * 2, i + 1));
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxDistance(string s, int k) {
        int retVal = 0;

        int latitude = 0;
        int longitude = 0;
        int sSize = s.size();
        for (int i = 0; i < sSize; i++) {
            switch (s[i]) {
                case 'N':
                    latitude++;
                    break;
                case 'S':
                    latitude--;
                    break;
                case 'E':
                    longitude++;
                    break;
                case 'W':
                    longitude--;
                    break;
            }
            retVal = max(retVal, min(abs(latitude) + abs(longitude) + k * 2, i + 1));
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxDistance(self, s: str, k: int) -> int:
        retVal = 0

        latitude = 0
        longitude = 0
        sSize = len(s)
        for i in range(sSize):
            if s[i] == "N":
                latitude += 1
            elif s[i] == "S":
                latitude -= 1
            elif s[i] == "E":
                longitude += 1
            elif s[i] == "W":
                longitude -= 1
            retVal = max(retVal, min(abs(latitude) + abs(longitude) + k * 2, i + 1))

        return retVal
```

</details>
