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

An integer n is a power of two, if there exists an integer x such that n == 2x.

Example 1:
Input: n = 1
Output: true
Explanation: 20 = 1

Example 2:
Input: n = 16
Output: true
Explanation: 24 = 16

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

## [1071. Greatest Common Divisor of Strings](https://leetcode.com/problems/greatest-common-divisor-of-strings/)  1397

- [Official](https://leetcode.com/problems/greatest-common-divisor-of-strings/editorial/)
- [Official](https://leetcode.cn/problems/greatest-common-divisor-of-strings/solutions/143956/zi-fu-chuan-de-zui-da-gong-yin-zi-by-leetcode-solu/)

<details><summary>Description</summary>

```text
For two strings s and t, we say "t divides s" if and only if s = t + ... + t
(i.e., t is concatenated with itself one or more times).

Given two strings str1 and str2, return the largest string x such that x divides both str1 and str2.

Example 1:
Input: str1 = "ABCABC", str2 = "ABC"
Output: "ABC"

Example 2:
Input: str1 = "ABABAB", str2 = "ABAB"
Output: "AB"

Example 3:
Input: str1 = "LEET", str2 = "CODE"
Output: ""

Constraints:
1 <= str1.length, str2.length <= 1000
str1 and str2 consist of English uppercase letters.
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
char* gcdOfStrings(char* str1, char* str2) {
    char* pRetVal = NULL;

    /* Math: Greatest Common Divisor
     *  if str1 and str2 have Greatest Common Divisor of Strings
     *  let str1 = m * (substr), str2 = n * (substr)
     *  => str1 + str2 = m * (substr) + n * (substr) = (m + n)(substr)
     *  => str2 + str1 = n * (substr) + m * (substr) = (n + m)(substr)
     *  => str1 + str2 = str2 + str1
     *  let lenStr1 = m * lenSubstr, lenStr2 = n * lenSubstr
     *  => gcd(lenStr1, lenStr2) = lenSubstr
     *  Hence, str1 and str2 Greatest Common Divisor of Strings is str1[0:lenSubstr] or str2[0:lenSubstr]
     */
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int gcdLen = gcd(len1, len2);
    pRetVal = (char*)calloc(gcdLen + 1, sizeof(char));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }

    char buf1[len1 + len2 + 1];
    memset(buf1, 0, sizeof(buf1));
    snprintf(buf1, sizeof(buf1), "%s%s", str1, str2);
    char buf2[len1 + len2 + 1];
    memset(buf2, 0, sizeof(buf1));
    snprintf(buf2, sizeof(buf2), "%s%s", str2, str1);
    if (strcmp(buf1, buf2) != 0) {
        return pRetVal;
    }
    memcpy(pRetVal, str1, gcdLen);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string gcdOfStrings(string str1, string str2) {
        string retVal = "";

        /* Math: Greatest Common Divisor
         *  if str1 and str2 have Greatest Common Divisor of Strings
         *  let str1 = m * (substr), str2 = n * (substr)
         *  => str1 + str2 = m * (substr) + n * (substr) = (m + n)(substr)
         *  => str2 + str1 = n * (substr) + m * (substr) = (n + m)(substr)
         *  => str1 + str2 = str2 + str1
         *  let lenStr1 = m * lenSubstr, lenStr2 = n * lenSubstr
         *  => gcd(lenStr1, lenStr2) = lenSubstr
         *  Hence, str1 and str2 Greatest Common Divisor of Strings is str1[0:lenSubstr] or str2[0:lenSubstr]
         */
        if (str1 + str2 != str2 + str1) {
            return retVal;
        }

        int gcdLength = gcd(str1.size(), str2.size());
        retVal = str1.substr(0, gcdLength);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def gcdOfStrings(self, str1: str, str2: str) -> str:
        retVal = ""

        # /* Math: Greatest Common Divisor
        #  *  if str1 and str2 have Greatest Common Divisor of Strings
        #  *  let str1 = m * (substr), str2 = n * (substr)
        #  *  => str1 + str2 = m * (substr) + n * (substr) = (m + n)(substr)
        #  *  => str2 + str1 = n * (substr) + m * (substr) = (n + m)(substr)
        #  *  => str1 + str2 = str2 + str1
        #  *  let lenStr1 = m * lenSubstr, lenStr2 = n * lenSubstr
        #  *  => gcd(lenStr1, lenStr2) = lenSubstr
        #  *  Hence, str1 and str2 Greatest Common Divisor of Strings is str1[0:lenSubstr] or str2[0:lenSubstr]
        #  */
        if str1 + str2 != str2 + str1:
            return retVal

        gcdLength = gcd(len(str1), len(str2))
        retVal = str1[:gcdLength]

        return retVal
```

</details>

## [1217. Minimum Cost to Move Chips to The Same Position](https://leetcode.com/problems/minimum-cost-to-move-chips-to-the-same-position/)  1407

- [Official](https://leetcode.com/problems/minimum-cost-to-move-chips-to-the-same-position/solutions/845669/minimum-cost-to-move-chips-to-the-same-position/)
- [Official](https://leetcode.cn/problems/minimum-cost-to-move-chips-to-the-same-position/solutions/1651725/wan-chou-ma-by-leetcode-solution-swnp/)

<details><summary>Description</summary>

```text
We have n chips, where the position of the ith chip is position[i].

We need to move all the chips to the same position. In one step, we can change the position of the ith chip from position[i] to:
- position[i] + 2 or position[i] - 2 with cost = 0.
- position[i] + 1 or position[i] - 1 with cost = 1.
Return the minimum cost needed to move all the chips to the same position.

Example 1:
Input: position = [1,2,3]
Output: 1
Explanation: First step: Move the chip at position 3 to position 1 with cost = 0.
Second step: Move the chip at position 2 to position 1 with cost = 1.
Total cost is 1.

Example 2:
Input: position = [2,2,2,3,3]
Output: 2
Explanation: We can move the two chips at position  3 to position 2. Each move has cost = 1. The total cost = 2.

Example 3:
Input: position = [1,1000000000]
Output: 1

Constraints:
1 <= position.length <= 100
1 <= position[i] <= 10^9
```

</details>

<details><summary>C</summary>

```c
int minCostToMoveChips(int* position, int positionSize) {
    int retVal = 0;

    int odd = 0;
    int even = 0;
    int i;
    for (i = 0; i < positionSize; ++i) {
        if (position[i] % 2 == 0) {
            ++even;
        } else if (position[i] % 2 == 1) {
            ++odd;
        }
    }
    retVal = ((odd < even) ? odd : even);

    return retVal;
}
```

</details>

## [1232. Check If It Is a Straight Line](https://leetcode.com/problems/check-if-it-is-a-straight-line/)  1247

- [Official](https://leetcode.com/problems/check-if-it-is-a-straight-line/editorial/)
- [Official](https://leetcode.cn/problems/check-if-it-is-a-straight-line/solutions/562860/zhui-dian-cheng-xian-by-leetcode-solutio-lpt6/)

<details><summary>Description</summary>

```text
You are given an array coordinates, coordinates[i] = [x, y], where [x, y] represents the coordinate of a point.
Check if these points make a straight line in the XY plane.

Example 1:
Input: coordinates = [[1,2],[2,3],[3,4],[4,5],[5,6],[6,7]]
Output: true

Example 2:
Input: coordinates = [[1,1],[2,2],[3,4],[4,5],[5,6],[7,7]]
Output: false

Constraints:
2 <= coordinates.length <= 1000
coordinates[i].length == 2
-10^4 <= coordinates[i][0], coordinates[i][1] <= 10^4
coordinates contains no duplicate point.
```

<details><summary>Hint</summary>

```text
1. If there're only 2 points, return true.
2. Check if all other points lie on the line defined by the first 2 points.
3. Use cross product to check collinearity.
```

</details>

</details>

<details><summary>C</summary>

```c
bool checkStraightLine(int** coordinates, int coordinatesSize, int* coordinatesColSize) {
    bool retVal = true;

    if (coordinatesSize == 2) {
        return retVal;
    }

    // https://en.wikipedia.org/wiki/Cross_product
    int v1x, v1y;
    int v2x, v2y;
    int i;
    for (i = 2; i < coordinatesSize; ++i) {
        v1x = coordinates[i - 1][0] - coordinates[i - 2][0];
        v1y = coordinates[i - 1][1] - coordinates[i - 2][1];
        v2x = coordinates[i][0] - coordinates[i - 1][0];
        v2y = coordinates[i][1] - coordinates[i - 1][1];
        if ((v1x * v2y) != (v1y * v2x)) {
            retVal = false;
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
   public:
    bool checkStraightLine(vector<vector<int>>& coordinates) {
        bool retVal = true;

        int coordinatesSize = coordinates.size();
        if (coordinatesSize == 2) {
            return retVal;
        }

        // https://en.wikipedia.org/wiki/Cross_product
        for (int i = 2; i < coordinatesSize; ++i) {
            int v1x = coordinates[i - 1][0] - coordinates[i - 2][0];
            int v1y = coordinates[i - 1][1] - coordinates[i - 2][1];
            int v2x = coordinates[i][0] - coordinates[i - 1][0];
            int v2y = coordinates[i][1] - coordinates[i - 1][1];
            if ((v1x * v2y) != (v1y * v2x)) {
                retVal = false;
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
    def checkStraightLine(self, coordinates: List[List[int]]) -> bool:
        retVal = True

        coordinatesSize = len(coordinates)
        if coordinatesSize == 2:
            return retVal

        # // https://en.wikipedia.org/wiki/Cross_product
        for i in range(2, coordinatesSize):
            v1x = coordinates[i-1][0] - coordinates[i-2][0]
            v1y = coordinates[i-1][1] - coordinates[i-2][1]
            v2x = coordinates[i][0] - coordinates[i-1][0]
            v2y = coordinates[i][1] - coordinates[i-1][1]
            if v1x * v2y != v1y * v2x:
                retVal = False
                break

        return retVal
```

</details>

## [1250. Check If It Is a Good Array](https://leetcode.com/problems/check-if-it-is-a-good-array/)  1983

- [Official](https://leetcode.cn/problems/check-if-it-is-a-good-array/solutions/2110763/jian-cha-hao-shu-zu-by-leetcode-solution-qg2h/)

<details><summary>Description</summary>

```text
Given an array nums of positive integers.
Your task is to select some subset of nums, multiply each element by an integer and add all these numbers.
The array is said to be good if you can obtain a sum of 1 from the array by any possible subset and multiplicand.

Return True if the array is good otherwise return False.

Example 1:
Input: nums = [12,5,7,23]
Output: true
Explanation: Pick numbers 5 and 7.
5*3 + 7*(-2) = 1

Example 2:
Input: nums = [29,6,10]
Output: true
Explanation: Pick numbers 29, 6 and 10.
29*1 + 6*(-3) + 10*(-1) = 1

Example 3:
Input: nums = [3,6]
Output: false

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Eq. ax+by=1 has solution x, y if gcd(a,b) = 1.
2. Can you generalize the formula?. Check Bézout's lemma.
```

</details>

</details>

<details><summary>C</summary>

```c
int gcd(int a, int b) {
    int remainder;
    while (b != 0) {
        remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}
bool isGoodArray(int* nums, int numsSize) {
    bool retVal = false;

    /* Bézout's identity: https://en.wikipedia.org/wiki/B%C3%A9zout%27s_identity
     *  The basic idea is that for integers a and b,
     *  if gcd(a,b) = d, then there exist integers x and y, such that ax + by = d.
     *  This can be generalized for (n >= 2).
     *  if gcd(a,b,c) = d, then there exist integers x, y, and z, s.t, ax + by + cz = d.
     *
     *  Now this problem is just asking if gcd(x1, ......, xn) = 1
     */
    int d = gcd(nums[0], nums[0]);
    int i;
    for (i = 1; i < numsSize; ++i) {
        d = gcd(d, nums[i]);
    }
    if (d == 1) {
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
    bool isGoodArray(vector<int>& nums) {
        bool retVal = false;

        /* Bézout's identity: https://en.wikipedia.org/wiki/B%C3%A9zout%27s_identity
         *  The basic idea is that for integers a and b,
         *  if gcd(a,b) = d, then there exist integers x and y, such that ax + by = d.
         *  This can be generalized for (n >= 2).
         *  if gcd(a,b,c) = d, then there exist integers x, y, and z, s.t, ax + by + cz = d.
         *
         *  Now this problem is just asking if gcd(x1, ......, xn) = 1
         */
        int len = nums.size();
        int d = __gcd(nums[0], nums[0]);
        for (int i = 1; i < len; ++i) {
            d = __gcd(d, nums[i]);
        }
        if (d == 1) {
            retVal = true;
        }

        return retVal;
    }
};
```

</details>

## [1266. Minimum Time Visiting All Points](https://leetcode.com/problems/minimum-time-visiting-all-points/)  1302

- [Official](https://leetcode.com/problems/minimum-time-visiting-all-points/editorial/)
- [Official](https://leetcode.cn/problems/minimum-time-visiting-all-points/solutions/101816/fang-wen-suo-you-dian-de-zui-xiao-shi-jian-by-le-2/)

<details><summary>Description</summary>

```text
On a 2D plane, there are n points with integer coordinates points[i] = [xi, yi].
Return the minimum time in seconds to visit all the points in the order given by points.

You can move according to these rules:
- In 1 second, you can either:
  - move vertically by one unit,
  - move horizontally by one unit, or
  - move diagonally sqrt(2) units (in other words, move one unit vertically then one unit horizontally in 1 second).
- You have to visit the points in the same order as they appear in the array.
- You are allowed to pass through points that appear later in the order, but these do not count as visits.

Example 1:
Input: points = [[1,1],[3,4],[-1,0]]
Output: 7
Explanation: One optimal path is [1,1] -> [2,2] -> [3,3] -> [3,4] -> [2,3] -> [1,2] -> [0,1] -> [-1,0]
Time from [1,1] to [3,4] = 3 seconds
Time from [3,4] to [-1,0] = 4 seconds
Total time = 7 seconds

Example 2:
Input: points = [[3,2],[-2,2]]
Output: 5

Constraints:
points.length == n
1 <= n <= 100
points[i].length == 2
-1000 <= points[i][0], points[i][1] <= 1000
```

<details><summary>Hint</summary>

```text
1. To walk from point A to point B there will be an optimal strategy to walk ?
2. Advance in diagonal as possible then after that go in straight line.
3. Repeat the process until visiting all the points.
```

</details>

</details>

<details><summary>C</summary>

```c
int minTimeToVisitAllPoints(int** points, int pointsSize, int* pointsColSize) {
    int retVal = 0;

    int diffX, diffY;
    int i;
    for (i = 1; i < pointsSize; ++i) {
        diffX = abs(points[i - 1][0] - points[i][0]);
        diffY = abs(points[i - 1][1] - points[i][1]);
        retVal += fmax(diffX, diffY);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minTimeToVisitAllPoints(vector<vector<int>>& points) {
        int retVal = 0;

        int pointsSize = points.size();
        for (int i = 1; i < pointsSize; ++i) {
            int diffX = abs(points[i - 1][0] - points[i][0]);
            int diffY = abs(points[i - 1][1] - points[i][1]);
            retVal += max(diffX, diffY);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minTimeToVisitAllPoints(self, points: List[List[int]]) -> int:
        retVal = 0

        pointsSize = len(points)
        for i in range(1, pointsSize):
            diffX = abs(points[i-1][0] - points[i][0])
            diffY = abs(points[i-1][1] - points[i][1])
            retVal += max(diffX, diffY)

        return retVal
```

</details>

## [1281. Subtract the Product and Sum of Digits of an Integer](https://leetcode.com/problems/subtract-the-product-and-sum-of-digits-of-an-integer/)  1141

<details><summary>Description</summary>

```text
Given an integer number n, return the difference between the product of its digits and the sum of its digits.

Example 1:
Input: n = 234
Output: 15
Explanation:
Product of digits = 2 * 3 * 4 = 24
Sum of digits = 2 + 3 + 4 = 9
Result = 24 - 9 = 15

Example 2:
Input: n = 4421
Output: 21
Explanation:
Product of digits = 4 * 4 * 2 * 1 = 32
Sum of digits = 4 + 4 + 2 + 1 = 11
Result = 32 - 11 = 21

Constraints:
1 <= n <= 10^5
```

</details>

<details><summary>C</summary>

```c
int subtractProductAndSum(int n) {
    int retVal = 0;

    int product = 1;
    int sum = 0;
    int mod;
    while (n > 0) {
        mod = n % 10;
        product *= mod;
        sum += mod;
        n /= 10;
    }
    retVal = product - sum;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
public:
    int subtractProductAndSum(int n) {
        int retVal;

        int mod;
        int product = 1;
        int sum = 0;
        while (n > 0) {
            mod = n % 10;
            product *= mod;
            sum += mod;
            n /= 10;
        }
        retVal = product - sum;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def subtractProductAndSum(self, n: int) -> int:
        method = 1

        if method == 1:
            print("= math computing =")

            product = 1
            sum = 0
            while (n > 0):
                mod = n % 10
                product *= mod
                sum += mod
                n //= 10
            retVal = product - sum

            return retVal
        elif method == 2:
            print("= python function =")

            a = [int(x) for x in str(n)]
            return reduce((lambda x, y: x * y), a) - reduce((lambda x, y: x + y), a)
```

</details>

## [1323. Maximum 69 Number](https://leetcode.com/problems/maximum-69-number/)  1193

<details><summary>Description</summary>

```text
You are given a positive integer num consisting only of digits 6 and 9.

Return the maximum number you can get by changing at most one digit (6 becomes 9, and 9 becomes 6).

Example 1:
Input: num = 9669
Output: 9969
Explanation:
Changing the first digit results in 6669.
Changing the second digit results in 9969.
Changing the third digit results in 9699.
Changing the fourth digit results in 9666.
The maximum number is 9969.

Example 2:
Input: num = 9996
Output: 9999
Explanation: Changing the last digit 6 to 9 results in the maximum number.

Example 3:
Input: num = 9999
Output: 9999
Explanation: It is better not to apply any change.

Constraints:
1 <= num <= 10^4
num consists of only 6 and 9 digits.
```

</details>

<details><summary>C</summary>

```c
int maximum69Number(int num) {
    int retVal = num;

    int add = 0;
    int multiplier = 1;
    int mod;
    while (num > 0) {
        mod = num % 10;
        if (mod == 6) {
            add = 3 * multiplier;
        }

        num -= mod;
        num /= 10;
        multiplier *= 10;
    }
    retVal += add;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
public:
    int maximum69Number(int num) {
        int retVal = num;

        int add = 0;
        int multiplier = 1;
        int mod;
        while (num > 0) {
            mod = num % 10;
            if (mod == 6) {
                add = 3 * multiplier;
            }

            num -= mod;
            num /= 10;
            multiplier *= 10;
        }
        retVal += add;

        return retVal;
    }
};
```

</details>

## [1518. Water Bottles](https://leetcode.com/problems/water-bottles/)  1245

- [Official](https://leetcode.com/problems/water-bottles/editorial/)
- [Official](https://leetcode.cn/problems/water-bottles/solutions/339339/huan-jiu-wen-ti-by-leetcode-solution/)

<details><summary>Description</summary>

```text
There are numBottles water bottles that are initially full of water.
You can exchange numExchange empty water bottles from the market with one full water bottle.

The operation of drinking a full water bottle turns it into an empty bottle.

Given the two integers numBottles and numExchange, return the maximum number of water bottles you can drink.

Example 1:
Input: numBottles = 9, numExchange = 3
Output: 13
Explanation: You can exchange 3 empty bottles to get 1 full water bottle.
Number of water bottles you can drink: 9 + 3 + 1 = 13.

Example 2:
Input: numBottles = 15, numExchange = 4
Output: 19
Explanation: You can exchange 4 empty bottles to get 1 full water bottle.
Number of water bottles you can drink: 15 + 3 + 1 = 19.

Constraints:
1 <= numBottles <= 100
2 <= numExchange <= 100
```

<details><summary>Hint</summary>

```text
1. Simulate the process until there are not enough empty bottles for even one full bottle of water.
```

</details>

</details>

<details><summary>C</summary>

```c
int numWaterBottles(int numBottles, int numExchange) {
    int retVal = 0;

    int times;
    int consumedBottles = 0;
    while (numBottles >= numExchange) {
        times = numBottles / numExchange;
        consumedBottles += (numExchange * times);
        numBottles -= (numExchange * times);
        numBottles += times;
    }
    retVal = consumedBottles + numBottles;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int numWaterBottles(int numBottles, int numExchange) {
        int retVal = 0;

        int consumedBottles = 0;
        while (numBottles >= numExchange) {
            int times = numBottles / numExchange;
            consumedBottles += (numExchange * times);
            numBottles -= (numExchange * times);
            numBottles += times;
        }
        retVal = consumedBottles + numBottles;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def numWaterBottles(self, numBottles: int, numExchange: int) -> int:
        retVal = 0

        consumedBottles = 0
        while numBottles >= numExchange:
            times = numBottles // numExchange
            consumedBottles += (numExchange * times)
            numBottles -= (numExchange * times)
            numBottles += times
        retVal = consumedBottles + numBottles

        return retVal
```

</details>

## [1523. Count Odd Numbers in an Interval Range](https://leetcode.com/problems/count-odd-numbers-in-an-interval-range/)  1209

- [Official](https://leetcode.com/problems/count-odd-numbers-in-an-interval-range/editorial/)
- [Official](https://leetcode.cn/problems/count-odd-numbers-in-an-interval-range/solutions/371283/zai-qu-jian-fan-wei-nei-tong-ji-qi-shu-shu-mu-by-l/)

<details><summary>Description</summary>

```text
Given two non-negative integers low and high. Return the count of odd numbers between low and high (inclusive).

Example 1:
Input: low = 3, high = 7
Output: 3
Explanation: The odd numbers between 3 and 7 are [3,5,7].

Example 2:
Input: low = 8, high = 10
Output: 1
Explanation: The odd numbers between 8 and 10 are [9].

Constraints:
0 <= low <= high <= 10^9
```

<details><summary>Hint</summary>

```text
1. If the range (high - low + 1) is even, the number of even and odd numbers in this range will be the same.
2. If the range (high - low + 1) is odd, the solution will depend on the parity of high and low.
```

</details>

</details>

<details><summary>C</summary>

```c
int countOdds(int low, int high) {
    int retVal = 0;

    int range = high - low + 1;
    retVal = range / 2;
    if ((range % 2) == 1) {
        retVal = (((low % 2) == 1) || ((high % 2) == 1)) ? retVal + 1 : retVal;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int countOdds(int low, int high) {
        int retVal = 0;

        int range = high - low + 1;
        retVal = range / 2;
        if ((range % 2) == 1) {
            retVal = (((low % 2) == 1) || ((high % 2) == 1)) ? retVal + 1 : retVal;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def countOdds(self, low: int, high: int) -> int:
        range = high - low + 1
        retVal = range // 2
        if ((range % 2) == 1):
            retVal = retVal+1 if (((low % 2) == 1) or ((high % 2) == 1)) else retVal

        return retVal
```

</details>

## [1588. Sum of All Odd Length Subarrays](https://leetcode.com/problems/sum-of-all-odd-length-subarrays/)  1408

- [Official](https://leetcode.com/problems/sum-of-all-odd-length-subarrays/solutions/2773805/sum-of-all-odd-length-subarrays/)
- [Official](https://leetcode.cn/problems/sum-of-all-odd-length-subarrays/solutions/964878/suo-you-qi-shu-chang-du-zi-shu-zu-de-he-yoaqu/)

<details><summary>Description</summary>

```text
Given an array of positive integers arr, return the sum of all possible odd-length subarrays of arr.

A subarray is a contiguous subsequence of the array.

Example 1:
Input: arr = [1,4,2,5,3]
Output: 58
Explanation: The odd-length subarrays of arr and their sums are:
[1] = 1
[4] = 4
[2] = 2
[5] = 5
[3] = 3
[1,4,2] = 7
[4,2,5] = 11
[2,5,3] = 10
[1,4,2,5,3] = 15
If we add all these together we get 1 + 4 + 2 + 5 + 3 + 7 + 11 + 10 + 15 = 58

Example 2:
Input: arr = [1,2]
Output: 3
Explanation: There are only 2 subarrays of odd length, [1] and [2]. Their sum is 3.

Example 3:
Input: arr = [10,11,12]
Output: 66

Constraints:
1 <= arr.length <= 100
1 <= arr[i] <= 1000

Follow up:
Could you solve this problem in O(n) time complexity?
```

</details>

<details><summary>C</summary>

```c
#define ARRAY_BRUTE_FORCE       (0) // Time Complexity: O(n^3), Space Complexity: O(1).
#define ARRAY_TWO_LOOP          (0) // Time Complexity: O(n^2), Space Complexity: O(1).
#define MATH_INDEX_OCCURRENCE   (1) // Time Complexity: O(n), Space Complexity: O(1).

int sumOddLengthSubarrays(int* arr, int arrSize) {
    int retVal = 0;

#if (ARRAY_BRUTE_FORCE)
    printf("Approach 1: Brute Force\n");

    int sum, idx;
    int start, end;
    for (start=0; start<arrSize; ++start) {
        for (end=start; end<arrSize; ++end) {
            if (((end-start+1)%2) == 0) {
                continue;
            }
            sum = 0;
            for (idx=start; idx<=end; ++idx) {
                sum += arr[idx];
            }
            retVal += sum;
        }
    }
#elif (ARRAY_TWO_LOOP)
    printf("Approach 2: Two Loops\n");

    int sum;
    int start, end;
    for (start=0; start<arrSize; ++start) {
        sum = 0;
        for (end=start; end<arrSize; ++end) {
            sum += arr[end];
            if (((end-start+1)%2) == 1) {
                retVal += sum;
            }
        }
    }
#elif (MATH_INDEX_OCCURRENCE)
    printf("Approach 3: Check the occurrence of each index\n");

    int oddLeft, oddRight;
    int evenLeft, evenRight;
    int head, tail;
    int i;
    for (i=0; i<arrSize; ++i) {
        head = i;
        tail = arrSize - i - 1;

        oddLeft = (head / 2) + 1;
        oddRight = (tail / 2) + 1;
        evenLeft = (head + 1) / 2;
        evenRight = (tail + 1) / 2;

        retVal += (arr[i] * (oddLeft * oddRight));
        retVal += (arr[i] * (evenLeft * evenRight));
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
#define ARRAY_BRUTE_FORCE       (0) // Time Complexity: O(n^3), Space Complexity: O(1).
#define ARRAY_TWO_LOOP          (0) // Time Complexity: O(n^2), Space Complexity: O(1).
#define MATH_INDEX_OCCURRENCE   (1) // Time Complexity: O(n), Space Complexity: O(1).
    int sumOddLengthSubarrays(vector<int>& arr) {
        int retVal = 0;

        int arrSize = arr.size();
#if (ARRAY_BRUTE_FORCE)
        cout << "Approach 1: Brute Force" << "\n";

        int sum, idx;
        int start, end;
        for (start=0; start<arrSize; ++start) {
            for (end=start; end<arrSize; ++end) {
                if (((end-start+1)%2) == 0) {
                    continue;
                }
                sum = 0;
                for (idx=start; idx<=end; ++idx) {
                    sum += arr[idx];
                }
                retVal += sum;
            }
        }
#elif (ARRAY_TWO_LOOP)
        cout <<  "Approach 2: Two Loops" << "\n";

        int sum;
        int start, end;
        for (start=0; start<arrSize; ++start) {
            sum = 0;
            for (end=start; end<arrSize; ++end) {
                sum += arr[end];
                if (((end-start+1)%2) == 1) {
                    retVal += sum;
                }
            }
        }
#elif (MATH_INDEX_OCCURRENCE)
        cout << "Approach 3: Check the occurrence of each index" << "\n";

        int oddLeft, oddRight;
        int evenLeft, evenRight;
        int head, tail;
        int i;
        for (i=0; i<arrSize; ++i) {
            head = i;
            tail = arrSize - i - 1;

            oddLeft = (head / 2) + 1;
            oddRight = (tail / 2) + 1;
            evenLeft = (head + 1) / 2;
            evenRight = (tail + 1) / 2;

            retVal += (arr[i] * (oddLeft * oddRight));
            retVal += (arr[i] * (evenLeft * evenRight));
        }
#endif

        return retVal;
    }
};
```

</details>

## [1688. Count of Matches in Tournament](https://leetcode.com/problems/count-of-matches-in-tournament/)  1203

- [Official](https://leetcode.com/problems/count-of-matches-in-tournament/editorial/)
- [Official](https://leetcode.cn/problems/count-of-matches-in-tournament/solutions/1230104/bi-sai-zhong-de-pei-dui-ci-shu-by-leetco-ugvj/)

<details><summary>Description</summary>

```text
You are given an integer n, the number of teams in a tournament that has strange rules:
- If the current number of teams is even, each team gets paired with another team.
  A total of n / 2 matches are played, and n / 2 teams advance to the next round.
- If the current number of teams is odd, one team randomly advances in the tournament, and the rest gets paired.
  A total of (n - 1) / 2 matches are played, and (n - 1) / 2 + 1 teams advance to the next round.

Return the number of matches played in the tournament until a winner is decided.

Example 1:
Input: n = 7
Output: 6
Explanation: Details of the tournament:
- 1st Round: Teams = 7, Matches = 3, and 4 teams advance.
- 2nd Round: Teams = 4, Matches = 2, and 2 teams advance.
- 3rd Round: Teams = 2, Matches = 1, and 1 team is declared the winner.
Total number of matches = 3 + 2 + 1 = 6.

Example 2:
Input: n = 14
Output: 13
Explanation: Details of the tournament:
- 1st Round: Teams = 14, Matches = 7, and 7 teams advance.
- 2nd Round: Teams = 7, Matches = 3, and 4 teams advance.
- 3rd Round: Teams = 4, Matches = 2, and 2 teams advance.
- 4th Round: Teams = 2, Matches = 1, and 1 team is declared the winner.
Total number of matches = 7 + 3 + 2 + 1 = 13.

Constraints:
1 <= n <= 200
```

<details><summary>Hint</summary>

```text
1. Simulate the tournament as given in the statement.
2. Be careful when handling odd integers.
```

</details>

</details>

<details><summary>C</summary>

```c
int numberOfMatches(int n) {
    int retVal = 0;

    int next;
    while (n > 1) {
        next = n >> 1;
        n -= next;
        retVal += next;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int numberOfMatches(int n) {
        int retVal = 0;

        while (n > 1) {
            int next = n >> 1;
            n -= next;
            retVal += next;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def numberOfMatches(self, n: int) -> int:
        retVal = 0

        while n > 1:
            next = n >> 1
            n -= next
            retVal += next

        return retVal
```

</details>

## [1716. Calculate Money in Leetcode Bank](https://leetcode.com/problems/calculate-money-in-leetcode-bank/)

- [Official](https://leetcode.com/problems/calculate-money-in-leetcode-bank/editorial/)
- [Official](https://leetcode.cn/problems/calculate-money-in-leetcode-bank/solutions/1210174/ji-suan-li-kou-yin-xing-de-qian-by-leetc-xogx/)

<details><summary>Description</summary>

```text
Hercy wants to save money for his first car. He puts money in the Leetcode bank every day.

He starts by putting in $1 on Monday, the first day. Every day from Tuesday to Sunday,
he will put in $1 more than the day before.
On every subsequent Monday, he will put in $1 more than the previous Monday.

Given n, return the total amount of money he will have in the Leetcode bank at the end of the nth day.

Example 1:
Input: n = 4
Output: 10
Explanation: After the 4th day, the total is 1 + 2 + 3 + 4 = 10.

Example 2:
Input: n = 10
Output: 37
Explanation: After the 10th day, the total is (1 + 2 + 3 + 4 + 5 + 6 + 7) + (2 + 3 + 4) = 37.
Notice that on the 2nd Monday, Hercy only puts in $2.

Example 3:
Input: n = 20
Output: 96
Explanation: After the 20th day,
the total is (1 + 2 + 3 + 4 + 5 + 6 + 7) + (2 + 3 + 4 + 5 + 6 + 7 + 8) + (3 + 4 + 5 + 6 + 7 + 8) = 96.

Constraints:
1 <= n <= 1000
```

<details><summary>Hint</summary>

```text
1. Simulate the process by keeping track of how much money John is putting in and which day of the week it is,
   and use this information to deduce how much money John will put in the next day.
```

</details>

</details>

<details><summary>C</summary>

```c
int totalMoney(int n) {
    int retVal = 0;

    int weeks = n / 7;
    int days = n % 7;

    int firstWeek = (1 + 7) * 7 / 2;
    int lastWeek = firstWeek + (weeks - 1) * 7;
    int weeksMoney = (firstWeek + lastWeek) * weeks / 2;

    int dyasMoney = 0;
    int monday = 1 + weeks;
    int i;
    for (i = 0; i < days; ++i) {
        dyasMoney += (monday + i);
    }

    retVal = weeksMoney + dyasMoney;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int totalMoney(int n) {
        int retVal = 0;

        int weeks = n / 7;
        int days = n % 7;

        int firstWeek = (1 + 7) * 7 / 2;
        int lastWeek = firstWeek + (weeks - 1) * 7;
        int weeksMoney = (firstWeek + lastWeek) * weeks / 2;

        int dyasMoney = 0;
        int monday = 1 + weeks;
        for (int i = 0; i < days; ++i) {
            dyasMoney += (monday + i);
        }

        retVal = weeksMoney + dyasMoney;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def totalMoney(self, n: int) -> int:
        retVal = 0

        weeks = n // 7
        days = n % 7

        firstWeek = (1 + 7) * 7 // 2
        lastWeek = firstWeek + (weeks-1) * 7
        weeksMoney = (firstWeek + lastWeek) * weeks // 2

        dyasMoney = 0
        monday = 1 + weeks
        for i in range(days):
            dyasMoney += (monday + i)

        retVal = weeksMoney + dyasMoney

        return retVal
```

</details>

## [1759. Count Number of Homogenous Substrings](https://leetcode.com/problems/count-number-of-homogenous-substrings/)  1490

- [Official](https://leetcode.com/problems/count-number-of-homogenous-substrings/editorial/)
- [Official](https://leetcode.cn/problems/count-number-of-homogenous-substrings/solutions/2031869/tong-ji-tong-gou-zi-zi-fu-chuan-de-shu-m-tw5m/)

<details><summary>Description</summary>

```text
Given a string s, return the number of homogenous substrings of s.
Since the answer may be too large, return it modulo 10^9 + 7.

A string is homogenous if all the characters of the string are the same.

A substring is a contiguous sequence of characters within a string.

Example 1:
Input: s = "abbcccaa"
Output: 13
Explanation: The homogenous substrings are listed as below:
"a"   appears 3 times.
"aa"  appears 1 time.
"b"   appears 2 times.
"bb"  appears 1 time.
"c"   appears 3 times.
"cc"  appears 2 times.
"ccc" appears 1 time.
3 + 1 + 2 + 1 + 3 + 2 + 1 = 13.

Example 2:
Input: s = "xy"
Output: 2
Explanation: The homogenous substrings are "x" and "y".

Example 3:
Input: s = "zzzzz"
Output: 15

Constraints:
1 <= s.length <= 10^5
s consists of lowercase letters.
```

<details><summary>Hint</summary>

```text
1. A string of only 'a's of length k contains k choose 2 homogenous substrings.
2. Split the string into substrings where each substring contains only one letter,
   and apply the formula on each substring's length.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MODULO (int)(1e9 + 7)
int countHomogenous(char* s) {
    int retVal = 1;  // 1 <= s.length <= 10^5

    int sSize = strlen(s);
    int homogenous = 1;
    int i;
    for (i = 1; i < sSize; ++i) {
        if (s[i - 1] == s[i]) {
            homogenous += 1;
        } else {
            homogenous = 1;
        }

        retVal += homogenous;
        retVal %= MODULO;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define MODULO (int)(1e9 + 7)
   public:
    int countHomogenous(string s) {
        int retVal = 1;  // 1 <= s.length <= 10^5

        int sSize = s.size();
        int homogenous = 1;
        for (int i = 1; i < sSize; ++i) {
            if (s[i - 1] == s[i]) {
                homogenous += 1;
            } else {
                homogenous = 1;
            }

            retVal += homogenous;
            retVal %= MODULO;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def __init__(self):
        self.MODULO = 10 ** 9 + 7

    def countHomogenous(self, s: str) -> int:
        retVal = 1  # 1 <= s.length <= 10^5

        sSize = len(s)
        homogenous = 1
        for i in range(1, sSize):
            if s[i-1] == s[i]:
                homogenous += 1
            else:
                homogenous = 1

            retVal += homogenous
            retVal %= self.MODULO

        return retVal
```

</details>

## [1780. Check if Number is a Sum of Powers of Three](https://leetcode.com/problems/check-if-number-is-a-sum-of-powers-of-three/)  1505

- [Official](https://leetcode.com/problems/check-if-number-is-a-sum-of-powers-of-three/editorial/)
- [Official](https://leetcode.cn/problems/check-if-number-is-a-sum-of-powers-of-three/solutions/2011470/pan-duan-yi-ge-shu-zi-shi-fou-ke-yi-biao-0j5k/)

<details><summary>Description</summary>

```text
Given an integer n, return true if it is possible to represent n as the sum of distinct powers of three.
Otherwise, return false.

An integer y is a power of three if there exists an integer x such that y == 3x.

Example 1:
Input: n = 12
Output: true
Explanation: 12 = 31 + 32

Example 2:
Input: n = 91
Output: true
Explanation: 91 = 30 + 32 + 34

Example 3:
Input: n = 21
Output: false

Constraints:
1 <= n <= 10^7
```

<details><summary>Hint</summary>

```text
1. Let's note that the maximum power of 3 you'll use in your soln is 3^16
2. The number can not be represented as a sum of powers of 3 if it's ternary presentation has a 2 in it
```

</details>

</details>

<details><summary>C</summary>

```c
bool checkPowersOfThree(int n) {
    bool retVal = false;

    /* get MAX power of three
     *  n = 3^x
     *  => log(n) = x * log(3)
     *  => x = log(n) / log(3)
     */
    int x = log10(n) / log10(3);

    // check the sum of distinct powers of three
    int powValue;
    int i;
    for (i = x; i >= 0; --i) {
        powValue = pow(3, i);
        if (n >= powValue) {
            n -= powValue;
        }
    }

    if (n == 0) {
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
    bool checkPowersOfThree(int n) {
        bool retVal = false;

        /*  可以將 n 轉換成 3 進位
         *  如果 n 的 3 進制表示中每一位均不為 2, 那麼答案為 True, 否則為 False.
         *  例如, 當 n = 12 時, 12 = 110, 滿足要求; 當 n = 21 時, 21 = 210, 不滿足要求.
         */
        while (n > 0) {
            if (n % 3 == 2) {  // Check if this power should be used twice
                return retVal;
            }
            n /= 3;  // Divide n by 3 to move to the next greater power
        }
        retVal = true;  // The ternary representation of n consists only of 0s and 1s

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def checkPowersOfThree(self, n: int) -> bool:
        retVal = False

        # 可以將 n 轉換成 3 進位
        # 如果 n 的 3 進制表示中每一位均不為 2, 那麼答案為 True, 否則為 False.
        # 例如, 當 n = 12 時, 12 = 110, 滿足要求; 當 n = 21 時, 21 = 210, 不滿足要求.
        while n > 0:
            if n % 3 == 2:  # Check if this power should be used twice
                return retVal
            n //= 3  # Divide n by 3 to move to the next greater power
        retVal = True  # The ternary representation of n consists only of 0s and 1s

        return retVal
```

</details>

## [1812. Determine Color of a Chessboard Square](https://leetcode.com/problems/determine-color-of-a-chessboard-square/)  1328

- [Official](https://leetcode.cn/problems/determine-color-of-a-chessboard-square/solutions/2009904/pan-duan-guo-ji-xiang-qi-qi-pan-zhong-yi-8dv4/)

<details><summary>Description</summary>

```text
You are given coordinates, a string that represents the coordinates of a square of the chessboard.
Below is a chessboard for your reference.
 8 | W B W B W B W B
 7 | B W B W B W B W
 6 | W B W B W B W B
 5 | B W B W B W B W
 4 | W B W B W B W B
 3 | B W B W B W B W
 2 | W B W B W B W B
 1 | B W B W B W B W
---------------------
   | a b c d e f g h

Return true if the square is white, and false if the square is black.

The coordinate will always represent a valid chessboard square.
The coordinate will always have the letter first, and the number second.

Example 1:
Input: coordinates = "a1"
Output: false
Explanation: From the chessboard above, the square with coordinates "a1" is black, so return false.

Example 2:
Input: coordinates = "h3"
Output: true
Explanation: From the chessboard above, the square with coordinates "h3" is white, so return true.

Example 3:
Input: coordinates = "c7"
Output: false

Constraints:
coordinates.length == 2
a <= coordinates[0] <= h
1 <= coordinates[1] <= 8
```

<details><summary>Hint</summary>

```text
1. Convert the coordinates to (x, y) - that is, "a1" is (1, 1), "d7" is (4, 7).
2. Try add the numbers together and look for a pattern.
```

</details>

</details>

<details><summary>C</summary>

```c
bool squareIsWhite(char* coordinates) {
    bool retVal = false;

    if (strlen(coordinates) != 2) {
        return retVal;
    }

    int row = coordinates[0] - 'a';
    int col = coordinates[1] - '0';
    if (((row%2)==0) && ((col%2)==0)) {
        retVal = true;
    }
    else if (((row%2)==1) && ((col%2)==1)) {
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
    bool squareIsWhite(string coordinates) {
        bool retVal = false;

        if (coordinates.length() != 2) {
            return retVal;
        }

        int row = coordinates[0] - 'a';
        int col = coordinates[1] - '0';
        if (((row%2)==0) && ((col%2)==0)) {
            retVal = true;
        }
        else if (((row%2)==1) && ((col%2)==1)) {
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
    def squareIsWhite(self, coordinates: str) -> bool:
        if (len(coordinates) != 2):
            return False

        row = ord(coordinates[0]) - ord('a')
        col = ord(coordinates[1]) - ord('0')
        if (((row%2)==0) and ((col%2)==0)):
            return True
        elif (((row%2)==1) and ((col%2)==1)):
            return True

        return False
```

</details>

## [1819. Number of Different Subsequences GCDs](https://leetcode.com/problems/number-of-different-subsequences-gcds/)  2539

- [Official](https://leetcode.cn/problems/number-of-different-subsequences-gcds/solutions/2060230/xu-lie-zhong-bu-tong-zui-da-gong-yue-shu-ha1j/)

<details><summary>Description</summary>

```text
You are given an array nums that consists of positive integers.

The GCD of a sequence of numbers is defined as the greatest integer that divides all the numbers in the sequence evenly.
- For example, the GCD of the sequence [4,6,16] is 2.

A subsequence of an array is a sequence that can be formed by removing some elements (possibly none) of the array.
- For example, [2,5,10] is a subsequence of [1,2,1,2,4,1,5,10].

Return the number of different GCDs among all non-empty subsequences of nums.

Example 1:
Input: nums = [6,10,3]
Output: 5
Explanation: The figure shows all the non-empty subsequences and their GCDs.
The different GCDs are 6, 10, 3, 2, and 1.

Example 2:
Input: nums = [5,15,40,5,6]
Output: 7

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 2 * 10^5
```

</details>

<details><summary>C</summary>

```c
int gcd(int a, int b) {
    int remainder;
    while (b != 0) {
        remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}
int countDifferentSubsequenceGCDs(int* nums, int numsSize) {
    int retVal = 0;

    int i, j;

    int maxNums = 0;
    for (i = 0; i < numsSize; ++i) {
        maxNums = fmax(maxNums, nums[i]);
    }
    bool NumsExist[maxNums + 1];
    memset(NumsExist, false, sizeof(NumsExist));
    for (i = 0; i < numsSize; ++i) {
        NumsExist[nums[i]] = true;
    }

    int subGcd;
    for (i = 1; i <= maxNums; i++) {
        subGcd = 0;
        for (j = i; j <= maxNums; j += i) {
            if (NumsExist[j] == false) {
                continue;
            }

            if (subGcd == 0) {
                subGcd = j;
            } else {
                subGcd = gcd(subGcd, j);
            }

            if (subGcd == i) {
                ++retVal;
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
    int countDifferentSubsequenceGCDs(vector<int>& nums) {
        int retVal = 0;

        int maxNums = *max_element(nums.begin(), nums.end());
        vector<bool> NumsExist(maxNums + 1, false);
        for (auto num : nums) {
            NumsExist[num] = true;
        }

        for (int i = 1; i <= maxNums; i++) {
            int subGcd = 0;
            for (int j = i; j <= maxNums; j += i) {
                if (NumsExist[j] == false) {
                    continue;
                }

                if (subGcd == 0) {
                    subGcd = j;
                } else {
                    subGcd = __gcd(subGcd, j);
                }

                if (subGcd == i) {
                    ++retVal;
                    break;
                }
            }
        }

        return retVal;
    }
};
```

</details>

## [1822. Sign of the Product of an Array](https://leetcode.com/problems/sign-of-the-product-of-an-array/)  1209

- [Official](https://leetcode.com/problems/sign-of-the-product-of-an-array/editorial/)
- [Official](https://leetcode.cn/problems/sign-of-the-product-of-an-array/solutions/1925354/shu-zu-yuan-su-ji-de-fu-hao-by-leetcode-f4uuj/)

<details><summary>Description</summary>

```text
There is a function signFunc(x) that returns:
- 1 if x is positive.
- -1 if x is negative.
- 0 if x is equal to 0.
You are given an integer array nums. Let product be the product of all values in the array nums.

Return signFunc(product).

Example 1:
Input: nums = [-1,-2,-3,-4,3,2,1]
Output: 1
Explanation: The product of all values in the array is 144, and signFunc(144) = 1

Example 2:
Input: nums = [1,5,0,2,-3]
Output: 0
Explanation: The product of all values in the array is 0, and signFunc(0) = 0

Example 3:
Input: nums = [-1,1,-1,1,-1]
Output: -1
Explanation: The product of all values in the array is -1, and signFunc(-1) = -1

Constraints:
1 <= nums.length <= 1000
-100 <= nums[i] <= 100
```

<details><summary>Hint</summary>

```text
1. If there is a 0 in the array the answer is 0
2. To avoid overflow make all the negative numbers -1 and all positive numbers 1 and calculate the prod
```

</details>

</details>

<details><summary>C</summary>

```c
int arraySign(int* nums, int numsSize) {
    int retVal = 1;

    int i;
    for (i=0; i<numsSize; ++i) {
        if (nums[i] == 0) {
            retVal = 0;
            break;
        }
        else if (nums[i] > 0) {
            retVal *= 1;
        }
        else if (nums[i] < 0) {
            retVal *= (-1);
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
    int arraySign(vector<int>& nums) {
        int retVal = 1;

        for (long unsigned int i=0; i<nums.size(); ++i) {
            if (nums[i] == 0) {
                retVal = 0;
                break;
            }
            else if (nums[i] > 0) {
                retVal *= 1;
            }
            else if (nums[i] < 0) {
                retVal *= (-1);
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
    def arraySign(self, nums: List[int]) -> int:
        retVal = 1
        for value in nums:
            if value == 0:
                retVal = 0
                break
            elif value > 1:
                retVal *= 1
            elif value < 1:
                retVal *= (-1)

        return retVal
```

</details>

## [1823. Find the Winner of the Circular Game](https://leetcode.com/problems/find-the-winner-of-the-circular-game/)  1412

- [Official](https://leetcode.com/problems/find-the-winner-of-the-circular-game/editorial/)
- [Official](https://leetcode.cn/problems/find-the-winner-of-the-circular-game/solutions/1463524/zhao-chu-you-xi-de-huo-sheng-zhe-by-leet-w2jd/)

<details><summary>Description</summary>

```text
There are n friends that are playing a game.
The friends are sitting in a circle and are numbered from 1 to n in clockwise order.
More formally, moving clockwise from the ith friend brings you to the (i+1)th friend for 1 <= i < n,
and moving clockwise from the nth friend brings you to the 1st friend.

The rules of the game are as follows:
1. Start at the 1st friend.
2. Count the next k friends in the clockwise direction including the friend you started at.
   The counting wraps around the circle and may count some friends more than once.
3. The last friend you counted leaves the circle and loses the game.
4. If there is still more than one friend in the circle,
   go back to step 2 starting from the friend immediately clockwise of the friend who just lost and repeat.
5. Else, the last friend in the circle wins the game.

Given the number of friends, n, and an integer k, return the winner of the game.

Example 1:
Input: n = 5, k = 2
Output: 3
Explanation: Here are the steps of the game:
1) Start at friend 1.
2) Count 2 friends clockwise, which are friends 1 and 2.
3) Friend 2 leaves the circle. Next start is friend 3.
4) Count 2 friends clockwise, which are friends 3 and 4.
5) Friend 4 leaves the circle. Next start is friend 5.
6) Count 2 friends clockwise, which are friends 5 and 1.
7) Friend 1 leaves the circle. Next start is friend 3.
8) Count 2 friends clockwise, which are friends 3 and 5.
9) Friend 5 leaves the circle. Only friend 3 is left, so they are the winner.

Example 2:
Input: n = 6, k = 5
Output: 1
Explanation: The friends leave in this order: 5, 4, 6, 2, 3. The winner is friend 1.

Constraints:
1 <= k <= n <= 500

Follow up:
Could you solve this problem in linear time with constant space?
```

<details><summary>Hint</summary>

```text
1. Simulate the process.
2. Maintain in a circular list the people who are still in the circle and the current person you are standing at.
3. In each turn, count k people and remove the last person from the list.
```

</details>

</details>

<details><summary>C</summary>

```c
int findTheWinner(int n, int k) {
    int retVal = 1;

    if (n == 1) {
        return retVal;
    }
    retVal = (k + findTheWinner(n - 1, k) - 1) % n + 1;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int findTheWinner(int n, int k) {
        int retVal = 1;

        if (n == 1) {
            return retVal;
        }
        retVal = (k + findTheWinner(n - 1, k) - 1) % n + 1;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def findTheWinner(self, n: int, k: int) -> int:
        retVal = 1

        if n == 1:
            return retVal
        retVal = (k + self.findTheWinner(n - 1, k) - 1) % n + 1

        return retVal
```

</details>

## [1828. Queries on Number of Points Inside a Circle](https://leetcode.com/problems/queries-on-number-of-points-inside-a-circle/)  1380

- [Official](https://leetcode.cn/problems/queries-on-number-of-points-inside-a-circle/solutions/2072843/tong-ji-yi-ge-yuan-zhong-dian-de-shu-mu-jnylm/)

<details><summary>Description</summary>

```text
You are given an array points where points[i] = [xi, yi] is the coordinates of the ith point on a 2D plane.
Multiple points can have the same coordinates.

You are also given an array queries
where queries[j] = [xj, yj, rj] describes a circle centered at (xj, yj) with a radius of rj.

For each query queries[j], compute the number of points inside the jth circle.
Points on the border of the circle are considered inside.

Return an array answer, where answer[j] is the answer to the jth query.

Example 1:
Input: points = [[1,3],[3,3],[5,3],[2,2]], queries = [[2,3,1],[4,3,1],[1,1,2]]
Output: [3,2,2]
Explanation: The points and circles are shown above.
queries[0] is the green circle, queries[1] is the red circle, and queries[2] is the blue circle.

Example 2:
Input: points = [[1,1],[2,2],[3,3],[4,4],[5,5]], queries = [[1,2,2],[2,2,2],[4,3,2],[4,3,3]]
Output: [2,3,2,4]
Explanation: The points and circles are shown above.
queries[0] is green, queries[1] is red, queries[2] is blue, and queries[3] is purple.

Constraints:
1 <= points.length <= 500
points[i].length == 2
0 <= x​​​​​​i, y​​​​​​i <= 500
1 <= queries.length <= 500
queries[j].length == 3
0 <= xj, yj <= 500
1 <= rj <= 500
All coordinates are integers.
```

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countPoints(int** points, int pointsSize, int* pointsColSize, int** queries, int queriesSize, int* queriesColSize,
                 int* returnSize) {
    int* retVal = NULL;

    //
    (*returnSize) = queriesSize;
    retVal = (int*)malloc(((*returnSize)) * sizeof(int));
    if (retVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return retVal;
    }
    memset(retVal, 0, (((*returnSize)) * sizeof(int)));

    //
    int originX, originY, radius;
    int x, y;
    int count;
    int i, j;
    for (i = 0; i < queriesSize; ++i) {
        count = 0;

        originX = queries[i][0];
        originY = queries[i][1];
        radius = queries[i][2];
        for (j = 0; j < pointsSize; ++j) {
            x = points[j][0];
            y = points[j][1];

            if (pow(abs(originX - x), 2) + pow(abs(originY - y), 2) <= pow(radius, 2)) {
                ++count;
            }
        }

        retVal[i] = count;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> countPoints(vector<vector<int>>& points, vector<vector<int>>& queries) {
        vector<int> retVal;

        for (auto querie : queries) {
            int count = 0;

            int originX = querie[0];
            int originY = querie[1];
            int radius = querie[2];
            for (auto point : points) {
                int x = point[0];
                int y = point[1];

                if (pow(abs(originX - x), 2) + pow(abs(originY - y), 2) <= pow(radius, 2)) {
                    ++count;
                }
            }

            retVal.emplace_back(count);
        }

        return retVal;
    }
};
```

</details>

## [1903. Largest Odd Number in String](https://leetcode.com/problems/largest-odd-number-in-string/description/)  1248

- [Official](https://leetcode.com/problems/largest-odd-number-in-string/editorial/)
- [Official](https://leetcode.cn/problems/largest-odd-number-in-string/solutions/836344/zi-fu-chuan-zhong-de-zui-da-qi-shu-by-le-xggo/)

<details><summary>Description</summary>

```text
You are given a string num, representing a large integer.
Return the largest-valued odd integer (as a string) that is a non-empty substring of num,
or an empty string "" if no odd integer exists.

A substring is a contiguous sequence of characters within a string.

Example 1:
Input: num = "52"
Output: "5"
Explanation: The only non-empty substrings are "5", "2", and "52". "5" is the only odd number.

Example 2:
Input: num = "4206"
Output: ""
Explanation: There are no odd numbers in "4206".

Example 3:
Input: num = "35427"
Output: "35427"
Explanation: "35427" is already an odd number.

Constraints:
1 <= num.length <= 10^5
num only consists of digits and does not contain any leading zeros.
```

<details><summary>Hint</summary>

```text
1. In what order should you iterate through the digits?
2. If an odd number exists, where must the number start from?
```

</details>

</details>

<details><summary>C</summary>

```c
char* largestOddNumber(char* num) {
    char* pRetVal = "";

    int numSize = strlen(num);
    int i;
    for (i = numSize - 1; i >= 0; --i) {
        if ((num[i] - '0') % 2 == 0) {
            continue;
        }
        pRetVal = num;
        num[i + 1] = '\0';
        break;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string largestOddNumber(string num) {
        string retVal = "";

        int numSize = num.size();
        for (int i = numSize - 1; i >= 0; --i) {
            if ((num[i] - '0') % 2 == 0) {
                continue;
            }
            retVal = num.substr(0, i + 1);
            break;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def largestOddNumber(self, num: str) -> str:
        retVal = ""

        numSize = len(num)
        for i in range(numSize-1, -1, -1):
            if int(num[i]) % 2 == 0:
                continue
            retVal = num[:i+1]
            break

        return retVal
```

</details>

## [1922. Count Good Numbers](https://leetcode.com/problems/count-good-numbers/)  1674

- [Official](https://leetcode.com/problems/count-good-numbers/editorial/)
- [Official](https://leetcode.cn/problems/count-good-numbers/solutions/857968/tong-ji-hao-shu-zi-de-shu-mu-by-leetcode-53jj/)

<details><summary>Description</summary>

```text
A digit string is good if the digits (0-indexed) at even indices are even
and the digits at odd indices are prime (2, 3, 5, or 7).
- For example, "2582" is good because the digits (2 and 8) at even positions are even
  and the digits (5 and 2) at odd positions are prime.
  However, "3245" is not good because 3 is at an even index but is not even.

Given an integer n, return the total number of good digit strings of length n.
Since the answer may be large, return it modulo 109 + 7.

A digit string is a string consisting of digits 0 through 9 that may contain leading zeros.

Example 1:
Input: n = 1
Output: 5
Explanation: The good numbers of length 1 are "0", "2", "4", "6", "8".

Example 2:
Input: n = 4
Output: 400

Example 3:
Input: n = 50
Output: 564908303

Constraints:
1 <= n <= 10^15
```

<details><summary>Hint</summary>

```text
1. Is there a formula we can use to find the count of all the good numbers?
2. Exponentiation can be done very fast if we looked at the binary bits of n.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MODULO (int)(1e9 + 7)
long long quickmul(int x, long long y) {
    long long retVal = 1;

    long long mul = x;
    while (y > 0) {
        if (y % 2 == 1) {
            retVal = (retVal * mul) % MODULO;
        }
        mul = (mul * mul) % MODULO;
        y /= 2;
    }

    return retVal;
}
int countGoodNumbers(long long n) {
    int retVal = 0;

    retVal = (int)(quickmul(5, (n + 1) / 2) * quickmul(4, n / 2) % MODULO);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define MODULO (int)(1e9 + 7)
   private:
    long long quickmul(int x, long long y) {
        long long retVal = 1;

        long long mul = x;
        while (y > 0) {
            if (y % 2 == 1) {
                retVal = (retVal * mul) % MODULO;
            }
            mul = (mul * mul) % MODULO;
            y /= 2;
        }

        return retVal;
    }

   public:
    int countGoodNumbers(long long n) {
        int retVal = 0;

        retVal = (int)(quickmul(5, (n + 1) / 2) * quickmul(4, n / 2) % MODULO);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def __init__(self):
        self.MODULO = 10 ** 9 + 7

    def quickmul(self, x: int, y: int) -> int:
        retVal = 1

        mul = x
        while y > 0:
            if y % 2 == 1:
                retVal = retVal * mul % self.MODULO
            mul = mul * mul % self.MODULO
            y //= 2

        return retVal

    def countGoodNumbers(self, n: int) -> int:
        retVal = 0

        retVal = self.quickmul(5, (n + 1) // 2) * self.quickmul(4, n // 2) % self.MODULO

        return retVal
```

</details>

## [1979. Find Greatest Common Divisor of Array](https://leetcode.com/problems/find-greatest-common-divisor-of-array/)  1184

<details><summary>Description</summary>

```text
Given an integer array nums, return the greatest common divisor of the smallest number and largest number in nums.

The greatest common divisor of two numbers is the largest positive integer that evenly divides both numbers.

Example 1:
Input: nums = [2,5,6,9,10]
Output: 2
Explanation:
The smallest number in nums is 2.
The largest number in nums is 10.
The greatest common divisor of 2 and 10 is 2.

Example 2:
Input: nums = [7,5,6,8,3]
Output: 1
Explanation:
The smallest number in nums is 3.
The largest number in nums is 8.
The greatest common divisor of 3 and 8 is 1.

Example 3:
Input: nums = [3,3]
Output: 3
Explanation:
The smallest number in nums is 3.
The largest number in nums is 3.
The greatest common divisor of 3 and 3 is 3.

Constraints:
2 <= nums.length <= 1000
1 <= nums[i] <= 1000
```

</details>

<details><summary>C</summary>

```c
int gcd(int a, int b) {
    int remainder;
    while (b != 0) {
        remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}
int findGCD(int* nums, int numsSize) {
    int retVal = 0;

    int minNums = INT_MAX;
    int maxNums = INT_MIN;
    int i;
    for (i = 0; i < numsSize; ++i) {
        minNums = fmin(minNums, nums[i]);
        maxNums = fmax(maxNums, nums[i]);
    }
    retVal = gcd(minNums, maxNums);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
public:
    int findGCD(vector<int>& nums) {
        int retVal = 0;

        int minNums = *min_element(nums.begin(), nums.end());
        int maxNums = *max_element(nums.begin(), nums.end());
        retVal = __gcd(minNums, maxNums);

        return retVal;
    }
};
```

</details>

## [2028. Find Missing Observations](https://leetcode.com/problems/find-missing-observations/)  1444

- [Official](https://leetcode.com/problems/find-missing-observations/editorial/)
- [Official](https://leetcode.cn/problems/find-missing-observations/solutions/1368819/zhao-chu-que-shi-de-guan-ce-shu-ju-by-le-0z7j/)

<details><summary>Description</summary>

```text
You have observations of n + m 6-sided dice rolls with each face numbered from 1 to 6.
n of the observations went missing, and you only have the observations of m rolls.
Fortunately, you have also calculated the average value of the n + m rolls.

You are given an integer array rolls of length m where rolls[i] is the value of the ith observation.
You are also given the two integers mean and n.

Return an array of length n containing the missing observations
such that the average value of the n + m rolls is exactly mean.
If there are multiple valid answers, return any of them. If no such array exists, return an empty array.

The average value of a set of k numbers is the sum of the numbers divided by k.

Note that mean is an integer, so the sum of the n + m rolls should be divisible by n + m.

Example 1:
Input: rolls = [3,2,4,3], mean = 4, n = 2
Output: [6,6]
Explanation: The mean of all n + m rolls is (3 + 2 + 4 + 3 + 6 + 6) / 6 = 4.

Example 2:
Input: rolls = [1,5,6], mean = 3, n = 4
Output: [2,3,2,2]
Explanation: The mean of all n + m rolls is (1 + 5 + 6 + 2 + 3 + 2 + 2) / 7 = 3.

Example 3:
Input: rolls = [1,2,3,4], mean = 6, n = 4
Output: []
Explanation: It is impossible for the mean to be 6 no matter what the 4 missing rolls are.

Constraints:
m == rolls.length
1 <= n, m <= 10^5
1 <= rolls[i], mean <= 6
```

<details><summary>Hint</summary>

```text
1. What should the sum of the n rolls be?
2. Could you generate an array of size n such that each element is between 1 and 6?
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *missingRolls(int *rolls, int rollsSize, int mean, int n, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;

    int total = mean * (rollsSize + n);
    int i;
    for (i = 0; i < rollsSize; ++i) {
        total -= rolls[i];
    }
    if ((total > (6 * n)) || (total < n)) {
        return pRetVal;
    }

    int average = total / n;
    int index = total % n;

    pRetVal = (int *)malloc(n * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (n * sizeof(int)));
    for (i = 0; i < n; ++i) {
        pRetVal[i] = average;
        if (i < index) {
            pRetVal[i] += 1;
        }
    }
    (*returnSize) = n;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> missingRolls(vector<int>& rolls, int mean, int n) {
        vector<int> retVal;

        int rollsSize = rolls.size();
        int total = mean * (rollsSize + n);
        for (int roll : rolls) {
            total -= roll;
        }
        if ((total > (6 * n)) || (total < n)) {
            return retVal;
        }

        int average = total / n;
        int index = total % n;

        retVal.resize(n, average);
        for (int i = 0; i < index; ++i) {
            retVal[i] += 1;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def missingRolls(self, rolls: List[int], mean: int, n: int) -> List[int]:
        retVal = []

        rollsSize = len(rolls)
        total = mean * (rollsSize + n)
        for roll in rolls:
            total -= roll
        if (total > (6 * n)) or (total < n):
            return retVal

        average = total // n
        index = total % n

        retVal = [average] * n
        for i in range(index):
            retVal[i] += 1

        return retVal
```

</details>

## [2125. Number of Laser Beams in a Bank](https://leetcode.com/problems/number-of-laser-beams-in-a-bank/)  1280

- [Official](https://leetcode.com/problems/number-of-laser-beams-in-a-bank/editorial)

<details><summary>Description</summary>

```text
Anti-theft security devices are activated inside a bank.
You are given a 0-indexed binary string array bank representing the floor plan of the bank, which is an m x n 2D matrix.
bank[i] represents the ith row, consisting of '0's and '1's.
'0' means the cell is empty, while'1' means the cell has a security device.

There is one laser beam between any two security devices if both conditions are met:
- The two devices are located on two different rows: r1 and r2, where r1 < r2.
- For each row i where r1 < i < r2, there are no security devices in the ith row.

Laser beams are independent, i.e., one beam does not interfere nor join with another.

Return the total number of laser beams in the bank.

Example 1:
Input: bank = ["011001","000000","010100","001000"]
Output: 8
Explanation: Between each of the following device pairs, there is one beam. In total, there are 8 beams:
 * bank[0][1] -- bank[2][1]
 * bank[0][1] -- bank[2][3]
 * bank[0][2] -- bank[2][1]
 * bank[0][2] -- bank[2][3]
 * bank[0][5] -- bank[2][1]
 * bank[0][5] -- bank[2][3]
 * bank[2][1] -- bank[3][2]
 * bank[2][3] -- bank[3][2]
Note that there is no beam between any device on the 0th row with any on the 3rd row.
This is because the 2nd row contains security devices, which breaks the second condition.

Example 2:
Input: bank = ["000","111","000"]
Output: 0
Explanation: There does not exist two devices located on two different rows.

Constraints:
m == bank.length
n == bank[i].length
1 <= m, n <= 500
bank[i][j] is either '0' or '1'.
```

<details><summary>Hint</summary>

```text
1. What is the commonality between security devices on the same row?
2. Each device on the same row has the same number of beams pointing towards the devices on the next row with devices.
3. If you were given an integer array where each element is the number of security devices on each row, can you solve it?
4. Convert the input to such an array, skip any row with no security device,
   then find the sum of the product between adjacent elements.
```

</details>

</details>

<details><summary>C</summary>

```c
int numberOfBeams(char** bank, int bankSize) {
    int retVal = 0;

    int previous = 0;
    int count, len;
    int i, j;
    for (i = 0; i < bankSize; ++i) {
        count = 0;
        len = strlen(bank[i]);
        for (j = 0; j < len; ++j) {
            if (bank[i][j] == '1') {
                count++;
            }
        }

        if (count != 0) {
            retVal += (previous * count);
            previous = count;
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
    int numberOfBeams(vector<string>& bank) {
        int retVal = 0;

        int previous = 0;
        for (string row : bank) {
            int count = 0;
            for (char c : row) {
                if (c == '1') {
                    count++;
                }
            }

            if (count != 0) {
                retVal += (previous * count);
                previous = count;
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
    def numberOfBeams(self, bank: List[str]) -> int:
        retVal = 0

        previous = 0
        for row in bank:
            count1 = Counter(row)['1']
            if count1 != 0:
                retVal += (previous * count1)
                previous = count1

        return retVal
```

</details>

## [2147. Number of Ways to Divide a Long Corridor](https://leetcode.com/problems/number-of-ways-to-divide-a-long-corridor/)  1914

- [Official](https://leetcode.com/problems/number-of-ways-to-divide-a-long-corridor/editorial/)
- [Official](https://leetcode.cn/problems/number-of-ways-to-divide-a-long-corridor/solutions/1231280/fen-ge-chang-lang-de-fang-an-shu-by-leet-p9wr/)

<details><summary>Description</summary>

```text
Along a long library corridor, there is a line of seats and decorative plants.
You are given a 0-indexed string corridor of length n consisting of letters 'S' and 'P'
where each 'S' represents a seat and each 'P' represents a plant.

One room divider has already been installed to the left of index 0, and another to the right of index n - 1.
Additional room dividers can be installed.
For each position between indices i - 1 and i (1 <= i <= n - 1), at most one divider can be installed.

Divide the corridor into non-overlapping sections, where each section has exactly two seats with any number of plants.
There may be multiple ways to perform the division.
Two ways are different if there is a position with a room divider installed in the first way but not in the second way.

Return the number of ways to divide the corridor. Since the answer may be very large, return it modulo 109 + 7.
If there is no way, return 0.

Example 1:
Input: corridor = "SSPPSPS"
Output: 3
Explanation: There are 3 different ways to divide the corridor.
The black bars in the above image indicate the two room dividers already installed.
Note that in each of the ways, each section has exactly two seats.

Example 2:
Input: corridor = "PPSPSP"
Output: 1
Explanation: There is only 1 way to divide the corridor, by not installing any additional dividers.
Installing any would create some section that does not have exactly two seats.

Example 3:
Input: corridor = "S"
Output: 0
Explanation: There is no way to divide the corridor
because there will always be a section that does not have exactly two seats.

Constraints:
n == corridor.length
1 <= n <= 10^5
corridor[i] is either 'S' or 'P'.
```

<details><summary>Hint</summary>

```text
1. Divide the corridor into segments.
   Each segment has two seats, starts precisely with one seat, and ends precisely with the other seat.
2. How many dividers can you install between two adjacent segments?
   You must install precisely one. Otherwise, you would have created a section with not exactly two seats.
3. If there are k plants between two adjacent segments,
   there are k + 1 positions (ways) you could install the divider you must install.
4. The problem now becomes: Find the product of all possible positions between every two adjacent segments.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MODULO (int)(1e9 + 7)
int numberOfWays(char* corridor) {
    int retVal = 0;

    int corridorSize = strlen(corridor);

    long answer = 1;
    int count = 0;
    int previous = -1;
    for (int i = 0; i < corridorSize; ++i) {
        if (corridor[i] == 'S') {
            count++;

            if ((count >= 3) && (count % 2 == 1)) {
                answer = (answer * (i - previous)) % MODULO;
            }

            previous = i;
        }
    }

    if ((count < 2) || (count % 2 == 1)) {
        answer = 0;
    }
    retVal = answer;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define MODULO (int)(1e9 + 7)
   public:
    int numberOfWays(string corridor) {
        int retVal = 0;

        int corridorSize = corridor.size();

        long answer = 1;
        int count = 0;
        int previous = -1;
        for (int i = 0; i < corridorSize; ++i) {
            if (corridor[i] == 'S') {
                count++;

                if ((count >= 3) && (count % 2 == 1)) {
                    answer = (answer * (i - previous)) % MODULO;
                }

                previous = i;
            }
        }

        if ((count < 2) || (count % 2 == 1)) {
            answer = 0;
        }
        retVal = answer;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def __init__(self):
        self.MODULO = 10 ** 9 + 7

    def numberOfWays(self, corridor: str) -> int:
        retVal = 1

        count = 0
        previous = -1
        for index, value in enumerate(corridor):
            if value == "S":
                count += 1

                if (count >= 3) and (count % 2 == 1):
                    retVal = (retVal * (index - previous)) % self.MODULO

                previous = index

        if (count < 2) or (count % 2 == 1):
            retVal = 0

        return retVal
```

</details>

## [2180. Count Integers With Even Digit Sum](https://leetcode.com/problems/count-integers-with-even-digit-sum/)  1257

- [Official](https://leetcode.cn/problems/count-integers-with-even-digit-sum/solutions/2045888/tong-ji-ge-wei-shu-zi-zhi-he-wei-ou-shu-rvqol/)

<details><summary>Description</summary>

```text
Given a positive integer num, return the number of positive integers less than or equal to num whose digit sums are even.

The digit sum of a positive integer is the sum of all its digits.

Example 1:
Input: num = 4
Output: 2
Explanation:
The only integers less than or equal to 4 whose digit sums are even are 2 and 4.

Example 2:
Input: num = 30
Output: 14
Explanation:
The 14 integers less than or equal to 30 whose digit sums are even are
2, 4, 6, 8, 11, 13, 15, 17, 19, 20, 22, 24, 26, and 28.

Constraints:
1 <= num <= 1000
```

</details>

<details><summary>C</summary>

```c
#define MATH (1)
#define BRUTE_FORCE (1)
int countEven(int num) {
    int retVal = 0;

#if (MATH)
    printf("MATH\n");

    /* Math
     *  nums = xyz, sum of digits = x + y + z.
     *  if x + y + z is even, the even digit sums is nums / 2.
     *  if x + y + z is odd, the even digit sums is (nums - 1) / 2.
     */
    int sum = 0;
    int tmp = num;
    while (tmp > 0) {
        sum += (tmp % 10);
        tmp /= 10;
    }

    if (sum % 2 == 0) {
        retVal = num / 2;
    } else {
        retVal = (num - 1) / 2;
    }
#elif (BRUTE_FORCE)
    printf("BRUTE_FORCE\n");

    int tmp;
    int sum;
    int i;
    for (i = 2; i <= num; ++i) {
        sum = 0;
        tmp = i;
        while (tmp > 0) {
            sum += (tmp % 10);
            tmp /= 10;
        }
        if (sum % 2 == 0) {
            ++retVal;
        }
    }
#endif

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define MATH (1)
#define BRUTE_FORCE (1)
   public:
    int countEven(int num) {
        int retVal = 0;

#if (MATH)
        cout << "MATH\n";

        /* Math
         *  nums = xyz, sum of digits = x + y + z.
         *  if x + y + z is even, the even digit sums is nums / 2.
         *  if x + y + z is odd, the even digit sums is (nums - 1) / 2.
         */
        int sum = 0;
        int tmp = num;
        while (tmp > 0) {
            sum += (tmp % 10);
            tmp /= 10;
        }

        if (sum % 2 == 0) {
            retVal = num / 2;
        } else {
            retVal = (num - 1) / 2;
        }
#elif (BRUTE_FORCE)
        cout << "BRUTE_FORCE\n";

        for (int i = 2; i <= num; ++i) {
            int sum = 0;
            int tmp = i;
            while (tmp > 0) {
                sum += (tmp % 10);
                tmp /= 10;
            }
            if (sum % 2 == 0) {
                ++retVal;
            }
        }
#endif

        return retVal;
    }
};
```

</details>

## [2235. Add Two Integers](https://leetcode.com/problems/add-two-integers/)

<details><summary>Description</summary>

```text
Given two integers num1 and num2, return the sum of the two integers.

Example 1:
Input: num1 = 12, num2 = 5
Output: 17
Explanation: num1 is 12, num2 is 5, and their sum is 12 + 5 = 17, so 17 is returned.

Example 2:
Input: num1 = -10, num2 = 4
Output: -6
Explanation: num1 + num2 = -6, so -6 is returned.

Constraints:
-100 <= num1, num2 <= 100
```

</details>

<details><summary>C</summary>

```c
int sum(int num1, int num2){
    int retVal = num1 + num2;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int sum(int num1, int num2) {
        int retVal = num1 + num2;

        return retVal;
    }
};
```

</details>

<details><summary>Rust</summary>

```rust
impl Solution {
    pub fn sum(num1: i32, num2: i32) -> i32 {
        let retVal = num1 + num2;

        return retVal;
    }
}
```

</details>

## [2338. Count the Number of Ideal Arrays](https://leetcode.com/problems/count-the-number-of-ideal-arrays/)  2615

- [Official](https://leetcode.com/problems/count-the-number-of-ideal-arrays/editorial/)
- [Official](https://leetcode.cn/problems/count-the-number-of-ideal-arrays/solutions/3650511/tong-ji-li-xiang-shu-zu-de-shu-mu-by-lee-usvr/)

<details><summary>Description</summary>

```text
You are given two integers n and maxValue, which are used to describe an ideal array.

A 0-indexed integer array arr of length n is considered ideal if the following conditions hold:
- Every arr[i] is a value from 1 to maxValue, for 0 <= i < n.
- Every arr[i] is divisible by arr[i - 1], for 0 < i < n.

Return the number of distinct ideal arrays of length n. Since the answer may be very large, return it modulo 10^9 + 7.

Example 1:
Input: n = 2, maxValue = 5
Output: 10
Explanation: The following are the possible ideal arrays:
- Arrays starting with the value 1 (5 arrays): [1,1], [1,2], [1,3], [1,4], [1,5]
- Arrays starting with the value 2 (2 arrays): [2,2], [2,4]
- Arrays starting with the value 3 (1 array): [3,3]
- Arrays starting with the value 4 (1 array): [4,4]
- Arrays starting with the value 5 (1 array): [5,5]
There are a total of 5 + 2 + 1 + 1 + 1 = 10 distinct ideal arrays

Example 2:
Input: n = 5, maxValue = 3
Output: 11
Explanation: The following are the possible ideal arrays:
- Arrays starting with the value 1 (9 arrays):
   - With no other distinct values (1 array): [1,1,1,1,1]
   - With 2nd distinct value 2 (4 arrays): [1,1,1,1,2], [1,1,1,2,2], [1,1,2,2,2], [1,2,2,2,2]
   - With 2nd distinct value 3 (4 arrays): [1,1,1,1,3], [1,1,1,3,3], [1,1,3,3,3], [1,3,3,3,3]
- Arrays starting with the value 2 (1 array): [2,2,2,2,2]
- Arrays starting with the value 3 (1 array): [3,3,3,3,3]
There are a total of 9 + 1 + 1 = 11 distinct ideal arrays.

Constraints:
2 <= n <= 10^4
1 <= maxValue <= 10^4
```

<details><summary>Hint</summary>

```text
1. Notice that an ideal array is non-decreasing.
2. Consider an alternative problem: where an ideal array must also be strictly increasing. Can you use DP to solve it?
3. Will combinatorics help to get an answer from the alternative problem to the actual problem?
```

</details>

</details>

<details><summary>C</summary>

```c
#define MODULO (int)(1e9 + 7)
#define MAX_N (10010)
#define MAX_P (15)  // There are up to 15 prime factors
int c[MAX_N + MAX_P][MAX_P + 1];
int sieve[MAX_N];                    // Minimum prime factor
int ps[MAX_N][MAX_P], psLen[MAX_N];  // List of prime factor counts
void init() {
    if (c[0][0]) {
        return;
    }

    for (int i = 2; i < MAX_N; i++) {
        if (sieve[i] != 0) {
            continue;
        }
        for (int j = i; j < MAX_N; j += i) {
            if (sieve[j] == 0) {
                sieve[j] = i;
            }
        }
    }

    for (int i = 2; i < MAX_N; i++) {
        int x = i;
        psLen[i] = 0;
        while (x > 1) {
            int p = sieve[x];
            int cnt = 0;
            while (x % p == 0) {
                x /= p;
                cnt++;
            }
            ps[i][psLen[i]++] = cnt;
        }
    }

    c[0][0] = 1;
    for (int i = 1; i < MAX_N + MAX_P; i++) {
        c[i][0] = 1;
        for (int j = 1; j <= MAX_P && j <= i; j++) {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MODULO;
        }
    }
}
int idealArrays(int n, int maxValue) {
    int retVal = 0;

    init();
    long long ans = 0;
    for (int x = 1; x <= maxValue; x++) {
        long long mul = 1;
        for (int i = 0; i < psLen[x]; i++) {
            mul = mul * c[n + ps[x][i] - 1][ps[x][i]] % MODULO;
        }
        ans = (ans + mul) % MODULO;
    }
    retVal = ans;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
#define MODULO (int)(1e9 + 7)
#define MAX_N (int)(1e4 + 10)
#define MAX_P (15)      // There are up to 15 prime factors
int sieve[MAX_N];       // Minimum prime factor
vector<int> ps[MAX_N];  // List of prime factor counts
int c[MAX_N + MAX_P][MAX_P + 1];
class Solution {
   public:
    Solution() {
        if (c[0][0]) {
            return;
        }

        for (int i = 2; i < MAX_N; i++) {
            if (sieve[i] != 0) {
                continue;
            }
            for (int j = i; j < MAX_N; j += i) {
                sieve[j] = i;
            }
        }

        for (int i = 2; i < MAX_N; i++) {
            int x = i;
            while (x > 1) {
                int p = sieve[x];
                int cnt = 0;
                while (x % p == 0) {
                    x /= p;
                    cnt++;
                }
                ps[i].push_back(cnt);
            }
        }

        c[0][0] = 1;
        for (int i = 1; i < MAX_N + MAX_P; i++) {
            c[i][0] = 1;
            for (int j = 1; j <= min(i, MAX_P); j++) {
                c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MODULO;
            }
        }
    }
    int idealArrays(int n, int maxValue) {
        int retVal = 0;

        long long ans = 0;
        for (int x = 1; x <= maxValue; x++) {
            long long mul = 1;
            for (int p : ps[x]) {
                mul = mul * c[n + p - 1][p] % MODULO;
            }
            ans = (ans + mul) % MODULO;
        }
        retVal = ans;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def __init__(self) -> None:
        self.MODULO = 10 ** 9 + 7
        self.MAX_N = 10**4 + 10
        self.MAX_P = 15  # There are up to 15 prime factors

        self.sieve = [0] * self.MAX_N  # // Minimum prime factor
        for i in range(2, self.MAX_N):
            if self.sieve[i] != 0:
                continue
            for j in range(i, self.MAX_N, i):
                self.sieve[j] = i

        self.ps = [[] for _ in range(self.MAX_N)]
        for i in range(2, self.MAX_N):
            x = i
            while x > 1:
                p = self.sieve[x]
                cnt = 0
                while x % p == 0:
                    x //= p
                    cnt += 1
                self.ps[i].append(cnt)

        self.c = [[0] * (self.MAX_P + 1) for _ in range(self.MAX_N + self.MAX_P)]
        self.c[0][0] = 1
        for i in range(1, self.MAX_N + self.MAX_P):
            self.c[i][0] = 1
            for j in range(1, min(i, self.MAX_P) + 1):
                self.c[i][j] = (self.c[i - 1][j] + self.c[i - 1][j - 1]) % self.MODULO

    def idealArrays(self, n: int, maxValue: int) -> int:
        retVal = 0

        for x in range(1, maxValue + 1):
            mul = 1
            for p in self.ps[x]:
                mul = mul * self.c[n + p - 1][p] % self.MODULO
            retVal = (retVal + mul) % self.MODULO

        return retVal
```

</details>

## [2413. Smallest Even Multiple](https://leetcode.com/problems/smallest-even-multiple/)  1144

- [Official](https://leetcode.cn/problems/smallest-even-multiple/solutions/2236371/zui-xiao-ou-bei-shu-by-leetcode-solution-vy2o/)

<details><summary>Description</summary>

```text
Given a positive integer n, return the smallest positive integer that is a multiple of both 2 and n.

Example 1:
Input: n = 5
Output: 10
Explanation: The smallest multiple of both 5 and 2 is 10.

Example 2:
Input: n = 6
Output: 6
Explanation: The smallest multiple of both 6 and 2 is 6. Note that a number is a multiple of itself.

Constraints:
1 <= n <= 150
```

<details><summary>Hint</summary>

```text
1. A guaranteed way to find a multiple of 2 and n is to multiply them together.
   When is this the answer, and when is there a smaller answer?
2. There is a smaller answer when n is even.
```

</details>

</details>

<details><summary>C</summary>

```c
int smallestEvenMultiple(int n) {
    int retVal = 0;

#if (1)
    retVal = n << (n & 1);
#else
    retVal = n;
    if (n % 2 == 1) {
        retVal = n * 2;
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
    int smallestEvenMultiple(int n) {
        int retVal = 0;

#if (1)
        retVal = n << (n & 1);
#else
        retVal = n;
        if (n % 2 == 1) {
            retVal = n * 2;
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
    def smallestEvenMultiple(self, n: int) -> int:
        retVal = 0

        retVal = n << (n & 1)
        # retVal = n
        # if n % 2 == 1:
        #     retVal = n * 2

        return retVal
```

</details>

## [2485. Find the Pivot Integer](https://leetcode.com/problems/find-the-pivot-integer/)  1207

- [Official](https://leetcode.com/problems/find-the-pivot-integer/editorial/)
- [Official](https://leetcode.cn/problems/find-the-pivot-integer/solutions/2306030/zhao-chu-zhong-shu-zheng-shu-by-leetcode-t7gn/)

<details><summary>Description</summary>

```text
Given a positive integer n, find the pivot integer x such that:
- The sum of all elements between 1 and x inclusively equals the sum of all elements between x and n inclusively.
Return the pivot integer x. If no such integer exists, return -1.
It is guaranteed that there will be at most one pivot index for the given input.

Example 1:
Input: n = 8
Output: 6
Explanation: 6 is the pivot integer since: 1 + 2 + 3 + 4 + 5 + 6 = 6 + 7 + 8 = 21.

Example 2:
Input: n = 1
Output: 1
Explanation: 1 is the pivot integer since: 1 = 1.

Example 3:
Input: n = 4
Output: -1
Explanation: It can be proved that no such integer exist.

Constraints:
1 <= n <= 1000
```

<details><summary>Hint</summary>

```text
1. Can you use brute force to check every number from 1 to n if any of them is the pivot integer?
2. If you know the sum of [1: pivot], how can you efficiently calculate the sum of the other parts?
```

</details>

</details>

<details><summary>C</summary>

```c
int pivotInteger(int n) {
    int retVal = -1;

    /* 1 + 2 + ... + x = x + ... + n
     * => x * (x+1) / 2 = (n-x+1) * (n+x) / 2
     * => 2 * x^2 = n^2 + n
     * => x = ((n^2 + n) / 2)^(1/2)
     * => x = ((n * (n+1) / 2))^(1/2)
     */
    int sum = n * (n + 1) / 2;
    int x = sqrt(sum);
    if (x * x == sum) {
        retVal = x;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int pivotInteger(int n) {
        int retVal = -1;

        /* 1 + 2 + ... + x = x + ... + n
         * => x * (x+1) / 2 = (n-x+1) * (n+x) / 2
         * => 2 * x^2 = n^2 + n
         * => x = ((n^2 + n) / 2)^(1/2)
         * => x = ((n * (n+1) / 2))^(1/2)
         */
        int sum = n * (n + 1) / 2;
        int x = sqrt(sum);
        if (x * x == sum) {
            retVal = x;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def pivotInteger(self, n: int) -> int:
        retVal = -1

        # 1 + 2 + ... + x = x + ... + n
        # => x * (x+1) / 2 = (n-x+1) * (n+x) / 2
        # => 2 * x^2 = n^2 + n
        # => x = ((n^2 + n) / 2)^(1/2)
        # => x = ((n * (n+1) / 2))^(1/2)
        sum = n * (n + 1) // 2
        x = int(sqrt(sum))
        if x * x == sum:
            retVal = x

        return retVal
```

</details>

## [2523. Closest Prime Numbers in Range](https://leetcode.com/problems/closest-prime-numbers-in-range/)  1649

- [Official](https://leetcode.com/problems/closest-prime-numbers-in-range/editorial/)

<details><summary>Description</summary>

```text
Given two positive integers left and right, find the two integers num1 and num2 such that:
- left <= num1 < num2 <= right .
- Both num1 and num2 are prime numbers.
- num2 - num1 is the minimum amongst all other pairs satisfying the above conditions.

Return the positive integer array ans = [num1, num2]. If there are multiple pairs satisfying these conditions,
return the one with the smallest num1 value. If no such numbers exist, return [-1, -1].

Example 1:
Input: left = 10, right = 19
Output: [11,13]
Explanation: The prime numbers between 10 and 19 are 11, 13, 17, and 19.
The closest gap between any pair is 2, which can be achieved by [11,13] or [17,19].
Since 11 is smaller than 17, we return the first pair.

Example 2:
Input: left = 4, right = 6
Output: [-1,-1]
Explanation: There exists only one prime number in the given range, so the conditions cannot be satisfied.

Constraints:
1 <= left <= right <= 10^6
```

<details><summary>Hint</summary>

```text
1. Use Sieve of Eratosthenes to mark numbers that are primes.
2. Iterate from right to left and find pair with the minimum distance between marked numbers.
```

</details>

</details>

<details><summary>C</summary>

```c
#define NOT_PRIME (1)
void sieve(int upperLimit, int* sieveArray) {
    // 0 and 1 are not prime
    sieveArray[0] = NOT_PRIME;
    sieveArray[1] = NOT_PRIME;

    for (int number = 2; number * number <= upperLimit; number++) {
        if (sieveArray[number] == NOT_PRIME) {
            continue;
        }

        // Mark all multiples of 'number' as non-prime
        for (int multiple = number * number; multiple <= upperLimit; multiple += number) {
            sieveArray[multiple] = NOT_PRIME;
        }
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* closestPrimes(int left, int right, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int*)calloc(2, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }
    pRetVal[0] = -1;
    pRetVal[1] = -1;
    (*returnSize) = 2;

    // Step 1: Get all prime numbers up to 'right' using sieve
    int upperLimit = right;
    int* sieveArray = (int*)calloc((upperLimit + 1), sizeof(int));
    if (sieveArray == NULL) {
        perror("calloc");
        return pRetVal;
    }
    sieve(upperLimit, sieveArray);

    int primeNumbersSize = 0;
    int primeNumbers[right - left + 1];  // Store all primes in the range [left, right]
    memset(primeNumbers, 0, sizeof(primeNumbers));
    for (int num = left; num <= right; num++) {
        // If number is prime add to the primeNumbers list
        if (sieveArray[num] != NOT_PRIME) {
            primeNumbers[primeNumbersSize++] = num;
        }
    }

    // Step 2: Find the closest prime pair
    if (primeNumbersSize < 2) {
        free(sieveArray);
        sieveArray = NULL;
        return pRetVal;
    }

    int minDifference = INT_MAX;
    for (int index = 1; index < primeNumbersSize; index++) {
        int difference = primeNumbers[index] - primeNumbers[index - 1];
        if (difference < minDifference) {
            minDifference = difference;
            pRetVal[0] = primeNumbers[index - 1];
            pRetVal[1] = primeNumbers[index];
        }
    }

    //
    free(sieveArray);
    sieveArray = NULL;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    vector<int> sieve(int upperLimit) {
        vector<int> retVal(upperLimit + 1, 1);  // Initiate an int array to mark prime numbers

        // 0 and 1 are not prime
        retVal[0] = 0;
        retVal[1] = 0;
        for (int number = 2; number * number <= upperLimit; number++) {
            if (retVal[number] == 0) {
                continue;
            }

            // Mark all multiples of 'number' as non-prime
            for (int multiple = number * number; multiple <= upperLimit; multiple += number) {
                retVal[multiple] = 0;
            }
        }

        return retVal;
    }

   public:
    vector<int> closestPrimes(int left, int right) {
        vector<int> retVal(2, -1);

        // Step 1: Get all prime numbers up to 'right' using sieve
        int upperLimit = right;
        vector<int> sieveArray = sieve(upperLimit);

        vector<int> primeNumbers;  // Store all primes in the range [left, right]
        for (int num = left; num <= right; num++) {
            // If number is prime add to the primeNumbers list
            if (sieveArray[num] == 1) {
                primeNumbers.push_back(num);
            }
        }
        int primeNumbersSize = primeNumbers.size();

        // Step 2: Find the closest prime pair
        if (primeNumbersSize < 2) {
            return retVal;
        }

        int minDifference = numeric_limits<int>::max();
        for (int index = 1; index < primeNumbersSize; index++) {
            int difference = primeNumbers[index] - primeNumbers[index - 1];
            if (difference < minDifference) {
                minDifference = difference;
                retVal[0] = primeNumbers[index - 1];
                retVal[1] = primeNumbers[index];
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
    def sieve(self, upperLimit):
        retVal = [True] * (upperLimit + 1)  # True = prime, False = not prime

        # 0 and 1 are not prime
        retVal[0] = False
        retVal[1] = False

        for number in range(2, int(upperLimit**0.5) + 1):
            if retVal[number] == False:
                continue
            for multiple in range(number * number, upperLimit + 1, number):
                retVal[multiple] = False  # Mark all multiples of 'number' as non-prime

        return retVal

    def closestPrimes(self, left: int, right: int) -> List[int]:
        retVal = [-1] * 2

        # Step 1: Get all prime numbers up to 'right' using sieve
        sieveArray = self.sieve(right)
        primeNumbers = []
        for num in range(left, right + 1):
            if sieveArray[num] == True:
                primeNumbers.append(num)

        # Step 2: Find the closest prime pair
        primeNumbersSize = len(primeNumbers)
        if primeNumbersSize < 2:
            return retVal  # Less than two primes

        minDifference = float("inf")
        for index in range(1, primeNumbersSize):
            difference = primeNumbers[index] - primeNumbers[index - 1]
            if difference < minDifference:
                minDifference = difference
                retVal[0] = primeNumbers[index - 1]
                retVal[1] = primeNumbers[index]

        return retVal
```

</details>

## [2544. Alternating Digit Sum](https://leetcode.com/problems/alternating-digit-sum/)  1184

<details><summary>Description</summary>

```text
You are given a positive integer n. Each digit of n has a sign according to the following rules:
- The most significant digit is assigned a positive sign.
- Each other digit has an opposite sign to its adjacent digits.

Return the sum of all digits with their corresponding sign.

Example 1:
Input: n = 521
Output: 4
Explanation: (+5) + (-2) + (+1) = 4.

Example 2:
Input: n = 111
Output: 1
Explanation: (+1) + (-1) + (+1) = 1.

Example 3:
Input: n = 886996
Output: 0
Explanation: (+8) + (-8) + (+6) + (-9) + (+9) + (-6) = 0.

Constraints:
1 <= n <= 10^9
```

</details>

<details><summary>C</summary>

```c
#define REVERSE (1)
#define MATH (1)
int alternateDigitSum(int n) {
    int retVal = 0;

#if (REVERSE)
    printf("REVERSE\n");

    int reverse = 0;
    while (n > 0) {
        reverse = reverse * 10 + (n % 10);
        n /= 10;
    }

    int round = 0;
    while (reverse > 0) {
        if (round % 2 == 0) {
            retVal += (reverse % 10);
        } else {
            retVal -= (reverse % 10);
        }
        ++round;
        reverse /= 10;
    }
#elif (MATH)
    printf("MATH\n");

    /* Alternating Digit Sum
     *  n has odd digit: n = abcde, a - b + c - d + e = (e - d + c - b + a) * (1)
     *  n has even digit: n = abcd, a - b + c - d = (d - c + b - a) * (-1)
     */
    int sign = -1;
    while (n > 0) {
        sign *= (-1);
        retVal += (sign * (n % 10));
        n /= 10;
    }
    retVal *= sign;
#endif

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define REVERSE (1)
#define MATH (1)
   public:
    int alternateDigitSum(int n) {
        int retVal = 0;

        vector<int> nums;
#if (REVERSE)
        cout << "REVERSE\n";

        while (n > 0) {
            nums.push_back(n % 10);
            n /= 10;
        }
        reverse(nums.begin(), nums.end());

        int sign = 1;
        for (auto num : nums) {
            retVal += (sign * num);
            sign *= (-1);
        }
#elif (MATH)
        cout << "MATH\n";

        /* Alternating Digit Sum
         *  n has odd digit: n = abcde, a - b + c - d + e = (e - d + c - b + a) * (1)
         *  n has even digit: n = abcd, a - b + c - d = (d - c + b - a) * (-1)
         */
        int sign = -1;
        while (n > 0) {
            sign *= (-1);
            retVal += (sign * (n % 10));
            n /= 10;
        }
        retVal *= sign;
#endif

        return retVal;
    }
};
```

</details>

<details><summary>Rust</summary>

```rust
impl Solution {
    pub fn alternate_digit_sum(n: i32) -> i32 {
        let mut ret_val: i32 = 0;

        let mut n: i32 = n;
        let mut reverse: i32 = 0;
        while n > 0 {
            reverse = reverse * 10 + n % 10;
            n = n / 10;
        }
        #[cfg(string_reverse)]
        {
            let n: String = format!("{:?}", n);
            let reverse: String = n.chars().rev().collect::<String>();
            let mut reverse: i32 = reverse.parse().unwrap();
        }

        let mut sign: i32 = 1;
        while reverse > 0 {
            ret_val = ret_val + (sign * (reverse % 10));
            sign = sign * (-1);
            reverse = reverse / 10;
        }

        return ret_val;
    }
}
```

</details>

## [2579. Count Total Number of Colored Cells](https://leetcode.com/problems/count-total-number-of-colored-cells/)  1356

- [Official](https://leetcode.com/problems/count-total-number-of-colored-cells/editorial/)

<details><summary>Description</summary>

```text
There exists an infinitely large two-dimensional grid of uncolored unit cells.
You are given a positive integer n, indicating that you must do the following routine for n minutes:
- At the first minute, color any arbitrary unit cell blue.
- Every minute thereafter, color blue every uncolored cell that touches a blue cell.

Below is a pictorial representation of the state of the grid after minutes 1, 2, and 3.
                  3
       2        3 2 3
1 -> 2 1 2 -> 3 2 1 2 3
       2        3 2 3
                  3
Return the number of colored cells at the end of n minutes.

Example 1:
Input: n = 1
Output: 1
Explanation: After 1 minute, there is only 1 blue cell, so we return 1.

Example 2:
Input: n = 2
Output: 5
Explanation: After 2 minutes, there are 4 colored cells on the boundary and 1 in the center, so we return 5.

Constraints:
1 <= n <= 10^5
```

<details><summary>Hint</summary>

```text
1. Derive a mathematical relation between total number of colored cells and the time elapsed in minutes.
```

</details>

</details>

<details><summary>C</summary>

```c
long long coloredCells(int n) {
    long long retVal = 0;

    /*    1 + (4×1) + (4×2) + ... + (4×(n−1))
     *  = 1 + 4 x (1 + 2 + ... + (n-1))
     *  = 1 + 4 x (n x (n-1) / 2)
     *  = 1 + 2 x n x (n-1)
     */
    retVal = 1 + (long long)(2) * (long long)(n) * (long long)(n - 1);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long coloredCells(int n) {
        long long retVal = 0;

        /*    1 + (4×1) + (4×2) + ... + (4×(n−1))
         *  = 1 + 4 x (1 + 2 + ... + (n-1))
         *  = 1 + 4 x (n x (n-1) / 2)
         *  = 1 + 2 x n x (n-1)
         */
        retVal = 1 + (long long)(2) * (long long)(n) * (long long)(n - 1);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def coloredCells(self, n: int) -> int:
        retVal = 0

        # /*    1 + (4×1) + (4×2) + ... + (4×(n−1))
        #  *  = 1 + 4 x (1 + 2 + ... + (n-1))
        #  *  = 1 + 4 x (n x (n-1) / 2)
        #  *  = 1 + 2 x n x (n-1)
        #  */
        retVal = 1 + 2 * n * (n - 1)

        return retVal
```

</details>

## [2582. Pass the Pillow](https://leetcode.com/problems/pass-the-pillow/)  1278

- [Official](https://leetcode.com/problems/pass-the-pillow/editorial/)
- [Official](https://leetcode.cn/problems/pass-the-pillow/solutions/2451117/di-zhen-tou-by-leetcode-solution-kl5e/)

<details><summary>Description</summary>

```text
There are n people standing in a line labeled from 1 to n. The first person in the line is holding a pillow initially.
Every second, the person holding the pillow passes it to the next person standing in the line.
Once the pillow reaches the end of the line, the direction changes,
and people continue passing the pillow in the opposite direction.
- For example, once the pillow reaches the nth person they pass it to the n - 1th person,
  then to the n - 2th person and so on.

Given the two positive integers n and time, return the index of the person holding the pillow after time seconds.

Example 1:
Input: n = 4, time = 5
Output: 2
Explanation: People pass the pillow in the following way: 1 -> 2 -> 3 -> 4 -> 3 -> 2.
After five seconds, the 2nd person is holding the pillow.

Example 2:
Input: n = 3, time = 2
Output: 3
Explanation: People pass the pillow in the following way: 1 -> 2 -> 3.
After two seconds, the 3rd person is holding the pillow.

Constraints:
2 <= n <= 1000
1 <= time <= 1000
```

<details><summary>Hint</summary>

```text
1. Maintain two integer variables, direction and i,
   where direction denotes the current direction in which the pillow should pass,
   and i denotes an index of the person holding the pillow.
2. While time is positive, update the current index with the current direction.
   If the index reaches the end of the line, multiply direction by - 1.
```

</details>

</details>

<details><summary>C</summary>

```c
int passThePillow(int n, int time) {
    int retVal = 0;

    int direction = time / (n - 1);
    int index = time % (n - 1);
    if (direction % 2 == 0) {
        retVal = index + 1;
    } else if (direction % 2 == 1) {
        retVal = n - index;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int passThePillow(int n, int time) {
        int retVal = 0;

        int direction = time / (n - 1);
        int index = time % (n - 1);
        if (direction % 2 == 0) {
            retVal = index + 1;
        } else if (direction % 2 == 1) {
            retVal = n - index;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def passThePillow(self, n: int, time: int) -> int:
        retVal = 0

        direction = time // (n-1)
        index = time % (n-1)
        if direction % 2 == 0:
            retVal = index + 1
        elif direction % 2 == 1:
            retVal = n - index

        return retVal
```

</details>

## [2601. Prime Subtraction Operation](https://leetcode.com/problems/prime-subtraction-operation/)  1779

- [Official](https://leetcode.com/problems/prime-subtraction-operation/editorial/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array nums of length n.

You can perform the following operation as many times as you want:
- Pick an index i that you haven’t picked before,
  and pick a prime p strictly less than nums[i], then subtract p from nums[i].

Return true if you can make nums a strictly increasing array using the above operation and false otherwise.

A strictly increasing array is an array whose each element is strictly greater than its preceding element.

Example 1:
Input: nums = [4,9,6,10]
Output: true
Explanation:
In the first operation: Pick i = 0 and p = 3, and then subtract 3 from nums[0], so that nums becomes [1,9,6,10].
In the second operation: i = 1, p = 7, subtract 7 from nums[1], so nums becomes equal to [1,2,6,10].
After the second operation, nums is sorted in strictly increasing order, so the answer is true.

Example 2:
Input: nums = [6,8,11,12]
Output: true
Explanation: Initially nums is sorted in strictly increasing order, so we don't need to make any operations.

Example 3:
Input: nums = [5,8,3]
Output: false
Explanation:
It can be proven that there is no way to perform operations to make nums sorted in strictly increasing order,
so the answer is false.

Constraints:
1 <= nums.length <= 1000
1 <= nums[i] <= 1000
nums.length == n
```

<details><summary>Hint</summary>

```text
1. Think about if we have many primes to subtract from nums[i]. Which prime is more optimal?
2. The most optimal prime to subtract from nums[i] is the one
   that makes nums[i] the smallest as possible and greater than nums[i-1].
```

</details>

</details>

<details><summary>C</summary>

```c
bool primeSubOperation(int* nums, int numsSize) {
    bool retVal = false;

    int i, j;

    // Store the sieve array.
    int maxElement = nums[0];
    for (i = 1; i < numsSize; ++i) {
        maxElement = fmax(maxElement, nums[i]);
    }

    int sieve[maxElement + 1];
    for (i = 0; i < maxElement + 1; ++i) {
        sieve[i] = 1;
    }

    sieve[1] = 0;
    for (i = 2; i <= sqrt(maxElement + 1); i++) {
        if (sieve[i] == 1) {
            for (j = i * i; j <= maxElement; j += i) {
                sieve[j] = 0;
            }
        }
    }

    // Start by storing the currValue as 1, and the initial index as 0.
    int currValue = 1;
    int difference;
    i = 0;
    while (i < numsSize) {
        // Store the difference needed to make nums[i] equal to currValue.
        difference = nums[i] - currValue;
        // If difference is less than 0, then nums[i] is already less than currValue. Return false in this case.
        if (difference < 0) {
            return retVal;
        }

        // If the difference is prime or zero, then nums[i] can be made equal to currValue.
        // Otherwise, try for the next currValue.
        if ((sieve[difference] == 1) || (difference == 0)) {
            i++;
            currValue++;
        } else {
            currValue++;
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
    bool primeSubOperation(vector<int>& nums) {
        bool retVal = false;

        // Store the sieve array.
        int maxElement = *max_element(nums.begin(), nums.end());
        vector<int> sieve(maxElement + 1, 1);
        sieve[1] = 0;
        for (int i = 2; i <= sqrt(maxElement + 1); i++) {
            if (sieve[i] == 1) {
                for (int j = i * i; j <= maxElement; j += i) {
                    sieve[j] = 0;
                }
            }
        }

        // Start by storing the currValue as 1, and the initial index as 0.
        int currValue = 1;
        int numsSize = nums.size();
        int i = 0;
        while (i < numsSize) {
            // Store the difference needed to make nums[i] equal to currValue.
            int difference = nums[i] - currValue;
            // If difference is less than 0, then nums[i] is already less than currValue. Return false in this case.
            if (difference < 0) {
                return retVal;
            }

            // If the difference is prime or zero, then nums[i] can be made equal to currValue.
            // Otherwise, try for the next currValue.
            if ((sieve[difference] == 1) || (difference == 0)) {
                i++;
                currValue++;
            } else {
                currValue++;
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
    def primeSubOperation(self, nums: List[int]) -> bool:
        retVal = False

        # Store the sieve array.
        maxElement = max(nums)
        sieve = [1] * (maxElement + 1)
        sieve[1] = 0
        for i in range(2, int(sqrt(maxElement + 1)) + 1):
            if sieve[i] == 1:
                for j in range(i * i, maxElement + 1, i):
                    sieve[j] = 0

        # Start by storing the currValue as 1, and the initial index as 0.
        currValue = 1

        numsSize = len(nums)
        i = 0
        while i < numsSize:
            # Store the difference needed to make nums[i] equal to currValue.
            difference = nums[i] - currValue
            # If difference is less than 0, then nums[i] is already less than currValue. Return false in this case.
            if difference < 0:
                return retVal

            # If the difference is prime or zero, then nums[i] can be made equal to currValue.
            # Otherwise, try for the next currValue.
            if sieve[difference] or difference == 0:
                i += 1
                currValue += 1
            else:
                currValue += 1

        retVal = True

        return retVal
```

</details>

## [2843. Count Symmetric Integers](https://leetcode.com/problems/count-symmetric-integers/)  1269

- [Official](https://leetcode.com/problems/count-symmetric-integers/editorial/)
- [Official](https://leetcode.cn/problems/count-symmetric-integers/solutions/3636168/tong-ji-dui-cheng-zheng-shu-de-shu-mu-by-layo/)

<details><summary>Description</summary>

```text
You are given two positive integers low and high.

An integer x consisting of 2 * n digits is symmetric
if the sum of the first n digits of x is equal to the sum of the last n digits of x.
Numbers with an odd number of digits are never symmetric.

Return the number of symmetric integers in the range [low, high].

Example 1:
Input: low = 1, high = 100
Output: 9
Explanation: There are 9 symmetric integers between 1 and 100: 11, 22, 33, 44, 55, 66, 77, 88, and 99.

Example 2:
Input: low = 1200, high = 1230
Output: 4
Explanation: There are 4 symmetric integers between 1200 and 1230: 1203, 1212, 1221, and 1230.

Constraints:
1 <= low <= high <= 10^4
```

<details><summary>Hint</summary>

```text
1. Iterate over all numbers from low to high
2. Convert each number to a string and compare the sum of the first half with that of the second.
```

</details>

</details>

<details><summary>C</summary>

```c
int countSymmetricIntegers(int low, int high) {
    int retVal = 0;

    // 1 <= low <= high <= 10^4
    for (int num = low; num <= high; ++num) {
        if (num < 100) {
            if (num % 11 == 0) {
                retVal++;
            }
        } else if ((1000 <= num) && (num < 10000)) {
            int left = num / 1000 + (num % 1000) / 100;
            int right = (num % 100) / 10 + num % 10;
            if (left == right) {
                retVal++;
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
    int countSymmetricIntegers(int low, int high) {
        int retVal = 0;

        // 1 <= low <= high <= 10^4
        for (int num = low; num <= high; ++num) {
            if (num < 100) {
                if (num % 11 == 0) {
                    retVal++;
                }
            } else if ((1000 <= num) && (num < 10000)) {
                int left = num / 1000 + (num % 1000) / 100;
                int right = (num % 100) / 10 + num % 10;
                if (left == right) {
                    retVal++;
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
    def countSymmetricIntegers(self, low: int, high: int) -> int:
        retVal = 0

        # 1 <= low <= high <= 10^4
        for num in range(low, high + 1):
            if num < 100:
                if num % 11 == 0:
                    retVal += 1
            elif 1000 <= num < 10000:
                left = num // 1000 + num % 1000 // 100
                right = num % 100 // 10 + num % 10
                if left == right:
                    retVal += 1

        return retVal
```

</details>

## [2849. Determine if a Cell Is Reachable at a Given Time](https://leetcode.com/problems/determine-if-a-cell-is-reachable-at-a-given-time/)  1515

- [Official](https://leetcode.com/problems/determine-if-a-cell-is-reachable-at-a-given-time/editorial/)

<details><summary>Description</summary>

```text
You are given four integers sx, sy, fx, fy, and a non-negative integer t.

In an infinite 2D grid, you start at the cell (sx, sy). Each second, you must move to any of its adjacent cells.

Return true if you can reach cell (fx, fy) after exactly t seconds, or false otherwise.

A cell's adjacent cells are the 8 cells around it that share at least one corner with it.
You can visit the same cell several times.

Example 1:
Input: sx = 2, sy = 4, fx = 7, fy = 7, t = 6
Output: true
Explanation: Starting at cell (2, 4),
we can reach cell (7, 7) in exactly 6 seconds by going through the cells depicted in the picture above.

Example 2:
Input: sx = 3, sy = 1, fx = 7, fy = 3, t = 3
Output: false
Explanation: Starting at cell (3, 1),
it takes at least 4 seconds to reach cell (7, 3) by going through the cells depicted in the picture above.
Hence, we cannot reach cell (7, 3) at the third second.

Constraints:
1 <= sx, sy, fx, fy <= 10^9
0 <= t <= 10^9
```

<details><summary>Hint</summary>

```text
1. Minimum time to reach the cell should be less than or equal to given time.
2. The answer is true if t is greater or equal than the Chebyshev distance from (sx, sy) to (fx, fy).
   However, there is one more edge case to be considered.
3. The answer is false If sx == fx and sy == fy
```

</details>

</details>

<details><summary>C</summary>

```c
bool isReachableAtTime(int sx, int sy, int fx, int fy, int t) {
    bool retVal = false;

    int diffX = abs(fx - sx);
    int diffY = abs(fy - sy);

    if ((diffX == 0) && (diffY == 0)) {
        if (t != 1) {
            retVal = true;
        }
    } else {
        if ((t - fmin(diffX, diffY)) >= (fmax(diffX, diffY) - fmin(diffX, diffY))) {
            retVal = true;
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
    bool isReachableAtTime(int sx, int sy, int fx, int fy, int t) {
        bool retVal = false;

        int diffX = abs(fx - sx);
        int diffY = abs(fy - sy);

        if ((diffX == 0) && (diffY == 0)) {
            if (t != 1) {
                retVal = true;
            }
        } else {
            if ((t - min(diffX, diffY)) >= (max(diffX, diffY) - min(diffX, diffY))) {
                retVal = true;
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
    def isReachableAtTime(self, sx: int, sy: int, fx: int, fy: int, t: int) -> bool:
        retVal = False

        diffX = abs(fx - sx)
        diffY = abs(fy - sy)

        if (diffX == 0) and (diffY == 0):
            if t != 1:
                retVal = True
        else:
            if (t - min(diffX, diffY)) >= (max(diffX, diffY) - min(diffX, diffY)):
                retVal = True

        return retVal
```

</details>

## [2864. Maximum Odd Binary Number](https://leetcode.com/problems/maximum-odd-binary-number/)  1237

- [Official](https://leetcode.com/problems/maximum-odd-binary-number/editorial/)

<details><summary>Description</summary>

```text
You are given a binary string s that contains at least one '1'.

You have to rearrange the bits in such a way
that the resulting binary number is the maximum odd binary number that can be created from this combination.

Return a string representing the maximum odd binary number that can be created from the given combination.

Note that the resulting string can have leading zeros.

Example 1:
Input: s = "010"
Output: "001"
Explanation: Because there is just one '1', it must be in the last position. So the answer is "001".

Example 2:
Input: s = "0101"
Output: "1001"
Explanation: One of the '1's must be in the last position.
The maximum number that can be made with the remaining digits is "100". So the answer is "1001".

Constraints:
1 <= s.length <= 100
s consists only of '0' and '1'.
s contains at least one '1'.
```

<details><summary>Hint</summary>

```text
1. The binary representation of an odd number contains '1' in the least significant place.
```

</details>

</details>

<details><summary>C</summary>

```c
char* maximumOddBinaryNumber(char* s) {
    char* pRetVal = s;

    int sSize = strlen(s);

    int count1 = 0;
    int i;
    for (i = 0; i < sSize; ++i) {
        if (s[i] == '1') {
            count1++;
        }
    }

    for (i = 0; i < (count1 - 1); ++i) {
        pRetVal[i] = '1';
    }
    for (i = (count1 - 1); i < (sSize - 1); ++i) {
        pRetVal[i] = '0';
    }
    pRetVal[sSize - 1] = '1';

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string maximumOddBinaryNumber(string s) {
        string retVal = "";

        int count1 = 0;
        int count0 = 0;
        for (auto c : s) {
            if (c == '1') {
                count1++;
            } else {
                count0++;
            }
        }

        for (int i = 1; i < count1; ++i) {
            retVal += "1";
        }
        for (int i = 0; i < count0; ++i) {
            retVal += "0";
        }
        retVal += "1";

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maximumOddBinaryNumber(self, s: str) -> str:
        retVal = ""

        sSize = len(s)

        count1 = s.count('1')
        retVal = '1' * (count1 - 1) + '0' * (sSize - count1) + '1'

        return retVal
```

</details>

## [2894. Divisible and Non-divisible Sums Difference](https://leetcode.com/problems/divisible-and-non-divisible-sums-difference/)  1140

- [Official](https://leetcode.com/problems/divisible-and-non-divisible-sums-difference/editorial/)
- [Official](https://leetcode.cn/problems/divisible-and-non-divisible-sums-difference/solutions/3676585/fen-lei-qiu-he-bing-zuo-chai-by-leetcode-xok4/)

<details><summary>Description</summary>

```text
You are given positive integers n and m.

Define two integers as follows:
- num1: The sum of all integers in the range [1, n] (both inclusive) that are not divisible by m.
- num2: The sum of all integers in the range [1, n] (both inclusive) that are divisible by m.

Return the integer num1 - num2.

Example 1:
Input: n = 10, m = 3
Output: 19
Explanation: In the given example:
- Integers in the range [1, 10] that are not divisible by 3 are [1,2,4,5,7,8,10], num1 is the sum of those integers = 37.
- Integers in the range [1, 10] that are divisible by 3 are [3,6,9], num2 is the sum of those integers = 18.
We return 37 - 18 = 19 as the answer.

Example 2:
Input: n = 5, m = 6
Output: 15
Explanation: In the given example:
- Integers in the range [1, 5] that are not divisible by 6 are [1,2,3,4,5], num1 is the sum of those integers = 15.
- Integers in the range [1, 5] that are divisible by 6 are [], num2 is the sum of those integers = 0.
We return 15 - 0 = 15 as the answer.

Example 3:
Input: n = 5, m = 1
Output: -15
Explanation: In the given example:
- Integers in the range [1, 5] that are not divisible by 1 are [], num1 is the sum of those integers = 0.
- Integers in the range [1, 5] that are divisible by 1 are [1,2,3,4,5], num2 is the sum of those integers = 15.
We return 0 - 15 = -15 as the answer.

Constraints:
1 <= n, m <= 1000
```

<details><summary>Hint</summary>

```text
1. With arithmetic progression we know that the sum of integers in the range [1, n] is n * (n + 1) / 2 .
```

</details>

</details>

<details><summary>C</summary>

```c
int differenceOfSums(int n, int m) {
    int retVal = 0;

    for (int i = 1; i <= n; ++i) {
        if (i % m == 0) {
            retVal -= i;
        } else {
            retVal += i;
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
    int differenceOfSums(int n, int m) {
        int retVal = 0;

        for (int i = 1; i <= n; ++i) {
            if (i % m == 0) {
                retVal -= i;
            } else {
                retVal += i;
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
    def differenceOfSums(self, n: int, m: int) -> int:
        retVal = 0

        for i in range(1, n+1):
            if i % m == 0:
                retVal -= i
            else:
                retVal += i

        return retVal
```

</details>

## [2929. Distribute Candies Among Children II](https://leetcode.com/problems/distribute-candies-among-children-ii/)  1701

- [Official](https://leetcode.com/problems/distribute-candies-among-children-ii/editorial/)
- [Official](https://leetcode.cn/problems/distribute-candies-among-children-ii/solutions/2791756/gei-xiao-peng-you-men-fen-tang-guo-ii-by-1jj9/)

<details><summary>Description</summary>

```text
You are given two positive integers n and limit.

Return the total number of ways to distribute n candies among 3 children such that no child gets more than limit candies.

Example 1:
Input: n = 5, limit = 2
Output: 3
Explanation: There are 3 ways to distribute 5 candies such that no child gets more than 2 candies:
(1, 2, 2), (2, 1, 2) and (2, 2, 1).

Example 2:
Input: n = 3, limit = 3
Output: 10
Explanation: There are 10 ways to distribute 3 candies such that no child gets more than 3 candies:
(0, 0, 3), (0, 1, 2), (0, 2, 1), (0, 3, 0), (1, 0, 2), (1, 1, 1), (1, 2, 0), (2, 0, 1), (2, 1, 0) and (3, 0, 0).

Constraints:
1 <= n <= 10^6
1 <= limit <= 10^6
```

<details><summary>Hint</summary>

```text
1. We can enumerate the number of candies of one particular child, let it be i which means 0 <= i <= min(limit, n).
2. Suppose the 2nd child gets j candies. Then 0 <= j <= limit and i + j <= n.
3. The 3rd child will hence get n - i - j candies and we should have 0 <= n - i - j <= limit.
4. After some transformations, for each i, we have max(0, n - i - limit) <= j <= min(limit, n - i),
   each j corresponding to a solution.
   So the number of solutions for some i is max(min(limit, n - i) - max(0, n - i - limit) + 1, 0).
   Sum the expression for every i in [0, min(n, limit)].
```

</details>

</details>

<details><summary>C</summary>

```c
long long distributeCandies(int n, int limit) {
    long long retVal = 0;

    int minLimit = fmin(limit, n);
    for (int i = 0; i <= minLimit; i++) {
        if ((n - i) > (2 * limit)) {
            continue;
        }
        retVal += (fmin(n - i, limit) - fmax(0, n - i - limit) + 1);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long distributeCandies(int n, int limit) {
        long long retVal = 0;

        int minLimit = min(limit, n);
        for (int i = 0; i <= minLimit; i++) {
            if ((n - i) > (2 * limit)) {
                continue;
            }
            retVal += (min(n - i, limit) - max(0, n - i - limit) + 1);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def distributeCandies(self, n: int, limit: int) -> int:
        retVal = 0

        minLimit = min(limit, n)
        for i in range(minLimit + 1):
            if (n - i) > (2 * limit):
                continue
            retVal += (min(n - i, limit) - max(0, n - i - limit) + 1)

        return retVal
```

</details>

## [3024. Type of Triangle](https://leetcode.com/problems/type-of-triangle/)  1134

- [Official](https://leetcode.com/problems/type-of-triangle/editorial/)
- [Official](https://leetcode.cn/problems/type-of-triangle/solutions/3670439/san-jiao-xing-lei-xing-by-leetcode-solut-we7x/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array nums of size 3 which can form the sides of a triangle.
- A triangle is called equilateral if it has all sides of equal length.
- A triangle is called isosceles if it has exactly two sides of equal length.
- A triangle is called scalene if all its sides are of different lengths.

Return a string representing the type of triangle that can be formed or "none" if it cannot form a triangle.

Example 1:
Input: nums = [3,3,3]
Output: "equilateral"
Explanation: Since all the sides are of equal length, therefore, it will form an equilateral triangle.

Example 2:
Input: nums = [3,4,5]
Output: "scalene"
Explanation:
nums[0] + nums[1] = 3 + 4 = 7, which is greater than nums[2] = 5.
nums[0] + nums[2] = 3 + 5 = 8, which is greater than nums[1] = 4.
nums[1] + nums[2] = 4 + 5 = 9, which is greater than nums[0] = 3.
Since the sum of the two sides is greater than the third side for all three cases, therefore, it can form a triangle.
As all the sides are of different lengths, it will form a scalene triangle.

Constraints:
nums.length == 3
1 <= nums[i] <= 100
```

<details><summary>Hint</summary>

```text
1. The condition for a valid triangle is that for any two sides,
   the sum of their lengths must be greater than the third side.
2. Simply count the number of unique edge lengths after checking it’s a valid triangle.
```

</details>

</details>

<details><summary>C</summary>

```c
#define NONE_STR "none"
#define EQUILATERAL_STR "equilateral"
#define ISOSCELES_STR "isosceles"
#define SCALENE_STR "scalene"
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
char* triangleType(int* nums, int numsSize) {
    char* pRetVal;

    qsort(nums, numsSize, sizeof(int), compareInteger);
    if (nums[0] + nums[1] <= nums[2]) {
        pRetVal = NONE_STR;
    } else if (nums[0] == nums[2]) {
        pRetVal = EQUILATERAL_STR;
    } else if ((nums[0] == nums[1]) || (nums[1] == nums[2])) {
        pRetVal = ISOSCELES_STR;
    } else {
        pRetVal = SCALENE_STR;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    string none = "none";
    string equilateral = "equilateral";
    string isosceles = "isosceles";
    string scalene = "scalene";

   public:
    string triangleType(vector<int>& nums) {
        string retVal;

        sort(nums.begin(), nums.end());
        if (nums[0] + nums[1] <= nums[2]) {
            retVal = none;
        } else if (nums[0] == nums[2]) {
            retVal = equilateral;
        } else if ((nums[0] == nums[1]) || (nums[1] == nums[2])) {
            retVal = isosceles;
        } else {
            retVal = scalene;
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
        self.none = "none"
        self.equilateral = "equilateral"
        self.isosceles = "isosceles"
        self.scalene = "scalene"

    def triangleType(self, nums: List[int]) -> str:
        retVal = ""

        nums.sort()
        if nums[0] + nums[1] <= nums[2]:
            retVal = self.none
        elif nums[0] == nums[2]:
            retVal = self.equilateral
        elif (nums[0] == nums[1]) or (nums[1] == nums[2]):
            retVal = self.isosceles
        else:
            retVal = self.scalene

        return retVal
```

</details>

## [3272. Find the Count of Good Integers](https://leetcode.com/problems/find-the-count-of-good-integers/)  2382

- [Official](https://leetcode.com/problems/find-the-count-of-good-integers/editorial/)
- [Official](https://leetcode.cn/problems/find-the-count-of-good-integers/solutions/3637602/tong-ji-hao-zheng-shu-de-shu-mu-by-leetc-m5l4/)

<details><summary>Description</summary>

```text
You are given two positive integers n and k.

An integer x is called k-palindromic if:
- x is a palindrome.
- x is divisible by k.

An integer is called good if its digits can be rearranged to form a k-palindromic integer.
For example, for k = 2, 2020 can be rearranged to form the k-palindromic integer 2002,
whereas 1010 cannot be rearranged to form a k-palindromic integer.

Return the count of good integers containing n digits.

Note that any integer must not have leading zeros, neither before nor after rearrangement.
For example, 1010 cannot be rearranged to form 101.

Example 1:
Input: n = 3, k = 5
Output: 27
Explanation:
Some of the good integers are:
551 because it can be rearranged to form 515.
525 because it is already k-palindromic.

Example 2:
Input: n = 1, k = 4
Output: 2
Explanation:
The two good integers are 4 and 8.

Example 3:
Input: n = 5, k = 6
Output: 2468

Constraints:
1 <= n <= 10
1 <= k <= 9
```

<details><summary>Hint</summary>

```text
1. How to generate all K-palindromic strings of length n? Do we need to go through all n digits?
2. Use permutations to calculate the number of possible rearrangements.
```

</details>

</details>

<details><summary>C</summary>

```c
struct hashTable {
    char *key;
    UT_hash_handle hh;
};
void freeAll(struct hashTable *pFree) {
    struct hashTable *current;
    struct hashTable *tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%s\n", pFree->key);
        HASH_DEL(pFree, current);
        free(current->key);
        free(current);
    }
}
int compareChar(const void *c1, const void *c2) {
    // ascending order
    return (*(char *)c1 > *(char *)c2);
}
long long countGoodIntegers(int n, int k) {
    long long retVal = 0;

    // Enumerate the number of palindrome numbers of n digits
    int base = (int)pow(10, (n - 1) / 2);
    int skip = n & 1;
    char s[16];
    int sSize;
    long long palindromicInteger;
    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    for (int i = base; i < base * 10; i++) {
        memset(s, 0, sizeof(s));
        sprintf(s, "%d", i);
        sSize = strlen(s);
        for (int j = sSize - 1 - skip; j >= 0; j--) {
            s[sSize + (sSize - skip - 1 - j)] = s[j];
        }
        s[2 * sSize - skip] = '\0';
        palindromicInteger = atoll(s);

        // If the current palindrome number is a k-palindromic integer
        if (palindromicInteger % k == 0) {
            sSize = strlen(s);
            qsort(s, sSize, sizeof(char), compareChar);

            pTemp = NULL;
            HASH_FIND_STR(pHashTable, s, pTemp);
            if (pTemp != NULL) {
                continue;
            }
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                return retVal;
            }
            pTemp->key = strdup(s);
            HASH_ADD_STR(pHashTable, key, pTemp);
        }
    }

    long long *factorial = malloc((n + 1) * sizeof(long long));
    if (factorial == NULL) {
        perror("malloc");
        freeAll(pHashTable);
        return retVal;
    }
    factorial[0] = 1;
    for (int i = 1; i <= n; i++) {
        factorial[i] = factorial[i - 1] * i;
    }

    pTemp = NULL;
    int cnt[10];
    long long tot;
    for (pTemp = pHashTable; pTemp; pTemp = pTemp->hh.next) {
        memset(cnt, 0, sizeof(cnt));
        for (int j = 0; pTemp->key[j] != '\0'; j++) {
            cnt[pTemp->key[j] - '0']++;
        }

        // Calculate permutations and combinations
        tot = (n - cnt[0]) * factorial[n - 1];
        for (int j = 0; j < 10; j++) {
            tot /= factorial[cnt[j]];
        }
        retVal += tot;
    }

    //
    free(factorial);
    freeAll(pHashTable);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long countGoodIntegers(int n, int k) {
        long long retVal = 0;

        // Enumerate the number of palindrome numbers of n digits
        int base = pow(10, (n - 1) / 2);
        int skip = n & 1;
        unordered_set<string> dict;
        for (int i = base; i < base * 10; i++) {
            string s = to_string(i);
            s += string(s.rbegin() + skip, s.rend());
            long long palindromicInteger = stoll(s);

            // If the current palindrome number is a k-palindromic integer
            if (palindromicInteger % k == 0) {
                sort(s.begin(), s.end());
                dict.emplace(s);
            }
        }

        vector<long long> factorial(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            factorial[i] = factorial[i - 1] * i;
        }
        for (const string& s : dict) {
            vector<int> cnt(10);
            for (char c : s) {
                cnt[c - '0']++;
            }

            // Calculate permutations and combinations
            long long tot = (n - cnt[0]) * factorial[n - 1];
            for (int x : cnt) {
                tot /= factorial[x];
            }
            retVal += tot;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def countGoodIntegers(self, n: int, k: int) -> int:
        retVal = 0

        # Enumerate the number of palindrome numbers of n digits
        base = 10 ** ((n - 1) // 2)
        skip = n & 1
        dictionary = set()
        for i in range(base, base * 10):
            s = str(i)
            s += s[::-1][skip:]
            palindromicInteger = int(s)

            # If the current palindrome number is a k-palindromic integer
            if palindromicInteger % k == 0:
                sorted_s = "".join(sorted(s))
                dictionary.add(sorted_s)

        fac = [factorial(i) for i in range(n + 1)]
        for s in dictionary:
            cnt = [0] * 10
            for c in s:
                cnt[int(c)] += 1

            # Calculate permutations and combinations
            tot = (n - cnt[0]) * fac[n - 1]
            for x in cnt:
                tot //= fac[x]
            retVal += tot

        return retVal
```

</details>
