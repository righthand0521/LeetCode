# [Prefix Sum](https://en.wikipedia.org/wiki/Prefix_sum)

## [303. Range Sum Query - Immutable](https://leetcode.com/problems/range-sum-query-immutable/)

<details><summary>Description</summary>

```text
Given an integer array nums, handle multiple queries of the following type:

Calculate the sum of the elements of nums between indices left and right inclusive where left <= right.

Implement the NumArray class:
- NumArray(int[] nums)
    Initializes the object with the integer array nums.
- int sumRange(int left, int right)
    Returns the sum of the elements of nums between indices left and right inclusive
    (i.e. nums[left] + nums[left + 1] + ... + nums[right]).

Example 1:
Input
["NumArray", "sumRange", "sumRange", "sumRange"]
[[[-2, 0, 3, -5, 2, -1]], [0, 2], [2, 5], [0, 5]]
Output
[null, 1, -1, -3]
Explanation
NumArray numArray = new NumArray([-2, 0, 3, -5, 2, -1]);
numArray.sumRange(0, 2); // return (-2) + 0 + 3 = 1
numArray.sumRange(2, 5); // return 3 + (-5) + 2 + (-1) = -1
numArray.sumRange(0, 5); // return (-2) + 0 + 3 + (-5) + 2 + (-1) = -3

Constraints:
1 <= nums.length <= 10^4
-10^5 <= nums[i] <= 10^5
0 <= left <= right < nums.length
At most 10^4 calls will be made to sumRange.
```

</details>

<details><summary>C</summary>

```c
typedef struct {
    int* pNums;
} NumArray;

NumArray* numArrayCreate(int* nums, int numsSize) {
    NumArray* pCreate = (NumArray*)malloc(sizeof(NumArray));
    if (pCreate == NULL) {
        perror("malloc");
        return pCreate;
    }
    pCreate->pNums = NULL;

    pCreate->pNums = (int*)malloc(numsSize*sizeof(int));
    if (pCreate->pNums == NULL) {
        perror("malloc");
        free(pCreate);
        pCreate = NULL;
        return pCreate;
    }
    memset(pCreate->pNums, 0, (numsSize*sizeof(int)));
    memcpy(pCreate->pNums, nums, (numsSize*sizeof(int)));

    return pCreate;
}

int numArraySumRange(NumArray* obj, int left, int right) {
    int retVal = 0;

    int i;
    for (i=left; i<=right; ++i) {
        retVal += obj->pNums[i];
    }

    return retVal;
}

void numArrayFree(NumArray* obj) {
    if (obj == NULL) {
        return;
    }

    if (obj->pNums) {
        free(obj->pNums);
        obj->pNums = NULL;
    }
    free(obj);
    obj = NULL;
}

/**
 * Your NumArray struct will be instantiated and called as such:
 * NumArray* obj = numArrayCreate(nums, numsSize);
 * int param_1 = numArraySumRange(obj, left, right);
 * numArrayFree(obj);
 */
```

</details>

## [304. Range Sum Query 2D - Immutable](https://leetcode.com/problems/range-sum-query-2d-immutable/)

