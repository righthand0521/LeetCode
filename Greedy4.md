# Greedy

## [3014. Minimum Number of Pushes to Type Word I](https://leetcode.com/problems/minimum-number-of-pushes-to-type-word-i/)  1324

<details><summary>Description</summary>

```text
You are given a string word containing distinct lowercase English letters.

Telephone keypads have keys mapped with distinct collections of lowercase English letters,
which can be used to form words by pushing them.
For example, the key 2 is mapped with ["a","b","c"], we need to push the key one time to type "a",
two times to type "b", and three times to type "c" .

It is allowed to remap the keys numbered 2 to 9 to distinct collections of letters.
The keys can be remapped to any amount of letters, but each letter must be mapped to exactly one key.
You need to find the minimum number of times the keys will be pushed to type the string word.

Return the minimum number of pushes needed to type word after remapping the keys.

An example mapping of letters to keys on a telephone keypad is given below.
Note that 1, *, #, and 0 do not map to any letters.

Example 1:
Input: word = "abcde"
Output: 5
Explanation: The remapped keypad given in the image provides the minimum cost.
"a" -> one push on key 2
"b" -> one push on key 3
"c" -> one push on key 4
"d" -> one push on key 5
"e" -> one push on key 6
Total cost is 1 + 1 + 1 + 1 + 1 = 5.
It can be shown that no other mapping can provide a lower cost.

Example 2:
Input: word = "xycdefghij"
Output: 12
Explanation: The remapped keypad given in the image provides the minimum cost.
"x" -> one push on key 2
"y" -> two pushes on key 2
"c" -> one push on key 3
"d" -> two pushes on key 3
"e" -> one push on key 4
"f" -> one push on key 5
"g" -> one push on key 6
"h" -> one push on key 7
"i" -> one push on key 8
"j" -> one push on key 9
Total cost is 1 + 2 + 1 + 2 + 1 + 1 + 1 + 1 + 1 + 1 = 12.
It can be shown that no other mapping can provide a lower cost.

Constraints:
1 <= word.length <= 26
word consists of lowercase English letters.
All letters in word are distinct.
```

<details><summary>Hint</summary>

```text
1. We have 8 keys in total.
   We can type 8 characters with one push each, 8 different characters with two pushes each, and so on.
2. The optimal way is to map letters to keys evenly.
```

</details>

</details>

<details><summary>C</summary>

```c
int minimumPushes(char* word) {
    int retVal = 0;

    int wordSize = strlen(word);
    int quotient = wordSize / 8;
    int remainder = wordSize % 8;
    retVal = ((quotient << 2) + remainder) * (quotient + 1);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minimumPushes(string word) {
        int retVal = 0;

        int wordSize = word.size();
        int quotient = wordSize / 8;
        int remainder = wordSize % 8;
        retVal = ((quotient << 2) + remainder) * (quotient + 1);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minimumPushes(self, word: str) -> int:
        retVal = 0

        wordSize = len(word)
        quotient, remainder = divmod(wordSize, 8)
        retVal = ((quotient << 2) + remainder) * (quotient + 1)

        return retVal
```

</details>

## [3016. Minimum Number of Pushes to Type Word II](https://leetcode.com/problems/minimum-number-of-pushes-to-type-word-ii/)  1533

