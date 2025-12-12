# Sorting

## [56. Merge Intervals](https://leetcode.com/problems/merge-intervals/)

- [Official](https://leetcode.cn/problems/merge-intervals/solutions/203562/he-bing-qu-jian-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals,
and return an array of the non-overlapping intervals that cover all the intervals in the input.

Example 1:
Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].

Example 2:
Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.

Constraints:
1 <= intervals.length <= 10^4
intervals[i].length == 2
0 <= starti <= endi <= 10^4
```

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
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int**)malloc(intervalsSize * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    qsort(intervals, intervalsSize, sizeof(int*), compareIntArray);

    pRetVal[(*returnSize)] = (int*)malloc(intervalsColSize[(*returnSize)] * sizeof(int));
    if (pRetVal[(*returnSize)] == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal[(*returnSize)], 0, (intervalsColSize[(*returnSize)] * sizeof(int)));
    memcpy(pRetVal[(*returnSize)], intervals[(*returnSize)], (intervalsColSize[(*returnSize)] * sizeof(int)));
    (*returnSize)++;

    int i;
    for (i = 1; i < intervalsSize; ++i) {
        if (pRetVal[(*returnSize) - 1][1] >= intervals[i][0]) {
            pRetVal[(*returnSize) - 1][1] = fmax(pRetVal[(*returnSize) - 1][1], intervals[i][1]);
        } else {
            pRetVal[(*returnSize)] = (int*)malloc(intervalsColSize[(*returnSize)] * sizeof(int));
            if (pRetVal[(*returnSize)] == NULL) {
                perror("malloc");
                return pRetVal;
            }
            memset(pRetVal[(*returnSize)], 0, (intervalsColSize[(*returnSize)] * sizeof(int)));
            memcpy(pRetVal[(*returnSize)], intervals[i], (intervalsColSize[(*returnSize)] * sizeof(int)));
            (*returnSize)++;
        }
    }

    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, ((*returnSize) * sizeof(int)));
    for (i = 0; i < (*returnSize); ++i) {
        (*returnColumnSizes)[i] = intervalsColSize[0];
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> retVal;

        sort(intervals.begin(), intervals.end(), [&](const vector<int>& x, const vector<int>& y) {
            // ascending order
            if (x[0] == y[0]) {
                return (x[1] < y[1]);
            }
            return (x[0] < y[0]);
        });

        int intervalsSize = intervals.size();
        retVal.emplace_back(intervals[0]);
        for (int i = 1; i < intervalsSize; ++i) {
            if (retVal.back()[1] >= intervals[i][0]) {
                retVal.back()[1] = max(retVal.back()[1], intervals[i][1]);
            } else {
                retVal.emplace_back(intervals[i]);
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
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        retVal = []

        intervals.sort(key=lambda intervals: intervals[0])

        intervalsSize = len(intervals)
        retVal.append(intervals[0])
        for i in range(1, intervalsSize):
            if retVal[-1][1] >= intervals[i][0]:
                retVal[-1][1] = max(retVal[-1][1], intervals[i][1])
            else:
                retVal.append(intervals[i])

        return retVal
```

</details>

## [75. Sort Colors](https://leetcode.com/problems/sort-colors/)

