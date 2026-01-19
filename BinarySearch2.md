# [Binary Search](https://en.wikipedia.org/wiki/Binary_search_algorithm)

## [1011. Capacity To Ship Packages Within D Days](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/)  1725

- [Official](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/solutions/2934252/capacity-to-ship-packages-within-d-days/)
- [Official](https://leetcode.cn/problems/capacity-to-ship-packages-within-d-days/solutions/743995/zai-d-tian-nei-song-da-bao-guo-de-neng-l-ntml/)

<details><summary>Description</summary>

```text
A conveyor belt has packages that must be shipped from one port to another within days days.

The ith package on the conveyor belt has a weight of weights[i].
Each day, we load the ship with packages on the conveyor belt (in the order given by weights).
We may not load more weight than the maximum weight capacity of the ship.

Return the least weight capacity of the ship
that will result in all the packages on the conveyor belt being shipped within days days.

Example 1:
Input: weights = [1,2,3,4,5,6,7,8,9,10], days = 5
Output: 15
Explanation: A ship capacity of 15 is the minimum to ship all the packages in 5 days like this:
1st day: 1, 2, 3, 4, 5
2nd day: 6, 7
3rd day: 8
4th day: 9
5th day: 10
Note that the cargo must be shipped in the order given, so using a ship of capacity 14
and splitting the packages into parts like (2, 3, 4, 5), (1, 6, 7), (8), (9), (10) is not allowed.

Example 2:
Input: weights = [3,2,2,4,1,4], days = 3
Output: 6
Explanation: A ship capacity of 6 is the minimum to ship all the packages in 3 days like this:
1st day: 3, 2
2nd day: 2, 4
3rd day: 1, 4

Example 3:
Input: weights = [1,2,3,1,1], days = 4
Output: 3
Explanation:
1st day: 1
2nd day: 2
3rd day: 3
4th day: 1, 1

Constraints:
1 <= days <= weights.length <= 5 * 10^4
1 <= weights[i] <= 500
```

<details><summary>Hint</summary>

```text
1. Binary search on the answer.
   We need a function possible(capacity) which returns true if and only if we can do the task in D days.
```

</details>

</details>

<details><summary>C</summary>

```c
int shipWithinDays(int *weights, int weightsSize, int days) {
    int retVal = 0;

    int i;

    int left = 0;
    int right = 0;
    for (i = 0; i < weightsSize; ++i) {
        left = fmax(left, weights[i]);
        right += weights[i];
    }

    int middle;
    int useDays;
    int capacity;
    while (left < right) {
        middle = left + (right - left) / 2;

        useDays = 1;
        capacity = 0;
        for (i = 0; i < weightsSize; ++i) {
            capacity += weights[i];
            if (capacity > middle) {
                capacity = weights[i];
                useDays += 1;
            }
        }

        if (useDays > days) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    retVal = left;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int shipWithinDays(vector<int>& weights, int days) {
        int retVal = 0;

        int left = *max_element(weights.begin(), weights.end());
        int right = accumulate(weights.begin(), weights.end(), 0);
        while (left < right) {
            int middle = left + (right - left) / 2;

            int useDays = 1;
            int capacity = 0;
            for (auto weight : weights) {
                capacity += weight;
                if (capacity > middle) {
                    capacity = weight;
                    useDays += 1;
                }
            }
            if (useDays > days) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }
        retVal = left;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def shipWithinDays(self, weights: List[int], days: int) -> int:
        retVal = 0

        left = max(weights)
        right = sum(weights)
        while left < right:
            middle = left + (right - left) // 2

            capacity = 0
            useDays = 1
            for weight in weights:
                capacity += weight
                if capacity > middle:
                    useDays += 1
                    capacity = weight

            if useDays > days:
                left = middle + 1
            else:
                right = middle
        retVal = left

        return retVal
```

</details>

## [1095. Find in Mountain Array](https://leetcode.com/problems/find-in-mountain-array/)  1827

- [Official](https://leetcode.com/problems/find-in-mountain-array/editorial/)
- [Official](https://leetcode.cn/problems/find-in-mountain-array/solutions/223827/shan-mai-shu-zu-zhong-cha-zhao-mu-biao-zhi-by-leet/)

<details><summary>Description</summary>

```text
(This problem is an interactive problem.)

You may recall that an array arr is a mountain array if and only if:
- arr.length >= 3
- There exists some i with 0 < i < arr.length - 1 such that:
  - arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
  - arr[i] > arr[i + 1] > ... > arr[arr.length - 1]

Given a mountain array mountainArr, return the minimum index such that mountainArr.get(index) == target.
If such an index does not exist, return -1.

You cannot access the mountain array directly. You may only access the array using a MountainArray interface:
- MountainArray.get(k) returns the element of the array at index k (0-indexed).
- MountainArray.length() returns the length of the array.

Submissions making more than 100 calls to MountainArray.get will be judged Wrong Answer.
Also, any solutions that attempt to circumvent the judge will result in disqualification.

Example 1:
Input: array = [1,2,3,4,5,3,1], target = 3
Output: 2
Explanation: 3 exists in the array, at index=2 and index=5. Return the minimum index, which is 2.

Example 2:
Input: array = [0,1,2,4,2,1], target = 3
Output: -1
Explanation: 3 does not exist in the array, so we return -1.

Constraints:
3 <= mountain_arr.length() <= 10^4
0 <= target <= 10^9
0 <= mountain_arr.get(index) <= 10^9
```

<details><summary>Hint</summary>

```text
1. Based on whether A[i-1] < A[i] < A[i+1], A[i-1] < A[i] > A[i+1], or A[i-1] > A[i] > A[i+1],
   we are either at the left side, peak, or right side of the mountain.
   We can binary search to find the peak.
   After finding the peak, we can binary search
   two more times to find whether the value occurs on either side of the peak.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * *********************************************************************
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * *********************************************************************
 *
 * int get(MountainArray *, int index);
 * int length(MountainArray *);
 */
int findInMountainArray(int target, MountainArray* mountainArr) {
    int retVal = -1;

    int arrSize = length(mountainArr);
    int left, right, middle, peak, value;

    // Find the index of the peak element
    left = 0;
    right = arrSize - 1;
    while (left < right) {
        middle = left + (right - left) / 2;
        if (get(mountainArr, middle) < get(mountainArr, middle + 1)) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    peak = left;

    // Search in the strictly increasing part of the array. If found, will be returned in the loop itself.
    left = 0;
    right = peak;
    while (left <= right) {
        middle = left + (right - left) / 2;
        value = get(mountainArr, middle);
        if (value == target) {
            retVal = middle;
            return retVal;
        } else if (value < target) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    // Search in the strictly decreasing part of the array. If found, will be returned in the loop itself.
    left = peak + 1;
    right = arrSize - 1;
    while (left <= right) {
        middle = left + (right - left) / 2;
        value = get(mountainArr, middle);
        if (value == target) {
            retVal = middle;
            return retVal;
        } else if (value > target) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *     int get(int index);
 *     int length();
 * };
 */
class Solution {
   public:
    int findInMountainArray(int target, MountainArray& mountainArr) {
        int retVal = -1;

        int arrSize = mountainArr.length();
        int left, right, middle, peak, value;

        // Find the index of the peak element
        left = 0;
        right = arrSize - 1;
        while (left < right) {
            middle = left + (right - left) / 2;
            if (mountainArr.get(middle) < mountainArr.get(middle + 1)) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }
        peak = left;

        // Search in the strictly increasing part of the array. If found, will be returned in the loop itself.
        left = 0;
        right = peak;
        while (left <= right) {
            middle = left + (right - left) / 2;
            value = mountainArr.get(middle);
            if (value == target) {
                retVal = middle;
                return retVal;
            } else if (value < target) {
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }

        // Search in the strictly decreasing part of the array. If found, will be returned in the loop itself.
        left = peak + 1;
        right = arrSize - 1;
        while (left <= right) {
            middle = left + (right - left) / 2;
            value = mountainArr.get(middle);
            if (value == target) {
                retVal = middle;
                return retVal;
            } else if (value > target) {
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
# """
# This is MountainArray's API interface.
# You should not implement it, or speculate about its implementation
# """
# class MountainArray:
#    def get(self, index: int) -> int:
#    def length(self) -> int:


class Solution:
    def findInMountainArray(self, target: int, mountain_arr: 'MountainArray') -> int:
        retVal = -1

        arrSize = mountain_arr.length()

        # Find the index of the peak element
        left = 0
        right = arrSize - 1
        while left < right:
            middle = left + (right - left) // 2
            if mountain_arr.get(middle) < mountain_arr.get(middle+1):
                left = middle + 1
            else:
                right = middle
        peak = left

        # Search in the strictly increasing part of the array. If found, will be returned in the loop itself.
        left = 0
        right = peak
        while left <= right:
            middle = (left + right) // 2
            value = mountain_arr.get(middle)
            if value == target:
                retVal = middle
                return retVal
            elif value < target:
                left = middle + 1
            else:
                right = middle - 1

        # Search in the strictly decreasing part of the array. If found, will be returned in the loop itself.
        left = peak + 1
        right = arrSize - 1
        while left <= right:
            middle = (left + right) // 2
            value = mountain_arr.get(middle)
            if value == target:
                retVal = middle
                return retVal
            elif value > target:
                left = middle + 1
            else:
                right = middle - 1

        return retVal
```

</details>

## [1283. Find the Smallest Divisor Given a Threshold](https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/)  1541

- [Official](https://leetcode.cn/problems/find-the-smallest-divisor-given-a-threshold/solutions/101358/shi-jie-guo-bu-chao-guo-yu-zhi-de-zui-xiao-chu-s-3/)

<details><summary>Description</summary>

```text
Given an array of integers nums and an integer threshold,
we will choose a positive integer divisor, divide all the array by it, and sum the division's result.
Find the smallest divisor such that the result mentioned above is less than or equal to threshold.

Each result of the division is rounded to the nearest integer greater than or equal to that element.
(For example: 7/3 = 3 and 10/2 = 5).

The test cases are generated so that there will be an answer.

Example 1:
Input: nums = [1,2,5,9], threshold = 6
Output: 5
Explanation: We can get a sum to 17 (1+2+5+9) if the divisor is 1.
If the divisor is 4 we can get a sum of 7 (1+1+2+3) and if the divisor is 5 the sum will be 5 (1+1+1+2).

Example 2:
Input: nums = [44,22,33,11,1], threshold = 5
Output: 44

Constraints:
1 <= nums.length <= 5 * 10^4
1 <= nums[i] <= 10^6
nums.length <= threshold <= 10^6
```

<details><summary>Hint</summary>

```text
1. Examine every possible number for solution. Choose the largest of them.
2. Use binary search to reduce the time complexity.
```

</details>

</details>

<details><summary>C</summary>

```c
int smallestDivisor(int* nums, int numsSize, int threshold) {
    int retVal = 0;

    int i;

    int left = 1;
    int right = 0;
    for (i = 0; i < numsSize; ++i) {
        right = fmax(right, nums[i]);
    }

    int middle;
    int sum;
    while (left < right) {
        middle = left + (right - left) / 2;

        sum = 0;
        for (i = 0; i < numsSize; ++i) {
            sum += ((nums[i] + middle - 1) / middle);
        }

        if (sum > threshold) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    retVal = left;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        int retVal = 0;

        int left = 1;
        int right = *max_element(nums.begin(), nums.end());
        while (left < right) {
            int middle = left + (right - left) / 2;

            int sum = 0;
            for (auto num : nums) {
                sum += ((num + middle - 1) / middle);
            }

            if (sum > threshold) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }
        retVal = left;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def smallestDivisor(self, nums: List[int], threshold: int) -> int:
        retVal = 0

        left = 1
        right = max(nums)
        while left < right:
            middle = left + (right - left) // 2

            sum = 0
            for num in nums:
                sum += ((num + middle - 1) // middle)

            if sum > threshold:
                left = middle + 1
            else:
                right = middle
        retVal = left

        return retVal
```

</details>

## [1292. Maximum Side Length of a Square with Sum Less than or Equal to Threshold](https://leetcode.com/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold/)  1735

- [Official](https://leetcode.com/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold/editorial/)
- [Official](https://leetcode.cn/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold/solutions/101737/yuan-su-he-xiao-yu-deng-yu-yu-zhi-de-zheng-fang-2/)

<details><summary>Description</summary>

```text
Given a m x n matrix mat and an integer threshold,
return the maximum side-length of a square with a sum less than or equal to threshold
or return 0 if there is no such square.

Example 1:
Input: mat = [[1,1,3,2,4,3,2],[1,1,3,2,4,3,2],[1,1,3,2,4,3,2]], threshold = 4
Output: 2
Explanation: The maximum side length of square with sum less than 4 is 2 as shown.

Example 2:
Input: mat = [[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2]], threshold = 1
Output: 0

Constraints:
m == mat.length
n == mat[i].length
1 <= m, n <= 300
0 <= mat[i][j] <= 10^4
0 <= threshold <= 10^5
```

<details><summary>Hint</summary>

```text
1. Store prefix sum of all grids in another 2D array.
2. Try all possible solutions and if you cannot find one return -1.
3. If x is a valid answer then any y < x is also valid answer. Use binary search to find answer.
```

</details>

</details>

<details><summary>C</summary>

```c
int getRect(int** P, int x1, int y1, int x2, int y2) {
    int retVal = P[x2][y2] - P[x1 - 1][y2] - P[x2][y1 - 1] + P[x1 - 1][y1 - 1];

    return retVal;
}
int maxSideLength(int** mat, int matSize, int* matColSize, int threshold) {
    int retVal = 0;

    int rowSize = matSize;
    int colSize = matColSize[0];

    int** P = (int**)malloc((rowSize + 1) * sizeof(int*));
    if (P == NULL) {
        perror("malloc");
        return retVal;
    }
    for (int i = 0; i <= rowSize; i++) {
        P[i] = (int*)calloc(colSize + 1, sizeof(int));
        if (P[i] == NULL) {
            perror("calloc");
            goto exit;
        }
    }
    for (int i = 1; i <= rowSize; i++) {
        for (int j = 1; j <= colSize; j++) {
            P[i][j] = P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1] + mat[i - 1][j - 1];
        }
    }

    int r = (rowSize < colSize) ? (rowSize) : (colSize);
    for (int i = 1; i <= rowSize; i++) {
        for (int j = 1; j <= colSize; j++) {
            for (int c = retVal + 1; c <= r; c++) {
                if (i + c - 1 > rowSize) {
                    break;
                } else if (j + c - 1 > colSize) {
                    break;
                } else if (getRect(P, i, j, i + c - 1, j + c - 1) > threshold) {
                    break;
                }
                retVal = c;
            }
        }
    }

exit:
    for (int i = 0; i <= rowSize; i++) {
        if (P[i] != NULL) {
            free(P[i]);
            P[i] = NULL;
        }
    }
    free(P);
    P = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    int getRect(const vector<vector<int>>& P, int x1, int y1, int x2, int y2) {
        int retVal = P[x2][y2] - P[x1 - 1][y2] - P[x2][y1 - 1] + P[x1 - 1][y1 - 1];

        return retVal;
    }

   public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        int retVal = 0;

        int rowSize = mat.size();
        int colSize = mat[0].size();

        vector<vector<int>> P(rowSize + 1, vector<int>(colSize + 1));
        for (int i = 1; i <= rowSize; ++i) {
            for (int j = 1; j <= colSize; ++j) {
                P[i][j] = P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1] + mat[i - 1][j - 1];
            }
        }

        int r = min(rowSize, colSize);
        for (int i = 1; i <= rowSize; ++i) {
            for (int j = 1; j <= colSize; ++j) {
                for (int c = retVal + 1; c <= r; ++c) {
                    if (i + c - 1 > rowSize) {
                        break;
                    } else if (j + c - 1 > colSize) {
                        break;
                    } else if (getRect(P, i, j, i + c - 1, j + c - 1) > threshold) {
                        break;
                    }

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
    def getRect(self, P: List[List[int]], x1: int, y1: int, x2: int, y2: int) -> int:
        retVal = P[x2][y2] - P[x1 - 1][y2] - P[x2][y1 - 1] + P[x1 - 1][y1 - 1]

        return retVal

    def maxSideLength(self, mat: List[List[int]], threshold: int) -> int:
        retVal = 0

        rowSize = len(mat)
        colSize = len(mat[0])

        P = [[0] * (colSize + 1) for _ in range(rowSize + 1)]
        for i in range(1, rowSize + 1):
            for j in range(1, colSize + 1):
                P[i][j] = P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1] + mat[i - 1][j - 1]

        r = min(rowSize, colSize)
        for i in range(1, rowSize + 1):
            for j in range(1, colSize + 1):
                for c in range(retVal + 1, r + 1):
                    if i + c - 1 > rowSize:
                        break
                    elif j + c - 1 > colSize:
                        break
                    elif self.getRect(P, i, j, i + c - 1, j + c - 1) > threshold:
                        break

                    retVal += 1

        return retVal
```

</details>

## [1337. The K Weakest Rows in a Matrix](https://leetcode.com/problems/the-k-weakest-rows-in-a-matrix/)  1224

- [Official](https://leetcode.cn/problems/the-k-weakest-rows-in-a-matrix/solutions/130589/fang-zhen-zhong-zhan-dou-li-zui-ruo-de-k-xing-by-l/)

<details><summary>Description</summary>

```text
You are given an m x n binary matrix mat of 1's (representing soldiers) and 0's (representing civilians).
The soldiers are positioned in front of the civilians.
That is, all the 1's will appear to the left of all the 0's in each row.

A row i is weaker than a row j if one of the following is true:
- The number of soldiers in row i is less than the number of soldiers in row j.
- Both rows have the same number of soldiers and i < j.

Return the indices of the k weakest rows in the matrix ordered from weakest to strongest.

Example 1:
Input: mat = [[1,1,0,0,0], [1,1,1,1,0], [1,0,0,0,0], [1,1,0,0,0], [1,1,1,1,1]], k = 3
Output: [2,0,3]
Explanation:
The number of soldiers in each row is:
- Row 0: 2
- Row 1: 4
- Row 2: 1
- Row 3: 2
- Row 4: 5
The rows ordered from weakest to strongest are [2,0,3,1,4].

Example 2:
Input: mat = [[1,0,0,0], [1,1,1,1], [1,0,0,0], [1,0,0,0]], k = 2
Output: [0,2]
Explanation:
The number of soldiers in each row is:
- Row 0: 1
- Row 1: 4
- Row 2: 1
- Row 3: 1
The rows ordered from weakest to strongest are [0,2,3,1].

Constraints:
m == mat.length
n == mat[i].length
2 <= n, m <= 100
1 <= k <= m
matrix[i][j] is either 0 or 1.
```

<details><summary>Hint</summary>

```text
1. Sort the matrix row indexes by the number of soldiers and then row indexes.
```

</details>

</details>

<details><summary>C</summary>

```c
struct Count {
    int soldiers;
    int index;
};
int compareStruct(const void* a1, const void* a2) {
    struct Count* p1 = (struct Count*)a1;
    struct Count* p2 = (struct Count*)a2;

    // ascending order
    if (p1->soldiers == p2->soldiers) {
        return (p1->index > p2->index);
    } else {
        return (p1->soldiers > p2->soldiers);
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* kWeakestRows(int** mat, int matSize, int* matColSize, int k, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    struct Count value[matSize];
    memset(value, 0, sizeof(value));
    int soldiers;
    int row, col;
    for (row = 0; row < matSize; ++row) {
        soldiers = 0;
        for (col = 0; col < matColSize[row]; ++col) {
            if (mat[row][col] == 0) {
                break;
            }
            soldiers++;
        }
        value[row].soldiers = soldiers;
        value[row].index = row;
    }
    qsort(value, matSize, sizeof(struct Count), compareStruct);

    pRetVal = (int*)malloc(matSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (matSize * sizeof(int)));

    int i;
    for (i = 0; i < k; ++i) {
        pRetVal[i] = value[i].index;
        (*returnSize)++;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        vector<int> retVal;

        vector<pair<int, int>> value;

        int matSize = mat.size();
        for (int row = 0; row < matSize; ++row) {
            int soldiers = 0;
            int matColSize = mat[row].size();
            for (int col = 0; col < matColSize; ++col) {
                if (mat[row][col] == 0) {
                    break;
                }
                soldiers++;
            }
            value.emplace_back(soldiers, row);
        }

        priority_queue heap(greater<pair<int, int>>(), move(value));
        for (int i = 0; i < k; ++i) {
            retVal.push_back(heap.top().second);
            heap.pop();
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def kWeakestRows(self, mat: List[List[int]], k: int) -> List[int]:
        retVal = []

        matSize = len(mat)

        value = []
        for row in range(matSize):
            soldiers = 0
            for col in mat[row]:
                if col == 0:
                    break
                soldiers += 1
            value.append([soldiers, row])

        heapify(value)
        for _ in range(k):
            retVal.append(heappop(value)[1])

        return retVal
```

</details>

## [1482. Minimum Number of Days to Make m Bouquets](https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/)  1945

- [Official](https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/editorial/)
- [Official](https://leetcode.cn/problems/minimum-number-of-days-to-make-m-bouquets/solutions/764671/zhi-zuo-m-shu-hua-suo-xu-de-zui-shao-tia-mxci/)

<details><summary>Description</summary>

```text
You are given an integer array bloomDay, an integer m and an integer k.

You want to make m bouquets. To make a bouquet, you need to use k adjacent flowers from the garden.

The garden consists of n flowers,
the ith flower will bloom in the bloomDay[i] and then can be used in exactly one bouquet.

Return the minimum number of days you need to wait to be able to make m bouquets from the garden.
If it is impossible to make m bouquets return -1.

Example 1:
Input: bloomDay = [1,10,3,10,2], m = 3, k = 1
Output: 3
Explanation: Let us see what happened in the first three days.
x means flower bloomed and _ means flower did not bloom in the garden.
We need 3 bouquets each should contain 1 flower.
After day 1: [x, _, _, _, _]   // we can only make one bouquet.
After day 2: [x, _, _, _, x]   // we can only make two bouquets.
After day 3: [x, _, x, _, x]   // we can make 3 bouquets. The answer is 3.

Example 2:
Input: bloomDay = [1,10,3,10,2], m = 3, k = 2
Output: -1
Explanation: We need 3 bouquets each has 2 flowers, that means we need 6 flowers.
We only have 5 flowers so it is impossible to get the needed bouquets and we return -1.

Example 3:
Input: bloomDay = [7,7,7,7,12,7,7], m = 2, k = 3
Output: 12
Explanation: We need 2 bouquets each should have 3 flowers.
Here is the garden after the 7 and 12 days:
After day 7: [x, x, x, x, _, x, x]
We can make one bouquet of the first three flowers that bloomed.
We cannot make another bouquet from the last three flowers that bloomed because they are not adjacent.
After day 12: [x, x, x, x, x, x, x]
It is obvious that we can make two bouquets in different ways.

Constraints:
bloomDay.length == n
1 <= n <= 10^5
1 <= bloomDay[i] <= 10^9
1 <= m <= 10^6
1 <= k <= n
```

<details><summary>Hint</summary>

```text
1. If we can make m or more bouquets at day x, then we can still make m or more bouquets at any day y > x.
2. We can check easily if we can make enough bouquets at day x if we can get group adjacent flowers at day x.
```

</details>

</details>

<details><summary>C</summary>

```c
int minDays(int* bloomDay, int bloomDaySize, int m, int k) {
    int retVal = -1;

    long flowers = (long)m * (long)k;
    if (flowers > bloomDaySize) {
        return retVal;
    }

    int left = 0;
    int right = bloomDay[0];
    int i;
    for (i = 1; i < bloomDaySize; ++i) {
        right = fmax(right, bloomDay[i]);
    }

    int bouquets, count;
    int middle;
    while (left <= right) {
        middle = (left + right) / 2;

        bouquets = 0;
        count = 0;
        for (i = 0; i < bloomDaySize; ++i) {
            if (bloomDay[i] <= middle) {
                count += 1;
            } else {
                count = 0;
            }

            if (count == k) {
                bouquets += 1;
                count = 0;
            }
        }

        if (bouquets >= m) {
            retVal = middle;
            right = middle - 1;
        } else {
            left = middle + 1;
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
    int minDays(vector<int>& bloomDay, int m, int k) {
        int retVal = -1;

        int bloomDaySize = bloomDay.size();
        long flowers = (long)m * (long)k;
        if (flowers > bloomDaySize) {
            return retVal;
        }

        int left = 0;
        int right = *max_element(bloomDay.begin(), bloomDay.end());
        while (left <= right) {
            int middle = (left + right) / 2;

            int bouquets = 0;
            int count = 0;
            for (int day : bloomDay) {
                if (day <= middle) {
                    count += 1;
                } else {
                    count = 0;
                }

                if (count == k) {
                    bouquets += 1;
                    count = 0;
                }
            }

            if (bouquets >= m) {
                retVal = middle;
                right = middle - 1;
            } else {
                left = middle + 1;
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
    def minDays(self, bloomDay: List[int], m: int, k: int) -> int:
        retVal = -1

        bloomDaySize = len(bloomDay)
        if m * k > bloomDaySize:
            return retVal

        left = 0
        right = max(bloomDay)
        while left <= right:
            middle = (left + right) // 2

            bouquets = 0
            count = 0
            for day in bloomDay:
                if day <= middle:
                    count += 1
                else:
                    count = 0

                if count == k:
                    bouquets += 1
                    count = 0

            if bouquets >= m:
                retVal = middle
                right = middle - 1
            else:
                left = middle + 1

        return retVal
```

</details>

## [1539. Kth Missing Positive Number](https://leetcode.com/problems/kth-missing-positive-number/)  1295

- [Official](https://leetcode.cn/problems/kth-missing-positive-number/solutions/391243/di-k-ge-que-shi-de-zheng-zheng-shu-by-leetcode-sol)

<details><summary>Description</summary>

```text
Given an array arr of positive integers sorted in a strictly increasing order, and an integer k.

Return the kth positive integer that is missing from this array.

Example 1:
Input: arr = [2,3,4,7,11], k = 5
Output: 9
Explanation: The missing positive integers are [1,5,6,8,9,10,12,13,...]. The 5th missing positive integer is 9.

Example 2:
Input: arr = [1,2,3,4], k = 2
Output: 6
Explanation: The missing positive integers are [5,6,7,...]. The 2nd missing positive integer is 6.

Constraints:
1 <= arr.length <= 1000
1 <= arr[i] <= 1000
1 <= k <= 1000
arr[i] < arr[j] for 1 <= i < j <= arr.length

Follow up:
Could you solve this problem in less than O(n) complexity?
```

<details><summary>Hint</summary>

```text
1. Keep track of how many positive numbers are missing as you scan the array.
```

</details>

</details>

<details><summary>C</summary>

```c
#define BINARY_SEARCH (1)
int findKthPositive(int *arr, int arrSize, int k) {
    int retVal = 0;

#if (BINARY_SEARCH)
    printf("BINARY_SEARCH\n");

    int left = 0;
    int right = arrSize;
    int middle;
    while (left < right) {
        middle = left + (right - left) / 2;
        if (arr[middle] - middle >= k + 1) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }
    retVal = k + left;
#else
    int i;
    for (i = 0; i < arrSize; ++i) {
        ++retVal;
        if (retVal != arr[i]) {
            --i;
            --k;
        }

        if (k == 0) {
            break;
        }
    }

    while (k > 0) {
        ++retVal;
        --k;
    }
#endif

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define BINARY_SEARCH (1)
   public:
    int findKthPositive(vector<int>& arr, int k) {
        int retVal = 0;

        int arrSize = arr.size();

#if (BINARY_SEARCH)
        cout << "BINARY_SEARCH\n";

        int left = 0;
        int right = arrSize;
        while (left < right) {
            int middle = left + (right - left) / 2;
            if (arr[middle] - middle >= k + 1) {
                right = middle;
            } else {
                left = middle + 1;
            }
        }
        retVal = k + left;
#else
        for (int i = 0; i < arrSize; ++i) {
            ++retVal;
            if (retVal != arr[i]) {
                --i;
                --k;
            }

            if (k == 0) {
                break;
            }
        }

        while (k > 0) {
            ++retVal;
            --k;
        }
#endif

        return retVal;
    }
};
```

</details>

## [1552. Magnetic Force Between Two Balls](https://leetcode.com/problems/magnetic-force-between-two-balls/)  1919

- [Official](https://leetcode.com/problems/magnetic-force-between-two-balls/editorial/)
- [Official](https://leetcode.cn/problems/magnetic-force-between-two-balls/solutions/403701/liang-qiu-zhi-jian-de-ci-li-by-leetcode-solution/)

<details><summary>Description</summary>

```text
In the universe Earth C-137,
Rick discovered a special form of magnetic force between two balls if they are put in his new invented basket.
Rick has n empty baskets, the ith basket is at position[i],
Morty has m balls and needs to distribute the balls into the baskets
such that the minimum magnetic force between any two balls is maximum.

Rick stated that magnetic force between two different balls at positions x and y is |x - y|.

Given the integer array position and the integer m. Return the required force.

Example 1:
Input: position = [1,2,3,4,7], m = 3
Output: 3
Explanation: Distributing the 3 balls into baskets 1, 4 and 7 will make the magnetic force between ball pairs [3, 3, 6].
The minimum magnetic force is 3. We cannot achieve a larger minimum magnetic force than 3.

Example 2:
Input: position = [5,4,3,2,1,1000000000], m = 2
Output: 999999999
Explanation: We can use baskets 1 and 1000000000.

Constraints:
n == position.length
2 <= n <= 10^5
1 <= position[i] <= 10^9
All integers in position are distinct.
2 <= m <= position.length
```

<details><summary>Hint</summary>

```text
1. If you can place balls such that the answer is x then you can do it for y where y < x.
2. Similarly if you cannot place balls such that the answer is x then you can do it for y where y > x.
3. Binary search on the answer and greedily see if it is possible.
```

</details>

</details>

<details><summary>C</summary>

```c
// Check if we can place 'm' balls at 'position' with each ball having at least 'x' gap.
bool canPlaceBalls(int x, int* position, int positionSize, int m) {
    bool retVal = false;

    // Place the first ball at the first position.
    int prevBallPos = position[0];
    int ballsPlaced = 1;

    // Iterate on each 'position' and place a ball there if we can place it.
    int currPos;
    int i;
    for (i = 1; i < positionSize && ballsPlaced < m; ++i) {
        currPos = position[i];

        // Check if we can place the ball at the current position.
        if (currPos - prevBallPos >= x) {
            ballsPlaced += 1;
            prevBallPos = currPos;
        }
    }
    // If all 'm' balls are placed, return 'true'.
    if (ballsPlaced == m) {
        retVal = true;
    }

    return retVal;
}
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int maxDistance(int* position, int positionSize, int m) {
    int retVal = 0;

    qsort(position, positionSize, sizeof(int), compareInteger);

    // Initial search space.
    int middle;
    int low = 1;
    int high = ceil(position[positionSize - 1] / (m - 1.0));
    while (low <= high) {
        middle = low + (high - low) / 2;

        // If we can place all balls having a gap at least 'mid',
        if (canPlaceBalls(middle, position, positionSize, m)) {
            retVal = middle;   // then 'mid' can be our answer,
            low = middle + 1;  // and discard the left half search space.
        } else {
            high = middle - 1;  // Discard the right half search space.
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
    // Check if we can place 'm' balls at 'position' with each ball having at least 'x' gap.
    bool canPlaceBalls(int x, vector<int>& position, int m) {
        bool retVal = false;

        int positionSize = position.size();

        // Place the first ball at the first position.
        int prevBallPos = position[0];
        int ballsPlaced = 1;

        // Iterate on each 'position' and place a ball there if we can place it.
        for (int i = 1; i < positionSize && ballsPlaced < m; ++i) {
            int currPos = position[i];

            // Check if we can place the ball at the current position.
            if (currPos - prevBallPos >= x) {
                ballsPlaced += 1;
                prevBallPos = currPos;
            }
        }
        // If all 'm' balls are placed, return 'true'.
        if (ballsPlaced == m) {
            retVal = true;
        }

        return retVal;
    }
    int maxDistance(vector<int>& position, int m) {
        int retVal = 0;

        int positionSize = position.size();

        sort(position.begin(), position.end());

        // Initial search space.
        int low = 1;
        int high = ceil(position[positionSize - 1] / (m - 1.0));
        while (low <= high) {
            int middle = low + (high - low) / 2;

            // If we can place all balls having a gap at least 'mid',
            if (canPlaceBalls(middle, position, m)) {
                retVal = middle;   // then 'mid' can be our answer,
                low = middle + 1;  // and discard the left half search space.
            } else {
                high = middle - 1;  // Discard the right half search space.
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
    # Check if we can place 'm' balls at 'position' with each ball having at least 'x' gap.
    def canPlaceBalls(self, x: int, position: List[int],  m: int) -> bool:
        retVal = False

        positionSize = len(position)

        # Place the first ball at the first position.
        prev_ball_pos = position[0]
        balls_placed = 1

        # Iterate on each 'position' and place a ball there if we can place it.
        for i in range(1, positionSize):

            # Check if we can place the ball at the current position.
            curr_pos = position[i]
            if curr_pos - prev_ball_pos >= x:
                balls_placed += 1
                prev_ball_pos = curr_pos

            # If all 'm' balls are placed, return 'True'.
            if balls_placed == m:
                retVal = True
                break

        return retVal

    def maxDistance(self, position: List[int], m: int) -> int:
        retVal = 0

        position.sort()

        # Initial search space.
        low = 1
        high = int(position[-1] / (m - 1.0)) + 1
        while low <= high:
            middle = low + (high - low) // 2

            # If we can place all balls having a gap at least 'mid',
            if self.canPlaceBalls(middle, position, m):
                retVal = middle    # then 'mid' can be our answer,
                low = middle + 1   # and discard the left half search space.
            else:
                high = middle - 1  # Discard the right half search space.

        return retVal
```

</details>

## [1671. Minimum Number of Removals to Make Mountain Array](https://leetcode.com/problems/minimum-number-of-removals-to-make-mountain-array/)  1912

- [Official](https://leetcode.com/problems/minimum-number-of-removals-to-make-mountain-array/editorial/)
- [Official](https://leetcode.cn/problems/minimum-number-of-removals-to-make-mountain-array/solutions/2570598/zui-chang-di-zeng-zi-xu-lie-by-leetcode-2ipno/)

<details><summary>Description</summary>

```text
You may recall that an array arr is a mountain array if and only if:
- arr.length >= 3
- There exists some index i (0-indexed) with 0 < i < arr.length - 1 such that:
  - arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
  - arr[i] > arr[i + 1] > ... > arr[arr.length - 1]

Given an integer array nums​​​, return the minimum number of elements to remove to make nums​​​ a mountain array.

Example 1:
Input: nums = [1,3,1]
Output: 0
Explanation: The array itself is a mountain array so we do not need to remove any elements.

Example 2:
Input: nums = [2,1,1,5,6,2,3,1]
Output: 3
Explanation: One solution is to remove the elements at indices 0, 1, and 5, making the array nums = [1,5,6,3,1].

Constraints:
3 <= nums.length <= 1000
1 <= nums[i] <= 10^9
It is guaranteed that you can make a mountain array out of nums.
```

<details><summary>Hint</summary>

```text
1. Think the opposite direction instead of minimum elements to remove the maximum mountain subsequence
2. Think of LIS it's kind of close
```

</details>

</details>

<details><summary>C</summary>

```c
int binarySearch(const int *seq, int seqSize, int target) {
    int retVal = 0;

    int middle;
    int left = 0;
    int right = seqSize;
    while (left < right) {
        middle = left + (right - left) / 2;
        if (seq[middle] >= target) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }
    retVal = left;

    return retVal;
}
int *getLISArray(const int *nums, int numsSize) {
    int *pRetVal = NULL;

    pRetVal = (int *)malloc(numsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int i;
    for (i = 0; i < numsSize; i++) {
        pRetVal[i] = 1;
    }

    int index;
    int seq[numsSize];
    int pos = 0;
    for (i = 0; i < numsSize; ++i) {
        index = binarySearch(seq, pos, nums[i]);
        if (index == pos) {
            seq[pos++] = nums[i];
            pRetVal[i] = pos;
        } else {
            seq[index] = nums[i];
            pRetVal[i] = index + 1;
        }
    }

    return pRetVal;
}
void reverse(int *nums, int numsSize) {
    int tmp;
    int i, j;
    for (i = 0, j = numsSize - 1; i < j; i++, j--) {
        tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
}
int minimumMountainRemovals(int *nums, int numsSize) {
    int retVal = 0;

    int *pre = getLISArray(nums, numsSize);
    if (pre == NULL) {
        free(pre);
        pre = NULL;
        return retVal;
    }
    reverse(nums, numsSize);

    int *suf = getLISArray(nums, numsSize);
    if (suf == NULL) {
        return retVal;
    }
    reverse(suf, numsSize);

    int i;
    for (i = 0; i < numsSize; ++i) {
        if ((pre[i] > 1) && (suf[i] > 1)) {
            retVal = fmax(retVal, pre[i] + suf[i] - 1);
        }
    }
    retVal = numsSize - retVal;

    //
    free(pre);
    pre = NULL;
    free(suf);
    suf = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> getLongestIncreasingSubsequenceLength(vector<int>& v) {
        vector<int> retVal;

        int vSize = v.size();
        retVal.resize(vSize, 1);

        vector<int> lis = {v[0]};
        for (int i = 1; i < vSize; i++) {
            int index = lower_bound(lis.begin(), lis.end(), v[i]) - lis.begin();
            int lisSize = lis.size();
            if (index == lisSize) {
                lis.push_back(v[i]);
            } else {
                lis[index] = v[i];
            }

            retVal[i] = lis.size();
        }

        return retVal;
    }
    int minimumMountainRemovals(vector<int>& nums) {
        int retVal = 0;

        vector<int> lisLength = getLongestIncreasingSubsequenceLength(nums);
        reverse(nums.begin(), nums.end());
        vector<int> ldsLength = getLongestIncreasingSubsequenceLength(nums);
        reverse(ldsLength.begin(), ldsLength.end());

        int numsSize = nums.size();
        retVal = numeric_limits<int>::max();
        for (int i = 0; i < numsSize; i++) {
            if ((lisLength[i] > 1) && (ldsLength[i] > 1)) {
                retVal = min(retVal, numsSize - lisLength[i] - ldsLength[i] + 1);
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
    def lowerBound(self, lis: List[int], target: int) -> int:
        retVal = 0

        left = 0
        right = len(lis)
        while left < right:
            mid = left + (right - left) // 2
            if lis[mid] < target:
                left = mid + 1
            else:
                right = mid
        retVal = left

        return retVal

    def getLongestIncreasingSubsequenceLength(self, v: List[int]) -> List[int]:
        retVal = None

        vSize = len(v)
        retVal = [1] * vSize
        lis = [v[0]]
        for i in range(1, vSize):
            index = self.lowerBound(lis, v[i])
            if index == len(lis):
                lis.append(v[i])
            else:
                lis[index] = v[i]

            retVal[i] = len(lis)

        return retVal

    def minimumMountainRemovals(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        lisLength = self.getLongestIncreasingSubsequenceLength(nums)
        nums.reverse()
        ldsLength = self.getLongestIncreasingSubsequenceLength(nums)
        ldsLength.reverse()

        retVal = float("inf")
        for i in range(numsSize):
            if (lisLength[i] > 1) and (ldsLength[i] > 1):
                retVal = min(retVal, numsSize - lisLength[i] - ldsLength[i] + 1)

        return retVal
```

</details>

## [1760. Minimum Limit of Balls in a Bag](https://leetcode.com/problems/minimum-limit-of-balls-in-a-bag/)  1939

- [Official](https://leetcode.com/problems/minimum-limit-of-balls-in-a-bag/editorial/)
- [Official](https://leetcode.cn/problems/minimum-limit-of-balls-in-a-bag/solutions/2025611/dai-zi-li-zui-shao-shu-mu-de-qiu-by-leet-boay/)

<details><summary>Description</summary>

```text
You are given an integer array nums where the ith bag contains nums[i] balls.
You are also given an integer maxOperations.

You can perform the following operation at most maxOperations times:
- Take any bag of balls and divide it into two new bags with a positive number of balls.
  - For example, a bag of 5 balls can become two new bags of 1 and 4 balls, or two new bags of 2 and 3 balls.

Your penalty is the maximum number of balls in a bag. You want to minimize your penalty after the operations.

Return the minimum possible penalty after performing the operations.

Example 1:
Input: nums = [9], maxOperations = 2
Output: 3
Explanation:
- Divide the bag with 9 balls into two bags of sizes 6 and 3. [9] -> [6,3].
- Divide the bag with 6 balls into two bags of sizes 3 and 3. [6,3] -> [3,3,3].
The bag with the most number of balls has 3 balls, so your penalty is 3 and you should return 3.

Example 2:
Input: nums = [2,4,8,2], maxOperations = 4
Output: 2
Explanation:
- Divide the bag with 8 balls into two bags of sizes 4 and 4. [2,4,8,2] -> [2,4,4,4,2].
- Divide the bag with 4 balls into two bags of sizes 2 and 2. [2,4,4,4,2] -> [2,2,2,4,4,2].
- Divide the bag with 4 balls into two bags of sizes 2 and 2. [2,2,2,4,4,2] -> [2,2,2,2,2,4,2].
- Divide the bag with 4 balls into two bags of sizes 2 and 2. [2,2,2,2,2,4,2] -> [2,2,2,2,2,2,2,2].
The bag with the most number of balls has 2 balls, so your penalty is 2, and you should return 2.

Constraints:
1 <= nums.length <= 10^5
1 <= maxOperations, nums[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Let's change the question if we know the maximum size of a bag what is the minimum number of bags you can make
2. note that as the maximum size increases the minimum number of bags decreases so we can binary search the maximum size
```

</details>

</details>

<details><summary>C</summary>

```c
bool isPossible(int maxBallsInBag, int* nums, int numsSize, int maxOperations) {
    bool retVal = true;  // We can split the balls within the allowed operations, return true

    int operations;
    int totalOperations = 0;
    for (int i = 0; i < numsSize; ++i) {
        // Calculate the number of operations needed to split this bag
        operations = ceil(nums[i] / (double)maxBallsInBag) - 1;
        totalOperations += operations;

        // Total operations exceed maxOperations, return false
        if (totalOperations > maxOperations) {
            retVal = false;
            break;
        }
    }

    return retVal;
}
int minimumSize(int* nums, int numsSize, int maxOperations) {
    int retVal = 0;

    // Perform binary search to find the optimal maxBallsInBag
    int left = 1;
    int right = 0;
    for (int i = 0; i < numsSize; ++i) {
        right = fmax(right, nums[i]);
    }
    int middle;
    while (left < right) {
        middle = (left + right) / 2;

        // Check if a valid distribution is possible with the current middle value
        if (isPossible(middle, nums, numsSize, maxOperations)) {
            right = middle;  // If possible, try a smaller value (shift right to middle)
        } else {
            left = middle + 1;  // If not possible, try a larger value (shift left to middle + 1)
        }
    }
    retVal = left;  // Return the smallest possible value for maxBallsInBag

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    bool isPossible(int maxBallsInBag, vector<int>& nums, int maxOperations) {
        bool retVal = true;  // We can split the balls within the allowed operations, return true

        int totalOperations = 0;
        for (int num : nums) {
            // Calculate the number of operations needed to split this bag
            int operations = ceil(num / (double)maxBallsInBag) - 1;
            totalOperations += operations;

            // Total operations exceed maxOperations, return false
            if (totalOperations > maxOperations) {
                retVal = false;
                break;
            }
        }

        return retVal;
    }

   public:
    int minimumSize(vector<int>& nums, int maxOperations) {
        int retVal = 0;

        // Perform binary search to find the optimal maxBallsInBag
        int left = 1;
        int right = 0;
        for (auto num : nums) {
            right = max(right, num);
        }
        while (left < right) {
            int middle = (left + right) / 2;

            // Check if a valid distribution is possible with the current middle value
            if (isPossible(middle, nums, maxOperations)) {
                right = middle;  // If possible, try a smaller value (shift right to middle)
            } else {
                left = middle + 1;  // If not possible, try a larger value (shift left to middle + 1)
            }
        }
        retVal = left;  // Return the smallest possible value for maxBallsInBag

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def isPossible(self, maxBallsInBag, nums, maxOperations) -> bool:
        retVal = True  # We can split the balls within the allowed operations, return True

        totalOperations = 0
        for num in nums:
            # Calculate the number of operations needed to split this bag
            operations = ceil(num / maxBallsInBag) - 1
            totalOperations += operations

            # If total operations exceed maxOperations, return False
            if totalOperations > maxOperations:
                retVal = False
                break

        return retVal

    def minimumSize(self, nums: List[int], maxOperations: int) -> int:
        retVal = 0

        # Perform binary search to find the optimal maxBallsInBag
        left = 1
        right = max(nums)
        while left < right:
            middle = (left + right) // 2

            # Check if a valid distribution is possible with the current middle value
            if self.isPossible(middle, nums, maxOperations):
                # If possible, try a smaller value (shift right to middle)
                right = middle
            else:
                # If not possible, try a larger value (shift left to middle + 1)
                left = middle + 1

        retVal = left  # Return the smallest possible value for maxBallsInBag

        return retVal
```

</details>

## [1802. Maximum Value at a Given Index in a Bounded Array](https://leetcode.com/problems/maximum-value-at-a-given-index-in-a-bounded-array/)  1929

- [Official](https://leetcode.com/problems/maximum-value-at-a-given-index-in-a-bounded-array/editorial/)
- [Official](https://leetcode.cn/problems/maximum-value-at-a-given-index-in-a-bounded-array/solutions/2042360/you-jie-shu-zu-zhong-zhi-ding-xia-biao-c-aav4/)

<details><summary>Description</summary>

```text
You are given three positive integers: n, index, and maxSum.
You want to construct an array nums (0-indexed) that satisfies the following conditions:
- nums.length == n
- nums[i] is a positive integer where 0 <= i < n.
- abs(nums[i] - nums[i+1]) <= 1 where 0 <= i < n-1.
- The sum of all the elements of nums does not exceed maxSum.
- nums[index] is maximized.
Return nums[index] of the constructed array.

Note that abs(x) equals x if x >= 0, and -x otherwise.

Example 1:
Input: n = 4, index = 2,  maxSum = 6
Output: 2
Explanation: nums = [1,2,2,1] is one array that satisfies all the conditions.
There are no arrays that satisfy all the conditions and have nums[2] == 3, so 2 is the maximum nums[2].

Example 2:
Input: n = 6, index = 1,  maxSum = 10
Output: 3

Constraints:
1 <= n <= maxSum <= 10^9
0 <= index < n
```

<details><summary>Hint</summary>

```text
1. What if the problem was instead determining if you could generate a valid array with nums[index] == target?
2. To generate the array, set nums[index] to target, nums[index-i] to target-i, and nums[index+i] to target-i.
   Then, this will give the minimum possible sum, so check if the sum is less than or equal to maxSum.
3. n is too large to actually generate the array,
   so you can use the formula 1 + 2 + ... + n = n * (n+1) / 2
   to quickly find the sum of nums[0...index] and nums[index...n-1].
4. Binary search for the target. If it is possible, then move the lower bound up.
   Otherwise, move the upper bound down.
```

</details>

</details>

<details><summary>C</summary>

```c
long getSum(int index, int value, int n) {
    long retVal = 0;

    // On index's left:
    // If value > index, there are index + 1 numbers in the arithmetic sequence:
    // [value - index, ..., value - 1, value].
    // Otherwise, there are value numbers in the arithmetic sequence:
    // [1, 2, ..., value - 1, value], plus a sequence of length (index - value + 1) of 1s.
    if (value > index) {
        retVal += (long)(value + value - index) * (index + 1) / 2;
    } else {
        retVal += (long)(value + 1) * value / 2 + index - value + 1;
    }

    // On index's right:
    // If value >= n - index, there are n - index numbers in the arithmetic sequence:
    // [value, value - 1, ..., value - n + 1 + index].
    // Otherwise, there are value numbers in the arithmetic sequence:
    // [value, value - 1, ..., 1], plus a sequence of length (n - index - value) of 1s.
    if (value >= n - index) {
        retVal += (long)(value + value - n + 1 + index) * (n - index) / 2;
    } else {
        retVal += (long)(value + 1) * value / 2 + n - index - value;
    }

    retVal -= value;

    return retVal;
}
int maxValue(int n, int index, int maxSum) {
    int retVal = 0;

    int middle;
    int left = 1;
    int right = maxSum;
    while (left < right) {
        middle = (left + right + 1) / 2;
        // 1 <= n <= maxSum <= 10^9, 0 <= index < n
        if (getSum(index, middle, n) <= maxSum) {
            left = middle;
        } else {
            right = middle - 1;
        }
    }
    retVal = left;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long getSum(int index, int value, int n) {
        long retVal = 0;

        // On index's left:
        // If value > index, there are index + 1 numbers in the arithmetic sequence:
        // [value - index, ..., value - 1, value].
        // Otherwise, there are value numbers in the arithmetic sequence:
        // [1, 2, ..., value - 1, value], plus a sequence of length (index - value + 1) of 1s.
        if (value > index) {
            retVal += (long)(value + value - index) * (index + 1) / 2;
        } else {
            retVal += (long)(value + 1) * value / 2 + index - value + 1;
        }

        // On index's right:
        // If value >= n - index, there are n - index numbers in the arithmetic sequence:
        // [value, value - 1, ..., value - n + 1 + index].
        // Otherwise, there are value numbers in the arithmetic sequence:
        // [value, value - 1, ..., 1], plus a sequence of length (n - index - value) of 1s.
        if (value >= n - index) {
            retVal += (long)(value + value - n + 1 + index) * (n - index) / 2;
        } else {
            retVal += (long)(value + 1) * value / 2 + n - index - value;
        }

        retVal -= value;

        return retVal;
    }
    int maxValue(int n, int index, int maxSum) {
        int retVal = 0;

        int middle;
        int left = 1;
        int right = maxSum;
        while (left < right) {
            middle = (left + right + 1) / 2;
            // 1 <= n <= maxSum <= 10^9, 0 <= index < n
            if (getSum(index, middle, n) <= maxSum) {
                left = middle;
            } else {
                right = middle - 1;
            }
        }
        retVal = left;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def getSum(self, index: int, value: int, n: int) -> int:
        retVal = 0

        count = 0

        # On index's left:
        # If value > index, there are index + 1 numbers in the arithmetic sequence:
        # [value - index, ..., value - 1, value].
        # Otherwise, there are value numbers in the arithmetic sequence:
        # [1, 2, ..., value - 1, value], plus a sequence of length (index - value + 1) of 1s.
        if value > index:
            count += (value + value - index) * (index + 1) // 2
        else:
            count += (value + 1) * value // 2 + index - value + 1

        # On index's right:
        # If value >= n - index, there are n - index numbers in the arithmetic sequence:
        # [value, value - 1, ..., value - n + 1 + index].
        # Otherwise, there are value numbers in the arithmetic sequence:
        # [value, value - 1, ..., 1], plus a sequence of length (n - index - value) of 1s.
        if value >= n - index:
            count += (value + value - n + 1 + index) * (n - index) // 2
        else:
            count += (value + 1) * value // 2 + n - index - value

        retVal = count - value

        return retVal

    def maxValue(self, n: int, index: int, maxSum: int) -> int:
        retVal = 0

        left = 1
        right = maxSum
        while left < right:
            middle = (left + right + 1) // 2
            if self.getSum(index, middle, n) <= maxSum:
                left = middle
            else:
                right = middle - 1
        retVal = left

        return retVal
```

</details>

## [1870. Minimum Speed to Arrive on Time](https://leetcode.com/problems/minimum-speed-to-arrive-on-time/)  1675

- [Official](https://leetcode.com/problems/minimum-speed-to-arrive-on-time/editorial/)
- [Official](https://leetcode.cn/problems/minimum-speed-to-arrive-on-time/solutions/791412/zhun-shi-dao-da-de-lie-che-zui-xiao-shi-tl9df/)

<details><summary>Description</summary>

```text
You are given a floating-point number hour, representing the amount of time you have to reach the office.
To commute to the office, you must take n trains in sequential order.
You are also given an integer array dist of length n,
where dist[i] describes the distance (in kilometers) of the ith train ride.

Each train can only depart at an integer hour, so you may need to wait in between each train ride.
- For example, if the 1st train ride takes 1.5 hours,
  you must wait for an additional 0.5 hours before you can depart on the 2nd train ride at the 2 hour mark.
Return the minimum positive integer speed (in kilometers per hour) that all the trains must travel
at for you to reach the office on time, or -1 if it is impossible to be on time.

Tests are generated such that the answer will not exceed 10^7
and hour will have at most two digits after the decimal point.

Example 1:
Input: dist = [1,3,2], hour = 6
Output: 1
Explanation: At speed 1:
- The first train ride takes 1/1 = 1 hour.
- Since we are already at an integer hour, we depart immediately at the 1 hour mark.
  The second train takes 3/1 = 3 hours.
- Since we are already at an integer hour, we depart immediately at the 4 hour mark.
  The third train takes 2/1 = 2 hours.
- You will arrive at exactly the 6 hour mark.

Example 2:
Input: dist = [1,3,2], hour = 2.7
Output: 3
Explanation: At speed 3:
- The first train ride takes 1/3 = 0.33333 hours.
- Since we are not at an integer hour, we wait until the 1 hour mark to depart.
  The second train ride takes 3/3 = 1 hour.
- Since we are already at an integer hour, we depart immediately at the 2 hour mark.
  The third train takes 2/3 = 0.66667 hours.
- You will arrive at the 2.66667 hour mark.

Example 3:
Input: dist = [1,3,2], hour = 1.9
Output: -1
Explanation: It is impossible because the earliest the third train can depart is at the 2 hour mark.

Constraints:
n == dist.length
1 <= n <= 10^5
1 <= dist[i] <= 10^5
1 <= hour <= 10^9
There will be at most two digits after the decimal point in hour.
```

<details><summary>Hint</summary>

```text
1. Given the speed the trains are traveling at, can you find the total time it takes for you to arrive?
2. Is there a cutoff where any speeds larger will always allow you to arrive on time?
```

</details>

</details>

<details><summary>C</summary>

```c
int minSpeedOnTime(int* dist, int distSize, double hour) {
    int retVal = -1;

    if ((double)(distSize - 1) >= hour) {
        return retVal;
    }

    int i;
    double totalHour;
    int middle;
    // Tests are generated such that the answer will not exceed 10^7
    // and hour will have at most two digits after the decimal point.
    int left = 1;
    int right = 1e7;
    while (left < right) {
        middle = left + (right - left) / 2;

        /* Example: dist = [1,3,2], hour = 2.7
         *  Speed   Time Required
         *    1     (1/1) + (3/1) + (2/1) = 6
         *    2     (1/2) + (3/2) + (2/2) = 1 + 2 + 1 = 4
         *    3     (1/3) + (3/3) + (2/3) = 1 + 1 + 0.67 = 2.67
         *
         *   10^7
         */
        totalHour = 0;
        for (i = 0; i < distSize - 1; ++i) {
            totalHour += ((dist[i] + middle - 1) / middle);
        }
        totalHour += (((double)dist[i]) / middle);

        if (totalHour > hour) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    retVal = left;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minSpeedOnTime(vector<int>& dist, double hour) {
        int retVal = -1;

        int distSize = dist.size();
        if ((double)(distSize - 1) >= hour) {
            return retVal;
        }

        // Tests are generated such that the answer will not exceed 10^7
        // and hour will have at most two digits after the decimal point.
        int left = 1;
        int right = 1e7;
        while (left < right) {
            int middle = left + (right - left) / 2;

            /* Example: dist = [1,3,2], hour = 2.7
             *  Speed   Time Required
             *    1     (1/1) + (3/1) + (2/1) = 6
             *    2     (1/2) + (3/2) + (2/2) = 1 + 2 + 1 = 4
             *    3     (1/3) + (3/3) + (2/3) = 1 + 1 + 0.67 = 2.67
             *
             *   10^7
             */
            double totalHour = 0;
            int i;
            for (i = 0; i < distSize - 1; ++i) {
                totalHour += ((dist[i] + middle - 1) / middle);
            }
            totalHour += (((double)dist[i]) / middle);

            if (totalHour > hour) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }
        retVal = left;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minSpeedOnTime(self, dist: List[int], hour: float) -> int:
        retVal = -1

        distSize = len(dist)
        if (distSize - 1) >= hour:
            return retVal

        # Tests are generated such that the answer will not exceed 10 ^ 7
        # and hour will have at most two digits after the decimal point.
        left = 1
        right = 1e7
        while left < right:
            middle = left + (right - left) // 2

            # /* Example: dist = [1,3,2], hour = 2.7
            #  *  Speed   Time Required
            #  *    1     (1/1) + (3/1) + (2/1) = 6
            #  *    2     (1/2) + (3/2) + (2/2) = 1 + 2 + 1 = 4
            #  *    3     (1/3) + (3/3) + (2/3) = 1 + 1 + 0.67 = 2.67
            #  *
            #  *   10^7
            #  */
            totalHour = 0
            for i in range(distSize - 1):
                totalHour += ((dist[i] + middle - 1) // middle)
            totalHour += (dist[distSize - 1] / middle)

            if totalHour > hour:
                left = middle + 1
            else:
                right = middle

        retVal = int(left)

        return retVal
```

</details>

## [1964. Find the Longest Valid Obstacle Course at Each Position](https://leetcode.com/problems/find-the-longest-valid-obstacle-course-at-each-position/)  1933

- [Official](https://leetcode.com/problems/find-the-longest-valid-obstacle-course-at-each-position/editorial/)
- [Official](https://leetcode.cn/problems/find-the-longest-valid-obstacle-course-at-each-position/solutions/922831/zhao-chu-dao-mei-ge-wei-zhi-wei-zhi-zui-pb8mu/)

<details><summary>Description</summary>

```text
You want to build some obstacle courses.
You are given a 0-indexed integer array obstacles of length n, where obstacles[i] describes the height of the ith obstacle.

For every index i between 0 and n - 1 (inclusive), find the length of the longest obstacle course in obstacles such that:
- You choose any number of obstacles between 0 and i inclusive.
- You must include the ith obstacle in the course.
- You must put the chosen obstacles in the same order as they appear in obstacles.
- Every obstacle (except the first) is taller than or the same height as the obstacle immediately before it.

Return an array ans of length n, where ans[i] is the length of the longest obstacle course for index i as described above.

Example 1:
Input: obstacles = [1,2,3,2]
Output: [1,2,3,3]
Explanation: The longest valid obstacle course at each position is:
- i = 0: [1], [1] has length 1.
- i = 1: [1,2], [1,2] has length 2.
- i = 2: [1,2,3], [1,2,3] has length 3.
- i = 3: [1,2,3,2], [1,2,2] has length 3.

Example 2:
Input: obstacles = [2,2,1]
Output: [1,2,1]
Explanation: The longest valid obstacle course at each position is:
- i = 0: [2], [2] has length 1.
- i = 1: [2,2], [2,2] has length 2.
- i = 2: [2,2,1], [1] has length 1.

Example 3:
Input: obstacles = [3,1,5,6,4,2]
Output: [1,1,2,3,2,2]
Explanation: The longest valid obstacle course at each position is:
- i = 0: [3], [3] has length 1.
- i = 1: [3,1], [1] has length 1.
- i = 2: [3,1,5], [3,5] has length 2. [1,5] is also valid.
- i = 3: [3,1,5,6], [3,5,6] has length 3. [1,5,6] is also valid.
- i = 4: [3,1,5,6,4], [3,4] has length 2. [1,4] is also valid.
- i = 5: [3,1,5,6,4,2], [1,2] has length 2.

Constraints:
n == obstacles.length
1 <= n <= 10^5
1 <= obstacles[i] <= 10^7
```

<details><summary>Hint</summary>

```text
1. Can you keep track of the minimum height for each obstacle course length?
2. You can use binary search to find the longest previous obstacle course length that satisfies the conditions.
```

</details>

</details>

<details><summary>C</summary>

```c
#define BINARY_SEARCH (1)
#define DYNAMIC_PROGRAMMING (1)  // Time Limit Exceeded
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* longestObstacleCourseAtEachPosition(int* obstacles, int obstaclesSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = obstaclesSize;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));

#if (BINARY_SEARCH)
    printf("BINARY_SEARCH\n");

    int greedy[obstaclesSize];
    memset(greedy, 0, sizeof(greedy));
    greedy[0] = obstacles[0];

    pRetVal[0] = 1;
    int position = 1;

    int left, right, middle;
    int i;
    for (i = 1; i < obstaclesSize; ++i) {
        if (obstacles[i] >= greedy[position - 1]) {
            greedy[position++] = obstacles[i];
            pRetVal[i] = position;
            continue;
        }

        left = 0;
        right = position - 1;
        while (left < right) {
            middle = left + (right - left) / 2;
            if (obstacles[i] >= greedy[middle]) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }
        greedy[right] = obstacles[i];
        pRetVal[i] = right + 1;
    }
#elif (DYNAMIC_PROGRAMMING)
    printf("DYNAMIC_PROGRAMMING: Time Limit Exceeded\n");

    int dp[obstaclesSize];
    memset(dp, 0, sizeof(dp));
    int i, j;
    for (i = 0; i < obstaclesSize; ++i) {
        dp[i] = 1;
        for (j = 0; j < i; ++j) {
            if (obstacles[j] <= obstacles[i]) {
                dp[i] = fmax(dp[i], dp[j] + 1);
            }
        }
    }
    memcpy(pRetVal, dp, ((*returnSize) * sizeof(int)));
#endif

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
#define BINARY_SEARCH (1)
#define DYNAMIC_PROGRAMMING (1)  // Time Limit Exceeded
class Solution {
   public:
    Solution() {
#if (BINARY_SEARCH)
        cout << "BINARY_SEARCH\n";
#elif (DYNAMIC_PROGRAMMING)
        cout << "DYNAMIC_PROGRAMMING: Time Limit Exceeded\n";
#endif
        cout << "\n";
    }
    vector<int> longestObstacleCourseAtEachPosition(vector<int>& obstacles) {
        vector<int> retVal;

#if (BINARY_SEARCH)
        vector<int> greedy;
        for (int obstacle : obstacles) {
            if ((greedy.empty() == true) || (obstacle >= greedy.back())) {
                greedy.push_back(obstacle);
                retVal.push_back(greedy.size());
            } else {
                int position = upper_bound(greedy.begin(), greedy.end(), obstacle) - greedy.begin();
                retVal.push_back(position + 1);
                greedy[position] = obstacle;
            }
        }
#elif (DYNAMIC_PROGRAMMING)
        int obstaclesSize = obstacles.size();
        vector<int> dp(obstaclesSize, 1);
        for (int i = 0; i < obstaclesSize; ++i) {
            for (int j = 0; j < i; ++j) {
                if (obstacles[j] <= obstacles[i]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        retVal.assign(dp.begin(), dp.end());
#endif

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def __init__(self):
        self.method = 1

        if self.method == 1:
            print("BINARY_SEARCH")
        elif self.method == 2:
            print("DYNAMIC_PROGRAMMING: Time Limit Exceeded")
        print()

    def longestObstacleCourseAtEachPosition(self, obstacles: List[int]) -> List[int]:
        retVal = []

        if self.method == 1:
            greedy = []
            for obstacle in obstacles:
                if not greedy or obstacle >= greedy[-1]:
                    greedy.append(obstacle)
                    retVal.append(len(greedy))
                else:
                    position = bisect_right(greedy, obstacle)
                    retVal.append(position + 1)
                    greedy[position] = obstacle
        elif self.method == 2:
            obstaclesSize = len(obstacles)
            dp = [1] * obstaclesSize
            for i in range(obstaclesSize):
                for j in range(i):
                    if (obstacles[j] <= obstacles[i]):
                        dp[i] = max(dp[i], dp[j] + 1)
            retVal = dp

        return retVal
```

</details>
