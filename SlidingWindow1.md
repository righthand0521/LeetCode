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
struct hashTable {
    int key;
    int value;
    UT_hash_handle hh;
};
bool addKey(struct hashTable **pObj, int key, int value) {
    bool retVal = true;

    struct hashTable *pTemp = NULL;
    HASH_FIND_INT(*pObj, &key, pTemp);
    if (pTemp != NULL) {
        pTemp->value += value;
        if (pTemp->value == 0) {
            HASH_DEL(*pObj, pTemp);
            free(pTemp);
        }

        return retVal;
    }

    pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
    if (pTemp == NULL) {
        perror("malloc");
        retVal = false;
    } else {
        pTemp->key = key;
        pTemp->value = value;
        HASH_ADD_INT(*pObj, key, pTemp);
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
int totalFruit(int *fruits, int fruitsSize) {
    int retVal = 0;

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
    struct hashTable *frequency = NULL;
    int frequencySize;
    int key;
    bool isValid = true;
    int head = 0;
    int tail = 0;
    while (tail < fruitsSize) {
        key = fruits[tail];
        isValid = addKey(&frequency, key, 1);
        if (isValid == false) {
            freeAll(frequency);
            return retVal;
        }
        frequencySize = HASH_COUNT(frequency);

        while (frequencySize > 2) {
            key = fruits[head];
            isValid = addKey(&frequency, key, -1);
            if (isValid == false) {
                freeAll(frequency);
                return retVal;
            }
            frequencySize = HASH_COUNT(frequency);

            head++;
        }
        retVal = fmax(retVal, tail - head + 1);

        ++tail;
    }

    //
    freeAll(frequency);

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

        int fruitsSize = fruits.size();
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
        unordered_map<int, int> frequency;
        int frequencySize;
        int head = 0;
        int tail = 0;
        while (tail < fruitsSize) {
            frequency[fruits[tail]]++;
            frequencySize = frequency.size();

            while (frequencySize > 2) {
                frequency[fruits[head]]--;
                if (frequency[fruits[head]] == 0) {
                    frequency.erase(fruits[head]);
                }
                frequencySize = frequency.size();
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

<details><summary>Python3</summary>

```python
class Solution:
    def totalFruit(self, fruits: List[int]) -> int:
        retVal = 0

        fruitsSize = len(fruits)

        # /* Example
        #  *          +--------------------------------------------+-----------------------------+
        #  *          | 3 | 3 | 3 | 1 | 2 | 1 | 1 | 2 | 3 | 3 | 4  |                             |
        #  *          +--------------------------------------------+-------------------------+---+
        #  *    tail  | 0 > 1 > 2 > 3 > 4                          | size: 1 > 1 > 1 > 2 > 3 |   |
        #  *    head  | 0                                          |  max: 1 > 2 > 3 > 4     | 4 |
        #  *          +--------------------------------------------+-------------------------+---|
        #  *    tail  |                 4                          | size: 3 > 3 > 3 > 2     |   |
        #  *    head  | 0 > 1 > 2 > 3                              |  max: 4 > 2             | 4 |
        #  *          +--------------------------------------------+-------------------------+---+
        #  *    tail  |                 4 > 5 > 6 > 7 > 8          | size: 2 > 2 > 2 > 2 > 3 |   |
        #  *    head  |             3                              |  max: 2 > 3 > 4 > 5     | 5 |
        #  *          +--------------------------------------------+-------------------------+---+
        #  *    tail  |                                 8          | size: 3 > 3 > 3 > 3 > 2 |   |
        #  *    head  |             3 > 4 > 5 > 6 > 7              |  max: 5 > 2             | 5 |
        #  *          +--------------------------------------------+-------------------------+---+
        #  *    tail  |                                 8 > 9 > 10 | size: 2 > 2 > 3         |   |
        #  *    head  |                             7              |  max: 2 > 3             | 5 |
        #  *          +--------------------------------------------+-------------------------+---+
        #  *    tail  |                                         10 | size: 3 > 2             |   |
        #  *    head  |                             7 > 8          |  max: 3 > 3             | 5 |
        #  *          +--------------------------------------------+-------------------------+---+
        #  */
        frequency = Counter()
        head = 0
        tail = 0
        while (tail < fruitsSize):
            frequency[fruits[tail]] += 1
            frequencySize = len(frequency)
            while frequencySize > 2:
                frequency[fruits[head]] -= 1
                if frequency[fruits[head]] == 0:
                    del frequency[fruits[head]]
                frequencySize = len(frequency)
                head += 1

            retVal = max(retVal, tail - head + 1)

            tail += 1

        return retVal
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
