# [Stack](https://en.wikipedia.org/wiki/Stack_(abstract_data_type))

- Monotonic Stack

## [3174. Clear Digits](https://leetcode.com/problems/clear-digits/)  1255

- [Official](https://leetcode.com/problems/clear-digits/editorial/)
- [Official](https://leetcode.cn/problems/clear-digits/solutions/2901101/qing-chu-shu-zi-by-leetcode-solution-66qk/)

<details><summary>Description</summary>

```text
You are given a string s.

Your task is to remove all digits by doing this operation repeatedly:
- Delete the first digit and the closest non-digit character to its left.

Return the resulting string after removing all digits.

Example 1:
Input: s = "abc"
Output: "abc"
Explanation:
There is no digit in the string.

Example 2:
Input: s = "cb34"
Output: ""
Explanation:
First, we apply the operation on s[2], and s becomes "c4".
Then we apply the operation on s[1], and s becomes "".

Constraints:
1 <= s.length <= 100
s consists only of lowercase English letters and digits.
The input is generated such that it is possible to delete all digits.
```

<details><summary>Hint</summary>

```text
1. Process string s from left to right, if s[i] is a digit, mark the nearest unmarked non-digit index to its left.
2. Delete all digits and all marked characters.
```

</details>

</details>

<details><summary>C</summary>

```c
char* clearDigits(char* s) {
    char* pRetVal = NULL;

    int sSize = strlen(s);
    int returnSize = sSize + 1;

    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));

    returnSize = 0;
    for (int i = 0; i < sSize; ++i) {
        if ((isdigit(s[i]) != 0) && (returnSize > 0)) {
            pRetVal[--returnSize] = 0;
        } else {
            pRetVal[returnSize++] = s[i];
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
    string clearDigits(string s) {
        string retVal;

        for (char c : s) {
            if (isdigit(c) != 0) {
                retVal.pop_back();
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
    def clearDigits(self, s: str) -> str:
        retVal = ""

        for c in s:
            if c.isdigit():
                retVal = retVal[:-1]
            else:
                retVal += c

        return retVal
```

</details>

## [3542. Minimum Operations to Convert All Elements to Zero](https://leetcode.com/problems/minimum-operations-to-convert-all-elements-to-zero/)  1890

- [Official](https://leetcode.com/problems/minimum-operations-to-convert-all-elements-to-zero/editorial/)
- [Official](https://leetcode.cn/problems/minimum-operations-to-convert-all-elements-to-zero/solutions/3819899/jiang-suo-you-yuan-su-bian-wei-0-de-zui-6f2r3/)

<details><summary>Description</summary>

```text
You are given an array nums of size n, consisting of non-negative integers.
Your task is to apply some (possibly zero) operations on the array so that all elements become 0.

In one operation, you can select a subarray [i, j] (where 0 <= i <= j < n)
and set all occurrences of the minimum non-negative integer in that subarray to 0.

Return the minimum number of operations required to make all elements in the array 0.

Example 1:
Input: nums = [0,2]
Output: 1
Explanation:
- Select the subarray [1,1] (which is [2]), where the minimum non-negative integer is 2.
  Setting all occurrences of 2 to 0 results in [0,0].
- Thus, the minimum number of operations required is 1.

Example 2:
Input: nums = [3,1,2,1]
Output: 3
Explanation:
- Select subarray [1,3] (which is [1,2,1]), where the minimum non-negative integer is 1.
  Setting all occurrences of 1 to 0 results in [3,0,2,0].
- Select subarray [2,2] (which is [2]), where the minimum non-negative integer is 2.
  Setting all occurrences of 2 to 0 results in [3,0,0,0].
- Select subarray [0,0] (which is [3]), where the minimum non-negative integer is 3.
  Setting all occurrences of 3 to 0 results in [0,0,0,0].
- Thus, the minimum number of operations required is 3.

Example 3:
Input: nums = [1,2,1,2,1,2]
Output: 4
Explanation:
- Select subarray [0,5] (which is [1,2,1,2,1,2]), where the minimum non-negative integer is 1.
  Setting all occurrences of 1 to 0 results in [0,2,0,2,0,2].
- Select subarray [1,1] (which is [2]), where the minimum non-negative integer is 2.
  Setting all occurrences of 2 to 0 results in [0,0,0,2,0,2].
- Select subarray [3,3] (which is [2]), where the minimum non-negative integer is 2.
  Setting all occurrences of 2 to 0 results in [0,0,0,0,0,2].
- Select subarray [5,5] (which is [2]), where the minimum non-negative integer is 2.
  Setting all occurrences of 2 to 0 results in [0,0,0,0,0,0].
- Thus, the minimum number of operations required is 4.

Constraints:
1 <= n == nums.length <= 10^5
0 <= nums[i] <= 10^5
```

<details><summary>Hint</summary>

```text
1. Process the values in nums from smallest to largest (excluding 0).
2. For each target value v, identify its maximal contiguous segments (subarrays where nums[i] == v);
   each segment can be zeroed out in one operation.
3. After setting those segments to zero, dynamically update the remaining array and repeat with the next value.
```

</details>

</details>

<details><summary>C</summary>

```c
int minOperations(int* nums, int numsSize) {
    int retVal = 0;

    int monotonicStack[numsSize];
    int monotonicStackTop = 0;
    int num;
    for (int i = 0; i < numsSize; ++i) {
        num = nums[i];
        while ((monotonicStackTop > 0) && (monotonicStack[monotonicStackTop - 1] > num)) {
            --monotonicStackTop;
        }
        if (num == 0) {
            continue;
        }

        if ((monotonicStackTop == 0) || (monotonicStack[monotonicStackTop - 1] < num)) {
            retVal++;
            monotonicStack[monotonicStackTop++] = num;
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
    int minOperations(vector<int>& nums) {
        int retVal = 0;

        vector<int> monotonicStack;
        for (int num : nums) {
            while ((monotonicStack.empty() == false) && (monotonicStack.back() > num)) {
                monotonicStack.pop_back();
            }
            if (num == 0) {
                continue;
            }

            if ((monotonicStack.empty() == true) || (monotonicStack.back() < num)) {
                ++retVal;
                monotonicStack.push_back(num);
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
    def minOperations(self, nums: List[int]) -> int:
        retVal = 0

        monotonicStack = []
        for num in nums:
            while (monotonicStack) and (monotonicStack[-1] > num):
                monotonicStack.pop()
            if num == 0:
                continue

            if (not monotonicStack) or (monotonicStack[-1] < num):
                retVal += 1
                monotonicStack.append(num)

        return retVal
```

</details>
