# [Stack](https://en.wikipedia.org/wiki/Stack_(abstract_data_type))

- Monotonic Stack

## [3174. Clear Digits](https://leetcode.com/problems/clear-digits/)  1255

- [Official](https://leetcode.com/problems/clear-digits/editorial/)
- [Official](https://leetcode.cn/problems/clear-digits/solutions/2901101/qing-chu-shu-zi-by-leetcode-solution-66qk/)

<details><summary>Description</summary>

```text
You are given a string s.

Your task is to remove all digits by doing this operation repeatedly:
- Delete the first digit and the closest non-digit character to its left.

Return the resulting string after removing all digits.

Example 1:
Input: s = "abc"
Output: "abc"
Explanation:
There is no digit in the string.

Example 2:
Input: s = "cb34"
Output: ""
Explanation:
First, we apply the operation on s[2], and s becomes "c4".
Then we apply the operation on s[1], and s becomes "".

Constraints:
1 <= s.length <= 100
s consists only of lowercase English letters and digits.
The input is generated such that it is possible to delete all digits.
```

<details><summary>Hint</summary>

```text
1. Process string s from left to right, if s[i] is a digit, mark the nearest unmarked non-digit index to its left.
2. Delete all digits and all marked characters.
```

</details>

</details>

<details><summary>C</summary>

```c
char* clearDigits(char* s) {
    char* pRetVal = NULL;

    int sSize = strlen(s);
    int returnSize = sSize + 1;

    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));

    returnSize = 0;
    for (int i = 0; i < sSize; ++i) {
        if ((isdigit(s[i]) != 0) && (returnSize > 0)) {
            pRetVal[--returnSize] = 0;
        } else {
            pRetVal[returnSize++] = s[i];
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
    string clearDigits(string s) {
        string retVal;

        for (char c : s) {
            if (isdigit(c) != 0) {
                retVal.pop_back();
            } else {
                retVal += c;
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
    def clearDigits(self, s: str) -> str:
        retVal = ""

        for c in s:
            if c.isdigit():
                retVal = retVal[:-1]
            else:
                retVal += c

        return retVal
```

</details>
