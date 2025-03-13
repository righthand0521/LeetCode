# [Binary Search](https://en.wikipedia.org/wiki/Binary_search_algorithm)

## [4. Median of Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/)

- [Official](https://leetcode.com/problems/median-of-two-sorted-arrays/editorial)
- [Official](https://leetcode.cn/problems/median-of-two-sorted-arrays/solutions/258842/xun-zhao-liang-ge-you-xu-shu-zu-de-zhong-wei-s-114/)

<details><summary>Description</summary>

```text
Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.

The overall run time complexity should be O(log (m+n)).

Example 1:
Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.

Example 2:
Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.

Constraints:
nums1.length == m
nums2.length == n
0 <= m <= 1000
0 <= n <= 1000
1 <= m + n <= 2000
-10^6 <= nums1[i], nums2[i] <= 10^6
```

</details>

<details><summary>C</summary>

```c
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    double retVal = 0;

    int total = nums1Size + nums2Size;
    int merge[total];
    memset(merge, 0, total * sizeof(int));

    int idx1 = 0;
    int idx2 = 0;
    int idx;
    for (idx = 0; idx < total; ++idx) {
        if ((idx1 == nums1Size) || (idx2 == nums2Size)) {
            break;
        }
        merge[idx] = (nums1[idx1] < nums2[idx2]) ? nums1[idx1++] : nums2[idx2++];
    }
    while (idx < total) {
        if (idx1 == nums1Size) {
            merge[idx] = nums2[idx2++];
        } else if (idx2 == nums2Size) {
            merge[idx] = nums1[idx1++];
        }
        idx++;
    }

    if ((total % 2) == 1) {
        retVal = merge[total / 2];
    } else {
        retVal = merge[total / 2 - 1] + merge[total / 2];
        retVal /= 2.0;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        double retVal = 0;

        int len1 = nums1.size();
        int len2 = nums2.size();
        int len = len1 + len2;
        vector<int> numsMerge(len);
        merge(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), numsMerge.begin());

        if (len % 2 == 1) {
            retVal = numsMerge[len / 2];
        } else {
            retVal = (double)(numsMerge[len / 2 - 1] + numsMerge[len / 2]) / 2;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        retVal = 0

        numsMerge = sorted(nums1 + nums2)
        numsMergeSize = len(numsMerge)

        if numsMergeSize % 2 == 1:
            retVal = float(numsMerge[numsMergeSize // 2])
        else:
            retVal = float((numsMerge[numsMergeSize // 2 - 1] + numsMerge[numsMergeSize // 2]) / 2)

        return retVal
```

</details>

## [33. Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/)

- [Official](https://leetcode.com/problems/search-in-rotated-sorted-array/editorial/)
- [Official](https://leetcode.cn/problems/search-in-rotated-sorted-array/solutions/220083/sou-suo-xuan-zhuan-pai-xu-shu-zu-by-leetcode-solut/)

<details><summary>Description</summary>

```text
There is an integer array nums sorted in ascending order (with distinct values).

Prior to being passed to your function, nums is possibly rotated at an unknown pivot index k (1 <= k < nums.length)
such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed).
For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become [4,5,6,7,0,1,2].

Given the array nums after the possible rotation and an integer target,
return the index of target if it is in nums, or -1 if it is not in nums.

You must write an algorithm with O(log n) runtime complexity.

Example 1:
Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4

Example 2:
Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1

Example 3:
Input: nums = [1], target = 0
Output: -1

Constraints:
1 <= nums.length <= 5000
-10^4 <= nums[i] <= 10^4
All values of nums are unique.
nums is an ascending array that is possibly rotated.
-10^4 <= target <= 10^4
```

</details>

<details><summary>C</summary>

```c
int search(int* nums, int numsSize, int target) {
    int retVal = -1;

    int middle;
    int left = 0;
    int right = numsSize - 1;
    while (left <= right) {
        middle = left + (right - left) / 2;
        if (nums[middle] == target) {
            retVal = middle;
            break;
        } else if (nums[middle] >= nums[left]) {
            if ((target >= nums[left]) && (target < nums[middle])) {
                right = middle - 1;
            } else {
                left = middle + 1;
            }
        } else {
            if ((target <= nums[right]) && (target > nums[middle])) {
                left = middle + 1;
            } else {
                right = middle - 1;
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
    int search(vector<int>& nums, int target) {
        int retVal = -1;

        int left = 0;
        int right = nums.size() - 1;
        while (left <= right) {
            int middle = left + (right - left) / 2;
            if (nums[middle] == target) {
                retVal = middle;
                break;
            } else if (nums[middle] >= nums[left]) {
                if ((target >= nums[left]) && (target < nums[middle])) {
                    right = middle - 1;
                } else {
                    left = middle + 1;
                }
            } else {
                if ((target <= nums[right]) && (target > nums[middle])) {
                    left = middle + 1;
                } else {
                    right = middle - 1;
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
    def search(self, nums: List[int], target: int) -> int:
        retVal = -1

        left = 0
        right = len(nums) - 1
        while left <= right:
            middle = left + (right - left) // 2
            if nums[middle] == target:
                retVal = middle
                break
            elif nums[middle] >= nums[left]:
                if (target >= nums[left]) and (target < nums[middle]):
                    right = middle - 1
                else:
                    left = middle + 1
            else:
                if (target <= nums[right]) and (target > nums[middle]):
                    left = middle + 1
                else:
                    right = middle - 1

        return retVal
```

</details>

## [34. Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/)

- [Official](https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/solutions/504484/zai-pai-xu-shu-zu-zhong-cha-zhao-yuan-su-de-di-3-4/)

<details><summary>Description</summary>

```text
Given an array of integers nums sorted in non-decreasing order,
find the starting and ending position of a given target value.

If target is not found in the array, return [-1, -1].

You must write an algorithm with O(log n) runtime complexity.

Example 1:
Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]

Example 2:
Input: nums = [5,7,7,8,8,10], target = 6
Output: [-1,-1]

Example 3:
Input: nums = [], target = 0
Output: [-1,-1]

Constraints:
0 <= nums.length <= 10^5
-109 <= nums[i] <= 10^9
nums is a non-decreasing array.
-10^9 <= target <= 10^9
```

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 2;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    pRetVal[0] = -1;
    pRetVal[1] = -1;

    if (numsSize == 0) {
        return pRetVal;
    }
    int left, right, middle;

    left = 0;
    right = numsSize - 1;
    while (left < right) {
        middle = left + (right - left) / 2;
        if (nums[middle] >= target) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }
    if (nums[right] != target) {
        return pRetVal;
    }
    pRetVal[0] = right;

    left = 0;
    right = numsSize - 1;
    while (left < right) {
        middle = right - (right - left) / 2;
        if (nums[middle] <= target) {
            left = middle;
        } else {
            right = middle - 1;
        }
    }
    if (nums[right] != target) {
        pRetVal[0] = -1;
        return pRetVal;
    }
    pRetVal[1] = left;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> retVal(2, -1);

        int numsSize = nums.size();
        if (numsSize == 0) {
            return retVal;
        }
        int left, right, middle;

        left = 0;
        right = numsSize - 1;
        while (left < right) {
            middle = left + (right - left) / 2;
            if (nums[middle] >= target) {
                right = middle;
            } else {
                left = middle + 1;
            }
        }
        if (nums[right] != target) {
            return retVal;
        }
        retVal[0] = right;

        left = 0;
        right = numsSize - 1;
        while (left < right) {
            middle = right - (right - left) / 2;
            if (nums[middle] <= target) {
                left = middle;
            } else {
                right = middle - 1;
            }
        }
        if (nums[right] != target) {
            retVal[0] = -1;
            return retVal;
        }
        retVal[1] = left;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def searchRange(self, nums: List[int], target: int) -> List[int]:
        retVal = [-1, -1]

        numsSize = len(nums)
        if numsSize == 0:
            return retVal

        left = 0
        right = numsSize - 1
        while left < right:
            middle = left + (right - left) // 2
            if nums[middle] >= target:
                right = middle
            else:
                left = middle + 1
        if nums[right] != target:
            return retVal
        retVal[0] = right

        left = 0
        right = numsSize - 1
        while left < right:
            middle = right - (right - left) // 2
            if nums[middle] <= target:
                left = middle
            else:
                right = middle - 1
        if nums[right] != target:
            retVal[0] = -1
            return retVal
        retVal[1] = left

        return retVal
```

</details>

## [35. Search Insert Position](https://leetcode.com/problems/search-insert-position/)

- [Official](https://leetcode.cn/problems/search-insert-position/solutions/333632/sou-suo-cha-ru-wei-zhi-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given a sorted array of distinct integers and a target value, return the index if the target is found.
If not, return the index where it would be if it were inserted in order.

You must write an algorithm with O(log n) runtime complexity.

Example 1:
Input: nums = [1,3,5,6], target = 5
Output: 2

Example 2:
Input: nums = [1,3,5,6], target = 2
Output: 1

Example 3:
Input: nums = [1,3,5,6], target = 7
Output: 4

Constraints:
1 <= nums.length <= 10^4
-10^4 <= nums[i] <= 10^4
nums contains distinct values sorted in ascending order.
-10^4 <= target <= 10^4
```

</details>

<details><summary>C</summary>

```c
int searchInsert(int* nums, int numsSize, int target) {
    int retVal = 0;

    int middle;
    int left = 0;
    int right = numsSize - 1;
    while (left <= right) {
        middle = left + (right - left) / 2;
        if (nums[middle] < target) {
            left = middle + 1;
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
    int searchInsert(vector<int>& nums, int target) {
        int retVal = 0;

        int left = 0;
        int right = nums.size() - 1;
        while (left <= right) {
            int middle = left + (right - left) / 2;
            if (nums[middle] < target) {
                left = middle + 1;
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
    def searchInsert(self, nums: List[int], target: int) -> int:
        retVal = 0

        left = 0
        right = len(nums) - 1
        while left <= right:
            middle = left + (right - left) // 2
            if nums[middle] < target:
                left = middle + 1
            else:
                right = middle - 1
        retVal = left

        return retVal
```

</details>

## [74. Search a 2D Matrix](https://leetcode.com/problems/search-a-2d-matrix/)

- [Official](https://leetcode.cn/problems/search-a-2d-matrix/solutions/688117/sou-suo-er-wei-ju-zhen-by-leetcode-solut-vxui/)

<details><summary>Description</summary>

```text
Write an efficient algorithm that searches for a value target in an m x n integer matrix matrix.
This matrix has the following properties:
- Integers in each row are sorted from left to right.
- The first integer of each row is greater than the last integer of the previous row.

Example 1:
Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
Output: true

Example 2:
Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
Output: false

Constraints:
m == matrix.length
n == matrix[i].length
1 <= m, n <= 100
-10^4 <= matrix[i][j], target <= 10^4
```

</details>

<details><summary>C</summary>

```c
#define BINARY_SEARCH (0)
bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target) {
    bool retVal = false;

    // m == matrix.length, n == matrix[i].length, 1 <= m, n <= 100
    int matrixRow = matrixSize;
    int matrixCol = matrixColSize[0];

#if (BINARY_SEARCH)
    int middle, middleValue;
    int left = 0;
    int right = matrixRow * matrixCol - 1;
    while (left <= right) {
        middle = left + (right - left) / 2;

        middleValue = matrix[middle / matrixCol][middle % matrixCol];
        if (middleValue == target) {
            retVal = true;
            break;
        } else if (middleValue < target) {
            left = middle + 1;
        } else if (middleValue > target) {
            right = middle - 1;
        }
    }
#else
    /* Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3; Output: true
     *      0  1  2   3  |  0  1  2   3  |  0  1   2  3
     *  0   1  3  5  [7] |  1  3 [5]  7  |  1 [3]  5  7
     *  1  10 11 16  20  | 10 11 16  20  | 10 11  16 20
     *  2  23 30 34  60  | 23 30 34  60  | 23 30  34 60
     *
     * Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13; Output: false
     *      0  1  2   3  |  0  1  2   3  |  0   1   2   3 |  0   1   2  3 |  0   1   2  3 |   0   1  2  3
     *  0   1  3  5  [7] |  1  3  5   7  |  1   3   5   7 |  1   3   5  7 |  1   3   5  7 |   1   3  5  7
     *  1  10 11 16  20  | 10 11 16 [20] | 10  11 [16] 20 | 10 [11] 16 20 | 10  11  16 20 |  10  11 16 20
     *  2  23 30 34  60  | 23 30 34  60  | 23  30  34  60 | 23  30  34 60 | 23 [30] 34 60 | [23] 30 34 60
     */
    int value;
    int row = 0;
    int col = matrixCol - 1;
    while ((row < matrixRow) && (col >= 0)) {
        value = matrix[row][col];
        if (value == target) {
            retVal = true;
            break;
        } else if (value < target) {
            row++;
        } else if (value > target) {
            col--;
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
#define BINARY_SEARCH (0)
   public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        bool retVal = false;

        // m == matrix.length, n == matrix[i].length, 1 <= m, n <= 100
        int matrixRowSize = matrix.size();
        int matrixColSize = matrix[0].size();

#if (BINARY_SEARCH)
        int left = 0;
        int right = matrixRowSize * matrixColSize - 1;
        while (left <= right) {
            int middle = left + (right - left) / 2;

            int middleValue = matrix[middle / matrixColSize][middle % matrixColSize];
            if (middleValue == target) {
                retVal = true;
                break;
            } else if (middleValue < target) {
                left = middle + 1;
            } else if (middleValue > target) {
                right = middle - 1;
            }
        }
#else
        /* Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3; Output: true
         *      0  1  2   3  |  0  1  2   3  |  0  1   2  3
         *  0   1  3  5  [7] |  1  3 [5]  7  |  1 [3]  5  7
         *  1  10 11 16  20  | 10 11 16  20  | 10 11  16 20
         *  2  23 30 34  60  | 23 30 34  60  | 23 30  34 60
         *
         * Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13; Output: false
         *      0  1  2   3  |  0  1  2   3  |  0   1   2   3 |  0   1   2  3 |  0   1   2  3 |   0   1  2  3
         *  0   1  3  5  [7] |  1  3  5   7  |  1   3   5   7 |  1   3   5  7 |  1   3   5  7 |   1   3  5  7
         *  1  10 11 16  20  | 10 11 16 [20] | 10  11 [16] 20 | 10 [11] 16 20 | 10  11  16 20 |  10  11 16 20
         *  2  23 30 34  60  | 23 30 34  60  | 23  30  34  60 | 23  30  34 60 | 23 [30] 34 60 | [23] 30 34 60
         */
        int row = 0;
        int col = matrixColSize - 1;
        while ((row < matrixRowSize) && (col >= 0)) {
            int value = matrix[row][col];
            if (value == target) {
                retVal = true;
                break;
            } else if (value < target) {
                row++;
            } else if (value > target) {
                col--;
            }
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
    def __init__(self) -> None:
        self.method = 2

    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
        retVal = False

        # m == matrix.length, n == matrix[i].length, 1 <= m, n <= 100
        rowSize = len(matrix)
        colSize = len(matrix[0])

        if self.method == 1:    # Binary Search
            left = 0
            right = rowSize * colSize - 1
            while left <= right:
                middle = left + (right - left) // 2
                middleValue = matrix[middle//colSize][middle % colSize]
                if middleValue == target:
                    retVal = True
                    break
                elif middleValue < target:
                    left = middle + 1
                elif middleValue > target:
                    right = middle - 1
        elif self.method == 2:
            # /* Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3; Output: true
            #  *      0  1  2   3  |  0  1  2   3  |  0  1   2  3
            #  *  0   1  3  5  [7] |  1  3 [5]  7  |  1 [3]  5  7
            #  *  1  10 11 16  20  | 10 11 16  20  | 10 11  16 20
            #  *  2  23 30 34  60  | 23 30 34  60  | 23 30  34 60
            #  *
            #  * Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13; Output: false
            #  *      0  1  2   3  |  0  1  2   3  |  0   1   2   3 |  0   1   2  3 |  0   1   2  3 |   0   1  2  3
            #  *  0   1  3  5  [7] |  1  3  5   7  |  1   3   5   7 |  1   3   5  7 |  1   3   5  7 |   1   3  5  7
            #  *  1  10 11 16  20  | 10 11 16 [20] | 10  11 [16] 20 | 10 [11] 16 20 | 10  11  16 20 |  10  11 16 20
            #  *  2  23 30 34  60  | 23 30 34  60  | 23  30  34  60 | 23  30  34 60 | 23 [30] 34 60 | [23] 30 34 60
            #  */
            row = 0
            col = colSize - 1
            while (row < rowSize) and (col >= 0):
                value = matrix[row][col]
                if value == target:
                    retVal = True
                    break
                elif value < target:
                    row += 1
                elif value > target:
                    col -= 1

        return retVal
```

</details>

## [81. Search in Rotated Sorted Array II](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/)

- [Official](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/editorial/)
- [Official](https://leetcode.cn/problems/search-in-rotated-sorted-array-ii/solutions/704686/sou-suo-xuan-zhuan-pai-xu-shu-zu-ii-by-l-0nmp/)

<details><summary>Description</summary>

```text
There is an integer array nums sorted in non-decreasing order (not necessarily with distinct values).

Before being passed to your function, nums is rotated at an unknown pivot index k (0 <= k < nums.length)
such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed).
For example, [0,1,2,4,4,4,5,6,6,7] might be rotated at pivot index 5 and become [4,5,6,6,7,0,1,2,4,4].

Given the array nums after the rotation and an integer target,
return true if target is in nums, or false if it is not in nums.

You must decrease the overall operation steps as much as possible.

Example 1:
Input: nums = [2,5,6,0,0,1,2], target = 0
Output: true

Example 2:
Input: nums = [2,5,6,0,0,1,2], target = 3
Output: false

Constraints:
1 <= nums.length <= 5000
-10^4 <= nums[i] <= 10^4
nums is guaranteed to be rotated at some pivot.
-10^4 <= target <= 10^4
```

</details>

<details><summary>C</summary>

```c
bool search(int* nums, int numsSize, int target) {
    bool retVal = false;

    int middle;
    int left = 0;
    int right = numsSize - 1;
    while (left <= right) {
        middle = left + (right - left) / 2;
        if (nums[middle] == target) {
            retVal = true;
            break;
        } else if ((nums[middle] == nums[left]) && (nums[middle] == nums[right])) {
            left += 1;
            right -= 1;

        } else if (nums[middle] >= nums[left]) {
            if ((target >= nums[left]) && (target < nums[middle])) {
                right = middle - 1;
            } else {
                left = middle + 1;
            }
        } else {
            if ((target <= nums[right]) && (target > nums[middle])) {
                left = middle + 1;
            } else {
                right = middle - 1;
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
    bool search(vector<int>& nums, int target) {
        bool retVal = false;

        int left = 0;
        int right = nums.size() - 1;
        while (left <= right) {
            int middle = left + (right - left) / 2;
            if (nums[middle] == target) {
                retVal = true;
                break;
            } else if ((nums[middle] == nums[left]) && (nums[middle] == nums[right])) {
                left += 1;
                right -= 1;
            } else if (nums[middle] >= nums[left]) {
                if ((target >= nums[left]) && (target < nums[middle])) {
                    right = middle - 1;
                } else {
                    left = middle + 1;
                }
            } else {
                if ((target <= nums[right]) && (target > nums[middle])) {
                    left = middle + 1;
                } else {
                    right = middle - 1;
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
    def search(self, nums: List[int], target: int) -> bool:
        retVal = False

        left = 0
        right = len(nums) - 1
        while left <= right:
            middle = left + (right - left) // 2
            if nums[middle] == target:
                retVal = True
                break
            elif (nums[middle] == nums[left]) and (nums[middle] == nums[right]):
                left += 1
                right -= 1
            elif nums[middle] >= nums[left]:
                if (target >= nums[left]) and (target < nums[middle]):
                    right = middle - 1
                else:
                    left = middle + 1
            else:
                if (target <= nums[right]) and (target > nums[middle]):
                    left = middle + 1
                else:
                    right = middle - 1

        return retVal
```

</details>

## [153. Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/)

- [Official](https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array/solutions/698479/xun-zhao-xuan-zhuan-pai-xu-shu-zu-zhong-5irwp/)

<details><summary>Description</summary>

```text
Suppose an array of length n sorted in ascending order is rotated between 1 and n times.
For example, the array nums = [0,1,2,4,5,6,7] might become:
- [4,5,6,7,0,1,2] if it was rotated 4 times.
- [0,1,2,4,5,6,7] if it was rotated 7 times.
Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results
in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].

Given the sorted rotated array nums of unique elements, return the minimum element of this array.

You must write an algorithm that runs in O(log n) time.

Example 1:
Input: nums = [3,4,5,1,2]
Output: 1
Explanation: The original array was [1,2,3,4,5] rotated 3 times.

Example 2:
Input: nums = [4,5,6,7,0,1,2]
Output: 0
Explanation: The original array was [0,1,2,4,5,6,7] and it was rotated 4 times.

Example 3:
Input: nums = [11,13,15,17]
Output: 11
Explanation: The original array was [11,13,15,17] and it was rotated 4 times.

Constraints:
n == nums.length
1 <= n <= 5000
-5000 <= nums[i] <= 5000
All the integers of nums are unique.
nums is sorted and rotated between 1 and n times.
```

<details><summary>Hint</summary>

```text
1. Array was originally in ascending order.
   Now that the array is rotated, there would be a point in the array
   where there is a small deflection from the increasing sequence.
   eg. The array would be something like [4, 5, 6, 7, 0, 1, 2].
2. You can divide the search space into two and see which direction to go.
   Can you think of an algorithm which has O(logN) search complexity?
3. All the elements to the left of inflection point > first element of the array.
   All the elements to the right of inflection point < first element of the array.
```

</details>

</details>

<details><summary>C</summary>

```c
int findMin(int *nums, int numsSize) {
    int retVal = 0;

    int middle = 0;
    int left = 0;
    int right = numsSize - 1;
    while (left < right) {
        middle = left + (right - left) / 2;
        if (nums[middle] < nums[right]) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }
    retVal = nums[left];

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int findMin(vector<int>& nums) {
        int retVal = 0;

        int left = 0;
        int right = nums.size() - 1;
        while (left < right) {
            int middle = left + (right - left) / 2;
            if (nums[middle] < nums[right]) {
                right = middle;
            } else {
                left = middle + 1;
            }
        }
        retVal = nums[left];

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def findMin(self, nums: List[int]) -> int:
        retVal = 0

        left = 0
        right = len(nums) - 1
        while left < right:
            middle = left + (right - left) // 2
            if nums[middle] < nums[right]:
                right = middle
            else:
                left = middle + 1
        retVal = nums[left]

        return retVal
```

</details>

## [154. Find Minimum in Rotated Sorted Array II](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/)

- [Official](https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array-ii/solutions/340800/xun-zhao-xuan-zhuan-pai-xu-shu-zu-zhong-de-zui--16/)

<details><summary>Description</summary>

```text
Suppose an array of length n sorted in ascending order is rotated between 1 and n times.
For example, the array nums = [0,1,4,4,5,6,7] might become:
- [4,5,6,7,0,1,4] if it was rotated 4 times.
- [0,1,4,4,5,6,7] if it was rotated 7 times.

Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results
in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].

Given the sorted rotated array nums that may contain duplicates, return the minimum element of this array.

You must decrease the overall operation steps as much as possible.

Example 1:
Input: nums = [1,3,5]
Output: 1

Example 2:
Input: nums = [2,2,2,0,1]
Output: 0

Constraints:
n == nums.length
1 <= n <= 5000
-5000 <= nums[i] <= 5000
nums is sorted and rotated between 1 and n times.

Follow up: This problem is similar to Find Minimum in Rotated Sorted Array, but nums may contain duplicates.
Would this affect the runtime complexity? How and why?
```

</details>

<details><summary>C</summary>

```c
int findMin(int* nums, int numsSize) {
    int retVal = 0;

    int middle = 0;
    int left = 0;
    int right = numsSize - 1;
    while (left < right) {
        middle = left + (right - left) / 2;
        if (nums[middle] < nums[right]) {
            right = middle;
        } else if (nums[middle] > nums[right]) {
            left = middle + 1;
        } else {
            right -= 1;
        }
    }
    retVal = nums[left];

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int findMin(vector<int>& nums) {
        int retVal = 0;

        int left = 0;
        int right = nums.size() - 1;
        while (left < right) {
            int middle = left + (right - left) / 2;
            if (nums[middle] < nums[right]) {
                right = middle;
            } else if (nums[middle] > nums[right]) {
                left = middle + 1;
            } else {
                right -= 1;
            }
        }
        retVal = nums[left];

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def findMin(self, nums: List[int]) -> int:
        retVal = 0

        left = 0
        right = len(nums) - 1
        while left < right:
            middle = left + (right - left) // 2
            if nums[middle] < nums[right]:
                right = middle
            elif nums[middle] > nums[right]:
                left = middle + 1
            else:
                right -= 1
        retVal = nums[left]

        return retVal
```

</details>

## [162. Find Peak Element](https://leetcode.com/problems/find-peak-element/)

- [Official](https://leetcode.cn/problems/find-peak-element/solutions/998152/xun-zhao-feng-zhi-by-leetcode-solution-96sj/)

<details><summary>Description</summary>

```text
A peak element is an element that is strictly greater than its neighbors.

Given a 0-indexed integer array nums, find a peak element, and return its index.
If the array contains multiple peaks, return the index to any of the peaks.

You may imagine that nums[-1] = nums[n] = -∞.
In other words, an element is always considered to be strictly greater than a neighbor that is outside the array.

You must write an algorithm that runs in O(log n) time.

Example 1:
Input: nums = [1,2,3,1]
Output: 2
Explanation: 3 is a peak element and your function should return the index number 2.

Example 2:
Input: nums = [1,2,1,3,5,6,4]
Output: 5
Explanation: Your function can return either index number 1 where the peak element is 2,
or index number 5 where the peak element is 6.

Constraints:
1 <= nums.length <= 1000
-2^31 <= nums[i] <= 2^31 - 1
nums[i] != nums[i + 1] for all valid i.
```

</details>

<details><summary>C</summary>

```c
int findPeakElement(int* nums, int numsSize) {
    int retVal = 0;

    int left = 0;
    int right = numsSize - 1;
    int middle;
    while (left < right) {
        middle = left + (right - left) / 2;
        if (nums[middle] > nums[middle + 1]) {
            right = middle;
        } else {
            left = middle + 1;
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
    int findPeakElement(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        int left = 0;
        int right = numsSize - 1;
        while (left < right) {
            int middle = left + (right - left) / 2;
            if (nums[middle] > nums[middle + 1]) {
                right = middle;
            } else {
                left = middle + 1;
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
    def findPeakElement(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        left = 0
        right = numsSize - 1
        while left < right:
            middle = left + (right - left) // 2
            if nums[middle] > nums[middle + 1]:
                right = middle
            else:
                left = middle + 1
        retVal = left

        return retVal
```

</details>

## [240. Search a 2D Matrix II](https://leetcode.com/problems/search-a-2d-matrix-ii/)

- [Official](https://leetcode.cn/problems/search-a-2d-matrix-ii/solutions/1062538/sou-suo-er-wei-ju-zhen-ii-by-leetcode-so-9hcx/)

<details><summary>Description</summary>

```text
Write an efficient algorithm that searches for a value target in an m x n integer matrix matrix.
This matrix has the following properties:
- Integers in each row are sorted in ascending from left to right.
- Integers in each column are sorted in ascending from top to bottom.

Example 1:
Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
Output: true

Example 2:
Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
Output: false

Constraints:
m == matrix.length
n == matrix[i].length
1 <= n, m <= 300
-10^9 <= matrix[i][j] <= 10^9
All the integers in each row are sorted in ascending order.
All the integers in each column are sorted in ascending order.
-10^9 <= target <= 10^9
```

</details>

<details><summary>C</summary>

```c
bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target) {
    bool retVal = false;

    // m == matrix.length, n == matrix[i].length, 1 <= n, m <= 300
    int matrixRow = matrixSize;
    int matrixCol = matrixColSize[0];

    /* Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
     *      0  1  2  3  4   |  0   1   2    3  4  |  0   1   2  3  4
     *  0   1  4  7 11 [15] |  1  [4] [7] [11] 15 |  1   4   7 11 15
     *  1   2  5  8 12  19  |  2   5   8   12  19 |  2  [5]  8 12 19
     *  2   3  6  9 16  22  |  3   6   9   16  22 |  3   6   9 16 22
     *  3  10 13 14 17  24  | 10  13  14   17  24 | 10  13  14 17 24
     *  4  18 21 23 26  30  | 18  21  23   26  30 | 18  21  23 26 30
     *
     * Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
     *      0  1  2  3  4   |  0  1  2  3   4  |  0  1  2   3   4 |  0   1    2   3  4 |   0   1  2  3  4
     *  0   1  4  7 11 [15] |  1  4  7 11  15  |  1  4  7  11  15 |  1   4    7  11 15 |   1   4  7 11 15
     *  1   2  5  8 12  19  |  2  5  8 12 [19] |  2  5  8  12  19 |  2   5    8  12 19 |   2   5  8 12 19
     *  2   3  6  9 16  22  |  3  6  9 16 [22] |  3  6  9 [16] 22 |  3   6    9  16 22 |   3   6  9 16 22
     *  3  10 13 14 17  24  | 10 13 14 17  24  | 10 13 14 [17] 24 | 10  13   14  17 24 |  10  13 14 17 24
     *  4  18 21 23 26  30  | 18 21 23 26  30  | 18 21 23 [26] 30 | 18 [21] [23] 26 30 | [18] 21 23 26 30
     */
    int value;
    int row = 0;
    int col = matrixCol - 1;
    while ((row < matrixRow) && (col >= 0)) {
        value = matrix[row][col];
        if (value == target) {
            retVal = true;
            break;
        } else if (value < target) {
            row++;
        } else if (value > target) {
            col--;
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
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        bool retVal = false;

        // m == matrix.length, n == matrix[i].length, 1 <= n, m <= 300
        int matrixRowSize = matrix.size();
        int matrixColSize = matrix[0].size();

        /* Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
         *      0  1  2  3  4   |  0   1   2    3  4  |  0   1   2  3  4
         *  0   1  4  7 11 [15] |  1  [4] [7] [11] 15 |  1   4   7 11 15
         *  1   2  5  8 12  19  |  2   5   8   12  19 |  2  [5]  8 12 19
         *  2   3  6  9 16  22  |  3   6   9   16  22 |  3   6   9 16 22
         *  3  10 13 14 17  24  | 10  13  14   17  24 | 10  13  14 17 24
         *  4  18 21 23 26  30  | 18  21  23   26  30 | 18  21  23 26 30
         *
         * Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
         *      0  1  2  3  4   |  0  1  2  3   4  |  0  1  2   3   4 |  0   1    2   3  4 |   0   1  2  3  4
         *  0   1  4  7 11 [15] |  1  4  7 11  15  |  1  4  7  11  15 |  1   4    7  11 15 |   1   4  7 11 15
         *  1   2  5  8 12  19  |  2  5  8 12 [19] |  2  5  8  12  19 |  2   5    8  12 19 |   2   5  8 12 19
         *  2   3  6  9 16  22  |  3  6  9 16 [22] |  3  6  9 [16] 22 |  3   6    9  16 22 |   3   6  9 16 22
         *  3  10 13 14 17  24  | 10 13 14 17  24  | 10 13 14 [17] 24 | 10  13   14  17 24 |  10  13 14 17 24
         *  4  18 21 23 26  30  | 18 21 23 26  30  | 18 21 23 [26] 30 | 18 [21] [23] 26 30 | [18] 21 23 26 30
         */
        int row = 0;
        int col = matrixColSize - 1;
        while ((row < matrixRowSize) && (col >= 0)) {
            int value = matrix[row][col];
            if (value == target) {
                retVal = true;
                break;
            } else if (value < target) {
                row++;
            } else if (value > target) {
                col--;
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
    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
        retVal = False

        # m == matrix.length, n == matrix[i].length, 1 <= n, m <= 300
        rowSize = len(matrix)
        colSize = len(matrix[0])

        # /* Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
        #  *      0  1  2  3  4   |  0   1   2    3  4  |  0   1   2  3  4
        #  *  0   1  4  7 11 [15] |  1  [4] [7] [11] 15 |  1   4   7 11 15
        #  *  1   2  5  8 12  19  |  2   5   8   12  19 |  2  [5]  8 12 19
        #  *  2   3  6  9 16  22  |  3   6   9   16  22 |  3   6   9 16 22
        #  *  3  10 13 14 17  24  | 10  13  14   17  24 | 10  13  14 17 24
        #  *  4  18 21 23 26  30  | 18  21  23   26  30 | 18  21  23 26 30
        #  *
        #  * Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
        #  *      0  1  2  3  4   |  0  1  2  3   4  |  0  1  2   3   4 |  0   1    2   3  4 |   0   1  2  3  4
        #  *  0   1  4  7 11 [15] |  1  4  7 11  15  |  1  4  7  11  15 |  1   4    7  11 15 |   1   4  7 11 15
        #  *  1   2  5  8 12  19  |  2  5  8 12 [19] |  2  5  8  12  19 |  2   5    8  12 19 |   2   5  8 12 19
        #  *  2   3  6  9 16  22  |  3  6  9 16 [22] |  3  6  9 [16] 22 |  3   6    9  16 22 |   3   6  9 16 22
        #  *  3  10 13 14 17  24  | 10 13 14 17  24  | 10 13 14 [17] 24 | 10  13   14  17 24 |  10  13 14 17 24
        #  *  4  18 21 23 26  30  | 18 21 23 26  30  | 18 21 23 [26] 30 | 18 [21] [23] 26 30 | [18] 21 23 26 30
        #  */
        row = 0
        col = colSize - 1
        while (row < rowSize) and (col >= 0):
            value = matrix[row][col]
            if value == target:
                retVal = True
                break
            elif value < target:
                row += 1
            elif value > target:
                col -= 1

        return retVal
```

</details>

## [278. First Bad Version](https://leetcode.com/problems/first-bad-version/)

- [Official](https://leetcode.cn/problems/first-bad-version/solutions/824522/di-yi-ge-cuo-wu-de-ban-ben-by-leetcode-s-pf8h/)

<details><summary>Description</summary>

```text
You are a product manager and currently leading a team to develop a new product.
Unfortunately, the latest version of your product fails the quality check.
Since each version is developed based on the previous version, all the versions after a bad version are also bad.

Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one,
which causes all the following ones to be bad.

You are given an API bool isBadVersion(version) which returns whether version is bad.
Implement a function to find the first bad version. You should minimize the number of calls to the API.

Example 1:
Input: n = 5, bad = 4
Output: 4
Explanation:
call isBadVersion(3) -> false
call isBadVersion(5) -> true
call isBadVersion(4) -> true
Then 4 is the first bad version.

Example 2:
Input: n = 1, bad = 1
Output: 1

Constraints:
1 <= bad <= n <= 2^31 - 1
```

</details>

<details><summary>C</summary>

```c
// The API isBadVersion is defined for you.
// bool isBadVersion(int version);
int firstBadVersion(int n) {
    int retVal = 1;

    int mid;
    while (retVal < n) {
        mid = (retVal / 2) + (n / 2);
        if (isBadVersion(mid) == true) {
            n = mid;
        } else {
            retVal = mid + 1;
        }
    }

    return retVal;
}
```

</details>

## [300. Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/)

- [Official](https://leetcode.cn/problems/longest-increasing-subsequence/solutions/147667/zui-chang-shang-sheng-zi-xu-lie-by-leetcode-soluti/)

<details><summary>Description</summary>

```text
Given an integer array nums, return the length of the longest strictly increasing subsequence.

Example 1:
Input: nums = [10,9,2,5,3,7,101,18]
Output: 4
Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.

Example 2:
Input: nums = [0,1,0,3,2,3]
Output: 4

Example 3:
Input: nums = [7,7,7,7,7,7,7]
Output: 1

Constraints:
1 <= nums.length <= 2500
-10^4 <= nums[i] <= 10^4

Follow up: Can you come up with an algorithm that runs in O(n log(n)) time complexity?
```

</details>

<details><summary>C</summary>

```c
#define BINARY_SEARCH (1)
#define DYNAMIC_PROGRAMMING (1)
int lengthOfLIS(int* nums, int numsSize) {
    int retVal = 0;

    if (numsSize == 0) {
        return retVal;
    }

#if (BINARY_SEARCH)
    printf("BINARY_SEARCH\n");

    int greedy[numsSize + 1];
    memset(greedy, 0, sizeof(greedy));
    int idx = 1;
    greedy[idx] = nums[0];

    int left, right, middle;
    int position;
    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[i] > greedy[idx]) {
            greedy[++idx] = nums[i];
            continue;
        }

        left = 1;
        right = idx;
        position = 0;
        while (left < right) {
            middle = left + (right - left) / 2;
            if (greedy[middle] < nums[i]) {
                position = middle;
                left = middle + 1;
            } else {
                right = middle;
            }
        }
        greedy[position + 1] = nums[i];
    }
    retVal = idx;
#elif (DYNAMIC_PROGRAMMING)
    printf("DYNAMIC_PROGRAMMING\n");

    int dp[numsSize];
    memset(dp, 0, sizeof(dp));
    int i, j;
    for (i = 0; i < numsSize; ++i) {
        dp[i] = 1;
        for (j = 0; j < i; ++j) {
            if (nums[j] < nums[i]) {
                dp[i] = fmax(dp[i], dp[j] + 1);
            }
        }
    }

    for (i = 0; i < numsSize; ++i) {
        retVal = fmax(retVal, dp[i]);
    }
#endif

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
#define BINARY_SEARCH (1)
#define DYNAMIC_PROGRAMMING (1)
class Solution {
   public:
    Solution() {
#if (BINARY_SEARCH)
        cout << "BINARY_SEARCH\n";
#elif (DYNAMIC_PROGRAMMING)
        cout << "DYNAMIC_PROGRAMMING\n";
#endif
        cout << "\n";
    }
    int lengthOfLIS(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        if (numsSize == 0) {
            return retVal;
        }

#if (BINARY_SEARCH)
        vector<int> greedy(numsSize + 1, 0);
        int idx = 1;
        greedy[idx] = nums[0];

        for (int i = 1; i < numsSize; ++i) {
            if (nums[i] > greedy[idx]) {
                greedy[++idx] = nums[i];
                continue;
            }

            int left = 1;
            int right = idx;
            int position = 0;
            while (left < right) {
                int middle = left + (right - left) / 2;
                if (greedy[middle] < nums[i]) {
                    position = middle;
                    left = middle + 1;
                } else {
                    right = middle;
                }
            }
            greedy[position + 1] = nums[i];
        }
        retVal = idx;
#elif (DYNAMIC_PROGRAMMING)
        vector<int> dp(numsSize, 0);
        for (int i = 0; i < numsSize; ++i) {
            dp[i] = 1;
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        retVal = *max_element(dp.begin(), dp.end());
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
            print("DYNAMIC_PROGRAMMING")
        print()

    def lengthOfLIS(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)
        if numsSize == 0:
            return retVal

        if self.method == 1:
            greedy = [0] * (numsSize + 1)
            idx = 1
            greedy[idx] = nums[0]

            for i in range(1, numsSize):
                if nums[i] > greedy[idx]:
                    idx += 1
                    greedy[idx] = nums[i]
                    continue

                left = 1
                right = idx
                position = 0
                while left < right:
                    middle = left + (right - left) // 2
                    if greedy[middle] < nums[i]:
                        position = middle
                        left = middle + 1
                    else:
                        right = middle
                greedy[position + 1] = nums[i]

            retVal = idx
        elif self.method == 2:
            dp = [0] * numsSize
            for i in range(numsSize):
                dp[i] = 1
                for j in range(i):
                    if nums[j] < nums[i]:
                        dp[i] = max(dp[i], dp[j] + 1)
            retVal = max(dp)

        return retVal
```

</details>

## [374. Guess Number Higher or Lower](https://leetcode.com/problems/guess-number-higher-or-lower/)

- [Official](https://leetcode.cn/problems/guess-number-higher-or-lower/solutions/824520/cai-shu-zi-da-xiao-by-leetcode-solution-qdzu/)

<details><summary>Description</summary>

```text
We are playing the Guess Game. The game is as follows:

I pick a number from 1 to n. You have to guess which number I picked.

Every time you guess wrong, I will tell you whether the number I picked is higher or lower than your guess.

You call a pre-defined API int guess(int num), which returns three possible results:
-1: Your guess is higher than the number I picked (i.e. num > pick).
1: Your guess is lower than the number I picked (i.e. num < pick).
0: your guess is equal to the number I picked (i.e. num == pick).

Return the number that I picked.

Example 1:
Input: n = 10, pick = 6
Output: 6

Example 2:
Input: n = 1, pick = 1
Output: 1

Example 3:
Input: n = 2, pick = 1
Output: 1

Constraints:
1 <= n <= 2^31 - 1
1 <= pick <= n
```

</details>

<details><summary>C</summary>

```c
/**
 * Forward declaration of guess API.
 * @param  num  your guess
 * @return      -1 if num is higher than the picked number
 *               1 if num is lower than the picked number
 *               otherwise return 0
 * int guess(int num);
 */
int guessNumber(int n) {
    int retVal = 0;

    int left = 1;
    int right = n;
    int middle, ret;
    while (left <= right) {
        middle = left + ((right - left) / 2);

        ret = guess(middle);
        if (ret == 0) {
            retVal = middle;
            break;
        } else if (ret == -1) {
            right = middle - 1;
        } else if (ret == 1) {
            left = middle + 1;
        }
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/**
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return       -1 if num is higher than the picked number
 *         1 if num is lower than the picked number
 *               otherwise return 0
 * int guess(int num);
 */
class Solution {
   public:
    int guessNumber(int n) {
        int retVal = 0;

        int left = 1;
        int right = n;
        while (left <= right) {
            int middle = left + ((right - left) / 2);

            int ret = guess(middle);
            if (ret == 0) {
                retVal = middle;
                break;
            } else if (ret == -1) {
                right = middle - 1;
            } else if (ret == 1) {
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
# The guess API is already defined for you.
# @param num, your guess
# @return -1 if num is higher than the picked number
#          1 if num is lower than the picked number
#          otherwise return 0
# def guess(num: int) -> int:
class Solution:
    def guessNumber(self, n: int) -> int:
        retVal = 0

        left = 1
        right = n
        while (left <= right):
            middle = left + ((right - left) // 2)

            ret = guess(middle)
            if ret == 0:
                retVal = middle
                break
            elif ret == -1:
                right = middle - 1
            elif ret == 1:
                left = middle + 1

        return retVal
```

</details>

## [540. Single Element in a Sorted Array](https://leetcode.com/problems/single-element-in-a-sorted-array/)

- [Official](https://leetcode.cn/problems/single-element-in-a-sorted-array/solutions/1252764/you-xu-shu-zu-zhong-de-dan-yi-yuan-su-by-y8gh/)

<details><summary>Description</summary>

```text
You are given a sorted array consisting of only integers where every element appears exactly twice,
except for one element which appears exactly once.

Return the single element that appears only once.

Your solution must run in O(log n) time and O(1) space.

Example 1:
Input: nums = [1,1,2,3,3,4,4,8,8]
Output: 2

Example 2:
Input: nums = [3,3,7,7,10,11,11]
Output: 10

Constraints:
1 <= nums.length <= 10^5
0 <= nums[i] <= 10^5
```

</details>

<details><summary>C</summary>

```c
int singleNonDuplicate(int* nums, int numsSize) {
    int retVal = 0;

    // 1 <= nums.length <= 10^5
    if (numsSize == 1) {
        retVal = nums[0];
        return retVal;
    }

    int middle = 0;
    int left = 0;
    int right = numsSize - 1;
    while (left < right) {
        middle = left + (right - left) / 2;
        /* middle is odd or even
         *  middle is odd: middle % 2 == 1
         *  +---------------------------------+
         *  |  0  | 1 | 2 | [3] | 4 | 5 |  6  |
         *  +---------------------------------+
         *  |  1  | 1 | 2 |  2  | 3 | 3 | (4) | nums[middle] == nums[middle - 1]
         *  | (1) | 2 | 2 |  3  | 3 | 4 |  4  | nums[middle] != nums[middle - 1]
         *  +---------------------------------+
         *
         *  middle is even: middle % 2 == 0
         *  +-----------------------------------------+
         *  |  0  | 1 | 2 | 3 | [4] | 5 | 6 | 7 |  8  |
         *  +-----------------------------------------+
         *  | (1) | 2 | 2 | 3 |  3  | 4 | 4 | 5 |  5  | nums[middle] == nums[middle - 1]
         *  |  1  | 1 | 2 | 2 |  3  | 3 | 4 | 4 | (5) | nums[middle] != nums[middle - 1]
         *  +-----------------------------------------+
         */
        if (middle % 2 == 1) {
            if (nums[middle] == nums[middle - 1]) {
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        } else {
            if (nums[middle] == nums[middle - 1]) {
                right = middle;
            } else {
                left = middle;
            }
        }
    }
    retVal = nums[left];

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int singleNonDuplicate(vector<int>& nums) {
        int retVal = 0;

        // 1 <= nums.length <= 10^5
        int len = nums.size();
        if (len == 1) {
            retVal = nums[0];
            return retVal;
        }

        int middle = 0;
        int left = 0;
        int right = len - 1;
        while (left < right) {
            middle = left + (right - left) / 2;
            /* middle is odd or even
             *  middle is odd: middle % 2 == 1
             *  +---------------------------------+
             *  |  0  | 1 | 2 | [3] | 4 | 5 |  6  |
             *  +---------------------------------+
             *  |  1  | 1 | 2 |  2  | 3 | 3 | (4) | nums[middle] == nums[middle - 1]
             *  | (1) | 2 | 2 |  3  | 3 | 4 |  4  | nums[middle] != nums[middle - 1]
             *  +---------------------------------+
             *
             *  middle is even: middle % 2 == 0
             *  +-----------------------------------------+
             *  |  0  | 1 | 2 | 3 | [4] | 5 | 6 | 7 |  8  |
             *  +-----------------------------------------+
             *  | (1) | 2 | 2 | 3 |  3  | 4 | 4 | 5 |  5  | nums[middle] == nums[middle - 1]
             *  |  1  | 1 | 2 | 2 |  3  | 3 | 4 | 4 | (5) | nums[middle] != nums[middle - 1]
             *  +-----------------------------------------+
             */
            if (middle % 2 == 1) {
                if (nums[middle] == nums[middle - 1]) {
                    left = middle + 1;
                } else {
                    right = middle - 1;
                }
            } else {
                if (nums[middle] == nums[middle - 1]) {
                    right = middle;
                } else {
                    left = middle;
                }
            }
        }
        retVal = nums[left];

        return retVal;
    }
};
```

</details>

## [704. Binary Search](https://leetcode.com/problems/binary-search/)

- [Official](https://leetcode.com/problems/binary-search/solutions/2794222/binary-search/)
- [Official](https://leetcode.cn/problems/binary-search/solutions/980494/er-fen-cha-zhao-by-leetcode-solution-f0xw)

<details><summary>Description</summary>

```text
Given an array of integers nums which is sorted in ascending order, and an integer target,
write a function to search target in nums. If target exists, then return its index. Otherwise, return -1.

You must write an algorithm with O(log n) runtime complexity.

Example 1:
Input: nums = [-1,0,3,5,9,12], target = 9
Output: 4
Explanation: 9 exists in nums and its index is 4

Example 2:
Input: nums = [-1,0,3,5,9,12], target = 2
Output: -1
Explanation: 2 does not exist in nums so return -1

Constraints:
1 <= nums.length <= 10^4
-10^4 < nums[i], target < 10^4
All the integers in nums are unique.
nums is sorted in ascending order.
```

</details>

<details><summary>C</summary>

```c
int search(int* nums, int numsSize, int target) {
    int retVal = -1;

    int mid = 0;
    int low = 0;
    int high = numsSize - 1;
    while (low <= high) {
        mid = low + (high - low) / 2;
        if (nums[mid] == target) {
            retVal = mid;
            break;
        }

        if (nums[mid] > target) {
            high = mid - 1;
        } else if (nums[mid] < target) {
            low = mid + 1;
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
    int search(vector<int>& nums, int target) {
        int retVal = -1;

        int numsSize = nums.size();

        int mid = 0;
        int low = 0;
        int high = numsSize - 1;
        while (low <= high) {
            mid = low + (high - low) / 2;
            if (nums[mid] == target) {
                retVal = mid;
                break;
            }

            if (nums[mid] > target) {
                high = mid - 1;
            } else if (nums[mid] < target) {
                low = mid + 1;
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
    def search(self, nums: List[int], target: int) -> int:
        retVal = -1

        low = 0
        high = len(nums) - 1
        while (low <= high):
            mid = low + (high - low) // 2
            if target == nums[mid]:
                retVal = mid
                break
            elif target > nums[mid]:
                low = mid + 1
            elif target < nums[mid]:
                high = mid - 1

        return retVal
```

</details>

## [719. Find K-th Smallest Pair Distance](https://leetcode.com/problems/find-k-th-smallest-pair-distance/)

- [Official](https://leetcode.com/problems/find-k-th-smallest-pair-distance/editorial/)
- [Official](https://leetcode.cn/problems/find-k-th-smallest-pair-distance/solutions/1600107/zhao-chu-di-k-xiao-de-shu-dui-ju-chi-by-xwfgf/)

<details><summary>Description</summary>

```text
The distance of a pair of integers a and b is defined as the absolute difference between a and b.

Given an integer array nums and an integer k,
return the kth smallest distance among all the pairs nums[i] and nums[j] where 0 <= i < j < nums.length.

Example 1:
Input: nums = [1,3,1], k = 1
Output: 0
Explanation: Here are all the pairs:
(1,3) -> 2
(1,1) -> 0
(3,1) -> 2
Then the 1st smallest distance pair is (1,1), and its distance is 0.

Example 2:
Input: nums = [1,1,1], k = 2
Output: 0

Example 3:
Input: nums = [1,6,1], k = 3
Output: 5

Constraints:
n == nums.length
2 <= n <= 10^4
0 <= nums[i] <= 10^6
1 <= k <= n * (n - 1) / 2
```

<details><summary>Hint</summary>

```text
1. Binary search for the answer. How can you check how many pairs have distance <= X?
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int smallestDistancePair(int* nums, int numsSize, int k) {
    int retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int middle, index, i, j;
    int left = 0;
    int right = nums[numsSize - 1] - nums[0];
    while (left <= right) {
        middle = (left + right) / 2;

        index = 0;
        i = 0;
        for (j = 0; j < numsSize; j++) {
            while (nums[j] - nums[i] > middle) {
                i++;
            }
            index += (j - i);
        }

        if (index >= k) {
            right = middle - 1;
        } else {
            left = middle + 1;
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
    int smallestDistancePair(vector<int>& nums, int k) {
        int retVal = 0;

        sort(nums.begin(), nums.end());

        int numsSize = nums.size();
        int left = 0;
        int right = nums[numsSize - 1] - nums[0];
        while (left <= right) {
            int middle = (left + right) / 2;

            int index = 0;
            int i = 0;
            for (int j = 0; j < numsSize; j++) {
                while (nums[j] - nums[i] > middle) {
                    i++;
                }
                index += (j - i);
            }

            if (index >= k) {
                right = middle - 1;
            } else {
                left = middle + 1;
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
    def smallestDistancePair(self, nums: List[int], k: int) -> int:
        retVal = 0

        nums.sort()

        numsSize = len(nums)
        left = 0
        right = nums[numsSize - 1] - nums[0]
        while left <= right:
            middle = (left + right) // 2

            index = 0
            i = 0
            for j in range(numsSize):
                while nums[j] - nums[i] > middle:
                    i += 1
                index += (j-i)

            if index >= k:
                right = middle - 1
            else:
                left = middle + 1

        retVal = left

        return retVal
```

</details>

## [729. My Calendar I](https://leetcode.com/problems/my-calendar-i/)

- [Official](https://leetcode.com/problems/my-calendar-i/editorial/)
- [Official](https://leetcode.cn/problems/my-calendar-i/solutions/1643942/wo-de-ri-cheng-an-pai-biao-i-by-leetcode-nlxr/)

<details><summary>Description</summary>

```text
You are implementing a program to use as your calendar.
We can add a new event if adding the event will not cause a double booking.

A double booking happens when two events have some non-empty intersection (i.e., some moment is common to both events.).

The event can be represented as a pair of integers start and end
that represents a booking on the half-open interval [start, end),
the range of real numbers x such that start <= x < end.

Implement the MyCalendar class:
- MyCalendar()
  Initializes the calendar object.
- boolean book(int start, int end)
  Returns true if the event can be added to the calendar successfully without causing a double booking.
  Otherwise, return false and do not add the event to the calendar.

Example 1:
Input
["MyCalendar", "book", "book", "book"]
[[], [10, 20], [15, 25], [20, 30]]
Output
[null, true, false, true]
Explanation
MyCalendar myCalendar = new MyCalendar();
myCalendar.book(10, 20); // return True
myCalendar.book(15, 25); // return False, It can not be booked because time 15 is already booked by another event.
myCalendar.book(20, 30); // return True, The event can be booked, as the first event takes every time less than 20,
but not including 20.

Constraints:
0 <= start < end <= 10^9
At most 1000 calls will be made to book.
```

<details><summary>Hint</summary>

```text
1. Store the events as a sorted list of intervals. If none of the events conflict, then the new event can be added.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MAX_CALLS (1000 + 4)  // At most 1000 calls will be made to book.
typedef struct {
    int start[MAX_CALLS];
    int end[MAX_CALLS];
    int idx;
} MyCalendar;
MyCalendar* myCalendarCreate() {
    MyCalendar* pObj = NULL;

    pObj = (MyCalendar*)malloc(sizeof(MyCalendar));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    memset(pObj, -1, sizeof(MyCalendar));
    pObj->idx = 0;

    return pObj;
}
bool myCalendarBook(MyCalendar* obj, int start, int end) {
    bool retVal = false;

    if (obj->idx == 0) {
        obj->start[obj->idx] = start;
        obj->end[obj->idx] = end;
        obj->idx += 1;
        retVal = true;
        return retVal;
    }

    int i;
    for (i = 0; i < obj->idx; ++i) {
        if ((start >= obj->start[i]) && (start < obj->end[i])) {
            return retVal;
        } else if ((end > obj->start[i]) && (end < obj->end[i])) {
            return retVal;
        } else if ((start <= obj->start[i]) && (end >= obj->end[i])) {
            return retVal;
        }
    }

    obj->start[obj->idx] = start;
    obj->end[obj->idx] = end;
    obj->idx += 1;
    retVal = true;

    return retVal;
}
void myCalendarFree(MyCalendar* obj) {
    free(obj);
    obj = NULL;
}
/**
 * Your MyCalendar struct will be instantiated and called as such:
 * MyCalendar* obj = myCalendarCreate();
 * bool param_1 = myCalendarBook(obj, start, end);
 * myCalendarFree(obj);
 */
```

</details>

<details><summary>C++</summary>

```c++
class MyCalendar {
   private:
    set<pair<int, int>> calendar;

   public:
    MyCalendar() {}
    bool book(int start, int end) {
        bool retVal = false;

        const pair<int, int> event{start, end};
        const auto nextEvent = calendar.lower_bound(event);
        if ((nextEvent != calendar.end()) && (nextEvent->first < end)) {
            return retVal;
        }

        if (nextEvent != calendar.begin()) {
            const auto prevEvent = prev(nextEvent);
            if (prevEvent->second > start) {
                return retVal;
            }
        }
        calendar.insert(event);
        retVal = true;

        return retVal;
    }
};
/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */
```

</details>

<details><summary>Python3</summary>

```python
from sortedcontainers import SortedList

class MyCalendar:
    def __init__(self):
        self.calendar = SortedList()

    def book(self, start: int, end: int) -> bool:
        retVal = False

        calendarSize = len(self.calendar)

        idx = self.calendar.bisect_right((start, end))
        if (idx > 0) and (self.calendar[idx-1][1] > start):
            return retVal
        elif (idx < calendarSize) and (self.calendar[idx][0] < end):
            return retVal

        self.calendar.add((start, end))
        retVal = True

        return retVal

# Your MyCalendar object will be instantiated and called as such:
# obj = MyCalendar()
# param_1 = obj.book(start,end)
```

</details>

## [731. My Calendar II](https://leetcode.com/problems/my-calendar-ii/)

- [Official](https://leetcode.com/problems/my-calendar-ii/editorial/)
- [Official](https://leetcode.cn/problems/my-calendar-ii/solutions/1678660/wo-de-ri-cheng-an-pai-biao-ii-by-leetcod-wo6n/)

<details><summary>Description</summary>

```text
You are implementing a program to use as your calendar.
We can add a new event if adding the event will not cause a triple booking.

A triple booking happens when three events have some non-empty intersection
(i.e., some moment is common to all the three events.).

The event can be represented as a pair of integers start and end
that represents a booking on the half-open interval [start, end),
the range of real numbers x such that start <= x < end.

Implement the MyCalendarTwo class:
- MyCalendarTwo()
  Initializes the calendar object.
- boolean book(int start, int end)
  Returns true if the event can be added to the calendar successfully without causing a triple booking.
  Otherwise, return false and do not add the event to the calendar.

Example 1:
Input
["MyCalendarTwo", "book", "book", "book", "book", "book", "book"]
[[], [10, 20], [50, 60], [10, 40], [5, 15], [5, 10], [25, 55]]
Output
[null, true, true, true, false, true, true]
Explanation
MyCalendarTwo myCalendarTwo = new MyCalendarTwo();
myCalendarTwo.book(10, 20); // return True, The event can be booked.
myCalendarTwo.book(50, 60); // return True, The event can be booked.
myCalendarTwo.book(10, 40); // return True, The event can be double booked.
myCalendarTwo.book(5, 15);  // return False, The event cannot be booked, because it would result in a triple booking.
myCalendarTwo.book(5, 10);  // return True, The event can be booked,
as it does not use time 10 which is already double booked.
myCalendarTwo.book(25, 55); // return True, The event can be booked,
as the time in [25, 40) will be double booked with the third event, the time [40, 50) will be single booked,
and the time [50, 55) will be double booked with the second event.

Constraints:
0 <= start < end <= 10^9
At most 1000 calls will be made to book.
```

<details><summary>Hint</summary>

```text
1. Store two sorted lists of intervals: one list will be all times that are at least single booked,
   and another list will be all times that are definitely double booked.
   If none of the double bookings conflict, then the booking will succeed,
   and you should update your single and double bookings accordingly.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MAX_CALLS (1000 + 4)  // At most 1000 calls will be made to book.
typedef struct {
    int bookings[MAX_CALLS][2];
    int bookingsIndex;
    int overlapBookings[MAX_CALLS][2];
    int overlapBookingsIndex;
} MyCalendarTwo;
MyCalendarTwo* myCalendarTwoCreate() {
    MyCalendarTwo* pObj = NULL;

    pObj = (MyCalendarTwo*)malloc(sizeof(MyCalendarTwo));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    memset(pObj, 0, sizeof(MyCalendarTwo));
    pObj->bookingsIndex = 0;
    pObj->overlapBookingsIndex = 0;

    return pObj;
}
// Return true if the booking [start1, end1) & [start2, end2) overlaps.
bool doesOverlap(MyCalendarTwo* obj, int start1, int end1, int start2, int end2) {
    bool retVal = false;

    int maxStart = fmax(start1, start2);
    int minEnd = fmin(end1, end2);
    if (maxStart < minEnd) {
        retVal = true;
    }

    return retVal;
}
// Return overlapping booking between [start1, end1) & [start2, end2).
void getOverlapped(MyCalendarTwo* obj, int start1, int end1, int start2, int end2) {
    obj->overlapBookings[obj->overlapBookingsIndex][0] = fmax(start1, start2);
    obj->overlapBookings[obj->overlapBookingsIndex][1] = fmin(end1, end2);
    obj->overlapBookingsIndex += 1;
}
bool myCalendarTwoBook(MyCalendarTwo* obj, int start, int end) {
    bool retVal = false;

    int i;

    // Returns false if the new booking overlaps with the existing double-booked bookings.
    for (i = 0; i < obj->overlapBookingsIndex; ++i) {
        if (doesOverlap(obj, obj->overlapBookings[i][0], obj->overlapBookings[i][1], start, end) == true) {
            return retVal;
        }
    }

    // Add the double overlapping if any with the new booking.
    int bookStart, bookEnd;
    for (i = 0; i < obj->bookingsIndex; ++i) {
        bookStart = obj->bookings[i][0];
        bookEnd = obj->bookings[i][1];
        if (doesOverlap(obj, bookStart, bookEnd, start, end) == true) {
            getOverlapped(obj, bookStart, bookEnd, start, end);
        }
    }

    // Add the booking to the list of bookings.
    obj->bookings[obj->bookingsIndex][0] = start;
    obj->bookings[obj->bookingsIndex][1] = end;
    obj->bookingsIndex += 1;
    retVal = true;

    return retVal;
}
void myCalendarTwoFree(MyCalendarTwo* obj) {
    free(obj);
    obj = NULL;
}
/**
 * Your MyCalendarTwo struct will be instantiated and called as such:
 * MyCalendarTwo* obj = myCalendarTwoCreate();
 * bool param_1 = myCalendarTwoBook(obj, start, end);
 * myCalendarTwoFree(obj);
 */
```

</details>

<details><summary>C++</summary>

```c++
class MyCalendarTwo {
   private:
    // Return true if the booking [start1, end1) & [start2, end2) overlaps.
    bool doesOverlap(int start1, int end1, int start2, int end2) {
        bool retVal = false;

        if (max(start1, start2) < min(end1, end2)) {
            retVal = true;
        }

        return retVal;
    }
    // Return overlapping booking between [start1, end1) & [start2, end2).
    pair<int, int> getOverlapped(int start1, int end1, int start2, int end2) {
        pair<int, int> retVal;

        retVal = {max(start1, start2), min(end1, end2)};

        return retVal;
    }

   public:
    vector<pair<int, int>> bookings;
    vector<pair<int, int>> overlapBookings;

    MyCalendarTwo() {}
    bool book(int start, int end) {
        bool retVal = false;

        // Returns false if the new booking overlaps with the existing double-booked bookings.
        for (pair<int, int> booking : overlapBookings) {
            if (doesOverlap(booking.first, booking.second, start, end) == true) {
                return retVal;
            }
        }

        // Add the double overlapping if any with the new booking.
        for (pair<int, int> booking : bookings) {
            if (doesOverlap(booking.first, booking.second, start, end) == true) {
                overlapBookings.push_back(getOverlapped(booking.first, booking.second, start, end));
            }
        }

        // Add the booking to the list of bookings.
        bookings.push_back({start, end});
        retVal = true;

        return retVal;
    }
};
/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(start,end);
 */
```

</details>

<details><summary>Python3</summary>

```python
class MyCalendarTwo:
    def __init__(self):
        self.bookings = []
        self.overlapBookings = []

    # Return True if the booking [start1, end1) & [start2, end2) overlaps.
    def doesOverlap(self, start1: int, end1: int, start2: int, end2: int) -> bool:
        retVal = False

        if max(start1, start2) < min(end1, end2):
            retVal = True

        return retVal

    # Return the overlapping booking between [start1, end1) & [start2, end2).
    def getOverlapped(self, start1: int, end1: int, start2: int, end2: int) -> tuple:
        retVal = max(start1, start2), min(end1, end2)

        return retVal

    def book(self, start: int, end: int) -> bool:
        retVal = False

        # Check if the new booking overlaps with any double-booked booking.
        for booking in self.overlapBookings:
            if self.doesOverlap(booking[0], booking[1], start, end) == True:
                return retVal

        # Add any new double overlaps that the current booking creates.
        for booking in self.bookings:
            if self.doesOverlap(booking[0], booking[1], start, end) == True:
                self.overlapBookings.append(self.getOverlapped(booking[0], booking[1], start, end))

        # Add the new booking to the list of bookings.
        self.bookings.append((start, end))
        retVal = True

        return retVal

# Your MyCalendarTwo object will be instantiated and called as such:
# obj = MyCalendarTwo()
# param_1 = obj.book(start,end)
```

</details>

## [786. K-th Smallest Prime Fraction](https://leetcode.com/problems/k-th-smallest-prime-fraction/)  2168

- [Official](https://leetcode.com/problems/k-th-smallest-prime-fraction/editorial/)
- [Official](https://leetcode.cn/problems/k-th-smallest-prime-fraction/solutions/1127103/di-k-ge-zui-xiao-de-su-shu-fen-shu-by-le-argw/)

<details><summary>Description</summary>

```text
You are given a sorted integer array arr containing 1 and prime numbers, where all the integers of arr are unique.
You are also given an integer k.

For every i and j where 0 <= i < j < arr.length, we consider the fraction arr[i] / arr[j].

Return the kth smallest fraction considered.
Return your answer as an array of integers of size 2, where answer[0] == arr[i] and answer[1] == arr[j].

Example 1:
Input: arr = [1,2,3,5], k = 3
Output: [2,5]
Explanation: The fractions to be considered in sorted order are:
1/5, 1/3, 2/5, 1/2, 3/5, and 2/3.
The third fraction is 2/5.

Example 2:
Input: arr = [1,7], k = 1
Output: [1,7]

Constraints:
2 <= arr.length <= 1000
1 <= arr[i] <= 3 * 10^4
arr[0] == 1
arr[i] is a prime number for i > 0.
All the numbers of arr are unique and sorted in strictly increasing order.
1 <= k <= arr.length * (arr.length - 1) / 2

Follow up: Can you solve the problem with better than O(n2) complexity?
```

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *kthSmallestPrimeFraction(int *arr, int arrSize, int k, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 2;
    pRetVal = (int *)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));

    int i, j;
    double maxFraction, fraction;
    int totalSmallerFractions, numeratorIdx, denominatorIdx;
    double middle;
    double left = 0;
    double right = 1.0;
    while (left < right) {
        middle = (left + right) / 2;

        maxFraction = 0.0;
        totalSmallerFractions = 0;
        numeratorIdx = 0;
        denominatorIdx = 0;
        j = 1;
        for (i = 0; i < (arrSize - 1); ++i) {
            while ((j < arrSize) && (arr[i] >= middle * arr[j])) {
                j += 1;
            }

            totalSmallerFractions += (arrSize - j);

            if (j == arrSize) {
                break;
            }

            fraction = (double)(arr[i]) / arr[j];
            if (fraction > maxFraction) {
                numeratorIdx = i;
                denominatorIdx = j;
                maxFraction = fraction;
            }
        }

        if (totalSmallerFractions == k) {
            pRetVal[0] = arr[numeratorIdx];
            pRetVal[1] = arr[denominatorIdx];
            break;
        } else if (totalSmallerFractions > k) {
            right = middle;
        } else {
            left = middle;
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
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        vector<int> retVal;

        int arrSize = arr.size();

        double left = 0;
        double right = 1.0;
        while (left < right) {
            double middle = (left + right) / 2;

            double maxFraction = 0.0;
            int totalSmallerFractions = 0;
            int numeratorIdx = 0;
            int denominatorIdx = 0;
            int j = 1;
            for (int i = 0; i < (arrSize - 1); ++i) {
                while ((j < arrSize) && (arr[i] >= middle * arr[j])) {
                    j += 1;
                }

                totalSmallerFractions += (arrSize - j);

                if (j == arrSize) {
                    break;
                }

                double fraction = static_cast<double>(arr[i]) / arr[j];
                if (fraction > maxFraction) {
                    numeratorIdx = i;
                    denominatorIdx = j;
                    maxFraction = fraction;
                }
            }

            if (totalSmallerFractions == k) {
                retVal.emplace_back(arr[numeratorIdx]);
                retVal.emplace_back(arr[denominatorIdx]);
                break;
            } else if (totalSmallerFractions > k) {
                right = middle;
            } else {
                left = middle;
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
    def kthSmallestPrimeFraction(self, arr: List[int], k: int) -> List[int]:
        retVal = []

        arrSize = len(arr)

        left = 0
        right = 1.0
        while left < right:
            middle = (left + right) / 2

            maxFraction = 0.0
            totalSmallerFractions = 0
            numeratorIdx = 0
            denominatorIdx = 0
            j = 1
            for i in range(arrSize - 1):
                while (j < arrSize) and (arr[i] >= middle * arr[j]):
                    j += 1

                totalSmallerFractions += (arrSize - j)

                if j == arrSize:
                    break

                fraction = arr[i] / arr[j]
                if fraction > maxFraction:
                    numeratorIdx = i
                    denominatorIdx = j
                    maxFraction = fraction

            if totalSmallerFractions == k:
                retVal = [arr[numeratorIdx], arr[denominatorIdx]]
                break
            elif totalSmallerFractions > k:
                right = middle
            else:
                left = middle

        return retVal
```

</details>

## [852. Peak Index in a Mountain Array](https://leetcode.com/problems/peak-index-in-a-mountain-array/)  1181

- [Official](https://leetcode.com/problems/peak-index-in-a-mountain-array/editorial/)
- [Official](https://leetcode.cn/problems/peak-index-in-a-mountain-array/solutions/828156/shan-mai-shu-zu-de-feng-ding-suo-yin-by-dtqvv/)

<details><summary>Description</summary>

```text
An array arr a mountain if the following properties hold:
- arr.length >= 3
- There exists some i with 0 < i < arr.length - 1 such that:
  - arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
  - arr[i] > arr[i + 1] > ... > arr[arr.length - 1]

Given a mountain array arr,
return the index i such that arr[0] < arr[1] < ... < arr[i - 1] < arr[i] > arr[i + 1] > ... > arr[arr.length - 1].

You must solve it in O(log(arr.length)) time complexity.

Example 1:
Input: arr = [0,1,0]
Output: 1

Example 2:
Input: arr = [0,2,1,0]
Output: 1

Example 3:
Input: arr = [0,10,5,2]
Output: 1

Constraints:
3 <= arr.length <= 10^5
0 <= arr[i] <= 10^6
arr is guaranteed to be a mountain array.
```

</details>

<details><summary>C</summary>

```c
int peakIndexInMountainArray(int* arr, int arrSize) {
    int retVal = 0;

    int middle;
    int left = 0;
    int right = arrSize - 1;
    while (left < right) {
        middle = left + (right - left) / 2;
        if (arr[middle] < arr[middle + 1]) {
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
    int peakIndexInMountainArray(vector<int>& arr) {
        int retVal = 0;

        int arrSize = arr.size();
        int left = 0;
        int right = arrSize - 1;
        while (left < right) {
            int middle = left + (right - left) / 2;
            if (arr[middle] < arr[middle + 1]) {
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
    def peakIndexInMountainArray(self, arr: List[int]) -> int:
        retVal = 0

        arrSize = len(arr)
        left = 0
        right = arrSize - 1
        while left < right:
            middle = left + (right - left) // 2
            if arr[middle] < arr[middle + 1]:
                left = middle + 1
            else:
                right = middle
        retVal = left

        return retVal
```

</details>

## [875. Koko Eating Bananas](https://leetcode.com/problems/koko-eating-bananas/)  1765

- [Official](https://leetcode.cn/problems/koko-eating-bananas/solutions/1537914/ai-chi-xiang-jiao-de-ke-ke-by-leetcode-s-z4rt/)

<details><summary>Description</summary>

```text
Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas.
The guards have gone and will come back in h hours.

Koko can decide her bananas-per-hour eating speed of k.
Each hour, she chooses some pile of bananas and eats k bananas from that pile.
If the pile has less than k bananas, she eats all of them instead and will not eat any more bananas during this hour.

Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.

Return the minimum integer k such that she can eat all the bananas within h hours.

Example 1:
Input: piles = [3,6,7,11], h = 8
Output: 4

Example 2:
Input: piles = [30,11,23,4,20], h = 5
Output: 30

Example 3:
Input: piles = [30,11,23,4,20], h = 6
Output: 23

Constraints:
1 <= piles.length <= 10^4
piles.length <= h <= 10^9
1 <= piles[i] <= 10^9
```

</details>

<details><summary>C</summary>

```c
int minEatingSpeed(int *piles, int pilesSize, int h) {
    int retVal = 0;

    int i;

    int left = 1;
    int right = 0;
    for (i = 0; i < pilesSize; ++i) {
        right = fmax(right, piles[i]);
    }

    int useHour;
    int middle;
    while (left < right) {
        middle = left + (right - left) / 2;

        useHour = 0;
        for (i = 0; i < pilesSize; ++i) {
            // ceiling of an integer division
            useHour += ((piles[i] + middle - 1) / middle);
        }
        if (useHour > h) {
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
    int minEatingSpeed(vector<int>& piles, int h) {
        int retVal;

        int left = 1;
        int right = *max_element(piles.begin(), piles.end());
        while (left < right) {
            int middle = left + (right - left) / 2;

            int useHour = 0;
            for (auto pile : piles) {
                // ceiling of an integer division
                useHour += ((pile + middle - 1) / middle);
            }
            if (useHour > h) {
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
    def minEatingSpeed(self, piles: List[int], h: int) -> int:
        retVal = 0

        left = 1
        right = max(piles)
        while left < right:
            middle = left + (right - left) // 2

            useHour = 0
            for pile in piles:
                useHour += ((pile + middle - 1) // middle)

            if useHour > h:
                left = middle + 1
            else:
                right = middle
        retVal = left

        return retVal
```

</details>

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

## [2064. Minimized Maximum of Products Distributed to Any Store](https://leetcode.com/problems/minimized-maximum-of-products-distributed-to-any-store/)  1885

- [Official](https://leetcode.com/problems/minimized-maximum-of-products-distributed-to-any-store/editorial/)
- [Official](https://leetcode.cn/problems/minimized-maximum-of-products-distributed-to-any-store/solutions/1101801/fen-pei-gei-shang-dian-de-zui-duo-shang-g0nc2/)

<details><summary>Description</summary>

```text
You are given an integer n indicating there are n specialty retail stores.
There are m product types of varying amounts, which are given as a 0-indexed integer array quantities,
where quantities[i] represents the number of products of the ith product type.

You need to distribute all products to the retail stores following these rules:
- A store can only be given at most one product type but can be given any amount of it.
- After distribution, each store will have been given some number of products (possibly 0).
  Let x represent the maximum number of products given to any store.
  You want x to be as small as possible,
  i.e., you want to minimize the maximum number of products that are given to any store.

Return the minimum possible x.

Example 1:
Input: n = 6, quantities = [11,6]
Output: 3
Explanation: One optimal way is:
- The 11 products of type 0 are distributed to the first four stores in these amounts: 2, 3, 3, 3
- The 6 products of type 1 are distributed to the other two stores in these amounts: 3, 3
The maximum number of products given to any store is max(2, 3, 3, 3, 3, 3) = 3.

Example 2:
Input: n = 7, quantities = [15,10,10]
Output: 5
Explanation: One optimal way is:
- The 15 products of type 0 are distributed to the first three stores in these amounts: 5, 5, 5
- The 10 products of type 1 are distributed to the next two stores in these amounts: 5, 5
- The 10 products of type 2 are distributed to the last two stores in these amounts: 5, 5
The maximum number of products given to any store is max(5, 5, 5, 5, 5, 5, 5) = 5.

Example 3:
Input: n = 1, quantities = [100000]
Output: 100000
Explanation: The only optimal way is:
- The 100000 products of type 0 are distributed to the only store.
The maximum number of products given to any store is max(100000) = 100000.

Constraints:
m == quantities.length
1 <= m <= n <= 10^5
1 <= quantities[i] <= 10^5
```

<details><summary>Hint</summary>

```text
1. There exists a monotonic nature such that when x is smaller than some number, there will be no way to distribute,
   and when x is not smaller than that number, there will always be a way to distribute.
2. If you are given a number k, where the number of products given to any store does not exceed k,
   could you determine if all products can be distributed?
3. Implement a function canDistribute(k), which returns true if you can distribute all products
   such that any store will not be given more than k products, and returns false if you cannot.
   Use this function to binary search for the smallest possible k.
```

</details>

</details>

<details><summary>C</summary>

```c
bool canDistribute(int x, int* quantities, int quantitiesSize, int n) {
    bool retVal = false;

    int j = 0;
    int remaining = quantities[j];
    int i;
    for (i = 0; i < n; i++) {
        if (remaining > x) {
            remaining -= x;
            continue;
        }

        j++;
        if (j == quantitiesSize) {
            retVal = true;
            break;
        }
        remaining = quantities[j];
    }

    return retVal;
}
int minimizedMaximum(int n, int* quantities, int quantitiesSize) {
    int retVal = 0;

    int maxElement = quantities[0];
    for (int i = 1; i < quantitiesSize; ++i) {
        if (maxElement < quantities[i]) {
            maxElement = quantities[i];
        }
    }

    int middle;
    int left = 0;
    int right = maxElement;
    while (left < right) {
        middle = (left + right) / 2;
        if (canDistribute(middle, quantities, quantitiesSize, n) == true) {
            right = middle;
        } else {
            left = middle + 1;
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
   private:
    bool canDistribute(int x, vector<int>& quantities, int n) {
        bool retVal = false;

        int quantitiesSize = quantities.size();
        int j = 0;
        int remaining = quantities[j];
        for (int i = 0; i < n; i++) {
            if (remaining > x) {
                remaining -= x;
                continue;
            }

            j++;
            if (j == quantitiesSize) {
                retVal = true;
                break;
            }
            remaining = quantities[j];
        }

        return retVal;
    }

   public:
    int minimizedMaximum(int n, vector<int>& quantities) {
        int retVal = 0;

        int left = 0;
        int right = *max_element(quantities.begin(), quantities.end());
        while (left < right) {
            int middle = (left + right) / 2;
            if (canDistribute(middle, quantities, n) == true) {
                right = middle;
            } else {
                left = middle + 1;
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
    def canDistribute(self, x: int, quantities: List[int], n: int) -> bool:
        retVal = False

        quantitiesSize = len(quantities)

        i = 0
        remaining = quantities[i]
        for _ in range(n):
            if remaining > x:
                remaining -= x
                continue

            i += 1
            if i == quantitiesSize:
                retVal = True
                break
            remaining = quantities[i]

        return retVal

    def minimizedMaximum(self, n: int, quantities: List[int]) -> int:
        retVal = 0

        left = 0
        right = max(quantities)
        while left < right:
            middle = (left + right) // 2
            if self.canDistribute(middle, quantities, n) == True:
                right = middle
            else:
                left = middle + 1
        retVal = left

        return retVal
```

</details>

## [2141. Maximum Running Time of N Computers](https://leetcode.com/problems/maximum-running-time-of-n-computers/)  2265

- [Official](https://leetcode.com/problems/maximum-running-time-of-n-computers/editorial/)
- [Official](https://leetcode.cn/problems/maximum-running-time-of-n-computers/solutions/1216064/tong-shi-yun-xing-n-tai-dian-nao-de-zui-ozvvu/)

<details><summary>Description</summary>

```text
You have n computers. You are given the integer n and a 0-indexed integer array batteries
where the ith battery can run a computer for batteries[i] minutes.
You are interested in running all n computers simultaneously using the given batteries.

Initially, you can insert at most one battery into each computer. After that and at any integer time moment,
you can remove a battery from a computer and insert another battery any number of times.
The inserted battery can be a totally new battery or a battery from another computer.
You may assume that the removing and inserting processes take no time.

Note that the batteries cannot be recharged.

Return the maximum number of minutes you can run all the n computers simultaneously.

Example 1:
Input: n = 2, batteries = [3,3,3]
Output: 4
Explanation:
Initially, insert battery 0 into the first computer and battery 1 into the second computer.
After two minutes, remove battery 1 from the second computer and insert battery 2 instead.
Note that battery 1 can still run for one minute.
At the end of the third minute, battery 0 is drained,
and you need to remove it from the first computer and insert battery 1 instead.
By the end of the fourth minute, battery 1 is also drained, and the first computer is no longer running.
We can run the two computers simultaneously for at most 4 minutes, so we return 4.

Example 2:
Input: n = 2, batteries = [1,1,1,1]
Output: 2
Explanation:
Initially, insert battery 0 into the first computer and battery 2 into the second computer.
After one minute, battery 0 and battery 2 are drained
so you need to remove them and insert battery 1 into the first computer and battery 3 into the second computer.
After another minute, battery 1 and battery 3 are also drained so the first and second computers are no longer running.
We can run the two computers simultaneously for at most 2 minutes, so we return 2.

Constraints:
1 <= n <= batteries.length <= 10^5
1 <= batteries[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. For a given running time, can you determine if it is possible to run all n computers simultaneously?
2. Try to use Binary Search to find the maximal running time
```

</details>

</details>

<details><summary>C</summary>

```c
long long maxRunTime(int n, int* batteries, int batteriesSize) {
    long long retVal = 0;

    int i;

    long sumPower = 0;
    for (i = 0; i < batteriesSize; ++i) {
        sumPower += batteries[i];
    }

    long long middle;
    long long left = 1;
    long long right = sumPower / n;
    while (left < right) {
        middle = right - (right - left) / 2;

        long long total = 0;
        for (i = 0; i < batteriesSize; ++i) {
            total += fmin(batteries[i], middle);
        }
        if (total >= (long long)(n * middle)) {
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
    long long maxRunTime(int n, vector<int>& batteries) {
        long long retVal = 0;

        long sumPower = 0;
        for (auto battery : batteries) {
            sumPower += battery;
        }

        long long left = 1;
        long long right = sumPower / n;
        while (left < right) {
            long long middle = right - (right - left) / 2;

            long long total = 0;
            for (long long battery : batteries) {
                total += min(battery, middle);
            }
            if (total >= (long long)(n * middle)) {
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
    def maxRunTime(self, n: int, batteries: List[int]) -> int:
        retVal = 0

        left = 1
        right = sum(batteries) // n
        while left < right:
            middle = right - (right - left) // 2

            total = 0
            for power in batteries:
                total += min(power, middle)
            if total // n >= middle:
                left = middle
            else:
                right = middle - 1

        retVal = left

        return retVal
```

</details>

## [2187. Minimum Time to Complete Trips](https://leetcode.com/problems/minimum-time-to-complete-trips/)  1640

- [Official](https://leetcode.cn/problems/minimum-time-to-complete-trips/solutions/1300957/wan-cheng-lu-tu-de-zui-shao-shi-jian-by-uxyrp/)

<details><summary>Description</summary>

```text
You are given an array time where time[i] denotes the time taken by the ith bus to complete one trip.

Each bus can make multiple trips successively;
that is, the next trip can start immediately after completing the current trip.
Also, each bus operates independently; that is, the trips of one bus do not influence the trips of any other bus.

You are also given an integer totalTrips, which denotes the number of trips all buses should make in total.
Return the minimum time required for all buses to complete at least totalTrips trips.

Example 1:
Input: time = [1,2,3], totalTrips = 5
Output: 3
Explanation:
- At time t = 1, the number of trips completed by each bus are [1,0,0].
  The total number of trips completed is 1 + 0 + 0 = 1.
- At time t = 2, the number of trips completed by each bus are [2,1,0].
  The total number of trips completed is 2 + 1 + 0 = 3.
- At time t = 3, the number of trips completed by each bus are [3,1,1].
  The total number of trips completed is 3 + 1 + 1 = 5.
So the minimum time needed for all buses to complete at least 5 trips is 3.

Example 2:
Input: time = [2], totalTrips = 1
Output: 2
Explanation:
There is only one bus, and it will complete its first trip at t = 2.
So the minimum time needed to complete 1 trip is 2.

Constraints:
1 <= time.length <= 10^5
1 <= time[i], totalTrips <= 10^7
```

<details><summary>Hint</summary>

```text
1. For a given amount of time, how can we count the total number of trips completed by all buses within that time?
2. Consider using binary search.
```

</details>

</details>

<details><summary>C</summary>

```c
long long minimumTime(int *time, int timeSize, int totalTrips) {
    long long retVal = 0;

    long long minTime = time[0];
    int i;
    for (i = 1; i < timeSize; ++i) {
        minTime = fmin(minTime, time[i]);
    }

    long long tmpTrip = 0;
    long long middle;
    long long left = 1;
    long long right = (long long)totalTrips * minTime;
    while (left < right) {
        middle = left + (right - left) / 2;

        tmpTrip = 0;
        for (i = 0; i < timeSize; ++i) {
            tmpTrip += (middle / time[i]);
        }

        if (tmpTrip < totalTrips) {
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
    long long minimumTime(vector<int>& time, int totalTrips) {
        long long retVal = 0;

        long long left = 1;
        long long right = (long long)totalTrips * (*min_element(time.begin(), time.end()));
        while (left < right) {
            long long middle = left + (right - left) / 2;

            long long tmpTrip = 0;
            for (auto iter : time) {
                tmpTrip += (middle / iter);
            }

            if (tmpTrip < totalTrips) {
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
    def minimumTime(self, time: List[int], totalTrips: int) -> int:
        retVal = 0

        left = 0
        right = min(time) * totalTrips
        while left < right:
            middle = left + (right - left) // 2

            tmpTrips = 0
            for iterator in time:
                tmpTrips += (middle//iterator)

            if tmpTrips < totalTrips:
                left = middle + 1
            else:
                right = middle
        retVal = left

        return retVal
```

</details>

## [2226. Maximum Candies Allocated to K Children](https://leetcode.com/problems/maximum-candies-allocated-to-k-children/)  1646

- [Official](https://leetcode.cn/problems/maximum-candies-allocated-to-k-children/solutions/1398462/mei-ge-xiao-hai-zui-duo-neng-fen-dao-duo-2717/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array candies.
Each element in the array denotes a pile of candies of size candies[i].
You can divide each pile into any number of sub piles, but you cannot merge two piles together.

You are also given an integer k.
You should allocate piles of candies to k children such that each child gets the same number of candies.
Each child can take at most one pile of candies and some piles of candies may go unused.

Return the maximum number of candies each child can get.

Example 1:
Input: candies = [5,8,6], k = 3
Output: 5
Explanation: We can divide candies[1] into 2 piles of size 5 and 3, and candies[2] into 2 piles of size 5 and 1.
We now have five piles of candies of sizes 5, 5, 3, 5, and 1.
We can allocate the 3 piles of size 5 to 3 children. It can be proven that each child cannot receive more than 5 candies.

Example 2:
Input: candies = [2,5], k = 11
Output: 0
Explanation: There are 11 children but only 7 candies in total,
so it is impossible to ensure each child receives at least one candy.
Thus, each child gets no candy and the answer is 0.

Constraints:
1 <= candies.length <= 10^5
1 <= candies[i] <= 10^7
1 <= k <= 10^12
```

<details><summary>Hint</summary>

```text
1. For a fixed number of candies c, how can you check if each child can get c candies?
2. Use binary search to find the maximum c as the answer.
```

</details>

</details>

<details><summary>C</summary>

```c
int maximumCandies(int *candies, int candiesSize, long long k) {
    int retVal = 0;

    int i;

    int maxCandies = candies[0];
    for (i = 1; i < candiesSize; ++i) {
        maxCandies = fmax(maxCandies, candies[i]);
    }

    long long tmpCandies;
    int middle;
    int left = 1;
    int right = 1 + maxCandies;
    while (left < right) {
        middle = left + (right - left) / 2;

        tmpCandies = 0;
        for (i = 0; i < candiesSize; ++i) {
            tmpCandies += (candies[i] / middle);
        }

        if (tmpCandies >= k) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    retVal = left - 1;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maximumCandies(vector<int>& candies, long long k) {
        int retVal = 0;

        int left = 1;
        int right = 1 + (*max_element(candies.begin(), candies.end()));
        while (left < right) {
            int middle = left + (right - left) / 2;

            long long tmpCandies = 0;
            for (auto candy : candies) {
                tmpCandies += (candy / middle);
            }

            if (tmpCandies >= k) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }
        retVal = left - 1;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maximumCandies(self, candies: List[int], k: int) -> int:
        retVal = 0

        left = 1
        right = 1 + max(candies)
        while left < right:
            middle = left + (right - left) // 2

            tmpCandies = 0
            for candy in candies:
                tmpCandies += candy // middle

            if tmpCandies >= k:
                left = middle + 1
            else:
                right = middle
        retVal = left - 1

        return retVal
```

</details>

## [2251. Number of Flowers in Full Bloom](https://leetcode.com/problems/number-of-flowers-in-full-bloom/)  2022

- [Official](https://leetcode.com/problems/number-of-flowers-in-full-bloom/editorial/)
- [Official](https://leetcode.cn/problems/number-of-flowers-in-full-bloom/solutions/2457828/hua-qi-nei-hua-de-shu-mu-by-leetcode-sol-j94l/)

<details><summary>Description</summary>

```text
You are given a 0-indexed 2D integer array flowers,
where flowers[i] = [starti, endi] means the ith flower will be in full bloom from starti to endi (inclusive).
You are also given a 0-indexed integer array people of size n,
where people[i] is the time that the ith person will arrive to see the flowers.

Return an integer array answer of size n,
where answer[i] is the number of flowers that are in full bloom when the ith person arrives.

Example 1:
Input: flowers = [[1,6],[3,7],[9,12],[4,13]], poeple = [2,3,7,11]
Output: [1,2,2,2]
Explanation: The figure above shows the times when the flowers are in full bloom and when the people arrive.
For each person, we return the number of flowers in full bloom during their arrival.

Example 2:
Input: flowers = [[1,10],[3,3]], poeple = [3,3,2]
Output: [2,2,1]
Explanation: The figure above shows the times when the flowers are in full bloom and when the people arrive.
For each person, we return the number of flowers in full bloom during their arrival.

Constraints:
1 <= flowers.length <= 5 * 10^4
flowers[i].length == 2
1 <= starti <= endi <= 10^9
1 <= people.length <= 5 * 10^4
1 <= people[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Notice that for any given time t, the number of flowers blooming at time t is equal to
   the number of flowers that have started blooming minus the number of flowers that have already stopped blooming.
2. We can obtain these values efficiently using binary search.
3. We can store the starting times in sorted order,
   which then allows us to binary search to find how many flowers have started blooming for a given time t.
4. We do the same for the ending times to find how many flowers have stopped blooming at time t.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int binarySearch(int* arr, int left, int right, int val) {
    int retVal = right + 1;

    int middle;
    while (left <= right) {
        middle = left + (right - left) / 2;

        if (arr[middle] > val) {
            retVal = middle;
            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }

    return retVal;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* fullBloomFlowers(int** flowers, int flowersSize, int* flowersColSize, int* people, int peopleSize,
                      int* returnSize) {
    int* pRetVal = NULL;

    int starts[flowersSize];
    memset(starts, 0, sizeof(starts));
    int ends[flowersSize];
    memset(ends, 0, sizeof(ends));
    int i;
    for (i = 0; i < flowersSize; ++i) {
        starts[i] = flowers[i][0];
        ends[i] = flowers[i][1] + 1;
    }
    qsort(starts, flowersSize, sizeof(int), compareInteger);
    qsort(ends, flowersSize, sizeof(int), compareInteger);

    (*returnSize) = 0;
    pRetVal = (int*)malloc(peopleSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    int x, y;
    for (i = 0; i < peopleSize; ++i) {
        x = binarySearch(starts, 0, flowersSize - 1, people[i]);
        y = binarySearch(ends, 0, flowersSize - 1, people[i]);
        pRetVal[i] = x - y;
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
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& people) {
        vector<int> retVal;

        vector<int> starts;
        vector<int> ends;
        for (vector<int>& flower : flowers) {
            starts.push_back(flower[0]);
            ends.push_back(flower[1] + 1);
        }
        sort(starts.begin(), starts.end());
        sort(ends.begin(), ends.end());

        for (int p : people) {
            int i = upper_bound(starts.begin(), starts.end(), p) - starts.begin();
            int j = upper_bound(ends.begin(), ends.end(), p) - ends.begin();
            retVal.push_back(i - j);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def fullBloomFlowers(self, flowers: List[List[int]], people: List[int]) -> List[int]:
        retVal = []

        starts = []
        ends = []
        for start, end in flowers:
            starts.append(start)
            ends.append(end + 1)
        starts.sort()
        ends.sort()

        for p in people:
            i = bisect_right(starts, p)
            j = bisect_right(ends, p)
            retVal.append(i - j)

        return retVal
```

</details>

## [2300. Successful Pairs of Spells and Potions](https://leetcode.com/problems/successful-pairs-of-spells-and-potions/)  1476

<details><summary>Description</summary>

```text
You are given two positive integer arrays spells and potions, of length n and m respectively,
where spells[i] represents the strength of the ith spell and potions[j] represents the strength of the jth potion.

You are also given an integer success.
A spell and potion pair is considered successful if the product of their strengths is at least success.

Return an integer array pairs of length n where pairs[i] is the number of potions
that will form a successful pair with the ith spell.

Example 1:
Input: spells = [5,1,3], potions = [1,2,3,4,5], success = 7
Output: [4,0,3]
Explanation:
- 0th spell: 5 * [1,2,3,4,5] = [5,10,15,20,25]. 4 pairs are successful.
- 1st spell: 1 * [1,2,3,4,5] = [1,2,3,4,5]. 0 pairs are successful.
- 2nd spell: 3 * [1,2,3,4,5] = [3,6,9,12,15]. 3 pairs are successful.
Thus, [4,0,3] is returned.

Example 2:
Input: spells = [3,1,2], potions = [8,5,8], success = 16
Output: [2,0,2]
Explanation:
- 0th spell: 3 * [8,5,8] = [24,15,24]. 2 pairs are successful.
- 1st spell: 1 * [8,5,8] = [8,5,8]. 0 pairs are successful.
- 2nd spell: 2 * [8,5,8] = [16,10,16]. 2 pairs are successful.
Thus, [2,0,2] is returned.

Constraints:
n == spells.length
m == potions.length
1 <= n, m <= 10^5
1 <= spells[i], potions[i] <= 10^5
1 <= success <= 10^10
```

<details><summary>Hint</summary>

```text
1. Notice that if a spell and potion pair is successful, then the spell and all stronger potions will be successful too.
2. Thus, for each spell, we need to find the potion with the least strength that will form a successful pair.
3. We can efficiently do this by sorting the potions based on strength and using binary search.
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
int* successfulPairs(int* spells, int spellsSize, int* potions, int potionsSize, long long success, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = spellsSize;
    pRetVal = (int*)calloc((*returnSize), sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        (*returnSize) = 0;
        return pRetVal;
    }

    qsort(potions, potionsSize, sizeof(int), compareInteger);
    long divisor;
    int left, right, middle;
    int i;
    for (i = 0; i < spellsSize; ++i) {
        divisor = (success + spells[i] - 1) / spells[i];

        left = 0;
        right = potionsSize;
        while (left < right) {
            middle = left + (right - left) / 2;
            if (potions[middle] < divisor) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }

        pRetVal[i] = potionsSize - left;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        vector<int> retVal;

        sort(potions.begin(), potions.end());
        for (auto spell : spells) {
            long divisor = (success + spell - 1) / spell;
            auto iterator = lower_bound(potions.begin(), potions.end(), divisor);
            retVal.emplace_back(potions.end() - iterator);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def successfulPairs(self, spells: List[int], potions: List[int], success: int) -> List[int]:
        retVal = []

        potions.sort()
        for spell in spells:
            divisor = (success + spell - 1) // spell
            iterator = bisect_left(potions, divisor)
            retVal.append(len(potions) - iterator)

        return retVal
```

</details>

## [2389. Longest Subsequence With Limited Sum](https://leetcode.com/problems/longest-subsequence-with-limited-sum/)  1387

- [Official](https://leetcode.com/problems/longest-subsequence-with-limited-sum/solutions/2644327/longest-subsequence-with-limited-sum/)

<details><summary>Description</summary>

```text
You are given an integer array nums of length n, and an integer array queries of length m.

Return an array answer of length m where answer[i] is the maximum size of a subsequence
that you can take from nums such that the sum of its elements is less than or equal to queries[i].

A subsequence is an array that can be derived from another array by deleting some
or no elements without changing the order of the remaining elements.

Example 1:
Input: nums = [4,5,2,1], queries = [3,10,21]
Output: [2,3,4]
Explanation: We answer the queries as follows:
- The subsequence [2,1] has a sum less than or equal to 3.
  It can be proven that 2 is the maximum size of such a subsequence, so answer[0] = 2.
- The subsequence [4,5,1] has a sum less than or equal to 10.
  It can be proven that 3 is the maximum size of such a subsequence, so answer[1] = 3.
- The subsequence [4,5,2,1] has a sum less than or equal to 21.
  It can be proven that 4 is the maximum size of such a subsequence, so answer[2] = 4.

Example 2:
Input: nums = [2,3,4,5], queries = [1]
Output: [0]
Explanation: The empty subsequence is the only subsequence that has a sum less than or equal to 1, so answer[0] = 0.

Constraints:
n == nums.length
m == queries.length
1 <= n, m <= 1000
1 <= nums[i], queries[i] <= 10^6
```

<details><summary>Hint</summary>

```text
1. Solve each query independently.
2. When solving a query, which elements of nums should you choose to make the subsequence as long as possible?
3. Choose the smallest elements in nums that add up to a sum less than the query.
```

</details>

</details>

<details><summary>C</summary>

```c
#define BINARY_SEARCH (1)
#define SORTING (1)
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* answerQueries(int* nums, int numsSize, int* queries, int queriesSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = queriesSize;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));

    qsort(nums, numsSize, sizeof(int), compareInteger);

#if (BINARY_SEARCH)
    printf("BINARY_SEARCH\n");

    int i;

    int prefixSum[numsSize];
    memset(prefixSum, 0, sizeof(prefixSum));
    prefixSum[0] = nums[0];
    for (i = 1; i < numsSize; ++i) {
        prefixSum[i] = nums[i] + prefixSum[i - 1];
    }

    int left, right, middle;
    for (i = 0; i < queriesSize; ++i) {
        left = 0;
        right = numsSize;
        while (left < right) {
            middle = left + (right - left) / 2;
            if (prefixSum[middle] <= queries[i]) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }

        pRetVal[i] = right;
    }

#elif (SORTING)
    printf("SORTING\n");

    int i, j;
    for (i = 0; i < queriesSize; ++i) {
        for (j = 0; j < numsSize; ++j) {
            if (queries[i] < nums[j]) {
                break;
            }
            queries[i] -= nums[j];
            ++pRetVal[i];
        }
    }
#endif

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define BINARY_SEARCH (1)
#define SORTING (1)
   public:
    vector<int> answerQueries(vector<int>& nums, vector<int>& queries) {
        vector<int> retVal;

        sort(nums.begin(), nums.end());
#if (BINARY_SEARCH)
        cout << "BINARY_SEARCH\n";

        int numsSize = nums.size();
        vector<int> prefixSum(numsSize, 0);
        prefixSum[0] = nums[0];
        for (int i = 1; i < numsSize; ++i) {
            prefixSum[i] = nums[i] + prefixSum[i - 1];
        }

        for (auto query : queries) {
            auto iterator = upper_bound(prefixSum.begin(), prefixSum.end(), query);
            retVal.emplace_back(iterator - prefixSum.begin());
        }
#elif (SORTING)
        cout << "SORTING\n";

        for (int query : queries) {
            int count = 0;
            for (int num : nums) {
                query -= num;
                if (query < 0) {
                    break;
                }
                ++count;
            }
            retVal.emplace_back(count);
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
    def __init__(self):
        self.method = 1

    def answerQueries(self, nums: List[int], queries: List[int]) -> List[int]:
        retVal = []

        if self.method == 1:
            print("Binary Search")

            nums.sort()
            prefixSum = list(accumulate(nums))
            for query in queries:
                iterator = bisect_right(prefixSum, query)
                retVal.append(iterator)

        elif self.method == 2:
            print("Sorting")

            nums.sort()
            for query in queries:
                count = 0
                for num in nums:
                    query -= num
                    if query < 0:
                        break
                    count += 1
                retVal.append(count)

        return retVal
```

</details>

## [2439. Minimize Maximum of Array](https://leetcode.com/problems/minimize-maximum-of-array/)  1965

<details><summary>Description</summary>

```text
You are given a 0-indexed array nums comprising of n non-negative integers.

In one operation, you must:
- Choose an integer i such that 1 <= i < n and nums[i] > 0.
- Decrease nums[i] by 1.
- Increase nums[i - 1] by 1.

Return the minimum possible value of the maximum integer of nums after performing any number of operations.

Example 1:
Input: nums = [3,7,1,6]
Output: 5
Explanation:
One set of optimal operations is as follows:
1. Choose i = 1, and nums becomes [4,6,1,6].
2. Choose i = 3, and nums becomes [4,6,2,5].
3. Choose i = 1, and nums becomes [5,5,2,5].
The maximum integer of nums is 5. It can be shown that the maximum number cannot be less than 5.
Therefore, we return 5.

Example 2:
Input: nums = [10,1]
Output: 10
Explanation:
It is optimal to leave nums as is, and since 10 is the maximum value, we return 10.

Constraints:
n == nums.length
2 <= n <= 10^5
0 <= nums[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Try a binary search approach.
2. Perform a binary search over the minimum value that can be achieved for the maximum number of the array.
3. In each binary search iteration, iterate through the array backwards,
   greedily decreasing the current element until it is within the limit.
```

</details>

</details>

<details><summary>C</summary>

```c
#define BINARY_SEARCH (1)
#define AVERAGE (1)
int minimizeArrayValue(int *nums, int numsSize) {
    int retVal = 0;

#if (BINARY_SEARCH)
    printf("BINARY_SEARCH\n");

    int i;

    int maxValue = 0;
    for (i = 0; i < numsSize; ++i) {
        maxValue = fmax(maxValue, nums[i]);
    }

    bool operationFlag;
    /* use long to avoid signed integer overflow
     *  n == nums.length
     *  2 <= n <= 10^5
     *  0 <= nums[i] <= 10^9
     */
    long operation;
    int left = 0;
    int right = maxValue;
    int middle;
    while (left < right) {
        middle = left + (right - left) / 2;

        operationFlag = true;
        operation = 0;
        for (i = 0; i < numsSize; ++i) {
            if (nums[i] <= middle) {
                operation += (middle - nums[i]);
                continue;
            }

            if (operation < (nums[i] - middle)) {
                operationFlag = false;
                break;
            }

            operation -= (nums[i] - middle);
        }

        if (operationFlag == false) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    retVal = left;

#elif (AVERAGE)
    printf("AVERAGE\n");

    // https://leetcode.com/problems/minimize-maximum-of-array/solutions/2706521/java-c-python-prefix-sum-average-o-n/
    int prefixSumSize = numsSize;
    /* use long to avoid signed integer overflow
     *  n == nums.length
     *  2 <= n <= 10^5
     *  0 <= nums[i] <= 10^9
     */
    long prefixSum[prefixSumSize];
    memset(prefixSum, 0, sizeof(prefixSum));
    prefixSum[0] = nums[0];

    int i;
    for (i = 1; i < prefixSumSize; ++i) {
        prefixSum[i] = nums[i] + prefixSum[i - 1];
    }

    for (i = 0; i < prefixSumSize; ++i) {
        retVal = fmax((long)retVal, ((prefixSum[i] + i) / (i + 1)));
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
#define AVERAGE (1)
   public:
    int minimizeArrayValue(vector<int>& nums) {
        int retVal = 0;

#if (BINARY_SEARCH)
        cout << "BINARY_SEARCH\n";

        int left = 0;
        int right = *max_element(nums.begin(), nums.end());
        while (left < right) {
            int middle = left + (right - left) / 2;

            bool operationFlag = true;
            /* use long to avoid signed integer overflow
             *  n == nums.length
             *  2 <= n <= 10^5
             *  0 <= nums[i] <= 10^9
             */
            long operation = 0;
            for (auto num : nums) {
                if (num <= middle) {
                    operation += (middle - num);
                    continue;
                }

                if (operation < (num - middle)) {
                    operationFlag = false;
                    break;
                }

                operation -= (num - middle);
            }

            if (operationFlag == false) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }
        retVal = left;

#elif (AVERAGE)
        cout << "AVERAGE\n";

        // https://leetcode.com/problems/minimize-maximum-of-array/solutions/2706521/java-c-python-prefix-sum-average-o-n/
        int prefixSumSize = nums.size();
        /* use long to avoid signed integer overflow
         *  n == nums.length
         *  2 <= n <= 10^5
         *  0 <= nums[i] <= 10^9
         */
        vector<long> prefixSum(prefixSumSize, 0);

        prefixSum[0] = nums[0];
        for (int i = 1; i < prefixSumSize; ++i) {
            prefixSum[i] = nums[i] + prefixSum[i - 1];
        }

        for (int i = 0; i < prefixSumSize; ++i) {
            retVal = max((long)retVal, ((prefixSum[i] + i) / (i + 1)));
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
    def __init__(self):
        self.method = 1

    def minimizeArrayValue(self, nums: List[int]) -> int:
        retVal = 0

        if self.method == 1:
            print("Binary Search")

            left = 0
            right = max(nums)
            while left < right:
                middle = left + (right - left) // 2

                operationFlag = True
                operation = 0
                for num in nums:
                    if num <= middle:
                        operation += (middle - num)
                        continue

                    if operation < (num - middle):
                        operationFlag = False
                        break
                    operation -= (num - middle)

                if operationFlag == False:
                    left = middle + 1
                else:
                    right = middle
            retVal = left
        elif self.method == 2:
            print("Average")

            # https://leetcode.com/problems/minimize-maximum-of-array/solutions/2706521/java-c-python-prefix-sum-average-o-n/
            prefixSum = list(accumulate(nums))
            prefixSumSize = len(prefixSum)
            for i in range(prefixSumSize):
                retVal = max(retVal, ((prefixSum[i] + i) // (i + 1)))

        return retVal
```

</details>

## [2448. Minimum Cost to Make Array Equal](https://leetcode.com/problems/minimum-cost-to-make-array-equal/)  2005

- [Official](https://leetcode.com/problems/minimum-cost-to-make-array-equal/editorial/)

<details><summary>Description</summary>

```text
You are given two 0-indexed arrays nums and cost consisting each of n positive integers.

You can do the following operation any number of times:
- Increase or decrease any element of the array nums by 1.

The cost of doing one operation on the ith element is cost[i].

Return the minimum total cost such that all the elements of the array nums become equal.

Example 1:
Input: nums = [1,3,5,2], cost = [2,3,1,14]
Output: 8
Explanation: We can make all the elements equal to 2 in the following way:
- Increase the 0th element one time. The cost is 2.
- Decrease the 1st element one time. The cost is 3.
- Decrease the 2nd element three times. The cost is 1 + 1 + 1 = 3.
The total cost is 2 + 3 + 3 = 8.
It can be shown that we cannot make the array equal with a smaller cost.

Example 2:
Input: nums = [2,2,2,2,2], cost = [4,2,8,1,3]
Output: 0
Explanation: All the elements are already equal, so no operations are needed.

Constraints:
n == nums.length == cost.length
1 <= n <= 10^5
1 <= nums[i], cost[i] <= 10^6
```

<details><summary>Hint</summary>

```text
1. Changing the elements into one of the numbers already existing in the array nums is optimal.
2. Try finding the cost of changing the array into each element, and return the minimum value.
```

</details>

</details>

<details><summary>C</summary>

```c
long long getCost(int base, int* nums, int numsSize, int* cost, int costSize) {
    long long retVal = 0;

    int i;
    for (i = 0; i < numsSize; ++i) {
        retVal += ((long long)(abs(base - nums[i])) * cost[i]);
    }

    return retVal;
}
long long minCost(int* nums, int numsSize, int* cost, int costSize) {
    long long retVal = 0;

    retVal = getCost(nums[0], nums, numsSize, cost, costSize);
    int left = nums[0];
    int right = nums[0];
    int i;
    for (i = 0; i < numsSize; ++i) {
        left = (left < nums[i]) ? (left) : (nums[i]);
        right = (right > nums[i]) ? (right) : (nums[i]);
    }

    int middle;
    long long costLeft, costRight;
    while (left < right) {
        middle = (left + right) / 2;

        costLeft = getCost(middle, nums, numsSize, cost, costSize);
        costRight = getCost((middle + 1), nums, numsSize, cost, costSize);
        retVal = fmin(costLeft, costRight);

        if (costLeft > costRight) {
            left = middle + 1;
        } else {
            right = middle;
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
    long long getCost(int base, vector<int>& nums, vector<int>& cost) {
        long long retVal = 0;

        int numsSize = nums.size();
        for (int i = 0; i < numsSize; ++i) {
            retVal += ((long long)(abs(base - nums[i])) * cost[i]);
        }

        return retVal;
    }
    long long minCost(vector<int>& nums, vector<int>& cost) {
        long long retVal = 0;

        retVal = getCost(nums[0], nums, cost);
        int left = *min_element(nums.begin(), nums.end());
        int right = *max_element(nums.begin(), nums.end());

        while (left < right) {
            int middle = (left + right) / 2;

            long long costLeft = getCost(middle, nums, cost);
            long long costRight = getCost((middle + 1), nums, cost);
            retVal = min(costLeft, costRight);

            if (costLeft > costRight) {
                left = middle + 1;
            } else {
                right = middle;
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
    def getCost(self, base: int, nums: List[int], cost: List[int]) -> int:
        retVal = 0

        retVal = sum(abs(base - num) * c for num, c in zip(nums, cost))

        return retVal

    def minCost(self, nums: List[int], cost: List[int]) -> int:
        retVal = 0

        retVal = self.getCost(nums[0], nums, cost)
        left = min(nums)
        right = max(nums)
        while left < right:
            middle = (left + right) // 2

            costLeft = self.getCost(middle, nums, cost)
            costRight = self.getCost((middle + 1), nums, cost)
            retVal = min(costLeft, costRight)

            if costLeft > costRight:
                left = middle + 1
            else:
                right = middle

        return retVal
```

</details>

## [2616. Minimize the Maximum Difference of Pairs](https://leetcode.com/problems/minimize-the-maximum-difference-of-pairs/)  2155

- [Official](https://leetcode.com/problems/minimize-the-maximum-difference-of-pairs/editorial/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array nums and an integer p.
Find p pairs of indices of nums such that the maximum difference amongst all the pairs is minimized.
Also, ensure no index appears more than once amongst the p pairs.

Note that for a pair of elements at the index i and j,
the difference of this pair is |nums[i] - nums[j]|, where |x| represents the absolute value of x.

Return the minimum maximum difference among all p pairs. We define the maximum of an empty set to be zero.

Example 1:
Input: nums = [10,1,2,7,1,3], p = 2
Output: 1
Explanation: The first pair is formed from the indices 1 and 4, and the second pair is formed from the indices 2 and 5.
The maximum difference is max(|nums[1] - nums[4]|, |nums[2] - nums[5]|) = max(0, 1) = 1. Therefore, we return 1.

Example 2:
Input: nums = [4,2,1,2], p = 1
Output: 0
Explanation: Let the indices 1 and 3 form a pair.
The difference of that pair is |2 - 2| = 0, which is the minimum we can attain.

Constraints:
1 <= nums.length <= 10^5
0 <= nums[i] <= 10^9
0 <= p <= (nums.length)/2
```

<details><summary>Hint</summary>

```text
1. Can we use dynamic programming here?
2. To minimize the answer, the array should be sorted first.
3. The recurrence relation is fn(i, x) = min(fn(i+1, x), max(abs(nums[i]-nums[i+1]), fn(i+2, p-1)),
   and fn(0,p) gives the desired answer.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int countValidPairs(int* nums, int numsSize, int threshold) {
    int retVal = 0;

    int index = 0;
    while (index < numsSize - 1) {
        // If a valid pair is found, skip both numbers.
        if (nums[index + 1] - nums[index] <= threshold) {
            retVal += 1;
            index += 1;
        }
        index += 1;
    }

    return retVal;
}
int minimizeMax(int* nums, int numsSize, int p) {
    int retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int middle;
    int left = 0;
    int right = nums[numsSize - 1] - nums[0];
    while (left < right) {
        middle = left + (right - left) / 2;
        // If there are enough pairs, look for a smaller threshold.Otherwise, look for a larger threshold.
        if (countValidPairs(nums, numsSize, middle) >= p) {
            right = middle;
        } else {
            left = middle + 1;
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
    int countValidPairs(vector<int>& nums, int threshold) {
        int retVal = 0;

        int index = 0;
        int numsSize = nums.size();
        while (index < numsSize - 1) {
            // If a valid pair is found, skip both numbers.
            if (nums[index + 1] - nums[index] <= threshold) {
                retVal += 1;
                index += 1;
            }
            index += 1;
        }

        return retVal;
    }
    int minimizeMax(vector<int>& nums, int p) {
        int retVal = 0;

        sort(nums.begin(), nums.end());

        int numsSize = nums.size();
        int left = 0;
        int right = nums[numsSize - 1] - nums[0];
        while (left < right) {
            int middle = left + (right - left) / 2;
            // If there are enough pairs, look for a smaller threshold.Otherwise, look for a larger threshold.
            if (countValidPairs(nums, middle) >= p) {
                right = middle;
            } else {
                left = middle + 1;
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
    def countValidPairs(self, nums: List[int], threshold) -> int:
        retVal = 0

        index = 0
        numsSize = len(nums)
        while index < numsSize - 1:
            # If a valid pair is found, skip both numbers.
            if nums[index + 1] - nums[index] <= threshold:
                retVal += 1
                index += 1
            index += 1

        return retVal

    def minimizeMax(self, nums: List[int], p: int) -> int:
        retVal = 0

        nums.sort()

        left = 0
        right = nums[-1] - nums[0]
        while left < right:
            middle = left + (right - left) // 2
            # If there are enough pairs, look for a smaller threshold. Otherwise, look for a larger threshold.
            if self.countValidPairs(nums, middle) >= p:
                right = middle
            else:
                left = middle + 1
        retVal = left

        return retVal
```

</details>

## [2940. Find Building Where Alice and Bob Can Meet](https://leetcode.com/problems/find-building-where-alice-and-bob-can-meet/)  2327

- [Official](https://leetcode.com/problems/find-building-where-alice-and-bob-can-meet/editorial/)
- [Official](https://leetcode.cn/problems/find-building-where-alice-and-bob-can-meet/solutions/2872957/zhao-dao-alice-he-bob-ke-yi-xiang-yu-de-x5i0t/)

<details><summary>Description</summary>

```text
You are given a 0-indexed array heights of positive integers,
where heights[i] represents the height of the ith building.

If a person is in building i, they can move to any other building j if and only if i < j and heights[i] < heights[j].

You are also given another array queries where queries[i] = [ai, bi].
On the ith query, Alice is in building ai while Bob is in building bi.

Return an array ans where ans[i] is the index of the leftmost building where Alice and Bob can meet on the ith query.
If Alice and Bob cannot move to a common building on query i, set ans[i] to -1.

Example 1:
Input: heights = [6,4,8,5,2,7], queries = [[0,1],[0,3],[2,4],[3,4],[2,2]]
Output: [2,5,-1,5,2]
Explanation:
In the first query, Alice and Bob can move to building 2 since heights[0] < heights[2] and heights[1] < heights[2].
In the second query, Alice and Bob can move to building 5 since heights[0] < heights[5] and heights[3] < heights[5].
In the third query, Alice cannot meet Bob since Alice cannot move to any other building.
In the fourth query, Alice and Bob can move to building 5 since heights[3] < heights[5] and heights[4] < heights[5].
In the fifth query, Alice and Bob are already in the same building.
For ans[i] != -1, It can be shown that ans[i] is the leftmost building where Alice and Bob can meet.
For ans[i] == -1, It can be shown that there is no building where Alice and Bob can meet.

Example 2:
Input: heights = [5,3,8,2,6,1,4,6], queries = [[0,7],[3,5],[5,2],[3,0],[1,6]]
Output: [7,6,-1,4,6]
Explanation:
In the first query, Alice can directly move to Bob's building since heights[0] < heights[7].
In the second query, Alice and Bob can move to building 6 since heights[3] < heights[6] and heights[5] < heights[6].
In the third query, Alice cannot meet Bob since Bob cannot move to any other building.
In the fourth query, Alice and Bob can move to building 4 since heights[3] < heights[4] and heights[0] < heights[4].
In the fifth query, Alice can directly move to Bob's building since heights[1] < heights[6].
For ans[i] != -1, It can be shown that ans[i] is the leftmost building where Alice and Bob can meet.
For ans[i] == -1, It can be shown that there is no building where Alice and Bob can meet.

Constraints:
1 <= heights.length <= 5 * 10^4
1 <= heights[i] <= 10^9
1 <= queries.length <= 5 * 10^4
queries[i] = [ai, bi]
0 <= ai, bi <= heights.length - 1
```

<details><summary>Hint</summary>

```text
1. For each query [x, y], if x > y, swap x and y. Now, we can assume that x <= y.
2. For each query [x, y], if x == y or heights[x] < heights[y], then the answer is y since x ≤ y.
3. Otherwise, we need to find the smallest index t such that y < t and heights[x] < heights[t].
   Note that heights[y] <= heights[x], so heights[x] < heights[t] is a sufficient condition.
4. To find index t for each query, sort the queries in descending order of y.
   Iterate over the queries while maintaining a monotonic stack which we can binary search over to find index t.
```

</details>

</details>

<details><summary>C</summary>

```c
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* leftmostBuildingQueries(int* heights, int heightsSize, int** queries, int queriesSize, int* queriesColSize,
                             int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    //
    pRetVal = (int*)malloc(queriesSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (queriesSize * sizeof(int)));
    (*returnSize) = queriesSize;

    //
    int querySize[heightsSize];
    memset(querySize, 0, sizeof(querySize));
    for (int i = 0; i < queriesSize; i++) {
        int a = queries[i][0];
        int b = queries[i][1];
        if (a > b) {
            swap(&a, &b);
        }

        if ((a == b) || (heights[a] < heights[b])) {
            pRetVal[i] = b;
            continue;
        }

        querySize[b]++;
    }

    //
    struct Pair {
        int first;
        int second;
    };
    struct Pair* newQueries[heightsSize];
    for (int i = 0; i < heightsSize; i++) {
        newQueries[i] = (struct Pair*)malloc(querySize[i] * sizeof(struct Pair));
    }
    int newQueriesIdx[heightsSize];
    memset(newQueriesIdx, 0, sizeof(newQueriesIdx));
    for (int i = 0; i < queriesSize; i++) {
        int a = queries[i][0];
        int b = queries[i][1];
        if (a > b) {
            swap(&a, &b);
        }

        if (!((a == b) || (heights[a] < heights[b]))) {
            newQueries[b][newQueriesIdx[b]].first = i;
            newQueries[b][newQueriesIdx[b]].second = heights[a];
            newQueriesIdx[b]++;
        }
    }

    //
    int monoStackTop = -1;
    int* monoStack = (int*)malloc(heightsSize * sizeof(int));
    for (int i = heightsSize - 1; i >= 0; i--) {
        for (int j = 0; j < querySize[i]; j++) {
            int q = newQueries[i][j].first;
            int val = newQueries[i][j].second;
            if ((monoStackTop == -1) || (heights[monoStack[0]] <= val)) {
                pRetVal[q] = -1;
                continue;
            }

            int left = 0;
            int right = monoStackTop;
            while (left <= right) {
                int middle = (left + right) / 2;
                if (heights[monoStack[middle]] > val) {
                    left = middle + 1;
                } else {
                    right = middle - 1;
                }
            }
            pRetVal[q] = monoStack[right];
        }

        while ((monoStackTop >= 0) && (heights[monoStack[monoStackTop]] <= heights[i])) {
            monoStackTop--;
        }

        monoStack[++monoStackTop] = i;
    }

    //
    free(monoStack);
    for (int i = 0; i < heightsSize; i++) {
        free(newQueries[i]);
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    int search(int height, vector<pair<int, int>>& monoStack) {
        int retVal = -1;

        int left = 0;
        int right = monoStack.size() - 1;
        while (left <= right) {
            int middle = (left + right) / 2;
            if (monoStack[middle].first > height) {
                retVal = max(retVal, middle);
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }

        return retVal;
    }

   public:
    vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries) {
        vector<int> retVal;

        int queriesSize = queries.size();
        retVal.assign(queriesSize, -1);

        int heightsSize = heights.size();
        vector<vector<pair<int, int>>> newQueries(heightsSize);

        for (int i = 0; i < queriesSize; i++) {
            int a = queries[i][0];
            int b = queries[i][1];
            if (a > b) {
                swap(a, b);
            }

            if ((heights[b] > heights[a]) || (a == b)) {
                retVal[i] = b;
            } else {
                newQueries[b].push_back({heights[a], i});
            }
        }

        vector<pair<int, int>> monoStack;
        for (int i = heightsSize - 1; i >= 0; i--) {
            int monoStackSize = monoStack.size();
            for (auto& [a, b] : newQueries[i]) {
                int position = search(a, monoStack);
                if ((position < monoStackSize) && (position >= 0)) {
                    retVal[b] = monoStack[position].second;
                }
            }

            while ((monoStack.empty() == false) && (monoStack.back().first <= heights[i])) {
                monoStack.pop_back();
            }
            monoStack.push_back({heights[i], i});
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def search(self, height, monoStack):
        retVal = -1

        left = 0
        right = len(monoStack) - 1
        while left <= right:
            middle = (left + right) // 2
            if monoStack[middle][0] > height:
                retVal = max(retVal, middle)
                left = middle + 1
            else:
                right = middle - 1

        return retVal

    def leftmostBuildingQueries(self, heights: List[int], queries: List[List[int]]) -> List[int]:
        retVal = []

        queriesSize = len(queries)
        retVal = [-1 for _ in range(queriesSize)]

        heightsSize = len(heights)
        newQueries = [[] for _ in range(heightsSize)]

        for i in range(queriesSize):
            a = queries[i][0]
            b = queries[i][1]
            if a > b:
                a, b = b, a

            if (heights[b] > heights[a]) or (a == b):
                retVal[i] = b
            else:
                newQueries[b].append((heights[a], i))

        monoStack = []
        for i in range(heightsSize - 1, -1, -1):
            monoStackSize = len(monoStack)
            for a, b in newQueries[i]:
                position = self.search(a, monoStack)
                if (position < monoStackSize) and (position >= 0):
                    retVal[b] = monoStack[position][1]

            while monoStack and (monoStack[-1][0] <= heights[i]):
                monoStack.pop()
            monoStack.append((heights[i], i))

        return retVal
```

</details>

## [3356. Zero Array Transformation II](https://leetcode.com/problems/zero-array-transformation-ii/)  1913

- [Official](https://leetcode.com/problems/zero-array-transformation-ii/editorial/)

<details><summary>Description</summary>

```text
You are given an integer array nums of length n and a 2D array queries where queries[i] = [li, ri, vali].

Each queries[i] represents the following action on nums:
- Decrement the value at each index in the range [li, ri] in nums by at most vali.
- The amount by which each value is decremented can be chosen independently for each index.

A Zero Array is an array with all its elements equal to 0.

Return the minimum possible non-negative value of k, such that after processing the first k queries in sequence,
nums becomes a Zero Array. If no such k exists, return -1.

Example 1:
Input: nums = [2,0,2], queries = [[0,2,1],[0,2,1],[1,1,3]]
Output: 2
Explanation:
For i = 0 (l = 0, r = 2, val = 1):
Decrement values at indices [0, 1, 2] by [1, 0, 1] respectively.
The array will become [1, 0, 1].
For i = 1 (l = 0, r = 2, val = 1):
Decrement values at indices [0, 1, 2] by [1, 0, 1] respectively.
The array will become [0, 0, 0], which is a Zero Array. Therefore, the minimum value of k is 2.

Example 2:
Input: nums = [4,3,2,1], queries = [[1,3,2],[0,2,1]]
Output: -1
Explanation:
For i = 0 (l = 1, r = 3, val = 2):
Decrement values at indices [1, 2, 3] by [2, 2, 1] respectively.
The array will become [4, 1, 0, 0].
For i = 1 (l = 0, r = 2, val = 1):
Decrement values at indices [0, 1, 2] by [1, 1, 0] respectively.
The array will become [3, 0, 0, 0], which is not a Zero Array.

Constraints:
1 <= nums.length <= 10^5
0 <= nums[i] <= 5 * 10^5
1 <= queries.length <= 10^5
queries[i].length == 3
0 <= li <= ri < nums.length
1 <= vali <= 5
```

<details><summary>Hint</summary>

```text
1. Can we apply binary search here?
2. Utilize a difference array to optimize the processing of queries.
```

</details>

</details>

<details><summary>C</summary>

```c
int minZeroArray(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize) {
    int retVal = 0;

    int sum = 0;
    int differenceArray[numsSize + 1];
    memset(differenceArray, 0, sizeof(differenceArray));
    int differenceArrayIdx;
    int left, right, val;
    for (int index = 0; index < numsSize; index++) {
        // Iterate through queries while current index of nums cannot equal zero
        while (sum + differenceArray[index] < nums[index]) {
            retVal++;
            // Zero array isn't formed after all queries are processed
            if (retVal > queriesSize) {
                retVal = -1;
                return retVal;
            }

            // Process start and end of range
            left = queries[retVal - 1][0];
            right = queries[retVal - 1][1];
            val = queries[retVal - 1][2];
            if (right >= index) {
                differenceArrayIdx = fmax(left, index);
                differenceArray[differenceArrayIdx] += val;
                differenceArray[right + 1] -= val;
            }
        }

        sum += differenceArray[index];  // Update prefix sum at current index
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int retVal = 0;

        int numsSize = nums.size();
        int queriesSize = queries.size();

        int sum = 0;
        vector<int> differenceArray(numsSize + 1);
        for (int index = 0; index < numsSize; index++) {
            // Iterate through queries while current index of nums cannot equal zero
            while (sum + differenceArray[index] < nums[index]) {
                retVal++;
                // Zero array isn't formed after all queries are processed
                if (retVal > queriesSize) {
                    retVal = -1;
                    return retVal;
                }

                // Process start and end of range
                int left = queries[retVal - 1][0];
                int right = queries[retVal - 1][1];
                int val = queries[retVal - 1][2];
                if (right >= index) {
                    differenceArray[max(left, index)] += val;
                    differenceArray[right + 1] -= val;
                }
            }

            sum += differenceArray[index];  // Update prefix sum at current index
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minZeroArray(self, nums: List[int], queries: List[List[int]]) -> int:
        retVal = 0

        numsSize = len(nums)
        queriesSize = len(queries)

        sum = 0
        differenceArray = [0] * (numsSize + 1)
        for index in range(numsSize):
            # Iterate through queries while current index of nums cannot equal zero
            while sum + differenceArray[index] < nums[index]:
                retVal += 1
                # Zero array isn't formed after all queries are processed
                if retVal > queriesSize:
                    retVal = -1
                    return retVal

                # Process start and end of range
                left, right, val = queries[retVal - 1]
                if right >= index:
                    differenceArray[max(left, index)] += val
                    differenceArray[right + 1] -= val

            # Update prefix sum at current index
            sum += differenceArray[index]

        return retVal
```

</details>
