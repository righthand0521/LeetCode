# Array

## [3000. Maximum Area of Longest Diagonal Rectangle](https://leetcode.com/problems/maximum-area-of-longest-diagonal-rectangle/)  1250

- [Official](https://leetcode.com/problems/maximum-area-of-longest-diagonal-rectangle/editorial/)
- [Official](https://leetcode.cn/problems/maximum-area-of-longest-diagonal-rectangle/solutions/3756161/dui-jiao-xian-zui-chang-de-ju-xing-de-mi-t0ux/)

<details><summary>Description</summary>

```text
You are given a 2D 0-indexed integer array dimensions.

For all indices i, 0 <= i < dimensions.length,
dimensions[i][0] represents the length and dimensions[i][1] represents the width of the rectangle i.

Return the area of the rectangle having the longest diagonal.
If there are multiple rectangles with the longest diagonal, return the area of the rectangle having the maximum area.

Example 1:
Input: dimensions = [[9,3],[8,6]]
Output: 48
Explanation:
For index = 0, length = 9 and width = 3. Diagonal length = sqrt(9 * 9 + 3 * 3) = sqrt(90) ≈ 9.487.
For index = 1, length = 8 and width = 6. Diagonal length = sqrt(8 * 8 + 6 * 6) = sqrt(100) = 10.
So, the rectangle at index 1 has a greater diagonal length therefore we return area = 8 * 6 = 48.

Example 2:
Input: dimensions = [[3,4],[4,3]]
Output: 12
Explanation: Length of diagonal is the same for both which is 5, so maximum area = 12.

Constraints:
1 <= dimensions.length <= 100
dimensions[i].length == 2
1 <= dimensions[i][0], dimensions[i][1] <= 100
```

<details><summary>Hint</summary>

```text
1. Diagonal of rectangle is sqrt(length2 + width2).
```

</details>

</details>

<details><summary>C</summary>

```c
int areaOfMaxDiagonal(int** dimensions, int dimensionsSize, int* dimensionsColSize) {
    int retVal = 0;

    int maxDiagonal = 0;
    for (int i = 0; i < dimensionsSize; ++i) {
        int width = dimensions[i][0];
        int height = dimensions[i][1];
        int diagonal = (width * width + height * height);
        int area = width * height;

        if (diagonal > maxDiagonal) {
            maxDiagonal = diagonal;
            retVal = area;
        } else if (diagonal == maxDiagonal) {
            retVal = fmax(retVal, area);
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
    int areaOfMaxDiagonal(vector<vector<int>>& dimensions) {
        int retVal = 0;

        int maxDiagonal = 0;
        for (const auto& dimension : dimensions) {
            int width = dimension[0];
            int height = dimension[1];
            int diagonal = (width * width + height * height);
            int area = width * height;

            if (diagonal > maxDiagonal) {
                maxDiagonal = diagonal;
                retVal = area;
            } else if (diagonal == maxDiagonal) {
                retVal = max(retVal, area);
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
    def areaOfMaxDiagonal(self, dimensions: List[List[int]]) -> int:
        retVal = 0

        maxDiagonal = 0
        for dimension in dimensions:
            width, height = dimension
            diagonal = (width ** 2 + height ** 2)
            area = width * height

            if diagonal > maxDiagonal:
                maxDiagonal = diagonal
                retVal = area
            elif diagonal == maxDiagonal:
                retVal = max(retVal, area)

        return retVal
```

</details>

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

## [3197. Find the Minimum Area to Cover All Ones II](https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-ii/)  2541

- [Official](https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-ii/editorial/)
- [Official](https://leetcode.cn/problems/find-the-minimum-area-to-cover-all-ones-ii/solutions/3756159/bao-han-suo-you-1-de-zui-xiao-ju-xing-mi-ioth/)

<details><summary>Description</summary>

```text
You are given a 2D binary array grid.
You need to find 3 non-overlapping rectangles having non-zero areas with horizontal and vertical sides
such that all the 1's in grid lie inside these rectangles.

Return the minimum possible sum of the area of these rectangles.

Note that the rectangles are allowed to touch.

Example 1:
Input: grid = [[1,0,1],[1,1,1]]
Output: 5
Explanation:
The 1's at (0, 0) and (1, 0) are covered by a rectangle of area 2.
The 1's at (0, 2) and (1, 2) are covered by a rectangle of area 2.
The 1 at (1, 1) is covered by a rectangle of area 1.

Example 2:
Input: grid = [[1,0,1,0],[0,1,0,1]]
Output: 5
Explanation:
The 1's at (0, 0) and (0, 2) are covered by a rectangle of area 3.
The 1 at (1, 1) is covered by a rectangle of area 1.
The 1 at (1, 3) is covered by a rectangle of area 1.

Constraints:
1 <= grid.length, grid[i].length <= 30
grid[i][j] is either 0 or 1.
The input is generated such that there are at least three 1's in grid.
```

<details><summary>Hint</summary>

```text
1. Consider covering using 2 rectangles. As the rectangles don’t overlap,
   one of the rectangles must either be vertically above or horizontally left to the other.
2. To find the minimum area, check all possible vertical and horizontal splits.
3. For 3 rectangles, extend the idea to first covering using one rectangle,
   and then try splitting leftover ones both horizontally and vertically.
```

</details>

</details>

<details><summary>C</summary>

```c
int minimumSum2(int** grid, int gridSize, int* gridColSize, int u, int d, int l, int r) {
    int min_i = gridSize, max_i = 0;
    int min_j = gridColSize[0], max_j = 0;
    for (int i = u; i <= d; i++) {
        for (int j = l; j <= r; j++) {
            if (grid[i][j] == 1) {
                min_i = fmin(min_i, i);
                min_j = fmin(min_j, j);
                max_i = fmax(max_i, i);
                max_j = fmax(max_j, j);
            }
        }
    }
    return min_i <= max_i ? (max_i - min_i + 1) * (max_j - min_j + 1) : INT_MAX / 3;
}
int solve(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int rowSize = gridSize;
    int colSize = gridColSize[0];
    int x, y, z;
    retVal = rowSize * colSize;
    for (int i = 0; i + 1 < rowSize; i++) {
        for (int j = 0; j + 1 < colSize; j++) {
            x = minimumSum2(grid, rowSize, gridColSize, 0, i, 0, colSize - 1);
            y = minimumSum2(grid, rowSize, gridColSize, i + 1, rowSize - 1, 0, j);
            z = minimumSum2(grid, rowSize, gridColSize, i + 1, rowSize - 1, j + 1, colSize - 1);
            retVal = fmin(retVal, x + y + z);

            x = minimumSum2(grid, rowSize, gridColSize, 0, i, 0, j);
            y = minimumSum2(grid, rowSize, gridColSize, 0, i, j + 1, colSize - 1);
            z = minimumSum2(grid, rowSize, gridColSize, i + 1, rowSize - 1, 0, colSize - 1);
            retVal = fmin(retVal, x + y + z);
        }
    }
    for (int i = 0; i + 2 < rowSize; i++) {
        for (int j = i + 1; j + 1 < rowSize; j++) {
            x = minimumSum2(grid, rowSize, gridColSize, 0, i, 0, colSize - 1);
            y = minimumSum2(grid, rowSize, gridColSize, i + 1, j, 0, colSize - 1);
            z = minimumSum2(grid, rowSize, gridColSize, j + 1, rowSize - 1, 0, colSize - 1);
            retVal = fmin(retVal, x + y + z);
        }
    }

    return retVal;
}
int** rotate(int** grid, int gridSize, int* gridColSize, int* returnSize, int** returnColSizes) {
    int** pRetVal = NULL;

    int rowSize = gridSize;
    int colSize = gridColSize[0];

    (*returnSize) = 0;
    (*returnColSizes) = (int*)malloc(colSize * sizeof(int));
    if ((*returnColSizes) == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal = (int**)malloc(colSize * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColSizes));
        (*returnColSizes) = NULL;
        return pRetVal;
    }
    for (int i = 0; i < colSize; i++) {
        pRetVal[i] = (int*)malloc(rowSize * sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            for (int j = 0; j < i; j++) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free((*returnColSizes));
            (*returnColSizes) = NULL;
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        (*returnColSizes)[i] = rowSize;
    }

    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            pRetVal[colSize - j - 1][i] = grid[i][j];
        }
    }
    (*returnSize) = colSize;

    return pRetVal;
}
int minimumSum(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int rotateGridSize = 0;
    int* rotateGridColSizes = NULL;
    int** rotateGrid = rotate(grid, gridSize, gridColSize, &rotateGridSize, &rotateGridColSizes);
    if (rotateGrid != NULL) {
        retVal = fmin(solve(grid, gridSize, gridColSize), solve(rotateGrid, rotateGridSize, rotateGridColSizes));
    }

    //
    for (int i = 0; i < rotateGridSize; i++) {
        free(rotateGrid[i]);
        rotateGrid[i] = NULL;
    }
    free(rotateGrid);
    rotateGrid = NULL;
    free(rotateGridColSizes);
    rotateGridColSizes = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    int minimumSum2(vector<vector<int>> &grid, int u, int d, int l, int r) {
        int retVal = 0;

        int minRow = grid.size();
        int maxRow = 0;
        int minCol = grid[0].size();
        int maxCol = 0;
        for (int i = u; i <= d; i++) {
            for (int j = l; j <= r; j++) {
                if (grid[i][j] == 1) {
                    minRow = min(minRow, i);
                    minCol = min(minCol, j);
                    maxRow = max(maxRow, i);
                    maxCol = max(maxCol, j);
                }
            }
        }
        retVal = numeric_limits<int>::max() / 3;
        if (minRow <= maxRow) {
            retVal = (maxRow - minRow + 1) * (maxCol - minCol + 1);
        }

        return retVal;
    }
    int solve(vector<vector<int>> &grid) {
        int retVal = 0;

        int gridSize = grid.size();
        int gridColSize = grid[0].size();

        int x, y, z;
        retVal = gridSize * gridColSize;
        for (int i = 0; i + 1 < gridSize; i++) {
            for (int j = 0; j + 1 < gridColSize; j++) {
                x = minimumSum2(grid, 0, i, 0, gridColSize - 1);
                y = minimumSum2(grid, i + 1, gridSize - 1, 0, j);
                z = minimumSum2(grid, i + 1, gridSize - 1, j + 1, gridColSize - 1);
                retVal = min(retVal, x + y + z);

                x = minimumSum2(grid, 0, i, 0, j);
                y = minimumSum2(grid, 0, i, j + 1, gridColSize - 1);
                z = minimumSum2(grid, i + 1, gridSize - 1, 0, gridColSize - 1);
                retVal = min(retVal, x + y + z);
            }
        }

        for (int i = 0; i + 2 < gridSize; i++) {
            for (int j = i + 1; j + 1 < gridSize; j++) {
                x = minimumSum2(grid, 0, i, 0, gridColSize - 1);
                y = minimumSum2(grid, i + 1, j, 0, gridColSize - 1);
                z = minimumSum2(grid, j + 1, gridSize - 1, 0, gridColSize - 1);
                retVal = min(retVal, x + y + z);
            }
        }

        return retVal;
    }
    vector<vector<int>> rotate(vector<vector<int>> &grid) {
        vector<vector<int>> retVal;

        int gridSize = grid.size();
        int gridColSize = grid[0].size();
        retVal.resize(gridColSize, vector<int>(gridSize));
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridColSize; j++) {
                retVal[gridColSize - j - 1][i] = grid[i][j];
            }
        }

        return retVal;
    }

   public:
    int minimumSum(vector<vector<int>> &grid) {
        int retVal = 0;

        auto rotateGrid = rotate(grid);
        retVal = min(solve(grid), solve(rotateGrid));

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minimumSum2(self, grid: List[List[int]], u: int, d: int, l: int, r: int) -> int:
        retVal = 0

        minRow = len(grid)
        maxRow = 0
        minCol = len(grid[0])
        maxCol = 0
        for i in range(u, d + 1):
            for j in range(l, r + 1):
                if grid[i][j] == 1:
                    minRow = min(minRow, i)
                    minCol = min(minCol, j)
                    maxRow = max(maxRow, i)
                    maxCol = max(maxCol, j)

        retVal = ((maxRow - minRow + 1) * (maxCol - minCol + 1) if minRow <= maxRow else sys.maxsize // 3)

        return retVal

    def rotate(self, grid: List[List[int]]) -> List[List[int]]:
        retVal = []

        gridSize = len(grid)
        gridColSize = len(grid[0]) if gridSize > 0 else 0

        retVal = [[0] * gridSize for _ in range(gridColSize)]
        for i in range(gridSize):
            for j in range(gridColSize):
                retVal[gridColSize - j - 1][i] = grid[i][j]

        return retVal

    def solve(self, grid: List[List[int]]) -> int:
        retVal = 0

        gridSize = len(grid)
        gridColSize = len(grid[0]) if gridSize > 0 else 0
        retVal = gridSize * gridColSize

        for i in range(gridSize - 1):
            for j in range(gridColSize - 1):
                x = self.minimumSum2(grid, 0, i, 0, gridColSize - 1)
                y = self.minimumSum2(grid, i + 1, gridSize - 1, 0, j)
                z = self.minimumSum2(grid, i + 1, gridSize - 1, j + 1, gridColSize - 1)
                retVal = min(retVal, x + y + z)

                x = self.minimumSum2(grid, 0, i, 0, j)
                y = self.minimumSum2(grid, 0, i, j + 1, gridColSize - 1)
                z = self.minimumSum2(grid, i + 1, gridSize - 1, 0, gridColSize - 1)
                retVal = min(retVal, x + y + z)

        for i in range(gridSize - 2):
            for j in range(i + 1, gridSize - 1):
                x = self.minimumSum2(grid, 0, i, 0, gridColSize - 1)
                y = self.minimumSum2(grid, i + 1, j, 0, gridColSize - 1)
                z = self.minimumSum2(grid, j + 1, gridSize - 1, 0, gridColSize - 1)
                retVal = min(retVal, x + y + z)

        return retVal

    def minimumSum(self, grid: List[List[int]]) -> int:
        retVal = 0

        rotateGrid = self.rotate(grid)
        retVal = min(self.solve(grid), self.solve(rotateGrid))

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

## [3446. Sort Matrix by Diagonals](https://leetcode.com/problems/sort-matrix-by-diagonals/)  1373

- [Official](https://leetcode.com/problems/sort-matrix-by-diagonals/editorial/)
- [Official](https://leetcode.cn/problems/sort-matrix-by-diagonals/description/)

<details><summary>Description</summary>

```text
You are given an n x n square matrix of integers grid. Return the matrix such that:
- The diagonals in the bottom-left triangle (including the middle diagonal) are sorted in non-increasing order.
- The diagonals in the top-right triangle are sorted in non-decreasing order.

Example 1:
Input: grid = [[1,7,3],[9,8,2],[4,5,6]]
Output: [[8,2,3],[9,6,7],[4,5,1]]
Explanation:
The diagonals with a black arrow (bottom-left triangle) should be sorted in non-increasing order:
[1, 8, 6] becomes [8, 6, 1].
[9, 5] and [4] remain unchanged.
The diagonals with a blue arrow (top-right triangle) should be sorted in non-decreasing order:
[7, 2] becomes [2, 7].
[3] remains unchanged.

Example 2:
Input: grid = [[0,1],[1,2]]
Output: [[2,1],[1,0]]
Explanation:
The diagonals with a black arrow must be non-increasing, so [0, 2] is changed to [2, 0].
The other diagonals are already in the correct order.

Example 3:
Input: grid = [[1]]
Output: [[1]]
Explanation:
Diagonals with exactly one element are already in order, so no changes are needed.

Constraints:
grid.length == grid[i].length == n
1 <= n <= 10
-10^5 <= grid[i][j] <= 10^5
```

<details><summary>Hint</summary>

```text
1. Use a data structure to store all values in each diagonal.
2. Sort and replace them in the matrix.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareIntegerAscending(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int compareIntegerDescending(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** sortMatrix(int** grid, int gridSize, int* gridColSize, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;

    (*returnColumnSizes) = (int*)calloc(gridSize, sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("calloc");
        return pRetVal;
    }
    pRetVal = (int**)malloc(gridSize * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }
    for (int i = 0; i < gridSize; ++i) {
        pRetVal[i] = (int*)calloc(gridColSize[i], sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("calloc");
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            for (int j = 0; j < i; ++j) {
                free(pRetVal[j]);
            }
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        for (int j = 0; j < gridColSize[i]; j++) {
            pRetVal[i][j] = grid[i][j];
        }
        (*returnColumnSizes)[i] = gridColSize[i];
    }
    (*returnSize) = gridSize;

    int tmp[gridSize + 1];
    int len;

    for (int i = 0; i < gridSize; i++) {
        memset(tmp, 0, sizeof(tmp));
        len = 0;
        for (int j = 0; i + j < gridSize; j++) {
            tmp[len++] = pRetVal[i + j][j];
        }
        qsort(tmp, len, sizeof(int), compareIntegerDescending);

        for (int j = 0; i + j < gridSize; j++) {
            pRetVal[i + j][j] = tmp[j];
        }
    }

    for (int j = 1; j < gridSize; j++) {
        memset(tmp, 0, sizeof(tmp));
        len = 0;
        for (int i = 0; j + i < gridColSize[i]; i++) {
            tmp[len++] = pRetVal[i][j + i];
        }
        qsort(tmp, len, sizeof(int), compareIntegerAscending);

        for (int i = 0; j + i < gridColSize[i]; i++) {
            pRetVal[i][j + i] = tmp[i];
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
    vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
        vector<vector<int>> retVal = grid;

        int gridSize = grid.size();

        for (int i = 0; i < gridSize; i++) {
            vector<int> tmp;
            for (int j = 0; i + j < gridSize; j++) {
                tmp.emplace_back(grid[i + j][j]);
            }
            sort(tmp.begin(), tmp.end(), greater<int>());

            for (int j = 0; i + j < gridSize; j++) {
                retVal[i + j][j] = tmp[j];
            }
        }

        for (int j = 1; j < gridSize; j++) {
            vector<int> tmp;
            for (int i = 0; j + i < gridSize; i++) {
                tmp.emplace_back(retVal[i][j + i]);
            }

            sort(tmp.begin(), tmp.end());
            for (int i = 0; j + i < gridSize; i++) {
                retVal[i][j + i] = tmp[i];
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
    def sortMatrix(self, grid: List[List[int]]) -> List[List[int]]:
        retVal = None

        retVal = deepcopy(grid)

        gridSize = len(grid)

        for i in range(gridSize):
            tmp = [retVal[i + j][j] for j in range(gridSize - i)]
            tmp.sort(reverse=True)
            for j in range(gridSize - i):
                retVal[i + j][j] = tmp[j]

        for j in range(1, gridSize):
            tmp = [retVal[i][j + i] for i in range(gridSize - j)]
            tmp.sort()
            for i in range(gridSize - j):
                retVal[i][j + i] = tmp[i]

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
