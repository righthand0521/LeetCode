# Array

## [3105. Longest Strictly Increasing or Strictly Decreasing Subarray](https://leetcode.com/problems/longest-strictly-increasing-or-strictly-decreasing-subarray/)  1217

- [Official](https://leetcode.com/problems/longest-strictly-increasing-or-strictly-decreasing-subarray/editorial/)

<details><summary>Description</summary>

```text
You are given an array of integers nums.
Return the length of the longest subarray of nums which is either strictly increasing or strictly decreasing.

Example 1:
Input: nums = [1,4,3,3,2]
Output: 2
Explanation:
The strictly increasing subarrays of nums are [1], [2], [3], [3], [4], and [1,4].
The strictly decreasing subarrays of nums are [1], [2], [3], [3], [4], [3,2], and [4,3].
Hence, we return 2.

Example 2:
Input: nums = [3,3,3,3]
Output: 1
Explanation:
The strictly increasing subarrays of nums are [3], [3], [3], and [3].
The strictly decreasing subarrays of nums are [3], [3], [3], and [3].
Hence, we return 1.

Example 3:
Input: nums = [3,2,1]
Output: 3
Explanation:
The strictly increasing subarrays of nums are [3], [2], and [1].
The strictly decreasing subarrays of nums are [3], [2], [1], [3,2], [2,1], and [3,2,1].
Hence, we return 3.

Constraints:
1 <= nums.length <= 50
1 <= nums[i] <= 50
```

</details>

<details><summary>C</summary>

```c
int longestMonotonicSubarray(int* nums, int numsSize) {
    int retVal = 1;

    int increasing = 1;
    int decreasing = 1;
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i - 1] < nums[i]) {
            increasing += 1;
            decreasing = 1;
        } else if (nums[i - 1] > nums[i]) {
            decreasing += 1;
            increasing = 1;
        } else {
            increasing = 1;
            decreasing = 1;
        }
        retVal = fmax(retVal, fmax(increasing, decreasing));
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int longestMonotonicSubarray(vector<int>& nums) {
        int retVal = 1;

        int numsSize = nums.size();

        int increasing = 1;
        int decreasing = 1;
        for (int i = 1; i < numsSize; ++i) {
            if (nums[i - 1] < nums[i]) {
                increasing += 1;
                decreasing = 1;
            } else if (nums[i - 1] > nums[i]) {
                decreasing += 1;
                increasing = 1;
            } else {
                increasing = 1;
                decreasing = 1;
            }
            retVal = max(retVal, max(increasing, decreasing));
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def longestMonotonicSubarray(self, nums: List[int]) -> int:
        retVal = 1

        numsSize = len(nums)

        increasing = 1
        decreasing = 1
        for i in range(1, numsSize):
            if (nums[i-1] < nums[i]):
                increasing += 1
                decreasing = 1
            elif (nums[i-1] > nums[i]):
                decreasing += 1
                increasing = 1
            else:
                increasing = 1
                decreasing = 1
            retVal = max(retVal, max(increasing, decreasing))

        return retVal
```

</details>

## [3151. Special Array I](https://leetcode.com/problems/special-array-i/)  1152

- [Official](https://leetcode.com/problems/special-array-i/editorial/)
- [Official](https://leetcode.cn/problems/special-array-i/solutions/2872838/te-shu-shu-zu-i-by-leetcode-solution-kpjn/)

<details><summary>Description</summary>

```text
An array is considered special if every pair of its adjacent elements contains two numbers with different parity.

You are given an array of integers nums. Return true if nums is a special array, otherwise, return false.

Example 1:
Input: nums = [1]
Output: true
Explanation:
There is only one element. So the answer is true.

Example 2:
Input: nums = [2,1,4]
Output: true
Explanation:
There is only two pairs: (2,1) and (1,4), and both of them contain numbers with different parity. So the answer is true.

Example 3:
Input: nums = [4,3,1,6]
Output: false
Explanation:
nums[1] and nums[2] are both odd. So the answer is false.

Constraints:
1 <= nums.length <= 100
1 <= nums[i] <= 100
```

<details><summary>Hint</summary>

```text
1. Try to check the parity of each element and its previous element.
```

</details>

</details>

<details><summary>C</summary>

```c
bool isArraySpecial(int* nums, int numsSize) {
    bool retVal = true;

    for (int i = 1; i < numsSize; ++i) {
        if (nums[i - 1] % 2 == nums[i] % 2) {
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
    bool isArraySpecial(vector<int>& nums) {
        bool retVal = true;

        int numsSize = nums.size();
        for (int i = 1; i < numsSize; ++i) {
            if (nums[i - 1] % 2 == nums[i] % 2) {
                retVal = false;
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
    def isArraySpecial(self, nums: List[int]) -> bool:
        retVal = True

        numsSize = len(nums)
        for i in range(1, numsSize):
            if nums[i-1] % 2 == nums[i] % 2:
                retVal = False
                break

        return retVal
```

</details>

## [3206. Alternating Groups I](https://leetcode.com/problems/alternating-groups-i/)  1223

- [Official](https://leetcode.cn/problems/alternating-groups-i/)

<details><summary>Description</summary>

```text
There is a circle of red and blue tiles. You are given an array of integers colors.
The color of tile i is represented by colors[i]:
- colors[i] == 0 means that tile i is red.
- colors[i] == 1 means that tile i is blue.

Every 3 contiguous tiles in the circle with alternating colors
(the middle tile has a different color from its left and right tiles) is called an alternating group.

Return the number of alternating groups.

Note that since colors represents a circle, the first and the last tiles are considered to be next to each other.

Example 1:
Input: colors = [1,1,1]
Output: 0

Example 2:
Input: colors = [0,1,0,0,1]
Output: 3

Constraints:
3 <= colors.length <= 100
0 <= colors[i] <= 1
```

<details><summary>Hint</summary>

```text
1. For each tile, check that the previous and the next tile have different colors from that tile or not.
```

</details>

</details>

<details><summary>C</summary>

```c
int numberOfAlternatingGroups(int* colors, int colorsSize) {
    int retVal = 0;

    for (int i = 0; i < colorsSize; ++i) {
        if (colors[i] == colors[(i - 1 + colorsSize) % colorsSize]) {
            continue;
        } else if (colors[i] == colors[(i + 1) % colorsSize]) {
            continue;
        }
        retVal++;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int numberOfAlternatingGroups(vector<int>& colors) {
        int retVal = 0;

        int colorsSize = colors.size();
        for (int i = 0; i < colorsSize; ++i) {
            if (colors[i] == colors[(i - 1 + colorsSize) % colorsSize]) {
                continue;
            } else if (colors[i] == colors[(i + 1) % colorsSize]) {
                continue;
            }
            retVal++;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def numberOfAlternatingGroups(self, colors: List[int]) -> int:
        retVal = 0

        colorsSize = len(colors)
        for i in range(colorsSize):
            if colors[i] == colors[(i-1+colorsSize) % colorsSize]:
                continue
            elif colors[i] == colors[(i+1) % colorsSize]:
                continue
            retVal += 1

        return retVal
```

</details>

## [3208. Alternating Groups II](https://leetcode.com/problems/alternating-groups-ii/)  1721

- [Official](https://leetcode.com/problems/alternating-groups-ii/editorial/)
- [Official](https://leetcode.cn/problems/alternating-groups-ii/solutions/2986846/jiao-ti-zu-ii-by-leetcode-solution-7912/)

<details><summary>Description</summary>

```text
There is a circle of red and blue tiles. You are given an array of integers colors and an integer k.
The color of tile i is represented by colors[i]:
- colors[i] == 0 means that tile i is red.
- colors[i] == 1 means that tile i is blue.

An alternating group is every k contiguous tiles in the circle with alternating colors
(each tile in the group except the first and last one has a different color from its left and right tiles).

Return the number of alternating groups.

Note that since colors represents a circle, the first and the last tiles are considered to be next to each other.

Example 1:
Input: colors = [0,1,0,1,0], k = 3
Output: 3

Example 2:
Input: colors = [0,1,0,0,1,0,1], k = 6
Output: 2

Example 3:
Input: colors = [1,1,0,1], k = 4
Output: 0

Constraints:
3 <= colors.length <= 10^5
0 <= colors[i] <= 1
3 <= k <= colors.length
```

<details><summary>Hint</summary>

```text
1. Try to find a tile that has the same color as its next tile (if it exists).
2. Then try to find maximal alternating groups by starting a single for loop from that tile.
```

</details>

</details>

<details><summary>C</summary>

```c
int numberOfAlternatingGroups(int* colors, int colorsSize, int k) {
    int retVal = 0;

    int index;
    int alternatingElementsCount = 1;
    int lastColor = colors[0];
    for (int i = 1; i < colorsSize + k - 1; i++) {
        index = i % colorsSize;

        // Check if current color is the same as last color
        if (colors[index] == lastColor) {
            // Pattern breaks, reset sequence length
            alternatingElementsCount = 1;
            lastColor = colors[index];
            continue;
        }

        // Extend alternating sequence
        alternatingElementsCount += 1;

        // If sequence length reaches at least k, count it
        if (alternatingElementsCount >= k) {
            retVal++;
        }

        lastColor = colors[index];
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int numberOfAlternatingGroups(vector<int>& colors, int k) {
        int retVal = 0;

        int colorsSize = colors.size();
        int alternatingElementsCount = 1;
        int lastColor = colors[0];
        for (int i = 1; i < colorsSize + k - 1; i++) {
            int index = i % colorsSize;

            // Check if current color is the same as last color
            if (colors[index] == lastColor) {
                // Pattern breaks, reset sequence length
                alternatingElementsCount = 1;
                lastColor = colors[index];
                continue;
            }

            // Extend alternating sequence
            alternatingElementsCount += 1;

            // If sequence length reaches at least k, count it
            if (alternatingElementsCount >= k) {
                retVal++;
            }

            lastColor = colors[index];
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def numberOfAlternatingGroups(self, colors: List[int], k: int) -> int:
        retVal = 0

        colorsSize = len(colors)
        alternatingElementsCount = 1
        lastColor = colors[0]
        for i in range(1, colorsSize + k - 1):
            index = i % colorsSize

            # Check if current color is the same as the last color
            if colors[index] == lastColor:
                # Pattern breaks, reset sequence length
                alternatingElementsCount = 1
                lastColor = colors[index]
                continue

            # Extend sequence
            alternatingElementsCount += 1

            # If sequence length reaches at least k, count it
            if alternatingElementsCount >= k:
                retVal += 1

            lastColor = colors[index]

        return retVal
```

</details>

## [3392. Count Subarrays of Length Three With a Condition](https://leetcode.com/problems/count-subarrays-of-length-three-with-a-condition/)  1200

- [Official](https://leetcode.com/problems/count-subarrays-of-length-three-with-a-condition/editorial/)
- [Official](https://leetcode.cn/problems/count-subarrays-of-length-three-with-a-condition/solutions/3651614/tong-ji-fu-he-tiao-jian-chang-du-wei-3-d-t7rt/)

<details><summary>Description</summary>

```text
Given an integer array nums, return the number of subarrays of length 3
such that the sum of the first and third numbers equals exactly half of the second number.

Example 1:
Input: nums = [1,2,1,4,1]
Output: 1
Explanation:
Only the subarray [1,4,1] contains exactly 3 elements
where the sum of the first and third numbers equals half the middle number.

Example 2:
Input: nums = [1,1,1]
Output: 0
Explanation:
[1,1,1] is the only subarray of length 3. However, its first and third numbers do not add to half the middle number.

Constraints:
3 <= nums.length <= 100
-100 <= nums[i] <= 100
```

<details><summary>Hint</summary>

```text
1. The constraints are small. Consider checking every subarray.
```

</details>

</details>

<details><summary>C</summary>

```c
int countSubarrays(int* nums, int numsSize) {
    int retVal = 0;

    for (int i = 0; i < numsSize - 2; ++i) {
        if (2 * (nums[i] + nums[i + 2]) == nums[i + 1]) {
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
    int countSubarrays(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        for (int i = 0; i < numsSize - 2; ++i) {
            if (2 * (nums[i] + nums[i + 2]) == nums[i + 1]) {
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
    def countSubarrays(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)
        for i in range(numsSize-2):
            if 2 * (nums[i] + nums[i+2]) == nums[i+1]:
                retVal += 1

        return retVal
```

</details>

## [3423. Maximum Difference Between Adjacent Elements in a Circular Array](https://leetcode.com/problems/maximum-difference-between-adjacent-elements-in-a-circular-array/)  1184

- [Official](https://leetcode.com/problems/maximum-difference-between-adjacent-elements-in-a-circular-array/editorial/)
- [Official](https://leetcode.cn/problems/maximum-difference-between-adjacent-elements-in-a-circular-array/solutions/3692736/xun-huan-shu-zu-zhong-xiang-lin-yuan-su-q5nq3/)

<details><summary>Description</summary>

```text
Given a circular array nums, find the maximum absolute difference between adjacent elements.

Note: In a circular array, the first and last elements are adjacent.

Example 1:
Input: nums = [1,2,4]
Output: 3
Explanation:
Because nums is circular, nums[0] and nums[2] are adjacent. They have the maximum absolute difference of |4 - 1| = 3.

Example 2:
Input: nums = [-5,-10,-5]
Output: 5
Explanation:
The adjacent elements nums[0] and nums[1] have the maximum absolute difference of |-5 - (-10)| = 5.

Constraints:
2 <= nums.length <= 100
-100 <= nums[i] <= 100
```

<details><summary>Hint</summary>

```text
1. Traverse from the second element to the last element and check the difference of every adjacent pair.
2. The edge case is to check the difference between the first and last elements.
```

</details>

</details>

<details><summary>C</summary>

```c
int maxAdjacentDistance(int* nums, int numsSize) {
    int retVal = 0;

    retVal = fmax(retVal, abs(nums[0] - nums[numsSize - 1]));
    for (int i = 1; i < numsSize; ++i) {
        retVal = fmax(retVal, abs(nums[i] - nums[i - 1]));
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxAdjacentDistance(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        retVal = max(retVal, abs(nums[0] - nums[numsSize - 1]));
        for (int i = 1; i < numsSize; ++i) {
            retVal = max(retVal, abs(nums[i] - nums[i - 1]));
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxAdjacentDistance(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)
        retVal = max(retVal, abs(nums[0] - nums[numsSize-1]))
        for i in range(1, numsSize):
            retVal = max(retVal, abs(nums[i] - nums[i-1]))

        return retVal
```

</details>
