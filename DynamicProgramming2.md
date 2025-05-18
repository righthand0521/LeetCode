# Dynamic Programming

## [1014. Best Sightseeing Pair](https://leetcode.com/problems/best-sightseeing-pair/)  1730

- [Official](https://leetcode.com/problems/best-sightseeing-pair/editorial/)
- [Official](https://leetcode.cn/problems/best-sightseeing-pair/solutions/291380/zui-jia-guan-guang-zu-he-by-leetcode-solution/)

<details><summary>Description</summary>

```text
You are given an integer array values where values[i] represents the value of the ith sightseeing spot.
Two sightseeing spots i and j have a distance j - i between them.

The score of a pair (i < j) of sightseeing spots is values[i] + values[j] + i - j:
the sum of the values of the sightseeing spots, minus the distance between them.

Return the maximum score of a pair of sightseeing spots.

Example 1:
Input: values = [8,1,5,2,6]
Output: 11
Explanation: i = 0, j = 2, values[i] + values[j] + i - j = 8 + 5 + 0 - 2 = 11

Example 2:
Input: values = [1,2]
Output: 2

Constraints:
2 <= values.length <= 5 * 10^4
1 <= values[i] <= 1000
```

<details><summary>Hint</summary>

```text
1. Can you tell the best sightseeing spot in one pass (ie. as you iterate over the input?)
   What should we store or keep track of as we iterate to do this?
```

</details>

</details>

<details><summary>C</summary>

```c
int maxScoreSightseeingPair(int* values, int valuesSize) {
    int retVal = 0;

    // The score of a pair (i < j) of sightseeing spots is
    // values[i] + values[j] + i - j = (values[i] + i) + (values[j] - j)
    int maxScore = values[0] + 0;
    int i;
    for (i = 1; i < valuesSize; ++i) {
        retVal = fmax(retVal, (maxScore + values[i] - i));
        maxScore = fmax(maxScore, values[i] + i);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxScoreSightseeingPair(vector<int>& values) {
        int retVal = 0;

        // The score of a pair (i < j) of sightseeing spots is
        // values[i] + values[j] + i - j = (values[i] + i) + (values[j] - j)
        int maxScore = values[0] + 0;
        int valuesSize = values.size();
        for (int i = 1; i < valuesSize; ++i) {
            retVal = max(retVal, (maxScore + values[i] - i));
            maxScore = max(maxScore, values[i] + i);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxScoreSightseeingPair(self, values: List[int]) -> int:
        retVal = 0

        # The score of a pair (i < j) of sightseeing spots is
        #  values[i] + values[j] + i - j = (values[i] + i) + (values[j] - j)
        maxScore = values[0] + 0
        valuesSize = len(values)
        for i in range(1, valuesSize):
            retVal = max(retVal, (maxScore + values[i] - i))
            maxScore = max(maxScore, values[i] + i)

        return retVal
```

</details>

## [1024. Video Stitching](https://leetcode.com/problems/video-stitching/)  1746

- [Official](https://leetcode.cn/problems/video-stitching/solutions/458461/shi-pin-pin-jie-by-leetcode-solution/)

<details><summary>Description</summary>

```text
You are given a series of video clips from a sporting event that lasted time seconds.
These video clips can be overlapping with each other and have varying lengths.

Each video clip is described by an array clips
where clips[i] = [starti, endi] indicates that the ith clip started at starti and ended at endi.

We can cut these clips into segments freely.
- For example, a clip [0, 7] can be cut into segments [0, 1] + [1, 3] + [3, 7].

Return the minimum number of clips needed
so that we can cut the clips into segments that cover the entire sporting event [0, time].
If the task is impossible, return -1.

Example 1:
Input: clips = [[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]], time = 10
Output: 3
Explanation: We take the clips [0,2], [8,10], [1,9]; a total of 3 clips.
Then, we can reconstruct the sporting event as follows:
We cut [1,9] into segments [1,2] + [2,8] + [8,9].
Now we have segments [0,2] + [2,8] + [8,10] which cover the sporting event [0, 10].

Example 2:
Input: clips = [[0,1],[1,2]], time = 5
Output: -1
Explanation: We cannot cover [0,5] with only [0,1] and [1,2].

Example 3:
Input: clips = [[0,1],[6,8],[0,2],[5,6],[0,4],[0,3],[6,7],[1,3],[4,7],[1,4],[2,5],[2,6],[3,4],[4,5],[5,7],[6,9]],
time = 9
Output: 3
Explanation: We can take clips [0,4], [4,7], and [6,9].

Constraints:
1 <= clips.length <= 100
0 <= starti <= endi <= 100
1 <= time <= 100
```

<details><summary>Hint</summary>

```text
1. What if we sort the intervals?
   Considering the sorted intervals, how can we solve the problem with dynamic programming?
2. Let's consider a DP(pos, limit) where pos represents the position of the current interval
   we are gonna take the decision and limit is the current covered area from [0 - limit].
   This DP returns the minimum number of taken intervals or infinite if it's not possible to cover the [0 - T] section.
```

</details>

</details>

<details><summary>C</summary>

```c
int videoStitching(int** clips, int clipsSize, int* clipsColSize, int time) {
    int retVal = -1;

    int record[time];
    memset(record, 0, sizeof(record));

    int start, end;
    int i;
    for (i = 0; i < clipsSize; ++i) {
        start = clips[i][0];
        end = clips[i][1];
        if (start < time) {
            record[start] = fmax(record[start], end);
        }
    }

    retVal = 0;
    int lastEnd = 0;
    int previousEnd = 0;
    for (i = 0; i < time; ++i) {
        lastEnd = fmax(lastEnd, record[i]);
        if (i == lastEnd) {
            retVal = -1;
            break;
        } else if (i == previousEnd) {
            retVal += 1;
            previousEnd = lastEnd;
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
    int videoStitching(vector<vector<int>>& clips, int time) {
        int retVal = -1;

        vector<int> record(time, 0);
        for (auto iterator : clips) {
            int start = iterator[0];
            int end = iterator[1];
            if (start < time) {
                record[start] = max(record[start], end);
            }
        }

        retVal = 0;
        int lastEnd = 0;
        int previousEnd = 0;
        for (int i = 0; i < time; ++i) {
            lastEnd = max(lastEnd, record[i]);
            if (i == lastEnd) {
                retVal = -1;
                break;
            } else if (i == previousEnd) {
                retVal += 1;
                previousEnd = lastEnd;
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
    def videoStitching(self, clips: List[List[int]], time: int) -> int:
        retVal = -1

        record = [0] * time
        for start, end in clips:
            if start < time:
                record[start] = max(record[start], end)

        retVal = 0
        lastEnd = 0
        previousEnd = 0
        for i in range(time):
            lastEnd = max(lastEnd, record[i])
            if i == lastEnd:
                retVal = -1
                break
            elif i == previousEnd:
                retVal += 1
                previousEnd = lastEnd

        return retVal
```

</details>

## [1027. Longest Arithmetic Subsequence](https://leetcode.com/problems/longest-arithmetic-subsequence/)  1758

- [Official](https://leetcode.com/problems/longest-arithmetic-subsequence/editorial/)
- [Official](https://leetcode.cn/problems/longest-arithmetic-subsequence/solutions/2238031/zui-chang-deng-chai-shu-lie-by-leetcode-eieq8/)

<details><summary>Description</summary>

```text
Given an array nums of integers, return the length of the longest arithmetic subsequence in nums.

Note that:
- A subsequence is an array that can be derived from another array
  by deleting some or no elements without changing the order of the remaining elements.
- A sequence seq is arithmetic if seq[i + 1] - seq[i] are all the same value (for 0 <= i < seq.length - 1).

Example 1:
Input: nums = [3,6,9,12]
Output: 4
Explanation:  The whole array is an arithmetic sequence with steps of length = 3.

Example 2:
Input: nums = [9,4,7,2,10]
Output: 3
Explanation:  The longest arithmetic subsequence is [4,7,10].

Example 3:
Input: nums = [20,1,15,3,10,5,8]
Output: 4
Explanation:  The longest arithmetic subsequence is [20,15,10,5].

Constraints:
2 <= nums.length <= 1000
0 <= nums[i] <= 500
```

</details>

<details><summary>C</summary>

```c
int longestArithSeqLength(int* nums, int numsSize) {
    int retVal = 1;

    int i;

    // 0 <= nums[i] <= 500
    int minNum = INT_MAX;
    int maxNum = INT_MIN;
    for (i = 0; i < numsSize; ++i) {
        minNum = fmin(minNum, nums[i]);
        maxNum = fmax(maxNum, nums[i]);
    }
    int diff = maxNum - minNum;

    int idx;
    int dp[maxNum + 1];
    int interval;
    for (interval = (-diff); interval <= diff; ++interval) {
        memset(dp, -1, sizeof(dp));

        for (i = 0; i < numsSize; ++i) {
            idx = nums[i] - interval;

            if ((idx >= minNum) && (idx <= maxNum) && (dp[idx] != -1)) {
                dp[nums[i]] = fmax(dp[nums[i]], dp[idx] + 1);
                retVal = fmax(retVal, dp[nums[i]]);
            }
            dp[nums[i]] = fmax(dp[nums[i]], 1);
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
    int longestArithSeqLength(vector<int>& nums) {
        int retVal = 1;

        int minNum = *min_element(nums.begin(), nums.end());
        int maxNum = *max_element(nums.begin(), nums.end());
        int diff = maxNum - minNum;
        for (int interval = (-diff); interval <= diff; ++interval) {
            vector<int> dp(maxNum + 1, -1);

            for (int num : nums) {
                int idx = num - interval;

                if ((idx >= minNum) && (idx <= maxNum) && (dp[idx] != -1)) {
                    dp[num] = max(dp[num], dp[idx] + 1);
                    retVal = max(retVal, dp[num]);
                }
                dp[num] = max(dp[num], 1);
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
    def __init__(self):
        self.method = 1

    def longestArithSeqLength(self, nums: List[int]) -> int:
        retVal = 0

        if self.method == 1:
            dp = defaultdict()
            numsSize = len(nums)
            for right in range(numsSize):
                for left in range(0, right):
                    dp[(right, nums[right] - nums[left])] = dp.get((left, nums[right] - nums[left]), 1) + 1
            retVal = max(dp.values())
        elif self.method == 2:
            minNum = min(nums)
            maxNum = max(nums)
            diff = maxNum - minNum
            for interval in range(-diff, diff+1):
                dp = defaultdict(int)
                for num in nums:
                    idx = num - interval
                    if idx in dp:
                        dp[num] = max(dp.get(num, 0), dp[idx] + 1)
                        retVal = max(retVal, dp[num])
                    dp[num] = max(dp.get(num, 0), 1)

        return retVal
```

</details>

## [1035. Uncrossed Lines](https://leetcode.com/problems/uncrossed-lines/)  1805

- [Official](https://leetcode.com/problems/uncrossed-lines/editorial/)
- [Official](https://leetcode.cn/problems/uncrossed-lines/solutions/787955/bu-xiang-jiao-de-xian-by-leetcode-soluti-6tqz/)

<details><summary>Description</summary>

```text
You are given two integer arrays nums1 and nums2.
We write the integers of nums1 and nums2 (in the order they are given) on two separate horizontal lines.

We may draw connecting lines: a straight line connecting two numbers nums1[i] and nums2[j] such that:
- nums1[i] == nums2[j], and
- the line we draw does not intersect any other connecting (non-horizontal) line.

Note that a connecting line cannot intersect even at the endpoints
(i.e., each number can only belong to one connecting line).

Return the maximum number of connecting lines we can draw in this way.

Example 1:
Input: nums1 = [1,4,2], nums2 = [1,2,4]
Output: 2
Explanation: We can draw 2 uncrossed lines as in the diagram.
We cannot draw 3 uncrossed lines,
because the line from nums1[1] = 4 to nums2[2] = 4 will intersect the line from nums1[2]=2 to nums2[1]=2.

Example 2:
Input: nums1 = [2,5,1,2,5], nums2 = [10,5,2,1,5,2]
Output: 3

Example 3:
Input: nums1 = [1,3,7,1,7,5], nums2 = [1,9,2,5,1]
Output: 2

Constraints:
1 <= nums1.length, nums2.length <= 500
1 <= nums1[i], nums2[j] <= 2000
```

<details><summary>Hint</summary>

```text
1. Think dynamic programming.
   Given an oracle dp(i,j) that tells us how many lines A[i:], B[j:]
   [the sequence A[i], A[i+1], ... and B[j], B[j+1], ...] are uncrossed, can we write this as a recursion?
```

</details>

</details>

<details><summary>C</summary>

```c
int maxUncrossedLines(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int retVal = 0;

    int dp[nums1Size + 1][nums2Size + 1];
    memset(dp, 0, sizeof(dp));

    /* Example: Input: nums1 = [2,5,1,2,5], nums2 = [10,5,2,1,5,2]
     *     10 5 2 1 5 2
     *    0 0 0 0 0 0 0
     *  2 0 0 0 1 1 1 1
     *  5 0 0 1 1 1 2 2
     *  1 0 0 1 1 2 2 2
     *  2 0 0 1 2 2 2 3
     *  5 0 0 1 2 2 3 3
     */
    int idx1, idx2;
    for (idx1 = 1; idx1 <= nums1Size; ++idx1) {
        for (idx2 = 1; idx2 <= nums2Size; ++idx2) {
            if (nums1[idx1 - 1] == nums2[idx2 - 1]) {
                dp[idx1][idx2] = dp[idx1 - 1][idx2 - 1] + 1;
            } else {
                dp[idx1][idx2] = fmax(dp[idx1 - 1][idx2], dp[idx1][idx2 - 1]);
            }
        }
    }
    retVal = dp[nums1Size][nums2Size];

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
        int retVal = 0;

        int len1 = nums1.size();
        int len2 = nums2.size();

        /* Example: Input: nums1 = [2,5,1,2,5], nums2 = [10,5,2,1,5,2]
         *     10 5 2 1 5 2
         *    0 0 0 0 0 0 0
         *  2 0 0 0 1 1 1 1
         *  5 0 0 1 1 1 2 2
         *  1 0 0 1 1 2 2 2
         *  2 0 0 1 2 2 2 3
         *  5 0 0 1 2 2 3 3
         */
        vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1));
        int idx1, idx2;
        for (idx1 = 1; idx1 <= len1; ++idx1) {
            for (idx2 = 1; idx2 <= len2; ++idx2) {
                if (nums1[idx1 - 1] == nums2[idx2 - 1]) {
                    dp[idx1][idx2] = dp[idx1 - 1][idx2 - 1] + 1;
                } else {
                    dp[idx1][idx2] = max(dp[idx1 - 1][idx2], dp[idx1][idx2 - 1]);
                }
            }
        }
        retVal = dp[len1][len2];

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxUncrossedLines(self, nums1: List[int], nums2: List[int]) -> int:
        retVal = 0

        nums1Size = len(nums1)
        nums2Size = len(nums2)

        # /* Example: Input: nums1 = [2,5,1,2,5], nums2 = [10,5,2,1,5,2]
        #  *     10 5 2 1 5 2
        #  *    0 0 0 0 0 0 0
        #  *  2 0 0 0 1 1 1 1
        #  *  5 0 0 1 1 1 2 2
        #  *  1 0 0 1 1 2 2 2
        #  *  2 0 0 1 2 2 2 3
        #  *  5 0 0 1 2 2 3 3
        #  */
        dp = [[0] * (nums2Size + 1) for _ in range(nums1Size + 2)]
        for idx1 in range(1, nums1Size + 1):
            for idx2 in range(1, nums2Size + 1, 1):
                if nums1[idx1 - 1] == nums2[idx2 - 1]:
                    dp[idx1][idx2] = dp[idx1 - 1][idx2 - 1] + 1
                else:
                    dp[idx1][idx2] = max(dp[idx1 - 1][idx2], dp[idx1][idx2 - 1])
        retVal = dp[nums1Size][nums2Size]

        return retVal
```

</details>

## [1043. Partition Array for Maximum Sum](https://leetcode.com/problems/partition-array-for-maximum-sum/)  1916

- [Official](https://leetcode.com/problems/partition-array-for-maximum-sum/editorial/)
- [Official](https://leetcode.cn/problems/partition-array-for-maximum-sum/solutions/2233208/fen-ge-shu-zu-yi-de-dao-zui-da-he-by-lee-mydv/)

<details><summary>Description</summary>

```text
Given an integer array arr, partition the array into (contiguous) subarrays of length at most k.
After partitioning, each subarray has their values changed to become the maximum value of that subarray.

Return the largest sum of the given array after partitioning.
Test cases are generated so that the answer fits in a 32-bit integer.

Example 1:
Input: arr = [1,15,7,9,2,5,10], k = 3
Output: 84
Explanation: arr becomes [15,15,15,9,10,10,10]

Example 2:
Input: arr = [1,4,1,5,7,3,6,1,9,9,3], k = 4
Output: 83

Example 3:
Input: arr = [1], k = 1
Output: 1

Constraints:
1 <= arr.length <= 500
0 <= arr[i] <= 10^9
1 <= k <= arr.length
```

<details><summary>Hint</summary>

```text
1. Think dynamic programming: dp[i] will be the answer for array A[0], ..., A[i-1].
2. For j = 1 .. k that keeps everything in bounds, dp[i] is the maximum of dp[i-j] + max(A[i-1], ..., A[i-j]) * j .
```

</details>

</details>

<details><summary>C</summary>

```c
int maxSumAfterPartitioning(int* arr, int arrSize, int k) {
    int retVal = 0;

    int dp[arrSize + 1];
    memset(dp, 0, sizeof(dp));

    int maxValue;
    int i, j;
    for (i = 1; i <= arrSize; ++i) {
        maxValue = arr[i - 1];
        for (j = i - 1; ((j >= 0) && (j >= i - k)); --j) {
            dp[i] = fmax(dp[i], dp[j] + maxValue * (i - j));
            if (j > 0) {
                maxValue = fmax(maxValue, arr[j - 1]);
            }
        }
    }

    retVal = dp[arrSize];

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        int retVal = 0;

        int arrSize = arr.size();

        vector<int> dp(arrSize + 1, 0);
        for (int i = 1; i <= arrSize; ++i) {
            int maxValue = arr[i - 1];
            for (int j = i - 1; ((j >= 0) && (j >= i - k)); --j) {
                dp[i] = max(dp[i], dp[j] + maxValue * (i - j));
                if (j > 0) {
                    maxValue = max(maxValue, arr[j - 1]);
                }
            }
        }

        retVal = dp[arrSize];

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxSumAfterPartitioning(self, arr: List[int], k: int) -> int:
        retVal = 0

        arrSize = len(arr)

        dp = [0] * (arrSize + 1)
        for i in range(1, arrSize + 1):
            maxValue = arr[i - 1]
            for j in range(i - 1, max(-1, i - k - 1), -1):
                dp[i] = max(dp[i], dp[j] + maxValue * (i - j))
                if j > 0:
                    maxValue = max(maxValue, arr[j - 1])

        retVal = dp[arrSize]

        return retVal
```

</details>

## [1048. Longest String Chain](https://leetcode.com/problems/longest-string-chain/)  1599

- [Official](https://leetcode.cn/problems/longest-string-chain/solutions/2246535/zui-chang-zi-fu-chuan-lian-by-leetcode-s-4uoe/)

<details><summary>Description</summary>

```text
You are given an array of words where each word consists of lowercase English letters.

wordA is a predecessor of wordB if and only if we can insert exactly one letter anywhere in wordA
without changing the order of the other characters to make it equal to wordB.

For example, "abc" is a predecessor of "abac", while "cba" is not a predecessor of "bcad".
A word chain is a sequence of words [word1, word2, ..., wordk] with k >= 1,
where word1 is a predecessor of word2, word2 is a predecessor of word3, and so on.
A single word is trivially a word chain with k == 1.

Return the length of the longest possible word chain with words chosen from the given list of words.

Example 1:
Input: words = ["a","b","ba","bca","bda","bdca"]
Output: 4
Explanation: One of the longest word chains is ["a","ba","bda","bdca"].

Example 2:
Input: words = ["xbc","pcxbcf","xb","cxbc","pcxbc"]
Output: 5
Explanation: All the words can be put in a word chain ["xb", "xbc", "cxbc", "pcxbc", "pcxbcf"].

Example 3:
Input: words = ["abcd","dbqca"]
Output: 1
Explanation: The trivial word chain ["abcd"] is one of the longest word chains.
["abcd","dbqca"] is not a valid word chain because the ordering of the letters is changed.

Constraints:
1 <= words.length <= 1000
1 <= words[i].length <= 16
words[i] only consists of lowercase English letters.
```

</details>

<details><summary>C</summary>

```c
#ifndef HASH_H
#define HASH_H

typedef struct {
    char *key;
    int value;
    UT_hash_handle hh;
} HashItem;
void freeAll(HashItem *pFree) {
    HashItem *pCurrent;
    HashItem *pTmp;
    HASH_ITER(hh, pFree, pCurrent, pTmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, pCurrent);
        free(pCurrent);
    }
}
#endif  // HASH_H
static int compareStringLength(const void *pa, const void *pb) {
    // ascending order
    return strlen(*(char **)pa) - strlen(*(char **)pb);
}
int longestStrChain(char **words, int wordsSize) {
    int retVal = 0;

    HashItem *pCount = NULL;

    qsort(words, wordsSize, sizeof(char *), compareStringLength);

    int wordLength;
    int previousValue, wordValue;
    char previous[32];  // 1 <= words[i].length <= 16
    HashItem *pTemp;
    int i, j;
    for (i = 0; i < wordsSize; i++) {
        pTemp = NULL;
        HASH_FIND_STR(pCount, words[i], pTemp);
        if (pTemp == NULL) {
            pTemp = (HashItem *)malloc(sizeof(HashItem));
            if (pTemp == NULL) {
                perror("malloc");
                goto _exit;
            }
            pTemp->key = words[i];
            pTemp->value = 1;
            HASH_ADD_STR(pCount, key, pTemp);
        }

        memset(previous, 0, sizeof(previous));
        wordLength = strlen(words[i]);
        for (j = 0; j < wordLength; j++) {
            strcpy(previous + j, words[i] + j + 1);

            pTemp = NULL;
            HASH_FIND_STR(pCount, previous, pTemp);
            if (pTemp != NULL) {
                previousValue = pTemp->value + 1;

                wordValue = 0;
                pTemp = NULL;
                HASH_FIND_STR(pCount, words[i], pTemp);
                if (pTemp != NULL) {
                    wordValue = pTemp->value;
                }

                if (previousValue > wordValue) {
                    pTemp = NULL;
                    HASH_FIND_STR(pCount, words[i], pTemp);
                    if (pTemp == NULL) {
                        pTemp = (HashItem *)malloc(sizeof(HashItem));
                        if (pTemp == NULL) {
                            perror("malloc");
                            goto _exit;
                        }
                        pTemp->key = words[i];
                        pTemp->value = previousValue;
                        HASH_ADD_STR(pCount, key, pTemp);
                    } else {
                        pTemp->value = previousValue;
                    }
                }
            }

            previous[j] = words[i][j];
        }

        pTemp = NULL;
        HASH_FIND_STR(pCount, words[i], pTemp);
        if (pTemp != NULL) {
            if (pTemp->value > retVal) {
                retVal = pTemp->value;
            }
        }
    }

_exit:
    freeAll(pCount);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int longestStrChain(vector<string>& words) {
        int retVal = 0;

        unordered_map<string, int> count;

        sort(words.begin(), words.end(), [](const string& a, const string& b) {
            // ascending order
            return a.size() < b.size();
        });
        for (string word : words) {
            count[word] = 1;

            int wordSize = word.size();
            for (int i = 0; i < wordSize; ++i) {
                string previous = word.substr(0, i) + word.substr(i + 1);
                if (count.count(previous)) {
                    count[word] = max(count[word], count[previous] + 1);
                }
            }

            retVal = max(retVal, count[word]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def longestStrChain(self, words: List[str]) -> int:
        retVal = 0

        count = defaultdict(int)

        words.sort(key=len)
        for word in words:
            count[word] = 1

            wordSize = len(word)
            for i in range(wordSize):
                previous = word[:i] + word[i+1:]
                if previous in count:
                    count[word] = max(count[word], count[previous] + 1)

            retVal = max(retVal, count[word])

        return retVal
```

</details>

## [1092. Shortest Common Supersequence](https://leetcode.com/problems/shortest-common-supersequence/)  1976

- [Official](https://leetcode.com/problems/shortest-common-supersequence/editorial/)
- [Official](https://leetcode.cn/problems/shortest-common-supersequence/solutions/2193928/zui-duan-gong-gong-chao-xu-lie-by-leetco-c1tu/)

<details><summary>Description</summary>

```text
Given two strings str1 and str2, return the shortest string that has both str1 and str2 as subsequences.
If there are multiple valid strings, return any of them.

A string s is a subsequence of string t
if deleting some number of characters from t (possibly 0) results in the string s.

Example 1:
Input: str1 = "abac", str2 = "cab"
Output: "cabac"
Explanation:
str1 = "abac" is a subsequence of "cabac" because we can delete the first "c".
str2 = "cab" is a subsequence of "cabac" because we can delete the last "ac".
The answer provided is the shortest such string that satisfies these properties.

Example 2:
Input: str1 = "aaaaaaaa", str2 = "aaaaaaaa"
Output: "aaaaaaaa"

Constraints:
1 <= str1.length, str2.length <= 1000
str1 and str2 consist of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. We can find the length of the longest common subsequence
   between str1[i:] and str2[j:] (for all (i, j)) by using dynamic programming.
2. We can use this information to recover the shortest common supersequence.
```

</details>

</details>

<details><summary>C</summary>

```c
char* shortestCommonSupersequence(char* str1, char* str2) {
    char* pRetVal = NULL;

    int str1Size = strlen(str1);
    int str2Size = strlen(str2);

    // Initialize the base cases
    int dp[str1Size + 1][str2Size + 1];
    memset(dp, 0, sizeof(dp));
    // When str2 is empty, the supersequence is str1 itself (length = row index)
    for (int row = 0; row <= str1Size; row++) {
        dp[row][0] = row;
    }
    // When str1 is empty, the supersequence is str2 itself (length = col index)
    for (int col = 0; col <= str2Size; col++) {
        dp[0][col] = col;
    }

    for (int row = 1; row <= str1Size; row++) {
        for (int col = 1; col <= str2Size; col++) {
            if (str1[row - 1] == str2[col - 1]) {  // If characters match, inherit the length from the diagonal + 1
                dp[row][col] = dp[row - 1][col - 1] + 1;
            } else {  // If characters do not match, take the minimum length option + 1
                dp[row][col] = fmin(dp[row - 1][col], dp[row][col - 1]) + 1;
            }
        }
    }

    // Reverse the built sequence to get the correct order
    int idx = str1Size + str2Size;
    char buf[idx + 1];
    memset(buf, 0, sizeof(buf));

    int row = str1Size;
    int col = str2Size;
    while ((row > 0) && (col > 0)) {
        if (str1[row - 1] == str2[col - 1]) {  // If characters match, take it from diagonal
            buf[--idx] = str1[row - 1];
            row--;
            col--;
        } else if (dp[row - 1][col] < dp[row][col - 1]) {  // If str1’s character is part of the retVal, move up
            buf[--idx] = str1[row - 1];
            row--;
        } else {  // If str2’s character is part of the retVal, move left
            buf[--idx] = str2[col - 1];
            col--;
        }
    }

    // Append any remaining characters If there are leftover characters in str1
    while (row > 0) {
        buf[--idx] = str1[row - 1];
        row--;
    }
    // If there are leftover characters in str2
    while (col > 0) {
        buf[--idx] = str2[col - 1];
        col--;
    }

    int returnSize = strlen(buf + idx) + 1;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));
    memcpy(pRetVal, buf + idx, returnSize - 1);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string shortestCommonSupersequence(string str1, string str2) {
        string retVal = "";

        int str1Size = str1.length();
        int str2Size = str2.length();

        // Initialize the base cases
        vector<vector<int>> dp(str1Size + 1, vector<int>(str2Size + 1, 0));
        // When str2 is empty, the supersequence is str1 itself (length = row index)
        for (int row = 0; row <= str1Size; row++) {
            dp[row][0] = row;
        }
        // When str1 is empty, the supersequence is str2 itself (length = col index)
        for (int col = 0; col <= str2Size; col++) {
            dp[0][col] = col;
        }

        for (int row = 1; row <= str1Size; row++) {
            for (int col = 1; col <= str2Size; col++) {
                if (str1[row - 1] == str2[col - 1]) {  // If characters match, inherit the length from the diagonal + 1
                    dp[row][col] = dp[row - 1][col - 1] + 1;
                } else {  // If characters do not match, take the minimum length option + 1
                    dp[row][col] = min(dp[row - 1][col], dp[row][col - 1]) + 1;
                }
            }
        }

        int row = str1Size;
        int col = str2Size;
        while (row > 0 && col > 0) {
            if (str1[row - 1] == str2[col - 1]) {  // If characters match, take it from diagonal
                retVal += str1[row - 1];
                row--;
                col--;
            } else if (dp[row - 1][col] < dp[row][col - 1]) {  // If str1’s character is part of the retVal, move up
                retVal += str1[row - 1];
                row--;
            } else {  // If str2’s character is part of the retVal, move left
                retVal += str2[col - 1];
                col--;
            }
        }

        // Append any remaining characters If there are leftover characters in str1
        while (row > 0) {
            retVal += str1[row - 1];
            row--;
        }
        // If there are leftover characters in str2
        while (col > 0) {
            retVal += str2[col - 1];
            col--;
        }
        // Reverse the built sequence to get the correct order
        reverse(retVal.begin(), retVal.end());

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def shortestCommonSupersequence(self, str1: str, str2: str) -> str:
        retVal = ""

        str1Size = len(str1)
        str2Size = len(str2)

        # Initialize the base cases
        dp = [[0 for _ in range(str2Size + 1)] for _ in range(str1Size + 1)]
        # When str2 is empty, the supersequence is str1 itself (length = row index)
        for row in range(str1Size + 1):
            dp[row][0] = row
        # When str1 is empty, the supersequence is str2 itself (length = col index)
        for col in range(str2Size + 1):
            dp[0][col] = col

        for row in range(1, str1Size + 1):
            for col in range(1, str2Size + 1):
                if str1[row - 1] == str2[col - 1]:  # If characters match, inherit the length from the diagonal +1
                    dp[row][col] = dp[row - 1][col - 1] + 1
                else:  # If characters do not match, take the minimum length option +1
                    dp[row][col] = min(dp[row - 1][col], dp[row][col - 1]) + 1

        row = str1Size
        col = str2Size
        while row > 0 and col > 0:
            if str1[row - 1] == str2[col - 1]:  # If characters match, take it from diagonal
                retVal += str1[row - 1]
                row -= 1
                col -= 1
            elif dp[row - 1][col] < dp[row][col - 1]:  # If str1’s character is part of the supersequence, move up
                retVal += str1[row - 1]
                row -= 1
            else:  # If str2’s character is part of the supersequence, move left
                retVal += str2[col - 1]
                col -= 1

        # Append any remaining characters if there are leftover characters in str1
        while row > 0:
            retVal += str1[row - 1]
            row -= 1
        # If there are leftover characters in str2
        while col > 0:
            retVal += str2[col - 1]
            col -= 1
        # Reverse the built sequence to get the correct order
        retVal = retVal[::-1]

        return retVal
```

</details>

## [1105. Filling Bookcase Shelves](https://leetcode.com/problems/filling-bookcase-shelves/)  2014

- [Official](https://leetcode.com/problems/filling-bookcase-shelves/editorial/)
- [Official](https://leetcode.cn/problems/filling-bookcase-shelves/solutions/2239727/tian-chong-shu-jia-by-leetcode-solution-b7py/)

<details><summary>Description</summary>

```text
You are given an array books where books[i] = [thicknessi, heighti] indicates the thickness and height of the ith book.
You are also given an integer shelfWidth.

We want to place these books in order onto bookcase shelves that have a total width shelfWidth.

We choose some of the books to place on this shelf
such that the sum of their thickness is less than or equal to shelfWidth,
then build another level of the shelf of the bookcase
so that the total height of the bookcase has increased by the maximum height of the books we just put down.
We repeat this process until there are no more books to place.

Note that at each step of the above process,
the order of the books we place is the same order as the given sequence of books.
- For example, if we have an ordered list of 5 books, we might place the first and second book onto the first shelf,
the third book on the second shelf, and the fourth and fifth book on the last shelf.

Return the minimum possible height that the total bookshelf can be after placing shelves in this manner.

Example 1:
Input: books = [[1,1],[2,3],[2,3],[1,1],[1,1],[1,1],[1,2]], shelfWidth = 4
Output: 6
Explanation:
The sum of the heights of the 3 shelves is 1 + 3 + 2 = 6.
Notice that book number 2 does not have to be on the first shelf.

Example 2:
Input: books = [[1,3],[2,4],[3,2]], shelfWidth = 6
Output: 4

Constraints:
1 <= books.length <= 1000
1 <= thicknessi <= shelfWidth <= 1000
1 <= heighti <= 1000
```

<details><summary>Hint</summary>

```text
1. Use dynamic programming: dp(i) will be the answer to the problem for books[i:].
```

</details>

</details>

<details><summary>C</summary>

```c
int minHeightShelves(int **books, int booksSize, int *booksColSize, int shelfWidth) {
    int retVal = 0;

    // dp[i] will store the minimum height of the bookcase containing all books up to and excluding i
    int dp[booksSize + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 0;
    dp[1] = books[0][1];

    int remainingShelfWidth, maxHeight;
    int i, j;
    for (i = 1; i <= booksSize; ++i) {
        // new shelf built to hold current book
        remainingShelfWidth = shelfWidth - books[i - 1][0];
        maxHeight = books[i - 1][1];
        dp[i] = dp[i - 1] + maxHeight;

        // calculate the height when previous books are added onto a new shelf
        j = i - 1;
        while ((j > 0) && (remainingShelfWidth - books[j - 1][0] >= 0)) {
            remainingShelfWidth -= books[j - 1][0];
            maxHeight = fmax(maxHeight, books[j - 1][1]);
            dp[i] = fmin(dp[i], dp[j - 1] + maxHeight);
            j--;
        }
    }
    retVal = dp[booksSize];

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        int retVal = 0;

        int booksSize = books.size();

        // dp[i] will store the minimum height of the bookcase containing all books up to and excluding i
        vector<int> dp(booksSize + 1, 0);
        dp[0] = 0;
        dp[1] = books[0][1];
        for (int i = 1; i <= booksSize; ++i) {
            // new shelf built to hold current book
            int remainingShelfWidth = shelfWidth - books[i - 1][0];
            int maxHeight = books[i - 1][1];
            dp[i] = dp[i - 1] + maxHeight;

            // calculate the height when previous books are added onto a new shelf
            int j = i - 1;
            while ((j > 0) && (remainingShelfWidth - books[j - 1][0] >= 0)) {
                remainingShelfWidth -= books[j - 1][0];
                maxHeight = max(maxHeight, books[j - 1][1]);
                dp[i] = min(dp[i], dp[j - 1] + maxHeight);
                j--;
            }
        }
        retVal = dp[booksSize];

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minHeightShelves(self, books: List[List[int]], shelfWidth: int) -> int:
        retVal = 0

        booksSize = len(books)

        # dp[i] will store the minimum height of the bookcase containing all books up to and excluding i
        dp = [0] * (booksSize + 1)
        dp[0] = 0
        dp[1] = books[0][1]

        for i in range(2, booksSize + 1):
            # new shelf built to hold current book
            remainingShelfWidth = shelfWidth - books[i - 1][0]
            maxHeight = books[i - 1][1]
            dp[i] = books[i - 1][1] + dp[i - 1]

            # calculate the height when previous books are added to new shelf
            j = i - 1
            while (j > 0) and (remainingShelfWidth - books[j - 1][0] >= 0):
                maxHeight = max(maxHeight, books[j - 1][1])
                remainingShelfWidth -= books[j - 1][0]
                dp[i] = min(dp[i], maxHeight + dp[j - 1])
                j -= 1

        retVal = dp[booksSize]

        return retVal
```

</details>

## [1125. Smallest Sufficient Team](https://leetcode.com/problems/smallest-sufficient-team/)  2250

- [Official](https://leetcode.com/problems/smallest-sufficient-team/editorial/)
- [Official](https://leetcode.cn/problems/smallest-sufficient-team/solutions/2213332/zui-xiao-de-bi-yao-tuan-dui-by-leetcode-2mbmz/)

<details><summary>Description</summary>

```text
In a project, you have a list of required skills req_skills, and a list of people.
The ith person people[i] contains a list of skills that the person has.

Consider a sufficient team: a set of people such that for every required skill in req_skills,
there is at least one person in the team who has that skill.
We can represent these teams by the index of each person.
- For example, team = [0, 1, 3] represents the people with skills people[0], people[1], and people[3].

Return any sufficient team of the smallest possible size, represented by the index of each person.
You may return the answer in any order.

It is guaranteed an answer exists.

Example 1:
Input: req_skills = ["java","nodejs","reactjs"], people = [["java"],["nodejs"],["nodejs","reactjs"]]
Output: [0,2]

Example 2:
Input:
req_skills = ["algorithms","math","java","reactjs","csharp","aws"],
people = [["algorithms","math","java"],["algorithms","math","reactjs"],["java","csharp","aws"],
["reactjs","csharp"],["csharp","math"],["aws","java"]]
Output: [1,2]

Constraints:
1 <= req_skills.length <= 16
1 <= req_skills[i].length <= 16
req_skills[i] consists of lowercase English letters.
All the strings of req_skills are unique.
1 <= people.length <= 60
0 <= people[i].length <= 16
1 <= people[i][j].length <= 16
people[i][j] consists of lowercase English letters.
All the strings of people[i] are unique.
Every skill in people[i] is a skill in req_skills.
It is guaranteed a sufficient team exists.
```

<details><summary>Hint</summary>

```text
1. Do a bitmask DP.
2. For each person, for each set of skills,
   we can update our understanding of a minimum set of people needed to perform this set of skills.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MAX_LENGTH (16 + 4)  // 1 <= req_skills[i].length <= 16
struct hashStruct {
    char key[MAX_LENGTH];
    int value;
    UT_hash_handle hh;
};
void freeAll(struct hashStruct *pFree) {
    struct hashStruct *current;
    struct hashStruct *tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%s: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int compareInteger(const void *n1, const void *n2) {
    // ascending order
    return (*(int *)n1 > *(int *)n2);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *smallestSufficientTeam(char **req_skills, int req_skillsSize, char ***people, int peopleSize, int *peopleColSize,
                            int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;

    int i, j;

    //
    struct hashStruct *pSkillIndex = NULL;
    struct hashStruct *pTemp;
    for (i = 0; i < req_skillsSize; ++i) {
        // All the strings of req_skills are unique.
        pTemp = (struct hashStruct *)malloc(sizeof(struct hashStruct));
        if (pTemp == NULL) {
            perror("malloc");
            freeAll(pSkillIndex);
            return pRetVal;
        }
        snprintf(pTemp->key, MAX_LENGTH, "%s", req_skills[i]);
        pTemp->value = i;
        HASH_ADD_STR(pSkillIndex, key, pTemp);
    }

    //
    int dpSize = (1 << req_skillsSize);
    int dp[dpSize];
    memset(dp, 0, sizeof(dp));
    dp[0] = 0;
    for (i = 1; i < dpSize; ++i) {
        dp[i] = peopleSize;
    }

    //
    int curSkill, prev, comb;
    int prevSkillSize = (1 << req_skillsSize);
    int prevSkill[prevSkillSize];
    memset(prevSkill, 0, sizeof(prevSkill));
    int prevPeopleSize = (1 << req_skillsSize);
    int prevPeople[prevPeopleSize];
    memset(prevPeople, 0, sizeof(prevPeople));
    for (i = 0; i < peopleSize; ++i) {
        curSkill = 0;
        for (j = 0; j < peopleColSize[i]; ++j) {
            pTemp = NULL;
            HASH_FIND_STR(pSkillIndex, people[i][j], pTemp);
            if (pTemp == NULL) {
                freeAll(pSkillIndex);
                return pRetVal;
            }
            curSkill |= (1 << pTemp->value);
        }

        for (prev = 0; prev < (1 << req_skillsSize); prev++) {
            comb = prev | curSkill;
            if (dp[comb] > dp[prev] + 1) {
                dp[comb] = dp[prev] + 1;
                prevSkill[comb] = prev;
                prevPeople[comb] = i;
            }
        }
    }

    //
    pRetVal = (int *)malloc(req_skillsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        freeAll(pSkillIndex);
        return pRetVal;
    }
    memset(pRetVal, 0, (req_skillsSize * sizeof(int)));
    i = (1 << req_skillsSize) - 1;
    while (i > 0) {
        pRetVal[(*returnSize)++] = prevPeople[i];
        i = prevSkill[i];
    }
    qsort(pRetVal, (*returnSize), sizeof(int), compareInteger);

    //
    freeAll(pSkillIndex);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        vector<int> retVal;

        int req_skillsSize = req_skills.size();
        int peopleSize = people.size();

        unordered_map<string, int> skill_index;
        for (int i = 0; i < req_skillsSize; ++i) {
            skill_index[req_skills[i]] = i;
        }

        vector<int> dp(1 << req_skillsSize, peopleSize);
        dp[0] = 0;

        vector<int> prev_skill(1 << req_skillsSize, 0);
        vector<int> prev_people(1 << req_skillsSize, 0);
        for (int i = 0; i < peopleSize; ++i) {
            int cur_skill = 0;

            for (string& skill : people[i]) {
                cur_skill |= (1 << skill_index[skill]);
            }

            for (int prev = 0; prev < (1 << req_skillsSize); prev++) {
                int comb = prev | cur_skill;
                if (dp[comb] > dp[prev] + 1) {
                    dp[comb] = dp[prev] + 1;
                    prev_skill[comb] = prev;
                    prev_people[comb] = i;
                }
            }
        }

        int i = (1 << req_skillsSize) - 1;
        while (i > 0) {
            retVal.push_back(prev_people[i]);
            i = prev_skill[i];
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
    def smallestSufficientTeam(self, req_skills: List[str], people: List[List[str]]) -> List[int]:
        retVal = []

        req_skillsSize = len(req_skills)
        peopleSize = len(people)

        req_skills_index = {skill: index for index, skill in enumerate(req_skills)}

        dp = [peopleSize] * (1 << req_skillsSize)
        dp[0] = 0

        prev_skill = [0] * (1 << req_skillsSize)
        prev_people = [0] * (1 << req_skillsSize)
        for index, value in enumerate(people):
            cur_skill = 0

            for skill in value:
                cur_skill |= (1 << req_skills_index[skill])

            for prev in range(1 << req_skillsSize):
                comb = prev | cur_skill
                if dp[comb] > dp[prev] + 1:
                    dp[comb] = dp[prev] + 1
                    prev_skill[comb] = prev
                    prev_people[comb] = index

        index = (1 << req_skillsSize) - 1
        while index > 0:
            retVal.append(prev_people[index])
            index = prev_skill[index]
        retVal.sort()

        return retVal
```

</details>

## [1137. N-th Tribonacci Number](https://leetcode.com/problems/n-th-tribonacci-number/)  1142

- [Official](https://leetcode.cn/problems/n-th-tribonacci-number/solutions/921898/di-n-ge-tai-bo-na-qi-shu-by-leetcode-sol-kn16/)

<details><summary>Description</summary>

```text
The Tribonacci sequence Tn is defined as follows:

T0 = 0, T1 = 1, T2 = 1, and Tn+3 = Tn + Tn+1 + Tn+2 for n >= 0.

Given n, return the value of Tn.

Example 1:
Input: n = 4
Output: 4
Explanation:
T_3 = 0 + 1 + 1 = 2
T_4 = 1 + 1 + 2 = 4

Example 2:
Input: n = 25
Output: 1389537

Constraints:
0 <= n <= 37
The answer is guaranteed to fit within a 32-bit integer, ie. answer <= 2^31 - 1.
```

<details><summary>Hint</summary>

```text
1. Make an array F of length 38, and set F[0] = 0, F[1] = F[2] = 1.
2. Now write a loop where you set F[n+3] = F[n] + F[n+1] + F[n+2], and return F[n].
```

</details>

</details>

<details><summary>C</summary>

```c
int tribonacci(int n) {
    int retVal = 0;

#define TRIBONACCI_0 (0)
#define TRIBONACCI_1 (1)
#define TRIBONACCI_2 (1)
    if (n == 0) {
        retVal = TRIBONACCI_0;
        return retVal;
    } else if (n == 1) {
        retVal = TRIBONACCI_1;
        return retVal;
    } else if (n == 2) {
        retVal = TRIBONACCI_2;
        return retVal;
    }

#define MAX_SIZE (4)
    int TRIBONACCI[MAX_SIZE] = {TRIBONACCI_0, TRIBONACCI_1, TRIBONACCI_2, 0};
    int i;
    for (i = 3; i <= n; ++i) {
        TRIBONACCI[i % MAX_SIZE] =
            TRIBONACCI[(i - 1) % MAX_SIZE] + TRIBONACCI[(i - 2) % MAX_SIZE] + TRIBONACCI[(i - 3) % 4];
        retVal = TRIBONACCI[i % MAX_SIZE];
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define TRIBONACCI_0 (0)
#define TRIBONACCI_1 (1)
#define TRIBONACCI_2 (1)
   public:
    int tribonacci(int n) {
        int retVal = 0;

        switch (n) {
            case 0:
                retVal = TRIBONACCI_0;
                break;

            case 1:
                retVal = TRIBONACCI_1;
                break;

            case 2:
                retVal = TRIBONACCI_2;
                break;

            default:
                vector<int> dp(n + 1, 0);
                dp[0] = TRIBONACCI_0;
                dp[1] = TRIBONACCI_1;
                dp[2] = TRIBONACCI_2;
                for (int i = 3; i <= n; ++i) {
                    dp[i] = dp[i - 3] + dp[i - 2] + dp[i - 1];
                }
                retVal = dp[n];
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
    def tribonacci(self, n: int) -> int:
        retVal = 0

        # T0 = 0, T1 = 1, T2 = 1, and Tn+3 = Tn + Tn+1 + Tn+2 for n >= 0.
        dp = []
        dp.append(0)
        dp.append(1)
        dp.append(1)
        for i in range(3, n+1):
            dp.append(dp[i-1] + dp[i-2] + dp[i-3])
        retVal = dp[n]

        return retVal
```

</details>

<details><summary>Rust</summary>

```rust
// #[cfg(clang)]
impl Solution {
    pub fn tribonacci(n: i32) -> i32 {
        let ret_val;

        // println!("clang");

        let mut vec = Vec::new();
        vec.push(0);
        vec.push(1);
        vec.push(1);
        for i in 3..n + 1 {
            vec.push(vec[(i - 1) as usize] + vec[(i - 2) as usize] + vec[(i - 3) as usize]);
        }

        ret_val = vec[n as usize];

        return ret_val;
    }
}
// https://leetcode.com/problems/n-th-tribonacci-number/solutions/1994145/
#[cfg(rust)]
impl Solution {
    pub fn tribonacci(n: i32) -> i32 {
        println!("rust");

        match n {
            0 => 0,
            1 | 2 => 1,
            _ => {
                let (_, _, c) = (3..=n).fold((0, 1, 1), |(a, b, c), _| (b, c, c + b + a));
                c
            }
        }
    }
}
```

</details>

## [1139. Largest 1-Bordered Square](https://leetcode.com/problems/largest-1-bordered-square/)  1744

- [Official](https://leetcode.cn/problems/largest-1-bordered-square/solutions/2114369/zui-da-de-yi-1-wei-bian-jie-de-zheng-fan-74ce/)

<details><summary>Description</summary>

```text
Given a 2D grid of 0s and 1s,
return the number of elements in the largest square subgrid that has all 1s on its border,
or 0 if such a subgrid doesn't exist in the grid.

Example 1:
Input: grid = [[1,1,1],[1,0,1],[1,1,1]]
Output: 9

Example 2:
Input: grid = [[1,1,0,0]]
Output: 1

Constraints:
1 <= grid.length <= 100
1 <= grid[0].length <= 100
grid[i][j] is 0 or 1
```

<details><summary>Hint</summary>

```text
1. For each square, know how many ones are up, left, down, and right of this square.
   You can find it in O(N^2) using dynamic programming.
2. Now for each square ( O(N^3) ), we can evaluate whether that square is 1-bordered in O(1).
```

</details>

</details>

<details><summary>C</summary>

```c
int largest1BorderedSquare(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    /* https://leetcode.com/problems/largest-1-bordered-square/solutions/345233/java-c-python-straight-forward/
     *  1. Count the number of consecutive 1s on the top and on the left.
     *  2. From length of edge l = min(m,n) to l = 1, check if the 1-bordered square exist.
     *
     *  Example: grid = [[1,1,1],[1,0,1],[1,1,1]]
     *       +-----------+
     *       | 1 | 1 | 1 |
     *   top | 2 | 0 | 2 |
     *       | 3 | 1 | 3 |
     *       +-----------+
     *         ^   ^   ^
     *       +-----------+    +-----------+
     *       | 1 | 1 | 1 | -> | 1 | 2 | 3 |
     *  grid | 1 | 0 | 1 | -> | 1 | 0 | 1 | left
     *       | 1 | 1 | 1 | -> | 1 | 2 | 3 |
     *       +-----------+    +-----------+
     */
    int row = gridSize;
    int col = gridColSize[0];
    int left[row][col];
    memset(left, 0, sizeof(left));
    int top[row][col];
    memset(top, 0, sizeof(top));

    int i, j;
    for (i = 0; i < row; ++i) {
        for (j = 0; j < col; ++j) {
            left[i][j] = grid[i][j] + (j && grid[i][j] ? left[i][j - 1] : 0);
            top[i][j] = grid[i][j] + (i && grid[i][j] ? top[i - 1][j] : 0);
        }
    }

    int min, topMin, leftMin;
    int idx;
    for (idx = fmin(row, col); idx > 0; --idx) {
        for (i = 0; i < row - idx + 1; ++i) {
            for (j = 0; j < col - idx + 1; ++j) {
                topMin = fmin(top[i + idx - 1][j], top[i + idx - 1][j + idx - 1]);
                leftMin = fmin(left[i][j + idx - 1], left[i + idx - 1][j + idx - 1]);
                min = fmin(topMin, leftMin);
                if (min >= idx) {
                    retVal = idx * idx;
                    return retVal;
                }
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
    int largest1BorderedSquare(vector<vector<int>>& grid) {
        int retVal = 0;

        /* https://leetcode.com/problems/largest-1-bordered-square/solutions/345233/java-c-python-straight-forward/
         *  1. Count the number of consecutive 1s on the top and on the left.
         *  2. From length of edge l = min(m,n) to l = 1, check if the 1-bordered square exist.
         *
         *  Example: grid = [[1,1,1],[1,0,1],[1,1,1]]
         *       +-----------+
         *       | 1 | 1 | 1 |
         *   top | 2 | 0 | 2 |
         *       | 3 | 1 | 3 |
         *       +-----------+
         *         ^   ^   ^
         *       +-----------+    +-----------+
         *       | 1 | 1 | 1 | -> | 1 | 2 | 3 |
         *  grid | 1 | 0 | 1 | -> | 1 | 0 | 1 | left
         *       | 1 | 1 | 1 | -> | 1 | 2 | 3 |
         *       +-----------+    +-----------+
         */
        int row = grid.size();
        int col = grid[0].size();
        vector<vector<int>> left(row, vector<int>(col));
        vector<vector<int>> top(row, vector<int>(col));
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                left[i][j] = grid[i][j] + (j && grid[i][j] ? left[i][j - 1] : 0);
                top[i][j] = grid[i][j] + (i && grid[i][j] ? top[i - 1][j] : 0);
            }
        }

        for (int idx = min(row, col); idx > 0; --idx) {
            for (int i = 0; i < row - idx + 1; ++i) {
                for (int j = 0; j < col - idx + 1; ++j) {
                    int topHead = top[i + idx - 1][j];
                    int topTail = top[i + idx - 1][j + idx - 1];
                    int leftHead = left[i][j + idx - 1];
                    int leftTail = left[i + idx - 1][j + idx - 1];
                    if (min({topHead, topTail, leftHead, leftTail}) >= idx) {
                        retVal = idx * idx;
                        return retVal;
                    }
                }
            }
        }

        return retVal;
    }
};
```

</details>

## [1140. Stone Game II](https://leetcode.com/problems/stone-game-ii/)  2034

- [Official](https://leetcode.com/problems/stone-game-ii/editorial/)
- [Official](https://leetcode.cn/problems/stone-game-ii/solutions/2125131/shi-zi-you-xi-ii-by-leetcode-solution-3pwv/)

<details><summary>Description</summary>

```text
Alice and Bob continue their games with piles of stones.
There are a number of piles arranged in a row, and each pile has a positive integer number of stones piles[i].
The objective of the game is to end with the most stones.

Alice and Bob take turns, with Alice starting first.  Initially, M = 1.

On each player's turn, that player can take all the stones in the first X remaining piles, where 1 <= X <= 2M.
Then, we set M = max(M, X).

The game continues until all the stones have been taken.

Assuming Alice and Bob play optimally, return the maximum number of stones Alice can get.

Example 1:
Input: piles = [2,7,9,4,4]
Output: 10
Explanation:  If Alice takes one pile at the beginning, Bob takes two piles, then Alice takes 2 piles again.
Alice can get 2 + 4 + 4 = 10 piles in total.
If Alice takes two piles at the beginning, then Bob can take all three piles left.
In this case, Alice get 2 + 7 = 9 piles in total. So we return 10 since it's larger.

Example 2:
Input: piles = [1,2,3,4,5,100]
Output: 104

Constraints:
1 <= piles.length <= 100
1 <= piles[i] <= 10^4
```

<details><summary>Hint</summary>

```text
1. Use dynamic programming: the states are (i, m) for the answer of piles[i:] and that given m.
```

</details>

</details>

<details><summary>C</summary>

```c
// https://leetcode.cn/problems/stone-game-ii/solutions/284065/java-dong-tai-gui-hua-qing-xi-yi-dong-17xing-by-lg/
int stoneGameII(int* piles, int pilesSize) {
    int retVal = 0;

    int dp[pilesSize][pilesSize + 1];
    memset(dp, 0, sizeof(dp));
    int sum = 0;
    for (int i = pilesSize - 1; i >= 0; --i) {
        sum += piles[i];
        for (int M = 1; M <= pilesSize; ++M) {
            if (i + 2 * M >= pilesSize) {
                dp[i][M] = sum;
            } else {
                for (int x = 1; x <= 2 * M; ++x) {
                    int j = fmax(M, x);
                    dp[i][M] = fmax(dp[i][M], sum - dp[i + x][j]);
                }
            }
        }
    }
    retVal = dp[0][1];

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    // https://leetcode.cn/problems/stone-game-ii/solutions/284065/java-dong-tai-gui-hua-qing-xi-yi-dong-17xing-by-lg/
    int stoneGameII(vector<int>& piles) {
        int retVal = 0;

        int pilesSize = piles.size();
        vector<vector<int>> dp(pilesSize, vector<int>(pilesSize + 1));
        int sum = 0;
        for (int i = pilesSize - 1; i >= 0; --i) {
            sum += piles[i];
            for (int M = 1; M <= pilesSize; ++M) {
                if (i + 2 * M >= pilesSize) {
                    dp[i][M] = sum;
                } else {
                    for (int x = 1; x <= 2 * M; ++x) {
                        dp[i][M] = max(dp[i][M], sum - dp[i + x][max(M, x)]);
                    }
                }
            }
        }
        retVal = dp[0][1];

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    # https://leetcode.cn/problems/stone-game-ii/solutions/284065/java-dong-tai-gui-hua-qing-xi-yi-dong-17xing-by-lg/
    def stoneGameII(self, piles: List[int]) -> int:
        retVal = 0

        pilesSize = len(piles)
        dp = [[0 for _ in range(pilesSize + 1)] for _ in range(pilesSize)]
        sum = 0
        for i in range(pilesSize - 1, -1, -1):
            sum += piles[i]
            for M in range(1, pilesSize + 1):
                if i + 2 * M >= pilesSize:
                    dp[i][M] = sum
                else:
                    for x in range(1, 2 * M + 1):
                        dp[i][M] = max(dp[i][M], sum - dp[i + x][max(M, x)])
        retVal = dp[0][1]

        return retVal
```

</details>

## [1143. Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/)

- [Official](https://leetcode.cn/problems/longest-common-subsequence/solutions/696763/zui-chang-gong-gong-zi-xu-lie-by-leetcod-y7u0/)

<details><summary>Description</summary>

```text
Given two strings text1 and text2, return the length of their longest common subsequence.
If there is no common subsequence, return 0.

A subsequence of a string is a new string generated from the original string with some characters (can be none)
deleted without changing the relative order of the remaining characters.
- For example, "ace" is a subsequence of "abcde".

A common subsequence of two strings is a subsequence that is common to both strings.

Example 1:
Input: text1 = "abcde", text2 = "ace"
Output: 3
Explanation: The longest common subsequence is "ace" and its length is 3.

Example 2:
Input: text1 = "abc", text2 = "abc"
Output: 3
Explanation: The longest common subsequence is "abc" and its length is 3.

Example 3:
Input: text1 = "abc", text2 = "def"
Output: 0
Explanation: There is no such common subsequence, so the result is 0.

Constraints:
1 <= text1.length, text2.length <= 1000
text1 and text2 consist of only lowercase English characters.
```

<details><summary>Hint</summary>

```text
1. Try dynamic programming. DP[i][j] represents the longest common subsequence of text1[0 ... i] & text2[0 ... j].
2. DP[i][j] = DP[i - 1][j - 1] + 1 , if text1[i] == text2[j] DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]) , otherwise
```

</details>

</details>

<details><summary>C</summary>

```c
int longestCommonSubsequence(char* text1, char* text2) {
    int retVal = 0;

    // 712. Minimum ASCII Delete Sum for Two Strings:
    // https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/
    int s1Size = strlen(text1);
    int s2Size = strlen(text2);
    int dp[s1Size + 1][s2Size + 1];
    memset(dp, 0, sizeof(dp));

    /* https://pic.leetcode-cn.com/1617411822-KhEKGw-image.png
     *      0 1 2 3 4 5
     *      - a b c d e
     *  0 - 0 0 0 0 0 0
     *  1 a 0 1 1 1 1 1
     *  2 c 0 1 1 2 2 2
     *  3 e 0 1 1 2 2 3
     */
    int idx1, idx2;
    for (idx1 = 1; idx1 <= s1Size; ++idx1) {
        for (idx2 = 1; idx2 <= s2Size; ++idx2) {
            if (text1[idx1 - 1] == text2[idx2 - 1]) {
                dp[idx1][idx2] = dp[idx1 - 1][idx2 - 1] + 1;
            } else {
                dp[idx1][idx2] = fmax(dp[idx1 - 1][idx2], dp[idx1][idx2 - 1]);
            }
        }
    }
    retVal = dp[s1Size][s2Size];

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int longestCommonSubsequence(string text1, string text2) {
        int retVal = 0;

        // 712. Minimum ASCII Delete Sum for Two Strings:
        // https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/
        int s1Size = text1.length();
        int s2Size = text2.length();

        /* https://pic.leetcode-cn.com/1617411822-KhEKGw-image.png
         *      0 1 2 3 4 5
         *      - a b c d e
         *  0 - 0 0 0 0 0 0
         *  1 a 0 1 1 1 1 1
         *  2 c 0 1 1 2 2 2
         *  3 e 0 1 1 2 2 3
         */
        vector<vector<int>> dp(s1Size + 1, vector<int>(s2Size + 1));
        int idx1, idx2;
        for (idx1 = 1; idx1 <= s1Size; ++idx1) {
            for (idx2 = 1; idx2 <= s2Size; ++idx2) {
                if (text1[idx1 - 1] == text2[idx2 - 1]) {
                    dp[idx1][idx2] = dp[idx1 - 1][idx2 - 1] + 1;
                } else {
                    dp[idx1][idx2] = max(dp[idx1 - 1][idx2], dp[idx1][idx2 - 1]);
                }
            }
        }
        retVal = dp[s1Size][s2Size];

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def longestCommonSubsequence(self, text1: str, text2: str) -> int:
        retVal = 0

        # // 712. Minimum ASCII Delete Sum for Two Strings:
        # // https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/
        s1Size = len(text1)
        s2Size = len(text2)

        # /* https://pic.leetcode-cn.com/1617411822-KhEKGw-image.png
        #  *      0 1 2 3 4 5
        #  *      - a b c d e
        #  *  0 - 0 0 0 0 0 0
        #  *  1 a 0 1 1 1 1 1
        #  *  2 c 0 1 1 2 2 2
        #  *  3 e 0 1 1 2 2 3
        #  */
        dp = [[0 for i in range(s2Size+1)] for _ in range(s1Size+1)]
        for idx1 in range(1, s1Size+1):
            for idx2 in range(1, s2Size+1):
                if text1[idx1 - 1] == text2[idx2 - 1]:
                    dp[idx1][idx2] = dp[idx1 - 1][idx2 - 1] + 1
                else:
                    dp[idx1][idx2] = max(
                        dp[idx1 - 1][idx2], dp[idx1][idx2 - 1])
        retVal = dp[s1Size][s2Size]

        return retVal
```

</details>

## [1155. Number of Dice Rolls With Target Sum](https://leetcode.com/problems/number-of-dice-rolls-with-target-sum/)  1653

- [Official](https://leetcode.cn/problems/number-of-dice-rolls-with-target-sum/solutions/2490436/zhi-tou-zi-deng-yu-mu-biao-he-de-fang-fa-eewv/)

<details><summary>Description</summary>

```text
You have n dice, and each die has k faces numbered from 1 to k.

Given three integers n, k, and target, return the number of possible ways (out of the kn total ways) to roll the dice,
so the sum of the face-up numbers equals target.
Since the answer may be too large, return it modulo 10^9 + 7.

Example 1:
Input: n = 1, k = 6, target = 3
Output: 1
Explanation: You throw one die with 6 faces.
There is only one way to get a sum of 3.

Example 2:
Input: n = 2, k = 6, target = 7
Output: 6
Explanation: You throw two dice, each with 6 faces.
There are 6 ways to get a sum of 7: 1+6, 2+5, 3+4, 4+3, 5+2, 6+1.

Example 3:
Input: n = 30, k = 30, target = 500
Output: 222616187
Explanation: The answer must be returned modulo 10^9 + 7.

Constraints:
1 <= n, k <= 30
1 <= target <= 1000
```

<details><summary>Hint</summary>

```text
1. Use dynamic programming. The states are how many dice are remaining, and what sum total you have rolled so far.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MODULO (int)(1e9 + 7)
int numRollsToTarget(int n, int k, int target) {
    int retVal = 0;

    /* dp[n][target] = dp[n-1][target-x], x = 1, .., k
     *    0 1 2 3 4 5 6 7
     *  0 1 0 0 0 0 0 0 0
     *  1 0 1 1 1 1 1 1 0
     *  2 0 0 1 2 3 4 5 6
     */
    int dp[n + 1][target + 1];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    long long sum;
    int i, j, x;
    for (i = 1; i < (n + 1); ++i) {
        for (j = 1; j < (target + 1); ++j) {
            for (x = 1; x < (k + 1); ++x) {
                if (j - x >= 0) {
                    sum = dp[i][j] + dp[i - 1][j - x];
                    dp[i][j] = sum % MODULO;
                }
            }
        }
    }
    retVal = dp[n][target];

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
#define MODULO (int)(1e9 + 7)
    int numRollsToTarget(int n, int k, int target) {
        int retVal = 0;

        /* dp[n][target] = dp[n-1][target-x], x = 1, .., k
         *    0 1 2 3 4 5 6 7
         *  0 1 0 0 0 0 0 0 0
         *  1 0 1 1 1 1 1 1 0
         *  2 0 0 1 2 3 4 5 6
         */
        vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));
        dp[0][0] = 1;
        for (int i = 1; i < (n + 1); ++i) {
            for (int j = 1; j < (target + 1); ++j) {
                for (int x = 1; x < (k + 1); ++x) {
                    if (j - x >= 0) {
                        long long sum = dp[i][j] + dp[i - 1][j - x];
                        dp[i][j] = sum % MODULO;
                    }
                }
            }
        }
        retVal = dp[n][target];

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

    def numRollsToTarget(self, n: int, k: int, target: int) -> int:
        retVal = 0

        # dp[n][target] = dp[n-1][target-x], x = 1, .., k
        #   0 1 2 3 4 5 6 7
        # 0 1 0 0 0 0 0 0 0
        # 1 0 1 1 1 1 1 1 0
        # 2 0 0 1 2 3 4 5 6
        dp = [[0] * (target + 1) for _ in range(n + 1)]
        dp[0][0] = 1
        for i in range(1, n + 1):
            for j in range(target + 1):
                for x in range(1, k + 1):
                    if j - x >= 0:
                        dp[i][j] = (dp[i][j] + dp[i - 1][j - x]) % self.MODULO
        retVal = dp[n][target]

        return retVal
```

</details>

## [1187. Make Array Strictly Increasing](https://leetcode.com/problems/make-array-strictly-increasing/)  2315

- [Official](https://leetcode.com/problems/make-array-strictly-increasing/editorial/)
- [Official](https://leetcode.cn/problems/make-array-strictly-increasing/solutions/2235513/shi-shu-zu-yan-ge-di-zeng-by-leetcode-so-6p94/)

<details><summary>Description</summary>

```text
Given two integer arrays arr1 and arr2,
return the minimum number of operations (possibly zero) needed to make arr1 strictly increasing.

In one operation, you can choose two indices 0 <= i < arr1.length
and 0 <= j < arr2.length and do the assignment arr1[i] = arr2[j].

If there is no way to make arr1 strictly increasing, return -1.

Example 1:
Input: arr1 = [1,5,3,6,7], arr2 = [1,3,2,4]
Output: 1
Explanation: Replace 5 with 2, then arr1 = [1, 2, 3, 6, 7].

Example 2:
Input: arr1 = [1,5,3,6,7], arr2 = [4,3,1]
Output: 2
Explanation: Replace 5 with 3 and then replace 3 with 4. arr1 = [1, 3, 4, 6, 7].

Example 3:
Input: arr1 = [1,5,3,6,7], arr2 = [1,6,3,3]
Output: -1
Explanation: You can't make arr1 strictly increasing.

Constraints:
1 <= arr1.length, arr2.length <= 2000
0 <= arr1[i], arr2[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Use dynamic programming.
2. The state would be the index in arr1 and the index of the previous element in arr2
   after sorting it and removing duplicates.
```

</details>

</details>

<details><summary>C</summary>

```c
#define INF (int)(0x3f3f3f3f)  // 0 <= arr1[i], arr2[i] <= 10^9
int compareInteger(const void *n1, const void *n2) {
    // ascending order
    return (*(int *)n1 > *(int *)n2);
}
int binarySearch(int *arr, int left, int right, int val) {
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
int makeArrayIncreasing(int *arr1, int arr1Size, int *arr2, int arr2Size) {
    int retVal = -1;

    int i, j;

    qsort(arr2, arr2Size, sizeof(int), compareInteger);
    int arr2Idx = 0;
    for (i = 0; i < arr2Size; i++) {
        if ((i == 0) || (arr2[i] != arr2[i - 1])) {
            arr2[arr2Idx++] = arr2[i];
        }
    }

    int dpRowSize = arr1Size + 1;
    int dpColSize = fmin(arr1Size, arr2Idx) + 1;
    int dp[dpRowSize][dpColSize];
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = -1;

    int index;
    for (i = 1; i <= arr1Size; i++) {
        for (j = 0; j <= fmin(i, arr2Idx); j++) {
            if (arr1[i - 1] > dp[i - 1][j]) {
                dp[i][j] = arr1[i - 1];
            }

            if ((j > 0) && (dp[i - 1][j - 1] != INF)) {
                index = binarySearch(arr2, j - 1, arr2Idx - 1, dp[i - 1][j - 1]);
                if (index != arr2Idx) {
                    dp[i][j] = fmin(dp[i][j], arr2[index]);
                }
            }

            if ((i == arr1Size) && (dp[i][j] != INF)) {
                retVal = j;
                return retVal;
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
#define INF (int)(0x3f3f3f3f)  // 0 <= arr1[i], arr2[i] <= 10^9

   public:
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        int retVal = -1;

        sort(arr2.begin(), arr2.end());

        arr2.erase(unique(arr2.begin(), arr2.end()), arr2.end());
        int arr1Size = arr1.size();
        int arr2Size = arr2.size();

        vector<vector<int>> dp(arr1Size + 1, vector<int>(min(arr2Size, arr1Size) + 1, INF));
        dp[0][0] = -1;

        for (int i = 1; i <= arr1Size; i++) {
            for (int j = 0; j <= min(i, arr2Size); j++) {
                if (arr1[i - 1] > dp[i - 1][j]) {
                    dp[i][j] = arr1[i - 1];
                }

                if ((j > 0) && (dp[i - 1][j - 1] != INF)) {
                    auto it = upper_bound(arr2.begin() + j - 1, arr2.end(), dp[i - 1][j - 1]);
                    if (it != arr2.end()) {
                        dp[i][j] = min(dp[i][j], *it);
                    }
                }

                if ((i == arr1Size) && (dp[i][j] != INF)) {
                    retVal = j;
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
    def makeArrayIncreasing(self, arr1: List[int], arr2: List[int]) -> int:
        retVal = -1

        arr2 = sorted(set(arr2))

        arr1Size = len(arr1)
        arr2Size = len(arr2)

        dp = [[inf] * (min(arr2Size, arr1Size) + 1) for _ in range(arr1Size + 1)]
        dp[0][0] = -1

        for i in range(1, arr1Size + 1):
            for j in range(min(i, arr2Size) + 1):
                if arr1[i - 1] > dp[i - 1][j]:
                    dp[i][j] = arr1[i - 1]

                if j and (dp[i - 1][j - 1] != inf):
                    k = bisect_right(arr2, dp[i - 1][j - 1], j - 1)
                    if k < arr2Size:
                        dp[i][j] = min(dp[i][j], arr2[k])

                if (i == arr1Size) and (dp[i][j] != inf):
                    retVal = j
                    return retVal

        return retVal
```

</details>

## [1218. Longest Arithmetic Subsequence of Given Difference](https://leetcode.com/problems/longest-arithmetic-subsequence-of-given-difference/)  1597

- [Official](https://leetcode.com/problems/longest-arithmetic-subsequence-of-given-difference/editorial/)
- [Official](https://leetcode.cn/problems/longest-arithmetic-subsequence-of-given-difference/solutions/1083218/zui-chang-ding-chai-zi-xu-lie-by-leetcod-xkua/)

<details><summary>Description</summary>

```text
Given an integer array arr and an integer difference,
return the length of the longest subsequence in arr which is an arithmetic sequence
such that the difference between adjacent elements in the subsequence equals difference.

A subsequence is a sequence
that can be derived from arr by deleting some or no elements without changing the order of the remaining elements.

Example 1:
Input: arr = [1,2,3,4], difference = 1
Output: 4
Explanation: The longest arithmetic subsequence is [1,2,3,4].

Example 2:
Input: arr = [1,3,5,7], difference = 1
Output: 1
Explanation: The longest arithmetic subsequence is any single element.

Example 3:
Input: arr = [1,5,7,8,5,3,4,2,1], difference = -2
Output: 4
Explanation: The longest arithmetic subsequence is [7,5,3,1].

Constraints:
1 <= arr.length <= 10^5
-10^4 <= arr[i], difference <= 10^4
```

<details><summary>Hint</summary>

```text
1. Use dynamic programming.
2. Let dp[i] be the maximum length of a subsequence of the given difference whose last element is i.
3. dp[i] = 1 + dp[i-k]
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
int longestSubsequence(int *arr, int arrSize, int difference) {
    int retVal = 0;

    /* Input : arr = [1, 5, 7, 8, 5, 3, 4, 2, 1], difference = -2
     *  1 dp{1 : 1 }
     *  5 dp{1 : 1, 5 : 1 }
     *  7 dp{1 : 1, 5 : 1, 7 : 1 }
     *  8 dp{1 : 1, 5 : 1, 7 : 1, 8 : 1 }
     *  5 dp{1 : 1, 5 : 2, 7 : 1, 8 : 1 }
     *  3 dp{1 : 1, 5 : 2, 7 : 1, 8 : 1, 3 : 3 }
     *  4 dp{1 : 1, 5 : 2, 7 : 1, 8 : 1, 3 : 3, 4 : 1 }
     *  2 dp{1 : 1, 5 : 2, 7 : 1, 8 : 1, 3 : 3, 4 : 1, 2 : 2 }
     *  1 dp{1 : 1, 5 : 2, 7 : 1, 8 : 1, 3 : 3, 4 : 1, 2 : 2, 1 : 4 }
     */
    struct hashTable *pDp = NULL;
    struct hashTable *pTmp;
    int key, value;
    int i;
    for (i = 0; i < arrSize; ++i) {
        key = arr[i] - difference;
        value = 0;

        pTmp = NULL;
        HASH_FIND_INT(pDp, &key, pTmp);
        if (pTmp != NULL) {
            value = pTmp->value;
        }

        key = arr[i];
        pTmp = NULL;
        HASH_FIND_INT(pDp, &key, pTmp);
        if (pTmp == NULL) {
            pTmp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTmp == NULL) {
                perror("malloc");
                freeAll(pDp);
                return retVal;
            }
            pTmp->key = key;
            pTmp->value = value + 1;
            HASH_ADD_INT(pDp, key, pTmp);
        } else {
            pTmp->value = value + 1;
        }

        retVal = fmax(retVal, value + 1);
    }
    freeAll(pDp);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int longestSubsequence(vector<int>& arr, int difference) {
        int retVal = 0;

        /* Input : arr = [1, 5, 7, 8, 5, 3, 4, 2, 1], difference = -2
         *  1 dp{1 : 1 }
         *  5 dp{1 : 1, 5 : 1 }
         *  7 dp{1 : 1, 5 : 1, 7 : 1 }
         *  8 dp{1 : 1, 5 : 1, 7 : 1, 8 : 1 }
         *  5 dp{1 : 1, 5 : 2, 7 : 1, 8 : 1 }
         *  3 dp{1 : 1, 5 : 2, 7 : 1, 8 : 1, 3 : 3 }
         *  4 dp{1 : 1, 5 : 2, 7 : 1, 8 : 1, 3 : 3, 4 : 1 }
         *  2 dp{1 : 1, 5 : 2, 7 : 1, 8 : 1, 3 : 3, 4 : 1, 2 : 2 }
         *  1 dp{1 : 1, 5 : 2, 7 : 1, 8 : 1, 3 : 3, 4 : 1, 2 : 2, 1 : 4 }
         */
        unordered_map<int, int> dp;
        for (int value : arr) {
            dp[value] = dp[value - difference] + 1;
            retVal = max(retVal, dp[value]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def longestSubsequence(self, arr: List[int], difference: int) -> int:
        retVal = 0

        # /* Input : arr = [1, 5, 7, 8, 5, 3, 4, 2, 1], difference = -2
        #  *  1 dp{1 : 1 }
        #  *  5 dp{1 : 1, 5 : 1 }
        #  *  7 dp{1 : 1, 5 : 1, 7 : 1 }
        #  *  8 dp{1 : 1, 5 : 1, 7 : 1, 8 : 1 }
        #  *  5 dp{1 : 1, 5 : 2, 7 : 1, 8 : 1 }
        #  *  3 dp{1 : 1, 5 : 2, 7 : 1, 8 : 1, 3 : 3 }
        #  *  4 dp{1 : 1, 5 : 2, 7 : 1, 8 : 1, 3 : 3, 4 : 1 }
        #  *  2 dp{1 : 1, 5 : 2, 7 : 1, 8 : 1, 3 : 3, 4 : 1, 2 : 2 }
        #  *  1 dp{1 : 1, 5 : 2, 7 : 1, 8 : 1, 3 : 3, 4 : 1, 2 : 2, 1 : 4 }
        #  */
        dp = defaultdict(int)
        for value in arr:
            dp[value] = dp[value - difference] + 1
        retVal = max(dp.values())

        return retVal
```

</details>

## [1220. Count Vowels Permutation](https://leetcode.com/problems/count-vowels-permutation/)  1729

- [Official](https://leetcode.cn/problems/count-vowels-permutation/solutions/1210214/tong-ji-yuan-yin-zi-mu-xu-lie-de-shu-mu-jxo09/)

<details><summary>Description</summary>

```text
Given an integer n, your task is to count how many strings of length n can be formed under the following rules:
- Each character is a lower case vowel ('a', 'e', 'i', 'o', 'u')
- Each vowel 'a' may only be followed by an 'e'.
- Each vowel 'e' may only be followed by an 'a' or an 'i'.
- Each vowel 'i' may not be followed by another 'i'.
- Each vowel 'o' may only be followed by an 'i' or a 'u'.
- Each vowel 'u' may only be followed by an 'a'.
Since the answer may be too large, return it modulo 10^9 + 7.

Example 1:
Input: n = 1
Output: 5
Explanation: All possible strings are: "a", "e", "i" , "o" and "u".

Example 2:
Input: n = 2
Output: 10
Explanation: All possible strings are: "ae", "ea", "ei", "ia", "ie", "io", "iu", "oi", "ou" and "ua".

Example 3:
Input: n = 5
Output: 68

Constraints:
1 <= n <= 2 * 10^4
```

<details><summary>Hint</summary>

```text
1. Use dynamic programming.
2. Let dp[i][j] be the number of strings of length i that ends with the j-th vowel.
3. Deduce the recurrence from the given relations between vowels.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MODULO (int)(1e9 + 7)
int countVowelPermutation(int n) {
    int retVal = 0;

    int numberOfCharacter = 5;  // Each character is a lower case vowel ('a', 'e', 'i', 'o', 'u')
    int i;

    long long *dp = (long long *)malloc(numberOfCharacter * sizeof(long long));
    if (dp == NULL) {
        perror("malloc");
        return retVal;
    }
    for (i = 0; i < numberOfCharacter; ++i) {
        dp[i] = 1;
    }

    long long *nextDp = (long long *)malloc(numberOfCharacter * sizeof(long long));
    if (nextDp == NULL) {
        perror("malloc");
        free(dp);
        dp = NULL;
        return retVal;
    }
    for (i = 2; i <= n; ++i) {
        nextDp[0] = (dp[1] + dp[2] + dp[4]) % MODULO;
        nextDp[1] = (dp[0] + dp[2]) % MODULO;
        nextDp[2] = (dp[1] + dp[3]) % MODULO;
        nextDp[3] = dp[2];
        nextDp[4] = (dp[2] + dp[3]) % MODULO;

        memcpy(dp, nextDp, (numberOfCharacter * sizeof(long long)));
    }

    long long answer = 0;
    for (i = 0; i < numberOfCharacter; ++i) {
        answer = (answer + dp[i]) % MODULO;
    }
    retVal = answer;

    free(dp);
    dp = NULL;
    free(nextDp);
    nextDp = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
#define MODULO (int)(1e9 + 7)
    int countVowelPermutation(int n) {
        int retVal = 0;

        int numberOfCharacter = 5;  // Each character is a lower case vowel ('a', 'e', 'i', 'o', 'u')

        vector<long long> dp(numberOfCharacter, 1);
        vector<long long> nextDp(numberOfCharacter);
        for (int i = 2; i <= n; ++i) {
            nextDp[0] = (dp[1] + dp[2] + dp[4]) % MODULO;
            nextDp[1] = (dp[0] + dp[2]) % MODULO;
            nextDp[2] = (dp[1] + dp[3]) % MODULO;
            nextDp[3] = dp[2];
            nextDp[4] = (dp[2] + dp[3]) % MODULO;

            dp = nextDp;
        }
        retVal = accumulate(dp.begin(), dp.end(), 0LL) % MODULO;

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

    def countVowelPermutation(self, n: int) -> int:
        retVal = 0

        # dp[i][j]: length is i and last character is j, j = 0, 1, 2, 3, 4 that means a, e, i, o, u.
        # dp[i][0] = dp[i−1][1]+dp[i−1][2]+dp[i−1][4]
        # dp[i][1] = dp[i−1][0]+dp[i−1][2]
        # dp[i][2] = dp[i−1][1]+dp[i−1][3]
        # dp[i][3] = dp[i−1][2]
        # dp[i][4] = dp[i−1][2]+dp[i−1][3] 
        dp = (1, 1, 1, 1, 1)
        for _ in range(n - 1):
            dp1 = (dp[1] + dp[2] + dp[4]) % self.MODULO
            dp2 = (dp[0] + dp[2]) % self.MODULO
            dp3 = (dp[1] + dp[3]) % self.MODULO
            dp4 = dp[2]
            dp5 = (dp[2] + dp[3]) % self.MODULO
            dp = (dp1, dp2, dp3, dp4, dp5)
        retVal = sum(dp) % self.MODULO

        return retVal
```

</details>

## [1235. Maximum Profit in Job Scheduling](https://leetcode.com/problems/maximum-profit-in-job-scheduling/)  2022

- [Official](https://leetcode.cn/problems/maximum-profit-in-job-scheduling/solutions/1910416/gui-hua-jian-zhi-gong-zuo-by-leetcode-so-gu0e/)

<details><summary>Description</summary>

```text
We have n jobs, where every job is scheduled to be done from startTime[i] to endTime[i], obtaining a profit of profit[i].

You're given the startTime, endTime and profit arrays,
return the maximum profit you can take such that there are no two jobs in the subset with overlapping time range.

If you choose a job that ends at time X you will be able to start another job that starts at time X.

Example 1:
+-----------------------+
| 1 | 2 | 3 | 4 | 5 | 6 |
+-----------+-----------+
| profit=50 |
+---+-------+---+
    | profit=10 |
    +---+-------+---+
        | profit=40 |
        +-----------+---+
        | profit=70     |
        +---------------+
Input: startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
Output: 120
Explanation: The subset chosen is the first and fourth job.
Time range [1-3]+[3-6] , we get profit of 120 = 50 + 70.

Example 2:
+-------------------------------------------------+
|  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 |
+--------------+----------------------------------+
| profit=20    |
+----+---------+---------+
     | profit=20         |
     +----+--------------+------------------------+
          | profit=100                            |
          +----+--------------+-------------------+
               | profit=70    |
               +--------------+--------------+
                              | profit=60    |
                              +--------------+
Input: startTime = [1,2,3,4,6], endTime = [3,5,10,6,9], profit = [20,20,100,70,60]
Output: 150
Explanation: The subset chosen is the first, fourth and fifth job.
Profit obtained 150 = 20 + 70 + 60.

Example 3:
+-----------------------+
|  1  |  2  |  3  |  4  |
+-----------+-----------+
| profit=5  |
+-----------+-----+
| profit=6        |
+-----------------+-----+
| profit=4              |
+-----------------------+
Input: startTime = [1,1,1], endTime = [2,3,4], profit = [5,6,4]
Output: 6

Constraints:
1 <= startTime.length == endTime.length == profit.length <= 5 * 10^4
1 <= startTime[i] < endTime[i] <= 10^9
1 <= profit[i] <= 10^4
```

<details><summary>Hint</summary>

```text
1. Think on DP.
2. Sort the elements by starting time,
   then define the dp[i] as the maximum profit taking elements from the suffix starting at i.
3. Use binarySearch (lower_bound/upper_bound on C++) to get the next index for the DP transition.
```

</details>

</details>

<details><summary>C</summary>

```c
int binarySearch(int jobs[][3], int right, int target) {
    int retVal = 0;

    int left = 0;
    int middle;
    while (left < right) {
        middle = left + (right - left) / 2;
        if (jobs[middle][1] > target) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }
    retVal = left;

    return retVal;
}
int compareIntArray(const void* a1, const void* a2) {
    int* p1 = (int*)a1;
    int* p2 = (int*)a2;

    // ascending order
    return (p1[1] > p2[1]);
}
int jobScheduling(int* startTime, int startTimeSize, int* endTime, int endTimeSize, int* profit, int profitSize) {
    int retVal = 0;

    int n = startTimeSize;

    int jobs[n][3];
    int i;
    for (i = 0; i < n; ++i) {
        jobs[i][0] = startTime[i];
        jobs[i][1] = endTime[i];
        jobs[i][2] = profit[i];
    }
    qsort(jobs, n, sizeof(jobs[0]), compareIntArray);

    int dp[n + 1];
    memset(dp, 0, sizeof(dp));

    int k;
    for (i = 1; i <= n; ++i) {
        k = binarySearch(jobs, i - 1, jobs[i - 1][0]);
        dp[i] = fmax(dp[i - 1], dp[k] + jobs[i - 1][2]);
    }
    retVal = dp[n];

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int retVal = 0;

        int startTimeSize = startTime.size();

        vector<vector<int>> jobs(startTimeSize);
        for (int i = 0; i < startTimeSize; i++) {
            jobs[i] = {startTime[i], endTime[i], profit[i]};
        }
        sort(jobs.begin(), jobs.end(),
             [](const vector<int>& job1, const vector<int>& job2) -> bool { return job1[1] < job2[1]; });

        vector<int> dp(startTimeSize + 1);
        for (int i = 1; i <= startTimeSize; i++) {
            int k = upper_bound(jobs.begin(), jobs.begin() + i - 1, jobs[i - 1][0],
                                [&](int st, const vector<int>& job) -> bool { return st < job[1]; }) -
                    jobs.begin();
            dp[i] = max(dp[i - 1], dp[k] + jobs[i - 1][2]);
        }
        retVal = dp[startTimeSize];

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def jobScheduling(self, startTime: List[int], endTime: List[int], profit: List[int]) -> int:
        retVal = 0

        startTimeSize = len(startTime)

        jobs = sorted(zip(startTime, endTime, profit), key=lambda p: p[1])

        dp = [0] * (startTimeSize + 1)
        for i in range(1, startTimeSize + 1):
            k = bisect_right(jobs, jobs[i - 1][0], hi=i, key=lambda p: p[1])
            dp[i] = max(dp[i - 1], dp[k] + jobs[i - 1][2])
        retVal = dp[startTimeSize]

        return retVal
```

</details>

## [1269. Number of Ways to Stay in the Same Place After Some Steps](https://leetcode.com/problems/number-of-ways-to-stay-in-the-same-place-after-some-steps/)  1854

- [Official](https://leetcode.com/problems/number-of-ways-to-stay-in-the-same-place-after-some-steps/editorial/)
- [Official](https://leetcode.cn/problems/number-of-ways-to-stay-in-the-same-place-after-some-steps/solutions/101825/ting-zai-yuan-di-de-fang-an-shu-by-leetcode-soluti/)

<details><summary>Description</summary>

```text
You have a pointer at index 0 in an array of size arrLen.
At each step, you can move 1 position to the left, 1 position to the right in the array,
or stay in the same place (The pointer should not be placed outside the array at any time).

Given two integers steps and arrLen,
return the number of ways such that your pointer is still at index 0 after exactly steps steps.
Since the answer may be too large, return it modulo 10^9 + 7.

Example 1:
Input: steps = 3, arrLen = 2
Output: 4
Explanation: There are 4 differents ways to stay at index 0 after 3 steps.
Right, Left, Stay
Stay, Right, Left
Right, Stay, Left
Stay, Stay, Stay

Example 2:
Input: steps = 2, arrLen = 4
Output: 2
Explanation: There are 2 differents ways to stay at index 0 after 2 steps
Right, Left
Stay, Stay

Example 3:
Input: steps = 4, arrLen = 2
Output: 8

Constraints:
1 <= steps <= 500
1 <= arrLen <= 10^6
```

<details><summary>Hint</summary>

```text
1. Try with Dynamic programming, dp(pos,steps): number of ways to back pos = 0 using exactly "steps" moves.
2. Notice that the computational complexity does not depend of "arrlen".
```

</details>

</details>

<details><summary>C</summary>

```c
#define MODULO (int)(1e9 + 7)
int numWays(int steps, int arrLen) {
    int retVal = 0;

    // dp[step][index] : 0 <= step <= steps, 0 <= index <= arrLen - 1.
    // => dp[step][index] : 0 <= step <= steps, 0 <= index <= min(arrLen - 1, steps).
    // => dpNextStep[index], 0 <= index <= min(arrLen - 1, steps).
    int maxIndex = fmin(arrLen - 1, steps);
    int dp[maxIndex + 1];
    memset(dp, 0, sizeof(dp));
    int dpNextStep[maxIndex + 1];
    dp[0] = 1;
    for (int i = 1; i <= steps; ++i) {
        memset(dpNextStep, 0, sizeof(dpNextStep));
        for (int j = 0; j <= maxIndex; ++j) {
            dpNextStep[j] = dp[j];
            if (j - 1 >= 0) {
                dpNextStep[j] = (dpNextStep[j] + dp[j - 1]) % MODULO;
            }
            if (j + 1 <= maxIndex) {
                dpNextStep[j] = (dpNextStep[j] + dp[j + 1]) % MODULO;
            }
        }
        memcpy(dp, dpNextStep, sizeof(dp));
    }
    retVal = dp[0];

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define MODULO (int)(1e9 + 7)
   public:
    int numWays(int steps, int arrLen) {
        int retVal = 0;

        // dp[step][index] : 0 <= step <= steps, 0 <= index <= arrLen - 1.
        // => dp[step][index] : 0 <= step <= steps, 0 <= index <= min(arrLen - 1, steps).
        // => dpNextStep[index], 0 <= index <= min(arrLen - 1, steps).
        int maxIndex = min(arrLen - 1, steps);
        vector<int> dp(maxIndex + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= steps; ++i) {
            vector<int> dpNextStep(maxIndex + 1, 0);
            for (int j = 0; j <= maxIndex; ++j) {
                dpNextStep[j] = dp[j];
                if (j - 1 >= 0) {
                    dpNextStep[j] = (dpNextStep[j] + dp[j - 1]) % MODULO;
                }
                if (j + 1 <= maxIndex) {
                    dpNextStep[j] = (dpNextStep[j] + dp[j + 1]) % MODULO;
                }
            }
            dp = dpNextStep;
        }
        retVal = dp[0];

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

    def numWays(self, steps: int, arrLen: int) -> int:
        retVal = 0

        # dp[step][index]: 0 <= step <= steps, 0 <= index <= arrLen-1.
        # => dp[step][index]: 0 <= step <= steps, 0 <= index <= min(arrLen-1, steps).
        # => dpNextStep[index], 0 <= index <= min(arrLen-1, steps).
        maxIndex = min(arrLen - 1, steps)
        dp = [0] * (maxIndex + 1)
        dp[0] = 1
        for _ in range(1, steps + 1):
            dpNextStep = [0] * (maxIndex + 1)
            for j in range(0, maxIndex + 1):
                dpNextStep[j] = dp[j]
                if j - 1 >= 0:
                    dpNextStep[j] = (dpNextStep[j] + dp[j - 1]) % self.MODULO
                if j + 1 <= maxIndex:
                    dpNextStep[j] = (dpNextStep[j] + dp[j + 1]) % self.MODULO
            dp = dpNextStep
        retVal = dp[0]

        return retVal
```

</details>

## [1277. Count Square Submatrices with All Ones](https://leetcode.com/problems/count-square-submatrices-with-all-ones/)  1613

- [Official](https://leetcode.com/problems/count-square-submatrices-with-all-ones/editorial/)
- [Official](https://leetcode.cn/problems/count-square-submatrices-with-all-ones/solutions/101706/tong-ji-quan-wei-1-de-zheng-fang-xing-zi-ju-zhen-2/)

<details><summary>Description</summary>

```text
Given a m * n matrix of ones and zeros, return how many square submatrices have all ones.

Example 1:
Input: matrix =
[
  [0,1,1,1],
  [1,1,1,1],
  [0,1,1,1]
]
Output: 15
Explanation:
There are 10 squares of side 1.
There are 4 squares of side 2.
There is  1 square of side 3.
Total number of squares = 10 + 4 + 1 = 15.

Example 2:
Input: matrix =
[
  [1,0,1],
  [1,1,0],
  [1,1,0]
]
Output: 7
Explanation:
There are 6 squares of side 1.
There is 1 square of side 2.
Total number of squares = 6 + 1 = 7.

Constraints:
1 <= arr.length <= 300
1 <= arr[0].length <= 300
0 <= arr[i][j] <= 1
```

<details><summary>Hint</summary>

```text
1. Create an additive table that counts the sum of elements of submatrix with the superior corner at (0,0).
2. Loop over all subsquares in O(n^3) and check if the sum make the whole array to be ones,
   if it checks then add 1 to the answer.
```

</details>

</details>

<details><summary>C</summary>

```c
int countSquares(int** matrix, int matrixSize, int* matrixColSize) {
    int retVal = 0;

    int row = matrixSize;
    int col = matrixColSize[0];
    int dp[row + 1][col + 1];
    memset(dp, 0, sizeof(dp));
    int x, y;
    for (x = 0; x < row; ++x) {
        for (y = 0; y < col; ++y) {
            if (matrix[x][y] == 0) {
                continue;
            }
            dp[x + 1][y + 1] = fmin(fmin(dp[x][y + 1], dp[x + 1][y]), dp[x][y]) + 1;
            retVal += dp[x + 1][y + 1];
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
    int countSquares(vector<vector<int>>& matrix) {
        int retVal = 0;

        int row = matrix.size();
        int col = matrix[0].size();
        vector<vector<int>> dp(row + 1, vector<int>(col + 1, 0));
        for (int x = 0; x < row; ++x) {
            for (int y = 0; y < col; ++y) {
                if (matrix[x][y] == 0) {
                    continue;
                }
                dp[x + 1][y + 1] = min({dp[x][y + 1], dp[x + 1][y], dp[x][y]}) + 1;
                retVal += dp[x + 1][y + 1];
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
    def countSquares(self, matrix: List[List[int]]) -> int:
        retVal = 0

        row = len(matrix)
        col = len(matrix[0])
        dp = [[0] * (col + 1) for _ in range(row + 1)]
        for x in range(row):
            for y in range(col):
                if matrix[x][y] == 0:
                    continue
                dp[x + 1][y + 1] = (min(dp[x][y + 1], dp[x + 1][y], dp[x][y]) + 1)
                retVal += dp[x + 1][y + 1]

        return retVal
```

</details>

## [1289. Minimum Falling Path Sum II](https://leetcode.com/problems/minimum-falling-path-sum-ii/)  1697

- [Official](https://leetcode.com/problems/minimum-falling-path-sum-ii/editorial/)
- [Official](https://leetcode.cn/problems/minimum-falling-path-sum-ii/solutions/101728/xia-jiang-lu-jing-zui-xiao-he-ii-by-leetcode-solut/)

<details><summary>Description</summary>

```text
Given an n x n integer matrix grid, return the minimum sum of a falling path with non-zero shifts.

A falling path with non-zero shifts is a choice of exactly one element
from each row of grid such that no two elements chosen in adjacent rows are in the same column.

Example 1:
Input: grid = [[1,2,3],[4,5,6],[7,8,9]]
Output: 13
Explanation:
The possible falling paths are:
[1,5,9], [1,5,7], [1,6,7], [1,6,8],
[2,4,8], [2,4,9], [2,6,7], [2,6,8],
[3,4,8], [3,4,9], [3,5,7], [3,5,9]
The falling path with the smallest sum is [1,5,7], so the answer is 13.

Example 2:
Input: grid = [[7]]
Output: 7

Constraints:
n == grid.length == grid[i].length
1 <= n <= 200
-99 <= grid[i][j] <= 99
```

<details><summary>Hint</summary>

```text
1. Use dynamic programming.
2. Let dp[i][j] be the answer for the first i rows such that column j is chosen from row i.
3. Use the concept of cumulative array to optimize the complexity of the solution.
```

</details>

</details>

<details><summary>C</summary>

```c
int minFallingPathSum(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int i, j, k;

    int dp[gridSize][gridSize];
    for (i = 0; i < gridSize; ++i) {
        for (j = 0; j < gridSize; ++j) {
            dp[i][j] = INT_MAX;
        }
    }
    for (i = 0; i < gridSize; ++i) {
        dp[0][i] = grid[0][i];
    }

    for (i = 1; i < gridSize; ++i) {
        for (j = 0; j < gridSize; ++j) {
            for (k = 0; k < gridSize; ++k) {
                if (j == k) {
                    continue;
                }
                dp[i][j] = fmin(dp[i][j], dp[i - 1][k] + grid[i][j]);
            }
        }
    }

    retVal = dp[gridSize - 1][0];
    for (i = 1; i < gridSize; ++i) {
        retVal = fmin(retVal, dp[gridSize - 1][i]);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        int retVal = 0;

        int gridSize = grid.size();

        vector<vector<int>> dp(gridSize, vector<int>(gridSize, numeric_limits<int>::max()));
        for (int i = 0; i < gridSize; ++i) {
            dp[0][i] = grid[0][i];
        }

        for (int i = 1; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                for (int k = 0; k < gridSize; ++k) {
                    if (j == k) {
                        continue;
                    }
                    dp[i][j] = min(dp[i][j], dp[i - 1][k] + grid[i][j]);
                }
            }
        }

        retVal = dp[gridSize - 1][0];
        for (int i = 1; i < gridSize; ++i) {
            retVal = min(retVal, dp[gridSize - 1][i]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minFallingPathSum(self, grid: List[List[int]]) -> int:
        retVal = 0

        gridSize = len(grid)

        dp = [[float('inf') for _ in range(gridSize)] for _ in range(gridSize)]
        for i in range(gridSize):
            dp[0][i] = grid[0][i]

        for i in range(gridSize):
            for j in range(gridSize):
                for k in range(gridSize):
                    if j == k:
                        continue
                    dp[i][j] = min(dp[i][j], dp[i - 1][k] + grid[i][j])

        retVal = min(dp[gridSize - 1])

        return retVal
```

</details>

## [1312. Minimum Insertion Steps to Make a String Palindrome](https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/)  1786

- [Official](https://leetcode.cn/problems/minimum-insertion-steps-to-make-a-string-palindrome/solutions/101721/rang-zi-fu-chuan-cheng-wei-hui-wen-chuan-de-zui--2/)

<details><summary>Description</summary>

```text
Given a string s. In one step you can insert any character at any index of the string.

Return the minimum number of steps to make s palindrome.

A Palindrome String is one that reads the same backward as well as forward.

Example 1:
Input: s = "zzazz"
Output: 0
Explanation: The string "zzazz" is already palindrome we do not need any insertions.

Example 2:
Input: s = "mbadm"
Output: 2
Explanation: String can be "mbdadbm" or "mdbabdm".

Example 3:
Input: s = "leetcode"
Output: 5
Explanation: Inserting 5 characters the string becomes "leetcodocteel".


Constraints:
1 <= s.length <= 500
s consists of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Is dynamic programming suitable for this problem ?
2. If we know the longest palindromic sub-sequence is x and the length of the string is n then,
   what is the answer to this problem?
   It is n - x as we need n - x insertions to make the remaining characters also palindrome.
```

</details>

</details>

<details><summary>C</summary>

```c
int minInsertions(char *s) {
    int retVal = 0;

    int sSize = strlen(s);
    int dp[sSize + 1][sSize + 1];
    memset(dp, 0, sizeof(dp));

    int i, j;
    char sReverse[sSize + 1];
    memset(sReverse, 0, sizeof(sReverse));
    for (i = 0; i < sSize; ++i) {
        sReverse[sSize - 1 - i] = s[i];
    }
    for (i = 1; i <= sSize; ++i) {
        for (j = 1; j <= sSize; ++j) {
            dp[i][j] = fmax(dp[i - 1][j], dp[i][j - 1]);
            if (s[i - 1] == sReverse[j - 1]) {
                dp[i][j] = fmax(dp[i][j], dp[i - 1][j - 1] + 1);
            }
        }
    }
    retVal = sSize - dp[sSize][sSize];

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minInsertions(string s) {
        int retVal = 0;

        int sSize = s.size();
        vector<vector<int>> dp(sSize + 1, vector<int>(sSize + 1));

        string sReverse(s.rbegin(), s.rend());
        for (int i = 1; i <= sSize; ++i) {
            for (int j = 1; j <= sSize; ++j) {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                if (s[i - 1] == sReverse[j - 1]) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
                }
            }
        }
        retVal = sSize - dp[sSize][sSize];

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minInsertions(self, s: str) -> int:
        retVal = 0

        sSize = len(s)
        dp = [[0] * (sSize + 1) for _ in range(sSize + 1)]

        sReverse = s[::-1]
        for i in range(1, sSize + 1):
            for j in range(1, sSize + 1):
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
                if s[i - 1] == sReverse[j - 1]:
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1)
        retVal = sSize - dp[sSize][sSize]

        return retVal
```

</details>

## [1314. Matrix Block Sum](https://leetcode.com/problems/matrix-block-sum/)  1483

- [Official](https://leetcode.cn/problems/matrix-block-sum/solutions/101300/ju-zhen-qu-yu-he-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given a m x n matrix mat and an integer k,
return a matrix answer where each answer[i][j] is the sum of all elements mat[r][c] for:
- i - k <= r <= i + k,
- j - k <= c <= j + k, and
- (r, c) is a valid position in the matrix.

Example 1:
Input: mat = [[1,2,3],[4,5,6],[7,8,9]], k = 1
Output: [[12,21,16],[27,45,33],[24,39,28]]

Example 2:
Input: mat = [[1,2,3],[4,5,6],[7,8,9]], k = 2
Output: [[45,45,45],[45,45,45],[45,45,45]]

Constraints:
m == mat.length
n == mat[i].length
1 <= m, n, k <= 100
1 <= mat[i][j] <= 100
```

</details>

<details><summary>C</summary>

```c
int** matrixBlockSum(int** mat, int matSize, int* matColSize, int k, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    int i, j;

    (*returnSize) = matSize;
    pRetVal = (int**)malloc((*returnSize) * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }

    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }

    int x, y, sum;
    for (i = 0; i < (*returnSize); ++i) {
        (*returnColumnSizes)[i] = matColSize[i];
        pRetVal[i] = (int*)malloc(((*returnColumnSizes)[i]) * sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            (*returnSize) = 0;
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
        memset(pRetVal[i], 0, (((*returnColumnSizes)[i]) * sizeof(int)));

        for (j = 0; j < ((*returnColumnSizes)[i]); ++j) {
            sum = 0;
            for (x = i - k; x <= i + k; ++x) {
                if ((x < 0) || (x >= matSize)) {
                    continue;
                }
                for (y = j - k; y <= j + k; ++y) {
                    if ((y < 0) || (y >= matColSize[i])) {
                        continue;
                    }
                    sum += mat[x][y];
                }
            }
            pRetVal[i][j] = sum;
        }
    }

    return pRetVal;
}
```

</details>

## [1326. Minimum Number of Taps to Open to Water a Garden](https://leetcode.com/problems/minimum-number-of-taps-to-open-to-water-a-garden/)  1885

- [Official](https://leetcode.com/problems/minimum-number-of-taps-to-open-to-water-a-garden/editorial/)
- [Official](https://leetcode.cn/problems/minimum-number-of-taps-to-open-to-water-a-garden/solutions/101269/guan-gai-hua-yuan-de-zui-shao-shui-long-tou-shu-3/)

<details><summary>Description</summary>

```text
There is a one-dimensional garden on the x-axis.
The garden starts at the point 0 and ends at the point n. (i.e The length of the garden is n).

There are n + 1 taps located at points [0, 1, ..., n] in the garden.

Given an integer n and an integer array ranges of length n + 1
where ranges[i] (0-indexed) means the i-th tap can water the area [i - ranges[i], i + ranges[i]] if it was open.

Return the minimum number of taps that should be open to water the whole garden,
If the garden cannot be watered return -1.

Example 1:
Input: n = 5, ranges = [3,4,1,1,0,0]
Output: 1
Explanation: The tap at point 0 can cover the interval [-3,3]
The tap at point 1 can cover the interval [-3,5]
The tap at point 2 can cover the interval [1,3]
The tap at point 3 can cover the interval [2,4]
The tap at point 4 can cover the interval [4,4]
The tap at point 5 can cover the interval [5,5]
Opening Only the second tap will water the whole garden [0,5]

Example 2:
Input: n = 3, ranges = [0,0,0,0]
Output: -1
Explanation: Even if you activate all the four taps you cannot water the whole garden.

Constraints:
1 <= n <= 10^4
ranges.length == n + 1
0 <= ranges[i] <= 100
```

<details><summary>Hint</summary>

```text
1. Create intervals of the area covered by each tap, sort intervals by the left end.
2. We need to cover the interval [0, n].
   we can start with the first interval and out of all intervals that intersect with it we choose the one
   that covers the farthest point to the right.
3. What if there is a gap between intervals that is not covered ?
   we should stop and return -1 as there is some interval that cannot be covered.
```

</details>

</details>

<details><summary>C</summary>

```c
int minTaps(int n, int* ranges, int rangesSize) {
    int retVal = -1;

    int i, j;

    // 1 <= n <= 10^4; ranges.length == n + 1; 0 <= ranges[i] <= 100
    int infinity = (int)(1e9);

    int dpSize = n + 1;
    int dp[dpSize];
    memset(dp, 0, sizeof(dp));
    dp[0] = 0;
    for (i = 1; i < dpSize; ++i) {
        dp[i] = infinity;
    }

    int tapStart, tapEnd;
    for (i = 0; i <= n; ++i) {
        tapStart = fmax(0, i - ranges[i]);
        tapEnd = fmin(n, i + ranges[i]);
        for (j = tapStart; j <= tapEnd; ++j) {
            dp[tapEnd] = fmin(dp[tapEnd], dp[j] + 1);
        }
    }

    if (dp[n] != infinity) {
        retVal = dp[n];
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minTaps(int n, vector<int>& ranges) {
        int retVal = -1;

        // 1 <= n <= 10^4; ranges.length == n + 1; 0 <= ranges[i] <= 100
        int infinity = (int)(1e9);

        vector<int> dp(n + 1, infinity);
        dp[0] = 0;

        for (int i = 0; i <= n; ++i) {
            int tapStart = max(0, i - ranges[i]);
            int tapEnd = min(n, i + ranges[i]);
            for (int j = tapStart; j <= tapEnd; ++j) {
                dp[tapEnd] = min(dp[tapEnd], dp[j] + 1);
            }
        }

        if (dp[n] != infinity) {
            retVal = dp[n];
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minTaps(self, n: int, ranges: List[int]) -> int:
        retVal = -1

        # 1 <= n <= 10^4; ranges.length == n + 1; 0 <= ranges[i] <= 100
        infinity = int(1e9)

        dp = [infinity] * (n + 1)
        dp[0] = 0

        for i in range(n + 1):
            tapStart = max(0, i - ranges[i])
            tapEnd = min(n, i + ranges[i])
            for j in range(tapStart, tapEnd + 1):
                dp[tapEnd] = min(dp[tapEnd], dp[j] + 1)

        if dp[n] != infinity:
            retVal = dp[n]

        return retVal
```

</details>

## [1335. Minimum Difficulty of a Job Schedule](https://leetcode.com/problems/minimum-difficulty-of-a-job-schedule/)  2034

- [Official](https://leetcode.cn/problems/minimum-difficulty-of-a-job-schedule/solutions/2271103/gong-zuo-ji-hua-de-zui-di-nan-du-by-leet-dule/)

<details><summary>Description</summary>

```text
You want to schedule a list of jobs in d days.
Jobs are dependent (i.e To work on the ith job, you have to finish all the jobs j where 0 <= j < i).

You have to finish at least one task every day.
The difficulty of a job schedule is the sum of difficulties of each day of the d days.
The difficulty of a day is the maximum difficulty of a job done on that day.

You are given an integer array jobDifficulty and an integer d.
The difficulty of the ith job is jobDifficulty[i].

Return the minimum difficulty of a job schedule.
If you cannot find a schedule for the jobs return -1.

Example 1:
Input: jobDifficulty = [6,5,4,3,2,1], d = 2
Output: 7
Explanation: First day you can finish the first 5 jobs, total difficulty = 6.
Second day you can finish the last job, total difficulty = 1.
The difficulty of the schedule = 6 + 1 = 7

Example 2:
Input: jobDifficulty = [9,9,9], d = 4
Output: -1
Explanation: If you finish a job per day you will still have a free day. you cannot find a schedule for the given jobs.

Example 3:
Input: jobDifficulty = [1,1,1], d = 3
Output: 3
Explanation: The schedule is one job per day. total difficulty will be 3.

Constraints:
1 <= jobDifficulty.length <= 300
0 <= jobDifficulty[i] <= 1000
1 <= d <= 10
```

<details><summary>Hint</summary>

```text
1. Use DP. Try to cut the array into d non-empty sub-arrays. Try all possible cuts for the array.
2. Use dp[i][j] where DP states are i the index of the last cut and j the number of remaining cuts.
   Complexity is O(n * n * d).
```

</details>

</details>

<details><summary>C</summary>

```c
int minDifficulty(int* jobDifficulty, int jobDifficultySize, int d) {
    int retVal = -1;

    if (jobDifficultySize < d) {
        return retVal;
    }

    int i, j;

    int maxDifficulty = 0;
    int dp[jobDifficultySize];
    for (i = 0; i < jobDifficultySize; ++i) {
        maxDifficulty = fmax(maxDifficulty, jobDifficulty[i]);
        dp[i] = maxDifficulty;
    }

    int minDifficulty;
    int monotonicStack[jobDifficultySize][2];
    int monotonicStackTop;
    int dpNext[jobDifficultySize];
    for (i = 1; i < d; ++i) {
        memset(dpNext, 0, sizeof(dpNext));
        memset(monotonicStack, 0, sizeof(monotonicStack));
        monotonicStackTop = 0;

        for (j = i; j < jobDifficultySize; ++j) {
            minDifficulty = dp[j - 1];
            while ((monotonicStackTop > 0) &&
                   (jobDifficulty[monotonicStack[monotonicStackTop - 1][0]] < jobDifficulty[j])) {
                minDifficulty = fmin(minDifficulty, monotonicStack[monotonicStackTop - 1][1]);
                --monotonicStackTop;
            }

            if (monotonicStackTop == 0) {
                dpNext[j] = minDifficulty + jobDifficulty[j];
            } else {
                dpNext[j] = fmin(dpNext[monotonicStack[monotonicStackTop - 1][0]], minDifficulty + jobDifficulty[j]);
            }
            monotonicStack[monotonicStackTop][0] = j;
            monotonicStack[monotonicStackTop][1] = minDifficulty;
            ++monotonicStackTop;
        }
        memcpy(dp, dpNext, sizeof(dp));
    }
    retVal = dp[jobDifficultySize - 1];

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        int retVal = -1;

        int jobDifficultySize = jobDifficulty.size();
        if (jobDifficultySize < d) {
            return retVal;
        }

        int maxDifficulty = 0;
        vector<int> dp(jobDifficultySize);
        for (int i = 0; i < jobDifficultySize; ++i) {
            maxDifficulty = max(maxDifficulty, jobDifficulty[i]);
            dp[i] = maxDifficulty;
        }

        for (int i = 1; i < d; ++i) {
            vector<int> dpNext(jobDifficultySize);

            stack<pair<int, int>> monotonicStack;
            for (int j = i; j < jobDifficultySize; ++j) {
                int minDifficulty = dp[j - 1];
                while ((monotonicStack.empty() == false) &&
                       (jobDifficulty[monotonicStack.top().first] < jobDifficulty[j])) {
                    minDifficulty = min(minDifficulty, monotonicStack.top().second);
                    monotonicStack.pop();
                }

                if (monotonicStack.empty() == true) {
                    dpNext[j] = minDifficulty + jobDifficulty[j];
                } else {
                    dpNext[j] = min(dpNext[monotonicStack.top().first], minDifficulty + jobDifficulty[j]);
                }
                monotonicStack.emplace(j, minDifficulty);
            }
            swap(dp, dpNext);
        }
        retVal = dp[jobDifficultySize - 1];

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minDifficulty(self, jobDifficulty: List[int], d: int) -> int:
        retVal = -1

        jobDifficultySize = len(jobDifficulty)
        if jobDifficultySize < d:
            return retVal

        maxDifficulty = 0
        dp = [0] * jobDifficultySize
        for i in range(jobDifficultySize):
            maxDifficulty = max(maxDifficulty, jobDifficulty[i])
            dp[i] = maxDifficulty

        for i in range(1, d):
            dpNext = [0] * jobDifficultySize

            monotonicStack = []
            for j in range(i, jobDifficultySize):
                minDifficulty = dp[j - 1]
                while monotonicStack and jobDifficulty[monotonicStack[-1][0]] < jobDifficulty[j]:
                    minDifficulty = min(minDifficulty, monotonicStack[-1][1])
                    monotonicStack.pop()

                if monotonicStack:
                    dpNext[j] = min(dpNext[monotonicStack[-1][0]], minDifficulty + jobDifficulty[j])
                else:
                    dpNext[j] = minDifficulty + jobDifficulty[j]

                monotonicStack.append((j, minDifficulty))

            dp = dpNext

        retVal = dp[jobDifficultySize - 1]

        return retVal
```

</details>

## [1359. Count All Valid Pickup and Delivery Options](https://leetcode.com/problems/count-all-valid-pickup-and-delivery-options/)  1722

- [Official](https://leetcode.cn/problems/count-all-valid-pickup-and-delivery-options/solutions/108077/you-xiao-de-kuai-di-xu-lie-shu-mu-by-leetcode-solu/)

<details><summary>Description</summary>

```text
Given n orders, each order consist in pickup and delivery services.

Count all valid pickup/delivery possible sequences such that delivery(i) is always after of pickup(i).

Since the answer may be too large, return it modulo 10^9 + 7.

Example 1:
Input: n = 1
Output: 1
Explanation: Unique order (P1, D1), Delivery 1 always is after of Pickup 1.

Example 2:
Input: n = 2
Output: 6
Explanation: All possible orders:
(P1,P2,D1,D2), (P1,P2,D2,D1), (P1,D1,P2,D2), (P2,P1,D1,D2), (P2,P1,D2,D1) and (P2,D2,P1,D1).
This is an invalid order (P1,D2,P2,D1) because Pickup 2 is after of Delivery 2.

Example 3:
Input: n = 3
Output: 90

Constraints:
1 <= n <= 500
```

<details><summary>Hint</summary>

```text
1. Use the permutation and combination theory to add one (P, D) pair each time until n pairs.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MODULO (int)(1e9 + 7)
int countOrders(int n) {
    int retVal = 0;

    // https://leetcode.com/problems/count-all-valid-pickup-and-delivery-options/solutions/516968/java-c-python-easy-and-concise/
    long combinatorics = 1;
    int i;
    for (i = 1; i <= n; ++i) {
        combinatorics = combinatorics * ((i * 2 - 1) * i) % MODULO;
    }
    retVal = combinatorics;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define MODULO (int)(1e9 + 7)
   public:
    int countOrders(int n) {
        int retVal = 0;

        // https://leetcode.com/problems/count-all-valid-pickup-and-delivery-options/solutions/516968/java-c-python-easy-and-concise/
        long combinatorics = 1;
        for (int i = 1; i <= n; ++i) {
            combinatorics = combinatorics * ((i * 2 - 1) * i) % MODULO;
        }
        retVal = combinatorics;

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

    def countOrders(self, n: int) -> int:
        retVal = 0

        # https://leetcode.com/problems/count-all-valid-pickup-and-delivery-options/solutions/516968/java-c-python-easy-and-concise/
        combinatorics = 1
        for i in range(1, n+1):
            combinatorics = combinatorics * ((i * 2 - 1) * i) % self.MODULO
        retVal = combinatorics

        return retVal
```

</details>

## [1395. Count Number of Teams](https://leetcode.com/problems/count-number-of-teams/)  1343

- [Official](https://leetcode.com/problems/count-number-of-teams/editorial/)
- [Official](https://leetcode.cn/problems/count-number-of-teams/solutions/186425/tong-ji-zuo-zhan-dan-wei-shu-by-leetcode-solution/)

<details><summary>Description</summary>

```text
There are n soldiers standing in a line. Each soldier is assigned a unique rating value.

You have to form a team of 3 soldiers amongst them under the following rules:
- Choose 3 soldiers with index (i, j, k) with rating (rating[i], rating[j], rating[k]).
- A team is valid if: (rating[i] < rating[j] < rating[k]) or (rating[i] > rating[j] > rating[k])
  where (0 <= i < j < k < n).

Return the number of teams you can form given the conditions. (soldiers can be part of multiple teams).

Example 1:
Input: rating = [2,5,3,4,1]
Output: 3
Explanation: We can form three teams given the conditions. (2,3,4), (5,4,1), (5,3,1).

Example 2:
Input: rating = [2,1,3]
Output: 0
Explanation: We can't form any team given the conditions.

Example 3:
Input: rating = [1,2,3,4]
Output: 4

Constraints:
n == rating.length
3 <= n <= 1000
1 <= rating[i] <= 10^5
All the integers in rating are unique.
```

<details><summary>Hint</summary>

```text
1. BruteForce, check all possibilities.
```

</details>

</details>

<details><summary>C</summary>

```c
int numTeams(int* rating, int ratingSize) {
    int retVal = 0;

    int leftLarger, rightSmaller;
    int leftSmaller, rightLarger;
    int middle, left, right;
    for (middle = 0; middle < ratingSize; ++middle) {
        // Count soldiers with smaller ratings on the left side of the current soldier
        leftSmaller = 0;
        for (left = middle - 1; left >= 0; --left) {
            if (rating[left] < rating[middle]) {
                leftSmaller += 1;
            }
        }

        // Count soldiers with larger ratings on the right side of the current soldier
        rightLarger = 0;
        for (right = middle + 1; right < ratingSize; ++right) {
            if (rating[right] > rating[middle]) {
                rightLarger += 1;
            }
        }

        // Calculate and add the number of ascending rating teams (small-middle-large)
        retVal += (leftSmaller * rightLarger);

        // Calculate soldiers with larger ratings on the left and smaller ratings on the right
        leftLarger = middle - leftSmaller;
        rightSmaller = ratingSize - middle - 1 - rightLarger;

        // Calculate and add the number of descending rating teams (large-middle-small)
        retVal += (leftLarger * rightSmaller);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int numTeams(vector<int>& rating) {
        int retVal = 0;

        int ratingSize = rating.size();
        for (int middle = 0; middle < ratingSize; ++middle) {
            // Count soldiers with smaller ratings on the left side of the current soldier
            int leftSmaller = 0;
            for (int left = middle - 1; left >= 0; --left) {
                if (rating[left] < rating[middle]) {
                    leftSmaller += 1;
                }
            }

            // Count soldiers with larger ratings on the right side of the current soldier
            int rightLarger = 0;
            for (int right = middle + 1; right < ratingSize; ++right) {
                if (rating[right] > rating[middle]) {
                    rightLarger += 1;
                }
            }

            // Calculate and add the number of ascending rating teams (small-middle-large)
            retVal += (leftSmaller * rightLarger);

            // Calculate soldiers with larger ratings on the left and smaller ratings on the right
            int leftLarger = middle - leftSmaller;
            int rightSmaller = ratingSize - middle - 1 - rightLarger;

            // Calculate and add the number of descending rating teams (large-middle-small)
            retVal += (leftLarger * rightSmaller);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def numTeams(self, rating: List[int]) -> int:
        retVal = 0

        ratingSize = len(rating)
        for middle in range(ratingSize):
            # Count soldiers with smaller ratings on the left side of the current soldier
            leftSmaller = 0
            for left in range(middle - 1, -1, -1):
                if rating[left] < rating[middle]:
                    leftSmaller += 1

            # Count soldiers with larger ratings on the right side of the current soldier
            rightLarger = 0
            for right in range(middle + 1, ratingSize):
                if rating[right] > rating[middle]:
                    rightLarger += 1

            # Calculate and add the number of ascending rating teams (small-middle-large)
            retVal += (leftSmaller * rightLarger)

            # Calculate soldiers with larger ratings on the left and smaller ratings on the right
            leftLarger = middle - leftSmaller
            rightSmaller = ratingSize - middle - 1 - rightLarger

            # Calculate and add the number of descending rating teams (large-middle-small)
            retVal += (leftLarger * rightSmaller)

        return retVal
```

</details>

## [1406. Stone Game III](https://leetcode.com/problems/stone-game-iii/)  2026

- [Official](https://leetcode.com/problems/stone-game-iii/editorial/)
- [Official](https://leetcode.cn/problems/stone-game-iii/solutions/327144/shi-zi-you-xi-iii-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Alice and Bob continue their games with piles of stones.
There are several stones arranged in a row,
and each stone has an associated value which is an integer given in the array stoneValue.

Alice and Bob take turns, with Alice starting first.
On each player's turn, that player can take 1, 2, or 3 stones from the first remaining stones in the row.

The score of each player is the sum of the values of the stones taken. The score of each player is 0 initially.

The objective of the game is to end with the highest score,
and the winner is the player with the highest score and there could be a tie.
The game continues until all the stones have been taken.

Assume Alice and Bob play optimally.

Return "Alice" if Alice will win, "Bob" if Bob will win, or "Tie" if they will end the game with the same score.

Example 1:
Input: values = [1,2,3,7]
Output: "Bob"
Explanation: Alice will always lose. Her best move will be to take three piles and the score become 6.
Now the score of Bob is 7 and Bob wins.

Example 2:
Input: values = [1,2,3,-9]
Output: "Alice"
Explanation: Alice must choose all the three piles at the first move to win and leave Bob with negative score.
If Alice chooses one pile her score will be 1 and the next move Bob's score becomes 5.
In the next move, Alice will take the pile with value = -9 and lose.
If Alice chooses two piles her score will be 3 and the next move Bob's score becomes 3.
In the next move, Alice will take the pile with value = -9 and also lose.
Remember that both play optimally so here Alice will choose the scenario that makes her win.

Example 3:
Input: values = [1,2,3,6]
Output: "Tie"
Explanation: Alice cannot win this game.
She can end the game in a draw if she decided to choose all the first three piles, otherwise she will lose.

Constraints:
1 <= stoneValue.length <= 5 * 10^4
-1000 <= stoneValue[i] <= 1000
```

<details><summary>Hint</summary>

```text
1. The game can be mapped to minmax game. Alice tries to maximize the total score and Bob tries to minimize it.
2. Use dynamic programming to simulate the game.
   If the total score was 0 the game is "Tie", and if it has positive value then "Alice" wins, otherwise "Bob" wins.
```

</details>

</details>

<details><summary>C</summary>

```c
char* stoneGameIII(int* stoneValue, int stoneValueSize) {
    char* pRetVal = "Tie";

    int dp[stoneValueSize + 1];
    memset(dp, 0, sizeof(dp));
    int i;
    for (i = stoneValueSize - 1; i >= 0; --i) {
        dp[i] = stoneValue[i] - dp[i + 1];
        if (i + 2 <= stoneValueSize) {
            dp[i] = fmax(dp[i], stoneValue[i] + stoneValue[i + 1] - dp[i + 2]);
        }
        if (i + 3 <= stoneValueSize) {
            dp[i] = fmax(dp[i], stoneValue[i] + stoneValue[i + 1] + stoneValue[i + 2] - dp[i + 3]);
        }
    }

    if (dp[0] > 0) {
        pRetVal = "Alice";
    } else if (dp[0] < 0) {
        pRetVal = "Bob";
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string stoneGameIII(vector<int>& stoneValue) {
        string retVal = "Tie";

        int stoneValueSize = stoneValue.size();
        vector<int> dp(stoneValueSize + 1, 0);
        for (int i = stoneValueSize - 1; i >= 0; --i) {
            dp[i] = stoneValue[i] - dp[i + 1];
            if (i + 2 <= stoneValueSize) {
                dp[i] = max(dp[i], stoneValue[i] + stoneValue[i + 1] - dp[i + 2]);
            }
            if (i + 3 <= stoneValueSize) {
                dp[i] = max(dp[i], stoneValue[i] + stoneValue[i + 1] + stoneValue[i + 2] - dp[i + 3]);
            }
        }

        if (dp[0] > 0) {
            retVal = "Alice";
        } else if (dp[0] < 0) {
            retVal = "Bob";
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def stoneGameIII(self, stoneValue: List[int]) -> str:
        retVal = "Tie"

        stoneValueSize = len(stoneValue)
        dp = [0] * (stoneValueSize + 1)
        for i in range(stoneValueSize - 1, -1, -1):
            dp[i] = stoneValue[i] - dp[i + 1]
            if i + 2 <= stoneValueSize:
                dp[i] = max(dp[i], stoneValue[i] + stoneValue[i + 1] - dp[i + 2])
            if i + 3 <= stoneValueSize:
                dp[i] = max(dp[i], stoneValue[i] + stoneValue[i + 1] + stoneValue[i + 2] - dp[i + 3])

        if dp[0] > 0:
            retVal = "Alice"
        elif dp[0] < 0:
            retVal = "Bob"

        return retVal
```

</details>

## [1416. Restore The Array](https://leetcode.com/problems/restore-the-array/)  1919

- [Official](https://leetcode.cn/problems/restore-the-array/solutions/223857/hui-fu-shu-zu-by-leetcode-solution/)

<details><summary>Description</summary>

```text
A program was supposed to print an array of integers.
The program forgot to print whitespaces and the array is printed as a string of digits s
and all we know is that all integers in the array were in the range [1, k] and there are no leading zeros in the array.

Given the string s and the integer k,
return the number of the possible arrays that can be printed as s using the mentioned program.
Since the answer may be very large, return it modulo 109 + 7.

Example 1:
Input: s = "1000", k = 10000
Output: 1
Explanation: The only possible array is [1000]

Example 2:
Input: s = "1000", k = 10
Output: 0
Explanation: There cannot be an array that was printed this way and has all integer >= 1 and <= 10.

Example 3:
Input: s = "1317", k = 2000
Output: 8
Explanation: Possible arrays are [1317],[131,7],[13,17],[1,317],[13,1,7],[1,31,7],[1,3,17],[1,3,1,7]

Constraints:
1 <= s.length <= 10^5
s consists of only digits and does not contain leading zeros.
1 <= k <= 10^9
```

<details><summary>Hint</summary>

```text
1. Use dynamic programming.
   Build an array dp where dp[i] is the number of ways you can divide the string starting from index i to the end.
2. Keep in mind that the answer is modulo 10^9 + 7 and take the mod for each operation.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MODULO (int)(1e9 + 7)
int numberOfArrays(char *s, int k) {
    int retVal = 0;

    int sSize = strlen(s);

    // dp[i] is the number of ways you can divide the string starting from index i to the end.
    int dp[sSize + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    long long num;
    int i, j;
    for (i = 0; i < sSize; ++i) {
        if (s[i] == '0') {
            continue;
        }

        num = s[i] - '0';
        for (j = (i + 1); j < (sSize + 1); ++j) {
            if (num > (long long)k) {
                break;
            }
            num *= 10;
            num += s[j] - '0';

            dp[j] += dp[i];
            dp[j] %= MODULO;
        }

        dp[i] %= MODULO;
    }
    retVal = dp[sSize] % MODULO;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define MODULO (int)(1e9 + 7)
   public:
    int numberOfArrays(string s, int k) {
        int retVal = 0;

        int sSize = s.size();

        // dp[i] is the number of ways you can divide the string starting from index i to the end.
        vector<int> dp(sSize + 1, 0);
        dp[0] = 1;

        for (int i = 0; i < sSize; ++i) {
            if (s[i] == '0') {
                continue;
            }

            long long num = s[i] - '0';
            for (int j = (i + 1); j < (sSize + 1); ++j) {
                if (num > (long long)k) {
                    break;
                }
                num *= 10;
                num += s[j] - '0';

                dp[j] += dp[i];
                dp[j] %= MODULO;
            }

            dp[i] %= MODULO;
        }
        retVal = dp.back() % MODULO;

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

    def numberOfArrays(self, s: str, k: int) -> int:
        retVal = 0

        sSize = len(s)

        # dp[i] is the number of ways you can divide the string starting from index i to the end.
        dp = [0] * (sSize + 1)
        dp[0] = 1

        for i in range(0, sSize):
            if s[i] == '0':
                continue

            for j in range(i+1, sSize+1):
                if int(s[i:j]) > k:
                    break

                dp[j] += dp[i]

            dp[i] %= self.MODULO

        retVal = dp[-1] % self.MODULO

        return retVal
```

</details>

## [1420. Build Array Where You Can Find The Maximum Exactly K Comparisons](https://leetcode.com/problems/build-array-where-you-can-find-the-maximum-exactly-k-comparisons/)  2175

- [Official](https://leetcode.com/problems/build-array-where-you-can-find-the-maximum-exactly-k-comparisons/editorial/)
- [Official](https://leetcode.cn/problems/build-array-where-you-can-find-the-maximum-exactly-k-comparisons/solutions/514326/sheng-cheng-shu-zu-by-leetcode-solution-yswf/)

<details><summary>Description</summary>

```text
You are given three integers n, m and k.
Consider the following algorithm to find the maximum element of an array of positive integers:

maximum_value = -1
maximum_index = -1
search_cost = 0
n = arr.length
for (i = 0; i < n; i++) {
    if (maximum_value < arr[i]) {
        maximum_value = arr[i]
        maximum_index = i
        search_cost = search_cost + 1
    }
}
return maximum_index

You should build the array arr which has the following properties:
- arr has exactly n integers.
- 1 <= arr[i] <= m where (0 <= i < n).
- After applying the mentioned algorithm to arr, the value search_cost is equal to k.

Return the number of ways to build the array arr under the mentioned conditions.
As the answer may grow large, the answer must be computed modulo 10^9 + 7.

Example 1:
Input: n = 2, m = 3, k = 1
Output: 6
Explanation: The possible arrays are [1, 1], [2, 1], [2, 2], [3, 1], [3, 2] [3, 3]

Example 2:
Input: n = 5, m = 2, k = 3
Output: 0
Explanation: There are no possible arrays that satisify the mentioned conditions.

Example 3:
Input: n = 9, m = 1, k = 1
Output: 1
Explanation: The only possible array is [1, 1, 1, 1, 1, 1, 1, 1, 1]

Constraints:
1 <= n <= 50
1 <= m <= 100
0 <= k <= n
```

<details><summary>Hint</summary>

```text
1. Use dynamic programming approach.
   Build dp table where dp[a][b][c] is the number of ways you can start building the array
   starting from index a where the search_cost = c and the maximum used integer was b.
2. Recursively, solve the small sub-problems first.
   Optimize your answer by stopping the search if you exceeded k changes.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MODULO (int)(1e9 + 7)
int numOfArrays(int n, int m, int k) {
    int retVal = 0;

    long long dp[m + 1][k + 1];
    memset(dp, 0, sizeof(dp));
    long long prefix[m + 1][k + 1];
    memset(prefix, 0, sizeof(prefix));
    long long prevDp[m + 1][k + 1];
    memset(prevDp, 0, sizeof(prevDp));
    long long prevPrefix[m + 1][k + 1];
    memset(prevPrefix, 0, sizeof(prevPrefix));

    int i;
    for (i = 1; i <= m; i++) {
        dp[i][1] = 1;
    }
    long long answer;
    int maxNum, cost;
    for (i = 1; i <= n; i++) {
        if (i > 1) {
            memset(dp, 0, sizeof(dp));
        }

        memset(prefix, 0, sizeof(prefix));
        for (maxNum = 1; maxNum <= m; maxNum++) {
            for (cost = 1; cost <= k; cost++) {
                answer = (maxNum * prevDp[maxNum][cost]) % MODULO;
                answer = (answer + prevPrefix[maxNum - 1][cost - 1]) % MODULO;

                dp[maxNum][cost] += answer;
                dp[maxNum][cost] %= MODULO;

                prefix[maxNum][cost] = (prefix[maxNum - 1][cost] + dp[maxNum][cost]);
                prefix[maxNum][cost] %= MODULO;
            }
        }

        for (maxNum = 0; maxNum <= m; maxNum++) {
            for (cost = 0; cost <= k; cost++) {
                prevDp[maxNum][cost] = dp[maxNum][cost];
                prevPrefix[maxNum][cost] = prefix[maxNum][cost];
            }
        }
    }
    retVal = prefix[m][k];

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define MODULO (int)(1e9 + 7)
   public:
    int numOfArrays(int n, int m, int k) {
        int retVal = 0;

        long long dp[m + 1][k + 1];
        memset(dp, 0, sizeof(dp));
        long long prefix[m + 1][k + 1];
        memset(prefix, 0, sizeof(prefix));
        long long prevDp[m + 1][k + 1];
        memset(prevDp, 0, sizeof(prevDp));
        long long prevPrefix[m + 1][k + 1];
        memset(prevPrefix, 0, sizeof(prevPrefix));

        for (int num = 1; num <= m; num++) {
            dp[num][1] = 1;
        }
        for (int i = 1; i <= n; i++) {
            if (i > 1) {
                memset(dp, 0, sizeof(dp));
            }

            memset(prefix, 0, sizeof(prefix));
            for (int maxNum = 1; maxNum <= m; maxNum++) {
                for (int cost = 1; cost <= k; cost++) {
                    long long answer = (maxNum * prevDp[maxNum][cost]) % MODULO;
                    answer = (answer + prevPrefix[maxNum - 1][cost - 1]) % MODULO;

                    dp[maxNum][cost] += answer;
                    dp[maxNum][cost] %= MODULO;

                    prefix[maxNum][cost] = (prefix[maxNum - 1][cost] + dp[maxNum][cost]);
                    prefix[maxNum][cost] %= MODULO;
                }
            }

            for (int maxNum = 0; maxNum <= m; maxNum++) {
                for (int cost = 0; cost <= k; cost++) {
                    prevDp[maxNum][cost] = dp[maxNum][cost];
                    prevPrefix[maxNum][cost] = prefix[maxNum][cost];
                }
            }
        }
        retVal = prefix[m][k];

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

    def numOfArrays(self, n: int, m: int, k: int) -> int:
        retVal = 0

        dp = [[0] * (k + 1) for _ in range(m + 1)]
        prefix = [[0] * (k + 1) for _ in range(m + 1)]
        prevDp = [[0] * (k + 1) for _ in range(m + 1)]
        prevPrefix = [[0] * (k + 1) for _ in range(m + 1)]

        for num in range(1, m + 1):
            dp[num][1] = 1
        for i in range(1, n + 1):
            if i > 1:
                dp = [[0] * (k + 1) for _ in range(m + 1)]

            prefix = [[0] * (k + 1) for _ in range(m + 1)]
            for max_num in range(1, m + 1):
                for cost in range(1, k + 1):
                    answer = (max_num * prevDp[max_num][cost]) % self.MODULO
                    answer = (answer + prevPrefix[max_num - 1][cost - 1]) % self.MODULO

                    dp[max_num][cost] += answer
                    dp[max_num][cost] %= self.MODULO

                    prefix[max_num][cost] = (prefix[max_num - 1][cost] + dp[max_num][cost]) % self.MODULO

            prevDp = dp
            prevPrefix = prefix

        retVal = prefix[m][k]

        return retVal
```

</details>

## [1425. Constrained Subsequence Sum](https://leetcode.com/problems/constrained-subsequence-sum/)  2032

- [Official](https://leetcode.com/problems/constrained-subsequence-sum/editorial/)
- [Official](https://leetcode.cn/problems/constrained-subsequence-sum/solutions/514353/dai-xian-zhi-de-zi-xu-lie-he-by-leetcode-k5dw/)

<details><summary>Description</summary>

```text
Given an integer array nums and an integer k,
return the maximum sum of a non-empty subsequence of that array such that
for every two consecutive integers in the subsequence, nums[i] and nums[j],
where i < j, the condition j - i <= k is satisfied.

A subsequence of an array is obtained by deleting some number of elements (can be zero) from the array,
leaving the remaining elements in their original order.

Example 1:
Input: nums = [10,2,-10,5,20], k = 2
Output: 37
Explanation: The subsequence is [10, 2, 5, 20].

Example 2:
Input: nums = [-1,-2,-3], k = 1
Output: -1
Explanation: The subsequence must be non-empty, so we choose the largest number.

Example 3:
Input: nums = [10,-2,-10,-5,20], k = 2
Output: 23
Explanation: The subsequence is [10, -2, -5, 20].

Constraints:
1 <= k <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4
```

<details><summary>Hint</summary>

```text
1. Use dynamic programming.
2. Let dp[i] be the solution for the prefix of the array that ends at index i,
   if the element at index i is in the subsequence.
3. dp[i] = nums[i] + max(0, dp[i-k], dp[i-k+1], ..., dp[i-1])
4. Use a heap with the sliding window technique to optimize the dp.
```

</details>

</details>

<details><summary>C</summary>

```c
int constrainedSubsetSum(int* nums, int numsSize, int k) {
    int retVal = 0;

    struct deque {
        int value;
        int index;
    } monotonicDeque[numsSize];
    int monotonicDequeHead = 0;
    int monotonicDequeTail = 0;
    monotonicDeque[monotonicDequeTail].value = nums[0];
    monotonicDeque[monotonicDequeTail].index = 0;
    monotonicDequeTail++;

    int dp[numsSize];
    memset(dp, 0, sizeof(dp));
    dp[0] = nums[0];

    retVal += nums[0];

    int i;
    for (i = 1; i < numsSize; i++) {
        dp[i] = fmax(0, dp[monotonicDeque[monotonicDequeHead].index]) + nums[i];
        retVal = fmax(retVal, dp[i]);

        while ((monotonicDequeHead < monotonicDequeTail) &&
               (dp[i] >= dp[monotonicDeque[monotonicDequeTail - 1].index])) {
            monotonicDequeTail--;
        }
        monotonicDeque[monotonicDequeTail].value = nums[i];
        monotonicDeque[monotonicDequeTail].index = i;
        monotonicDequeTail++;
        if ((i - monotonicDeque[monotonicDequeHead].index) >= k) {
            monotonicDequeHead++;
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
    int constrainedSubsetSum(vector<int>& nums, int k) {
        int retVal = 0;

        int numsSize = nums.size();

        deque<int> monotonicDeque;
        vector<int> dp(numsSize);

        for (int i = 0; i < numsSize; i++) {
            if ((monotonicDeque.empty() == false) && (i - monotonicDeque.front() > k)) {
                monotonicDeque.pop_front();
            }

            dp[i] = ((monotonicDeque.empty() == false) ? (dp[monotonicDeque.front()]) : (0)) + nums[i];
            while ((monotonicDeque.empty() == false) && (dp[monotonicDeque.back()] < dp[i])) {
                monotonicDeque.pop_back();
            }

            if (dp[i] > 0) {
                monotonicDeque.push_back(i);
            }
        }

        retVal = *max_element(dp.begin(), dp.end());

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def constrainedSubsetSum(self, nums: List[int], k: int) -> int:
        retVal = 0

        numsSize = len(nums)

        monotonicDeque = deque()
        dp = [0] * numsSize

        for i in range(numsSize):
            if monotonicDeque and i - monotonicDeque[0] > k:
                monotonicDeque.popleft()

            dp[i] = (dp[monotonicDeque[0]] if monotonicDeque else 0) + nums[i]
            while monotonicDeque and dp[monotonicDeque[-1]] < dp[i]:
                monotonicDeque.pop()

            if dp[i] > 0:
                monotonicDeque.append(i)

        retVal = max(dp)

        return retVal
```

</details>

## [1444. Number of Ways of Cutting a Pizza](https://leetcode.com/problems/number-of-ways-of-cutting-a-pizza/)  2126

<details><summary>Description</summary>

```text
Given a rectangular pizza represented as a rows x cols matrix containing the following characters:
'A' (an apple) and '.' (empty cell) and given the integer k.
You have to cut the pizza into k pieces using k-1 cuts.

For each cut you choose the direction: vertical or horizontal,
then you choose a cut position at the cell boundary and cut the pizza into two pieces.
If you cut the pizza vertically, give the left part of the pizza to a person.
If you cut the pizza horizontally, give the upper part of the pizza to a person.
Give the last piece of pizza to the last person.

Return the number of ways of cutting the pizza such that each piece contains at least one apple.
Since the answer can be a huge number, return this modulo 10^9 + 7.

Example 1:
Input: pizza = ["A..","AAA","..."], k = 3
Output: 3
Explanation: The figure above shows the three ways to cut the pizza. Note that pieces must contain at least one apple.

Example 2:
Input: pizza = ["A..","AA.","..."], k = 3
Output: 1

Example 3:
Input: pizza = ["A..","A..","..."], k = 1
Output: 1

Constraints:
1 <= rows, cols <= 50
rows == pizza.length
cols == pizza[i].length
1 <= k <= 10
pizza consists of characters 'A' and '.' only.
```

<details><summary>Hint</summary>

```text
1. Note that after each cut the remaining piece of pizza always has the lower right coordinate at (rows-1,cols-1).
2. Use dynamic programming approach with states (row1, col1, c) which
   computes the number of ways of cutting the pizza using "c" cuts where
   the current piece of pizza has upper left coordinate at (row1,col1) and lower right coordinate at (rows-1,cols-1).
3. For the transitions try all vertical and horizontal cuts
   such that the piece of pizza you have to give a person must contain at least one apple.
   The base case is when c=k-1.
4. Additionally use a 2D dynamic programming to respond in O(1) if a piece of pizza contains at least one apple.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MODULO (int)(1e9 + 7)
// https://leetcode.com/problems/number-of-ways-of-cutting-a-pizza/solutions/623732/java-c-python-dp-prefixsum-in-matrix-clean-code/
int dfs(int row, int col, int k, int r, int c, int*** dp, int** preSum) {
    int retVal = 0;

    // if the remain piece has no apple -> invalid
    if (preSum[r][c] == 0) {
        return retVal;
    }

    // found valid way after using k-1 cuts
    if (k == 0) {
        retVal = 1;
        return retVal;
    }

    if (dp[k][r][c] != -1) {
        retVal = dp[k][r][c];
        return retVal;
    }

    // cut in horizontal
    int nr;
    for (nr = r + 1; nr < row; nr++) {
        // cut if the upper piece contains at least one apple
        if (preSum[r][c] - preSum[nr][c] > 0) {
            retVal = (retVal + dfs(row, col, k - 1, nr, c, dp, preSum)) % MODULO;
        }
    }

    // cut in vertical
    int nc;
    for (nc = c + 1; nc < col; nc++) {
        // cut if the left piece contains at least one apple
        if (preSum[r][c] - preSum[r][nc] > 0) {
            retVal = (retVal + dfs(row, col, k - 1, r, nc, dp, preSum)) % MODULO;
        }
    }

    dp[k][r][c] = retVal;

    return retVal;
}
int ways(char** pizza, int pizzaSize, int k) {
    int retVal = 0;

    int x, y, z;
    int row = pizzaSize;
    int col = strlen(pizza[0]);

    int** preSum = (int**)calloc(row + 1, sizeof(int*));
    if (preSum == NULL) {
        perror("calloc");
        return retVal;
    }
    for (x = 0; x < (row + 1); ++x) {
        preSum[x] = (int*)calloc((col + 1), sizeof(int));
        if (preSum[x] == NULL) {
            perror("calloc");
            return retVal;
        }
    }
    for (x = row - 1; x >= 0; --x) {
        for (y = col - 1; y >= 0; --y) {
            preSum[x][y] = preSum[x][y + 1] + preSum[x + 1][y] - preSum[x + 1][y + 1] + (pizza[x][y] == 'A');
        }
    }

    int*** dp = (int***)calloc(k, sizeof(int**));
    if (dp == NULL) {
        perror("calloc");
        return retVal;
    }
    for (x = 0; x < k; ++x) {
        dp[x] = (int**)calloc(row, sizeof(int*));
        if (dp[x] == NULL) {
            perror("calloc");
            return retVal;
        }
        for (y = 0; y < row; ++y) {
            dp[x][y] = (int*)calloc(col, sizeof(int));
            if (dp[x][y] == NULL) {
                perror("calloc");
                return retVal;
            }
            for (z = 0; z < col; ++z) {
                dp[x][y][z] = -1;
            }
        }
    }

    retVal = dfs(row, col, k - 1, 0, 0, dp, preSum);

    for (x = 0; x < (row + 1); ++x) {
        free(preSum[x]);
        preSum[x] = NULL;
    }
    free(preSum);
    preSum = NULL;
    for (x = 0; x < k; ++x) {
        for (y = 0; y < row; ++y) {
            free(dp[x][y]);
            dp[x][y] = NULL;
        }
        free(dp[x]);
        dp[x] = NULL;
    }
    free(dp);
    dp = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define MODULO (int)(1e9 + 7)
   public:
    // https://leetcode.com/problems/number-of-ways-of-cutting-a-pizza/solutions/623732/java-c-python-dp-prefixsum-in-matrix-clean-code/
    int dfs(int row, int col, int k, int r, int c, vector<vector<vector<int>>>& dp, vector<vector<int>>& preSum) {
        int retVal = 0;

        // if the remain piece has no apple -> invalid
        if (preSum[r][c] == 0) {
            return retVal;
        }

        // found valid way after using k-1 cuts
        if (k == 0) {
            retVal = 1;
            return retVal;
        }

        if (dp[k][r][c] != -1) {
            retVal = dp[k][r][c];
            return retVal;
        }

        // cut in horizontal
        for (int nr = r + 1; nr < row; nr++) {
            // cut if the upper piece contains at least one apple
            if (preSum[r][c] - preSum[nr][c] > 0) {
                retVal = (retVal + dfs(row, col, k - 1, nr, c, dp, preSum)) % MODULO;
            }
        }

        // cut in vertical
        for (int nc = c + 1; nc < col; nc++) {
            // cut if the left piece contains at least one apple
            if (preSum[r][c] - preSum[r][nc] > 0) {
                retVal = (retVal + dfs(row, col, k - 1, r, nc, dp, preSum)) % MODULO;
            }
        }

        dp[k][r][c] = retVal;

        return retVal;
    }
    int ways(vector<string>& pizza, int k) {
        int retVal = 0;

        int row = pizza.size();
        int col = pizza[0].size();

        // preSum[r][c] is the total number of apples in pizza[r:][c:]
        vector<vector<int>> preSum = vector(row + 1, vector(col + 1, 0));
        for (int r = row - 1; r >= 0; r--) {
            for (int c = col - 1; c >= 0; c--) {
                preSum[r][c] = preSum[r][c + 1] + preSum[r + 1][c] - preSum[r + 1][c + 1] + (pizza[r][c] == 'A');
            }
        }

        vector<vector<vector<int>>> dp = vector(k, vector(row, vector(col, -1)));
        retVal = dfs(row, col, k - 1, 0, 0, dp, preSum);

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

    # https://leetcode.com/problems/number-of-ways-of-cutting-a-pizza/solutions/623732/java-c-python-dp-prefixsum-in-matrix-clean-code/
    def ways(self, pizza: List[str], k: int) -> int:
        retVal = 0

        row = len(pizza)
        col = len(pizza[0])
        preSum = [[0] * (col + 1) for _ in range(row + 1)]
        for r in range(row - 1, -1, -1):
            for c in range(col - 1, -1, -1):
                preSum[r][c] = preSum[r][c + 1] + preSum[r + 1][c] - preSum[r + 1][c + 1] + (pizza[r][c] == 'A')

        @lru_cache(None)
        def dp(k, r, c):
            retVal = 0

            # if the remain piece has no apple -> invalid
            if preSum[r][c] == 0:
                return retVal

            # found valid way after using k-1 cuts
            if k == 0:
                retVal = 1
                return retVal

            # cut horizontally
            for nr in range(r + 1, row):
                if preSum[r][c] - preSum[nr][c] > 0:
                    retVal = (retVal + dp(k - 1, nr, c)) % self.MODULO

            # cut vertically
            for nc in range(c + 1, col):
                if preSum[r][c] - preSum[r][nc] > 0:
                    retVal = (retVal + dp(k - 1, r, nc)) % self.MODULO

            return retVal

        retVal = dp(k - 1, 0, 0)

        return retVal
```

</details>

## [1458. Max Dot Product of Two Subsequences](https://leetcode.com/problems/max-dot-product-of-two-subsequences/)  1823

- [Official](https://leetcode.com/problems/max-dot-product-of-two-subsequences/editorial/)
- [Official](https://leetcode.cn/problems/max-dot-product-of-two-subsequences/solutions/519006/liang-ge-zi-xu-lie-de-zui-da-dian-ji-by-jwqux/)

<details><summary>Description</summary>

```text
Given two arrays nums1 and nums2.

Return the maximum dot product between non-empty subsequences of nums1 and nums2 with the same length.

A subsequence of a array is a new array which is formed from the original array
by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters.
(ie, [2,3,5] is a subsequence of [1,2,3,4,5] while [1,5,3] is not).

Example 1:
Input: nums1 = [2,1,-2,5], nums2 = [3,0,-6]
Output: 18
Explanation: Take subsequence [2,-2] from nums1 and subsequence [3,-6] from nums2.
Their dot product is (2*3 + (-2)*(-6)) = 18.

Example 2:
Input: nums1 = [3,-2], nums2 = [2,-6,7]
Output: 21
Explanation: Take subsequence [3] from nums1 and subsequence [7] from nums2.
Their dot product is (3*7) = 21.

Example 3:
Input: nums1 = [-1,-1], nums2 = [1,1]
Output: -1
Explanation: Take subsequence [-1] from nums1 and subsequence [1] from nums2.
Their dot product is -1.

Constraints:
1 <= nums1.length, nums2.length <= 500
-1000 <= nums1[i], nums2[i] <= 1000
```

<details><summary>Hint</summary>

```text
1. Use dynamic programming,
   define DP[i][j] as the maximum dot product of two subsequences
   starting in the position i of nums1 and position j of nums2.
```

</details>

</details>

<details><summary>C</summary>

```c
int maxDotProduct(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int retVal = 0;

    int dp[nums1Size][nums2Size];
    memset(dp, 0, sizeof(dp));
    int product;
    int row, col;
    for (row = 0; row < nums1Size; ++row) {
        for (col = 0; col < nums2Size; ++col) {
            product = nums1[row] * nums2[col];

            dp[row][col] = product;
            if (row > 0) {
                dp[row][col] = fmax(dp[row][col], dp[row - 1][col]);
            }
            if (col > 0) {
                dp[row][col] = fmax(dp[row][col], dp[row][col - 1]);
            }
            if ((row > 0) && (col > 0)) {
                dp[row][col] = fmax(dp[row][col], dp[row - 1][col - 1] + product);
            }
        }
    }
    retVal = dp[nums1Size - 1][nums2Size - 1];

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        int retVal = 0;

        int nums1Size = nums1.size();
        int nums2Size = nums2.size();
        vector<vector<int>> dp(nums1Size, vector<int>(nums2Size, 0));
        for (int row = 0; row < nums1Size; ++row) {
            for (int col = 0; col < nums2Size; ++col) {
                int product = nums1[row] * nums2[col];

                dp[row][col] = product;
                if (row > 0) {
                    dp[row][col] = max(dp[row][col], dp[row - 1][col]);
                }
                if (col > 0) {
                    dp[row][col] = max(dp[row][col], dp[row][col - 1]);
                }
                if ((row > 0) && (col > 0)) {
                    dp[row][col] = max(dp[row][col], dp[row - 1][col - 1] + product);
                }
            }
        }
        retVal = dp[nums1Size - 1][nums2Size - 1];

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxDotProduct(self, nums1: List[int], nums2: List[int]) -> int:
        retVal = 0

        nums1Size = len(nums1)
        nums2Size = len(nums2)
        dp = [[0] * nums2Size for _ in range(nums1Size)]

        for row in range(nums1Size):
            for col in range(nums2Size):
                product = nums1[row] * nums2[col]

                dp[row][col] = product
                if row > 0:
                    dp[row][col] = max(dp[row][col], dp[row - 1][col])
                if col > 0:
                    dp[row][col] = max(dp[row][col], dp[row][col - 1])
                if row > 0 and col > 0:
                    dp[row][col] = max(dp[row][col], dp[row - 1][col - 1] + product)

        retVal = dp[nums1Size - 1][nums2Size - 1]

        return retVal
```

</details>

## [1463. Cherry Pickup II](https://leetcode.com/problems/cherry-pickup-ii/)  1956

- [Official](https://leetcode.cn/problems/cherry-pickup-ii/solutions/521172/zhai-ying-tao-ii-by-leetcode-solution-v2k5/)

<details><summary>Description</summary>

```text
You are given a rows x cols matrix grid representing a field of cherries
where grid[i][j] represents the number of cherries that you can collect from the (i, j) cell.

You have two robots that can collect cherries for you:
- Robot #1 is located at the top-left corner (0, 0), and
- Robot #2 is located at the top-right corner (0, cols - 1).

Return the maximum number of cherries collection using both robots by following the rules below:
- From a cell (i, j), robots can move to cell (i + 1, j - 1), (i + 1, j), or (i + 1, j + 1).
- When any robot passes through a cell, It picks up all cherries, and the cell becomes an empty cell.
- When both robots stay in the same cell, only one takes the cherries.
- Both robots cannot move outside of the grid at any moment.
- Both robots should reach the bottom row in grid.

Example 1:
Input: grid = [[3,1,1],[2,5,1],[1,5,5],[2,1,1]]
Output: 24
Explanation: Path of robot #1 and #2 are described in color green and blue respectively.
Cherries taken by Robot #1, (3 + 2 + 5 + 2) = 12.
Cherries taken by Robot #2, (1 + 5 + 5 + 1) = 12.
Total of cherries: 12 + 12 = 24.

Example 2:
Input: grid = [[1,0,0,0,0,0,1],[2,0,0,0,0,3,0],[2,0,9,0,0,0,0],[0,3,0,5,4,0,0],[1,0,2,3,0,0,6]]
Output: 28
Explanation: Path of robot #1 and #2 are described in color green and blue respectively.
Cherries taken by Robot #1, (1 + 9 + 5 + 2) = 17.
Cherries taken by Robot #2, (1 + 3 + 4 + 3) = 11.
Total of cherries: 17 + 11 = 28.

Constraints:
rows == grid.length
cols == grid[i].length
2 <= rows, cols <= 70
0 <= grid[i][j] <= 100
```

<details><summary>Hint</summary>

```text
1. Use dynammic programming, define DP[i][j][k]: The maximum cherries
   that both robots can take starting on the ith row, and column j and k of Robot 1 and 2 respectively.
```

</details>

</details>

<details><summary>C</summary>

```c
int cherryPickup(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int rowSize = gridSize;
    int colSize = gridColSize[0];
    int i, j, k;

    int dp[rowSize][colSize][colSize];
    for (i = 0; i < rowSize; ++i) {
        for (j = 0; j < colSize; ++j) {
            for (k = 0; k < colSize; ++k) {
                dp[i][j][k] = -1;
            }
        }
    }
    dp[0][0][colSize - 1] = grid[0][0] + grid[0][colSize - 1];

    int a, b, c, d, e, f, g, h, t, temp;
    for (i = 1; i < rowSize; ++i) {
        for (j = 0; j < colSize; ++j) {
            for (k = 0; k < colSize; ++k) {
                a = -1;
                if ((i > 0) && (j > 0) && (k > 0)) {
                    a = dp[i - 1][j - 1][k - 1];
                }

                b = -1;
                if ((i > 0) && (j > 0)) {
                    b = dp[i - 1][j - 1][k];
                }

                c = -1;
                if ((i > 0) && (j > 0) && (k + 1 < colSize)) {
                    c = dp[i - 1][j - 1][k + 1];
                }

                d = -1;
                if ((i > 0) && (k > 0)) {
                    d = dp[i - 1][j][k - 1];
                }

                e = -1;
                if (i > 0) {
                    e = dp[i - 1][j][k];
                }

                f = -1;
                if ((i > 0) && (k + 1 < colSize)) {
                    f = dp[i - 1][j][k + 1];
                }

                g = -1;
                if ((i > 0) && (j + 1 < colSize) && (k > 0)) {
                    g = dp[i - 1][j + 1][k - 1];
                }

                h = -1;
                if ((i > 0) && (j + 1 < colSize)) {
                    h = dp[i - 1][j + 1][k];
                }

                t = -1;
                if ((i > 0) && (j + 1 < colSize) && (k + 1 < colSize)) {
                    t = dp[i - 1][j + 1][k + 1];
                }

                temp = fmax(fmax(fmax(fmax(a, b), fmax(c, d)), fmax(fmax(e, f), fmax(g, h))), t);
                if (temp == -1) {
                    dp[i][j][k] = -1;
                } else {
                    if (j == k) {
                        dp[i][j][k] = temp + grid[i][j];
                    } else {
                        dp[i][j][k] = temp + grid[i][j] + grid[i][k];
                    }
                }
            }
        }
    }

    for (i = 0; i < colSize; ++i) {
        for (j = 0; j < colSize; ++j) {
            retVal = fmax(retVal, dp[rowSize - 1][i][j]);
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
    int cherryPickup(vector<vector<int>>& grid) {
        int retVal = 0;

        int rowSize = grid.size();
        int colSize = grid[0].size();

        vector<vector<vector<int>>> dp(rowSize, vector<vector<int>>(colSize, vector<int>(colSize, -1)));
        dp[0][0][colSize - 1] = grid[0][0] + grid[0][colSize - 1];
        for (int i = 1; i < rowSize; ++i) {
            for (int j = 0; j < colSize; ++j) {
                for (int k = 0; k < colSize; ++k) {
                    int a = -1;
                    if ((i > 0) && (j > 0) && (k > 0)) {
                        a = dp[i - 1][j - 1][k - 1];
                    }

                    int b = -1;
                    if ((i > 0) && (j > 0)) {
                        b = dp[i - 1][j - 1][k];
                    }

                    int c = -1;
                    if ((i > 0) && (j > 0) && (k + 1 < colSize)) {
                        c = dp[i - 1][j - 1][k + 1];
                    }

                    int d = -1;
                    if ((i > 0) && (k > 0)) {
                        d = dp[i - 1][j][k - 1];
                    }

                    int e = -1;
                    if (i > 0) {
                        e = dp[i - 1][j][k];
                    }

                    int f = -1;
                    if ((i > 0) && (k + 1 < colSize)) {
                        f = dp[i - 1][j][k + 1];
                    }

                    int g = -1;
                    if ((i > 0) && (j + 1 < colSize) && (k > 0)) {
                        g = dp[i - 1][j + 1][k - 1];
                    }

                    int h = -1;
                    if ((i > 0) && (j + 1 < colSize)) {
                        h = dp[i - 1][j + 1][k];
                    }

                    int t = -1;
                    if ((i > 0) && (j + 1 < colSize) && (k + 1 < colSize)) {
                        t = dp[i - 1][j + 1][k + 1];
                    }

                    int temp = max(max(max(max(a, b), max(c, d)), max(max(e, f), max(g, h))), t);
                    if (temp == -1) {
                        dp[i][j][k] = -1;
                    } else {
                        if (j == k) {
                            dp[i][j][k] = temp + grid[i][j];
                        } else {
                            dp[i][j][k] = temp + grid[i][j] + grid[i][k];
                        }
                    }
                }
            }
        }

        for (int i = 0; i < colSize; ++i) {
            for (int j = 0; j < colSize; ++j) {
                retVal = max(retVal, dp[rowSize - 1][i][j]);
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
    def cherryPickup(self, grid: List[List[int]]) -> int:
        retVal = 0

        rowSize = len(grid)
        colSize = len(grid[0])

        dp = [[[-1] * colSize for _ in range(colSize)] for _ in range(rowSize)]
        dp[0][0][colSize-1] = grid[0][0] + grid[0][colSize-1]
        for i in range(1, rowSize):
            for j in range(colSize):
                for k in range(colSize):
                    a = -1
                    if (i > 0) and (j > 0) and (k > 0):
                        a = dp[i-1][j-1][k-1]

                    b = -1
                    if (i > 0) and (j > 0):
                        b = dp[i-1][j-1][k]

                    c = -1
                    if (i > 0) and (j > 0) and (k + 1 < colSize):
                        c = dp[i-1][j-1][k+1]

                    d = -1
                    if (i > 0) and (k > 0):
                        d = dp[i-1][j][k-1]

                    e = -1
                    if i > 0:
                        e = dp[i-1][j][k]

                    f = -1
                    if (i > 0) and (k + 1 < colSize):
                        f = dp[i-1][j][k+1]


                    g = -1
                    if (i > 0) and (j + 1 < colSize) and (k > 0):
                        g = dp[i-1][j+1][k-1]

                    h = -1
                    if (i > 0) and (j + 1 < colSize):
                        h = dp[i-1][j+1][k]

                    t = -1
                    if (i > 0) and (j + 1 < colSize) and (k + 1 < colSize):
                        t = dp[i-1][j+1][k+1]

                    temp = max(a, b, c, d, e, f, g, h, t)
                    if temp == -1:
                        dp[i][j][k] = -1
                    else:
                        if j == k:
                            dp[i][j][k] = temp + grid[i][j]
                        else:
                            dp[i][j][k] = temp + grid[i][j] + grid[i][k]

        for i in range(colSize):
            for j in range(colSize):
                retVal = max(retVal, dp[rowSize-1][i][j])

        return retVal
```

</details>

## [1547. Minimum Cost to Cut a Stick](https://leetcode.com/problems/minimum-cost-to-cut-a-stick/)  2116

- [Official](https://leetcode.com/problems/minimum-cost-to-cut-a-stick/editorial/)
- [Official](https://leetcode.cn/problems/minimum-cost-to-cut-a-stick/solutions/379074/qie-gun-zi-de-zui-xiao-cheng-ben-by-leetcode-solut/)

<details><summary>Description</summary>

```text
Given a wooden stick of length n units. The stick is labelled from 0 to n.
For example, a stick of length 6 is labelled as follows:

Given an integer array cuts where cuts[i] denotes a position you should perform a cut at.

You should perform the cuts in order, you can change the order of the cuts as you wish.

The cost of one cut is the length of the stick to be cut, the total cost is the sum of costs of all cuts.
When you cut a stick,
it will be split into two smaller sticks (i.e. the sum of their lengths is the length of the stick before the cut).
Please refer to the first example for a better explanation.

Return the minimum total cost of the cuts.

Example 1:
Input: n = 7, cuts = [1,3,4,5]
Output: 16
Explanation: Using cuts order = [1, 3, 4, 5] as in the input leads to the following scenario:
The first cut is done to a rod of length 7 so the cost is 7.
The second cut is done to a rod of length 6
(i.e. the second part of the first cut),
the third is done to a rod of length 4 and the last cut is to a rod of length 3. The total cost is 7 + 6 + 4 + 3 = 20.
Rearranging the cuts to be [3, 5, 1, 4]
for example will lead to a scenario with total cost = 16 (as shown in the example photo 7 + 4 + 3 + 2 = 16).

Example 2:
Input: n = 9, cuts = [5,6,1,4,2]
Output: 22
Explanation: If you try the given cuts ordering the cost will be 25.
There are much ordering with total cost <= 25,
for example, the order [4, 6, 5, 2, 1] has total cost = 22 which is the minimum possible.

Constraints:
2 <= n <= 10^6
1 <= cuts.length <= min(n - 1, 100)
1 <= cuts[i] <= n - 1
All the integers in cuts array are distinct.
```

<details><summary>Hint</summary>

```text
1. Build a dp array where dp[i][j] is the minimum cost to achieve all the cuts between i and j.
2. When you try to get the minimum cost between i and j, try all possible cuts k between them,
   dp[i][j] = min(dp[i][k] + dp[k][j]) + (j - i) for all possible cuts k between them.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int minCost(int n, int* cuts, int cutsSize) {
    int retVal = 0;

    // 2 <= n <= 10^6, 1 <= cuts[i] <= n - 1
    int sortCutsSize = cutsSize + 2;
    int sortCuts[sortCutsSize];
    memset(sortCuts, 0, sizeof(sortCuts));
    memcpy(sortCuts + 1, cuts, cutsSize * sizeof(cuts[0]));
    sortCuts[0] = -1;
    sortCuts[sortCutsSize - 1] = INT_MAX;
    qsort(sortCuts, sortCutsSize, sizeof(int), compareInteger);
    sortCuts[0] = 0;
    sortCuts[sortCutsSize - 1] = n;

    int dp[cutsSize + 2][cutsSize + 2];
    memset(dp, 0, sizeof(dp));
    int ans;
    int diff, left, right, mid;
    for (diff = 2; diff < cutsSize + 2; ++diff) {
        for (left = 0; left < cutsSize + 2 - diff; ++left) {
            right = left + diff;
            ans = INT_MAX;
            for (mid = left + 1; mid < right; ++mid) {
                ans = fmin(ans, dp[left][mid] + dp[mid][right] + sortCuts[right] - sortCuts[left]);
            }
            dp[left][right] = ans;
        }
    }

    retVal = dp[0][cutsSize + 1];

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minCost(int n, vector<int>& cuts) {
        int retVal = 0;

        int cutsSize = cuts.size();

        sort(cuts.begin(), cuts.end());
        cuts.insert(cuts.begin(), 0);
        cuts.emplace_back(n);

        vector<vector<int>> dp(cutsSize + 2, vector<int>(cutsSize + 2));
        for (int diff = 2; diff < cutsSize + 2; ++diff) {
            for (int left = 0; left < cutsSize + 2 - diff; ++left) {
                int right = left + diff;
                int ans = numeric_limits<int>::max();
                for (int mid = left + 1; mid < right; ++mid) {
                    ans = min(ans, dp[left][mid] + dp[mid][right] + cuts[right] - cuts[left]);
                }
                dp[left][right] = ans;
            }
        }

        retVal = dp[0][cutsSize + 1];

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minCost(self, n: int, cuts: List[int]) -> int:
        retVal = 0

        cutsSize = len(cuts)

        cuts = [0] + sorted(cuts) + [n]

        dp = [[0] * (cutsSize + 2) for _ in range(cutsSize + 2)]
        for diff in range(2, cutsSize + 2):
            for left in range(cutsSize + 2 - diff):
                right = left + diff
                ans = float('inf')
                for mid in range(left + 1, right):
                    ans = min(ans, dp[left][mid] + dp[mid][right] + cuts[right] - cuts[left])
                dp[left][right] = ans

        retVal = dp[0][cutsSize + 1]

        return retVal
```

</details>

## [1567. Maximum Length of Subarray With Positive Product](https://leetcode.com/problems/maximum-length-of-subarray-with-positive-product/)  1710

- [Official](https://leetcode.cn/problems/maximum-length-of-subarray-with-positive-product/solutions/441152/cheng-ji-wei-zheng-shu-de-zui-chang-zi-shu-zu-ch-3/)

<details><summary>Description</summary>

```text
Given an array of integers nums, find the maximum length of a subarray where the product of all its elements is positive.

A subarray of an array is a consecutive sequence of zero or more values taken out of that array.

Return the maximum length of a subarray with positive product.

Example 1:
Input: nums = [1,-2,-3,4]
Output: 4
Explanation: The array nums already has a positive product of 24.

Example 2:
Input: nums = [0,1,-2,-3,-4]
Output: 3
Explanation: The longest subarray with positive product is [1,-2,-3] which has a product of 6.
Notice that we cannot include 0 in the subarray since that'll make the product 0 which is not positive.

Example 3:
Input: nums = [-1,-2,-3,0,1]
Output: 2
Explanation: The longest subarray with positive product is [-1,-2] or [-2,-3].

Constraints:
1 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9
```

</details>

<details><summary>C</summary>

```c
int getMaxLen(int* nums, int numsSize) {
    int retVal = 0;

    int positive = (nums[0] > 0 ? 1 : 0);
    int negative = (nums[0] < 0 ? 1 : 0);
    retVal = positive;

    int tmp;
    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[i] == 0) {
            positive = 0;
            negative = 0;
        } else if (nums[i] > 0) {
            ++positive;
            negative = (negative > 0 ? negative + 1 : 0);
        } else if (nums[i] < 0) {
            tmp = positive;
            positive = (negative > 0 ? negative + 1 : 0);
            negative = tmp + 1;
        }

        retVal = fmax(retVal, positive);
    }

    return retVal;
}
```

</details>

## [1575. Count All Possible Routes](https://leetcode.com/problems/count-all-possible-routes/)  2055

- [Official](https://leetcode.com/problems/count-all-possible-routes/editorial/)
- [Official](https://leetcode.cn/problems/count-all-possible-routes/solutions/441176/tong-ji-suo-you-ke-xing-lu-jing-by-leetcode-soluti/)

<details><summary>Description</summary>

```text
You are given an array of distinct positive integers locations where locations[i] represents the position of city i.
You are also given integers start, finish and fuel representing the starting city, ending city,
and the initial amount of fuel you have, respectively.

At each step, if you are at city i,
you can pick any city j such that j != i and 0 <= j < locations.length and move to city j.
Moving from city i to city j reduces the amount of fuel you have by |locations[i] - locations[j]|.
Please notice that |x| denotes the absolute value of x.

Notice that fuel cannot become negative at any point in time,
and that you are allowed to visit any city more than once (including start and finish).

Return the count of all possible routes from start to finish.
Since the answer may be too large, return it modulo 10^9 + 7.

Example 1:
Input: locations = [2,3,6,8,4], start = 1, finish = 3, fuel = 5
Output: 4
Explanation: The following are all possible routes, each uses 5 units of fuel:
1 -> 3
1 -> 2 -> 3
1 -> 4 -> 3
1 -> 4 -> 2 -> 3

Example 2:
Input: locations = [4,3,1], start = 1, finish = 0, fuel = 6
Output: 5
Explanation: The following are all possible routes:
1 -> 0, used fuel = 1
1 -> 2 -> 0, used fuel = 5
1 -> 2 -> 1 -> 0, used fuel = 5
1 -> 0 -> 1 -> 0, used fuel = 3
1 -> 0 -> 1 -> 0 -> 1 -> 0, used fuel = 5

Example 3:
Input: locations = [5,2,1], start = 0, finish = 2, fuel = 3
Output: 0
Explanation: It is impossible to get from 0 to 2 using only 3 units of fuel
since the shortest route needs 4 units of fuel.

Constraints:
2 <= locations.length <= 100
1 <= locations[i] <= 10^9
All integers in locations are distinct.
0 <= start, finish < locations.length
1 <= fuel <= 200
```

<details><summary>Hint</summary>

```text
1. Use dynamic programming to solve this problem with each state defined by the city index and fuel left.
2. Since the array contains distinct integers fuel will always be spent in each move and so there can be no cycles.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MODULO (int)(1e9 + 7)
int countRoutes(int* locations, int locationsSize, int start, int finish, int fuel) {
    int retVal = 0;

    int i;

    int dp[locationsSize][fuel + 1];
    memset(dp, 0, sizeof(dp));
    for (i = 0; i <= fuel; i++) {
        dp[finish][i] = 1;
    }

    int src, dst;
    for (i = 0; i <= fuel; ++i) {
        for (src = 0; src < locationsSize; ++src) {
            for (dst = 0; dst < locationsSize; ++dst) {
                if (dst == src) {
                    continue;
                }
                if (abs(locations[src] - locations[dst]) <= i) {
                    dp[src][i] = (dp[src][i] + dp[dst][i - abs(locations[src] - locations[dst])]) % MODULO;
                }
            }
        }
    }

    retVal = dp[start][fuel];

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define MODULO (int)(1e9 + 7)
   public:
    int countRoutes(vector<int>& locations, int start, int finish, int fuel) {
        int retVal = 0;

        int locationsSize = locations.size();
        vector<vector<int>> dp(locationsSize, vector<int>(fuel + 1));
        for (int i = 0; i <= fuel; i++) {
            dp[finish][i] = 1;
        }

        for (int i = 0; i <= fuel; ++i) {
            for (int src = 0; src < locationsSize; ++src) {
                for (int dst = 0; dst < locationsSize; ++dst) {
                    if (dst == src) {
                        continue;
                    }
                    if (abs(locations[src] - locations[dst]) <= i) {
                        dp[src][i] = (dp[src][i] + dp[dst][i - abs(locations[src] - locations[dst])]) % MODULO;
                    }
                }
            }
        }

        retVal = dp[start][fuel];

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

    def countRoutes(self, locations: List[int], start: int, finish: int, fuel: int) -> int:
        retVal = 0

        locationsSize = len(locations)

        dp = [[0] * (fuel + 1) for _ in range(locationsSize)]
        for i in range(fuel + 1):
            dp[finish][i] = 1

        for i in range(fuel + 1):
            for src in range(locationsSize):
                for dst in range(locationsSize):
                    if dst == src:
                        continue
                    if abs(locations[src] - locations[dst]) <= i:
                        dp[src][i] = (dp[src][i] + dp[dst][i - abs(locations[src] - locations[dst])]) % self.MODULO

        retVal = dp[start][fuel]

        return retVal
```

</details>

## [1531. String Compression II](https://leetcode.com/problems/string-compression-ii/)  2575

- [Official](https://leetcode.cn/problems/string-compression-ii/solutions/379042/ya-suo-zi-fu-chuan-ii-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Run-length encoding is a string compression method
that works by replacing consecutive identical characters (repeated 2 or more times)
with the concatenation of the character and the number marking the count of the characters (length of the run).
For example, to compress the string "aabccc" we replace "aa" by "a2" and replace "ccc" by "c3".
Thus the compressed string becomes "a2bc3".

Notice that in this problem, we are not adding '1' after single characters.

Given a string s and an integer k.
You need to delete at most k characters from s such that the run-length encoded version of s has minimum length.

Find the minimum length of the run-length encoded version of s after deleting at most k characters.

Example 1:
Input: s = "aaabcccd", k = 2
Output: 4
Explanation: Compressing s without deleting anything will give us "a3bc3d" of length 6.
Deleting any of the characters 'a' or 'c' would at most decrease the length of the compressed string to 5,
for instance delete 2 'a' then we will have s = "abcccd" which compressed is abc3d.
Therefore, the optimal way is to delete 'b' and 'd', then the compressed version of s will be "a3c3" of length 4.

Example 2:
Input: s = "aabbaa", k = 2
Output: 2
Explanation: If we delete both 'b' characters, the resulting compressed string would be "a4" of length 2.

Example 3:
Input: s = "aaaaaaaaaaa", k = 0
Output: 3
Explanation: Since k is zero, we cannot delete anything. The compressed string is "a11" of length 3.

Constraints:
1 <= s.length <= 100
0 <= k <= s.length
s contains only lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Use dynamic programming.
2. The state of the DP can be the current index and the remaining characters to delete.
3. Having a prefix sum for each character can help you determine for a certain character c in some specific range,
   how many characters you need to delete to merge all occurrences of c in that range.
```

</details>

</details>

<details><summary>C</summary>

```c
int calc(int x) {
    int retVal = 4;

    if (x == 1) {
        retVal = 1;
    } else if (x < 10) {
        retVal = 2;
    } else if (x < 100) {
        retVal = 3;
    }

    return retVal;
}
int getLengthOfOptimalCompression(char *s, int k) {
    int retVal = 0;

    int sSize = strlen(s);

    int dp[sSize + 1][k + 1];
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;

    int same, diff;
    int x, y, z;
    for (x = 1; x <= sSize; ++x) {
        for (y = 0; y <= k && y <= x; ++y) {
            if (y > 0) {
                dp[x][y] = dp[x - 1][y - 1];
            }

            same = 0;
            diff = 0;
            for (z = x; (z >= 1 && diff <= y); --z) {
                if (s[z - 1] == s[x - 1]) {
                    ++same;
                    dp[x][y] = fmin(dp[x][y], dp[z - 1][y - diff] + calc(same));
                } else {
                    ++diff;
                }
            }
        }
    }
    retVal = dp[sSize][k];

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int calc(int x) {
        int retVal = 4;

        if (x == 1) {
            retVal = 1;
        } else if (x < 10) {
            retVal = 2;
        } else if (x < 100) {
            retVal = 3;
        }

        return retVal;
    }
    int getLengthOfOptimalCompression(string s, int k) {
        int retVal = 0;

        int sSize = s.size();

        vector<vector<int>> dp(sSize + 1, vector<int>(k + 1, numeric_limits<int>::max() >> 1));
        dp[0][0] = 0;
        for (int x = 1; x <= sSize; ++x) {
            for (int y = 0; y <= k && y <= x; ++y) {
                if (y > 0) {
                    dp[x][y] = dp[x - 1][y - 1];
                }

                int same = 0;
                int diff = 0;
                for (int z = x; (z >= 1 && diff <= y); --z) {
                    if (s[z - 1] == s[x - 1]) {
                        ++same;
                        dp[x][y] = min(dp[x][y], dp[z - 1][y - diff] + calc(same));
                    } else {
                        ++diff;
                    }
                }
            }
        }
        retVal = dp[sSize][k];

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def calc(self, x: int) -> int:
        retVal = 0

        if x == 1:
            retVal = 1
        elif x < 10:
            retVal = 2
        elif x < 100:
            retVal = 3
        else:
            retVal = 4

        return retVal

    def getLengthOfOptimalCompression(self, s: str, k: int) -> int:
        retVal = 0

        sSize = len(s)

        dp = [[10**9] * (k + 1) for _ in range(sSize + 1)]
        dp[0][0] = 0

        for x in range(1, sSize + 1):
            for y in range(min(k, x) + 1):
                if y > 0:
                    dp[x][y] = dp[x - 1][y - 1]

                same = 0
                diff = 0
                for z in range(x, 0, -1):
                    if s[z - 1] == s[x - 1]:
                        same += 1
                        value = dp[z - 1][y - diff] + self.calc(same)
                        dp[x][y] = min(dp[x][y], value)
                    else:
                        diff += 1
                        if diff > y:
                            break

        retVal = dp[sSize][k]

        return retVal
```

</details>

## [1626. Best Team With No Conflicts](https://leetcode.com/problems/best-team-with-no-conflicts/)  2027

- [Official](https://leetcode.com/problems/best-team-with-no-conflicts/solutions/2886659/best-team-with-no-conflicts/)

<details><summary>Description</summary>

```text
You are the manager of a basketball team.
For the upcoming tournament, you want to choose the team with the highest overall score.
The score of the team is the sum of scores of all the players in the team.

However, the basketball team is not allowed to have conflicts.
A conflict exists if a younger player has a strictly higher score than an older player.
A conflict does not occur between players of the same age.

Given two lists, scores and ages, where each scores[i] and ages[i] represents the score and age of the ith player,
respectively, return the highest overall score of all possible basketball teams.

Example 1:
Input: scores = [1,3,5,10,15], ages = [1,2,3,4,5]
Output: 34
Explanation: You can choose all the players.

Example 2:
Input: scores = [4,5,6,5], ages = [2,1,2,1]
Output: 16
Explanation: It is best to choose the last 3 players. Notice that you are allowed to choose multiple people of the same age.

Example 3:
Input: scores = [1,2,3,5], ages = [8,9,10,1]
Output: 6
Explanation: It is best to choose the first 3 players.

Constraints:
1 <= scores.length, ages.length <= 1000
scores.length == ages.length
1 <= scores[i] <= 106
1 <= ages[i] <= 1000
```

</details>

<details><summary>C</summary>

```c
#define INDEX_AGES (0)
#define INDEX_SCORES (1)
int compareIntArray(const void* pA, const void* pB) {
    int* a = (int*)pA;
    int* b = (int*)pB;

    // ascending order: ages, scores
    if (a[INDEX_AGES] == b[INDEX_AGES]) {
        return (a[INDEX_SCORES] > b[INDEX_SCORES]);
    } else {
        return (a[INDEX_AGES] > b[INDEX_AGES]);
    }
}
int bestTeamScore(int* scores, int scoresSize, int* ages, int agesSize) {
    int retVal = 0;

    int i, j;

    int player[scoresSize][2];
    for (i = 0; i < scoresSize; ++i) {
        player[i][INDEX_AGES] = ages[i];
        player[i][INDEX_SCORES] = scores[i];
    }
    qsort(player, scoresSize, sizeof(player[0]), compareIntArray);

    int dp[scoresSize];
    for (i = 0; i < scoresSize; ++i) {
        dp[i] = player[i][INDEX_SCORES];
        for (j = 0; j < i; ++j) {
            if (player[j][INDEX_SCORES] <= player[i][INDEX_SCORES]) {
                dp[i] = fmax(dp[i], dp[j] + player[i][INDEX_SCORES]);
            }
        }
        retVal = fmax(retVal, dp[i]);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        int retVal = 0;

        int len = scores.size();

        vector<int> player(len);
        for (int i = 0; i < len; ++i) {
            player[i] = i;
        }
        sort(player.begin(), player.end(),
             [&](int i, int j) { return ages[i] < ages[j] || (ages[i] == ages[j] && scores[i] < scores[j]); });

        vector<int> dp(len);
        for (int i = 0; i < len; ++i) {
            int index = player[i];
            dp[i] = scores[index];
            for (int j = 0; j < i; ++j) {
                if (scores[player[j]] <= scores[index]) {
                    dp[i] = max(dp[i], dp[j] + scores[index]);
                }
            }
            retVal = max(retVal, dp[i]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Rust</summary>

```rust
// https://leetcode.com/problems/best-team-with-no-conflicts/solutions/3120917/rust-dp-solution/
use std::cmp;
impl Solution {
    pub fn best_team_score(scores: Vec<i32>, ages: Vec<i32>) -> i32 {
        let mut ret_val = 0;

        let len = scores.len();

        let mut player: Vec<(i32, i32)> = ages.into_iter().zip(scores.into_iter()).collect();
        player.sort_by(|a, b| {
            if a.0 == b.0 {
                a.1.cmp(&b.1)
            } else {
                a.0.cmp(&b.0)
            }
        });

        let mut dp = vec![0; len];
        for i in 0..len {
            dp[i] = player[i].1;
            for j in 0..i {
                if player[j].1 <= player[i].1 {
                    dp[i] = cmp::max(dp[i], dp[j] + player[i].1);
                }
            }
            ret_val = cmp::max(ret_val, dp[i]);
        }

        return ret_val;
    }
}
```

</details>

## [1639. Number of Ways to Form a Target String Given a Dictionary](https://leetcode.com/problems/number-of-ways-to-form-a-target-string-given-a-dictionary/)  2081

- [Official](https://leetcode.com/problems/number-of-ways-to-form-a-target-string-given-a-dictionary/editorial/)

<details><summary>Description</summary>

```text
You are given a list of strings of the same length words and a string target.

Your task is to form target using the given words under the following rules:
- target should be formed from left to right.
- To form the ith character (0-indexed) of target,
  you can choose the kth character of the jth string in words if target[i] = words[j][k].
- Once you use the kth character of the jth string of words,
  you can no longer use the xth character of any string in words where x <= k.
  In other words, all characters to the left of or at index k become unusuable for every string.
- Repeat the process until you form the string target.

Notice that you can use multiple characters from the same string in words provided the conditions above are met.

Return the number of ways to form target from words. Since the answer may be too large, return it modulo 109 + 7.

Example 1:
Input: words = ["acca","bbbb","caca"], target = "aba"
Output: 6
Explanation: There are 6 ways to form target.
"aba" -> index 0 ("acca"), index 1 ("bbbb"), index 3 ("caca")
"aba" -> index 0 ("acca"), index 2 ("bbbb"), index 3 ("caca")
"aba" -> index 0 ("acca"), index 1 ("bbbb"), index 3 ("acca")
"aba" -> index 0 ("acca"), index 2 ("bbbb"), index 3 ("acca")
"aba" -> index 1 ("caca"), index 2 ("bbbb"), index 3 ("acca")
"aba" -> index 1 ("caca"), index 2 ("bbbb"), index 3 ("caca")

Example 2:
Input: words = ["abba","baab"], target = "bab"
Output: 4
Explanation: There are 4 ways to form target.
"bab" -> index 0 ("baab"), index 1 ("baab"), index 2 ("abba")
"bab" -> index 0 ("baab"), index 1 ("baab"), index 3 ("baab")
"bab" -> index 0 ("baab"), index 2 ("baab"), index 3 ("baab")
"bab" -> index 1 ("abba"), index 2 ("baab"), index 3 ("baab")

Constraints:
1 <= words.length <= 1000
1 <= words[i].length <= 1000
All strings in words have the same length.
1 <= target.length <= 1000
words[i] and target contain only lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. For each index i, store the frequency of each character in the ith row.
2. Use dynamic programing to calculate the number of ways to get the target string using the frequency array,
```

</details>

</details>

<details><summary>C</summary>

```c
// https://leetcode.com/problems/number-of-ways-to-form-a-target-string-given-a-dictionary/solutions/917779/java-c-python-space-o-n/
#define MODULO (int)(1e9 + 7)
int numWays(char** words, int wordsSize, char* target) {
    int retVal = 0;

    int targetSize = strlen(target);
    long dp[targetSize + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    int wordLength = strlen(words[0]);
    int count[26];  // words[i] and target contain only lowercase English letters.
    int i, j;
    for (i = 0; i < wordLength; ++i) {
        memset(count, 0, sizeof(count));
        for (j = 0; j < wordsSize; ++j) {
            count[words[j][i] - 'a']++;
        }

        for (j = targetSize - 1; j >= 0; --j) {
            dp[j + 1] += dp[j] * count[target[j] - 'a'] % MODULO;
        }
    }
    retVal = dp[targetSize] % MODULO;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
// https://leetcode.com/problems/number-of-ways-to-form-a-target-string-given-a-dictionary/solutions/917779/java-c-python-space-o-n/
class Solution {
#define MODULO (int)(1e9 + 7)
   public:
    int numWays(vector<string>& words, string target) {
        int retVal = 0;

        int targetSize = target.size();
        vector<long> dp(targetSize + 1, 0);
        dp[0] = 1;
        for (long unsigned int i = 0; i < words[0].size(); ++i) {
            vector<int> count(26);  // words[i] and target contain only lowercase English letters.
            for (auto& word : words) {
                count[word[i] - 'a']++;
            }

            for (int j = targetSize - 1; j >= 0; --j) {
                dp[j + 1] += dp[j] * count[target[j] - 'a'] % MODULO;
            }
        }
        retVal = dp[targetSize] % MODULO;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
# https://leetcode.com/problems/number-of-ways-to-form-a-target-string-given-a-dictionary/solutions/917779/java-c-python-space-o-n/
class Solution:
    def __init__(self):
        self.MODULO = 10 ** 9 + 7

    def numWays(self, words: List[str], target: str) -> int:
        retVal = 0

        targetSize = len(target)
        dp = [1] + [0] * targetSize
        for i in range(len(words[0])):
            count = Counter(word[i] for word in words)
            for j in range(targetSize, 0, -1):
                dp[j] += dp[j-1] * count[target[j-1]] % self.MODULO
        retVal = dp[targetSize] % self.MODULO

        return retVal
```

</details>

## [1653. Minimum Deletions to Make String Balanced](https://leetcode.com/problems/minimum-deletions-to-make-string-balanced/)  1793

- [Official](https://leetcode.com/problems/minimum-deletions-to-make-string-balanced/editorial/)
- [Official](https://leetcode.cn/problems/minimum-deletions-to-make-string-balanced/solutions/2147032/shi-zi-fu-chuan-ping-heng-de-zui-shao-sh-l5lk/)

<details><summary>Description</summary>

```text
You are given a string s consisting only of characters 'a' and 'b'​​​​.

You can delete any number of characters in s to make s balanced.
s is balanced if there is no pair of indices (i,j) such that i < j and s[i] = 'b' and s[j]= 'a'.

Return the minimum number of deletions needed to make s balanced.

Example 1:
Input: s = "aababbab"
Output: 2
Explanation: You can either:
Delete the characters at 0-indexed positions 2 and 6 ("aababbab" -> "aaabbb"), or
Delete the characters at 0-indexed positions 3 and 6 ("aababbab" -> "aabbbb").

Example 2:
Input: s = "bbaaaaabb"
Output: 2
Explanation: The only solution is to delete the first two characters.

Constraints:
1 <= s.length <= 10^5
s[i] is 'a' or 'b'​​.
```

<details><summary>Hint</summary>

```text
1. You need to find for every index the number of Bs before it and the number of A's after it
2. You can speed up the finding of A's and B's in suffix and prefix using preprocessing
```

</details>

</details>

<details><summary>C</summary>

```c
int minimumDeletions(char *s) {
    int retVal = 0;

    /* 926. Flip String to Monotone Increasing
     *  https://leetcode.com/problems/flip-string-to-monotone-increasing/
     */
    int num = 0;
    int sSize = strlen(s);
    int i;
    for (i = 0; i < sSize; ++i) {
        /* Let num be the number of character 'b' in s' prefix of length i:
         *  dp[i] = dp[i - 1] if s[i - 1] = 'b'
         *  dp[i] = min(num, dp[i - 1] + 1) otherwise.
         */
        if (s[i] == 'a') {
            retVal = fmin((retVal + 1), num);
        } else {
            ++num;
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
    int minimumDeletions(string s) {
        int retVal = 0;

        /* 926. Flip String to Monotone Increasing
         *  https://leetcode.com/problems/flip-string-to-monotone-increasing/
         */
        int num = 0;
        for (char c : s) {
            /* Let num be the number of character 'b' in s' prefix of length i:
             *  dp[i] = dp[i - 1] if s[i - 1] = 'b'
             *  dp[i] = min(num, dp[i - 1] + 1) otherwise.
             */
            if (c == 'a') {
                retVal = min((retVal + 1), num);
            } else {
                ++num;
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
    def minimumDeletions(self, s: str) -> int:
        retVal = 0

        # 926. Flip String to Monotone Increasing
        #   https://leetcode.com/problems/flip-string-to-monotone-increasing/
        num = 0
        for c in s:
            # Let num be the number of character 'b' in s' prefix of length i:
            #   dp[i] = dp[i - 1] if s[i - 1] = 'b'
            #   dp[i] = min(num, dp[i - 1] + 1) otherwise.
            if c == 'a':
                retVal = min((retVal + 1), num)
            else:
                num += 1

        return retVal
```

</details>

## [1664. Ways to Make a Fair Array](https://leetcode.com/problems/ways-to-make-a-fair-array/)  1590

- [Official](https://leetcode.cn/problems/ways-to-make-a-fair-array/solutions/2078340/sheng-cheng-ping-heng-shu-zu-de-fang-an-0mkaj/)

<details><summary>Description</summary>

```text
You are given an integer array nums. You can choose exactly one index (0-indexed) and remove the element.
Notice that the index of the elements may change after the removal.

For example, if nums = [6,1,7,4,1]:
- Choosing to remove index 1 results in nums = [6,7,4,1].
- Choosing to remove index 2 results in nums = [6,1,4,1].
- Choosing to remove index 4 results in nums = [6,1,7,4].

An array is fair if the sum of the odd-indexed values equals the sum of the even-indexed values.

Return the number of indices that you could choose such that after the removal, nums is fair.

Example 1:
Input: nums = [2,1,6,4]
Output: 1
Explanation:
Remove index 0: [1,6,4] -> Even sum: 1 + 4 = 5. Odd sum: 6. Not fair.
Remove index 1: [2,6,4] -> Even sum: 2 + 4 = 6. Odd sum: 6. Fair.
Remove index 2: [2,1,4] -> Even sum: 2 + 4 = 6. Odd sum: 1. Not fair.
Remove index 3: [2,1,6] -> Even sum: 2 + 6 = 8. Odd sum: 1. Not fair.
There is 1 index that you can remove to make nums fair.

Example 2:
Input: nums = [1,1,1]
Output: 3
Explanation: You can remove any index and the remaining array is fair.

Example 3:
Input: nums = [1,2,3]
Output: 0
Explanation: You cannot make a fair array after removing any index.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^4
```

</details>

<details><summary>C</summary>

```c
int waysToMakeFair(int* nums, int numsSize) {
    int retVal = 0;

    /* https://leetcode.com/problems/ways-to-make-a-fair-array/solutions/944544/java-python-python-easy-and-concise/
     *
     *  left[odd] + right[even] = left[even] + right[odd]
     *  +-----------------------------+---------------------------+
     *  | 0 | 1 | 2 | 3 | 4 | 5 | ... | 0 _ 2 _ 4 _ | _ 1 _ 3 _ 5 |
     *  +-----------------------------+---------------------------+
     *  |   | 1 | 2 | 3 | 4 | 5 | ... | x _ 2 _ 4 _ | _ 1 _ 3 _ 5 |
     *  | 0 |   | 2 | 3 | 4 | 5 | ... | x _ 2 _ 4 _ | 0 x _ 3 _ 5 |
     *  | 0 | 1 |   | 3 | 4 | 5 | ... | x 1 x _ 4 _ | 0 x _ 3 _ 5 |
     *  | 0 | 1 | 2 |   | 4 | 5 | ... | x 1 x _ 4 _ | 0 x 2 x _ 5 |
     *  | 0 | 1 | 2 | 3 |   | 5 | ... | x 1 x 3 x _ | 0 x 2 x _ 5 |
     *  | 0 | 1 | 2 | 3 | 4 |   | ... | x 1 x 3 x _ | 0 x 2 x 4 x |
     *  +-----------------------------+---------------------------+
     */

    int i;

    int right[2];
    memset(right, 0, sizeof(right));
    for (i = 0; i < numsSize; ++i) {
        right[i % 2] += nums[i];
    }

    int left[2];
    memset(left, 0, sizeof(left));
    for (i = 0; i < numsSize; ++i) {
        right[i % 2] -= nums[i];
        if ((left[(i + 1) % 2] + right[i % 2]) == (left[i % 2] + right[(i + 1) % 2])) {
            ++retVal;
        }
        left[i % 2] += nums[i];
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int waysToMakeFair(vector<int>& nums) {
        int retVal = 0;

        /* https://leetcode.com/problems/ways-to-make-a-fair-array/solutions/944544/java-python-python-easy-and-concise/
         *
         *  left[odd] + right[even] = left[even] + right[odd]
         *  +-----------------------------+---------------------------+
         *  | 0 | 1 | 2 | 3 | 4 | 5 | ... | 0 _ 2 _ 4 _ | _ 1 _ 3 _ 5 |
         *  +-----------------------------+---------------------------+
         *  |   | 1 | 2 | 3 | 4 | 5 | ... | x _ 2 _ 4 _ | _ 1 _ 3 _ 5 |
         *  | 0 |   | 2 | 3 | 4 | 5 | ... | x _ 2 _ 4 _ | 0 x _ 3 _ 5 |
         *  | 0 | 1 |   | 3 | 4 | 5 | ... | x 1 x _ 4 _ | 0 x _ 3 _ 5 |
         *  | 0 | 1 | 2 |   | 4 | 5 | ... | x 1 x _ 4 _ | 0 x 2 x _ 5 |
         *  | 0 | 1 | 2 | 3 |   | 5 | ... | x 1 x 3 x _ | 0 x 2 x _ 5 |
         *  | 0 | 1 | 2 | 3 | 4 |   | ... | x 1 x 3 x _ | 0 x 2 x 4 x |
         *  +-----------------------------+---------------------------+
         */

        int len = nums.size();

        vector<int> right(2, 0);
        for (int i = 0; i < len; ++i) {
            right[i % 2] += nums[i];
        }

        vector<int> left(2, 0);
        for (int i = 0; i < len; ++i) {
            right[i % 2] -= nums[i];
            if ((left[(i + 1) % 2] + right[i % 2]) == (left[i % 2] + right[(i + 1) % 2])) {
                ++retVal;
            }
            left[i % 2] += nums[i];
        }

        return retVal;
    }
};
```

</details>

## [1691. Maximum Height by Stacking Cuboids](https://leetcode.com/problems/maximum-height-by-stacking-cuboids/)  2171

<details><summary>Description</summary>

```text
Given n cuboids where the dimensions of the ith cuboid is cuboids[i] = [widthi, lengthi, heighti] (0-indexed).
Choose a subset of cuboids and place them on each other.

You can place cuboid i on cuboid j if widthi <= widthj and lengthi <= lengthj and heighti <= heightj.
You can rearrange any cuboid's dimensions by rotating it to put it on another cuboid.

Return the maximum height of the stacked cuboids.

Example 1:

Input: cuboids = [[50,45,20],[95,37,53],[45,23,12]]
Output: 190
Explanation:
Cuboid 1 is placed on the bottom with the 53x37 side facing down with height 95.
Cuboid 0 is placed next with the 45x20 side facing down with height 50.
Cuboid 2 is placed next with the 23x12 side facing down with height 45.
The total height is 95 + 50 + 45 = 190.

Example 2:
Input: cuboids = [[38,25,45],[76,35,3]]
Output: 76
Explanation:
You can't place any of the cuboids on the other.
We choose cuboid 1 and rotate it so that the 35x3 side is facing down and its height is 76.

Example 3:
Input: cuboids = [[7,11,17],[7,17,11],[11,7,17],[11,17,7],[17,7,11],[17,11,7]]
Output: 102
Explanation:
After rearranging the cuboids, you can see that all cuboids have the same dimension.
You can place the 11x7 side down on all cuboids so their heights are 17.
The maximum height of stacked cuboids is 6 * 17 = 102.

Constraints:
n == cuboids.length
1 <= n <= 100
1 <= widthi, lengthi, heighti <= 100
```

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int compareIntArray(const void* pa, const void* pb) {
    const int* a = *(const int**)pa;
    const int* b = *(const int**)pb;

    // ascending order
    if ((a[0] == b[0]) && (a[1] == b[1])) {
        return a[2] - b[2];
    } else if (a[0] == b[0]) {
        return a[1] - b[1];
    } else {
        return a[0] - b[0];
    }
}
int maxHeight(int** cuboids, int cuboidsSize, int* cuboidsColSize) {
    int retVal = 0;

    int i, j;

    for (i = 0; i < cuboidsSize; ++i) {
        qsort(cuboids[i], cuboidsColSize[i], sizeof(int), compareInteger);
    }
    qsort(cuboids, cuboidsSize, sizeof(cuboids[0]), compareIntArray);

    int dp[cuboidsSize];
    memset(dp, 0, sizeof(dp));
    for (i = 0; i < cuboidsSize; ++i) {
        for (j = 0; j < i; ++j) {
            if ((cuboids[j][1] <= cuboids[i][1]) && (cuboids[j][2] <= cuboids[i][2])) {
                dp[i] = fmax(dp[i], dp[j]);
            }
        }
        dp[i] += cuboids[i][2];
        retVal = fmax(retVal, dp[i]);
    }

    return retVal;
}
```

</details>

## [1751. Maximum Number of Events That Can Be Attended II](https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended-ii/)  2040

- [Official](https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended-ii/editorial/)

<details><summary>Description</summary>

```text
You are given an array of events where events[i] = [startDayi, endDayi, valuei].
The ith event starts at startDayi and ends at endDayi, and if you attend this event, you will receive a value of valuei.
You are also given an integer k which represents the maximum number of events you can attend.

You can only attend one event at a time.
If you choose to attend an event, you must attend the entire event.
Note that the end day is inclusive:
that is, you cannot attend two events where one of them starts and the other ends on the same day.

Return the maximum sum of values that you can receive by attending events.

Example 1:
Input: events = [[1,2,4],[3,4,3],[2,3,1]], k = 2
Output: 7
Explanation: Choose the green events, 0 and 1 (0-indexed) for a total value of 4 + 3 = 7.

Example 2:
Input: events = [[1,2,4],[3,4,3],[2,3,10]], k = 2
Output: 10
Explanation: Choose event 2 for a total value of 10.
Notice that you cannot attend any other event as they overlap, and that you do not have to attend k events.

Example 3:
Input: events = [[1,1,1],[2,2,2],[3,3,3],[4,4,4]], k = 3
Output: 9
Explanation: Although the events do not overlap, you can only attend 3 events. Pick the highest valued three.

Constraints:
1 <= k <= events.length
1 <= k * events.length <= 10^6
1 <= startDayi <= endDayi <= 10^9
1 <= valuei <= 10^6
```

<details><summary>Hint</summary>

```text
1. Sort the events by its startTime.
2. For every event, you can either choose it and consider the next event available, or you can ignore it.
   You can efficiently find the next event that is available using binary search.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareIntArray(const void* a1, const void* a2) {
    const int* p1 = *(const int**)a1;
    const int* p2 = *(const int**)a2;

    // ascending order by Array[][0]
    return ((p1[0] > p2[0]) ? (1) : (-1));
}
int dfs(int** events, int eventsSize, int k, int** dp, int index, int count, int previousEndDay) {
    int retVal = 0;

    if ((index == eventsSize) || (count == k)) {
        return retVal;
    }

    if (events[index][0] <= previousEndDay) {
        retVal = dfs(events, eventsSize, k, dp, index + 1, count, previousEndDay);
    } else if (dp[count][index] != -1) {
        retVal = dp[count][index];
    } else {
        int ans1 = dfs(events, eventsSize, k, dp, index + 1, count, previousEndDay);
        int ans2 = dfs(events, eventsSize, k, dp, index + 1, count + 1, events[index][1]) + events[index][2];
        retVal = fmax(ans1, ans2);
        dp[count][index] = retVal;
    }

    return retVal;
}
int maxValue(int** events, int eventsSize, int* eventsColSize, int k) {
    int retVal = 0;

    int i, j;

    qsort(events, eventsSize, sizeof(events[0]), compareIntArray);

    int** pDp = (int**)malloc((k + 1) * sizeof(int*));
    if (pDp == NULL) {
        perror("malloc");
        return retVal;
    }
    memset(pDp, 0, ((k + 1) * sizeof(int*)));
    for (i = 0; i < (k + 1); ++i) {
        pDp[i] = (int*)malloc(eventsSize * sizeof(int));
        if (pDp[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pDp[i]);
                pDp[j] = NULL;
            }
            free(pDp);
            pDp = NULL;
        }
        memset(pDp[i], -1, (eventsSize * sizeof(int)));
    }
    int index = 0;
    int count = 0;
    int previousEndDay = -1;
    retVal = dfs(events, eventsSize, k, pDp, index, count, previousEndDay);

    //
    for (i = 0; i < (k + 1); ++i) {
        free(pDp[i]);
        pDp[i] = NULL;
    }
    free(pDp);
    pDp = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int dfs(vector<vector<int>>& events, int eventsSize, int k, vector<vector<int>>& dp, int index, int count,
            int previousEndDay) {
        int retVal = 0;

        if ((index == eventsSize) || (count == k)) {
            return retVal;
        }

        if (events[index][0] <= previousEndDay) {
            retVal = dfs(events, eventsSize, k, dp, index + 1, count, previousEndDay);
        } else if (dp[count][index] != -1) {
            retVal = dp[count][index];
        } else {
            int ans1 = dfs(events, eventsSize, k, dp, index + 1, count, previousEndDay);
            int ans2 = dfs(events, eventsSize, k, dp, index + 1, count + 1, events[index][1]) + events[index][2];
            retVal = max(ans1, ans2);
            dp[count][index] = retVal;
        }

        return retVal;
    }
    int maxValue(vector<vector<int>>& events, int k) {
        int retVal = 0;

        sort(events.begin(), events.end());

        int eventsSize = events.size();
        vector<vector<int>> dp(k + 1, vector<int>(eventsSize, -1));
        int index = 0;
        int count = 0;
        int previousEndDay = -1;
        retVal = dfs(events, eventsSize, k, dp, index, count, previousEndDay);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def dfs(self, events: List[List[int]], eventsSize, k: int, dp, index, count, previousEndDay) -> int:
        retVal = 0

        if (index == eventsSize) or (count == k):
            return retVal

        if events[index][0] <= previousEndDay:
            retVal = self.dfs(events, eventsSize, k, dp, index + 1, count, previousEndDay)
        elif dp[count][index] != -1:
            retVal = dp[count][index]
        else:
            ans1 = self.dfs(events, eventsSize, k, dp, index + 1, count, previousEndDay)
            ans2 = self.dfs(events, eventsSize, k, dp, index + 1, count + 1, events[index][1]) + events[index][2]
            retVal = max(ans1, ans2)
            dp[count][index] = retVal

        return retVal

    def maxValue(self, events: List[List[int]], k: int) -> int:
        retVal = 0

        events.sort()

        eventsSize = len(events)
        dp = [[-1] * eventsSize for _ in range(k + 1)]
        index = 0
        count = 0
        previousEndDay = -1
        retVal = self.dfs(events, eventsSize, k, dp, index, count, previousEndDay)

        return retVal
```

</details>

## [1774. Closest Dessert Cost](https://leetcode.com/problems/closest-dessert-cost/)  1701

<details><summary>Description</summary>

```text
You would like to make dessert and are preparing to buy the ingredients.
You have n ice cream base flavors and m types of toppings to choose from.
You must follow these rules when making your dessert:
- There must be exactly one ice cream base.
- You can add one or more types of topping or have no toppings at all.
- There are at most two of each type of topping.

You are given three inputs:
- baseCosts, an integer array of length n, where each baseCosts[i] represents the price of the ith ice cream base flavor.
- toppingCosts, an integer array of length m, where each toppingCosts[i] is the price of one of the ith topping.
- target, an integer representing your target price for dessert.

You want to make a dessert with a total cost as close to target as possible.

Return the closest possible cost of the dessert to target. If there are multiple, return the lower one.

Example 1:
Input: baseCosts = [1,7], toppingCosts = [3,4], target = 10
Output: 10
Explanation: Consider the following combination (all 0-indexed):
- Choose base 1: cost 7
- Take 1 of topping 0: cost 1 x 3 = 3
- Take 0 of topping 1: cost 0 x 4 = 0
Total: 7 + 3 + 0 = 10.

Example 2:
Input: baseCosts = [2,3], toppingCosts = [4,5,100], target = 18
Output: 17
Explanation: Consider the following combination (all 0-indexed):
- Choose base 1: cost 3
- Take 1 of topping 0: cost 1 x 4 = 4
- Take 2 of topping 1: cost 2 x 5 = 10
- Take 0 of topping 2: cost 0 x 100 = 0
Total: 3 + 4 + 10 + 0 = 17. You cannot make a dessert with a total cost of 18.

Example 3:
Input: baseCosts = [3,10], toppingCosts = [2,5], target = 9
Output: 8
Explanation: It is possible to make desserts with cost 8 and 10. Return 8 as it is the lower cost.


Constraints:
n == baseCosts.length
m == toppingCosts.length
1 <= n, m <= 10
1 <= baseCosts[i], toppingCosts[i] <= 10^4
1 <= target <= 10^4
```

</details>

<details><summary>C</summary>

```c
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
int closestCost(int* baseCosts, int baseCostsSize, int* toppingCosts, int toppingCostsSize, int target) {
    int retVal = INT_MAX;

    int i, j;

    for (i = 0; i < baseCostsSize; ++i) {
        retVal = MIN(retVal, baseCosts[i]);
    }
    if (retVal >= target) {
        return retVal;
    }

    bool dp[target + 1];
    memset(dp, false, sizeof(dp));

    retVal = 2 * target - retVal;
    for (i = 0; i < baseCostsSize; ++i) {
        if (baseCosts[i] <= target) {
            dp[baseCosts[i]] = true;
        } else {
            retVal = MIN(retVal, baseCosts[i]);
        }
    }

    int toppingCount;
    for (j = 0; j < toppingCostsSize; ++j) {
        for (toppingCount = 0; toppingCount < 2; ++toppingCount) {
            for (i = target; i > 0; --i) {
                if (dp[i] && (i + toppingCosts[j] > target)) {
                    retVal = MIN(retVal, (i + toppingCosts[j]));
                }

                if (i - toppingCosts[j] > 0) {
                    dp[i] = dp[i] | (dp[i - toppingCosts[j]]);
                }
            }
        }
    }

    for (i = 0; i <= (retVal - target); ++i) {
        if (dp[target - i]) {
            retVal = target - i;
            return retVal;
        }
    }

    return retVal;
}
```

</details>

## [1799. Maximize Score After N Operations](https://leetcode.com/problems/maximize-score-after-n-operations/)  2072

- [Official](https://leetcode.com/problems/maximize-score-after-n-operations/editorial/)
- [Official](https://leetcode.cn/problems/maximize-score-after-n-operations/solutions/2028201/n-ci-cao-zuo-hou-de-zui-da-fen-shu-he-by-i9k5/)

<details><summary>Description</summary>

```text
You are given nums, an array of positive integers of size 2 * n. You must perform n operations on this array.

In the ith operation (1-indexed), you will:
- Choose two elements, x and y.
- Receive a score of i * gcd(x, y).
- Remove x and y from nums.

Return the maximum score you can receive after performing n operations.

The function gcd(x, y) is the greatest common divisor of x and y.

Example 1:
Input: nums = [1,2]
Output: 1
Explanation: The optimal choice of operations is:
(1 * gcd(1, 2)) = 1

Example 2:
Input: nums = [3,4,6,8]
Output: 11
Explanation: The optimal choice of operations is:
(1 * gcd(3, 6)) + (2 * gcd(4, 8)) = 3 + 8 = 11

Example 3:
Input: nums = [1,2,3,4,5,6]
Output: 14
Explanation: The optimal choice of operations is:
(1 * gcd(1, 5)) + (2 * gcd(2, 4)) + (3 * gcd(3, 6)) = 1 + 4 + 9 = 14

Constraints:
1 <= n <= 7
nums.length == 2 * n
1 <= nums[i] <= 10^6
```

<details><summary>Hint</summary>

```text
1. Find every way to split the array until n groups of 2. Brute force recursion is acceptable.
2. Calculate the gcd of every pair and greedily multiply the largest gcds.
```

</details>

</details>

<details><summary>C</summary>

```c
int gcd(int num1, int num2) {
    while (num2 != 0) {
        int temp = num1;
        num1 = num2;
        num2 = temp % num2;
    }
    return num1;
}
int maxScore(int *nums, int numsSize) {
    int retVal = 0;

    int maxStates = 1 << numsSize;
    int finalMask = maxStates - 1;
    int dp[maxStates];
    memset(dp, 0, sizeof(dp));

    int currentScore, stateAfterPickingCurrPair, remainingScore;
    int firstIndex;
    int numbersTaken, pairsFormed;
    int state;
    for (state = finalMask; state >= 0; state -= 1) {
        if (state == finalMask) {
            dp[state] = 0;
            continue;
        }

        numbersTaken = __builtin_popcount(state);
        pairsFormed = numbersTaken / 2;
        if (numbersTaken % 2) {
            continue;
        }

        for (firstIndex = 0; firstIndex < numsSize; firstIndex += 1) {
            for (int secondIndex = firstIndex + 1; secondIndex < numsSize; secondIndex += 1) {
                if (((state >> firstIndex) & 1) == 1 || ((state >> secondIndex) & 1) == 1) {
                    continue;
                }

                currentScore = (pairsFormed + 1) * gcd(nums[firstIndex], nums[secondIndex]);
                stateAfterPickingCurrPair = state | (1 << firstIndex) | (1 << secondIndex);
                remainingScore = dp[stateAfterPickingCurrPair];
                dp[state] = fmax(dp[state], currentScore + remainingScore);
            }
        }
    }
    retVal = dp[0];

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxScore(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        int maxStates = 1 << numsSize;
        int finalMask = maxStates - 1;
        vector<int> dp(maxStates, 0);
        for (int state = finalMask; state >= 0; state -= 1) {
            if (state == finalMask) {
                dp[state] = 0;
                continue;
            }

            int numbersTaken = __builtin_popcount(state);
            int pairsFormed = numbersTaken / 2;
            if (numbersTaken % 2) {
                continue;
            }

            for (int firstIndex = 0; firstIndex < numsSize; firstIndex += 1) {
                for (int secondIndex = firstIndex + 1; secondIndex < numsSize; secondIndex += 1) {
                    if (((state >> firstIndex) & 1) == 1 || ((state >> secondIndex) & 1) == 1) {
                        continue;
                    }

                    int currentScore = (pairsFormed + 1) * __gcd(nums[firstIndex], nums[secondIndex]);
                    int stateAfterPickingCurrPair = state | (1 << firstIndex) | (1 << secondIndex);
                    int remainingScore = dp[stateAfterPickingCurrPair];
                    dp[state] = max(dp[state], currentScore + remainingScore);
                }
            }
        }
        retVal = dp[0];

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxScore(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)
        maxStates = 1 << numsSize
        finalMask = maxStates - 1
        dp = [0] * maxStates
        for state in range(finalMask, -1, -1):
            if state == finalMask:
                dp[state] = 0
                continue

            numbersTaken = bin(state).count('1')
            pairsFormed = numbersTaken // 2
            if numbersTaken % 2:
                continue

            for firstIndex in range(len(nums)):
                for secondIndex in range(firstIndex + 1, len(nums)):
                    if (state >> firstIndex & 1) == 1 or (state >> secondIndex & 1) == 1:
                        continue

                    currentScore = (pairsFormed + 1) * gcd(nums[firstIndex], nums[secondIndex])
                    stateAfterPickingCurrPair = state | (1 << firstIndex) | (1 << secondIndex)
                    remainingScore = dp[stateAfterPickingCurrPair]
                    dp[state] = max(dp[state], currentScore + remainingScore)
        retVal = dp[0]

        return retVal
```

</details>

## [1931. Painting a Grid With Three Different Colors](https://leetcode.com/problems/painting-a-grid-with-three-different-colors/)  2170

- [Official](https://leetcode.com/problems/painting-a-grid-with-three-different-colors/editorial/)
- [Official](https://leetcode.cn/problems/painting-a-grid-with-three-different-colors/solutions/870045/yong-san-chong-bu-tong-yan-se-wei-wang-g-7nb2/)

<details><summary>Description</summary>

```text
You are given two integers m and n. Consider an m x n grid where each cell is initially white.
You can paint each cell red, green, or blue. All cells must be painted.

Return the number of ways to color the grid with no two adjacent cells having the same color.
Since the answer can be very large, return it modulo 10^9 + 7.

Example 1:
Input: m = 1, n = 1
Output: 3
Explanation: The three possible colorings are shown in the image above.

Example 2:
Input: m = 1, n = 2
Output: 6
Explanation: The six possible colorings are shown in the image above.

Example 3:
Input: m = 5, n = 5
Output: 580986

Constraints:
1 <= m <= 5
1 <= n <= 1000
```

<details><summary>Hint</summary>

```text
1. Represent each colored column by a bitmask based on each cell color.
2. Use bitmasks DP with state (currentCell, prevColumn).
```

</details>

</details>

<details><summary>C</summary>

```c
#ifndef LISTNODE_H
#define LISTNODE_H

struct ListNode *createList(int val) {
    struct ListNode *pObj = NULL;

    pObj = (struct ListNode *)malloc(sizeof(struct ListNode));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->val = val;
    pObj->next = NULL;

    return pObj;
}
void freeList(struct ListNode *pObj) {
    if (pObj == NULL) {
        return;
    }

    struct ListNode *pFree;
    while (pObj) {
        pFree = pObj;
        pObj = pObj->next;
        free(pFree);
        pFree = NULL;
    }
}

#endif  // LISTNODE_H
#ifndef HASH_H
#define HASH_H

struct hashTable {
    int key;
    struct ListNode *val;
    UT_hash_handle hh;
};
void hashAddItem(struct hashTable **obj, int key, int val) {
    struct ListNode *p = createList(val);

    struct hashTable *pEntry = NULL;
    HASH_FIND_INT(*obj, &key, pEntry);
    if (pEntry == NULL) {
        pEntry = (struct hashTable *)malloc(sizeof(struct hashTable));
        if (pEntry == NULL) {
            perror("malloc");
            return;
        }
        pEntry->key = key;
        pEntry->val = p;
        HASH_ADD_INT(*obj, key, pEntry);
    } else {
        p->next = pEntry->val;
        pEntry->val = p;
    }
}
struct ListNode *hashGetItem(struct hashTable **obj, int key) {
    struct ListNode *pRetVal = NULL;

    struct hashTable *pEntry = NULL;
    HASH_FIND_INT(*obj, &key, pEntry);
    if (pEntry == NULL) {
        return pRetVal;
    }
    pRetVal = pEntry->val;

    return pRetVal;
}
void hashFree(struct hashTable **pObj) {
    struct hashTable *pCurrent = NULL;
    struct hashTable *pTmp = NULL;
    HASH_ITER(hh, *pObj, pCurrent, pTmp) {
        HASH_DEL(*pObj, pCurrent);
        freeList(pCurrent->val);
        pCurrent->val = NULL;
        free(pCurrent);
        pCurrent = NULL;
    }
}

#endif  // HASH_H
#define MODULO (int)(1e9 + 7)
int colorTheGrid(int m, int n) {
    int retVal = 0;

    // Hash mapping stores all valid coloration schemes for a single row that meet the requirements
    // The key represents mask, and the value represents the ternary string of mask (stored as a list)
    struct hashTable *valid = NULL;
    // Enumerate masks that meet the requirements within the range [0, 3^m)
    int mask_end = pow(3, m);
    for (int mask = 0; mask < mask_end; ++mask) {
        int mm = mask;
        int color[m];
        for (int i = 0; i < m; ++i) {
            color[i] = mm % 3;
            mm /= 3;
        }

        bool check = true;
        for (int i = 0; i < m - 1; ++i) {
            if (color[i] == color[i + 1]) {
                check = false;
                break;
            }
        }
        if (check == true) {
            for (int i = 0; i < m; i++) {
                hashAddItem(&valid, mask, color[i]);
            }
        }
    }

    // Preprocess all (mask1, mask2) binary tuples, satisfying mask1 and mask2 When adjacent rows,
    // the colors of the two cells in the same column are different
    struct hashTable *adjacent = NULL;
    for (struct hashTable *pEntry1 = valid; pEntry1; pEntry1 = pEntry1->hh.next) {
        int mask1 = pEntry1->key;
        for (struct hashTable *pEntry2 = valid; pEntry2; pEntry2 = pEntry2->hh.next) {
            int mask2 = pEntry2->key;

            bool check = true;
            for (struct ListNode *p1 = pEntry1->val, *p2 = pEntry2->val; p1 && p2; p1 = p1->next, p2 = p2->next) {
                if (p1->val == p2->val) {
                    check = false;
                    break;
                }
            }
            if (check == true) {
                hashAddItem(&adjacent, mask1, mask2);
            }
        }
    }

    int f[mask_end];
    memset(f, 0, sizeof(f));
    for (struct hashTable *pEntry = valid; pEntry; pEntry = pEntry->hh.next) {
        int mask = pEntry->key;
        f[mask] = 1;
    }
    for (int i = 1; i < n; ++i) {
        int g[mask_end];
        memset(g, 0, sizeof(g));
        for (struct hashTable *pEntry1 = valid; pEntry1; pEntry1 = pEntry1->hh.next) {
            int mask2 = pEntry1->key;
            for (struct ListNode *p = hashGetItem(&adjacent, mask2); p != NULL; p = p->next) {
                int mask1 = p->val;
                g[mask2] += f[mask1];
                if (g[mask2] >= MODULO) {
                    g[mask2] -= MODULO;
                }
            }
        }
        memcpy(f, g, sizeof(f));
    }

    hashFree(&valid);
    hashFree(&adjacent);

    for (int i = 0; i < mask_end; i++) {
        retVal += f[i];
        if (retVal >= MODULO) {
            retVal -= MODULO;
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
    const int MODULO = 1e9 + 7;

   public:
    int colorTheGrid(int m, int n) {
        int retVal = 0;

        // Hash mapping stores all valid coloration schemes for a single row that meet the requirements
        // The key represents mask, and the value represents the ternary string of mask (stored as a list)
        unordered_map<int, vector<int>> valid;
        // Enumerate masks that meet the requirements within the range [0, 3^m)
        int mask_end = pow(3, m);
        for (int mask = 0; mask < mask_end; ++mask) {
            vector<int> color;
            int mm = mask;
            for (int i = 0; i < m; ++i) {
                color.push_back(mm % 3);
                mm /= 3;
            }

            bool check = true;
            for (int i = 0; i < m - 1; ++i) {
                if (color[i] == color[i + 1]) {
                    check = false;
                    break;
                }
            }
            if (check == true) {
                valid[mask] = move(color);
            }
        }

        // Preprocess all (mask1, mask2) binary tuples, satisfying mask1 and mask2 When adjacent rows,
        // the colors of the two cells in the same column are different
        unordered_map<int, vector<int>> adjacent;
        for (const auto& [mask1, color1] : valid) {
            for (const auto& [mask2, color2] : valid) {
                bool check = true;
                for (int i = 0; i < m; ++i) {
                    if (color1[i] == color2[i]) {
                        check = false;
                        break;
                    }
                }
                if (check == true) {
                    adjacent[mask1].push_back(mask2);
                }
            }
        }

        vector<int> f(mask_end);
        for (const auto& [mask, _] : valid) {
            f[mask] = 1;
        }
        for (int i = 1; i < n; ++i) {
            vector<int> g(mask_end);
            for (const auto& [mask2, _] : valid) {
                for (int mask1 : adjacent[mask2]) {
                    g[mask2] += f[mask1];
                    if (g[mask2] >= MODULO) {
                        g[mask2] -= MODULO;
                    }
                }
            }
            f = move(g);
        }

        for (int num : f) {
            retVal += num;
            if (retVal >= MODULO) {
                retVal -= MODULO;
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
    def __init__(self) -> None:
        self.MODULO = 10 ** 9 + 7

    def colorTheGrid(self, m: int, n: int) -> int:
        retVal = 0

        # Hash mapping stores all valid coloration schemes for a single row that meet the requirements
        # The key represents mask, and the value represents the ternary string of mask (stored as a list)
        valid = dict()
        # Enumerate masks that meet the requirements within the range [0, 3^m)
        for mask in range(3**m):
            color = list()
            mm = mask
            for _ in range(m):
                color.append(mm % 3)
                mm //= 3

            if any(color[i] == color[i + 1] for i in range(m - 1)):
                continue

            valid[mask] = color

        # Preprocess all (mask1, mask2) binary tuples, satisfying mask1 and mask2 When adjacent rows,
        # the colors of the two cells in the same column are different
        adjacent = defaultdict(list)
        for mask1, color1 in valid.items():
            for mask2, color2 in valid.items():
                if not any(x == y for x, y in zip(color1, color2)):
                    adjacent[mask1].append(mask2)

        f = [int(mask in valid) for mask in range(3**m)]
        for i in range(1, n):
            g = [0] * (3**m)
            for mask2 in valid.keys():
                for mask1 in adjacent[mask2]:
                    g[mask2] += f[mask1]
                    if g[mask2] >= self.MODULO:
                        g[mask2] -= self.MODULO
            f = g

        retVal = sum(f) % self.MODULO

        return retVal
```

</details>

## [1937. Maximum Number of Points with Cost](https://leetcode.com/problems/maximum-number-of-points-with-cost/)  2105

- [Official](https://leetcode.com/problems/maximum-number-of-points-with-cost/editorial/)
- [Official](https://leetcode.cn/problems/maximum-number-of-points-with-cost/solutions/883393/kou-fen-hou-de-zui-da-de-fen-by-leetcode-60zl/)

<details><summary>Description</summary>

```text
You are given an m x n integer matrix points (0-indexed).
Starting with 0 points, you want to maximize the number of points you can get from the matrix.

To gain points, you must pick one cell in each row.
Picking the cell at coordinates (r, c) will add points[r][c] to your score.

However, you will lose points if you pick a cell too far from the cell that you picked in the previous row.
For every two adjacent rows r and r + 1 (where 0 <= r < m - 1),
picking cells at coordinates (r, c1) and (r + 1, c2) will subtract abs(c1 - c2) from your score.

Return the maximum number of points you can achieve.
abs(x) is defined as:
- x for x >= 0.
- -x for x < 0.

Example 1:
Input: points = [[1,2,3],[1,5,1],[3,1,1]]
Output: 9
Explanation:
The blue cells denote the optimal cells to pick, which have coordinates (0, 2), (1, 1), and (2, 0).
You add 3 + 5 + 3 = 11 to your score.
However, you must subtract abs(2 - 1) + abs(1 - 0) = 2 from your score.
Your final score is 11 - 2 = 9.

Example 2:
Input: points = [[1,5],[2,3],[4,2]]
Output: 11
Explanation:
The blue cells denote the optimal cells to pick, which have coordinates (0, 1), (1, 1), and (2, 0).
You add 5 + 3 + 4 = 12 to your score.
However, you must subtract abs(1 - 1) + abs(1 - 0) = 1 from your score.
Your final score is 12 - 1 = 11.

Constraints:
m == points.length
n == points[r].length
1 <= m, n <= 10^5
1 <= m * n <= 10^5
0 <= points[r][c] <= 10^5
```

<details><summary>Hint</summary>

```text
1. Try using dynamic programming.
2. dp[i][j] is the maximum number of points you can have if points[i][j] is the most recent cell you picked.
```

</details>

</details>

<details><summary>C</summary>

```c
long long maxPoints(int** points, int pointsSize, int* pointsColSize) {
    long long retVal = 0;

    int i, j, k;

    int row = pointsSize;
    int col = pointsColSize[0];
    long long dp[row][col];
    memset(dp, 0, sizeof(dp));
    for (i = 0; i < col; ++i) {
        dp[0][i] = points[0][i];
    }

    // https://leetcode.com/problems/maximum-number-of-points-with-cost/solutions/1344888/c-dp-from-o-m-n-n-to-o-m-n/
    //  dp[i][j] = max(dp[i - 1][k] + point[i][j] - abs(j - k)) for each 0 <= k < points[i - 1].size()
    //  => dp[i][j] = max(dp[i - 1][k] + k) + points[i][j] - j for all 0 <= k <= j
    //  => dp[i][j] = max(dp[i - 1][k] - k) + points[i][j] + j for all j <= k <= points[i].size() - 1
    long long dpLeft[col];
    long long dpRight[col];
    for (i = 1; i < row; ++i) {
        memset(dpLeft, 0, sizeof(dpLeft));
        dpLeft[0] = dp[i - 1][0];
        for (int k = 1; k < col; ++k) {
            dpLeft[k] = fmax(dpLeft[k - 1], dp[i - 1][k] + k);
        }

        memset(dpRight, 0, sizeof(dpRight));
        dpRight[col - 1] = dp[i - 1][col - 1] - col + 1;
        for (k = col - 2; k >= 0; --k) {
            dpRight[k] = fmax(dpRight[k + 1], dp[i - 1][k] - k);
        }

        for (j = 0; j < col; ++j) {
            dp[i][j] = fmax(dpLeft[j] - j, dpRight[j] + j) + points[i][j];
        }
    }
    for (j = 0; j < col; ++j) {
        retVal = fmax(retVal, dp[row - 1][j]);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long maxPoints(vector<vector<int>>& points) {
        long long retVal = 0;

        int row = points.size();
        int col = points[0].size();
        vector<vector<long long>> dp(row, vector<long long>(col, 0));
        for (int i = 0; i < col; ++i) {
            dp[0][i] = points[0][i];
        }

        // https://leetcode.com/problems/maximum-number-of-points-with-cost/solutions/1344888/c-dp-from-o-m-n-n-to-o-m-n/
        //  dp[i][j] = max(dp[i - 1][k] + point[i][j] - abs(j - k)) for each 0 <= k < points[i - 1].size()
        //  => dp[i][j] = max(dp[i - 1][k] + k) + points[i][j] - j for all 0 <= k <= j
        //  => dp[i][j] = max(dp[i - 1][k] - k) + points[i][j] + j for all j <= k <= points[i].size() - 1
        for (int i = 1; i < row; ++i) {
            vector<long long> dpLeft(col, 0);
            dpLeft[0] = dp[i - 1][0];
            for (int k = 1; k < col; ++k) {
                dpLeft[k] = max(dpLeft[k - 1], dp[i - 1][k] + k);
            }

            vector<long long> dpRight(col, 0);
            dpRight[col - 1] = dp[i - 1][col - 1] - col + 1;
            for (int k = col - 2; k >= 0; --k) {
                dpRight[k] = max(dpRight[k + 1], dp[i - 1][k] - k);
            }

            for (int j = 0; j < col; ++j) {
                dp[i][j] = max(dpLeft[j] - j, dpRight[j] + j) + points[i][j];
            }
        }
        retVal = *max_element(dp[row - 1].begin(), dp[row - 1].end());

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxPoints(self, points: List[List[int]]) -> int:
        retVal = 0

        row = len(points)
        col = len(points[0])    # 1 <= m, n <= 10^5
        dp = [[0 for j in range(col)] for _ in range(row)]
        dp[0] = points[0]

        # https://leetcode.com/problems/maximum-number-of-points-with-cost/solutions/1344888/c-dp-from-o-m-n-n-to-o-m-n/
        #   dp[i][j] = max(dp[i - 1][k] + point[i][j] - abs(j - k)) for each 0 <= k < points[i - 1].size()
        #   => dp[i][j] = max(dp[i - 1][k] + k) + points[i][j] - j for all 0 <= k <= j
        #   => dp[i][j] = max(dp[i - 1][k] - k) + points[i][j] + j for all j <= k <= points[i].size() - 1
        for i in range(1, row):
            dpLeft = [0 for j in range(col)]
            dpLeft[0] = dp[i - 1][0]
            for k in range(1, col):
                dpLeft[k] = max(dpLeft[k-1], dp[i-1][k]+k)

            dpRight = [0 for j in range(col)]
            dpRight[col-1] = dp[i - 1][col-1] - col + 1
            for k in range(col-2, -1, -1):
                dpRight[k] = max(dpRight[k+1], dp[i-1][k]-k)

            for j in range(col):
                dp[i][j] = max(dpLeft[j] - j, dpRight[j] + j) + points[i][j]

        retVal = max(dp[row-1])

        return retVal
```

</details>
