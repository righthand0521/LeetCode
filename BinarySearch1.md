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

## [315. Count of Smaller Numbers After Self](https://leetcode.com/problems/count-of-smaller-numbers-after-self/)

- [Official](https://leetcode.cn/problems/count-of-smaller-numbers-after-self/solutions/324892/ji-suan-you-ce-xiao-yu-dang-qian-yuan-su-de-ge-s-7/)

<details><summary>Description</summary>

```text
Given an integer array nums,
return an integer array counts where counts[i] is the number of smaller elements to the right of nums[i].

Example 1:
Input: nums = [5,2,6,1]
Output: [2,1,1,0]
Explanation:
To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.

Example 2:
Input: nums = [-1]
Output: [0]

Example 3:
Input: nums = [-1,-1]
Output: [0,0]

Constraints:
1 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4
```

</details>

<details><summary>C</summary>

```c
void Update(int* c, int discretizationIndex, int pos) {
    while (pos < discretizationIndex) {
        c[pos] += 1;
        pos += (pos & (-pos));
    }
}
int Query(int* c, int pos) {
    int retVal = 0;

    while (pos > 0) {
        retVal += c[pos];
        pos -= (pos & (-pos));
    }

    return retVal;
}
int lowerBound(int* a, int discretizationIndex, int x) {
    int retVal = 0;

    int middle;
    int left = 0;
    int right = discretizationIndex;
    while (left < right) {
        middle = (left + right) >> 1;
        if (a[middle] < x) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    retVal = left;

    return retVal;
}
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int Discretization(int* a, int* nums, int numsSize) {
    int retVal = 0;

    memcpy(a, nums, sizeof(int) * numsSize);
    qsort(a, numsSize, sizeof(int), compareInteger);

    for (int i = 1; i < numsSize; i++) {
        if (a[i] > a[retVal]) {
            a[++retVal] = a[i];
        }
    }
    retVal += 1;

    return retVal;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countSmaller(int* nums, int numsSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    int* a = (int*)calloc(numsSize, sizeof(int));
    if (a == NULL) {
        perror("calloc");
        return pRetVal;
    }
    int discretizationIndex = Discretization(a, nums, numsSize);

    int* c = (int*)calloc(numsSize + 1, sizeof(int));
    if (c == NULL) {
        perror("calloc");
        free(a);
        return pRetVal;
    }
    pRetVal = (int*)calloc(numsSize, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        free(a);
        free(c);
        return pRetVal;
    }
    for (int i = numsSize - 1; i >= 0; --i) {
        int id = lowerBound(a, discretizationIndex, nums[i]) + 1;
        pRetVal[i] = Query(c, id - 1);
        Update(c, discretizationIndex + 1, id);
    }
    (*returnSize) = numsSize;

    // Free allocated memory
    free(a);
    free(c);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    vector<int> c;
    vector<int> a;

    void Update(int pos) {
        int cSize = c.size();
        while (pos < cSize) {
            c[pos] += 1;
            pos += (pos & (-pos));
        }
    }
    int Query(int pos) {
        int retVal = 0;

        while (pos > 0) {
            retVal += c[pos];
            pos -= (pos & (-pos));
        }

        return retVal;
    }
    int getId(int x) {
        int retVal = lower_bound(a.begin(), a.end(), x) - a.begin() + 1;

        return retVal;
    }
    void Init(int length) {
        //
        c.resize(length, 0);
    }
    void Discretization(vector<int>& nums) {
        a.assign(nums.begin(), nums.end());
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
    }

   public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> retVal;

        int numsSize = nums.size();

        Discretization(nums);
        Init(numsSize + 5);
        for (int i = numsSize - 1; i >= 0; --i) {
            int id = getId(nums[i]);
            retVal.emplace_back(Query(id - 1));
            Update(id);
        }
        reverse(retVal.begin(), retVal.end());

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def __init__(self) -> None:
        self.a = None
        self.c = None

    def Discretization(self, nums: List[int]) -> None:
        self.a = nums.copy()
        self.a.sort()
        self.a = list(dict.fromkeys(self.a))

    def Update(self, pos: int) -> None:
        cSize = len(self.c)
        while pos < cSize:
            self.c[pos] += 1
            pos += (pos & (-pos))

    def Query(self, pos: int) -> int:
        retVal = 0

        while pos > 0:
            retVal += self.c[pos]
            pos -= (pos & (-pos))

        return retVal

    def getId(self, x: int) -> int:
        retVal = bisect_left(self.a, x) + 1

        return retVal

    def countSmaller(self, nums: List[int]) -> List[int]:
        retVal = None

        numSize = len(nums)

        self.a = [0] * numSize
        self.Discretization(nums)

        self.c = [0] * (numSize + 5)
        retVal = [0] * numSize
        for i in range(numSize - 1, -1, -1):
            id = self.getId(nums[i])
            retVal[i] = self.Query(id - 1)
            self.Update(id)

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

## [778. Swim in Rising Water](https://leetcode.com/problems/swim-in-rising-water/)  2097

- [Official](https://leetcode.cn/problems/swim-in-rising-water/solutions/582250/shui-wei-shang-sheng-de-yong-chi-zhong-y-862o/)

<details><summary>Description</summary>

```text
You are given an n x n integer matrix grid where each value grid[i][j] represents the elevation at that point (i, j).

It starts raining, and water gradually rises over time.
At time t, the water level is t, meaning any cell with elevation less than equal to t is submerged or reachable.

You can swim from a square to another 4-directionally adjacent square
if and only if the elevation of both squares individually are at most t.
You can swim infinite distances in zero time. Of course,
you must stay within the boundaries of the grid during your swim.

Return the minimum time until you can reach the bottom right square (n - 1, n - 1)
if you start at the top left square (0, 0).

Example 1:
Input: grid = [[0,2],[1,3]]
Output: 3
Explanation:
At time 0, you are in grid location (0, 0).
You cannot go anywhere else because 4-directionally adjacent neighbors have a higher elevation than t = 0.
You cannot reach point (1, 1) until time 3.
When the depth of water is 3, we can swim anywhere inside the grid.

Example 2:
Input: grid = [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
Output: 16
Explanation: The final route is shown.
We need to wait until time 16 so that (0, 0) and (4, 4) are connected.

Constraints:
n == grid.length
n == grid[i].length
1 <= n <= 50
0 <= grid[i][j] < n2
Each value grid[i][j] is unique.
```

<details><summary>Hint</summary>

```text
1. Use either Dijkstra's, or binary search for the best time T for
   which you can reach the end if you only step on squares at most T.
```

</details>

</details>

<details><summary>C</summary>

```c
bool bfs(int** grid, int gridSize, int* gridColSize, int threshold) {
    bool retVal = false;

    if (grid[0][0] > threshold) {
        return retVal;
    }

    bool visited[gridSize][gridSize];
    memset(visited, false, sizeof(visited));
    visited[0][0] = true;

    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int bfsQueue[gridSize * gridSize][2];
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    bfsQueue[bfsQueueTail][0] = 0;
    bfsQueue[bfsQueueTail][1] = 0;
    bfsQueueTail++;

    int x, y, nextX, nextY;
    while (bfsQueueHead < bfsQueueTail) {
        x = bfsQueue[bfsQueueHead][0];
        y = bfsQueue[bfsQueueHead][1];
        bfsQueueHead++;

        for (int i = 0; i < 4; i++) {
            nextX = x + directions[i][0];
            nextY = y + directions[i][1];
            if ((nextX < 0) || (nextX >= gridSize) || (nextY < 0) || (nextY >= gridSize)) {
                continue;
            } else if (visited[nextX][nextY]) {
                continue;
            } else if (grid[nextX][nextY] > threshold) {
                continue;
            }

            if ((nextX == gridSize - 1) && (nextY == gridSize - 1)) {
                retVal = true;
                return retVal;
            }
            visited[nextX][nextY] = true;
            bfsQueue[bfsQueueTail][0] = nextX;
            bfsQueue[bfsQueueTail][1] = nextY;
            bfsQueueTail++;
        }
    }

    return retVal;
}
int swimInWater(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int middle;
    int left = 0;
    int right = gridSize * gridSize - 1;
    while (left < right) {
        middle = (left + right) / 2;
        if ((grid[0][0] <= middle) && (bfs(grid, gridSize, gridColSize, middle) == true)) {
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
    bool bfs(vector<vector<int>>& grid, int threshold) {
        bool retVal = false;

        int gridSize = grid.size();
        if (grid[0][0] > threshold) {
            return retVal;
        }

        vector<vector<bool>> visited(gridSize, vector<bool>(gridSize, false));
        visited[0][0] = true;
        vector<vector<int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        queue<pair<int, int>> bfsQueue;
        bfsQueue.push({0, 0});
        while (bfsQueue.empty() == false) {
            auto [x, y] = bfsQueue.front();
            bfsQueue.pop();

            for (int i = 0; i < 4; i++) {
                int nextX = x + directions[i][0];
                int nextY = y + directions[i][1];
                if ((nextX < 0) || (nextX >= gridSize) || (nextY < 0) || (nextY >= gridSize)) {
                    continue;
                } else if (visited[nextX][nextY]) {
                    continue;
                } else if (grid[nextX][nextY] > threshold) {
                    continue;
                }

                if (nextX == gridSize - 1 && nextY == gridSize - 1) {
                    retVal = true;
                    return retVal;
                }
                visited[nextX][nextY] = true;
                bfsQueue.push({nextX, nextY});
            }
        }

        return retVal;
    }

   public:
    int swimInWater(vector<vector<int>>& grid) {
        int retVal = 0;

        int gridSize = grid.size();

        int left = 0;
        int right = gridSize * gridSize - 1;
        while (left < right) {
            int middle = (left + right) / 2;
            if ((grid[0][0] <= middle) && (bfs(grid, middle) == true)) {
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
    def bfs(self, grid, threshold) -> bool:
        retVal = False

        gridSize = len(grid)

        visited = [[False] * gridSize for _ in range(gridSize)]
        visited[0][0] = True
        bfsQueue = deque([(0, 0)])
        while bfsQueue:
            x, y = bfsQueue.popleft()
            for dx, dy in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                nextX = x + dx
                nextY = y + dy
                if (nextX < 0) or (nextX >= gridSize) or (nextY < 0) or (nextY >= gridSize):
                    continue
                elif visited[nextX][nextY] == True:
                    continue
                elif grid[nextX][nextY] > threshold:
                    continue

                if (nextX == gridSize - 1) and (nextY == gridSize - 1):
                    retVal = True
                    return retVal
                bfsQueue.append((nextX, nextY))
                visited[nextX][nextY] = True

        return retVal

    def swimInWater(self, grid: List[List[int]]) -> int:
        retVal = 0

        gridSize = len(grid)

        left = 0
        right = gridSize * gridSize - 1
        while left < right:
            middle = (left + right) // 2
            if (grid[0][0] <= middle) and (self.bfs(grid, middle) == True):
                right = middle
            else:
                left = middle + 1
        retVal = left

        return retVal
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
