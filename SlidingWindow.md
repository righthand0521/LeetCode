# Sliding Window

## [3. Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/)

- [Official](https://leetcode.cn/problems/longest-substring-without-repeating-characters/solutions/227999/wu-zhong-fu-zi-fu-de-zui-chang-zi-chuan-by-leetc-2/)

<details><summary>Description</summary>

```text
Given a string s, find the length of the longest substring without repeating characters.

Example 1:
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

Example 2:
Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:
Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.

Constraints:
0 <= s.length <= 5 * 10^4
s consists of English letters, digits, symbols and spaces.
```

</details>

<details><summary>C</summary>

```c
int lengthOfLongestSubstring(char *s) {
    int retVal = 0;

    // s consists of English letters, digits, symbols and spaces.
#define MAX_CHAR_RANGE (256)
    int hashTable[MAX_CHAR_RANGE];
    memset(hashTable, 0, sizeof(hashTable));

    int head = 0;
    int tail = 0;
    while ((*(s + head) != 0) && (*(s + tail) != 0)) {
        if ((hashTable[(int)(*(s + head))] != 0) && (hashTable[(int)(*(s + tail))] != 0)) {
            hashTable[(int)(*(s + head))] = 0;
            ++head;
        } else {
            hashTable[(int)(*(s + tail))] = 1;
            ++tail;
        }
        retVal = fmax(retVal, (tail - head));
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int lengthOfLongestSubstring(string s) {
        int retVal = 0;

        unordered_map<int, int> hashTable;
        int len = s.length();
        int head = 0;
        int tail = 0;
        while ((head < len) && (tail < len)) {
            if ((hashTable[s[head]] != 0) && (hashTable[s[tail]] != 0)) {
                hashTable[s[head]] = 0;
                ++head;
            } else {
                ++hashTable[s[tail]];
                ++tail;
            }
            retVal = max(retVal, (tail - head));
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        retVal = 0

        hashTable = defaultdict(dict)
        sSize = len(s)
        head = 0
        tail = 0
        while head < sSize and tail < sSize:
            if hashTable[s[head]] and hashTable[s[tail]]:
                hashTable.pop(s[head])
                head += 1
            else:
                hashTable[s[tail]] = 1
                tail += 1
            retVal = max(retVal, tail - head)

        return retVal
```

</details>

## [30. Substring with Concatenation of All Words](https://leetcode.com/problems/substring-with-concatenation-of-all-words/)

- [Official](https://leetcode.cn/problems/substring-with-concatenation-of-all-words/solutions/1616997/chuan-lian-suo-you-dan-ci-de-zi-chuan-by-244a/)

<details><summary>Description</summary>

```text
You are given a string s and an array of strings words. All the strings of words are of the same length.

A concatenated string is a string that exactly contains all the strings of any permutation of words concatenated.
- For example, if words = ["ab","cd","ef"], then "abcdef", "abefcd", "cdabef", "cdefab", "efabcd",
  and "efcdab" are all concatenated strings.
  "acdbef" is not a concatenated string because it is not the concatenation of any permutation of words.

Return an array of the starting indices of all the concatenated substrings in s. You can return the answer in any order.

Example 1:
Input: s = "barfoothefoobarman", words = ["foo","bar"]
Output: [0,9]
Explanation:
The substring starting at 0 is "barfoo". It is the concatenation of ["bar","foo"] which is a permutation of words.
The substring starting at 9 is "foobar". It is the concatenation of ["foo","bar"] which is a permutation of words.

Example 2:
Input: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
Output: []
Explanation:
There is no concatenated substring.

Example 3:
Input: s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
Output: [6,9,12]
Explanation:
The substring starting at 6 is "foobarthe". It is the concatenation of ["foo","bar","the"].
The substring starting at 9 is "barthefoo". It is the concatenation of ["bar","the","foo"].
The substring starting at 12 is "thefoobar". It is the concatenation of ["the","foo","bar"].

Constraints:
1 <= s.length <= 10^4
1 <= words.length <= 5000
1 <= words[i].length <= 30
s and words[i] consist of lowercase English letters.
```

</details>

<details><summary>C</summary>

```c
#define MAX_WORD_SIZE (32)  // 1 <= words[i].length <= 30
struct hashTable {
    char key[MAX_WORD_SIZE];
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
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findSubstring(char* s, char** words, int wordsSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    int wordLength = strlen(words[0]);
    int sLength = strlen(s);

    pRetVal = (int*)malloc(sLength * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (sLength * sizeof(int)));

    struct hashTable* pDiff = NULL;
    struct hashTable* pEntry = NULL;
    char word[MAX_WORD_SIZE];
    int pos = 0;
    int i, j, start;
    for (i = 0; i < wordLength; i++) {
        if (i + wordsSize * wordLength > sLength) {
            break;
        }

        memset(word, 0, sizeof(word));
        for (j = 0; j < wordsSize; j++) {
            snprintf(word, wordLength + 1, "%s", s + i + j * wordLength);

            pEntry = NULL;
            HASH_FIND_STR(pDiff, word, pEntry);
            if (pEntry == NULL) {
                pEntry = (struct hashTable*)malloc(sizeof(struct hashTable));
                if (pEntry == NULL) {
                    perror("malloc");
                    freeAll(pDiff);
                    pDiff = NULL;
                    return pRetVal;
                }
                strcpy(pEntry->key, word);
                pEntry->value = 0;
                HASH_ADD_STR(pDiff, key, pEntry);
            }
            pEntry->value++;
        }

        for (j = 0; j < wordsSize; j++) {
            pEntry = NULL;
            HASH_FIND_STR(pDiff, words[j], pEntry);
            if (pEntry == NULL) {
                pEntry = (struct hashTable*)malloc(sizeof(struct hashTable));
                if (pEntry == NULL) {
                    perror("malloc");
                    freeAll(pDiff);
                    pDiff = NULL;
                    return pRetVal;
                }
                strcpy(pEntry->key, words[j]);
                pEntry->value = 0;
                HASH_ADD_STR(pDiff, key, pEntry);
            }
            pEntry->value--;

            if (pEntry->value == 0) {
                HASH_DEL(pDiff, pEntry);
                free(pEntry);
            }
        }

        for (start = i; start < sLength - wordsSize * wordLength + 1; start += wordLength) {
            if (start != i) {
                memset(word, 0, sizeof(word));
                snprintf(word, wordLength + 1, "%s", s + start + (wordsSize - 1) * wordLength);

                pEntry = NULL;
                HASH_FIND_STR(pDiff, word, pEntry);
                if (NULL == pEntry) {
                    pEntry = (struct hashTable*)malloc(sizeof(struct hashTable));
                    if (pEntry == NULL) {
                        perror("malloc");
                        freeAll(pDiff);
                        pDiff = NULL;
                        return pRetVal;
                    }
                    strcpy(pEntry->key, word);
                    pEntry->value = 0;
                    HASH_ADD_STR(pDiff, key, pEntry);
                }
                pEntry->value++;

                if (pEntry->value == 0) {
                    HASH_DEL(pDiff, pEntry);
                    free(pEntry);
                }

                snprintf(word, wordLength + 1, "%s", s + start - wordLength);

                pEntry = NULL;
                HASH_FIND_STR(pDiff, word, pEntry);
                if (NULL == pEntry) {
                    pEntry = (struct hashTable*)malloc(sizeof(struct hashTable));
                    if (pEntry == NULL) {
                        perror("malloc");
                        freeAll(pDiff);
                        pDiff = NULL;
                        return pRetVal;
                    }
                    strcpy(pEntry->key, word);
                    pEntry->value = 0;
                    HASH_ADD_STR(pDiff, key, pEntry);
                }
                pEntry->value--;

                if (pEntry->value == 0) {
                    HASH_DEL(pDiff, pEntry);
                    free(pEntry);
                }
            }

            if (HASH_COUNT(pDiff) == 0) {
                pRetVal[pos++] = start;
            }
        }

        freeAll(pDiff);
        pDiff = NULL;
    }
    (*returnSize) = pos;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> retVal;

        int wordsSize = words.size();
        int wordLength = words[0].size();
        int sLength = s.size();
        for (int i = 0; ((i < wordLength) && (i + wordsSize * wordLength <= sLength)); ++i) {
            unordered_map<string, int> differ;
            for (int j = 0; j < wordsSize; ++j) {
                ++differ[s.substr(i + j * wordLength, wordLength)];
            }

            for (string& word : words) {
                if (--differ[word] == 0) {
                    differ.erase(word);
                }
            }

            for (int start = i; start < sLength - wordsSize * wordLength + 1; start += wordLength) {
                if (start != i) {
                    string word = s.substr(start + (wordsSize - 1) * wordLength, wordLength);

                    if (++differ[word] == 0) {
                        differ.erase(word);
                    }

                    word = s.substr(start - wordLength, wordLength);

                    if (--differ[word] == 0) {
                        differ.erase(word);
                    }
                }

                if (differ.empty() == true) {
                    retVal.emplace_back(start);
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
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        retVal = []

        wordsSize = len(words)
        wordLength = len(words[0])
        sLength = len(s)

        for i in range(wordLength):
            if i + wordsSize * wordLength > sLength:
                break

            differ = Counter()
            for j in range(wordsSize):
                word = s[i + j * wordLength: i + (j + 1) * wordLength]
                differ[word] += 1

            for word in words:
                differ[word] -= 1
                if differ[word] == 0:
                    del differ[word]

            for start in range(i, sLength - wordsSize * wordLength + 1, wordLength):
                if start != i:
                    wordLeft = start + (wordsSize - 1) * wordLength
                    wordRight = start + wordsSize * wordLength
                    word = s[wordLeft:wordRight]

                    differ[word] += 1
                    if differ[word] == 0:
                        del differ[word]

                    word = s[start - wordLength: start]

                    differ[word] -= 1
                    if differ[word] == 0:
                        del differ[word]

                differSize = len(differ)
                if differSize == 0:
                    retVal.append(start)

        return retVal
```

</details>

## [76. Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/)

- [Official](https://leetcode.cn/problems/minimum-window-substring/solutions/257359/zui-xiao-fu-gai-zi-chuan-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given two strings s and t of lengths m and n respectively,
return the minimum window substring of s such that every character in t (including duplicates) is included in the window.
If there is no such substring, return the empty string "".

The testcases will be generated such that the answer is unique.

A substring is a contiguous sequence of characters within the string.

Example 1:
Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.

Example 2:
Input: s = "a", t = "a"
Output: "a"
Explanation: The entire string s is the minimum window.

Example 3:
Input: s = "a", t = "aa"
Output: ""
Explanation: Both 'a's from t must be included in the window.
Since the largest window of s only has one 'a', return empty string.

Constraints:
m == s.length
n == t.length
1 <= m, n <= 10^5
s and t consist of uppercase and lowercase English letters.

Follow up: Could you find an algorithm that runs in O(m + n) time?
```

<details><summary>Hint</summary>

```text
1. Use two pointers to create a window of letters in s, which would have all the characters from t.
2. Expand the right pointer until all the characters of t are covered.
3. Once all the characters are covered,
   move the left pointer and ensure that all the characters are still covered to minimize the subarray size.
4. Continue expanding the right and left pointers until you reach the end of s.
```

</details>

</details>

<details><summary>C</summary>

```c
char* minWindow(char* s, char* t) {
    char* pRetVal = "";

    int sSize = strlen(s);
    int tSize = strlen(t);

    int i;

#define ASCII_SIZE (128)      // s and t consist of uppercase and lowercase English letters.
    int hashSet[ASCII_SIZE];  // use hash set to record character in t
    memset(hashSet, 0, sizeof(hashSet));
    for (i = 0; i < tSize; ++i) {
        ++hashSet[(unsigned char)t[i]];
    }

    /* Process
     *  |   0  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |  10  |  11  |  12  | ABC           |
     *  |------------------------------------------------------------------------------------------|---------------|
     *  |   A  |   D  |   O  |   B  |   E  |   C  |   O  |   D  |   E  |   B  |   A  |   N  |   C  |               |
     *  | head |      |      |      |      | tail |      |      |      |      |      |      |      | => ADOBEC     |
     *  |      | head |      |      |      | tail |      |      |      |      |      |      |      | -X-> DOBEC    |
     *  |      | head |      |      |      |      |      |      |      |      | tail |      |      | => DOBECODEBA |
     *  |      |      | head |      |      |      |      |      |      |      | tail |      |      | => OBECODEBA  |
     *  |      |      |      | head |      |      |      |      |      |      | tail |      |      | => BECODEBA   |
     *  |      |      |      |      | head |      |      |      |      |      | tail |      |      | => ECODEBA    |
     *  |      |      |      |      |      | head |      |      |      |      | tail |      |      | => CODEBA     |
     *  |      |      |      |      |      |      | head |      |      |      | tail |      |      | -X-> ODEBA    |
     *  |      |      |      |      |      |      | head |      |      |      |      |      | tail | => ODEBANC    |
     *  |      |      |      |      |      |      |      | head |      |      |      |      | tail | => DEBANC     |
     *  |      |      |      |      |      |      |      |      | head |      |      |      | tail | => EBANC      |
     *  |      |      |      |      |      |      |      |      |      | head |      |      | tail | => BANC       |
     */
    int count = 0;
    int head = 0;
    int retHead = 0;
    int retTail = 0;
    int minLen = INT_MAX;
    for (i = 0; i < sSize; ++i) {
        // update hash set by character in s
        --hashSet[(unsigned char)s[i]];

        // if character both in t and s
        if (hashSet[(unsigned char)s[i]] >= 0) {
            ++count;
        }

        while (count == tSize) {
            // update head and tail according to Minimum record
            if ((i - head + 1) < minLen) {
                minLen = i - head + 1;
                retHead = head;
                retTail = i;
            }

            // update hash set by character in s
            ++hashSet[(unsigned char)s[head]];

            // if character in s
            if (hashSet[(unsigned char)s[head]] > 0) {
                --count;
            }

            // move head
            head++;
        }
    }
    if (minLen != INT_MAX) {
        s[retTail + 1] = 0;
        pRetVal = &(s[retHead]);
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string minWindow(string s, string t) {
        string retVal;

        int sSize = s.size();
        int tSize = t.size();

        unordered_map<char, int> hashSet;
        for (char c : t) {
            ++hashSet[c];
        }

        /* Process
         *  |   0  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |  10  |  11  |  12  | ABC           |
         *  |------------------------------------------------------------------------------------------|---------------|
         *  |   A  |   D  |   O  |   B  |   E  |   C  |   O  |   D  |   E  |   B  |   A  |   N  |   C  |               |
         *  | head |      |      |      |      | tail |      |      |      |      |      |      |      | => ADOBEC     |
         *  |      | head |      |      |      | tail |      |      |      |      |      |      |      | -X-> DOBEC    |
         *  |      | head |      |      |      |      |      |      |      |      | tail |      |      | => DOBECODEBA |
         *  |      |      | head |      |      |      |      |      |      |      | tail |      |      | => OBECODEBA  |
         *  |      |      |      | head |      |      |      |      |      |      | tail |      |      | => BECODEBA   |
         *  |      |      |      |      | head |      |      |      |      |      | tail |      |      | => ECODEBA    |
         *  |      |      |      |      |      | head |      |      |      |      | tail |      |      | => CODEBA     |
         *  |      |      |      |      |      |      | head |      |      |      | tail |      |      | -X-> ODEBA    |
         *  |      |      |      |      |      |      | head |      |      |      |      |      | tail | => ODEBANC    |
         *  |      |      |      |      |      |      |      | head |      |      |      |      | tail | => DEBANC     |
         *  |      |      |      |      |      |      |      |      | head |      |      |      | tail | => EBANC      |
         *  |      |      |      |      |      |      |      |      |      | head |      |      | tail | => BANC       |
         */
        int count = 0;
        int head = 0;
        int retHead = 0;
        int retTail = 0;
        int minLen = numeric_limits<int>::max();
        for (int i = 0; i < sSize; ++i) {
            // update hash set by character in s
            --hashSet[s[i]];

            // if character both in t and s
            if (hashSet[s[i]] >= 0) {
                ++count;
            }

            while (count == tSize) {
                // update head and tail according to Minimum record
                if ((i - head + 1) < minLen) {
                    minLen = i - head + 1;
                    retHead = head;
                    retTail = i;
                }

                // update hash set by character in s
                ++hashSet[s[head]];

                // if character in s
                if (hashSet[s[head]] > 0) {
                    --count;
                }

                // move head
                head++;
            }
        }
        if (minLen != numeric_limits<int>::max()) {
            s[retTail + 1] = 0;
            retVal = &(s[retHead]);
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
        # s and t consist of uppercase and lowercase English letters.
        self.ASCII_SIZE = 128

    def minWindow(self, s: str, t: str) -> str:
        retVal = ""

        sSize = len(s)
        tSize = len(t)

        hashSet = [0] * self.ASCII_SIZE
        for c in t:
            hashSet[ord(c)] += 1

        # /* Process
        #  *  |   0  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |  10  |  11  |  12  | ABC           |
        #  *  |------------------------------------------------------------------------------------------|---------------|
        #  *  |   A  |   D  |   O  |   B  |   E  |   C  |   O  |   D  |   E  |   B  |   A  |   N  |   C  |               |
        #  *  | head |      |      |      |      | tail |      |      |      |      |      |      |      | => ADOBEC     |
        #  *  |      | head |      |      |      | tail |      |      |      |      |      |      |      | -X-> DOBEC    |
        #  *  |      | head |      |      |      |      |      |      |      |      | tail |      |      | => DOBECODEBA |
        #  *  |      |      | head |      |      |      |      |      |      |      | tail |      |      | => OBECODEBA  |
        #  *  |      |      |      | head |      |      |      |      |      |      | tail |      |      | => BECODEBA   |
        #  *  |      |      |      |      | head |      |      |      |      |      | tail |      |      | => ECODEBA    |
        #  *  |      |      |      |      |      | head |      |      |      |      | tail |      |      | => CODEBA     |
        #  *  |      |      |      |      |      |      | head |      |      |      | tail |      |      | -X-> ODEBA    |
        #  *  |      |      |      |      |      |      | head |      |      |      |      |      | tail | => ODEBANC    |
        #  *  |      |      |      |      |      |      |      | head |      |      |      |      | tail | => DEBANC     |
        #  *  |      |      |      |      |      |      |      |      | head |      |      |      | tail | => EBANC      |
        #  *  |      |      |      |      |      |      |      |      |      | head |      |      | tail | => BANC       |
        #  */
        count = 0
        head = 0
        retHead = 0
        retTail = 0
        minLen = float('inf')
        for i in range(sSize):
            # update hash set by character in s
            hashSet[ord(s[i])] -= 1

            # if character both in t and s
            if hashSet[ord(s[i])] >= 0:
                count += 1

            while (count == tSize):
                # update head and tail according to Minimum record
                if (i - head + 1) < minLen:
                    minLen = i - head + 1
                    retHead = head
                    retTail = i

                # update hash set by character in s
                hashSet[ord(s[head])] += 1

                # if character in s
                if hashSet[ord(s[head])] > 0:
                    count -= 1

                #  move head
                head += 1
        if minLen != float('inf'):
            retVal = s[retHead:retTail+1]

        return retVal
```

</details>

## [209. Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/)

- [Official](https://leetcode.com/problems/minimum-size-subarray-sum/editorial/)
- [Official](https://leetcode.cn/problems/minimum-size-subarray-sum/solutions/305704/chang-du-zui-xiao-de-zi-shu-zu-by-leetcode-solutio/)

<details><summary>Description</summary>

```text
Given an array of positive integers nums and a positive integer target,
return the minimal length of a subarray whose sum is greater than or equal to target.
If there is no such subarray, return 0 instead.

Example 1:
Input: target = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: The subarray [4,3] has the minimal length under the problem constraint.

Example 2:
Input: target = 4, nums = [1,4,4]
Output: 1

Example 3:
Input: target = 11, nums = [1,1,1,1,1,1,1,1]
Output: 0

Constraints:
1 <= target <= 10^9
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^4

Follow up: If you have figured out the O(n) solution,
try coding another solution of which the time complexity is O(n log(n)).
```

</details>

<details><summary>C</summary>

```c
int minSubArrayLen(int target, int* nums, int numsSize) {
    int retVal = numsSize + 1;

    int sum = 0;
    int head = 0;
    int tail;
    for (tail = 0; tail < numsSize; ++tail) {
        sum += nums[tail];
        while (sum >= target) {
            retVal = fmin(retVal, (tail - head + 1));
            sum -= nums[head++];
        }
    }
    if (retVal == numsSize + 1) {
        retVal = 0;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int retVal = 0;

        int len = nums.size();
        retVal = len + 1;
        int sum = 0;
        int head = 0;
        int tail;
        for (tail = 0; tail < len; ++tail) {
            sum += nums[tail];
            while (sum >= target) {
                retVal = min(retVal, tail - head + 1);

                sum -= nums[head];
                ++head;
            }
        }
        if (retVal == len + 1) {
            retVal = 0;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minSubArrayLen(self, target: int, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)
        retVal = numsSize + 1
        sum = 0
        head = 0
        for tail in range(numsSize):
            sum += nums[tail]
            while sum >= target:
                retVal = min(retVal, tail - head + 1)
                sum -= nums[head]
                head += 1

        if retVal == numsSize + 1:
            retVal = 0

        return retVal
```

</details>

## [424. Longest Repeating Character Replacement](https://leetcode.com/problems/longest-repeating-character-replacement/)

- [Official](https://leetcode.com/problems/longest-repeating-character-replacement/editorial/)
- [Official](https://leetcode.cn/problems/longest-repeating-character-replacement/solutions/586648/ti-huan-hou-de-zui-chang-zhong-fu-zi-fu-eaacp/)

<details><summary>Description</summary>

```text
You are given a string s and an integer k.
You can choose any character of the string and change it to any other uppercase English character.
You can perform this operation at most k times.

Return the length of the longest substring containing the same letter you can get after performing the above operations.

Example 1:
Input: s = "ABAB", k = 2
Output: 4
Explanation: Replace the two 'A's with two 'B's or vice versa.

Example 2:
Input: s = "AABABBA", k = 1
Output: 4
Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
The substring "BBBB" has the longest repeating letters, which is 4.

Constraints:
1 <= s.length <= 10^5
s consists of only uppercase English letters.
0 <= k <= s.length
```

</details>

<details><summary>C</summary>

```c
int characterReplacement(char* s, int k) {
    int retVal = 0;

    // s consists of only uppercase English letters.
#define MAX_RECORD (26)
    int Record[MAX_RECORD];
    memset(Record, 0, sizeof(Record));

    int maxRecord = 0;
    int sSize = strlen(s);
    int left = 0;
    int right = 0;
    while (right < sSize) {
        Record[s[right] - 'A']++;

        maxRecord = fmax(maxRecord, Record[s[right] - 'A']);
        if (right - left + 1 - maxRecord > k) {
            Record[s[left] - 'A']--;
            left++;
        }

        right++;
    }
    retVal = right - left;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int characterReplacement(string s, int k) {
        int retVal = 0;

        // s consists of only uppercase English letters.
#define MAX_RECORD (26)
        vector<int> Record(MAX_RECORD, 0);

        int maxRecord = 0;
        int sSize = s.length();
        int left = 0;
        int right = 0;
        while (right < sSize) {
            Record[s[right] - 'A']++;

            maxRecord = max(maxRecord, Record[s[right] - 'A']);
            if (right - left + 1 - maxRecord > k) {
                Record[s[left] - 'A']--;
                left++;
            }

            right++;
        }
        retVal = right - left;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def characterReplacement(self, s: str, k: int) -> int:
        retVal = 0

        # s consists of only uppercase English letters.
        MAX_RECORD = 26
        Record = [0] * MAX_RECORD

        maxRecord = 0
        sSize = len(s)
        left = 0
        right = 0
        while right < sSize:
            idx = ord(s[right]) - ord("A")
            Record[idx] += 1

            maxRecord = max(maxRecord, Record[idx])
            if right - left + 1 - maxRecord > k:
                Record[ord(s[left]) - ord("A")] -= 1
                left += 1

            right += 1

        retVal = right - left

        return retVal
```

</details>

## [438. Find All Anagrams in a String](https://leetcode.com/problems/find-all-anagrams-in-a-string/)

- [Official](https://leetcode.cn/problems/find-all-anagrams-in-a-string/solutions/1123971/zhao-dao-zi-fu-chuan-zhong-suo-you-zi-mu-xzin/)

<details><summary>Description</summary>

```text
Given two strings s and p, return an array of all the start indices of p's anagrams in s.
You may return the answer in any order.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase,
typically using all the original letters exactly once.

Example 1:
Input: s = "cbaebabacd", p = "abc"
Output: [0,6]
Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".

Example 2:
Input: s = "abab", p = "ab"
Output: [0,1,2]
Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".

Constraints:
1 <= s.length, p.length <= 3 * 10^4
s and p consist of lowercase English letters.
```

</details>

<details><summary>C</summary>

```c
#define MAX_LETTERS (26)  // s and p consist of lowercase English letters.
bool isSame(int* pRecordS, int* pRecordP) {
    int retVal = false;

    int i;
    for (i = 0; i < MAX_LETTERS; i++) {
        if (pRecordS[i] != pRecordP[i]) {
            return retVal;
        }
    }
    retVal = true;

    return retVal;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findAnagrams(char* s, char* p, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    int sSize = strlen(s);
    int pSize = strlen(p);
    if (sSize < pSize) {
        return pRetVal;
    }

    pRetVal = (int*)malloc(sSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (sSize * sizeof(int)));

    int sCount[MAX_LETTERS];
    memset(sCount, 0, sizeof(sCount));
    int pCount[MAX_LETTERS];
    memset(pCount, 0, sizeof(pCount));

    int i;
    for (i = 0; i < pSize; i++) {
        sCount[s[i] - 'a']++;
        pCount[p[i] - 'a']++;
    }
    if (isSame(sCount, pCount) == true) {
        pRetVal[(*returnSize)++] = 0;
    }

    for (i = pSize; i < sSize; i++) {
        sCount[s[i] - 'a']++;
        sCount[s[i - pSize] - 'a']--;
        if (isSame(sCount, pCount) == true) {
            pRetVal[(*returnSize)++] = i - pSize + 1;
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
    int letters = 26;  // s and p consist of lowercase English letters.

   public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> retVal;

        int sSize = s.size();
        int pSize = p.size();
        if (sSize < pSize) {
            return retVal;
        }

        vector<int> sCount(letters, 0);
        vector<int> pCount(letters, 0);
        for (int i = 0; i < pSize; ++i) {
            ++sCount[s[i] - 'a'];
            ++pCount[p[i] - 'a'];
        }
        if (sCount == pCount) {
            retVal.emplace_back(0);
        }

        for (int i = pSize; i < sSize; ++i) {
            ++sCount[s[i] - 'a'];
            --sCount[s[i - pSize] - 'a'];
            if (sCount == pCount) {
                retVal.emplace_back(i - pSize + 1);
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
        self.letters = 26  # s and p consist of lowercase English letters.

    def findAnagrams(self, s: str, p: str) -> List[int]:
        retVal = []

        sSize = len(s)
        pSize = len(p)
        if sSize < pSize:
            return retVal

        sCount = [0] * self.letters
        pCount = [0] * self.letters
        for i in range(pSize):
            sCount[ord(s[i]) - ord('a')] += 1
            pCount[ord(p[i]) - ord('a')] += 1
        if sCount == pCount:
            retVal.append(0)

        for i in range(pSize, sSize):
            sCount[ord(s[i]) - ord('a')] += 1
            sCount[ord(s[i - pSize]) - ord('a')] -= 1
            if sCount == pCount:
                retVal.append(i - pSize + 1)

        return retVal
```

</details>

## [567. Permutation in String](https://leetcode.com/problems/permutation-in-string/)

- [Official](https://leetcode.com/problems/permutation-in-string/editorial/)
- [Official](https://leetcode.cn/problems/permutation-in-string/solutions/599202/zi-fu-chuan-de-pai-lie-by-leetcode-solut-7k7u/)

<details><summary>Description</summary>

```text
Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.

In other words, return true if one of s1's permutations is the substring of s2.

Example 1:
Input: s1 = "ab", s2 = "eidbaooo"
Output: true
Explanation: s2 contains one permutation of s1 ("ba").

Example 2:
Input: s1 = "ab", s2 = "eidboaoo"
Output: false

Constraints:
1 <= s1.length, s2.length <= 10^4
s1 and s2 consist of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Obviously, brute force will result in TLE. Think of something else.
2. How will you check whether one string is a permutation of another string?
3. One way is to sort the string and then compare. But, Is there a better way?
4. If one string is a permutation of another string then they must have one common metric. What is that?
5. Both strings must have same character frequencies, if one is permutation of another.
   Which data structure should be used to store frequencies?
6. What about hash table? An array of size 26?
```

</details>

</details>

<details><summary>C</summary>

```c
#define MAX_LETTERS_SIZE (26)  // s1 and s2 consist of lowercase English letters.
bool isCountEqual(int* pCount1, int* pCount2) {
    bool retVal = false;

    int i;
    for (i = 0; i < MAX_LETTERS_SIZE; ++i) {
        if (pCount1[i] != pCount2[i]) {
            return retVal;
        }
    }
    retVal = true;

    return retVal;
}
bool checkInclusion(char* s1, char* s2) {
    bool retVal = false;

    int s1Size = strlen(s1);
    int s2Size = strlen(s2);
    if (s2Size < s1Size) {
        return retVal;
    }

    int count1[MAX_LETTERS_SIZE];
    memset(count1, 0, sizeof(count1));
    int count2[MAX_LETTERS_SIZE];
    memset(count2, 0, sizeof(count2));

    int i;
    for (i = 0; i < s1Size; ++i) {
        ++count1[(unsigned int)(s1[i] - 'a')];
        ++count2[(unsigned int)(s2[i] - 'a')];
    }
    if (isCountEqual(count1, count2) == true) {
        retVal = true;
        return retVal;
    }

    for (i = s1Size; i < s2Size; ++i) {
        ++count2[(unsigned int)(s2[i] - 'a')];
        --count2[(unsigned int)(s2[i - s1Size] - 'a')];
        if (isCountEqual(count1, count2) == true) {
            retVal = true;
            return retVal;
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
    int lettersSize = 26;  // s1 and s2 consist of lowercase English letters.

   public:
    bool checkInclusion(string s1, string s2) {
        bool retVal = false;

        int s1Size = s1.size();
        int s2Size = s2.size();
        if (s2Size < s1Size) {
            return retVal;
        }

        vector<int> count1(lettersSize, 0);
        vector<int> count2(lettersSize, 0);

        for (int i = 0; i < s1Size; ++i) {
            ++count1[s1[i] - 'a'];
            ++count2[s2[i] - 'a'];
        }
        if (count1 == count2) {
            retVal = true;
            return retVal;
        }

        for (int i = s1Size; i < s2Size; ++i) {
            ++count2[s2[i] - 'a'];
            --count2[s2[i - s1Size] - 'a'];
            if (count1 == count2) {
                retVal = true;
                return retVal;
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
        self.letters = 26  # // s1 and s2 consist of lowercase English letters.

    def checkInclusion(self, s1: str, s2: str) -> bool:
        retVal = False

        s1Size = len(s1)
        s2Size = len(s2)
        if s2Size < s1Size:
            return retVal

        count1 = [0] * self.letters
        count2 = [0] * self.letters

        for i in range(s1Size):
            count1[ord(s1[i]) - ord('a')] += 1
            count2[ord(s2[i]) - ord('a')] += 1
        if count1 == count2:
            retVal = True
            return retVal

        for i in range(s1Size, s2Size):
            count2[ord(s2[i]) - ord('a')] += 1
            count2[ord(s2[i-s1Size]) - ord('a')] -= 1
            if count1 == count2:
                retVal = True
                return retVal

        return retVal
```

</details>

<details><summary>Rust</summary>

```rust
const COUNT_SIZE: usize = 26; // s1 and s2 consist of lowercase English letters.
impl Solution {
    pub fn check_inclusion(s1: String, s2: String) -> bool {
        let mut ret_val = false;

        let len1 = s1.len();
        let len2 = s2.len();
        if len2 < len1 {
            return ret_val;
        }

        let mut count1: [usize; COUNT_SIZE] = [0; COUNT_SIZE];
        let mut count2: [usize; COUNT_SIZE] = [0; COUNT_SIZE];

        for i in 0..len1 {
            count1[(s1.chars().nth(i).unwrap() as u8 - b'a') as usize] += 1;
            count2[(s2.chars().nth(i).unwrap() as u8 - b'a') as usize] += 1;
        }
        if count1 == count2 {
            ret_val = true;
            return ret_val;
        }

        for i in len1..len2 {
            count2[(s2.chars().nth(i).unwrap() as u8 - b'a') as usize] += 1;
            count2[(s2.chars().nth(i - len1).unwrap() as u8 - b'a') as usize] -= 1;
            if count1 == count2 {
                ret_val = true;
                break;
            }
        }

        return ret_val;
    }
}
```

</details>

## [632. Smallest Range Covering Elements from K Lists](https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/)

- [Official](https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/editorial/)
- [Official](https://leetcode.cn/problems/smallest-range-covering-elements-from-k-lists/solutions/355881/zui-xiao-qu-jian-by-leetcode-solution/)

<details><summary>Description</summary>

```text
You have k lists of sorted integers in non-decreasing order.
Find the smallest range that includes at least one number from each of the k lists.

We define the range [a, b] is smaller than range [c, d] if b - a < d - c or a < c if b - a == d - c.

Example 1:
Input: nums = [[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]
Output: [20,24]
Explanation:
List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
List 2: [0, 9, 12, 20], 20 is in range [20,24].
List 3: [5, 18, 22, 30], 22 is in range [20,24].

Example 2:
Input: nums = [[1,2,3],[1,2,3],[1,2,3]]
Output: [1,1]

Constraints:
nums.length == k
1 <= k <= 3500
1 <= nums[i].length <= 50
-10^5 <= nums[i][j] <= 10^5
nums[i] is sorted in non-decreasing order.
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
    }

    return (p1[0] > p2[0]);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* smallestRange(int** nums, int numsSize, int* numsColSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    int i, j;

    // Merge all lists with their list index
    int mergedIndex = 0;
    int mergedSize = 0;
    for (i = 0; i < numsSize; ++i) {
        mergedSize += numsColSize[i];
    }
    int merged[mergedSize][2];
    memset(merged, 0, sizeof(merged));
    for (i = 0; i < numsSize; ++i) {
        for (j = 0; j < numsColSize[i]; ++j) {
            merged[mergedIndex][0] = nums[i][j];
            merged[mergedIndex][1] = i;
            mergedIndex++;
        }
    }
    qsort(merged, mergedSize, sizeof(merged[0]), compareIntArray);

    // Two pointers to track the smallest range
    int freq[numsSize];
    memset(freq, 0, sizeof(freq));
    int rangeStart = 0;
    int rangeEnd = INT_MAX;
    int curRange;
    int count = 0;
    int left = 0;
    int right = 0;
    for (right = 0; right < mergedSize; right++) {
        freq[merged[right][1]]++;
        if (freq[merged[right][1]] == 1) {
            count++;
        }

        // When all lists are represented, try to shrink the window
        while (count == numsSize) {
            curRange = merged[right][0] - merged[left][0];
            if (curRange < rangeEnd - rangeStart) {
                rangeStart = merged[left][0];
                rangeEnd = merged[right][0];
            }

            freq[merged[left][1]]--;
            if (freq[merged[left][1]] == 0) {
                count--;
            }

            left++;
        }
    }

    pRetVal = (int*)calloc(2, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }
    pRetVal[0] = rangeStart;
    pRetVal[1] = rangeEnd;
    (*returnSize) = 2;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        vector<int> retVal;

        int numsSize = nums.size();

        // Merge all lists with their list index
        vector<pair<int, int>> merged;
        for (int i = 0; i < numsSize; ++i) {
            for (int num : nums[i]) {
                merged.push_back({num, i});
            }
        }
        sort(merged.begin(), merged.end());
        int mergedSize = merged.size();

        // Two pointers to track the smallest range
        unordered_map<int, int> freq;
        int rangeStart = 0;
        int rangeEnd = numeric_limits<int>::max();
        int count = 0;
        int left = 0;
        for (int right = 0; right < mergedSize; right++) {
            freq[merged[right].second]++;
            if (freq[merged[right].second] == 1) {
                count++;
            }

            // When all lists are represented, try to shrink the window
            while (count == numsSize) {
                int curRange = merged[right].first - merged[left].first;
                if (curRange < rangeEnd - rangeStart) {
                    rangeStart = merged[left].first;
                    rangeEnd = merged[right].first;
                }

                freq[merged[left].second]--;
                if (freq[merged[left].second] == 0) {
                    count--;
                }

                left++;
            }
        }

        retVal = {rangeStart, rangeEnd};

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def smallestRange(self, nums: List[List[int]]) -> List[int]:
        retVal = []

        numsSize = len(nums)

        # Merge all lists with their list index
        merged = []
        for i in range(numsSize):
            for num in nums[i]:
                merged.append((num, i))
        merged.sort()
        mergedSize = len(merged)

        # Two pointers to track the smallest range
        freq = defaultdict(int)
        rangeStart = 0
        rangeEnd = float("inf")
        count = 0
        left = 0
        for right in range(mergedSize):
            freq[merged[right][1]] += 1
            if freq[merged[right][1]] == 1:
                count += 1

            # When all lists are represented, try to shrink the window
            while count == numsSize:
                curRange = merged[right][0] - merged[left][0]
                if curRange < rangeEnd - rangeStart:
                    rangeStart = merged[left][0]
                    rangeEnd = merged[right][0]

                freq[merged[left][1]] -= 1
                if freq[merged[left][1]] == 0:
                    count -= 1

                left += 1

        retVal = [rangeStart, rangeEnd]

        return retVal
```

</details>

## [643. Maximum Average Subarray I](https://leetcode.com/problems/maximum-average-subarray-i/)

- [Official](https://leetcode.com/problems/maximum-average-subarray-i/editorial/)
- [Official](https://leetcode.cn/problems/maximum-average-subarray-i/solutions/590322/zi-shu-zu-zui-da-ping-jun-shu-i-by-leetc-us1k/)

<details><summary>Description</summary>

```text
You are given an integer array nums consisting of n elements, and an integer k.

Find a contiguous subarray whose length is equal to k that has the maximum average value and return this value.
Any answer with a calculation error less than 10-5 will be accepted.

Example 1:
Input: nums = [1,12,-5,-6,50,3], k = 4
Output: 12.75000
Explanation: Maximum average is (12 - 5 - 6 + 50) / 4 = 51 / 4 = 12.75

Example 2:
Input: nums = [5], k = 1
Output: 5.00000

Constraints:
n == nums.length
1 <= k <= n <= 10^5
-10^4 <= nums[i] <= 10^4
```

</details>

<details><summary>C</summary>

```c
double findMaxAverage(int* nums, int numsSize, int k) {
    double retVal = 0;

    int sum = 0;
    int i;
    for (i = 0; i < k; ++i) {
        sum += nums[i];
    }
    double max = sum;

    for (i = k; i < numsSize; ++i) {
        sum += (nums[i] - nums[i - k]);
        max = fmax(max, sum);
    }
    retVal = max / k;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    double findMaxAverage(vector<int>& nums, int k) {
        double retVal;

        int numsSize = nums.size();

        double sum = 0;
        for (int i = 0; i < k; ++i) {
            sum += nums[i];
        }
        double maxValue = sum;

        for (int i = k; i < numsSize; ++i) {
            sum += (nums[i] - nums[i - k]);
            maxValue = max(maxValue, sum);
        }
        retVal = maxValue / k;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def findMaxAverage(self, nums: List[int], k: int) -> float:
        retVal = 0

        numsSize = len(nums)

        sum = 0
        for i in range(k):
            sum += nums[i]
        maxValue = sum

        for i in range(k, numsSize):
            sum += (nums[i] - nums[i - k])
            maxValue = max(maxValue, sum)
        retVal = maxValue / k

        return retVal
```

</details>

## [713. Subarray Product Less Than K](https://leetcode.com/problems/subarray-product-less-than-k/)

- [Official](https://leetcode.com/problems/subarray-product-less-than-k/editorial/)
- [Official](https://leetcode.cn/problems/subarray-product-less-than-k/solutions/1463527/cheng-ji-xiao-yu-k-de-zi-shu-zu-by-leetc-92wl/)

<details><summary>Description</summary>

```text
Given an array of integers nums and an integer k,
return the number of contiguous subarrays where the product of all the elements in the subarray is strictly less than k.

Example 1:
Input: nums = [10,5,2,6], k = 100
Output: 8
Explanation: The 8 subarrays that have product less than 100 are:
[10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6]
Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.

Example 2:
Input: nums = [1,2,3], k = 0
Output: 0

Constraints:
1 <= nums.length <= 3 * 10^4
1 <= nums[i] <= 1000
0 <= k <= 10^6
```

<details><summary>Hint</summary>

```text
1. For each j, let opt(j) be the smallest i so that nums[i] * nums[i+1] * ... * nums[j] is less than k.
   opt is an increasing function.
```

</details>

</details>

<details><summary>C</summary>

```c
int numSubarrayProductLessThanK(int* nums, int numsSize, int k) {
    int retVal = 0;

    /* the product of nums could not be strictly less than 1
     *  1 <= nums.length <= 3 * 10^4
     *  1 <= nums[i] <= 1000
     *  0 <= k <= 10^6
     */
    if (k <= 1) {
        return retVal;
    }

    /* Sliding window with Two Pointer
     *  +--------------------------------------------+
     *  |    0   |      1      |   2   |      3      |
     *  +--------------------------------------------+
     *  |   10   |      5      |   2   |      6      |
     *  +--------------------------------------------+
     *  |  right -1-> right -2-> right -4-> right    |
     *  |  left  -3-> left                           |
     *  +--------------------------------------------+
     *  | product = 10                               |
     *  | product = 50, product = 100                |
     *  | product = 10                               |
     *  | product = 60                               |
     *  +--------------------------------------------+
     */
    int product = 1;
    int right = 0;
    int left = 0;
    for (right = 0; right < numsSize; right++) {
        product *= nums[right];
        while (product >= k) {
            product /= nums[left];
            left++;
        }
        retVal += (right - left + 1);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int retVal = 0;

        /* the product of nums could not be strictly less than 1
         *  1 <= nums.length <= 3 * 10^4
         *  1 <= nums[i] <= 1000
         *  0 <= k <= 10^6
         */
        if (k <= 1) {
            return retVal;
        }

        /* Sliding window with Two Pointer
         *  +--------------------------------------------+
         *  |    0   |      1      |   2   |      3      |
         *  +--------------------------------------------+
         *  |   10   |      5      |   2   |      6      |
         *  +--------------------------------------------+
         *  |  right -1-> right -2-> right -4-> right    |
         *  |  left  -3-> left                           |
         *  +--------------------------------------------+
         *  | product = 10                               |
         *  | product = 50, product = 100                |
         *  | product = 10                               |
         *  | product = 60                               |
         *  +--------------------------------------------+
         */
        int numsSize = nums.size();
        int product = 1;
        int right = 0;
        int left = 0;
        for (right = 0; right < numsSize; right++) {
            product *= nums[right];
            while (product >= k) {
                product /= nums[left];
                left++;
            }
            retVal += (right - left + 1);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def numSubarrayProductLessThanK(self, nums: List[int], k: int) -> int:
        retVal = 0

        # /* the product of nums could not be strictly less than 1
        #  *  1 <= nums.length <= 3 * 10^4
        #  *  1 <= nums[i] <= 1000
        #  *  0 <= k <= 10^6
        #  */
        if k <= 1:
            return retVal

        # /* Sliding window with Two Pointer
        #  *  +--------------------------------------------+
        #  *  |    0   |      1      |   2   |      3      |
        #  *  +--------------------------------------------+
        #  *  |   10   |      5      |   2   |      6      |
        #  *  +--------------------------------------------+
        #  *  |  right -1-> right -2-> right -4-> right    |
        #  *  |  left  -3-> left                           |
        #  *  +--------------------------------------------+
        #  *  | product = 10                               |
        #  *  | product = 50, product = 100                |
        #  *  | product = 10                               |
        #  *  | product = 60                               |
        #  *  +--------------------------------------------+
        #  */
        numsSize = len(nums)
        product = 1
        right = 0
        left = 0
        for right in range(numsSize):
            product *= nums[right]
            while product >= k:
                product /= nums[left]
                left += 1
            retVal += (right - left + 1)

        return retVal
```

</details>

## [904. Fruit Into Baskets](https://leetcode.com/problems/fruit-into-baskets/)  1516

- [Official](https://leetcode.com/problems/fruit-into-baskets/solutions/2960000/fruit-into-baskets/)
- [Official](https://leetcode.cn/problems/fruit-into-baskets/solutions/1893352/shui-guo-cheng-lan-by-leetcode-solution-1uyu/)

<details><summary>Description</summary>

```text
You are visiting a farm that has a single row of fruit trees arranged from left to right.
The trees are represented by an integer array fruits where fruits[i] is the type of fruit the ith tree produces.

You want to collect as much fruit as possible. However, the owner has some strict rules that you must follow:
- You only have two baskets, and each basket can only hold a single type of fruit.
  There is no limit on the amount of fruit each basket can hold.
- Starting from any tree of your choice, you must pick exactly one fruit from every tree (including the start tree)
  while moving to the right. The picked fruits must fit in one of your baskets.
- Once you reach a tree with fruit that cannot fit in your baskets, you must stop.

Given the integer array fruits, return the maximum number of fruits you can pick.

Example 1:
Input: fruits = [1,2,1]
Output: 3
Explanation: We can pick from all 3 trees.

Example 2:
Input: fruits = [0,1,2,2]
Output: 3
Explanation: We can pick from trees [1,2,2].
If we had started at the first tree, we would only pick from trees [0,1].

Example 3:
Input: fruits = [1,2,3,2,2]
Output: 4
Explanation: We can pick from trees [2,3,2,2].
If we had started at the first tree, we would only pick from trees [1,2].

Constraints:
1 <= fruits.length <= 10^5
0 <= fruits[i] < fruits.length
```

</details>

<details><summary>C</summary>

```c
int totalFruit(int* fruits, int fruitsSize) {
    int retVal = 0;

    // 1 <= fruits.length <= 10^5, 0 <= fruits[i] < fruits.length.
#define MAX_HASHTABLE ((int)(1e5))
    int HashTable[MAX_HASHTABLE];
    memset(HashTable, 0, sizeof(HashTable));
    unsigned int countHashTable = 0;
    int head = 0;
    int tail = 0;
    /* Example
     *          +--------------------------------------------+-----------------------------+
     *          | 3 | 3 | 3 | 1 | 2 | 1 | 1 | 2 | 3 | 3 | 4  |                             |
     *          +--------------------------------------------+-------------------------+---+
     *    tail  | 0 > 1 > 2 > 3 > 4                          | size: 1 > 1 > 1 > 2 > 3 |   |
     *    head  | 0                                          |  max: 1 > 2 > 3 > 4     | 4 |
     *          +--------------------------------------------+-------------------------+---|
     *    tail  |                 4                          | size: 3 > 3 > 3 > 2     |   |
     *    head  | 0 > 1 > 2 > 3                              |  max: 4 > 2             | 4 |
     *          +--------------------------------------------+-------------------------+---+
     *    tail  |                 4 > 5 > 6 > 7 > 8          | size: 2 > 2 > 2 > 2 > 3 |   |
     *    head  |             3                              |  max: 2 > 3 > 4 > 5     | 5 |
     *          +--------------------------------------------+-------------------------+---+
     *    tail  |                                 8          | size: 3 > 3 > 3 > 3 > 2 |   |
     *    head  |             3 > 4 > 5 > 6 > 7              |  max: 5 > 2             | 5 |
     *          +--------------------------------------------+-------------------------+---+
     *    tail  |                                 8 > 9 > 10 | size: 2 > 2 > 3         |   |
     *    head  |                             7              |  max: 2 > 3             | 5 |
     *          +--------------------------------------------+-------------------------+---+
     *    tail  |                                         10 | size: 3 > 2             |   |
     *    head  |                             7 > 8          |  max: 3 > 3             | 5 |
     *          +--------------------------------------------+-------------------------+---+
     */
    while (tail < fruitsSize) {
        if (HashTable[fruits[tail]] == 0) {
            ++countHashTable;
        }
        ++HashTable[fruits[tail]];

        while (countHashTable > 2) {
            --HashTable[fruits[head]];
            if (HashTable[fruits[head]] == 0) {
                --countHashTable;
            }
            ++head;
        }
        retVal = fmax(retVal, tail - head + 1);

        ++tail;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int totalFruit(vector<int>& fruits) {
        int retVal = 0;

        unordered_map<int, int> hashTable;
        int len = fruits.size();
        int head = 0;
        int tail = 0;
        /* Example
         *          +--------------------------------------------+-----------------------------+
         *          | 3 | 3 | 3 | 1 | 2 | 1 | 1 | 2 | 3 | 3 | 4  |                             |
         *          +--------------------------------------------+-------------------------+---+
         *    tail  | 0 > 1 > 2 > 3 > 4                          | size: 1 > 1 > 1 > 2 > 3 |   |
         *    head  | 0                                          |  max: 1 > 2 > 3 > 4     | 4 |
         *          +--------------------------------------------+-------------------------+---|
         *    tail  |                 4                          | size: 3 > 3 > 3 > 2     |   |
         *    head  | 0 > 1 > 2 > 3                              |  max: 4 > 2             | 4 |
         *          +--------------------------------------------+-------------------------+---+
         *    tail  |                 4 > 5 > 6 > 7 > 8          | size: 2 > 2 > 2 > 2 > 3 |   |
         *    head  |             3                              |  max: 2 > 3 > 4 > 5     | 5 |
         *          +--------------------------------------------+-------------------------+---+
         *    tail  |                                 8          | size: 3 > 3 > 3 > 3 > 2 |   |
         *    head  |             3 > 4 > 5 > 6 > 7              |  max: 5 > 2             | 5 |
         *          +--------------------------------------------+-------------------------+---+
         *    tail  |                                 8 > 9 > 10 | size: 2 > 2 > 3         |   |
         *    head  |                             7              |  max: 2 > 3             | 5 |
         *          +--------------------------------------------+-------------------------+---+
         *    tail  |                                         10 | size: 3 > 2             |   |
         *    head  |                             7 > 8          |  max: 3 > 3             | 5 |
         *          +--------------------------------------------+-------------------------+---+
         */
        while (tail < len) {
            hashTable[fruits[tail]]++;

            while (hashTable.size() > 2) {
                hashTable[fruits[head]]--;
                if (hashTable[fruits[head]] == 0) {
                    hashTable.erase(fruits[head]);
                }
                head++;
            }
            retVal = max(retVal, tail - head + 1);

            tail++;
        }

        return retVal;
    }
};
```

</details>

## [992. Subarrays with K Different Integers](https://leetcode.com/problems/subarrays-with-k-different-integers/)  2210

- [Official](https://leetcode.com/problems/subarrays-with-k-different-integers/editorial/)
- [Official](https://leetcode.cn/problems/subarrays-with-k-different-integers/solutions/597667/k-ge-bu-tong-zheng-shu-de-zi-shu-zu-by-l-ud34/)

<details><summary>Description</summary>

```text
Given an integer array nums and an integer k, return the number of good subarrays of nums.

A good array is an array where the number of different integers in that array is exactly k.
- For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.

A subarray is a contiguous part of an array.

Example 1:
Input: nums = [1,2,1,2,3], k = 2
Output: 7
Explanation: Subarrays formed with exactly 2 different integers: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2]

Example 2:
Input: nums = [1,2,1,3,4], k = 3
Output: 3
Explanation: Subarrays formed with exactly 3 different integers: [1,2,1,3], [2,1,3], [1,3,4].

Constraints:
1 <= nums.length <= 2 * 10^4
1 <= nums[i], k <= nums.length
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
int atMostDifferent(int* nums, int numsSize, int k) {
    int retVal = 0;

    int pHashTableSize = 0;
    struct hashTable* pHashTable = NULL;
    struct hashTable* pTemp;
    int key;
    int left = 0;
    int right = 0;
    for (right = 0; right < numsSize; ++right) {
        key = nums[right];
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &key, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                break;
            }
            pTemp->key = key;
            pTemp->value = 1;
            HASH_ADD_INT(pHashTable, key, pTemp);
        } else {
            pTemp->value += 1;
        }

        pHashTableSize = HASH_COUNT(pHashTable);
        while (pHashTableSize > k) {
            key = nums[left];
            pTemp = NULL;
            HASH_FIND_INT(pHashTable, &key, pTemp);
            if (pTemp != NULL) {
                pTemp->value -= 1;
                if (pTemp->value == 0) {
                    HASH_DEL(pHashTable, pTemp);
                    free(pTemp);
                    pHashTableSize = HASH_COUNT(pHashTable);
                }
            }
            ++left;
        }

        retVal += (right - left);
    }
    freeAll(pHashTable);

    return retVal;
}
int subarraysWithKDistinct(int* nums, int numsSize, int k) {
    int retVal = 0;

    // https://leetcode.com/problems/subarrays-with-k-different-integers/solutions/523136/JavaC++Python-Sliding-Window/
    retVal = atMostDifferent(nums, numsSize, k) - atMostDifferent(nums, numsSize, k - 1);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int atMostDifferent(vector<int>& nums, int k) {
        int retVal = 0;

        int numsSize = nums.size();
        unordered_map<int, int> hashTable;
        int left = 0;
        int right = 0;
        for (right = 0; right < numsSize; ++right) {
            hashTable[nums[right]]++;
            int hashTableSize = hashTable.size();
            while (hashTableSize > k) {
                hashTable[nums[left]]--;
                if (hashTable[nums[left]] == 0) {
                    hashTable.erase(nums[left]);
                    hashTableSize = hashTable.size();
                }
                left++;
            }
            retVal += (right - left);
        }

        return retVal;
    }
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        int retVal = 0;

        // https://leetcode.com/problems/subarrays-with-k-different-integers/solutions/523136/JavaC++Python-Sliding-Window/
        retVal = atMostDifferent(nums, k) - atMostDifferent(nums, k - 1);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def atMostDifferent(self, nums: List[int], k: int) -> int:
        retVal = 0

        hashTable = defaultdict(int)
        left = 0
        for right, rightValue in enumerate(nums):
            hashTable[rightValue] += 1

            hashTableSize = len(hashTable)
            while hashTableSize > k:
                leftValue= nums[left]
                hashTable[leftValue] -= 1
                if hashTable[leftValue] == 0:
                    del hashTable[leftValue]
                    hashTableSize = len(hashTable)
                left += 1

            retVal += (right - left)

        return retVal

    def subarraysWithKDistinct(self, nums: List[int], k: int) -> int:
        retVal = 0

        # https://leetcode.com/problems/subarrays-with-k-different-integers/solutions/523136/JavaC++Python-Sliding-Window/
        retVal = self.atMostDifferent(nums, k) - self.atMostDifferent(nums, k - 1)

        return retVal
```

</details>

## [1004. Max Consecutive Ones III](https://leetcode.com/problems/max-consecutive-ones-iii/)  1655

- [Official](https://leetcode.cn/problems/max-consecutive-ones-iii/solutions/608931/zui-da-lian-xu-1de-ge-shu-iii-by-leetcod-hw12/)

<details><summary>Description</summary>

```text
Given a binary array nums and an integer k,
return the maximum number of consecutive 1's in the array if you can flip at most k 0's.

Example 1:
Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
Output: 6
Explanation: [1,1,1,0,0,1,1,1,1,1,1]
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.

Example 2:
Input: nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
Output: 10
Explanation: [0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.

Constraints:
1 <= nums.length <= 10^5
nums[i] is either 0 or 1.
0 <= k <= nums.length
```

<details><summary>Hint</summary>

```text
1. One thing's for sure, we will only flip a zero if it extends an existing window of 1s.
   Otherwise, there's no point in doing it, right? Think Sliding Window!
2. Since we know this problem can be solved using the sliding window construct,
   we might as well focus in that direction for hints.
   Basically, in a given window, we can never have > K zeros, right?
3. We don't have a fixed size window in this case.
   The window size can grow and shrink depending upon the number of zeros we have
   (we don't actually have to flip the zeros here!).
4. The way to shrink or expand a window would be based on the number of zeros that can still be flipped and so on.
```

</details>

</details>

<details><summary>C</summary>

```c
int longestOnes(int *nums, int numsSize, int k) {
    int retVal = 0;

    int flip = 0;
    int left = 0;
    int right = 0;
    for (right = 0; right < numsSize; ++right) {
        flip += (1 - nums[right]);
        while (flip > k) {
            flip -= (1 - nums[left]);
            left += 1;
        }

        retVal = fmax(retVal, right - left + 1);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int longestOnes(vector<int>& nums, int k) {
        int retVal = 0;

        int numsSize = nums.size();

        int flip = 0;
        int left = 0;
        int right = 0;
        for (right = 0; right < numsSize; ++right) {
            flip += (1 - nums[right]);
            while (flip > k) {
                flip -= (1 - nums[left]);
                left += 1;
            }

            retVal = max(retVal, right - left + 1);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def longestOnes(self, nums: List[int], k: int) -> int:
        retVal = 0

        numsSize = len(nums)

        flip = 0
        left = 0
        right = 0
        for right in range(numsSize):
            flip += (1 - nums[right])
            while flip > k:
                flip -= (1 - nums[left])
                left += 1

            retVal = max(retVal, right - left + 1)

        return retVal
```

</details>

## [1052. Grumpy Bookstore Owner](https://leetcode.com/problems/grumpy-bookstore-owner/)  1418

- [Official](https://leetcode.com/problems/grumpy-bookstore-owner/editorial/)
- [Official](https://leetcode.cn/problems/grumpy-bookstore-owner/solutions/615133/ai-sheng-qi-de-shu-dian-lao-ban-by-leetc-dloq/)

<details><summary>Description</summary>

```text
There is a bookstore owner that has a store open for n minutes. Every minute, some number of customers enter the store.
You are given an integer array customers of length n where customers[i] is the number of the customer
that enters the store at the start of the ith minute and all those customers leave after the end of that minute.

On some minutes, the bookstore owner is grumpy.
You are given a binary array grumpy
where grumpy[i] is 1 if the bookstore owner is grumpy during the ith minute, and is 0 otherwise.

When the bookstore owner is grumpy, the customers of that minute are not satisfied, otherwise, they are satisfied.

The bookstore owner knows a secret technique to keep themselves not grumpy for minutes consecutive minutes,
but can only use it once.

Return the maximum number of customers that can be satisfied throughout the day.

Example 1:
Input: customers = [1,0,1,2,1,1,7,5], grumpy = [0,1,0,1,0,1,0,1], minutes = 3
Output: 16
Explanation: The bookstore owner keeps themselves not grumpy for the last 3 minutes.
The maximum number of customers that can be satisfied = 1 + 1 + 1 + 1 + 7 + 5 = 16.

Example 2:
Input: customers = [1], grumpy = [0], minutes = 1
Output: 1

Constraints:
n == customers.length == grumpy.length
1 <= minutes <= n <= 2 * 10^4
0 <= customers[i] <= 1000
grumpy[i] is either 0 or 1.
```

<details><summary>Hint</summary>

```text
1. Say the store owner uses their power in minute 1 to X and we have some answer A.
   If they instead use their power from minute 2 to X+1,
   we only have to use data from minutes 1, 2, X and X+1 to update our answer A.
```

</details>

</details>

<details><summary>C</summary>

```c
int maxSatisfied(int* customers, int customersSize, int* grumpy, int grumpySize, int minutes) {
    int retVal = 0;

    int i;

    // Calculate initial number of unrealized customers in first 'minutes' window
    int unrealizedCustomers = 0;
    for (i = 0; i < minutes; ++i) {
        unrealizedCustomers += customers[i] * grumpy[i];
    }
    int maxUnrealizedCustomers = unrealizedCustomers;

    // Slide the 'minutes' window across the rest of the customers array
    for (i = minutes; i < customersSize; ++i) {
        // Add current minute's unsatisfied customers if the owner is grumpy
        // and remove the customers that are out of the current window
        unrealizedCustomers += customers[i] * grumpy[i];
        unrealizedCustomers -= customers[i - minutes] * grumpy[i - minutes];

        // Update the maximum unrealized customers
        maxUnrealizedCustomers = fmax(maxUnrealizedCustomers, unrealizedCustomers);
    }

    // Start with maximum possible satisfied customers due to secret technique
    int totalCustomers = maxUnrealizedCustomers;

    // Add the satisfied customers during non-grumpy minutes
    for (i = 0; i < customersSize; ++i) {
        totalCustomers += customers[i] * (1 - grumpy[i]);
    }

    // Return the maximum number of satisfied customers
    retVal = totalCustomers;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int retVal = 0;

        // Calculate initial number of unrealized customers in first 'minutes' window
        int unrealizedCustomers = 0;
        for (int i = 0; i < minutes; ++i) {
            unrealizedCustomers += customers[i] * grumpy[i];
        }
        int maxUnrealizedCustomers = unrealizedCustomers;

        // Slide the 'minutes' window across the rest of the customers array
        int customersSize = customers.size();
        for (int i = minutes; i < customersSize; ++i) {
            // Add current minute's unsatisfied customers if the owner is grumpy
            // and remove the customers that are out of the current window
            unrealizedCustomers += customers[i] * grumpy[i];
            unrealizedCustomers -= customers[i - minutes] * grumpy[i - minutes];

            // Update the maximum unrealized customers
            maxUnrealizedCustomers = max(maxUnrealizedCustomers, unrealizedCustomers);
        }

        // Start with maximum possible satisfied customers due to secret technique
        int totalCustomers = maxUnrealizedCustomers;

        // Add the satisfied customers during non-grumpy minutes
        for (int i = 0; i < customersSize; ++i) {
            totalCustomers += customers[i] * (1 - grumpy[i]);
        }

        // Return the maximum number of satisfied customers
        retVal = totalCustomers;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxSatisfied(self, customers: List[int], grumpy: List[int], minutes: int) -> int:
        retVal = 0

        # Calculate initial number of unrealized customers in first 'minutes' window
        unrealizedCustomers = 0
        for i in range(minutes):
            unrealizedCustomers += customers[i] * grumpy[i]
        maxUnrealizedCustomers = unrealizedCustomers

        # Slide the 'minutes' window across the rest of the customers array
        customersSize = len(customers)
        for i in range(minutes, customersSize):
            # Add current minute's unsatisfied customers if the owner is grumpy
            # and remove the customers that are out of the current window
            unrealizedCustomers += customers[i] * grumpy[i]
            unrealizedCustomers -= customers[i - minutes] * grumpy[i - minutes]

            # Update the maximum unrealized customers
            maxUnrealizedCustomers = max(maxUnrealizedCustomers, unrealizedCustomers)

        # Start with maximum possible satisfied customers due to secret technique
        totalCustomers = maxUnrealizedCustomers

        # Add the satisfied customers during non-grumpy minutes
        for i in range(customersSize):
            totalCustomers += customers[i] * (1 - grumpy[i])

        # Return the maximum number of satisfied customers
        retVal = totalCustomers

        return retVal
```

</details>

## [1208. Get Equal Substrings Within Budget](https://leetcode.com/problems/get-equal-substrings-within-budget/)  1496

- [Official](https://leetcode.com/problems/get-equal-substrings-within-budget/editorial/)
- [Official](https://leetcode.cn/problems/get-equal-substrings-within-budget/solutions/591367/jin-ke-neng-shi-zi-fu-chuan-xiang-deng-b-higz/)

<details><summary>Description</summary>

```text
You are given two strings s and t of the same length and an integer maxCost.

You want to change s to t. Changing the ith character of s to ith character of t costs |s[i] - t[i]|
(i.e., the absolute difference between the ASCII values of the characters).

Return the maximum length of a substring of s that can be changed to be the same
as the corresponding substring of t with a cost less than or equal to maxCost.
If there is no substring from s that can be changed to its corresponding substring from t, return 0.

Example 1:
Input: s = "abcd", t = "bcdf", maxCost = 3
Output: 3
Explanation: "abc" of s can change to "bcd".
That costs 3, so the maximum length is 3.

Example 2:
Input: s = "abcd", t = "cdef", maxCost = 3
Output: 1
Explanation: Each character in s costs 2 to change to character in t,  so the maximum length is 1.

Example 3:
Input: s = "abcd", t = "acde", maxCost = 0
Output: 1
Explanation: You cannot make any change, so the maximum length is 1.

Constraints:
1 <= s.length <= 10^5
t.length == s.length
0 <= maxCost <= 10^6
s and t consist of only lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Calculate the differences between a[i] and b[i].
2. Use a sliding window to track the longest valid substring.
```

</details>

</details>

<details><summary>C</summary>

```c
int equalSubstring(char* s, char* t, int maxCost) {
    int retVal = 0;

    int sSize = strlen(s);

    int cost = 0;
    int start = 0;
    int end = 0;
    for (end = 0; end < sSize; ++end) {
        cost += abs(s[end] - t[end]);
        while (cost > maxCost) {
            cost -= abs(s[start] - t[start]);
            start += 1;
        }
        retVal = fmax(retVal, end - start + 1);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int equalSubstring(string s, string t, int maxCost) {
        int retVal = 0;

        int sSize = s.size();

        int cost = 0;
        int start = 0;
        int end = 0;
        for (end = 0; end < sSize; ++end) {
            cost += abs(s[end] - t[end]);
            while (cost > maxCost) {
                cost -= abs(s[start] - t[start]);
                start += 1;
            }
            retVal = max(retVal, end - start + 1);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def equalSubstring(self, s: str, t: str, maxCost: int) -> int:
        retVal = 0

        sSize = len(s)

        cost = 0
        start = 0
        end = 0
        for end in range(sSize):
            cost += abs(ord(s[end]) - ord(t[end]))
            while cost > maxCost:
                cost -= abs(ord(s[start]) - ord(t[start]))
                start += 1
            retVal = max(retVal, end-start+1)

        return retVal
```

</details>

## [1248. Count Number of Nice Subarrays](https://leetcode.com/problems/count-number-of-nice-subarrays/)  1623

- [Official](https://leetcode.com/problems/count-number-of-nice-subarrays/editorial/)
- [Official](https://leetcode.cn/problems/count-number-of-nice-subarrays/solutions/211268/tong-ji-you-mei-zi-shu-zu-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given an array of integers nums and an integer k. A continuous subarray is called nice if there are k odd numbers on it.

Return the number of nice sub-arrays.

Example 1:
Input: nums = [1,1,2,1,1], k = 3
Output: 2
Explanation: The only sub-arrays with 3 odd numbers are [1,1,2,1] and [1,2,1,1].

Example 2:
Input: nums = [2,4,6], k = 1
Output: 0
Explanation: There are no odd numbers in the array.

Example 3:
Input: nums = [2,2,2,1,2,2,1,2,2,2], k = 2
Output: 16

Constraints:
1 <= nums.length <= 50000
1 <= nums[i] <= 10^5
1 <= k <= nums.length
```

<details><summary>Hint</summary>

```text
1. After replacing each even by zero and every odd by one can we use prefix sum to find answer ?
2. Can we use two pointers to count number of sub-arrays ?
3. Can we store indices of odd numbers and for each k indices count number of sub-arrays contains them ?
```

</details>

</details>

<details><summary>C</summary>

```c
int numberOfSubarrays(int* nums, int numsSize, int k) {
    int retVal = 0;

    int initialGap = 0;
    int qsize = 0;
    int start = 0;
    for (int end = 0; end < numsSize; ++end) {
        // If current element is odd, increment qsize by 1.
        if (nums[end] % 2 == 1) {
            qsize += 1;
        }

        if (qsize == k) {
            initialGap = 0;

            // Calculate the number of even elements in the beginning of subarray.
            while (qsize == k) {
                qsize -= nums[start] % 2;
                initialGap += 1;
                start += 1;
            }
        }

        retVal += initialGap;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int retVal = 0;

        int numsSize = nums.size();

        int initialGap = 0;
        int qsize = 0;
        int start = 0;
        for (int end = 0; end < numsSize; ++end) {
            // If current element is odd, increment qsize by 1.
            if (nums[end] % 2 == 1) {
                qsize += 1;
            }

            if (qsize == k) {
                initialGap = 0;

                // Calculate the number of even elements in the beginning of subarray.
                while (qsize == k) {
                    qsize -= nums[start] % 2;
                    initialGap += 1;
                    start += 1;
                }
            }

            retVal += initialGap;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def numberOfSubarrays(self, nums: List[int], k: int) -> int:
        retVal = 0

        numsSize = len(nums)

        initialGap = 0
        qsize = 0
        start = 0
        for end in range(numsSize):
            # If current element is odd, increment qsize by 1.
            if nums[end] % 2 == 1:
                qsize += 1

            if qsize == k:
                initialGap = 0

                while qsize == k:   # Calculate the number of even elements in the beginning of subarray.
                    qsize -= nums[start] % 2
                    initialGap += 1
                    start += 1

            retVal += initialGap

        return retVal
```

</details>

## [1343. Number of Sub-arrays of Size K and Average Greater than or Equal to Threshold](https://leetcode.com/problems/number-of-sub-arrays-of-size-k-and-average-greater-than-or-equal-to-threshold/)  1317

<details><summary>Description</summary>

```text
Given an array of integers arr and two integers k and threshold,
return the number of sub-arrays of size k and average greater than or equal to threshold.

Example 1:
Input: arr = [2,2,2,2,5,5,5,8], k = 3, threshold = 4
Output: 3
Explanation: Sub-arrays [2,5,5],[5,5,5] and [5,5,8] have averages 4, 5 and 6 respectively.
All other sub-arrays of size 3 have averages less than 4 (the threshold).

Example 2:
Input: arr = [11,13,17,23,29,31,7,5,2,3], k = 3, threshold = 5
Output: 6
Explanation: The first 6 sub-arrays of size 3 have averages greater than 5. Note that averages are not integers.

Constraints:
1 <= arr.length <= 10^5
1 <= arr[i] <= 10^4
1 <= k <= arr.length
0 <= threshold <= 10^4
```

<details><summary>Hint</summary>

```text
1. Start with a window of size K and test its average against the threshold.
2. Keep moving the window by one element maintaining its size k until you cover the whole array.
   count number of windows that satisfy that its average is greater than the threshold.
```

</details>

</details>

<details><summary>C</summary>

```c
int numOfSubarrays(int* arr, int arrSize, int k, int threshold) {
    int retVal = 0;

    long long prefixSum = 0;  // 1 <= arr.length <= 10^5, 1 <= arr[i] <= 10^4, 1 <= k <= arr.length
    int i;
    for (i = 0; i < (k - 1); ++i) {
        prefixSum += arr[i];
    }

    for (i = (k - 1); i < arrSize; ++i) {
        prefixSum += arr[i];
        if ((prefixSum / k) >= threshold) {
            ++retVal;
        }

        prefixSum -= arr[i - k + 1];
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        int retVal = 0;

        int arrSize = arr.size();

        long long prefixSum = 0;  // 1 <= arr.length <= 10^5, 1 <= arr[i] <= 10^4, 1 <= k <= arr.length
        for (int i = 0; i < (k - 1); ++i) {
            prefixSum += arr[i];
        }

        for (int i = (k - 1); i < arrSize; ++i) {
            prefixSum += arr[i];
            if ((prefixSum / k) >= threshold) {
                ++retVal;
            }

            prefixSum -= arr[i - k + 1];
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def numOfSubarrays(self, arr: List[int], k: int, threshold: int) -> int:
        retVal = 0

        arrSize = len(arr)

        prefixSum = 0
        for i in range(k-1):
            prefixSum += arr[i]

        for i in range(k-1, arrSize):
            prefixSum += arr[i]
            if prefixSum // k >= threshold:
                retVal += 1
            prefixSum -= arr[i-k+1]

        return retVal
```

</details>

## [1423. Maximum Points You Can Obtain from Cards](https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/)  1573

- [Official](https://leetcode.cn/problems/maximum-points-you-can-obtain-from-cards/solutions/514347/ke-huo-de-de-zui-da-dian-shu-by-leetcode-7je9/)

<details><summary>Description</summary>

```text
There are several cards arranged in a row, and each card has an associated number of points.
The points are given in the integer array cardPoints.

In one step, you can take one card from the beginning or from the end of the row. You have to take exactly k cards.

Your score is the sum of the points of the cards you have taken.

Given the integer array cardPoints and the integer k, return the maximum score you can obtain.

Example 1:
Input: cardPoints = [1,2,3,4,5,6,1], k = 3
Output: 12
Explanation: After the first step, your score will always be 1.
However, choosing the rightmost card first will maximize your total score.
The optimal strategy is to take the three cards on the right, giving a final score of 1 + 6 + 5 = 12.

Example 2:
Input: cardPoints = [2,2,2], k = 2
Output: 4
Explanation: Regardless of which two cards you take, your score will always be 4.

Example 3:
Input: cardPoints = [9,7,7,9,7,7,9], k = 7
Output: 55
Explanation: You have to take all the cards. Your score is the sum of points of all cards.

Constraints:
1 <= cardPoints.length <= 10^5
1 <= cardPoints[i] <= 10^4
1 <= k <= cardPoints.length
```

</details>

<details><summary>C</summary>

```c
int maxScore(int* cardPoints, int cardPointsSize, int k) {
    int retVal = 0;

    /* maximum sum of k elements that take one card from the beginning or from the end of the row
     * => minimum sum of n-k continuously elements
     *
     *  +---------------------------+
     *  | 1 | 2 | 3 | 4 | 5 | 6 | 1 |
     *  +---------------------------+
     *  |->minsum(n-k)<-|
     *      |->minsum(n-k)<-|
     *          |->minsum(n-k)<-|
     *              |->minsum(n-k)<-|
     */
    int windowSum = 0;
    int windowSize = cardPointsSize - k;
    int i;
    for (i = 0; i < windowSize; ++i) {
        windowSum += cardPoints[i];
    }

    int totalSum = windowSum;
    int minSum = windowSum;
    for (i = windowSize; i < cardPointsSize; ++i) {
        totalSum += cardPoints[i];

        windowSum += (cardPoints[i] - cardPoints[i - windowSize]);
        minSum = fmin(minSum, windowSum);
    }
    retVal = totalSum - minSum;

    return retVal;
}
```

</details>

## [1456. Maximum Number of Vowels in a Substring of Given Length](https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/)  1263

- [Official](https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/editorial/)
- [Official](https://leetcode.cn/problems/maximum-number-of-vowels-in-a-substring-of-given-length/solutions/518995/ding-chang-zi-chuan-zhong-yuan-yin-de-zu-4ka7/)

<details><summary>Description</summary>

```text
Given a string s and an integer k, return the maximum number of vowel letters in any substring of s with length k.

Vowel letters in English are 'a', 'e', 'i', 'o', and 'u'.

Example 1:
Input: s = "abciiidef", k = 3
Output: 3
Explanation: The substring "iii" contains 3 vowel letters.

Example 2:
Input: s = "aeiou", k = 2
Output: 2
Explanation: Any substring of length 2 contains 2 vowels.

Example 3:
Input: s = "leetcode", k = 3
Output: 2
Explanation: "lee", "eet" and "ode" contain 2 vowels.

Constraints:
1 <= s.length <= 10^5
s consists of lowercase English letters.
1 <= k <= s.length
```

<details><summary>Hint</summary>

```text
1. Keep a window of size k and maintain the number of vowels in it.
2. Keep moving the window and update the number of vowels while moving. Answer is max number of vowels of any window.
```

</details>

</details>

<details><summary>C</summary>

```c
int maxVowels(char* s, int k) {
    int retVal = 0;

#define MAX_VOWELS_SIZE (5)
    char vowels[MAX_VOWELS_SIZE] = {'a', 'e', 'i', 'o', 'u'};

    int i, j;

    int count = 0;
    for (i = 0; i < k; ++i) {
        for (j = 0; j < MAX_VOWELS_SIZE; ++j) {
            if (s[i] == vowels[j]) {
                ++count;
                break;
            }
        }
    }
    retVal = count;

    int sSize = strlen(s);
    for (i = k; i < sSize; ++i) {
        for (j = 0; j < MAX_VOWELS_SIZE; ++j) {
            if (s[i] == vowels[j]) {
                ++count;
            }

            if (s[i - k] == vowels[j]) {
                --count;
            }
        }
        retVal = fmax(retVal, count);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxVowels(string s, int k) {
        int retVal = 0;

        vector<char> vowels = {'a', 'e', 'i', 'o', 'u'};

        int count = 0;
        for (int i = 0; i < k; ++i) {
            for (auto c : vowels) {
                if (s[i] == c) {
                    ++count;
                    break;
                }
            }
        }
        retVal = count;

        int sSize = s.size();
        for (int i = k; i < sSize; ++i) {
            for (auto c : vowels) {
                if (s[i] == c) {
                    ++count;
                }

                if (s[i - k] == c) {
                    --count;
                }
            }
            retVal = max(retVal, count);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxVowels(self, s: str, k: int) -> int:
        retVal = 0

        vowels = {'a', 'e', 'i', 'o', 'u'}

        count = 0
        for i in range(k):
            count += int(s[i] in vowels)
        retVal = count

        for i in range(k, len(s)):
            count += int(s[i] in vowels)
            count -= int(s[i - k] in vowels)
            retVal = max(retVal, count)

        return retVal
```

</details>

## [1493. Longest Subarray of 1's After Deleting One Element](https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/)  1423

- [Official](https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/editorial/)
- [Official](https://leetcode.cn/problems/longest-subarray-of-1s-after-deleting-one-element/solutions/327132/shan-diao-yi-ge-yuan-su-yi-hou-quan-wei-1-de-zui-c/)

<details><summary>Description</summary>

```text
Given a binary array nums, you should delete one element from it.

Return the size of the longest non-empty subarray containing only 1's in the resulting array.
Return 0 if there is no such subarray.

Example 1:
Input: nums = [1,1,0,1]
Output: 3
Explanation: After deleting the number in position 2, [1,1,1] contains 3 numbers with value of 1's.

Example 2:
Input: nums = [0,1,1,1,0,1,1,0,1]
Output: 5
Explanation: After deleting the number in position 4, [0,1,1,1,1,1,0,1] longest subarray with value of 1's is [1,1,1,1,1].

Example 3:
Input: nums = [1,1,1]
Output: 2
Explanation: You must delete one element.

Constraints:
1 <= nums.length <= 10^5
nums[i] is either 0 or 1.
```

<details><summary>Hint</summary>

```text
1. Maintain a sliding window where there is at most one zero on it.
```

</details>

</details>

<details><summary>C</summary>

```c
int longestSubarray(int* nums, int numsSize) {
    int retVal = 0;

    int i;
    int start = 0;
    int zeroCount = 0;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] == 0) {
            ++zeroCount;
        }

        while (zeroCount > 1) {
            if (nums[start] == 0) {
                --zeroCount;
            }
            ++start;
        }

        retVal = fmax(retVal, i - start);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int longestSubarray(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        int start = 0;
        int zeroCount = 0;
        for (int i = 0; i < numsSize; ++i) {
            if (nums[i] == 0) {
                ++zeroCount;
            }

            while (zeroCount > 1) {
                if (nums[start] == 0) {
                    --zeroCount;
                }
                ++start;
            }

            retVal = max(retVal, i - start);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def longestSubarray(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        start = 0
        zeroCount = 0
        for i in range(numsSize):
            if nums[i] == 0:
                zeroCount += 1

            while zeroCount > 1:
                if nums[start] == 0:
                    zeroCount -= 1
                start += 1

            retVal = max(retVal, i-start)

        return retVal
```

</details>

## [1652. Defuse the Bomb](https://leetcode.com/problems/defuse-the-bomb/)  1416

- [Official](https://leetcode.com/problems/defuse-the-bomb/editorial/)
- [Official](https://leetcode.cn/problems/defuse-the-bomb/solutions/1843157/chai-zha-dan-by-leetcode-solution-01x3/)

<details><summary>Description</summary>

```text
You have a bomb to defuse, and your time is running out!
Your informer will provide you with a circular array code of length of n and a key k.

To decrypt the code, you must replace every number. All the numbers are replaced simultaneously.
- If k > 0, replace the ith number with the sum of the next k numbers.
- If k < 0, replace the ith number with the sum of the previous k numbers.
- If k == 0, replace the ith number with 0.

As code is circular, the next element of code[n-1] is code[0], and the previous element of code[0] is code[n-1].

Given the circular array code and an integer key k, return the decrypted code to defuse the bomb!

Example 1:
Input: code = [5,7,1,4], k = 3
Output: [12,10,16,13]
Explanation: Each number is replaced by the sum of the next 3 numbers.
The decrypted code is [7+1+4, 1+4+5, 4+5+7, 5+7+1]. Notice that the numbers wrap around.

Example 2:
Input: code = [1,2,3,4], k = 0
Output: [0,0,0,0]
Explanation: When k is zero, the numbers are replaced by 0.

Example 3:
Input: code = [2,4,9,3], k = -2
Output: [12,5,6,13]
Explanation: The decrypted code is [3+9, 2+3, 4+2, 9+4].
Notice that the numbers wrap around again. If k is negative, the sum is of the previous numbers.

Constraints:
n == code.length
1 <= n <= 100
1 <= code[i] <= 100
-(n - 1) <= k <= n - 1
```

<details><summary>Hint</summary>

```text
1. As the array is circular, use modulo to find the correct index.
2. The constraints are low enough for a brute-force solution.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *decrypt(int *code, int codeSize, int k, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int *)calloc(codeSize, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }
    (*returnSize) = codeSize;

    if (k == 0) {
        return pRetVal;
    }

    int start = 1;
    int end = k;
    if (k < 0) {  // If k < 0, the starting point will be end of the array.
        start = codeSize - abs(k);
        end = codeSize - 1;
    }

    int sum = 0;
    for (int i = start; i <= end; i++) {
        sum += code[i];
    }

    // Scan through the code array as i moving to the right, update the window sum.
    for (int i = 0; i < codeSize; i++) {
        pRetVal[i] = sum;
        sum -= code[start % codeSize];
        sum += code[(end + 1) % codeSize];
        start++;
        end++;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> decrypt(vector<int>& code, int k) {
        vector<int> retVal;

        int codeSize = code.size();

        retVal.assign(codeSize, 0);
        if (k == 0) {
            return retVal;
        }

        int start = 1;
        int end = k;
        if (k < 0) {  // If k < 0, the starting point will be end of the array.
            start = codeSize - abs(k);
            end = codeSize - 1;
        }

        int sum = 0;
        for (int i = start; i <= end; i++) {
            sum += code[i];
        }

        // Scan through the code array as i moving to the right, update the window sum.
        for (int i = 0; i < codeSize; i++) {
            retVal[i] = sum;
            sum -= code[start % codeSize];
            sum += code[(end + 1) % codeSize];
            start++;
            end++;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def decrypt(self, code: List[int], k: int) -> List[int]:
        retVal = []

        codeSize = len(code)
        retVal = [0] * codeSize
        if k == 0:
            return retVal

        start = 1
        end = k
        if k < 0:  # If k < 0, the starting point will be end of the array.
            start = codeSize - abs(k)
            end = codeSize - 1

        sum = 0
        for i in range(start, end + 1):
            sum += code[i]

        # Scan through the code array as i moving to the right, update the window sum.
        for i in range(codeSize):
            retVal[i] = sum
            sum -= code[start % codeSize]
            sum += code[(end + 1) % codeSize]
            start += 1
            end += 1

        return retVal
```

</details>

## [1658. Minimum Operations to Reduce X to Zero](https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/)  1817

- [Official](https://leetcode.cn/problems/minimum-operations-to-reduce-x-to-zero/solutions/2047253/jiang-x-jian-dao-0-de-zui-xiao-cao-zuo-s-hl7u/)

<details><summary>Description</summary>

```text
You are given an integer array nums and an integer x.
In one operation, you can either remove the leftmost
or the rightmost element from the array nums and subtract its value from x.
Note that this modifies the array for future operations.

Return the minimum number of operations to reduce x to exactly 0 if it is possible, otherwise, return -1.

Example 1:
Input: nums = [1,1,4,2,3], x = 5
Output: 2
Explanation: The optimal solution is to remove the last two elements to reduce x to zero.

Example 2:
Input: nums = [5,6,7,8,9], x = 4
Output: -1

Example 3:
Input: nums = [3,2,20,1,1,3], x = 10
Output: 5
Explanation: The optimal solution is to remove the last three elements
and the first two elements (5 operations in total) to reduce x to zero.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^4
1 <= x <= 10^9
```

<details><summary>Hint</summary>

```text
1. Think in reverse; instead of finding the minimum prefix + suffix, find the maximum subarray.
2. Finding the maximum subarray is standard and can be done greedily.
```

</details>

</details>

<details><summary>C</summary>

```c
int minOperations(int* nums, int numsSize, int x) {
    int retVal = -1;

    int target = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        target += nums[i];
    }
    target -= x;
    if (target < 0) {
        return retVal;
    }

    /* https://leetcode.cn/problems/minimum-operations-to-reduce-x-to-zero/solutions/485281/shi-yong-hua-dong-chuang-kou-zhao-zhong-jian-zui-c/
     *  sum(fragment of nums) = sum(nums) - x
     *  Example
     *  +-------------------+   +----------------------------+
     *  | sum-x     | x=5   |   | x=10  | sum-x  | x=10      |
     *  | = 11-5    |       |   |       | =30-10 |           |
     *  +-------------------+   +----------------------------+
     *  | 1 | 1 | 4 | 2 | 3 |   | 3 | 2 |   20   | 1 | 1 | 3 |
     *  +-------------------+   +----------------------------+
     */
    int sum = 0;
    int head = 0;
    int tail = 0;
    for (tail = 0; tail < numsSize; ++tail) {
        sum += nums[tail];

        while (sum > target) {
            sum -= nums[head];
            ++head;
        }

        if (sum == target) {
            retVal = fmax(retVal, (tail - head + 1));
        }
    }
    retVal = ((retVal < 0) ? (-1) : (numsSize - retVal));

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minOperations(vector<int>& nums, int x) {
        int retVal = -1;

        int target = accumulate(nums.begin(), nums.end(), 0) - x;
        if (target < 0) {
            return retVal;
        }

        /* https://leetcode.cn/problems/minimum-operations-to-reduce-x-to-zero/solutions/485281/shi-yong-hua-dong-chuang-kou-zhao-zhong-jian-zui-c/
         *  sum(fragment of nums) = sum(nums) - x
         *  Example
         *  +-------------------+   +----------------------------+
         *  | sum-x     | x=5   |   | x=10  | sum-x  | x=10      |
         *  | = 11-5    |       |   |       | =30-10 |           |
         *  +-------------------+   +----------------------------+
         *  | 1 | 1 | 4 | 2 | 3 |   | 3 | 2 |   20   | 1 | 1 | 3 |
         *  +-------------------+   +----------------------------+
         */
        int numsSize = nums.size();
        int sum = 0;
        int start = 0;
        for (int tail = 0; tail < numsSize; ++tail) {
            sum += nums[tail];
            while (sum > target) {
                sum -= nums[start++];
            }

            if (sum == target) {
                retVal = max(retVal, tail - start + 1);
            }
        }

        if (retVal != -1) {
            retVal = numsSize - retVal;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minOperations(self, nums: List[int], x: int) -> int:
        retVal = -1

        target = sum(nums) - x
        if target < 0:
            return retVal

        # /* https://leetcode.cn/problems/minimum-operations-to-reduce-x-to-zero/solutions/485281/shi-yong-hua-dong-chuang-kou-zhao-zhong-jian-zui-c/
        #  *  sum(fragment of nums) = sum(nums) - x
        #  *  Example
        #  *  +-------------------+   +----------------------------+
        #  *  | sum-x     | x=5   |   | x=10  | sum-x  | x=10      |
        #  *  | = 11-5    |       |   |       | =30-10 |           |
        #  *  +-------------------+   +----------------------------+
        #  *  | 1 | 1 | 4 | 2 | 3 |   | 3 | 2 |   20   | 1 | 1 | 3 |
        #  *  +-------------------+   +----------------------------+
        #  */
        numsSize = len(nums)
        sumOfNums = 0
        start = 0
        for tail in range(numsSize):
            sumOfNums += nums[tail]
            while sumOfNums > target:
                sumOfNums -= nums[start]
                start += 1

            if sumOfNums == target:
                retVal = max(retVal, tail-start+1)

        if retVal != -1:
            retVal = numsSize - retVal

        return retVal
```

</details>

## [1838. Frequency of the Most Frequent Element](https://leetcode.com/problems/frequency-of-the-most-frequent-element/)  1876

- [Official](https://leetcode.com/problems/frequency-of-the-most-frequent-element/editorial/)
- [Official](https://leetcode.cn/problems/frequency-of-the-most-frequent-element/solutions/742719/zui-gao-pin-yuan-su-de-pin-shu-by-leetco-q5g9/)

<details><summary>Description</summary>

```text
The frequency of an element is the number of times it occurs in an array.

You are given an integer array nums and an integer k.
In one operation, you can choose an index of nums and increment the element at that index by 1.

Return the maximum possible frequency of an element after performing at most k operations.

Example 1:
Input: nums = [1,2,4], k = 5
Output: 3
Explanation: Increment the first element three times and the second element two times to make nums = [4,4,4].
4 has a frequency of 3.

Example 2:
Input: nums = [1,4,8,13], k = 5
Output: 2
Explanation: There are multiple optimal solutions:
- Increment the first element three times to make nums = [4,4,8,13]. 4 has a frequency of 2.
- Increment the second element four times to make nums = [1,8,8,13]. 8 has a frequency of 2.
- Increment the third element five times to make nums = [1,4,13,13]. 13 has a frequency of 2.

Example 3:
Input: nums = [3,9,6], k = 2
Output: 1

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^5
1 <= k <= 10^5
```

<details><summary>Hint</summary>

```text
1. Note that you can try all values in a brute force manner and find the maximum frequency of that value.
2. To find the maximum frequency of a value consider the biggest elements smaller than or equal to this value
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int maxFrequency(int* nums, int numsSize, int k) {
    int retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    long current = 0;
    int left = 0;
    long target;
    int right;
    for (right = 0; right < numsSize; right++) {
        target = nums[right];
        current += target;

        if ((right - left + 1) * target - current > k) {
            current -= nums[left];
            left++;
        }
    }
    retVal = numsSize - left;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxFrequency(vector<int>& nums, int k) {
        int retVal = 0;

        sort(nums.begin(), nums.end());

        int numsSize = nums.size();
        long current = 0;
        int left = 0;
        for (int right = 0; right < numsSize; right++) {
            long target = nums[right];
            current += target;

            if ((right - left + 1) * target - current > k) {
                current -= nums[left];
                left++;
            }
        }
        retVal = numsSize - left;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxFrequency(self, nums: List[int], k: int) -> int:
        retVal = 0

        nums.sort()

        numsSize = len(nums)
        current = 0
        left = 0
        for right in range(numsSize):
            target = nums[right]
            current += target

            if (right - left + 1) * target - current > k:
                current -= nums[left]
                left += 1
        retVal = numsSize - left

        return retVal
```

</details>

## [2090. K Radius Subarray Averages](https://leetcode.com/problems/k-radius-subarray-averages/)  1358

- [Official](https://leetcode.com/problems/k-radius-subarray-averages/editorial/)
- [Official](https://leetcode.cn/problems/k-radius-subarray-averages/solutions/1127983/ban-jing-wei-k-de-zi-shu-zu-ping-jun-zhi-jqo8/)

<details><summary>Description</summary>

```text
You are given a 0-indexed array nums of n integers, and an integer k.

The k-radius average for a subarray of nums centered at some index i
with the radius k is the average of all elements in nums between the indices i - k and i + k (inclusive).
If there are less than k elements before or after the index i, then the k-radius average is -1.

Build and return an array avgs of length n where avgs[i] is the k-radius average for the subarray centered at index i.

The average of x elements is the sum of the x elements divided by x, using integer division.
The integer division truncates toward zero, which means losing its fractional part.

For example, the average of four elements 2, 3, 1, and 5 is (2 + 3 + 1 + 5) / 4 = 11 / 4 = 2.75, which truncates to 2.

Example 1:
Input: nums = [7,4,3,9,1,8,5,2,6], k = 3
Output: [-1,-1,-1,5,4,4,-1,-1,-1]
Explanation:
- avg[0], avg[1], and avg[2] are -1 because there are less than k elements before each index.
- The sum of the subarray centered at index 3 with radius 3 is: 7 + 4 + 3 + 9 + 1 + 8 + 5 = 37.
  Using integer division, avg[3] = 37 / 7 = 5.
- For the subarray centered at index 4, avg[4] = (4 + 3 + 9 + 1 + 8 + 5 + 2) / 7 = 4.
- For the subarray centered at index 5, avg[5] = (3 + 9 + 1 + 8 + 5 + 2 + 6) / 7 = 4.
- avg[6], avg[7], and avg[8] are -1 because there are less than k elements after each index.

Example 2:
Input: nums = [100000], k = 0
Output: [100000]
Explanation:
- The sum of the subarray centered at index 0 with radius 0 is: 100000.
  avg[0] = 100000 / 1 = 100000.

Example 3:
Input: nums = [8], k = 100000
Output: [-1]
Explanation:
- avg[0] is -1 because there are less than k elements before and after index 0.

Constraints:
n == nums.length
1 <= n <= 10^5
0 <= nums[i], k <= 10^5
```

<details><summary>Hint</summary>

```text
1. To calculate the average of a subarray, you need the sum and the K. K is already given.
   How could you quickly calculate the sum of a subarray?
2. Use the Prefix Sums method to calculate the subarray sums.
3. It is possible that the sum of all the elements does not fit in a 32-bit integer type.
   Be sure to use a 64-bit integer type for the prefix sum array.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getAverages(int* nums, int numsSize, int k, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = numsSize;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, -1, ((*returnSize) * sizeof(int)));

    int i;

    // n == nums.length, 1 <= n <= 10^5, 0 <= nums[i], k <= 10^5
    long long prefixSum[numsSize + 1];
    memset(prefixSum, 0, sizeof(prefixSum));
    for (i = 0; i < numsSize; ++i) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    for (i = k; i < numsSize - k; ++i) {
        pRetVal[i] = (prefixSum[i + k + 1] - prefixSum[i - k]) / (2 * k + 1);
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> getAverages(vector<int>& nums, int k) {
        vector<int> retVal;

        int numsSize = nums.size();

        // n == nums.length, 1 <= n <= 10^5, 0 <= nums[i], k <= 10^5
        vector<long long> prefixSum(numsSize + 1, 0);
        for (int i = 0; i < numsSize; ++i) {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
        }

        retVal.resize(numsSize, -1);
        for (int i = k; i < numsSize - k; ++i) {
            retVal[i] = (prefixSum[i + k + 1] - prefixSum[i - k]) / (2 * k + 1);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def getAverages(self, nums: List[int], k: int) -> List[int]:
        retVal = []

        numsSize = len(nums)

        prefixSum = [0]
        for i in range(numsSize):
            prefixSum.append(prefixSum[i] + nums[i])

        retVal = [-1] * numsSize
        for i in range(k, numsSize - k):
            retVal[i] = (prefixSum[i + k + 1] - prefixSum[i - k]) // (2 * k + 1)

        return retVal
```

</details>

## [2024. Maximize the Confusion of an Exam](https://leetcode.com/problems/maximize-the-confusion-of-an-exam/)  1643

- [Official](https://leetcode.com/problems/maximize-the-confusion-of-an-exam/editorial/)
- [Official](https://leetcode.cn/problems/maximize-the-confusion-of-an-exam/solutions/1368825/kao-shi-de-zui-da-kun-rao-du-by-leetcode-qub5/)

<details><summary>Description</summary>

```text
A teacher is writing a test with n true/false questions, with 'T' denoting true and 'F' denoting false.
He wants to confuse the students by maximizing the number of consecutive questions with the same answer
(multiple trues or multiple falses in a row).

You are given a string answerKey, where answerKey[i] is the original answer to the ith question.
In addition, you are given an integer k, the maximum number of times you may perform the following operation:
- Change the answer key for any question to 'T' or 'F' (i.e., set answerKey[i] to 'T' or 'F').

Return the maximum number of consecutive 'T's or 'F's in the answer key after performing the operation at most k times.

Example 1:
Input: answerKey = "TTFF", k = 2
Output: 4
Explanation: We can replace both the 'F's with 'T's to make answerKey = "TTTT".
There are four consecutive 'T's.

Example 2:
Input: answerKey = "TFFT", k = 1
Output: 3
Explanation: We can replace the first 'T' with an 'F' to make answerKey = "FFFT".
Alternatively, we can replace the second 'T' with an 'F' to make answerKey = "TFFF".
In both cases, there are three consecutive 'F's.

Example 3:
Input: answerKey = "TTFTTFTT", k = 1
Output: 5
Explanation: We can replace the first 'F' to make answerKey = "TTTTTFTT"
Alternatively, we can replace the second 'F' to make answerKey = "TTFTTTTT".
In both cases, there are five consecutive 'T's.

Constraints:
n == answerKey.length
1 <= n <= 5 * 10^4
answerKey[i] is either 'T' or 'F'
1 <= k <= n
```

<details><summary>Hint</summary>

```text
1. Can we use the maximum length at the previous position to help us find the answer for the current position?
2. Can we use binary search to find the maximum consecutive same answer at every position?
```

</details>

</details>

<details><summary>C</summary>

```c
int maxConsecutiveAnswers(char* answerKey, int k) {
    int retVal = 0;

    // answerKey[i] is either 'T' or 'F'
#define MAX_RECORD (26)
    int Record[MAX_RECORD];
    memset(Record, 0, sizeof(Record));

    int maxRecord = 0;
    int answerKeySize = strlen(answerKey);
    int left = 0;
    int right = 0;
    while (right < answerKeySize) {
        Record[answerKey[right] - 'A']++;

        maxRecord = fmax(maxRecord, Record[answerKey[right] - 'A']);
        if (right - left + 1 - maxRecord > k) {
            Record[answerKey[left] - 'A']--;
            left++;
        }

        right++;
    }
    retVal = right - left;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxConsecutiveAnswers(string answerKey, int k) {
        int retVal = 0;

        // answerKey[i] is either 'T' or 'F'
#define MAX_RECORD (26)
        vector<int> Record(MAX_RECORD, 0);

        int maxRecord = 0;
        int answerKeySize = answerKey.length();
        int left = 0;
        int right = 0;
        while (right < answerKeySize) {
            Record[answerKey[right] - 'A']++;

            maxRecord = max(maxRecord, Record[answerKey[right] - 'A']);
            if (right - left + 1 - maxRecord > k) {
                Record[answerKey[left] - 'A']--;
                left++;
            }

            right++;
        }
        retVal = right - left;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxConsecutiveAnswers(self, answerKey: str, k: int) -> int:
        retVal = 0

        # answerKey[i] is either 'T' or 'F'
        MAX_RECORD = 26
        Record = [0] * MAX_RECORD

        maxRecord = 0
        answerKeysSize = len(answerKey)
        left = 0
        right = 0
        while right < answerKeysSize:
            idx = ord(answerKey[right]) - ord("A")
            Record[idx] += 1

            maxRecord = max(maxRecord, Record[idx])
            if right - left + 1 - maxRecord > k:
                Record[ord(answerKey[left]) - ord("A")] -= 1
                left += 1

            right += 1

        retVal = right - left

        return retVal
```

</details>

## [2134. Minimum Swaps to Group All 1's Together II](https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together-ii/)  1748

- [Official](https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together-ii/editorial/)
- [Official](https://leetcode.cn/problems/minimum-swaps-to-group-all-1s-together-ii/solutions/1202043/zui-shao-jiao-huan-ci-shu-lai-zu-he-suo-iaghf/)

<details><summary>Description</summary>

```text
A swap is defined as taking two distinct positions in an array and swapping the values in them.

A circular array is defined as an array where we consider the first element and the last element to be adjacent.

Given a binary circular array nums,
return the minimum number of swaps required to group all 1's present in the array together at any location.

Example 1:
Input: nums = [0,1,0,1,1,0,0]
Output: 1
Explanation: Here are a few of the ways to group all the 1's together:
[0,0,1,1,1,0,0] using 1 swap.
[0,1,1,1,0,0,0] using 1 swap.
[1,1,0,0,0,0,1] using 2 swaps (using the circular property of the array).
There is no way to group all 1's together with 0 swaps.
Thus, the minimum number of swaps required is 1.

Example 2:
Input: nums = [0,1,1,1,0,0,1,1,0]
Output: 2
Explanation: Here are a few of the ways to group all the 1's together:
[1,1,1,0,0,0,0,1,1] using 2 swaps (using the circular property of the array).
[1,1,1,1,1,0,0,0,0] using 2 swaps.
There is no way to group all 1's together with 0 or 1 swaps.
Thus, the minimum number of swaps required is 2.

Example 3:
Input: nums = [1,1,0,0,1]
Output: 0
Explanation: All the 1's are already grouped together due to the circular property of the array.
Thus, the minimum number of swaps required is 0.

Constraints:
1 <= nums.length <= 10^5
nums[i] is either 0 or 1.
```

<details><summary>Hint</summary>

```text
1. Notice that the number of 1’s to be grouped together is fixed. It is the number of 1's the whole array has.
2. Call this number total. We should then check for every subarray of size total (possibly wrapped around),
   how many swaps are required to have the subarray be all 1’s.
3. The number of swaps required is the number of 0’s in the subarray.
4. To eliminate the circular property of the array, we can append the original array to itself.
   Then, we check each subarray of length total.
5. How do we avoid recounting the number of 0’s in the subarray each time? The Sliding Window technique can help.
```

</details>

</details>

<details><summary>C</summary>

```c
// Helper function to calculate the minimum swaps required to group all value together
int minSwapsHelper(int* nums, int numsSize, int value) {
    int retVal = 0;

    // Count the total number of value in the array
    int totalValCount = 0;
    int i;
    for (i = numsSize - 1; i >= 0; i--) {
        if (nums[i] == value) {
            totalValCount++;
        }
    }
    // If there is no value or the array is full of value, no swaps are needed
    if ((totalValCount == 0) || (totalValCount == numsSize)) {
        return retVal;
    }

    int start = 0;
    int end = 0;
    int maxValInWindow = 0;
    int currentValInWindow = 0;

    // Initial window setup: count the number of value in the first window of size `totalValCount`
    while (end < totalValCount) {
        if (nums[end++] == value) {
            currentValInWindow++;
        }
    }
    maxValInWindow = fmax(maxValInWindow, currentValInWindow);

    // Slide the window across the array to find the maximum number of value in any window
    while (end < numsSize) {
        if (nums[start++] == value) {
            currentValInWindow--;
        }

        if (nums[end++] == value) {
            currentValInWindow++;
        }

        maxValInWindow = fmax(maxValInWindow, currentValInWindow);
    }

    // Minimum swaps are the total value minus the maximum found in any window
    retVal = totalValCount - maxValInWindow;

    return retVal;
}
int minSwaps(int* nums, int numsSize) {
    int retVal = 0;

    // Calculate the minimum swaps needed to group all 1s or all 0s together
    int op0 = minSwapsHelper(nums, numsSize, 0);  // Grouping all 0s together
    int op1 = minSwapsHelper(nums, numsSize, 1);  // Grouping all 1s together
    retVal = fmin(op0, op1);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    // Helper function to calculate the minimum swaps required to group all value together
    int minSwapsHelper(vector<int>& nums, int value) {
        int retVal = 0;

        int numsSize = nums.size();

        // Count the total number of value in the array
        int totalValCount = 0;
        for (int i = numsSize - 1; i >= 0; i--) {
            if (nums[i] == value) {
                totalValCount++;
            }
        }
        // If there is no value or the array is full of value, no swaps are needed
        if ((totalValCount == 0) || (totalValCount == numsSize)) {
            return retVal;
        }

        int start = 0;
        int end = 0;
        int maxValInWindow = 0;
        int currentValInWindow = 0;

        // Initial window setup: count the number of value in the first window of size `totalValCount`
        while (end < totalValCount) {
            if (nums[end++] == value) {
                currentValInWindow++;
            }
        }
        maxValInWindow = max(maxValInWindow, currentValInWindow);

        // Slide the window across the array to find the maximum number of value in any window
        while (end < numsSize) {
            if (nums[start++] == value) {
                currentValInWindow--;
            }

            if (nums[end++] == value) {
                currentValInWindow++;
            }

            maxValInWindow = max(maxValInWindow, currentValInWindow);
        }

        // Minimum swaps are the total value minus the maximum found in any window
        retVal = totalValCount - maxValInWindow;

        return retVal;
    }

   public:
    int minSwaps(vector<int>& nums) {
        int retVal = 0;

        // Calculate the minimum swaps needed to group all 1s or all 0s together
        int op0 = minSwapsHelper(nums, 0);  // Grouping all 0s together
        int op1 = minSwapsHelper(nums, 1);  // Grouping all 1s together
        retVal = min(op0, op1);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    # Helper function to calculate the minimum swaps required to group all value together
    def minSwapsHelper(self, nums: List[int], value: int) -> int:
        retVal = 0

        numsSize = len(nums)

        # Count the total number of value in the array
        totalValCount = 0
        for i in range(numsSize - 1, -1, -1):
            if nums[i] == value:
                totalValCount += 1
        # If there is no value or the array is full of value, no swaps are needed
        if (totalValCount == 0) or (totalValCount == numsSize):
            return retVal

        start = 0
        end = 0
        currentValInWindow = 0
        maxValInWindow = 0

        # Initial window setup: count the number of value in the first window of size `totalValCount`
        while end < totalValCount:
            if nums[end] == value:
                currentValInWindow += 1
            end += 1
        maxValInWindow = max(maxValInWindow, currentValInWindow)

        # Slide the window across the array to find the maximum number of value in any window
        while end < numsSize:
            if nums[start] == value:
                currentValInWindow -= 1
            start += 1

            if nums[end] == value:
                currentValInWindow += 1
            end += 1

            maxValInWindow = max(maxValInWindow, currentValInWindow)

        # Minimum swaps are the total value minus the maximum found in any window
        retVal = totalValCount - maxValInWindow

        return retVal

    def minSwaps(self, nums: List[int]) -> int:
        retVal = 0

        # Calculate the minimum swaps needed to group all 1s or all 0s together
        op0 = self.minSwapsHelper(nums, 0)  # Grouping all 0s together
        op1 = self.minSwapsHelper(nums, 1)  # Grouping all 1s together
        retVal = min(op0, op1)

        return retVal
```

</details>

## [2401. Longest Nice Subarray](https://leetcode.com/problems/longest-nice-subarray/)  1749

<details><summary>Description</summary>

```text
You are given an array nums consisting of positive integers.

We call a subarray of nums nice if the bitwise AND of every pair of elements
that are in different positions in the subarray is equal to 0.

Return the length of the longest nice subarray.

A subarray is a contiguous part of an array.

Note that subarrays of length 1 are always considered nice.

Example 1:
Input: nums = [1,3,8,48,10]
Output: 3
Explanation: The longest nice subarray is [3,8,48]. This subarray satisfies the conditions:
- 3 AND 8 = 0.
- 3 AND 48 = 0.
- 8 AND 48 = 0.
It can be proven that no longer nice subarray can be obtained, so we return 3.

Example 2:
Input: nums = [3,1,5,11,13]
Output: 1
Explanation: The length of the longest nice subarray is 1. Any subarray of length 1 can be chosen.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. What is the maximum possible length of a nice subarray?
2. The length of the longest nice subarray cannot exceed 30. Why is that?
```

</details>

</details>

<details><summary>C</summary>

```c
int longestNiceSubarray(int* nums, int numsSize) {
    int retVal = 0;

    int niceCheck = 0;
    int head = 0;
    int tail = 0;
    while (tail < numsSize) {
        while ((niceCheck & nums[tail]) != 0) {
            niceCheck ^= nums[head];
            ++head;
        }
        retVal = fmax(retVal, tail - head + 1);

        niceCheck |= nums[tail];
        ++tail;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int longestNiceSubarray(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        int niceCheck = 0;
        int head = 0;
        int tail = 0;
        while (tail < numsSize) {
            while ((niceCheck & nums[tail]) != 0) {
                niceCheck ^= nums[head];
                head++;
            }
            retVal = max(retVal, tail - head + 1);

            niceCheck |= nums[tail];
            tail++;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def longestNiceSubarray(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        niceCheck = 0
        head = 0
        tail = 0
        while (tail < numsSize):
            while ((niceCheck & nums[tail]) != 0):
                niceCheck ^= nums[head]
                head += 1
            retVal = max(retVal, tail - head + 1)

            niceCheck |= nums[tail]
            tail += 1

        return retVal
```

</details>

## [2444. Count Subarrays With Fixed Bounds](https://leetcode.com/problems/count-subarrays-with-fixed-bounds/)  2092

<details><summary>Description</summary>

```text
You are given an integer array nums and two integers minK and maxK.

A fixed-bound subarray of nums is a subarray that satisfies the following conditions:
- The minimum value in the subarray is equal to minK.
- The maximum value in the subarray is equal to maxK.
Return the number of fixed-bound subarrays.

A subarray is a contiguous part of an array.

Example 1:
Input: nums = [1,3,5,2,7,5], minK = 1, maxK = 5
Output: 2
Explanation: The fixed-bound subarrays are [1,3,5] and [1,3,5,2].

Example 2:
Input: nums = [1,1,1,1], minK = 1, maxK = 1
Output: 10
Explanation: Every subarray of nums is a fixed-bound subarray. There are 10 possible subarrays.

Constraints:
2 <= nums.length <= 10^5
1 <= nums[i], minK, maxK <= 10^6
```

<details><summary>Hint</summary>

```text
1. Can you solve the problem if all the numbers in the array were between minK and maxK inclusive?
2. Think of the inclusion-exclusion principle.
3. Divide the array into multiple subarrays such that each number in each subarray is between minK and maxK inclusive,
   solve the previous problem for each subarray, and sum all the answers.
```

</details>

</details>

<details><summary>C</summary>

```c
long long countSubarrays(int *nums, int numsSize, int minK, int maxK) {
    long long retVal = 0;

    /* Ref
     *  https://leetcode.com/problems/count-subarrays-with-fixed-bounds/solutions/2708099/java-c-python-sliding-window-with-explanation/
     *  https://leetcode.cn/problems/count-subarrays-with-fixed-bounds/solutions/1895734/fen-xi-ding-jie-zi-shu-zu-de-xing-zhi-yi-qusi/
     *  https://leetcode.cn/problems/count-subarrays-with-fixed-bounds/solutions/1895713/jian-ji-xie-fa-pythonjavacgo-by-endlessc-gag2/
     */
    long long badIdx = -1;
    long long minIdx = -1;
    long long maxIdx = -1;
    for (int i = 0; i < numsSize; ++i) {
        if ((nums[i] < minK) || (nums[i] > maxK)) {
            badIdx = i;
        }

        if (nums[i] == minK) {
            minIdx = i;
        }

        if (nums[i] == maxK) {
            maxIdx = i;
        }

        retVal += fmax(0, fmin(minIdx, maxIdx) - badIdx);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        long long retVal = 0;

        /* Ref
         *  https://leetcode.com/problems/count-subarrays-with-fixed-bounds/solutions/2708099/java-c-python-sliding-window-with-explanation/
         *  https://leetcode.cn/problems/count-subarrays-with-fixed-bounds/solutions/1895734/fen-xi-ding-jie-zi-shu-zu-de-xing-zhi-yi-qusi/
         *  https://leetcode.cn/problems/count-subarrays-with-fixed-bounds/solutions/1895713/jian-ji-xie-fa-pythonjavacgo-by-endlessc-gag2/
         */
        int len = nums.size();
        long long badIdx = -1;
        long long minIdx = -1;
        long long maxIdx = -1;
        for (int i = 0; i < len; ++i) {
            if ((nums[i] < minK) || (nums[i] > maxK)) {
                badIdx = i;
            }

            if (nums[i] == minK) {
                minIdx = i;
            }

            if (nums[i] == maxK) {
                maxIdx = i;
            }

            /* avoid different type between a and b in max function
             *  Because std::max is a function template whose signature is, for example,
             *  template< class T >
             *  const T& max( const T& a, const T& b );
             */
            long long n1 = 0;
            long long n2 = min(minIdx, maxIdx) - badIdx;
            retVal += max(n1, n2);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def countSubarrays(self, nums: List[int], minK: int, maxK: int) -> int:
        retVal = 0

        # /* Ref
        #  *  https://leetcode.com/problems/count-subarrays-with-fixed-bounds/solutions/2708099/java-c-python-sliding-window-with-explanation/
        #  *  https://leetcode.cn/problems/count-subarrays-with-fixed-bounds/solutions/1895734/fen-xi-ding-jie-zi-shu-zu-de-xing-zhi-yi-qusi/
        #  *  https://leetcode.cn/problems/count-subarrays-with-fixed-bounds/solutions/1895713/jian-ji-xie-fa-pythonjavacgo-by-endlessc-gag2/
        #  */
        numsSize = len(nums)
        badIdx = -1
        minIdx = -1
        maxIdx = -1
        for i in range(numsSize):
            if (nums[i] < minK) or (nums[i] > maxK):
                badIdx = i

            if (nums[i] == minK):
                minIdx = i

            if (nums[i] == maxK):
                maxIdx = i

            # /* avoid different type between a and b in max function
            #  *  Because std::max is a function template whose signature is, for example,
            #  *  template< class T >
            #  *  const T& max( const T& a, const T& b );
            #  */

            n1 = 0
            n2 = min(minIdx, maxIdx) - badIdx
            retVal += max(n1, n2)

        return retVal
```

</details>

## [2461. Maximum Sum of Distinct Subarrays With Length K](https://leetcode.com/problems/maximum-sum-of-distinct-subarrays-with-length-k/)  1552

- [Official](https://leetcode.com/problems/maximum-sum-of-distinct-subarrays-with-length-k/editorial/)

<details><summary>Description</summary>

```text
You are given an integer array nums and an integer k.
Find the maximum subarray sum of all the subarrays of nums that meet the following conditions:
- The length of the subarray is k, and
- All the elements of the subarray are distinct.

Return the maximum subarray sum of all the subarrays that meet the conditions.
If no subarray meets the conditions, return 0.

A subarray is a contiguous non-empty sequence of elements within an array.

Example 1:
Input: nums = [1,5,4,2,9,9,9], k = 3
Output: 15
Explanation: The subarrays of nums with length 3 are:
- [1,5,4] which meets the requirements and has a sum of 10.
- [5,4,2] which meets the requirements and has a sum of 11.
- [4,2,9] which meets the requirements and has a sum of 15.
- [2,9,9] which does not meet the requirements because the element 9 is repeated.
- [9,9,9] which does not meet the requirements because the element 9 is repeated.
We return 15 because it is the maximum subarray sum of all the subarrays that meet the conditions

Example 2:
Input: nums = [4,4,4], k = 3
Output: 0
Explanation: The subarrays of nums with length 3 are:
- [4,4,4] which does not meet the requirements because the element 4 is repeated.
We return 0 because no subarrays meet the conditions.

Constraints:
1 <= k <= nums.length <= 10^5
1 <= nums[i] <= 10^5
```

<details><summary>Hint</summary>

```text
1. Which elements change when moving from the subarray of size k
   that ends at index i to the subarray of size k that ends at index i + 1?
2. Only two elements change, the element at i + 1 is added into the subarray,
   and the element at i - k + 1 gets removed from the subarray.
3. Iterate through each subarray of size k and keep track of the sum of the subarray
   and the frequency of each element.
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
long long maximumSubarraySum(int *nums, int numsSize, int k) {
    long long retVal = 0;

    struct hashTable *numToIndex = NULL;
    struct hashTable *pTemp;

    int currNum, lastOccurrence;
    long long currentSum = 0;
    int begin = 0;
    int end = 0;
    while (end < numsSize) {
        currNum = nums[end];

        pTemp = NULL;
        HASH_FIND_INT(numToIndex, &currNum, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(numToIndex);
                return retVal;
            }
            pTemp->key = currNum;
            pTemp->value = -1;
            HASH_ADD_INT(numToIndex, key, pTemp);
        }
        lastOccurrence = pTemp->value;

        // if current window already has number or if window is too big, adjust window
        while ((begin <= lastOccurrence) || (end - begin + 1 > k)) {
            currentSum -= nums[begin];
            begin++;
        }

        pTemp = NULL;
        pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
        if (pTemp == NULL) {
            perror("malloc");
            freeAll(numToIndex);
            return retVal;
        }
        pTemp->key = currNum;
        pTemp->value = end;
        HASH_ADD_INT(numToIndex, key, pTemp);

        currentSum += nums[end];
        if (end - begin + 1 == k) {
            retVal = fmax(retVal, currentSum);
        }

        end++;
    }

    //
    freeAll(numToIndex);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        long long retVal = 0;

        int numsSize = nums.size();

        unordered_map<int, int> numToIndex;
        long long currentSum = 0;
        int begin = 0;
        int end = 0;
        while (end < numsSize) {
            int currNum = nums[end];
            int lastOccurrence = (numToIndex.count(currNum) ? numToIndex[currNum] : -1);

            // if current window already has number or if window is too big, adjust window
            while ((begin <= lastOccurrence) || (end - begin + 1 > k)) {
                currentSum -= nums[begin];
                begin++;
            }

            numToIndex[currNum] = end;
            currentSum += nums[end];
            if (end - begin + 1 == k) {
                retVal = max(retVal, currentSum);
            }

            end++;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maximumSubarraySum(self, nums: List[int], k: int) -> int:
        retVal = 0

        numsSize = len(nums)

        numToIndex = {}
        currentSum = 0
        begin = 0
        end = 0
        while end < numsSize:
            currNum = nums[end]
            lastOccurrence = numToIndex.get(currNum, -1)

            # if current window already has number or if window is too big, adjust window
            while (begin <= lastOccurrence) or (end - begin + 1 > k):
                currentSum -= nums[begin]
                begin += 1

            numToIndex[currNum] = end
            currentSum += nums[end]
            if end - begin + 1 == k:
                retVal = max(retVal, currentSum)

            end += 1

        return retVal
```

</details>

## [2958. Length of Longest Subarray With at Most K Frequency](https://leetcode.com/problems/length-of-longest-subarray-with-at-most-k-frequency/)  1535

- [Official](https://leetcode.com/problems/length-of-longest-subarray-with-at-most-k-frequency/editorial/)

<details><summary>Description</summary>

```text
You are given an integer array nums and an integer k.

The frequency of an element x is the number of times it occurs in an array.

An array is called good if the frequency of each element in this array is less than or equal to k.

Return the length of the longest good subarray of nums.

A subarray is a contiguous non-empty sequence of elements within an array.

Example 1:
Input: nums = [1,2,3,1,2,3,1,2], k = 2
Output: 6
Explanation: The longest possible good subarray is [1,2,3,1,2,3]
since the values 1, 2, and 3 occur at most twice in this subarray.
Note that the subarrays [2,3,1,2,3,1] and [3,1,2,3,1,2] are also good.
It can be shown that there are no good subarrays with length more than 6.

Example 2:
Input: nums = [1,2,1,2,1,2,1,2], k = 1
Output: 2
Explanation: The longest possible good subarray is [1,2] since the values 1 and 2 occur at most once in this subarray.
Note that the subarray [2,1] is also good.
It can be shown that there are no good subarrays with length more than 2.

Example 3:
Input: nums = [5,5,5,5,5,5,5], k = 4
Output: 4
Explanation: The longest possible good subarray is [5,5,5,5] since the value 5 occurs 4 times in this subarray.
It can be shown that there are no good subarrays with length more than 4.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
1 <= k <= nums.length
```

<details><summary>Hint</summary>

```text
1. For each index i,
   find the rightmost index j >= i such that the frequency of each element in the subarray [i, j] is at most k.
2. We can use 2 pointers / sliding window to achieve it.
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
int maxSubarrayLength(int *nums, int numsSize, int k) {
    int retVal = 0;

    struct hashTable *pFrequency = NULL;
    struct hashTable *pTempStart, *pTempEnd;
    int startKey, endKey;
    int start = -1, end = 0;
    for (end = 0; end < numsSize; ++end) {
        endKey = nums[end];
        pTempEnd = NULL;
        HASH_FIND_INT(pFrequency, &endKey, pTempEnd);
        if (pTempEnd == NULL) {
            pTempEnd = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTempEnd == NULL) {
                perror("malloc");
                goto exit;
            }
            pTempEnd->key = endKey;
            pTempEnd->value = 1;
            HASH_ADD_INT(pFrequency, key, pTempEnd);
        } else {
            pTempEnd->value += 1;
        }

        while (pTempEnd->value > k) {
            start++;

            startKey = nums[start];
            pTempStart = NULL;
            HASH_FIND_INT(pFrequency, &startKey, pTempStart);
            pTempStart->value -= 1;
        }

        retVal = fmax(retVal, (end - start));
    }

exit:
    freeAll(pFrequency);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        int retVal = 0;

        int numsSize = nums.size();
        unordered_map<int, int> frequency;
        int start = -1;
        for (int end = 0; end < numsSize; ++end) {
            frequency[nums[end]]++;
            while (frequency[nums[end]] > k) {
                start++;
                frequency[nums[start]]--;
            }
            retVal = max(retVal, (end - start));
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxSubarrayLength(self, nums: List[int], k: int) -> int:
        retVal = 0

        frequency = defaultdict(int)
        start = -1
        for end, value in enumerate(nums):
            frequency[value] += 1
            while frequency[value] > k:
                start += 1
                frequency[nums[start]] -= 1
            retVal = max(retVal, end - start)

        return retVal
```

</details>

## [2962. Count Subarrays Where Max Element Appears at Least K Times](https://leetcode.com/problems/count-subarrays-where-max-element-appears-at-least-k-times/)  1700

- [Official](https://leetcode.com/problems/count-subarrays-where-max-element-appears-at-least-k-times/editorial/)

<details><summary>Description</summary>

```text
You are given an integer array nums and a positive integer k.

Return the number of subarrays where the maximum element of nums appears at least k times in that subarray.

A subarray is a contiguous sequence of elements within an array.

Example 1:
Input: nums = [1,3,2,3,3], k = 2
Output: 6
Explanation: The subarrays that contain the element 3 at least 2 times are:
[1,3,2,3], [1,3,2,3,3], [3,2,3], [3,2,3,3], [2,3,3] and [3,3].

Example 2:
Input: nums = [1,4,2,1], k = 3
Output: 0
Explanation: No subarray contains the element 4 at least 3 times.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^6
1 <= k <= 10^5
```

</details>

<details><summary>C</summary>

```c
long long countSubarrays(int *nums, int numsSize, int k) {
    long long retVal = 0;

    int maxNum = nums[0];  // 1 <= nums.length <= 10^5
    int i;
    for (i = 1; i < numsSize; ++i) {
        if (maxNum < nums[i]) {
            maxNum = nums[i];
        }
    }
    int maxNumWindow = 0;

    int start = 0;
    int end = 0;
    for (end = 0; end < numsSize; ++end) {
        if (nums[end] == maxNum) {
            maxNumWindow++;
        }

        while (maxNumWindow == k) {
            if (nums[start] == maxNum) {
                maxNumWindow--;
            }
            start++;
        }

        retVal += start;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long countSubarrays(vector<int>& nums, int k) {
        long long retVal = 0;

        int numsSize = nums.size();
        int maxNum = *max_element(nums.begin(), nums.end());
        int maxNumWindow = 0;
        int start = 0;
        int end = 0;
        for (end = 0; end < numsSize; ++end) {
            if (nums[end] == maxNum) {
                maxNumWindow++;
            }

            while (maxNumWindow == k) {
                if (nums[start] == maxNum) {
                    maxNumWindow--;
                }
                start++;
            }

            retVal += start;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def countSubarrays(self, nums: List[int], k: int) -> int:
        retVal = 0

        numsSize = len(nums)
        maxNum = max(nums)
        maxNumWindow = 0
        start = 0
        for end in range(numsSize):
            if nums[end] == maxNum:
                maxNumWindow += 1

            while maxNumWindow == k:
                if nums[start] == maxNum:
                    maxNumWindow -= 1
                start += 1

            retVal += start

        return retVal
```

</details>

## [3254. Find the Power of K-Size Subarrays I](https://leetcode.com/problems/find-the-power-of-k-size-subarrays-i/)  1266

- [Official](https://leetcode.com/problems/find-the-power-of-k-size-subarrays-i/editorial/)
- [Official](https://leetcode.cn/problems/find-the-power-of-k-size-subarrays-i/solutions/2973321/chang-du-wei-k-de-zi-shu-zu-de-neng-lian-vxim/)

<details><summary>Description</summary>

```text
You are given an array of integers nums of length n and a positive integer k.

The power of an array is defined as:
- Its maximum element if all of its elements are consecutive and sorted in ascending order.
- -1 otherwise.

You need to find the power of all subarrays of nums of size k.

Return an integer array results of size n - k + 1, where results[i] is the power of nums[i..(i + k - 1)].

Example 1:
Input: nums = [1,2,3,4,3,2,5], k = 3
Output: [3,4,-1,-1,-1]
Explanation:
There are 5 subarrays of nums of size 3:
[1, 2, 3] with the maximum element 3.
[2, 3, 4] with the maximum element 4.
[3, 4, 3] whose elements are not consecutive.
[4, 3, 2] whose elements are not sorted.
[3, 2, 5] whose elements are not consecutive.

Example 2:
Input: nums = [2,2,2,2,2], k = 4
Output: [-1,-1]

Example 3:
Input: nums = [3,2,3,2,3,2], k = 2
Output: [-1,3,-1,3,-1]

Constraints:
1 <= n == nums.length <= 500
1 <= nums[i] <= 10^5
1 <= k <= n
```

<details><summary>Hint</summary>

```text
1. Can we use a brute force solution with nested loops and HashSet?
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *resultsArray(int *nums, int numsSize, int k, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = numsSize - k + 1;
    pRetVal = (int *)malloc(((*returnSize) * sizeof(int)));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, -1, ((*returnSize) * sizeof(int)));

    int consecutiveCount = 0;
    for (int i = 0; i < numsSize; ++i) {
        if ((i != 0) && (nums[i - 1] + 1 == nums[i])) {
            consecutiveCount++;
        } else {
            consecutiveCount = 1;
        }

        if (consecutiveCount >= k) {
            pRetVal[i - k + 1] = nums[i];
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
    vector<int> resultsArray(vector<int>& nums, int k) {
        vector<int> retVal;

        if (k == 1) {
            retVal = nums;
            return retVal;
        }

        int numsSize = nums.size();
        retVal.resize(numsSize - k + 1, -1);
        int consecutiveCount = 1;
        for (int i = 0; i < numsSize - 1; ++i) {
            if (nums[i] + 1 == nums[i + 1]) {
                consecutiveCount++;
            } else {
                consecutiveCount = 1;
            }

            if (consecutiveCount >= k) {
                retVal[i - k + 2] = nums[i + 1];
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
    def resultsArray(self, nums: List[int], k: int) -> List[int]:
        retVal = []

        if k == 1:
            retVal = nums
            return retVal

        numsSize = len(nums)
        retVal = [-1] * (numsSize - k + 1)
        consecutiveCount = 1
        for i in range(numsSize - 1):
            if nums[i] + 1 == nums[i + 1]:
                consecutiveCount += 1
            else:
                consecutiveCount = 1

            if consecutiveCount >= k:
                retVal[i - k + 2] = nums[i + 1]

        return retVal
```

</details>
