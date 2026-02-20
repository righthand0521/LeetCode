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

- [Official](https://leetcode.cn/problems/count-and-say/solutions/1047325/wai-guan-shu-lie-by-leetcode-solution-9rt8/)

<details><summary>Description</summary>

```text
The count-and-say sequence is a sequence of digit strings defined by the recursive formula:
- countAndSay(1) = "1"
- countAndSay(n) is the run-length encoding of countAndSay(n - 1).

Run-length encoding (RLE) is a string compression method
that works by replacing consecutive identical characters (repeated 2 or more times)
with the concatenation of the character and the number marking the count of the characters (length of the run).
For example, to compress the string "3322251" we replace "33" with "23", replace "222" with "32",
replace "5" with "15" and replace "1" with "11".
Thus the compressed string becomes "23321511".

Given a positive integer n, return the nth element of the count-and-say sequence.

Example 1:
Input: n = 4
Output: "1211"
Explanation:
countAndSay(1) = "1"
countAndSay(2) = RLE of "1" = "11"
countAndSay(3) = RLE of "11" = "21"
countAndSay(4) = RLE of "21" = "1211"

Example 2:
Input: n = 1
Output: "1"
Explanation:
This is the base case.

Constraints:
1 <= n <= 30

Follow up: Could you solve it iteratively?
```

<details><summary>Hint</summary>

```text
1. Create a helper function that maps an integer to pairs of its digits and their frequencies.
   For example, if you call this function with "223314444411",
   then it maps it to an array of pairs [[2,2], [3,2], [1,1], [4,5], [1, 2]].
2. Create another helper function that takes the array of pairs and creates a new integer.
   For example, if you call this function with [[2,2], [3,2], [1,1], [4,5], [1, 2]],
   it should create "22"+"23"+"11"+"54"+"21" = "2223115421".
3. Now, with the two helper functions, you can start with "1" and call the two functions alternatively n-1 times.
   The answer is the last integer you will obtain.
```

</details>

</details>

<details><summary>C</summary>

```c
char* help(char* pSequence) {
    char* pRetVal = NULL;

    int len = strlen(pSequence);
    int returnSize = 2 * len * sizeof(char) + 1;
    pRetVal = (char*)malloc(returnSize);
    if (pRetVal == NULL) {
        perror("malloc");
        free(pSequence);
        return pRetVal;
    }
    memset(pRetVal, 0, returnSize);

    int idx = 0;
    char digit = pSequence[0];
    int count = 0;
    int i;
    for (i = 0; i < len; ++i) {
        if (digit != pSequence[i]) {
            idx += snprintf(pRetVal + idx, returnSize - idx, "%d%c", count, digit);
            digit = pSequence[i];
            count = 1;
            continue;
        }
        ++count;
    }
    idx += snprintf(pRetVal + idx, returnSize - idx, "%d%c", count, digit);
    free(pSequence);

    return pRetVal;
}
char* countAndSay(int n) {
    char* pRetVal = NULL;

    pRetVal = (char*)malloc(2 * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, 2 * sizeof(char));
    snprintf(pRetVal, 2 * sizeof(char), "%d", 1);

    if (n == 1) {
        return pRetVal;
    }

    int i;
    for (i = 2; i <= n; ++i) {
        pRetVal = help(pRetVal);
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string countAndSay(int n) {
        string retVal = "1";

        for (int i = 2; i <= n; ++i) {
            string curr = "";
            int start = 0;
            int pos = 0;
            int retValSize = retVal.size();
            while (pos < retValSize) {
                while ((pos < retValSize) && (retVal[pos] == retVal[start])) {
                    pos++;
                }
                curr += to_string(pos - start) + retVal[start];
                start = pos;
            }
            retVal = curr;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def countAndSay(self, n: int) -> str:
        retVal = "1"

        for i in range(n-1):
            curr = ""
            pos = 0
            start = 0
            retValSize = len(retVal)
            while pos < retValSize:
                while (pos < retValSize) and (retVal[pos] == retVal[start]):
                    pos += 1
                curr += str(pos - start) + retVal[start]
                start = pos
            retVal = curr

        return retVal
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

## [696. Count Binary Substrings](https://leetcode.com/problems/count-binary-substrings/)

- [Official](https://leetcode.com/problems/count-binary-substrings/editorial/)
- [Official](https://leetcode.cn/problems/count-binary-substrings/solutions/367704/ji-shu-er-jin-zhi-zi-chuan-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given a binary string s, return the number of non-empty substrings that have the same number of 0's and 1's,
and all the 0's and all the 1's in these substrings are grouped consecutively.

Substrings that occur multiple times are counted the number of times they occur.

Example 1:
Input: s = "00110011"
Output: 6
Explanation:
There are 6 substrings that have equal number of consecutive 1's and 0's: "0011", "01", "1100", "10", "0011", and "01".
Notice that some of these substrings repeat and are counted the number of times they occur.
Also, "00110011" is not a valid substring because all the 0's (and 1's) are not grouped together.

Example 2:
Input: s = "10101"
Output: 4
Explanation:
There are 4 substrings: "10", "01", "10", "01" that have equal number of consecutive 1's and 0's.

Constraints:
1 <= s.length <= 10^5
s[i] is either '0' or '1'.
```

<details><summary>Hint</summary>

```text
1. How many valid binary substrings exist in "000111", and how many in "11100"? What about "00011100"?
```

</details>

</details>

<details><summary>C</summary>

```c
int countBinarySubstrings(char* s) {
    int retVal = 0;

    int sSize = strlen(s);

    int current = 1;
    int previous = 0;
    for (int i = 1; i < sSize; ++i) {
        if (s[i] != s[i - 1]) {
            retVal += fmin(current, previous);
            previous = current;
            current = 1;
        } else {
            ++current;
        }
    }
    retVal += fmin(current, previous);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int countBinarySubstrings(string s) {
        int retVal = 0;

        int sSize = s.size();

        int current = 1;
        int previous = 0;
        for (int i = 1; i < sSize; ++i) {
            if (s[i] != s[i - 1]) {
                retVal += min(current, previous);
                previous = current;
                current = 1;
            } else {
                ++current;
            }
        }
        retVal += min(current, previous);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def countBinarySubstrings(self, s: str) -> int:
        retVal = 0

        sSize = len(s)

        current = 1
        previous = 0
        for i in range(1, sSize):
            if s[i] != s[i - 1]:
                retVal += min(previous, current)
                previous = current
                current = 1
            else:
                current += 1
        retVal += min(previous, current)

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

## [761. Special Binary String](https://leetcode.com/problems/special-binary-string/)  2292

- [Official](https://leetcode.cn/problems/special-binary-string/solutions/1728412/te-shu-de-er-jin-zhi-xu-lie-by-leetcode-sb7ry/)

<details><summary>Description</summary>

```text
Special binary strings are binary strings with the following two properties:
- The number of 0's is equal to the number of 1's.
- Every prefix of the binary string has at least as many 1's as 0's.

You are given a special binary string s.

A move consists of choosing two consecutive, non-empty, special substrings of s, and swapping them.
Two strings are consecutive if the last character of the first string is exactly one index
before the first character of the second string.

Return the lexicographically largest resulting string possible after applying the mentioned operations on the string.

Example 1:
Input: s = "11011000"
Output: "11100100"
Explanation: The strings "10" [occuring at s[1]] and "1100" [at s[3]] are swapped.
This is the lexicographically largest string possible after some number of swaps.

Example 2:
Input: s = "10"
Output: "10"

Constraints:
1 <= s.length <= 50
s[i] is either '0' or '1'.
s is a special binary string.
```

<details><summary>Hint</summary>

```text
1. Draw a line from (x, y) to (x+1, y+1) if we see a "1", else to (x+1, y-1).
   A special substring is just a line that starts and ends at the same y-coordinate,
   and that is the lowest y-coordinate reached.
   Call a mountain a special substring with no special prefixes -
   ie. only at the beginning and end is the lowest y-coordinate reached.
   If F is the answer function, and S has mountain decomposition M1,M2,M3,...,Mk,
   then the answer is: reverse_sorted(F(M1), F(M2), ..., F(Mk)).
   However, you'll also need to deal with the case that S is a mountain, such as 11011000 -> 11100100.
```

</details>

</details>

<details><summary>C</summary>

```c
int qsort_compareString(const void* str1, const void* str2) {
    // descending order
    return strcmp(*(char**)str2, *(char**)str1);
}
char* helper(char* s, int start, int end) {
    char* pRetVal = NULL;

    int len = end - start + 1;
    if (len <= 2) {
        pRetVal = (char*)malloc((len + 1) * sizeof(char));
        if (pRetVal == NULL) {
            perror("malloc");
            return pRetVal;
        }
        memset(pRetVal, 0, (len + 1) * sizeof(char));
        strncpy(pRetVal, s + start, len);
        pRetVal[len] = '\0';

        return pRetVal;
    }

    int cnt = 0;
    int left = start;
    char** subs = (char**)malloc(len * sizeof(char*));
    int subsSize = 0;
    char* helpReturn = NULL;
    int helpReturnSize = 0;
    for (int i = start; i <= end; ++i) {
        if (s[i] == '1') {
            ++cnt;
            continue;
        }

        --cnt;
        if (cnt != 0) {
            continue;
        }

        helpReturn = helper(s, left + 1, i - 1);
        if (helpReturn == NULL) {
            for (int j = 0; j < subsSize; ++j) {
                free(subs[j]);
                subs[j] = NULL;
            }
            free(subs);
            subs = NULL;
            return pRetVal;
        }
        helpReturnSize = strlen(helpReturn);

        subs[subsSize] = (char*)malloc(sizeof(char) * (helpReturnSize + 3));
        sprintf(subs[subsSize], "%s%s%s", "1", helpReturn, "0");
        free(helpReturn);
        helpReturn = NULL;
        left = i + 1;
        subsSize++;
    }
    qsort(subs, subsSize, sizeof(char*), qsort_compareString);

    pRetVal = (char*)malloc((len + 1) * sizeof(char));
    int pos = 0;
    for (int i = 0; i < subsSize; i++) {
        pos += sprintf(pRetVal + pos, "%s", subs[i]);
        free(subs[i]);
        subs[i] = NULL;
    }
    pRetVal[pos] = '\0';

    //
    free(subs);
    subs = NULL;

    return pRetVal;
}
char* makeLargestSpecial(char* s) {
    char* pRetVal = NULL;

    int sSize = strlen(s);
    pRetVal = helper(s, 0, sSize - 1);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string makeLargestSpecial(string s) {
        string retVal = "";

        int sSize = s.size();
        if (sSize <= 2) {
            retVal = s;
            return retVal;
        }

        int cnt = 0;
        int left = 0;
        vector<string> subs;
        for (int i = 0; i < sSize; ++i) {
            if (s[i] == '1') {
                cnt++;
                continue;
            }
            cnt--;
            if (cnt == 0) {
                subs.push_back("1" + makeLargestSpecial(s.substr(left + 1, i - left - 1)) + "0");
                left = i + 1;
            }
        }
        sort(subs.begin(), subs.end(), greater<string>());
        for (const auto& sub : subs) {
            retVal += sub;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def makeLargestSpecial(self, s: str) -> str:
        retVal = ""

        sSize = len(s)
        if sSize <= 2:
            retVal = s
            return retVal

        cnt = 0
        left = 0
        subs = list()
        for i, ch in enumerate(s):
            if ch == "1":
                cnt += 1
                continue
            cnt -= 1
            if cnt == 0:
                subs.append("1" + self.makeLargestSpecial(s[left+1:i]) + "0")
                left = i + 1
        subs.sort(reverse=True)
        retVal = "".join(subs)

        return retVal
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

- [Official](https://leetcode.com/problems/rotate-string/editorial/)
- [Official](https://leetcode.cn/problems/rotate-string/solutions/1398076/xuan-zhuan-zi-fu-chuan-by-leetcode-solut-4hlp/)

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

    int sSize = strlen(s);
    int goalSize = strlen(goal);
    if (sSize != goalSize) {
        return retVal;
    }

    char doubleS[sSize * 2 + 1];
    memset(doubleS, 0, sizeof(doubleS));
    snprintf(doubleS, sizeof(doubleS), "%s%s", s, s);
    if (strstr(doubleS, goal) != NULL) {
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
    bool rotateString(string s, string goal) {
        bool retVal = false;

        if (s.size() != goal.size()) {
            return retVal;
        }

        if ((s + s).find(goal) != string::npos) {
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
    def rotateString(self, s: str, goal: str) -> bool:
        retVal = False

        if len(s) != len(goal):
            return retVal

        if goal in s+s:
            retVal = True

        return retVal
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

## [916. Word Subsets](https://leetcode.com/problems/word-subsets/)  1624

- [Official](https://leetcode.com/problems/word-subsets/editorial/)
- [Official](https://leetcode.cn/problems/word-subsets/solutions/21315/dan-ci-zi-ji-by-leetcode/)

<details><summary>Description</summary>

```text
You are given two string arrays words1 and words2.

A string b is a subset of string a if every letter in b occurs in a including multiplicity.
- For example, "wrr" is a subset of "warrior" but is not a subset of "world".

A string a from words1 is universal if for every string b in words2, b is a subset of a.

Return an array of all the universal strings in words1. You may return the answer in any order.

Example 1:
Input: words1 = ["amazon","apple","facebook","google","leetcode"], words2 = ["e","o"]
Output: ["facebook","google","leetcode"]

Example 2:
Input: words1 = ["amazon","apple","facebook","google","leetcode"], words2 = ["l","e"]
Output: ["apple","google","leetcode"]

Constraints:
1 <= words1.length, words2.length <= 10^4
1 <= words1[i].length, words2[i].length <= 10
words1[i] and words2[i] consist only of lowercase English letters.
All the strings of words1 are unique.
```

</details>

<details><summary>C</summary>

```c
#define MAX_LETTER (26)
void count(char* word, int* pReturnCountArray) {
    int wordSize = strlen(word);
    for (int i = 0; i < wordSize; ++i) {
        pReturnCountArray[word[i] - 'a'] += 1;
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** wordSubsets(char** words1, int words1Size, char** words2, int words2Size, int* returnSize) {
    char** pRetVal = NULL;

    (*returnSize) = 0;

    int* pCountArray = (int*)malloc(sizeof(int) * MAX_LETTER);
    if (pCountArray == NULL) {
        return pRetVal;
    }
    int i, j;

    int bmax[MAX_LETTER];
    memset(bmax, 0, sizeof(bmax));
    for (i = 0; i < words2Size; ++i) {
        memset(pCountArray, 0, (sizeof(int) * MAX_LETTER));
        count(words2[i], pCountArray);
        for (j = 0; j < MAX_LETTER; ++j) {
            bmax[j] = fmax(bmax[j], pCountArray[j]);
        }
    }

    pRetVal = (char**)malloc(sizeof(char*) * words1Size);
    if (pRetVal == NULL) {
        free(pCountArray);
        pCountArray = NULL;
        return pRetVal;
    }

    int x, y;
    for (i = 0; i < words1Size; ++i) {
        memset(pCountArray, 0, (sizeof(int) * MAX_LETTER));
        count(words1[i], pCountArray);
        for (j = 0; j < MAX_LETTER; ++j) {
            x = pCountArray[j];
            y = bmax[j];
            if (x < y) {
                break;
            }
        }
        if (j == MAX_LETTER) {
            pRetVal[(*returnSize)++] = words1[i];
        }
    }

    free(pCountArray);
    pCountArray = NULL;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    int letter = 26;
    vector<int> count(string word) {
        vector<int> retVal(letter, 0);

        for (char c : word) {
            retVal[c - 'a'] += 1;
        }

        return retVal;
    }

   public:
    vector<string> wordSubsets(vector<string> &words1, vector<string> &words2) {
        vector<string> retVal;

        vector<int> bmax(letter, 0);
        for (string word : words2) {
            vector<int> countResult = count(word);
            for (int i = 0; i < letter; ++i) {
                bmax[i] = max(bmax[i], countResult[i]);
            }
        }

        for (string word : words1) {
            vector<int> countResult = count(word);
            int i;
            for (i = 0; i < letter; ++i) {
                int x = countResult[i];
                int y = bmax[i];
                if (x < y) {
                    break;
                }
            }
            if (i == letter) {
                retVal.emplace_back(word);
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
        self.letter = 26

    def count(self, word) -> List[int]:
        retVal = []

        retVal = [0] * self.letter
        for letter in word:
            retVal[ord(letter) - ord('a')] += 1

        return retVal

    def wordSubsets(self, words1: List[str], words2: List[str]) -> List[str]:
        retVal = []

        bmax = [0] * self.letter
        for word in words2:
            for i, c in enumerate(self.count(word)):
                bmax[i] = max(bmax[i], c)

        for word in words1:
            flag = True
            for x, y in zip(self.count(word), bmax):
                if x < y:
                    flag = False
                    break
            if flag == True:
                retVal.append(word)

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
