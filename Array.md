# Array

## [26. Remove Duplicates from Sorted Array](https://leetcode.com/problems/remove-duplicates-from-sorted-array/)

- [Official](https://leetcode.cn/problems/remove-duplicates-from-sorted-array/solutions/728105/shan-chu-pai-xu-shu-zu-zhong-de-zhong-fu-tudo/)

<details><summary>Description</summary>

```text
Given an integer array nums sorted in non-decreasing order,
remove the duplicates in-place such that each unique element appears only once.
The relative order of the elements should be kept the same.

Since it is impossible to change the length of the array in some languages,
you must instead have the result be placed in the first part of the array nums.
More formally, if there are k elements after removing the duplicates,
then the first k elements of nums should hold the final result.
It does not matter what you leave beyond the first k elements.

Return k after placing the final result in the first k slots of nums.

Do not allocate extra space for another array.
You must do this by modifying the input array in-place with O(1) extra memory.

Custom Judge:
The judge will test your solution with the following code:

int[] nums = [...]; // Input array
int[] expectedNums = [...]; // The expected answer with correct length

int k = removeDuplicates(nums); // Calls your implementation

assert k == expectedNums.length;
for (int i = 0; i < k; i++) {
    assert nums[i] == expectedNums[i];
}

If all assertions pass, then your solution will be accepted.

Example 1:
Input: nums = [1,1,2]
Output: 2, nums = [1,2,_]
Explanation: Your function should return k = 2, with the first two elements of nums being 1 and 2 respectively.
It does not matter what you leave beyond the returned k (hence they are underscores).

Example 2:
Input: nums = [0,0,1,1,1,2,2,3,3,4]
Output: 5, nums = [0,1,2,3,4,_,_,_,_,_]
Explanation: Your function should return k = 5, with the first five elements of nums being 0, 1, 2, 3, and 4 respectively.
It does not matter what you leave beyond the returned k (hence they are underscores).

Constraints:
1 <= nums.length <= 3 * 10^4
-100 <= nums[i] <= 100
nums is sorted in non-decreasing order.
```

<details><summary>Hint</summary>

```text
1. In this problem, the key point to focus on is the input array being sorted.
   As far as duplicate elements are concerned, what is their positioning in the array when the given array is sorted?
   Look at the image above for the answer.
   If we know the position of one of the elements, do we also know the positioning of all the duplicate elements?
2. We need to modify the array in-place and the size of
   the final array would potentially be smaller than the size of the input array.
   So, we ought to use a two-pointer approach here.
   One, that would keep track of the current element in the original array and another one for just the unique elements.
3. We need to modify the array in-place and the size of
   the final array would potentially be smaller than the size of the input array.
   So, we ought to use a two-pointer approach here.
   One, that would keep track of the current element in the original array and another one for just the unique elements.
```

</details>

</details>

<details><summary>C</summary>

```c
int removeDuplicates(int* nums, int numsSize) {
    int retVal = 0;

    if (numsSize == 0) {
        return retVal;
    }

    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[retVal] != nums[i]) {
            nums[++retVal] = nums[i];
        }
    }
    ++retVal;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int removeDuplicates(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        if (numsSize == 0) {
            return retVal;
        }

        for (int i = 1; i < numsSize; ++i) {
            if (nums[retVal] != nums[i]) {
                nums[++retVal] = nums[i];
            }
        }
        ++retVal;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def removeDuplicates(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)
        if numsSize == 0:
            return retVal

        for i in range(1, numsSize):
            if nums[retVal] != nums[i]:
                retVal += 1
                nums[retVal] = nums[i]
        retVal += 1

        return retVal
```

</details>

## [27. Remove Element](https://leetcode.com/problems/remove-element/)

- [Official](https://leetcode.cn/problems/remove-element/solutions/730203/yi-chu-yuan-su-by-leetcode-solution-svxi/)

<details><summary>Description</summary>

```text
Given an integer array nums and an integer val, remove all occurrences of val in nums in-place.
The relative order of the elements may be changed.

Since it is impossible to change the length of the array in some languages,
you must instead have the result be placed in the first part of the array nums.
More formally, if there are k elements after removing the duplicates,
then the first k elements of nums should hold the final result.
It does not matter what you leave beyond the first k elements.

Return k after placing the final result in the first k slots of nums.

Do not allocate extra space for another array.
You must do this by modifying the input array in-place with O(1) extra memory.

Custom Judge:
The judge will test your solution with the following code:

int[] nums = [...]; // Input array
int val = ...; // Value to remove
int[] expectedNums = [...]; // The expected answer with correct length.
                            // It is sorted with no values equaling val.

int k = removeElement(nums, val); // Calls your implementation

assert k == expectedNums.length;
sort(nums, 0, k); // Sort the first k elements of nums
for (int i = 0; i < actualLength; i++) {
    assert nums[i] == expectedNums[i];
}

If all assertions pass, then your solution will be accepted.

Example 1:
Input: nums = [3,2,2,3], val = 3
Output: 2, nums = [2,2,_,_]
Explanation: Your function should return k = 2, with the first two elements of nums being 2.
It does not matter what you leave beyond the returned k (hence they are underscores).

Example 2:
Input: nums = [0,1,2,2,3,0,4,2], val = 2
Output: 5, nums = [0,1,4,0,3,_,_,_]
Explanation: Your function should return k = 5, with the first five elements of nums containing 0, 0, 1, 3, and 4.
Note that the five elements can be returned in any order.
It does not matter what you leave beyond the returned k (hence they are underscores).

Constraints:
0 <= nums.length <= 100
0 <= nums[i] <= 50
0 <= val <= 100
```

<details><summary>Hint</summary>

```text
1. The problem statement clearly asks us to modify the array in-place and
   it also says that the element beyond the new length of the array can be anything.
   Given an element, we need to remove all the occurrences of it from the array.
   We don't technically need to remove that element per-say, right?
2. We can move all the occurrences of this element to the end of the array. Use two pointers!
3. Yet another direction of thought is to consider the elements to be removed as non-existent.
   In a single pass, if we keep copying the visible elements in-place, that should also solve this problem for us.
```

</details>

</details>

<details><summary>C</summary>

```c
int removeElement(int* nums, int numsSize, int val) {
    int retVal = 0;

    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] != val) {
            nums[retVal++] = nums[i];
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
    int removeElement(vector<int>& nums, int val) {
        int retVal = 0;

        int numsSize = nums.size();
        for (int i = 0; i < numsSize; ++i) {
            if (nums[i] != val) {
                nums[retVal++] = nums[i];
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
    def removeElement(self, nums: List[int], val: int) -> int:
        retVal = 0

        numsSize = len(nums)
        for i in range(numsSize):
            if nums[i] != val:
                nums[retVal] = nums[i]
                retVal += 1

        return retVal
```

</details>

## [48. Rotate Image](https://leetcode.com/problems/rotate-image/)

- [Official](https://leetcode.cn/problems/rotate-image/solutions/526980/xuan-zhuan-tu-xiang-by-leetcode-solution-vu3m/)

<details><summary>Description</summary>

```text
You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).

You have to rotate the image in-place, which means you have to modify the input 2D matrix directly.
DO NOT allocate another 2D matrix and do the rotation.

Example 1:
Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[7,4,1],[8,5,2],[9,6,3]]

Example 2:
Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]

Constraints:
n == matrix.length == matrix[i].length
1 <= n <= 20
-1000 <= matrix[i][j] <= 1000
```

</details>

<details><summary>C</summary>

```c
void swap(int* pNum1, int* pNum2) {
    int temp = *pNum1;
    *pNum1 = *pNum2;
    *pNum2 = temp;
}
void rotate(int** matrix, int matrixSize, int* matrixColSize) {
    int matrixRow = matrixSize;
    int matrixCol = matrixColSize[0];
    int i, j;

    for (i = 0; i < matrixRow; ++i) {
        for (j = 0; j < (matrixCol / 2); ++j) {
            swap(&matrix[i][j], &matrix[i][matrixCol - j - 1]);
        }
    }

    for (i = 0; i < matrixRow; ++i) {
        for (j = 0; j < matrixCol - i; ++j) {
            swap(&matrix[i][j], &matrix[matrixCol - 1 - j][matrixCol - 1 - i]);
        }
    }
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    void rotate(vector<vector<int>>& matrix) {
        int matrixSize = matrix.size();

        for (int i = 0; i < matrixSize; ++i) {
            int matrixColSize = matrix[i].size();
            for (int j = 0; j < (matrixColSize / 2); ++j) {
                swap(matrix[i][j], matrix[i][matrixColSize - j - 1]);
            }
        }

        for (int i = 0; i < matrixSize; ++i) {
            int matrixColSize = matrix[i].size();
            for (int j = 0; j < matrixColSize - i; ++j) {
                swap(matrix[i][j], matrix[matrixColSize - 1 - j][matrixSize - 1 - i]);
            }
        }
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def rotate(self, matrix: List[List[int]]) -> None:
        """
        Do not return anything, modify matrix in-place instead.
        """

        matrixSize = len(matrix)

        for i in range(matrixSize):
            matrixColSize = len(matrix[i])
            for j in range(matrixColSize//2):
                matrix[i][j], matrix[i][matrixColSize-j-1] = \
                    matrix[i][matrixColSize-j-1], matrix[i][j]

        for i in range(matrixSize):
            matrixColSize = len(matrix[i])
            for j in range(matrixColSize-i):
                matrix[i][j], matrix[matrixColSize-1-j][matrixSize-1-i] = \
                    matrix[matrixColSize-1-j][matrixSize-1-i], matrix[i][j]
```

</details>

## [54. Spiral Matrix](https://leetcode.com/problems/spiral-matrix/)

- [Official](https://leetcode.cn/problems/spiral-matrix/solutions/275393/luo-xuan-ju-zhen-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given an m x n matrix, return all elements of the matrix in spiral order.

Example 1:
Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,3,6,9,8,7,4,5]

Example 2:
Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]

Constraints:
m == matrix.length
n == matrix[i].length
1 <= m, n <= 10
-100 <= matrix[i][j] <= 100
```

<details><summary>Hint</summary>

```text
1. Well for some problems, the best way really is to come up with some algorithms for simulation.
   Basically, you need to simulate what the problem asks us to do.
2. We go boundary by boundary and move inwards. That is the essential operation.
   First row, last column, last row, first column, and then we move inwards by 1 and repeat.
   That's all. That is all the simulation that we need.
3. Think about when you want to switch the progress on one of the indexes.
   If you progress on i out of [i, j], you'll shift in the same column.
   Similarly, by changing values for j, you'd be shifting in the same row.
   Also, keep track of the end of a boundary so that you can move inwards and then keep repeating.
   It's always best to simulate edge cases like a single column or a single row to see if anything breaks or not.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {
    int* pRetVal = NULL;

    int maxReturnSize = matrixSize * matrixColSize[0];
    (*returnSize) = maxReturnSize;
    pRetVal = (int*)calloc((*returnSize), sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        (*returnSize) = 0;
        return pRetVal;
    }

    int i, j;
    (*returnSize) = 0;
    for (i = 0; i <= matrixSize / 2; ++i) {
        /* first row: x1, last column: x2, last row: x3, first column: x4.
         *
         *  (top,left)               (top,right)
         *      +------------------------+
         *      | 11 | 11 | 11 | 11 | 11 |
         *      | 14 | 21 | 21 | 21 | 12 |
         *      | 14 | 24 | 31 | 22 | 12 |
         *      | 14 | 23 | 23 | 22 | 12 |
         *      | 13 | 13 | 13 | 13 | 12 |
         *      +------------------------+
         * (down,left)              (down,right)
         */

        // first row
        for (j = i; j < matrixColSize[i] - i; ++j) {
            pRetVal[(*returnSize)++] = matrix[i][j];
            if (((*returnSize)) == maxReturnSize) {
                return pRetVal;
            }
        }
        if (i + 1 == matrixSize - i) {
            continue;
        }

        // last column
        for (j = i + 1; j < matrixSize - i; ++j) {
            pRetVal[(*returnSize)++] = matrix[j][matrixColSize[i] - 1 - i];
            if (((*returnSize)) == maxReturnSize) {
                return pRetVal;
            }
        }
        if (i + 1 == matrixColSize[i]) {
            continue;
        }

        // last row
        for (j = matrixColSize[i] - 1 - (i + 1); j >= i; --j) {
            pRetVal[(*returnSize)++] = matrix[matrixSize - 1 - i][j];
            if (((*returnSize)) == maxReturnSize) {
                return pRetVal;
            }
        }

        // first column
        for (j = matrixSize - 1 - (i + 1); j > i; --j) {
            pRetVal[(*returnSize)++] = matrix[j][i];
            if (((*returnSize)) == maxReturnSize) {
                return pRetVal;
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
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> retVal;

        int rowSize = matrix.size();
        int colSize = matrix[0].size();
        int maxReturnSize = rowSize * colSize;

        int returnSize = 0;
        int i, j;
        for (i = 0; i <= rowSize / 2; ++i) {
            /* first row: x1, last column: x2, last row: x3, first column: x4.
             *
             *  (top,left)               (top,right)
             *      +------------------------+
             *      | 11 | 11 | 11 | 11 | 11 |
             *      | 14 | 21 | 21 | 21 | 12 |
             *      | 14 | 24 | 31 | 22 | 12 |
             *      | 14 | 23 | 23 | 22 | 12 |
             *      | 13 | 13 | 13 | 13 | 12 |
             *      +------------------------+
             * (down,left)              (down,right)
             */

            // first row
            for (j = i; j < colSize - i; ++j) {
                retVal.push_back(matrix[i][j]);
                ++returnSize;
                if (returnSize == maxReturnSize) {
                    return retVal;
                }
            }
            if (i + 1 == rowSize - i) {
                continue;
            }

            // last column
            for (j = i + 1; j < rowSize - i; ++j) {
                retVal.push_back(matrix[j][colSize - 1 - i]);
                ++returnSize;
                if (returnSize == maxReturnSize) {
                    return retVal;
                }
            }
            if (i + 1 == colSize) {
                continue;
            }

            // last row
            for (j = colSize - 1 - (i + 1); j >= i; --j) {
                retVal.push_back(matrix[rowSize - 1 - i][j]);
                ++returnSize;
                if (returnSize == maxReturnSize) {
                    return retVal;
                }
            }

            // first column
            for (j = rowSize - 1 - (i + 1); j > i; --j) {
                retVal.push_back(matrix[j][i]);
                ++returnSize;
                if (returnSize == maxReturnSize) {
                    return retVal;
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
    def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
        retVal = []

        rowSize = len(matrix)
        colSize = len(matrix[0])
        maxReturnSize = rowSize * colSize

        returnSize = 0
        for row in range(rowSize // 2 + 1):
            # /* first row: x1, last column: x2, last row: x3, first column: x4.
            #  *
            #  *  (top,left)               (top,right)
            #  *      +------------------------+
            #  *      | 11 | 11 | 11 | 11 | 11 |
            #  *      | 14 | 21 | 21 | 21 | 12 |
            #  *      | 14 | 24 | 31 | 22 | 12 |
            #  *      | 14 | 23 | 23 | 22 | 12 |
            #  *      | 13 | 13 | 13 | 13 | 12 |
            #  *      +------------------------+
            #  * (down,left)              (down,right)
            #  */

            # first row
            for col in range(row, colSize - row):
                retVal.append(matrix[row][col])
                returnSize += 1
                if returnSize == maxReturnSize:
                    return retVal
            if row + 1 == rowSize - row:
                continue

            # last column
            for col in range((row + 1), (rowSize - row)):
                retVal.append(matrix[col][colSize - 1 - row])
                returnSize += 1
                if returnSize == maxReturnSize:
                    return retVal
            if row + 1 == colSize:
                continue

            # last row
            for col in range((colSize - 1 - (row + 1)), (row - 1), -1):
                retVal.append(matrix[rowSize - 1 - row][col])
                returnSize += 1
                if returnSize == maxReturnSize:
                    return retVal

            # first column
            for col in range((rowSize - 1 - (row + 1)), row, -1):
                retVal.append(matrix[col][row])
                returnSize += 1
                if returnSize == maxReturnSize:
                    return retVal

        return retVal
```

</details>

## [57. Insert Interval](https://leetcode.com/problems/insert-interval/)

- [Official](https://leetcode.cn/problems/insert-interval/solutions/472151/cha-ru-qu-jian-by-leetcode-solution/)

<details><summary>Description</summary>

```text
You are given an array of non-overlapping intervals intervals where intervals[i] = [starti, endi]
represent the start and the end of the ith interval and intervals is sorted in ascending order by starti.
You are also given an interval newInterval = [start, end] that represents the start and end of another interval.

Insert newInterval into intervals such that intervals is still sorted in ascending order by starti
and intervals still does not have any overlapping intervals (merge overlapping intervals if necessary).

Return intervals after the insertion.

Example 1:
Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]

Example 2:
Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].

Constraints:
0 <= intervals.length <= 10^4
intervals[i].length == 2
0 <= starti <= endi <= 10^5
intervals is sorted by starti in ascending order.
newInterval.length == 2
0 <= start <= end <= 10^5
```

</details>

<details><summary>C</summary>

```c
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** insert(int** intervals, int intervalsSize, int* intervalsColSize, int* newInterval, int newIntervalSize,
             int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    pRetVal = (int**)malloc((intervalsSize + 1) * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    (*returnColumnSizes) = (int*)malloc((intervalsSize + 1) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, ((*returnSize) * sizeof(int)));

    //
    int colSize = 2;
    int left = newInterval[0];
    int right = newInterval[1];
    int* pInterval;
    bool placed = false;
    int* tmp;
    int i;
    for (i = 0; i < intervalsSize; ++i) {
        pInterval = intervals[i];
        if (pInterval[0] > right) {
            if (placed == false) {
                tmp = (int*)malloc(colSize * sizeof(int));
                if (tmp == NULL) {
                    perror("malloc");
                    goto exit;
                }
                memset(tmp, 0, (colSize * sizeof(int)));
                tmp[0] = left;
                tmp[1] = right;
                (*returnColumnSizes)[(*returnSize)] = colSize;
                pRetVal[(*returnSize)++] = tmp;

                placed = true;
            }

            tmp = (int*)malloc(colSize * sizeof(int));
            if (tmp == NULL) {
                perror("malloc");
                goto exit;
            }
            memset(tmp, 0, (colSize * sizeof(int)));
            memcpy(tmp, pInterval, (colSize * sizeof(int)));
            (*returnColumnSizes)[*returnSize] = colSize;
            pRetVal[(*returnSize)++] = tmp;
        } else if (pInterval[1] < left) {
            tmp = (int*)malloc(colSize * sizeof(int));
            if (tmp == NULL) {
                perror("malloc");
                goto exit;
            }
            memset(tmp, 0, (colSize * sizeof(int)));
            memcpy(tmp, pInterval, (colSize * sizeof(int)));
            (*returnColumnSizes)[*returnSize] = colSize;
            pRetVal[(*returnSize)++] = tmp;
        } else {
            left = fmin(left, pInterval[0]);
            right = fmax(right, pInterval[1]);
        }
    }

    //
    if (placed == false) {
        tmp = (int*)malloc(colSize * sizeof(int));
        if (tmp == NULL) {
            perror("malloc");
            goto exit;
        }
        memset(tmp, 0, (colSize * sizeof(int)));
        tmp[0] = left;
        tmp[1] = right;
        (*returnColumnSizes)[*returnSize] = colSize;
        pRetVal[(*returnSize)++] = tmp;
    }

    return pRetVal;

exit:
    free((*returnColumnSizes));
    (*returnColumnSizes) = NULL;

    for (i = 0; i < (*returnSize); ++i) {
        free(pRetVal[i]);
        pRetVal[i] = NULL;
    }
    free(pRetVal);
    pRetVal = NULL;
    (*returnSize) = 0;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> retVal;

        int left = newInterval[0];
        int right = newInterval[1];
        bool placed = false;
        for (const auto& interval : intervals) {
            if (interval[0] > right) {
                if (placed == false) {
                    retVal.push_back({left, right});
                    placed = true;
                }

                retVal.push_back(interval);
            } else if (interval[1] < left) {
                retVal.push_back(interval);
            } else {
                left = min(left, interval[0]);
                right = max(right, interval[1]);
            }
        }

        if (placed == false) {
            retVal.push_back({left, right});
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def insert(self, intervals: List[List[int]], newInterval: List[int]) -> List[List[int]]:
        retVal = []

        left = newInterval[0]
        right = newInterval[1]
        place = False

        for interval in intervals:
            if interval[0] > right:
                if place == False:
                    retVal.append([left, right])
                    place = True
                retVal.append(interval)
            elif interval[1] < left:
                retVal.append(interval)
            else:
                left = min(left, interval[0])
                right = max(right, interval[1])

        if place == False:
            retVal.append([left, right])

        return retVal
```

</details>

## [59. Spiral Matrix II](https://leetcode.com/problems/spiral-matrix-ii/)

- [Official](https://leetcode.com/problems/spiral-matrix-ii/editorial/)
- [Official](https://leetcode.cn/problems/spiral-matrix-ii/solutions/658676/luo-xuan-ju-zhen-ii-by-leetcode-solution-f7fp/)

<details><summary>Description</summary>

```text
Given a positive integer n, generate an n x n matrix filled with elements from 1 to n2 in spiral order.

Example 1:
Input: n = 3
Output: [[1,2,3],[8,9,4],[7,6,5]]

Example 2:
Input: n = 1
Output: [[1]]

Constraints:
1 <= n <= 20
```

</details>

<details><summary>C</summary>

```c
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** generateMatrix(int n, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    //
    (*returnSize) = n;
    //
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, ((*returnSize) * sizeof(int)));
    //
    pRetVal = (int**)malloc((*returnSize) * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        (*returnSize) = 0;
        return pRetVal;
    }
    int i, j;
    for (i = 0; i < (*returnSize); ++i) {
        pRetVal[i] = (int*)malloc((*returnSize) * sizeof(int));
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
            (*returnSize) = 0;
            return pRetVal;
        }
        memset(pRetVal[i], 0, ((*returnSize) * sizeof(int)));
        (*returnColumnSizes)[i] = (*returnSize);
    }

    /*
     *  (top,left)                              (top,right)
     *      +---------------------------------------+
     *      | 01(111) | 02(112) | 03(113) | 04(114) |
     *      | 12(142) | 13(211) | 14(212) | 05(121) |
     *      | 11(141) | 16(231) | 15(221) | 06(122) |
     *      | 10(133) | 09(132) | 08(131) | 07(123) |
     *      +---------------------------------------+
     * (down,left)                             (down,right)
     */
    int left = 0;
    int right = n - 1;
    int top = 0;
    int down = n - 1;
    int num = 1;
    int row, col;
    while ((left <= right) && (top <= down)) {
        for (col = left; col < right + 1; ++col) {
            pRetVal[top][col] = num;
            ++num;
        }

        for (row = top + 1; row < down + 1; ++row) {
            pRetVal[row][right] = num;
            ++num;
        }

        if ((left < right) && (top < down)) {
            for (col = right - 1; col > left; --col) {
                pRetVal[down][col] = num;
                ++num;
            }

            for (row = down; row > top; --row) {
                pRetVal[row][left] = num;
                ++num;
            }
        }

        ++left;
        --right;
        ++top;
        --down;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> retVal(n, vector<int>(n));

        /*
         *  (top,left)                              (top,right)
         *      +---------------------------------------+
         *      | 01(111) | 02(112) | 03(113) | 04(114) |
         *      | 12(142) | 13(211) | 14(212) | 05(121) |
         *      | 11(141) | 16(231) | 15(221) | 06(122) |
         *      | 10(133) | 09(132) | 08(131) | 07(123) |
         *      +---------------------------------------+
         * (down,left)                             (down,right)
         */
        int left = 0;
        int right = n - 1;
        int top = 0;
        int down = n - 1;
        int num = 1;
        while ((left <= right) && (top <= down)) {
            for (int col = left; col < right + 1; ++col) {
                retVal[top][col] = num;
                ++num;
            }

            for (int row = top + 1; row < down + 1; ++row) {
                retVal[row][right] = num;
                ++num;
            }

            if ((left < right) && (top < down)) {
                for (int col = right - 1; col > left; --col) {
                    retVal[down][col] = num;
                    ++num;
                }

                for (int row = down; row > top; --row) {
                    retVal[row][left] = num;
                    ++num;
                }
            }

            ++left;
            --right;
            ++top;
            --down;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def generateMatrix(self, n: int) -> List[List[int]]:
        retVal = [[0] * n for _ in range(n)]

        # /*
        #  *  (top,left)                              (top,right)
        #  *      +---------------------------------------+
        #  *      | 01(111) | 02(112) | 03(113) | 04(114) |
        #  *      | 12(142) | 13(211) | 14(212) | 05(121) |
        #  *      | 11(141) | 16(231) | 15(221) | 06(122) |
        #  *      | 10(133) | 09(132) | 08(131) | 07(123) |
        #  *      +---------------------------------------+
        #  * (down,left)                             (down,right)
        #  */
        left = 0
        right = n - 1
        top = 0
        down = n - 1
        num = 1
        while (left <= right) and (top <= down):
            for col in range(left, right + 1):
                retVal[top][col] = num
                num += 1

            for row in range(top + 1, down + 1):
                retVal[row][right] = num
                num += 1

            if (left < right) and (top < down):
                for col in range(right - 1, left, -1):
                    retVal[down][col] = num
                    num += 1

                for row in range(down, top, -1):
                    retVal[row][left] = num
                    num += 1

            left += 1
            right -= 1
            top += 1
            down -= 1

        return retVal
```

</details>

## [80. Remove Duplicates from Sorted Array II](https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/)

- [Official](https://leetcode.cn/problems/remove-duplicates-from-sorted-array-ii/solutions/702644/shan-chu-pai-xu-shu-zu-zhong-de-zhong-fu-yec2/)

<details><summary>Description</summary>

```text
Given an integer array nums sorted in non-decreasing order,
remove some duplicates in-place such that each unique element appears at most twice.
The relative order of the elements should be kept the same.

Since it is impossible to change the length of the array in some languages,
you must instead have the result be placed in the first part of the array nums.
More formally, if there are k elements after removing the duplicates,
then the first k elements of nums should hold the final result.
It does not matter what you leave beyond the first k elements.

Return k after placing the final result in the first k slots of nums.

Do not allocate extra space for another array.
You must do this by modifying the input array in-place with O(1) extra memory.

Custom Judge:
The judge will test your solution with the following code:

int[] nums = [...]; // Input array
int[] expectedNums = [...]; // The expected answer with correct length

int k = removeDuplicates(nums); // Calls your implementation

assert k == expectedNums.length;
for (int i = 0; i < k; i++) {
    assert nums[i] == expectedNums[i];
}

If all assertions pass, then your solution will be accepted.

Example 1:
Input: nums = [1,1,1,2,2,3]
Output: 5, nums = [1,1,2,2,3,_]
Explanation: Your function should return k = 5,
with the first five elements of nums being 1, 1, 2, 2 and 3 respectively.
It does not matter what you leave beyond the returned k (hence they are underscores).

Example 2:
Input: nums = [0,0,1,1,1,1,2,3,3]
Output: 7, nums = [0,0,1,1,2,3,3,_,_]
Explanation: Your function should return k = 7,
with the first seven elements of nums being 0, 0, 1, 1, 2, 3 and 3 respectively.
It does not matter what you leave beyond the returned k (hence they are underscores).

Constraints:
1 <= nums.length <= 3 * 10^4
-10^4 <= nums[i] <= 10^4
nums is sorted in non-decreasing order.
```

</details>

<details><summary>C</summary>

```c
int removeDuplicates(int* nums, int numsSize) {
    int retVal = 0;

    if (numsSize < 2) {
        retVal = numsSize;
        return retVal;
    }

    int count = 0;
    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[retVal] != nums[i]) {
            count = 0;
        } else {
            count++;
        }

        if (count < 2) {
            retVal++;
            nums[retVal] = nums[i];
        }
    }
    retVal += 1;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int removeDuplicates(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        if (numsSize < 2) {
            retVal = numsSize;
            return retVal;
        }

        int count = 0;
        for (int i = 1; i < numsSize; ++i) {
            if (nums[retVal] != nums[i]) {
                count = 0;
            } else {
                ++count;
            }

            if (count < 2) {
                retVal++;
                nums[retVal] = nums[i];
            }
        }
        retVal += 1;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def removeDuplicates(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)
        if numsSize < 2:
            retVal = numsSize
            return retVal

        count = 0
        for i in range(1, numsSize):
            if nums[retVal] != nums[i]:
                count = 0
            else:
                count += 1

            if count < 2:
                retVal += 1
                nums[retVal] = nums[i]
        retVal += 1

        return retVal
```

</details>

## [135. Candy](https://leetcode.com/problems/candy/)

- [Official](https://leetcode.cn/problems/candy/solutions/533150/fen-fa-tang-guo-by-leetcode-solution-f01p/)

<details><summary>Description</summary>

```text
There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.

You are giving candies to these children subjected to the following requirements:
- Each child must have at least one candy.
- Children with a higher rating get more candies than their neighbors.

Return the minimum number of candies you need to have to distribute the candies to the children.

Example 1:
Input: ratings = [1,0,2]
Output: 5
Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.

Example 2:
Input: ratings = [1,2,2]
Output: 4
Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
The third child gets 1 candy because it satisfies the above two conditions.

Constraints:
n == ratings.length
1 <= n <= 2 * 10^4
0 <= ratings[i] <= 2 * 10^4
```

</details>

<details><summary>C</summary>

```c
int candy(int* ratings, int ratingsSize) {
    int retVal = 0;

    int i;

    int left[ratingsSize];
    memset(left, 0, sizeof(left));
    for (i = 0; i < ratingsSize; i++) {
        if ((i > 0) && (ratings[i] > ratings[i - 1])) {
            left[i] = left[i - 1] + 1;
        } else {
            left[i] = 1;
        }
    }

    int right = 0;
    for (i = ratingsSize - 1; i >= 0; i--) {
        if ((i < ratingsSize - 1) && (ratings[i] > ratings[i + 1])) {
            right++;
        } else {
            right = 1;
        }
        retVal += fmax(left[i], right);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int candy(vector<int>& ratings) {
        int retVal = 0;

        int ratingsSize = ratings.size();

        vector<int> left(ratingsSize, 0);
        for (int i = 0; i < ratingsSize; i++) {
            if ((i > 0) && (ratings[i] > ratings[i - 1])) {
                left[i] = left[i - 1] + 1;
            } else {
                left[i] = 1;
            }
        }

        int right = 0;
        for (int i = ratingsSize - 1; i >= 0; i--) {
            if ((i < ratingsSize - 1) && (ratings[i] > ratings[i + 1])) {
                right++;
            } else {
                right = 1;
            }

            retVal += max(left[i], right);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def candy(self, ratings: List[int]) -> int:
        retVal = 0

        ratingsSize = len(ratings)

        left = [0] * ratingsSize
        for i in range(ratingsSize):
            if (i > 0) and (ratings[i] > ratings[i - 1]):
                left[i] = left[i - 1] + 1
            else:
                left[i] = 1

        right = 0
        for i in range(ratingsSize - 1, -1, -1):
            if (i < ratingsSize - 1) and (ratings[i] > ratings[i + 1]):
                right += 1
            else:
                right = 1

            retVal += max(left[i], right)

        return retVal
```

</details>

## [189. Rotate Array](https://leetcode.com/problems/rotate-array/)

- [Official](https://leetcode.cn/problems/rotate-array/solutions/551039/xuan-zhuan-shu-zu-by-leetcode-solution-nipk)

<details><summary>Description</summary>

```text
Given an array, rotate the array to the right by k steps, where k is non-negative.

Example 1:
Input: nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]

Example 2:
Input: nums = [-1,-100,3,99], k = 2
Output: [3,99,-1,-100]
Explanation:
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]

Constraints:
1 <= nums.length <= 10^5
-2^31 <= nums[i] <= 2^31 - 1
0 <= k <= 10^5

Follow up:
Try to come up with as many solutions as you can. There are at least three different ways to solve this problem.
Could you do it in-place with O(1) extra space?
```

<details><summary>Hint</summary>

```text
1. The easiest solution would use additional memory and that is perfectly fine.
2. The actual trick comes when trying to solve this problem without using any additional memory.
   This means you need to use the original array somehow to move the elements around.
   Now, we can place each element in its original location and shift all the elements around it
   to adjust as that would be too costly and most likely will time out on larger input arrays.
3. One line of thought is based on reversing the array (or parts of it) to obtain the desired result.
   Think about how reversal might potentially help us out by using an example.
4. The other line of thought is a tad bit complicated but essentially it builds on the idea of placing each element
   in its original position while keeping track of the element originally in that position.
   Basically, at every step, we place an element in its rightful position
   and keep track of the element already there or the one being overwritten in an additional variable.
   We can't do this in one linear pass and the idea here is based on cyclic-dependencies between elements.
```

</details>

</details>

<details><summary>C</summary>

```c
void reverse(int* nums, int start, int end) {
    int tmp;
    while (start < end) {
        tmp = nums[start];
        nums[start] = nums[end];
        nums[end] = tmp;

        ++start;
        --end;
    }
}
void rotate(int* nums, int numsSize, int k) {
    /* Example: Input: nums = [1,2,3,4,5,6,7], k = 3; Output: [5,6,7,1,2,3,4]
     *  +---------+-------+    +-------+---------+    +-------+---------+    +-------+---------+
     *  | 1 2 3 4 | 5 6 7 | => | 7 6 5 | 4 3 2 1 | => | 5 6 7 | 4 3 2 1 | => | 5 6 7 | 1 2 3 4 |
     *  +---------+-------+    +-------+---------+    +-------+---------+    +-------+---------+
     */
    k %= numsSize;
    reverse(nums, 0, numsSize - 1);
    reverse(nums, 0, k - 1);
    reverse(nums, k, numsSize - 1);
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    void rotate(vector<int>& nums, int k) {
        /* Example: Input: nums = [1,2,3,4,5,6,7], k = 3; Output: [5,6,7,1,2,3,4]
         *  +---------+-------+    +-------+---------+    +-------+---------+    +-------+---------+
         *  | 1 2 3 4 | 5 6 7 | => | 7 6 5 | 4 3 2 1 | => | 5 6 7 | 4 3 2 1 | => | 5 6 7 | 1 2 3 4 |
         *  +---------+-------+    +-------+---------+    +-------+---------+    +-------+---------+
         */
        int numsSize = nums.size();
        k %= numsSize;
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + k);
        reverse(nums.begin() + k, nums.end());
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def rotate(self, nums: List[int], k: int) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """

        # Example: Input: nums = [1,2,3,4,5,6,7], k = 3; Output: [5,6,7,1,2,3,4]
        #   +---------+-------+    +-------+---------+    +-------+---------+    +-------+---------+
        #   | 1 2 3 4 | 5 6 7 | => | 7 6 5 | 4 3 2 1 | => | 5 6 7 | 4 3 2 1 | => | 5 6 7 | 1 2 3 4 |
        #   +---------+-------+    +-------+---------+    +-------+---------+    +-------+---------+
        numsSize = len(nums)
        k %= numsSize
        nums[:] = nums[::-1]
        nums[:k] = nums[:k][::-1]
        nums[k:] = nums[k:][::-1]
```

</details>

## [228. Summary Ranges](https://leetcode.com/problems/summary-ranges/)

- [Official](https://leetcode.com/problems/summary-ranges/editorial/)
- [Official](https://leetcode.cn/problems/summary-ranges/solutions/553645/hui-zong-qu-jian-by-leetcode-solution-6zrs/)

<details><summary>Description</summary>

```text
You are given a sorted unique integer array nums.

A range [a,b] is the set of all integers from a to b (inclusive).

Return the smallest sorted list of ranges that cover all the numbers in the array exactly.
That is, each element of nums is covered by exactly one of the ranges, and there is no integer x
such that x is in one of the ranges but not in nums.

Each range [a,b] in the list should be output as:
- "a->b" if a != b
- "a" if a == b

Example 1:
Input: nums = [0,1,2,4,5,7]
Output: ["0->2","4->5","7"]
Explanation: The ranges are:
[0,2] --> "0->2"
[4,5] --> "4->5"
[7,7] --> "7"

Example 2:
Input: nums = [0,2,3,4,6,8,9]
Output: ["0","2->4","6","8->9"]
Explanation: The ranges are:
[0,0] --> "0"
[2,4] --> "2->4"
[6,6] --> "6"
[8,9] --> "8->9"

Constraints:
0 <= nums.length <= 20
-2^31 <= nums[i] <= 2^31 - 1
All the values of nums are unique.
nums is sorted in ascending order.
```

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** summaryRanges(int* nums, int numsSize, int* returnSize) {
    char** pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (char**)malloc(numsSize * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

#define MAX_RETURN_SIZE (32)  // -2^31 <= nums[i] <= 2^31 - 1
    char buf[MAX_RETURN_SIZE];
    int tmp;
    int idx = 0;
    while (idx < numsSize) {
        tmp = nums[idx];
        while ((idx + 1 < numsSize) && (nums[idx] + 1 == nums[idx + 1])) {
            ++idx;
        }

        memset(buf, 0, sizeof(buf));
        if (tmp == nums[idx]) {
            snprintf(buf, sizeof(buf), "%d", tmp);
        } else {
            snprintf(buf, sizeof(buf), "%d->%d", tmp, nums[idx]);
        }
        pRetVal[(*returnSize)] = (char*)malloc(MAX_RETURN_SIZE * sizeof(char));
        if (pRetVal[(*returnSize)] == NULL) {
            perror("malloc");
            return pRetVal;
        }
        memset(pRetVal[(*returnSize)], 0, (MAX_RETURN_SIZE * sizeof(char)));
        memcpy(pRetVal[(*returnSize)], buf, (MAX_RETURN_SIZE * sizeof(char)));
        (*returnSize)++;

        ++idx;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> retVal;

        int numsSize = nums.size();

        int idx = 0;
        while (idx < numsSize) {
            int tmp = nums[idx];
            while ((idx + 1 < numsSize) && (nums[idx] + 1 == nums[idx + 1])) {
                ++idx;
            }

            if (tmp == nums[idx]) {
                retVal.emplace_back(to_string(tmp));
            } else {
                retVal.emplace_back(to_string(tmp) + "->" + to_string(nums[idx]));
            }

            ++idx;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def summaryRanges(self, nums: List[int]) -> List[str]:
        retVal = []

        numsSize = len(nums)

        idx = 0
        while idx < numsSize:
            tmp = nums[idx]
            while (idx+1 < numsSize) and (nums[idx]+1 == nums[idx+1]):
                idx += 1

            if tmp == nums[idx]:
                retVal.append(str(tmp))
            else:
                retVal.append(str(tmp)+"->"+str(nums[idx]))

            idx += 1

        return retVal
```

</details>

## [238. Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self)

- [Official](https://leetcode.cn/problems/product-of-array-except-self/solutions/272369/chu-zi-shen-yi-wai-shu-zu-de-cheng-ji-by-leetcode-/)

<details><summary>Description</summary>

```text
Given an integer array nums,
return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].

The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

You must write an algorithm that runs in O(n) time and without using the division operation.

Example 1:
Input: nums = [1,2,3,4]
Output: [24,12,8,6]

Example 2:
Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]

Constraints:
2 <= nums.length <= 10^5
-30 <= nums[i] <= 30
The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

Follow up: Can you solve the problem in O(1) extra space complexity?
(The output array does not count as extra space for space complexity analysis.)
```

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *productExceptSelf(int *nums, int numsSize, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int *)malloc(numsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (numsSize * sizeof(int)));
    pRetVal[0] = 1;

    /*
     *   1  2  3  4
     *  x1 24 12  4 => 1 x 24 = 24
     *   1 x1 12  4 => 1 x 12 = 12
     *   1  2 x1  4 => 2 x  4 =  8
     *   1  2  6 x1 => 6 x  1 =  6
     */
    int i;
    for (i = 1; i < numsSize; ++i) {
        pRetVal[i] = pRetVal[i - 1] * nums[i - 1];
    }
    int tmp = 1;
    for (i = numsSize - 2; i >= 0; --i) {
        tmp *= nums[i + 1];
        pRetVal[i] *= tmp;
    }
    (*returnSize) = numsSize;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> retVal;

        int numsSize = nums.size();
        for (int i = 0; i < numsSize; ++i) {
            retVal.emplace_back(1);
        }

        /*
         *   1  2  3  4
         *  x1 24 12  4 => 1 x 24 = 24
         *   1 x1 12  4 => 1 x 12 = 12
         *   1  2 x1  4 => 2 x  4 =  8
         *   1  2  6 x1 => 6 x  1 =  6
         */
        for (int i = 1; i < numsSize; ++i) {
            retVal[i] = retVal[i - 1] * nums[i - 1];
        }
        int tmp = 1;
        for (int i = numsSize - 2; i >= 0; --i) {
            tmp *= nums[i + 1];
            retVal[i] *= tmp;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def productExceptSelf(self, nums: List[int]) -> List[int]:
        retVal = []

        numsSize = len(nums)

        #  1  2  3  4
        # x1 24 12  4 => 1 x 24 = 24
        #  1 x1 12  4 => 1 x 12 = 12
        #  1  2 x1  4 => 2 x  4 =  8
        #  1  2  6 x1 => 6 x  1 =  6
        retVal = [1] * numsSize
        for i in range(1, numsSize):
            retVal[i] = retVal[i - 1] * nums[i - 1]
        tmp = 1
        for i in range(numsSize - 2, -1, -1):
            tmp *= nums[i + 1]
            retVal[i] *= tmp

        return retVal
```

</details>

## [274. H-Index](https://leetcode.com/problems/h-index/)

- [Official](https://leetcode.cn/problems/h-index/solutions/869042/h-zhi-shu-by-leetcode-solution-fnhl/)

<details><summary>Description</summary>

```text
Given an array of integers citations where citations[i] is the number of citations
a researcher received for their ith paper, return the researcher's h-index.

According to the definition of h-index on Wikipedia:
The h-index is defined as the maximum value of h
such that the given researcher has published at least h papers that have each been cited at least h times.

Example 1:
Input: citations = [3,0,6,1,5]
Output: 3
Explanation: [3,0,6,1,5] means the researcher has 5 papers in total
and each of them had received 3, 0, 6, 1, 5 citations respectively.
Since the researcher has 3 papers with at least 3 citations each
and the remaining two with no more than 3 citations each, their h-index is 3.

Example 2:
Input: citations = [1,3,1]
Output: 1

Constraints:
n == citations.length
1 <= n <= 5000
0 <= citations[i] <= 1000
```

<details><summary>Hint</summary>

```text
1. An easy approach is to sort the array first.
2. What are the possible values of h-index?
3. A faster approach is to use extra space.
```

</details>

</details>

<details><summary>C</summary>

```c
int hIndex(int* citations, int citationsSize) {
    int retVal = 0;

    int countMap[citationsSize + 1];
    memset(countMap, 0, sizeof(countMap));

    int cited = 0;
    int i;
    for (i = 0; i < citationsSize; ++i) {
        if (citations[i] > citationsSize) {
            cited++;
        } else {
            countMap[citations[i]]++;
        }
    }

    for (i = citationsSize; i >= 0; --i) {
        cited += countMap[i];
        if (cited >= i) {
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
    int hIndex(vector<int>& citations) {
        int retVal = 0;

        int citationsSize = citations.size();

        vector<int> countMap(citationsSize + 1, 0);
        int cited = 0;
        for (int citation : citations) {
            if (citation > citationsSize) {
                cited++;
            } else {
                countMap[citation]++;
            }
        }

        for (int i = citationsSize; i >= 0; --i) {
            cited += countMap[i];
            if (cited >= i) {
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
    def hIndex(self, citations: List[int]) -> int:
        retVal = 0

        citationsSize = len(citations)

        countMap = [0] * (citationsSize+1)
        cited = 0
        for citation in citations:
            if citation > citationsSize:
                cited += 1
            else:
                countMap[citation] += 1

        for i in range(citationsSize, -1, -1):
            cited += countMap[i]
            if cited >= i:
                retVal = i
                break

        return retVal
```

</details>

## [287. Find the Duplicate Number](https://leetcode.com/problems/find-the-duplicate-number/)

- [Official](https://leetcode.cn/problems/find-the-duplicate-number/solutions/261119/xun-zhao-zhong-fu-shu-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given an array of integers nums containing n + 1 integers where each integer is in the range [1, n] inclusive.

There is only one repeated number in nums, return this repeated number.

You must solve the problem without modifying the array nums and uses only constant extra space.

Example 1:
Input: nums = [1,3,4,2,2]
Output: 2

Example 2:
Input: nums = [3,1,3,4,2]
Output: 3

Constraints:
1 <= n <= 10^5
nums.length == n + 1
1 <= nums[i] <= n
All the integers in nums appear only once except for precisely one integer which appears two or more times.

Follow up:
How can we prove that at least one duplicate number must exist in nums?
Can you solve the problem in linear runtime complexity?
```

</details>

<details><summary>C</summary>

```c
int findDuplicate(int* nums, int numsSize) {
    int retVal = 0;

    int* pCount = (int*)malloc(numsSize * sizeof(int));
    if (pCount == NULL) {
        perror("malloc");
        return retVal;
    }
    memset(pCount, 0, (numsSize * sizeof(int)));

    int i;
    for (i = 0; i < numsSize; ++i) {
        if (pCount[nums[i]] != 0) {
            retVal = nums[i];
            break;
        }
        pCount[nums[i]]++;
    }
    free(pCount);
    pCount = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int findDuplicate(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        vector<int> count(numsSize, 0);
        for (auto num : nums) {
            if (count[num] != 0){
                retVal = num;
                break;
            }
            count[num]++;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def findDuplicate(self, nums: List[int]) -> int:
        retVal = 0

        retVal = Counter(nums).most_common(1)[0][0]

        return retVal
```

</details>

## [289. Game of Life](https://leetcode.com/problems/game-of-life/)

- [Official](https://leetcode.cn/problems/game-of-life/solutions/179750/sheng-ming-you-xi-by-leetcode-solution/)

<details><summary>Description</summary>

```text
According to Wikipedia's article:
"The Game of Life, also known simply as Life,
is a cellular automaton devised by the British mathematician John Horton Conway in 1970."

The board is made up of an m x n grid of cells, where each cell has an initial state:
live (represented by a 1) or dead (represented by a 0).
Each cell interacts with its eight neighbors (horizontal, vertical, diagonal)
using the following four rules (taken from the above Wikipedia article):
 1. Any live cell with fewer than two live neighbors dies as if caused by under-population.
 2. Any live cell with two or three live neighbors lives on to the next generation.
 3. Any live cell with more than three live neighbors dies, as if by over-population.
 4. Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

The next state is created by applying the above rules simultaneously to every cell in the current state,
where births and deaths occur simultaneously.
Given the current state of the m x n grid board, return the next state.

Example 1:
+---+---+---+      +---+---+---+
| 0 | 1 | 0 |      | 0 | 0 | 0 |
+---+---+---+      +---+---+---+
| 0 | 0 | 1 |      | 1 | 0 | 1 |
+---+---+---+  =>  +---+---+---+
| 1 | 1 | 1 |      | 0 | 1 | 1 |
+---+---+---+      +---+---+---+
| 0 | 0 | 0 |      | 0 | 1 | 0 |
+---+---+---+      +---+---+---+
Input: board = [[0,1,0],[0,0,1],[1,1,1],[0,0,0]]
Output: [[0,0,0],[1,0,1],[0,1,1],[0,1,0]]

Example 2:
+---+---+      +---+---+
| 1 | 1 |      | 1 | 1 |
+---+---+  =>  +---+---+
| 1 | 0 |      | 1 | 1 |
+---+---+      +---+---+
Input: board = [[1,1],[1,0]]
Output: [[1,1],[1,1]]

Constraints:
m == board.length
n == board[i].length
1 <= m, n <= 25
board[i][j] is 0 or 1.

Follow up:
- Could you solve it in-place? Remember that the board needs to be updated simultaneously:
  You cannot update some cells first and then use their updated values to update other cells.
- In this question, we represent the board using a 2D array.
  In principle, the board is infinite, which would cause problems
  when the active area encroaches upon the border of the array (i.e., live cells reach the border).
  How would you address these problems?
```

</details>

<details><summary>C</summary>

```c
void gameOfLife(int** board, int boardSize, int* boardColSize) {
    // m == board.length, n == board[i].length, 1 <= m, n <= 25
    int rowSize = boardSize;
    int colSize = boardColSize[0];
    int x, y;
    int i, j;

    int backup[rowSize][colSize];
    memset(backup, 0, sizeof(backup));
    for (x = 0; x < rowSize; ++x) {
        for (y = 0; y < colSize; ++y) {
            backup[x][y] = board[x][y];
        }
    }

    int live, neighborX, neighborY;
    for (x = 0; x < rowSize; ++x) {
        for (y = 0; y < colSize; ++y) {
            live = 0;
            for (i = -1; i <= 1; ++i) {
                neighborX = x + i;
                if ((neighborX < 0) || (neighborX >= rowSize)) {
                    continue;
                }

                for (j = -1; j <= 1; ++j) {
                    if ((i == 0) && (j == 0)) {
                        continue;
                    }

                    neighborY = y + j;
                    if ((neighborY < 0) || (neighborY >= colSize)) {
                        continue;
                    }

                    if (backup[neighborX][neighborY] == 1) {
                        ++live;
                    }
                }
            }

            if (backup[x][y] == 1) {
                if ((live < 2) || (live > 3)) {
                    board[x][y] = 0;
                }
            } else if (backup[x][y] == 0) {
                if (live == 3) {
                    board[x][y] = 1;
                }
            }
        }
    }
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    void gameOfLife(vector<vector<int>>& board) {
        // m == board.length, n == board[i].length, 1 <= m, n <= 25
        int rowSize = board.size();
        int colSize = board[0].size();

        vector<vector<int>> backup(rowSize, vector<int>(colSize, 0));
        for (int x = 0; x < rowSize; ++x) {
            for (int y = 0; y < colSize; ++y) {
                backup[x][y] = board[x][y];
            }
        }

        for (int x = 0; x < rowSize; ++x) {
            for (int y = 0; y < colSize; ++y) {
                int live = 0;
                for (int i = -1; i <= 1; ++i) {
                    int neighborX = x + i;
                    if ((neighborX < 0) || (neighborX >= rowSize)) {
                        continue;
                    }

                    for (int j = -1; j <= 1; ++j) {
                        if ((i == 0) && (j == 0)) {
                            continue;
                        }

                        int neighborY = y + j;
                        if ((neighborY < 0) || (neighborY >= colSize)) {
                            continue;
                        }

                        if (backup[neighborX][neighborY] == 1) {
                            ++live;
                        }
                    }
                }

                if (backup[x][y] == 1) {
                    if ((live < 2) || (live > 3)) {
                        board[x][y] = 0;
                    }
                } else if (backup[x][y] == 0) {
                    if (live == 3) {
                        board[x][y] = 1;
                    }
                }
            }
        }
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def gameOfLife(self, board: List[List[int]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """
        # m == board.length, n == board[i].length, 1 <= m, n <= 25
        rowSize = len(board)
        colSize = len(board[0])

        backup = [[board[x][y] for y in range(colSize)] for x in range(rowSize)]

        for x in range(rowSize):
            for y in range(colSize):
                live = 0
                for i in range(-1, 2):
                    neighborX = x + i
                    if (neighborX < 0) or (neighborX >= rowSize):
                        continue

                    for j in range(-1, 2):
                        if (i == 0) and (j == 0):
                            continue

                        neighborY = y + j
                        if (neighborY < 0) or (neighborY >= colSize):
                            continue

                        if backup[neighborX][neighborY] == 1:
                            live += 1

                if backup[x][y] == 1:
                    if (live < 2) or (live > 3):
                        board[x][y] = 0
                elif backup[x][y] == 0:
                    if live == 3:
                        board[x][y] = 1
```

</details>

## [485. Max Consecutive Ones](https://leetcode.com/problems/max-consecutive-ones/)

- [Official](https://leetcode.cn/problems/max-consecutive-ones/solutions/603700/zui-da-lian-xu-1de-ge-shu-by-leetcode-so-252a/)

<details><summary>Description</summary>

```text
Given a binary array nums, return the maximum number of consecutive 1's in the array.

Example 1:
Input: nums = [1,1,0,1,1,1]
Output: 3
Explanation: The first two digits or the last three digits are consecutive 1s.
The maximum number of consecutive 1s is 3.

Example 2:
Input: nums = [1,0,1,1,0,1]
Output: 2

Constraints:
1 <= nums.length <= 10^5
nums[i] is either 0 or 1.
```

</details>

<details><summary>Hint</summary>

```text
1. You need to think about two things as far as any window is concerned. One is the starting point for the window.
   How do you detect that a new window of 1s has started? The next part is detecting the ending point for this window.
   How do you detect the ending point for an existing window?
   If you figure these two things out, you will be able to detect the windows of consecutive ones.
   All that remains afterward is to find the longest such window and return the size.
```

</details>

<details><summary>C</summary>

```c
int findMaxConsecutiveOnes(int* nums, int numsSize) {
    int retVal = 0;

    int count = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] == 1) {
            ++count;
            continue;
        }
        retVal = (retVal > count) ? retVal : count;
        count = 0;
    }
    retVal = (retVal > count) ? retVal : count;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int retVal = 0;

        int count = 0;
        for (int num : nums) {
            if (num == 1) {
                ++count;
            } else {
                retVal = max(retVal, count);
                count = 0;
            }
        }
        retVal = max(retVal, count);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def findMaxConsecutiveOnes(self, nums: List[int]) -> int:
        retVal = 0

        count = 0
        for num in nums:
            if num == 1:
                count += 1
            else:
                retVal = max(retVal, count)
                count = 0
        retVal = max(retVal, count)

        return retVal
```

</details>

## [495. Teemo Attacking](https://leetcode.com/problems/teemo-attacking/)

- [Official](https://leetcode.com/problems/teemo-attacking/editorial/)
- [Official](https://leetcode.cn/problems/teemo-attacking/solutions/1092090/ti-mo-gong-ji-by-leetcode-solution-6p4k/)

<details><summary>Description</summary>

```text
Our hero Teemo is attacking an enemy Ashe with poison attacks!
When Teemo attacks Ashe, Ashe gets poisoned for a exactly duration seconds.
More formally, an attack at second t will mean Ashe is poisoned during the inclusive time interval [t, t + duration - 1].
If Teemo attacks again before the poison effect ends, the timer for it is reset,
and the poison effect will end duration seconds after the new attack.

You are given a non-decreasing integer array timeSeries,
where timeSeries[i] denotes that Teemo attacks Ashe at second timeSeries[i], and an integer duration.

Return the total number of seconds that Ashe is poisoned.

Example 1:
Input: timeSeries = [1,4], duration = 2
Output: 4
Explanation: Teemo's attacks on Ashe go as follows:
- At second 1, Teemo attacks, and Ashe is poisoned for seconds 1 and 2.
- At second 4, Teemo attacks, and Ashe is poisoned for seconds 4 and 5.
Ashe is poisoned for seconds 1, 2, 4, and 5, which is 4 seconds in total.

Example 2:
Input: timeSeries = [1,2], duration = 2
Output: 3
Explanation: Teemo's attacks on Ashe go as follows:
- At second 1, Teemo attacks, and Ashe is poisoned for seconds 1 and 2.
- At second 2 however, Teemo attacks again and resets the poison timer. Ashe is poisoned for seconds 2 and 3.
Ashe is poisoned for seconds 1, 2, and 3, which is 3 seconds in total.

Constraints:
1 <= timeSeries.length <= 10^4
0 <= timeSeries[i], duration <= 10^7
timeSeries is sorted in non-decreasing order.
```

</details>

<details><summary>C</summary>

```c
int findPoisonedDuration(int* timeSeries, int timeSeriesSize, int duration) {
    int retVal = 0;

    int expired = 0;
    int i;
    for (i = 0; i < timeSeriesSize; ++i) {
        if (timeSeries[i] >= expired) {
            retVal += duration;
        } else {
            retVal += (timeSeries[i] + duration - expired);
        }
        expired = timeSeries[i] + duration;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {
        int retVal = 0;

        int expired = 0;
        for (auto timeSerie : timeSeries) {
            if (timeSerie >= expired) {
                retVal += duration;
            } else {
                retVal += (timeSerie + duration - expired);
            }
            expired = timeSerie + duration;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def findPoisonedDuration(self, timeSeries: List[int], duration: int) -> int:
        retVal = 0

        expired = 0
        for timeSerie in timeSeries:
            if timeSerie >= expired:
                retVal += duration
            else:
                retVal += (timeSerie + duration - expired)
            expired = timeSerie + duration

        return retVal
```

</details>

## [566. Reshape the Matrix](https://leetcode.com/problems/reshape-the-matrix/)

<details><summary>Description</summary>

```text
In MATLAB, there is a handy function called reshape which can reshape an m x n matrix
into a new one with a different size r x c keeping its original data.

You are given an m x n matrix mat and two integers r and c representing
the number of rows and the number of columns of the wanted reshaped matrix.

The reshaped matrix should be filled with all the elements of the original matrix
in the same row-traversing order as they were.

If the reshape operation with given parameters is possible and legal, output the new reshaped matrix;
Otherwise, output the original matrix.

Example 1:
Input: mat = [[1,2],[3,4]], r = 1, c = 4
Output: [[1,2,3,4]]

Example 2:
Input: mat = [[1,2],[3,4]], r = 2, c = 4
Output: [[1,2],[3,4]]

Constraints:
m == mat.length
n == mat[i].length
1 <= m, n <= 100
-1000 <= mat[i][j] <= 1000
1 <= r, c <= 300
```

</details>

<details><summary>C</summary>

```c
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** matrixReshape(int** mat, int matSize, int* matColSize, int r, int c, int* returnSize, int** returnColumnSizes){
    int** pRetVal = NULL;
    int i, j;

    if ((matSize * (*matColSize)) != (r * c))
    {
        pRetVal = mat;
        (*returnSize) = matSize;
        (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
        if ((*returnColumnSizes) == NULL)
        {
            perror("malloc");
            return pRetVal;
        }
        for (i=0; i<(*returnSize); ++i)
        {
            (*returnColumnSizes)[i] = (*matColSize);
        }

        return pRetVal;
    }

    (*returnSize) = r;
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL)
    {
        perror("malloc");
        return pRetVal;
    }
    for (i=0; i<(*returnSize); ++i)
    {
        (*returnColumnSizes)[i] = c;
    }
    pRetVal = (int**)malloc((*returnSize) * sizeof(int*));
    if (pRetVal == NULL)
    {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }

    int m = 0;
    int n = 0;
    for (i=0; i<(*returnSize); ++i)
    {
        pRetVal[i] = (int*)malloc(((*returnColumnSizes)[i]) * sizeof(int));
        if (pRetVal[i] == NULL)
        {
            perror("malloc");
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            for (j=0; j<i; ++j)
            {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }

        for (j=0; j<((*returnColumnSizes)[i]); ++j)
        {
            pRetVal[i][j] = mat[m][n++];
            if (n == (*matColSize))
            {
                ++m;
                n = 0;
            }
            if (m == matSize)
            {
                return pRetVal;
            }
        }
    }

    return pRetVal;
}
```

</details>

## [621. Task Scheduler](https://leetcode.com/problems/task-scheduler/)

- [Official](https://leetcode.com/problems/task-scheduler/editorial/)
- [Official](https://leetcode.cn/problems/task-scheduler/solutions/509687/ren-wu-diao-du-qi-by-leetcode-solution-ur9w/)

<details><summary>Description</summary>

```text
You are given an array of CPU tasks, each represented by letters A to Z, and a cooling time, n.
Each cycle or interval allows the completion of one task.
Tasks can be completed in any order, but there's a constraint:
identical tasks must be separated by at least n intervals due to cooling time.

​Return the minimum number of intervals required to complete all tasks.

Example 1:
Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation: A possible sequence is: A -> B -> idle -> A -> B -> idle -> A -> B.
After completing task A, you must wait two cycles before doing A again.
The same applies to task B. In the 3rd interval, neither A nor B can be done,
so you idle. By the 4th cycle, you can do A again as 2 intervals have passed.

Example 2:
Input: tasks = ["A","C","A","B","D","B"], n = 1
Output: 6
Explanation: A possible sequence is: A -> B -> C -> D -> A -> B.
With a cooling interval of 1, you can repeat a task after just one other task.

Example 3:
Input: tasks = ["A","A","A", "B","B","B"], n = 3
Output: 10
Explanation: A possible sequence is: A -> B -> idle -> idle -> A -> B -> idle -> idle -> A -> B.
There are only two types of tasks, A and B, which need to be separated by 3 intervals.
This leads to idling twice between repetitions of these tasks.

Constraints:
1 <= tasks.length <= 10^4
tasks[i] is an uppercase English letter.
0 <= n <= 100
```

</details>

<details><summary>C</summary>

```c
int leastInterval(char* tasks, int tasksSize, int n) {
    int retVal = 0;

    int frequencySize = 26;
    int frequency[frequencySize];
    memset(frequency, 0, sizeof(frequency));
    int maxFrequency = 0;

    int i;
    for (i = 0; i < tasksSize; ++i) {
        int idx = tasks[i] - 'A';
        frequency[idx]++;
        maxFrequency = fmax(maxFrequency, frequency[idx]);
    }

    int time = (maxFrequency - 1) * (n + 1);
    for (i = 0; i < frequencySize; ++i) {
        if (frequency[i] == maxFrequency) {
            time++;
        }
    }

    retVal = fmax(tasksSize, time);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int leastInterval(vector<char>& tasks, int n) {
        int retVal = 0;

        int tasksSize = tasks.size();

        vector<int> frequency(26, 0);
        int maxFrequency = 0;
        for (char task : tasks) {
            int idx = task - 'A';
            frequency[idx]++;
            maxFrequency = max(maxFrequency, frequency[idx]);
        }

        int time = (maxFrequency - 1) * (n + 1);
        for (int f : frequency) {
            if (f == maxFrequency) {
                time++;
            }
        }

        retVal = max(tasksSize, time);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def leastInterval(self, tasks: List[str], n: int) -> int:
        retVal = 0

        tasksSize = len(tasks)

        frequency = [0] * 26
        maxFrequency = 0
        for task in tasks:
            idx = ord(task) - ord('A')
            frequency[idx] += 1
            maxFrequency = max(maxFrequency, frequency[idx])

        time = (maxFrequency - 1) * (n + 1)
        for f in frequency:
            if f == maxFrequency:
                time += 1

        retVal = max(tasksSize, time)

        return retVal
```

</details>

## [661. Image Smoother](https://leetcode.com/problems/image-smoother/)

- [Official](https://leetcode.com/problems/image-smoother/editorial/)
- [Official](https://leetcode.cn/problems/image-smoother/solutions/1358687/tu-pian-ping-hua-qi-by-leetcode-solution-9oi5/)

<details><summary>Description</summary>

```text
An image smoother is a filter of the size 3 x 3 that can be applied to each cell of an image
by rounding down the average of the cell and the eight surrounding cells
(i.e., the average of the nine cells in the blue smoother).
If one or more of the surrounding cells of a cell is not present,
we do not consider it in the average (i.e., the average of the four cells in the red smoother).

Given an m x n integer matrix img representing the grayscale of an image,
return the image after applying the smoother on each cell of it.

Example 1:
Input: img = [[1,1,1],[1,0,1],[1,1,1]]
Output: [[0,0,0],[0,0,0],[0,0,0]]
Explanation:
For the points (0,0), (0,2), (2,0), (2,2): floor(3/4) = floor(0.75) = 0
For the points (0,1), (1,0), (1,2), (2,1): floor(5/6) = floor(0.83333333) = 0
For the point (1,1): floor(8/9) = floor(0.88888889) = 0

Example 2:
Input: img = [[100,200,100],[200,50,200],[100,200,100]]
Output: [[137,141,137],[141,138,141],[137,141,137]]
Explanation:
For the points (0,0), (0,2), (2,0), (2,2): floor((100+200+200+50)/4) = floor(137.5) = 137
For the points (0,1), (1,0), (1,2), (2,1): floor((200+200+50+200+100+100)/6) = floor(141.666667) = 141
For the point (1,1): floor((50+200+200+200+200+100+100+100+100)/9) = floor(138.888889) = 138

Constraints:
m == img.length
n == img[i].length
1 <= m, n <= 200
0 <= img[i][j] <= 255
```

</details>

<details><summary>C</summary>

```c
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** imageSmoother(int** img, int imgSize, int* imgColSize, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;
    int i, j, x, y;

    int rowSize = imgSize;
    int colSize = imgColSize[0];
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

    int sum, count;
    for (i = 0; i < rowSize; ++i) {
        for (j = 0; j < colSize; ++j) {
            sum = 0;
            count = 0;
            for (x = (i - 1); x <= (i + 1); ++x) {
                for (y = (j - 1); y <= (j + 1); ++y) {
                    if (((0 <= x) && (x < rowSize)) && ((0 <= y) && (y < colSize))) {
                        sum += img[x][y];
                        count += 1;
                    }
                }
            }
            pRetVal[i][j] = sum / count;
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
    vector<vector<int>> imageSmoother(vector<vector<int>>& img) {
        vector<vector<int>> retVal;

        int rowSize = img.size();
        int colSize = img[0].size();

        retVal.resize(rowSize, vector<int>(colSize, 0));
        for (int i = 0; i < rowSize; ++i) {
            for (int j = 0; j < colSize; ++j) {
                int sum = 0;
                int count = 0;
                for (int x = (i - 1); x <= (i + 1); ++x) {
                    for (int y = (j - 1); y <= (j + 1); ++y) {
                        if (((0 <= x) && (x < rowSize)) && ((0 <= y) && (y < colSize))) {
                            sum += img[x][y];
                            count += 1;
                        }
                    }
                }
                retVal[i][j] = sum / count;
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
    def imageSmoother(self, img: List[List[int]]) -> List[List[int]]:
        retVal = []

        rowSize = len(img)
        colSize = len(img[0])

        retVal = [[0] * colSize for _ in range(rowSize)]
        for i in range(rowSize):
            for j in range(colSize):
                sum = 0
                count = 0
                for x in (i - 1, i, i + 1):
                    for y in (j - 1, j, j + 1):
                        if (0 <= x < rowSize) and (0 <= y < colSize):
                            sum += img[x][y]
                            count += 1
                retVal[i][j] = sum // count

        return retVal
```

</details>

## [665. Non-decreasing Array](https://leetcode.com/problems/non-decreasing-array/)

- [Official](https://leetcode.cn/problems/non-decreasing-array/solutions/594758/fei-di-jian-shu-lie-by-leetcode-solution-zdsm/)

<details><summary>Description</summary>

```text
Given an array nums with n integers, your task is to check if it could become non-decreasing by modifying at most one element.

We define an array is non-decreasing if nums[i] <= nums[i + 1] holds for every i (0-based) such that (0 <= i <= n - 2).

Example 1:
Input: nums = [4,2,3]
Output: true
Explanation: You could modify the first 4 to 1 to get a non-decreasing array.

Example 2:
Input: nums = [4,2,1]
Output: false
Explanation: You cannot get a non-decreasing array by modifying at most one element.

Constraints:
n == nums.length
1 <= n <= 10^4
-10^5 <= nums[i] <= 10^5
```

</details>

<details><summary>C</summary>

```c
bool checkPossibility(int* nums, int numsSize) {
    bool retVal = false;

    int modify = 0;
    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[i - 1] <= nums[i]) {
            continue;
        }

        ++modify;
        if (modify > 1) {
            return retVal;
        }
        if ((i >= 2) && (nums[i] < nums[i - 2])) {
            nums[i] = nums[i - 1];
        }
    }
    retVal = true;

    return retVal;
}
```

</details>

## [674. Longest Continuous Increasing Subsequence](https://leetcode.com/problems/longest-continuous-increasing-subsequence/)

- [Official](https://leetcode.com/problems/longest-continuous-increasing-subsequence/editorial/)
- [Official](https://leetcode.cn/problems/longest-continuous-increasing-subsequence/solutions/573383/zui-chang-lian-xu-di-zeng-xu-lie-by-leet-dmb8/)

<details><summary>Description</summary>

```text
Given an unsorted array of integers nums,
return the length of the longest continuous increasing subsequence (i.e. subarray).
The subsequence must be strictly increasing.

A continuous increasing subsequence is defined by two indices l and r (l < r)
such that it is [nums[l], nums[l + 1], ..., nums[r - 1], nums[r]] and for each l <= i < r, nums[i] < nums[i + 1].

Example 1:
Input: nums = [1,3,5,4,7]
Output: 3
Explanation: The longest continuous increasing subsequence is [1,3,5] with length 3.
Even though [1,3,5,7] is an increasing subsequence, it is not continuous as elements 5 and 7 are separated by element 4.

Example 2:
Input: nums = [2,2,2,2,2]
Output: 1
Explanation: The longest continuous increasing subsequence is [2] with length 1.
Note that it must be strictly increasing.

Constraints:
1 <= nums.length <= 10^4
-10^9 <= nums[i] <= 10^9
```

</details>

<details><summary>C</summary>

```c
int findLengthOfLCIS(int* nums, int numsSize) {
    int retVal = 0;

    int previousNum = INT_MIN;  // - 10 ^ 9 <= nums[i] <= 10 ^ 9
    int count = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] > previousNum) {
            ++count;
        } else {
            retVal = fmax(retVal, count);
            count = 1;
        }
        previousNum = nums[i];
    }
    retVal = fmax(retVal, count);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int findLengthOfLCIS(vector<int>& nums) {
        int retVal = 0;

        int previousNum = numeric_limits<int>::min();  // - 10 ^ 9 <= nums[i] <= 10 ^ 9
        int count = 0;
        for (int num : nums) {
            if (num > previousNum) {
                ++count;
            } else {
                retVal = max(retVal, count);
                count = 1;
            }
            previousNum = num;
        }
        retVal = max(retVal, count);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def findLengthOfLCIS(self, nums: List[int]) -> int:
        retVal = 0

        previousNum = float('-inf')   # -10^9 <= nums[i] <= 10^9
        count = 0
        for num in nums:
            if num > previousNum:
                count += 1
            else:
                retVal = max(retVal, count)
                count = 1
            previousNum = num
        retVal = max(retVal, count)

        return retVal
```

</details>

## [744. Find Smallest Letter Greater Than Target](https://leetcode.com/problems/find-smallest-letter-greater-than-target/)

- [Official](https://leetcode.com/problems/find-smallest-letter-greater-than-target/editorial/)
- [Official](https://leetcode.cn/problems/find-smallest-letter-greater-than-target/solutions/1385592/xun-zhao-bi-mu-biao-zi-mu-da-de-zui-xiao-lhm7/)

<details><summary>Description</summary>

```text
You are given an array of characters letters that is sorted in non-decreasing order, and a character target.
There are at least two different characters in letters.

Return the smallest character in letters that is lexicographically greater than target.
If such a character does not exist, return the first character in letters.

Example 1:
Input: letters = ["c","f","j"], target = "a"
Output: "c"
Explanation: The smallest character that is lexicographically greater than 'a' in letters is 'c'.

Example 2:
Input: letters = ["c","f","j"], target = "c"
Output: "f"
Explanation: The smallest character that is lexicographically greater than 'c' in letters is 'f'.

Example 3:
Input: letters = ["x","x","y","y"], target = "z"
Output: "x"
Explanation: There are no characters in letters that is lexicographically greater than 'z' so we return letters[0].

Constraints:
2 <= letters.length <= 10^4
letters[i] is a lowercase English letter.
letters is sorted in non-decreasing order.
letters contains at least two different characters.
target is a lowercase English letter.
```

<details><summary>Hint</summary>

```text
1. Try to find whether each of 26 next letters are in the given string array.
```

</details>

</details>

<details><summary>C</summary>

```c
char nextGreatestLetter(char* letters, int lettersSize, char target) {
    char retVal = letters[0];

    int i;
    for (i = 0; i < lettersSize; ++i) {
        if (letters[i] > target) {
            retVal = letters[i];
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
    char nextGreatestLetter(vector<char>& letters, char target) {
        char retVal = letters[0];

        for (auto c : letters) {
            if (c > target) {
                retVal = c;
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
    def nextGreatestLetter(self, letters: List[str], target: str) -> str:
        retVal = letters[0]

        for c in letters:
            if c > target:
                retVal = c
                break

        return retVal
```

</details>

## [766. Toeplitz Matrix](https://leetcode.com/problems/toeplitz-matrix/)  1249

<details><summary>Description</summary>

```text
Given an m x n matrix, return true if the matrix is Toeplitz. Otherwise, return false.

A matrix is Toeplitz if every diagonal from top-left to bottom-right has the same elements.

Example 1:
Input: matrix = [[1,2,3,4],[5,1,2,3],[9,5,1,2]]
Output: true
Explanation:
In the above grid, the diagonals are:
"[9]", "[5, 5]", "[1, 1, 1]", "[2, 2, 2]", "[3, 3]", "[4]".
In each diagonal all elements are the same, so the answer is True.

Example 2:
Input: matrix = [[1,2],[2,2]]
Output: false
Explanation:
The diagonal "[1, 2]" has different elements.

Constraints:
m == matrix.length
n == matrix[i].length
1 <= m, n <= 20
0 <= matrix[i][j] <= 99

Follow up:
- What if the matrix is stored on disk,
  and the memory is limited such that you can only load at most one row of the matrix into the memory at once?
- What if the matrix is so large that you can only load up a partial row into the memory at once?
```

</details>

<details><summary>C</summary>

```c
bool isToeplitzMatrix(int** matrix, int matrixSize, int* matrixColSize) {
    bool retVal = false;

    int i, j;
    for (i=1; i<matrixSize; ++i) {
        for (j=1; j<matrixColSize[i]; ++j) {
            if (matrix[i-1][j-1] != matrix[i][j]) {
                return retVal;
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
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        bool retVal = false;

        for (long unsigned int i=1; i<matrix.size(); ++i) {
            for (long unsigned int j=1; j<matrix[i].size(); ++j) {
                if (matrix[i-1][j-1] != matrix[i][j]) {
                    return retVal;
                }
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
    def isToeplitzMatrix(self, matrix: List[List[int]]) -> bool:
        for i in range(1, len(matrix)):
            for j in range(1, len(matrix[i])):
                if matrix[i-1][j-1] != matrix[i][j]:
                    return False

        return True
```

</details>

## [835. Image Overlap](https://leetcode.com/problems/image-overlap/)  1969

<details><summary>Description</summary>

```text
You are given two images, img1 and img2, represented as binary, square matrices of size n x n.
A binary matrix has only 0s and 1s as values.

We translate one image however we choose by sliding all the 1 bits left, right, up, and/or down any number of units.
We then place it on top of the other image.
We can then calculate the overlap by counting the number of positions that have a 1 in both images.

Note also that a translation does not include any kind of rotation.
Any 1 bits that are translated outside of the matrix borders are erased.

Return the largest possible overlap.

Example 1:
Input: img1 = [[1,1,0],[0,1,0],[0,1,0]], img2 = [[0,0,0],[0,1,1],[0,0,1]]
Output: 3
Explanation: We translate img1 to right by 1 unit and down by 1 unit.
The number of positions that have a 1 in both images is 3 (shown in red).

Example 2:
Input: img1 = [[1]], img2 = [[1]]
Output: 1

Example 3:
Input: img1 = [[0]], img2 = [[0]]
Output: 0

Constraints:
n == img1.length == img1[i].length
n == img2.length == img2[i].length
1 <= n <= 30
img1[i][j] is either 0 or 1.
img2[i][j] is either 0 or 1.
```

</details>

<details><summary>C</summary>

```c
#define BRUTE_FORCE     (1)

#if (BRUTE_FORCE)   // Time Complexity: O(n^4), Space Complexity: O(n^2)
int overlap(int** img1, int** img2, int n, int row, int col)
{
    int count = 0;

    int i, j;

    // create shifting img1
    int tmp[n][n];
    int x, y;
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            tmp[i][j] = 0;

            x = -1;
            if (((i+row) >= 0) && ((i+row) < n))
            {
                x = i + row;
            }

            y = -1;
            if (((j+col) >= 0) && ((j+col) < n))
            {
                y = j + col;
            }

            if ((x >= 0) && (y >= 0))
            {
                tmp[i][j] = img1[x][y];
            }
        }
    }

    // count overlap
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            if (tmp[i][j] == 0)
            {
                continue;
            }
            if (tmp[i][j] == img2[i][j])
            {
                count++;
            }
        }
    }

    return count;
}
#endif

int largestOverlap(int** img1, int img1Size, int* img1ColSize, int** img2, int img2Size, int* img2ColSize){
    int retVal = 0;

#if (BRUTE_FORCE)
    int n = img1Size;
    int count;
    int i, j;
    for (i=(-n+1); i<n; i++)
    {
        for (j=(-n+1); j<n; j++)
        {
            count = overlap(img1, img2, n, i, j);
            retVal = (retVal>count)?retVal:count;
        }
    }
#endif

    return retVal;
}
```

</details>

## [867. Transpose Matrix](https://leetcode.com/problems/transpose-matrix/)  1258

- [Official](https://leetcode.com/problems/transpose-matrix/editorial/)
- [Official](https://leetcode.cn/problems/transpose-matrix/solutions/620604/zhuan-zhi-ju-zhen-by-leetcode-solution-85s2/)

<details><summary>Description</summary>

```text
Given a 2D integer array matrix, return the transpose of matrix.

The transpose of a matrix is the matrix flipped over its main diagonal, switching the matrix's row and column indices.

Example 1:
Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[1,4,7],[2,5,8],[3,6,9]]

Example 2:
Input: matrix = [[1,2,3],[4,5,6]]
Output: [[1,4],[2,5],[3,6]]

Constraints:
m == matrix.length
n == matrix[i].length
1 <= m, n <= 1000
1 <= m * n <= 10^5
-10^9 <= matrix[i][j] <= 10^9
```

<details><summary>Hint</summary>

```text
1. We don't need any special algorithms to do this.
   You just need to know what the transpose of a matrix looks like. Rows become columns and vice versa!
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
int** transpose(int** matrix, int matrixSize, int* matrixColSize, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    int rowSize = matrixColSize[0];
    int colSize = matrixSize;
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
                free(pRetVal);
                pRetVal = NULL;
            }
            return pRetVal;
        }
        memset(pRetVal[i], 0, (colSize * sizeof(int)));
    }
    (*returnColumnSizes) = (int*)malloc(rowSize * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        for (j = 0; j < colSize; ++j) {
            free(pRetVal[j]);
            pRetVal[j] = NULL;
            free(pRetVal);
            pRetVal = NULL;
        }
        return pRetVal;
    }
    for (i = 0; i < rowSize; ++i) {
        (*returnColumnSizes)[i] = colSize;
    }
    (*returnSize) = rowSize;

    for (i = 0; i < matrixSize; ++i) {
        for (j = 0; j < matrixColSize[i]; ++j) {
            pRetVal[j][i] = matrix[i][j];
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
    vector<vector<int>> transpose(vector<vector<int>>& matrix) {
        vector<vector<int>> retVal;

        int rowSize = matrix[0].size();
        int colSize = matrix.size();
        retVal.resize(rowSize, vector<int>(colSize, 0));
        for (int i = 0; i < rowSize; ++i) {
            for (int j = 0; j < colSize; ++j) {
                retVal[i][j] = matrix[j][i];
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
    def transpose(self, matrix: List[List[int]]) -> List[List[int]]:
        retVal = [[]]

        rowSize = len(matrix[0])
        colSize = len(matrix)
        retVal = [[0] * colSize for _ in range(rowSize)]
        for i, row in enumerate(matrix):
            for j, value in enumerate(row):
                retVal[j][i] = value

        return retVal
```

</details>

## [885. Spiral Matrix III](https://leetcode.com/problems/spiral-matrix-iii/)  1678

- [Official](https://leetcode.com/problems/spiral-matrix-iii/editorial/)
- [Official](https://leetcode.cn/problems/spiral-matrix-iii/solutions/3546/luo-xuan-ju-zhen-iii-by-leetcode/)

<details><summary>Description</summary>

```text
You start at the cell (rStart, cStart) of an rows x cols grid facing east.
The northwest corner is at the first row and column in the grid, and the southeast corner is at the last row and column.

You will walk in a clockwise spiral shape to visit every position in this grid.
Whenever you move outside the grid's boundary,
we continue our walk outside the grid (but may return to the grid boundary later.).
Eventually, we reach all rows * cols spaces of the grid.

Return an array of coordinates representing the positions of the grid in the order you visited them.

Example 1:
Input: rows = 1, cols = 4, rStart = 0, cStart = 0
Output: [[0,0],[0,1],[0,2],[0,3]]

Example 2:
Input: rows = 5, cols = 6, rStart = 1, cStart = 4
Output: [[1,4],[1,5],[2,5],[2,4],[2,3],[1,3],[0,3],[0,4],[0,5],[3,5],[3,4],[3,3],[3,2],[2,2],[1,2],[0,2],
[4,5],[4,4],[4,3],[4,2],[4,1],[3,1],[2,1],[1,1],[0,1],[4,0],[3,0],[2,0],[1,0],[0,0]]

Constraints:
1 <= rows, cols <= 100
0 <= rStart < rows
0 <= cStart < cols
```

</details>

<details><summary>C</summary>

```c
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** spiralMatrixIII(int rows, int cols, int rStart, int cStart, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int**)malloc(rows * cols * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    (*returnColumnSizes) = (int*)malloc(rows * cols * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }

    // East, South, West, North
    const int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    int idx = 0;
    int retValSize = (*returnSize);
    int i, j;
    int step;
    for (step = 1; retValSize < rows * cols;) {
        for (i = 0; i < 2; ++i) {
            for (j = 0; j < step; ++j) {
                if ((rStart >= 0) && (rStart < rows) && (cStart >= 0) && (cStart < cols)) {
                    pRetVal[(*returnSize)] = (int*)malloc(2 * sizeof(int));
                    if (pRetVal[(*returnSize)] == NULL) {
                        perror("malloc");
                        for (i = 0; i < (*returnSize); ++i) {
                            free(pRetVal[i]);
                            pRetVal[i] = NULL;
                        }
                        free(pRetVal);
                        pRetVal = NULL;
                        free((*returnColumnSizes));
                        (*returnColumnSizes) = NULL;
                        (*returnSize) = 0;
                        return pRetVal;
                    }
                    memset(pRetVal[(*returnSize)], 0, (2 * sizeof(int)));
                    (*returnColumnSizes)[(*returnSize)] = 2;

                    pRetVal[(*returnSize)][0] = rStart;
                    pRetVal[(*returnSize)][1] = cStart;
                    (*returnSize) += 1;
                }
                rStart += directions[idx][0];
                cStart += directions[idx][1];
            }
            idx = (idx + 1) % 4;
        }
        ++step;
        retValSize = (*returnSize);
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart) {
        vector<vector<int>> retVal;

        // East, South, West, North
        vector<vector<int>> directions{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        int idx = 0;
        int retValSize = retVal.size();
        for (int step = 1; retValSize < rows * cols;) {
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < step; ++j) {
                    if ((rStart >= 0) && (rStart < rows) && (cStart >= 0) && (cStart < cols)) {
                        retVal.push_back({rStart, cStart});
                    }
                    rStart += directions[idx][0];
                    cStart += directions[idx][1];
                }
                idx = (idx + 1) % 4;
            }
            ++step;
            retValSize = retVal.size();
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def spiralMatrixIII(self, rows: int, cols: int, rStart: int, cStart: int) -> List[List[int]]:
        retVal = []

        # East, South, West, North
        directions = [[0, 1], [1, 0], [0, -1], [-1, 0]]

        step = 1
        idx = 0
        retValSize = len(retVal)
        while retValSize < (rows * cols):
            for _ in range(2):
                for _ in range(step):
                    if ((rStart >= 0) and (rStart < rows) and (cStart >= 0) and (cStart < cols)):
                        retVal.append([rStart, cStart])
                    rStart += directions[idx][0]
                    cStart += directions[idx][1]
                idx = (idx + 1) % 4
            step += 1
            retValSize = len(retVal)

        return retVal
```

</details>

## [896. Monotonic Array](https://leetcode.com/problems/monotonic-array/)  1258

- [Official](https://leetcode.cn/problems/monotonic-array/solutions/624659/dan-diao-shu-lie-by-leetcode-solution-ysex/)

<details><summary>Description</summary>

```text
An array is monotonic if it is either monotone increasing or monotone decreasing.

An array nums is monotone increasing if for all i <= j, nums[i] <= nums[j].
An array nums is monotone decreasing if for all i <= j, nums[i] >= nums[j].

Given an integer array nums, return true if the given array is monotonic, or false otherwise.

Example 1:
Input: nums = [1,2,2,3]
Output: true

Example 2:
Input: nums = [6,5,4,4]
Output: true

Example 3:
Input: nums = [1,3,2]
Output: false

Constraints:
1 <= nums.length <= 10^5
-10^5 <= nums[i] <= 10^5
```

</details>

<details><summary>C</summary>

```c
bool isMonotonic(int* nums, int numsSize) {
    bool retVal = true;

    if (numsSize == 1) {  // 1 <= nums.length <= 10^5
        return retVal;
    }

    int diff = 1;
    int previous = 0;
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i] == nums[i - 1]) {
            continue;
        } else if (nums[i] > nums[i - 1]) {
            diff = 1;
        } else if (nums[i] < nums[i - 1]) {
            diff = -1;
        }

        if (previous != 0) {
            if (previous != diff) {
                retVal = false;
                break;
            }
        }
        previous = diff;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    bool isMonotonic(vector<int>& nums) {
        bool retVal = true;

        int numsSize = nums.size();
        if (numsSize == 1) {  // 1 <= nums.length <= 10^5
            return retVal;
        }

        int diff = 1;
        int previous = 0;
        for (int i = 1; i < numsSize; ++i) {
            if (nums[i] == nums[i - 1]) {
                continue;
            } else if (nums[i] > nums[i - 1]) {
                diff = 1;
            } else if (nums[i] < nums[i - 1]) {
                diff = -1;
            }

            if (previous != 0) {
                if (previous != diff) {
                    retVal = false;
                    break;
                }
            }
            previous = diff;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def isMonotonic(self, nums: List[int]) -> bool:
        retVal = True

        numsSize = len(nums)
        if numsSize == 1:   # 1 <= nums.length <= 10^5
            return retVal

        previous = 0
        for i in range(1, numsSize):
            if nums[i] == nums[i-1]:
                continue
            elif nums[i] > nums[i-1]:
                diff = 1
            elif nums[i] < nums[i-1]:
                diff = -1

            if (previous != 0):
                if previous != diff:
                    retVal = False
                    break
            previous = diff

        return retVal
```

</details>

## [941. Valid Mountain Array](https://leetcode.com/problems/valid-mountain-array/)  1208

<details><summary>Description</summary>

```text
Given an array of integers arr, return true if and only if it is a valid mountain array.

Recall that arr is a mountain array if and only if:
- arr.length >= 3
- There exists some i with 0 < i < arr.length - 1 such that:
  - arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
  - arr[i] > arr[i + 1] > ... > arr[arr.length - 1]

Example 1:
Input: arr = [2,1]
Output: false

Example 2:
Input: arr = [3,5,5]
Output: false

Example 3:
Input: arr = [0,3,2,1]
Output: true

Constraints:
1 <= arr.length <= 10^4
0 <= arr[i] <= 10^4
```

</details>

<details><summary>C</summary>

```c
bool validMountainArray(int* arr, int arrSize){
    bool retVal = false;

    if (arrSize < 3)
    {
        return retVal;
    }

#if 1
    int i = 0;
    while (i < (arrSize-1))
    {
        if (arr[i+1] <= arr[i])
        {
            break;
        }
        ++i;
    }
    if (i == 0)
    {
        return retVal;
    }

    int j = arrSize - 1;
    while (j > 0)
    {
        if (arr[j] >= arr[j-1])
        {
            break;
        }
        --j;
    }
    if (j == arrSize - 1)
    {
        return retVal;
    }

    retVal = (i==j)?true:false;
#else
    int i;
    for (i=1; i<arrSize; ++i)
    {
        if (arr[i] == arr[i-1])
        {
            return retVal;
        }
        else if (arr[i] < arr[i-1])
        {
            break;
        }
    }
    if ((i == arrSize) || (i == 1))
    {
        return retVal;
    }

    while (i < arrSize)
    {
        if (arr[i] >= arr[i-1])
        {
            return retVal;
        }
        ++i;
    }
    retVal = true;
#endif

    return retVal;
}
```

</details>

## [944. Delete Columns to Make Sorted](https://leetcode.com/problems/delete-columns-to-make-sorted/)  1396

- [Official](https://leetcode.com/problems/delete-columns-to-make-sorted/solutions/2868555/delete-columns-to-make-sorted/)
- [Official](https://leetcode.cn/problems/delete-columns-to-make-sorted/solutions/1483008/shan-lie-zao-xu-by-leetcode-solution-bqyy/)

<details><summary>Description</summary>

```text
You are given an array of n strings strs, all of the same length.

The strings can be arranged such that there is one on each line, making a grid.
For example, strs = ["abc", "bce", "cae"] can be arranged as:
abc
bce
cae
You want to delete the columns that are not sorted lexicographically.
In the above example (0-indexed),
columns 0 ('a', 'b', 'c') and 2 ('c', 'e', 'e') are sorted while column 1 ('b', 'c', 'a') is not,
so you would delete column 1.

Return the number of columns that you will delete.

Example 1:
Input: strs = ["cba","daf","ghi"]
Output: 1
Explanation: The grid looks as follows:
  cba
  daf
  ghi
Columns 0 and 2 are sorted, but column 1 is not, so you only need to delete 1 column.

Example 2:
Input: strs = ["a","b"]
Output: 0
Explanation: The grid looks as follows:
  a
  b
Column 0 is the only column and is sorted, so you will not delete any columns.

Example 3:
Input: strs = ["zyx","wvu","tsr"]
Output: 3
Explanation: The grid looks as follows:
  zyx
  wvu
  tsr
All 3 columns are not sorted, so you will delete all 3.

Constraints:
n == strs.length
1 <= n <= 100
1 <= strs[i].length <= 1000
strs[i] consists of lowercase English letters.
```

</details>

<details><summary>C</summary>

```c
int minDeletionSize(char** strs, int strsSize) {
    int retVal = 0;

    int len = strlen(strs[0]);
    int i, j;
    for (i = 0; i < len; ++i) {
        for (j = 1; j < strsSize; ++j) {
            if (strs[j - 1][i] > strs[j][i]) {
                ++retVal;
                break;
            }
        }
    }

    return retVal;
}
```

</details>

## [985. Sum of Even Numbers After Queries](https://leetcode.com/problems/sum-of-even-numbers-after-queries/)  1198

<details><summary>Description</summary>

```text
You are given an integer array nums and an array queries where queries[i] = [vali, indexi].

For each query i, first, apply nums[indexi] = nums[indexi] + vali, then print the sum of the even values of nums.

Return an integer array answer where answer[i] is the answer to the ith query.

Example 1:
Input: nums = [1,2,3,4], queries = [[1,0],[-3,1],[-4,0],[2,3]]
Output: [8,6,2,4]
Explanation: At the beginning, the array is [1,2,3,4].
After adding 1 to nums[0], the array is [2,2,3,4], and the sum of even values is 2 + 2 + 4 = 8.
After adding -3 to nums[1], the array is [2,-1,3,4], and the sum of even values is 2 + 4 = 6.
After adding -4 to nums[0], the array is [-2,-1,3,4], and the sum of even values is -2 + 4 = 2.
After adding 2 to nums[3], the array is [-2,-1,3,6], and the sum of even values is -2 + 6 = 4.

Example 2:
Input: nums = [1], queries = [[4,0]]
Output: [0]

Constraints:
1 <= nums.length <= 10^4
-10^4 <= nums[i] <= 10^4
1 <= queries.length <= 10^4
-10^4 <= vali <= 10^4
0 <= indexi < nums.length
```

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sumEvenAfterQueries(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    int* pRetVal;
    *returnSize = queriesSize;
    pRetVal = (int*)malloc(*returnSize*sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        *returnSize = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, *returnSize*sizeof(int));

    int i;
#if 1
    int sum = 0;
    for (i=0; i<numsSize; ++i) {
        sum += (nums[i]%2==0)?nums[i]:0;
    }

    int index;
    int value;
    for (i=0; i<queriesSize; ++i) {
        index = queries[i][1];
        value = queries[i][0];
        if (nums[index]%2 == 0) {
            if (value%2 == 0) {
                sum += value;
            }
            else {
                sum -= nums[index];
            }
        }
        else {
            if (value%2 == 0) {
                ;
            }
            else {
                sum += (nums[index] + value);
            }
        }
        nums[index] += value;
        pRetVal[i] = sum;
    }
#else
    int j;
    for (i=0; i<queriesSize; ++i) {
        nums[queries[i][1]] += queries[i][0];
        for (j=0; j<numsSize; ++j) {
            pRetVal[i] += (nums[j]%2==0)?nums[j]:0;
        }
    }
#endif

    return pRetVal;
}
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def sumEvenAfterQueries(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        retVal = []

        total = sum(i for i in nums if i%2==0)
        for i in range(0,len(queries)):
            index = queries[i][1]
            value = queries[i][0]
            if (nums[index]%2 == 0):
                if (value%2 == 0):
                    total += value;
                else:
                    total -= nums[index];
            else:
                if (value%2 == 0):
                    pass
                else:
                    total += (nums[index] + value);
            nums[index] += value
            retVal.append(total)

        return retVal
```

</details>

## [989. Add to Array-Form of Integer](https://leetcode.com/problems/add-to-array-form-of-integer/)  1234

- [Official](https://leetcode.com/problems/add-to-array-form-of-integer/solutions/234456/add-to-array-form-of-integer/)
- [Official](https://leetcode.cn/problems/add-to-array-form-of-integer/solutions/570434/shu-zu-xing-shi-de-zheng-shu-jia-fa-by-l-jljp/)

<details><summary>Description</summary>

```text
The array-form of an integer num is an array representing its digits in left to right order.
- For example, for num = 1321, the array form is [1,3,2,1].
Given num, the array-form of an integer, and an integer k, return the array-form of the integer num + k.

Example 1:
Input: num = [1,2,0,0], k = 34
Output: [1,2,3,4]
Explanation: 1200 + 34 = 1234

Example 2:
Input: num = [2,7,4], k = 181
Output: [4,5,5]
Explanation: 274 + 181 = 455

Example 3:
Input: num = [2,1,5], k = 806
Output: [1,0,2,1]
Explanation: 215 + 806 = 1021

Constraints:
1 <= num.length <= 10^4
0 <= num[i] <= 9
num does not contain any leading zeros except for the zero itself.
1 <= k <= 10^4

```

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* addToArrayForm(int* num, int numSize, int k, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    // 1 <= k <= 10^4
#define MAX_K_SIZE (5)
    int len = (numSize > MAX_K_SIZE) ? (numSize + 1) : (MAX_K_SIZE + 1);
    int buf[len];
    memset(buf, 0, sizeof(buf));
    --numSize;

    int sum = 0;
    int carry = 0;
    int idx = len - 1;
    while ((numSize >= 0) && (k > 0)) {
        sum = num[numSize--] + (k % 10) + carry;
        carry = sum / 10;
        buf[idx--] = sum % 10;
        k /= 10;
    }
    while (numSize >= 0) {
        sum = num[numSize--] + carry;
        carry = sum / 10;
        buf[idx--] = sum % 10;
    }
    while (k > 0) {
        sum = (k % 10) + carry;
        carry = sum / 10;
        buf[idx--] = sum % 10;
        k /= 10;
    }
    if (carry == 1) {
        buf[idx--] = carry;
    }

    (*returnSize) = len - 1 - idx;
    pRetVal = (int*)calloc((*returnSize), sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memcpy(pRetVal, buf + 1 + idx, (*returnSize) * sizeof(int));

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> addToArrayForm(vector<int>& num, int k) {
        vector<int> retVal;

        int sum;
        int carry = 0;
        int idx = num.size() - 1;
        while ((idx >= 0) && (k > 0)) {
            sum = num[idx] + k % 10 + carry;
            carry = sum / 10;
            retVal.push_back(sum % 10);
            k /= 10;
            --idx;
        }
        while (idx >= 0) {
            sum = num[idx] + carry;
            carry = sum / 10;
            retVal.push_back(sum % 10);
            --idx;
        }
        while (k > 0) {
            sum = k % 10 + carry;
            carry = sum / 10;
            retVal.push_back(sum % 10);
            k /= 10;
        }
        if (sum >= 10) {
            carry = sum / 10;
            retVal.push_back(carry);
        }
        reverse(retVal.begin(), retVal.end());

        return retVal;
    }
};
```

</details>

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

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* minOperations(char* boxes, int* returnSize) {
    int* pRetVal = NULL;

    // malloc return array
    (*returnSize) = strlen(boxes);
    pRetVal = (int*)malloc((*returnSize)*sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize)*sizeof(int)));

    // count moving steps
    int i, j;
    for (i = 0; i < (*returnSize); ++i) {
        for (j = 0; j < (*returnSize); ++j) {
            if ((i == j) || (boxes[j] == '0')) {
                continue;
            }
            pRetVal[i] += (abs(j - i));
        }
    }

    return pRetVal;
}
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

</details>

<details><summary>C</summary>

```c
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** construct2DArray(int* original, int originalSize, int m, int n, int* returnSize, int** returnColumnSizes){
    int** pRetVal = NULL;
    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    if (originalSize != (m * n))
    {
        return pRetVal;
    }

    (*returnSize) = m;
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL)
    {
        perror("malloc");
        return pRetVal;
    }
    int i;
    for (i=0; i<(*returnSize); ++i)
    {
        (*returnColumnSizes)[i] = n;
    }

    pRetVal = (int**)malloc((*returnSize) * sizeof(int*));
    if (pRetVal == NULL)
    {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }

    i = 0;
    int row = 0;
    int col = 0;
    for (row=0; row<(*returnSize); ++row)
    {
        pRetVal[row] = (int*)malloc(((*returnColumnSizes)[row]) * sizeof(int));
        if (pRetVal[row] == NULL)
        {
            perror("malloc");
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            for (i=0; i<row; ++i)
            {
                free(pRetVal[i]);
                pRetVal[i] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        memset(pRetVal[row], 0, ((*returnColumnSizes)[row]) * sizeof(int));

        while (i<originalSize)
        {
            pRetVal[row][col++] = original[i++];
            if (col == (*returnColumnSizes)[row])
            {
                col = 0;
                break;
            }
        }
    }

    return pRetVal;
}
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
