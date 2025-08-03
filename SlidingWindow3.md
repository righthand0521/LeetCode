# Sliding Window

## [2090. K Radius Subarray Averages](https://leetcode.com/problems/k-radius-subarray-averages/)  1358

- [Official](https://leetcode.com/problems/k-radius-subarray-averages/editorial/)
- [Official](https://leetcode.cn/problems/k-radius-subarray-averages/solutions/1127983/ban-jing-wei-k-de-zi-shu-zu-ping-jun-zhi-jqo8/)

<details><summary>Description</summary>

```text
You are given a 0-indexed array nums of n integers, and an integer k.

The k-radius average for a subarray of nums centered at some index i
with the radius k is the average of all elements in nums between the indices i - k and i + k (inclusive).
If there are less than k elements before or after the index i, then the k-radius average is -1.

Build and return an array avgs of length n where avgs[i] is the k-radius average for the subarray centered at index i.

The average of x elements is the sum of the x elements divided by x, using integer division.
The integer division truncates toward zero, which means losing its fractional part.

For example, the average of four elements 2, 3, 1, and 5 is (2 + 3 + 1 + 5) / 4 = 11 / 4 = 2.75, which truncates to 2.

Example 1:
Input: nums = [7,4,3,9,1,8,5,2,6], k = 3
Output: [-1,-1,-1,5,4,4,-1,-1,-1]
Explanation:
- avg[0], avg[1], and avg[2] are -1 because there are less than k elements before each index.
- The sum of the subarray centered at index 3 with radius 3 is: 7 + 4 + 3 + 9 + 1 + 8 + 5 = 37.
  Using integer division, avg[3] = 37 / 7 = 5.
- For the subarray centered at index 4, avg[4] = (4 + 3 + 9 + 1 + 8 + 5 + 2) / 7 = 4.
- For the subarray centered at index 5, avg[5] = (3 + 9 + 1 + 8 + 5 + 2 + 6) / 7 = 4.
- avg[6], avg[7], and avg[8] are -1 because there are less than k elements after each index.

Example 2:
Input: nums = [100000], k = 0
Output: [100000]
Explanation:
- The sum of the subarray centered at index 0 with radius 0 is: 100000.
  avg[0] = 100000 / 1 = 100000.

Example 3:
Input: nums = [8], k = 100000
Output: [-1]
Explanation:
- avg[0] is -1 because there are less than k elements before and after index 0.

Constraints:
n == nums.length
1 <= n <= 10^5
0 <= nums[i], k <= 10^5
```

<details><summary>Hint</summary>

```text
1. To calculate the average of a subarray, you need the sum and the K. K is already given.
   How could you quickly calculate the sum of a subarray?
2. Use the Prefix Sums method to calculate the subarray sums.
3. It is possible that the sum of all the elements does not fit in a 32-bit integer type.
   Be sure to use a 64-bit integer type for the prefix sum array.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getAverages(int* nums, int numsSize, int k, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = numsSize;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, -1, ((*returnSize) * sizeof(int)));

    int i;

    // n == nums.length, 1 <= n <= 10^5, 0 <= nums[i], k <= 10^5
    long long prefixSum[numsSize + 1];
    memset(prefixSum, 0, sizeof(prefixSum));
    for (i = 0; i < numsSize; ++i) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    for (i = k; i < numsSize - k; ++i) {
        pRetVal[i] = (prefixSum[i + k + 1] - prefixSum[i - k]) / (2 * k + 1);
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> getAverages(vector<int>& nums, int k) {
        vector<int> retVal;

        int numsSize = nums.size();

        // n == nums.length, 1 <= n <= 10^5, 0 <= nums[i], k <= 10^5
        vector<long long> prefixSum(numsSize + 1, 0);
        for (int i = 0; i < numsSize; ++i) {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
        }

        retVal.resize(numsSize, -1);
        for (int i = k; i < numsSize - k; ++i) {
            retVal[i] = (prefixSum[i + k + 1] - prefixSum[i - k]) / (2 * k + 1);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def getAverages(self, nums: List[int], k: int) -> List[int]:
        retVal = []

        numsSize = len(nums)

        prefixSum = [0]
        for i in range(numsSize):
            prefixSum.append(prefixSum[i] + nums[i])

        retVal = [-1] * numsSize
        for i in range(k, numsSize - k):
            retVal[i] = (prefixSum[i + k + 1] - prefixSum[i - k]) // (2 * k + 1)

        return retVal
```

</details>

## [2024. Maximize the Confusion of an Exam](https://leetcode.com/problems/maximize-the-confusion-of-an-exam/)  1643

- [Official](https://leetcode.com/problems/maximize-the-confusion-of-an-exam/editorial/)
- [Official](https://leetcode.cn/problems/maximize-the-confusion-of-an-exam/solutions/1368825/kao-shi-de-zui-da-kun-rao-du-by-leetcode-qub5/)

<details><summary>Description</summary>

```text
A teacher is writing a test with n true/false questions, with 'T' denoting true and 'F' denoting false.
He wants to confuse the students by maximizing the number of consecutive questions with the same answer
(multiple trues or multiple falses in a row).

You are given a string answerKey, where answerKey[i] is the original answer to the ith question.
In addition, you are given an integer k, the maximum number of times you may perform the following operation:
- Change the answer key for any question to 'T' or 'F' (i.e., set answerKey[i] to 'T' or 'F').

Return the maximum number of consecutive 'T's or 'F's in the answer key after performing the operation at most k times.

Example 1:
Input: answerKey = "TTFF", k = 2
Output: 4
Explanation: We can replace both the 'F's with 'T's to make answerKey = "TTTT".
There are four consecutive 'T's.

Example 2:
Input: answerKey = "TFFT", k = 1
Output: 3
Explanation: We can replace the first 'T' with an 'F' to make answerKey = "FFFT".
Alternatively, we can replace the second 'T' with an 'F' to make answerKey = "TFFF".
In both cases, there are three consecutive 'F's.

Example 3:
Input: answerKey = "TTFTTFTT", k = 1
Output: 5
Explanation: We can replace the first 'F' to make answerKey = "TTTTTFTT"
Alternatively, we can replace the second 'F' to make answerKey = "TTFTTTTT".
In both cases, there are five consecutive 'T's.

Constraints:
n == answerKey.length
1 <= n <= 5 * 10^4
answerKey[i] is either 'T' or 'F'
1 <= k <= n
```

<details><summary>Hint</summary>

```text
1. Can we use the maximum length at the previous position to help us find the answer for the current position?
2. Can we use binary search to find the maximum consecutive same answer at every position?
```

</details>

</details>

<details><summary>C</summary>

```c
int maxConsecutiveAnswers(char* answerKey, int k) {
    int retVal = 0;

    // answerKey[i] is either 'T' or 'F'
#define MAX_RECORD (26)
    int Record[MAX_RECORD];
    memset(Record, 0, sizeof(Record));

    int maxRecord = 0;
    int answerKeySize = strlen(answerKey);
    int left = 0;
    int right = 0;
    while (right < answerKeySize) {
        Record[answerKey[right] - 'A']++;

        maxRecord = fmax(maxRecord, Record[answerKey[right] - 'A']);
        if (right - left + 1 - maxRecord > k) {
            Record[answerKey[left] - 'A']--;
            left++;
        }

        right++;
    }
    retVal = right - left;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxConsecutiveAnswers(string answerKey, int k) {
        int retVal = 0;

        // answerKey[i] is either 'T' or 'F'
#define MAX_RECORD (26)
        vector<int> Record(MAX_RECORD, 0);

        int maxRecord = 0;
        int answerKeySize = answerKey.length();
        int left = 0;
        int right = 0;
        while (right < answerKeySize) {
            Record[answerKey[right] - 'A']++;

            maxRecord = max(maxRecord, Record[answerKey[right] - 'A']);
            if (right - left + 1 - maxRecord > k) {
                Record[answerKey[left] - 'A']--;
                left++;
            }

            right++;
        }
        retVal = right - left;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxConsecutiveAnswers(self, answerKey: str, k: int) -> int:
        retVal = 0

        # answerKey[i] is either 'T' or 'F'
        MAX_RECORD = 26
        Record = [0] * MAX_RECORD

        maxRecord = 0
        answerKeysSize = len(answerKey)
        left = 0
        right = 0
        while right < answerKeysSize:
            idx = ord(answerKey[right]) - ord("A")
            Record[idx] += 1

            maxRecord = max(maxRecord, Record[idx])
            if right - left + 1 - maxRecord > k:
                Record[ord(answerKey[left]) - ord("A")] -= 1
                left += 1

            right += 1

        retVal = right - left

        return retVal
```

</details>

## [2106. Maximum Fruits Harvested After at Most K Steps](https://leetcode.com/problems/maximum-fruits-harvested-after-at-most-k-steps/)  2062

- [Official](https://leetcode.com/problems/maximum-fruits-harvested-after-at-most-k-steps/editorial/)
- [Official](https://leetcode.cn/problems/maximum-fruits-harvested-after-at-most-k-steps/solutions/2254268/zhai-shui-guo-by-leetcode-solution-4j9v/)

<details><summary>Description</summary>

```text
Fruits are available at some positions on an infinite x-axis.
You are given a 2D integer array fruits where fruits[i] = [positioni, amounti]
depicts amounti fruits at the position positioni.
fruits is already sorted by positioni in ascending order, and each positioni is unique.

You are also given an integer startPos and an integer k.
Initially, you are at the position startPos.
From any position, you can either walk to the left or right.
It takes one step to move one unit on the x-axis, and you can walk at most k steps in total.
For every position you reach,
you harvest all the fruits at that position, and the fruits will disappear from that position.

Return the maximum total number of fruits you can harvest.

Example 1:
Input: fruits = [[2,8],[6,3],[8,6]], startPos = 5, k = 4
Output: 9
Explanation:
The optimal way is to:
- Move right to position 6 and harvest 3 fruits
- Move right to position 8 and harvest 6 fruits
You moved 3 steps and harvested 3 + 6 = 9 fruits in total.

Example 2:
Input: fruits = [[0,9],[4,1],[5,7],[6,2],[7,4],[10,9]], startPos = 5, k = 4
Output: 14
Explanation:
You can move at most k = 4 steps, so you cannot reach position 0 nor 10.
The optimal way is to:
- Harvest the 7 fruits at the starting position 5
- Move left to position 4 and harvest 1 fruit
- Move right to position 6 and harvest 2 fruits
- Move right to position 7 and harvest 4 fruits
You moved 1 + 3 = 4 steps and harvested 7 + 1 + 2 + 4 = 14 fruits in total.

Example 3:
Input: fruits = [[0,3],[6,4],[8,5]], startPos = 3, k = 2
Output: 0
Explanation:
You can move at most k = 2 steps and cannot reach any position with fruits.

Constraints:
1 <= fruits.length <= 10^5
fruits[i].length == 2
0 <= startPos, positioni <= 2 * 10^5
positioni-1 < positioni for any i > 0 (0-indexed)
1 <= amounti <= 10^4
0 <= k <= 2 * 10^5
```

<details><summary>Hint</summary>

```text
1. Does an optimal path have very few patterns? For example, could a path that goes left, turns and goes right,
   then turns again and goes left be any better than a path that simply goes left, turns, and goes right?
2. The optimal path turns at most once. That is, the optimal path is one of these:
   to go left only; to go right only; to go left, turn and go right; or to go right, turn and go left.
3. Moving x steps left then k-x steps right gives you a range of positions that you can reach.
4. Use prefix sums to get the sum of all fruits for each possible range.
5. Use a similar strategy for all the paths that go right, then turn and go left.
```

</details>

</details>

<details><summary>C</summary>

```c
int step(int** fruits, int fruitsSize, int* fruitsColSize, int startPos, int left, int right) {
    int retVal = 0;

    if (fruits[right][0] <= startPos) {
        retVal = startPos - fruits[left][0];
    } else if (fruits[left][0] >= startPos) {
        retVal = fruits[right][0] - startPos;
    } else {
        retVal = fmin(abs(startPos - fruits[right][0]), abs(startPos - fruits[left][0]));
        retVal += fruits[right][0];
        retVal -= fruits[left][0];
    }

    return retVal;
}
int maxTotalFruits(int** fruits, int fruitsSize, int* fruitsColSize, int startPos, int k) {
    int retVal = 0;

    int sum = 0;
    int left = 0;
    int right = 0;
    while (right < fruitsSize) {
        sum += fruits[right][1];

        while ((left <= right) && (step(fruits, fruitsSize, fruitsColSize, startPos, left, right) > k)) {
            sum -= fruits[left][1];
            left++;
        }
        retVal = fmax(retVal, sum);

        right++;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    int step(vector<vector<int>>& fruits, int startPos, int left, int right) {
        int retVal = 0;

        if (fruits[right][0] <= startPos) {
            retVal = startPos - fruits[left][0];
        } else if (fruits[left][0] >= startPos) {
            retVal = fruits[right][0] - startPos;
        } else {
            retVal = min(abs(startPos - fruits[right][0]), abs(startPos - fruits[left][0]));
            retVal += fruits[right][0];
            retVal -= fruits[left][0];
        }

        return retVal;
    }

   public:
    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
        int retVal = 0;

        int fruitsSize = fruits.size();

        int sum = 0;
        int left = 0;
        int right = 0;
        while (right < fruitsSize) {
            sum += fruits[right][1];

            while ((left <= right) && (step(fruits, startPos, left, right) > k)) {
                sum -= fruits[left][1];
                left++;
            }
            retVal = max(retVal, sum);

            right++;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def step(self, fruits: List[List[int]], startPos: int, left: int, right: int) -> int:
        retVal = 0

        if fruits[right][0] <= startPos:
            retVal = startPos - fruits[left][0]
        elif fruits[left][0] >= startPos:
            retVal = fruits[right][0] - startPos
        else:
            retVal = min(abs(startPos - fruits[right][0]), abs(startPos - fruits[left][0]))
            retVal += fruits[right][0]
            retVal -= fruits[left][0]

        return retVal

    def maxTotalFruits(self, fruits: List[List[int]], startPos: int, k: int) -> int:
        retVal = 0

        fruitsSize = len(fruits)

        sum = 0
        left = 0
        right = 0
        while right < fruitsSize:
            sum += fruits[right][1]

            while (left <= right) and (self.step(fruits, startPos, left, right) > k):
                sum -= fruits[left][1]
                left += 1
            retVal = max(retVal, sum)

            right += 1

        return retVal
```

</details>

## [2134. Minimum Swaps to Group All 1's Together II](https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together-ii/)  1748

- [Official](https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together-ii/editorial/)
- [Official](https://leetcode.cn/problems/minimum-swaps-to-group-all-1s-together-ii/solutions/1202043/zui-shao-jiao-huan-ci-shu-lai-zu-he-suo-iaghf/)

<details><summary>Description</summary>

```text
A swap is defined as taking two distinct positions in an array and swapping the values in them.

A circular array is defined as an array where we consider the first element and the last element to be adjacent.

Given a binary circular array nums,
return the minimum number of swaps required to group all 1's present in the array together at any location.

Example 1:
Input: nums = [0,1,0,1,1,0,0]
Output: 1
Explanation: Here are a few of the ways to group all the 1's together:
[0,0,1,1,1,0,0] using 1 swap.
[0,1,1,1,0,0,0] using 1 swap.
[1,1,0,0,0,0,1] using 2 swaps (using the circular property of the array).
There is no way to group all 1's together with 0 swaps.
Thus, the minimum number of swaps required is 1.

Example 2:
Input: nums = [0,1,1,1,0,0,1,1,0]
Output: 2
Explanation: Here are a few of the ways to group all the 1's together:
[1,1,1,0,0,0,0,1,1] using 2 swaps (using the circular property of the array).
[1,1,1,1,1,0,0,0,0] using 2 swaps.
There is no way to group all 1's together with 0 or 1 swaps.
Thus, the minimum number of swaps required is 2.

Example 3:
Input: nums = [1,1,0,0,1]
Output: 0
Explanation: All the 1's are already grouped together due to the circular property of the array.
Thus, the minimum number of swaps required is 0.

Constraints:
1 <= nums.length <= 10^5
nums[i] is either 0 or 1.
```

<details><summary>Hint</summary>

```text
1. Notice that the number of 1’s to be grouped together is fixed. It is the number of 1's the whole array has.
2. Call this number total. We should then check for every subarray of size total (possibly wrapped around),
   how many swaps are required to have the subarray be all 1’s.
3. The number of swaps required is the number of 0’s in the subarray.
4. To eliminate the circular property of the array, we can append the original array to itself.
   Then, we check each subarray of length total.
5. How do we avoid recounting the number of 0’s in the subarray each time? The Sliding Window technique can help.
```

</details>

</details>

<details><summary>C</summary>

```c
// Helper function to calculate the minimum swaps required to group all value together
int minSwapsHelper(int* nums, int numsSize, int value) {
    int retVal = 0;

    // Count the total number of value in the array
    int totalValCount = 0;
    int i;
    for (i = numsSize - 1; i >= 0; i--) {
        if (nums[i] == value) {
            totalValCount++;
        }
    }
    // If there is no value or the array is full of value, no swaps are needed
    if ((totalValCount == 0) || (totalValCount == numsSize)) {
        return retVal;
    }

    int start = 0;
    int end = 0;
    int maxValInWindow = 0;
    int currentValInWindow = 0;

    // Initial window setup: count the number of value in the first window of size `totalValCount`
    while (end < totalValCount) {
        if (nums[end++] == value) {
            currentValInWindow++;
        }
    }
    maxValInWindow = fmax(maxValInWindow, currentValInWindow);

    // Slide the window across the array to find the maximum number of value in any window
    while (end < numsSize) {
        if (nums[start++] == value) {
            currentValInWindow--;
        }

        if (nums[end++] == value) {
            currentValInWindow++;
        }

        maxValInWindow = fmax(maxValInWindow, currentValInWindow);
    }

    // Minimum swaps are the total value minus the maximum found in any window
    retVal = totalValCount - maxValInWindow;

    return retVal;
}
int minSwaps(int* nums, int numsSize) {
    int retVal = 0;

    // Calculate the minimum swaps needed to group all 1s or all 0s together
    int op0 = minSwapsHelper(nums, numsSize, 0);  // Grouping all 0s together
    int op1 = minSwapsHelper(nums, numsSize, 1);  // Grouping all 1s together
    retVal = fmin(op0, op1);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    // Helper function to calculate the minimum swaps required to group all value together
    int minSwapsHelper(vector<int>& nums, int value) {
        int retVal = 0;

        int numsSize = nums.size();

        // Count the total number of value in the array
        int totalValCount = 0;
        for (int i = numsSize - 1; i >= 0; i--) {
            if (nums[i] == value) {
                totalValCount++;
            }
        }
        // If there is no value or the array is full of value, no swaps are needed
        if ((totalValCount == 0) || (totalValCount == numsSize)) {
            return retVal;
        }

        int start = 0;
        int end = 0;
        int maxValInWindow = 0;
        int currentValInWindow = 0;

        // Initial window setup: count the number of value in the first window of size `totalValCount`
        while (end < totalValCount) {
            if (nums[end++] == value) {
                currentValInWindow++;
            }
        }
        maxValInWindow = max(maxValInWindow, currentValInWindow);

        // Slide the window across the array to find the maximum number of value in any window
        while (end < numsSize) {
            if (nums[start++] == value) {
                currentValInWindow--;
            }

            if (nums[end++] == value) {
                currentValInWindow++;
            }

            maxValInWindow = max(maxValInWindow, currentValInWindow);
        }

        // Minimum swaps are the total value minus the maximum found in any window
        retVal = totalValCount - maxValInWindow;

        return retVal;
    }

   public:
    int minSwaps(vector<int>& nums) {
        int retVal = 0;

        // Calculate the minimum swaps needed to group all 1s or all 0s together
        int op0 = minSwapsHelper(nums, 0);  // Grouping all 0s together
        int op1 = minSwapsHelper(nums, 1);  // Grouping all 1s together
        retVal = min(op0, op1);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    # Helper function to calculate the minimum swaps required to group all value together
    def minSwapsHelper(self, nums: List[int], value: int) -> int:
        retVal = 0

        numsSize = len(nums)

        # Count the total number of value in the array
        totalValCount = 0
        for i in range(numsSize - 1, -1, -1):
            if nums[i] == value:
                totalValCount += 1
        # If there is no value or the array is full of value, no swaps are needed
        if (totalValCount == 0) or (totalValCount == numsSize):
            return retVal

        start = 0
        end = 0
        currentValInWindow = 0
        maxValInWindow = 0

        # Initial window setup: count the number of value in the first window of size `totalValCount`
        while end < totalValCount:
            if nums[end] == value:
                currentValInWindow += 1
            end += 1
        maxValInWindow = max(maxValInWindow, currentValInWindow)

        # Slide the window across the array to find the maximum number of value in any window
        while end < numsSize:
            if nums[start] == value:
                currentValInWindow -= 1
            start += 1

            if nums[end] == value:
                currentValInWindow += 1
            end += 1

            maxValInWindow = max(maxValInWindow, currentValInWindow)

        # Minimum swaps are the total value minus the maximum found in any window
        retVal = totalValCount - maxValInWindow

        return retVal

    def minSwaps(self, nums: List[int]) -> int:
        retVal = 0

        # Calculate the minimum swaps needed to group all 1s or all 0s together
        op0 = self.minSwapsHelper(nums, 0)  # Grouping all 0s together
        op1 = self.minSwapsHelper(nums, 1)  # Grouping all 1s together
        retVal = min(op0, op1)

        return retVal
```

</details>

## [2379. Minimum Recolors to Get K Consecutive Black Blocks](https://leetcode.com/problems/minimum-recolors-to-get-k-consecutive-black-blocks/)  1360

- [Official](https://leetcode.com/problems/minimum-recolors-to-get-k-consecutive-black-blocks/editorial/)
- [Official](https://leetcode.cn/problems/minimum-recolors-to-get-k-consecutive-black-blocks/solutions/2154899/de-dao-kge-hei-kuai-de-zui-shao-tu-se-ci-gjb0/)

<details><summary>Description</summary>

```text
You are given a 0-indexed string blocks of length n,
where blocks[i] is either 'W' or 'B', representing the color of the ith block.
The characters 'W' and 'B' denote the colors white and black, respectively.

You are also given an integer k, which is the desired number of consecutive black blocks.

In one operation, you can recolor a white block such that it becomes a black block.

Return the minimum number of operations needed such that there is at least one occurrence of k consecutive black blocks.

Example 1:
Input: blocks = "WBBWWBBWBW", k = 7
Output: 3
Explanation:
One way to achieve 7 consecutive black blocks is to recolor the 0th, 3rd, and 4th blocks
so that blocks = "BBBBBBBWBW".
It can be shown that there is no way to achieve 7 consecutive black blocks in less than 3 operations.
Therefore, we return 3.

Example 2:
Input: blocks = "WBWBBBW", k = 2
Output: 0
Explanation:
No changes need to be made, since 2 consecutive black blocks already exist.
Therefore, we return 0.

Constraints:
n == blocks.length
1 <= n <= 100
blocks[i] is either 'W' or 'B'.
1 <= k <= n
```

<details><summary>Hint</summary>

```text
1. Iterate through all possible consecutive substrings of k characters.
2. Find the number of changes for each substring to make all blocks black, and return the minimum of these.
```

</details>

</details>

<details><summary>C</summary>

```c
int minimumRecolors(char* blocks, int k) {
    int retVal = k;

    int blocksSize = strlen(blocks);
    int left = 0;
    int numWhites = 0;
    for (int right = 0; right < blocksSize; right++) {
        if (blocks[right] == 'W') {
            numWhites++;
        }

        if (right - left + 1 == k) {
            retVal = fmin(retVal, numWhites);

            if (blocks[left] == 'W') {
                numWhites--;
            }

            left++;
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
    int minimumRecolors(string blocks, int k) {
        int retVal = k;

        int blocksSize = blocks.size();
        int left = 0;
        int numWhites = 0;
        for (int right = 0; right < blocksSize; right++) {
            if (blocks[right] == 'W') {
                numWhites++;
            }

            if (right - left + 1 == k) {
                retVal = min(retVal, numWhites);

                if (blocks[left] == 'W') {
                    numWhites--;
                }

                left++;
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
    def minimumRecolors(self, blocks: str, k: int) -> int:
        retVal = k

        blocksSize = len(blocks)
        left = 0
        numWhites = 0
        for right in range(blocksSize):
            if blocks[right] == "W":
                numWhites += 1

            if right - left + 1 == k:
                retVal = min(retVal, numWhites)

                if blocks[left] == "W":
                    numWhites -= 1

                left += 1

        return retVal
```

</details>

## [2401. Longest Nice Subarray](https://leetcode.com/problems/longest-nice-subarray/)  1749

<details><summary>Description</summary>

```text
You are given an array nums consisting of positive integers.

We call a subarray of nums nice if the bitwise AND of every pair of elements
that are in different positions in the subarray is equal to 0.

Return the length of the longest nice subarray.

A subarray is a contiguous part of an array.

Note that subarrays of length 1 are always considered nice.

Example 1:
Input: nums = [1,3,8,48,10]
Output: 3
Explanation: The longest nice subarray is [3,8,48]. This subarray satisfies the conditions:
- 3 AND 8 = 0.
- 3 AND 48 = 0.
- 8 AND 48 = 0.
It can be proven that no longer nice subarray can be obtained, so we return 3.

Example 2:
Input: nums = [3,1,5,11,13]
Output: 1
Explanation: The length of the longest nice subarray is 1. Any subarray of length 1 can be chosen.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. What is the maximum possible length of a nice subarray?
2. The length of the longest nice subarray cannot exceed 30. Why is that?
```

</details>

</details>

<details><summary>C</summary>

```c
int longestNiceSubarray(int* nums, int numsSize) {
    int retVal = 0;

    int niceCheck = 0;
    int head = 0;
    int tail = 0;
    while (tail < numsSize) {
        while ((niceCheck & nums[tail]) != 0) {
            niceCheck ^= nums[head];
            ++head;
        }
        retVal = fmax(retVal, tail - head + 1);

        niceCheck |= nums[tail];
        ++tail;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int longestNiceSubarray(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        int niceCheck = 0;
        int head = 0;
        int tail = 0;
        while (tail < numsSize) {
            while ((niceCheck & nums[tail]) != 0) {
                niceCheck ^= nums[head];
                head++;
            }
            retVal = max(retVal, tail - head + 1);

            niceCheck |= nums[tail];
            tail++;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def longestNiceSubarray(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        niceCheck = 0
        head = 0
        tail = 0
        while (tail < numsSize):
            while ((niceCheck & nums[tail]) != 0):
                niceCheck ^= nums[head]
                head += 1
            retVal = max(retVal, tail - head + 1)

            niceCheck |= nums[tail]
            tail += 1

        return retVal
```

</details>

## [2444. Count Subarrays With Fixed Bounds](https://leetcode.com/problems/count-subarrays-with-fixed-bounds/)  2092

<details><summary>Description</summary>

```text
You are given an integer array nums and two integers minK and maxK.

A fixed-bound subarray of nums is a subarray that satisfies the following conditions:
- The minimum value in the subarray is equal to minK.
- The maximum value in the subarray is equal to maxK.
Return the number of fixed-bound subarrays.

A subarray is a contiguous part of an array.

Example 1:
Input: nums = [1,3,5,2,7,5], minK = 1, maxK = 5
Output: 2
Explanation: The fixed-bound subarrays are [1,3,5] and [1,3,5,2].

Example 2:
Input: nums = [1,1,1,1], minK = 1, maxK = 1
Output: 10
Explanation: Every subarray of nums is a fixed-bound subarray. There are 10 possible subarrays.

Constraints:
2 <= nums.length <= 10^5
1 <= nums[i], minK, maxK <= 10^6
```

<details><summary>Hint</summary>

```text
1. Can you solve the problem if all the numbers in the array were between minK and maxK inclusive?
2. Think of the inclusion-exclusion principle.
3. Divide the array into multiple subarrays such that each number in each subarray is between minK and maxK inclusive,
   solve the previous problem for each subarray, and sum all the answers.
```

</details>

</details>

<details><summary>C</summary>

```c
long long countSubarrays(int *nums, int numsSize, int minK, int maxK) {
    long long retVal = 0;

    /* Ref
     *  https://leetcode.com/problems/count-subarrays-with-fixed-bounds/solutions/2708099/java-c-python-sliding-window-with-explanation/
     *  https://leetcode.cn/problems/count-subarrays-with-fixed-bounds/solutions/1895734/fen-xi-ding-jie-zi-shu-zu-de-xing-zhi-yi-qusi/
     *  https://leetcode.cn/problems/count-subarrays-with-fixed-bounds/solutions/1895713/jian-ji-xie-fa-pythonjavacgo-by-endlessc-gag2/
     */
    long long badIdx = -1;
    long long minIdx = -1;
    long long maxIdx = -1;
    for (int i = 0; i < numsSize; ++i) {
        if ((nums[i] < minK) || (nums[i] > maxK)) {
            badIdx = i;
        }

        if (nums[i] == minK) {
            minIdx = i;
        }

        if (nums[i] == maxK) {
            maxIdx = i;
        }

        retVal += fmax(0, fmin(minIdx, maxIdx) - badIdx);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        long long retVal = 0;

        /* Ref
         *  https://leetcode.com/problems/count-subarrays-with-fixed-bounds/solutions/2708099/java-c-python-sliding-window-with-explanation/
         *  https://leetcode.cn/problems/count-subarrays-with-fixed-bounds/solutions/1895734/fen-xi-ding-jie-zi-shu-zu-de-xing-zhi-yi-qusi/
         *  https://leetcode.cn/problems/count-subarrays-with-fixed-bounds/solutions/1895713/jian-ji-xie-fa-pythonjavacgo-by-endlessc-gag2/
         */
        int len = nums.size();
        long long badIdx = -1;
        long long minIdx = -1;
        long long maxIdx = -1;
        for (int i = 0; i < len; ++i) {
            if ((nums[i] < minK) || (nums[i] > maxK)) {
                badIdx = i;
            }

            if (nums[i] == minK) {
                minIdx = i;
            }

            if (nums[i] == maxK) {
                maxIdx = i;
            }

            /* avoid different type between a and b in max function
             *  Because std::max is a function template whose signature is, for example,
             *  template< class T >
             *  const T& max( const T& a, const T& b );
             */
            long long n1 = 0;
            long long n2 = min(minIdx, maxIdx) - badIdx;
            retVal += max(n1, n2);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def countSubarrays(self, nums: List[int], minK: int, maxK: int) -> int:
        retVal = 0

        # /* Ref
        #  *  https://leetcode.com/problems/count-subarrays-with-fixed-bounds/solutions/2708099/java-c-python-sliding-window-with-explanation/
        #  *  https://leetcode.cn/problems/count-subarrays-with-fixed-bounds/solutions/1895734/fen-xi-ding-jie-zi-shu-zu-de-xing-zhi-yi-qusi/
        #  *  https://leetcode.cn/problems/count-subarrays-with-fixed-bounds/solutions/1895713/jian-ji-xie-fa-pythonjavacgo-by-endlessc-gag2/
        #  */
        numsSize = len(nums)
        badIdx = -1
        minIdx = -1
        maxIdx = -1
        for i in range(numsSize):
            if (nums[i] < minK) or (nums[i] > maxK):
                badIdx = i

            if (nums[i] == minK):
                minIdx = i

            if (nums[i] == maxK):
                maxIdx = i

            # /* avoid different type between a and b in max function
            #  *  Because std::max is a function template whose signature is, for example,
            #  *  template< class T >
            #  *  const T& max( const T& a, const T& b );
            #  */

            n1 = 0
            n2 = min(minIdx, maxIdx) - badIdx
            retVal += max(n1, n2)

        return retVal
```

</details>

## [2461. Maximum Sum of Distinct Subarrays With Length K](https://leetcode.com/problems/maximum-sum-of-distinct-subarrays-with-length-k/)  1552

- [Official](https://leetcode.com/problems/maximum-sum-of-distinct-subarrays-with-length-k/editorial/)

<details><summary>Description</summary>

```text
You are given an integer array nums and an integer k.
Find the maximum subarray sum of all the subarrays of nums that meet the following conditions:
- The length of the subarray is k, and
- All the elements of the subarray are distinct.

Return the maximum subarray sum of all the subarrays that meet the conditions.
If no subarray meets the conditions, return 0.

A subarray is a contiguous non-empty sequence of elements within an array.

Example 1:
Input: nums = [1,5,4,2,9,9,9], k = 3
Output: 15
Explanation: The subarrays of nums with length 3 are:
- [1,5,4] which meets the requirements and has a sum of 10.
- [5,4,2] which meets the requirements and has a sum of 11.
- [4,2,9] which meets the requirements and has a sum of 15.
- [2,9,9] which does not meet the requirements because the element 9 is repeated.
- [9,9,9] which does not meet the requirements because the element 9 is repeated.
We return 15 because it is the maximum subarray sum of all the subarrays that meet the conditions

Example 2:
Input: nums = [4,4,4], k = 3
Output: 0
Explanation: The subarrays of nums with length 3 are:
- [4,4,4] which does not meet the requirements because the element 4 is repeated.
We return 0 because no subarrays meet the conditions.

Constraints:
1 <= k <= nums.length <= 10^5
1 <= nums[i] <= 10^5
```

<details><summary>Hint</summary>

```text
1. Which elements change when moving from the subarray of size k
   that ends at index i to the subarray of size k that ends at index i + 1?
2. Only two elements change, the element at i + 1 is added into the subarray,
   and the element at i - k + 1 gets removed from the subarray.
3. Iterate through each subarray of size k and keep track of the sum of the subarray
   and the frequency of each element.
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
long long maximumSubarraySum(int *nums, int numsSize, int k) {
    long long retVal = 0;

    struct hashTable *numToIndex = NULL;
    struct hashTable *pTemp;

    int currNum, lastOccurrence;
    long long currentSum = 0;
    int begin = 0;
    int end = 0;
    while (end < numsSize) {
        currNum = nums[end];

        pTemp = NULL;
        HASH_FIND_INT(numToIndex, &currNum, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(numToIndex);
                return retVal;
            }
            pTemp->key = currNum;
            pTemp->value = -1;
            HASH_ADD_INT(numToIndex, key, pTemp);
        }
        lastOccurrence = pTemp->value;

        // if current window already has number or if window is too big, adjust window
        while ((begin <= lastOccurrence) || (end - begin + 1 > k)) {
            currentSum -= nums[begin];
            begin++;
        }

        pTemp = NULL;
        pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
        if (pTemp == NULL) {
            perror("malloc");
            freeAll(numToIndex);
            return retVal;
        }
        pTemp->key = currNum;
        pTemp->value = end;
        HASH_ADD_INT(numToIndex, key, pTemp);

        currentSum += nums[end];
        if (end - begin + 1 == k) {
            retVal = fmax(retVal, currentSum);
        }

        end++;
    }

    //
    freeAll(numToIndex);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        long long retVal = 0;

        int numsSize = nums.size();

        unordered_map<int, int> numToIndex;
        long long currentSum = 0;
        int begin = 0;
        int end = 0;
        while (end < numsSize) {
            int currNum = nums[end];
            int lastOccurrence = (numToIndex.count(currNum) ? numToIndex[currNum] : -1);

            // if current window already has number or if window is too big, adjust window
            while ((begin <= lastOccurrence) || (end - begin + 1 > k)) {
                currentSum -= nums[begin];
                begin++;
            }

            numToIndex[currNum] = end;
            currentSum += nums[end];
            if (end - begin + 1 == k) {
                retVal = max(retVal, currentSum);
            }

            end++;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maximumSubarraySum(self, nums: List[int], k: int) -> int:
        retVal = 0

        numsSize = len(nums)

        numToIndex = {}
        currentSum = 0
        begin = 0
        end = 0
        while end < numsSize:
            currNum = nums[end]
            lastOccurrence = numToIndex.get(currNum, -1)

            # if current window already has number or if window is too big, adjust window
            while (begin <= lastOccurrence) or (end - begin + 1 > k):
                currentSum -= nums[begin]
                begin += 1

            numToIndex[currNum] = end
            currentSum += nums[end]
            if end - begin + 1 == k:
                retVal = max(retVal, currentSum)

            end += 1

        return retVal
```

</details>

## [2516. Take K of Each Character From Left and Right](https://leetcode.com/problems/take-k-of-each-character-from-left-and-right/)  1947

- [Official](https://leetcode.com/problems/take-k-of-each-character-from-left-and-right/editorial/)
- [Official](https://leetcode.cn/problems/take-k-of-each-character-from-left-and-right/solutions/2928177/mei-chong-zi-fu-zhi-shao-qu-k-ge-by-leet-10ct/)

<details><summary>Description</summary>

```text
You are given a string s consisting of the characters 'a', 'b', and 'c' and a non-negative integer k.
Each minute, you may take either the leftmost character of s, or the rightmost character of s.

Return the minimum number of minutes needed for you to take at least k of each character,
or return -1 if it is not possible to take k of each character.

Example 1:
Input: s = "aabaaaacaabc", k = 2
Output: 8
Explanation:
Take three characters from the left of s. You now have two 'a' characters, and one 'b' character.
Take five characters from the right of s. You now have four 'a' characters, two 'b' characters, and two 'c' characters.
A total of 3 + 5 = 8 minutes is needed.
It can be proven that 8 is the minimum number of minutes needed.

Example 2:
Input: s = "a", k = 1
Output: -1
Explanation: It is not possible to take one 'b' or 'c' so return -1.

Constraints:
1 <= s.length <= 10^5
s consists of only the letters 'a', 'b', and 'c'.
0 <= k <= s.length
```

<details><summary>Hint</summary>

```text
1. Start by counting the frequency of each character and checking if it is possible.
2. If you take x characters from the left side, what is the minimum number of characters you need to take
   from the right side? Find this for all values of x in the range 0 ≤ x ≤ s.length.
3. Use a two-pointers approach to avoid computing the same information multiple times.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MAX_LETTERS_SIZE (3)  // s consists of only the letters 'a', 'b', and 'c'.
int takeCharacters(char* s, int k) {
    int retVal = -1;

    int sSize = strlen(s);
    int i;

    // Count total occurrences
    int count[MAX_LETTERS_SIZE];
    memset(count, 0, sizeof(count));
    for (i = 0; i < sSize; ++i) {
        count[s[i] - 'a']++;
    }

    // Check if we have enough characters
    for (i = 0; i < MAX_LETTERS_SIZE; i++) {
        if (count[i] < k) {
            return retVal;
        }
    }

    // Find the longest window that leaves k of each character outside
    int window[MAX_LETTERS_SIZE];
    memset(window, 0, sizeof(window));
    int maxWindow = 0;
    int left = 0;
    int right = 0;
    for (right = 0; right < sSize; right++) {
        window[s[right] - 'a']++;

        // Shrink window if we take too many characters
        while ((left <= right) &&
               ((count[0] - window[0] < k) || (count[1] - window[1] < k) || (count[2] - window[2] < k))) {
            window[s[left] - 'a']--;
            left++;
        }

        maxWindow = fmax(maxWindow, right - left + 1);
    }

    retVal = sSize - maxWindow;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    int lettersSize = 3;  // s consists of only the letters 'a', 'b', and 'c'.

   public:
    int takeCharacters(string s, int k) {
        int retVal = -1;

        int sSize = s.length();

        // Count total occurrences
        vector<int> count(lettersSize, 0);
        for (char c : s) {
            count[c - 'a']++;
        }

        // Check if we have enough characters
        for (int i = 0; i < lettersSize; i++) {
            if (count[i] < k) {
                return retVal;
            }
        }

        // Find the longest window that leaves k of each character outside
        vector<int> window(lettersSize, 0);
        int maxWindow = 0;
        int left = 0;
        for (int right = 0; right < sSize; right++) {
            window[s[right] - 'a']++;

            // Shrink window if we take too many characters
            while ((left <= right) &&
                   ((count[0] - window[0] < k) || (count[1] - window[1] < k) || (count[2] - window[2] < k))) {
                window[s[left] - 'a']--;
                left++;
            }

            maxWindow = max(maxWindow, right - left + 1);
        }

        retVal = sSize - maxWindow;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def __init__(self) -> None:
        self.letters = 3  # s consists of only the letters 'a', 'b', and 'c'.

    def takeCharacters(self, s: str, k: int) -> int:
        retVal = -1

        sSize = len(s)

        # Count total occurrences
        count = [0] * self.letters
        for c in s:
            count[ord(c) - ord("a")] += 1

        # Check if we have enough characters
        for i in range(self.letters):
            if count[i] < k:
                return retVal

        # Find the longest window that leaves k of each character outside
        window = [0] * self.letters
        maxWindow = 0
        left = 0
        for right in range(sSize):
            window[ord(s[right]) - ord("a")] += 1

            # Shrink window if we take too many characters
            while ((left <= right) and
                   ((count[0] - window[0] < k) or (count[1] - window[1] < k) or (count[2] - window[2] < k))):
                window[ord(s[left]) - ord("a")] -= 1
                left += 1

            maxWindow = max(maxWindow, right - left + 1)

        retVal = sSize - maxWindow

        return retVal
```

</details>

## [2762. Continuous Subarrays](https://leetcode.com/problems/continuous-subarrays/)  1940

- [Official](https://leetcode.com/problems/continuous-subarrays/editorial/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array nums. A subarray of nums is called continuous if:
- Let i, i + 1, ..., j be the indices in the subarray.
  Then, for each pair of indices i <= i1, i2 <= j, 0 <= |nums[i1] - nums[i2]| <= 2.

Return the total number of continuous subarrays.

A subarray is a contiguous non-empty sequence of elements within an array.

Example 1:
Input: nums = [5,4,2,4]
Output: 8
Explanation:
Continuous subarray of size 1: [5], [4], [2], [4].
Continuous subarray of size 2: [5,4], [4,2], [2,4].
Continuous subarray of size 3: [4,2,4].
Thereare no subarrys of size 4.
Total continuous subarrays = 4 + 3 + 1 = 8.
It can be shown that there are no more continuous subarrays.

Example 2:
Input: nums = [1,2,3]
Output: 6
Explanation:
Continuous subarray of size 1: [1], [2], [3].
Continuous subarray of size 2: [1,2], [2,3].
Continuous subarray of size 3: [1,2,3].
Total continuous subarrays = 3 + 2 + 1 = 6.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Try using the sliding window technique.
2. Use a set or map to keep track of the maximum and minimum of subarrays.
```

</details>

</details>

<details><summary>C</summary>

```c
long long continuousSubarrays(int* nums, int numsSize) {
    long long retVal = 0;

    int right = 0;
    int left = 0;
    int curMin = nums[right];
    int curMax = nums[right];
    long long windowLen = 0;
    for (right = 0; right < numsSize; right++) {
        curMin = fmin(curMin, nums[right]);
        curMax = fmax(curMax, nums[right]);
        if (curMax - curMin <= 2) {
            continue;
        }

        // Add subarrays from the previous valid window
        windowLen = (right - left);
        retVal += (windowLen * (windowLen + 1) / 2);
        // Start a new window at the current position
        left = right;
        curMin = curMax = nums[right];
        // Expand left boundary while maintaining the condition
        while ((left > 0) && (abs(nums[right] - nums[left - 1]) <= 2)) {
            left--;
            curMin = fmin(curMin, nums[left]);
            curMax = fmax(curMax, nums[left]);
        }
        // Remove overcounted subarrays if left boundary expanded
        if (left < right) {
            windowLen = right - left;
            retVal -= (windowLen * (windowLen + 1) / 2);
        }
    }

    // Add subarrays from the final window
    windowLen = right - left;
    retVal += (windowLen * (windowLen + 1) / 2);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long continuousSubarrays(vector<int>& nums) {
        long long retVal = 0;

        int numsSize = nums.size();

        int right = 0;
        int left = 0;
        int curMin = nums[right];
        int curMax = nums[right];
        long long windowLen = 0;
        for (right = 0; right < numsSize; right++) {
            curMin = min(curMin, nums[right]);
            curMax = max(curMax, nums[right]);
            if (curMax - curMin <= 2) {
                continue;
            }

            // Add subarrays from the previous valid window
            windowLen = (right - left);
            retVal += (windowLen * (windowLen + 1) / 2);
            // Start a new window at the current position
            left = right;
            curMin = curMax = nums[right];
            // Expand left boundary while maintaining the condition
            while ((left > 0) && (abs(nums[right] - nums[left - 1]) <= 2)) {
                left--;
                curMin = min(curMin, nums[left]);
                curMax = max(curMax, nums[left]);
            }
            // Remove overcounted subarrays if left boundary expanded
            if (left < right) {
                windowLen = right - left;
                retVal -= (windowLen * (windowLen + 1) / 2);
            }
        }

        // Add subarrays from the final window
        windowLen = right - left;
        retVal += (windowLen * (windowLen + 1) / 2);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def continuousSubarrays(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        right = 0
        left = 0
        curMin = nums[right]
        curMax = nums[right]
        windowLen = 0
        for right in range(numsSize):
            curMin = min(curMin, nums[right])
            curMax = max(curMax, nums[right])
            if curMax - curMin <= 2:
                continue

            # Add subarrays from previous valid window
            windowLen = right - left
            retVal += windowLen * (windowLen + 1) // 2
            # Start new window at current position
            left = right
            curMin = nums[right]
            curMax = nums[right]
            # Expand left boundary while maintaining condition
            while (left > 0) and (abs(nums[right] - nums[left - 1]) <= 2):
                left -= 1
                curMin = min(curMin, nums[left])
                curMax = max(curMax, nums[left])
            # Remove overcounted subarrays if left boundary expanded
            if left < right:
                windowLen = right - left
                retVal -= windowLen * (windowLen + 1) // 2

        # Add subarrays from final window
        windowLen = right - left + 1
        retVal += windowLen * (windowLen + 1) // 2

        return retVal
```

</details>

## [2799. Count Complete Subarrays in an Array](https://leetcode.com/problems/count-complete-subarrays-in-an-array/)  1397

- [Official](https://leetcode.com/problems/count-complete-subarrays-in-an-array/editorial/)
- [Official](https://leetcode.cn/problems/count-complete-subarrays-in-an-array/solutions/3650491/tong-ji-wan-quan-zi-shu-zu-de-shu-mu-by-ysvhb/)

<details><summary>Description</summary>

```text
You are given an array nums consisting of positive integers.

We call a subarray of an array complete if the following condition is satisfied:
- The number of distinct elements in the subarray is equal to the number of distinct elements in the whole array.

Return the number of complete subarrays.

A subarray is a contiguous non-empty part of an array.

Example 1:
Input: nums = [1,3,1,2,2]
Output: 4
Explanation: The complete subarrays are the following: [1,3,1,2], [1,3,1,2,2], [3,1,2] and [3,1,2,2].

Example 2:
Input: nums = [5,5,5,5]
Output: 10
Explanation: The array consists only of the integer 5, so any subarray is complete.
The number of subarrays that we can choose is 10.

Constraints:
1 <= nums.length <= 1000
1 <= nums[i] <= 2000
```

<details><summary>Hint</summary>

```text
1. Let’s say k is the number of distinct elements in the array.
   Our goal is to find the number of subarrays with k distinct elements.
2. Since the constraints are small, you can check every subarray.
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
        // printf("%d: %d\n", current->key, current->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int countCompleteSubarrays(int *nums, int numsSize) {
    int retVal = 0;

    struct hashTable *pDistinct = NULL;
    struct hashTable *pTemp;
    int key;
    for (int i = 0; i < numsSize; i++) {
        key = nums[i];
        pTemp = NULL;
        HASH_FIND_INT(pDistinct, &key, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pDistinct);
                return retVal;
            }
            pTemp->key = key;
            pTemp->value = 1;
            HASH_ADD_INT(pDistinct, key, pTemp);
        }
    }
    int distinctSize = HASH_COUNT(pDistinct);

    struct hashTable *pHashTable = NULL;
    int pHashTableSize;
    int remove, add;
    int right = 0;
    for (int left = 0; left < numsSize; left++) {
        if (left > 0) {
            remove = nums[left - 1];
            pTemp = NULL;
            HASH_FIND_INT(pHashTable, &remove, pTemp);
            if (pTemp == NULL) {
                pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
                if (pTemp == NULL) {
                    perror("malloc");
                    freeAll(pHashTable);
                    freeAll(pDistinct);
                    return retVal;
                }
                pTemp->key = remove;
                pTemp->value = -1;
                HASH_ADD_INT(pHashTable, key, pTemp);
            } else {
                pTemp->value -= 1;
            }

            if (pTemp->value == 0) {
                HASH_DEL(pHashTable, pTemp);
                free(pTemp);
            }
        }

        pHashTableSize = HASH_COUNT(pHashTable);
        while (right < numsSize) {
            if (pHashTableSize >= distinctSize) {
                break;
            }

            add = nums[right];
            pTemp = NULL;
            HASH_FIND_INT(pHashTable, &add, pTemp);
            if (pTemp == NULL) {
                pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
                if (pTemp == NULL) {
                    perror("malloc");
                    freeAll(pHashTable);
                    freeAll(pDistinct);
                    return retVal;
                }
                pTemp->key = add;
                pTemp->value = 1;
                HASH_ADD_INT(pHashTable, key, pTemp);
            } else {
                pTemp->value += 1;
            }
            pHashTableSize = HASH_COUNT(pHashTable);

            right++;
        }

        if (pHashTableSize == distinctSize) {
            retVal += (numsSize - right + 1);
        }
    }

    //
    freeAll(pHashTable);
    freeAll(pDistinct);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int countCompleteSubarrays(vector<int>& nums) {
        int retVal = 0;

        unordered_set<int> distinct(nums.begin(), nums.end());
        int distinctSize = distinct.size();

        unordered_map<int, int> hashTable;
        int numsSize = nums.size();
        int right = 0;
        for (int left = 0; left < numsSize; left++) {
            if (left > 0) {
                int remove = nums[left - 1];
                hashTable[remove]--;
                if (hashTable[remove] == 0) {
                    hashTable.erase(remove);
                }
            }

            int hashTableSize = hashTable.size();
            while (right < numsSize) {
                if (hashTableSize >= distinctSize) {
                    break;
                }

                int add = nums[right];
                hashTable[add]++;
                hashTableSize = hashTable.size();
                right++;
            }

            if (hashTableSize == distinctSize) {
                retVal += (numsSize - right + 1);
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
    def countCompleteSubarrays(self, nums: List[int]) -> int:
        retVal = 0

        distinct = set(nums)
        distinctSize = len(distinct)

        hashTable = {}
        numsSize = len(nums)
        right = 0
        for left in range(numsSize):
            if left > 0:
                remove = nums[left - 1]
                hashTable[remove] -= 1
                if hashTable[remove] == 0:
                    hashTable.pop(remove)

            hashTableSize = len(hashTable)
            while right < numsSize:
                if hashTableSize >= distinctSize:
                    break
                add = nums[right]
                hashTable[add] = hashTable.get(add, 0) + 1
                hashTableSize = len(hashTable)
                right += 1

            if hashTableSize == distinctSize:
                retVal += (numsSize - right + 1)

        return retVal
```

</details>

## [2958. Length of Longest Subarray With at Most K Frequency](https://leetcode.com/problems/length-of-longest-subarray-with-at-most-k-frequency/)  1535

- [Official](https://leetcode.com/problems/length-of-longest-subarray-with-at-most-k-frequency/editorial/)

<details><summary>Description</summary>

```text
You are given an integer array nums and an integer k.

The frequency of an element x is the number of times it occurs in an array.

An array is called good if the frequency of each element in this array is less than or equal to k.

Return the length of the longest good subarray of nums.

A subarray is a contiguous non-empty sequence of elements within an array.

Example 1:
Input: nums = [1,2,3,1,2,3,1,2], k = 2
Output: 6
Explanation: The longest possible good subarray is [1,2,3,1,2,3]
since the values 1, 2, and 3 occur at most twice in this subarray.
Note that the subarrays [2,3,1,2,3,1] and [3,1,2,3,1,2] are also good.
It can be shown that there are no good subarrays with length more than 6.

Example 2:
Input: nums = [1,2,1,2,1,2,1,2], k = 1
Output: 2
Explanation: The longest possible good subarray is [1,2] since the values 1 and 2 occur at most once in this subarray.
Note that the subarray [2,1] is also good.
It can be shown that there are no good subarrays with length more than 2.

Example 3:
Input: nums = [5,5,5,5,5,5,5], k = 4
Output: 4
Explanation: The longest possible good subarray is [5,5,5,5] since the value 5 occurs 4 times in this subarray.
It can be shown that there are no good subarrays with length more than 4.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
1 <= k <= nums.length
```

<details><summary>Hint</summary>

```text
1. For each index i,
   find the rightmost index j >= i such that the frequency of each element in the subarray [i, j] is at most k.
2. We can use 2 pointers / sliding window to achieve it.
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
int maxSubarrayLength(int *nums, int numsSize, int k) {
    int retVal = 0;

    struct hashTable *pFrequency = NULL;
    struct hashTable *pTempStart, *pTempEnd;
    int startKey, endKey;
    int start = -1, end = 0;
    for (end = 0; end < numsSize; ++end) {
        endKey = nums[end];
        pTempEnd = NULL;
        HASH_FIND_INT(pFrequency, &endKey, pTempEnd);
        if (pTempEnd == NULL) {
            pTempEnd = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTempEnd == NULL) {
                perror("malloc");
                goto exit;
            }
            pTempEnd->key = endKey;
            pTempEnd->value = 1;
            HASH_ADD_INT(pFrequency, key, pTempEnd);
        } else {
            pTempEnd->value += 1;
        }

        while (pTempEnd->value > k) {
            start++;

            startKey = nums[start];
            pTempStart = NULL;
            HASH_FIND_INT(pFrequency, &startKey, pTempStart);
            pTempStart->value -= 1;
        }

        retVal = fmax(retVal, (end - start));
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
    int maxSubarrayLength(vector<int>& nums, int k) {
        int retVal = 0;

        int numsSize = nums.size();
        unordered_map<int, int> frequency;
        int start = -1;
        for (int end = 0; end < numsSize; ++end) {
            frequency[nums[end]]++;
            while (frequency[nums[end]] > k) {
                start++;
                frequency[nums[start]]--;
            }
            retVal = max(retVal, (end - start));
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxSubarrayLength(self, nums: List[int], k: int) -> int:
        retVal = 0

        frequency = defaultdict(int)
        start = -1
        for end, value in enumerate(nums):
            frequency[value] += 1
            while frequency[value] > k:
                start += 1
                frequency[nums[start]] -= 1
            retVal = max(retVal, end - start)

        return retVal
```

</details>

## [2962. Count Subarrays Where Max Element Appears at Least K Times](https://leetcode.com/problems/count-subarrays-where-max-element-appears-at-least-k-times/)  1700

- [Official](https://leetcode.com/problems/count-subarrays-where-max-element-appears-at-least-k-times/editorial/)

<details><summary>Description</summary>

```text
You are given an integer array nums and a positive integer k.

Return the number of subarrays where the maximum element of nums appears at least k times in that subarray.

A subarray is a contiguous sequence of elements within an array.

Example 1:
Input: nums = [1,3,2,3,3], k = 2
Output: 6
Explanation: The subarrays that contain the element 3 at least 2 times are:
[1,3,2,3], [1,3,2,3,3], [3,2,3], [3,2,3,3], [2,3,3] and [3,3].

Example 2:
Input: nums = [1,4,2,1], k = 3
Output: 0
Explanation: No subarray contains the element 4 at least 3 times.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^6
1 <= k <= 10^5
```

</details>

<details><summary>C</summary>

```c
long long countSubarrays(int *nums, int numsSize, int k) {
    long long retVal = 0;

    int maxNum = nums[0];  // 1 <= nums.length <= 10^5
    int i;
    for (i = 1; i < numsSize; ++i) {
        if (maxNum < nums[i]) {
            maxNum = nums[i];
        }
    }
    int maxNumWindow = 0;

    int start = 0;
    int end = 0;
    for (end = 0; end < numsSize; ++end) {
        if (nums[end] == maxNum) {
            maxNumWindow++;
        }

        while (maxNumWindow == k) {
            if (nums[start] == maxNum) {
                maxNumWindow--;
            }
            start++;
        }

        retVal += start;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long countSubarrays(vector<int>& nums, int k) {
        long long retVal = 0;

        int numsSize = nums.size();
        int maxNum = *max_element(nums.begin(), nums.end());
        int maxNumWindow = 0;
        int start = 0;
        int end = 0;
        for (end = 0; end < numsSize; ++end) {
            if (nums[end] == maxNum) {
                maxNumWindow++;
            }

            while (maxNumWindow == k) {
                if (nums[start] == maxNum) {
                    maxNumWindow--;
                }
                start++;
            }

            retVal += start;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def countSubarrays(self, nums: List[int], k: int) -> int:
        retVal = 0

        numsSize = len(nums)
        maxNum = max(nums)
        maxNumWindow = 0
        start = 0
        for end in range(numsSize):
            if nums[end] == maxNum:
                maxNumWindow += 1

            while maxNumWindow == k:
                if nums[start] == maxNum:
                    maxNumWindow -= 1
                start += 1

            retVal += start

        return retVal
```

</details>
