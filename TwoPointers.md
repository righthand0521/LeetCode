# Two Pointers

## [11. Container With Most Water](https://leetcode.com/problems/container-with-most-water/)

- [Official](https://leetcode.cn/problems/container-with-most-water/solutions/207215/sheng-zui-duo-shui-de-rong-qi-by-leetcode-solution/)

<details><summary>Description</summary>

```text
You are given an integer array height of length n.
There are n vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).

Find two lines that together with the x-axis form a container, such that the container contains the most water.

Return the maximum amount of water a container can store.

Notice that you may not slant the container.

Example 1:
Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7].
In this case, the max area of water (blue section) the container can contain is 49.

Example 2:
Input: height = [1,1]
Output: 1

Constraints:
n == height.length
2 <= n <= 10^5
0 <= height[i] <= 10^4
```

<details><summary>Hint</summary>

```text
1. If you simulate the problem, it will be O(n^2) which is not efficient.
2. Try to use two-pointers. Set one pointer to the left and one to the right of the array.
   Always move the pointer that points to the lower line.
3. How can you calculate the amount of water at each step?
```

</details>

</details>

<details><summary>C</summary>

```c
int maxArea(int* height, int heightSize) {
    int retVal = 0;

    int leftValue, rightValue, minValue;
    int left = 0;
    int right = heightSize - 1;
    while (left < right) {
        leftValue = height[left];
        rightValue = height[right];
        minValue = fmin(leftValue, rightValue);
        retVal = fmax(retVal, minValue * (right - left));

        if (leftValue > rightValue) {
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
    int maxArea(vector<int>& height) {
        int retVal = 0;

        int heightSize = height.size();

        int left = 0;
        int right = heightSize - 1;
        while (left < right) {
            int leftValue = height[left];
            int rightValue = height[right];
            int minValue = min(leftValue, rightValue);
            retVal = max(retVal, minValue * (right - left));

            if (leftValue > rightValue) {
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
    def maxArea(self, height: List[int]) -> int:
        retVal = 0

        heightSize = len(height)

        left = 0
        right = heightSize - 1
        while left < right:
            leftValue = height[left]
            rightValue = height[right]
            minValue = min(leftValue, rightValue)
            retVal = max(retVal, minValue * (right - left))

            if leftValue > rightValue:
                right -= 1
            else:
                left += 1

        return retVal
```

</details>

## [15. 3Sum](https://leetcode.com/problems/3sum/)

- [Official](https://leetcode.cn/problems/3sum/solutions/284681/san-shu-zhi-he-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given an integer array nums,
return all the triplets [nums[i], nums[j], nums[k]]
such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.

Example 1:
Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation:
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are [-1,0,1] and [-1,-1,2].
Notice that the order of the output and the order of the triplets does not matter.

Example 2:
Input: nums = [0,1,1]
Output: []
Explanation: The only possible triplet does not sum up to 0.

Example 3:
Input: nums = [0,0,0]
Output: [[0,0,0]]
Explanation: The only possible triplet sums up to 0.

Constraints:

3 <= nums.length <= 3000
-10^5 <= nums[i] <= 10^5
```

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;

    if (numsSize < 3) {
        return pRetVal;
    }

#define MAX_ROW (numsSize * numsSize)
#define MAX_COLUMN (3)
    (*returnColumnSizes) = (int*)malloc(MAX_ROW * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, (MAX_ROW * sizeof(int)));
    pRetVal = (int**)malloc(MAX_ROW * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int first, second, third, target;
    for (first = 0; first < numsSize - 2; ++first) {
        if (nums[first] > 0) {
            break;
        }

        // Notice that the order of the output and the order of the triplets does not matter.
        if ((first > 0) && (nums[first - 1] == nums[first])) {
            continue;
        }

        second = first + 1;
        third = numsSize - 1;
        while (second < third) {
            target = nums[first] + nums[second] + nums[third];
            if (target == 0) {
                // Notice that the order of the output and the order of the triplets does not matter.
                if ((second > first + 1) && (nums[second - 1] == nums[second])) {
                    second += 1;
                    continue;
                }

                (*returnColumnSizes)[(*returnSize)] = MAX_COLUMN;
                pRetVal[(*returnSize)] = (int*)malloc(((*returnColumnSizes)[(*returnSize)]) * sizeof(int));
                if (pRetVal[(*returnSize)] == NULL) {
                    perror("malloc");
                    return pRetVal;
                }
                pRetVal[(*returnSize)][0] = nums[first];
                pRetVal[(*returnSize)][1] = nums[second];
                pRetVal[(*returnSize)][2] = nums[third];
                (*returnSize) += 1;

                second += 1;
                third -= 1;
            } else if (target < 0) {
                second += 1;
            } else if (target > 0) {
                third -= 1;
            }
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
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> retVal;

        int numsSize = nums.size();
        if (numsSize < 3) {
            return retVal;
        }

        sort(nums.begin(), nums.end());
        for (int first = 0; first < numsSize - 2; ++first) {
            if (nums[first] > 0) {
                break;
            }

            // Notice that the order of the output and the order of the triplets does not matter.
            if ((first > 0) && (nums[first - 1] == nums[first])) {
                continue;
            }

            int second = first + 1;
            int third = numsSize - 1;
            while (second < third) {
                int target = nums[first] + nums[second] + nums[third];
                if (target == 0) {
                    // Notice that the order of the output and the order of the triplets does not matter.
                    if ((second > first + 1) && (nums[second - 1] == nums[second])) {
                        second += 1;
                        continue;
                    }
                    vector<int> tmp = {nums[first], nums[second], nums[third]};
                    retVal.emplace_back(tmp);
                    second += 1;
                    third -= 1;
                } else if (target < 0) {
                    second += 1;
                } else if (target > 0) {
                    third -= 1;
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
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        retVal = []

        numsSize = len(nums)
        if numsSize < 3:
            return retVal

        nums.sort()
        for first in range(numsSize-2):
            if nums[first] > 0:
                break

            # Notice that the order of the output and the order of the triplets does not matter.
            if (first > 0) and (nums[first-1] == nums[first]):
                continue

            second = first + 1
            third = numsSize - 1
            while second < third:
                target = nums[first] + nums[second] + nums[third]
                if target == 0:
                    # Notice that the order of the output and the order of the triplets does not matter.
                    if (second > first + 1) and (nums[second - 1] == nums[second]):
                        second += 1
                        continue
                    retVal.append([nums[first], nums[second], nums[third]])
                    second += 1
                    third -= 1
                elif target < 0:
                    second += 1
                elif target > 0:
                    third -= 1

        return retVal
```

</details>

## [16. 3Sum Closest](https://leetcode.com/problems/3sum-closest/)

- [Official](https://leetcode.cn/problems/3sum-closest/solutions/301382/zui-jie-jin-de-san-shu-zhi-he-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given an integer array nums of length n and an integer target,
find three integers in nums such that the sum is closest to target.

Return the sum of the three integers.

You may assume that each input would have exactly one solution.

Example 1:
Input: nums = [-1,2,1,-4], target = 1
Output: 2
Explanation: The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).

Example 2:
Input: nums = [0,0,0], target = 1
Output: 0
Explanation: The sum that is closest to the target is 0. (0 + 0 + 0 = 0).

Constraints:
3 <= nums.length <= 500
-1000 <= nums[i] <= 1000
-10^4 <= target <= 10^4
```

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int threeSumClosest(int* nums, int numsSize, int target) {
    int retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int closest = INT_MAX;
    int first, second, third, sum, diff;
    for (first = 0; first < numsSize - 2; ++first) {
        second = first + 1;
        third = numsSize - 1;
        while (second < third) {
            sum = nums[first] + nums[second] + nums[third];
            diff = abs(target - sum);
            if (closest > diff) {
                closest = diff;
                retVal = sum;
            }

            if (sum == target) {
                return retVal;
            } else if (sum < target) {
                second += 1;
            } else if (sum > target) {
                third -= 1;
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
    int threeSumClosest(vector<int>& nums, int target) {
        int retVal = 0;

        sort(nums.begin(), nums.end());

        int closest = numeric_limits<int>::max();
        int numsSize = nums.size();
        for (int first = 0; first < numsSize - 2; ++first) {
            int second = first + 1;
            int third = numsSize - 1;
            while (second < third) {
                int sum = nums[first] + nums[second] + nums[third];
                int diff = abs(target - sum);
                if (closest > diff) {
                    closest = diff;
                    retVal = sum;
                }

                if (sum == target) {
                    return retVal;
                } else if (sum < target) {
                    second += 1;
                } else if (sum > target) {
                    third -= 1;
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
    def threeSumClosest(self, nums: List[int], target: int) -> int:
        retVal = 0

        nums.sort()

        closest = float('inf')
        numsSize = len(nums)
        for first in range(numsSize-2):
            second = first + 1
            third = numsSize - 1
            while second < third:
                sum = nums[first] + nums[second] + nums[third]
                diff = abs(target-sum)
                if closest > diff:
                    closest = diff
                    retVal = sum

                if sum == target:
                    return retVal
                elif sum < target:
                    second += 1
                elif sum > target:
                    third -= 1

        return retVal
```

</details>

## [18. 4Sum](https://leetcode.com/problems/4sum/)

- [Official](https://leetcode.com/problems/4sum/editorial/)
- [Official](https://leetcode.cn/problems/4sum/solutions/436368/si-shu-zhi-he-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given an array nums of n integers,
return an array of all the unique quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:
- 0 <= a, b, c, d < n
- a, b, c, and d are distinct.
- nums[a] + nums[b] + nums[c] + nums[d] == target
You may return the answer in any order.

Example 1:
Input: nums = [1,0,-1,0,-2,2], target = 0
Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]

Example 2:
Input: nums = [2,2,2,2,2], target = 8
Output: [[2,2,2,2]]

Constraints:
1 <= nums.length <= 200
-10^9 <= nums[i] <= 10^9
-10^9 <= target <= 10^9
```

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** fourSum(int* nums, int numsSize, int target, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;

    if (numsSize < 4) {
        return pRetVal;
    }

#define MAX_ROW (numsSize * numsSize)
#define MAX_COLUMN (4)
    (*returnColumnSizes) = (int*)malloc(MAX_ROW * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, (MAX_ROW * sizeof(int)));
    pRetVal = (int**)malloc(MAX_ROW * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }

    qsort(nums, numsSize, sizeof(int), compareInteger);

    long compare;
    int a, b, c, d;
    for (a = 0; a < numsSize - 3; ++a) {
        // Notice that the order of the output and the order of the triplets does not matter.
        if ((a > 0) && (nums[a - 1] == nums[a])) {
            continue;
        }

        for (b = a + 1; b < numsSize - 2; ++b) {
            // Notice that the order of the output and the order of the triplets does not matter.
            if ((b > a + 1) && (nums[b - 1] == nums[b])) {
                continue;
            }

            c = b + 1;
            d = numsSize - 1;
            while (c < d) {
                compare = (long)(nums[a]) + (long)(nums[b]) + (long)(nums[c]) + (long)(nums[d]);
                if (compare < target) {
                    c += 1;
                } else if (compare > target) {
                    d -= 1;
                } else {
                    // Notice that the order of the output and the order of the triplets does not matter.
                    if ((c > b + 1) && (nums[c - 1] == nums[c])) {
                        c += 1;
                        continue;
                    }

                    (*returnColumnSizes)[(*returnSize)] = MAX_COLUMN;
                    pRetVal[(*returnSize)] = (int*)malloc(((*returnColumnSizes)[(*returnSize)]) * sizeof(int));
                    if (pRetVal[(*returnSize)] == NULL) {
                        perror("malloc");
                        return pRetVal;
                    }
                    pRetVal[(*returnSize)][0] = nums[a];
                    pRetVal[(*returnSize)][1] = nums[b];
                    pRetVal[(*returnSize)][2] = nums[c];
                    pRetVal[(*returnSize)][3] = nums[d];
                    (*returnSize) += 1;

                    c += 1;
                    d -= 1;
                }
            }
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
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> retVal;

        int numsSize = nums.size();
        if (numsSize < 4) {
            return retVal;
        }

        sort(nums.begin(), nums.end());
        for (int a = 0; a < numsSize - 3; ++a) {
            // Notice that the order of the output and the order of the triplets does not matter.
            if ((a > 0) && (nums[a - 1] == nums[a])) {
                continue;
            }

            for (int b = a + 1; b < numsSize - 2; ++b) {
                // Notice that the order of the output and the order of the triplets does not matter.
                if ((b > a + 1) && (nums[b - 1] == nums[b])) {
                    continue;
                }

                int c = b + 1;
                int d = numsSize - 1;
                while (c < d) {
                    long compare = (long)(nums[a]) + (long)(nums[b]) + (long)(nums[c]) + (long)(nums[d]);
                    if (compare < target) {
                        c += 1;
                    } else if (compare > target) {
                        d -= 1;
                    } else {
                        // Notice that the order of the output and the order of the triplets does not matter.
                        if ((c > b + 1) && (nums[c - 1] == nums[c])) {
                            c += 1;
                            continue;
                        }

                        vector<int> tmp = {nums[a], nums[b], nums[c], nums[d]};
                        retVal.emplace_back(tmp);
                        c += 1;
                        d -= 1;
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
    def fourSum(self, nums: List[int], target: int) -> List[List[int]]:
        retVal = []

        numsSize = len(nums)
        if numsSize < 4:
            return retVal

        nums.sort()
        numsSize = len(nums)
        for a in range(numsSize-3):
            # Notice that the order of the output and the order of the triplets does not matter.
            if (a > 0) and (nums[a-1] == nums[a]):
                continue

            for b in range(a + 1, numsSize - 2):
                # Notice that the order of the output and the order of the triplets does not matter.
                if (b > a + 1) and (nums[b-1] == nums[b]):
                    continue

                c = b + 1
                d = numsSize - 1
                while c < d:
                    if nums[a] + nums[b] + nums[c] + nums[d] < target:
                        c += 1
                    elif nums[a] + nums[b] + nums[c] + nums[d] > target:
                        d -= 1
                    else:
                        # Notice that the order of the output and the order of the triplets does not matter.
                        if (c > b + 1) and (nums[c - 1] == nums[c]):
                            c += 1
                            continue

                        retVal.append([nums[a], nums[b], nums[c], nums[d]])
                        c += 1
                        d -= 1

        return retVal
```

</details>

## [125. Valid Palindrome](https://leetcode.com/problems/valid-palindrome/)

- [Official](https://leetcode.cn/problems/valid-palindrome/solutions/292148/yan-zheng-hui-wen-chuan-by-leetcode-solution/)

<details><summary>Description</summary>

```text
A phrase is a palindrome if, after converting all uppercase letters into lowercase letters
and removing all non-alphanumeric characters, it reads the same forward and backward.
Alphanumeric characters include letters and numbers.

Given a string s, return true if it is a palindrome, or false otherwise.

Example 1:
Input: s = "A man, a plan, a canal: Panama"
Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.

Example 2:
Input: s = "race a car"
Output: false
Explanation: "raceacar" is not a palindrome.

Example 3:
Input: s = " "
Output: true
Explanation: s is an empty string "" after removing non-alphanumeric characters.
Since an empty string reads the same forward and backward, it is a palindrome.

Constraints:
1 <= s.length <= 2 * 10^5
s consists only of printable ASCII characters.
```

</details>

<details><summary>C</summary>

```c
bool isPalindrome(char *s) {
    int retVal = true;

    int len = strlen(s);
    if (len == 0) {
        return retVal;
    }

    char *pHead = s;
    char *pTail = s + len - 1;
    while (pHead < pTail) {
        // A phrase is a palindrome if, after converting all uppercase letters into lowercase letters
        // and removing all non - alphanumeric characters, it reads the same forward and backward.
        // Alphanumeric characters include letters and numbers.
        if (isalnum(*pHead) == 0) {
            pHead++;
            continue;
        }
        if (isalnum(*pTail) == 0) {
            pTail--;
            continue;
        }

        if (isupper(*pHead)) {
            *pHead += 32;
        }
        if (isupper(*pTail)) {
            *pTail += 32;
        }
        if ((*pHead - *pTail) != 0) {
            retVal = false;
            break;
        }
        pHead++;
        pTail--;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    bool isPalindrome(string s) {
        bool retVal = true;

        // A phrase is a palindrome if, after converting all uppercase letters into lowercase letters
        // and removing all non - alphanumeric characters, it reads the same forward and backward.
        // Alphanumeric characters include letters and numbers.
        string palindrome;
        for (char ch : s) {
            if (isalnum(ch)) {
                palindrome += tolower(ch);
            }
        }

        int head = 0;
        int tail = palindrome.size() - 1;
        while (head < tail) {
            if (palindrome[head] != palindrome[tail]) {
                retVal = false;
                break;
            }
            ++head;
            --tail;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def isPalindrome(self, s: str) -> bool:
        retVal = True

        # A phrase is a palindrome if, after converting all uppercase letters into lowercase letters
        # and removing all non-alphanumeric characters, it reads the same forward and backward.
        # Alphanumeric characters include letters and numbers.
        palindrome = "".join(ch.lower() for ch in s if ch.isalnum())

        head = 0
        tail = len(palindrome) - 1
        while head < tail:
            if palindrome[head] != palindrome[tail]:
                retVal = False
                break
            head += 1
            tail -= 1

        return retVal
```

</details>

## [151. Reverse Words in a String](https://leetcode.com/problems/reverse-words-in-a-string/)

- [Official](https://leetcode.cn/problems/reverse-words-in-a-string/solutions/194450/fan-zhuan-zi-fu-chuan-li-de-dan-ci-by-leetcode-sol/)

<details><summary>Description</summary>

```text
Given an input string s, reverse the order of the words.

A word is defined as a sequence of non-space characters. The words in s will be separated by at least one space.

Return a string of the words in reverse order concatenated by a single space.

Note that s may contain leading or trailing spaces or multiple spaces between two words.
The returned string should only have a single space separating the words. Do not include any extra spaces.

Example 1:
Input: s = "the sky is blue"
Output: "blue is sky the"

Example 2:
Input: s = "  hello world  "
Output: "world hello"
Explanation: Your reversed string should not contain leading or trailing spaces.

Example 3:
Input: s = "a good   example"
Output: "example good a"
Explanation: You need to reduce multiple spaces between two words to a single space in the reversed string.

Constraints:
1 <= s.length <= 10^4
s contains English letters (upper-case and lower-case), digits, and spaces ' '.
There is at least one word in s.

Follow-up: If the string data type is mutable in your language, can you solve it in-place with O(1) extra space?
```

</details>

<details><summary>C</summary>

```c
char* reverseWords(char* s) {
    char* pRetVal = NULL;

    // malloc return string
    int len = strlen(s) + 1;
    pRetVal = (char*)malloc(len*sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, len*sizeof(char));

    // record return string length
    int idx = 0;
    // record head and tail index of word in the input string
    int head = (len - 1) - 1;
    int tail = (len - 1) - 1;
    for (head=((len-1)-1); head>=0; --head) {
        if (s[head] != ' ') {
            continue;
        }

        if (head != tail) {
            // add separated space for reverse words
            if (idx != 0) {
                idx += snprintf(pRetVal+idx, len-idx, "%s", " ");
            }
            idx += snprintf(pRetVal+idx, len-idx, "%s", s+head+1);
        }
        tail = head - 1;
        s[head] = 0;
    }
    // add separated space for reverse words
    if ((idx!=0) && (strlen(s+head+1)>0)) {
        idx += snprintf(pRetVal+idx, len-idx, "%s", " ");
    }
    idx += snprintf(pRetVal+idx, len-idx, "%s", s+head+1);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string reverseWords(string s) {
        string retVal = "";

        int sSize = s.size();
        string splitStr = "";
        for (int i = 0; i <= sSize; ++i) {
            if ((s[i] != ' ') && (s[i] != '\0')) {
                splitStr.push_back(s[i]);
                continue;
            }

            if (splitStr.empty() == true) {
                continue;
            }
            retVal = splitStr + " " + retVal;

            splitStr = "";
        }
        retVal.pop_back();

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def reverseWords(self, s: str) -> str:
        retVal = ""

        for pStr in s.split():
            retVal = pStr + " " + retVal
        retVal = retVal.rstrip()

        return retVal
```

</details>

## [165. Compare Version Numbers](https://leetcode.com/problems/compare-version-numbers/)

- [Official](https://leetcode.cn/problems/compare-version-numbers/solutions/970416/bi-jiao-ban-ben-hao-by-leetcode-solution-k6wi/)

<details><summary>Description</summary>

```text
Given two version numbers, version1 and version2, compare them.

Version numbers consist of one or more revisions joined by a dot '.'.
Each revision consists of digits and may contain leading zeros.
Every revision contains at least one character.
Revisions are 0-indexed from left to right, with the leftmost revision being revision 0,
the next revision being revision 1, and so on. For example 2.5.33 and 0.1 are valid version numbers.

To compare version numbers, compare their revisions in left-to-right order.
Revisions are compared using their integer value ignoring any leading zeros.
This means that revisions 1 and 001 are considered equal.
If a version number does not specify a revision at an index, then treat the revision as 0.
For example, version 1.0 is less than version 1.1 because their revision 0s are the same,
but their revision 1s are 0 and 1 respectively, and 0 < 1.

Return the following:
- If version1 < version2, return -1.
- If version1 > version2, return 1.
- Otherwise, return 0.

Example 1:
Input: version1 = "1.01", version2 = "1.001"
Output: 0
Explanation: Ignoring leading zeroes, both "01" and "001" represent the same integer "1".

Example 2:
Input: version1 = "1.0", version2 = "1.0.0"
Output: 0
Explanation: version1 does not specify revision 2, which means it is treated as "0".

Example 3:
Input: version1 = "0.1", version2 = "1.1"
Output: -1
Explanation: version1's revision 0 is "0", while version2's revision 0 is "1". 0 < 1, so version1 < version2.

Constraints:
1 <= version1.length, version2.length <= 500
version1 and version2 only contain digits and '.'.
version1 and version2 are valid version numbers.
All the given revisions in version1 and version2 can be stored in a 32-bit integer.
```

</details>

<details><summary>C</summary>

```c
/* Return the following:
 *  If version1 < version2, return -1.
 *  If version1 > version2, return 1.
 *  Otherwise, return 0.
 */
#define COMPARE_SMALL (-1)
#define COMPARE_LARGE (1)
#define COMPARE_EQUAL (0)
int compareVersion(char* version1, char* version2) {
    int retVal = COMPARE_EQUAL;

    int version1Size = strlen(version1);
    int version2Size = strlen(version2);

    int sum1, sum2 = 0;
    int idx1 = 0;
    int idx2 = 0;
    while ((idx1 < version1Size) || (idx2 < version2Size)) {
        sum1 = 0;
        while ((idx1 < version1Size) && (version1[idx1] != '.')) {
            sum1 = 10 * sum1 + (version1[idx1] - '0');
            idx1++;
        }
        idx1++;

        sum2 = 0;
        while ((idx2 < version2Size) && (version2[idx2] != '.')) {
            sum2 = 10 * sum2 + (version2[idx2] - '0');
            idx2++;
        }
        idx2++;

        if (sum1 > sum2) {
            retVal = COMPARE_LARGE;
            break;
        } else if (sum1 < sum2) {
            retVal = COMPARE_SMALL;
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
    /* Return the following:
     *  If version1 < version2, return -1.
     *  If version1 > version2, return 1.
     *  Otherwise, return 0.
     */
    int small = -1;
    int large = 1;
    int equal = 0;

   public:
    int compareVersion(string version1, string version2) {
        int retVal = equal;

        int version1Size = version1.size();
        int version2Size = version2.size();

        int idx1 = 0;
        int idx2 = 0;
        while ((idx1 < version1Size) || (idx2 < version2Size)) {
            int sum1 = 0;
            while ((idx1 < version1Size) && (version1[idx1] != '.')) {
                sum1 = 10 * sum1 + (version1[idx1] - '0');
                idx1++;
            }
            idx1++;

            int sum2 = 0;
            while ((idx2 < version2Size) && (version2[idx2] != '.')) {
                sum2 = 10 * sum2 + (version2[idx2] - '0');
                idx2++;
            }
            idx2++;

            if (sum1 > sum2) {
                retVal = large;
                break;
            } else if (sum1 < sum2) {
                retVal = small;
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
    def __init__(self) -> None:
        self.small = -1
        self.large = 1
        self.equal = 0

    def compareVersion(self, version1: str, version2: str) -> int:
        retVal = self.equal

        version1Size = len(version1)
        version2Size = len(version2)

        idx1 = 0
        idx2 = 0
        while (idx1 < version1Size) or (idx2 < version2Size):
            sum1 = 0
            while (idx1 < version1Size) and (version1[idx1] != '.'):
                sum1 = sum1 * 10 + int(version1[idx1])
                idx1 += 1
            idx1 += 1

            sum2 = 0
            while (idx2 < version2Size) and (version2[idx2] != '.'):
                sum2 = sum2 * 10 + int(version2[idx2])
                idx2 += 1
            idx2 += 1

            if sum1 > sum2:
                retVal = self.large
                break
            elif sum1 < sum2:
                retVal = self.small
                break

        return retVal
```

</details>

## [167. Two Sum II - Input Array Is Sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/)

- [Official](https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/solutions/337156/liang-shu-zhi-he-ii-shu-ru-you-xu-shu-zu-by-leet-2)

<details><summary>Description</summary>

```text
Given a 1-indexed array of integers numbers that is already sorted in non-decreasing order,
find two numbers such that they add up to a specific target number.
Let these two numbers be numbers[index1] and numbers[index2] where 1 <= index1 < index2 <= numbers.length.

Return the indices of the two numbers, index1 and index2, added by one as an integer array [index1, index2] of length 2.

The tests are generated such that there is exactly one solution. You may not use the same element twice.

Your solution must use only constant extra space.

Example 1:
Input: numbers = [2,7,11,15], target = 9
Output: [1,2]
Explanation: The sum of 2 and 7 is 9. Therefore, index1 = 1, index2 = 2. We return [1, 2].

Example 2:
Input: numbers = [2,3,4], target = 6
Output: [1,3]
Explanation: The sum of 2 and 4 is 6. Therefore index1 = 1, index2 = 3. We return [1, 3].

Example 3:
Input: numbers = [-1,0], target = -1
Output: [1,2]
Explanation: The sum of -1 and 0 is -1. Therefore index1 = 1, index2 = 2. We return [1, 2].

Constraints:
2 <= numbers.length <= 3 * 10^4
-1000 <= numbers[i] <= 1000
numbers is sorted in non-decreasing order.
-1000 <= target <= 1000
The tests are generated such that there is exactly one solution.
```

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* numbers, int numbersSize, int target, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 2;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));

    int left = 0;
    int right = numbersSize - 1;
    int sum = numbers[left] + numbers[right];
    while (sum != target) {
        if (sum > target) {
            --right;
        } else if (sum < target) {
            ++left;
        }
        sum = numbers[left] + numbers[right];
    }
    pRetVal[0] = left + 1;
    pRetVal[1] = right + 1;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> retVal;

        int left = 0;
        int right = numbers.size() - 1;
        int sum = numbers[left] + numbers[right];
        while (sum != target) {
            if (sum > target) {
                --right;
            } else if (sum < target) {
                ++left;
            }
            sum = numbers[left] + numbers[right];
        }
        retVal.emplace_back(left + 1);
        retVal.emplace_back(right + 1);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def twoSum(self, numbers: List[int], target: int) -> List[int]:
        retVal = []

        left = 0
        right = len(numbers) - 1
        sum = numbers[left] + numbers[right]
        while sum != target:
            if sum > target:
                right -= 1
            elif sum < target:
                left += 1
            sum = numbers[left] + numbers[right]
        retVal = [left+1, right+1]

        return retVal
```

</details>

## [283. Move Zeroes](https://leetcode.com/problems/move-zeroes/)

- [Official](https://leetcode.com/problems/move-zeroes/editorial/)
- [Official](https://leetcode.cn/problems/move-zeroes/solutions/489622/yi-dong-ling-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given an integer array nums, move all 0's to the end of it while maintaining the relative order of the non-zero elements.

Note that you must do this in-place without making a copy of the array.

Example 1:
Input: nums = [0,1,0,3,12]
Output: [1,3,12,0,0]

Example 2:
Input: nums = [0]
Output: [0]

Constraints:
1 <= nums.length <= 10^4
-2^31 <= nums[i] <= 2^31 - 1

Follow up: Could you minimize the total number of operations done?
```

<details><summary>Hint</summary>

```text
1. In-place means we should not be allocating any space for extra array.
   But we are allowed to modify the existing array.
   However, as a first step, try coming up with a solution that makes use of additional space.
   For this problem as well,
   first apply the idea discussed using an additional array and the in-place solution will pop up eventually.
2. A two-pointer approach could be helpful here.
   The idea would be to have one pointer for iterating the array and another pointer
   that just works on the non-zero elements of the array.
```

</details>

</details>

<details><summary>C</summary>

```c
void moveZeroes(int* nums, int numsSize) {
    int lastNonZeroFoundAt = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] != 0) {
            nums[lastNonZeroFoundAt++] = nums[i];
        }
    }
    for (i = lastNonZeroFoundAt; i < numsSize; ++i) {
        nums[i] = 0;
    }
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    void moveZeroes(vector<int>& nums) {
        int numsSize = nums.size();
        int lastNonZeroFoundAt = 0;
        for (int i = 0; i < numsSize; ++i) {
            if (nums[i] != 0) {
                nums[lastNonZeroFoundAt++] = nums[i];
            }
        }
        for (int i = lastNonZeroFoundAt; i < numsSize; ++i) {
            nums[i] = 0;
        }
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def moveZeroes(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        numsSize = len(nums)
        lastNonZeroFoundAt = 0
        for i in range(numsSize):
            if nums[i] != 0:
                nums[lastNonZeroFoundAt] = nums[i]
                lastNonZeroFoundAt += 1
        for i in range(lastNonZeroFoundAt, numsSize):
            nums[i] = 0
```

</details>

## [344. Reverse String](https://leetcode.com/problems/reverse-string/)

- [Official](https://leetcode.cn/problems/reverse-string/solutions/439034/fan-zhuan-zi-fu-chuan-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Write a function that reverses a string. The input string is given as an array of characters s.

You must do this by modifying the input array in-place with O(1) extra memory.

Example 1:
Input: s = ["h","e","l","l","o"]
Output: ["o","l","l","e","h"]

Example 2:
Input: s = ["H","a","n","n","a","h"]
Output: ["h","a","n","n","a","H"]

Constraints:
1 <= s.length <= 10^5
s[i] is a printable ascii character.
```

<details><summary>Hint</summary>

```text
1. The entire logic for reversing a string is based on using the opposite directional two-pointer approach!
```

</details>

</details>

<details><summary>C</summary>

```c
void reverseString(char* s, int sSize) {
    char tmp;
    int idx;
    for (idx = 0; idx < sSize / 2; ++idx) {
        tmp = s[idx];
        s[idx] = s[sSize - idx - 1];
        s[sSize - idx - 1] = tmp;
    }
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    void reverseString(vector<char>& s) {
        //
        reverse(s.begin(), s.end());
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def reverseString(self, s: List[str]) -> None:
        """
        Do not return anything, modify s in-place instead.
        """
        s.reverse()
```

</details>

## [345. Reverse Vowels of a String](https://leetcode.com/problems/reverse-vowels-of-a-string/)

- [Official](https://leetcode.com/problems/reverse-vowels-of-a-string/editorial/)
- [Official](https://leetcode.cn/problems/reverse-vowels-of-a-string/solutions/944385/fan-zhuan-zi-fu-chuan-zhong-de-yuan-yin-2bmos/)

<details><summary>Description</summary>

```text
Given a string s, reverse only all the vowels in the string and return it.

The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in both lower and upper cases, more than once.

Example 1:
Input: s = "hello"
Output: "holle"

Example 2:
Input: s = "leetcode"
Output: "leotcede"

Constraints:
1 <= s.length <= 3 * 10^5
s consist of printable ASCII characters.
```

</details>

<details><summary>C</summary>

```c
bool isVowel(char c) {
    bool retVal = false;

    // The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in both lower and upper cases
    if ((c == 'a') || (c == 'e') || (c == 'i') || (c == 'o') || (c == 'u')) {
        retVal = true;
    } else if ((c == 'A') || (c == 'E') || (c == 'I') || (c == 'O') || (c == 'U')) {
        retVal = true;
    }

    return retVal;
}
char* reverseVowels(char* s) {
    char* pRetVal = NULL;

    char tmp;
    int len = strlen(s);
    int left = 0;
    int right = len - 1;
    while (left < right) {
        while ((left < len) && (isVowel(s[left]) == false)) {
            ++left;
        }
        while ((right > 0) && (isVowel(s[right]) == false)) {
            --right;
        }

        if (left < right) {
            tmp = s[left];
            s[left++] = s[right];
            s[right--] = tmp;
        }
    }
    pRetVal = s;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    bool isVowel(char c) {
        bool retVal = false;

        // The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in both lower and upper cases
        if ((c == 'a') || (c == 'e') || (c == 'i') || (c == 'o') || (c == 'u')) {
            retVal = true;
        } else if ((c == 'A') || (c == 'E') || (c == 'I') || (c == 'O') || (c == 'U')) {
            retVal = true;
        }

        return retVal;
    }
    string reverseVowels(string s) {
        string retVal = "";

        int sSize = s.size();

        int left = 0;
        int right = sSize - 1;
        while (left < right) {
            while ((left < sSize) && (isVowel(s[left]) == false)) {
                ++left;
            }
            while ((right > 0) && (isVowel(s[right]) == false)) {
                --right;
            }

            if (left < right) {
                swap(s[left++], s[right--]);
            }
        }
        retVal = s;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def reverseVowels(self, s: str) -> str:
        retVal = ""

        s = list(s)
        sSize = len(s)

        left = 0
        right = sSize - 1
        while left < right:
            while (left < sSize) and (s[left] not in "aeiouAEIOU"):
                left += 1
            while (right > 0) and (s[right] not in "aeiouAEIOU"):
                right -= 1

            if left < right:
                s[left], s[right] = s[right], s[left]
                left += 1
                right -= 1
        retVal = "".join(s)

        return retVal
```

</details>

## [392. Is Subsequence](https://leetcode.com/problems/is-subsequence/)

- [Official](https://leetcode.cn/problems/is-subsequence/solutions/346539/pan-duan-zi-xu-lie-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given two strings s and t, return true if s is a subsequence of t, or false otherwise.

A subsequence of a string is a new string that is formed from the original string
by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters.
(i.e., "ace" is a subsequence of "abcde" while "aec" is not).

Example 1:
Input: s = "abc", t = "ahbgdc"
Output: true

Example 2:
Input: s = "axc", t = "ahbgdc"
Output: false

Constraints:
0 <= s.length <= 100
0 <= t.length <= 10^4
s and t consist only of lowercase English letters.

Follow up:
Suppose there are lots of incoming s, say s1, s2, ..., sk where k >= 109,
and you want to check one by one to see if t has its subsequence.
In this scenario, how would you change your code?
```

</details>

<details><summary>C</summary>

```c
bool isSubsequence(char* s, char* t) {
    bool retVal = false;

    while (*s && *t) {
        if (*s == *t) {
            ++s;
        }
        ++t;
    }

    if (!(*s)) {
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
    bool isSubsequence(string s, string t) {
        bool retVal = false;

        int sSize = s.size();
        int tSize = t.size();
        if (sSize > tSize) {
            return retVal;
        }

        int sIdx = 0;
        int tIdx = 0;
        while ((sIdx < sSize) && (tIdx < tSize)) {
            if (s[sIdx] == t[tIdx]) {
                ++sIdx;
            }
            ++tIdx;
        }
        if (sIdx == sSize) {
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
    def isSubsequence(self, s: str, t: str) -> bool:
        retVal = False

        sSize = len(s)
        tSize = len(t)
        if sSize > tSize:
            return retVal

        sIdx = 0
        tIdx = 0
        while (sIdx < sSize) and (tIdx < tSize):
            if s[sIdx] == t[tIdx]:
                sIdx += 1
            tIdx += 1
        if sIdx == sSize:
            retVal = True

        return retVal
```

</details>

## [541. Reverse String II](https://leetcode.com/problems/reverse-string-ii/)

- [Official](https://leetcode.com/problems/reverse-string-ii/editorial/)
- [Official](https://leetcode.cn/problems/reverse-string-ii/solutions/946553/fan-zhuan-zi-fu-chuan-ii-by-leetcode-sol-ua7s/)

<details><summary>Description</summary>

```text
Given a string s and an integer k,
reverse the first k characters for every 2k characters counting from the start of the string.

If there are fewer than k characters left, reverse all of them.
If there are less than 2k but greater than or equal to k characters,
then reverse the first k characters and leave the other as original.

Example 1:
Input: s = "abcdefg", k = 2
Output: "bacdfeg"

Example 2:
Input: s = "abcd", k = 2
Output: "bacd"

Constraints:
1 <= s.length <= 10^4
s consists of only lowercase English letters.
1 <= k <= 10^4
```

</details>

<details><summary>C</summary>

```c
char* reverseStr(char* s, int k) {
    char* pRetVal = s;

    int sSize = strlen(s);
    char tmp;
    int left, right;
    int i;
    for (i = 0; i < sSize; i += 2 * k) {
        left = i;
        right = fmin(i + k, sSize) - 1;
        while (left < right) {
            tmp = s[left];
            s[left++] = s[right];
            s[right--] = tmp;
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
    string reverseStr(string s, int k) {
        string retVal = s;

        int retValSize = retVal.size();
        for (int i = 0; i < retValSize; i += 2 * k) {
            reverse(retVal.begin() + i, retVal.begin() + min(i + k, retValSize));
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def reverseStr(self, s: str, k: int) -> str:
        retVal = ""

        sSize = len(s)
        for i in range(0, sSize, 2 * k):
            pStr1 = s[i: i + k]
            pStr2 = s[i + k: i + 2 * k]
            retVal += (pStr1[::-1] + pStr2)

        return retVal
```

</details>

## [557. Reverse Words in a String III](https://leetcode.com/problems/reverse-words-in-a-string-iii/)

- [Official](https://leetcode.com/problems/reverse-words-in-a-string-iii/editorial/)
- [Official](https://leetcode.cn/problems/reverse-words-in-a-string-iii/solutions/393471/fan-zhuan-zi-fu-chuan-zhong-de-dan-ci-iii-by-lee-2/)

<details><summary>Description</summary>

```text
Given a string s, reverse the order of characters in each word
within a sentence while still preserving whitespace and initial word order.

Example 1:
Input: s = "Let's take LeetCode contest"
Output: "s'teL ekat edoCteeL tsetnoc"

Example 2:
Input: s = "God Ding"
Output: "doG gniD"

Constraints:
1 <= s.length <= 5 * 10^4
s contains printable ASCII characters.
s does not contain any leading or trailing spaces.
There is at least one word in s.
All the words in s are separated by a single space.
```

</details>

<details><summary>C</summary>

```c
char* reverseWords(char* s) {
    char* pRetVal = s;

    int begin = 0;
    int end = 0;
    char tmp;
    int len = strlen(s);
    int idx;
    for (idx = 0; idx <= len; ++idx) {
        if ((s[idx] != ' ') && (s[idx] != '\0')) {
            continue;
        }

        end = idx - 1;
        while (end > begin) {
            tmp = s[begin];
            s[begin++] = s[end];
            s[end--] = tmp;
        }
        begin = idx + 1;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string reverseWords(string s) {
        string retVal = s;

        int retValSize = retVal.size();

        int left = 0;
        int right = 0;
        for (int i = 0; i <= retValSize; ++i) {
            if ((retVal[i] != ' ') && (retVal[i] != '\0')) {
                continue;
            }

            right = i - 1;
            while (left < right) {
                char tmp = retVal[left];
                retVal[left++] = retVal[right];
                retVal[right--] = tmp;
            }
            left = i + 1;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def reverseWords(self, s: str) -> str:
        retVal = ""

        for pStr in s.split():
            retVal += pStr[::-1] + " "
        retVal = retVal.rstrip()

        return retVal
```

</details>

## [792. Number of Matching Subsequences](https://leetcode.com/problems/number-of-matching-subsequences/)  1695

- [Official](https://leetcode.cn/problems/number-of-matching-subsequences/solutions/1973995/pi-pei-zi-xu-lie-de-dan-ci-shu-by-leetco-vki7/)

<details><summary>Description</summary>

```text
Given a string s and an array of strings words, return the number of words[i] that is a subsequence of s.

A subsequence of a string is a new string generated from the original string with some characters (can be none)
deleted without changing the relative order of the remaining characters.

For example, "ace" is a subsequence of "abcde".

Example 1:
Input: s = "abcde", words = ["a","bb","acd","ace"]
Output: 3
Explanation: There are three strings in words that are a subsequence of s: "a", "acd", "ace".

Example 2:
Input: s = "dsahjpjauf", words = ["ahjpjau","ja","ahbwzgqnuk","tnmlanowax"]
Output: 2

Constraints:
1 <= s.length <= 5 * 10^4
1 <= words.length <= 5000
1 <= words[i].length <= 50
s and words[i] consist of only lowercase English letters.
```

</details>

<details><summary>C</summary>

```c
#ifndef QUEUE_H
#define QUEUE_H

typedef struct Node {
    int idx;
    int size;
    struct Node *next;
} Node;
typedef struct {
    struct Node *head;
    struct Node *tail;
    int size;
} myQueue;
myQueue *myQueueCreate() {
    myQueue *pRetVal = NULL;

    pRetVal = (myQueue *)malloc(sizeof(myQueue));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->size = 0;
    pRetVal->head = NULL;
    pRetVal->tail = NULL;

    return pRetVal;
}
bool myQueueEnQueue(myQueue *pObj, int idx, int size) {
    bool retVal = false;

    struct Node *pNew = (struct Node *)malloc(sizeof(struct Node));
    if (pNew == NULL) {
        perror("malloc");
        return retVal;
    }
    retVal = true;

    pNew->idx = idx;
    pNew->size = size;
    pNew->next = NULL;
    if (pObj->head == NULL) {
        pObj->head = pNew;
        pObj->tail = pNew;
    } else {
        pObj->tail->next = pNew;
        pObj->tail = pNew;
    }
    pObj->size++;

    return retVal;
}
bool myQueueDeQueue(myQueue *pObj) {
    bool retVal = false;

    if (pObj->size == 0) {
        return retVal;
    }
    retVal = true;

    struct Node *pFree = pObj->head;
    pObj->head = pObj->head->next;
    pObj->size--;
    free(pFree);
    pFree = NULL;

    return retVal;
}
Node *myQueueFront(myQueue *pObj) {
    struct Node *pRetVal = NULL;

    if (pObj->size == 0) {
        return pRetVal;
    }
    pRetVal = pObj->head;

    return pRetVal;
}
bool myQueueIsEmpty(myQueue *pObj) {
    bool retVal = false;

    if (pObj->size == 0) {
        retVal = true;
    }

    return retVal;
}
void myQueueQueueFree(myQueue *pObj) {
    struct Node *pFree = NULL;
    struct Node *pCurrent = pObj->head;
    while (pCurrent != NULL) {
        pFree = pCurrent;
        pCurrent = pCurrent->next;
        free(pFree);
        pFree = NULL;
    }
    free(pObj);
    pObj = NULL;
}
#endif  // QUEUE_H
int numMatchingSubseq(char *s, char **words, int wordsSize) {
    int retVal = 0;

    int i;

#define MAX_RECORD_SIZE (26)  // s and words[i] consist of only lowercase English letters.
    myQueue *record[MAX_RECORD_SIZE];
    for (i = 0; i < MAX_RECORD_SIZE; ++i) {
        record[i] = myQueueCreate();
        if (record[i] == NULL) {
            goto _exit;
        }
    }
    for (i = 0; i < wordsSize; ++i) {
        myQueueEnQueue(record[words[i][0] - 'a'], i, 0);
    }

    int recordSize;
    Node *pEntry;
    int size, idx;
    int wordLength;
    int sSize = strlen(s);
    for (i = 0; i < sSize; ++i) {
        recordSize = record[s[i] - 'a']->size;
        while (recordSize) {
            recordSize--;

            pEntry = myQueueFront(record[s[i] - 'a']);
            idx = pEntry->idx;
            size = pEntry->size;

            myQueueDeQueue(record[s[i] - 'a']);
            wordLength = strlen(words[idx]);
            if (size == wordLength - 1) {
                ++retVal;
            } else {
                ++size;
                myQueueEnQueue(record[words[idx][size] - 'a'], idx, size);
            }
        }
    }

_exit:
    for (i = 0; i < MAX_RECORD_SIZE; i++) {
        myQueueQueueFree(record[i]);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int numMatchingSubseq(string s, vector<string>& words) {
        int retVal = 0;

        int wordsSize = words.size();

        vector<queue<pair<int, int>>> record(26);  // s and words[i] consist of only lowercase English letters.
        for (int i = 0; i < wordsSize; ++i) {
            record[words[i][0] - 'a'].emplace(i, 0);
        }

        for (char c : s) {
            auto& entry = record[c - 'a'];
            int size = entry.size();
            while (size--) {
                auto [wordsIndex, idx] = entry.front();
                entry.pop();

                int wordLength = words[wordsIndex].size();
                ++idx;
                if (idx == wordLength) {
                    ++retVal;
                } else {
                    record[words[wordsIndex][idx] - 'a'].emplace(wordsIndex, idx);
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
    def numMatchingSubseq(self, s: str, words: List[str]) -> int:
        retVal = 0

        record = defaultdict(list)
        for wordsIndex, word in enumerate(words):
            record[word[0]].append((wordsIndex, 0))

        for c in s:
            entry = record[c]
            record[c] = []

            for wordsIndex, idx in entry:
                idx += 1
                if idx == len(words[wordsIndex]):
                    retVal += 1
                else:
                    record[words[wordsIndex][idx]].append((wordsIndex, idx))

        return retVal
```

</details>

## [881. Boats to Save People](https://leetcode.com/problems/boats-to-save-people/)  1529

- [Official](https://leetcode.cn/problems/boats-to-save-people/solutions/958838/jiu-sheng-ting-by-leetcode-solution-0nsp/)

<details><summary>Description</summary>

```text
You are given an array people where people[i] is the weight of the ith person,
and an infinite number of boats where each boat can carry a maximum weight of limit.
Each boat carries at most two people at the same time, provided the sum of the weight of those people is at most limit.

Return the minimum number of boats to carry every given person.

Example 1:
Input: people = [1,2], limit = 3
Output: 1
Explanation: 1 boat (1, 2)

Example 2:
Input: people = [3,2,2,1], limit = 3
Output: 3
Explanation: 3 boats (1, 2), (2) and (3)

Example 3:
Input: people = [3,5,3,4], limit = 5
Output: 4
Explanation: 4 boats (3), (3), (4), (5)

Constraints:
1 <= people.length <= 5 * 10^4
1 <= people[i] <= limit <= 3 * 10^4
```

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int numRescueBoats(int* people, int peopleSize, int limit) {
    int retVal = 0;

    qsort(people, peopleSize, sizeof(int), compareInteger);

    int left = 0;
    int right = peopleSize - 1;
    while (left <= right) {
        if (people[left] + people[right] <= limit) {
            ++left;
        }
        --right;
        ++retVal;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int numRescueBoats(vector<int>& people, int limit) {
        int retVal = 0;

        sort(people.begin(), people.end());

        int left = 0;
        int right = people.size() - 1;
        while (left <= right) {
            if (people[left] + people[right] <= limit) {
                ++left;
            }
            --right;
            ++retVal;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def numRescueBoats(self, people: List[int], limit: int) -> int:
        retVal = 0

        people.sort()
        left = 0
        right = len(people) - 1
        while left <= right:
            if people[left] + people[right] <= limit:
                left += 1
            right -= 1
            retVal += 1

        return retVal
```

</details>

## [905. Sort Array By Parity](https://leetcode.com/problems/sort-array-by-parity/)  1178

<details><summary>Description</summary>

- [Official](https://leetcode.cn/problems/sort-array-by-parity/solutions/1449791/an-qi-ou-pai-xu-shu-zu-by-leetcode-solut-gpmm/)

```text
Given an integer array nums, move all the even integers at the beginning of the array followed by all the odd integers.

Return any array that satisfies this condition.

Example 1:
Input: nums = [3,1,2,4]
Output: [2,4,3,1]
Explanation: The outputs [4,2,3,1], [2,4,1,3], and [4,2,1,3] would also be accepted.

Example 2:
Input: nums = [0]
Output: [0]

Constraints:
1 <= nums.length <= 5000
0 <= nums[i] <= 5000
```

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortArrayByParity(int* nums, int numsSize, int* returnSize) {
    int* pRetVal;

    (*returnSize) = numsSize;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, (*returnSize) * sizeof(int));

    int head = 0;
    int tail = numsSize - 1;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if ((nums[i] % 2) == 0) {
            pRetVal[head++] = nums[i];
        } else {
            pRetVal[tail--] = nums[i];
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
    vector<int> sortArrayByParity(vector<int>& nums) {
        vector<int> retVal;

        for (int num : nums) {
            if (num % 2 == 0) {
                retVal.emplace_back(num);
            }
        }
        for (int num : nums) {
            if (num % 2 == 1) {
                retVal.emplace_back(num);
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
    def sortArrayByParity(self, nums: List[int]) -> List[int]:
        retVal = []

        for num in nums:
            if num % 2 == 0:
                retVal.append(num)

        for num in nums:
            if num % 2 == 1:
                retVal.append(num)

        return retVal
```

</details>

## [977. Squares of a Sorted Array](https://leetcode.com/problems/squares-of-a-sorted-array/)  1129

- [Official](https://leetcode.cn/problems/squares-of-a-sorted-array/solutions/447736/you-xu-shu-zu-de-ping-fang-by-leetcode-solution)

<details><summary>Description</summary>

```text
Given an integer array nums sorted in non-decreasing order,
return an array of the squares of each number sorted in non-decreasing order.

Example 1:
Input: nums = [-4,-1,0,3,10]
Output: [0,1,9,16,100]
Explanation: After squaring, the array becomes [16,1,0,9,100].
After sorting, it becomes [0,1,9,16,100].

Example 2:
Input: nums = [-7,-3,2,3,11]
Output: [4,9,9,49,121]

Constraints:
1 <= nums.length <= 10^4
-10^4 <= nums[i] <= 10^4
nums is sorted in non-decreasing order.

Follow up:
Squaring each element and sorting the new array is very trivial,
could you find an O(n) solution using a different approach?
```

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortedSquares(int* nums, int numsSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int*)malloc(numsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int left = 0;
    int right = numsSize - 1;
    int i;
    for (i = (numsSize - 1); i >= 0; --i) {
        if (abs(nums[left]) > abs(nums[right])) {
            pRetVal[i] = nums[left] * nums[left];
            ++left;
        } else {
            pRetVal[i] = nums[right] * nums[right];
            --right;
        }
    }
    (*returnSize) = numsSize;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> sortedSquares(vector<int>& nums) {
        vector<int> retVal;

        int numsSize = nums.size();
        retVal.resize(numsSize, 0);

        int left = 0;
        int right = numsSize - 1;
        for (int i = (numsSize - 1); i >= 0; --i) {
            if (abs(nums[left]) > abs(nums[right])) {
                retVal[i] = nums[left] * nums[left];
                ++left;
            } else {
                retVal[i] = nums[right] * nums[right];
                --right;
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
    def sortedSquares(self, nums: List[int]) -> List[int]:
        retVal = []

        numsSize = len(nums)
        retVal = [0] * numsSize

        left = 0
        right = numsSize - 1
        for i in range(numsSize-1, -1, -1):
            if abs(nums[left]) > abs(nums[right]):
                retVal[i] = nums[left] * nums[left]
                left += 1
            else:
                retVal[i] = nums[right] * nums[right]
                right -= 1

        return retVal
```

</details>

## [1498. Number of Subsequences That Satisfy the Given Sum Condition](https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/)  2276

- [Official](https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/editorial/)
- [Official](https://leetcode.cn/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/solutions/310424/man-zu-tiao-jian-de-zi-xu-lie-shu-mu-by-leetcode-s/)

<details><summary>Description</summary>

```text
You are given an array of integers nums and an integer target.

Return the number of non-empty subsequences of nums
such that the sum of the minimum and maximum element on it is less or equal to target.
Since the answer may be too large, return it modulo 109 + 7.

Example 1:
Input: nums = [3,5,6,7], target = 9
Output: 4
Explanation: There are 4 subsequences that satisfy the condition.
[3] -> Min value + max value <= target (3 + 3 <= 9)
[3,5] -> (3 + 5 <= 9)
[3,5,6] -> (3 + 6 <= 9)
[3,6] -> (3 + 6 <= 9)

Example 2:
Input: nums = [3,3,6,8], target = 10
Output: 6
Explanation: There are 6 subsequences that satisfy the condition. (nums can have repeated numbers).
[3] , [3] , [3,3], [3,6] , [3,6] , [3,3,6]

Example 3:
Input: nums = [2,3,3,4,6,7], target = 12
Output: 61
Explanation: There are 63 non-empty subsequences, two of them do not satisfy the condition ([6,7], [7]).
Number of valid subsequences (63 - 2 = 61).

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^6
1 <= target <= 10^6
```

<details><summary>Hint</summary>

```text
1. Sort the array nums.
2. Use two pointers approach:
   Given an index i (choose it as the minimum in a subsequence)
   find the maximum j where j ≥ i and nums[i] +nums[j] ≤ target.
3. Count the number of subsequences.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MODULO (int)(1e9 + 7)
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int numSubseq(int* nums, int numsSize, int target) {
    int retVal = 0;

    int pows[numsSize];
    memset(pows, 0, sizeof(pows));
    pows[0] = 1;
    int i;
    for (i = 1; i < numsSize; ++i) {
        pows[i] = pows[i - 1] * 2 % MODULO;
    }

    qsort(nums, numsSize, sizeof(int), compareInteger);
    int head = 0;
    int tail = numsSize - 1;
    while (head <= tail) {
        if (nums[head] + nums[tail] > target) {
            --tail;
            continue;
        }

        retVal += pows[tail - head];
        retVal %= MODULO;
        ++head;
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
    int numSubseq(vector<int>& nums, int target) {
        int retVal = 0;

        int numsSize = nums.size();
        vector<int> pows(numsSize, 1);
        for (int i = 1; i < numsSize; ++i) {
            pows[i] = pows[i - 1] * 2 % MODULO;
        }

        sort(nums.begin(), nums.end());
        int head = 0;
        int tail = numsSize - 1;
        while (head <= tail) {
            if (nums[head] + nums[tail] > target) {
                --tail;
                continue;
            }

            retVal += pows[tail - head];
            retVal %= MODULO;
            ++head;
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

    def numSubseq(self, nums: List[int], target: int) -> int:
        retVal = 0

        nums.sort()

        head = 0
        tail = len(nums) - 1
        while head <= tail:
            if nums[head] + nums[tail] > target:
                tail -= 1
                continue
            retVal += pow(2, (tail - head))
            retVal %= self.MODULO
            head += 1

        return retVal
```

</details>

## [1679. Max Number of K-Sum Pairs](https://leetcode.com/problems/max-number-of-k-sum-pairs)  1345

<details><summary>Description</summary>

```text
You are given an integer array nums and an integer k.

In one operation, you can pick two numbers from the array whose sum equals k and remove them from the array.

Return the maximum number of operations you can perform on the array.

Example 1:
Input: nums = [1,2,3,4], k = 5
Output: 2
Explanation: Starting with nums = [1,2,3,4]:
- Remove numbers 1 and 4, then nums = [2,3]
- Remove numbers 2 and 3, then nums = []
There are no more pairs that sum up to 5, hence a total of 2 operations.

Example 2:
Input: nums = [3,1,3,4,3], k = 6
Output: 1
Explanation: Starting with nums = [3,1,3,4,3]:
- Remove the first two 3's, then nums = [1,4,3]
There are no more pairs that sum up to 6, hence a total of 1 operation.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
1 <= k <= 10^9
```

<details><summary>Hint</summary>

```text
1. The abstract problem asks to count the number of disjoint pairs with a given sum k.
2. For each possible value x, it can be paired up with k - x.
3. The number of such pairs equals to min(count(x), count(k-x)), unless that x = k / 2,
   where the number of such pairs will be floor(count(x) / 2).
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int maxOperations(int* nums, int numsSize, int k) {
    int retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);
    int sum;
    int left = 0;
    int right = numsSize - 1;
    while (left < right) {
        sum = nums[left] + nums[right];
        if (sum == k) {
            ++left;
            --right;
            ++retVal;
        } else if (sum < k) {
            ++left;
        } else if (sum > k) {
            --right;
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
    int maxOperations(vector<int>& nums, int k) {
        int retVal = 0;

        sort(nums.begin(), nums.end());
        int numsSize = nums.size();
        int left = 0;
        int right = numsSize - 1;
        while (left < right) {
            int sum = nums[left] + nums[right];
            if (sum == k) {
                ++left;
                --right;
                ++retVal;
            } else if (sum < k) {
                ++left;
            } else if (sum > k) {
                --right;
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
    def maxOperations(self, nums: List[int], k: int) -> int:
        retVal = 0

        nums.sort()
        numsSize = len(nums)
        left = 0
        right = numsSize - 1
        while left < right:
            sum = nums[left] + nums[right]
            if sum == k:
                left += 1
                right -= 1
                retVal += 1
            elif sum < k:
                left += 1
            elif sum > k:
                right -= 1

        return retVal
```

</details>

## [1750. Minimum Length of String After Deleting Similar Ends](https://leetcode.com/problems/minimum-length-of-string-after-deleting-similar-ends/)  1501

- [Official](https://leetcode.cn/problems/minimum-length-of-string-after-deleting-similar-ends/solutions/2033813/shan-chu-zi-fu-chuan-liang-duan-xiang-to-biep/)

<details><summary>Description</summary>

```text
Given a string s consisting only of characters 'a', 'b', and 'c'.
You are asked to apply the following algorithm on the string any number of times:

Pick a non-empty prefix from the string s where all the characters in the prefix are equal.
Pick a non-empty suffix from the string s where all the characters in this suffix are equal.
The prefix and the suffix should not intersect at any index.
The characters from the prefix and suffix must be the same.
Delete both the prefix and the suffix.
Return the minimum length of s after performing the above operation any number of times (possibly zero times).

Example 1:
Input: s = "ca"
Output: 2
Explanation: You can't remove any characters, so the string stays as is.

Example 2:
Input: s = "cabaabac"
Output: 0
Explanation: An optimal sequence of operations is:
- Take prefix = "c" and suffix = "c" and remove them, s = "abaaba".
- Take prefix = "a" and suffix = "a" and remove them, s = "baab".
- Take prefix = "b" and suffix = "b" and remove them, s = "aa".
- Take prefix = "a" and suffix = "a" and remove them, s = "".

Example 3:
Input: s = "aabccabba"
Output: 3
Explanation: An optimal sequence of operations is:
- Take prefix = "aa" and suffix = "a" and remove them, s = "bccabb".
- Take prefix = "b" and suffix = "bb" and remove them, s = "cca".

Constraints:
1 <= s.length <= 10^5
s only consists of characters 'a', 'b', and 'c'.
```

<details><summary>Hint</summary>

```text
1. If both ends have distinct characters, no more operations can be made.
   Otherwise, the only operation is to remove all of the same characters from both ends.
   We will do this as many times as we can.
2. Note that if the length is equal 1 the answer is 1
```

</details>

</details>

<details><summary>C</summary>

```c
int minimumLength(char* s) {
    int retVal = 0;

    char equal;
    int left = 0;
    int right = strlen(s) - 1;
    while ((left < right) && (s[left] == s[right])) {
        equal = s[left];
        while ((left <= right) && (s[left] == equal)) {
            ++left;
        }
        while ((left <= right) && (s[right] == equal)) {
            --right;
        }
    }
    retVal = right - left + 1;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minimumLength(string s) {
        int retVal = 0;

        int left = 0;
        int right = s.size() - 1;
        while ((left < right) && (s[left] == s[right])) {
            char equal = s[left];
            while ((left <= right) && (s[left] == equal)) {
                ++left;
            }
            while ((left <= right) && (s[right] == equal)) {
                --right;
            }
        }
        retVal = right - left + 1;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minimumLength(self, s: str) -> int:
        retVal = 0

        left = 0
        right = len(s) - 1
        while (left < right) and (s[left] == s[right]):
            equal = s[left]
            while (left <= right) and (s[left] == equal):
                left += 1
            while (left <= right) and (s[right] == equal):
                right -= 1
        retVal = right - left + 1

        return retVal
```

</details>

## [1793. Maximum Score of a Good Subarray](https://leetcode.com/problems/maximum-score-of-a-good-subarray/)  1945

- [Official](https://leetcode.com/problems/maximum-score-of-a-good-subarray/editorial/)

<details><summary>Description</summary>

```text
You are given an array of integers nums (0-indexed) and an integer k.

The score of a subarray (i, j) is defined as min(nums[i], nums[i+1], ..., nums[j]) * (j - i + 1).
A good subarray is a subarray where i <= k <= j.

Return the maximum possible score of a good subarray.

Example 1:
Input: nums = [1,4,3,7,4,5], k = 3
Output: 15
Explanation: The optimal subarray is (1, 5) with a score of min(4,3,7,4,5) * (5-1+1) = 3 * 5 = 15.

Example 2:
Input: nums = [5,5,4,5,4,1,1,1], k = 0
Output: 20
Explanation: The optimal subarray is (0, 4) with a score of min(5,5,4,5,4) * (4-0+1) = 4 * 5 = 20.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 2 * 10^4
0 <= k < nums.length
```

<details><summary>Hint</summary>

```text
1. Try thinking about the prefix before index k and the suffix after index k as two separate arrays.
2. Using two pointers or binary search,
   we can find the maximum prefix of each array where the numbers are less than or equal to a certain value
```

</details>

</details>

<details><summary>C</summary>

```c
int maximumScore(int* nums, int numsSize, int k) {
    int retVal = 0;

    retVal = nums[k];
    int minValue = nums[k];
    int leftValue, rightValue;
    int left = k;
    int right = k;
    while ((left > 0) || (right < numsSize - 1)) {
        // 1 <= nums[i] <= 2 * 10^4, 0 <= k < nums.length
        leftValue = ((left > 0) ? nums[left - 1] : 0);
        rightValue = ((right < numsSize - 1) ? nums[right + 1] : 0);
        if (leftValue < rightValue) {
            right++;
            minValue = fmin(minValue, nums[right]);
        } else {
            left--;
            minValue = fmin(minValue, nums[left]);
        }

        retVal = fmax(retVal, minValue * (right - left + 1));
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maximumScore(vector<int>& nums, int k) {
        int retVal = 0;

        int numsSize = nums.size();

        retVal = nums[k];
        int minValue = nums[k];
        int left = k;
        int right = k;
        while ((left > 0) || (right < numsSize - 1)) {
            // 1 <= nums[i] <= 2 * 10^4, 0 <= k < nums.length
            int leftValue = ((left > 0) ? nums[left - 1] : 0);
            int rightValue = ((right < numsSize - 1) ? nums[right + 1] : 0);
            if (leftValue < rightValue) {
                right++;
                minValue = min(minValue, nums[right]);
            } else {
                left--;
                minValue = min(minValue, nums[left]);
            }

            retVal = max(retVal, minValue * (right - left + 1));
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maximumScore(self, nums: List[int], k: int) -> int:
        retVal = 0

        numsSize = len(nums)

        retVal = nums[k]
        minValue = nums[k]
        left = k
        right = k
        while (left > 0) or (right < numsSize-1):
            # 1 <= nums[i] <= 2 * 10^4, 0 <= k < nums.length
            leftValue = nums[left - 1] if left > 0 else 0
            rightValue = nums[right + 1] if right < numsSize-1 else 0
            if leftValue < rightValue:
                right += 1
                minValue = min(minValue, nums[right])
            else:
                left -= 1
                minValue = min(minValue, nums[left])

            retVal = max(retVal, minValue*(right-left+1))

        return retVal
```

</details>

## [1813. Sentence Similarity III](https://leetcode.com/problems/sentence-similarity-iii/)  1588

- [Official](https://leetcode.cn/problems/sentence-similarity-iii/solutions/2062566/ju-zi-xiang-si-xing-iii-by-leetcode-solu-vjy7/)

<details><summary>Description</summary>

```text
A sentence is a list of words that are separated by a single space with no leading or trailing spaces.
For example, "Hello World", "HELLO", "hello world hello world" are all sentences.
Words consist of only uppercase and lowercase English letters.

Two sentences sentence1 and sentence2 are similar if it is possible to insert an arbitrary sentence (possibly empty)
inside one of these sentences such that the two sentences become equal.
For example, sentence1 = "Hello my name is Jane" and sentence2 = "Hello Jane" can be made equal
by inserting "my name is" between "Hello" and "Jane" in sentence2.

Given two sentences sentence1 and sentence2, return true if sentence1 and sentence2 are similar.
Otherwise, return false.

Example 1:
Input: sentence1 = "My name is Haley", sentence2 = "My Haley"
Output: true
Explanation: sentence2 can be turned to sentence1 by inserting "name is" between "My" and "Haley".

Example 2:
Input: sentence1 = "of", sentence2 = "A lot of words"
Output: false
Explanation: No single sentence can be inserted inside one of the sentences to make it equal to the other.

Example 3:
Input: sentence1 = "Eating right now", sentence2 = "Eating"
Output: true
Explanation: sentence2 can be turned to sentence1 by inserting "right now" at the end of the sentence.

Constraints:
1 <= sentence1.length, sentence2.length <= 100
sentence1 and sentence2 consist of lowercase and uppercase English letters and spaces.
The words in sentence1 and sentence2 are separated by a single space.
```

</details>

<details><summary>C</summary>

```c
bool areSentencesSimilar(char* sentence1, char* sentence2) {
    bool retVal = false;

#define STRTOK_PATTERN (" ")
    char* p = NULL;

    char* words1[strlen(sentence1)];
    int words1Size = 0;
    p = strtok(sentence1, STRTOK_PATTERN);
    while (p != NULL) {
        words1[words1Size++] = p;
        p = strtok(NULL, STRTOK_PATTERN);
    }

    char* words2[strlen(sentence2)];
    int words2Size = 0;
    p = strtok(sentence2, STRTOK_PATTERN);
    while (p != NULL) {
        words2[words2Size++] = p;
        p = strtok(NULL, STRTOK_PATTERN);
    }

    int head = 0;
    while ((head < words1Size) && (head < words2Size)) {
        if (strcmp(words1[head], words2[head]) != 0) {
            break;
        }
        ++head;
    }

    int tail = 0;
    while ((tail < words1Size - head) && (tail < words2Size - head)) {
        if (strcmp(words1[words1Size - 1 - tail], words2[words2Size - 1 - tail]) != 0) {
            break;
        }
        ++tail;
    }

    if ((head + tail) == fmin(words1Size, words2Size)) {
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
    bool areSentencesSimilar(string sentence1, string sentence2) {
        bool retVal = false;

        vector<string> words1;
        istringstream in1(sentence1);
        string word1;
        while (in1 >> word1) {
            words1.push_back(word1);
        }

        vector<string> words2;
        istringstream in2(sentence2);
        string word2;
        while (in2 >> word2) {
            words2.push_back(word2);
        }

        while ((words1.empty() == false) && (words2.empty() == false)) {
            if (words1.front() == words2.front()) {
                words1.erase(words1.begin());
                words2.erase(words2.begin());
            } else {
                break;
            }
        }

        while ((words1.empty() == false) && (words2.empty() == false)) {
            if (words1.back() == words2.back()) {
                words1.pop_back();
                words2.pop_back();
            } else {
                break;
            }
        }

        if ((words1.empty() == true) || (words2.empty() == true)) {
            retVal = true;
        }

        return retVal;
    }
};
```

</details>

## [2000. Reverse Prefix of Word](https://leetcode.com/problems/reverse-prefix-of-word/)  1199

- [Official](https://leetcode.com/problems/reverse-prefix-of-word/editorial/)
- [Official](https://leetcode.cn/problems/reverse-prefix-of-word/solutions/1239946/fan-zhuan-dan-ci-qian-zhui-by-leetcode-s-ruaj/)

<details><summary>Description</summary>

```text
Given a 0-indexed string word and a character ch,
reverse the segment of word that starts at index 0 and ends at the index of the first occurrence of ch (inclusive).
If the character ch does not exist in word, do nothing.
- For example, if word = "abcdefd" and ch = "d",
  then you should reverse the segment that starts at 0 and ends at 3 (inclusive).
  The resulting string will be "dcbaefd".

Return the resulting string.

Example 1:
Input: word = "abcdefd", ch = "d"
Output: "dcbaefd"
Explanation: The first occurrence of "d" is at index 3.
Reverse the part of word from 0 to 3 (inclusive), the resulting string is "dcbaefd".

Example 2:
Input: word = "xyxzxe", ch = "z"
Output: "zxyxxe"
Explanation: The first and only occurrence of "z" is at index 3.
Reverse the part of word from 0 to 3 (inclusive), the resulting string is "zxyxxe".

Example 3:
Input: word = "abcd", ch = "z"
Output: "abcd"
Explanation: "z" does not exist in word.
You should not do any reverse operation, the resulting string is "abcd".

Constraints:
1 <= word.length <= 250
word consists of lowercase English letters.
ch is a lowercase English letter.
```

<details><summary>Hint</summary>

```text
1. Find the first index where ch appears.
2. Find a way to reverse a substring of word.
```

</details>

</details>

<details><summary>C</summary>

```c
char* reversePrefix(char* word, char ch) {
    char* pRetVal = word;

    int wordSize = strlen(word);
    int i;
    for (i = 0; i < wordSize; ++i) {
        if (word[i] == ch) {
            break;
        }
    }
    if (i == wordSize) {
        return pRetVal;
    }

    char tmp;
    int left = 0;
    int right = i;
    while (left < right) {
        tmp = word[right];
        word[right--] = word[left];
        word[left++] = tmp;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string reversePrefix(string word, char ch) {
        string retVal = word;

        size_t index = word.find(ch);
        if (index == string::npos) {
            return retVal;
        }
        reverse(retVal.begin(), retVal.begin() + index + 1);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def reversePrefix(self, word: str, ch: str) -> str:
        retVal = word

        idx = word.find(ch) + 1
        retVal = word[:idx][::-1] + word[idx:]

        return retVal
```

</details>

## [2108. Find First Palindromic String in the Array](https://leetcode.com/problems/find-first-palindromic-string-in-the-array/)  1215

- [Official](https://leetcode.com/problems/find-first-palindromic-string-in-the-array/editorial/)
- [Official](https://leetcode.cn/problems/find-first-palindromic-string-in-the-array/solutions/1165775/zhao-chu-shu-zu-zhong-de-di-yi-ge-hui-we-mo3m/)

<details><summary>Description</summary>

```text
Given an array of strings words, return the first palindromic string in the array.
If there is no such string, return an empty string "".

A string is palindromic if it reads the same forward and backward.

Example 1:
Input: words = ["abc","car","ada","racecar","cool"]
Output: "ada"
Explanation: The first string that is palindromic is "ada".
Note that "racecar" is also palindromic, but it is not the first.

Example 2:
Input: words = ["notapalindrome","racecar"]
Output: "racecar"
Explanation: The first and only string that is palindromic is "racecar".

Example 3:
Input: words = ["def","ghi"]
Output: ""
Explanation: There are no palindromic strings, so the empty string is returned.

Constraints:
1 <= words.length <= 100
1 <= words[i].length <= 100
words[i] consists only of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Iterate through the elements in order. As soon as the current element is a palindrome, return it.
2. To check if an element is a palindrome, can you reverse the string?
```

</details>

</details>

<details><summary>C</summary>

```c
bool isPalindrome(char *word, int wordSize) {
    bool retVal = true;

    int left = 0;
    int right = wordSize - 1;
    while (left < right) {
        if (word[left++] != word[right--]) {
            retVal = false;
            break;
        }
    }

    return retVal;
}
char *firstPalindrome(char **words, int wordsSize) {
    char *retVal = "";

    int i;
    for (i = 0; i < wordsSize; ++i) {
        if (isPalindrome(words[i], strlen(words[i])) == true) {
            retVal = words[i];
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
    bool isPalindrome(string word) {
        bool retVal = true;

        int left = 0;
        int right = word.size() - 1;
        while (left < right) {
            if (word[left++] != word[right--]) {
                retVal = false;
                break;
            }
        }

        return retVal;
    }
    string firstPalindrome(vector<string>& words) {
        string retVal = "";

        for (string word : words) {
            if (isPalindrome(word) == true) {
                retVal = word;
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
    def isPalindrome(self, word: str) -> bool:
        retVal = True

        wordSize = len(word)
        left = 0
        right = wordSize - 1
        while left < right:
            if word[left] != word[right]:
                retVal = False
                break
            left += 1
            right -= 1

        return retVal

    def firstPalindrome(self, words: List[str]) -> str:
        retVal = ""

        for word in words:
            if self.isPalindrome(word) == True:
                retVal = word
                break

        return retVal
```

</details>

## [2149. Rearrange Array Elements by Sign](https://leetcode.com/problems/rearrange-array-elements-by-sign/)  1235

- [Official](https://leetcode.com/problems/rearrange-array-elements-by-sign/editorial/)
- [Official](https://leetcode.cn/problems/rearrange-array-elements-by-sign/solutions/1231295/an-fu-hao-zhong-pai-shu-zu-by-leetcode-s-bgds/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array nums of even length
consisting of an equal number of positive and negative integers.

You should rearrange the elements of nums such that the modified array follows the given conditions:
1. Every consecutive pair of integers have opposite signs.
2. For all integers with the same sign, the order in which they were present in nums is preserved.
3. The rearranged array begins with a positive integer.

Return the modified array after rearranging the elements to satisfy the aforementioned conditions.

Example 1:
Input: nums = [3,1,-2,-5,2,-4]
Output: [3,-2,1,-5,2,-4]
Explanation:
The positive integers in nums are [3,1,2]. The negative integers are [-2,-5,-4].
The only possible way to rearrange them such that they satisfy all conditions is [3,-2,1,-5,2,-4].
Other ways such as [1,-2,2,-5,3,-4], [3,1,2,-2,-5,-4], [-2,3,-5,1,-4,2] are incorrect
because they do not satisfy one or more conditions.

Example 2:
Input: nums = [-1,1]
Output: [1,-1]
Explanation:
1 is the only positive integer and -1 the only negative integer in nums.
So nums is rearranged to [1,-1].

Constraints:
2 <= nums.length <= 2 * 10^5
nums.length is even
1 <= |nums[i]| <= 10^5
nums consists of equal number of positive and negative integers.
```

<details><summary>Hint</summary>

```text
1. Divide the array into two parts- one comprising of only positive integers and the other of negative integers.
2. Merge the two parts to get the resultant array.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *rearrangeArray(int *nums, int numsSize, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int *)malloc(numsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (numsSize * sizeof(int)));

    int positive = 0;
    int negative = 1;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] > 0) {
            pRetVal[positive] = nums[i];
            positive += 2;
        } else {
            pRetVal[negative] = nums[i];
            negative += 2;
        }
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
    vector<int> rearrangeArray(vector<int>& nums) {
        vector<int> retVal = nums;

        int positive = 0;
        int negative = 1;
        for (int num : nums) {
            if (num > 0) {
                retVal[positive] = num;
                positive += 2;
            } else {
                retVal[negative] = num;
                negative += 2;
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
    def rearrangeArray(self, nums: List[int]) -> List[int]:
        retVal = []

        positive = []
        negative = []
        for num in nums:
            if num > 0:
                positive.append(num)
            else:
                negative.append(num)

        for i, j in zip(positive, negative):
            retVal.append(i)
            retVal.append(j)

        return retVal
```

</details>

## [2332. The Latest Time to Catch a Bus](https://leetcode.com/problems/the-latest-time-to-catch-a-bus/)  1840

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array buses of length n, where buses[i] represents the departure time of the ith bus.
You are also given a 0-indexed integer array passengers of length m,
where passengers[j] represents the arrival time of the jth passenger.
All bus departure times are unique. All passenger arrival times are unique.

You are given an integer capacity, which represents the maximum number of passengers that can get on each bus.

When a passenger arrives, they will wait in line for the next available bus.
You can get on a bus that departs at x minutes if you arrive at y minutes where y <= x, and the bus is not full.
Passengers with the earliest arrival times get on the bus first.

More formally when a bus arrives, either:
- If capacity or fewer passengers are waiting for a bus, they will all get on the bus, or
- The capacity passengers with the earliest arrival times will get on the bus.

Return the latest time you may arrive at the bus station to catch a bus.
You cannot arrive at the same time as another passenger.

Note: The arrays buses and passengers are not necessarily sorted.

Example 1:
Input: buses = [10,20], passengers = [2,17,18,19], capacity = 2
Output: 16
Explanation: Suppose you arrive at time 16.
At time 10, the first bus departs with the 0th passenger.
At time 20, the second bus departs with you and the 1st passenger.
Note that you may not arrive at the same time as another passenger,
which is why you must arrive before the 1st passenger to catch the bus.

Example 2:
Input: buses = [20,30,10], passengers = [19,13,26,4,25,11,21], capacity = 2
Output: 20
Explanation: Suppose you arrive at time 20.
At time 10, the first bus departs with the 3rd passenger.
At time 20, the second bus departs with the 5th and 1st passengers.
At time 30, the third bus departs with the 0th passenger and you.
Notice if you had arrived any later, then the 6th passenger would have taken your seat on the third bus.

Constraints:
n == buses.length
m == passengers.length
1 <= n, m, capacity <= 10^5
2 <= buses[i], passengers[i] <= 10^9
Each element in buses is unique.
Each element in passengers is unique.
```

<details><summary>Hint</summary>

```text
1. Sort the buses and passengers arrays.
2. Use 2 pointers to traverse buses and passengers with a simulation of passengers getting on a particular bus.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int latestTimeCatchTheBus(int* buses, int busesSize, int* passengers, int passengersSize, int capacity) {
    int retVal = 0;

    //
    int busesIdx = 0;
    qsort(buses, busesSize, sizeof(int), compareInteger);
    int passengersIdx = 0;
    qsort(passengers, passengersSize, sizeof(int), compareInteger);
    int capacityIdx;

    //
    capacityIdx = 0;
    while ((busesIdx < (busesSize - 1)) && (passengersIdx < passengersSize)) {
        if ((passengers[passengersIdx] <= buses[busesIdx]) && (capacityIdx < capacity)) {
            ++passengersIdx;
            ++capacityIdx;
        } else {
            ++busesIdx;
            capacityIdx = 0;
        }
    }
    capacityIdx = 0;
    while ((passengersIdx < passengersSize) && (passengers[passengersIdx] <= buses[busesSize - 1]) &&
           (capacityIdx < capacity)) {
        ++passengersIdx;
        ++capacityIdx;
    }

    //
    if (capacityIdx < capacity) {
        retVal = buses[busesSize - 1];
    } else {
        retVal = passengers[passengersIdx - 1];
    }
    --passengersIdx;
    while ((passengersIdx >= 0) && (retVal == passengers[passengersIdx])) {
        retVal = passengers[passengersIdx] - 1;
        --passengersIdx;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int latestTimeCatchTheBus(vector<int>& buses, vector<int>& passengers, int capacity) {
        int retVal = 0;

        //
        int busesSize = buses.size();
        int busesIdx = 0;
        sort(buses.begin(), buses.end());
        int passengersSize = passengers.size();
        int passengersIdx = 0;
        sort(passengers.begin(), passengers.end());
        int capacityIdx;

        //
        capacityIdx = 0;
        while ((busesIdx < (busesSize - 1)) && (passengersIdx < passengersSize)) {
            if ((passengers[passengersIdx] <= buses[busesIdx]) && (capacityIdx < capacity)) {
                ++passengersIdx;
                ++capacityIdx;
            } else {
                ++busesIdx;
                capacityIdx = 0;
            }
        }
        capacityIdx = 0;
        while ((passengersIdx < passengersSize) && (passengers[passengersIdx] <= buses[busesSize - 1]) &&
               (capacityIdx < capacity)) {
            ++passengersIdx;
            ++capacityIdx;
        }

        //
        if (capacityIdx < capacity) {
            retVal = buses[busesSize - 1];
        } else {
            retVal = passengers[passengersIdx - 1];
        }
        --passengersIdx;
        while ((passengersIdx >= 0) && (retVal == passengers[passengersIdx])) {
            retVal = passengers[passengersIdx] - 1;
            --passengersIdx;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def latestTimeCatchTheBus(self, buses: List[int], passengers: List[int], capacity: int) -> int:
        retVal = 0

        #
        busesSize = len(buses)
        busesIdx = 0
        buses.sort()
        passengersSize = len(passengers)
        passengersIdx = 0
        passengers.sort()

        #
        capacityIdx = 0
        while (busesIdx < (busesSize - 1)) and (passengersIdx < passengersSize):
            if (passengers[passengersIdx] <= buses[busesIdx]) and (capacityIdx < capacity):
                passengersIdx += 1
                capacityIdx += 1
            else:
                busesIdx += 1
                capacityIdx = 0
        capacityIdx = 0
        while (passengersIdx < passengersSize) and \
                (passengers[passengersIdx] <= buses[busesSize - 1]) and \
                (capacityIdx < capacity):
            passengersIdx += 1
            capacityIdx += 1

        #
        if capacityIdx < capacity:
            retVal = buses[busesSize - 1]
        else:
            retVal = passengers[passengersIdx - 1]
        passengersIdx -= 1
        while (passengersIdx >= 0) and (retVal == passengers[passengersIdx]):
            retVal = passengers[passengersIdx] - 1
            passengersIdx -= 1

        return retVal
```

</details>

## [2441. Largest Positive Integer That Exists With Its Negative](https://leetcode.com/problems/largest-positive-integer-that-exists-with-its-negative/)  1167

- [Official](https://leetcode.com/problems/largest-positive-integer-that-exists-with-its-negative/editorial/)
- [Official](https://leetcode.cn/problems/largest-positive-integer-that-exists-with-its-negative/solutions/2266809/yu-dui-ying-fu-shu-tong-shi-cun-zai-de-z-kg8f/)

<details><summary>Description</summary>

```text
Given an integer array nums that does not contain any zeros,
find the largest positive integer k such that -k also exists in the array.

Return the positive integer k. If there is no such integer, return -1.

Example 1:
Input: nums = [-1,2,-3,3]
Output: 3
Explanation: 3 is the only valid k we can find in the array.

Example 2:
Input: nums = [-1,10,6,7,-7,1]
Output: 7
Explanation: Both 1 and 7 have their corresponding negative values in the array. 7 has a larger value.

Example 3:
Input: nums = [-10,8,6,7,-2,-3]
Output: -1
Explanation: There is no a single valid k, we return -1.

Constraints:
1 <= nums.length <= 1000
-1000 <= nums[i] <= 1000
nums[i] != 0
```

<details><summary>Hint</summary>

```text
1. What data structure can help you to determine if an element exists?
2. Would a hash table help?
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int findMaxK(int* nums, int numsSize) {
    int retVal = -1;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int left = 0;
    int right = numsSize - 1;
    while (left < right) {
        if ((-nums[left]) == nums[right]) {
            retVal = nums[right];
            break;
        } else if ((-nums[left]) > nums[right]) {
            left += 1;
        } else if ((-nums[left]) < nums[right]) {
            right -= 1;
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
    int findMaxK(vector<int>& nums) {
        int retVal = -1;

        sort(nums.begin(), nums.end());

        int left = 0;
        int right = nums.size() - 1;
        while (left < right) {
            if ((-nums[left]) == nums[right]) {
                retVal = nums[right];
                break;
            } else if ((-nums[left]) > nums[right]) {
                left += 1;
            } else if ((-nums[left]) < nums[right]) {
                right -= 1;
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
    def findMaxK(self, nums: List[int]) -> int:
        retVal = -1

        nums.sort()

        left = 0
        right = len(nums) - 1
        while left < right:
            if (-nums[left]) == nums[right]:
                retVal = nums[right]
                break
            elif (-nums[left]) > nums[right]:
                left += 1
            elif (-nums[left]) < nums[right]:
                right -= 1

        return retVal
```

</details>

## [2540. Minimum Common Value](https://leetcode.com/problems/minimum-common-value/)  1249

- [Official](https://leetcode.com/problems/minimum-common-value/editorial/)

<details><summary>Description</summary>

```text
Given two integer arrays nums1 and nums2, sorted in non-decreasing order,
return the minimum integer common to both arrays.
If there is no common integer amongst nums1 and nums2, return -1.

Note that an integer is said to be common to nums1 and nums2
if both arrays have at least one occurrence of that integer.

Example 1:
Input: nums1 = [1,2,3], nums2 = [2,4]
Output: 2
Explanation: The smallest element common to both arrays is 2, so we return 2.

Example 2:
Input: nums1 = [1,2,3,6], nums2 = [2,3,4,5]
Output: 2
Explanation: There are two common elements in the array 2 and 3 out of which 2 is the smallest, so 2 is returned.

Constraints:
1 <= nums1.length, nums2.length <= 10^5
1 <= nums1[i], nums2[j] <= 10^9
Both nums1 and nums2 are sorted in non-decreasing order.
```

<details><summary>Hint</summary>

```text
1. Try to use a set.
2. Otherwise, try to use a two-pointer approach.
```

</details>

</details>

<details><summary>C</summary>

```c
int getCommon(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int retVal = -1;

    int nums1Idx = 0;
    int nums2Idx = 0;
    while ((nums1Idx < nums1Size) && (nums2Idx < nums2Size)) {
        if (nums1[nums1Idx] == nums2[nums2Idx]) {
            retVal = nums1[nums1Idx];
            break;
        } else if (nums1[nums1Idx] > nums2[nums2Idx]) {
            nums2Idx++;
        } else if (nums1[nums1Idx] < nums2[nums2Idx]) {
            nums1Idx++;
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
    int getCommon(vector<int>& nums1, vector<int>& nums2) {
        int retVal = -1;

        int nums1Size = nums1.size();
        int nums2Size = nums2.size();

        int nums1Idx = 0;
        int nums2Idx = 0;
        while ((nums1Idx < nums1Size) && (nums2Idx < nums2Size)) {
            if (nums1[nums1Idx] == nums2[nums2Idx]) {
                retVal = nums1[nums1Idx];
                break;
            } else if (nums1[nums1Idx] > nums2[nums2Idx]) {
                nums2Idx++;
            } else if (nums1[nums1Idx] < nums2[nums2Idx]) {
                nums1Idx++;
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
    def getCommon(self, nums1: List[int], nums2: List[int]) -> int:
        retVal = -1

        num1Size = len(nums1)
        num2Size = len(nums2)

        nums1Idx = 0
        nums2Idx = 0
        while (nums1Idx < num1Size) and (nums2Idx < num2Size):
            if nums1[nums1Idx] == nums2[nums2Idx]:
                retVal = nums1[nums1Idx]
                break
            elif nums1[nums1Idx] > nums2[nums2Idx]:
                nums2Idx += 1
            elif nums1[nums1Idx] < nums2[nums2Idx]:
                nums1Idx += 1

        return retVal
```

</details>

## [2810. Faulty Keyboard](https://leetcode.com/problems/faulty-keyboard/)  1192

<details><summary>Description</summary>

```text
Your laptop keyboard is faulty, and whenever you type a character 'i' on it,
it reverses the string that you have written.
Typing other characters works as expected.

You are given a 0-indexed string s, and you type each character of s using your faulty keyboard.

Return the final string that will be present on your laptop screen.

Example 1:
Input: s = "string"
Output: "rtsng"
Explanation:
After typing first character, the text on the screen is "s".
After the second character, the text is "st".
After the third character, the text is "str".
Since the fourth character is an 'i', the text gets reversed and becomes "rts".
After the fifth character, the text is "rtsn".
After the sixth character, the text is "rtsng".
Therefore, we return "rtsng".

Example 2:
Input: s = "poiinter"
Output: "ponter"
Explanation:
After the first character, the text on the screen is "p".
After the second character, the text is "po".
Since the third character you type is an 'i', the text gets reversed and becomes "op".
Since the fourth character you type is an 'i', the text gets reversed and becomes "po".
After the fifth character, the text is "pon".
After the sixth character, the text is "pont".
After the seventh character, the text is "ponte".
After the eighth character, the text is "ponter".
Therefore, we return "ponter".

Constraints:
1 <= s.length <= 100
s consists of lowercase English letters.
s[0] != 'i'
```

<details><summary>Hint</summary>

```text
1. Try to build a new string by traversing the given string and reversing whenever you get the character ‘i’.
```

</details>

</details>

<details><summary>C</summary>

```c
char* finalString(char* s) {
    char* pRetVal = NULL;

    int sSize = strlen(s);

    int left, right;
    char tmp;
    int i;
    for (i = 0; i < sSize; ++i) {
        if (s[i] != 'i') {
            continue;
        }

        left = 0;
        right = i - 1;
        while (left < right) {
            tmp = s[left];
            s[left++] = s[right];
            s[right--] = tmp;
        }
    }

    int returnSize = sSize + 1;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));

    int idx = 0;
    for (i = 0; i < sSize; ++i) {
        if (s[i] != 'i') {
            pRetVal[idx++] = s[i];
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
    string finalString(string s) {
        string retVal = "";

        for (char c : s) {
            if (c == 'i') {
                reverse(retVal.begin(), retVal.end());
            } else {
                retVal += c;
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
    def finalString(self, s: str) -> str:
        retVal = ""

        for c in s:
            if c == 'i':
                retVal = retVal[::-1]
            else:
                retVal += c

        return retVal
```

</details>
