# Greedy

## [45. Jump Game II](https://leetcode.com/problems/jump-game-ii/)

- [Official](https://leetcode.cn/problems/jump-game-ii/solutions/230241/tiao-yue-you-xi-ii-by-leetcode-solution/)

<details><summary>Description</summary>

```text
You are given a 0-indexed array of integers nums of length n. You are initially positioned at nums[0].

Each element nums[i] represents the maximum length of a forward jump from index i.
In other words, if you are at nums[i], you can jump to any nums[i + j] where:
- 0 <= j <= nums[i] and
- i + j < n

Return the minimum number of jumps to reach nums[n - 1].
The test cases are generated such that you can reach nums[n - 1].

Example 1:
Input: nums = [2,3,1,1,4]
Output: 2
Explanation:
The minimum number of jumps to reach the last index is 2.
Jump 1 step from index 0 to 1, then 3 steps to the last index.

Example 2:
Input: nums = [2,3,0,1,4]
Output: 2

Constraints:
1 <= nums.length <= 10^4
0 <= nums[i] <= 1000
It's guaranteed that you can reach nums[n - 1].
```

</details>

<details><summary>C</summary>

```c
int jump(int* nums, int numsSize) {
    int retVal = 0;

    int maxPosition = 0;
    int end = 0;
    int i;
    for (i = 0; i < (numsSize - 1); ++i) {
        // find maximum jumping length
        maxPosition = fmax(maxPosition, nums[i] + i);

        // reach end boundary need to  update end boundary and add steps
        if (i == end) {
            end = maxPosition;
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
    int jump(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        int maxPosition = 0;
        int end = 0;
        for (int i = 0; i < (numsSize - 1); ++i) {
            // find maximum jumping length
            maxPosition = max(maxPosition, nums[i] + i);

            // reach end boundary need to  update end boundary and add steps
            if (i == end) {
                end = maxPosition;
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
    def jump(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)
        maxPosition = 0
        end = 0
        for i in range(numsSize-1):
            # find maximum jumping length
            maxPosition = max(maxPosition, nums[i] + i)

            # reach end boundary need to  update end boundary and add steps
            if i == end:
                end = maxPosition
                retVal += 1

        return retVal
```

</details>

## [55. Jump Game](https://leetcode.com/problems/jump-game/)

- [Official](https://leetcode.cn/problems/jump-game/solutions/203549/tiao-yue-you-xi-by-leetcode-solution/)

<details><summary>Description</summary>

```text
You are given an integer array nums.
You are initially positioned at the array's first index,
and each element in the array represents your maximum jump length at that position.

Return true if you can reach the last index, or false otherwise.

Example 1:
Input: nums = [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.

Example 2:
Input: nums = [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what.
Its maximum jump length is 0, which makes it impossible to reach the last index.

Constraints:
1 <= nums.length <= 10^4
0 <= nums[i] <= 10^5
```

</details>

<details><summary>C</summary>

```c
bool canJump(int* nums, int numsSize) {
    bool retVal = false;

    /* maxPosition is index + nums[index]
     *  If maxPosition could not reach next index, thah is, it could not reach the last index.
     */
    int maxPosition = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if (i > maxPosition) {
            return retVal;
        }

        maxPosition = fmax(maxPosition, i + nums[i]);
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
    bool canJump(vector<int>& nums) {
        bool retVal = false;

        /* maxPosition is index + nums[index]
         *  If maxPosition could not reach next index, thah is, it could not reach the last index.
         */
        int maxPosition = 0;
        int numsSize = nums.size();
        for (int i = 0; i < numsSize; ++i) {
            if (i > maxPosition) {
                return retVal;
            }

            maxPosition = max(maxPosition, i + nums[i]);
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
    def canJump(self, nums: List[int]) -> bool:
        retVal = False

        # maxPosition is index + nums[index]
        #   If maxPosition could not reach next index, thah is, it could not reach the last index.
        maxPosition = 0
        numsSize = len(nums)
        for i in range(numsSize):
            if i > maxPosition:
                return retVal
            maxPosition = max(maxPosition, i + nums[i])
        retVal = True

        return retVal
```

</details>

## [134. Gas Station](https://leetcode.com/problems/gas-station/)

- [Official](https://leetcode.cn/problems/gas-station/solutions/488357/jia-you-zhan-by-leetcode-solution/)

<details><summary>Description</summary>

```text
There are n gas stations along a circular route, where the amount of gas at the ith station is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas
to travel from the ith station to its next (i + 1)th station.
You begin the journey with an empty tank at one of the gas stations.

Given two integer arrays gas and cost, return the starting gas station's index
if you can travel around the circuit once in the clockwise direction, otherwise return -1.
If there exists a solution, it is guaranteed to be unique

Example 1:
Input: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
Output: 3
Explanation:
Start at station 3 (index 3) and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 4. Your tank = 4 - 1 + 5 = 8
Travel to station 0. Your tank = 8 - 2 + 1 = 7
Travel to station 1. Your tank = 7 - 3 + 2 = 6
Travel to station 2. Your tank = 6 - 4 + 3 = 5
Travel to station 3. The cost is 5. Your gas is just enough to travel back to station 3.
Therefore, return 3 as the starting index.

Example 2:
Input: gas = [2,3,4], cost = [3,4,3]
Output: -1
Explanation:
You can't start at station 0 or 1, as there is not enough gas to travel to the next station.
Let's start at station 2 and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 0. Your tank = 4 - 3 + 2 = 3
Travel to station 1. Your tank = 3 - 3 + 3 = 3
You cannot travel back to station 2, as it requires 4 unit of gas but you only have 3.
Therefore, you can't travel around the circuit once no matter where you start.

Constraints:
n == gas.length == cost.length
1 <= n <= 10^5
0 <= gas[i], cost[i] <= 10^4
```

</details>

<details><summary>C</summary>

```c
int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize) {
    int retVal = -1;

    /* https://leetcode.cn/problems/gas-station/solutions/488498/shou-hua-tu-jie-liang-ge-guan-jian-jie-lun-de-jian/
     *  1. if sum(gas) < sum(cost), then it has no solution(-1).
     *  2. if sum(gas) >= sum(cost), then it has solution(i).
     *
     *      sum(gas) < sum(cost)     sum(gas) >= sum(cost)
     *     /                    \   /                     \
     *  [0]----------------------[i]-----------------------[n]
     */
    int tank = 0;
    int totalSum = 0;
    int start = 0;
    int i;
    for (i = 0; i < gasSize; ++i) {
        totalSum += (gas[i] - cost[i]);

        tank += (gas[i] - cost[i]);
        if (tank < 0) {
            start = i + 1;
            tank = 0;
        }
    }

    if (totalSum >= 0) {
        retVal = start;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int retVal = -1;

        int gasSize = gas.size();

        /* https://leetcode.cn/problems/gas-station/solutions/488498/shou-hua-tu-jie-liang-ge-guan-jian-jie-lun-de-jian/
         *  1. if sum(gas) < sum(cost), then it has no solution(-1).
         *  2. if sum(gas) >= sum(cost), then it has solution(i).
         *
         *      sum(gas) < sum(cost)     sum(gas) >= sum(cost)
         *     /                    \   /                     \
         *  [0]----------------------[i]-----------------------[n]
         */
        int tank = 0;
        int totalSum = 0;
        int start = 0;
        for (int i = 0; i < gasSize; ++i) {
            totalSum += (gas[i] - cost[i]);

            tank += (gas[i] - cost[i]);
            if (tank < 0) {
                start = i + 1;
                tank = 0;
            }
        }

        if (totalSum >= 0) {
            retVal = start;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def canCompleteCircuit(self, gas: List[int], cost: List[int]) -> int:
        retVal = -1

        gasSize = len(gas)

        # /* https://leetcode.cn/problems/gas-station/solutions/488498/shou-hua-tu-jie-liang-ge-guan-jian-jie-lun-de-jian/
        #  *  1. if sum(gas) < sum(cost), then it has no solution(-1).
        #  *  2. if sum(gas) >= sum(cost), then it has solution(i).
        #  *
        #  *      sum(gas) < sum(cost)     sum(gas) >= sum(cost)
        #  *     /                    \   /                     \
        #  *  [0]----------------------[i]-----------------------[n]
        #  */
        tank = 0
        totalSum = 0
        start = 0
        for i in range(gasSize):
            totalSum += (gas[i] - cost[i])
            tank += (gas[i] - cost[i])
            if tank < 0:
                start = i + 1
                tank = 0

        if totalSum >= 0:
            retVal = start

        return retVal
```

</details>

## [330. Patching Array](https://leetcode.com/problems/patching-array/)

- [Official](https://leetcode.cn/problems/patching-array/solutions/538939/an-yao-qiu-bu-qi-shu-zu-by-leetcode-solu-klp1/)

<details><summary>Description</summary>

```text
Given a sorted integer array nums and an integer n,
add/patch elements to the array such that any number in the range [1, n]
inclusive can be formed by the sum of some elements in the array.

Return the minimum number of patches required.

Example 1:
Input: nums = [1,3], n = 6
Output: 1
Explanation:
Combinations of nums are [1], [3], [1,3], which form possible sums of: 1, 3, 4.
Now if we add/patch 2 to nums, the combinations are: [1], [2], [3], [1,3], [2,3], [1,2,3].
Possible sums are 1, 2, 3, 4, 5, 6, which now covers the range [1, 6].
So we only need 1 patch.

Example 2:
Input: nums = [1,5,10], n = 20
Output: 2
Explanation: The two patches can be [2, 4].

Example 3:
Input: nums = [1,2,2], n = 5
Output: 0

Constraints:
1 <= nums.length <= 1000
1 <= nums[i] <= 10^4
nums is sorted in ascending order.
1 <= n <= 2^31 - 1
```

</details>

<details><summary>C</summary>

```c
int minPatches(int* nums, int numsSize, int n) {
    int retVal = 0;

    int index = 0;
    long x = 1;
    while (x <= n) {
        if ((index < numsSize) && (nums[index] <= x)) {
            x += nums[index];
            index += 1;
        } else {
            x <<= 1;
            retVal += 1;
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
    int minPatches(vector<int>& nums, int n) {
        int retVal = 0;

        int numsSize = nums.size();
        int index = 0;
        long x = 1;
        while (x <= n) {
            if ((index < numsSize) && (nums[index] <= x)) {
                x += nums[index];
                index += 1;
            } else {
                x <<= 1;
                retVal += 1;
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
    def minPatches(self, nums: List[int], n: int) -> int:
        retVal = 0

        numsSize = len(nums)
        index = 0
        x = 1
        while x <= n:
            if (index < numsSize) and (nums[index] <= x):
                x += nums[index]
                index += 1
            else:
                x <<= 1
                retVal += 1

        return retVal
```

</details>

## [334. Increasing Triplet Subsequence](https://leetcode.com/problems/increasing-triplet-subsequence/)

- [Official](https://leetcode.cn/problems/increasing-triplet-subsequence/solutions/1204375/di-zeng-de-san-yuan-zi-xu-lie-by-leetcod-dp2r/)

<details><summary>Description</summary>

```text
Given an integer array nums, return true if there exists a triple of indices (i, j, k)
such that i < j < k and nums[i] < nums[j] < nums[k]. If no such indices exists, return false.

Example 1:
Input: nums = [1,2,3,4,5]
Output: true
Explanation: Any triplet where i < j < k is valid.

Example 2:
Input: nums = [5,4,3,2,1]
Output: false
Explanation: No triplet exists.

Example 3:
Input: nums = [2,1,5,0,4,6]
Output: true
Explanation: The triplet (3, 4, 5) is valid because nums[3] == 0 < nums[4] == 4 < nums[5] == 6.

Constraints:
1 <= nums.length <= 5 * 10^5
-2^31 <= nums[i] <= 2^31 - 1

Follow up: Could you implement a solution that runs in O(n) time complexity and O(1) space complexity?
```

</details>

<details><summary>C</summary>

```c
bool increasingTriplet(int* nums, int numsSize) {
    bool retVal = false;

    int first = INT_MAX;
    int second = INT_MAX;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] <= first) {
            first = nums[i];
        } else if (nums[i] <= second) {
            second = nums[i];
        } else {
            retVal = true;
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
    bool increasingTriplet(vector<int>& nums) {
        bool retVal = false;

        int first = numeric_limits<int>::max();
        int second = numeric_limits<int>::max();
        for (int num : nums) {
            if (num <= first) {
                first = num;
            } else if (num <= second) {
                second = num;
            } else {
                retVal = true;
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
    def increasingTriplet(self, nums: List[int]) -> bool:
        retVal = False

        first = float('inf')
        second = float('inf')
        for num in nums:
            if num <= first:
                first = num
            elif num <= second:
                second = num
            else:
                retVal = True
                break

        return retVal
```

</details>

## [402. Remove K Digits](https://leetcode.com/problems/remove-k-digits/)

- [Official](https://leetcode.cn/problems/remove-k-digits/solutions/484940/yi-diao-kwei-shu-zi-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given string num representing a non-negative integer num, and an integer k,
return the smallest possible integer after removing k digits from num.

Example 1:
Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.

Example 2:
Input: num = "10200", k = 1
Output: "200"
Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.

Example 3:
Input: num = "10", k = 2
Output: "0"
Explanation: Remove all the digits from the number and it is left with nothing which is 0.

Constraints:
1 <= k <= num.length <= 10^5
num consists of only digits.
num does not have any leading zeros except for the zero itself.
```

</details>

<details><summary>C</summary>

```c
char* removeKdigits(char* num, int k) {
    char* pRetVal = NULL;

    int numSize = strlen(num);

    char numStack[numSize + 1];
    memset(numStack, 0, sizeof(numStack));
    int numStackTop = -1;
    int i;
    for (i = 0; i < numSize; ++i) {
        while ((k > 0) && (numStackTop != -1) && (numStack[numStackTop] > num[i])) {
            numStackTop--;
            k--;
        }
        numStack[++numStackTop] = num[i];
    }

    while (k > 0) {
        numStackTop--;
        k--;
    }

    pRetVal = (char*)malloc((numStackTop + 4) * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, ((numStackTop + 4) * sizeof(char)));

    int leadingZeros = 1;
    int idx = 0;
    for (i = 0; i <= numStackTop; ++i) {
        if ((leadingZeros == 1) && (numStack[i] == '0')) {
            continue;
        }
        leadingZeros = 0;
        pRetVal[idx++] = numStack[i];
    }
    if (idx == 0) {
        pRetVal[0] = '0';
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string removeKdigits(string num, int k) {
        string retVal = "";

        vector<char> numStack;
        for (auto c : num) {
            while ((k > 0) && (numStack.empty() == false) && (numStack.back() > c)) {
                numStack.pop_back();
                k--;
            }
            numStack.emplace_back(c);
        }

        while (k > 0) {
            numStack.pop_back();
            k--;
        }

        bool leadingZeros = true;
        for (auto c : numStack) {
            if ((leadingZeros == true) && (c == '0')) {
                continue;
            }
            leadingZeros = false;
            retVal += c;
        }
        if (retVal == "") {
            retVal = "0";
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def removeKdigits(self, num: str, k: int) -> str:
        retVal = ""

        numStack = []
        for digit in num:
            while k and numStack and numStack[-1] > digit:
                numStack.pop()
                k -= 1
            numStack.append(digit)

        if k > 0:
            numStack = numStack[:-k]

        retVal = "".join(numStack).lstrip('0') or "0"

        return retVal
```

</details>

## [435. Non-overlapping Intervals](https://leetcode.com/problems/non-overlapping-intervals/)

- [Official](https://leetcode.com/problems/non-overlapping-intervals/editorial/)
- [Official](https://leetcode.cn/problems/non-overlapping-intervals/solutions/541543/wu-zhong-die-qu-jian-by-leetcode-solutio-cpsb/)

<details><summary>Description</summary>

```text
Given an array of intervals intervals where intervals[i] = [starti, endi],
return the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.

Example 1:
Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
Output: 1
Explanation: [1,3] can be removed and the rest of the intervals are non-overlapping.

Example 2:
Input: intervals = [[1,2],[1,2],[1,2]]
Output: 2
Explanation: You need to remove two [1,2] to make the rest of the intervals non-overlapping.

Example 3:
Input: intervals = [[1,2],[2,3]]
Output: 0
Explanation: You don't need to remove any of the intervals since they're already non-overlapping.

Constraints:
1 <= intervals.length <= 10^5
intervals[i].length == 2
-5 * 10^4 <= starti < endi <= 5 * 10^4
```

</details>

<details><summary>C</summary>

```c
int compareIntArray(const void* a1, const void* a2) {
    const int* p1 = *(const int**)a1;
    const int* p2 = *(const int**)a2;

    // ascending order
    if (p1[1] == p2[1]) {
        return (p1[0] > p2[0]);
    }
    return (p1[1] > p2[1]);
}
int eraseOverlapIntervals(int** intervals, int intervalsSize, int* intervalsColSize) {
    int retVal = 0;

    qsort(intervals, intervalsSize, sizeof(int*), compareIntArray);

    int overlapping = INT_MIN;
    int start, end;
    int i;
    for (i = 0; i < intervalsSize; ++i) {
        start = intervals[i][0];
        end = intervals[i][1];

        if (start < overlapping) {
            ++retVal;
        } else {
            overlapping = end;
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
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        int retVal = 0;

        sort(intervals.begin(), intervals.end(), [&](const vector<int>& x, const vector<int>& y) {
            // ascending order
            if (x[1] == y[1]) {
                return (x[0] < y[0]);
            }
            return (x[1] < y[1]);
        });

        int overlapping = numeric_limits<int>::min();
        for (auto interval : intervals) {
            int start = interval[0];
            int end = interval[1];

            if (start < overlapping) {
                ++retVal;
            } else {
                overlapping = end;
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
    def eraseOverlapIntervals(self, intervals: List[List[int]]) -> int:
        retVal = 0

        overlapping = float('-inf')
        intervals.sort(key=lambda intervals: (intervals[1], intervals[0]))
        for start, end in intervals:
            if start < overlapping:
                retVal += 1
            else:
                overlapping = end

        return retVal
```

</details>

## [452. Minimum Number of Arrows to Burst Balloons](https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/)

- [Official](https://leetcode.cn/problems/minimum-number-of-arrows-to-burst-balloons/solutions/494515/yong-zui-shao-shu-liang-de-jian-yin-bao-qi-qiu-1-2/)

<details><summary>Description</summary>

```text
There are some spherical balloons taped onto a flat wall that represents the XY-plane.
The balloons are represented as a 2D integer array points where points[i] = [xstart, xend]
denotes a balloon whose horizontal diameter stretches between xstart and xend.
You do not know the exact y-coordinates of the balloons.

Arrows can be shot up directly vertically (in the positive y-direction) from different points along the x-axis.
A balloon with xstart and xend is burst by an arrow shot at x if xstart <= x <= xend.
There is no limit to the number of arrows that can be shot.
A shot arrow keeps traveling up infinitely, bursting any balloons in its path.

Given the array points, return the minimum number of arrows that must be shot to burst all balloons.

Example 1:
Input: points = [[10,16],[2,8],[1,6],[7,12]]
Output: 2
Explanation: The balloons can be burst by 2 arrows:
- Shoot an arrow at x = 6, bursting the balloons [2,8] and [1,6].
- Shoot an arrow at x = 11, bursting the balloons [10,16] and [7,12].

Example 2:
Input: points = [[1,2],[3,4],[5,6],[7,8]]
Output: 4
Explanation: One arrow needs to be shot for each balloon for a total of 4 arrows.

Example 3:
Input: points = [[1,2],[2,3],[3,4],[4,5]]
Output: 2
Explanation: The balloons can be burst by 2 arrows:
- Shoot an arrow at x = 2, bursting the balloons [1,2] and [2,3].
- Shoot an arrow at x = 4, bursting the balloons [3,4] and [4,5].

Constraints:
1 <= points.length <= 10^5
points[i].length == 2
-2^31 <= xstart < xend <= 2^31 - 1
```

</details>

<details><summary>C</summary>

```c
int compareIntArray(const void* a1, const void* a2) {
    const int* p1 = *(const int**)a1;
    const int* p2 = *(const int**)a2;

    // ascending order
    if (p1[1] == p2[1]) {
        return (p1[0] > p2[0]);
    }
    return (p1[1] > p2[1]);
}
int findMinArrowShots(int** points, int pointsSize, int* pointsColSize) {
    int retVal = 0;

    qsort(points, pointsSize, sizeof(points[0]), compareIntArray);

    int arrow = points[0][1];
    ++retVal;
    int start, end;
    int i;
    for (i = 1; i < pointsSize; ++i) {
        start = points[i][0];
        end = points[i][1];
        if (start > arrow) {
            arrow = end;
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
    int findMinArrowShots(vector<vector<int>>& points) {
        int retVal = 0;

        sort(points.begin(), points.end(), [&](const vector<int>& x, const vector<int>& y) {
            // ascending order
            if (x[1] == y[1]) {
                return (x[0] < y[0]);
            }
            return (x[1] < y[1]);
        });

        int pointsSize = points.size();
        int arrow = points[0][1];
        ++retVal;
        for (int i = 1; i < pointsSize; ++i) {
            int start = points[i][0];
            int end = points[i][1];
            if (start > arrow) {
                ++retVal;
                arrow = end;
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
    def findMinArrowShots(self, points: List[List[int]]) -> int:
        retVal = 0

        points.sort(key=lambda points: (points[1], points[0]))

        arrow = float('-inf')
        for start, end in points:
            if start > arrow:
                retVal += 1
                arrow = end

        return retVal
```

</details>

## [455. Assign Cookies](https://leetcode.com/problems/assign-cookies/)

- [Official](https://leetcode.com/problems/assign-cookies/editorial/)
- [Official](https://leetcode.cn/problems/assign-cookies/solutions/534281/fen-fa-bing-gan-by-leetcode-solution-50se/)

<details><summary>Description</summary>

```text
Assume you are an awesome parent and want to give your children some cookies.
But, you should give each child at most one cookie.

Each child i has a greed factor g[i],
which is the minimum size of a cookie that the child will be content with; and each cookie j has a size s[j].
If s[j] >= g[i], we can assign the cookie j to the child i, and the child i will be content.
Your goal is to maximize the number of your content children and output the maximum number.

Example 1:
Input: g = [1,2,3], s = [1,1]
Output: 1
Explanation: You have 3 children and 2 cookies. The greed factors of 3 children are 1, 2, 3.
And even though you have 2 cookies, since their size is both 1,
you could only make the child whose greed factor is 1 content.
You need to output 1.

Example 2:
Input: g = [1,2], s = [1,2,3]
Output: 2
Explanation: You have 2 children and 3 cookies. The greed factors of 2 children are 1, 2.
You have 3 cookies and their sizes are big enough to gratify all of the children,
You need to output 2.

Constraints:
1 <= g.length <= 3 * 10^4
0 <= s.length <= 3 * 10^4
1 <= g[i], s[j] <= 2^31 - 1
```

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int findContentChildren(int* g, int gSize, int* s, int sSize) {
    int retVal = 0;

    qsort(g, gSize, sizeof(int), compareInteger);
    int gIdx = 0;

    qsort(s, sSize, sizeof(int), compareInteger);
    int sIdx = 0;

    while ((gIdx < gSize) && (sIdx < sSize)) {
        if (g[gIdx] <= s[sIdx]) {
            ++gIdx;
            ++retVal;
        }
        ++sIdx;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        int retVal = 0;

        int gSize = g.size();
        sort(g.begin(), g.end());
        int gIdx = 0;

        int sSize = s.size();
        sort(s.begin(), s.end());
        int sIdx = 0;

        while ((gIdx < gSize) && (sIdx < sSize)) {
            if (g[gIdx] <= s[sIdx]) {
                ++gIdx;
                ++retVal;
            }
            ++sIdx;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def findContentChildren(self, g: List[int], s: List[int]) -> int:
        retVal = 0

        gSize = len(g)
        g.sort()
        gIdx = 0

        sSize = len(s)
        s.sort()
        sIdx = 0

        while gIdx < gSize and sIdx < sSize:
            if g[gIdx] <= s[sIdx]:
                gIdx += 1
                retVal += 1
            sIdx += 1

        return retVal
```

</details>

## [605. Can Place Flowers](https://leetcode.com/problems/can-place-flowers/)

- [Official](https://leetcode.cn/problems/can-place-flowers/solutions/542556/chong-hua-wen-ti-by-leetcode-solution-sojr/)

<details><summary>Description</summary>

```text
You have a long flowerbed in which some of the plots are planted, and some are not.
However, flowers cannot be planted in adjacent plots.

Given an integer array flowerbed containing 0's and 1's, where 0 means empty and 1 means not empty, and an integer n,
return if n new flowers can be planted in the flowerbed without violating the no-adjacent-flowers rule.

Example 1:
Input: flowerbed = [1,0,0,0,1], n = 1
Output: true

Example 2:
Input: flowerbed = [1,0,0,0,1], n = 2
Output: false

Constraints:
1 <= flowerbed.length <= 2 * 10^4
flowerbed[i] is 0 or 1.
There are no two adjacent flowers in flowerbed.
0 <= n <= flowerbed.length
```

</details>

<details><summary>C</summary>

```c
bool canPlaceFlowers(int *flowerbed, int flowerbedSize, int n) {
    bool retVal = false;

    int i;
    for (i = 0; i < flowerbedSize; ++i) {
        if (flowerbed[i] == 1) {
            continue;
        }

        if (i == 0) {
            if ((flowerbedSize == 1) || (flowerbed[i + 1] == 0)) {
                --n;
                flowerbed[i] = 1;
            }
        } else if (i == flowerbedSize - 1) {
            if (flowerbed[i - 1] == 0) {
                --n;
                flowerbed[i] = 1;
            }
        } else {
            if ((flowerbed[i - 1] == 0) && (flowerbed[i + 1] == 0)) {
                --n;
                flowerbed[i] = 1;
            }
        }
    }
    if (n <= 0) {
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
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        bool retVal = false;

        int flowerbedSize = flowerbed.size();
        for (int i = 0; i < flowerbedSize; ++i) {
            if (flowerbed[i] == 1) {
                continue;
            }

            if (i == 0) {
                if ((flowerbedSize == 1) || (flowerbed[i + 1] == 0)) {
                    --n;
                    flowerbed[i] = 1;
                }
            } else if (i == flowerbedSize - 1) {
                if (flowerbed[i - 1] == 0) {
                    --n;
                    flowerbed[i] = 1;
                }
            } else {
                if ((flowerbed[i - 1] == 0) && (flowerbed[i + 1] == 0)) {
                    --n;
                    flowerbed[i] = 1;
                }
            }
        }
        if (n <= 0) {
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
    def canPlaceFlowers(self, flowerbed: List[int], n: int) -> bool:
        retVal = False

        flowerbedSize = len(flowerbed)
        for i in range(flowerbedSize):
            if flowerbed[i] == 1:
                continue

            if i == 0:
                if flowerbedSize == 1 or flowerbed[i+1] == 0:
                    n -= 1
                    flowerbed[i] = 1
            elif i == flowerbedSize - 1:
                if flowerbed[i-1] == 0:
                    n -= 1
                    flowerbed[i] = 1
            else:
                if flowerbed[i-1] == 0 and flowerbed[i+1] == 0:
                    n -= 1
                    flowerbed[i] = 1
        if n <= 0:
            retVal = True

        return retVal
```

</details>

## [624. Maximum Distance in Arrays](https://leetcode.com/problems/maximum-distance-in-arrays/)

- [Official](https://leetcode.cn/problems/maximum-distance-in-arrays/solutions/2393060/shu-zu-lie-biao-zhong-de-zui-da-ju-chi-b-f9x4/)

<details><summary>Description</summary>

```text
You are given m arrays, where each array is sorted in ascending order.

You can pick up two integers from two different arrays (each array picks one) and calculate the distance.
We define the distance between two integers a and b to be their absolute difference |a - b|.

Return the maximum distance.

Example 1:
Input: arrays = [[1,2,3],[4,5],[1,2,3]]
Output: 4
Explanation: One way to reach the maximum distance 4 is to
pick 1 in the first or third array and pick 5 in the second array.

Example 2:
Input: arrays = [[1],[1]]
Output: 0

Constraints:
m == arrays.length
2 <= m <= 10^5
1 <= arrays[i].length <= 500
-10^4 <= arrays[i][j] <= 10^4
arrays[i] is sorted in ascending order.
There will be at most 10^5 integers in all the arrays.
```

</details>

<details><summary>C</summary>

```c
int maxDistance(int** arrays, int arraysSize, int* arraysColSize) {
    int retVal = 0;

    int minValue = arrays[0][0];
    int maxValue = arrays[0][arraysColSize[0] - 1];
    int diff1, diff2;
    int i;
    for (i = 1; i < arraysSize; ++i) {
        diff1 = abs(arrays[i][arraysColSize[i] - 1] - minValue);
        diff2 = abs(maxValue - arrays[i][0]);
        retVal = fmax(retVal, fmax(diff1, diff2));

        minValue = fmin(minValue, arrays[i][0]);
        maxValue = fmax(maxValue, arrays[i][arraysColSize[i] - 1]);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxDistance(vector<vector<int>>& arrays) {
        int retVal = 0;

        int arraysSize = arrays.size();

        int arraysColSize = arrays[0].size();
        int minValue = arrays[0][0];
        int maxValue = arrays[0][arraysColSize - 1];
        for (int i = 1; i < arraysSize; ++i) {
            arraysColSize = arrays[i].size();
            int diff1 = abs(arrays[i][arraysColSize - 1] - minValue);
            int diff2 = abs(maxValue - arrays[i][0]);
            retVal = max(retVal, max(diff1, diff2));

            minValue = min(minValue, arrays[i][0]);
            maxValue = max(maxValue, arrays[i][arraysColSize - 1]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxDistance(self, arrays: List[List[int]]) -> int:
        retVal = 0

        arraysSize = len(arrays)

        minValue = arrays[0][0]
        maxValue = arrays[0][-1]
        for i in range(1, arraysSize):
            diff1 = abs(arrays[i][-1] - minValue)
            diff2 = abs(maxValue - arrays[i][0])
            retVal = max(retVal, diff1, diff2)

            minValue = min(minValue, arrays[i][0])
            maxValue = max(maxValue, arrays[i][-1])

        return retVal
```

</details>

## [646. Maximum Length of Pair Chain](https://leetcode.com/problems/maximum-length-of-pair-chain/)

- [Official](https://leetcode.com/problems/maximum-length-of-pair-chain/editorial/)
- [Official](https://leetcode.cn/problems/maximum-length-of-pair-chain/solutions/1793617/zui-chang-shu-dui-lian-by-leetcode-solut-ifpn/)

<details><summary>Description</summary>

```text
You are given an array of n pairs pairs where pairs[i] = [lefti, righti] and lefti < righti.

A pair p2 = [c, d] follows a pair p1 = [a, b] if b < c. A chain of pairs can be formed in this fashion.

Return the length longest chain which can be formed.

You do not need to use up all the given intervals. You can select pairs in any order.

Example 1:
Input: pairs = [[1,2],[2,3],[3,4]]
Output: 2
Explanation: The longest chain is [1,2] -> [3,4].

Example 2:
Input: pairs = [[1,2],[7,8],[4,5]]
Output: 3
Explanation: The longest chain is [1,2] -> [4,5] -> [7,8].

Constraints:
n == pairs.length
1 <= n <= 1000
-1000 <= lefti < righti <= 1000
```

</details>

<details><summary>C</summary>

```c
#define GREEDY (1)
#define DYNAMIC_PROGRAMMING (1)
int compareIntArray(const void* a1, const void* a2) {
    const int* p1 = *(const int**)a1;
    const int* p2 = *(const int**)a2;

    // ascending order
#if (GREEDY)
    if (p1[1] == p2[1]) {
        return (p1[0] > p2[0]);
    }
    return (p1[1] > p2[1]);
#elif (DYNAMIC_PROGRAMMING)
    if (p1[0] == p2[0]) {
        return (p1[1] > p2[1]);
    }
    return (p1[0] > p2[0]);
#endif
}
int findLongestChain(int** pairs, int pairsSize, int* pairsColSize) {
    int retVal = 0;

#if (GREEDY)
    printf("Greedy\n");

    qsort(pairs, pairsSize, sizeof(int*), compareIntArray);

    int preRight = -1001;  // -1000 <= lefti < righti <= 1000
    int left, right;
    int i;
    for (i = 0; i < pairsSize; ++i) {
        left = pairs[i][0];
        right = pairs[i][1];

        if (left > preRight) {
            ++retVal;
            preRight = right;
        }
    }
#elif (DYNAMIC_PROGRAMMING)
    printf("Dynamic Programming\n");

    qsort(pairs, pairsSize, sizeof(int*), compareIntArray);

    // dp[i] will store the length of the longest chain starting from pair i
    int dp[pairsSize];
    memset(dp, 0, sizeof(dp));

    int preRight, left;
    int i, j;
    for (i = 0; i < pairsSize; ++i) {
        dp[i] = 1;
    }
    for (i = pairsSize - 1; i >= 0; --i) {
        preRight = pairs[i][1];
        for (j = i + 1; j < pairsSize; ++j) {
            left = pairs[j][0];
            if (preRight < left) {
                dp[i] = fmax(dp[i], dp[j] + 1);
            }
        }
        retVal = fmax(retVal, dp[i]);
    }

#endif

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define GREEDY (1)
#define DYNAMIC_PROGRAMMING (1)
   public:
    Solution() {
#if (GREEDY)
        cout << "Greedy\n\n";
#elif (DYNAMIC_PROGRAMMING)
        cout << "Dynamic Programming\n\n";
#endif
    }
    int findLongestChain(vector<vector<int>>& pairs) {
        int retVal = 0;

#if (GREEDY)
        sort(pairs.begin(), pairs.end(), [&](const vector<int>& x, const vector<int>& y) {
            // ascending order
            if (x[1] == y[1]) {
                return (x[0] < y[0]);
            }
            return (x[1] < y[1]);
        });

        int preRight = -1001;  // -1000 <= lefti < righti <= 1000
        for (auto pair : pairs) {
            int left = pair[0];
            int right = pair[1];

            if (left > preRight) {
                ++retVal;
                preRight = right;
            }
        }
#elif (DYNAMIC_PROGRAMMING)
        sort(pairs.begin(), pairs.end());

        // dp[i] will store the length of the longest chain starting from pair i
        int pairsSize = pairs.size();
        vector<int> dp(pairsSize, 1);
        for (int i = pairsSize - 1; i >= 0; --i) {
            int preRight = pairs[i][1];
            for (int j = i + 1; j < pairsSize; ++j) {
                int left = pairs[j][0];
                if (preRight < left) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            retVal = max(retVal, dp[i]);
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
        self.method = 1

        if self.method == 1:
            print("Greedy")
        elif self.method == 2:
            print("Dynamic Programming")
        print()

    def findLongestChain(self, pairs: List[List[int]]) -> int:
        retVal = 0

        if self.method == 1:
            pairs.sort(key=lambda right: right[1])

            preRight = -1001    # -1000 <= lefti < righti <= 1000
            for left, right in pairs:
                if left > preRight:
                    retVal += 1
                    preRight = right
        elif self.method == 2:
            pairs.sort()

            # dp[i] will store the length of the longest chain starting from pair i
            pairsSize = len(pairs)
            dp = [1] * pairsSize
            for i in range(pairsSize - 1, -1, -1):
                preRight = pairs[i][1]
                for j in range(i + 1, pairsSize):
                    left = pairs[j][0]
                    if preRight < left:
                        dp[i] = max(dp[i], dp[j] + 1)
                retVal = max(retVal, dp[i])

        return retVal
```

</details>

## [649. Dota2 Senate](https://leetcode.com/problems/dota2-senate/)

- [Official](https://leetcode.cn/problems/dota2-senate/solutions/517088/dota2-can-yi-yuan-by-leetcode-solution-jb7l/)

<details><summary>Description</summary>

```text
In the world of Dota2, there are two parties: the Radiant and the Dire.

The Dota2 senate consists of senators coming from two parties.
Now the Senate wants to decide on a change in the Dota2 game.
The voting for this change is a round-based procedure.
In each round, each senator can exercise one of the two rights:
- Ban one senator's right: A senator can make another senator lose all his rights in this and all the following rounds.
- Announce the victory: If this senator found the senators who still have rights to vote are all from the same party,
  he can announce the victory and decide on the change in the game.

Given a string senate representing each senator's party belonging.
The character 'R' and 'D' represent the Radiant party and the Dire party.
Then if there are n senators, the size of the given string will be n.

The round-based procedure starts from the first senator to the last senator in the given order.
This procedure will last until the end of voting.
All the senators who have lost their rights will be skipped during the procedure.

Suppose every senator is smart enough and will play the best strategy for his own party.
Predict which party will finally announce the victory and change the Dota2 game.
The output should be "Radiant" or "Dire".

Example 1:
Input: senate = "RD"
Output: "Radiant"
Explanation:
The first senator comes from Radiant and he can just ban the next senator's right in round 1.
And the second senator can't exercise any rights anymore since his right has been banned.
And in round 2, the first senator can just announce the victory since he is the only guy in the senate who can vote.

Example 2:
Input: senate = "RDD"
Output: "Dire"
Explanation:
The first senator comes from Radiant and he can just ban the next senator's right in round 1.
And the second senator can't exercise any rights anymore since his right has been banned.
And the third senator comes from Dire and he can ban the first senator's right in round 1.
And in round 2, the third senator can just announce the victory since he is the only guy in the senate who can vote.

Constraints:
n == senate.length
1 <= n <= 10^4
senate[i] is either 'R' or 'D'.
```

</details>

<details><summary>C</summary>

```c
char* predictPartyVictory(char* senate) {
    char* pRetVal = NULL;

#define MAX_RETURN_SIZE (8)
    pRetVal = (char*)malloc(MAX_RETURN_SIZE * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (MAX_RETURN_SIZE * sizeof(char)));

    int senateSize = strlen(senate);
    int queueRadiant[senateSize];
    memset(queueRadiant, 0, sizeof(queueRadiant));
    int queueRadiantHead = 0;
    int queueRadiantTail = 0;
    int queueDire[senateSize];
    memset(queueDire, 0, sizeof(queueDire));
    int queueDireHead = 0;
    int queueDireTail = 0;

    int i;
    for (i = 0; i < senateSize; ++i) {
        if (senate[i] == 'R') {
            queueRadiant[queueRadiantHead++] = i;
        } else if (senate[i] == 'D') {
            queueDire[queueDireHead++] = i;
        }
    }

    int queueRadiantIdx, queueDireIdx;
    while ((queueRadiantHead > queueRadiantTail) && (queueDireHead > queueDireTail)) {
        queueRadiantIdx = queueRadiant[queueRadiantTail];
        queueDireIdx = queueDire[queueDireTail];

        if (queueRadiantIdx < queueDireIdx) {
            queueRadiant[queueRadiantHead++] = queueRadiantIdx + senateSize;
        } else if (queueRadiantIdx > queueDireIdx) {
            queueDire[queueDireHead++] = queueDireIdx + senateSize;
        }

        ++queueRadiantTail;
        ++queueDireTail;
    }

    if (queueRadiantHead > queueRadiantTail) {
        snprintf(pRetVal, (MAX_RETURN_SIZE * sizeof(char)), "%s", "Radiant");
    } else if (queueDireHead > queueDireTail) {
        snprintf(pRetVal, (MAX_RETURN_SIZE * sizeof(char)), "%s", "Dire");
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string predictPartyVictory(string senate) {
        string retVal;

        queue<int> queueRadiant;
        queue<int> queueDire;

        int senateSize = senate.size();
        for (int i = 0; i < senateSize; ++i) {
            if (senate[i] == 'R') {
                queueRadiant.push(i);
            } else if (senate[i] == 'D') {
                queueDire.push(i);
            }
        }

        while ((queueRadiant.empty() == false) && (queueDire.empty() == false)) {
            auto idxRadiant = queueRadiant.front();
            auto idxDire = queueDire.front();

            if (idxRadiant < idxDire) {
                queueRadiant.push(idxRadiant + senateSize);
            } else if (idxRadiant > idxDire) {
                queueDire.push(idxDire + senateSize);
            }

            queueRadiant.pop();
            queueDire.pop();
        }

        if (queueRadiant.empty() == false) {
            retVal = "Radiant";
        } else if (queueDire.empty() == false) {
            retVal = "Dire";
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def predictPartyVictory(self, senate: str) -> str:
        retVal = ""

        queueRadiant = deque()
        queueDire = deque()

        senateSize = len(senate)
        for i in range(senateSize):
            if senate[i] == 'R':
                queueRadiant.append(i)
            elif senate[i] == 'D':
                queueDire.append(i)

        while queueRadiant and queueDire:
            idxRadiant = queueRadiant.popleft()
            idxDire = queueDire.popleft()
            if idxRadiant < idxDire:
                queueRadiant.append(idxRadiant + senateSize)
            elif idxRadiant > idxDire:
                queueDire.append(idxDire + senateSize)

        if queueRadiant:
            retVal = "Radiant"
        elif queueDire:
            retVal = "Dire"

        return retVal
```

</details>

## [670. Maximum Swap](https://leetcode.com/problems/maximum-swap/)

- [Official](https://leetcode.com/problems/maximum-swap/editorial/)
- [Official](https://leetcode.cn/problems/maximum-swap/solutions/1818457/zui-da-jiao-huan-by-leetcode-solution-lnd5/)

<details><summary>Description</summary>

```text
You are given an integer num. You can swap two digits at most once to get the maximum valued number.

Return the maximum valued number you can get.

Example 1:
Input: num = 2736
Output: 7236
Explanation: Swap the number 2 and the number 7.

Example 2:
Input: num = 9973
Output: 9973
Explanation: No swap.

Constraints:
0 <= num <= 10^8
```

</details>

<details><summary>C</summary>

```c
int maximumSwap(int num) {
    int retVal = 0;

    char numStr[32];
    memset(numStr, 0, sizeof(numStr));
    snprintf(numStr, sizeof(numStr), "%d", num);
    int numStrSize = strlen(numStr);

    int maxDigitIndex = -1;
    int swapIdx1 = -1;
    int swapIdx2 = -1;
    int i;
    for (i = numStrSize - 1; i >= 0; --i) {
        if ((maxDigitIndex == -1) || (numStr[i] > numStr[maxDigitIndex])) {
            maxDigitIndex = i;
        } else if (numStr[i] < numStr[maxDigitIndex]) {
            swapIdx1 = i;
            swapIdx2 = maxDigitIndex;
        }
    }

    int tmp;
    if ((swapIdx1 != -1) && (swapIdx2 != -1)) {
        tmp = numStr[swapIdx1];
        numStr[swapIdx1] = numStr[swapIdx2];
        numStr[swapIdx2] = tmp;
    }
    retVal = atoi(numStr);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maximumSwap(int num) {
        int retVal = 0;

        string numStr = to_string(num);
        int numStrSize = numStr.size();
        int maxDigitIndex = -1;
        int swapIdx1 = -1;
        int swapIdx2 = -1;
        for (int i = numStrSize - 1; i >= 0; --i) {
            if ((maxDigitIndex == -1) || (numStr[i] > numStr[maxDigitIndex])) {
                maxDigitIndex = i;
            } else if (numStr[i] < numStr[maxDigitIndex]) {
                swapIdx1 = i;
                swapIdx2 = maxDigitIndex;
            }
        }

        if ((swapIdx1 != -1) && (swapIdx2 != -1)) {
            swap(numStr[swapIdx1], numStr[swapIdx2]);
        }
        retVal = stoi(numStr);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maximumSwap(self, num: int) -> int:
        retVal = 0

        numStr = list(str(num))
        numStrSize = len(numStr)
        maxDigitIndex = -1
        swapIdx1 = -1
        swapIdx2 = -1
        for i in range(numStrSize - 1, -1, -1):
            if maxDigitIndex == -1 or numStr[i] > numStr[maxDigitIndex]:
                maxDigitIndex = i
            elif numStr[i] < numStr[maxDigitIndex]:
                swapIdx1 = i
                swapIdx2 = maxDigitIndex

        if swapIdx1 != -1 and swapIdx2 != -1:
            numStr[swapIdx1], numStr[swapIdx2] = numStr[swapIdx2], numStr[swapIdx1]

        retVal = int("".join(numStr))

        return retVal
```

</details>

## [678. Valid Parenthesis String](https://leetcode.com/problems/valid-parenthesis-string/)

- [Official](https://leetcode.com/problems/valid-parenthesis-string/editorial/)
- [Official](https://leetcode.cn/problems/valid-parenthesis-string/solutions/992347/you-xiao-de-gua-hao-zi-fu-chuan-by-leetc-osi3/)

<details><summary>Description</summary>

```text
Given a string s containing only three types of characters: '(', ')' and '*', return true if s is valid.

The following rules define a valid string:
- Any left parenthesis '(' must have a corresponding right parenthesis ')'.
- Any right parenthesis ')' must have a corresponding left parenthesis '('.
- Left parenthesis '(' must go before the corresponding right parenthesis ')'.
- '*' could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an empty string "".

Example 1:
Input: s = "()"
Output: true

Example 2:
Input: s = "(*)"
Output: true

Example 3:
Input: s = "(*))"
Output: true

Constraints:
1 <= s.length <= 100
s[i] is '(', ')' or '*'.
```

</details>

<details><summary>C</summary>

```c
bool checkValidString(char* s) {
    bool retVal = false;

    int sSize = strlen(s);
    int leftParenthesis = 0;
    int rightParenthesis = 0;
    int left, right;
    for (left = 0; left < sSize; ++left) {
        if ((s[left] == '(') || (s[left] == '*')) {
            leftParenthesis++;
        } else if (s[left] == ')') {
            leftParenthesis--;
        }

        right = sSize - 1 - left;
        if ((s[right] == ')') || (s[right] == '*')) {
            rightParenthesis++;
        } else if (s[right] == '(') {
            rightParenthesis--;
        }

        if ((leftParenthesis < 0) || (rightParenthesis < 0)) {
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
    bool checkValidString(string s) {
        bool retVal = false;

        int sSize = s.size();
        int leftParenthesis = 0;
        int rightParenthesis = 0;
        for (int left = 0; left < sSize; ++left) {
            if ((s[left] == '(') || (s[left] == '*')) {
                leftParenthesis++;
            } else if (s[left] == ')') {
                leftParenthesis--;
            }

            int right = sSize - 1 - left;
            if ((s[right] == ')') || (s[right] == '*')) {
                rightParenthesis++;
            } else if (s[right] == '(') {
                rightParenthesis--;
            }

            if ((leftParenthesis < 0) || (rightParenthesis < 0)) {
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
    def checkValidString(self, s: str) -> bool:
        retVal = False

        sSize = len(s)

        leftParenthesis = 0
        rightParenthesis = 0
        for left in range(sSize):
            if (s[left] == '(') or (s[left] == '*'):
                leftParenthesis += 1
            elif s[left] == ')':
                leftParenthesis -= 1

            right = sSize - 1 - left
            if (s[right] == ')') or (s[right] == '*'):
                rightParenthesis += 1
            elif s[right] == '(':
                rightParenthesis -= 1

            if (leftParenthesis < 0) or (rightParenthesis < 0):
                return retVal

        retVal = True

        return retVal
```

</details>

## [763. Partition Labels](https://leetcode.com/problems/partition-labels/)  1443

- [Official](https://leetcode.com/problems/partition-labels/editorial/)
- [Official](https://leetcode.cn/problems/partition-labels/solutions/455703/hua-fen-zi-mu-qu-jian-by-leetcode-solution/)

<details><summary>Description</summary>

```text
You are given a string s.
We want to partition the string into as many parts as possible so that each letter appears in at most one part.

Note that the partition is done so that after concatenating all the parts in order, the resultant string should be s.

Return a list of integers representing the size of these parts.

Example 1:
Input: s = "ababcbacadefegdehijhklij"
Output: [9,7,8]
Explanation:
The partition is "ababcbaca", "defegde", "hijhklij".
This is a partition so that each letter appears in at most one part.
A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits s into less parts.

Example 2:
Input: s = "eccbbbbdec"
Output: [10]

Constraints:
1 <= s.length <= 500
s consists of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Try to greedily choose the smallest partition that includes the first letter.
   If you have something like "abaccbdeffed", then you might need to add b.
   You can use an map like "last['b'] = 5" to help you expand the width of your partition.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MAX_LETTERS (26)  // s consists of lowercase English letters.
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *partitionLabels(char *s, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;

    int sSize = strlen(s);
    pRetVal = (int *)calloc(sSize, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }
    int i;

    int last[MAX_LETTERS];
    memset(last, 0, sizeof(last));
    for (i = 0; i < sSize; ++i) {
        last[s[i] - 'a'] = i;
    }

    int start = 0;
    int end = 0;
    for (i = 0; i < sSize; ++i) {
        end = fmax(end, last[s[i] - 'a']);
        if (i == end) {
            pRetVal[(*returnSize)++] = i - start + 1;
            start = i + 1;
        }
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    int letters = 26;  // s consists of lowercase English letters.

   public:
    vector<int> partitionLabels(string s) {
        vector<int> retVal;

        vector<int> last(letters, 0);
        int sSize = s.size();
        for (int i = 0; i < sSize; ++i) {
            last[s[i] - 'a'] = i;
        }

        int start = 0;
        int end = 0;
        for (int i = 0; i < sSize; ++i) {
            end = max(end, last[s[i] - 'a']);
            if (i == end) {
                retVal.emplace_back(i - start + 1);
                start = i + 1;
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
        self.lowercase = 26  # s consists of lowercase English letters.

    def partitionLabels(self, s: str) -> List[int]:
        retVal = []

        last = [0] * self.lowercase
        for idx, ch in enumerate(s):
            last[ord(ch)-ord('a')] = idx

        start = 0
        end = 0
        for idx, ch in enumerate(s):
            end = max(end, last[ord(ch)-ord('a')])
            if idx == end:
                retVal.append(idx - start + 1)
                start = idx + 1

        return retVal
```

</details>

## [769. Max Chunks To Make Sorted](https://leetcode.com/problems/max-chunks-to-make-sorted/)  1566

- [Official](https://leetcode.com/problems/max-chunks-to-make-sorted/editorial/)
- [Official](https://leetcode.cn/problems/max-chunks-to-make-sorted/solutions/1886333/zui-duo-neng-wan-cheng-pai-xu-de-kuai-by-gc4k/)

<details><summary>Description</summary>

```text
You are given an integer array arr of length n that represents a permutation of the integers in the range [0, n - 1].

We split arr into some number of chunks (i.e., partitions), and individually sort each chunk.
After concatenating them, the result should equal the sorted array.

Return the largest number of chunks we can make to sort the array.

Example 1:
Input: arr = [4,3,2,1,0]
Output: 1
Explanation:
Splitting into two or more chunks will not return the required result.
For example, splitting into [4, 3], [2, 1, 0] will result in [3, 4, 0, 1, 2], which isn't sorted.

Example 2:
Input: arr = [1,0,2,3,4]
Output: 4
Explanation:
We can split into two chunks, such as [1, 0], [2, 3, 4].
However, splitting into [1, 0], [2], [3], [4] is the highest number of chunks possible.

Constraints:
n == arr.length
1 <= n <= 10
0 <= arr[i] < n
All the elements of arr are unique.
```

<details><summary>Hint</summary>

```text
1. The first chunk can be found as the smallest k for which A[:k+1] == [0, 1, 2, ...k]; then we repeat this process.
```

</details>

</details>

<details><summary>C</summary>

```c
int maxChunksToSorted(int* arr, int arrSize) {
    int retVal = 0;

    int maxElement = 0;
    int i;
    for (i = 0; i < arrSize; i++) {
        maxElement = fmax(maxElement, arr[i]);
        // All values in range [0, i] belong to the prefix arr[0:i]; a new chunk can be formed
        if (maxElement == i) {
            retVal++;
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
    int maxChunksToSorted(vector<int>& arr) {
        int retVal = 0;

        int arrSize = arr.size();
        int maxElement = 0;
        for (int i = 0; i < arrSize; i++) {
            maxElement = max(maxElement, arr[i]);
            // All values in range [0, i] belong to the prefix arr[0:i]; a new chunk can be formed
            if (maxElement == i) {
                retVal++;
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
    def maxChunksToSorted(self, arr: List[int]) -> int:
        retVal = 0

        arrSize = len(arr)
        maxElement = 0
        for i in range(arrSize):
            maxElement = max(maxElement, arr[i])
            # All values in range [0, i] belong to the prefix arr[0:i]; a chunk can be formed
            if maxElement == i:
                retVal += 1

        return retVal
```

</details>

## [781. Rabbits in Forest](https://leetcode.com/problems/rabbits-in-forest/)  1453

- [Official](https://leetcode.cn/problems/rabbits-in-forest/solutions/698444/sen-lin-zhong-de-tu-zi-by-leetcode-solut-kvla/)

<details><summary>Description</summary>

```text
There is a forest with an unknown number of rabbits.
We asked n rabbits "How many rabbits have the same color as you?" and collected the answers in an integer array answers
where answers[i] is the answer of the ith rabbit.

Given the array answers, return the minimum number of rabbits that could be in the forest.

Example 1:
Input: answers = [1,1,2]
Output: 5
Explanation:
The two rabbits that answered "1" could both be the same color, say red.
The rabbit that answered "2" can't be red or the answers would be inconsistent.
Say the rabbit that answered "2" was blue.
Then there should be 2 other blue rabbits in the forest that didn't answer into the array.
The smallest possible number of rabbits in the forest is therefore 5: 3 that answered plus 2 that didn't.

Example 2:
Input: answers = [10,10,10]
Output: 11

Constraints:
1 <= answers.length <= 1000
0 <= answers[i] < 1000
```

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
int numRabbits(int *answers, int answersSize) {
    int retVal = 0;

    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    for (int i = 0; i < answersSize; i++) {
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &answers[i], pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                return retVal;
            }
            pTemp->key = answers[i];
            pTemp->value = 1;
            HASH_ADD_INT(pHashTable, key, pTemp);
        } else {
            pTemp->value++;
        }
    }

    pTemp = NULL;
    struct hashTable *pCurrent;
    HASH_ITER(hh, pHashTable, pCurrent, pTemp) {
        retVal += ((pCurrent->value + pCurrent->key) / (pCurrent->key + 1) * (pCurrent->key + 1));
        HASH_DEL(pHashTable, pCurrent);
        free(pCurrent);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int numRabbits(vector<int>& answers) {
        int retVal = 0;

        unordered_map<int, int> hashTable;
        for (int answer : answers) {
            ++hashTable[answer];
        }

        for (auto& [answer, count] : hashTable) {
            retVal += ((count + answer) / (answer + 1) * (answer + 1));
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def numRabbits(self, answers: List[int]) -> int:
        retVal = 0

        hashTable = Counter(answers)
        retVal = sum((count + answer) // (answer + 1) * (answer + 1) for answer, count in hashTable.items())

        return retVal
```

</details>

## [826. Most Profit Assigning Work](https://leetcode.com/problems/most-profit-assigning-work/)  1708

- [Official](https://leetcode.cn/problems/most-profit-assigning-work/solutions/22424/an-pai-gong-zuo-yi-da-dao-zui-da-shou-yi-by-leetco/)

<details><summary>Description</summary>

```text
You have n jobs and m workers. You are given three arrays: difficulty, profit, and worker where:

difficulty[i] and profit[i] are the difficulty and the profit of the ith job, and
worker[j] is the ability of jth worker (i.e., the jth worker can only complete a job with difficulty at most worker[j]).
Every worker can be assigned at most one job, but one job can be completed multiple times.

For example, if three workers attempt the same job that pays $1, then the total profit will be $3.
If a worker cannot complete any job, their profit is $0.
Return the maximum profit we can achieve after assigning the workers to the jobs.

Example 1:
Input: difficulty = [2,4,6,8,10], profit = [10,20,30,40,50], worker = [4,5,6,7]
Output: 100
Explanation: Workers are assigned jobs of difficulty [4,4,6,6] and they get a profit of [20,20,30,30] separately.

Example 2:
Input: difficulty = [85,47,57], profit = [24,66,99], worker = [40,25,25]
Output: 0

Constraints:
n == difficulty.length
n == profit.length
m == worker.length
1 <= n, m <= 10^4
1 <= difficulty[i], profit[i], worker[i] <= 10^5
```

</details>

<details><summary>C</summary>

```c
int compareIntArray(const void* a1, const void* a2) {
    int* p1 = (int*)a1;
    int* p2 = (int*)a2;

    // ascending order
    if (p1[0] == p2[0]) {
        return (p1[1] > p2[1]);
    } else {
        return (p1[0] > p2[0]);
    }
}
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int maxProfitAssignment(int* difficulty, int difficultySize, int* profit, int profitSize, int* worker, int workerSize) {
    int retVal = 0;

    int jobIdx = 0;
    int jobSize = difficultySize;
    int job[jobSize][2];
    int i;
    for (i = 0; i < jobSize; ++i) {
        job[i][0] = difficulty[i];
        job[i][1] = profit[i];
    }
    qsort(job, jobSize, sizeof(job[0]), compareIntArray);

    int maxProfit = 0;
    qsort(worker, workerSize, sizeof(int), compareInteger);
    for (i = 0; i < workerSize; ++i) {
        while ((jobIdx < jobSize) && (worker[i] >= job[jobIdx][0])) {
            maxProfit = fmax(maxProfit, job[jobIdx][1]);
            ++jobIdx;
        }
        retVal += maxProfit;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        int retVal = 0;

        vector<pair<int, int>> job;
        int jobIdx = 0;
        int jobSize = difficulty.size();
        for (int i = 0; i < jobSize; ++i) {
            job.emplace_back(difficulty[i], profit[i]);
        }
        sort(job.begin(), job.end());

        int maxProfit = 0;
        sort(worker.begin(), worker.end());
        for (auto pWork : worker) {
            while ((jobIdx < jobSize) && (pWork >= job[jobIdx].first)) {
                maxProfit = max(maxProfit, job[jobIdx].second);
                ++jobIdx;
            }
            retVal += maxProfit;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxProfitAssignment(self, difficulty: List[int], profit: List[int], worker: List[int]) -> int:
        retVal = 0

        job = sorted(zip(difficulty, profit))
        jobSize = len(job)
        jobIdx = 0

        maxProfit = 0
        worker.sort()
        for pWorker in worker:
            while (jobIdx < jobSize) and (pWorker >= job[jobIdx][0]):
                maxProfit = max(maxProfit, job[jobIdx][1])
                jobIdx += 1

            retVal += maxProfit

        return retVal
```

</details>

## [846. Hand of Straights](https://leetcode.com/problems/hand-of-straights/)  1565

- [Official](https://leetcode.com/problems/hand-of-straights/editorial/)
- [Official](https://leetcode.cn/problems/hand-of-straights/solutions/1179042/yi-shou-shun-zi-by-leetcode-solution-4lwn/)

<details><summary>Description</summary>

```text
Alice has some number of cards and she wants to rearrange the cards into groups so that each group is of size groupSize,
and consists of groupSize consecutive cards.

Given an integer array hand where hand[i] is the value written on the ith card and an integer groupSize,
return true if she can rearrange the cards, or false otherwise.

Example 1:
Input: hand = [1,2,3,6,2,3,4,7,8], groupSize = 3
Output: true
Explanation: Alice's hand can be rearranged as [1,2,3],[2,3,4],[6,7,8]

Example 2:
Input: hand = [1,2,3,4,5], groupSize = 4
Output: false
Explanation: Alice's hand can not be rearranged into groups of 4.

Constraints:
1 <= hand.length <= 10^4
0 <= hand[i] <= 10^9
1 <= groupSize <= hand.length

Note: This question is the same as 1296: https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers/
```

</details>

<details><summary>C</summary>

```c
typedef struct Node {
    int value;
    int frequency;
} Node;
int compareInteger(const void *n1, const void *n2) {
    // ascending order
    return (*(int *)n1 > *(int *)n2);
}
bool isNStraightHand(int *hand, int handSize, int groupSize) {
    bool retVal = false;

    if (handSize % groupSize != 0) {
        return retVal;
    }

    qsort(hand, handSize, sizeof(int), compareInteger);

    int i, j;

    Node *pCount = (Node *)malloc(handSize * sizeof(Node));
    if (pCount == NULL) {
        perror("malloc");
        return retVal;
    }
    memset(pCount, 0, sizeof(Node) * handSize);
    pCount[0].value = hand[0];
    pCount[0].frequency = 1;
    int cardSize = 0;
    for (i = 1; i < handSize; ++i) {
        if (hand[i] != pCount[cardSize].value) {
            cardSize++;
        }
        pCount[cardSize].value = hand[i];
        pCount[cardSize].frequency++;
    }

    int num;
    int pos = 0;
    for (i = 0; i < handSize; ++i) {
        while ((pos < cardSize) && (pCount[pos].frequency == 0)) {
            pos++;
        }

        if ((pCount[pos].value == hand[i]) && (pCount[pos].frequency > 0)) {
            for (j = 0; j < groupSize; ++j) {
                num = hand[i] + j;
                if ((pCount[pos + j].frequency > 0) && (pCount[pos + j].value == num)) {
                    pCount[pos + j].frequency--;
                } else {
                    goto exit;
                }
            }
        }
    }
    retVal = true;

exit:
    //
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
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        bool retVal = false;

        int handSize = hand.size();
        if (handSize % groupSize != 0) {
            return retVal;
        }

        sort(hand.begin(), hand.end());

        unordered_map<int, int> count;
        for (auto& num : hand) {
            count[num]++;
        }

        for (auto& x : hand) {
            if (count.count(x) == 0) {
                continue;
            }

            for (int i = 0; i < groupSize; i++) {
                int num = x + i;
                if (count.count(num) == 0) {
                    return retVal;
                }

                count[num]--;
                if (count[num] == 0) {
                    count.erase(num);
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
    def isNStraightHand(self, hand: List[int], groupSize: int) -> bool:
        retVal = False

        handSize = len(hand)
        if handSize % groupSize > 0:
            return retVal

        hand.sort()

        count = Counter(hand)
        for x in hand:
            if count[x] == 0:
                continue

            for num in range(x, x + groupSize):
                if count[num] == 0:
                    return retVal
                count[num] -= 1
        retVal = True

        return retVal
```

</details>

## [860. Lemonade Change](https://leetcode.com/problems/lemonade-change/)  1285

- [Official](https://leetcode.com/problems/lemonade-change/editorial/)
- [Official](https://leetcode.cn/problems/lemonade-change/solutions/515708/ning-meng-shui-zhao-ling-by-leetcode-sol-nvp7/)

<details><summary>Description</summary>

```text
At a lemonade stand, each lemonade costs $5.
Customers are standing in a queue to buy from you and order one at a time (in the order specified by bills).
Each customer will only buy one lemonade and pay with either a $5, $10, or $20 bill.
You must provide the correct change to each customer so that the net transaction is that the customer pays $5.

Note that you do not have any change in hand at first.

Given an integer array bills where bills[i] is the bill the ith customer pays,
return true if you can provide every customer with the correct change, or false otherwise.

Example 1:
Input: bills = [5,5,5,10,20]
Output: true
Explanation:
From the first 3 customers, we collect three $5 bills in order.
From the fourth customer, we collect a $10 bill and give back a $5.
From the fifth customer, we give a $10 bill and a $5 bill.
Since all customers got correct change, we output true.

Example 2:
Input: bills = [5,5,10,10,20]
Output: false
Explanation:
From the first two customers in order, we collect two $5 bills.
For the next two customers in order, we collect a $10 bill and give back a $5 bill.
For the last customer, we can not give the change of $15 back because we only have two $10 bills.
Since not every customer received the correct change, the answer is false.

Constraints:
1 <= bills.length <= 10^5
bills[i] is either 5, 10, or 20.
```

</details>

<details><summary>C</summary>

```c
bool lemonadeChange(int* bills, int billsSize) {
    bool retVal = true;

    int five = 0;
    int ten = 0;
    int bill;
    int i;
    for (i = 0; i < billsSize; ++i) {
        bill = bills[i];
        if (bill == 5) {
            five += 1;
        } else if (bill == 10) {
            if (five == 0) {
                retVal = false;
                break;
            }
            five -= 1;
            ten += 1;
        } else if (bill == 20) {
            if ((ten >= 1) && (five >= 1)) {
                ten -= 1;
                five -= 1;
            } else if (five >= 3) {
                five -= 3;
            } else {
                retVal = false;
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
    bool lemonadeChange(vector<int>& bills) {
        bool retVal = true;

        int five = 0;
        int ten = 0;
        for (int bill : bills) {
            if (bill == 5) {
                five += 1;
            } else if (bill == 10) {
                if (five == 0) {
                    retVal = false;
                    break;
                }
                five -= 1;
                ten += 1;
            } else if (bill == 20) {
                if ((ten >= 1) && (five >= 1)) {
                    ten -= 1;
                    five -= 1;
                } else if (five >= 3) {
                    five -= 3;
                } else {
                    retVal = false;
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
    def lemonadeChange(self, bills: List[int]) -> bool:
        retVal = True

        five = 0
        ten = 0
        for bill in bills:
            if bill == 5:
                five += 1
            elif bill == 10:
                if five == 0:
                    retVal = False
                    break
                five -= 1
                ten += 1
            elif bill == 20:
                if ten >= 1 and five >= 1:
                    ten -= 1
                    five -= 1
                elif five >= 3:
                    five -= 3
                else:
                    retVal = False
                    break

        return retVal
```

</details>

## [861. Score After Flipping Matrix](https://leetcode.com/problems/score-after-flipping-matrix/)  1818

- [Official](https://leetcode.com/problems/score-after-flipping-matrix/editorial/)
- [Official](https://leetcode.cn/problems/score-after-flipping-matrix/solutions/511825/fan-zhuan-ju-zhen-hou-de-de-fen-by-leetc-cxma/)

<details><summary>Description</summary>

```text
You are given an m x n binary matrix grid.

A move consists of choosing any row or column and toggling each value in that row or column
(i.e., changing all 0's to 1's, and all 1's to 0's).

Every row of the matrix is interpreted as a binary number, and the score of the matrix is the sum of these numbers.

Return the highest possible score after making any number of moves (including zero moves).

Example 1:
Input: grid = [[0,0,1,1],[1,0,1,0],[1,1,0,0]]
Output: 39
Explanation: 0b1111 + 0b1001 + 0b1111 = 15 + 9 + 15 = 39

Example 2:
Input: grid = [[0]]
Output: 1

Constraints:
m == grid.length
n == grid[i].length
1 <= m, n <= 20
grid[i][j] is either 0 or 1.
```

</details>

<details><summary>C</summary>

```c
int matrixScore(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    // Set score to summation of first column
    retVal = (1 << (gridColSize[0] - 1)) * gridSize;

    int countSameBits, columnScore;
    int row, col;
    for (col = 1; col < gridColSize[0]; col++) {
        countSameBits = 0;
        for (row = 0; row < gridSize; row++) {
            // Count elements matching first in row
            if (grid[row][col] == grid[row][0]) {
                countSameBits++;
            }
        }

        // Calculate score based on the number of same bits in a column
        countSameBits = fmax(countSameBits, gridSize - countSameBits);

        // Calculate the score contribution for the current column
        columnScore = (1 << (gridColSize[0] - col - 1)) * countSameBits;

        // Add contribution to score
        retVal += columnScore;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int matrixScore(vector<vector<int>>& grid) {
        int retVal = 0;

        int gridSize = grid.size();
        int gridColSize = grid[0].size();

        // Set score to summation of first column
        retVal = (1 << (gridColSize - 1)) * gridSize;

        for (int col = 1; col < gridColSize; col++) {
            int countSameBits = 0;
            for (int row = 0; row < gridSize; row++) {
                // Count elements matching first in row
                if (grid[row][col] == grid[row][0]) {
                    countSameBits++;
                }
            }

            // Calculate score based on the number of same bits in a column
            countSameBits = max(countSameBits, gridSize - countSameBits);

            // Calculate the score contribution for the current column
            int columnScore = (1 << (gridColSize - col - 1)) * countSameBits;

            // Add contribution to score
            retVal += columnScore;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def matrixScore(self, grid: List[List[int]]) -> int:
        retVal = 0

        gridSize = len(grid)
        gridColSize = len(grid[0])

        # Set score to summation of first column
        retVal = (1 << (gridColSize - 1)) * gridSize

        for col in range(1, gridColSize):
            count_same_bits = 0
            for row in range(gridSize):
                # Count elements matching first in row
                if grid[row][col] == grid[row][0]:
                    count_same_bits += 1

            # Calculate score based on the number of same bits in a column
            count_same_bits = max(count_same_bits, gridSize - count_same_bits)

            # Calculate the score contribution for the current column
            column_score = (1 << (gridColSize - col - 1)) * count_same_bits

            # Add contribution to score
            retVal += column_score

        return retVal
```

</details>

## [948. Bag of Tokens](https://leetcode.com/problems/bag-of-tokens/)  1762

- [Official](https://leetcode.com/problems/bag-of-tokens/editorial/)
- [Official](https://leetcode.cn/problems/bag-of-tokens/solutions/15987/ling-pai-fang-zhi-by-leetcode/)

<details><summary>Description</summary>

```text
You start with an initial power of power, an initial score of 0,
and a bag of tokens given as an integer array tokens, where each tokens[i] donates the value of tokeni.

Your goal is to maximize the total score by strategically playing these tokens.
In one move, you can play an unplayed token in one of the two ways (but not both for the same token):
- Face-up: If your current power is at least tokens[i], you may play tokeni, losing tokens[i] power and gaining 1 score.
- Face-down: If your current score is at least 1, you may play tokeni, gaining tokens[i] power and losing 1 score.

Return the maximum possible score you can achieve after playing any number of tokens.

Example 1:
Input: tokens = [100], power = 50
Output: 0
Explanation: Since your score is 0 initially, you cannot play the token face-down.
You also cannot play it face-up since your power (50) is less than tokens[0] (100).

Example 2:
Input: tokens = [200,100], power = 150
Output: 1
Explanation: Play token1 (100) face-up, reducing your power to 50 and increasing your score to 1.
There is no need to play token0, since you cannot play it face-up to add to your score.
The maximum score achievable is 1.

Example 3:
Input: tokens = [100,200,300,400], power = 200
Output: 2
Explanation: Play the tokens in this order to get a score of 2:
Play token0 (100) face-up, reducing power to 100 and increasing score to 1.
Play token3 (400) face-down, increasing power to 500 and reducing score to 0.
Play token1 (200) face-up, reducing power to 300 and increasing score to 1.
Play token2 (300) face-up, reducing power to 0 and increasing score to 2.
The maximum score achievable is 2.

Constraints:
0 <= tokens.length <= 1000
0 <= tokens[i], power < 10^4
```

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int bagOfTokensScore(int* tokens, int tokensSize, int power) {
    int retVal = 0;

    qsort(tokens, tokensSize, sizeof(int), compareInteger);
    int left = 0;
    int right = tokensSize - 1;
    while (left <= right) {
        if (power >= tokens[left]) {
            power -= tokens[left];
            left++;
            retVal++;
        } else if ((left < right) && (retVal > 0)) {
            power += tokens[right];
            right--;
            retVal--;
        } else {
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
    int bagOfTokensScore(vector<int>& tokens, int power) {
        int retVal = 0;

        int tokensSize = tokens.size();

        sort(tokens.begin(), tokens.end());
        int left = 0;
        int right = tokensSize - 1;
        while (left <= right) {
            if (power >= tokens[left]) {
                power -= tokens[left];
                left++;
                retVal++;
            } else if ((left < right) && (retVal > 0)) {
                power += tokens[right];
                right--;
                retVal--;
            } else {
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
    def bagOfTokensScore(self, tokens: List[int], power: int) -> int:
        retVal = 0

        tokensSize = len(tokens)

        tokens.sort()
        left = 0
        right = tokensSize - 1
        while left <= right:
            if power >= tokens[left]:
                power -= tokens[left]
                left += 1
                retVal += 1
            elif (left < right) and (retVal > 0):
                power += tokens[right]
                right -= 1
                retVal -= 1
            else:
                break

        return retVal
```

</details>
