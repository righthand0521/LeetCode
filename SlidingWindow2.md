# Sliding Window

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

## [1052. Grumpy Bookstore Owner](https://leetcode.com/problems/grumpy-bookstore-owner/)  1418

- [Official](https://leetcode.com/problems/grumpy-bookstore-owner/editorial/)
- [Official](https://leetcode.cn/problems/grumpy-bookstore-owner/solutions/615133/ai-sheng-qi-de-shu-dian-lao-ban-by-leetc-dloq/)

<details><summary>Description</summary>

```text
There is a bookstore owner that has a store open for n minutes. Every minute, some number of customers enter the store.
You are given an integer array customers of length n where customers[i] is the number of the customer
that enters the store at the start of the ith minute and all those customers leave after the end of that minute.

On some minutes, the bookstore owner is grumpy.
You are given a binary array grumpy
where grumpy[i] is 1 if the bookstore owner is grumpy during the ith minute, and is 0 otherwise.

When the bookstore owner is grumpy, the customers of that minute are not satisfied, otherwise, they are satisfied.

The bookstore owner knows a secret technique to keep themselves not grumpy for minutes consecutive minutes,
but can only use it once.

Return the maximum number of customers that can be satisfied throughout the day.

Example 1:
Input: customers = [1,0,1,2,1,1,7,5], grumpy = [0,1,0,1,0,1,0,1], minutes = 3
Output: 16
Explanation: The bookstore owner keeps themselves not grumpy for the last 3 minutes.
The maximum number of customers that can be satisfied = 1 + 1 + 1 + 1 + 7 + 5 = 16.

Example 2:
Input: customers = [1], grumpy = [0], minutes = 1
Output: 1

Constraints:
n == customers.length == grumpy.length
1 <= minutes <= n <= 2 * 10^4
0 <= customers[i] <= 1000
grumpy[i] is either 0 or 1.
```

<details><summary>Hint</summary>

```text
1. Say the store owner uses their power in minute 1 to X and we have some answer A.
   If they instead use their power from minute 2 to X+1,
   we only have to use data from minutes 1, 2, X and X+1 to update our answer A.
```

</details>

</details>

<details><summary>C</summary>

```c
int maxSatisfied(int* customers, int customersSize, int* grumpy, int grumpySize, int minutes) {
    int retVal = 0;

    int i;

    // Calculate initial number of unrealized customers in first 'minutes' window
    int unrealizedCustomers = 0;
    for (i = 0; i < minutes; ++i) {
        unrealizedCustomers += customers[i] * grumpy[i];
    }
    int maxUnrealizedCustomers = unrealizedCustomers;

    // Slide the 'minutes' window across the rest of the customers array
    for (i = minutes; i < customersSize; ++i) {
        // Add current minute's unsatisfied customers if the owner is grumpy
        // and remove the customers that are out of the current window
        unrealizedCustomers += customers[i] * grumpy[i];
        unrealizedCustomers -= customers[i - minutes] * grumpy[i - minutes];

        // Update the maximum unrealized customers
        maxUnrealizedCustomers = fmax(maxUnrealizedCustomers, unrealizedCustomers);
    }

    // Start with maximum possible satisfied customers due to secret technique
    int totalCustomers = maxUnrealizedCustomers;

    // Add the satisfied customers during non-grumpy minutes
    for (i = 0; i < customersSize; ++i) {
        totalCustomers += customers[i] * (1 - grumpy[i]);
    }

    // Return the maximum number of satisfied customers
    retVal = totalCustomers;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int retVal = 0;

        // Calculate initial number of unrealized customers in first 'minutes' window
        int unrealizedCustomers = 0;
        for (int i = 0; i < minutes; ++i) {
            unrealizedCustomers += customers[i] * grumpy[i];
        }
        int maxUnrealizedCustomers = unrealizedCustomers;

        // Slide the 'minutes' window across the rest of the customers array
        int customersSize = customers.size();
        for (int i = minutes; i < customersSize; ++i) {
            // Add current minute's unsatisfied customers if the owner is grumpy
            // and remove the customers that are out of the current window
            unrealizedCustomers += customers[i] * grumpy[i];
            unrealizedCustomers -= customers[i - minutes] * grumpy[i - minutes];

            // Update the maximum unrealized customers
            maxUnrealizedCustomers = max(maxUnrealizedCustomers, unrealizedCustomers);
        }

        // Start with maximum possible satisfied customers due to secret technique
        int totalCustomers = maxUnrealizedCustomers;

        // Add the satisfied customers during non-grumpy minutes
        for (int i = 0; i < customersSize; ++i) {
            totalCustomers += customers[i] * (1 - grumpy[i]);
        }

        // Return the maximum number of satisfied customers
        retVal = totalCustomers;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxSatisfied(self, customers: List[int], grumpy: List[int], minutes: int) -> int:
        retVal = 0

        # Calculate initial number of unrealized customers in first 'minutes' window
        unrealizedCustomers = 0
        for i in range(minutes):
            unrealizedCustomers += customers[i] * grumpy[i]
        maxUnrealizedCustomers = unrealizedCustomers

        # Slide the 'minutes' window across the rest of the customers array
        customersSize = len(customers)
        for i in range(minutes, customersSize):
            # Add current minute's unsatisfied customers if the owner is grumpy
            # and remove the customers that are out of the current window
            unrealizedCustomers += customers[i] * grumpy[i]
            unrealizedCustomers -= customers[i - minutes] * grumpy[i - minutes]

            # Update the maximum unrealized customers
            maxUnrealizedCustomers = max(maxUnrealizedCustomers, unrealizedCustomers)

        # Start with maximum possible satisfied customers due to secret technique
        totalCustomers = maxUnrealizedCustomers

        # Add the satisfied customers during non-grumpy minutes
        for i in range(customersSize):
            totalCustomers += customers[i] * (1 - grumpy[i])

        # Return the maximum number of satisfied customers
        retVal = totalCustomers

        return retVal
```

</details>

## [1208. Get Equal Substrings Within Budget](https://leetcode.com/problems/get-equal-substrings-within-budget/)  1496

- [Official](https://leetcode.com/problems/get-equal-substrings-within-budget/editorial/)
- [Official](https://leetcode.cn/problems/get-equal-substrings-within-budget/solutions/591367/jin-ke-neng-shi-zi-fu-chuan-xiang-deng-b-higz/)

<details><summary>Description</summary>

```text
You are given two strings s and t of the same length and an integer maxCost.

You want to change s to t. Changing the ith character of s to ith character of t costs |s[i] - t[i]|
(i.e., the absolute difference between the ASCII values of the characters).

Return the maximum length of a substring of s that can be changed to be the same
as the corresponding substring of t with a cost less than or equal to maxCost.
If there is no substring from s that can be changed to its corresponding substring from t, return 0.

Example 1:
Input: s = "abcd", t = "bcdf", maxCost = 3
Output: 3
Explanation: "abc" of s can change to "bcd".
That costs 3, so the maximum length is 3.

Example 2:
Input: s = "abcd", t = "cdef", maxCost = 3
Output: 1
Explanation: Each character in s costs 2 to change to character in t,  so the maximum length is 1.

Example 3:
Input: s = "abcd", t = "acde", maxCost = 0
Output: 1
Explanation: You cannot make any change, so the maximum length is 1.

Constraints:
1 <= s.length <= 10^5
t.length == s.length
0 <= maxCost <= 10^6
s and t consist of only lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Calculate the differences between a[i] and b[i].
2. Use a sliding window to track the longest valid substring.
```

</details>

</details>

<details><summary>C</summary>

```c
int equalSubstring(char* s, char* t, int maxCost) {
    int retVal = 0;

    int sSize = strlen(s);

    int cost = 0;
    int start = 0;
    int end = 0;
    for (end = 0; end < sSize; ++end) {
        cost += abs(s[end] - t[end]);
        while (cost > maxCost) {
            cost -= abs(s[start] - t[start]);
            start += 1;
        }
        retVal = fmax(retVal, end - start + 1);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int equalSubstring(string s, string t, int maxCost) {
        int retVal = 0;

        int sSize = s.size();

        int cost = 0;
        int start = 0;
        int end = 0;
        for (end = 0; end < sSize; ++end) {
            cost += abs(s[end] - t[end]);
            while (cost > maxCost) {
                cost -= abs(s[start] - t[start]);
                start += 1;
            }
            retVal = max(retVal, end - start + 1);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def equalSubstring(self, s: str, t: str, maxCost: int) -> int:
        retVal = 0

        sSize = len(s)

        cost = 0
        start = 0
        end = 0
        for end in range(sSize):
            cost += abs(ord(s[end]) - ord(t[end]))
            while cost > maxCost:
                cost -= abs(ord(s[start]) - ord(t[start]))
                start += 1
            retVal = max(retVal, end-start+1)

        return retVal
```

</details>

## [1248. Count Number of Nice Subarrays](https://leetcode.com/problems/count-number-of-nice-subarrays/)  1623

- [Official](https://leetcode.com/problems/count-number-of-nice-subarrays/editorial/)
- [Official](https://leetcode.cn/problems/count-number-of-nice-subarrays/solutions/211268/tong-ji-you-mei-zi-shu-zu-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given an array of integers nums and an integer k. A continuous subarray is called nice if there are k odd numbers on it.

Return the number of nice sub-arrays.

Example 1:
Input: nums = [1,1,2,1,1], k = 3
Output: 2
Explanation: The only sub-arrays with 3 odd numbers are [1,1,2,1] and [1,2,1,1].

Example 2:
Input: nums = [2,4,6], k = 1
Output: 0
Explanation: There are no odd numbers in the array.

Example 3:
Input: nums = [2,2,2,1,2,2,1,2,2,2], k = 2
Output: 16

Constraints:
1 <= nums.length <= 50000
1 <= nums[i] <= 10^5
1 <= k <= nums.length
```

<details><summary>Hint</summary>

```text
1. After replacing each even by zero and every odd by one can we use prefix sum to find answer ?
2. Can we use two pointers to count number of sub-arrays ?
3. Can we store indices of odd numbers and for each k indices count number of sub-arrays contains them ?
```

</details>

</details>

<details><summary>C</summary>

```c
int numberOfSubarrays(int* nums, int numsSize, int k) {
    int retVal = 0;

    int initialGap = 0;
    int qsize = 0;
    int start = 0;
    for (int end = 0; end < numsSize; ++end) {
        // If current element is odd, increment qsize by 1.
        if (nums[end] % 2 == 1) {
            qsize += 1;
        }

        if (qsize == k) {
            initialGap = 0;

            // Calculate the number of even elements in the beginning of subarray.
            while (qsize == k) {
                qsize -= nums[start] % 2;
                initialGap += 1;
                start += 1;
            }
        }

        retVal += initialGap;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int retVal = 0;

        int numsSize = nums.size();

        int initialGap = 0;
        int qsize = 0;
        int start = 0;
        for (int end = 0; end < numsSize; ++end) {
            // If current element is odd, increment qsize by 1.
            if (nums[end] % 2 == 1) {
                qsize += 1;
            }

            if (qsize == k) {
                initialGap = 0;

                // Calculate the number of even elements in the beginning of subarray.
                while (qsize == k) {
                    qsize -= nums[start] % 2;
                    initialGap += 1;
                    start += 1;
                }
            }

            retVal += initialGap;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def numberOfSubarrays(self, nums: List[int], k: int) -> int:
        retVal = 0

        numsSize = len(nums)

        initialGap = 0
        qsize = 0
        start = 0
        for end in range(numsSize):
            # If current element is odd, increment qsize by 1.
            if nums[end] % 2 == 1:
                qsize += 1

            if qsize == k:
                initialGap = 0

                while qsize == k:   # Calculate the number of even elements in the beginning of subarray.
                    qsize -= nums[start] % 2
                    initialGap += 1
                    start += 1

            retVal += initialGap

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

## [1358. Number of Substrings Containing All Three Characters](https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/)  1646

- [Official](https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/editorial/)
- [Official](https://leetcode.cn/problems/number-of-substrings-containing-all-three-characters/solutions/109170/bao-han-suo-you-san-chong-zi-fu-de-zi-zi-fu-chuan-/)

<details><summary>Description</summary>

```text
Given a string s consisting only of characters a, b and c.

Return the number of substrings containing at least one occurrence of all these characters a, b and c.

Example 1:
Input: s = "abcabc"
Output: 10
Explanation: The substrings containing at least one occurrence of
the characters a, b and c are "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again).

Example 2:
Input: s = "aaacb"
Output: 3
Explanation: The substrings containing at least one occurrence of
the characters a, b and c are "aaacb", "aacb" and "acb".

Example 3:
Input: s = "abc"
Output: 1

Constraints:
3 <= s.length <= 5 x 10^4
s only consists of a, b or c characters.
```

<details><summary>Hint</summary>

```text
1. For each position we simply need to find the first occurrence of a/b/c on or after this position.
2. So we can pre-compute three link-list of indices of each a, b, and c.
```

</details>

</details>

<details><summary>C</summary>

```c
int numberOfSubstrings(char* s) {
    int retVal = 0;

    int lastPos[3] = {-1, -1, -1};  // Track last position of a, b, c
    int sSize = strlen(s);
    for (int pos = 0; pos < sSize; pos++) {
        // Update last position of current character
        lastPos[s[pos] - 'a'] = pos;

        // Add count of valid substrings ending at current position
        // If any character is missing, min will be -1
        // Else min gives leftmost required character position
        retVal += 1 + fmin(lastPos[0], fmin(lastPos[1], lastPos[2]));
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int numberOfSubstrings(string s) {
        int retVal = 0;

        vector<int> lastPos = {-1, -1, -1};  // Track last position of a, b, c
        int sSize = s.length();
        for (int pos = 0; pos < sSize; pos++) {
            // Update last position of current character
            lastPos[s[pos] - 'a'] = pos;

            // Add count of valid substrings ending at current position
            // If any character is missing, min will be -1
            // Else min gives leftmost required character position
            retVal += 1 + min({lastPos[0], lastPos[1], lastPos[2]});
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def numberOfSubstrings(self, s: str) -> int:
        retVal = 0

        lastPos = [-1] * 3  # Track last position of a, b, c
        sSize = len(s)
        for pos in range(sSize):
            # Update last position of current character
            lastPos[ord(s[pos]) - ord("a")] = pos

            # Add count of valid substrings ending at current position
            # If any character is missing, min will be -1
            # Else min gives leftmost required character position
            retVal += 1 + min(lastPos)

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

## [1652. Defuse the Bomb](https://leetcode.com/problems/defuse-the-bomb/)  1416

- [Official](https://leetcode.com/problems/defuse-the-bomb/editorial/)
- [Official](https://leetcode.cn/problems/defuse-the-bomb/solutions/1843157/chai-zha-dan-by-leetcode-solution-01x3/)

<details><summary>Description</summary>

```text
You have a bomb to defuse, and your time is running out!
Your informer will provide you with a circular array code of length of n and a key k.

To decrypt the code, you must replace every number. All the numbers are replaced simultaneously.
- If k > 0, replace the ith number with the sum of the next k numbers.
- If k < 0, replace the ith number with the sum of the previous k numbers.
- If k == 0, replace the ith number with 0.

As code is circular, the next element of code[n-1] is code[0], and the previous element of code[0] is code[n-1].

Given the circular array code and an integer key k, return the decrypted code to defuse the bomb!

Example 1:
Input: code = [5,7,1,4], k = 3
Output: [12,10,16,13]
Explanation: Each number is replaced by the sum of the next 3 numbers.
The decrypted code is [7+1+4, 1+4+5, 4+5+7, 5+7+1]. Notice that the numbers wrap around.

Example 2:
Input: code = [1,2,3,4], k = 0
Output: [0,0,0,0]
Explanation: When k is zero, the numbers are replaced by 0.

Example 3:
Input: code = [2,4,9,3], k = -2
Output: [12,5,6,13]
Explanation: The decrypted code is [3+9, 2+3, 4+2, 9+4].
Notice that the numbers wrap around again. If k is negative, the sum is of the previous numbers.

Constraints:
n == code.length
1 <= n <= 100
1 <= code[i] <= 100
-(n - 1) <= k <= n - 1
```

<details><summary>Hint</summary>

```text
1. As the array is circular, use modulo to find the correct index.
2. The constraints are low enough for a brute-force solution.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *decrypt(int *code, int codeSize, int k, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int *)calloc(codeSize, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }
    (*returnSize) = codeSize;

    if (k == 0) {
        return pRetVal;
    }

    int start = 1;
    int end = k;
    if (k < 0) {  // If k < 0, the starting point will be end of the array.
        start = codeSize - abs(k);
        end = codeSize - 1;
    }

    int sum = 0;
    for (int i = start; i <= end; i++) {
        sum += code[i];
    }

    // Scan through the code array as i moving to the right, update the window sum.
    for (int i = 0; i < codeSize; i++) {
        pRetVal[i] = sum;
        sum -= code[start % codeSize];
        sum += code[(end + 1) % codeSize];
        start++;
        end++;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> decrypt(vector<int>& code, int k) {
        vector<int> retVal;

        int codeSize = code.size();

        retVal.assign(codeSize, 0);
        if (k == 0) {
            return retVal;
        }

        int start = 1;
        int end = k;
        if (k < 0) {  // If k < 0, the starting point will be end of the array.
            start = codeSize - abs(k);
            end = codeSize - 1;
        }

        int sum = 0;
        for (int i = start; i <= end; i++) {
            sum += code[i];
        }

        // Scan through the code array as i moving to the right, update the window sum.
        for (int i = 0; i < codeSize; i++) {
            retVal[i] = sum;
            sum -= code[start % codeSize];
            sum += code[(end + 1) % codeSize];
            start++;
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
    def decrypt(self, code: List[int], k: int) -> List[int]:
        retVal = []

        codeSize = len(code)
        retVal = [0] * codeSize
        if k == 0:
            return retVal

        start = 1
        end = k
        if k < 0:  # If k < 0, the starting point will be end of the array.
            start = codeSize - abs(k)
            end = codeSize - 1

        sum = 0
        for i in range(start, end + 1):
            sum += code[i]

        # Scan through the code array as i moving to the right, update the window sum.
        for i in range(codeSize):
            retVal[i] = sum
            sum -= code[start % codeSize]
            sum += code[(end + 1) % codeSize]
            start += 1
            end += 1

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
