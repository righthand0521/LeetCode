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

## [3195. Find the Minimum Area to Cover All Ones I](https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-i/)  1348

- [Official](https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-i/editorial/)
- [Official](https://leetcode.cn/problems/find-the-minimum-area-to-cover-all-ones-i/solutions/3751483/bao-han-suo-you-1-de-zui-xiao-ju-xing-mi-zty7/)

<details><summary>Description</summary>

```text
You are given a 2D binary array grid. Find a rectangle with horizontal and vertical sides with the smallest area,
such that all the 1's in grid lie inside this rectangle.

Return the minimum possible area of the rectangle.

Example 1:
Input: grid = [[0,1,0],[1,0,1]]
Output: 6
Explanation:
The smallest rectangle has a height of 2 and a width of 3, so it has an area of 2 * 3 = 6.

Example 2:
Input: grid = [[1,0],[0,0]]
Output: 1
Explanation:
The smallest rectangle has both height and width 1, so its area is 1 * 1 = 1.

Constraints:
1 <= grid.length, grid[i].length <= 1000
grid[i][j] is either 0 or 1.
The input is generated such that there is at least one 1 in grid.
```

<details><summary>Hint</summary>

```text
1. Find the minimum and maximum coordinates of a cell with a value of 1 in both directions.
```

</details>

</details>

<details><summary>C</summary>

```c
int minimumArea(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int rowSize = gridSize;
    int colSize = gridColSize[0];

    int minRow = rowSize;
    int maxRow = 0;
    int minCol = colSize;
    int maxCol = 0;
    for (int x = 0; x < rowSize; x++) {
        for (int y = 0; y < colSize; y++) {
            if (grid[x][y] == 1) {
                minRow = fmin(minRow, x);
                maxRow = fmax(maxRow, x);
                minCol = fmin(minCol, y);
                maxCol = fmax(maxCol, y);
            }
        }
    }
    retVal = (maxRow - minRow + 1) * (maxCol - minCol + 1);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minimumArea(vector<vector<int>>& grid) {
        int retVal = 0;

        int gridSize = grid.size();
        int gridColSize = grid[0].size();

        int minRow = gridSize;
        int maxRow = 0;
        int minCol = gridColSize;
        int maxCol = 0;
        for (int x = 0; x < gridSize; x++) {
            for (int y = 0; y < gridColSize; y++) {
                if (grid[x][y] == 1) {
                    minRow = min(minRow, x);
                    maxRow = max(maxRow, x);
                    minCol = min(minCol, y);
                    maxCol = max(maxCol, y);
                }
            }
        }
        retVal = (maxRow - minRow + 1) * (maxCol - minCol + 1);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minimumArea(self, grid: List[List[int]]) -> int:
        retVal = 0

        gridSize = len(grid)
        gridColSize = len(grid[0])

        minRow = gridSize
        maxRow = 0
        minCol = gridColSize
        maxCol = 0
        for x in range(gridSize):
            for y in range(gridColSize):
                if grid[x][y] == 1:
                    minRow = min(minRow, x)
                    maxRow = max(maxRow, x)
                    minCol = min(minCol, y)
                    maxCol = max(maxCol, y)

        retVal = (maxRow - minRow + 1) * (maxCol - minCol + 1)

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

## [3480. Maximize Subarrays After Removing One Conflicting Pair](https://leetcode.com/problems/maximize-subarrays-after-removing-one-conflicting-pair/)  2763

- [Official](https://leetcode.com/problems/maximize-subarrays-after-removing-one-conflicting-pair/editorial/)
- [Official](https://leetcode.cn/problems/maximize-subarrays-after-removing-one-conflicting-pair/solutions/3730080/shan-chu-yi-ge-chong-tu-dui-hou-zui-da-z-lquv/)

<details><summary>Description</summary>

```text
You are given an integer n which represents an array nums containing the numbers from 1 to n in order.
Additionally, you are given a 2D array conflictingPairs,
where conflictingPairs[i] = [a, b] indicates that a and b form a conflicting pair.

Remove exactly one element from conflictingPairs.
Afterward, count the number of non-empty subarrays of nums
which do not contain both a and b for any remaining conflicting pair [a, b].

Return the maximum number of subarrays possible after removing exactly one conflicting pair.

Example 1:
Input: n = 4, conflictingPairs = [[2,3],[1,4]]
Output: 9
Explanation:
Remove [2, 3] from conflictingPairs. Now, conflictingPairs = [[1, 4]].
There are 9 subarrays in nums where [1, 4] do not appear together.
They are [1], [2], [3], [4], [1, 2], [2, 3], [3, 4], [1, 2, 3] and [2, 3, 4].
The maximum number of subarrays we can achieve after removing one element from conflictingPairs is 9.

Example 2:
Input: n = 5, conflictingPairs = [[1,2],[2,5],[3,5]]
Output: 12
Explanation:
Remove [1, 2] from conflictingPairs. Now, conflictingPairs = [[2, 5], [3, 5]].
There are 12 subarrays in nums where [2, 5] and [3, 5] do not appear together.
The maximum number of subarrays we can achieve after removing one element from conflictingPairs is 12.

Constraints:
2 <= n <= 10^5
1 <= conflictingPairs.length <= 2 * n
conflictingPairs[i].length == 2
1 <= conflictingPairs[i][j] <= n
conflictingPairs[i][0] != conflictingPairs[i][1]
```

<details><summary>Hint</summary>

```text
1. Let f[i] (where i = 1, 2, 3, ..., n) be the end index of the longest valid subarray (without any conflicting pair)
   starting at index i.
2. The answer is: sigma(f[i] - i + 1) for i in [1..n], which simplifies to: sigma(f[i]) - n * (n + 1) / 2 + n.
3. Focus on maintaining f[i].
4. If we have a conflicting pair (x, y) with x < y:
   1. Sort the conflicting pairs by y values in non-increasing order.
   2. Update each prefix of the f array accordingly.
5. Use a segment tree or another suitable data structure to maintain the range update and sum query efficiently.
```

</details>

</details>

<details><summary>C</summary>

```c
long long maxSubarrays(int n, int **conflictingPairs, int conflictingPairsSize, int *conflictingPairsColSize) {
    long long retVal = 0;

    int *bMin1 = (int *)malloc((n + 1) * sizeof(int));
    if (bMin1 == NULL) {
        perror("malloc");
        return retVal;
    }
    int *bMin2 = (int *)malloc((n + 1) * sizeof(int));
    if (bMin2 == NULL) {
        perror("malloc");
        free(bMin1);
        return retVal;
    }
    for (int i = 0; i <= n; i++) {
        bMin1[i] = INT_MAX;
        bMin2[i] = INT_MAX;
    }
    int a, b;
    for (int i = 0; i < conflictingPairsSize; i++) {
        a = fmin(conflictingPairs[i][0], conflictingPairs[i][1]);
        b = fmax(conflictingPairs[i][0], conflictingPairs[i][1]);
        if (bMin1[a] > b) {
            bMin2[a] = bMin1[a];
            bMin1[a] = b;
        } else if (bMin2[a] > b) {
            bMin2[a] = b;
        }
    }

    long long *delCount = (long long *)calloc(n + 1, sizeof(long long));
    if (delCount == NULL) {
        perror("malloc");
        free(bMin1);
        free(bMin2);
        return retVal;
    }
    int ib1 = n;
    int b2 = INT_MAX;
    for (int i = n; i >= 1; i--) {
        if (bMin1[ib1] > bMin1[i]) {
            b2 = fmin(b2, bMin1[ib1]);
            ib1 = i;
        } else {
            b2 = fmin(b2, bMin1[i]);
        }
        retVal += (fmin(bMin1[ib1], n + 1) - i);
        delCount[ib1] += (fmin(fmin(b2, bMin2[ib1]), n + 1) - fmin(bMin1[ib1], n + 1));
    }
    long long max = 0;
    for (int i = 0; i <= n; i++) {
        if (delCount[i] > max) {
            max = delCount[i];
        }
    }
    retVal += max;

    //
    free(bMin1);
    free(bMin2);
    free(delCount);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long maxSubarrays(int n, vector<vector<int>>& conflictingPairs) {
        long long retVal = 0;

        vector<int> bMin1(n + 1, numeric_limits<int>::max());
        vector<int> bMin2(n + 1, numeric_limits<int>::max());
        for (const auto& pair : conflictingPairs) {
            int a = min(pair[0], pair[1]);
            int b = max(pair[0], pair[1]);
            if (bMin1[a] > b) {
                bMin2[a] = bMin1[a];
                bMin1[a] = b;
            } else if (bMin2[a] > b) {
                bMin2[a] = b;
            }
        }

        int ib1 = n;
        int b2 = numeric_limits<int>::max();
        vector<long long> delCount(n + 1, 0);
        for (int i = n; i >= 1; i--) {
            if (bMin1[ib1] > bMin1[i]) {
                b2 = min(b2, bMin1[ib1]);
                ib1 = i;
            } else {
                b2 = min(b2, bMin1[i]);
            }
            retVal += (min(bMin1[ib1], n + 1) - i);
            delCount[ib1] += (min(min(b2, bMin2[ib1]), n + 1) - min(bMin1[ib1], n + 1));
        }
        retVal += *max_element(delCount.begin(), delCount.end());

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxSubarrays(self, n: int, conflictingPairs: List[List[int]]) -> int:
        retVal = 0

        bMin1 = [2**31 - 1] * (n + 1)
        bMin2 = [2**31 - 1] * (n + 1)
        for pair in conflictingPairs:
            a = min(pair[0], pair[1])
            b = max(pair[0], pair[1])
            if bMin1[a] > b:
                bMin2[a] = bMin1[a]
                bMin1[a] = b
            elif bMin2[a] > b:
                bMin2[a] = b

        ib1 = n
        b2 = 0x3FFFFFFF
        delCount = [0] * (n + 1)
        for i in range(n, 0, -1):
            if bMin1[ib1] > bMin1[i]:
                b2 = min(b2, bMin1[ib1])
                ib1 = i
            else:
                b2 = min(b2, bMin1[i])
            retVal += min(bMin1[ib1], n + 1) - i
            delCount[ib1] += (min(min(b2, bMin2[ib1]), n + 1) - min(bMin1[ib1], n + 1))
        retVal += max(delCount)

        return retVal
```

</details>