- [Official](https://leetcode.com/problems/range-sum-query-2d-immutable/solutions/127813/range-sum-query-2d-immutable/)
- [Official](https://leetcode.cn/problems/range-sum-query-2d-immutable/solutions/627420/er-wei-qu-yu-he-jian-suo-ju-zhen-bu-ke-b-2z5n/)

<details><summary>Description</summary>

```text
Given a 2D matrix matrix, handle multiple queries of the following type:
- Calculate the sum of the elements of matrix inside the rectangle defined by its upper left corner (row1, col1)
and lower right corner (row2, col2).

Implement the NumMatrix class:
- NumMatrix(int[][] matrix)
  Initializes the object with the integer matrix matrix.
- int sumRegion(int row1, int col1, int row2, int col2)
  Returns the sum of the elements of matrix inside the rectangle defined by its upper left corner (row1, col1)
  and lower right corner (row2, col2).

You must design an algorithm where sumRegion works on O(1) time complexity.


Example 1:
+-------------------+
| 3 | 0 | 1 | 4 | 2 |
| 5 | 6 | 3 | 2 | 1 |
| 1 | 2 | 0 | 1 | 5 |
| 4 | 1 | 0 | 1 | 7 |
| 1 | 0 | 3 | 0 | 5 |
+-------------------+

Input
["NumMatrix", "sumRegion", "sumRegion", "sumRegion"]
[
    [[[3, 0, 1, 4, 2],[5, 6, 3, 2, 1],[1, 2, 0, 1, 5],[4, 1, 0, 1, 7],[1, 0, 3, 0, 5]]],
    [2, 1, 4, 3],
    [1, 1, 2, 2],
    [1, 2, 2, 4]
]
Output
[null, 8, 11, 12]
Explanation
NumMatrix numMatrix = new NumMatrix([[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]]);
numMatrix.sumRegion(2, 1, 4, 3); // return 8 (i.e sum of the red rectangle)
numMatrix.sumRegion(1, 1, 2, 2); // return 11 (i.e sum of the green rectangle)
numMatrix.sumRegion(1, 2, 2, 4); // return 12 (i.e sum of the blue rectangle)

Constraints:
m == matrix.length
n == matrix[i].length
1 <= m, n <= 200
-10^4 <= matrix[i][j] <= 10^4
0 <= row1 <= row2 < m
0 <= col1 <= col2 < n
At most 10^4 calls will be made to sumRegion.
```

</details>

<details><summary>C</summary>

```c
typedef struct {
    int** sums;
    int sumsSize;
} NumMatrix;
NumMatrix* numMatrixCreate(int** matrix, int matrixSize, int* matrixColSize) {
    NumMatrix* pCreate = (NumMatrix*)malloc(sizeof(NumMatrix));
    if (pCreate == NULL) {
        perror("malloc");
        return pCreate;
    }

    pCreate->sumsSize = matrixSize + 1;
    pCreate->sums = (int**)malloc((matrixSize + 1) * sizeof(int*));
    if (pCreate->sums == NULL) {
        perror("malloc");
        free(pCreate);
        pCreate = NULL;
        return pCreate;
    }

    int n = matrixSize ? matrixColSize[0] : 0;
    int i, j;
    for (i = 0; i <= matrixSize; i++) {
        pCreate->sums[i] = (int*)malloc((n + 1) * sizeof(int));
        if (pCreate->sums[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pCreate->sums[j]);
                pCreate->sums[j] = NULL;
            }
            free(pCreate->sums);
            pCreate->sums = NULL;
            free(pCreate);
            pCreate = NULL;
            return pCreate;
        }
        memset(pCreate->sums[i], 0, ((n + 1) * sizeof(int)));
    }

    for (i = 0; i < matrixSize; ++i) {
        for (j = 0; j < matrixColSize[i]; ++j) {
            pCreate->sums[i + 1][j + 1] =
                pCreate->sums[i][j + 1] + pCreate->sums[i + 1][j] - pCreate->sums[i][j] + matrix[i][j];
        }
    }

    return pCreate;
}
int numMatrixSumRegion(NumMatrix* obj, int row1, int col1, int row2, int col2) {
    int retVal = 0;

    if (obj == NULL) {
        return retVal;
    }
    retVal =
        obj->sums[row2 + 1][col2 + 1] - obj->sums[row1][col2 + 1] - obj->sums[row2 + 1][col1] + obj->sums[row1][col1];

    return retVal;
}
void numMatrixFree(NumMatrix* obj) {
    if (obj == NULL) {
        return;
    }

    int i;
    for (i = 0; i < obj->sumsSize; ++i) {
        free(obj->sums[i]);
        obj->sums[i] = NULL;
    }
    free(obj->sums);
    obj->sums = NULL;
    free(obj);
    obj = NULL;
}
/**
 * Your NumMatrix struct will be instantiated and called as such:
 * NumMatrix* obj = numMatrixCreate(matrix, matrixSize, matrixColSize);
 * int param_1 = numMatrixSumRegion(obj, row1, col1, row2, col2);

 * numMatrixFree(obj);
*/
```

</details>

## [724. Find Pivot Index](https://leetcode.com/problems/find-pivot-index/)

- [Official](https://leetcode.com/problems/find-pivot-index/editorial/)
- [Official](https://leetcode.cn/problems/find-pivot-index/solutions/579264/xun-zhao-shu-zu-de-zhong-xin-suo-yin-by-gzjle/)

<details><summary>Description</summary>

```text
Given an array of integers nums, calculate the pivot index of this array.

The pivot index is the index where the sum of all the numbers strictly to the left of the index
is equal to the sum of all the numbers strictly to the index's right.

If the index is on the left edge of the array, then the left sum is 0 because there are no elements to the left.
This also applies to the right edge of the array.

Return the leftmost pivot index. If no such index exists, return -1.

Example 1:
Input: nums = [1,7,3,6,5,6]
Output: 3
Explanation:
The pivot index is 3.
Left sum = nums[0] + nums[1] + nums[2] = 1 + 7 + 3 = 11
Right sum = nums[4] + nums[5] = 5 + 6 = 11

Example 2:
Input: nums = [1,2,3]
Output: -1
Explanation:
There is no index that satisfies the conditions in the problem statement.

Example 3:
Input: nums = [2,1,-1]
Output: 0
Explanation:
The pivot index is 0.
Left sum = 0 (no elements to the left of index 0)
Right sum = nums[1] + nums[2] = 1 + -1 = 0

Constraints:
1 <= nums.length <= 10^4
-1000 <= nums[i] <= 1000

Note: This question is the same as 1991: https://leetcode.com/problems/find-the-middle-index-in-array/
```

<details><summary>Hint</summary>

```text
1. Create an array sumLeft where sumLeft[i] is the sum of all the numbers to the left of index i.
2. Create an array sumRight where sumRight[i] is the sum of all the numbers to the right of index i.
3. For each index i, check if sumLeft[i] equals sumRight[i] return i. If no i found, return -1.
```

</details>

</details>

<details><summary>C</summary>

```c
int pivotIndex(int* nums, int numsSize) {
    int retVal = -1;

    int i;

    int sumLeft[numsSize];
    sumLeft[0] = nums[0];
    for (i = 1; i < numsSize; ++i) {
        sumLeft[i] = sumLeft[i - 1] + nums[i];
    }

    int sumRight[numsSize];
    sumRight[numsSize - 1] = nums[numsSize - 1];
    for (i = numsSize - 2; i >= 0; --i) {
        sumRight[i] = sumRight[i + 1] + nums[i];
    }

    for (i = 0; i < numsSize; ++i) {
        if (sumLeft[i] == sumRight[i]) {
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
    int pivotIndex(vector<int>& nums) {
        int retVal = -1;

        int numsSize = nums.size();

        vector<int> sumLeft(numsSize, 0);
        sumLeft[0] = nums[0];
        for (int i = 1; i < numsSize; ++i) {
            sumLeft[i] = sumLeft[i - 1] + nums[i];
        }

        vector<int> sumRight(numsSize, 0);
        sumRight[numsSize - 1] = nums[numsSize - 1];
        for (int i = numsSize - 2; i >= 0; --i) {
            sumRight[i] = sumRight[i + 1] + nums[i];
        }

        for (int i = 0; i < numsSize; ++i) {
            if (sumLeft[i] == sumRight[i]) {
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
    def pivotIndex(self, nums: List[int]) -> int:
        retVal = -1

        numsSize = len(nums)

        sumLeft = [0] * numsSize
        sumLeft[0] = nums[0]
        for i in range(1, numsSize):
            sumLeft[i] = sumLeft[i - 1] + nums[i]

        sumRight = [0] * numsSize
        sumRight[numsSize - 1] = nums[numsSize - 1]
        for i in range(numsSize - 2, -1, -1):
            sumRight[i] = sumRight[i + 1] + nums[i]

        for i in range(numsSize):
            if sumLeft[i] == sumRight[i]:
                retVal = i
                break

        return retVal
```

</details>

## [974. Subarray Sums Divisible by K](https://leetcode.com/problems/subarray-sums-divisible-by-k/)  1675

- [Official](https://leetcode.com/problems/subarray-sums-divisible-by-k/editorial/)
- [Official](https://leetcode.cn/problems/subarray-sums-divisible-by-k/solutions/187947/he-ke-bei-k-zheng-chu-de-zi-shu-zu-by-leetcode-sol/)

<details><summary>Description</summary>

```text
Given an integer array nums and an integer k, return the number of non-empty subarrays that have a sum divisible by k.

A subarray is a contiguous part of an array.

Example 1:
Input: nums = [4,5,0,-2,-3,1], k = 5
Output: 7
Explanation: There are 7 subarrays with a sum divisible by k = 5:
[4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]

Example 2:
Input: nums = [5], k = 9
Output: 0

Constraints:
1 <= nums.length <= 3 * 10^4
-10^4 <= nums[i] <= 10^4
2 <= k <= 10^4
```

</details>

<details><summary>C</summary>

```c
int subarraysDivByK(int* nums, int numsSize, int k) {
    int retVal = 0;

    int modRecord[k];
    memset(modRecord, 0, sizeof(modRecord));
    modRecord[0] = 1;

    int prefixSumMod = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        prefixSumMod = (prefixSumMod + nums[i] % k + k) % k;
        retVal += modRecord[prefixSumMod];
        modRecord[prefixSumMod]++;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int subarraysDivByK(vector<int>& nums, int k) {
        int retVal = 0;

        vector<int> modRecord(k, 0);
        modRecord[0] = 1;

        int prefixSumMod = 0;
        for (int num : nums) {
            prefixSumMod = (prefixSumMod + num % k + k) % k;
            retVal += modRecord[prefixSumMod];
            modRecord[prefixSumMod]++;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def subarraysDivByK(self, nums: List[int], k: int) -> int:
        retVal = 0

        modRecord = [0] * k
        modRecord[0] = 1

        prefixSumMod = 0
        for num in nums:
            prefixSumMod = (prefixSumMod + num % k + k) % k
            retVal += modRecord[prefixSumMod]
            modRecord[prefixSumMod] += 1

        return retVal
```

</details>

## [1310. XOR Queries of a Subarray](https://leetcode.com/problems/xor-queries-of-a-subarray/)  1459

- [Official](https://leetcode.com/problems/xor-queries-of-a-subarray/editorial/)
- [Official](https://leetcode.cn/problems/xor-queries-of-a-subarray/solutions/101717/zi-shu-zu-yi-huo-cha-xun-by-leetcode-solution/)

<details><summary>Description</summary>

```text
You are given an array arr of positive integers.
You are also given the array queries where queries[i] = [lefti, righti].

For each query i compute the XOR of elements from lefti to righti
(that is, arr[lefti] XOR arr[lefti + 1] XOR ... XOR arr[righti] ).

Return an array answer where answer[i] is the answer to the ith query.

Example 1:
Input: arr = [1,3,4,8], queries = [[0,1],[1,2],[0,3],[3,3]]
Output: [2,7,14,8]
Explanation:
The binary representation of the elements in the array are:
1 = 0001
3 = 0011
4 = 0100
8 = 1000
The XOR values for queries are:
[0,1] = 1 xor 3 = 2
[1,2] = 3 xor 4 = 7
[0,3] = 1 xor 3 xor 4 xor 8 = 14
[3,3] = 8

Example 2:
Input: arr = [4,8,2,10], queries = [[2,3],[1,3],[0,0],[0,3]]
Output: [8,0,4,4]

Constraints:
1 <= arr.length, queries.length <= 3 * 10^4
1 <= arr[i] <= 10^9
queries[i].length == 2
0 <= lefti <= righti < arr.length
```

<details><summary>Hint</summary>

```text
1. What is the result of x ^ y ^ x ?
2. Compute the prefix sum for XOR.
3. Process the queries with the prefix sum values.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* xorQueries(int* arr, int arrSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    int i;

    int prefixSum[arrSize + 1];
    memset(prefixSum, 0, sizeof(prefixSum));
    for (i = 0; i < arrSize; ++i) {
        prefixSum[i + 1] = prefixSum[i] ^ arr[i];
    }

    pRetVal = (int*)malloc(queriesSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (queriesSize * sizeof(int)));
    for (i = 0; i < queriesSize; ++i) {
        pRetVal[i] = prefixSum[queries[i][1] + 1] ^ prefixSum[queries[i][0]];
        (*returnSize) += 1;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
        vector<int> retVal;

        int arrSize = arr.size();
        int prefixSumSize = arrSize + 1;
        vector<int> prefixSum(prefixSumSize, 0);
        for (int i = 0; i < arrSize; ++i) {
            prefixSum[i + 1] = prefixSum[i] ^ arr[i];
        }

        int queriesSize = queries.size();
        for (int i = 0; i < queriesSize; ++i) {
            retVal.emplace_back(prefixSum[queries[i][1] + 1] ^ prefixSum[queries[i][0]]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def xorQueries(self, arr: List[int], queries: List[List[int]]) -> List[int]:
        retVal = []

        prefixSum = [0]
        for key, value in enumerate(arr):
            prefixSum.append(prefixSum[key] ^ arr[key])

        for query in queries:
            retVal.append(prefixSum[query[1]+1] ^ prefixSum[query[0]])

        return retVal
```

</details>

## [1371. Find the Longest Substring Containing Vowels in Even Counts](https://leetcode.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/)  2040

- [Official](https://leetcode.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/editorial/)
- [Official](https://leetcode.cn/problems/find-the-longest-substring-containing-vowels-in-even-counts/solutions/238567/mei-ge-yuan-yin-bao-han-ou-shu-ci-de-zui-chang-z-2/)

<details><summary>Description</summary>

```text
Given the string s, return the size of the longest substring containing each vowel an even number of times.
That is, 'a', 'e', 'i', 'o', and 'u' must appear an even number of times.

Example 1:
Input: s = "eleetminicoworoep"
Output: 13
Explanation: The longest substring is "leetminicowor"
which contains two each of the vowels: e, i and o and zero of the vowels: a and u.

Example 2:
Input: s = "leetcodeisgreat"
Output: 5
Explanation: The longest substring is "leetc" which contains two e's.

Example 3:
Input: s = "bcbcbc"
Output: 6
Explanation: In this case,
the given string "bcbcbc" is the longest because all vowels: a, e, i, o and u appear zero times.

Constraints:
1 <= s.length <= 5 x 10^5
s contains only lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Represent the counts (odd or even) of vowels with a bitmask.
2. Precompute the prefix xor for the bitmask of vowels and then get the longest valid substring.
```

</details>

</details>

<details><summary>C</summary>

```c
int findTheLongestSubstring(char* s) {
    int retVal = 0;

    int characterMap[26];  // s contains only lowercase English letters.
    memset(characterMap, 0, sizeof(characterMap));
    characterMap['a' - 'a'] = 1;
    characterMap['e' - 'a'] = 2;
    characterMap['i' - 'a'] = 4;
    characterMap['o' - 'a'] = 8;
    characterMap['u' - 'a'] = 16;
    int mp[32];  // 1 + 2 + 4 + 8 + 16 = 31 < 32
    memset(mp, -1, sizeof(mp));

    int sSize = strlen(s);
    int prefixXOR = 0;
    int i;
    for (i = 0; i < sSize; ++i) {
        prefixXOR ^= characterMap[s[i] - 'a'];
        if ((mp[prefixXOR] == -1) && (prefixXOR != 0)) {
            mp[prefixXOR] = i;
        }
        retVal = fmax(retVal, i - mp[prefixXOR]);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int findTheLongestSubstring(string s) {
        int retVal = 0;

        vector<int> characterMap(26, 0);  // s contains only lowercase English letters.
        characterMap['a' - 'a'] = 1;
        characterMap['e' - 'a'] = 2;
        characterMap['i' - 'a'] = 4;
        characterMap['o' - 'a'] = 8;
        characterMap['u' - 'a'] = 16;
        vector<int> mp(32, -1);  // 1 + 2 + 4 + 8 + 16 = 31 < 32

        int sSize = s.size();
        int prefixXOR = 0;
        for (int i = 0; i < sSize; ++i) {
            prefixXOR ^= characterMap[s[i] - 'a'];
            if ((mp[prefixXOR] == -1) && (prefixXOR != 0)) {
                mp[prefixXOR] = i;
            }
            retVal = max(retVal, i - mp[prefixXOR]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def findTheLongestSubstring(self, s: str) -> int:
        retVal = 0

        characterMap = [0] * 26  # s contains only lowercase English letters.
        characterMap[ord("a") - ord("a")] = 1
        characterMap[ord("e") - ord("a")] = 2
        characterMap[ord("i") - ord("a")] = 4
        characterMap[ord("o") - ord("a")] = 8
        characterMap[ord("u") - ord("a")] = 16
        mp = [-1] * 32  # 1+2+4+8+16=31 < 32

        sSize = len(s)
        prefixXOR = 0
        for i in range(sSize):
            prefixXOR ^= characterMap[ord(s[i]) - ord("a")]
            if (mp[prefixXOR] == -1) and (prefixXOR != 0):
                mp[prefixXOR] = i
            retVal = max(retVal, i - mp[prefixXOR])

        return retVal
```

</details>

## [1480. Running Sum of 1d Array](https://leetcode.com/problems/running-sum-of-1d-array/)  1104

- [Official](https://leetcode.com/problems/running-sum-of-1d-array/editorial/)
- [Official](https://leetcode.cn/problems/running-sum-of-1d-array/solutions/962723/yi-wei-shu-zu-de-dong-tai-he-by-leetcode-flkm/)

<details><summary>Description</summary>

```text
Given an array nums. We define a running sum of an array as runningSum[i] = sum(nums[0]…nums[i]).

Return the running sum of nums.

Example 1:
Input: nums = [1,2,3,4]
Output: [1,3,6,10]
Explanation: Running sum is obtained as follows: [1, 1+2, 1+2+3, 1+2+3+4].

Example 2:
Input: nums = [1,1,1,1,1]
Output: [1,2,3,4,5]
Explanation: Running sum is obtained as follows: [1, 1+1, 1+1+1, 1+1+1+1, 1+1+1+1+1].

Example 3:
Input: nums = [3,1,2,10,1]
Output: [3,4,6,16,17]

Constraints:
1 <= nums.length <= 1000
-10^6 <= nums[i] <= 10^6
```

<details><summary>Hint</summary>

```text
1. Think about how we can calculate the i-th number in the running sum from the (i-1)-th number.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* runningSum(int* nums, int numsSize, int* returnSize) {
    int* pRetVal = NULL;

    *returnSize = numsSize;
    pRetVal = (int*)malloc(*returnSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int i = 0;
    pRetVal[i] = nums[i];
    for (i = 1; i < numsSize; ++i) {
        pRetVal[i] = pRetVal[i - 1] + nums[i];
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> runningSum(vector<int>& nums) {
        vector<int> retval;

        retval.push_back(nums[0]);
        for (long unsigned int i = 1; i < nums.size(); ++i) {
            retval.push_back(retval[i - 1] + nums[i]);
        }

        return retval;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def runningSum(self, nums: List[int]) -> List[int]:
        retVal = []

        retVal.append(nums[0])
        for i in range(1, len(nums)):
            retVal.append(retVal[i-1] + nums[i])

        return retVal
```

</details>

## [1590. Make Sum Divisible by P](https://leetcode.com/problems/make-sum-divisible-by-p/)  2038

- [Official](https://leetcode.com/problems/make-sum-divisible-by-p/editorial/)
- [Official](https://leetcode.cn/problems/make-sum-divisible-by-p/solutions/2157277/shi-shu-zu-he-neng-bei-p-zheng-chu-by-le-dob9/)

<details><summary>Description</summary>

```text
Given an array of positive integers nums, remove the smallest subarray (possibly empty)
such that the sum of the remaining elements is divisible by p.
It is not allowed to remove the whole array.

Return the length of the smallest subarray that you need to remove, or -1 if it's impossible.

A subarray is defined as a contiguous block of elements in the array.

Example 1:
Input: nums = [3,1,4,2], p = 6
Output: 1
Explanation: The sum of the elements in nums is 10, which is not divisible by 6.
We can remove the subarray [4], and the sum of the remaining elements is 6, which is divisible by 6.

Example 2:
Input: nums = [6,3,5,2], p = 9
Output: 2
Explanation: We cannot remove a single element to get a sum divisible by 9.
The best way is to remove the subarray [5,2], leaving us with [6,3] with sum 9.

Example 3:
Input: nums = [1,2,3], p = 3
Output: 0
Explanation: Here the sum is 6. which is already divisible by 3. Thus we do not need to remove anything.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
1 <= p <= 10^9
```

<details><summary>Hint</summary>

```text
1. Use prefix sums to calculate the subarray sums.
2. Suppose you know the remainder for the sum of the entire array. How does removing a subarray affect that remainder?
   What remainder does the subarray need to have in order to make the rest of the array sum up to be divisible by k?
3. Use a map to keep track of the rightmost index for every prefix sum % p.
```

</details>

</details>

<details><summary>C</summary>

```c
struct hashTable {
    int key;
    int value;
    UT_hash_handle hh;
};
void freeAll(struct hashTable *pFree) {
    struct hashTable *current;
    struct hashTable *tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int minSubarray(int *nums, int numsSize, int p) {
    int retVal = 0;

    // Step 1: Calculate total sum and target remainder
    int totalSum = 0;
    for (int i = 0; i < numsSize; ++i) {
        totalSum = (totalSum + nums[i]) % p;
    }
    int target = totalSum % p;
    if (target == 0) {  // The array is already divisible by p
        return retVal;
    }

    // Step 2: Use a hash map to track prefix sum mod p
    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp = NULL;
    pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
    if (pTemp == NULL) {
        perror("malloc");
        freeAll(pHashTable);
        return retVal;
    }
    pTemp->key = 0;
    pTemp->value = -1;
    HASH_ADD_INT(pHashTable, key, pTemp);

    // Step 3: Iterate over the array
    retVal = numsSize;
    int needed;
    int currentSum = 0;
    for (int i = 0; i < numsSize; ++i) {
        currentSum = (currentSum + nums[i]) % p;

        needed = (currentSum - target + p) % p;  // Calculate what we need to remove
        // If we have seen the needed remainder, we can consider this subarray
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &needed, pTemp);
        if (pTemp != NULL) {
            retVal = fmin(retVal, i - pTemp->value);
        }

        // Store the current remainder and index
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &currentSum, pTemp);
        if (pTemp == NULL) {
            pTemp = NULL;
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                return retVal;
            }
            pTemp->key = currentSum;
            pTemp->value = i;
            HASH_ADD_INT(pHashTable, key, pTemp);
        } else {
            pTemp->value = i;
        }
    }

    if (retVal == numsSize) {
        retVal = -1;
    }

    //
    freeAll(pHashTable);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minSubarray(vector<int>& nums, int p) {
        int retVal = 0;

        int numsSize = nums.size();

        // Step 1: Calculate total sum and target remainder
        int totalSum = 0;
        for (int num : nums) {
            totalSum = (totalSum + num) % p;
        }
        int target = totalSum % p;
        if (target == 0) {  // The array is already divisible by p
            return retVal;
        }

        // Step 2: Use a hash map to track prefix sum mod p
        unordered_map<int, int> modMap;
        modMap[0] = -1;  // To handle the case where the whole prefix is the answer

        // Step 3: Iterate over the array
        retVal = numsSize;
        int currentSum = 0;
        for (int i = 0; i < numsSize; ++i) {
            currentSum = (currentSum + nums[i]) % p;

            int needed = (currentSum - target + p) % p;  // Calculate what we need to remove
            // If we have seen the needed remainder, we can consider this subarray
            if (modMap.find(needed) != modMap.end()) {
                retVal = min(retVal, i - modMap[needed]);
            }

            modMap[currentSum] = i;  // Store the current remainder and index
        }

        if (retVal == numsSize) {
            retVal = -1;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minSubarray(self, nums: List[int], p: int) -> int:
        retVal = 0

        numsSize = len(nums)

        # Step 1: Calculate total sum and target remainder
        totalSum = 0
        for num in nums:
            totalSum = (totalSum + num) % p
        target = totalSum % p
        if target == 0:
            return retVal  # The array is already divisible by p

        # Step 2: Use a dict to track prefix sum mod p
        modMap = {0: -1}    # To handle the case where the whole prefix is the answer

        # Step 3: Iterate over the array
        retVal = numsSize
        currentSum = 0
        for i in range(numsSize):
            currentSum = (currentSum + nums[i]) % p

            needed = (currentSum - target + p) % p  # Calculate what we need to remove
            # If we have seen the needed remainder, we can consider this subarray
            if needed in modMap:
                retVal = min(retVal, i - modMap[needed])

            modMap[currentSum] = i  # Store the current remainder and index

        if retVal == numsSize:
            retVal = -1

        return retVal
```

</details>

## [1685. Sum of Absolute Differences in a Sorted Array](https://leetcode.com/problems/sum-of-absolute-differences-in-a-sorted-array/)  1495

- [Official](https://leetcode.com/problems/sum-of-absolute-differences-in-a-sorted-array/editorial/)

<details><summary>Description</summary>

```text
You are given an integer array nums sorted in non-decreasing order.

Build and return an integer array result with the same length as nums such that result[i] is equal to
the summation of absolute differences between nums[i] and all the other elements in the array.

In other words, result[i] is equal to sum(|nums[i]-nums[j]|) where 0 <= j < nums.length and j != i (0-indexed).

Example 1:
Input: nums = [2,3,5]
Output: [4,3,5]
Explanation: Assuming the arrays are 0-indexed, then
result[0] = |2-2| + |2-3| + |2-5| = 0 + 1 + 3 = 4,
result[1] = |3-2| + |3-3| + |3-5| = 1 + 0 + 2 = 3,
result[2] = |5-2| + |5-3| + |5-5| = 3 + 2 + 0 = 5.

Example 2:
Input: nums = [1,4,6,8,10]
Output: [24,15,13,15,21]

Constraints:
2 <= nums.length <= 10^5
1 <= nums[i] <= nums[i + 1] <= 10^4
```

<details><summary>Hint</summary>

```text
1. Absolute difference is the same as max(a, b) - min(a, b).
   How can you use this fact with the fact that the array is sorted?
2. For nums[i], the answer is (nums[i] - nums[0]) + (nums[i] - nums[1]) + ... + (nums[i] - nums[i-1])
   + (nums[i+1] - nums[i]) + (nums[i+2] - nums[i]) + ... + (nums[n-1] - nums[i]).
3. It can be simplified to (nums[i] * i - (nums[0] + nums[1] + ... + nums[i-1]))
   + ((nums[i+1] + nums[i+2] + ... + nums[n-1]) - nums[i] * (n-i-1)).
   One can build prefix and suffix sums to compute this quickly.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *getSumAbsoluteDifferences(int *nums, int numsSize, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;
    int i;

    pRetVal = (int *)malloc(numsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (numsSize * sizeof(int)));

    int prefixSum[numsSize];
    memset(prefixSum, 0, sizeof(prefixSum));
    prefixSum[0] = nums[0];
    for (i = 1; i < numsSize; ++i) {
        prefixSum[i] = prefixSum[i - 1] + nums[i];
    }

    int left, right;
    for (i = 0; i < numsSize; ++i) {
        left = (nums[i] * i) - (prefixSum[i] - nums[i]);
        right = (prefixSum[numsSize - 1] - prefixSum[i]) - (nums[i] * (numsSize - 1 - i));
        pRetVal[(*returnSize)++] = left + right;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> getSumAbsoluteDifferences(vector<int>& nums) {
        vector<int> retVal;

        int numsSize = nums.size();

        vector<int> prefixSum;
        prefixSum.emplace_back(nums[0]);
        for (int i = 1; i < numsSize; ++i) {
            prefixSum.emplace_back(prefixSum[i - 1] + nums[i]);
        }

        for (int i = 0; i < numsSize; ++i) {
            int left = (nums[i] * i) - (prefixSum[i] - nums[i]);
            int right = (prefixSum[numsSize - 1] - prefixSum[i]) - (nums[i] * (numsSize - 1 - i));
            retVal.emplace_back(left + right);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def getSumAbsoluteDifferences(self, nums: List[int]) -> List[int]:
        retVal = []

        numsSize = len(nums)

        prefixSum = [nums[0]]
        for i in range(1, numsSize):
            prefixSum.append(prefixSum[-1] + nums[i])

        for i in range(numsSize):
            left = (nums[i] * i) - (prefixSum[i] - nums[i])
            right = (prefixSum[-1] - prefixSum[i]) - (nums[i] * (numsSize - 1 - i))
            retVal.append(left + right)

        return retVal
```

</details>

## [1732. Find the Highest Altitude](https://leetcode.com/problems/find-the-highest-altitude/)  1256

- [Official](https://leetcode.com/problems/find-the-highest-altitude/editorial/)
- [Official](https://leetcode.cn/problems/find-the-highest-altitude/solutions/1977801/zhao-dao-zui-gao-hai-ba-by-leetcode-solu-l01c/)

<details><summary>Description</summary>

```text
There is a biker going on a road trip.
The road trip consists of n + 1 points at different altitudes.
The biker starts his trip on point 0 with altitude equal 0.

You are given an integer array gain of length n
where gain[i] is the net gain in altitude between points i​​​​​​ and i + 1 for all (0 <= i < n).
Return the highest altitude of a point.

Example 1:
Input: gain = [-5,1,5,0,-7]
Output: 1
Explanation: The altitudes are [0,-5,-4,1,1,-6]. The highest is 1.

Example 2:
Input: gain = [-4,-3,-2,-1,4,3,2]
Output: 0
Explanation: The altitudes are [0,-4,-7,-9,-10,-6,-3,-1]. The highest is 0.

Constraints:
n == gain.length
1 <= n <= 100
-100 <= gain[i] <= 100
```

<details><summary>Hint</summary>

```text
1. Let's note that the altitude of an element is the sum of gains of all the elements behind it
2. Getting the altitudes can be done by getting the prefix sum array of the given array
```

</details>

</details>

<details><summary>C</summary>

```c
int largestAltitude(int* gain, int gainSize) {
    int retVal = 0;

    int prefixSum = retVal;
    int i;
    for (i = 0; i < gainSize; ++i) {
        prefixSum += gain[i];
        retVal = fmax(retVal, prefixSum);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int largestAltitude(vector<int>& gain) {
        int retVal = 0;

        int prefixSum = retVal;
        for (auto iterator : gain) {
            prefixSum += iterator;
            retVal = max(retVal, prefixSum);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def largestAltitude(self, gain: List[int]) -> int:
        retVal = 0

        prefixSum = retVal
        for i in gain:
            prefixSum += i
            retVal = max(retVal, prefixSum)

        return retVal
```

</details>

## [1894. Find the Student that Will Replace the Chalk](https://leetcode.com/problems/find-the-student-that-will-replace-the-chalk/)  1355

- [Official](https://leetcode.com/problems/find-the-student-that-will-replace-the-chalk/editorial/)
- [Official](https://leetcode.cn/problems/find-the-student-that-will-replace-the-chalk/solutions/825464/zhao-dao-xu-yao-bu-chong-fen-bi-de-xue-s-qrn1/)

<details><summary>Description</summary>

```text
There are n students in a class numbered from 0 to n - 1.
The teacher will give each student a problem starting with the student number 0, then the student number 1,
and so on until the teacher reaches the student number n - 1.
After that, the teacher will restart the process, starting with the student number 0 again.

You are given a 0-indexed integer array chalk and an integer k. There are initially k pieces of chalk.
When the student number i is given a problem to solve, they will use chalk[i] pieces of chalk to solve that problem.
However, if the current number of chalk pieces is strictly less than chalk[i],
then the student number i will be asked to replace the chalk.

Return the index of the student that will replace the chalk pieces.

Example 1:
Input: chalk = [5,1,5], k = 22
Output: 0
Explanation: The students go in turns as follows:
- Student number 0 uses 5 chalk, so k = 17.
- Student number 1 uses 1 chalk, so k = 16.
- Student number 2 uses 5 chalk, so k = 11.
- Student number 0 uses 5 chalk, so k = 6.
- Student number 1 uses 1 chalk, so k = 5.
- Student number 2 uses 5 chalk, so k = 0.
Student number 0 does not have enough chalk, so they will have to replace it.

Example 2:
Input: chalk = [3,4,1,2], k = 25
Output: 1
Explanation: The students go in turns as follows:
- Student number 0 uses 3 chalk so k = 22.
- Student number 1 uses 4 chalk so k = 18.
- Student number 2 uses 1 chalk so k = 17.
- Student number 3 uses 2 chalk so k = 15.
- Student number 0 uses 3 chalk so k = 12.
- Student number 1 uses 4 chalk so k = 8.
- Student number 2 uses 1 chalk so k = 7.
- Student number 3 uses 2 chalk so k = 5.
- Student number 0 uses 3 chalk so k = 2.
Student number 1 does not have enough chalk, so they will have to replace it.

Constraints:
chalk.length == n
1 <= n <= 10^5
1 <= chalk[i] <= 10^5
1 <= k <= 10^9
```

<details><summary>Hint</summary>

```text
1. Subtract the sum of chalk from k until k is less than the sum of chalk.
2. Now iterate over the array. If chalk[i] is less than k, this is the answer.
   Otherwise, subtract chalk[i] from k and continue.
```

</details>

</details>

<details><summary>C</summary>

```c
int chalkReplacer(int* chalk, int chalkSize, int k) {
    int retVal = 0;

    int i;

    long long total = 0;
    for (i = 0; i < chalkSize; ++i) {
        total += chalk[i];
    }
    k %= total;

    for (i = 0; i < chalkSize; ++i) {
        if (chalk[i] > k) {
            retVal = i;
            break;
        }
        k -= chalk[i];
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int chalkReplacer(vector<int>& chalk, int k) {
        int retVal = 0;

        long long total = accumulate(chalk.begin(), chalk.end(), 0LL);
        k %= total;

        int chalkSize = chalk.size();
        for (int i = 0; i < chalkSize; ++i) {
            if (chalk[i] > k) {
                retVal = i;
                break;
            }
            k -= chalk[i];
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def chalkReplacer(self, chalk: List[int], k: int) -> int:
        retVal = 0

        total = sum(chalk)
        k = k % total

        for key, value in enumerate(chalk):
            if value > k:
                retVal = key
                break
            k -= value

        return retVal
```

</details>

## [1915. Number of Wonderful Substrings](https://leetcode.com/problems/number-of-wonderful-substrings)  2234

- [Official](https://leetcode.com/problems/number-of-wonderful-substrings/editorial/)
- [Official](https://leetcode.cn/problems/number-of-wonderful-substrings/solutions/847086/zui-mei-zi-zi-fu-chuan-de-shu-mu-by-leet-2j7g/)

<details><summary>Description</summary>

```text
A wonderful string is a string where at most one letter appears an odd number of times.
- For example, "ccjjc" and "abab" are wonderful, but "ab" is not.

Given a string word that consists of the first ten lowercase English letters ('a' through 'j'),
return the number of wonderful non-empty substrings in word.
If the same substring appears multiple times in word, then count each occurrence separately.

A substring is a contiguous sequence of characters in a string.

Example 1:
Input: word = "aba"
Output: 4
Explanation: The four wonderful substrings are underlined below:
- "aba" -> "a"
- "aba" -> "b"
- "aba" -> "a"
- "aba" -> "aba"

Example 2:
Input: word = "aabb"
Output: 9
Explanation: The nine wonderful substrings are underlined below:
- "aabb" -> "a"
- "aabb" -> "aa"
- "aabb" -> "aab"
- "aabb" -> "aabb"
- "aabb" -> "a"
- "aabb" -> "abb"
- "aabb" -> "b"
- "aabb" -> "bb"
- "aabb" -> "b"

Example 3:
Input: word = "he"
Output: 2
Explanation: The two wonderful substrings are underlined below:
- "he" -> "h"
- "he" -> "e"

Constraints:
1 <= word.length <= 10^5
word consists of lowercase English letters from 'a' to 'j'.
```

<details><summary>Hint</summary>

```text
1. For each prefix of the string,
   check which characters are of even frequency and which are not and represent it by a bitmask.
2. Find the other prefixes whose masks differs from the current prefix mask by at most one bit.
```

</details>

</details>

<details><summary>C</summary>

```c
struct hashTable {
    int key;
    int value;
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
long long wonderfulSubstrings(char* word) {
    long long retVal = 0;

    struct hashTable* pFrequency = NULL;
    struct hashTable* pTemp = NULL;

    // Create the frequency map : Key = bitmask, Value = frequency of bitmask key
    pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
    if (pTemp == NULL) {
        perror("malloc");
        goto exit;
    }
    pTemp->key = 0;
    pTemp->value = 1;
    HASH_ADD_INT(pFrequency, key, pTemp);

    int bit, odd, bitmask;
    int mask = 0;
    int wordSize = strlen(word);
    int i;
    for (i = 0; i < wordSize; ++i) {
        // a string word that consists of the first ten lowercase English letters
        bit = word[i] - 'a';

        // Flip the parity of the c-th bit in the running prefix mask
        mask ^= (1 << bit);

        // Count smaller prefixes that create substrings with no odd occurring letters
        pTemp = NULL;
        HASH_FIND_INT(pFrequency, &mask, pTemp);
        if (pTemp != NULL) {
            retVal += pTemp->value;
            pTemp->value += 1;
        } else {
            pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                goto exit;
            }
            pTemp->key = mask;
            pTemp->value = 1;
            HASH_ADD_INT(pFrequency, key, pTemp);
        }

        // Loop through every possible letter that can appear an odd number of times in a substring
        for (odd = 0; odd < 10; ++odd) {
            bitmask = mask ^ (1 << odd);
            pTemp = NULL;
            HASH_FIND_INT(pFrequency, &bitmask, pTemp);
            if (pTemp != NULL) {
                retVal += pTemp->value;
            }
        }
    }

exit:
    freeAll(pFrequency);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long wonderfulSubstrings(string word) {
        long long retVal = 0;

        // Create the frequency map : Key = bitmask, Value = frequency of bitmask key
        unordered_map<int, int> frequency;
        frequency[0] = 1;

        int mask = 0;
        for (auto c : word) {
            // a string word that consists of the first ten lowercase English letters
            int bit = c - 'a';

            // Flip the parity of the c-th bit in the running prefix mask
            mask ^= (1 << bit);

            // Count smaller prefixes that create substrings with no odd occurring letters
            auto iterator = frequency.find(mask);
            if (iterator != frequency.end()) {
                retVal += frequency[mask];
                frequency[mask] += 1;
            } else {
                frequency[mask] = 1;
            }

            // Loop through every possible letter that can appear an odd number of times in a substring
            for (int odd = 0; odd < 10; ++odd) {
                int bitmask = mask ^ (1 << odd);
                auto iterator = frequency.find(bitmask);
                if (iterator != frequency.end()) {
                    retVal += frequency[bitmask];
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
    def wonderfulSubstrings(self, word: str) -> int:
        retVal = 0

        # Create the frequency map: Key = bitmask, Value = frequency of bitmask key
        frequency = {}
        frequency[0] = 1

        mask = 0
        for c in word:
            # a string word that consists of the first ten lowercase English letters
            bit = ord(c) - ord('a')

            # Flip the parity of the c-th bit in the running prefix mask
            mask ^= (1 << bit)
            if mask in frequency:   # Count smaller prefixes that create substrings with no odd occurring letters
                retVal += frequency[mask]
                frequency[mask] += 1
            else:
                frequency[mask] = 1

            # Loop through every possible letter that can appear an odd number of times in a substring
            for odd in range(0, 10):
                bitmask = mask ^ (1 << odd)
                if bitmask in frequency:
                    retVal += frequency[bitmask]

        return retVal
```

</details>

## [1991. Find the Middle Index in Array](https://leetcode.com/problems/find-the-middle-index-in-array/)  1302

- [Official](https://leetcode.cn/problems/find-the-middle-index-in-array/solutions/1010005/zhao-dao-shu-zu-de-zhong-jian-wei-zhi-by-s8cy/)

<details><summary>Description</summary>

```text
Given a 0-indexed integer array nums, find the leftmost middleIndex (i.e., the smallest amongst all the possible ones).

A middleIndex is an index where
nums[0] + nums[1] + ... + nums[middleIndex-1] == nums[middleIndex+1] + nums[middleIndex+2] + ... + nums[nums.length-1].

If middleIndex == 0, the left side sum is considered to be 0.
Similarly, if middleIndex == nums.length - 1, the right side sum is considered to be 0.

Return the leftmost middleIndex that satisfies the condition, or -1 if there is no such index.

Example 1:
Input: nums = [2,3,-1,8,4]
Output: 3
Explanation: The sum of the numbers before index 3 is: 2 + 3 + -1 = 4
The sum of the numbers after index 3 is: 4 = 4

Example 2:
Input: nums = [1,-1,4]
Output: 2
Explanation: The sum of the numbers before index 2 is: 1 + -1 = 0
The sum of the numbers after index 2 is: 0

Example 3:
Input: nums = [2,5]
Output: -1
Explanation: There is no valid middleIndex.

Constraints:
1 <= nums.length <= 100
-1000 <= nums[i] <= 1000

Note: This question is the same as 724: https://leetcode.com/problems/find-pivot-index/
```

<details><summary>Hint</summary>

```text
1. Could we go from left to right and check to see if an index is a middle index?
2. Do we need to sum every number to the left and right of an index each time?
3. Use a prefix sum array where prefix[i] = nums[0] + nums[1] + ... + nums[i].
```

</details>

</details>

<details><summary>C</summary>

```c
int findMiddleIndex(int* nums, int numsSize) {
    int retVal = -1;

    int i;

    int sumLeft[numsSize];
    sumLeft[0] = nums[0];
    for (i = 1; i < numsSize; ++i) {
        sumLeft[i] = sumLeft[i - 1] + nums[i];
    }

    int sumRight[numsSize];
    sumRight[numsSize - 1] = nums[numsSize - 1];
    for (i = numsSize - 2; i >= 0; --i) {
        sumRight[i] = sumRight[i + 1] + nums[i];
    }

    for (i = 0; i < numsSize; ++i) {
        if (sumLeft[i] == sumRight[i]) {
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
    int findMiddleIndex(vector<int>& nums) {
        int retVal = -1;

        int numsSize = nums.size();

        vector<int> sumLeft(numsSize, 0);
        sumLeft[0] = nums[0];
        for (int i = 1; i < numsSize; ++i) {
            sumLeft[i] = sumLeft[i - 1] + nums[i];
        }

        vector<int> sumRight(numsSize, 0);
        sumRight[numsSize - 1] = nums[numsSize - 1];
        for (int i = numsSize - 2; i >= 0; --i) {
            sumRight[i] = sumRight[i + 1] + nums[i];
        }

        for (int i = 0; i < numsSize; ++i) {
            if (sumLeft[i] == sumRight[i]) {
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
    def findMiddleIndex(self, nums: List[int]) -> int:
        retVal = -1

        numsSize = len(nums)

        sumLeft = [0] * numsSize
        sumLeft[0] = nums[0]
        for i in range(1, numsSize):
            sumLeft[i] = sumLeft[i - 1] + nums[i]

        sumRight = [0] * numsSize
        sumRight[numsSize - 1] = nums[numsSize - 1]
        for i in range(numsSize - 2, -1, -1):
            sumRight[i] = sumRight[i + 1] + nums[i]

        for i in range(numsSize):
            if sumLeft[i] == sumRight[i]:
                retVal = i
                break

        return retVal
```

</details>

## [2256. Minimum Average Difference](https://leetcode.com/problems/minimum-average-difference/)  1394

- [Official](https://leetcode.com/problems/minimum-average-difference/solutions/2709899/minimum-average-difference/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array nums of length n.

The average difference of the index i is the absolute difference between
the average of the first i + 1 elements of nums and the average of the last n - i - 1 elements.
Both averages should be rounded down to the nearest integer.

Return the index with the minimum average difference. If there are multiple such indices, return the smallest one.

Note:
- The absolute difference of two numbers is the absolute value of their difference.
- The average of n elements is the sum of the n elements divided (integer division) by n.
- The average of 0 elements is considered to be 0.

Example 1:
Input: nums = [2,5,3,9,5,3]
Output: 3
Explanation:
- The average difference of index 0 is: |2 / 1 - (5 + 3 + 9 + 5 + 3) / 5| = |2 / 1 - 25 / 5| = |2 - 5| = 3.
- The average difference of index 1 is: |(2 + 5) / 2 - (3 + 9 + 5 + 3) / 4| = |7 / 2 - 20 / 4| = |3 - 5| = 2.
- The average difference of index 2 is: |(2 + 5 + 3) / 3 - (9 + 5 + 3) / 3| = |10 / 3 - 17 / 3| = |3 - 5| = 2.
- The average difference of index 3 is: |(2 + 5 + 3 + 9) / 4 - (5 + 3) / 2| = |19 / 4 - 8 / 2| = |4 - 4| = 0.
- The average difference of index 4 is: |(2 + 5 + 3 + 9 + 5) / 5 - 3 / 1| = |24 / 5 - 3 / 1| = |4 - 3| = 1.
- The average difference of index 5 is: |(2 + 5 + 3 + 9 + 5 + 3) / 6 - 0| = |27 / 6 - 0| = |4 - 0| = 4.
The average difference of index 3 is the minimum average difference so return 3.

Example 2:
Input: nums = [0]
Output: 0
Explanation:
The only index is 0 so return 0.
The average difference of index 0 is: |0 / 1 - 0| = |0 - 0| = 0.

Constraints:
1 <= nums.length <= 10^5
0 <= nums[i] <= 10^5
```

</details>

<details><summary>C</summary>

```c
int minimumAverageDifference(int* nums, int numsSize) {
    int retVal = 0;

    // Boundary Conditions: numsSize is 1
    if (numsSize == 1) {
        return retVal;
    }

    // Prepare sum of all elements
    long long sum = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        sum += nums[i];
    }

    long long currentDiff;
    long long minDiff = LONG_MAX;
    long long prefixSum = 0;
    // avoid divide zero, so prefix range from 0 to (numsSize - 1).
    for (i = 0; i < (numsSize - 1); ++i) {
        prefixSum += nums[i];
        sum -= nums[i];
        currentDiff = abs((prefixSum / (i + 1)) - (sum / (numsSize - (i + 1))));
        if (minDiff > currentDiff) {
            minDiff = currentDiff;
            retVal = i;
        }
    }

    // Boundary Conditions: prefix has numsSize elements, others is zero.
    prefixSum += nums[i];
    currentDiff = (prefixSum / (i + 1));
    if (minDiff > currentDiff) {
        minDiff = currentDiff;
        retVal = i;
    }

    return retVal;
}
```

</details>

## [2391. Minimum Amount of Time to Collect Garbage](https://leetcode.com/problems/minimum-amount-of-time-to-collect-garbage/)  1455

- [Official](https://leetcode.com/problems/minimum-amount-of-time-to-collect-garbage/editorial/)

<details><summary>Description</summary>

```text
You are given a 0-indexed array of strings garbage
where garbage[i] represents the assortment of garbage at the ith house.
garbage[i] consists only of the characters 'M', 'P' and 'G' representing one unit of metal,
paper and glass garbage respectively.
Picking up one unit of any type of garbage takes 1 minute.

You are also given a 0-indexed integer array travel
where travel[i] is the number of minutes needed to go from house i to house i + 1.

There are three garbage trucks in the city, each responsible for picking up one type of garbage.
Each garbage truck starts at house 0 and must visit each house in order; however, they do not need to visit every house.

Only one garbage truck may be used at any given moment.
While one truck is driving or picking up garbage, the other two trucks cannot do anything.

Return the minimum number of minutes needed to pick up all the garbage.

Example 1:
Input: garbage = ["G","P","GP","GG"], travel = [2,4,3]
Output: 21
Explanation:
The paper garbage truck:
1. Travels from house 0 to house 1
2. Collects the paper garbage at house 1
3. Travels from house 1 to house 2
4. Collects the paper garbage at house 2
Altogether, it takes 8 minutes to pick up all the paper garbage.
The glass garbage truck:
1. Collects the glass garbage at house 0
2. Travels from house 0 to house 1
3. Travels from house 1 to house 2
4. Collects the glass garbage at house 2
5. Travels from house 2 to house 3
6. Collects the glass garbage at house 3
Altogether, it takes 13 minutes to pick up all the glass garbage.
Since there is no metal garbage, we do not need to consider the metal garbage truck.
Therefore, it takes a total of 8 + 13 = 21 minutes to collect all the garbage.

Example 2:
Input: garbage = ["MMM","PGM","GP"], travel = [3,10]
Output: 37
Explanation:
The metal garbage truck takes 7 minutes to pick up all the metal garbage.
The paper garbage truck takes 15 minutes to pick up all the paper garbage.
The glass garbage truck takes 15 minutes to pick up all the glass garbage.
It takes a total of 7 + 15 + 15 = 37 minutes to collect all the garbage.

Constraints:
2 <= garbage.length <= 10^5
garbage[i] consists of only the letters 'M', 'P', and 'G'.
1 <= garbage[i].length <= 10
travel.length == garbage.length - 1
1 <= travel[i] <= 100
```

<details><summary>Hint</summary>

```text
1. Where can we save time? By not visiting all the houses.
2. For each type of garbage, find the house with the highest index that has at least 1 unit of this type of garbage.
```

</details>

</details>

<details><summary>C</summary>

```c
int garbageCollection(char** garbage, int garbageSize, int* travel, int travelSize) {
    int retVal = 0;

    int i, j;

    int travelPrefixSum[travelSize + 1];
    memset(travelPrefixSum, 0, sizeof(travelPrefixSum));
    for (i = 0; i < travelSize; ++i) {
        travelPrefixSum[i + 1] = travelPrefixSum[i] + travel[i];
    }

    // garbage[i] consists only of the characters 'M', 'P' and 'G'
    int garbageType = 4;
    int lastGarbage[garbageType];
    memset(lastGarbage, 0, sizeof(lastGarbage));

    int len;
    for (i = 0; i < garbageSize; ++i) {
        len = strlen(garbage[i]);
        for (j = 0; j < len; ++j) {
            if (garbage[i][j] == 'M') {
                lastGarbage[1] = i;
            } else if (garbage[i][j] == 'P') {
                lastGarbage[2] = i;
            } else if (garbage[i][j] == 'G') {
                lastGarbage[3] = i;
            }
            retVal += 1;
        }
    }

    for (i = 0; i < garbageType; ++i) {
        retVal += travelPrefixSum[lastGarbage[i]];
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int garbageCollection(vector<string>& garbage, vector<int>& travel) {
        int retVal = 0;

        int travelSize = travel.size();
        vector<int> travelPrefixSum((travelSize + 1), 0);
        for (int i = 0; i < travelSize; ++i) {
            travelPrefixSum[i + 1] = travelPrefixSum[i] + travel[i];
        }

        // garbage[i] consists only of the characters 'M', 'P' and 'G'
        int garbageType = 4;
        vector<int> lastGarbage(garbageType, 0);
        int garbageSize = garbage.size();
        for (int i = 0; i < garbageSize; ++i) {
            for (char c : garbage[i]) {
                if (c == 'M') {
                    lastGarbage[1] = i;
                } else if (c == 'P') {
                    lastGarbage[2] = i;
                } else if (c == 'G') {
                    lastGarbage[3] = i;
                }
                retVal += 1;
            }
        }

        for (int i = 0; i < garbageType; ++i) {
            retVal += travelPrefixSum[lastGarbage[i]];
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def garbageCollection(self, garbage: List[str], travel: List[int]) -> int:
        retVal = 0

        travelSize = len(travel)
        travelPrefixSum = [0] * (travelSize+1)
        for i in range(travelSize):
            travelPrefixSum[i+1] = travelPrefixSum[i] + travel[i]

        # garbage[i] consists only of the characters 'M', 'P' and 'G'
        garbageType = 4

        lastGarbage = [0] * garbageType
        for index, value in enumerate(garbage):
            for p in value:
                if p == 'M':
                    lastGarbage[1] = index
                elif p == 'P':
                    lastGarbage[2] = index
                elif p == 'G':
                    lastGarbage[3] = index

                retVal += 1

        for i in range(garbageType):
            retVal += travelPrefixSum[lastGarbage[i]]

        return retVal
```

</details>

## [2483. Minimum Penalty for a Shop](https://leetcode.com/problems/minimum-penalty-for-a-shop/)  1494

- [Official](https://leetcode.com/problems/minimum-penalty-for-a-shop/editorial/)

<details><summary>Description</summary>

```text
You are given the customer visit log of a shop represented by a 0-indexed string
customers consisting only of characters 'N' and 'Y':
- if the ith character is 'Y', it means that customers come at the ith hour
- whereas 'N' indicates that no customers come at the ith hour.

If the shop closes at the jth hour (0 <= j <= n), the penalty is calculated as follows:
- For every hour when the shop is open and no customers come, the penalty increases by 1.
- For every hour when the shop is closed and customers come, the penalty increases by 1.

Return the earliest hour at which the shop must be closed to incur a minimum penalty.

Note that if a shop closes at the jth hour, it means the shop is closed at the hour j.

Example 1:
Input: customers = "YYNY"
Output: 2
Explanation:
- Closing the shop at the 0th hour incurs in 1+1+0+1 = 3 penalty.
- Closing the shop at the 1st hour incurs in 0+1+0+1 = 2 penalty.
- Closing the shop at the 2nd hour incurs in 0+0+0+1 = 1 penalty.
- Closing the shop at the 3rd hour incurs in 0+0+1+1 = 2 penalty.
- Closing the shop at the 4th hour incurs in 0+0+1+0 = 1 penalty.
Closing the shop at 2nd or 4th hour gives a minimum penalty. Since 2 is earlier, the optimal closing time is 2.

Example 2:
Input: customers = "NNNNN"
Output: 0
Explanation: It is best to close the shop at the 0th hour as no customers arrive.

Example 3:
Input: customers = "YYYY"
Output: 4
Explanation: It is best to close the shop at the 4th hour as customers arrive at each hour.

Constraints:
1 <= customers.length <= 10^5
customers consists only of characters 'Y' and 'N'.
```

<details><summary>Hint</summary>

```text
1. At any index, the penalty is the sum of prefix count of 'N' and suffix count of 'Y'.
2. Enumerate all indices and find the minimum such value.
```

</details>

</details>

<details><summary>C</summary>

```c
int bestClosingTime(char *customers) {
    int retVal = 0;

    /* At any index, the penalty is the sum of prefix count of 'N' and suffix count of 'Y'.
     *  Y Y N Y     N N N N N     Y Y Y Y
     *  3 2 1 1 0   0 0 0 0 0 0   4 3 2 1 0
     *  0 0 0 1 1   0 1 2 3 4 5   0 0 0 0 0
     */
    int customersSize = strlen(customers);
    int penalty = 0;
    int i;
    for (i = 0; i < customersSize; ++i) {
        if (customers[i] == 'Y') {
            ++penalty;
        }
    }
    int minPenalty = penalty;
    for (i = 0; i < customersSize; ++i) {
        if (customers[i] == 'Y') {
            --penalty;
        } else if (customers[i] == 'N') {
            ++penalty;
        }

        if (minPenalty > penalty) {
            minPenalty = penalty;
            retVal = i + 1;
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
    int bestClosingTime(string customers) {
        int retVal = 0;

        /* At any index, the penalty is the sum of prefix count of 'N' and suffix count of 'Y'.
         *  Y Y N Y     N N N N N     Y Y Y Y
         *  3 2 1 1 0   0 0 0 0 0 0   4 3 2 1 0
         *  0 0 0 1 1   0 1 2 3 4 5   0 0 0 0 0
         */
        int penalty = count(customers.begin(), customers.end(), 'Y');
        int minPenalty = penalty;
        int customersSize = customers.size();
        for (int i = 0; i < customersSize; ++i) {
            if (customers[i] == 'Y') {
                --penalty;
            } else if (customers[i] == 'N') {
                ++penalty;
            }

            if (minPenalty > penalty) {
                minPenalty = penalty;
                retVal = i + 1;
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
    def bestClosingTime(self, customers: str) -> int:
        retVal = 0

        # /* At any index, the penalty is the sum of prefix count of 'N' and suffix count of 'Y'.
        #  *  Y Y N Y     N N N N N     Y Y Y Y
        #  *  3 2 1 1 0   0 0 0 0 0 0   4 3 2 1 0
        #  *  0 0 0 1 1   0 1 2 3 4 5   0 0 0 0 0
        #  */
        penalty = customers.count('Y')
        minPenalty = penalty
        customersSize = len(customers)
        for i in range(customersSize):
            if customers[i] == 'Y':
                penalty -= 1
            elif customers[i] == 'N':
                penalty += 1

            if minPenalty > penalty:
                minPenalty = penalty
                retVal = i + 1

        return retVal
```

</details>

## [2779. Maximum Beauty of an Array After Applying Operation](https://leetcode.com/problems/maximum-beauty-of-an-array-after-applying-operation/)  2779

- [Official](https://leetcode.com/problems/maximum-beauty-of-an-array-after-applying-operation/editorial/)
- [Official](https://leetcode.cn/problems/maximum-beauty-of-an-array-after-applying-operation/solutions/2806897/shu-zu-de-zui-da-mei-li-zhi-by-leetcode-9jgs0/)

<details><summary>Description</summary>

```text
You are given a 0-indexed array nums and a non-negative integer k.

In one operation, you can do the following:
- Choose an index i that hasn't been chosen before from the range [0, nums.length - 1].
- Replace nums[i] with any integer from the range [nums[i] - k, nums[i] + k].

The beauty of the array is the length of the longest subsequence consisting of equal elements.

Return the maximum possible beauty of the array nums after applying the operation any number of times.

Note that you can apply the operation to each index only once.

A subsequence of an array is a new array generated from the original array by deleting some elements (possibly none)
without changing the order of the remaining elements.

Example 1:
Input: nums = [4,6,1,2], k = 2
Output: 3
Explanation: In this example, we apply the following operations:
- Choose index 1, replace it with 4 (from range [4,8]), nums = [4,4,1,2].
- Choose index 3, replace it with 4 (from range [0,4]), nums = [4,4,1,4].
After the applied operations, the beauty of the array nums is 3 (subsequence consisting of indices 0, 1, and 3).
It can be proven that 3 is the maximum possible length we can achieve.

Example 2:
Input: nums = [1,1,1,1], k = 10
Output: 4
Explanation: In this example we don't have to apply any operations.
The beauty of the array nums is 4 (whole array).

Constraints:
1 <= nums.length <= 10^5
0 <= nums[i], k <= 10^5
```

<details><summary>Hint</summary>

```text
1. Sort the array.
2. The problem becomes the following: find maximum subarray A[i … j] such that A[j] - A[i] ≤ 2 * k.
```

</details>

</details>

<details><summary>C</summary>

```c
int maximumBeauty(int* nums, int numsSize, int k) {
    int retVal = 0;

    if (numsSize == 1) {  // If there's only one element, the maximum beauty is 1
        retVal = 1;
        return retVal;
    }

    int maxValue = 0;
    for (int i = 0; i < numsSize; ++i) {
        maxValue = fmax(maxValue, nums[i]);
    }

    int countSize = maxValue + 1;
    int count[maxValue + 1];
    memset(count, 0, sizeof(count));
    int idx;
    for (int i = 0; i < numsSize; ++i) {
        idx = fmax(nums[i] - k, 0);
        count[idx]++;  // Increment at the start of the range
        if (nums[i] + k + 1 <= maxValue) {
            count[nums[i] + k + 1]--;  // Decrement after the range
        }
    }

    // Calculate the prefix sum and find the maximum value
    int currentSum = 0;
    for (int i = 0; i < countSize; ++i) {
        currentSum += count[i];
        retVal = fmax(retVal, currentSum);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maximumBeauty(vector<int>& nums, int k) {
        int retVal = 0;

        int numsSize = nums.size();
        if (numsSize == 1) {  // If there's only one element, the maximum beauty is 1
            retVal = 1;
            return retVal;
        }

        int maxValue = 0;
        for (int num : nums) {
            maxValue = max(maxValue, num);
        }

        vector<int> count(maxValue + 1, 0);
        for (int num : nums) {
            count[max(num - k, 0)]++;  // Increment at the start of the range
            if (num + k + 1 <= maxValue) {
                count[num + k + 1]--;  // Decrement after the range
            }
        }

        // Calculate the prefix sum and find the maximum value
        int currentSum = 0;
        for (int value : count) {
            currentSum += value;
            retVal = max(retVal, currentSum);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maximumBeauty(self, nums: List[int], k: int) -> int:
        retVal = 0

        numsSize = len(nums)
        if numsSize == 1:  # If there's only one element, the maximum beauty is 1
            retVal = 1
            return retVal

        maxValue = max(nums)
        count = [0] * (maxValue + 1)
        for num in nums:
            count[max(num - k, 0)] += 1  # Increment at the start of the range
            if num + k + 1 <= maxValue:
                count[num + k + 1] -= 1  # Decrement after the range

        # Calculate the prefix sum and find the maximum beauty
        currentSum = 0
        for value in count:
            currentSum += value
            retVal = max(retVal, currentSum)

        return retVal
```

</details>

## [3152. Special Array II](https://leetcode.com/problems/special-array-ii/)  1523

- [Official](https://leetcode.com/problems/special-array-ii/editorial/)
- [Official](https://leetcode.cn/problems/special-array-ii/solutions/2877223/te-shu-shu-zu-ii-by-leetcode-solution-ozu1/)

<details><summary>Description</summary>

```text
An array is considered special if every pair of its adjacent elements contains two numbers with different parity.

You are given an array of integer nums and a 2D integer matrix queries,
where for queries[i] = [fromi, toi] your task is to check that subarray nums[fromi..toi] is special or not.

Return an array of booleans answer such that answer[i] is true if nums[fromi..toi] is special.

Example 1:
Input: nums = [3,4,1,2,6], queries = [[0,4]]
Output: [false]
Explanation:
The subarray is [3,4,1,2,6]. 2 and 6 are both even.

Example 2:
Input: nums = [4,3,1,6], queries = [[0,2],[2,3]]
Output: [false,true]
Explanation:
The subarray is [4,3,1]. 3 and 1 are both odd. So the answer to this query is false.
The subarray is [1,6]. There is only one pair: (1,6) and it contains numbers with different parity.
So the answer to this query is true.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^5
1 <= queries.length <= 10^5
queries[i].length == 2
0 <= queries[i][0] <= queries[i][1] <= nums.length - 1
```

<details><summary>Hint</summary>

```text
1. Try to split the array into some non-intersected continuous special subarrays.
2. For each query check that the first and the last elements of that query are in the same subarray or not.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* isArraySpecial(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    bool* pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (bool*)malloc(queriesSize * sizeof(bool));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (queriesSize) * sizeof(bool));

    int prefix[numsSize];
    memset(prefix, 0, sizeof(prefix));
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i] % 2 == nums[i - 1] % 2) {
            prefix[i] = prefix[i - 1] + 1;  // new violative index found
        } else {
            prefix[i] = prefix[i - 1];
        }
    }

    bool value;
    int start, end;
    for (int i = 0; i < queriesSize; ++i) {
        start = queries[i][0];
        end = queries[i][1];
        value = (prefix[end] - prefix[start] == 0);
        pRetVal[(*returnSize)] = value;
        (*returnSize) += 1;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++

class Solution {
   public:
    vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries) {
        vector<bool> retVal;

        int numsSize = nums.size();
        vector<int> prefix(numsSize, 0);
        for (int i = 1; i < numsSize; ++i) {
            if (nums[i] % 2 == nums[i - 1] % 2) {
                prefix[i] = prefix[i - 1] + 1;  // new violative index found
            } else {
                prefix[i] = prefix[i - 1];
            }
        }

        for (auto& query : queries) {
            int start = query[0];
            int end = query[1];
            bool value = (prefix[end] - prefix[start] == 0);
            retVal.emplace_back(value);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def isArraySpecial(self, nums: List[int], queries: List[List[int]]) -> List[bool]:
        retVal = []

        numsSize = len(nums)
        prefix = [0] * numsSize
        for i in range(1, numsSize):
            if nums[i] % 2 == nums[i - 1] % 2:
                prefix[i] = prefix[i - 1] + 1  # new violative index found
            else:
                prefix[i] = prefix[i - 1]

        for start, end in queries:
            value = (prefix[end] - prefix[start] == 0)
            retVal.append(value)

        return retVal
```

</details>
