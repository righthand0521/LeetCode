# Math

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

## [3304. Find the K-th Character in String Game I](https://leetcode.com/problems/find-the-k-th-character-in-string-game-i/)  1288

- [Official](https://leetcode.com/problems/find-the-k-th-character-in-string-game-i/editorial/)
- [Official](https://leetcode.cn/problems/find-the-k-th-character-in-string-game-i/solutions/3708678/zhao-chu-di-k-ge-zi-fu-i-by-leetcode-sol-9epa/)

<details><summary>Description</summary>

```text
Alice and Bob are playing a game. Initially, Alice has a string word = "a".

You are given a positive integer k.

Now Bob will ask Alice to perform the following operation forever:
- Generate a new string by changing each character in word to its next character in the English alphabet,
  and append it to the original word.

For example, performing the operation on "c" generates "cd" and performing the operation on "zb" generates "zbac".

Return the value of the kth character in word,
after enough operations have been done for word to have at least k characters.

Note that the character 'z' can be changed to 'a' in the operation.

Example 1:
Input: k = 5
Output: "b"
Explanation:
Initially, word = "a". We need to do the operation three times:
Generated string is "b", word becomes "ab".
Generated string is "bc", word becomes "abbc".
Generated string is "bccd", word becomes "abbcbccd".

Example 2:
Input: k = 10
Output: "c"

Constraints:
1 <= k <= 500
```

<details><summary>Hint</summary>

```text
1. The constraints are small. Construct the string by simulating the operations.
```

</details>

</details>

<details><summary>C</summary>

```c
char kthCharacter(int k) {
    char retVal;

    int ans = 0;
    while (k != 1) {
        int shift = 31 - __builtin_clz(k);
        if ((1 << shift) == k) {
            shift--;
        }
        k = k - (1 << shift);
        ans++;
    }
    retVal = 'a' + ans;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    char kthCharacter(int k) {
        char retVal;

        int ans = 0;
        while (k != 1) {
            int shift = __lg(k);
            if ((1 << shift) == k) {
                shift--;
            }
            k = k - (1 << shift);
            ans++;
        }
        retVal = 'a' + ans;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def kthCharacter(self, k: int) -> str:
        retVal = ""

        ans = 0
        while k != 1:
            shift = k.bit_length() - 1
            if (1 << shift) == k:
                shift -= 1
            k -= (1 << shift)
            ans += 1
        retVal = chr(ord("a") + ans)

        return retVal
```

</details>

## [3307. Find the K-th Character in String Game II](https://leetcode.com/problems/find-the-k-th-character-in-string-game-ii/)  2232

- [Official](https://leetcode.com/problems/find-the-k-th-character-in-string-game-ii/editorial/)
- [Official](https://leetcode.cn/problems/find-the-k-th-character-in-string-game-ii/solutions/3708679/zhao-chu-di-k-ge-zi-fu-ii-by-leetcode-so-kx1d/)

<details><summary>Description</summary>

```text
Alice and Bob are playing a game. Initially, Alice has a string word = "a".

You are given a positive integer k.
You are also given an integer array operations, where operations[i] represents the type of the ith operation.

Now Bob will ask Alice to perform all operations in sequence:
- If operations[i] == 0, append a copy of word to itself.
- If operations[i] == 1,
  generate a new string by changing each character in word to its next character in the English alphabet,
  and append it to the original word.
  For example, performing the operation on "c" generates "cd" and performing the operation on "zb" generates "zbac".

Return the value of the kth character in word after performing all the operations.

Note that the character 'z' can be changed to 'a' in the second type of operation.

Example 1:
Input: k = 5, operations = [0,0,0]
Output: "a"
Explanation:
Initially, word == "a". Alice performs the three operations as follows:
Appends "a" to "a", word becomes "aa".
Appends "aa" to "aa", word becomes "aaaa".
Appends "aaaa" to "aaaa", word becomes "aaaaaaaa".

Example 2:
Input: k = 10, operations = [0,1,0,1]
Output: "b"
Explanation:
Initially, word == "a". Alice performs the four operations as follows:
Appends "a" to "a", word becomes "aa".
Appends "bb" to "aa", word becomes "aabb".
Appends "aabb" to "aabb", word becomes "aabbaabb".
Appends "bbccbbcc" to "aabbaabb", word becomes "aabbaabbbbccbbcc".

Constraints:
1 <= k <= 10^14
1 <= operations.length <= 100
operations[i] is either 0 or 1.
The input is generated such that word has at least k characters after all operations.
```

<details><summary>Hint</summary>

```text
1. Try to replay the operations kth character was part of.
2. The kth character is only affected if it is present in the first half of the string.
```

</details>

</details>

<details><summary>C</summary>

```c
char kthCharacter(long long k, int* operations, int operationsSize) {
    char retVal;

    int ans = 0;
    k--;
    for (int i = (int)log2(k); i >= 0; i--) {
        if ((k >> i) & 1) {
            ans += operations[i];
        }
    }
    retVal = 'a' + (ans % 26);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    char kthCharacter(long long k, vector<int>& operations) {
        char retVal;

        int ans = 0;
        k--;
        for (int i = __lg(k); i >= 0; i--) {
            if (k >> i & 1) {
                ans += operations[i];
            }
        }
        retVal = 'a' + (ans % 26);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def kthCharacter(self, k: int, operations: List[int]) -> str:
        retVal = ""

        ans = 0
        k -= 1
        for i in range(k.bit_length() - 1, -1, -1):
            if (k >> i) & 1:
                ans += operations[i]
        retVal = chr(ord("a") + (ans % 26))

        return retVal
```

</details>

## [3405. Count the Number of Arrays with K Matching Adjacent Elements](https://leetcode.com/problems/count-the-number-of-arrays-with-k-matching-adjacent-elements/)  2309

- [Official](https://leetcode.com/problems/count-the-number-of-arrays-with-k-matching-adjacent-elements/editorial/)
- [Official](https://leetcode.cn/problems/count-the-number-of-arrays-with-k-matching-adjacent-elements/solutions/3693518/tong-ji-qia-hao-you-k-ge-xiang-deng-xian-uxt4/)

<details><summary>Description</summary>

```text
You are given three integers n, m, k. A good array arr of size n is defined as follows:
- Each element in arr is in the inclusive range [1, m].
- Exactly k indices i (where 1 <= i < n) satisfy the condition arr[i - 1] == arr[i].

Return the number of good arrays that can be formed.

Since the answer may be very large, return it modulo 109 + 7.

Example 1:
Input: n = 3, m = 2, k = 1
Output: 4
Explanation:
There are 4 good arrays. They are [1, 1, 2], [1, 2, 2], [2, 1, 1] and [2, 2, 1].
Hence, the answer is 4.

Example 2:
Input: n = 4, m = 2, k = 2
Output: 6
Explanation:
The good arrays are [1, 1, 1, 2], [1, 1, 2, 2], [1, 2, 2, 2], [2, 1, 1, 1], [2, 2, 1, 1] and [2, 2, 2, 1].
Hence, the answer is 6.

Example 3:
Input: n = 5, m = 2, k = 0
Output: 2
Explanation:
The good arrays are [1, 2, 1, 2, 1] and [2, 1, 2, 1, 2]. Hence, the answer is 2.

Constraints:
1 <= n <= 10^5
1 <= m <= 10^5
0 <= k <= n - 1
```

<details><summary>Hint</summary>

```text
1. The first position arr[0] has m choices.
2. For each of the remaining n - 1 indices, 0 < i < n, select k positions from left to right and set arr[i] = arr[i - 1].
3. For all other indices, set arr[i] != arr[i - 1] with (m - 1) choices for each of the n - 1 - k positions.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MODULO (int)(1e9 + 7)
#define MAX_NUMBER (int)(1e5)  // 1 <= n <= 10^5, 1 <= m <= 10^5
long long factory[MAX_NUMBER];
long long incertFactory[MAX_NUMBER];
long long qpower(long long x, int n) {
    long long retVal = 1;

    while (n) {
        if (n & 1) {
            retVal = retVal * x % MODULO;
        }
        x = x * x % MODULO;
        n >>= 1;
    }

    return retVal;
}
long long combine(int n, int m) {
    long long retVal = factory[n] * incertFactory[m] % MODULO * incertFactory[n - m] % MODULO;

    return retVal;
}
int countGoodArrays(int n, int m, int k) {
    int retVal = 0;

    if (factory[0] == 0) {
        factory[0] = 1;
        for (int i = 1; i < MAX_NUMBER; i++) {
            factory[i] = factory[i - 1] * i % MODULO;
        }

        incertFactory[MAX_NUMBER - 1] = qpower(factory[MAX_NUMBER - 1], MODULO - 2);
        for (int i = MAX_NUMBER - 1; i > 0; i--) {
            incertFactory[i - 1] = incertFactory[i] * i % MODULO;
        }
    }
    retVal = combine(n - 1, k) * m % MODULO * qpower(m - 1, n - k - 1) % MODULO;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
static const int maxNumber = 1e5;  // // 1 <= n <= 10^5, 1 <= m <= 10^5
vector<long long> factory(maxNumber);
vector<long long> incertFactory(maxNumber);
class Solution {
   private:
    static constexpr int MODULO = 1e9 + 7;

    long long qpower(long long x, int n) {
        long long retVal = 1;

        while (n) {
            if (n & 1) {
                retVal = retVal * x % MODULO;
            }
            x = x * x % MODULO;
            n >>= 1;
        }

        return retVal;
    }
    long long combine(int n, int m) {
        long long retVal = factory[n] * incertFactory[m] % MODULO * incertFactory[n - m] % MODULO;

        return retVal;
    }

   public:
    int countGoodArrays(int n, int m, int k) {
        int retVal = 0;

        if (factory[0] == 0) {
            factory[0] = 1;
            for (int i = 1; i < maxNumber; i++) {
                factory[i] = factory[i - 1] * i % MODULO;
            }

            incertFactory[maxNumber - 1] = qpower(factory[maxNumber - 1], MODULO - 2);
            for (int i = maxNumber - 1; i; i--) {
                incertFactory[i - 1] = incertFactory[i] * i % MODULO;
            }
        }
        retVal = combine(n - 1, k) * m % MODULO * qpower(m - 1, n - k - 1) % MODULO;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
maxNumber = 10**5  # 1 <= n <= 10^5, 1 <= m <= 10^5
factory = [0] * maxNumber
incertFactory = [0] * maxNumber


class Solution:
    def __init__(self):
        self.MODULO = 10 ** 9 + 7

    def qpower(self, x, n):
        retVal = 1

        while n:
            if n & 1:
                retVal = retVal * x % self.MODULO
            x = x * x % self.MODULO
            n >>= 1

        return retVal

    def combine(self, n, m):
        retVal = factory[n] * incertFactory[m] % self.MODULO * incertFactory[n - m] % self.MODULO

        return retVal

    def countGoodArrays(self, n: int, m: int, k: int) -> int:
        retVal = 0

        if factory[0] == 0:
            factory[0] = 1
            for i in range(1, maxNumber):
                factory[i] = factory[i - 1] * i % self.MODULO

            incertFactory[maxNumber - 1] = self.qpower(factory[maxNumber - 1], self.MODULO - 2)
            for i in range(maxNumber - 1, 0, -1):
                incertFactory[i - 1] = incertFactory[i] * i % self.MODULO

        retVal = self.combine(n - 1, k) * m % self.MODULO * self.qpower(m - 1, n - k - 1) % self.MODULO

        return retVal
```

</details>

## [3443. Maximum Manhattan Distance After K Changes](https://leetcode.com/problems/maximum-manhattan-distance-after-k-changes/)  1855

- [Official](https://leetcode.com/problems/maximum-manhattan-distance-after-k-changes/editorial/)
- [Official](https://leetcode.cn/problems/maximum-manhattan-distance-after-k-changes/solutions/3688589/kci-xiu-gai-hou-de-zui-da-man-ha-dun-ju-q5twm/)

<details><summary>Description</summary>

```text
You are given a string s consisting of the characters 'N', 'S', 'E', and 'W',
where s[i] indicates movements in an infinite grid:
- 'N' : Move north by 1 unit.
- 'S' : Move south by 1 unit.
- 'E' : Move east by 1 unit.
- 'W' : Move west by 1 unit.

Initially, you are at the origin (0, 0). You can change at most k characters to any of the four directions.

Find the maximum Manhattan distance from the origin
that can be achieved at any time while performing the movements in order.

The Manhattan Distance between two cells (xi, yi) and (xj, yj) is |xi - xj| + |yi - yj|.

Example 1:
Input: s = "NWSE", k = 1
Output: 3
Explanation:
Change s[2] from 'S' to 'N'. The string s becomes "NWNE".
Movement Position (x, y) Manhattan Distance Maximum
s[0] == 'N' (0, 1) 0 + 1 = 1 1
s[1] == 'W' (-1, 1) 1 + 1 = 2 2
s[2] == 'N' (-1, 2) 1 + 2 = 3 3
s[3] == 'E' (0, 2) 0 + 2 = 2 3
The maximum Manhattan distance from the origin that can be achieved is 3. Hence, 3 is the output.

Example 2:
Input: s = "NSWWEW", k = 3
Output: 6
Explanation:
Change s[1] from 'S' to 'N', and s[4] from 'E' to 'W'. The string s becomes "NNWWWW".
The maximum Manhattan distance from the origin that can be achieved is 6. Hence, 6 is the output.

Constraints:
1 <= s.length <= 10^5
0 <= k <= s.length
s consists of only 'N', 'S', 'E', and 'W'.
```

<details><summary>Hint</summary>

```text
1. We can brute force all the possible directions (NE, NW, SE, SW).
2. Change up to k characters to maximize the distance in the chosen direction.
```

</details>

</details>

<details><summary>C</summary>

```c
int maxDistance(char* s, int k) {
    int retVal = 0;

    int latitude = 0;
    int longitude = 0;
    int sSize = strlen(s);
    for (int i = 0; i < sSize; i++) {
        switch (s[i]) {
            case 'N':
                latitude++;
                break;
            case 'S':
                latitude--;
                break;
            case 'E':
                longitude++;
                break;
            case 'W':
                longitude--;
                break;
        }
        retVal = fmax(retVal, fmin(abs(latitude) + abs(longitude) + k * 2, i + 1));
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxDistance(string s, int k) {
        int retVal = 0;

        int latitude = 0;
        int longitude = 0;
        int sSize = s.size();
        for (int i = 0; i < sSize; i++) {
            switch (s[i]) {
                case 'N':
                    latitude++;
                    break;
                case 'S':
                    latitude--;
                    break;
                case 'E':
                    longitude++;
                    break;
                case 'W':
                    longitude--;
                    break;
            }
            retVal = max(retVal, min(abs(latitude) + abs(longitude) + k * 2, i + 1));
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxDistance(self, s: str, k: int) -> int:
        retVal = 0

        latitude = 0
        longitude = 0
        sSize = len(s)
        for i in range(sSize):
            if s[i] == "N":
                latitude += 1
            elif s[i] == "S":
                latitude -= 1
            elif s[i] == "E":
                longitude += 1
            elif s[i] == "W":
                longitude -= 1
            retVal = max(retVal, min(abs(latitude) + abs(longitude) + k * 2, i + 1))

        return retVal
```

</details>
