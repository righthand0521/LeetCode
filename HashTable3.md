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

## [2094. Finding 3-Digit Even Numbers](https://leetcode.com/problems/finding-3-digit-even-numbers/)  1454

- [Official](https://leetcode.com/problems/finding-3-digit-even-numbers/editorial/)
- [Official](https://leetcode.cn/problems/finding-3-digit-even-numbers/solutions/1140756/zhao-chu-3-wei-ou-shu-by-leetcode-soluti-hptf/)

<details><summary>Description</summary>

```text
You are given an integer array digits, where each element is a digit. The array may contain duplicates.

You need to find all the unique integers that follow the given requirements:
- The integer consists of the concatenation of three elements from digits in any arbitrary order.
- The integer does not have leading zeros.
- The integer is even.

For example, if the given digits were [1, 2, 3], integers 132 and 312 follow the requirements.

Return a sorted array of the unique integers.

Example 1:
Input: digits = [2,1,3,0]
Output: [102,120,130,132,210,230,302,310,312,320]
Explanation: All the possible integers that follow the requirements are in the output array.
Notice that there are no odd integers or integers with leading zeros.

Example 2:
Input: digits = [2,2,8,8,2]
Output: [222,228,282,288,822,828,882]
Explanation: The same digit can be used as many times as it appears in digits.
In this example, the digit 8 is used twice each time in 288, 828, and 882.

Example 3:
Input: digits = [3,7,5]
Output: []
Explanation: No even integers can be formed using the given digits.

Constraints:
3 <= digits.length <= 100
0 <= digits[i] <= 9
```

<details><summary>Hint</summary>

```text
1. The range of possible answers includes all even numbers between 100 and 999 inclusive.
   Could you check each possible answer to see if it could be formed from the digits in the array?
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
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
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findEvenNumbers(int* digits, int digitsSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    struct hashTable* pHashTable = NULL;
    struct hashTable* pTemp;
    int num;
    for (int i = 0; i < digitsSize; ++i) {
        for (int j = 0; j < digitsSize; ++j) {
            for (int k = 0; k < digitsSize; ++k) {
                if (i == j || j == k || i == k) {
                    continue;
                }
                num = digits[i] * 100 + digits[j] * 10 + digits[k];
                if ((num < 100) || (num % 2 != 0)) {
                    continue;
                }

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
                    HASH_ADD_INT(pHashTable, key, pTemp);
                }
            }
        }
    }

    pRetVal = (int*)calloc(HASH_COUNT(pHashTable), sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        freeAll(pHashTable);
        return pRetVal;
    }
    struct hashTable* pCurrent;
    pTemp = NULL;
    HASH_ITER(hh, pHashTable, pCurrent, pTemp) {
        pRetVal[(*returnSize)++] = pHashTable->key;
        HASH_DEL(pHashTable, pCurrent);
        free(pCurrent);
    }
    qsort(pRetVal, (*returnSize), sizeof(int), compareInteger);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> findEvenNumbers(vector<int>& digits) {
        vector<int> retVal;

        unordered_set<int> nums;
        int digitsSize = digits.size();
        for (int i = 0; i < digitsSize; ++i) {
            for (int j = 0; j < digitsSize; ++j) {
                for (int k = 0; k < digitsSize; ++k) {
                    if (i == j || j == k || i == k) {
                        continue;
                    }
                    int num = digits[i] * 100 + digits[j] * 10 + digits[k];
                    if ((num >= 100) && (num % 2 == 0)) {
                        nums.insert(num);
                    }
                }
            }
        }

        for (const int num : nums) {
            retVal.emplace_back(num);
        }
        sort(retVal.begin(), retVal.end());

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def findEvenNumbers(self, digits: List[int]) -> List[int]:
        retVal = []

        nums = set()
        digitsSize = len(digits)
        for i in range(digitsSize):
            for j in range(digitsSize):
                for k in range(digitsSize):
                    if (i == j) or (i == k) or (j == k):
                        continue
                    num = digits[i] * 100 + digits[j] * 10 + digits[k]
                    if (num >= 100) and (num % 2 == 0):
                        nums.add(num)
        retVal = sorted(nums)

        return retVal
```

</details>

## [2131. Longest Palindrome by Concatenating Two Letter Words](https://leetcode.com/problems/longest-palindrome-by-concatenating-two-letter-words/)  1556

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

<details><summary>Hint</summary>

```text
1. A palindrome must be mirrored over the center. Suppose we have a palindrome.
   If we prepend the word "ab" on the left, what must we append on the right to keep it a palindrome?
2. We must append "ba" on the right.
   The number of times we can do this is the minimum of (occurrences of "ab") and (occurrences of "ba").
3. For words that are already palindromes,
   e.g. "aa", we can prepend and append these in pairs as described in the previous hint.
   We can also use exactly one in the middle to form an even longer palindrome.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MAX_LETTERS (26)  // words[i] consists of lowercase English letters.
int longestPalindrome(char** words, int wordsSize) {
    int retVal = 0;

    int frequencySize = MAX_LETTERS * MAX_LETTERS;  // words[i].length == 2
    int frequency[frequencySize];
    memset(frequency, 0, sizeof(frequency));
    for (int i = 0; i < wordsSize; i++) {
        int idx = (words[i][0] - 'a') * 26 + (words[i][1] - 'a');
        frequency[idx]++;
    }

    bool middle = false;
    for (int i = 0; i < frequencySize; i++) {
        if (frequency[i] == 0) {
            continue;
        }
        int reverseWord = (i % 26) * 26 + (i / 26);
        if (i == reverseWord) {
            if (frequency[i] % 2 == 1) {
                middle = true;
            }
            retVal += (2 * (frequency[i] / 2 * 2));
        } else if (i > reverseWord) {
            retVal += (4 * fmin(frequency[i], frequency[reverseWord]));
        }
    }
    if (middle == true) {
        retVal += 2;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int longestPalindrome(vector<string>& words) {
        int retVal = 0;

        unordered_map<string, int> frequency;
        for (const string& word : words) {
            frequency[word]++;
        }

        bool middle = false;
        for (const auto& [word, count] : frequency) {
            string reverseWord = string(1, word[1]) + word[0];
            if (word == reverseWord) {
                if (count % 2 == 1) {
                    middle = true;
                }
                retVal += (2 * (count / 2 * 2));
            } else if (word > reverseWord) {
                retVal += (4 * min(count, frequency[reverseWord]));
            }
        }
        if (middle == true) {
            retVal += 2;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def longestPalindrome(self, words: List[str]) -> int:
        retVal = 0

        frequency = Counter(words)

        middle = False
        for word, count in frequency.items():
            reverseWord = word[1] + word[0]
            if word == reverseWord:
                if count % 2 == 1:
                    middle = True
                retVal += (2 * (count // 2 * 2))
            elif word > reverseWord:
                retVal += (4 * min(frequency[word], frequency[reverseWord]))
        if middle == True:
            retVal += 2

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

## [2206. Divide Array Into Equal Pairs](https://leetcode.com/problems/divide-array-into-equal-pairs/)  1223

- [Official](https://leetcode.com/problems/divide-array-into-equal-pairs/editorial/)
- [Official](https://leetcode.cn/problems/divide-array-into-equal-pairs/solutions/1374492/jiang-shu-zu-hua-fen-cheng-xiang-deng-sh-vrd5/)

<details><summary>Description</summary>

```text
You are given an integer array nums consisting of 2 * n integers.

You need to divide nums into n pairs such that:
- Each element belongs to exactly one pair.
- The elements present in a pair are equal.

Return true if nums can be divided into n pairs, otherwise return false.

Example 1:
Input: nums = [3,2,3,2,2,2]
Output: true
Explanation:
There are 6 elements in nums, so they should be divided into 6 / 2 = 3 pairs.
If nums is divided into the pairs (2, 2), (3, 3), and (2, 2), it will satisfy all the conditions.

Example 2:
Input: nums = [1,2,3,4]
Output: false
Explanation:
There is no way to divide nums into 4 / 2 = 2 pairs such that the pairs satisfy every condition.

Constraints:
nums.length == 2 * n
1 <= n <= 500
1 <= nums[i] <= 500
```

<details><summary>Hint</summary>

```text
1. For any number x in the range [1, 500], count the number of elements in nums whose values are equal to x.
2. The elements with equal value can be divided completely into pairs if and only if their count is even.
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
bool divideArray(int *nums, int numsSize) {
    bool retVal = true;

    if ((numsSize % 2) == 1) {
        retVal = false;
        return retVal;
    }

    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    int key;
    for (int i = 0; i < numsSize; ++i) {
        key = nums[i];

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

    pTemp = NULL;
    struct hashTable *pCurrent = NULL;
    HASH_ITER(hh, pHashTable, pCurrent, pTemp) {
        // printf("%d: %d\n", pHashTable->key, pHashTable->value);
        if ((pHashTable->value % 2) == 1) {
            retVal = false;
        }
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
    bool divideArray(vector<int>& nums) {
        bool retVal = true;

        int numsSize = nums.size();
        if ((numsSize % 2) == 1) {
            retVal = false;
            return retVal;
        }

        unordered_map<int, int> hashTable;
        for (int num : nums) {
            hashTable[num]++;
        }
        for (auto [key, value] : hashTable) {
            if ((value % 2) == 1) {
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
    def divideArray(self, nums: List[int]) -> bool:
        retVal = True

        numsSize = len(nums)
        if (numsSize % 2) == 1:
            retVal = False
            return retVal

        hashTable = Counter(nums)
        for times in hashTable.values():
            if (times % 2) == 1:
                retVal = False
                break

        return retVal
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

## [2342. Max Sum of a Pair With Equal Sum of Digits](https://leetcode.com/problems/max-sum-of-a-pair-with-equal-sum-of-digits/)  1308

- [Official](https://leetcode.com/problems/max-sum-of-a-pair-with-equal-sum-of-digits/editorial/)

<details><summary>Description</summary>

```text
You are given a 0-indexed array nums consisting of positive integers.
You can choose two indices i and j, such that i != j,
and the sum of digits of the number nums[i] is equal to that of nums[j].

Return the maximum value of nums[i] + nums[j]
that you can obtain over all possible indices i and j that satisfy the conditions.

Example 1:
Input: nums = [18,43,36,13,7]
Output: 54
Explanation: The pairs (i, j) that satisfy the conditions are:
- (0, 2), both numbers have a sum of digits equal to 9, and their sum is 18 + 36 = 54.
- (1, 4), both numbers have a sum of digits equal to 7, and their sum is 43 + 7 = 50.
So the maximum sum that we can obtain is 54.

Example 2:
Input: nums = [10,12,19,14]
Output: -1
Explanation: There are no two numbers that satisfy the conditions, so we return -1.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. What is the largest possible sum of digits a number can have?
2. Group the array elements by the sum of their digits, and find the largest two elements of each group.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareIntArray(const void* a1, const void* a2) {
    int* p1 = (int*)a1;
    int* p2 = (int*)a2;

    // ascending order
    if (p1[0] == p2[0]) {
        return (p1[1] > p2[1]);
    }

    return (p1[0] > p2[0]);
}
int calculateDigitSum(int num) {
    int retVal = 0;

    while (num > 0) {
        retVal += num % 10;
        num /= 10;
    }

    return retVal;
}
int maximumSum(int* nums, int numsSize) {
    int retVal = -1;

    // Store numbers with their digit sums as pairs
    int digitSumPairsSize = numsSize;
    int digitSumPairs[digitSumPairsSize][2];
    memset(digitSumPairs, 0, sizeof(digitSumPairs));
    for (int i = 0; i < numsSize; ++i) {
        digitSumPairs[i][0] = calculateDigitSum(nums[i]);
        digitSumPairs[i][1] = nums[i];
    }
    // Sort based on digit sums, and if equal, by number value
    qsort(digitSumPairs, digitSumPairsSize, sizeof(digitSumPairs[0]), compareIntArray);

    // Iterate through the sorted array to find the maximum sum of pairs
    for (int index = 1; index < digitSumPairsSize; index++) {
        int currentDigitSum = digitSumPairs[index][0];
        int previousDigitSum = digitSumPairs[index - 1][0];
        // If two consecutive numbers have the same digit sum
        if (currentDigitSum == previousDigitSum) {
            int currentSum = digitSumPairs[index][1] + digitSumPairs[index - 1][1];
            retVal = fmax(retVal, currentSum);
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
    int calculateDigitSum(int num) {
        int retVal = 0;

        while (num > 0) {
            retVal += num % 10;
            num /= 10;
        }

        return retVal;
    }

   public:
    int maximumSum(vector<int>& nums) {
        int retVal = -1;

        // Store numbers with their digit sums as pairs
        vector<pair<int, int>> digitSumPairs;
        for (int number : nums) {
            int digitSum = calculateDigitSum(number);
            digitSumPairs.push_back({digitSum, number});
        }
        sort(digitSumPairs.begin(), digitSumPairs.end());  // Sort based on digit sums, and if equal, by number value

        // Iterate through the sorted array to find the maximum sum of pairs
        int digitSumPairsSize = digitSumPairs.size();
        for (int index = 1; index < digitSumPairsSize; index++) {
            int currentDigitSum = digitSumPairs[index].first;
            int previousDigitSum = digitSumPairs[index - 1].first;
            // If two consecutive numbers have the same digit sum
            if (currentDigitSum == previousDigitSum) {
                int currentSum = digitSumPairs[index].second + digitSumPairs[index - 1].second;
                retVal = max(retVal, currentSum);
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
    def calculateDigitSum(self, num):
        retVal = 0

        while num > 0:
            retVal += num % 10
            num //= 10

        return retVal

    def maximumSum(self, nums: List[int]) -> int:
        retVal = -1

        # Store numbers with their digit sums as pairs
        digitSumPairs = []
        for number in nums:
            digitSum = self.calculateDigitSum(number)
            digitSumPairs.append((digitSum, number))
        digitSumPairs.sort()  # Sort based on digit sums, and if equal, by number value

        # Iterate through the sorted array to find the maximum sum of pairs
        digitSumPairsSize = len(digitSumPairs)
        for index in range(1, digitSumPairsSize):
            currentDigitSum = digitSumPairs[index][0]
            previousDigitSum = digitSumPairs[index - 1][0]
            # If two consecutive numbers have the same digit sum
            if currentDigitSum == previousDigitSum:
                currentSum = digitSumPairs[index][1] + digitSumPairs[index - 1][1]
                retVal = max(retVal, currentSum)

        return retVal
```

</details>

## [2349. Design a Number Container System](https://leetcode.com/problems/design-a-number-container-system/)  1540

- [Official](https://leetcode.com/problems/design-a-number-container-system/editorial/)

<details><summary>Description</summary>

```text
Design a number container system that can do the following:
- Insert or Replace a number at the given index in the system.
- Return the smallest index for the given number in the system.

Implement the NumberContainers class:
- NumberContainers()
  Initializes the number container system.
- void change(int index, int number)
  Fills the container at index with the number. If there is already a number at that index, replace it.
- int find(int number)
  Returns the smallest index for the given number, or -1 if there is no index that is filled by number in the system.

Example 1:
Input
["NumberContainers", "find", "change", "change", "change", "change", "find", "change", "find"]
[[], [10], [2, 10], [1, 10], [3, 10], [5, 10], [10], [1, 20], [10]]
Output
[null, -1, null, null, null, null, 1, null, 2]
Explanation
NumberContainers nc = new NumberContainers();
nc.find(10); // There is no index that is filled with number 10. Therefore, we return -1.
nc.change(2, 10); // Your container at index 2 will be filled with number 10.
nc.change(1, 10); // Your container at index 1 will be filled with number 10.
nc.change(3, 10); // Your container at index 3 will be filled with number 10.
nc.change(5, 10); // Your container at index 5 will be filled with number 10.
nc.find(10); // Number 10 is at the indices 1, 2, 3, and 5.
Since the smallest index that is filled with 10 is 1, we return 1.
nc.change(1, 20); // Your container at index 1 will be filled with number 20.
Note that index 1 was filled with 10 and then replaced with 20.
nc.find(10); // Number 10 is at the indices 2, 3, and 5.
The smallest index that is filled with 10 is 2. Therefore, we return 2.

Constraints:
1 <= index, number <= 10^9
At most 10^5 calls will be made in total to change and find.
```

<details><summary>Hint</summary>

```text
1. Use a hash table to efficiently map each number to all of its indices in the container
   and to map each index to their current number.
2. In addition, you can use ordered set to store all of the indices for each number to solve the find method.
   Do not forget to update the ordered set according to the change method.
```

</details>

</details>

<details><summary>C</summary>

```c
// https://leetcode.cn/problems/design-a-number-container-system/solutions/2830597/cyu-yan-ti-jie-by-6oofy-i3anachhuk-jakh/
typedef struct IndexList {
    int index;
    struct IndexList *next;
} IndexList;
typedef struct ValType {
    int val;
    int minIndex;
    IndexList *head;
    UT_hash_handle hh;
} ValType;
typedef struct IndexType {
    int index;
    int val;
    UT_hash_handle hh;
} IndexType;
typedef struct {
    IndexType *indexDict;
    ValType *valDict;
} NumberContainers;
NumberContainers *numberContainersCreate() {
    NumberContainers *obj = (NumberContainers *)malloc(sizeof(NumberContainers));
    obj->indexDict = NULL;
    obj->valDict = NULL;
    return obj;
}
void numberContainersChange(NumberContainers *obj, int index, int number) {
    IndexType *indexRes = NULL;
    ValType *temp1 = NULL;
    ValType *temp2 = NULL;
    int flag = 0;
    int insertVal = 0;
    HASH_FIND_INT(obj->indexDict, &index, indexRes);
    if (indexRes == NULL) {
        indexRes = malloc(sizeof(IndexType));
        indexRes->index = index;
        indexRes->val = number;
        HASH_ADD_INT(obj->indexDict, index, indexRes);
    } else {
        if (indexRes->val == number) {
            flag = 1;
        } else {
            flag = 2;
            insertVal = indexRes->val;
            indexRes->val = number;
        }
    }
    if (flag == 1) {
        return;
    }
    HASH_FIND_INT(obj->valDict, &number, temp2);
    if (temp2 == NULL) {
        temp2 = malloc(sizeof(ValType));
        temp2->val = number;
        temp2->minIndex = index;
        temp2->head = malloc(sizeof(IndexList));
        temp2->head->index = index;
        temp2->head->next = NULL;
        HASH_ADD_INT(obj->valDict, val, temp2);
    } else {
        IndexList *node1 = malloc(sizeof(IndexList));
        IndexList *cur10 = temp2->head;
        node1->index = index;
        node1->next = cur10;
        temp2->head = node1;
        if (index < temp2->minIndex) {
            temp2->minIndex = index;
        }
    }
    if (flag == 2) {
        HASH_FIND_INT(obj->valDict, &insertVal, temp1);
        IndexList *dummy = malloc(sizeof(IndexList));
        IndexList *node = dummy;
        dummy->next = temp1->head;
        int update = 0;
        if (temp1->minIndex == index) {
            update = 1;
        }
        while (dummy->next) {
            if (dummy->next->index == index) {
                IndexList *temp10 = dummy->next;
                dummy->next = dummy->next->next;
                free(temp10);
                break;
            } else {
                dummy = dummy->next;
            }
        }
        if (node->next == NULL) {
            HASH_DEL(obj->valDict, temp1);
            free(temp1);
        } else {
            temp1->head = node->next;
            if (update == 1) {
                IndexList *node88 = temp1->head;
                temp1->minIndex = node88->index;
                while (node88) {
                    if (node88->index < temp1->minIndex) {
                        temp1->minIndex = node88->index;
                    }
                    node88 = node88->next;
                }
            }
        }
    }
}
int numberContainersFind(NumberContainers *obj, int number) {
    int index = -1;
    ValType *temp2 = NULL;
    HASH_FIND_INT(obj->valDict, &number, temp2);
    if (temp2 != NULL) {
        return temp2->minIndex;
    }
    return index;
}
void numberContainersFree(NumberContainers *obj) {
    IndexType *cur;
    IndexType *nxt;
    HASH_ITER(hh, obj->indexDict, cur, nxt) {
        HASH_DEL(obj->indexDict, cur);
        free(cur);
    }
    ValType *cur2;
    ValType *nxt2;
    HASH_ITER(hh, obj->valDict, cur2, nxt2) {
        HASH_DEL(obj->valDict, cur2);
        while (cur2->head) {
            IndexList *temp = cur2->head;
            cur2->head = cur2->head->next;
            free(temp);
        }
        free(cur2);
    }
    free(obj);
}
/**
 * Your NumberContainers struct will be instantiated and called as such:
 * NumberContainers* obj = numberContainersCreate();
 * numberContainersChange(obj, index, number);
 * int param_2 = numberContainersFind(obj, number);
 * numberContainersFree(obj);
 */
```

</details>

<details><summary>C++</summary>

```c++
class NumberContainers {
   private:
    unordered_map<int, set<int>> numberToIndices;  // Map from number to set of indices
    unordered_map<int, int> indexToNumbers;        // Map from index to number

   public:
    // Constructor: The data structures are already initialized as part of the member variable declarations.
    NumberContainers() {}
    void change(int index, int number) {
        if (indexToNumbers.find(index) != indexToNumbers.end()) {
            int previousNumber = indexToNumbers[index];
            numberToIndices[previousNumber].erase(index);
            if (numberToIndices[previousNumber].empty()) {
                numberToIndices.erase(previousNumber);
            }
        }
        indexToNumbers[index] = number;
        numberToIndices[number].insert(index);
    }
    int find(int number) {
        int retVal = -1;

        if (numberToIndices.find(number) != numberToIndices.end()) {
            // Get the smallest index
            retVal = *numberToIndices[number].begin();
        }

        return retVal;
    }
};
/**
 * Your NumberContainers object will be instantiated and called as such:
 * NumberContainers* obj = new NumberContainers();
 * obj->change(index,number);
 * int param_2 = obj->find(number);
 */
```

</details>

<details><summary>Python3</summary>

```python
class NumberContainers:
    def __init__(self):
        self.numberToIndices = defaultdict(list)  # Map to store number -> min heap of indices
        self.indexToNumbers = {}  # Map to store index -> number

    def change(self, index: int, number: int) -> None:
        self.indexToNumbers[index] = number  # Update index to number mapping
        heappush(self.numberToIndices[number], index)  # Add index to the min heap for this number

    def find(self, number: int) -> int:
        retVal = -1

        # If number doesn't exist in our map
        if not self.numberToIndices[number]:
            return retVal

        # Keep checking top element until we find valid index
        while self.numberToIndices[number]:
            index = self.numberToIndices[number][0]

            # If index still maps to our target number, return it
            if self.indexToNumbers.get(index) == number:
                retVal = index
                break

            # Otherwise remove this stale index
            heappop(self.numberToIndices[number])

        return retVal

# Your NumberContainers object will be instantiated and called as such:
# obj = NumberContainers()
# obj.change(index,number)
# param_2 = obj.find(number)
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

## [2364. Count Number of Bad Pairs](https://leetcode.com/problems/count-number-of-bad-pairs/)  1622

- [Official](https://leetcode.com/problems/count-number-of-bad-pairs/editorial/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array nums.
A pair of indices (i, j) is a bad pair if i < j and j - i != nums[j] - nums[i].

Return the total number of bad pairs in nums.

Example 1:
Input: nums = [4,1,3,3]
Output: 5
Explanation: The pair (0, 1) is a bad pair since 1 - 0 != 1 - 4.
The pair (0, 2) is a bad pair since 2 - 0 != 3 - 4, 2 != -1.
The pair (0, 3) is a bad pair since 3 - 0 != 3 - 4, 3 != -1.
The pair (1, 2) is a bad pair since 2 - 1 != 3 - 1, 1 != 2.
The pair (2, 3) is a bad pair since 3 - 2 != 3 - 3, 1 != 0.
There are a total of 5 bad pairs, so we return 5.

Example 2:
Input: nums = [1,2,3,4,5]
Output: 0
Explanation: There are no bad pairs.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Would it be easier to count the number of pairs that are not bad pairs?
2. Notice that (j - i != nums[j] - nums[i]) is the same as (nums[i] - i != nums[j] - j).
3. Keep a counter of nums[i] - i. To be efficient, use a HashMap.
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
long long countBadPairs(int *nums, int numsSize) {
    long long retVal = 0;

    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    int diff, goodPairsCount;
    for (int pos = 0; pos < numsSize; pos++) {
        diff = pos - nums[pos];

        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &diff, pTemp);
        if (pTemp == NULL) {
            goodPairsCount = 0;  // Count of previous positions with same difference

            // Update count of positions with this difference
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                return retVal;
            }
            pTemp->key = diff;
            pTemp->value = 1;
            HASH_ADD_INT(pHashTable, key, pTemp);
        } else {
            goodPairsCount = pTemp->value;      // Count of previous positions with same difference
            pTemp->value = goodPairsCount + 1;  // Update count of positions with this difference
        }

        retVal += (pos - goodPairsCount);  // Total possible pairs minus good pairs = bad pairs
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
    long long countBadPairs(vector<int>& nums) {
        long long retVal = 0;

        int numsSize = nums.size();
        unordered_map<int, int> diffCount;
        for (int pos = 0; pos < numsSize; pos++) {
            int diff = pos - nums[pos];
            int goodPairsCount = diffCount[diff];  // Count of previous positions with same difference
            retVal += (pos - goodPairsCount);      // Total possible pairs minus good pairs = bad pairs
            diffCount[diff] = goodPairsCount + 1;  // Update count of positions with this difference
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def countBadPairs(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)
        diffCount = {}
        for pos in range(numsSize):
            diff = pos - nums[pos]
            goodPairsCount = diffCount.get(diff, 0)  # Count of previous positions with same difference
            retVal += pos - goodPairsCount  # Total possible pairs minus good pairs = bad pairs
            diffCount[diff] = goodPairsCount + 1  # Update count of positions with this difference

        return retVal
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

## [2537. Count the Number of Good Subarrays](https://leetcode.com/problems/count-the-number-of-good-subarrays/)  1891

- [Official](https://leetcode.com/problems/count-the-number-of-good-subarrays/editorial/)
- [Official](https://leetcode.cn/problems/count-the-number-of-good-subarrays/solutions/3643775/tong-ji-hao-zi-shu-zu-de-shu-mu-by-leetc-uvcm/)

<details><summary>Description</summary>

```text
Given an integer array nums and an integer k, return the number of good subarrays of nums.

A subarray arr is good if there are at least k pairs of indices (i, j) such that i < j and arr[i] == arr[j].

A subarray is a contiguous non-empty sequence of elements within an array.

Example 1:
Input: nums = [1,1,1,1,1], k = 10
Output: 1
Explanation: The only good subarray is the array nums itself.

Example 2:
Input: nums = [3,1,4,3,2,2,4], k = 2
Output: 4
Explanation: There are 4 different good subarrays:
- [3,1,4,3,2,2] that has 2 pairs.
- [3,1,4,3,2,2,4] that has 3 pairs.
- [1,4,3,2,2,4] that has 2 pairs.
- [4,3,2,2,4] that has 2 pairs.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i], k <= 10^9
```

<details><summary>Hint</summary>

```text
1. For a fixed index l, try to find the minimum value of index r, such that the subarray is not good
2. When a number is added to a subarray, it increases the number of pairs by its previous appearances.
3. When a number is removed from the subarray, it decreases the number of pairs by its remaining appearances.
4. Maintain 2-pointers l and r such that we can keep in account the number of equal pairs.
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
long long countGood(int *nums, int numsSize, int k) {
    long long retVal = 0;

    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    int key;

    int same = 0;
    int right = -1;
    for (int left = 0; left < numsSize; ++left) {
        while ((same < k) && (right + 1 < numsSize)) {
            ++right;

            pTemp = NULL;
            key = nums[right];
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
                same += pTemp->value;
                pTemp->value += 1;
            }
        }

        if (same >= k) {
            retVal += (numsSize - right);
        }

        pTemp = NULL;
        key = nums[left];
        HASH_FIND_INT(pHashTable, &key, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                return retVal;
            }
            pTemp->key = key;
            pTemp->value = -1;
            HASH_ADD_INT(pHashTable, key, pTemp);
        } else {
            pTemp->value -= 1;
            same -= pTemp->value;
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
    long long countGood(vector<int>& nums, int k) {
        long long retVal = 0;

        unordered_map<int, int> hashTable;

        int numsSize = nums.size();
        int same = 0;
        int right = -1;
        for (int left = 0; left < numsSize; ++left) {
            while ((same < k) && (right + 1 < numsSize)) {
                ++right;
                same += hashTable[nums[right]];
                ++hashTable[nums[right]];
            }

            if (same >= k) {
                retVal += (numsSize - right);
            }

            --hashTable[nums[left]];
            same -= hashTable[nums[left]];
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def countGood(self, nums: List[int], k: int) -> int:
        retVal = 0

        hashTable = Counter()

        numsSize = len(nums)
        same = 0
        right = -1
        for left in range(numsSize):
            while (same < k) and (right + 1 < numsSize):
                right += 1
                same += hashTable[nums[right]]
                hashTable[nums[right]] += 1

            if same >= k:
                retVal += (numsSize - right)

            hashTable[nums[left]] -= 1
            same -= hashTable[nums[left]]

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

## [2661. First Completely Painted Row or Column](https://leetcode.com/problems/first-completely-painted-row-or-column/)  1502

- [Official](https://leetcode.com/problems/first-completely-painted-row-or-column/editorial/)
- [Official](https://leetcode.cn/problems/first-completely-painted-row-or-column/solutions/2546583/zhao-dao-die-tu-yuan-su-by-leetcode-solu-8pz6/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array arr, and an m x n integer matrix mat.
arr and mat both contain all the integers in the range [1, m * n].

Go through each index i in arr starting from index 0 and paint the cell in mat containing the integer arr[i].

Return the smallest index i at which either a row or a column will be completely painted in mat.

Example 1:
Input: arr = [1,3,4,2], mat = [[1,4],[2,3]]
Output: 2
Explanation: The moves are shown in order,
and both the first row and second column of the matrix become fully painted at arr[2].

Example 2:
Input: arr = [2,8,7,4,1,3,5,6,9], mat = [[3,2,5],[1,4,6],[8,7,9]]
Output: 3
Explanation: The second column becomes fully painted at arr[3].

Constraints:
m == mat.length
n = mat[i].length
arr.length == m * n
1 <= m, n <= 10^5
1 <= m * n <= 10^5
1 <= arr[i], mat[r][c] <= m * n
All the integers of arr are unique.
All the integers of mat are unique.
```

<details><summary>Hint</summary>

```text
1. Can we use a frequency array?
2. Pre-process the positions of the values in the matrix.
3. Traverse the array and increment the corresponding row and column frequency using the pre-processed positions.
4. If the row frequency becomes equal to the number of columns, or vice-versa return the current index.
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
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int firstCompleteIndex(int* arr, int arrSize, int** mat, int matSize, int* matColSize) {
    int retVal = 0;

    struct hashTable* pHashTable = NULL;
    struct hashTable* pTemp;
    int key;
    for (int i = 0; i < arrSize; ++i) {
        key = arr[i];
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &key, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                return retVal;
            }
            pTemp->key = key;
            pTemp->value = i;
            HASH_ADD_INT(pHashTable, key, pTemp);
        } else {
            pTemp->value = i;
        }
    }

    int rowSize = matSize;
    int colSize = matColSize[0];
    retVal = INT_MAX;
    int lastElementIndex, indexVal;
    for (int row = 0; row < rowSize; row++) {
        lastElementIndex = INT_MIN;
        for (int col = 0; col < colSize; col++) {
            indexVal = lastElementIndex;
            key = mat[row][col];
            pTemp = NULL;
            HASH_FIND_INT(pHashTable, &key, pTemp);
            if (pTemp != NULL) {
                indexVal = pTemp->value;
            }
            lastElementIndex = fmax(lastElementIndex, indexVal);
        }
        retVal = fmin(retVal, lastElementIndex);
    }
    for (int col = 0; col < colSize; col++) {
        lastElementIndex = INT_MIN;
        for (int row = 0; row < rowSize; row++) {
            indexVal = lastElementIndex;
            key = mat[row][col];
            pTemp = NULL;
            HASH_FIND_INT(pHashTable, &key, pTemp);
            if (pTemp != NULL) {
                indexVal = pTemp->value;
            }
            lastElementIndex = fmax(lastElementIndex, indexVal);
        }
        retVal = fmin(retVal, lastElementIndex);
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
    int firstCompleteIndex(vector<int>& arr, vector<vector<int>>& mat) {
        int retVal = 0;

        int arrSize = arr.size();
        unordered_map<int, int> numToIndex;
        for (int i = 0; i < arrSize; i++) {
            numToIndex[arr[i]] = i;
        }

        int matRowSize = mat.size();
        int matColSize = mat[0].size();
        retVal = numeric_limits<int>::max();
        for (int row = 0; row < matRowSize; row++) {
            int lastElementIndex = numeric_limits<int>::min();
            for (int col = 0; col < matColSize; col++) {
                int indexVal = numToIndex[mat[row][col]];
                lastElementIndex = max(lastElementIndex, indexVal);
            }
            retVal = min(retVal, lastElementIndex);
        }
        for (int col = 0; col < matColSize; col++) {
            int lastElementIndex = numeric_limits<int>::min();
            for (int row = 0; row < matRowSize; row++) {
                int indexVal = numToIndex[mat[row][col]];
                lastElementIndex = max(lastElementIndex, indexVal);
            }
            retVal = min(retVal, lastElementIndex);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def firstCompleteIndex(self, arr: List[int], mat: List[List[int]]) -> int:
        retVal = 0

        arrSize = len(arr)
        numToIndex = {}
        for i in range(arrSize):
            numToIndex[arr[i]] = i

        matRowSize = len(mat)
        matColSize = len(mat[0])
        retVal = float("inf")
        for row in range(matRowSize):
            lastElementIndex = float("-inf")
            for col in range(matColSize):
                indexVal = numToIndex[mat[row][col]]
                lastElementIndex = max(lastElementIndex, indexVal)
            retVal = min(retVal, lastElementIndex)
        for col in range(matColSize):
            lastElementIndex = float("-inf")
            for row in range(matRowSize):
                indexVal = numToIndex[mat[row][col]]
                lastElementIndex = max(lastElementIndex, indexVal)
            retVal = min(retVal, lastElementIndex)

        return retVal
```

</details>

## [2780. Minimum Index of a Valid Split](https://leetcode.com/problems/minimum-index-of-a-valid-split/)

- [Official](https://leetcode.com/problems/minimum-index-of-a-valid-split/editorial/)

<details><summary>Description</summary>

```text
An element x of an integer array arr of length m is dominant if more than half the elements of arr have a value of x.

You are given a 0-indexed integer array nums of length n with one dominant element.

You can split nums at an index i into two arrays nums[0, ..., i] and nums[i + 1, ..., n - 1],
but the split is only valid if:
- 0 <= i < n - 1
- nums[0, ..., i], and nums[i + 1, ..., n - 1] have the same dominant element.

Here, nums[i, ..., j] denotes the subarray of nums starting at index i and ending at index j,
both ends being inclusive. Particularly, if j < i then nums[i, ..., j] denotes an empty subarray.

Return the minimum index of a valid split. If no valid split exists, return -1.

Example 1:
Input: nums = [1,2,2,2]
Output: 2
Explanation: We can split the array at index 2 to obtain arrays [1,2,2] and [2].
In array [1,2,2], element 2 is dominant since it occurs twice in the array and 2 * 2 > 3.
In array [2], element 2 is dominant since it occurs once in the array and 1 * 2 > 1.
Both [1,2,2] and [2] have the same dominant element as nums, so this is a valid split.
It can be shown that index 2 is the minimum index of a valid split.

Example 2:
Input: nums = [2,1,3,1,1,1,7,1,2,1]
Output: 4
Explanation: We can split the array at index 4 to obtain arrays [2,1,3,1,1] and [1,7,1,2,1].
In array [2,1,3,1,1], element 1 is dominant since it occurs thrice in the array and 3 * 2 > 5.
In array [1,7,1,2,1], element 1 is dominant since it occurs thrice in the array and 3 * 2 > 5.
Both [2,1,3,1,1] and [1,7,1,2,1] have the same dominant element as nums, so this is a valid split.
It can be shown that index 4 is the minimum index of a valid split.

Example 3:
Input: nums = [3,3,3,3,7,2,2]
Output: -1
Explanation: It can be shown that there is no valid split.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
nums has exactly one dominant element.
```

<details><summary>Hint</summary>

```text
1. Find the dominant element of nums by using a hashmap to maintain element frequency,
   we denote the dominant element as x and its frequency as f.
2. For each index in [0, n - 2], calculate f1, x’s frequency in the subarray [0, i] when looping the index.
   And f2, x’s frequency in the subarray [i + 1, n - 1] which is equal to f - f1.
   Then we can check whether x is dominant in both subarrays.
```

</details>

</details>

<details><summary>C</summary>

```c
int minimumIndex(int* nums, int numsSize) {
    int retVal = -1;  // If no valid split exists, return -1.

    // Find the majority element
    int x = nums[0];
    int count = 0;
    for (int index = 0; index < numsSize; index++) {
        if (nums[index] == x) {
            count++;
        } else {
            count--;
        }

        if (count == 0) {
            x = nums[index];
            count = 1;
        }
    }

    // Count frequency of majority element
    int xCount = 0;
    for (int index = 0; index < numsSize; index++) {
        if (nums[index] == x) {
            xCount++;
        }
    }

    // Check if valid split is possible
    count = 0;
    for (int index = 0; index < numsSize; index++) {
        if (nums[index] == x) {
            count++;
        }

        int remainingCount = xCount - count;

        if ((count * 2 > index + 1) && (remainingCount * 2 > numsSize - index - 1)) {
            retVal = index;
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
    int minimumIndex(vector<int>& nums) {
        int retVal = -1;  // If no valid split exists, return -1.

        // Find the majority element
        int x = nums[0];
        int count = 0;
        for (auto& num : nums) {
            if (num == x) {
                count++;
            } else {
                count--;
            }

            if (count == 0) {
                x = num;
                count = 1;
            }
        }

        // Count frequency of majority element
        int xCount = 0;
        for (auto& num : nums) {
            if (num == x) {
                xCount++;
            }
        }

        // Check if valid split is possible
        count = 0;
        int numsSize = nums.size();
        for (int index = 0; index < numsSize; index++) {
            if (nums[index] == x) {
                count++;
            }

            int remainingCount = xCount - count;

            if ((count * 2 > index + 1) && (remainingCount * 2 > numsSize - index - 1)) {
                retVal = index;
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
    def minimumIndex(self, nums: List[int]) -> int:
        retVal = -1  # If no valid split exists, return -1.

        # Find the majority element
        x = nums[0]
        count = 0
        for num in nums:
            if num == x:
                count += 1
            else:
                count -= 1

            if count == 0:
                x = num
                count = 1

        # Count frequency of majority element
        xCount = 0
        for num in nums:
            if num == x:
                xCount += 1

        # Check if valid split is possible
        count = 0
        numsSize = len(nums)
        for index in range(numsSize):
            if nums[index] == x:
                count += 1

            remainingCount = xCount - count

            if (count * 2 > index + 1) and (remainingCount * 2 > numsSize - index - 1):
                retVal = index
                break

        return retVal
```

</details>

## [2965. Find Missing and Repeated Values](https://leetcode.com/problems/find-missing-and-repeated-values/)  1244

- [Official](https://leetcode.com/problems/find-missing-and-repeated-values/editorial/)
- [Official](https://leetcode.cn/problems/find-missing-and-repeated-values/solutions/)

<details><summary>Description</summary>

```text
You are given a 0-indexed 2D integer matrix grid of size n * n with values in the range [1, n2].
Each integer appears exactly once except a which appears twice and b which is missing.
The task is to find the repeating and missing numbers a and b.

Return a 0-indexed integer array ans of size 2 where ans[0] equals to a and ans[1] equals to b.

Example 1:
Input: grid = [[1,3],[2,2]]
Output: [2,4]
Explanation: Number 2 is repeated and number 4 is missing so the answer is [2,4].

Example 2:
Input: grid = [[9,1,7],[8,9,2],[3,4,6]]
Output: [9,5]
Explanation: Number 9 is repeated and number 5 is missing so the answer is [9,5].

Constraints:
2 <= n == grid.length == grid[i].length <= 50
1 <= grid[i][j] <= n * n
For all x that 1 <= x <= n * n there is exactly one x that is not equal to any of the grid members.
For all x that 1 <= x <= n * n there is exactly one x that is equal to exactly two of the grid members.
For all x that 1 <= x <= n * n except two of them
there is exatly one pair of i, j that 0 <= i, j <= n - 1 and grid[i][j] == x.
```

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findMissingAndRepeatedValues(int** grid, int gridSize, int* gridColSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int*)calloc(2, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }

    // Store frequency of each number in the grid
    int freqSize = gridSize * gridSize + 1;  // 1 <= grid[i][j] <= n * n
    int freq[freqSize];
    memset(freq, 0, sizeof(freq));
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridColSize[i]; ++j) {
            freq[grid[i][j]]++;
        }
    }

    // Check numbers from 1 to n^2 to find missing and repeated values
    for (int num = 1; num <= gridSize * gridSize; num++) {
        if (freq[num] == 0) {
            pRetVal[1] = num;
        } else if (freq[num] == 2) {
            pRetVal[0] = num;
        }
    }
    (*returnSize) = 2;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
        vector<int> retVal(2, 0);

        // Store frequency of each number in the grid
        unordered_map<int, int> freq;
        for (auto& row : grid) {
            for (int num : row) {
                freq[num]++;
            }
        }

        // Check numbers from 1 to n^2 to find missing and repeated values
        int missing = -1;
        int repeat = -1;
        int gridSize = grid.size();
        for (int num = 1; num <= gridSize * gridSize; num++) {
            if (freq.count(num) == 0) {
                missing = num;
            } else if (freq[num] == 2) {
                repeat = num;
            }
        }
        retVal = {repeat, missing};

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def findMissingAndRepeatedValues(self, grid: List[List[int]]) -> List[int]:
        retVal = []

        # Store frequency of each number in the grid
        freq = {}
        for row in grid:
            for num in row:
                freq[num] = freq.get(num, 0) + 1

        # Check numbers from 1 to n^2 to find missing and repeated values
        gridSize = len(grid)
        for num in range(1, gridSize * gridSize + 1):
            if num not in freq:
                missing = num
            elif freq[num] == 2:
                repeat = num
        retVal = [repeat, missing]

        return retVal
```

</details>

## [2981. Find Longest Special Substring That Occurs Thrice I](https://leetcode.com/problems/find-longest-special-substring-that-occurs-thrice-i/)  1505

- [Official](https://leetcode.com/problems/find-longest-special-substring-that-occurs-thrice-i/editorial/)
- [Official](https://leetcode.cn/problems/find-longest-special-substring-that-occurs-thrice-i/solutions/2787295/zhao-chu-chu-xian-zhi-shao-san-ci-de-zui-a109/)

<details><summary>Description</summary>

```text
You are given a string s that consists of lowercase English letters.

A string is called special if it is made up of only a single character.
For example, the string "abc" is not special, whereas the strings "ddd", "zz", and "f" are special.

Return the length of the longest special substring of s which occurs at least thrice,
or -1 if no special substring occurs at least thrice.

A substring is a contiguous non-empty sequence of characters within a string.

Example 1:
Input: s = "aaaa"
Output: 2
Explanation: The longest special substring which occurs thrice is "aa": substrings "aaaa", "aaaa", and "aaaa".
It can be shown that the maximum length achievable is 2.

Example 2:
Input: s = "abcdef"
Output: -1
Explanation: There exists no special substring which occurs at least thrice. Hence return -1.

Example 3:
Input: s = "abcaba"
Output: 1
Explanation: The longest special substring which occurs thrice is "a": substrings "abcaba", "abcaba", and "abcaba".
It can be shown that the maximum length achievable is 1.

Constraints:
3 <= s.length <= 50
s consists of only lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. The constraints are small.
2. Brute force checking all substrings.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MAX_KEY_SIZE (32)  // 3 <= s.length <= 50
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
int maximumLength(char* s) {
    int retVal = 0;

    struct hashTable* pHashTable = NULL;
    char character;
    int substringLength;
    int count;

    struct hashTable* pTmp;
    char key[MAX_KEY_SIZE];
    int sSize = strlen(s);
    int start, end;
    for (start = 0; start < sSize; ++start) {
        character = s[start];
        substringLength = 0;
        for (end = start; end < sSize; ++end) {
            // If the string is empty, or the current character is equal to the previously added character,
            // then add it to the map. Otherwise, break the iteration.
            if (character != s[end]) {
                break;
            }
            substringLength++;

            // s consists of only lowercase English letters.
            memset(key, 0, sizeof(key));
            snprintf(key, sizeof(key), "%c%d", character, substringLength);

            pTmp = NULL;
            HASH_FIND_STR(pHashTable, key, pTmp);
            if (pTmp == NULL) {
                pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
                if (pTmp == NULL) {
                    perror("malloc");
                    freeAll(pHashTable);
                    pHashTable = NULL;
                    return retVal;
                }
                strcpy(pTmp->key, key);
                pTmp->value = 0;
                HASH_ADD_STR(pHashTable, key, pTmp);
            }
            pTmp->value++;
        }
    }

    struct hashTable* pCurrent = NULL;
    pTmp = NULL;
    HASH_ITER(hh, pHashTable, pCurrent, pTmp) {
        sscanf(pHashTable->key, "%c%d", &character, &substringLength);
        count = pHashTable->value;
        if ((count >= 3) && (substringLength > retVal)) {
            retVal = substringLength;
        }

        HASH_DEL(pHashTable, pCurrent);
        free(pCurrent);
        pCurrent = NULL;
    }
    pHashTable = NULL;
    if (retVal == 0) {
        retVal = -1;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maximumLength(string s) {
        int retVal = 0;

        map<pair<char, int>, int> hashTable;
        char character;
        int substringLength;
        int count;

        int sSize = s.size();
        substringLength = 0;
        for (int start = 0; start < sSize; start++) {
            character = s[start];
            substringLength = 0;
            for (int end = start; end < sSize; end++) {
                // If the string is empty, or the current character is equal to the previously added character,
                // then add it to the map. Otherwise, break the iteration.
                if (character != s[end]) {
                    break;
                }
                substringLength++;
                hashTable[{character, substringLength}]++;
            }
        }

        for (auto iterator : hashTable) {
            character = iterator.first.first;
            substringLength = iterator.first.second;
            count = iterator.second;
            if ((count >= 3) && (substringLength > retVal)) {
                retVal = substringLength;
            }
        }
        if (retVal == 0) {
            retVal = -1;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maximumLength(self, s: str) -> int:
        retVal = 0

        sSize = len(s)
        hashTable = {}
        for start in range(sSize):
            character = s[start]
            substringLength = 0
            for end in range(start, sSize):
                # If the string is empty, or the current character is equal to the previously added character,
                # then add it to the map. Otherwise, break the iteration.
                if character != s[end]:
                    break
                substringLength += 1
                hashTable[(character, substringLength)] = hashTable.get((character, substringLength), 0) + 1

        for (character, substringLength), count in hashTable.items():
            if (count >= 3) and (substringLength > retVal):
                retVal = substringLength
        if retVal == 0:
            retVal = - 1

        return retVal
```

</details>
