# Bit Manipulation

## [29. Divide Two Integers](https://leetcode.com/problems/divide-two-integers/)

- [Official](https://leetcode.cn/problems/divide-two-integers/solutions/1041939/liang-shu-xiang-chu-by-leetcode-solution-5hic/)

<details><summary>Description</summary>

```text
Given two integers dividend and divisor, divide two integers without using multiplication, division, and mod operator.

The integer division should truncate toward zero, which means losing its fractional part.
For example, 8.345 would be truncated to 8, and -2.7335 would be truncated to -2.

Return the quotient after dividing dividend by divisor.

Note: Assume we are dealing with an environment that could only store integers
within the 32-bit signed integer range: [−2^31, 2^31 − 1].
For this problem, if the quotient is strictly greater than 2^31 - 1,
then return 2^31 - 1, and if the quotient is strictly less than -2^31, then return -2^31.

Example 1:
Input: dividend = 10, divisor = 3
Output: 3
Explanation: 10/3 = 3.33333.. which is truncated to 3.

Example 2:
Input: dividend = 7, divisor = -3
Output: -2
Explanation: 7/-3 = -2.33333.. which is truncated to -2.

Constraints:
-2^31 <= dividend, divisor <= 2^31 - 1
divisor != 0
```

</details>

<details><summary>C</summary>

```c
int divide(int dividend, int divisor) {
    int quotient = 0;

    if ((dividend == 0) || (divisor == 0)) {
        return quotient;
    }

    long absDividend = labs(dividend);
    long absDivisor = labs(divisor);
    if (absDividend < absDivisor) {
        return quotient;
    }

    int i;
    for (i = 31; i >= 0; --i) {
        if ((absDivisor << i) > absDividend) {
            continue;
        }
        absDividend -= (absDivisor << i);
        quotient += ((long)1 << i);
    }

    int negative = (((dividend < 0) ^ (divisor < 0)) == 1) ? (-1) : 1;
    if ((quotient == INT_MIN) && (negative == 1)) {
        quotient = INT_MAX;
    } else if ((quotient == INT_MIN) && (negative == -1)) {
        negative = 1;
    }
    quotient = negative * quotient;

    return quotient;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int divide(int dividend, int divisor) {
        int quotient = 0;

        if ((dividend == 0) || (divisor == 0)) {
            return quotient;
        }

        long absDividend = labs(dividend);
        long absDivisor = labs(divisor);
        if (absDividend < absDivisor) {
            return quotient;
        }

        int i;
        for (i = 31; i >= 0; --i) {
            if ((absDivisor << i) > absDividend) {
                continue;
            }
            absDividend -= (absDivisor << i);
            quotient += ((long)1 << i);
        }

        int negative = (((dividend < 0) ^ (divisor < 0)) == 1) ? (-1) : 1;
        if ((quotient == numeric_limits<int>::min()) && (negative == 1)) {
            quotient = numeric_limits<int>::max();
        } else if ((quotient == numeric_limits<int>::min()) && (negative == -1)) {
            negative = 1;
        }
        quotient = negative * quotient;

        return quotient;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def divide(self, dividend: int, divisor: int) -> int:
        quotient = 0

        negative = dividend < 0 or divisor < 0
        if dividend < 0 and divisor < 0:
            negative = 0

        dividend = abs(dividend)
        divisor = abs(divisor)
        for i in range(31,-1,-1):
            if (divisor<<i) <= dividend:
                dividend -= (divisor<<i)
                quotient += (1<<i)

        if quotient == 2147483648 and negative == 0:
            quotient = 2147483647

        if negative == 1:
            quotient =  -1 * quotient

        return quotient
```

</details>

## [67. Add Binary](https://leetcode.com/problems/add-binary/)

- [Official](https://leetcode.cn/problems/add-binary/solutions/299667/er-jin-zhi-qiu-he-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given two binary strings a and b, return their sum as a binary string.

Example 1:
Input: a = "11", b = "1"
Output: "100"

Example 2:
Input: a = "1010", b = "1011"
Output: "10101"

Constraints:
1 <= a.length, b.length <= 10^4
a and b consist only of '0' or '1' characters.
Each string does not contain leading zeros except for the zero itself.
```

</details>

<details><summary>C</summary>

```c
char *addBinary(char *a, char *b) {
    char *pRetVal = NULL;

    //
    int lenA = strlen(a) - 1;
    int lenB = strlen(b) - 1;
    int len = (lenA > lenB ? (lenA + 1) : (lenB + 1)) + 2;
    char buf[len];
    memset(buf, 0, sizeof(buf));
    int idx = len - 2;

    //
    int sum;
    int carry = 0;
    while ((lenA >= 0) && (lenB >= 0)) {
        sum = (a[lenA--] - '0') + (b[lenB--] - '0') + carry;
        carry = (sum > 1 ? 1 : 0);
        buf[idx--] = (sum % 2) + '0';
    }
    while (lenA >= 0) {
        sum = (a[lenA--] - '0') + carry;
        carry = (sum > 1 ? 1 : 0);
        buf[idx--] = (sum % 2) + '0';
    }
    while (lenB >= 0) {
        sum = (b[lenB--] - '0') + carry;
        carry = (sum > 1 ? 1 : 0);
        buf[idx--] = (sum % 2) + '0';
    }
    if (carry == 1) {
        buf[idx--] = carry + '0';
    }

    //
    pRetVal = (char *)calloc((len - 1 - idx), sizeof(char));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }
    memcpy(pRetVal, buf + 1 + idx, ((len - 1 - idx) * sizeof(char)));

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string addBinary(string a, string b) {
        string retVal;

        int sum;
        int carry = 0;
        int idxA = a.length() - 1;
        int idxB = b.length() - 1;
        while ((idxA >= 0) && (idxB >= 0)) {
            sum = (a[idxA--] - '0') + (b[idxB--] - '0') + carry;
            carry = sum > 1 ? 1 : 0;
            retVal = (char)((sum % 2) + '0') + retVal;
        }
        while (idxA >= 0) {
            sum = (a[idxA--] - '0') + carry;
            carry = sum > 1 ? 1 : 0;
            retVal = (char)((sum % 2) + '0') + retVal;
        }
        while (idxB >= 0) {
            sum = (b[idxB--] - '0') + carry;
            carry = sum > 1 ? 1 : 0;
            retVal = (char)((sum % 2) + '0') + retVal;
        }
        if (carry == 1) {
            retVal = (char)((carry + '0')) + retVal;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def addBinary(self, a: str, b: str) -> str:
        retVal = ""

        carry = 0
        aIdx = len(a) - 1
        bIdx = len(b) - 1
        while (aIdx >= 0) and (bIdx >= 0):
            value = int(a[aIdx]) + int(b[bIdx]) + carry
            retVal = str(value % 2) + retVal
            carry = value // 2
            aIdx -= 1
            bIdx -= 1
        while (aIdx >= 0):
            value = int(a[aIdx]) + carry
            retVal = str(value % 2) + retVal
            carry = value // 2
            aIdx -= 1
        while (bIdx >= 0):
            value = int(b[bIdx]) + carry
            retVal = str(value % 2) + retVal
            carry = value // 2
            bIdx -= 1
        if carry == 1:
            retVal = "1" + retVal

        return retVal
```

</details>

## [78. Subsets](https://leetcode.com/problems/subsets/)

- [Official](https://leetcode.cn/problems/subsets/solutions/420294/zi-ji-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given an integer array nums of unique elements, return all possible subsets (the power set).

The solution set must not contain duplicate subsets. Return the solution in any order.

Example 1:
Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

Example 2:
Input: nums = [0]
Output: [[],[0]]

Constraints:
1 <= nums.length <= 10
-10 <= nums[i] <= 10
All the numbers of nums are unique.
```

</details>

<details><summary>C</summary>

```c
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;

    //
    int mallocSize = 1 << numsSize;
    pRetVal = (int**)malloc(mallocSize * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    (*returnColumnSizes) = (int*)malloc(mallocSize * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, (mallocSize * sizeof(int)));

    //
    int i, j;
    for (i = 0; i < mallocSize; ++i) {
        pRetVal[i] = (int*)malloc(numsSize * sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        memset(pRetVal[i], 0, (numsSize * sizeof(int)));

        for (j = 0; j < numsSize; ++j) {
            if (i >> j & 1) {
                pRetVal[i][(*returnColumnSizes)[i]] = nums[j];
                (*returnColumnSizes)[i]++;
            }
        }
    }
    (*returnSize) = mallocSize;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> retVal;

        int numsSize = nums.size();
        for (int bitmask = 0; bitmask < (1 << numsSize); ++bitmask) {
            vector<int> sequence;
            for (int i = 0; i < numsSize; ++i) {
                if (((bitmask >> i) & 1) == 1) {
                    sequence.push_back(nums[i]);
                }
            }
            retVal.push_back(sequence);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        retVal = []

        numsSize = len(nums)
        for bitmask in range((1 << numsSize)):
            sequence = []
            for i in range(numsSize):
                if ((bitmask >> i) & 1) == 1:
                    sequence.append(nums[i])
            retVal.append(sequence)

        return retVal
```

</details>

## [89. Gray Code](https://leetcode.com/problems/gray-code/)

<details><summary>Description</summary>

```text
An n-bit gray code sequence is a sequence of 2n integers where:
- Every integer is in the inclusive range [0, 2n - 1],
- The first integer is 0,
- An integer appears no more than once in the sequence,
- The binary representation of every pair of adjacent integers differs by exactly one bit, and
- The binary representation of the first and last integers differs by exactly one bit.

Given an integer n, return any valid n-bit gray code sequence.

Example 1:
Input: n = 2
Output: [0,1,3,2]
Explanation:
The binary representation of [0,1,3,2] is [00,01,11,10].
- 00 and 01 differ by one bit
- 01 and 11 differ by one bit
- 11 and 10 differ by one bit
- 10 and 00 differ by one bit
[0,2,3,1] is also a valid gray code sequence, whose binary representation is [00,10,11,01].
- 00 and 10 differ by one bit
- 10 and 11 differ by one bit
- 11 and 01 differ by one bit
- 01 and 00 differ by one bit

Example 2:
Input: n = 1
Output: [0,1]

Constraints:
1 <= n <= 16
```

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* grayCode(int n, int* returnSize){
    int* pRetVal = NULL;

    *returnSize = (1 << n);
    pRetVal = (int*)malloc((*returnSize)*sizeof(int));
    if (pRetVal == NULL)
    {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (*returnSize)*sizeof(int));

    int shift;
    int tmp;
    int i = 0;
    /* 直接排列
     *  以二進制為0值的格雷碼為第零項，
     *  第一項改變最右邊的位元，
     *  第二項改變右起第一個為1的位元的左邊位元，
     *  第三、四項方法同第一、二項，如此反覆，即可排列出n個位元的格雷碼。
     *
     *  https://zh.wikipedia.org/wiki/%E6%A0%BC%E9%9B%B7%E7%A0%81
     */
    while (i < *returnSize)
    {
        pRetVal[i+1] = pRetVal[i] ^ 1;
        ++i;

        if ((i+1) >= (*returnSize))
        {
            break;
        }
        shift = 0;
        tmp = pRetVal[i];
        while ((tmp&1) == 0)
        {
            ++shift;
            tmp >>= 1;
        }
        ++shift;
        pRetVal[i+1] = (1<<shift) ^ pRetVal[i];
        ++i;
    }

    return pRetVal;
}
```

</details>

## [136. Single Number](https://leetcode.com/problems/single-number/)

- [Official](https://leetcode.cn/problems/single-number/solutions/242211/zhi-chu-xian-yi-ci-de-shu-zi-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.

You must implement a solution with a linear runtime complexity and use only constant extra space.

Example 1:
Input: nums = [2,2,1]
Output: 1

Example 2:
Input: nums = [4,1,2,1,2]
Output: 4

Example 3:
Input: nums = [1]
Output: 1

Constraints:
1 <= nums.length <= 3 * 10^4
-3 * 10^4 <= nums[i] <= 3 * 10^4
Each element in the array appears twice except for one element which appears only once.
```

</details>

<details><summary>C</summary>

```c
int singleNumber(int* nums, int numsSize) {
    int retVal = 0;

    int i;
    for (i = 0; i < numsSize; ++i) {
        retVal ^= nums[i];
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int singleNumber(vector<int>& nums) {
        int retVal = 0;

        for (auto num : nums) {
            retVal ^= num;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def singleNumber(self, nums: List[int]) -> int:
        retVal = 0

        for num in nums:
            retVal ^= num

        return retVal
```

</details>

## [137. Single Number II](https://leetcode.com/problems/single-number-ii/)

- [Official](https://leetcode.cn/problems/single-number-ii/solutions/746993/zhi-chu-xian-yi-ci-de-shu-zi-ii-by-leetc-23t6/)

<details><summary>Description</summary>

```text
Given an integer array nums where every element appears three times except for one, which appears exactly once.
Find the single element and return it.

You must implement a solution with a linear runtime complexity and use only constant extra space.

Example 1:
Input: nums = [2,2,3,2]
Output: 3

Example 2:
Input: nums = [0,1,0,1,0,1,99]
Output: 99

Constraints:
1 <= nums.length <= 3 * 10^4
-2^31 <= nums[i] <= 2^31 - 1
Each element in nums appears exactly three times except for one element which appears once.
```

</details>

<details><summary>C</summary>

```c
int singleNumber(int* nums, int numsSize) {
    int retVal = 0;

    int ones = 0;
    int twos = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        ones = ((ones ^ nums[i]) & (~twos));
        twos = ((twos ^ nums[i]) & (~ones));
    }
    retVal = ones;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int singleNumber(vector<int>& nums) {
        int retVal = 0;

        int ones = 0;
        int twos = 0;
        for (int num : nums) {
            ones = ((ones ^ num) & (~twos));
            twos = ((twos ^ num) & (~ones));
        }
        retVal = ones;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def singleNumber(self, nums: List[int]) -> int:
        retVal = 0

        ones = 0
        twos = 0
        for num in nums:
            ones = ones ^ num & ~twos
            twos = twos ^ num & ~ones
        retVal = ones

        return retVal
```

</details>

## [190. Reverse Bits](https://leetcode.com/problems/reverse-bits/)

- [Official](https://leetcode.cn/problems/reverse-bits/solutions/685436/dian-dao-er-jin-zhi-wei-by-leetcode-solu-yhxz/)

<details><summary>Description</summary>

```text
Reverse bits of a given 32 bits unsigned integer.

Note:
Note that in some languages, such as Java, there is no unsigned integer type.
In this case, both input and output will be given as a signed integer type.
They should not affect your implementation,
as the integer's internal binary representation is the same, whether it is signed or unsigned.
In Java, the compiler represents the signed integers using 2's complement notation.
Therefore, in Example 2 above,
the input represents the signed integer -3 and the output represents the signed integer -1073741825.

Example 1:
Input: n = 00000010100101000001111010011100
Output:    964176192 (00111001011110000010100101000000)
Explanation: The input binary string 00000010100101000001111010011100 represents the unsigned integer 43261596,
so return 964176192 which its binary representation is 00111001011110000010100101000000.

Example 2:
Input: n = 11111111111111111111111111111101
Output:   3221225471 (10111111111111111111111111111111)
Explanation: The input binary string 11111111111111111111111111111101 represents the unsigned integer 4294967293,
so return 3221225471 which its binary representation is 10111111111111111111111111111111.

Constraints:
The input must be a binary string of length 32

Follow up: If this function is called many times, how would you optimize it?
```

</details>

<details><summary>C</summary>

```c
uint32_t reverseBits(uint32_t n) {
    uint32_t retVal = 0;

#if (1)
    int i;
    for (i = 0; i < 32; ++i) {
        retVal = (retVal << 1) | (n & 0x1);
        n >>= 1;
    }
#else
#define M1 (0x55555555)
#define M2 (0x33333333)
#define M4 (0x0f0f0f0f)
#define M8 (0x00ff00ff)

    n = ((n >> 1) & M1) | ((n & M1) << 1);
    n = ((n >> 2) & M2) | ((n & M2) << 2);
    n = ((n >> 4) & M4) | ((n & M4) << 4);
    n = ((n >> 8) & M8) | ((n & M8) << 8);
    retVal = ((n >> 16) | (n << 16));
#endif

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t retVal = 0;

        for (int i = 0; i < 32; ++i) {
            retVal = (retVal << 1) | (n & 0x1);
            n >>= 1;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def reverseBits(self, n: int) -> int:
        retVal = 0

        for _ in range(32):
            retVal = (retVal << 1) | (n & 0x1)
            n >>= 1

        return retVal
```

</details>

## [191. Number of 1 Bits](https://leetcode.com/problems/number-of-1-bits/)

- [Official](https://leetcode.cn/problems/number-of-1-bits/solutions/672082/wei-1de-ge-shu-by-leetcode-solution-jnwf/)

<details><summary>Description</summary>

```text
Write a function that takes an unsigned integer and returns the number of '1' bits it has (also known as the Hamming weight).

Note:
Note that in some languages, such as Java, there is no unsigned integer type.
In this case, the input will be given as a signed integer type.
It should not affect your implementation, as the integer's internal binary representation is the same,
whether it is signed or unsigned.
In Java, the compiler represents the signed integers using 2's complement notation.
Therefore, in Example 3, the input represents the signed integer. -3.

Example 1:
Input: n = 00000000000000000000000000001011
Output: 3
Explanation: The input binary string 00000000000000000000000000001011 has a total of three '1' bits.

Example 2:
Input: n = 00000000000000000000000010000000
Output: 1
Explanation: The input binary string 00000000000000000000000010000000 has a total of one '1' bit.

Example 3:
Input: n = 11111111111111111111111111111101
Output: 31
Explanation: The input binary string 11111111111111111111111111111101 has a total of thirty one '1' bits.

Constraints:
The input must be a binary string of length 32.

Follow up: If this function is called many times, how would you optimize it?
```

</details>

<details><summary>C</summary>

```c
int hammingWeight(uint32_t n) {
    int retVal = 0;

    while (n) {
        if (n & 1) {
            ++retVal;
        }
        n >>= 1;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int retVal = 0;

        while (n > 0) {
            retVal += (n&1);
            n >>= 1;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def hammingWeight(self, n: int) -> int:
        return sum(((n&(1<<i)) != 0) for i in range(32))
```

</details>

## [201. Bitwise AND of Numbers Range](https://leetcode.com/problems/bitwise-and-of-numbers-range/)

- [Official](https://leetcode.cn/problems/bitwise-and-of-numbers-range/solutions/384938/shu-zi-fan-wei-an-wei-yu-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given two integers left and right that represent the range [left, right],
return the bitwise AND of all numbers in this range, inclusive.

Example 1:
Input: left = 5, right = 7
Output: 4

Example 2:
Input: left = 0, right = 0
Output: 0

Example 3:
Input: left = 1, right = 2147483647
Output: 0

Constraints:
0 <= left <= right <= 2^31 - 1
```

</details>

<details><summary>C</summary>

```c
int rangeBitwiseAnd(int left, int right) {
    int retVal = 0;

    int shift = 0;
    while (left < right) {
        left >>= 1;
        right >>= 1;
        shift += 1;
    }
    retVal = left << shift;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int rangeBitwiseAnd(int left, int right) {
        int retVal = 0;

        int shift = 0;
        while (left < right) {
            left >>= 1;
            right >>= 1;
            shift += 1;
        }
        retVal = left << shift;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def rangeBitwiseAnd(self, left: int, right: int) -> int:
        retVal = 0

        shift = 0
        while left < right:
            left >>= 1
            right >>= 1
            shift += 1
        retVal = left << shift

        return retVal
```

</details>

## [260. Single Number III](https://leetcode.com/problems/single-number-iii/)

- [Official](https://leetcode.cn/problems/single-number-iii/solutions/587516/zhi-chu-xian-yi-ci-de-shu-zi-iii-by-leet-4i8e/)

<details><summary>Description</summary>

```text
Given an integer array nums, in which exactly two elements appear only once
and all the other elements appear exactly twice.
Find the two elements that appear only once. You can return the answer in any order.

You must write an algorithm that runs in linear runtime complexity and uses only constant extra space.

Example 1:
Input: nums = [1,2,1,3,2,5]
Output: [3,5]
Explanation:  [5, 3] is also a valid answer.

Example 2:
Input: nums = [-1,0]
Output: [-1,0]

Example 3:
Input: nums = [0,1]
Output: [1,0]

Constraints:
2 <= nums.length <= 3 * 10^4
-2^31 <= nums[i] <= 2^31 - 1
Each integer in nums will appear twice, only two integers will appear once.
```

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *singleNumber(int *nums, int numsSize, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 2;
    pRetVal = (int *)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));

    int i;

    unsigned int xorSum = 0;
    for (i = 0; i < numsSize; ++i) {
        xorSum ^= nums[i];
    }
    unsigned int lsb = xorSum & (-xorSum);

    for (i = 0; i < numsSize; ++i) {
        pRetVal[((lsb & nums[i]) ? 1 : 0)] ^= nums[i];
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> singleNumber(vector<int>& nums) {
        vector<int> retVal(2, 0);

        unsigned int xorSum = 0;
        for (int num : nums) {
            xorSum ^= num;
        }
        unsigned int lsb = xorSum & (-xorSum);

        for (int num : nums) {
            retVal[((lsb & num) ? 1 : 0)] ^= num;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def singleNumber(self, nums: List[int]) -> List[int]:
        retVal = [0, 0]

        xorSum = 0
        for num in nums:
            xorSum ^= num
        lsb = xorSum & (-xorSum)

        for num in nums:
            idx = 0 if lsb & num == 0 else 1
            retVal[idx] ^= num

        return retVal
```

</details>

## [268. Missing Number](https://leetcode.com/problems/missing-number/)

- [Official](https://leetcode.cn/problems/missing-number/solutions/1085105/diu-shi-de-shu-zi-by-leetcode-solution-naow/)

<details><summary>Description</summary>

```text
Given an array nums containing n distinct numbers in the range [0, n],
return the only number in the range that is missing from the array.

Example 1:
Input: nums = [3,0,1]
Output: 2
Explanation: n = 3 since there are 3 numbers, so all numbers are in the range [0,3].
2 is the missing number in the range since it does not appear in nums.

Example 2:
Input: nums = [0,1]
Output: 2
Explanation: n = 2 since there are 2 numbers, so all numbers are in the range [0,2].
2 is the missing number in the range since it does not appear in nums.

Example 3:
Input: nums = [9,6,4,2,3,5,7,0,1]
Output: 8
Explanation: n = 9 since there are 9 numbers, so all numbers are in the range [0,9].
8 is the missing number in the range since it does not appear in nums.

Constraints:
n == nums.length
1 <= n <= 10^4
0 <= nums[i] <= n
All the numbers of nums are unique.


Follow up: Could you implement a solution using only O(1) extra space complexity and O(n) runtime complexity?
```

</details>

<details><summary>C</summary>

```c
#define METHOD_SUM (0)
#define METHOD_XOR (1)
int missingNumber(int* nums, int numsSize) {
#if (METHOD_SUM)
    int retVal = (numsSize * (numsSize + 1)) / 2;
#elif (METHOD_XOR)
    int retVal = numsSize;
#endif

    int i;
    for (i = 0; i < numsSize; ++i) {
#if (METHOD_SUM)
        retVal -= nums[i];
#elif (METHOD_XOR)
        retVal ^= i;
        retVal ^= nums[i];
#endif
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
#define METHOD_SUM (0)
#define METHOD_XOR (1)
    int missingNumber(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

#if (METHOD_SUM)
        retVal = (numsSize * (numsSize + 1)) / 2;
#elif (METHOD_XOR)
        retVal = numsSize;
#endif

        for (int i = 0; i < numsSize; ++i) {
#if (METHOD_SUM)
            retVal -= nums[i];
#elif (METHOD_XOR)
            retVal ^= i;
            retVal ^= nums[i];
#endif
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def missingNumber(self, nums: List[int]) -> int:
        retVal = 0

        numSize = len(nums)
        retVal = (1 + numSize) * numSize // 2
        for num in nums:
            retVal -= num

        return retVal
```

</details>

## [338. Counting Bits](https://leetcode.com/problems/counting-bits/)

- [Official](https://leetcode.cn/problems/counting-bits/solutions/627418/bi-te-wei-ji-shu-by-leetcode-solution-0t1i/)

<details><summary>Description</summary>

```text
Given an integer n, return an array ans of length n + 1 such that for each i (0 <= i <= n),
ans[i] is the number of 1's in the binary representation of i.

Example 1:
Input: n = 2
Output: [0,1,1]
Explanation:
0 --> 0
1 --> 1
2 --> 10

Example 2:
Input: n = 5
Output: [0,1,1,2,1,2]
Explanation:
0 --> 0
1 --> 1
2 --> 10
3 --> 11
4 --> 100
5 --> 101

Constraints:
0 <= n <= 10^5

Follow up:
- It is very easy to come up with a solution with a runtime of O(n log n).
  Can you do it in linear time O(n) and possibly in a single pass?
- Can you do it without using any built-in function (i.e., like __builtin_popcount in C++)?
```

<details><summary>Hint</summary>

```text
1. You should make use of what you have produced already.
2. Divide the numbers in ranges like [2-3], [4-7], [8-15] and so on. And try to generate new range from previous.
3. Or does the odd/even status of the number help you in calculating the number of 1s?
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countBits(int n, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = n + 1;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));

    int i;
    for (i = 1; i < (*returnSize); ++i) {
#if (1)  // O(n)
        /* f[i] = f[i/2] + i%2
         *  pRetVal[000] = 0
         *  pRetVal[001] = pRetVal[00] + (1%2) = 0 + 1 = 1
         *  pRetVal[010] = pRetVal[01] + (2%2) = 1 + 0 = 1
         *  pRetVal[011] = pRetVal[01] + (3%2) = 1 + 1 = 2
         *  pRetVal[100] = pRetVal[10] + (4%2) = 1 + 0 = 1
         *  pRetVal[101] = pRetVal[10] + (5%2) = 1 + 1 = 2
         *  pRetVal[110] = pRetVal[11] + (6%2) = 2 + 0 = 2
         *  pRetVal[111] = pRetVal[11] + (7%2) = 2 + 1 = 3
         */
        pRetVal[i] = pRetVal[i >> 1] + (i & 1);
#else  // O(n log n)
        unsigned int tmp = i;
        while (tmp) {
            if (tmp & 1) {
                pRetVal[i]++;
            }
            tmp >>= 1;
        }
#endif
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> countBits(int n) {
        vector<int> retVal(n + 1, 0);

        for (int i = 1; i < n + 1; ++i) {
#if (1)  // O(n)
            /* f[i] = f[i/2] + i%2
             *  retVal[000] = 0
             *  retVal[001] = retVal[00] + (1%2) = 0 + 1 = 1
             *  retVal[010] = retVal[01] + (2%2) = 1 + 0 = 1
             *  retVal[011] = retVal[01] + (3%2) = 1 + 1 = 2
             *  retVal[100] = retVal[10] + (4%2) = 1 + 0 = 1
             *  retVal[101] = retVal[10] + (5%2) = 1 + 1 = 2
             *  retVal[110] = retVal[11] + (6%2) = 2 + 0 = 2
             *  retVal[111] = retVal[11] + (7%2) = 2 + 1 = 3
             */
            retVal[i] = retVal[i >> 1] + (i & 1);
#else  // O(n log n)
            unsigned int tmp = i;
            while (tmp) {
                if (tmp & 1) {
                    retVal[i]++;
                }
                tmp >>= 1;
            }
#endif
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
        self.method = 1


    def countBits(self, n: int) -> List[int]:
        retVal = [0] * (n+1)

        for i in range(n+1):
            if self.method == 1:    # O(n)
                # /* f[i] = f[i/2] + i%2
                #  *  retVal[000] = 0
                #  *  retVal[001] = retVal[00] + (1%2) = 0 + 1 = 1
                #  *  retVal[010] = retVal[01] + (2%2) = 1 + 0 = 1
                #  *  retVal[011] = retVal[01] + (3%2) = 1 + 1 = 2
                #  *  retVal[100] = retVal[10] + (4%2) = 1 + 0 = 1
                #  *  retVal[101] = retVal[10] + (5%2) = 1 + 1 = 2
                #  *  retVal[110] = retVal[11] + (6%2) = 2 + 0 = 2
                #  *  retVal[111] = retVal[11] + (7%2) = 2 + 1 = 3
                #  */
                retVal[i] = retVal[i >> 1] + (i & 1)
            elif self.method == 2:  # O(n log n)
                tmp = i
                while tmp>0:
                    if (tmp & 1) == 1:
                        retVal[i] += 1
                    tmp >>= 1

        return retVal
```

</details>

## [371. Sum of Two Integers](https://leetcode.com/problems/sum-of-two-integers/)

<details><summary>Description</summary>

```text
Given two integers a and b, return the sum of the two integers without using the operators + and -.

Example 1:
Input: a = 1, b = 2
Output: 3

Example 2:
Input: a = 2, b = 3
Output: 5

Constraints:
-1000 <= a, b <= 1000
```

</details>

<details><summary>C</summary>

```c
int getSum(int a, int b){
    int retVal = 0;

    unsigned int carry;
    // iterate till there is no carry
    while (b != 0)
    {
        // carry now contains common set bits of a and b
        carry = a & b;

        // sum of bits of a and b where at least one of the bits is not set
        a = a ^ b;

        // carry is shifted by one so that adding it to a gives the required sum
        b = carry << 1;
    }
    retVal = a;

    return retVal;
}
```

</details>

## [389. Find the Difference](https://leetcode.com/problems/find-the-difference/)

- [Official](https://leetcode.cn/problems/find-the-difference/solutions/525705/zhao-bu-tong-by-leetcode-solution-mtqf/)

<details><summary>Description</summary>

```text
You are given two strings s and t.

String t is generated by random shuffling string s and then add one more letter at a random position.

Return the letter that was added to t.

Example 1:
Input: s = "abcd", t = "abcde"
Output: "e"
Explanation: 'e' is the letter that was added.

Example 2:
Input: s = "", t = "y"
Output: "y"

Constraints:
0 <= s.length <= 1000
t.length == s.length + 1
s and t consist of lowercase English letters.
```

</details>

<details><summary>C</summary>

```c
char findTheDifference(char* s, char* t) {
    char retVal = 0;

    while (*s) {
        retVal ^= (*s);
        ++s;
    }

    while (*t) {
        retVal ^= (*t);
        ++t;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    char findTheDifference(string s, string t) {
        char retVal = 0;

        for (char c : s) {
            retVal ^= c;
        }

        for (char c : t) {
            retVal ^= c;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def findTheDifference(self, s: str, t: str) -> str:
        retVal = 0

        for c in s:
            retVal ^= ord(c)

        for c in t:
            retVal ^= ord(c)

        retVal = chr(retVal)

        return retVal
```

</details>

## [405. Convert a Number to Hexadecimal](https://leetcode.com/problems/convert-a-number-to-hexadecimal/)

<details><summary>Description</summary>

```text
Given an integer num, return a string representing its hexadecimal representation.
For negative integers, two’s complement method is used.

All the letters in the answer string should be lowercase characters,
and there should not be any leading zeros in the answer except for the zero itself.

Note: You are not allowed to use any built-in library method to directly solve this problem.

Example 1:
Input: num = 26
Output: "1a"

Example 2:
Input: num = -1
Output: "ffffffff"

Constraints:
-2^31 <= num <= 2^31 - 1
```

</details>

<details><summary>C</summary>

```c
char * toHex(int num){
#define MAX_SIZE    9
    char* pRetVal = (char*)malloc(MAX_SIZE*sizeof(char));
    if (pRetVal == NULL)
    {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, MAX_SIZE*sizeof(char));

#if 1
    if (num == 0)
    {
        pRetVal[0] = '0';
        return pRetVal;
    }

    int i;
    unsigned n = num;
    while (n > 0)
    {
        // printf("%d: %x\n", n&0xf, n&0xf);
        for (i=(MAX_SIZE-1); i>=1; --i)
        {
            pRetVal[i] = pRetVal[i-1];
        }
        pRetVal[0] = ((n&0xf)<10)?((n&0xf)+48):((n&0xf)-10+97);
        n >>= 4;
    }
#else
    snprintf(pRetVal, MAX_SIZE*sizeof(char), "%x", num);
    printf("%s\n", pRetVal);
#endif

    return pRetVal;
}
```

</details>

## [461. Hamming Distance](https://leetcode.com/problems/hamming-distance/)

<details><summary>Description</summary>

```text
The Hamming distance between two integers is the number of positions at which the corresponding bits are different.

Given two integers x and y, return the Hamming distance between them.

Example 1:
Input: x = 1, y = 4
Output: 2
Explanation:
1   (0 0 0 1)
4   (0 1 0 0)
       ↑   ↑
The above arrows point to positions where the corresponding bits are different.

Example 2:
Input: x = 3, y = 1
Output: 1

Constraints:
0 <= x, y <= 2^31 - 1
```

</details>

<details><summary>C</summary>

```c
int hammingDistance(int x, int y){
    int retVal = 0;

    int n = x^y;
    while (n > 0)
    {
        retVal += (n & 0x1);
        n >>= 1;
    }

    return retVal;
}
```

</details>

## [476. Number Complement](https://leetcode.com/problems/number-complement/)

- [Official](https://leetcode.cn/problems/number-complement/solutions/1050060/shu-zi-de-bu-shu-by-leetcode-solution-xtn8/)

<details><summary>Description</summary>

```text
The complement of an integer is the integer you get when you flip all the 0's to 1's
and all the 1's to 0's in its binary representation.

For example, The integer 5 is "101" in binary and its complement is "010" which is the integer 2.
Given an integer num, return its complement.

Example 1:
Input: num = 5
Output: 2
Explanation: The binary representation of 5 is 101 (no leading zero bits),
and its complement is 010. So you need to output 2.

Example 2:
Input: num = 1
Output: 0
Explanation: The binary representation of 1 is 1 (no leading zero bits),
and its complement is 0. So you need to output 0.

Constraints:
1 <= num < 2^31

Note: This question is the same as 1009: https://leetcode.com/problems/complement-of-base-10-integer/
```

</details>

<details><summary>C</summary>

```c
int findComplement(int num) {
    int retVal = num;

    int i = 31;
    while ((retVal & ((uint32_t)1 << i)) == 0) {
        i--;
    }

    while (i >= 0) {
        retVal ^= (1 << i--);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int findComplement(int num) {
        int retVal = num;

        int i = 31;
        while ((retVal & ((uint32_t)1 << i)) == 0) {
            i--;
        }

        while (i >= 0) {
            retVal ^= (1 << i--);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def findComplement(self, num: int) -> int:
        retVal = num

        i = 31
        while retVal & (1 << i) == 0:
            i -= 1

        while i >= 0:
            retVal ^= (1 << i)
            i -= 1

        return retVal
```

</details>

## [477. Total Hamming Distance](https://leetcode.com/problems/total-hamming-distance/)

<details><summary>Description</summary>

```text
The Hamming distance between two integers is the number of positions at which the corresponding bits are different.

Given an integer array nums, return the sum of Hamming distances between all the pairs of the integers in nums.

Example 1:
Input: nums = [4,14,2]
Output: 6
Explanation: In binary representation, the 4 is 0100, 14 is 1110, and 2 is 0010 (just
showing the four bits relevant in this case).
The answer will be:
HammingDistance(4, 14) + HammingDistance(4, 2) + HammingDistance(14, 2) = 2 + 2 + 2 = 6.

Example 2:
Input: nums = [4,14,4]
Output: 4

Constraints:
1 <= nums.length <= 10^4
0 <= nums[i] <= 10^9
The answer for the given input will fit in a 32-bit integer.
```

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int totalHammingDistance(int* nums, int numsSize) {
    int retVal = 0;

#if 1
    int countOne;
    int countZero;
    int i, j;
    for (i = 0; i < 32; ++i) {
        countZero = 0;
        countOne = 0;
        for (j = 0; j < numsSize; ++j) {
            if ((nums[j] & ((unsigned int)1 << i)) != 0) {
                ++countOne;
            } else {
                ++countZero;
            }
        }
        retVal += (countOne * countZero);
    }
#else
    qsort(nums, numsSize, sizeof(int), compareInteger);

    int xorValue;
    int i, j;
    for (i = 0; i < numsSize; ++i) {
        for (j = (i + 1); j < numsSize; ++j) {
            if (nums[i] == nums[j]) {
                continue;
            }
            xorValue = nums[i] ^ nums[j];
            while (xorValue > 0) {
                retVal += (xorValue & 0x1);
                xorValue >>= 1;
            }
        }
    }
#endif

    return retVal;
}
```

</details>

## [693. Binary Number with Alternating Bits](https://leetcode.com/problems/binary-number-with-alternating-bits/)

<details><summary>Description</summary>

```text
Given a positive integer, check whether it has alternating bits:
namely, if two adjacent bits will always have different values.

Example 1:
Input: n = 5
Output: true
Explanation: The binary representation of 5 is: 101

Example 2:
Input: n = 7
Output: false
Explanation: The binary representation of 7 is: 111.

Example 3:
Input: n = 11
Output: false
Explanation: The binary representation of 11 is: 1011.

Constraints:
1 <= n <= 2^31 - 1
```

</details>

<details><summary>C</summary>

```c
bool hasAlternatingBits(int n){
    bool retVal = false;

#if 1
    /* right shift 2 bit will become all 2^n
     *    000101010
     *  ^ 000001010
     *  = 000100000
     */
    n ^= (n >> 2);
    unsigned int m = (unsigned int)(n) - 1;
    if ((n & m) == 0)
    {
        retVal = true;
    }
#else
    /* right shift 1 bit will become 2^n-1
     *    000101010
     *  ^ 000010101
     *  = 000111111
     */
    n ^= (n >> 1);
    unsigned int m = (unsigned int)(n) + 1;
    if ((n & m) == 0)
    {
        retVal = true;
    }
#endif

    return retVal;
}
```

</details>

## [762. Prime Number of Set Bits in Binary Representation](https://leetcode.com/problems/prime-number-of-set-bits-in-binary-representation/)  1383

<details><summary>Description</summary>

```text
Given two integers left and right, return the count of numbers
in the inclusive range [left, right] having a prime number of set bits in their binary representation.

Recall that the number of set bits an integer has is the number of 1's present when written in binary.
- For example, 21 written in binary is 10101, which has 3 set bits.

Example 1:
Input: left = 6, right = 10
Output: 4
Explanation:
6  -> 110 (2 set bits, 2 is prime)
7  -> 111 (3 set bits, 3 is prime)
8  -> 1000 (1 set bit, 1 is not prime)
9  -> 1001 (2 set bits, 2 is prime)
10 -> 1010 (2 set bits, 2 is prime)
4 numbers have a prime number of set bits.

Example 2:
Input: left = 10, right = 15
Output: 5
Explanation:
10 -> 1010 (2 set bits, 2 is prime)
11 -> 1011 (3 set bits, 3 is prime)
12 -> 1100 (2 set bits, 2 is prime)
13 -> 1101 (3 set bits, 3 is prime)
14 -> 1110 (3 set bits, 3 is prime)
15 -> 1111 (4 set bits, 4 is not prime)
5 numbers have a prime number of set bits.

Constraints:
1 <= left <= right <= 10^6
0 <= right - left <= 10^4
```

</details>

<details><summary>C</summary>

```c
int isPrime(int num)
{
    int retVal = 0;

    if (num <= 1)
    {
        return retVal;
    }

    if ((num > 2) && (num % 2 == 0))
    {
        return retVal;
    }

    int i;
    for(i=3; i<num/2; i+=2)
    {
        if (num % i == 0)
        {
            return retVal;
        }
    }
    retVal = 1;

    return retVal;
}

int countBits(int n)
{
    int retVal = 0;

    while (n)
    {
        if (n & 1)
        {
            retVal++;
        }
        n >>= 1;
    }

    return retVal;
}

int countPrimeSetBits(int left, int right){
    int retVal = 0;

    int setBits;
    int i;
    for (i=left; i<=right; ++i)
    {
        setBits = countBits(i);
        retVal += isPrime(setBits);
    }

    return retVal;
}
```

</details>

## [779. K-th Symbol in Grammar](https://leetcode.com/problems/k-th-symbol-in-grammar/)  1571

- [Official](https://leetcode.com/problems/k-th-symbol-in-grammar/editorial/)
- [Official](https://leetcode.cn/problems/k-th-symbol-in-grammar/solutions/1903508/di-kge-yu-fa-fu-hao-by-leetcode-solution-zgwd/)

<details><summary>Description</summary>

```text
We build a table of n rows (1-indexed).
We start by writing 0 in the 1st row.
Now in every subsequent row,
we look at the previous row and replace each occurrence of 0 with 01, and each occurrence of 1 with 10.
- For example, for n = 3, the 1st row is 0, the 2nd row is 01, and the 3rd row is 0110.

Given two integer n and k, return the kth (1-indexed) symbol in the nth row of a table of n rows.

Example 1:
Input: n = 1, k = 1
Output: 0
Explanation: row 1: 0

Example 2:
Input: n = 2, k = 1
Output: 0
Explanation:
row 1: 0
row 2: 01

Example 3:
Input: n = 2, k = 2
Output: 1
Explanation:
row 1: 0
row 2: 01

Constraints:
1 <= n <= 30
1 <= k <= 2^n - 1
```

<details><summary>Hint</summary>

```text
1. Try to represent the current (N, K) in terms of some (N-1, prevK). What is prevK ?
```

</details>

</details>

<details><summary>C</summary>

```c
int kthGrammar(int n, int k) {
    int retVal = 0;

#if (0)  // Recursion
    /*
     *  0
     *  0 1
     *  0 1 1 0
     *  0 1 1 0 1 0 0 1
     *  0 1 1 0 1 0 0 1 1 0 0 1 0 1 1 0
     */
    if (k == 1) {
        return retVal;
    }
    if (k > (1 << (n - 2))) {
        retVal = 1 ^ (kthGrammar(n - 1, k - (1 << (n - 2))));
        return retVal;
    }
    retVal = kthGrammar(n - 1, k);
#else  // Bit Manipulation: 0->01, 1-> 10.
    /*
     *  +-------------------------------+
     *  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
     *  +-------------------------------+
     *  | 0 | 1 | 1 | 0 | 1 | 0 | 0 | 1 |
     *  +-------------------------------+
     *  | 0 | 1 |   |   |   |   |   |   |
     *  |   | 1 | 1 | 0 |   |   |   |   |
     *  |   |   | 1 |   | 1 | 0 |   |   |
     *  |   |   |   | 0 |   |   | 0 | 1 |
     *  +-------------------------------+
     */
    // retVal = __builtin_popcount(k - 1) & 1;
    k--;
    while (k > 0) {
        k &= (k - 1);
        retVal ^= 1;
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
    int kthGrammar(int n, int k) {
        int retVal = 0;

#if (0)  // Recursion
        /*
         *  0
         *  0 1
         *  0 1 1 0
         *  0 1 1 0 1 0 0 1
         *  0 1 1 0 1 0 0 1 1 0 0 1 0 1 1 0
         */
        if (k == 1) {
            return retVal;
        }
        if (k > (1 << (n - 2))) {
            retVal = 1 ^ (kthGrammar(n - 1, k - (1 << (n - 2))));
            return retVal;
        }
        retVal = kthGrammar(n - 1, k);
#else  // Bit Manipulation: 0->01, 1-> 10.
        /*
         *  +-------------------------------+
         *  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
         *  +-------------------------------+
         *  | 0 | 1 | 1 | 0 | 1 | 0 | 0 | 1 |
         *  +-------------------------------+
         *  | 0 | 1 |   |   |   |   |   |   |
         *  |   | 1 | 1 | 0 |   |   |   |   |
         *  |   |   | 1 |   | 1 | 0 |   |   |
         *  |   |   |   | 0 |   |   | 0 | 1 |
         *  +-------------------------------+
         */
        // retVal = __builtin_popcount(k - 1) & 1;
        k--;
        while (k > 0) {
            k &= (k - 1);
            retVal ^= 1;
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
    def kthGrammar(self, n: int, k: int) -> int:
        retVal = 0

        if 1 == 0:  # Recursion
            # 0
            # 0 1
            # 0 1 1 0
            # 0 1 1 0 1 0 0 1
            # 0 1 1 0 1 0 0 1 1 0 0 1 0 1 1 0
            if k == 1:
                return retVal
            if k > (1 << (n - 2)):
                retVal = 1 ^ self.kthGrammar(n - 1, k - (1 << (n - 2)))
                return retVal
            retVal = self.kthGrammar(n - 1, k)
        else:   # Bit Manipulation: 0->01, 1-> 10.
            # +-------------------------------+
            # | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
            # +-------------------------------+
            # | 0 | 1 | 1 | 0 | 1 | 0 | 0 | 1 |
            # +-------------------------------+
            # | 0 | 1 |   |   |   |   |   |   |
            # |   | 1 | 1 | 0 |   |   |   |   |
            # |   |   | 1 |   | 1 | 0 |   |   |
            # |   |   |   | 0 |   |   | 0 | 1 |
            # +-------------------------------+
            # retVal = (k - 1).bit_count() & 1
            k -= 1
            while k:
                k &= (k - 1)
                retVal ^= 1

        return retVal
```

</details>

## [898. Bitwise ORs of Subarrays](https://leetcode.com/problems/bitwise-ors-of-subarrays/)  2133

- [Official](https://leetcode.com/problems/bitwise-ors-of-subarrays/editorial/)
- [Official](https://leetcode.cn/problems/bitwise-ors-of-subarrays/solutions/18772/zi-shu-zu-an-wei-huo-cao-zuo-by-leetcode/)

<details><summary>Description</summary>

```text
Given an integer array arr, return the number of distinct bitwise ORs of all the non-empty subarrays of arr.

The bitwise OR of a subarray is the bitwise OR of each integer in the subarray.
The bitwise OR of a subarray of one integer is that integer.

A subarray is a contiguous non-empty sequence of elements within an array.

Example 1:
Input: arr = [0]
Output: 1
Explanation: There is only one possible result: 0.

Example 2:
Input: arr = [1,1,2]
Output: 3
Explanation: The possible subarrays are [1], [1], [2], [1, 1], [1, 2], [1, 1, 2].
These yield the results 1, 1, 2, 1, 3, 3.
There are 3 unique values, so the answer is 3.

Example 3:
Input: arr = [1,2,4]
Output: 6
Explanation: The possible results are 1, 2, 3, 4, 6, and 7.

Constraints:
1 <= arr.length <= 5 * 10^4
0 <= arr[i] <= 10^9
```

</details>

<details><summary>C</summary>

```c
struct hashTable {
    int key;
    // int value;
    UT_hash_handle hh;
};
bool addKey(struct hashTable **pObj, int key) {
    bool retVal = true;

    struct hashTable *pTemp = NULL;
    HASH_FIND_INT(*pObj, &key, pTemp);
    if (pTemp != NULL) {
        return retVal;
    }

    pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
    if (pTemp == NULL) {
        perror("malloc");
        retVal = false;
    } else {
        pTemp->key = key;
        HASH_ADD_INT(*pObj, key, pTemp);
    }

    return retVal;
}
void freeAll(struct hashTable *pFree) {
    struct hashTable *current;
    struct hashTable *tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d\n", pFree->key);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int subarrayBitwiseORs(int *arr, int arrSize) {
    int retVal = 0;

    if (arrSize < 2) {
        return arrSize;
    }

    struct hashTable *result = NULL;
    int key;
    bool isValid = true;
    for (int i = 0; i < arrSize; i++) {
        key = arr[i];
        isValid = addKey(&result, key);
        if (isValid == false) {
            goto exit;
        }

        for (int j = i - 1; j >= 0; j--) {
            if ((arr[j] & arr[i]) == arr[i]) {
                break;
            }
            arr[j] |= arr[i];

            key = arr[j];
            isValid = addKey(&result, key);
            if (isValid == false) {
                goto exit;
            }
        }
    }
    retVal = HASH_COUNT(result);

exit:
    freeAll(result);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int subarrayBitwiseORs(vector<int>& arr) {
        int retVal = 0;

        unordered_set<int> result;
        unordered_set<int> current;
        current.insert(0);
        for (int x : arr) {
            unordered_set<int> current2;
            for (int y : current) {
                current2.insert(x | y);
            }
            current2.insert(x);
            current = current2;
            result.insert(current.begin(), current.end());
        }
        retVal = result.size();

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def subarrayBitwiseORs(self, arr: List[int]) -> int:
        retVal = 0

        result = set()
        current = {0}
        for x in arr:
            current = {x | y for y in current} | {x}
            result |= current
        retVal = len(result)

        return retVal
```

</details>

## [995. Minimum Number of K Consecutive Bit Flips](https://leetcode.com/problems/minimum-number-of-k-consecutive-bit-flips/)  1835

- [Official](https://leetcode.com/problems/minimum-number-of-k-consecutive-bit-flips/editorial/)
- [Official](https://leetcode.cn/problems/minimum-number-of-k-consecutive-bit-flips/solutions/607416/k-lian-xu-wei-de-zui-xiao-fan-zhuan-ci-s-bikk/)

<details><summary>Description</summary>

```text
You are given a binary array nums and an integer k.

A k-bit flip is choosing a subarray of length k from nums and
simultaneously changing every 0 in the subarray to 1, and every 1 in the subarray to 0.

Return the minimum number of k-bit flips required so that there is no 0 in the array. If it is not possible, return -1.

A subarray is a contiguous part of an array.

Example 1:
Input: nums = [0,1,0], k = 1
Output: 2
Explanation: Flip nums[0], then flip nums[2].

Example 2:
Input: nums = [1,1,0], k = 2
Output: -1
Explanation: No matter how we flip subarrays of size 2, we cannot make the array become [1,1,1].

Example 3:
Input: nums = [0,0,0,1,0,1,1,0], k = 3
Output: 3
Explanation:
Flip nums[0],nums[1],nums[2]: nums becomes [1,1,1,1,0,1,1,0]
Flip nums[4],nums[5],nums[6]: nums becomes [1,1,1,1,1,0,0,0]
Flip nums[5],nums[6],nums[7]: nums becomes [1,1,1,1,1,1,1,1]


Constraints:
1 <= nums.length <= 10^5
1 <= k <= nums.length
```

</details>

<details><summary>C</summary>

```c
int minKBitFlips(int* nums, int numsSize, int k) {
    int retVal = 0;

    int revCnt = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if ((i >= k) && (nums[i - k] > 1)) {
            revCnt ^= 1;
            nums[i - k] -= 2;
        }

        if (nums[i] == revCnt) {
            if (i + k > numsSize) {
                retVal = -1;
                break;
            }
            ++retVal;
            revCnt ^= 1;
            nums[i] += 2;
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
    int minKBitFlips(vector<int>& nums, int k) {
        int retVal = 0;

        int numsSize = nums.size();
        int revCnt = 0;
        for (int i = 0; i < numsSize; ++i) {
            if ((i >= k) && (nums[i - k] > 1)) {
                revCnt ^= 1;
                nums[i - k] -= 2;
            }

            if (nums[i] == revCnt) {
                if (i + k > numsSize) {
                    retVal = -1;
                    break;
                }
                ++retVal;
                revCnt ^= 1;
                nums[i] += 2;
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
    def minKBitFlips(self, nums: List[int], k: int) -> int:
        retVal = 0

        numsSize = len(nums)
        revCnt = 0
        for i in range(numsSize):
            if (i >= k) and (nums[i - k] > 1):
                revCnt ^= 1
                nums[i - k] -= 2

            if nums[i] == revCnt:
                if i + k > numsSize:
                    retVal = -1
                    break
                retVal += 1
                revCnt ^= 1
                nums[i] += 2

        return retVal
```

</details>

## [1009. Complement of Base 10 Integer](https://leetcode.com/problems/complement-of-base-10-integer/)  1234

- [Official](https://leetcode.cn/problems/complement-of-base-10-integer/solutions/1050059/shi-jin-zhi-zheng-shu-de-fan-ma-by-leetc-vofe/)

<details><summary>Description</summary>

```text
The complement of an integer is the integer you get
when you flip all the 0's to 1's and all the 1's to 0's in its binary representation.
- For example, The integer 5 is "101" in binary and its complement is "010" which is the integer 2.

Given an integer n, return its complement.

Example 1:
Input: n = 5
Output: 2
Explanation: 5 is "101" in binary, with complement "010" in binary, which is 2 in base-10.

Example 2:
Input: n = 7
Output: 0
Explanation: 7 is "111" in binary, with complement "000" in binary, which is 0 in base-10.

Example 3:
Input: n = 10
Output: 5
Explanation: 10 is "1010" in binary, with complement "0101" in binary, which is 5 in base-10.

Constraints:
0 <= n < 10^9

Note: This question is the same as 476: https://leetcode.com/problems/number-complement/
```

<details><summary>Hint</summary>

```text
1. A binary number plus its complement will equal 111....111 in binary. Also, N = 0 is a corner case.
```

</details>

</details>

<details><summary>C</summary>

```c
int bitwiseComplement(int n) {
    int retVal = n;

    // 0 <= n < 10^9
    if (n == 0) {
        retVal = 1;
        return retVal;
    }

    int i = 31;
    while ((retVal & ((uint32_t)1 << i)) == 0) {
        i--;
    }

    while (i >= 0) {
        retVal ^= (1 << i--);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int bitwiseComplement(int n) {
        int retVal = n;

        // 0 <= n < 10^9
        if (n == 0) {
            retVal = 1;
            return retVal;
        }

        int i = 31;
        while ((retVal & ((uint32_t)1 << i)) == 0) {
            i--;
        }

        while (i >= 0) {
            retVal ^= (1 << i--);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def bitwiseComplement(self, n: int) -> int:
        retVal = n

        # 0 <= n < 10^9
        if n == 0:
            retVal = 1
            return retVal

        i = 31
        while retVal & (1 << i) == 0:
            i -= 1

        while i >= 0:
            retVal ^= (1 << i)
            i -= 1

        return retVal
```

</details>

## [1318. Minimum Flips to Make a OR b Equal to c](https://leetcode.com/problems/minimum-flips-to-make-a-or-b-equal-to-c/)  1382

- [Official](https://leetcode.com/problems/minimum-flips-to-make-a-or-b-equal-to-c/editorial/)
- [Official](https://leetcode.cn/problems/minimum-flips-to-make-a-or-b-equal-to-c/solutions/101777/huo-yun-suan-de-zui-xiao-fan-zhuan-ci-shu-by-lee-2/)

<details><summary>Description</summary>

```text
Given 3 positives numbers a, b and c.
Return the minimum flips required in some bits of a and b to make ( a OR b == c ). (bitwise OR operation).
Flip operation consists of change any single bit 1 to 0 or change the bit 0 to 1 in their binary representation.

Example 1:
Input: a = 2, b = 6, c = 5
Output: 3
Explanation: After flips a = 1 , b = 4 , c = 5 such that (a OR b == c)

Example 2:
Input: a = 4, b = 2, c = 7
Output: 1

Example 3:
Input: a = 1, b = 2, c = 3
Output: 0

Constraints:
1 <= a <= 10^9
1 <= b <= 10^9
1 <= c <= 10^9
```

<details><summary>Hint</summary>

```text
1. Check the bits one by one whether they need to be flipped.
```

</details>

</details>

<details><summary>C</summary>

```c
int minFlips(int a, int b, int c) {
    int retVal = 0;

    while ((a > 0) || (b > 0) || (c > 0)) {
        if (c & 1) {
            retVal += ((~((a & 1) | (b & 1))) & 1);
        } else {
            retVal += ((a & 1) + (b & 1));
        }

        a >>= 1;
        b >>= 1;
        c >>= 1;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minFlips(int a, int b, int c) {
        int retVal = 0;

        while ((a > 0) || (b > 0) || (c > 0)) {
            if (c & 1) {
                retVal += ((~((a & 1) | (b & 1))) & 1);
            } else {
                retVal += ((a & 1) + (b & 1));
            }

            a >>= 1;
            b >>= 1;
            c >>= 1;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minFlips(self, a: int, b: int, c: int) -> int:
        retVal = 0

        while ((a > 0) or (b > 0) or (c > 0)):
            if c & 1:
                retVal += ((~((a & 1) | (b & 1))) & 1)
            else:
                retVal += ((a & 1) + (b & 1))

            a >>= 1
            b >>= 1
            c >>= 1

        return retVal
```

</details>

## [1342. Number of Steps to Reduce a Number to Zero](https://leetcode.com/problems/number-of-steps-to-reduce-a-number-to-zero/)  1163

<details><summary>Description</summary>

```text
Given an integer num, return the number of steps to reduce it to zero.

In one step, if the current number is even, you have to divide it by 2, otherwise, you have to subtract 1 from it.

Example 1:
Input: num = 14
Output: 6
Explanation:
Step 1) 14 is even; divide by 2 and obtain 7.
Step 2) 7 is odd; subtract 1 and obtain 6.
Step 3) 6 is even; divide by 2 and obtain 3.
Step 4) 3 is odd; subtract 1 and obtain 2.
Step 5) 2 is even; divide by 2 and obtain 1.
Step 6) 1 is odd; subtract 1 and obtain 0.

Example 2:
Input: num = 8
Output: 4
Explanation:
Step 1) 8 is even; divide by 2 and obtain 4.
Step 2) 4 is even; divide by 2 and obtain 2.
Step 3) 2 is even; divide by 2 and obtain 1.
Step 4) 1 is odd; subtract 1 and obtain 0.

Example 3:
Input: num = 123
Output: 12

Constraints:
0 <= num <= 10^6
```

</details>

<details><summary>C</summary>

```c
int numberOfSteps(int num){
    int retVal = 0;

    while (num > 0)
    {
        num = ((num%2)==0)?(num>>1):(num-1);
        ++retVal;
    }

    return retVal;
}
```

</details>

## [1356. Sort Integers by The Number of 1 Bits](https://leetcode.com/problems/sort-integers-by-the-number-of-1-bits/)  1257

- [Official](https://leetcode.com/problems/sort-integers-by-the-number-of-1-bits/editorial/)
- [Official](https://leetcode.cn/problems/sort-integers-by-the-number-of-1-bits/solutions/109168/gen-ju-shu-zi-er-jin-zhi-xia-1-de-shu-mu-pai-xu-by/)

<details><summary>Description</summary>

```text
You are given an integer array arr.
Sort the integers in the array in ascending order by the number of 1's in their binary representation
and in case of two or more integers have the same number of 1's you have to sort them in ascending order.

Return the array after sorting it.

Example 1:
Input: arr = [0,1,2,3,4,5,6,7,8]
Output: [0,1,2,4,8,3,5,6,7]
Explantion: [0] is the only integer with 0 bits.
[1,2,4,8] all have 1 bit.
[3,5,6] have 2 bits.
[7] has 3 bits.
The sorted array by bits is [0,1,2,4,8,3,5,6,7]

Example 2:
Input: arr = [1024,512,256,128,64,32,16,8,4,2,1]
Output: [1,2,4,8,16,32,64,128,256,512,1024]
Explantion: All integers have 1 bit in the binary representation, you should just sort them in ascending order.

Constraints:
1 <= arr.length <= 500
0 <= arr[i] <= 10^4
```

<details><summary>Hint</summary>

```text
1. Simulate the problem. Count the number of 1's in the binary representation of each integer.
2. Sort by the number of 1's ascending and by the value in case of tie.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareTheNumberOfBits(const void* n1, const void* n2) {
    if (__builtin_popcount(*(int*)n1) > __builtin_popcount(*(int*)n2)) {
        return 1;
    } else if (__builtin_popcount(*(int*)n1) < __builtin_popcount(*(int*)n2)) {
        return 0;
    } else {
        return (*(int*)n1 - *(int*)n2);
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortByBits(int* arr, int arrSize, int* returnSize) {
    int* pRetVal = NULL;
    (*returnSize) = arrSize;

    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));
    memcpy(pRetVal, arr, ((*returnSize) * sizeof(int)));

    qsort(pRetVal, (*returnSize), sizeof(int), compareTheNumberOfBits);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> sortByBits(vector<int>& arr) {
        vector<int> retVal;

        retVal = arr;
        sort(retVal.begin(), retVal.end(), [&](const int& a, const int& b) {
            if (__builtin_popcount(a) == __builtin_popcount(b)) {
                return a < b;
            }

            return __builtin_popcount(a) < __builtin_popcount(b);
        });

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def sortByBits(self, arr: List[int]) -> List[int]:
        retVal = []

        retVal = arr
        retVal.sort(key=lambda num: (num.bit_count(), num))

        return retVal
```

</details>

## [1404. Number of Steps to Reduce a Number in Binary Representation to One](https://leetcode.com/problems/number-of-steps-to-reduce-a-number-in-binary-representation-to-one/)  1396

- [Official](https://leetcode.com/problems/number-of-steps-to-reduce-a-number-in-binary-representation-to-one/editorial/)
- [Official](https://leetcode.cn/problems/number-of-steps-to-reduce-a-number-in-binary-representation-to-one/solutions/202251/jiang-er-jin-zhi-biao-shi-jian-dao-1-de-bu-zou-shu/)

<details><summary>Description</summary>

```text
Given the binary representation of an integer as a string s,
return the number of steps to reduce it to 1 under the following rules:
- If the current number is even, you have to divide it by 2.
- If the current number is odd, you have to add 1 to it.

It is guaranteed that you can always reach one for all test cases.

Example 1:
Input: s = "1101"
Output: 6
Explanation: "1101" corressponds to number 13 in their decimal representation.
Step 1) 13 is odd, add 1 and obtain 14.
Step 2) 14 is even, divide by 2 and obtain 7.
Step 3) 7 is odd, add 1 and obtain 8.
Step 4) 8 is even, divide by 2 and obtain 4.
Step 5) 4 is even, divide by 2 and obtain 2.
Step 6) 2 is even, divide by 2 and obtain 1.

Example 2:
Input: s = "10"
Output: 1
Explanation: "10" corressponds to number 2 in their decimal representation.
Step 1) 2 is even, divide by 2 and obtain 1.

Example 3:
Input: s = "1"
Output: 0

Constraints:
1 <= s.length <= 500
s consists of characters '0' or '1'
s[0] == '1'
```

<details><summary>Hint</summary>

```text
1. Read the string from right to left, if the string ends in '0' then the number is even otherwise it is odd.
2. Simulate the steps described in the binary string.
```

</details>

</details>

<details><summary>C</summary>

```c
int numSteps(char* s) {
    int retVal = 0;

    int sSize = strlen(s);
    int operations = 0;
    int carry = 0;
    int i;
    for (i = sSize - 1; i > 0; i--) {
        if (((s[i] - '0') + carry) % 2) {
            operations += 2;
            carry = 1;
        } else {
            operations++;
        }
    }
    retVal = operations + carry;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int numSteps(string s) {
        int retVal = 0;

        int sSize = s.size();
        int operations = 0;
        int carry = 0;
        for (int i = sSize - 1; i > 0; i--) {
            if (((s[i] - '0') + carry) % 2) {
                operations += 2;
                carry = 1;
            } else {
                operations++;
            }
        }
        retVal = operations + carry;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def numSteps(self, s: str) -> int:
        retVal = 0

        num = int(s, 2)
        while num > 1:
            if num % 2 == 0:
                num >>= 1
            else:
                num += 1
            retVal += 1

        return retVal
```

</details>

## [1611. Minimum One Bit Operations to Make Integers Zero](https://leetcode.com/problems/minimum-one-bit-operations-to-make-integers-zero/)  2345

- [Official](https://leetcode.com/problems/minimum-one-bit-operations-to-make-integers-zero/editorial/)
- [Official](https://leetcode.cn/problems/minimum-one-bit-operations-to-make-integers-zero/solutions/2477522/shi-zheng-shu-bian-wei-0-de-zui-shao-cao-gxmc/)

<details><summary>Description</summary>

```text
Given an integer n, you must transform it into 0 using the following operations any number of times:
- Change the rightmost (0th) bit in the binary representation of n.
- Change the ith bit in the binary representation of n
  if the (i-1)th bit is set to 1 and the (i-2)th through 0th bits are set to 0.

Return the minimum number of operations to transform n into 0.

Example 1:
Input: n = 3
Output: 2
Explanation: The binary representation of 3 is "11".
"11" -> "01" with the 2nd operation since the 0th bit is 1.
"01" -> "00" with the 1st operation.

Example 2:
Input: n = 6
Output: 4
Explanation: The binary representation of 6 is "110".
"110" -> "010" with the 2nd operation since the 1st bit is 1 and 0th through 0th bits are 0.
"010" -> "011" with the 1st operation.
"011" -> "001" with the 2nd operation since the 0th bit is 1.
"001" -> "000" with the 1st operation.

Constraints:
0 <= n <= 10^9
```

<details><summary>Hint</summary>

```text
1. The fastest way to convert n to zero is to remove all set bits starting from the leftmost one.
   Try some simple examples to learn the rule of how many steps are needed to remove one set bit.
2. consider n=2^k case first, then solve for all n.
```

</details>

</details>

<details><summary>C</summary>

```c
int minimumOneBitOperations(int n) {
    int retVal = 0;

    int k = 0;
    int mask = 1;
    while (mask <= n) {
        if ((n & mask) != 0) {
            retVal = (1 << (k + 1)) - 1 - retVal;
        }
        mask <<= 1;
        k++;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minimumOneBitOperations(int n) {
        int retVal = 0;

        int k = 0;
        int mask = 1;
        while (mask <= n) {
            if ((n & mask) != 0) {
                retVal = (1 << (k + 1)) - 1 - retVal;
            }
            mask <<= 1;
            k++;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minimumOneBitOperations(self, n: int) -> int:
        retVal = 0

        k = 0
        mask = 1
        while mask <= n:
            if n & mask:
                retVal = 2 ** (k + 1) - 1 - retVal
            mask <<= 1
            k += 1

        return retVal
```

</details>

## [1680. Concatenation of Consecutive Binary Numbers](https://leetcode.com/problems/concatenation-of-consecutive-binary-numbers/)  1629

<details><summary>Description</summary>

```text
Given an integer n, return the decimal value of the binary string formed
by concatenating the binary representations of 1 to n in order, modulo 10^9 + 7.

Example 1:
Input: n = 1
Output: 1
Explanation: "1" in binary corresponds to the decimal value 1.

Example 2:
Input: n = 3
Output: 27
Explanation: In binary, 1, 2, and 3 corresponds to "1", "10", and "11".
After concatenating them, we have "11011", which corresponds to the decimal value 27.

Example 3:
Input: n = 12
Output: 505379714
Explanation: The concatenation results in "1101110010111011110001001101010111100".
The decimal value of that is 118505380540.
After modulo 109 + 7, the result is 505379714.

Constraints:
1 <= n <= 10^5
```

</details>

<details><summary>C</summary>

```c
unsigned int getMostSignificantBit(unsigned int n)
{
    unsigned int count = 0;

    while (n >>= 1)
    {
        ++count;
    }

    return count;
}

int concatenatedBinary(int n){
    int retVal = 0;

    /* A few distributive properties of modulo are as follows:
     *  1. ( a + b ) % c = ( ( a % c ) + ( b % c ) ) % c
     *  2. ( a * b ) % c = ( ( a % c ) * ( b % c ) ) % c
     *  3. ( a – b ) % c = ( ( a % c ) - ( b % c ) ) % c ( see notes at bottom )
     *  4. ( a / b ) % c NOT EQUAL TO ( ( a % c ) / ( b % c ) ) % c
     */
    int modulo = 1000000000 + 7;
#if 1
    unsigned int shift;
    long ans = 0;
    int i;
    for (i=1; i<=n; ++i)
    {
        shift = getMostSignificantBit(i) + 1;
        ans = (((ans<<shift) % modulo) + i) % modulo;
    }
    retVal = ans;
#else
    unsigned int shift;
    unsigned int shiftTotal = 0;
    unsigned int tmp = 0;
    int i, j;
    for (i=n; i>=1; --i)
    {
        shift = getMostSignificantBit(i) + 1;

        tmp = i;
        for (j=0; j<shiftTotal; ++j)
        {
            tmp = ((tmp % modulo) * (2 % modulo)) % modulo;
        }
        retVal += (tmp % modulo);
        retVal %= modulo;

        shiftTotal += shift;
    }
#endif

    return retVal;
}
```

</details>

## [1829. Maximum XOR for Each Query](https://leetcode.com/problems/maximum-xor-for-each-query/)  1523

- [Official](https://leetcode.com/problems/maximum-xor-for-each-query/editorial/)
- [Official](https://leetcode.cn/problems/maximum-xor-for-each-query/solutions/728291/mei-ge-cha-xun-de-zui-da-yi-huo-zhi-by-l-haol/)

<details><summary>Description</summary>

```text
You are given a sorted array nums of n non-negative integers and an integer maximumBit.
You want to perform the following query n times:
1. Find a non-negative integer k < 2^maximumBit
   such that nums[0] XOR nums[1] XOR ... XOR nums[nums.length-1] XOR k is maximized.
   k is the answer to the ith query.
2. Remove the last element from the current array nums.

Return an array answer, where answer[i] is the answer to the ith query.

Example 1:
Input: nums = [0,1,1,3], maximumBit = 2
Output: [0,3,2,3]
Explanation: The queries are answered as follows:
1st query: nums = [0,1,1,3], k = 0 since 0 XOR 1 XOR 1 XOR 3 XOR 0 = 3.
2nd query: nums = [0,1,1], k = 3 since 0 XOR 1 XOR 1 XOR 3 = 3.
3rd query: nums = [0,1], k = 2 since 0 XOR 1 XOR 2 = 3.
4th query: nums = [0], k = 3 since 0 XOR 3 = 3.

Example 2:
Input: nums = [2,3,4,7], maximumBit = 3
Output: [5,2,6,5]
Explanation: The queries are answered as follows:
1st query: nums = [2,3,4,7], k = 5 since 2 XOR 3 XOR 4 XOR 7 XOR 5 = 7.
2nd query: nums = [2,3,4], k = 2 since 2 XOR 3 XOR 4 XOR 2 = 7.
3rd query: nums = [2,3], k = 6 since 2 XOR 3 XOR 6 = 7.
4th query: nums = [2], k = 5 since 2 XOR 5 = 7.

Example 3:
Input: nums = [0,1,2,2,5,7], maximumBit = 3
Output: [4,3,6,4,6,7]

Constraints:
nums.length == n
1 <= n <= 10^5
1 <= maximumBit <= 20
0 <= nums[i] < 2^maximumBit
nums​​​ is sorted in ascending order.
```

<details><summary>Hint</summary>

```text
1. Note that the maximum possible XOR result is always 2^(maximumBit) - 1
2. So the answer for a prefix is the XOR of that prefix XORed with 2^(maximumBit)-1
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *getMaximumXor(int *nums, int numsSize, int maximumBit, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int *)malloc(numsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (numsSize * sizeof(int)));

    int xorProduct = 0;
    for (int i = 0; i < numsSize; i++) {
        xorProduct = xorProduct ^ nums[i];
    }

    int mask = (1 << maximumBit) - 1;
    for (int i = 0; i < numsSize; i++) {
        pRetVal[(*returnSize)++] = (xorProduct ^ mask);
        // remove last element
        xorProduct = xorProduct ^ nums[numsSize - 1 - i];
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> getMaximumXor(vector<int>& nums, int maximumBit) {
        vector<int> retVal;

        int numsSize = nums.size();

        int xorProduct = 0;
        for (int i = 0; i < numsSize; i++) {
            xorProduct = xorProduct ^ nums[i];
        }

        int mask = (1 << maximumBit) - 1;
        for (int i = 0; i < numsSize; i++) {
            retVal.emplace_back(xorProduct ^ mask);
            // remove last element
            xorProduct = xorProduct ^ nums[numsSize - 1 - i];
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def getMaximumXor(self, nums: List[int], maximumBit: int) -> List[int]:
        retVal = []

        numsSize = len(nums)

        xorProduct = 0
        for i in range(numsSize):
            xorProduct = xorProduct ^ nums[i]

        mask = (1 << maximumBit) - 1
        for i in range(numsSize):
            retVal.append(xorProduct ^ mask)
            # remove last element
            xorProduct = xorProduct ^ nums[numsSize - 1 - i]

        return retVal
```

</details>

## [1863. Sum of All Subset XOR Totals](https://leetcode.com/problems/sum-of-all-subset-xor-totals/)  1372

- [Official](https://leetcode.com/problems/sum-of-all-subset-xor-totals/editorial/)
- [Official](https://leetcode.cn/problems/sum-of-all-subset-xor-totals/solutions/784306/sum-of-all-subset-xor-totals-by-leetcode-o5aa/)

<details><summary>Description</summary>

```text
The XOR total of an array is defined as the bitwise XOR of all its elements, or 0 if the array is empty.
- For example, the XOR total of the array [2,5,6] is 2 XOR 5 XOR 6 = 1.

Given an array nums, return the sum of all XOR totals for every subset of nums.

Note: Subsets with the same elements should be counted multiple times.

An array a is a subset of an array b if a can be obtained from b by deleting some (possibly zero) elements of b.

Example 1:
Input: nums = [1,3]
Output: 6
Explanation: The 4 subsets of [1,3] are:
- The empty subset has an XOR total of 0.
- [1] has an XOR total of 1.
- [3] has an XOR total of 3.
- [1,3] has an XOR total of 1 XOR 3 = 2.
0 + 1 + 3 + 2 = 6

Example 2:
Input: nums = [5,1,6]
Output: 28
Explanation: The 8 subsets of [5,1,6] are:
- The empty subset has an XOR total of 0.
- [5] has an XOR total of 5.
- [1] has an XOR total of 1.
- [6] has an XOR total of 6.
- [5,1] has an XOR total of 5 XOR 1 = 4.
- [5,6] has an XOR total of 5 XOR 6 = 3.
- [1,6] has an XOR total of 1 XOR 6 = 7.
- [5,1,6] has an XOR total of 5 XOR 1 XOR 6 = 2.
0 + 5 + 1 + 6 + 4 + 3 + 7 + 2 = 28

Example 3:
Input: nums = [3,4,5,6,7,8]
Output: 480
Explanation: The sum of all XOR totals for every subset is 480.

Constraints:
1 <= nums.length <= 12
1 <= nums[i] <= 20
```

<details><summary>Hint</summary>

```text
1. Is there a way to iterate through all the subsets of the array?
2. Can we use recursion to efficiently iterate through all the subsets?
```

</details>

</details>

<details><summary>C</summary>

```c
int subsetXORSum(int* nums, int numsSize) {
    int retVal = 0;

    // Capture each bit that is set in any of the elements
    int i;
    for (i = 0; i < numsSize; ++i) {
        retVal |= nums[i];
    }

    // Multiply by the number of subset XOR totals that will have each bit set
    retVal = retVal << (numsSize - 1);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int subsetXORSum(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        // Capture each bit that is set in any of the elements
        for (int num : nums) {
            retVal |= num;
        }

        // Multiply by the number of subset XOR totals that will have each bit set
        retVal = retVal << (numsSize - 1);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def subsetXORSum(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        # Capture each bit that is set in any of the elements
        for num in nums:
            retVal |= num

        # Multiply by the number of subset XOR totals that will have each bit set
        retVal = retVal << (numsSize - 1)

        return retVal
```

</details>

## [2044. Count Number of Maximum Bitwise-OR Subsets](https://leetcode.com/problems/count-number-of-maximum-bitwise-or-subsets/)  1567

- [Official](https://leetcode.com/problems/count-number-of-maximum-bitwise-or-subsets/editorial/)
- [Official](https://leetcode.cn/problems/count-number-of-maximum-bitwise-or-subsets/solutions/1335667/tong-ji-an-wei-huo-neng-de-dao-zui-da-zh-r6zd/)

<details><summary>Description</summary>

```text
Given an integer array nums, find the maximum possible bitwise OR of a subset of nums
and return the number of different non-empty subsets with the maximum bitwise OR.

An array a is a subset of an array b if a can be obtained from b by deleting some (possibly zero) elements of b.
Two subsets are considered different if the indices of the elements chosen are different.

The bitwise OR of an array a is equal to a[0] OR a[1] OR ... OR a[a.length - 1] (0-indexed).

Example 1:
Input: nums = [3,1]
Output: 2
Explanation: The maximum possible bitwise OR of a subset is 3. There are 2 subsets with a bitwise OR of 3:
- [3]
- [3,1]

Example 2:
Input: nums = [2,2,2]
Output: 7
Explanation: All non-empty subsets of [2,2,2] have a bitwise OR of 2. There are 23 - 1 = 7 total subsets.

Example 3:
Input: nums = [3,2,1,5]
Output: 6
Explanation: The maximum possible bitwise OR of a subset is 7. There are 6 subsets with a bitwise OR of 7:
- [3,5]
- [3,1,5]
- [3,2,5]
- [3,2,1,5]
- [2,5]
- [2,1,5]

Constraints:
1 <= nums.length <= 16
1 <= nums[i] <= 10^5
```

<details><summary>Hint</summary>

```text
1. Can we enumerate all possible subsets?
2. The maximum bitwise-OR is the bitwise-OR of the whole array.
```

</details>

</details>

<details><summary>C</summary>

```c
int countMaxOrSubsets(int* nums, int numsSize) {
    int retVal = 0;

    int dp[1 << 17];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    int max = 0;
    int i, j;
    for (i = 0; i < numsSize; ++i) {
        for (j = max; j >= 0; --j) {
            dp[j | nums[i]] += dp[j];
        }
        max |= nums[i];
    }
    retVal = dp[max];

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int countMaxOrSubsets(vector<int>& nums) {
        int retVal = 0;

        vector<int> dp(1 << 17, 0);
        dp[0] = 1;

        int max = 0;
        for (int num : nums) {
            for (int i = max; i >= 0; i--) {
                dp[i | num] += dp[i];
            }
            max |= num;
        }
        retVal = dp[max];

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def countMaxOrSubsets(self, nums: List[int]) -> int:
        retVal = 0

        dp = [0] * (1 << 17)
        dp[0] = 1

        maxValue = 0
        for num in nums:
            for i in range(maxValue, -1, -1):
                dp[i | num] += dp[i]
            maxValue |= num

        retVal = dp[maxValue]

        return retVal
```

</details>

## [2220. Minimum Bit Flips to Convert Number](https://leetcode.com/problems/minimum-bit-flips-to-convert-number/)  1282

- [Official](https://leetcode.com/problems/minimum-bit-flips-to-convert-number/editorial/)
- [Official](https://leetcode.cn/problems/minimum-bit-flips-to-convert-number/solutions/1398488/zhuan-huan-shu-zi-de-zui-shao-wei-fan-zh-awf2/)

<details><summary>Description</summary>

```text
A bit flip of a number x is choosing a bit in the binary representation of x and flipping it from either 0 to 1 or 1 to 0.
- For example, for x = 7, the binary representation is 111 and we may choose any bit (including any leading zeros not shown)
  and flip it. We can flip the first bit from the right to get 110, flip the second bit from the right to get 101,
  flip the fifth bit from the right (a leading zero) to get 10111, etc.

Given two integers start and goal, return the minimum number of bit flips to convert start to goal.

Example 1:
Input: start = 10, goal = 7
Output: 3
Explanation: The binary representation of 10 and 7 are 1010 and 0111 respectively. We can convert 10 to 7 in 3 steps:
- Flip the first bit from the right: 1010 -> 1011.
- Flip the third bit from the right: 1011 -> 1111.
- Flip the fourth bit from the right: 1111 -> 0111.
It can be shown we cannot convert 10 to 7 in less than 3 steps. Hence, we return 3.

Example 2:
Input: start = 3, goal = 4
Output: 3
Explanation: The binary representation of 3 and 4 are 011 and 100 respectively. We can convert 3 to 4 in 3 steps:
- Flip the first bit from the right: 011 -> 010.
- Flip the second bit from the right: 010 -> 000.
- Flip the third bit from the right: 000 -> 100.
It can be shown we cannot convert 3 to 4 in less than 3 steps. Hence, we return 3.

Constraints:
0 <= start, goal <= 10^9
```

<details><summary>Hint</summary>

```text
1. If the value of a bit in start and goal differ, then we need to flip that bit.
2. Consider using the XOR operation to determine which bits need a bit flip.
```

</details>

</details>

<details><summary>C</summary>

```c
int minBitFlips(int start, int goal) {
    int retVal = 0;

    int i;
    for (i = 0; i < 32; ++i) {
        retVal += (start & 1) ^ (goal & 1);
        start >>= 1;
        goal >>= 1;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minBitFlips(int start, int goal) {
        int retVal = 0;

        for (int i = 0; i < 32; ++i) {
            retVal += (start & 1) ^ (goal & 1);
            start >>= 1;
            goal >>= 1;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minBitFlips(self, start: int, goal: int) -> int:
        retVal = 0

        for _ in range(32):
            retVal += (start & 1) ^ (goal & 1)
            start >>= 1
            goal >>= 1

        return retVal
```

</details>

## [2275. Largest Combination With Bitwise AND Greater Than Zero](https://leetcode.com/problems/largest-combination-with-bitwise-and-greater-than-zero/)  1642

- [Official](https://leetcode.com/problems/largest-combination-with-bitwise-and-greater-than-zero/editorial/)
- [Official](https://leetcode.cn/problems/largest-combination-with-bitwise-and-greater-than-zero/solutions/1538671/an-wei-yu-jie-guo-da-yu-ling-de-zui-chan-hm7c/)

<details><summary>Description</summary>

```text
The bitwise AND of an array nums is the bitwise AND of all integers in nums.
- For example, for nums = [1, 5, 3], the bitwise AND is equal to 1 & 5 & 3 = 1.
- Also, for nums = [7], the bitwise AND is 7.

You are given an array of positive integers candidates.
Evaluate the bitwise AND of every combination of numbers of candidates.
Each number in candidates may only be used once in each combination.

Return the size of the largest combination of candidates with a bitwise AND greater than 0.

Example 1:
Input: candidates = [16,17,71,62,12,24,14]
Output: 4
Explanation: The combination [16,17,62,24] has a bitwise AND of 16 & 17 & 62 & 24 = 16 > 0.
The size of the combination is 4.
It can be shown that no combination with a size greater than 4 has a bitwise AND greater than 0.
Note that more than one combination may have the largest size.
For example, the combination [62,12,24,14] has a bitwise AND of 62 & 12 & 24 & 14 = 8 > 0.

Example 2:
Input: candidates = [8,8]
Output: 2
Explanation: The largest combination [8,8] has a bitwise AND of 8 & 8 = 8 > 0.
The size of the combination is 2, so we return 2.

Constraints:
1 <= candidates.length <= 10^5
1 <= candidates[i] <= 10^7
```

<details><summary>Hint</summary>

```text
1. For the bitwise AND to be greater than zero, at least one bit should be 1 for every number in the combination.
2. The candidates are 24 bits long, so for every bit position,
   we can calculate the size of the largest combination such that the bitwise AND will have a 1 at that bit position.
```

</details>

</details>

<details><summary>C</summary>

```c
int largestCombination(int* candidates, int candidatesSize) {
    int retVal = 0;

    // 1 <= candidates[i] <= 10^7 < 2^24
    int maxCount;
    int i, j;
    for (i = 0; i < 24; ++i) {
        maxCount = 0;
        for (j = 0; j < candidatesSize; ++j) {
            if ((candidates[j] & (1 << i)) != 0) {
                maxCount++;
            }
        }
        retVal = fmax(retVal, maxCount);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int largestCombination(vector<int>& candidates) {
        int retVal = 0;

        // 1 <= candidates[i] <= 10^7 < 2^24
        for (int i = 0; i < 24; ++i) {
            int maxCount = 0;
            for (int candidate : candidates) {
                if ((candidate & (1 << i)) != 0) {
                    maxCount++;
                }
            }
            retVal = max(retVal, maxCount);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def largestCombination(self, candidates: List[int]) -> int:
        retVal = 0

        # 1 <= candidates[i] <= 10^7 < 2^24
        for i in range(24):
            maxCount = 0
            for candidate in candidates:
                if (candidate & (1 << i)) != 0:
                    maxCount += 1
            retVal = max(retVal, maxCount)

        return retVal
```

</details>

## [2419. Longest Subarray With Maximum Bitwise AND](https://leetcode.com/problems/longest-subarray-with-maximum-bitwise-and/)  1495

- [Official](https://leetcode.com/problems/longest-subarray-with-maximum-bitwise-and/editorial/)
- [Official](https://leetcode.cn/problems/longest-subarray-with-maximum-bitwise-and/solutions/3726046/an-wei-yu-zui-da-de-zui-chang-zi-shu-zu-w0t3f/)

<details><summary>Description</summary>

```text
You are given an integer array nums of size n.

Consider a non-empty subarray from nums that has the maximum possible bitwise AND.
- In other words, let k be the maximum value of the bitwise AND of any subarray of nums.
  Then, only subarrays with a bitwise AND equal to k should be considered.

Return the length of the longest such subarray.

The bitwise AND of an array is the bitwise AND of all the numbers in it.

A subarray is a contiguous sequence of elements within an array.

Example 1:
Input: nums = [1,2,3,3,2,2]
Output: 2
Explanation:
The maximum possible bitwise AND of a subarray is 3.
The longest subarray with that value is [3,3], so we return 2.

Example 2:
Input: nums = [1,2,3,4]
Output: 1
Explanation:
The maximum possible bitwise AND of a subarray is 4.
The longest subarray with that value is [4], so we return 1.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^6
```

<details><summary>Hint</summary>

```text
1. Notice that the bitwise AND of two different numbers
   will always be strictly less than the maximum of those two numbers.
2. What does that tell us about the nature of the subarray that we should choose?
```

</details>

</details>

<details><summary>C</summary>

```c
int longestSubarray(int* nums, int numsSize) {
    int retVal = 0;

    // The maximum possible bitwise AND should not be less than a largest element.
    // Therefore, the subarray must only include one or more largest elements.
    int maxNum = nums[0];  // 1 <= nums.length <= 10^5
    int count = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] == maxNum) {
            count++;
            retVal = (retVal > count) ? (retVal) : (count);
        } else if (nums[i] > maxNum) {
            maxNum = nums[i];
            count = 1;
            retVal = 1;
        } else if (nums[i] < maxNum) {
            count = 0;
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
    int longestSubarray(vector<int>& nums) {
        int retVal = 0;

        // The maximum possible bitwise AND should not be less than a largest element.
        // Therefore, the subarray must only include one or more largest elements.
        int maxNum = nums[0];  // 1 <= nums.length <= 10^5
        int count = 0;
        for (int num : nums) {
            if (num == maxNum) {
                count++;
                retVal = max(retVal, count);
            } else if (num > maxNum) {
                maxNum = num;
                count = 1;
                retVal = 1;
            } else if (num < maxNum) {
                count = 0;
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
    def longestSubarray(self, nums: List[int]) -> int:
        retVal = 0

        # The maximum possible bitwise AND should not be less than a largest element.
        # Therefore, the subarray must only include one or more largest elements.
        maxNum = max(nums)
        count = 0
        for num in nums:
            if num == maxNum:
                count += 1
            else:
                count = 0
            retVal = max(retVal, count)

        return retVal
```

</details>

## [2425. Bitwise XOR of All Pairings](https://leetcode.com/problems/bitwise-xor-of-all-pairings/)  1622

- [Official](https://leetcode.com/problems/bitwise-xor-of-all-pairings/editorial/)

<details><summary>Description</summary>

```text
You are given two 0-indexed arrays, nums1 and nums2, consisting of non-negative integers.
There exists another array, nums3, which contains the bitwise XOR of all pairings of integers between nums1 and nums2
(every integer in nums1 is paired with every integer in nums2 exactly once).

Return the bitwise XOR of all integers in nums3.

Example 1:
Input: nums1 = [2,1,3], nums2 = [10,2,5,0]
Output: 13
Explanation:
A possible nums3 array is [8,0,7,2,11,3,4,1,9,1,6,3].
The bitwise XOR of all these numbers is 13, so we return 13.

Example 2:
Input: nums1 = [1,2], nums2 = [3,4]
Output: 0
Explanation:
All possible pairs of bitwise XORs are nums1[0] ^ nums2[0], nums1[0] ^ nums2[1], nums1[1] ^ nums2[0],
and nums1[1] ^ nums2[1].
Thus, one possible nums3 array is [2,5,1,6].
2 ^ 5 ^ 1 ^ 6 = 0, so we return 0.

Constraints:
1 <= nums1.length, nums2.length <= 10^5
0 <= nums1[i], nums2[j] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Think how the count of each individual integer affects the final answer.
2. If the length of nums1 is m and the length of nums2 is n,
   then each number in nums1 is repeated n times and each number in nums2 is repeated m times.
```

</details>

</details>

<details><summary>C</summary>

```c
int xorAllNums(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int retVal = 0;

    int xor1 = 0;
    if (nums2Size % 2 != 0) {
        for (int i = 0; i < nums1Size; i++) {
            xor1 ^= nums1[i];
        }
    }

    int xor2 = 0;
    if (nums1Size % 2 != 0) {
        for (int i = 0; i < nums2Size; i++) {
            xor2 ^= nums2[i];
        }
    }

    retVal = xor1 ^ xor2;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int xorAllNums(vector<int>& nums1, vector<int>& nums2) {
        int retVal = 0;

        int nums1Size = nums1.size();
        int nums2Size = nums2.size();

        int xor1 = 0;
        if (nums2Size % 2 != 0) {
            for (int num : nums1) {
                xor1 ^= num;
            }
        }

        int xor2 = 0;
        if (nums1Size % 2 != 0) {
            for (int num : nums2) {
                xor2 ^= num;
            }
        }

        retVal = xor1 ^ xor2;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def xorAllNums(self, nums1: List[int], nums2: List[int]) -> int:
        retVal = 0

        nums1Size = len(nums1)
        nums2Size = len(nums2)

        xor1 = 0
        if nums2Size % 2:
            for num in nums1:
                xor1 ^= num

        xor2 = 0
        if nums1Size % 2:
            for num in nums2:
                xor2 ^= num

        retVal = xor1 ^ xor2

        return retVal
```

</details>

## [2429. Minimize XOR](https://leetcode.com/problems/minimize-xor/)  1532

- [Official](https://leetcode.com/problems/minimize-xor/editorial/)

<details><summary>Description</summary>

```text
Given two positive integers num1 and num2, find the positive integer x such that:
- x has the same number of set bits as num2, and
- The value x XOR num1 is minimal.

Note that XOR is the bitwise XOR operation.

Return the integer x. The test cases are generated such that x is uniquely determined.

The number of set bits of an integer is the number of 1's in its binary representation.

Example 1:
Input: num1 = 3, num2 = 5
Output: 3
Explanation:
The binary representations of num1 and num2 are 0011 and 0101, respectively.
The integer 3 has the same number of set bits as num2, and the value 3 XOR 3 = 0 is minimal.

Example 2:
Input: num1 = 1, num2 = 12
Output: 3
Explanation:
The binary representations of num1 and num2 are 0001 and 1100, respectively.
The integer 3 has the same number of set bits as num2, and the value 3 XOR 1 = 2 is minimal.

Constraints:
1 <= num1, num2 <= 10^9
```

<details><summary>Hint</summary>

```text
1. To arrive at a small xor, try to turn off some bits from num1
2. If there are still left bits to set, try to set them from the least significant bit
```

</details>

</details>

<details><summary>C</summary>

```c
bool isSet(int x, int bit) {
    bool retVal = x & (1 << bit);

    return retVal;
}
int setBit(int x, int bit) {
    int retVal = x | (1 << bit);

    return retVal;
}
int unsetBit(int x, int bit) {
    int retVal = x & (~(1 << bit));

    return retVal;
}
int minimizeXor(int num1, int num2) {
    int retVal = num1;

    int targetSetBitsCount = __builtin_popcount(num2);
    int setBitsCount = __builtin_popcount(retVal);
    int currentBit = 0;

    while (setBitsCount < targetSetBitsCount) {
        if (isSet(retVal, currentBit) == false) {
            retVal = setBit(retVal, currentBit);
            setBitsCount++;
        }
        currentBit++;
    }

    while (setBitsCount > targetSetBitsCount) {
        if (isSet(retVal, currentBit) == true) {
            retVal = unsetBit(retVal, currentBit);
            setBitsCount--;
        }
        currentBit++;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    bool isSet(int x, int bit) {
        bool retVal = x & (1 << bit);

        return retVal;
    }
    int setBit(int x, int bit) {
        int retVal = x | (1 << bit);

        return retVal;
    }
    int unsetBit(int x, int bit) {
        int retVal = x & (~(1 << bit));

        return retVal;
    }

   public:
    int minimizeXor(int num1, int num2) {
        int retVal = num1;

        int targetSetBitsCount = __builtin_popcount(num2);
        int setBitsCount = __builtin_popcount(retVal);
        int currentBit = 0;

        while (setBitsCount < targetSetBitsCount) {
            if (isSet(retVal, currentBit) == false) {
                retVal = setBit(retVal, currentBit);
                setBitsCount++;
            }
            currentBit++;
        }

        while (setBitsCount > targetSetBitsCount) {
            if (isSet(retVal, currentBit) == true) {
                retVal = unsetBit(retVal, currentBit);
                setBitsCount--;
            }
            currentBit++;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def isSet(self, x: int, bit: int) -> bool:
        retVal = ((x & (1 << bit)) != 0)

        return retVal

    def setBit(self, x: int, bit: int) -> int:
        retVal = (x | (1 << bit))

        return retVal

    def unsetBit(self, x: int, bit: int) -> int:
        retVal = (x & ~(1 << bit))

        return retVal

    def minimizeXor(self, num1: int, num2: int) -> int:
        retVal = num1

        targetSetBitsCount = bin(num2).count("1")
        setBitsCount = bin(retVal).count("1")
        currentBit = 0

        while setBitsCount < targetSetBitsCount:
            if self.isSet(retVal, currentBit) == False:
                retVal = self.setBit(retVal, currentBit)
                setBitsCount += 1
            currentBit += 1

        while setBitsCount > targetSetBitsCount:
            if self.isSet(retVal, currentBit) == True:
                retVal = self.unsetBit(retVal, currentBit)
                setBitsCount -= 1
            currentBit += 1

        return retVal
```

</details>

## [2433. Find The Original Array of Prefix Xor](https://leetcode.com/problems/find-the-original-array-of-prefix-xor/)  1366

- [Official](https://leetcode.com/problems/find-the-original-array-of-prefix-xor/editorial/)

<details><summary>Description</summary>

```text
You are given an integer array pref of size n. Find and return the array arr of size n that satisfies:
- pref[i] = arr[0] ^ arr[1] ^ ... ^ arr[i].
Note that ^ denotes the bitwise-xor operation.

It can be proven that the answer is unique.

Example 1:
Input: pref = [5,2,0,3,1]
Output: [5,7,2,3,2]
Explanation: From the array [5,7,2,3,2] we have the following:
- pref[0] = 5.
- pref[1] = 5 ^ 7 = 2.
- pref[2] = 5 ^ 7 ^ 2 = 0.
- pref[3] = 5 ^ 7 ^ 2 ^ 3 = 3.
- pref[4] = 5 ^ 7 ^ 2 ^ 3 ^ 2 = 1.

Example 2:
Input: pref = [13]
Output: [13]
Explanation: We have pref[0] = arr[0] = 13.

Constraints:
1 <= pref.length <= 10^5
0 <= pref[i] <= 10^6
```

<details><summary>Hint</summary>

```text
1. Consider the following equation: x ^ a = b. How can you find x?
2. Notice that arr[i] ^ pref[i-1] = pref[i]. This is the same as the previous equation.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *findArray(int *pref, int prefSize, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int *)malloc(prefSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (prefSize * sizeof(int)));

    pRetVal[0] = pref[0];  // 1 <= pref.length <= 10^5
    (*returnSize)++;
    int i;
    for (i = 1; i < prefSize; ++i) {
        pRetVal[i] = pref[i - 1] ^ pref[i];
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
    vector<int> findArray(vector<int>& pref) {
        vector<int> retVal;

        retVal.emplace_back(pref[0]);  // 1 <= pref.length <= 10^5
        int prefSize = pref.size();
        for (int i = 1; i < prefSize; ++i) {
            retVal.emplace_back(pref[i - 1] ^ pref[i]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def findArray(self, pref: List[int]) -> List[int]:
        retVal = []

        retVal.append(pref[0])  # 1 <= pref.length <= 10^5
        prefSize = len(pref)
        for i in range(1, prefSize):
            retVal.append(pref[i-1] ^ pref[i])

        return retVal
```

</details>

## [2683. Neighboring Bitwise XOR](https://leetcode.com/problems/neighboring-bitwise-xor/)  1517

- [Official](https://leetcode.com/problems/neighboring-bitwise-xor/editorial/)

<details><summary>Description</summary>

```text
A 0-indexed array derived with length n is derived
by computing the bitwise XOR (⊕) of adjacent values in a binary array original of length n.

Specifically, for each index i in the range [0, n - 1]:
- If i = n - 1, then derived[i] = original[i] ⊕ original[0].
- Otherwise, derived[i] = original[i] ⊕ original[i + 1].

Given an array derived,
your task is to determine whether there exists a valid binary array original that could have formed derived.

Return true if such an array exists or false otherwise.
- A binary array is an array containing only 0's and 1's

Example 1:
Input: derived = [1,1,0]
Output: true
Explanation: A valid original array that gives derived is [0,1,0].
derived[0] = original[0] ⊕ original[1] = 0 ⊕ 1 = 1
derived[1] = original[1] ⊕ original[2] = 1 ⊕ 0 = 1
derived[2] = original[2] ⊕ original[0] = 0 ⊕ 0 = 0

Example 2:
Input: derived = [1,1]
Output: true
Explanation: A valid original array that gives derived is [0,1].
derived[0] = original[0] ⊕ original[1] = 1
derived[1] = original[1] ⊕ original[0] = 1

Example 3:
Input: derived = [1,0]
Output: false
Explanation: There is no valid original array that gives derived.

Constraints:
n == derived.length
1 <= n <= 10^5
The values in derived are either 0's or 1's
```

<details><summary>Hint</summary>

```text
1. Understand that from the original element, we are using each element twice to construct the derived array
2. The xor-sum of the derived array should be 0 since there is always a duplicate occurrence of each element.
```

</details>

</details>

<details><summary>C</summary>

```c
bool doesValidArrayExist(int* derived, int derivedSize) {
    bool retVal = false;

    int XOR = 0;
    for (int i = 0; i < derivedSize; ++i) {
        XOR = XOR ^ derived[i];
    }
    if (XOR == 0) {
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
    bool doesValidArrayExist(vector<int>& derived) {
        bool retVal = false;

        int XOR = 0;
        for (auto element : derived) {
            XOR = XOR ^ element;
        }
        if (XOR == 0) {
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
    def doesValidArrayExist(self, derived: List[int]) -> bool:
        retVal = False

        XOR = 0
        for element in derived:
            XOR = XOR ^ element
        if XOR == 0:
            retVal = True

        return retVal
```

</details>

## [2997. Minimum Number of Operations to Make Array XOR Equal to K](https://leetcode.com/problems/minimum-number-of-operations-to-make-array-xor-equal-to-k/)  1524

- [Official](https://leetcode.com/problems/minimum-number-of-operations-to-make-array-xor-equal-to-k/editorial/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array nums and a positive integer k.

You can apply the following operation on the array any number of times:
- Choose any element of the array and flip a bit in its binary representation.
  Flipping a bit means changing a 0 to 1 or vice versa.

Return the minimum number of operations required to make the bitwise XOR of all elements of the final array equal to k.

Note that you can flip leading zero bits in the binary representation of elements.
For example, for the number (101)2 you can flip the fourth bit and obtain (1101)2.

Example 1:
Input: nums = [2,1,3,4], k = 1
Output: 2
Explanation: We can do the following operations:
- Choose element 2 which is 3 == (011)2, we flip the first bit and we obtain (010)2 == 2. nums becomes [2,1,2,4].
- Choose element 0 which is 2 == (010)2, we flip the third bit and we obtain (110)2 = 6. nums becomes [6,1,2,4].
The XOR of elements of the final array is (6 XOR 1 XOR 2 XOR 4) == 1 == k.
It can be shown that we cannot make the XOR equal to k in less than 2 operations.

Example 2:
Input: nums = [2,0,2,0], k = 0
Output: 0
Explanation: The XOR of elements of the array is (2 XOR 0 XOR 2 XOR 0) == 0 == k. So no operation is needed.

Constraints:
1 <= nums.length <= 10^5
0 <= nums[i] <= 10^6
0 <= k <= 10^6
```

<details><summary>Hint</summary>

```text
1. Calculate the bitwise XOR of all elements of the original array and compare it to k in their binary representation.
2. For each different bit between the bitwise XOR of elements of the original array and k
   we have to flip exactly one bit of an element in nums to make that bit equal.
```

</details>

</details>

<details><summary>C</summary>

```c
int minOperations(int* nums, int numsSize, int k) {
    int retVal = 0;

    int xorValue = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        xorValue ^= nums[i];
    }
    xorValue ^= k;
    retVal = __builtin_popcount(xorValue);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minOperations(vector<int>& nums, int k) {
        int retVal = 0;

        int xorValue = 0;
        for (int num : nums) {
            xorValue ^= num;
        }
        xorValue ^= k;
        retVal = __builtin_popcount(xorValue);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minOperations(self, nums: List[int], k: int) -> int:
        retVal = 0

        xorValue = 0
        for num in nums:
            xorValue ^= num
        xorValue ^= k
        retVal = xorValue.bit_count()

        return retVal
```

</details>

## [3011. Find if Array Can Be Sorted](https://leetcode.com/problems/find-if-array-can-be-sorted/)  1496

- [Official](https://leetcode.com/problems/find-if-array-can-be-sorted/editorial/)
- [Official](https://leetcode.cn/problems/find-if-array-can-be-sorted/solutions/2837005/pan-duan-yi-ge-shu-zu-shi-fou-ke-yi-bian-xwgy/)

<details><summary>Description</summary>

```text
You are given a 0-indexed array of positive integers nums.

In one operation, you can swap any two adjacent elements if they have the same number of set bits.
You are allowed to do this operation any number of times (including zero).

Return true if you can sort the array, else return false.

Example 1:
Input: nums = [8,4,2,30,15]
Output: true
Explanation: Let's look at the binary representation of every element.
The numbers 2, 4, and 8 have one set bit each with binary representation "10", "100", and "1000" respectively.
The numbers 15 and 30 have four set bits each with binary representation "1111" and "11110".
We can sort the array using 4 operations:
- Swap nums[0] with nums[1]. This operation is valid because 8 and 4 have one set bit each.
  The array becomes [4,8,2,30,15].
- Swap nums[1] with nums[2]. This operation is valid because 8 and 2 have one set bit each.
  The array becomes [4,2,8,30,15].
- Swap nums[0] with nums[1]. This operation is valid because 4 and 2 have one set bit each.
  The array becomes [2,4,8,30,15].
- Swap nums[3] with nums[4]. This operation is valid because 30 and 15 have four set bits each.
  The array becomes [2,4,8,15,30].
The array has become sorted, hence we return true.
Note that there may be other sequences of operations which also sort the array.

Example 2:
Input: nums = [1,2,3,4,5]
Output: true
Explanation: The array is already sorted, hence we return true.

Example 3:
Input: nums = [3,16,8,4,2]
Output: false
Explanation: It can be shown that it is not possible to sort the input array using any number of operations.

Constraints:
1 <= nums.length <= 100
1 <= nums[i] <= 28
```

<details><summary>Hint</summary>

```text
1. Split the array into segments. Each segment contains consecutive elements with the same number of set bits.
2. From left to right,
   the previous segment’s largest element should be smaller than the current segment’s smallest element.
```

</details>

</details>

<details><summary>C</summary>

```c
bool canSortArray(int* nums, int numsSize) {
    bool retVal = true;

    int lastCnt = 0;
    int lastGroupMax = 0;
    int curGroupMax = 0;
    int curCnt;
    int i;
    for (i = 0; i < numsSize; i++) {
        curCnt = __builtin_popcount(nums[i]);
        if (curCnt == lastCnt) {
            curGroupMax = fmax(curGroupMax, nums[i]);
        } else {
            lastCnt = curCnt;
            lastGroupMax = curGroupMax;
            curGroupMax = nums[i];
        }

        if (nums[i] < lastGroupMax) {
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
    bool canSortArray(vector<int>& nums) {
        bool retVal = true;

        int lastCnt = 0;
        int lastGroupMax = 0;
        int curGroupMax = 0;
        for (int num : nums) {
            int curCnt = __builtin_popcount(num);
            if (curCnt == lastCnt) {
                curGroupMax = max(curGroupMax, num);
            } else {
                lastCnt = curCnt;
                lastGroupMax = curGroupMax;
                curGroupMax = num;
            }

            if (num < lastGroupMax) {
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
    def canSortArray(self, nums: List[int]) -> bool:
        retVal = True

        lastCnt = 0
        lastGroupMax = 0
        curGroupMax = 0
        for num in nums:
            curCnt = num.bit_count()
            if curCnt == lastCnt:
                curGroupMax = max(curGroupMax, num)
            else:
                lastCnt = curCnt
                lastGroupMax = curGroupMax
                curGroupMax = num

            if num < lastGroupMax:
                retVal = False
                break

        return retVal
```

</details>

## [3095. Shortest Subarray With OR at Least K I](https://leetcode.com/problems/shortest-subarray-with-or-at-least-k-i/)  1368

<details><summary>Description</summary>

```text
You are given an array nums of non-negative integers and an integer k.

An array is called special if the bitwise OR of all of its elements is at least k.

Return the length of the shortest special non-empty subarray of nums, or return -1 if no special subarray exists.

Example 1:
Input: nums = [1,2,3], k = 2
Output: 1
Explanation:
The subarray [3] has OR value of 3. Hence, we return 1.
Note that [2] is also a special subarray.

Example 2:
Input: nums = [2,1,8], k = 10
Output: 3
Explanation:
The subarray [2,1,8] has OR value of 11. Hence, we return 3.

Example 3:
Input: nums = [1,2], k = 0
Output: 1
Explanation:
The subarray [1] has OR value of 1. Hence, we return 1.

Constraints:
1 <= nums.length <= 50
0 <= nums[i] <= 50
0 <= k < 64
```

<details><summary>Hint</summary>

```text
1. The constraints are small. Brute force checking all the subarrays.
```

</details>

</details>

<details><summary>C</summary>

```c
void updateBitCounts(int* bitCounts, int bitCountsSize, int number, int delta) {
    int bitPosition;
    for (bitPosition = 0; bitPosition < bitCountsSize; bitPosition++) {
        if ((number >> bitPosition) & 1) {
            bitCounts[bitPosition] += delta;
        }
    }
}
int convertBitCountsToNumber(int* bitCounts, int bitCountsSize) {
    int retVal = 0;

    int bitPosition = 0;
    for (bitPosition = 0; bitPosition < bitCountsSize; bitPosition++) {
        if (bitCounts[bitPosition] != 0) {
            retVal |= (1 << bitPosition);
        }
    }

    return retVal;
}
int minimumSubarrayLength(int* nums, int numsSize, int k) {
    int retVal = -1;

    int bitCountsSize = 32;
    int* bitCounts = (int*)calloc(bitCountsSize, sizeof(int));
    if (bitCounts == NULL) {
        perror("calloc");
        return retVal;
    }
    int minLength = INT_MAX;
    int windowStart = 0;
    int windowEnd;
    for (windowEnd = 0; windowEnd < numsSize; ++windowEnd) {
        updateBitCounts(bitCounts, bitCountsSize, nums[windowEnd], 1);

        while ((windowStart <= windowEnd) && (convertBitCountsToNumber(bitCounts, bitCountsSize) >= k)) {
            minLength = fmin(minLength, windowEnd - windowStart + 1);
            updateBitCounts(bitCounts, bitCountsSize, nums[windowStart], -1);
            windowStart++;
        }
    }

    if (minLength != INT_MAX) {
        retVal = minLength;
    }

    //
    free(bitCounts);
    bitCounts = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    void updateBitCounts(vector<int>& bitCounts, int number, int delta) {
        for (int bitPosition = 0; bitPosition < 32; bitPosition++) {
            if ((number >> bitPosition) & 1) {
                bitCounts[bitPosition] += delta;
            }
        }
    }
    int convertBitCountsToNumber(const vector<int>& bitCounts) {
        int retVal = 0;

        for (int bitPosition = 0; bitPosition < 32; bitPosition++) {
            if (bitCounts[bitPosition] != 0) {
                retVal |= (1 << bitPosition);
            }
        }

        return retVal;
    }

   public:
    int minimumSubarrayLength(vector<int>& nums, int k) {
        int retVal = -1;

        int numsSize = nums.size();
        int windowStart = 0;
        vector<int> bitCounts(32, 0);
        int minLength = numeric_limits<int>::max();
        for (int windowEnd = 0; windowEnd < numsSize; ++windowEnd) {
            updateBitCounts(bitCounts, nums[windowEnd], 1);

            while ((windowStart <= windowEnd) && (convertBitCountsToNumber(bitCounts) >= k)) {
                minLength = min(minLength, windowEnd - windowStart + 1);
                updateBitCounts(bitCounts, nums[windowStart], -1);
                windowStart++;
            }
        }

        if (minLength != numeric_limits<int>::max()) {
            retVal = minLength;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def updateBitCounts(self, bitCounts: list, number: int, delta: int) -> None:
        for bitPosition in range(32):
            if number & (1 << bitPosition):
                bitCounts[bitPosition] += delta

    def convertBitCountsToNumber(self, bitCounts: list) -> int:
        retVal = 0

        for bitPosition in range(32):
            if bitCounts[bitPosition]:
                retVal |= (1 << bitPosition)

        return retVal

    def minimumSubarrayLength(self, nums: List[int], k: int) -> int:
        retVal = -1

        numsSize = len(nums)
        windowStart = 0
        bitCounts = [0] * 32
        minLength = float("inf")
        for windowEnd in range(numsSize):
            self.updateBitCounts(bitCounts, nums[windowEnd], 1)

            while (windowStart <= windowEnd) and (self.convertBitCountsToNumber(bitCounts) >= k):
                minLength = min(minLength, windowEnd - windowStart + 1)
                self.updateBitCounts(bitCounts, nums[windowStart], -1)
                windowStart += 1

        if minLength != float("inf"):
            retVal = minLength

        return retVal
```

</details>

## [3097. Shortest Subarray With OR at Least K II](https://leetcode.com/problems/shortest-subarray-with-or-at-least-k-ii/)  1891

- [Official](https://leetcode.com/problems/shortest-subarray-with-or-at-least-k-ii/editorial/)

<details><summary>Description</summary>

```text
You are given an array nums of non-negative integers and an integer k.

An array is called special if the bitwise OR of all of its elements is at least k.

Return the length of the shortest special non-empty subarray of nums, or return -1 if no special subarray exists.

Example 1:
Input: nums = [1,2,3], k = 2
Output: 1
Explanation:
The subarray [3] has OR value of 3. Hence, we return 1.

Example 2:
Input: nums = [2,1,8], k = 10
Output: 3
Explanation:
The subarray [2,1,8] has OR value of 11. Hence, we return 3.

Example 3:
Input: nums = [1,2], k = 0
Output: 1
Explanation:
The subarray [1] has OR value of 1. Hence, we return 1.

Constraints:
1 <= nums.length <= 2 * 10^5
0 <= nums[i] <= 10^9
0 <= k <= 10^9
```

<details><summary>Hint</summary>

```text
1. For each nums[i], we can maintain each subarray’s bitwise OR result ending with it.
2. The property of bitwise OR is that it never unsets any bits and only sets new bits
3. So the number of different results for each nums[i] is at most the number of bits 32.
```

</details>

</details>

<details><summary>C</summary>

```c
void updateBitCounts(int* bitCounts, int bitCountsSize, int number, int delta) {
    int bitPosition;
    for (bitPosition = 0; bitPosition < bitCountsSize; bitPosition++) {
        if ((number >> bitPosition) & 1) {
            bitCounts[bitPosition] += delta;
        }
    }
}
int convertBitCountsToNumber(int* bitCounts, int bitCountsSize) {
    int retVal = 0;

    int bitPosition = 0;
    for (bitPosition = 0; bitPosition < bitCountsSize; bitPosition++) {
        if (bitCounts[bitPosition] != 0) {
            retVal |= (1 << bitPosition);
        }
    }

    return retVal;
}
int minimumSubarrayLength(int* nums, int numsSize, int k) {
    int retVal = -1;

    int bitCountsSize = 32;
    int* bitCounts = (int*)calloc(bitCountsSize, sizeof(int));
    if (bitCounts == NULL) {
        perror("calloc");
        return retVal;
    }
    int minLength = INT_MAX;
    int windowStart = 0;
    int windowEnd;
    for (windowEnd = 0; windowEnd < numsSize; ++windowEnd) {
        updateBitCounts(bitCounts, bitCountsSize, nums[windowEnd], 1);

        while ((windowStart <= windowEnd) && (convertBitCountsToNumber(bitCounts, bitCountsSize) >= k)) {
            minLength = fmin(minLength, windowEnd - windowStart + 1);
            updateBitCounts(bitCounts, bitCountsSize, nums[windowStart], -1);
            windowStart++;
        }
    }

    if (minLength != INT_MAX) {
        retVal = minLength;
    }

    //
    free(bitCounts);
    bitCounts = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    void updateBitCounts(vector<int>& bitCounts, int number, int delta) {
        for (int bitPosition = 0; bitPosition < 32; bitPosition++) {
            if ((number >> bitPosition) & 1) {
                bitCounts[bitPosition] += delta;
            }
        }
    }
    int convertBitCountsToNumber(const vector<int>& bitCounts) {
        int retVal = 0;

        for (int bitPosition = 0; bitPosition < 32; bitPosition++) {
            if (bitCounts[bitPosition] != 0) {
                retVal |= (1 << bitPosition);
            }
        }

        return retVal;
    }

   public:
    int minimumSubarrayLength(vector<int>& nums, int k) {
        int retVal = -1;

        int numsSize = nums.size();
        int windowStart = 0;
        vector<int> bitCounts(32, 0);
        int minLength = numeric_limits<int>::max();
        for (int windowEnd = 0; windowEnd < numsSize; ++windowEnd) {
            updateBitCounts(bitCounts, nums[windowEnd], 1);

            while ((windowStart <= windowEnd) && (convertBitCountsToNumber(bitCounts) >= k)) {
                minLength = min(minLength, windowEnd - windowStart + 1);
                updateBitCounts(bitCounts, nums[windowStart], -1);
                windowStart++;
            }
        }

        if (minLength != numeric_limits<int>::max()) {
            retVal = minLength;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def updateBitCounts(self, bitCounts: list, number: int, delta: int) -> None:
        for bitPosition in range(32):
            if number & (1 << bitPosition):
                bitCounts[bitPosition] += delta

    def convertBitCountsToNumber(self, bitCounts: list) -> int:
        retVal = 0

        for bitPosition in range(32):
            if bitCounts[bitPosition]:
                retVal |= (1 << bitPosition)

        return retVal

    def minimumSubarrayLength(self, nums: List[int], k: int) -> int:
        retVal = -1

        numsSize = len(nums)
        windowStart = 0
        bitCounts = [0] * 32
        minLength = float("inf")
        for windowEnd in range(numsSize):
            self.updateBitCounts(bitCounts, nums[windowEnd], 1)

            while (windowStart <= windowEnd) and (self.convertBitCountsToNumber(bitCounts) >= k):
                minLength = min(minLength, windowEnd - windowStart + 1)
                self.updateBitCounts(bitCounts, nums[windowStart], -1)
                windowStart += 1

        if minLength != float("inf"):
            retVal = minLength

        return retVal
```

</details>

## [3133. Minimum Array End](https://leetcode.com/problems/minimum-array-end/)  1934

- [Official](https://leetcode.com/problems/minimum-array-end/editorial/)
- [Official](https://leetcode.cn/problems/minimum-array-end/solutions/2885445/shu-zu-zui-hou-yi-ge-yuan-su-de-zui-xiao-4tbz/)

<details><summary>Description</summary>

```text
You are given two integers n and x.
You have to construct an array of positive integers nums of size n
where for every 0 <= i < n - 1, nums[i + 1] is greater than nums[i],
and the result of the bitwise AND operation between all elements of nums is x.

Return the minimum possible value of nums[n - 1].

Example 1:
Input: n = 3, x = 4
Output: 6
Explanation:
nums can be [4,5,6] and its last element is 6.

Example 2:
Input: n = 2, x = 7
Output: 15
Explanation:
nums can be [7,15] and its last element is 15.

Constraints:
1 <= n, x <= 10^8
```

<details><summary>Hint</summary>

```text
1. Each element of the array should be obtained by “merging” x and v where v = 0, 1, 2, …(n - 1).
2. To merge x with another number v, keep the set bits of x untouched,
   for all the other bits, fill the set bits of v from right to left in order one by one.
3. So the final answer is the “merge” of x and n - 1.
```

</details>

</details>

<details><summary>C</summary>

```c
long long minEnd(int n, int x) {
    long long retVal = x;

    --n;  // Reducing n by 1 to exclude x from the iteration

    // Step 1: Iterate over each bit position with mask starting at 1 and shifting left
    long long mask;
    for (mask = 1; n > 0; mask <<= 1) {
        // Step 2: If the corresponding bit in x is 0
        if ((mask & x) == 0) {
            retVal |= ((n & 1) * mask);  // Set the bit in result based on the least significant bit of n
            n >>= 1;                     // Shift n to the right by 1 to process the next bit
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
    long long minEnd(int n, int x) {
        long long retVal = x;

        --n;  // Reducing n by 1 to exclude x from the iteration

        // Step 1: Iterate over each bit position with mask starting at 1 and shifting left
        long long mask;
        for (mask = 1; n > 0; mask <<= 1) {
            // Step 2: If the corresponding bit in x is 0
            if ((mask & x) == 0) {
                retVal |= ((n & 1) * mask);  // Set the bit in result based on the least significant bit of n
                n >>= 1;                     // Shift n to the right by 1 to process the next bit
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
    def minEnd(self, n: int, x: int) -> int:
        retVal = x

        n -= 1  # Reducing n by 1 to exclude x from the iteration
        mask = 1
        while n > 0:  # Step 1: Iterate while n > 0, using mask for bit positions
            if (mask & x) == 0:  # Step 2: If the corresponding bit in x is 0
                # Set the bit in result based on least significant bit of n
                retVal |= ((n & 1) * mask)
                # Shift n right by 1 to process next bit
                n >>= 1
            mask <<= 1  # Shift mask left by 1 for next iteration

        return retVal
```

</details>

## [3191. Minimum Operations to Make Binary Array Elements Equal to One I](https://leetcode.com/problems/minimum-operations-to-make-binary-array-elements-equal-to-one-i/)  1311

- [Official](https://leetcode.com/problems/minimum-operations-to-make-binary-array-elements-equal-to-one-i/editorial/)
- [Official](https://leetcode.cn/problems/minimum-operations-to-make-binary-array-elements-equal-to-one-i/)

<details><summary>Description</summary>

```text
You are given a binary array nums.

You can do the following operation on the array any number of times (possibly zero):
- Choose any 3 consecutive elements from the array and flip all of them.

Flipping an element means changing its value from 0 to 1, and from 1 to 0.

Return the minimum number of operations required to make all elements in nums equal to 1.
If it is impossible, return -1.

Example 1:
Input: nums = [0,1,1,1,0,0]
Output: 3
Explanation:
We can do the following operations:
Choose the elements at indices 0, 1 and 2. The resulting array is nums = [1,0,0,1,0,0].
Choose the elements at indices 1, 2 and 3. The resulting array is nums = [1,1,1,0,0,0].
Choose the elements at indices 3, 4 and 5. The resulting array is nums = [1,1,1,1,1,1].

Example 2:
Input: nums = [0,1,1,1]
Output: -1
Explanation:
It is impossible to make all elements equal to 1.

Constraints:
3 <= nums.length <= 10^5
0 <= nums[i] <= 1
```

<details><summary>Hint</summary>

```text
1. If nums[0] is 0, then the only way to change it to 1 is by doing an operation on the first 3 elements of the array.
2. After Changing nums[0] to 1, use the same logic on the remaining array.
```

</details>

</details>

<details><summary>C</summary>

```c
int minOperations(int* nums, int numsSize) {
    int retVal = 0;

    for (int i = 0; i < numsSize - 2; ++i) {
        if (nums[i] == 1) {
            continue;
        }
        nums[i] = 1;
        nums[i + 1] = (nums[i + 1] == 0) ? 1 : 0;
        nums[i + 2] = (nums[i + 2] == 0) ? 1 : 0;
        retVal++;
    }
    if ((nums[numsSize - 2] == 0) || (nums[numsSize - 1] == 0)) {
        retVal = -1;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minOperations(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        for (int i = 0; i < numsSize - 2; ++i) {
            if (nums[i] == 1) {
                continue;
            }
            nums[i] = 1;
            nums[i + 1] = (nums[i + 1] == 0) ? 1 : 0;
            nums[i + 2] = (nums[i + 2] == 0) ? 1 : 0;
            retVal++;
        }
        if ((nums[numsSize - 2] == 0) || (nums[numsSize - 1] == 0)) {
            retVal = -1;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minOperations(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)
        for i in range(numsSize - 2):
            if nums[i] == 1:
                continue
            nums[i] = 1
            nums[i + 1] = 1 if (nums[i + 1] == 0) else 0
            nums[i + 2] = 1 if (nums[i + 2] == 0) else 0
            retVal += 1

        if (nums[numsSize - 2] == 0) or (nums[numsSize - 1] == 0):
            retVal = -1

        return retVal
```

</details>
