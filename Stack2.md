# [Stack](https://en.wikipedia.org/wiki/Stack_(abstract_data_type))

- Monotonic Stack

## [1047. Remove All Adjacent Duplicates In String](https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/)  1286

- [Official](https://leetcode.cn/problems/remove-all-adjacent-duplicates-in-string/solutions/643955/shan-chu-zi-fu-chuan-zhong-de-suo-you-xi-4ohr/)

<details><summary>Description</summary>

```text
You are given a string s consisting of lowercase English letters.
A duplicate removal consists of choosing two adjacent and equal letters and removing them.

We repeatedly make duplicate removals on s until we no longer can.

Return the final string after all such duplicate removals have been made.
It can be proven that the answer is unique.

Example 1:
Input: s = "abbaca"
Output: "ca"
Explanation:
For example, in "abbaca" we could remove "bb" since the letters are adjacent and equal, and this is the only possible move.
The result of this move is that the string is "aaca", of which only "aa" is possible, so the final string is "ca".

Example 2:
Input: s = "azxxzy"
Output: "ay"

Constraints:
1 <= s.length <= 10^5
s consists of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Use a stack to process everything greedily.
```

</details>

</details>

<details><summary>C</summary>

```c
char* removeDuplicates(char* s) {
    char* pRetVal = NULL;

    int sSize = strlen(s);
    pRetVal = (char*)calloc(sSize + 1, sizeof(char));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }
    int stackHead = 0;

    int i;
    for (i = 0; i < sSize; ++i) {
        if (stackHead == 0) {
            pRetVal[stackHead++] = s[i];
            continue;
        }

        if (pRetVal[stackHead - 1] == s[i]) {
            pRetVal[--stackHead] = 0;
        } else {
            pRetVal[stackHead++] = s[i];
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
    string removeDuplicates(string s) {
        string retVal;

        for (char c : s) {
            if (retVal.empty() == true) {
                retVal.push_back(c);
                continue;
            }

            if (retVal.back() == c) {
                retVal.pop_back();
            } else {
                retVal.push_back(c);
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
    def removeDuplicates(self, s: str) -> str:
        retVal = ""

        stack = []
        for c in s:
            if not stack:
                stack.append(c)
                continue

            if stack[-1] == c:
                stack.pop()
            else:
                stack.append(c)
        retVal = "".join(stack)

        return retVal
```

</details>

## [1081. Smallest Subsequence of Distinct Characters](https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/)  2184

- [Official](https://leetcode.cn/problems/smallest-subsequence-of-distinct-characters/solutions/528066/bu-tong-zi-fu-de-zui-xiao-zi-xu-lie-by-l-5qyk/)

<details><summary>Description</summary>

```text
Given a string s, return the lexicographically smallest subsequence of s
that contains all the distinct characters of s exactly once.

Example 1:
Input: s = "bcabc"
Output: "abc"

Example 2:
Input: s = "cbacdcbc"
Output: "acdb"

Constraints:
1 <= s.length <= 1000
s consists of lowercase English letters.

Note: This question is the same as 316: https://leetcode.com/problems/remove-duplicate-letters/
```

<details><summary>Hint</summary>

```text
1. Greedily try to add one missing character.
   How to check if adding some character will not cause problems?
   Use bit-masks to check whether you will be able to complete the sub-sequence
   if you add the character at some index i.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MAX_LETTERS (26)  // s consists of lowercase English letters.
char *smallestSubsequence(char *s) {
    char *pRetVal = NULL;

    //
    pRetVal = (char *)malloc((MAX_LETTERS + 1) * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloe");
        return pRetVal;
    }
    memset(pRetVal, 0, ((MAX_LETTERS + 1) * sizeof(char)));
    int returnSize = 0;

    //
    int sSize = strlen(s);
    int i;
    int appears[MAX_LETTERS];
    memset(appears, 0, sizeof(appears));
    for (i = 0; i < sSize; ++i) {
        appears[s[i] - 'a']++;
    }
    int visit[MAX_LETTERS];
    memset(visit, 0, sizeof(visit));

    //
    int idx;
    for (i = 0; i < sSize; ++i) {
        idx = s[i] - 'a';

        if (visit[idx] == 0) {
            while ((returnSize > 0) && (pRetVal[returnSize - 1] > s[i])) {
                if (appears[pRetVal[returnSize - 1] - 'a'] > 0) {
                    visit[pRetVal[returnSize - 1] - 'a'] = 0;
                    returnSize -= 1;
                } else {
                    break;
                }
            }
            visit[idx] = 1;
            pRetVal[returnSize] = s[i];
            returnSize += 1;
        }
        appears[idx] -= 1;
    }
    pRetVal[returnSize] = '\0';

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string removeDuplicateLetters(string s) {
        string retVal;

#define MAX_LETTERS (26)  // s consists of lowercase English letters.
        vector<int> appears(MAX_LETTERS, 0);
        for (char ch : s) {
            appears[ch - 'a']++;
        }

        vector<int> visit(MAX_LETTERS, 0);
        for (char ch : s) {
            int idx = ch - 'a';

            if (visit[idx] == 0) {
                while ((retVal.empty() == false) && (retVal.back() > ch)) {
                    if (appears[retVal.back() - 'a'] > 0) {
                        visit[retVal.back() - 'a'] = 0;
                        retVal.pop_back();
                    } else {
                        break;
                    }
                }
                visit[idx] = 1;
                retVal.push_back(ch);
            }

            appears[idx] -= 1;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def smallestSubsequence(self, s: str) -> str:
        retVal = s

        stack = []
        visit = set()
        appears = Counter(s)
        for c in s:
            if c not in visit:
                while stack and c < stack[-1] and appears[stack[-1]] > 0:
                    visit.discard(stack.pop())
                visit.add(c)
                stack.append(c)
            appears[c] -= 1
        retVal = ''.join(stack)

        return retVal
```

</details>

## [1106. Parsing A Boolean Expression](https://leetcode.com/problems/parsing-a-boolean-expression/)  1880

- [Official](https://leetcode.com/problems/parsing-a-boolean-expression/editorial/)
- [Official](https://leetcode.cn/problems/parsing-a-boolean-expression/solutions/1948172/jie-xi-bu-er-biao-da-shi-by-leetcode-sol-vmvg/)

<details><summary>Description</summary>

```text
A boolean expression is an expression that evaluates to either true or false. It can be in one of the following shapes:
- 't' that evaluates to true.
- 'f' that evaluates to false.
- '!(subExpr)' that evaluates to the logical NOT of the inner expression subExpr.
- '&(subExpr1, subExpr2, ..., subExprn)' that evaluates to the logical AND of
  the inner expressions subExpr1, subExpr2, ..., subExprn where n >= 1.
- '|(subExpr1, subExpr2, ..., subExprn)' that evaluates to the logical OR of
  the inner expressions subExpr1, subExpr2, ..., subExprn where n >= 1.

Given a string expression that represents a boolean expression, return the evaluation of that expression.

It is guaranteed that the given expression is valid and follows the given rules.

Example 1:
Input: expression = "&(|(f))"
Output: false
Explanation:
First, evaluate |(f) --> f. The expression is now "&(f)".
Then, evaluate &(f) --> f. The expression is now "f".
Finally, return false.

Example 2:
Input: expression = "|(f,f,f,t)"
Output: true
Explanation: The evaluation of (false OR false OR false OR true) is true.

Example 3:
Input: expression = "!(&(f,t))"
Output: true
Explanation:
First, evaluate &(f,t) --> (false AND true) --> false --> f. The expression is now "!(f)".
Then, evaluate !(f) --> NOT false --> true. We return true.

Constraints:
1 <= expression.length <= 2 * 10^4
expression[i] is one following characters: '(', ')', '&', '|', '!', 't', 'f', and ','.
```

<details><summary>Hint</summary>

```text
1. Write a function "parse" which calls helper functions "parse_or", "parse_and", "parse_not".
```

</details>

</details>

<details><summary>C</summary>

```c
bool parseBoolExpr(char* expression) {
    bool retVal = false;

    int expressionSize = strlen(expression);

    int stackTop = -1;
    char stack[expressionSize + 1];
    memset(stack, 0, sizeof(stack));

    bool hasTrue, hasFalse;
    char c, topValue, op;
    int i;
    for (i = 0; i < expressionSize; ++i) {
        c = expression[i];
        if ((c == ',') || (c == '(')) {
            continue;
        } else if ((c == 't') || (c == 'f') || (c == '!') || (c == '&') || (c == '|')) {
            stack[++stackTop] = c;
        } else if (c == ')') {
            hasTrue = false;
            hasFalse = false;
            while (stackTop >= 0) {
                if ((stack[stackTop] == '!') || (stack[stackTop] == '&') || (stack[stackTop] == '|')) {
                    break;
                }
                topValue = stack[stackTop--];
                if (topValue == 't') {
                    hasTrue = true;
                } else if (topValue == 'f') {
                    hasFalse = true;
                }
            }

            op = (stackTop >= 0) ? stack[stackTop--] : '0';
            if (op == '!') {
                stack[++stackTop] = (hasTrue == true) ? 'f' : 't';
            } else if (op == '&') {
                stack[++stackTop] = (hasFalse == true) ? 'f' : 't';
            } else {
                stack[++stackTop] = (hasTrue == true) ? 't' : 'f';
            }
        }
    }
    if ((stackTop >= 0) && (stack[stackTop] == 't')) {
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
    bool parseBoolExpr(string expression) {
        bool retVal = false;

        stack<char> st;
        for (char c : expression) {
            if (c == ',' || c == '(') {
                continue;
            } else if ((c == 't') || (c == 'f') || (c == '!') || (c == '&') || (c == '|')) {
                st.push(c);
            } else if (c == ')') {
                bool hasTrue = false;
                bool hasFalse = false;
                while ((st.top() != '!') && (st.top() != '&') && (st.top() != '|')) {
                    char topValue = st.top();
                    st.pop();
                    if (topValue == 't') {
                        hasTrue = true;
                    } else if (topValue == 'f') {
                        hasFalse = true;
                    }
                }

                char op = st.top();
                st.pop();
                if (op == '!') {
                    st.push((hasTrue == true) ? 'f' : 't');
                } else if (op == '&') {
                    st.push((hasFalse == true) ? 'f' : 't');
                } else {
                    st.push((hasTrue == true) ? 't' : 'f');
                }
            }
        }
        if (st.top() == 't') {
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
    def parseBoolExpr(self, expression: str) -> bool:
        retVal = False

        stack = deque()
        for c in expression:
            if c == "," or c == "(":
                continue
            elif c in ["t", "f", "!", "&", "|"]:
                stack.append(c)
            elif c == ")":
                hasTrue = False
                hasFalse = False
                while stack[-1] not in ["!", "&", "|"]:
                    topValue = stack.pop()
                    if topValue == "t":
                        hasTrue = True
                    elif topValue == "f":
                        hasFalse = True

                op = stack.pop()
                if op == "!":
                    stack.append("f" if (hasTrue == True) else "t")
                elif op == "&":
                    stack.append("f" if (hasFalse == True) else "t")
                else:
                    stack.append("t" if (hasTrue == True) else "f")

        if stack[-1] == "t":
            retVal = True

        return retVal
```

</details>

## [1124. Longest Well-Performing Interval](https://leetcode.com/problems/longest-well-performing-interval/)  1908

- [Official](https://leetcode.cn/problems/longest-well-performing-interval/solutions/2109622/biao-xian-liang-hao-de-zui-chang-shi-jia-rlij/)

<details><summary>Description</summary>

```text
We are given hours, a list of the number of hours worked per day for a given employee.

A day is considered to be a tiring day if and only if the number of hours worked is (strictly) greater than 8.

A well-performing interval is an interval of days
for which the number of tiring days is strictly larger than the number of non-tiring days.

Return the length of the longest well-performing interval.

Example 1:
Input: hours = [9,9,6,0,6,6,9]
Output: 3
Explanation: The longest well-performing interval is [9,9,6].

Example 2:
Input: hours = [6,6,6]
Output: 0

Constraints:
1 <= hours.length <= 10^4
0 <= hours[i] <= 16
```

<details><summary>Hint</summary>

```text
1. Make a new array A of +1/-1s corresponding to if hours[i] is > 8 or not.
   The goal is to find the longest subarray with positive sum.
2. Using prefix sums (PrefixSum[i+1] = A[0] + A[1] + ... + A[i]),
   you need to find for each j, the smallest i < j with PrefixSum[i] + 1 == PrefixSum[j].
```

</details>

</details>

<details><summary>C</summary>

```c
int longestWPI(int* hours, int hoursSize) {
    int retVal = 0;

    int i;

    int prefixSum[hoursSize + 1];
    memset(prefixSum, 0, sizeof(prefixSum));
    int monotonicStack[hoursSize + 1];
    memset(monotonicStack, 0, sizeof(monotonicStack));
    int monotonicStackTop = 0;

    monotonicStack[monotonicStackTop++] = 0;
    prefixSum[0] = 0;
    for (i = 1; i <= hoursSize; ++i) {
        prefixSum[i] = prefixSum[i - 1] + (hours[i - 1] > 8 ? 1 : -1);
        if (prefixSum[monotonicStack[monotonicStackTop - 1]] > prefixSum[i]) {
            monotonicStack[monotonicStackTop++] = i;
        }
    }

    for (i = hoursSize; i >= 1; --i) {
        while ((monotonicStackTop != 0) && (prefixSum[monotonicStack[monotonicStackTop - 1]] < prefixSum[i])) {
            retVal = fmax(retVal, i - monotonicStack[monotonicStackTop - 1]);
            --monotonicStackTop;
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
    int longestWPI(vector<int>& hours) {
        int retVal = 0;

        int hoursSize = hours.size();

        vector<int> prefixSum(hoursSize + 1, 0);
        stack<int> monotonicStack;
        monotonicStack.push(0);
        for (int i = 1; i <= hoursSize; ++i) {
            prefixSum[i] = prefixSum[i - 1] + (hours[i - 1] > 8 ? 1 : -1);
            if (prefixSum[monotonicStack.top()] > prefixSum[i]) {
                monotonicStack.push(i);
            }
        }

        for (int i = hoursSize; i >= 1; --i) {
            while ((monotonicStack.size()) && (prefixSum[monotonicStack.top()] < prefixSum[i])) {
                retVal = max(retVal, i - monotonicStack.top());
                monotonicStack.pop();
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
    def longestWPI(self, hours: List[int]) -> int:
        retVal = 0

        hoursSize = len(hours)

        prefixSum = [0] * (hoursSize + 1)
        monotonicStack = [0]
        for idx, hour in enumerate(hours, 1):
            prefixSum[idx] = prefixSum[idx - 1] + (1 if hour > 8 else -1)
            if prefixSum[idx] < prefixSum[monotonicStack[-1]]:
                monotonicStack.append(idx)

        for i in range(hoursSize, 0, -1):
            while monotonicStack and prefixSum[i] > prefixSum[monotonicStack[-1]]:
                retVal = max(retVal, i - monotonicStack.pop())

        return retVal
```

</details>

## [1190. Reverse Substrings Between Each Pair of Parentheses](https://leetcode.com/problems/reverse-substrings-between-each-pair-of-parentheses/)  1485

- [Official](https://leetcode.com/problems/reverse-substrings-between-each-pair-of-parentheses/editorial/)
- [Official](https://leetcode.cn/problems/reverse-substrings-between-each-pair-of-parentheses/solutions/795515/fan-zhuan-mei-dui-gua-hao-jian-de-zi-chu-gwpv/)

<details><summary>Description</summary>

```text
You are given a string s that consists of lower case English letters and brackets.

Reverse the strings in each pair of matching parentheses, starting from the innermost one.

Your result should not contain any brackets.

Example 1:
Input: s = "(abcd)"
Output: "dcba"

Example 2:
Input: s = "(u(love)i)"
Output: "iloveu"
Explanation: The substring "love" is reversed first, then the whole string is reversed.

Example 3:
Input: s = "(ed(et(oc))el)"
Output: "leetcode"
Explanation: First, we reverse the substring "oc", then "etco", and finally, the whole string.

Constraints:
1 <= s.length <= 2000
s only contains lower case English characters and parentheses.
It is guaranteed that all parentheses are balanced.
```

<details><summary>Hint</summary>

```text
1. Find all brackets in the string.
2. Does the order of the reverse matter ?
3. The order does not matter.
```

</details>

</details>

<details><summary>C</summary>

```c
char* reverseParentheses(char* s) {
    char* pRetVal = NULL;

    int sSize = strlen(s);

    int returnSize = sSize + 1;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));

    int pRetValTop = -1;
    int reverseStackTop;
    char reverseStack[returnSize];
    int i, j;
    for (i = 0; i < sSize; ++i) {
        if (s[i] == ')') {
            reverseStackTop = -1;
            memset(reverseStack, 0, sizeof(reverseStack));

            while ((pRetValTop > -1) && (pRetVal[pRetValTop] != '(')) {
                reverseStackTop++;
                reverseStack[reverseStackTop] = pRetVal[pRetValTop];
                pRetVal[pRetValTop] = '\0';
                pRetValTop--;
            }

            if (pRetValTop > -1) {
                pRetVal[pRetValTop] = '\0';
                pRetValTop--;
            }

            for (j = 0; j <= reverseStackTop; ++j) {
                pRetValTop++;
                pRetVal[pRetValTop] = reverseStack[j];
            }
        } else {
            pRetValTop++;
            pRetVal[pRetValTop] = s[i];
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
    string reverseParentheses(string s) {
        string retVal = "";

        vector<char> stack;
        for (char c : s) {
            if (c == ')') {
                vector<char> reverseStack;
                while (stack[stack.size() - 1] != '(') {
                    reverseStack.emplace_back(stack[stack.size() - 1]);
                    stack.erase(stack.end() - 1);
                }
                stack.erase(stack.end() - 1);
                stack.insert(stack.end(), reverseStack.begin(), reverseStack.end());
            } else {
                stack.emplace_back(c);
            }
        }
        for (char c : stack) {
            retVal += c;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def reverseParentheses(self, s: str) -> str:
        retVal = None

        stack = []
        for c in s:
            if c == ")":
                reverseStack = []
                while (stack[-1] != "("):
                    reverseStack.append(stack[-1])
                    stack.pop()
                stack.pop()
                stack += reverseStack
            else:
                stack.append(c)
        retVal = "".join(stack)

        return retVal
```

</details>

## [1249. Minimum Remove to Make Valid Parentheses](https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/)  1657

- [Official](https://leetcode.cn/problems/minimum-remove-to-make-valid-parentheses/solutions/99460/yi-chu-wu-xiao-gua-hao-by-leetcode/)

<details><summary>Description</summary>

```text
Given a string s of '(' , ')' and lowercase English characters.

Your task is to remove the minimum number of parentheses ( '(' or ')', in any positions )
so that the resulting parentheses string is valid and return any valid string.

Formally, a parentheses string is valid if and only if:
- It is the empty string, contains only lowercase characters, or
- It can be written as AB (A concatenated with B), where A and B are valid strings, or
- It can be written as (A), where A is a valid string.

Example 1:
Input: s = "lee(t(c)o)de)"
Output: "lee(t(c)o)de"
Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.

Example 2:
Input: s = "a)b(c)d"
Output: "ab(c)d"

Example 3:
Input: s = "))(("
Output: ""
Explanation: An empty string is also valid.

Constraints:
1 <= s.length <= 10^5
s[i] is either'(' , ')', or lowercase English letter.
```

<details><summary>Hint</summary>

```text
1. Each prefix of a balanced parentheses has a number of open parentheses greater or equal than closed parentheses,
   similar idea with each suffix.
2. Check the array from left to right, remove characters that do not meet the property mentioned above,
   same idea in backward way.
```

</details>

</details>

<details><summary>C</summary>

```c
char* minRemoveToMakeValid(char* s) {
    char* pRetVal = s;

    int sSize = strlen(s);

    int parenthesesRight[sSize];
    memset(parenthesesRight, 0, sizeof(parenthesesRight));
    int parenthesesStack[sSize];
    memset(parenthesesStack, 0, sizeof(parenthesesStack));
    int parenthesesStackTop = -1;

    int i, j;
    for (i = 0; i < sSize; ++i) {
        if (s[i] == '(') {
            parenthesesStack[i] = 1;
            parenthesesStackTop = i;
        } else if (s[i] == ')') {
            if (parenthesesStackTop == -1) {
                parenthesesRight[i] = 1;
                continue;
            }

            for (j = parenthesesStackTop; j >= 0; --j) {
                if (parenthesesStack[j] == 1) {
                    parenthesesStack[j] = 0;
                    parenthesesStackTop = j;
                    break;
                }
            }
            for (j = parenthesesStackTop; j >= 0; --j) {
                if (parenthesesStack[j] == 1) {
                    parenthesesStackTop = j;
                    break;
                }
            }
            if (j == -1) {
                parenthesesStackTop = j;
            }
        }
    }

    int idx = 0;
    for (i = 0; i < sSize; ++i) {
        if ((parenthesesRight[i] == 1) || (parenthesesStack[i] == 1)) {
            continue;
        }
        pRetVal[idx++] = s[i];
    }
    pRetVal[idx] = 0;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string minRemoveToMakeValid(string s) {
        string retVal;

        int sSize = s.size();

        vector<int> parenthesesRight;
        vector<int> parenthesesStack;
        for (int i = 0; i < sSize; ++i) {
            if (s[i] == '(') {
                parenthesesStack.push_back(i);
            } else if (s[i] == ')') {
                int parenthesesStackSize = parenthesesStack.size();
                if (parenthesesStackSize == 0) {
                    parenthesesRight.push_back(i);
                } else {
                    parenthesesStack.pop_back();
                }
            }
        }
        parenthesesStack.insert(parenthesesStack.end(), parenthesesRight.begin(), parenthesesRight.end());

        for (int i = 0; i < sSize; ++i) {
            if (find(parenthesesStack.begin(), parenthesesStack.end(), i) != parenthesesStack.end()) {
                continue;
            }
            retVal.push_back(s[i]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minRemoveToMakeValid(self, s: str) -> str:
        retVal = ""

        parenthesesRight = []
        parenthesesStack = []
        for idx, value in enumerate(s):
            if value == "(":
                parenthesesStack.append(idx)
            elif value == ")":
                if len(parenthesesStack) == 0:
                    parenthesesRight.append(idx)
                else:
                    parenthesesStack.pop()
        parenthesesStack = parenthesesStack + parenthesesRight

        for idx, value in enumerate(s):
            if idx in parenthesesStack:
                continue
            retVal += value

        return retVal
```

</details>

## [1381. Design a Stack With Increment Operation](https://leetcode.com/problems/design-a-stack-with-increment-operation/)  1285

- [Official](https://leetcode.com/problems/design-a-stack-with-increment-operation/editorial/)
- [Official](https://leetcode.cn/problems/design-a-stack-with-increment-operation/solutions/241895/she-ji-yi-ge-zhi-chi-zeng-liang-cao-zuo-de-zhan-by/)

<details><summary>Description</summary>

```text
Design a stack that supports increment operations on its elements.

Implement the CustomStack class:
- CustomStack(int maxSize)
  Initializes the object with maxSize which is the maximum number of elements in the stack.
- void push(int x)
  Adds x to the top of the stack if the stack has not reached the maxSize.
- int pop()
  Pops and returns the top of the stack or -1 if the stack is empty.
- void inc(int k, int val)
  Increments the bottom k elements of the stack by val.
  If there are less than k elements in the stack, increment all the elements in the stack.

Example 1:
Input
["CustomStack","push","push","pop","push","push","push","increment","increment","pop","pop","pop","pop"]
[[3],[1],[2],[],[2],[3],[4],[5,100],[2,100],[],[],[],[]]
Output
[null,null,null,2,null,null,null,null,null,103,202,201,-1]
Explanation
CustomStack stk = new CustomStack(3); // Stack is Empty []
stk.push(1);                          // stack becomes [1]
stk.push(2);                          // stack becomes [1, 2]
stk.pop();                            // return 2 --> Return top of the stack 2, stack becomes [1]
stk.push(2);                          // stack becomes [1, 2]
stk.push(3);                          // stack becomes [1, 2, 3]
stk.push(4);                          // stack still [1, 2, 3], Do not add another elements as size is 4
stk.increment(5, 100);                // stack becomes [101, 102, 103]
stk.increment(2, 100);                // stack becomes [201, 202, 103]
stk.pop();                            // return 103 --> Return top of the stack 103, stack becomes [201, 202]
stk.pop();                            // return 202 --> Return top of the stack 202, stack becomes [201]
stk.pop();                            // return 201 --> Return top of the stack 201, stack becomes []
stk.pop();                            // return -1 --> Stack is empty return -1.

Constraints:
1 <= maxSize, x, k <= 1000
0 <= val <= 100
At most 1000 calls will be made to each method of increment, push and pop each separately.
```

<details><summary>Hint</summary>

```text
1. Use an array to represent the stack. Push will add new integer to the array.
   Pop removes the last element in the array and increment will add val to the first k elements of the array.
2. This solution run in O(1) per push and pop and O(k) per increment.
```

</details>

</details>

<details><summary>C</summary>

```c
typedef struct {
    int* data;
    int top;
    int maxSize;
} CustomStack;
CustomStack* customStackCreate(int maxSize) {
    CustomStack* obj = NULL;

    obj = (CustomStack*)malloc(sizeof(CustomStack));
    if (obj == NULL) {
        perror("malloc");
        return obj;
    }
    obj->data = (int*)malloc(maxSize * sizeof(int));
    if (obj->data == NULL) {
        perror("malloc");
        return obj;
    }
    obj->maxSize = maxSize;
    obj->top = -1;  // Pops and returns the top of the stack or -1 if the stack is empty.

    return obj;
}
void customStackPush(CustomStack* obj, int x) {
    if (obj->top == obj->maxSize - 1) {
        return;
    }
    obj->top += 1;
    obj->data[obj->top] = x;
}
int customStackPop(CustomStack* obj) {
    int retVal = -1;  // Pops and returns the top of the stack or -1 if the stack is empty.

    if (obj->top == -1) {
        return retVal;
    }
    retVal = obj->data[obj->top];
    obj->top -= 1;

    return retVal;
}
void customStackIncrement(CustomStack* obj, int k, int val) {
    int i;
    if (obj->top + 1 < k) {
        for (i = 0; i <= obj->top; i++) {
            obj->data[i] += val;
        }
    } else {
        for (i = 0; i < k; i++) {
            obj->data[i] += val;
        }
    }
}
void customStackFree(CustomStack* obj) {
    free(obj->data);
    obj->data = NULL;
    free(obj);
    obj = NULL;
}
/**
 * Your CustomStack struct will be instantiated and called as such:
 * CustomStack* obj = customStackCreate(maxSize);
 * customStackPush(obj, x);
 * int param_2 = customStackPop(obj);
 * customStackIncrement(obj, k, val);
 * customStackFree(obj);
 */
```

</details>

<details><summary>C++</summary>

```c++
class CustomStack {
   private:
    list<int> stack;
    int maxSize;

   public:
    CustomStack(int maxSize) {
        //
        this->maxSize = maxSize;
    }
    void push(int x) {
        int stackSize = stack.size();
        if (stackSize < maxSize) {
            stack.push_back(x);
        }
    }
    int pop() {
        int retVal = -1;  // Pops and returns the top of the stack or -1 if the stack is empty.

        if (stack.empty()) {
            return retVal;
        }
        retVal = stack.back();
        stack.pop_back();

        return retVal;
    }
    void increment(int k, int val) {
        auto iterator = stack.begin();
        for (int i = 0; (i < k && iterator != stack.end()); (i++, iterator++)) {
            (*iterator) += val;
        }
    }
};
/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */
```

</details>

<details><summary>Python3</summary>

```python
class CustomStack:
    def __init__(self, maxSize: int):
        self.stack = deque()
        self.maxSize = maxSize

    def push(self, x: int) -> None:
        stackSize = len(self.stack)
        if stackSize < self.maxSize:
            self.stack.append(x)

    def pop(self) -> int:
        # Pops and returns the top of the stack or -1 if the stack is empty.
        retVal = -1

        if self.stack:
            retVal = self.stack.pop()

        return retVal

    def increment(self, k: int, val: int) -> None:
        for i, _ in zip(range(k), self.stack):
            self.stack[i] += val


# Your CustomStack object will be instantiated and called as such:
# obj = CustomStack(maxSize)
# obj.push(x)
# param_2 = obj.pop()
# obj.increment(k,val)
```

</details>

## [1441. Build an Array With Stack Operations](https://leetcode.com/problems/build-an-array-with-stack-operations/)  1180

- [Official](https://leetcode.com/problems/build-an-array-with-stack-operations/editorial/)
- [Official](https://leetcode.cn/problems/build-an-array-with-stack-operations/solutions/1890865/yong-zhan-cao-zuo-gou-jian-shu-zu-by-lee-omde/)

<details><summary>Description</summary>

```text
You are given an array target and an integer n.

In each iteration, you will read a number from list = [1, 2, 3, ..., n].

Build the target array using the following operations:
"Push": Reads a new element from the beginning list, and pushes it in the array.
"Pop": Deletes the last element of the array.
If the target array is already built, stop reading more elements.

Return a list of the operations needed to build target. If there are multiple valid answers, return any of them.

Example 1:
Input: target = [1,3], n = 3
Output: ["Push","Push","Pop","Push"]
Explanation:
Read number 1 and automatically push in the array -> [1]
Read number 2 and automatically push in the array then Pop it -> [1]
Read number 3 and automatically push in the array -> [1,3]

Example 2:
Input: target = [1,2,3], n = 3
Output: ["Push","Push","Push"]

Example 3:
Input: target = [1,2], n = 4
Output: ["Push","Push"]
Explanation: You only need to read the first 2 numbers and stop.

Constraints:
1 <= target.length <= 100
1 <= n <= 100
1 <= target[i] <= n
target is strictly increasing.
```

<details><summary>Hint</summary>

```text
1. Use "Push" for numbers to be kept in target array and ["Push", "Pop"] for numbers to be discarded.
```

</details>

</details>

<details><summary>C</summary>

```c
char** buildArray(int* target, int targetSize, int n, int* returnSize) {
    char** pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (char**)malloc(sizeof(char*) * (n * 2));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

#define STR_SIZE (8)
#define STR_PUSH "Push"
#define STR_POP "Pop"
    int targetIndex = 0;
    int i;
    for (i = 1; i <= n; ++i) {
        if (targetIndex == targetSize) {
            break;
        }

        if (i == target[targetIndex]) {
            pRetVal[(*returnSize)] = (char*)malloc(STR_SIZE * sizeof(char));
            if (pRetVal[(*returnSize)] == NULL) {
                perror("malloc");
                return pRetVal;
            }
            memset(pRetVal[(*returnSize)], 0, (STR_SIZE * sizeof(char)));
            snprintf(pRetVal[(*returnSize)], (STR_SIZE * sizeof(char)), "%s", STR_PUSH);
            targetIndex++;
            (*returnSize)++;
        } else {
            pRetVal[(*returnSize)] = (char*)malloc(STR_SIZE * sizeof(char));
            if (pRetVal[(*returnSize)] == NULL) {
                perror("malloc");
                return pRetVal;
            }
            memset(pRetVal[(*returnSize)], 0, (STR_SIZE * sizeof(char)));
            snprintf(pRetVal[(*returnSize)], (STR_SIZE * sizeof(char)), "%s", STR_PUSH);
            (*returnSize)++;

            pRetVal[(*returnSize)] = (char*)malloc(STR_SIZE * sizeof(char));
            if (pRetVal[(*returnSize)] == NULL) {
                perror("malloc");
                return pRetVal;
            }
            memset(pRetVal[(*returnSize)], 0, (STR_SIZE * sizeof(char)));
            snprintf(pRetVal[(*returnSize)], (STR_SIZE * sizeof(char)), "%s", STR_POP);
            (*returnSize)++;
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
    vector<string> buildArray(vector<int>& target, int n) {
        vector<string> retVal;

#define STR_PUSH "Push"
#define STR_POP "Pop"
        int targetSize = target.size();
        int targetIndex = 0;
        for (int i = 1; i <= n; ++i) {
            if (targetIndex >= targetSize) {
                break;
            }

            if (i == target[targetIndex]) {
                retVal.emplace_back(STR_PUSH);
                targetIndex += 1;
            } else {
                retVal.emplace_back(STR_PUSH);
                retVal.emplace_back(STR_POP);
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
        self.strPush = "Push"
        self.strPop = "Pop"

    def buildArray(self, target: List[int], n: int) -> List[str]:
        retVal = []

        targetSize = len(target)
        targetIndex = 0
        for i in range(1, n + 1):
            if targetIndex >= targetSize:
                break

            if i == target[targetIndex]:
                retVal.append(self.strPush)
                targetIndex += 1
            else:
                retVal.append(self.strPush)
                retVal.append(self.strPop)

        return retVal
```

</details>

## [1475. Final Prices With a Special Discount in a Shop](https://leetcode.com/problems/final-prices-with-a-special-discount-in-a-shop/)  1212

- [Official](https://leetcode.com/problems/final-prices-with-a-special-discount-in-a-shop/editorial/)
- [Official](https://leetcode.cn/problems/final-prices-with-a-special-discount-in-a-shop/solutions/1788169/shang-pin-zhe-kou-hou-de-zui-zhong-jie-g-ind3/)

<details><summary>Description</summary>

```text
You are given an integer array prices where prices[i] is the price of the ith item in a shop.

There is a special discount for items in the shop.
If you buy the ith item, then you will receive a discount equivalent to prices[j]
where j is the minimum index such that j > i and prices[j] <= prices[i].
Otherwise, you will not receive any discount at all.

Return an integer array answer where answer[i] is the final price you will pay for the ith item of the shop,
considering the special discount.

Example 1:
Input: prices = [8,4,6,2,3]
Output: [4,2,4,2,3]
Explanation:
For item 0 with price[0]=8 you will receive a discount equivalent to prices[1]=4,
therefore, the final price you will pay is 8 - 4 = 4.
For item 1 with price[1]=4 you will receive a discount equivalent to prices[3]=2,
therefore, the final price you will pay is 4 - 2 = 2.
For item 2 with price[2]=6 you will receive a discount equivalent to prices[3]=2,
therefore, the final price you will pay is 6 - 2 = 4.
For items 3 and 4 you will not receive any discount at all.

Example 2:
Input: prices = [1,2,3,4,5]
Output: [1,2,3,4,5]
Explanation: In this case, for all items, you will not receive any discount at all.

Example 3:
Input: prices = [10,1,1,6]
Output: [9,0,1,6]

Constraints:
1 <= prices.length <= 500
1 <= prices[i] <= 1000
```

<details><summary>Hint</summary>

```text
1. Use brute force: For the ith item in the shop with a loop find the first position j satisfying the conditions
   and apply the discount, otherwise, the discount is 0.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *finalPrices(int *prices, int pricesSize, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int *)malloc(pricesSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (pricesSize * sizeof(int)));
    memcpy(pRetVal, prices, (pricesSize * sizeof(int)));
    (*returnSize) = pricesSize;

    int monotonicStackTop = -1;
    int monotonicStack[pricesSize];
    memset(monotonicStack, 0, sizeof(monotonicStack));
    for (int i = 0; i < pricesSize; ++i) {
        // Process items that can be discounted by current price
        while ((monotonicStackTop != -1) && (prices[monotonicStack[monotonicStackTop]] >= prices[i])) {
            // Apply discount to previous item using current price
            pRetVal[monotonicStack[monotonicStackTop]] -= prices[i];
            monotonicStack[monotonicStackTop--] = 0;
        }

        // Add current index to monotonicStack
        monotonicStack[++monotonicStackTop] = i;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> finalPrices(vector<int>& prices) {
        vector<int> retVal = prices;

        stack<int> monotonicStack;
        int pricesSize = prices.size();
        for (int i = 0; i < pricesSize; ++i) {
            // Process items that can be discounted by current price
            while ((monotonicStack.empty() == false) && (prices[monotonicStack.top()] >= prices[i])) {
                // Apply discount to previous item using current price
                retVal[monotonicStack.top()] -= prices[i];
                monotonicStack.pop();
            }

            // Add current index to monotonicStack
            monotonicStack.push(i);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def finalPrices(self, prices: List[int]) -> List[int]:
        retVal = prices

        monotonicStack = deque()
        priceSize = len(prices)
        for i in range(priceSize):
            # Process items that can be discounted by current price
            while monotonicStack and (prices[monotonicStack[-1]] >= prices[i]):
                # Apply discount to previous item using current price
                retVal[monotonicStack.pop()] -= prices[i]

            # Add current index to monotonicStack
            monotonicStack.append(i)

        return retVal
```

</details>

## [1504. Count Submatrices With All Ones](https://leetcode.com/problems/count-submatrices-with-all-ones/)  1845

- [Official](https://leetcode.com/problems/count-submatrices-with-all-ones/editorial/)
- [Official](https://leetcode.cn/problems/count-submatrices-with-all-ones/solutions/336410/tong-ji-quan-1-zi-ju-xing-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given an m x n binary matrix mat, return the number of submatrices that have all ones.

Example 1:
Input: mat = [[1,0,1],[1,1,0],[1,1,0]]
Output: 13
Explanation:
There are 6 rectangles of side 1x1.
There are 2 rectangles of side 1x2.
There are 3 rectangles of side 2x1.
There is 1 rectangle of side 2x2.
There is 1 rectangle of side 3x1.
Total number of rectangles = 6 + 2 + 3 + 1 + 1 = 13.

Example 2:
Input: mat = [[0,1,1,0],[0,1,1,1],[1,1,1,0]]
Output: 24
Explanation:
There are 8 rectangles of side 1x1.
There are 5 rectangles of side 1x2.
There are 2 rectangles of side 1x3.
There are 4 rectangles of side 2x1.
There are 2 rectangles of side 2x2.
There are 2 rectangles of side 3x1.
There is 1 rectangle of side 3x2.
Total number of rectangles = 8 + 5 + 2 + 4 + 2 + 2 + 1 = 24.

Constraints:
1 <= m, n <= 150
mat[i][j] is either 0 or 1.
```

<details><summary>Hint</summary>

```text
1. For each row i, create an array nums where: if mat[i][j] == 0 then nums[j] = 0 else nums[j] = nums[j-1] +1.
2. In the row i, number of rectangles between column j and k(inclusive) and ends in row i,
   is equal to SUM(min(nums[j, .. idx])) where idx go from j to k.
   Expected solution is O(n^3).
```

</details>

</details>

<details><summary>C</summary>

```c
int numSubmat(int** mat, int matSize, int* matColSize) {
    int retVal = 0;

    int colSize = matColSize[0];

    int heights[colSize];
    memset(heights, 0, sizeof(heights));

    int monotonicStack[colSize + 1][3];
    int monotonicStackTop = 0;
    for (int r = 0; r < matSize; r++) {
        for (int i = 0; i < colSize; i++) {
            heights[i] = (mat[r][i] == 0) ? (0) : (heights[i] + 1);
        }

        monotonicStackTop = 0;
        monotonicStack[monotonicStackTop][0] = -1;
        monotonicStack[monotonicStackTop][1] = 0;
        monotonicStack[monotonicStackTop][2] = -1;
        monotonicStackTop++;
        for (int i = 0; i < colSize; i++) {
            int h = heights[i];
            while ((monotonicStackTop > 0) && (monotonicStack[monotonicStackTop - 1][2] >= h)) {
                monotonicStackTop--;
            }

            int j = monotonicStack[monotonicStackTop - 1][0];
            int prev = monotonicStack[monotonicStackTop - 1][1];
            int cur = prev + (i - j) * h;
            monotonicStack[monotonicStackTop][0] = i;
            monotonicStack[monotonicStackTop][1] = cur;
            monotonicStack[monotonicStackTop][2] = h;
            monotonicStackTop++;

            retVal += cur;
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
    int numSubmat(vector<vector<int>>& mat) {
        int retVal = 0;

        int matColSize = mat[0].size();

        vector<int> heights(matColSize, 0);
        for (const auto& row : mat) {
            for (int i = 0; i < matColSize; ++i) {
                heights[i] = (row[i] == 0) ? 0 : heights[i] + 1;
            }

            stack<vector<int>> monotonicStack;
            monotonicStack.push({-1, 0, -1});
            for (int i = 0; i < matColSize; ++i) {
                int h = heights[i];
                while (monotonicStack.top()[2] >= h) {
                    monotonicStack.pop();
                }

                auto& top = monotonicStack.top();
                int j = top[0];
                int prev = top[1];
                int cur = prev + (i - j) * h;
                monotonicStack.push({i, cur, h});

                retVal += cur;
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
    def numSubmat(self, mat: List[List[int]]) -> int:
        retVal = 0

        matColSize = len(mat[0])
        heights = [0] * matColSize

        for row in mat:
            for i, x in enumerate(row):
                heights[i] = 0 if x == 0 else heights[i] + 1

            monotonicStack = [[-1, 0, -1]]
            for i, h in enumerate(heights):
                while monotonicStack[-1][2] >= h:
                    monotonicStack.pop()

                j, prev, _ = monotonicStack[-1]
                cur = prev + (i - j) * h
                monotonicStack.append([i, cur, h])

                retVal += cur

        return retVal
```

</details>

## [1544. Make The String Great](https://leetcode.com/problems/make-the-string-great/)  1344

- [Official](https://leetcode.cn/problems/make-the-string-great/solutions/382513/zheng-li-zi-fu-chuan-by-leetcode-solution/)

<details><summary>Description</summary>

```text
tring s of lower and upper case English letters.

A good string is a string which doesn't have two adjacent characters s[i] and s[i + 1] where:
- 0 <= i <= s.length - 2
- s[i] is a lower-case letter and s[i + 1] is the same letter but in upper-case or vice-versa.

To make the string good, you can choose two adjacent characters that make the string bad and remove them.
You can keep doing this until the string becomes good.

Return the string after making it good. The answer is guaranteed to be unique under the given constraints.

Notice that an empty string is also good.

Example 1:
Input: s = "leEeetcode"
Output: "leetcode"
Explanation: In the first step, either you choose i = 1 or i = 2, both will result "leEeetcode" to be reduced to "leetcode".

Example 2:
Input: s = "abBAcC"
Output: ""
Explanation: We have many possible scenarios, and all lead to the same answer. For example:
"abBAcC" --> "aAcC" --> "cC" --> ""
"abBAcC" --> "abBA" --> "aA" --> ""

Example 3:
Input: s = "s"
Output: "s"

Constraints:
1 <= s.length <= 100
s contains only lower and upper case English letters.
```

<details><summary>Hint</summary>

```text
1. The order you choose 2 characters to remove doesn't matter.
2. Keep applying the mentioned step to s till the length of the string is not changed.
```

</details>

</details>

<details><summary>C</summary>

```c
char* makeGood(char* s) {
    char* pRetVal = s;

    int sSize = strlen(s);
    int top = -1;
    int i;
    for (i = 0; i < sSize; ++i) {
        if ((top != -1) && (pRetVal[top] == (pRetVal[i] ^ 32))) {
            --top;
        } else {
            pRetVal[++top] = pRetVal[i];
        }
    }
    pRetVal[++top] = 0;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string makeGood(string s) {
        string retVal;

        for (char c : s) {
            if ((retVal.empty() == false) && (retVal.back() == (c ^ 32))) {
                retVal.pop_back();
            } else {
                retVal.push_back(c);
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
    def makeGood(self, s: str) -> str:
        retVal = ""

        for c in s:
            if (retVal != "") and (ord(retVal[-1]) == ord(c) ^ 32):
                retVal = retVal[:-1]
            else:
                retVal += c

        return retVal
```

</details>

## [1598. Crawler Log Folder](https://leetcode.com/problems/crawler-log-folder/)  1297

- [Official](https://leetcode.com/problems/crawler-log-folder/editorial/)
- [Official](https://leetcode.cn/problems/crawler-log-folder/solutions/1811170/wen-jian-jia-cao-zuo-ri-zhi-sou-ji-qi-by-6unr/)

<details><summary>Description</summary>

```text
The Leetcode file system keeps a log each time some user performs a change folder operation.

The operations are described below:
- "../" : Move to the parent folder of the current folder.
  (If you are already in the main folder, remain in the same folder).
- "./" : Remain in the same folder.
- "x/" : Move to the child folder named x (This folder is guaranteed to always exist).

You are given a list of strings logs where logs[i] is the operation performed by the user at the ith step.

The file system starts in the main folder, then the operations in logs are performed.

Return the minimum number of operations needed to go back to the main folder after the change folder operations.

Example 1:
Input: logs = ["d1/","d2/","../","d21/","./"]
Output: 2
Explanation: Use this change folder operation "../" 2 times and go back to the main folder.

Example 2:
Input: logs = ["d1/","d2/","./","d3/","../","d31/"]
Output: 3

Example 3:
Input: logs = ["d1/","../","../","../"]
Output: 0

Constraints:
1 <= logs.length <= 10^3
2 <= logs[i].length <= 10
logs[i] contains lowercase English letters, digits, '.', and '/'.
logs[i] follows the format described in the statement.
Folder names consist of lowercase English letters and digits.
```

<details><summary>Hint</summary>

```text
1. Simulate the process but don’t move the pointer beyond the main folder.
2. Simulate the process but don’t move the pointer beyond the main folder.
```

</details>

</details>

<details><summary>C</summary>

```c
int minOperations(char** logs, int logsSize) {
    int retVal = 0;

    int i;
    for (i = 0; i < logsSize; ++i) {
        if (strcmp(logs[i], "../") == 0) {
            retVal = (retVal > 0) ? (retVal - 1) : (retVal);
        } else if (strcmp(logs[i], "./") == 0) {
            continue;
        } else {
            ++retVal;
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
    int minOperations(vector<string>& logs) {
        int retVal = 0;

        int logsSize = logs.size();
        for (int i = 0; i < logsSize; ++i) {
            if (logs[i] == "../") {
                if (retVal > 0) {
                    retVal--;
                }
            } else if (logs[i] == "./") {
                continue;
            } else {
                ++retVal;
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
    def minOperations(self, logs: List[str]) -> int:
        retVal = 0

        for log in logs:
            if log == "../":
                if retVal > 0:
                    retVal -= 1
            elif log == "./":
                continue
            else:
                retVal += 1

        return retVal
```

</details>

## [1614. Maximum Nesting Depth of the Parentheses](https://leetcode.com/problems/maximum-nesting-depth-of-the-parentheses/)  1322

- [Official](https://leetcode.com/problems/maximum-nesting-depth-of-the-parentheses/editorial/)
- [Official](https://leetcode.cn/problems/maximum-nesting-depth-of-the-parentheses/solutions/1194617/gua-hao-de-zui-da-qian-tao-shen-du-by-le-av5b/)

<details><summary>Description</summary>

```text
A string is a valid parentheses string (denoted VPS) if it meets one of the following:
- It is an empty string "", or a single character not equal to "(" or ")",
- It can be written as AB (A concatenated with B), where A and B are VPS's, or
- It can be written as (A), where A is a VPS.

We can similarly define the nesting depth depth(S) of any VPS S as follows:
- depth("") = 0
- depth(C) = 0, where C is a string with a single character not equal to "(" or ")".
- depth(A + B) = max(depth(A), depth(B)), where A and B are VPS's.
- depth("(" + A + ")") = 1 + depth(A), where A is a VPS.

For example, "", "()()", and "()(()())" are VPS's (with nesting depths 0, 1, and 2), and ")(" and "(()" are not VPS's.

Given a VPS represented as string s, return the nesting depth of s.

Example 1:
Input: s = "(1+(2*3)+((8)/4))+1"
Output: 3
Explanation: Digit 8 is inside of 3 nested parentheses in the string.

Example 2:
Input: s = "(1)+((2))+(((3)))"
Output: 3

Constraints:
1 <= s.length <= 100
s consists of digits 0-9 and characters '+', '-', '*', '/', '(', and ')'.
It is guaranteed that parentheses expression s is a VPS.
```

<details><summary>Hint</summary>

```text
1. The depth of any character in the VPS is
   the ( number of left brackets before it ) - ( number of right brackets before it )
```

</details>

</details>

<details><summary>C</summary>

```c
int maxDepth(char* s) {
    int retVal = 0;

    int sSize = strlen(s);
    int count = 0;
    int i;
    for (i = 0; i < sSize; ++i) {
        if (s[i] == '(') {
            count++;
        } else if (s[i] == ')') {
            count--;
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
    int maxDepth(string s) {
        int retVal = 0;

        int count = 0;
        for (char c : s) {
            if (c == '(') {
                count++;
            } else if (c == ')') {
                count--;
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
    def maxDepth(self, s: str) -> int:
        retVal = 0

        count = 0
        for c in s:
            if c == '(':
                count += 1
            elif c == ')':
                count -= 1
            retVal = max(retVal, count)

        return retVal
```

</details>

## [1700. Number of Students Unable to Eat Lunch](https://leetcode.com/problems/number-of-students-unable-to-eat-lunch/)  1404

- [Official](https://leetcode.com/problems/number-of-students-unable-to-eat-lunch/editorial/)
- [Official](https://leetcode.cn/problems/number-of-students-unable-to-eat-lunch/solutions/1900373/wu-fa-chi-wu-can-de-xue-sheng-shu-liang-fv3f5/)

<details><summary>Description</summary>

```text
The school cafeteria offers circular and square sandwiches at lunch break, referred to by numbers 0 and 1 respectively.
All students stand in a queue. Each student either prefers square or circular sandwiches.

The number of sandwiches in the cafeteria is equal to the number of students.
The sandwiches are placed in a stack. At each step:
- If the student at the front of the queue prefers the sandwich on the top of the stack,
  they will take it and leave the queue.
- Otherwise, they will leave it and go to the queue's end.

This continues until none of the queue students want to take the top sandwich and are thus unable to eat.

You are given two integer arrays students and sandwiches
where sandwiches[i] is the type of the i​​​​​​th sandwich in the stack (i = 0 is the top of the stack)
and students[j] is the preference of the j​​​​​​th student in the initial queue (j = 0 is the front of the queue).
Return the number of students that are unable to eat.

Example 1:
Input: students = [1,1,0,0], sandwiches = [0,1,0,1]
Output: 0
Explanation:
- Front student leaves the top sandwich and returns to the end of the line making students = [1,0,0,1].
- Front student leaves the top sandwich and returns to the end of the line making students = [0,0,1,1].
- Front student takes the top sandwich and leaves the line making students = [0,1,1] and sandwiches = [1,0,1].
- Front student leaves the top sandwich and returns to the end of the line making students = [1,1,0].
- Front student takes the top sandwich and leaves the line making students = [1,0] and sandwiches = [0,1].
- Front student leaves the top sandwich and returns to the end of the line making students = [0,1].
- Front student takes the top sandwich and leaves the line making students = [1] and sandwiches = [1].
- Front student takes the top sandwich and leaves the line making students = [] and sandwiches = [].
Hence all students are able to eat.

Example 2:
Input: students = [1,1,1,0,0,1], sandwiches = [1,0,0,0,1,1]
Output: 3

Constraints:
1 <= students.length, sandwiches.length <= 100
students.length == sandwiches.length
sandwiches[i] is 0 or 1.
students[i] is 0 or 1.
```

<details><summary>Hint</summary>

```text
1. Simulate the given in the statement
2. Calculate those who will eat instead of those who will not.
```

</details>

</details>

<details><summary>C</summary>

```c
int countStudents(int* students, int studentsSize, int* sandwiches, int sandwichesSize) {
    int retVal = 0;

    int i;

    // The school cafeteria offers circular and square sandwiches at lunch break,
    // referred to by numbers 0 and 1 respectively.
    int circular = 0;
    int square = 0;
    for (i = 0; i < studentsSize; ++i) {
        if (students[i] == 0) {
            circular++;
        } else if (students[i] == 1) {
            square++;
        }
    }

    for (i = 0; i < sandwichesSize; ++i) {
        if ((sandwiches[i] == 0) && (circular != 0)) {
            circular--;
        } else if ((sandwiches[i] == 1) && (square != 0)) {
            square--;
        } else {
            retVal = circular + square;
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
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        int retVal = 0;

        // The school cafeteria offers circular and square sandwiches at lunch break,
        // referred to by numbers 0 and 1 respectively.
        int circular = 0;
        int square = 0;
        for (int student : students) {
            if (student == 0) {
                circular++;
            } else if (student == 1) {
                square++;
            }
        }

        for (int sandwiche : sandwiches) {
            if ((sandwiche == 0) && (circular != 0)) {
                circular--;
            } else if ((sandwiche == 1) && (square != 0)) {
                square--;
            } else {
                retVal = circular + square;
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
    def countStudents(self, students: List[int], sandwiches: List[int]) -> int:
        retVal = 0

        # The school cafeteria offers circular and square sandwiches at lunch break,
        # referred to by numbers 0 and 1 respectively.
        circular = 0
        square = 0
        for student in students:
            if student == 0:
                circular += 1
            elif student == 1:
                square += 1

        for sandwiche in sandwiches:
            if (sandwiche == 0) and (circular != 0):
                circular -= 1
            elif (sandwiche == 1) and (square != 0):
                square -= 1
            else:
                retVal = circular + square
                break

        return retVal
```

</details>

## [1910. Remove All Occurrences of a Substring](https://leetcode.com/problems/remove-all-occurrences-of-a-substring/)  1460

- [Official](https://leetcode.com/problems/remove-all-occurrences-of-a-substring/editorial/)
- [Official](https://leetcode.cn/problems/remove-all-occurrences-of-a-substring/solutions/847225/shan-chu-yi-ge-zi-fu-chuan-zhong-suo-you-4j08/)

<details><summary>Description</summary>

```text
Given two strings s and part,
perform the following operation on s until all occurrences of the substring part are removed:
- Find the leftmost occurrence of the substring part and remove it from s.

Return s after removing all occurrences of part.

A substring is a contiguous sequence of characters in a string.

Example 1:
Input: s = "daabcbaabcbc", part = "abc"
Output: "dab"
Explanation: The following operations are done:
- s = "daabcbaabcbc", remove "abc" starting at index 2, so s = "dabaabcbc".
- s = "dabaabcbc", remove "abc" starting at index 4, so s = "dababc".
- s = "dababc", remove "abc" starting at index 3, so s = "dab".
Now s has no occurrences of "abc".

Example 2:
Input: s = "axxxxyyyyb", part = "xy"
Output: "ab"
Explanation: The following operations are done:
- s = "axxxxyyyyb", remove "xy" starting at index 4 so s = "axxxyyyb".
- s = "axxxyyyb", remove "xy" starting at index 3 so s = "axxyyb".
- s = "axxyyb", remove "xy" starting at index 2 so s = "axyb".
- s = "axyb", remove "xy" starting at index 1 so s = "ab".
Now s has no occurrences of "xy".

Constraints:
1 <= s.length <= 1000
1 <= part.length <= 1000
s​​​​​​ and part consists of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Note that a new occurrence of pattern can appear if you remove an old one,
   For example, s = "ababcc" and pattern = "abc".
2. You can maintain a stack of characters
   and if the last character of the pattern size in the stack match the pattern remove them
```

</details>

</details>

<details><summary>C</summary>

```c
bool checkMatch(char* stack, int stackTop, char* part, int partLength) {
    bool retVal = true;

    int tmpTop = stackTop;
    char tmp[(stackTop + 1) + 1];
    snprintf(tmp, sizeof(tmp), "%s", stack);
    for (int partIndex = partLength - 1; partIndex >= 0; partIndex--) {
        if (tmp[tmpTop] != part[partIndex]) {
            retVal = false;
            break;
        }
        tmpTop--;
    }

    return retVal;
}
char* removeOccurrences(char* s, char* part) {
    char* pRetVal = "";

    int sSize = strlen(s);
    int partSize = strlen(part);

    int stackTop = -1;
    int returnSize = sSize + 4;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));
    returnSize = 0;

    for (int index = 0; index < sSize; index++) {
        pRetVal[++stackTop] = s[index];
        returnSize = stackTop + 1;

        if ((returnSize < partSize) || (checkMatch(pRetVal, stackTop, part, partSize) == false)) {
            continue;
        }

        for (int j = 0; j < partSize; j++) {
            pRetVal[stackTop--] = '\0';
        }
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    bool checkMatch(stack<char>& stk, string& part, int partLength) {
        bool retVal = true;

        stack<char> temp = stk;
        for (int partIndex = partLength - 1; partIndex >= 0; partIndex--) {
            if (temp.top() != part[partIndex]) {
                retVal = false;
                break;
            }
            temp.pop();
        }

        return retVal;
    }

   public:
    string removeOccurrences(string s, string part) {
        string retVal = "";

        int sSize = s.size();
        int partSize = part.size();
        stack<char> stk;
        for (int index = 0; index < sSize; index++) {
            stk.push(s[index]);
            int stkSize = stk.size();
            if ((stkSize < partSize) || (checkMatch(stk, part, partSize) == false)) {
                continue;
            }

            for (int j = 0; j < partSize; j++) {
                stk.pop();
            }
        }

        while (stk.empty() == false) {
            retVal = stk.top() + retVal;
            stk.pop();
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def checkMatch(self, stack: list, part: str, partLength: int) -> bool:
        retVal = False

        if "".join(stack[-partLength:]) == part:
            retVal = True

        return retVal

    def removeOccurrences(self, s: str, part: str) -> str:
        retVal = ""

        partSize = len(part)
        stack = []
        for char in s:
            stack.append(char)
            stackSize = len(stack)
            if (stackSize < partSize) or (self.checkMatch(stack, part, partSize) == False):
                continue
            for _ in range(partSize):
                stack.pop()
        retVal = "".join(stack)

        return retVal
```

</details>

## [1963. Minimum Number of Swaps to Make the String Balanced](https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-string-balanced/)  1688

- [Official](https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-string-balanced/editorial/)
- [Official](https://leetcode.cn/problems/minimum-number-of-swaps-to-make-the-string-balanced/solutions/922748/shi-zi-fu-chuan-ping-heng-de-zui-xiao-ji-f7ye/)

<details><summary>Description</summary>

```text
You are given a 0-indexed string s of even length n.
The string consists of exactly n / 2 opening brackets '[' and n / 2 closing brackets ']'.

A string is called balanced if and only if:
- It is the empty string, or
- It can be written as AB, where both A and B are balanced strings, or
- It can be written as [C], where C is a balanced string.

You may swap the brackets at any two indices any number of times.

Return the minimum number of swaps to make s balanced.

Example 1:
Input: s = "][]["
Output: 1
Explanation: You can make the string balanced by swapping index 0 with index 3.
The resulting string is "[[]]".

Example 2:
Input: s = "]]][[["
Output: 2
Explanation: You can do the following to make the string balanced:
- Swap index 0 with index 4. s = "[]][][".
- Swap index 1 with index 5. s = "[[][]]".
The resulting string is "[[][]]".

Example 3:
Input: s = "[]"
Output: 0
Explanation: The string is already balanced.

Constraints:
n == s.length
2 <= n <= 10^6
n is even.
s[i] is either '[' or ']'.
The number of opening brackets '[' equals n / 2, and the number of closing brackets ']' equals n / 2.
```

<details><summary>Hint</summary>

```text
1. Iterate over the string and keep track of the number of opening and closing brackets on each step.
2. If the number of closing brackets is ever larger, you need to make a swap.
3. Swap it with the opening bracket closest to the end of s.
```

</details>

</details>

<details><summary>C</summary>

```c
int minSwaps(char* s) {
    int retVal = 0;

    int stackSize = 0;
    int sSize = strlen(s);
    for (int i = 0; i < sSize; ++i) {
        if (s[i] == '[') {
            // If character is opening bracket, increment the stack size.
            stackSize++;
        } else if (stackSize > 0) {
            // If the character is closing bracket, and we have an opening bracket, decrease the stack size.
            stackSize--;
        }
    }
    retVal = (stackSize + 1) / 2;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minSwaps(string s) {
        int retVal = 0;

        int stackSize = 0;
        for (char c : s) {
            if (c == '[') {
                // If character is opening bracket, increment the stack size.
                stackSize++;
            } else if (stackSize > 0) {
                // If the character is closing bracket, and we have an opening bracket, decrease the stack size.
                stackSize--;
            }
        }
        retVal = (stackSize + 1) / 2;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minSwaps(self, s: str) -> int:
        retVal = 0

        stackSize = 0
        for ch in s:
            # If character is opening bracket, increment the stack size.
            if ch == "[":
                stackSize += 1
            # If the character is closing bracket, and we have an opening bracket, decrease the stack size.
            elif stackSize > 0:
                stackSize -= 1
        retVal = (stackSize + 1) // 2

        return retVal
```

</details>
