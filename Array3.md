# Array

## [2009. Minimum Number of Operations to Make Array Continuous](https://leetcode.com/problems/minimum-number-of-operations-to-make-array-continuous/)  2084

- [Official](https://leetcode.com/problems/minimum-number-of-operations-to-make-array-continuous/editorial/)

<details><summary>Description</summary>

```text
You are given an integer array nums. In one operation, you can replace any element in nums with any integer.

nums is considered continuous if both of the following conditions are fulfilled:
- All elements in nums are unique.
- The difference between the maximum element and the minimum element in nums equals nums.length - 1.

For example, nums = [4, 2, 5, 3] is continuous, but nums = [1, 2, 3, 5, 6] is not continuous.

Return the minimum number of operations to make nums continuous.

Example 1:
Input: nums = [4,2,5,3]
Output: 0
Explanation: nums is already continuous.

Example 2:
Input: nums = [1,2,3,5,6]
Output: 1
Explanation: One possible solution is to change the last element to 4.
The resulting array is [1,2,3,5,4], which is continuous.

Example 3:
Input: nums = [1,10,100,1000]
Output: 3
Explanation: One possible solution is to:
- Change the second element to 2.
- Change the third element to 3.
- Change the fourth element to 4.
The resulting array is [1,2,3,4], which is continuous.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Sort the array.
2. For every index do a binary search to get the possible right end of the window and calculate the possible answer.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int minOperations(int* nums, int numsSize) {
    int retVal = 0;

    int numsSort[numsSize];
    memset(numsSort, 0, sizeof(numsSort));
    memcpy(numsSort, nums, sizeof(numsSort));
    qsort(numsSort, numsSize, sizeof(int), compareInteger);

    int numsUiqueSortSize = 0;
    int numsUiqueSort[numsSize];
    memset(numsUiqueSort, 0, sizeof(numsUiqueSort));
    numsUiqueSort[numsUiqueSortSize++] = numsSort[0];
    int i;
    for (i = 1; i < numsSize; ++i) {
        if (numsSort[i] != numsUiqueSort[numsUiqueSortSize - 1]) {
            numsUiqueSort[numsUiqueSortSize++] = numsSort[i];
        }
    }

    retVal = numsSize;
    int count;
    int j = 0;
    for (i = 0; i < numsUiqueSortSize; i++) {
        while ((j < numsUiqueSortSize) && (numsUiqueSort[j] < numsUiqueSort[i] + numsSize)) {
            j++;
        }

        count = j - i;
        retVal = fmin(retVal, numsSize - count);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minOperations(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        set<int> unique(nums.begin(), nums.end());
        vector<int> numsUiqueSort;
        for (int num : unique) {
            numsUiqueSort.push_back(num);
        }
        int numsUiqueSortSize = numsUiqueSort.size();

        retVal = numsSize;
        int j = 0;
        for (int i = 0; i < numsUiqueSortSize; i++) {
            while ((j < numsUiqueSortSize) && (numsUiqueSort[j] < numsUiqueSort[i] + numsSize)) {
                j++;
            }

            int count = j - i;
            retVal = min(retVal, numsSize - count);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minOperations(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        numsUiqueSort = sorted(set(nums))
        numsUiqueSortSize = len(numsUiqueSort)

        retVal = numsSize
        j = 0
        for i in range(numsUiqueSortSize):
            while (j < numsUiqueSortSize) and (numsUiqueSort[j] < numsUiqueSort[i] + numsSize):
                j += 1
            count = j - i
            retVal = min(retVal, numsSize - count)

        return retVal
```

</details>

## [2016. Maximum Difference Between Increasing Elements](https://leetcode.com/problems/maximum-difference-between-increasing-elements/)  1246

<details><summary>Description</summary>

```text
Given a 0-indexed integer array nums of size n,
find the maximum difference between nums[i] and nums[j] (i.e., nums[j] - nums[i]),
such that 0 <= i < j < n and nums[i] < nums[j].

Return the maximum difference. If no such i and j exists, return -1.

Example 1:
Input: nums = [7,1,5,4]
Output: 4
Explanation:
The maximum difference occurs with i = 1 and j = 2, nums[j] - nums[i] = 5 - 1 = 4.
Note that with i = 1 and j = 0, the difference nums[j] - nums[i] = 7 - 1 = 6, but i > j, so it is not valid.

Example 2:
Input: nums = [9,4,3,2]
Output: -1
Explanation:
There is no i and j such that i < j and nums[i] < nums[j].

Example 3:
Input: nums = [1,5,2,10]
Output: 9
Explanation:
The maximum difference occurs with i = 0 and j = 3, nums[j] - nums[i] = 10 - 1 = 9.

Constraints:
n == nums.length
2 <= n <= 1000
1 <= nums[i] <= 10^9
```

</details>

<details><summary>C</summary>

```c
int maximumDifference(int* nums, int numsSize) {
    int retVal = -1;  // If no such i and j exists, return -1.

    int i = 0;
    int j;
    for (j = 1; j < numsSize; ++j) {
        if (nums[j] < nums[i]) {
            i = j;
            continue;
        }

        retVal = fmax(retVal, nums[j] - nums[i]);
    }

    // find the maximum difference between nums[i] and nums[j], such that 0 <= i < j < n and nums[i] < nums[j].
    retVal = (retVal == 0) ? -1 : retVal;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maximumDifference(vector<int>& nums) {
        int retVal = -1;  // If no such i and j exists, return -1.

        // 1 <= nums[i] <= 10^9
        int minNum = 1e9 + 1;
        int maxNum = 1e9 + 1;
        for (auto num : nums) {
            if (minNum > num) {
                minNum = num;
                maxNum = num;
                continue;
            }

            if (maxNum < num) {
                maxNum = num;
            }

            retVal = max(retVal, maxNum - minNum);
        }

        // find the maximum difference between nums[i] and nums[j], such that 0 <= i < j < n and nums[i] < nums[j].
        retVal = (retVal == 0) ? -1 : retVal;

        return retVal;
    }
};
```

</details>

## [2022. Convert 1D Array Into 2D Array](https://leetcode.com/problems/convert-1d-array-into-2d-array/)  1307

- [Official](https://leetcode.com/problems/convert-1d-array-into-2d-array/editorial/)
- [Official](https://leetcode.cn/problems/convert-1d-array-into-2d-array/solutions/1185411/jiang-yi-wei-shu-zu-zhuan-bian-cheng-er-zt47o/)

<details><summary>Description</summary>

```text
You are given a 0-indexed 1-dimensional (1D) integer array original, and two integers, m and n.
You are tasked with creating a 2-dimensional (2D) array with m rows and n columns using all the elements from original.

The elements from indices 0 to n - 1 (inclusive) of original should form the first row of the constructed 2D array,
the elements from indices n to 2 * n - 1 (inclusive) should form the second row of the constructed 2D array, and so on.

Return an m x n 2D array constructed according to the above procedure, or an empty 2D array if it is impossible.

Example 1:
Input: original = [1,2,3,4], m = 2, n = 2
Output: [[1,2],[3,4]]
Explanation: The constructed 2D array should contain 2 rows and 2 columns.
The first group of n=2 elements in original, [1,2], becomes the first row in the constructed 2D array.
The second group of n=2 elements in original, [3,4], becomes the second row in the constructed 2D array.

Example 2:
Input: original = [1,2,3], m = 1, n = 3
Output: [[1,2,3]]
Explanation: The constructed 2D array should contain 1 row and 3 columns.
Put all three elements in original into the first row of the constructed 2D array.

Example 3:
Input: original = [1,2], m = 1, n = 1
Output: []
Explanation: There are 2 elements in original.
It is impossible to fit 2 elements in a 1x1 2D array, so return an empty 2D array.

Constraints:
1 <= original.length <= 5 * 10^4
1 <= original[i] <= 10^5
1 <= m, n <= 4 * 10^4
```

<details><summary>Hint</summary>

```text
1. When is it possible to convert original into a 2D array and when is it impossible?
2. It is possible if and only if m * n == original.length
3. If it is possible to convert original to a 2D array,
   keep an index i such that original[i] is the next element to add to the 2D array.
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
int** construct2DArray(int* original, int originalSize, int m, int n, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    if (originalSize != (m * n)) {
        return pRetVal;
    }

    (*returnColumnSizes) = (int*)malloc(m * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, (m * sizeof(int)));

    pRetVal = (int**)malloc(m * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }

    int originalIndex = 0;
    int x, y;
    for (x = 0; x < m; ++x) {
        pRetVal[x] = (int*)malloc(n * sizeof(int));
        if (pRetVal[x] == NULL) {
            perror("malloc");
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            for (int i = 0; i < x; ++i) {
                free(pRetVal[i]);
                pRetVal[i] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        memset(pRetVal[x], 0, (n * sizeof(int)));
        for (y = 0; y < n; ++y) {
            pRetVal[x][y] = original[originalIndex++];
        }
        (*returnColumnSizes)[x] = n;
    }
    (*returnSize) = m;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<vector<int>> construct2DArray(vector<int>& original, int m, int n) {
        vector<vector<int>> retVal;

        int originalSize = original.size();
        if (originalSize != m * n) {
            return retVal;
        }
        retVal.resize(m, vector<int>(n, false));

        int originalIndex = 0;
        for (int x = 0; x < m; ++x) {
            for (int y = 0; y < n; ++y) {
                retVal[x][y] = original[originalIndex++];
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
    def construct2DArray(self, original: List[int], m: int, n: int) -> List[List[int]]:
        retVal = []

        originalSize = len(original)
        if originalSize != m * n:
            return retVal
        retVal = [[0] * n for _ in range(m)]

        originalIndex = 0
        for x in range(m):
            for y in range(n):
                retVal[x][y] = original[originalIndex]
                originalIndex += 1

        return retVal
```

</details>

## [2078. Two Furthest Houses With Different Colors](https://leetcode.com/problems/two-furthest-houses-with-different-colors/)  1240

<details><summary>Description</summary>

```text
There are n houses evenly lined up on the street, and each house is beautifully painted.
You are given a 0-indexed integer array colors of length n, where colors[i] represents the color of the ith house.

Return the maximum distance between two houses with different colors.

The distance between the ith and jth houses is abs(i - j), where abs(x) is the absolute value of x.

Example 1:
Input: colors = [1,1,1,6,1,1,1]
Output: 3
Explanation: In the above image, color 1 is blue, and color 6 is red.
The furthest two houses with different colors are house 0 and house 3.
House 0 has color 1, and house 3 has color 6. The distance between them is abs(0 - 3) = 3.
Note that houses 3 and 6 can also produce the optimal answer.

Example 2:
Input: colors = [1,8,3,8,3]
Output: 4
Explanation: In the above image, color 1 is blue, color 8 is yellow, and color 3 is green.
The furthest two houses with different colors are house 0 and house 4.
House 0 has color 1, and house 4 has color 3. The distance between them is abs(0 - 4) = 4.

Example 3:
Input: colors = [0,1]
Output: 1
Explanation: The furthest two houses with different colors are house 0 and house 1.
House 0 has color 0, and house 1 has color 1. The distance between them is abs(0 - 1) = 1.

Constraints:
n == colors.length
2 <= n <= 100
0 <= colors[i] <= 100
Test data are generated such that at least two houses have different colors.
```

</details>

<details><summary>C</summary>

```c
int maxDistance(int* colors, int colorsSize){
    int retVal = 1;

    int i, j;
    for (i=0; i<colorsSize; ++i)
    {
        for (j=colorsSize-1; j>i; --j)
        {
            if (colors[i] != colors[j])
            {
                retVal = (retVal>(j-i))?retVal:(j-i);
                break;
            }
        }
    }

    return retVal;
}
```

</details>

## [2145. Count the Hidden Sequences](https://leetcode.com/problems/count-the-hidden-sequences/)  1614

- [Official](https://leetcode.com/problems/count-the-hidden-sequences/editorial/)
- [Official](https://leetcode.cn/problems/count-the-hidden-sequences/solutions/1231197/tong-ji-yin-cang-shu-zu-shu-mu-by-leetco-t5su/)

<details><summary>Description</summary>

```text
You are given a 0-indexed array of n integers differences,
which describes the differences between each pair of consecutive integers of a hidden sequence of length (n + 1).
More formally, call the hidden sequence hidden, then we have that differences[i] = hidden[i + 1] - hidden[i].

You are further given two integers lower and upper
that describe the inclusive range of values [lower, upper] that the hidden sequence can contain.
- For example, given differences = [1, -3, 4], lower = 1, upper = 6,
  the hidden sequence is a sequence of length 4 whose elements are in between 1 and 6 (inclusive).
  - [3, 4, 1, 5] and [4, 5, 2, 6] are possible hidden sequences.
  - [5, 6, 3, 7] is not possible since it contains an element greater than 6.
  - [1, 2, 3, 4] is not possible since the differences are not correct.

Return the number of possible hidden sequences there are. If there are no possible sequences, return 0.

Example 1:
Input: differences = [1,-3,4], lower = 1, upper = 6
Output: 2
Explanation: The possible hidden sequences are:
- [3, 4, 1, 5]
- [4, 5, 2, 6]
Thus, we return 2.

Example 2:
Input: differences = [3,-4,5,1,-2], lower = -4, upper = 5
Output: 4
Explanation: The possible hidden sequences are:
- [-3, 0, -4, 1, 2, 0]
- [-2, 1, -3, 2, 3, 1]
- [-1, 2, -2, 3, 4, 2]
- [0, 3, -1, 4, 5, 3]
Thus, we return 4.

Example 3:
Input: differences = [4,-7,2], lower = 3, upper = 6
Output: 0
Explanation: There are no possible hidden sequences. Thus, we return 0.

Constraints:
n == differences.length
1 <= n <= 10^5
-10^5 <= differences[i] <= 10^5
-10^5 <= lower <= upper <= 10^5
```

<details><summary>Hint</summary>

```text
1. Fix the first element of the hidden sequence to any value x and ignore the given bounds.
   Notice that we can then determine all the other elements of the sequence by using the differences array.
2. We will also be able to determine the difference between the minimum and maximum elements of the sequence.
   Notice that the value of x does not affect this.
3. We now have the ‘range’ of the sequence (difference between min and max element),
   we can then calculate how many ways there are to fit this range into the given range of lower to upper.
4. Answer is (upper - lower + 1) - (range of sequence)
```

</details>

</details>

<details><summary>C</summary>

```c
int numberOfArrays(int* differences, int differencesSize, int lower, int upper) {
    int retVal = 0;

    int minValue = 0;
    int maxValue = 0;
    int currentSum = 0;
    for (int i = 0; i < differencesSize; i++) {
        currentSum += differences[i];
        minValue = fmin(minValue, currentSum);
        maxValue = fmax(maxValue, currentSum);
        if ((maxValue - minValue) > (upper - lower)) {
            return retVal;
        }
    }
    retVal = (upper - lower) - (maxValue - minValue) + 1;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int numberOfArrays(vector<int>& differences, int lower, int upper) {
        int retVal = 0;

        int minValue = 0;
        int maxValue = 0;
        int currentSum = 0;
        for (int difference : differences) {
            currentSum += difference;
            minValue = min(minValue, currentSum);
            maxValue = max(maxValue, currentSum);
            if ((maxValue - minValue) > (upper - lower)) {
                return retVal;
            }
        }
        retVal = (upper - lower) - (maxValue - minValue) + 1;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def numberOfArrays(self, differences: List[int], lower: int, upper: int) -> int:
        retVal = 0

        minValue = 0
        maxValue = 0
        currentSum = 0
        for difference in differences:
            currentSum += difference
            minValue = min(minValue, currentSum)
            maxValue = max(maxValue, currentSum)
            if (maxValue - minValue) > (upper - lower):
                return retVal
        retVal = (upper - lower) - (maxValue - minValue) + 1

        return retVal
```

</details>

## [2176. Count Equal and Divisible Pairs in an Array](https://leetcode.com/problems/count-equal-and-divisible-pairs-in-an-array/)  1215

- [Official](https://leetcode.com/problems/count-equal-and-divisible-pairs-in-an-array/editorial/)
- [Official](https://leetcode.cn/problems/count-equal-and-divisible-pairs-in-an-array/solutions/1300992/tong-ji-shu-zu-zhong-xiang-deng-qie-ke-y-tc4p/)

<details><summary>Description</summary>

```text
Given a 0-indexed integer array nums of length n and an integer k,
return the number of pairs (i, j) where 0 <= i < j < n, such that nums[i] == nums[j] and (i * j) is divisible by k.

Example 1:
Input: nums = [3,1,2,2,2,1,3], k = 2
Output: 4
Explanation:
There are 4 pairs that meet all the requirements:
- nums[0] == nums[6], and 0 * 6 == 0, which is divisible by 2.
- nums[2] == nums[3], and 2 * 3 == 6, which is divisible by 2.
- nums[2] == nums[4], and 2 * 4 == 8, which is divisible by 2.
- nums[3] == nums[4], and 3 * 4 == 12, which is divisible by 2.

Example 2:
Input: nums = [1,2,3,4], k = 1
Output: 0
Explanation: Since no value in nums is repeated, there are no pairs (i,j) that meet all the requirements.

Constraints:
1 <= nums.length <= 100
1 <= nums[i], k <= 100
```

<details><summary>Hint</summary>

```text
1. For every possible pair of indices (i, j) where i < j, check if it satisfies the given conditions.
```

</details>

</details>

<details><summary>C</summary>

```c
int countPairs(int* nums, int numsSize, int k) {
    int retVal = 0;

    for (int i = 0; i < numsSize - 1; ++i) {
        for (int j = i + 1; j < numsSize; ++j) {
            if ((nums[i] == nums[j]) && ((i * j) % k == 0)) {
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
    int countPairs(vector<int>& nums, int k) {
        int retVal = 0;

        int numsSize = nums.size();
        for (int i = 0; i < numsSize - 1; ++i) {
            for (int j = i + 1; j < numsSize; ++j) {
                if ((nums[i] == nums[j]) && ((i * j) % k == 0)) {
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
    def countPairs(self, nums: List[int], k: int) -> int:
        retVal = 0

        numsSize = len(nums)
        for i in range(numsSize-1):
            for j in range(i+1, numsSize):
                if (nums[i] == nums[j]) and ((i * j) % k == 0):
                    retVal += 1

        return retVal
```

</details>

## [2210. Count Hills and Valleys in an Array](https://leetcode.com/problems/count-hills-and-valleys-in-an-array/)  1354

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array nums.
An index i is part of a hill in nums if the closest non-equal neighbors of i are smaller than nums[i].
Similarly, an index i is part of a valley in nums if the closest non-equal neighbors of i are larger than nums[i].
Adjacent indices i and j are part of the same hill or valley if nums[i] == nums[j].

Note that for an index to be part of a hill or valley,
it must have a non-equal neighbor on both the left and right of the index.

Return the number of hills and valleys in nums.

Example 1:
Input: nums = [2,4,1,1,6,5]
Output: 3
Explanation:
At index 0: There is no non-equal neighbor of 2 on the left, so index 0 is neither a hill nor a valley.
At index 1: The closest non-equal neighbors of 4 are 2 and 1. Since 4 > 2 and 4 > 1, index 1 is a hill.
At index 2: The closest non-equal neighbors of 1 are 4 and 6. Since 1 < 4 and 1 < 6, index 2 is a valley.
At index 3: The closest non-equal neighbors of 1 are 4 and 6. Since 1 < 4 and 1 < 6,
index 3 is a valley, but note that it is part of the same valley as index 2.
At index 4: The closest non-equal neighbors of 6 are 1 and 5. Since 6 > 1 and 6 > 5, index 4 is a hill.
At index 5: There is no non-equal neighbor of 5 on the right, so index 5 is neither a hill nor a valley.
There are 3 hills and valleys so we return 3.

Example 2:
Input: nums = [6,6,5,5,4,1]
Output: 0
Explanation:
At index 0: There is no non-equal neighbor of 6 on the left, so index 0 is neither a hill nor a valley.
At index 1: There is no non-equal neighbor of 6 on the left, so index 1 is neither a hill nor a valley.
At index 2: The closest non-equal neighbors of 5 are 6 and 4. Since 5 < 6 and 5 > 4,
index 2 is neither a hill nor a valley.
At index 3: The closest non-equal neighbors of 5 are 6 and 4. Since 5 < 6 and 5 > 4,
index 3 is neither a hill nor a valley.
At index 4: The closest non-equal neighbors of 4 are 5 and 1. Since 4 < 5 and 4 > 1,
index 4 is neither a hill nor a valley.
At index 5: There is no non-equal neighbor of 1 on the right, so index 5 is neither a hill nor a valley.
There are 0 hills and valleys so we return 0.

Constraints:
3 <= nums.length <= 100
1 <= nums[i] <= 100
```

<details><summary>Hint</summary>

```text
1. For each index, could you find the closest non-equal neighbors?
2. Ensure that adjacent indices that are part of the same hill or valley are not double-counted.
```

</details>

</details>

<details><summary>C</summary>

```c
int countHillValley(int* nums, int numsSize) {
    int retVal = 0;

    /* Example: Input: nums = [2,4,1,1,6,5]
     *  2   4   1   1   6   5
     *    2  -3   0   5  -1
     */
    int diff = 0;
    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[i] > nums[i - 1]) {
            if (diff == -1) {
                ++retVal;
            }
            diff = 1;
        } else if (nums[i] < nums[i - 1]) {
            if (diff == 1) {
                ++retVal;
            }
            diff = -1;
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
    int countHillValley(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        /* Example: Input: nums = [2,4,1,1,6,5]
         *  2   4   1   1   6   5
         *    2  -3   0   5  -1
         */
        int diff = 0;
        for (int i = 1; i < numsSize; ++i) {
            if (nums[i] > nums[i - 1]) {
                if (diff == -1) {
                    ++retVal;
                }
                diff = 1;
            } else if (nums[i] < nums[i - 1]) {
                if (diff == 1) {
                    ++retVal;
                }
                diff = -1;
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
    def countHillValley(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        # /* Example: Input: nums = [2,4,1,1,6,5]
        #  *  2   4   1   1   6   5
        #  *    2  -3   0   5  -1
        #  */
        diff = 0
        for i in range(1, numsSize):
            if nums[i] > nums[i-1]:
                if diff == -1:
                    retVal += 1
                diff = 1
            elif nums[i] < nums[i-1]:
                if diff == 1:
                    retVal += 1
                diff = -1

        return retVal
```

</details>

## [2257. Count Unguarded Cells in the Grid](https://leetcode.com/problems/count-unguarded-cells-in-the-grid/)  1708

- [Official](https://leetcode.com/problems/count-unguarded-cells-in-the-grid/editorial/)
- [Official](https://leetcode.cn/problems/count-unguarded-cells-in-the-grid/solutions/1486086/tong-ji-wang-ge-tu-zhong-mei-you-bei-bao-ba6m/)

<details><summary>Description</summary>

```text
You are given two integers m and n representing a 0-indexed m x n grid.
You are also given two 2D integer arrays guards and walls where guards[i] = [rowi, coli] and walls[j] = [rowj, colj]
represent the positions of the ith guard and jth wall respectively.

A guard can see every cell in the four cardinal directions (north, east, south, or west)
starting from their position unless obstructed by a wall or another guard.
A cell is guarded if there is at least one guard that can see it.

Return the number of unoccupied cells that are not guarded.

Example 1:
Input: m = 4, n = 6, guards = [[0,0],[1,1],[2,3]], walls = [[0,1],[2,2],[1,4]]
Output: 7
Explanation: The guarded and unguarded cells are shown in red and green respectively in the above diagram.
There are a total of 7 unguarded cells, so we return 7.

Example 2:
Input: m = 3, n = 3, guards = [[1,1]], walls = [[0,1],[1,0],[2,1],[1,2]]
Output: 4
Explanation: The unguarded cells are shown in green in the above diagram.
There are a total of 4 unguarded cells, so we return 4.

Constraints:
1 <= m, n <= 10^5
2 <= m * n <= 10^5
1 <= guards.length, walls.length <= 5 * 10^4
2 <= guards.length + walls.length <= m * n
guards[i].length == walls[j].length == 2
0 <= rowi, rowj < m
0 <= coli, colj < n
All the positions in guards and walls are unique.
```

<details><summary>Hint</summary>

```text
1. Create a 2D array to represent the grid. Can you mark the tiles that can be seen by a guard?
2. Iterate over the guards, and for each of the 4 directions, advance the current tile and mark the tile.
   When should you stop advancing?
```

</details>

</details>

<details><summary>C</summary>

```c
void markUnguarded(int row, int col, int** grid, int gridSize, int gridColSize) {
    int x;
    for (x = row - 1; x >= 0; x--) {
        if ((grid[x][col] == 3) || (grid[x][col] == 2)) {
            break;
        }
        grid[x][col] = 1;
    }
    for (x = row + 1; x < gridSize; x++) {
        if ((grid[x][col] == 3) || (grid[x][col] == 2)) {
            break;
        }
        grid[x][col] = 1;
    }

    int y;
    for (y = col - 1; y >= 0; y--) {
        if ((grid[row][y] == 3) || (grid[row][y] == 2)) {
            break;
        }
        grid[row][y] = 1;
    }
    for (y = col + 1; y < gridColSize; y++) {
        if ((grid[row][y] == 3) || (grid[row][y] == 2)) {
            break;
        }
        grid[row][y] = 1;
    }
}
int countUnguarded(int m, int n, int** guards, int guardsSize, int* guardsColSize, int** walls, int wallsSize,
                   int* wallsColSize) {
    int retVal = 0;

    int i, j;

    int** pGrid = (int**)malloc(m * sizeof(int*));
    if (pGrid == NULL) {
        perror("malloc");
        return retVal;
    }
    memset(pGrid, 0, (m * sizeof(int*)));
    for (i = 0; i < m; ++i) {
        pGrid[i] = (int*)malloc(n * sizeof(int));
        if (pGrid[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++i) {
                free(pGrid[j]);
                pGrid[j] = NULL;
            }
            free(pGrid);
            pGrid = NULL;
            return retVal;
        }
        memset(pGrid[i], 0, (n * sizeof(int)));
    }

    for (i = 0; i < guardsSize; ++i) {
        pGrid[guards[i][0]][guards[i][1]] = 2;
    }
    for (i = 0; i < wallsSize; ++i) {
        pGrid[walls[i][0]][walls[i][1]] = 3;
    }

    for (i = 0; i < guardsSize; ++i) {
        markUnguarded(guards[i][0], guards[i][1], pGrid, m, n);
    }

    for (i = 0; i < m; ++i) {
        for (j = 0; j < n; ++j) {
            if (pGrid[i][j] == 0) {
                retVal++;
            }
        }
    }

    //
    for (i = 0; i < m; ++i) {
        free(pGrid[i]);
        pGrid[i] = NULL;
    }
    free(pGrid);
    pGrid = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    void markUnguarded(int row, int col, vector<vector<int>>& grid) {
        int gridSize = grid.size();
        for (int x = row - 1; x >= 0; x--) {
            if ((grid[x][col] == 3) || (grid[x][col] == 2)) {
                break;
            }
            grid[x][col] = 1;
        }
        for (int x = row + 1; x < gridSize; x++) {
            if ((grid[x][col] == 3) || (grid[x][col] == 2)) {
                break;
            }
            grid[x][col] = 1;
        }

        int gridColSize = grid[row].size();
        for (int y = col - 1; y >= 0; y--) {
            if ((grid[row][y] == 3) || (grid[row][y] == 2)) {
                break;
            }
            grid[row][y] = 1;
        }
        for (int y = col + 1; y < gridColSize; y++) {
            if ((grid[row][y] == 3) || (grid[row][y] == 2)) {
                break;
            }
            grid[row][y] = 1;
        }
    }
    int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
        int retVal = 0;

        vector<vector<int>> grid(m, vector<int>(n, 0));
        for (const auto& guard : guards) {
            grid[guard[0]][guard[1]] = 2;
        }
        for (const auto& wall : walls) {
            grid[wall[0]][wall[1]] = 3;
        }

        for (const auto& guard : guards) {
            markUnguarded(guard[0], guard[1], grid);
        }

        for (const auto& row : grid) {
            for (const auto& cell : row) {
                if (cell == 0) {
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
    def markUnguarded(self, row: int, col: int, grid: List[List[int]]) -> None:
        gridSize = len(grid)
        for x in range(row - 1, -1, -1):
            if (grid[x][col] == 3) or (grid[x][col] == 2):
                break
            grid[x][col] = 1
        for x in range(row + 1, gridSize):
            if (grid[x][col] == 3) or (grid[x][col] == 2):
                break
            grid[x][col] = 1

        gridColSize = len(grid[0])
        for y in range(col - 1, -1, -1):
            if (grid[row][y] == 3) or (grid[row][y] == 2):
                break
            grid[row][y] = 1
        for y in range(col + 1, gridColSize):
            if (grid[row][y] == 3) or (grid[row][y] == 2):
                break
            grid[row][y] = 1

    def countUnguarded(self, m: int, n: int, guards: List[List[int]], walls: List[List[int]]) -> int:
        retVal = 0

        grid = [[0] * n for _ in range(m)]
        for guard in guards:
            grid[guard[0]][guard[1]] = 2
        for wall in walls:
            grid[wall[0]][wall[1]] = 3

        for guard in guards:
            self.markUnguarded(guard[0], guard[1], grid)

        for row in grid:
            for cell in row:
                if cell == 0:
                    retVal += 1

        return retVal
```

</details>

## [2273. Find Resultant Array After Removing Anagrams](https://leetcode.com/problems/find-resultant-array-after-removing-anagrams/)  1294

<details><summary>Description</summary>

```text
You are given a 0-indexed string array words, where words[i] consists of lowercase English letters.

In one operation, select any index i such that 0 < i < words.length
and words[i - 1] and words[i] are anagrams, and delete words[i] from words.
Keep performing this operation as long as you can select an index that satisfies the conditions.

Return words after performing all operations.
It can be shown that selecting the indices for each operation in any arbitrary order will lead to the same result.

An Anagram is a word or phrase formed by rearranging the letters of a different word or
phrase using all the original letters exactly once.
For example, "dacb" is an anagram of "abdc".

Example 1:
Input: words = ["abba","baba","bbaa","cd","cd"]
Output: ["abba","cd"]
Explanation:
One of the ways we can obtain the resultant array is by using the following operations:
- Since words[2] = "bbaa" and words[1] = "baba" are anagrams, we choose index 2 and delete words[2].
  Now words = ["abba","baba","cd","cd"].
- Since words[1] = "baba" and words[0] = "abba" are anagrams, we choose index 1 and delete words[1].
  Now words = ["abba","cd","cd"].
- Since words[2] = "cd" and words[1] = "cd" are anagrams, we choose index 2 and delete words[2].
  Now words = ["abba","cd"].
We can no longer perform any operations, so ["abba","cd"] is the final answer.

Example 2:
Input: words = ["a","b","c","d","e"]
Output: ["a","b","c","d","e"]
Explanation:
No two adjacent strings in words are anagrams of each other, so no operations are performed.

Constraints:
1 <= words.length <= 100
1 <= words[i].length <= 10
words[i] consists of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Instead of removing each repeating anagram,
   try to find all the strings in words which will not be present in the final answer.
2. For every index i, find the largest index j < i such that words[j] will be present in the final answer.
3. Check if words[i] and words[j] are anagrams.
   If they are, then it can be confirmed that words[i] will not be present in the final answer.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MAX_LENGTH (100 + 4)
int compareChar(const void* c1, const void* c2) {
    // ascending order
    return (*(char*)c1 - *(char*)c2);
}
bool isAnagrams(char* pSrc, char* pDst) {
    int retVal = false;

    char sortSrc[MAX_LENGTH];
    memset(sortSrc, 0, sizeof(sortSrc));
    snprintf(sortSrc, sizeof(sortSrc), "%s", pSrc);
    qsort(sortSrc, strlen(sortSrc), sizeof(char), compareChar);

    char sortDst[MAX_LENGTH];
    memset(sortDst, 0, sizeof(sortDst));
    snprintf(sortDst, sizeof(sortDst), "%s", pDst);
    qsort(sortDst, strlen(sortDst), sizeof(char), compareChar);

    if (strcmp(sortSrc, sortDst) == 0) {
        retVal = true;
    }

    return retVal;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** removeAnagrams(char** words, int wordsSize, int* returnSize) {
    (*returnSize) = 1;

    int len;
    int i;
    for (i = 1; i < wordsSize; ++i) {
        if (isAnagrams(words[(*returnSize) - 1], words[i]) == true) {
            continue;
        }

        if ((*returnSize) != i) {
            free(words[(*returnSize)]);
            words[(*returnSize)] = NULL;

            len = strlen(words[i]) + 1;
            words[(*returnSize)] = (char*)malloc(len * sizeof(char));
            if (words[(*returnSize)] == NULL) {
                perror("malloc");
                return words;
            }
            memset(words[(*returnSize)], 0, len * sizeof(char));
            snprintf(words[(*returnSize)], len * sizeof(char), "%s", words[i]);
        }

        (*returnSize)++;
    }

    return words;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<string> removeAnagrams(vector<string>& words) {
        vector<string> retVal;

        int idx = 0;
        retVal.push_back(words[0]);

        int len = words.size();
        for (int i = 1; i < len; ++i) {
            string ret = retVal[idx];
            string ori = words[i];
            sort(ret.begin(), ret.end());
            sort(ori.begin(), ori.end());
            if (ret.compare(ori) == 0) {
                continue;
            }

            ++idx;
            retVal.push_back(words[i]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def removeAnagrams(self, words: List[str]) -> List[str]:
        retVal = []

        for s in words:
            if not retVal:
                retVal.append(s)
                compare = s
                continue

            if sorted(s) == sorted(compare):
                continue

            retVal.append(s)
            compare = s

        return retVal
```

</details>

## [2293. Min Max Game](https://leetcode.com/problems/min-max-game/)  1241

- [Official](https://leetcode.cn/problems/min-max-game/solutions/2061544/ji-da-ji-xiao-you-xi-by-leetcode-solutio-ucpt/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array nums whose length is a power of 2.

Apply the following algorithm on nums:
Let n be the length of nums. If n == 1, end the process. Otherwise, create a new 0-indexed integer array newNums of length n / 2.
For every even index i where 0 <= i < n / 2, assign the value of newNums[i] as min(nums[2 * i], nums[2 * i + 1]).
For every odd index i where 0 <= i < n / 2, assign the value of newNums[i] as max(nums[2 * i], nums[2 * i + 1]).
Replace the array nums with newNums.
Repeat the entire process starting from step 1.
Return the last number that remains in nums after applying the algorithm.

Example 1:
Input: nums = [1,3,5,2,4,8,2,2]
Output: 1
Explanation: The following arrays are the results of applying the algorithm repeatedly.
First: nums = [1,5,4,2]
Second: nums = [1,4]
Third: nums = [1]
1 is the last remaining number, so we return 1.

Example 2:
Input: nums = [3]
Output: 3
Explanation: 3 is already the last remaining number, so we return 3.

Constraints:
1 <= nums.length <= 1024
1 <= nums[i] <= 10^9
nums.length is a power of 2.
```

</details>

<details><summary>C</summary>

```c
int minMaxGame(int* nums, int numsSize) {
    int retVal = 0;

    int i;
    while (numsSize != 1) {
        numsSize /= 2;
        for (i = 0; i < numsSize; ++i) {
            if (i % 2 == 0) {
                nums[i] = fmin(nums[2 * i], nums[2 * i + 1]);
            } else {
                nums[i] = fmax(nums[2 * i], nums[2 * i + 1]);
            }
        }
    }
    retVal = nums[0];

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minMaxGame(vector<int>& nums) {
        int retVal = 0;

        int len = nums.size();
        while (len != 1) {
            len /= 2;
            for (int i = 0; i < len; ++i) {
                if (i % 2 == 0) {
                    nums[i] = min(nums[2 * i], nums[2 * i + 1]);
                } else {
                    nums[i] = max(nums[2 * i], nums[2 * i + 1]);
                }
            }
        }
        retVal = nums[0];

        return retVal;
    }
};
```

</details>

## [2303. Calculate Amount Paid in Taxes](https://leetcode.com/problems/calculate-amount-paid-in-taxes/)  1283

- [Official](https://leetcode.cn/problems/calculate-amount-paid-in-taxes/solutions/2072838/ji-suan-ying-jiao-shui-kuan-zong-e-by-le-jv5s/)

<details><summary>Description</summary>

```text
You are given a 0-indexed 2D integer array brackets where brackets[i] = [upperi, percenti]
means that the ith tax bracket has an upper bound of upperi and is taxed at a rate of percenti.
The brackets are sorted by upper bound (i.e. upperi-1 < upperi for 0 < i < brackets.length).

Tax is calculated as follows:
- The first upper0 dollars earned are taxed at a rate of percent0.
- The next upper1 - upper0 dollars earned are taxed at a rate of percent1.
- The next upper2 - upper1 dollars earned are taxed at a rate of percent2.
- And so on.

You are given an integer income representing the amount of money you earned.
Return the amount of money that you have to pay in taxes. Answers within 10-5 of the actual answer will be accepted.

Example 1:
Input: brackets = [[3,50],[7,10],[12,25]], income = 10
Output: 2.65000
Explanation:
Based on your income, you have 3 dollars in the 1st tax bracket, 4 dollars in the 2nd tax bracket,
and 3 dollars in the 3rd tax bracket.
The tax rate for the three tax brackets is 50%, 10%, and 25%, respectively.
In total, you pay $3 * 50% + $4 * 10% + $3 * 25% = $2.65 in taxes.

Example 2:
Input: brackets = [[1,0],[4,25],[5,50]], income = 2
Output: 0.25000
Explanation:
Based on your income, you have 1 dollar in the 1st tax bracket and 1 dollar in the 2nd tax bracket.
The tax rate for the two tax brackets is 0% and 25%, respectively.
In total, you pay $1 * 0% + $1 * 25% = $0.25 in taxes.

Example 3:
Input: brackets = [[2,50]], income = 0
Output: 0.00000
Explanation:
You have no income to tax, so you have to pay a total of $0 in taxes.

Constraints:
1 <= brackets.length <= 100
1 <= upperi <= 1000
0 <= percenti <= 100
0 <= income <= 1000
upperi is sorted in ascending order.
All the values of upperi are unique.
The upper bound of the last tax bracket is greater than or equal to income.
```

</details>

<details><summary>C</summary>

```c
double calculateTax(int** brackets, int bracketsSize, int* bracketsColSize, int income) {
    double retVal = 0;

    int lower = 0;
    int upper;
    int percent;
    int i;
    for (i = 0; i < bracketsSize; ++i) {
        upper = brackets[i][0];
        percent = brackets[i][1];
        retVal += ((double)((fmin(income, upper) - lower) * percent) / 100);
        lower = upper;

        if (income < brackets[i][0]) {
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
    double calculateTax(vector<vector<int>>& brackets, int income) {
        double retVal = 0;

        int lower = 0;
        int upper;
        int percent;
        for (long unsigned int i = 0; i < brackets.size(); ++i) {
            upper = brackets[i][0];
            percent = brackets[i][1];
            retVal += ((double)((min(income, upper) - lower) * percent) / 100);
            lower = upper;

            if (income < upper) {
                break;
            }
        }

        return retVal;
    }
};
```

</details>

## [2319. Check if Matrix Is X-Matrix](https://leetcode.com/problems/check-if-matrix-is-x-matrix/)  1200

- [Official](https://leetcode.cn/problems/check-if-matrix-is-x-matrix/solutions/2079502/pan-duan-ju-zhen-shi-fou-shi-yi-ge-x-ju-aloq7/)

<details><summary>Description</summary>

```text
A square matrix is said to be an X-Matrix if both of the following conditions hold:

All the elements in the diagonals of the matrix are non-zero.
All other elements are 0.
Given a 2D integer array grid of size n x n representing a square matrix, return true if grid is an X-Matrix.
Otherwise, return false.

Example 1:
Input: grid = [[2,0,0,1],[0,3,1,0],[0,5,2,0],[4,0,0,2]]
Output: true
Explanation: Refer to the diagram above.
An X-Matrix should have the green elements (diagonals) be non-zero and the red elements be 0.
Thus, grid is an X-Matrix.

Example 2:
Input: grid = [[5,7,0],[0,3,1],[0,5,0]]
Output: false
Explanation: Refer to the diagram above.
An X-Matrix should have the green elements (diagonals) be non-zero and the red elements be 0.
Thus, grid is not an X-Matrix.

Constraints:
n == grid.length == grid[i].length
3 <= n <= 100
0 <= grid[i][j] <= 10^5
```

</details>

<details><summary>C</summary>

```c
bool checkXMatrix(int** grid, int gridSize, int* gridColSize) {
    bool retVal = false;

    int i, j;
    for (i = 0; i < gridSize; ++i) {
        for (j = 0; j < gridColSize[i]; ++j) {
            if ((j == i) || (j == gridColSize[i] - 1 - i)) {
                if (grid[i][j] == 0) {
                    return retVal;
                }
            } else {
                if (grid[i][j] != 0) {
                    return retVal;
                }
            }
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
    bool checkXMatrix(vector<vector<int>>& grid) {
        bool retVal = false;

        for (long unsigned int i = 0; i < grid.size(); ++i) {
            for (long unsigned int j = 0; j < grid[i].size(); ++j) {
                if ((j == i) || (j == grid[i].size() - 1 - i)) {
                    if (grid[i][j] == 0) {
                        return retVal;
                    }
                } else {
                    if (grid[i][j] != 0) {
                        return retVal;
                    }
                }
            }
        }
        retVal = true;

        return retVal;
    }
};
```

</details>

<details><summary>Rust</summary>

```rust
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
```

</details>

## [2326. Spiral Matrix IV](https://leetcode.com/problems/spiral-matrix-iv/)  1421

- [Official](https://leetcode.com/problems/spiral-matrix-iv/editorial/)

<details><summary>Description</summary>

```text
You are given two integers m and n, which represent the dimensions of a matrix.

You are also given the head of a linked list of integers.

Generate an m x n matrix that contains the integers in the linked list presented in spiral order (clockwise),
starting from the top-left of the matrix. If there are remaining empty spaces, fill them with -1.

Return the generated matrix.

Example 1:
Input: m = 3, n = 5, head = [3,0,2,6,8,1,7,9,4,2,5,5,0]
Output: [[3,0,2,6,8],[5,0,-1,-1,1],[5,2,4,9,7]]
Explanation: The diagram above shows how the values are printed in the matrix.
Note that the remaining spaces in the matrix are filled with -1.

Example 2:
Input: m = 1, n = 4, head = [0,1,2]
Output: [[0,1,2,-1]]
Explanation: The diagram above shows how the values are printed from left to right in the matrix.
The last space in the matrix is set to -1.

Constraints:
1 <= m, n <= 10^5
1 <= m * n <= 10^5
The number of nodes in the list is in the range [1, m * n].
0 <= Node.val <= 1000
```

<details><summary>Hint</summary>

```text
1. First, generate an m x n matrix filled with -1s.
2. Navigate within the matrix at (i, j) with the help of a direction vector ⟨di, dj⟩. At (i, j),
   you need to decide if you can keep going in the current direction.
3. If you cannot keep going, rotate the direction vector clockwise by 90 degrees.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** spiralMatrix(int m, int n, struct ListNode* head, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    int i, j;

    (*returnColumnSizes) = (int*)malloc(m * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, (m * sizeof(int)));
    pRetVal = (int**)malloc(m * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }
    for (i = 0; i < m; ++i) {
        pRetVal[i] = (int*)malloc(n * sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            for (j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        memset(pRetVal[i], -1, (n * sizeof(int)));
        (*returnColumnSizes)[i] = n;
    }
    (*returnSize) = m;

    int movement[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int movementIndex = 0;
    int x = 0;
    int y = 0;
    struct ListNode* pCurrent = head;
    while (pCurrent != NULL) {
        pRetVal[x][y] = pCurrent->val;

        x += movement[movementIndex][0];
        y += movement[movementIndex][1];
        // 0 <= Node.val <= 1000
        if ((x < 0) || (y < 0) || (x >= m) || (y >= n) || (pRetVal[x][y] != -1)) {
            x -= movement[movementIndex][0];
            y -= movement[movementIndex][1];
            movementIndex = (movementIndex + 1) % 4;
            x += movement[movementIndex][0];
            y += movement[movementIndex][1];
        }

        pCurrent = pCurrent->next;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
   public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
        vector<vector<int>> retVal(m, vector<int>(n, -1));

        vector<vector<int>> movement = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        int movementIndex = 0;
        int x = 0;
        int y = 0;
        ListNode* pCurrent = head;
        while (pCurrent != nullptr) {
            retVal[x][y] = pCurrent->val;

            x += movement[movementIndex][0];
            y += movement[movementIndex][1];
            // 0 <= Node.val <= 1000
            if ((x < 0) || (y < 0) || (x >= m) || (y >= n) || (retVal[x][y] != -1)) {
                x -= movement[movementIndex][0];
                y -= movement[movementIndex][1];
                movementIndex = (movementIndex + 1) % 4;
                x += movement[movementIndex][0];
                y += movement[movementIndex][1];
            }

            pCurrent = pCurrent->next;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def spiralMatrix(self, m: int, n: int, head: Optional[ListNode]) -> List[List[int]]:
        retVal = [[-1] * n for _ in range(m)]

        movement = [[0, 1], [1, 0], [0, -1], [-1, 0]]
        movementIndex = 0
        x = 0
        y = 0
        pCurrent = head
        while pCurrent != None:
            retVal[x][y] = pCurrent.val

            x += movement[movementIndex][0]
            y += movement[movementIndex][1]
            # 0 <= Node.val <= 1000
            if (x < 0) or (y < 0) or (x >= m) or (y >= n) or (retVal[x][y] != -1):
                x -= movement[movementIndex][0]
                y -= movement[movementIndex][1]
                movementIndex = (movementIndex + 1) % 4
                x += movement[movementIndex][0]
                y += movement[movementIndex][1]

            pCurrent = pCurrent.next

        return retVal
```

</details>

## [2348. Number of Zero-Filled Subarrays](https://leetcode.com/problems/number-of-zero-filled-subarrays/)  1315

<details><summary>Description</summary>

```text
Given an integer array nums, return the number of subarrays filled with 0.

A subarray is a contiguous non-empty sequence of elements within an array.

Example 1:
Input: nums = [1,3,0,0,2,0,0,4]
Output: 6
Explanation:
There are 4 occurrences of [0] as a subarray.
There are 2 occurrences of [0,0] as a subarray.
There is no occurrence of a subarray with a size more than 2 filled with 0. Therefore, we return 6.

Example 2:
Input: nums = [0,0,0,2,0,0]
Output: 9
Explanation:
There are 5 occurrences of [0] as a subarray.
There are 3 occurrences of [0,0] as a subarray.
There is 1 occurrence of [0,0,0] as a subarray.
There is no occurrence of a subarray with a size more than 3 filled with 0. Therefore, we return 9.

Example 3:
Input: nums = [2,10,2019]
Output: 0
Explanation: There is no subarray filled with 0. Therefore, we return 0.

Constraints:
1 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. For each zero, you can calculate the number of zero-filled subarrays that end on that index,
   which is the number of consecutive zeros behind the current element + 1.
2. Maintain the number of consecutive zeros behind the current element,
   count the number of zero-filled subarrays that end on each index, sum it up to get the answer.
```

</details>

</details>

<details><summary>C</summary>

```c
long long zeroFilledSubarray(int *nums, int numsSize) {
    long long retVal = 0;

    int contiguous = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] != 0) {
            contiguous = 0;
            continue;
        }

        ++contiguous;
        retVal += contiguous;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long zeroFilledSubarray(vector<int>& nums) {
        long long retVal = 0;

        int contiguous = 0;
        for (auto num : nums) {
            if (num != 0) {
                contiguous = 0;
                continue;
            }

            ++contiguous;
            retVal += contiguous;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def zeroFilledSubarray(self, nums: List[int]) -> int:
        retVal = 0

        contiguous = 0
        for num in nums:
            if num != 0:
                contiguous = 0
                continue

            contiguous += 1
            retVal += contiguous

        return retVal
```

</details>

## [2352. Equal Row and Column Pairs](https://leetcode.com/problems/equal-row-and-column-pairs/)  1286

- [Official](https://leetcode.cn/problems/equal-row-and-column-pairs/solutions/2293933/xiang-deng-xing-lie-dui-by-leetcode-solu-gvcg/)

<details><summary>Description</summary>

```text
Given a 0-indexed n x n integer matrix grid, return the number of pairs (ri, cj) such that row ri and column cj are equal.

A row and column pair is considered equal if they contain the same elements in the same order (i.e., an equal array).

Example 1:
Input: grid = [[3,2,1],[1,7,6],[2,7,7]]
Output: 1
Explanation: There is 1 equal row and column pair:
- (Row 2, Column 1): [2,7,7]

Example 2:
Input: grid = [[3,1,2,2],[1,4,4,5],[2,4,2,2],[2,4,2,2]]
Output: 3
Explanation: There are 3 equal row and column pairs:
- (Row 0, Column 0): [3,1,2,2]
- (Row 2, Column 2): [2,4,2,2]
- (Row 3, Column 2): [2,4,2,2]

Constraints:
n == grid.length == grid[i].length
1 <= n <= 200
1 <= grid[i][j] <= 10^5
```

<details><summary>Hint</summary>

```text
1. We can use nested loops to compare every row against every column.
2. Another loop is necessary to compare the row and column element by element.
3. It is also possible to hash the arrays and compare the hashed values instead.
```

</details>

</details>

<details><summary>C</summary>

```c
int equalPairs(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    bool match = true;
    int idx;
    int row, col;
    for (row = 0; row < gridSize; ++row) {
        for (col = 0; col < gridSize; ++col) {
            match = true;

            for (idx = 0; idx < gridSize; ++idx) {
                if (grid[row][idx] != grid[idx][col]) {
                    match = false;
                    break;
                }
            }

            if (match == true) {
                ++retVal;
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
    int equalPairs(vector<vector<int>>& grid) {
        int retVal = 0;

        int gridSize = grid.size();
        for (int row = 0; row < gridSize; ++row) {
            for (int col = 0; col < gridSize; ++col) {
                bool match = true;

                for (int idx = 0; idx < gridSize; ++idx) {
                    if (grid[row][idx] != grid[idx][col]) {
                        match = false;
                        break;
                    }
                }

                if (match == true) {
                    ++retVal;
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
    def equalPairs(self, grid: List[List[int]]) -> int:
        retVal = 0

        gridSize = len(grid)
        for row in range(gridSize):
            for col in range(gridSize):
                match = True

                for idx in range(gridSize):
                    if grid[row][idx] != grid[idx][col]:
                        match = False
                        break

                if match == True:
                    retVal += 1

        return retVal
```

</details>

## [2373. Largest Local Values in a Matrix](https://leetcode.com/problems/largest-local-values-in-a-matrix/)  1331

- [Official](https://leetcode.com/problems/largest-local-values-in-a-matrix/editorial/)
- [Official](https://leetcode.cn/problems/largest-local-values-in-a-matrix/solutions/2138032/ju-zhen-zhong-de-ju-bu-zui-da-zhi-by-lee-o703/)

<details><summary>Description</summary>

```text
You are given an n x n integer matrix grid.

Generate an integer matrix maxLocal of size (n - 2) x (n - 2) such that:
- maxLocal[i][j] is equal to the largest value of the 3 x 3 matrix in grid centered around row i + 1 and column j + 1.

In other words, we want to find the largest value in every contiguous 3 x 3 matrix in grid.

Return the generated matrix.

Example 1:
Input: grid = [[9,9,8,1],[5,6,2,6],[8,2,6,4],[6,2,2,2]]
Output: [[9,9],[8,6]]
Explanation: The diagram above shows the original matrix and the generated matrix.
Notice that each value in the generated matrix corresponds to the largest value of a contiguous 3 x 3 matrix in grid.

Example 2:
Input: grid = [[1,1,1,1,1],[1,1,1,1,1],[1,1,2,1,1],[1,1,1,1,1],[1,1,1,1,1]]
Output: [[2,2,2],[2,2,2],[2,2,2]]
Explanation: Notice that the 2 is contained within every contiguous 3 x 3 matrix in grid.

Constraints:
n == grid.length == grid[i].length
3 <= n <= 100
1 <= grid[i][j] <= 100
```

<details><summary>Hint</summary>

```text
1. Use nested loops to run through all possible 3 x 3 windows in the matrix.
2. For each 3 x 3 window, iterate through the values to get the maximum value within the window.
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
int** largestLocal(int** grid, int gridSize, int* gridColSize, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    // malloc return value
    (*returnSize) = gridSize - 2;
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, ((*returnSize) * sizeof(int)));
    pRetVal = (int**)malloc((*returnSize) * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        (*returnSize) = 0;
        return pRetVal;
    }

    int i, j;
    int x, y;
    for (i = 0; i < (*returnSize); ++i) {
        pRetVal[i] = (int*)malloc((*returnSize) * sizeof(int));
        (*returnColumnSizes)[i] = (*returnSize);
        if (pRetVal[i] == NULL) {
            perror("malloc");
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            for (j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            (*returnSize) = 0;
            return pRetVal;
        }
        memset(pRetVal[i], 0, ((*returnSize) * sizeof(int)));
        for (j = 0; j < (*returnSize); ++j) {
            for (x = i; x <= i + 2; ++x) {
                for (y = j; y <= j + 2; ++y) {
                    pRetVal[i][j] = fmax(pRetVal[i][j], grid[x][y]);
                }
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
    vector<vector<int>> largestLocal(vector<vector<int>>& grid) {
        int row = grid.size();
        int col = grid[0].size();
        vector<vector<int>> retVal(row - 2, vector<int>(col - 2));  // 1 <= grid[i][j] <= 100

        for (int i = 0; i < row - 2; ++i) {
            for (int j = 0; j < col - 2; ++j) {
                for (int x = i; x <= i + 2; ++x) {
                    for (int y = j; y <= j + 2; ++y) {
                        retVal[i][j] = max(retVal[i][j], grid[x][y]);
                    }
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
    def largestLocal(self, grid: List[List[int]]) -> List[List[int]]:
        retVal = None

        rowSize = len(grid)
        colSize = len(grid[0])
        retVal = [[0 for _ in range(colSize-2)] for _ in range(rowSize-2)]
        for row in range(rowSize-2):
            for col in range(colSize-2):
                for x in range(row, row+3):
                    for y in range(col, col+3):
                        retVal[row][col] = max(retVal[row][col], grid[x][y])

        return retVal
```

</details>

## [2460. Apply Operations to an Array](https://leetcode.com/problems/apply-operations-to-an-array/)  1223

- [Official](https://leetcode.com/problems/apply-operations-to-an-array/editorial/)
- [Official](https://leetcode.cn/problems/apply-operations-to-an-array/solutions/2289491/dui-shu-zu-zhi-xing-cao-zuo-by-leetcode-vz70b/)

<details><summary>Description</summary>

```text
You are given a 0-indexed array nums of size n consisting of non-negative integers.

You need to apply n - 1 operations to this array where, in the ith operation (0-indexed),
you will apply the following on the ith element of nums:
- If nums[i] == nums[i + 1], then multiply nums[i] by 2 and set nums[i + 1] to 0. Otherwise, you skip this operation.

After performing all the operations, shift all the 0's to the end of the array.
- For example, the array [1,0,2,0,0,1] after shifting all its 0's to the end, is [1,2,1,0,0,0].

Return the resulting array.

Note that the operations are applied sequentially, not all at once.

Example 1:
Input: nums = [1,2,2,1,1,0]
Output: [1,4,2,0,0,0]
Explanation: We do the following operations:
- i = 0: nums[0] and nums[1] are not equal, so we skip this operation.
- i = 1: nums[1] and nums[2] are equal, we multiply nums[1] by 2 and change nums[2] to 0. The array becomes [1,4,0,1,1,0].
- i = 2: nums[2] and nums[3] are not equal, so we skip this operation.
- i = 3: nums[3] and nums[4] are equal, we multiply nums[3] by 2 and change nums[4] to 0. The array becomes [1,4,0,2,0,0].
- i = 4: nums[4] and nums[5] are equal, we multiply nums[4] by 2 and change nums[5] to 0. The array becomes [1,4,0,2,0,0].
After that, we shift the 0's to the end, which gives the array [1,4,2,0,0,0].

Example 2:
Input: nums = [0,1]
Output: [1,0]
Explanation: No operation can be applied, we just shift the 0 to the end.

Constraints:
2 <= nums.length <= 2000
0 <= nums[i] <= 1000
```

<details><summary>Hint</summary>

```text
1. Iterate over the array and simulate the described process.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* applyOperations(int* nums, int numsSize, int* returnSize) {
    int* pRetVal = NULL;

    int writeIndex = 0;  // Pointer to place non-zero elements
    for (int index = 0; index < numsSize; index++) {
        // Step 1: Merge adjacent equal elements if they are non-zero
        if ((index < numsSize - 1) && (nums[index] == nums[index + 1]) && (nums[index] != 0)) {
            nums[index] *= 2;
            nums[index + 1] = 0;
        }

        // Step 2: Shift non-zero elements to the front
        int tmp;
        if (nums[index] != 0) {
            if (index != writeIndex) {
                tmp = nums[index];
                nums[index] = nums[writeIndex];
                nums[writeIndex] = tmp;
            }
            writeIndex++;
        }
    }
    (*returnSize) = numsSize;
    pRetVal = nums;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> applyOperations(vector<int>& nums) {
        vector<int> retVal;

        int numsSize = nums.size();
        int writeIndex = 0;  // Pointer to place non-zero elements
        for (int index = 0; index < numsSize; index++) {
            // Step 1: Merge adjacent equal elements if they are non-zero
            if ((index < numsSize - 1) && (nums[index] == nums[index + 1]) && (nums[index] != 0)) {
                nums[index] *= 2;
                nums[index + 1] = 0;
            }

            // Step 2: Shift non-zero elements to the front
            if (nums[index] != 0) {
                if (index != writeIndex) {
                    swap(nums[index], nums[writeIndex]);
                }
                writeIndex++;
            }
        }
        retVal = nums;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def applyOperations(self, nums: List[int]) -> List[int]:
        retVal = nums

        numsSize = len(nums)
        writeIndex = 0  # Pointer to place non-zero elements
        for index in range(numsSize):
            # Step 1: Merge adjacent equal elements if they are non-zero
            if (index < numsSize - 1) and (nums[index] == nums[index + 1]) and (nums[index] != 0):
                nums[index] *= 2
                nums[index + 1] = 0

            # Step 2: Shift non-zero elements to the front
            if nums[index] != 0:
                if index != writeIndex:
                    nums[index], nums[writeIndex] = nums[writeIndex], nums[index]
                writeIndex += 1

        retVal = nums

        return retVal
```

</details>

## [2482. Difference Between Ones and Zeros in Row and Column](https://leetcode.com/problems/difference-between-ones-and-zeros-in-row-and-column/)  1372

- [Official](https://leetcode.com/problems/difference-between-ones-and-zeros-in-row-and-column/editorial/)

<details><summary>Description</summary>

```text
You are given a 0-indexed m x n binary matrix grid.

A 0-indexed m x n difference matrix diff is created with the following procedure:
- Let the number of ones in the ith row be onesRowi.
- Let the number of ones in the jth column be onesColj.
- Let the number of zeros in the ith row be zerosRowi.
- Let the number of zeros in the jth column be zerosColj.
- diff[i][j] = onesRowi + onesColj - zerosRowi - zerosColj

Return the difference matrix diff.

Example 1:
Input: grid = [[0,1,1],[1,0,1],[0,0,1]]
Output: [[0,0,4],[0,0,4],[-2,-2,2]]
Explanation:
- diff[0][0] = onesRow0 + onesCol0 - zerosRow0 - zerosCol0 = 2 + 1 - 1 - 2 = 0
- diff[0][1] = onesRow0 + onesCol1 - zerosRow0 - zerosCol1 = 2 + 1 - 1 - 2 = 0
- diff[0][2] = onesRow0 + onesCol2 - zerosRow0 - zerosCol2 = 2 + 3 - 1 - 0 = 4
- diff[1][0] = onesRow1 + onesCol0 - zerosRow1 - zerosCol0 = 2 + 1 - 1 - 2 = 0
- diff[1][1] = onesRow1 + onesCol1 - zerosRow1 - zerosCol1 = 2 + 1 - 1 - 2 = 0
- diff[1][2] = onesRow1 + onesCol2 - zerosRow1 - zerosCol2 = 2 + 3 - 1 - 0 = 4
- diff[2][0] = onesRow2 + onesCol0 - zerosRow2 - zerosCol0 = 1 + 1 - 2 - 2 = -2
- diff[2][1] = onesRow2 + onesCol1 - zerosRow2 - zerosCol1 = 1 + 1 - 2 - 2 = -2
- diff[2][2] = onesRow2 + onesCol2 - zerosRow2 - zerosCol2 = 1 + 3 - 2 - 0 = 2

Example 2:
Input: grid = [[1,1,1],[1,1,1]]
Output: [[5,5,5],[5,5,5]]
Explanation:
- diff[0][0] = onesRow0 + onesCol0 - zerosRow0 - zerosCol0 = 3 + 2 - 0 - 0 = 5
- diff[0][1] = onesRow0 + onesCol1 - zerosRow0 - zerosCol1 = 3 + 2 - 0 - 0 = 5
- diff[0][2] = onesRow0 + onesCol2 - zerosRow0 - zerosCol2 = 3 + 2 - 0 - 0 = 5
- diff[1][0] = onesRow1 + onesCol0 - zerosRow1 - zerosCol0 = 3 + 2 - 0 - 0 = 5
- diff[1][1] = onesRow1 + onesCol1 - zerosRow1 - zerosCol1 = 3 + 2 - 0 - 0 = 5
- diff[1][2] = onesRow1 + onesCol2 - zerosRow1 - zerosCol2 = 3 + 2 - 0 - 0 = 5

Constraints:
m == grid.length
n == grid[i].length
1 <= m, n <= 10^5
1 <= m * n <= 10^5
grid[i][j] is either 0 or 1.
```

<details><summary>Hint</summary>

```text
1. You need to reuse information about a row or a column many times.
   Try storing it to avoid computing it multiple times.
2. Use an array to store the number of 1’s in each row and another array to store the number of 1’s in each column.
   Once you know the number of 1’s in each row or column, you can also easily calculate the number of 0’s.
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
int** onesMinusZeros(int** grid, int gridSize, int* gridColSize, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    // m == grid.length, n == grid[i].length, 1 <= m, n <= 10^5.
    int rowSize = gridSize;
    int colSize = gridColSize[0];
    int i, j;

    pRetVal = (int**)malloc(rowSize * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    for (i = 0; i < rowSize; ++i) {
        pRetVal[i] = (int*)malloc(colSize * sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        memset(pRetVal[i], 0, (colSize * sizeof(int)));
    }

    (*returnColumnSizes) = (int*)malloc(rowSize * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        for (j = 0; j < rowSize; ++j) {
            free(pRetVal[j]);
            pRetVal[j] = NULL;
        }
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, (rowSize * sizeof(int)));

    int rowSum[rowSize];
    memset(rowSum, 0, sizeof(rowSum));
    int colSum[colSize];
    memset(colSum, 0, sizeof(colSum));
    for (i = 0; i < rowSize; ++i) {
        for (j = 0; j < colSize; ++j) {
            // grid[i][j] is either 0 or 1.
            rowSum[i] += grid[i][j];
            colSum[j] += grid[i][j];
        }
    }

    for (i = 0; i < rowSize; ++i) {
        for (j = 0; j < colSize; ++j) {
            pRetVal[i][j] = rowSum[i] + colSum[j];
            pRetVal[i][j] -= (rowSize - rowSum[i]);
            pRetVal[i][j] -= (colSize - colSum[j]);
        }
        (*returnColumnSizes)[i] = colSize;
    }
    (*returnSize) = rowSize;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<vector<int>> onesMinusZeros(vector<vector<int>>& grid) {
        vector<vector<int>> retVal;

        // m == grid.length, n == grid[i].length, 1 <= m, n <= 10^5.
        int rowSize = grid.size();
        int colSize = grid[0].size();
        retVal.resize(rowSize, vector<int>(colSize, 0));

        vector<int> rowSum(rowSize, 0);
        vector<int> colSum(colSize, 0);
        for (int i = 0; i < rowSize; ++i) {
            for (int j = 0; j < colSize; ++j) {
                // grid[i][j] is either 0 or 1.
                rowSum[i] += grid[i][j];
                colSum[j] += grid[i][j];
            }
        }

        for (int i = 0; i < rowSize; ++i) {
            for (int j = 0; j < colSize; ++j) {
                retVal[i][j] = rowSum[i] + colSum[j];
                retVal[i][j] -= (rowSize - rowSum[i]);
                retVal[i][j] -= (colSize - colSum[j]);
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
    def onesMinusZeros(self, grid: List[List[int]]) -> List[List[int]]:
        retVal = [[]]

        # m == grid.length, n == grid[i].length, 1 <= m, n <= 10^5.
        rowSize = len(grid)
        colSize = len(grid[0])
        retVal = [[0 for _ in range(colSize)] for _ in range(rowSize)]

        rowSum = [0] * rowSize
        colSum = [0] * colSize
        for i in range(rowSize):
            for j in range(colSize):
                # grid[i][j] is either 0 or 1.
                rowSum[i] += grid[i][j]
                colSum[j] += grid[i][j]

        for i in range(rowSize):
            for j in range(colSize):
                retVal[i][j] = rowSum[i] + colSum[j]
                retVal[i][j] -= (rowSize - rowSum[i])
                retVal[i][j] -= (colSize - colSum[j])

        return retVal
```

</details>

## [2529. Maximum Count of Positive Integer and Negative Integer](https://leetcode.com/problems/maximum-count-of-positive-integer-and-negative-integer/)  1195

- [Official](https://leetcode.com/problems/maximum-count-of-positive-integer-and-negative-integer/editorial/)
- [Official](https://leetcode.cn/problems/maximum-count-of-positive-integer-and-negative-integer/solutions/2726974/zheng-zheng-shu-he-fu-zheng-shu-de-zui-d-psye/)

<details><summary>Description</summary>

```text
Given an array nums sorted in non-decreasing order,
return the maximum between the number of positive integers and the number of negative integers.
- In other words, if the number of positive integers in nums is pos and the number of negative integers is neg,
then return the maximum of pos and neg.

Note that 0 is neither positive nor negative.

Example 1:
Input: nums = [-2,-1,-1,1,2,3]
Output: 3
Explanation: There are 3 positive integers and 3 negative integers. The maximum count among them is 3.

Example 2:
Input: nums = [-3,-2,-1,0,0,1,2]
Output: 3
Explanation: There are 2 positive integers and 3 negative integers. The maximum count among them is 3.

Example 3:
Input: nums = [5,20,66,1314]
Output: 4

Explanation: There are 4 positive integers and 0 negative integers. The maximum count among them is 4.

Constraints:
1 <= nums.length <= 2000
-2000 <= nums[i] <= 2000
nums is sorted in a non-decreasing order.

Follow up: Can you solve the problem in O(log(n)) time complexity?
```

<details><summary>Hint</summary>

```text
1. Count how many positive integers and negative integers are in the array.
2. Since the array is sorted, can we use the binary search?
```

</details>

</details>

<details><summary>C</summary>

```c
int maximumCount(int *nums, int numsSize) {
    int retVal = 0;

    int negative = 0;
    int zero = 0;
    int positive = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] < 0) {
            ++negative;
        } else if (nums[i] == 0) {
            ++zero;
        } else {
            break;
        }
    }
    positive = numsSize - negative - zero;

    retVal = fmax(negative, positive);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maximumCount(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        int negative = 0;
        int zero = 0;
        int positive = 0;
        for (int i = 0; i < numsSize; ++i) {
            if (nums[i] < 0) {
                ++negative;
            } else if (nums[i] == 0) {
                ++zero;
            } else {
                break;
            }
        }
        positive = numsSize - negative - zero;

        retVal = max(negative, positive);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maximumCount(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        negative = 0
        zero = 0
        positive = 0
        for i in range(numsSize):
            if nums[i] < 0:
                negative += 1
            elif nums[i] == 0:
                zero += 1
            else:
                break
        positive = numsSize - negative - zero

        retVal = max(negative, positive)

        return retVal
```

</details>

## [2553. Separate the Digits in an Array](https://leetcode.com/problems/separate-the-digits-in-an-array/)  1216

<details><summary>Description</summary>

```text
Given an array of positive integers nums, return an array answer
that consists of the digits of each integer in nums after separating them in the same order they appear in nums.

To separate the digits of an integer is to get all the digits it has in the same order.
- For example, for the integer 10921, the separation of its digits is [1,0,9,2,1].

Example 1:
Input: nums = [13,25,83,77]
Output: [1,3,2,5,8,3,7,7]
Explanation:
- The separation of 13 is [1,3].
- The separation of 25 is [2,5].
- The separation of 83 is [8,3].
- The separation of 77 is [7,7].
answer = [1,3,2,5,8,3,7,7]. Note that answer contains the separations in the same order.

Example 2:
Input: nums = [7,1,3,9]
Output: [7,1,3,9]
Explanation: The separation of each integer in nums is itself.
answer = [7,1,3,9].

Constraints:
1 <= nums.length <= 1000
1 <= nums[i] <= 10^5
```

<details><summary>Hint</summary>

```text
1. Convert each number into a list and append that list to the answer.
2. You can convert the integer into a string to do that easily.
```

</details>

</details>

<details><summary>C</summary>

```c
#define Biweekly_Contest_97 (1)  // 0:23:42; 0
#if (Biweekly_Contest_97)
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* separateDigits(int* nums, int numsSize, int* returnSize) {
    int* pRetVal = NULL;

#define MAX_RETURN_SIZE (6 * 1000)
    pRetVal = (int*)calloc(MAX_RETURN_SIZE, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }

    (*returnSize) = 0;
    int buf[8];
    int count;
    int i;
    for (i = 0; i < numsSize; ++i) {
        memset(buf, 0, sizeof(int));
        count = 0;
        while (nums[i] > 0) {
            buf[count++] = nums[i] % 10;
            nums[i] /= 10;
        }

        while (count > 0) {
            pRetVal[(*returnSize)++] = buf[--count];
        }
    }

    return pRetVal;
}
#endif
```

</details>

## [2657. Find the Prefix Common Array of Two Arrays](https://leetcode.com/problems/find-the-prefix-common-array-of-two-arrays/)  1304

- [Official](https://leetcode.com/problems/find-the-prefix-common-array-of-two-arrays/editorial/)

<details><summary>Description</summary>

```text
You are given two 0-indexed integer permutations A and B of length n.

A prefix common array of A and B is an array C
such that C[i] is equal to the count of numbers that are present at or before the index i in both A and B.

Return the prefix common array of A and B.

A sequence of n integers is called a permutation if it contains all integers from 1 to n exactly once.

Example 1:
Input: A = [1,3,2,4], B = [3,1,2,4]
Output: [0,2,3,4]
Explanation: At i = 0: no number is common, so C[0] = 0.
At i = 1: 1 and 3 are common in A and B, so C[1] = 2.
At i = 2: 1, 2, and 3 are common in A and B, so C[2] = 3.
At i = 3: 1, 2, 3, and 4 are common in A and B, so C[3] = 4.

Example 2:
Input: A = [2,3,1], B = [3,1,2]
Output: [0,1,3]
Explanation: At i = 0: no number is common, so C[0] = 0.
At i = 1: only 3 is common in A and B, so C[1] = 1.
At i = 2: 1, 2, and 3 are common in A and B, so C[2] = 3.

Constraints:
1 <= A.length == B.length == n <= 50
1 <= A[i], B[i] <= n
It is guaranteed that A and B are both a permutation of n integers.
```

<details><summary>Hint</summary>

```text
1. Consider keeping a frequency array that stores the count of occurrences of each number till index i.
2. If a number occurred two times,
   it means it occurred in both A and B since they’re both permutations so add one to the answer.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findThePrefixCommonArray(int* A, int ASize, int* B, int BSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int*)calloc(ASize, sizeof(int));
    if (pRetVal == NULL) {
        perror("malcallocloc");
        return pRetVal;
    }
    (*returnSize) = ASize;

    int frequency[ASize + 1];
    memset(frequency, 0, sizeof(frequency));
    int commonCount = 0;
    for (int currentIndex = 0; currentIndex < ASize; ++currentIndex) {
        frequency[A[currentIndex]]++;
        if (frequency[A[currentIndex]] == 2) {
            ++commonCount;
        }

        frequency[B[currentIndex]]++;
        if (frequency[B[currentIndex]] == 2) {
            ++commonCount;
        }

        pRetVal[currentIndex] = commonCount;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        vector<int> retVal;

        int ASize = A.size();
        retVal.resize(ASize, 0);

        vector<int> frequency(ASize + 1, 0);
        int commonCount = 0;
        for (int currentIndex = 0; currentIndex < ASize; ++currentIndex) {
            frequency[A[currentIndex]]++;
            if (frequency[A[currentIndex]] == 2) {
                ++commonCount;
            }

            frequency[B[currentIndex]]++;
            if (frequency[B[currentIndex]] == 2) {
                ++commonCount;
            }

            retVal[currentIndex] = commonCount;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def findThePrefixCommonArray(self, A: List[int], B: List[int]) -> List[int]:
        retVal = None

        ASize = len(A)
        retVal = [0] * ASize

        frequency = [0] * (ASize+1)
        commonCount = 0
        for currentIndex in range(ASize):
            frequency[A[currentIndex]] += 1
            if frequency[A[currentIndex]] == 2:
                commonCount += 1

            frequency[B[currentIndex]] += 1
            if frequency[B[currentIndex]] == 2:
                commonCount += 1

            retVal[currentIndex] = commonCount

        return retVal
```

</details>

## [2873. Maximum Value of an Ordered Triplet I](https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-i/)  1270

- [Official](https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-i/editorial/)
- [Official](https://leetcode.cn/problems/maximum-value-of-an-ordered-triplet-i/solutions/3610891/you-xu-san-yuan-zu-zhong-de-zui-da-zhi-i-y6zb/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array nums.

Return the maximum value over all triplets of indices (i, j, k) such that i < j < k.
If all such triplets have a negative value, return 0.

The value of a triplet of indices (i, j, k) is equal to (nums[i] - nums[j]) * nums[k].

Example 1:
Input: nums = [12,6,1,2,7]
Output: 77
Explanation: The value of the triplet (0, 2, 4) is (nums[0] - nums[2]) * nums[4] = 77.
It can be shown that there are no ordered triplets of indices with a value greater than 77.

Example 2:
Input: nums = [1,10,3,4,19]
Output: 133
Explanation: The value of the triplet (1, 2, 4) is (nums[1] - nums[2]) * nums[4] = 133.
It can be shown that there are no ordered triplets of indices with a value greater than 133.

Example 3:
Input: nums = [1,2,3]
Output: 0
Explanation: The only ordered triplet of indices (0, 1, 2) has a negative value of (nums[0] - nums[1]) * nums[2] = -3.
Hence, the answer would be 0.

Constraints:
3 <= nums.length <= 100
1 <= nums[i] <= 10^6
```

<details><summary>Hint</summary>

```text
1. Use three nested loops to find all the triplets.
```

</details>

</details>

<details><summary>C</summary>

```c
long long maximumTripletValue(int* nums, int numsSize) {
    long long retVal = 0;

    long long idxMax = 0;
    long long diffMax = 0;
    for (int k = 0; k < numsSize; k++) {
        retVal = fmax(retVal, diffMax * nums[k]);
        diffMax = fmax(diffMax, idxMax - nums[k]);
        idxMax = fmax(idxMax, (long long)nums[k]);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long maximumTripletValue(vector<int>& nums) {
        long long retVal = 0;

        int numsSize = nums.size();
        long long idxMax = 0;
        long long diffMax = 0;
        for (int k = 0; k < numsSize; k++) {
            retVal = max(retVal, diffMax * nums[k]);
            diffMax = max(diffMax, idxMax - nums[k]);
            idxMax = max(idxMax, (long long)nums[k]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maximumTripletValue(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)
        idxMax = 0
        diffMax = 0
        for k in range(numsSize):
            retVal = max(retVal, diffMax * nums[k])
            diffMax = max(diffMax, idxMax - nums[k])
            idxMax = max(idxMax, nums[k])

        return retVal
```

</details>

## [2874. Maximum Value of an Ordered Triplet II](https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-ii/)  1583

- [Official](https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-ii/editorial/)
- [Official](https://leetcode.cn/problems/maximum-value-of-an-ordered-triplet-ii/solutions/3610892/you-xu-san-yuan-zu-zhong-de-zui-da-zhi-i-angc/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array nums.

Return the maximum value over all triplets of indices (i, j, k) such that i < j < k.
If all such triplets have a negative value, return 0.

The value of a triplet of indices (i, j, k) is equal to (nums[i] - nums[j]) * nums[k].

Example 1:
Input: nums = [12,6,1,2,7]
Output: 77
Explanation: The value of the triplet (0, 2, 4) is (nums[0] - nums[2]) * nums[4] = 77.
It can be shown that there are no ordered triplets of indices with a value greater than 77.

Example 2:
Input: nums = [1,10,3,4,19]
Output: 133
Explanation: The value of the triplet (1, 2, 4) is (nums[1] - nums[2]) * nums[4] = 133.
It can be shown that there are no ordered triplets of indices with a value greater than 133.

Example 3:
Input: nums = [1,2,3]
Output: 0
Explanation: The only ordered triplet of indices (0, 1, 2) has a negative value of (nums[0] - nums[1]) * nums[2] = -3.
Hence, the answer would be 0.

Constraints:
3 <= nums.length <= 10^5
1 <= nums[i] <= 10^6
```

<details><summary>Hint</summary>

```text
1. Preprocess the prefix maximum array, prefix_max[i] = max(nums[0], nums[1], …, nums[i]) and the suffix maximum array,
   suffix_max[i] = max(nums[i], nums[i + 1], …, nums[i - 1]).
2. For each index j, find two indices i and k such that i < j < k and (nums[i] - nums[j]) * nums[k] is the maximum,
   using the prefix and suffix maximum arrays.
3. For index j, the maximum triplet value is (prefix_max[j - 1] - nums[j]) * suffix_max[j + 1].
```

</details>

</details>

<details><summary>C</summary>

```c
long long maximumTripletValue(int* nums, int numsSize) {
    long long retVal = 0;

    long long idxMax = 0;
    long long diffMax = 0;
    for (int k = 0; k < numsSize; k++) {
        retVal = fmax(retVal, diffMax * nums[k]);
        diffMax = fmax(diffMax, idxMax - nums[k]);
        idxMax = fmax(idxMax, (long long)nums[k]);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long maximumTripletValue(vector<int>& nums) {
        long long retVal = 0;

        int numsSize = nums.size();
        long long idxMax = 0;
        long long diffMax = 0;
        for (int k = 0; k < numsSize; k++) {
            retVal = max(retVal, diffMax * nums[k]);
            diffMax = max(diffMax, idxMax - nums[k]);
            idxMax = max(idxMax, (long long)nums[k]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maximumTripletValue(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)
        idxMax = 0
        diffMax = 0
        for k in range(numsSize):
            retVal = max(retVal, diffMax * nums[k])
            diffMax = max(diffMax, idxMax - nums[k])
            idxMax = max(idxMax, nums[k])

        return retVal
```

</details>

## [2923. Find Champion I](https://leetcode.com/problems/find-champion-i/)  1235

- [Official](https://leetcode.cn/problems/find-champion-i/description/)

<details><summary>Description</summary>

```text
There are n teams numbered from 0 to n - 1 in a tournament.

Given a 0-indexed 2D boolean matrix grid of size n * n.
For all i, j that 0 <= i, j <= n - 1 and i != j team i is stronger than team j if grid[i][j] == 1,
otherwise, team j is stronger than team i.

Team a will be the champion of the tournament if there is no team b that is stronger than team a.

Return the team that will be the champion of the tournament.

Example 1:
Input: grid = [[0,1],[0,0]]
Output: 0
Explanation: There are two teams in this tournament.
grid[0][1] == 1 means that team 0 is stronger than team 1. So team 0 will be the champion.

Example 2:
Input: grid = [[0,0,1],[1,0,1],[0,0,0]]
Output: 1
Explanation: There are three teams in this tournament.
grid[1][0] == 1 means that team 1 is stronger than team 0.
grid[1][2] == 1 means that team 1 is stronger than team 2.
So team 1 will be the champion.

Constraints:
n == grid.length
n == grid[i].length
2 <= n <= 100
grid[i][j] is either 0 or 1.
For all i grid[i][i] is 0.
For all i, j that i != j, grid[i][j] != grid[j][i].
The input is generated such that if team a is stronger than team b and team b is stronger than team c,
then team a is stronger than team c.
```

<details><summary>Hint</summary>

```text
1. The champion should be stronger than all the other teams.
```

</details>

</details>

<details><summary>C</summary>

```c
int findChampion(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int stronger = 0;
    int x, y;
    for (x = 0; x < gridSize; ++x) {
        stronger = 0;
        for (y = 0; y < gridColSize[x]; ++y) {
            stronger += grid[x][y];
        }

        if (stronger == gridSize - 1) {
            retVal = x;
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
    int findChampion(vector<vector<int>>& grid) {
        int retVal = 0;

        int gridSize = grid.size();
        for (int x = 0; x < gridSize; ++x) {
            int stronger = 0;
            int gridColSize = grid[x].size();
            for (int y = 0; y < gridColSize; ++y) {
                stronger += grid[x][y];
            }

            if (stronger == gridSize - 1) {
                retVal = x;
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
    def findChampion(self, grid: List[List[int]]) -> int:
        retVal = 0

        gridSize = len(grid)
        for row in range(gridSize):
            stronger = 0
            for cell in grid[row]:
                stronger += cell

            if stronger == (gridSize-1):
                retVal = row
                break

        return retVal
```

</details>

## [3105. Longest Strictly Increasing or Strictly Decreasing Subarray](https://leetcode.com/problems/longest-strictly-increasing-or-strictly-decreasing-subarray/)  1217

- [Official](https://leetcode.com/problems/longest-strictly-increasing-or-strictly-decreasing-subarray/editorial/)

<details><summary>Description</summary>

```text
You are given an array of integers nums.
Return the length of the longest subarray of nums which is either strictly increasing or strictly decreasing.

Example 1:
Input: nums = [1,4,3,3,2]
Output: 2
Explanation:
The strictly increasing subarrays of nums are [1], [2], [3], [3], [4], and [1,4].
The strictly decreasing subarrays of nums are [1], [2], [3], [3], [4], [3,2], and [4,3].
Hence, we return 2.

Example 2:
Input: nums = [3,3,3,3]
Output: 1
Explanation:
The strictly increasing subarrays of nums are [3], [3], [3], and [3].
The strictly decreasing subarrays of nums are [3], [3], [3], and [3].
Hence, we return 1.

Example 3:
Input: nums = [3,2,1]
Output: 3
Explanation:
The strictly increasing subarrays of nums are [3], [2], and [1].
The strictly decreasing subarrays of nums are [3], [2], [1], [3,2], [2,1], and [3,2,1].
Hence, we return 3.

Constraints:
1 <= nums.length <= 50
1 <= nums[i] <= 50
```

</details>

<details><summary>C</summary>

```c
int longestMonotonicSubarray(int* nums, int numsSize) {
    int retVal = 1;

    int increasing = 1;
    int decreasing = 1;
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i - 1] < nums[i]) {
            increasing += 1;
            decreasing = 1;
        } else if (nums[i - 1] > nums[i]) {
            decreasing += 1;
            increasing = 1;
        } else {
            increasing = 1;
            decreasing = 1;
        }
        retVal = fmax(retVal, fmax(increasing, decreasing));
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int longestMonotonicSubarray(vector<int>& nums) {
        int retVal = 1;

        int numsSize = nums.size();

        int increasing = 1;
        int decreasing = 1;
        for (int i = 1; i < numsSize; ++i) {
            if (nums[i - 1] < nums[i]) {
                increasing += 1;
                decreasing = 1;
            } else if (nums[i - 1] > nums[i]) {
                decreasing += 1;
                increasing = 1;
            } else {
                increasing = 1;
                decreasing = 1;
            }
            retVal = max(retVal, max(increasing, decreasing));
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def longestMonotonicSubarray(self, nums: List[int]) -> int:
        retVal = 1

        numsSize = len(nums)

        increasing = 1
        decreasing = 1
        for i in range(1, numsSize):
            if (nums[i-1] < nums[i]):
                increasing += 1
                decreasing = 1
            elif (nums[i-1] > nums[i]):
                decreasing += 1
                increasing = 1
            else:
                increasing = 1
                decreasing = 1
            retVal = max(retVal, max(increasing, decreasing))

        return retVal
```

</details>

## [3151. Special Array I](https://leetcode.com/problems/special-array-i/)  1152

- [Official](https://leetcode.com/problems/special-array-i/editorial/)
- [Official](https://leetcode.cn/problems/special-array-i/solutions/2872838/te-shu-shu-zu-i-by-leetcode-solution-kpjn/)

<details><summary>Description</summary>

```text
An array is considered special if every pair of its adjacent elements contains two numbers with different parity.

You are given an array of integers nums. Return true if nums is a special array, otherwise, return false.

Example 1:
Input: nums = [1]
Output: true
Explanation:
There is only one element. So the answer is true.

Example 2:
Input: nums = [2,1,4]
Output: true
Explanation:
There is only two pairs: (2,1) and (1,4), and both of them contain numbers with different parity. So the answer is true.

Example 3:
Input: nums = [4,3,1,6]
Output: false
Explanation:
nums[1] and nums[2] are both odd. So the answer is false.

Constraints:
1 <= nums.length <= 100
1 <= nums[i] <= 100
```

<details><summary>Hint</summary>

```text
1. Try to check the parity of each element and its previous element.
```

</details>

</details>

<details><summary>C</summary>

```c
bool isArraySpecial(int* nums, int numsSize) {
    bool retVal = true;

    for (int i = 1; i < numsSize; ++i) {
        if (nums[i - 1] % 2 == nums[i] % 2) {
            retVal = false;
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
    bool isArraySpecial(vector<int>& nums) {
        bool retVal = true;

        int numsSize = nums.size();
        for (int i = 1; i < numsSize; ++i) {
            if (nums[i - 1] % 2 == nums[i] % 2) {
                retVal = false;
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
    def isArraySpecial(self, nums: List[int]) -> bool:
        retVal = True

        numsSize = len(nums)
        for i in range(1, numsSize):
            if nums[i-1] % 2 == nums[i] % 2:
                retVal = False
                break

        return retVal
```

</details>

## [3206. Alternating Groups I](https://leetcode.com/problems/alternating-groups-i/)  1223

- [Official](https://leetcode.cn/problems/alternating-groups-i/)

<details><summary>Description</summary>

```text
There is a circle of red and blue tiles. You are given an array of integers colors.
The color of tile i is represented by colors[i]:
- colors[i] == 0 means that tile i is red.
- colors[i] == 1 means that tile i is blue.

Every 3 contiguous tiles in the circle with alternating colors
(the middle tile has a different color from its left and right tiles) is called an alternating group.

Return the number of alternating groups.

Note that since colors represents a circle, the first and the last tiles are considered to be next to each other.

Example 1:
Input: colors = [1,1,1]
Output: 0

Example 2:
Input: colors = [0,1,0,0,1]
Output: 3

Constraints:
3 <= colors.length <= 100
0 <= colors[i] <= 1
```

<details><summary>Hint</summary>

```text
1. For each tile, check that the previous and the next tile have different colors from that tile or not.
```

</details>

</details>

<details><summary>C</summary>

```c
int numberOfAlternatingGroups(int* colors, int colorsSize) {
    int retVal = 0;

    for (int i = 0; i < colorsSize; ++i) {
        if (colors[i] == colors[(i - 1 + colorsSize) % colorsSize]) {
            continue;
        } else if (colors[i] == colors[(i + 1) % colorsSize]) {
            continue;
        }
        retVal++;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int numberOfAlternatingGroups(vector<int>& colors) {
        int retVal = 0;

        int colorsSize = colors.size();
        for (int i = 0; i < colorsSize; ++i) {
            if (colors[i] == colors[(i - 1 + colorsSize) % colorsSize]) {
                continue;
            } else if (colors[i] == colors[(i + 1) % colorsSize]) {
                continue;
            }
            retVal++;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def numberOfAlternatingGroups(self, colors: List[int]) -> int:
        retVal = 0

        colorsSize = len(colors)
        for i in range(colorsSize):
            if colors[i] == colors[(i-1+colorsSize) % colorsSize]:
                continue
            elif colors[i] == colors[(i+1) % colorsSize]:
                continue
            retVal += 1

        return retVal
```

</details>

## [3208. Alternating Groups II](https://leetcode.com/problems/alternating-groups-ii/)  1721

- [Official](https://leetcode.com/problems/alternating-groups-ii/editorial/)
- [Official](https://leetcode.cn/problems/alternating-groups-ii/solutions/2986846/jiao-ti-zu-ii-by-leetcode-solution-7912/)

<details><summary>Description</summary>

```text
There is a circle of red and blue tiles. You are given an array of integers colors and an integer k.
The color of tile i is represented by colors[i]:
- colors[i] == 0 means that tile i is red.
- colors[i] == 1 means that tile i is blue.

An alternating group is every k contiguous tiles in the circle with alternating colors
(each tile in the group except the first and last one has a different color from its left and right tiles).

Return the number of alternating groups.

Note that since colors represents a circle, the first and the last tiles are considered to be next to each other.

Example 1:
Input: colors = [0,1,0,1,0], k = 3
Output: 3

Example 2:
Input: colors = [0,1,0,0,1,0,1], k = 6
Output: 2

Example 3:
Input: colors = [1,1,0,1], k = 4
Output: 0

Constraints:
3 <= colors.length <= 10^5
0 <= colors[i] <= 1
3 <= k <= colors.length
```

<details><summary>Hint</summary>

```text
1. Try to find a tile that has the same color as its next tile (if it exists).
2. Then try to find maximal alternating groups by starting a single for loop from that tile.
```

</details>

</details>

<details><summary>C</summary>

```c
int numberOfAlternatingGroups(int* colors, int colorsSize, int k) {
    int retVal = 0;

    int index;
    int alternatingElementsCount = 1;
    int lastColor = colors[0];
    for (int i = 1; i < colorsSize + k - 1; i++) {
        index = i % colorsSize;

        // Check if current color is the same as last color
        if (colors[index] == lastColor) {
            // Pattern breaks, reset sequence length
            alternatingElementsCount = 1;
            lastColor = colors[index];
            continue;
        }

        // Extend alternating sequence
        alternatingElementsCount += 1;

        // If sequence length reaches at least k, count it
        if (alternatingElementsCount >= k) {
            retVal++;
        }

        lastColor = colors[index];
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int numberOfAlternatingGroups(vector<int>& colors, int k) {
        int retVal = 0;

        int colorsSize = colors.size();
        int alternatingElementsCount = 1;
        int lastColor = colors[0];
        for (int i = 1; i < colorsSize + k - 1; i++) {
            int index = i % colorsSize;

            // Check if current color is the same as last color
            if (colors[index] == lastColor) {
                // Pattern breaks, reset sequence length
                alternatingElementsCount = 1;
                lastColor = colors[index];
                continue;
            }

            // Extend alternating sequence
            alternatingElementsCount += 1;

            // If sequence length reaches at least k, count it
            if (alternatingElementsCount >= k) {
                retVal++;
            }

            lastColor = colors[index];
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def numberOfAlternatingGroups(self, colors: List[int], k: int) -> int:
        retVal = 0

        colorsSize = len(colors)
        alternatingElementsCount = 1
        lastColor = colors[0]
        for i in range(1, colorsSize + k - 1):
            index = i % colorsSize

            # Check if current color is the same as the last color
            if colors[index] == lastColor:
                # Pattern breaks, reset sequence length
                alternatingElementsCount = 1
                lastColor = colors[index]
                continue

            # Extend sequence
            alternatingElementsCount += 1

            # If sequence length reaches at least k, count it
            if alternatingElementsCount >= k:
                retVal += 1

            lastColor = colors[index]

        return retVal
```

</details>

## [3392. Count Subarrays of Length Three With a Condition](https://leetcode.com/problems/count-subarrays-of-length-three-with-a-condition/)  1200

- [Official](https://leetcode.com/problems/count-subarrays-of-length-three-with-a-condition/editorial/)
- [Official](https://leetcode.cn/problems/count-subarrays-of-length-three-with-a-condition/solutions/3651614/tong-ji-fu-he-tiao-jian-chang-du-wei-3-d-t7rt/)

<details><summary>Description</summary>

```text
Given an integer array nums, return the number of subarrays of length 3
such that the sum of the first and third numbers equals exactly half of the second number.

Example 1:
Input: nums = [1,2,1,4,1]
Output: 1
Explanation:
Only the subarray [1,4,1] contains exactly 3 elements
where the sum of the first and third numbers equals half the middle number.

Example 2:
Input: nums = [1,1,1]
Output: 0
Explanation:
[1,1,1] is the only subarray of length 3. However, its first and third numbers do not add to half the middle number.

Constraints:
3 <= nums.length <= 100
-100 <= nums[i] <= 100
```

<details><summary>Hint</summary>

```text
1. The constraints are small. Consider checking every subarray.
```

</details>

</details>

<details><summary>C</summary>

```c
int countSubarrays(int* nums, int numsSize) {
    int retVal = 0;

    for (int i = 0; i < numsSize - 2; ++i) {
        if (2 * (nums[i] + nums[i + 2]) == nums[i + 1]) {
            retVal++;
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
    int countSubarrays(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        for (int i = 0; i < numsSize - 2; ++i) {
            if (2 * (nums[i] + nums[i + 2]) == nums[i + 1]) {
                retVal++;
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
    def countSubarrays(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)
        for i in range(numsSize-2):
            if 2 * (nums[i] + nums[i+2]) == nums[i+1]:
                retVal += 1

        return retVal
```

</details>

## [3423. Maximum Difference Between Adjacent Elements in a Circular Array](https://leetcode.com/problems/maximum-difference-between-adjacent-elements-in-a-circular-array/)  1184

- [Official](https://leetcode.com/problems/maximum-difference-between-adjacent-elements-in-a-circular-array/editorial/)
- [Official](https://leetcode.cn/problems/maximum-difference-between-adjacent-elements-in-a-circular-array/solutions/3692736/xun-huan-shu-zu-zhong-xiang-lin-yuan-su-q5nq3/)

<details><summary>Description</summary>

```text
Given a circular array nums, find the maximum absolute difference between adjacent elements.

Note: In a circular array, the first and last elements are adjacent.

Example 1:
Input: nums = [1,2,4]
Output: 3
Explanation:
Because nums is circular, nums[0] and nums[2] are adjacent. They have the maximum absolute difference of |4 - 1| = 3.

Example 2:
Input: nums = [-5,-10,-5]
Output: 5
Explanation:
The adjacent elements nums[0] and nums[1] have the maximum absolute difference of |-5 - (-10)| = 5.

Constraints:
2 <= nums.length <= 100
-100 <= nums[i] <= 100
```

<details><summary>Hint</summary>

```text
1. Traverse from the second element to the last element and check the difference of every adjacent pair.
2. The edge case is to check the difference between the first and last elements.
```

</details>

</details>

<details><summary>C</summary>

```c
int maxAdjacentDistance(int* nums, int numsSize) {
    int retVal = 0;

    retVal = fmax(retVal, abs(nums[0] - nums[numsSize - 1]));
    for (int i = 1; i < numsSize; ++i) {
        retVal = fmax(retVal, abs(nums[i] - nums[i - 1]));
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxAdjacentDistance(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        retVal = max(retVal, abs(nums[0] - nums[numsSize - 1]));
        for (int i = 1; i < numsSize; ++i) {
            retVal = max(retVal, abs(nums[i] - nums[i - 1]));
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxAdjacentDistance(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)
        retVal = max(retVal, abs(nums[0] - nums[numsSize-1]))
        for i in range(1, numsSize):
            retVal = max(retVal, abs(nums[i] - nums[i-1]))

        return retVal
```

</details>
