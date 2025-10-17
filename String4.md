# String

## [3003. Maximize the Number of Partitions After Operations](https://leetcode.com/problems/maximize-the-number-of-partitions-after-operations/)  3039

- [Official](https://leetcode.com/problems/maximize-the-number-of-partitions-after-operations/editorial/)
- [Official](https://leetcode.cn/problems/maximize-the-number-of-partitions-after-operations/solutions/3799989/zhi-xing-cao-zuo-hou-de-zui-da-fen-ge-sh-fwni/)

<details><summary>Description</summary>

```text
You are given a string s and an integer k.

First, you are allowed to change at most one index in s to another lowercase English letter.

After that, do the following partitioning operation until s is empty:
- Choose the longest prefix of s containing at most k distinct characters.
- Delete the prefix from s and increase the number of partitions by one.
  The remaining characters (if any) in s maintain their initial order.

Return an integer denoting the maximum number of resulting partitions
after the operations by optimally choosing at most one index to change.

Example 1:
Input: s = "accca", k = 2
Output: 3
Explanation:
The optimal way is to change s[2] to something other than a and c, for example, b. then it becomes "acbca".
Then we perform the operations:
- The longest prefix containing at most 2 distinct characters is "ac", we remove it and s becomes "bca".
- Now The longest prefix containing at most 2 distinct characters is "bc", so we remove it and s becomes "a".
- Finally, we remove "a" and s becomes empty, so the procedure ends.
Doing the operations, the string is divided into 3 partitions, so the answer is 3.

Example 2:
Input: s = "aabaab", k = 3
Output: 1
Explanation:
Initially s contains 2 distinct characters, so whichever character we change,
it will contain at most 3 distinct characters,
so the longest prefix with at most 3 distinct characters would always be all of it, therefore the answer is 1.

Example 3:
Input: s = "xxyz", k = 1
Output: 4
Explanation:
The optimal way is to change s[0] or s[1] to something other than characters in s, for example, to change s[0] to w.
Then s becomes "wxyz", which consists of 4 distinct characters, so as k is 1, it will divide into 4 partitions.

Constraints:
1 <= s.length <= 10^4
s consists only of lowercase English letters.
1 <= k <= 26
```

<details><summary>Hint</summary>

```text
1. For each position, try to brute-force the replacements.
2. To speed up the brute-force solution,
   we can precompute the following (without changing any index) using prefix sums and binary search:
   - pref[i]: The number of resulting partitions from the operations by performing the operations on s[0:i].
   - suff[i]: The number of resulting partitions from the operations by performing the operations on s[i:n - 1],
     where n == s.length.
   - partition_start[i]: The start index of the partition containing the ith index after performing the operations.
3. Now, for a position i, we can try all possible 25 replacements:
   For a replacement, using prefix sums and binary search, we need to find the rightmost index, r,
   such that the number of distinct characters in the range [partition_start[i], r] is at most k.
   There are 2 cases:
   - r >= i: the number of resulting partitions in this case is 1 + pref[partition_start[i] - 1] + suff[r + 1].
   - Otherwise, we need to find the rightmost index r2
     such that the number of distinct characters in the range [r:r2] is at most k.
     The answer in this case is 2 + pref[partition_start[i] - 1] + suff[r2 + 1]
4. The answer is the maximum among all replacements.
```

</details>

</details>

<details><summary>C</summary>

```c
int maxPartitionsAfterOperations(char* s, int k) {
    int retVal = 0;

    int sSize = strlen(s);

    int left[sSize][3];
    memset(left, 0, sizeof(left));
    int right[sSize][3];
    memset(right, 0, sizeof(right));
    int num, mask, count, binary;

    num = 0;
    mask = 0;
    count = 0;
    for (int i = 0; i < sSize - 1; i++) {
        binary = 1 << (s[i] - 'a');
        if (!(mask & binary)) {
            count++;
            if (count <= k) {
                mask |= binary;
            } else {
                num++;
                mask = binary;
                count = 1;
            }
        }
        left[i + 1][0] = num;
        left[i + 1][1] = mask;
        left[i + 1][2] = count;
    }

    num = 0;
    mask = 0;
    count = 0;
    for (int i = sSize - 1; i > 0; i--) {
        binary = 1 << (s[i] - 'a');
        if (!(mask & binary)) {
            count++;
            if (count <= k) {
                mask |= binary;
            } else {
                num++;
                mask = binary;
                count = 1;
            }
        }
        right[i - 1][0] = num;
        right[i - 1][1] = mask;
        right[i - 1][2] = count;
    }

    int maxLetters = 26;  // s consists only of lowercase English letters.
    int seg, totMask, totCount, minVal;
    for (int i = 0; i < sSize; i++) {
        seg = left[i][0] + right[i][0] + 2;
        totMask = left[i][1] | right[i][1];
        totCount = 0;
        while (totMask) {
            totMask = totMask & (totMask - 1);
            totCount++;
        }

        if ((left[i][2] == k) && (right[i][2] == k) && (totCount < maxLetters)) {
            seg++;
        } else {
            minVal = fmin(totCount + 1, maxLetters);
            if (minVal <= k) {
                seg--;
            }
        }
        retVal = fmax(retVal, seg);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxPartitionsAfterOperations(string s, int k) {
        int retVal = 0;

        int sSize = s.length();
        vector<vector<int>> left(sSize, vector<int>(3));
        vector<vector<int>> right(sSize, vector<int>(3));
        int num, mask, count;

        num = 0;
        mask = 0;
        count = 0;
        for (int i = 0; i < sSize - 1; i++) {
            int binary = 1 << (s[i] - 'a');
            if (!(mask & binary)) {
                count++;
                if (count <= k) {
                    mask |= binary;
                } else {
                    num++;
                    mask = binary;
                    count = 1;
                }
            }
            left[i + 1][0] = num;
            left[i + 1][1] = mask;
            left[i + 1][2] = count;
        }

        num = 0;
        mask = 0;
        count = 0;
        for (int i = sSize - 1; i > 0; i--) {
            int binary = 1 << (s[i] - 'a');
            if (!(mask & binary)) {
                count++;
                if (count <= k) {
                    mask |= binary;
                } else {
                    num++;
                    mask = binary;
                    count = 1;
                }
            }
            right[i - 1][0] = num;
            right[i - 1][1] = mask;
            right[i - 1][2] = count;
        }

        int maxLetters = 26;  // s consists only of lowercase English letters.
        for (int i = 0; i < sSize; i++) {
            int seg = left[i][0] + right[i][0] + 2;
            int totMask = left[i][1] | right[i][1];
            int totCount = 0;
            while (totMask) {
                totMask = totMask & (totMask - 1);
                totCount++;
            }
            if ((left[i][2] == k) && (right[i][2] == k) && (totCount < maxLetters)) {
                seg++;
            } else if (min(totCount + 1, maxLetters) <= k) {
                seg--;
            }
            retVal = max(retVal, seg);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxPartitionsAfterOperations(self, s: str, k: int) -> int:
        retVal = 0

        sSize = len(s)
        left = [[0] * 3 for _ in range(sSize)]
        right = [[0] * 3 for _ in range(sSize)]

        num, mask, count = 0, 0, 0
        for i in range(sSize - 1):
            binary = 1 << (ord(s[i]) - ord("a"))
            if not (mask & binary):
                count += 1
                if count <= k:
                    mask |= binary
                else:
                    num += 1
                    mask = binary
                    count = 1
            left[i + 1][0] = num
            left[i + 1][1] = mask
            left[i + 1][2] = count

        num, mask, count = 0, 0, 0
        for i in range(sSize - 1, 0, -1):
            binary = 1 << (ord(s[i]) - ord("a"))
            if not (mask & binary):
                count += 1
                if count <= k:
                    mask |= binary
                else:
                    num += 1
                    mask = binary
                    count = 1
            right[i - 1][0] = num
            right[i - 1][1] = mask
            right[i - 1][2] = count

        maxLetters = 26  # s consists only of lowercase English letters.
        for i in range(sSize):
            seg = left[i][0] + right[i][0] + 2
            totMask = left[i][1] | right[i][1]
            totCount = bin(totMask).count("1")
            if (left[i][2] == k) and (right[i][2] == k) and (totCount < maxLetters):
                seg += 1
            elif min(totCount + 1, maxLetters) <= k:
                seg -= 1
            retVal = max(retVal, seg)

        return retVal
```

</details>

## [3042. Count Prefix and Suffix Pairs I](https://leetcode.com/problems/count-prefix-and-suffix-pairs-i/)  1214

- [Official](https://leetcode.com/problems/count-prefix-and-suffix-pairs-i/editorial/)

<details><summary>Description</summary>

```text
You are given a 0-indexed string array words.

Let's define a boolean function isPrefixAndSuffix that takes two strings, str1 and str2:
- isPrefixAndSuffix(str1, str2) returns true if str1 is both a prefix and a suffix of str2, and false otherwise.

For example, isPrefixAndSuffix("aba", "ababa") is true because "aba" is a prefix of "ababa" and also a suffix,
but isPrefixAndSuffix("abc", "abcd") is false.

Return an integer denoting the number of index pairs (i, j) such that i < j,
and isPrefixAndSuffix(words[i], words[j]) is true.

Example 1:
Input: words = ["a","aba","ababa","aa"]
Output: 4
Explanation: In this example, the counted index pairs are:
i = 0 and j = 1 because isPrefixAndSuffix("a", "aba") is true.
i = 0 and j = 2 because isPrefixAndSuffix("a", "ababa") is true.
i = 0 and j = 3 because isPrefixAndSuffix("a", "aa") is true.
i = 1 and j = 2 because isPrefixAndSuffix("aba", "ababa") is true.
Therefore, the answer is 4.

Example 2:
Input: words = ["pa","papa","ma","mama"]
Output: 2
Explanation: In this example, the counted index pairs are:
i = 0 and j = 1 because isPrefixAndSuffix("pa", "papa") is true.
i = 2 and j = 3 because isPrefixAndSuffix("ma", "mama") is true.
Therefore, the answer is 2.

Example 3:
Input: words = ["abab","ab"]
Output: 0
Explanation: In this example, the only valid index pair is i = 0 and j = 1,
and isPrefixAndSuffix("abab", "ab") is false.
Therefore, the answer is 0.

Constraints:
1 <= words.length <= 50
1 <= words[i].length <= 10
words[i] consists only of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Iterate through all index pairs (i, j), such that i < j, and check isPrefixAndSuffix(words[i], words[j]).
2. The answer is the total number of pairs where isPrefixAndSuffix(words[i], words[j]) == true.
```

</details>

</details>

<details><summary>C</summary>

```c
int countPrefixSuffixPairs(char** words, int wordsSize) {
    int retVal = 0;

    int wordiSize, wordjSize;
    int i, j;
    for (i = 0; i < wordsSize; ++i) {
        for (j = i + 1; j < wordsSize; ++j) {
            wordiSize = strlen(words[i]);
            wordjSize = strlen(words[j]);
            if (wordiSize > wordjSize) {
                continue;
            }

            if (strncmp(words[j], words[i], wordiSize) != 0) {
                continue;
            }
            if (strncmp(words[j] + (wordjSize - wordiSize), words[i], wordiSize) != 0) {
                continue;
            }

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
    int countPrefixSuffixPairs(vector<string>& words) {
        int retVal = 0;

        int wordsSize = words.size();
        for (int i = 0; i < wordsSize; ++i) {
            for (int j = i + 1; j < wordsSize; ++j) {
                string str1 = words[i];
                string str2 = words[j];
                if (str1.size() > str2.size()) {
                    continue;
                }

                if ((str2.find(str1) == 0) && (str2.rfind(str1) == str2.size() - str1.size())) {
                    ++retVal;
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
    def countPrefixSuffixPairs(self, words: List[str]) -> int:
        retVal = 0

        wordsSize = len(words)
        for i in range(wordsSize):
            for j in range(i + 1, wordsSize):
                str1 = words[i]
                str2 = words[j]
                if len(str1) > len(str2):
                    continue

                if (str2.startswith(str1)) and (str2.endswith(str1)):
                    retVal += 1

        return retVal
```

</details>

## [3110. Score of a String](https://leetcode.com/problems/score-of-a-string/)  1152

- [Official](https://leetcode.com/problems/score-of-a-string/editorial/)

<details><summary>Description</summary>

```text
You are given a string s.
The score of a string is defined as the sum of the absolute difference between the ASCII values of adjacent characters.

Return the score of s.

Example 1:
Input: s = "hello"
Output: 13
Explanation:
The ASCII values of the characters in s are: 'h' = 104, 'e' = 101, 'l' = 108, 'o' = 111.
So, the score of s would be |104 - 101| + |101 - 108| + |108 - 108| + |108 - 111| = 3 + 7 + 0 + 3 = 13.

Example 2:
Input: s = "zaz"
Output: 50
Explanation:
The ASCII values of the characters in s are: 'z' = 122, 'a' = 97.
So, the score of s would be |122 - 97| + |97 - 122| = 25 + 25 = 50.

Constraints:
2 <= s.length <= 100
s consists only of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Sum the difference between all the adjacent characters by just taking the absolute difference of their ASCII values.
```

</details>

</details>

<details><summary>C</summary>

```c
int scoreOfString(char* s) {
    int retVal = 0;

    int sSize = strlen(s);
    int i;
    for (i = 1; i < sSize; ++i) {
        retVal += abs(s[i - 1] - s[i]);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int scoreOfString(string s) {
        int retVal = 0;

        int sSize = s.size();
        for (int i = 1; i < sSize; ++i) {
            retVal += abs(s[i - 1] - s[i]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def scoreOfString(self, s: str) -> int:
        retVal = 0

        sSize = len(s)
        for i in range(1, sSize):
            retVal += abs(ord(s[i-1]) - ord(s[i]))

        return retVal
```

</details>

## [3136. Valid Word](https://leetcode.com/problems/valid-word/)  1249

- [Official](https://leetcode.com/problems/valid-word/editorial/)
- [Official](https://leetcode.cn/problems/valid-word/solutions/3717148/you-xiao-dan-ci-by-leetcode-solution-qege/)

<details><summary>Description</summary>

```text
A word is considered valid if:
- It contains a minimum of 3 characters.
- It contains only digits (0-9), and English letters (uppercase and lowercase).
- It includes at least one vowel.
- It includes at least one consonant.

You are given a string word.

Return true if word is valid, otherwise, return false.

Notes:
- 'a', 'e', 'i', 'o', 'u', and their uppercases are vowels.
- A consonant is an English letter that is not a vowel.

Example 1:
Input: word = "234Adas"
Output: true
Explanation:
This word satisfies the conditions.

Example 2:
Input: word = "b3"
Output: false
Explanation:
The length of this word is fewer than 3, and does not have a vowel.

Example 3:
Input: word = "a3$e"
Output: false
Explanation:
This word contains a '$' character and does not have a consonant.

Constraints:
1 <= word.length <= 20
word consists of English uppercase and lowercase letters, digits, '@', '#', and '$'.
```

<details><summary>Hint</summary>

```text
1. Use if-else to check all the conditions.
```

</details>

</details>

<details><summary>C</summary>

```c
bool isValid(char* word) {
    bool retVal = false;

    int wordSize = strlen(word);
    if (wordSize < 3) {
        return retVal;
    }

    bool hasVowel = false;
    bool hasConsonant = false;
    for (int i = 0; i < wordSize; ++i) {
        char c = word[i];
        if (isalpha(c)) {
            c = tolower(c);
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                hasVowel = true;
            } else {
                hasConsonant = true;
            }
        } else if (isdigit(c)) {
            continue;
        } else {
            return retVal;
        }
    }
    retVal = hasVowel && hasConsonant;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    bool isValid(string word) {
        bool retVal = false;

        int wordSize = word.size();
        if (wordSize < 3) {
            return retVal;
        }

        bool hasVowel = false;
        bool hasConsonant = false;
        for (char c : word) {
            if (isalpha(c)) {
                c = tolower(c);
                if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                    hasVowel = true;
                } else {
                    hasConsonant = true;
                }
            } else if (isdigit(c)) {
                continue;
            } else {
                return retVal;
            }
        }
        retVal = hasVowel && hasConsonant;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def isValid(self, word: str) -> bool:
        retVal = False

        wordSize = len(word)
        if wordSize < 3:
            return retVal

        hasVowel = False
        hasConsonant = False
        for c in word:
            if c.isalpha():
                if c.lower() in "aeiou":
                    hasVowel = True
                else:
                    hasConsonant = True
            elif c.isdigit():
                continue
            else:
                return retVal
        retVal = hasVowel and hasConsonant

        return retVal
```

</details>

## [3163. String Compression III](https://leetcode.com/problems/string-compression-iii/)  2697

- [Official](https://leetcode.com/problems/string-compression-iii/editorial/)

<details><summary>Description</summary>

```text
Given a string word, compress it using the following algorithm:
- Begin with an empty string comp. While word is not empty, use the following operation:
  - Remove a maximum length prefix of word made of a single character c repeating at most 9 times.
  - Append the length of the prefix followed by c to comp.

Return the string comp.

Example 1:
Input: word = "abcde"
Output: "1a1b1c1d1e"
Explanation:
Initially, comp = "".
Apply the operation 5 times, choosing "a", "b", "c", "d", and "e" as the prefix in each operation.
For each prefix, append "1" followed by the character to comp.

Example 2:
Input: word = "aaaaaaaaaaaaaabb"
Output: "9a5a2b"
Explanation:
Initially, comp = "".
Apply the operation 3 times, choosing "aaaaaaaaa", "aaaaa", and "bb" as the prefix in each operation.
For prefix "aaaaaaaaa", append "9" followed by "a" to comp.
For prefix "aaaaa", append "5" followed by "a" to comp.
For prefix "bb", append "2" followed by "b" to comp.

Constraints:
1 <= word.length <= 2 * 10^5
word consists only of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Each time, just cut the same character in prefix up to at max 9 times. It’s always better to cut a bigger prefix.
```

</details>

</details>

<details><summary>C</summary>

```c
char* compressedString(char* word) {
    char* pRetVal = NULL;

    int wordSize = strlen(word);
    int retValSize = 2 * wordSize + 1;
    pRetVal = (char*)malloc(retValSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (retValSize * sizeof(char)));

    int idx = 0;
    int count = 1;
    int i;
    for (i = 1; i < wordSize; ++i) {
        if ((word[i] == word[i - 1]) && (count < 9)) {
            count++;
            continue;
        }
        idx += snprintf(pRetVal + idx, retValSize - idx, "%d%c", count, word[i - 1]);
        count = 1;
    }
    idx += snprintf(pRetVal + idx, retValSize - idx, "%d%c", count, word[wordSize - 1]);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string compressedString(string word) {
        string retVal;

        int wordSize = word.size();

        int count = 1;
        for (int i = 1; i < wordSize; ++i) {
            if ((word[i] == word[i - 1]) && (count < 9)) {
                count++;
                continue;
            }
            retVal += (to_string(count) + word[i - 1]);
            count = 1;
        }
        retVal += (to_string(count) + word[wordSize - 1]);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def compressedString(self, word: str) -> str:
        retVal = ""

        wordSize = len(word)

        count = 1
        for i in range(1, wordSize):
            if (word[i] == word[i-1]) and (count < 9):
                count += 1
                continue
            retVal += (str(count) + word[i-1])
            count = 1
        retVal += (str(count) + word[wordSize-1])

        return retVal
```

</details>

## [3223. Minimum Length of String After Operations](https://leetcode.com/problems/minimum-length-of-string-after-operations/)  1445

- [Official](https://leetcode.com/problems/minimum-length-of-string-after-operations/editorial/)

<details><summary>Description</summary>

```text
You are given a string s.

You can perform the following process on s any number of times:
- Choose an index i in the string such that
  there is at least one character to the left of index i that is equal to s[i],
  and at least one character to the right that is also equal to s[i].
- Delete the closest character to the left of index i that is equal to s[i].
- Delete the closest character to the right of index i that is equal to s[i].

Return the minimum length of the final string s that you can achieve.

Example 1:
Input: s = "abaacbcbb"
Output: 5
Explanation:
We do the following operations:
Choose index 2, then remove the characters at indices 0 and 3. The resulting string is s = "bacbcbb".
Choose index 3, then remove the characters at indices 0 and 5. The resulting string is s = "acbcb".

Example 2:
Input: s = "aa"
Output: 2
Explanation:
We cannot perform any operations, so we return the length of the original string.

Constraints:
1 <= s.length <= 2 * 10^5
s consists only of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Only the frequency of each character matters in finding the final answer.
2. If a character occurs less than 3 times, we cannot perform any process with it.
3. Suppose there is a character that occurs at least 3 times in the string,
   we can repeatedly delete two of these characters until there are at most 2 occurrences left of it.
```

</details>

</details>

<details><summary>C</summary>

```c
int minimumLength(char* s) {
    int retVal = 0;

#define MAX_LETTTER (26)  // s consists only of lowercase English letters.
    int charFrequency[MAX_LETTTER];
    memset(charFrequency, 0, sizeof(charFrequency));

    int sSize = strlen(s);
    for (int i = 0; i < sSize; ++i) {
        charFrequency[s[i] - 'a']++;
    }

    for (int i = 0; i < MAX_LETTTER; ++i) {
        if (charFrequency[i] == 0) {
            continue;
        }

        if (charFrequency[i] % 2 == 0) {
            retVal += 2;
        } else {
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
    int minimumLength(string s) {
        int retVal = 0;

        vector<int> charFrequency(26, 0);  // s consists only of lowercase English letters.
        for (char currentChar : s) {
            charFrequency[currentChar - 'a']++;
        }

        for (int frequency : charFrequency) {
            if (frequency == 0) {
                continue;
            }

            if (frequency % 2 == 0) {
                retVal += 2;
            } else {
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
    def minimumLength(self, s: str) -> int:
        retVal = 0

        # s consists only of lowercase English letters.
        charFrequency = [0] * 26
        for current_char in s:
            charFrequency[ord(current_char) - ord("a")] += 1

        for frequency in charFrequency:
            if frequency == 0:
                continue

            if frequency % 2 == 0:
                retVal += 2
            else:
                retVal += 1

        return retVal
```

</details>

## [3330. Find the Original Typed String I](https://leetcode.com/problems/find-the-original-typed-string-i/)  1338

- [Official](https://leetcode.com/problems/find-the-original-typed-string-i/editorial/)
- [Official](https://leetcode.cn/problems/find-the-original-typed-string-i/solutions/3706276/zhao-dao-chu-shi-shu-ru-zi-fu-chuan-i-by-y2ve/)

<details><summary>Description</summary>

```text
Alice is attempting to type a specific string on her computer.
However, she tends to be clumsy and may press a key for too long, resulting in a character being typed multiple times.

Although Alice tried to focus on her typing, she is aware that she may still have done this at most once.

You are given a string word, which represents the final output displayed on Alice's screen.

Return the total number of possible original strings that Alice might have intended to type.

Example 1:
Input: word = "abbcccc"
Output: 5
Explanation:
The possible strings are: "abbcccc", "abbccc", "abbcc", "abbc", and "abcccc".

Example 2:
Input: word = "abcd"
Output: 1
Explanation:
The only possible string is "abcd".

Example 3:
Input: word = "aaaa"
Output: 4

Constraints:
1 <= word.length <= 100
word consists only of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Any group of consecutive characters might have been the mistake.
```

</details>

</details>

<details><summary>C</summary>

```c
int possibleStringCount(char* word) {
    int retVal = 1;

    int wordSize = strlen(word);
    for (int i = 1; i < wordSize; ++i) {
        if (word[i - 1] == word[i]) {
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
    int possibleStringCount(string word) {
        int retVal = 1;

        int wordSize = word.size();
        for (int i = 1; i < wordSize; ++i) {
            if (word[i - 1] == word[i]) {
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
    def possibleStringCount(self, word: str) -> int:
        retVal = 1

        wordSize = len(word)
        for i in range(1, wordSize):
            if word[i-1] == word[i]:
                retVal += 1

        return retVal
```

</details>
