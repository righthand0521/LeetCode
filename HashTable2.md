# [Hash Table](https://en.wikipedia.org/wiki/Hash_table)

- [uthash](https://troydhanson.github.io/uthash/)

## [1002. Find Common Characters](https://leetcode.com/problems/find-common-characters/)  1279

- [Official](https://leetcode.com/problems/find-common-characters/editorial/)
- [Official](https://leetcode.cn/problems/find-common-characters/solutions/445468/cha-zhao-chang-yong-zi-fu-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given a string array words, return an array of all characters
that show up in all strings within the words (including duplicates).
You may return the answer in any order.

Example 1:
Input: words = ["bella","label","roller"]
Output: ["e","l","l"]

Example 2:
Input: words = ["cool","lock","cook"]
Output: ["c","o"]

Constraints:
1 <= words.length <= 100
1 <= words[i].length <= 100
words[i] consists of lowercase English letters.
```

</details>

<details><summary>C</summary>

```c
#define MAX_LETTERS (26)  // words[i] consists of lowercase English letters.
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** commonChars(char** words, int wordsSize, int* returnSize) {
    char** pRetVal = NULL;

    (*returnSize) = 0;

    int i, j;

    int minFrequency[MAX_LETTERS];
    memset(minFrequency, 0, sizeof(minFrequency));
    for (i = 0; i < MAX_LETTERS; ++i) {
        minFrequency[i] = INT_MAX;
    }
    int frequency[MAX_LETTERS];
    int wordSize, idx;
    for (i = 0; i < wordsSize; ++i) {
        memset(frequency, 0, sizeof(frequency));
        wordSize = strlen(words[i]);
        for (j = 0; j < wordSize; ++j) {
            idx = words[i][j] - 'a';
            frequency[idx] += 1;
        }

        for (j = 0; j < MAX_LETTERS; ++j) {
            minFrequency[j] = fmin(minFrequency[j], frequency[j]);
        }
    }

    for (i = 0; i < MAX_LETTERS; ++i) {
        (*returnSize) += minFrequency[i];
    }
    pRetVal = (char**)malloc((*returnSize) * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    (*returnSize) = 0;
    for (i = 0; i < MAX_LETTERS; ++i) {
        for (j = 0; j < minFrequency[i]; ++j) {
            pRetVal[(*returnSize)] = (char*)malloc(2 * sizeof(char));
            if (pRetVal[(*returnSize)] == NULL) {
                perror("malloc");
                return pRetVal;
            }
            memset(pRetVal[(*returnSize)], 0, (2 * sizeof(char)));
            pRetVal[(*returnSize)][0] = i + 'a';
            (*returnSize) += 1;
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
    int letters = 26;  // words[i] consists of lowercase English letters.

   public:
    vector<string> commonChars(vector<string>& words) {
        vector<string> retVal;

        vector<int> minFrequency(letters, numeric_limits<int>::max());
        for (string word : words) {
            vector<int> frequency(letters, 0);
            for (char c : word) {
                int idx = c - 'a';
                frequency[idx] += 1;
            }
            for (int i = 0; i < letters; ++i) {
                minFrequency[i] = min(minFrequency[i], frequency[i]);
            }
        }

        for (int i = 0; i < letters; ++i) {
            for (int j = 0; j < minFrequency[i]; ++j) {
                retVal.emplace_back(1, i + 'a');
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
        self.letters = 26  # words[i] consists of lowercase English letters.

    def commonChars(self, words: List[str]) -> List[str]:
        retVal = []

        minFrequency = [float("inf")] * self.letters
        for word in words:
            frequency = [0] * self.letters
            for c in word:
                frequency[ord(c)-ord('a')] += 1
            for i in range(self.letters):
                minFrequency[i] = min(minFrequency[i], frequency[i])

        for i in range(self.letters):
            for _ in range(minFrequency[i]):
                retVal.append(chr(i + ord('a')))

        return retVal
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

## [1072. Flip Columns For Maximum Number of Equal Rows](https://leetcode.com/problems/flip-columns-for-maximum-number-of-equal-rows/)  1797

- [Official](https://leetcode.com/problems/flip-columns-for-maximum-number-of-equal-rows/editorial/)
- [Official](https://leetcode.cn/problems/flip-columns-for-maximum-number-of-equal-rows/solutions/2267115/an-lie-fan-zhuan-de-dao-zui-da-zhi-deng-teeig/)

<details><summary>Description</summary>

```text
You are given an m x n binary matrix matrix.

You can choose any number of columns in the matrix and flip every cell in that column
(i.e., Change the value of the cell from 0 to 1 or vice versa).

Return the maximum number of rows that have all values equal after some number of flips.

Example 1:
Input: matrix = [[0,1],[1,1]]
Output: 1
Explanation: After flipping no values, 1 row has all values equal.

Example 2:
Input: matrix = [[0,1],[1,0]]
Output: 2
Explanation: After flipping values in the first column, both rows have equal values.

Example 3:
Input: matrix = [[0,0,0],[0,0,1],[1,1,0]]
Output: 2
Explanation: After flipping values in the first two columns, the last two rows have equal values.

Constraints:
m == matrix.length
n == matrix[i].length
1 <= m, n <= 300
matrix[i][j] is either 0 or 1.
```

<details><summary>Hint</summary>

```text
1. Flipping a subset of columns is like doing a bitwise XOR of some number K onto each row.
   We want rows X with X ^ K = all 0s or all 1s.
   This is the same as X = X^K ^K = (all 0s or all 1s) ^ K, so we want to count rows that have opposite bits set.
   For example, if K = 1, then we count rows X = (00000...001, or 1111....110).
```

</details>

</details>

<details><summary>C</summary>

```c
#define MAX_KEY_SIZE (300 + 4)  // m == matrix.length, n == matrix[i].length, 1 <= m, n <= 300
struct hashTable {
    char key[MAX_KEY_SIZE];
    int value;
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%s: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int maxEqualRowsAfterFlips(int** matrix, int matrixSize, int* matrixColSize) {
    int retVal = 0;

    struct hashTable* pPatternFrequency = NULL;  // Map to store frequency of each pattern
    struct hashTable* pTmp;
    char patternBuilder[MAX_KEY_SIZE];
    for (int row = 0; row < matrixSize; ++row) {
        memset(patternBuilder, 0, sizeof(patternBuilder));

        // Convert row to pattern relative to its first element
        for (int col = 0; col < matrixColSize[row]; col++) {
            // 'T' if current element matches first element, 'F' otherwise
            if (matrix[row][0] == matrix[row][col]) {
                strcat(patternBuilder, "T");
            } else {
                strcat(patternBuilder, "F");
            }
        }

        // Convert pattern to string and update its frequency in map
        pTmp = NULL;
        HASH_FIND_STR(pPatternFrequency, patternBuilder, pTmp);
        if (pTmp == NULL) {
            pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (pTmp == NULL) {
                perror("malloc");
                freeAll(pPatternFrequency);
                pPatternFrequency = NULL;
                return retVal;
            }
            snprintf(pTmp->key, MAX_KEY_SIZE, "%s", patternBuilder);
            pTmp->value = 0;
            HASH_ADD_STR(pPatternFrequency, key, pTmp);
        }
        pTmp->value++;
    }

    // Find the pattern with maximum frequency
    struct hashTable* pFree = NULL;
    pTmp = NULL;
    HASH_ITER(hh, pPatternFrequency, pFree, pTmp) {
        // printf("%s: %d\n", pPatternFrequency->key, pPatternFrequency->value);
        retVal = fmax(pPatternFrequency->value, retVal);
        HASH_DEL(pPatternFrequency, pFree);
        free(pFree);
        pFree = NULL;
    }
    pPatternFrequency = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
        int retVal = 0;

        unordered_map<string, int> patternFrequency;  // Map to store frequency of each pattern
        for (auto& currentRow : matrix) {
            string patternBuilder = "";

            // Convert row to pattern relative to its first element
            int currentRowSize = currentRow.size();
            for (int col = 0; col < currentRowSize; col++) {
                // 'T' if current element matches first element, 'F' otherwise
                if (currentRow[0] == currentRow[col]) {
                    patternBuilder += "T";
                } else {
                    patternBuilder += "F";
                }
            }

            // Convert pattern to string and update its frequency in map
            patternFrequency[patternBuilder]++;
        }

        // Find the pattern with maximum frequency
        for (auto& entry : patternFrequency) {
            retVal = max(entry.second, retVal);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxEqualRowsAfterFlips(self, matrix: List[List[int]]) -> int:
        retVal = 0

        patternFrequency = {}  # Dictionary to store frequency of each pattern
        for currentRow in matrix:
            patternBuilder = ""

            # Convert row to pattern using list comprehension and
            # join 'T' if element matches first element, 'F' otherwise
            for cell in currentRow:
                if cell == currentRow[0]:
                    patternBuilder += "T"
                else:
                    patternBuilder += "F"

            # Update pattern frequency using dict.get() with default value
            patternFrequency[patternBuilder] = patternFrequency.get(patternBuilder, 0) + 1

        # Return maximum frequency using max() with default of 0
        retVal = max(patternFrequency.values(), default=0)

        return retVal
```

</details>

## [1074. Number of Submatrices That Sum to Target](https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/)  2189

- [Official](https://leetcode.cn/problems/number-of-submatrices-that-sum-to-target/solutions/798061/yuan-su-he-wei-mu-biao-zhi-de-zi-ju-zhen-8ym2/)

<details><summary>Description</summary>

```text
Given a matrix and a target, return the number of non-empty submatrices that sum to target.

A submatrix x1, y1, x2, y2 is the set of all cells matrix[x][y] with x1 <= x <= x2 and y1 <= y <= y2.

Two submatrices (x1, y1, x2, y2) and (x1', y1', x2', y2') are different if they have some coordinate that is different:
for example, if x1 != x1'.

Example 1:
Input: matrix = [[0,1,0],[1,1,1],[0,1,0]], target = 0
Output: 4
Explanation: The four 1x1 submatrices that only contain 0.

Example 2:
Input: matrix = [[1,-1],[-1,1]], target = 0
Output: 5
Explanation: The two 1x2 submatrices, plus the two 2x1 submatrices, plus the 2x2 submatrix.

Example 3:
Input: matrix = [[904]], target = 0
Output: 0

Constraints:
1 <= matrix.length <= 100
1 <= matrix[0].length <= 100
-1000 <= matrix[i] <= 1000
-10^8 <= target <= 10^8
```

<details><summary>Hint</summary>

```text
1. Using a 2D prefix sum, we can query the sum of any submatrix in O(1) time.
   Now for each (r1, r2), we can find the largest sum of a submatrix
   that uses every row in [r1, r2] in linear time using a sliding window.
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
int subarraySum(int *prefixSumList, int prefixSumListSize, int target) {
    int retVal = 0;

    struct hashTable *pPrefixSumMap = NULL;
    struct hashTable *pTmp = NULL;
    pTmp = (struct hashTable *)malloc(sizeof(struct hashTable));
    if (pTmp == NULL) {
        perror("malloc");
        goto exit;
    }
    pTmp->key = 0;
    pTmp->value = 1;
    HASH_ADD_INT(pPrefixSumMap, key, pTmp);

    int prefixSum = 0;
    int sum;
    int i;
    for (i = 0; i < prefixSumListSize; ++i) {
        prefixSum += prefixSumList[i];

        sum = prefixSum - target;
        pTmp = NULL;
        HASH_FIND_INT(pPrefixSumMap, &sum, pTmp);
        if (pTmp != NULL) {
            retVal += pTmp->value;
        }

        sum = prefixSum;
        pTmp = NULL;
        HASH_FIND_INT(pPrefixSumMap, &sum, pTmp);
        if (pTmp == NULL) {
            pTmp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTmp == NULL) {
                perror("malloc");
                goto exit;
            }
            pTmp->key = sum;
            pTmp->value = 1;
            HASH_ADD_INT(pPrefixSumMap, key, pTmp);
        } else {
            pTmp->value += 1;
        }
    }

exit:
    //
    freeAll(pPrefixSumMap);
    pPrefixSumMap = NULL;

    return retVal;
}
int numSubmatrixSumTarget(int **matrix, int matrixSize, int *matrixColSize, int target) {
    int retVal = 0;

    int rowSize = matrixSize;
    int colSize = matrixColSize[0];

    int prefixSumSize = colSize;
    int prefixSum[colSize];
    int row, x, y;
    for (row = 0; row < rowSize; ++row) {
        memset(prefixSum, 0, sizeof(prefixSum));
        for (x = row; x < rowSize; ++x) {
            for (y = 0; y < colSize; ++y) {
                prefixSum[y] += matrix[x][y];
            }
            retVal += subarraySum(prefixSum, prefixSumSize, target);
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
    int subarraySum(vector<int>& prefixSumList, int target) {
        int retVal = 0;

        unordered_map<int, int> hashTable;
        hashTable[0] = 1;

        int prefixSum = 0;
        for (int value : prefixSumList) {
            prefixSum += value;
            if (hashTable.find(prefixSum - target) != hashTable.end()) {
                retVal += hashTable[prefixSum - target];
            }
            hashTable[prefixSum]++;
        }

        return retVal;
    }
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int retVal = 0;

        int rowSize = matrix.size();
        int colSize = matrix[0].size();
        for (int row = 0; row < rowSize; ++row) {
            vector<int> prefixSum(colSize, 0);
            for (int x = row; x < rowSize; ++x) {
                for (int y = 0; y < colSize; ++y) {
                    prefixSum[y] += matrix[x][y];
                }
                retVal += subarraySum(prefixSum, target);
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
    def subarraySum(self, prefixSumList: List[int], target: int) -> int:
        retVal = 0

        hashTable = defaultdict(int)
        hashTable[0] = 1

        prefixSum = 0
        for value in prefixSumList:
            prefixSum += value
            if (prefixSum - target) in hashTable:
                retVal += hashTable[prefixSum - target]
            hashTable[prefixSum] += 1

        return retVal

    def numSubmatrixSumTarget(self, matrix: List[List[int]], target: int) -> int:
        retVal = 0

        rowSize = len(matrix)
        colSize = len(matrix[0])
        for row in range(rowSize):
            prefixSum = [0] * colSize
            for x in range(row, rowSize):
                for y in range(colSize):
                    prefixSum[y] += matrix[x][y]
                retVal += self.subarraySum(prefixSum, target)

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

## [1331. Rank Transform of an Array](https://leetcode.com/problems/rank-transform-of-an-array/)  1355

- [Official](https://leetcode.com/problems/rank-transform-of-an-array/editorial/)
- [Official](https://leetcode.cn/problems/rank-transform-of-an-array/solutions/1701490/shu-zu-xu-hao-zhuan-huan-by-leetcode-sol-8zlu/)

<details><summary>Description</summary>

```text
Given an array of integers arr, replace each element with its rank.

The rank represents how large the element is. The rank has the following rules:
- Rank is an integer starting from 1.
- The larger the element, the larger the rank. If two elements are equal, their rank must be the same.
- Rank should be as small as possible.

Example 1:
Input: arr = [40,10,20,30]
Output: [4,1,2,3]
Explanation: 40 is the largest element. 10 is the smallest. 20 is the second smallest. 30 is the third smallest.

Example 2:
Input: arr = [100,100,100]
Output: [1,1,1]
Explanation: Same elements share the same rank.

Example 3:
Input: arr = [37,12,28,9,100,56,80,5,12]
Output: [5,3,4,2,8,6,7,1,3]

Constraints:
0 <= arr.length <= 10^5
-10^9 <= arr[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1; Use a temporary array to copy the array and sort it.
2. The rank of each element is the number of unique elements smaller than it in the sorted array plus one.
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
int compareInteger(const void *n1, const void *n2) {
    // ascending order
    return (*(int *)n1 > *(int *)n2);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *arrayRankTransform(int *arr, int arrSize, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;

    if (arrSize == 0) {
        return pRetVal;
    }

    pRetVal = (int *)calloc(arrSize, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }

    memcpy(pRetVal, arr, (arrSize * sizeof(int)));
    qsort(pRetVal, arrSize, sizeof(int), compareInteger);

    int rank = 1;
    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
    if (pTemp == NULL) {
        perror("malloc");
        freeAll(pHashTable);
        pHashTable = NULL;
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    pTemp->key = pRetVal[0];
    pTemp->value = rank;
    HASH_ADD_INT(pHashTable, key, pTemp);

    int i;
    for (i = 1; i < arrSize; ++i) {
        if (pRetVal[i] > pRetVal[i - 1]) {
            rank++;
        }
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &pRetVal[i], pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                pHashTable = NULL;
                free(pRetVal);
                pRetVal = NULL;
                return pRetVal;
            }
            pTemp->key = pRetVal[i];
            pTemp->value = rank;
            HASH_ADD_INT(pHashTable, key, pTemp);
        }
    }

    for (i = 0; i < arrSize; ++i) {
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &arr[i], pTemp);
        pRetVal[(*returnSize)++] = pTemp->value;
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
    vector<int> arrayRankTransform(vector<int>& arr) {
        vector<int> retVal;

        int arrSize = arr.size();
        if (arrSize == 0) {
            return retVal;
        }

        vector<int> sortedArr(arr);
        sort(sortedArr.begin(), sortedArr.end());

        int rank = 1;
        unordered_map<int, int> hashTable;
        hashTable[sortedArr[0]] = rank;
        for (int i = 1; i < arrSize; ++i) {
            if (sortedArr[i] > sortedArr[i - 1]) {
                rank++;
            }
            hashTable[sortedArr[i]] = rank;
        }

        for (int value : arr) {
            retVal.emplace_back(hashTable[value]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def arrayRankTransform(self, arr: List[int]) -> List[int]:
        retVal = []

        arrSize = len(arr)
        if arrSize == 0:
            return retVal

        sortArr = sorted(arr)

        rank = 1
        hashTable = defaultdict(int)
        hashTable[sortArr[0]] = rank

        for i in range(1, arrSize):
            if sortArr[i] > sortArr[i - 1]:
                rank += 1
            hashTable[sortArr[i]] = rank

        for value in arr:
            retVal.append(hashTable[value])

        return retVal
```

</details>

## [1346. Check If N and Its Double Exist](https://leetcode.com/problems/check-if-n-and-its-double-exist/)  1225

- [Official](https://leetcode.com/problems/check-if-n-and-its-double-exist/editorial/)
- [Official](https://leetcode.cn/problems/check-if-n-and-its-double-exist/solutions/101742/jian-cha-zheng-shu-ji-qi-liang-bei-shu-shi-fou-cun/)

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

<details><summary>Hint</summary>

```text
1. Loop from i = 0 to arr.length, maintaining in a hashTable the array elements from [0, i - 1].
2. On each step of the loop check if we have seen the element 2 * arr[i] so far.
3. Also check if we have seen arr[i] / 2 in case arr[i] % 2 == 0.
```

</details>

</details>

<details><summary>C</summary>

```c
struct hashTable {
    int value;
    int count;
    UT_hash_handle hh;
};
void freeAll(struct hashTable *pFree) {
    struct hashTable *pCurrent;
    struct hashTable *pTemp;
    HASH_ITER(hh, pFree, pCurrent, pTemp) {
        // printf("%d: %d\n", pFree->value, pFree->count);
        HASH_DEL(pFree, pCurrent);
        free(pCurrent);
    }
}
bool checkIfExist(int *arr, int arrSize) {
    bool retVal = false;

    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    int value;
    int i;
    for (i = 0; i < arrSize; ++i) {
        value = arr[i];

        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &value, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                goto _exit;
            }
            pTemp->value = value;
            pTemp->count = 1;
            HASH_ADD_INT(pHashTable, value, pTemp);
        } else {
            pTemp->count += 1;
        }
    }

    for (i = 0; i < arrSize; ++i) {
        value = arr[i];

        pTemp = NULL;
        if (value == 0) {
            HASH_FIND_INT(pHashTable, &value, pTemp);
            if (pTemp == NULL) {
                break;
            }

            if (pTemp->count > 1) {
                retVal = true;
                break;
            }
        } else if (value != 0) {
            value *= 2;

            HASH_FIND_INT(pHashTable, &value, pTemp);
            if (pTemp != NULL) {
                retVal = true;
                break;
            }
        }
    }

_exit:
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
    bool checkIfExist(vector<int>& arr) {
        bool retVal = false;

        unordered_map<int, int> hashTable;
        for (int value : arr) {
            hashTable[value]++;
        }

        for (int value : arr) {
            if ((value == 0) && (hashTable[value] > 1)) {
                retVal = true;
                break;
            } else if ((value != 0) && (hashTable.count(2 * value) != 0)) {
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
    def checkIfExist(self, arr: List[int]) -> bool:
        retVal = False

        hashTable = defaultdict(int)
        for value in arr:
            hashTable[value] += 1

        for value in arr:
            if (value == 0) and (hashTable[value] > 1):
                retVal = True
                break
            elif (value != 0) and ((2*value) in hashTable):
                retVal = True
                break

        return retVal
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

## [1442. Count Triplets That Can Form Two Arrays of Equal XOR](https://leetcode.com/problems/count-triplets-that-can-form-two-arrays-of-equal-xor/)  1524

- [Official](https://leetcode.com/problems/count-triplets-that-can-form-two-arrays-of-equal-xor/editorial/)
- [Official](https://leetcode.cn/problems/count-triplets-that-can-form-two-arrays-of-equal-xor/solutions/579281/xing-cheng-liang-ge-yi-huo-xiang-deng-sh-jud0/)

<details><summary>Description</summary>

```text
Given an array of integers arr.

We want to select three indices i, j and k where (0 <= i < j <= k < arr.length).

Let's define a and b as follows:
- a = arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1]
- b = arr[j] ^ arr[j + 1] ^ ... ^ arr[k]
Note that ^ denotes the bitwise-xor operation.

Return the number of triplets (i, j and k) Where a == b.

Example 1:
Input: arr = [2,3,1,6,7]
Output: 4
Explanation: The triplets are (0,1,2), (0,2,2), (2,3,4) and (2,4,4)

Example 2:
Input: arr = [1,1,1,1,1]
Output: 10

Constraints:
1 <= arr.length <= 300
1 <= arr[i] <= 10^8
```

<details><summary>Hint</summary>

```text
1. We are searching for sub-array of length ≥ 2 and we need to split it to 2 non-empty arrays
   so that the xor of the first array is equal to the xor of the second array.
   This is equivalent to searching for sub-array with xor = 0.
2. Keep the prefix xor of arr in another array, check the xor of all sub-arrays in O(n^2),
   if the xor of sub-array of length x is 0 add x-1 to the answer.
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
int getValue(struct hashTable* pObj, int x) {
    int retVal = 0;

    struct hashTable* pTmp = NULL;
    HASH_FIND_INT(pObj, &x, pTmp);
    if (pTmp != NULL) {
        retVal = pTmp->value;
    }

    return retVal;
}
void addValue(struct hashTable** pObj, int x, int y) {
    struct hashTable* pTmp = NULL;
    HASH_FIND_INT(*pObj, &x, pTmp);
    if (pTmp == NULL) {
        pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
        if (pTmp == NULL) {
            return;
        }
        pTmp->key = x;
        pTmp->value = y;
        HASH_ADD_INT(*pObj, key, pTmp);
    } else {
        pTmp->value += y;
    }
}
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int countTriplets(int* arr, int arrSize) {
    int retVal = 0;

    // Maps to store counts and totals of XOR values encountered
    struct hashTable* pCountHashTable = NULL;
    addValue(&pCountHashTable, 0, 1);
    struct hashTable* pTotalHashTable = NULL;

    // Iterating through the array
    int prefix = 0;
    int i;
    for (i = 0; i < arrSize; ++i) {
        // Calculating XOR prefix
        prefix ^= arr[i];

        // Calculating contribution of current element to the result
        retVal += getValue(pCountHashTable, prefix) * i - getValue(pTotalHashTable, prefix);

        // Updating total count of current XOR value
        addValue(&pTotalHashTable, prefix, i + 1);
        addValue(&pCountHashTable, prefix, 1);
    }

    //
    freeAll(pCountHashTable);
    pCountHashTable = NULL;
    freeAll(pTotalHashTable);
    pTotalHashTable = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int countTriplets(vector<int>& arr) {
        int retVal = 0;

        int arrSize = arr.size();

        // Maps to store counts and totals of XOR values encountered
        unordered_map<int, int> countMap = {{0, 1}};
        unordered_map<int, int> totalMap;

        // Iterating through the array
        int prefix = 0;
        for (int i = 0; i < arrSize; ++i) {
            // Calculating XOR prefix
            prefix ^= arr[i];

            // Calculating contribution of current element to the result
            retVal += countMap[prefix] * i - totalMap[prefix];

            // Updating total count of current XOR value
            totalMap[prefix] += i + 1;
            countMap[prefix] += 1;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def countTriplets(self, arr: List[int]) -> int:
        retVal = 0

        arrSize = len(arr)

        # Dictionaries to store counts and totals of XOR values encountered
        count_map = defaultdict(int)
        count_map[0] = 1
        total_map = defaultdict(int)

        # Iterating through the array
        prefix = 0
        for i in range(arrSize):
            # Calculating XOR prefix
            prefix ^= arr[i]

            # Calculating contribution of current element to the result
            retVal += count_map[prefix] * i - total_map[prefix]

            # Updating total count of current XOR value
            total_map[prefix] += i + 1
            count_map[prefix] += 1

        return retVal
```

</details>

## [1460. Make Two Arrays Equal by Reversing Subarrays](https://leetcode.com/problems/make-two-arrays-equal-by-reversing-subarrays/)  1151

- [Official](https://leetcode.com/problems/make-two-arrays-equal-by-reversing-subarrays/editorial/)
- [Official](https://leetcode.cn/problems/make-two-arrays-equal-by-reversing-subarrays/solutions/1769118/tong-guo-fan-zhuan-zi-shu-zu-shi-liang-g-dueo/)

<details><summary>Description</summary>

```text
You are given two integer arrays of equal length target and arr.
In one step, you can select any non-empty subarray of arr and reverse it.
You are allowed to make any number of steps.

Return true if you can make arr equal to target or false otherwise.

Example 1:
Input: target = [1,2,3,4], arr = [2,4,1,3]
Output: true
Explanation: You can follow the next steps to convert arr to target:
1- Reverse subarray [2,4,1], arr becomes [1,4,2,3]
2- Reverse subarray [4,2], arr becomes [1,2,4,3]
3- Reverse subarray [4,3], arr becomes [1,2,3,4]
There are multiple ways to convert arr to target, this is not the only way to do so.

Example 2:
Input: target = [7], arr = [7]
Output: true
Explanation: arr is equal to target without any reverses.

Example 3:
Input: target = [3,7,9], arr = [3,7,11]
Output: false
Explanation: arr does not have value 9 and it can never be converted to target.

Constraints:
target.length == arr.length
1 <= target.length <= 1000
1 <= target[i] <= 1000
1 <= arr[i] <= 1000
```

<details><summary>Hint</summary>

```text
1. Each element of target should have a corresponding element in arr,
   and if it doesn't have a corresponding element, return false.
2. To solve it easiely you can sort the two arrays and check if they are equal.
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
void addValue(struct hashTable** pObj, int key, int value) {
    struct hashTable* pTmp = NULL;
    HASH_FIND_INT(*pObj, &key, pTmp);
    if (pTmp == NULL) {
        pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
        if (pTmp == NULL) {
            perror("malloc");
            return;
        }
        pTmp->key = key;
        pTmp->value = 1;
        HASH_ADD_INT(*pObj, key, pTmp);
    } else {
        pTmp->value += value;
    }
}
bool canBeEqual(int* target, int targetSize, int* arr, int arrSize) {
    bool retVal = true;

    struct hashTable* pCountHashTable = NULL;
    int i;
    for (i = 0; i < targetSize; ++i) {
        addValue(&pCountHashTable, target[i], 1);
    }
    for (i = 0; i < arrSize; ++i) {
        addValue(&pCountHashTable, arr[i], -1);
    }

    struct hashTable* pCurrent = NULL;
    struct hashTable* pTmp = NULL;
    HASH_ITER(hh, pCountHashTable, pCurrent, pTmp) {
        if (pCountHashTable->value != 0) {
            retVal = false;
        }
        HASH_DEL(pCountHashTable, pCurrent);
        free(pCurrent);
        pCurrent = NULL;
    }
    pTmp = NULL;
    pCountHashTable = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    bool canBeEqual(vector<int>& target, vector<int>& arr) {
        bool retVal = true;

        unordered_map<int, int> hashTable;
        for (int value : target) {
            hashTable[value] += 1;
        }
        for (int value : arr) {
            hashTable[value] -= 1;
        }

        for (auto& value : hashTable) {
            if (value.second != 0) {
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
    def canBeEqual(self, target: List[int], arr: List[int]) -> bool:
        retVal = True

        hashTable = defaultdict(int)
        for value in target:
            hashTable[value] += 1
        for value in arr:
            hashTable[value] -= 1

        for value in hashTable.values():
            if value != 0:
                retVal = False
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

## [1497. Check If Array Pairs Are Divisible by k](https://leetcode.com/problems/check-if-array-pairs-are-divisible-by-k/)  1787

- [Official](https://leetcode.com/problems/check-if-array-pairs-are-divisible-by-k/editorial/)
- [Official](https://leetcode.cn/problems/check-if-array-pairs-are-divisible-by-k/solutions/310418/jian-cha-shu-zu-dui-shi-fou-ke-yi-bei-k-zheng-chu-/)

<details><summary>Description</summary>

```text
Given an array of integers arr of even length n and an integer k.
We want to divide the array into exactly n / 2 pairs such that the sum of each pair is divisible by k.
Return true If you can find a way to do that or false otherwise.

Example 1:
Input: arr = [1,2,3,4,5,10,6,7,8,9], k = 5
Output: true
Explanation: Pairs are (1,9),(2,8),(3,7),(4,6) and (5,10).

Example 2:
Input: arr = [1,2,3,4,5,6], k = 7
Output: true
Explanation: Pairs are (1,6),(2,5) and(3,4).

Example 3:
Input: arr = [1,2,3,4,5,6], k = 10
Output: false
Explanation: You can try all possible pairs to see that
there is no way to divide arr into 3 pairs each with sum divisible by 10.

Constraints:
arr.length == n
1 <= n <= 10^5
n is even.
-10^9 <= arr[i] <= 10^9
1 <= k <= 10^5
```

<details><summary>Hint</summary>

```text
1. Keep an array of the frequencies of ((x % k) + k) % k for each x in arr.
2. for each i in [0, k - 1] we need to check if freq[i] == freq[k - i]
3. Take care of the case when i == k - i and when i == 0
```

</details>

</details>

<details><summary>C</summary>

```c
bool canArrange(int* arr, int arrSize, int k) {
    bool retVal = false;

    int remainderCount[k];
    memset(remainderCount, 0, sizeof(remainderCount));

    int remainder;
    int i;
    for (i = 0; i < arrSize; ++i) {
        remainder = (arr[i] % k + k) % k;
        remainderCount[remainder]++;
    }

    for (i = 0; i < arrSize; ++i) {
        remainder = (arr[i] % k + k) % k;
        if (remainder == 0) {
            if (remainderCount[remainder] % 2 == 1) {
                return retVal;
            }
        } else if (remainderCount[remainder] != remainderCount[k - remainder]) {
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
    bool canArrange(vector<int>& arr, int k) {
        bool retVal = false;

        unordered_map<int, int> remainderCount;
        for (auto i : arr) {
            remainderCount[(i % k + k) % k]++;
        }

        for (auto i : arr) {
            int remainder = (i % k + k) % k;

            if (remainder == 0) {
                if (remainderCount[remainder] % 2 == 1) {
                    return retVal;
                }
            } else if (remainderCount[remainder] != remainderCount[k - remainder]) {
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
    def canArrange(self, arr: List[int], k: int) -> bool:
        retVal = False

        remainderCount = {}
        for i in arr:
            remainder = (i % k + k) % k
            remainderCount[remainder] = remainderCount.get(remainder, 0) + 1

        for i in arr:
            remainder = (i % k + k) % k
            if remainder == 0:
                if remainderCount[remainder] % 2 == 1:
                    return retVal
            elif remainderCount[remainder] != remainderCount.get(k - remainder, 0):
                return retVal
        retVal = True

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

## [1624. Largest Substring Between Two Equal Characters](https://leetcode.com/problems/largest-substring-between-two-equal-characters/)  1281

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

## [1684. Count the Number of Consistent Strings](https://leetcode.com/problems/count-the-number-of-consistent-strings/)  1288

- [Official](https://leetcode.com/problems/count-the-number-of-consistent-strings/editorial/)
- [Official](https://leetcode.cn/problems/count-the-number-of-consistent-strings/solutions/1953831/tong-ji-yi-zhi-zi-fu-chuan-de-shu-mu-by-38356/)

<details><summary>Description</summary>

```text
You are given a string allowed consisting of distinct characters and an array of strings words.
A string is consistent if all characters in the string appear in the string allowed.

Return the number of consistent strings in the array words.

Example 1:
Input: allowed = "ab", words = ["ad","bd","aaab","baa","badab"]
Output: 2
Explanation: Strings "aaab" and "baa" are consistent since they only contain characters 'a' and 'b'.

Example 2:
Input: allowed = "abc", words = ["a","b","c","ab","ac","bc","abc"]
Output: 7
Explanation: All strings are consistent.

Example 3:
Input: allowed = "cad", words = ["cc","acd","b","ba","bac","bad","ac","d"]
Output: 4
Explanation: Strings "cc", "acd", "ac", and "d" are consistent.

Constraints:
1 <= words.length <= 10^4
1 <= allowed.length <= 26
1 <= words[i].length <= 10
The characters in allowed are distinct.
words[i] and allowed contain only lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. A string is incorrect if it contains a character that is not allowed
2. Constraints are small enough for brute force
```

</details>

</details>

<details><summary>C</summary>

```c
int countConsistentStrings(char *allowed, char **words, int wordsSize) {
    int retVal = 0;

    int i, j;

    int allowedChars[26];  // words[i] and allowed contain only lowercase English letters.
    memset(allowedChars, 0, sizeof(allowedChars));
    int allowedSize = strlen(allowed);
    for (i = 0; i < allowedSize; ++i) {
        allowedChars[allowed[i] - 'a'] = 1;
    }

    int wordSize;
    int isConsistent;
    for (i = 0; i < wordsSize; ++i) {
        isConsistent = 1;
        wordSize = strlen(words[i]);
        for (j = 0; j < wordSize; ++j) {
            if (allowedChars[words[i][j] - 'a'] == 0) {
                isConsistent = 0;
                break;
            }
        }
        if (isConsistent == 1) {
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
    int countConsistentStrings(string allowed, vector<string>& words) {
        int retVal = 0;

        vector<int> allowedChars(26, 0);  // words[i] and allowed contain only lowercase English letters.
        for (char c : allowed) {
            allowedChars[c - 'a'] = 1;
        }

        for (string word : words) {
            int isConsistent = 1;
            for (char c : word) {
                if (allowedChars[c - 'a'] == 0) {
                    isConsistent = 0;
                    break;
                }
            }
            if (isConsistent == 1) {
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
    def countConsistentStrings(self, allowed: str, words: List[str]) -> int:
        retVal = 0

        # words[i] and allowed contain only lowercase English letters.
        allowedChars = [0] * 26
        for c in allowed:
            allowedChars[ord(c)-ord('a')] = 1

        for word in words:
            isConsistent = 1
            for c in word:
                if allowedChars[ord(c)-ord('a')] == 0:
                    isConsistent = 0
                    break
            if isConsistent == 1:
                retVal += 1

        return retVal
```

</details>

## [1726. Tuple with Same Product](https://leetcode.com/problems/tuple-with-same-product/)  1530

- [Official](https://leetcode.com/problems/tuple-with-same-product/editorial/)
- [Official](https://leetcode.cn/problems/tuple-with-same-product/solutions/2470655/tong-ji-yuan-zu-by-leetcode-solution-7yyy/)

<details><summary>Description</summary>

```text
Given an array nums of distinct positive integers,
return the number of tuples (a, b, c, d) such that a * b = c * d
where a, b, c, and d are elements of nums, and a != b != c != d.

Example 1:
Input: nums = [2,3,4,6]
Output: 8
Explanation: There are 8 valid tuples:
(2,6,3,4) , (2,6,4,3) , (6,2,3,4) , (6,2,4,3)
(3,4,2,6) , (4,3,2,6) , (3,4,6,2) , (4,3,6,2)

Example 2:
Input: nums = [1,2,4,5,10]
Output: 16
Explanation: There are 16 valid tuples:
(1,10,2,5) , (1,10,5,2) , (10,1,2,5) , (10,1,5,2)
(2,5,1,10) , (2,5,10,1) , (5,2,1,10) , (5,2,10,1)
(2,10,4,5) , (2,10,5,4) , (10,2,4,5) , (10,2,5,4)
(4,5,2,10) , (4,5,10,2) , (5,4,2,10) , (5,4,10,2)

Constraints:
1 <= nums.length <= 1000
1 <= nums[i] <= 10^4
All elements in nums are distinct.
```

<details><summary>Hint</summary>

```text
1. Note that all of the integers are distinct.
   This means that each time a product is formed it must be formed by two unique integers.
2. Count the frequency of each product of 2 distinct numbers. Then calculate the permutations formed.
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
int tupleSameProduct(int *nums, int numsSize) {
    int retVal = 0;

    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    int productValue;
    for (int firstIndex = 0; firstIndex < numsSize; firstIndex++) {
        for (int secondIndex = firstIndex + 1; secondIndex < numsSize; secondIndex++) {
            productValue = nums[firstIndex] * nums[secondIndex];

            pTemp = NULL;
            HASH_FIND_INT(pHashTable, &productValue, pTemp);
            if (pTemp == NULL) {
                pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
                if (pTemp == NULL) {
                    perror("malloc");
                    freeAll(pHashTable);
                    return retVal;
                }
                pTemp->key = productValue;
                pTemp->value = 1;
                HASH_ADD_INT(pHashTable, key, pTemp);
            } else {
                pTemp->value += 1;
            }
        }
    }

    struct hashTable *pCurrent;
    HASH_ITER(hh, pHashTable, pCurrent, pTemp) {
        retVal += 8 * ((pHashTable->value - 1) * pHashTable->value / 2);  // each pair can form 8 tuples
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
    int tupleSameProduct(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        unordered_map<int, int> pairProductsFrequency;
        for (int firstIndex = 0; firstIndex < numsSize; firstIndex++) {
            for (int secondIndex = firstIndex + 1; secondIndex < numsSize; secondIndex++) {
                pairProductsFrequency[nums[firstIndex] * nums[secondIndex]]++;
            }
        }

        for (auto [productValue, productFrequency] : pairProductsFrequency) {
            int pairsOfEqualProduct = (productFrequency - 1) * productFrequency / 2;
            retVal += 8 * pairsOfEqualProduct;  // each pair can form 8 tuples
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def tupleSameProduct(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        pairProductsFrequency = {}
        for firstIndex in range(numsSize):
            for secondIndex in range(firstIndex + 1, numsSize):
                productValue = nums[firstIndex] * nums[secondIndex]
                if productValue in pairProductsFrequency:
                    pairProductsFrequency[productValue] += 1
                else:
                    pairProductsFrequency[productValue] = 1

        for productFrequency in pairProductsFrequency.values():
            pairsOfEqualProduct = ((productFrequency - 1) * productFrequency // 2)
            retVal += 8 * pairsOfEqualProduct  # each pair can form 8 tuples

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
