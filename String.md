# String

## [6. Zigzag Conversion](https://leetcode.com/problems/zigzag-conversion/)

- [Official](https://leetcode.cn/problems/zigzag-conversion/solutions/1298127/z-zi-xing-bian-huan-by-leetcode-solution-4n3u/)

<details><summary>Description</summary>

```text
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this:
(you may want to display this pattern in a fixed font for better legibility)
P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:
string convert(string s, int numRows);

Example 1:
Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"

Example 2:
Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:
P     I    N
A   L S  I G
Y A   H R
P     I

Example 3:
Input: s = "A", numRows = 1
Output: "A"

Constraints:
1 <= s.length <= 1000
s consists of English letters (lower-case and upper-case), ',' and '.'.
1 <= numRows <= 1000
```

</details>

<details><summary>C</summary>

```c
char* convert(char* s, int numRows) {
    char* pRetVal = NULL;

    int len = strlen(s);

    int returnSize = len + 1;
    pRetVal = (char*)calloc(returnSize, sizeof(char));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }

    if (numRows == 1) {
        memcpy(pRetVal, s, returnSize * sizeof(char));
        return pRetVal;
    }

    /* numRows - 1 + numRows - 1 = 2 x numRows - 2 = 2 x (numRows - 1)
     *
     *  n = 3: 2x(3-1) = 4
     *  +-------+-------+----+
     *  | 0 |   | 4 |   | 8  |
     *  | 1 | 3 | 5 | 7 | 9  | ...
     *  | 2 |   | 6 |   | 10 |
     *  +-------+-------+----+
     *
     *  n = 4: 2x(4-1) = 6
     *  +-----------+-------------+----+
     *  | 0 |   |   | 6 |    |    | 12 |
     *  | 1 |   | 5 | 7 |    | 11 | 13 | ...
     *  | 2 | 4 |   | 8 | 10 |    | 14 |
     *  | 3 |   |   | 9 |    |    | 15 |
     *  +-----------+-------------+----+
     *
     *  n = 5: 2x(5-1) = 8
     *  +---------------+-------------------+----+
     *  | 0 |   |   |   |  8 |    |    |    | 16 |
     *  | 1 |   |   | 7 |  9 |    |    | 15 | 17 |
     *  | 2 |   | 6 |   | 10 |    | 14 |    | 18 | ...
     *  | 3 | 5 |   |   | 11 | 13 |    |    | 19 |
     *  | 4 |   |   |   | 12 |    |    |    | 20 |
     *  +---------------+-------------------+----+
     */
    int charsInSection = 2 * (numRows - 1);

    int returnIdx = 0;
    int sIdx, innerIdx;
    int row;
    for (row = 0; row < numRows; ++row) {
        sIdx = row;

        while (sIdx < len) {
            pRetVal[returnIdx++] = s[sIdx];

            if ((row != 0) && (row != numRows - 1)) {
                innerIdx = sIdx + charsInSection - (2 * row);
                if (innerIdx < len) {
                    pRetVal[returnIdx++] = s[innerIdx];
                }
            }

            sIdx += charsInSection;
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
    string convert(string s, int numRows) {
        string retVal;

        if (numRows == 1) {
            retVal = s;
            return retVal;
        }

        /* numRows - 1 + numRows - 1 = 2 x numRows - 2 = 2 x (numRows - 1)
         *
         *  n = 3: 2x(3-1) = 4
         *  +-------+-------+----+
         *  | 0 |   | 4 |   | 8  |
         *  | 1 | 3 | 5 | 7 | 9  | ...
         *  | 2 |   | 6 |   | 10 |
         *  +-------+-------+----+
         *
         *  n = 4: 2x(4-1) = 6
         *  +-----------+-------------+----+
         *  | 0 |   |   | 6 |    |    | 12 |
         *  | 1 |   | 5 | 7 |    | 11 | 13 | ...
         *  | 2 | 4 |   | 8 | 10 |    | 14 |
         *  | 3 |   |   | 9 |    |    | 15 |
         *  +-----------+-------------+----+
         *
         *  n = 5: 2x(5-1) = 8
         *  +---------------+-------------------+----+
         *  | 0 |   |   |   |  8 |    |    |    | 16 |
         *  | 1 |   |   | 7 |  9 |    |    | 15 | 17 |
         *  | 2 |   | 6 |   | 10 |    | 14 |    | 18 | ...
         *  | 3 | 5 |   |   | 11 | 13 |    |    | 19 |
         *  | 4 |   |   |   | 12 |    |    |    | 20 |
         *  +---------------+-------------------+----+
         */
        int len = s.length();
        int charsInSection = 2 * (numRows - 1);
        for (int currRow = 0; currRow < numRows; ++currRow) {
            int index = currRow;
            while (index < len) {
                retVal += s[index];

                // If currRow is not the first or last row then we have to add one more character of current section.
                if ((currRow != 0) && (currRow != numRows - 1)) {
                    int charsInBetween = charsInSection - 2 * currRow;
                    int secondIndex = index + charsInBetween;
                    if (secondIndex < len) {
                        retVal += s[secondIndex];
                    }
                }

                // Jump to same row's first character of next section.
                index += charsInSection;
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
    def convert(self, s: str, numRows: int) -> str:
        retVal = ""

        if numRows == 1:
            retVal = s
            return retVal

        # /* numRows - 1 + numRows - 1 = 2 x numRows - 2 = 2 x (numRows - 1)
        #  *
        #  *  n = 3: 2x(3-1) = 4
        #  *  +-------+-------+----+
        #  *  | 0 |   | 4 |   | 8  |
        #  *  | 1 | 3 | 5 | 7 | 9  | ...
        #  *  | 2 |   | 6 |   | 10 |
        #  *  +-------+-------+----+
        #  *
        #  *  n = 4: 2x(4-1) = 6
        #  *  +-----------+-------------+----+
        #  *  | 0 |   |   | 6 |    |    | 12 |
        #  *  | 1 |   | 5 | 7 |    | 11 | 13 | ...
        #  *  | 2 | 4 |   | 8 | 10 |    | 14 |
        #  *  | 3 |   |   | 9 |    |    | 15 |
        #  *  +-----------+-------------+----+
        #  *
        #  *  n = 5: 2x(5-1) = 8
        #  *  +---------------+-------------------+----+
        #  *  | 0 |   |   |   |  8 |    |    |    | 16 |
        #  *  | 1 |   |   | 7 |  9 |    |    | 15 | 17 |
        #  *  | 2 |   | 6 |   | 10 |    | 14 |    | 18 | ...
        #  *  | 3 | 5 |   |   | 11 | 13 |    |    | 19 |
        #  *  | 4 |   |   |   | 12 |    |    |    | 20 |
        #  *  +---------------+-------------------+----+
        #  */
        sSize = len(s)
        charsInSection = 2 * (numRows - 1)
        for currRow in range(numRows):
            index = currRow
            while index < sSize:
                retVal += s[index]

                # // If currRow is not the first or last row then we have to add one more character of current section.
                if (currRow != 0) and (currRow != numRows - 1):
                    charsInBetween = charsInSection - 2 * currRow
                    secondIndex = index + charsInBetween
                    if secondIndex < sSize:
                        retVal += s[secondIndex]

                # // Jump to same row's first character of next section.
                index += charsInSection

        return retVal
```

</details>

## [8. String to Integer (atoi)](https://leetcode.com/problems/string-to-integer-atoi/)

- [Official](https://leetcode.cn/problems/string-to-integer-atoi/solutions/183164/zi-fu-chuan-zhuan-huan-zheng-shu-atoi-by-leetcode-/)

<details><summary>Description</summary>

```text
Implement the myAtoi(string s) function,
which converts a string to a 32-bit signed integer (similar to C/C++'s atoi function).

The algorithm for myAtoi(string s) is as follows:
1. Read in and ignore any leading whitespace.
2. Check if the next character (if not already at the end of the string) is '-' or '+'.
   Read this character in if it is either.
   This determines if the final result is negative or positive respectively.
   Assume the result is positive if neither is present.
3. Read in next the characters until the next non-digit character or the end of the input is reached.
   The rest of the string is ignored.
4. Convert these digits into an integer (i.e. "123" -> 123, "0032" -> 32).
   If no digits were read, then the integer is 0.
   Change the sign as necessary (from step 2).
5. If the integer is out of the 32-bit signed integer range [-2^31, 2^31 - 1],
   then clamp the integer so that it remains in the range.
   Specifically, integers less than -2^31 should be clamped to -2^31,
   and integers greater than 2^31 - 1 should be clamped to 2^31 - 1.
6. Return the integer as the final result.
Note:
- Only the space character ' ' is considered a whitespace character.
- Do not ignore any characters other than the leading whitespace or the rest of the string after the digits.

Example 1:
Input: s = "42"
Output: 42
Explanation: The underlined characters are what is read in, the caret is the current reader position.
Step 1: "42" (no characters read because there is no leading whitespace)
         ^
Step 2: "42" (no characters read because there is neither a '-' nor '+')
         ^
Step 3: "42" ("42" is read in)
           ^
The parsed integer is 42.
Since 42 is in the range [-231, 231 - 1], the final result is 42.

Example 2:
Input: s = "   -42"
Output: -42
Explanation:
Step 1: "   -42" (leading whitespace is read and ignored)
            ^
Step 2: "   -42" ('-' is read, so the result should be negative)
             ^
Step 3: "   -42" ("42" is read in)
               ^
The parsed integer is -42.
Since -42 is in the range [-2^31, 2^31 - 1], the final result is -42.

Example 3:
Input: s = "4193 with words"
Output: 4193
Explanation:
Step 1: "4193 with words" (no characters read because there is no leading whitespace)
         ^
Step 2: "4193 with words" (no characters read because there is neither a '-' nor '+')
         ^
Step 3: "4193 with words" ("4193" is read in; reading stops because the next character is a non-digit)
             ^
The parsed integer is 4193.
Since 4193 is in the range [-2^31, 2^31 - 1], the final result is 4193.

Constraints:
0 <= s.length <= 200
s consists of English letters (lower-case and upper-case), digits (0-9), ' ', '+', '-', and '.'.
```

</details>

<details><summary>C</summary>

```c
int myAtoi(char *s) {
    int retVal = 0;

    int sSize = strlen(s);

    bool signStatus = false;
    bool numberStatus = false;
    bool isMinus = false;
    long sum = 0;
    int i;
    for (i = 0; i < sSize; ++i) {
        if ((s[i] == '-') || (s[i] == '+') || (s[i] == ' ')) {
            if ((signStatus == true) || (numberStatus == true)) {
                break;
            }

            if (s[i] == '-') {
                isMinus = true;
            }

            if (s[i] != ' ') {
                signStatus = true;
            }
        } else if ((s[i] > '9') || (s[i] < '0')) {
            break;
        } else {
            numberStatus = true;
            sum = 10 * sum + (s[i] - '0');
            if (sum > INT_MAX) {
                break;
            }
        }
    }

    if (isMinus == true) {
        sum = -(sum);
    }

    /* 5. If the integer is out of the 32-bit signed integer range [-2^31, 2^31 - 1],
     *  then clamp the integer so that it remains in the range.
     *  Specifically, integers less than -2^31 should be clamped to -2^31,
     *  and integers greater than 2^31 - 1 should be clamped to 2^31 - 1.
     */
    if (sum > INT_MAX) {
        retVal = INT_MAX;
    } else if (sum < INT_MIN) {
        retVal = INT_MIN;
    } else {
        retVal = sum;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int myAtoi(string s) {
        int retVal = 0;

        bool signStatus = false;
        bool numberStatus = false;
        bool isMinus = false;
        long sum = 0;
        for (auto c : s) {
            if ((c == '-') || (c == '+') || (c == ' ')) {
                if ((signStatus == true) || (numberStatus == true)) {
                    break;
                }

                if (c == '-') {
                    isMinus = true;
                }

                if (c != ' ') {
                    signStatus = true;
                }
            } else if ((c > '9') || (c < '0')) {
                break;
            } else {
                numberStatus = true;
                sum = 10 * sum + (c - '0');
                if (sum > numeric_limits<int>::max()) {
                    break;
                }
            }
        }

        if (isMinus == true) {
            sum = -(sum);
        }

        /* 5. If the integer is out of the 32-bit signed integer range [-2^31, 2^31 - 1],
         *  then clamp the integer so that it remains in the range.
         *  Specifically, integers less than -2^31 should be clamped to -2^31,
         *  and integers greater than 2^31 - 1 should be clamped to 2^31 - 1.
         */
        if (sum > numeric_limits<int>::max()) {
            retVal = numeric_limits<int>::max();
        } else if (sum < numeric_limits<int>::min()) {
            retVal = numeric_limits<int>::min();
        } else {
            retVal = sum;
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
        # integer range [-2^31, 2^31 - 1]
        self.INT_MAX = 2 ** 31 - 1
        self.INT_MIN = -2 ** 31

    def myAtoi(self, s: str) -> int:
        retVal = 0

        signStatus = False
        numberStatus = False
        isMinus = False
        sum = 0
        for c in s:
            if (c == '+') or (c == '-') or (c == ' '):
                if (signStatus == True) or (numberStatus == True):
                    break
                isMinus = True if (c == '-') else False
                signStatus = False if (c == ' ') else True
            elif (48 <= ord(c) <= 57):
                numberStatus = True
                sum = (10 * sum) + (ord(c) - 48)
                if sum > self.INT_MAX:
                    break
            else:
                break

        if isMinus == True:
            sum = -(sum)

        '''
        5. If the integer is out of the 32-bit signed integer range [-2^31, 2^31 - 1],
        then clamp the integer so that it remains in the range.
        Specifically, integers less than -2^31 should be clamped to -2^31,
        and integers greater than 2^31 - 1 should be clamped to 2^31 - 1.
        '''
        if sum > self.INT_MAX:
            retVal = self.INT_MAX
        elif sum < self.INT_MIN:
            retVal = self.INT_MIN
        else:
            retVal = sum

        return retVal
```

</details>

## [12. Integer to Roman](https://leetcode.com/problems/integer-to-roman/)

- [Official](https://leetcode.cn/problems/integer-to-roman/solutions/774611/zheng-shu-zhuan-luo-ma-shu-zi-by-leetcod-75rs/)

<details><summary>Description</summary>

```text
Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
For example, 2 is written as II in Roman numeral, just two one's added together.
12 is written as XII, which is simply X + II.
The number 27 is written as XXVII, which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right.
However, the numeral for four is not IIII. Instead, the number four is written as IV.
Because the one is before the five we subtract it making four.
The same principle applies to the number nine, which is written as IX.
There are six instances where subtraction is used:
- I can be placed before V (5) and X (10) to make 4 and 9.
- X can be placed before L (50) and C (100) to make 40 and 90.
- C can be placed before D (500) and M (1000) to make 400 and 900.

Given an integer, convert it to a roman numeral.

Example 1:
Input: num = 3
Output: "III"
Explanation: 3 is represented as 3 ones.

Example 2:
Input: num = 58
Output: "LVIII"
Explanation: L = 50, V = 5, III = 3.

Example 3:
Input: num = 1994
Output: "MCMXCIV"
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.

Constraints:
1 <= num <= 3999
```

</details>

<details><summary>C</summary>

```c
char* intToRoman(int num) {
    char* pRetVal = NULL;

#define MAX_ROMAN_SIZE (16)
    pRetVal = (char*)malloc(MAX_ROMAN_SIZE * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (MAX_ROMAN_SIZE * sizeof(char)));

    struct Map {
        int value;
        char* symbol;
    } romanMapping[] = {{1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, {90, "XC"}, {50, "L"},
                        {40, "XL"},  {10, "X"},   {9, "IX"},  {5, "V"},    {4, "IV"},  {1, "I"}};
    int numberOfRoman = sizeof(romanMapping) / sizeof(romanMapping[0]);

    int i;
    for (i = 0; i < numberOfRoman; ++i) {
        while ((num > 0) && ((num - romanMapping[i].value) >= 0)) {
            num -= romanMapping[i].value;
            strncat(pRetVal, romanMapping[i].symbol, MAX_ROMAN_SIZE - strlen(pRetVal));
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
    string intToRoman(int num) {
        string retVal;

        map<int, string> romanMapping = {{1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"},
                                         {90, "XC"},  {50, "L"},   {40, "XL"}, {10, "X"},   {9, "IX"},
                                         {5, "V"},    {4, "IV"},   {1, "I"}};
        for (auto iterate = romanMapping.rbegin(); iterate != romanMapping.rend(); ++iterate) {
            int key = iterate->first;
            string value = iterate->second;

            while ((num > 0) && ((num - key) >= 0)) {
                num -= key;
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
    def intToRoman(self, num: int) -> str:
        retVal = ""

        romanMapping = {
            1000: "M",
            900: "CM",
            500: "D",
            400: "CD",
            100: "C",
            90: "XC",
            50: "L",
            40: "XL",
            10: "X",
            9: "IX",
            5: "V",
            4: "IV",
            1: "I"
        }
        for key, value in romanMapping.items():
            while (num > 0) and (num - key >= 0):
                num -= key
                retVal += value

        return retVal
```

</details>

## [13. Roman to Integer](https://leetcode.com/problems/roman-to-integer/)

- [Official](https://leetcode.cn/problems/roman-to-integer/solutions/774992/luo-ma-shu-zi-zhuan-zheng-shu-by-leetcod-w55p/)

<details><summary>Description</summary>

```text
Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
For example, 2 is written as II in Roman numeral, just two ones added together.
12 is written as XII, which is simply X + II.
The number 27 is written as XXVII, which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right.
However, the numeral for four is not IIII. Instead, the number four is written as IV.
Because the one is before the five we subtract it making four.
The same principle applies to the number nine, which is written as IX.
There are six instances where subtraction is used:
- I can be placed before V (5) and X (10) to make 4 and 9.
- X can be placed before L (50) and C (100) to make 40 and 90.
- C can be placed before D (500) and M (1000) to make 400 and 900.

Given a roman numeral, convert it to an integer.

Example 1:
Input: s = "III"
Output: 3
Explanation: III = 3.

Example 2:
Input: s = "LVIII"
Output: 58
Explanation: L = 50, V= 5, III = 3.

Example 3:
Input: s = "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.

Constraints:
1 <= s.length <= 15
s contains only the characters ('I', 'V', 'X', 'L', 'C', 'D', 'M').
It is guaranteed that s is a valid roman numeral in the range [1, 3999].
```

<details><summary>Hint</summary>

```text
1. Problem is simpler to solve by working the string from back to front and using a map.
```

</details>

</details>

<details><summary>C</summary>

```c
int romanToInt(char *s) {
    int retVal = 0;

    int romanMapping[26];  // s contains only the characters ('I', 'V', 'X', 'L', 'C', 'D', 'M').
    romanMapping['I' - 'A'] = 1;
    romanMapping['V' - 'A'] = 5;
    romanMapping['X' - 'A'] = 10;
    romanMapping['L' - 'A'] = 50;
    romanMapping['C' - 'A'] = 100;
    romanMapping['D' - 'A'] = 500;
    romanMapping['M' - 'A'] = 1000;

    // III = I + I + I = 1 + 1 + 1 = 3
    // LVIII = L + V + I + I + I = 50 + 5 + 1 + 1 + 1 = 58
    // MCMXCIV = M + C + M + X + C + I + V = 1000 - 100 + 1000 - 10 + 100 - 1 + 5 = 1994
    int currentValue, nextValue;
    int sSize = strlen(s);
    int i;
    for (i = 0; i < sSize - 1; ++i) {
        currentValue = romanMapping[s[i] - 'A'];
        nextValue = romanMapping[s[i + 1] - 'A'];
        if (currentValue < nextValue) {
            retVal -= currentValue;
        } else {
            retVal += currentValue;
        }
    }
    currentValue = romanMapping[s[sSize - 1] - 'A'];
    retVal += currentValue;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int romanToInt(string s) {
        int retVal = 0;

        unordered_map<char, int> romanMapping = {
            {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000},
        };

        // III = I + I + I = 1 + 1 + 1 = 3
        // LVIII = L + V + I + I + I = 50 + 5 + 1 + 1 + 1 = 58
        // MCMXCIV = M + C + M + X + C + I + V = 1000 - 100 + 1000 - 10 + 100 - 1 + 5 = 1994
        int currentValue, nextValue;
        int sSize = s.size();
        for (int i = 0; i < sSize - 1; ++i) {
            currentValue = romanMapping[s[i]];
            nextValue = romanMapping[s[i + 1]];
            if (currentValue < nextValue) {
                retVal -= currentValue;
            } else {
                retVal += currentValue;
            }
        }
        currentValue = romanMapping[s[sSize - 1]];
        retVal += currentValue;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def romanToInt(self, s: str) -> int:
        retVal = 0

        romanMapping = {
            'I': 1,
            'V': 5,
            'X': 10,
            'L': 50,
            'C': 100,
            'D': 500,
            'M': 1000,
        }

        # III = I + I + I = 1 + 1 + 1 = 3
        # LVIII = L + V + I + I + I = 50 + 5 + 1 + 1 + 1 = 58
        # MCMXCIV = M + C + M + X + C + I + V = 1000 - 100 + 1000 - 10 + 100 - 1 + 5 = 1994
        sSize = len(s)
        for i in range(sSize-1):
            currentValue = romanMapping[s[i]]
            nextValue = romanMapping[s[i+1]]
            if currentValue < nextValue:
                retVal -= currentValue
            else:
                retVal += currentValue
        currentValue = romanMapping[s[sSize-1]]
        retVal += currentValue

        return retVal
```

</details>

## [14. Longest Common Prefix](https://leetcode.com/problems/longest-common-prefix/)

- [Official](https://leetcode.com/problems/longest-common-prefix/editorial/)
- [Official](https://leetcode.cn/problems/longest-common-prefix/solutions/288575/zui-chang-gong-gong-qian-zhui-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string "".

Example 1:
Input: strs = ["flower","flow","flight"]
Output: "fl"

Example 2:
Input: strs = ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.

Constraints:
1 <= strs.length <= 200
0 <= strs[i].length <= 200
strs[i] consists of only lowercase English letters.
```

</details>

<details><summary>C</summary>

```c
char *longestCommonPrefix(char **strs, int strsSize) {
    char *retVal = NULL;

    retVal = strs[0];  // 1 <= strs.length <= 200
    int retValLength = strlen(retVal);
    int i, j;
    for (i = 1; i < strsSize; ++i) {
        for (j = 0; j < retValLength; ++j) {
            if ((j == (int)strlen(strs[i])) || (retVal[j] != strs[i][j])) {
                retValLength = j;
                break;
            }
        }
    }
    retVal[retValLength] = '\0';

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string longestCommonPrefix(vector<string>& strs) {
        string retVal;

        retVal = strs[0];  // 1 <= strs.length <= 200
        int retValLength = retVal.size();
        int strsSize = strs.size();
        for (int i = 1; i < strsSize; ++i) {
            for (int j = 0; j < retValLength; ++j) {
                if ((j == (int)strs[i].size()) || (retVal[j] != strs[i][j])) {
                    retValLength = j;
                    break;
                }
            }
        }
        retVal = retVal.substr(0, retValLength);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def longestCommonPrefix(self, strs: List[str]) -> str:
        retVal = ""

        retVal = strs[0]  # 1 <= strs.length <= 200
        retValLength = len(retVal)
        strsSize = len(strs)
        for i in range(1, strsSize):
            for j in range(retValLength):
                if (j == len(strs[i])) or (retVal[j] != strs[i][j]):
                    retValLength = j
                    break
        retVal = retVal[:retValLength]

        return retVal
```

</details>

## [28. Find the Index of the First Occurrence in a String](https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/)

- [Official](https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/solutions/732236/shi-xian-strstr-by-leetcode-solution-ds6y/)

<details><summary>Description</summary>

```text
Given two strings needle and haystack, return the index of the first occurrence of needle in haystack,
or -1 if needle is not part of haystack.

Example 1:
Input: haystack = "sadbutsad", needle = "sad"
Output: 0
Explanation: "sad" occurs at index 0 and 6.
The first occurrence is at index 0, so we return 0.

Example 2:
Input: haystack = "leetcode", needle = "leeto"
Output: -1
Explanation: "leeto" did not occur in "leetcode", so we return -1.

Constraints:
1 <= haystack.length, needle.length <= 10^4
haystack and needle consist of only lowercase English characters.
```

</details>

<details><summary>C</summary>

```c
#define KMP_START_IDX (-1)
// https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
void kmp(int* next, char* pattern) {
    int patternSize = strlen(pattern);

    int j = KMP_START_IDX;
    next[0] = j;
    int i;
    for (i = 1; i < patternSize; ++i) {
        while ((j >= 0) && (pattern[i] != pattern[j + 1])) {
            j = next[j];
        }

        if (pattern[i] == pattern[j + 1]) {
            j++;
        }

        next[i] = j;
    }
}
int strStr(char* haystack, char* needle) {
    int retVal = -1;

    int needleSize = strlen(needle);
    if (needleSize == 0) {
        retVal = 0;
        return retVal;
    }
    int next[needleSize];
    memset(next, 0, sizeof(next));
    kmp(next, needle);

    int haystackSize = strlen(haystack);
    int needleIdx = KMP_START_IDX;
    int haystackIdx = 0;
    for (haystackIdx = 0; haystackIdx < haystackSize; ++haystackIdx) {
        while ((needleIdx >= 0) && (haystack[haystackIdx] != needle[needleIdx + 1])) {
            needleIdx = next[needleIdx];
        }

        if (haystack[haystackIdx] == needle[needleIdx + 1]) {
            ++needleIdx;
        }

        if (needleIdx == needleSize - 1) {
            retVal = haystackIdx - needleSize + 1;
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
    int KMP_START_IDX = -1;

   public:
    // https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
    void kmp(vector<int>& next, string pattern) {
        int patternSize = pattern.size();

        int j = KMP_START_IDX;
        next[0] = j;
        for (int i = 1; i < patternSize; ++i) {
            while ((j >= 0) && (pattern[i] != pattern[j + 1])) {
                j = next[j];
            }

            if (pattern[i] == pattern[j + 1]) {
                j++;
            }

            next[i] = j;
        }
    }
    int strStr(string haystack, string needle) {
        int retVal = -1;

        int needleSize = needle.size();
        if (needleSize == 0) {
            retVal = 0;
            return retVal;
        }
        vector<int> next(needleSize, 0);
        kmp(next, needle);

        int haystackSize = haystack.size();
        int needleIdx = KMP_START_IDX;
        for (int haystackIdx = 0; haystackIdx < haystackSize; ++haystackIdx) {
            while ((needleIdx >= 0) && (haystack[haystackIdx] != needle[needleIdx + 1])) {
                needleIdx = next[needleIdx];
            }

            if (haystack[haystackIdx] == needle[needleIdx + 1]) {
                ++needleIdx;
            }

            if (needleIdx == needleSize - 1) {
                retVal = haystackIdx - needleSize + 1;
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
        self.kmpStartIdx = -1

    # https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
    def kmp(self, next: List[int], pattern: str) -> None:
        patternSize = len(pattern)

        j = self.kmpStartIdx
        next[0] = j
        for i in range(1, patternSize):
            while (j >= 0) and (pattern[i] != pattern[j + 1]):
                j = next[j]

            if pattern[i] == pattern[j + 1]:
                j += 1

            next[i] = j

    def strStr(self, haystack: str, needle: str) -> int:
        retVal = -1

        needleSize = len(needle)
        if needleSize == 0:
            retVal = 0
            return retVal
        next = [0] * needleSize
        self.kmp(next, needle)

        haystackSize = len(haystack)
        needleIdx = self.kmpStartIdx
        for haystackIdx in range(haystackSize):
            while (needleIdx >= 0) and (haystack[haystackIdx] != needle[needleIdx + 1]):
                needleIdx = next[needleIdx]

            if haystack[haystackIdx] == needle[needleIdx + 1]:
                needleIdx += 1

            if needleIdx == needleSize - 1:
                retVal = haystackIdx - needleSize + 1
                break

        return retVal
```

</details>

## [38. Count and Say](https://leetcode.com/problems/count-and-say/)

<details><summary>Description</summary>

```text
The count-and-say sequence is a sequence of digit strings defined by the recursive formula:
- countAndSay(1) = "1"
- countAndSay(n) is the way you would "say" the digit string from countAndSay(n-1),
  which is then converted into a different digit string.

To determine how you "say" a digit string, split it into the minimal number of substrings
such that each substring contains exactly one unique digit.
Then for each substring, say the number of digits, then say the digit. Finally, concatenate every said digit.

For example, the saying and conversion for digit string "3322251":
 "3322251"
 = two 3's, three 2's, one 5 and one 1
 = 2 3 + 3 2 + 1 5 + 11
 = "23321511"

Given a positive integer n, return the nth term of the count-and-say sequence.

Example 1:
Input: n = 1
Output: "1"
Explanation: This is the base case.

Example 2:
Input: n = 4
Output: "1211"
Explanation:
countAndSay(1) = "1"
countAndSay(2) = say "1" = one 1 = "11"
countAndSay(3) = say "11" = two 1's = "21"
countAndSay(4) = say "21" = one 2 + one 1 = "12" + "11" = "1211"

Constraints:
1 <= n <= 30
```

</details>

<details><summary>C</summary>

```c
char* help(char* pSequence)
{
    char* pRetVal = NULL;

    int len = strlen(pSequence);
    int returnSize = 2 * len * sizeof(char) + 1;
    pRetVal = (char*)malloc(returnSize);
    if (pRetVal == NULL)
    {
        perror("malloc");
        free(pSequence);
        return pRetVal;
    }
    memset(pRetVal, 0, returnSize);

    int idx = 0;
    char digit = pSequence[0];
    int count = 0;
    int i;
    for (i=0; i<len; ++i)
    {
        if (digit != pSequence[i])
        {
            idx += snprintf(pRetVal+idx, returnSize-idx, "%d%c", count, digit);
            digit = pSequence[i];
            count = 1;
            continue;
        }
        ++count;
    }
    idx += snprintf(pRetVal+idx, returnSize-idx, "%d%c", count, digit);
    free(pSequence);

    return pRetVal;
}

char * countAndSay(int n){
    char* pRetVal = NULL;

    pRetVal = (char*)malloc(2*sizeof(char));
    if (pRetVal == NULL)
    {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, 2*sizeof(char));
    snprintf(pRetVal, 2*sizeof(char), "%d", 1);

    if (n == 1)
    {
        return pRetVal;
    }

    int i;
    for (i=2; i<=n; ++i)
    {
        pRetVal = help(pRetVal);
    }

    return pRetVal;
}
```

</details>

## [43. Multiply Strings](https://leetcode.com/problems/multiply-strings/)

<details><summary>Description</summary>

```text
Given two non-negative integers num1 and num2 represented as strings,
return the product of num1 and num2, also represented as a string.

Note: You must not use any built-in BigInteger library or convert the inputs to integer directly.

Example 1:
Input: num1 = "2", num2 = "3"
Output: "6"

Example 2:
Input: num1 = "123", num2 = "456"
Output: "56088"

Constraints:
- 1 <= num1.length, num2.length <= 200
- num1 and num2 consist of digits only.
- Both num1 and num2 do not contain any leading zero, except the number 0 itself.
```

</details>

<details><summary>C</summary>

```c
char * multiply(char * num1, char * num2){
    unsigned char* pRetVal = NULL;

    if ((strcmp(num1, "0") == 0) || (strcmp(num2, "0") == 0))
    {
        pRetVal = (unsigned char*)malloc(2*sizeof(unsigned char));
        if (pRetVal == NULL)
        {
            perror("malloc");
            return (char*)(pRetVal);
        }
        memset(pRetVal, 0, 2*sizeof(unsigned char));
        pRetVal[0] = '0';

        return (char*)(pRetVal);
    }

    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int len = len1 + len2 + 1;
    pRetVal = (unsigned char*)malloc(len*sizeof(unsigned char));
    if (pRetVal == NULL)
    {
        perror("malloc");
        return (char*)(pRetVal);
    }
    memset(pRetVal, '0', (len-1)*sizeof(unsigned char));
    pRetVal[len-1] = 0;

    int multiplicand;
    int multiplier;
    int product = 0;
    int carry = 0;
    int i, j;
    for (i=len1-1; i>=0; --i)
    {
        multiplicand = num1[i] - '0';
        for (j=len2-1; j>=0; --j)
        {
            multiplier = num2[j] - '0';
            product = multiplicand * multiplier;

            pRetVal[i+j+1] = pRetVal[i+j+1] + product;
            carry = (pRetVal[i+j+1] - '0') / 10;
            pRetVal[i+j+1] = ((pRetVal[i+j+1] - '0') % 10) + '0';
            pRetVal[i+j] = pRetVal[i+j] + carry;

            //printf("(%d,%d)[%d,%d][%d,%d][%s]\n", i,j,multiplicand, multiplier, carry, product, pRetVal);
        }
    }

    if (pRetVal[0] == '0')
    {
        for (i=0; i<(len-2); ++i)
        {
            pRetVal[i] = pRetVal[i+1];
        }
        pRetVal[i] = 0;
    }

    return (char*)(pRetVal);
}
```

</details>

## [58. Length of Last Word](https://leetcode.com/problems/length-of-last-word/)

- [Official](https://leetcode.cn/problems/length-of-last-word/solutions/1008504/zui-hou-yi-ge-dan-ci-de-chang-du-by-leet-51ih/)

<details><summary>Description</summary>

```text
Given a string s consisting of words and spaces, return the length of the last word in the string.

A word is a maximal substring consisting of non-space characters only.

Example 1:
Input: s = "Hello World"
Output: 5
Explanation: The last word is "World" with length 5.

Example 2:
Input: s = "   fly me   to   the moon  "
Output: 4
Explanation: The last word is "moon" with length 4.

Example 3:
Input: s = "luffy is still joyboy"
Output: 6
Explanation: The last word is "joyboy" with length 6.

Constraints:
1 <= s.length <= 10^4
s consists of only English letters and spaces ' '.
There will be at least one word in s.
```

</details>

<details><summary>C</summary>

```c
int lengthOfLastWord(char *s) {
    int retVal = 0;

    int sSize = strlen(s);
    int i;
    for (i = sSize - 1; i >= 0; --i) {
        if (s[i] != ' ') {
            ++retVal;
        } else {
            if (retVal != 0) {
                break;
            }
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
    int lengthOfLastWord(string s) {
        int retVal = 0;

        int sSize = s.size();
        for (int i = sSize - 1; i >= 0; --i) {
            if (s[i] != ' ') {
                ++retVal;
            } else {
                if (retVal != 0) {
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
    def lengthOfLastWord(self, s: str) -> int:
        retVal = 0

        sSize = len(s)
        for i in range(sSize-1, -1, -1):
            if s[i] != ' ':
                retVal += 1
            else:
                if retVal != 0:
                    break

        return retVal
```

</details>

## [68. Text Justification](https://leetcode.com/problems/text-justification/)

- [Official](https://leetcode.com/problems/text-justification/editorial/)
- [Official](https://leetcode.cn/problems/text-justification/solutions/986756/wen-ben-zuo-you-dui-qi-by-leetcode-solut-dyeg/)

<details><summary>Description</summary>

```text
Given an array of strings words and a width maxWidth,
format the text such that each line has exactly maxWidth characters and is fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as you can in each line.
Pad extra spaces ' ' when necessary so that each line has exactly maxWidth characters.

Extra spaces between words should be distributed as evenly as possible.
If the number of spaces on a line does not divide evenly between words,
the empty slots on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left-justified, and no extra space is inserted between words.

Note:
- A word is defined as a character sequence consisting of non-space characters only.
- Each word's length is guaranteed to be greater than 0 and not exceed maxWidth.
- The input array words contains at least one word.

Example 1:
Input: words = ["This", "is", "an", "example", "of", "text", "justification."], maxWidth = 16
Output:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]

Example 2:
Input: words = ["What","must","be","acknowledgment","shall","be"], maxWidth = 16
Output:
[
  "What   must   be",
  "acknowledgment  ",
  "shall be        "
]
Explanation: Note that the last line is "shall be    " instead of "shall     be",
because the last line must be left-justified instead of fully-justified.
Note that the second line is also left-justified because it contains only one word.

Example 3:
Input: words = ["Science","is","what","we","understand","well","enough","to","explain","to","a","computer.",
"Art","is","everything","else","we","do"], maxWidth = 20
Output:
[
  "Science  is  what we",
  "understand      well",
  "enough to explain to",
  "a  computer.  Art is",
  "everything  else  we",
  "do                  "
]

Constraints:
1 <= words.length <= 300
1 <= words[i].length <= 20
words[i] consists of only English letters and symbols.
1 <= maxWidth <= 100
words[i].length <= maxWidth
```

</details>

<details><summary>C</summary>

```c
void fillWords(char** words, int iNum, char* pRet, int iLen, int maxWidth) {
    int iAveNum = 0;
    int iresNum = 0;
    int iSpaceNum = maxWidth - iLen;
    if (iNum > 1) {
        iAveNum = iSpaceNum / (iNum - 1);
        iresNum = iSpaceNum % (iNum - 1);
    }

    int i;
    for (i = 0; i < maxWidth; i++) {
        pRet[i] = ' ';
    }
    int ipos = 0;
    for (i = 0; i < iNum; i++) {
        memcpy(&pRet[ipos], words[i], strlen(words[i]));
        ipos += strlen(words[i]) + iAveNum;
        if (iresNum > 0) {
            ipos += 1;
            iresNum -= 1;
        }
    }
}
void fillWordsLastRow(char** words, int iNum, char* pRet, int maxWidth) {
    int i;
    for (i = 0; i < maxWidth; i++) {
        pRet[i] = ' ';
    }
    int ipos = 0;
    for (i = 0; i < iNum; i++) {
        memcpy(&pRet[ipos], words[i], strlen(words[i]));
        ipos += strlen(words[i]) + 1;
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** fullJustify(char** words, int wordsSize, int maxWidth, int* returnSize) {
    char** pRetVal = NULL;

    (*returnSize) = 0;

    //
    if ((NULL == words) || (0 == wordsSize)) {
        return pRetVal;
    }

    //
    pRetVal = (char**)malloc(wordsSize * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (wordsSize * sizeof(char*)));
    int returnColumnSize = maxWidth + 1;

    //
    int iPos = 0;
    int iTmpNum = 0;
    int iTmpLen = 0;
    int iRetSize = 0;
    int i, j;
    for (i = 0; i < wordsSize; i++) {
        if (iTmpLen + strlen(words[i]) + iTmpNum > maxWidth) {
            pRetVal[iRetSize] = (char*)malloc(returnColumnSize * sizeof(char));
            if (pRetVal[iRetSize] == NULL) {
                perror("malloc");
                for (j = 0; j < i; ++j) {
                    free(pRetVal[j]);
                    pRetVal[j] = NULL;
                }
                free(pRetVal);
                pRetVal = NULL;
                return pRetVal;
            }
            memset(pRetVal[iRetSize], 0, (returnColumnSize * sizeof(char)));

            fillWords(&words[iPos], iTmpNum, pRetVal[iRetSize], iTmpLen, maxWidth);
            iPos = i;
            iTmpNum = 0;
            iTmpLen = 0;
            iRetSize += 1;
        }

        iTmpNum += 1;
        iTmpLen += strlen(words[i]);
    }
    //
    if (iPos <= wordsSize - 1) {
        pRetVal[iRetSize] = (char*)malloc(returnColumnSize * sizeof(char));
        if (pRetVal[iRetSize] == NULL) {
            perror("malloc");
            for (j = 0; j < iRetSize; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        memset(pRetVal[iRetSize], 0, (returnColumnSize * sizeof(char)));

        fillWordsLastRow(&words[iPos], iTmpNum, pRetVal[iRetSize], maxWidth);
        iRetSize += 1;
    }
    //
    (*returnSize) = iRetSize;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string blank(int n) {
        string retVal = string(n, ' ');

        return retVal;
    }
    string join(vector<string>& words, int left, int right, string sep) {
        string retVal = words[left];

        for (int i = left + 1; i < right; ++i) {
            retVal += sep + words[i];
        }

        return retVal;
    }
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> retVal;

        int wordsSize = words.size();
        int right = 0;
        while (true) {
            int left = right;
            int sumLen = 0;

            while ((right < wordsSize) && (sumLen + (int)(words[right].length()) + right - left <= maxWidth)) {
                sumLen += words[right++].length();
            }

            if (right == wordsSize) {
                string s = join(words, left, wordsSize, " ");
                retVal.emplace_back(s + blank(maxWidth - s.length()));
                return retVal;
            }

            int numSpaces = maxWidth - sumLen;
            int numWords = right - left;
            if (numWords == 1) {
                retVal.emplace_back(words[left] + blank(numSpaces));
                continue;
            }

            int avgSpaces = numSpaces / (numWords - 1);
            int extraSpaces = numSpaces % (numWords - 1);
            string s1 = join(words, left, left + extraSpaces + 1, blank(avgSpaces + 1));
            string s2 = join(words, left + extraSpaces + 1, right, blank(avgSpaces));
            retVal.emplace_back(s1 + blank(avgSpaces) + s2);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def get_words(self, words: List[str], maxWidth: int, i: int) -> List[str]:
        retVal = []

        curr_length = 0
        while (i < len(words)) and (curr_length + len(words[i]) <= maxWidth):
            retVal.append(words[i])
            curr_length += len(words[i]) + 1
            i += 1

        return retVal

    def create_line(self, words: List[str], maxWidth: int, line: List[str], i: int) -> str:
        retVal = ""

        base_length = -1
        for word in line:
            base_length += len(word) + 1
        extra_spaces = maxWidth - base_length
        if (len(line) == 1) or (i == len(words)):
            retVal = " ".join(line) + " " * extra_spaces
            return retVal

        word_count = len(line) - 1
        spaces_per_word = extra_spaces // word_count
        needs_extra_space = extra_spaces % word_count
        for j in range(needs_extra_space):
            line[j] += " "
        for j in range(word_count):
            line[j] += " " * spaces_per_word
        retVal = " ".join(line)

        return retVal

    def fullJustify(self, words: List[str], maxWidth: int) -> List[str]:
        retVal = []

        i = 0
        while i < len(words):
            current_line = self.get_words(words, maxWidth, i)
            i += len(current_line)
            retVal.append(self.create_line(words, maxWidth, current_line, i))

        return retVal
```

</details>

## [161. One-Edit-Distance](https://leetcode.com/problems/one-edit-distance/)  unlock

- Subscribe to unlock
  - Yandex
  - Facebook
  - Yahoo
- [One Edit Distance LeetCode Solution](https://www.tutorialcup.com/leetcode-solutions/one-edit-distance-leetcode-solution.htm)

<details><summary>Description</summary>

```text
Given two strings s and t, return true if they are both one edit distance apart, otherwise return false.

A string s is said to be one distance apart from a string t if you can:
- Insert exactly one character into s to get t.
- Delete exactly one character from s to get t.
- Replace exactly one character of s with a different character to get t.

Example 1:
Input: s = "ab", t = "acb"
Output: true
Explanation: We can insert 'c' into s to get t.

Example 2:
Input: s = "", t = ""
Output: false
Explanation: We cannot get t from s by only one step.

Constraints:
0 <= s.length, t.length <= 10^4
s and t consist of lowercase letters, uppercase letters, and digits.
```

</details>

<details><summary>C</summary>

```c
bool isOneEditDistance(char* s, char* t) {
    bool retVal = false;

    // check the length of difference could not exceed 1
    int lenS = strlen(s);
    int lenT = strlen(t);
    if (abs(lenS - lenT) > 1) {
        return retVal;
    }

    int i;
    int diff = 0;
    // at most one character could different if the length are the same
    if (lenS == lenT) {
        for (i = 0; i < lenS; ++i) {
            if (s[i] != t[i]) {
                ++diff;
            }
        }
        if (diff == 1) {
            retVal = true;
        }

        return retVal;
    }

    int idxS = 0;
    int idxT = 0;
    while ((idxS < lenS) && (idxT < lenT)) {
        // check remaining characters are the same except the only one different character if the length are different
        if (s[idxS] != t[idxT]) {
            if (idxS != idxT) {
                return retVal;
            }
            if (lenS > lenT) {
                ++idxS;
            } else {
                ++idxT;
            }
            continue;
        }

        ++idxS;
        ++idxT;
    }
    retVal = true;

    return retVal;
}
```

</details>

## [214. Shortest Palindrome](https://leetcode.com/problems/shortest-palindrome/)

- [Official](https://leetcode.com/problems/shortest-palindrome/editorial/)
- [Official](https://leetcode.cn/problems/shortest-palindrome/solutions/392561/zui-duan-hui-wen-chuan-by-leetcode-solution/)

<details><summary>Description</summary>

```text
You are given a string s. You can convert s to palindrome by adding characters in front of it.

Return the shortest palindrome you can find by performing this transformation.

Example 1:
Input: s = "aacecaaa"
Output: "aaacecaaa"

Example 2:
Input: s = "abcd"
Output: "dcbabcd"

Constraints:
0 <= s.length <= 5 * 10^4
s consists of lowercase English letters only.
```

</details>

<details><summary>C</summary>

```c
// https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
void kmp(char* s, int* pPrefixTable) {
    int sSize = strlen(s);

    int length = 0;
    int i;
    for (i = 1; i < sSize; i++) {
        while ((length > 0) && (s[i] != s[length])) {
            length = pPrefixTable[length - 1];
        }

        if (s[i] == s[length]) {
            length++;
        }

        pPrefixTable[i] = length;
    }
}
char* shortestPalindrome(char* s) {
    char* pRetVal = NULL;

    int sSize = strlen(s);
    int i;

    char reversedString[sSize + 1];
    memset(reversedString, 0, sizeof(reversedString));
    for (i = 0; i < sSize; ++i) {
        reversedString[i] = s[sSize - 1 - i];
    }

    int combinedStringSize = 2 * (sSize + 1) + 1;
    char combinedString[combinedStringSize];
    memset(combinedString, 0, sizeof(combinedString));
    snprintf(combinedString, sizeof(combinedString), "%s#%s", s, reversedString);

    int* pPrefixTable = (int*)malloc(combinedStringSize * sizeof(int));
    memset(pPrefixTable, 0, (combinedStringSize * sizeof(int)));
    kmp(combinedString, pPrefixTable);
    int palindromeLength = pPrefixTable[strlen(combinedString) - 1];

    char suffix[sSize + 1];
    memset(suffix, 0, sizeof(suffix));
    strncpy(suffix, reversedString, sSize - palindromeLength);

    pRetVal = (char*)malloc(combinedStringSize * sizeof(char));
    memset(pRetVal, 0, (combinedStringSize * sizeof(char)));
    snprintf(pRetVal, (combinedStringSize * sizeof(char)), "%s%s", suffix, s);

    //
    free(pPrefixTable);
    pPrefixTable = NULL;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    // https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
    vector<int> kmp(string s) {
        vector<int> retVal;

        int sSize = s.size();

        retVal.resize(sSize, 0);
        int length = 0;
        for (int i = 1; i < sSize; i++) {
            while ((length > 0) && (s[i] != s[length])) {
                length = retVal[length - 1];
            }

            if (s[i] == s[length]) {
                length++;
            }

            retVal[i] = length;
        }

        return retVal;
    }

   public:
    string shortestPalindrome(string s) {
        string retVal = s;

        string reversedString = string(s.rbegin(), s.rend());
        string combinedString = s + "#" + reversedString;

        vector<int> prefixTable = kmp(combinedString);
        int palindromeLength = prefixTable[combinedString.length() - 1];

        string suffix = reversedString.substr(0, s.length() - palindromeLength);
        retVal = suffix + s;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    # https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
    def kmp(self, s: str) -> List[int]:
        retVal = []

        sSize = len(s)

        retVal = [0] * sSize
        length = 0
        for i in range(1, sSize):
            while (length > 0) and (s[i] != s[length]):
                length = retVal[length - 1]

            if s[i] == s[length]:
                length += 1

            retVal[i] = length

        return retVal

    def shortestPalindrome(self, s: str) -> str:
        retVal = s

        reversedString = s[::-1]
        combinedString = s + "#" + reversedString

        prefixTable = self.kmp(combinedString)
        palindromeLength = prefixTable[-1]

        suffix = reversedString[: len(s) - palindromeLength]
        retVal = suffix + s

        return retVal
```

</details>

## [273. Integer to English Words](https://leetcode.com/problems/integer-to-english-words/)

- [Official](https://leetcode.com/problems/integer-to-english-words/editorial/)
- [Official](https://leetcode.cn/problems/integer-to-english-words/solutions/1040791/zheng-shu-zhuan-huan-ying-wen-biao-shi-b-ivik/)

<details><summary>Description</summary>

```text
Convert a non-negative integer num to its English words representation.

Example 1:
Input: num = 123
Output: "One Hundred Twenty Three"

Example 2:
Input: num = 12345
Output: "Twelve Thousand Three Hundred Forty Five"

Example 3:
Input: num = 1234567
Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"

Constraints:
0 <= num <= 2^31 - 1
```

<details><summary>Hint</summary>

```text
1. Did you see a pattern in dividing the number into chunk of words? For example, 123 and 123000.
2. Group the number by thousands (3 digits).
   You can write a helper function that takes a number less than 1000 and convert just that chunk to words.
3. There are many edge cases. What are some good test cases? Does your code work with input such as 0?
   Or 1000010? (middle chunk is zero and should not be printed out)
```

</details>

</details>

<details><summary>C</summary>

```c
char* numberToWords(int num) {
    char* pRetVal = NULL;

    int returnSize = 1000;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));

    if (num == 0) {
        snprintf(pRetVal, returnSize, "%s", "Zero");
        return pRetVal;
    }

    char* ones[] = {"",         "One",     "Two",     "Three",     "Four",     "Five",    "Six",
                    "Seven",    "Eight",   "Nine",    "Ten",       "Eleven",   "Twelve",  "Thirteen",
                    "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    char* tens[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    char* thousands[] = {"", "Thousand", "Million", "Billion"};

    int groupResultIdx;
    char groupResult[returnSize];
    int part;
    int groupIndex = 0;
    while (num > 0) {
        if (num % 1000 != 0) {
            groupResultIdx = 0;
            memset(groupResult, 0, sizeof(groupResult));
            part = num % 1000;

            if (part >= 100) {
                groupResultIdx += snprintf(groupResult + groupResultIdx, sizeof(groupResult) - groupResultIdx - 1,
                                           "%s Hundred ", ones[part / 100]);
                part %= 100;
            }

            if (part >= 20) {
                groupResultIdx += snprintf(groupResult + groupResultIdx, sizeof(groupResult) - groupResultIdx - 1,
                                           "%s ", tens[part / 10]);
                part %= 10;
            }

            if (part > 0) {
                groupResultIdx +=
                    snprintf(groupResult + groupResultIdx, sizeof(groupResult) - groupResultIdx - 1, "%s ", ones[part]);
            }

            groupResultIdx += snprintf(groupResult + groupResultIdx, sizeof(groupResult) - groupResultIdx - 1, "%s ",
                                       thousands[groupIndex]);
            groupResultIdx +=
                snprintf(groupResult + groupResultIdx, sizeof(groupResult) - groupResultIdx - 1, "%s", pRetVal);
            snprintf(pRetVal, returnSize, "%s", groupResult);
        }

        num /= 1000;
        groupIndex += 1;
    }

    int i = strlen(pRetVal) - 1;
    while (pRetVal[i] == ' ') {
        pRetVal[i--] = '\0';
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string numberToWords(int num) {
        string retVal;

        if (num == 0) {
            retVal = "Zero";
            return retVal;
        }

        vector<string> ones{"",         "One",     "Two",     "Three",     "Four",     "Five",    "Six",
                            "Seven",    "Eight",   "Nine",    "Ten",       "Eleven",   "Twelve",  "Thirteen",
                            "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
        vector<string> tens{"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
        vector<string> thousands{"", "Thousand", "Million", "Billion"};

        int groupIndex = 0;
        while (num > 0) {
            if (num % 1000 != 0) {
                string groupResult = "";
                int part = num % 1000;

                if (part >= 100) {
                    groupResult += ones[part / 100] + " Hundred ";
                    part %= 100;
                }

                if (part >= 20) {
                    groupResult += tens[part / 10] + " ";
                    part %= 10;
                }

                if (part > 0) {
                    groupResult += ones[part] + " ";
                }

                groupResult += thousands[groupIndex] + " ";
                retVal = groupResult + retVal;
            }

            num /= 1000;
            groupIndex += 1;
        }

        retVal = retVal.substr(0, retVal.find_last_not_of(" ") + 1);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def numberToWords(self, num: int) -> str:
        retVal = ""

        if num == 0:
            retVal = "Zero"
            return retVal

        ones = ["", "One", "Two", "Three", "Four",
                "Five", "Six", "Seven", "Eight", "Nine",
                "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen",
                "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"]
        tens = ["", "", "Twenty", "Thirty", "Forty",
                "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"]
        thousands = ["", "Thousand", "Million", "Billion"]

        groupIndex = 0
        while num > 0:
            if num % 1000 != 0:
                groupResult = ""
                part = num % 1000

                if part >= 100:
                    groupResult += ones[part // 100] + " Hundred "
                    part %= 100

                if part >= 20:
                    groupResult += tens[part // 10] + " "
                    part %= 10

                if part > 0:
                    groupResult += ones[part] + " "

                groupResult += thousands[groupIndex] + " "
                retVal = groupResult + retVal

            num //= 1000
            groupIndex += 1

        retVal = retVal.strip()

        return retVal
```

</details>

## [412. Fizz Buzz](https://leetcode.com/problems/fizz-buzz/)

<details><summary>Description</summary>

```text
Given an integer n, return a string array answer (1-indexed) where:

answer[i] == "FizzBuzz" if i is divisible by 3 and 5.
answer[i] == "Fizz" if i is divisible by 3.
answer[i] == "Buzz" if i is divisible by 5.
answer[i] == i (as a string) if none of the above conditions are true.

Example 1:
Input: n = 3
Output: ["1","2","Fizz"]

Example 2:
Input: n = 5
Output: ["1","2","Fizz","4","Buzz"]

Example 3:
Input: n = 15
Output: ["1","2","Fizz","4","Buzz","Fizz","7","8","Fizz","Buzz","11","Fizz","13","14","FizzBuzz"]

Constraints:
1 <= n <= 10^4
```

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** fizzBuzz(int n, int* returnSize){
    char** pRetVal;

#define ANSWER3 "Fizz"
#define ANSWER5 "Buzz"
    *returnSize = n;
    pRetVal = (char**)malloc((*returnSize) * sizeof(char*));
    if (pRetVal == NULL)
    {
        perror("malloc");
        *returnSize = 0;
        return pRetVal;
    }

    int len = strlen(ANSWER3) + strlen(ANSWER5) + 1;
    int i;
    for (i=0; i<(*returnSize); ++i)
    {
        pRetVal[i] = (char*)malloc(len * sizeof(char));
        if (pRetVal[i] == NULL)
        {
            perror("malloc");
            break;
        }
        memset(pRetVal[i], 0, len * sizeof(char));
        if ((((i+1)%3) == 0) && (((i+1)%5) == 0))
        {
            snprintf(pRetVal[i], len, "%s%s", ANSWER3, ANSWER5);
        }
        else if (((i+1)%3) == 0)
        {
            snprintf(pRetVal[i], len, "%s", ANSWER3);
        }
        else if (((i+1)%5) == 0)
        {
            snprintf(pRetVal[i], len, "%s", ANSWER5);
        }
        else
        {
            snprintf(pRetVal[i], len, "%d", (i+1));
        }
    }
    if (i != (*returnSize))
    {
        *returnSize = i;
        for (i=0; i<*returnSize; ++i)
        {
            if (pRetVal[i] == NULL)
            {
                continue;
            }
            free(pRetVal[i]);
        }
        free(pRetVal);
        *returnSize = 0;
        return pRetVal;
    }

    return pRetVal;
}
```

</details>

## [443. String Compression](https://leetcode.com/problems/string-compression/)

- [Official](https://leetcode.com/problems/string-compression/editorial)
- [Official](https://leetcode.cn/problems/string-compression/solutions/948556/ya-suo-zi-fu-chuan-by-leetcode-solution-kbuc/)

<details><summary>Description</summary>

```text
Given an array of characters chars, compress it using the following algorithm:

Begin with an empty string s. For each group of consecutive repeating characters in chars:
- If the group's length is 1, append the character to s.
- Otherwise, append the character followed by the group's length.

The compressed string s should not be returned separately, but instead, be stored in the input character array chars.
Note that group lengths that are 10 or longer will be split into multiple characters in chars.

After you are done modifying the input array, return the new length of the array.

You must write an algorithm that uses only constant extra space.

Example 1:
Input: chars = ["a","a","b","b","c","c","c"]
Output: Return 6, and the first 6 characters of the input array should be: ["a","2","b","2","c","3"]
Explanation: The groups are "aa", "bb", and "ccc". This compresses to "a2b2c3".

Example 2:
Input: chars = ["a"]
Output: Return 1, and the first character of the input array should be: ["a"]
Explanation: The only group is "a", which remains uncompressed since it's a single character.

Example 3:
Input: chars = ["a","b","b","b","b","b","b","b","b","b","b","b","b"]
Output: Return 4, and the first 4 characters of the input array should be: ["a","b","1","2"].
Explanation: The groups are "a" and "bbbbbbbbbbbb". This compresses to "ab12".

Constraints:
1 <= chars.length <= 2000
chars[i] is a lowercase English letter, uppercase English letter, digit, or symbol.
```

<details><summary>Hint</summary>

```text
1. How do you know if you are at the end of a consecutive group of characters?
```

</details>

</details>

<details><summary>C</summary>

```c
int compress(char* chars, int charsSize) {
    int retVal = 0;

    // 1 <= chars.length <= 2000 and Integer range: [2, 2147483647]
    char buf[12];
    int count = 1;
    int i, j;
    for (i = 1; i < charsSize; ++i) {
        if (chars[i - 1] == chars[i]) {
            ++count;
            continue;
        }

        chars[retVal++] = chars[i - 1];
        if (count != 1) {
            memset(buf, 0, sizeof(buf));
            snprintf(buf, sizeof(buf), "%d", count);
            for (j = 0; j < strlen(buf); ++j) {
                chars[retVal++] = buf[j];
            }
        }
        count = 1;
    }
    chars[retVal++] = chars[i - 1];
    if (count != 1) {
        memset(buf, 0, sizeof(buf));
        snprintf(buf, sizeof(buf), "%d", count);
        for (j = 0; j < strlen(buf); ++j) {
            chars[retVal++] = buf[j];
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
    int compress(vector<char>& chars) {
        int retVal = 0;

        int count = 1;
        int charsSize = chars.size();
        int i;
        for (i = 1; i < charsSize; ++i) {
            if (chars[i - 1] == chars[i]) {
                ++count;
                continue;
            }

            chars[retVal++] = chars[i - 1];
            if (count != 1) {
                string tmp = to_string(count);
                for (char c : tmp) {
                    chars[retVal++] = c;
                }
            }
            count = 1;
        }
        chars[retVal++] = chars[i - 1];
        if (count != 1) {
            string tmp = to_string(count);
            for (char c : tmp) {
                chars[retVal++] = c;
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
    def compress(self, chars: List[str]) -> int:
        retVal = 0

        count = 1
        charsSize = len(chars)
        i = 1
        while i < charsSize:
            if chars[i-1] == chars[i]:
                count += 1
                i += 1
                continue

            chars[retVal] = chars[i-1]
            retVal += 1
            if count != 1:
                for c in str(count):
                    chars[retVal] = c
                    retVal += 1
            count = 1
            i += 1

        chars[retVal] = chars[i - 1]
        retVal += 1
        if count != 1:
            for c in str(count):
                chars[retVal] = c
                retVal += 1

        return retVal
```

</details>

## [459. Repeated Substring Pattern](https://leetcode.com/problems/repeated-substring-pattern/)

- [Official](https://leetcode.com/problems/repeated-substring-pattern/editorial/)
- [Official](https://leetcode.cn/problems/repeated-substring-pattern/solutions/386481/zhong-fu-de-zi-zi-fu-chuan-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given a string s,
check if it can be constructed by taking a substring of it and appending multiple copies of the substring together.

Example 1:
Input: s = "abab"
Output: true
Explanation: It is the substring "ab" twice.

Example 2:
Input: s = "aba"
Output: false

Example 3:
Input: s = "abcabcabcabc"
Output: true
Explanation: It is the substring "abc" four times or the substring "abcabc" twice.

Constraints:
1 <= s.length <= 10^4
s consists of lowercase English letters.
```

</details>

<details><summary>C</summary>

```c
#define KMP (1)  // https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
#define STRING_CONCATENATION (1)
bool repeatedSubstringPattern(char* s) {
    bool retVal = false;

    int sSize = strlen(s);
#if (KMP)
    printf("Knuth-Morris-Pratt Algorithm\n");

    int next[sSize];
    memset(next, 0, sizeof(next));

    int j = -1;
    next[0] = j;
    int i;
    for (i = 1; i < sSize; ++i) {
        while ((j >= 0) && (s[i] != s[j + 1])) {
            j = next[j];
        }

        if (s[i] == s[j + 1]) {
            ++j;
        }

        next[i] = j;
    }

    if ((next[sSize - 1] != -1) && (sSize % (sSize - next[sSize - 1] - 1) == 0)) {
        retVal = true;
    }
#elif (STRING_CONCATENATION)
    printf("String Concatenation\n");

    char buf[2 * sSize + 1];
    memset(buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf), "%s%s", s, s);
    if (strstr(buf + 1, s) - buf != sSize) {
        retVal = true;
    }
#endif

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define KMP (1)  // https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
#define STRING_CONCATENATION (1)
   public:
    Solution() {
#if (KMP)
        cout << "Knuth-Morris-Pratt Algorithm\n\n";
#elif (STRING_CONCATENATION)
        cout << "String Concatenation\n\n";
#endif
    }
    bool repeatedSubstringPattern(string s) {
        bool retVal = false;

#if (KMP)
        int sSize = s.size();
        vector<int> next(sSize, 0);

        int j = -1;
        next[0] = j;
        int i;
        for (i = 1; i < sSize; ++i) {
            while ((j >= 0) && (s[i] != s[j + 1])) {
                j = next[j];
            }

            if (s[i] == s[j + 1]) {
                ++j;
            }

            next[i] = j;
        }

        if ((next[sSize - 1] != -1) && (sSize % (sSize - next[sSize - 1] - 1) == 0)) {
            retVal = true;
        }
#elif (STRING_CONCATENATION)
        if ((s + s).find(s, 1) != s.size()) {
            retVal = true;
        }
#endif

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def __init__(self):
        self.method = 1

        if self.method == 1:    # https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
            print("Knuth-Morris-Pratt Algorithm")
        elif self.method == 2:
            print("String Concatenation")
        print()

    def repeatedSubstringPattern(self, s: str) -> bool:
        retVal = False

        if self.method == 1:
            sSize = len(s)

            fail = [-1] * sSize
            for i in range(1, sSize):
                j = fail[i - 1]
                while (j != -1) and (s[j + 1] != s[i]):
                    j = fail[j]

                if s[j + 1] == s[i]:
                    fail[i] = j + 1

            if (fail[sSize - 1] != -1) and (sSize % (sSize - fail[sSize - 1] - 1) == 0):
                retVal = True

        elif self.method == 2:
            doubleString = s + s
            if s in doubleString[1:-1]:
                retVal = True

        return retVal
```

</details>

## [468. Validate IP Address](https://leetcode.com/problems/validate-ip-address/)

- [Official](https://leetcode.com/problems/validate-ip-address/solutions/478754/validate-ip-address/)
- [Official](https://leetcode.cn/problems/validate-ip-address/solutions/1521467/yan-zheng-ipdi-zhi-by-leetcode-solution-kge5/)

<details><summary>Description</summary>

```text
Given a string queryIP, return "IPv4" if IP is a valid IPv4 address,
"IPv6" if IP is a valid IPv6 address or "Neither" if IP is not a correct IP of any type.

A valid IPv4 address is an IP in the form "x1.x2.x3.x4" where 0 <= xi <= 255 and xi cannot contain leading zeros.
For example, "192.168.1.1" and "192.168.1.0" are valid IPv4 addresses while "192.168.01.1", "192.168.1.00",
and "192.168@1.1" are invalid IPv4 addresses.

A valid IPv6 address is an IP in the form "x1:x2:x3:x4:x5:x6:x7:x8" where:
- 1 <= xi.length <= 4
- xi is a hexadecimal string which may contain digits,
  lowercase English letter ('a' to 'f') and upper-case English letters ('A' to 'F').
- Leading zeros are allowed in xi.

For example, "2001:0db8:85a3:0000:0000:8a2e:0370:7334" and "2001:db8:85a3:0:0:8A2E:0370:7334" are valid IPv6 addresses,
while "2001:0db8:85a3::8A2E:037j:7334" and "02001:0db8:85a3:0000:0000:8a2e:0370:7334" are invalid IPv6 addresses.

Example 1:
Input: queryIP = "172.16.254.1"
Output: "IPv4"
Explanation: This is a valid IPv4 address, return "IPv4".

Example 2:
Input: queryIP = "2001:0db8:85a3:0:0:8A2E:0370:7334"
Output: "IPv6"
Explanation: This is a valid IPv6 address, return "IPv6".

Example 3:
Input: queryIP = "256.256.256.256"
Output: "Neither"
Explanation: This is neither a IPv4 address nor a IPv6 address.

Constraints:
queryIP consists only of English letters, digits and the characters '.' and ':'.
```

</details>

<details><summary>C</summary>

```c
#define RETURN_IPV4 "IPv4"
#define RETURN_IPV6 "IPv6"
#define RETURN_NEITHER "Neither"
#if 0  // inet_pton - convert IPv4 and IPv6 addresses from text to binary form
#include <arpa/inet.h>

char* validIPAddress(char* queryIP) {
    char buf[16];
    memset(buf, 0, sizeof(buf));

    if (inet_pton(AF_INET, queryIP, buf)) {
        return RETURN_IPV4;
    } else if (inet_pton(AF_INET6, queryIP, buf)) {
        return RETURN_IPV6;
    }

    return RETURN_NEITHER;
}
#else
char* validIPAddress(char* queryIP) {
    char* pRetVal = RETURN_NEITHER;

    int len = strlen(queryIP);
    if (len == 0) {
        return pRetVal;
    }

    int n;
    char x[8][len];
    char extra[len];
    int num;
    int i;

    // x1.x2.x3.x4
    memset(x, 0, sizeof(x));
    memset(extra, 0, sizeof(extra));
    n = sscanf(queryIP, "%[^.].%[^.].%[^.].%[^.]%s", x[0], x[1], x[2], x[3], extra);
    if (n == 4) {
        for (i = 0; i < n; ++i) {
            if ((strlen(x[i]) > 1) && (x[i][0] == '0')) {
                return pRetVal;
            }

            memset(extra, 0, sizeof(extra));
            if (sscanf(x[i], "%d%s", &num, extra) != 1) {
                return pRetVal;
            }
            if ((num < 0) || (num > 255)) {
                return pRetVal;
            }
        }
        pRetVal = RETURN_IPV4;
        return pRetVal;
    }

    // x1:x2:x3:x4:x5:x6:x7:x8
    memset(x, 0, sizeof(x));
    memset(extra, 0, sizeof(extra));
    n = sscanf(queryIP, "%[^:]:%[^:]:%[^:]:%[^:]:%[^:]:%[^:]:%[^:]:%[^:]%s", x[0], x[1], x[2], x[3], x[4], x[5], x[6],
               x[7], extra);
    if (n == 8) {
        for (i = 0; i < n; ++i) {
            if (strlen(x[i]) > 4) {
                return pRetVal;
            }

            memset(extra, 0, sizeof(extra));
            if (sscanf(x[i], "%x%s", &num, extra) != 1) {
                return pRetVal;
            }
            if ((num < 0) || (num > 65535)) {
                return pRetVal;
            }
        }
        pRetVal = RETURN_IPV6;
        return pRetVal;
    }

    return pRetVal;
}
#endif
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define RETURN_IPV4 "IPv4"
#define RETURN_IPV6 "IPv6"
#define RETURN_NEITHER "Neither"
   public:
    string validIPAddress(string queryIP) {
        string retVal(RETURN_NEITHER);

        int len = queryIP.length();
        if (len == 0) {
            return retVal;
        }

        int last;
        long unsigned int cur;
        int i;
        long unsigned int j;

        if (queryIP.find('.') != string::npos) {
            last = -1;

            for (i = 0; i < 4; ++i) {
                if (i == 3) {
                    cur = queryIP.size();
                } else {
                    cur = queryIP.find('.', last + 1);
                }
                if (cur == string::npos) {
                    return retVal;
                } else if (cur - last - 1 < 1 || cur - last - 1 > 3) {
                    return retVal;
                }

                int addr = 0;
                for (j = last + 1; j < cur; ++j) {
                    if (!isdigit(queryIP[j])) {
                        return retVal;
                    }
                    addr = addr * 10 + (queryIP[j] - '0');
                }
                if (addr > 255) {
                    return retVal;
                } else if ((addr > 0) && (queryIP[last + 1] == '0')) {
                    return retVal;
                } else if ((addr == 0) && (cur - last - 1 > 1)) {
                    return retVal;
                }

                last = cur;
            }

            return RETURN_IPV4;
        }

        last = -1;
        for (i = 0; i < 8; ++i) {
            if (i == 7) {
                cur = queryIP.size();
            } else {
                cur = queryIP.find(':', last + 1);
            }
            if (cur == string::npos) {
                return retVal;
            } else if ((cur - last - 1 < 1) || (cur - last - 1 > 4)) {
                return retVal;
            }

            for (j = last + 1; j < cur; ++j) {
                if ((!isdigit(queryIP[j])) && (!(('a' <= tolower(queryIP[j])) && (tolower(queryIP[j]) <= 'f')))) {
                    return retVal;
                }
            }

            last = cur;
        }

        return RETURN_IPV6;
    }
};
```

</details>

## [520. Detect Capital](https://leetcode.com/problems/detect-capital/)

- [Official](https://leetcode.com/problems/detect-capital/solutions/728399/detect-capital/)
- [Official](https://leetcode.cn/problems/detect-capital/solutions/1097378/jian-ce-da-xie-zi-mu-by-leetcode-solutio-449z/)

<details><summary>Description</summary>

```text
We define the usage of capitals in a word to be right when one of the following cases holds:
- All letters in this word are capitals, like "USA".
- All letters in this word are not capitals, like "leetcode".
- Only the first letter in this word is capital, like "Google".
Given a string word, return true if the usage of capitals in it is right.

Example 1:
Input: word = "USA"
Output: true

Example 2:
Input: word = "FlaG"
Output: false

Constraints:
1 <= word.length <= 100
word consists of lowercase and uppercase English letters.
```

</details>

<details><summary>C</summary>

```c
bool detectCapitalUse(char* word) {
    bool retVal = true;

    int len = strlen(word);
    if (len == 1) {
        return retVal;
    }

    int i;
    // All letters in this word are capitals
    if (isupper(word[0]) && isupper(word[1])) {
        for (i=2; i<len; ++i) {
            retVal = isupper(word[i]);
            if (retVal == false) {
                return retVal;
            }
        }

        return retVal;
    }
    // All letters in this word are not capitals or Only the first letter in this word is capital
    for (i=1; i<len; ++i) {
        retVal = islower(word[i]);
        if (retVal == false) {
            return retVal;
        }
    }

    return retVal;
}
```

</details>

## [551. Student Attendance Record I](https://leetcode.com/problems/student-attendance-record-i/)

- [Official](https://leetcode.cn/problems/student-attendance-record-i/solutions/939224/xue-sheng-chu-qin-ji-lu-i-by-leetcode-so-fcol/)

<details><summary>Description</summary>

```text
You are given a string s representing an attendance record for a student
where each character signifies whether the student was absent, late, or present on that day.
The record only contains the following three characters:
- 'A': Absent.
- 'L': Late.
- 'P': Present.

The student is eligible for an attendance award if they meet both of the following criteria:
- The student was absent ('A') for strictly fewer than 2 days total.
- The student was never late ('L') for 3 or more consecutive days.

Return true if the student is eligible for an attendance award, or false otherwise.

Example 1:
Input: s = "PPALLP"
Output: true
Explanation: The student has fewer than 2 absences and was never late 3 or more consecutive days.

Example 2:
Input: s = "PPALLL"
Output: false
Explanation: The student was late 3 consecutive days in the last 3 days, so is not eligible for the award.

Constraints:
1 <= s.length <= 1000
s[i] is either 'A', 'L', or 'P'.
```

</details>

<details><summary>C</summary>

```c
bool checkRecord(char* s) {
    bool retVal = true;

    int sSize = strlen(s);
    int late = 0;
    int absent = 0;
    int i;
    for (i = 0; i < sSize; ++i) {
        if (s[i] == 'A') {
            late = 0;
            absent++;
            if (absent >= 2) {
                retVal = false;
                break;
            }
        } else if (s[i] == 'L') {
            late++;
            if (late >= 3) {
                retVal = false;
                break;
            }
        } else {
            late = 0;
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
    bool checkRecord(string s) {
        bool retVal = true;

        int late = 0;
        int absent = 0;
        for (char c : s) {
            if (c == 'A') {
                late = 0;
                absent++;
                if (absent >= 2) {
                    retVal = false;
                    break;
                }
            } else if (c == 'L') {
                late++;
                if (late >= 3) {
                    retVal = false;
                    break;
                }
            } else {
                late = 0;
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
    def checkRecord(self, s: str) -> bool:
        retVal = True

        late = 0
        absent = 0
        for c in s:
            if c == 'A':
                late = 0
                absent += 1
                if absent >= 2:
                    retVal = False
                    break
            elif c == 'L':
                late += 1
                if late >= 3:
                    retVal = False
                    break
            else:
                late = 0

        return retVal
```

</details>

## [647. Palindromic Substrings](https://leetcode.com/problems/palindromic-substrings/)

- [Official](https://leetcode.cn/problems/palindromic-substrings/solutions/379987/hui-wen-zi-chuan-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given a string s, return the number of palindromic substrings in it.

A string is a palindrome when it reads the same backward as forward.

A substring is a contiguous sequence of characters within the string.

Example 1:
Input: s = "abc"
Output: 3
Explanation: Three palindromic strings: "a", "b", "c".

Example 2:
Input: s = "aaa"
Output: 6
Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".

Constraints:
1 <= s.length <= 1000
s consists of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. How can we reuse a previously computed palindrome to compute a larger palindrome?
2. If "aba" is a palindrome, is “xabax” a palindrome? Similarly is “xabay” a palindrome?
3. Complexity based hint:
   If we use brute force and check whether for every start and end position a substring is a palindrome
   we have O(n^2) start - end pairs and O(n) palindromic checks.
   Can we reduce the time for palindromic checks to O(1) by reusing some previous computation?
```

</details>

</details>

<details><summary>C</summary>

```c
int countSubstrings(char* s) {
    int retVal = 0;

    int sSize = strlen(s);

    int left, right;
    int i;
    for (i = 0; i < (2 * sSize - 1); ++i) {
        left = i / 2;
        right = i / 2 + i % 2;
        while ((left >= 0) && (right < sSize) && (s[left] == s[right])) {
            --left;
            ++right;
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
    int countSubstrings(string s) {
        int retVal = 0;

        int sSize = s.size();

        for (int i = 0; i < (2 * sSize - 1); ++i) {
            int left = i / 2;
            int right = i / 2 + i % 2;
            while ((left >= 0) && (right < sSize) && (s[left] == s[right])) {
                --left;
                ++right;
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
    def countSubstrings(self, s: str) -> int:
        retVal = 0

        sSize = len(s)

        for i in range(2 * sSize - 1):
            left = i // 2
            right = (i // 2) + (i % 2)
            while ((left >= 0) and (right < sSize) and (s[left] == s[right])):
                left -= 1
                right += 1
                retVal += 1

        return retVal
```

</details>

## [686. Repeated String Match](https://leetcode.com/problems/repeated-string-match/)

- [Official](https://leetcode.cn/problems/repeated-string-match/solutions/1170235/zhong-fu-die-jia-zi-fu-chuan-pi-pei-by-l-vnye/)

<details><summary>Description</summary>

```text
Given two strings a and b, return the minimum number of times
you should repeat string a so that string b is a substring of it.
If it is impossible for b​​​​​​ to be a substring of a after repeating it, return -1.

Notice: string "abc" repeated 0 times is "", repeated 1 time is "abc" and repeated 2 times is "abcabc".

Example 1:
Input: a = "abcd", b = "cdabcdab"
Output: 3
Explanation: We return 3 because by repeating a three times "abcdabcdabcd", b is a substring of it.

Example 2:
Input: a = "a", b = "aa"
Output: 2

Constraints:
1 <= a.length, b.length <= 10^4
a and b consist of lowercase English letters.
```

</details>

<details><summary>C</summary>

```c
// https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
void kmp(int* next, char* pattern) {
    int patternSize = strlen(pattern);

    int j = 0;
    for (int i = 1; i < patternSize; ++i) {
        while ((j > 0) && (pattern[i] != pattern[j])) {
            j = next[j - 1];
        }

        if (pattern[i] == pattern[j]) {
            j++;
        }

        next[i] = j;
    }
}
int strStr(char* haystack, char* needle) {
    int retVal = -1;

    int needleSize = strlen(needle);
    if (needleSize == 0) {
        retVal = 0;
        return retVal;
    }
    int next[needleSize];
    memset(next, 0, sizeof(next));
    kmp(next, needle);

    int haystackSize = strlen(haystack);
    int haystackIdx = 0;
    int needleIdx = 0;
    while (haystackIdx - needleIdx < haystackSize) {
        while ((needleIdx > 0) && (haystack[haystackIdx % haystackSize] != needle[needleIdx])) {
            needleIdx = next[needleIdx - 1];
        }

        if (haystack[haystackIdx % haystackSize] == needle[needleIdx]) {
            ++needleIdx;
        }

        if (needleIdx == needleSize) {
            retVal = haystackIdx - needleSize + 1;
            break;
        }

        ++haystackIdx;
    }

    return retVal;
}
int repeatedStringMatch(char* a, char* b) {
    int retVal = -1;

    int aSize = strlen(a);
    int bSize = strlen(b);
    int index = strStr(a, b);
    if (index == -1) {
        retVal = -1;
    } else if (aSize - index >= bSize) {
        retVal = 1;
    } else {
        retVal = (bSize + index - aSize - 1) / aSize + 2;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    // https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
    void kmp(vector<int>& next, string pattern) {
        int patternSize = pattern.size();

        int j = 0;
        for (int i = 1; i < patternSize; ++i) {
            while ((j > 0) && (pattern[i] != pattern[j])) {
                j = next[j - 1];
            }

            if (pattern[i] == pattern[j]) {
                j++;
            }

            next[i] = j;
        }
    }
    int strStr(string haystack, string needle) {
        int retVal = -1;

        int needleSize = needle.size();
        if (needleSize == 0) {
            retVal = 0;
            return retVal;
        }
        vector<int> next(needleSize, 0);
        kmp(next, needle);

        int haystackSize = haystack.size();
        int haystackIdx = 0;
        int needleIdx = 0;
        while (haystackIdx - needleIdx < haystackSize) {
            while ((needleIdx > 0) && (haystack[haystackIdx % haystackSize] != needle[needleIdx])) {
                needleIdx = next[needleIdx - 1];
            }

            if (haystack[haystackIdx % haystackSize] == needle[needleIdx]) {
                ++needleIdx;
            }

            if (needleIdx == needleSize) {
                retVal = haystackIdx - needleSize + 1;
                break;
            }

            ++haystackIdx;
        }

        return retVal;
    }
    int repeatedStringMatch(string a, string b) {
        int retVal = -1;

        int aSize = a.size();
        int bSize = b.size();
        int index = strStr(a, b);
        if (index == -1) {
            retVal = -1;
        } else if (aSize - index >= bSize) {
            retVal = 1;
        } else {
            retVal = (bSize + index - aSize - 1) / aSize + 2;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    # https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
    def kmp(self, next: List[int], pattern: str) -> None:
        patternSize = len(pattern)

        j = 0
        for i in range(1, patternSize):
            while (j > 0) and (pattern[i] != pattern[j]):
                j = next[j-1]

            if pattern[i] == pattern[j]:
                j += 1

            next[i] = j

    def strstr(self, haystack: str, needle: str) -> int:
        retVal = -1

        needleSize = len(needle)
        if needleSize == 0:
            retVal = 0
            return retVal
        next = [0] * needleSize
        self.kmp(next, needle)

        haystackSize = len(haystack)
        haystackIdx = 0
        needleIdx = 0
        while haystackIdx - needleIdx < haystackSize:
            while (needleIdx > 0) and (haystack[haystackIdx % haystackSize] != needle[needleIdx]):
                needleIdx = next[needleIdx - 1]

            if haystack[haystackIdx % haystackSize] == needle[needleIdx]:
                needleIdx += 1

            if needleIdx == needleSize:
                retVal = haystackIdx - needleSize + 1
                break

            haystackIdx += 1

        return retVal

    def repeatedStringMatch(self, a: str, b: str) -> int:
        retVal = -1

        aSize = len(a)
        bSize = len(b)
        index = self.strstr(a, b)
        if index == -1:
            retVal = -1
        elif aSize - index >= bSize:
            retVal = 1
        else:
            retVal = (bSize + index - aSize - 1) // aSize + 2

        return retVal
```

</details>

## [709. To Lower Case](https://leetcode.com/problems/to-lower-case/)

<details><summary>Description</summary>

```text
Given a string s, return the string after replacing every uppercase letter with the same lowercase letter.

Example 1:
Input: s = "Hello"
Output: "hello"

Example 2:
Input: s = "here"
Output: "here"

Example 3:
Input: s = "LOVELY"
Output: "lovely"

Constraints:
1 <= s.length <= 100
s consists of printable ASCII characters.
```

</details>

<details><summary>C</summary>

```c
char* toLowerCase(char* s) {
    char* pRetVal = s;

    while (*s) {
        if (((*s) >= 65) && ((*s) <= 90)) {
            (*s) ^= 32;
        }
        ++s;
    }

    return pRetVal;
}
```

</details>

## [767. Reorganize String](https://leetcode.com/problems/reorganize-string/)  1681

- [Official](https://leetcode.com/problems/reorganize-string/editorial/)
- [Official](https://leetcode.cn/problems/reorganize-string/solutions/503231/zhong-gou-zi-fu-chuan-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given a string s, rearrange the characters of s so that any two adjacent characters are not the same.

Return any possible rearrangement of s or return "" if not possible.

Example 1:
Input: s = "aab"
Output: "aba"

Example 2:
Input: s = "aaab"
Output: ""

Constraints:
1 <= s.length <= 500
s consists of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Alternate placing the most common letters.
```

</details>

</details>

<details><summary>C</summary>

```c
typedef struct {
    char letters;
    int number;
} pair;
int compareStruct(const void* a, const void* b) {
    int pa = ((pair*)a)->number;
    int pb = ((pair*)b)->number;

    return (pa < pb);
}
char* reorganizeString(char* s) {
    char* pRetVal = NULL;

    int sSize = strlen(s);
    int returnSize = sSize + 1;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));

#define MAX_LETTERS (26)  // s consists of lowercase English letters.
    pair* pCount = malloc(MAX_LETTERS * sizeof(pair));
    if (pCount == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pCount, 0, (MAX_LETTERS * sizeof(pair)));
    int maxCount = -1;
    int idx;
    int i;
    for (i = 0; i < sSize; ++i) {
        idx = s[i] - 'a';  // s consists of lowercase English letters.
        pCount[idx].letters = s[i];
        pCount[idx].number += 1;
        maxCount = fmax(maxCount, pCount[idx].number);
    }

    if (maxCount > ((sSize + 1) / 2)) {
        free(pCount);
        pCount = NULL;
        return pRetVal;
    }

    qsort(pCount, MAX_LETTERS, sizeof(pair), compareStruct);
    idx = 0;
    int j;
    for (i = 0; i < MAX_LETTERS; ++i) {
        if (pCount[i].letters == 0) {
            continue;
        }

        for (j = 0; j < pCount[i].number; ++j) {
            pRetVal[idx] = pCount[i].letters;
            idx += 2;
            if (idx >= sSize) {
                idx = 1;
            }
        }
    }

    free(pCount);
    pCount = NULL;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string reorganizeString(string s) {
        string retVal;

        int maxCount = -1;
        unordered_map<char, int> count;
        for (auto c : s) {
            ++count[c];
            maxCount = max(maxCount, count[c]);
        }

        int sSize = s.size();
        if (maxCount > ((sSize + 1) / 2)) {
            return retVal;
        }

        string sortS = s;
        sort(sortS.begin(), sortS.end(),
             [&count](char a, char b) { return count[a] > count[b] || (count[a] == count[b] && a > b); });
        retVal = s;
        int idx = 0;
        for (auto c : sortS) {
            retVal[idx] = c;
            idx += 2;
            if (idx >= sSize) {
                idx = 1;
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
    def reorganizeString(self, s: str) -> str:
        retVal = ""

        count = defaultdict(int)
        for c in s:
            count[c] += 1
        count = sorted(count.items(), key=lambda kv: kv[1], reverse=True)

        sSize = len(s)
        if count[0][1] > ((sSize + 1) // 2):
            return retVal

        retVal = [""] * sSize
        idx = 0
        for key, value in count:
            for i in range(value):
                retVal[idx] = key
                idx += 2
                if idx >= sSize:
                    idx = 1
        retVal = "".join(retVal)

        return retVal
```

</details>

## [796. Rotate String](https://leetcode.com/problems/rotate-string/)  1167

<details><summary>Description</summary>

```text
Given two strings s and goal, return true if and only if s can become goal after some number of shifts on s.

A shift on s consists of moving the leftmost character of s to the rightmost position.
For example, if s = "abcde", then it will be "bcdea" after one shift.

Example 1:
Input: s = "abcde", goal = "cdeab"
Output: true

Example 2:
Input: s = "abcde", goal = "abced"
Output: false

Constraints:
1 <= s.length, goal.length <= 100
s and goal consist of lowercase English letters.
```

</details>

<details><summary>C</summary>

```c
bool rotateString(char* s, char* goal) {
    bool retVal = false;

    int lenS = strlen(s);
    int lenGoal = strlen(goal);
    if (lenS != lenGoal) {
        return retVal;
    }

    char buf[lenS + 1];
    int i;
    for (i = 0; i < lenS; ++i) {
        if (*(s + i) == *(goal)) {
            memset(buf, 0, sizeof(buf));
            strncpy(buf, s + i, lenS - i);
            strncat(buf, s, i);
            if (strcmp(buf, goal) == 0) {
                retVal = true;
                return retVal;
            }
        }
    }

    return retVal;
}
```

</details>

## [859. Buddy Strings](https://leetcode.com/problems/buddy-strings/)  1341

- [Official](https://leetcode.com/problems/buddy-strings/editorial/)
- [Official](https://leetcode.cn/problems/buddy-strings/solutions/1090079/qin-mi-zi-fu-chuan-by-leetcode-solution-yyis)

<details><summary>Description</summary>

```text
Given two strings s and goal,
return true if you can swap two letters in s so the result is equal to goal, otherwise, return false.

Swapping letters is defined as taking two indices i and j (0-indexed)
such that i != j and swapping the characters at s[i] and s[j].

For example, swapping at indices 0 and 2 in "abcd" results in "cbad".

Example 1:
Input: s = "ab", goal = "ba"
Output: true
Explanation: You can swap s[0] = 'a' and s[1] = 'b' to get "ba", which is equal to goal.

Example 2:
Input: s = "ab", goal = "ab"
Output: false
Explanation: The only letters you can swap are s[0] = 'a' and s[1] = 'b', which results in "ba" != goal.

Example 3:
Input: s = "aa", goal = "aa"
Output: true
Explanation: You can swap s[0] = 'a' and s[1] = 'a' to get "aa", which is equal to goal.


Constraints:
1 <= s.length, goal.length <= 2 * 10^4
s and goal consist of lowercase letters.
```

</details>

<details><summary>C</summary>

```c
bool buddyStrings(char* s, char* goal) {
    bool retVal = false;

    int sSize = strlen(s);
    int goalSize = strlen(goal);
    if (sSize != goalSize) {
        return retVal;
    }

    int i;

    int frequency[26];
    memset(frequency, 0, sizeof(frequency));
    if (strcmp(s, goal) == 0) {
        // If we have 2 same characters in string 's', we can swap them and still strings will remain equal.
        for (i = 0; i < sSize; ++i) {
            frequency[s[i] - 'a'] += 1;
            if (frequency[s[i] - 'a'] == 2) {
                retVal = true;
                return retVal;
            }
        }

        // Otherwise, if we swap any two chanacters it will make strings unequal.
        return retVal;
    }

    int firstIndex = -1;
    int secondIndex = -1;
    for (i = 0; i < sSize; ++i) {
        if (s[i] != goal[i]) {
            if (firstIndex == -1) {
                firstIndex = i;
            } else if (secondIndex == -1) {
                secondIndex = i;
            } else {
                // We have atleast 3 indices with differnet characters,
                // thus, we can never make strings equal with only one swap.
                return retVal;
            }
        }
    }

    if (secondIndex == -1) {
        // We can't swap if character at only one index is different.
        return retVal;
    }

    // All characters of both the string are same except two indices.
    retVal = ((s[firstIndex] == goal[secondIndex]) && (s[secondIndex] == goal[firstIndex]));

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    bool buddyStrings(string s, string goal) {
        bool retVal = false;

        int sSize = s.size();
        int goalSize = goal.size();
        if (sSize != goalSize) {
            return retVal;
        }

        if (s == goal) {
            // If we have 2 same characters in string 's', we can swap them and still strings will remain equal.
            vector<int> frequency(26, 0);
            for (auto& ch : s) {
                frequency[ch - 'a'] += 1;
                if (frequency[ch - 'a'] == 2) {
                    retVal = true;
                    return retVal;
                }
            }

            // Otherwise, if we swap any two chanacters it will make strings unequal.
            return retVal;
        }

        int firstIndex = -1;
        int secondIndex = -1;
        for (int i = 0; i < sSize; ++i) {
            if (s[i] != goal[i]) {
                if (firstIndex == -1) {
                    firstIndex = i;
                } else if (secondIndex == -1) {
                    secondIndex = i;
                } else {
                    // We have atleast 3 indices with differnet characters,
                    // thus, we can never make strings equal with only one swap.
                    return retVal;
                }
            }
        }

        if (secondIndex == -1) {
            // We can't swap if character at only one index is different.
            return retVal;
        }

        // All characters of both the string are same except two indices.
        retVal = ((s[firstIndex] == goal[secondIndex]) && (s[secondIndex] == goal[firstIndex]));

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def buddyStrings(self, s: str, goal: str) -> bool:
        retVal = False

        sSize = len(s)
        goalSize = len(goal)
        if sSize != goalSize:
            return retVal

        if s == goal:
            # If we have 2 same characters in string 's', we can swap them and still the strings will remain equal.
            frequency = [0] * 26
            for ch in s:
                frequency[ord(ch) - ord('a')] += 1
                if frequency[ord(ch) - ord('a')] == 2:
                    retVal = True
                    return retVal

            # Otherwise, if we swap any two characters, it will make the strings unequal.
            return retVal

        firstIndex = -1
        secondIndex = -1
        for i in range(sSize):
            if s[i] != goal[i]:
                if firstIndex == -1:
                    firstIndex = i
                elif secondIndex == -1:
                    secondIndex = i
                else:
                    # We have at least 3 indices with different characters,
                    # thus, we can never make the strings equal with only one swap.
                    return retVal

        if secondIndex == -1:
            # We can't swap if the character at only one index is different.
            return retVal

        # All characters of both strings are the same except two indices.
        retVal = (s[firstIndex] == goal[secondIndex]) and (s[secondIndex] == goal[firstIndex])

        return retVal
```

</details>

## [953. Verifying an Alien Dictionary](https://leetcode.com/problems/verifying-an-alien-dictionary/)  1299

- [Official](https://leetcode.com/problems/verifying-an-alien-dictionary/solutions/1130430/verifying-an-alien-dictionary/)
- [Official](https://leetcode.cn/problems/verifying-an-alien-dictionary/solutions/1496288/yan-zheng-wai-xing-yu-ci-dian-by-leetcod-jew7)

<details><summary>Description</summary>

```text
In an alien language, surprisingly, they also use English lowercase letters, but possibly in a different order.
The order of the alphabet is some permutation of lowercase letters.

Given a sequence of words written in the alien language, and the order of the alphabet,
return true if and only if the given words are sorted lexicographically in this alien language.

Example 1:
Input: words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
Output: true
Explanation: As 'h' comes before 'l' in this language, then the sequence is sorted.

Example 2:
Input: words = ["word","world","row"], order = "worldabcefghijkmnpqstuvxyz"
Output: false
Explanation: As 'd' comes after 'l' in this language, then words[0] > words[1], hence the sequence is unsorted.

Example 3:
Input: words = ["apple","app"], order = "abcdefghijklmnopqrstuvwxyz"
Output: false
Explanation: The first three characters "app" match, and the second string is shorter (in size.)
According to lexicographical rules "apple" > "app", because 'l' > '∅',
where '∅' is defined as the blank character which is less than any other character (More info).

Constraints:
1 <= words.length <= 100
1 <= words[i].length <= 20
order.length == 26
All characters in words[i] and order are English lowercase letters.
```

</details>

<details><summary>C</summary>

```c
bool isAlienSorted(char** words, int wordsSize, char* order) {
    bool retVal = false;

    int i, j;

// order.length == 26, All characters in words[i] and order are English lowercase letters.
#define MAX_ORDER_SIZE (26)
    int orderMap[MAX_ORDER_SIZE];

    int len = strlen(order);
    for (i = 0; i < len; ++i) {
        orderMap[order[i] - 'a'] = i;
    }

    for (i = 0; i < wordsSize - 1; ++i) {
        for (j = 0; j < strlen(words[i]); ++j) {
            // substring between words[i] and words[i+1] are the same,
            // but the length of words[i] is greater than words[i+1]
            if (j >= strlen(words[i + 1])) {
                return retVal;
            }

            if (words[i][j] == words[i + 1][j]) {
                continue;
            }

            if (orderMap[words[i][j] - 'a'] > orderMap[words[i + 1][j] - 'a']) {
                return retVal;
            }
            break;
        }
    }
    retVal = true;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
// https://leetcode.com/problems/verifying-an-alien-dictionary/solutions/203185/java-c-python-mapping-to-normal-order/
class Solution {
// order.length == 26, All characters in words[i] and order are English lowercase letters.
#define MAX_ORDER_SIZE (26)
   public:
    bool isAlienSorted(vector<string>& words, string order) {
        bool retVal = false;

        int orderMap[MAX_ORDER_SIZE];
        for (int i = 0; i < MAX_ORDER_SIZE; ++i) {
            orderMap[order[i] - 'a'] = i + 'a';
        }

        for (string& str : words) {
            for (char& c : str) {
                c = orderMap[c - 'a'];
            }
        }
        retVal = is_sorted(words.begin(), words.end());

        return retVal;
    }
};
```

</details>

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

</details>

<details><summary>C</summary>

```c
bool areAlmostEqual(char* s1, char* s2) {
    bool retVal = false;

    int count = 0;
    int record[2] = {0};

    int len = strlen(s1);
    int i;
    for (i=0; i<len; ++i) {
        if (s1[i] == s2[i]) {
            continue;
        }
        record[0] |= (1<<(s1[i]-'a'));
        record[1] |= (1<<(s2[i]-'a'));
        ++count;
    }

    if (count == 0) {
        retVal = true;
    }
    else if ((count == 2) && (record[0] == record[1])) {
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

        int count = 0;
        int record[2] = {0};
        for (long unsigned int i=0; i<s1.length(); ++i) {
            if (s1[i] == s2[i]) {
                continue;
            }
            record[0] |= (1<<(s1[i]-'a'));
            record[1] |= (1<<(s2[i]-'a'));
            ++count;
        }

        if (count == 0) {
            retVal = true;
        }
        else if ((count == 2) && (record[0] == record[1])) {
            retVal = true;
        }

        return retVal;
    }
};
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

## [2109. Adding Spaces to a String](https://leetcode.com/problems/adding-spaces-to-a-string/)  1315

<details><summary>Description</summary>

```text
You are given a 0-indexed string s and a 0-indexed integer array spaces
that describes the indices in the original string where spaces will be added.
Each space should be inserted before the character at the given index.

For example, given s = "EnjoyYourCoffee" and spaces = [5, 9], we place spaces before 'Y' and 'C',
which are at indices 5 and 9 respectively. Thus, we obtain "Enjoy Your Coffee".

Return the modified string after the spaces have been added.

Example 1:
Input: s = "LeetcodeHelpsMeLearn", spaces = [8,13,15]
Output: "Leetcode Helps Me Learn"
Explanation:
The indices 8, 13, and 15 correspond to the underlined characters in "LeetcodeHelpsMeLearn".
We then place spaces before those characters.

Example 2:
Input: s = "icodeinpython", spaces = [1,5,7,9]
Output: "i code in py thon"
Explanation:
The indices 1, 5, 7, and 9 correspond to the underlined characters in "icodeinpython".
We then place spaces before those characters.

Example 3:
Input: s = "spacing", spaces = [0,1,2,3,4,5,6]
Output: " s p a c i n g"
Explanation:
We are also able to place spaces before the first character of the string.

Constraints:
1 <= s.length <= 3 * 10^5
s consists only of lowercase and uppercase English letters.
1 <= spaces.length <= 3 * 10^5
0 <= spaces[i] <= s.length - 1
All the values of spaces are strictly increasing.
```

</details>

<details><summary>C</summary>

```c
char* addSpaces(char* s, int* spaces, int spacesSize) {
    char* pRetVal = NULL;

    int len = strlen(s);
    int modifiedLen = len + spacesSize + 1;
    pRetVal = malloc(modifiedLen);
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, modifiedLen);

    int index = 0;
    int i;
    for (i=0; i<len; ++i) {
        if (index < spacesSize) {
            if (i == spaces[index]) {
                *(pRetVal+i+index) = ' ';
                index++;
            }
        }
        *(pRetVal+i+index) = *(s+i);
    }

    return pRetVal;
}
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

## [2185. Counting Words With a Given Prefix](https://leetcode.com/problems/counting-words-with-a-given-prefix/)  1167

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
