# String

## [1108. Defanging an IP Address](https://leetcode.com/problems/defanging-an-ip-address/)  1084

- [Official](https://leetcode.cn/problems/defanging-an-ip-address/solutions/1612962/ip-di-zhi-wu-xiao-hua-by-leetcode-soluti-7q15/)

<details><summary>Description</summary>

```text
Given a valid (IPv4) IP address, return a defanged version of that IP address.

A defanged IP address replaces every period "." with "[.]".

Example 1:
Input: address = "1.1.1.1"
Output: "1[.]1[.]1[.]1"

Example 2:
Input: address = "255.100.50.0"
Output: "255[.]100[.]50[.]0"

Constraints:
The given address is a valid IPv4 address.
```

</details>

<details><summary>C</summary>

```c
char* defangIPaddr(char* address) {
    char* pRetVal = NULL;

    int len = strlen(address);
    int returnSize = len + 3 * 2 + 1;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, returnSize * sizeof(char));

#if (1)
    printf("for\n");

    int idx = 0;
    int i;
    for (i = 0; i < len; ++i) {
        if (address[i] == '.') {
            pRetVal[idx++] = '[';
            pRetVal[idx++] = '.';
            pRetVal[idx++] = ']';
        } else {
            pRetVal[idx++] = address[i];
        }
    }
#else
    printf("sscanf\n");

    int ip1, ip2, ip3, ip4;
    sscanf(address, "%d.%d.%d.%d", &ip1, &ip2, &ip3, &ip4);
    snprintf(pRetVal, returnSize * sizeof(char), "%d[.]%d[.]%d[.]%d", ip1, ip2, ip3, ip4);
#endif

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string defangIPaddr(string address) {
        string retVal;

        for (auto c : address) {
            if (c == '.') {
                retVal += "[.]";
            } else {
                retVal += c;
            }
        }

        return retVal;
    }
};
```

</details>

## [1138. Alphabet Board Path](https://leetcode.com/problems/alphabet-board-path/)  1410

- [Official](https://leetcode.cn/problems/alphabet-board-path/solutions/2105828/zi-mu-ban-shang-de-lu-jing-by-leetcode-s-c30t/)

<details><summary>Description</summary>

```text
On an alphabet board, we start at position (0, 0), corresponding to character board[0][0].

Here, board = ["abcde", "fghij", "klmno", "pqrst", "uvwxy", "z"], as shown in the diagram below.
+-------------------+
| a | b | c | d | e |
|-------------------|
| f | g | h | i | k |
|-------------------|
| k | l | m | n | o |
|-------------------|
| p | q | r | s | t |
|-------------------|
| u | v | w | x | y |
|-------------------+
| z |
+---+

We may make the following moves:
- 'U' moves our position up one row, if the position exists on the board;
- 'D' moves our position down one row, if the position exists on the board;
- 'L' moves our position left one column, if the position exists on the board;
- 'R' moves our position right one column, if the position exists on the board;
- '!' adds the character board[r][c] at our current position (r, c) to the answer.
(Here, the only positions that exist on the board are positions with letters on them.)

Return a sequence of moves that makes our answer equal to target in the minimum number of moves.
You may return any path that does so.

Example 1:
Input: target = "leet"
Output: "DDR!UURRR!!DDD!"

Example 2:
Input: target = "code"
Output: "RR!DDRR!UUL!R!"

Constraints:
1 <= target.length <= 100
target consists only of English lowercase letters.
```

<details><summary>Hint</summary>

```text
1. Create a hashmap from letter to position on the board.
2. Now for each letter, try moving there in steps, where at each step you check if it is inside the boundaries of the board.
```

</details>

</details>

<details><summary>C</summary>

```c
char* alphabetBoardPath(char* target) {
    char* pRetVal = NULL;

    int len = strlen(target);
    pRetVal = (char*)calloc(10 * len, sizeof(char));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }
    int idx = 0;

    int src[2];
    memset(src, 0, sizeof(src));
    int dest[2];
    memset(dest, 0, sizeof(dest));
    int row, col, move;
    int i;
    for (i = 0; i < len; ++i) {
        dest[0] = (target[i] - 'a') / 5;
        dest[1] = (target[i] - 'a') % 5;

        row = dest[0] - src[0];
        col = dest[1] - src[1];

        /* Because Address of 'z'
         *  Notice that moving down and moving right, may move into a square that doesn't exist.
         *  To avoid this, we put L U before R D.
         *
         *  You may return any path that does so.
         */
        if (row < 0) {
            for (move = 0; move < abs(row); ++move) {
                pRetVal[idx++] = 'U';
            }
        }
        if (col < 0) {
            for (move = 0; move < abs(col); ++move) {
                pRetVal[idx++] = 'L';
            }
        }
        if (row > 0) {
            for (move = 0; move < abs(row); ++move) {
                pRetVal[idx++] = 'D';
            }
        }
        if (col > 0) {
            for (move = 0; move < abs(col); ++move) {
                pRetVal[idx++] = 'R';
            }
        }
        pRetVal[idx++] = '!';

        memcpy(src, dest, sizeof(src));
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string alphabetBoardPath(string target) {
        string retVal;

        vector<int> src(2, 0);
        vector<int> dest(2, 0);
        for (auto c : target) {
            dest[0] = (c - 'a') / 5;
            dest[1] = (c - 'a') % 5;

            int rowMove = dest[0] - src[0];
            int colMove = dest[1] - src[1];

            /* Because Address of 'z'
             *  Notice that moving down and moving right, may move into a square that doesn't exist.
             *  To avoid this, we put L U before R D.
             *
             *  You may return any path that does so.
             */
            if (rowMove < 0) {
                retVal += string(-rowMove, 'U');
            }
            if (colMove < 0) {
                retVal += string(-colMove, 'L');
            }
            if (rowMove > 0) {
                retVal += string(rowMove, 'D');
            }
            if (colMove > 0) {
                retVal += string(colMove, 'R');
            }
            retVal += '!';

            src = dest;
        }

        return retVal;
    }
};
```

</details>

## [1309. Decrypt String from Alphabet to Integer Mapping](https://leetcode.com/problems/decrypt-string-from-alphabet-to-integer-mapping/)  1257

<details><summary>Description</summary>

```text
You are given a string s formed by digits and '#'. We want to map s to English lowercase characters as follows:
- Characters ('a' to 'i') are represented by ('1' to '9') respectively.
- Characters ('j' to 'z') are represented by ('10#' to '26#') respectively.
Return the string formed after mapping.

The test cases are generated so that a unique mapping will always exist.

Example 1:
Input: s = "10#11#12"
Output: "jkab"
Explanation: "j" -> "10#" , "k" -> "11#" , "a" -> "1" , "b" -> "2".

Example 2:
Input: s = "1326#"
Output: "acz"

Constraints:
1 <= s.length <= 1000
s consists of digits and the '#' letter.
s will be a valid string such that mapping is always possible.
```

</details>

<details><summary>C</summary>

```c
char* freqAlphabets(char* s) {
    char* pRetVal = s;

    int len = strlen(s);
    int index = 0;
    int i;
    for (i=0; i<len; ++i) {
        if (((i+2) < len) && (s[i+2] == '#')) {
            s[index++] = (10 * (s[i] - '0') + (s[i+1] - '0')) - 1 + 'a';
            i += 2;
        }
        else {
            s[index++] = (s[i] - '0') - 1 + 'a';
        }
    }
    s[index] = 0;

    return pRetVal;
}
```

</details>

## [1328. Break a Palindrome](https://leetcode.com/problems/break-a-palindrome/)  1473

<details><summary>Description</summary>

```text
Given a palindromic string of lowercase English letters palindrome,
replace exactly one character with any lowercase English letter
so that the resulting string is not a palindrome and that it is the lexicographically smallest one possible.

Return the resulting string. If there is no way to replace a character to make it not a palindrome, return an empty string.

A string a is lexicographically smaller than a string b (of the same length) if in the first position where a and b differ,
a has a character strictly smaller than the corresponding character in b.
For example, "abcc" is lexicographically smaller than "abcd"
because the first position they differ is at the fourth character, and 'c' is smaller than 'd'.

Example 1:
Input: palindrome = "abccba"
Output: "aaccba"
Explanation: There are many ways to make "abccba" not a palindrome, such as "zbccba", "aaccba", and "abacba".
Of all the ways, "aaccba" is the lexicographically smallest.

Example 2:
Input: palindrome = "a"
Output: ""
Explanation: There is no way to replace a single character to make "a" not a palindrome, so return an empty string.

Constraints:
1 <= palindrome.length <= 1000
palindrome consists of only lowercase English letters.
```

</details>

<details><summary>C</summary>

```c
char * breakPalindrome(char * palindrome){
    char* pRetVal = "";

    int len = strlen(palindrome);
    // There is no way to replace a single character
    if (len == 1)
    {
        return pRetVal;
    }

    int head = 0;
    int tail = len - 1;
    while (head < tail)
    {
        // replace first to lexicographically smallest
        if (*(palindrome+head) != 'a')
        {
            *(palindrome+head) = 'a';
            break;
        }
        ++head;
        --tail;
    }
    // update last character to lexicographically smallest
    if (head >= tail)
    {
        *(palindrome + len - 1) = 'b';
    }
    pRetVal = palindrome;

    return pRetVal;
}
```

</details>

## [1400. Construct K Palindrome Strings](https://leetcode.com/problems/construct-k-palindrome-strings/)  1530

- [Official](https://leetcode.com/problems/construct-k-palindrome-strings/editorial/)
- [Official](https://leetcode.cn/problems/construct-k-palindrome-strings/solutions/198217/gou-zao-k-ge-hui-wen-zi-fu-chuan-by-leetcode-solut/)

<details><summary>Description</summary>

```text
Given a string s and an integer k,
return true if you can use all the characters in s to construct k palindrome strings or false otherwise.

Example 1:
Input: s = "annabelle", k = 2
Output: true
Explanation: You can construct two palindromes using all characters in s.
Some possible constructions "anna" + "elble", "anbna" + "elle", "anellena" + "b"

Example 2:
Input: s = "leetcode", k = 3
Output: false
Explanation: It is impossible to construct 3 palindromes using all the characters of s.

Example 3:
Input: s = "true", k = 4
Output: true
Explanation: The only possible solution is to put each character in a separate string.

Constraints:
1 <= s.length <= 10^5
s consists of lowercase English letters.
1 <= k <= 10^5
```

<details><summary>Hint</summary>

```text
1. If the s.length < k we cannot construct k strings from s and answer is false.
2. If the number of characters that have odd counts is > k
   then the minimum number of palindrome strings we can construct is > k and answer is false.
3. Otherwise you can construct exactly k palindrome strings and answer is true (why ?).
```

</details>

</details>

<details><summary>C</summary>

```c
bool canConstruct(char* s, int k) {
    bool retVal = false;

    int sSize = strlen(s);
    if (sSize < k) {
        return retVal;
    } else if (sSize == k) {
        retVal = true;
        return retVal;
    }

    int frequencySize = 26;  // s consists of lowercase English letters.
    int frequency[frequencySize];
    memset(frequency, 0, sizeof(frequency));
    for (int i = 0; i < sSize; ++i) {
        frequency[s[i] - 'a']++;
    }

    int oddCount = 0;
    for (int i = 0; i < frequencySize; ++i) {
        if (frequency[i] % 2 == 1) {
            oddCount++;
        }
    }

    if (oddCount <= k) {
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
    bool canConstruct(string s, int k) {
        int retVal = false;

        int sSize = s.size();
        if (sSize < k) {
            return retVal;
        } else if (sSize == k) {
            retVal = true;
            return retVal;
        }

        vector<int> frequency(26, 0);  // s consists of lowercase English letters.
        for (auto& chr : s) {
            frequency[chr - 'a']++;
        }

        int oddCount = 0;
        for (auto count : frequency) {
            if (count % 2 == 1) {
                oddCount++;
            }
        }

        if (oddCount <= k) {
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
    def canConstruct(self, s: str, k: int) -> bool:
        retVal = False

        sSize = len(s)
        if sSize < k:
            return retVal
        elif sSize == k:
            retVal = True
            return retVal

        frequency = [0] * 26  # s consists of lowercase English letters.
        for c in s:
            frequency[ord(c) - ord("a")] += 1

        oddCount = 0
        for count in frequency:
            if count % 2 == 1:
                oddCount += 1

        if oddCount <= k:
            retVal = True

        return retVal
```

</details>

## [1408. String Matching in an Array](https://leetcode.com/problems/string-matching-in-an-array/)  1223

- [Official](https://leetcode.com/problems/string-matching-in-an-array/editorial/)
- [Official](https://leetcode.cn/problems/string-matching-in-an-array/solutions/1723228/shu-zu-zhong-de-zi-fu-chuan-pi-pei-by-le-rpmt/)

<details><summary>Description</summary>

```text
Given an array of string words, return all strings in words that is a substring of another word.
You can return the answer in any order.

A substring is a contiguous sequence of characters within a string

Example 1:
Input: words = ["mass","as","hero","superhero"]
Output: ["as","hero"]
Explanation: "as" is substring of "mass" and "hero" is substring of "superhero".
["hero","as"] is also a valid answer.

Example 2:
Input: words = ["leetcode","et","code"]
Output: ["et","code"]
Explanation: "et", "code" are substring of "leetcode".

Example 3:
Input: words = ["blue","green","bu"]
Output: []
Explanation: No string of words is substring of another string.

Constraints:
1 <= words.length <= 100
1 <= words[i].length <= 30
words[i] contains only lowercase English letters.
All the strings of words are unique.
```

<details><summary>Hint</summary>

```text
1. Bruteforce to find if one string is substring of another or use KMP algorithm.
```

</details>

</details>

<details><summary>C</summary>

```c
void computeLPSArray(char* substring, int substringSize, int* lps) {
    int length = 0;
    int currentIndex = 1;
    while (currentIndex < substringSize) {
        if (substring[currentIndex] == substring[length]) {
            length++;
            lps[currentIndex] = length;
            currentIndex++;
            continue;
        }

        if (length > 0) {
            length = lps[length - 1];  // Backtrack using LPS array to find a shorter match.
        } else {
            currentIndex++;
        }
    }
}
bool isSubstringOf(char* substring, int substringSize, char* main, int mainSize, int* lps) {
    bool retVal = false;

    int mainIndex = 0;
    int substringIndex = 0;
    while (mainIndex < mainSize) {
        if (main[mainIndex] == substring[substringIndex]) {
            substringIndex++;
            mainIndex++;
            if (substringIndex == substringSize) {
                retVal = true;
                return retVal;
            }
            continue;
        }

        if (substringIndex > 0) {
            substringIndex = lps[substringIndex - 1];  // Use the LPS to skip unnecessary comparisons.
        } else {
            mainIndex++;
        }
    }

    return retVal;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** stringMatching(char** words, int wordsSize, int* returnSize) {
    char** pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (char**)malloc(sizeof(char*) * wordsSize);
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int* pLPS = NULL;
    int currentWordSize, otherWordSize;
    int currentWordIndex, otherWordIndex;
    for (currentWordIndex = 0; currentWordIndex < wordsSize; currentWordIndex++) {
        currentWordSize = strlen(words[currentWordIndex]);
        pLPS = (int*)calloc(currentWordSize, sizeof(int));
        if (pLPS == NULL) {
            perror("calloc");
            return pRetVal;
        }
        computeLPSArray(words[currentWordIndex], currentWordSize, pLPS);

        // Compare the current word with all other words.
        for (otherWordIndex = 0; otherWordIndex < wordsSize; otherWordIndex++) {
            if (currentWordIndex == otherWordIndex) {
                continue;  // Skip comparing the word with itself.
            }

            // Check if the current word is a substring of another word.
            currentWordSize = strlen(words[currentWordIndex]);
            otherWordSize = strlen(words[otherWordIndex]);
            if (isSubstringOf(words[currentWordIndex], currentWordSize, words[otherWordIndex], otherWordSize, pLPS) ==
                true) {
                pRetVal[(*returnSize)++] = words[currentWordIndex];
                break;  // No need to check further for this word.
            }
        }

        free(pLPS);
        pLPS = NULL;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    vector<int> computeLPSArray(string &substring) {
        vector<int> retVal;

        int substringSize = substring.size();
        retVal.assign(substringSize, 0);

        int length = 0;
        int currentIndex = 1;
        while (currentIndex < substringSize) {
            if (substring[currentIndex] == substring[length]) {
                length++;
                retVal[currentIndex] = length;
                currentIndex++;
                continue;
            }

            if (length > 0) {
                length = retVal[length - 1];  // Backtrack using LPS array to find a shorter match.
            } else {
                currentIndex++;
            }
        }

        return retVal;
    }
    bool isSubstringOf(string &substring, string &main, vector<int> &lps) {
        bool retVal = false;

        int mainSize = main.size();
        int substringSize = substring.size();
        int mainIndex = 0;
        int substringIndex = 0;
        while (mainIndex < mainSize) {
            if (main[mainIndex] == substring[substringIndex]) {
                substringIndex++;
                mainIndex++;
                if (substringIndex == substringSize) {
                    retVal = true;
                    return retVal;
                }
                continue;
            }

            if (substringIndex > 0) {
                substringIndex = lps[substringIndex - 1];  // Use the LPS to skip unnecessary comparisons.
            } else {
                mainIndex++;
            }
        }

        return retVal;
    }

   public:
    vector<string> stringMatching(vector<string> &words) {
        vector<string> retVal;

        int wordsSize = words.size();
        for (int currentWordIndex = 0; currentWordIndex < wordsSize; currentWordIndex++) {
            vector<int> lps = computeLPSArray(words[currentWordIndex]);

            // Compare the current word with all other words.
            for (int otherWordIndex = 0; otherWordIndex < wordsSize; otherWordIndex++) {
                if (currentWordIndex == otherWordIndex) {
                    continue;  // Skip comparing the word with itself.
                }

                // Check if the current word is a substring of another word.
                if (isSubstringOf(words[currentWordIndex], words[otherWordIndex], lps) == true) {
                    retVal.emplace_back(words[currentWordIndex]);
                    break;  // No need to check further for this word.
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
    def computeLPSArray(self, substring: str) -> List[int]:
        retVal = []

        substringSize = len(substring)
        retVal = [0] * substringSize

        length = 0
        currentIndex = 1
        while currentIndex < substringSize:
            if substring[currentIndex] == substring[length]:
                length += 1
                retVal[currentIndex] = length
                currentIndex += 1
                continue

            if length > 0:  # Backtrack using Longest Prefix Suffix Array to find a shorter match.
                length = retVal[length - 1]
            else:
                currentIndex += 1

        return retVal

    def isSubstringOf(self, substring: str, main: str, lps) -> bool:
        retVal = False

        mainSize = len(main)
        substringSize = len(substring)
        mainIndex = 0
        substringIndex = 0
        while mainIndex < mainSize:
            if main[mainIndex] == substring[substringIndex]:
                mainIndex += 1
                substringIndex += 1
                if substringIndex == substringSize:
                    retVal = True
                    return retVal
                continue

            if substringIndex > 0:
                # Use the Longest Prefix Suffix to skip unnecessary comparisons.
                substringIndex = lps[substringIndex - 1]
            else:
                mainIndex += 1

        return retVal

    def stringMatching(self, words: List[str]) -> List[str]:
        retVal = []

        wordsSize = len(words)
        for currentWordIndex in range(wordsSize):
            lps = self.computeLPSArray(words[currentWordIndex])

            # Compare the current word with all other words.
            for otherWordIndex in range(wordsSize):
                if currentWordIndex == otherWordIndex:
                    continue  # Skip comparing the word with itself.

                # Check if the current word is a substring of another word.
                if self.isSubstringOf(words[currentWordIndex], words[otherWordIndex], lps) == True:
                    retVal.append(words[currentWordIndex])
                    break  # No need to check further for this word.

        return retVal
```

</details>

## [1422. Maximum Score After Splitting a String](https://leetcode.com/problems/maximum-score-after-splitting-a-string/)  1237

- [Official](https://leetcode.com/problems/maximum-score-after-splitting-a-string/editorial/)
- [Official](https://leetcode.cn/problems/maximum-score-after-splitting-a-string/solutions/1743691/fen-ge-zi-fu-chuan-de-zui-da-de-fen-by-l-7u5p/)

<details><summary>Description</summary>

```text
Given a string s of zeros and ones, return the maximum score after splitting the string into two non-empty substrings
(i.e. left substring and right substring).

The score after splitting a string is the number of zeros in the left substring
plus the number of ones in the right substring.

Example 1:
Input: s = "011101"
Output: 5
Explanation:
All possible ways of splitting s into two non-empty substrings are:
left = "0" and right = "11101", score = 1 + 4 = 5
left = "01" and right = "1101", score = 1 + 3 = 4
left = "011" and right = "101", score = 1 + 2 = 3
left = "0111" and right = "01", score = 1 + 1 = 2
left = "01110" and right = "1", score = 2 + 1 = 3

Example 2:
Input: s = "00111"
Output: 5
Explanation: When left = "00" and right = "111", we get the maximum score = 2 + 3 = 5

Example 3:
Input: s = "1111"
Output: 3

Constraints:
2 <= s.length <= 500
The string s consists of characters '0' and '1' only.
```

<details><summary>Hint</summary>

```text
1. Precompute a prefix sum of ones ('1').
2. Iterate from left to right counting the number of zeros ('0'),
   then use the precomputed prefix sum for counting ones ('1').
   Update the answer.
```

</details>

</details>

<details><summary>C</summary>

```c
int maxScore(char* s) {
    int retVal = 0;

    int sSize = strlen(s);
    int i;

    int ones = 0;
    for (i = 0; i < sSize; ++i) {
        if (s[i] == '1') {
            ones++;
        }
    }

    int zeros = 0;
    for (i = 0; i < sSize - 1; ++i) {
        if (s[i] == '0') {
            zeros++;
        } else {
            ones--;
        }

        retVal = fmax(retVal, (zeros + ones));
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxScore(string s) {
        int retVal = 0;

        int sSize = s.size();

        int ones = 0;
        for (int i = 0; i < sSize; ++i) {
            if (s[i] == '1') {
                ones++;
            }
        }

        int zeros = 0;
        for (int i = 0; i < sSize - 1; ++i) {
            if (s[i] == '0') {
                zeros++;
            } else {
                ones--;
            }

            retVal = max(retVal, (zeros + ones));
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxScore(self, s: str) -> int:
        retVal = 0

        sSize = len(s)

        ones = 0
        for i in range(sSize):
            if s[i] == '1':
                ones += 1

        zeros = 0
        for i in range(sSize-1):
            if s[i] == '0':
                zeros += 1
            else:
                ones -= 1

            retVal = max(retVal, (zeros + ones))

        return retVal
```

</details>

## [1455. Check If a Word Occurs As a Prefix of Any Word in a Sentence](https://leetcode.com/problems/check-if-a-word-occurs-as-a-prefix-of-any-word-in-a-sentence/)  1125

- [Official](https://leetcode.com/problems/check-if-a-word-occurs-as-a-prefix-of-any-word-in-a-sentence/editorial/)
- [Official](https://leetcode.cn/problems/check-if-a-word-occurs-as-a-prefix-of-any-word-in-a-sentence/solutions/1761732/jian-cha-dan-ci-shi-fou-wei-ju-zhong-qi-pqpu2/)

<details><summary>Description</summary>

```text
Given a sentence that consists of some words separated by a single space, and a searchWord,
check if searchWord is a prefix of any word in sentence.

Return the index of the word in sentence (1-indexed) where searchWord is a prefix of this word.
If searchWord is a prefix of more than one word, return the index of the first word (minimum index).
If there is no such word return -1.

A prefix of a string s is any leading contiguous substring of s.

Example 1:
Input: sentence = "i love eating burger", searchWord = "burg"
Output: 4
Explanation: "burg" is prefix of "burger" which is the 4th word in the sentence.

Example 2:
Input: sentence = "this problem is an easy problem", searchWord = "pro"
Output: 2
Explanation: "pro" is prefix of "problem" which is the 2nd and the 6th word in the sentence,
but we return 2 as it's the minimal index.

Example 3:
Input: sentence = "i am tired", searchWord = "you"
Output: -1
Explanation: "you" is not a prefix of any word in the sentence.

Constraints:
1 <= sentence.length <= 100
1 <= searchWord.length <= 10
sentence consists of lowercase English letters and spaces.
searchWord consists of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. First extract the words of the sentence.
2. Check for each word if searchWord occurs at index 0, if so return the index of this word (1-indexed)
3. If searchWord doesn't exist as a prefix of any word return the default value (-1).
```

</details>

</details>

<details><summary>C</summary>

```c
int isPrefixOfWord(char* sentence, char* searchWord) {
    int retVal = -1;

    int len = strlen(searchWord);
    int idx = 0;
#define SEPARATED " "
    char* pStr = strtok(sentence, SEPARATED);
    while (pStr != NULL) {
        ++idx;
        if (strncmp(pStr, searchWord, len) == 0) {
            retVal = idx;
            break;
        }

        pStr = strtok(NULL, SEPARATED);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int isPrefixOfWord(string sentence, string searchWord) {
        int retVal = -1;

        int idx = 0;
        int searchWordSize = searchWord.size();
        int searchWordIdx = 0;
        bool startSearch = true;
        for (char c : sentence) {
            if (c == ' ') {
                idx++;
                searchWordIdx = 0;
                startSearch = true;
                continue;
            } else if (startSearch == false) {
                continue;
            }

            if (c == searchWord[searchWordIdx]) {
                searchWordIdx++;
                if (searchWordIdx == searchWordSize) {
                    retVal = idx + 1;
                    break;
                }
            } else {
                searchWordIdx = 0;
                startSearch = false;
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
    def isPrefixOfWord(self, sentence: str, searchWord: str) -> int:
        retVal = -1

        words = sentence.split()
        for idx, word in enumerate(words):
            if word.startswith(searchWord):
                retVal = idx + 1
                break

        return retVal
```

</details>

## [1545. Find Kth Bit in Nth Binary String](https://leetcode.com/problems/find-kth-bit-in-nth-binary-string/)  1479

- [Official](https://leetcode.com/problems/find-kth-bit-in-nth-binary-string/editorial/)
- [Official](https://leetcode.cn/problems/find-kth-bit-in-nth-binary-string/solutions/382517/zhao-chu-di-n-ge-er-jin-zhi-zi-fu-chuan-zhong-de-2/)

<details><summary>Description</summary>

```text
Given two positive integers n and k, the binary string Sn is formed as follows:
- S1 = "0"
- Si = Si - 1 + "1" + reverse(invert(Si - 1)) for i > 1

Where + denotes the concatenation operation, reverse(x) returns the reversed string x,
and invert(x) inverts all the bits in x (0 changes to 1 and 1 changes to 0).

For example, the first four strings in the above sequence are:
- S1 = "0"
- S2 = "011"
- S3 = "0111001"
- S4 = "011100110110001"

Return the kth bit in Sn. It is guaranteed that k is valid for the given n.

Example 1:
Input: n = 3, k = 1
Output: "0"
Explanation: S3 is "0111001".
The 1st bit is "0".

Example 2:
Input: n = 4, k = 11
Output: "1"
Explanation: S4 is "011100110110001".
The 11th bit is "1".

Constraints:
1 <= n <= 20
1 <= k <= 2^n - 1
```

<details><summary>Hint</summary>

```text
1. Since n is small, we can simply simulate the process of constructing S1 to Sn.
```

</details>

</details>

<details><summary>C</summary>

```c
char findKthBit(int n, int k) {
    char retVal = '0';

    if (n == 1) {
        return retVal;
    }

    char correspondingBit;
    int length = 1 << n;
    if (k < length / 2) {
        retVal = findKthBit(n - 1, k);
    } else if (k == length / 2) {
        retVal = '1';
    } else {
        correspondingBit = findKthBit(n - 1, length - k);
        retVal = (correspondingBit == '0') ? '1' : '0';
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    char findKthBit(int n, int k) {
        int retVal = '0';

        if (n == 1) {
            return retVal;
        }

        int length = 1 << n;
        if (k < length / 2) {
            retVal = findKthBit(n - 1, k);
        } else if (k == length / 2) {
            retVal = '1';
        } else {
            char correspondingBit = findKthBit(n - 1, length - k);
            retVal = (correspondingBit == '0') ? '1' : '0';
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def findKthBit(self, n: int, k: int) -> str:
        retVal = '0'

        if n == 1:
            return retVal

        length = 1 << n
        if k < length // 2:
            retVal = self.findKthBit(n - 1, k)
        elif k == length // 2:
            retVal = '1'
        else:
            correspondingBit = self.findKthBit(n - 1, length - k)
            retVal = "1" if correspondingBit == "0" else "0"

        return retVal
```

</details>

## [1678. Goal Parser Interpretation](https://leetcode.com/problems/goal-parser-interpretation/)  1221

<details><summary>Description</summary>

```text
You own a Goal Parser that can interpret a string command.
The command consists of an alphabet of "G", "()" and/or "(al)" in some order.
The Goal Parser will interpret "G" as the string "G", "()" as the string "o", and "(al)" as the string "al".
The interpreted strings are then concatenated in the original order.

Given the string command, return the Goal Parser's interpretation of command.

Example 1:
Input: command = "G()(al)"
Output: "Goal"
Explanation: The Goal Parser interprets the command as follows:
G -> G
() -> o
(al) -> al
The final concatenated result is "Goal".

Example 2:
Input: command = "G()()()()(al)"
Output: "Gooooal"

Example 3:
Input: command = "(al)G(al)()()G"
Output: "alGalooG"

Constraints:
1 <= command.length <= 100
command consists of "G", "()", and/or "(al)" in some order.
```

</details>

<details><summary>C</summary>

```c
char* interpret(char* command) {
    int idx = 0;
    int i = -1;
    while (command[++i]) {
        if (command[i] == 'G') {
            command[idx++] = 'G';
        }
        else if (command[i] == ')') {
            if (command[i-1] == '(') {
                command[idx++] = 'o';
            }
            else if (command[i-1] == 'l') {
                command[idx++] = 'a';
                command[idx++] = 'l';
            }
        }
    }
    command[idx] = 0;

    return command;
}
```

</details>

## [1704. Determine if String Halves Are Alike](https://leetcode.com/problems/determine-if-string-halves-are-alike/)  1207

- [Official](https://leetcode.cn/problems/determine-if-string-halves-are-alike/solutions/1960619/pan-duan-zi-fu-chuan-de-liang-ban-shi-fo-d21g/)

<details><summary>Description</summary>

```text
You are given a string s of even length. Split this string into two halves of equal lengths,
and let a be the first half and b be the second half.

Two strings are alike if they have the same number of vowels ('a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U').
Notice that s contains uppercase and lowercase letters.

Return true if a and b are alike. Otherwise, return false.

Example 1:
Input: s = "book"
Output: true
Explanation: a = "bo" and b = "ok". a has 1 vowel and b has 1 vowel. Therefore, they are alike.

Example 2:
Input: s = "textbook"
Output: false
Explanation: a = "text" and b = "book". a has 1 vowel whereas b has 2. Therefore, they are not alike.
Notice that the vowel o is counted twice.

Constraints:
2 <= s.length <= 1000
s.length is even.
s consists of uppercase and lowercase letters.
```

<details><summary>Hint</summary>

```text
1. Create a function that checks if a character is a vowel, either uppercase or lowercase.
```

</details>

</details>

<details><summary>C</summary>

```c
bool halvesAreAlike(char* s) {
    bool retVal = true;

    char* vowels = "aeiouAEIOU";

    int count = 0;
    int head = 0;
    int tail = strlen(s) - 1;
    while (head < tail) {
        if (strchr(vowels, s[head])) {
            ++count;
        }
        ++head;

        if (strchr(vowels, s[tail])) {
            --count;
        }
        --tail;
    }

    if (count != 0) {
        retVal = false;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    bool halvesAreAlike(string s) {
        bool retVal = true;

        string vowels = "aeiouAEIOU";

        int count = 0;
        int head = 0;
        int tail = s.size() - 1;
        while (head < tail) {
            if (vowels.find(s[head]) != string::npos) {
                ++count;
            }
            ++head;

            if (vowels.find(s[tail]) != string::npos) {
                --count;
            }
            --tail;
        }

        if (count != 0) {
            retVal = false;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def halvesAreAlike(self, s: str) -> bool:
        retVal = True

        vowels = "aeiouAEIOU"

        count = 0
        head = 0
        tail = len(s) - 1
        while head < tail:
            if s[head] in vowels:
                count += 1
            head += 1

            if s[tail] in vowels:
                count -= 1
            tail -= 1

        if count != 0:
            retVal = False

        return retVal
```

</details>

## [1758. Minimum Changes To Make Alternating Binary String](https://leetcode.com/problems/minimum-changes-to-make-alternating-binary-string/)  1353

- [Official](https://leetcode.com/problems/minimum-changes-to-make-alternating-binary-string/editorial/)
- [Official](https://leetcode.cn/problems/minimum-changes-to-make-alternating-binary-string/solutions/1995159/sheng-cheng-jiao-ti-er-jin-zhi-zi-fu-chu-91c5/)

<details><summary>Description</summary>

```text
You are given a string s consisting only of the characters '0' and '1'.
In one operation, you can change any '0' to '1' or vice versa.

The string is called alternating if no two adjacent characters are equal.
For example, the string "010" is alternating, while the string "0100" is not.

Return the minimum number of operations needed to make s alternating.

Example 1:
Input: s = "0100"
Output: 1
Explanation: If you change the last character to '1', s will be "0101", which is alternating.

Example 2:
Input: s = "10"
Output: 0
Explanation: s is already alternating.

Example 3:
Input: s = "1111"
Output: 2
Explanation: You need two operations to reach "0101" or "1010".

Constraints:
1 <= s.length <= 10^4
s[i] is either '0' or '1'.
```

<details><summary>Hint</summary>

```text
1. Think about how the final string will look like.
2. It will either start with a '0' and be like '010101010..' or with a '1' and be like '10101010..'
3. Try both ways, and check for each way, the number of changes needed to reach it from the given string.
   The answer is the minimum of both ways.
```

</details>

</details>

<details><summary>C</summary>

```c
int minOperations(char* s) {
    int retVal = 0;

    int sSize = strlen(s);
    int i;
    for (i = 0; i < sSize; ++i) {
        if (s[i] != '0' + (i % 2)) {
            ++retVal;
        }
    }
    retVal = fmin(retVal, (sSize - retVal));

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minOperations(string s) {
        int retVal = 0;

        int sSize = s.size();
        for (int i = 0; i < sSize; ++i) {
            if (s[i] != '0' + (i % 2)) {
                ++retVal;
            }
        }
        retVal = min(retVal, (sSize - retVal));

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minOperations(self, s: str) -> int:
        retVal = 0

        sSize = len(s)

        for idx, c in enumerate(s):
            if int(c) != int(idx % 2):
                retVal += 1
        retVal = min(retVal, sSize-retVal)

        return retVal
```

</details>

## [1768. Merge Strings Alternately](https://leetcode.com/problems/merge-strings-alternately/)  1166

- [Official](https://leetcode.cn/problems/merge-strings-alternately/solutions/1913930/jiao-ti-he-bing-zi-fu-chuan-by-leetcode-ac4ih/)

<details><summary>Description</summary>

```text
You are given two strings word1 and word2.
Merge the strings by adding letters in alternating order, starting with word1.
If a string is longer than the other, append the additional letters onto the end of the merged string.

Return the merged string.

Example 1:
Input: word1 = "abc", word2 = "pqr"
Output: "apbqcr"
Explanation: The merged string will be merged as so:
word1:  a   b   c
word2:    p   q   r
merged: a p b q c r

Example 2:
Input: word1 = "ab", word2 = "pqrs"
Output: "apbqrs"
Explanation: Notice that as word2 is longer, "rs" is appended to the end.
word1:  a   b
word2:    p   q   r   s
merged: a p b q   r   s

Example 3:
Input: word1 = "abcd", word2 = "pq"
Output: "apbqcd"
Explanation: Notice that as word1 is longer, "cd" is appended to the end.
word1:  a   b   c   d
word2:    p   q
merged: a p b q c   d

Constraints:
1 <= word1.length, word2.length <= 100
word1 and word2 consist of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Use two pointers, one pointer for each string.
   Alternately choose the character from each pointer, and move the pointer upwards.
```

</details>

</details>

<details><summary>C</summary>

```c
char* mergeAlternately(char* word1, char* word2) {
    char* pRetVal = NULL;

    int len1 = strlen(word1);
    int len2 = strlen(word2);

    int len = len1 + len2 + 1;
    pRetVal = (char*)malloc(len * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (len * sizeof(char)));

    int idx = 0;
    int idx1 = 0;
    int idx2 = 0;
    while ((idx1 < len1) || (idx2 < len2)) {
        if (idx1 < len1) {
            pRetVal[idx++] = word1[idx1++];
        }

        if (idx2 < len2) {
            pRetVal[idx++] = word2[idx2++];
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
    string mergeAlternately(string word1, string word2) {
        string retVal = "";

        int idx1 = 0;
        int word1Size = word1.size();
        int idx2 = 0;
        int word2Size = word2.size();
        while ((idx1 < word1Size) || (idx2 < word2Size)) {
            if (idx1 < word1Size) {
                retVal += word1[idx1++];
            }

            if (idx2 < word2Size) {
                retVal += word2[idx2++];
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
    def mergeAlternately(self, word1: str, word2: str) -> str:
        retVal = ""

        idx1 = 0
        len1 = len(word1)
        idx2 = 0
        len2 = len(word2)
        while idx1 < len1 or idx2 < len2:
            if idx1 < len1:
                retVal += word1[idx1]
                idx1 += 1
            if idx2 < len2:
                retVal += word2[idx2]
                idx2 += 1

        return retVal
```

</details>

## [1790. Check if One String Swap Can Make Strings Equal](https://leetcode.com/problems/check-if-one-string-swap-can-make-strings-equal/)  1300

- [Official](https://leetcode.com/problems/check-if-one-string-swap-can-make-strings-equal/editorial/)
- [Official](https://leetcode.cn/problems/check-if-one-string-swap-can-make-strings-equal/solutions/1881111/jin-zhi-xing-yi-ci-zi-fu-chuan-jiao-huan-j8si/)

<details><summary>Description</summary>

```text
You are given two strings s1 and s2 of equal length.
A string swap is an operation where you choose two indices in a string (not necessarily different)
and swap the characters at these indices.

Return true if it is possible to make both strings equal by performing at most one string swap on exactly one of the strings.
Otherwise, return false.

Example 1:
Input: s1 = "bank", s2 = "kanb"
Output: true
Explanation: For example, swap the first character with the last character of s2 to make "bank".

Example 2:
Input: s1 = "attack", s2 = "defend"
Output: false
Explanation: It is impossible to make them equal with one string swap.

Example 3:
Input: s1 = "kelb", s2 = "kelb"
Output: true
Explanation: The two strings are already equal, so no string swap operation is required.

Constraints:
1 <= s1.length, s2.length <= 100
s1.length == s2.length
s1 and s2 consist of only lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. The answer is false if the number of nonequal positions in the strings is not equal to 0 or 2.
2. Check that these positions have the same set of characters.
```

</details>

</details>

<details><summary>C</summary>

```c
bool areAlmostEqual(char* s1, char* s2) {
    bool retVal = false;

    int s1Size = strlen(s1);
    int count = 0;
    int record[2] = {0};
    for (int i = 0; i < s1Size; ++i) {
        if (s1[i] == s2[i]) {
            continue;
        }
        record[0] |= (1 << (s1[i] - 'a'));
        record[1] |= (1 << (s2[i] - 'a'));
        ++count;
    }

    if (count == 0) {
        retVal = true;
    } else if ((count == 2) && (record[0] == record[1])) {
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
    bool areAlmostEqual(string s1, string s2) {
        bool retVal = false;

        int s1Size = s1.size();
        int count = 0;
        int record[2] = {0};
        for (int i = 0; i < s1Size; ++i) {
            if (s1[i] == s2[i]) {
                continue;
            }
            record[0] |= (1 << (s1[i] - 'a'));
            record[1] |= (1 << (s2[i] - 'a'));
            ++count;
        }

        if (count == 0) {
            retVal = true;
        } else if ((count == 2) && (record[0] == record[1])) {
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
    def areAlmostEqual(self, s1: str, s2: str) -> bool:
        retVal = False

        s1Size = len(s1)
        firstIndexDiff = 0
        secondIndexDiff = 0
        numDiffs = 0
        for i in range(s1Size):
            if s1[i] == s2[i]:
                continue

            numDiffs += 1
            if numDiffs > 2:  # numDiffs is more than 2, one string swap will not make two strings equal
                return retVal
            elif numDiffs == 1:
                firstIndexDiff = i  # store the index of first difference
            else:
                secondIndexDiff = i  # store the index of second difference

        # check if swap is possible
        retVal = (s1[firstIndexDiff] == s2[secondIndexDiff]) and (s1[secondIndexDiff] == s2[firstIndexDiff])

        return retVal
```

</details>

## [1805. Number of Different Integers in a String](https://leetcode.com/problems/number-of-different-integers-in-a-string/)  1333

<details><summary>Description</summary>

```text
You are given a string word that consists of digits and lowercase English letters.

You will replace every non-digit character with a space. For example, "a123bc34d8ef34" will become " 123  34 8  34".
Notice that you are left with some integers that are separated by at least one space: "123", "34", "8", and "34".

Return the number of different integers after performing the replacement operations on word.

Two integers are considered different if their decimal representations without any leading zeros are different.

Example 1:
Input: word = "a123bc34d8ef34"
Output: 3
Explanation: The three different integers are "123", "34", and "8". Notice that "34" is only counted once.

Example 2:

Input: word = "leet1234code234"
Output: 2

Example 3:
Input: word = "a1b01c001"
Output: 1
Explanation: The three integers "1", "01", and "001" all represent the same integer because
the leading zeros are ignored when comparing their decimal values.

Constraints:
1 <= word.length <= 1000
word consists of digits and lowercase English letters.
```

</details>

<details><summary>C</summary>

```c
int numDifferentIntegers(char* word) {
    int retVal = 0;

    int len = strlen(word);
    char Record[len][len];
    memset(Record, 0, sizeof(Record));
    int row = 0;
    int col = 0;

    int i, j;
    for (i = 0; i < len; ++i) {
        if ((word[i] >= '0') && (word[i] <= '9')) {
            // the leading zeros are ignored
            if ((col == 1) && (Record[row][0] == '0')) {
                --col;
            }
            Record[row][col] = word[i];
            ++col;
            continue;
        }
        if (col != 0) {
            ++row;
        }
        col = 0;
    }

    for (i = 0; i < len; ++i) {
        if (strlen(Record[i]) == 0) {
            break;
        }
        ++retVal;

        // check different integers
        for (j = 0; j < i; ++j) {
            if (strcmp(Record[i], Record[j]) == 0) {
                --retVal;
                break;
            }
        }
    }

    return retVal;
}
```

</details>

## [1859. Sorting the Sentence](https://leetcode.com/problems/sorting-the-sentence/)  1290

- [Official](https://leetcode.cn/problems/sorting-the-sentence/solutions/779147/jiang-ju-zi-pai-xu-by-leetcode-solution-wnts/)

<details><summary>Description</summary>

```text
A sentence is a list of words that are separated by a single space with no leading or trailing spaces.
Each word consists of lowercase and uppercase English letters.

A sentence can be shuffled by appending the 1-indexed word position to each word then rearranging the words in the sentence.
- For example, the sentence "This is a sentence" can be shuffled as "sentence4 a3 is2 This1" or "is2 sentence4 This1 a3".
Given a shuffled sentence s containing no more than 9 words, reconstruct and return the original sentence.

Example 1:
Input: s = "is2 sentence4 This1 a3"
Output: "This is a sentence"
Explanation: Sort the words in s to their original positions "This1 is2 a3 sentence4", then remove the numbers.

Example 2:
Input: s = "Myself2 Me1 I4 and3"
Output: "Me Myself and I"
Explanation: Sort the words in s to their original positions "Me1 Myself2 and3 I4", then remove the numbers.

Constraints:
2 <= s.length <= 200
s consists of lowercase and uppercase English letters, spaces, and digits from 1 to 9.
The number of words in s is between 1 and 9.
The words in s are separated by a single space.
s contains no leading or trailing spaces.
```

<details><summary>Hint</summary>

```text
1. Divide the string into the words as an array of strings
2. Sort the words by removing the last character from each word and sorting according to it
```

</details>

</details>

<details><summary>C</summary>

```c
char *sortSentence(char *s) {
    char *pRetVal = NULL;

    int sSize = strlen(s);

    pRetVal = (char *)calloc(sSize + 1, sizeof(char));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }

#define MAX_WORDS (9)  //  The number of words in s is between 1 and 9.
    char buf[MAX_WORDS][sSize];
    memset(buf, 0, sizeof(buf));

    int idx = 0;
    char tmp[sSize];
    memset(tmp, 0, sizeof(tmp));
    int len = 0;
    int i;
    for (i = 0; i < sSize; ++i) {
        if (s[i] == ' ') {
            continue;
        } else if (isdigit(s[i])) {
            idx = (s[i] - '0') - 1;
            snprintf(buf[idx], sSize, "%s", tmp);
            memset(tmp, 0, sizeof(tmp));
            len = 0;
        } else {
            tmp[len++] = s[i];
        }
    }

    idx = 0;
    for (i = 0; i < MAX_WORDS; ++i) {
        if (strlen(buf[i]) == 0) {
            continue;
        }
        idx += snprintf(pRetVal + idx, ((sSize + 1) * sizeof(char)), "%s ", buf[i]);
    }
    pRetVal[strlen(pRetVal) - 1] = '\0';

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string sortSentence(string s) {
        string retVal = "";

        map<int, string> sMap;
        string tmp = "";
        for (auto c : s) {
            if (isdigit(c)) {
                sMap[c - '0'] = tmp;
                tmp = "";
            } else if (c == ' ') {
                continue;
            } else {
                tmp += c;
            }
        }
        for (auto& iter : sMap) {
            retVal += iter.second;
            retVal += ' ';
        }
        retVal.pop_back();

        return retVal;
    }
};
```

</details>

## [1945. Sum of Digits of String After Convert](https://leetcode.com/problems/sum-of-digits-of-string-after-convert/)  1254

<details><summary>Description</summary>

- [Official](https://leetcode.com/problems/sum-of-digits-of-string-after-convert/editorial/)
- [Official](https://leetcode.cn/problems/sum-of-digits-of-string-after-convert/solutions/2019652/zi-fu-chuan-zhuan-hua-hou-de-ge-wei-shu-bhdx4/)

```text
You are given a string s consisting of lowercase English letters, and an integer k.

First, convert s into an integer by replacing each letter with its position in the alphabet
(i.e., replace 'a' with 1, 'b' with 2, ..., 'z' with 26).
Then, transform the integer by replacing it with the sum of its digits.
Repeat the transform operation k times in total.

For example, if s = "zbax" and k = 2, then the resulting integer would be 8 by the following operations:
- Convert: "zbax" ➝ "(26)(2)(1)(24)" ➝ "262124" ➝ 262124
- Transform #1: 262124 ➝ 2 + 6 + 2 + 1 + 2 + 4 ➝ 17
- Transform #2: 17 ➝ 1 + 7 ➝ 8

Return the resulting integer after performing the operations described above.

Example 1:
Input: s = "iiii", k = 1
Output: 36
Explanation: The operations are as follows:
- Convert: "iiii" ➝ "(9)(9)(9)(9)" ➝ "9999" ➝ 9999
- Transform #1: 9999 ➝ 9 + 9 + 9 + 9 ➝ 36
Thus the resulting integer is 36.

Example 2:
Input: s = "leetcode", k = 2
Output: 6
Explanation: The operations are as follows:
- Convert: "leetcode" ➝ "(12)(5)(5)(20)(3)(15)(4)(5)" ➝ "12552031545" ➝ 12552031545
- Transform #1: 12552031545 ➝ 1 + 2 + 5 + 5 + 2 + 0 + 3 + 1 + 5 + 4 + 5 ➝ 33
- Transform #2: 33 ➝ 3 + 3 ➝ 6
Thus the resulting integer is 6.

Example 3:
Input: s = "zbax", k = 2
Output: 8

Constraints:
1 <= s.length <= 100
1 <= k <= 10
s consists of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. First, let's note that after the first transform the value will be at most 100 * 10 which is not much
2. After The first transform, we can just do the rest of the transforms by brute force
```

</details>

</details>

<details><summary>C</summary>

```c
int getLucky(char* s, int k) {
    int retVal = 0;

    int sum = 0;
    int translateToInteger = 0;
    while (*s) {
        translateToInteger = *(s++) - 'a' + 1;
        sum += (translateToInteger % 10);
        sum += (translateToInteger / 10);
    }

    retVal = sum;
    int i;
    for (i = 1; i < k; ++i) {
        retVal = 0;
        while (sum > 0) {
            retVal += (sum % 10);
            sum /= 10;
        }
        sum = retVal;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int getLucky(string s, int k) {
        int retVal = 0;

        int sum = 0;
        for (char c : s) {
            int translateToInteger = c - 'a' + 1;
            sum += (translateToInteger % 10);
            sum += (translateToInteger / 10);
        }

        retVal = sum;
        for (int i = 1; i < k; ++i) {
            retVal = 0;
            while (sum > 0) {
                retVal += (sum % 10);
                sum /= 10;
            }
            sum = retVal;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def getLucky(self, s: str, k: int) -> int:
        retVal = 0

        sum = 0
        for c in s:
            translateToInteger = (ord(c) - ord('a') + 1)
            sum += (translateToInteger % 10)
            sum += (translateToInteger // 10)

        retVal = sum
        for _ in range(1, k):
            retVal = 0
            while sum > 0:
                retVal += (sum % 10)
                sum //= 10
            sum = retVal

        return retVal
```

</details>

## [1957. Delete Characters to Make Fancy String](https://leetcode.com/problems/delete-characters-to-make-fancy-string/)  1357

- [Official](https://leetcode.com/problems/delete-characters-to-make-fancy-string/editorial/)
- [Official](https://leetcode.cn/problems/delete-characters-to-make-fancy-string/)

<details><summary>Description</summary>

```text
A fancy string is a string where no three consecutive characters are equal.

Given a string s, delete the minimum possible number of characters from s to make it fancy.

Return the final string after the deletion. It can be shown that the answer will always be unique.

Example 1:
Input: s = "leeetcode"
Output: "leetcode"
Explanation:
Remove an 'e' from the first group of 'e's to create "leetcode".
No three consecutive characters are equal, so return "leetcode".

Example 2:
Input: s = "aaabaaaa"
Output: "aabaa"
Explanation:
Remove an 'a' from the first group of 'a's to create "aabaaaa".
Remove two 'a's from the second group of 'a's to create "aabaa".
No three consecutive characters are equal, so return "aabaa".

Example 3:
Input: s = "aab"
Output: "aab"
Explanation: No three consecutive characters are equal, so return "aab".

Constraints:
1 <= s.length <= 10^5
s consists only of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. What's the optimal way to delete characters if three or more consecutive characters are equal?
2. If three or more consecutive characters are equal, keep two of them and delete the rest.
```

</details>

</details>

<details><summary>C</summary>

```c
char* makeFancyString(char* s) {
    char* pRetVal = NULL;

    int sSize = strlen(s) + 1;

    pRetVal = (char*)malloc(sSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (sSize * sizeof(char)));
    int returnSize = 0;

    int i;
    for (i = 0; i < sSize; ++i) {
        if ((returnSize >= 2) && (pRetVal[returnSize - 1] == s[i]) && (pRetVal[returnSize - 2] == s[i])) {
            continue;
        }
        pRetVal[returnSize++] = s[i];
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string makeFancyString(string s) {
        string retVal;

        for (char c : s) {
            int retValSize = retVal.size();
            if ((retValSize >= 2) && (retVal[retValSize - 1] == c) && (retVal[retValSize - 2] == c)) {
                continue;
            }
            retVal += c;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def makeFancyString(self, s: str) -> str:
        retVal = ""

        for c in s:
            retValSize = len(retVal)
            if (retValSize >= 2) and (c == retVal[-1]) and (c == retVal[-2]):
                continue
            retVal += c

        return retVal
```

</details>
