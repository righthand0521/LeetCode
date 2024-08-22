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

## [2220. Minimum Bit Flips to Convert Number](https://leetcode.com/problems/minimum-bit-flips-to-convert-number/)  1282

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

</details>

<details><summary>C</summary>

```c
int minBitFlips(int start, int goal){
    int retVal = 0;

    int i;
    for (i=0; i<32; ++i)
    {
        retVal += (start&1)^(goal&1);
        start >>= 1;
        goal >>= 1;
    }

    return retVal;
}
```

</details>

## [2419. Longest Subarray With Maximum Bitwise AND](https://leetcode.com/problems/longest-subarray-with-maximum-bitwise-and/)  1495

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
