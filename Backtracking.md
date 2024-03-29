# Backtracking

## [17. Letter Combinations of a Phone Number](https://leetcode.com/problems/letter-combinations-of-a-phone-number/)

- [Official](https://leetcode.cn/problems/letter-combinations-of-a-phone-number/solutions/388738/dian-hua-hao-ma-de-zi-mu-zu-he-by-leetcode-solutio/)

<details><summary>Description</summary>

```text
Given a string containing digits from 2-9 inclusive,
return all possible letter combinations that the number could represent.
Return the answer in any order.

A mapping of digits to letters (just like on the telephone buttons) is given below.
Note that 1 does not map to any letters.

Example 1:
Input: digits = "23"
Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]

Example 2:
Input: digits = ""
Output: []

Example 3:
Input: digits = "2"
Output: ["a","b","c"]

Constraints:
0 <= digits.length <= 4
digits[i] is a digit in the range ['2', '9'].
```

</details>

<details><summary>C</summary>

```c
void backtracking(char *digits, int *returnSize, char **pRetVal, char **phoneMap, char *combination,
                  int *combinationIdx, int index) {
    char *pTmp = NULL;

    int digitsSize = strlen(digits);
    if (index == digitsSize) {
        pTmp = (char *)malloc(((*combinationIdx) + 1) * sizeof(char));
        if (pTmp == NULL) {
            perror("malloc");
            return;
        }
        memset(pTmp, 0, (((*combinationIdx) + 1) * sizeof(char)));
        memcpy(pTmp, combination, (((*combinationIdx) + 1) * sizeof(char)));
        pRetVal[(*returnSize)++] = pTmp;
        return;
    }

    char *letters = phoneMap[digits[index] - '0'];
    int len = strlen(letters);
    for (int i = 0; i < len; i++) {
        combination[(*combinationIdx)++] = letters[i];
        combination[(*combinationIdx)] = 0;
        backtracking(digits, returnSize, pRetVal, phoneMap, combination, combinationIdx, index + 1);
        combination[--(*combinationIdx)] = 0;
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **letterCombinations(char *digits, int *returnSize) {
    char **pRetVal = NULL;

    (*returnSize) = 0;

    int digitsSize = strlen(digits);

    //
    int maxReturnsize = 1;
    int i;
    for (i = 0; i < digitsSize; i++) {
        maxReturnsize *= 4;
    }
    pRetVal = (char **)malloc(maxReturnsize * sizeof(char *));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    //
    if (digitsSize == 0) {
        return pRetVal;
    }

    //
    int phoneMapSize = 10;
    char **phoneMap = (char **)malloc(phoneMapSize * sizeof(char *));
    if (pRetVal == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    int phoneMapColSize = 5;
    int j;
    for (i = 0; i < phoneMapSize; ++i) {
        phoneMap[i] = (char *)malloc(phoneMapColSize * sizeof(char));
        if (phoneMap[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(phoneMap[j]);
                phoneMap[j] = NULL;
            }
            free(phoneMap);
            phoneMap = NULL;
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        memset(phoneMap[i], 0, (phoneMapColSize * sizeof(char)));
    }
    snprintf(phoneMap[2], (phoneMapColSize * sizeof(char)), "abc");
    snprintf(phoneMap[3], (phoneMapColSize * sizeof(char)), "def");
    snprintf(phoneMap[4], (phoneMapColSize * sizeof(char)), "ghi");
    snprintf(phoneMap[5], (phoneMapColSize * sizeof(char)), "jkl");
    snprintf(phoneMap[6], (phoneMapColSize * sizeof(char)), "mno");
    snprintf(phoneMap[7], (phoneMapColSize * sizeof(char)), "pqrs");
    snprintf(phoneMap[8], (phoneMapColSize * sizeof(char)), "tuv");
    snprintf(phoneMap[9], (phoneMapColSize * sizeof(char)), "wxyz");
    int combinationSize = digitsSize + 1;
    char *combination = (char *)malloc(combinationSize * sizeof(char));
    if (combination == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset(combination, 0, (combinationSize * sizeof(char)));
    int combinationIdx = 0;
    backtracking(digits, returnSize, pRetVal, phoneMap, combination, &combinationIdx, 0);

    //
    for (i = 0; i < phoneMapSize; ++i) {
        free(phoneMap[i]);
        phoneMap[i] = NULL;
    }
    free(phoneMap);
    phoneMap = NULL;
    free(combination);
    combination = NULL;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    void backtracking(string digits, vector<string>& retVal, unordered_map<char, string>& phoneMap, string combination,
                      int index) {
        int digitsSize = digits.size();
        if (index == digitsSize) {
            retVal.emplace_back(combination);
            return;
        }

        for (auto letter : phoneMap[digits[index]]) {
            combination.push_back(letter);
            backtracking(digits, retVal, phoneMap, combination, index + 1);
            combination.pop_back();
        }
    }
    vector<string> letterCombinations(string digits) {
        vector<string> retVal;

        int digitsSize = digits.size();
        if (digitsSize == 0) {
            return retVal;
        }

        unordered_map<char, string> phoneMap{{'2', "abc"}, {'3', "def"},  {'4', "ghi"}, {'5', "jkl"},
                                             {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}};

        string combination;
        backtracking(digits, retVal, phoneMap, combination, 0);

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

    def backtracking(self, digits: str, retVal: List[str], phoneMap: dict, combination: List[str], index: int) -> None:
        if index == len(digits):
            retVal.append("".join(combination))
            return

        digit = digits[index]
        for letter in phoneMap[digit]:
            combination.append(letter)
            self.backtracking(digits, retVal, phoneMap, combination, index + 1)
            combination.pop()

    def letterCombinations(self, digits: str) -> List[str]:
        retVal = []

        if not digits:
            return retVal

        phoneMap = {
            "2": "abc",
            "3": "def",
            "4": "ghi",
            "5": "jkl",
            "6": "mno",
            "7": "pqrs",
            "8": "tuv",
            "9": "wxyz",
        }

        if self.method == 1:
            combination = list()
            self.backtracking(digits, retVal, phoneMap, combination, 0)
        elif self.method == 2:
            groups = (phoneMap[digit] for digit in digits)
            from itertools import product
            retVal = ["".join(combination) for combination in product(*groups)]

        return retVal
```

</details>

## [22. Generate Parentheses](https://leetcode.com/problems/generate-parentheses/)

- [Official](https://leetcode.cn/problems/generate-parentheses/solutions/192912/gua-hao-sheng-cheng-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

Example 1:
Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]

Example 2:
Input: n = 1
Output: ["()"]

Constraints:
1 <= n <= 8
```

</details>

<details><summary>C</summary>

```c
#define MAX_RETURN_COUNT (1430)  // 1 <= n <= 8: 1, 1, 2, 5, 14, 42, 132, 429, 1430
void backtracking(char **retVal, int n, int *returnSize, char *str, int strIdx, int open, int close) {
    int maxSize = 2 * n + 1;

    if ((open == 0) && (close == 0)) {
        retVal[(*returnSize)] = (char *)calloc(maxSize, sizeof(char));
        if (retVal[(*returnSize)] == NULL) {
            perror("calloc");
            return;
        }
        snprintf(retVal[(*returnSize)++], (maxSize * sizeof(char)), "%s", str);

        return;
    }

    str[strIdx] = '(';
    if (open > 0) {
        backtracking(retVal, n, returnSize, str, strIdx + 1, open - 1, close);
    }
    if (close > open) {
        str[strIdx] = ')';
        backtracking(retVal, n, returnSize, str, strIdx + 1, open, close - 1);
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **generateParenthesis(int n, int *returnSize) {
    char **pRetVal = NULL;

    pRetVal = (char **)malloc(MAX_RETURN_COUNT * sizeof(char *));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int maxSize = 2 * n + 1;
    char *str = (char *)calloc(maxSize, sizeof(char));
    if (str == NULL) {
        perror("calloc");
        return pRetVal;
    }
    int strIdx = 0;

    (*returnSize) = 0;
    backtracking(pRetVal, n, returnSize, str, strIdx, n, n);
    free(str);
    str = NULL;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    void backtracking(vector<string>& retVal, string str, int open, int close) {
        if ((open == 0) && (close == 0)) {
            retVal.emplace_back(str);
            return;
        }

        if (open > 0) {
            backtracking(retVal, str + "(", open - 1, close);
        }
        if (close > open) {
            backtracking(retVal, str + ")", open, close - 1);
        }
    }
    vector<string> generateParenthesis(int n) {
        vector<string> retVal;

        backtracking(retVal, "", n, n);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def backtracking(self, retVal: List[str], str: str, open: int, close: int):
        if open == 0 and close == 0:
            retVal.append(str)

        if open > 0:
            self.backtracking(retVal, str + "(", open - 1, close)

        if close > open:
            self.backtracking(retVal, str + ")", open, close-1)

    def generateParenthesis(self, n: int) -> List[str]:
        retVal = []

        self.backtracking(retVal, "", n, n)

        return retVal
```

</details>

## [39. Combination Sum](https://leetcode.com/problems/combination-sum/)

- [Official](https://leetcode.cn/problems/combination-sum/solutions/406516/zu-he-zong-he-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given an array of distinct integers candidates and a target integer target,
return a list of all unique combinations of candidates where the chosen numbers sum to target.
You may return the combinations in any order.

The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the
frequency of at least one of the chosen numbers is different.

The test cases are generated such that the number of unique combinations
that sum up to target is less than 150 combinations for the given input.

Example 1:
Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Explanation:
2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
7 is a candidate, and 7 = 7.
These are the only two combinations.

Example 2:
Input: candidates = [2,3,5], target = 8
Output: [[2,2,2,2],[2,3,3],[3,5]]

Example 3:
Input: candidates = [2], target = 1
Output: []

Constraints:
1 <= candidates.length <= 30
2 <= candidates[i] <= 40
All elements of candidates are distinct.
1 <= target <= 40
```

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
void backtracking(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes,
                  int** answer, int* combine, int* combineSize, int idx) {
    if (idx == candidatesSize) {
        return;
    }

    int* pTmp = NULL;
    if (target == 0) {
        pTmp = (int*)malloc((*combineSize) * sizeof(int));
        if (pTmp == NULL) {
            perror("malloc");
            return;
        }
        memset(pTmp, 0, ((*combineSize) * sizeof(int)));
        memcpy(pTmp, combine, ((*combineSize) * sizeof(int)));
        answer[(*returnSize)] = pTmp;
        (*returnColumnSizes)[(*returnSize)++] = (*combineSize);
        return;
    }

    backtracking(candidates, candidatesSize, target, returnSize, returnColumnSizes, answer, combine, combineSize,
                 idx + 1);
    if (target - candidates[idx] >= 0) {
        combine[(*combineSize)++] = candidates[idx];
        backtracking(candidates, candidatesSize, target - candidates[idx], returnSize, returnColumnSizes, answer,
                     combine, combineSize, idx);
        (*combineSize)--;
    }
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    //
    (*returnSize) = 0;
#define MAX_RETURNSIZE (1000)
    (*returnColumnSizes) = (int*)malloc(MAX_RETURNSIZE * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, (MAX_RETURNSIZE * sizeof(int)));

    pRetVal = (int**)malloc(MAX_RETURNSIZE * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }

    //
    if (candidatesSize == 0) {
        return pRetVal;
    }

    qsort(candidates, candidatesSize, sizeof(int), compareInteger);
    if (candidates[0] > target) {
        return pRetVal;
    }

#define MAX_RETURNCOLUMNSIZES (int)(40 / 2 + 4)  // 2 <= candidates[i] <= 40, 1 <= target <= 40
    int combineSize = 0;
    int combine[MAX_RETURNCOLUMNSIZES];
    memset(combine, 0, sizeof(combine));
    backtracking(candidates, candidatesSize, target, returnSize, returnColumnSizes, pRetVal, combine, &combineSize, 0);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    void backtracking(vector<int>& candidates, int target, int idx, vector<int>& combine, vector<vector<int>>& answer) {
        if (target < 0) {
            return;
        } else if (target == 0) {
            answer.emplace_back(combine);
            return;
        }

        int candidatesSize = candidates.size();
        for (int i = idx; i < candidatesSize; i++) {
            if (candidates[i] > target) {
                break;
            }
            combine.push_back(candidates[i]);
            backtracking(candidates, target - candidates[i], i, combine, answer);
            combine.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> retVal;

        if (candidates.empty() == true) {
            return retVal;
        }

        if (*min_element(candidates.begin(), candidates.end()) > target) {
            return retVal;
        }

        sort(candidates.begin(), candidates.end());
        vector<int> combine;
        backtracking(candidates, target, 0, combine, retVal);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def backtracking(self, candidates: List[int], target: int, combine: List[int], answer: List[List[int]]) -> None:
        if target < 0:
            return
        elif target == 0:
            answer.append(combine)
            return

        candidatesSize = len(candidates)
        for i in range(candidatesSize):
            if candidates[i] > target:
                break
            self.backtracking(candidates[i:], target-candidates[i], combine+[candidates[i]], answer)

    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        retVal = []

        if not candidates:
            return retVal

        if min(candidates) > target:
            retVal

        candidates.sort()
        combine = []
        self.backtracking(candidates, target, combine, retVal)

        return retVal
```

</details>

## [40. Combination Sum II](https://leetcode.com/problems/combination-sum-ii/)

- [Official](https://leetcode.com/problems/combination-sum-ii/editorial/)
- [Official](https://leetcode.cn/problems/combination-sum-ii/solutions/407850/zu-he-zong-he-ii-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given a collection of candidate numbers (candidates) and a target number (target),
find all unique combinations in candidates where the candidate numbers sum to target.

Each number in candidates may only be used once in the combination.

Note: The solution set must not contain duplicate combinations.

Example 1:
Input: candidates = [10,1,2,7,6,1,5], target = 8
Output:
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]

Example 2:
Input: candidates = [2,5,2,1,2], target = 5
Output:
[
[1,2,2],
[5]
]

Constraints:
1 <= candidates.length <= 100
1 <= candidates[i] <= 50
1 <= target <= 30
```

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
void backtracking(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes,
                  int** answer, int* combine, int* combineSize, int idx, int* back) {
    int* pTmp = NULL;
    if (target == 0) {
        pTmp = (int*)malloc((*combineSize) * sizeof(int));
        if (pTmp == NULL) {
            perror("malloc");
            return;
        }
        memset(pTmp, 0, ((*combineSize) * sizeof(int)));
        memcpy(pTmp, combine, ((*combineSize) * sizeof(int)));
        answer[(*returnSize)] = pTmp;
        (*returnColumnSizes)[(*returnSize)++] = (*combineSize);
        return;
    }

    if (idx == candidatesSize) {
        return;
    }

    int i;
    for (i = idx; i < candidatesSize; ++i) {
        if (candidates[i] > target) {
            break;
        }

        if (candidates[i] == (*back)) {
            continue;
        }

        combine[(*combineSize)++] = candidates[i];
        backtracking(candidates, candidatesSize, target - candidates[i], returnSize, returnColumnSizes, answer, combine,
                     combineSize, i + 1, back);
        (*back) = combine[--(*combineSize)];
    }
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combinationSum2(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    //
    (*returnSize) = 0;
#define MAX_RETURNSIZE (1000)
    (*returnColumnSizes) = (int*)malloc(MAX_RETURNSIZE * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, (MAX_RETURNSIZE * sizeof(int)));

    pRetVal = (int**)malloc(MAX_RETURNSIZE * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }

    //
    if (candidatesSize == 0) {
        return pRetVal;
    }

    qsort(candidates, candidatesSize, sizeof(int), compareInteger);
    if (candidates[0] > target) {
        return pRetVal;
    }

#define MAX_RETURNCOLUMNSIZES (int)(30 / 1 + 2)  // 2 <= candidates[i] <= 40, 1 <= target <= 40
    int combineSize = 0;
    int combine[MAX_RETURNCOLUMNSIZES];
    memset(combine, 0, sizeof(combine));
    int back = 0;  // 1 <= candidates[i] <= 50
    backtracking(candidates, candidatesSize, target, returnSize, returnColumnSizes, pRetVal, combine, &combineSize, 0,
                 &back);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    void backtracking(vector<int>& candidates, int target, int idx, int* back, vector<int>& combine,
                      vector<vector<int>>& answer) {
        if (target == 0) {
            answer.emplace_back(combine);
            return;
        }

        int candidatesSize = candidates.size();
        if (idx == candidatesSize) {
            return;
        }

        for (int i = idx; i < candidatesSize; ++i) {
            if (candidates[i] > target) {
                break;
            }

            if (candidates[i] == (*back)) {
                continue;
            }
            combine.emplace_back(candidates[i]);
            backtracking(candidates, target - candidates[i], i + 1, back, combine, answer);
            (*back) = combine.back();
            combine.pop_back();
        }
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> retVal;

        if (candidates.empty() == true) {
            return retVal;
        }

        if (*min_element(candidates.begin(), candidates.end()) > target) {
            return retVal;
        }

        int back = 0;  // 1 <= candidates[i] <= 50
        vector<int> combine;
        sort(candidates.begin(), candidates.end());
        backtracking(candidates, target, 0, &back, combine, retVal);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def backtracking(self, candidates: List[int], target: int, start: int, combine: List[int],
                     answer: List[List[int]]) -> None:
        if target == 0:
            answer.append(combine[:])
            return

        candidatesSize = len(candidates)
        for i in range(start, candidatesSize):
            if (i > start) and (candidates[i] == candidates[i - 1]):
                continue

            updateTarget = target - candidates[i]
            if updateTarget < 0:
                break

            combine.append(candidates[i])
            self.backtracking(candidates, updateTarget, i + 1, combine, answer)
            combine.pop()

    def combinationSum2(self, candidates: List[int], target: int) -> List[List[int]]:
        retVal = []

        if not candidates:
            return retVal

        if min(candidates) > target:
            retVal

        candidates.sort()

        combine = []
        self.backtracking(candidates, target, 0, combine, retVal)

        return retVal
```

</details>

## [46. Permutations](https://leetcode.com/problems/permutations/)

- [Official](https://leetcode.com/problems/permutations/editorial/)
- [Official](https://leetcode.cn/problems/permutations/solutions/218275/quan-pai-lie-by-leetcode-solution-2/)

<details><summary>Description</summary>

```text
Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.

Example 1:
Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

Example 2:
Input: nums = [0,1]
Output: [[0,1],[1,0]]

Example 3:
Input: nums = [1]
Output: [[1]]

Constraints:
1 <= nums.length <= 6
-10 <= nums[i] <= 10
```

</details>

<details><summary>C</summary>

```c
void swap(int* nums, int indexA, int indexB) {
    int temp = nums[indexA];
    nums[indexA] = nums[indexB];
    nums[indexB] = temp;
}
void backtrack(int* nums, int numsSize, int* returnSize, int** returnColumnSizes, int** pRetVal, int offset) {
    if (offset == numsSize) {
        pRetVal[(*returnSize)] = (int*)malloc(numsSize * sizeof(int));
        if (pRetVal[(*returnSize)] == NULL) {
            perror("malloc");
            return;
        }
        memset(pRetVal[(*returnSize)], 0, (numsSize * sizeof(int)));
        memcpy(pRetVal[(*returnSize)], nums, (numsSize * sizeof(int)));
        (*returnColumnSizes)[(*returnSize)++] = numsSize;
        return;
    }

    int i;
    for (i = offset; i < numsSize; i++) {
        swap(nums, i, offset);
        backtrack(nums, numsSize, returnSize, returnColumnSizes, pRetVal, offset + 1);
        swap(nums, i, offset);
    }
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

#define MAX_RETURN_SIZE (6 * 5 * 4 * 3 * 2 * 1 + 1)

    (*returnSize) = 0;

    (*returnColumnSizes) = (int*)malloc(MAX_RETURN_SIZE * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        return pRetVal;
    }

    pRetVal = (int**)malloc(MAX_RETURN_SIZE * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }

    backtrack(nums, numsSize, returnSize, returnColumnSizes, pRetVal, 0);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    void backtracking(vector<vector<int>>& answer, vector<int>& output, int first, int len) {
        if (first == len) {
            answer.emplace_back(output);
            return;
        }

        for (int i = first; i < len; ++i) {
            swap(output[i], output[first]);
            backtracking(answer, output, first + 1, len);
            swap(output[i], output[first]);
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> retVal;

        int numsSize = nums.size();
        backtracking(retVal, nums, 0, numsSize);

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

    def backtracking(self, sol: List[int], nums: List[int], check: int, answer: List[List[int]]) -> None:
        if len(sol) == len(nums):
            answer.append(sol)
            return

        for i in range(len(nums)):
            if check[i] == 1:
                continue
            check[i] = 1
            self.backtracking(sol+[nums[i]], nums, check, answer)
            check[i] = 0

    def permute(self, nums: List[int]) -> List[List[int]]:
        retVal = []

        if self.method == 1:
            check = [0 for i in range(len(nums))]
            self.backtracking([], nums, check, retVal)
        elif self.method == 2:
            from itertools import permutations
            retVal = list(permutations(nums))

        return retVal
```

</details>

## [77. Combinations](https://leetcode.com/problems/combinations)

- [Official](https://leetcode.cn/problems/combinations/solutions/405094/zu-he-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given two integers n and k, return all possible combinations of k numbers chosen from the range [1, n].

You may return the answer in any order.

Example 1:
Input: n = 4, k = 2
Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
Explanation: There are 4 choose 2 = 6 total combinations.
Note that combinations are unordered, i.e., [1,2] and [2,1] are considered to be the same combination.

Example 2:
Input: n = 1, k = 1
Output: [[1]]
Explanation: There is 1 choose 1 = 1 total combination.

Constraints:
1 <= n <= 20
1 <= k <= n
```

</details>

<details><summary>C</summary>

```c
void backtracking(int cur, int n, int k, int** ans, int* ansSize, int* temp, int* tempSize) {
    if ((*tempSize) + (n - cur + 1) < k) {
        return;
    }

    if ((*tempSize) == k) {
        int* tmp = malloc(sizeof(int) * k);
        for (int i = 0; i < k; i++) {
            tmp[i] = temp[i];
        }
        ans[(*ansSize)++] = tmp;
        return;
    }

    temp[(*tempSize)++] = cur;
    backtracking(cur + 1, n, k, ans, ansSize, temp, tempSize);
    (*tempSize)--;
    backtracking(cur + 1, n, k, ans, ansSize, temp, tempSize);
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combine(int n, int k, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int**)malloc(10001 * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int tempSize = 0;
    int* temp = malloc(k * sizeof(int));
    if (temp == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }

    backtracking(1, n, k, pRetVal, returnSize, temp, &tempSize);

    int i;
    (*returnColumnSizes) = (int*)malloc(sizeof(int) * (*returnSize));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        free(temp);
        temp = NULL;
        for (i = 0; i < (*returnSize); ++i) {
            free(pRetVal[i]);
            pRetVal[i] = NULL;
        }
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    for (i = 0; i < (*returnSize); i++) {
        (*returnColumnSizes)[i] = k;
    }

    free(temp);
    temp = NULL;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    void backtracking(int cur, int n, int k, vector<vector<int>>& answer, vector<int>& temp) {
        int tempSize = temp.size();

        if (tempSize + (n - cur + 1) < k) {
            return;
        }

        if (tempSize == k) {
            answer.push_back(temp);
            return;
        }

        temp.push_back(cur);
        backtracking(cur + 1, n, k, answer, temp);
        temp.pop_back();
        backtracking(cur + 1, n, k, answer, temp);
    }
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> retVal;

        vector<int> temp;
        backtracking(1, n, k, retVal, temp);

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

    def backtracking(self, remain: int, comb: List[int], next: int, n: int, answer: List[List[int]]) -> None:
        if remain == 0:
            answer.append(comb.copy())
            return

        for i in range(next, n+1):
            comb.append(i)
            self.backtracking(remain-1, comb, i+1, n, answer)
            comb.pop()

    def combine(self, n: int, k: int) -> List[List[int]]:
        retVal = []

        if self.method == 1:
            self.backtracking(k, [], 1, n, retVal)
        elif self.method == 2:
            from itertools import combinations
            retVal = list(combinations(range(1, n+1), k))

        return retVal
```

</details>

## [93. Restore IP Addresses](https://leetcode.com/problems/restore-ip-addresses/)

- [Official](https://leetcode.com/problems/restore-ip-addresses/solutions/2868540/restore-ip-addresses/)
- [Official](https://leetcode.cn/problems/restore-ip-addresses/solutions/366426/fu-yuan-ipdi-zhi-by-leetcode-solution/)

<details><summary>Description</summary>

```text
A valid IP address consists of exactly four integers separated by single dots.
Each integer is between 0 and 255 (inclusive) and cannot have leading zeros.
- For example, "0.1.2.201" and "192.168.1.1" are valid IP addresses,
  but "0.011.255.245", "192.168.1.312" and "192.168@1.1" are invalid IP addresses.

Given a string s containing only digits, return all possible valid IP addresses that can be formed by inserting dots into s.
You are not allowed to reorder or remove any digits in s.
You may return the valid IP addresses in any order.

Example 1:
Input: s = "25525511135"
Output: ["255.255.11.135","255.255.111.35"]

Example 2:
Input: s = "0000"
Output: ["0.0.0.0"]

Example 3:
Input: s = "101023"
Output: ["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]

Constraints:
1 <= s.length <= 20
s consists of digits only.
```

</details>

<details><summary>C</summary>

```c
// https://leetcode.cn/problems/restore-ip-addresses/solutions/404642/hui-su-jian-zhi-0ms100-by-shaw-r/
#define MAX_IP_FORMAT_LENGTH (5)
void dfs(char* s, char** pRetVal, int* returnSize, int step, int index, int len, char* pTmp) {
    int tmpSize = len + MAX_IP_FORMAT_LENGTH;

    if (step == 4) {
        pRetVal[*returnSize] = (char*)malloc(tmpSize * sizeof(char));
        if (pRetVal[*returnSize] == NULL) {
            perror("malloc");
            return;
        }
        memset(pRetVal[*returnSize], 0, (tmpSize * sizeof(char)));

        pTmp[index + step - 1] = '\0';
        memcpy(pRetVal[*returnSize], pTmp, (sizeof(char) * tmpSize));
        (*returnSize)++;

        return;
    }

    if ((len - index - 1 <= (3 - step) * 3) && (len - index - 1 >= (3 - step))) {
        pTmp[index + step] = s[index];
        pTmp[index + step + 1] = '.';

        dfs(s, pRetVal, returnSize, step + 1, index + 1, len, pTmp);
    }

    if ((len - index - 2 <= (3 - step) * 3) && (len - index - 2 >= (3 - step)) && (s[index] != '0')) {
        pTmp[index + step] = s[index];
        pTmp[index + step + 1] = s[index + 1];
        pTmp[index + step + 2] = '.';

        dfs(s, pRetVal, returnSize, step + 1, index + 2, len, pTmp);
    }

    if ((len - index - 3 <= (3 - step) * 3 && len - index - 3 >= (3 - step) && s[index] != '0') &&
        ((s[index] - '0') * 100 + (s[index + 1] - '0') * 10 + s[index + 2] - '0' <= 255)) {
        pTmp[index + step] = s[index];
        pTmp[index + step + 1] = s[index + 1];
        pTmp[index + step + 2] = s[index + 2];
        pTmp[index + step + 3] = '.';

        dfs(s, pRetVal, returnSize, step + 1, index + 3, len, pTmp);
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** restoreIpAddresses(char* s, int* returnSize) {
    char** pRetVal = NULL;

    (*returnSize) = 0;

    int len = strlen(s);
    // IP Format: xxx.xxx.xxx.xxx or x.x.x.x
    if ((len > 12) || (len < 4)) {
        return pRetVal;
    }

#define MAX_RETURN (200)
    pRetVal = (char**)malloc(MAX_RETURN * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int tmpSize = len + MAX_IP_FORMAT_LENGTH;
    char* pTmp = (char*)malloc(tmpSize * sizeof(char));
    if (pTmp == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pTmp, 0, (tmpSize * sizeof(char)));
    dfs(s, pRetVal, returnSize, 0, 0, len, pTmp);
    free(pTmp);
    pTmp = NULL;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {

    }
};
```

</details>

## [131. Palindrome Partitioning](https://leetcode.com/problems/palindrome-partitioning/)

- [Official](https://leetcode.com/problems/palindrome-partitioning/solutions/857510/palindrome-partitioning/)
- [Official](https://leetcode.cn/problems/palindrome-partitioning/solutions/639633/fen-ge-hui-wen-chuan-by-leetcode-solutio-6jkv/)

<details><summary>Description</summary>

```text
Given a string s, partition s such that every substring of the partition is a palindrome.
Return all possible palindrome partitioning of s.

Example 1:
Input: s = "aab"
Output: [["a","a","b"],["aa","b"]]

Example 2:
Input: s = "a"
Output: [["a"]]

Constraints:
1 <= s.length <= 16
s contains only lowercase English letters.
```

</details>

<details><summary>C</summary>

```c
int isPalindrome(char* s, int** dp, int i, int j) {
    if (dp[i][j]) {
        return dp[i][j];
    }

    if (i >= j) {
        return dp[i][j] = 1;
    }

    return dp[i][j] = (s[i] == s[j] ? isPalindrome(s, dp, i + 1, j - 1) : -1);
}
void dfs(char* s, int len, int idx, int** dp, char*** ret, int* retSize, int* retColSize, char** ans, int* ansSize) {
    int i, j;

    if (idx == len) {
        int ansColSize;
        char** tmp = (char**)malloc((*ansSize) * sizeof(char*));
        if (tmp == NULL) {
            perror("malloc");
            return;
        }
        for (i = 0; i < (*ansSize); ++i) {
            ansColSize = strlen(ans[i]) + 1;
            tmp[i] = (char*)malloc(ansColSize * sizeof(char));
            if (tmp[i] == NULL) {
                perror("malloc");
                for (j = 0; j < i; ++j) {
                    free(tmp[j]);
                    tmp[j] = NULL;
                }
                free(tmp);
                tmp = NULL;
                return;
            }
            memset(tmp[i], 0, (ansColSize * sizeof(char)));
            memcpy(tmp[i], ans[i], (ansColSize * sizeof(char)));
        }
        ret[(*retSize)] = tmp;
        retColSize[(*retSize)++] = (*ansSize);

        return;
    }

    char* sub = NULL;
    for (i = idx; i < len; ++i) {
        if (isPalindrome(s, dp, idx, i) == 1) {
            sub = (char*)malloc((i - idx + 2) * sizeof(char));
            if (sub == NULL) {
                perror("malloc");
                return;
            }
            for (j = idx; j <= i; ++j) {
                sub[j - idx] = s[j];
            }
            sub[i - idx + 1] = '\0';

            ans[(*ansSize)++] = sub;
            dfs(s, len, i + 1, dp, ret, retSize, retColSize, ans, ansSize);
            --(*ansSize);

            free(sub);
            sub = NULL;
        }
    }
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** partition(char* s, int* returnSize, int** returnColumnSizes) {
    char*** pRetVal = NULL;

    int i, j;

    int len = strlen(s);

    // max return size
    (*returnSize) = len * (1 << len);

    // malloc returnColumnSizes
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }

    // malloc return char*** array
    pRetVal = (char***)malloc((*returnSize) * sizeof(char**));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        (*returnSize) = 0;
        return pRetVal;
    }

    /* Dynamic Programming Preprocessing
     *  f(i,j): s[i..j] is Palindrome or not
     *            | True, i≥j
     *  f(i,j) = <
     *            | f(i+1, j−1) ∧ (s[i]=s[j]), otherwise
     */
    int* dp[len];
    for (i = 0; i < len; ++i) {
        dp[i] = (int*)malloc(len * sizeof(int));
        if (dp[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(dp[j]);
                dp[j] = NULL;
            }
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        for (j = 0; j < len; ++j) {
            dp[i][j] = 1;
        }
    }
    for (i = len - 1; i >= 0; --i) {
        for (j = i + 1; j < len; ++j) {
            dp[i][j] = (s[i] == s[j]) && dp[i + 1][j - 1];
        }
    }

    //
    (*returnSize) = 0;
    char* answer[len];
    int answerSize = 0;
    dfs(s, len, 0, dp, pRetVal, returnSize, *returnColumnSizes, answer, &answerSize);

    // free Dynamic Programming Preprocessing
    for (i = 0; i < len; ++i) {
        free(dp[i]);
        dp[i] = NULL;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
public:
    vector<vector<string>> partition(string s) {

    }
};
```

</details>

## [216. Combination Sum III](https://leetcode.com/problems/combination-sum-iii/)

- [Official](https://leetcode.cn/problems/combination-sum-iii/solutions/409198/zu-he-zong-he-iii-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Find all valid combinations of k numbers that sum up to n such that the following conditions are true:
- Only numbers 1 through 9 are used.
- Each number is used at most once.

Return a list of all possible valid combinations.
The list must not contain the same combination twice, and the combinations may be returned in any order.

Example 1:
Input: k = 3, n = 7
Output: [[1,2,4]]
Explanation:
1 + 2 + 4 = 7
There are no other valid combinations.

Example 2:
Input: k = 3, n = 9
Output: [[1,2,6],[1,3,5],[2,3,4]]
Explanation:
1 + 2 + 6 = 9
1 + 3 + 5 = 9
2 + 3 + 4 = 9
There are no other valid combinations.

Example 3:
Input: k = 4, n = 1
Output: []
Explanation: There are no valid combinations.
Using 4 different numbers in the range [1,9], the smallest sum we can get is 1+2+3+4 = 10 and since 10 > 1,
there are no valid combination.

Constraints:
2 <= k <= 9
1 <= n <= 60
```

</details>

<details><summary>C</summary>

```c
void backtracking(int k, int n, int* returnSize, int** returnColumnSizes, int start, int* combine, int* combineSize,
                  int** answer) {
    int* pTmp = NULL;
    if ((*combineSize) > k) {
        return;
    } else if (n < 0) {
        return;
    } else if (((*combineSize) == k) && (n == 0)) {
        pTmp = (int*)malloc(k * sizeof(int));
        if (pTmp == NULL) {
            perror("malloc");
            return;
        }
        memset(pTmp, 0, (k * sizeof(int)));
        memcpy(pTmp, combine, (k * sizeof(int)));
        answer[(*returnSize)] = pTmp;
        (*returnColumnSizes)[(*returnSize)] = k;
        (*returnSize)++;
        return;
    }

    // Only numbers 1 through 9 are used.
    int i;
    for (i = start; i < 10; ++i) {
        combine[(*combineSize)++] = i;
        backtracking(k, n - i, returnSize, returnColumnSizes, i + 1, combine, combineSize, answer);
        (*combineSize)--;
    }
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combinationSum3(int k, int n, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;

#define MAX_RETURN_SIZE (10001)
    pRetVal = (int**)malloc(MAX_RETURN_SIZE * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    (*returnColumnSizes) = (int*)malloc(MAX_RETURN_SIZE * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }

    int maxCombineSize = k + 1;
    int* combine = (int*)malloc(maxCombineSize * sizeof(int));
    int combineSize = 0;
    if (combine == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset(combine, 0, (maxCombineSize * sizeof(int)));
    backtracking(k, n, returnSize, returnColumnSizes, 1, combine, &combineSize, pRetVal);
    free(combine);
    combine = NULL;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    void backtracking(int k, int n, int start, vector<int>& combine, vector<vector<int>>& answer) {
        int combineSize = combine.size();
        if (combineSize > k) {
            return;
        } else if (n < 0) {
            return;
        } else if ((combineSize == k) && (n == 0)) {
            answer.push_back(combine);
            return;
        }

        // Only numbers 1 through 9 are used.
        for (int i = start; i < 10; ++i) {
            combine.push_back(i);
            backtracking(k, n - i, i + 1, combine, answer);
            combine.pop_back();
        }
    }
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> retVal;

        vector<int> combine;
        backtracking(k, n, 1, combine, retVal);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def backtracking(self, k: int, n: int, start: int, combine: List[int], answer: List[List[int]]) -> None:
        if (len(combine) > k) or (n < 0):
            return

        if (len(combine) == k) and (n == 0):
            answer.append(combine[:])
            return

        # Only numbers 1 through 9 are used.
        for i in range(start, 10):
            combine.append(i)
            self.backtracking(k, n-i, i+1, combine, answer)
            combine.pop()

    def combinationSum3(self, k: int, n: int) -> List[List[int]]:
        retVal = []

        combine = []
        self.backtracking(k, n, 1, combine, retVal)

        return retVal
```

</details>

## [491. Non-decreasing Subsequences](https://leetcode.com/problems/non-decreasing-subsequences/)

- [Official](https://leetcode.com/problems/non-decreasing-subsequences/solutions/2910678/increasing-subsequences/)
- [Official](https://leetcode.cn/problems/non-decreasing-subsequences/solutions/387656/di-zeng-zi-xu-lie-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given an integer array nums,
return all the different possible non-decreasing subsequences of the given array with at least two elements.
You may return the answer in any order.

Example 1:
Input: nums = [4,6,7,7]
Output: [[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]

Example 2:
Input: nums = [4,4,3,2,1]
Output: [[4,4]]

Constraints:
1 <= nums.length <= 15
-100 <= nums[i] <= 100
```

</details>

<details><summary>C</summary>

```c
#define BITMASKS (1)  // Time Limit Exceeded    // https://leetcode.com/problems/subsets/
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** findSubsequences(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int** retVal = NULL;

    int i, j, k;

    //
    (*returnSize) = 1 << numsSize;

    //
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return retVal;
    }
    memset((*returnColumnSizes), 0, ((*returnSize) * sizeof(int)));
    //
    retVal = (int**)malloc((*returnSize) * sizeof(int*));
    if (retVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        (*returnSize) = 0;
        return retVal;
    }
#if 0
    for (i = 0; i < (*returnSize); ++i) {
        retVal[i] = (int*)malloc(numsSize * sizeof(int));
        if (retVal[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(retVal[j]);
                retVal[j] = NULL;
            }
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            (*returnSize) = 0;
            return retVal;
        }
        memset(retVal[i], 0, (numsSize * sizeof(int)));
    }
#endif

#if (BITMASKS)
    printf("BITMASKS\n");

    //
    int idx = 0;
    for (i = 1; i < (1 << numsSize); ++i) {
        retVal[idx] = (int*)malloc(numsSize * sizeof(int));
        if (retVal[idx] == NULL) {
            perror("malloc");
            for (j = 0; j < idx; ++j) {
                free(retVal[j]);
                retVal[j] = NULL;
            }
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            (*returnSize) = 0;
            return retVal;
        }
        memset(retVal[idx], 0, (numsSize * sizeof(int)));

        for (j = 0; j < numsSize; ++j) {
            if (i >> j & 1) {
                retVal[idx][(*returnColumnSizes)[idx]] = nums[j];
                (*returnColumnSizes)[idx]++;
            }
        }

        if ((*returnColumnSizes)[idx] < 2) {
            (*returnColumnSizes)[idx] = 0;
            free(retVal[idx]);
            retVal[idx] = NULL;
            continue;
        }

        for (j = 1; j < (*returnColumnSizes)[idx]; ++j) {
            if (retVal[idx][j - 1] > retVal[idx][j]) {
                break;
            }
        }
        if (j != (*returnColumnSizes)[idx]) {
            (*returnColumnSizes)[idx] = 0;
            free(retVal[idx]);
            retVal[idx] = NULL;
            continue;
        }

        for (j = 0; j < idx; ++j) {
            if ((*returnColumnSizes)[idx] != (*returnColumnSizes)[j]) {
                continue;
            }

            for (k = 0; k < (*returnColumnSizes)[j]; ++k) {
                if (retVal[idx][k] != retVal[j][k]) {
                    break;
                }
            }
            if (k == (*returnColumnSizes)[j]) {
                break;
            }
        }
        if (j != idx) {
            (*returnColumnSizes)[idx] = 0;
            free(retVal[idx]);
            retVal[idx] = NULL;
            continue;
        }

        ++idx;
    }
    (*returnSize) = idx;
#endif

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        vector<vector<int>> retVal;

        int n = nums.size();
        set<vector<int>> result;
        for (int bitmask = 1; bitmask < (1 << n); ++bitmask) {
            vector<int> sequence;
            for (int i = 0; i < n; ++i) {
                if (((bitmask >> i) & 1) == 1) {
                    sequence.push_back(nums[i]);
                }
            }

            if (sequence.size() >= 2) {
                bool isIncreasing = true;
                for (long unsigned int i = 0; i < sequence.size() - 1; ++i) {
                    isIncreasing &= sequence[i] <= sequence[i + 1];
                }
                if (isIncreasing) {
                    result.insert(sequence);
                }
            }
        }
        retVal = vector(result.begin(), result.end());

        return retVal;
    }
};
```

</details>

## [784. Letter Case Permutation](https://leetcode.com/problems/letter-case-permutation)  1341

- [Official](https://leetcode.cn/problems/letter-case-permutation/solutions/1934375/zi-mu-da-xiao-xie-quan-pai-lie-by-leetco-cwpx/)

<details><summary>Description</summary>

```text
Given a string s, you can transform every letter individually to be lowercase or uppercase to create another string.

Return a list of all possible strings we could create. Return the output in any order.

Example 1:
Input: s = "a1b2"
Output: ["a1b2","a1B2","A1b2","A1B2"]

Example 2:
Input: s = "3z4"
Output: ["3z4","3Z4"]

Constraints:
1 <= s.length <= 12
s consists of lowercase English letters, uppercase English letters, and digits.
```

</details>

<details><summary>C</summary>

```c
void backtracking(char *s, int idx, char **returnValue, int *returnSize) {
    while ((s[idx] != '\0') && (isdigit(s[idx]))) {
        ++idx;
    }

    if (s[idx] == '\0') {
        returnValue[(*returnSize)] = (char *)malloc((strlen(s) + 1) * sizeof(char));
        if (returnValue[(*returnSize)] == NULL) {
            perror("malloc");
            return;
        }
        memset(returnValue[(*returnSize)], 0, ((strlen(s) + 1) * sizeof(char)));
        memcpy(returnValue[(*returnSize)], s, ((strlen(s) + 1) * sizeof(char)));
        (*returnSize)++;

        return;
    }

    s[idx] ^= 32;
    backtracking(s, idx + 1, returnValue, returnSize);

    s[idx] ^= 32;
    backtracking(s, idx + 1, returnValue, returnSize);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **letterCasePermutation(char *s, int *returnSize) {
    char **pRetVal = NULL;

    int len = strlen(s);

    (*returnSize) = 0;
    pRetVal = (char **)malloc((1 << len) * sizeof(char *));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    backtracking(s, 0, pRetVal, returnSize);

    return pRetVal;
}
```

</details>

## [980. Unique Paths III](https://leetcode.com/problems/unique-paths-iii/)  1830

- [Official](https://leetcode.cn/problems/unique-paths-iii/solutions/3594/bu-tong-lu-jing-iii-by-leetcode/)

<details><summary>Description</summary>

```text
You are given an m x n integer array grid where grid[i][j] could be:
- 1 representing the starting square. There is exactly one starting square.
- 2 representing the ending square. There is exactly one ending square.
- 0 representing empty squares we can walk over.
- -1 representing obstacles that we cannot walk over.
Return the number of 4-directional walks from the starting square to the ending square,
that walk over every non-obstacle square exactly once.

Example 1:
Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
Output: 2
Explanation: We have the following two paths:
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)

Example 2:
Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,0,2]]
Output: 4
Explanation: We have the following four paths:
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2),(2,3)
2. (0,0),(0,1),(1,1),(1,0),(2,0),(2,1),(2,2),(1,2),(0,2),(0,3),(1,3),(2,3)
3. (0,0),(1,0),(2,0),(2,1),(2,2),(1,2),(1,1),(0,1),(0,2),(0,3),(1,3),(2,3)
4. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2),(2,3)

Example 3:
Input: grid = [[0,1],[2,0]]
Output: 0
Explanation: There is no path that walks over every empty square exactly once.
Note that the starting and ending square can be anywhere in the grid.

Constraints:
m == grid.length
n == grid[i].length
1 <= m, n <= 20
1 <= m * n <= 20
-1 <= grid[i][j] <= 2
There is exactly one starting cell and one ending cell.
```

</details>

<details><summary>C</summary>

```c
void dfs(int** grid, int gridSize, int* gridColSize, int* pathNum, int* zeroNum, int t, int x, int y) {
    if ((x < 0) || (x >= gridSize) || (y < 0) || (y >= gridColSize[0])) {
        return;
    }

    if ((grid[x][y] == 2) && (t != (*zeroNum))) {
        return;
    }

    if ((grid[x][y] == 2) && (t == (*zeroNum))) {
        (*pathNum)++;
        return;
    }

    if (grid[x][y] == -1) {
        return;
    }

    int temp = grid[x][y];
    grid[x][y] = -1;
    dfs(grid, gridSize, gridColSize, pathNum, zeroNum, t + 1, x - 1, y);
    dfs(grid, gridSize, gridColSize, pathNum, zeroNum, t + 1, x + 1, y);
    dfs(grid, gridSize, gridColSize, pathNum, zeroNum, t + 1, x, y + 1);
    dfs(grid, gridSize, gridColSize, pathNum, zeroNum, t + 1, x, y - 1);
    grid[x][y] = temp;
}
int uniquePathsIII(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int pathNum = 0;
    int zeroNum = 0;
    int x = 0;
    int y = 0;
    int i, j;
    for (i = 0; i < gridSize; ++i) {
        for (j = 0; j < gridColSize[0]; ++j) {
            if (grid[i][j] == 0) {
                ++zeroNum;
            }
            if (grid[i][j] == 1) {
                x = i;
                y = j;
            }
        }
    }
    dfs(grid, gridSize, gridColSize, &pathNum, &zeroNum, -1, x, y);

    retVal = pathNum;

    return retVal;
}
```

</details>

## [1239. Maximum Length of a Concatenated String with Unique Characters](https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/)  1719

- [Official](https://leetcode.cn/problems/maximum-length-of-a-concatenated-string-with-unique-characters/solutions/834267/chuan-lian-zi-fu-chuan-de-zui-da-chang-d-g6gk/)

<details><summary>Description</summary>

```text
You are given an array of strings arr.
A string s is formed by the concatenation of a subsequence of arr that has unique characters.

Return the maximum possible length of s.

A subsequence is an array that can be derived from another array
by deleting some or no elements without changing the order of the remaining elements.

Example 1:
Input: arr = ["un","iq","ue"]
Output: 4
Explanation: All the valid concatenations are:
- ""
- "un"
- "iq"
- "ue"
- "uniq" ("un" + "iq")
- "ique" ("iq" + "ue")
Maximum length is 4.

Example 2:
Input: arr = ["cha","r","act","ers"]
Output: 6
Explanation: Possible longest valid concatenations are "chaers" ("cha" + "ers") and "acters" ("act" + "ers").

Example 3:
Input: arr = ["abcdefghijklmnopqrstuvwxyz"]
Output: 26
Explanation: The only string in arr has all 26 characters.

Constraints:
1 <= arr.length <= 16
1 <= arr[i].length <= 26
arr[i] contains only lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. You can try all combinations and keep mask of characters you have.
2. You can use DP.
```

</details>

</details>

<details><summary>C</summary>

```c
void backtracking(unsigned int* pMasks, int start, int end, unsigned int mask, int* pMaxLength) {
    int i;
    for (i = start; i < end; ++i) {
        if ((mask & pMasks[i]) == 0) {
            backtracking(pMasks, i + 1, end, (mask | pMasks[i]), pMaxLength);
        }
    }

    int count = 0;
    while (mask) {
        count += (mask & 1);
        mask >>= 1;
    }
    (*pMaxLength) = ((*pMaxLength) > count) ? (*pMaxLength) : count;
}
int maxLength(char** arr, int arrSize) {
    int retVal = 0;

    unsigned int masks[arrSize];
    memset(masks, 0, sizeof(masks));
    unsigned int mask;
    int i;
    for (i = 0; i < arrSize; ++i) {
        while (*arr[i]) {
            mask = (1 << (*arr[i] - 'a'));
            if ((masks[i] & mask) != 0) {
                masks[i] = 0;
                break;
            }
            masks[i] |= mask;

            arr[i]++;
        }
    }
    backtracking(masks, 0, arrSize, 0, &retVal);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    void backtracking(vector<unsigned int>& masks, int start, int end, unsigned int mask, int* returnLength) {
        for (int i = start; i < end; ++i) {
            if ((mask & masks[i]) == 0) {
                backtracking(masks, i + 1, end, (mask | masks[i]), returnLength);
            }
        }

        int count = 0;
        while (mask) {
            count += (mask & 1);
            mask >>= 1;
        }
        (*returnLength) = max((*returnLength), count);
    }
    int maxLength(vector<string>& arr) {
        int retVal = 0;

        int arrSize = arr.size();
        vector<unsigned int> masks(arrSize, 0);
        for (int i = 0; i < arrSize; ++i) {
            for (char c : arr[i]) {
                unsigned int mask = 1 << (c - 'a');
                if ((mask & masks[i]) != 0) {
                    masks[i] = 0;
                    break;
                }
                masks[i] |= mask;
            }
        }
        backtracking(masks, 0, arrSize, 0, &retVal);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def __init__(self) -> None:
        self.returnLength = 0

    def backtracking(self, masks: List[int], start: int, end: int, mask: int) -> None:
        for i in range(start, end):
            if (mask & masks[i]) == 0:
                self.backtracking(masks, i+1, end,  (mask | masks[i]))

        count = 0
        while mask:
            count += (mask & 1)
            mask >>= 1
        self.returnLength = max(self.returnLength, count)

    def maxLength(self, arr: List[str]) -> int:
        retVal = 0

        arrSize = len(arr)
        masks = [0] * arrSize
        for idx, value in enumerate(arr):
            for c in value:
                mask = 1 << (ord(c) - ord('a'))
                if (mask & masks[idx]) != 0:
                    masks[idx] = 0
                    break
                masks[idx] |= mask
        self.returnLength = 0
        self.backtracking(masks, 0, arrSize, 0)

        retVal = self.returnLength

        return retVal
```

</details>

## [1601. Maximum Number of Achievable Transfer Requests](https://leetcode.com/problems/maximum-number-of-achievable-transfer-requests/)  2118

- [Official](https://leetcode.com/problems/maximum-number-of-achievable-transfer-requests/editorial/)
- [Official](https://leetcode.cn/problems/maximum-number-of-achievable-transfer-requests/solutions/1283215/zui-duo-ke-da-cheng-de-huan-lou-qing-qiu-ae0e/)

<details><summary>Description</summary>

```text
We have n buildings numbered from 0 to n - 1.
Each building has a number of employees.
It's transfer season, and some employees want to change the building they reside in.

You are given an array requests where requests[i] = [fromi, toi] represents
an employee's request to transfer from building fromi to building toi.

All buildings are full, so a list of requests is achievable only if for each building,
the net change in employee transfers is zero.
This means the number of employees leaving is equal to the number of employees moving in.
For example if n = 3 and two employees are leaving building 0, one is leaving building 1, and one is leaving building 2,
there should be two employees moving to building 0, one employee moving to building 1,
and one employee moving to building 2.

Return the maximum number of achievable requests.

Example 1:
Input: n = 5, requests = [[0,1],[1,0],[0,1],[1,2],[2,0],[3,4]]
Output: 5
Explantion: Let's see the requests:
From building 0 we have employees x and y and both want to move to building 1.
From building 1 we have employees a and b and they want to move to buildings 2 and 0 respectively.
From building 2 we have employee z and they want to move to building 0.
From building 3 we have employee c and they want to move to building 4.
From building 4 we don't have any requests.
We can achieve the requests of users x and b by swapping their places.
We can achieve the requests of users y, a and z by swapping the places in the 3 buildings.

Example 2:
Input: n = 3, requests = [[0,0],[1,2],[2,1]]
Output: 3
Explantion: Let's see the requests:
From building 0 we have employee x and they want to stay in the same building 0.
From building 1 we have employee y and they want to move to building 2.
From building 2 we have employee z and they want to move to building 1.
We can achieve all the requests.

Example 3:
Input: n = 4, requests = [[0,3],[3,1],[1,2],[2,0]]
Output: 4

Constraints:
1 <= n <= 20
1 <= requests.length <= 16
requests[i].length == 2
0 <= fromi, toi < n
```

<details><summary>Hint</summary>

```text
1. Think brute force
2. When is a subset of requests okay?
```

</details>

</details>

<details><summary>C</summary>

```c
void backtracking(int n, int** requests, int requestsSize, int* requestsColSize, int index, int* building, int* count,
                  int* zero, int* answer) {
    if (index == requestsSize) {
        if ((*zero) == n) {
            (*answer) = fmax((*answer), (*count));
        }
        return;
    }

    backtracking(n, requests, requestsSize, requestsColSize, index + 1, building, count, zero, answer);

    int z = (*zero);
    (*count) += 1;
    int x = requests[index][0];
    int y = requests[index][1];
    (*zero) -= (building[x] == 0);
    building[x] -= 1;
    (*zero) += (building[x] == 0);
    (*zero) -= (building[y] == 0);
    building[y] += 1;
    (*zero) += building[y] == 0;
    backtracking(n, requests, requestsSize, requestsColSize, index + 1, building, count, zero, answer);
    building[y] -= 1;
    building[x] += 1;
    (*count) -= 1;
    (*zero) = z;
}
int maximumRequests(int n, int** requests, int requestsSize, int* requestsColSize) {
    int retVal = 0;

    int building[n];
    memset(building, 0, sizeof(building));
    int count = 0;
    int zero = n;
    backtracking(n, requests, requestsSize, requestsColSize, 0, building, &count, &zero, &retVal);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    int answer = 0;

   public:
    void backtracking(int n, vector<vector<int>>& requests, int index, vector<int>& building, int count, int zero) {
        int requestsSize = requests.size();
        if (index == requestsSize) {
            if (zero == n) {
                answer = max(answer, count);
            }
            return;
        }

        backtracking(n, requests, index + 1, building, count, zero);

        int z = zero;
        ++count;
        int x = requests[index][0];
        int y = requests[index][1];
        zero -= (building[x] == 0);
        building[x] -= 1;
        zero += (building[x] == 0);
        zero -= (building[y] == 0);
        building[y] += 1;
        zero += building[y] == 0;
        backtracking(n, requests, index + 1, building, count, zero);
        building[y] -= 1;
        building[x] += 1;
        --count;
        zero = z;
    }
    int maximumRequests(int n, vector<vector<int>>& requests) {
        int retVal = 0;

        answer = 0;
        vector<int> building(n, 0);
        int count = 0;
        int zero = n;
        backtracking(n, requests, 0, building, count, zero);
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
        self.answer = 0
        self.n = 0
        self.requests = [[]]
        self.requestsSize = 0

    def backtracking(self, index: int, building: List[int], count: int, zero: int) -> None:
        if index == self.requestsSize:
            if zero == self.n:
                self.answer = max(self.answer, count)
            return

        self.backtracking(index + 1, building, count, zero)

        z = zero
        count += 1
        x, y = self.requests[index]
        zero -= (building[x] == 0)
        building[x] -= 1
        zero += (building[x] == 0)
        zero -= (building[y] == 0)
        building[y] += 1
        zero += building[y] == 0
        self.backtracking(index + 1, building, count, zero)
        building[y] -= 1
        building[x] += 1
        count -= 1
        zero = z

    def maximumRequests(self, n: int, requests: List[List[int]]) -> int:
        retVal = 0

        self.answer = 0
        self.n = n
        self.requests = requests
        self.requestsSize = len(requests)

        building = [0] * n
        count = 0
        zero = n
        self.backtracking(0, building, count, zero)
        retVal = self.answer

        return retVal
```

</details>

## [2305. Fair Distribution of Cookies](https://leetcode.com/problems/fair-distribution-of-cookies/)  1886

- [Official](https://leetcode.com/problems/fair-distribution-of-cookies/editorial/)

<details><summary>Description</summary>

```text
You are given an integer array cookies, where cookies[i] denotes the number of cookies in the ith bag.
You are also given an integer k that denotes the number of children to distribute all the bags of cookies to.
All the cookies in the same bag must go to the same child and cannot be split up.

The unfairness of a distribution is defined as the maximum total cookies obtained by a single child in the distribution.

Return the minimum unfairness of all distributions.

Example 1:
Input: cookies = [8,15,10,20,8], k = 2
Output: 31
Explanation: One optimal distribution is [8,15,8] and [10,20]
- The 1st child receives [8,15,8] which has a total of 8 + 15 + 8 = 31 cookies.
- The 2nd child receives [10,20] which has a total of 10 + 20 = 30 cookies.
The unfairness of the distribution is max(31,30) = 31.
It can be shown that there is no distribution with an unfairness less than 31.

Example 2:
Input: cookies = [6,1,3,2,2,4,1,2], k = 3
Output: 7
Explanation: One optimal distribution is [6,1], [3,2,2], and [4,1,2]
- The 1st child receives [6,1] which has a total of 6 + 1 = 7 cookies.
- The 2nd child receives [3,2,2] which has a total of 3 + 2 + 2 = 7 cookies.
- The 3rd child receives [4,1,2] which has a total of 4 + 1 + 2 = 7 cookies.
The unfairness of the distribution is max(7,7,7) = 7.
It can be shown that there is no distribution with an unfairness less than 7.

Constraints:
2 <= cookies.length <= 8
1 <= cookies[i] <= 10^5
2 <= k <= cookies.length
```

<details><summary>Hint</summary>

```text
1. We have to give each bag to one of the children. How can we enumerate all of the possibilities?
2. Use recursion and keep track of the current number of cookies each child has.
   Once all the bags have been distributed, find the child with the most cookies.
```

</details>

</details>

<details><summary>C</summary>

```c
int backtracking(int i, int* distribute, int distributeSize, int* cookies, int cookiesSize, int k, int zeroCount) {
    int retVal = INT_MAX;

    if (cookiesSize - i < zeroCount) {
        return retVal;
    }

    int idx;
    if (i == cookiesSize) {
        retVal = distribute[0];
        for (idx = 1; idx < distributeSize; ++idx) {
            retVal = fmax(retVal, distribute[idx]);
        }

        return retVal;
    }

    int j;
    for (j = 0; j < k; ++j) {
        if (distribute[j] == 0) {
            zeroCount -= 1;
        }
        distribute[j] += cookies[i];

        retVal = fmin(retVal, backtracking(i + 1, distribute, distributeSize, cookies, cookiesSize, k, zeroCount));

        distribute[j] -= cookies[i];
        if (distribute[j] == 0) {
            zeroCount += 1;
        }
    }

    return retVal;
}
int distributeCookies(int* cookies, int cookiesSize, int k) {
    int retVal = 0;

    int distributeSize = k;
    int distribute[distributeSize];
    memset(distribute, 0, sizeof(distribute));
    retVal = backtracking(0, distribute, distributeSize, cookies, cookiesSize, k, k);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int backtracking(int i, vector<int>& distribute, vector<int>& cookies, int k, int zeroCount) {
        int retVal = numeric_limits<int>::max();

        int cookiesSize = cookies.size();
        if (cookiesSize - i < zeroCount) {
            return retVal;
        }

        if (i == cookiesSize) {
            retVal = *max_element(distribute.begin(), distribute.end());
            return retVal;
        }

        for (int j = 0; j < k; ++j) {
            if (distribute[j] == 0) {
                zeroCount -= 1;
            }
            distribute[j] += cookies[i];

            retVal = min(retVal, backtracking(i + 1, distribute, cookies, k, zeroCount));

            distribute[j] -= cookies[i];
            if (distribute[j] == 0) {
                zeroCount += 1;
            }
        }

        return retVal;
    }
    int distributeCookies(vector<int>& cookies, int k) {
        int retVal = 0;

        vector<int> distribute(k, 0);
        retVal = backtracking(0, distribute, cookies, k, k);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def backtracking(self, i, distribute: List[int], cookies: List[int], k: int, zeroCount) -> int:
        retVal = float('inf')

        cookiesSize = len(cookies)

        if cookiesSize - i < zeroCount:
            return retVal

        if i == cookiesSize:
            retVal = max(distribute)
            return retVal

        for j in range(k):
            zeroCount -= int(distribute[j] == 0)
            distribute[j] += cookies[i]
            retVal = min(retVal, self.backtracking(i + 1, distribute, cookies, k, zeroCount))

            distribute[j] -= cookies[i]
            zeroCount += int(distribute[j] == 0)

        return retVal

    def distributeCookies(self, cookies: List[int], k: int) -> int:
        retVal = 0

        distribute = [0] * k
        retVal = self.backtracking(0, distribute, cookies, k, k)

        return retVal
```

</details>
