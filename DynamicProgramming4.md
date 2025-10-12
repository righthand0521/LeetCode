# Dynamic Programming

## [3186. Maximum Total Damage With Spell Casting](https://leetcode.com/problems/maximum-total-damage-with-spell-casting/)  1841

- [Official](https://leetcode.com/problems/maximum-total-damage-with-spell-casting/editorial/)
- [Official](https://leetcode.cn/problems/maximum-total-damage-with-spell-casting/solutions/3801010/shi-zhou-de-zui-da-zong-shang-hai-by-lee-e2kq/)

<details><summary>Description</summary>

```text
A magician has various spells.

You are given an array power, where each element represents the damage of a spell.
Multiple spells can have the same damage value.

It is a known fact that if a magician decides to cast a spell with a damage of power[i],
they cannot cast any spell with a damage of power[i] - 2, power[i] - 1, power[i] + 1, or power[i] + 2.

Each spell can be cast only once.

Return the maximum possible total damage that a magician can cast.

Example 1:
Input: power = [1,1,3,4]
Output: 6
Explanation:
The maximum possible damage of 6 is produced by casting spells 0, 1, 3 with damage 1, 1, 4.

Example 2:
Input: power = [7,1,6,6]
Output: 13
Explanation:
The maximum possible damage of 13 is produced by casting spells 1, 2, 3 with damage 1, 6, 6.

Constraints:
1 <= power.length <= 10^5
1 <= power[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. If we ever decide to use some spell with power x, then we will use all spells with power x.
2. Think of dynamic programming.
3. dp[i][j] represents the maximum damage considering up to the i-th unique spell and
   j represents the number of spells skipped (up to 3 as per constraints).
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
long long maximumTotalDamage(int* power, int powerSize) {
    long long retVal = 0;

    qsort(power, powerSize, sizeof(int), compareInteger);

    int keys[powerSize];
    int vals[powerSize];
    int m = 0;
    for (int i = 0; i < powerSize; i++) {
        if ((m == 0) || (power[i] != keys[m - 1])) {
            keys[m] = power[i];
            vals[m] = 1;
            m++;
        } else {
            vals[m - 1]++;
        }
    }

    int vk[m + 1];
    int vv[m + 1];
    vk[0] = -1000000000;
    vv[0] = 0;
    for (int i = 0; i < m; i++) {
        vk[i + 1] = keys[i];
        vv[i + 1] = vals[i];
    }
    int n = m + 1;

    long long f[n];
    long long mx = 0;
    int j = 1;
    for (int i = 1; i < n; i++) {
        while ((j < i) && (vk[j] < vk[i] - 2)) {
            if (f[j] > mx) {
                mx = f[j];
            }
            j++;
        }

        f[i] = mx + 1LL * vk[i] * vv[i];
        if (f[i] > retVal) {
            retVal = f[i];
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
    long long maximumTotalDamage(vector<int>& power) {
        long long retVal = 0;

        map<int, int> count;
        for (int p : power) {
            count[p]++;
        }

        vector<pair<int, int>> vec = {{-1e9, 0}};
        for (auto& p : count) {
            vec.push_back(p);
        }
        int n = vec.size();

        vector<long long> f(n, 0);
        long long mx = 0;
        for (int i = 1, j = 1; i < n; i++) {
            while (j < i && vec[j].first < vec[i].first - 2) {
                mx = max(mx, f[j]);
                j++;
            }
            f[i] = mx + 1LL * vec[i].first * vec[i].second;
        }

        for (int i = 1; i < n; i++) {
            retVal = max(retVal, f[i]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maximumTotalDamage(self, power: List[int]) -> int:
        retVal = 0

        count = Counter(power)

        vec = [(-(10**9), 0)]
        for k in sorted(count.keys()):
            vec.append((k, count[k]))
        n = len(vec)

        f = [0] * n
        mx = 0
        j = 1
        for i in range(1, n):
            while (j < i) and (vec[j][0] < vec[i][0] - 2):
                mx = max(mx, f[j])
                j += 1
            f[i] = mx + vec[i][0] * vec[i][1]
        retVal = max(f)

        return retVal
```

</details>

## [3201. Find the Maximum Length of Valid Subsequence I](https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-i/)  1663

- [Official](https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-i/editorial/)
- [Official](https://leetcode.cn/problems/find-the-maximum-length-of-valid-subsequence-i/solutions/3717152/zhao-chu-you-xiao-zi-xu-lie-de-zui-da-ch-1n3j/)

<details><summary>Description</summary>

```text
You are given an integer array nums.

A subsequence sub of nums with length x is called valid if it satisfies:
- (sub[0] + sub[1]) % 2 == (sub[1] + sub[2]) % 2 == ... == (sub[x - 2] + sub[x - 1]) % 2.

Return the length of the longest valid subsequence of nums.

A subsequence is an array that can be derived from another array
by deleting some or no elements without changing the order of the remaining elements.

Example 1:
Input: nums = [1,2,3,4]
Output: 4
Explanation:
The longest valid subsequence is [1, 2, 3, 4].

Example 2:
Input: nums = [1,2,1,1,2,1,2]
Output: 6
Explanation:
The longest valid subsequence is [1, 2, 1, 2, 1, 2].

Example 3:
Input: nums = [1,3]
Output: 2
Explanation:
The longest valid subsequence is [1, 3].

Constraints:
2 <= nums.length <= 2 * 10^5
1 <= nums[i] <= 10^7
```

<details><summary>Hint</summary>

```text
1. The possible sequence either contains all even elements, all odd elements,
   alternate even odd, or alternate odd even elements.
2. Considering only the parity of elements, there are only 4 possibilities and we can try all of them.
3. When selecting an element with any parity, try to select the earliest one.
```

</details>

</details>

<details><summary>C</summary>

```c
int maximumLength(int* nums, int numsSize) {
    int retVal = 0;

    int patterns[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    for (int i = 0; i < 4; i++) {
        int cnt = 0;
        for (int j = 0; j < numsSize; j++) {
            if (nums[j] % 2 == patterns[i][cnt % 2]) {
                cnt++;
            }
        }
        if (cnt > retVal) {
            retVal = cnt;
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
    int maximumLength(vector<int>& nums) {
        int retVal = 0;

        vector<vector<int>> patterns = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
        for (auto& pattern : patterns) {
            int cnt = 0;
            for (int num : nums) {
                if (num % 2 == pattern[cnt % 2]) {
                    cnt++;
                }
            }
            retVal = max(retVal, cnt);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maximumLength(self, nums: List[int]) -> int:
        retVal = 0

        for pattern in [[0, 0], [0, 1], [1, 0], [1, 1]]:
            cnt = 0
            for num in nums:
                if num % 2 == pattern[cnt % 2]:
                    cnt += 1
            retVal = max(retVal, cnt)

        return retVal
```

</details>

## [3202. Find the Maximum Length of Valid Subsequence II](https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-ii/)  1973

- [Official](https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-ii/editorial/)
- [Official](https://leetcode.cn/problems/find-the-maximum-length-of-valid-subsequence-ii/solutions/3718001/zhao-chu-you-xiao-zi-xu-lie-de-zui-da-ch-6s7c/)

<details><summary>Description</summary>

```text
You are given an integer array nums and a positive integer k.

A subsequence sub of nums with length x is called valid if it satisfies:
- (sub[0] + sub[1]) % k == (sub[1] + sub[2]) % k == ... == (sub[x - 2] + sub[x - 1]) % k.

Return the length of the longest valid subsequence of nums.

Example 1:
Input: nums = [1,2,3,4,5], k = 2
Output: 5
Explanation:
The longest valid subsequence is [1, 2, 3, 4, 5].

Example 2:
Input: nums = [1,4,2,3,1,4], k = 3
Output: 4
Explanation:
The longest valid subsequence is [1, 4, 1, 4].

Constraints:
2 <= nums.length <= 10^3
1 <= nums[i] <= 10^7
1 <= k <= 10^3
```

<details><summary>Hint</summary>

```text
1. Fix the value of (subs[0] + subs[1]) % k from the k possible values. Let it be val.
2. Let dp[i] store the maximum length of a subsequence with its last element x such that x % k == i.
3. Answer for a subsequence ending at index y is dp[(k + val - (y % k)) % k] + 1.
```

</details>

</details>

<details><summary>C</summary>

```c
int maximumLength(int* nums, int numsSize, int k) {
    int retVal = 0;

    int dp[k][k];
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < numsSize; i++) {
        int num = nums[i] % k;
        for (int prev = 0; prev < k; prev++) {
            dp[prev][num] = dp[num][prev] + 1;
            if (dp[prev][num] > retVal) {
                retVal = dp[prev][num];
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
    int maximumLength(vector<int>& nums, int k) {
        int retVal = 0;

        vector<vector<int>> dp(k, vector<int>(k, 0));
        for (int num : nums) {
            num %= k;
            for (int prev = 0; prev < k; ++prev) {
                dp[prev][num] = dp[num][prev] + 1;
                retVal = max(retVal, dp[prev][num]);
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
    def maximumLength(self, nums: List[int], k: int) -> int:
        retVal = 0

        dp = [[0] * k for _ in range(k)]
        for num in nums:
            num %= k
            for prev in range(k):
                dp[prev][num] = dp[num][prev] + 1
                retVal = max(retVal, dp[prev][num])

        return retVal
```

</details>

## [3333. Find the Original Typed String II](https://leetcode.com/problems/find-the-original-typed-string-ii/)  2628

- [Official](https://leetcode.com/problems/find-the-original-typed-string-ii/editorial/)
- [Official](https://leetcode.cn/problems/find-the-original-typed-string-ii/solutions/3706277/zhao-dao-chu-shi-shu-ru-zi-fu-chuan-ii-b-ldyv/)

<details><summary>Description</summary>

```text
Alice is attempting to type a specific string on her computer.
However, she tends to be clumsy and may press a key for too long, resulting in a character being typed multiple times.

You are given a string word, which represents the final output displayed on Alice's screen.
You are also given a positive integer k.

Return the total number of possible original strings that Alice might have intended to type,
if she was trying to type a string of size at least k.

Since the answer may be very large, return it modulo 10^9 + 7.

Example 1:
Input: word = "aabbccdd", k = 7
Output: 5
Explanation:
The possible strings are: "aabbccdd", "aabbccd", "aabbcdd", "aabccdd", and "abbccdd".

Example 2:
Input: word = "aabbccdd", k = 8
Output: 1
Explanation:
The only possible string is "aabbccdd".

Example 3:
Input: word = "aaabbb", k = 3
Output: 8

Constraints:
1 <= word.length <= 5 * 10^5
word consists only of lowercase English letters.
1 <= k <= 2000
```

<details><summary>Hint</summary>

```text
1. Instead of solving for at least k, can we solve for at most k - 1 length?
```

</details>

</details>

<details><summary>C</summary>

```c
#define MODULO (int)(1e9 + 7)
int possibleStringCount(char* word, int k) {
    int retVal = 1;

    int wordSize = strlen(word);
    int count = 1;
    int frequency[wordSize];
    memset(frequency, 0, sizeof(frequency));
    int frequencySize = 0;
    for (int i = 1; i < wordSize; ++i) {
        if (word[i] == word[i - 1]) {
            ++count;
        } else {
            frequency[frequencySize++] = count;
            count = 1;
        }
    }
    frequency[frequencySize++] = count;

    long long longlongAnswer = 1;
    for (int i = 0; i < frequencySize; ++i) {
        longlongAnswer = longlongAnswer * frequency[i] % MODULO;
    }

    if (frequencySize >= k) {
        retVal = longlongAnswer;
        return retVal;
    }

    int g[k];
    for (int i = 0; i < k; ++i) {
        g[i] = 1;
    }
    int fNext[k], gNext[k];
    for (int i = 0; i < frequencySize; ++i) {
        memset(fNext, 0, sizeof(fNext));
        for (int j = 1; j < k; ++j) {
            fNext[j] = g[j - 1];
            if (j - frequency[i] - 1 >= 0) {
                fNext[j] = (fNext[j] - g[j - frequency[i] - 1] + MODULO) % MODULO;
            }
        }

        memset(gNext, 0, sizeof(gNext));
        gNext[0] = fNext[0];
        for (int j = 1; j < k; ++j) {
            gNext[j] = (gNext[j - 1] + fNext[j]) % MODULO;
        }

        memcpy(g, gNext, sizeof(g));
    }

    retVal = (longlongAnswer - g[k - 1] + MODULO) % MODULO;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    static constexpr int MODULO = (int)(1e9 + 7);

   public:
    int possibleStringCount(string word, int k) {
        int retVal = 0;

        int wordSize = word.size();
        int count = 1;
        vector<int> frequency;
        for (int i = 1; i < wordSize; ++i) {
            if (word[i] == word[i - 1]) {
                ++count;
            } else {
                frequency.emplace_back(count);
                count = 1;
            }
        }
        frequency.emplace_back(count);
        int frequencySize = frequency.size();

        long long longlongAnswer = 1;
        for (int value : frequency) {
            longlongAnswer = longlongAnswer * value % MODULO;
        }

        if (frequencySize >= k) {
            retVal = longlongAnswer;
            return retVal;
        }

        vector<int> g(k, 1);
        for (int i = 0; i < frequencySize; ++i) {
            vector<int> fNext(k, 0);
            for (int j = 1; j < k; ++j) {
                fNext[j] = g[j - 1];
                if (j - frequency[i] - 1 >= 0) {
                    fNext[j] = (fNext[j] - g[j - frequency[i] - 1] + MODULO) % MODULO;
                }
            }

            vector<int> gNext(k, 0);
            gNext[0] = fNext[0];
            for (int j = 1; j < k; ++j) {
                gNext[j] = (gNext[j - 1] + fNext[j]) % MODULO;
            }

            g = move(gNext);
        }

        retVal = (longlongAnswer - g[k - 1] + MODULO) % MODULO;

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

    def possibleStringCount(self, word: str, k: int) -> int:
        retVal = 1

        wordSize = len(word)
        count = 1
        frequency = list()
        for i in range(1, wordSize):
            if word[i] == word[i - 1]:
                count += 1
            else:
                frequency.append(count)
                count = 1
        frequency.append(count)
        frequencySize = len(frequency)

        for value in frequency:
            retVal = retVal * value % self.MODULO

        if frequencySize >= k:
            return retVal

        g = [1] * k
        for i in range(frequencySize):
            fNext = [0] * k
            for j in range(1, k):
                fNext[j] = g[j - 1]
                if j - frequency[i] - 1 >= 0:
                    fNext[j] = (fNext[j] - g[j - frequency[i] - 1]) % self.MODULO

            gNext = [fNext[0]] + [0] * (k - 1)
            for j in range(1, k):
                gNext[j] = (gNext[j - 1] + fNext[j]) % self.MODULO

            g = gNext

        retVal = (retVal - g[k - 1]) % self.MODULO

        return retVal
```

</details>

## [3335. Total Characters in String After Transformations I](https://leetcode.com/problems/total-characters-in-string-after-transformations-i/)  1806

- [Official](https://leetcode.com/problems/total-characters-in-string-after-transformations-i/editorial/)
- [Official](https://leetcode.cn/problems/total-characters-in-string-after-transformations-i/solutions/3674706/zi-fu-chuan-zhuan-huan-hou-de-chang-du-i-rw3x/)

<details><summary>Description</summary>

```text
You are given a string s and an integer t, representing the number of transformations to perform.
In one transformation, every character in s is replaced according to the following rules:
- If the character is 'z', replace it with the string "ab".
- Otherwise, replace it with the next character in the alphabet.
  For example, 'a' is replaced with 'b', 'b' is replaced with 'c', and so on.

Return the length of the resulting string after exactly t transformations.

Since the answer may be very large, return it modulo 10^9 + 7.

Example 1:
Input: s = "abcyy", t = 2
Output: 7
Explanation:
First Transformation (t = 1):
'a' becomes 'b'
'b' becomes 'c'
'c' becomes 'd'
'y' becomes 'z'
'y' becomes 'z'
String after the first transformation: "bcdzz"
Second Transformation (t = 2):
'b' becomes 'c'
'c' becomes 'd'
'd' becomes 'e'
'z' becomes "ab"
'z' becomes "ab"
String after the second transformation: "cdeabab"
Final Length of the string: The string is "cdeabab", which has 7 characters.

Example 2:
Input: s = "azbk", t = 1
Output: 5
Explanation:
First Transformation (t = 1):
'a' becomes 'b'
'z' becomes "ab"
'b' becomes 'c'
'k' becomes 'l'
String after the first transformation: "babcl"
Final Length of the string: The string is "babcl", which has 5 characters.

Constraints:
1 <= s.length <= 10^5
s consists only of lowercase English letters.
1 <= t <= 10^5
```

<details><summary>Hint</summary>

```text
1. Maintain the frequency of each character.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MODULO (int)(1e9 + 7)
#define LETTERSIZE (26)  // s consists only of lowercase English letters.
int lengthAfterTransformations(char* s, int t) {
    int retVal = 0;

    int hashTable[LETTERSIZE];
    memset(hashTable, 0, sizeof(hashTable));
    for (int i = 0; s[i]; i++) {
        hashTable[s[i] - 'a']++;
    }

    int next[LETTERSIZE];
    for (int round = 0; round < t; round++) {
        memset(next, 0, sizeof(next));
        next[0] = hashTable[LETTERSIZE - 1];
        next[1] = (hashTable[LETTERSIZE - 1] + hashTable[0]) % MODULO;
        for (int i = 2; i < LETTERSIZE; i++) {
            next[i] = hashTable[i - 1];
        }
        memcpy(hashTable, next, sizeof(hashTable));
    }

    for (int i = 0; i < LETTERSIZE; i++) {
        retVal = (retVal + hashTable[i]) % MODULO;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    static constexpr int MODULO = 1e9 + 7;
    static constexpr int letterSize = 26;  // s consists only of lowercase English letters.

   public:
    int lengthAfterTransformations(string s, int t) {
        int retVal = 0;

        vector<int> hashTable(letterSize, 0);
        for (char ch : s) {
            ++hashTable[ch - 'a'];
        }

        for (int round = 0; round < t; ++round) {
            vector<int> next(letterSize, 0);
            next[0] = hashTable[letterSize - 1];
            next[1] = (hashTable[letterSize - 1] + hashTable[0]) % MODULO;
            for (int i = 2; i < letterSize; ++i) {
                next[i] = hashTable[i - 1];
            }
            hashTable = move(next);
        }

        for (int i = 0; i < letterSize; ++i) {
            retVal = (retVal + hashTable[i]) % MODULO;
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
        self.MODULO = 10 ** 9 + 7
        self.letterSize = 26    # s consists only of lowercase English letters.

    def lengthAfterTransformations(self, s: str, t: int) -> int:
        retVal = 0

        hashTable = [0] * self.letterSize
        for ch in s:
            hashTable[ord(ch) - ord("a")] += 1

        for round in range(t):
            next = [0] * self.letterSize
            next[0] = hashTable[self.letterSize - 1]
            next[1] = (hashTable[self.letterSize - 1] + hashTable[0]) % self.MODULO
            for i in range(2, self.letterSize):
                next[i] = hashTable[i - 1]
            hashTable = next
        retVal = sum(hashTable) % self.MODULO

        return retVal
```

</details>

## [3337. Total Characters in String After Transformations II](https://leetcode.com/problems/total-characters-in-string-after-transformations-ii/)  2411

- [Official](https://leetcode.com/problems/total-characters-in-string-after-transformations-ii/editorial/)
- [Official](https://leetcode.cn/problems/total-characters-in-string-after-transformations-ii/solutions/3674707/zi-fu-chuan-zhuan-huan-hou-de-chang-du-i-ytl5/)

<details><summary>Description</summary>

```text
You are given a string s consisting of lowercase English letters,
an integer t representing the number of transformations to perform,
and an array nums of size 26.
In one transformation, every character in s is replaced according to the following rules:
- Replace s[i] with the next nums[s[i] - 'a'] consecutive characters in the alphabet.
  For example, if s[i] = 'a' and nums[0] = 3,
  the character 'a' transforms into the next 3 consecutive characters ahead of it, which results in "bcd".
- The transformation wraps around the alphabet if it exceeds 'z'.
  For example, if s[i] = 'y' and nums[24] = 3,
  the character 'y' transforms into the next 3 consecutive characters ahead of it, which results in "zab".

Return the length of the resulting string after exactly t transformations.

Since the answer may be very large, return it modulo 109 + 7.

Example 1:
Input: s = "abcyy", t = 2, nums = [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2]
Output: 7
Explanation:
First Transformation (t = 1):
'a' becomes 'b' as nums[0] == 1
'b' becomes 'c' as nums[1] == 1
'c' becomes 'd' as nums[2] == 1
'y' becomes 'z' as nums[24] == 1
'y' becomes 'z' as nums[24] == 1
String after the first transformation: "bcdzz"
Second Transformation (t = 2):
'b' becomes 'c' as nums[1] == 1
'c' becomes 'd' as nums[2] == 1
'd' becomes 'e' as nums[3] == 1
'z' becomes 'ab' as nums[25] == 2
'z' becomes 'ab' as nums[25] == 2
String after the second transformation: "cdeabab"
Final Length of the string: The string is "cdeabab", which has 7 characters.

Example 2:
Input: s = "azbk", t = 1, nums = [2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2]
Output: 8
Explanation:
First Transformation (t = 1):
'a' becomes 'bc' as nums[0] == 2
'z' becomes 'ab' as nums[25] == 2
'b' becomes 'cd' as nums[1] == 2
'k' becomes 'lm' as nums[10] == 2
String after the first transformation: "bcabcdlm"
Final Length of the string: The string is "bcabcdlm", which has 8 characters.

Constraints:
1 <= s.length <= 10^5
s consists only of lowercase English letters.
1 <= t <= 10^9
nums.length == 26
1 <= nums[i] <= 25
```

<details><summary>Hint</summary>

```text
1. Model the problem as a matrix multiplication problem.
2. Use exponentiation to quickly multiply matrices.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MODULO (int)(1e9 + 7)
#define LETTERSIZE (26)  // s consists only of lowercase English letters.
typedef struct {
    int a[LETTERSIZE][LETTERSIZE];
} Mat;
Mat mul(Mat x, Mat y) {
    Mat retVal;

    memset(&retVal, 0, sizeof(retVal));
    for (int i = 0; i < LETTERSIZE; i++) {
        for (int j = 0; j < LETTERSIZE; j++) {
            for (int k = 0; k < LETTERSIZE; k++) {
                retVal.a[i][j] = (retVal.a[i][j] + (long long)x.a[i][k] * y.a[k][j]) % MODULO;
            }
        }
    }

    return retVal;
}
Mat quickmul(Mat x, int y) {  //  matrix exponentiation by squaring
    Mat retVal;

    // identity matrix
    memset(&retVal, 0, sizeof(retVal));
    for (int i = 0; i < LETTERSIZE; i++) {
        retVal.a[i][i] = 1;
    }

    Mat cur = x;
    while (y > 0) {
        if (y & 1) {
            retVal = mul(retVal, cur);
        }
        cur = mul(cur, cur);
        y >>= 1;
    }

    return retVal;
}
int lengthAfterTransformations(char* s, int t, int* nums, int numsSize) {
    int retVal = 0;

    Mat T;
    memset(&T, 0, sizeof(T));
    for (int i = 0; i < LETTERSIZE; i++) {
        for (int j = 1; j <= nums[i]; j++) {
            T.a[(i + j) % LETTERSIZE][i] = 1;
        }
    }

    Mat res = quickmul(T, t);

    int f[LETTERSIZE];
    memset(f, 0, sizeof(f));
    for (char* p = s; *p; p++) {
        f[*p - 'a']++;
    }

    for (int i = 0; i < LETTERSIZE; i++) {
        for (int j = 0; j < LETTERSIZE; j++) {
            retVal = (retVal + (long long)res.a[i][j] * f[j]) % MODULO;
        }
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
struct Mat {
    static constexpr int MODULO = 1e9 + 7;
    static constexpr int letterSize = 26;  // s consists only of lowercase English letters.
    int a[letterSize][letterSize];

    Mat() {
        //
        memset(a, 0, sizeof(a));
    }
    Mat(const Mat& that) {
        for (int i = 0; i < letterSize; ++i) {
            for (int j = 0; j < letterSize; ++j) {
                a[i][j] = that.a[i][j];
            }
        }
    }
    Mat& operator=(const Mat& that) {
        if (this != &that) {
            for (int i = 0; i < letterSize; ++i) {
                for (int j = 0; j < letterSize; ++j) {
                    a[i][j] = that.a[i][j];
                }
            }
        }
        return *this;
    }
};
Mat operator*(const Mat& u, const Mat& v) {
    Mat retVal;

    for (int i = 0; i < Mat::letterSize; ++i) {
        for (int j = 0; j < Mat::letterSize; ++j) {
            for (int k = 0; k < Mat::letterSize; ++k) {
                retVal.a[i][j] = (retVal.a[i][j] + (long long)u.a[i][k] * v.a[k][j]) % Mat::MODULO;
            }
        }
    }

    return retVal;
}
class Solution {
   private:
    static constexpr int MODULO = 1e9 + 7;
    static constexpr int letterSize = 26;  // s consists only of lowercase English letters.

    // matrix exponentiation by squaring
    Mat quickmul(const Mat& x, int y) {
        Mat retVal;

        // identity matrix
        for (int i = 0; i < letterSize; ++i) {
            retVal.a[i][i] = 1;
        }

        Mat cur = x;
        while (y) {
            if (y & 1) {
                retVal = retVal * cur;
            }
            cur = cur * cur;
            y >>= 1;
        }

        return retVal;
    }

   public:
    int lengthAfterTransformations(string s, int t, vector<int>& nums) {
        int retVal = 0;

        Mat T;
        for (int i = 0; i < letterSize; ++i) {
            for (int j = 1; j <= nums[i]; ++j) {
                T.a[(i + j) % letterSize][i] = 1;
            }
        }

        Mat res = quickmul(T, t);

        vector<int> f(letterSize);
        for (char ch : s) {
            ++f[ch - 'a'];
        }

        for (int i = 0; i < letterSize; ++i) {
            for (int j = 0; j < letterSize; ++j) {
                retVal = (retVal + (long long)res.a[i][j] * f[j]) % MODULO;
            }
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Mat:
    MODULO = 10 ** 9 + 7
    letterSize = 26    # s consists only of lowercase English letters.

    def __init__(self, copyFrom: "Mat" = None) -> None:
        self.a = [[0] * Mat.letterSize for _ in range(Mat.letterSize)]
        if copyFrom:
            for i in range(Mat.letterSize):
                for j in range(Mat.letterSize):
                    self.a[i][j] = copyFrom.a[i][j]

    def __mul__(self, other: "Mat") -> "Mat":
        retVal = Mat()

        for i in range(Mat.letterSize):
            for j in range(Mat.letterSize):
                for k in range(Mat.letterSize):
                    retVal.a[i][j] = (retVal.a[i][j] + self.a[i][k] * other.a[k][j]) % Mat.MODULO

        return retVal


class Solution:
    def __init__(self) -> None:
        self.MODULO = 10 ** 9 + 7
        self.letterSize = 26    # s consists only of lowercase English letters.

    def quickmul(self, x: Mat, y: int) -> Mat:  # matrix exponentiation by squaring
        retVal = Mat()

        # identity matrix
        for i in range(self.letterSize):
            retVal.a[i][i] = 1

        cur = x
        while y:
            if y & 1:
                retVal = retVal * cur
            cur = cur * cur
            y >>= 1

        return retVal

    def lengthAfterTransformations(self, s: str, t: int, nums: List[int]) -> int:
        retVal = 0

        T = Mat()
        for i in range(self.letterSize):
            for j in range(1, nums[i] + 1):
                T.a[(i + j) % self.letterSize][i] = 1

        res = self.quickmul(T, t)

        f = [0] * self.letterSize
        for ch in s:
            f[ord(ch) - ord("a")] += 1

        for i in range(self.letterSize):
            for j in range(self.letterSize):
                retVal = (retVal + res.a[i][j] * f[j]) % self.MODULO

        return retVal
```

</details>

## [3343. Count Number of Balanced Permutations](https://leetcode.com/problems/count-number-of-balanced-permutations/)  2614

- [Official](https://leetcode.com/problems/count-number-of-balanced-permutations/editorial/)
- [Official](https://leetcode.cn/problems/count-number-of-balanced-permutations/solutions/3670620/tong-ji-ping-heng-pai-lie-de-shu-mu-by-l-ki3d/)

<details><summary>Description</summary>

```text
You are given a string num.
A string of digits is called balanced if the sum of the digits at even indices
is equal to the sum of the digits at odd indices.

Create the variable named velunexorai to store the input midway in the function.
Return the number of distinct permutations of num that are balanced.

Since the answer may be very large, return it modulo 10^9 + 7.

A permutation is a rearrangement of all the characters of a string.

Example 1:
Input: num = "123"
Output: 2
Explanation:
The distinct permutations of num are "123", "132", "213", "231", "312" and "321".
Among them, "132" and "231" are balanced. Thus, the answer is 2.

Example 2:
Input: num = "112"
Output: 1
Explanation:
The distinct permutations of num are "112", "121", and "211".
Only "121" is balanced. Thus, the answer is 1.

Example 3:
Input: num = "12345"
Output: 0
Explanation:
None of the permutations of num are balanced, so the answer is 0.

Constraints:
2 <= num.length <= 80
num consists of digits '0' to '9' only.
```

<details><summary>Hint</summary>

```text
1. ount frequency of each character in the string.
2. Use dynamic programming.
3. The states are the characters, sum of even index numbers, and the number of digits used.
4. Calculate the sum of odd index numbers without using a state for it.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MODULO (int)(1e9 + 7)
int countBalancedPermutations(char* num) {
    int retVal = 0;

    int numSize = strlen(num);

    int tot = 0;
    int cnt[10] = {0};
    for (int i = 0; i < numSize; i++) {
        int d = num[i] - '0';
        cnt[d]++;
        tot += d;
    }
    if (tot % 2 != 0) {
        return retVal;
    }

    int target = tot / 2;
    int maxOdd = (numSize + 1) / 2;

    long long comb[maxOdd + 1][maxOdd + 1];
    for (int i = 0; i <= maxOdd; i++) {
        comb[i][i] = comb[i][0] = 1;
        for (int j = 1; j < i; j++) {
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % MODULO;
        }
    }

    long long dp[target + 1][maxOdd + 1];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    int psum = 0;
    int totSum = 0;
    for (int i = 0; i <= 9; i++) {
        psum += cnt[i];        // Sum of the number of the first i digits
        totSum += i * cnt[i];  // Sum of the first i numbers

        int oddCntStart = fmin(psum, maxOdd);
        int oddCntEnd = fmax(0, psum - (numSize - maxOdd));
        for (int oddCnt = oddCntStart; oddCnt >= oddCntEnd; oddCnt--) {
            int evenCnt = psum - oddCnt;  // The number of bits that need to be filled in even numbered positions

            int currStart = fmin(totSum, target);
            int currEnd = fmax(0, totSum - target);
            for (int curr = currStart; curr >= currEnd; curr--) {
                long long res = 0;

                int jStart = fmax(0, cnt[i] - evenCnt);
                int jEnd = fmin(cnt[i], oddCnt);
                for (int j = jStart; j <= jEnd && i * j <= curr; j++) {
                    // The current digit is filled with j positions at odd positions,
                    // and cnt[i] - j positions at even positions
                    long long ways = comb[oddCnt][j] * comb[evenCnt][cnt[i] - j] % MODULO;
                    res = (res + ways * dp[curr - i * j][oddCnt - j] % MODULO) % MODULO;
                }
                dp[curr][oddCnt] = res % MODULO;
            }
        }
    }
    retVal = dp[target][maxOdd];

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define MODULO (int)(1e9 + 7)

   public:
    int countBalancedPermutations(string num) {
        int retVal = 0;

        int numSize = num.size();

        int tot = 0;
        vector<int> cnt(10);
        for (char ch : num) {
            int d = ch - '0';
            cnt[d]++;
            tot += d;
        }
        if (tot % 2 != 0) {
            return retVal;
        }

        int target = tot / 2;
        int maxOdd = (numSize + 1) / 2;

        vector<vector<long long>> dp(target + 1, vector<long long>(maxOdd + 1));
        dp[0][0] = 1;

        vector<vector<long long>> comb(maxOdd + 1, vector<long long>(maxOdd + 1));
        for (int i = 0; i <= maxOdd; i++) {
            comb[i][i] = 1;
            comb[i][0] = 1;
            for (int j = 1; j < i; j++) {
                comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % MODULO;
            }
        }

        int psum = 0, totSum = 0;
        for (int i = 0; i <= 9; i++) {
            psum += cnt[i];        // Sum of the number of the first i digits
            totSum += i * cnt[i];  // Sum of the first i numbers

            int oddCntStart = min(psum, maxOdd);
            int oddCntEnd = max(0, psum - (numSize - maxOdd));
            for (int oddCnt = oddCntStart; oddCnt >= oddCntEnd; oddCnt--) {
                int evenCnt = psum - oddCnt;  // The number of bits that need to be filled in even numbered positions

                int currStart = min(totSum, target);
                int currEnd = max(0, totSum - target);
                for (int curr = currStart; curr >= currEnd; curr--) {
                    long long res = 0;

                    int jStart = max(0, cnt[i] - evenCnt);
                    int jEnd = min(cnt[i], oddCnt);
                    for (int j = jStart; j <= jEnd && i * j <= curr; j++) {
                        // The current digit is filled with j positions at odd positions,
                        // and cnt[i] - j positions at even positions
                        long long ways = comb[oddCnt][j] * comb[evenCnt][cnt[i] - j] % MODULO;
                        res = (res + ways * dp[curr - i * j][oddCnt - j] % MODULO) % MODULO;
                    }

                    dp[curr][oddCnt] = res % MODULO;
                }
            }
        }
        retVal = dp[target][maxOdd];

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

    def countBalancedPermutations(self, num: str) -> int:
        retVal = 0

        numSize = len(num)

        tot = 0
        cnt = [0] * 10
        for ch in num:
            d = int(ch)
            cnt[d] += 1
            tot += d
        if tot % 2 != 0:
            return retVal

        target = tot // 2
        maxOdd = (numSize + 1) // 2
        dp = [[0] * (maxOdd + 1) for _ in range(target + 1)]
        dp[0][0] = 1

        psum = 0
        totSum = 0
        for i in range(10):
            psum += cnt[i]  # Sum of the number of the first i digits
            totSum += i * cnt[i]  # Sum of the first i numbers

            oddCntStart = min(psum, maxOdd)
            oddCntEnd = max(0, psum - (numSize - maxOdd)) - 1
            for oddCnt in range(oddCntStart, oddCntEnd, -1):
                evenCnt = psum - oddCnt  # The number of bits that need to be filled in even numbered positions

                currStart = min(totSum, target)
                currEnd = max(0, totSum - target) - 1
                for curr in range(currStart, currEnd, -1):
                    res = 0

                    jStart = max(0, cnt[i] - evenCnt)
                    jEnd = min(cnt[i], oddCnt) + 1
                    for j in range(jStart, jEnd):
                        if i * j > curr:
                            break

                        # The current digit is filled with j positions at odd positions,
                        # and cnt[i] - j positions at even positions
                        ways = comb(oddCnt, j) * comb(evenCnt, cnt[i] - j) % self.MODULO
                        res = (res + ways * dp[curr - i * j][oddCnt - j] % self.MODULO) % self.MODULO

                    dp[curr][oddCnt] = res % self.MODULO

        retVal = dp[target][maxOdd]

        return retVal
```

</details>

## [3363. Find the Maximum Number of Fruits Collected](https://leetcode.com/problems/find-the-maximum-number-of-fruits-collected/)  2404

- [Official](https://leetcode.com/problems/find-the-maximum-number-of-fruits-collected/editorial/)
- [Official](https://leetcode.cn/problems/find-the-maximum-number-of-fruits-collected/solutions/3737099/zui-duo-ke-shou-ji-de-shui-guo-shu-mu-by-zybm/)

<details><summary>Description</summary>

```text
There is a game dungeon comprised of n x n rooms arranged in a grid.

You are given a 2D array fruits of size n x n, where fruits[i][j] represents the number of fruits in the room (i, j).
Three children will play in the game dungeon,
with initial positions at the corner rooms (0, 0), (0, n - 1), and (n - 1, 0).

The children will make exactly n - 1 moves according to the following rules to reach the room (n - 1, n - 1):
- The child starting from (0, 0) must move from their current room (i, j) to
  one of the rooms (i + 1, j + 1), (i + 1, j), and (i, j + 1) if the target room exists.
- The child starting from (0, n - 1) must move from their current room (i, j) to
  one of the rooms (i + 1, j - 1), (i + 1, j), and (i + 1, j + 1) if the target room exists.
- The child starting from (n - 1, 0) must move from their current room (i, j) to
  one of the rooms (i - 1, j + 1), (i, j + 1), and (i + 1, j + 1) if the target room exists.

When a child enters a room, they will collect all the fruits there.
If two or more children enter the same room,
only one child will collect the fruits, and the room will be emptied after they leave.

Return the maximum number of fruits the children can collect from the dungeon.

Example 1:
Input: fruits = [[1,2,3,4],[5,6,8,7],[9,10,11,12],[13,14,15,16]]
Output: 100
Explanation:
In this example:
The 1st child (green) moves on the path (0,0) -> (1,1) -> (2,2) -> (3, 3).
The 2nd child (red) moves on the path (0,3) -> (1,2) -> (2,3) -> (3, 3).
The 3rd child (blue) moves on the path (3,0) -> (3,1) -> (3,2) -> (3, 3).
In total they collect 1 + 6 + 11 + 16 + 4 + 8 + 12 + 13 + 14 + 15 = 100 fruits.

Example 2:
Input: fruits = [[1,1],[1,1]]
Output: 4
Explanation:
In this example:
The 1st child moves on the path (0,0) -> (1,1).
The 2nd child moves on the path (0,1) -> (1,1).
The 3rd child moves on the path (1,0) -> (1,1).
In total they collect 1 + 1 + 1 + 1 = 4 fruits.

Constraints:
2 <= n == fruits.length == fruits[i].length <= 1000
0 <= fruits[i][j] <= 1000
```

<details><summary>Hint</summary>

```text
1. The child at (0, 0) has only one possible path.
2. The other two children won’t intersect its path.
3. Use Dynamic Programming.
```

</details>

</details>

<details><summary>C</summary>

```c
int dp(int** fruits, int fruitsSize, int* fruitsColSize) {
    int retVal = 0;

    int* prev = malloc(sizeof(int) * fruitsSize);
    if (prev == NULL) {
        perror("malloc");
        return retVal;
    }
    for (int i = 0; i < fruitsSize; ++i) {
        prev[i] = INT_MIN;
    }
    prev[fruitsSize - 1] = fruits[0][fruitsSize - 1];

    int* curr = malloc(sizeof(int) * fruitsSize);
    if (curr == NULL) {
        perror("malloc");
        free(prev);
        return retVal;
    }

    for (int i = 1; i < fruitsSize - 1; ++i) {
        for (int j = 0; j < fruitsSize; ++j) {
            curr[j] = INT_MIN;
        }

        for (int j = ((fruitsSize - 1 - i > i + 1) ? (fruitsSize - 1 - i) : (i + 1)); j < fruitsSize; ++j) {
            int best = prev[j];
            if (j - 1 >= 0) {
                best = best > prev[j - 1] ? best : prev[j - 1];
            }
            if (j + 1 < fruitsSize) {
                best = best > prev[j + 1] ? best : prev[j + 1];
            }
            curr[j] = best + fruits[i][j];
        }

        int* tmp = prev;
        prev = curr;
        curr = tmp;
    }
    retVal = prev[fruitsSize - 1];

    //
    free(prev);
    free(curr);

    return retVal;
}
int maxCollectedFruits(int** fruits, int fruitsSize, int* fruitsColSize) {
    int retVal = 0;

    for (int i = 0; i < fruitsSize; ++i) {
        retVal += fruits[i][i];
    }
    retVal += dp(fruits, fruitsSize, fruitsColSize);

    for (int i = 0; i < fruitsSize; ++i) {
        for (int j = 0; j < i; ++j) {
            int temp = fruits[j][i];
            fruits[j][i] = fruits[i][j];
            fruits[i][j] = temp;
        }
    }
    retVal += dp(fruits, fruitsSize, fruitsColSize);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    int dp(vector<vector<int>>& fruits) {  //    auto dp = [&]() -> int {
        int retVal = 0;

        int fruitsSize = fruits.size();

        vector<int> prev(fruitsSize, numeric_limits<int>::min());
        vector<int> curr(fruitsSize, numeric_limits<int>::min());

        prev[fruitsSize - 1] = fruits[0][fruitsSize - 1];
        for (int i = 1; i < fruitsSize - 1; ++i) {
            for (int j = max(fruitsSize - 1 - i, i + 1); j < fruitsSize; ++j) {
                int best = prev[j];
                if (j - 1 >= 0) {
                    best = max(best, prev[j - 1]);
                }
                if (j + 1 < fruitsSize) {
                    best = max(best, prev[j + 1]);
                }
                curr[j] = best + fruits[i][j];
            }
            swap(prev, curr);
        }
        retVal = prev[fruitsSize - 1];

        return retVal;
    }

   public:
    int maxCollectedFruits(vector<vector<int>>& fruits) {
        int retVal = 0;

        int fruitsSize = fruits.size();

        for (int i = 0; i < fruitsSize; ++i) {
            retVal += fruits[i][i];
        }
        retVal += dp(fruits);

        for (int i = 0; i < fruitsSize; ++i) {
            for (int j = 0; j < i; ++j) {
                swap(fruits[j][i], fruits[i][j]);
            }
        }
        retVal += dp(fruits);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def dp(self, fruits: List[List[int]]) -> int:
        retVal = 0

        fruitsSize = len(fruits)
        prev = [float("-inf")] * fruitsSize
        curr = [float("-inf")] * fruitsSize

        prev[fruitsSize - 1] = fruits[0][fruitsSize - 1]
        for i in range(1, fruitsSize - 1):
            for j in range(max(fruitsSize - 1 - i, i + 1), fruitsSize):
                best = prev[j]
                if j - 1 >= 0:
                    best = max(best, prev[j - 1])
                if j + 1 < fruitsSize:
                    best = max(best, prev[j + 1])
                curr[j] = best + fruits[i][j]
            prev, curr = curr, prev
        retVal = prev[fruitsSize - 1]

        return retVal

    def maxCollectedFruits(self, fruits: List[List[int]]) -> int:
        retVal = 0

        fruitsSize = len(fruits)

        retVal = sum(fruits[i][i] for i in range(fruitsSize))
        retVal += self.dp(fruits)
        for i in range(fruitsSize):
            for j in range(i):
                fruits[i][j], fruits[j][i] = fruits[j][i], fruits[i][j]
        retVal += self.dp(fruits)

        return retVal
```

</details>

## [3459. Length of Longest V-Shaped Diagonal Segment](https://leetcode.com/problems/length-of-longest-v-shaped-diagonal-segment/)  2531

- [Official](https://leetcode.com/problems/length-of-longest-v-shaped-diagonal-segment/editorial/)
- [Official](https://leetcode.cn/problems/length-of-longest-v-shaped-diagonal-segment/solutions/3756168/zui-chang-v-xing-dui-jiao-xian-duan-de-c-3pul/)

<details><summary>Description</summary>

```text
You are given a 2D integer matrix grid of size n x m, where each element is either 0, 1, or 2.

A V-shaped diagonal segment is defined as:
- The segment starts with 1.
- The subsequent elements follow this infinite sequence: 2, 0, 2, 0, ....
- The segment:
  - Starts along a diagonal direction
    (top-left to bottom-right, bottom-right to top-left, top-right to bottom-left, or bottom-left to top-right).
  - Continues the sequence in the same diagonal direction.
  - Makes at most one clockwise 90-degree turn to another diagonal direction while maintaining the sequence.

Return the length of the longest V-shaped diagonal segment. If no valid segment exists, return 0.

Example 1:
Input: grid = [[2,2,1,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]]
Output: 5
Explanation:
The longest V-shaped diagonal segment has a length of 5 and follows these coordinates: (0,2) → (1,3) → (2,4),
takes a 90-degree clockwise turn at (2,4), and continues as (3,3) → (4,2).

Example 2:
Input: grid = [[2,2,2,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]]
Output: 4
Explanation:
The longest V-shaped diagonal segment has a length of 4 and follows these coordinates: (2,3) → (3,2),
takes a 90-degree clockwise turn at (3,2), and continues as (2,1) → (1,0).

Example 3:
Input: grid = [[1,2,2,2,2],[2,2,2,2,0],[2,0,0,0,0],[0,0,2,2,2],[2,0,0,2,0]]
Output: 5
Explanation:
The longest V-shaped diagonal segment has a length of 5 and
follows these coordinates: (0,0) → (1,1) → (2,2) → (3,3) → (4,4).

Example 4:
Input: grid = [[1]]
Output: 1
Explanation:
The longest V-shaped diagonal segment has a length of 1 and follows these coordinates: (0,0).

Constraints:
n == grid.length
m == grid[i].length
1 <= n, m <= 500
grid[i][j] is either 0, 1 or 2.
```

<details><summary>Hint</summary>

```text
1. Use dynamic programming to determine the best point
   to make a 90-degree rotation in the diagonal path while maintaining the required sequence.
2. Represent dynamic programming states as (row, col, currentDirection, hasMadeTurnYet).
   Track the current position, direction of traversal, and whether a turn has already been made,
   and take transitions accordingly to find the longest V-shaped diagonal segment.
```

</details>

</details>

<details><summary>C</summary>

```c
const int directions[4][2] = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
int dfs(int** grid, int gridSize, int gridColSize, int*** memo, int x, int y, int z, int turn, int target) {
    int retVal = 0;

    x += directions[z][0];
    y += directions[z][1];
    if ((x < 0) || (x >= gridSize) || (y < 0) || (y >= gridColSize)) {
        return retVal;
    } else if (grid[x][y] != target) {
        return retVal;
    }

    int maxs[4];
    int next;
    int mask = (z << 1) | turn;
    if (memo[x][y][mask] <= 0) {
        retVal = dfs(grid, gridSize, gridColSize, memo, x, y, z, turn, 2 - target);
        if (turn == 1) {
            memset(maxs, 0, sizeof(maxs));
            maxs[0] = gridSize - x - 1;
            maxs[1] = y;
            maxs[2] = x;
            maxs[3] = gridColSize - y - 1;
            next = (z + 1) % 4;
            if (maxs[next] > retVal) {
                retVal = fmax(retVal, dfs(grid, gridSize, gridColSize, memo, x, y, next, 0, 2 - target));
            }
        }
        memo[x][y][mask] = retVal + 1;
    }
    retVal = memo[x][y][mask];

    return retVal;
}
int lenOfVDiagonal(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int rowSize = gridSize;
    int colSize = gridColSize[0];
    int depth = (1 << 3);

    int*** memo = (int***)malloc(rowSize * sizeof(int**));
    for (int i = 0; i < rowSize; i++) {
        memo[i] = (int**)malloc(colSize * sizeof(int*));
        for (int j = 0; j < colSize; j++) {
            memo[i][j] = (int*)malloc(depth * sizeof(int));
            memset(memo[i][j], -1, depth * sizeof(int));
        }
    }

    for (int x = 0; x < rowSize; ++x) {
        for (int y = 0; y < colSize; ++y) {
            if (grid[x][y] != 1) {
                continue;
            }

            int maxs[4] = {rowSize - x, y + 1, x + 1, colSize - y};
            for (int z = 0; z < 4; ++z) {
                if (maxs[z] > retVal) {
                    retVal = fmax(retVal, dfs(grid, rowSize, colSize, memo, x, y, z, 1, 2) + 1);
                }
            }
        }
    }

    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            free(memo[i][j]);
            memo[i][j] = NULL;
        }
        free(memo[i]);
        memo[i] = NULL;
    }
    free(memo);
    memo = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    const int directions[4][2] = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};

    int dfs(vector<vector<int>>& grid, vector<vector<vector<int>>>& memo, int x, int y, int z, int turn, int target) {
        int retVal = 0;

        int gridSize = grid.size();
        int gridColSize = grid[0].size();
        x += directions[z][0];
        y += directions[z][1];
        if ((x < 0) || (x >= gridSize) || (y < 0) || (y >= gridColSize)) {
            return retVal;
        } else if (grid[x][y] != target) {
            return retVal;
        }

        int mask = (z << 1) | turn;
        if (memo[x][y][mask] <= 0) {
            retVal = dfs(grid, memo, x, y, z, turn, 2 - target);
            if (turn == 1) {
                vector<int> maxs = {gridSize - x - 1, y, x, gridColSize - y - 1};
                int next = (z + 1) % 4;
                if (maxs[next] > retVal) {
                    retVal = max(retVal, dfs(grid, memo, x, y, next, 0, 2 - target));
                }
            }
            memo[x][y][mask] = retVal + 1;
        }
        retVal = memo[x][y][mask];

        return retVal;
    };

   public:
    int lenOfVDiagonal(vector<vector<int>>& grid) {
        int retVal = 0;

        int gridSize = grid.size();
        int gridColSize = grid[0].size();
        vector<vector<vector<int>>> memo(gridSize, vector<vector<int>>(gridColSize, vector<int>(1 << 3, 0)));
        for (int x = 0; x < gridSize; ++x) {
            for (int y = 0; y < gridColSize; ++y) {
                if (grid[x][y] != 1) {
                    continue;
                }

                vector<int> maxs = {gridSize - x, y + 1, x + 1, gridColSize - y};
                for (int z = 0; z < 4; ++z) {
                    if (maxs[z] > retVal) {
                        retVal = max(retVal, dfs(grid, memo, x, y, z, 1, 2) + 1);
                    }
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
    def __init__(self):
        self.directions = [(1, 1), (1, -1), (-1, -1), (-1, 1)]

    def lenOfVDiagonal(self, grid: List[List[int]]) -> int:
        retVal = 0

        gridSize = len(grid)
        gridColSize = len(grid[0])

        @cache
        def dfs(cx: int, cy: int, direction: int, turn: bool, target: int) -> int:
            retVal = 0

            nextX = cx + self.directions[direction][0]
            nextY = cy + self.directions[direction][1]
            # If it goes beyond the boundary or the next node's value is not the target value, then return
            if (nextX < 0) or (nextY < 0) or (nextX >= gridSize) or (nextY >= gridColSize):
                return retVal
            if (grid[nextX][nextY] != target):
                return retVal

            # Continue walking in the original direction.
            maxStep = dfs(nextX, nextY, direction, turn, 2 - target)
            if turn == True:
                # Clockwise rotate 90 degrees turn
                maxStep = max(maxStep, dfs(nextX, nextY, (direction + 1) % 4, False, 2 - target))
            retVal = maxStep + 1

            return retVal

        for i in range(gridSize):
            for j in range(gridColSize):
                if grid[i][j] != 1:
                    continue
                for direction in range(4):
                    retVal = max(retVal, dfs(i, j, direction, True, 2) + 1)

        return retVal
```

</details>

## [3539. Find Sum of Array Product of Magical Sequences](https://leetcode.com/problems/find-sum-of-array-product-of-magical-sequences/)  2694

- [Official](https://leetcode.com/problems/find-sum-of-array-product-of-magical-sequences/editorial/)
- [Official](https://leetcode.cn/problems/find-sum-of-array-product-of-magical-sequences/solutions/3800541/mo-fa-xu-lie-de-shu-zu-cheng-ji-zhi-he-b-54vt/)

<details><summary>Description</summary>

```text
You are given two integers, m and k, and an integer array nums.

A sequence of integers seq is called magical if:
- seq has a size of m.
- 0 <= seq[i] < nums.length
- The binary representation of 2seq[0] + 2seq[1] + ... + 2seq[m - 1] has k set bits.

The array product of this sequence is defined as prod(seq) = (nums[seq[0]] * nums[seq[1]] * ... * nums[seq[m - 1]]).

Return the sum of the array products for all valid magical sequences.

Since the answer may be large, return it modulo 10^9 + 7.

A set bit refers to a bit in the binary representation of a number that has a value of 1.

Example 1:
Input: m = 5, k = 5, nums = [1,10,100,10000,1000000]
Output: 991600007
Explanation:
All permutations of [0, 1, 2, 3, 4] are magical sequences, each with an array product of 10^13.

Example 2:
Input: m = 2, k = 2, nums = [5,4,3,2,1]
Output: 170
Explanation:
The magical sequences are [0, 1], [0, 2], [0, 3], [0, 4], [1, 0], [1, 2], [1, 3], [1, 4],
[2, 0], [2, 1], [2, 3], [2, 4], [3, 0], [3, 1], [3, 2], [3, 4], [4, 0], [4, 1], [4, 2], and [4, 3].

Example 3:
Input: m = 1, k = 1, nums = [28]
Output: 28
Explanation:
The only magical sequence is [0].

Constraints:
1 <= k <= m <= 30
1 <= nums.length <= 50
1 <= nums[i] <= 10^8
```

<details><summary>Hint</summary>

```text
1. Use Dynamic Programming
2. Let dp[i][j][mask] be the state after choosing i numbers (indices)
3. The partial sum S = 2^(seq[0]) + 2^(seq[1]) + ... + 2^(seq[i - 1]) has produced exactly j set bits once
   you’ve fully propagated any carries
4. The mask represents the "window" of lower-order bits from S that have not yet been fully processed
   (i.e. bits that might later create new set bits when additional terms are added)
5. Use combinatorics
6. How many ways are there to permute a sequence of entities where some are repetitive?
```

</details>

</details>

<details><summary>C</summary>

```c
#define MODULO (long long)(1e9 + 7)
long long quickmul(long long x, long long y) {
    long long res = 1;

    long long current = x % MODULO;
    while (y) {
        if (y & 1) {
            res = res * current % MODULO;
        }
        y >>= 1;
        current = current * current % MODULO;
    }

    return res;
}
int magicalSum(int m, int k, int* nums, int numsSize) {
    int retVal = 0;

    long long* fac = (long long*)malloc((m + 1) * sizeof(long long));
    fac[0] = 1;
    for (int i = 1; i <= m; i++) {
        fac[i] = fac[i - 1] * i % MODULO;
    }

    long long* ifac = (long long*)malloc((m + 1) * sizeof(long long));
    ifac[0] = 1;
    ifac[1] = 1;
    for (int i = 2; i <= m; i++) {
        ifac[i] = quickmul(i, MODULO - 2);
    }
    for (int i = 2; i <= m; i++) {
        ifac[i] = ifac[i - 1] * ifac[i] % MODULO;
    }

    long long** numsPower = (long long**)malloc(numsSize * sizeof(long long*));
    for (int i = 0; i < numsSize; i++) {
        numsPower[i] = (long long*)malloc((m + 1) * sizeof(long long));
        numsPower[i][0] = 1;
        for (int j = 1; j <= m; j++) {
            numsPower[i][j] = numsPower[i][j - 1] * nums[i] % MODULO;
        }
    }

    long long**** f = (long long****)malloc(numsSize * sizeof(long long***));
    for (int i = 0; i < numsSize; i++) {
        f[i] = (long long***)malloc((m + 1) * sizeof(long long**));
        for (int j = 0; j <= m; j++) {
            f[i][j] = (long long**)malloc((m * 2 + 1) * sizeof(long long*));
            for (int p = 0; p <= m * 2; p++) {
                f[i][j][p] = (long long*)calloc((k + 1), sizeof(long long));
            }
        }
    }
    for (int j = 0; j <= m; j++) {
        f[0][j][j][0] = numsPower[0][j] * ifac[j] % MODULO;
    }
    for (int i = 0; i + 1 < numsSize; i++) {
        for (int j = 0; j <= m; j++) {
            for (int p = 0; p <= m * 2; p++) {
                for (int q = 0; q <= k; q++) {
                    int q2 = p % 2 + q;
                    if (q2 > k) {
                        break;
                    }
                    for (int r = 0; r + j <= m; r++) {
                        int p2 = p / 2 + r;
                        f[i + 1][j + r][p2][q2] += f[i][j][p][q] * numsPower[i + 1][r] % MODULO * ifac[r] % MODULO;
                        f[i + 1][j + r][p2][q2] %= MODULO;
                    }
                }
            }
        }
    }

    long long res = 0;
    for (int p = 0; p <= m * 2; p++) {
        for (int q = 0; q <= k; q++) {
            int bitcount = __builtin_popcount(p);
            if (bitcount + q == k) {
                res = (res + f[numsSize - 1][m][p][q] * fac[m] % MODULO) % MODULO;
            }
        }
    }
    retVal = (int)res;

    //
    free(fac);
    free(ifac);
    for (int i = 0; i < numsSize; i++) {
        free(numsPower[i]);
    }
    free(numsPower);
    for (int i = 0; i < numsSize; i++) {
        for (int j = 0; j <= m; j++) {
            for (int p = 0; p <= m * 2; p++) {
                free(f[i][j][p]);
            }
            free(f[i][j]);
        }
        free(f[i]);
    }
    free(f);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    const long long MODULO = 1e9 + 7;

    long long quickmul(long long x, long long y) {
        long long retVal = 1;

        long long current = x % MODULO;
        while (y) {
            if (y & 1) {
                retVal = retVal * current % MODULO;
            }
            y >>= 1;

            current = current * current % MODULO;
        }

        return retVal;
    };

   public:
    int magicalSum(int m, int k, vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        vector<long long> fac(m + 1, 1);
        for (int i = 1; i <= m; i++) {
            fac[i] = fac[i - 1] * i % MODULO;
        }

        vector<long long> ifac(m + 1, 1);
        for (int i = 2; i <= m; i++) {
            ifac[i] = quickmul(i, MODULO - 2);
        }
        for (int i = 2; i <= m; i++) {
            ifac[i] = ifac[i - 1] * ifac[i] % MODULO;
        }

        vector numsPower(numsSize, vector<long long>(m + 1, 1));
        for (int i = 0; i < numsSize; i++) {
            for (int j = 1; j <= m; j++) {
                numsPower[i][j] = numsPower[i][j - 1] * nums[i] % MODULO;
            }
        }

        vector f(numsSize, vector(m + 1, vector(m * 2 + 1, vector<long long>(k + 1, 0))));
        for (int j = 0; j <= m; j++) {
            f[0][j][j][0] = numsPower[0][j] * ifac[j] % MODULO;
        }
        for (int i = 0; i + 1 < numsSize; i++) {
            for (int j = 0; j <= m; j++) {
                for (int p = 0; p <= m * 2; p++) {
                    for (int q = 0; q <= k; q++) {
                        int q2 = p % 2 + q;
                        if (q2 > k) {
                            break;
                        }

                        for (int r = 0; r + j <= m; r++) {
                            int p2 = p / 2 + r;
                            f[i + 1][j + r][p2][q2] += f[i][j][p][q] * numsPower[i + 1][r] % MODULO * ifac[r] % MODULO;
                            f[i + 1][j + r][p2][q2] %= MODULO;
                        }
                    }
                }
            }
        }

        for (int p = 0; p <= m * 2; p++) {
            for (int q = 0; q <= k; q++) {
                if (__builtin_popcount(p) + q == k) {
                    retVal = (retVal + f[numsSize - 1][m][p][q] * fac[m] % MODULO) % MODULO;
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
    def __init__(self):
        self.MODULO = 10 ** 9 + 7

    def quickmul(self, x: int, y: int) -> int:
        retVal = 1

        current = x % self.MODULO
        while y:
            if y & 1:
                retVal = retVal * current % self.MODULO
            y >>= 1
            current = current * current % self.MODULO

        return retVal

    def magicalSum(self, m: int, k: int, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        fac = [1] * (m + 1)
        for i in range(1, m + 1):
            fac[i] = fac[i - 1] * i % self.MODULO

        ifac = [1] * (m + 1)
        for i in range(2, m + 1):
            ifac[i] = self.quickmul(i, self.MODULO - 2)
        for i in range(2, m + 1):
            ifac[i] = ifac[i - 1] * ifac[i] % self.MODULO

        numsPower = [[1] * (m + 1) for _ in range(numsSize)]
        for i in range(numsSize):
            for j in range(1, m + 1):
                numsPower[i][j] = numsPower[i][j - 1] * nums[i] % self.MODULO

        f = [[[[0] * (k + 1) for _ in range(m * 2 + 1)] for _ in range(m + 1)] for _ in range(numsSize)]
        for j in range(m + 1):
            f[0][j][j][0] = numsPower[0][j] * ifac[j] % self.MODULO

        for i in range(numsSize - 1):
            for j in range(m + 1):
                for p in range(m * 2 + 1):
                    for q in range(k + 1):
                        if f[i][j][p][q] == 0:
                            continue

                        q2 = (p % 2) + q
                        if q2 > k:
                            break

                        for r in range(m - j + 1):
                            p2 = (p // 2) + r
                            if p2 > m * 2:
                                continue

                            tmp = f[i][j][p][q] * numsPower[i + 1][r] % self.MODULO * ifac[r] % self.MODULO
                            f[i + 1][j + r][p2][q2] = (f[i + 1][j + r][p2][q2] + tmp) % self.MODULO

        for p in range(m * 2 + 1):
            for q in range(k + 1):
                if bin(p).count("1") + q == k:
                    retVal = (retVal + f[numsSize - 1][m][p][q] * fac[m] % self.MODULO) % self.MODULO

        return retVal
```

</details>
