# Sliding Window

## [3254. Find the Power of K-Size Subarrays I](https://leetcode.com/problems/find-the-power-of-k-size-subarrays-i/)  1266

- [Official](https://leetcode.com/problems/find-the-power-of-k-size-subarrays-i/editorial/)
- [Official](https://leetcode.cn/problems/find-the-power-of-k-size-subarrays-i/solutions/2973321/chang-du-wei-k-de-zi-shu-zu-de-neng-lian-vxim/)

<details><summary>Description</summary>

```text
You are given an array of integers nums of length n and a positive integer k.

The power of an array is defined as:
- Its maximum element if all of its elements are consecutive and sorted in ascending order.
- -1 otherwise.

You need to find the power of all subarrays of nums of size k.

Return an integer array results of size n - k + 1, where results[i] is the power of nums[i..(i + k - 1)].

Example 1:
Input: nums = [1,2,3,4,3,2,5], k = 3
Output: [3,4,-1,-1,-1]
Explanation:
There are 5 subarrays of nums of size 3:
[1, 2, 3] with the maximum element 3.
[2, 3, 4] with the maximum element 4.
[3, 4, 3] whose elements are not consecutive.
[4, 3, 2] whose elements are not sorted.
[3, 2, 5] whose elements are not consecutive.

Example 2:
Input: nums = [2,2,2,2,2], k = 4
Output: [-1,-1]

Example 3:
Input: nums = [3,2,3,2,3,2], k = 2
Output: [-1,3,-1,3,-1]

Constraints:
1 <= n == nums.length <= 500
1 <= nums[i] <= 10^5
1 <= k <= n
```

<details><summary>Hint</summary>

```text
1. Can we use a brute force solution with nested loops and HashSet?
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *resultsArray(int *nums, int numsSize, int k, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = numsSize - k + 1;
    pRetVal = (int *)malloc(((*returnSize) * sizeof(int)));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, -1, ((*returnSize) * sizeof(int)));

    int consecutiveCount = 0;
    for (int i = 0; i < numsSize; ++i) {
        if ((i != 0) && (nums[i - 1] + 1 == nums[i])) {
            consecutiveCount++;
        } else {
            consecutiveCount = 1;
        }

        if (consecutiveCount >= k) {
            pRetVal[i - k + 1] = nums[i];
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
    vector<int> resultsArray(vector<int>& nums, int k) {
        vector<int> retVal;

        if (k == 1) {
            retVal = nums;
            return retVal;
        }

        int numsSize = nums.size();
        retVal.resize(numsSize - k + 1, -1);
        int consecutiveCount = 1;
        for (int i = 0; i < numsSize - 1; ++i) {
            if (nums[i] + 1 == nums[i + 1]) {
                consecutiveCount++;
            } else {
                consecutiveCount = 1;
            }

            if (consecutiveCount >= k) {
                retVal[i - k + 2] = nums[i + 1];
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
    def resultsArray(self, nums: List[int], k: int) -> List[int]:
        retVal = []

        if k == 1:
            retVal = nums
            return retVal

        numsSize = len(nums)
        retVal = [-1] * (numsSize - k + 1)
        consecutiveCount = 1
        for i in range(numsSize - 1):
            if nums[i] + 1 == nums[i + 1]:
                consecutiveCount += 1
            else:
                consecutiveCount = 1

            if consecutiveCount >= k:
                retVal[i - k + 2] = nums[i + 1]

        return retVal
```

</details>

## [3306. Count of Substrings Containing Every Vowel and K Consonants II](https://leetcode.com/problems/count-of-substrings-containing-every-vowel-and-k-consonants-ii/)  2200

- [Official](https://leetcode.com/problems/count-of-substrings-containing-every-vowel-and-k-consonants-ii/editorial/)
- [Official](https://leetcode.cn/problems/count-of-substrings-containing-every-vowel-and-k-consonants-ii/solutions/3077749/yuan-yin-fu-yin-zi-fu-chuan-ji-shu-ii-by-rbrn/)

<details><summary>Description</summary>

```text
You are given a string word and a non-negative integer k.

Return the total number of substrings of word that contain every vowel ('a', 'e', 'i', 'o', and 'u') at least once
and exactly k consonants.

Example 1:
Input: word = "aeioqq", k = 1
Output: 0
Explanation:
There is no substring with every vowel.

Example 2:
Input: word = "aeiou", k = 0
Output: 1
Explanation:
The only substring with every vowel and zero consonants is word[0..4], which is "aeiou".

Example 3:
Input: word = "ieaouqqieaouqq", k = 1
Output: 3
Explanation:
The substrings with every vowel and one consonant are:
word[0..5], which is "ieaouq".
word[6..11], which is "qieaou".
word[7..12], which is "ieaouq".

Constraints:
5 <= word.length <= 2 * 10^5
word consists only of lowercase English letters.
0 <= k <= word.length - 5
```

<details><summary>Hint</summary>

```text
1. We can use sliding window and binary search.
2. For each index r, find the maximum l such that both conditions are satisfied using binary search.
```

</details>

</details>

<details><summary>C</summary>

```c
bool isVowel(char c) {
    bool retVal = (c == 'a') || (c == 'e') || (c == 'i') || (c == 'o') || (c == 'u');

    return retVal;
}
long long count(char* word, int k) {
    long long retVal = 0;

    int wordSize = strlen(word);

    int vowel[26];
    memset(vowel, 0, sizeof(vowel));
    int vowelSize = 0;
    int consonants = 0;
    for (int i = 0, j = 0; i < wordSize; i++) {
        while ((j < wordSize) && ((consonants < k) || (vowelSize < 5))) {
            if (isVowel(word[j]) == true) {
                vowel[word[j] - 'a']++;
                vowelSize += vowel[word[j] - 'a'] == 1;
            } else {
                consonants++;
            }
            j++;
        }

        if ((consonants >= k) && (vowelSize == 5)) {
            retVal += wordSize - j + 1;
        }

        if (isVowel(word[i]) == true) {
            vowel[word[i] - 'a']--;
            if (vowel[word[i] - 'a'] == 0) {
                vowelSize--;
            }
        } else {
            consonants--;
        }
    }

    return retVal;
}
long long countOfSubstrings(char* word, int k) {
    long long retVal = count(word, k) - count(word, k + 1);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    bool isVowel(char c) {
        bool retVal = (c == 'a') || (c == 'e') || (c == 'i') || (c == 'o') || (c == 'u');

        return retVal;
    }

   public:
    long long countOfSubstrings(string word, int k) {
        long long retVal = 0;

        int wordSize = word.size();

        vector<int> nextConsonant(wordSize);
        int nextConsonantIndex = wordSize;
        for (int i = wordSize - 1; i >= 0; i--) {
            nextConsonant[i] = nextConsonantIndex;
            if (isVowel(word[i]) == false) {
                nextConsonantIndex = i;
            }
        }

        unordered_map<char, int> vowelCount;
        int consonantCount = 0;
        int start = 0;
        int end = 0;
        while (end < wordSize) {
            char newLetter = word[end];
            if (isVowel(newLetter) == true) {
                vowelCount[newLetter]++;
            } else {
                consonantCount++;
            }

            while (consonantCount > k) {
                char startLetter = word[start];
                if (isVowel(startLetter) == true) {
                    vowelCount[startLetter]--;
                    if (vowelCount[startLetter] == 0) {
                        vowelCount.erase(startLetter);
                    }
                } else {
                    consonantCount--;
                }
                start++;
            }

            while ((start < wordSize) && (vowelCount.size() == 5) && (consonantCount == k)) {
                retVal += nextConsonant[end] - end;
                char startLetter = word[start];
                if (isVowel(startLetter) == true) {
                    vowelCount[startLetter]--;
                    if (vowelCount[startLetter] == 0) {
                        vowelCount.erase(startLetter);
                    }
                } else {
                    consonantCount--;
                }

                start++;
            }

            end++;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def isVowel(self, c: str) -> bool:
        retVal = (c == "a") or (c == "e") or (c == "i") or (c == "o") or (c == "u")

        return retVal

    def countOfSubstrings(self, word: str, k: int) -> int:
        retVal = 0

        wordSize = len(word)

        nextConsonant = [0] * wordSize  # Array to compute index of next consonant for all indices
        nextConsonantIndex = wordSize
        for i in range(wordSize - 1, -1, -1):
            nextConsonant[i] = nextConsonantIndex
            if self.isVowel(word[i]) == False:
                nextConsonantIndex = i

        vowelCount = {}  # Dictionary to keep counts of vowels
        consonantCount = 0  # Count of consonants
        start = 0
        end = 0
        while end < wordSize:
            newLetter = word[end]
            if self.isVowel(newLetter) == True:
                vowelCount[newLetter] = vowelCount.get(newLetter, 0) + 1
            else:
                consonantCount += 1

            # Shrink window if too many consonants are present
            while (consonantCount > k):
                startLetter = word[start]
                if self.isVowel(startLetter) == True:
                    vowelCount[startLetter] -= 1
                    if vowelCount[startLetter] == 0:
                        del vowelCount[startLetter]
                else:
                    consonantCount -= 1
                start += 1

            # Try to shrink if window is valid
            while (start < wordSize) and (len(vowelCount) == 5) and (consonantCount == k):
                retVal += nextConsonant[end] - end
                startLetter = word[start]
                if self.isVowel(startLetter) == True:
                    vowelCount[startLetter] -= 1
                    if vowelCount[startLetter] == 0:
                        del vowelCount[startLetter]
                else:
                    consonantCount -= 1
                start += 1

            end += 1

        return retVal
```

</details>
