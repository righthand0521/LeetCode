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

- [Official](https://leetcode.com/problems/largest-number/solutions/127595/largest-number/)
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
    long digits1 = 10;
    while (digits1 <= *(int*)n1) {
        digits1 *= 10;
    }
    long digits2 = 10;
    while (digits2 <= *(int*)n2) {
        digits2 *= 10;
    }
    long comp1 = (*(int*)n2) * digits1 + (*(int*)n1);
    long comp2 = (*(int*)n1) * digits2 + (*(int*)n2);

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
        idx += snprintf(pRetVal + idx, returnSize - idx - 1, "%d", nums[i]);
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string largestNumber(vector<int>& nums) {
        string retVal;

        sort(nums.begin(), nums.end(), [](const int& n1, const int& n2) {
            /* Example
             *  43243 432
             *  43243: 43243000 +   432 = 43243432
             *    432: 43200000 + 43243 = 43243243
             *
             *  432 43200
             *    432: 43200000 + 43200 = 43243200
             *  43200: 43200000 +   432 = 43200432
             */
            long digits1 = 10;
            while (digits1 <= n1) {
                digits1 *= 10;
            }
            long digits2 = 10;
            while (digits2 <= n2) {
                digits2 *= 10;
            }
            long comp1 = n1 * digits2 + n2;
            long comp2 = n2 * digits1 + n1;

            return (comp1 > comp2);
        });

        // Input: nums = [0, 0], Output: "0".
        if (nums[0] == 0) {
            retVal = "0";
            return retVal;
        }

        for (auto num : nums) {
            retVal += to_string(num);
        }

        return retVal;
    }
};
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
#define MERGE_SORT (1)
#define QUICK_SORT (1)  // Time Limit Exceeded
#if (MERGE_SORT)
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
#elif (QUICK_SORT)
void quickSort(int* nums, int left, int right) {
    if (left >= right) {
        return;
    }

    int temp;
    int pivot = left;
    int leftIdx = left;
    int rightIdx = right;
    while (leftIdx < rightIdx) {
        while ((nums[leftIdx] <= nums[pivot]) && (leftIdx < right)) {
            leftIdx++;
        }

        while (nums[rightIdx] > nums[pivot]) {
            rightIdx--;
        }

        if (leftIdx < rightIdx) {
            temp = nums[leftIdx];
            nums[leftIdx] = nums[rightIdx];
            nums[rightIdx] = temp;
        }
    }
    temp = nums[pivot];
    nums[pivot] = nums[rightIdx];
    nums[rightIdx] = temp;

    quickSort(nums, left, rightIdx - 1);
    quickSort(nums, rightIdx + 1, right);
}
#endif
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortArray(int* nums, int numsSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = numsSize;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));
    memcpy(pRetVal, nums, ((*returnSize) * sizeof(int)));

#if (MERGE_SORT)
    printf("MERGE_SORT\n");
    mergeSort(pRetVal, 0, numsSize - 1);
#elif (QUICK_SORT)
    printf("QUICK_SORT\n");
    quickSort(pRetVal, 0, numsSize - 1);
#endif

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

## [976. Largest Perimeter Triangle](https://leetcode.com/problems/largest-perimeter-triangle/)  1340

<details><summary>Description</summary>

```text
Given an integer array nums, return the largest perimeter of a triangle with a non-zero area, formed from three of these lengths.
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

        // descending order
        sort(nums.begin(), nums.end(), greater<int>());
        for (long unsigned int i=0; i<nums.size()-2; ++i) {
            if (nums[i] < (nums[i+1] + nums[i+2])) {
                retVal = nums[i] + nums[i+1] + nums[i+2];
                break;
            }
        }

        return retVal;
    }
};
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

## [2554. Maximum Number of Integers to Choose From a Range I](https://leetcode.com/problems/maximum-number-of-integers-to-choose-from-a-range-i/)  1333

<details><summary>Description</summary>

```text
You are given an integer array banned and two integers n and maxSum.
You are choosing some number of integers following the below rules:
- The chosen integers have to be in the range [1, n].
- Each integer can be chosen at most once.
- The chosen integers should not be in the array banned.
- The sum of the chosen integers should not exceed maxSum.

Return the maximum number of integers you can choose following the mentioned rules.

Example 1:
Input: banned = [1,6,5], n = 5, maxSum = 6
Output: 2
Explanation: You can choose the integers 2 and 4.
2 and 4 are from the range [1, 5], both did not appear in banned, and their sum is 6, which did not exceed maxSum.

Example 2:
Input: banned = [1,2,3,4,5,6,7], n = 8, maxSum = 1
Output: 0
Explanation: You cannot choose any integer while following the mentioned conditions.

Example 3:
Input: banned = [11], n = 7, maxSum = 50
Output: 7
Explanation: You can choose the integers 1, 2, 3, 4, 5, 6, and 7.
They are from the range [1, 7], all did not appear in banned, and their sum is 28, which did not exceed maxSum.

Constraints:
1 <= banned.length <= 10^4
1 <= banned[i], n <= 10^4
1 <= maxSum <= 10^9
```

<details><summary>Hint</summary>

```text
1. Keep the banned numbers that are less than n in a set.
2. Loop over the numbers from 1 to n and if the number is not banned, use it.
3. Keep adding numbers while they are not banned, and their sum is less than k.
```

</details>

</details>

<details><summary>C</summary>

```c
#define Biweekly_Contest_97 (1)  // 1:12:39; 3
#if (Biweekly_Contest_97)
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int maxCount(int* banned, int bannedSize, int n, int maxSum) {
    int retVal = 0;

    qsort(banned, bannedSize, sizeof(int), compareInteger);

    int sum = 0;
    int idx = 0;
    int i, j;
    for (i = 1; i <= n; ++i) {
        for (j = idx; j < bannedSize; ++j) {
            if (i == banned[j]) {
                idx = j;
                break;
            }
        }
        if (j != bannedSize) {
            continue;
        }

        sum += i;
        if (sum > maxSum) {
            break;
        }
        ++retVal;
    }

    return retVal;
}
#endif
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
