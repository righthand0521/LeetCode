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

## [1402. Reducing Dishes](https://leetcode.com/problems/reducing-dishes/)  1679

- [Official](https://leetcode.cn/problems/reducing-dishes/solutions/198214/zuo-cai-shun-xu-by-leetcode-solution/)

<details><summary>Description</summary>

```text
A chef has collected data on the satisfaction level of his n dishes. Chef can cook any dish in 1 unit of time.

Like-time coefficient of a dish is defined as the time taken to cook
that dish including previous dishes multiplied by its satisfaction level i.e. time[i] * satisfaction[i].

Return the maximum sum of like-time coefficient that the chef can obtain after dishes preparation.

Dishes can be prepared in any order and the chef can discard some dishes to get this maximum value.

Example 1:
Input: satisfaction = [-1,-8,0,5,-9]
Output: 14
Explanation: After Removing the second and last dish,
the maximum total like-time coefficient will be equal to (-1*1 + 0*2 + 5*3 = 14).
Each dish is prepared in one unit of time.

Example 2:
Input: satisfaction = [4,3,2]
Output: 20
Explanation: Dishes can be prepared in any order, (2*1 + 3*2 + 4*3 = 20)

Example 3:
Input: satisfaction = [-1,-4,-5]
Output: 0
Explanation: People do not like the dishes. No dish is prepared.

Constraints:
n == satisfaction.length
1 <= n <= 500
-1000 <= satisfaction[i] <= 1000
```

<details><summary>Hint</summary>

```text
1. Use dynamic programming to find the optimal solution by saving the previous best like-time coefficient
   and its corresponding element sum.
2. If adding the current element to the previous best like-time coefficient
   and its corresponding element sum would increase the best like-time coefficient, then go ahead and add it.
   Otherwise, keep the previous best like-time coefficient.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
int maxSatisfaction(int* satisfaction, int satisfactionSize) {
    int retVal = 0;

    qsort(satisfaction, satisfactionSize, sizeof(int), compareInteger);

    int sum = 0;
    int i;
    for (i = 0; i < satisfactionSize; ++i) {
        sum += satisfaction[i];
        if (sum < 0) {
            break;
        }
        retVal += sum;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxSatisfaction(vector<int>& satisfaction) {
        int retVal = 0;

        sort(satisfaction.begin(), satisfaction.end(), [&](const int& x, const int& y) {
            // descending order
            return (x > y);
        });

        int sum = 0;
        for (auto iterator : satisfaction) {
            sum += iterator;
            if (sum <= 0) {
                break;
            }
            retVal += sum;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxSatisfaction(self, satisfaction: List[int]) -> int:
        retVal = 0

        satisfaction.sort(reverse=True)

        sum = 0
        for i in satisfaction:
            sum += i
            if sum >= 0:
                retVal += sum

        return retVal
```

</details>

## [1481. Least Number of Unique Integers after K Removals](https://leetcode.com/problems/least-number-of-unique-integers-after-k-removals/)  1284

- [Official](https://leetcode.com/problems/least-number-of-unique-integers-after-k-removals/editorial/)
- [Official](https://leetcode.cn/problems/least-number-of-unique-integers-after-k-removals/solutions/579291/bu-tong-zheng-shu-de-zui-shao-shu-mu-by-h6h4i/)

<details><summary>Description</summary>

```text
Given an array of integers arr and an integer k.
Find the least number of unique integers after removing exactly k elements.

Example 1:
Input: arr = [5,5,4], k = 1
Output: 1
Explanation: Remove the single 4, only 5 is left.

Example 2:
Input: arr = [4,3,1,1,3,3,2], k = 3
Output: 2
Explanation: Remove 4, 2 and either one of the two 1s or three 3s. 1 and 3 will be left.

Constraints:
1 <= arr.length <= 10^5
1 <= arr[i] <= 10^9
0 <= k <= arr.length
```

<details><summary>Hint</summary>

```text
1. Use a map to count the frequencies of the numbers in the array.
2. An optimal strategy is to remove the numbers with the smallest count first.
```

</details>

</details>

<details><summary>C</summary>

```c
typedef struct {
    int number;
    int times;
} pair;
int compareStruct(const void* a, const void* b) {
    int pa = ((pair*)a)->times;
    int pb = ((pair*)b)->times;

    // ascending order
    return (pa > pb);
}
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int findLeastNumOfUniqueInts(int* arr, int arrSize, int k) {
    int retVal = 0;

    int i;

    qsort(arr, arrSize, sizeof(int), compareInteger);
    int previous = arr[0];
    int occurrencesSize = 1;
    for (i = 1; i < arrSize; ++i) {
        if (previous != arr[i]) {
            previous = arr[i];
            occurrencesSize++;
        }
    }

    pair occurrences[occurrencesSize];
    memset(occurrences, 0, sizeof(occurrences));
    occurrencesSize = 0;
    occurrences[occurrencesSize].number = arr[0];
    occurrences[occurrencesSize].times += 1;
    for (i = 1; i < arrSize; ++i) {
        if (occurrences[occurrencesSize].number != arr[i]) {
            occurrencesSize++;
            occurrences[occurrencesSize].number = arr[i];
        }
        occurrences[occurrencesSize].times += 1;
    }
    occurrencesSize++;
    qsort(occurrences, occurrencesSize, sizeof(pair), compareStruct);

    for (i = 0; i < occurrencesSize; ++i) {
        k -= occurrences[i].times;
        if (k < 0) {
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
    int findLeastNumOfUniqueInts(vector<int>& arr, int k) {
        int retVal = 0;

        unordered_map<int, int> occurrences;
        for (auto iterator : arr) {
            occurrences[iterator]++;
        }

        vector<pair<int, int>> occurrencesSort(occurrences.begin(), occurrences.end());
        sort(occurrencesSort.begin(), occurrencesSort.end(), [&](auto x1, auto x2) {
            // ascending order
            return x1.second < x2.second;
        });

        for (auto iterator : occurrencesSort) {
            k -= iterator.second;
            if (k < 0) {
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
    def findLeastNumOfUniqueInts(self, arr: List[int], k: int) -> int:
        retVal = 0

        arrCount = Counter(arr).most_common()
        arrCount.reverse()
        for _, times in arrCount:
            k -= times
            if k < 0:
                retVal += 1

        return retVal
```

</details>

## [1561. Maximum Number of Coins You Can Get](https://leetcode.com/problems/maximum-number-of-coins-you-can-get/)  1405

- [Official](https://leetcode.com/problems/maximum-number-of-coins-you-can-get/editorial/)
- [Official](https://leetcode.cn/problems/maximum-number-of-coins-you-can-get/solutions/409109/ni-ke-yi-huo-de-de-zui-da-ying-bi-shu-mu-by-leetco/)

<details><summary>Description</summary>

```text
There are 3n piles of coins of varying size, you and your friends will take piles of coins as follows:
- In each step, you will choose any 3 piles of coins (not necessarily consecutive).
- Of your choice, Alice will pick the pile with the maximum number of coins.
- You will pick the next pile with the maximum number of coins.
- Your friend Bob will pick the last pile.
- Repeat until there are no more piles of coins.

Given an array of integers piles where piles[i] is the number of coins in the ith pile.
Return the maximum number of coins that you can have.

Example 1:
Input: piles = [2,4,1,2,7,8]
Output: 9
Explanation: Choose the triplet (2, 7, 8),
Alice Pick the pile with 8 coins, you the pile with 7 coins and Bob the last one.
Choose the triplet (1, 2, 4), Alice Pick the pile with 4 coins, you the pile with 2 coins and Bob the last one.
The maximum number of coins which you can have are: 7 + 2 = 9.
On the other hand if we choose this arrangement (1, 2, 8), (2, 4, 7) you only get 2 + 4 = 6 coins which is not optimal.

Example 2:
Input: piles = [2,4,5]
Output: 4

Example 3:
Input: piles = [9,8,7,6,5,1,2,3,4]
Output: 18

Constraints:
3 <= piles.length <= 10^5
piles.length % 3 == 0
1 <= piles[i] <= 10^4
```

<details><summary>Hint</summary>

```text
1. Which pile of coins will you never be able to pick up?
2. Bob is forced to take the last pile of coins, no matter what it is. Which pile should you give to him?
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int maxCoins(int* piles, int pilesSize) {
    int retVal = 0;

    qsort(piles, pilesSize, sizeof(int), compareInteger);

    int left = 0;
    int right = pilesSize - 1;
    while (left < right) {
        --right;
        retVal += piles[right];
        --right;
        ++left;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxCoins(vector<int>& piles) {
        int retVal = 0;

        int pilesSize = piles.size();
        sort(piles.begin(), piles.end());

        int left = 0;
        int right = pilesSize - 1;
        while (left < right) {
            --right;
            retVal += piles[right];
            --right;
            ++left;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxCoins(self, piles: List[int]) -> int:
        retVal = 0

        pilesSize = len(piles)
        piles.sort()

        left = 0
        right = pilesSize - 1
        while left < right:
            right -= 1
            retVal += piles[right]
            right -= 1
            left += 1

        return retVal
```

</details>

## [1578. Minimum Time to Make Rope Colorful](https://leetcode.com/problems/minimum-time-to-make-rope-colorful/)  1574

- [Official](https://leetcode.cn/problems/minimum-time-to-make-rope-colorful/solutions/440327/bi-mian-zhong-fu-zi-mu-de-zui-xiao-shan-chu-chen-4/)

<details><summary>Description</summary>

```text
Alice has n balloons arranged on a rope.
You are given a 0-indexed string colors where colors[i] is the color of the ith balloon.

Alice wants the rope to be colorful.
She does not want two consecutive balloons to be of the same color, so she asks Bob for help.
Bob can remove some balloons from the rope to make it colorful.
You are given a 0-indexed integer array neededTime where neededTime[i] is the time (in seconds)
that Bob needs to remove the ith balloon from the rope.

Return the minimum time Bob needs to make the rope colorful.

Example 1:
Input: colors = "abaac", neededTime = [1,2,3,4,5]
Output: 3
Explanation: In the above image, 'a' is blue, 'b' is red, and 'c' is green.
Bob can remove the blue balloon at index 2. This takes 3 seconds.
There are no longer two consecutive balloons of the same color. Total time = 3.

Example 2:
Input: colors = "abc", neededTime = [1,2,3]
Output: 0
Explanation: The rope is already colorful. Bob does not need to remove any balloons from the rope.

Example 3:
Input: colors = "aabaa", neededTime = [1,2,3,4,1]
Output: 2
Explanation: Bob will remove the ballons at indices 0 and 4. Each ballon takes 1 second to remove.
There are no longer two consecutive balloons of the same color. Total time = 1 + 1 = 2.

Constraints:
n == colors.length == neededTime.length
1 <= n <= 10^5
1 <= neededTime[i] <= 10^4
colors contains only lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Maintain the running sum and max value for repeated letters.
```

</details>

</details>

<details><summary>C</summary>

```c
int minCost(char* colors, int* neededTime, int neededTimeSize) {
    int retVal = 0;

    int colorsSize = strlen(colors);

    int maxNeededTime, cost;
    char previous;
    int i = 0;
    while (i < colorsSize) {
        previous = colors[i];
        maxNeededTime = 0;
        cost = 0;
        while ((i < colorsSize) && (colors[i] == previous)) {
            maxNeededTime = fmax(maxNeededTime, neededTime[i]);
            cost += neededTime[i];
            ++i;
        }
        retVal += (cost - maxNeededTime);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minCost(string colors, vector<int>& neededTime) {
        int retVal = 0;

        int colorsSize = colors.size();

        int i = 0;
        while (i < colorsSize) {
            char previous = colors[i];
            int maxNeededTime = 0;
            int cost = 0;
            while ((i < colorsSize) && (colors[i] == previous)) {
                maxNeededTime = max(maxNeededTime, neededTime[i]);
                cost += neededTime[i];
                ++i;
            }
            retVal += (cost - maxNeededTime);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minCost(self, colors: str, neededTime: List[int]) -> int:
        retVal = 0

        colorsSize = len(colors)

        i = 0
        while i < colorsSize:
            previous = colors[i]
            maxNeededTime = 0
            cost = 0
            while i < colorsSize and colors[i] == previous:
                maxNeededTime = max(maxNeededTime, neededTime[i])
                cost += neededTime[i]
                i += 1
            retVal += cost - maxNeededTime

        return retVal
```

</details>

## [1642. Furthest Building You Can Reach](https://leetcode.com/problems/furthest-building-you-can-reach/)  1962

<details><summary>Description</summary>

```text
You are given an integer array heights representing the heights of buildings, some bricks, and some ladders.

You start your journey from building 0 and move to the next building by possibly using bricks or ladders.

While moving from building i to building i+1 (0-indexed),
- If the current building's height is greater than or equal to the next building's height,
  you do not need a ladder or bricks.
- If the current building's height is less than the next building's height,
  you can either use one ladder or (h[i+1] - h[i]) bricks.

Return the furthest building index (0-indexed) you can reach if you use the given ladders and bricks optimally.

Example 1:
Input: heights = [4,2,7,6,9,14,12], bricks = 5, ladders = 1
Output: 4
Explanation: Starting at building 0, you can follow these steps:
- Go to building 1 without using ladders nor bricks since 4 >= 2.
- Go to building 2 using 5 bricks. You must use either bricks or ladders because 2 < 7.
- Go to building 3 without using ladders nor bricks since 7 >= 6.
- Go to building 4 using your only ladder. You must use either bricks or ladders because 6 < 9.
It is impossible to go beyond building 4 because you do not have any more bricks or ladders.

Example 2:
Input: heights = [4,12,2,7,3,18,20,3,19], bricks = 10, ladders = 2
Output: 7

Example 3:
Input: heights = [14,3,19,3], bricks = 17, ladders = 0
Output: 3

Constraints:
1 <= heights.length <= 10^5
1 <= heights[i] <= 10^6
0 <= bricks <= 10^9
0 <= ladders <= heights.length
```

<details><summary>Hint</summary>

```text
1. Assume the problem is to check whether you can reach the last building or not.
2. You'll have to do a set of jumps, and choose for each one whether to do it using a ladder or bricks.
   It's always optimal to use ladders in the largest jumps.
3. Iterate on the buildings, maintaining the largest r jumps and the sum of the remaining ones so far,
   and stop whenever this sum exceeds b.
```

</details>

</details>

<details><summary>C</summary>

```c
#ifndef HEAP_H
#define HEAP_H

//
void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}
//
typedef struct {
    int* data;     // Array to store the heap elements
    int size;      // Current size of the heap
    int capacity;  // Maximum capacity of the heap
} MinHeap;
//
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = NULL;

    minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    if (minHeap == NULL) {
        perror("malloc");
        return minHeap;
    }

    minHeap->data = (int*)malloc(capacity * sizeof(int));
    if (minHeap == NULL) {
        perror("malloc");
        free(minHeap);
        minHeap = NULL;
        return minHeap;
    }
    minHeap->size = 0;
    minHeap->capacity = capacity;

    return minHeap;
}
void heapifyMinHeap(MinHeap* minHeap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    // Function to heapify the heap starting from the given index
    if ((left < minHeap->size) && (minHeap->data[left] < minHeap->data[smallest])) {
        smallest = left;
    }

    if ((right < minHeap->size) && (minHeap->data[right] < minHeap->data[smallest])) {
        smallest = right;
    }

    if (smallest != index) {
        swap(&minHeap->data[index], &minHeap->data[smallest]);
        heapifyMinHeap(minHeap, smallest);
    }
}
void pushMinHeap(MinHeap* minHeap, int value) {
    if (minHeap->size == minHeap->capacity) {
        printf("Heap is full. Cannot insert more elements.\n");
        return;
    }

    int index = minHeap->size++;
    minHeap->data[index] = value;

    // Fix the min heap property by comparing the value with its parent
    while ((index != 0) && (minHeap->data[(index - 1) / 2] > minHeap->data[index])) {
        swap(&minHeap->data[(index - 1) / 2], &minHeap->data[index]);
        index = (index - 1) / 2;
    }
}
int popMinHeap(MinHeap* minHeap) {
    int retVal = -1;

    if (minHeap->size == 0) {
        printf("Heap is empty. Cannot remove elements.\n");
        return retVal;
    }

    retVal = minHeap->data[0];
    minHeap->data[0] = minHeap->data[minHeap->size - 1];
    minHeap->size--;
    heapifyMinHeap(minHeap, 0);

    return retVal;
}
void printMinHeap(MinHeap* minHeap) {
    printf("Min Heap: ");
    for (int i = 0; i < minHeap->size; i++) {
        printf("%d ", minHeap->data[i]);
    }
    printf("\n");
}
void freeMinHeap(MinHeap* minHeap) {
    free(minHeap->data);
    minHeap->data = NULL;
    free(minHeap);
    minHeap = NULL;
}

#endif  // HEAP_H
int furthestBuilding(int* heights, int heightsSize, int bricks, int ladders) {
    int retVal = 0;

    int brickSum = 0;
    MinHeap* pLaddersHeap = createMinHeap(heightsSize);
    if (pLaddersHeap == NULL) {
        return retVal;
    }

    int diff;
    int i;
    for (i = 1; i < heightsSize; ++i) {
        diff = heights[i] - heights[i - 1];
        if (diff <= 0) {
            continue;
        }

        pushMinHeap(pLaddersHeap, diff);
        if (pLaddersHeap->size > ladders) {
            brickSum += popMinHeap(pLaddersHeap);
        }

        if (brickSum > bricks) {
            retVal = i - 1;
            goto exit;
        }
    }
    retVal = heightsSize - 1;

exit:
    //
    freeMinHeap(pLaddersHeap);
    pLaddersHeap = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
        int retVal = 0;

        int heightsSize = heights.size();

        int brickSum = 0;
        priority_queue<int, vector<int>, greater<int>> laddersHeap;
        for (int i = 1; i < heightsSize; ++i) {
            int diff = heights[i] - heights[i - 1];
            if (diff <= 0) {
                continue;
            }

            laddersHeap.push(diff);
            int laddersHeapSize = laddersHeap.size();
            if (laddersHeapSize > ladders) {
                brickSum += laddersHeap.top();
                laddersHeap.pop();
            }

            if (brickSum > bricks) {
                retVal = i - 1;
                return retVal;
            }
        }

        retVal = heightsSize - 1;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def furthestBuilding(self, heights: List[int], bricks: int, ladders: int) -> int:
        retVal = 0

        heightsSize = len(heights)

        bricksSum = 0
        laddersHeap = []
        for i in range(1, heightsSize):
            diff = heights[i] - heights[i-1]
            if diff <= 0:
                continue

            heappush(laddersHeap, diff)
            if len(laddersHeap) > ladders:
                bricksSum += heappop(laddersHeap)

            if bricksSum > bricks:
                retVal = i - 1
                return retVal

        retVal = heightsSize - 1

        return retVal
```

</details>

## [1727. Largest Submatrix With Rearrangements](https://leetcode.com/problems/largest-submatrix-with-rearrangements/)  1926

- [Official](https://leetcode.com/problems/largest-submatrix-with-rearrangements/editorial/)

<details><summary>Description</summary>

```text
You are given a binary matrix matrix of size m x n,
and you are allowed to rearrange the columns of the matrix in any order.

Return the area of the largest submatrix within matrix where every element of the submatrix is 1
after reordering the columns optimally.

Example 1:
Input: matrix = [[0,0,1],[1,1,1],[1,0,1]]
Output: 4
Explanation: You can rearrange the columns as shown above.
The largest submatrix of 1s, in bold, has an area of 4.

Example 2:
Input: matrix = [[1,0,1,0,1]]
Output: 3
Explanation: You can rearrange the columns as shown above.
The largest submatrix of 1s, in bold, has an area of 3.

Example 3:
Input: matrix = [[1,1,0],[1,0,1]]
Output: 2
Explanation: Notice that you must rearrange entire columns,
and there is no way to make a submatrix of 1s larger than an area of 2.

Constraints:
m == matrix.length
n == matrix[i].length
1 <= m * n <= 10^5
matrix[i][j] is either 0 or 1.
```

<details><summary>Hint</summary>

```text
1. For each column, find the number of consecutive ones ending at each position.
2. For each row, sort the cumulative ones in non-increasing order and "fit" the largest submatrix.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
int largestSubmatrix(int** matrix, int matrixSize, int* matrixColSize) {
    int retVal = 0;

    int rowSize = matrixSize;
    int colSize = matrixColSize[0];
    int x, y;

    for (x = 1; x < rowSize; ++x) {
        for (y = 0; y < colSize; ++y) {
            if (matrix[x][y] == 1) {
                matrix[x][y] += matrix[x - 1][y];
            }
        }
    }

    for (x = 0; x < rowSize; ++x) {
        qsort(matrix[x], colSize, sizeof(int), compareInteger);
        for (y = 0; y < colSize; ++y) {
            retVal = fmax(retVal, matrix[x][y] * (y + 1));
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
    int largestSubmatrix(vector<vector<int>>& matrix) {
        int retVal = 0;

        int rowSize = matrix.size();
        int colSize = matrix[0].size();

        for (int x = 1; x < rowSize; ++x) {
            for (int y = 0; y < colSize; ++y) {
                if (matrix[x][y] == 1) {
                    matrix[x][y] += matrix[x - 1][y];
                }
            }
        }

        for (int x = 0; x < rowSize; ++x) {
            sort(matrix[x].begin(), matrix[x].end(), greater());
            for (int y = 0; y < colSize; ++y) {
                retVal = max(retVal, matrix[x][y] * (y + 1));
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
    def largestSubmatrix(self, matrix: List[List[int]]) -> int:
        retVal = 0

        rowSize = len(matrix)
        colSize = len(matrix[0])

        for x in range(1, rowSize):
            for y in range(colSize):
                if matrix[x][y] == 1:
                    matrix[x][y] += matrix[x - 1][y]

        for x in range(rowSize):
            matrix[x].sort(reverse=True)
            for y in range(colSize):
                retVal = max(retVal, matrix[x][y] * (y + 1))

        return retVal
```

</details>

## [1764. Form Array by Concatenating Subarrays of Another Array](https://leetcode.com/problems/form-array-by-concatenating-subarrays-of-another-array/)  1588

- [Official](https://leetcode.cn/problems/form-array-by-concatenating-subarrays-of-another-array/solutions/2022689/tong-guo-lian-jie-ling-yi-ge-shu-zu-de-z-xsvx/)

<details><summary>Description</summary>

```text
You are given a 2D integer array groups of length n. You are also given an integer array nums.

You are asked if you can choose n disjoint subarrays from the array nums
such that the ith subarray is equal to groups[i] (0-indexed), and if i > 0,
the (i-1)th subarray appears before the ith subarray in nums (i.e. the subarrays must be in the same order as groups).

Return true if you can do this task, and false otherwise.

Note that the subarrays are disjoint if and only if there is no index k such that nums[k] belongs to more than one subarray.
A subarray is a contiguous sequence of elements within an array.

Example 1:
Input: groups = [[1,-1,-1],[3,-2,0]], nums = [1,-1,0,1,-1,-1,3,-2,0]
Output: true
Explanation: You can choose the 0th subarray as [1,-1,0,1,-1,-1,3,-2,0] and the 1st one as [1,-1,0,1,-1,-1,3,-2,0].
These subarrays are disjoint as they share no common nums[k] element.

Example 2:
Input: groups = [[10,-2],[1,2,3,4]], nums = [1,2,3,4,10,-2]
Output: false
Explanation: Note that choosing the subarrays [1,2,3,4,10,-2] and [1,2,3,4,10,-2] is incorrect
because they are not in the same order as in groups.
[10,-2] must come before [1,2,3,4].

Example 3:
Input: groups = [[1,2,3],[3,4]], nums = [7,7,1,2,3,4,7,7]
Output: false
Explanation: Note that choosing the subarrays [7,7,1,2,3,4,7,7] and [7,7,1,2,3,4,7,7] is invalid because they are not disjoint.
They share a common elements nums[4] (0-indexed).

Constraints:
groups.length == n
1 <= n <= 10^3
1 <= groups[i].length, sum(groups[i].length) <= 10^3
1 <= nums.length <= 10^3
-10^7 <= groups[i][j], nums[k] <= 10^7
```

</details>

<details><summary>C</summary>

```c
bool canChoose(int** groups, int groupsSize, int* groupsColSize, int* nums, int numsSize) {
    bool retVal = false;

    int i;
    int idx = 0;
    int row = 0;
    while ((idx < numsSize) && (row < groupsSize)) {
        if (idx + groupsColSize[row] > numsSize) {
            return retVal;
        }

        for (i = 0; i < groupsColSize[row]; ++i) {
            if (groups[row][i] != nums[idx + i]) {
                ++idx;
                break;
            }
        }
        if (i < groupsColSize[row]) {
            continue;
        }

        idx += groupsColSize[row];
        ++row;
    }

    if (row == groupsSize) {
        retVal = true;
    }

    return retVal;
}
```

</details>

## [1785. Minimum Elements to Add to Form a Given Sum](https://leetcode.com/problems/minimum-elements-to-add-to-form-a-given-sum/)  1432

- [Official](https://leetcode.cn/problems/minimum-elements-to-add-to-form-a-given-sum/solutions/2020959/gou-cheng-te-ding-he-xu-yao-tian-jia-de-m3gnt/)

<details><summary>Description</summary>

```text
You are given an integer array nums and two integers limit and goal.
The array nums has an interesting property that abs(nums[i]) <= limit.

Return the minimum number of elements you need to add to make the sum of the array equal to goal.
The array must maintain its property that abs(nums[i]) <= limit.

Note that abs(x) equals x if x >= 0, and -x otherwise.

Example 1:
Input: nums = [1,-1,1], limit = 3, goal = -4
Output: 2
Explanation: You can add -2 and -3, then the sum of the array will be 1 - 1 + 1 - 2 - 3 = -4.

Example 2:
Input: nums = [1,-10,9,1], limit = 100, goal = 0
Output: 1

Constraints:
1 <= nums.length <= 10^5
1 <= limit <= 10^6
-limit <= nums[i] <= limit
-10^9 <= goal <= 10^9
```

</details>

<details><summary>C</summary>

```c
int minElements(int* nums, int numsSize, int limit, int goal) {
    int retVal = 0;

    /* Boundary
     *  1 <= nums.length <= 10^5
     *  1 <= limit <= 10^6.
     */
    long long sum = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        sum += nums[i];
    }

    long long diff = llabs(sum - goal);
    /* divisible or not divisible
     *  diff = n * limit
     *  diff = n * limit + r
     */
    retVal = (diff + limit - 1) / limit;

    return retVal;
}
```

</details>

## [1827. Minimum Operations to Make the Array Increasing](https://leetcode.com/problems/minimum-operations-to-make-the-array-increasing/)  1314

- [Official](https://leetcode.cn/problems/minimum-operations-to-make-the-array-increasing/solutions/2014890/zui-shao-cao-zuo-shi-shu-zu-di-zeng-by-l-sjr6/)

<details><summary>Description</summary>

```text
You are given an integer array nums (0-indexed).
In one operation, you can choose an element of the array and increment it by 1.
- For example, if nums = [1,2,3], you can choose to increment nums[1] to make nums = [1,3,3].

Return the minimum number of operations needed to make nums strictly increasing.

An array nums is strictly increasing if nums[i] < nums[i+1] for all 0 <= i < nums.length - 1.
An array of length 1 is trivially strictly increasing.

Example 1:
Input: nums = [1,1,1]
Output: 3
Explanation: You can do the following operations:
1) Increment nums[2], so nums becomes [1,1,2].
2) Increment nums[1], so nums becomes [1,2,2].
3) Increment nums[2], so nums becomes [1,2,3].

Example 2:
Input: nums = [1,5,2,4,1]
Output: 14

Example 3:
Input: nums = [8]
Output: 0

Constraints:
1 <= nums.length <= 5000
1 <= nums[i] <= 10^4
```

<details><summary>Hint</summary>

```text
1. nums[i+1] must be at least equal to nums[i] + 1.
2. Think greedily. You don't have to increase nums[i+1] beyond nums[i]+1.
3. Iterate on i and set nums[i] = max(nums[i-1]+1, nums[i]) .
```

</details>

</details>

<details><summary>C</summary>

```c
int minOperations(int* nums, int numsSize) {
    int retVal = 0;

    int diff;
    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[i - 1] >= nums[i]) {
            diff = nums[i - 1] - nums[i] + 1;
            nums[i] += diff;
            retVal += diff;
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

        int numsSize = nums.size();
        for (int i = 1; i < numsSize; ++i) {
            if (nums[i - 1] >= nums[i]) {
                int diff = nums[i - 1] - nums[i] + 1;
                nums[i] += diff;
                retVal += diff;
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

        numsSize = len(nums)
        for i in range(1,numsSize):
            if nums[i - 1] >= nums[i]:
                diff = nums[i - 1] - nums[i] + 1
                nums[i] += diff
                retVal += diff

        return retVal
```

</details>

## [1846. Maximum Element After Decreasing and Rearranging](https://leetcode.com/problems/maximum-element-after-decreasing-and-rearranging/)  1454

- [Official](https://leetcode.com/problems/maximum-element-after-decreasing-and-rearranging/editorial/)
- [Official](https://leetcode.cn/problems/maximum-element-after-decreasing-and-rearranging/solutions/754917/jian-xiao-he-zhong-xin-pai-lie-shu-zu-ho-mzee/)

<details><summary>Description</summary>

```text
You are given an array of positive integers arr.
Perform some operations (possibly none) on arr so that it satisfies these conditions:
- The value of the first element in arr must be 1.
- The absolute difference between any 2 adjacent elements must be less than or equal to 1.
  In other words, abs(arr[i] - arr[i - 1]) <= 1 for each i where 1 <= i < arr.length (0-indexed).
  abs(x) is the absolute value of x.

There are 2 types of operations that you can perform any number of times:
- Decrease the value of any element of arr to a smaller positive integer.
- Rearrange the elements of arr to be in any order.

Return the maximum possible value of an element in arr after performing the operations to satisfy the conditions.

Example 1:
Input: arr = [2,2,1,2,1]
Output: 2
Explanation:
We can satisfy the conditions by rearranging arr so it becomes [1,2,2,2,1].
The largest element in arr is 2.

Example 2:
Input: arr = [100,1,1000]
Output: 3
Explanation:
One possible way to satisfy the conditions is by doing the following:
1. Rearrange arr so it becomes [1,100,1000].
2. Decrease the value of the second element to 2.
3. Decrease the value of the third element to 3.
Now arr = [1,2,3], which satisfies the conditions.
The largest element in arr is 3.

Example 3:
Input: arr = [1,2,3,4,5]
Output: 5
Explanation: The array already satisfies the conditions, and the largest element is 5.

Constraints:
1 <= arr.length <= 10^5
1 <= arr[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Sort the Array.
2. Decrement each element to the largest integer that satisfies the conditions.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int maximumElementAfterDecrementingAndRearranging(int* arr, int arrSize) {
    int retVal = 1;

    qsort(arr, arrSize, sizeof(int), compareInteger);

    int i;
    for (i = 1; i < arrSize; ++i) {
        if (arr[i] - retVal >= 1) {
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
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        int retVal = 1;

        sort(arr.begin(), arr.end());

        int arrSize = arr.size();
        for (int i = 1; i < arrSize; ++i) {
            if (arr[i] - retVal >= 1) {
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
    def maximumElementAfterDecrementingAndRearranging(self, arr: List[int]) -> int:
        retVal = 1

        arr.sort()

        arrSize = len(arr)
        for i in range(1, arrSize):
            if arr[i] - retVal >= 1:
                retVal += 1

        return retVal
```

</details>

## [1921. Eliminate Maximum Number of Monsters](https://leetcode.com/problems/eliminate-maximum-number-of-monsters/)  1527

- [Official](https://leetcode.com/problems/eliminate-maximum-number-of-monsters/editorial/)
- [Official](https://leetcode.cn/problems/eliminate-maximum-number-of-monsters/solutions/857961/xiao-mie-guai-wu-de-zui-da-shu-liang-by-0ou2p/)

<details><summary>Description</summary>

```text
You are playing a video game where you are defending your city from a group of n monsters.
You are given a 0-indexed integer array dist of size n,
where dist[i] is the initial distance in kilometers of the ith monster from the city.

The monsters walk toward the city at a constant speed.
The speed of each monster is given to you in an integer array speed of size n,
where speed[i] is the speed of the ith monster in kilometers per minute.

You have a weapon that, once fully charged, can eliminate a single monster.
However, the weapon takes one minute to charge. The weapon is fully charged at the very start.

You lose when any monster reaches your city.
If a monster reaches the city at the exact moment the weapon is fully charged,
it counts as a loss, and the game ends before you can use your weapon.

Return the maximum number of monsters that you can eliminate before you lose,
or n if you can eliminate all the monsters before they reach the city.

Example 1:
Input: dist = [1,3,4], speed = [1,1,1]
Output: 3
Explanation:
In the beginning, the distances of the monsters are [1,3,4]. You eliminate the first monster.
After a minute, the distances of the monsters are [X,2,3]. You eliminate the second monster.
After a minute, the distances of the monsters are [X,X,2]. You eliminate the thrid monster.
All 3 monsters can be eliminated.

Example 2:
Input: dist = [1,1,2,3], speed = [1,1,1,1]
Output: 1
Explanation:
In the beginning, the distances of the monsters are [1,1,2,3]. You eliminate the first monster.
After a minute, the distances of the monsters are [X,0,1,2], so you lose.
You can only eliminate 1 monster.

Example 3:
Input: dist = [3,2,4], speed = [5,3,2]
Output: 1
Explanation:
In the beginning, the distances of the monsters are [3,2,4]. You eliminate the first monster.
After a minute, the distances of the monsters are [X,0,2], so you lose.
You can only eliminate 1 monster.

Constraints:
n == dist.length == speed.length
1 <= n <= 10^5
1 <= dist[i], speed[i] <= 10^5
```

<details><summary>Hint</summary>

```text
1. Find the amount of time it takes each monster to arrive.
2. Find the order in which the monsters will arrive.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareDouble(const void* n1, const void* n2) {
    // ascending order
    return (*(double*)n1 > *(double*)n2);
}
int eliminateMaximum(int* dist, int distSize, int* speed, int speedSize) {
    int retVal = 0;

    double arrival[distSize];
    memset(arrival, 0, sizeof(arrival));

    int i;
    for (i = 0; i < distSize; ++i) {
        arrival[i] = (double)dist[i] / speed[i];
    }

    qsort(arrival, distSize, sizeof(double), compareDouble);

    for (i = 0; i < distSize; ++i) {
        if (arrival[i] <= i) {
            break;
        }
        retVal += 1;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int eliminateMaximum(vector<int>& dist, vector<int>& speed) {
        int retVal = 0;

        int distSize = dist.size();  // n == dist.length == speed.length

        vector<double> arrival;
        for (int i = 0; i < distSize; ++i) {
            arrival.emplace_back((double)dist[i] / speed[i]);
        }

        sort(arrival.begin(), arrival.end());

        for (int i = 0; i < distSize; ++i) {
            if (arrival[i] <= i) {
                break;
            }
            retVal += 1;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def eliminateMaximum(self, dist: List[int], speed: List[int]) -> int:
        retVal = 0

        arrival = []
        for d, s in zip(dist, speed):
            arrival.append(d / s)

        arrival.sort()

        for idx, value in enumerate(arrival):
            if value <= idx:
                break
            retVal += 1

        return retVal
```

</details>

## [2027. Minimum Moves to Convert String](https://leetcode.com/problems/minimum-moves-to-convert-string/)  1346

- [Official](https://leetcode.cn/problems/minimum-moves-to-convert-string/solutions/2032769/zhuan-huan-zi-fu-chuan-de-zui-shao-cao-z-cji1/)

<details><summary>Description</summary>

```text
You are given a string s consisting of n characters which are either 'X' or 'O'.

A move is defined as selecting three consecutive characters of s and converting them to 'O'.
Note that if a move is applied to the character 'O', it will stay the same.

Return the minimum number of moves required so that all the characters of s are converted to 'O'.

Example 1:
Input: s = "XXX"
Output: 1
Explanation: XXX -> OOO
We select all the 3 characters and convert them in one move.

Example 2:
Input: s = "XXOX"
Output: 2
Explanation: XXOX -> OOOX -> OOOO
We select the first 3 characters in the first move, and convert them to 'O'.
Then we select the last 3 characters and convert them so that the final string contains all 'O's.

Example 3:
Input: s = "OOOO"
Output: 0
Explanation: There are no 'X's in s to convert.

Constraints:
3 <= s.length <= 1000
s[i] is either 'X' or 'O'.
```

</details>

<details><summary>C</summary>

```c
int minimumMoves(char* s) {
    int retVal = 0;

    int len = strlen(s);

#define CONTINUE_COUNT (3)
#define CONTINUE_CHAR 'X'
    int count = 0;
    int i;
    for (i = 0; i < len; ++i) {
        if (s[i] == CONTINUE_CHAR) {
            ++count;
        } else {
            if (count != 0) {
                ++count;
            }
        }

        if (count == CONTINUE_COUNT) {
            ++retVal;
            count = 0;
        }
    }
    if (count != 0) {
        ++retVal;
    }

    return retVal;
}
```

</details>

## [2038. Remove Colored Pieces if Both Neighbors are the Same Color](https://leetcode.com/problems/remove-colored-pieces-if-both-neighbors-are-the-same-color/)  1467

- [Official](https://leetcode.com/problems/remove-colored-pieces-if-both-neighbors-are-the-same-color/editorial/)
- [Official](https://leetcode.cn/problems/remove-colored-pieces-if-both-neighbors-are-the-same-color/solutions/1355114/ru-guo-xiang-lin-liang-ge-yan-se-jun-xia-rfbk/)

<details><summary>Description</summary>

```text
There are n pieces arranged in a line, and each piece is colored either by 'A' or by 'B'.
You are given a string colors of length n where colors[i] is the color of the ith piece.

Alice and Bob are playing a game where they take alternating turns removing pieces from the line.
In this game, Alice moves first.
- Alice is only allowed to remove a piece colored 'A' if both its neighbors are also colored 'A'.
  She is not allowed to remove pieces that are colored 'B'.
- Bob is only allowed to remove a piece colored 'B' if both its neighbors are also colored 'B'.
  He is not allowed to remove pieces that are colored 'A'.
- Alice and Bob cannot remove pieces from the edge of the line.
- If a player cannot make a move on their turn, that player loses and the other player wins.

Assuming Alice and Bob play optimally, return true if Alice wins, or return false if Bob wins.

Example 1:
Input: colors = "AAABABB"
Output: true
Explanation:
AAABABB -> AABABB
Alice moves first.
She removes the second 'A' from the left since that is the only 'A' whose neighbors are both 'A'.
Now it's Bob's turn.
Bob cannot make a move on his turn since there are no 'B's whose neighbors are both 'B'.
Thus, Alice wins, so return true.

Example 2:
Input: colors = "AA"
Output: false
Explanation:
Alice has her turn first.
There are only two 'A's and both are on the edge of the line, so she cannot move on her turn.
Thus, Bob wins, so return false.

Example 3:
Input: colors = "ABBBBBBBAAA"
Output: false
Explanation:
ABBBBBBBAAA -> ABBBBBBBAA
Alice moves first.
Her only option is to remove the second to last 'A' from the right.
ABBBBBBBAA -> ABBBBBBAA
Next is Bob's turn.
He has many options for which 'B' piece to remove. He can pick any.
On Alice's second turn, she has no more pieces that she can remove.
Thus, Bob wins, so return false.

Constraints:
1 <= colors.length <= 10^5
colors consists of only the letters 'A' and 'B'
```

<details><summary>Hint</summary>

```text
1. Does the number of moves a player can make depend on what the other player does? No
2. How many moves can Alice make if colors == "AAAAAA"
3. If a group of n consecutive pieces has the same color,
   the player can take n - 2 of those pieces if n is greater than or equal to 3
```

</details>

</details>

<details><summary>C</summary>

```c
bool winnerOfGame(char *colors) {
    bool retVal = false;

    int colorsSize = strlen(colors);

    int Alice = 0;
    int Bob = 0;
    int i;
    for (i = 1; i < colorsSize - 1; ++i) {
        // The number of moves available to Alice is the number of times the substring "AAA" appears.
        // The number of moves available to Bob is the number of times the substring "BBB" appears.
        if ((colors[i] == colors[i - 1]) && (colors[i] == colors[i + 1])) {
            if (colors[i] == 'A') {
                Alice++;
            } else if (colors[i] == 'B') {
                Bob++;
            }
        }
    }
    if (Alice > Bob) {
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
    bool winnerOfGame(string colors) {
        bool retVal = false;

        int colorsSize = colors.size();

        int Alice = 0;
        int Bob = 0;
        for (int i = 1; i < colorsSize - 1; ++i) {
            // The number of moves available to Alice is the number of times the substring "AAA" appears.
            // The number of moves available to Bob is the number of times the substring "BBB" appears.
            if ((colors[i] == colors[i - 1]) && (colors[i] == colors[i + 1])) {
                if (colors[i] == 'A') {
                    Alice++;
                } else if (colors[i] == 'B') {
                    Bob++;
                }
            }
        }
        if (Alice > Bob) {
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
    def winnerOfGame(self, colors: str) -> bool:
        retVal = False

        colorsSize = len(colors)

        Alice = 0
        Bob = 0
        for i in range(1, colorsSize-1):
            # The number of moves available to Alice is the number of times the substring "AAA" appears.
            # The number of moves available to Bob is the number of times the substring "BBB" appears.
            if (colors[i] == colors[i-1]) and (colors[i] == colors[i+1]):
                if colors[i] == 'A':
                    Alice += 1
                elif colors[i] == 'B':
                    Bob += 1
        if Alice > Bob:
            retVal = True

        return retVal
```

</details>

## [2126. Destroying Asteroids](https://leetcode.com/problems/destroying-asteroids/)  1334

- [Official](https://leetcode.cn/problems/destroying-asteroids/solutions/1202026/cui-hui-xiao-xing-xing-by-leetcode-solut-ng2v/)

<details><summary>Description</summary>

```text
You are given an integer mass, which represents the original mass of a planet.
You are further given an integer array asteroids, where asteroids[i] is the mass of the ith asteroid.

You can arrange for the planet to collide with the asteroids in any arbitrary order.
If the mass of the planet is greater than or equal to the mass of the asteroid,
the asteroid is destroyed and the planet gains the mass of the asteroid.
Otherwise, the planet is destroyed.

Return true if all asteroids can be destroyed. Otherwise, return false.

Example 1:
Input: mass = 10, asteroids = [3,9,19,5,21]
Output: true
Explanation: One way to order the asteroids is [9,19,5,3,21]:
- The planet collides with the asteroid with a mass of 9. New planet mass: 10 + 9 = 19
- The planet collides with the asteroid with a mass of 19. New planet mass: 19 + 19 = 38
- The planet collides with the asteroid with a mass of 5. New planet mass: 38 + 5 = 43
- The planet collides with the asteroid with a mass of 3. New planet mass: 43 + 3 = 46
- The planet collides with the asteroid with a mass of 21. New planet mass: 46 + 21 = 67
All asteroids are destroyed.

Example 2:
Input: mass = 5, asteroids = [4,9,23,4]
Output: false
Explanation:
The planet cannot ever gain enough mass to destroy the asteroid with a mass of 23.
After the planet destroys the other asteroids, it will have a mass of 5 + 4 + 9 + 4 = 22.
This is less than 23, so a collision would not destroy the last asteroid.

Constraints:
1 <= mass <= 10^5
1 <= asteroids.length <= 10^5
1 <= asteroids[i] <= 10^5
```

<details><summary>Hint</summary>

```text
1. Choosing the asteroid to collide with can be done greedily.
2. If an asteroid will destroy the planet, then every bigger asteroid will also destroy the planet.
3. You only need to check the smallest asteroid at each collision.
   If it will destroy the planet, then every other asteroid will also destroy the planet.
4. Sort the asteroids in non-decreasing order by mass, then greedily try to collide with the asteroids in that order.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
bool asteroidsDestroyed(int mass, int* asteroids, int asteroidsSize) {
    bool retVal = true;

    qsort(asteroids, asteroidsSize, sizeof(int), compareInteger);
    long long sum = mass;  // 1 <= asteroids.length <= 10^5, 1 <= asteroids[i] <= 10^5.
    int i;
    for (i = 0; i < asteroidsSize; ++i) {
        if (sum < asteroids[i]) {
            retVal = false;
            break;
        }
        sum += asteroids[i];
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    bool asteroidsDestroyed(int mass, vector<int>& asteroids) {
        bool retVal = true;

        sort(asteroids.begin(), asteroids.end());
        long long sum = mass;  // 1 <= asteroids.length <= 10^5, 1 <= asteroids[i] <= 10^5.
        for (auto asteroid : asteroids) {
            if (sum < asteroid) {
                retVal = false;
                break;
            }
            sum += asteroid;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def asteroidsDestroyed(self, mass: int, asteroids: List[int]) -> bool:
        retVal = True

        asteroids.sort()
        sum = mass
        for asteroid in asteroids:
            if sum < asteroid:
                retVal = False
                break
            sum += asteroid

        return retVal
```

</details>

## [2244. Minimum Rounds to Complete All Tasks](https://leetcode.com/problems/minimum-rounds-to-complete-all-tasks/)  1371

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array tasks, where tasks[i] represents the difficulty level of a task.
In each round, you can complete either 2 or 3 tasks of the same difficulty level.

Return the minimum rounds required to complete all the tasks, or -1 if it is not possible to complete all the tasks.

Example 1:
Input: tasks = [2,2,3,3,2,4,4,4,4,4]
Output: 4
Explanation: To complete all the tasks, a possible plan is:
- In the first round, you complete 3 tasks of difficulty level 2.
- In the second round, you complete 2 tasks of difficulty level 3.
- In the third round, you complete 3 tasks of difficulty level 4.
- In the fourth round, you complete 2 tasks of difficulty level 4.
It can be shown that all the tasks cannot be completed in fewer than 4 rounds, so the answer is 4.

Example 2:
Input: tasks = [2,3,3]
Output: -1
Explanation: There is only 1 task of difficulty level 2,
but in each round, you can only complete either 2 or 3 tasks of the same difficulty level.
Hence, you cannot complete all the tasks, and the answer is -1.

Constraints:
1 <= tasks.length <= 10^5
1 <= tasks[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Which data structure can you use to store the number of tasks of each difficulty level?
2. For any particular difficulty level, what can be the optimal strategy to complete the tasks using minimum rounds?
3. When can we not complete all tasks of a difficulty level?
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int minimumRounds(int* tasks, int tasksSize) {
    int retVal = 0;

    qsort(tasks, tasksSize, sizeof(int), compareInteger);

    int count = 1;
    int i;
    for (i = 1; i < tasksSize; ++i) {
        if (tasks[i] == tasks[i - 1]) {
            ++count;
            continue;
        }

        if (count == 1) {
            retVal = -1;
            return retVal;
        }
        retVal += (count / 3);
        retVal += (count % 3 == 0 ? 0 : 1);

        count = 1;
    }
    if (count == 1) {
        retVal = -1;
        return retVal;
    }
    retVal += (count / 3);
    retVal += (count % 3 == 0 ? 0 : 1);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minimumRounds(vector<int>& tasks) {
        int retVal = 0;

        sort(tasks.begin(), tasks.end());

        int tasksSize = tasks.size();

        int count = 1;
        for (int i = 1; i < tasksSize; ++i) {
            if (tasks[i] == tasks[i - 1]) {
                ++count;
                continue;
            }

            if (count == 1) {
                retVal = -1;
                return retVal;
            }
            retVal += (count / 3);
            retVal += (count % 3 == 0 ? 0 : 1);

            count = 1;
        }
        if (count == 1) {
            retVal = -1;
            return retVal;
        }
        retVal += (count / 3);
        retVal += (count % 3 == 0 ? 0 : 1);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minimumRounds(self, tasks: List[int]) -> int:
        retVal = 0

        tasks.sort()

        tasksSize = len(tasks)
        count = 1
        for i in range(1, tasksSize):
            if tasks[i] == tasks[i-1]:
                count += 1
                continue

            if count == 1:
                retVal = -1
                return retVal
            retVal += (count // 3)
            retVal += 0 if count % 3 == 0 else 1

            count = 1

        if count == 1:
            retVal = -1
            return retVal
        retVal += (count // 3)
        retVal += 0 if count % 3 == 0 else 1

        return retVal
```

</details>

## [2279. Maximum Bags With Full Capacity of Rocks](https://leetcode.com/problems/maximum-bags-with-full-capacity-of-rocks/)  1249

- [Official](https://leetcode.com/problems/maximum-bags-with-full-capacity-of-rocks/solutions/2643763/maximum-bags-with-full-capacity-of-rocks/)

<details><summary>Description</summary>

```text
You have n bags numbered from 0 to n - 1.
You are given two 0-indexed integer arrays capacity and rocks.
The ith bag can hold a maximum of capacity[i] rocks and currently contains rocks[i] rocks.
You are also given an integer additionalRocks, the number of additional rocks you can place in any of the bags.

Return the maximum number of bags that could have full capacity after placing the additional rocks in some bags.

Example 1:
Input: capacity = [2,3,4,5], rocks = [1,2,4,4], additionalRocks = 2
Output: 3
Explanation:
Place 1 rock in bag 0 and 1 rock in bag 1.
The number of rocks in each bag are now [2,3,4,4].
Bags 0, 1, and 2 have full capacity.
There are 3 bags at full capacity, so we return 3.
It can be shown that it is not possible to have more than 3 bags at full capacity.
Note that there may be other ways of placing the rocks that result in an answer of 3.

Example 2:
Input: capacity = [10,2,2], rocks = [2,2,0], additionalRocks = 100
Output: 3
Explanation:
Place 8 rocks in bag 0 and 2 rocks in bag 2.
The number of rocks in each bag are now [10,2,2].
Bags 0, 1, and 2 have full capacity.
There are 3 bags at full capacity, so we return 3.
It can be shown that it is not possible to have more than 3 bags at full capacity.
Note that we did not use all of the additional rocks.

Constraints:
n == capacity.length == rocks.length
1 <= n <= 5 * 10^4
1 <= capacity[i] <= 10^9
0 <= rocks[i] <= capacity[i]
1 <= additionalRocks <= 10^9
```

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int maximumBags(int* capacity, int capacitySize, int* rocks, int rocksSize, int additionalRocks) {
    int retVal = 0;

    int space[capacitySize];
    memset(space, 0, sizeof(space));
    int i;
    for (i = 0; i < capacitySize; ++i) {
        space[i] = capacity[i] - rocks[i];
    }
    qsort(space, capacitySize, sizeof(int), compareInteger);

    for (i = 0; i < capacitySize; ++i) {
        additionalRocks -= space[i];
        if (additionalRocks >= 0) {
            ++retVal;
            continue;
        }
        break;
    }

    return retVal;
}
```

</details>

## [2335. Minimum Amount of Time to Fill Cups](https://leetcode.com/problems/minimum-amount-of-time-to-fill-cups/)  1360

- [Official](https://leetcode.cn/problems/minimum-amount-of-time-to-fill-cups/solutions/2103691/zhuang-man-bei-zi-xu-yao-de-zui-duan-zon-c7y4/)

<details><summary>Description</summary>

```text
ou have a water dispenser that can dispense cold, warm, and hot water.
Every second, you can either fill up 2 cups with different types of water, or 1 cup of any type of water.

You are given a 0-indexed integer array amount of length 3
where amount[0], amount[1], and amount[2] denote the number of cold, warm, and hot water cups you need to fill respectively.
Return the minimum number of seconds needed to fill up all the cups.

Example 1:
Input: amount = [1,4,2]
Output: 4
Explanation: One way to fill up the cups is:
Second 1: Fill up a cold cup and a warm cup.
Second 2: Fill up a warm cup and a hot cup.
Second 3: Fill up a warm cup and a hot cup.
Second 4: Fill up a warm cup.
It can be proven that 4 is the minimum number of seconds needed.

Example 2:
Input: amount = [5,4,4]
Output: 7
Explanation: One way to fill up the cups is:
Second 1: Fill up a cold cup, and a hot cup.
Second 2: Fill up a cold cup, and a warm cup.
Second 3: Fill up a cold cup, and a warm cup.
Second 4: Fill up a warm cup, and a hot cup.
Second 5: Fill up a cold cup, and a hot cup.
Second 6: Fill up a cold cup, and a warm cup.
Second 7: Fill up a hot cup.

Example 3:
Input: amount = [5,0,0]
Output: 5
Explanation: Every second, we fill up a cold cup.

Constraints:
amount.length == 3
0 <= amount[i] <= 100
```

<details><summary>Hint</summary>

```text
1. To minimize the amount of time needed, you want to fill up as many cups as possible in each second.
   This means that you want to maximize the number of seconds where you are filling up two cups.
2. You always want to fill up the two types of water with the most unfilled cups.
```

</details>

</details>

<details><summary>C</summary>

```c
#define BRUTE_FORCE (1)
#define MATH_1 (1)
#define MATH_2 (1)
int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
int fillCups(int* amount, int amountSize) {
    int retVal = 0;

#if (BRUTE_FORCE)
    printf("BRUTE_FORCE\n");

    /* Intuition
     *  142: 131, 021, 010, 000
     *  544: 434, 333, 223, 122, 111, 001, 000
     *  500: 400, 300, 200, 100, 000
     */
    qsort(amount, amountSize, sizeof(int), compareInteger);
    while (amount[0] > 0) {
        if (amount[0] > 0) {
            amount[0] -= 1;
        }

        if (amount[1] > 0) {
            amount[1] -= 1;
        }

        ++retVal;

        qsort(amount, amountSize, sizeof(int), compareInteger);
    }
#elif (MATH_1)
    printf("MATH_1\n");

    /* https://leetcode.cn/problems/minimum-amount-of-time-to-fill-cups/solutions/1658941/by-tsreaper-158c/
     *  Let amount[2] < amount[1] < amount[0]
     *  1. If amount[2] + amount[1] <= amount[0]
     *     => amount[0] is the minimum number of seconds needed
     *  2. If amount[2] + amount[1] > amount[0]
     *     Let Exceed = amount[2] + amount[1] - amount[0]
     *     if Exceed is even: (Exceed / 2) + amount[0] is the minimum number of seconds needed
     *     => (Exceed / 2) + amount[0]
     *        = (amount[2] + amount[1] - amount[0]) / 2 + amount[0]
     *        = (amount[2] + amount[1] + amount[0]) / 2
     *     if Exceed is odd: ((Exceed - 1) / 2) + amount[0] + 1 is the minimum number of seconds needed
     *     => ((Exceed - 1) / 2) + amount[0] + 1
     *        = (amount[2] + amount[1] - amount[0] - 1) / 2 + amount[0] + 1
     *        = (amount[2] + amount[1] + amount[0] + 1) / 2
     */
    qsort(amount, amountSize, sizeof(int), compareInteger);
    if ((amount[1] + amount[2]) <= amount[0]) {
        retVal = amount[0];
    } else {
        retVal = (amount[2] + amount[1] + amount[0] + 1) / 2;
    }
#elif (MATH_2)
    printf("MATH_2\n");

    /* https://leetcode.com/problems/minimum-amount-of-time-to-fill-cups/solutions/2261394/java-c-python-max-max-a-sum-a-1-2/
     *  Let amount[2] < amount[1] < amount[0]
     *  Max between amount[0] and (amount[2] + amount[1] + amount[0] + 1) / 2 is the minimum number of seconds needed
     */
    int maxAmount = 0;
    int i;
    for (i = 0; i < amountSize; ++i) {
        maxAmount = fmax(maxAmount, amount[i]);
        retVal += amount[i];
    }
    retVal = (retVal + 1) / 2;
    retVal = fmax(retVal, maxAmount);
#endif

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define BRUTE_FORCE (0)
#define MATH_1 (0)
#define MATH_2 (1)
   public:
    int fillCups(vector<int>& amount) {
        int retVal = 0;

#if (BRUTE_FORCE)
        cout << "BRUTE_FORCE\n";

        /* Intuition
         *  142: 131, 021, 010, 000
         *  544: 434, 333, 223, 122, 111, 001, 000
         *  500: 400, 300, 200, 100, 000
         */
        sort(amount.begin(), amount.end(), [](const int& n1, const int& n2) {
            // descending order
            return (n1 > n2);
        });
        while (amount[0] > 0) {
            if (amount[0] > 0) {
                amount[0] -= 1;
            }

            if (amount[1] > 0) {
                amount[1] -= 1;
            }

            ++retVal;

            sort(amount.begin(), amount.end(), [](const int& n1, const int& n2) {
                // descending order
                return (n1 > n2);
            });
        }
#elif (MATH_1)
        cout << "MATH_1\n";

        /* https://leetcode.cn/problems/minimum-amount-of-time-to-fill-cups/solutions/1658941/by-tsreaper-158c/
         *  Let amount[2] < amount[1] < amount[0]
         *  1. If amount[2] + amount[1] <= amount[0]
         *     => amount[0] is the minimum number of seconds needed
         *  2. If amount[2] + amount[1] > amount[0]
         *     Let Exceed = amount[2] + amount[1] - amount[0]
         *     if Exceed is even: (Exceed / 2) + amount[0] is the minimum number of seconds needed
         *     => (Exceed / 2) + amount[0]
         *        = (amount[2] + amount[1] - amount[0]) / 2 + amount[0]
         *        = (amount[2] + amount[1] + amount[0]) / 2
         *     if Exceed is odd: ((Exceed - 1) / 2) + amount[0] + 1 is the minimum number of seconds needed
         *     => ((Exceed - 1) / 2) + amount[0] + 1
         *        = (amount[2] + amount[1] - amount[0] - 1) / 2 + amount[0] + 1
         *        = (amount[2] + amount[1] + amount[0] + 1) / 2
         */
        sort(amount.begin(), amount.end());
        if (amount[0] + amount[1] <= amount[2]) {
            retVal = amount[2];
        } else {
            retVal = (amount[0] + amount[1] + amount[2] + 1) / 2;
        }
#elif (MATH_2)
        cout << "MATH_2\n";

        /* https://leetcode.com/problems/minimum-amount-of-time-to-fill-cups/solutions/2261394/java-c-python-max-max-a-sum-a-1-2/
         *  Let amount[2] < amount[1] < amount[0]
         *  Max between amount[0] and (amount[2] + amount[1] + amount[0] + 1) / 2 is the minimum number of seconds
         * needed
         */
        int maxAmount = 0;
        for (auto n : amount) {
            maxAmount = max(maxAmount, n);
            retVal += n;
        }
        retVal = (retVal + 1) / 2;
        retVal = max(retVal, maxAmount);
#endif

        return retVal;
    }
};
```

</details>

## [2366. Minimum Replacements to Sort the Array](https://leetcode.com/problems/minimum-replacements-to-sort-the-array/)  2060

- [Official](https://leetcode.com/problems/minimum-replacements-to-sort-the-array/editorial/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array nums.
In one operation you can replace any element of the array with any two elements that sum to it.
- For example, consider nums = [5,6,7].
  In one operation, we can replace nums[1] with 2 and 4 and convert nums to [5,2,4,7].

Return the minimum number of operations to make an array that is sorted in non-decreasing order.

Example 1:
Input: nums = [3,9,3]
Output: 2
Explanation: Here are the steps to sort the array in non-decreasing order:
- From [3,9,3], replace the 9 with 3 and 6 so the array becomes [3,3,6,3]
- From [3,3,6,3], replace the 6 with 3 and 3 so the array becomes [3,3,3,3,3]
There are 2 steps to sort the array in non-decreasing order. Therefore, we return 2.

Example 2:
Input: nums = [1,2,3,4,5]
Output: 0
Explanation: The array is already in non-decreasing order. Therefore, we return 0.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. It is optimal to never make an operation to the last element of the array.
2. You can iterate from the second last element to the first.
   If the current value is greater than the previous bound,
   we want to break it into pieces so that the smaller one is as large as possible but not larger than the previous one.
```

</details>

</details>

<details><summary>C</summary>

```c
long long minimumReplacement(int* nums, int numsSize) {
    long long retVal = 0;

    long long operations;
    int i;
    for (i = numsSize - 2; i >= 0; --i) {
        if (nums[i] <= nums[i + 1]) {
            continue;
        }

        operations = (nums[i] + nums[i + 1] - 1) / nums[i + 1];
        retVal += (operations - 1);
        nums[i] = nums[i] / operations;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long minimumReplacement(vector<int>& nums) {
        long long retVal = 0;

        int numsSize = nums.size();
        for (int i = numsSize - 2; i >= 0; i--) {
            if (nums[i] <= nums[i + 1]) {
                continue;
            }

            long long operations = (nums[i] + nums[i + 1] - 1LL) / nums[i + 1];
            retVal += (operations - 1);
            nums[i] = nums[i] / operations;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minimumReplacement(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)
        for i in range(numsSize - 2, -1, -1):
            if nums[i] <= nums[i + 1]:
                continue

            operations = (nums[i] + nums[i + 1] - 1) // nums[i + 1]
            retVal += (operations - 1)
            nums[i] = nums[i] // operations

        return retVal
```

</details>

## [2410. Maximum Matching of Players With Trainers](https://leetcode.com/problems/maximum-matching-of-players-with-trainers/)  1381

- [Official](https://leetcode.cn/problems/maximum-matching-of-players-with-trainers/solutions/1850596/yun-dong-yuan-he-xun-lian-shi-de-zui-da-3icgd/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array players, where players[i] represents the ability of the ith player.
You are also given a 0-indexed integer array trainers,
where trainers[j] represents the training capacity of the jth trainer.

The ith player can match with the jth trainer
if the player's ability is less than or equal to the trainer's training capacity.
Additionally, the ith player can be matched with at most one trainer,
and the jth trainer can be matched with at most one player.

Return the maximum number of matchings between players and trainers that satisfy these conditions.

Example 1:
Input: players = [4,7,9], trainers = [8,2,5,8]
Output: 2
Explanation:
One of the ways we can form two matchings is as follows:
- players[0] can be matched with trainers[0] since 4 <= 8.
- players[1] can be matched with trainers[3] since 7 <= 8.
It can be proven that 2 is the maximum number of matchings that can be formed.

Example 2:
Input: players = [1,1,1], trainers = [10]
Output: 1
Explanation:
The trainer can be matched with any of the 3 players.
Each player can only be matched with one trainer, so the maximum answer is 1.

Constraints:
1 <= players.length, trainers.length <= 10^5
1 <= players[i], trainers[j] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Sort both the arrays.
2. Construct the matching greedily.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int matchPlayersAndTrainers(int* players, int playersSize, int* trainers, int trainersSize) {
    int retVal = 0;

    qsort(players, playersSize, sizeof(int), compareInteger);
    qsort(trainers, trainersSize, sizeof(int), compareInteger);

    int playersIdx = 0;
    int trainersIdx = 0;
    while ((playersIdx < playersSize) && (trainersIdx < trainersSize)) {
        while ((trainersIdx < trainersSize) && (players[playersIdx] > trainers[trainersIdx])) {
            ++trainersIdx;
        }

        if (trainersIdx < trainersSize) {
            ++retVal;
        }

        ++playersIdx;
        ++trainersIdx;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers) {
        int retVal = 0;

        sort(players.begin(), players.end());
        int playersSize = players.size();
        int playersIdx = 0;

        sort(trainers.begin(), trainers.end());
        int trainersSize = trainers.size();
        int trainersIdx = 0;

        while ((playersIdx < playersSize) && (trainersIdx < trainersSize)) {
            while ((trainersIdx < trainersSize) && (players[playersIdx] > trainers[trainersIdx])) {
                ++trainersIdx;
            }

            if (trainersIdx < trainersSize) {
                ++retVal;
            }

            ++playersIdx;
            ++trainersIdx;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def matchPlayersAndTrainers(self, players: List[int], trainers: List[int]) -> int:
        retVal = 0

        players.sort()
        playersSize = len(players)
        playersIdx = 0

        trainers.sort()
        trainersSize = len(trainers)
        trainersIdx = 0

        while (playersIdx < playersSize) and (trainersIdx < trainersSize):
            while (trainersIdx < trainersSize) and (players[playersIdx] > trainers[trainersIdx]):
                trainersIdx += 1
            retVal += 1 if trainersIdx < trainersSize else 0
            playersIdx += 1
            trainersIdx += 1

        return retVal
```

</details>

## [2551. Put Marbles in Bags](https://leetcode.com/problems/put-marbles-in-bags/)  2042

- [Official](https://leetcode.com/problems/put-marbles-in-bags/editorial/)

<details><summary>Description</summary>

```text
You have k bags. You are given a 0-indexed integer array weights where weights[i] is the weight of the ith marble.
You are also given the integer k.

Divide the marbles into the k bags according to the following rules:
- No bag is empty.
- If the ith marble and jth marble are in a bag,
  then all marbles with an index between the ith and jth indices should also be in that same bag.
- If a bag consists of all the marbles with an index from i to j inclusively,
  then the cost of the bag is weights[i] + weights[j].

The score after distributing the marbles is the sum of the costs of all the k bags.

Return the difference between the maximum and minimum scores among marble distributions.

Example 1:
Input: weights = [1,3,5,1], k = 2
Output: 4
Explanation:
The distribution [1],[3,5,1] results in the minimal score of (1+1) + (3+1) = 6.
The distribution [1,3],[5,1], results in the maximal score of (1+3) + (5+1) = 10.
Thus, we return their difference 10 - 6 = 4.

Example 2:
Input: weights = [1, 3], k = 2
Output: 0
Explanation: The only distribution possible is [1],[3].
Since both the maximal and minimal score are the same, we return 0.

Constraints:
1 <= k <= weights.length <= 10^5
1 <= weights[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Each bag will contain a sub-array.
2. Only the endpoints of the sub-array matter.
3. Try to use a priority queue.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareLonglong(const void* n1, const void* n2) {
    // ascending order
    return (*(long long*)n1 > *(long long*)n2);
}
// https://leetcode.com/problems/put-marbles-in-bags/solutions/3111736/java-c-python-3-approachs-best-o-n/
// https://leetcode.cn/problems/put-marbles-in-bags/solutions/2080577/by-wan-shi-liang-de-mang-fu-mwjh/
long long putMarbles(int* weights, int weightsSize, int k) {
    long long retVal = 0;

    /* Example: weights = [1,3,5,1], k = 2. Return the difference between the maximum and minimum scores.
     *  [1] [3,5,1]: (1+1) + (3+1) = 6  ->  6 - (1+1) = 4
     *  [1,3] [5,1]: (1+3) + (5+1) = 10 -> 10 - (1+1) = 8
     *  [1,3 5] [1]: (1+5) + (1+1) = 8  ->  8 - (1+1) = 6
     *
     *  [1,3,5,1] => [(1+3),(3+5),(5+1)] = [4,8,6]
     *
     *  1. 對weights進行兩兩求和得到map
     *  2. map中挑k-1個值，並累和得到sum
     *  3. 求出sum的最大值和最小值並做差
     */
    int mapSize = weightsSize - 1;
    if (weightsSize == 1) {
        return retVal;
    }
    long long map[mapSize];
    memset(map, 0, sizeof(map));
    for (int i = 1; i < weightsSize; i++) {
        map[i - 1] = weights[i] + weights[i - 1];
    }
    qsort(map, mapSize, sizeof(long long), compareLonglong);

    long long minimumScores = 0;
    long long maximumScores = 0;
    for (int i = 0; i < k - 1; i++) {
        minimumScores += map[i];
        maximumScores += map[mapSize - 1 - i];
    }
    retVal = maximumScores - minimumScores;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    // https://leetcode.com/problems/put-marbles-in-bags/solutions/3111736/java-c-python-3-approachs-best-o-n/
    // https://leetcode.cn/problems/put-marbles-in-bags/solutions/2080577/by-wan-shi-liang-de-mang-fu-mwjh/
    long long putMarbles(vector<int>& weights, int k) {
        long long retVal = 0;

        /* Example: weights = [1,3,5,1], k = 2. Return the difference between the maximum and minimum scores.
         *  [1] [3,5,1]: (1+1) + (3+1) = 6  ->  6 - (1+1) = 4
         *  [1,3] [5,1]: (1+3) + (5+1) = 10 -> 10 - (1+1) = 8
         *  [1,3 5] [1]: (1+5) + (1+1) = 8  ->  8 - (1+1) = 6
         *
         *  [1,3,5,1] => [(1+3),(3+5),(5+1)] = [4,8,6]
         *
         *  1. 對weights進行兩兩求和得到map
         *  2. map中挑k-1個值，並累和得到sum
         *  3. 求出sum的最大值和最小值並做差
         */
        int weightsSize = weights.size();
        vector<long long> map;
        for (int i = 1; i < weightsSize; i++) {
            map.emplace_back(weights[i] + weights[i - 1]);
        }
        sort(map.begin(), map.end());
        int mapSize = map.size();

        long long minimumScores = 0;
        long long maximumScores = 0;
        for (int i = 0; i < k - 1; i++) {
            minimumScores += map[i];
            maximumScores += map[mapSize - 1 - i];
        }
        retVal = maximumScores - minimumScores;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    # https://leetcode.com/problems/put-marbles-in-bags/solutions/3111736/java-c-python-3-approachs-best-o-n/
    # https://leetcode.cn/problems/put-marbles-in-bags/solutions/2080577/by-wan-shi-liang-de-mang-fu-mwjh/
    def putMarbles(self, weights: List[int], k: int) -> int:
        retVal = 0

        # /* Example: weights = [1,3,5,1], k = 2. Return the difference between the maximum and minimum scores.
        #  *  [1] [3,5,1]: (1+1) + (3+1) = 6  ->  6 - (1+1) = 4
        #  *  [1,3] [5,1]: (1+3) + (5+1) = 10 -> 10 - (1+1) = 8
        #  *  [1,3 5] [1]: (1+5) + (1+1) = 8  ->  8 - (1+1) = 6
        #  *
        #  *  [1,3,5,1] => [(1+3),(3+5),(5+1)] = [4,8,6]
        #  *
        #  *  1. 對weights進行兩兩求和得到map
        #  *  2. map中挑k-1個值，並累和得到sum
        #  *  3. 求出sum的最大值和最小值並做差
        #  */
        weightsSize = len(weights)
        map = []
        for i in range(1, weightsSize):
            map.append(weights[i] + weights[i - 1])
        map.sort()
        mapSize = len(map)

        minimumScores = 0
        maximumScores = 0
        for i in range(k - 1):
            minimumScores += map[i]
            maximumScores += map[mapSize - 1 - i]
        retVal = maximumScores - minimumScores

        return retVal
```

</details>

## [2870. Minimum Number of Operations to Make Array Empty](https://leetcode.com/problems/minimum-number-of-operations-to-make-array-empty/)  1392

- [Official](https://leetcode.com/problems/minimum-number-of-operations-to-make-array-empty/editorial/)

<details><summary>Description</summary>

```text
You are given a 0-indexed array nums consisting of positive integers.

There are two types of operations that you can apply on the array any number of times:
- Choose two elements with equal values and delete them from the array.
- Choose three elements with equal values and delete them from the array.

Return the minimum number of operations required to make the array empty, or -1 if it is not possible.

Example 1:
Input: nums = [2,3,3,2,2,4,2,3,4]
Output: 4
Explanation: We can apply the following operations to make the array empty:
- Apply the first operation on the elements at indices 0 and 3. The resulting array is nums = [3,3,2,4,2,3,4].
- Apply the first operation on the elements at indices 2 and 4. The resulting array is nums = [3,3,4,3,4].
- Apply the second operation on the elements at indices 0, 1, and 3. The resulting array is nums = [4,4].
- Apply the first operation on the elements at indices 0 and 1. The resulting array is nums = [].
It can be shown that we cannot make the array empty in less than 4 operations.

Example 2:
Input: nums = [2,1,2,2,3,3]
Output: -1
Explanation: It is impossible to empty the array.

Constraints:
2 <= nums.length <= 10^5
1 <= nums[i] <= 10^6
```

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int minOperations(int* nums, int numsSize) {
    int retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int count = 1;
    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[i - 1] == nums[i]) {
            count++;
            continue;
        }

        if (count == 1) {
            retVal = -1;
            return retVal;
        }
        retVal += (count / 3);
        if (count % 3 != 0) {
            retVal += 1;
        }

        count = 1;
    }
    if (count == 1) {
        retVal = -1;
        return retVal;
    }
    retVal += (count / 3);
    if (count % 3 != 0) {
        retVal += 1;
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

        unordered_map<int, int> hashTable;
        for (int num : nums) {
            auto iterator = hashTable.find(num);
            if (iterator != hashTable.end()) {
                hashTable[num]++;
            } else {
                hashTable[num] = 1;
            }
        }

        for (auto iterator : hashTable) {
            int times = iterator.second;
            if (times == 1) {
                retVal = -1;
                break;
            }

            retVal += (times / 3);
            if (times % 3 != 0) {
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
    def minOperations(self, nums: List[int]) -> int:
        retVal = 0

        count = Counter(nums)
        for times in count.values():
            if times == 1:
                retVal = -1
                break

            operations = times // 3
            if times % 3 == 0:
                retVal += operations
            else:
                retVal += (operations + 1)

        return retVal
```

</details>

## [2966. Divide Array Into Arrays With Max Difference](https://leetcode.com/problems/divide-array-into-arrays-with-max-difference/)  1395

- [Official](https://leetcode.com/problems/divide-array-into-arrays-with-max-difference/editorial/)

<details><summary>Description</summary>

```text
You are given an integer array nums of size n and a positive integer k.

Divide the array into one or more arrays of size 3 satisfying the following conditions:
- Each element of nums should be in exactly one array.
- The difference between any two elements in one array is less than or equal to k.

Return a 2D array containing all the arrays.
If it is impossible to satisfy the conditions, return an empty array.
And if there are multiple answers, return any of them.

Example 1:
Input: nums = [1,3,4,8,7,9,3,5,1], k = 2
Output: [[1,1,3],[3,4,5],[7,8,9]]
Explanation: We can divide the array into the following arrays: [1,1,3], [3,4,5] and [7,8,9].
The difference between any two elements in each array is less than or equal to 2.
Note that the order of elements is not important.

Example 2:
Input: nums = [1,3,3,2,7,3], k = 3
Output: []
Explanation: It is not possible to divide the array satisfying all the conditions.

Constraints:
n == nums.length
1 <= n <= 10^5
n is a multiple of 3.
1 <= nums[i] <= 10^5
1 <= k <= 10^5
```

<details><summary>Hint</summary>

```text
1. Try to use a greedy approach.
2. Sort the array and try to group each 3 consecutive elements.
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
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** divideArray(int* nums, int numsSize, int k, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    if (numsSize % 3 != 0) {
        return pRetVal;
    }
    (*returnSize) = numsSize / 3;

    pRetVal = (int**)malloc((*returnSize) * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        goto exit1;
    }
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        goto exit2;
    }
    memset((*returnColumnSizes), 0, ((*returnSize) * sizeof(int)));

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int i, j;
    for (i = 0; i < (*returnSize); ++i) {
        if (nums[3 * i + 2] - nums[3 * i] > k) {
            goto exit3;
        }

        pRetVal[i] = (int*)malloc(3 * sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            goto exit3;
        }
        memset(pRetVal[i], 0, (3 * sizeof(int)));
        (*returnColumnSizes)[i] = 3;
        pRetVal[i][0] = nums[3 * i];
        pRetVal[i][1] = nums[3 * i + 1];
        pRetVal[i][2] = nums[3 * i + 2];
    }

    return pRetVal;

exit3:
    for (j = 0; j < i; ++j) {
        free(pRetVal[j]);
        pRetVal[j] = NULL;
    }
    free((*returnColumnSizes));
    (*returnColumnSizes) = NULL;

exit2:
    free(pRetVal);
    pRetVal = NULL;

exit1:
    (*returnSize) = 0;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<vector<int>> divideArray(vector<int>& nums, int k) {
        vector<vector<int>> retVal;

        int numsSize = nums.size();
        if (numsSize % 3 != 0) {
            return retVal;
        }

        sort(nums.begin(), nums.end());
        for (int i = 0; i < numsSize; i += 3) {
            if (nums[i + 2] - nums[i] > k) {
                retVal = {};
                break;
            }

            retVal.push_back({nums[i], nums[i + 1], nums[i + 2]});
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def divideArray(self, nums: List[int], k: int) -> List[List[int]]:
        retVal = []

        numsSize = len(nums)
        if (numsSize % 3) != 0:
            return retVal

        nums.sort()
        for i in range(0, numsSize, 3):
            if (nums[i+2] - nums[i]) > k:
                retVal = []
                break
            retVal.append([nums[i], nums[i+1], nums[i+2]])

        return retVal
```

</details>

## [2971. Find Polygon With the Largest Perimeter](https://leetcode.com/problems/find-polygon-with-the-largest-perimeter/)  1521

- [Official](https://leetcode.com/problems/find-polygon-with-the-largest-perimeter/editorial/)

<details><summary>Description</summary>

```text
You are given an array of positive integers nums of length n.

A polygon is a closed plane figure that has at least 3 sides.
The longest side of a polygon is smaller than the sum of its other sides.

Conversely, if you have k (k >= 3) positive real numbers a1, a2, a3, ..., ak
where a1 <= a2 <= a3 <= ... <= ak and a1 + a2 + a3 + ... + ak-1 > ak,
then there always exists a polygon with k sides whose lengths are a1, a2, a3, ..., ak.

The perimeter of a polygon is the sum of lengths of its sides.

Return the largest possible perimeter of a polygon whose sides can be formed from nums,
or -1 if it is not possible to create a polygon.

Example 1:
Input: nums = [5,5,5]
Output: 15
Explanation: The only possible polygon that can be made from nums has 3 sides: 5, 5, and 5.
The perimeter is 5 + 5 + 5 = 15.

Example 2:
Input: nums = [1,12,1,2,5,50,3]
Output: 12
Explanation: The polygon with the largest perimeter which can be made from nums has 5 sides: 1, 1, 2, 3, and 5.
The perimeter is 1 + 1 + 2 + 3 + 5 = 12.
We cannot have a polygon with either 12 or 50 as the longest side
because it is not possible to include 2 or more smaller sides that have a greater sum than either of them.
It can be shown that the largest possible perimeter is 12.

Example 3:
Input: nums = [5,5,50]
Output: -1
Explanation: There is no possible way to form a polygon from nums, as a polygon has at least 3 sides and 50 > 5 + 5.

Constraints:
3 <= n <= 10^5
1 <= nums[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Sort the array.
2. Use greedy algorithm. If we select an edge as the longest side,
   it is always better to pick up all the edges with length no longer than this longest edge.
3. Note that the number of edges should not be less than 3.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
long long largestPerimeter(int* nums, int numsSize) {
    long long retVal = -1;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    long long sum = nums[0] + nums[1];
    int i;
    for (i = 2; i < numsSize; ++i) {
        if (sum > nums[i]) {
            retVal = sum + nums[i];
        }
        sum += nums[i];
    }
    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long largestPerimeter(vector<int>& nums) {
        long long retVal = -1;

        int numsSize = nums.size();

        sort(nums.begin(), nums.end());
        long long sum = nums[0] + nums[1];
        for (int i = 2; i < numsSize; ++i) {
            if (sum > nums[i]) {
                retVal = sum + nums[i];
            }
            sum += nums[i];
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
        retVal = -1

        numsSize = len(nums)

        nums.sort()
        sum = nums[0] + nums[1]
        for i in range(2, numsSize):
            if sum > nums[i]:
                retVal = sum + nums[i]
            sum += nums[i]

        return retVal
```

</details>

## [3075. Maximize Happiness of Selected Children](https://leetcode.com/problems/maximize-happiness-of-selected-children/)  1325

- [Official](https://leetcode.com/problems/maximize-happiness-of-selected-children/editorial/)

<details><summary>Description</summary>

```text
You are given an array happiness of length n, and a positive integer k.

There are n children standing in a queue, where the ith child has happiness value happiness[i].
You want to select k children from these n children in k turns.

In each turn, when you select a child,
the happiness value of all the children that have not been selected till now decreases by 1.
Note that the happiness value cannot become negative and gets decremented only if it is positive.

Return the maximum sum of the happiness values of the selected children you can achieve by selecting k children.

Example 1:
Input: happiness = [1,2,3], k = 2
Output: 4
Explanation: We can pick 2 children in the following way:
- Pick the child with the happiness value == 3. The happiness value of the remaining children becomes [0,1].
- Pick the child with the happiness value == 1. The happiness value of the remaining child becomes [0].
  Note that the happiness value cannot become less than 0.
The sum of the happiness values of the selected children is 3 + 1 = 4.

Example 2:
Input: happiness = [1,1,1,1], k = 2
Output: 1
Explanation: We can pick 2 children in the following way:
- Pick any child with the happiness value == 1. The happiness value of the remaining children becomes [0,0,0].
- Pick the child with the happiness value == 0. The happiness value of the remaining child becomes [0,0].
The sum of the happiness values of the selected children is 1 + 0 = 1.

Example 3:
Input: happiness = [2,3,4,5], k = 1
Output: 5
Explanation: We can pick 1 child in the following way:
- Pick the child with the happiness value == 5. The happiness value of the remaining children becomes [1,2,3].
The sum of the happiness values of the selected children is 5.

Constraints:
1 <= n == happiness.length <= 2 * 10^5
1 <= happiness[i] <= 10^8
1 <= k <= n
```

<details><summary>Hint</summary>

```text
1. Since all the unselected numbers are decreasing at the same rate, we should greedily select k largest values.
2. The ith largest number (i = 1, 2, 3,…k) should decrease by (i - 1) when it is picked.
3. Add 0 if the decreased value is negative.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
long long maximumHappinessSum(int* happiness, int happinessSize, int k) {
    long long retVal = 0;

    qsort(happiness, happinessSize, sizeof(int), compareInteger);
    int happy;
    int i;
    for (i = 0; i < k; ++i) {
        happy = happiness[i] - i;
        if (happy <= 0) {
            break;
        }
        retVal += happy;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long maximumHappinessSum(vector<int>& happiness, int k) {
        long long retVal = 0;

        sort(happiness.begin(), happiness.end(), greater<int>());
        for (int i = 0; i < k; ++i) {
            int happy = happiness[i] - i;
            if (happy <= 0) {
                break;
            }
            retVal += happy;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maximumHappinessSum(self, happiness: List[int], k: int) -> int:
        retVal = 0

        happiness.sort(reverse=True)
        for i in range(k):
            happy = happiness[i] - i
            if happy <= 0:
                break
            retVal += happy

        return retVal
```

</details>
