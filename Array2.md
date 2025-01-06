# Array

## [1089. Duplicate Zeros](https://leetcode.com/problems/duplicate-zeros/)  1262

<details><summary>Description</summary>

```text
Given a fixed-length integer array arr, duplicate each occurrence of zero, shifting the remaining elements to the right.

Note that elements beyond the length of the original array are not written.
Do the above modifications to the input array in place and do not return anything.

Example 1:
Input: arr = [1,0,2,3,0,4,5,0]
Output: [1,0,0,2,3,0,0,4]
Explanation: After calling your function, the input array is modified to: [1,0,0,2,3,0,0,4]

Example 2:
Input: arr = [1,2,3]
Output: [1,2,3]
Explanation: After calling your function, the input array is modified to: [1,2,3]

Constraints:
1 <= arr.length <= 10^4
0 <= arr[i] <= 9
```

</details>

<details><summary>C</summary>

```c
void duplicateZeros(int* arr, int arrSize){
    int i, j;
    for (i=0; i<arrSize; ++i)
    {
        if (arr[i] != 0)
        {
            continue;
        }

        for (j=arrSize-2; j>=i; --j)
        {
            arr[j+1] = arr[j];
        }
        ++i;
    }
}
```

</details>

## [1160. Find Words That Can Be Formed by Characters](https://leetcode.com/problems/find-words-that-can-be-formed-by-characters/)  1205

