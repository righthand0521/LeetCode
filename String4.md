# String

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
