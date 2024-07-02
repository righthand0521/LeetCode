# [Hash Table](https://en.wikipedia.org/wiki/Hash_table)

- [uthash](https://troydhanson.github.io/uthash/)

## [1. Two Sum](https://leetcode.com/problems/two-sum/)

- [Official](https://leetcode.com/problems/two-sum/solutions/127810/two-sum/)
- [Official](https://leetcode.cn/problems/two-sum/solutions/434597/liang-shu-zhi-he-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
You may assume that each input would have exactly one solution, and you may not use the same element twice.
You can return the answer in any order.

Example 1:
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].

Example 2:
Input: nums = [3,2,4], target = 6
Output: [1,2]

Example 3:
Input: nums = [3,3], target = 6
Output: [0,1]

Constraints:
2 <= nums.length <= 10^4
-10^9 <= nums[i] <= 10^9
-10^9 <= target <= 10^9
Only one valid answer exists.
```

<details><summary>Hint</summary>

```text
1. A really brute force way would be to search for all possible pairs of numbers but that would be too slow.
   Again, it's best to try out brute force solutions for just for completeness.
   It is from these brute force solutions that you can come up with optimizations.
2. So, if we fix one of the numbers, say x, we have to scan the entire array
   to find the next number y which is value - x where value is the input parameter.
   Can we change our array somehow so that this search becomes faster?
3. The second train of thought is, without changing the array, can we use additional space somehow?
   Like maybe a hash map to speed up the search?
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
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *twoSum(int *nums, int numsSize, int target, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 2;
    pRetVal = (int *)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }

    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    int complement;
    int i;
    for (i = 0; i < numsSize; ++i) {
        complement = target - nums[i];

        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &complement, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                free(pRetVal);
                pRetVal = NULL;
                (*returnSize) = 0;
                return pRetVal;
            }
            pTemp->key = nums[i];
            pTemp->value = i;
            HASH_ADD_INT(pHashTable, key, pTemp);
        } else {
            *(pRetVal + 0) = pTemp->value;
            *(pRetVal + 1) = i;
            break;
        }
    }
    freeAll(pHashTable);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> retVal;

        unordered_map<int, int> hashTable;
        int numsSize = nums.size();
        for (int i = 0; i < numsSize; ++i) {
            auto iterator = hashTable.find(target - nums[i]);
            if (iterator != hashTable.end()) {
                retVal.push_back(iterator->second);
                retVal.push_back(i);
                return retVal;
            }
            hashTable[nums[i]] = i;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        retVal = []

        hashTable = defaultdict(int)
        for idx, num in enumerate(nums):
            if num in hashTable:
                retVal = [hashTable[num], idx]
                break
            hashTable[target - num] = idx

        return retVal
```

</details>

## [36. Valid Sudoku](https://leetcode.com/problems/valid-sudoku/)

- [Official](https://leetcode.cn/problems/valid-sudoku/solutions/1001859/you-xiao-de-shu-du-by-leetcode-solution-50m6/)

<details><summary>Description</summary>

```text
Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:
1. Each row must contain the digits 1-9 without repetition.
2. Each column must contain the digits 1-9 without repetition.
3. Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.

Note:
- A Sudoku board (partially filled) could be valid but is not necessarily solvable.
- Only the filled cells need to be validated according to the mentioned rules.

Example 1:
Input: board =
[["5","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
Output: true

Example 2:
Input: board =
[["8","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
Output: false
Explanation:
Same as Example 1, except with the 5 in the top left corner being modified to 8.
Since there are two 8's in the top left 3x3 sub-box, it is invalid.

Constraints:
board.length == 9
board[i].length == 9
board[i][j] is a digit 1-9 or '.'.
```

</details>

<details><summary>C</summary>

```c
bool isValidSudoku(char** board, int boardSize, int* boardColSize) {
    bool retVal = false;

    int i, j;
#define MAX_SIZE (9)
    int HASHTABLE[MAX_SIZE];
    int idx;

    // check each row
    for (i = 0; i < boardSize; ++i) {
        memset(HASHTABLE, 0, sizeof(HASHTABLE));
        for (j = 0; j < boardColSize[i]; ++j) {
            if (board[i][j] == '.') {
                continue;
            }
            idx = (board[i][j] - '0') - 1;
            if (HASHTABLE[idx] != 0) {
                return retVal;
            }
            ++HASHTABLE[idx];
        }
    }

    // check each column
    for (j = 0; j < boardColSize[0]; ++j) {
        memset(HASHTABLE, 0, sizeof(HASHTABLE));
        for (i = 0; i < boardSize; ++i) {
            if (board[i][j] == '.') {
                continue;
            }
            idx = (board[i][j] - '0') - 1;
            if (HASHTABLE[idx] != 0) {
                return retVal;
            }
            ++HASHTABLE[idx];
        }
    }

    // check 3x3 sub-boxes
    int rowShift;
    int colShift;
    for (rowShift = 0; rowShift < boardSize; rowShift += 3) {
        for (colShift = 0; colShift < boardColSize[0]; colShift += 3) {
            memset(HASHTABLE, 0, sizeof(HASHTABLE));
            for (i = 0; i < 3; ++i) {
                for (j = 0; j < 3; ++j) {
                    if (board[i + rowShift][j + colShift] == '.') {
                        continue;
                    }
                    idx = (board[i + rowShift][j + colShift] - '0') - 1;
                    if (HASHTABLE[idx] != 0) {
                        return retVal;
                    }
                    ++HASHTABLE[idx];
                }
            }
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
    bool isValidSudoku(vector<vector<char>>& board) {
        bool retVal = false;

        int boardSize = board.size();
        int boardColSize = board[0].size();

        vector<vector<int>> rowHashTable(boardColSize, vector<int>(boardSize, 0));
        vector<vector<int>> colHashTable(boardColSize, vector<int>(boardSize, 0));
        vector<vector<int>> boxHashTable(boardColSize, vector<int>(boardSize, 0));
        for (int x = 0; x < boardSize; ++x) {
            for (int y = 0; y < boardColSize; ++y) {
                if (board[x][y] == '.') {
                    continue;
                }

                int digits = board[x][y] - '0' - 1;
                int boxIndex = (x / 3) * 3 + y / 3;
                if ((rowHashTable[x][digits]) || (colHashTable[y][digits]) || (boxHashTable[boxIndex][digits])) {
                    return retVal;
                }
                rowHashTable[x][digits] = 1;
                colHashTable[y][digits] = 1;
                boxHashTable[boxIndex][digits] = 1;
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
    def isValidSudoku(self, board: List[List[str]]) -> bool:
        retVal = True

        boardSize = len(board)
        boardColSize = len(board[0])

        rowHashTable = [[0 for _ in range(boardColSize)] for _ in range(boardSize)]
        colHashTable = [[0 for _ in range(boardColSize)] for _ in range(boardSize)]
        boxHashTable = [[0 for _ in range(boardColSize)] for _ in range(boardSize)]
        for x in range(boardSize):
            for y in range(len(board[x])):
                if board[x][y] == ".":
                    continue

                digits = int(board[x][y]) - 1
                boxIndex = (x // 3) * 3 + y // 3
                if rowHashTable[x][digits] or colHashTable[y][digits] or boxHashTable[boxIndex][digits]:
                    retVal = False
                    return retVal

                rowHashTable[x][digits] = 1
                colHashTable[y][digits] = 1
                boxHashTable[boxIndex][digits] = 1

        return retVal
```

</details>

## [41. First Missing Positive](https://leetcode.com/problems/first-missing-positive/)

- [Official](https://leetcode.cn/problems/first-missing-positive/solutions/304743/que-shi-de-di-yi-ge-zheng-shu-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given an unsorted integer array nums, return the smallest missing positive integer.

You must implement an algorithm that runs in O(n) time and uses constant extra space.

Example 1:
Input: nums = [1,2,0]
Output: 3
Explanation: The numbers in the range [1,2] are all in the array.

Example 2:
Input: nums = [3,4,-1,1]
Output: 2
Explanation: 1 is in the array but 2 is missing.

Example 3:
Input: nums = [7,8,9,11,12]
Output: 1
Explanation: The smallest positive integer 1 is missing.

Constraints:
1 <= nums.length <= 10^5
-2^31 <= nums[i] <= 2^31 - 1
```

<details><summary>Hint</summary>

```text
1. Think about how you would solve the problem in non-constant space. Can you apply that logic to the existing space?
2. We don't care about duplicates or non-positive integers
3. Remember that O(2n) = O(n)
```

</details>

</details>

<details><summary>C</summary>

```c
int firstMissingPositive(int* nums, int numsSize) {
    int retVal = 0;

    int seenSize = numsSize + 1;
    int seen[seenSize];
    memset(seen, 0, sizeof(seen));

    int value;
    int i;
    for (i = 0; i < numsSize; ++i) {
        value = nums[i];
        if ((0 < value) && (value <= numsSize)) {
            seen[value] = 1;
        }
    }

    for (i = 1; i <= numsSize; ++i) {
        if (seen[i] == 0) {
            retVal = i;
            return retVal;
        }
    }
    retVal = numsSize + 1;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int firstMissingPositive(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        vector<bool> seen((numsSize + 1), false);
        for (int num : nums) {
            if ((0 < num) && (num <= numsSize)) {
                seen[num] = true;
            }
        }

        for (int i = 1; i <= numsSize; ++i) {
            if (seen[i] == false) {
                retVal = i;
                return retVal;
            }
        }
        retVal = numsSize + 1;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def firstMissingPositive(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        seen = [False] * (numsSize + 1)
        for num in nums:
            if 0 < num <= numsSize:
                seen[num] = True

        for i in range(1, numsSize + 1):
            if seen[i] == False:
                retVal = i
                return retVal
        retVal = numsSize + 1

        return retVal
```

</details>

## [49. Group Anagrams](https://leetcode.com/problems/group-anagrams/)

- [Official](https://leetcode.cn/problems/group-anagrams/solutions/520469/zi-mu-yi-wei-ci-fen-zu-by-leetcode-solut-gyoc/)

<details><summary>Description</summary>

```text
Given an array of strings strs, group the anagrams together. You can return the answer in any order.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase,
typically using all the original letters exactly once.

Example 1:
Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]

Example 2:
Input: strs = [""]
Output: [[""]]

Example 3:
Input: strs = ["a"]
Output: [["a"]]

Constraints:
1 <= strs.length <= 10^4
0 <= strs[i].length <= 100
strs[i] consists of lowercase English letters.
```

</details>

<details><summary>C</summary>

```c
#define MAX_LENGTH (100 + 4)  // 0 <= strs[i].length <= 100
struct hashTable {
    char key[MAX_LENGTH];
    int count;
    int idx;
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%s: %d\n", pFree->key, pFree->count);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int compareChar(const void* c1, const void* c2) {
    // ascending order
    return (*(char*)c1 - *(char*)c2);
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    char*** pRetVal = NULL;

    //
    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    int i, j, k;

    //
    char pSortStr[MAX_LENGTH];
    struct hashTable* pMap = NULL;
    struct hashTable* pTmp;
    for (i = 0; i < strsSize; ++i) {
        memset(pSortStr, 0, sizeof(pSortStr));
        snprintf(pSortStr, sizeof(pSortStr), "%s", strs[i]);
        qsort(pSortStr, strlen(pSortStr), sizeof(char), compareChar);

        pTmp = NULL;
        HASH_FIND_STR(pMap, pSortStr, pTmp);
        if (pTmp != NULL) {
            pTmp->count++;
            continue;
        }
        pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
        if (pTmp == NULL) {
            perror("malloc");
            (*returnSize) = 0;
            goto exit;
        }
        snprintf(pTmp->key, MAX_LENGTH, "%s", pSortStr);
        pTmp->count = 1;
        HASH_ADD_STR(pMap, key, pTmp);

        (*returnSize)++;
    }

    //
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        goto exit;
    }
    i = 0;
    for (pTmp = pMap; pTmp != NULL; pTmp = pTmp->hh.next) {
        (*returnColumnSizes)[i++] = pTmp->count;
    }
    freeAll(pMap);
    pMap = NULL;

    //
    pRetVal = (char***)malloc((*returnSize) * sizeof(char**));
    if (pRetVal == NULL) {
        perror("malloc");
        goto exit_returnColumnSizes;
    }
    for (i = 0; i < (*returnSize); ++i) {
        pRetVal[i] = (char**)malloc(((*returnColumnSizes)[i]) * sizeof(char*));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            goto exit_returnValue;
        }
        for (j = 0; j < (*returnColumnSizes)[i]; ++j) {
            pRetVal[i][j] = (char*)malloc(MAX_LENGTH * sizeof(char));
            if (pRetVal[i][j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pRetVal[i][k]);
                    pRetVal[i][k] = NULL;
                }
                for (k = 0; k < i; ++k) {
                    free(pRetVal[k]);
                    pRetVal[k] = NULL;
                }
                goto exit_returnValue;
            }
            memset(pRetVal[i][j], 0, MAX_LENGTH);
        }
    }

    //
    int idx = 0;
    for (i = 0; i < strsSize; ++i) {
        memset(pSortStr, 0, sizeof(pSortStr));
        snprintf(pSortStr, sizeof(pSortStr), "%s", strs[i]);
        qsort(pSortStr, strlen(pSortStr), sizeof(char), compareChar);

        pTmp = NULL;
        HASH_FIND_STR(pMap, pSortStr, pTmp);
        if (pTmp != NULL) {
            snprintf(pRetVal[pTmp->idx][pTmp->count], MAX_LENGTH, "%s", strs[i]);
            pTmp->count++;
            continue;
        }
        pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
        if (pTmp == NULL) {
            perror("malloc");
            freeAll(pMap);
            pMap = NULL;
            for (j = 0; j < (*returnSize); ++j) {
                for (k = 0; k < (*returnColumnSizes)[j]; ++k) {
                    free(pRetVal[j][k]);
                    pRetVal[j][k] = NULL;
                }
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            goto exit_returnValue;
        }
        snprintf(pTmp->key, MAX_LENGTH, "%s", pSortStr);
        pTmp->count = 1;
        pTmp->idx = idx;
        HASH_ADD_STR(pMap, key, pTmp);

        snprintf(pRetVal[idx++][0], MAX_LENGTH, "%s", strs[i]);
    }

exit:
    //
    freeAll(pMap);
    pMap = NULL;

    return pRetVal;

exit_returnValue:
    free(pRetVal);
    pRetVal = NULL;

exit_returnColumnSizes:
    free((*returnColumnSizes));
    (*returnColumnSizes) = NULL;

    (*returnSize) = 0;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> retVal;

        unordered_map<string, vector<string>> hashTable;
        for (string str : strs) {
            string key = str;
            sort(key.begin(), key.end());
            hashTable[key].emplace_back(str);
        }

        for (auto iterator = hashTable.begin(); iterator != hashTable.end(); ++iterator) {
            retVal.emplace_back(iterator->second);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        retVal = []

        hashTable = defaultdict(list)
        for str in strs:
            key = "".join(sorted(str))
            hashTable[key].append(str)
        retVal = list(hashTable.values())

        return retVal
```

</details>

## [73. Set Matrix Zeroes](https://leetcode.com/problems/set-matrix-zeroes/)

- [Official](https://leetcode.cn/problems/set-matrix-zeroes/solutions/669901/ju-zhen-zhi-ling-by-leetcode-solution-9ll7/)

<details><summary>Description</summary>

```text
Given an m x n integer matrix matrix, if an element is 0, set its entire row and column to 0's.
You must do it in place.

Example 1:
Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
Output: [[1,0,1],[0,0,0],[1,0,1]]

Example 2:
Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]

Constraints:
m == matrix.length
n == matrix[0].length
1 <= m, n <= 200
-2^31 <= matrix[i][j] <= 2^31 - 1

Follow up:
A straightforward solution using O(mn) space is probably a bad idea.
A simple improvement uses O(m + n) space, but still not the best solution.
Could you devise a constant space solution?
```

<details><summary>Hint</summary>

```text
1. If any cell of the matrix has a zero we can record its row and column number using additional memory.
   But if you don't want to use extra memory then you can manipulate the array instead.
   i.e. simulating exactly what the question says.
2. Setting cell values to zero on the fly while iterating might lead to discrepancies.
   What if you use some other integer value as your marker?
   There is still a better approach for this problem with 0(1) space.
3. We could have used 2 sets to keep a record of rows/columns which need to be set to zero.
   But for an O(1) space solution,
   you can use one of the rows and and one of the columns to keep track of this information.
4. We can use the first cell of every row and column as a flag.
   This flag would determine whether a row or column has been set to zero.
```

</details>

</details>

<details><summary>C</summary>

```c
void setZeroes(int** matrix, int matrixSize, int* matrixColSize) {
    int matrixRow = matrixSize;
    int matrixCol = matrixColSize[0];

    int rowHashTable[matrixRow];
    memset(rowHashTable, 0, matrixRow * sizeof(int));
    int colHashTable[matrixCol];
    memset(colHashTable, 0, matrixCol * sizeof(int));

    int i, j;
    for (i = 0; i < matrixRow; ++i) {
        for (j = 0; j < matrixCol; ++j) {
            if (matrix[i][j] == 0) {
                rowHashTable[i] = 1;
                colHashTable[j] = 1;
            }
        }
    }

    for (i = 0; i < matrixRow; ++i) {
        for (j = 0; j < matrixCol; ++j) {
            if ((rowHashTable[i] == 1) || (colHashTable[j] == 1)) {
                matrix[i][j] = 0;
            }
        }
    }
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    void setZeroes(vector<vector<int>>& matrix) {
        int matrixRow = matrix.size();
        int matrixCol = matrix[0].size();

        vector<int> rowHashTable(matrixRow, 0);
        vector<int> colHashTable(matrixCol, 0);
        for (int i = 0; i < matrixRow; ++i) {
            for (int j = 0; j < matrixCol; ++j) {
                if (matrix[i][j] == 0) {
                    rowHashTable[i] = 1;
                    colHashTable[j] = 1;
                }
            }
        }

        for (int i = 0; i < matrixRow; ++i) {
            for (int j = 0; j < matrixCol; ++j) {
                if ((rowHashTable[i] == 1) || (colHashTable[j] == 1)) {
                    matrix[i][j] = 0;
                }
            }
        }
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def setZeroes(self, matrix: List[List[int]]) -> None:
        """
        Do not return anything, modify matrix in-place instead.
        """
        matrixRow = len(matrix)
        matrixCol = len(matrix[0])

        rowHashTable = [0] * matrixRow
        colHashTable = [0] * matrixCol
        for i in range(matrixRow):
            for j in range(matrixCol):
                if matrix[i][j] == 0:
                    rowHashTable[i] = 1
                    colHashTable[j] = 1

        for i in range(matrixRow):
            for j in range(matrixCol):
                if (rowHashTable[i] == 1) or (colHashTable[j] == 1):
                    matrix[i][j] = 0
```

</details>

## [128. Longest Consecutive Sequence](https://leetcode.com/problems/longest-consecutive-sequence)

- [Official](https://leetcode.cn/problems/longest-consecutive-sequence/solutions/276931/zui-chang-lian-xu-xu-lie-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.

You must write an algorithm that runs in O(n) time.

Example 1:
Input: nums = [100,4,200,1,3,2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.

Example 2:
Input: nums = [0,3,7,2,5,8,4,6,0,1]
Output: 9

Constraints:
0 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9
```

</details>

<details><summary>C</summary>

```c
struct hashTable {
    int key;
    int value;
    UT_hash_handle hh;
};
int updateHashTable(struct hashTable **pHashTable, int key, int value) {
    int retVal = EXIT_SUCCESS;

    struct hashTable *pTemp = NULL;
    HASH_FIND_INT((*pHashTable), &key, pTemp);
    if (pTemp != NULL) {
        pTemp->value = value;
    } else {
        pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
        if (pTemp == NULL) {
            perror("malloc");
            retVal = EXIT_FAILURE;
            return retVal;
        }
        pTemp->key = key;
        pTemp->value = value;
        HASH_ADD_INT((*pHashTable), key, pTemp);
    }

    return retVal;
}
void freeAll(struct hashTable *pFree) {
    struct hashTable *current;
    struct hashTable *tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int longestConsecutive(int *nums, int numsSize) {
    int retVal = 0;

    //
    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    int key;
    int left, right, length;
    int i;
    for (i = 0; i < numsSize; ++i) {
        key = nums[i];
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &key, pTemp);
        if (pTemp != NULL) {
            continue;
        }

        //
        left = 0;
        key = nums[i] - 1;
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &key, pTemp);
        if (pTemp != NULL) {
            left = pTemp->value;
        }

        right = 0;
        key = nums[i] + 1;
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &key, pTemp);
        if (pTemp != NULL) {
            right = pTemp->value;
        }

        //
        length = left + right + 1;

        key = nums[i];
        if (updateHashTable(&pHashTable, key, 1) == EXIT_FAILURE) {
            goto exit;
        }

        key = nums[i] - left;
        if (updateHashTable(&pHashTable, key, length) == EXIT_FAILURE) {
            goto exit;
        }

        key = nums[i] + right;
        if (updateHashTable(&pHashTable, key, length) == EXIT_FAILURE) {
            goto exit;
        }

        //
        retVal = fmax(retVal, length);
    }

exit:
    //
    freeAll(pHashTable);
    pHashTable = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int longestConsecutive(vector<int>& nums) {
        int retVal = 0;

        unordered_map<int, int> hashTable;
        for (int num : nums) {
            if (hashTable.find(num) != hashTable.end()) {
                continue;
            }

            int left = 0;
            if (hashTable.find(num - 1) != hashTable.end()) {
                left = hashTable[num - 1];
            }

            int right = 0;
            if (hashTable.find(num + 1) != hashTable.end()) {
                right = hashTable[num + 1];
            }

            int length = left + right + 1;
            hashTable[num] = 1;
            hashTable[num - left] = length;
            hashTable[num + right] = length;

            retVal = max(retVal, length);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def longestConsecutive(self, nums: List[int]) -> int:
        retVal = 0

        hashTable = defaultdict(int)
        for num in nums:
            if num in hashTable:
                continue

            left = 0
            if (num - 1) in hashTable:
                left = hashTable[num - 1]

            right = 0
            if (num + 1) in hashTable:
                right = hashTable[num + 1]

            length = left + right + 1
            hashTable[num] = 1
            hashTable[num - left] = length
            hashTable[num + right] = length

            retVal = max(retVal, length)

        return retVal
```

</details>

## [149. Max Points on a Line](https://leetcode.com/problems/max-points-on-a-line/)

- [Official](https://leetcode.cn/problems/max-points-on-a-line/solutions/842114/zhi-xian-shang-zui-duo-de-dian-shu-by-le-tq8f/)

<details><summary>Description</summary>

```text
Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane,
return the maximum number of points that lie on the same straight line.

Example 1:
  ^
4 |
3 |     x
2 |   x
1 | x
  +--------->
    1 2 3 4
Input: points = [[1,1],[2,2],[3,3]]
Output: 3

Example 2:
  ^
5 |
4 | x
3 |   x     x
2 |     x
1 | x     x
  +----------->
    1 2 3 4 5
Input: points = [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
Output: 4

Constraints:
1 <= points.length <= 300
points[i].length == 2
-10^4 <= xi, yi <= 10^4
All the points are unique.
```

</details>

<details><summary>C</summary>

```c
#define MAX_LENGTH (32)
struct hashStruct {
    char key[MAX_LENGTH];
    int count;
    UT_hash_handle hh;
};
void freeAll(struct hashStruct* pFree) {
    struct hashStruct* current;
    struct hashStruct* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        HASH_DEL(pFree, current);
        free(current);
    }
}
int gcd(int a, int b) {
    int remainder;
    while (b != 0) {
        remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}
int maxPoints(int** points, int pointsSize, int* pointsColSize) {
    int retVal = 0;

    struct hashStruct* map;
    struct hashStruct* temp;
    char key[MAX_LENGTH];
    int maxCount, duplicate, vertical, horizontal;
    int x, y, greatestCommonDivisor;
    int i, j;
    for (i = 0; i < pointsSize; ++i) {
        maxCount = 0;
        duplicate = 0;
        vertical = 0;
        horizontal = 0;
        map = NULL;
        for (j = (i + 1); j < pointsSize; ++j) {
            x = points[j][0] - points[i][0];
            y = points[j][1] - points[i][1];

            if ((x == 0) && (y == 0)) {
                ++duplicate;
            } else if (x == 0) {
                ++vertical;
                maxCount = fmax(maxCount, vertical);
            } else if (y == 0) {
                ++horizontal;
                maxCount = fmax(maxCount, horizontal);
            } else {
                greatestCommonDivisor = gcd(x, y);
                x /= greatestCommonDivisor;
                y /= greatestCommonDivisor;
                memset(key, 0, sizeof(key));
                snprintf(key, sizeof(key), "%d@%d", x, y);
                temp = NULL;
                HASH_FIND_STR(map, key, temp);
                if (temp == NULL) {
                    temp = (struct hashStruct*)malloc(sizeof(struct hashStruct));
                    if (temp == NULL) {
                        perror("malloc");
                        freeAll(map);
                        return retVal;
                    }
                    snprintf(temp->key, MAX_LENGTH, "%s", key);
                    temp->count = 1;
                    HASH_ADD_STR(map, key, temp);
                } else {
                    temp->count += 1;
                }
                maxCount = fmax(maxCount, temp->count);
            }
        }
        freeAll(map);

        retVal = fmax(retVal, maxCount + duplicate + 1);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxPoints(vector<vector<int>>& points) {
        int retVal = 1;

        int pointsSize = points.size();
        if (pointsSize == 1) {
            return retVal;
        }

        retVal = 2;
        for (int i = 0; i < pointsSize; ++i) {
            unordered_map<double, int> hashTable;
            for (int j = 0; j < pointsSize; ++j) {
                if (i == j) {
                    continue;
                }
                int x = points[j][0] - points[i][0];
                int y = points[j][1] - points[i][1];
                hashTable[atan2(y, x)]++;
            }

            for (auto [arctangent, count] : hashTable) {
                retVal = max(retVal, count + 1);
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
    def maxPoints(self, points: List[List[int]]) -> int:
        retVal = 1

        pointsSize = len(points)
        if pointsSize == 1:
            return retVal

        retVal = 2
        for i in range(pointsSize):
            hashTable = defaultdict(lambda: 0)
            for j in range(pointsSize):
                if i == j:
                    continue
                x = points[j][0] - points[i][0]
                y = points[j][1] - points[i][1]
                hashTable[atan2(y, x)] += 1

            for arctangent in hashTable:
                retVal = max(retVal, hashTable[arctangent] + 1)

        return retVal
```

</details>

## [169. Majority Element](https://leetcode.com/problems/majority-element/)

- [Official](https://leetcode.cn/problems/majority-element/solutions/146074/duo-shu-yuan-su-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given an array nums of size n, return the majority element.

The majority element is the element that appears more than ⌊n / 2⌋ times.
You may assume that the majority element always exists in the array.

Example 1:
Input: nums = [3,2,3]
Output: 3

Example 2:
Input: nums = [2,2,1,1,1,2,2]
Output: 2

Constraints:
n == nums.length
1 <= n <= 5 * 10^4
-10^9 <= nums[i] <= 10^9
```

</details>

<details><summary>C</summary>

```c
int majorityElement(int* nums, int numsSize) {
    int retVal = 0;

    /* Boyer–Moore majority vote algorithm
     *  https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_majority_vote_algorithm
     *
     *  Example: Input: nums = [2,2,1,1,1,2,2]
     *  +-----------+---------------------------+
     *  | nums      | 2 | 2 | 1 | 1 | 1 | 2 | 2 |
     *  | appears   | 1 | 2 | 1 | 0 | 1 | 0 | 1 |
     *  |-----------+---------------------------+
     *  | candidate | 2 | 2 | 2 | 2 | 1 | 1 | 2 |
     *  | count     | 1 | 2 | 1 | 0 | 1 | 0 | 1 |
     *  +-----------+---------------------------+
     */
    int appears = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if (appears == 0) {
            retVal = nums[i];
        }

        if (retVal == nums[i]) {
            ++appears;
        } else {
            --appears;
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
    int majorityElement(vector<int>& nums) {
        int retVal = 0;

        /* Boyer–Moore majority vote algorithm
         *  https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_majority_vote_algorithm
         *
         *  Example: Input: nums = [2,2,1,1,1,2,2]
         *  +-----------+---------------------------+
         *  | nums      | 2 | 2 | 1 | 1 | 1 | 2 | 2 |
         *  | appears   | 1 | 2 | 1 | 0 | 1 | 0 | 1 |
         *  |-----------+---------------------------+
         *  | candidate | 2 | 2 | 2 | 2 | 1 | 1 | 2 |
         *  | count     | 1 | 2 | 1 | 0 | 1 | 0 | 1 |
         *  +-----------+---------------------------+
         */
        int appears = 0;
        for (int num : nums) {
            if (appears == 0) {
                retVal = num;
            }

            if (retVal == num) {
                ++appears;
            } else {
                --appears;
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
    def majorityElement(self, nums: List[int]) -> int:
        retVal = 0

        # /* Boyer–Moore majority vote algorithm
        #  *  https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_majority_vote_algorithm
        #  *
        #  *  Example: Input: nums = [2,2,1,1,1,2,2]
        #  *  +-----------+---------------------------+
        #  *  | nums      | 2 | 2 | 1 | 1 | 1 | 2 | 2 |
        #  *  | appears   | 1 | 2 | 1 | 0 | 1 | 0 | 1 |
        #  *  |-----------+---------------------------+
        #  *  | candidate | 2 | 2 | 2 | 2 | 1 | 1 | 2 |
        #  *  | count     | 1 | 2 | 1 | 0 | 1 | 0 | 1 |
        #  *  +-----------+---------------------------+
        #  */
        appears = 0
        for num in nums:
            if appears == 0:
                retVal = num

            if retVal == num:
                appears += 1
            else:
                appears -= 1

        return retVal
```

</details>

## [202. Happy Number](https://leetcode.com/problems/happy-number/)

- [Official](https://leetcode.cn/problems/happy-number/solutions/224894/kuai-le-shu-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Write an algorithm to determine if a number n is happy.

A happy number is a number defined by the following process:
- Starting with any positive integer, replace the number by the sum of the squares of its digits.
- Repeat the process until the number equals 1 (where it will stay),
  or it loops endlessly in a cycle which does not include 1.
- Those numbers for which this process ends in 1 are happy.

Return true if n is a happy number, and false if not.

Example 1:
Input: n = 19
Output: true
Explanation:
1^2 + 9^2 = 82
8^2 + 2^2 = 68
6^2 + 8^2 = 100
1^2 + 0^2 + 0^2 = 1

Example 2:
Input: n = 2
Output: false

Constraints:
1 <= n <= 2^31 - 1
```

</details>

<details><summary>C</summary>

```c
struct hashTable {
    int key;
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d\n", pFree->key);
        HASH_DEL(pFree, current);
        free(current);
    }
}
bool isHappy(int n) {
    bool retVal = false;

    struct hashTable* pMap = NULL;
    struct hashTable* pTmp;
    int square, digit;
    while (n != 1) {
        pTmp = NULL;
        HASH_FIND_INT(pMap, &n, pTmp);
        if (pTmp != NULL) {
            break;
        }
        pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
        if (pTmp == NULL) {
            perror("malloc");
            goto exit;
        }
        pTmp->key = n;
        HASH_ADD_INT(pMap, key, pTmp);

        square = 0;
        while (n > 0) {
            digit = n % 10;
            square += (digit * digit);
            n /= 10;
        }
        n = square;
    }

    if (n == 1) {
        retVal = true;
    }

exit:
    //
    freeAll(pMap);
    pMap = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    bool isHappy(int n) {
        bool retVal = false;

        unordered_set<int> hashTable;
        while (n != 1) {
            if (hashTable.find(n) != hashTable.end()) {
                break;
            }
            hashTable.insert(n);

            int square = 0;
            while (n > 0) {
                int digit = n % 10;
                square += (digit * digit);
                n /= 10;
            }
            n = square;
        }

        if (n == 1) {
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
    def isHappy(self, n: int) -> bool:
        retVal = False

        hashTable = set()
        while n != 1:
            if n in hashTable:
                break
            hashTable.add(n)

            square = 0
            while n > 0:
                digit = n % 10
                square += (digit * digit)
                n //= 10
            n = square

        if n == 1:
            retVal = True

        return retVal
```

</details>

## [205. Isomorphic Strings](https://leetcode.com/problems/isomorphic-strings/)

- [Official](https://leetcode.cn/problems/isomorphic-strings/solutions/536521/tong-gou-zi-fu-chuan-by-leetcode-solutio-s6fd/)

<details><summary>Description</summary>

```text
Given two strings s and t, determine if they are isomorphic.

Two strings s and t are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while preserving the order of characters.
No two characters may map to the same character, but a character may map to itself.

Example 1:
Input: s = "egg", t = "add"
Output: true

Example 2:
Input: s = "foo", t = "bar"
Output: false

Example 3:
Input: s = "paper", t = "title"
Output: true

Constraints:
1 <= s.length <= 5 * 10^4
t.length == s.length
s and t consist of any valid ascii character.
```

</details>

<details><summary>C</summary>

```c
bool isIsomorphic(char* s, char* t) {
    bool retVal = false;

    int sSize = strlen(s);
    int tSize = strlen(t);
    if (sSize != tSize) {
        return retVal;
    }

#define MAX_HASHTABLE_SIZE (128)  // s and t consist of any valid ascii character.
#define HASHTABLE_INIT_VALUE (-1)
    int hashTableS[MAX_HASHTABLE_SIZE];
    int hashTableT[MAX_HASHTABLE_SIZE];

    int i;
    for (i = 0; i < MAX_HASHTABLE_SIZE; ++i) {
        hashTableS[i] = HASHTABLE_INIT_VALUE;
        hashTableT[i] = HASHTABLE_INIT_VALUE;
    }

    int si, ti;
    for (i = 0; i < sSize; ++i) {
        si = s[i];
        ti = t[i];
        if ((hashTableS[si] != HASHTABLE_INIT_VALUE) && (hashTableS[si] != ti)) {
            return retVal;
        } else if ((hashTableT[ti] != HASHTABLE_INIT_VALUE) && (hashTableT[ti] != si)) {
            return retVal;
        } else {
            hashTableS[si] = ti;
            hashTableT[ti] = si;
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
    bool isIsomorphic(string s, string t) {
        bool retVal = false;

        int sSize = s.size();
        int tSize = t.size();
        if (sSize != tSize) {
            return retVal;
        }

        unordered_map<char, char> hashTableS;
        unordered_map<char, char> hashTableT;
        for (int i = 0; i < sSize; ++i) {
            if ((hashTableS.count(s[i]) != 0) && (hashTableS[s[i]] != t[i])) {
                return retVal;
            } else if ((hashTableT.count(t[i]) != 0) && (hashTableT[t[i]] != s[i])) {
                return retVal;
            } else {
                hashTableS[s[i]] = t[i];
                hashTableT[t[i]] = s[i];
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
    def isIsomorphic(self, s: str, t: str) -> bool:
        retVal = False

        sSize = len(s)
        tSize = len(t)
        if sSize != tSize:
            return retVal

        hashTableS = defaultdict()
        hashTableT = defaultdict()
        for i in range(sSize):
            if (s[i] in hashTableS) and (hashTableS[s[i]] != t[i]):
                return retVal
            elif (t[i] in hashTableT) and (hashTableT[t[i]] != s[i]):
                return retVal
            else:
                hashTableS[s[i]] = t[i]
                hashTableT[t[i]] = s[i]
        retVal = True

        return retVal
```

</details>

## [217. Contains Duplicate](https://leetcode.com/problems/contains-duplicate/)

- [Official](https://leetcode.cn/problems/contains-duplicate/solutions/518991/cun-zai-zhong-fu-yuan-su-by-leetcode-sol-iedd/)

<details><summary>Description</summary>

```text
Given an integer array nums, return true if any value appears at least twice in the array,
and return false if every element is distinct.

Example 1:
Input: nums = [1,2,3,1]
Output: true

Example 2:
Input: nums = [1,2,3,4]
Output: false

Example 3:
Input: nums = [1,1,1,3,3,4,3,2,4,2]
Output: true

Constraints:
1 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9
```

</details>

<details><summary>C</summary>

```c
struct hashStruct {
    int key;
    UT_hash_handle hh;
};
void freeAll(struct hashStruct* pFree) {
    struct hashStruct* current;
    struct hashStruct* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
bool containsDuplicate(int* nums, int numsSize) {
    bool retVal = false;

    struct hashStruct* pHashTable = NULL;
    struct hashStruct* pTemp;
    int i;
    for (i = 0; i < numsSize; ++i) {
        pTemp = NULL;

        HASH_FIND_INT(pHashTable, &nums[i], pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashStruct*)malloc(sizeof(struct hashStruct));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                return retVal;
            }
            pTemp->key = nums[i];
            HASH_ADD_INT(pHashTable, key, pTemp);
        } else {
            retVal = true;
            break;
        }
    }
    freeAll(pHashTable);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    bool containsDuplicate(vector<int>& nums) {
        bool retVal = false;

        unordered_map<int, int> hashTable;
        for (auto num : nums) {
            auto iterator = hashTable.find(num);
            if (iterator != hashTable.end()) {
                retVal = true;
                break;
            }
            hashTable[num] = 1;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def containsDuplicate(self, nums: List[int]) -> bool:
        retVal = False

        hashTable = defaultdict(int)
        for num in nums:
            if num in hashTable:
                retVal = True
                break
            hashTable[num] = 1

        return retVal
```

</details>

## [219. Contains Duplicate II](https://leetcode.com/problems/contains-duplicate-ii/)

- [Official](https://leetcode.cn/problems/contains-duplicate-ii/solutions/1218075/cun-zai-zhong-fu-yuan-su-ii-by-leetcode-kluvk/)

<details><summary>Description</summary>

```text
Given an integer array nums and an integer k, return true
if there are two distinct indices i and j in the array such that nums[i] == nums[j] and abs(i - j) <= k.

Example 1:
Input: nums = [1,2,3,1], k = 3
Output: true

Example 2:
Input: nums = [1,0,1,1], k = 1
Output: true

Example 3:
Input: nums = [1,2,3,1,2,3], k = 2
Output: false

Constraints:
1 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9
0 <= k <= 10^5
```

</details>

<details><summary>C</summary>

```c
struct hashStruct {
    int key;
    int value;
    UT_hash_handle hh;
};
void freeAll(struct hashStruct* pFree) {
    struct hashStruct* current;
    struct hashStruct* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
bool containsNearbyDuplicate(int* nums, int numsSize, int k) {
    bool retVal = false;

    struct hashStruct* pHashTable = NULL;
    struct hashStruct* pTemp;
    int i;
    for (i = 0; i < numsSize; ++i) {
        pTemp = NULL;

        HASH_FIND_INT(pHashTable, &nums[i], pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashStruct*)malloc(sizeof(struct hashStruct));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                return retVal;
            }
            pTemp->key = nums[i];
            pTemp->value = i;
            HASH_ADD_INT(pHashTable, key, pTemp);
            continue;
        }

        if ((i - pTemp->value) <= k) {
            retVal = true;
            break;
        }

        pTemp->value = i;
    }
    freeAll(pHashTable);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        bool retVal = false;

        unordered_map<int, int> hashTable;
        int numsSize = nums.size();
        for (int i = 0; i < numsSize; ++i) {
            auto iterator = hashTable.find(nums[i]);
            if (iterator != hashTable.end()) {
                if (i - iterator->second <= k) {
                    retVal = true;
                    break;
                }
            }
            hashTable[nums[i]] = i;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def containsNearbyDuplicate(self, nums: List[int], k: int) -> bool:
        retVal = False

        hashTable = defaultdict(int)
        for i in range(len(nums)):
            if nums[i] in hashTable:
                if i - hashTable[nums[i]] <= k:
                    retVal = True
                    break
            hashTable[nums[i]] = i

        return retVal
```

</details>

## [229. Majority Element II](https://leetcode.com/problems/majority-element-ii/)

- [Official](https://leetcode.cn/problems/majority-element-ii/solutions/1058790/qiu-zhong-shu-ii-by-leetcode-solution-y1rn/)

<details><summary>Description</summary>

```text
Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.

Example 1:
Input: nums = [3,2,3]
Output: [3]

Example 2:
Input: nums = [1]
Output: [1]

Example 3:
Input: nums = [1,2]
Output: [1,2]

Constraints:
1 <= nums.length <= 5 * 10^4
-10^9 <= nums[i] <= 10^9

Follow up: Could you solve the problem in linear time and in O(1) space?
```

<details><summary>Hint</summary>

```text
1. How many majority elements could it possibly have? Do you have a better hint? Suggest it!
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *majorityElement(int *nums, int numsSize, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;
    int i;

    /* Boyer–Moore majority vote algorithm
     *  https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_majority_vote_algorithm
     */
    int candidate1 = 0;
    int count1 = 0;
    int candidate2 = 0;
    int count2 = 0;
    for (i = 0; i < numsSize; ++i) {
        if ((count1 > 0) && (candidate1 == nums[i])) {
            ++count1;
        } else if ((count2 > 0) && (candidate2 == nums[i])) {
            ++count2;
        } else if (count1 == 0) {
            candidate1 = nums[i];
            ++count1;
        } else if (count2 == 0) {
            candidate2 = nums[i];
            ++count2;
        } else {
            --count1;
            --count2;
        }
    }

    int check1 = 0;
    int check2 = 0;
    for (i = 0; i < numsSize; ++i) {
        if ((nums[i] == candidate1) && (count1 > 0)) {
            ++check1;
        } else if ((nums[i] == candidate2) && (count2 > 0)) {
            ++check2;
        }
    }

    pRetVal = (int *)malloc(2 * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (2 * sizeof(int)));
    if (check1 > numsSize / 3) {
        pRetVal[(*returnSize)++] = candidate1;
    }
    if (check2 > numsSize / 3) {
        pRetVal[(*returnSize)++] = candidate2;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> majorityElement(vector<int>& nums) {
        vector<int> retVal;

        /* Boyer–Moore majority vote algorithm
         *  https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_majority_vote_algorithm
         */
        int candidate1 = 0;
        int count1 = 0;
        int candidate2 = 0;
        int count2 = 0;
        for (int num : nums) {
            if ((count1 > 0) && (candidate1 == num)) {
                ++count1;
            } else if ((count2 > 0) && (candidate2 == num)) {
                ++count2;
            } else if (count1 == 0) {
                candidate1 = num;
                ++count1;
            } else if (count2 == 0) {
                candidate2 = num;
                ++count2;
            } else {
                --count1;
                --count2;
            }
        }

        int check1 = 0;
        int check2 = 0;
        for (int num : nums) {
            if ((num == candidate1) && (count1 > 0)) {
                ++check1;
            } else if ((num == candidate2) && (count2 > 0)) {
                ++check2;
            }
        }

        int numsSize = nums.size();
        if (check1 > numsSize / 3) {
            retVal.emplace_back(candidate1);
        }
        if (check2 > numsSize / 3) {
            retVal.emplace_back(candidate2);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def majorityElement(self, nums: List[int]) -> List[int]:
        retVal = []

        # /* Boyer–Moore majority vote algorithm
        #  *  https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_majority_vote_algorithm
        #  */
        candidate1 = 0
        count1 = 0
        candidate2 = 0
        count2 = 0
        for num in nums:
            if count1 > 0 and candidate1 == num:
                count1 += 1
            elif count2 > 0 and candidate2 == num:
                count2 += 1
            elif count1 == 0:
                candidate1 = num
                count1 += 1
            elif count2 == 0:
                candidate2 = num
                count2 += 1
            else:
                count1 -= 1
                count2 -= 1

        check1 = 0
        check2 = 0
        for num in nums:
            if num == candidate1 and count1 > 0:
                check1 += 1
            elif num == candidate2 and count2 > 0:
                check2 += 1

        numsSize = len(nums)
        if check1 > numsSize/3:
            retVal.append(candidate1)
        if check2 > numsSize/3:
            retVal.append(candidate2)

        return retVal
```

</details>

## [242. Valid Anagram](https://leetcode.com/problems/valid-anagram/)

<details><summary>Description</summary>

```text
Given two strings s and t, return true if t is an anagram of s, and false otherwise.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase,
typically using all the original letters exactly once.

Example 1:
Input: s = "anagram", t = "nagaram"
Output: true

Example 2:
Input: s = "rat", t = "car"
Output: false

Constraints:
1 <= s.length, t.length <= 5 * 10^4
s and t consist of lowercase English letters.

Follow up: What if the inputs contain Unicode characters? How would you adapt your solution to such a case?
```

</details>

<details><summary>C</summary>

```c
bool isAnagram(char* s, char* t) {
    bool retVal = false;

    int sSize = strlen(s);
    int tSize = strlen(t);
    if (sSize != tSize) {
        return retVal;
    }

#define CHAR_RANGE (256)
    int countChar[CHAR_RANGE];
    memset(countChar, 0, sizeof(countChar));
    int i;
    for (i = 0; i < sSize; ++i) {
        countChar[(int)(s[i])]++;
        countChar[(int)(t[i])]--;
    }

    for (i = 0; i < CHAR_RANGE; ++i) {
        if (countChar[i] != 0) {
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
    bool isAnagram(string s, string t) {
        bool retVal = false;

        int sSize = s.size();
        int tSize = t.size();
        if (sSize != tSize) {
            return retVal;
        }

        unordered_map<char, int> HashTable;
        for (int i = 0; i < sSize; ++i) {
            ++HashTable[s[i]];
            --HashTable[t[i]];
        }
        for (auto [key, value] : HashTable) {
            if (value != 0) {
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
    def isAnagram(self, s: str, t: str) -> bool:
        retVal = True

        sSize = len(s)
        tSzie = len(t)
        if sSize != tSzie:
            retVal = False
            return retVal

        letterSize = 26  # s and t consist of lowercase English letters.
        letterCount = [0] * letterSize
        for cS, cT in zip(s, t):
            letterCount[ord(cS) - ord('a')] += 1
            letterCount[ord(cT) - ord('a')] -= 1

        for i in range(letterSize):
            if letterCount[i] != 0:
                retVal = False
                break

        return retVal
```

</details>

<details><summary>Rust</summary>

```rust
impl Solution {
    pub fn is_anagram(s: String, t: String) -> bool {
        let mut ret_val = false;

        let mut s_vector: Vec<char> = s.chars().collect();
        s_vector.sort_by(|a, b| b.cmp(a));

        let mut t_vector: Vec<char> = t.chars().collect();
        t_vector.sort_by(|a, b| b.cmp(a));

        if s_vector == t_vector {
            ret_val = true;
        }

        return ret_val;
    }
}
```

</details>

## [266. Palindrome Permutation](https://leetcode.com/problems/palindrome-permutation/)  unlock

- Subscribe to unlock
  - Facebook
  - Google
  - Microsoft
- [Palindrome Permutation LeetCode Solution](https://www.tutorialcup.com/leetcode-solutions/palindrome-permutation-leetcode-solution.htm)

<details><summary>Description</summary>

```text
Given a string s, return true if a permutation of the string could form a palindrome and false otherwise.

Example 1:
Input: s = "code"
Output: false

Example 2:
Input: s = "aab"
Output: true

Example 3:
Input: s = "carerac"
Output: true

Constraints:
1 <= s.length <= 5000
s consists of only lowercase English letters.
```

</details>

<details><summary>C</summary>

```c
bool canPermutePalindrome(char* s) {
    bool retVal = false;

// s consists of only lowercase English letters.
#define MAX_HASHTABLE (26)
    int HashTable[MAX_HASHTABLE];
    memset(HashTable, 0, sizeof(HashTable));

    int len = strlen(s);
    int i;
    for (i = 0; i < len; ++i) {
        ++HashTable[s[i] - 'a'];
    }

    int count = 0;
    for (i = 0; i < MAX_HASHTABLE; ++i) {
        if (HashTable[i] % 2 == 1) {
            ++count;
        }
    }
    if (count <= 1) {
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
    bool canPermutePalindrome(string s) {
        bool retVal = false;

        unordered_map<char, int> hashTable;
        for (char c : s) {
            ++hashTable[c];
        }

        int count = 0;
        for (auto [key, value] : hashTable) {
            if (value % 2 == 1) {
                ++count;
            }
        }
        if (count <= 1) {
            retVal = true;
        }

        return retVal;
    }
};
```

</details>

## [290. Word Pattern](https://leetcode.com/problems/word-pattern/)

- [Official](https://leetcode.cn/problems/word-pattern/solutions/523102/dan-ci-gui-lu-by-leetcode-solution-6vqv/)

<details><summary>Description</summary>

```text
Given a pattern and a string s, find if s follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in s.

Example 1:
Input: pattern = "abba", s = "dog cat cat dog"
Output: true

Example 2:
Input: pattern = "abba", s = "dog cat cat fish"
Output: false

Example 3:
Input: pattern = "aaaa", s = "dog cat cat dog"
Output: false

Constraints:
1 <= pattern.length <= 300
pattern contains only lower-case English letters.
1 <= s.length <= 3000
s contains only lowercase English letters and spaces ' '.
s does not contain any leading or trailing spaces.
All the words in s are separated by a single space.
```

</details>

<details><summary>C</summary>

```c
struct hashTable {
    int key;
    char* val;
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* pCurrent;
    struct hashTable* pTmp;
    HASH_ITER(hh, pFree, pCurrent, pTmp) {
        // printf("%d: %s\n", pFree->key, pFree->val);
        HASH_DEL(pFree, pCurrent);
        free(pCurrent);
    }
}
bool wordPattern(char* pattern, char* s) {
    bool retVal = false;

    //
    struct hashTable* pHashTableKey = NULL;
    struct hashTable* pHashTableVal = NULL;
    struct hashTable* pTemp;
    int key;
    char* val;

#define SEPARATED " "  // All the words in s are separated by a single space.
    char* pStr = strtok(s, SEPARATED);
    while ((*pattern) && (pStr != NULL)) {
        key = (*pattern);
        val = pStr;

        //
        pTemp = NULL;
        HASH_FIND_INT(pHashTableKey, &key, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                goto exit;
            }
            pTemp->key = key;
            pTemp->val = val;
            HASH_ADD_INT(pHashTableKey, key, pTemp);
        } else {
            if (strcmp(val, pTemp->val) != 0) {
                goto exit;
            }
        }

        //
        pTemp = NULL;
        HASH_FIND_STR(pHashTableVal, val, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                goto exit;
            }
            pTemp->key = key;
            pTemp->val = val;
            HASH_ADD_STR(pHashTableVal, val, pTemp);
        } else {
            if (key != pTemp->key) {
                goto exit;
            }
        }

        ++pattern;
        pStr = strtok(NULL, SEPARATED);
    }
    if ((*pattern) || (pStr != NULL)) {
        goto exit;
    }
    retVal = true;

exit:
    //
    freeAll(pHashTableKey);
    pHashTableKey = NULL;
    freeAll(pHashTableVal);
    pHashTableVal = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    bool wordPattern(string pattern, string s) {
        bool retVal = false;

        vector<string> sList;
        string delimiter = " ";
        size_t pos = 0;
        string token;
        while ((pos = s.find(delimiter)) != string::npos) {
            token = s.substr(0, pos);
            sList.emplace_back(token);
            s.erase(0, pos + delimiter.length());
        }
        sList.emplace_back(s);

        int patternSize = pattern.size();
        int sSize = sList.size();
        if (patternSize != sSize) {
            return retVal;
        }

        unordered_map<char, string> hashTableKey;
        unordered_map<string, char> hashTableVal;
        for (int i = 0; i < patternSize; ++i) {
            if ((hashTableKey.count(pattern[i]) != 0) && (hashTableKey[pattern[i]] != sList[i])) {
                return retVal;
            } else if ((hashTableVal.count(sList[i]) != 0) && (hashTableVal[sList[i]] != pattern[i])) {
                return retVal;
            } else {
                hashTableKey[pattern[i]] = sList[i];
                hashTableVal[sList[i]] = pattern[i];
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
    def wordPattern(self, pattern: str, s: str) -> bool:
        retVal = False

        patternSize = len(pattern)
        sList = s.split()
        sSize = len(sList)
        if patternSize != sSize:
            return retVal

        hashTableKey = defaultdict()
        hashTableVal = defaultdict()
        for key, val in zip(pattern, sList):
            if (key in hashTableKey) and (hashTableKey[key] != val):
                return retVal
            elif (val in hashTableVal) and (hashTableVal[val] != key):
                return retVal
            else:
                hashTableKey[key] = val
                hashTableVal[val] = key
        retVal = True

        return retVal
```

</details>

## [299. Bulls and Cows](https://leetcode.com/problems/bulls-and-cows/)

<details><summary>Description</summary>

```text
You are playing the Bulls and Cows game with your friend.

You write down a secret number and ask your friend to guess what the number is.
When your friend makes a guess, you provide a hint with the following info:

The number of "bulls", which are digits in the guess that are in the correct position.
The number of "cows", which are digits in the guess that are in your secret number but are located in the wrong position.
Specifically, the non-bull digits in the guess that could be rearranged such that they become bulls.

Given the secret number secret and your friend's guess guess, return the hint for your friend's guess.

The hint should be formatted as "xAyB", where x is the number of bulls and y is the number of cows.
Note that both secret and guess may contain duplicate digits.

Example 1:
Input: secret = "1807", guess = "7810"
Output: "1A3B"
Explanation: Bulls are connected with a '|' and cows are underlined:
"1807"
  |
"7810"

Example 2:
Input: secret = "1123", guess = "0111"
Output: "1A1B"
Explanation: Bulls are connected with a '|' and cows are underlined:
"1123"        "1123"
  |      or     |
"0111"        "0111"
Note that only one of the two unmatched 1s is counted as a cow
since the non-bull digits can only be rearranged to allow one 1 to be a bull.

Constraints:
1 <= secret.length, guess.length <= 1000
secret.length == guess.length
secret and guess consist of digits only.
```

</details>

<details><summary>C</summary>

```c
#define MIN(a,b)    (((a)<(b))?(a):(b))

char* getHint(char* secret, char* guess) {
    char* pRetVal = NULL;

#define MAX_INPUT   (2)
#define MAX_DIGITS  (10)
    int Record[MAX_INPUT*MAX_DIGITS] = {0};
    int countA = 0;
    while (*secret) {
        if ((*secret) == (*guess)) {
            ++countA;
        }
        else {
            Record[(unsigned char)(*secret-'0')]++;
            Record[(unsigned char)(*guess-'0') + MAX_DIGITS]++;
        }
        ++secret;
        ++guess;
    }

    int countB = 0;
    int i;
    for (i=0; i<MAX_DIGITS; ++i) {
        countB += MIN(Record[i], Record[i+MAX_DIGITS]);
    }

#define MAX_RETURN_SIZE     (16)
    int returnSize = MAX_RETURN_SIZE * sizeof(char);
    pRetVal = (char*)malloc(returnSize);
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, returnSize);
    snprintf(pRetVal, returnSize, "%dA%dB", countA, countB);

    return pRetVal;
}
```

</details>

## [347. Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/)

- [Official](https://leetcode.com/problems/top-k-frequent-elements/editorial/)
- [Official](https://leetcode.cn/problems/top-k-frequent-elements/solutions/402568/qian-k-ge-gao-pin-yuan-su-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.

Example 1:
Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]

Example 2:
Input: nums = [1], k = 1
Output: [1]

Constraints:
1 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4
k is in the range [1, the number of unique elements in the array].
It is guaranteed that the answer is unique.

Follow up: Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
```

</details>

<details><summary>C</summary>

```c
struct hashTable {
    int key;
    int value;
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        HASH_DEL(pFree, current);
        free(current);
    }
}
int compareIntArray(const void* a1, const void* a2) {
    int* p1 = (int*)a1;
    int* p2 = (int*)a2;

    // descending order
    if (p1[1] == p2[1]) {
        return (p1[0] > p2[0]);
    }
    return (p1[1] < p2[1]);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    //
    int hashTableSize = 0;
    struct hashTable* pMap = NULL;
    struct hashTable* pTmp;
    int i;
    for (i = 0; i < numsSize; ++i) {
        pTmp = NULL;
        HASH_FIND_INT(pMap, &nums[i], pTmp);
        if (pTmp == NULL) {
            pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (pTmp == NULL) {
                perror("malloc");
                freeAll(pMap);
                return pRetVal;
            }
            pTmp->key = nums[i];
            pTmp->value = 1;
            HASH_ADD_INT(pMap, key, pTmp);
            ++hashTableSize;
        } else {
            pTmp->value += 1;
        }
    }

    //
    int sortCounter[hashTableSize][2];
    memset(sortCounter, 0, sizeof(sortCounter));
    i = 0;
    pTmp = NULL;
    struct hashTable* pCurrent = NULL;
    HASH_ITER(hh, pMap, pCurrent, pTmp) {
        sortCounter[i][0] = pCurrent->key;
        sortCounter[i][1] = pCurrent->value;
        ++i;

        HASH_DEL(pMap, pCurrent);
        free(pCurrent);
    }
    qsort(sortCounter, hashTableSize, sizeof(sortCounter[0]), compareIntArray);

    //
    (*returnSize) = k;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));
    for (i = 0; i < (*returnSize); ++i) {
        pRetVal[i] = sortCounter[i][0];
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> retVal;

        unordered_map<int, int> hashTable;
        for (int num : nums) {
            ++hashTable[num];
        }

        priority_queue<pair<int, int>> priorityQueue;
        for (auto iterator = hashTable.begin(); iterator != hashTable.end(); ++iterator) {
            priorityQueue.push(make_pair(iterator->second, iterator->first));
        }
        for (int i = 0; i < k; ++i) {
            retVal.emplace_back(priorityQueue.top().second);
            priorityQueue.pop();
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        retVal = []

        hashTable = Counter(nums)
        for key, value in hashTable.most_common(k):
            retVal.append(key)

        return retVal
```

</details>

## [349. Intersection of Two Arrays](https://leetcode.com/problems/intersection-of-two-arrays/)

- [Official](https://leetcode.com/problems/intersection-of-two-arrays/editorial/)
- [Official](https://leetcode.cn/problems/intersection-of-two-arrays/solutions/469445/liang-ge-shu-zu-de-jiao-ji-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given two integer arrays nums1 and nums2, return an array of their intersection.
Each element in the result must be unique and you may return the result in any order.

Example 1:
Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2]

Example 2:
Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [9,4]
Explanation: [4,9] is also accepted.

Constraints:
1 <= nums1.length, nums2.length <= 1000
0 <= nums1[i], nums2[i] <= 1000
```

</details>

<details><summary>C</summary>

```c
struct hashTable {
    int key;
    int value;
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    //
    int mallocSize = (nums1Size > nums2Size) ? nums1Size : nums2Size;
    pRetVal = (int*)malloc(mallocSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (mallocSize * sizeof(int)));

    //
    struct hashTable* pHashTable = NULL;
    struct hashTable* pTemp;
    int num;
    int i;
    for (i = 0; i < nums1Size; ++i) {
        num = nums1[i];

        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &num, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                return pRetVal;
            }
            pTemp->key = num;
            pTemp->value = 1;
            HASH_ADD_INT(pHashTable, key, pTemp);
        }
    }
    //
    for (i = 0; i < nums2Size; ++i) {
        num = nums2[i];

        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &num, pTemp);
        if (pTemp == NULL) {
            continue;
        }

        if (pTemp->value == 1) {
            pRetVal[(*returnSize)++] = num;
            pTemp->value = 0;
        }
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
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        vector<int> retVal;

        unordered_map<int, int> hashTable;
        for (int num : nums1) {
            hashTable[num] = 1;
        }

        for (int num : nums2) {
            if (hashTable[num] == 1) {
                retVal.push_back(num);
                hashTable[num] = 0;
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
    def intersection(self, nums1: List[int], nums2: List[int]) -> List[int]:
        retVal = []

        hashTable = defaultdict(int)
        for num in nums1:
            hashTable[num] = 1

        for num in nums2:
            if hashTable[num] == 1:
                retVal.append(num)
                hashTable[num] = 0

        return retVal
```

</details>

## [350. Intersection of Two Arrays II](https://leetcode.com/problems/intersection-of-two-arrays-ii/)

- [Official](https://leetcode.cn/problems/intersection-of-two-arrays-ii/solutions/327356/liang-ge-shu-zu-de-jiao-ji-ii-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given two integer arrays nums1 and nums2, return an array of their intersection.
Each element in the result must appear as many times as
it shows in both arrays and you may return the result in any order.

Example 1:
Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2,2]

Example 2:
Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [4,9]
Explanation: [9,4] is also accepted.

Constraints:
1 <= nums1.length, nums2.length <= 1000
0 <= nums1[i], nums2[i] <= 1000

Follow up:
- What if the given array is already sorted? How would you optimize your algorithm?
- What if nums1's size is small compared to nums2's size? Which algorithm is better?
- What if elements of nums2 are stored on disk,
  and the memory is limited such that you cannot load all elements into the memory at once?
```

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    int maxSize = (nums1Size > nums2Size) ? nums1Size : nums2Size;
    pRetVal = (int*)malloc(maxSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (maxSize * sizeof(int)));

#define MAX_RECORD (1001)  // 0 <= nums1[i], nums2[i] <= 1000
    int RECORD[MAX_RECORD];
    memset(RECORD, 0, sizeof(RECORD));
    int i;
    for (i = 0; i < nums1Size; ++i) {
        RECORD[nums1[i]]++;
    }
    for (i = 0; i < nums2Size; ++i) {
        if (RECORD[nums2[i]] != 0) {
            pRetVal[(*returnSize)++] = nums2[i];
            RECORD[nums2[i]]--;
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
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        vector<int> retVal;

        unordered_map<int, int> hashTable;
        for (int num : nums1) {
            hashTable[num] += 1;
        }

        for (int num : nums2) {
            if (hashTable[num] != 0) {
                retVal.push_back(num);
                hashTable[num] -= 1;
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
    def intersect(self, nums1: List[int], nums2: List[int]) -> List[int]:
        retVal = []

        hashTable = defaultdict(int)
        for num in nums1:
            hashTable[num] += 1

        for num in nums2:
            if hashTable[num] != 0:
                retVal.append(num)
                hashTable[num] -= 1

        return retVal
```

</details>

## [380. Insert Delete GetRandom O(1)](https://leetcode.com/problems/insert-delete-getrandom-o1/)

- [Official](https://leetcode.cn/problems/insert-delete-getrandom-o1/solutions/1411578/o1-shi-jian-cha-ru-shan-chu-he-huo-qu-su-rlz2/)

<details><summary>Description</summary>

```text
Implement the RandomizedSet class:
- RandomizedSet()
  Initializes the RandomizedSet object.
- bool insert(int val)
  Inserts an item val into the set if not present. Returns true if the item was not present, false otherwise.
- bool remove(int val)
  Removes an item val from the set if present. Returns true if the item was present, false otherwise.
- int getRandom()
  Returns a random element from the current set of elements (it's guaranteed that at least one element exists
  when this method is called). Each element must have the same probability of being returned.

You must implement the functions of the class such that each function works in average O(1) time complexity.

Example 1:
Input
["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"]
[[], [1], [2], [2], [], [1], [2], []]
Output
[null, true, false, true, 2, true, false, 2]
Explanation
RandomizedSet randomizedSet = new RandomizedSet();
randomizedSet.insert(1); // Inserts 1 to the set. Returns true as 1 was inserted successfully.
randomizedSet.remove(2); // Returns false as 2 does not exist in the set.
randomizedSet.insert(2); // Inserts 2 to the set, returns true. Set now contains [1,2].
randomizedSet.getRandom(); // getRandom() should return either 1 or 2 randomly.
randomizedSet.remove(1); // Removes 1 from the set, returns true. Set now contains [2].
randomizedSet.insert(2); // 2 was already in the set, so return false.
randomizedSet.getRandom(); // Since 2 is the only number in the set, getRandom() will always return 2.

Constraints:
-2^31 <= val <= 2^31 - 1
At most 2 * 10^5 calls will be made to insert, remove, and getRandom.
There will be at least one element in the data structure when getRandom is called.
```

</details>

<details><summary>C</summary>

```c
struct hashStruct {
    int val;
    UT_hash_handle hh;
};
typedef struct {
    struct hashStruct* map;
} RandomizedSet;
RandomizedSet* randomizedSetCreate() {
    RandomizedSet* pNew = (RandomizedSet*)malloc(sizeof(RandomizedSet));
    if (pNew == NULL) {
        perror("malloc");
        return pNew;
    }
    pNew->map = NULL;

    return pNew;
}
bool randomizedSetInsert(RandomizedSet* obj, int val) {
    bool retVal = false;

    struct hashStruct* temp = NULL;
    HASH_FIND_INT(obj->map, &val, temp);
    if (temp != NULL) {
        return retVal;
    }
    temp = (struct hashStruct*)malloc(sizeof(struct hashStruct));
    if (temp == NULL) {
        perror("malloc");
        return retVal;
    }
    temp->val = val;
    HASH_ADD_INT(obj->map, val, temp);
    retVal = true;

    return retVal;
}
bool randomizedSetRemove(RandomizedSet* obj, int val) {
    bool retVal = false;

    struct hashStruct* temp = NULL;
    HASH_FIND_INT(obj->map, &val, temp);
    if (temp == NULL) {
        return retVal;
    }
    HASH_DEL(obj->map, temp);
    free(temp);
    retVal = true;

    return retVal;
}
int randomizedSetGetRandom(RandomizedSet* obj) {
    int retVal = 0;

    int idx = rand() % (HASH_COUNT(obj->map));
    struct hashStruct* temp = obj->map;
    while ((idx > 0) && (temp != NULL)) {
        temp = temp->hh.next;
        --idx;
    }
    retVal = temp->val;

    return retVal;
}
void randomizedSetFree(RandomizedSet* obj) {
    struct hashStruct* current;
    struct hashStruct* tmp;
    HASH_ITER(hh, obj->map, current, tmp) {
        // printf("%d\n", obj->map->val);
        HASH_DEL(obj->map, current);
        free(current);
    }
    free(obj);
    obj = NULL;
}
/**
 * Your RandomizedSet struct will be instantiated and called as such:
 * RandomizedSet* obj = randomizedSetCreate();
 * bool param_1 = randomizedSetInsert(obj, val);
 * bool param_2 = randomizedSetRemove(obj, val);
 * int param_3 = randomizedSetGetRandom(obj);
 * randomizedSetFree(obj);
 */
```

</details>

<details><summary>C++</summary>

```c++
class RandomizedSet {
   private:
    vector<int> nums;
    unordered_map<int, int> indices;

   public:
    RandomizedSet() {
        //
        srand((unsigned)time(NULL));
    }
    bool insert(int val) {
        bool retVal = false;

        if (indices.count(val) != 0) {
            return retVal;
        }
        int index = nums.size();
        nums.emplace_back(val);
        indices[val] = index;
        retVal = true;

        return retVal;
    }
    bool remove(int val) {
        bool retVal = false;

        if (indices.count(val) == 0) {
            return retVal;
        }
        int index = indices[val];
        int last = nums.back();
        nums[index] = last;
        indices[last] = index;
        nums.pop_back();
        indices.erase(val);
        retVal = true;

        return retVal;
    }
    int getRandom() {
        int retVal = 0;

        int randomIndex = rand() % nums.size();
        retVal = nums[randomIndex];

        return retVal;
    }
};
/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
```

</details>

<details><summary>Python3</summary>

```python
class RandomizedSet:
    def __init__(self):
        self.nums = []
        self.indices = {}

    def insert(self, val: int) -> bool:
        retVal = False

        if val in self.indices:
            return retVal
        self.indices[val] = len(self.nums)
        self.nums.append(val)
        retVal = True

        return retVal

    def remove(self, val: int) -> bool:
        retVal = False

        if val not in self.indices:
            return retVal
        id = self.indices[val]
        self.nums[id] = self.nums[-1]
        self.indices[self.nums[id]] = id
        self.nums.pop()
        del self.indices[val]
        retVal = True

        return retVal

    def getRandom(self) -> int:
        retVal = 0

        retVal = choice(self.nums)

        return retVal

# Your RandomizedSet object will be instantiated and called as such:
# obj = RandomizedSet()
# param_1 = obj.insert(val)
# param_2 = obj.remove(val)
# param_3 = obj.getRandom()
```

</details>

## [383. Ransom Note](https://leetcode.com/problems/ransom-note/)

- [Official](https://leetcode.cn/problems/ransom-note/solutions/1135839/shu-jin-xin-by-leetcode-solution-ji8a/)

<details><summary>Description</summary>

```text
Given two strings ransomNote and magazine,
return true if ransomNote can be constructed by using the letters from magazine and false otherwise.

Each letter in magazine can only be used once in ransomNote.

Example 1:
Input: ransomNote = "a", magazine = "b"
Output: false

Example 2:
Input: ransomNote = "aa", magazine = "ab"
Output: false

Example 3:
Input: ransomNote = "aa", magazine = "aab"
Output: true

Constraints:
1 <= ransomNote.length, magazine.length <= 10^5
ransomNote and magazine consist of lowercase English letters.
```

</details>

<details><summary>C</summary>

```c
bool canConstruct(char* ransomNote, char* magazine) {
    bool retVal = false;

    int ransomNoteSize = strlen(ransomNote);
    int magazineSize = strlen(magazine);
    if (ransomNoteSize > magazineSize) {
        return retVal;
    }

    // ransomNote and magazine consist of lowercase English letters.
#define LETTER_SIZE (26)
    int hashTable[LETTER_SIZE];
    memset(hashTable, 0, sizeof(hashTable));

    int i;
    for (i = 0; i < ransomNoteSize; ++i) {
        --hashTable[ransomNote[i] - 'a'];
        ++hashTable[magazine[i] - 'a'];
    }
    for (i = ransomNoteSize; i < magazineSize; ++i) {
        ++hashTable[magazine[i] - 'a'];
    }

    for (i = 0; i < LETTER_SIZE; ++i) {
        if (hashTable[i] < 0) {
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
   private:
    // ransomNote and magazine consist of lowercase English letters.
    int letterSize = 26;

   public:
    bool canConstruct(string ransomNote, string magazine) {
        bool retVal = false;

        int ransomNoteSize = ransomNote.size();
        int magazineSize = magazine.size();
        if (ransomNoteSize > magazineSize) {
            return retVal;
        }

        vector<int> hashTable(letterSize, 0);
        for (int i = 0; i < ransomNoteSize; ++i) {
            --hashTable[ransomNote[i] - 'a'];
            ++hashTable[magazine[i] - 'a'];
        }
        for (int i = ransomNoteSize; i < magazineSize; ++i) {
            ++hashTable[magazine[i] - 'a'];
        }

        for (int i = 0; i < letterSize; ++i) {
            if (hashTable[i] < 0) {
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
    def __init__(self) -> None:
        # ransomNote and magazine consist of lowercase English letters.
        self.letterSize = 26

    def canConstruct(self, ransomNote: str, magazine: str) -> bool:
        retVal = False

        ransomNoteSize = len(ransomNote)
        magazineSize = len(magazine)
        if magazineSize < ransomNoteSize:
            return retVal

        hashTable = [0] * self.letterSize
        for i in range(ransomNoteSize):
            hashTable[ord(ransomNote[i]) - ord('a')] -= 1
            hashTable[ord(magazine[i]) - ord('a')] += 1
        for i in range(ransomNoteSize, magazineSize):
            hashTable[ord(magazine[i]) - ord('a')] += 1

        for i in range(self.letterSize):
            if hashTable[i] < 0:
                return retVal
        retVal = True

        return retVal
```

</details>

## [387. First Unique Character in a String](https://leetcode.com/problems/first-unique-character-in-a-string/)

- [Official](https://leetcode.com/problems/first-unique-character-in-a-string/editorial/)
- [Official](https://leetcode.cn/problems/first-unique-character-in-a-string/solutions/531740/zi-fu-chuan-zhong-de-di-yi-ge-wei-yi-zi-x9rok/)

<details><summary>Description</summary>

```text
Given a string s, find the first non-repeating character in it and return its index. If it does not exist, return -1.

Example 1:
Input: s = "leetcode"
Output: 0

Example 2:
Input: s = "loveleetcode"
Output: 2

Example 3:
Input: s = "aabb"
Output: -1

Constraints:
1 <= s.length <= 10^5
s consists of only lowercase English letters.
```

</details>

<details><summary>C</summary>

```c
int firstUniqChar(char* s) {
    int retVal = -1;

#define MAX_HASHTABLE_SIZE (26)  // s consists of only lowercase English letters.
    int hashTable[MAX_HASHTABLE_SIZE];
    memset(hashTable, 0, sizeof(hashTable));

    int sSize = strlen(s);
    int idx;
    int i;
    for (i = 0; i < sSize; ++i) {
        idx = s[i] - 'a';
        ++hashTable[idx];
    }

    for (i = 0; i < sSize; ++i) {
        idx = s[i] - 'a';
        if (hashTable[idx] == 1) {
            retVal = i;
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
    int firstUniqChar(string s) {
        int retVal = -1;

        int sSize = s.size();

        unordered_map<char, int> hashTable;
        for (int i = 0; i < sSize; ++i) {
            hashTable[s[i]] += 1;
        }

        for (int i = 0; i < sSize; ++i) {
            if (hashTable[s[i]] == 1) {
                retVal = i;
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
    def firstUniqChar(self, s: str) -> int:
        retVal = -1

        hashTable = defaultdict(int)
        for c in s:
            hashTable[c] += 1

        for idx, c in enumerate(s):
            if hashTable[c] == 1:
                retVal = idx
                break

        return retVal
```

</details>

## [409. Longest Palindrome](https://leetcode.com/problems/longest-palindrome/)

- [Official](https://leetcode.com/problems/longest-palindrome/editorial/)
- [Official](https://leetcode.cn/problems/longest-palindrome/solutions/156931/zui-chang-hui-wen-chuan-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given a string s which consists of lowercase or uppercase letters,
return the length of the longest palindrome that can be built with those letters.

Letters are case sensitive, for example, "Aa" is not considered a palindrome here.

Example 1:
Input: s = "abccccdd"
Output: 7
Explanation: One longest palindrome that can be built is "dccaccd", whose length is 7.

Example 2:
Input: s = "a"
Output: 1
Explanation: The longest palindrome that can be built is "a", whose length is 1.

Constraints:
1 <= s.length <= 2000
s consists of lowercase and/or uppercase English letters only.
```

</details>

<details><summary>C</summary>

```c
int longestPalindrome(char* s) {
    int retVal = 0;

#define MAX_FREQUENCY_SIZE (128)  // s consists of lowercase and/or uppercase English letters only.
    int frequency[MAX_FREQUENCY_SIZE];
    memset(frequency, 0, sizeof(frequency));
    int sSize = strlen(s);
    int idx;
    int i;
    for (i = 0; i < sSize; ++i) {
        idx = s[i];
        frequency[idx] += 1;
    }

    int value;
    for (i = 0; i < MAX_FREQUENCY_SIZE; ++i) {
        value = frequency[i];
        retVal += (value / 2 * 2);
        if ((value % 2 == 1) && (retVal % 2 == 0)) {
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
    int longestPalindrome(string s) {
        int retVal = 0;

        unordered_map<char, int> frequency;
        for (char c : s) {
            ++frequency[c];
        }

        for (auto p : frequency) {
            int value = p.second;
            retVal += (value / 2 * 2);
            if ((value % 2 == 1) && (retVal % 2 == 0)) {
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
    def longestPalindrome(self, s: str) -> int:
        retVal = 0

        frequency = Counter(s)
        for value in frequency.values():
            retVal += (value // 2 * 2)
            if (retVal % 2 == 0) and (value % 2 == 1):
                retVal += 1

        return retVal
```

</details>

## [442. Find All Duplicates in an Array](https://leetcode.com/problems/find-all-duplicates-in-an-array/)

- [Official](https://leetcode.cn/problems/find-all-duplicates-in-an-array/solutions/1473718/shu-zu-zhong-zhong-fu-de-shu-ju-by-leetc-782l/)

<details><summary>Description</summary>

```text
Given an integer array nums of length n where all the integers of nums are in the range [1, n]
and each integer appears once or twice,
return an array of all the integers that appears twice.

You must write an algorithm that runs in O(n) time and uses only constant extra space.

Example 1:
Input: nums = [4,3,2,7,8,2,3,1]
Output: [2,3]

Example 2:
Input: nums = [1,1,2]
Output: [1]

Example 3:
Input: nums = [1]
Output: []

Constraints:
n == nums.length
1 <= n <= 10^5
1 <= nums[i] <= n
Each element in nums appears once or twice.
```

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *findDuplicates(int *nums, int numsSize, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int *)malloc(numsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (numsSize * sizeof(int)));

    int idx;
    int i;
    for (i = 0; i < numsSize; ++i) {
        idx = abs(nums[i]);
        if (nums[idx - 1] > 0) {
            // in the range [1, n]
            nums[idx - 1] *= (-1);
        } else {
            // each integer appears once or twice
            pRetVal[(*returnSize)++] = idx;
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
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> retVal;

        for (int num : nums) {
            int idx = abs(num);
            if (nums[idx - 1] > 0) {
                // in the range [1, n]
                nums[idx - 1] *= (-1);
            } else {
                // each integer appears once or twice
                retVal.emplace_back(idx);
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
    def findDuplicates(self, nums: List[int]) -> List[int]:
        retVal = []

        for num in nums:
            idx = abs(num)
            if nums[idx-1] > 0:     # in the range [1, n]
                nums[idx-1] *= (-1)
            else:                   # each integer appears once or twice
                retVal.append(idx)

        return retVal
```

</details>

## [448. Find All Numbers Disappeared in an Array](https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/)

<details><summary>Description</summary>

```text
Given an array nums of n integers where nums[i] is in the range [1, n],
return an array of all the integers in the range [1, n] that do not appear in nums.

Example 1:
Input: nums = [4,3,2,7,8,2,3,1]
Output: [5,6]

Example 2:
Input: nums = [1,1]
Output: [2]

Constraints:
n == nums.length
1 <= n <= 10^5
1 <= nums[i] <= n

Follow up:
Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.
```

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findDisappearedNumbers(int* nums, int numsSize, int* returnSize){
    int* pRetVal = NULL;

#if 1
    *returnSize = numsSize;

    int idx;
    int i;
    for (i=0; i<numsSize; ++i)
    {
        idx = abs(nums[i]) - 1;
        if (nums[idx] > 0)
        {
            nums[idx] = 0 - nums[idx];
            (*returnSize)--;
        }
    }
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL)
    {
        perror("malloc");
        return pRetVal;
    }

    idx = 0;
    for (i=0; i<numsSize; ++i)
    {
        if (nums[i] > 0)
        {
            pRetVal[idx++] = i + 1;
        }
    }
#else
    *returnSize = numsSize;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL)
    {
        perror("malloc");
        return pRetVal;
    }

    int i;
    for (i=0; i<(*returnSize); ++i)
    {
        pRetVal[i] = i + 1;
    }

    for (i=0; i<numsSize; ++i)
    {
        pRetVal[nums[i] - 1] = 0;
    }

    *returnSize = 0;
    for (i=0; i<numsSize; ++i)
    {
        if (pRetVal[i] != 0)
        {
            pRetVal[*returnSize] = pRetVal[i];
            (*returnSize)++;
        }
    }
#endif

    return pRetVal;
}
```

</details>

## [451. Sort Characters By Frequency](https://leetcode.com/problems/sort-characters-by-frequency/)

- [Official](https://leetcode.cn/problems/sort-characters-by-frequency/solutions/855833/gen-ju-zi-fu-chu-xian-pin-lu-pai-xu-by-l-zmvy/)

<details><summary>Description</summary>

```text
Given a string s, sort it in decreasing order based on the frequency of the characters.
The frequency of a character is the number of times it appears in the string.

Return the sorted string. If there are multiple answers, return any of them.

Example 1:
Input: s = "tree"
Output: "eert"
Explanation: 'e' appears twice while 'r' and 't' both appear once.
So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.

Example 2:
Input: s = "cccaaa"
Output: "aaaccc"
Explanation: Both 'c' and 'a' appear three times, so both "cccaaa" and "aaaccc" are valid answers.
Note that "cacaca" is incorrect, as the same characters must be together.

Example 3:
Input: s = "Aabb"
Output: "bbAa"
Explanation: "bbaA" is also a valid answer, but "Aabb" is incorrect.
Note that 'A' and 'a' are treated as two different characters.

Constraints:
1 <= s.length <= 5 * 10^5
s consists of uppercase and lowercase English letters and digits.
```

</details>

<details><summary>C</summary>

```c
int compareIntArray(const void *pa, const void *pb) {
    const int *a = *(const int **)pa;
    const int *b = *(const int **)pb;

    // descending order
    if (a[1] == b[1]) {
        return b[0] - a[0];
    } else {
        return b[1] - a[1];
    }
}
char *frequencySort(char *s) {
    char *pRetVal = s;

    int i, j;

#define HASHTABLE_SIZE (128)  // s consists of uppercase and lowercase English letters and digits.
    int **pHashTable = (int **)malloc(HASHTABLE_SIZE * sizeof(int *));
    if (pHashTable == NULL) {
        perror("malloc");
        return pRetVal;
    }
    for (i = 0; i < HASHTABLE_SIZE; ++i) {
        pHashTable[i] = (int *)malloc(2 * sizeof(int));
        if (pHashTable[i] == NULL) {
            perror("malloc");
            goto exit;
        }
        pHashTable[i][0] = i;
        pHashTable[i][1] = 0;
    }

    int idx;
    int sSize = strlen(s);
    for (i = 0; i < sSize; ++i) {
        idx = s[i];
        ++pHashTable[idx][1];
    }
    qsort(pHashTable, HASHTABLE_SIZE, sizeof(pHashTable[0]), compareIntArray);
    idx = 0;
    for (i = 0; i < HASHTABLE_SIZE; ++i) {
        for (j = 0; j < pHashTable[i][1]; ++j) {
            s[idx++] = pHashTable[i][0];
        }
    }

exit:
    for (j = 0; j < i; ++j) {
        free(pHashTable[j]);
        pHashTable[j] = NULL;
    }
    free(pHashTable);
    pHashTable = NULL;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string frequencySort(string s) {
        string retVal;

        unordered_map<char, int> hashTable;
        for (auto &c : s) {
            hashTable[c]++;
        }

        vector<pair<char, int>> sortHashTable;
        for (auto &iterator : hashTable) {
            sortHashTable.emplace_back(iterator);
        }
        sort(sortHashTable.begin(), sortHashTable.end(),
             [](const pair<char, int> &a, const pair<char, int> &b) { return a.second > b.second; });

        for (auto &iterator : sortHashTable) {
            for (int i = 0; i < iterator.second; ++i) {
                retVal.push_back(iterator.first);
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
    def frequencySort(self, s: str) -> str:
        retVal = ""

        hashTable = defaultdict(int)
        for c in s:
            hashTable[c] += 1
        sortHashTable = sorted(hashTable.items(), key=lambda kv: kv[1], reverse=True)

        for key, value in sortHashTable:
            for _ in range(value):
                retVal += key

        return retVal
```

</details>

## [523. Continuous Subarray Sum](https://leetcode.com/problems/continuous-subarray-sum/)

- [Official](https://leetcode.com/problems/continuous-subarray-sum/editorial/)
- [Official](https://leetcode.cn/problems/continuous-subarray-sum/solutions/807930/lian-xu-de-zi-shu-zu-he-by-leetcode-solu-rdzi/)

<details><summary>Description</summary>

```text
Given an integer array nums and an integer k,
return true if nums has a continuous subarray of size at least two whose elements sum up to a multiple of k,
or false otherwise.

An integer x is a multiple of k if there exists an integer n such that x = n * k.
0 is always a multiple of k.

Example 1:
Input: nums = [23,2,4,6,7], k = 6
Output: true
Explanation: [2, 4] is a continuous subarray of size 2 whose elements sum up to 6.

Example 2:
Input: nums = [23,2,6,4,7], k = 6
Output: true
Explanation: [23, 2, 6, 4, 7] is an continuous subarray of size 5 whose elements sum up to 42.
42 is a multiple of 6 because 42 = 7 * 6 and 7 is an integer.

Example 3:
Input: nums = [23,2,6,4,7], k = 13
Output: false

Constraints:
1 <= nums.length <= 10^5
0 <= nums[i] <= 10^9
0 <= sum(nums[i]) <= 2^31 - 1
1 <= k <= 2^31 - 1
```

</details>

<details><summary>C</summary>

```c
struct hashTable {
    int key;
    int value;
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
bool checkSubarraySum(int* nums, int numsSize, int k) {
    bool retVal = false;

    struct hashTable* pMmodSeen = NULL;
    struct hashTable* pTmp = NULL;
    pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
    if (pTmp == NULL) {
        goto exit;
    }
    pTmp->key = 0;
    pTmp->value = -1;
    HASH_ADD_INT(pMmodSeen, key, pTmp);

    int prefixMod = 0;
    int i;
    for (i = 0; i < numsSize; i++) {
        prefixMod = (prefixMod + nums[i]) % k;

        pTmp = NULL;
        HASH_FIND_INT(pMmodSeen, &prefixMod, pTmp);
        if (pTmp != NULL) {  // ensures that the size of subarray is atleast 2
            if (i - pTmp->value > 1) {
                retVal = true;
                break;
            }
        } else {  // mark the value of prefixMod with the current index.
            pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (pTmp == NULL) {
                goto exit;
            }
            pTmp->key = prefixMod;
            pTmp->value = i;
            HASH_ADD_INT(pMmodSeen, key, pTmp);
        }
    }

exit:
    //
    freeAll(pMmodSeen);
    pMmodSeen = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        bool retVal = false;

        int prefixMod = 0;
        unordered_map<int, int> modSeen;
        modSeen[0] = -1;

        int numsSize = nums.size();
        for (int i = 0; i < numsSize; i++) {
            prefixMod = (prefixMod + nums[i]) % k;
            if (modSeen.find(prefixMod) != modSeen.end()) {  // ensures that the size of subarray is atleast 2
                if (i - modSeen[prefixMod] > 1) {
                    retVal = true;
                    break;
                }
            } else {  // mark the value of prefixMod with the current index.
                modSeen[prefixMod] = i;
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
    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        retVal = False

        numsSize = len(nums)
        prefix_mod = 0
        mod_seen = {0: -1}
        for i in range(numsSize):
            prefix_mod = (prefix_mod + nums[i]) % k
            if prefix_mod in mod_seen:  # ensures that the size of subarray is at least 2
                if i - mod_seen[prefix_mod] > 1:
                    retVal = True
                    break
            else:   # mark the value of prefix_mod with the current index.
                mod_seen[prefix_mod] = i

        return retVal
```

</details>

## [525. Contiguous Array](https://leetcode.com/problems/contiguous-array/)

- [Official](https://leetcode.com/problems/contiguous-array/editorial/)
- [Official](https://leetcode.cn/problems/contiguous-array/solutions/809683/lian-xu-shu-zu-by-leetcode-solution-mvnm/)

<details><summary>Description</summary>

```text
Given a binary array nums, return the maximum length of a contiguous subarray with an equal number of 0 and 1.

Example 1:
Input: nums = [0,1]
Output: 2
Explanation: [0, 1] is the longest contiguous subarray with an equal number of 0 and 1.

Example 2:
Input: nums = [0,1,0]
Output: 2
Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.

Constraints:
1 <= nums.length <= 10^5
nums[i] is either 0 or 1.
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
int findMaxLength(int *nums, int numsSize) {
    int retVal = 0;

    int sum = 0;
    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp = NULL;
    pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
    if (pTemp == NULL) {
        perror("malloc");
        goto exit;
    }
    pTemp->key = sum;
    pTemp->value = -1;
    HASH_ADD_INT(pHashTable, key, pTemp);

    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] == 1) {
            sum++;
        } else if (nums[i] == 0) {
            sum--;
        }

        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &sum, pTemp);
        if (pTemp != NULL) {
            retVal = fmax(retVal, i - pTemp->value);
        } else {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                goto exit;
            }
            pTemp->key = sum;
            pTemp->value = i;
            HASH_ADD_INT(pHashTable, key, pTemp);
        }
    }

exit:
    freeAll(pHashTable);
    pHashTable = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int findMaxLength(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        int sum = 0;
        unordered_map<int, int> hashTable;
        hashTable[sum] = -1;
        for (int i = 0; i < numsSize; ++i) {
            if (nums[i] == 1) {
                sum++;
            } else if (nums[i] == 0) {
                sum--;
            }

            if (hashTable.count(sum) > 0) {
                retVal = max(retVal, i - hashTable[sum]);
            } else {
                hashTable[sum] = i;
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
    def findMaxLength(self, nums: List[int]) -> int:
        retVal = 0

        hashTable = defaultdict(int)

        sum = 0
        hashTable[sum] = -1
        for idx, num in enumerate(nums):
            if num == 1:
                sum += 1
            elif num == 0:
                sum -= 1

            if sum in hashTable:
                retVal = max(retVal, idx-hashTable[sum])
            else:
                hashTable[sum] = idx

        return retVal
```

</details>

## [560. Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/)

- [Official](https://leetcode.cn/problems/subarray-sum-equals-k/solutions/238572/he-wei-kde-zi-shu-zu-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals to k.

A subarray is a contiguous non-empty sequence of elements within an array.

Example 1:
Input: nums = [1,1,1], k = 2
Output: 2

Example 2:
Input: nums = [1,2,3], k = 3
Output: 2

Constraints:
1 <= nums.length <= 2 * 10^4
-1000 <= nums[i] <= 1000
-10^7 <= k <= 10^7
```

<details><summary>Hint</summary>

```text
1. Will Brute force work here? Try to optimize it.
2. Can we optimize it by using some extra space?
3. What about storing sum frequencies in a hash table? Will it be useful?
4. sum(i,j)=sum(0,j)-sum(0,i), where sum(i,j) represents the sum of all the elements from index i to j-1.
   Can we use this property to optimize it.
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
        HASH_DEL(pFree, current);
        free(current);
    }
}
int subarraySum(int *nums, int numsSize, int k) {
    int retVal = 0;

    struct hashTable *pPrefixSumMap = NULL;
    struct hashTable *pTmp = NULL;
    pTmp = (struct hashTable *)malloc(sizeof(struct hashTable));
    if (pTmp == NULL) {
        perror("malloc");
        freeAll(pPrefixSumMap);
        return retVal;
    }
    pTmp->key = 0;
    pTmp->value = 1;
    HASH_ADD_INT(pPrefixSumMap, key, pTmp);

    int prefixSum = 0;
    int num;
    int i;
    for (i = 0; i < numsSize; ++i) {
        prefixSum += nums[i];

        num = prefixSum - k;
        pTmp = NULL;
        HASH_FIND_INT(pPrefixSumMap, &num, pTmp);
        if (pTmp != NULL) {
            retVal += pTmp->value;
        }

        num = prefixSum;
        pTmp = NULL;
        HASH_FIND_INT(pPrefixSumMap, &num, pTmp);
        if (pTmp == NULL) {
            pTmp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTmp == NULL) {
                perror("malloc");
                freeAll(pPrefixSumMap);
                return retVal;
            }
            pTmp->key = num;
            pTmp->value = 1;
            HASH_ADD_INT(pPrefixSumMap, key, pTmp);
        } else {
            pTmp->value += 1;
        }
    }
    freeAll(pPrefixSumMap);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int subarraySum(vector<int>& nums, int k) {
        int retVal = 0;

        unordered_map<int, int> prefixSumMap;
        prefixSumMap[0] = 1;

        int prefixSum = 0;
        for (auto& num : nums) {
            prefixSum += num;
            if (prefixSumMap.find(prefixSum - k) != prefixSumMap.end()) {
                retVal += prefixSumMap[prefixSum - k];
            }
            prefixSumMap[prefixSum]++;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def subarraySum(self, nums: List[int], k: int) -> int:
        retVal = 0

        prefixSumMap = defaultdict(int)
        prefixSumMap[0] = 1

        prefixSum = 0
        for num in nums:
            prefixSum += num
            if (prefixSum - k) in prefixSumMap:
                retVal += prefixSumMap[prefixSum - k]
            prefixSumMap[prefixSum] += 1

        return retVal
```

</details>

## [645. Set Mismatch](https://leetcode.com/problems/set-mismatch/)

- [Official](https://leetcode.cn/problems/set-mismatch/solutions/857255/cuo-wu-de-ji-he-by-leetcode-solution-1ea4/)

<details><summary>Description</summary>

```text
You have a set of integers s, which originally contains all the numbers from 1 to n.
Unfortunately, due to some error, one of the numbers in s got duplicated to another number in the set,
which results in repetition of one number and loss of another number.

You are given an integer array nums representing the data status of this set after the error.

Find the number that occurs twice and the number that is missing and return them in the form of an array.

Example 1:
Input: nums = [1,2,2,4]
Output: [2,3]

Example 2:
Input: nums = [1,1]
Output: [1,2]

Constraints:
2 <= nums.length <= 10^4
1 <= nums[i] <= 10^4
```

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findErrorNums(int* nums, int numsSize, int* returnSize) {
    int* pRetVal = NULL;

    int hashTable[numsSize + 1];
    memset(hashTable, 0, sizeof(hashTable));
    int i;
    for (i = 0; i < numsSize; ++i) {
        hashTable[nums[i]]++;
    }

    (*returnSize) = 2;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, (*returnSize) * sizeof(int));
    for (i = 1; i <= numsSize; ++i) {
        if (hashTable[i] == 2) {
            pRetVal[0] = i;
        } else if (hashTable[i] == 0) {
            pRetVal[1] = i;
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
    vector<int> findErrorNums(vector<int>& nums) {
        vector<int> retVal(2, 0);

        int numsSize = nums.size() + 1;
        vector<int> hashTable(numsSize, 0);
        for (int num : nums) {
            hashTable[num]++;
        }

        for (int i = 1; i < numsSize; ++i) {
            if (hashTable[i] == 2) {
                retVal[0] = i;
            } else if (hashTable[i] == 0) {
                retVal[1] = i;
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
    def findErrorNums(self, nums: List[int]) -> List[int]:
        retVal = [0] * 2

        hashTable = defaultdict(int)
        for num in nums:
            hashTable[num] += 1

        numSize = len(nums)
        for i in range(1, numSize+1):
            if hashTable[i] == 2:
                retVal[0] = i
            elif hashTable[i] == 0:
                retVal[1] = i

        return retVal
```

</details>

## [648. Replace Words](https://leetcode.com/problems/replace-words/)

- [Official](https://leetcode.com/problems/replace-words/editorial/)
- [Official](https://leetcode.cn/problems/replace-words/solutions/1649109/dan-ci-ti-huan-by-leetcode-solution-pl6v/)

<details><summary>Description</summary>

```text
In English, we have a concept called root,
which can be followed by some other word to form another longer word - let's call this word derivative.
For example, when the root "help" is followed by the word "ful", we can form a derivative "helpful".

Given a dictionary consisting of many roots and a sentence consisting of words separated by spaces,
replace all the derivatives in the sentence with the root forming it.
If a derivative can be replaced by more than one root, replace it with the root that has the shortest length.

Return the sentence after the replacement.

Example 1:
Input: dictionary = ["cat","bat","rat"], sentence = "the cattle was rattled by the battery"
Output: "the cat was rat by the bat"

Example 2:
Input: dictionary = ["a","b","c"], sentence = "aadsfasf absbs bbab cadsfafs"
Output: "a a b c"

Constraints:
1 <= dictionary.length <= 1000
1 <= dictionary[i].length <= 100
dictionary[i] consists of only lower-case letters.
1 <= sentence.length <= 10^6
sentence consists of only lower-case letters and spaces.
The number of words in sentence is in the range [1, 1000]
The length of each word in sentence is in the range [1, 1000]
Every two consecutive words in sentence will be separated by exactly one space.
sentence does not have leading or trailing spaces.
```

</details>

<details><summary>C</summary>

```c
#define MAX_BUF_SIZE (1024)
#define MAX_LETTERS (26)  // dictionary[i] consists of only lower-case letters.
typedef struct Trie {
    bool isEnd;
    struct Trie *children[MAX_LETTERS];
} Trie;
Trie *creatTrie() {
    Trie *pRetVal = NULL;

    pRetVal = (Trie *)malloc(sizeof(Trie));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int i;
    for (i = 0; i < MAX_LETTERS; i++) {
        pRetVal->children[i] = NULL;
    }
    pRetVal->isEnd = false;

    return pRetVal;
}
void freeTrie(Trie *root) {
    int i;
    for (i = 0; i < MAX_LETTERS; i++) {
        if (root->children[i] != NULL) {
            freeTrie(root->children[i]);
        }
    }
    free(root);
    root = NULL;
}
void findRoot(const char *word, Trie *trie, char *pRetVal) {
    int wordSize = strlen(word);
    Trie *pCurrent = trie;

    int idx = 0;
    char c;
    int i;
    for (i = 0; i < wordSize; i++) {
        if (pCurrent->isEnd == true) {
            pRetVal[idx] = 0;
            return;
        }

        c = word[i];
        if (pCurrent->children[c - 'a'] == NULL) {
            snprintf(pRetVal, MAX_BUF_SIZE, "%s", word);
            return;
        }
        pRetVal[idx++] = c;
        pCurrent = pCurrent->children[c - 'a'];
    }
    pRetVal[idx] = 0;
}
char *replaceWords(char **dictionary, int dictionarySize, char *sentence) {
    char *pRetVal = NULL;

    //
    int sentenceSize = strlen(sentence);
    pRetVal = (char *)malloc((sentenceSize + 4) * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, ((sentenceSize + 1) * sizeof(char)));

    //
    Trie *pDictionaryTrie = creatTrie();
    Trie *pCurrent;
    char c;
    int len;
    int i, j;
    for (i = 0; i < dictionarySize; i++) {
        pCurrent = pDictionaryTrie;
        len = strlen(dictionary[i]);
        for (j = 0; j < len; j++) {
            c = dictionary[i][j];
            if (pCurrent->children[c - 'a'] == NULL) {
                pCurrent->children[c - 'a'] = creatTrie();
            }
            pCurrent = pCurrent->children[c - 'a'];
        }
        pCurrent->isEnd = true;
    }

    //
    int idx = 0;
    char *pTmp = NULL;
#define SEPARATED (" ")
    char *pStr = strtok(sentence, SEPARATED);
    while (pStr != NULL) {
        pTmp = (char *)malloc(MAX_BUF_SIZE * sizeof(char));
        if (pTmp == NULL) {
            perror("malloc");
            break;
        }
        memset(pTmp, 0, (MAX_BUF_SIZE * sizeof(char)));

        findRoot(pStr, pDictionaryTrie, pTmp);
        idx += sprintf(pRetVal + idx, "%s ", pTmp);

        free(pTmp);
        pTmp = NULL;

        pStr = strtok(NULL, SEPARATED);
    }
    if (idx >= 1) {
        pRetVal[idx - 1] = '\0';
    }

    //
    freeTrie(pDictionaryTrie);
    pDictionaryTrie = NULL;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<string> split(string &str, char ch) {
        vector<string> retVal;

        string s(str);
        int sSize = s.size();

        int pos = 0;
        int start = 0;
        while (pos < sSize) {
            while ((pos < sSize) && (s[pos] == ch)) {
                pos++;
            }
            start = pos;
            while ((pos < sSize) && (s[pos] != ch)) {
                pos++;
            }

            if (start < sSize) {
                retVal.emplace_back(s.substr(start, pos - start));
            }
        }

        return retVal;
    }
    string replaceWords(vector<string> &dictionary, string sentence) {
        string retVal;

        unordered_set<string> dictionarySet;
        for (auto &root : dictionary) {
            dictionarySet.emplace(root);
        }

        vector<string> words = split(sentence, ' ');
        for (auto &word : words) {
            int wordSize = word.size();
            for (int i = 0; i < wordSize; i++) {
                if (dictionarySet.count(word.substr(0, 1 + i)) != 0) {
                    word = word.substr(0, 1 + i);
                    break;
                }
            }
        }

        int wordsSize = words.size();
        for (int i = 0; i < wordsSize - 1; i++) {
            retVal.append(words[i]);
            retVal.append(" ");
        }
        retVal.append(words.back());

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def shortest_root(self, word: str, dict_set: set) -> str:
        retVal = word   # There is not a corresponding root in the dictionary

        wordSize = len(word)
        for i in range(wordSize):  # Find the shortest root of the word in the dictionary
            root = word[0:i]
            if root in dict_set:
                retVal = root
                break

        return retVal

    def replaceWords(self, dictionary: List[str], sentence: str) -> str:
        retVal = None

        dict_set = set(dictionary)

        wordArray = sentence.split()
        wordArraySize = len(wordArray)

        # Replace each word in sentence with the corresponding shortest root
        for word in range(wordArraySize):
            wordArray[word] = self.shortest_root(wordArray[word], dict_set)
        retVal = " ".join(wordArray)

        return retVal
```

</details>

## [692. Top K Frequent Words](https://leetcode.com/problems/top-k-frequent-words/)

- [Official](https://leetcode.cn/problems/top-k-frequent-words/solutions/785903/qian-kge-gao-pin-dan-ci-by-leetcode-solu-3qk0/)

<details><summary>Description</summary>

```text
Given an array of strings words and an integer k, return the k most frequent strings.

Return the answer sorted by the frequency from highest to lowest.
Sort the words with the same frequency by their lexicographical order.

Example 1:
Input: words = ["i","love","leetcode","i","love","coding"], k = 2
Output: ["i","love"]
Explanation: "i" and "love" are the two most frequent words.
Note that "i" comes before "love" due to a lower alphabetical order.

Example 2:
Input: words = ["the","day","is","sunny","the","the","the","sunny","is","is"], k = 4
Output: ["the","is","sunny","day"]
Explanation: "the", "is", "sunny" and "day" are the four most frequent words,
with the number of occurrence being 4, 3, 2 and 1 respectively.

Constraints:
1 <= words.length <= 500
1 <= words[i].length <= 10
words[i] consists of lowercase English letters.
k is in the range [1, The number of unique words[i]]

Follow-up: Could you solve it in O(n log(k)) time and O(n) extra space?
```

</details>

<details><summary>C</summary>

```c
int compareString(const void* str1, const void* str2) {
    // descending order
    return strcmp(*(char**)str2, *(char**)str1);
}
int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** topKFrequent(char** words, int wordsSize, int k, int* returnSize) {
    char** pRetVal = NULL;

    *returnSize = k;
    pRetVal = (char**)malloc((*returnSize) * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        *returnSize = 0;
        return pRetVal;
    }

    // descending order; Time Complexity: O(nlogn)
    qsort(words, wordsSize, sizeof(char*), compareString);

    // 1 <= words.length <= 500
#define COUNT_IDX (1000)
    int idx = 0;
    // Space Complexity: O(n)
    int count[wordsSize];
    count[idx] = idx + COUNT_IDX;
    int i;
    // Time Complexity: O(n)
    for (i = 1; i < wordsSize; ++i) {
        if (strcmp(words[i - 1], words[i]) == 0) {
            count[idx] += COUNT_IDX;
            count[i] = i;
            continue;
        }
        count[i] = i + COUNT_IDX;
        idx = i;
    }

    // descending order; Time Complexity: O(nlogn)
    qsort(count, wordsSize, sizeof(int), compareInteger);

    // Time Complexity: O(n)
    for (i = 0; i < (*returnSize); ++i) {
        pRetVal[i] = words[count[i] % 1000];
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        vector<string> retVal;

        //
        unordered_map<string, int> hashTable;
        for (string word : words) {
            ++hashTable[word];
        }
        auto sortHash = [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second == b.second ? a.first < b.first : a.second > b.second;
        };

        //
        priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(sortHash)> priorityQueue(sortHash);
        for (auto& iterator : hashTable) {
            priorityQueue.emplace(iterator);
            int priorityQueueSize = priorityQueue.size();
            if (priorityQueueSize > k) {
                priorityQueue.pop();
            }
        }
        for (int i = k - 1; i >= 0; i--) {
            retVal.emplace_back(priorityQueue.top().first);
            priorityQueue.pop();
        }
        reverse(retVal.begin(), retVal.end());

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def topKFrequent(self, words: List[str], k: int) -> List[str]:
        retVal = []

        hashTable = Counter(words)
        tmp = sorted(hashTable, key=lambda word:(-hashTable[word], word))
        retVal = tmp[:k]

        return retVal
```

</details>

## [705. Design HashSet](https://leetcode.com/problems/design-hashset/)

- [Official](https://leetcode.cn/problems/design-hashset/solutions/652778/she-ji-ha-xi-ji-he-by-leetcode-solution-xp4t/)

<details><summary>Description</summary>

```text
Design a HashSet without using any built-in hash table libraries.

Implement MyHashSet class:
- void add(key)
    Inserts the value key into the HashSet.
- bool contains(key)
    Returns whether the value key exists in the HashSet or not.
- void remove(key)
    Removes the value key in the HashSet. If key does not exist in the HashSet, do nothing.

Example 1:
Input
["MyHashSet", "add", "add", "contains", "contains", "add", "contains", "remove", "contains"]
[[], [1], [2], [1], [3], [2], [2], [2], [2]]
Output
[null, null, null, true, false, null, true, null, false]
Explanation
MyHashSet myHashSet = new MyHashSet();
myHashSet.add(1);      // set = [1]
myHashSet.add(2);      // set = [1, 2]
myHashSet.contains(1); // return True
myHashSet.contains(3); // return False, (not found)
myHashSet.add(2);      // set = [1, 2]
myHashSet.contains(2); // return True
myHashSet.remove(2);   // set = [1]
myHashSet.contains(2); // return False, (already removed)

Constraints:
0 <= key <= 10^6
At most 10^4 calls will be made to add, remove, and contains.
```

</details>

<details><summary>C</summary>

```c
#ifndef LIST_H
#define LIST_H

struct List {
    int val;
    struct List* next;
};
void listPush(struct List* pHead, int value) {
    struct List* pNew = (struct List*)malloc(sizeof(struct List));
    if (pNew == NULL) {
        perror("malloc");
        return;
    }
    pNew->val = value;
    pNew->next = pHead->next;
    pHead->next = pNew;
}
void listDelete(struct List* pHead, int value) {
    struct List* pFree = NULL;
    struct List* iterator;
    for (iterator = pHead; iterator->next; iterator = iterator->next) {
        if (iterator->next->val == value) {
            pFree = iterator->next;
            iterator->next = pFree->next;
            free(pFree);
            pFree = NULL;
            break;
        }
    }
}
bool listContains(struct List* pHead, int value) {
    bool retVal = false;

    struct List* iterator;
    for (iterator = pHead; iterator->next; iterator = iterator->next) {
        if (iterator->next->val == value) {
            retVal = true;
            break;
        }
    }

    return retVal;
}
void listFree(struct List* pHead) {
    struct List* pFree = NULL;
    while (pHead->next) {
        pFree = pHead->next;
        pHead->next = pFree->next;
        free(pFree);
        pFree = NULL;
    }
}
#endif

#define MyHashMod (1000)
typedef struct {
    struct List* bucket;
} MyHashSet;
MyHashSet* myHashSetCreate() {
    MyHashSet* pRetVal = (MyHashSet*)malloc(sizeof(MyHashSet));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    pRetVal->bucket = (struct List*)malloc(sizeof(struct List) * MyHashMod);
    if (pRetVal->bucket == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    int i;
    for (i = 0; i < MyHashMod; i++) {
        pRetVal->bucket[i].val = 0;
        pRetVal->bucket[i].next = NULL;
    }

    return pRetVal;
}
void myHashSetAdd(MyHashSet* obj, int key) {
    int idx = key % MyHashMod;
    if (listContains(&(obj->bucket[idx]), key) == false) {
        listPush(&(obj->bucket[idx]), key);
    }
}
void myHashSetRemove(MyHashSet* obj, int key) {
    int idx = key % MyHashMod;
    listDelete(&(obj->bucket[idx]), key);
}
bool myHashSetContains(MyHashSet* obj, int key) {
    bool retVal = false;

    int idx = key % MyHashMod;
    retVal = listContains(&(obj->bucket[idx]), key);

    return retVal;
}
void myHashSetFree(MyHashSet* obj) {
    int i;
    for (i = 0; i < MyHashMod; i++) {
        listFree(&(obj->bucket[i]));
    }
    free(obj->bucket);
    obj->bucket = NULL;

    free(obj);
    obj = NULL;
}
/**
 * Your MyHashSet struct will be instantiated and called as such:
 * MyHashSet* obj = myHashSetCreate();
 * myHashSetAdd(obj, key);
 * myHashSetRemove(obj, key);
 * bool param_3 = myHashSetContains(obj, key);
 * myHashSetFree(obj);
 */
```

</details>

<details><summary>C++</summary>

```c++
class MyHashSet {
   public:
    vector<vector<int>> bucket;
    int mod;

    MyHashSet() {
        mod = 1000;
        bucket = vector<vector<int>>(mod);
    }
    void add(int key) {
        int idx = key % mod;
        if (count(bucket[idx].begin(), bucket[idx].end(), key) == 0) {
            bucket[idx].emplace_back(key);
        }
    }
    void remove(int key) {
        int idx = key % mod;
        for (auto iterator = bucket[idx].begin(); iterator != bucket[idx].end(); ++iterator) {
            if (*iterator == key) {
                bucket[idx].erase(iterator);
                break;
            }
        }
    }
    bool contains(int key) {
        bool retVal = false;

        int idx = key % mod;
        if (count(bucket[idx].begin(), bucket[idx].end(), key) != 0) {
            retVal = true;
        }

        return retVal;
    }
};
/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */
```

</details>

<details><summary>Python3</summary>

```python
class MyHashSet:
    def __init__(self):
        self.mod = 1000
        self.bucket = [[] for _ in range(self.mod)]

    def add(self, key: int) -> None:
        idx = key % self.mod
        if key not in self.bucket[idx]:
            self.bucket[idx].append(key)

    def remove(self, key: int) -> None:
        idx = key % self.mod
        if key in self.bucket[idx]:
            self.bucket[idx].remove(key)

    def contains(self, key: int) -> bool:
        retVal = False

        idx = key % self.mod
        retVal = key in self.bucket[idx]

        return retVal

# Your MyHashSet object will be instantiated and called as such:
# obj = MyHashSet()
# obj.add(key)
# obj.remove(key)
# param_3 = obj.contains(key)
```

</details>

## [706. Design HashMap](https://leetcode.com/problems/design-hashmap/)

- [Official](https://leetcode.cn/problems/design-hashmap/solutions/654139/she-ji-ha-xi-ying-she-by-leetcode-soluti-klu9/)

<details><summary>Description</summary>

```text
Design a HashMap without using any built-in hash table libraries.

Implement the MyHashMap class:
- MyHashMap()
  initializes the object with an empty map.
- void put(int key, int value)
  inserts a (key, value) pair into the HashMap. If the key already exists in the map, update the corresponding value.
- int get(int key)
  returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key.
- void remove(key)
  removes the key and its corresponding value if the map contains the mapping for the key.

Example 1:
Input
["MyHashMap", "put", "put", "get", "get", "put", "get", "remove", "get"]
[[], [1, 1], [2, 2], [1], [3], [2, 1], [2], [2], [2]]
Output
[null, null, null, 1, -1, null, 1, null, -1]
Explanation
MyHashMap myHashMap = new MyHashMap();
myHashMap.put(1, 1); // The map is now [[1,1]]
myHashMap.put(2, 2); // The map is now [[1,1], [2,2]]
myHashMap.get(1);    // return 1, The map is now [[1,1], [2,2]]
myHashMap.get(3);    // return -1 (i.e., not found), The map is now [[1,1], [2,2]]
myHashMap.put(2, 1); // The map is now [[1,1], [2,1]] (i.e., update the existing value)
myHashMap.get(2);    // return 1, The map is now [[1,1], [2,1]]
myHashMap.remove(2); // remove the mapping for 2, The map is now [[1,1]]
myHashMap.get(2);    // return -1 (i.e., not found), The map is now [[1,1]]

Constraints:
0 <= key, value <= 10^6
At most 10^4 calls will be made to put, get, and remove.
```

</details>

<details><summary>C</summary>

```c
#ifndef LIST_H
#define LIST_H

struct List {
    int key;
    int val;
    struct List* next;
};
void listPush(struct List* pHead, int key, int value) {
    struct List* pNew = (struct List*)malloc(sizeof(struct List));
    if (pNew == NULL) {
        perror("malloc");
        return;
    }
    pNew->key = key;
    pNew->val = value;
    pNew->next = pHead->next;
    pHead->next = pNew;
}
void listDelete(struct List* pHead, int key) {
    struct List* pFree = NULL;
    struct List* iterator;
    for (iterator = pHead; iterator->next; iterator = iterator->next) {
        if (iterator->next->key == key) {
            pFree = iterator->next;
            iterator->next = pFree->next;
            free(pFree);
            pFree = NULL;
            break;
        }
    }
}
struct List* listFind(struct List* pHead, int key) {
    struct List* pRetVal = NULL;

    struct List* iterator;
    for (iterator = pHead; iterator->next; iterator = iterator->next) {
        if (iterator->next->key == key) {
            pRetVal = iterator->next;
            break;
        }
    }

    return pRetVal;
}
void listFree(struct List* pHead) {
    struct List* pFree = NULL;
    while (pHead->next) {
        pFree = pHead->next;
        pHead->next = pFree->next;
        free(pFree);
        pFree = NULL;
    }
}

#endif
#define MyHashMapMod (1000)
typedef struct {
    struct List* map;
} MyHashMap;
MyHashMap* myHashMapCreate() {
    MyHashMap* pRetVal = NULL;

    pRetVal = (MyHashMap*)malloc(sizeof(MyHashMap));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    pRetVal->map = (struct List*)malloc(sizeof(struct List) * MyHashMapMod);
    if (pRetVal->map == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    int i;
    for (i = 0; i < MyHashMapMod; i++) {
        pRetVal->map[i].key = i;
        pRetVal->map[i].val = -1;
        pRetVal->map[i].next = NULL;
    }

    return pRetVal;
}
void myHashMapPut(MyHashMap* obj, int key, int value) {
    int idx = key % MyHashMapMod;
    struct List* pRetVal = listFind(&(obj->map[idx]), key);
    if (pRetVal == NULL) {
        listPush(&(obj->map[idx]), key, value);
    } else {
        pRetVal->val = value;
    }
}
int myHashMapGet(MyHashMap* obj, int key) {
    int retVal = -1;

    int idx = key % MyHashMapMod;
    struct List* pRetVal = listFind(&(obj->map[idx]), key);
    if (pRetVal != NULL) {
        retVal = pRetVal->val;
    }

    return retVal;
}
void myHashMapRemove(MyHashMap* obj, int key) {
    int idx = key % MyHashMapMod;
    listDelete(&(obj->map[idx]), key);
}
void myHashMapFree(MyHashMap* obj) {
    int i;
    for (i = 0; i < MyHashMapMod; i++) {
        listFree(&(obj->map[i]));
    }
    free(obj->map);
    obj->map = NULL;

    free(obj);
    obj = NULL;
}
/**
 * Your MyHashMap struct will be instantiated and called as such:
 * MyHashMap* obj = myHashMapCreate();
 * myHashMapPut(obj, key, value);
 * int param_2 = myHashMapGet(obj, key);
 * myHashMapRemove(obj, key);
 * myHashMapFree(obj);
 */
```

</details>

<details><summary>C++</summary>

```c++
class MyHashMap {
   public:
    vector<vector<pair<int, int>>> map;
    int mod;

    MyHashMap() {
        mod = 1000;
        map = vector<vector<pair<int, int>>>(mod);
    }
    void put(int key, int value) {
        int idx = key % mod;
        for (auto iterator = map[idx].begin(); iterator != map[idx].end(); ++iterator) {
            if ((*iterator).first == key) {
                (*iterator).second = value;
                return;
            }
        }
        map[idx].push_back(make_pair(key, value));
    }
    int get(int key) {
        int retVal = -1;

        int idx = key % mod;
        for (auto iterator = map[idx].begin(); iterator != map[idx].end(); ++iterator) {
            if ((*iterator).first == key) {
                retVal = (*iterator).second;
            }
        }

        return retVal;
    }
    void remove(int key) {
        int idx = key % mod;
        for (auto iterator = map[idx].begin(); iterator != map[idx].end(); ++iterator) {
            if ((*iterator).first == key) {
                map[idx].erase(iterator);
                break;
            }
        }
    }
};
/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */
```

</details>

<details><summary>Python3</summary>

```python
class MyHashMap:
    def __init__(self):
        # 0 <= key, value <= 10^6
        self.mod = 1000
        self.map = [[-1] * self.mod for _ in range(self.mod + 1)]

    def put(self, key: int, value: int) -> None:
        row = key // self.mod
        col = key % self.mod
        self.map[row][col] = value

    def get(self, key: int) -> int:
        retVal = -1

        row = key // self.mod
        col = key % self.mod
        retVal = self.map[row][col]

        return retVal

    def remove(self, key: int) -> None:
        row = key // self.mod
        col = key % self.mod
        self.map[row][col] = -1

# Your MyHashMap object will be instantiated and called as such:
# obj = MyHashMap()
# obj.put(key,value)
# param_2 = obj.get(key)
# obj.remove(key)
```

</details>

## [930. Binary Subarrays With Sum](https://leetcode.com/problems/binary-subarrays-with-sum/)  1591

- [Official](https://leetcode.com/problems/binary-subarrays-with-sum/editorial/)
- [Official](https://leetcode.cn/problems/binary-subarrays-with-sum/solutions/864087/he-xiang-tong-de-er-yuan-zi-shu-zu-by-le-5caf/)

<details><summary>Description</summary>

```text
Given a binary array nums and an integer goal, return the number of non-empty subarrays with a sum goal.

A subarray is a contiguous part of the array.

Example 1:
Input: nums = [1,0,1,0,1], goal = 2
Output: 4
Explanation: The 4 subarrays are bolded and underlined below:
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]

Example 2:
Input: nums = [0,0,0,0,0], goal = 0
Output: 15

Constraints:
1 <= nums.length <= 3 * 10^4
nums[i] is either 0 or 1.
0 <= goal <= nums.length
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
int numSubarraysWithSum(int *nums, int numsSize, int goal) {
    int retVal = 0;

    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;

    int key;
    int sum = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &sum, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                goto exit;
            }
            pTemp->key = sum;
            pTemp->value = 1;
            HASH_ADD_INT(pHashTable, key, pTemp);
        } else {
            pTemp->value += 1;
        }

        sum += nums[i];

        key = sum - goal;
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &key, pTemp);
        if (pTemp != NULL) {
            retVal += pTemp->value;
        }
    }

exit:
    freeAll(pHashTable);
    pHashTable = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        int retVal = 0;

        unordered_map<int, int> hashTable;
        int sum = 0;
        for (int num : nums) {
            hashTable[sum] += 1;
            sum += num;
            retVal += hashTable[sum - goal];
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def numSubarraysWithSum(self, nums: List[int], goal: int) -> int:
        retVal = 0

        hashTable = defaultdict(int)
        sum = 0
        for num in nums:
            hashTable[sum] += 1
            sum += num
            retVal += hashTable[sum - goal]

        return retVal
```

</details>
