# [Hash Table](https://en.wikipedia.org/wiki/Hash_table)

- [uthash](https://troydhanson.github.io/uthash/)

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

## [3085. Minimum Deletions to Make String K-Special](https://leetcode.com/problems/minimum-deletions-to-make-string-k-special/)  1764

- [Official](https://leetcode.com/problems/minimum-deletions-to-make-string-k-special/editorial/)
- [Official](https://leetcode.cn/problems/minimum-deletions-to-make-string-k-special/solutions/3698508/cheng-wei-k-te-shu-zi-fu-chuan-xu-yao-sh-erdq/)

<details><summary>Description</summary>

```text
You are given a string word and an integer k.

We consider word to be k-special if |freq(word[i]) - freq(word[j])| <= k for all indices i and j in the string.

Here, freq(x) denotes the frequency of the character x in word, and |y| denotes the absolute value of y.

Return the minimum number of characters you need to delete to make word k-special.

Example 1:
Input: word = "aabcaba", k = 0
Output: 3
Explanation: We can make word 0-special by deleting 2 occurrences of "a" and 1 occurrence of "c".
Therefore, word becomes equal to "baba" where freq('a') == freq('b') == 2.

Example 2:
Input: word = "dabdcbdcdcd", k = 2
Output: 2
Explanation: We can make word 2-special by deleting 1 occurrence of "a" and 1 occurrence of "d".
Therefore, word becomes equal to "bdcbdcdcd" where freq('b') == 2, freq('c') == 3, and freq('d') == 4.

Example 3:
Input: word = "aaabaaa", k = 2
Output: 1
Explanation: We can make word 2-special by deleting 1 occurrence of "b".
Therefore, word becomes equal to "aaaaaa" where each letter's frequency is now uniformly 6.

Constraints:
1 <= word.length <= 10^5
0 <= k <= 10^5
word consists only of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Count the frequency of each letter.
2. Suppose we select several characters as the final answer,
   and let x be the character with the smallest frequency in the answer.
   It can be shown that out of the selected characters,
   the optimal solution will never delete an occurrence of character x to obtain the answer.
3. We will fix a character c and assume that it will be the character with the smallest frequency in the answer.
   Suppose its frequency is x.
4. Then, for every other character, we will count the number of occurrences that will be deleted.
   Suppose that the current character has y occurrences.
   - If y < x, we need to delete all of them.
   - if y > x + k, we should delete y - x - k of such character.
   - Otherwise we don’t need to delete it.
```

</details>

</details>

<details><summary>C</summary>

```c
int minimumDeletions(char* word, int k) {
    int retVal = 0;

#define MAX_LETTER_SIZE (26)  // word consists only of lowercase English letters.

    int frequency[MAX_LETTER_SIZE];
    memset(frequency, 0, sizeof(frequency));
    for (int i = 0; word[i]; i++) {
        frequency[word[i] - 'a']++;
    }

    retVal = strlen(word);
    int a, b, deleted;
    for (int i = 0; i < MAX_LETTER_SIZE; i++) {
        if (frequency[i] == 0) {
            continue;
        }

        a = frequency[i];
        deleted = 0;
        for (int j = 0; j < MAX_LETTER_SIZE; j++) {
            if (frequency[j] == 0) {
                continue;
            }

            b = frequency[j];
            if (a > b) {
                deleted += b;
            } else if (b > a + k) {
                deleted += b - (a + k);
            }
        }

        if (deleted < retVal) {
            retVal = deleted;
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
    int minimumDeletions(string word, int k) {
        int retVal = 0;

        unordered_map<char, int> frequency;
        for (auto &ch : word) {
            frequency[ch]++;
        }

        retVal = word.size();
        for (auto &[_, a] : frequency) {
            int deleted = 0;
            for (auto &[_, b] : frequency) {
                if (a > b) {
                    deleted += b;
                } else if (b > a + k) {
                    deleted += b - (a + k);
                }
            }
            retVal = min(retVal, deleted);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minimumDeletions(self, word: str, k: int) -> int:
        retVal = 0

        frequency = defaultdict(int)
        for c in word:
            frequency[c] += 1

        retVal = len(word)
        for a in frequency.values():
            deleted = 0
            for b in frequency.values():
                if a > b:
                    deleted += b
                elif b > a + k:
                    deleted += (b - (a + k))
            retVal = min(retVal, deleted)

        return retVal
```

</details>

## [3160. Find the Number of Distinct Colors Among the Balls](https://leetcode.com/problems/find-the-number-of-distinct-colors-among-the-balls/)  1517

- [Official](https://leetcode.com/problems/find-the-number-of-distinct-colors-among-the-balls/editorial/)

<details><summary>Description</summary>

```text
You are given an integer limit and a 2D array queries of size n x 2.

There are limit + 1 balls with distinct labels in the range [0, limit].
Initially, all balls are uncolored.
For every query in queries that is of the form [x, y], you mark ball x with the color y.
After each query, you need to find the number of distinct colors among the balls.

Return an array result of length n, where result[i] denotes the number of distinct colors after ith query.

Note that when answering a query, lack of a color will not be considered as a color.

Example 1:
Input: limit = 4, queries = [[1,4],[2,5],[1,3],[3,4]]
Output: [1,2,2,3]
Explanation:
After query 0, ball 1 has color 4.
After query 1, ball 1 has color 4, and ball 2 has color 5.
After query 2, ball 1 has color 3, and ball 2 has color 5.
After query 3, ball 1 has color 3, ball 2 has color 5, and ball 3 has color 4.

Example 2:
Input: limit = 4, queries = [[0,1],[1,2],[2,2],[3,4],[4,5]]
Output: [1,2,2,3,4]
Explanation:
After query 0, ball 0 has color 1.
After query 1, ball 0 has color 1, and ball 1 has color 2.
After query 2, ball 0 has color 1, and balls 1 and 2 have color 2.
After query 3, ball 0 has color 1, balls 1 and 2 have color 2, and ball 3 has color 4.
After query 4, ball 0 has color 1, balls 1 and 2 have color 2, ball 3 has color 4, and ball 4 has color 5.

Constraints:
1 <= limit <= 109
1 <= n == queries.length <= 10^5
queries[i].length == 2
0 <= queries[i][0] <= limit
1 <= queries[i][1] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Use two HashMaps to maintain the color of each ball and the set of balls with each color.
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
int *queryResults(int limit, int **queries, int queriesSize, int *queriesColSize, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int *)calloc(queriesSize, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return NULL;
    }

    struct hashTable *pColorHashTable = NULL;
    struct hashTable *pBallHashTable = NULL;
    struct hashTable *pTemp;
    int ball, color, prevColor;
    for (int i = 0; i < queriesSize; i++) {
        ball = queries[i][0];
        color = queries[i][1];

        pTemp = NULL;
        HASH_FIND_INT(pBallHashTable, &ball, pTemp);
        if (pTemp != NULL) {
            // Decrement count of the previous color on the ball
            prevColor = pTemp->value;
            pTemp->value = color;

            pTemp = NULL;
            HASH_FIND_INT(pColorHashTable, &prevColor, pTemp);
            if (pTemp != NULL) {
                pTemp->value--;
                // If there are no balls with previous color left, remove color from color map
                if (pTemp->value == 0) {
                    HASH_DEL(pColorHashTable, pTemp);
                    free(pTemp);
                }
            }
        } else {
            // Set color of ball to the new color
            pTemp = NULL;
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pColorHashTable);
                freeAll(pBallHashTable);
                free(pRetVal);
                pRetVal = NULL;
                return pRetVal;
            }
            pTemp->key = ball;
            pTemp->value = color;
            HASH_ADD_INT(pBallHashTable, key, pTemp);
        }

        // Increment the count of the new color
        pTemp = NULL;
        HASH_FIND_INT(pColorHashTable, &color, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pColorHashTable);
                freeAll(pBallHashTable);
                free(pRetVal);
                pRetVal = NULL;
                return pRetVal;
            }
            pTemp->key = color;
            pTemp->value = 1;
            HASH_ADD_INT(pColorHashTable, key, pTemp);
        } else {
            pTemp->value += 1;
        }

        pRetVal[i] = HASH_COUNT(pColorHashTable);
        (*returnSize)++;
    }

    //
    freeAll(pColorHashTable);
    freeAll(pBallHashTable);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> queryResults(int limit, vector<vector<int>>& queries) {
        vector<int> retVal;

        int queriesSize = queries.size();
        retVal.resize(queriesSize);

        unordered_map<int, int> colorMap;
        unordered_map<int, int> ballMap;
        for (int i = 0; i < queriesSize; i++) {
            int ball = queries[i][0];
            int color = queries[i][1];
            if (ballMap.find(ball) != ballMap.end()) {
                // Decrement count of the previous color on the ball
                int prevColor = ballMap[ball];
                colorMap[prevColor]--;

                // If there are no balls with previous color left, remove color from color map
                if (colorMap[prevColor] == 0) {
                    colorMap.erase(prevColor);
                }
            }
            ballMap[ball] = color;  // Set color of ball to the new color
            colorMap[color]++;      // Increment the count of the new color
            retVal[i] = colorMap.size();
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def queryResults(self, limit: int, queries: List[List[int]]) -> List[int]:
        retVal = []

        queriesSize = len(queries)

        colorMap = {}
        ballMap = {}
        for i in range(queriesSize):
            ball, color = queries[i]

            # Check if ball is already colored
            if ball in ballMap:
                # Decrement count of the previous color on the ball
                prevColor = ballMap[ball]
                colorMap[prevColor] -= 1

                # If there are no balls with previous color left, remove color from color map
                if colorMap[prevColor] == 0:
                    del colorMap[prevColor]

            ballMap[ball] = color  # Set color of ball to the new color
            colorMap[color] = colorMap.get(color, 0) + 1  # Increment the count of the new color

            retVal.append(len(colorMap))

        return retVal
```

</details>

## [3375. Minimum Operations to Make Array Values Equal to K](https://leetcode.com/problems/minimum-operations-to-make-array-values-equal-to-k/)  1382

- [Official](https://leetcode.com/problems/minimum-operations-to-make-array-values-equal-to-k/editorial/)
- [Official](https://leetcode.cn/problems/minimum-operations-to-make-array-values-equal-to-k/solutions/3636172/shi-shu-zu-de-zhi-quan-bu-wei-k-de-zui-s-bhcw/)

<details><summary>Description</summary>

```text
You are given an integer array nums and an integer k.

An integer h is called valid if all values in the array that are strictly greater than h are identical.

For example, if nums = [10, 8, 10, 8], a valid integer is h = 9 because all nums[i] > 9 are equal to 10,
but 5 is not a valid integer.

You are allowed to perform the following operation on nums:
- Select an integer h that is valid for the current values in nums.
- For each index i where nums[i] > h, set nums[i] to h.

Return the minimum number of operations required to make every element in nums equal to k.
If it is impossible to make all elements equal to k, return -1.

Example 1:
Input: nums = [5,2,5,4,5], k = 2
Output: 2
Explanation:
The operations can be performed in order using valid integers 4 and then 2.

Example 2:
Input: nums = [2,1,2], k = 2
Output: -1
Explanation:
It is impossible to make all the values equal to 2.

Example 3:
Input: nums = [9,7,5,3], k = 1
Output: 4
Explanation:
The operations can be performed using valid integers in the order 7, 5, 3, and 1.

Constraints:
1 <= nums.length <= 100
1 <= nums[i] <= 100
1 <= k <= 100
```

<details><summary>Hint</summary>

```text
1. Handle the case when the array contains an integer less than k
2. Start by performing operations on the highest integer
3. You can perform an operation on the highest integer using the second-highest,
   an operation on the second-highest using the third-highest, and so forth.
4. The answer is the number of distinct integers in the array that are larger than k.
```

</details>

</details>

<details><summary>C</summary>

```c
struct hashTable {
    int key;
    UT_hash_handle hh;
};
void freeAll(struct hashTable *pFree) {
    struct hashTable *current;
    struct hashTable *tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d\n", pFree->key);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int minOperations(int *nums, int numsSize, int k) {
    int retVal = -1;  // If it is impossible to make all elements equal to k, return -1.

    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    int key;
    for (int i = 0; i < numsSize; i++) {
        key = nums[i];
        if (key < k) {
            freeAll(pHashTable);
            return retVal;
        } else if (key > k) {
            pTemp = NULL;
            HASH_FIND_INT(pHashTable, &key, pTemp);
            if (pTemp != NULL) {
                continue;
            }

            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                return retVal;
            }
            pTemp->key = key;
            HASH_ADD_INT(pHashTable, key, pTemp);
        }
    }
    retVal = HASH_COUNT(pHashTable);
    freeAll(pHashTable);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minOperations(vector<int>& nums, int k) {
        int retVal = -1;  // If it is impossible to make all elements equal to k, return -1.

        unordered_set<int> hashTable;
        for (int x : nums) {
            if (x < k) {
                return retVal;
            } else if (x > k) {
                hashTable.insert(x);
            }
        }
        retVal = hashTable.size();

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minOperations(self, nums: List[int], k: int) -> int:
        retVal = -1  # If it is impossible to make all elements equal to k, return -1.

        hashTable = set()
        for x in nums:
            if x < k:
                return retVal
            elif x > k:
                hashTable.add(x)
        retVal = len(hashTable)

        return retVal
```

</details>

## [3396. Minimum Number of Operations to Make Elements in Array Distinct](https://leetcode.com/problems/minimum-number-of-operations-to-make-elements-in-array-distinct/)  1299

- [Official](https://leetcode.com/problems/minimum-number-of-operations-to-make-elements-in-array-distinct/editorial/)
- [Official](https://leetcode.cn/problems/minimum-number-of-operations-to-make-elements-in-array-distinct/solutions/3634685/shi-shu-zu-yuan-su-hu-bu-xiang-tong-suo-cay1s/)

<details><summary>Description</summary>

```text
You are given an integer array nums. You need to ensure that the elements in the array are distinct.
To achieve this, you can perform the following operation any number of times:
- Remove 3 elements from the beginning of the array.
  If the array has fewer than 3 elements, remove all remaining elements.

Note that an empty array is considered to have distinct elements.
Return the minimum number of operations needed to make the elements in the array distinct.

Example 1:
Input: nums = [1,2,3,4,2,3,3,5,7]
Output: 2
Explanation:
In the first operation, the first 3 elements are removed, resulting in the array [4, 2, 3, 3, 5, 7].
In the second operation, the next 3 elements are removed, resulting in the array [3, 5, 7], which has distinct elements.
Therefore, the answer is 2.

Example 2:
Input: nums = [4,5,6,4,4]
Output: 2
Explanation:
In the first operation, the first 3 elements are removed, resulting in the array [4, 4].
In the second operation, all remaining elements are removed, resulting in an empty array.
Therefore, the answer is 2.

Example 3:
Input: nums = [6,7,8,9]
Output: 0
Explanation:
The array already contains distinct elements. Therefore, the answer is 0.

Constraints:
1 <= nums.length <= 100
1 <= nums[i] <= 100
```

<details><summary>Hint</summary>

```text
1. The constraints are small. Try brute force.
```

</details>

</details>

<details><summary>C</summary>

```c
int minimumOperations(int* nums, int numsSize) {
    int retVal = 0;

    int hashTable[128];  // 1 <= nums.length <= 100
    memset(hashTable, 0, sizeof(hashTable));

    for (int i = numsSize - 1; i >= 0; --i) {
        if (hashTable[nums[i]] == 1) {
            retVal = i / 3 + 1;
            break;
        }
        hashTable[nums[i]] = 1;
    }

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

        vector<int> hashTable(128, 0);  // 1 <= nums.length <= 100

        int numsSize = nums.size();
        for (int i = numsSize - 1; i >= 0; --i) {
            if (hashTable[nums[i]] == 1) {
                retVal = i / 3 + 1;
                break;
            }
            hashTable[nums[i]] = 1;
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

        hashTable = [0] * 128  # 1 <= nums.length <= 100

        numsSize = len(nums)
        for i in range(numsSize-1, -1, -1):
            if hashTable[nums[i]] == 1:
                retVal = i // 3 + 1
                break
            hashTable[nums[i]] = 1

        return retVal
```

</details>

## [3442. Maximum Difference Between Even and Odd Frequency I](https://leetcode.com/problems/maximum-difference-between-even-and-odd-frequency-i/)  1220

- [Official](https://leetcode.com/problems/maximum-difference-between-even-and-odd-frequency-i/editorial/)
- [Official](https://leetcode.cn/problems/maximum-difference-between-even-and-odd-frequency-i/solutions/3692731/qi-ou-pin-ci-jian-de-zui-da-chai-zhi-i-b-wy8k/)

<details><summary>Description</summary>

```text
You are given a string s consisting of lowercase English letters.

Your task is to find the maximum difference diff = a1 - a2
between the frequency of characters a1 and a2 in the string such that:
- a1 has an odd frequency in the string.
- a2 has an even frequency in the string.

Return this maximum difference.

Example 1:
Input: s = "aaaaabbc"
Output: 3
Explanation:
The character 'a' has an odd frequency of 5, and 'b' has an even frequency of 2.
The maximum difference is 5 - 2 = 3.

Example 2:
Input: s = "abcabcab"
Output: 1
Explanation:
The character 'a' has an odd frequency of 3, and 'c' has an even frequency of 2.
The maximum difference is 3 - 2 = 1.

Constraints:
3 <= s.length <= 100
s consists only of lowercase English letters.
s contains at least one character with an odd frequency and one with an even frequency.
```

<details><summary>Hint</summary>

```text
1. Use a frequency map to identify the maximum odd and minimum even frequencies. Then, calculate their difference.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MAX_LETTERS (26)  // s consists only of lowercase English letters.
int maxDifference(char* s) {
    int retVal = 0;

    int frequency[MAX_LETTERS];
    memset(frequency, 0, sizeof(frequency));
    for (int i = 0; s[i] != '\0'; ++i) {
        frequency[s[i] - 'a']++;
    }

    int value;
    int maxOdd = 0;
    int minEven = strlen(s);
    for (int i = 0; i < MAX_LETTERS; ++i) {
        value = frequency[i];
        if (value == 0) {
            continue;  // Skip letters that do not appear in the string.
        }

        if (value % 2 == 1) {
            if (value > maxOdd) {
                maxOdd = value;
            }
        } else {
            if (value < minEven) {
                minEven = value;
            }
        }
    }
    retVal = maxOdd - minEven;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxDifference(string s) {
        int retVal = 0;

        unordered_map<char, int> frequency;
        for (char c : s) {
            frequency[c]++;
        }

        int maxOdd = 0;
        int minEven = s.size();
        for (const auto& [key, value] : frequency) {
            if (value % 2 == 1) {
                maxOdd = max(maxOdd, value);
            } else {
                minEven = min(minEven, value);
            }
        }
        retVal = maxOdd - minEven;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxDifference(self, s: str) -> int:
        retVal = 0

        frequency = Counter(s)

        maxOdd = max(i for i in frequency.values() if i % 2 == 1)
        minEven = min(i for i in frequency.values() if i % 2 == 0)
        retVal = maxOdd - minEven

        return retVal
```

</details>
