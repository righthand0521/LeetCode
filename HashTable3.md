# [Hash Table](https://en.wikipedia.org/wiki/Hash_table)

- [uthash](https://troydhanson.github.io/uthash/)

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

## [2053. Kth Distinct String in an Array](https://leetcode.com/problems/kth-distinct-string-in-an-array/)  1350

- [Official](https://leetcode.com/problems/kth-distinct-string-in-an-array/editorial/)
- [Official](https://leetcode.cn/problems/kth-distinct-string-in-an-array/solutions/1077086/zha-zhu-zhi-jian-de-pan-zi-by-leetcode-s-r92u/)

<details><summary>Description</summary>

```text
A distinct string is a string that is present only once in an array.

Given an array of strings arr, and an integer k, return the kth distinct string present in arr.
If there are fewer than k distinct strings, return an empty string "".

Note that the strings are considered in the order in which they appear in the array.

Example 1:
Input: arr = ["d","b","c","b","c","a"], k = 2
Output: "a"
Explanation:
The only distinct strings in arr are "d" and "a".
"d" appears 1st, so it is the 1st distinct string.
"a" appears 2nd, so it is the 2nd distinct string.
Since k == 2, "a" is returned.

Example 2:
Input: arr = ["aaa","aa","a"], k = 1
Output: "aaa"
Explanation:
All strings in arr are distinct, so the 1st string "aaa" is returned.

Example 3:
Input: arr = ["a","b","a"], k = 3
Output: ""
Explanation:
The only distinct string is "b". Since there are fewer than 3 distinct strings, we return an empty string "".

Constraints:
1 <= k <= arr.length <= 1000
1 <= arr[i].length <= 5
arr[i] consists of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Try 'mapping' the strings to check if they are unique or not.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MAX_LENGTH (8)  // 1 <= arr[i].length <= 5
struct hashTable {
    char key[MAX_LENGTH];
    int count;
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
char* kthDistinct(char** arr, int arrSize, int k) {
    char* pRetVal = "";

    struct hashTable* pHashTable = NULL;

    char pStr[MAX_LENGTH];
    struct hashTable* pTmp;
    int i;
    for (i = 0; i < arrSize; ++i) {
        memset(pStr, 0, sizeof(pStr));
        snprintf(pStr, sizeof(pStr), "%s", arr[i]);

        pTmp = NULL;
        HASH_FIND_STR(pHashTable, pStr, pTmp);
        if (pTmp != NULL) {
            pTmp->count++;
            continue;
        }

        pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
        if (pTmp == NULL) {
            perror("malloc");
            goto exit;
        }
        snprintf(pTmp->key, MAX_LENGTH, "%s", pStr);
        pTmp->count = 1;
        HASH_ADD_STR(pHashTable, key, pTmp);
    }

    for (i = 0; i < arrSize; ++i) {
        memset(pStr, 0, sizeof(pStr));
        snprintf(pStr, sizeof(pStr), "%s", arr[i]);

        pTmp = NULL;
        HASH_FIND_STR(pHashTable, pStr, pTmp);
        if (pTmp == NULL) {
            continue;
        }

        if (pTmp->count != 1) {
            continue;
        }

        k--;
        if (k == 0) {
            pRetVal = arr[i];
            break;
        }
    }

exit:
    //
    freeAll(pHashTable);
    pHashTable = NULL;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string kthDistinct(vector<string>& arr, int k) {
        string retVal = "";

        unordered_map<string, int> hashTable;
        for (string s : arr) {
            hashTable[s] += 1;
        }

        for (string s : arr) {
            if (hashTable[s] > 1) {
                continue;
            }

            k--;
            if (k == 0) {
                retVal = s;
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
    def kthDistinct(self, arr: List[str], k: int) -> str:
        retVal = ""

        hashTable = defaultdict(int)
        for s in arr:
            hashTable[s] += 1

        for key, value in hashTable.items():
            if value != 1:
                continue

            k -= 1
            if k == 0:
                retVal = key
                break

        return retVal
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

## [2491. Divide Players Into Teams of Equal Skill](https://leetcode.com/problems/divide-players-into-teams-of-equal-skill/)  1323

- [Official](https://leetcode.com/problems/divide-players-into-teams-of-equal-skill/editorial/)

<details><summary>Description</summary>

```text
You are given a positive integer array skill of even length n where skill[i] denotes the skill of the ith player.
Divide the players into n / 2 teams of size 2 such that the total skill of each team is equal.

The chemistry of a team is equal to the product of the skills of the players on that team.

Return the sum of the chemistry of all the teams,
or return -1 if there is no way to divide the players into teams such that the total skill of each team is equal.

Example 1:
Input: skill = [3,2,5,1,3,4]
Output: 22
Explanation:
Divide the players into the following teams: (1, 5), (2, 4), (3, 3), where each team has a total skill of 6.
The sum of the chemistry of all the teams is: 1 * 5 + 2 * 4 + 3 * 3 = 5 + 8 + 9 = 22.

Example 2:
Input: skill = [3,4]
Output: 12
Explanation:
The two players form a team with a total skill of 7.
The chemistry of the team is 3 * 4 = 12.

Example 3:
Input: skill = [1,1,2,3]
Output: -1
Explanation:
There is no way to divide the players into teams such that the total skill of each team is equal.

Constraints:
2 <= skill.length <= 10^5
skill.length is even.
1 <= skill[i] <= 1000
```

<details><summary>Hint</summary>

```text
1. Try sorting the skill array.
2. It is always optimal to pair the weakest available player with the strongest available player.
```

</details>

</details>

<details><summary>C</summary>

```c
long long dividePlayers(int* skill, int skillSize) {
    long long retVal = -1;

    int totalSkill = 0;
    int skillFrequency[1001];  // 1 <= skill[i] <= 1000
    memset(skillFrequency, 0, sizeof(skillFrequency));
    for (int i = 0; i < skillSize; ++i) {
        totalSkill += skill[i];
        skillFrequency[skill[i]]++;
    }
    if (totalSkill % (skillSize / 2) != 0) {
        return retVal;
    }

    int partnerSkill;
    int targetTeamSkill = totalSkill / (skillSize / 2);
    long long totalChemistry = 0;
    for (int i = 0; i < skillSize; ++i) {
        partnerSkill = targetTeamSkill - skill[i];
        if (skillFrequency[partnerSkill] == 0) {
            return retVal;
        }

        totalChemistry += (long long)skill[i] * (long long)partnerSkill;
        skillFrequency[partnerSkill]--;
    }
    retVal = totalChemistry / 2;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long dividePlayers(vector<int>& skill) {
        long long retVal = -1;

        int skillSize = skill.size();

        int totalSkill = 0;
        vector<int> skillFrequency(1001, 0);  // 1 <= skill[i] <= 1000
        for (int playerSkill : skill) {
            totalSkill += playerSkill;
            skillFrequency[playerSkill]++;
        }
        if (totalSkill % (skillSize / 2) != 0) {
            return retVal;
        }

        int targetTeamSkill = totalSkill / (skillSize / 2);
        long long totalChemistry = 0;
        for (int playerSkill : skill) {
            int partnerSkill = targetTeamSkill - playerSkill;
            if (skillFrequency[partnerSkill] == 0) {
                return retVal;
            }

            totalChemistry += (long long)playerSkill * (long long)partnerSkill;
            skillFrequency[partnerSkill]--;
        }
        retVal = totalChemistry / 2;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def dividePlayers(self, skill: List[int]) -> int:
        retVal = -1

        skillSize = len(skill)

        totalSkill = sum(skill)
        if totalSkill % (skillSize // 2) != 0:
            return retVal

        skillFrequency = [0] * 1001  # // 1 <= skill[i] <= 1000
        for playerSkill in skill:
            skillFrequency[playerSkill] += 1

        targetTeamSkill = totalSkill // (skillSize // 2)
        totalChemistry = 0
        for playerSkill in skill:
            partnerSkill = targetTeamSkill - playerSkill
            if skillFrequency[partnerSkill] == 0:
                return retVal

            totalChemistry += (playerSkill * partnerSkill)
            skillFrequency[partnerSkill] -= 1

        retVal = totalChemistry // 2

        return retVal
```

</details>

## [2501. Longest Square Streak in an Array](https://leetcode.com/problems/longest-square-streak-in-an-array/)  1479

- [Official](https://leetcode.com/problems/longest-square-streak-in-an-array/editorial/)

<details><summary>Description</summary>

```text
You are given an integer array nums. A subsequence of nums is called a square streak if:
- The length of the subsequence is at least 2, and
- after sorting the subsequence, each element (except the first element) is the square of the previous number.

Return the length of the longest square streak in nums, or return -1 if there is no square streak.

A subsequence is an array that can be derived from another array by deleting some
or no elements without changing the order of the remaining elements.

Example 1:
Input: nums = [4,3,6,16,8,2]
Output: 3
Explanation: Choose the subsequence [4,16,2]. After sorting it, it becomes [2,4,16].
- 4 = 2 * 2.
- 16 = 4 * 4.
Therefore, [4,16,2] is a square streak.
It can be shown that every subsequence of length 4 is not a square streak.

Example 2:
Input: nums = [2,3,5,6,7]
Output: -1
Explanation: There is no square streak in nums so return -1.

Constraints:
2 <= nums.length <= 10^5
2 <= nums[i] <= 10^5
```

<details><summary>Hint</summary>

```text
1. With the constraints, the length of the longest square streak possible is 5.
2. Store the elements of nums in a set to quickly check if it exists.
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
int longestSquareStreak(int *nums, int numsSize) {
    int retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    int root, squareStreak;
    int i;
    for (i = 0; i < numsSize; ++i) {
        root = (int)sqrt(nums[i]);
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &root, pTemp);
        if ((root * root == nums[i]) && (pTemp != NULL)) {
            squareStreak = pTemp->value + 1;
        } else {
            squareStreak = 1;
        }

        root = nums[i];
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &root, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                return retVal;
            }
            pTemp->key = root;
            pTemp->value = squareStreak;
            HASH_ADD_INT(pHashTable, key, pTemp);
        } else {
            pTemp->value = squareStreak;
        }
    }

    struct hashTable *pCurrent = NULL;
    pTemp = NULL;
    HASH_ITER(hh, pHashTable, pCurrent, pTemp) {
        retVal = fmax(retVal, pHashTable->value);
        HASH_DEL(pHashTable, pCurrent);
        free(pCurrent);
    }
    if (retVal == 1) {
        retVal = -1;  // return -1 if there is no square streak.
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int longestSquareStreak(vector<int>& nums) {
        int retVal = 0;

        sort(nums.begin(), nums.end());

        unordered_map<int, int> hashTable;
        for (int num : nums) {
            int root = (int)sqrt(num);
            if ((root * root == num) && (hashTable.find(root) != hashTable.end())) {
                hashTable[num] = hashTable[root] + 1;
            } else {
                hashTable[num] = 1;
            }
        }

        for (auto iterator = hashTable.begin(); iterator != hashTable.end(); ++iterator) {
            retVal = max(retVal, iterator->second);
        }
        if (retVal == 1) {
            retVal = -1;  // return -1 if there is no square streak.
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def longestSquareStreak(self, nums: List[int]) -> int:
        retVal = 0

        nums.sort()

        hashTable = defaultdict(int)
        for num in nums:
            root = int(num ** 0.5)
            if (root * root == num) and (root in hashTable):
                hashTable[num] = hashTable[root] + 1
            else:
                hashTable[num] = 1

        retVal = max(hashTable.values())
        if retVal == 1:
            retVal = -1  # return -1 if there is no square streak.

        return retVal
```

</details>

## [2554. Maximum Number of Integers to Choose From a Range I](https://leetcode.com/problems/maximum-number-of-integers-to-choose-from-a-range-i/)  1333

- [Official](https://leetcode.com/problems/maximum-number-of-integers-to-choose-from-a-range-i/editorial/)

<details><summary>Description</summary>

```text
You are given an integer array banned and two integers n and maxSum.
You are choosing some number of integers following the below rules:
- The chosen integers have to be in the range [1, n].
- Each integer can be chosen at most once.
- The chosen integers should not be in the array banned.
- The sum of the chosen integers should not exceed maxSum.

Return the maximum number of integers you can choose following the mentioned rules.

Example 1:
Input: banned = [1,6,5], n = 5, maxSum = 6
Output: 2
Explanation: You can choose the integers 2 and 4.
2 and 4 are from the range [1, 5], both did not appear in banned, and their sum is 6, which did not exceed maxSum.

Example 2:
Input: banned = [1,2,3,4,5,6,7], n = 8, maxSum = 1
Output: 0
Explanation: You cannot choose any integer while following the mentioned conditions.

Example 3:
Input: banned = [11], n = 7, maxSum = 50
Output: 7
Explanation: You can choose the integers 1, 2, 3, 4, 5, 6, and 7.
They are from the range [1, 7], all did not appear in banned, and their sum is 28, which did not exceed maxSum.

Constraints:
1 <= banned.length <= 10^4
1 <= banned[i], n <= 10^4
1 <= maxSum <= 10^9
```

<details><summary>Hint</summary>

```text
1. Keep the banned numbers that are less than n in a set.
2. Loop over the numbers from 1 to n and if the number is not banned, use it.
3. Keep adding numbers while they are not banned, and their sum is less than k.
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
int maxCount(int *banned, int bannedSize, int n, int maxSum) {
    int retVal = 0;

    // Store banned numbers in an unordered_set
    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    int key;
    int i;
    for (i = 0; i < bannedSize; ++i) {
        key = banned[i];

        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &key, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                return retVal;
            }
            pTemp->key = key;
            pTemp->value = 1;
            HASH_ADD_INT(pHashTable, key, pTemp);
        } else {
            pTemp->value += 1;
        }
    }

    for (i = 1; i <= n; ++i) {
        // Skip banned numbers
        key = i;
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &key, pTemp);
        if (pTemp != NULL) {
            continue;
        }

        // Return if adding current number exceeds maxSum
        if (maxSum - i < 0) {
            break;
        }

        // Include current number
        maxSum -= i;
        retVal++;
    }

    //
    freeAll(pHashTable);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxCount(vector<int>& banned, int n, int maxSum) {
        int retVal = 0;

        // Store banned numbers in an unordered_set
        unordered_set<int> bannedSet(banned.begin(), banned.end());

        for (int num = 1; num <= n; num++) {
            // Skip banned numbers
            if (bannedSet.count(num) != 0) {
                continue;
            }

            // Return if adding current number exceeds maxSum
            if (maxSum - num < 0) {
                break;
            }

            // Include current number
            maxSum -= num;
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
    def maxCount(self, banned: List[int], n: int, maxSum: int) -> int:
        retVal = 0

        # Store banned numbers in a set for quick lookup
        bannedSet = set(banned)

        for num in range(1, n + 1):
            # Skip banned numbers
            if num in bannedSet:
                continue

            # Return if adding the current number exceeds maxSum
            if maxSum - num < 0:
                break

            # Include current number
            maxSum -= num
            retVal += 1

        return retVal
```

</details>

## [2570. Merge Two 2D Arrays by Summing Values](https://leetcode.com/problems/merge-two-2d-arrays-by-summing-values/)  1281

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

## [3005. Count Elements With Maximum Frequency](https://leetcode.com/problems/count-elements-with-maximum-frequency/)  1216

- [Official](https://leetcode.com/problems/count-elements-with-maximum-frequency/editorial/)

<details><summary>Description</summary>

```text
You are given an array nums consisting of positive integers.

Return the total frequencies of elements in nums such that those elements all have the maximum frequency.

The frequency of an element is the number of occurrences of that element in the array.

Example 1:
Input: nums = [1,2,2,3,1,4]
Output: 4
Explanation: The elements 1 and 2 have a frequency of 2 which is the maximum frequency in the array.
So the number of elements in the array with maximum frequency is 4.

Example 2:
Input: nums = [1,2,3,4,5]
Output: 5
Explanation: All elements of the array have a frequency of 1 which is the maximum.
So the number of elements in the array with maximum frequency is 5.

Constraints:
1 <= nums.length <= 100
1 <= nums[i] <= 100
```

<details><summary>Hint</summary>

```text
1. Find frequencies of all elements of the array.
2. Find the elements that have the maximum frequencies and count their total occurrences.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
int maxFrequencyElements(int* nums, int numsSize) {
    int retVal = 0;

#define MAX_NUMS_SIZE (100)  // 1 <= nums.length <= 100; 1 <= nums[i] <= 100;
    int hashTable[MAX_NUMS_SIZE];
    memset(hashTable, 0, sizeof(hashTable));

    int i;
    for (i = 0; i < numsSize; ++i) {
        hashTable[nums[i] - 1]++;
    }
    qsort(hashTable, MAX_NUMS_SIZE, sizeof(int), compareInteger);

    int frequency;
    int maxFrequency = 0;
    for (i = 0; i < MAX_NUMS_SIZE; ++i) {
        frequency = hashTable[i];
        if (frequency >= maxFrequency) {
            maxFrequency = frequency;
            retVal += frequency;
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
   private:
    int numsMAXsize = 100;  // 1 <= nums.length <= 100; 1 <= nums[i] <= 100;

   public:
    int maxFrequencyElements(vector<int>& nums) {
        int retVal = 0;

        vector<int> hashTable(numsMAXsize, 0);
        for (int num : nums) {
            hashTable[num - 1]++;
        }
        sort(hashTable.begin(), hashTable.end(), greater());

        int maxFrequency = 0;
        for (int frequency : hashTable) {
            if (frequency >= maxFrequency) {
                maxFrequency = frequency;
                retVal += frequency;
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
    def maxFrequencyElements(self, nums: List[int]) -> int:
        retVal = 0

        frequency = Counter(nums).most_common()

        previous = 0
        for _, value in frequency:
            if value >= previous:
                previous = value
                retVal += value
            else:
                break

        return retVal
```

</details>