- [Official](https://leetcode.com/problems/find-words-that-can-be-formed-by-characters/editorial/)
- [Official](https://leetcode.cn/problems/find-words-that-can-be-formed-by-characters/solutions/152888/pin-xie-dan-ci-by-leetcode-solution/)

<details><summary>Description</summary>

```text
You are given an array of strings words and a string chars.

A string is good if it can be formed by characters from chars (each character can only be used once).

Return the sum of lengths of all good strings in words.

Example 1:
Input: words = ["cat","bt","hat","tree"], chars = "atach"
Output: 6
Explanation: The strings that can be formed are "cat" and "hat" so the answer is 3 + 3 = 6.

Example 2:
Input: words = ["hello","world","leetcode"], chars = "welldonehoneyr"
Output: 10
Explanation: The strings that can be formed are "hello" and "world" so the answer is 5 + 5 = 10.

Constraints:
1 <= words.length <= 1000
1 <= words[i].length, chars.length <= 100
words[i] and chars consist of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Solve the problem for each string in words independently.
2. Now try to think in frequency of letters.
3. Count how many times each character occurs in string chars.
4. To form a string using characters from chars, the frequency of each character in chars
   must be greater than or equal the frequency of that character in the string to be formed.
```

</details>

</details>

<details><summary>C</summary>

```c
int countCharacters(char **words, int wordsSize, char *chars) {
    int retVal = 0;

    int i, j, idx;

    // words[i] and chars consist of lowercase English letters.
    int charsCount[26];
    memset(charsCount, 0, sizeof(charsCount));

    int charsSize = strlen(chars);
    for (i = 0; i < charsSize; ++i) {
        idx = chars[i] - 'a';
        charsCount[idx]++;
    }

    int check[26];
    int count, wordSize;
    for (i = 0; i < wordsSize; ++i) {
        memset(check, 0, sizeof(check));
        memcpy(check, charsCount, sizeof(check));
        count = 0;

        wordSize = strlen(words[i]);
        for (j = 0; j < wordSize; ++j) {
            idx = words[i][j] - 'a';
            if (check[idx] == 0) {
                break;
            }
            check[idx]--;
            count++;
        }

        if (count == wordSize) {
            retVal += count;
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
    int countCharacters(vector<string>& words, string chars) {
        int retVal = 0;

        // words[i] and chars consist of lowercase English letters.
        vector<int> charsCount(26, 0);
        for (char c : chars) {
            int idx = c - 'a';
            charsCount[idx]++;
        }

        vector<int> check;
        for (string word : words) {
            check.assign(charsCount.begin(), charsCount.end());
            int count = 0;
            for (char c : word) {
                int idx = c - 'a';
                if (check[idx] == 0) {
                    break;
                }
                check[idx]--;
                count++;
            }

            int wordSize = word.size();
            if (count == wordSize) {
                retVal += count;
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
    def countCharacters(self, words: List[str], chars: str) -> int:
        retVal = 0

        # words[i] and chars consist of lowercase English letters.
        charsCount = [0] * 26

        for char in chars:
            idx = ord(char) - ord('a')
            charsCount[idx] += 1

        for word in words:
            check = charsCount.copy()
            count = 0
            for c in word:
                idx = ord(c) - ord('a')
                if check[idx] == 0:
                    break
                check[idx] -= 1
                count += 1

            wordSize = len(word)
            if count == wordSize:
                retVal += count

        return retVal
```

</details>

## [1287. Element Appearing More Than 25% In Sorted Array](https://leetcode.com/problems/element-appearing-more-than-25-in-sorted-array/)  1179

- [Official](https://leetcode.com/problems/element-appearing-more-than-25-in-sorted-array/editorial/)
- [Official](https://leetcode.cn/problems/element-appearing-more-than-25-in-sorted-array/solutions/101725/you-xu-shu-zu-zhong-chu-xian-ci-shu-chao-guo-25d-3/)

<details><summary>Description</summary>

```text
Given an integer array sorted in non-decreasing order,
there is exactly one integer in the array that occurs more than 25% of the time, return that integer.

Example 1:
Input: arr = [1,2,2,6,6,6,6,7,10]
Output: 6

Example 2:
Input: arr = [1,1]
Output: 1

Constraints:
1 <= arr.length <= 10^4
0 <= arr[i] <= 10^5
```

<details><summary>Hint</summary>

```text
1. Divide the array in four parts [1 - 25%] [25 - 50 %] [50 - 75 %] [75% - 100%]
2. The answer should be in one of the ends of the intervals.
3. In order to check which is element is the answer we can count the frequency with binarySearch.
```

</details>

</details>

<details><summary>C</summary>

```c
int findSpecialInteger(int* arr, int arrSize) {
    int retVal = 0;

    int shift = arrSize >> 2;  // there is exactly one integer in the array that occurs more than 25% of the time
    int i;
    for (i = 0; i < (arrSize - shift); ++i) {
        if (arr[i] != arr[i + shift]) {
            continue;
        }
        retVal = arr[i];
        break;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int findSpecialInteger(vector<int>& arr) {
        int retVal = 0;

        int arrSize = arr.size();
        int shift = arrSize >> 2;  // there is exactly one integer in the array that occurs more than 25% of the time
        for (int i = 0; i < (arrSize - shift); ++i) {
            if (arr[i] != arr[i + shift]) {
                continue;
            }
            retVal = arr[i];
            break;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def findSpecialInteger(self, arr: List[int]) -> int:
        retVal = 0

        arrSize = len(arr)
        # there is exactly one integer in the array that occurs more than 25% of the time
        shift = arrSize >> 2
        for i in range(arrSize-shift):
            if arr[i] != arr[i+shift]:
                continue
            retVal = arr[i]
            break

        return retVal
```

</details>

## [1291. Sequential Digits](https://leetcode.com/problems/sequential-digits/)  1373

- [Official](https://leetcode.cn/problems/sequential-digits/solutions/101734/shun-ci-shu-by-leetcode-solution/)

<details><summary>Description</summary>

```text
An integer has sequential digits if and only if each digit in the number is one more than the previous digit.

Return a sorted list of all the integers in the range [low, high] inclusive that have sequential digits.

Example 1:
Input: low = 100, high = 300
Output: [123,234]

Example 2:
Input: low = 1000, high = 13000
Output: [1234,2345,3456,4567,5678,6789,12345]

Constraints:
10 <= low <= high <= 10^9
```

<details><summary>Hint</summary>

```text
1. Generate all numbers with sequential digits and check if they are in the given range.
2. Fix the starting digit then do a recursion that tries to append all valid digits.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sequentialDigits(int low, int high, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    /* 10 <= low <= high <= 10^9
     *  9 * 8 / 2 = 36
     */
    int maxReturnSize = 64;
    pRetVal = (int*)malloc(maxReturnSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (maxReturnSize * sizeof(int)));

    // 10 <= low <= high <= 10^9
    int i, j, num;
    for (i = 1; i < 10; ++i) {
        num = i;
        for (j = i + 1; j < 10; ++j) {
            num = 10 * num + j;
            if ((num >= low) && (num <= high)) {
                pRetVal[(*returnSize)++] = num;
            }
        }
    }
    qsort(pRetVal, (*returnSize), sizeof(int), compareInteger);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> sequentialDigits(int low, int high) {
        vector<int> retVal;

        // 10 <= low <= high <= 10^9
        for (int i = 1; i < 10; ++i) {
            int num = i;
            for (int j = i + 1; j < 10; ++j) {
                num = 10 * num + j;
                if ((num >= low) && (num <= high)) {
                    retVal.emplace_back(num);
                }
            }
        }
        sort(retVal.begin(), retVal.end());

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def sequentialDigits(self, low: int, high: int) -> List[int]:
        retVal = []

        for i in range(1, 10):  # 10 <= low <= high <= 10^9
            num = i
            for j in range(i+1, 10):
                num = 10 * num + j
                if (num >= low) and (num <= high):
                    retVal.append(num)
        retVal.sort()

        return retVal
```

</details>

## [1295. Find Numbers with Even Number of Digits](https://leetcode.com/problems/find-numbers-with-even-number-of-digits/)  1139

- [Official](https://leetcode.cn/problems/find-numbers-with-even-number-of-digits/solutions/101807/tong-ji-wei-shu-wei-ou-shu-de-shu-zi-by-leetcode-s/)

<details><summary>Description</summary>

```text
Given an array nums of integers, return how many of them contain an even number of digits.

Example 1:
Input: nums = [12,345,2,6,7896]
Output: 2
Explanation:
12 contains 2 digits (even number of digits).
345 contains 3 digits (odd number of digits).
2 contains 1 digit (odd number of digits).
6 contains 1 digit (odd number of digits).
7896 contains 4 digits (even number of digits).
Therefore only 12 and 7896 contain an even number of digits.

Example 2:
Input: nums = [555,901,482,1771]
Output: 1
Explanation:
Only 1771 contains an even number of digits.

Constraints:
1 <= nums.length <= 500
1 <= nums[i] <= 10^5
```

</details>

<details><summary>C</summary>

```c
int getTheNumberOfDigits(int num) {
    int retVal = 0;

    while (num > 0) {
        ++retVal;
        num /= 10;
    }

    return retVal;
}
int findNumbers(int* nums, int numsSize) {
    int retVal = 0;

    int i;
    for (i = 0; i < numsSize; ++i) {
        if (getTheNumberOfDigits(nums[i]) % 2 == 0) {
            ++retVal;
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
    int findNumbers(vector<int>& nums) {
        int retVal = 0;

        for (long unsigned int i = 0; i < nums.size(); ++i) {
            int tmp = nums[i];
            int count = 0;
            while (tmp > 0) {
                ++count;
                tmp /= 10;
            }
            if (count % 2 == 0) {
                ++retVal;
            }
        }

        return retVal;
    }
};
```

</details>

## [1299. Replace Elements with Greatest Element on Right Side](https://leetcode.com/problems/replace-elements-with-greatest-element-on-right-side/)  1219

<details><summary>Description</summary>

```text
Given an array arr, replace every element in that array with the greatest element
among the elements to its right, and replace the last element with -1.

After doing so, return the array.

Example 1:
Input: arr = [17,18,5,4,6,1]
Output: [18,6,6,6,1,-1]
Explanation:
- index 0 --> the greatest element to the right of index 0 is index 1 (18).
- index 1 --> the greatest element to the right of index 1 is index 4 (6).
- index 2 --> the greatest element to the right of index 2 is index 4 (6).
- index 3 --> the greatest element to the right of index 3 is index 4 (6).
- index 4 --> the greatest element to the right of index 4 is index 5 (1).
- index 5 --> there are no elements to the right of index 5, so we put -1.

Example 2:
Input: arr = [400]
Output: [-1]
Explanation: There are no elements to the right of index 0.

Constraints:
1 <= arr.length <= 10^4
1 <= arr[i] <= 10^5
```

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* replaceElements(int* arr, int arrSize, int* returnSize){
#if 1   // return original arr taht is replaced
    *returnSize = arrSize;

    int greatest = -1;
    int tmp;
    int i;
    for (i=(arrSize-1); i>=0; --i)
    {
        tmp = arr[i];
        arr[i] = greatest;
        greatest = (greatest>tmp)?greatest:tmp;
    }

    return arr;
#else   // return new malloc array
    int* pRetVal;

    *returnSize = arrSize;
    pRetVal = (int*)malloc((*returnSize)*sizeof(int));
    if (pRetVal == NULL)
    {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (*returnSize)*sizeof(int));

    int greatest = -1;
    int i;
    for (i=(arrSize-1); i>=0; --i)
    {
        pRetVal[i] = greatest;
        greatest = (greatest>arr[i])?greatest:arr[i];
    }

    return pRetVal;
#endif
}
```

</details>

## [1351. Count Negative Numbers in a Sorted Matrix](https://leetcode.com/problems/count-negative-numbers-in-a-sorted-matrix/)  1139

- [Official](https://leetcode.com/problems/count-negative-numbers-in-a-sorted-matrix/editorial/)
- [Official](https://leetcode.cn/problems/count-negative-numbers-in-a-sorted-matrix/solutions/101204/tong-ji-you-xu-ju-zhen-zhong-de-fu-shu-by-leetcode/)

<details><summary>Description</summary>

```text
Given a m x n matrix grid which is sorted in non-increasing order both row-wise and column-wise,
return the number of negative numbers in grid.

Example 1:
Input: grid = [[4,3,2,-1],[3,2,1,-1],[1,1,-1,-2],[-1,-1,-2,-3]]
Output: 8
Explanation: There are 8 negatives number in the matrix.

Example 2:
Input: grid = [[3,2],[1,0]]
Output: 0

Constraints:
m == grid.length
n == grid[i].length
1 <= m, n <= 100
-100 <= grid[i][j] <= 100

Follow up: Could you find an O(n + m) solution?
```

<details><summary>Hint</summary>

```text
1. Use binary search for optimization or simply brute force.
```

</details>

</details>

<details><summary>C</summary>

```c
int countNegatives(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int count = 0;
    int shift = 0;
    int i, j;
    for (i = 0; i < gridSize; ++i) {
        shift = count;
        count = 0;
        for (j = gridColSize[i] - 1 - shift; j >= 0; --j) {
            if (grid[i][j] < 0) {
                ++count;
            }
        }
        retVal += count;
        retVal += shift;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int countNegatives(vector<vector<int>>& grid) {
        int retVal = 0;

        int gridSize = grid.size();
        int gridColSize = 0;

        int count = 0;
        int shift = 0;
        int i, j;
        for (i = 0; i < gridSize; ++i) {
            shift = count;
            count = 0;
            gridColSize = grid[i].size();
            for (j = gridColSize - 1 - shift; j >= 0; --j) {
                if (grid[i][j] < 0) {
                    ++count;
                }
            }
            retVal += count;
            retVal += shift;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def countNegatives(self, grid: List[List[int]]) -> int:
        retVal = 0

        gridSize = len(grid)

        count = 0
        shift = 0
        for i in range(gridSize):
            shift = count
            count = 0
            gridColSize = len(grid[i])
            for j in range(gridColSize - 1 - shift, -1, -1):
                if grid[i][j] < 0:
                    count += 1

            retVal += count
            retVal += shift

        return retVal
```

</details>

## [1380. Lucky Numbers in a Matrix](https://leetcode.com/problems/lucky-numbers-in-a-matrix/)  1207

- [Official](https://leetcode.com/problems/lucky-numbers-in-a-matrix/editorial/)
- [Official](https://leetcode.cn/problems/lucky-numbers-in-a-matrix/solutions/241888/ju-zhen-zhong-de-xing-yun-shu-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given an m x n matrix of distinct numbers, return all lucky numbers in the matrix in any order.

A lucky number is an element of the matrix such that it is the minimum element in its row and maximum in its column.

Example 1:
Input: matrix = [[3,7,8],[9,11,13],[15,16,17]]
Output: [15]
Explanation: 15 is the only lucky number since it is the minimum in its row and the maximum in its column.

Example 2:
Input: matrix = [[1,10,4,2],[9,3,8,7],[15,16,17,12]]
Output: [12]
Explanation: 12 is the only lucky number since it is the minimum in its row and the maximum in its column.

Example 3:
Input: matrix = [[7,8],[1,2]]
Output: [7]
Explanation: 7 is the only lucky number since it is the minimum in its row and the maximum in its column.

Constraints:
m == mat.length
n == mat[i].length
1 <= n, m <= 50
1 <= matrix[i][j] <= 10^5.
All elements in the matrix are distinct.
```

<details><summary>Hint</summary>

```text
1. Find out and save the minimum of each row and maximum of each column in two lists.
2. Then scan through the whole matrix to identify the elements that satisfy the criteria.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* luckyNumbers(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int*)malloc(matrixSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (matrixSize * sizeof(int)));

    int rowSize = matrixSize;
    int colSize;
    int value;
    int luckyIndex, luckyValue;
    int row, col, x;
    for (row = 0; row < rowSize; ++row) {
        luckyIndex = 0;
        luckyValue = matrix[row][luckyIndex];

        colSize = matrixColSize[row];
        for (col = 0; col < colSize; ++col) {
            value = matrix[row][col];
            if (value < luckyValue) {
                luckyIndex = col;
                luckyValue = value;
            }
        }

        for (x = 0; x < rowSize; ++x) {
            if (matrix[x][luckyIndex] > luckyValue) {
                luckyIndex = -1;
                break;
            }
        }

        if (luckyIndex != -1) {
            pRetVal[(*returnSize)] = luckyValue;
            (*returnSize) += 1;
        }
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> luckyNumbers(vector<vector<int>>& matrix) {
        vector<int> retVal;

        int rowSize = matrix.size();
        for (int row = 0; row < rowSize; ++row) {
            int luckyIndex = 0;
            int luckyValue = matrix[row][luckyIndex];

            int colSize = matrix[row].size();
            for (int col = 0; col < colSize; ++col) {
                int value = matrix[row][col];
                if (value < luckyValue) {
                    luckyIndex = col;
                    luckyValue = value;
                }
            }

            for (int x = 0; x < rowSize; ++x) {
                if (matrix[x][luckyIndex] > luckyValue) {
                    luckyIndex = -1;
                    break;
                }
            }

            if (luckyIndex != -1) {
                retVal.emplace_back(luckyValue);
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
    def luckyNumbers(self, matrix: List[List[int]]) -> List[int]:
        retVal = []

        for rowEntry in matrix:
            luckyIndex = 0
            luckyValue = rowEntry[luckyIndex]
            for key, value in enumerate(rowEntry):
                if value < luckyValue:
                    luckyIndex = key
                    luckyValue = value

            for rowEntry in matrix:
                value = rowEntry[luckyIndex]
                if value > luckyValue:
                    luckyIndex = -1
                    break

            if luckyIndex != -1:
                retVal.append(luckyValue)

        return retVal
```

</details>

## [1431. Kids With the Greatest Number of Candies](https://leetcode.com/problems/kids-with-the-greatest-number-of-candies/)  1176

- [Official](https://leetcode.cn/problems/kids-with-the-greatest-number-of-candies/solutions/269245/yong-you-zui-duo-tang-guo-de-hai-zi-by-leetcode-so/)

<details><summary>Description</summary>

```text
There are n kids with candies.
You are given an integer array candies, where each candies[i] represents the number of candies the ith kid has,
and an integer extraCandies, denoting the number of extra candies that you have.

Return a boolean array result of length n, where result[i] is true if, after giving the ith kid all the extraCandies,
they will have the greatest number of candies among all the kids, or false otherwise.

Note that multiple kids can have the greatest number of candies.

Example 1:
Input: candies = [2,3,5,1,3], extraCandies = 3
Output: [true,true,true,false,true]
Explanation: If you give all extraCandies to:
- Kid 1, they will have 2 + 3 = 5 candies, which is the greatest among the kids.
- Kid 2, they will have 3 + 3 = 6 candies, which is the greatest among the kids.
- Kid 3, they will have 5 + 3 = 8 candies, which is the greatest among the kids.
- Kid 4, they will have 1 + 3 = 4 candies, which is not the greatest among the kids.
- Kid 5, they will have 3 + 3 = 6 candies, which is the greatest among the kids.

Example 2:
Input: candies = [4,2,1,1,2], extraCandies = 1
Output: [true,false,false,false,false]
Explanation: There is only 1 extra candy.
Kid 1 will always have the greatest number of candies, even if a different kid is given the extra candy.

Example 3:
Input: candies = [12,1,12], extraCandies = 10
Output: [true,false,true]

Constraints:
n == candies.length
2 <= n <= 100
1 <= candies[i] <= 100
1 <= extraCandies <= 50
```

<details><summary>Hint</summary>

```text
1. Use greedy approach. For each kid check if candies[i] + extraCandies ≥ maximum in Candies[i].
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* kidsWithCandies(int* candies, int candiesSize, int extraCandies, int* returnSize) {
    bool* pRetVal = NULL;

    (*returnSize) = candiesSize;
    pRetVal = (bool*)malloc((*returnSize) * sizeof(bool));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, false, ((*returnSize) * sizeof(bool)));

    int i;
    int maxCandy = candies[0];
    for (i = 1; i < candiesSize; ++i) {
        maxCandy = fmax(maxCandy, candies[i]);
    }
    for (i = 0; i < candiesSize; ++i) {
        if (candies[i] + extraCandies >= maxCandy) {
            pRetVal[i] = true;
        } else {
            pRetVal[i] = false;
        }
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        vector<bool> retVal;

        int maxCandy = *max_element(candies.begin(), candies.end());
        for (auto candy : candies) {
            if (candy + extraCandies >= maxCandy) {
                retVal.emplace_back(true);
            } else {
                retVal.emplace_back(false);
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
    def kidsWithCandies(self, candies: List[int], extraCandies: int) -> List[bool]:
        retVal = []

        maxCandy = max(candies)
        for candy in candies:
            if candy + extraCandies >= maxCandy:
                retVal.append(True)
            else:
                retVal.append(False)

        return retVal
```

</details>

## [1464. Maximum Product of Two Elements in an Array](https://leetcode.com/problems/maximum-product-of-two-elements-in-an-array/)  1121

- [Official](https://leetcode.com/problems/maximum-product-of-two-elements-in-an-array/editorial/)
- [Official](https://leetcode.cn/problems/maximum-product-of-two-elements-in-an-array/solutions/1774263/shu-zu-zhong-liang-yuan-su-de-zui-da-che-oqkf/)

<details><summary>Description</summary>

```text
Given the array of integers nums, you will choose two different indices i and j of that array.
Return the maximum value of (nums[i]-1)*(nums[j]-1).

Example 1:
Input: nums = [3,4,5,2]
Output: 12
Explanation: If you choose the indices i=1 and j=2 (indexed from 0), you will get the maximum value,
that is, (nums[1]-1)*(nums[2]-1) = (4-1)*(5-1) = 3*4 = 12.

Example 2:
Input: nums = [1,5,4,5]
Output: 16
Explanation: Choosing the indices i=1 and j=3 (indexed from 0), you will get the maximum value of (5-1)*(5-1) = 16.

Example 3:
Input: nums = [3,7]
Output: 12

Constraints:
2 <= nums.length <= 500
1 <= nums[i] <= 10^3
```

<details><summary>Hint</summary>

```text
1. Use brute force: two loops to select i and j, then select the maximum value of (nums[i]-1)*(nums[j]-1).
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
int maxProduct(int* nums, int numsSize) {
    int retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);
    int first = nums[0] - 1;
    int second = nums[1] - 1;
    retVal = first * second;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxProduct(vector<int>& nums) {
        int retVal = 0;

        sort(nums.begin(), nums.end(), greater());
        int first = nums[0] - 1;
        int second = nums[1] - 1;
        retVal = first * second;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        retVal = 0

        nums.sort(reverse=True)
        first = nums[0] - 1
        second = nums[1] - 1
        retVal = first * second

        return retVal
```

</details>

## [1470. Shuffle the Array](https://leetcode.com/problems/shuffle-the-array/)  1120

- [Official](https://leetcode.com/problems/shuffle-the-array/solutions/2973933/shuffle-the-array/)
- [Official](https://leetcode.cn/problems/shuffle-the-array/solutions/1776605/zhong-xin-pai-lie-shu-zu-by-leetcode-sol-1eps/)

<details><summary>Description</summary>

```text
Given the array nums consisting of 2n elements in the form [x1,x2,...,xn,y1,y2,...,yn].

Return the array in the form [x1,y1,x2,y2,...,xn,yn].

Example 1:
Input: nums = [2,5,1,3,4,7], n = 3
Output: [2,3,5,4,1,7]
Explanation: Since x1=2, x2=5, x3=1, y1=3, y2=4, y3=7 then the answer is [2,3,5,4,1,7].

Example 2:
Input: nums = [1,2,3,4,4,3,2,1], n = 4
Output: [1,4,2,3,3,2,4,1]

Example 3:
Input: nums = [1,1,2,2], n = 2
Output: [1,2,1,2]

Constraints:
1 <= n <= 500
nums.length == 2n
1 <= nums[i] <= 10^3
```

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* shuffle(int* nums, int numsSize, int n, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = numsSize;
    pRetVal = (int*)calloc((*returnSize), sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        (*returnSize) = 0;
        return pRetVal;
    }

    int i;
    for (i = 0; i < n; ++i) {
        pRetVal[2 * i] = nums[i];
        pRetVal[2 * i + 1] = nums[i + n];
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> shuffle(vector<int>& nums, int n) {
        vector<int> retVal;

        for (int i = 0; i < n; ++i) {
            retVal.push_back(nums[i]);
            retVal.push_back(nums[i + n]);
        }

        return retVal;
    }
};
```

</details>

## [1491. Average Salary Excluding the Minimum and Maximum Salary](https://leetcode.com/problems/average-salary-excluding-the-minimum-and-maximum-salary/)  1201

- [Official](https://leetcode.com/problems/average-salary-excluding-the-minimum-and-maximum-salary/editorial/)

<details><summary>Description</summary>

```text
You are given an array of unique integers salary where salary[i] is the salary of the ith employee.

Return the average salary of employees excluding the minimum and maximum salary.
Answers within 10-5 of the actual answer will be accepted.

Example 1:
Input: salary = [4000,3000,1000,2000]
Output: 2500.00000
Explanation: Minimum salary and maximum salary are 1000 and 4000 respectively.
Average salary excluding minimum and maximum salary is (2000+3000) / 2 = 2500

Example 2:
Input: salary = [1000,2000,3000]
Output: 2000.00000
Explanation: Minimum salary and maximum salary are 1000 and 3000 respectively.
Average salary excluding minimum and maximum salary is (2000) / 1 = 2000

Constraints:
3 <= salary.length <= 100
1000 <= salary[i] <= 10^6
All the integers of salary are unique.
```

<details><summary>Hint</summary>

```text
1. Get the total sum and subtract the minimum and maximum value in the array. Finally divide the result by n - 2.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
double average(int* salary, int salarySize) {
    double retVal = 0;

    double sum = 0;
    int i;
#if (1)
    int max = salary[0];
    int min = salary[0];
    for (i = 0; i < salarySize; ++i) {
        max = ((max > salary[i]) ? max : salary[i]);
        min = ((min < salary[i]) ? min : salary[i]);
        sum += salary[i];
    }
    sum = sum - max - min;
#else
    qsort(salary, salarySize, sizeof(int), compareInteger);
    for (i = 1; i < (salarySize - 1); ++i) {
        sum += salary[i];
    }
#endif
    retVal = sum / (salarySize - 2);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    double average(vector<int>& salary) {
        double retVal = 0;

        int salarySize = salary.size();
        double sum = 0;
#if (1)
        sum = accumulate(salary.begin(), salary.end(), 0.);
        sum = sum - *max_element(salary.begin(), salary.end()) - *min_element(salary.begin(), salary.end());
#else
        sort(salary.begin(), salary.end());
        for (int i = 1; i < (salarySize - 1); ++i) {
            sum += salary[i];
        }
#endif
        retVal = sum / (salarySize - 2);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def average(self, salary: List[int]) -> float:
        retVal = 0

        # salary.sort()
        # retVal = sum(salary[1:-1]) / (len(salary) - 2)
        retVal = (sum(salary) - max(salary) - min(salary)) / (len(salary) - 2)

        return retVal
```

</details>

## [1503. Last Moment Before All Ants Fall Out of a Plank](https://leetcode.com/problems/last-moment-before-all-ants-fall-out-of-a-plank/)  1618

- [Official](https://leetcode.com/problems/last-moment-before-all-ants-fall-out-of-a-plank/editorial/)

<details><summary>Description</summary>

```text
We have a wooden plank of the length n units.
Some ants are walking on the plank, each ant moves with a speed of 1 unit per second.
Some of the ants move to the left, the other move to the right.

When two ants moving in two different directions meet at some point,
they change their directions and continue moving again.
Assume changing directions does not take any additional time.

When an ant reaches one end of the plank at a time t, it falls out of the plank immediately.

Given an integer n and two integer arrays left and right, the positions of the ants moving to the left and the right,
return the moment when the last ant(s) fall out of the plank.

Example 1:
Input: n = 4, left = [4,3], right = [0,1]
Output: 4
Explanation: In the image above:
-The ant at index 0 is named A and going to the right.
-The ant at index 1 is named B and going to the right.
-The ant at index 3 is named C and going to the left.
-The ant at index 4 is named D and going to the left.
The last moment when an ant was on the plank is t = 4 seconds.
After that, it falls immediately out of the plank.
(i.e., We can say that at t = 4.0000000001, there are no ants on the plank).

Example 2:
Input: n = 7, left = [], right = [0,1,2,3,4,5,6,7]
Output: 7
Explanation: All ants are going to the right, the ant at index 0 needs 7 seconds to fall.

Example 3:
Input: n = 7, left = [0,1,2,3,4,5,6,7], right = []
Output: 7
Explanation: All ants are going to the left, the ant at index 7 needs 7 seconds to fall.

Constraints:
1 <= n <= 10^4
0 <= left.length <= n + 1
0 <= left[i] <= n
0 <= right.length <= n + 1
0 <= right[i] <= n
1 <= left.length + right.length <= n + 1
All values of left and right are unique, and each value can appear only in one of the two arrays.
```

<details><summary>Hint</summary>

```text
1. The ants change their way when they meet is equivalent to continue moving without changing their direction.
2. Answer is the max distance for one ant to reach the end of the plank in the facing direction.
```

</details>

</details>

<details><summary>C</summary>

```c
int getLastMoment(int n, int* left, int leftSize, int* right, int rightSize) {
    int retVal = 0;

    /* Brainteaser
     *  最後一隻螞蟻從木板上掉下來的時刻，所以並不需要區分每隻螞蟻。
     *  由於改變移動方向不花費額外時間，而且改變移動方向後的移動速度不變。
     *  因此，兩隻相遇的螞蟻同時改變移動方向之後的情形等價於兩隻螞蟻都不改變移動方向，繼續以原來的方向和速度移動。
     *  這樣問題就簡化成根據每隻螞蟻的初始位置和移動方向得到最後一隻螞蟻到達木板邊界的時刻。
     *  假設一隻螞蟻在位置 p。
     *  如果這隻螞蟻向左移動，則它到達木板邊界所需的時間是 p。
     *  如果這隻螞蟻向右移動，則它到達木板邊界所需的時間是 n−p。
     */
    int i;
    for (i = 0; i < leftSize; ++i) {
        retVal = fmax(retVal, left[i]);
    }
    for (i = 0; i < rightSize; ++i) {
        retVal = fmax(retVal, n - right[i]);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int getLastMoment(int n, vector<int>& left, vector<int>& right) {
        int retVal = 0;

        /* Brainteaser
         *  最後一隻螞蟻從木板上掉下來的時刻，所以並不需要區分每隻螞蟻。
         *  由於改變移動方向不花費額外時間，而且改變移動方向後的移動速度不變。
         *  因此，兩隻相遇的螞蟻同時改變移動方向之後的情形等價於兩隻螞蟻都不改變移動方向，繼續以原來的方向和速度移動。
         *  這樣問題就簡化成根據每隻螞蟻的初始位置和移動方向得到最後一隻螞蟻到達木板邊界的時刻。
         *  假設一隻螞蟻在位置 p。
         *  如果這隻螞蟻向左移動，則它到達木板邊界所需的時間是 p。
         *  如果這隻螞蟻向右移動，則它到達木板邊界所需的時間是 n−p。
         */
        for (int p : left) {
            retVal = max(retVal, p);
        }
        for (int p : right) {
            retVal = max(retVal, n - p);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def getLastMoment(self, n: int, left: List[int], right: List[int]) -> int:
        retVal = 0

        # /* Brainteaser
        #  *  最後一隻螞蟻從木板上掉下來的時刻，所以並不需要區分每隻螞蟻。
        #  *  由於改變移動方向不花費額外時間，而且改變移動方向後的移動速度不變。
        #  *  因此，兩隻相遇的螞蟻同時改變移動方向之後的情形等價於兩隻螞蟻都不改變移動方向，繼續以原來的方向和速度移動。
        #  *  這樣問題就簡化成根據每隻螞蟻的初始位置和移動方向得到最後一隻螞蟻到達木板邊界的時刻。
        #  *  假設一隻螞蟻在位置 p。
        #  *  如果這隻螞蟻向左移動，則它到達木板邊界所需的時間是 p。
        #  *  如果這隻螞蟻向右移動，則它到達木板邊界所需的時間是 n−p。
        #  */
        for p in left:
            retVal = max(retVal, p)
        for p in right:
            retVal = max(retVal, n - p)

        return retVal
```

</details>

## [1508. Range Sum of Sorted Subarray Sums](https://leetcode.com/problems/range-sum-of-sorted-subarray-sums/)  1402

- [Official](https://leetcode.com/problems/range-sum-of-sorted-subarray-sums/editorial/)
- [Official](https://leetcode.cn/problems/range-sum-of-sorted-subarray-sums/solutions/371273/zi-shu-zu-he-pai-xu-hou-de-qu-jian-he-by-leetcode-/)

<details><summary>Description</summary>

```text
You are given the array nums consisting of n positive integers.
You computed the sum of all non-empty continuous subarrays from the array and then sorted them in non-decreasing order,
creating a new array of n * (n + 1) / 2 numbers.

Return the sum of the numbers from index left to index right (indexed from 1), inclusive, in the new array.
Since the answer can be a huge number return it modulo 109 + 7.

Example 1:
Input: nums = [1,2,3,4], n = 4, left = 1, right = 5
Output: 13
Explanation: All subarray sums are 1, 3, 6, 10, 2, 5, 9, 3, 7, 4.
After sorting them in non-decreasing order we have the new array [1, 2, 3, 3, 4, 5, 6, 7, 9, 10].
The sum of the numbers from index le = 1 to ri = 5 is 1 + 2 + 3 + 3 + 4 = 13.

Example 2:
Input: nums = [1,2,3,4], n = 4, left = 3, right = 4
Output: 6
Explanation: The given array is the same as example 1. We have the new array [1, 2, 3, 3, 4, 5, 6, 7, 9, 10].
The sum of the numbers from index le = 3 to ri = 4 is 3 + 3 = 6.

Example 3:
Input: nums = [1,2,3,4], n = 4, left = 1, right = 10
Output: 50

Constraints:
n == nums.length
1 <= nums.length <= 1000
1 <= nums[i] <= 100
1 <= left <= right <= n * (n + 1) / 2
```

<details><summary>Hint</summary>

```text
1. Compute all sums and save it in array.
2. Then just go from LEFT to RIGHT index and calculate answer modulo 1e9 + 7.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MODULO (int)(1e9 + 7)
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int rangeSum(int* nums, int numsSize, int n, int left, int right) {
    int retVal = 0;

    int numsSumSize = n * (n + 1) / 2;
    int numsSum[numsSumSize];
    memset(numsSum, 0, sizeof(numsSum));
    int numsSumIdx = 0;

    int idx, start, sum;
    for (start = 0; start < numsSize; ++start) {
        sum = 0;
        for (idx = start; idx < numsSize; ++idx) {
            sum += nums[idx];
            numsSum[numsSumIdx++] = sum;
        }
    }
    qsort(numsSum, numsSumIdx, sizeof(int), compareInteger);

    for (idx = left - 1; idx < right; ++idx) {
        retVal += numsSum[idx];
        retVal %= MODULO;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define MODULO (int)(1e9 + 7)
   public:
    int rangeSum(vector<int>& nums, int n, int left, int right) {
        int retVal = 0;

        int numsSize = nums.size();

        vector<int> numsSum;
        for (int start = 0; start < numsSize; ++start) {
            int sum = 0;
            for (int idx = start; idx < numsSize; ++idx) {
                sum += nums[idx];
                numsSum.emplace_back(sum);
            }
        }
        sort(numsSum.begin(), numsSum.end());

        for (int idx = left - 1; idx < right; ++idx) {
            retVal += numsSum[idx];
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

    def rangeSum(self, nums: List[int], n: int, left: int, right: int) -> int:
        retVal = 0

        numsSize = len(nums)

        numsSum = []
        for start in range(numsSize):
            sum = 0
            for idx in range(start, numsSize):
                sum += nums[idx]
                numsSum.append(sum)
        numsSum.sort()

        for idx in range(left-1, right):
            retVal += numsSum[idx]
            retVal %= self.MODULO

        return retVal
```

</details>

## [1535. Find the Winner of an Array Game](https://leetcode.com/problems/find-the-winner-of-an-array-game/)  1433

- [Official](https://leetcode.com/problems/find-the-winner-of-an-array-game/editorial/)
- [Official](https://leetcode.cn/problems/find-the-winner-of-an-array-game/solutions/371344/zhao-chu-shu-zu-you-xi-de-ying-jia-by-leetcode-sol/)

<details><summary>Description</summary>

```text
Given an integer array arr of distinct integers and an integer k.

A game will be played between the first two elements of the array (i.e. arr[0] and arr[1]).
In each round of the game, we compare arr[0] with arr[1], the larger integer wins and remains at position 0,
and the smaller integer moves to the end of the array.
The game ends when an integer wins k consecutive rounds.

Return the integer which will win the game.

It is guaranteed that there will be a winner of the game.

Example 1:
Input: arr = [2,1,3,5,4,6,7], k = 2
Output: 5
Explanation: Let's see the rounds of the game:
Round |       arr       | winner | win_count
  1   | [2,1,3,5,4,6,7] | 2      | 1
  2   | [2,3,5,4,6,7,1] | 3      | 1
  3   | [3,5,4,6,7,1,2] | 5      | 1
  4   | [5,4,6,7,1,2,3] | 5      | 2
So we can see that 4 rounds will be played and 5 is the winner because it wins 2 consecutive games.

Example 2:
Input: arr = [3,2,1], k = 10
Output: 3
Explanation: 3 will win the first 10 rounds consecutively.

Constraints:
2 <= arr.length <= 10^5
1 <= arr[i] <= 10^6
arr contains distinct integers.
1 <= k <= 10^9
```

<details><summary>Hint</summary>

```text
1. If k ≥ arr.length return the max element of the array.
2. If k < arr.length simulate the game until a number wins k consecutive games.
```

</details>

</details>

<details><summary>C</summary>

```c
int getWinner(int* arr, int arrSize, int k) {
    int retVal = 0;

    int winRounds = 0;
    int winIdx = 0;
    int nextIdx;
    for (nextIdx = 1; nextIdx < arrSize; ++nextIdx) {  // 2 <= arr.length <= 10^5
        if (arr[winIdx] > arr[nextIdx]) {
            winRounds += 1;
        } else if (arr[winIdx] < arr[nextIdx]) {
            winIdx = nextIdx;
            winRounds = 1;
        } else if (arr[winIdx] == arr[nextIdx]) {
            // arr contains distinct integers.
            continue;
        }

        if (winRounds == k) {
            break;
        }
    }
    retVal = arr[winIdx];

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int getWinner(vector<int>& arr, int k) {
        int retVal = 0;

        int arrSize = arr.size();

        int winRounds = 0;
        int winIdx = 0;
        int nextIdx;
        for (nextIdx = 1; nextIdx < arrSize; ++nextIdx) {  // 2 <= arr.length <= 10^5
            if (arr[winIdx] > arr[nextIdx]) {
                winRounds += 1;
            } else if (arr[winIdx] < arr[nextIdx]) {
                winIdx = nextIdx;
                winRounds = 1;
            } else if (arr[winIdx] == arr[nextIdx]) {
                // arr contains distinct integers.
                continue;
            }

            if (winRounds == k) {
                break;
            }
        }
        retVal = arr[winIdx];

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def getWinner(self, arr: List[int], k: int) -> int:
        retVal = 0

        arrSize = len(arr)

        winRounds = 0
        winIdx = 0
        for nextIdx in range(1, arrSize):  # 2 <= arr.length <= 10^5
            if arr[winIdx] > arr[nextIdx]:
                winRounds += 1
            elif arr[winIdx] < arr[nextIdx]:
                winIdx = nextIdx
                winRounds = 1
            elif arr[winIdx] == arr[nextIdx]:  # arr contains distinct integers.
                pass

            if winRounds == k:
                break

        retVal = arr[winIdx]

        return retVal
```

</details>

## [1550. Three Consecutive Odds](https://leetcode.com/problems/three-consecutive-odds/)  1221

- [Official](https://leetcode.com/problems/three-consecutive-odds/editorial/)
- [Official](https://leetcode.cn/problems/three-consecutive-odds/solutions/382537/cun-zai-lian-xu-san-ge-qi-shu-de-shu-zu-by-leetcod/)

<details><summary>Description</summary>

```text
Given an integer array arr, return true if there are three consecutive odd numbers in the array. Otherwise, return false.

Example 1:
Input: arr = [2,6,4,1]
Output: false
Explanation: There are no three consecutive odds.

Example 2:
Input: arr = [1,2,34,3,4,5,7,23,12]
Output: true
Explanation: [5,7,23] are three consecutive odds.

Constraints:
1 <= arr.length <= 1000
1 <= arr[i] <= 1000
```

<details><summary>Hint</summary>

```text
1. Check every three consecutive numbers in the array for parity.
```

</details>

</details>

<details><summary>C</summary>

```c
bool threeConsecutiveOdds(int* arr, int arrSize) {
    bool retVal = false;

    int consecutiveOdds = 0;
    int i;
    for (i = 0; i < arrSize; ++i) {
        if (arr[i] % 2 == 0) {
            consecutiveOdds = 0;
        } else {
            consecutiveOdds += 1;
            if (consecutiveOdds == 3) {
                retVal = true;
                break;
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
    bool threeConsecutiveOdds(vector<int>& arr) {
        bool retVal = false;

        int consecutiveOdds = 0;
        for (int num : arr) {
            if (num % 2 == 0) {
                consecutiveOdds = 0;
            } else {
                consecutiveOdds += 1;
                if (consecutiveOdds == 3) {
                    retVal = true;
                    break;
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
    def threeConsecutiveOdds(self, arr: List[int]) -> bool:
        retVal = False

        consecutiveOdds = 0
        for num in arr:
            if num % 2 == 0:
                consecutiveOdds = 0
            else:
                consecutiveOdds += 1
                if consecutiveOdds == 3:
                    retVal = True
                    break

        return retVal
```

</details>

## [1572. Matrix Diagonal Sum](https://leetcode.com/problems/matrix-diagonal-sum/)  1280

- [Official](https://leetcode.com/problems/matrix-diagonal-sum/editorial/)
- [Official](https://leetcode.cn/problems/matrix-diagonal-sum/solutions/441166/ju-zhen-dui-jiao-xian-yuan-su-de-he-by-leetcode-so/)

<details><summary>Description</summary>

```text
Given a square matrix mat, return the sum of the matrix diagonals.

Only include the sum of all the elements on the primary diagonal
and all the elements on the secondary diagonal that are not part of the primary diagonal.

Example 1:
Input: mat = [[1,2,3],
              [4,5,6],
              [7,8,9]]
Output: 25
Explanation: Diagonals sum: 1 + 5 + 9 + 3 + 7 = 25
Notice that element mat[1][1] = 5 is counted only once.

Example 2:
Input: mat = [[1,1,1,1],
              [1,1,1,1],
              [1,1,1,1],
              [1,1,1,1]]
Output: 8

Example 3:
Input: mat = [[5]]
Output: 5

Constraints:
n == mat.length == mat[i].length
1 <= n <= 100
1 <= mat[i][j] <= 100
```

<details><summary>Hint</summary>

```text
1. There will be overlap of elements in the primary and secondary diagonals
   if and only if the length of the matrix is odd, which is at the center.
```

</details>

</details>

<details><summary>C</summary>

```c
int diagonalSum(int** mat, int matSize, int* matColSize) {
    int retVal = 0;

    int i;
    for (i = 0; i < matSize; ++i) {
        retVal += mat[i][i];
        retVal += mat[i][matColSize[i] - 1 - i];
    }
    if (matSize % 2 == 1) {
        retVal -= mat[matSize / 2][matSize / 2];
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int diagonalSum(vector<vector<int>>& mat) {
        int retVal = 0;

        int row = mat.size();
        for (int i = 0; i < row; ++i) {
            retVal += mat[i][i];
            retVal += mat[i][mat[i].size() - 1 - i];
        }
        if (row % 2 == 1) {
            retVal -= mat[row / 2][row / 2];
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def diagonalSum(self, mat: List[List[int]]) -> int:
        retVal = 0

        row = len(mat)
        for i in range(row):
            retVal += mat[i][i]
            retVal += mat[i][len(mat[i]) - 1 - i]
        if row % 2 == 1:
            retVal -= mat[row // 2][row // 2]

        return retVal
```

</details>

## [1582. Special Positions in a Binary Matrix](https://leetcode.com/problems/special-positions-in-a-binary-matrix/)  1321

- [Official](https://leetcode.com/problems/special-positions-in-a-binary-matrix/editorial/)
- [Official](https://leetcode.cn/problems/special-positions-in-a-binary-matrix/solutions/1796614/er-jin-zhi-ju-zhen-zhong-de-te-shu-wei-z-kan4/)

<details><summary>Description</summary>

```text
Given an m x n binary matrix mat, return the number of special positions in mat.

A position (i, j) is called special if mat[i][j] == 1 and
all other elements in row i and column j are 0 (rows and columns are 0-indexed).

Example 1:
Input: mat = [[1,0,0],[0,0,1],[1,0,0]]
Output: 1
Explanation: (1, 2) is a special position because mat[1][2] == 1 and all other elements in row 1 and column 2 are 0.

Example 2:
Input: mat = [[1,0,0],[0,1,0],[0,0,1]]
Output: 3
Explanation: (0, 0), (1, 1) and (2, 2) are special positions.

Constraints:
m == mat.length
n == mat[i].length
1 <= m, n <= 100
mat[i][j] is either 0 or 1.
```

<details><summary>Hint</summary>

```text
1. Keep track of 1s in each row and in each column. Then while iterating over matrix,
   if the current position is 1 and current row as well as current column contains exactly one occurrence of 1.
```

</details>

</details>

<details><summary>C</summary>

```c
int numSpecial(int** mat, int matSize, int* matColSize) {
    int retVal = 0;

    // m == mat.length, n == mat[i].length, 1 <= m, n <= 100.
    int rowSize = matSize;
    int colSize = matColSize[0];

    int rowSum[rowSize];
    memset(rowSum, 0, sizeof(rowSum));
    int colSum[colSize];
    memset(colSum, 0, sizeof(colSum));

    int i, j;
    for (i = 0; i < rowSize; ++i) {
        for (j = 0; j < colSize; ++j) {
            // mat[i][j] is either 0 or 1.
            rowSum[i] += mat[i][j];
            colSum[j] += mat[i][j];
        }
    }

    for (i = 0; i < rowSize; ++i) {
        for (j = 0; j < colSize; ++j) {
            if (mat[i][j] != 1) {
                continue;
            }
            if ((rowSum[i] == 1) && (colSum[j] == 1)) {
                retVal += 1;
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
    int numSpecial(vector<vector<int>>& mat) {
        int retVal = 0;

        // m == mat.length, n == mat[i].length, 1 <= m, n <= 100.
        int rowSize = mat.size();
        int colSize = mat[0].size();

        vector<int> rowSum(rowSize, 0);
        vector<int> colSum(colSize, 0);
        for (int i = 0; i < rowSize; ++i) {
            for (int j = 0; j < colSize; ++j) {
                // mat[i][j] is either 0 or 1.
                rowSum[i] += mat[i][j];
                colSum[j] += mat[i][j];
            }
        }

        for (int i = 0; i < rowSize; ++i) {
            for (int j = 0; j < colSize; ++j) {
                if (mat[i][j] != 1) {
                    continue;
                }
                if ((rowSum[i] == 1) && (colSum[j] == 1)) {
                    retVal += 1;
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
    def numSpecial(self, mat: List[List[int]]) -> int:
        retVal = 0

        # m == mat.length, n == mat[i].length, 1 <= m, n <= 100.
        rowSize = len(mat)
        colSize = len(mat[0])

        rowSum = [0] * rowSize
        colSum = [0] * colSize
        for i in range(rowSize):
            for j in range(colSize):
                # mat[i][j] is either 0 or 1.
                rowSum[i] += mat[i][j]
                colSum[j] += mat[i][j]

        for i in range(rowSize):
            for j in range(colSize):
                if mat[i][j] != 1:
                    continue
                if (rowSum[i] == 1) and (colSum[j] == 1):
                    retVal += 1

        return retVal
```

</details>

## [1608. Special Array With X Elements Greater Than or Equal X](https://leetcode.com/problems/special-array-with-x-elements-greater-than-or-equal-x/)  1369

- [Official](https://leetcode.com/problems/special-array-with-x-elements-greater-than-or-equal-x/editorial/)
- [Official](https://leetcode.cn/problems/special-array-with-x-elements-greater-than-or-equal-x/solutions/1816575/te-shu-shu-zu-de-te-zheng-zhi-by-leetcod-9wfo/)

<details><summary>Description</summary>

```text
You are given an array nums of non-negative integers.
nums is considered special if there exists a number x such that
there are exactly x numbers in nums that are greater than or equal to x.

Notice that x does not have to be an element in nums.

Return x if the array is special, otherwise, return -1.
It can be proven that if nums is special, the value for x is unique.

Example 1:
Input: nums = [3,5]
Output: 2
Explanation: There are 2 values (3 and 5) that are greater than or equal to 2.

Example 2:
Input: nums = [0,0]
Output: -1
Explanation: No numbers fit the criteria for x.
If x = 0, there should be 0 numbers >= x, but there are 2.
If x = 1, there should be 1 number >= x, but there are 0.
If x = 2, there should be 2 numbers >= x, but there are 0.
x cannot be greater since there are only 2 numbers in nums.

Example 3:
Input: nums = [0,4,3,0,4]
Output: 3
Explanation: There are 3 values that are greater than or equal to 3.

Constraints:
1 <= nums.length <= 100
0 <= nums[i] <= 1000
```

<details><summary>Hint</summary>

```text
1. Count the number of elements greater than or equal to x for each x in the range [0, nums.length].
2. If for any x, the condition satisfies, return that x. Otherwise, there is no answer.
```

</details>

</details>

<details><summary>C</summary>

```c
int specialArray(int* nums, int numsSize) {
    int retVal = -1;

    int frequency[numsSize + 1];
    memset(frequency, 0, sizeof(frequency));

    int index;
    int i;
    for (i = 0; i < numsSize; ++i) {
        index = fmin(numsSize, nums[i]);
        frequency[index] += 1;
    }

    int greaterThanOrEqual = 0;
    for (i = numsSize; i >= 0; --i) {
        greaterThanOrEqual += frequency[i];
        if (i == greaterThanOrEqual) {
            retVal = i;
            break;
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
    int specialArray(vector<int>& nums) {
        int retVal = -1;

        int numsSize = nums.size();
        vector<int> frequency(numsSize + 1, 0);
        for (int num : nums) {
            int index = min(numsSize, num);
            frequency[index] += 1;
        }

        int greaterThanOrEqual = 0;
        for (int i = numsSize; i >= 0; --i) {
            greaterThanOrEqual += frequency[i];
            if (i == greaterThanOrEqual) {
                retVal = i;
                break;
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
    def specialArray(self, nums: List[int]) -> int:
        retVal = -1

        numsSize = len(nums)
        frequency = [0] * (numsSize+1)
        for num in nums:
            index = min(numsSize, num)
            frequency[index] += 1

        greaterThanOrEqual = 0
        for i in range(numsSize, 0, -1):
            greaterThanOrEqual += frequency[i]
            if i == greaterThanOrEqual:
                retVal = i
                break

        return retVal
```

</details>

## [1662. Check If Two String Arrays are Equivalent](https://leetcode.com/problems/check-if-two-string-arrays-are-equivalent/)  1217

- [Official](https://leetcode.com/problems/check-if-two-string-arrays-are-equivalent/editorial/)
- [Official](https://leetcode.cn/problems/check-if-two-string-arrays-are-equivalent/solutions/1938926/jian-cha-liang-ge-zi-fu-chuan-shu-zu-shi-9iuo/)

<details><summary>Description</summary>

```text
Given two string arrays word1 and word2, return true if the two arrays represent the same string, and false otherwise.

A string is represented by an array if the array elements concatenated in order forms the string.

Example 1:
Input: word1 = ["ab", "c"], word2 = ["a", "bc"]
Output: true
Explanation:
word1 represents string "ab" + "c" -> "abc"
word2 represents string "a" + "bc" -> "abc"
The strings are the same, so return true.

Example 2:
Input: word1 = ["a", "cb"], word2 = ["ab", "c"]
Output: false

Example 3:
Input: word1  = ["abc", "d", "defg"], word2 = ["abcddefg"]
Output: true

Constraints:
1 <= word1.length, word2.length <= 10^3
1 <= word1[i].length, word2[i].length <= 10^3
1 <= sum(word1[i].length), sum(word2[i].length) <= 10^3
word1[i] and word2[i] consist of lowercase letters.
```

<details><summary>Hint</summary>

```text
1. Concatenate all strings in the first array into a single string in the given order, the same for the second array.
2. Both arrays represent the same string if and only if the generated strings are the same.
```

</details>

</details>

<details><summary>C</summary>

```c
bool arrayStringsAreEqual(char** word1, int word1Size, char** word2, int word2Size) {
    bool retVal = false;

    int c1 = 0;
    int c2 = 0;
    int idx1 = 0;
    int idx2 = 0;
    while ((idx1 < word1Size) && (idx2 < word2Size)) {
        // compare characters between word1 and word2
        if (word1[idx1][c1] != word2[idx2][c2]) {
            return retVal;
        }

        // word1 shift, if go to the end, change to next one.
        ++c1;
        if (word1[idx1][c1] == 0) {
            c1 = 0;
            ++idx1;
        }

        // word2 shift, if go to the end, change to next one.
        ++c2;
        if (word2[idx2][c2] == 0) {
            c2 = 0;
            ++idx2;
        }
    }

    if ((idx1 == word1Size) && (idx2 == word2Size)) {
        retVal = true;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) {
        bool retVal = false;

        string words1 = "";
        for (string w : word1) {
            words1 += w;
        }

        string words2 = "";
        for (string w : word2) {
            words2 += w;
        }

        if (words1 == words2) {
            retVal = true;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def arrayStringsAreEqual(self, word1: List[str], word2: List[str]) -> bool:
        retVal = False

        words1 = "".join(word1)
        words2 = "".join(word2)
        if words1 == words2:
            retVal = True

        return retVal
```

</details>

## [1672. Richest Customer Wealth](https://leetcode.com/problems/richest-customer-wealth/)  1182

<details><summary>Description</summary>

```text
You are given an m x n integer grid accounts
where accounts[i][j] is the amount of money the i​​​​​​​​​​​th​​​​ customer has in the j​​​​​​​​​​​th​​​​ bank.
Return the wealth that the richest customer has.

A customer's wealth is the amount of money they have in all their bank accounts.
The richest customer is the customer that has the maximum wealth.

Example 1:
Input: accounts = [[1,2,3],[3,2,1]]
Output: 6
Explanation:
1st customer has wealth = 1 + 2 + 3 = 6
2nd customer has wealth = 3 + 2 + 1 = 6
Both customers are considered the richest with a wealth of 6 each, so return 6.

Example 2:
Input: accounts = [[1,5],[7,3],[3,5]]
Output: 10
Explanation:
1st customer has wealth = 6
2nd customer has wealth = 10
3rd customer has wealth = 8
The 2nd customer is the richest with a wealth of 10.

Example 3:
Input: accounts = [[2,8,7],[7,1,3],[1,9,5]]
Output: 17

Constraints:
m == accounts.length
n == accounts[i].length
1 <= m, n <= 50
1 <= accounts[i][j] <= 100
```

</details>

<details><summary>C</summary>

```c
int maximumWealth(int** accounts, int accountsSize, int* accountsColSize) {
    int retVal = 0;

    int sum;
    int i, j;
    for (i=0; i<accountsSize; ++i) {
        sum = 0;
        for (j=0; j<(*accountsColSize); ++j) {
            sum += accounts[i][j];
        }
        retVal = (retVal>sum)?retVal:sum;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
public:
    int maximumWealth(vector<vector<int>>& accounts) {
        int retVal = 0;

        int sum;
        for (long unsigned int i=0; i<accounts.size(); ++i) {
            sum = 0;
            for (long unsigned int j=0; j<accounts[i].size(); ++j) {
                sum += accounts[i][j];
            }
            retVal = (retVal>sum?retVal:sum);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maximumWealth(self, accounts: List[List[int]]) -> int:
        return max([sum(i) for i in accounts])
```

</details>

## [1701. Average Waiting Time](https://leetcode.com/problems/average-waiting-time/)  1436

- [Official](https://leetcode.com/problems/average-waiting-time/editorial/)

<details><summary>Description</summary>

```text
There is a restaurant with a single chef. You are given an array customers, where customers[i] = [arrivali, timei]:
- arrivali is the arrival time of the ith customer. The arrival times are sorted in non-decreasing order.
- timei is the time needed to prepare the order of the ith customer.

When a customer arrives, he gives the chef his order, and the chef starts preparing it once he is idle.
The customer waits till the chef finishes preparing his order.
The chef does not prepare food for more than one customer at a time.
The chef prepares food for customers in the order they were given in the input.

Return the average waiting time of all customers. Solutions within 10^-5 from the actual answer are considered accepted.

Example 1:
Input: customers = [[1,2],[2,5],[4,3]]
Output: 5.00000
Explanation:
1) The first customer arrives at time 1, the chef takes his order and starts preparing it immediately at time 1,
   and finishes at time 3, so the waiting time of the first customer is 3 - 1 = 2.
2) The second customer arrives at time 2, the chef takes his order and starts preparing it at time 3,
   and finishes at time 8, so the waiting time of the second customer is 8 - 2 = 6.
3) The third customer arrives at time 4, the chef takes his order and starts preparing it at time 8,
   and finishes at time 11, so the waiting time of the third customer is 11 - 4 = 7.
So the average waiting time = (2 + 6 + 7) / 3 = 5.

Example 2:
Input: customers = [[5,2],[5,4],[10,3],[20,1]]
Output: 3.25000
Explanation:
1) The first customer arrives at time 5, the chef takes his order and starts preparing it immediately at time 5,
   and finishes at time 7, so the waiting time of the first customer is 7 - 5 = 2.
2) The second customer arrives at time 5, the chef takes his order and starts preparing it at time 7,
   and finishes at time 11, so the waiting time of the second customer is 11 - 5 = 6.
3) The third customer arrives at time 10, the chef takes his order and starts preparing it at time 11,
   and finishes at time 14, so the waiting time of the third customer is 14 - 10 = 4.
4) The fourth customer arrives at time 20, the chef takes his order and starts preparing it immediately at time 20,
   and finishes at time 21, so the waiting time of the fourth customer is 21 - 20 = 1.
So the average waiting time = (2 + 6 + 4 + 1) / 4 = 3.25.

Constraints:
1 <= customers.length <= 10^5
1 <= arrivali, timei <= 10^4
arrivali <= arrivali+1
```

<details><summary>Hint</summary>

```text
1. Iterate on the customers, maintaining the time the chef will finish the previous orders.
2. If that time is before the current arrival time, the chef starts immediately.
   Else, the current customer waits till the chef finishes, and then the chef starts.
3. Update the running time by the time when the chef starts preparing + preparation time.
```

</details>

</details>

<details><summary>C</summary>

```c
double averageWaitingTime(int** customers, int customersSize, int* customersColSize) {
    double retVal = 0;

    int nextIdleTime = 0;
    double netWaitTime = 0;
    int i;
    for (i = 0; i < customersSize; ++i) {
        nextIdleTime = fmax(customers[i][0], nextIdleTime) + customers[i][1];
        netWaitTime += (nextIdleTime - customers[i][0]);
    }
    retVal = netWaitTime / customersSize;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    double averageWaitingTime(vector<vector<int>>& customers) {
        double retVal = 0;

        int customersSize = customers.size();

        int nextIdleTime = 0;
        double netWaitTime = 0;
        for (int i = 0; i < customersSize; ++i) {
            nextIdleTime = max(customers[i][0], nextIdleTime) + customers[i][1];
            netWaitTime += (nextIdleTime - customers[i][0]);
        }
        retVal = netWaitTime / customersSize;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def averageWaitingTime(self, customers: List[List[int]]) -> float:
        retVal = 0

        nextIdleTime = 0
        netWaitTime = 0
        for customer in customers:
            nextIdleTime = max(customer[0], nextIdleTime) + customer[1]
            netWaitTime += (nextIdleTime - customer[0])

        customersSize = len(customers)
        retVal = netWaitTime / customersSize

        return retVal
```

</details>

## [1752. Check if Array Is Sorted and Rotated](https://leetcode.com/problems/check-if-array-is-sorted-and-rotated/)  1324

- [Official](https://leetcode.cn/problems/check-if-array-is-sorted-and-rotated/solutions/1990942/jian-cha-shu-zu-shi-fou-jing-pai-xu-he-l-cbqk/)

<details><summary>Description</summary>

```text
Given an array nums, return true if the array was originally sorted in non-decreasing order,
then rotated some number of positions (including zero).
Otherwise, return false.

There may be duplicates in the original array.

Note: An array A rotated by x positions results in an array B of the same length such that A[i] == B[(i+x) % A.length],
where % is the modulo operation.

Example 1:
Input: nums = [3,4,5,1,2]
Output: true
Explanation: [1,2,3,4,5] is the original sorted array.
You can rotate the array by x = 3 positions to begin on the the element of value 3: [3,4,5,1,2].

Example 2:
Input: nums = [2,1,3,4]
Output: false
Explanation: There is no sorted array once rotated that can make nums.

Example 3:
Input: nums = [1,2,3]
Output: true
Explanation: [1,2,3] is the original sorted array.
You can rotate the array by x = 0 positions (i.e. no rotation) to make nums.

Constraints:
1 <= nums.length <= 100
1 <= nums[i] <= 100
```

</details>

<details><summary>C</summary>

```c
bool check(int* nums, int numsSize) {
    bool retVal = false;

    int head1 = 0;
    int tail1 = 0;
    int head2 = 0;
    int tail2 = numsSize - 1;

    int i;
    for (i=head1+1; i<numsSize; ++i) {
        if (nums[i-1] <= nums[i]) {
            continue;
        }
        tail1 = i - 1;
        head2 = i;
        break;
    }
    if (i == numsSize) {
        retVal = true;
        return retVal;
    }

    for (i=head2+1; i<numsSize; ++i) {
        if (nums[i-1] <= nums[i]) {
            continue;
        }
        return retVal;
    }

    if ((nums[head1]<nums[head2]) || (nums[head1]<nums[tail2])) {
        return retVal;
    }
    else if ((nums[tail1]<nums[head2]) || (nums[tail1]<nums[tail2])) {
        return retVal;
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
    bool check(vector<int>& nums) {
        bool retVal = true;

        int numsSize = nums.size();
        int idx = 0;
        for (int i = 1; i < numsSize; ++i) {
            if (nums[i - 1] > nums[i]) {
                idx = i;
                break;
            }
        }
        if (idx == 0) {
            return retVal;
        }

        for (int i = idx + 1; i < numsSize; ++i) {
            if (nums[i - 1] > nums[i]) {
                retVal = false;
                return retVal;
            }
        }

        if (nums[0] < nums[numsSize - 1]) {
            retVal = false;
        }

        return retVal;
    }
};
```

</details>

## [1769. Minimum Number of Operations to Move All Balls to Each Box](https://leetcode.com/problems/minimum-number-of-operations-to-move-all-balls-to-each-box/)  1294

<details><summary>Description</summary>

- [Official](https://leetcode.com/problems/minimum-number-of-operations-to-move-all-balls-to-each-box/editorial/)
- [Official](https://leetcode.cn/problems/minimum-number-of-operations-to-move-all-balls-to-each-box/solutions/2000188/yi-dong-suo-you-qiu-dao-mei-ge-he-zi-suo-y50e/)

```text
You have n boxes.
You are given a binary string boxes of length n,
where boxes[i] is '0' if the ith box is empty, and '1' if it contains one ball.

In one operation, you can move one ball from a box to an adjacent box.
Box i is adjacent to box j if abs(i - j) == 1.
Note that after doing so, there may be more than one ball in some boxes.

Return an array answer of size n,
where answer[i] is the minimum number of operations needed to move all the balls to the ith box.

Each answer[i] is calculated considering the initial state of the boxes.

Example 1:
Input: boxes = "110"
Output: [1,1,3]
Explanation: The answer for each box is as follows:
1) First box: you will have to move one ball from the second box to the first box in one operation.
2) Second box: you will have to move one ball from the first box to the second box in one operation.
3) Third box: you will have to move one ball from the first box to the third box in two operations,
   and move one ball from the second box to the third box in one operation.

Example 2:
Input: boxes = "001011"
Output: [11,8,5,4,3,4]

Constraints:
n == boxes.length
1 <= n <= 2000
boxes[i] is either '0' or '1'.
```

<details><summary>Hint</summary>

```text
1. If you want to move a ball from box i to box j, you'll need abs(i-j) moves.
2. To move all balls to some box, you can move them one by one.
3. For each box i, iterate on each ball in a box j, and add abs(i-j) to answers[i].
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* minOperations(char* boxes, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    int boxesSize = strlen(boxes);
    pRetVal = (int*)calloc(boxesSize, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }
    (*returnSize) = boxesSize;

    int ballsToLeft = 0;
    int movesToLeft = 0;
    int ballsToRight = 0;
    int movesToRight = 0;
    int i, j;
    for (i = 0; i < boxesSize; i++) {
        // Left pass
        pRetVal[i] += movesToLeft;
        ballsToLeft += boxes[i] - '0';
        movesToLeft += ballsToLeft;

        // Right pass
        j = boxesSize - 1 - i;
        pRetVal[j] += movesToRight;
        ballsToRight += boxes[j] - '0';
        movesToRight += ballsToRight;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> minOperations(string boxes) {
        vector<int> retVal;

        int boxesSize = boxes.size();
        retVal.assign(boxesSize, 0);

        int ballsToLeft = 0;
        int movesToLeft = 0;
        int ballsToRight = 0;
        int movesToRight = 0;
        for (int i = 0; i < boxesSize; i++) {
            // Left pass
            retVal[i] += movesToLeft;
            ballsToLeft += boxes[i] - '0';
            movesToLeft += ballsToLeft;

            // Right pass
            int j = boxesSize - 1 - i;
            retVal[j] += movesToRight;
            ballsToRight += boxes[j] - '0';
            movesToRight += ballsToRight;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minOperations(self, boxes: str) -> List[int]:
        retVal = []

        boxesSize = len(boxes)
        retVal = [0] * boxesSize

        ballsToLeft = 0
        movesToLeft = 0
        ballsToRight = 0
        movesToRight = 0
        for i in range(boxesSize):
            # Left pass
            retVal[i] += movesToLeft
            ballsToLeft += int(boxes[i])
            movesToLeft += ballsToLeft

            # Right pass
            j = boxesSize - 1 - i
            retVal[j] += movesToRight
            ballsToRight += int(boxes[j])
            movesToRight += ballsToRight

        return retVal
```

</details>

## [1779. Find Nearest Point That Has the Same X or Y Coordinate](https://leetcode.com/problems/find-nearest-point-that-has-the-same-x-or-y-coordinate/)  1259

<details><summary>Description</summary>

```text
You are given two integers, x and y, which represent your current location on a Cartesian grid: (x, y).
You are also given an array points where each points[i] = [ai, bi] represents that a point exists at (ai, bi).
A point is valid if it shares the same x-coordinate or the same y-coordinate as your location.

Return the index (0-indexed) of the valid point with the smallest Manhattan distance from your current location.
If there are multiple, return the valid point with the smallest index. If there are no valid points, return -1.

The Manhattan distance between two points (x1, y1) and (x2, y2) is abs(x1 - x2) + abs(y1 - y2).


Example 1:
Input: x = 3, y = 4, points = [[1,2],[3,1],[2,4],[2,3],[4,4]]
Output: 2
Explanation: Of all the points, only [3,1], [2,4] and [4,4] are valid.
Of the valid points, [2,4] and [4,4] have the smallest Manhattan distance from your current location,
with a distance of 1. [2,4] has the smallest index, so return 2.

Example 2:
Input: x = 3, y = 4, points = [[3,4]]
Output: 0
Explanation: The answer is allowed to be on the same location as your current location.

Example 3:
Input: x = 3, y = 4, points = [[2,3]]
Output: -1
Explanation: There are no valid points.

Constraints:
1 <= points.length <= 10^4
points[i].length == 2
1 <= x, y, ai, bi <= 10^4
```

</details>

<details><summary>C</summary>

```c
int nearestValidPoint(int x, int y, int** points, int pointsSize, int* pointsColSize) {
    int retVal = -1;

    int distance;
    int minDistance = INT_MAX;
    int i;
    for (i=pointsSize-1; i>=0; --i) {
        if ((x != points[i][0]) && (y != points[i][1])) {
            continue;
        }
        else if ((x == points[i][0]) && (y == points[i][1])) {
            distance = 0;
        }
        else if (x == points[i][0]) {
            distance = abs(y - points[i][1]);
        }
        else if (y == points[i][1]) {
            distance = abs(x - points[i][0]);
        }

        if (distance <= minDistance) {
            minDistance = distance;
            retVal = i;
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
    int nearestValidPoint(int x, int y, vector<vector<int>>& points) {
        int retVal = -1;

        int distanceMin = INT_MAX;
        int distanceRow;
        int distanceCol;
        for (int i=(points.size()-1); i>=0; --i) {
            distanceRow = abs(x - points[i][0]);
            distanceCol = abs(y - points[i][1]);
            if ((distanceRow!=0) && (distanceCol!=0)) {
                continue;
            }
            else if (distanceMin >= max(distanceRow, distanceCol)) {
                distanceMin = max(distanceRow, distanceCol);
                retVal = i;
            }
        }

        return retVal;
    }
};
```

</details>

## [1798. Maximum Number of Consecutive Values You Can Make](https://leetcode.com/problems/maximum-number-of-consecutive-values-you-can-make/)  1931

- [Official](https://leetcode.cn/problems/maximum-number-of-consecutive-values-you-can-make/solutions/2090079/ni-neng-gou-zao-chu-lian-xu-zhi-de-zui-d-wci4/)

<details><summary>Description</summary>

```text
You are given an integer array coins of length n which represents the n coins that you own.
The value of the ith coin is coins[i].
You can make some value x if you can choose some of your n coins such that their values sum up to x.

Return the maximum number of consecutive integer values that you can make with your coins starting from and including 0.

Note that you may have multiple coins of the same value.

Example 1:
Input: coins = [1,3]
Output: 2
Explanation: You can make the following values:
- 0: take []
- 1: take [1]
You can make 2 consecutive integer values starting from 0.

Example 2:
Input: coins = [1,1,1,4]
Output: 8
Explanation: You can make the following values:
- 0: take []
- 1: take [1]
- 2: take [1,1]
- 3: take [1,1,1]
- 4: take [4]
- 5: take [4,1]
- 6: take [4,1,1]
- 7: take [4,1,1,1]
You can make 8 consecutive integer values starting from 0.

Example 3:
Input: nums = [1,4,10,3,1]
Output: 20

Constraints:
coins.length == n
1 <= n <= 4 * 10^4
1 <= coins[i] <= 4 * 10^4
```

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int getMaximumConsecutive(int* coins, int coinsSize) {
    int retVal = 1;

    qsort(coins, coinsSize, sizeof(int), compareInteger);

    int i;
    for (i = 0; i < coinsSize; ++i) {
        // Return the maximum number of consecutive integer values
        // that you can make with your coins starting from and including 0.
        if (coins[i] > retVal) {
            break;
        }
        retVal += coins[i];
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int getMaximumConsecutive(vector<int>& coins) {
        int retVal = 1;

        sort(coins.begin(), coins.end());
        for (auto iter : coins) {
            // Return the maximum number of consecutive integer values
            // that you can make with your coins starting from and including 0.
            if (iter > retVal) {
                break;
            }
            retVal += iter;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Rust</summary>

```rust
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
```

</details>

## [1861. Rotating the Box](https://leetcode.com/problems/rotating-the-box/)  1536

- [Official](https://leetcode.com/problems/rotating-the-box/editorial/)
- [Official](https://leetcode.cn/problems/rotating-the-box/solutions/779199/xuan-zhuan-he-zi-by-leetcode-solution-us55/)

<details><summary>Description</summary>

```text
You are given an m x n matrix of characters box representing a side-view of a box.
Each cell of the box is one of the following:
- A stone '#'
- A stationary obstacle '*'
- Empty '.'

The box is rotated 90 degrees clockwise, causing some of the stones to fall due to gravity.
Each stone falls down until it lands on an obstacle, another stone, or the bottom of the box.
Gravity does not affect the obstacles' positions,
and the inertia from the box's rotation does not affect the stones' horizontal positions.

It is guaranteed that each stone in box rests on an obstacle, another stone, or the bottom of the box.

Return an n x m matrix representing the box after the rotation described above.

Example 1:
Input: box = [["#",".","#"]]
Output: [["."],
         ["#"],
         ["#"]]

Example 2:
Input: box = [["#",".","*","."],
              ["#","#","*","."]]
Output: [["#","."],
         ["#","#"],
         ["*","*"],
         [".","."]]

Example 3:
Input: box = [["#","#","*",".","*","."],
              ["#","#","#","*",".","."],
              ["#","#","#",".","#","."]]
Output: [[".","#","#"],
         [".","#","#"],
         ["#","#","*"],
         ["#","*","."],
         ["#",".","*"],
         ["#",".","."]]

Constraints:
m == box.length
n == box[i].length
1 <= m, n <= 500
box[i][j] is either '#', '*', or '.'.
```

<details><summary>Hint</summary>

```text
1. Rotate the box using the relation rotatedBox[i][j] = box[m - 1 - j][i].
2. Start iterating from the bottom of the box
   and for each empty cell check if there is any stone above it with no obstacles between them.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char** rotateTheBox(char** box, int boxSize, int* boxColSize, int* returnSize, int** returnColumnSizes) {
    char** pRetVal = NULL;

    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    int i, j;

    (*returnColumnSizes) = (int*)malloc(boxColSize[0] * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal = (char**)malloc(boxColSize[0] * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }
    for (i = 0; i < boxColSize[0]; ++i) {
        pRetVal[i] = (char*)malloc(boxSize * sizeof(char));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            return pRetVal;
        }
    }
    for (i = 0; i < boxColSize[0]; ++i) {
        for (j = 0; j < boxSize; ++j) {
            pRetVal[i][j] = '.';
        }
        (*returnColumnSizes)[i] = boxSize;
    }
    (*returnSize) = boxColSize[0];

    // Apply gravity to let stones fall to the lowest possible empty cell in each column
    int lowestRowWithEmptyCell;
    for (i = 0; i < boxSize; i++) {
        lowestRowWithEmptyCell = boxColSize[0] - 1;

        // Process each cell in row 'i' in reversed order
        for (j = boxColSize[0] - 1; j >= 0; j--) {
            // Found a stone - let it fall to the lowest empty cell
            if (box[i][j] == '#') {
                // Place it in the correct position in the rotated grid
                pRetVal[lowestRowWithEmptyCell][boxSize - i - 1] = '#';
                // (Optional - already initialized to '.') pRetVal[j][boxSize - i - 1] = '.';
                lowestRowWithEmptyCell--;
            }

            // Found an obstacle - reset 'lowestRowWithEmptyCell' to the row directly above it
            if (box[i][j] == '*') {
                // Place the obstacle in the correct position in the rotated grid
                pRetVal[j][boxSize - i - 1] = '*';
                lowestRowWithEmptyCell = j - 1;
            }
        }
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& box) {
        vector<vector<char>> retVal;

        int boxSize = box.size();
        int boxColSize = box[0].size();
        retVal.resize(boxColSize, vector<char>(boxSize, '.'));

        // Apply gravity to let stones fall to the lowest possible empty cell in each column
        for (int i = 0; i < boxSize; i++) {
            int lowestRowWithEmptyCell = boxColSize - 1;

            // Process each cell in row 'i' in reversed order
            for (int j = boxColSize - 1; j >= 0; j--) {
                // Found a stone - let it fall to the lowest empty cell
                if (box[i][j] == '#') {
                    // Place it in the correct position in the rotated grid
                    retVal[lowestRowWithEmptyCell][boxSize - i - 1] = '#';
                    // (Optional - already initialized to '.') retVal[j][boxSize - i - 1] = '.';
                    lowestRowWithEmptyCell--;
                }

                // Found an obstacle - reset 'lowestRowWithEmptyCell' to the row directly above it
                if (box[i][j] == '*') {
                    // Place the obstacle in the correct position in the rotated grid
                    retVal[j][boxSize - i - 1] = '*';
                    lowestRowWithEmptyCell = j - 1;
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
    def rotateTheBox(self, box: List[List[str]]) -> List[List[str]]:
        retVal = []

        boxSize = len(box)
        boxColSize = len(box[0])
        retVal = [["." for _ in range(boxSize)] for _ in range(boxColSize)]

        # Apply gravity to let stones fall to the lowest possible empty cell in each column
        for i in range(boxSize):
            lowestRowWithEmptyCell = boxColSize - 1

            # Process each cell in row 'i' in reversed order
            for j in range(boxColSize - 1, -1, -1):
                # Found a stone - let it fall to the lowest empty cell
                if box[i][j] == "#":
                    # Place it in the correct position in the rotated grid
                    retVal[lowestRowWithEmptyCell][boxSize - i - 1] = "#"
                    lowestRowWithEmptyCell -= 1

                # Found an obstacle - reset 'lowestRowWithEmptyCell' to the row directly above it
                if box[i][j] == "*":
                    # Place the obstacle in the correct position in the rotated grid
                    retVal[j][boxSize - i - 1] = "*"
                    lowestRowWithEmptyCell = j - 1

        return retVal
```

</details>

## [1913. Maximum Product Difference Between Two Pairs](https://leetcode.com/problems/maximum-product-difference-between-two-pairs/)  1144

- [Official](https://leetcode.com/problems/maximum-product-difference-between-two-pairs/editorial/)
- [Official](https://leetcode.cn/problems/maximum-product-difference-between-two-pairs/solutions/846940/liang-ge-shu-dui-zhi-jian-de-zui-da-chen-1ksh/)

<details><summary>Description</summary>

```text
The product difference between two pairs (a, b) and (c, d) is defined as (a * b) - (c * d).
- For example, the product difference between (5, 6) and (2, 7) is (5 * 6) - (2 * 7) = 16.

Given an integer array nums, choose four distinct indices w, x, y, and z
such that the product difference between pairs (nums[w], nums[x]) and (nums[y], nums[z]) is maximized.

Return the maximum such product difference.

Example 1:
Input: nums = [5,6,2,7,4]
Output: 34
Explanation: We can choose indices 1 and 3 for the first pair (6, 7) and indices 2 and 4 for the second pair (2, 4).
The product difference is (6 * 7) - (2 * 4) = 34.

Example 2:
Input: nums = [4,2,5,9,7,4,8]
Output: 64
Explanation: We can choose indices 3 and 6 for the first pair (9, 8) and indices 1 and 5 for the second pair (2, 4).
The product difference is (9 * 8) - (2 * 4) = 64.

Constraints:
4 <= nums.length <= 10^4
1 <= nums[i] <= 10^4
```

<details><summary>Hint</summary>

```text
1. If you only had to find the maximum product of 2 numbers in an array, which 2 numbers should you choose?
2. We only need to worry about 4 numbers in the array.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int maxProductDifference(int* nums, int numsSize) {
    int retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);
    retVal = (nums[numsSize - 1] * nums[numsSize - 2]) - (nums[0] * nums[1]);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxProductDifference(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        sort(nums.begin(), nums.end());
        retVal = (nums[numsSize - 1] * nums[numsSize - 2]) - (nums[0] * nums[1]);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxProductDifference(self, nums: List[int]) -> int:
        retVal = 0

        nums.sort()
        retVal = (nums[-1] * nums[-2]) - (nums[0] * nums[1])

        return retVal
```

</details>

## [1980. Find Unique Binary String](https://leetcode.com/problems/find-unique-binary-string/)  1361

- [Official](https://leetcode.com/problems/find-unique-binary-string/editorial/)
- [Official](https://leetcode.cn/problems/find-unique-binary-string/solutions/951996/zhao-chu-bu-tong-de-er-jin-zhi-zi-fu-chu-0t10/)

<details><summary>Description</summary>

```text
Given an array of strings nums containing n unique binary strings each of length n,
return a binary string of length n that does not appear in nums.
If there are multiple answers, you may return any of them.

Example 1:
Input: nums = ["01","10"]
Output: "11"
Explanation: "11" does not appear in nums. "00" would also be correct.

Example 2:
Input: nums = ["00","01"]
Output: "11"
Explanation: "11" does not appear in nums. "10" would also be correct.

Example 3:
Input: nums = ["111","011","001"]
Output: "101"
Explanation: "101" does not appear in nums. "000", "010", "100", and "110" would also be correct.

Constraints:
n == nums.length
1 <= n <= 16
nums[i].length == n
nums[i] is either '0' or '1'.
All the strings of nums are unique.
```

<details><summary>Hint</summary>

```text
1. We can convert the given strings into base 10 integers.
2. Can we use recursion to generate all possible strings?
```

</details>

</details>

<details><summary>C</summary>

```c
char* findDifferentBinaryString(char** nums, int numsSize) {
    char* pRetVal = NULL;

    int returnSize = numsSize + 1;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));

    // https://en.wikipedia.org/wiki/Cantor%27s_diagonal_argument
    char c;
    int i;
    for (i = 0; i < numsSize; ++i) {
        c = nums[i][i];
        pRetVal[i] = ((c == '0') ? '1' : '0');
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define MODULO (int)(1e9 + 7)
   public:
    string findDifferentBinaryString(vector<string>& nums) {
        string retVal;

        vector<int> intNums;
        for (string num : nums) {
            intNums.emplace_back(stoi(num, 0, 2));
        }

        int numsSize = nums.size();
        int maxRange = 1 << numsSize;  // n == nums.length, 1 <= n <= 16.
        for (int i = 0; i < maxRange; ++i) {
            if (find(intNums.begin(), intNums.end(), i) == intNums.end()) {
                retVal = bitset<16>(i).to_string();
                retVal = retVal.substr(16 - numsSize);
                break;
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
    def findDifferentBinaryString(self, nums: List[str]) -> str:
        retVal = ""

        intNums = []
        for num in nums:
            intNum = int(num, 2)
            intNums.append(intNum)

        numsSize = len(nums)
        maxRange = 1 << numsSize
        for i in range(maxRange):
            if i in intNums:
                continue

            retVal = str((bin(i)[2:]))
            retVal = "0" * (numsSize - len(retVal)) + retVal
            break

        return retVal
```

</details>
