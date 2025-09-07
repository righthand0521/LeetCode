# Math

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

## [1304. Find N Unique Integers Sum up to Zero](https://leetcode.com/problems/find-n-unique-integers-sum-up-to-zero/)  1167

- [Official](https://leetcode.com/problems/find-n-unique-integers-sum-up-to-zero/editorial/)
- [Official](https://leetcode.cn/problems/find-n-unique-integers-sum-up-to-zero/solutions/101790/he-wei-ling-de-nge-wei-yi-zheng-shu-by-leetcode-so/)

<details><summary>Description</summary>

```text
Given an integer n, return any array containing n unique integers such that they add up to 0.

Example 1:
Input: n = 5
Output: [-7,-1,1,3,4]
Explanation: These arrays also are accepted [-5,-1,1,2,3] , [-3,-1,2,-2,4].

Example 2:
Input: n = 3
Output: [-1,0,1]

Example 3:
Input: n = 1
Output: [0]

Constraints:
1 <= n <= 1000
```

<details><summary>Hint</summary>

```text
1. Return an array where the values are symmetric. (+x , -x).
2. If n is odd, append value 0 in your returned array.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sumZero(int n, int* returnSize) {
    int* pRetVal = NULL;

    pRetVal = (int*)calloc(n, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }
    (*returnSize) = n;

    for (int i = 0; i < n / 2; i++) {
        pRetVal[i] = (i + 1);
        pRetVal[n - 1 - i] = -(i + 1);
    }
    if (n % 2 == 1) {
        pRetVal[n / 2] = 0;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> sumZero(int n) {
        vector<int> retVal(n, 0);

        for (int i = 0; i < n / 2; i++) {
            retVal[i] = (i + 1);
            retVal[n - 1 - i] = -(i + 1);
        }
        if (n % 2 == 1) {
            retVal[n / 2] = 0;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def sumZero(self, n: int) -> List[int]:
        retVal = None

        retVal = [0] * n
        for i in range(n//2):
            retVal[i] = (i + 1)
            retVal[n - 1 - i] = -(i + 1)
        if n % 2 == 1:
            retVal[n//2] = 0

        return retVal
```

</details>

## [1323. Maximum 69 Number](https://leetcode.com/problems/maximum-69-number/)  1193

- [Official](https://leetcode.cn/problems/maximum-69-number/solutions/101258/6-he-9-zu-cheng-de-zui-da-shu-zi-by-leetcode-solut/)

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

<details><summary>Hint</summary>

```text
1. Convert the number in an array of its digits.
2. Brute force on every digit to get the maximum number.
```

</details>

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

<details><summary>Python3</summary>

```python
class Solution:
    def maximum69Number(self, num: int) -> int:
        retVal = num

        base = 0
        if retVal != 0:
            base = 10 ** int(log10(retVal))

        while base > 0:
            if (retVal // base) % 10 == 6:
                retVal += 3 * base
                break
            base = base // 10

        return retVal
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
