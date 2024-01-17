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

</details>

<details><summary>C</summary>

```c
int firstMissingPositive(int* nums, int numsSize){
    int retVal = 1;

    int i;

#define MAX_RECORD      100000
    int RECORD[MAX_RECORD];
    for (i=0; i<MAX_RECORD; ++i)
    {
        RECORD[i] = INT_MAX;
    }

    int idx;
    for (i=0; i<numsSize; ++i)
    {
        if (nums[i] <= 0)
        {
            continue;
        }
        idx = (nums[i] - 1) % MAX_RECORD;
        RECORD[idx] = (RECORD[idx]<nums[i])?RECORD[idx]:nums[i];

        if (nums[i] == retVal)
        {
            ++retVal;
        }
    }

    idx = (retVal-1) % MAX_RECORD;
    while (retVal <= INT_MAX)
    {
        if ((RECORD[idx] == INT_MAX) || (RECORD[idx] != retVal))
        {
            break;
        }
        ++retVal;
        idx = (retVal-1) % MAX_RECORD;
    }

    return retVal;
}
```

</details>

## [49. Group Anagrams](https://leetcode.com/problems/group-anagrams/)

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
#define MAX_LENGTH      (100)

struct hash_struct {
    char key[MAX_LENGTH];
    int count;
    int idx;
    UT_hash_handle hh;
};
void freeAll(struct hash_struct* pFree) {
    struct hash_struct* current;
    struct hash_struct* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
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
    (*returnSize) = 0;

    int i, j, k;
    char pSortStr[MAX_LENGTH];
    struct hash_struct* map = NULL;
    struct hash_struct* temp;


    /* 1. use hash map to count strs[i] appear times to prepare malloc return arrays */
    for (i=0; i<strsSize; ++i) {
        // sort strs[i] as hash key
        memset(pSortStr, 0, sizeof(pSortStr));
        snprintf(pSortStr, sizeof(pSortStr), "%s", strs[i]);
        qsort(pSortStr, strlen(pSortStr), sizeof(char), compareChar);

        temp = NULL;
        HASH_FIND_STR(map, pSortStr, temp);

        // strs[i] exist in hash map
        if (temp != NULL) {
            temp->count++;
            continue;
        }

        // strs[i] does not exist in hash map
        temp = (struct hash_struct*)malloc(sizeof(struct hash_struct));
        if (temp == NULL) {
            perror("malloc");
            freeAll(map);
            map = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        snprintf(temp->key, MAX_LENGTH, "%s", pSortStr);
        temp->count = 1;
        HASH_ADD_STR(map, key, temp);

        // update returnSize
        (*returnSize)++;
    }


    /* 2. malloc return arrays */
    // update returnColumnSizes
    (*returnColumnSizes) = (int*)malloc((*returnSize)*sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        freeAll(map);
        map = NULL;
        (*returnSize) = 0;
        return pRetVal;
    }
    i = 0;
    for (temp=map; temp!=NULL; temp=temp->hh.next) {
        (*returnColumnSizes)[i++] = temp->count;
    }

    // temporary free hash map
    freeAll(map);
    map = NULL;

    // update return char ***
    pRetVal = (char***)malloc((*returnSize)*sizeof(char**));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        (*returnSize) = 0;
        return pRetVal;
    }
    for (i=0; i<(*returnSize); ++i) {
        pRetVal[i] = (char**)malloc(((*returnColumnSizes)[i])*sizeof(char*));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            for (j=0; j<i; ++j)
            {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            free(pRetVal);
            pRetVal = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        for (j=0; j<(*returnColumnSizes)[i]; ++j) {
            pRetVal[i][j] = (char*)malloc(MAX_LENGTH*sizeof(char));
            if (pRetVal[i][j] == NULL) {
                perror("malloc");
                for (k=0; k<j; ++k) {
                    free(pRetVal[i][k]);
                    pRetVal[i][k] = NULL;
                }
                for (k=0; k<i; ++k) {
                    free(pRetVal[k]);
                    pRetVal[k] = NULL;
                }
                free((*returnColumnSizes));
                (*returnColumnSizes) = NULL;
                free(pRetVal);
                pRetVal = NULL;
                (*returnSize) = 0;
                return pRetVal;
            }
            memset(pRetVal[i][j], 0, MAX_LENGTH);
        }
    }


    /* 3. re-use hash map to copy strs[i] to return arrays */
    int idx = 0;
    for (i=0; i<strsSize; ++i) {
        // sort strs[i] as hash key
        memset(pSortStr, 0, sizeof(pSortStr));
        snprintf(pSortStr, sizeof(pSortStr), "%s", strs[i]);
        qsort(pSortStr, strlen(pSortStr), sizeof(char), compareChar);

        temp = NULL;
        HASH_FIND_STR(map, pSortStr, temp);

        // strs[i] exist in hash map
        if (temp != NULL) {
            // copy strs[i] to return arrays
            snprintf(pRetVal[temp->idx][temp->count], MAX_LENGTH, "%s", strs[i]);

            temp->count++;
            continue;
        }

        // strs[i] does not exist in hash map
        temp = (struct hash_struct*)malloc(sizeof(struct hash_struct));
        if (temp == NULL) {
            perror("malloc");
            freeAll(map);
            map = NULL;
            for (j=0; j<(*returnSize); ++j) {
                for (k=0; k<(*returnColumnSizes)[j]; ++k) {
                    free(pRetVal[j][k]);
                    pRetVal[j][k] = NULL;
                }
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            free(pRetVal);
            pRetVal = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        snprintf(temp->key, MAX_LENGTH, "%s", pSortStr);
        temp->count = 1;
        temp->idx = idx;
        HASH_ADD_STR(map, key, temp);

        // copy strs[i] to return arrays
        snprintf(pRetVal[idx++][0], MAX_LENGTH, "%s", strs[i]);
    }

    // free hash map
    freeAll(map);
    map = NULL;

    return pRetVal;
}
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
12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1

Example 2:
Input: n = 2
Output: false

Constraints:
1 <= n <= 2^31 - 1
```

</details>

<details><summary>C</summary>

```c
#define LINK_LIST (1)
#define UTHASH (1)
#if (LINK_LIST)
struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* createNode(int value) {
    struct ListNode* pNew = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (pNew == NULL) {
        perror("malloc");
        return pNew;
    }
    pNew->val = value;
    pNew->next = NULL;

    return pNew;
}
void freeNode(struct ListNode* pHead) {
    struct ListNode* pFree = NULL;
    while (pHead != NULL) {
        pFree = pHead;
        pHead = pHead->next;
        free(pFree);
    }
}
struct ListNode* addValueToEnd(struct ListNode* pHead, int value) {
    struct ListNode* pNew = createNode(value);
    if (pNew == NULL) {
        return pHead;
    }

    if (pHead == NULL) {
        pHead = pNew;
        return pHead;
    }

    struct ListNode* pCurrent = pHead;
    while (pCurrent->next != NULL) {
        pCurrent = pCurrent->next;
    }
    pCurrent->next = pNew;

    return pHead;
}
bool searchNode(struct ListNode* pHead, int searchValue) {
    bool retVal = true;

    struct ListNode* pCurrent = pHead;
    while (pCurrent != NULL) {
        if (pCurrent->val == searchValue) {
            return retVal;
        }
        pCurrent = pCurrent->next;
    }
    retVal = false;

    return retVal;
}
#elif (UTHASH)
#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashStruct {
    int value;
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
#endif
bool isHappy(int n) {
    bool retVal = true;

#if (LINK_LIST)
    printf("LINK_LIST\n");

    struct ListNode* pHead = NULL;
#elif (UTHASH)
    printf("UTHASH\n");

    struct hashStruct* map = NULL;
    struct hashStruct* temp;
#endif

    int sum;
    int num = n;
    while (num != 1) {
#if (LINK_LIST)
        retVal = searchNode(pHead, num);
        if (retVal == true) {
            break;
        }
        pHead = addValueToEnd(pHead, num);
#elif (UTHASH)
        temp = NULL;
        HASH_FIND_INT(map, &num, temp);
        if (temp != NULL) {
            break;
        }
        temp = (struct hashStruct*)malloc(sizeof(struct hashStruct));
        if (temp == NULL) {
            perror("malloc");
            freeAll(map);
            retVal = false;
            return retVal;
        }
        temp->value = num;
        HASH_ADD_INT(map, value, temp);
#endif

        sum = 0;
        while (num > 0) {
            sum += ((num % 10) * (num % 10));
            num = (num - num % 10) / 10;
        }
        num = sum;
    }
    retVal = (num == 1) ? true : false;

#if (LINK_LIST)
    if (pHead != NULL) {
        freeNode(pHead);
        pHead = NULL;
    }
#elif (UTHASH)
    freeAll(map);
#endif

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
public:
    bool isHappy(int n) {
        bool retVal = true;

        unordered_set<int> recordSet;
        int sum;
        int num = n;
        while (num != 1) {
            if (recordSet.find(num) != recordSet.end()) {
                break;
            }
            recordSet.insert(num);

            sum = 0;
            while (num > 0) {
                sum += ((num%10) * (num%10));
                num = (num - num%10) / 10;
            }
            num = sum;
        }
        retVal = (num == 1)?true:false;

        return retVal;
    }
};
```

</details>

## [205. Isomorphic Strings](https://leetcode.com/problems/isomorphic-strings/)

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

    // t.length == s.length
#if 0
    if (strlen(s) != strlen(t))
    {
        return retVal;
    }
#endif

    // s and t consist of any valid ascii character.
#define MAX_HASHTABLE_SIZE      (128)
    int HASH_TABLE[2][MAX_HASHTABLE_SIZE] = {0};
    int idx = 1;
    while (*s) {
        HASH_TABLE[0][(unsigned char)*s] = (HASH_TABLE[0][(unsigned char)*s]==0)?idx:HASH_TABLE[0][(unsigned char)*s];
        HASH_TABLE[1][(unsigned char)*t] = (HASH_TABLE[1][(unsigned char)*t]==0)?idx:HASH_TABLE[1][(unsigned char)*t];
        if (HASH_TABLE[0][(unsigned char)*s] != HASH_TABLE[1][(unsigned char)*t]) {
            return retVal;
        }

        ++s;
        ++t;
        ++idx;
    }
    retVal = true;

    return retVal;
}
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
bool wordPattern(char* pattern, char* s) {
    bool retVal = false;

    int i, j;

    // pattern contains only lower-case English letters.
#define HASHTABLE_SIZE (26)
    char* HASH_TABLE[HASHTABLE_SIZE];
    for (i = 0; i < HASHTABLE_SIZE; ++i) {
        HASH_TABLE[i] = NULL;
    }

    // All the words in s are separated by a single space.
#define SEPARATED " "
    char* pStr = strtok(s, SEPARATED);
    while ((pStr != NULL) && (*pattern)) {
        if (HASH_TABLE[(unsigned char)(*pattern) - 'a'] == NULL) {
            HASH_TABLE[(unsigned char)(*pattern) - 'a'] = pStr;
        } else if (strcmp(HASH_TABLE[(unsigned char)(*pattern) - 'a'], pStr) != 0) {
            return retVal;
        }

        ++pattern;
        pStr = strtok(NULL, SEPARATED);
    }
    if ((pStr != NULL) || (*pattern)) {
        return retVal;
    }

    for (i = 0; i < HASHTABLE_SIZE; ++i) {
        if (HASH_TABLE[i] == NULL) {
            continue;
        }
        for (j = i + 1; j < HASHTABLE_SIZE; ++j) {
            if (HASH_TABLE[j] == NULL) {
                continue;
            }
            if (strcmp(HASH_TABLE[i], HASH_TABLE[j]) == 0) {
                return retVal;
            }
        }
    }
    retVal = true;

    return retVal;
}
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
#define HASH_TABLE (1)
#define SORTING (1)
#if (HASH_TABLE)
#elif (SORTING)
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
#endif
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = (nums1Size > nums2Size) ? nums1Size : nums2Size;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, -1, ((*returnSize) * sizeof(int)));

#if (HASH_TABLE)
    printf("HASH_TABLE\n");

#define MAX_RECORD (1001)
    int RECORD[MAX_RECORD];
    memset(RECORD, 0, sizeof(RECORD));

    int i;
    for (i = 0; i < nums1Size; ++i) {
        RECORD[nums1[i]] = 1;
    }

    (*returnSize) = 0;
    for (i = 0; i < nums2Size; ++i) {
        if (RECORD[nums2[i]] == 1) {
            pRetVal[(*returnSize)] = nums2[i];
            (*returnSize)++;
            RECORD[nums2[i]]++;
        }
    }
#elif (SORTING)
    printf("SORTING\n");

    qsort(nums1, nums1Size, sizeof(int), compareInteger);
    qsort(nums2, nums2Size, sizeof(int), compareInteger);

    (*returnSize) = 0;
    int idx1 = 0;
    int idx2 = 0;
    while ((idx1 < nums1Size) && (idx2 < nums2Size)) {
        if (nums1[idx1] == nums2[idx2]) {
            if ((*returnSize) == 0) {
                pRetVal[(*returnSize)] = nums1[idx1];
                (*returnSize)++;
            } else if (nums1[idx1] != pRetVal[(*returnSize) - 1]) {
                pRetVal[(*returnSize)] = nums1[idx1];
                (*returnSize)++;
            }
            idx1++;
            idx2++;
        } else if (nums1[idx1] > nums2[idx2]) {
            idx2++;
        } else if (nums1[idx1] < nums2[idx2]) {
            idx1++;
        }
    }
#endif

    return pRetVal;
}
```

</details>

## [350. Intersection of Two Arrays II](https://leetcode.com/problems/intersection-of-two-arrays-ii/)

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
#define HASH_TABLE (1)
#define SORTING (1)
#if (HASH_TABLE)
#elif (SORTING)
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
#endif
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = (nums1Size > nums2Size) ? nums1Size : nums2Size;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, -1, ((*returnSize) * sizeof(int)));

#if (HASH_TABLE)
    printf("HASH_TABLE\n");

#define MAX_RECORD (1001)
    int RECORD[MAX_RECORD];
    memset(RECORD, 0, sizeof(RECORD));

    int i;
    for (i = 0; i < nums1Size; ++i) {
        RECORD[nums1[i]]++;
    }

    (*returnSize) = 0;
    for (i = 0; i < nums2Size; ++i) {
        if (RECORD[nums2[i]] != 0) {
            pRetVal[(*returnSize)++] = nums2[i];
            RECORD[nums2[i]]--;
        }
    }
#elif (SORTING)
    printf("SORTING\n");

    qsort(nums1, nums1Size, sizeof(int), compareInteger);
    qsort(nums2, nums2Size, sizeof(int), compareInteger);

    (*returnSize) = 0;
    int idx1 = 0;
    int idx2 = 0;
    while ((idx1 < nums1Size) && (idx2 < nums2Size)) {
        if (nums1[idx1] == nums2[idx2]) {
            pRetVal[(*returnSize)++] = nums1[idx1];
            idx1++;
            idx2++;
        } else if (nums1[idx1] > nums2[idx2]) {
            idx2++;
        } else if (nums1[idx1] < nums2[idx2]) {
            idx1++;
        }
    }
#endif

    return pRetVal;
}
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
bool canConstruct(char * ransomNote, char * magazine){
    bool retVal = false;

    int lenRansomNote = strlen(ransomNote);
    int lenMagazine = strlen(magazine);
    if (lenRansomNote > lenMagazine)
    {
        return retVal;
    }
    int RECORD[26] = {0};

    int i;
    for (i=0; i<lenRansomNote; ++i)
    {
        --RECORD[ransomNote[i]-'a'];
        ++RECORD[magazine[i]-'a'];
    }
    for (i=lenRansomNote; i<lenMagazine; ++i)
    {
        ++RECORD[magazine[i]-'a'];
    }

    for (i=0; i<26; ++i)
    {
        if (RECORD[i] < 0)
        {
            return retVal;
        }
    }
    retVal = true;

    return retVal;
}
```

</details>

## [387. First Unique Character in a String](https://leetcode.com/problems/first-unique-character-in-a-string/)

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
int firstUniqChar(char * s){
#if 1
    int retVal = -1;

// only lowercase English letters
#define MAX_SIZE    26
    int lettersCount[MAX_SIZE] = {0};
    int idx;

    int len = strlen(s);
    int i;
    for (i=0; i<len; ++i)
    {
        idx = *(s+i) - 'a';
        // count the number each appear letters of string s
        ++lettersCount[idx];
    }

    for (i=0; i<len; ++i)
    {
        idx = *(s+i) - 'a';
        // traverse string s to check which letter first appear only once
        if (lettersCount[idx] == 1)
        {
            retVal = i;
            break;
        }
    }
#else
    int retVal = INT_MAX;

// only lowercase English letters
#define MAX_SIZE    26
    int HASHTABLE[MAX_SIZE] = {0};
    int idx;

    int len = strlen(s);
    int i;
    for (i=0; i<len; ++i)
    {
        idx = *(s+i) - 'a';
        if (HASHTABLE[idx] == -1)
        {
            // has been repeated
            continue;
        }
        else if (HASHTABLE[idx] != 0)
        {
            // repeating character
            HASHTABLE[idx] = -1;
        }
        else if (HASHTABLE[idx] == 0)
        {
            // first appear
            HASHTABLE[idx] = i + 1;
        }
    }

    for (i=0; i<MAX_SIZE; ++i)
    {
        if ((HASHTABLE[i] == -1) || (HASHTABLE[i] == 0))
        {
            continue;
        }
        // update which letters appear first
        retVal = (retVal<HASHTABLE[i])?retVal:HASHTABLE[i];
    }
    retVal = (retVal==INT_MAX)?(-1):(retVal-1);
#endif

    return retVal;
}
```

</details>

## [409. Longest Palindrome](https://leetcode.com/problems/longest-palindrome/)

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

#define ASCII_SIZE  (128)
    int asciiTable[ASCII_SIZE] = {0};

    while (*s) {
        ++asciiTable[(unsigned char)(*s)];
        if (asciiTable[(unsigned char)(*s)] == 2) {
            retVal += 2;
            asciiTable[(unsigned char)(*s)] = 0;
        }
        ++s;
    }

    int i;
    for (i=0; i<ASCII_SIZE; ++i) {
        if (asciiTable[i] == 1) {
            ++retVal;
            break;
        }
    }

    return retVal;
}
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
    int i, j;

    // s consists of uppercase and lowercase English letters and digits.
#define HASHTABLE_SIZE (128)
    // malloc hash table
    int **pHashTable = (int **)malloc(HASHTABLE_SIZE * sizeof(int *));
    if (pHashTable == NULL) {
        perror("malloc");
        return s;
    }
    for (i = 0; i < HASHTABLE_SIZE; ++i) {
        pHashTable[i] = (int *)malloc(2 * sizeof(int));
        if (pHashTable[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pHashTable[j]);
                pHashTable[j] = NULL;
            }
            free(pHashTable);
            pHashTable = NULL;
            return s;
        }
        pHashTable[i][0] = i;
        pHashTable[i][1] = 0;
    }

    // use hash table to record the frequency of the characters
    int len = strlen(s);
    for (i = 0; i < len; ++i) {
        ++pHashTable[(int)s[i]][1];
    }

    // sort the number of character appearance
    qsort(pHashTable, HASHTABLE_SIZE, sizeof(pHashTable[0]), compareIntArray);

    // update return string based on the frequency of the characters
    int count = 0;
    for (i = 0; i < HASHTABLE_SIZE; ++i) {
        if (pHashTable[i][1] == 0) {
            break;
        }

        for (j = 0; j < pHashTable[i][1]; ++j) {
            s[count] = pHashTable[i][0];
            ++count;
        }
    }

    // free hash table
    for (i = 0; i < HASHTABLE_SIZE; ++i) {
        free(pHashTable[i]);
        pHashTable[i] = NULL;
    }
    free(pHashTable);
    pHashTable = NULL;

    return s;
}
```

</details>

## [523. Continuous Subarray Sum](https://leetcode.com/problems/continuous-subarray-sum/)

- [Official](https://leetcode.com/problems/continuous-subarray-sum/solutions/2523150/continuous-subarray-sum/)
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
// https://troydhanson.github.io/uthash/
#define UTHASH      (1)

#if (UTHASH)
struct hashTable{
    int key;
    int value;
    UT_hash_handle hh;
};

void freeAll(struct hashTable* pFree)
{
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp)
    {
        HASH_DEL(pFree, current);
        free(current);
    }
}
#else
#define TIME_LIMIT_EXCEEDED     (0)
#endif

bool checkSubarraySum(int* nums, int numsSize, int k)
{
    bool retVal = false;

#if (UTHASH)
    struct hashTable* map = NULL;

    struct hashTable* first;
    first = (struct hashTable*)malloc(sizeof(struct hashTable));
    if (first == NULL)
    {
        perror("malloc");
        freeAll(map);
        return retVal;
    }
    first->key = nums[0] % k;
    first->value = 0;
    HASH_ADD_INT(map, key, first);

    struct hashTable* temp;
    int i;
    for(i=1; i<numsSize; ++i)
    {
        nums[i] = (nums[i] + nums[i-1]) % k;
        if (nums[i] == 0)
        {
            retVal = true;
            break;
        }

        HASH_FIND_INT( map, &nums[i], temp);
        if (temp == NULL)
        {
            temp = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (temp == NULL)
            {
                perror("malloc");
                break;
            }
            temp->key = nums[i];
            temp->value = i;
            HASH_ADD_INT(map, key, temp);
        }
        else if ((i - temp->value) > 1)
        {
            retVal = true;
            break;
        }
    }

    freeAll(map);
#else
    if (numsSize == 1)  // nums has a continuous subarray of size at least two
    {
        return retVal;
    }
    else if (k == 1)    // multiple of 1
    {
        retVal = true;
        return retVal;
    }

    // use hash table to record sum of nums status
    bool* pHashTable = (bool*)malloc(k * sizeof(bool));
    if (pHashTable == NULL)
    {
        perror("malloc");
        return retVal;
    }
    memset(pHashTable, 0, k*sizeof(bool));

    int sum = 0;
    int i;
    for (i=0; i<numsSize; ++i)
    {
        // multiple of k in above HashTable is like stand still(0 is always a multiple of k)
        if (nums[i] % k == 0)
        {
            // at least two
            if ((i<(numsSize-1)) && ((nums[i+1]%k)==0))
            {
                retVal = true;
                break;
            }
            continue;
        }

        sum += nums[i];
        if ((sum%k) == 0)
        {
            retVal = true;
            break;
        }
        else if (pHashTable[sum%k] == true)
        {
            retVal = true;
            break;
        }
        pHashTable[sum % k] = true;
    }

#if (TIME_LIMIT_EXCEEDED)
    free(pHashTable);
    pHashTable = NULL;
#endif

#endif

    return retVal;
}
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
int* findErrorNums(int* nums, int numsSize, int* returnSize){
    *returnSize = 2;
    int* pRetVal = (int*)malloc((*returnSize)*sizeof(int));
    if (pRetVal == NULL)
    {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (*returnSize)*sizeof(int));

    bool* pRecord = (bool*)malloc(numsSize*sizeof(bool));
    if (pRecord == NULL)
    {
        perror("malloc");
        return pRetVal;
    }
    memset(pRecord, 0, numsSize*sizeof(bool));

    int i;
    for (i=0; i<numsSize; ++i)
    {
        if (pRecord[nums[i]-1] == true)
        {
            pRetVal[0] = nums[i];
        }
        pRecord[nums[i]-1] = true;
    }

    for (i=0; i<numsSize; ++i)
    {
        if (pRecord[i] == false)
        {
            pRetVal[1] = i + 1;
            break;
        }
    }

    free(pRecord);

    return pRetVal;
}
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

## [1010. Pairs of Songs With Total Durations Divisible by 60](https://leetcode.com/problems/pairs-of-songs-with-total-durations-divisible-by-60/)  1377

- [Official](https://leetcode.cn/problems/pairs-of-songs-with-total-durations-divisible-by-60/solutions/2258328/zong-chi-xu-shi-jian-ke-bei-60-zheng-chu-42cu/)

<details><summary>Description</summary>

```text
You are given a list of songs where the ith song has a duration of time[i] seconds.