- [Official](https://leetcode.com/problems/minimum-number-of-pushes-to-type-word-ii/editorial/)

<details><summary>Description</summary>

```text
You are given a string word containing lowercase English letters.

Telephone keypads have keys mapped with distinct collections of lowercase English letters,
which can be used to form words by pushing them.
For example, the key 2 is mapped with ["a","b","c"], we need to push the key one time to type "a",
two times to type "b", and three times to type "c" .

It is allowed to remap the keys numbered 2 to 9 to distinct collections of letters.
The keys can be remapped to any amount of letters, but each letter must be mapped to exactly one key.
You need to find the minimum number of times the keys will be pushed to type the string word.

Return the minimum number of pushes needed to type word after remapping the keys.

An example mapping of letters to keys on a telephone keypad is given below.
Note that 1, *, #, and 0 do not map to any letters.

Example 1:
Input: word = "abcde"
Output: 5
Explanation: The remapped keypad given in the image provides the minimum cost.
"a" -> one push on key 2
"b" -> one push on key 3
"c" -> one push on key 4
"d" -> one push on key 5
"e" -> one push on key 6
Total cost is 1 + 1 + 1 + 1 + 1 = 5.
It can be shown that no other mapping can provide a lower cost.

Example 2:
Input: word = "xyzxyzxyzxyz"
Output: 12
Explanation: The remapped keypad given in the image provides the minimum cost.
"x" -> one push on key 2
"y" -> one push on key 3
"z" -> one push on key 4
Total cost is 1 * 4 + 1 * 4 + 1 * 4 = 12
It can be shown that no other mapping can provide a lower cost.
Note that the key 9 is not mapped to any letter:
it is not necessary to map letters to every key, but to map all the letters.

Example 3:
Input: word = "aabbccddeeffgghhiiiiii"
Output: 24
Explanation: The remapped keypad given in the image provides the minimum cost.
"a" -> one push on key 2
"b" -> one push on key 3
"c" -> one push on key 4
"d" -> one push on key 5
"e" -> one push on key 6
"f" -> one push on key 7
"g" -> one push on key 8
"h" -> two pushes on key 9
"i" -> one push on key 9
Total cost is 1 * 2 + 1 * 2 + 1 * 2 + 1 * 2 + 1 * 2 + 1 * 2 + 1 * 2 + 2 * 2 + 6 * 1 = 24.
It can be shown that no other mapping can provide a lower cost.

Constraints:
1 <= word.length <= 10^5
word consists of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. We have 8 keys in total.
   We can type 8 characters with one push each, 8 different characters with two pushes each, and so on.
2. The optimal way is to map letters to keys evenly.
3. Sort the letters by frequencies in the word in non-increasing order.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MAX_LETTERS (26)  // word consists of lowercase English letters.
int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
int minimumPushes(char* word) {
    int retVal = 0;

    int frequency[MAX_LETTERS];
    memset(frequency, 0, sizeof(frequency));

    int wordSize = strlen(word);
    int i;
    for (i = 0; i < wordSize; ++i) {
        ++frequency[word[i] - 'a'];
    }
    qsort(frequency, MAX_LETTERS, sizeof(int), compareInteger);

    for (i = 0; i < MAX_LETTERS; ++i) {
        if (frequency[i] == 0) {
            break;
        }
        retVal += (i / 8 + 1) * frequency[i];
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    int letters = 26;  // word consists of lowercase English letters.

   public:
    int minimumPushes(string word) {
        int retVal = 0;

        vector<int> frequency(letters, 0);
        for (char& c : word) {
            ++frequency[c - 'a'];
        }
        sort(frequency.rbegin(), frequency.rend());

        for (int i = 0; i < letters; ++i) {
            if (frequency[i] == 0) {
                break;
            }
            retVal += (i / 8 + 1) * frequency[i];
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
        self.letters = 26   # word consists of lowercase English letters.

    def minimumPushes(self, word: str) -> int:
        retVal = 0

        frequency = [0] * self.letters
        for c in word:
            frequency[ord(c) - ord("a")] += 1
        frequency.sort(reverse=True)

        for i in range(self.letters):
            if frequency[i] == 0:
                break
            retVal += (i // 8 + 1) * frequency[i]

        return retVal
```

</details>

## [3068. Find the Maximum Sum of Node Values](https://leetcode.com/problems/find-the-maximum-sum-of-node-values/)  2267

- [Official](https://leetcode.com/problems/find-the-maximum-sum-of-node-values/editorial/)

<details><summary>Description</summary>

```text
There exists an undirected tree with n nodes numbered 0 to n - 1.
You are given a 0-indexed 2D integer array edges of length n - 1,
where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the tree.
You are also given a positive integer k, and a 0-indexed array of non-negative integers nums of length n,
where nums[i] represents the value of the node numbered i.

Alice wants the sum of values of tree nodes to be maximum,
for which Alice can perform the following operation any number of times (including zero) on the tree:
- Choose any edge [u, v] connecting the nodes u and v, and update their values as follows:
  - nums[u] = nums[u] XOR k
  - nums[v] = nums[v] XOR k

Return the maximum possible sum of the values Alice can achieve by performing the operation any number of times.

Example 1:
Input: nums = [1,2,1], k = 3, edges = [[0,1],[0,2]]
Output: 6
Explanation: Alice can achieve the maximum sum of 6 using a single operation:
- Choose the edge [0,2]. nums[0] and nums[2] become: 1 XOR 3 = 2, and the array nums becomes: [1,2,1] -> [2,2,2].
The total sum of values is 2 + 2 + 2 = 6.
It can be shown that 6 is the maximum achievable sum of values.

Example 2:
Input: nums = [2,3], k = 7, edges = [[0,1]]
Output: 9
Explanation: Alice can achieve the maximum sum of 9 using a single operation:
- Choose the edge [0,1]. nums[0] becomes: 2 XOR 7 = 5 and nums[1] become: 3 XOR 7 = 4,
  and the array nums becomes: [2,3] -> [5,4].
The total sum of values is 5 + 4 = 9.
It can be shown that 9 is the maximum achievable sum of values.

Example 3:
Input: nums = [7,7,7,7,7,7], k = 3, edges = [[0,1],[0,2],[0,3],[0,4],[0,5]]
Output: 42
Explanation: The maximum achievable sum is 42 which can be achieved by Alice performing no operations.

Constraints:
2 <= n == nums.length <= 2 * 10^4
1 <= k <= 10^9
0 <= nums[i] <= 10^9
edges.length == n - 1
edges[i].length == 2
0 <= edges[i][0], edges[i][1] <= n - 1
The input is generated such that edges represent a valid tree.
```

<details><summary>Hint</summary>

```text
1. Select any node as the root.
2. Let dp[x][c] be the maximum sum we can get for the subtree rooted at node x,
   where c is a boolean representing whether the edge between node x and its parent (if any) is selected or not.
3. dp[x][c] = max(sum(dp[y][cy]) + v(nums[x], sum(cy) + c)) where cy is 0 or 1.
   When sum(cy) + c is odd, v(nums[x], sum(cy) + c) = nums[x] XOR k.
   When sum(cy) + c is even, v(nums[x], sum(cy) + c) = nums[x].
4. There’s also an easier solution - does the parity of the number of elements where nums[i] XOR k > nums[i] help?
```

</details>

</details>

<details><summary>C</summary>

```c
long long maximumValueSum(int* nums, int numsSize, int k, int** edges, int edgesSize, int* edgesColSize) {
    long long retVal = 0;

    long long sum = 0;
    int count = 0;
    int positiveMinimum = (1 << 30);
    int negativeMaximum = -1 * (1 << 30);
    int operatedNodeValue, netChange;
    int i;
    for (i = 0; i < numsSize; ++i) {
        operatedNodeValue = nums[i] ^ k;
        sum += nums[i];
        netChange = operatedNodeValue - nums[i];
        if (netChange > 0) {
            positiveMinimum = fmin(positiveMinimum, netChange);
            sum += netChange;
            count++;
        } else {
            negativeMaximum = fmax(negativeMaximum, netChange);
        }
    }

    // If the number of positive netChange values is even return the sum.
    // Otherwise return the maximum of both discussed cases.
    if (count % 2 == 0) {
        retVal = sum;
    } else {
        retVal = fmax(sum - positiveMinimum, sum + negativeMaximum);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long maximumValueSum(vector<int>& nums, int k, vector<vector<int>>& edges) {
        long long retVal = 0;

        long long sum = 0;
        int count = 0;
        int positiveMinimum = (1 << 30);
        int negativeMaximum = -1 * (1 << 30);
        for (int nodeValue : nums) {
            int operatedNodeValue = nodeValue ^ k;
            sum += nodeValue;
            int netChange = operatedNodeValue - nodeValue;
            if (netChange > 0) {
                positiveMinimum = min(positiveMinimum, netChange);
                sum += netChange;
                count++;
            } else {
                negativeMaximum = max(negativeMaximum, netChange);
            }
        }

        // If the number of positive netChange values is even return the sum.
        // Otherwise return the maximum of both discussed cases.
        if (count % 2 == 0) {
            retVal = sum;
        } else {
            retVal = max(sum - positiveMinimum, sum + negativeMaximum);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
    def maximumValueSum(self, nums: List[int], k: int, edges: List[List[int]]) -> int:
        retVal = 0

        sumVal = 0
        count = 0
        positiveMinimum = 1 << 30
        negativeMaximum = -1 * (1 << 30)
        for nodeValue in nums:
            operatedNodeValue = nodeValue ^ k
            sumVal += nodeValue
            netChange = operatedNodeValue - nodeValue
            if netChange > 0:
                positiveMinimum = min(positiveMinimum, netChange)
                sumVal += netChange
                count += 1
            else:
                negativeMaximum = max(negativeMaximum, netChange)

        # If the number of positive netChange values is even, return the sum.
        # Otherwise return the maximum of both discussed cases.
        if count % 2 == 0:
            retVal = sumVal
        else:
            retVal = max(sumVal - positiveMinimum, sumVal + negativeMaximum)

        return retVal
```

</details>

## [3075. Maximize Happiness of Selected Children](https://leetcode.com/problems/maximize-happiness-of-selected-children/)  1325

- [Official](https://leetcode.com/problems/maximize-happiness-of-selected-children/editorial/)

<details><summary>Description</summary>

```text
You are given an array happiness of length n, and a positive integer k.

There are n children standing in a queue, where the ith child has happiness value happiness[i].
You want to select k children from these n children in k turns.

In each turn, when you select a child,
the happiness value of all the children that have not been selected till now decreases by 1.
Note that the happiness value cannot become negative and gets decremented only if it is positive.

Return the maximum sum of the happiness values of the selected children you can achieve by selecting k children.

Example 1:
Input: happiness = [1,2,3], k = 2
Output: 4
Explanation: We can pick 2 children in the following way:
- Pick the child with the happiness value == 3. The happiness value of the remaining children becomes [0,1].
- Pick the child with the happiness value == 1. The happiness value of the remaining child becomes [0].
  Note that the happiness value cannot become less than 0.
The sum of the happiness values of the selected children is 3 + 1 = 4.

Example 2:
Input: happiness = [1,1,1,1], k = 2
Output: 1
Explanation: We can pick 2 children in the following way:
- Pick any child with the happiness value == 1. The happiness value of the remaining children becomes [0,0,0].
- Pick the child with the happiness value == 0. The happiness value of the remaining child becomes [0,0].
The sum of the happiness values of the selected children is 1 + 0 = 1.

Example 3:
Input: happiness = [2,3,4,5], k = 1
Output: 5
Explanation: We can pick 1 child in the following way:
- Pick the child with the happiness value == 5. The happiness value of the remaining children becomes [1,2,3].
The sum of the happiness values of the selected children is 5.

Constraints:
1 <= n == happiness.length <= 2 * 10^5
1 <= happiness[i] <= 10^8
1 <= k <= n
```

<details><summary>Hint</summary>

```text
1. Since all the unselected numbers are decreasing at the same rate, we should greedily select k largest values.
2. The ith largest number (i = 1, 2, 3,…k) should decrease by (i - 1) when it is picked.
3. Add 0 if the decreased value is negative.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
long long maximumHappinessSum(int* happiness, int happinessSize, int k) {
    long long retVal = 0;

    qsort(happiness, happinessSize, sizeof(int), compareInteger);
    int happy;
    int i;
    for (i = 0; i < k; ++i) {
        happy = happiness[i] - i;
        if (happy <= 0) {
            break;
        }
        retVal += happy;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long maximumHappinessSum(vector<int>& happiness, int k) {
        long long retVal = 0;

        sort(happiness.begin(), happiness.end(), greater<int>());
        for (int i = 0; i < k; ++i) {
            int happy = happiness[i] - i;
            if (happy <= 0) {
                break;
            }
            retVal += happy;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maximumHappinessSum(self, happiness: List[int], k: int) -> int:
        retVal = 0

        happiness.sort(reverse=True)
        for i in range(k):
            happy = happiness[i] - i
            if happy <= 0:
                break
            retVal += happy

        return retVal
```

</details>

## [3170. Lexicographically Minimum String After Removing Stars](https://leetcode.com/problems/lexicographically-minimum-string-after-removing-stars/)  1772

- [Official](https://leetcode.com/problems/lexicographically-minimum-string-after-removing-stars/editorial/)
- [Official](https://leetcode.cn/problems/lexicographically-minimum-string-after-removing-stars/solutions/3687879/shan-chu-xing-hao-yi-hou-zi-dian-xu-zui-u847n/)

<details><summary>Description</summary>

```text
You are given a string s. It may contain any number of '*' characters. Your task is to remove all '*' characters.

While there is a '*', do the following operation:
- Delete the leftmost '*' and the smallest non-'*' character to its left.
  If there are several smallest characters, you can delete any of them.

Return the lexicographically smallest resulting string after removing all '*' characters.

Example 1:
Input: s = "aaba*"
Output: "aab"
Explanation:
We should delete one of the 'a' characters with '*'. If we choose s[3], s becomes the lexicographically smallest.

Example 2:
Input: s = "abc"
Output: "abc"
Explanation:
There is no '*' in the string.

Constraints:
1 <= s.length <= 10^5
s consists only of lowercase English letters and '*'.
The input is generated such that it is possible to delete all '*' characters.
```

</details>

<details><summary>C</summary>

```c
#define MAX_LETTERS (26)  // s consists only of lowercase English letters and '*'.
typedef struct {
    int* data;
    int size;
    int capacity;
} Stack;
Stack* createStack(int capacity) {
    Stack* pObj = NULL;

    pObj = (Stack*)malloc(sizeof(Stack));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->data = (int*)malloc(capacity * sizeof(int));
    if (pObj->data == NULL) {
        perror("malloc");
        free(pObj);
        pObj = NULL;
        return pObj;
    }
    pObj->size = 0;
    pObj->capacity = capacity;

    return pObj;
}
void push(Stack* stack, int value) {
    if (stack->size < stack->capacity) {
        stack->data[stack->size++] = value;
    }
}
int pop(Stack* stack) {
    int retVal = -1;

    if (stack->size > 0) {
        retVal = stack->data[--stack->size];
    }

    return retVal;
}
int isEmpty(Stack* stack) {
    int retVal = (stack->size == 0);

    return retVal;
}
void freeStack(Stack* stack) {
    free(stack->data);
    stack->data = NULL;
    free(stack);
    stack = NULL;
}
char* clearStars(char* s) {
    char* pRetVal = NULL;

    int sSize = strlen(s);

    Stack* lettersStack[MAX_LETTERS];
    for (int i = 0; i < MAX_LETTERS; i++) {
        lettersStack[i] = createStack(sSize);
        if (lettersStack[i] == NULL) {
            perror("createStack");
            for (int j = 0; j < i; j++) {
                freeStack(lettersStack[j]);
            }
            return pRetVal;
        }
    }
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] != '*') {
            push(lettersStack[s[i] - 'a'], i);
            continue;
        }
        for (int j = 0; j < MAX_LETTERS; j++) {
            if (isEmpty(lettersStack[j]) == 0) {
                s[pop(lettersStack[j])] = '*';
                break;
            }
        }
    }

    int returnSize = 0;
    pRetVal = calloc(sSize + 1, sizeof(char));
    if (pRetVal != NULL) {
        for (int i = 0; i < sSize; i++) {
            if (s[i] != '*') {
                pRetVal[returnSize++] = s[i];
            }
        }
    } else {
        perror("calloc");
    }

    // Free the stacks
    for (int i = 0; i < MAX_LETTERS; i++) {
        freeStack(lettersStack[i]);
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    const int letters = 26;  // s consists only of lowercase English letters and '*'.

   public:
    string clearStars(string s) {
        string retVal = "";

        vector<stack<int>> lettersStack(letters);
        int sSize = s.size();
        for (int i = 0; i < sSize; i++) {
            if (s[i] != '*') {
                lettersStack[s[i] - 'a'].push(i);
                continue;
            }
            for (int j = 0; j < letters; j++) {
                if (lettersStack[j].empty() == false) {
                    s[lettersStack[j].top()] = '*';
                    lettersStack[j].pop();
                    break;
                }
            }
        }

        for (int i = 0; i < sSize; i++) {
            if (s[i] != '*') {
                retVal += s[i];
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
        self.letters = 26  # s consists only of lowercase English letters and '*'.

    def clearStars(self, s: str) -> str:
        retVal = ""

        lettersStack = [[] for _ in range(self.letters)]
        sArray = list(s)
        for i, c in enumerate(sArray):
            if c != "*":
                lettersStack[ord(c) - ord("a")].append(i)
                continue
            for j in range(self.letters):
                if lettersStack[j]:
                    sArray[lettersStack[j].pop()] = "*"
                    break
        retVal = "".join(c for c in sArray if c != "*")

        return retVal
```

</details>
