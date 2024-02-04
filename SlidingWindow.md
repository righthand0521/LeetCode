# Sliding Window

## [3. Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/)

- [Official](https://leetcode.cn/problems/longest-substring-without-repeating-characters/solutions/227999/wu-zhong-fu-zi-fu-de-zui-chang-zi-chuan-by-leetc-2/)

<details><summary>Description</summary>

```text
Given a string s, find the length of the longest substring without repeating characters.

Example 1:
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

Example 2:
Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:
Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.

Constraints:
0 <= s.length <= 5 * 10^4
s consists of English letters, digits, symbols and spaces.
```

</details>

<details><summary>C</summary>

```c
int lengthOfLongestSubstring(char *s) {
    int retVal = 0;

    // s consists of English letters, digits, symbols and spaces.
#define MAX_CHAR_RANGE (256)
    int hashTable[MAX_CHAR_RANGE];
    memset(hashTable, 0, sizeof(hashTable));

    int head = 0;
    int tail = 0;
    while ((*(s + head) != 0) && (*(s + tail) != 0)) {
        if ((hashTable[(int)(*(s + head))] != 0) && (hashTable[(int)(*(s + tail))] != 0)) {
            hashTable[(int)(*(s + head))] = 0;
            ++head;
        } else {
            hashTable[(int)(*(s + tail))] = 1;
            ++tail;
        }
        retVal = fmax(retVal, (tail - head));
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int lengthOfLongestSubstring(string s) {
        int retVal = 0;

        unordered_map<int, int> hashTable;
        int len = s.length();
        int head = 0;
        int tail = 0;
        while ((head < len) && (tail < len)) {
            if ((hashTable[s[head]] != 0) && (hashTable[s[tail]] != 0)) {
                hashTable[s[head]] = 0;
                ++head;
            } else {
                ++hashTable[s[tail]];
                ++tail;
            }
            retVal = max(retVal, (tail - head));
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        retVal = 0

        hashTable = defaultdict(dict)
        sSize = len(s)
        head = 0
        tail = 0
        while head < sSize and tail < sSize:
            if hashTable[s[head]] and hashTable[s[tail]]:
                hashTable.pop(s[head])
                head += 1
            else:
                hashTable[s[tail]] = 1
                tail += 1
            retVal = max(retVal, tail - head)

        return retVal
```

</details>

## [76. Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/)

- [Official](https://leetcode.cn/problems/minimum-window-substring/solutions/257359/zui-xiao-fu-gai-zi-chuan-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given two strings s and t of lengths m and n respectively,
return the minimum window substring of s such that every character in t (including duplicates) is included in the window.
If there is no such substring, return the empty string "".

The testcases will be generated such that the answer is unique.

A substring is a contiguous sequence of characters within the string.

Example 1:
Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.

Example 2:
Input: s = "a", t = "a"
Output: "a"
Explanation: The entire string s is the minimum window.

Example 3:
Input: s = "a", t = "aa"
Output: ""
Explanation: Both 'a's from t must be included in the window.
Since the largest window of s only has one 'a', return empty string.

Constraints:
m == s.length
n == t.length
1 <= m, n <= 10^5
s and t consist of uppercase and lowercase English letters.

Follow up: Could you find an algorithm that runs in O(m + n) time?
```

<details><summary>Hint</summary>

```text
1. Use two pointers to create a window of letters in s, which would have all the characters from t.
2. Expand the right pointer until all the characters of t are covered.
3. Once all the characters are covered,
   move the left pointer and ensure that all the characters are still covered to minimize the subarray size.
4. Continue expanding the right and left pointers until you reach the end of s.
```

</details>

</details>

<details><summary>C</summary>

```c
char* minWindow(char* s, char* t) {
    char* pRetVal = "";

    int sSize = strlen(s);
    int tSize = strlen(t);

    int i;

#define ASCII_SIZE (128)      // s and t consist of uppercase and lowercase English letters.
    int hashSet[ASCII_SIZE];  // use hash set to record character in t
    memset(hashSet, 0, sizeof(hashSet));
    for (i = 0; i < tSize; ++i) {
        ++hashSet[(unsigned char)t[i]];
    }

    /* Process
     *  |   0  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |  10  |  11  |  12  | ABC           |
     *  |------------------------------------------------------------------------------------------|---------------|
     *  |   A  |   D  |   O  |   B  |   E  |   C  |   O  |   D  |   E  |   B  |   A  |   N  |   C  |               |
     *  | head |      |      |      |      | tail |      |      |      |      |      |      |      | => ADOBEC     |
     *  |      | head |      |      |      | tail |      |      |      |      |      |      |      | -X-> DOBEC    |
     *  |      | head |      |      |      |      |      |      |      |      | tail |      |      | => DOBECODEBA |
     *  |      |      | head |      |      |      |      |      |      |      | tail |      |      | => OBECODEBA  |
     *  |      |      |      | head |      |      |      |      |      |      | tail |      |      | => BECODEBA   |
     *  |      |      |      |      | head |      |      |      |      |      | tail |      |      | => ECODEBA    |
     *  |      |      |      |      |      | head |      |      |      |      | tail |      |      | => CODEBA     |
     *  |      |      |      |      |      |      | head |      |      |      | tail |      |      | -X-> ODEBA    |
     *  |      |      |      |      |      |      | head |      |      |      |      |      | tail | => ODEBANC    |
     *  |      |      |      |      |      |      |      | head |      |      |      |      | tail | => DEBANC     |
     *  |      |      |      |      |      |      |      |      | head |      |      |      | tail | => EBANC      |
     *  |      |      |      |      |      |      |      |      |      | head |      |      | tail | => BANC       |
     */
    int count = 0;
    int head = 0;
    int retHead = 0;
    int retTail = 0;
    int minLen = INT_MAX;
    for (i = 0; i < sSize; ++i) {
        // update hash set by character in s
        --hashSet[(unsigned char)s[i]];

        // if character both in t and s
        if (hashSet[(unsigned char)s[i]] >= 0) {
            ++count;
        }

        while (count == tSize) {
            // update head and tail according to Minimum record
            if ((i - head + 1) < minLen) {
                minLen = i - head + 1;
                retHead = head;
                retTail = i;
            }

            // update hash set by character in s
            ++hashSet[(unsigned char)s[head]];

            // if character in s
            if (hashSet[(unsigned char)s[head]] > 0) {
                --count;
            }

            // move head
            head++;
        }
    }
    if (minLen != INT_MAX) {
        s[retTail + 1] = 0;
        pRetVal = &(s[retHead]);
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string minWindow(string s, string t) {
        string retVal;

        int sSize = s.size();
        int tSize = t.size();

        unordered_map<char, int> hashSet;
        for (char c : t) {
            ++hashSet[c];
        }

        /* Process
         *  |   0  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |  10  |  11  |  12  | ABC           |
         *  |------------------------------------------------------------------------------------------|---------------|
         *  |   A  |   D  |   O  |   B  |   E  |   C  |   O  |   D  |   E  |   B  |   A  |   N  |   C  |               |
         *  | head |      |      |      |      | tail |      |      |      |      |      |      |      | => ADOBEC     |
         *  |      | head |      |      |      | tail |      |      |      |      |      |      |      | -X-> DOBEC    |
         *  |      | head |      |      |      |      |      |      |      |      | tail |      |      | => DOBECODEBA |
         *  |      |      | head |      |      |      |      |      |      |      | tail |      |      | => OBECODEBA  |
         *  |      |      |      | head |      |      |      |      |      |      | tail |      |      | => BECODEBA   |
         *  |      |      |      |      | head |      |      |      |      |      | tail |      |      | => ECODEBA    |
         *  |      |      |      |      |      | head |      |      |      |      | tail |      |      | => CODEBA     |
         *  |      |      |      |      |      |      | head |      |      |      | tail |      |      | -X-> ODEBA    |
         *  |      |      |      |      |      |      | head |      |      |      |      |      | tail | => ODEBANC    |
         *  |      |      |      |      |      |      |      | head |      |      |      |      | tail | => DEBANC     |
         *  |      |      |      |      |      |      |      |      | head |      |      |      | tail | => EBANC      |
         *  |      |      |      |      |      |      |      |      |      | head |      |      | tail | => BANC       |
         */
        int count = 0;
        int head = 0;
        int retHead = 0;
        int retTail = 0;
        int minLen = numeric_limits<int>::max();
        for (int i = 0; i < sSize; ++i) {
            // update hash set by character in s
            --hashSet[s[i]];

            // if character both in t and s
            if (hashSet[s[i]] >= 0) {
                ++count;
            }

            while (count == tSize) {
                // update head and tail according to Minimum record
                if ((i - head + 1) < minLen) {
                    minLen = i - head + 1;
                    retHead = head;
                    retTail = i;
                }

                // update hash set by character in s
                ++hashSet[s[head]];

                // if character in s
                if (hashSet[s[head]] > 0) {
                    --count;
                }

                // move head
                head++;
            }
        }
        if (minLen != numeric_limits<int>::max()) {
            s[retTail + 1] = 0;
            retVal = &(s[retHead]);
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
        # s and t consist of uppercase and lowercase English letters.
        self.ASCII_SIZE = 128

    def minWindow(self, s: str, t: str) -> str:
        retVal = ""

        sSize = len(s)
        tSize = len(t)

        hashSet = [0] * self.ASCII_SIZE
        for c in t:
            hashSet[ord(c)] += 1

        # /* Process
        #  *  |   0  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |  10  |  11  |  12  | ABC           |
        #  *  |------------------------------------------------------------------------------------------|---------------|
        #  *  |   A  |   D  |   O  |   B  |   E  |   C  |   O  |   D  |   E  |   B  |   A  |   N  |   C  |               |
        #  *  | head |      |      |      |      | tail |      |      |      |      |      |      |      | => ADOBEC     |
        #  *  |      | head |      |      |      | tail |      |      |      |      |      |      |      | -X-> DOBEC    |
        #  *  |      | head |      |      |      |      |      |      |      |      | tail |      |      | => DOBECODEBA |
        #  *  |      |      | head |      |      |      |      |      |      |      | tail |      |      | => OBECODEBA  |
        #  *  |      |      |      | head |      |      |      |      |      |      | tail |      |      | => BECODEBA   |
        #  *  |      |      |      |      | head |      |      |      |      |      | tail |      |      | => ECODEBA    |
        #  *  |      |      |      |      |      | head |      |      |      |      | tail |      |      | => CODEBA     |
        #  *  |      |      |      |      |      |      | head |      |      |      | tail |      |      | -X-> ODEBA    |
        #  *  |      |      |      |      |      |      | head |      |      |      |      |      | tail | => ODEBANC    |
        #  *  |      |      |      |      |      |      |      | head |      |      |      |      | tail | => DEBANC     |
        #  *  |      |      |      |      |      |      |      |      | head |      |      |      | tail | => EBANC      |
        #  *  |      |      |      |      |      |      |      |      |      | head |      |      | tail | => BANC       |
        #  */
        count = 0
        head = 0
        retHead = 0
        retTail = 0
        minLen = float('inf')
        for i in range(sSize):
            # update hash set by character in s
            hashSet[ord(s[i])] -= 1

            # if character both in t and s
            if hashSet[ord(s[i])] >= 0:
                count += 1

            while (count == tSize):
                # update head and tail according to Minimum record
                if (i - head + 1) < minLen:
                    minLen = i - head + 1
                    retHead = head
                    retTail = i

                # update hash set by character in s
                hashSet[ord(s[head])] += 1

                # if character in s
                if hashSet[ord(s[head])] > 0:
                    count -= 1

                #  move head
                head += 1
        if minLen != float('inf'):
            retVal = s[retHead:retTail+1]

        return retVal
```

</details>

## [209. Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/)

- [Official](https://leetcode.com/problems/minimum-size-subarray-sum/editorial/)
- [Official](https://leetcode.cn/problems/minimum-size-subarray-sum/solutions/305704/chang-du-zui-xiao-de-zi-shu-zu-by-leetcode-solutio/)

<details><summary>Description</summary>

```text
Given an array of positive integers nums and a positive integer target,
return the minimal length of a subarray whose sum is greater than or equal to target.
If there is no such subarray, return 0 instead.

Example 1:
Input: target = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: The subarray [4,3] has the minimal length under the problem constraint.

Example 2:
Input: target = 4, nums = [1,4,4]
Output: 1

Example 3:
Input: target = 11, nums = [1,1,1,1,1,1,1,1]
Output: 0

Constraints:
1 <= target <= 10^9
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^4

Follow up: If you have figured out the O(n) solution,
try coding another solution of which the time complexity is O(n log(n)).
```

</details>

<details><summary>C</summary>

```c
int minSubArrayLen(int target, int* nums, int numsSize) {
    int retVal = numsSize + 1;

    int sum = 0;
    int head = 0;
    int tail;
    for (tail = 0; tail < numsSize; ++tail) {
        sum += nums[tail];
        while (sum >= target) {
            retVal = fmin(retVal, (tail - head + 1));
            sum -= nums[head++];
        }
    }
    if (retVal == numsSize + 1) {
        retVal = 0;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int retVal = 0;

        int len = nums.size();
        retVal = len + 1;
        int sum = 0;
        int head = 0;
        int tail;
        for (tail = 0; tail < len; ++tail) {
            sum += nums[tail];
            while (sum >= target) {
                retVal = min(retVal, tail - head + 1);

                sum -= nums[head];
                ++head;
            }
        }
        if (retVal == len + 1) {
            retVal = 0;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minSubArrayLen(self, target: int, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)
        retVal = numsSize + 1
        sum = 0
        head = 0
        for tail in range(numsSize):
            sum += nums[tail]
            while sum >= target:
                retVal = min(retVal, tail - head + 1)
                sum -= nums[head]
                head += 1

        if retVal == numsSize + 1:
            retVal = 0

        return retVal
```

</details>

## [424. Longest Repeating Character Replacement](https://leetcode.com/problems/longest-repeating-character-replacement/)

- [Official](https://leetcode.com/problems/longest-repeating-character-replacement/editorial/)
- [Official](https://leetcode.cn/problems/longest-repeating-character-replacement/solutions/586648/ti-huan-hou-de-zui-chang-zhong-fu-zi-fu-eaacp/)

<details><summary>Description</summary>

```text
You are given a string s and an integer k.
You can choose any character of the string and change it to any other uppercase English character.
You can perform this operation at most k times.

Return the length of the longest substring containing the same letter you can get after performing the above operations.

Example 1:
Input: s = "ABAB", k = 2
Output: 4
Explanation: Replace the two 'A's with two 'B's or vice versa.

Example 2:
Input: s = "AABABBA", k = 1
Output: 4
Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
The substring "BBBB" has the longest repeating letters, which is 4.

Constraints:
1 <= s.length <= 10^5
s consists of only uppercase English letters.
0 <= k <= s.length
```

</details>

<details><summary>C</summary>

```c
int characterReplacement(char* s, int k) {
    int retVal = 0;

    // s consists of only uppercase English letters.
#define MAX_RECORD (26)
    int Record[MAX_RECORD];
    memset(Record, 0, sizeof(Record));

    int maxRecord = 0;
    int sSize = strlen(s);
    int left = 0;
    int right = 0;
    while (right < sSize) {
        Record[s[right] - 'A']++;

        maxRecord = fmax(maxRecord, Record[s[right] - 'A']);
        if (right - left + 1 - maxRecord > k) {
            Record[s[left] - 'A']--;
            left++;
        }

        right++;
    }
    retVal = right - left;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int characterReplacement(string s, int k) {
        int retVal = 0;

        // s consists of only uppercase English letters.
#define MAX_RECORD (26)
        vector<int> Record(MAX_RECORD, 0);

        int maxRecord = 0;
        int sSize = s.length();
        int left = 0;
        int right = 0;
        while (right < sSize) {
            Record[s[right] - 'A']++;

            maxRecord = max(maxRecord, Record[s[right] - 'A']);
            if (right - left + 1 - maxRecord > k) {
                Record[s[left] - 'A']--;
                left++;
            }

            right++;
        }
        retVal = right - left;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def characterReplacement(self, s: str, k: int) -> int:
        retVal = 0

        # s consists of only uppercase English letters.
        MAX_RECORD = 26
        Record = [0] * MAX_RECORD

        maxRecord = 0
        sSize = len(s)
        left = 0
        right = 0
        while right < sSize:
            idx = ord(s[right]) - ord("A")
            Record[idx] += 1

            maxRecord = max(maxRecord, Record[idx])
            if right - left + 1 - maxRecord > k:
                Record[ord(s[left]) - ord("A")] -= 1
                left += 1

            right += 1

        retVal = right - left

        return retVal
```

</details>

## [438. Find All Anagrams in a String](https://leetcode.com/problems/find-all-anagrams-in-a-string/)

- [Official](https://leetcode.cn/problems/find-all-anagrams-in-a-string/solutions/1123971/zhao-dao-zi-fu-chuan-zhong-suo-you-zi-mu-xzin/)

<details><summary>Description</summary>

```text
Given two strings s and p, return an array of all the start indices of p's anagrams in s.
You may return the answer in any order.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase,
typically using all the original letters exactly once.

Example 1:
Input: s = "cbaebabacd", p = "abc"
Output: [0,6]
Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".

Example 2:
Input: s = "abab", p = "ab"
Output: [0,1,2]
Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".

Constraints:
1 <= s.length, p.length <= 3 * 10^4
s and p consist of lowercase English letters.
```

</details>

<details><summary>C</summary>

```c
#define MAX_RECORD (26)  // s and p consist of lowercase English letters.
bool isSame(int* pRecordS, int* pRecordP) {
    int retVal = false;

    int i;
    for (i = 0; i < MAX_RECORD; i++) {
        if (pRecordS[i] != pRecordP[i]) {
            return retVal;
        }
    }
    retVal = true;

    return retVal;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findAnagrams(char* s, char* p, int* returnSize) {
    int* pRetVal = NULL;
    (*returnSize) = 0;

    int lenS = strlen(s);
    int lenP = strlen(p);
    if (lenS < lenP) {
        return pRetVal;
    }

    pRetVal = (int*)malloc(lenS * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int i;
    int RecordS[MAX_RECORD] = {0};
    int RecordP[MAX_RECORD] = {0};

    for (i = 0; i < lenP; i++) {
        RecordS[s[i] - 'a']++;
        RecordP[p[i] - 'a']++;
    }
    if (isSame(RecordS, RecordP) == true) {
        pRetVal[(*returnSize)++] = 0;
    }

    for (i = lenP; i < lenS; i++) {
        RecordS[s[i] - 'a']++;
        RecordS[s[i - lenP] - 'a']--;
        if (isSame(RecordS, RecordP) == true) {
            pRetVal[(*returnSize)++] = i - lenP + 1;
        }
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define MAX_COUNT_SIZE (26)  // s and p consist of lowercase English letters.
   public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> retVal;

        int lenS = s.length();
        int lenP = p.length();
        if (lenS < lenP) {
            return retVal;
        }

        vector<int> countS(MAX_COUNT_SIZE, 0);
        vector<int> countP(MAX_COUNT_SIZE, 0);
        for (int i = 0; i < lenP; ++i) {
            ++countS[s[i] - 'a'];
            ++countP[p[i] - 'a'];
        }
        if (countS == countP) {
            retVal.push_back(0);
        }

        for (int i = lenP; i < lenS; ++i) {
            ++countS[s[i] - 'a'];
            --countS[s[i - lenP] - 'a'];
            if (countS == countP) {
                retVal.push_back(i - lenP + 1);
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
    def findAnagrams(self, s: str, p: str) -> List[int]:
```

</details>

<details><summary>Rust</summary>

```rust
const COUNT_SIZE: usize = 26; // s and p consist of lowercase English letters.
impl Solution {
    pub fn find_anagrams(s: String, p: String) -> Vec<i32> {
        let mut ret_val = vec![];

        let len_s = s.len();
        let len_p = p.len();
        if len_s < len_p {
            return ret_val;
        }

        let mut count_s: [usize; COUNT_SIZE] = [0; COUNT_SIZE];
        let mut count_p: [usize; COUNT_SIZE] = [0; COUNT_SIZE];

        for i in 0..len_p {
            count_s[(s.chars().nth(i).unwrap() as u8 - b'a') as usize] += 1;
            count_p[(p.chars().nth(i).unwrap() as u8 - b'a') as usize] += 1;
        }
        if count_s == count_p {
            ret_val.push(0);
        }

        for i in len_p..len_s {
            count_s[(s.chars().nth(i).unwrap() as u8 - b'a') as usize] += 1;
            count_s[(s.chars().nth(i - len_p).unwrap() as u8 - b'a') as usize] -= 1;
            if count_s == count_p {
                ret_val.push(i as i32 - len_p as i32 + 1);
            }
        }

        return ret_val;
    }
}
```

</details>

## [567. Permutation in String](https://leetcode.com/problems/permutation-in-string/)

- [Official](https://leetcode.com/problems/permutation-in-string/editorial/)
- [Official](https://leetcode.cn/problems/permutation-in-string/solutions/599202/zi-fu-chuan-de-pai-lie-by-leetcode-solut-7k7u/)

<details><summary>Description</summary>

```text
Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.

In other words, return true if one of s1's permutations is the substring of s2.

Example 1:
Input: s1 = "ab", s2 = "eidbaooo"
Output: true
Explanation: s2 contains one permutation of s1 ("ba").

Example 2:
Input: s1 = "ab", s2 = "eidboaoo"
Output: false

Constraints:
1 <= s1.length, s2.length <= 10^4
s1 and s2 consist of lowercase English letters.
```

</details>

<details><summary>C</summary>

```c
#define COUNT_SIZE (26)  // s1 and s2 consist of lowercase English letters.
bool IsCountEqual(int* pCount1, int* pCount2) {
    bool retVal = false;

    int i;
    for (i = 0; i < COUNT_SIZE; ++i) {
        if (pCount1[i] != pCount2[i]) {
            return retVal;
        }
    }
    retVal = true;

    return retVal;
}
bool checkInclusion(char* s1, char* s2) {
    bool retVal = false;

    int len1 = strlen(s1);
    int len2 = strlen(s2);
    if (len2 < len1) {
        return retVal;
    }

    int Count1[COUNT_SIZE];
    memset(Count1, 0, sizeof(Count1));
    int Count2[COUNT_SIZE];
    memset(Count2, 0, sizeof(Count2));

    int i;
    for (i = 0; i < len1; ++i) {
        ++Count1[(unsigned int)(s1[i] - 'a')];
        ++Count2[(unsigned int)(s2[i] - 'a')];
    }
    if (IsCountEqual(Count1, Count2) == true) {
        retVal = true;
        return retVal;
    }

    for (i = len1; i < len2; ++i) {
        ++Count2[(unsigned int)(s2[i] - 'a')];
        --Count2[(unsigned int)(s2[i - len1] - 'a')];
        if (IsCountEqual(Count1, Count2) == true) {
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
#define MAX_COUNT_SIZE (26)  // s1 and s2 consist of lowercase English letters.
   public:
    bool checkInclusion(string s1, string s2) {
        bool retVal = false;

        int len1 = s1.length();
        int len2 = s2.length();
        if (len2 < len1) {
            return retVal;
        }

        vector<int> count1(MAX_COUNT_SIZE, 0);
        vector<int> count2(MAX_COUNT_SIZE, 0);

        for (int i = 0; i < len1; ++i) {
            ++count1[s1[i] - 'a'];
            ++count2[s2[i] - 'a'];
        }
        if (count1 == count2) {
            retVal = true;
            return retVal;
        }

        for (int i = len1; i < len2; ++i) {
            ++count2[s2[i] - 'a'];
            --count2[s2[i - len1] - 'a'];
            if (count1 == count2) {
                retVal = true;
                return retVal;
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
    def checkInclusion(self, s1: str, s2: str) -> bool:
```

</details>

<details><summary>Rust</summary>

```rust
const COUNT_SIZE: usize = 26; // s1 and s2 consist of lowercase English letters.
impl Solution {
    pub fn check_inclusion(s1: String, s2: String) -> bool {
        let mut ret_val = false;

        let len1 = s1.len();
        let len2 = s2.len();
        if len2 < len1 {
            return ret_val;
        }

        let mut count1: [usize; COUNT_SIZE] = [0; COUNT_SIZE];
        let mut count2: [usize; COUNT_SIZE] = [0; COUNT_SIZE];

        for i in 0..len1 {
            count1[(s1.chars().nth(i).unwrap() as u8 - b'a') as usize] += 1;
            count2[(s2.chars().nth(i).unwrap() as u8 - b'a') as usize] += 1;
        }
        if count1 == count2 {
            ret_val = true;
            return ret_val;
        }

        for i in len1..len2 {
            count2[(s2.chars().nth(i).unwrap() as u8 - b'a') as usize] += 1;
            count2[(s2.chars().nth(i - len1).unwrap() as u8 - b'a') as usize] -= 1;
            if count1 == count2 {
                ret_val = true;
                break;
            }
        }

        return ret_val;
    }
}
```

</details>

## [643. Maximum Average Subarray I](https://leetcode.com/problems/maximum-average-subarray-i/)

- [Official](https://leetcode.com/problems/maximum-average-subarray-i/editorial/)
- [Official](https://leetcode.cn/problems/maximum-average-subarray-i/solutions/590322/zi-shu-zu-zui-da-ping-jun-shu-i-by-leetc-us1k/)

<details><summary>Description</summary>

```text
You are given an integer array nums consisting of n elements, and an integer k.

Find a contiguous subarray whose length is equal to k that has the maximum average value and return this value.
Any answer with a calculation error less than 10-5 will be accepted.

Example 1:
Input: nums = [1,12,-5,-6,50,3], k = 4
Output: 12.75000
Explanation: Maximum average is (12 - 5 - 6 + 50) / 4 = 51 / 4 = 12.75

Example 2:
Input: nums = [5], k = 1
Output: 5.00000

Constraints:
n == nums.length
1 <= k <= n <= 10^5
-10^4 <= nums[i] <= 10^4
```

</details>

<details><summary>C</summary>

```c
double findMaxAverage(int* nums, int numsSize, int k) {
    double retVal = 0;

    int sum = 0;
    int i;
    for (i = 0; i < k; ++i) {
        sum += nums[i];
    }
    double max = sum;

    for (i = k; i < numsSize; ++i) {
        sum += (nums[i] - nums[i - k]);
        max = fmax(max, sum);
    }
    retVal = max / k;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    double findMaxAverage(vector<int>& nums, int k) {
        double retVal;

        int numsSize = nums.size();

        double sum = 0;
        for (int i = 0; i < k; ++i) {
            sum += nums[i];
        }
        double maxValue = sum;

        for (int i = k; i < numsSize; ++i) {
            sum += (nums[i] - nums[i - k]);
            maxValue = max(maxValue, sum);
        }
        retVal = maxValue / k;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def findMaxAverage(self, nums: List[int], k: int) -> float:
        retVal = 0

        numsSize = len(nums)

        sum = 0
        for i in range(k):
            sum += nums[i]
        maxValue = sum

        for i in range(k, numsSize):
            sum += (nums[i] - nums[i - k])
            maxValue = max(maxValue, sum)
        retVal = maxValue / k

        return retVal
```

</details>

## [713. Subarray Product Less Than K](https://leetcode.com/problems/subarray-product-less-than-k/)

- [Official](https://leetcode.com/problems/subarray-product-less-than-k/solutions/127670/subarray-product-less-than-k/)
- [Official](https://leetcode.cn/problems/subarray-product-less-than-k/solutions/1463527/cheng-ji-xiao-yu-k-de-zi-shu-zu-by-leetc-92wl/)

<details><summary>Description</summary>

```text
Given an array of integers nums and an integer k,
return the number of contiguous subarrays where the product of all the elements in the subarray is strictly less than k.

Example 1:
Input: nums = [10,5,2,6], k = 100
Output: 8
Explanation: The 8 subarrays that have product less than 100 are:
[10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6]
Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.

Example 2:
Input: nums = [1,2,3], k = 0
Output: 0

Constraints:
1 <= nums.length <= 3 * 10^4
1 <= nums[i] <= 1000
0 <= k <= 10^6
```

</details>

<details><summary>C</summary>

```c
int numSubarrayProductLessThanK(int* nums, int numsSize, int k) {
    int retVal = 0;

    /* the product of nums could not be strictly less than 1
     *  1 <= nums.length <= 3 * 10^4
     *  1 <= nums[i] <= 1000
     *  0 <= k <= 10^6
     */
    if (k <= 1) {
        return retVal;
    }

    int product = 1;
    int right = 0;
    int left = 0;
    for (right=0; right<numsSize; right++) {
        /* Sliding window with Two Pointer
         *  +--------------------------------------------+
         *  |    0   |      1      |   2   |      3      |
         *  +--------------------------------------------+
         *  |   10   |      5      |   2   |      6      |
         *  +--------------------------------------------+
         *  |  right -1-> right -2-> right -4-> right    |
         *  |  left  -3-> left                           |
         *  +--------------------------------------------+
         *  | product = 10                               |
         *  | product = 50, product = 100                |
         *  | product = 10                               |
         *  | product = 60                               |
         *  +--------------------------------------------+
         */
        product *= nums[right];
        while (product >= k) {
            product /= nums[left];
            left++;
        }

        retVal += (right - left + 1);
    }

    return retVal;
}
```

</details>

## [904. Fruit Into Baskets](https://leetcode.com/problems/fruit-into-baskets/)  1516

- [Official](https://leetcode.com/problems/fruit-into-baskets/solutions/2960000/fruit-into-baskets/)
- [Official](https://leetcode.cn/problems/fruit-into-baskets/solutions/1893352/shui-guo-cheng-lan-by-leetcode-solution-1uyu/)

<details><summary>Description</summary>

```text
You are visiting a farm that has a single row of fruit trees arranged from left to right.
The trees are represented by an integer array fruits where fruits[i] is the type of fruit the ith tree produces.

You want to collect as much fruit as possible. However, the owner has some strict rules that you must follow:
- You only have two baskets, and each basket can only hold a single type of fruit.
  There is no limit on the amount of fruit each basket can hold.
- Starting from any tree of your choice, you must pick exactly one fruit from every tree (including the start tree)
  while moving to the right. The picked fruits must fit in one of your baskets.
- Once you reach a tree with fruit that cannot fit in your baskets, you must stop.

Given the integer array fruits, return the maximum number of fruits you can pick.

Example 1:
Input: fruits = [1,2,1]
Output: 3
Explanation: We can pick from all 3 trees.

Example 2:
Input: fruits = [0,1,2,2]
Output: 3
Explanation: We can pick from trees [1,2,2].
If we had started at the first tree, we would only pick from trees [0,1].

Example 3:
Input: fruits = [1,2,3,2,2]
Output: 4
Explanation: We can pick from trees [2,3,2,2].
If we had started at the first tree, we would only pick from trees [1,2].

Constraints:
1 <= fruits.length <= 10^5
0 <= fruits[i] < fruits.length
```

</details>

<details><summary>C</summary>

```c
int totalFruit(int* fruits, int fruitsSize) {
    int retVal = 0;

    // 1 <= fruits.length <= 10^5, 0 <= fruits[i] < fruits.length.
#define MAX_HASHTABLE ((int)(1e5))
    int HashTable[MAX_HASHTABLE];
    memset(HashTable, 0, sizeof(HashTable));
    unsigned int countHashTable = 0;
    int head = 0;
    int tail = 0;
    /* Example
     *          +--------------------------------------------+-----------------------------+
     *          | 3 | 3 | 3 | 1 | 2 | 1 | 1 | 2 | 3 | 3 | 4  |                             |
     *          +--------------------------------------------+-------------------------+---+
     *    tail  | 0 > 1 > 2 > 3 > 4                          | size: 1 > 1 > 1 > 2 > 3 |   |
     *    head  | 0                                          |  max: 1 > 2 > 3 > 4     | 4 |
     *          +--------------------------------------------+-------------------------+---|
     *    tail  |                 4                          | size: 3 > 3 > 3 > 2     |   |
     *    head  | 0 > 1 > 2 > 3                              |  max: 4 > 2             | 4 |
     *          +--------------------------------------------+-------------------------+---+
     *    tail  |                 4 > 5 > 6 > 7 > 8          | size: 2 > 2 > 2 > 2 > 3 |   |
     *    head  |             3                              |  max: 2 > 3 > 4 > 5     | 5 |
     *          +--------------------------------------------+-------------------------+---+
     *    tail  |                                 8          | size: 3 > 3 > 3 > 3 > 2 |   |
     *    head  |             3 > 4 > 5 > 6 > 7              |  max: 5 > 2             | 5 |
     *          +--------------------------------------------+-------------------------+---+
     *    tail  |                                 8 > 9 > 10 | size: 2 > 2 > 3         |   |
     *    head  |                             7              |  max: 2 > 3             | 5 |
     *          +--------------------------------------------+-------------------------+---+
     *    tail  |                                         10 | size: 3 > 2             |   |
     *    head  |                             7 > 8          |  max: 3 > 3             | 5 |
     *          +--------------------------------------------+-------------------------+---+
     */
    while (tail < fruitsSize) {
        if (HashTable[fruits[tail]] == 0) {
            ++countHashTable;
        }
        ++HashTable[fruits[tail]];

        while (countHashTable > 2) {
            --HashTable[fruits[head]];
            if (HashTable[fruits[head]] == 0) {
                --countHashTable;
            }
            ++head;
        }
        retVal = fmax(retVal, tail - head + 1);

        ++tail;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int totalFruit(vector<int>& fruits) {
        int retVal = 0;

        unordered_map<int, int> hashTable;
        int len = fruits.size();
        int head = 0;
        int tail = 0;
        /* Example
         *          +--------------------------------------------+-----------------------------+
         *          | 3 | 3 | 3 | 1 | 2 | 1 | 1 | 2 | 3 | 3 | 4  |                             |
         *          +--------------------------------------------+-------------------------+---+
         *    tail  | 0 > 1 > 2 > 3 > 4                          | size: 1 > 1 > 1 > 2 > 3 |   |
         *    head  | 0                                          |  max: 1 > 2 > 3 > 4     | 4 |
         *          +--------------------------------------------+-------------------------+---|
         *    tail  |                 4                          | size: 3 > 3 > 3 > 2     |   |
         *    head  | 0 > 1 > 2 > 3                              |  max: 4 > 2             | 4 |
         *          +--------------------------------------------+-------------------------+---+
         *    tail  |                 4 > 5 > 6 > 7 > 8          | size: 2 > 2 > 2 > 2 > 3 |   |
         *    head  |             3                              |  max: 2 > 3 > 4 > 5     | 5 |
         *          +--------------------------------------------+-------------------------+---+
         *    tail  |                                 8          | size: 3 > 3 > 3 > 3 > 2 |   |
         *    head  |             3 > 4 > 5 > 6 > 7              |  max: 5 > 2             | 5 |
         *          +--------------------------------------------+-------------------------+---+
         *    tail  |                                 8 > 9 > 10 | size: 2 > 2 > 3         |   |
         *    head  |                             7              |  max: 2 > 3             | 5 |
         *          +--------------------------------------------+-------------------------+---+
         *    tail  |                                         10 | size: 3 > 2             |   |
         *    head  |                             7 > 8          |  max: 3 > 3             | 5 |
         *          +--------------------------------------------+-------------------------+---+
         */
        while (tail < len) {
            hashTable[fruits[tail]]++;

            while (hashTable.size() > 2) {
                hashTable[fruits[head]]--;
                if (hashTable[fruits[head]] == 0) {
                    hashTable.erase(fruits[head]);
                }
                head++;
            }
            retVal = max(retVal, tail - head + 1);

            tail++;
        }

        return retVal;
    }
};
```

</details>

## [992. Subarrays with K Different Integers](https://leetcode.com/problems/subarrays-with-k-different-integers/)  2210

- [Official](https://leetcode.cn/problems/subarrays-with-k-different-integers/solutions/597667/k-ge-bu-tong-zheng-shu-de-zi-shu-zu-by-l-ud34/)

<details><summary>Description</summary>

```text
Given an integer array nums and an integer k, return the number of good subarrays of nums.

A good array is an array where the number of different integers in that array is exactly k.
- For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.

A subarray is a contiguous part of an array.

Example 1:
Input: nums = [1,2,1,2,3], k = 2
Output: 7
Explanation: Subarrays formed with exactly 2 different integers: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2]

Example 2:
Input: nums = [1,2,1,3,4], k = 3
Output: 3
Explanation: Subarrays formed with exactly 3 different integers: [1,2,1,3], [2,1,3], [1,3,4].

Constraints:
1 <= nums.length <= 2 * 10^4
1 <= nums[i], k <= nums.length
```

</details>

<details><summary>C</summary>

```c
int atMostDifferent(int* nums, int numsSize, int k) {
    int retVal = 0;

    // 1 <= nums.length <= 2 * 10^4, 1 <= nums[i], k <= nums.length.
#define MAX_HASHTABLE (int)(2 * 1e4 + 4)
    int HashTable[MAX_HASHTABLE];
    memset(HashTable, 0, sizeof(HashTable));
    int countHashTable = 0;
    int head = 0;
    int tail = 0;
    while (tail < numsSize) {
        if (HashTable[nums[tail]] == 0) {
            ++countHashTable;
        }
        ++HashTable[nums[tail]];
        ++tail;

        while (countHashTable > k) {
            --HashTable[nums[head]];
            if (HashTable[nums[head]] == 0) {
                --countHashTable;
            }
            ++head;
        }
        retVal += (tail - head);
    }

    return retVal;
}
int subarraysWithKDistinct(int* nums, int numsSize, int k) {
    int retVal = 0;

    // https://leetcode.com/problems/subarrays-with-k-different-integers/solutions/523136/JavaC++Python-Sliding-Window/
    retVal = atMostDifferent(nums, numsSize, k) - atMostDifferent(nums, numsSize, k - 1);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int atMostDifferent(vector<int>& nums, int k) {
        int retVal = 0;

        unordered_map<int, int> hashTable;
        int len = nums.size();
        int head = 0;
        int tail = 0;
        while (tail < len) {
            hashTable[nums[tail]]++;
            tail++;

            while ((int)hashTable.size() > k) {
                hashTable[nums[head]]--;
                if (hashTable[nums[head]] == 0) {
                    hashTable.erase(nums[head]);
                }
                head++;
            }
            retVal += (tail - head);
        }

        return retVal;
    }
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        int retVal = 0;

        // https://leetcode.com/problems/subarrays-with-k-different-integers/solutions/523136/JavaC++Python-Sliding-Window/
        retVal = atMostDifferent(nums, k) - atMostDifferent(nums, k - 1);

        return retVal;
    }
};
```

</details>

## [1004. Max Consecutive Ones III](https://leetcode.com/problems/max-consecutive-ones-iii/)  1655

- [Official](https://leetcode.cn/problems/max-consecutive-ones-iii/solutions/608931/zui-da-lian-xu-1de-ge-shu-iii-by-leetcod-hw12/)

<details><summary>Description</summary>

```text
Given a binary array nums and an integer k,
return the maximum number of consecutive 1's in the array if you can flip at most k 0's.

Example 1:
Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
Output: 6
Explanation: [1,1,1,0,0,1,1,1,1,1,1]
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.

Example 2:
Input: nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
Output: 10
Explanation: [0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.

Constraints:
1 <= nums.length <= 10^5
nums[i] is either 0 or 1.
0 <= k <= nums.length
```

<details><summary>Hint</summary>

```text
1. One thing's for sure, we will only flip a zero if it extends an existing window of 1s.
   Otherwise, there's no point in doing it, right? Think Sliding Window!
2. Since we know this problem can be solved using the sliding window construct,
   we might as well focus in that direction for hints.
   Basically, in a given window, we can never have > K zeros, right?
3. We don't have a fixed size window in this case.
   The window size can grow and shrink depending upon the number of zeros we have
   (we don't actually have to flip the zeros here!).
4. The way to shrink or expand a window would be based on the number of zeros that can still be flipped and so on.
```

</details>

</details>

<details><summary>C</summary>

```c
int longestOnes(int *nums, int numsSize, int k) {
    int retVal = 0;

    int flip = 0;
    int left = 0;
    int right = 0;
    for (right = 0; right < numsSize; ++right) {
        flip += (1 - nums[right]);
        while (flip > k) {
            flip -= (1 - nums[left]);
            left += 1;
        }

        retVal = fmax(retVal, right - left + 1);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int longestOnes(vector<int>& nums, int k) {
        int retVal = 0;

        int numsSize = nums.size();

        int flip = 0;
        int left = 0;
        int right = 0;
        for (right = 0; right < numsSize; ++right) {
            flip += (1 - nums[right]);
            while (flip > k) {
                flip -= (1 - nums[left]);
                left += 1;
            }

            retVal = max(retVal, right - left + 1);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def longestOnes(self, nums: List[int], k: int) -> int:
        retVal = 0

        numsSize = len(nums)

        flip = 0
        left = 0
        right = 0
        for right in range(numsSize):
            flip += (1 - nums[right])
            while flip > k:
                flip -= (1 - nums[left])
                left += 1

            retVal = max(retVal, right - left + 1)

        return retVal
```

</details>

## [1343. Number of Sub-arrays of Size K and Average Greater than or Equal to Threshold](https://leetcode.com/problems/number-of-sub-arrays-of-size-k-and-average-greater-than-or-equal-to-threshold/)  1317

<details><summary>Description</summary>

```text
Given an array of integers arr and two integers k and threshold,
return the number of sub-arrays of size k and average greater than or equal to threshold.

Example 1:
Input: arr = [2,2,2,2,5,5,5,8], k = 3, threshold = 4
Output: 3
Explanation: Sub-arrays [2,5,5],[5,5,5] and [5,5,8] have averages 4, 5 and 6 respectively.
All other sub-arrays of size 3 have averages less than 4 (the threshold).

Example 2:
Input: arr = [11,13,17,23,29,31,7,5,2,3], k = 3, threshold = 5
Output: 6
Explanation: The first 6 sub-arrays of size 3 have averages greater than 5. Note that averages are not integers.

Constraints:
1 <= arr.length <= 10^5
1 <= arr[i] <= 10^4
1 <= k <= arr.length
0 <= threshold <= 10^4
```

<details><summary>Hint</summary>

```text
1. Start with a window of size K and test its average against the threshold.
2. Keep moving the window by one element maintaining its size k until you cover the whole array.
   count number of windows that satisfy that its average is greater than the threshold.
```

</details>

</details>

<details><summary>C</summary>

```c
int numOfSubarrays(int* arr, int arrSize, int k, int threshold) {
    int retVal = 0;

    long long prefixSum = 0;  // 1 <= arr.length <= 10^5, 1 <= arr[i] <= 10^4, 1 <= k <= arr.length
    int i;
    for (i = 0; i < (k - 1); ++i) {
        prefixSum += arr[i];
    }

    for (i = (k - 1); i < arrSize; ++i) {
        prefixSum += arr[i];
        if ((prefixSum / k) >= threshold) {
            ++retVal;
        }

        prefixSum -= arr[i - k + 1];
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        int retVal = 0;

        int arrSize = arr.size();

        long long prefixSum = 0;  // 1 <= arr.length <= 10^5, 1 <= arr[i] <= 10^4, 1 <= k <= arr.length
        for (int i = 0; i < (k - 1); ++i) {
            prefixSum += arr[i];
        }

        for (int i = (k - 1); i < arrSize; ++i) {
            prefixSum += arr[i];
            if ((prefixSum / k) >= threshold) {
                ++retVal;
            }

            prefixSum -= arr[i - k + 1];
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def numOfSubarrays(self, arr: List[int], k: int, threshold: int) -> int:
        retVal = 0

        arrSize = len(arr)

        prefixSum = 0
        for i in range(k-1):
            prefixSum += arr[i]

        for i in range(k-1, arrSize):
            prefixSum += arr[i]
            if prefixSum // k >= threshold:
                retVal += 1
            prefixSum -= arr[i-k+1]

        return retVal
```

</details>

## [1423. Maximum Points You Can Obtain from Cards](https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/)  1573

- [Official](https://leetcode.cn/problems/maximum-points-you-can-obtain-from-cards/solutions/514347/ke-huo-de-de-zui-da-dian-shu-by-leetcode-7je9/)

<details><summary>Description</summary>

```text
There are several cards arranged in a row, and each card has an associated number of points.
The points are given in the integer array cardPoints.

In one step, you can take one card from the beginning or from the end of the row. You have to take exactly k cards.

Your score is the sum of the points of the cards you have taken.

Given the integer array cardPoints and the integer k, return the maximum score you can obtain.

Example 1:
Input: cardPoints = [1,2,3,4,5,6,1], k = 3
Output: 12
Explanation: After the first step, your score will always be 1.
However, choosing the rightmost card first will maximize your total score.
The optimal strategy is to take the three cards on the right, giving a final score of 1 + 6 + 5 = 12.

Example 2:
Input: cardPoints = [2,2,2], k = 2
Output: 4
Explanation: Regardless of which two cards you take, your score will always be 4.

Example 3:
Input: cardPoints = [9,7,7,9,7,7,9], k = 7
Output: 55
Explanation: You have to take all the cards. Your score is the sum of points of all cards.

Constraints:
1 <= cardPoints.length <= 10^5
1 <= cardPoints[i] <= 10^4
1 <= k <= cardPoints.length
```

</details>

<details><summary>C</summary>

```c
int maxScore(int* cardPoints, int cardPointsSize, int k) {
    int retVal = 0;

    /* maximum sum of k elements that take one card from the beginning or from the end of the row
     * => minimum sum of n-k continuously elements
     *
     *  +---------------------------+
     *  | 1 | 2 | 3 | 4 | 5 | 6 | 1 |
     *  +---------------------------+
     *  |->minsum(n-k)<-|
     *      |->minsum(n-k)<-|
     *          |->minsum(n-k)<-|
     *              |->minsum(n-k)<-|
     */
    int windowSum = 0;
    int windowSize = cardPointsSize - k;
    int i;
    for (i = 0; i < windowSize; ++i) {
        windowSum += cardPoints[i];
    }

    int totalSum = windowSum;
    int minSum = windowSum;
    for (i = windowSize; i < cardPointsSize; ++i) {
        totalSum += cardPoints[i];

        windowSum += (cardPoints[i] - cardPoints[i - windowSize]);
        minSum = fmin(minSum, windowSum);
    }
    retVal = totalSum - minSum;

    return retVal;
}
```

</details>

## [1456. Maximum Number of Vowels in a Substring of Given Length](https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/)  1263

- [Official](https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/editorial/)
- [Official](https://leetcode.cn/problems/maximum-number-of-vowels-in-a-substring-of-given-length/solutions/518995/ding-chang-zi-chuan-zhong-yuan-yin-de-zu-4ka7/)

<details><summary>Description</summary>

```text
Given a string s and an integer k, return the maximum number of vowel letters in any substring of s with length k.

Vowel letters in English are 'a', 'e', 'i', 'o', and 'u'.

Example 1:
Input: s = "abciiidef", k = 3
Output: 3
Explanation: The substring "iii" contains 3 vowel letters.

Example 2:
Input: s = "aeiou", k = 2
Output: 2
Explanation: Any substring of length 2 contains 2 vowels.

Example 3:
Input: s = "leetcode", k = 3
Output: 2
Explanation: "lee", "eet" and "ode" contain 2 vowels.

Constraints:
1 <= s.length <= 10^5
s consists of lowercase English letters.
1 <= k <= s.length
```

<details><summary>Hint</summary>

```text
1. Keep a window of size k and maintain the number of vowels in it.
2. Keep moving the window and update the number of vowels while moving. Answer is max number of vowels of any window.
```

</details>

</details>

<details><summary>C</summary>

```c
int maxVowels(char* s, int k) {
    int retVal = 0;

#define MAX_VOWELS_SIZE (5)
    char vowels[MAX_VOWELS_SIZE] = {'a', 'e', 'i', 'o', 'u'};

    int i, j;

    int count = 0;
    for (i = 0; i < k; ++i) {
        for (j = 0; j < MAX_VOWELS_SIZE; ++j) {
            if (s[i] == vowels[j]) {
                ++count;
                break;
            }
        }
    }
    retVal = count;

    int sSize = strlen(s);
    for (i = k; i < sSize; ++i) {
        for (j = 0; j < MAX_VOWELS_SIZE; ++j) {
            if (s[i] == vowels[j]) {
                ++count;
            }

            if (s[i - k] == vowels[j]) {
                --count;
            }
        }
        retVal = fmax(retVal, count);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxVowels(string s, int k) {
        int retVal = 0;

        vector<char> vowels = {'a', 'e', 'i', 'o', 'u'};

        int count = 0;
        for (int i = 0; i < k; ++i) {
            for (auto c : vowels) {
                if (s[i] == c) {
                    ++count;
                    break;
                }
            }
        }
        retVal = count;

        int sSize = s.size();
        for (int i = k; i < sSize; ++i) {
            for (auto c : vowels) {
                if (s[i] == c) {
                    ++count;
                }

                if (s[i - k] == c) {
                    --count;
                }
            }
            retVal = max(retVal, count);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxVowels(self, s: str, k: int) -> int:
        retVal = 0

        vowels = {'a', 'e', 'i', 'o', 'u'}

        count = 0
        for i in range(k):
            count += int(s[i] in vowels)
        retVal = count

        for i in range(k, len(s)):
            count += int(s[i] in vowels)
            count -= int(s[i - k] in vowels)
            retVal = max(retVal, count)

        return retVal
```

</details>

## [1493. Longest Subarray of 1's After Deleting One Element](https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/)  1423

- [Official](https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/editorial/)
- [Official](https://leetcode.cn/problems/longest-subarray-of-1s-after-deleting-one-element/solutions/327132/shan-diao-yi-ge-yuan-su-yi-hou-quan-wei-1-de-zui-c/)

<details><summary>Description</summary>

```text
Given a binary array nums, you should delete one element from it.

Return the size of the longest non-empty subarray containing only 1's in the resulting array.
Return 0 if there is no such subarray.

Example 1:
Input: nums = [1,1,0,1]
Output: 3
Explanation: After deleting the number in position 2, [1,1,1] contains 3 numbers with value of 1's.

Example 2:
Input: nums = [0,1,1,1,0,1,1,0,1]
Output: 5
Explanation: After deleting the number in position 4, [0,1,1,1,1,1,0,1] longest subarray with value of 1's is [1,1,1,1,1].

Example 3:
Input: nums = [1,1,1]
Output: 2
Explanation: You must delete one element.

Constraints:
1 <= nums.length <= 10^5
nums[i] is either 0 or 1.
```

<details><summary>Hint</summary>

```text
1. Maintain a sliding window where there is at most one zero on it.
```

</details>

</details>

<details><summary>C</summary>

```c
int longestSubarray(int* nums, int numsSize) {
    int retVal = 0;

    int i;
    int start = 0;
    int zeroCount = 0;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] == 0) {
            ++zeroCount;
        }

        while (zeroCount > 1) {
            if (nums[start] == 0) {
                --zeroCount;
            }
            ++start;
        }

        retVal = fmax(retVal, i - start);
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

        int numsSize = nums.size();

        int start = 0;
        int zeroCount = 0;
        for (int i = 0; i < numsSize; ++i) {
            if (nums[i] == 0) {
                ++zeroCount;
            }

            while (zeroCount > 1) {
                if (nums[start] == 0) {
                    --zeroCount;
                }
                ++start;
            }

            retVal = max(retVal, i - start);
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

        numsSize = len(nums)

        start = 0
        zeroCount = 0
        for i in range(numsSize):
            if nums[i] == 0:
                zeroCount += 1

            while zeroCount > 1:
                if nums[start] == 0:
                    zeroCount -= 1
                start += 1

            retVal = max(retVal, i-start)

        return retVal
```

</details>

## [1658. Minimum Operations to Reduce X to Zero](https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/)  1817

- [Official](https://leetcode.cn/problems/minimum-operations-to-reduce-x-to-zero/solutions/2047253/jiang-x-jian-dao-0-de-zui-xiao-cao-zuo-s-hl7u/)

<details><summary>Description</summary>

```text
You are given an integer array nums and an integer x.
In one operation, you can either remove the leftmost
or the rightmost element from the array nums and subtract its value from x.
Note that this modifies the array for future operations.

Return the minimum number of operations to reduce x to exactly 0 if it is possible, otherwise, return -1.

Example 1:
Input: nums = [1,1,4,2,3], x = 5
Output: 2
Explanation: The optimal solution is to remove the last two elements to reduce x to zero.

Example 2:
Input: nums = [5,6,7,8,9], x = 4
Output: -1

Example 3:
Input: nums = [3,2,20,1,1,3], x = 10
Output: 5
Explanation: The optimal solution is to remove the last three elements
and the first two elements (5 operations in total) to reduce x to zero.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^4
1 <= x <= 10^9
```

<details><summary>Hint</summary>

```text
1. Think in reverse; instead of finding the minimum prefix + suffix, find the maximum subarray.
2. Finding the maximum subarray is standard and can be done greedily.
```

</details>

</details>

<details><summary>C</summary>

```c
int minOperations(int* nums, int numsSize, int x) {
    int retVal = -1;

    int target = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        target += nums[i];
    }
    target -= x;
    if (target < 0) {
        return retVal;
    }

    /* https://leetcode.cn/problems/minimum-operations-to-reduce-x-to-zero/solutions/485281/shi-yong-hua-dong-chuang-kou-zhao-zhong-jian-zui-c/
     *  sum(fragment of nums) = sum(nums) - x
     *  Example
     *  +-------------------+   +----------------------------+
     *  | sum-x     | x=5   |   | x=10  | sum-x  | x=10      |
     *  | = 11-5    |       |   |       | =30-10 |           |
     *  +-------------------+   +----------------------------+
     *  | 1 | 1 | 4 | 2 | 3 |   | 3 | 2 |   20   | 1 | 1 | 3 |
     *  +-------------------+   +----------------------------+
     */
    int sum = 0;
    int head = 0;
    int tail = 0;
    for (tail = 0; tail < numsSize; ++tail) {
        sum += nums[tail];

        while (sum > target) {
            sum -= nums[head];
            ++head;
        }

        if (sum == target) {
            retVal = fmax(retVal, (tail - head + 1));
        }
    }
    retVal = ((retVal < 0) ? (-1) : (numsSize - retVal));

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minOperations(vector<int>& nums, int x) {
        int retVal = -1;

        int target = accumulate(nums.begin(), nums.end(), 0) - x;
        if (target < 0) {
            return retVal;
        }

        /* https://leetcode.cn/problems/minimum-operations-to-reduce-x-to-zero/solutions/485281/shi-yong-hua-dong-chuang-kou-zhao-zhong-jian-zui-c/
         *  sum(fragment of nums) = sum(nums) - x
         *  Example
         *  +-------------------+   +----------------------------+
         *  | sum-x     | x=5   |   | x=10  | sum-x  | x=10      |
         *  | = 11-5    |       |   |       | =30-10 |           |
         *  +-------------------+   +----------------------------+
         *  | 1 | 1 | 4 | 2 | 3 |   | 3 | 2 |   20   | 1 | 1 | 3 |
         *  +-------------------+   +----------------------------+
         */
        int numsSize = nums.size();
        int sum = 0;
        int start = 0;
        for (int tail = 0; tail < numsSize; ++tail) {
            sum += nums[tail];
            while (sum > target) {
                sum -= nums[start++];
            }

            if (sum == target) {
                retVal = max(retVal, tail - start + 1);
            }
        }

        if (retVal != -1) {
            retVal = numsSize - retVal;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minOperations(self, nums: List[int], x: int) -> int:
        retVal = -1

        target = sum(nums) - x
        if target < 0:
            return retVal

        # /* https://leetcode.cn/problems/minimum-operations-to-reduce-x-to-zero/solutions/485281/shi-yong-hua-dong-chuang-kou-zhao-zhong-jian-zui-c/
        #  *  sum(fragment of nums) = sum(nums) - x
        #  *  Example
        #  *  +-------------------+   +----------------------------+
        #  *  | sum-x     | x=5   |   | x=10  | sum-x  | x=10      |
        #  *  | = 11-5    |       |   |       | =30-10 |           |
        #  *  +-------------------+   +----------------------------+
        #  *  | 1 | 1 | 4 | 2 | 3 |   | 3 | 2 |   20   | 1 | 1 | 3 |
        #  *  +-------------------+   +----------------------------+
        #  */
        numsSize = len(nums)
        sumOfNums = 0
        start = 0
        for tail in range(numsSize):
            sumOfNums += nums[tail]
            while sumOfNums > target:
                sumOfNums -= nums[start]
                start += 1

            if sumOfNums == target:
                retVal = max(retVal, tail-start+1)

        if retVal != -1:
            retVal = numsSize - retVal

        return retVal
```

</details>

## [1838. Frequency of the Most Frequent Element](https://leetcode.com/problems/frequency-of-the-most-frequent-element/)  1876

- [Official](https://leetcode.com/problems/frequency-of-the-most-frequent-element/editorial/)
- [Official](https://leetcode.cn/problems/frequency-of-the-most-frequent-element/solutions/742719/zui-gao-pin-yuan-su-de-pin-shu-by-leetco-q5g9/)

<details><summary>Description</summary>

```text
The frequency of an element is the number of times it occurs in an array.

You are given an integer array nums and an integer k.
In one operation, you can choose an index of nums and increment the element at that index by 1.

Return the maximum possible frequency of an element after performing at most k operations.

Example 1:
Input: nums = [1,2,4], k = 5
Output: 3
Explanation: Increment the first element three times and the second element two times to make nums = [4,4,4].
4 has a frequency of 3.

Example 2:
Input: nums = [1,4,8,13], k = 5
Output: 2
Explanation: There are multiple optimal solutions:
- Increment the first element three times to make nums = [4,4,8,13]. 4 has a frequency of 2.
- Increment the second element four times to make nums = [1,8,8,13]. 8 has a frequency of 2.
- Increment the third element five times to make nums = [1,4,13,13]. 13 has a frequency of 2.

Example 3:
Input: nums = [3,9,6], k = 2
Output: 1

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^5
1 <= k <= 10^5
```

<details><summary>Hint</summary>

```text
1. Note that you can try all values in a brute force manner and find the maximum frequency of that value.
2. To find the maximum frequency of a value consider the biggest elements smaller than or equal to this value
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int maxFrequency(int* nums, int numsSize, int k) {
    int retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    long current = 0;
    int left = 0;
    long target;
    int right;
    for (right = 0; right < numsSize; right++) {
        target = nums[right];
        current += target;

        if ((right - left + 1) * target - current > k) {
            current -= nums[left];
            left++;
        }
    }
    retVal = numsSize - left;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxFrequency(vector<int>& nums, int k) {
        int retVal = 0;

        sort(nums.begin(), nums.end());

        int numsSize = nums.size();
        long current = 0;
        int left = 0;
        for (int right = 0; right < numsSize; right++) {
            long target = nums[right];
            current += target;

            if ((right - left + 1) * target - current > k) {
                current -= nums[left];
                left++;
            }
        }
        retVal = numsSize - left;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxFrequency(self, nums: List[int], k: int) -> int:
        retVal = 0

        nums.sort()

        numsSize = len(nums)
        current = 0
        left = 0
        for right in range(numsSize):
            target = nums[right]
            current += target

            if (right - left + 1) * target - current > k:
                current -= nums[left]
                left += 1
        retVal = numsSize - left

        return retVal
```

</details>

## [2090. K Radius Subarray Averages](https://leetcode.com/problems/k-radius-subarray-averages/)  1358

- [Official](https://leetcode.com/problems/k-radius-subarray-averages/editorial/)
- [Official](https://leetcode.cn/problems/k-radius-subarray-averages/solutions/1127983/ban-jing-wei-k-de-zi-shu-zu-ping-jun-zhi-jqo8/)

<details><summary>Description</summary>

```text
You are given a 0-indexed array nums of n integers, and an integer k.

The k-radius average for a subarray of nums centered at some index i
with the radius k is the average of all elements in nums between the indices i - k and i + k (inclusive).
If there are less than k elements before or after the index i, then the k-radius average is -1.

Build and return an array avgs of length n where avgs[i] is the k-radius average for the subarray centered at index i.

The average of x elements is the sum of the x elements divided by x, using integer division.
The integer division truncates toward zero, which means losing its fractional part.

For example, the average of four elements 2, 3, 1, and 5 is (2 + 3 + 1 + 5) / 4 = 11 / 4 = 2.75, which truncates to 2.

Example 1:
Input: nums = [7,4,3,9,1,8,5,2,6], k = 3
Output: [-1,-1,-1,5,4,4,-1,-1,-1]
Explanation:
- avg[0], avg[1], and avg[2] are -1 because there are less than k elements before each index.
- The sum of the subarray centered at index 3 with radius 3 is: 7 + 4 + 3 + 9 + 1 + 8 + 5 = 37.
  Using integer division, avg[3] = 37 / 7 = 5.
- For the subarray centered at index 4, avg[4] = (4 + 3 + 9 + 1 + 8 + 5 + 2) / 7 = 4.
- For the subarray centered at index 5, avg[5] = (3 + 9 + 1 + 8 + 5 + 2 + 6) / 7 = 4.
- avg[6], avg[7], and avg[8] are -1 because there are less than k elements after each index.

Example 2:
Input: nums = [100000], k = 0
Output: [100000]
Explanation:
- The sum of the subarray centered at index 0 with radius 0 is: 100000.
  avg[0] = 100000 / 1 = 100000.

Example 3:
Input: nums = [8], k = 100000
Output: [-1]
Explanation:
- avg[0] is -1 because there are less than k elements before and after index 0.

Constraints:
n == nums.length
1 <= n <= 10^5
0 <= nums[i], k <= 10^5
```

<details><summary>Hint</summary>

```text
1. To calculate the average of a subarray, you need the sum and the K. K is already given.
   How could you quickly calculate the sum of a subarray?
2. Use the Prefix Sums method to calculate the subarray sums.
3. It is possible that the sum of all the elements does not fit in a 32-bit integer type.
   Be sure to use a 64-bit integer type for the prefix sum array.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getAverages(int* nums, int numsSize, int k, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = numsSize;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, -1, ((*returnSize) * sizeof(int)));

    int i;

    // n == nums.length, 1 <= n <= 10^5, 0 <= nums[i], k <= 10^5
    long long prefixSum[numsSize + 1];
    memset(prefixSum, 0, sizeof(prefixSum));
    for (i = 0; i < numsSize; ++i) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    for (i = k; i < numsSize - k; ++i) {
        pRetVal[i] = (prefixSum[i + k + 1] - prefixSum[i - k]) / (2 * k + 1);
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> getAverages(vector<int>& nums, int k) {
        vector<int> retVal;

        int numsSize = nums.size();

        // n == nums.length, 1 <= n <= 10^5, 0 <= nums[i], k <= 10^5
        vector<long long> prefixSum(numsSize + 1, 0);
        for (int i = 0; i < numsSize; ++i) {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
        }

        retVal.resize(numsSize, -1);
        for (int i = k; i < numsSize - k; ++i) {
            retVal[i] = (prefixSum[i + k + 1] - prefixSum[i - k]) / (2 * k + 1);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def getAverages(self, nums: List[int], k: int) -> List[int]:
        retVal = []

        numsSize = len(nums)

        prefixSum = [0]
        for i in range(numsSize):
            prefixSum.append(prefixSum[i] + nums[i])

        retVal = [-1] * numsSize
        for i in range(k, numsSize - k):
            retVal[i] = (prefixSum[i + k + 1] - prefixSum[i - k]) // (2 * k + 1)

        return retVal
```

</details>

## [2024. Maximize the Confusion of an Exam](https://leetcode.com/problems/maximize-the-confusion-of-an-exam/)  1643

- [Official](https://leetcode.com/problems/maximize-the-confusion-of-an-exam/editorial/)
- [Official](https://leetcode.cn/problems/maximize-the-confusion-of-an-exam/solutions/1368825/kao-shi-de-zui-da-kun-rao-du-by-leetcode-qub5/)

<details><summary>Description</summary>

```text
A teacher is writing a test with n true/false questions, with 'T' denoting true and 'F' denoting false.
He wants to confuse the students by maximizing the number of consecutive questions with the same answer
(multiple trues or multiple falses in a row).

You are given a string answerKey, where answerKey[i] is the original answer to the ith question.
In addition, you are given an integer k, the maximum number of times you may perform the following operation:
- Change the answer key for any question to 'T' or 'F' (i.e., set answerKey[i] to 'T' or 'F').

Return the maximum number of consecutive 'T's or 'F's in the answer key after performing the operation at most k times.

Example 1:
Input: answerKey = "TTFF", k = 2
Output: 4
Explanation: We can replace both the 'F's with 'T's to make answerKey = "TTTT".
There are four consecutive 'T's.

Example 2:
Input: answerKey = "TFFT", k = 1
Output: 3
Explanation: We can replace the first 'T' with an 'F' to make answerKey = "FFFT".
Alternatively, we can replace the second 'T' with an 'F' to make answerKey = "TFFF".
In both cases, there are three consecutive 'F's.

Example 3:
Input: answerKey = "TTFTTFTT", k = 1
Output: 5
Explanation: We can replace the first 'F' to make answerKey = "TTTTTFTT"
Alternatively, we can replace the second 'F' to make answerKey = "TTFTTTTT".
In both cases, there are five consecutive 'T's.

Constraints:
n == answerKey.length
1 <= n <= 5 * 10^4
answerKey[i] is either 'T' or 'F'
1 <= k <= n
```

<details><summary>Hint</summary>

```text
1. Can we use the maximum length at the previous position to help us find the answer for the current position?
2. Can we use binary search to find the maximum consecutive same answer at every position?
```

</details>

</details>

<details><summary>C</summary>

```c
int maxConsecutiveAnswers(char* answerKey, int k) {
    int retVal = 0;

    // answerKey[i] is either 'T' or 'F'
#define MAX_RECORD (26)
    int Record[MAX_RECORD];
    memset(Record, 0, sizeof(Record));

    int maxRecord = 0;
    int answerKeySize = strlen(answerKey);
    int left = 0;
    int right = 0;
    while (right < answerKeySize) {
        Record[answerKey[right] - 'A']++;

        maxRecord = fmax(maxRecord, Record[answerKey[right] - 'A']);
        if (right - left + 1 - maxRecord > k) {
            Record[answerKey[left] - 'A']--;
            left++;
        }

        right++;
    }
    retVal = right - left;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxConsecutiveAnswers(string answerKey, int k) {
        int retVal = 0;

        // answerKey[i] is either 'T' or 'F'
#define MAX_RECORD (26)
        vector<int> Record(MAX_RECORD, 0);

        int maxRecord = 0;
        int answerKeySize = answerKey.length();
        int left = 0;
        int right = 0;
        while (right < answerKeySize) {
            Record[answerKey[right] - 'A']++;

            maxRecord = max(maxRecord, Record[answerKey[right] - 'A']);
            if (right - left + 1 - maxRecord > k) {
                Record[answerKey[left] - 'A']--;
                left++;
            }

            right++;
        }
        retVal = right - left;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxConsecutiveAnswers(self, answerKey: str, k: int) -> int:
        retVal = 0

        # answerKey[i] is either 'T' or 'F'
        MAX_RECORD = 26
        Record = [0] * MAX_RECORD

        maxRecord = 0
        answerKeysSize = len(answerKey)
        left = 0
        right = 0
        while right < answerKeysSize:
            idx = ord(answerKey[right]) - ord("A")
            Record[idx] += 1

            maxRecord = max(maxRecord, Record[idx])
            if right - left + 1 - maxRecord > k:
                Record[ord(answerKey[left]) - ord("A")] -= 1
                left += 1

            right += 1

        retVal = right - left

        return retVal
```

</details>

## [2401. Longest Nice Subarray](https://leetcode.com/problems/longest-nice-subarray/)  1749

<details><summary>Description</summary>

```text
You are given an array nums consisting of positive integers.

We call a subarray of nums nice if the bitwise AND of every pair of elements
that are in different positions in the subarray is equal to 0.

Return the length of the longest nice subarray.

A subarray is a contiguous part of an array.

Note that subarrays of length 1 are always considered nice.

Example 1:
Input: nums = [1,3,8,48,10]
Output: 3
Explanation: The longest nice subarray is [3,8,48]. This subarray satisfies the conditions:
- 3 AND 8 = 0.
- 3 AND 48 = 0.
- 8 AND 48 = 0.
It can be proven that no longer nice subarray can be obtained, so we return 3.

Example 2:
Input: nums = [3,1,5,11,13]
Output: 1
Explanation: The length of the longest nice subarray is 1. Any subarray of length 1 can be chosen.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
```

</details>

<details><summary>C</summary>

```c
int longestNiceSubarray(int* nums, int numsSize) {
    int retVal = 0;

    int niceCheck = 0;
    int head = 0;
    int tail = 0;
    while (tail < numsSize) {
        while ((niceCheck & nums[tail]) != 0) {
            niceCheck ^= nums[head];
            ++head;
        }
        retVal = fmax(retVal, tail - head + 1);

        niceCheck |= nums[tail];
        ++tail;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int longestNiceSubarray(vector<int>& nums) {
        int retVal = 0;

        int niceCheck = 0;
        int len = nums.size();
        int head = 0;
        int tail = 0;
        while (tail < len) {
            while ((niceCheck & nums[tail]) != 0) {
                niceCheck ^= nums[head];
                head++;
            }
            retVal = max(retVal, tail - head + 1);

            niceCheck |= nums[tail];
            tail++;
        }

        return retVal;
    }
};
```

</details>

## [2444. Count Subarrays With Fixed Bounds](https://leetcode.com/problems/count-subarrays-with-fixed-bounds/)  2092

<details><summary>Description</summary>

```text
You are given an integer array nums and two integers minK and maxK.

A fixed-bound subarray of nums is a subarray that satisfies the following conditions:
- The minimum value in the subarray is equal to minK.
- The maximum value in the subarray is equal to maxK.
Return the number of fixed-bound subarrays.

A subarray is a contiguous part of an array.

Example 1:
Input: nums = [1,3,5,2,7,5], minK = 1, maxK = 5
Output: 2
Explanation: The fixed-bound subarrays are [1,3,5] and [1,3,5,2].

Example 2:
Input: nums = [1,1,1,1], minK = 1, maxK = 1
Output: 10
Explanation: Every subarray of nums is a fixed-bound subarray. There are 10 possible subarrays.

Constraints:
2 <= nums.length <= 10^5
1 <= nums[i], minK, maxK <= 10^6
```

<details><summary>Hint</summary>

```text
1. Can you solve the problem if all the numbers in the array were between minK and maxK inclusive?
2. Think of the inclusion-exclusion principle.
3. Divide the array into multiple subarrays such that each number in each subarray is between minK and maxK inclusive,
   solve the previous problem for each subarray, and sum all the answers.
```

</details>

</details>

<details><summary>C</summary>

```c
long long countSubarrays(int *nums, int numsSize, int minK, int maxK) {
    long long retVal = 0;

    /* Ref
     *  https://leetcode.com/problems/count-subarrays-with-fixed-bounds/solutions/2708099/java-c-python-sliding-window-with-explanation/
     *  https://leetcode.cn/problems/count-subarrays-with-fixed-bounds/solutions/1895734/fen-xi-ding-jie-zi-shu-zu-de-xing-zhi-yi-qusi/
     *  https://leetcode.cn/problems/count-subarrays-with-fixed-bounds/solutions/1895713/jian-ji-xie-fa-pythonjavacgo-by-endlessc-gag2/
     */
    long long badIdx = -1;
    long long minIdx = -1;
    long long maxIdx = -1;
    for (int i = 0; i < numsSize; ++i) {
        if ((nums[i] < minK) || (nums[i] > maxK)) {
            badIdx = i;
        }

        if (nums[i] == minK) {
            minIdx = i;
        }

        if (nums[i] == maxK) {
            maxIdx = i;
        }

        retVal += fmax(0, fmin(minIdx, maxIdx) - badIdx);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        long long retVal = 0;

        /* Ref
         *  https://leetcode.com/problems/count-subarrays-with-fixed-bounds/solutions/2708099/java-c-python-sliding-window-with-explanation/
         *  https://leetcode.cn/problems/count-subarrays-with-fixed-bounds/solutions/1895734/fen-xi-ding-jie-zi-shu-zu-de-xing-zhi-yi-qusi/
         *  https://leetcode.cn/problems/count-subarrays-with-fixed-bounds/solutions/1895713/jian-ji-xie-fa-pythonjavacgo-by-endlessc-gag2/
         */
        int len = nums.size();
        long long badIdx = -1;
        long long minIdx = -1;
        long long maxIdx = -1;
        for (int i = 0; i < len; ++i) {
            if ((nums[i] < minK) || (nums[i] > maxK)) {
                badIdx = i;
            }

            if (nums[i] == minK) {
                minIdx = i;
            }

            if (nums[i] == maxK) {
                maxIdx = i;
            }

            /* avoid different type between a and b in max function
             *  Because std::max is a function template whose signature is, for example,
             *  template< class T >
             *  const T& max( const T& a, const T& b );
             */
            long long n1 = 0;
            long long n2 = min(minIdx, maxIdx) - badIdx;
            retVal += max(n1, n2);
        }

        return retVal;
    }
};
```

</details>