Return the number of pairs of songs for which their total duration in seconds is divisible by 60.
Formally, we want the number of indices i, j such that i < j with (time[i] + time[j]) % 60 == 0.

Example 1:
Input: time = [30,20,150,100,40]
Output: 3
Explanation: Three pairs have a total duration divisible by 60:
(time[0] = 30, time[2] = 150): total duration 180
(time[1] = 20, time[3] = 100): total duration 120
(time[1] = 20, time[4] = 40): total duration 60

Example 2:
Input: time = [60,60,60]
Output: 3
Explanation: All three pairs have a total duration of 120, which is divisible by 60.

Constraints:
1 <= time.length <= 6 * 10^4
1 <= time[i] <= 500
```

<details><summary>Hint</summary>

```text
1. We only need to consider each song length modulo 60.
2. We can count the number of songs with (length % 60) equal to r, and store that in an array of size 60.
```

</details>

</details>

<details><summary>C</summary>

```c
int numPairsDivisibleBy60(int* time, int timeSize) {
    int retVal = 0;

#define DIVISIBLE (60)
    int hashTable[DIVISIBLE];
    memset(hashTable, 0, sizeof(hashTable));
    int value;
    int i;
    for (i = 0; i < timeSize; ++i) {
        value = time[i] % DIVISIBLE;
        if (hashTable[value] != 0) {
            retVal += hashTable[value];
        }

        value = (60 - value) % 60;
        hashTable[value] += 1;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int numPairsDivisibleBy60(vector<int>& time) {
        int retVal = 0;

        unordered_map<int, int> hashTable;
        for (auto value : time) {
            value %= 60;
            auto iterator = hashTable.find(value);
            if (iterator != hashTable.end()) {
                retVal += hashTable[value];
            }

            value = (60 - value) % 60;
            hashTable[value] += 1;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def numPairsDivisibleBy60(self, time: List[int]) -> int:
        retVal = 0

        hashTable = defaultdict(int)
        for value in time:
            value %= 60
            if value in hashTable:
                retVal += hashTable[value]

            value = (60 - value) % 60
            hashTable[value] += 1

        return retVal
```

</details>

## [1207. Unique Number of Occurrences](https://leetcode.com/problems/unique-number-of-occurrences/)  1195

- [Official](https://leetcode.cn/problems/unique-number-of-occurrences/solutions/463180/du-yi-wu-er-de-chu-xian-ci-shu-by-leetcode-solutio/)

<details><summary>Description</summary>

```text
Given an array of integers arr,
return true if the number of occurrences of each value in the array is unique, or false otherwise.

Example 1:
Input: arr = [1,2,2,1,1,3]
Output: true
Explanation: The value 1 has 3 occurrences, 2 has 2 and 3 has 1. No two values have the same number of occurrences.

Example 2:
Input: arr = [1,2]
Output: false

Example 3:
Input: arr = [-3,0,1,-3,1,1,1,-3,10,0]
Output: true

Constraints:
1 <= arr.length <= 1000
-1000 <= arr[i] <= 1000
```

<details><summary>Hint</summary>

```text
1. Find the number of occurrences of each element in the array using a hash map.
2. Iterate through the hash map and check if there is a repeated value.
```

</details>

</details>

<details><summary>C</summary>

```c
bool uniqueOccurrences(int* arr, int arrSize) {
    bool retVal = false;

    int i;

// 1 <= arr.length <= 1000, -1000 <= arr[i] <= 1000
#define MAX_RANGE (1000)
#define MAX_SIZE (MAX_RANGE + 1 + MAX_RANGE)

    int occurrences[MAX_SIZE];
    memset(occurrences, 0, sizeof(occurrences));
    for (i = 0; i < arrSize; ++i) {
        // f(x) = 1000 + x, -1000 <= x <= 1000, 0 <= f(x) <= 2000.
        occurrences[MAX_RANGE + arr[i]] += 1;
    }

    int times[MAX_SIZE];
    memset(times, 0, sizeof(times));
    int index;
    for (i = 0; i < MAX_SIZE; ++i) {
        index = occurrences[i];
        if (index == 0) {
            continue;
        }

        if (times[index] != 0) {
            return retVal;
        }
        times[index] += 1;
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
    bool uniqueOccurrences(vector<int>& arr) {
        bool retVal = false;

        unordered_map<int, int> occurrences;
        for (auto iterator : arr) {
            occurrences[iterator]++;
        }

        unordered_set<int> times;
        for (auto [key, value] : occurrences) {
            times.insert(value);
        }

        if (times.size() == occurrences.size()) {
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
    def uniqueOccurrences(self, arr: List[int]) -> bool:
        retVal = True

        # occurrences = Counter(arr)
        # if len(occurrences.values()) != len(set(occurrences.values())):
        #     retVal = False
        occurrences = Counter(arr).most_common()
        previous = 0
        for _, value in occurrences:
            if previous != value:
                previous = value
            else:
                retVal = False
                break

        return retVal
```

</details>

## [1282. Group the People Given the Group Size They Belong To](https://leetcode.com/problems/group-the-people-given-the-group-size-they-belong-to/)  1267

- [Official](https://leetcode.com/problems/group-the-people-given-the-group-size-they-belong-to/editorial/)
- [Official](https://leetcode.cn/problems/group-the-people-given-the-group-size-they-belong-to/solutions/101355/yong-hu-fen-zu-by-leetcode-solution/)

<details><summary>Description</summary>

```text
There are n people that are split into some unknown number of groups.
Each person is labeled with a unique ID from 0 to n - 1.

You are given an integer array groupSizes, where groupSizes[i] is the size of the group that person i is in.
For example, if groupSizes[1] = 3, then person 1 must be in a group of size 3.

Return a list of groups such that each person i is in a group of size groupSizes[i].

Each person should appear in exactly one group, and every person must be in a group.
If there are multiple answers, return any of them.
It is guaranteed that there will be at least one valid solution for the given input.

Example 1:
Input: groupSizes = [3,3,3,3,3,1,3]
Output: [[5],[0,1,2],[3,4,6]]
Explanation:
The first group is [5]. The size is 1, and groupSizes[5] = 1.
The second group is [0,1,2]. The size is 3, and groupSizes[0] = groupSizes[1] = groupSizes[2] = 3.
The third group is [3,4,6]. The size is 3, and groupSizes[3] = groupSizes[4] = groupSizes[6] = 3.
Other possible solutions are [[2,1,6],[5],[0,4,3]] and [[5],[0,6,2],[4,3,1]].

Example 2:
Input: groupSizes = [2,1,3,3,3,2]
Output: [[1],[0,5],[2,3,4]]

Constraints:
groupSizes.length == n
1 <= n <= 500
1 <= groupSizes[i] <= n
```

<details><summary>Hint</summary>

```text
1. Put people's IDs with same groupSize into buckets, then split each bucket into groups.
2. Greedy fill until you need a new group.
```

</details>

</details>

<details><summary>C</summary>

```c
struct hashTable {
    int key;
    int* value;
    int valueSize;
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d; ", pFree->key, pFree->valueSize);
        // for (int i = 0; i < pFree->valueSize; ++i) {
        //     printf("%d ", pFree->value[i]);
        // }
        // printf("\n");

        free(pFree->value);
        pFree->value = NULL;
        HASH_DEL(pFree, current);
        free(current);
    }
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** groupThePeople(int* groupSizes, int groupSizesSize, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;

    int i, j;

    //
    struct hashTable* pHashTable = NULL;
    struct hashTable* pTemp;
    int value;
    for (i = 0; i < groupSizesSize; ++i) {
        value = groupSizes[i];

        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &value, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                return pRetVal;
            }
            pTemp->key = value;
            pTemp->value = (int*)malloc(groupSizesSize * sizeof(int));
            memset(pTemp->value, 0, (groupSizesSize * sizeof(int)));
            pTemp->value[0] = i;
            pTemp->valueSize = 1;

            HASH_ADD_INT(pHashTable, key, pTemp);
        } else {
            pTemp->value[pTemp->valueSize] = i;
            pTemp->valueSize += 1;
        }
    }

    //
    (*returnColumnSizes) = (int*)malloc(groupSizesSize * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        freeAll(pHashTable);
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, (groupSizesSize * sizeof(int)));
    pRetVal = (int**)malloc(groupSizesSize * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        freeAll(pHashTable);
        return pRetVal;
    }

    //
    int groupSize;
    struct hashTable* pCurrent;
    HASH_ITER(hh, pHashTable, pCurrent, pTemp) {
        groupSize = pCurrent->valueSize / pCurrent->key;
        for (i = 0; i < groupSize; ++i) {
            pRetVal[(*returnSize)] = (int*)malloc(pCurrent->key * sizeof(int));
            if (pRetVal[(*returnSize)] == NULL) {
                perror("malloc");
                for (j = 0; j < (*returnSize); ++j) {
                    free(pRetVal[j]);
                    pRetVal[j] = NULL;
                }
                free((*returnColumnSizes));
                (*returnColumnSizes) = NULL;
                freeAll(pHashTable);
                (*returnSize) = 0;
                return pRetVal;
            }
            memset(pRetVal[(*returnSize)], 0, (pCurrent->key * sizeof(int)));
            for (j = 0; j < pCurrent->key; ++j) {
                pRetVal[(*returnSize)][j] = pCurrent->value[j + (pCurrent->key * i)];
            }
            (*returnColumnSizes)[(*returnSize)] = pCurrent->key;
            (*returnSize)++;
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
    vector<vector<int>> groupThePeople(vector<int>& groupSizes) {
        vector<vector<int>> retVal;

        map<int, vector<int>> hashTable;

        int groupSizesSize = groupSizes.size();
        for (int i = 0; i < groupSizesSize; ++i) {
            hashTable[groupSizes[i]].emplace_back(i);
        }

        for (auto [key, value] : hashTable) {
            int groupSize = value.size() / key;
            for (int i = 0; i < groupSize; ++i) {
                vector<int> group(value.begin() + key * i, value.begin() + key * (i + 1));
                retVal.emplace_back(group);
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
    def groupThePeople(self, groupSizes: List[int]) -> List[List[int]]:
        retVal = []

        hashTable = defaultdict(list)

        groupSizesSize = len(groupSizes)
        for i in range(groupSizesSize):
            hashTable[groupSizes[i]].append(i)
        hashTable = sorted(hashTable.items())

        for key, value in hashTable:
            valueSize = len(value)
            for i in range(valueSize//key):
                retVal.append(value[key*i:key*(i+1)])

        return retVal
```

</details>

## [1346. Check If N and Its Double Exist](https://leetcode.com/problems/check-if-n-and-its-double-exist/)  1225

<details><summary>Description</summary>

```text
Given an array arr of integers, check if there exist two indices i and j such that :
- i != j
- 0 <= i, j < arr.length
- arr[i] == 2 * arr[j]

Example 1:
Input: arr = [10,2,5,3]
Output: true
Explanation: For i = 0 and j = 2, arr[i] == 10 == 2 * 5 == 2 * arr[j]

Example 2:
Input: arr = [3,1,7,11]
Output: false
Explanation: There is no i and j that satisfy the conditions.

Constraints:
2 <= arr.length <= 500
-10^3 <= arr[i] <= 10^3
```

</details>

<details><summary>C</summary>

```c
bool checkIfExist(int* arr, int arrSize) {
    bool retVal = false;

    /* -10^3 <= arr[i] <= 10^3
     *          arr[i]:  -1000 ...   0  ... 1000
     *  HashTable[idx]: 0~1999 ... 2000 ... 2001~4000
     */
#define HASHTABLE_IDX_SHIFT (2000)
#define HASHTABLE_MAX_SIZE (HASHTABLE_IDX_SHIFT + 1 + HASHTABLE_IDX_SHIFT)
    int HashTable[HASHTABLE_MAX_SIZE];
    memset(HashTable, 0, sizeof(HashTable));

    int i;
    for (i = 0; i < arrSize; ++i) {
        if (HashTable[arr[i] * 2 + HASHTABLE_IDX_SHIFT] != 0) {
            retVal = true;
            break;
        }

        if ((arr[i] % 2 == 0) && (HashTable[arr[i] / 2 + HASHTABLE_IDX_SHIFT] != 0)) {
            retVal = true;
            break;
        }

        ++HashTable[arr[i] + HASHTABLE_IDX_SHIFT];
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    bool checkIfExist(vector<int>& arr) {
        bool retVal = false;

        unordered_map<int, int> hashTable;
        for (auto i : arr) {
            if (hashTable.count(i * 2) != 0) {
                retVal = true;
                break;
            }

            if ((i % 2 == 0) && (hashTable.count(i / 2) != 0)) {
                retVal = true;
                break;
            }

            ++hashTable[i];
        }

        return retVal;
    }
};
```

</details>

## [1347. Minimum Number of Steps to Make Two Strings Anagram](https://leetcode.com/problems/minimum-number-of-steps-to-make-two-strings-anagram/)  1330

- [Official](https://leetcode.com/problems/minimum-number-of-steps-to-make-two-strings-anagram/editorial/)

<details><summary>Description</summary>

```text
You are given two strings of the same length s and t.
In one step you can choose any character of t and replace it with another character.

Return the minimum number of steps to make t an anagram of s.

An Anagram of a string is a string that contains the same characters with a different (or the same) ordering.

Example 1:
Input: s = "bab", t = "aba"
Output: 1
Explanation: Replace the first 'a' in t with b, t = "bba" which is anagram of s.

Example 2:
Input: s = "leetcode", t = "practice"
Output: 5
Explanation: Replace 'p', 'r', 'a', 'i' and 'c' from t with proper characters to make t anagram of s.

Example 3:
Input: s = "anagram", t = "mangaar"
Output: 0
Explanation: "anagram" and "mangaar" are anagrams.

Constraints:
1 <= s.length <= 5 * 10^4
s.length == t.length
s and t consist of lowercase English letters only.
```

<details><summary>Hint</summary>

```text
1. Count the frequency of characters of each string.
2. Loop over all characters if the frequency of a character in t is less than the frequency of the same character in s
   then add the difference between the frequencies to the answer.
```

</details>

</details>

<details><summary>C</summary>

```c
int minSteps(char* s, char* t) {
    int retVal = 0;

    int sSize = strlen(s);  // s.length == t.length
    int i;

#define MAX_HASHTABLE_SIZE (26)  // s and t consist of lowercase English letters only.
    int hashTable[MAX_HASHTABLE_SIZE];
    memset(hashTable, 0, sizeof(hashTable));
    for (i = 0; i < sSize; ++i) {
        hashTable[s[i] - 'a']++;
        hashTable[t[i] - 'a']--;
    }

    for (i = 0; i < MAX_HASHTABLE_SIZE; ++i) {
        if (hashTable[i] > 0) {
            retVal += hashTable[i];
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
    int minSteps(string s, string t) {
        int retVal = 0;

        int sSize = s.size();  // s and t consist of lowercase English letters only.

        unordered_map<char, int> hashTable;
        for (int i = 0; i < sSize; ++i) {
            ++hashTable[s[i]];
            --hashTable[t[i]];
        }

        for (auto [key, value] : hashTable) {
            if (value > 0) {
                retVal += value;
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
    def minSteps(self, s: str, t: str) -> int:
        retVal = 0

        hashTable = defaultdict(int)
        for cS, cT in zip(s, t):
            hashTable[cS] += 1
            hashTable[cT] -= 1

        for key in hashTable:
            if hashTable[key] > 0:
                retVal += hashTable[key]

        return retVal
```

</details>

## [1394. Find Lucky Integer in an Array](https://leetcode.com/problems/find-lucky-integer-in-an-array)  1118

- [Official](https://leetcode.cn/problems/find-lucky-integer-in-an-array/solutions/186438/zhao-chu-shu-zu-zhong-de-xing-yun-shu-by-leetcode-/)

<details><summary>Description</summary>

```text
Given an array of integers arr, a lucky integer is an integer that has a frequency in the array equal to its value.

Return the largest lucky integer in the array. If there is no lucky integer return -1.

Example 1:
Input: arr = [2,2,3,4]
Output: 2
Explanation: The only lucky number in the array is 2 because frequency[2] == 2.

Example 2:
Input: arr = [1,2,2,3,3,3]
Output: 3
Explanation: 1, 2 and 3 are all lucky numbers, return the largest of them.

Example 3:
Input: arr = [2,2,2,3,3]
Output: -1
Explanation: There are no lucky numbers in the array.

Constraints:
1 <= arr.length <= 500
1 <= arr[i] <= 500
```

</details>

<details><summary>C</summary>

```c
int findLucky(int* arr, int arrSize) {
    int retVal = -1;

#define MAX_HASH_SIZE (500 + 1)
    int HashTable[MAX_HASH_SIZE];
    memset(HashTable, 0, sizeof(HashTable));

    int i;
    for (i = 0; i < arrSize; ++i) {
        ++HashTable[arr[i]];
    }

    for (i = (MAX_HASH_SIZE - 1); i > 0; --i) {
        if (i == HashTable[i]) {
            retVal = i;
            break;
        }
    }

    return retVal;
}
```

</details>

## [1396. Design Underground System](https://leetcode.com/problems/design-underground-system/)  1464

- [Official](https://leetcode.cn/problems/design-underground-system/solutions/178324/she-ji-di-tie-xi-tong-by-leetcode-solution/)

<details><summary>Description</summary>

```text
An underground railway system is keeping track of customer travel times between different stations.
They are using this data to calculate the average time it takes to travel from one station to another.

Implement the UndergroundSystem class:
void checkIn(int id, string stationName, int t)
- A customer with a card ID equal to id, checks in at the station stationName at time t.
- A customer can only be checked into one place at a time.
void checkOut(int id, string stationName, int t)
- A customer with a card ID equal to id, checks out from the station stationName at time t.
double getAverageTime(string startStation, string endStation)
- Returns the average time it takes to travel from startStation to endStation.
- The average time is computed from all the previous traveling times
  from startStation to endStation that happened directly,
  meaning a check in at startStation followed by a check out from endStation.
- The time it takes to travel from startStation to endStation may be different
  from the time it takes to travel from endStation to startStation.
- There will be at least one customer that has traveled from startStation to endStation before getAverageTime is called.

You may assume all calls to the checkIn and checkOut methods are consistent.
If a customer checks in at time t1 then checks out at time t2, then t1 < t2. All events happen in chronological order.

Example 1:
Input
["UndergroundSystem","checkIn","checkIn","checkIn","checkOut",
"checkOut","checkOut","getAverageTime","getAverageTime","checkIn",
"getAverageTime","checkOut","getAverageTime"]
[[],[45,"Leyton",3],[32,"Paradise",8],[27,"Leyton",10],[45,"Waterloo",15],
[27,"Waterloo",20],[32,"Cambridge",22],["Paradise","Cambridge"],["Leyton","Waterloo"],[10,"Leyton",24],
["Leyton","Waterloo"],[10,"Waterloo",38],["Leyton","Waterloo"]]
Output
[null,null,null,null,null,null,null,14.00000,11.00000,null,11.00000,null,12.00000]
Explanation
UndergroundSystem undergroundSystem = new UndergroundSystem();
undergroundSystem.checkIn(45, "Leyton", 3);
undergroundSystem.checkIn(32, "Paradise", 8);
undergroundSystem.checkIn(27, "Leyton", 10);
undergroundSystem.checkOut(45, "Waterloo", 15);  // Customer 45 "Leyton" -> "Waterloo" in 15-3 = 12
undergroundSystem.checkOut(27, "Waterloo", 20);  // Customer 27 "Leyton" -> "Waterloo" in 20-10 = 10
undergroundSystem.checkOut(32, "Cambridge", 22); // Customer 32 "Paradise" -> "Cambridge" in 22-8 = 14
undergroundSystem.getAverageTime("Paradise", "Cambridge");
// return 14.00000. One trip "Paradise" -> "Cambridge", (14) / 1 = 14
undergroundSystem.getAverageTime("Leyton", "Waterloo");
// return 11.00000. Two trips "Leyton" -> "Waterloo", (10 + 12) / 2 = 11
undergroundSystem.checkIn(10, "Leyton", 24);
undergroundSystem.getAverageTime("Leyton", "Waterloo");    // return 11.00000
undergroundSystem.checkOut(10, "Waterloo", 38);  // Customer 10 "Leyton" -> "Waterloo" in 38-24 = 14
undergroundSystem.getAverageTime("Leyton", "Waterloo");
// return 12.00000. Three trips "Leyton" -> "Waterloo", (10 + 12 + 14) / 3 = 12

Example 2:
Input
["UndergroundSystem","checkIn","checkOut","getAverageTime","checkIn",
"checkOut","getAverageTime","checkIn","checkOut","getAverageTime"]
[[],[10,"Leyton",3],[10,"Paradise",8],["Leyton","Paradise"],[5,"Leyton",10],
[5,"Paradise",16],["Leyton","Paradise"],[2,"Leyton",21],[2,"Paradise",30],["Leyton","Paradise"]]
Output
[null,null,null,5.00000,null,null,5.50000,null,null,6.66667]
Explanation
UndergroundSystem undergroundSystem = new UndergroundSystem();
undergroundSystem.checkIn(10, "Leyton", 3);
undergroundSystem.checkOut(10, "Paradise", 8); // Customer 10 "Leyton" -> "Paradise" in 8-3 = 5
undergroundSystem.getAverageTime("Leyton", "Paradise"); // return 5.00000, (5) / 1 = 5
undergroundSystem.checkIn(5, "Leyton", 10);
undergroundSystem.checkOut(5, "Paradise", 16); // Customer 5 "Leyton" -> "Paradise" in 16-10 = 6
undergroundSystem.getAverageTime("Leyton", "Paradise"); // return 5.50000, (5 + 6) / 2 = 5.5
undergroundSystem.checkIn(2, "Leyton", 21);
undergroundSystem.checkOut(2, "Paradise", 30); // Customer 2 "Leyton" -> "Paradise" in 30-21 = 9
undergroundSystem.getAverageTime("Leyton", "Paradise"); // return 6.66667, (5 + 6 + 9) / 3 = 6.66667

Constraints:
1 <= id, t <= 10^6
1 <= stationName.length, startStation.length, endStation.length <= 10
All strings consist of uppercase and lowercase English letters and digits.
There will be at most 2 * 10^4 calls in total to checkIn, checkOut, and getAverageTime.
Answers within 10-5 of the actual value will be accepted.
```

</details>

<details><summary>C</summary>

```c
// https://leetcode.cn/problems/design-underground-system/solutions/1041714/cyu-yan-liang-ge-hashbiao-by-suckerfish-zl9lj/
#define STATION_LEN (12)  // 1 <= stationName.length, startStation.length, endStation.length <= 10
typedef struct {
    char station[STATION_LEN + STATION_LEN];
    int cnt;
    double averageTime;
    UT_hash_handle hh;
} Hash;
Hash* g_res = NULL;
typedef struct {
    int id;
    int checkInTime;
    char checkInStation[STATION_LEN];
    UT_hash_handle hh;
} UndergroundSystem;
UndergroundSystem* g_checkIn = NULL;
UndergroundSystem* undergroundSystemCreate() {
    UndergroundSystem* pRetVal = NULL;

    g_checkIn = NULL;
    g_res = NULL;

    return pRetVal;
}
void undergroundSystemCheckIn(UndergroundSystem* obj, int id, char* stationName, int t) {
    UndergroundSystem* temp = (UndergroundSystem*)calloc(1, sizeof(UndergroundSystem));
    temp->id = id;
    temp->checkInTime = t;
    strcpy(temp->checkInStation, stationName);

    HASH_ADD_INT(g_checkIn, id, temp);
}
void undergroundSystemCheckOut(UndergroundSystem* obj, int id, char* stationName, int t) {
    Hash* data = NULL;
    char str[STATION_LEN + STATION_LEN] = {0};

    UndergroundSystem* temp = NULL;
    HASH_FIND_INT(g_checkIn, &id, temp);
    if (temp != NULL) {
        strcpy(str, temp->checkInStation);
        strcat(str, "-");
        strcat(str, stationName);
        HASH_FIND_STR(g_res, str, data);
        if (data != NULL) {
            data->averageTime = ((data->averageTime * data->cnt) + (t - temp->checkInTime)) / (data->cnt + 1.0f);
            data->cnt++;
        } else {
            data = (Hash*)calloc(1, sizeof(Hash));
            strcpy(data->station, str);
            data->cnt = 1;
            data->averageTime = t - temp->checkInTime;
            HASH_ADD_STR(g_res, station, data);
        }
        HASH_DEL(g_checkIn, temp);
        free(temp);
    }
}
double undergroundSystemGetAverageTime(UndergroundSystem* obj, char* startStation, char* endStation) {
    double retVal = 0;

    char str[STATION_LEN + STATION_LEN] = {0};
    strcpy(str, startStation);
    strcat(str, "-");
    strcat(str, endStation);

    Hash* temp = NULL;
    HASH_FIND_STR(g_res, str, temp);
    if (temp != NULL) {
        retVal = temp->averageTime;
    }

    return retVal;
}
void undergroundSystemFree(UndergroundSystem* obj) {
    UndergroundSystem* cur = NULL;
    UndergroundSystem* tar = NULL;
    HASH_ITER(hh, g_checkIn, cur, tar) {
        if (cur) {
            HASH_DEL(g_checkIn, cur);
            free(cur);
        }
    }

    Hash* cur1 = NULL;
    Hash* tar1 = NULL;
    HASH_ITER(hh, g_res, cur1, tar1) {
        if (cur1) {
            HASH_DEL(g_res, cur1);
            free(cur1);
        }
    }
}
/**
 * Your UndergroundSystem struct will be instantiated and called as such:
 * UndergroundSystem* obj = undergroundSystemCreate();
 * undergroundSystemCheckIn(obj, id, stationName, t);
 * undergroundSystemCheckOut(obj, id, stationName, t);
 * double param_3 = undergroundSystemGetAverageTime(obj, startStation, endStation);
 * undergroundSystemFree(obj);
 */
```

</details>

<details><summary>C++</summary>

```c++
class UndergroundSystem {
   public:
    using Start = pair<string, int>;
    using StartEnd = pair<string, string>;
    using SumAndAmount = pair<int, int>;
    struct StartEndHash {
        int operator()(const StartEnd& x) const { return hash<string>()(x.first + x.second); }
    };
    unordered_map<int, Start> startInfo;
    unordered_map<StartEnd, SumAndAmount, StartEndHash> table;

    UndergroundSystem() {}
    void checkIn(int id, string stationName, int t) {
        //
        startInfo[id] = {stationName, t};
    }
    void checkOut(int id, string stationName, int t) {
        auto startTime = startInfo[id].second;
        table[{startInfo[id].first, stationName}].first += (t - startTime);
        table[{startInfo[id].first, stationName}].second++;
    }
    double getAverageTime(string startStation, string endStation) {
        double retVal;

        auto sum = table[{startStation, endStation}].first;
        auto amount = table[{startStation, endStation}].second;
        retVal = double(sum) / amount;

        return retVal;
    }
};
/**
 * Your UndergroundSystem object will be instantiated and called as such:
 * UndergroundSystem* obj = new UndergroundSystem();
 * obj->checkIn(id,stationName,t);
 * obj->checkOut(id,stationName,t);
 * double param_3 = obj->getAverageTime(startStation,endStation);
 */
```

</details>

<details><summary>Python3</summary>

```python
class UndergroundSystem:
    def __init__(self):
        self.startInfo = dict()
        self.table = dict()

    def checkIn(self, id: int, stationName: str, t: int) -> None:
        self.startInfo[id] = (stationName, t)

    def checkOut(self, id: int, stationName: str, t: int) -> None:
        startTime = self.startInfo[id][1]
        index = (self.startInfo[id][0], stationName)
        rec = self.table.get(index, (0, 0))
        self.table[index] = (rec[0] + t - startTime, rec[1] + 1)

    def getAverageTime(self, startStation: str, endStation: str) -> float:
        retVal = 0

        index = (startStation, endStation)
        sum, amount = self.table[index]
        retVal = sum / amount

        return retVal

# Your UndergroundSystem object will be instantiated and called as such:
# obj = UndergroundSystem()
# obj.checkIn(id,stationName,t)
# obj.checkOut(id,stationName,t)
# param_3 = obj.getAverageTime(startStation,endStation)
```

</details>

## [1436. Destination City](https://leetcode.com/problems/destination-city/)  1192

- [Official](https://leetcode.com/problems/destination-city/editorial/)
- [Official](https://leetcode.cn/problems/destination-city/solutions/1026156/lu-xing-zhong-dian-zhan-by-leetcode-solu-pscd/)

<details><summary>Description</summary>

```text
You are given the array paths,
where paths[i] = [cityAi, cityBi] means there exists a direct path going from cityAi to cityBi.
Return the destination city, that is, the city without any path outgoing to another city.

It is guaranteed that the graph of paths forms a line without any loop,
therefore, there will be exactly one destination city.

Example 1:
Input: paths = [["London","New York"],["New York","Lima"],["Lima","Sao Paulo"]]
Output: "Sao Paulo"
Explanation: Starting at "London" city you will reach "Sao Paulo" city which is the destination city.
Your trip consist of: "London" -> "New York" -> "Lima" -> "Sao Paulo".

Example 2:
Input: paths = [["B","C"],["D","B"],["C","A"]]
Output: "A"
Explanation: All possible trips are:
"D" -> "B" -> "C" -> "A".
"B" -> "C" -> "A".
"C" -> "A".
"A".
Clearly the destination city is "A".

Example 3:
Input: paths = [["A","Z"]]
Output: "Z"

Constraints:
1 <= paths.length <= 100
paths[i].length == 2
1 <= cityAi.length, cityBi.length <= 10
cityAi != cityBi
All strings consist of lowercase and uppercase English letters and the space character.
```

<details><summary>Hint</summary>

```text
1. Start in any city and use the path to move to the next city.
2. Eventually, you will reach a city with no path outgoing, this is the destination city.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MAX_LENGTH (10 + 1)
struct hashStruct {
    char key[MAX_LENGTH];
    UT_hash_handle hh;
};
void freeAll(struct hashStruct* pFree) {
    struct hashStruct* current;
    struct hashStruct* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%s\n", pFree->key);
        HASH_DEL(pFree, current);
        free(current);
    }
}
char* destCity(char*** paths, int pathsSize, int* pathsColSize) {
    char* pRetVal = NULL;

    struct hashStruct* pOutgoing = NULL;
    struct hashStruct* pAdd;
    int i;
    for (i = 0; i < pathsSize; ++i) {
        pAdd = NULL;
        HASH_FIND_STR(pOutgoing, paths[i][0], pAdd);
        pAdd = (struct hashStruct*)malloc(sizeof(struct hashStruct));
        if (pAdd == NULL) {
            perror("malloc");
            freeAll(pOutgoing);
            free(pRetVal);
            return pRetVal;
        }
        snprintf(pAdd->key, MAX_LENGTH, "%s", paths[i][0]);
        HASH_ADD_STR(pOutgoing, key, pAdd);
    }

    for (i = 0; i < pathsSize; ++i) {
        pAdd = NULL;
        HASH_FIND_STR(pOutgoing, paths[i][1], pAdd);
        if (pAdd == NULL) {
            pRetVal = paths[i][1];
            break;
        }
    }

    freeAll(pOutgoing);
    pOutgoing = NULL;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string destCity(vector<vector<string>>& paths) {
        string retVal;

        int pathsSize = paths.size();

        unordered_set<string> outgoing;
        for (int i = 0; i < pathsSize; ++i) {
            outgoing.insert(paths[i][0]);
        }

        for (int i = 0; i < pathsSize; ++i) {
            string cityB = paths[i][1];
            if (outgoing.count(cityB) == 0) {
                retVal = cityB;
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
    def destCity(self, paths: List[List[str]]) -> str:
        retVal = ""

        outgoing = set()
        for cityA, cityB in paths:
            outgoing.add(cityA)

        for cityA, cityB in paths:
            if cityB not in outgoing:
                retVal = cityB
                break

        return retVal
```

</details>

## [1496. Path Crossing](https://leetcode.com/problems/path-crossing/)  1508

- [Official](https://leetcode.com/problems/path-crossing/editorial/)
- [Official](https://leetcode.cn/problems/path-crossing/description/)

<details><summary>Description</summary>

```text
Given a string path, where path[i] = 'N', 'S', 'E' or 'W',
each representing moving one unit north, south, east, or west, respectively.
You start at the origin (0, 0) on a 2D plane and walk on the path specified by path.

Return true if the path crosses itself at any point, that is,
if at any time you are on a location you have previously visited.
Return false otherwise.

Example 1:
Input: path = "NES"
Output: false
Explanation: Notice that the path doesn't cross any point more than once.

Example 2:
Input: path = "NESWW"
Output: true
Explanation: Notice that the path visits the origin twice.

Constraints:
1 <= path.length <= 10^4
path[i] is either 'N', 'S', 'E', or 'W'.
```

<details><summary>Hint</summary>

```text
1. Simulate the process while keeping track of visited points.
2. Use a set to store previously visited points.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MAX_LENGTH (16)  // 1 <= path.length <= 10^4
struct hashTable {
    char key[MAX_LENGTH];
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* pCurrent;
    struct hashTable* pTmp;
    HASH_ITER(hh, pFree, pCurrent, pTmp) {
        // printf("%s\n", pFree->key);
        HASH_DEL(pFree, pCurrent);
        free(pCurrent);
    }
}
bool isPathCrossing(char* path) {
    bool retVal = false;

    int x = 0;
    int y = 0;
    char pointsHash[MAX_LENGTH];
    memset(pointsHash, 0, sizeof(pointsHash));
    snprintf(pointsHash, sizeof(pointsHash), "%d,%d", x, y);

    struct hashTable* pVisited = NULL;
    struct hashTable* pTmp = NULL;
    pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
    if (pTmp == NULL) {
        perror("malloc");
        return retVal;
    }
    snprintf(pTmp->key, MAX_LENGTH, "%s", pointsHash);
    HASH_ADD_STR(pVisited, key, pTmp);

    int pathSize = strlen(path);
    int i;
    for (i = 0; i < pathSize; ++i) {
        if (path[i] == 'N') {
            y += 1;
        } else if (path[i] == 'S') {
            y -= 1;
        } else if (path[i] == 'E') {
            x += 1;
        } else if (path[i] == 'W') {
            x -= 1;
        }
        memset(pointsHash, 0, sizeof(pointsHash));
        snprintf(pointsHash, sizeof(pointsHash), "%d,%d", x, y);

        pTmp = NULL;
        HASH_FIND_STR(pVisited, pointsHash, pTmp);
        if (pTmp != NULL) {
            retVal = true;
            break;
        }
        pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
        if (pTmp == NULL) {
            perror("malloc");
            freeAll(pVisited);
            pVisited = NULL;
            return retVal;
        }
        snprintf(pTmp->key, MAX_LENGTH, "%s", pointsHash);
        HASH_ADD_STR(pVisited, key, pTmp);
    }

    freeAll(pVisited);
    pVisited = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    bool isPathCrossing(string path) {
        bool retVal = false;

        unordered_map<char, pair<int, int>> moves;
        moves['N'] = {0, 1};
        moves['S'] = {0, -1};
        moves['W'] = {-1, 0};
        moves['E'] = {1, 0};

        unordered_set<string> visited;

        int x = 0;
        int y = 0;
        string pointsHash = to_string(x) + "," + to_string(y);
        visited.insert(pointsHash);

        for (char direction : path) {
            x += moves[direction].first;
            y += moves[direction].second;
            string pointsHash = to_string(x) + "," + to_string(y);
            if (visited.find(pointsHash) != visited.end()) {
                retVal = true;
                break;
            }
            visited.insert(pointsHash);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def isPathCrossing(self, path: str) -> bool:
        retVal = False

        moves = {
            "N": (0, 1),
            "S": (0, -1),
            "W": (-1, 0),
            "E": (1, 0)
        }

        visited = {(0, 0)}
        x = 0
        y = 0
        for direction in path:
            x += moves[direction][0]
            y += moves[direction][1]
            if (x, y) in visited:
                retVal = True
                break
            visited.add((x, y))

        return retVal
```

</details>

## [1512. Number of Good Pairs](https://leetcode.com/problems/number-of-good-pairs/)  1160

- [Official](https://leetcode.cn/problems/number-of-good-pairs/solutions/336449/hao-shu-dui-de-shu-mu-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given an array of integers nums, return the number of good pairs.

A pair (i, j) is called good if nums[i] == nums[j] and i < j.

Example 1:
Input: nums = [1,2,3,1,1,3]
Output: 4
Explanation: There are 4 good pairs (0,3), (0,4), (3,4), (2,5) 0-indexed.

Example 2:
Input: nums = [1,1,1,1]
Output: 6
Explanation: Each pair in the array are good.

Example 3:
Input: nums = [1,2,3]
Output: 0

Constraints:
1 <= nums.length <= 100
1 <= nums[i] <= 100
```

<details><summary>Hint</summary>

```text
1. Count how many times each number appears.
   If a number appears n times, then n * (n – 1) // 2 good pairs can be made with this number.
```

</details>

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
int numIdenticalPairs(int* nums, int numsSize) {
    int retVal = 0;

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
            pTemp->value = 1;
            HASH_ADD_INT(pHashTable, key, pTemp);
        } else {
            retVal += pTemp->value;
            pTemp->value += 1;
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
    int numIdenticalPairs(vector<int>& nums) {
        int retVal = 0;

        unordered_map<int, int> hashTable;
        for (auto num : nums) {
            auto iterator = hashTable.find(num);
            if (iterator != hashTable.end()) {
                retVal += hashTable[num];
            }
            hashTable[num] += 1;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def numIdenticalPairs(self, nums: List[int]) -> int:
        retVal = 0

        hashTable = defaultdict(int)
        for num in nums:
            if num in hashTable:
                retVal += hashTable[num]
            hashTable[num] += 1

        return retVal
```

</details>

## [1604. Alert Using Same Key-Card Three or More Times in a One Hour Period](https://leetcode.com/problems/alert-using-same-key-card-three-or-more-times-in-a-one-hour-period/)  1606

- [Official](https://leetcode.cn/problems/alert-using-same-key-card-three-or-more-times-in-a-one-hour-period/solutions/2095526/jing-gao-yi-xiao-shi-nei-shi-yong-xiang-ioeiw/)

<details><summary>Description</summary>

```text
LeetCode company workers use key-cards to unlock office doors.
Each time a worker uses their key-card, the security system saves the worker's name and the time when it was used.
The system emits an alert if any worker uses the key-card three or more times in a one-hour period.

You are given a list of strings keyName and keyTime where [keyName[i], keyTime[i]]
corresponds to a person's name and the time when their key-card was used in a single day.

Access times are given in the 24-hour time format "HH:MM", such as "23:51" and "09:49".

Return a list of unique worker names who received an alert for frequent keycard use.
Sort the names in ascending order alphabetically.

Notice that "10:00" - "11:00" is considered to be within a one-hour period,
while "22:51" - "23:52" is not considered to be within a one-hour period.

Example 1:
Input: keyName = ["daniel","daniel","daniel","luis","luis","luis","luis"],
keyTime = ["10:00","10:40","11:00","09:00","11:00","13:00","15:00"]
Output: ["daniel"]
Explanation: "daniel" used the keycard 3 times in a one-hour period ("10:00","10:40", "11:00").

Example 2:
Input: keyName = ["alice","alice","alice","bob","bob","bob","bob"],
keyTime = ["12:01","12:00","18:00","21:00","21:20","21:30","23:00"]
Output: ["bob"]
Explanation: "bob" used the keycard 3 times in a one-hour period ("21:00","21:20", "21:30").

Constraints:
1 <= keyName.length, keyTime.length <= 10^5
keyName.length == keyTime.length
keyTime[i] is in the format "HH:MM".
[keyName[i], keyTime[i]] is unique.
1 <= keyName[i].length <= 10
keyName[i] contains only lowercase English letters.
```

</details>

<details><summary>C</summary>

```c
#define MAX_NAME_LENGTH (10 + 2)  // 1 <= keyName[i].length <= 10
struct hash_struct {
    char name[MAX_NAME_LENGTH];
    struct ListNode* timeList;  // use list instead of array to avoid Time Limit Exceeded
    UT_hash_handle hh;
};
void freeTimeList(struct ListNode* pFree) {
    struct ListNode* pCurrent = NULL;
    while (pFree != NULL) {
        pCurrent = pFree;
        pFree = pFree->next;
        free(pCurrent);
        pCurrent = NULL;
    }
}
void freeAll(struct hash_struct* pFree) {
    struct hash_struct* current;
    struct hash_struct* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        HASH_DEL(pFree, current);
        freeTimeList(current->timeList);
        free(current);
    }
}
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int compareString(const void* str1, const void* str2) {
    char* const* p1 = str1;
    char* const* p2 = str2;

    // ascending order
    return strcmp(*p1, *p2);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** alertNames(char** keyName, int keyNameSize, char** keyTime, int keyTimeSize, int* returnSize) {
    char** pRetVal = NULL;

    //
    (*returnSize) = 0;

    // hashTable(name, time)
    struct hash_struct* hashTable = NULL;
    struct hash_struct* pTmp;
    struct ListNode* pNode;
    int i;
    for (i = 0; i < keyNameSize; ++i) {
        pTmp = NULL;
        HASH_FIND_STR(hashTable, keyName[i], pTmp);
        if (pTmp == NULL) {
            pTmp = (struct hash_struct*)malloc(sizeof(struct hash_struct));
            if (pTmp == NULL) {
                perror("malloc");
                freeAll(hashTable);
                hashTable = NULL;
                return pRetVal;
            }
            snprintf(pTmp->name, MAX_NAME_LENGTH, "%s", keyName[i]);
            pTmp->timeList = NULL;
            HASH_ADD_STR(hashTable, name, pTmp);
        }
        pNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        if (pNode == NULL) {
            perror("malloc");
            freeAll(hashTable);
            hashTable = NULL;
            return pRetVal;
        }
        pNode->val = 60 * ((keyTime[i][0] - '0') * 10 + (keyTime[i][1] - '0')) +
                     ((keyTime[i][3] - '0') * 10 + (keyTime[i][4] - '0'));
        pNode->next = pTmp->timeList;
        pTmp->timeList = pNode;
    }

    // malloc return value
    pRetVal = (char**)malloc(keyNameSize * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        freeAll(hashTable);
        hashTable = NULL;
        return pRetVal;
    }

    //
    int timeSize = 0;
    int timeArray[keyNameSize];
    struct ListNode* pNext;
    struct hash_struct* pCurrent;
    pTmp = NULL;
    HASH_ITER(hh, hashTable, pCurrent, pTmp) {
        timeSize = 0;
        memset(timeArray, 0, sizeof(timeArray));
        for (pNext = pCurrent->timeList; pNext; pNext = pNext->next) {
            timeArray[timeSize++] = pNext->val;
        }
        qsort(timeArray, timeSize, sizeof(int), compareInteger);

        for (i = 2; i < timeSize; ++i) {
            if (timeArray[i] - timeArray[i - 2] <= 60) {
                pRetVal[(*returnSize)] = (char*)malloc(MAX_NAME_LENGTH * sizeof(char));
                if (pRetVal[(*returnSize)] == NULL) {
                    perror("malloc");
                    freeAll(hashTable);
                    hashTable = NULL;
                    for (i = 0; i < (*returnSize); ++i) {
                        free(pRetVal[i]);
                        pRetVal[i] = NULL;
                    }
                    free(pRetVal);
                    pRetVal = NULL;
                    (*returnSize) = 0;
                    return pRetVal;
                }
                memset(pRetVal[(*returnSize)], 0, (MAX_NAME_LENGTH * sizeof(char)));
                snprintf(pRetVal[(*returnSize)], (MAX_NAME_LENGTH * sizeof(char)), "%s", pCurrent->name);
                (*returnSize)++;
                break;
            }
        }
    }
    qsort(pRetVal, (*returnSize), sizeof(char*), compareString);

    //
    freeAll(hashTable);
    hashTable = NULL;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<string> alertNames(vector<string>& keyName, vector<string>& keyTime) {
        vector<string> retVal;

        int len = keyName.size();

        unordered_map<string, vector<int>> hashTable;
        for (int i = 0; i < len; ++i) {
            int hour = (keyTime[i][0] - '0') * 10 + (keyTime[i][1] - '0');
            int minute = (keyTime[i][3] - '0') * 10 + (keyTime[i][4] - '0');
            hashTable[keyName[i]].emplace_back(hour * 60 + minute);
        }

        for (auto& [pName, pTime] : hashTable) {
            sort(pTime.begin(), pTime.end());

            for (long unsigned int i = 2; i < pTime.size(); ++i) {
                if (pTime[i] - pTime[i - 2] <= 60) {
                    retVal.emplace_back(pName);
                    break;
                }
            }
        }
        sort(retVal.begin(), retVal.end());

        return retVal;
    }
};
```

</details>

## [1624. Largest Substring Between Two Equal Characters](https://leetcode.com/problems/largest-substring-between-two-equal-characters/)

- [Official](https://leetcode.com/problems/largest-substring-between-two-equal-characters/editorial/)
- [Official](https://leetcode.cn/problems/largest-substring-between-two-equal-characters/solutions/1827900/liang-ge-xiang-tong-zi-fu-zhi-jian-de-zu-9n2l/)

<details><summary>Description</summary>

```text
Given a string s, return the length of the longest substring between two equal characters,
excluding the two characters.
If there is no such substring return -1.

A substring is a contiguous sequence of characters within a string.

Example 1:
Input: s = "aa"
Output: 0
Explanation: The optimal substring here is an empty substring between the two 'a's.

Example 2:
Input: s = "abca"
Output: 2
Explanation: The optimal substring here is "bc".

Example 3:
Input: s = "cbzxy"
Output: -1
Explanation: There are no characters that appear twice in s.

Constraints:
1 <= s.length <= 300
s contains only lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Try saving the first and last position of each character
2. Try finding every pair of indexes with equal characters
```

</details>

</details>

<details><summary>C</summary>

```c
int maxLengthBetweenEqualCharacters(char* s) {
    int retVal = -1;

    int sSize = strlen(s);

#define MAX_LETTERS (26)  // s contains only lowercase English letters.
    int hashTable[MAX_LETTERS];
    memset(hashTable, -1, sizeof(hashTable));

    int idx;
    int i;
    for (i = 0; i < sSize; ++i) {
        idx = s[i] - 'a';
        if (hashTable[idx] != -1) {
            retVal = fmax(retVal, i - hashTable[idx] - 1);
        } else {
            hashTable[idx] = i;
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
    int maxLengthBetweenEqualCharacters(string s) {
        int retVal = -1;

        int sSize = s.size();

#define MAX_LETTERS (26)  // s contains only lowercase English letters.
        vector<int> hashTable(MAX_LETTERS, -1);
        for (int i = 0; i < sSize; ++i) {
            int idx = s[i] - 'a';
            if (hashTable[idx] != -1) {
                retVal = max(retVal, i - hashTable[idx] - 1);
            } else {
                hashTable[idx] = i;
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
    def maxLengthBetweenEqualCharacters(self, s: str) -> int:
        retVal = -1

        hashTable = defaultdict(int)
        for idx, c in enumerate(s):
            if c in hashTable:
                retVal = max(retVal, idx - hashTable[c] - 1)
            else:
                hashTable[c] = idx

        return retVal
```

</details>

## [1647. Minimum Deletions to Make Character Frequencies Unique](https://leetcode.com/problems/minimum-deletions-to-make-character-frequencies-unique/)  1509

<details><summary>Description</summary>

```text
A string s is called good if there are no two different characters in s that have the same frequency.

Given a string s, return the minimum number of characters you need to delete to make s good.

The frequency of a character in a string is the number of times it appears in the string.
For example, in the string "aab", the frequency of 'a' is 2, while the frequency of 'b' is 1.

Example 1:
Input: s = "aab"
Output: 0
Explanation: s is already good.

Example 2:
Input: s = "aaabbbcc"
Output: 2
Explanation: You can delete two 'b's resulting in the good string "aaabcc".
Another way it to delete one 'b' and one 'c' resulting in the good string "aaabbc".

Example 3:
Input: s = "ceabaacb"
Output: 2
Explanation: You can delete both 'c's resulting in the good string "eabaab".
Note that we only care about characters that are still in the string at the end (i.e. frequency of 0 is ignored).

Constraints:
1 <= s.length <= 10^5
s contains only lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. As we can only delete characters, if we have multiple characters having the same frequency,
   we must decrease all the frequencies of them, except one.
2. Sort the alphabet characters by their frequencies non-increasingly.
3. Iterate on the alphabet characters,
   keep decreasing the frequency of the current character until it reaches a value that has not appeared before.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
int minDeletions(char* s) {
    int retVal = 0;

#define MAX_FREQUENCY_SIZE (26)  // s contains only lowercase English letters.
    int frequency[MAX_FREQUENCY_SIZE];
    memset(frequency, 0, sizeof(frequency));

    int sSize = strlen(s);
    int i;
    for (i = 0; i < sSize; ++i) {
        frequency[s[i] - 'a']++;
    }
    qsort(frequency, MAX_FREQUENCY_SIZE, sizeof(int), compareInteger);

    int previousFrequency = frequency[0];
    int j;
    for (i = 1; i < MAX_FREQUENCY_SIZE; ++i) {
        for (j = frequency[i]; j > 0; --j) {
            if (j < previousFrequency) {
                previousFrequency = j;
                break;
            }
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
    int minDeletions(string s) {
        int retVal = 0;

        map<char, int> frequency;
        for (char c : s) {
            frequency[c]++;
        }

        set<int> hashSet;
        for (auto [key, value] : frequency) {
            for (int i = value; i > 0; --i) {
                if (hashSet.count(i) == 0) {
                    hashSet.insert(i);
                    break;
                }
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
    def minDeletions(self, s: str) -> int:
        retVal = 0

        frequency = Counter(s).most_common()

        hashSet = set()
        for key, value in frequency:
            for i in range(value, 0, -1):
                if i not in hashSet:
                    hashSet.add(i)
                    break
                retVal += 1

        return retVal
```

</details>

## [1657. Determine if Two Strings Are Close](https://leetcode.com/problems/determine-if-two-strings-are-close/)  1530

- [Official](https://leetcode.cn/problems/determine-if-two-strings-are-close/solutions/2539741/que-ding-liang-ge-zi-fu-chuan-shi-fou-ji-jdpa/)

<details><summary>Description</summary>

```text
Two strings are considered close if you can attain one from the other using the following operations:
- Operation 1: Swap any two existing characters.
  - For example, abcde -> aecdb
- Operation 2: Transform every occurrence of one existing character into another existing character,
  and do the same with the other character.
  - For example, aacabb -> bbcbaa (all a's turn into b's, and all b's turn into a's)

You can use the operations on either string as many times as necessary.

Given two strings, word1 and word2, return true if word1 and word2 are close, and false otherwise.

Example 1:
Input: word1 = "abc", word2 = "bca"
Output: true
Explanation: You can attain word2 from word1 in 2 operations.
Apply Operation 1: "abc" -> "acb"
Apply Operation 1: "acb" -> "bca"

Example 2:
Input: word1 = "a", word2 = "aa"
Output: false
Explanation: It is impossible to attain word2 from word1, or vice versa, in any number of operations.

Example 3:
Input: word1 = "cabbba", word2 = "abbccc"
Output: true
Explanation: You can attain word2 from word1 in 3 operations.
Apply Operation 1: "cabbba" -> "caabbb"
Apply Operation 2: "caabbb" -> "baaccc"
Apply Operation 2: "baaccc" -> "abbccc"

Constraints:
1 <= word1.length, word2.length <= 10^5
word1 and word2 contain only lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Operation 1 allows you to freely reorder the string.
2. Operation 2 allows you to freely reassign the letters' frequencies.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
bool closeStrings(char* word1, char* word2) {
    bool retVal = false;

    int word1Size = strlen(word1);
    int word2Size = strlen(word2);
    if (word1Size != word2Size) {
        return retVal;
    }

#define HASHTABLE_SIZE (26)  // word1 and word2 contain only lowercase English letters.
    int hashTable1[HASHTABLE_SIZE];
    memset(hashTable1, 0, sizeof(hashTable1));
    int hashTable2[HASHTABLE_SIZE];
    memset(hashTable2, 0, sizeof(hashTable2));
    int i;
    for (i = 0; i < word1Size; ++i) {
        ++hashTable1[word1[i] - 'a'];
        ++hashTable2[word2[i] - 'a'];
    }

    for (i = 0; i < HASHTABLE_SIZE; ++i) {
        if ((hashTable1[i] == 0) && (hashTable2[i] != 0)) {
            return retVal;
        } else if ((hashTable1[i] != 0) && (hashTable2[i] == 0)) {
            return retVal;
        }
    }

    qsort(hashTable1, HASHTABLE_SIZE, sizeof(hashTable1[0]), compareInteger);
    qsort(hashTable2, HASHTABLE_SIZE, sizeof(hashTable2[0]), compareInteger);
    for (i = 0; i < HASHTABLE_SIZE; ++i) {
        if (hashTable1[i] != hashTable2[i]) {
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
    bool closeStrings(string word1, string word2) {
        bool retVal = false;

        int word1Size = word1.size();
        int word2Size = word2.size();
        if (word1Size != word2Size) {
            return retVal;
        }

#define HASHTABLE_SIZE (26)  // word1 and word2 contain only lowercase English letters.
        vector<int> hashTable1(HASHTABLE_SIZE, 0);
        vector<int> hashTable2(HASHTABLE_SIZE, 0);
        for (int i = 0; i < word1Size; ++i) {
            hashTable1[word1[i] - 'a']++;
            hashTable2[word2[i] - 'a']++;
        }

        for (int i = 0; i < HASHTABLE_SIZE; ++i) {
            if ((hashTable1[i] == 0) && (hashTable2[i] != 0)) {
                return retVal;
            } else if ((hashTable1[i] != 0) && (hashTable2[i] == 0)) {
                return retVal;
            }
        }

        sort(hashTable1.begin(), hashTable1.end());
        sort(hashTable2.begin(), hashTable2.end());
        if (hashTable1 != hashTable2) {
            return retVal;
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
    def closeStrings(self, word1: str, word2: str) -> bool:
        retVal = False

        word1Size = len(word1)
        word2Size = len(word2)
        if word1Size != word2Size:
            return retVal

        hashTable1 = Counter(word1)
        hashTable2 = Counter(word2)

        if hashTable1.keys() != hashTable2.keys():
            return retVal

        if sorted(hashTable1.values()) != sorted(hashTable2.values()):
            return retVal

        retVal = True

        return retVal
```

</details>

## [1781. Sum of Beauty of All Substrings](https://leetcode.com/problems/sum-of-beauty-of-all-substrings/)  1714

- [Official](https://leetcode.cn/problems/sum-of-beauty-of-all-substrings/solutions/2016548/suo-you-zi-zi-fu-chuan-mei-li-zhi-zhi-he-rq3x/)

<details><summary>Description</summary>

```text
The beauty of a string is the difference in frequencies between the most frequent and least frequent characters.
- For example, the beauty of "abaacc" is 3 - 1 = 2.
Given a string s, return the sum of beauty of all of its substrings.

Example 1:
Input: s = "aabcb"
Output: 5
Explanation: The substrings with non-zero beauty are ["aab","aabc","aabcb","abcb","bcb"], each with beauty equal to 1.

Example 2:
Input: s = "aabcbaa"
Output: 17

Constraints:
1 <= s.length <= 500
s consists of only lowercase English letters.
```

</details>

<details><summary>C</summary>

```c
// https://leetcode.cn/problems/sum-of-beauty-of-all-substrings/solutions/2016548/suo-you-zi-zi-fu-chuan-mei-li-zhi-zhi-he-rq3x/
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
int beautySum(char* s) {
    int retVal = 0;

    int len = strlen(s);
    if (len == 1) {
        return retVal;
    }

// s consists of only lowercase English letters
#define HASH_SIZE (26)
    int HASHTABLE[HASH_SIZE];
    int mostFrequencies;
    int leastFrequencies;
    int idx;

    int i, j, k;
    for (i = 0; i < len; ++i) {
        memset(HASHTABLE, 0, sizeof(HASHTABLE));
        mostFrequencies = 0;
        for (j = i; j < len; ++j) {
            idx = s[j] - 'a';
            ++HASHTABLE[idx];
            mostFrequencies = MAX(mostFrequencies, HASHTABLE[idx]);

            leastFrequencies = len;
            for (k = 0; k < HASH_SIZE; ++k) {
                if (HASHTABLE[k] == 0) {
                    continue;
                }
                leastFrequencies = MIN(leastFrequencies, HASHTABLE[k]);
            }

            retVal += (mostFrequencies - leastFrequencies);
        }
    }

    return retVal;
}
```

</details>

## [1796. Second Largest Digit in a String](https://leetcode.com/problems/second-largest-digit-in-a-string/)  1341

<details><summary>Description</summary>

```text
Given an alphanumeric string s, return the second largest numerical digit that appears in s, or -1 if it does not exist.

An alphanumeric string is a string consisting of lowercase English letters and digits.

Example 1:
Input: s = "dfa12321afd"
Output: 2
Explanation: The digits that appear in s are [1, 2, 3]. The second largest digit is 2.

Example 2:
Input: s = "abc1111"
Output: -1
Explanation: The digits that appear in s are [1]. There is no second largest digit.

Constraints:
1 <= s.length <= 500
s consists of only lowercase English letters and/or digits.
```

</details>

<details><summary>C</summary>

```c
int secondHighest(char* s) {
    int retVal = -1;

    // use hash table to record appeared numerical digit
    int hashTable[10] = {0};
    while (*s) {
        if ((*s >= '0') && (*s <= '9')) {
            ++hashTable[*s - '0'];
        }
        ++s;
    }

    // travel hash table to return the second largest
    int count = 0;
    int i;
    for (i = 9; i >= 0; --i) {
        if (hashTable[i] != 0) {
            ++count;
            if (count == 2) {
                retVal = i;
                break;
            }
        }
    }

    return retVal;
}
```

</details>

## [1807. Evaluate the Bracket Pairs of a String](https://leetcode.com/problems/evaluate-the-bracket-pairs-of-a-string/)  1481

- [Official](https://leetcode.cn/problems/evaluate-the-bracket-pairs-of-a-string/solutions/2055952/ti-huan-zi-fu-chuan-zhong-de-gua-hao-nei-y8d3/)

<details><summary>Description</summary>

```text
You are given a string s that contains some bracket pairs, with each pair containing a non-empty key.
- For example, in the string "(name)is(age)yearsold", there are two bracket pairs that contain the keys "name" and "age".

You know the values of a wide range of keys.
This is represented by a 2D string array knowledge
where each knowledge[i] = [keyi, valuei] indicates that key keyi has a value of valuei.

You are tasked to evaluate all of the bracket pairs.
When you evaluate a bracket pair that contains some key keyi, you will:
- Replace keyi and the bracket pair with the key's corresponding valuei.
- If you do not know the value of the key,
  you will replace keyi and the bracket pair with a question mark "?" (without the quotation marks).

Each key will appear at most once in your knowledge. There will not be any nested brackets in s.

Return the resulting string after evaluating all of the bracket pairs.

Example 1:
Input: s = "(name)is(age)yearsold", knowledge = [["name","bob"],["age","two"]]
Output: "bobistwoyearsold"
Explanation:
The key "name" has a value of "bob", so replace "(name)" with "bob".
The key "age" has a value of "two", so replace "(age)" with "two".

Example 2:
Input: s = "hi(name)", knowledge = [["a","b"]]
Output: "hi?"
Explanation: As you do not know the value of the key "name", replace "(name)" with "?".

Example 3:
Input: s = "(a)(a)(a)aaa", knowledge = [["a","yes"]]
Output: "yesyesyesaaa"
Explanation: The same key can appear multiple times.
The key "a" has a value of "yes", so replace all occurrences of "(a)" with "yes".
Notice that the "a"s not in a bracket pair are not evaluated.

Constraints:
1 <= s.length <= 10^5
0 <= knowledge.length <= 10^5
knowledge[i].length == 2
1 <= keyi.length, valuei.length <= 10
s consists of lowercase English letters and round brackets '(' and ')'.
Every open bracket '(' in s will have a corresponding close bracket ')'.
The key in each bracket pair of s will be non-empty.
There will not be any nested bracket pairs in s.
keyi and valuei consist of lowercase English letters.
Each keyi in knowledge is unique.
```

</details>

<details><summary>C</summary>

```c
#define MAX_LENGTH (10 + 1)
struct hashStruct {
    char key[MAX_LENGTH];
    char value[MAX_LENGTH];
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
char* evaluate(char* s, char*** knowledge, int knowledgeSize, int* knowledgeColSize) {
    char* pRetVal = NULL;

    int i;

    //
    int len = strlen(s);
    pRetVal = (char*)malloc((MAX_LENGTH - 2) * len * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, ((MAX_LENGTH - 2) * len * sizeof(char)));
    int returnSize = 0;

    //
    struct hashStruct* pKnowledgeHash = NULL;
    struct hashStruct* pAdd;
    for (i = 0; i < knowledgeSize; ++i) {
        pAdd = NULL;
        HASH_FIND_STR(pKnowledgeHash, knowledge[i][0], pAdd);
        pAdd = (struct hashStruct*)malloc(sizeof(struct hashStruct));
        if (pAdd == NULL) {
            perror("malloc");
            freeAll(pKnowledgeHash);
            free(pRetVal);
            return pRetVal;
        }
        snprintf(pAdd->key, MAX_LENGTH, "%s", knowledge[i][0]);
        snprintf(pAdd->value, MAX_LENGTH, "%s", knowledge[i][1]);
        HASH_ADD_STR(pKnowledgeHash, key, pAdd);
    }

    //
    bool findKey = false;
    char key[len];
    memset(key, 0, sizeof(key));
    int keySize = 0;
    struct hashStruct* pFind;
    for (i = 0; i < len; ++i) {
        if (s[i] == '(') {
            findKey = true;
        } else if (s[i] == ')') {
            pFind = NULL;
            HASH_FIND_STR(pKnowledgeHash, key, pFind);
            if (pFind != NULL) {
                returnSize += sprintf(pRetVal + returnSize, "%s", pFind->value);
            } else {
                pRetVal[returnSize++] = '?';
            }
            findKey = false;
            memset(key, 0, sizeof(key));
            keySize = 0;
        } else {
            if (findKey == true) {
                key[keySize++] = s[i];
            } else {
                pRetVal[returnSize++] = s[i];
            }
        }
    }

    //
    freeAll(pKnowledgeHash);

    return pRetVal;
}
```

</details>

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        string retVal;

        //
        unordered_map<string, string> hashTable;
        for (auto& pKnowledge : knowledge) {
            hashTable[pKnowledge[0]] = pKnowledge[1];
        }

        //
        bool findKey = false;
        string key;
        for (char c : s) {
            if (c == '(') {
                findKey = true;
            } else if (c == ')') {
                if (hashTable.count(key) > 0) {
                    retVal += hashTable[key];
                } else {
                    retVal.push_back('?');
                }
                findKey = false;
                key.clear();
            } else {
                if (findKey == true) {
                    key.push_back(c);
                } else {
                    retVal.push_back(c);
                }
            }
        }

        return retVal;
    }
};
```

</details>

## [1814. Count Nice Pairs in an Array](https://leetcode.com/problems/count-nice-pairs-in-an-array/)  1737

- [Official](https://leetcode.com/problems/count-nice-pairs-in-an-array/editorial/)
- [Official](https://leetcode.cn/problems/count-nice-pairs-in-an-array/solutions/2064186/tong-ji-yi-ge-shu-zu-zhong-hao-dui-zi-de-ywux/)

<details><summary>Description</summary>

```text
You are given an array nums that consists of non-negative integers.
Let us define rev(x) as the reverse of the non-negative integer x.
For example, rev(123) = 321, and rev(120) = 21.
A pair of indices (i, j) is nice if it satisfies all of the following conditions:
- 0 <= i < j < nums.length
- nums[i] + rev(nums[j]) == nums[j] + rev(nums[i])
Return the number of nice pairs of indices. Since that number can be too large, return it modulo 10^9 + 7.

Example 1:
Input: nums = [42,11,1,97]
Output: 2
Explanation: The two pairs are:
 - (0,3) : 42 + rev(97) = 42 + 79 = 121, 97 + rev(42) = 97 + 24 = 121.
 - (1,2) : 11 + rev(1) = 11 + 1 = 12, 1 + rev(11) = 1 + 11 = 12.

Example 2:
Input: nums = [13,10,35,24,76]
Output: 4

Constraints:
1 <= nums.length <= 10^5
0 <= nums[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. The condition can be rearranged to (nums[i] - rev(nums[i])) == (nums[j] - rev(nums[j])).
2. Transform each nums[i] into (nums[i] - rev(nums[i])). Then, count the number of (i, j) pairs that have equal values.
3. Keep a map storing the frequencies of values that you have seen so far. For each i, check if nums[i] is in the map.
   If it is, then add that count to the overall count. Then, increment the frequency of nums[i].
```

</details>

</details>

<details><summary>C</summary>

```c
#define MODULO (int)(1e9 + 7)
struct hashTable {
    int index;
    int count;
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
int reverseInteger(int num) {
    int retVal = 0;

    while (num > 0) {
        retVal = 10 * retVal + num % 10;
        num /= 10;
    }
    return retVal;
}
int countNicePairs(int *nums, int numsSize) {
    int retVal = 0;

    /* nums[i] + rev(nums[j]) == nums[j] + rev(nums[i])
     * =>  nums[i] - rev(nums[i]) == nums[j] - rev(nums[j])
     */
    struct hashTable *pHashTable = NULL;
    struct hashTable *pTmp;
    int index;
    int i;
    for (i = 0; i < numsSize; ++i) {
        index = nums[i] - reverseInteger(nums[i]);

        pTmp = NULL;
        HASH_FIND_INT(pHashTable, &index, pTmp);
        if (pTmp == NULL) {
            pTmp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTmp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                return retVal;
            }
            pTmp->index = index;
            pTmp->count = 1;
            HASH_ADD_INT(pHashTable, index, pTmp);
        } else {
            retVal = (retVal + pTmp->count) % MODULO;
            pTmp->count++;
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
#define MODULO (int)(1e9 + 7)

   public:
    int reverseInteger(int num) {
        int retVal = 0;

        while (num > 0) {
            retVal = retVal * 10 + num % 10;
            num /= 10;
        }

        return retVal;
    }
    int countNicePairs(vector<int>& nums) {
        int retVal = 0;

        /* nums[i] + rev(nums[j]) == nums[j] + rev(nums[i])
         * =>  nums[i] - rev(nums[i]) == nums[j] - rev(nums[j])
         */
        unordered_map<int, int> hashTable;
        for (int num : nums) {
            int reverse = reverseInteger(num);

            retVal = (retVal + hashTable[num - reverse]) % MODULO;
            ++hashTable[num - reverse];
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

    def countNicePairs(self, nums: List[int]) -> int:
        retVal = 0

        # /* nums[i] + rev(nums[j]) == nums[j] + rev(nums[i])
        #  * =>  nums[i] - rev(nums[i]) == nums[j] - rev(nums[j])
        #  */
        hashTable = defaultdict(int)
        for num in nums:
            index = num - int(str(num)[::-1])
            retVal += hashTable[index]
            retVal %= self.MODULO
            hashTable[index] += 1

        return retVal
```

</details>

## [1832. Check if the Sentence Is Pangram](https://leetcode.com/problems/check-if-the-sentence-is-pangram/)  1166

- [Official](https://leetcode.com/problems/check-if-the-sentence-is-pangram/solutions/2616018/check-if-the-sentence-is-pangram/)

<details><summary>Description</summary>

```text
A pangram is a sentence where every letter of the English alphabet appears at least once.

Given a string sentence containing only lowercase English letters, return true if sentence is a pangram, or false otherwise.

Example 1:
Input: sentence = "thequickbrownfoxjumpsoverthelazydog"
Output: true
Explanation: sentence contains at least one of every letter of the English alphabet.

Example 2:
Input: sentence = "leetcode"
Output: false

Constraints:
1 <= sentence.length <= 1000
sentence consists of lowercase English letters.
```

</details>

<details><summary>C</summary>

```c
#define LOWERCASE_MIN_LENGTH (26)
#define LOWERCASE_HASH_TABLE (0x3ffffff)
bool checkIfPangram(char *sentence) {
    bool retVal = false;

    if (strlen(sentence) < LOWERCASE_MIN_LENGTH) {
        return retVal;
    }

    unsigned int record = 0;
    while (*sentence) {
        record |= (1 << (*(sentence) - 'a'));
        sentence++;
    }

    if (record == LOWERCASE_HASH_TABLE) {
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
    bool checkIfPangram(string sentence) {
        bool retVal = false;

        unordered_set<char> seen(sentence.begin(), sentence.end());
        if (seen.size() == 26) {
            retVal = true;
        }

        return retVal;
    }
};
```

</details>

## [1897. Redistribute Characters to Make All Strings Equal](https://leetcode.com/problems/redistribute-characters-to-make-all-strings-equal/)  1309

- [Official](https://leetcode.com/problems/redistribute-characters-to-make-all-strings-equal/editorial/)
- [Official](https://leetcode.cn/problems/redistribute-characters-to-make-all-strings-equal/solutions/826105/zhong-xin-fen-pei-zi-fu-shi-suo-you-zi-f-r29g/)

<details><summary>Description</summary>

```text
You are given an array of strings words (0-indexed).

In one operation, pick two distinct indices i and j, where words[i] is a non-empty string,
and move any character from words[i] to any position in words[j].

Return true if you can make every string in words equal using any number of operations, and false otherwise.

Example 1:
Input: words = ["abc","aabc","bc"]
Output: true
Explanation: Move the first 'a' in words[1] to the front of words[2],
to make words[1] = "abc" and words[2] = "abc".
All the strings are now equal to "abc", so return true.

Example 2:
Input: words = ["ab","a"]
Output: false
Explanation: It is impossible to make all the strings equal using the operation.

Constraints:
1 <= words.length <= 100
1 <= words[i].length <= 100
words[i] consists of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Characters are independent—only the frequency of characters matters.
2. It is possible to distribute characters if all characters can be divided equally among all strings.
```

</details>

</details>

<details><summary>C</summary>

```c
bool makeEqual(char** words, int wordsSize) {
    bool retVal = true;

// words[i] consists of lowercase English letters.
#define MAX_LETTERS (26)

    int hashTable[MAX_LETTERS];
    memset(hashTable, 0, sizeof(hashTable));

    int len, idx;
    int i, j;
    for (i = 0; i < wordsSize; ++i) {
        len = strlen(words[i]);
        for (j = 0; j < len; ++j) {
            idx = words[i][j] - 'a';
            hashTable[idx] += 1;
        }
    }

    for (i = 0; i < MAX_LETTERS; ++i) {
        if (hashTable[i] % wordsSize != 0) {
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
// words[i] consists of lowercase English letters.
#define MAX_LETTERS (26)
   public:
    bool makeEqual(vector<string>& words) {
        bool retVal = true;

        int wordsSize = words.size();

        vector<int> hashTable(MAX_LETTERS, 0);
        for (string word : words) {
            for (char c : word) {
                int idx = c - 'a';
                hashTable[idx] += 1;
            }
        }

        for (int value : hashTable) {
            if (value % wordsSize != 0) {
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
    def __init__(self) -> None:
        self.letters = 26   # words[i] consists of lowercase English letters.

    def makeEqual(self, words: List[str]) -> bool:
        retVal = True

        wordsSize = len(words)

        hashTable = [0] * self.letters
        for word in words:
            for c in word:
                idx = ord(c)-ord('a')
                hashTable[idx] += 1

        for value in hashTable:
            if value % wordsSize != 0:
                retVal = False
                break

        return retVal
```

</details>

## [1930. Unique Length-3 Palindromic Subsequences](https://leetcode.com/problems/unique-length-3-palindromic-subsequences/)  1533

- [Official](https://leetcode.com/problems/unique-length-3-palindromic-subsequences/editorial/)
- [Official](https://leetcode.cn/problems/unique-length-3-palindromic-subsequences/solutions/870024/chang-du-wei-3-de-bu-tong-hui-wen-zi-xu-21trj/)

<details><summary>Description</summary>

```text
Given a string s, return the number of unique palindromes of length three that are a subsequence of s.

Note that even if there are multiple ways to obtain the same subsequence, it is still only counted once.

A palindrome is a string that reads the same forwards and backwards.

A subsequence of a string is a new string generated from the original string with some characters (can be none)
deleted without changing the relative order of the remaining characters.
- For example, "ace" is a subsequence of "abcde".

Example 1:
Input: s = "aabca"
Output: 3
Explanation: The 3 palindromic subsequences of length 3 are:
- "aba" (subsequence of "aabca")
- "aaa" (subsequence of "aabca")
- "aca" (subsequence of "aabca")

Example 2:
Input: s = "adc"
Output: 0
Explanation: There are no palindromic subsequences of length 3 in "adc".

Example 3:
Input: s = "bbcbaba"
Output: 4
Explanation: The 4 palindromic subsequences of length 3 are:
- "bbb" (subsequence of "bbcbaba")
- "bcb" (subsequence of "bbcbaba")
- "bab" (subsequence of "bbcbaba")
- "aba" (subsequence of "bbcbaba")

Constraints:
3 <= s.length <= 10^5
s consists of only lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. What is the maximum number of length-3 palindromic strings?
2. How can we keep track of the characters that appeared to the left of a given position?
```

</details>

</details>

<details><summary>C</summary>

```c
#define LETTERS_SIZE (26)  // s consists of only lowercase English letters.
int countPalindromicSubsequence(char* s) {
    int retVal = 0;

    int sSize = strlen(s);
    int i, j;

    int left[LETTERS_SIZE];
    int right[LETTERS_SIZE];
    for (i = 0; i < LETTERS_SIZE; ++i) {
        left[i] = -1;
        right[i] = -1;
    }

    int idx;
    for (i = 0; i < sSize; ++i) {
        idx = s[i] - 'a';
        if (left[idx] == -1) {
            left[idx] = i;
        }
        right[idx] = i;
    }

    int betweenCount;
    int between[LETTERS_SIZE];
    for (i = 0; i < LETTERS_SIZE; ++i) {
        if (left[i] == -1) {
            continue;
        }

        betweenCount = 0;
        memset(between, 0, sizeof(between));
        for (j = left[i] + 1; j < right[i]; ++j) {
            idx = s[j] - 'a';
            if (between[idx] == 0) {
                between[idx]++;
                betweenCount++;
            }
        }
        retVal += betweenCount;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    int lettersSize = 26;  // s consists of only lowercase English letters.

   public:
    int countPalindromicSubsequence(string s) {
        int retVal = 0;

        int sSize = s.size();

        vector<int> left(lettersSize, -1);
        vector<int> right(lettersSize, -1);
        for (int i = 0; i < sSize; ++i) {
            int idx = s[i] - 'a';
            if (left[idx] == -1) {
                left[idx] = i;
            }
            right[idx] = i;
        }

        for (int i = 0; i < lettersSize; ++i) {
            if (left[i] == -1) {
                continue;
            }

            unordered_set<char> between;
            for (int j = left[i] + 1; j < right[i]; ++j) {
                between.insert(s[j]);
            }
            retVal += between.size();
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
        self.lettersSize = 26   # s consists of only lowercase English letters.

    def countPalindromicSubsequence(self, s: str) -> int:
        retVal = 0

        sSize = len(s)

        left = [-1] * self.lettersSize
        right = [-1] * self.lettersSize
        for i in range(sSize):
            idx = ord(s[i]) - ord('a')
            if left[idx] == -1:
                left[idx] = i
            right[idx] = i

        for i in range(self.lettersSize):
            if left[i] == -1:
                continue

            between = set()
            for j in range(left[i] + 1, right[i]):
                between.add(s[j])
            retVal += len(between)

        return retVal
```

</details>

## [2007. Find Original Array From Doubled Array](https://leetcode.com/problems/find-original-array-from-doubled-array/)  1557

<details><summary>Description</summary>

```text
An integer array original is transformed into a doubled array changed by appending twice the value of every element in original,
and then randomly shuffling the resulting array.

Given an array changed, return original if changed is a doubled array.
If changed is not a doubled array, return an empty array. The elements in original may be returned in any order.

Example 1:
Input: changed = [1,3,4,2,6,8]
Output: [1,3,4]
Explanation: One possible original array could be [1,3,4]:
- Twice the value of 1 is 1 * 2 = 2.
- Twice the value of 3 is 3 * 2 = 6.
- Twice the value of 4 is 4 * 2 = 8.
Other original arrays could be [4,3,1] or [3,1,4].

Example 2:
Input: changed = [6,3,0,1]
Output: []
Explanation: changed is not a doubled array.

Example 3:
Input: changed = [1]
Output: []
Explanation: changed is not a doubled array.

Constraints:
1 <= changed.length <= 10^5
0 <= changed[i] <= 10^5
```

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
int* findOriginalArray(int* changed, int changedSize, int* returnSize) {
    int* pRetVal = NULL;

    if (changedSize % 2 != 0) {
        *returnSize = 0;
        return pRetVal;
    }
    *returnSize = changedSize / 2;
    pRetVal = (int*)malloc(*returnSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        *returnSize = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, *returnSize * sizeof(int));
    // sort from large to small
    qsort(changed, changedSize, sizeof(int), compareInteger);

    // appending twice the value and hash function is one to one, so the Hash Table need double constraints size
#define MAX_RECORD (100000 * 2 + 4)
    int RECORD[MAX_RECORD] = {0};
    int idx = 0;
    int i;
    for (i = 0; i < changedSize; ++i) {
        if (RECORD[2 * changed[i]] == 0) {
            ++RECORD[changed[i]];
            continue;
        }
        pRetVal[idx++] = changed[i];
        --RECORD[2 * changed[i]];
    }

    for (i = 0; i < MAX_RECORD; ++i) {
        if (RECORD[i] != 0) {
            *returnSize = 0;
            free(pRetVal);
            pRetVal = NULL;
            break;
        }
    }

    return pRetVal;
}
```

</details>

## [2032. Two Out of Three](https://leetcode.com/problems/two-out-of-three/)  1269

- [Official](https://leetcode.cn/problems/two-out-of-three/solutions/2034884/zhi-shao-zai-liang-ge-shu-zu-zhong-chu-x-5131/)

<details><summary>Description</summary>

```text
Given three integer arrays nums1, nums2, and nums3,
return a distinct array containing all the values that are present in at least two out of the three arrays.
You may return the values in any order.

Example 1:
Input: nums1 = [1,1,3,2], nums2 = [2,3], nums3 = [3]
Output: [3,2]
Explanation: The values that are present in at least two arrays are:
- 3, in all three arrays.
- 2, in nums1 and nums2.

Example 2:
Input: nums1 = [3,1], nums2 = [2,3], nums3 = [1,2]
Output: [2,3,1]
Explanation: The values that are present in at least two arrays are:
- 2, in nums2 and nums3.
- 3, in nums1 and nums2.
- 1, in nums1 and nums3.

Example 3:
Input: nums1 = [1,2,2], nums2 = [4,3,3], nums3 = [5]
Output: []
Explanation: No value is present in at least two arrays.

Constraints:
1 <= nums1.length, nums2.length, nums3.length <= 100
1 <= nums1[i], nums2[j], nums3[k] <= 100
```

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoOutOfThree(int* nums1, int nums1Size, int* nums2, int nums2Size, int* nums3, int nums3Size, int* returnSize) {
    int* pRetVal = NULL;

// 1 <= nums1.length, nums2.length, nums3.length <= 100
#define MAX_HASH_TABLE_SIZE (100 + 4)
    int HashTable[MAX_HASH_TABLE_SIZE];
    memset(HashTable, 0, sizeof(HashTable));

    (*returnSize) = MAX_HASH_TABLE_SIZE;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));

    int i;
    for (i = 0; i < nums1Size; ++i) {
        HashTable[nums1[i]] |= (1 << 0);
    }
    for (i = 0; i < nums2Size; ++i) {
        HashTable[nums2[i]] |= (1 << 1);
    }
    for (i = 0; i < nums3Size; ++i) {
        HashTable[nums3[i]] |= (1 << 2);
    }

    (*returnSize) = 0;
    for (i = 0; i < MAX_HASH_TABLE_SIZE; ++i) {
        if (HashTable[i] & (HashTable[i] - 1)) {
            pRetVal[(*returnSize)] = i;
            ++(*returnSize);
        }
    }

    return pRetVal;
}
```

</details>

## [2131. Longest Palindrome by Concatenating Two Letter Words](https://leetcode.com/problems/longest-palindrome-by-concatenating-two-letter-words/)  1556

- [Official](https://leetcode.com/problems/longest-palindrome-by-concatenating-two-letter-words/solutions/2715749/longest-palindrome-by-concatenating-two-letter-words/)
- [Official](https://leetcode.cn/problems/longest-palindrome-by-concatenating-two-letter-words/solutions/1202034/lian-jie-liang-zi-mu-dan-ci-de-dao-de-zu-vs99/)

<details><summary>Description</summary>

```text
You are given an array of strings words. Each element of words consists of two lowercase English letters.

Create the longest possible palindrome by selecting some elements from words and concatenating them in any order.
Each element can be selected at most once.

Return the length of the longest palindrome that you can create. If it is impossible to create any palindrome, return 0.

A palindrome is a string that reads the same forward and backward.

Example 1:
Input: words = ["lc","cl","gg"]
Output: 6
Explanation: One longest palindrome is "lc" + "gg" + "cl" = "lcggcl", of length 6.
Note that "clgglc" is another longest palindrome that can be created.

Example 2:
Input: words = ["ab","ty","yt","lc","cl","ab"]
Output: 8
Explanation: One longest palindrome is "ty" + "lc" + "cl" + "yt" = "tylcclyt", of length 8.
Note that "lcyttycl" is another longest palindrome that can be created.

Example 3:
Input: words = ["cc","ll","xx"]
Output: 2
Explanation: One longest palindrome is "cc", of length 2.
Note that "ll" is another longest palindrome that can be created, and so is "xx".

Constraints:
1 <= words.length <= 10^5
words[i].length == 2
words[i] consists of lowercase English letters.
```

</details>

<details><summary>C</summary>

```c
#if 0   // Time Limit Exceeded
#define MAX_WORD_LENGTH     (4)
bool search(char** pRecord, int pRecordSize, char* pSearch)
{
    int i;
    for (i=0; i<pRecordSize; ++i)
    {
        // printf("%2d: %s; %s\n", i, pRecord[i], pSearch);
        if (strcmp(pRecord[i], pSearch) == 0)
        {
            memset(pRecord[i], 0, MAX_WORD_LENGTH*sizeof(char));
            return true;
        }
    }

    return false;
}
int longestPalindrome(char ** words, int wordsSize){
    int retVal = 0;

    int i, j;

    char** pRecord = (char**)malloc(wordsSize*sizeof(char*));
    if (pRecord == NULL)
    {
        perror("malloc");
        return retVal;
    }
    for (i=0; i<wordsSize; ++i)
    {
        pRecord[i] = (char*)malloc(MAX_WORD_LENGTH*sizeof(char));
        if (pRecord[i] == NULL)
        {
            perror("malloc");
            for (j=0; j<i; ++j)
            {
                free(pRecord[j]);
                pRecord[j] = NULL;
            }
            free(pRecord);
            pRecord = NULL;
            return retVal;
        }
        memset(pRecord[i], 0, MAX_WORD_LENGTH*sizeof(char));
    }

    bool isHit = false;
    for (i=0; i<wordsSize; ++i)
    {
        isHit = search(pRecord, i+1, words[i]);
        if (isHit == false)
        {
            pRecord[i][0] = words[i][1];
            pRecord[i][1] = words[i][0];
            continue;
        }
        retVal += 4;
    }
    for (i=0; i<wordsSize; ++i)
    {
        //printf("%2d: %s\n", i, pRecord[i]);
        if (strlen(pRecord[i]) == 0)
        {
            continue;
        }

        if (pRecord[i][0] == pRecord[i][1])
        {
            retVal += 2;
            break;
        }
    }

    for (i=0; i<wordsSize; ++i)
    {
        free(pRecord[i]);
        pRecord[i] = NULL;
    }
    free(pRecord);
    pRecord = NULL;

    return retVal;
}
#else
int longestPalindrome(char ** words, int wordsSize){
    int retVal = 0;

    // words[i] consists of lowercase English letters.
#define MAX_LETTERS     (26)
#define MAX_RECORD      (MAX_LETTERS*MAX_LETTERS)
    int RECORD[MAX_RECORD] = {0};

    int index;
    int i;
    for (i=0; i<wordsSize; ++i)
    {
        index = ((words[i][0]-'a') * MAX_LETTERS) + (words[i][1]-'a');
        if (RECORD[index] == 0)
        {
            index = ((words[i][1]-'a') * MAX_LETTERS) + (words[i][0]-'a');
            ++RECORD[index];
            continue;
        }
        retVal += 4;
        --RECORD[index];
    }

    for (i=0; i<MAX_LETTERS; ++i)
    {
        index = (i * MAX_LETTERS) + i;
        if (RECORD[index] != 0)
        {
            retVal += 2;
            break;
        }
    }

    return retVal;
}
#endif
```

</details>

<details><summary>C++</summary>

```c++
#define HASH_MAP                    (0)
#define TWO_DIMENSIONAL_ARRAY       (1)

class Solution {
public:
    int longestPalindrome(vector<string>& words) {
        int retVal = 0;

        bool central = false;

#if (HASH_MAP)
        cout << "A Hash Map Approach" << "\n";

        unordered_map<string, int> count;
        for (const string& word : words) {
            count[word]++;
        }

        for (const auto& [word, countOfTheWord] : count) {
            // if the word is a palindrome
            if (word[0] == word[1]) {
                if (countOfTheWord % 2 == 0) {
                    retVal += countOfTheWord;
                } else {
                    retVal += countOfTheWord - 1;
                    central = true;
                }
            // consider a pair of non-palindrome words such that one is the
            // reverse of another ({word[1], word[0]} is the reversed word)
            } else if (word[0] < word[1] && count.count({word[1], word[0]})) {
                retVal += 2 * min(countOfTheWord, count[{word[1], word[0]}]);
            }
        }
#elif (TWO_DIMENSIONAL_ARRAY)
        cout << "A Two-Dimensional Array Approach" << "\n";

        constexpr int alphabetSize = 26;
        vector count(alphabetSize, vector<int>(alphabetSize));
        for (const string& word : words) {
            count[word[0]-'a'][word[1]-'a']++;
        }

        for (int i=0; i<alphabetSize; ++i) {
            if (count[i][i] % 2 == 0) {
                retVal += count[i][i];
            } else {
                retVal += count[i][i] - 1;
                central = true;
            }
            for (int j=(i+1); j<alphabetSize; ++j) {
                retVal += (2 * min(count[i][j], count[j][i]));
            }
        }
#endif

        if (central) {
            retVal++;
        }
        retVal *= 2;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def __init__(self):
        self.method = 2

        if self.method == 1:
            print("A Hash Map Approach")
        elif self.method == 2:
            print("A Two-Dimensional Array Approach")
        print()

    def longestPalindrome(self, words: List[str]) -> int:
        retVal = 0

        central = False
        if self.method == 1:
            # a count variable contains the number of occurrences of each word
            count = Counter(words)

            for word, count_of_the_word in count.items():
                # if the word is a palindrome
                if word[0] == word[1]:
                    if count_of_the_word % 2 == 0:
                        retVal += count_of_the_word
                    else:
                        retVal += count_of_the_word - 1
                        central = True
                # consider a pair of non-palindrome words,
                # such that one is the reverse of another word[1] + word[0] is the reversed word
                elif word[0] < word[1]:
                    retVal += 2 * min(count_of_the_word,
                                      count[word[1] + word[0]])
        elif self.method == 2:
            alphabet_size = 26
            count = [[0 for j in range(alphabet_size)]
                     for i in range(alphabet_size)]

            for word in words:
                count[ord(word[0]) - ord('a')][ord(word[1]) - ord('a')] += 1

            for i in range(alphabet_size):
                if count[i][i] % 2 == 0:
                    retVal += count[i][i]
                else:
                    retVal += count[i][i] - 1
                    central = True
                for j in range(i + 1, alphabet_size):
                    retVal += 2 * min(count[i][j], count[j][i])

        if central:
            retVal += 1
        retVal = 2 * retVal

        return retVal
```

</details>

## [2133. Check if Every Row and Column Contains All Numbers](https://leetcode.com/problems/check-if-every-row-and-column-contains-all-numbers/)  1264

<details><summary>Description</summary>

```text
An n x n matrix is valid if every row and every column contains all the integers from 1 to n (inclusive).

Given an n x n integer matrix matrix, return true if the matrix is valid. Otherwise, return false.

Example 1:
Input: matrix = [[1,2,3],[3,1,2],[2,3,1]]
Output: true
Explanation: In this case, n = 3, and every row and column contains the numbers 1, 2, and 3.
Hence, we return true.

Example 2:
Input: matrix = [[1,1,1],[1,2,3],[1,2,3]]
Output: false
Explanation: In this case, n = 3, but the first row and the first column do not contain the numbers 2 or 3.
Hence, we return false.

Constraints:
n == matrix.length == matrix[i].length
1 <= n <= 100
1 <= matrix[i][j] <= n
```

</details>

<details><summary>C</summary>

```c
bool checkValid(int** matrix, int matrixSize, int* matrixColSize){
    bool retVal = false;

#define MAX_SIZE    (matrixSize)
    int HASHTABLE[MAX_SIZE];
    int idx;

    int i, j;

    // check every row
    for (i=0; i<matrixSize; ++i)
    {
        memset(HASHTABLE, 0, sizeof(HASHTABLE));
        for (j=0; j<matrixColSize[i]; ++j)
        {
            idx = matrix[i][j] - 1;
            if (HASHTABLE[idx] != 0)
            {
                return retVal;
            }
            ++HASHTABLE[idx];
        }
    }

    // check every column
    for (j=0; j<matrixColSize[0]; ++j)
    {
        memset(HASHTABLE, 0, sizeof(HASHTABLE));
        for (i=0; i<matrixSize; ++i)
        {
            idx = matrix[i][j] - 1;
            if (HASHTABLE[idx] != 0)
            {
                return retVal;
            }
            ++HASHTABLE[idx];
        }
    }

    retVal = true;

    return retVal;
}
```

</details>

## [2154. Keep Multiplying Found Values by Two](https://leetcode.com/problems/keep-multiplying-found-values-by-two/)  1235

<details><summary>Description</summary>

```text
You are given an array of integers nums.
You are also given an integer original which is the first number that needs to be searched for in nums.

You then do the following steps:
1. If original is found in nums, multiply it by two (i.e., set original = 2 * original).
2. Otherwise, stop the process.
3. Repeat this process with the new number as long as you keep finding the number.
Return the final value of original.

Example 1:
Input: nums = [5,3,6,1,12], original = 3
Output: 24
Explanation:
- 3 is found in nums. 3 is multiplied by 2 to obtain 6.
- 6 is found in nums. 6 is multiplied by 2 to obtain 12.
- 12 is found in nums. 12 is multiplied by 2 to obtain 24.
- 24 is not found in nums. Thus, 24 is returned.

Example 2:
Input: nums = [2,7,9], original = 4
Output: 4
Explanation:
- 4 is not found in nums. Thus, 4 is returned.

Constraints:
1 <= nums.length <= 1000
1 <= nums[i], original <= 1000
```

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int findFinalValue(int* nums, int numsSize, int original) {
    int retVal = original;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] == retVal) {
            retVal *= 2;
        }
    }

    return retVal;
}
```

</details>

## [2215. Find the Difference of Two Arrays](https://leetcode.com/problems/find-the-difference-of-two-arrays/)  1207

- [Official](https://leetcode.com/problems/find-the-difference-of-two-arrays/editorial/)
- [Official](https://leetcode.cn/problems/find-the-difference-of-two-arrays/solutions/1379222/zhao-chu-liang-shu-zu-de-bu-tong-by-leet-78u0/)

<details><summary>Description</summary>

```text
Given two 0-indexed integer arrays nums1 and nums2, return a list answer of size 2 where:
- answer[0] is a list of all distinct integers in nums1 which are not present in nums2.
- answer[1] is a list of all distinct integers in nums2 which are not present in nums1.
Note that the integers in the lists may be returned in any order.

Example 1:
Input: nums1 = [1,2,3], nums2 = [2,4,6]
Output: [[1,3],[4,6]]
Explanation:
For nums1, nums1[1] = 2 is present at index 0 of nums2, whereas nums1[0] = 1 and nums1[2] = 3 are not present in nums2.
Therefore, answer[0] = [1,3].
For nums2, nums2[0] = 2 is present at index 1 of nums1, whereas nums2[1] = 4 and nums2[2] = 6 are not present in nums2.
Therefore, answer[1] = [4,6].

Example 2:
Input: nums1 = [1,2,3,3], nums2 = [1,1,2,2]
Output: [[3],[]]
Explanation:
For nums1, nums1[2] and nums1[3] are not present in nums2. Since nums1[2] == nums1[3],
their value is only included once and answer[0] = [3].
Every integer in nums2 is present in nums1. Therefore, answer[1] = [].

Constraints:
1 <= nums1.length, nums2.length <= 1000
-1000 <= nums1[i], nums2[i] <= 1000
```

<details><summary>Hint</summary>

```text
1. For each integer in nums1, check if it exists in nums2.
2. Do the same for each integer in nums2.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** findDifference(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 2;
    //
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        (*returnSize) = 0;
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, ((*returnSize) * sizeof(int)));
    //
    pRetVal = (int**)malloc((*returnSize) * sizeof(int*));
    if (pRetVal == NULL) {
        (*returnSize) = 0;
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }
    pRetVal[0] = (int*)malloc(nums1Size * sizeof(int));
    if (pRetVal[0] == NULL) {
        (*returnSize) = 0;
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset(pRetVal[0], 0, (nums1Size * sizeof(int)));
    pRetVal[1] = (int*)malloc(nums2Size * sizeof(int));
    if (pRetVal[1] == NULL) {
        (*returnSize) = 0;
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        free(pRetVal[0]);
        pRetVal[0] = NULL;
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset(pRetVal[1], 0, (nums2Size * sizeof(int)));

// -1000 <= nums1[i], nums2[i] <= 1000
#define SHIFT_HASHTABLE_IDX (1000)
#define MAX_HASHTABLE_SIZE ((SHIFT_HASHTABLE_IDX) + 1 + (SHIFT_HASHTABLE_IDX))
    int i;

    //
    int hashTable1[MAX_HASHTABLE_SIZE];
    memset(hashTable1, 0, sizeof(hashTable1));
    for (i = 0; i < nums1Size; ++i) {
        hashTable1[nums1[i] + SHIFT_HASHTABLE_IDX] = 1;
    }
    int hashTable2[MAX_HASHTABLE_SIZE];
    memset(hashTable2, 0, sizeof(hashTable2));
    for (i = 0; i < nums2Size; ++i) {
        hashTable2[nums2[i] + SHIFT_HASHTABLE_IDX] = 1;
    }

    //
    for (i = 0; i < nums1Size; ++i) {
        if (hashTable2[nums1[i] + SHIFT_HASHTABLE_IDX] == 0) {
            pRetVal[0][((*returnColumnSizes)[0])++] = nums1[i];
            hashTable2[nums1[i] + SHIFT_HASHTABLE_IDX] = 1;
        }
    }
    for (i = 0; i < nums2Size; ++i) {
        if (hashTable1[nums2[i] + SHIFT_HASHTABLE_IDX] == 0) {
            pRetVal[1][((*returnColumnSizes)[1])++] = nums2[i];
            hashTable1[nums2[i] + SHIFT_HASHTABLE_IDX] = 1;
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
    vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2) {
        vector<vector<int>> retVal(2);

        set<int> hashSet1(begin(nums1), end(nums1));
        set<int> hashSet2(begin(nums2), end(nums2));
        set_difference(hashSet1.begin(), hashSet1.end(), hashSet2.begin(), hashSet2.end(), back_inserter(retVal[0]));
        set_difference(hashSet2.begin(), hashSet2.end(), hashSet1.begin(), hashSet1.end(), back_inserter(retVal[1]));

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def findDifference(self, nums1: List[int], nums2: List[int]) -> List[List[int]]:
        retVal = [[], []]

        hashTable1 = set(nums1)
        hashTable2 = set(nums2)
        retVal = [list(hashTable1-hashTable2), list(hashTable2-hashTable1)]

        return retVal
```

</details>

## [2225. Find Players With Zero or One Losses](https://leetcode.com/problems/find-players-with-zero-or-one-losses/)  1316

- [Official](https://leetcode.cn/problems/find-players-with-zero-or-one-losses/solutions/1418074/zhao-chu-shu-diao-ling-chang-huo-yi-chan-fpsj/)

<details><summary>Description</summary>

```text
You are given an integer array matches where matches[i] = [winneri, loseri]
indicates that the player winneri defeated player loseri in a match.

Return a list answer of size 2 where:
- answer[0] is a list of all players that have not lost any matches.
- answer[1] is a list of all players that have lost exactly one match.
The values in the two lists should be returned in increasing order.

Note:
- You should only consider the players that have played at least one match.
- The testcases will be generated such that no two matches will have the same outcome.

Example 1:
Input: matches = [[1,3],[2,3],[3,6],[5,6],[5,7],[4,5],[4,8],[4,9],[10,4],[10,9]]
Output: [[1,2,10],[4,5,7,8]]
Explanation:
Players 1, 2, and 10 have not lost any matches.
Players 4, 5, 7, and 8 each have lost one match.
Players 3, 6, and 9 each have lost two matches.
Thus, answer[0] = [1,2,10] and answer[1] = [4,5,7,8].

Example 2:
Input: matches = [[2,3],[1,3],[5,4],[6,4]]
Output: [[1,2,5,6],[]]
Explanation:
Players 1, 2, 5, and 6 have not lost any matches.
Players 3 and 4 each have lost two matches.
Thus, answer[0] = [1,2,5,6] and answer[1] = [].

Constraints:
1 <= matches.length <= 10^5
matches[i].length == 2
1 <= winneri, loseri <= 10^5
winneri != loseri
All matches[i] are unique.
```

<details><summary>Hint</summary>

```text
1. Count the number of times a player loses while iterating through the matches.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
struct hashStruct {
    int id;
    int win;
    int lose;
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
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** findWinners(int** matches, int matchesSize, int* matchesColSize, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 2;
    int i, j;

    // malloc return value
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, ((*returnSize) * sizeof(int)));
    pRetVal = (int**)malloc((*returnSize) * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        (*returnSize) = 0;
        return pRetVal;
    }
    for (i = 0; i < (*returnSize); ++i) {
        pRetVal[i] = (int*)malloc(matchesSize * sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        memset(pRetVal[i], 0, (matchesSize * sizeof(int)));
    }

    // record win and lose
    struct hashStruct* pMap = NULL;
    struct hashStruct* pTmp;
    for (i = 0; i < matchesSize; ++i) {
        // win
        pTmp = NULL;
        HASH_FIND_INT(pMap, &matches[i][0], pTmp);
        if (pTmp == NULL) {
            pTmp = (struct hashStruct*)malloc(sizeof(struct hashStruct));
            if (pTmp == NULL) {
                perror("malloc");
                freeAll(pMap);
                return pRetVal;
            }
            pTmp->id = matches[i][0];
            pTmp->win = 1;
            pTmp->lose = 0;
            HASH_ADD_INT(pMap, id, pTmp);
        } else {
            pTmp->win++;
        }

        // lose
        pTmp = NULL;
        HASH_FIND_INT(pMap, &matches[i][1], pTmp);
        if (pTmp == NULL) {
            pTmp = (struct hashStruct*)malloc(sizeof(struct hashStruct));
            if (pTmp == NULL) {
                perror("malloc");
                freeAll(pMap);
                return pRetVal;
            }
            pTmp->id = matches[i][1];
            pTmp->win = 0;
            pTmp->lose = 1;
            HASH_ADD_INT(pMap, id, pTmp);
        } else {
            pTmp->lose++;
        }
    }

    // answer[0] is a list of all players that have not lost any matches.
    // answer[1] is a list of all players that have lost exactly one match.
    (*returnColumnSizes)[0] = 0;
    (*returnColumnSizes)[1] = 0;
    pTmp = NULL;
    for (pTmp = pMap; pTmp != NULL; pTmp = pTmp->hh.next) {
        // printf("[%d](%d, %d)\n", pTmp->id, pTmp->win, pTmp->lose);

        if (pTmp->lose == 0) {
            pRetVal[0][(*returnColumnSizes)[0]] = pTmp->id;
            (*returnColumnSizes)[0]++;
        } else if (pTmp->lose == 1) {
            pRetVal[1][(*returnColumnSizes)[1]] = pTmp->id;
            (*returnColumnSizes)[1]++;
        }
    }
    freeAll(pMap);

    // The values in the two lists should be returned in increasing order.
    qsort(pRetVal[0], (*returnColumnSizes)[0], sizeof(int), compareInteger);
    qsort(pRetVal[1], (*returnColumnSizes)[1], sizeof(int), compareInteger);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<vector<int>> findWinners(vector<vector<int>>& matches) {
        vector<vector<int>> retVal;

        unordered_map<int, int> lostHashTable;
        for (auto& match : matches) {
            int win = match[0];
            int lost = match[1];
            auto iterator = lostHashTable.find(win);
            if (iterator == lostHashTable.end()) {
                lostHashTable[win] = 0;
            }
            lostHashTable[lost]++;
        }

        vector<int> notLost;
        vector<int> lostExactlyOne;
        for (auto& iterator : lostHashTable) {
            if (iterator.second == 0) {
                notLost.emplace_back(iterator.first);
            } else if (iterator.second == 1) {
                lostExactlyOne.emplace_back(iterator.first);
            }
        }
        sort(notLost.begin(), notLost.end());
        sort(lostExactlyOne.begin(), lostExactlyOne.end());
        retVal.emplace_back(notLost);
        retVal.emplace_back(lostExactlyOne);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def findWinners(self, matches: List[List[int]]) -> List[List[int]]:
        retVal = []

        winHashTable = defaultdict(int)
        lostHashTable = defaultdict(int)
        for win, lost in matches:
            winHashTable[win] += 1
            lostHashTable[lost] += 1

        lostExactlyOne = []
        for i in lostHashTable:
            if lostHashTable[i] == 1:
                lostExactlyOne.append(i)
        lostExactlyOne.sort()

        notLost = []
        for i in winHashTable:
            if i not in lostHashTable:
                notLost.append(i)
        notLost.sort()

        retVal = [notLost, lostExactlyOne]

        return retVal
```

</details>

## [2283. Check if Number Has Equal Digit Count and Digit Value](https://leetcode.com/problems/check-if-number-has-equal-digit-count-and-digit-value/)  1253

- [Official](https://leetcode.cn/problems/check-if-number-has-equal-digit-count-and-digit-value/solutions/2054497/pan-duan-yi-ge-shu-de-shu-zi-ji-shu-shi-ozwa7/)

<details><summary>Description</summary>

```text
You are given a 0-indexed string num of length n consisting of digits.

Return true if for every index i in the range 0 <= i < n, the digit i occurs num[i] times in num, otherwise return false.

Example 1:
Input: num = "1210"
Output: true
Explanation:
num[0] = '1'. The digit 0 occurs once in num.
num[1] = '2'. The digit 1 occurs twice in num.
num[2] = '1'. The digit 2 occurs once in num.
num[3] = '0'. The digit 3 occurs zero times in num.
The condition holds true for every index in "1210", so return true.

Example 2:
Input: num = "030"
Output: false
Explanation:
num[0] = '0'. The digit 0 should occur zero times, but actually occurs twice in num.
num[1] = '3'. The digit 1 should occur three times, but actually occurs zero times in num.
num[2] = '0'. The digit 2 occurs zero times in num.
The indices 0 and 1 both violate the condition, so return false.

Constraints:
n == num.length
1 <= n <= 10
num consists of digits.
```

</details>

<details><summary>C</summary>

```c
bool digitCount(char* num) {
    bool retVal = false;

#define MAX_HASH_TABLE (10 + 1)
    char HashTable[MAX_HASH_TABLE];
    memset(HashTable, '0', sizeof(HashTable));
    HashTable[sizeof(HashTable) - 1] = 0;

    int len = strlen(num);
    int i;
    for (i = 0; i < len; ++i) {
        ++HashTable[num[i] - '0'];
    }

    if (strncmp(HashTable, num, len) == 0) {
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
    bool digitCount(string num) {
        bool retVal = false;

        int len = num.length();

#if (1)
        unordered_map<int, int> hashTable;

        for (int i = 0; i < len; ++i) {
            ++hashTable[num[i] - '0'];
        }

        for (int i = 0; i < len; i++) {
            if (hashTable[i] != num[i] - '0') {
                return retVal;
            }
        }
        retVal = true;
#else
#define MAX_HASH_TABLE (10 + 1)
        vector<char> hashTable(MAX_HASH_TABLE, '0');

        for (int i = 0; i < len; ++i) {
            ++hashTable[num[i] - '0'];
        }

        string hashTableString(hashTable.begin(), hashTable.end());
        if ((hashTableString.compare(0, len, num)) == 0) {
            retVal = true;
        }
#endif

        return retVal;
    }
};
```

</details>

## [2287. Rearrange Characters to Make Target String](https://leetcode.com/problems/rearrange-characters-to-make-target-string/)  1299

- [Official](https://leetcode.cn/problems/rearrange-characters-to-make-target-string/solutions/2058193/zhong-pai-zi-fu-xing-cheng-mu-biao-zi-fu-v5te/)

<details><summary>Description</summary>

```text
You are given two 0-indexed strings s and target. You can take some letters from s and rearrange them to form new strings.

Return the maximum number of copies of target that can be formed by taking letters from s and rearranging them.

Example 1:
Input: s = "ilovecodingonleetcode", target = "code"
Output: 2
Explanation:
For the first copy of "code", take the letters at indices 4, 5, 6, and 7.
For the second copy of "code", take the letters at indices 17, 18, 19, and 20.
The strings that are formed are "ecod" and "code" which can both be rearranged into "code".
We can make at most two copies of "code", so we return 2.

Example 2:
Input: s = "abcba", target = "abc"
Output: 1
Explanation:
We can make one copy of "abc" by taking the letters at indices 0, 1, and 2.
We can make at most one copy of "abc", so we return 1.
Note that while there is an extra 'a' and 'b' at indices 3 and 4, we cannot reuse the letter 'c' at index 2,
so we cannot make a second copy of "abc".

Example 3:
Input: s = "abbaccaddaeea", target = "aaaaa"
Output: 1
Explanation:
We can make one copy of "aaaaa" by taking the letters at indices 0, 3, 6, 9, and 12.
We can make at most one copy of "aaaaa", so we return 1.

Constraints:
1 <= s.length <= 100
1 <= target.length <= 10
s and target consist of lowercase English letters.
```

</details>

<details><summary>C</summary>

```c
int rearrangeCharacters(char* s, char* target) {
    int retVal = 0;

    // s and target consist of lowercase English letters.
#define MAX_HASH_TABLE_SIZE (26)
    int HashTable[MAX_HASH_TABLE_SIZE][2];
    memset(HashTable, 0, sizeof(HashTable));

    int i;
    int sLen = strlen(s);
    for (i = 0; i < sLen; ++i) {
        ++HashTable[s[i] - 'a'][0];
    }
    int targetLen = strlen(target);
    for (i = 0; i < targetLen; ++i) {
        ++HashTable[target[i] - 'a'][1];
    }

    retVal = fmax(sLen, targetLen);
    for (i = 0; i < MAX_HASH_TABLE_SIZE; ++i) {
        if (HashTable[i][1] == 0) {
            continue;
        }

        retVal = fmin(retVal, (HashTable[i][0] / HashTable[i][1]));
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int rearrangeCharacters(string s, string target) {
        int retVal = 0;

        unordered_map<char, int> sHashTable;
        for (char c : s) {
            ++sHashTable[c];
        }

        unordered_map<char, int> targetHashTable;
        for (char c : target) {
            ++targetHashTable[c];
        }

        retVal = max(s.length(), target.length());
        for (auto [key, value] : targetHashTable) {
            retVal = min(retVal, (sHashTable[key] / targetHashTable[key]));
        }

        return retVal;
    }
};
```

</details>

## [2309. Greatest English Letter in Upper and Lower Case](https://leetcode.com/problems/greatest-english-letter-in-upper-and-lower-case/)  1242

- [Official](https://leetcode.cn/problems/greatest-english-letter-in-upper-and-lower-case/solutions/2076006/jian-ju-da-xiao-xie-de-zui-hao-ying-wen-o5u2s/)

<details><summary>Description</summary>

```text
Given a string of English letters s,
return the greatest English letter which occurs as both a lowercase and uppercase letter in s.
The returned letter should be in uppercase. If no such letter exists, return an empty string.

An English letter b is greater than another letter a if b appears after a in the English alphabet.

Example 1:
Input: s = "lEeTcOdE"
Output: "E"
Explanation:
The letter 'E' is the only letter to appear in both lower and upper case.

Example 2:
Input: s = "arRAzFif"
Output: "R"
Explanation:
The letter 'R' is the greatest letter to appear in both lower and upper case.
Note that 'A' and 'F' also appear in both lower and upper case, but 'R' is greater than 'F' or 'A'.

Example 3:
Input: s = "AbCdEfGhIjK"
Output: ""
Explanation:
There is no letter that appears in both lower and upper case.

Constraints:
1 <= s.length <= 1000
s consists of lowercase and uppercase English letters.
```

</details>

<details><summary>C</summary>

```c
char* greatestLetter(char* s) {
    char* pRetVal = NULL;

    pRetVal = (char*)malloc(2 * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (2 * sizeof(char)));

// s consists of lowercase and uppercase English letters.
#define SHIFT_LOWERCASE (0)
#define SHIFT_UPPERCASE (1)
#define MAX_HASHTABLE (26)
    int HashTable[MAX_HASHTABLE];
    memset(HashTable, 0, sizeof(HashTable));

    int len = strlen(s);
    int i;
    for (i = 0; i < len; ++i) {
        if ((s[i] >= 'A') && (s[i] <= 'Z')) {
            HashTable[s[i] - 'A'] |= (1 << SHIFT_UPPERCASE);
        } else if ((s[i] >= 'a') && (s[i] <= 'z')) {
            HashTable[s[i] - 'a'] |= (1 << SHIFT_LOWERCASE);
        }
    }

    for (i = (MAX_HASHTABLE - 1); i >= 0; --i) {
        if (HashTable[i] == ((1 << SHIFT_LOWERCASE) | (1 << SHIFT_UPPERCASE))) {
            snprintf(pRetVal, (2 * sizeof(char)), "%c", i + 'A');
            break;
        }
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
// s consists of lowercase and uppercase English letters.
#define MAX_HASHTABLE (26)

   public:
    string greatestLetter(string s) {
        string retVal;

        unordered_set<char> hashTable(s.begin(), s.end());
        for (int i = (MAX_HASHTABLE - 1); i >= 0; --i) {
            if ((hashTable.count('a' + i) > 0) && (hashTable.count('A' + i) > 0)) {
                retVal = string(1, 'A' + i);
                break;
            }
        }

        return retVal;
    }
};
```

</details>

## [2325. Decode the Message](https://leetcode.com/problems/decode-the-message/)  1268

- [Official](https://leetcode.cn/problems/decode-the-message/solutions/2084137/jie-mi-xiao-xi-by-leetcode-solution-wckx)

<details><summary>Description</summary>

```text
You are given the strings key and message, which represent a cipher key and a secret message, respectively.
The steps to decode message are as follows:

Use the first appearance of all 26 lowercase English letters in key as the order of the substitution table.
Align the substitution table with the regular English alphabet.
Each letter in message is then substituted using the table.
Spaces ' ' are transformed to themselves.
- For example, given key = "happy boy" (actual key would have at least one instance of each letter in the alphabet),
we have the partial substitution table of ('h' -> 'a', 'a' -> 'b', 'p' -> 'c', 'y' -> 'd', 'b' -> 'e', 'o' -> 'f').
Return the decoded message.

Example 1:
Input: key = "the quick brown fox jumps over the lazy dog", message = "vkbs bs t suepuv"
Output: "this is a secret"
Explanation: The diagram above shows the substitution table.
It is obtained by taking the first appearance of each letter in "the quick brown fox jumps over the lazy dog".

Example 2:
Input: key = "eljuxhpwnyrdgtqkviszcfmabo", message = "zwx hnfx lqantp mnoeius ycgk vcnjrdb"
Output: "the five boxing wizards jump quickly"
Explanation: The diagram above shows the substitution table.
It is obtained by taking the first appearance of each letter in "eljuxhpwnyrdgtqkviszcfmabo".

Constraints:
26 <= key.length <= 2000
key consists of lowercase English letters and ' '.
key contains every letter in the English alphabet ('a' to 'z') at least once.
1 <= message.length <= 2000
message consists of lowercase English letters and ' '.
```

</details>

<details><summary>C</summary>

```c
char* decodeMessage(char* key, char* message) {
    char* pRetVal = NULL;

    int messageLen = strlen(message);
    pRetVal = (char*)malloc((messageLen + 1) * sizeof(char));
    if (pRetVal == NULL) {
        perror("mmalloc");
        return pRetVal;
    }
    memset(pRetVal, 0, ((messageLen + 1) * sizeof(char)));

// key consists of lowercase English letters and ' '.
#define MAX_HASHTABLE (26)
    char HashTable[MAX_HASHTABLE];
    memset(HashTable, 0, sizeof(HashTable));
    int keyLen = strlen(key);
    int index = 0;
    int HashTableUse = 0;
    int i;
    for (i = 0; i < keyLen; ++i) {
        if (key[i] == ' ') {
            continue;
        }

        if (HashTableUse == MAX_HASHTABLE) {
            break;
        }

        index = key[i] - 'a';
        if (HashTable[index] == 0) {
            HashTable[index] = HashTableUse + 'a';
            ++HashTableUse;
        }
    }

    for (i = 0; i < messageLen; ++i) {
        if (message[i] == ' ') {
            pRetVal[i] = ' ';
            continue;
        }

        index = message[i] - 'a';
        pRetVal[i] = HashTable[index];
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
// key consists of lowercase English letters and ' '.
#define MAX_HASHTABLE (26)
   public:
    string decodeMessage(string key, string message) {
        string pRetVal;

        int HashTableUse = 0;
        vector<char> HashTable(MAX_HASHTABLE, 0);
        for (auto c : key) {
            if (c == ' ') {
                continue;
            }

            if (HashTableUse == MAX_HASHTABLE) {
                break;
            }

            int index = c - 'a';
            if (HashTable[index] == 0) {
                HashTable[index] = HashTableUse + 'a';
                ++HashTableUse;
            }
        }

        for (auto c : message) {
            if (c == ' ') {
                pRetVal.append(1, ' ');
                continue;
            }

            int index = c - 'a';
            pRetVal.append(1, HashTable[index]);
        }

        return pRetVal;
    }
};
```

</details>

<details><summary>Rust</summary>

```rust
use std::collections::HashMap;
impl Solution {
    pub fn decode_message(key: String, message: String) -> String {
        let mut ret_val = String::new();

        let mut hash_map = HashMap::new();
        let mut hash_map_use = 0;
        for c in key.chars() {
            if hash_map_use == 26 {
                break;
            }

            if c == ' ' || hash_map.contains_key(&c) == true {
                continue;
            }

            hash_map.insert(c, (b'a' + hash_map_use) as char);
            hash_map_use += 1;
        }

        for c in message.chars() {
            if c == ' ' {
                ret_val.push(c);
                continue;
            }

            if hash_map.contains_key(&c) {
                ret_val.push(hash_map[&c]);
            }
        }

        return ret_val;
    }
}
```

</details>

## [2353. Design a Food Rating System](https://leetcode.com/problems/design-a-food-rating-system/)  1781

- [Official](https://leetcode.com/problems/design-a-food-rating-system/editorial/)

<details><summary>Description</summary>

```text
Design a food rating system that can do the following:
- Modify the rating of a food item listed in the system.
- Return the highest-rated food item for a type of cuisine in the system.

Implement the FoodRatings class:
- FoodRatings(String[] foods, String[] cuisines, int[] ratings)
  Initializes the system. The food items are described by foods, cuisines and ratings, all of which have a length of n.
  - foods[i] is the name of the ith food,
  - cuisines[i] is the type of cuisine of the ith food, and
  - ratings[i] is the initial rating of the ith food.
- void changeRating(String food, int newRating)
  Changes the rating of the food item with the name food.
- String highestRated(String cuisine)
  Returns the name of the food item that has the highest rating for the given type of cuisine.
  If there is a tie, return the item with the lexicographically smaller name.

Note that a string x is lexicographically smaller than string y if x comes before y in dictionary order,
that is, either x is a prefix of y, or if i is the first position such that x[i] != y[i],
then x[i] comes before y[i] in alphabetic order.

Example 1:
Input
["FoodRatings", "highestRated", "highestRated", "changeRating", "highestRated", "changeRating", "highestRated"]
[[["kimchi", "miso", "sushi", "moussaka", "ramen", "bulgogi"],
["korean", "japanese", "japanese", "greek", "japanese", "korean"], [9, 12, 8, 15, 14, 7]],
["korean"], ["japanese"], ["sushi", 16], ["japanese"], ["ramen", 16], ["japanese"]]
Output
[null, "kimchi", "ramen", null, "sushi", null, "ramen"]
Explanation
FoodRatings foodRatings = new FoodRatings(["kimchi", "miso", "sushi", "moussaka", "ramen", "bulgogi"],
["korean", "japanese", "japanese", "greek", "japanese", "korean"], [9, 12, 8, 15, 14, 7]);
foodRatings.highestRated("korean"); // return "kimchi"
                                    // "kimchi" is the highest rated korean food with a rating of 9.
foodRatings.highestRated("japanese"); // return "ramen"
                                      // "ramen" is the highest rated japanese food with a rating of 14.
foodRatings.changeRating("sushi", 16); // "sushi" now has a rating of 16.
foodRatings.highestRated("japanese"); // return "sushi"
                                      // "sushi" is the highest rated japanese food with a rating of 16.
foodRatings.changeRating("ramen", 16); // "ramen" now has a rating of 16.
foodRatings.highestRated("japanese"); // return "ramen"
                                      // Both "sushi" and "ramen" have a rating of 16.
                                      // However, "ramen" is lexicographically smaller than "sushi".

Constraints:
1 <= n <= 2 * 10^4
n == foods.length == cuisines.length == ratings.length
1 <= foods[i].length, cuisines[i].length <= 10
foods[i], cuisines[i] consist of lowercase English letters.
1 <= ratings[i] <= 10^8
All the strings in foods are distinct.
food will be the name of a food item in the system across all calls to changeRating.
cuisine will be a type of cuisine of at least one food item in the system across all calls to highestRated.
At most 2 * 104 calls in total will be made to changeRating and highestRated.
```

<details><summary>Hint</summary>

```text
1. The key to solving this problem is to properly store the data using the right data structures.
2. Firstly, a hash table is needed to efficiently map each food item to its cuisine and current rating.
3. In addition, another hash table is needed to map cuisines to foods within each cuisine
   stored in an ordered set according to their ratings.
```

</details>

</details>

<details><summary>C</summary>

```c
typedef struct {
} FoodRatings;
FoodRatings* foodRatingsCreate(char** foods, int foodsSize, char** cuisines, int cuisinesSize, int* ratings,
                               int ratingsSize) {}
void foodRatingsChangeRating(FoodRatings* obj, char* food, int newRating) {}
char* foodRatingsHighestRated(FoodRatings* obj, char* cuisine) {}
void foodRatingsFree(FoodRatings* obj) {}
/**
 * Your FoodRatings struct will be instantiated and called as such:
 * FoodRatings* obj = foodRatingsCreate(foods, foodsSize, cuisines, cuisinesSize, ratings, ratingsSize);
 * foodRatingsChangeRating(obj, food, newRating);
 * char* param_2 = foodRatingsHighestRated(obj, cuisine);
 * foodRatingsFree(obj);
 */
```

</details>

<details><summary>C++</summary>

```c++
class Food {
   public:
    int foodRating;   // Store the food's rating.
    string foodName;  // Store the food's name.

    Food(int foodRating, string foodName) {
        this->foodRating = foodRating;
        this->foodName = foodName;
    }
    // Overload the less than operator for comparison
    bool operator<(const Food& other) const {
        // If food ratings are same sort on the basis of their name. (lexographically smaller name food will be on top)
        if (foodRating == other.foodRating) {
            return foodName > other.foodName;
        }
        // Sort on the basis of food rating. (bigger rating food will be on top)
        return foodRating < other.foodRating;
    }
};
class FoodRatings {
    unordered_map<string, int> foodRatingMap;      // Map food with its rating.
    unordered_map<string, string> foodCuisineMap;  // Map food with cuisine it belongs to.
    // Store all food of a cusine in priority queue (to sort them on ratings/name)
    // Priority queue element -> Food: (foodRating, foodName)
    unordered_map<string, priority_queue<Food>> cuisineFoodMap;

   public:
    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        int foodsSize = foods.size();
        for (int i = 0; i < foodsSize; ++i) {
            // Store 'rating' and 'cuisine' of current 'food' in 'foodRatingMap' and 'foodCuisineMap' maps.
            foodRatingMap[foods[i]] = ratings[i];
            foodCuisineMap[foods[i]] = cuisines[i];
            // Insert the '(rating, name)' element in current cuisine's priority queue.
            cuisineFoodMap[cuisines[i]].push(Food(ratings[i], foods[i]));
        }
    }
    void changeRating(string food, int newRating) {
        // Update food's rating in 'foodRating' map.
        foodRatingMap[food] = newRating;
        // Insert the '(new rating, name)' element in respective cuisine's priority queue.
        auto cuisineName = foodCuisineMap[food];
        cuisineFoodMap[cuisineName].push(Food(newRating, food));
    }
    string highestRated(string cuisine) {
        // Get the highest rated 'food' of 'cuisine'.
        auto highestRated = cuisineFoodMap[cuisine].top();

        // If latest rating of 'food' doesn't match with 'rating' on which it was sorted in priority queue,
        // then we discard this element of the priority queue.
        while (foodRatingMap[highestRated.foodName] != highestRated.foodRating) {
            cuisineFoodMap[cuisine].pop();
            highestRated = cuisineFoodMap[cuisine].top();
        }
        // Return name of the highest rated 'food' of 'cuisine'.
        return highestRated.foodName;
    }
};
/**
 * Your FoodRatings object will be instantiated and called as such:
 * FoodRatings* obj = new FoodRatings(foods, cuisines, ratings);
 * obj->changeRating(food,newRating);
 * string param_2 = obj->highestRated(cuisine);
 */
```

</details>

<details><summary>Python3</summary>

```python
class Food:
    def __init__(self, food_rating, food_name):
        # Store the food's rating.
        self.food_rating = food_rating
        # Store the food's name.
        self.food_name = food_name

    def __lt__(self, other):
        # Overload the less than operator for comparison.
        # If food ratings are the same, sort based on their name (lexicographically smaller name food will be on top).
        if self.food_rating == other.food_rating:
            return self.food_name < other.food_name
        # Sort based on food rating (bigger rating food will be on top).
        return self.food_rating > other.food_rating


class FoodRatings:
    def __init__(self, foods: List[str], cuisines: List[str], ratings: List[int]):
        # Map food with its rating.
        self.food_rating_map = {}
        # Map food with the cuisine it belongs to.
        self.food_cuisine_map = {}
        # Store all food of a cuisine in a priority queue (to sort them on ratings/name).
        # Priority queue element -> Food: (food_rating, food_name)
        self.cuisine_food_map = defaultdict(list)

        for i in range(len(foods)):
            # Store 'rating' and 'cuisine' of the current 'food' in 'food_rating_map' and 'food_cuisine_map' maps.
            self.food_rating_map[foods[i]] = ratings[i]
            self.food_cuisine_map[foods[i]] = cuisines[i]
            # Insert the '(rating, name)' element into the current cuisine's priority queue.
            heappush(self.cuisine_food_map[cuisines[i]], Food(
                ratings[i], foods[i]))

    def changeRating(self, food: str, newRating: int) -> None:
        # Update food's rating in 'food_rating' map.
        self.food_rating_map[food] = newRating
        # Insert the '(new rating, name)' element in the respective cuisine's priority queue.
        cuisineName = self.food_cuisine_map[food]
        heappush(
            self.cuisine_food_map[cuisineName], Food(newRating, food))

    def highestRated(self, cuisine: str) -> str:
        # Get the highest rated 'food' of 'cuisine'.
        highest_rated = self.cuisine_food_map[cuisine][0]

        # If the latest rating of 'food' doesn't match with the 'rating' on which it was sorted in the priority queue,
        # then we discard this element from the priority queue.
        while self.food_rating_map[highest_rated.food_name] != highest_rated.food_rating:
            heappop(self.cuisine_food_map[cuisine])
            highest_rated = self.cuisine_food_map[cuisine][0]

        # Return the name of the highest-rated 'food' of 'cuisine'.
        return highest_rated.food_name

# Your FoodRatings object will be instantiated and called as such:
# obj = FoodRatings(foods, cuisines, ratings)
# obj.changeRating(food,newRating)
# param_2 = obj.highestRated(cuisine)
```

</details>

## [2357. Make Array Zero by Subtracting Equal Amounts](https://leetcode.com/problems/make-array-zero-by-subtracting-equal-amounts/)  1225

- [Official](https://leetcode.cn/problems/make-array-zero-by-subtracting-equal-amounts/solutions/2128232/shi-shu-zu-zhong-suo-you-yuan-su-du-deng-ix12/)

<details><summary>Description</summary>

```text
You are given a non-negative integer array nums. In one operation, you must:
- Choose a positive integer x such that x is less than or equal to the smallest non-zero element in nums.
- Subtract x from every positive element in nums.

Return the minimum number of operations to make every element in nums equal to 0.

Example 1:
Input: nums = [1,5,0,3,5]
Output: 3
Explanation:
In the first operation, choose x = 1. Now, nums = [0,4,0,2,4].
In the second operation, choose x = 2. Now, nums = [0,2,0,0,2].
In the third operation, choose x = 2. Now, nums = [0,0,0,0,0].

Example 2:
Input: nums = [0]
Output: 0
Explanation: Each element in nums is already 0 so no operations are needed.

Constraints:
1 <= nums.length <= 100
0 <= nums[i] <= 100
```

<details><summary>Hint</summary>

```text
1. It is always best to set x as the smallest non-zero element in nums.
2. Elements with the same value will always take the same number of operations to become 0.
   Contrarily, elements with different values will always take a different number of operations to become 0.
3. The answer is the number of unique non-zero numbers in nums.
```

</details>

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
int minimumOperations(int* nums, int numsSize) {
    int retVal = 0;

    struct hashStruct* pHashTable = NULL;
    struct hashStruct* pTemp;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] == 0) {  // Each element in nums is already 0 so no operations are needed.
            continue;
        }

        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &nums[i], pTemp);
        if (pTemp == NULL) {
            ++retVal;

            pTemp = (struct hashStruct*)malloc(sizeof(struct hashStruct));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                return retVal;
            }
            pTemp->key = nums[i];
            HASH_ADD_INT(pHashTable, key, pTemp);
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
    int minimumOperations(vector<int>& nums) {
        int retVal = 0;

        unordered_map<int, int> hashTable;
        for (auto num : nums) {
            if (num == 0) {  // Each element in nums is already 0 so no operations are needed.
                continue;
            }

            auto iterator = hashTable.find(num);
            if (iterator == hashTable.end()) {
                ++retVal;
            }
            hashTable[num] += 1;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minimumOperations(self, nums: List[int]) -> int:
        retVal = 0

        hashTable = defaultdict(int)
        for num in nums:
            if num == 0:    # Each element in nums is already 0 so no operations are needed.
                continue

            if num not in hashTable:
                retVal += 1

            hashTable[num] += 1

        return retVal
```

</details>

## [2363. Merge Similar Items](https://leetcode.com/problems/merge-similar-items/)  1270

- [Official](https://leetcode.cn/problems/merge-similar-items/solutions/2136734/he-bing-xiang-si-de-wu-pin-by-leetcode-s-ywx0/)

<details><summary>Description</summary>

```text
You are given two 2D integer arrays, items1 and items2, representing two sets of items.
Each array items has the following properties:

items[i] = [valuei, weighti] where valuei represents the value and weighti represents the weight of the ith item.
The value of each item in items is unique.
Return a 2D integer array ret where ret[i] = [valuei, weighti],
with weighti being the sum of weights of all items with value valuei.

Note: ret should be returned in ascending order by value.

Example 1:
Input: items1 = [[1,1],[4,5],[3,8]], items2 = [[3,1],[1,5]]
Output: [[1,6],[3,9],[4,5]]
Explanation:
The item with value = 1 occurs in items1 with weight = 1 and in items2 with weight = 5, total weight = 1 + 5 = 6.
The item with value = 3 occurs in items1 with weight = 8 and in items2 with weight = 1, total weight = 8 + 1 = 9.
The item with value = 4 occurs in items1 with weight = 5, total weight = 5.
Therefore, we return [[1,6],[3,9],[4,5]].

Example 2:
Input: items1 = [[1,1],[3,2],[2,3]], items2 = [[2,1],[3,2],[1,3]]
Output: [[1,4],[2,4],[3,4]]
Explanation:
The item with value = 1 occurs in items1 with weight = 1 and in items2 with weight = 3, total weight = 1 + 3 = 4.
The item with value = 2 occurs in items1 with weight = 3 and in items2 with weight = 1, total weight = 3 + 1 = 4.
The item with value = 3 occurs in items1 with weight = 2 and in items2 with weight = 2, total weight = 2 + 2 = 4.
Therefore, we return [[1,4],[2,4],[3,4]].

Example 3:
Input: items1 = [[1,3],[2,2]], items2 = [[7,1],[2,2],[1,4]]
Output: [[1,7],[2,4],[7,1]]
Explanation:
The item with value = 1 occurs in items1 with weight = 3 and in items2 with weight = 4, total weight = 3 + 4 = 7.
The item with value = 2 occurs in items1 with weight = 2 and in items2 with weight = 2, total weight = 2 + 2 = 4.
The item with value = 7 occurs in items2 with weight = 1, total weight = 1.
Therefore, we return [[1,7],[2,4],[7,1]].

Constraints:
1 <= items1.length, items2.length <= 1000
items1[i].length == items2[i].length == 2
1 <= valuei, weighti <= 1000
Each valuei in items1 is unique.
Each valuei in items2 is unique.
```

<details><summary>Hint</summary>

```text
1. Map the weights using the corresponding values as keys.
2. Make sure your output is sorted in ascending order by value.
```

</details>

</details>

<details><summary>C</summary>

```c
#define HASH_TABLE (0)
#define SORT (1)
int compareIntArray(const void* a1, const void* a2) {
    const int* p1 = *(const int**)a1;
    const int* p2 = *(const int**)a2;

    // ascending order
    return (p1[0] > p2[0]);
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** mergeSimilarItems(int** items1, int items1Size, int* items1ColSize, int** items2, int items2Size,
                        int* items2ColSize, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    // malloc return value
    (*returnSize) = items1Size + items2Size;
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, ((*returnSize) * sizeof(int)));
    pRetVal = (int**)malloc((*returnSize) * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        (*returnSize) = 0;
        return pRetVal;
    }

#if (HASH_TABLE)
    printf("HASH_TABLE\n");

#elif (SORT)
    printf("SORT\n");

    // sort items1 and items2
    qsort(items1, items1Size, sizeof(int*), compareIntArray);
    qsort(items2, items2Size, sizeof(int*), compareIntArray);

    // merge items1 and items2
    int i;
    (*returnSize) = 0;
    int idx1 = 0;
    int idx2 = 0;
    while ((idx1 < items1Size) && (idx2 < items2Size)) {
        (*returnColumnSizes)[(*returnSize)] = 2;
        pRetVal[(*returnSize)] = (int*)malloc(((*returnColumnSizes)[(*returnSize)]) * sizeof(int));
        if (pRetVal[(*returnSize)] == NULL) {
            perror("malloc");
            for (i = 0; i < (*returnSize); ++i) {
                free(pRetVal[i]);
                pRetVal[i] = NULL;
            }
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        if (items1[idx1][0] == items2[idx2][0]) {
            pRetVal[(*returnSize)][0] = items1[idx1][0];
            pRetVal[(*returnSize)][1] = items1[idx1][1] + items2[idx2][1];
            ++idx1;
            ++idx2;
        } else if (items1[idx1][0] < items2[idx2][0]) {
            pRetVal[(*returnSize)][0] = items1[idx1][0];
            pRetVal[(*returnSize)][1] = items1[idx1][1];
            ++idx1;
        } else if (items1[idx1][0] > items2[idx2][0]) {
            pRetVal[(*returnSize)][0] = items2[idx2][0];
            pRetVal[(*returnSize)][1] = items2[idx2][1];
            ++idx2;
        }

        ++(*returnSize);
    }
    while (idx1 < items1Size) {
        (*returnColumnSizes)[(*returnSize)] = 2;
        pRetVal[(*returnSize)] = (int*)malloc(((*returnColumnSizes)[(*returnSize)]) * sizeof(int));
        if (pRetVal[(*returnSize)] == NULL) {
            perror("malloc");
            for (i = 0; i < (*returnSize); ++i) {
                free(pRetVal[i]);
                pRetVal[i] = NULL;
            }
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        pRetVal[(*returnSize)][0] = items1[idx1][0];
        pRetVal[(*returnSize)][1] = items1[idx1][1];
        ++idx1;

        ++(*returnSize);
    }
    while (idx2 < items2Size) {
        (*returnColumnSizes)[(*returnSize)] = 2;
        pRetVal[(*returnSize)] = (int*)malloc(((*returnColumnSizes)[(*returnSize)]) * sizeof(int));
        if (pRetVal[(*returnSize)] == NULL) {
            perror("malloc");
            for (i = 0; i < (*returnSize); ++i) {
                free(pRetVal[i]);
                pRetVal[i] = NULL;
            }
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        pRetVal[(*returnSize)][0] = items2[idx2][0];
        pRetVal[(*returnSize)][1] = items2[idx2][1];
        ++idx2;

        ++(*returnSize);
    }
#endif

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define HASH_TABLE (1)
#define SORT (1)
   public:
    vector<vector<int>> mergeSimilarItems(vector<vector<int>>& items1, vector<vector<int>>& items2) {
        vector<vector<int>> retVal;

#if (HASH_TABLE)
        cout << "HASH_TABLE\n";

        map<int, int> hashTable;
        for (auto& item : items1) {
            hashTable[item[0]] += item[1];
        }
        for (auto& item : items2) {
            hashTable[item[0]] += item[1];
        }

        for (auto& [key, value] : hashTable) {
            retVal.push_back({key, value});
        }
#elif (SORT)
        cout << "SORT\n";

        sort(items1.begin(), items1.end(), [&](const vector<int>& x, const vector<int>& y) { return (x[0] < y[0]); });
        sort(items2.begin(), items2.end(), [&](const vector<int>& x, const vector<int>& y) { return (x[0] < y[0]); });

        int len1 = items1.size();
        int len2 = items2.size();
        int idx1 = 0;
        int idx2 = 0;
        while ((idx1 < len1) && (idx2 < len2)) {
            vector<int> iter(2);
            if (items1[idx1][0] == items2[idx2][0]) {
                iter[0] = items1[idx1][0];
                iter[1] = items1[idx1][1] + items2[idx2][1];
                ++idx1;
                ++idx2;
            } else if (items1[idx1][0] < items2[idx2][0]) {
                iter[0] = items1[idx1][0];
                iter[1] = items1[idx1][1];
                ++idx1;
            } else if (items1[idx1][0] > items2[idx2][0]) {
                iter[0] = items2[idx2][0];
                iter[1] = items2[idx2][1];
                ++idx2;
            }
            retVal.push_back(iter);
        }
        while (idx1 < len1) {
            vector<int> iter(2);
            iter[0] = items1[idx1][0];
            iter[1] = items1[idx1][1];
            retVal.push_back(iter);
            ++idx1;
        }
        while (idx2 < len2) {
            vector<int> iter(2);
            iter[0] = items2[idx2][0];
            iter[1] = items2[idx2][1];
            retVal.push_back(iter);
            ++idx2;
        }
#endif

        return retVal;
    }
};
```

</details>

## [2367. Number of Arithmetic Triplets](https://leetcode.com/problems/number-of-arithmetic-triplets/)  1203

- [Official](https://leetcode.cn/problems/number-of-arithmetic-triplets/description/)

<details><summary>Description</summary>

```text
You are given a 0-indexed, strictly increasing integer array nums and a positive integer diff.
A triplet (i, j, k) is an arithmetic triplet if the following conditions are met:
- i < j < k,
- nums[j] - nums[i] == diff, and
- nums[k] - nums[j] == diff.
Return the number of unique arithmetic triplets.

Example 1:
Input: nums = [0,1,4,6,7,10], diff = 3
Output: 2
Explanation:
(1, 2, 4) is an arithmetic triplet because both 7 - 4 == 3 and 4 - 1 == 3.
(2, 4, 5) is an arithmetic triplet because both 10 - 7 == 3 and 7 - 4 == 3.

Example 2:
Input: nums = [4,5,6,7,8,9], diff = 2
Output: 2
Explanation:
(0, 2, 4) is an arithmetic triplet because both 8 - 6 == 2 and 6 - 4 == 2.
(1, 3, 5) is an arithmetic triplet because both 9 - 7 == 2 and 7 - 5 == 2.

Constraints:
3 <= nums.length <= 200
0 <= nums[i] <= 200
1 <= diff <= 50
nums is strictly increasing.
```

<details><summary>Hint</summary>

```text
1. Are the constraints small enough for brute force?
2. We can use three loops, each iterating through the array to go through every possible triplet.
   Be sure to not count duplicates.
```

</details>

</details>

<details><summary>C</summary>

```c
int arithmeticTriplets(int* nums, int numsSize, int diff) {
    int retVal = 0;

#define MAX_HASHTABLE_SIZE (200 + 50 + 50 + 4)  // 3 <= nums.length <= 200; 0 <= nums[i] <= 200; 1 <= diff <= 50
    int hashTable[MAX_HASHTABLE_SIZE];
    memset(hashTable, 0, sizeof(hashTable));

    int i;
    for (i = 0; i < numsSize; ++i) {
        hashTable[nums[i]] = MAX_HASHTABLE_SIZE;  // 0 <= nums[i] <= 200
    }
    for (i = 0; i < numsSize; ++i) {
        if (hashTable[nums[i] + diff] != MAX_HASHTABLE_SIZE) {
            continue;
        }
        if (hashTable[nums[i] + diff + diff] != MAX_HASHTABLE_SIZE) {
            continue;
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
    int arithmeticTriplets(vector<int>& nums, int diff) {
        int retVal = 0;

        unordered_map<int, int> hashTable;
        for (auto num : nums) {
            hashTable[num] = num;
        }
        for (auto num : nums) {
            if (hashTable.find(num + diff) == hashTable.end()) {
                continue;
            }
            if (hashTable.find(num + diff + diff) == hashTable.end()) {
                continue;
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
    def arithmeticTriplets(self, nums: List[int], diff: int) -> int:
        retVal = 0

        hashTable = defaultdict(bool)
        for num in nums:
            hashTable[num] = True
        for num in nums:
            if (num+diff in hashTable) and (num+diff+diff in hashTable):
                retVal += 1

        # for num in nums:
        #     if (num+diff in nums) and (num+diff+diff in nums):
        #         retVal += 1

        return retVal
```

</details>

## [2404. Most Frequent Even Element](https://leetcode.com/problems/most-frequent-even-element/)  1259

- [Official](https://leetcode.cn/problems/most-frequent-even-element/solutions/2219974/chu-xian-zui-pin-fan-de-ou-shu-yuan-su-b-cxeo/)

<details><summary>Description</summary>

```text
Given an integer array nums, return the most frequent even element.

If there is a tie, return the smallest one. If there is no such element, return -1.

Example 1:
Input: nums = [0,1,2,2,4,4,1]
Output: 2
Explanation:
The even elements are 0, 2, and 4. Of these, 2 and 4 appear the most.
We return the smallest one, which is 2.

Example 2:
Input: nums = [4,4,4,9,2,4]
Output: 4
Explanation: 4 is the even element appears the most.

Example 3:
Input: nums = [29,47,21,41,13,37,25,7]
Output: -1
Explanation: There is no even element.

Constraints:
1 <= nums.length <= 2000
0 <= nums[i] <= 10^5
```

<details><summary>Hint</summary>

```text
1. Could you count the frequency of each even element in the array?
2. Would a hashmap help?
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
int mostFrequentEven(int* nums, int numsSize) {
    int retVal = -1;

    //
    int hashTableSize = 0;
    struct hashTable* pMap = NULL;
    struct hashTable* pTmp;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] % 2 != 0) {
            continue;
        }

        pTmp = NULL;
        HASH_FIND_INT(pMap, &nums[i], pTmp);
        if (pTmp == NULL) {
            pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (pTmp == NULL) {
                perror("malloc");
                freeAll(pMap);
                return retVal;
            }
            pTmp->key = nums[i];
            pTmp->value = 1;
            HASH_ADD_INT(pMap, key, pTmp);
            ++hashTableSize;
        } else {
            pTmp->value += 1;
        }
    }
    if (hashTableSize == 0) {
        return retVal;
    }

    //
    int sortHashTable[hashTableSize][2];
    memset(sortHashTable, 0, sizeof(sortHashTable));
    i = 0;
    pTmp = NULL;
    struct hashTable* pCurrent = NULL;
    HASH_ITER(hh, pMap, pCurrent, pTmp) {
        sortHashTable[i][0] = pCurrent->key;
        sortHashTable[i][1] = pCurrent->value;
        ++i;

        HASH_DEL(pMap, pCurrent);
        free(pCurrent);
    }
    qsort(sortHashTable, hashTableSize, sizeof(sortHashTable[0]), compareIntArray);
    retVal = sortHashTable[0][0];

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int mostFrequentEven(vector<int>& nums) {
        int retVal = -1;

        //
        map<int, int> hashTable;
        for (int num : nums) {
            if (num % 2 != 0) {
                continue;
            }
            ++hashTable[num];
        }
        if (hashTable.size() == 0) {
            return retVal;
        }

        //
        vector<pair<int, int>> sortHashTable;
        for (auto iterator = hashTable.begin(); iterator != hashTable.end(); ++iterator) {
            sortHashTable.push_back(*iterator);
        }
        sort(sortHashTable.begin(), sortHashTable.end(), [=](pair<int, int>& a, pair<int, int>& b) {
            return a.second == b.second ? a.first < b.first : a.second > b.second;
        });
        retVal = sortHashTable[0].first;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def mostFrequentEven(self, nums: List[int]) -> int:
        retVal = -1

        hashTable = Counter(nums)
        sortHashTableKey = sorted(hashTable, key=lambda i: (-hashTable[i], i))
        for key in sortHashTableKey:
            if key % 2 == 0:
                retVal = key
                break

        return retVal
```

</details>

## [2405. Optimal Partition of String](https://leetcode.com/problems/optimal-partition-of-string/)  1355

<details><summary>Description</summary>

```text
Given a string s, partition the string into one or more substrings such that the characters in each substring are unique.
That is, no letter appears in a single substring more than once.

Return the minimum number of substrings in such a partition.

Note that each character should belong to exactly one substring in a partition.

Example 1:
Input: s = "abacaba"
Output: 4
Explanation:
Two possible partitions are ("a","ba","cab","a") and ("ab","a","ca","ba").
It can be shown that 4 is the minimum number of substrings needed.

Example 2:
Input: s = "ssssss"
Output: 6
Explanation:
The only valid partition is ("s","s","s","s","s","s").

Constraints:
1 <= s.length <= 10^5
s consists of only English lowercase letters.
```

<details><summary>Hint</summary>

```text
1. Try to come up with a greedy approach.
2. From left to right, extend every substring in the partition as much as possible.
```

</details>

</details>

<details><summary>C</summary>

```c
int partitionString(char *s) {
    int retVal = 0;

    // s consists of only English lowercase letters.
#define MAX_HASHTABLE_SIZE (26)
    int HashTable[MAX_HASHTABLE_SIZE];
    memset(HashTable, 0, sizeof(HashTable));

    int idx;
    int len = strlen(s);
    int i;
    for (i = 0; i < len; ++i) {
        idx = s[i] - 'a';
        if (HashTable[idx] != 0) {
            memset(HashTable, 0, sizeof(HashTable));
            ++retVal;
        }
        ++HashTable[idx];
    }
    ++retVal;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int partitionString(string s) {
        int retVal = 0;

        unordered_map<char, int> hashTable;
        for (auto c : s) {
            if (hashTable[c] == 1) {
                for (auto iterator : hashTable) {
                    hashTable[iterator.first] = 0;
                }
                ++retVal;
            }
            hashTable[c] = 1;
        }
        ++retVal;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def partitionString(self, s: str) -> int:
        retVal = 0

        hashTable = defaultdict(dict)
        for c in s:
            if hashTable[c] != {}:
                hashTable = defaultdict(dict)
                retVal += 1
            hashTable[c] = 1
        retVal += 1

        return retVal
```

</details>

## [2453. Destroy Sequential Targets](https://leetcode.com/problems/destroy-sequential-targets/)  1761

<details><summary>Description</summary>

```text
You are given a 0-indexed array nums consisting of positive integers, representing targets on a number line.
You are also given an integer space.

You have a machine which can destroy targets.
Seeding the machine with some nums[i] allows it to destroy all targets with values
that can be represented as nums[i] + c * space, where c is any non-negative integer.
You want to destroy the maximum number of targets in nums.

Return the minimum value of nums[i] you can seed the machine with to destroy the maximum number of targets.

Example 1:
Input: nums = [3,7,8,1,1,5], space = 2
Output: 1
Explanation: If we seed the machine with nums[3], then we destroy all targets equal to 1,3,5,7,9,...
In this case, we would destroy 5 total targets (all except for nums[2]).
It is impossible to destroy more than 5 targets, so we return nums[3].

Example 2:
Input: nums = [1,3,5,2,4,6], space = 2
Output: 1
Explanation: Seeding the machine with nums[0], or nums[3] destroys 3 targets.
It is not possible to destroy more than 3 targets.
Since nums[0] is the minimal integer that can destroy 3 targets, we return 1.

Example 3:
Input: nums = [6,2,5], space = 100
Output: 2
Explanation: Whatever initial seed we select, we can only destroy 1 target. The minimal seed is nums[1].

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
1 <= space <= 10^9
```

<details><summary>Hint</summary>

```text
1. Keep track of nums[i] modulo k.
2. Iterate over nums in sorted order.
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
int destroyTargets(int *nums, int numsSize, int space) {
    int retVal = INT_MAX;

    struct hashTable *pCount = NULL;
    struct hashTable *pTmp;
    int maxTarget = 0;
    int key, value;
    int i;
    for (i = 0; i < numsSize; ++i) {
        key = nums[i] % space;
        value = 0;

        pTmp = NULL;
        HASH_FIND_INT(pCount, &key, pTmp);
        if (pTmp != NULL) {
            value = pTmp->value;
        }

        key = nums[i] % space;
        pTmp = NULL;
        HASH_FIND_INT(pCount, &key, pTmp);
        if (pTmp == NULL) {
            pTmp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTmp == NULL) {
                perror("malloc");
                freeAll(pCount);
                return retVal;
            }
            pTmp->key = key;
            pTmp->value = value + 1;
            HASH_ADD_INT(pCount, key, pTmp);
        } else {
            pTmp->value = value + 1;
        }

        maxTarget = fmax(maxTarget, value + 1);
    }
    for (i = 0; i < numsSize; ++i) {
        key = nums[i] % space;
        value = 0;

        pTmp = NULL;
        HASH_FIND_INT(pCount, &key, pTmp);
        if (pTmp != NULL) {
            value = pTmp->value;
        }
        if (value == maxTarget) {
            retVal = fmin(retVal, nums[i]);
        }
    }
    freeAll(pCount);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int destroyTargets(vector<int>& nums, int space) {
        int retVal = numeric_limits<int>::max();

        int maxTarget = 0;
        unordered_map<int, int> count;
        for (auto num : nums) {
            count[num % space] += 1;
            maxTarget = max(maxTarget, count[num % space]);
        }

        for (auto num : nums) {
            if (count[num % space] == maxTarget) {
                retVal = min(retVal, num);
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
    def destroyTargets(self, nums: List[int], space: int) -> int:
        retVal = float('inf')

        count = defaultdict(int)
        for num in nums:
            count[num % space] += 1
        maxTarget = max(count.values())

        for num in nums:
            if count[num % space] == maxTarget:
                retVal = min(retVal, num)

        return retVal
```

</details>

## [2570. Merge Two 2D Arrays by Summing Values](https://leetcode.com/problems/merge-two-2d-arrays-by-summing-values/)

<details><summary>Description</summary>

```text
You are given two 2D integer arrays nums1 and nums2.
- nums1[i] = [idi, vali] indicate that the number with the id idi has a value equal to vali.
- nums2[i] = [idi, vali] indicate that the number with the id idi has a value equal to vali.

Each array contains unique ids and is sorted in ascending order by id.

Merge the two arrays into one array that is sorted in ascending order by id, respecting the following conditions:
- Only ids that appear in at least one of the two arrays should be included in the resulting array.
- Each id should be included only once and its value should be the sum of the values of this id in the two arrays.
  If the id does not exist in one of the two arrays then its value in that array is considered to be 0.

Return the resulting array. The returned array must be sorted in ascending order by id.

Example 1:
Input: nums1 = [[1,2],[2,3],[4,5]], nums2 = [[1,4],[3,2],[4,1]]
Output: [[1,6],[2,3],[3,2],[4,6]]
Explanation: The resulting array contains the following:
- id = 1, the value of this id is 2 + 4 = 6.
- id = 2, the value of this id is 3.
- id = 3, the value of this id is 2.
- id = 4, the value of this id is 5 + 1 = 6.

Example 2:
Input: nums1 = [[2,4],[3,6],[5,5]], nums2 = [[1,3],[4,3]]
Output: [[1,3],[2,4],[3,6],[4,3],[5,5]]
Explanation: There are no common ids, so we just include each id with its value in the resulting list.

Constraints:
1 <= nums1.length, nums2.length <= 200
nums1[i].length == nums2[j].length == 2
1 <= idi, vali <= 1000
Both arrays contain unique ids.
Both arrays are in strictly ascending order by id.
```

<details><summary>Hint</summary>

```text
1. Use a dictionary/hash map to keep track of the indices and their sum values.
```

</details>

</details>

<details><summary>C</summary>

```c
#define HASH_TABLE (0)
#define SORT (1)
int compareIntArray(const void* a1, const void* a2) {
    const int* p1 = *(const int**)a1;
    const int* p2 = *(const int**)a2;

    // ascending order
    return (p1[0] > p2[0]);
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** mergeArrays(int** nums1, int nums1Size, int* nums1ColSize, int** nums2, int nums2Size, int* nums2ColSize,
                  int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    // malloc return value
    (*returnSize) = nums1Size + nums2Size;
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, ((*returnSize) * sizeof(int)));
    pRetVal = (int**)malloc((*returnSize) * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        (*returnSize) = 0;
        return pRetVal;
    }

#if (HASH_TABLE)
    printf("HASH_TABLE\n");

#elif (SORT)
    printf("SORT\n");

    // sort nums1 and nums2
    qsort(nums1, nums1Size, sizeof(int*), compareIntArray);
    qsort(nums2, nums2Size, sizeof(int*), compareIntArray);

    // merge nums1 and nums2
    int i;
    (*returnSize) = 0;
    int idx1 = 0;
    int idx2 = 0;
    while ((idx1 < nums1Size) && (idx2 < nums2Size)) {
        (*returnColumnSizes)[(*returnSize)] = 2;
        pRetVal[(*returnSize)] = (int*)malloc(((*returnColumnSizes)[(*returnSize)]) * sizeof(int));
        if (pRetVal[(*returnSize)] == NULL) {
            perror("malloc");
            for (i = 0; i < (*returnSize); ++i) {
                free(pRetVal[i]);
                pRetVal[i] = NULL;
            }
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        if (nums1[idx1][0] == nums2[idx2][0]) {
            pRetVal[(*returnSize)][0] = nums1[idx1][0];
            pRetVal[(*returnSize)][1] = nums1[idx1][1] + nums2[idx2][1];
            ++idx1;
            ++idx2;
        } else if (nums1[idx1][0] < nums2[idx2][0]) {
            pRetVal[(*returnSize)][0] = nums1[idx1][0];
            pRetVal[(*returnSize)][1] = nums1[idx1][1];
            ++idx1;
        } else if (nums1[idx1][0] > nums2[idx2][0]) {
            pRetVal[(*returnSize)][0] = nums2[idx2][0];
            pRetVal[(*returnSize)][1] = nums2[idx2][1];
            ++idx2;
        }

        ++(*returnSize);
    }
    while (idx1 < nums1Size) {
        (*returnColumnSizes)[(*returnSize)] = 2;
        pRetVal[(*returnSize)] = (int*)malloc(((*returnColumnSizes)[(*returnSize)]) * sizeof(int));
        if (pRetVal[(*returnSize)] == NULL) {
            perror("malloc");
            for (i = 0; i < (*returnSize); ++i) {
                free(pRetVal[i]);
                pRetVal[i] = NULL;
            }
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        pRetVal[(*returnSize)][0] = nums1[idx1][0];
        pRetVal[(*returnSize)][1] = nums1[idx1][1];
        ++idx1;

        ++(*returnSize);
    }
    while (idx2 < nums2Size) {
        (*returnColumnSizes)[(*returnSize)] = 2;
        pRetVal[(*returnSize)] = (int*)malloc(((*returnColumnSizes)[(*returnSize)]) * sizeof(int));
        if (pRetVal[(*returnSize)] == NULL) {
            perror("malloc");
            for (i = 0; i < (*returnSize); ++i) {
                free(pRetVal[i]);
                pRetVal[i] = NULL;
            }
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        pRetVal[(*returnSize)][0] = nums2[idx2][0];
        pRetVal[(*returnSize)][1] = nums2[idx2][1];
        ++idx2;

        ++(*returnSize);
    }
#endif

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define HASH_TABLE (1)
#define SORT (1)
   public:
    vector<vector<int>> mergeArrays(vector<vector<int>>& nums1, vector<vector<int>>& nums2) {
        vector<vector<int>> retVal;

#if (HASH_TABLE)
        cout << "HASH_TABLE\n";

        map<int, int> hashTable;
        for (auto& item : nums1) {
            hashTable[item[0]] += item[1];
        }
        for (auto& item : nums2) {
            hashTable[item[0]] += item[1];
        }

        for (auto& [key, value] : hashTable) {
            retVal.push_back({key, value});
        }
#elif (SORT)
        cout << "SORT\n";

        sort(nums1.begin(), nums1.end(), [&](const vector<int>& x, const vector<int>& y) { return (x[0] < y[0]); });
        sort(nums2.begin(), nums2.end(), [&](const vector<int>& x, const vector<int>& y) { return (x[0] < y[0]); });

        int len1 = nums1.size();
        int len2 = nums2.size();
        int idx1 = 0;
        int idx2 = 0;
        while ((idx1 < len1) && (idx2 < len2)) {
            vector<int> iter(2);
            if (nums1[idx1][0] == nums2[idx2][0]) {
                iter[0] = nums1[idx1][0];
                iter[1] = nums1[idx1][1] + nums2[idx2][1];
                ++idx1;
                ++idx2;
            } else if (nums1[idx1][0] < nums2[idx2][0]) {
                iter[0] = nums1[idx1][0];
                iter[1] = nums1[idx1][1];
                ++idx1;
            } else if (nums1[idx1][0] > nums2[idx2][0]) {
                iter[0] = nums2[idx2][0];
                iter[1] = nums2[idx2][1];
                ++idx2;
            }
            retVal.push_back(iter);
        }
        while (idx1 < len1) {
            vector<int> iter(2);
            iter[0] = nums1[idx1][0];
            iter[1] = nums1[idx1][1];
            retVal.push_back(iter);
            ++idx1;
        }
        while (idx2 < len2) {
            vector<int> iter(2);
            iter[0] = nums2[idx2][0];
            iter[1] = nums2[idx2][1];
            retVal.push_back(iter);
            ++idx2;
        }
#endif

        return retVal;
    }
};
```

</details>

## [2610. Convert an Array Into a 2D Array With Conditions](https://leetcode.com/problems/convert-an-array-into-a-2d-array-with-conditions/)  1373

- [Official](https://leetcode.com/problems/convert-an-array-into-a-2d-array-with-conditions/editorial/)

<details><summary>Description</summary>

```text
You are given an integer array nums. You need to create a 2D array from nums satisfying the following conditions:
- The 2D array should contain only the elements of the array nums.
- Each row in the 2D array contains distinct integers.
- The number of rows in the 2D array should be minimal.
Return the resulting array. If there are multiple answers, return any of them.

Note that the 2D array can have a different number of elements on each row.

Example 1:
Input: nums = [1,3,4,1,2,3,1]
Output: [[1,3,4,2],[1,3],[1]]
Explanation: We can create a 2D array that contains the following rows:
- 1,3,4,2
- 1,3
- 1
All elements of nums were used, and each row of the 2D array contains distinct integers, so it is a valid answer.
It can be shown that we cannot have less than 3 rows in a valid array.

Example 2:
Input: nums = [1,2,3,4]
Output: [[4,3,2,1]]
Explanation: All elements of the array are distinct, so we can keep all of them in the first row of the 2D array.

Constraints:
1 <= nums.length <= 200
1 <= nums[i] <= nums.length
```

<details><summary>Hint</summary>

```text
1. Process the elements in the array one by one in any order and only create a new row in the matrix
   when we cannot put it into the existing rows
2. We can simply iterate over the existing rows of the matrix to see if we can place each element.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** findMatrix(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    //
    pRetVal = (int**)malloc(numsSize * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    //
    (*returnColumnSizes) = (int*)malloc(numsSize * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, (numsSize * sizeof(int)));

    // 1 <= nums.length <= 200, 1 <= nums[i] <= nums.length.
#define MAX_NUMS_SIZE (200 + 4)
    int hashTable[MAX_NUMS_SIZE];
    memset(hashTable, 0, sizeof(hashTable));

    int i;
    for (i = 0; i < numsSize; ++i) {
        hashTable[nums[i]] += 1;
    }

    int count = numsSize;
    while (count > 0) {
        pRetVal[(*returnSize)] = (int*)malloc(numsSize * sizeof(int));
        if (pRetVal[(*returnSize)] == NULL) {
            perror("malloc");
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            for (i = 0; i < (*returnSize); ++i) {
                free(pRetVal[i]);
                pRetVal[i] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        memset(pRetVal[(*returnSize)], 0, (numsSize * sizeof(int)));
        for (i = 1; i < MAX_NUMS_SIZE; ++i) {
            if (hashTable[i] == 0) {
                continue;
            }
            pRetVal[(*returnSize)][(*returnColumnSizes)[(*returnSize)]] = i;
            (*returnColumnSizes)[(*returnSize)] += 1;

            hashTable[i] -= 1;
            count -= 1;
        }
        (*returnSize) += 1;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<vector<int>> findMatrix(vector<int>& nums) {
        vector<vector<int>> retVal;

        unordered_map<int, int> hashTable;
        for (int num : nums) {
            hashTable[num] += 1;
        }

        while (hashTable.empty() == false) {
            vector<int> row;
            for (auto iterator : hashTable) {
                int key = iterator.first;
                row.emplace_back(key);
                hashTable[key] -= 1;
            }
            retVal.emplace_back(row);

            for (auto iterator : row) {
                if (hashTable[iterator] == 0) {
                    hashTable.erase(iterator);
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
    def findMatrix(self, nums: List[int]) -> List[List[int]]:
        retVal = []

        hashTable = defaultdict(int)
        for num in nums:
            hashTable[num] += 1

        while hashTable:
            row = []
            for i in hashTable:
                row.append(i)
                hashTable[i] -= 1
            retVal.append(row)

            for i in row:
                if hashTable[i] == 0:
                    hashTable.pop(i)

        return retVal
```

</details>