- [Official](https://leetcode.cn/problems/sort-colors/solutions/437968/yan-se-fen-lei-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given an array nums with n objects colored red, white, or blue,
sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white, and blue.

We will use the integers 0, 1, and 2 to represent the color red, white, and blue, respectively.

You must solve this problem without using the library's sort function.

Example 1:
Input: nums = [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]

Example 2:
Input: nums = [2,0,1]
Output: [0,1,2]

Constraints:
n == nums.length
1 <= n <= 300
nums[i] is either 0, 1, or 2.

Follow up: Could you come up with a one-pass algorithm using only constant extra space?
```

<details><summary>Hint</summary>

```text
1. A rather straight forward solution is a two-pass algorithm using counting sort.
2. Iterate the array counting number of 0's, 1's, and 2's.
3. Overwrite array with the total number of 0's, then 1's and followed by 2's.
```

</details>

</details>

<details><summary>C</summary>

```c
void swap(int* n1, int* n2) {
    int tmp = (*n1);
    (*n1) = (*n2);
    (*n2) = tmp;
}
void sortColors(int* nums, int numsSize) {
    int ptr = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] == 0) {
            swap(&nums[i], &nums[ptr]);
            ptr++;
        }
    }
    for (i = ptr; i < numsSize; ++i) {
        if (nums[i] == 1) {
            swap(&nums[i], &nums[ptr]);
            ptr++;
        }
    }
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    void swap(int* n1, int* n2) {
        int tmp = (*n1);
        (*n1) = (*n2);
        (*n2) = tmp;
    }

   public:
    void sortColors(vector<int>& nums) {
        int numsSize = nums.size();
        int ptr = 0;
        for (int i = 0; i < numsSize; ++i) {
            if (nums[i] == 0) {
                swap(&nums[i], &nums[ptr]);
                ptr++;
            }
        }
        for (int i = ptr; i < numsSize; ++i) {
            if (nums[i] == 1) {
                swap(&nums[i], &nums[ptr]);
                ptr++;
            }
        }
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def sortColors(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        numsSize = len(nums)
        ptr = 0
        for i in range(numsSize):
            if nums[i] == 0:
                nums[i], nums[ptr] = nums[ptr], nums[i]
                ptr += 1
        for i in range(ptr, numsSize):
            if nums[i] == 1:
                nums[i], nums[ptr] = nums[ptr], nums[i]
                ptr += 1
```

</details>

## [88. Merge Sorted Array](https://leetcode.com/problems/merge-sorted-array/)

- [Official](https://leetcode.cn/problems/merge-sorted-array/solutions/666608/he-bing-liang-ge-you-xu-shu-zu-by-leetco-rrb0/)

<details><summary>Description</summary>

```text
You are given two integer arrays nums1 and nums2, sorted in non-decreasing order, and two integers m and n,
representing the number of elements in nums1 and nums2 respectively.

Merge nums1 and nums2 into a single array sorted in non-decreasing order.

The final sorted array should not be returned by the function, but instead be stored inside the array nums1.
To accommodate this, nums1 has a length of m + n, where the first m elements denote the elements that should be merged,
and the last n elements are set to 0 and should be ignored. nums2 has a length of n.

Example 1:
Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
Output: [1,2,2,3,5,6]
Explanation: The arrays we are merging are [1,2,3] and [2,5,6].
The result of the merge is [1,2,2,3,5,6] with the underlined elements coming from nums1.

Example 2:
Input: nums1 = [1], m = 1, nums2 = [], n = 0
Output: [1]
Explanation: The arrays we are merging are [1] and [].
The result of the merge is [1].

Example 3:
Input: nums1 = [0], m = 0, nums2 = [1], n = 1
Output: [1]
Explanation: The arrays we are merging are [] and [1].
The result of the merge is [1].
Note that because m = 0, there are no elements in nums1. The 0 is only there to ensure the merge result can fit in nums1.

Constraints:
nums1.length == m + n
nums2.length == n
0 <= m, n <= 200
1 <= m + n <= 200
-10^9 <= nums1[i], nums2[j] <= 10^9
```

<details><summary>Hint</summary>

```text
1. You can easily solve this problem if you simply think about two elements at a time rather than two arrays.
   We know that each of the individual arrays is sorted.
   What we don't know is how they will intertwine.
   Can we take a local decision and arrive at an optimal solution?
2. If you simply consider one element each at a time from the two arrays and make a decision and proceed accordingly,
   you will arrive at the optimal solution.
```

</details>

</details>

<details><summary>C</summary>

```c
#define BUILD_IN (0)
#define TWO_POINTERS (1)
#if (BUILD_IN)
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
#elif (TWO_POINTERS)
#endif
void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
    if ((m + n) > nums1Size) {
        return;
    }

#if (BUILD_IN)
    printf("BUILD_IN\n");

    memcpy(nums1 + m, nums2, n * sizeof(int));
    qsort(nums1, m + n, sizeof(int), compareInteger);
#elif (TWO_POINTERS)
    printf("TWO_POINTERS\n");

    int idx = nums1Size - 1;
    int idx1 = m - 1;
    int idx2 = n - 1;
    while ((idx1 >= 0) && (idx2 >= 0)) {
        if (nums1[idx1] > nums2[idx2]) {
            nums1[idx--] = nums1[idx1--];
        } else {
            nums1[idx--] = nums2[idx2--];
        }
    }
    while (idx1 >= 0) {
        nums1[idx--] = nums1[idx1--];
    }
    while (idx2 >= 0) {
        nums1[idx--] = nums2[idx2--];
    }
#endif
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int nums1Size = nums1.size();
        if ((m + n) > nums1Size) {
            return;
        }

        int idx = nums1Size - 1;
        int idx1 = m - 1;
        int idx2 = n - 1;
        while ((idx1 >= 0) && (idx2 >= 0)) {
            if (nums1[idx1] > nums2[idx2]) {
                nums1[idx--] = nums1[idx1--];
            } else {
                nums1[idx--] = nums2[idx2--];
            }
        }
        while (idx1 >= 0) {
            nums1[idx--] = nums1[idx1--];
        }
        while (idx2 >= 0) {
            nums1[idx--] = nums2[idx2--];
        }
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def merge(self, nums1: List[int], m: int, nums2: List[int], n: int) -> None:
        """
        Do not return anything, modify nums1 in-place instead.
        """
        nums1Size = len(nums1)
        if m+n > nums1Size:
            return

        idx = nums1Size - 1
        idx1 = m - 1
        idx2 = n - 1
        while ((idx1 >= 0) and (idx2 >= 0)):
            if nums1[idx1] > nums2[idx2]:
                nums1[idx] = nums1[idx1]
                idx -= 1
                idx1 -= 1
            else:
                nums1[idx] = nums2[idx2]
                idx -= 1
                idx2 -= 1

        while (idx1 >= 0):
            nums1[idx] = nums1[idx1]
            idx -= 1
            idx1 -= 1

        while (idx2 >= 0):
            nums1[idx] = nums2[idx2]
            idx -= 1
            idx2 -= 1
```

</details>

## [179. Largest Number](https://leetcode.com/problems/largest-number/)

- [Official](https://leetcode.com/problems/largest-number/editorial/)
- [Official](https://leetcode.cn/problems/largest-number/solutions/715680/zui-da-shu-by-leetcode-solution-sid5/)

<details><summary>Description</summary>

```text
Given a list of non-negative integers nums, arrange them such that they form the largest number and return it.

Since the result may be very large, so you need to return a string instead of an integer.

Example 1:
Input: nums = [10,2]
Output: "210"

Example 2:
Input: nums = [3,30,34,5,9]
Output: "9534330"

Constraints:
1 <= nums.length <= 100
0 <= nums[i] <= 10^9
```

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    /* Example
     *  43243 432
     *  43243: 43243000 +   432 = 43243432
     *    432: 43200000 + 43243 = 43243243
     *
     *  432 43200
     *    432: 43200000 + 43200 = 43243200
     *  43200: 43200000 +   432 = 43200432
     */
    double digits1 = 10;
    while (digits1 <= *(int*)n1) {
        digits1 *= 10;
    }
    double digits2 = 10;
    while (digits2 <= *(int*)n2) {
        digits2 *= 10;
    }
    double comp1 = (*(int*)n2) * digits1 + (*(int*)n1);
    double comp2 = (*(int*)n1) * digits2 + (*(int*)n2);

    return (comp1 > comp2);
}
char* largestNumber(int* nums, int numsSize) {
    char* pRetVal = NULL;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    // Input: nums = [0, 0], Output: "0".
    if (nums[0] == 0) {
        pRetVal = (char*)calloc(2, sizeof(char));
        if (pRetVal == NULL) {
            perror("calloc");
            return pRetVal;
        }
        pRetVal[0] = '0';

        return pRetVal;
    }

    // 0 <= nums[i] <= 10^9.
    int returnSize = numsSize * 10 + 1;
    pRetVal = (char*)calloc(returnSize, sizeof(char));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }

    int idx = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        idx += snprintf(pRetVal + idx, returnSize - idx, "%d", nums[i]);
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string largestNumber(vector<int> &nums) {
        string retVal;

        vector<string> numStrings;
        for (int num : nums) {
            numStrings.push_back(to_string(num));
        }
        sort(numStrings.begin(), numStrings.end(), [](string &a, string &b) {
            //
            return a + b > b + a;
        });

        if (numStrings[0] == "0") {
            retVal = "0";
        } else {
            retVal = "";
            for (string &numStr : numStrings) {
                retVal += numStr;
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
    def largestNumber(self, nums: List[int]) -> str:
        retVal = ""

        numsStrings = []
        for num in nums:
            numsStrings.append(str(num))
        numsStrings.sort(key=lambda a: a * 10, reverse=True)

        if numsStrings[0] == "0":
            retVal = "0"
        else:
            retVal = "".join(numsStrings)

        return retVal
```

</details>

## [252. Meeting Rooms](https://leetcode.com/problems/meeting-rooms/)  unlock

- Subscribe to unlock
  - Google
  - Amazon
  - Bloomberg
- [252. Meeting Rooms](https://leetcode.ca/2016-08-08-252-Meeting-Rooms/)

<details><summary>Description</summary>

```text
Given an array of meeting time intervals where intervals[i] = [starti, endi], determine if a person could attend all meetings.

Example 1:
Input: intervals = [[0,30],[5,10],[15,20]]
Output: false

Example 2:
Input: intervals = [[7,10],[2,4]]
Output: true

Constraints:
0 <= intervals.length <= 10^4
intervals[i].length == 2
0 <= starti < endi <= 10^6
```

</details>

<details><summary>C</summary>

```c
int compareIntArray(const void* a1, const void* a2) {
    const int* p1 = *(const int**)a1;
    const int* p2 = *(const int**)a2;

    // ascending order by Array[][0]
    return ((p1[0] > p2[0]) ? (1) : (-1));
}
bool canAttendMeetings(int** intervals, int intervalsSize, int* intervalsColSize) {
    bool retVal = true;

    qsort(intervals, intervalsSize, sizeof(intervals[0]), compareIntArray);

    int i;
    for (i = 1; i < intervalsSize; ++i) {
        if (intervals[i - 1][1] > intervals[i][0]) {
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
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        bool retVal = true;

#if (1)  // C++ sort function automatically sorts a vector first by the 1st element, then by the 2nd element and so on.
        sort(intervals.begin(), intervals.end());
#else
        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });
#endif

        for (long unsigned int i = 1; i < intervals.size(); ++i) {
            if (intervals[i - 1][1] > intervals[i][0]) {
                retVal = false;
                break;
            }
        }

        return retVal;
    }
};
```

</details>

## [414. Third Maximum Number](https://leetcode.com/problems/third-maximum-number/)

<details><summary>Description</summary>

```text
Given an integer array nums, return the third distinct maximum number in this array.
If the third maximum does not exist, return the maximum number.

Example 1:
Input: nums = [3,2,1]
Output: 1
Explanation:
The first distinct maximum is 3.
The second distinct maximum is 2.
The third distinct maximum is 1.

Example 2:
Input: nums = [1,2]
Output: 2
Explanation:
The first distinct maximum is 2.
The second distinct maximum is 1.
The third distinct maximum does not exist, so the maximum (2) is returned instead.

Example 3:
Input: nums = [2,2,3,1]
Output: 1
Explanation:
The first distinct maximum is 3.
The second distinct maximum is 2 (both 2's are counted together since they have the same value).
The third distinct maximum is 1.

Constraints:
1 <= nums.length <= 10^4
-2^31 <= nums[i] <= 2^31 - 1

Follow up: Can you find an O(n) solution?
```

</details>

<details><summary>C</summary>

```c
#define LONG_METHOD 1
#define SORT_METHOD 1
#if (LONG_METHOD)
#elif (SORT_METHOD)
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
#endif
int thirdMax(int* nums, int numsSize) {
    int retVal;

#if (LONG_METHOD)
    long first = nums[0];
    long second = LONG_MIN;
    long third = LONG_MIN;

    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[i] <= third) {
            continue;
        } else if (nums[i] < second) {
            third = nums[i];
            continue;
        } else if (nums[i] == second) {
            continue;
        } else if (nums[i] < first) {
            third = second;
            second = nums[i];
            continue;
        } else if (nums[i] == first) {
            continue;
        }

        third = second;
        second = first;
        first = nums[i];
    }
    retVal = (third != LONG_MIN) ? third : first;
#elif (SORT_METHOD)
    qsort(nums, numsSize, sizeof(int), compareInteger);
#define MAX_NUMBER 3
    retVal = nums[0];
    int count = 1;
    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[i - 1] != nums[i]) {
            ++count;
        }

        if (count == MAX_NUMBER) {
            retVal = nums[i];
            break;
        }
    }
#endif

    return retVal;
}
```

</details>

## [506. Relative Ranks](https://leetcode.com/problems/relative-ranks/)

- [Official](https://leetcode.com/problems/relative-ranks/editorial/)
- [Official](https://leetcode.cn/problems/relative-ranks/solutions/1131693/xiang-dui-ming-ci-by-leetcode-solution-5sua/)

<details><summary>Description</summary>

```text
You are given an integer array score of size n, where score[i] is the score of the ith athlete in a competition.
All the scores are guaranteed to be unique.

The athletes are placed based on their scores, where the 1st place athlete has the highest score,
the 2nd place athlete has the 2nd highest score, and so on.
The placement of each athlete determines their rank:
- The 1st place athlete's rank is "Gold Medal".
- The 2nd place athlete's rank is "Silver Medal".
- The 3rd place athlete's rank is "Bronze Medal".
- For the 4th place to the nth place athlete, their rank is their placement number
  (i.e., the xth place athlete's rank is "x").

Return an array answer of size n where answer[i] is the rank of the ith athlete.

Example 1:
Input: score = [5,4,3,2,1]
Output: ["Gold Medal","Silver Medal","Bronze Medal","4","5"]
Explanation: The placements are [1st, 2nd, 3rd, 4th, 5th].

Example 2:
Input: score = [10,3,8,9,4]
Output: ["Gold Medal","5","Bronze Medal","Silver Medal","4"]
Explanation: The placements are [1st, 5th, 3rd, 2nd, 4th].

Constraints:
n == score.length
1 <= n <= 10^4
0 <= score[i] <= 10^6
All the values in score are unique.
```

</details>

<details><summary>C</summary>

```c
int compareIntArray(const void *a1, const void *a2) {
    int *p1 = (int *)a1;
    int *p2 = (int *)a2;

    // descending order
    if (p1[1] == p2[1]) {
        return (p1[1] < p2[1]);
    }

    return (p1[1] < p2[1]);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **findRelativeRanks(int *score, int scoreSize, int *returnSize) {
    char **pRetVal = NULL;

    (*returnSize) = 0;

    int sortScore[scoreSize][2];
    memset(sortScore, 0, sizeof(sortScore));
    int i;
    for (i = 0; i < scoreSize; ++i) {
        sortScore[i][0] = i;
        sortScore[i][1] = score[i];
    }
    qsort(sortScore, scoreSize, sizeof(sortScore[0]), compareIntArray);

#define MAX_RETURN_COL_SIZE (16)
    pRetVal = (char **)malloc(scoreSize * sizeof(char *));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    for (i = 0; i < scoreSize; ++i) {
        pRetVal[i] = (char *)malloc(MAX_RETURN_COL_SIZE * sizeof(char));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            for (int j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        memset(pRetVal[(*returnSize)], 0, (MAX_RETURN_COL_SIZE * sizeof(char)));
    }
    (*returnSize) = scoreSize;

    for (i = 0; i < scoreSize; ++i) {
        if (i == 0) {
            snprintf(pRetVal[sortScore[i][0]], MAX_RETURN_COL_SIZE, "%s", "Gold Medal");
        } else if (i == 1) {
            snprintf(pRetVal[sortScore[i][0]], MAX_RETURN_COL_SIZE, "%s", "Silver Medal");
        } else if (i == 2) {
            snprintf(pRetVal[sortScore[i][0]], MAX_RETURN_COL_SIZE, "%s", "Bronze Medal");
        } else {
            snprintf(pRetVal[sortScore[i][0]], MAX_RETURN_COL_SIZE, "%d", i + 1);
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
    vector<string> findRelativeRanks(vector<int>& score) {
        vector<string> retVal;

        int scoreSize = score.size();
        vector<pair<int, int>> sortScore;
        for (int i = 0; i < scoreSize; ++i) {
            sortScore.emplace_back(i, score[i]);
        }
        sort(sortScore.begin(), sortScore.end(), [&](auto x1, auto x2) {
            // descending order
            return x1.second > x2.second;
        });

        retVal.resize(scoreSize);
        for (int i = 0; i < scoreSize; ++i) {
            if (i == 0) {
                retVal[sortScore[i].first] = "Gold Medal";
            } else if (i == 1) {
                retVal[sortScore[i].first] = "Silver Medal";
            } else if (i == 2) {
                retVal[sortScore[i].first] = "Bronze Medal";
            } else {
                retVal[sortScore[i].first] = to_string(i + 1);
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
    def findRelativeRanks(self, score: List[int]) -> List[str]:
        retVal = []

        sortScore = sorted(enumerate(score), key=lambda x: x[1], reverse=True)

        scoreSize = len(score)
        retVal = [""] * scoreSize
        for i in range(scoreSize):
            if i == 0:
                retVal[sortScore[i][0]] = "Gold Medal"
            elif i == 1:
                retVal[sortScore[i][0]] = "Silver Medal"
            elif i == 2:
                retVal[sortScore[i][0]] = "Bronze Medal"
            else:
                retVal[sortScore[i][0]] = str(i+1)

        return retVal
```

</details>

## [539. Minimum Time Difference](https://leetcode.com/problems/minimum-time-difference/)

- [Official](https://leetcode.com/problems/minimum-time-difference/editorial/)
- [Official](https://leetcode.cn/problems/minimum-time-difference/solutions/1216027/zui-xiao-shi-jian-chai-by-leetcode-solut-xolj/)

<details><summary>Description</summary>

```text
Given a list of 24-hour clock time points in "HH:MM" format,
return the minimum minutes difference between any two time-points in the list.

Example 1:
Input: timePoints = ["23:59","00:00"]
Output: 1

Example 2:
Input: timePoints = ["00:00","23:59","00:00"]
Output: 0

Constraints:
2 <= timePoints.length <= 2 * 10^4
timePoints[i] is in the format "HH:MM".
```

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int findMinDifference(char** timePoints, int timePointsSize) {
    int retVal = 0;

    int minutesSize = timePointsSize;
    int minutes[minutesSize];
    memset(minutes, 0, sizeof(minutes));

    int i;
    for (i = 0; i < timePointsSize; ++i) {
        minutes[i] += ((10 * (timePoints[i][0] - '0') + timePoints[i][1] - '0') * 60);
        minutes[i] += ((10 * (timePoints[i][3] - '0') + timePoints[i][4] - '0') * 1);
    }
    qsort(minutes, minutesSize, sizeof(int), compareInteger);

    retVal = 24 * 60 - minutes[minutesSize - 1] + minutes[0];
    for (i = 0; i < (minutesSize - 1); ++i) {
        retVal = fmin(retVal, minutes[i + 1] - minutes[i]);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int findMinDifference(vector<string>& timePoints) {
        int retVal = 0;

        vector<int> minutes;
        for (string timePoint : timePoints) {
            int minute = stoi(timePoint.substr(0, 2)) * 60 + stoi(timePoint.substr(3, 5));
            minutes.emplace_back(minute);
        }
        sort(minutes.begin(), minutes.end());

        int minutesSize = minutes.size();
        retVal = 24 * 60 - minutes[minutesSize - 1] + minutes[0];
        for (int i = 0; i < (minutesSize - 1); ++i) {
            retVal = min(retVal, minutes[i + 1] - minutes[i]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def findMinDifference(self, timePoints: List[str]) -> int:
        retVal = 0

        minutes = []
        for timePoint in timePoints:
            minutes.append(int(timePoint[:2]) * 60 + int(timePoint[3:]))
        minutes.sort()

        retVal = 24 * 60 - minutes[-1] + minutes[0]
        minutesSize = len(minutes)
        for i in range(minutesSize - 1):
            retVal = min(retVal, minutes[i + 1] - minutes[i])

        return retVal
```

</details>

## [658. Find K Closest Elements](https://leetcode.com/problems/find-k-closest-elements/)

<details><summary>Description</summary>

```text
Given a sorted integer array arr, two integers k and x, return the k closest integers to x in the array.
The result should also be sorted in ascending order.

An integer a is closer to x than an integer b if:

|a - x| < |b - x|, or
|a - x| == |b - x| and a < b

Example 1:
Input: arr = [1,2,3,4,5], k = 4, x = 3
Output: [1,2,3,4]

Example 2:
Input: arr = [1,2,3,4,5], k = 4, x = -1
Output: [1,2,3,4]

Constraints:
1 <= k <= arr.length
1 <= arr.length <= 10^4
arr is sorted in ascending order.
-10^4 <= arr[i], x <= 10^4
```

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findClosestElements(int* arr, int arrSize, int k, int x, int* returnSize){
    int* pRetVal = NULL;

    *returnSize = k;
    pRetVal = (int*)malloc((*returnSize)*sizeof(int));
    if (pRetVal == NULL)
    {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (*returnSize)*sizeof(int));

    int head = 0;
    int tail = arrSize - 1;
    while ((tail - head) >= k)
    {
        if (abs(arr[head]-x) > abs(arr[tail]-x))
        {
            ++head;
        }
        else
        {
            --tail;
        }
    }
    memcpy(pRetVal, arr+head, k*sizeof(int));

    return pRetVal;
}
```

</details>

## [747. Largest Number At Least Twice of Others](https://leetcode.com/problems/largest-number-at-least-twice-of-others/)  1188

<details><summary>Description</summary>

```text
You are given an integer array nums where the largest integer is unique.

Determine whether the largest element in the array is at least twice as much as every other number in the array.
If it is, return the index of the largest element, or return -1 otherwise.

Example 1:
Input: nums = [3,6,1,0]
Output: 1
Explanation: 6 is the largest integer.
For every other number in the array x, 6 is at least twice as big as x.
The index of value 6 is 1, so we return 1.

Example 2:
Input: nums = [1,2,3,4]
Output: -1
Explanation: 4 is less than twice the value of 3, so we return -1.

Constraints:
2 <= nums.length <= 50
0 <= nums[i] <= 100
The largest element in nums is unique.
```

</details>

<details><summary>C</summary>

```c
int dominantIndex(int* nums, int numsSize){
    int retVal = 0;

    int largest = nums[0];
    int second = 0;
    int i;
    for (i=1; i<numsSize; ++i)
    {
        if (nums[i] > largest)
        {
            second = largest;
            largest = nums[i];
            retVal = i;
            continue;
        }
        second = (second>nums[i])?second:nums[i];
    }

    if (largest < (2*second))
    {
        retVal = -1;
    }

    return retVal;
}
```

</details>

## [791. Custom Sort String](https://leetcode.com/problems/custom-sort-string/)  1423

- [Official](https://leetcode.cn/problems/custom-sort-string/solutions/1963410/zi-ding-yi-zi-fu-chuan-pai-xu-by-leetcod-1qvf/)

<details><summary>Description</summary>

```text
You are given two strings order and s.
All the characters of order are unique and were sorted in some custom order previously.

Permute the characters of s so that they match the order that order was sorted.
More specifically, if a character x occurs before a character y in order,
then x should occur before y in the permuted string.

Return any permutation of s that satisfies this property.

Example 1:
Input:  order = "cba", s = "abcd"
Output:  "cbad"
Explanation: "a", "b", "c" appear in order, so the order of "a", "b", "c" should be "c", "b", and "a".
Since "d" does not appear in order, it can be at any position in the returned string.
"dcba", "cdba", "cbda" are also valid outputs.

Example 2:
Input:  order = "bcafg", s = "abcd"
Output:  "bcad"
Explanation: The characters "b", "c", and "a" from order dictate the order for the characters in s.
The character "d" in s does not appear in order, so its position is flexible.
Following the order of appearance in order, "b", "c", and "a" from s
should be arranged as "b", "c", "a". "d" can be placed at any position since it's not in order.
The output "bcad" correctly follows this rule.
Other arrangements like "bacd" or "bcda" would also be valid, as long as "b", "c", "a" maintain their order.

Constraints:
1 <= order.length <= 26
1 <= s.length <= 200
order and s consist of lowercase English letters.
All the characters of order are unique.
```

</details>

<details><summary>C</summary>

```c
#define MAX_VAL_SIZE (26)  // 1 <= order.length <= 26
int val[MAX_VAL_SIZE];
int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (val[*(char*)n1 - 'a'] < val[*(char*)n2 - 'a']);
}
char* customSortString(char* order, char* s) {
    char* pRetVal = NULL;

    memset(val, 0, sizeof(val));

    int orderSize = strlen(order);
    int idx;
    int i;
    for (i = 0; i < orderSize; ++i) {
        idx = order[i] - 'a';
        val[idx] = MAX_VAL_SIZE - i;
    }

    int sSize = strlen(s);
    qsort(s, sSize, sizeof(char), compareInteger);
    pRetVal = s;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    int valSize = 26;  // 1 <= order.length <= 26

   public:
    string customSortString(string order, string s) {
        string retVal;

        int orderSize = order.size();
        vector<int> val(valSize, 0);
        for (int i = 0; i < orderSize; ++i) {
            int idx = order[i] - 'a';
            val[idx] = valSize - i;
        }

        sort(s.begin(), s.end(), [&](char c0, char c1) {
            // descending order
            return val[c0 - 'a'] > val[c1 - 'a'];
        });
        retVal = s;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def customSortString(self, order: str, s: str) -> str:
        retVal = ""

        val = defaultdict(int)
        for i, ch in enumerate(order):
            val[ch] = 26 - i    # 1 <= order.length <= 26
        retVal = "".join(sorted(s, key=lambda ch: val[ch], reverse=True))

        return retVal
```

</details>

## [853. Car Fleet](https://leetcode.com/problems/car-fleet/)  1678

- [Official](https://leetcode.cn/problems/car-fleet/solutions/20104/che-dui-by-leetcode/)

<details><summary>Description</summary>

```text
There are n cars going to the same destination along a one-lane road. The destination is target miles away.

You are given two integer array position and speed, both of length n,
where position[i] is the position of the ith car and speed[i] is the speed of the ith car (in miles per hour).

A car can never pass another car ahead of it, but it can catch up to it and drive bumper to bumper at the same speed.
The faster car will slow down to match the slower car's speed.
The distance between these two cars is ignored (i.e., they are assumed to have the same position).

A car fleet is some non-empty set of cars driving at the same position and same speed.
Note that a single car is also a car fleet.

If a car catches up to a car fleet right at the destination point, it will still be considered as one car fleet.

Return the number of car fleets that will arrive at the destination.

Example 1:
Input: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
Output: 3
Explanation:
The cars starting at 10 (speed 2) and 8 (speed 4) become a fleet, meeting each other at 12.
The car starting at 0 does not catch up to any other car, so it is a fleet by itself.
The cars starting at 5 (speed 1) and 3 (speed 3) become a fleet, meeting each other at 6.
The fleet moves at speed 1 until it reaches target.
Note that no other cars meet these fleets before the destination, so the answer is 3.

Example 2:
Input: target = 10, position = [3], speed = [3]
Output: 1
Explanation: There is only one car, hence there is only one fleet.

Example 3:
Input: target = 100, position = [0,2,4], speed = [4,2,1]
Output: 1
Explanation:
The cars starting at 0 (speed 4) and 2 (speed 2) become a fleet, meeting each other at 4. The fleet moves at speed 2.
Then, the fleet (speed 2) and the car starting at 4 (speed 1) become one fleet, meeting each other at 6.
The fleet moves at speed 1 until it reaches target.

Constraints:
n == position.length == speed.length
1 <= n <= 10^5
0 < target <= 10^6
0 <= position[i] < target
All the values of position are unique.
0 < speed[i] <= 10^6
```

</details>

<details><summary>C</summary>

```c
// https://leetcode.cn/problems/car-fleet/solutions/1117337/cyu-yan-jian-dan-bian-liang-mei-sha-suan-9lbs/
typedef struct {
    double distance;
    double speed;
    double time;
} CarInfo;
int compareStruct(const void *a1, const void *a2) {
    CarInfo *p1 = (CarInfo *)a1;
    CarInfo *p2 = (CarInfo *)a2;

    // ascending order
    return (p1->distance > p2->distance);
}
int carFleet(int target, int *position, int positionSize, int *speed, int speedSize) {
    int retVal = 0;

    int i;

    CarInfo *pCarInfo = malloc(sizeof(CarInfo) * positionSize);
    if (pCarInfo == NULL) {
        perror("malloc");
        return retVal;
    }
    for (i = 0; i < positionSize; i++) {
        pCarInfo[i].distance = target - position[i];
        pCarInfo[i].speed = speed[i];
        pCarInfo[i].time = pCarInfo[i].distance / pCarInfo[i].speed;
    }
    qsort(pCarInfo, positionSize, sizeof(CarInfo), compareStruct);

    double current = 0;
    for (i = 0; i < positionSize; i++) {
        if (pCarInfo[i].time > current) {
            retVal++;
            current = pCarInfo[i].time;
        }
    }

    free(pCarInfo);
    pCarInfo = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int retVal = 0;

        // https://leetcode.com/problems/car-fleet/solutions/139850/c-java-python-straight-forward/
        map<int, double> time;
        int positionSize = position.size();
        for (int i = 0; i < positionSize; ++i) {
            double value = target - position[i];
            time[-position[i]] = value / speed[i];
        }

        double current = 0;
        for (auto iterator : time) {
            if (iterator.second > current) {
                current = iterator.second;
                ++retVal;
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
    def carFleet(self, target: int, position: List[int], speed: List[int]) -> int:
        retVal = 0

        # // https://leetcode.com/problems/car-fleet/solutions/139850/c-java-python-straight-forward/
        time = [float(target - p) / s for p, s in sorted(zip(position, speed))]

        current = 0
        for t in time[::-1]:
            if t > current:
                retVal += 1
                current = t

        return retVal
```

</details>

## [899. Orderly Queue](https://leetcode.com/problems/orderly-queue/)  2096

- [Official](https://leetcode.com/problems/orderly-queue/solutions/165928/orderly-queue/)
- [Official](https://leetcode.cn/problems/orderly-queue/solutions/1715592/you-xu-dui-lie-by-leetcode-solution-p6gv/)

<details><summary>Description</summary>

```text
You are given a string s and an integer k.
You can choose one of the first k letters of s and append it at the end of the string..

Return the lexicographically smallest string you could have after applying the mentioned step any number of moves.

Example 1:
Input: s = "cba", k = 1
Output: "acb"
Explanation:
In the first move, we move the 1st character 'c' to the end, obtaining the string "bac".
In the second move, we move the 1st character 'b' to the end, obtaining the final result "acb".

Example 2:
Input: s = "baaca", k = 3
Output: "aaabc"
Explanation:
In the first move, we move the 1st character 'b' to the end, obtaining the string "aacab".
In the second move, we move the 3rd character 'c' to the end, obtaining the final result "aaabc".

Constraints:
1 <= k <= s.length <= 1000
s consist of lowercase English letters.
```

</details>

<details><summary>C</summary>

```c
int compareChar(const void* c1, const void* c2) {
    // ascending order
    return (*(char*)c1 - *(char*)c2);
}

char* orderlyQueue(char* s, int k) {
    char* pRetVal = NULL;

    int len = strlen(s);
    int returnSize = (len+1) * sizeof(char);
    pRetVal = (char*)malloc(returnSize);
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, returnSize);
    snprintf(pRetVal, returnSize, "%s", s);

    // k>=2: Bubble Sort Concept? it could get the optimal solution(ascending order)
    if (k > 1) {
        qsort(pRetVal, len, sizeof(char), compareChar);
        return pRetVal;
    }

    // k = 1: rotate the whole string to return the lexicographically smallest string
    char tmp;
    int i;
    for (i=0; i<len; ++i) {
        tmp = s[0];
        memmove(s, &(s[1]), len-1);
        s[len-1] = tmp;
        if (strcmp(pRetVal, s) > 0) {
            memset(pRetVal, 0, returnSize);
            snprintf(pRetVal, returnSize, "%s", s);
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
    string orderlyQueue(string s, int k) {
        string retVal = s;

        // k>=2: Bubble Sort Concept? it could get the optimal solution(ascending order)
        if (k > 1) {
            sort(retVal.begin(), retVal.end());
            return retVal;
        }

        // k = 1: rotate the whole string to return the lexicographically smallest string
        for (long unsigned int i=1; i<s.length(); ++i) {
            retVal = min(retVal, s.substr(i)+s.substr(0, i));
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def orderlyQueue(self, s: str, k: int) -> str:
        if k == 1:
            return min(s[i:] + s[:i] for i in range(len(s)))
        else:
            return ''.join(sorted(s))
```

</details>

## [912. Sort an Array](https://leetcode.com/problems/sort-an-array/)

- [Official](https://leetcode.cn/problems/sort-an-array/solutions/178305/pai-xu-shu-zu-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given an array of integers nums, sort the array in ascending order and return it.

You must solve the problem without using any built-in functions in O(nlog(n)) time complexity
and with the smallest space complexity possible.

Example 1:
Input: nums = [5,2,3,1]
Output: [1,2,3,5]
Explanation:
After sorting the array, the positions of some numbers are not changed (for example, 2 and 3),
while the positions of other numbers are changed (for example, 1 and 5).

Example 2:
Input: nums = [5,1,1,2,0,0]
Output: [0,0,1,1,2,5]
Explanation: Note that the values of nums are not necessairly unique.

Constraints:
1 <= nums.length <= 5 * 10^4
-5 * 10^4 <= nums[i] <= 5 * 10^4
```

</details>

<details><summary>C</summary>

```c
void merge(int* nums, int left, int middle, int right) {
    // copy left subarray
    int leftIdx = 0;
    int leftSize = middle - left + 1;
    int leftTmp[leftSize];
    memset(leftTmp, 0, sizeof(leftTmp));
    memcpy(leftTmp, &nums[left], sizeof(leftTmp));

    // copy right subarray
    int rightIdx = 0;
    int rightSize = right - middle;
    int rightTmp[rightSize];
    memset(rightTmp, 0, sizeof(rightTmp));
    memcpy(rightTmp, &nums[middle + 1], sizeof(rightTmp));

    // merge left and right subarray in ascending order
    int mergeIdx = left;
    while ((leftIdx < leftSize) && (rightIdx < rightSize)) {
        if (leftTmp[leftIdx] <= rightTmp[rightIdx]) {
            nums[mergeIdx++] = leftTmp[leftIdx++];
        } else {
            nums[mergeIdx++] = rightTmp[rightIdx++];
        }
    }

    // merge remaining left subarray
    while (leftIdx < leftSize) {
        nums[mergeIdx++] = leftTmp[leftIdx++];
    }

    // merge remaining right subarray
    while (rightIdx < rightSize) {
        nums[mergeIdx++] = rightTmp[rightIdx++];
    }
}
void mergeSort(int* nums, int left, int right) {
    if (left >= right) {
        return;
    }

    int middle = left + (right - left) / 2;
    mergeSort(nums, left, middle);
    mergeSort(nums, middle + 1, right);
    merge(nums, left, middle, right);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortArray(int* nums, int numsSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int*)malloc(numsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (numsSize * sizeof(int)));
    memcpy(pRetVal, nums, (numsSize * sizeof(int)));
    (*returnSize) = numsSize;

    mergeSort(pRetVal, 0, numsSize - 1);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    void merge(vector<int>& nums, int left, int right) {
        int middle = (left + right) / 2;
        int len1 = middle - left + 1;
        int len2 = right - middle;

        vector<int> first(len1);
        vector<int> second(len2);
        int idx;

        // copy elements
        idx = left;
        for (int i = 0; i < len1; i++) {
            first[i] = nums[idx++];
        }
        for (int i = 0; i < len2; i++) {
            second[i] = nums[idx++];
        }

        // merge 2 sorted array
        int index1 = 0;
        int index2 = 0;
        idx = left;
        while ((index1 < len1) && (index2 < len2)) {
            if (first[index1] < second[index2]) {
                nums[idx++] = first[index1++];
            } else {
                nums[idx++] = second[index2++];
            }
        }
        while (index1 < len1) {
            nums[idx++] = first[index1++];
        }
        while (index2 < len2) {
            nums[idx++] = second[index2++];
        }
    }
    void mergeSort(vector<int>& nums, int left, int right) {
        if (left >= right) {
            return;
        }
        int middle = (left + right) / 2;
        mergeSort(nums, left, middle);
        mergeSort(nums, middle + 1, right);
        merge(nums, left, right);
    }
    vector<int> sortArray(vector<int>& nums) {
        vector<int> retVal;

        retVal.assign(nums.begin(), nums.end());
        mergeSort(retVal, 0, retVal.size() - 1);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def mergeSort(self, nums: List[int], left: int, right: int) -> None:
        if left == right:
            return

        middle = (left + right) // 2
        self.mergeSort(nums, left, middle)
        self.mergeSort(nums, middle + 1, right)

        tmp = []
        i = left
        j = middle + 1
        while (i <= middle) or (j <= right):
            if (i > middle) or ((j <= right) and (nums[j] < nums[i])):
                tmp.append(nums[j])
                j += 1
            else:
                tmp.append(nums[i])
                i += 1
        nums[left: right + 1] = tmp

    def sortArray(self, nums: List[int]) -> List[int]:
        retVal = nums

        self.mergeSort(retVal, 0, len(retVal) - 1)

        return retVal
```

</details>

## [945. Minimum Increment to Make Array Unique](https://leetcode.com/problems/minimum-increment-to-make-array-unique/)  1448

- [Official](https://leetcode.com/problems/minimum-increment-to-make-array-unique/editorial/)
- [Official](https://leetcode.cn/problems/minimum-increment-to-make-array-unique/solutions/162346/shi-shu-zu-wei-yi-de-zui-xiao-zeng-liang-by-leet-2/)

<details><summary>Description</summary>

```text
You are given an integer array nums.
In one move, you can pick an index i where 0 <= i < nums.length and increment nums[i] by 1.

Return the minimum number of moves to make every value in nums unique.

The test cases are generated so that the answer fits in a 32-bit integer.

Example 1:
Input: nums = [1,2,2]
Output: 1
Explanation: After 1 move, the array could be [1, 2, 3].

Example 2:
Input: nums = [3,2,1,2,1,7]
Output: 6
Explanation: After 6 moves, the array could be [3, 4, 1, 2, 5, 7].
It can be shown with 5 or less moves that it is impossible for the array to have all unique values.

Constraints:
1 <= nums.length <= 10^5
0 <= nums[i] <= 10^5
```

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int minIncrementForUnique(int* nums, int numsSize) {
    int retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int increment;
    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[i] <= nums[i - 1]) {
            increment = nums[i - 1] + 1 - nums[i];
            retVal += increment;
            nums[i] = nums[i - 1] + 1;
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
    int minIncrementForUnique(vector<int>& nums) {
        int retVal = 0;

        sort(nums.begin(), nums.end());

        int numsSize = nums.size();
        for (int i = 1; i < numsSize; ++i) {
            if (nums[i] <= nums[i - 1]) {
                int increment = nums[i - 1] + 1 - nums[i];
                retVal += increment;
                nums[i] = nums[i - 1] + 1;
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
    def minIncrementForUnique(self, nums: List[int]) -> int:
        retVal = 0

        nums.sort()

        numsSize = len(nums)
        for i in range(1, numsSize):
            if nums[i] <= nums[i - 1]:
                increment = nums[i - 1] + 1 - nums[i]
                retVal += increment
                nums[i] = nums[i - 1] + 1

        return retVal
```

</details>

## [976. Largest Perimeter Triangle](https://leetcode.com/problems/largest-perimeter-triangle/)  1340

- [Official](https://leetcode.com/problems/largest-perimeter-triangle/editorial/)
- [Official](https://leetcode.cn/problems/largest-perimeter-triangle/solutions/501924/san-jiao-xing-de-zui-da-zhou-chang-by-leetcode-sol/)

<details><summary>Description</summary>

```text
Given an integer array nums, return the largest perimeter of a triangle with a non-zero area,
formed from three of these lengths.
If it is impossible to form any triangle of a non-zero area, return 0.

Example 1:
Input: nums = [2,1,2]
Output: 5

Example 2:
Input: nums = [1,2,1]
Output: 0

Constraints:
3 <= nums.length <= 10^4
1 <= nums[i] <= 10^6
```

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
int largestPerimeter(int* nums, int numsSize) {
    int retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);
    int i;
    for (i = 0; i < (numsSize - 2); ++i) {
        if (nums[i] < (nums[i + 1] + nums[i + 2])) {
            retVal = nums[i] + nums[i + 1] + nums[i + 2];
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
    int largestPerimeter(vector<int>& nums) {
        int retVal = 0;

        sort(nums.begin(), nums.end(), greater<int>());  // descending order
        for (long unsigned int i = 0; i < nums.size() - 2; ++i) {
            if (nums[i] < (nums[i + 1] + nums[i + 2])) {
                retVal = nums[i] + nums[i + 1] + nums[i + 2];
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
    def largestPerimeter(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)
        nums.sort(reverse=True)
        for i in range(numsSize-2):
            if nums[i] < (nums[i + 1] + nums[i + 2]):
                retVal = nums[i] + nums[i + 1] + nums[i + 2]
                break

        return retVal
```

</details>

## [1030. Matrix Cells in Distance Order](https://leetcode.com/problems/matrix-cells-in-distance-order/)  1585

- [Official](https://leetcode.cn/problems/matrix-cells-in-distance-order/solutions/487123/ju-chi-shun-xu-pai-lie-ju-zhen-dan-yuan-ge-by-leet/)

<details><summary>Description</summary>

```text
You are given four integers row, cols, rCenter, and cCenter.
There is a rows x cols matrix and you are on the cell with the coordinates (rCenter, cCenter).

Return the coordinates of all cells in the matrix,
sorted by their distance from (rCenter, cCenter) from the smallest distance to the largest distance.
You may return the answer in any order that satisfies this condition.

The distance between two cells (r1, c1) and (r2, c2) is |r1 - r2| + |c1 - c2|.

Example 1:
Input: rows = 1, cols = 2, rCenter = 0, cCenter = 0
Output: [[0,0],[0,1]]
Explanation: The distances from (0, 0) to other cells are: [0,1]

Example 2:
Input: rows = 2, cols = 2, rCenter = 0, cCenter = 1
Output: [[0,1],[0,0],[1,1],[1,0]]
Explanation: The distances from (0, 1) to other cells are: [0,1,1,2]
The answer [[0,1],[1,1],[0,0],[1,0]] would also be accepted as correct.

Example 3:
Input: rows = 2, cols = 3, rCenter = 1, cCenter = 2
Output: [[1,2],[0,2],[1,1],[0,1],[1,0],[0,0]]
Explanation: The distances from (1, 2) to other cells are: [0,1,1,2,2,3]
There are other answers that would also be accepted as correct, such as [[1,2],[1,1],[0,2],[1,0],[0,1],[0,0]].

Constraints:
1 <= rows, cols <= 100
0 <= rCenter < rows
0 <= cCenter < cols
```

</details>

<details><summary>C</summary>

```c
int _rCenter;
int _cCenter;
int compareIntArray(const void* a, const void* b) {
    int* p1 = *(int**)a;
    int* p2 = *(int**)b;

    // ascending order
    return fabs(p1[0] - _rCenter) + fabs(p1[1] - _cCenter) - fabs(p2[0] - _rCenter) - fabs(p2[1] - _cCenter);
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** allCellsDistOrder(int rows, int cols, int rCenter, int cCenter, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;

    int i, j;
    int mallocSize = rows * cols;
    (*returnColumnSizes) = (int*)malloc(mallocSize * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal = (int**)malloc(mallocSize * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }
    for (i = 0; i < mallocSize; ++i) {
        (*returnColumnSizes)[i] = 2;
        pRetVal[i] = (int*)malloc(2 * sizeof(int));
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
    }

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            pRetVal[(*returnSize)][0] = i;
            pRetVal[(*returnSize)][1] = j;
            (*returnSize)++;
        }
    }
    _rCenter = rCenter;
    _cCenter = cCenter;
    qsort(pRetVal, mallocSize, sizeof(int*), compareIntArray);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<vector<int>> allCellsDistOrder(int rows, int cols, int rCenter, int cCenter) {
        vector<vector<int>> retVal;

        for (int x = 0; x < rows; ++x) {
            for (int y = 0; y < cols; ++y) {
                retVal.push_back({x, y});
            }
        }
        sort(retVal.begin(), retVal.end(), [=](vector<int>& a, vector<int>& b) {
            return abs(a[0] - rCenter) + abs(a[1] - cCenter) < abs(b[0] - rCenter) + abs(b[1] - cCenter);
        });

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def allCellsDistOrder(self, rows: int, cols: int, rCenter: int, cCenter: int) -> List[List[int]]:
        retVal = []

        retVal = [(x, y) for x in range(rows) for y in range(cols)]
        retVal.sort(key=lambda x: abs(x[0] - rCenter) + abs(x[1] - cCenter))

        return retVal
```

</details>

## [1051. Height Checker](https://leetcode.com/problems/height-checker/)  1303

- [Official](https://leetcode.com/problems/height-checker/editorial/)
- [Official](https://leetcode.cn/problems/height-checker/solutions/1593917/gao-du-jian-cha-qi-by-leetcode-solution-jeb0/)

<details><summary>Description</summary>

```text
A school is trying to take an annual photo of all the students.
The students are asked to stand in a single file line in non-decreasing order by height.
Let this ordering be represented by the integer array expected
where expected[i] is the expected height of the ith student in line.

You are given an integer array heights representing the current order that the students are standing in.
Each heights[i] is the height of the ith student in line (0-indexed).

Return the number of indices where heights[i] != expected[i].

Example 1:
Input: heights = [1,1,4,2,1,3]
Output: 3
Explanation:
heights:  [1,1,4,2,1,3]
expected: [1,1,1,2,3,4]
Indices 2, 4, and 5 do not match.

Example 2:
Input: heights = [5,1,2,3,4]
Output: 5
Explanation:
heights:  [5,1,2,3,4]
expected: [1,2,3,4,5]
All indices do not match.

Example 3:
Input: heights = [1,2,3,4,5]
Output: 0
Explanation:
heights:  [1,2,3,4,5]
expected: [1,2,3,4,5]
All indices match.

Constraints:
1 <= heights.length <= 100
1 <= heights[i] <= 100
```

<details><summary>Hint</summary>

```text
1. Build the correct order of heights by sorting another array, then compare the two arrays.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int heightChecker(int* heights, int heightsSize) {
    int retVal = 0;

    int* expected = (int*)malloc(heightsSize * sizeof(int));
    if (expected == NULL) {
        perror("malloc");
        return retVal;
    }
    memset(expected, 0, heightsSize * sizeof(int));
    memcpy(expected, heights, heightsSize * sizeof(int));
    qsort(expected, heightsSize, sizeof(int), compareInteger);

    int i;
    for (i = 0; i < heightsSize; ++i) {
        if (heights[i] != expected[i]) {
            ++retVal;
        }
    }

    free(expected);
    expected = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int heightChecker(vector<int>& heights) {
        int retVal = 0;

        vector<int> expected(heights);
        sort(expected.begin(), expected.end());

        int heightsSize = heights.size();
        for (int i = 0; i < heightsSize; ++i) {
            if (heights[i] != expected[i]) {
                ++retVal;
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
    def heightChecker(self, heights: List[int]) -> int:
        retVal = 0

        expected = sorted(heights)
        for x, y in zip(heights, expected):
            if x != y:
                retVal += 1

        return retVal
```

</details>

## [1122. Relative Sort Array](https://leetcode.com/problems/relative-sort-array/)  1188

- [Official](https://leetcode.com/problems/relative-sort-array/editorial/)
- [Official](https://leetcode.cn/problems/relative-sort-array/solutions/483863/shu-zu-de-xiang-dui-pai-xu-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given two arrays arr1 and arr2, the elements of arr2 are distinct, and all elements in arr2 are also in arr1.

Sort the elements of arr1 such that the relative ordering of items in arr1 are the same as in arr2.
Elements that do not appear in arr2 should be placed at the end of arr1 in ascending order.

Example 1:
Input: arr1 = [2,3,1,3,2,4,6,7,9,2,19], arr2 = [2,1,4,3,9,6]
Output: [2,2,2,1,4,3,3,9,6,7,19]

Example 2:
Input: arr1 = [28,6,22,8,44,17], arr2 = [22,28,8,6]
Output: [22,28,8,6,17,44]

Constraints:
1 <= arr1.length, arr2.length <= 1000
0 <= arr1[i], arr2[i] <= 1000
All the elements of arr2 are distinct.
Each arr2[i] is in arr1.
```

<details><summary>Hint</summary>

```text
1. Using a hashmap, we can map the values of arr2 to their position in arr2.
2. After, we can use a custom sorting function.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* relativeSortArray(int* arr1, int arr1Size, int* arr2, int arr2Size, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int*)malloc(arr1Size * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (arr1Size * sizeof(int)));

    int i, j;

    int upper = arr1[0];
    for (i = 0; i < arr1Size; ++i) {
        upper = fmax(upper, arr1[i]);
    }

    int frequency[upper + 1];
    memset(frequency, 0, sizeof(frequency));
    for (i = 0; i < arr1Size; ++i) {
        frequency[arr1[i]] += 1;
    }

    for (i = 0; i < arr2Size; ++i) {
        for (j = 0; j < frequency[arr2[i]]; ++j) {
            pRetVal[*(returnSize)] = arr2[i];
            *(returnSize) += 1;
        }
        frequency[arr2[i]] = 0;
    }
    for (i = 0; i < upper + 1; ++i) {
        if (frequency[i] != 0) {
            for (j = 0; j < frequency[i]; ++j) {
                pRetVal[*(returnSize)] = i;
                *(returnSize) += 1;
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
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        vector<int> retVal;

        int upper = *max_element(arr1.begin(), arr1.end());
        vector<int> frequency(upper + 1, 0);
        for (int x : arr1) {
            frequency[x] += 1;
        }

        for (int x : arr2) {
            for (int i = 0; i < frequency[x]; ++i) {
                retVal.emplace_back(x);
            }
            frequency[x] = 0;
        }
        for (int x = 0; x < upper + 1; ++x) {
            if (frequency[x] != 0) {
                for (int i = 0; i < frequency[x]; ++i) {
                    retVal.emplace_back(x);
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
    def relativeSortArray(self, arr1: List[int], arr2: List[int]) -> List[int]:
        retVal = []

        upper = max(arr1)
        frequency = [0] * (upper + 1)
        for x in arr1:
            frequency[x] += 1

        for x in arr2:
            for _ in range(frequency[x]):
                retVal.append(x)
            frequency[x] = 0

        for x in range(upper + 1):
            if frequency[x] > 0:
                for _ in range(frequency[x]):
                    retVal.append(x)

        return retVal
```

</details>

## [1365. How Many Numbers Are Smaller Than the Current Number](https://leetcode.com/problems/how-many-numbers-are-smaller-than-the-current-number/)  1152

- [Official](https://leetcode.cn/problems/how-many-numbers-are-smaller-than-the-current-number/solutions/122909/you-duo-shao-xiao-yu-dang-qian-shu-zi-de-shu-zi--2/)

<details><summary>Description</summary>

```text
Given the array nums, for each nums[i] find out how many numbers in the array are smaller than it.
That is, for each nums[i] you have to count the number of valid j's such that j != i and nums[j] < nums[i].

Return the answer in an array.

Example 1:
Input: nums = [8,1,2,2,3]
Output: [4,0,1,1,3]
Explanation:
For nums[0]=8 there exist four smaller numbers than it (1, 2, 2 and 3).
For nums[1]=1 does not exist any smaller number than it.
For nums[2]=2 there exist one smaller number than it (1).
For nums[3]=2 there exist one smaller number than it (1).
For nums[4]=3 there exist three smaller numbers than it (1, 2 and 2).

Example 2:
Input: nums = [6,5,4,8]
Output: [2,1,0,3]

Example 3:
Input: nums = [7,7,7,7]
Output: [0,0,0,0]

Constraints:
2 <= nums.length <= 500
0 <= nums[i] <= 100
```

<details><summary>Hint</summary>

```text
1. Brute force for each array element.
2. In order to improve the time complexity, we can sort the array and get the answer for each array element.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* smallerNumbersThanCurrent(int* nums, int numsSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = numsSize;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));

    int i, j;
    for (i = 0; i < numsSize; ++i) {
        for (j = 0; j < numsSize; ++j) {
            if (nums[i] > nums[j]) {
                ++pRetVal[i];
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
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
        vector<int> retVal;

        for (auto idx : nums) {
            int count = 0;
            for (auto num : nums) {
                if (idx > num) {
                    ++count;
                }
            }
            retVal.emplace_back(count);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def smallerNumbersThanCurrent(self, nums: List[int]) -> List[int]:
        retVal = [0 for _ in nums]

        numsSize = len(nums)
        for idx in range(numsSize):
            for num in nums:
                retVal[idx] += 1 if nums[idx] > num else 0

        return retVal
```

</details>

## [1502. Can Make Arithmetic Progression From Sequence](https://leetcode.com/problems/can-make-arithmetic-progression-from-sequence/)  1154

- [Official](https://leetcode.com/problems/can-make-arithmetic-progression-from-sequence/editorial/)

<details><summary>Description</summary>

```text
A sequence of numbers is called an arithmetic progression
if the difference between any two consecutive elements is the same.

Given an array of numbers arr, return true if the array can be rearranged to form an arithmetic progression.
Otherwise, return false.

Example 1:
Input: arr = [3,5,1]
Output: true
Explanation: We can reorder the elements as [1,3,5] or [5,3,1] with differences 2 and -2 respectively,
between each consecutive elements.

Example 2:
Input: arr = [1,2,4]
Output: false
Explanation: There is no way to reorder the elements to obtain an arithmetic progression.

Constraints:
2 <= arr.length <= 1000
-10^6 <= arr[i] <= 10^6
```

<details><summary>Hint</summary>

```text
1. Consider that any valid arithmetic progression will be in sorted order.
2. Sort the array, then check if the differences of all consecutive elements are equal.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
bool canMakeArithmeticProgression(int* arr, int arrSize) {
    bool retVal = false;

    qsort(arr, arrSize, sizeof(int), compareInteger);
    int i;
    for (i = 2; i < arrSize; ++i) {
        if ((arr[i] - arr[i - 1]) != (arr[i - 1] - arr[i - 2])) {
            return retVal;
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
    bool canMakeArithmeticProgression(vector<int>& arr) {
        bool retVal = false;

        sort(arr.begin(), arr.end());
        for (long unsigned int i=2; i<arr.size(); ++i) {
            if ((arr[i] - arr[i-1]) != (arr[i-1] - arr[i-2])) {
                return retVal;
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
    def canMakeArithmeticProgression(self, arr: List[int]) -> bool:
        arr.sort()
        for i in range(2, len(arr)):
            if (arr[i-2]-arr[i-1]) != (arr[i-1]-arr[i]):
                return False

        return True
```

</details>

## [1630. Arithmetic Subarrays](https://leetcode.com/problems/arithmetic-subarrays/)  1421

- [Official](https://leetcode.com/problems/arithmetic-subarrays/editorial/)
- [Official](https://leetcode.cn/problems/arithmetic-subarrays/solutions/2184153/deng-chai-zi-shu-zu-by-leetcode-solution-pmrp/)

<details><summary>Description</summary>

```text
A sequence of numbers is called arithmetic if it consists of at least two elements,
and the difference between every two consecutive elements is the same.
More formally, a sequence s is arithmetic if and only if s[i+1] - s[i] == s[1] - s[0] for all valid i.

For example, these are arithmetic sequences:
1, 3, 5, 7, 9
7, 7, 7, 7
3, -1, -5, -9

The following sequence is not arithmetic:
1, 1, 2, 5, 7

You are given an array of n integers, nums, and two arrays of m integers each, l and r,
representing the m range queries, where the ith query is the range [l[i], r[i]].
All the arrays are 0-indexed.

Return a list of boolean elements answer,
where answer[i] is true if the subarray nums[l[i]], nums[l[i]+1], ... , nums[r[i]]
can be rearranged to form an arithmetic sequence, and false otherwise.

Example 1:
Input: nums = [4,6,5,9,3,7], l = [0,0,2], r = [2,3,5]
Output: [true,false,true]
Explanation:
In the 0th query, the subarray is [4,6,5]. This can be rearranged as [6,5,4], which is an arithmetic sequence.
In the 1st query, the subarray is [4,6,5,9]. This cannot be rearranged as an arithmetic sequence.
In the 2nd query, the subarray is [5,9,3,7]. This can be rearranged as [3,5,7,9], which is an arithmetic sequence.

Example 2:
Input: nums = [-12,-9,-3,-12,-6,15,20,-25,-20,-15,-10], l = [0,1,6,4,8,7], r = [4,4,9,7,9,10]
Output: [false,true,false,false,true,true]

Constraints:
n == nums.length
m == l.length
m == r.length
2 <= n <= 500
1 <= m <= 500
0 <= l[i] < r[i] < n
-10^5 <= nums[i] <= 10^5
```

<details><summary>Hint</summary>

```text
1. To check if a given sequence is arithmetic,
   just check that the difference between every two consecutive elements is the same.
2. If and only if a set of numbers can make an arithmetic sequence,
   then its sorted version makes an arithmetic sequence.
   So to check a set of numbers, sort it, and check if that sequence is arithmetic.
3. For each query, get the corresponding set of numbers which will be the sub-array represented by the query,
   sort it, and check if the result sequence is arithmetic.
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
bool* checkArithmeticSubarrays(int* nums, int numsSize, int* l, int lSize, int* r, int rSize, int* returnSize) {
    bool* pRetVal = NULL;

    (*returnSize) = lSize;

    pRetVal = (bool*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));

    int subarray[numsSize];
    int left, right, subarraySize;
    int i, j;
    for (i = 0; i < (*returnSize); ++i) {
        pRetVal[i] = true;

        left = l[i];
        right = r[i] + 1;
        subarraySize = right - left;
        memset(subarray, 0, sizeof(subarray));
        memcpy(subarray, nums + left, subarraySize * sizeof(int));

        qsort(subarray, subarraySize, sizeof(int), compareInteger);
        for (j = 1; j < (subarraySize - 1); ++j) {
            if ((subarray[j] - subarray[j - 1]) != (subarray[j + 1] - subarray[j])) {
                pRetVal[i] = false;
                break;
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
    vector<bool> checkArithmeticSubarrays(vector<int>& nums, vector<int>& l, vector<int>& r) {
        vector<bool> retVal;

        int lSize = l.size();
        for (int i = 0; i < lSize; ++i) {
            retVal.emplace_back(true);

            int left = l[i];
            int right = r[i] + 1;
            vector<int> subarray(begin(nums) + left, begin(nums) + right);
            sort(subarray.begin(), subarray.end());

            int subarraySize = right - left;
            for (int j = 1; j < (subarraySize - 1); ++j) {
                if ((subarray[j] - subarray[j - 1]) != (subarray[j + 1] - subarray[j])) {
                    retVal[i] = false;
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
    def checkArithmeticSubarrays(self, nums: List[int], l: List[int], r: List[int]) -> List[bool]:
        retVal = []

        for value in enumerate(zip(l, r)):
            index = value[0]
            left = value[1][0]
            right = value[1][1] + 1

            subarray = sorted(nums[left:right])

            retVal.append(True)
            subarraySize = right - left
            for i in range(1, subarraySize-1):
                if (subarray[i]-subarray[i-1]) != (subarray[i+1]-subarray[i]):
                    retVal[index] = False
                    break

        return retVal
```

</details>

## [1636. Sort Array by Increasing Frequency](https://leetcode.com/problems/sort-array-by-increasing-frequency/)  1430

- [Official](https://leetcode.com/problems/sort-array-by-increasing-frequency/editorial/)
- [Official](https://leetcode.cn/problems/sort-array-by-increasing-frequency/solutions/1831531/an-zhao-pin-lu-jiang-shu-zu-sheng-xu-pai-z2db/)

<details><summary>Description</summary>

```text
Given an array of integers nums, sort the array in increasing order based on the frequency of the values.
If multiple values have the same frequency, sort them in decreasing order.

Return the sorted array.

Example 1:
Input: nums = [1,1,2,2,2,3]
Output: [3,1,1,2,2,2]
Explanation: '3' has a frequency of 1, '1' has a frequency of 2, and '2' has a frequency of 3.

Example 2:
Input: nums = [2,3,1,3,2]
Output: [1,3,3,2,2]
Explanation: '2' and '3' both have a frequency of 2, so they are sorted in decreasing order.

Example 3:
Input: nums = [-1,1,-6,4,5,-6,1,4,1]
Output: [5,-1,4,4,-6,-6,1,1,1]

Constraints:
1 <= nums.length <= 100
-100 <= nums[i] <= 100
```

<details><summary>Hint</summary>

```text
1. Count the frequency of each value.
2. Use a custom comparator to compare values by their frequency.
   If two values have the same frequency, compare their values.
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
struct hashTable *pFrequency = NULL;
int hashGetItem(struct hashTable **obj, int key) {
    int retVal = 0;

    struct hashTable *pEntry = NULL;
    HASH_FIND_INT(*obj, &key, pEntry);
    if (pEntry != NULL) {
        retVal = pEntry->value;
    }

    return retVal;
}
void hashFree(struct hashTable *pFree) {
    struct hashTable *current;
    struct hashTable *tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
static inline int compareIntArray(const void *a1, const void *a2) {
    int p1 = *(int *)a1;
    int p2 = *(int *)a2;

    int pFrequency1 = hashGetItem(&pFrequency, p1);
    int pFrequency2 = hashGetItem(&pFrequency, p2);
    if (pFrequency1 == pFrequency2) {
        // descending order
        return (p1 < p2);
    }

    // ascending order
    return (pFrequency1 > pFrequency2);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *frequencySort(int *nums, int numsSize, int *returnSize) {
    int *pRetVal = NULL;

    //
    (*returnSize) = 0;

    //
    pFrequency = NULL;
    struct hashTable *pTemp;
    int key;
    int i;
    for (i = 0; i < numsSize; i++) {
        key = nums[i];
        pTemp = NULL;
        HASH_FIND_INT(pFrequency, &key, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                hashFree(pFrequency);
                return pRetVal;
            }
            pTemp->key = key;
            pTemp->value = 1;
            HASH_ADD_INT(pFrequency, key, pTemp);
        } else {
            pTemp->value += 1;
        }
    }

    //
    pRetVal = (int *)malloc(numsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        hashFree(pFrequency);
        return pRetVal;
    }
    memset(pRetVal, 0, (numsSize * sizeof(int)));
    memcpy(pRetVal, nums, (numsSize * sizeof(int)));
    (*returnSize) = numsSize;

    //
    qsort(pRetVal, (*returnSize), sizeof(int), compareIntArray);

    //
    hashFree(pFrequency);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> frequencySort(vector<int>& nums) {
        vector<int> retVal = nums;

        unordered_map<int, int> frequency;
        for (int num : nums) {
            frequency[num]++;
        }

        sort(retVal.begin(), retVal.end(), [&](int a, int b) {
            if (frequency[a] == frequency[b]) {
                return a > b;
            }
            return frequency[a] < frequency[b];
        });

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def frequencySort(self, nums: List[int]) -> List[int]:
        retVal = []

        frequency = Counter(nums)
        retVal = sorted(nums, key=lambda x: (frequency[x], -x))

        return retVal
```

</details>

## [1637. Widest Vertical Area Between Two Points Containing No Points](https://leetcode.com/problems/widest-vertical-area-between-two-points-containing-no-points/)  1486

- [Official](https://leetcode.com/problems/widest-vertical-area-between-two-points-containing-no-points/editorial/)
- [Official](https://leetcode.cn/problems/widest-vertical-area-between-two-points-containing-no-points/solutions/2196875/liang-dian-zhi-jian-bu-bao-han-ren-he-di-ol9u/)

<details><summary>Description</summary>

```text
Given n points on a 2D plane where points[i] = [xi, yi],
Return the widest vertical area between two points such that no points are inside the area.

A vertical area is an area of fixed-width extending infinitely along the y-axis (i.e., infinite height).
The widest vertical area is the one with the maximum width.

Note that points on the edge of a vertical area are not considered included in the area.

Example 1:
Input: points = [[8,7],[9,9],[7,4],[9,7]]
Output: 1
Explanation: Both the red and the blue area are optimal.

Example 2:
Input: points = [[3,1],[9,0],[1,0],[1,4],[5,3],[8,8]]
Output: 3

Constraints:
n == points.length
2 <= n <= 10^5
points[i].length == 2
0 <= xi, yi <= 10^9
```

<details><summary>Hint</summary>

```text
1. Try sorting the points
2. Think is the y-axis of a point relevant
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
int maxWidthOfVerticalArea(int** points, int pointsSize, int* pointsColSize) {
    int retVal = 0;

    qsort(points, pointsSize, sizeof(int*), compareIntArray);

    int i;
    for (i = 1; i < pointsSize; ++i) {
        retVal = fmax(retVal, (points[i][0] - points[i - 1][0]));
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxWidthOfVerticalArea(vector<vector<int>>& points) {
        int retVal = 0;

        sort(points.begin(), points.end(), [&](const vector<int>& x, const vector<int>& y) {
            // ascending order
            if (x[0] == y[0]) {
                return (x[1] < y[1]);
            }
            return (x[0] < y[0]);
        });

        int pointsSize = points.size();
        for (int i = 1; i < pointsSize; ++i) {
            retVal = max(retVal, (points[i][0] - points[i - 1][0]));
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxWidthOfVerticalArea(self, points: List[List[int]]) -> int:
        retVal = 0

        points.sort()

        pointsSize = len(points)
        for i in range(1, pointsSize):
            retVal = max(retVal, (points[i][0]-points[i-1][0]))

        return retVal
```

</details>

## [1710. Maximum Units on a Truck](https://leetcode.com/problems/maximum-units-on-a-truck/)  1309

<details><summary>Description</summary>

```text
You are assigned to put some amount of boxes onto one truck.
You are given a 2D array boxTypes, where boxTypes[i] = [numberOfBoxesi, numberOfUnitsPerBoxi]:
- numberOfBoxesi is the number of boxes of type i.
- numberOfUnitsPerBoxi is the number of units in each box of the type i.

You are also given an integer truckSize, which is the maximum number of boxes that can be put on the truck.
You can choose any boxes to put on the truck as long as the number of boxes does not exceed truckSize.

Return the maximum total number of units that can be put on the truck.

Example 1:
Input: boxTypes = [[1,3],[2,2],[3,1]], truckSize = 4
Output: 8
Explanation: There are:
- 1 box of the first type that contains 3 units.
- 2 boxes of the second type that contain 2 units each.
- 3 boxes of the third type that contain 1 unit each.
You can take all the boxes of the first and second types, and one box of the third type.
The total number of units will be = (1 * 3) + (2 * 2) + (1 * 1) = 8.

Example 2:
Input: boxTypes = [[5,10],[2,5],[4,7],[3,9]], truckSize = 10
Output: 91

Constraints:
1 <= boxTypes.length <= 1000
1 <= numberOfBoxesi, numberOfUnitsPerBoxi <= 1000
1 <= truckSize <= 10^6
```

</details>

<details><summary>C</summary>

```c
int compareIntArray(const void *pa, const void *pb) {
    const int *a = *(const int **)pa;
    const int *b = *(const int **)pb;
    if (a[1] == b[1]) {
        return b[0] - a[0];
    }
    else {
        return b[1] - a[1];
    }
}

int maximumUnits(int** boxTypes, int boxTypesSize, int* boxTypesColSize, int truckSize) {
    int retVal = 0;

    qsort(boxTypes, boxTypesSize, sizeof(boxTypes[0]), compareIntArray);

    int i;
    for (i=0; i<boxTypesSize; ++i) {
        if (truckSize > boxTypes[i][0]) {
            truckSize -= boxTypes[i][0];
            retVal += (boxTypes[i][0] * boxTypes[i][1]);
        }
        else {
            retVal += (truckSize * boxTypes[i][1]);
            break;
        }
    }

    return retVal;
}
```

</details>

## [1833. Maximum Ice Cream Bars](https://leetcode.com/problems/maximum-ice-cream-bars/)  1252

- [Official](https://leetcode.com/problems/maximum-ice-cream-bars/solutions/2885725/maximum-ice-cream-bars/)
- [Official](https://leetcode.cn/problems/maximum-ice-cream-bars/solutions/854165/xue-gao-de-zui-da-shu-liang-by-leetcode-ia3m7/)

<details><summary>Description</summary>

```text
It is a sweltering summer day, and a boy wants to buy some ice cream bars.

At the store, there are n ice cream bars.
You are given an array costs of length n, where costs[i] is the price of the ith ice cream bar in coins.
The boy initially has coins coins to spend, and he wants to buy as many ice cream bars as possible.

Return the maximum number of ice cream bars the boy can buy with coins coins.

Note: The boy can buy the ice cream bars in any order.

Example 1:
Input: costs = [1,3,2,4,1], coins = 7
Output: 4
Explanation: The boy can buy ice cream bars at indices 0,1,2,4 for a total price of 1 + 3 + 2 + 1 = 7.

Example 2:
Input: costs = [10,6,8,7,7,8], coins = 5
Output: 0
Explanation: The boy cannot afford any of the ice cream bars.

Example 3:
Input: costs = [1,6,3,1,2,5], coins = 20
Output: 6
Explanation: The boy can buy all the ice cream bars for a total price of 1 + 6 + 3 + 1 + 2 + 5 = 18.

Constraints:
costs.length == n
1 <= n <= 10^5
1 <= costs[i] <= 10^5
1 <= coins <= 10^8
```

</details>

<details><summary>C</summary>

```c
#define QUICK_SORT (1)
#define COUNT_SORT (1)
#if (QUICK_SORT)
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
#elif (COUNT_SORT)
#include <math.h>
#endif
int maxIceCream(int* costs, int costsSize, int coins) {
    int retVal = 0;

#if (QUICK_SORT)
    printf("QUICK_SORT\n");

    qsort(costs, costsSize, sizeof(int), compareInteger);
    for (retVal = 0; retVal < costsSize; ++retVal) {
        if (costs[retVal] > coins) {
            break;
        }
        coins -= costs[retVal];
    }
#elif (COUNT_SORT)
    printf("COUNT_SORT\n");

#define MAX_COUNT (int)(1e5 + 1)
    int CountSort[MAX_COUNT];
    memset(CountSort, 0, sizeof(CountSort));

    int i;
    for (i = 0; i < costsSize; ++i) {
        ++CountSort[costs[i]];
    }

    int count;
    for (i = 1; i < MAX_COUNT; ++i) {
        if (i > coins) {
            break;
        }
        count = fmin(CountSort[i], coins / i);
        retVal += count;
        coins -= i * count;
    }
#endif

    return retVal;
}
```

</details>

## [1877. Minimize Maximum Pair Sum in Array](https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/)  1301

- [Official](https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/editorial/)
- [Official](https://leetcode.cn/problems/minimize-maximum-pair-sum-in-array/solutions/802374/shu-zu-zhong-zui-da-shu-dui-he-de-zui-xi-cvll/)

<details><summary>Description</summary>

```text
The pair sum of a pair (a,b) is equal to a + b. The maximum pair sum is the largest pair sum in a list of pairs.
- For example, if we have pairs (1,5), (2,3), and (4,4),
  the maximum pair sum would be max(1+5, 2+3, 4+4) = max(6, 5, 8) = 8.

Given an array nums of even length n, pair up the elements of nums into n / 2 pairs such that:
- Each element of nums is in exactly one pair, and
- The maximum pair sum is minimized.

Return the minimized maximum pair sum after optimally pairing up the elements.

Example 1:
Input: nums = [3,5,2,3]
Output: 7
Explanation: The elements can be paired up into pairs (3,3) and (5,2).
The maximum pair sum is max(3+3, 5+2) = max(6, 7) = 7.

Example 2:
Input: nums = [3,5,4,2,4,6]
Output: 8
Explanation: The elements can be paired up into pairs (3,5), (4,4), and (6,2).
The maximum pair sum is max(3+5, 4+4, 6+2) = max(8, 8, 8) = 8.

Constraints:
n == nums.length
2 <= n <= 10^5
n is even.
1 <= nums[i] <= 10^5
```

<details><summary>Hint</summary>

```text
1. Would sorting help find the optimal order?
2. Given a specific element, how would you minimize its specific pairwise sum?
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int minPairSum(int* nums, int numsSize) {
    int retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int sum;
    int left = 0;
    int right = numsSize - 1;
    while (left < right) {
        sum = nums[left] + nums[right];
        if (sum > retVal) {
            retVal = sum;
        }
        left++;
        right--;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minPairSum(vector<int>& nums) {
        int retVal = 0;

        sort(nums.begin(), nums.end());

        int numsSize = nums.size();
        int left = 0;
        int right = numsSize - 1;
        while (left < right) {
            int sum = nums[left] + nums[right];
            if (sum > retVal) {
                retVal = sum;
            }
            left++;
            right--;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minPairSum(self, nums: List[int]) -> int:
        retVal = 0

        nums.sort()

        numsSize = len(nums)
        left = 0
        right = numsSize - 1
        while left < right:
            sum = nums[left] + nums[right]
            if sum > retVal:
                retVal = sum
            left += 1
            right -= 1

        return retVal
```

</details>

## [1887. Reduction Operations to Make the Array Elements Equal](https://leetcode.com/problems/reduction-operations-to-make-the-array-elements-equal/)  1427

- [Official](https://leetcode.com/problems/reduction-operations-to-make-the-array-elements-equal/editorial/)
- [Official](https://leetcode.cn/problems/reduction-operations-to-make-the-array-elements-equal/solutions/815375/shi-shu-zu-yuan-su-xiang-deng-de-jian-sh-lt55/)

<details><summary>Description</summary>

```text
Given an integer array nums, your goal is to make all elements in nums equal.
To complete one operation, follow these steps:
1. Find the largest value in nums. Let its index be i (0-indexed) and its value be largest.
   If there are multiple elements with the largest value, pick the smallest i.
2. Find the next largest value in nums strictly smaller than largest. Let its value be nextLargest.
3. Reduce nums[i] to nextLargest.

Return the number of operations to make all elements in nums equal.

Example 1:
Input: nums = [5,1,3]
Output: 3
Explanation: It takes 3 operations to make all elements in nums equal:
1. largest = 5 at index 0. nextLargest = 3. Reduce nums[0] to 3. nums = [3,1,3].
2. largest = 3 at index 0. nextLargest = 1. Reduce nums[0] to 1. nums = [1,1,3].
3. largest = 3 at index 2. nextLargest = 1. Reduce nums[2] to 1. nums = [1,1,1].

Example 2:
Input: nums = [1,1,1]
Output: 0
Explanation: All elements in nums are already equal.

Example 3:
Input: nums = [1,1,2,2,3]
Output: 4
Explanation: It takes 4 operations to make all elements in nums equal:
1. largest = 3 at index 4. nextLargest = 2. Reduce nums[4] to 2. nums = [1,1,2,2,2].
2. largest = 2 at index 2. nextLargest = 1. Reduce nums[2] to 1. nums = [1,1,1,2,2].
3. largest = 2 at index 3. nextLargest = 1. Reduce nums[3] to 1. nums = [1,1,1,1,2].
4. largest = 2 at index 4. nextLargest = 1. Reduce nums[4] to 1. nums = [1,1,1,1,1].

Constraints:
1 <= nums.length <= 5 * 10^4
1 <= nums[i] <= 5 * 10^4
```

<details><summary>Hint</summary>

```text
1. Sort the array.
2. Try to reduce all elements with maximum value to the next maximum value in one operation.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int reductionOperations(int* nums, int numsSize) {
    int retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int count = 0;
    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[i] != nums[i - 1]) {
            count += 1;
        }
        retVal += count;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int reductionOperations(vector<int>& nums) {
        int retVal = 0;

        sort(nums.begin(), nums.end());

        int numsSize = nums.size();
        int count = 0;
        for (int i = 1; i < numsSize; ++i) {
            if (nums[i] != nums[i - 1]) {
                count += 1;
            }
            retVal += count;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def reductionOperations(self, nums: List[int]) -> int:
        retVal = 0

        nums.sort()

        count = 0
        numsSize = len(nums)
        for i in range(1, numsSize):
            if nums[i] != nums[i-1]:
                count += 1
            retVal += count

        return retVal
```

</details>

## [2033. Minimum Operations to Make a Uni-Value Grid](https://leetcode.com/problems/minimum-operations-to-make-a-uni-value-grid/)  1671

- [Official](https://leetcode.com/problems/minimum-operations-to-make-a-uni-value-grid/editorial/)

<details><summary>Description</summary>

```text
You are given a 2D integer grid of size m x n and an integer x.
In one operation, you can add x to or subtract x from any element in the grid.

A uni-value grid is a grid where all the elements of it are equal.

Return the minimum number of operations to make the grid uni-value. If it is not possible, return -1.

Example 1:
Input: grid = [[2,4],[6,8]], x = 2
Output: 4
Explanation: We can make every element equal to 4 by doing the following:
- Add x to 2 once.
- Subtract x from 6 once.
- Subtract x from 8 twice.
A total of 4 operations were used.

Example 2:
Input: grid = [[1,5],[2,3]], x = 1
Output: 5
Explanation: We can make every element equal to 3.

Example 3:
Input: grid = [[1,2],[3,4]], x = 2
Output: -1
Explanation: It is impossible to make every element equal.

Constraints:
m == grid.length
n == grid[i].length
1 <= m, n <= 10^5
1 <= m * n <= 10^5
1 <= x, grid[i][j] <= 10^4
```

<details><summary>Hint</summary>

```text
1. Is it possible to make two integers a and b equal if they have different remainders dividing by x?
2. If it is possible, which number should you select to minimize the number of operations?
3. What if the elements are sorted?
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int minOperations(int** grid, int gridSize, int* gridColSize, int x) {
    int retVal = 0;

    // Flatten the grid into numsArray
    int numsArraySize = gridSize * gridColSize[0];
    int* numsArray = (int*)malloc(numsArraySize * sizeof(int));
    if (numsArray == NULL) {
        perror("malloc");
        return retVal;
    }
    for (int row = 0; row < gridSize; row++) {
        for (int col = 0; col < gridColSize[row]; col++) {
            numsArray[row * gridColSize[row] + col] = grid[row][col];
        }
    }

    // Sort numsArray in non-decreasing order to easily find the median
    qsort(numsArray, numsArraySize, sizeof(int), compareInteger);

    // Store the median element as the final common value
    int finalCommonNumber = numsArray[numsArraySize / 2];

    for (int i = 0; i < numsArraySize; i++) {
        // If the remainder when divided by x is different for any number, return -1
        if (numsArray[i] % x != finalCommonNumber % x) {
            retVal = -1;
            break;
        }
        // Add the number of operations required to make the current number equal to finalCommonNumber
        retVal += abs(finalCommonNumber - numsArray[i]) / x;
    }

    //
    free(numsArray);
    numsArray = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minOperations(vector<vector<int>>& grid, int x) {
        int retVal = 0;

        int gridSize = grid.size();
        int gridColSize = grid[0].size();

        // Flatten the grid into numsArray
        vector<int> numsArray;
        for (int row = 0; row < gridSize; row++) {
            for (int col = 0; col < gridColSize; col++) {
                numsArray.push_back(grid[row][col]);
            }
        }
        int numsArraySize = numsArray.size();

        // Partially sorts the array so that the median element is placed at the middle index
        nth_element(numsArray.begin(), numsArray.begin() + numsArraySize / 2, numsArray.end());

        // Store the median element as the final common value to make all elements equal to
        int finalCommonNumber = numsArray[numsArraySize / 2];

        for (int number : numsArray) {
            // If the remainder when divided by x is different for any number, return -1
            if (number % x != finalCommonNumber % x) {
                retVal = -1;
                break;
            }
            // Add the number of operations required to make the current number equal to finalCommonNumber
            retVal += abs(finalCommonNumber - number) / x;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minOperations(self, grid: List[List[int]], x: int) -> int:
        retVal = 0

        # Flatten the grid into numsArray
        numsArray = []
        for row in grid:
            for num in row:
                numsArray.append(num)
        numsArraySize = len(numsArray)

        # Sort numsArray in non-decreasing order to easily find the median
        numsArray.sort()

        # Store the median element as the final common value
        finalCommonNumber = numsArray[numsArraySize // 2]

        # Iterate through each number in numsArray
        for number in numsArray:
            # If the remainder when divided by x is different, return -1
            if number % x != finalCommonNumber % x:
                retVal = -1
                break
            # Add the number of operations required to make the current number equal to final_common_number
            retVal += abs(finalCommonNumber - number) // x

        return retVal
```

</details>

## [2054. Two Best Non-Overlapping Events](https://leetcode.com/problems/two-best-non-overlapping-events/)  1883

- [Official](https://leetcode.com/problems/two-best-non-overlapping-events/editorial/)
- [Official](https://leetcode.cn/problems/two-best-non-overlapping-events/solutions/1077100/liang-ge-zui-hao-de-bu-zhong-die-huo-don-urq5/)

<details><summary>Description</summary>

```text
You are given a 0-indexed 2D integer array of events where events[i] = [startTimei, endTimei, valuei].
The ith event starts at startTimei and ends at endTimei,
and if you attend this event, you will receive a value of valuei.
You can choose at most two non-overlapping events to attend such that the sum of their values is maximized.

Return this maximum sum.

Note that the start time and end time is inclusive:
that is, you cannot attend two events where one of them starts and the other ends at the same time.
More specifically, if you attend an event with end time t, the next event must start at or after t + 1.

Example 1:
Input: events = [[1,3,2],[4,5,2],[2,4,3]]
Output: 4
Explanation: Choose the green events, 0 and 1 for a sum of 2 + 2 = 4.

Example 2:
Input: events = [[1,3,2],[4,5,2],[1,5,5]]
Output: 5
Explanation: Choose event 2 for a sum of 5.

Example 3:
Input: events = [[1,5,3],[1,5,1],[6,6,5]]
Output: 8
Explanation: Choose events 0 and 2 for a sum of 3 + 5 = 8.

Constraints:
2 <= events.length <= 10^5
events[i].length == 3
1 <= startTimei <= endTimei <= 10^9
1 <= valuei <= 10^6
```

<details><summary>Hint</summary>

```text
1. How can sorting the events on the basis of their start times help? How about end times?
2. How can we quickly get the maximum score of an interval not intersecting with the interval we chose?
```

</details>

</details>

<details><summary>C</summary>

```c
int compareIntArray(const void* a1, const void* a2) {
    int* p1 = (int*)a1;
    int* p2 = (int*)a2;

    // ascending order
    if (p1[0] == p2[0]) {
        if (p1[1] == p2[1]) {
            return (p1[2] > p2[2]);
        }
        return (p1[1] > p2[1]);
    }

    return (p1[0] > p2[0]);
}
int maxTwoEvents(int** events, int eventsSize, int* eventsColSize) {
    int retVal = 0;

    int timesIndex = 0;
    int timesSize = eventsSize * 2;
    int times[timesSize][3];
    memset(times, 0, sizeof(times));
    for (int i = 0; i < eventsSize; ++i) {
        times[timesIndex][0] = events[i][0];
        times[timesIndex][1] = 1;  // 1 denotes start time.
        times[timesIndex][2] = events[i][2];
        timesIndex++;
        times[timesIndex][0] = events[i][1] + 1;
        times[timesIndex][1] = 0;  // 0 denotes end time.
        times[timesIndex][2] = events[i][2];
        timesIndex++;
    }
    qsort(times, timesSize, sizeof(times[0]), compareIntArray);

    int maxValue = 0;
    for (int i = 0; i < timesSize; ++i) {
        // If current time is a start time, find maximum sum of maximum end time till now.
        if (times[i][1]) {
            retVal = fmax(retVal, times[i][2] + maxValue);
        } else {
            maxValue = fmax(maxValue, times[i][2]);
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
    int maxTwoEvents(vector<vector<int>>& events) {
        int retVal = 0;

        vector<array<int, 3>> times;
        for (auto& event : events) {
            times.push_back({event[0], 1, event[2]});      // 1 denotes start time.
            times.push_back({event[1] + 1, 0, event[2]});  // 0 denotes end time.
        }
        sort(begin(times), end(times));

        int maxValue = 0;
        for (auto& timeValue : times) {
            // If current time is a start time, find maximum sum of maximum end time till now.
            if (timeValue[1]) {
                retVal = max(retVal, timeValue[2] + maxValue);
            } else {
                maxValue = max(maxValue, timeValue[2]);
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
    def maxTwoEvents(self, events: List[List[int]]) -> int:
        retVal = 0

        times = []
        for event in events:
            times.append([event[0], 1, event[2]])  # 1 denotes start time.
            times.append([event[1] + 1, 0, event[2]])  # 0 denotes end time.
        times.sort()

        maxValue = 0
        for timeValue in times:
            # If current time is a start time, find maximum sum of maximum end time till now.
            if timeValue[1]:
                retVal = max(retVal, timeValue[2] + maxValue)
            else:
                maxValue = max(maxValue, timeValue[2])

        return retVal
```

</details>

## [2070. Most Beautiful Item for Each Query](https://leetcode.com/problems/most-beautiful-item-for-each-query/)  1724

- [Official](https://leetcode.com/problems/most-beautiful-item-for-each-query/editorial/)
- [Official](https://leetcode.cn/problems/most-beautiful-item-for-each-query/solutions/1101845/mei-yi-ge-cha-xun-de-zui-da-mei-li-zhi-b-d8jw/)

<details><summary>Description</summary>

```text
You are given a 2D integer array items where items[i] = [pricei, beautyi]
denotes the price and beauty of an item respectively.

You are also given a 0-indexed integer array queries. For each queries[j],
you want to determine the maximum beauty of an item whose price is less than or equal to queries[j].
If no such item exists, then the answer to this query is 0.

Return an array answer of the same length as queries where answer[j] is the answer to the jth query.

Example 1:
Input: items = [[1,2],[3,2],[2,4],[5,6],[3,5]], queries = [1,2,3,4,5,6]
Output: [2,4,5,5,6,6]
Explanation:
- For queries[0]=1, [1,2] is the only item which has price <= 1. Hence, the answer for this query is 2.
- For queries[1]=2, the items which can be considered are [1,2] and [2,4].
  The maximum beauty among them is 4.
- For queries[2]=3 and queries[3]=4, the items which can be considered are [1,2], [3,2], [2,4], and [3,5].
  The maximum beauty among them is 5.
- For queries[4]=5 and queries[5]=6, all items can be considered.
  Hence, the answer for them is the maximum beauty of all items, i.e., 6.

Example 2:
Input: items = [[1,2],[1,2],[1,3],[1,4]], queries = [1]
Output: [4]
Explanation:
The price of every item is equal to 1, so we choose the item with the maximum beauty 4.
Note that multiple items can have the same price and/or beauty.

Example 3:
Input: items = [[10,1000]], queries = [5]
Output: [0]
Explanation:
No item has a price less than or equal to 5, so no item can be chosen.
Hence, the answer to the query is 0.

Constraints:
1 <= items.length, queries.length <= 10^5
items[i].length == 2
1 <= pricei, beautyi, queries[j] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Can we process the queries in a smart order to avoid repeatedly checking the same items?
2. How can we use the answer to a query for other queries?
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
int binarySearch(int** items, int itemsSize, int* itemsColSize, int targetPrice) {
    int retVal = 0;

    int left = 0;
    int right = itemsSize - 1;
    while (left <= right) {
        int middle = (left + right) / 2;
        if (items[middle][0] > targetPrice) {
            right = middle - 1;
        } else {
            retVal = fmax(retVal, items[middle][1]);
            left = middle + 1;
        }
    }

    return retVal;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maximumBeauty(int** items, int itemsSize, int* itemsColSize, int* queries, int queriesSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    qsort(items, itemsSize, sizeof(items[0]), compareIntArray);

    int maxBeauty = items[0][1];
    for (int i = 0; i < itemsSize; ++i) {
        maxBeauty = fmax(maxBeauty, items[i][1]);
        items[i][1] = maxBeauty;
    }

    pRetVal = (int*)calloc(queriesSize, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }

    for (int i = 0; i < queriesSize; ++i) {
        pRetVal[(*returnSize)++] = binarySearch(items, itemsSize, itemsColSize, queries[i]);
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int binarySearch(vector<vector<int>>& items, int targetPrice) {
        int retVal = 0;

        int left = 0;
        int right = items.size() - 1;
        while (left <= right) {
            int middle = (left + right) / 2;
            if (items[middle][0] > targetPrice) {
                right = middle - 1;
            } else {
                retVal = max(retVal, items[middle][1]);
                left = middle + 1;
            }
        }

        return retVal;
    }
    vector<int> maximumBeauty(vector<vector<int>>& items, vector<int>& queries) {
        vector<int> retVal;

        sort(items.begin(), items.end(), [](vector<int>& a, vector<int>& b) {
            // ascending order
            return a[0] < b[0];
        });

        int maxBeauty = items[0][1];
        for (auto& item : items) {
            maxBeauty = max(maxBeauty, item[1]);
            item[1] = maxBeauty;
        }

        for (int query : queries) {
            retVal.emplace_back(binarySearch(items, query));
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def binarySearch(self, items, targetPrice) -> int:
        retVal = 0

        left = 0
        right = len(items) - 1
        while left <= right:
            middle = (left + right) // 2
            if items[middle][0] > targetPrice:
                right = middle - 1
            else:
                retVal = max(retVal, items[middle][1])
                left = middle + 1

        return retVal

    def maximumBeauty(self, items: List[List[int]], queries: List[int]) -> List[int]:
        retVal = []

        items.sort(key=lambda x: x[0])

        maxBeauty = items[0][1]
        for item in items:
            maxBeauty = max(maxBeauty, item[1])
            item[1] = maxBeauty

        for query in queries:
            retVal.append(self.binarySearch(items, query))

        return retVal
```

</details>

## [2099. Find Subsequence of Length K With the Largest Sum](https://leetcode.com/problems/find-subsequence-of-length-k-with-the-largest-sum/)  1447

- [Official](https://leetcode.cn/problems/find-subsequence-of-length-k-with-the-largest-sum/solutions/1153679/zhao-dao-he-zui-da-de-chang-du-wei-k-de-01ike/)

<details><summary>Description</summary>

```text
You are given an integer array nums and an integer k.
You want to find a subsequence of nums of length k that has the largest sum.

Return any such subsequence as an integer array of length k.

A subsequence is an array that can be derived from another array
by deleting some or no elements without changing the order of the remaining elements.

Example 1:
Input: nums = [2,1,3,3], k = 2
Output: [3,3]
Explanation:
The subsequence has the largest sum of 3 + 3 = 6.

Example 2:
Input: nums = [-1,-2,3,4], k = 3
Output: [-1,3,4]
Explanation:
The subsequence has the largest sum of -1 + 3 + 4 = 6.

Example 3:
Input: nums = [3,4,3,3], k = 2
Output: [3,4]
Explanation:
The subsequence has the largest sum of 3 + 4 = 7.
Another possible subsequence is [4, 3].

Constraints:
1 <= nums.length <= 1000
-10^5 <= nums[i] <= 10^5
1 <= k <= nums.length
```

<details><summary>Hint</summary>

```text
1. From a greedy perspective, what k elements should you pick?
2. Could you sort the array while maintaining the index?
```

</details>

</details>

<details><summary>C</summary>

```c
struct sequenceType {
    int index;
    int value;
};
int compareStructByValue(const void *a1, const void *a2) {
    struct sequenceType *p1 = (struct sequenceType *)a1;
    struct sequenceType *p2 = (struct sequenceType *)a2;

    if (p1->value == p2->value) {
        return (p1->index > p2->index);
    }

    // descending order
    return (p1->value < p2->value);
}
int compareStructByIndex(const void *a1, const void *a2) {
    struct sequenceType *p1 = (struct sequenceType *)a1;
    struct sequenceType *p2 = (struct sequenceType *)a2;

    // ascending order
    return (p1->index > p2->index);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *maxSubsequence(int *nums, int numsSize, int k, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;

    struct sequenceType sequence[numsSize];
    memset(sequence, 0, sizeof(sequence));
    int i;
    for (i = 0; i < numsSize; ++i) {
        sequence[i].index = i;
        sequence[i].value = nums[i];
    }
    qsort(sequence, numsSize, sizeof(struct sequenceType), compareStructByValue);
    qsort(sequence, k, sizeof(struct sequenceType), compareStructByIndex);

    pRetVal = (int *)malloc(k * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (k * sizeof(int)));
    for (i = 0; i < k; ++i) {
        pRetVal[i] = sequence[i].value;
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
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        vector<int> retVal;

        int numsSize = nums.size();

        vector<pair<int, int>> sequence;
        for (int i = 0; i < numsSize; ++i) {
            sequence.emplace_back(i, nums[i]);
        }
        sort(sequence.begin(), sequence.end(), [&](auto x1, auto x2) {
            // descending order
            return x1.second > x2.second;
        });
        sort(sequence.begin(), sequence.begin() + k);

        for (int i = 0; i < k; ++i) {
            retVal.emplace_back(sequence[i].second);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxSubsequence(self, nums: List[int], k: int) -> List[int]:
        retVal = []

        sequence = [[index, value] for index, value in enumerate(nums)]
        sequence.sort(key=lambda sequence: -sequence[1])
        sequence = sequence[:k]
        sequence.sort(key=lambda sequence: sequence[0])
        retVal = [value for _, value in sequence]

        return retVal
```

</details>

## [2191. Sort the Jumbled Numbers](https://leetcode.com/problems/sort-the-jumbled-numbers/)  1496

- [Official](https://leetcode.com/problems/sort-the-jumbled-numbers/editorial/)
- [Official](https://leetcode.cn/problems/sort-the-jumbled-numbers/solutions/1328589/jiang-za-luan-wu-zhang-de-shu-zi-pai-xu-9zrmp/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array mapping which represents the mapping rule of a shuffled decimal system.
mapping[i] = j means digit i should be mapped to digit j in this system.

The mapped value of an integer is the new integer obtained
by replacing each occurrence of digit i in the integer with mapping[i] for all 0 <= i <= 9.

You are also given another integer array nums.
Return the array nums sorted in non-decreasing order based on the mapped values of its elements.

Notes:
- Elements with the same mapped values should appear in the same relative order as in the input.
- The elements of nums should only be sorted based on their mapped values and not be replaced by them.

Example 1:
Input: mapping = [8,9,4,0,2,1,3,5,7,6], nums = [991,338,38]
Output: [338,38,991]
Explanation:
Map the number 991 as follows:
1. mapping[9] = 6, so all occurrences of the digit 9 will become 6.
2. mapping[1] = 9, so all occurrences of the digit 1 will become 9.
Therefore, the mapped value of 991 is 669.
338 maps to 007, or 7 after removing the leading zeros.
38 maps to 07, which is also 7 after removing leading zeros.
Since 338 and 38 share the same mapped value, they should remain in the same relative order, so 338 comes before 38.
Thus, the sorted array is [338,38,991].

Example 2:
Input: mapping = [0,1,2,3,4,5,6,7,8,9], nums = [789,456,123]
Output: [123,456,789]
Explanation: 789 maps to 789, 456 maps to 456, and 123 maps to 123. Thus, the sorted array is [123,456,789].

Constraints:
mapping.length == 10
0 <= mapping[i] <= 9
All the values of mapping[i] are unique.
1 <= nums.length <= 3 * 10^4
0 <= nums[i] < 10^9
```

<details><summary>Hint</summary>

```text
1. Map the original numbers to new numbers by the mapping rule and sort the new numbers.
2. To maintain the same relative order for equal mapped values,
   use the index in the original input array as a tiebreaker.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareIntArray(const void *a1, const void *a2) {
    int *p1 = (int *)a1;
    int *p2 = (int *)a2;

    // ascending order
    if (p1[0] == p2[0]) {
        return (p1[1] > p2[1]);
    }

    return (p1[0] > p2[0]);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *sortJumbled(int *mapping, int mappingSize, int *nums, int numsSize, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;

    int storePairs[numsSize][2];
    memset(storePairs, 0, sizeof(storePairs));
    int num, mappedValue, shift;
    int idx;
    for (idx = 0; idx < numsSize; ++idx) {
        num = nums[idx];
        if (num == 0) {
            storePairs[idx][0] = mapping[num];
            storePairs[idx][1] = idx;
            continue;
        }

        mappedValue = 0;
        shift = 1;
        while (num > 0) {
            mappedValue += (mapping[num % 10] * shift);
            num /= 10;
            shift *= 10;
        }
        storePairs[idx][0] = mappedValue;
        storePairs[idx][1] = idx;
    }

    qsort(storePairs, numsSize, sizeof(storePairs[0]), compareIntArray);

    pRetVal = (int *)malloc(numsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (numsSize * sizeof(int)));
    for (idx = 0; idx < numsSize; ++idx) {
        pRetVal[idx] = nums[storePairs[idx][1]];
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
    vector<int> sortJumbled(vector<int>& mapping, vector<int>& nums) {
        vector<int> retVal;

        int numsSize = nums.size();
        vector<pair<int, int>> storePairs;
        for (int idx = 0; idx < numsSize; ++idx) {
            int num = nums[idx];
            if (num == 0) {
                storePairs.push_back({mapping[num], idx});
                continue;
            }

            int mappedValue = 0;
            int shift = 1;
            while (num > 0) {
                mappedValue += (mapping[num % 10] * shift);
                num /= 10;
                shift *= 10;
            }
            storePairs.push_back({mappedValue, idx});
        }

        sort(storePairs.begin(), storePairs.end());
        for (auto pair : storePairs) {
            retVal.emplace_back(nums[pair.second]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def sortJumbled(self, mapping: List[int], nums: List[int]) -> List[int]:
        retVal = []

        storePairs = []
        for idx, num in enumerate(nums):
            if num == 0:    # 0 <= nums[i] < 10^9
                storePairs.append((mapping[num], idx))
                continue

            mappedValue = 0
            shift = 1
            while num > 0:
                mappedValue += (mapping[num % 10] * shift)
                num //= 10
                shift *= 10
            storePairs.append((mappedValue, idx))

        storePairs.sort()
        for _, idx in storePairs:
            retVal.append(nums[idx])

        return retVal
```

</details>

## [2402. Meeting Rooms III](https://leetcode.com/problems/meeting-rooms-iii/)  2092

- [Official](https://leetcode.com/problems/meeting-rooms-iii/editorial/)

<details><summary>Description</summary>

```text
You are given an integer n. There are n rooms numbered from 0 to n - 1.

You are given a 2D integer array meetings where meetings[i] = [starti, endi]
means that a meeting will be held during the half-closed time interval [starti, endi).
All the values of starti are unique.

Meetings are allocated to rooms in the following manner:
1. Each meeting will take place in the unused room with the lowest number.
2. If there are no available rooms, the meeting will be delayed until a room becomes free.
   The delayed meeting should have the same duration as the original meeting.
3. When a room becomes unused, meetings that have an earlier original start time should be given the room.

Return the number of the room that held the most meetings.
If there are multiple rooms, return the room with the lowest number.

A half-closed interval [a, b) is the interval between a and b including a and not including b.

Example 1:
Input: n = 2, meetings = [[0,10],[1,5],[2,7],[3,4]]
Output: 0
Explanation:
- At time 0, both rooms are not being used. The first meeting starts in room 0.
- At time 1, only room 1 is not being used. The second meeting starts in room 1.
- At time 2, both rooms are being used. The third meeting is delayed.
- At time 3, both rooms are being used. The fourth meeting is delayed.
- At time 5, the meeting in room 1 finishes. The third meeting starts in room 1 for the time period [5,10).
- At time 10, the meetings in both rooms finish. The fourth meeting starts in room 0 for the time period [10,11).
Both rooms 0 and 1 held 2 meetings, so we return 0.

Example 2:
Input: n = 3, meetings = [[1,20],[2,10],[3,5],[4,9],[6,8]]
Output: 1
Explanation:
- At time 1, all three rooms are not being used. The first meeting starts in room 0.
- At time 2, rooms 1 and 2 are not being used. The second meeting starts in room 1.
- At time 3, only room 2 is not being used. The third meeting starts in room 2.
- At time 4, all three rooms are being used. The fourth meeting is delayed.
- At time 5, the meeting in room 2 finishes. The fourth meeting starts in room 2 for the time period [5,10).
- At time 6, all three rooms are being used. The fifth meeting is delayed.
- At time 10, the meetings in rooms 1 and 2 finish. The fifth meeting starts in room 1 for the time period [10,12).
Room 0 held 1 meeting while rooms 1 and 2 each held 2 meetings, so we return 1.

Constraints:
1 <= n <= 100
1 <= meetings.length <= 10^5
meetings[i].length == 2
0 <= starti < endi <= 5 * 10^5
All the values of starti are unique.
```

<details><summary>Hint</summary>

```text
1. Sort meetings based on start times.
2. Use two min heaps, the first one keeps track of the numbers of all the rooms that are free.
   The second heap keeps track of the end times of all the meetings that are happening and the room that they are in.
3. Keep track of the number of times each room is used in an array.
4. With each meeting, check if there are any free rooms.
   If there are, then use the room with the smallest number.
   Otherwise, assign the meeting to the room whose meeting will end the soonest.
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
int mostBooked(int n, int** meetings, int meetingsSize, int* meetingsColSize) {
    int retVal = 0;

    //
    qsort(meetings, meetingsSize, sizeof(meetings[0]), compareIntArray);

    //
    long long roomAvailabilityTime[n];
    memset(roomAvailabilityTime, 0, sizeof(roomAvailabilityTime));

    int meetingCount[n];
    memset(meetingCount, 0, sizeof(meetingCount));

    long long minRoomAvailabilityTime;
    int minAvailableTimeRoom;
    bool foundUnusedRoom;
    int start, end;

    int i, j;
    for (i = 0; i < meetingsSize; ++i) {
        start = meetings[i][0];
        end = meetings[i][1];

        minRoomAvailabilityTime = LLONG_MAX;
        minAvailableTimeRoom = 0;
        foundUnusedRoom = false;

        for (j = 0; j < n; ++j) {
            if (roomAvailabilityTime[j] <= start) {
                foundUnusedRoom = true;
                meetingCount[j]++;
                roomAvailabilityTime[j] = end;
                break;
            }

            if (minRoomAvailabilityTime > roomAvailabilityTime[j]) {
                minRoomAvailabilityTime = roomAvailabilityTime[j];
                minAvailableTimeRoom = j;
            }
        }

        if (foundUnusedRoom == false) {
            roomAvailabilityTime[minAvailableTimeRoom] += (end - start);
            meetingCount[minAvailableTimeRoom]++;
        }
    }

    //
    int maxMeetingCount = 0;
    int maxMeetingCountRoom = 0;
    for (i = 0; i < n; i++) {
        if (meetingCount[i] > maxMeetingCount) {
            maxMeetingCount = meetingCount[i];
            maxMeetingCountRoom = i;
        }
    }
    retVal = maxMeetingCountRoom;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        int retVal = 0;

        sort(meetings.begin(), meetings.end());

        vector<long long> roomAvailabilityTime(n, 0);
        vector<int> meetingCount(n, 0);
        for (auto& meeting : meetings) {
            int start = meeting[0];
            int end = meeting[1];

            long long minRoomAvailabilityTime = numeric_limits<long long>::max();
            int minAvailableTimeRoom = 0;
            bool foundUnusedRoom = false;

            for (int i = 0; i < n; i++) {
                if (roomAvailabilityTime[i] <= start) {
                    foundUnusedRoom = true;
                    meetingCount[i]++;
                    roomAvailabilityTime[i] = end;
                    break;
                }

                if (minRoomAvailabilityTime > roomAvailabilityTime[i]) {
                    minRoomAvailabilityTime = roomAvailabilityTime[i];
                    minAvailableTimeRoom = i;
                }
            }

            if (foundUnusedRoom == false) {
                roomAvailabilityTime[minAvailableTimeRoom] += end - start;
                meetingCount[minAvailableTimeRoom]++;
            }
        }

        int maxMeetingCount = 0;
        int maxMeetingCountRoom = 0;
        for (int i = 0; i < n; i++) {
            if (meetingCount[i] > maxMeetingCount) {
                maxMeetingCount = meetingCount[i];
                maxMeetingCountRoom = i;
            }
        }
        retVal = maxMeetingCountRoom;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def mostBooked(self, n: int, meetings: List[List[int]]) -> int:
        retVal = 0

        meetings = sorted(meetings)

        room_availability_time = [0] * n
        meeting_count = [0] * n
        for start, end in meetings:
            min_room_availability_time = float('inf')
            min_available_time_room = 0
            found_unused_room = False

            for i in range(n):
                if room_availability_time[i] <= start:
                    found_unused_room = True
                    meeting_count[i] += 1
                    room_availability_time[i] = end
                    break

                if min_room_availability_time > room_availability_time[i]:
                    min_room_availability_time = room_availability_time[i]
                    min_available_time_room = i

            if found_unused_room is False:
                room_availability_time[min_available_time_room] += end - start
                meeting_count[min_available_time_room] += 1

        retVal = meeting_count.index(max(meeting_count))

        return retVal
```

</details>

## [2418. Sort the People](https://leetcode.com/problems/sort-the-people/)  1193

- [Official](https://leetcode.cn/problems/sort-the-people/solutions/2242694/an-shen-gao-pai-xu-by-leetcode-solution-p6bk/)

<details><summary>Description</summary>

```text
You are given an array of strings names, and an array heights that consists of distinct positive integers.
Both arrays are of length n.

For each index i, names[i] and heights[i] denote the name and height of the ith person.

Return names sorted in descending order by the people's heights.

Example 1:
Input: names = ["Mary","John","Emma"], heights = [180,165,170]
Output: ["Mary","Emma","John"]
Explanation: Mary is the tallest, followed by Emma and John.

Example 2:
Input: names = ["Alice","Bob","Bob"], heights = [155,185,150]
Output: ["Bob","Alice","Bob"]
Explanation: The first Bob is the tallest, followed by Alice and the second Bob.

Constraints:
n == names.length == heights.length
1 <= n <= 10^3
1 <= names[i].length <= 20
1 <= heights[i] <= 10^5
names[i] consists of lower and upper case English letters.
All the values of heights are distinct.
```

<details><summary>Hint</summary>

```text
1. Find the tallest person and swap with the first person,
   then find the second tallest person and swap with the second person, etc.
   Repeat until you fix all n people.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareIntArray(const void* a1, const void* a2) {
    int* p1 = (int*)a1;
    int* p2 = (int*)a2;

    // descending order
    return (p1[0] < p2[0]);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** sortPeople(char** names, int namesSize, int* heights, int heightsSize, int* returnSize) {
    char** pRetVal = NULL;

    (*returnSize) = namesSize;
    pRetVal = (char**)malloc((*returnSize) * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }

    int id[(*returnSize)][2];
    int i;
    for (i = 0; i < (*returnSize); ++i) {
        id[i][0] = heights[i];
        id[i][1] = i;
    }
    qsort(id, (*returnSize), sizeof(id[0]), compareIntArray);
    for (i = 0; i < (*returnSize); ++i) {
        pRetVal[i] = names[id[i][1]];
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<string> sortPeople(vector<string>& names, vector<int>& heights) {
        vector<string> retVal;

        int namesSize = names.size();
        int id[namesSize];
        iota(id, id + namesSize, 0);
        sort(id, id + namesSize, [&](const auto& x, const auto& y) {
            // descending order
            return (heights[x] > heights[y]);
        });

        for (int i = 0; i < namesSize; ++i) {
            retVal.emplace_back(names[id[i]]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def sortPeople(self, names: List[str], heights: List[int]) -> List[str]:
        retVal = []

        retVal = [name for _, name in sorted(zip(heights, names), reverse=True)]

        return retVal
```

</details>

## [2706. Buy Two Chocolates](https://leetcode.com/problems/buy-two-chocolates/)  1207

- [Official](https://leetcode.com/problems/buy-two-chocolates/editorial/)

<details><summary>Description</summary>

```text
You are given an integer array prices representing the prices of various chocolates in a store.
You are also given a single integer money, which represents your initial amount of money.

You must buy exactly two chocolates in such a way that you still have some non-negative leftover money.
You would like to minimize the sum of the prices of the two chocolates you buy.

Return the amount of money you will have leftover after buying the two chocolates.
If there is no way for you to buy two chocolates without ending up in debt, return money.
Note that the leftover must be non-negative.

Example 1:
Input: prices = [1,2,2], money = 3
Output: 0
Explanation: Purchase the chocolates priced at 1 and 2 units respectively.
You will have 3 - 3 = 0 units of money afterwards. Thus, we return 0.

Example 2:
Input: prices = [3,2,3], money = 3
Output: 3
Explanation: You cannot buy 2 chocolates without going in debt, so we return 3.

Constraints:
2 <= prices.length <= 50
1 <= prices[i] <= 100
1 <= money <= 100
```

<details><summary>Hint</summary>

```text
1. Sort the array and check if the money is more than or equal to the sum of the two cheapest elements.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int buyChoco(int* prices, int pricesSize, int money) {
    int retVal = money;

    qsort(prices, pricesSize, sizeof(int), compareInteger);
    int leftover = money - (prices[0] + prices[1]);
    if (leftover >= 0) {
        retVal = leftover;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int buyChoco(vector<int>& prices, int money) {
        int retVal = money;

        sort(prices.begin(), prices.end());
        int leftover = money - (prices[0] + prices[1]);
        if (leftover >= 0) {
            retVal = leftover;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def buyChoco(self, prices: List[int], money: int) -> int:
        retVal = money

        prices.sort()
        leftover = money - (prices[0] + prices[1])
        if leftover >= 0:
            retVal = leftover

        return retVal
```

</details>

## [2785. Sort Vowels in a String](https://leetcode.com/problems/sort-vowels-in-a-string/description/)  1266

- [Official](https://leetcode.com/problems/sort-vowels-in-a-string/editorial/)

<details><summary>Description</summary>

```text
Given a 0-indexed string s, permute s to get a new string t such that:
- All consonants remain in their original places. More formally,
  if there is an index i with 0 <= i < s.length such that s[i] is a consonant, then t[i] = s[i].
- The vowels must be sorted in the nondecreasing order of their ASCII values.
  More formally, for pairs of indices i, j with 0 <= i < j < s.length such that s[i] and s[j] are vowels,
  then t[i] must not have a higher ASCII value than t[j].
Return the resulting string.

The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in lowercase or uppercase.
Consonants comprise all letters that are not vowels.

Example 1:
Input: s = "lEetcOde"
Output: "lEOtcede"
Explanation: 'E', 'O', and 'e' are the vowels in s; 'l', 't', 'c', and 'd' are all consonants.
The vowels are sorted according to their ASCII values, and the consonants remain in the same places.

Example 2:
Input: s = "lYmpH"
Output: "lYmpH"
Explanation: There are no vowels in s (all characters in s are consonants), so we return "lYmpH".

Constraints:
1 <= s.length <= 10^5
s consists only of letters of the English alphabet in uppercase and lowercase.
```

<details><summary>Hint</summary>

```text
1. Add all the vowels in an array and sort the array.
2. Replace characters in string s if it's a vowel from the new array.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareChar(const void* c1, const void* c2) {
    // ascending order
    return (*(char*)c1 > *(char*)c2);
}
char* sortVowels(char* s) {
    char* pRetVal = s;

    int sSize = strlen(s);
    int i;

    char vowels[sSize];
    memset(vowels, 0, sizeof(vowels));
    unsigned int vowelsIndex = 0;
    for (i = 0; i < sSize; ++i) {
        if ((s[i] == 'A') || (s[i] == 'E') || (s[i] == 'I') || (s[i] == 'O') || (s[i] == 'U') || (s[i] == 'a') ||
            (s[i] == 'e') || (s[i] == 'i') || (s[i] == 'o') || (s[i] == 'u')) {
            vowels[vowelsIndex++] = s[i];
        }
    }
    if (vowelsIndex == 0) {
        return pRetVal;
    }
    qsort(vowels, vowelsIndex, sizeof(char), compareChar);

    vowelsIndex = 0;
    for (i = 0; i < sSize; ++i) {
        if ((s[i] == 'A') || (s[i] == 'E') || (s[i] == 'I') || (s[i] == 'O') || (s[i] == 'U') || (s[i] == 'a') ||
            (s[i] == 'e') || (s[i] == 'i') || (s[i] == 'o') || (s[i] == 'u')) {
            pRetVal[i] = vowels[vowelsIndex++];
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
    string sortVowels(string s) {
        string retVal;

        vector<char> vowels;
        for (char c : s) {
            if ((c == 'A') || (c == 'E') || (c == 'I') || (c == 'O') || (c == 'U') || (c == 'a') || (c == 'e') ||
                (c == 'i') || (c == 'o') || (c == 'u')) {
                vowels.emplace_back(c);
            }
        }
        sort(vowels.begin(), vowels.end());

        int idx = 0;
        for (char c : s) {
            if ((c == 'A') || (c == 'E') || (c == 'I') || (c == 'O') || (c == 'U') || (c == 'a') || (c == 'e') ||
                (c == 'i') || (c == 'o') || (c == 'u')) {
                retVal += vowels[idx++];
            } else {
                retVal += c;
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
    def sortVowels(self, s: str) -> str:
        retVal = ""

        vowels = []
        for c in s:
            if c in "AEIOUaeiou":
                vowels.append(c)
        vowels.sort()

        idx = 0
        for key, value in enumerate(s):
            if value in "AEIOUaeiou":
                retVal += vowels[idx]
                idx += 1
            else:
                retVal += value

        return retVal
```

</details>

## [2948. Make Lexicographically Smallest Array by Swapping Elements](https://leetcode.com/problems/make-lexicographically-smallest-array-by-swapping-elements/)  2047

- [Official](https://leetcode.com/problems/make-lexicographically-smallest-array-by-swapping-elements/editorial/)

<details><summary>Description</summary>

```text
You are given a 0-indexed array of positive integers nums and a positive integer limit.

In one operation, you can choose any two indices i and j and swap nums[i] and nums[j] if |nums[i] - nums[j]| <= limit.

Return the lexicographically smallest array that can be obtained by performing the operation any number of times.

An array a is lexicographically smaller than an array b if in the first position where a and b differ,
array a has an element that is less than the corresponding element in b.
For example, the array [2,10,3] is lexicographically smaller than the array [10,2,3]
because they differ at index 0 and 2 < 10.

Example 1:
Input: nums = [1,5,3,9,8], limit = 2
Output: [1,3,5,8,9]
Explanation: Apply the operation 2 times:
- Swap nums[1] with nums[2]. The array becomes [1,3,5,9,8]
- Swap nums[3] with nums[4]. The array becomes [1,3,5,8,9]
We cannot obtain a lexicographically smaller array by applying any more operations.
Note that it may be possible to get the same result by doing different operations.

Example 2:
Input: nums = [1,7,6,18,2,1], limit = 3
Output: [1,6,7,18,1,2]
Explanation: Apply the operation 3 times:
- Swap nums[1] with nums[2]. The array becomes [1,6,7,18,2,1]
- Swap nums[0] with nums[4]. The array becomes [2,6,7,18,1,1]
- Swap nums[0] with nums[5]. The array becomes [1,6,7,18,1,2]
We cannot obtain a lexicographically smaller array by applying any more operations.

Example 3:
Input: nums = [1,7,28,19,10], limit = 3
Output: [1,7,28,19,10]
Explanation: [1,7,28,19,10] is the lexicographically smallest array
we can obtain because we cannot apply the operation on any two indices.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
1 <= limit <= 10^9
```

<details><summary>Hint</summary>

```text
1. Construct a virtual graph where all elements in nums are nodes
   and the pairs satisfying the condition have an edge between them.
2. Instead of constructing all edges, we only care about the connected components.
3. Can we use DSU?
4. Sort nums. Now we just need to consider if the consecutive elements have an edge to check
   if they belong to the same connected component.
   Hence, all connected components become a list of position-consecutive elements after sorting.
5. For each index of nums from 0 to nums.length - 1 we can change it to the current minimum value
   we have in its connected component and remove that value from the connected component.
```

</details>

</details>

<details><summary>C</summary>

```c
// https://leetcode.cn/problems/make-lexicographically-smallest-array-by-swapping-elements/solutions/2545365/c-by-awesome-ardinghelli-jqrs/
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
int compareStruct(const void *a, const void *b) {
    int pa = ((struct hashTable *)a)->value;
    int pb = ((struct hashTable *)b)->value;

    // ascending order
    return (pa > pb);
}
int compareInteger(const void *n1, const void *n2) {
    // ascending order
    return (*(int *)n1 > *(int *)n2);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *lexicographicallySmallestArray(int *nums, int numsSize, int limit, int *returnSize) {
    int *pRetVal = NULL;

    //
    (*returnSize) = 0;

    //
    pRetVal = (int *)calloc(numsSize, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }
    (*returnSize) = numsSize;

    //
    struct hashTable *pHashTable = NULL;
    struct hashTable *pTmp = NULL;
    for (int i = 0; i < numsSize; i++) {
        pTmp = NULL;
        pTmp = (struct hashTable *)malloc(sizeof(struct hashTable));
        if (pTmp == NULL) {
            perror("malloc");
            freeAll(pHashTable);
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        pTmp->key = i;
        pTmp->value = nums[i];
        HASH_ADD_INT(pHashTable, key, pTmp);
    }
    HASH_SORT(pHashTable, compareStruct);

    //
    int groupSize = (1e5);  // 1 <= nums.length <= 10^5
    int groupIndex[groupSize];
    memset(groupIndex, 0, sizeof(groupIndex));
    int group[groupSize];
    memset(group, 0, sizeof(group));
    int FirstNum = nums[0];
    int key = 0;
    struct hashTable *pCurrent = NULL;
    pTmp = NULL;
    HASH_ITER(hh, pHashTable, pCurrent, pTmp) {
        if (pCurrent->value - FirstNum > limit) {
            qsort(groupIndex, key, sizeof(groupIndex[0]), compareInteger);
            for (int i = 0; i < key; i++) {
                pRetVal[groupIndex[i]] = group[i];
            }
            key = 0;
        }
        group[key] = pCurrent->value;
        groupIndex[key++] = pCurrent->key;
        FirstNum = pCurrent->value;
    }

    //
    qsort(groupIndex, key, sizeof(groupIndex[0]), compareInteger);
    for (int i = 0; i < key; i++) {
        pRetVal[groupIndex[i]] = group[i];
    }

    //
    freeAll(pHashTable);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        vector<int> retVal = nums;

        int returnSize = retVal.size();

        vector<int> numsSorted(retVal);
        sort(numsSorted.begin(), numsSorted.end());

        int currGroup = 0;
        unordered_map<int, int> numToGroup;
        numToGroup.insert(pair<int, int>(numsSorted[0], currGroup));

        unordered_map<int, list<int>> groupToList;
        groupToList.insert(pair<int, list<int>>(currGroup, list<int>(1, numsSorted[0])));

        for (int i = 1; i < returnSize; i++) {
            if (abs(numsSorted[i] - numsSorted[i - 1]) > limit) {
                currGroup++;
            }
            numToGroup.insert(pair<int, int>(numsSorted[i], currGroup));

            if (groupToList.find(currGroup) == groupToList.end()) {
                groupToList[currGroup] = list<int>();
            }
            groupToList[currGroup].push_back(numsSorted[i]);
        }

        for (int i = 0; i < returnSize; i++) {
            int num = retVal[i];
            int group = numToGroup[num];
            retVal[i] = *groupToList[group].begin();
            groupToList[group].pop_front();
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def lexicographicallySmallestArray(self, nums: List[int], limit: int) -> List[int]:
        retVal = nums

        returnSize = len(retVal)
        numsSorted = sorted(retVal)

        currGroup = 0
        numToGroup = {}
        numToGroup[numsSorted[0]] = currGroup

        groupToList = {}
        groupToList[currGroup] = deque([numsSorted[0]])

        for i in range(1, returnSize):
            if abs(numsSorted[i] - numsSorted[i - 1]) > limit:
                currGroup += 1
            numToGroup[numsSorted[i]] = currGroup

            if currGroup not in groupToList:
                groupToList[currGroup] = deque()
            groupToList[currGroup].append(numsSorted[i])

        for i in range(returnSize):
            num = retVal[i]
            group = numToGroup[num]
            retVal[i] = groupToList[group].popleft()

        return retVal
```

</details>

## [3025. Find the Number of Ways to Place People I](https://leetcode.com/problems/find-the-number-of-ways-to-place-people-i/)  1707

- [Official](https://leetcode.com/problems/find-the-number-of-ways-to-place-people-i/editorial/)
- [Official](https://leetcode.cn/problems/find-the-number-of-ways-to-place-people-i/solutions/3764850/ren-yuan-zhan-wei-de-fang-an-shu-i-by-le-k2er/)

<details><summary>Description</summary>

```text
You are given a 2D array points of size n x 2 representing integer coordinates of some points on a 2D plane,
where points[i] = [xi, yi].

Count the number of pairs of points (A, B), where
- A is on the upper left side of B, and
- there are no other points in the rectangle (or line) they make (including the border).

Return the count.

Example 1:
Input: points = [[1,1],[2,2],[3,3]]
Output: 0
Explanation:
- There is no way to choose A and B so A is on the upper left side of B.

Example 2:
Input: points = [[6,2],[4,4],[2,6]]
Output: 2
Explanation:
- The left one is the pair (points[1], points[0]),
  where points[1] is on the upper left side of points[0] and the rectangle is empty.
- The middle one is the pair (points[2], points[1]), same as the left one it is a valid pair.
- The right one is the pair (points[2], points[0]), where points[2] is on the upper left side of points[0],
  but points[1] is inside the rectangle so it's not a valid pair.

Example 3:
Input: points = [[3,1],[1,3],[1,1]]
Output: 2
Explanation:
- The left one is the pair (points[2], points[0]),
  where points[2] is on the upper left side of points[0] and there are no other points on the line they form.
  Note that it is a valid state when the two points form a line.
- The middle one is the pair (points[1], points[2]), it is a valid pair same as the left one.
  The right one is the pair (points[1], points[0]),
  it is not a valid pair as points[2] is on the border of the rectangle.

Constraints:
2 <= n <= 50
points[i].length == 2
0 <= points[i][0], points[i][1] <= 50
All points[i] are distinct.
```

<details><summary>Hint</summary>

```text
1. We can enumerate all the upper-left and lower-right corners.
2. If the upper-left corner is (x1, y1) and lower-right corner is (x2, y2),
   check that there is no point (x, y) such that x1 <= x <= x2 and y2 <= y <= y1.
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
        return (p1[1] < p2[1]);
    }
    return (p1[0] > p2[0]);
}
int numberOfPairs(int** points, int pointsSize, int* pointsColSize) {
    int retVal = 0;

    qsort(points, pointsSize, sizeof(int*), compareIntArray);

    int *pointA, *pointB;
    int xMin, xMax, yMin, yMax;
    for (int i = 0; i < pointsSize - 1; i++) {
        pointA = points[i];
        xMin = pointA[0] - 1;
        xMax = INT_MAX;
        yMin = INT_MIN;
        yMax = pointA[1] + 1;

        for (int j = i + 1; j < pointsSize; j++) {
            pointB = points[j];
            if ((pointB[0] > xMin) && (pointB[0] < xMax) && (pointB[1] > yMin) && (pointB[1] < yMax)) {
                retVal++;
                xMin = pointB[0];
                yMin = pointB[1];
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
    int numberOfPairs(vector<vector<int>>& points) {
        int retVal = 0;

        sort(points.begin(), points.end(), [](const vector<int>& x, const vector<int>& y) {
            // ascending order
            if (x[0] == y[0]) {
                return (x[1] > y[1]);
            }
            return (x[0] < y[0]);
        });

        int pointsSize = points.size();
        for (int i = 0; i < pointsSize - 1; i++) {
            const auto& pointA = points[i];
            int xMin = pointA[0] - 1;
            int xMax = numeric_limits<int>::max();
            int yMin = numeric_limits<int>::min();
            int yMax = pointA[1] + 1;

            for (int j = i + 1; j < pointsSize; j++) {
                const auto& pointB = points[j];
                if ((pointB[0] > xMin) && (pointB[0] < xMax) && (pointB[1] > yMin) && (pointB[1] < yMax)) {
                    retVal++;
                    xMin = pointB[0];
                    yMin = pointB[1];
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
    def numberOfPairs(self, points: List[List[int]]) -> int:
        retVal = 0

        points.sort(key=lambda point: (point[0], -point[1]))

        for i in range(len(points) - 1):
            pointA = points[i]
            xMin = pointA[0] - 1
            xMax = inf
            yMin = -inf
            yMax = pointA[1] + 1

            for j in range(i + 1, len(points)):
                pointB = points[j]
                if ((pointB[0] > xMin) and (pointB[0] < xMax) and (pointB[1] > yMin) and (pointB[1] < yMax)):
                    retVal += 1
                    xMin = pointB[0]
                    yMin = pointB[1]

        return retVal
```

</details>

## [3027. Find the Number of Ways to Place People II](https://leetcode.com/problems/find-the-number-of-ways-to-place-people-ii/)  2020

- [Official](https://leetcode.com/problems/find-the-number-of-ways-to-place-people-ii/editorial/)
- [Official](https://leetcode.cn/problems/find-the-number-of-ways-to-place-people-ii/solutions/3764851/ren-yuan-zhan-wei-de-fang-an-shu-ii-by-l-5ors/)

<details><summary>Description</summary>

```text
You are given a 2D array points of size n x 2 representing integer coordinates of some points on a 2D-plane,
where points[i] = [xi, yi].

We define the right direction as positive x-axis (increasing x-coordinate)
and the left direction as negative x-axis (decreasing x-coordinate).
Similarly, we define the up direction as positive y-axis (increasing y-coordinate)
and the down direction as negative y-axis (decreasing y-coordinate)

You have to place n people, including Alice and Bob,
at these points such that there is exactly one person at every point.
Alice wants to be alone with Bob,
so Alice will build a rectangular fence with Alice's position as the upper left corner
and Bob's position as the lower right corner of the fence
(Note that the fence might not enclose any area, i.e. it can be a line).
If any person other than Alice and Bob is either inside the fence or on the fence, Alice will be sad.

Return the number of pairs of points where you can place Alice and Bob,
such that Alice does not become sad on building the fence.

Note that Alice can only build a fence with Alice's position as the upper left corner,
and Bob's position as the lower right corner.
For example, Alice cannot build either of the fences in the picture below
with four corners (1, 1), (1, 3), (3, 1), and (3, 3), because:
- With Alice at (3, 3) and Bob at (1, 1),
  Alice's position is not the upper left corner and Bob's position is not the lower right corner of the fence.
- With Alice at (1, 3) and Bob at (1, 1), Bob's position is not the lower right corner of the fence.

Example 1:
Input: points = [[1,1],[2,2],[3,3]]
Output: 0
Explanation: There is no way to place Alice and Bob such that Alice can build a fence
with Alice's position as the upper left corner and Bob's position as the lower right corner. Hence we return 0.

Example 2:
Input: points = [[6,2],[4,4],[2,6]]
Output: 2
Explanation: There are two ways to place Alice and Bob such that Alice will not be sad:
- Place Alice at (4, 4) and Bob at (6, 2).
- Place Alice at (2, 6) and Bob at (4, 4).
You cannot place Alice at (2, 6) and Bob at (6, 2) because the person at (4, 4) will be inside the fence.

Example 3:
Input: points = [[3,1],[1,3],[1,1]]
Output: 2
Explanation: There are two ways to place Alice and Bob such that Alice will not be sad:
- Place Alice at (1, 1) and Bob at (3, 1).
- Place Alice at (1, 3) and Bob at (1, 1).
You cannot place Alice at (1, 3) and Bob at (3, 1) because the person at (1, 1) will be on the fence.
Note that it does not matter if the fence encloses any area, the first and second fences in the image are valid.

Constraints:
2 <= n <= 1000
points[i].length == 2
-10^9 <= points[i][0], points[i][1] <= 10^9
All points[i] are distinct.
```

<details><summary>Hint</summary>

```text
1. Sort the points by x-coordinate in non-decreasing order and break the tie
   by sorting the y-coordinate in non-increasing order.
2. Now consider two points upper-left corner points[i] and lower-right corner points[j],
   such that i < j and points[i][0] <= points[j][0] and points[i][1] >= points[j][1].
3. Instead of brute force looping, we can save the largest y-coordinate that is no larger than points[i][1]
   when looping on j, say the value is m. And if m < points[j][1], the upper-left and lower-right corner pair is valid.
4. The actual values don’t matter, we can compress all x-coordinates and y-coordinates to the range [1, n].
   Can we use prefix sum now?
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
        return (p1[1] < p2[1]);
    }
    return (p1[0] > p2[0]);
}
int numberOfPairs(int** points, int pointsSize, int* pointsColSize) {
    int retVal = 0;

    qsort(points, pointsSize, sizeof(int*), compareIntArray);

    int *pointA, *pointB;
    int xMin, xMax, yMin, yMax;
    for (int i = 0; i < pointsSize - 1; i++) {
        pointA = points[i];
        xMin = pointA[0] - 1;
        xMax = INT_MAX;
        yMin = INT_MIN;
        yMax = pointA[1] + 1;

        for (int j = i + 1; j < pointsSize; j++) {
            pointB = points[j];
            if ((pointB[0] > xMin) && (pointB[0] < xMax) && (pointB[1] > yMin) && (pointB[1] < yMax)) {
                retVal++;
                xMin = pointB[0];
                yMin = pointB[1];
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
    int numberOfPairs(vector<vector<int>>& points) {
        int retVal = 0;

        sort(points.begin(), points.end(), [](const vector<int>& x, const vector<int>& y) {
            // ascending order
            if (x[0] == y[0]) {
                return (x[1] > y[1]);
            }
            return (x[0] < y[0]);
        });

        int pointsSize = points.size();
        for (int i = 0; i < pointsSize - 1; i++) {
            const auto& pointA = points[i];
            int xMin = pointA[0] - 1;
            int xMax = numeric_limits<int>::max();
            int yMin = numeric_limits<int>::min();
            int yMax = pointA[1] + 1;

            for (int j = i + 1; j < pointsSize; j++) {
                const auto& pointB = points[j];
                if ((pointB[0] > xMin) && (pointB[0] < xMax) && (pointB[1] > yMin) && (pointB[1] < yMax)) {
                    retVal++;
                    xMin = pointB[0];
                    yMin = pointB[1];
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
    def numberOfPairs(self, points: List[List[int]]) -> int:
        retVal = 0

        points.sort(key=lambda point: (point[0], -point[1]))

        for i in range(len(points) - 1):
            pointA = points[i]
            xMin = pointA[0] - 1
            xMax = inf
            yMin = -inf
            yMax = pointA[1] + 1

            for j in range(i + 1, len(points)):
                pointB = points[j]
                if ((pointB[0] > xMin) and (pointB[0] < xMax) and (pointB[1] > yMin) and (pointB[1] < yMax)):
                    retVal += 1
                    xMin = pointB[0]
                    yMin = pointB[1]

        return retVal
```

</details>

## [3169. Count Days Without Meetings](https://leetcode.com/problems/count-days-without-meetings/)  1483

- [Official](https://leetcode.com/problems/count-days-without-meetings/editorial/)

<details><summary>Description</summary>

```text
You are given a positive integer days
representing the total number of days an employee is available for work (starting from day 1).
You are also given a 2D array meetings of size n where, meetings[i] = [start_i, end_i]
represents the starting and ending days of meeting i (inclusive).

Return the count of days when the employee is available for work but no meetings are scheduled.

Note: The meetings may overlap.

Example 1:
Input: days = 10, meetings = [[5,7],[1,3],[9,10]]
Output: 2
Explanation:
There is no meeting scheduled on the 4th and 8th days.

Example 2:
Input: days = 5, meetings = [[2,4],[1,3]]
Output: 1
Explanation:
There is no meeting scheduled on the 5th day.

Example 3:
Input: days = 6, meetings = [[1,6]]
Output: 0
Explanation:
Meetings are scheduled for all working days.

Constraints:
1 <= days <= 10^9
1 <= meetings.length <= 10^5
meetings[i].length == 2
1 <= meetings[i][0] <= meetings[i][1] <= days
```

<details><summary>Hint</summary>

```text
1. Merge the overlapping meetings and sort the new meetings timings.
2. Return the sum of difference between the end time of a meeting
   and the start time of the next meeting for all adjacent pairs.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareIntArray(const void *a1, const void *a2) {
    const int *p1 = *(const int **)a1;
    const int *p2 = *(const int **)a2;

    // ascending order
    if (p1[0] == p2[0]) {
        return (p1[1] > p2[1]);
    }

    return (p1[0] > p2[0]);
}
int countDays(int days, int **meetings, int meetingsSize, int *meetingsColSize) {
    int retVal = 0;

    qsort(meetings, meetingsSize, sizeof(meetings[0]), compareIntArray);

    int latestEnd = 0;
    for (int i = 0; i < meetingsSize; ++i) {
        int start = meetings[i][0];
        int end = meetings[i][1];

        // Add current range of days without a meeting
        if (start > latestEnd + 1) {
            retVal += start - latestEnd - 1;
        }

        // Update latest meeting end
        latestEnd = fmax(latestEnd, end);
    }

    // Add all days after the last day of meetings
    retVal += days - latestEnd;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int countDays(int days, vector<vector<int>>& meetings) {
        int retVal = 0;

        sort(meetings.begin(), meetings.end());

        int latestEnd = 0;
        for (auto& meeting : meetings) {
            int start = meeting[0];
            int end = meeting[1];

            // Add current range of days without a meeting
            if (start > latestEnd + 1) {
                retVal += start - latestEnd - 1;
            }

            // Update latest meeting end
            latestEnd = max(latestEnd, end);
        }

        // Add all days after the last day of meetings
        retVal += days - latestEnd;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def countDays(self, days: int, meetings: List[List[int]]) -> int:
        retVal = 0

        meetings.sort()

        latestEnd = 0
        for start, end in meetings:
            # Add current range of days without a meeting
            if start > latestEnd + 1:
                retVal += start - latestEnd - 1

            # Update latest meeting end
            latestEnd = max(latestEnd, end)

        # Add all days after the last day of meetings
        retVal += days - latestEnd

        return retVal
```

</details>

## [3394. Check if Grid can be Cut into Sections](https://leetcode.com/problems/check-if-grid-can-be-cut-into-sections/)  1916

- [Official](https://leetcode.com/problems/check-if-grid-can-be-cut-into-sections/editorial/)

<details><summary>Description</summary>

```text
You are given an integer n representing the dimensions of an n x n grid,
with the origin at the bottom-left corner of the grid.
You are also given a 2D array of coordinates rectangles,
where rectangles[i] is in the form [startx, starty, endx, endy],
representing a rectangle on the grid. Each rectangle is defined as follows:
- (startx, starty): The bottom-left corner of the rectangle.
- (endx, endy): The top-right corner of the rectangle.

Note that the rectangles do not overlap.
Your task is to determine if it is possible to make either two horizontal or two vertical cuts on the grid such that:
- Each of the three resulting sections formed by the cuts contains at least one rectangle.
- Every rectangle belongs to exactly one section.

Return true if such cuts can be made; otherwise, return false.

Example 1:
Input: n = 5, rectangles = [[1,0,5,2],[0,2,2,4],[3,2,5,3],[0,4,4,5]]
Output: true
Explanation:
The grid is shown in the diagram. We can make horizontal cuts at y = 2 and y = 4. Hence, output is true.

Example 2:
Input: n = 4, rectangles = [[0,0,1,1],[2,0,3,4],[0,2,2,3],[3,0,4,3]]
Output: true
Explanation:
We can make vertical cuts at x = 2 and x = 3. Hence, output is true.

Example 3:
Input: n = 4, rectangles = [[0,2,2,4],[1,0,3,2],[2,2,3,4],[3,0,4,2],[3,2,4,4]]
Output: false
Explanation:
We cannot make two horizontal or two vertical cuts that satisfy the conditions. Hence, output is false.

Constraints:
3 <= n <= 10^9
3 <= rectangles.length <= 10^5
0 <= rectangles[i][0] < rectangles[i][2] <= n
0 <= rectangles[i][1] < rectangles[i][3] <= n
No two rectangles overlap.
```

<details><summary>Hint</summary>

```text
1. For each rectangle, consider ranges [start_x, end_x] and [start_y, end_y] separately.
2. For x and y directions, check whether we can split it into 3 parts.
```

</details>

</details>

<details><summary>C</summary>

```c
// https://leetcode.com/problems/check-if-grid-can-be-cut-into-sections/solutions/6575954/sorting-python-c-java-js-c-go-rust-kotlin-swift/
typedef struct {
    int start;
    int end;
} pair;
int compareStruct(const void *a, const void *b) {
    int pa = ((pair *)a)->start;
    int pb = ((pair *)b)->start;

    // ascending order
    return (pa > pb);
}
bool check(pair *intervals, int intervalsSize) {
    bool retVal = false;

    qsort(intervals, intervalsSize, sizeof(pair), compareStruct);

    int sections = 0;
    int maxEnd = intervals[0].end;
    int start, end;
    for (int i = 0; i < intervalsSize; ++i) {
        start = intervals[i].start;
        end = intervals[i].end;
        if (maxEnd <= start) {
            sections++;
        }
        maxEnd = fmax(maxEnd, end);
    }
    retVal = (sections >= 2);

    return retVal;
}
bool checkValidCuts(int n, int **rectangles, int rectanglesSize, int *rectanglesColSize) {
    bool retVal = false;

    pair *pXintervals = malloc(rectanglesSize * sizeof(pair));
    if (pXintervals == NULL) {
        perror("malloc");
        return retVal;
    }
    pair *pYintervals = malloc(rectanglesSize * sizeof(pair));
    if (pYintervals == NULL) {
        perror("malloc");
        free(pXintervals);
        pXintervals = NULL;
        return retVal;
    }
    for (int i = 0; i < rectanglesSize; ++i) {
        pXintervals[i].start = rectangles[i][0];
        pXintervals[i].end = rectangles[i][2];
        pYintervals[i].start = rectangles[i][1];
        pYintervals[i].end = rectangles[i][3];
    }
    retVal = check(pXintervals, rectanglesSize) || check(pYintervals, rectanglesSize);

    //
    free(pXintervals);
    pXintervals = NULL;
    free(pYintervals);
    pYintervals = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    bool checkCuts(vector<vector<int>>& rectangles, int dim) {
        bool retVal = false;

        // Sort rectangles by their starting coordinate in the given dimension
        sort(rectangles.begin(), rectangles.end(), [dim](const vector<int>& a, const vector<int>& b) {
            //
            return a[dim] < b[dim];
        });

        // Track the furthest ending coordinate seen so far
        int furthestEnd = rectangles[0][dim + 2];
        int gapCount = 0;
        for (size_t i = 1; i < rectangles.size(); i++) {
            vector<int>& rect = rectangles[i];
            // If current rectangle starts after the furthest end we've seen, we found a gap where a cut can be made
            if (furthestEnd <= rect[dim]) {
                gapCount++;
            }
            // Update the furthest ending coordinate
            furthestEnd = max(furthestEnd, rect[dim + 2]);
        }

        // We need at least 2 gaps to create 3 sections
        retVal = (gapCount >= 2);

        return retVal;
    }

   public:
    bool checkValidCuts(int n, vector<vector<int>>& rectangles) {
        bool retVal = false;

        // Try both horizontal and vertical cuts
        retVal = checkCuts(rectangles, 0) || checkCuts(rectangles, 1);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def checkCuts(self, rectangles: list[list[int]], dim: int) -> bool:
        retVal = False

        # Sort rectangles by their starting coordinate in the given dimension
        rectangles.sort(key=lambda rect: rect[dim])

        furthestEnd = rectangles[0][dim + 2]  # Track the furthest ending coordinate seen so far
        gapCount = 0
        for i in range(1, len(rectangles)):
            rect = rectangles[i]
            # If current rectangle starts after the furthest end we've seen, we found a gap where a cut can be made
            if furthestEnd <= rect[dim]:
                gapCount += 1
            # Update the furthest ending coordinate
            furthestEnd = max(furthestEnd, rect[dim + 2])

        # We need at least 2 gaps to create 3 sections
        retVal = (gapCount >= 2)

        return retVal

    def checkValidCuts(self, n: int, rectangles: List[List[int]]) -> bool:
        retVal = False

        # Try both horizontal and vertical cuts
        retVal = self.checkCuts(rectangles, 0) or self.checkCuts(rectangles, 1)

        return retVal
```

</details>

## [3433. Count Mentions Per User](https://leetcode.com/problems/count-mentions-per-user/)  1745

- [Official](https://leetcode.com/problems/count-mentions-per-user/editorial/)
- [Official](https://leetcode.cn/problems/count-mentions-per-user/solutions/3851672/tong-ji-yong-hu-bei-ti-ji-qing-kuang-by-36og5/)

<details><summary>Description</summary>

```text
You are given an integer numberOfUsers representing the total number of users and an array events of size n x 3.

Each events[i] can be either of the following two types:

1. Message Event: ["MESSAGE", "timestampi", "mentions_stringi"]
   - This event indicates that a set of users was mentioned in a message at timestampi.
   - The mentions_stringi string can contain one of the following tokens:
     - id<number>: where <number> is an integer in range [0,numberOfUsers - 1].
       There can be multiple ids separated by a single whitespace and may contain duplicates.
       This can mention even the offline users.
     - ALL: mentions all users.
     - HERE: mentions all online users.
2. Offline Event: ["OFFLINE", "timestampi", "idi"]
   - This event indicates that the user idi had become offline at timestampi for 60 time units.
     The user will automatically be online again at time timestampi + 60.

Return an array mentions where mentions[i]
represents the number of mentions the user with id i has across all MESSAGE events.

All users are initially online, and if a user goes offline or comes back online,
their status change is processed before handling any message event that occurs at the same timestamp.

Note that a user can be mentioned multiple times in a single message event,
and each mention should be counted separately.

Example 1:
Input: numberOfUsers = 2, events = [["MESSAGE","10","id1 id0"],["OFFLINE","11","0"],["MESSAGE","71","HERE"]]
Output: [2,2]
Explanation:
Initially, all users are online.
At timestamp 10, id1 and id0 are mentioned. mentions = [1,1]
At timestamp 11, id0 goes offline.
At timestamp 71, id0 comes back online and "HERE" is mentioned. mentions = [2,2]

Example 2:
Input: numberOfUsers = 2, events = [["MESSAGE","10","id1 id0"],["OFFLINE","11","0"],["MESSAGE","12","ALL"]]
Output: [2,2]
Explanation:
Initially, all users are online.
At timestamp 10, id1 and id0 are mentioned. mentions = [1,1]
At timestamp 11, id0 goes offline.
At timestamp 12, "ALL" is mentioned. This includes offline users, so both id0 and id1 are mentioned. mentions = [2,2]

Example 3:
Input: numberOfUsers = 2, events = [["OFFLINE","10","0"],["MESSAGE","12","HERE"]]
Output: [0,1]
Explanation:
Initially, all users are online.
At timestamp 10, id0 goes offline.
At timestamp 12, "HERE" is mentioned. Because id0 is still offline, they will not be mentioned. mentions = [0,1]

Constraints:
1 <= numberOfUsers <= 100
1 <= events.length <= 100
events[i].length == 3
events[i][0] will be one of MESSAGE or OFFLINE.
1 <= int(events[i][1]) <= 10^5
The number of id<number> mentions in any "MESSAGE" event is between 1 and 100.
0 <= <number> <= numberOfUsers - 1
It is guaranteed that the user id referenced in the OFFLINE event is online at the time the event occurs.
```

<details><summary>Hint</summary>

```text
1. Sort events by timestamp and then process each event.
2. Maintain two sets for offline and online user IDs.
```

</details>

</details>

<details><summary>C</summary>

```c
typedef struct {
    char type[8];
    int timestamp;
    char target[512];
} Event;
int compareEvents(const void* a, const void* b) {
    int retVal = 0;

    Event* e1 = (Event*)a;
    Event* e2 = (Event*)b;
    if (e1->timestamp != e2->timestamp) {
        retVal = e1->timestamp - e2->timestamp;
    } else {
        retVal = (strcmp(e1->type, "OFFLINE") == 0) ? (-1) : (1);
    }

    return retVal;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countMentions(int numberOfUsers, char*** events, int eventsSize, int* eventsColSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    Event* eventArr = (Event*)calloc(eventsSize, sizeof(Event));
    if (eventArr == NULL) {
        perror("calloc");
        return pRetVal;
    }
    for (int i = 0; i < eventsSize; i++) {
        strcpy(eventArr[i].type, events[i][0]);
        eventArr[i].timestamp = atoi(events[i][1]);
        strcpy(eventArr[i].target, events[i][2]);
    }
    qsort(eventArr, eventsSize, sizeof(Event), compareEvents);

    pRetVal = (int*)calloc(numberOfUsers, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        free(eventArr);
        return pRetVal;
    }

    int nextOnlineTime[numberOfUsers];
    memset(nextOnlineTime, 0, sizeof(nextOnlineTime));
    int curTime, idx;
    char *type, *target, *token;
    for (int i = 0; i < eventsSize; i++) {
        curTime = eventArr[i].timestamp;
        type = eventArr[i].type;
        target = eventArr[i].target;

        if (strcmp(type, "MESSAGE") == 0) {
            if (strcmp(target, "ALL") == 0) {
                for (int j = 0; j < numberOfUsers; j++) {
                    pRetVal[j]++;
                }
            } else if (strcmp(target, "HERE") == 0) {
                for (int j = 0; j < numberOfUsers; j++) {
                    if (nextOnlineTime[j] <= curTime) {
                        pRetVal[j]++;
                    }
                }
            } else {
                token = strtok(target, " ");
                while (token != NULL) {
                    idx = atoi(token + 2);
                    pRetVal[idx]++;
                    token = strtok(NULL, " ");
                }
            }
        } else {
            idx = atoi(target);
            nextOnlineTime[idx] = curTime + 60;
        }
    }
    (*returnSize) = numberOfUsers;

    //
    free(eventArr);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> countMentions(int numberOfUsers, vector<vector<string>>& events) {
        vector<int> retVal(numberOfUsers);

        sort(events.begin(), events.end(), [&](const vector<string>& lth, const vector<string>& rth) {
            bool ret = true;

            int lthTimestamp = stoi(lth[1]);
            int rthTimestamp = stoi(rth[1]);
            if (lthTimestamp != rthTimestamp) {
                ret = (lthTimestamp < rthTimestamp);
            } else if (rth[0] == "OFFLINE") {
                ret = false;
            }

            return ret;
        });

        vector<int> nextOnlineTime(numberOfUsers);
        for (auto&& event : events) {
            int curTime = stoi(event[1]);

            if (event[0] == "MESSAGE") {
                if (event[2] == "ALL") {
                    for (int i = 0; i < numberOfUsers; i++) {
                        retVal[i]++;
                    }
                } else if (event[2] == "HERE") {
                    for (int i = 0; i < numberOfUsers; i++) {
                        if (nextOnlineTime[i] <= curTime) {
                            retVal[i]++;
                        }
                    }
                } else {
                    int event2Size = event[2].size();
                    int idx = 0;
                    for (int i = 0; i < event2Size; i++) {
                        if (isdigit(event[2][i])) {
                            idx = idx * 10 + (event[2][i] - '0');
                        }
                        if ((i + 1 == event2Size) || (event[2][i + 1] == ' ')) {
                            retVal[idx]++;
                            idx = 0;
                        }
                    }
                }
            } else {
                int idx = stoi(event[2]);
                nextOnlineTime[idx] = curTime + 60;
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
    def countMentions(self, numberOfUsers: int, events: List[List[str]]) -> List[int]:
        retVal = [0] * numberOfUsers

        nextOnlineTime = [0] * numberOfUsers
        events.sort(key=lambda e: (int(e[1]), e[0] == "MESSAGE"))
        for event in events:
            curTime = int(event[1])

            if event[0] == "MESSAGE":
                if event[2] == "ALL":
                    for i in range(numberOfUsers):
                        retVal[i] += 1
                elif event[2] == "HERE":
                    for i, t in enumerate(nextOnlineTime):
                        if t <= curTime:
                            retVal[i] += 1
                else:
                    for idx in event[2].split():
                        retVal[int(idx[2:])] += 1
            else:
                nextOnlineTime[int(event[2])] = curTime + 60

        return retVal
```

</details>
