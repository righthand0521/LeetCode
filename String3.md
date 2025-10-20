# String

## [2011. Final Value of Variable After Performing Operations](https://leetcode.com/problems/final-value-of-variable-after-performing-operations/)  1165

- [Official](https://leetcode.com/problems/final-value-of-variable-after-performing-operations/editorial/)
- [Official](https://leetcode.cn/problems/final-value-of-variable-after-performing-operations/solutions/2028909/zhi-xing-cao-zuo-hou-de-bian-liang-zhi-b-knvg/)

<details><summary>Description</summary>

```text
There is a programming language with only four operations and one variable X:
- ++X and X++ increments the value of the variable X by 1.
- --X and X-- decrements the value of the variable X by 1.

Initially, the value of X is 0.

Given an array of strings operations containing a list of operations,
return the final value of X after performing all the operations.

Example 1:
Input: operations = ["--X","X++","X++"]
Output: 1
Explanation: The operations are performed as follows:
Initially, X = 0.
--X: X is decremented by 1, X =  0 - 1 = -1.
X++: X is incremented by 1, X = -1 + 1 =  0.
X++: X is incremented by 1, X =  0 + 1 =  1.

Example 2:
Input: operations = ["++X","++X","X++"]
Output: 3
Explanation: The operations are performed as follows:
Initially, X = 0.
++X: X is incremented by 1, X = 0 + 1 = 1.
++X: X is incremented by 1, X = 1 + 1 = 2.
X++: X is incremented by 1, X = 2 + 1 = 3.

Example 3:
Input: operations = ["X++","++X","--X","X--"]
Output: 0
Explanation: The operations are performed as follows:
Initially, X = 0.
X++: X is incremented by 1, X = 0 + 1 = 1.
++X: X is incremented by 1, X = 1 + 1 = 2.
--X: X is decremented by 1, X = 2 - 1 = 1.
X--: X is decremented by 1, X = 1 - 1 = 0.

Constraints:
1 <= operations.length <= 100
operations[i] will be either "++X", "X++", "--X", or "X--"
```

<details><summary>Hint</summary>

```text
1. There are only two operations to keep track of.
2. Use a variable to store the value after each operation.
```

</details>

</details>

<details><summary>C</summary>

```c
int finalValueAfterOperations(char** operations, int operationsSize) {
    int retVal = 0;

    for (int i = 0; i < operationsSize; i++) {
        // operations[i] will be either "++X", "X++", "--X", or "X--"
        if ((strcmp(operations[i], "++X") == 0) || (strcmp(operations[i], "X++") == 0)) {
            retVal++;
        } else {
            retVal--;
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
    int finalValueAfterOperations(vector<string>& operations) {
        int retVal = 0;

        for (const string& operation : operations) {
            // operations[i] will be either "++X", "X++", "--X", or "X--"
            if ((operation == "++X") || (operation == "X++")) {
                retVal++;
            } else {
                retVal--;
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
    def finalValueAfterOperations(self, operations: List[str]) -> int:
        retVal = 0

        for operation in operations:
            # operations[i] will be either "++X", "X++", "--X", or "X--"
            if operation == "++X" or operation == "X++":
                retVal += 1
            else:
                retVal -= 1

        return retVal
```

</details>

## [2014. Longest Subsequence Repeated k Times](https://leetcode.com/problems/longest-subsequence-repeated-k-times/)  2558

- [Official](https://leetcode.com/problems/longest-subsequence-repeated-k-times/editorial/)

<details><summary>Description</summary>

```text
You are given a string s of length n, and an integer k.
You are tasked to find the longest subsequence repeated k times in string s.

A subsequence is a string that can be derived from another string
by deleting some or no characters without changing the order of the remaining characters.

A subsequence seq is repeated k times in the string s if seq * k is a subsequence of s,
where seq * k represents a string constructed by concatenating seq k times.
- For example, "bba" is repeated 2 times in the string "bababcba",
  because the string "bbabba", constructed by concatenating "bba" 2 times, is a subsequence of the string "bababcba".

Return the longest subsequence repeated k times in string s.
If multiple such subsequences are found, return the lexicographically largest one.
If there is no such subsequence, return an empty string.

Example 1:
example 1
Input: s = "letsleetcode", k = 2
Output: "let"
Explanation: There are two longest subsequences repeated 2 times: "let" and "ete".
"let" is the lexicographically largest one.

Example 2:
Input: s = "bb", k = 2
Output: "b"
Explanation: The longest subsequence repeated 2 times is "b".

Example 3:
Input: s = "ab", k = 2
Output: ""
Explanation: There is no subsequence repeated 2 times. Empty string is returned.

Constraints:
n == s.length
2 <= n, k <= 2000
2 <= n < k * 8
s consists of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. The length of the longest subsequence does not exceed n/k. Do you know why?
2. Find the characters that could be included in the potential answer.
   A character occurring more than or equal to k times can be used in the answer up to (count of the character / k) times.
3. Try all possible candidates in reverse lexicographic order, and check the string for the subsequence condition.
```

</details>

</details>

<details><summary>C</summary>

```c
#ifndef QUEUE_H
#define QUEUE_H

typedef struct {
    char* str;
    int len;
} QueueNode;
typedef struct {
    QueueNode* data;
    int front, rear, size, capacity;
} Queue;
Queue* createQueue(int capacity) {
    Queue* obj = NULL;

    obj = (Queue*)malloc(sizeof(Queue));
    obj->data = (QueueNode*)malloc(capacity * sizeof(QueueNode));
    obj->front = obj->size = 0;
    obj->rear = capacity - 1;
    obj->capacity = capacity;

    return obj;
}
void enqueue(Queue* q, char* str, int len) {
    if (q->size == q->capacity) {
        //
        return;
    }
    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear].str = strdup(str);
    q->data[q->rear].len = len;
    q->size++;
}
QueueNode dequeue(Queue* q) {
    QueueNode obj;

    if (q->size == 0) {
        obj.str = NULL;
        obj.len = 0;
        return obj;
    }

    obj = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;

    return obj;
}

#endif  // QUEUE_H
bool isKRepeatedSubsequence(const char* s, const char* t, int k) {
    bool retVal = false;

    int tSize = strlen(t);
    int pos = 0;
    int matched = 0;
    for (int i = 0; s[i]; i++) {
        if (s[i] != t[pos]) {
            continue;
        }

        pos++;
        if (pos != tSize) {
            continue;
        }

        pos = 0;
        matched++;
        if (matched == k) {
            retVal = true;
            break;
        }
    }

    return retVal;
}
char* longestSubsequenceRepeatedK(char* s, int k) {
    char* pRetVal = NULL;  // strdup("");

    int returnSize = strlen(s) + 1;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));

    int letterSize = 26;  // s consists of lowercase English letters.
    int frequency[letterSize];
    memset(frequency, 0, sizeof(frequency));
    for (int i = 0; s[i]; i++) {
        frequency[s[i] - 'a']++;
    }

    char candidate[letterSize];
    int candidateSize = 0;
    for (int i = (letterSize - 1); i >= 0; i--) {
        if (frequency[i] >= k) {
            candidate[candidateSize++] = 'a' + i;
        }
    }

    int candidateQueueSize = 10000;
    Queue* candidateQueue = createQueue(candidateQueueSize);
    for (int i = 0; i < candidateSize; i++) {
        char str[2] = {candidate[i], '\0'};
        enqueue(candidateQueue, str, 1);
    }

    while (candidateQueue->size > 0) {
        QueueNode curr = dequeue(candidateQueue);
        if (curr.len > strlen(pRetVal)) {
            memset(pRetVal, 0, (returnSize * sizeof(char)));
            snprintf(pRetVal, returnSize - 1, "%s", curr.str);
        }

        // generate the next candidate string
        for (int i = 0; i < candidateSize; i++) {
            char next[curr.len + 2];
            memset(next, 0, sizeof(next));
            strcpy(next, curr.str);
            next[curr.len] = candidate[i];
            next[curr.len + 1] = '\0';
            if (isKRepeatedSubsequence(s, next, k) == true) {
                enqueue(candidateQueue, next, curr.len + 1);
            }
        }

        free(curr.str);
    }

    //
    free(candidateQueue->data);
    free(candidateQueue);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    int letterSize = 26;  // s consists of lowercase English letters.

    bool isKRepeatedSubsequence(const string& s, const string& t, int k) {
        bool retVal = false;

        int tSize = t.size();
        int pos = 0;
        int matched = 0;
        for (char ch : s) {
            if (ch != t[pos]) {
                continue;
            }

            pos++;
            if (pos != tSize) {
                continue;
            }

            pos = 0;
            matched++;
            if (matched == k) {
                retVal = true;
                break;
            }
        }

        return retVal;
    }

   public:
    string longestSubsequenceRepeatedK(string s, int k) {
        string retVal = "";

        vector<int> frequency(letterSize);
        for (char ch : s) {
            frequency[ch - 'a']++;
        }

        vector<char> candidate;
        for (int i = (letterSize - 1); i >= 0; i--) {
            if (frequency[i] >= k) {
                candidate.push_back('a' + i);
            }
        }

        queue<string> candidateQueue;
        for (char ch : candidate) {
            candidateQueue.push(string(1, ch));
        }

        while (candidateQueue.empty() == false) {
            string curr = candidateQueue.front();
            candidateQueue.pop();
            if (curr.size() > retVal.size()) {
                retVal = curr;
            }

            // generate the next candidate string
            for (char ch : candidate) {
                string next = curr + ch;
                if (isKRepeatedSubsequence(s, next, k) == true) {
                    candidateQueue.push(next);
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
    def longestSubsequenceRepeatedK(self, s: str, k: int) -> str:
        retVal = ""

        candidate = sorted([c for c, w in Counter(s).items() if w >= k], reverse=True)

        candidateQueue = deque(candidate)
        while candidateQueue:
            curr = candidateQueue.popleft()
            if len(curr) > len(retVal):
                retVal = curr

            # generate the next candidate string
            for ch in candidate:
                nxt = curr + ch
                it = iter(s)
                if all(ch in it for ch in nxt * k):
                    candidateQueue.append(nxt)

        return retVal
```

</details>

## [2042. Check if Numbers Are Ascending in a Sentence](https://leetcode.com/problems/check-if-numbers-are-ascending-in-a-sentence/)  1257

- [Official](https://leetcode.cn/problems/check-if-numbers-are-ascending-in-a-sentence/solutions/2041564/jian-cha-ju-zi-zhong-de-shu-zi-shi-fou-d-uhaf/)

<details><summary>Description</summary>

```text
A sentence is a list of tokens separated by a single space with no leading or trailing spaces.
Every token is either a positive number consisting of digits 0-9 with no leading zeros,
or a word consisting of lowercase English letters.

For example, "a puppy has 2 eyes 4 legs" is a sentence with seven tokens:
"2" and "4" are numbers and the other tokens such as "puppy" are words.
Given a string s representing a sentence,
you need to check if all the numbers in s are strictly increasing from left to right
(i.e., other than the last number, each number is strictly smaller than the number on its right in s).

Return true if so, or false otherwise.

Example 1:
Input: s = "1 box has 3 blue 4 red 6 green and 12 yellow marbles"
Output: true
Explanation: The numbers in s are: 1, 3, 4, 6, 12.
They are strictly increasing from left to right: 1 < 3 < 4 < 6 < 12.

Example 2:
Input: s = "hello world 5 x 5"
Output: false
Explanation: The numbers in s are: 5, 5. They are not strictly increasing.

Example 3:
Input: s = "sunset is at 7 51 pm overnight lows will be in the low 50 and 60 s"
Output: false
Explanation: The numbers in s are: 7, 51, 50, 60. They are not strictly increasing.

Constraints:
3 <= s.length <= 200
s consists of lowercase English letters, spaces, and digits from 0 to 9, inclusive.
The number of tokens in s is between 2 and 100, inclusive.
The tokens in s are separated by a single space.
There are at least two numbers in s.
Each number in s is a positive number less than 100, with no leading zeros.
s contains no leading or trailing spaces.
```

<details><summary>Hint</summary>

```text
1. Use string tokenization of your language to extract all the tokens of the string easily.
2. For each token extracted, how can you tell if it is a number? Does the first letter being a digit mean something?
3. Compare the number with the previously occurring number to check if ascending order is maintained.
```

</details>

</details>

<details><summary>C</summary>

```c
bool areNumbersAscending(char* s) {
    bool retVal = false;

    int previous = -1;
    int current = -1;
    int idx = -2;
    int len = strlen(s);
    int i;
    for (i = 0; i < len; ++i) {
        if (isdigit(s[i]) == false) {
            if (current != -1) {
                if (current <= previous) {
                    return retVal;
                }
                previous = current;
                current = -1;
            }
            continue;
        }

        if (i - idx == 1) {
            current = 10 * current + (s[i] - '0');
        } else {
            current = s[i] - '0';
        }
        idx = i;
    }
    if (current != -1) {
        if (current <= previous) {
            return retVal;
        }
        previous = current;
        current = -1;
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
    bool areNumbersAscending(string s) {
        bool retVal = false;

        int checkNum = -1;
        int num = 0;
        bool continueNum = false;
        for (auto c : s) {
            if (isdigit(c)) {
                num = 10 * num + (c - '0');
                continueNum = true;
                continue;
            }

            if (continueNum == true) {
                if (num <= checkNum) {
                    return retVal;
                }
                checkNum = num;
            }

            num = 0;
            continueNum = false;
            continue;
        }
        if (num != 0) {
            if (num <= checkNum) {
                return retVal;
            }
            checkNum = num;
        }
        retVal = true;

        return retVal;
    }
};
```

</details>

## [2124. Check if All A's Appears Before All B's](https://leetcode.com/problems/check-if-all-as-appears-before-all-bs/)  1201

- [Official](https://leetcode.cn/problems/check-if-all-as-appears-before-all-bs/solutions/1202021/jian-cha-shi-fou-suo-you-a-du-zai-b-zhi-e7p0q/)

<details><summary>Description</summary>

```text
Given a string s consisting of only the characters 'a' and 'b',
return true if every 'a' appears before every 'b' in the string. Otherwise, return false.

Example 1:
Input: s = "aaabbb"
Output: true
Explanation:
The 'a's are at indices 0, 1, and 2, while the 'b's are at indices 3, 4, and 5.
Hence, every 'a' appears before every 'b' and we return true.

Example 2:
Input: s = "abab"
Output: false
Explanation:
There is an 'a' at index 2 and a 'b' at index 1.
Hence, not every 'a' appears before every 'b' and we return false.

Example 3:
Input: s = "bbb"
Output: true
Explanation:
There are no 'a's, hence, every 'a' appears before every 'b' and we return true.

Constraints:
1 <= s.length <= 100
s[i] is either 'a' or 'b'.
```

<details><summary>Hint</summary>

```text
1. You can check the opposite: check if there is a ‘b’ before an ‘a’. Then, negate and return that answer.
2. s should not have any occurrences of “ba” as a substring.
```

</details>

</details>

<details><summary>C</summary>

```c
bool checkString(char* s) {
    bool retVal = true;

    bool isChanged = false;
    int sSize = strlen(s);
    int i;
    for (i = 0; i < sSize; ++i) {
        if (s[i] == 'a') {
            if (isChanged == true) {
                retVal = false;
                return retVal;
            }
            continue;
        }

        isChanged = true;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    bool checkString(string s) {
        bool retVal = true;

        bool isChanged = false;
        for (auto c : s) {
            if (c == 'a') {
                if (isChanged == true) {
                    retVal = false;
                    return retVal;
                }
                continue;
            }

            isChanged = true;
        }

        return retVal;
    }
};
```

</details>

## [2129. Capitalize the Title](https://leetcode.com/problems/capitalize-the-title/)  1274

<details><summary>Description</summary>

```text
You are given a string title consisting of one or more words separated by a single space,
where each word consists of English letters.
Capitalize the string by changing the capitalization of each word such that:
- If the length of the word is 1 or 2 letters, change all letters to lowercase.
- Otherwise, change the first letter to uppercase and the remaining letters to lowercase.
Return the capitalized title.

Example 1:
Input: title = "capiTalIze tHe titLe"
Output: "Capitalize The Title"
Explanation:
Since all the words have a length of at least 3,
the first letter of each word is uppercase, and the remaining letters are lowercase.

Example 2:
Input: title = "First leTTeR of EACH Word"
Output: "First Letter of Each Word"
Explanation:
The word "of" has length 2, so it is all lowercase.
The remaining words have a length of at least 3,
so the first letter of each remaining word is uppercase, and the remaining letters are lowercase.

Example 3:
Input: title = "i lOve leetcode"
Output: "i Love Leetcode"
Explanation:
The word "i" has length 1, so it is lowercase.
The remaining words have a length of at least 3,
so the first letter of each remaining word is uppercase, and the remaining letters are lowercase.

Constraints:
1 <= title.length <= 100
title consists of words separated by a single space without any leading or trailing spaces.
Each word consists of uppercase and lowercase English letters and is non-empty.
```

</details>

<details><summary>C</summary>

```c
char* capitalizeTitle(char* title) {
    int len = strlen(title);
    int head = 0;
    int tail = 0;
    for (tail=0; tail<len; ++tail) {
        if (title[tail] == ' ') {
            if ((tail-head) > 2) {
                title[head] = toupper(title[head]);
            }
            head = tail + 1;
        }
        (title[tail]) = tolower(title[tail]);
    }
    if ((tail-head) > 2) {
        title[head] = toupper(title[head]);
    }

    return title;
}
```

</details>

## [2138. Divide a String Into Groups of Size k](https://leetcode.com/problems/divide-a-string-into-groups-of-size-k/)  1273

- [Official](https://leetcode.com/problems/divide-a-string-into-groups-of-size-k/editorial/)
- [Official](https://leetcode.cn/problems/divide-a-string-into-groups-of-size-k/solutions/1233149/jiang-zi-fu-chuan-chai-fen-wei-ruo-gan-c-264k/)

<details><summary>Description</summary>

```text
A string s can be partitioned into groups of size k using the following procedure:
- The first group consists of the first k characters of the string,
  the second group consists of the next k characters of the string,
  and so on. Each element can be a part of exactly one group.
- For the last group, if the string does not have k characters remaining, a character fill is used to complete the group.

Note that the partition is done so that after removing the fill character from the last group (if it exists)
and concatenating all the groups in order, the resultant string should be s.

Given the string s, the size of each group k and the character fill,
return a string array denoting the composition of every group s has been divided into, using the above procedure.

Example 1:
Input: s = "abcdefghi", k = 3, fill = "x"
Output: ["abc","def","ghi"]
Explanation:
The first 3 characters "abc" form the first group.
The next 3 characters "def" form the second group.
The last 3 characters "ghi" form the third group.
Since all groups can be completely filled by characters from the string, we do not need to use fill.
Thus, the groups formed are "abc", "def", and "ghi".

Example 2:
Input: s = "abcdefghij", k = 3, fill = "x"
Output: ["abc","def","ghi","jxx"]
Explanation:
Similar to the previous example, we are forming the first three groups "abc", "def", and "ghi".
For the last group, we can only use the character 'j' from the string. To complete this group, we add 'x' twice.
Thus, the 4 groups formed are "abc", "def", "ghi", and "jxx".

Constraints:
1 <= s.length <= 100
s consists of lowercase English letters only.
1 <= k <= 100
fill is a lowercase English letter.
```

<details><summary>Hint</summary>

```text
1. Using the length of the string and k, can you count the number of groups the string can be divided into?
2. Try completing each group using characters from the string.
   If there aren’t enough characters for the last group, use the fill character to complete the group.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** divideString(char* s, int k, char fill, int* returnSize) {
    char** pRetVal = NULL;

    (*returnSize) = 0;

    int sSize = strlen(s);
    int numberOfStrings = (sSize + k - 1) / k;

    pRetVal = (char**)malloc(numberOfStrings * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    for (int i = 0; i < numberOfStrings; ++i) {
        pRetVal[i] = (char*)malloc((k + 1) * sizeof(char));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            for (int j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
    }

    int start, end;
    for (int i = 0; i < numberOfStrings; ++i) {
        start = i * k;
        end = start + k;
        if (end > sSize) {
            end = sSize;
        }
        strncpy(pRetVal[i], s + start, end - start);
        if (end - start < k) {
            memset(pRetVal[i] + (end - start), fill, k - (end - start));
        }
        pRetVal[i][k] = '\0';

        (*returnSize)++;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<string> divideString(string s, int k, char fill) {
        vector<string> retVal;

        int sSize = s.size();
        int numberOfSubstrings = (sSize + k - 1) / k;
        for (int i = 0; i < numberOfSubstrings; ++i) {
            string part = s.substr(i * k, k);
            int partSize = part.size();
            if (partSize < k) {
                part += string(k - partSize, fill);
            }
            retVal.emplace_back(part);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def divideString(self, s: str, k: int, fill: str) -> List[str]:
        retVal = []

        sSize = len(s)
        for i in range(0, sSize, k):
            part = s[i:i + k]
            partSize = len(part)
            if partSize < k:
                part += (fill * (k - partSize))
            retVal.append(part)

        return retVal
```

</details>

## [2185. Counting Words With a Given Prefix](https://leetcode.com/problems/counting-words-with-a-given-prefix/)  1167

- [Official](https://leetcode.com/problems/counting-words-with-a-given-prefix/editorial/)
- [Official](https://leetcode.cn/problems/counting-words-with-a-given-prefix/solutions/2047256/tong-ji-bao-han-gei-ding-qian-zhui-de-zi-aaq7/)

<details><summary>Description</summary>

```text
You are given an array of strings words and a string pref.

Return the number of strings in words that contain pref as a prefix.

A prefix of a string s is any leading contiguous substring of s.

Example 1:
Input: words = ["pay","attention","practice","attend"], pref = "at"
Output: 2
Explanation: The 2 strings that contain "at" as a prefix are: "attention" and "attend".

Example 2:
Input: words = ["leetcode","win","loops","success"], pref = "code"
Output: 0
Explanation: There are no strings that contain "code" as a prefix.

Constraints:
1 <= words.length <= 100
1 <= words[i].length, pref.length <= 100
words[i] and pref consist of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Go through each word in words and increment the answer if pref is a prefix of the word.
```

</details>

</details>

<details><summary>C</summary>

```c
int prefixCount(char** words, int wordsSize, char* pref) {
    int retVal = 0;

    int len = strlen(pref);
    int i;
    for (i = 0; i < wordsSize; ++i) {
        if (strncmp(words[i], pref, len) == 0) {
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
    int prefixCount(vector<string>& words, string pref) {
        int retVal = 0;

        for (string& word : words) {
            if (word.compare(0, pref.size(), pref) == 0) {
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
    def prefixCount(self, words: List[str], pref: str) -> int:
        retVal = 0

        for word in words:
            if word.startswith(pref):
                retVal += 1

        return retVal
```

</details>

## [2194. Cells in a Range on an Excel Sheet](https://leetcode.com/problems/cells-in-a-range-on-an-excel-sheet/)  2194

- [Official](https://leetcode.cn/problems/cells-in-a-range-on-an-excel-sheet/solutions/1365034/excel-biao-zhong-mou-ge-fan-wei-nei-de-d-uffw/)

<details><summary>Description</summary>

```text
A cell (r, c) of an excel sheet is represented as a string "<col><row>" where:
- <col> denotes the column number c of the cell. It is represented by alphabetical letters.
  - For example, the 1st column is denoted by 'A', the 2nd by 'B', the 3rd by 'C', and so on.
- <row> is the row number r of the cell. The rth row is represented by the integer r.

You are given a string s in the format "<col1><row1>:<col2><row2>",
where <col1> represents the column c1, <row1> represents the row r1, <col2> represents the column c2,
and <row2> represents the row r2, such that r1 <= r2 and c1 <= c2.

Return the list of cells (x, y) such that r1 <= x <= r2 and c1 <= y <= c2.
The cells should be represented as strings in the format mentioned above
and be sorted in non-decreasing order first by columns and then by rows.

Example 1:
Input: s = "K1:L2"
Output: ["K1","K2","L1","L2"]
Explanation:
The above diagram shows the cells which should be present in the list.
The red arrows denote the order in which the cells should be presented.

Example 2:
Input: s = "A1:F1"
Output: ["A1","B1","C1","D1","E1","F1"]
Explanation:
The above diagram shows the cells which should be present in the list.
The red arrow denotes the order in which the cells should be presented.

Constraints:
s.length == 5
'A' <= s[0] <= s[3] <= 'Z'
'1' <= s[1] <= s[4] <= '9'
s consists of uppercase English letters, digits and ':'.
```

<details><summary>Hint</summary>

```text
1. From the given string, find the corresponding rows and columns.
2. Iterate through the columns in ascending order and for each column,
   iterate through the rows in ascending order to obtain the required cells in sorted order.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** cellsInRange(char* s, int* returnSize) {
    char** pRetVal = NULL;

    (*returnSize) = (s[3] - s[0] + 1) * (s[4] - s[1] + 1);
    pRetVal = (char**)malloc((*returnSize) * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }

    // s.length == 5
    // 'A' <= s[0] <= s[3] <= 'Z'
    // '1' <= s[1] <= s[4] <= '9'
    (*returnSize) = 0;
    int returnColumnSizes = 3;
    char row, col;
    for (row = s[0]; row <= s[3]; ++row) {
        for (col = s[1]; col <= s[4]; ++col) {
            pRetVal[(*returnSize)] = (char*)malloc(returnColumnSizes * sizeof(char));
            if (pRetVal == NULL) {
                perror("malloc");
                for (int i = 0; i < (*returnSize); ++i) {
                    free(pRetVal[i]);
                    pRetVal[i] = NULL;
                }
                free(pRetVal);
                pRetVal = NULL;
                (*returnSize) = 0;
                return pRetVal;
            }
            memset(pRetVal[(*returnSize)], 0, (returnColumnSizes * sizeof(char)));
            pRetVal[(*returnSize)][0] = row;
            pRetVal[(*returnSize)][1] = col;
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
   public:
    vector<string> cellsInRange(string s) {
        vector<string> retVal;

        // s.length == 5
        // 'A' <= s[0] <= s[3] <= 'Z'
        // '1' <= s[1] <= s[4] <= '9'
        for (char row = s[0]; row <= s[3]; ++row) {
            for (char col = s[1]; col <= s[4]; ++col) {
                string cell;
                cell.push_back(row);
                cell.push_back(col);
                retVal.emplace_back(cell);
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
    def cellsInRange(self, s: str) -> List[str]:
        retVal = []

        # s.length == 5
        # 'A' <= s[0] <= s[3] <= 'Z'
        # '1' <= s[1] <= s[4] <= '9'
        for row in range(ord(s[0]), ord(s[3])+1):
            for col in range(ord(s[1]), ord(s[4])+1):
                cell = chr(row) + chr(col)
                retVal.append(cell)

        return retVal
```

</details>

## [2243. Calculate Digit Sum of a String](https://leetcode.com/problems/calculate-digit-sum-of-a-string/)  1301

<details><summary>Description</summary>

```text
You are given a string s consisting of digits and an integer k.

A round can be completed if the length of s is greater than k. In one round, do the following:
 1. Divide s into consecutive groups of size k such that the first k characters are in the first group,
 the next k characters are in the second group, and so on.
 Note that the size of the last group can be smaller than k.
 2. Replace each group of s with a string representing the sum of all its digits.
 For example, "346" is replaced with "13" because 3 + 4 + 6 = 13.
 3. Merge consecutive groups together to form a new string.
 If the length of the string is greater than k, repeat from step 1.

Return s after all rounds have been completed.

Example 1:
Input: s = "11111222223", k = 3
Output: "135"
Explanation:
- For the first round, we divide s into groups of size 3: "111", "112", "222", and "23".
  ​​​​​Then we calculate the digit sum of each group: 1 + 1 + 1 = 3, 1 + 1 + 2 = 4, 2 + 2 + 2 = 6, and 2 + 3 = 5.
  So, s becomes "3" + "4" + "6" + "5" = "3465" after the first round.
- For the second round, we divide s into "346" and "5".
  Then we calculate the digit sum of each group: 3 + 4 + 6 = 13, 5 = 5.
  So, s becomes "13" + "5" = "135" after second round.
Now, s.length <= k, so we return "135" as the answer.

Example 2:
Input: s = "00000000", k = 3
Output: "000"
Explanation:
We divide s into "000", "000", and "00".
Then we calculate the digit sum of each group: 0 + 0 + 0 = 0, 0 + 0 + 0 = 0, and 0 + 0 = 0.
s becomes "0" + "0" + "0" = "000", whose length is equal to k, so we return "000".

Constraints:
1 <= s.length <= 100
2 <= k <= 100
s consists of digits only.
```

</details>

<details><summary>C</summary>

```c
int process(char* srcBuf, int k, char* dstBuf)
{
    int idx = 0;

    int len = strlen(srcBuf) + 1;
    int count = k;
    int sum = 0;
    int i;
    for (i=0; *(srcBuf+i); ++i)
    {
        sum += ((int)(*(srcBuf+i)) - 48);
        count--;
        if (count == 0)
        {
            idx += snprintf(dstBuf+idx, len-idx, "%d", sum);
            count = k;
            sum = 0;
        }
    }
    if (count != k)
    {
        idx += snprintf(dstBuf+idx, len-idx, "%d", sum);
    }

    return idx;
}

char * digitSum(char * s, int k){
    char *pRetVal = NULL;

    int len = strlen(s);
    if (len <= k)
    {
        return s;
    }
    char srcBuf[len+1];
    memset(srcBuf, 0, sizeof(srcBuf));
    snprintf(srcBuf, sizeof(srcBuf), "%s", s);

    char dstBuf[len+1];
    len = k + 1;
    while (len > k)
    {
        memset(dstBuf, 0, sizeof(dstBuf));
        len = process(srcBuf, k, dstBuf);
        memset(srcBuf, 0, sizeof(srcBuf));
        snprintf(srcBuf, sizeof(srcBuf), "%s", dstBuf);
    }

    pRetVal = (char*)malloc((len+1)*sizeof(char));
    if (pRetVal == NULL)
    {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, len+1);
    memcpy(pRetVal, dstBuf, len);

    return pRetVal;
}
```

</details>

## [2255. Count Prefixes of a Given String](https://leetcode.com/problems/count-prefixes-of-a-given-string/)  1260

<details><summary>Description</summary>

```text
You are given a string array words and a string s, where words[i] and s comprise only of lowercase English letters.

Return the number of strings in words that are a prefix of s.

A prefix of a string is a substring that occurs at the beginning of the string.
A substring is a contiguous sequence of characters within a string.

Example 1:
Input: words = ["a","b","c","ab","bc","abc"], s = "abc"
Output: 3
Explanation:
The strings in words which are a prefix of s = "abc" are:
"a", "ab", and "abc".
Thus the number of strings in words which are a prefix of s is 3.

Example 2:
Input: words = ["a","a"], s = "aa"
Output: 2
Explanation:
Both of the strings are a prefix of s.
Note that the same string can occur multiple times in words, and it should be counted each time.

Constraints:
1 <= words.length <= 1000
1 <= words[i].length, s.length <= 10
words[i] and s consist of lowercase English letters only.
```

</details>

<details><summary>C</summary>

```c
int countPrefixes(char** words, int wordsSize, char* s) {
    int retVal = 0;

    int i;
    for (i = 0; i < wordsSize; ++i) {
        if (strncmp(words[i], s, strlen(words[i])) == 0) {
            ++retVal;
        }
    }

    return retVal;
}
```

</details>

## [2259. Remove Digit From Number to Maximize Result](https://leetcode.com/problems/remove-digit-from-number-to-maximize-result/)  1331

<details><summary>Description</summary>

```text
You are given a string number representing a positive integer and a character digit.

Return the resulting string after removing exactly one occurrence of digit
from number such that the value of the resulting string in decimal form is maximized.
The test cases are generated such that digit occurs at least once in number.

Example 1:
Input: number = "123", digit = "3"
Output: "12"
Explanation: There is only one '3' in "123". After removing '3', the result is "12".

Example 2:
Input: number = "1231", digit = "1"
Output: "231"
Explanation: We can remove the first '1' to get "231" or remove the second '1' to get "123".
Since 231 > 123, we return "231".

Example 3:
Input: number = "551", digit = "5"
Output: "51"
Explanation: We can remove either the first or second '5' from "551".
Both result in the string "51".

Constraints:
2 <= number.length <= 100
number consists of digits from '1' to '9'.
digit is a digit from '1' to '9'.
digit occurs at least once in number.
```

</details>

<details><summary>C</summary>

```c
char* removeDigit(char* number, char digit) {
    int len = strlen(number);
    int remove = 0;
    int i;
    for (i = 0; i < len; ++i) {
        if (number[i] != digit) {
            continue;
        }
        remove = i;

        if (((i + 1) < len) && (number[i] < number[i + 1])) {
            break;
        }
    }

    for (i = remove + 1; i < len; ++i) {
        number[i - 1] = number[i];
    }
    number[len - 1] = 0;

    return number;
}
```

</details>

## [2264. Largest 3-Same-Digit Number in String](https://leetcode.com/problems/largest-3-same-digit-number-in-string/)  1308

- [Official](https://leetcode.com/problems/largest-3-same-digit-number-in-string/editorial/)
- [Official](https://leetcode.cn/problems/largest-3-same-digit-number-in-string/solutions/1538493/zi-fu-chuan-zhong-zui-da-de-3-wei-xiang-isykz/)

<details><summary>Description</summary>

```text
You are given a string num representing a large integer. An integer is good if it meets the following conditions:
- It is a substring of num with length 3.
- It consists of only one unique digit.

Return the maximum good integer as a string or an empty string "" if no such integer exists.

Note:
- A substring is a contiguous sequence of characters within a string.
- There may be leading zeroes in num or a good integer.

Example 1:
Input: num = "6777133339"
Output: "777"
Explanation: There are two distinct good integers: "777" and "333".
"777" is the largest, so we return "777".

Example 2:
Input: num = "2300019"
Output: "000"
Explanation: "000" is the only good integer.

Example 3:
Input: num = "42352338"
Output: ""
Explanation: No substring of length 3 consists of only one unique digit. Therefore, there are no good integers.

Constraints:
3 <= num.length <= 1000
num only consists of digits.
```

<details><summary>Hint</summary>

```text
1. We can sequentially check if “999”, “888”, “777”, … , “000” exists in num in that order.
   The first to be found is the maximum good integer.
2. If we cannot find any of the above integers, we return an empty string “”.
```

</details>

</details>

<details><summary>C</summary>

```c
char* largestGoodInteger(char* num) {
    char* pRetVal = NULL;

    int numSize = strlen(num);
    if (numSize < 3) {  // 3 <= num.length <= 1000
        return pRetVal;
    }

    int returnSize = 3 + 1;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));

    char goodChar = 0;
    int i;
    for (i = 2; i < numSize; ++i) {
        if ((num[i - 2] != num[i - 1]) || (num[i - 1] != num[i])) {
            continue;
        } else if (goodChar >= num[i - 2]) {
            continue;
        }
        goodChar = num[i - 2];
    }
    if (goodChar != 0) {
        snprintf(pRetVal, returnSize, "%c%c%c", goodChar, goodChar, goodChar);
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string largestGoodInteger(string num) {
        string retVal = "";

        int numSize = num.size();
        if (numSize < 3) {  // 3 <= num.length <= 1000
            return retVal;
        }

        char goodChar = 0;
        for (int i = 2; i < numSize; ++i) {
            if ((num[i - 2] != num[i - 1]) || (num[i - 1] != num[i])) {
                continue;
            } else if (goodChar >= num[i - 2]) {
                continue;
            }
            goodChar = num[i - 2];
        }
        if (goodChar != 0) {
            retVal = string(3, goodChar);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def largestGoodInteger(self, num: str) -> str:
        retVal = ""

        numsSize = len(num)
        if numsSize < 3:    # 3 <= num.length <= 1000
            return retVal

        goodChar = ""
        for i in range(2, numsSize):
            if (num[i-2] != num[i-1]) or (num[i-1] != num[i]):
                continue
            elif goodChar >= num[i-2]:
                continue
            goodChar = num[i-2]
        retVal = goodChar + goodChar + goodChar

        return retVal
```

</details>

## [2299. Strong Password Checker II](https://leetcode.com/problems/strong-password-checker-ii/)  1241

- [Official](https://leetcode.cn/problems/strong-password-checker-ii/solutions/2067624/qiang-mi-ma-jian-yan-qi-ii-by-leetcode-s-p7ru/)

<details><summary>Description</summary>

```text
A password is said to be strong if it satisfies all the following criteria:
- It has at least 8 characters.
- It contains at least one lowercase letter.
- It contains at least one uppercase letter.
- It contains at least one digit.
- It contains at least one special character. The special characters are the characters in the following string: "!@#$%^&*()-+".
- It does not contain 2 of the same character in adjacent positions (i.e., "aab" violates this condition, but "aba" does not).
Given a string password, return true if it is a strong password. Otherwise, return false.

Example 1:
Input: password = "IloveLe3tcode!"
Output: true
Explanation: The password meets all the requirements. Therefore, we return true.

Example 2:
Input: password = "Me+You--IsMyDream"
Output: false
Explanation: The password does not contain a digit and also contains 2 of the same character in adjacent positions.
Therefore, we return false.

Example 3:
Input: password = "1aB!"
Output: false
Explanation: The password does not meet the length requirement. Therefore, we return false.

Constraints:
1 <= password.length <= 100
password consists of letters, digits, and special characters: "!@#$%^&*()-+".
```

</details>

<details><summary>C</summary>

```c
bool strongPasswordCheckerII(char* password) {
    bool retVal = false;

#define STRONG_PASSWORD_LENGTH (8)
#define STRONG_PASSWORD_SPECIAL_CHARACTERS "!@#$%^&*()-+"
#define STRONG_PASSWORD_LOWERCASE_BIT (0)
#define STRONG_PASSWORD_UPPERCASE_BIT (1)
#define STRONG_PASSWORD_DIGIT_BIT (2)
#define STRONG_PASSWORD_SPECIAL_BIT (3)

    int len = strlen(password);
    if (len < STRONG_PASSWORD_LENGTH) {
        return retVal;
    }

    int resultBit = 0;
    int idx;
    int i;
    for (i = 0; i < len; ++i) {
        // It does not contain 2 of the same character in adjacent positions.
        if (password[i] == password[i + 1]) {
            return retVal;
        }

        if ((password[i] >= 'a') && (password[i] <= 'z')) {
            resultBit |= (1 << STRONG_PASSWORD_LOWERCASE_BIT);
        } else if ((password[i] >= 'A') && (password[i] <= 'Z')) {
            resultBit |= (1 << STRONG_PASSWORD_UPPERCASE_BIT);
        } else if ((password[i] >= '0') && (password[i] <= '9')) {
            resultBit |= (1 << STRONG_PASSWORD_DIGIT_BIT);
        } else {
            idx = 0;
            while (STRONG_PASSWORD_SPECIAL_CHARACTERS[idx] != 0) {
                if (password[i] == STRONG_PASSWORD_SPECIAL_CHARACTERS[idx++]) {
                    resultBit |= (1 << STRONG_PASSWORD_SPECIAL_BIT);
                    break;
                }
            }
        }
    }
    if (resultBit == ((1 << STRONG_PASSWORD_LOWERCASE_BIT) | (1 << STRONG_PASSWORD_UPPERCASE_BIT) |
                      (1 << STRONG_PASSWORD_DIGIT_BIT) | (1 << STRONG_PASSWORD_SPECIAL_BIT))) {
        retVal = true;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define STRONG_PASSWORD_LENGTH (8)
#define STRONG_PASSWORD_LOWERCASE_BIT (0)
#define STRONG_PASSWORD_UPPERCASE_BIT (1)
#define STRONG_PASSWORD_DIGIT_BIT (2)
#define STRONG_PASSWORD_SPECIAL_BIT (3)

   public:
    bool strongPasswordCheckerII(string password) {
        bool retVal = false;

        int len = password.length();
        if (len < STRONG_PASSWORD_LENGTH) {
            return retVal;
        }

        int resultBit = 0;
        unordered_set<char> specialCharacters = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '+'};
        for (int i = 0; i < len; ++i) {
            if (password[i] == password[i + 1]) {
                return retVal;
            }

            if (islower(password[i])) {
                resultBit |= (1 << STRONG_PASSWORD_LOWERCASE_BIT);
            } else if (isupper(password[i])) {
                resultBit |= (1 << STRONG_PASSWORD_UPPERCASE_BIT);
            } else if (isdigit(password[i])) {
                resultBit |= (1 << STRONG_PASSWORD_DIGIT_BIT);
            } else if (specialCharacters.count(password[i])) {
                resultBit |= (1 << STRONG_PASSWORD_SPECIAL_BIT);
            }
        }
        if (resultBit == ((1 << STRONG_PASSWORD_LOWERCASE_BIT) | (1 << STRONG_PASSWORD_UPPERCASE_BIT) |
                          (1 << STRONG_PASSWORD_DIGIT_BIT) | (1 << STRONG_PASSWORD_SPECIAL_BIT))) {
            retVal = true;
        }

        return retVal;
    }
};
```

</details>

## [2306. Naming a Company](https://leetcode.com/problems/naming-a-company/)  2305

- [Official](https://leetcode.com/problems/naming-a-company/solutions/3081799/naming-a-company/)

<details><summary>Description</summary>

```text
You are given an array of strings ideas that represents a list of names to be used in the process of naming a company.
The process of naming a company is as follows:

Choose 2 distinct names from ideas, call them ideaA and ideaB.
Swap the first letters of ideaA and ideaB with each other.
If both of the new names are not found in the original ideas,
then the name ideaA ideaB (the concatenation of ideaA and ideaB, separated by a space) is a valid company name.
Otherwise, it is not a valid name.
Return the number of distinct valid names for the company.

Example 1:
Input: ideas = ["coffee","donuts","time","toffee"]
Output: 6
Explanation: The following selections are valid:
- ("coffee", "donuts"): The company name created is "doffee conuts".
- ("donuts", "coffee"): The company name created is "conuts doffee".
- ("donuts", "time"): The company name created is "tonuts dime".
- ("donuts", "toffee"): The company name created is "tonuts doffee".
- ("time", "donuts"): The company name created is "dime tonuts".
- ("toffee", "donuts"): The company name created is "doffee tonuts".
Therefore, there are a total of 6 distinct company names.
The following are some examples of invalid selections:
- ("coffee", "time"): The name "toffee" formed after swapping already exists in the original array.
- ("time", "toffee"): Both names are still the same after swapping and exist in the original array.
- ("coffee", "toffee"): Both names formed after swapping already exist in the original array.

Example 2:
Input: ideas = ["lack","back"]
Output: 0
Explanation: There are no valid selections. Therefore, 0 is returned.

Constraints:
2 <= ideas.length <= 5 * 10^4
1 <= ideas[i].length <= 10
ideas[i] consists of lowercase English letters.
All the strings in ideas are unique.
```

</details>

<details><summary>C</summary>

```c
#define MAX_IDEAS_CHAR (26)       // ideas[i] consists of lowercase English letters.
#define MAX_NAME_LENGTH (10 + 2)  // 1 <= ideas[i].length <= 10
struct hash_struct {
    char idea[MAX_NAME_LENGTH];
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
long long distinctNames(char** ideas, int ideasSize) {
    long long retVal = 0;

    int i, j;

    //
    struct hash_struct* hashTable = NULL;
    struct hash_struct* pTmp;
    for (i = 0; i < ideasSize; ++i) {
        pTmp = NULL;
        HASH_FIND_STR(hashTable, ideas[i], pTmp);
        if (pTmp == NULL) {
            pTmp = (struct hash_struct*)malloc(sizeof(struct hash_struct));
            if (pTmp == NULL) {
                perror("malloc");
                freeAll(hashTable);
                hashTable = NULL;
                return retVal;
            }
            snprintf(pTmp->idea, MAX_NAME_LENGTH, "%s", ideas[i]);
            HASH_ADD_STR(hashTable, idea, pTmp);
        }
    }

    //
    long long statistic[MAX_IDEAS_CHAR][MAX_IDEAS_CHAR];
    memset(statistic, 0, sizeof(statistic));
    int prefix;
    char buf[MAX_NAME_LENGTH];
    for (i = 0; i < ideasSize; ++i) {
        prefix = ideas[i][0] - 'a';

        for (j = 0; j < MAX_IDEAS_CHAR; ++j) {
            memset(buf, 0, sizeof(buf));
#if 0  // Time Limit Exceeded
            snprintf(buf, sizeof(buf), "%c%s", j + 'a', ideas[i] + 1);
#else
            buf[0] = j + 'a';
            strncpy(buf + 1, ideas[i] + 1, sizeof(buf) - 2);
#endif

            pTmp = NULL;
            HASH_FIND_STR(hashTable, buf, pTmp);
            if (pTmp == NULL) {
                ++statistic[prefix][j];
            }
        }
    }
    freeAll(hashTable);

    //
    for (i = 0; i < MAX_IDEAS_CHAR; ++i) {
        for (j = 0; j < MAX_IDEAS_CHAR; ++j) {
            retVal += (statistic[i][j] * statistic[j][i]);
        }
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define MAX_IDEAS_CHAR (26)  // ideas[i] consists of lowercase English letters.
   public:
    // https://leetcode.cn/problems/naming-a-company/solutions/1596934/c-by-kotori-5-ztts/
    long long distinctNames(vector<string>& ideas) {
        long long retVal = 0;

        vector<vector<long long>> statistic(MAX_IDEAS_CHAR, vector<long long>(MAX_IDEAS_CHAR));
        unordered_set<string> ideaSet(ideas.begin(), ideas.end());

        for (string& idea : ideas) {
            int prefix = idea[0] - 'a';

            for (int i = 0; i < MAX_IDEAS_CHAR; ++i) {
                idea[0] = (i + 'a');
                if (ideaSet.count(idea) == 0) {
                    statistic[prefix][i]++;
                }
            }
        }

        for (int i = 0; i < MAX_IDEAS_CHAR; ++i) {
            for (int j = 0; j < MAX_IDEAS_CHAR; ++j) {
                retVal += (statistic[i][j] * statistic[j][i]);
            }
        }

        return retVal;
    }
};
```

</details>

## [2315. Count Asterisks](https://leetcode.com/problems/count-asterisks/)  1250

- [Official](https://leetcode.cn/problems/count-asterisks/solutions/2079495/tong-ji-xing-hao-by-leetcode-solution-rwbs/)

<details><summary>Description</summary>

```text
You are given a string s, where every two consecutive vertical bars '|' are grouped into a pair.
In other words, the 1st and 2nd '|' make a pair, the 3rd and 4th '|' make a pair, and so forth.

Return the number of '*' in s, excluding the '*' between each pair of '|'.

Note that each '|' will belong to exactly one pair.

Example 1:
Input: s = "l|*e*et|c**o|*de|"
Output: 2
Explanation: The considered characters are underlined: "l|*e*et|c**o|*de|".
The characters between the first and second '|' are excluded from the answer.
Also, the characters between the third and fourth '|' are excluded from the answer.
There are 2 asterisks considered. Therefore, we return 2.

Example 2:
Input: s = "iamprogrammer"
Output: 0
Explanation: In this example, there are no asterisks in s. Therefore, we return 0.

Example 3:
Input: s = "yo|uar|e**|b|e***au|tifu|l"
Output: 5
Explanation: The considered characters are underlined: "yo|uar|e**|b|e***au|tifu|l".
There are 5 asterisks considered. Therefore, we return 5.

Constraints:
1 <= s.length <= 1000
s consists of lowercase English letters, vertical bars '|', and asterisks '*'.
s contains an even number of vertical bars '|'.
```

</details>

<details><summary>C</summary>

```c
int countAsterisks(char* s) {
    int retVal = 0;

    int verticalBars = 0;
    int len = strlen(s);
    int i;
    for (i = 0; i < len; ++i) {
        if (s[i] == '|') {
            ++verticalBars;
            continue;
        }

        if (verticalBars % 2 == 1) {
            continue;
        }

        if (s[i] == '*') {
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
    int countAsterisks(string s) {
        int retVal = 0;

        int verticalBars = 0;
        for (auto c : s) {
            if (c == '|') {
                ++verticalBars;
                continue;
            }

            if (verticalBars % 2 == 1) {
                continue;
            }

            if (c == '*') {
                ++retVal;
            }
        }

        return retVal;
    }
};
```

</details>

<details><summary>Rust</summary>

```rust
// #[cfg(clang)]
impl Solution {
    pub fn count_asterisks(s: String) -> i32 {
        let mut ret_val = 0;

        // println!("clang");

        let mut vertical_bars = 0;
        for c in s.chars() {
            if c == '|' {
                vertical_bars += 1;
                continue;
            }

            if vertical_bars % 2 == 1 {
                continue;
            }

            if c == '*' {
                ret_val += 1;
            }
        }

        return ret_val;
    }
}
// https://leetcode.com/problems/count-asterisks/solutions/2895643/rust-one-liner-on-iterators/
// #[cfg(not(clang))]
#[cfg(rust1)]
impl Solution {
    pub fn count_asterisks(s: String) -> i32 {
        println!("rust1");

        s.split("|")
            .step_by(2)
            .map(|str| str.chars().filter(|c| c == &'*').count() as i32)
            .sum::<i32>()
    }
}
// https://leetcode.com/problems/count-asterisks/solutions/2200493/rust-one-liner/
// #[cfg(not(clang))]
#[cfg(rust2)]
impl Solution {
    pub fn count_asterisks(s: String) -> i32 {
        println!("rust2");

        s.split('|')
            .enumerate()
            .filter_map(|(i, s)| if i % 2 == 0 { Some(s.chars()) } else { None })
            .flatten()
            .filter(|&c| c == '*')
            .count() as _
    }
}
```

</details>

## [2381. Shifting Letters II](https://leetcode.com/problems/shifting-letters-ii/)  1793

- [Official](https://leetcode.com/problems/shifting-letters-ii/editorial/)

<details><summary>Description</summary>

```text
You are given a string s of lowercase English letters
and a 2D integer array shifts where shifts[i] = [starti, endi, directioni].
For every i, shift the characters in s from the index starti to the index endi (inclusive) forward if directioni = 1,
or shift the characters backward if directioni = 0.

Shifting a character forward means
replacing it with the next letter in the alphabet (wrapping around so that 'z' becomes 'a').
Similarly, shifting a character backward means
replacing it with the previous letter in the alphabet (wrapping around so that 'a' becomes 'z').

Return the final string after all such shifts to s are applied.

Example 1:
Input: s = "abc", shifts = [[0,1,0],[1,2,1],[0,2,1]]
Output: "ace"
Explanation: Firstly, shift the characters from index 0 to index 1 backward. Now s = "zac".
Secondly, shift the characters from index 1 to index 2 forward. Now s = "zbd".
Finally, shift the characters from index 0 to index 2 forward. Now s = "ace".

Example 2:
Input: s = "dztz", shifts = [[0,0,0],[1,1,1]]
Output: "catz"
Explanation: Firstly, shift the characters from index 0 to index 0 backward. Now s = "cztz".
Finally, shift the characters from index 1 to index 1 forward. Now s = "catz".

Constraints:
1 <= s.length, shifts.length <= 5 * 10^4
shifts[i].length == 3
0 <= starti <= endi < s.length
0 <= directioni <= 1
s consists of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Instead of shifting every character in each shift,
   could you keep track of which characters are shifted and by how much across all shifts?
2. Try marking the start and ends of each shift, then perform a prefix sum of the shifts.
```

</details>

</details>

<details><summary>C</summary>

```c
char* shiftingLetters(char* s, int** shifts, int shiftsSize, int* shiftsColSize) {
    char* pRetVal = s;

    int sSize = strlen(s);

    int diffArray[sSize];
    memset(diffArray, 0, sizeof(diffArray));
    for (int i = 0; i < shiftsSize; i++) {
        if (shifts[i][2] == 1) {
            diffArray[shifts[i][0]]++;
            if (shifts[i][1] + 1 < sSize) {
                diffArray[shifts[i][1] + 1]--;
            }
        } else {
            diffArray[shifts[i][0]]--;
            if (shifts[i][1] + 1 < sSize) {
                diffArray[shifts[i][1] + 1]++;
            }
        }
    }

    int numberOfShifts = 0;
    for (int i = 0; i < sSize; i++) {
        numberOfShifts = (numberOfShifts + diffArray[i]) % 26;
        if (numberOfShifts < 0) {
            numberOfShifts += 26;
        }
        pRetVal[i] = 'a' + (s[i] - 'a' + numberOfShifts) % 26;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string shiftingLetters(string s, vector<vector<int>>& shifts) {
        string retVal = s;

        int sSize = s.size();

        vector<int> diffArray(sSize, 0);
        for (auto shift : shifts) {
            if (shift[2] == 1) {
                diffArray[shift[0]]++;
                if (shift[1] + 1 < sSize) {
                    diffArray[shift[1] + 1]--;
                }
            } else {
                diffArray[shift[0]]--;
                if (shift[1] + 1 < sSize) {
                    diffArray[shift[1] + 1]++;
                }
            }
        }

        int numberOfShifts = 0;
        for (int i = 0; i < sSize; i++) {
            numberOfShifts = (numberOfShifts + diffArray[i]) % 26;
            if (numberOfShifts < 0) {
                numberOfShifts += 26;
            }
            retVal[i] = 'a' + (s[i] - 'a' + numberOfShifts) % 26;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def shiftingLetters(self, s: str, shifts: List[List[int]]) -> str:
        retVal = ""

        sSize = len(s)

        diffArray = [0] * sSize
        for start, end, direction in shifts:
            if direction == 1:
                diffArray[start] += 1
                if end + 1 < sSize:
                    diffArray[end + 1] -= 1
            else:
                diffArray[start] -= 1
                if end + 1 < sSize:
                    diffArray[end + 1] += 1

        numberOfShifts = 0
        for i in range(sSize):
            numberOfShifts = (numberOfShifts + diffArray[i]) % 26
            if numberOfShifts < 0:
                numberOfShifts += 26
            retVal += chr((ord(s[i]) - ord("a") + numberOfShifts) % 26 + ord("a"))

        return retVal
```

</details>

## [2414. Length of the Longest Alphabetical Continuous Substring](https://leetcode.com/problems/length-of-the-longest-alphabetical-continuous-substring/)  1221

<details><summary>Description</summary>

```text
An alphabetical continuous string is a string consisting of consecutive letters in the alphabet.
In other words, it is any substring of the string "abcdefghijklmnopqrstuvwxyz".

For example, "abc" is an alphabetical continuous string, while "acb" and "za" are not.
Given a string s consisting of lowercase letters only, return the length of the longest alphabetical continuous substring.

Example 1:
Input: s = "abacaba"
Output: 2
Explanation: There are 4 distinct continuous substrings: "a", "b", "c" and "ab".
"ab" is the longest continuous substring.

Example 2:
Input: s = "abcde"
Output: 5
Explanation: "abcde" is the longest continuous substring.

Constraints:
1 <= s.length <= 10^5
s consists of only English lowercase letters.
```

</details>

<details><summary>C</summary>

```c
#define LOWERCASE_MAX_SIZE  (26)

int longestContinuousSubstring(char * s){
    int retVal = 1;

    int count = 1;
    int len = strlen(s);
    int i;
    for (i=1; i<len; ++i)
    {
        if (s[i] - s[i-1] == 1)
        {
            ++count;
            retVal = (retVal>count)?retVal:count;
        }
        else
        {
            count = 1;
        }

#if 1
        if (retVal == LOWERCASE_MAX_SIZE)
        {
            break;
        }
#endif
    }

    return retVal;
}
```

</details>

## [2490. Circular Sentence](https://leetcode.com/problems/circular-sentence/)  1262

- [Official](https://leetcode.com/problems/circular-sentence/editorial/)
- [Official](https://leetcode.cn/problems/circular-sentence/solutions/2314909/hui-huan-ju-by-leetcode-solution-h853/)

<details><summary>Description</summary>

```text
A sentence is a list of words that are separated by a single space with no leading or trailing spaces.
- For example, "Hello World", "HELLO", "hello world hello world" are all sentences.

Words consist of only uppercase and lowercase English letters.
Uppercase and lowercase English letters are considered different.

A sentence is circular if:
- The last character of a word is equal to the first character of the next word.
- The last character of the last word is equal to the first character of the first word.

For example, "leetcode exercises sound delightful", "eetcode", "leetcode eats soul" are all circular sentences.
However, "Leetcode is cool", "happy Leetcode", "Leetcode" and "I like Leetcode" are not circular sentences.

Given a string sentence, return true if it is circular. Otherwise, return false.

Example 1:
Input: sentence = "leetcode exercises sound delightful"
Output: true
Explanation: The words in sentence are ["leetcode", "exercises", "sound", "delightful"].
- leetcode's last character is equal to exercises's first character.
- exercises's last character is equal to sound's first character.
- sound's last character is equal to delightful's first character.
- delightful's last character is equal to leetcode's first character.
The sentence is circular.

Example 2:
Input: sentence = "eetcode"
Output: true
Explanation: The words in sentence are ["eetcode"].
- eetcode's last character is equal to eetcode's first character.
The sentence is circular.

Example 3:
Input: sentence = "Leetcode is cool"
Output: false
Explanation: The words in sentence are ["Leetcode", "is", "cool"].
- Leetcode's last character is not equal to is's first character.
The sentence is not circular.

Constraints:
1 <= sentence.length <= 500
sentence consist of only lowercase and uppercase English letters and spaces.
The words in sentence are separated by a single space.
There are no leading or trailing spaces.
```

<details><summary>Hint</summary>

```text
1. Check the character before the empty space and the character after the empty space.
2. Check the first character and the last character of the sentence.
```

</details>

</details>

<details><summary>C</summary>

```c
bool isCircularSentence(char* sentence) {
    bool retVal = false;

    int sentenceSize = strlen(sentence);
    if (sentence[0] != sentence[sentenceSize - 1]) {
        return retVal;
    }
    // A sentence is a list of words that are separated by a single space with no leading or trailing spaces.
    int i;
    for (i = 0; i < sentenceSize; ++i) {
        if ((sentence[i] == ' ') && (sentence[i - 1] != sentence[i + 1])) {
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
    bool isCircularSentence(string sentence) {
        bool retVal = false;

        int sentenceSize = sentence.size();
        if (sentence[0] != sentence[sentenceSize - 1]) {
            return retVal;
        }
        // A sentence is a list of words that are separated by a single space with no leading or trailing spaces.
        for (int i = 0; i < sentenceSize; ++i) {
            if ((sentence[i] == ' ') && (sentence[i - 1] != sentence[i + 1])) {
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
    def isCircularSentence(self, sentence: str) -> bool:
        retVal = False

        sentenceSize = len(sentence)

        if sentence[0] != sentence[sentenceSize-1]:
            return retVal

        # A sentence is a list of words that are separated by a single space with no leading or trailing spaces.
        for i in range(sentenceSize):
            if (sentence[i] == ' ') and (sentence[i-1] != sentence[i+1]):
                return retVal

        retVal = True

        return retVal
```

</details>

## [2645. Minimum Additions to Make Valid String](https://leetcode.com/problems/minimum-additions-to-make-valid-string/)  1477

<details><summary>Description</summary>

```text
Given a string word to which you can insert letters "a", "b" or "c" anywhere and any number of times,
return the minimum number of letters that must be inserted so that word becomes valid.

A string is called valid if it can be formed by concatenating the string "abc" several times.

Example 1:
Input: word = "b"
Output: 2
Explanation: Insert the letter "a" right before "b", and the letter "c" right next to "a" to obtain the valid string "abc".

Example 2:
Input: word = "aaa"
Output: 6
Explanation: Insert letters "b" and "c" next to each "a" to obtain the valid string "abcabcabc".

Example 3:
Input: word = "abc"
Output: 0
Explanation: word is already valid. No modifications are needed.

Constraints:
1 <= word.length <= 50
word consists of letters "a", "b" and "c" only.
```

<details><summary>Hint</summary>

```text
1. Maintain a pointer on word and another pointer on string “abc”.
2. If the two characters that are being pointed to differ, Increment the answer and the pointer to the string “abc” by one.
```

</details>

</details>

<details><summary>C</summary>

```c
// https://leetcode.com/problems/minimum-additions-to-make-valid-string/solutions/3421831/java-c-python-easy-and-concise-with-explanation/
int addMinimum(char* word) {
    int retVal = 0;

    int count = 0;
    char previousChar = 'z';
    int wordSize = strlen(word);
    int i;
    for (i = 0; i < wordSize; ++i) {
        count += (word[i] <= previousChar);
        previousChar = word[i];
    }
    retVal = 3 * count - wordSize;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    // https://leetcode.com/problems/minimum-additions-to-make-valid-string/solutions/3421831/java-c-python-easy-and-concise-with-explanation/
    int addMinimum(string word) {
        int retVal = 0;

        int count = 0;
        char previousChar = 'z';
        for (auto c : word) {
            count += (c <= previousChar);
            previousChar = c;
        }
        retVal = 3 * count - word.size();

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    # https://leetcode.com/problems/minimum-additions-to-make-valid-string/solutions/3421831/java-c-python-easy-and-concise-with-explanation/
    def addMinimum(self, word: str) -> int:
        retVal = 0

        count = 0
        previousChar = 'z'
        for c in word:
            count += (c <= previousChar)
            previousChar = c
        retVal = count * 3 - len(word)

        return retVal
```

</details>

## [2678. Number of Senior Citizens](https://leetcode.com/problems/number-of-senior-citizens/)  1198

- [Official](https://leetcode.com/problems/number-of-senior-citizens/editorial/)
- [Official](https://leetcode.cn/problems/number-of-senior-citizens/solutions/2379660/lao-ren-de-shu-mu-by-leetcode-solution-6msk/)

<details><summary>Description</summary>

```text
You are given a 0-indexed array of strings details.
Each element of details provides information about a given passenger compressed into a string of length 15.
The system is such that:
- The first ten characters consist of the phone number of passengers.
- The next character denotes the gender of the person.
- The following two characters are used to indicate the age of the person.
- The last two characters determine the seat allotted to that person.

Return the number of passengers who are strictly more than 60 years old.

Example 1:
Input: details = ["7868190130M7522","5303914400F9211","9273338290F4010"]
Output: 2
Explanation: The passengers at indices 0, 1, and 2 have ages 75, 92, and 40.
Thus, there are 2 people who are over 60 years old.

Example 2:
Input: details = ["1313579440F2036","2921522980M5644"]
Output: 0
Explanation: None of the passengers are older than 60.

Constraints:
1 <= details.length <= 100
details[i].length == 15
details[i] consists of digits from '0' to '9'.
details[i][10] is either 'M' or 'F' or 'O'.
The phone numbers and seat numbers of the passengers are distinct.
```

<details><summary>Hint</summary>

```text
1. Convert the value at index 11 and 12 to a numerical value.
2. The age of the person at index i is equal to details[i][11]*10+details[i][12].
```

</details>

</details>

<details><summary>C</summary>

```c
int countSeniors(char **details, int detailsSize) {
    int retVal = 0;

    int age;
    int i;
    for (i = 0; i < detailsSize; ++i) {
        age = 10 * (details[i][11] - '0') + (details[i][12] - '0');
        if (age > 60) {
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
    int countSeniors(vector<string>& details) {
        int retVal = 0;

        for (string detail : details) {
            int age = 10 * (detail[11] - '0') + (detail[12] - '0');
            if (age > 60) {
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
    def countSeniors(self, details: List[str]) -> int:
        retVal = 0

        for detail in details:
            age = 10 * (ord(detail[11])-ord('0')) + (ord(detail[12])-ord('0'))
            if age > 60:
                retVal += 1

        return retVal
```

</details>

## [2914. Minimum Number of Changes to Make Binary String Beautiful](https://leetcode.com/problems/minimum-number-of-changes-to-make-binary-string-beautiful/)  1479

- [Official](https://leetcode.com/problems/minimum-number-of-changes-to-make-binary-string-beautiful/editorial/)

<details><summary>Description</summary>

```text
You are given a 0-indexed binary string s having an even length.

A string is beautiful if it's possible to partition it into one or more substrings such that:
- Each substring has an even length.
- Each substring contains only 1's or only 0's.

You can change any character in s to 0 or 1.

Return the minimum number of changes required to make the string s beautiful.

Example 1:
Input: s = "1001"
Output: 2
Explanation: We change s[1] to 1 and s[3] to 0 to get string "1100".
It can be seen that the string "1100" is beautiful because we can partition it into "11|00".
It can be proven that 2 is the minimum number of changes needed to make the string beautiful.

Example 2:
Input: s = "10"
Output: 1
Explanation: We change s[1] to 1 to get string "11".
It can be seen that the string "11" is beautiful because we can partition it into "11".
It can be proven that 1 is the minimum number of changes needed to make the string beautiful.

Example 3:
Input: s = "0000"
Output: 0
Explanation: We don't need to make any changes as the string "0000" is beautiful already.

Constraints:
2 <= s.length <= 10^5
s has an even length.
s[i] is either '0' or '1'.
```

<details><summary>Hint</summary>

```text
1. For any valid partition, since each part consists of an even number of the same characters,
   we can further partition each part into lengths of exactly 2.
2. After noticing the first hint, we can decompose the whole string into disjoint blocks of size 2 and
   find the minimum number of changes required to make those blocks beautiful.
```

</details>

</details>

<details><summary>C</summary>

```c
int minChanges(char* s) {
    int retVal = 0;

    int sSize = strlen(s);
    int i;
    for (i = 1; i < sSize; i += 2) {
        if (s[i - 1] != s[i]) {
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
    int minChanges(string s) {
        int retVal = 0;

        int sSize = s.size();
        for (int i = 1; i < sSize; i += 2) {
            if (s[i - 1] != s[i]) {
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
    def minChanges(self, s: str) -> int:
        retVal = 0

        sSize = len(s)
        for i in range(1, sSize, 2):
            if s[i-1] != s[i]:
                retVal += 1

        return retVal
```

</details>

## [2942. Find Words Containing Character](https://leetcode.com/problems/find-words-containing-character/)  1182

- [Official](https://leetcode.com/problems/find-words-containing-character/editorial/)
- [Official](https://leetcode.cn/problems/find-words-containing-character/solutions/3674716/cha-zhao-bao-han-gei-ding-zi-fu-de-dan-c-ee7m/)

<details><summary>Description</summary>

```text
You are given a 0-indexed array of strings words and a character x.

Return an array of indices representing the words that contain the character x.

Note that the returned array may be in any order.

Example 1:
Input: words = ["leet","code"], x = "e"
Output: [0,1]
Explanation: "e" occurs in both words: "leet", and "code". Hence, we return indices 0 and 1.

Example 2:
Input: words = ["abc","bcd","aaaa","cbc"], x = "a"
Output: [0,2]
Explanation: "a" occurs in "abc", and "aaaa". Hence, we return indices 0 and 2.

Example 3:
Input: words = ["abc","bcd","aaaa","cbc"], x = "z"
Output: []
Explanation: "z" does not occur in any of the words. Hence, we return an empty array.

Constraints:
1 <= words.length <= 50
1 <= words[i].length <= 50
x is a lowercase English letter.
words[i] consists only of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Use two nested loops.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findWordsContaining(char** words, int wordsSize, char x, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int*)malloc(wordsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, wordsSize * sizeof(int));

    int wordSize;
    for (int i = 0; i < wordsSize; ++i) {
        wordSize = strlen(words[i]);
        for (int j = 0; j < wordSize; ++j) {
            if (words[i][j] == x) {
                pRetVal[(*returnSize)++] = i;
                break;
            }
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
    vector<int> findWordsContaining(vector<string>& words, char x) {
        vector<int> retVal;

        int wordsSize = words.size();
        for (int i = 0; i < wordsSize; ++i) {
            int wordSize = words[i].size();
            for (int j = 0; j < wordSize; ++j) {
                if (words[i][j] == x) {
                    retVal.emplace_back(i);
                    break;
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
    def findWordsContaining(self, words: List[str], x: str) -> List[int]:
        retVal = []

        for index, word in enumerate(words):
            if x in word:
                retVal.append(index)

        return retVal
```

</details>
