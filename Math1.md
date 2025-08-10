# Math

## [7. Reverse Integer](https://leetcode.com/problems/reverse-integer/)

- [Official](https://leetcode.com/problems/reverse-integer/editorial/)
- [Official](https://leetcode.cn/problems/reverse-integer/solutions/755611/zheng-shu-fan-zhuan-by-leetcode-solution-bccn/)

<details><summary>Description</summary>

```text
Given a signed 32-bit integer x, return x with its digits reversed.
If reversing x causes the value to go outside the signed 32-bit integer range [-2^31, 2^31 - 1], then return 0.

Assume the environment does not allow you to store 64-bit integers (signed or unsigned).

Example 1:
Input: x = 123
Output: 321

Example 2:
Input: x = -123
Output: -321

Example 3:
Input: x = 120
Output: 21

Constraints:
-2^31 <= x <= 2^31 - 1
```

</details>

<details><summary>C</summary>

```c
int reverse(int x) {
    int retVal = 0;

    long long reverseSum = 0;
    while (x != 0) {
        reverseSum = (reverseSum * 10) + (x % 10);
        x /= 10;
    }

    // If reversing x causes the value to go outside the signed 32 - bit integer range[-2 ^ 31, 2 ^ 31 - 1],
    // then return 0.
    if ((reverseSum < INT_MAX) && (reverseSum > INT_MIN)) {
        retVal = reverseSum;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int reverse(int x) {
        int retVal = 0;

        long long reverseSum = 0;
        while (x != 0) {
            reverseSum = (reverseSum * 10) + (x % 10);
            x /= 10;
        }

        // If reversing x causes the value to go outside the signed 32 - bit integer range[-2 ^ 31, 2 ^ 31 - 1],
        // then return 0.
        if ((reverseSum < numeric_limits<int>::max()) && (reverseSum > numeric_limits<int>::min())) {
            retVal = reverseSum;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def reverse(self, x: int) -> int:
        retVal = 0

        absoluteValue = abs(x)
        while absoluteValue > 0:
            retVal = (retVal * 10) + (absoluteValue % 10)
            absoluteValue //= 10
        if x < 0:
            retVal = -(retVal)

        # // If reversing x causes the value to go outside the signed 32 - bit integer range[-2 ^ 31, 2 ^ 31 - 1],
        # // then return 0.
        if (retVal > (2**31-1)) or (retVal < (-2**31)):
            retVal = 0

        return retVal
```

</details>

## [9. Palindrome Number](https://leetcode.com/problems/palindrome-number/)

<details><summary>Description</summary>

```text
Given an integer x, return true if x is palindrome integer.

An integer is a palindrome when it reads the same backward as forward.
For example, 121 is a palindrome while 123 is not.

Example 1:
Input: x = 121
Output: true
Explanation: 121 reads as 121 from left to right and from right to left.

Example 2:
Input: x = -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.

Example 3:
Input: x = 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.

Constraints:
-2^31 <= x <= 2^31 - 1

Follow up: Could you solve it without converting the integer to a string?
```

<details><summary>Hint</summary>

```text
1. Beware of overflow when you reverse the integer.
```

</details>

</details>

<details><summary>C</summary>

```c
bool isPalindrome(int x) {
    bool retVal = false;

    if (x < 0) {
        return retVal;
    }

    // Constraints: -2 ^ 31 <= x <= 2 ^ 31 - 1
    long original = x;
    long palindrome = 0;
    while (x > 0) {
        palindrome *= 10;
        palindrome += (x % 10);
        x /= 10;
    }

    if (original == palindrome) {
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
    bool isPalindrome(int x) {
        bool retVal = false;

        if (x < 0) {
            return retVal;
        }

        // Constraints: -2 ^ 31 <= x <= 2 ^ 31 - 1
        long original = x;
        long palindrome = 0;
        while (x > 0) {
            palindrome *= 10;
            palindrome += (x % 10);
            x /= 10;
        }

        if (original == palindrome) {
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
    def isPalindrome(self, x: int) -> bool:
        retVal = False

        if x < 0:
            return retVal

        original = x
        palindrome = 0
        while x > 0:
            palindrome *= 10
            palindrome += x % 10
            x //= 10

        if original == palindrome:
            retVal = True

        return retVal
```

</details>

## [43. Multiply Strings](https://leetcode.com/problems/multiply-strings/)

- [Official](https://leetcode.com/problems/multiply-strings/editorial/)
- [Official](https://leetcode.cn/problems/multiply-strings/solutions/372098/zi-fu-chuan-xiang-cheng-by-leetcode-solution/)

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
char* multiply(char* num1, char* num2) {
    char* pRetVal = NULL;

    if ((strcmp(num1, "0") == 0) || (strcmp(num2, "0") == 0)) {
        pRetVal = (char*)malloc(2 * sizeof(char));
        if (pRetVal == NULL) {
            perror("malloc");
            return pRetVal;
        }
        memset(pRetVal, 0, 2 * sizeof(char));
        pRetVal[0] = '0';

        return pRetVal;
    }

    int num1Size = strlen(num1);
    int num2Size = strlen(num2);
    int returnBufSize = num1Size + num2Size;
    int returnBuf[returnBufSize];
    memset(returnBuf, 0, sizeof(returnBuf));
    int multiplicand, multiplier, product, carry;
    int i, j;
    for (i = num1Size - 1; i >= 0; --i) {
        multiplicand = num1[i] - '0';
        for (j = num2Size - 1; j >= 0; --j) {
            multiplier = num2[j] - '0';
            product = multiplicand * multiplier;
            returnBuf[i + j + 1] = returnBuf[i + j + 1] + product;
            carry = returnBuf[i + j + 1] / 10;
            returnBuf[i + j + 1] = (returnBuf[i + j + 1] % 10);
            returnBuf[i + j] = returnBuf[i + j] + carry;
        }
    }

    int returnSize = num1Size + num2Size + 1;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));
    returnSize = 0;
    if (returnBuf[0] != 0) {
        pRetVal[returnSize++] += returnBuf[0] + '0';
    }
    for (i = 1; i < returnBufSize; ++i) {
        pRetVal[returnSize++] += returnBuf[i] + '0';
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string multiply(string num1, string num2) {
        string retVal = "";

        if ((num1 == "0") || (num2 == "0")) {
            retVal = "0";
            return retVal;
        }

        int num1Size = num1.size();
        int num2Size = num2.size();
        int returnSize = num1Size + num2Size;
        vector<int> returnBuf(returnSize, 0);
        for (int i = num1Size - 1; i >= 0; --i) {
            int multiplicand = num1[i] - '0';
            for (int j = num2Size - 1; j >= 0; --j) {
                int multiplier = num2[j] - '0';
                int product = multiplicand * multiplier;
                returnBuf[i + j + 1] = returnBuf[i + j + 1] + product;
                int carry = (returnBuf[i + j + 1]) / 10;
                returnBuf[i + j + 1] = (returnBuf[i + j + 1] % 10);
                returnBuf[i + j] = returnBuf[i + j] + carry;
            }
        }

        if (returnBuf[0] != 0) {
            retVal += to_string(returnBuf[0]);
        }
        for (int i = 1; i < returnSize; ++i) {
            retVal += to_string(returnBuf[i]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def multiply(self, num1: str, num2: str) -> str:
        retVal = ""

        if (num1 == "0") or (num2 == "0"):
            retVal = "0"
            return retVal

        num1Size = len(num1)
        num2Size = len(num2)
        returnSize = num1Size + num2Size
        returnBuf = [0] * returnSize
        for i in range(num1Size - 1, -1, -1):
            multiplicand = int(num1[i])
            for j in range(num2Size - 1, -1, -1):
                multiplier = int(num2[j])
                product = multiplicand * multiplier
                returnBuf[i + j + 1] = int(returnBuf[i + j + 1]) + product
                carry = int(returnBuf[i + j + 1]) // 10
                returnBuf[i + j + 1] = int(int(returnBuf[i + j + 1]) % 10)
                returnBuf[i + j] = int(returnBuf[i + j]) + carry

        if returnBuf[0] != 0:
            retVal += str(returnBuf[0])
        for i in returnBuf[1:]:
            retVal += str(i)

        return retVal
```

</details>

## [50. Pow(x, n)](https://leetcode.com/problems/powx-n/)

- [Official](https://leetcode.com/problems/powx-n/editorial/)
- [Official](https://leetcode.cn/problems/powx-n/solutions/238559/powx-n-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Implement pow(x, n), which calculates x raised to the power n (i.e., x^n).

Example 1:
Input: x = 2.00000, n = 10
Output: 1024.00000

Example 2:
Input: x = 2.10000, n = 3
Output: 9.26100

Example 3:
Input: x = 2.00000, n = -2
Output: 0.25000
Explanation: 2^-2 = 1/2^2 = 1/4 = 0.25

Constraints:
-100.0 < x < 100.0
-2^31 <= n <= 2^31-1
-10^4 <= x^n <= 10^4
```

</details>

<details><summary>C</summary>

```c
double myPow(double x, int n) {
    double retVal = 1;

    /* https://en.wikipedia.org/wiki/Exponentiation_by_squaring
     *
     * func binaryExp(x, n):
     *  if n == 0: return 1.0
     *  if n < 0: return 1.0 / binaryExp(x, -n)
     *  // Binary exponentiation steps.
     *  if n is odd: return x * binaryExp(x * x, (n - 1) / 2)
     *  otherwise: return binaryExp(x * x, n / 2)
     */

    if ((x == (double)0) || (x == (double)1)) {
        retVal = x;
        return retVal;
    } else if (x == (double)(-1)) {
        retVal = (n % 2 == 0) ? 1 : -1;
        return retVal;
    }

    x = (n > 0) ? x : 1 / x;
    if (n == INT_MIN) {
        n += 1;
    }

    int times = abs(n);
    while (times > 0) {
        if (times % 2 == 1) {
            retVal *= x;
            --times;
        }
        if (retVal == (double)0) {
            break;
        }

        x *= x;
        times >>= 1;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    double myPow(double x, int n) {
        double retVal = 1;

        /* https://en.wikipedia.org/wiki/Exponentiation_by_squaring
         *
         * func binaryExp(x, n):
         *  if n == 0: return 1.0
         *  if n < 0: return 1.0 / binaryExp(x, -n)
         *  // Binary exponentiation steps.
         *  if n is odd: return x * binaryExp(x * x, (n - 1) / 2)
         *  otherwise: return binaryExp(x * x, n / 2)
         */

        if ((x == (double)0) || (x == (double)1)) {
            retVal = x;
            return retVal;
        } else if (x == (double)(-1)) {
            retVal = (n % 2 == 0) ? 1 : -1;
            return retVal;
        }

        x = (n > 0) ? x : 1 / x;
        if (n == numeric_limits<int>::min()) {
            n += 1;
        }

        int times = abs(n);
        while (times > 0) {
            if (times % 2 == 1) {
                retVal *= x;
                --times;
            }
            if (retVal == (double)0) {
                break;
            }

            x *= x;
            times >>= 1;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def myPow(self, x: float, n: int) -> float:
        retVal = 1

        # /* https://en.wikipedia.org/wiki/Exponentiation_by_squaring
        #  *
        #  * func binaryExp(x, n):
        #  *  if n == 0: return 1.0
        #  *  if n < 0: return 1.0 / binaryExp(x, -n)
        #  *  // Binary exponentiation steps.
        #  *  if n is odd: return x * binaryExp(x * x, (n - 1) / 2)
        #  *  otherwise: return binaryExp(x * x, n / 2)
        #  */

        if (x == 0) or (x == 1):
            retVal = x
            return retVal
        elif x == -1:
            retVal = 1 if n % 2 == 0 else -1
            return retVal

        x = x if n > 0 else 1/x

        times = abs(n)
        while (times > 0):
            if times % 2 == 1:
                retVal *= x
                times -= 1
            if retVal == 0:
                break

            x *= x
            times = times >> 1

        return retVal
```

</details>

## [60. Permutation Sequence](https://leetcode.com/problems/permutation-sequence/)

<details><summary>Description</summary>

```text
The set [1, 2, 3, ..., n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order, we get the following sequence for n = 3:
 1. "123"
 2. "132"
 3. "213"
 4. "231"
 5. "312"
 6. "321"

Given n and k, return the kth permutation sequence.

Example 1:
Input: n = 3, k = 3
Output: "213"

Example 2:
Input: n = 4, k = 9
Output: "2314"

Example 3:
Input: n = 3, k = 1
Output: "123"

Constraints:
1 <= n <= 9
1 <= k <= n!
```

</details>

<details><summary>C</summary>

```c
int permutation(int n)
{
    int retVal = 1;

    int i;
    for (i=1; i<=n; ++i)
    {
        retVal *= i;
    }

    return retVal;
}

char * getPermutation(int n, int k){
    char* pRetVal = (char*)malloc((n+1)*sizeof(char));
    if (pRetVal == NULL)
    {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (n+1)*sizeof(char));

    char buf[n+1];
    memset(buf, 0, n+1);
    int idx;
    for (idx=0; idx<n; ++idx)
    {
        buf[idx] = (idx + 1) + '0';
    }

    int sum = 0;
    int interval;
    int i, j;
    for (i=1; i<=n-1; ++i)
    {
        interval = permutation(n-i);
        for (j=1; j<=n; ++j)
        {
            sum += interval;
            if (sum >= k)
            {
                sum -= interval;
                break;
            }
        }
        if (sum >= k)
        {
            break;
        }
        // printf("(%d,%d)[%6d][%6d]\n", i, j, interval, sum);

        pRetVal[i-1] = buf[j-1];
        for (idx=j-1; idx<n; ++idx)
        {
            buf[idx] = buf[idx+1];
        }
    }
    pRetVal[i-1] = buf[0];

    return pRetVal;
}
```

</details>

## [66. Plus One](https://leetcode.com/problems/plus-one/)

- [Official](https://leetcode.cn/problems/plus-one/solutions/1057162/jia-yi-by-leetcode-solution-2hor/)

<details><summary>Description</summary>

```text
You are given a large integer represented as an integer array digits,
where each digits[i] is the ith digit of the integer.
The digits are ordered from most significant to least significant in left-to-right order.
The large integer does not contain any leading 0's.

Increment the large integer by one and return the resulting array of digits.

Example 1:
Input: digits = [1,2,3]
Output: [1,2,4]
Explanation: The array represents the integer 123.
Incrementing by one gives 123 + 1 = 124.
Thus, the result should be [1,2,4].

Example 2:
Input: digits = [4,3,2,1]
Output: [4,3,2,2]
Explanation: The array represents the integer 4321.
Incrementing by one gives 4321 + 1 = 4322.
Thus, the result should be [4,3,2,2].

Example 3:
Input: digits = [9]
Output: [1,0]
Explanation: The array represents the integer 9.
Incrementing by one gives 9 + 1 = 10.
Thus, the result should be [1,0].

Constraints:
1 <= digits.length <= 100
0 <= digits[i] <= 9
digits does not contain any leading 0's.
```

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* plusOne(int* digits, int digitsSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int*)malloc((digitsSize + 1) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, ((digitsSize + 1) * sizeof(int)));
    memcpy(pRetVal, digits, (digitsSize * sizeof(int)));
    (*returnSize) = digitsSize;

    int i;
    for (i = digitsSize - 1; i >= 0; --i) {
        pRetVal[i] += 1;
        if (pRetVal[i] != 10) {
            return pRetVal;
        }
        pRetVal[i] = 0;
    }
    memset(pRetVal, 0, ((digitsSize + 1) * sizeof(int)));
    pRetVal[0] = 1;
    (*returnSize) = digitsSize + 1;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> plusOne(vector<int>& digits) {
        vector<int> retVal = digits;

        int digitsSize = digits.size();
        for (int i = digitsSize - 1; i >= 0; --i) {
            retVal[i] += 1;
            if (retVal[i] != 10) {
                return retVal;
            }
            retVal[i] = 0;
        }
        retVal.resize(digitsSize + 1);
        retVal[0] = 1;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def plusOne(self, digits: List[int]) -> List[int]:
        retVal = digits

        digitsSize = len(digits)
        for i in range(digitsSize-1, -1, -1):
            retVal[i] += 1
            if retVal[i] != 10:
                return retVal
            retVal[i] %= 10
        retVal = [1] + retVal

        return retVal
```

</details>

## [69. Sqrt(x)](https://leetcode.com/problems/sqrtx/)

- [Official](https://leetcode.cn/problems/sqrtx/solutions/238553/x-de-ping-fang-gen-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given a non-negative integer x, compute and return the square root of x.

Since the return type is an integer, the decimal digits are truncated,
and only the integer part of the result is returned.

Note: You are not allowed to use any built-in exponent function or operator, such as pow(x, 0.5) or x ** 0.5.

Example 1:
Input: x = 4
Output: 2

Example 2:
Input: x = 8
Output: 2
Explanation: The square root of 8 is 2.82842..., and since the decimal part is truncated, 2 is returned.

Constraints:
0 <= x <= 2^31 - 1
```

<details><summary>Hint</summary>

```text
1. Try exploring all integers. (Credits: @annujoshi)
2. Use the sorted property of integers to reduced the search space. (Credits: @annujoshi)
```

</details>

</details>

<details><summary>C</summary>

```c
int mySqrt(int x) {
    int retVal = 0;

    // Integer square root: Newton's method to find a solution for the equation x^2 - n = 0
    long long root = x;
    while (root * root > x) {
        root = (root + x / root) / 2;
    }
    retVal = (int)root;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int mySqrt(int x) {
        int retVal = 0;

        // Integer square root: Newton's method to find a solution for the equation x^2 - n = 0
        long long root = x;
        while (root * root > x) {
            root = (root + x / root) / 2;
        }
        retVal = (int)root;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def mySqrt(self, x: int) -> int:
        retVal = 0

        # Integer square root: Newton's method to find a solution for the equation x^2 - n = 0
        retVal = x
        while retVal * retVal > x:
            retVal = (retVal + x // retVal) // 2

        return retVal
```

</details>

## [168. Excel Sheet Column Title](https://leetcode.com/problems/excel-sheet-column-title/)

- [Official](https://leetcode.com/problems/excel-sheet-column-title/editorial/)
- [Official](https://leetcode.cn/problems/excel-sheet-column-title/solutions/849363/excelbiao-lie-ming-cheng-by-leetcode-sol-hgj4/)

<details><summary>Description</summary>

```text
Given an integer columnNumber, return its corresponding column title as it appears in an Excel sheet.

For example:

A -> 1
B -> 2
C -> 3
...
Z -> 26
AA -> 27
AB -> 28
...

Example 1:
Input: columnNumber = 1
Output: "A"

Example 2:
Input: columnNumber = 28
Output: "AB"

Example 3:
Input: columnNumber = 701
Output: "ZY"

Constraints:
1 <= columnNumber <= 2^31 - 1
```

</details>

<details><summary>C</summary>

```c
char* convertToTitle(int columnNumber) {
    char* pRetVal = NULL;

    int returnSize = 8;  // 1 <= columnNumber <= 2^31 - 1
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));

    char buf[returnSize];
    memset(buf, 0, sizeof(buf));
    int idx = 0;
    int multiple = 26;
    int remainder;
    while (columnNumber > 0) {
        --columnNumber;
        remainder = columnNumber % multiple;
        buf[idx++] = remainder + 'A';
        columnNumber /= multiple;
    }
    returnSize = 0;
    while (idx > 0) {
        pRetVal[returnSize++] = buf[--idx];
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string convertToTitle(int columnNumber) {
        string retVal;

        int multiple = 26;
        while (columnNumber > 0) {
            --columnNumber;
            int remainder = columnNumber % multiple;
            retVal += remainder + 'A';
            columnNumber /= multiple;
        }
        reverse(retVal.begin(), retVal.end());

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def convertToTitle(self, columnNumber: int) -> str:
        retVal = ""

        multiple = 26
        while columnNumber > 0:
            columnNumber -= 1
            remainder = columnNumber % multiple
            retVal = chr(remainder + ord("A")) + retVal
            columnNumber //= multiple

        return retVal
```

</details>

## [171. Excel Sheet Column Number](https://leetcode.com/problems/excel-sheet-column-number/)

- [Official](https://leetcode.cn/problems/excel-sheet-column-number/solutions/849149/excelbiao-lie-xu-hao-by-leetcode-solutio-r29l/)

<details><summary>Description</summary>

```text
Given a string columnTitle that represents the column title as appears in an Excel sheet,
return its corresponding column number.

For example:
A -> 1
B -> 2
C -> 3
...
Z -> 26
AA -> 27
AB -> 28
...

Example 1:
Input: columnTitle = "A"
Output: 1

Example 2:
Input: columnTitle = "AB"
Output: 28

Example 3:
Input: columnTitle = "ZY"
Output: 701

Constraints:
1 <= columnTitle.length <= 7
columnTitle consists only of uppercase English letters.
columnTitle is in the range ["A", "FXSHRXW"].
```

</details>

<details><summary>C</summary>

```c
int titleToNumber(char *columnTitle) {
    int retVal = 0;

    int multiple = 26;
    int columnTitleSize = strlen(columnTitle);
    int i;
    for (i = 0; i < columnTitleSize; ++i) {
        retVal *= multiple;
        retVal += columnTitle[i] - 'A' + 1;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int titleToNumber(string columnTitle) {
        int retVal = 0;

        int multiple = 26;
        int columnTitleSize = columnTitle.size();
        for (int i = 0; i < columnTitleSize; ++i) {
            retVal *= multiple;
            retVal += columnTitle[i] - 'A' + 1;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def titleToNumber(self, columnTitle: str) -> int:
        retVal = 0

        multiple = 26
        for char in columnTitle:
            retVal *= multiple
            retVal += (ord(char) - ord("A") + 1)

        return retVal
```

</details>

## [172. Factorial Trailing Zeroes](https://leetcode.com/problems/factorial-trailing-zeroes/)

- [Official](https://leetcode.cn/problems/factorial-trailing-zeroes/solutions/1360892/jie-cheng-hou-de-ling-by-leetcode-soluti-1egk/)

<details><summary>Description</summary>

```text
Given an integer n, return the number of trailing zeroes in n!.

Note that n! = n * (n - 1) * (n - 2) * ... * 3 * 2 * 1.

Example 1:
Input: n = 3
Output: 0
Explanation: 3! = 6, no trailing zero.

Example 2:
Input: n = 5
Output: 1
Explanation: 5! = 120, one trailing zero.

Example 3:
Input: n = 0
Output: 0

Constraints:
0 <= n <= 10^4

Follow up: Could you write a solution that works in logarithmic time complexity?
```

</details>

<details><summary>C</summary>

```c
int trailingZeroes(int n) {
    int retVal = 0;

    while (n >= 5) {
        retVal += (n / 5);
        n /= 5;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int trailingZeroes(int n) {
        int retVal = 0;

        while (n >= 5) {
            retVal += (n / 5);
            n /= 5;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def trailingZeroes(self, n: int) -> int:
        retVal = 0

        while n >= 5:
            retVal += n//5
            n //= 5

        return retVal
```

</details>

## [204. Count Primes](https://leetcode.com/problems/count-primes/)

<details><summary>Description</summary>

```text
Given an integer n, return the number of prime numbers that are strictly less than n.

Example 1:
Input: n = 10
Output: 4
Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.

Example 2:
Input: n = 0
Output: 0

Example 3:
Input: n = 1
Output: 0

Constraints:
0 <= n <= 5 * 10^6
```

</details>

<details><summary>C</summary>

```c
int countPrimes(int n) {
    int retVal = 0;

    if ((n==0) || (n==1)) {
        return retVal;
    }

    int i, j;

    /* https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
     *
     *  input: an integer n > 1.
     *  output: all prime numbers from 2 through n.
     *
     *  let A be an array of Boolean values, indexed by integers 2 to n, initially all set to true.
     *  for i = 2, 3, 4, ..., not exceeding √n do
     *      if A[i] is true
     *          for j = i^2, i^2+i, i^2+2i, i^2+3i, ..., not exceeding n do
     *              set A[j] := false
     *
     *  return all i such that A[i] is true.
     */
    bool isPrime[n+1];
    memset(isPrime, true, sizeof(isPrime));
    isPrime[0] = false;
    isPrime[1] = false;
    for (i=2; i*i<=n; ++i) {
        if (isPrime[i] == true) {
            for (j=i*i; j<=n; j+=i) {
                isPrime[j] = false;
            }
        }

    }

    for (i=0; i<sizeof(isPrime)-1; ++i) {
        if (isPrime[i] == true) {
            ++retVal;
        }
    }

    return retVal;
}
```

</details>

## [223. Rectangle Area](https://leetcode.com/problems/rectangle-area/)

- [Official](https://leetcode.com/problems/rectangle-area/solutions/2721023/rectangle-area/)
- [Official](https://leetcode.cn/problems/rectangle-area/solutions/1024639/ju-xing-mian-ji-by-leetcode-solution-xzbl/)

<details><summary>Description</summary>

```text
Given the coordinates of two rectilinear rectangles in a 2D plane, return the total area covered by the two rectangles.
The first rectangle is defined by its bottom-left corner (ax1, ay1) and its top-right corner (ax2, ay2).
The second rectangle is defined by its bottom-left corner (bx1, by1) and its top-right corner (bx2, by2).

Example 1:
Input: ax1 = -3, ay1 = 0, ax2 = 3, ay2 = 4, bx1 = 0, by1 = -1, bx2 = 9, by2 = 2
Output: 45

Example 2:
Input: ax1 = -2, ay1 = -2, ax2 = 2, ay2 = 2, bx1 = -2, by1 = -2, bx2 = 2, by2 = 2
Output: 16

Constraints:
-10^4 <= ax1 <= ax2 <= 10^4
-10^4 <= ay1 <= ay2 <= 10^4
-10^4 <= bx1 <= bx2 <= 10^4
-10^4 <= by1 <= by2 <= 10^4
```

</details>

<details><summary>C</summary>

```c
#define MAX(a,b)    (((a)>(b))?(a):(b))
#define MIN(a,b)    (((a)<(b))?(a):(b))

int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
    int retVal = 0;

    int aSpace = (ax2 - ax1) * (ay2 - ay1);
    int bSpace = (bx2 - bx1) * (by2 - by1);

    int xOverlap = MIN(ax2, bx2) - MAX(ax1, bx1);
    int yOverlap = MIN(ay2, by2) - MAX(ay1, by1);
    int overlapSpace = 0;
    if ((xOverlap > 0) && (yOverlap > 0)) {
        overlapSpace = xOverlap * yOverlap;
    }
    retVal = aSpace + bSpace - overlapSpace;

    return retVal;
}
```

</details>

## [231. Power of Two](https://leetcode.com/problems/power-of-two/)

- [Official](https://leetcode.cn/problems/power-of-two/solutions/796201/2de-mi-by-leetcode-solution-rny3/)

<details><summary>Description</summary>

```text
Given an integer n, return true if it is a power of two. Otherwise, return false.

An integer n is a power of two, if there exists an integer x such that n == 2^x.

Example 1:
Input: n = 1
Output: true
Explanation: 2^0 = 1

Example 2:
Input: n = 16
Output: true
Explanation: 2^4 = 16

Example 3:
Input: n = 3
Output: false

Constraints:
-2^31 <= n <= 2^31 - 1

Follow up: Could you solve it without loops/recursion?
```

</details>

<details><summary>C</summary>

```c
bool isPowerOfTwo(int n) {
    bool retVal = false;

    if (n <= 0) {
        return retVal;
    }

#if (0)
    if ((n & (n - 1)) == 0) {
        retVal = true;
    }
#else
    /* n = 2 ^ x
     * = > log(n) = x * log(2)
     * = > x = log(n) / log(2)
     */
    double x = log10(n) / log10(2);
    if (x - (int)x == 0) {
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
   public:
    bool isPowerOfTwo(int n) {
        bool retVal = false;

        if (n <= 0) {
            return retVal;
        }

#if (0)
        if ((n & (n - 1)) == 0) {
            retVal = true;
        }
#else
        /* n = 2 ^ x
         * = > log(n) = x * log(2)
         * = > x = log(n) / log(2)
         */
        double x = log10(n) / log10(2);
        if (x - (int)x == 0) {
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
    def __init__(self) -> None:
        self.method = 2

    def isPowerOfTwo(self, n: int) -> bool:
        retVal = False

        if n <= 0:
            return retVal

        if self.method == 1:
            if (n & (n - 1)) == 0:
                retVal = True
        elif self.method == 2:
            # /* n = 2 ^ x
            # * = > log(n) = x * log(2)
            # * = > x = log(n) / log(2)
            # */
            x = log10(n) / log10(2)
            if x - int(x) == 0:
                retVal = True

        return retVal
```

</details>

## [258. Add Digits](https://leetcode.com/problems/add-digits/)

- [Official](https://leetcode.com/problems/add-digits/editorial/)
- [Official](https://leetcode.cn/problems/add-digits/solutions/1301157/ge-wei-xiang-jia-by-leetcode-solution-u4kj/)

<details><summary>Description</summary>

```text
Given an integer num, repeatedly add all its digits until the result has only one digit, and return it.

Example 1:
Input: num = 38
Output: 2
Explanation: The process is
38 --> 3 + 8 --> 11
11 --> 1 + 1 --> 2
Since 2 has only one digit, return it.

Example 2:
Input: num = 0
Output: 0

Constraints:
0 <= num <= 2^31 - 1
```

<details><summary>Hint</summary>

```text
1. A naive implementation of the above process is trivial. Could you come up with other methods?
2. What are all the possible results?
3. How do they occur, periodically or randomly?
4. You may find this Wikipedia article useful.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MATH (1)
#define BRUTE_FORCE (1)
int addDigits(int num) {
    int retVal = 0;

#if (MATH)
    printf("MATH\n");

    /* https://en.wikipedia.org/wiki/Digital_root
     *  abcd
     *  = a * 1000 + b * 100 + c * 10 + d
     *  = a * (999 + 1) + b * (99 + 1) + c * (9 + 1) + d
     *  = (a * 999 + b * 99 + c * 9) + (a + b + c + d)
     */
    if (num != 0) {
        retVal = num % 9;
        if (retVal == 0) {
            retVal = 9;
        }
    }
#elif (BRUTE_FORCE)
    printf("BRUTE_FORCE\n");

    retVal = num;
    while (num >= 10) {
        retVal = 0;
        int tmp = num;
        while (tmp > 0) {
            retVal += (tmp % 10);
            tmp /= 10;
        }
        num = retVal;
    }
#endif

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
#define MATH (1)
#define BRUTE_FORCE (1)
class Solution {
   public:
    int addDigits(int num) {
        int retVal = 0;

#if (MATH)
        cout << "MATH\n";

        /* https://en.wikipedia.org/wiki/Digital_root
         *  abcd
         *  = a * 1000 + b * 100 + c * 10 + d
         *  = a * (999 + 1) + b * (99 + 1) + c * (9 + 1) + d
         *  = (a * 999 + b * 99 + c * 9) + (a + b + c + d)
         */
        if (num != 0) {
            retVal = num % 9;
            if (retVal == 0) {
                retVal = 9;
            }
        }
#elif (BRUTE_FORCE)
        cout << "BRUTE_FORCE\n";

        retVal = num;
        while (num >= 10) {
            retVal = 0;
            int tmp = num;
            while (tmp > 0) {
                retVal += (tmp % 10);
                tmp /= 10;
            }
            num = retVal;
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

        if self.method == 1:
            print("Math")
        elif self.method == 2:
            print("Brute force")
        print()

    def addDigits(self, num: int) -> int:
        retVal = 0

        if self.method == 1:
            # /* https://en.wikipedia.org/wiki/Digital_root
            #  *  abcd
            #  *  = a * 1000 + b * 100 + c * 10 + d
            #  *  = a * (999 + 1) + b * (99 + 1) + c * (9 + 1) + d
            #  *  = (a * 999 + b * 99 + c * 9) + (a + b + c + d)
            #  */
            if num != 0:
                retVal = num % 9
                if retVal == 0:
                    retVal = 9
        elif self.method == 2:
            retVal = num
            while num >= 10:
                retVal = 0
                tmp = num
                while tmp > 0:
                    retVal += (tmp % 10)
                    tmp //= 10
                num = retVal

        return retVal
```

</details>

## [263. Ugly Number](https://leetcode.com/problems/ugly-number/)

- [Official](https://leetcode.com/problems/ugly-number/solutions/2723159/ugly-number/)
- [Official](https://leetcode.cn/problems/ugly-number/solutions/712106/chou-shu-by-leetcode-solution-fazd/)

<details><summary>Description</summary>

```text
An ugly number is a positive integer whose prime factors are limited to 2, 3, and 5.

Given an integer n, return true if n is an ugly number.

Example 1:
Input: n = 6
Output: true
Explanation: 6 = 2 × 3

Example 2:
Input: n = 1
Output: true
Explanation: 1 has no prime factors, therefore all of its prime factors are limited to 2, 3, and 5.

Example 3:
Input: n = 14
Output: false
Explanation: 14 is not ugly since it includes the prime factor 7.

Constraints:
-2^31 <= n <= 2^31 - 1
```

</details>

<details><summary>C</summary>

```c
bool isUgly(int n) {
    bool retVal = false;

    if (n <= 0) {
        return retVal;
    }

    int factors[] = {2, 3, 5};
    int factorsSize = sizeof(factors) / sizeof(factors[0]);

    int i;
    for (i=0; i<factorsSize; ++i) {
        while (n%factors[i] == 0) {
            n /= factors[i];
        }
    }

    if (n == 1) {
        retVal = true;
    }

    return retVal;
}
```

</details>

## [319. Bulb Switcher](https://leetcode.com/problems/bulb-switcher/)

- [Official](https://leetcode.com/problems/bulb-switcher/editorial/)
- [Official](https://leetcode.cn/problems/bulb-switcher/solutions/1099002/deng-pao-kai-guan-by-leetcode-solution-rrgp/)

<details><summary>Description</summary>

```text
There are n bulbs that are initially off. You first turn on all the bulbs, then you turn off every second bulb.

On the third round, you toggle every third bulb (turning on if it's off or turning off if it's on).
For the ith round, you toggle every i bulb. For the nth round, you only toggle the last bulb.

Return the number of bulbs that are on after n rounds.

Example 1:
Input: n = 3
Output: 1
Explanation: At first, the three bulbs are [off, off, off].
After the first round, the three bulbs are [on, on, on].
After the second round, the three bulbs are [on, off, on].
After the third round, the three bulbs are [on, off, off].
So you should return 1 because there is only one bulb is on.

Example 2:
Input: n = 0
Output: 0

Example 3:
Input: n = 1
Output: 1

Constraints:
0 <= n <= 10^9
```

</details>

<details><summary>C</summary>

```c
int bulbSwitch(int n) {
    /*      1   2   3   4   5   6   7   8   9   10
     *    +---+
     *  1 | V | V   V   V   V   V   V   V   V   V   =>  1
     *    +---+---+
     *  2 | V   X | V   X   V   X   V   X   V   X   =>  1
     *    +-------+---+
     *  3 | V   X   X | X   V   V   V   X   X   X   =>  1
     *    +-----------+---+
     *  4 | V   X   X   V | V   V   V   V   X   X   =>  2
     *    +---------------+---+
     *  5 | V   X   X   V   X | V   V   V   X   V   =>  2
     *    +-------------------+---+
     *  6 | V   X   X   V   X   X | V   V   X   V   =>  2
     *    +-----------------------+---+
     *  7 | V   X   X   V   X   X   X | V   X   V   =>  2
     *    +---------------------------+---+
     *  8 | V   X   X   V   X   X   X   X | X   V   =>  2
     *    +-------------------------------+---+
     *  9 | V   X   X   V   X   X   X   X   V | V   =>  3
     *    +-----------------------------------+---+
     * 10 | V   X   X   V   X   X   X   X   V   X | =>  3
     *    +---------------------------------------+
     */
    int retVal = sqrt(n + 0.5);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int bulbSwitch(int n) {
        /*      1   2   3   4   5   6   7   8   9   10
         *    +---+
         *  1 | V | V   V   V   V   V   V   V   V   V   =>  1
         *    +---+---+
         *  2 | V   X | V   X   V   X   V   X   V   X   =>  1
         *    +-------+---+
         *  3 | V   X   X | X   V   V   V   X   X   X   =>  1
         *    +-----------+---+
         *  4 | V   X   X   V | V   V   V   V   X   X   =>  2
         *    +---------------+---+
         *  5 | V   X   X   V   X | V   V   V   X   V   =>  2
         *    +-------------------+---+
         *  6 | V   X   X   V   X   X | V   V   X   V   =>  2
         *    +-----------------------+---+
         *  7 | V   X   X   V   X   X   X | V   X   V   =>  2
         *    +---------------------------+---+
         *  8 | V   X   X   V   X   X   X   X | X   V   =>  2
         *    +-------------------------------+---+
         *  9 | V   X   X   V   X   X   X   X   V | V   =>  3
         *    +-----------------------------------+---+
         * 10 | V   X   X   V   X   X   X   X   V   X | =>  3
         *    +---------------------------------------+
         */
        int retVal = sqrt(n + 0.5);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def bulbSwitch(self, n: int) -> int:
        # /*      1   2   3   4   5   6   7   8   9   10
        #  *    +---+
        #  *  1 | V | V   V   V   V   V   V   V   V   V   =>  1
        #  *    +---+---+
        #  *  2 | V   X | V   X   V   X   V   X   V   X   =>  1
        #  *    +-------+---+
        #  *  3 | V   X   X | X   V   V   V   X   X   X   =>  1
        #  *    +-----------+---+
        #  *  4 | V   X   X   V | V   V   V   V   X   X   =>  2
        #  *    +---------------+---+
        #  *  5 | V   X   X   V   X | V   V   V   X   V   =>  2
        #  *    +-------------------+---+
        #  *  6 | V   X   X   V   X   X | V   V   X   V   =>  2
        #  *    +-----------------------+---+
        #  *  7 | V   X   X   V   X   X   X | V   X   V   =>  2
        #  *    +---------------------------+---+
        #  *  8 | V   X   X   V   X   X   X   X | X   V   =>  2
        #  *    +-------------------------------+---+
        #  *  9 | V   X   X   V   X   X   X   X   V | V   =>  3
        #  *    +-----------------------------------+---+
        #  * 10 | V   X   X   V   X   X   X   X   V   X | =>  3
        #  *    +---------------------------------------+
        #  */
        retVal = int(sqrt(n+0.5))

        return retVal
```

</details>

## [326. Power of Three](https://leetcode.com/problems/power-of-three/)

- [Official](https://leetcode.cn/problems/power-of-three/solutions/1011809/3de-mi-by-leetcode-solution-hnap/)

<details><summary>Description</summary>

```text
Given an integer n, return true if it is a power of three. Otherwise, return false.

An integer n is a power of three, if there exists an integer x such that n == 3^x.

Example 1:
Input: n = 27
Output: true
Explanation: 27 = 3^3

Example 2:
Input: n = 0
Output: false
Explanation: There is no x where 3^x = 0.

Example 3:
Input: n = -1
Output: false
Explanation: There is no x where 3^x = (-1).

Constraints:
-2^31 <= n <= 2^31 - 1

Follow up: Could you solve it without loops/recursion?
```

</details>

<details><summary>C</summary>

```c
bool isPowerOfThree(int n) {
    bool retVal = false;

    if (n <= 0) {
        return retVal;
    }

    if (n % 2 == 0) {
        return retVal;
    }

    /*  n = 3^x
     *  => log(n) = x * log(3)
     *  => x = log(n) / log(3)
     */
    double x = log10(n) / log10(3);
    if (x - (int)x == 0) {
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
    bool isPowerOfThree(int n) {
        bool retVal = false;

        if (n <= 0) {
            return retVal;
        }

        if (n % 2 == 0) {
            return retVal;
        }

        /*  n = 3^x
         *  => log(n) = x * log(3)
         *  => x = log(n) / log(3)
         */
        double x = log10(n) / log10(3);
        if (x - (int)x == 0) {
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
    def isPowerOfThree(self, n: int) -> bool:
        retVal = False

        if n <= 0:
            return retVal

        if n % 2 == 0:
            return retVal

        # /* n = 3 ^ x
        # * = > log(n) = x * log(3)
        # * = > x = log(n) / log(3)
        # */
        x = log10(n) / log10(3)
        if x - int(x) == 0:
            retVal = True

        return retVal
```

</details>

## [342. Power of Four](https://leetcode.com/problems/power-of-four/)

- [Official](https://leetcode.cn/problems/power-of-four/solutions/798268/4de-mi-by-leetcode-solution-b3ya/)

<details><summary>Description</summary>

```text
Given an integer n, return true if it is a power of four. Otherwise, return false.

An integer n is a power of four, if there exists an integer x such that n == 4^x.

Example 1:
Input: n = 16
Output: true

Example 2:
Input: n = 5
Output: false

Example 3:
Input: n = 1
Output: true

Constraints:
-2^31 <= n <= 2^31 - 1

Follow up: Could you solve it without loops/recursion?
```

</details>

<details><summary>C</summary>

```c
bool isPowerOfFour(int n) {
    bool retVal = false;

    if (n <= 0) {
        return retVal;
    }

#if (0)
    if ((n & (n - 1)) != 0) {
        return retVal;
    }

    if ((n & 0x55555555) != 0) {
        retVal = true;
    }
#else
    /* n = 4 ^ x
     * = > log(n) = x * log(4)
     * = > x = log(n) / log(4)
     */
    double x = log10(n) / log10(4);
    if (x - (int)x == 0) {
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
   public:
    bool isPowerOfFour(int n) {
        bool retVal = false;

        if (n <= 0) {
            return retVal;
        }

#if (0)
        if ((n & (n - 1)) != 0) {
            return retVal;
        }

        if ((n & 0x55555555) != 0) {
            retVal = true;
        }
#else
        /* n = 4 ^ x
         * = > log(n) = x * log(4)
         * = > x = log(n) / log(4)
         */
        double x = log10(n) / log10(4);
        if (x - (int)x == 0) {
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
    def __init__(self) -> None:
        self.method = 2

    def isPowerOfFour(self, n: int) -> bool:
        retVal = False

        if n <= 0:
            return retVal

        if self.method == 1:
            if (n & (n - 1)) != 0:
                return retVal

            if (n & 0x55555555) != 0:
                retVal = True
        elif self.method == 2:
            # /* n = 4 ^ x
            # * = > log(n) = x * log(4)
            # * = > x = log(n) / log(4)
            # */
            x = log10(n) / log10(4)
            if x - int(x) == 0:
                retVal = True

        return retVal
```

</details>

## [458. Poor Pigs](https://leetcode.com/problems/poor-pigs/)

- [Official](https://leetcode.cn/problems/poor-pigs/solutions/1119222/ke-lian-de-xiao-zhu-by-leetcode-solution-z0h7/)

<details><summary>Description</summary>

```text
There are buckets buckets of liquid, where exactly one of the buckets is poisonous.
To figure out which one is poisonous, you feed some number of (poor) pigs the liquid to see whether they will die or not.
Unfortunately, you only have minutesToTest minutes to determine which bucket is poisonous.

You can feed the pigs according to these steps:
1. Choose some live pigs to feed.
2. For each pig, choose which buckets to feed it.
   The pig will consume all the chosen buckets simultaneously and will take no time.
   Each pig can feed from any number of buckets, and each bucket can be fed from by any number of pigs.
3. Wait for minutesToDie minutes. You may not feed any other pigs during this time.
4. After minutesToDie minutes have passed,
   any pigs that have been fed the poisonous bucket will die, and all others will survive.
5. Repeat this process until you run out of time.

Given buckets, minutesToDie, and minutesToTest,
return the minimum number of pigs needed to figure out which bucket is poisonous within the allotted time.

Example 1:
Input: buckets = 4, minutesToDie = 15, minutesToTest = 15
Output: 2
Explanation: We can determine the poisonous bucket as follows:
At time 0, feed the first pig buckets 1 and 2, and feed the second pig buckets 2 and 3.
At time 15, there are 4 possible outcomes:
- If only the first pig dies, then bucket 1 must be poisonous.
- If only the second pig dies, then bucket 3 must be poisonous.
- If both pigs die, then bucket 2 must be poisonous.
- If neither pig dies, then bucket 4 must be poisonous.

Example 2:
Input: buckets = 4, minutesToDie = 15, minutesToTest = 30
Output: 2
Explanation: We can determine the poisonous bucket as follows:
At time 0, feed the first pig bucket 1, and feed the second pig bucket 2.
At time 15, there are 2 possible outcomes:
- If either pig dies, then the poisonous bucket is the one it was fed.
- If neither pig dies, then feed the first pig bucket 3, and feed the second pig bucket 4.
At time 30, one of the two pigs must die, and the poisonous bucket is the one it was fed.

Constraints:
1 <= buckets <= 1000
1 <= minutesToDie <= minutesToTest <= 100
```

<details><summary>Hint</summary>

```text
1. What if you only have one shot? Eg. 4 buckets, 15 mins to die, and 15 mins to test.
2. How many states can we generate with x pigs and T tests?
3. Find minimum x such that (T+1)^x >= N
```

</details>

</details>

<details><summary>C</summary>

```c
int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
    int retVal = 0;

    /* https://leetcode.cn/problems/poor-pigs/solutions/15770/hua-jie-suan-fa-458-ke-lian-de-xiao-zhu-by-guanpen/
     *  pow(base, answer) ≥ buckets
     *  => answer ≥ log(buckets) / log(base)
     *  => answer = ceil(log(buckets) / log(base))
     */
    int base = minutesToTest / minutesToDie + 1;
    retVal = ceil(log10(buckets) / log10(base));

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        int retVal = 0;

        /* https://leetcode.cn/problems/poor-pigs/solutions/15770/hua-jie-suan-fa-458-ke-lian-de-xiao-zhu-by-guanpen/
         *  pow(base, answer) ≥ buckets
         *  => answer ≥ log(buckets) / log(base)
         *  => answer = ceil(log(buckets) / log(base))
         */
        int base = minutesToTest / minutesToDie + 1;
        retVal = ceil(log10(buckets) / log10(base));

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def poorPigs(self, buckets: int, minutesToDie: int, minutesToTest: int) -> int:
        retVal = 0

        # https: // leetcode.cn/problems/poor-pigs/solutions/15770/hua-jie-suan-fa-458-ke-lian-de-xiao-zhu-by-guanpen/
        #   pow(base, answer) ≥ buckets
        #   = > answer ≥ log(buckets) / log(base)
        #   = > answer = ceil(log(buckets) / log(base))
        base = minutesToTest / minutesToDie + 1
        retVal = ceil(log10(buckets) / log10(base))

        return retVal
```

</details>

## [462. Minimum Moves to Equal Array Elements II](https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/)

- [Official](https://leetcode.cn/problems/minimum-moves-to-equal-array-elements-ii/solutions/1501230/zui-shao-yi-dong-ci-shu-shi-shu-zu-yuan-xt3r2/)

<details><summary>Description</summary>

```text
Given an integer array nums of size n, return the minimum number of moves required to make all array elements equal.

In one move, you can increment or decrement an element of the array by 1.

Test cases are designed so that the answer will fit in a 32-bit integer.

Example 1:
Input: nums = [1,2,3]
Output: 2
Explanation:
Only two moves are needed (remember each move increments or decrements one element):
[1,2,3]  =>  [2,2,3]  =>  [2,2,2]

Example 2:
Input: nums = [1,10,2,9]
Output: 16

Constraints:
n == nums.length
1 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9
```

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int minMoves2(int* nums, int numsSize) {
    int retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int i;
    for (i = 0; i < numsSize; ++i) {
        retVal += abs(nums[i] - nums[numsSize / 2]);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minMoves2(vector<int>& nums) {
        int retVal = 0;

        sort(nums.begin(), nums.end());

        int numsSize = nums.size();
        for (int i = 0; i < numsSize; ++i) {
            retVal += abs(nums[i] - nums[numsSize / 2]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minMoves2(self, nums: List[int]) -> int:
        retVal = 0

        nums.sort()

        numsSize = len(nums)
        for num in nums:
            retVal += abs(num - nums[numsSize//2])

        return retVal
```

</details>

## [564. Find the Closest Palindrome](https://leetcode.com/problems/find-the-closest-palindrome/)

- [Official](https://leetcode.com/problems/find-the-closest-palindrome/editorial/)
- [Official](https://leetcode.cn/problems/find-the-closest-palindrome/solutions/1300885/xun-zhao-zui-jin-de-hui-wen-shu-by-leetc-biyt/)

<details><summary>Description</summary>

```text
Given a string n representing an integer, return the closest integer (not including itself), which is a palindrome.
If there is a tie, return the smaller one.

The closest is defined as the absolute difference minimized between two integers.

Example 1:
Input: n = "123"
Output: "121"

Example 2:
Input: n = "1"
Output: "0"
Explanation: 0 and 2 are the closest palindromes but we return the smallest which is 0.

Constraints:
1 <= n.length <= 18
n consists of only digits.
n does not have leading zeros.
n is representing an integer in the range [1, 10^18 - 1].
```

<details><summary>Hint</summary>

```text
1. Will brute force work for this problem? Think of something else.
2. Take some examples like 1234, 999,1000, etc and check their closest palindromes.
   How many different cases are possible?
3. Do we have to consider only left half or right half of the string or both?
4. Try to find the closest palindrome of these numbers- 12932, 99800, 12120. Did you observe something?
```

</details>

</details>

<details><summary>C</summary>

```c
long halfToPalindrome(long left, bool even) {
    long retVal = left;

    if (even == false) {
        left = left / 10;
    }

    while (left > 0) {
        retVal = retVal * 10 + left % 10;
        left /= 10;
    }

    return retVal;
}
char* nearestPalindromic(char* n) {
    char* pRetVal = NULL;

    int nSize = strlen(n);

    int returnSize = nSize + 4;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (nSize * sizeof(char)));

    int i;
    int firstHalfSize = (nSize % 2 == 0) ? (nSize / 2 - 1) : (nSize / 2);
    long firstHalf = 0;
    for (i = 0; i < firstHalfSize + 1; ++i) {
        firstHalf = (long)(10 * firstHalf) + (long)(n[i] - '0');
    }

    /* Generate possible palindromic candidates:
     *  1. Create a palindrome by mirroring the first half.
     *  2. Create a palindrome by mirroring the first half incremented by 1.
     *  3. Create a palindrome by mirroring the first half decremented by 1.
     *  4. Handle edge cases by considering palindromes of the
     *     form 999...and 100...001 (smallest and largest n-digit palindromes).
     */
    int candidatesSize = 5;
    long candidates[candidatesSize];
    candidates[0] = halfToPalindrome(firstHalf, nSize % 2 == 0);
    candidates[1] = halfToPalindrome(firstHalf + 1, nSize % 2 == 0);
    candidates[2] = halfToPalindrome(firstHalf - 1, nSize % 2 == 0);
    candidates[3] = (long)pow(10, nSize - 1) - 1;
    candidates[4] = (long)pow(10, nSize) + 1;

    long diff = LONG_MAX;
    long res = 0;
    long nl = atol(n);
    for (i = 0; i < candidatesSize; ++i) {
        if (candidates[i] == nl) {
            continue;
        }

        if (labs(candidates[i] - nl) < diff) {
            diff = labs(candidates[i] - nl);
            res = candidates[i];
        } else if (labs(candidates[i] - nl) == diff) {
            res = fmin(res, candidates[i]);
        }
    }

    char buf[returnSize];
    memset(buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf), "%ld", res);
    memcpy(pRetVal, buf, returnSize);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    long halfToPalindrome(long left, bool even) {
        long retVal = left;

        if (even == false) {
            left = left / 10;
        }

        while (left > 0) {
            retVal = retVal * 10 + left % 10;
            left /= 10;
        }

        return retVal;
    }

   public:
    string nearestPalindromic(string n) {
        string retVal = "";

        int nSize = n.size();

        int i = (nSize % 2 == 0) ? (nSize / 2 - 1) : (nSize / 2);
        long firstHalf = stol(n.substr(0, i + 1));

        /* Generate possible palindromic candidates:
         *  1. Create a palindrome by mirroring the first half.
         *  2. Create a palindrome by mirroring the first half incremented by 1.
         *  3. Create a palindrome by mirroring the first half decremented by 1.
         *  4. Handle edge cases by considering palindromes of the
         *     form 999...and 100...001 (smallest and largest n-digit palindromes).
         */
        vector<long> candidates;
        candidates.push_back(halfToPalindrome(firstHalf, nSize % 2 == 0));
        candidates.push_back(halfToPalindrome(firstHalf + 1, nSize % 2 == 0));
        candidates.push_back(halfToPalindrome(firstHalf - 1, nSize % 2 == 0));
        candidates.push_back((long)pow(10, nSize - 1) - 1);
        candidates.push_back((long)pow(10, nSize) + 1);

        long diff = numeric_limits<long>::max();
        long res = 0;
        long nl = stol(n);
        for (auto candidate : candidates) {
            if (candidate == nl) {
                continue;
            }

            if (abs(candidate - nl) < diff) {
                diff = abs(candidate - nl);
                res = candidate;
            } else if (abs(candidate - nl) == diff) {
                res = min(res, candidate);
            }
        }
        retVal = to_string(res);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def halfToPalindrome(self, left: int, even: bool) -> int:
        retVal = left

        if not even:
            left = left // 10

        while left > 0:
            retVal = retVal * 10 + left % 10
            left //= 10

        return retVal

    def nearestPalindromic(self, n: str) -> str:
        retVal = ""

        nSize = len(n)

        i = nSize // 2 - 1 if nSize % 2 == 0 else nSize // 2
        firstHalf = int(n[: i + 1])

        # Generate possible palindromic candidates:
        #   1. Create a palindrome by mirroring the first half.
        #   2. Create a palindrome by mirroring the first half incremented by 1.
        #   3. Create a palindrome by mirroring the first half decremented by 1.
        #   4. Handle edge cases by considering palindromes of the
        #      form 999...and 100...001 (smallest and largest n-digit palindromes).
        candidates = []
        candidates.append(self.halfToPalindrome(firstHalf, nSize % 2 == 0))
        candidates.append(self.halfToPalindrome(firstHalf + 1, nSize % 2 == 0))
        candidates.append(self.halfToPalindrome(firstHalf - 1, nSize % 2 == 0))
        candidates.append(10 ** (nSize - 1) - 1)
        candidates.append(10**nSize + 1)

        diff = float("inf")
        res = 0
        nl = int(n)
        for candidate in candidates:
            if candidate == nl:
                continue

            if abs(candidate - nl) < diff:
                diff = abs(candidate - nl)
                res = candidate
            elif abs(candidate - nl) == diff:
                res = min(res, candidate)

        retVal = str(res)

        return retVal
```

</details>

## [587. Erect the Fence](https://leetcode.com/problems/erect-the-fence/)

- [Official](https://leetcode.com/problems/erect-the-fence/solutions/127731/erect-the-fence/)
- [Official](https://leetcode.cn/problems/erect-the-fence/solutions/1440879/an-zhuang-zha-lan-by-leetcode-solution-75s3/)

<details><summary>Description</summary>

```text
You are given an array trees where trees[i] = [xi, yi] represents the location of a tree in the garden.

You are asked to fence the entire garden using the minimum length of rope as it is expensive.
The garden is well fenced only if all the trees are enclosed.

Return the coordinates of trees that are exactly located on the fence perimeter.

Example 1:
 5 |
 4 |     o
 3 |        o
 2 |     o     o
 1 |  o
 0 +-----o---------
   0  1  2  3  4  5
Input: points = [[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]
Output: [[1,1],[2,0],[3,3],[2,4],[4,2]]

Example 2:
 4 |
 3 |
 2 |  o  o     o
 1 |
 0 +------------
   0  1  2  3  4
Input: points = [[1,2],[2,2],[4,2]]
Output: [[4,2],[2,2],[1,2]]

Constraints:
1 <= points.length <= 3000
points[i].length == 2
0 <= xi, yi <= 100
All the given points are unique.
```

</details>

<details><summary>C</summary>

```c
// https://en.wikipedia.org/wiki/Convex_hull
#define Jarvis_Algorithm    (1)     // Time Complexity: O(n^2), Space Complexity: O(n).
#define Graham_Scan         (1)     // Time Complexity: O(nlogn), Space Complexity: O(n).
#define Monotone_Chain      (1)     // Time Complexity: O(nlogn), Space Complexity: O(n).

int crossProduct(const int* p, const int* q, const int* r) {
    // https://en.wikipedia.org/wiki/Cross_product
    return (((q[0]-p[0]) * (r[1]-q[1])) - ((q[1]-p[1]) * (r[0]-q[0])));
}
#if (Jarvis_Algorithm)

#elif (Graham_Scan)
int distance(const int* p, const int* q) {
    return (((p[0]-q[0]) * (p[0]-q[0])) + ((p[1]-q[1]) * (p[1]-q[1])));
}
int* p = NULL;
int cmp(const void* pa, const void* pb) {
    int* a = *((int**)pa);
    int* b = *((int**)pb);

    int diff = crossProduct(p, a, b);
    if (diff == 0) {
        return (distance(p, a) - distance(p, b));
    } else {
        return -diff;
    }
}
void swap(int* pa, int* pb) {
    int c = pa[0];

    pa[0] = pb[0];
    pb[0] = c;
    c = pa[1];
    pa[1] = pb[1];
    pb[1] = c;
}
#elif (Monotone_Chain)
int cmp(const void* pa, const void* pb) {
    int* a = *((int **)pa);
    int* b = *((int **)pb);

    if (a[0] == b[0]) {
        return (a[1] - b[1]);
    }
    return a[0] - b[0];
}
#endif

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** outerTrees(int** trees, int treesSize, int* treesColSize, int* returnSize, int** returnColumnSizes) {
    int** retVal = NULL;
    (*returnSize) = 0;

    int pos = 0;
    int i, j;

    retVal = (int**)malloc(treesSize * sizeof(int*));
    if (retVal == NULL) {
        perror("malloc");
        return retVal;
    }

    if (treesSize < 4) {
        (*returnColumnSizes) = (int*)malloc(treesSize * sizeof(int));
        if ((*returnColumnSizes) == NULL) {
            perror("malloc");
            free(retVal);
            retVal = NULL;
            return retVal;
        }
        for (i=0; i<treesSize; ++i) {
            retVal[i] = (int*)malloc(2 * sizeof(int));
            if (retVal[i] == NULL) {
                perror("malloc");
                for (j=0; j<i; ++j) {
                    free(retVal[j]);
                    retVal[j] = NULL;
                }
                free((*returnColumnSizes));
                (*returnColumnSizes) = NULL;
                free(retVal);
                retVal = NULL;
                return retVal;
            }
            retVal[i][0] = trees[i][0];
            retVal[i][1] = trees[i][1];
            (*returnColumnSizes)[i] = 2;
        }
        (*returnSize) = treesSize;

        return retVal;
    }

#if (Jarvis_Algorithm)
    printf("Jarvis Algorithm: Time Complexity: O(n^2), Space Complexity: O(n).\n");

    int leftMost = 0;
    for (i=0; i<treesSize; ++i) {
        if ((trees[i][0] < trees[leftMost][0]) || ((trees[i][0]==trees[leftMost][0]) && (trees[i][1]<trees[leftMost][1]))) {
            leftMost = i;
        }
    }

    bool* visit = (bool*)malloc(treesSize * sizeof(bool));
    if (visit == NULL) {
        perror("malloc");
        free(retVal);
        retVal = NULL;
        return retVal;
    }
    memset(visit, 0, (treesSize * sizeof(bool)));

    int p = leftMost;
    int q;
    int r;
    do {
        q = (p + 1) % treesSize;
        for (r=0; r<treesSize; ++r) {
            // 如果 r 在 pq 的右側，則 q = r.
            if (crossProduct(trees[p], trees[q], trees[r]) < 0) {
                q = r;
            }
        }

        // 是否存在點 i, 使得 p 、q 、i 在同一條直線上
        for (i=0; i<treesSize; ++i) {
            if ((visit[i]) || (i==p) || (i==q)) {
                continue;
            }

            if (crossProduct(trees[p], trees[q], trees[i]) == 0) {
                retVal[pos] = (int *)malloc(2 * sizeof(int));
                if (retVal[pos] == NULL) {
                    perror("malloc");
                    for (j=0; j<pos; ++j) {
                        if (retVal[j]) {
                            free(retVal[j]);
                            retVal[j] = NULL;
                        }
                    }
                    free(visit);
                    visit = NULL;
                    free(retVal);
                    retVal = NULL;
                    return retVal;
                }

                retVal[pos][0] = trees[i][0];
                retVal[pos][1] = trees[i][1];
                pos++;
                visit[i] = true;
            }
        }

        if (!visit[q]) {
            visit[q] = true;
            retVal[pos] = (int*)malloc(2 * sizeof(int));
            if (retVal[pos] == NULL) {
                perror("malloc");
                for (j=0; j<pos; ++j) {
                    if (retVal[j]) {
                        free(retVal[j]);
                        retVal[j] = NULL;
                    }
                }
                free(visit);
                visit = NULL;
                free(retVal);
                retVal = NULL;
                return retVal;
            }
            retVal[pos][0] = trees[q][0];
            retVal[pos][1] = trees[q][1];
            pos++;
        }

        p = q;
    } while (p != leftMost);
    free(visit);
    visit = NULL;
#elif (Graham_Scan)
    printf("Graham Scan: Time Complexity: O(nlogn), Space Complexity: O(n).\n");

    // 找到 y 最小的點 bottom
    int bottom = 0;
    for (i=0; i<treesSize; ++i) {
        if ((trees[i][1] < trees[bottom][1]) || ((trees[i][1]==trees[bottom][1]) && (trees[i][0]<trees[bottom][0]))) {
            bottom = i;
        }
    }
    swap(trees[bottom], trees[0]);
    p = trees[0];

    // 以 bottom 原點，按照極坐標的角度大小進行排序
    qsort(trees + 1, treesSize - 1, sizeof(int *), cmp);

    // 對於凸包最後且在同一條直線的元素按照距離從大到小進行排序
    int r = treesSize - 1;
    while ((r >= 0) && (crossProduct(trees[0], trees[treesSize - 1], trees[r]) == 0)) {
        r--;
    }

    int l, h;
    for (l=r+1, h=treesSize-1; l<h; l++,h--) {
        swap(trees[l], trees[h]);
    }

    int* stack = (int*)malloc(treesSize * sizeof(int));
    if (stack == NULL) {
        perror("malloc");
        free(retVal);
        retVal = NULL;
        return retVal;
    }

    int top = 0;
    stack[top++] = 0;
    stack[top++] = 1;
    for (i=2; i<treesSize; ++i) {
        // 如果當前元素與棧頂的兩個元素構成的向量順時針旋轉，則彈出棧頂元素
        while ((top > 1) && (crossProduct(trees[stack[top-2]], trees[stack[top-1]], trees[i]) < 0)) {
            top--;
        }
        stack[top++] = i;
    }

    while (top > 0) {
        retVal[pos] = (int*)malloc(2 * sizeof(int));
        if (retVal[pos] == NULL) {
            perror("malloc");
            for (j=0; j<pos; ++j) {
                if (retVal[j]) {
                    free(retVal[j]);
                    retVal[j] = NULL;
                }
            }
            free(stack);
            stack = NULL;
            free(retVal);
            retVal = NULL;
            return retVal;
        }
        memcpy(retVal[pos], trees[stack[top-1]], (2 * sizeof(int)));

        pos++;
        top--;
    }

    free(stack);
    stack = NULL;
#elif (Monotone_Chain)
    printf("Monotone Chain: Time Complexity: O(nlogn), Space Complexity: O(n).\n");

    qsort(trees, treesSize, sizeof(int*), cmp);

    int* hull = (int *)malloc(sizeof(int) * (treesSize + 1));
    if (hull == NULL) {
        perror("malloc");
        free(retVal);
        retVal = NULL;
        return retVal;
    }
    int* used = (int *)malloc(sizeof(int) * treesSize);
    if (used == NULL) {
        perror("malloc");
        free(hull);
        hull = NULL;
        free(retVal);
        retVal = NULL;
        return retVal;
    }
    memset(used, 0, (treesSize * sizeof(int)));
    // hull[0] 需要入棧兩次，不進行標記
    hull[pos++] = 0;

    // 求出凸包的下半部分
    for (i=1; i<treesSize; ++i) {
        while ((pos > 1) && (crossProduct(trees[hull[pos-2]], trees[hull[pos-1]], trees[i]) < 0)) {
            used[hull[pos - 1]] = false;
            pos--;
        }
        used[i] = true;
        hull[pos++] = i;
    }
    int m = pos;

    // 求出凸包的上半部分
    for (i=treesSize-2; i>=0; --i) {
        if (!used[i]) {
            while ((pos > m) && (crossProduct(trees[hull[pos-2]], trees[hull[pos-1]], trees[i]) < 0)) {
                used[hull[pos - 1]] = false;
                pos--;
            }
            used[i] = true;
            hull[pos++] = i;
        }
    }

    // hull[0] 同時參與凸包的上半部分檢測，因此需去掉重複的 hull[0]
    pos--;

    for (i=0; i<pos; ++i) {
        retVal[i] = (int *)malloc(sizeof(int) * 2);
        if (retVal[i] == NULL) {
            perror("malloc");
            for (j=0; j<i; ++j) {
                if (retVal[j]) {
                    free(retVal[j]);
                    retVal[j] = NULL;
                }
            }
            free(used);
            used = NULL;
            free(hull);
            hull = NULL;
            free(retVal);
            retVal = NULL;
            return retVal;
        }
        memcpy(retVal[i], trees[hull[i]], (2 * sizeof(int)));
    }

    free(used);
    used = NULL;
    free(hull);
    hull = NULL;
#endif

    (*returnSize) = pos;
    (*returnColumnSizes) = (int *)malloc(pos * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        for (j=0; j<pos; ++j) {
            if (retVal[j]) {
                free(retVal[j]);
                retVal[j] = NULL;
            }
        }
        free(retVal);
        retVal = NULL;
        return retVal;
    }
    for (i=0; i<pos; ++i) {
        (*returnColumnSizes)[i] = 2;
    }

    return retVal;
}
```

</details>

## [592. Fraction Addition and Subtraction](https://leetcode.com/problems/fraction-addition-and-subtraction/)

- [Official](https://leetcode.com/problems/fraction-addition-and-subtraction/editorial/)
- [Official](https://leetcode.cn/problems/fraction-addition-and-subtraction/solutions/1699131/fen-shu-jia-jian-yun-suan-by-leetcode-so-2mto/)

<details><summary>Description</summary>

```text
Given a string expression representing an expression of fraction addition and subtraction,
return the calculation result in string format.

The final result should be an irreducible fraction.
If your final result is an integer, change it to the format of a fraction that has a denominator 1.
So in this case, 2 should be converted to 2/1.

Example 1:
Input: expression = "-1/2+1/2"
Output: "0/1"

Example 2:
Input: expression = "-1/2+1/2+1/3"
Output: "1/3"

Example 3:
Input: expression = "1/3-1/2"
Output: "-1/6"

Constraints:
- The input string only contains '0' to '9', '/', '+' and '-'. So does the output.
- Each fraction (input and output) has the format ±numerator/denominator.
  If the first input fraction or the output is positive, then '+' will be omitted.
- The input only contains valid irreducible fractions,
  where the numerator and denominator of each fraction will always be in the range [1, 10].
  If the denominator is 1, it means this fraction is actually an integer in a fraction format defined above.
- The number of given fractions will be in the range [1, 10].
- The numerator and denominator of the final result are guaranteed to be valid and in the range of 32-bit int.
```

</details>

<details><summary>C</summary>

```c
int gcd(int dividend, int divisor) {
    int remainder;
    while (divisor != 0) {
        remainder = dividend % divisor;
        dividend = divisor;
        divisor = remainder;
    }

    return dividend;
}
char* fractionAddition(char* expression) {
    char* pRetVal = NULL;

    int expressionSize = strlen(expression);

    int returnSize = expressionSize + 1;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));

    long long numerator = 0;
    long long x, sign;
    long long denominator = 1;
    long long y;
    int index = 0;
    while (index < expressionSize) {
        sign = 1;
        x = 0;
        if ((expression[index] == '-') || (expression[index] == '+')) {
            sign = expression[index] == '-' ? -1 : 1;
            index++;
        }
        while ((index < expressionSize) && (isdigit(expression[index]))) {
            x = x * 10 + expression[index] - '0';
            index++;
        }
        x = sign * x;
        index++;

        y = 0;
        while ((index < expressionSize) && (isdigit(expression[index]))) {
            y = y * 10 + expression[index] - '0';
            index++;
        }

        numerator = numerator * y + x * denominator;
        denominator *= y;
    }

    char buf[returnSize];
    memset(buf, 0, sizeof(buf));
    long long greatestCommonDivisor;
    if (numerator != 0) {
        greatestCommonDivisor = gcd(abs(numerator), denominator);
        snprintf(buf, sizeof(buf), "%lld/%lld", (numerator / greatestCommonDivisor),
                 (denominator / greatestCommonDivisor));
    } else {
        snprintf(buf, sizeof(buf), "0/1");
    }
    memcpy(pRetVal, buf, returnSize);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string fractionAddition(string expression) {
        string retVal = "0/1";

        int expressionSize = expression.size();

        long long numerator = 0;
        long long denominator = 1;
        int index = 0;
        while (index < expressionSize) {
            long long sign = 1;
            long long x = 0;
            if ((expression[index] == '-') || (expression[index] == '+')) {
                sign = expression[index] == '-' ? -1 : 1;
                index++;
            }
            while ((index < expressionSize) && (isdigit(expression[index]))) {
                x = x * 10 + expression[index] - '0';
                index++;
            }
            x = sign * x;
            index++;

            long long y = 0;
            while ((index < expressionSize) && (isdigit(expression[index]))) {
                y = y * 10 + expression[index] - '0';
                index++;
            }

            numerator = numerator * y + x * denominator;
            denominator *= y;
        }

        if (numerator != 0) {
            long long greatestCommonDivisor = gcd(abs(numerator), denominator);
            retVal = to_string(numerator / greatestCommonDivisor);
            retVal += "/";
            retVal += to_string(denominator / greatestCommonDivisor);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def fractionAddition(self, expression: str) -> str:
        retVal = "0/1"

        expressionSize = len(expression)

        numerator = 0
        denominator = 1
        i = 0
        while i < expressionSize:
            sign = 1
            x = 0
            if (expression[i] == '-') or (expression[i] == '+'):
                if expression[i] == '-':
                    sign = -1
                i += 1
            while (i < expressionSize) and (expression[i].isdigit()):
                x = x * 10 + int(expression[i])
                i += 1
            x = sign * x
            i += 1

            y = 0
            while (i < expressionSize) and (expression[i].isdigit()):
                y = y * 10 + int(expression[i])
                i += 1

            numerator = numerator * y + x * denominator
            denominator *= y

        if numerator != 0:
            greatestCommonDivisor = gcd(abs(numerator), denominator)
            numerator //= greatestCommonDivisor
            denominator //= greatestCommonDivisor
            retVal = str(numerator) + "/" + str(denominator)

        return retVal
```

</details>

## [633. Sum of Square Numbers](https://leetcode.com/problems/sum-of-square-numbers/)

- [Official](https://leetcode.com/problems/sum-of-square-numbers/editorial/)
- [Official](https://leetcode.cn/problems/sum-of-square-numbers/solutions/747079/ping-fang-shu-zhi-he-by-leetcode-solutio-8ydl/)

<details><summary>Description</summary>

```text
Given a non-negative integer c, decide whether there're two integers a and b such that a^2 + b^2 = c.

Example 1:
Input: c = 5
Output: true
Explanation: 1 * 1 + 2 * 2 = 5

Example 2:
Input: c = 3
Output: false

Constraints:
0 <= c <= 2^31 - 1
```

</details>

<details><summary>C</summary>

```c
bool judgeSquareSum(int c) {
    bool retVal = false;

    long sum;
    long left = 0;
    long right = (int)sqrt(c);
    while (left <= right) {
        sum = (left * left) + (right * right);
        if (sum == c) {
            retVal = true;
            break;
        } else if (sum > c) {
            right--;
        } else {
            left++;
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
    bool judgeSquareSum(int c) {
        bool retVal = false;

        long left = 0;
        long right = (int)sqrt(c);
        while (left <= right) {
            long sum = (left * left) + (right * right);
            if (sum == c) {
                retVal = true;
                break;
            } else if (sum > c) {
                right--;
            } else {
                left++;
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
    def judgeSquareSum(self, c: int) -> bool:
        retVal = False

        left = 0
        right = int(sqrt(c))
        while left <= right:
            sum = (left * left) + (right * right)
            if sum == c:
                retVal = True
                break
            elif sum > c:
                right -= 1
            else:
                left += 1

        return retVal
```

</details>

## [650. 2 Keys Keyboard](https://leetcode.com/problems/2-keys-keyboard/)

- [Official](https://leetcode.com/problems/2-keys-keyboard/editorial/)
- [Official](https://leetcode.cn/problems/2-keys-keyboard/solutions/1004937/zhi-you-liang-ge-jian-de-jian-pan-by-lee-ussa/)

<details><summary>Description</summary>

```text
There is only one character 'A' on the screen of a notepad.
You can perform one of two operations on this notepad for each step:
- Copy All: You can copy all the characters present on the screen (a partial copy is not allowed).
- Paste: You can paste the characters which are copied last time.

Given an integer n, return the minimum number of operations to get the character 'A' exactly n times on the screen.

Example 1:
Input: n = 3
Output: 3
Explanation: Initially, we have one character 'A'.
In step 1, we use Copy All operation.
In step 2, we use Paste operation to get 'AA'.
In step 3, we use Paste operation to get 'AAA'.

Example 2:
Input: n = 1
Output: 0

Constraints:
1 <= n <= 1000
```

<details><summary>Hint</summary>

```text
1. How many characters may be there in the clipboard at the last step if n = 3? n = 7? n = 10? n = 24?
```

</details>

</details>

<details><summary>C</summary>

```c
int minSteps(int n) {
    int retVal = 0;

    int i = 2;
    while (i * i <= n) {
        while (n % i == 0) {
            n /= i;
            retVal += i;
        }
        i += 1;
    }

    if (n > 1) {
        retVal += n;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minSteps(int n) {
        int retVal = 0;

        int i = 2;
        while (i * i <= n) {
            while (n % i == 0) {
                n /= i;
                retVal += i;
            }
            i += 1;
        }

        if (n > 1) {
            retVal += n;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minSteps(self, n: int) -> int:
        retVal = 0

        i = 2
        while i * i <= n:
            while n % i == 0:
                n //= i
                retVal += i
            i += 1

        if n > 1:
            retVal += n

        return retVal
```

</details>

## [775. Global and Local Inversions](https://leetcode.com/problems/global-and-local-inversions/)  1516

<details><summary>Description</summary>

```text
You are given an integer array nums of length n which represents a permutation of all the integers in the range [0, n - 1].

The number of global inversions is the number of the different pairs (i, j) where:
- 0 <= i < j < n
- nums[i] > nums[j]

The number of local inversions is the number of indices i where:
- 0 <= i < n - 1
- nums[i] > nums[i + 1]

Return true if the number of global inversions is equal to the number of local inversions.

Example 1:
Input: nums = [1,0,2]
Output: true
Explanation: There is 1 global inversion and 1 local inversion.

Example 2:
Input: nums = [1,2,0]
Output: false
Explanation: There are 2 global inversions and 1 local inversion.

Constraints:
n == nums.length
1 <= n <= 10^5
0 <= nums[i] < n
All the integers of nums are unique.
nums is a permutation of all the numbers in the range [0, n - 1].
```

</details>

<details><summary>C</summary>

```c
bool isIdealPermutation(int* nums, int numsSize) {
    bool retVal = false;

    /* if the absolute value is larger than 1, means the number of global inversion must be bigger than local inversion,
     * because a local inversion is a global inversion, but a global one may not be local.
     *
     * proof
     *  If A[i] > i + 1, means at least one number that is smaller than A[i] is kicked out from first A[i] numbers,
     *  and the distance between this smaller number and A[i] is at least 2, then it is a non-local global inversion.
     *  For example, A[i] = 3, i = 1, at least one number that is smaller than 3 is kicked out from first 3 numbers,
     *  and the distance between the smaller number and 3 is at least 2.
     *  If A[i] < i - 1, means at least one number that is bigger than A[i] is kicked out from last n - i numbers,
     *  and the distance between this bigger number and A[i] is at least 2, then it is a non-local global inversion.
     *
     * Ref
     *  https://leetcode.com/problems/global-and-local-inversions/discuss/113656/My-3-lines-C%2B%2B-Solution
     *  https://leetcode.cn/problems/global-and-local-inversions/solutions/1973203/-by-muse-77-q80y/
     */
    int i;
    for (i=0; i<numsSize; ++i) {
        if (abs(nums[i] - i) > 1) {
            return retVal;
        }
    }
    retVal = true;

    return retVal;
}
```

</details>

## [869. Reordered Power of 2](https://leetcode.com/problems/reordered-power-of-2/)  1505

- [Official](https://leetcode.cn/problems/reordered-power-of-2/solutions/1068761/zhong-xin-pai-xu-de-dao-2-de-mi-by-leetc-4fvs/)

<details><summary>Description</summary>

```text
You are given an integer n.
We reorder the digits in any order (including the original order) such that the leading digit is not zero.

Return true if and only if we can do this so that the resulting number is a power of two.

Example 1:
Input: n = 1
Output: true

Example 2:
Input: n = 10
Output: false

Constraints:
1 <= n <= 10^9
```

</details>

<details><summary>C</summary>

```c
long counter(int n) {
    long retVal = 0;

    for (; n; n /= 10) {
        retVal += pow(10, n % 10);
    }

    return retVal;
}
bool reorderedPowerOf2(int n) {
    bool retVal = false;

    long c = counter(n);
    for (int i = 0; i < 31; i++) {
        if (counter(1 << i) == c) {
            retVal = true;
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
    long counter(int n) {
        long retVal = 0;

        for (; n; n /= 10) {
            retVal += pow(10, n % 10);
        }

        return retVal;
    }

   public:
    bool reorderedPowerOf2(int n) {
        bool retVal = false;

        long c = counter(n);
        for (int i = 0; i < 32; i++) {
            if (counter(1 << i) == c) {
                retVal = true;
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
    def reorderedPowerOf2(self, n: int) -> bool:
        retVal = False

        c = Counter(str(n))
        for i in range(30):
            if Counter(str(1 << i)) == c:
                retVal = True
                break

        return retVal
```

</details>

## [908. Smallest Range I](https://leetcode.com/problems/smallest-range-i/)  1298

- [Official](https://leetcode.cn/problems/smallest-range-i/solutions/1449819/zui-xiao-chai-zhi-i-by-leetcode-solution-7lcl/)

<details><summary>Description</summary>

```text
You are given an integer array nums and an integer k.

In one operation, you can choose any index i where 0 <= i < nums.length
and change nums[i] to nums[i] + x where x is an integer from the range [-k, k].
You can apply this operation at most once for each index i.

The score of nums is the difference between the maximum and minimum elements in nums.

Return the minimum score of nums after applying the mentioned operation at most once for each index in it.

Example 1:
Input: nums = [1], k = 0
Output: 0
Explanation: The score is max(nums) - min(nums) = 1 - 1 = 0.

Example 2:
Input: nums = [0,10], k = 2
Output: 6
Explanation: Change nums to be [2, 8]. The score is max(nums) - min(nums) = 8 - 2 = 6.

Example 3:
Input: nums = [1,3,6], k = 3
Output: 0
Explanation: Change nums to be [4, 4, 4]. The score is max(nums) - min(nums) = 4 - 4 = 0.

Constraints:
1 <= nums.length <= 10^4
0 <= nums[i] <= 10^4
0 <= k <= 10^4
```

</details>

<details><summary>C</summary>

```c
int smallestRangeI(int* nums, int numsSize, int k) {
    int retVal = 0;

    /* https://leetcode.com/problems/smallest-range-i/solutions/173367/c-java-python-check-max-min/
     *  If min(nums) + k < max(nums) - k, then return max(nums) - min(nums) - 2 * k.
     *  If min(nums) + k >= max(nums) - k, then return 0.
     */
    int max = nums[0];
    int min = nums[0];
    int i;
    for (i = 1; i < numsSize; ++i) {
        max = fmax(max, nums[i]);
        min = fmin(min, nums[i]);
    }
    if ((min + k) < (max - k)) {
        retVal = max - min - 2 * k;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int smallestRangeI(vector<int>& nums, int k) {
        int retVal = 0;

        /* https://leetcode.com/problems/smallest-range-i/solutions/173367/c-java-python-check-max-min/
         *  If min(nums) + k < max(nums) - k, then return max(nums) - min(nums) - 2 * k.
         *  If min(nums) + k >= max(nums) - k, then return 0.
         */
        int max = *max_element(nums.begin(), nums.end());
        int min = *min_element(nums.begin(), nums.end());
        if ((min + k) < (max - k)) {
            retVal = max - min - 2 * k;
        }

        return retVal;
    }
};
```

</details>
