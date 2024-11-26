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

## [840. Magic Squares In Grid](https://leetcode.com/problems/magic-squares-in-grid/)  1425

- [Official](https://leetcode.com/problems/magic-squares-in-grid/editorial/)
- [Official](https://leetcode.cn/problems/magic-squares-in-grid/solutions/107797/ju-zhen-zhong-de-huan-fang-by-leetcode-2/)

<details><summary>Description</summary>

```text
A 3 x 3 magic square is a 3 x 3 grid filled with distinct numbers from 1 to 9
such that each row, column, and both diagonals all have the same sum.

Given a row x col grid of integers, how many 3 x 3 contiguous magic square subgrids are there?

Note: while a magic square can only contain numbers from 1 to 9, grid may contain numbers up to 15.

Example 1:
4 3 8 4
9 5 1 9
2 7 6 2
Input: grid = [[4,3,8,4],[9,5,1,9],[2,7,6,2]]
Output: 1
Explanation:
The following subgrid is a 3 x 3 magic square:
4 3 8
9 5 1
2 7 6
while this one is not:
3 8 4
5 1 9
7 6 2
In total, there is only one magic square inside the given grid.

Example 2:
Input: grid = [[8]]
Output: 0

Constraints:
row == grid.length
col == grid[i].length
1 <= row, col <= 10
0 <= grid[i][j] <= 15
```

</details>

<details><summary>C</summary>

```c
int isMagicSquare(int** grid, int row, int col) {
    int retVal = 0;

    int seen[10];  // while a magic square can only contain numbers from 1 to 9
    memset(seen, 0, sizeof(seen));

    int x, y, num;
    for (x = 0; x < 3; ++x) {
        for (y = 0; y < 3; ++y) {
            num = grid[row + x][col + y];
            if ((num < 1) || (num > 9)) {
                return retVal;
            } else if (seen[num] != 0) {
                return retVal;
            }
            seen[num] = 1;
        }
    }

    int diagonal1 = grid[row][col] + grid[row + 1][col + 1] + grid[row + 2][col + 2];
    int diagonal2 = grid[row + 2][col] + grid[row + 1][col + 1] + grid[row][col + 2];
    if (diagonal1 != diagonal2) {
        return retVal;
    }

    int row1 = grid[row][col] + grid[row][col + 1] + grid[row][col + 2];
    int row2 = grid[row + 1][col] + grid[row + 1][col + 1] + grid[row + 1][col + 2];
    int row3 = grid[row + 2][col] + grid[row + 2][col + 1] + grid[row + 2][col + 2];
    if ((row1 != diagonal1) || (row2 != diagonal1) || (row3 != diagonal1)) {
        return retVal;
    }

    int col1 = grid[row][col] + grid[row + 1][col] + grid[row + 2][col];
    int col2 = grid[row][col + 1] + grid[row + 1][col + 1] + grid[row + 2][col + 1];
    int col3 = grid[row][col + 2] + grid[row + 1][col + 2] + grid[row + 2][col + 2];
    if ((col1 != diagonal1) || (col2 != diagonal1) || (col3 != diagonal1)) {
        return retVal;
    }

    retVal = 1;

    return retVal;
}
int numMagicSquaresInside(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int rowSize = gridSize;
    int colSize = gridColSize[0];  // 1 <= row, col <= 10
    if ((rowSize < 3) || (colSize < 3)) {
        return retVal;
    }

    int x, y;
    for (x = 0; x < rowSize - 2; ++x) {
        for (y = 0; y < colSize - 2; ++y) {
            retVal += isMagicSquare(grid, x, y);
        }
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    int isMagicSquare(vector<vector<int>>& grid, int row, int col) {
        int retVal = 0;

        vector<int> seen(10, 0);  // while a magic square can only contain numbers from 1 to 9
        for (int x = 0; x < 3; ++x) {
            for (int y = 0; y < 3; ++y) {
                int num = grid[row + x][col + y];
                if ((num < 1) || (num > 9)) {
                    return retVal;
                } else if (seen[num] != 0) {
                    return retVal;
                }
                seen[num] = 1;
            }
        }

        int diagonal1 = grid[row][col] + grid[row + 1][col + 1] + grid[row + 2][col + 2];
        int diagonal2 = grid[row + 2][col] + grid[row + 1][col + 1] + grid[row][col + 2];
        if (diagonal1 != diagonal2) {
            return retVal;
        }

        int row1 = grid[row][col] + grid[row][col + 1] + grid[row][col + 2];
        int row2 = grid[row + 1][col] + grid[row + 1][col + 1] + grid[row + 1][col + 2];
        int row3 = grid[row + 2][col] + grid[row + 2][col + 1] + grid[row + 2][col + 2];
        if ((row1 != diagonal1) || (row2 != diagonal1) || (row3 != diagonal1)) {
            return retVal;
        }

        int col1 = grid[row][col] + grid[row + 1][col] + grid[row + 2][col];
        int col2 = grid[row][col + 1] + grid[row + 1][col + 1] + grid[row + 2][col + 1];
        int col3 = grid[row][col + 2] + grid[row + 1][col + 2] + grid[row + 2][col + 2];
        if ((col1 != diagonal1) || (col2 != diagonal1) || (col3 != diagonal1)) {
            return retVal;
        }

        retVal = 1;

        return retVal;
    }

   public:
    int numMagicSquaresInside(vector<vector<int>>& grid) {
        int retVal = 0;

        int rowSize = grid.size();
        int colSize = grid[0].size();  // 1 <= row, col <= 10
        if ((rowSize < 3) || (colSize < 3)) {
            return retVal;
        }

        for (int x = 0; x < rowSize - 2; ++x) {
            for (int y = 0; y < colSize - 2; ++y) {
                retVal += isMagicSquare(grid, x, y);
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
    def isMagicSquare(self, grid: List[List[int]], row: int, col: int) -> int:
        retVal = 0

        # while a magic square can only contain numbers from 1 to 9
        seen = [0] * 10
        for x in range(3):
            for y in range(3):
                num = grid[row+x][col+y]
                if (num < 1) or (num > 9):
                    return retVal
                elif seen[num]:
                    return retVal

                seen[num] = 1

        diagonal1 = grid[row][col] + grid[row+1][col+1] + grid[row+2][col+2]
        diagonal2 = grid[row+2][col] + grid[row+1][col+1] + grid[row][col+2]
        if diagonal1 != diagonal2:
            return retVal

        row1 = grid[row][col] + grid[row][col+1] + grid[row][col+2]
        row2 = grid[row+1][col] + grid[row+1][col+1] + grid[row+1][col+2]
        row3 = grid[row+2][col] + grid[row+2][col+1] + grid[row+2][col+2]
        if (row1 != diagonal1) or (row2 != diagonal1) or (row3 != diagonal1):
            return retVal

        col1 = grid[row][col] + grid[row+1][col] + grid[row+2][col]
        col2 = grid[row][col+1] + grid[row+1][col+1] + grid[row+2][col+1]
        col3 = grid[row][col+2] + grid[row+1][col+2] + grid[row+2][col+2]
        if (col1 != diagonal1) or (col2 != diagonal1) or (col3 != diagonal1):
            return retVal

        retVal = 1

        return retVal

    def numMagicSquaresInside(self, grid: List[List[int]]) -> int:
        retVal = 0

        rowSize = len(grid)
        colSize = len(grid[0])  # 1 <= row, col <= 10
        if (rowSize < 3) or (colSize < 3):
            return retVal

        for x in range(rowSize-2):
            for y in range(colSize-2):
                retVal += self.isMagicSquare(grid, x, y)

        return retVal
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
