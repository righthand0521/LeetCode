# [Stack](https://en.wikipedia.org/wiki/Stack_(abstract_data_type))

- Monotonic Stack

## [20. Valid Parentheses](https://leetcode.com/problems/valid-parentheses/)

<details><summary>Description</summary>

```text
Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
An input string is valid if:
Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.

Example 1:
Input: s = "()"
Output: true

Example 2:
Input: s = "()[]{}"
Output: true

Example 3:
Input: s = "(]"
Output: false

Constraints:
1 <= s.length <= 10^4
s consists of parentheses only '()[]{}'.
```

<details><summary>Hint</summary>

```text
1. Use a stack of characters.
2. When you encounter an opening bracket, push it to the top of the stack.
3. When you encounter a closing bracket, check if the top of the stack was the opening for it.
   If yes, pop it from the stack. Otherwise, return false.
```

</details>

</details>

<details><summary>C</summary>

```c
bool isValid(char *s) {
    bool retVal = false;

    int sSize = strlen(s);
    char stack[sSize];
    memset(stack, 0, sizeof(stack));
    int stackHead = 0;

    // s consists of parentheses only '()[]{}'.
    struct Parentheses_t {
        char open;
        char close;
    } parenthesesMap[] = {{'(', ')'}, {'[', ']'}, {'{', '}'}};
    int numberOfParentheses = sizeof(parenthesesMap) / sizeof(parenthesesMap[0]);

    int i, j;
    for (i = 0; i < sSize; ++i) {
        for (j = 0; j < numberOfParentheses; ++j) {
            if (s[i] == parenthesesMap[j].open) {
                stack[stackHead++] = parenthesesMap[j].close;
                break;
            }

            if (s[i] == parenthesesMap[j].close) {
                if (stackHead == 0) {
                    return retVal;
                }

                if (s[i] != stack[--stackHead]) {
                    return retVal;
                }
                stack[stackHead] = '\0';
            }
        }
    }
    if (stackHead == 0) {
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
    bool isValid(string s) {
        bool retVal = false;

        // s consists of parentheses only '()[]{}'.
        unordered_map<char, char> parenthesesMap = {{'(', ')'}, {'[', ']'}, {'{', '}'}};

        stack<char> stack;
        for (char c : s) {
            for (auto [key, value] : parenthesesMap) {
                if (c == key) {
                    stack.push(value);
                    break;
                }

                if (c == value) {
                    if (stack.empty() == true) {
                        return retVal;
                    }

                    if (c != stack.top()) {
                        return retVal;
                    }
                    stack.pop();
                }
            }
        }
        if (stack.empty() == true) {
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
    def isValid(self, s: str) -> bool:
        retVal = False

        # s consists of parentheses only '()[]{}'.
        parenthesesMap = {
            '(': ')',
            '[': ']',
            '{': '}'
        }

        stack = []
        for pChar in s:
            if pChar in parenthesesMap:
                stack.append(parenthesesMap[pChar])
                continue

            if not stack:
                return retVal

            if stack.pop() != pChar:
                return retVal
        if not stack:
            retVal = True

        return retVal
```

</details>

## [32. Longest Valid Parentheses](https://leetcode.com/problems/longest-valid-parentheses/)

- [Official](https://leetcode.cn/problems/longest-valid-parentheses/solutions/314683/zui-chang-you-xiao-gua-hao-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given a string containing just the characters '(' and ')',
return the length of the longest valid (well-formed) parentheses substring.

Example 1:
Input: s = "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()".

Example 2:
Input: s = ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()".

Example 3:
Input: s = ""
Output: 0

Constraints:
0 <= s.length <= 3 * 10^4
s[i] is '(', or ')'.
```

</details>

<details><summary>C</summary>

```c
int longestValidParentheses(char* s) {
    int retVal = 0;

    int sSize = strlen(s);

    int stackTop = -1;
    int stack[sSize + 1];
    memset(stack, 0, sizeof(stack));
    stackTop++;
    stack[stackTop] = -1;

    int i;
    for (i = 0; i < sSize; i++) {
        if (s[i] == '(') {
            stackTop++;
            stack[stackTop] = i;
            continue;
        }

        stack[stackTop] = 0;
        stackTop--;
        if (stackTop == -1) {
            stackTop++;
            stack[stackTop] = i;
        } else {
            retVal = fmax(retVal, i - stack[stackTop]);
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
    int longestValidParentheses(string s) {
        int retVal = 0;

        stack<int> stack;
        stack.push(-1);

        int sSize = s.size();
        for (int i = 0; i < sSize; i++) {
            if (s[i] == '(') {
                stack.push(i);
                continue;
            }

            stack.pop();
            if (stack.empty()) {
                stack.push(i);
            } else {
                retVal = max(retVal, i - stack.top());
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
    def longestValidParentheses(self, s: str) -> int:
        retVal = 0

        stack = []
        stack.append(-1)

        for idx, value in enumerate(s):
            if value == '(':
                stack.append(idx)
                continue

            stack.pop()
            if not stack:
                stack.append(idx)
            else:
                retVal = max(retVal, idx-stack[-1])

        return retVal
```

</details>

## [71. Simplify Path](https://leetcode.com/problems/simplify-path/)

- [Official](https://leetcode.cn/problems/simplify-path/solutions/1193258/jian-hua-lu-jing-by-leetcode-solution-aucq/)

<details><summary>Description</summary>

```text
Given a string path, which is an absolute path (starting with a slash '/') to a file or directory
in a Unix-style file system, convert it to the simplified canonical path.

In a Unix-style file system, a period '.' refers to the current directory, a double period '..'
refers to the directory up a level, and any multiple consecutive slashes (i.e. '//') are treated as a single slash '/'.
For this problem, any other format of periods such as '...' are treated as file/directory names.

The canonical path should have the following format:
- The path starts with a single slash '/'.
- Any two directories are separated by a single slash '/'.
- The path does not end with a trailing '/'.
- The path only contains the directories on the path from the root directory to the target file or directory
  (i.e., no period '.' or double period '..')

Return the simplified canonical path.

Example 1:
Input: path = "/home/"
Output: "/home"
Explanation: Note that there is no trailing slash after the last directory name.

Example 2:
Input: path = "/../"
Output: "/"
Explanation: Going one level up from the root directory is a no-op, as the root level is the highest level you can go.

Example 3:
Input: path = "/home//foo/"
Output: "/home/foo"
Explanation: In the canonical path, multiple consecutive slashes are replaced by a single one.

Constraints:
1 <= path.length <= 3000
path consists of English letters, digits, period '.', slash '/' or '_'.
path is a valid absolute Unix path.
```

</details>

<details><summary>C</summary>

```c
char *simplifyPath(char *path) {
    char *pRetVal = NULL;

    int pathSize = strlen(path);
    char *stack[pathSize];
    int stackHead = 0;
#define SEPARATED "/"
    char *pStr = strtok(path, SEPARATED);
    while (pStr != NULL) {
        if (strcmp(pStr, ".") == 0) {
            pStr = strtok(NULL, SEPARATED);
            continue;
        }

        if (strcmp(pStr, "..") == 0) {
            if (stackHead != 0) {
                --stackHead;
                free(stack[stackHead]);
                stack[stackHead] = NULL;
            }
        } else {
            stack[stackHead] = (char *)calloc((strlen(pStr) + 1), sizeof(char));
            if (stack[stackHead] == NULL) {
                perror("calloc");
                return pRetVal;
            }
            snprintf(stack[stackHead], (strlen(pStr) + 1), "%s", pStr);
            ++stackHead;
        }
        pStr = strtok(NULL, SEPARATED);
    }

    pRetVal = (char *)calloc((pathSize + 1), sizeof(char));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }
    int i;
    for (i = 0; i < stackHead; ++i) {
        snprintf(pRetVal + strlen(pRetVal), (pathSize + 1), "/%s", stack[i]);
        free(stack[i]);
        stack[i] = NULL;
    }
    if (strlen(pRetVal) == 0) {
        snprintf(pRetVal, (pathSize + 1), "/");
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string simplifyPath(string path) {
        string retVal = "";

        stack<string> stack;
        stringstream ss(path);
        string name;
        while (getline(ss, name, '/')) {
            if (name.length() == 0) {
                continue;
            }

            if (name.compare(".") == 0) {
                continue;
            } else if (name.compare("..") == 0) {
                if (stack.empty() == false) {
                    stack.pop();
                }
            } else {
                stack.push(name);
            }
        }

        while (stack.empty() == false) {
            retVal = "/" + stack.top() + retVal;
            stack.pop();
        }
        if (retVal.length() == 0) {
            retVal = "/";
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def simplifyPath(self, path: str) -> str:
        retVal = ""

        stack = []
        for name in path.split("/"):
            if not name or name == ".":
                continue

            if name == "..":
                if stack:
                    stack.pop()
            else:
                stack.append(name)
        retVal = "/" + "/".join(stack)

        return retVal
```

</details>

## [84. Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/)

- [Official](https://leetcode.cn/problems/largest-rectangle-in-histogram/solutions/266844/zhu-zhuang-tu-zhong-zui-da-de-ju-xing-by-leetcode-/)

<details><summary>Description</summary>

```text
Given an array of integers heights representing the histogram's bar height where the width of each bar is 1,
return the area of the largest rectangle in the histogram.

Example 1:
Input: heights = [2,1,5,6,2,3]
Output: 10
Explanation: The above is a histogram where width of each bar is 1.
The largest rectangle is shown in the red area, which has an area = 10 units.

Example 2:
Input: heights = [2,4]
Output: 4

Constraints:
1 <= heights.length <= 10^5
0 <= heights[i] <= 10^4
```

</details>

<details><summary>C</summary>

```c
int largestRectangleArea(int* heights, int heightsSize) {
    int retVal = 0;

    int i;

    int left[heightsSize];
    int right[heightsSize];
    for (i = 0; i < heightsSize; ++i) {
        left[i] = 0;
        right[i] = heightsSize;
    }

#define STACK_EMPTY (-1)
    int monotonicStackTop = STACK_EMPTY;
    int monotonicStack[heightsSize + 1];
    memset(monotonicStack, 0, sizeof(monotonicStack));

    for (i = 0; i < heightsSize; ++i) {
        while ((monotonicStackTop != STACK_EMPTY) && (heights[monotonicStack[monotonicStackTop]] >= heights[i])) {
            right[monotonicStack[monotonicStackTop]] = i;
            monotonicStack[monotonicStackTop] = 0;
            monotonicStackTop--;
        }

        left[i] = -1;
        if (monotonicStackTop != STACK_EMPTY) {
            left[i] = monotonicStack[monotonicStackTop];
        }

        monotonicStackTop++;
        monotonicStack[monotonicStackTop] = i;
    }

    for (i = 0; i < heightsSize; ++i) {
        retVal = fmax(retVal, (right[i] - left[i] - 1) * heights[i]);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int largestRectangleArea(vector<int>& heights) {
        int retVal = 0;

        int heightsSize = heights.size();

        vector<int> left(heightsSize, 0);
        vector<int> right(heightsSize, heightsSize);
        stack<int> monotonicStack;
        for (int i = 0; i < heightsSize; ++i) {
            while ((monotonicStack.empty() == false) && (heights[monotonicStack.top()] >= heights[i])) {
                right[monotonicStack.top()] = i;
                monotonicStack.pop();
            }

            left[i] = -1;
            if (monotonicStack.empty() == false) {
                left[i] = monotonicStack.top();
            }

            monotonicStack.push(i);
        }

        for (int i = 0; i < heightsSize; ++i) {
            retVal = max(retVal, (right[i] - left[i] - 1) * heights[i]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def largestRectangleArea(self, heights: List[int]) -> int:
        retVal = 0

        heightsSize = len(heights)

        left = [0] * heightsSize
        right = [heightsSize] * heightsSize
        monotonicStack = []
        for i in range(heightsSize):
            while (monotonicStack) and (heights[monotonicStack[-1]] >= heights[i]):
                right[monotonicStack[-1]] = i
                monotonicStack.pop()

            left[i] = -1
            if monotonicStack:
                left[i] = monotonicStack[-1]

            monotonicStack.append(i)

        for i in range(heightsSize):
            retVal = max(retVal, (right[i] - left[i] - 1) * heights[i])

        return retVal
```

</details>

## [85. Maximal Rectangle](https://leetcode.com/problems/maximal-rectangle/)

- [Official](https://leetcode.cn/problems/maximal-rectangle/solutions/535672/zui-da-ju-xing-by-leetcode-solution-bjlu/)

<details><summary>Description</summary>

```text
Given a rows x cols binary matrix filled with 0's and 1's,
find the largest rectangle containing only 1's and return its area.

Example 1:
Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
Output: 6
Explanation: The maximal rectangle is shown in the above picture.

Example 2:
Input: matrix = [["0"]]
Output: 0

Example 3:
Input: matrix = [["1"]]
Output: 1

Constraints:
rows == matrix.length
cols == matrix[i].length
1 <= row, cols <= 200
matrix[i][j] is '0' or '1'.
```

</details>

<details><summary>C</summary>

```c
int maximalRectangle(char** matrix, int matrixSize, int* matrixColSize) {
    int retVal = 0;

    int rowSize = matrixSize;
    if (rowSize == 0) {
        return 0;
    }
    int colSize = matrixColSize[0];

    int i, j;

    int left[rowSize][colSize];
    memset(left, 0, sizeof(left));
    for (i = 0; i < rowSize; i++) {
        for (j = 0; j < colSize; j++) {
            if (matrix[i][j] == '1') {
                left[i][j] = (j == 0 ? 0 : left[i][j - 1]) + 1;
            }
        }
    }

    int up[rowSize], down[rowSize];
    int monotonicStack[rowSize];
    int monotonicStackTop = 0;
    int height, area;
    for (j = 0; j < colSize; j++) {
        memset(up, 0, sizeof(up));
        monotonicStackTop = 0;
        for (i = 0; i < rowSize; i++) {
            while ((monotonicStackTop > 0) && (left[monotonicStack[monotonicStackTop - 1]][j] >= left[i][j])) {
                monotonicStackTop--;
            }
            up[i] = monotonicStackTop == 0 ? -1 : monotonicStack[monotonicStackTop - 1];
            monotonicStack[monotonicStackTop++] = i;
        }

        memset(down, 0, sizeof(down));
        monotonicStackTop = 0;
        for (i = rowSize - 1; i >= 0; i--) {
            while ((monotonicStackTop > 0) && (left[monotonicStack[monotonicStackTop - 1]][j] >= left[i][j])) {
                monotonicStackTop--;
            }
            down[i] = monotonicStackTop == 0 ? rowSize : monotonicStack[monotonicStackTop - 1];
            monotonicStack[monotonicStackTop++] = i;
        }

        for (i = 0; i < rowSize; i++) {
            height = down[i] - up[i] - 1;
            area = height * left[i][j];
            retVal = fmax(retVal, area);
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
    int maximalRectangle(vector<vector<char>>& matrix) {
        int retVal = 0;

        int rowSize = matrix.size();
        if (rowSize == 0) {
            return retVal;
        }
        int colSize = matrix[0].size();

        vector<vector<int>> left(rowSize, vector<int>(colSize, 0));
        for (int i = 0; i < rowSize; i++) {
            for (int j = 0; j < colSize; j++) {
                if (matrix[i][j] == '1') {
                    left[i][j] = (j == 0 ? 0 : left[i][j - 1]) + 1;
                }
            }
        }

        for (int j = 0; j < colSize; j++) {
            vector<int> up(rowSize, 0);
            stack<int> upMmonotonicStack;
            for (int i = 0; i < rowSize; i++) {
                while ((upMmonotonicStack.empty() == false) && (left[upMmonotonicStack.top()][j] >= left[i][j])) {
                    upMmonotonicStack.pop();
                }
                up[i] = upMmonotonicStack.empty() ? -1 : upMmonotonicStack.top();
                upMmonotonicStack.push(i);
            }

            vector<int> down(rowSize, 0);
            stack<int> downMmonotonicStack;
            for (int i = rowSize - 1; i >= 0; i--) {
                while ((downMmonotonicStack.empty() == false) && (left[downMmonotonicStack.top()][j] >= left[i][j])) {
                    downMmonotonicStack.pop();
                }
                down[i] = downMmonotonicStack.empty() ? rowSize : downMmonotonicStack.top();
                downMmonotonicStack.push(i);
            }

            for (int i = 0; i < rowSize; i++) {
                int height = down[i] - up[i] - 1;
                int area = height * left[i][j];
                retVal = max(retVal, area);
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
    def maximalRectangle(self, matrix: List[List[str]]) -> int:
        retVal = 0

        rowSize = len(matrix)
        if rowSize == 0:
            return retVal
        colSize = len(matrix[0])

        for i in range(rowSize):
            for j in range(colSize):
                if j==0:
                    matrix[i][j] = int(matrix[i][j])
                else:
                    matrix[i][j] = matrix[i][j-1]+1 if matrix[i][j]=='1' else 0

        for j in range(colSize):
            monostack = list()
            left = [-1]*rowSize
            right = [rowSize]*rowSize
            for i in range(rowSize):
                while monostack and matrix[monostack[-1]][j]>matrix[i][j]:
                    right[monostack[-1]] = i
                    monostack.pop()
                left[i] = monostack[-1] if monostack else -1
                monostack.append(i)
            tmp = max((right[i]-left[i]-1)*matrix[i][j] for i in range(rowSize))
            retVal = max(retVal,tmp)

        return retVal
```

</details>

## [150. Evaluate Reverse Polish Notation](https://leetcode.com/problems/evaluate-reverse-polish-notation/)

- [Official](https://leetcode.cn/problems/evaluate-reverse-polish-notation/solutions/667892/ni-bo-lan-biao-da-shi-qiu-zhi-by-leetcod-wue9/)

<details><summary>Description</summary>

```text
Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are +, -, *, and /. Each operand may be an integer or another expression.

Note that division between two integers should truncate toward zero.

It is guaranteed that the given RPN expression is always valid.
That means the expression would always evaluate to a result, and there will not be any division by zero operation.

Example 1:
Input: tokens = ["2","1","+","3","*"]
Output: 9
Explanation: ((2 + 1) * 3) = 9

Example 2:
Input: tokens = ["4","13","5","/","+"]
Output: 6
Explanation: (4 + (13 / 5)) = 6

Example 3:
Input: tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
Output: 22
Explanation: ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22

Constraints:
1 <= tokens.length <= 10^4
tokens[i] is either an operator: "+", "-", "*", or "/", or an integer in the range [-200, 200].
```

</details>

<details><summary>C</summary>

```c
#ifndef STACK
#define STACK (1)

typedef struct Node {
    long long data;
    struct Node* next;
} Node;
void stack_show(struct Node* pTop) {
    Node* pHead = pTop;
    while (pHead != NULL) {
        printf("%3lld -> ", pHead->data);
        pHead = pHead->next;
    }
    printf("NULL\n");
}
void stack_push(struct Node** pTop, int value) {
    Node* pNew = (Node*)malloc(sizeof(struct Node));
    if (pNew == NULL) {
        perror("malloc");
        return;
    }
    pNew->data = value;
    pNew->next = (*pTop);
    *(pTop) = pNew;
}
int stack_pop(struct Node** pTop) {
    int retVal = INT_MIN;

    Node* pHead = (*pTop);
    if (pHead == NULL) {
        printf("Stack is Empty");
        return retVal;
    }
    retVal = pHead->data;
    (*pTop) = pHead->next;
    free(pHead);
    pHead = NULL;

    return retVal;
}
void stack_free(struct Node** pTop) {
    Node* pFree = (*pTop);
    while ((*pTop) != NULL) {
        (*pTop) = (*pTop)->next;
        free(pFree);
        pFree = (*pTop);
    }
    pFree = NULL;
}
#endif
int evalRPN(char** tokens, int tokensSize) {
    int retVal = 0;

    Node* pTop = NULL;
    long long push, pop1, pop2;
    int i;
    for (i = 0; i < tokensSize; ++i) {
        push = 0;

        // tokens[i] is either an operator: "+", "-", "*", or "/"
        if ((strcmp(tokens[i], "+") == 0) || (strcmp(tokens[i], "-") == 0) || (strcmp(tokens[i], "*") == 0) ||
            (strcmp(tokens[i], "/") == 0)) {
            pop1 = stack_pop(&pTop);
            pop2 = stack_pop(&pTop);
            if (strcmp(tokens[i], "+") == 0) {
                push = pop2 + pop1;
            } else if (strcmp(tokens[i], "-") == 0) {
                push = pop2 - pop1;
            } else if (strcmp(tokens[i], "*") == 0) {
                push = pop2 * pop1;
            } else if (strcmp(tokens[i], "/") == 0) {
                push = pop2 / pop1;
            }
        } else {
            push = atoi(tokens[i]);
        }

        stack_push(&pTop, push);
    }
    retVal = stack_pop(&pTop);

    //
    stack_free(&pTop);
    pTop = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int evalRPN(vector<string>& tokens) {
        int retVal = 0;

        stack<int> stack;
        for (string token : tokens) {
            int value = 0;

            // tokens[i] is either an operator: "+", "-", "*", or "/"
            if ((token == "+") || (token == "-") || (token == "*") || (token == "/")) {
                value = stack.top();
                stack.pop();
                if (token == "+") {
                    value = stack.top() + value;
                } else if (token == "-") {
                    value = stack.top() - value;
                } else if (token == "*") {
                    value = stack.top() * value;
                } else if (token == "/") {
                    value = stack.top() / value;
                }
                stack.pop();
            } else {
                value = stoi(token);
            }

            stack.push(value);
        }
        retVal = stack.top();

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def evalRPN(self, tokens: List[str]) -> int:
        retVal = 0

        stack = []
        for token in tokens:
            # tokens[i] is either an operator: "+", "-", "*", or "/"
            if (token == "+") or (token == "-") or (token == "*") or (token == "/"):
                if token == "+":
                    value = stack[-2] + stack[-1]
                elif token == "-":
                    value = stack[-2] - stack[-1]
                elif token == "*":
                    value = stack[-2] * stack[-1]
                elif token == "/":
                    value = stack[-2] / stack[-1]

                stack.pop()
                stack.pop()
                stack.append(int(value))
            else:
                stack.append(int(token))

        retVal = stack[0]

        return retVal
```

</details>

## [155. Min Stack](https://leetcode.com/problems/min-stack/)

- [Official](https://leetcode.cn/problems/min-stack/solutions/242190/zui-xiao-zhan-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

Implement the MinStack class:
- MinStack()
  initializes the stack object.
- void push(int val)
  pushes the element val onto the stack.
- void pop()
  removes the element on the top of the stack.
- int top()
  gets the top element of the stack.
- int getMin()
  retrieves the minimum element in the stack.

You must implement a solution with O(1) time complexity for each function.

Example 1:
Input
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]
Output
[null,null,null,null,-3,null,0,-2]
Explanation
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin(); // return -3
minStack.pop();
minStack.top();    // return 0
minStack.getMin(); // return -2

Constraints:
-2^31 <= val <= 2^31 - 1
Methods pop, top and getMin operations will always be called on non-empty stacks.
At most 3 * 10^4 calls will be made to push, pop, top, and getMin.
```

</details>

<details><summary>C</summary>

```c
typedef struct MinStack {
    int data;
    int min;
    struct MinStack *next;
} MinStack;
MinStack *top = NULL;
void show() {
    MinStack *pHead = top;
    while (pHead != NULL) {
        printf("[%d|%d] -> ", pHead->data, pHead->min);
        pHead = pHead->next;
    }
    printf("NULL\n");
}
MinStack *minStackCreate() {
    MinStack *pRetVal = (MinStack *)malloc(sizeof(struct MinStack));
    if (pRetVal == NULL) {
        perror("malloc");
    }

    return pRetVal;
}
void minStackPush(MinStack *obj, int val) {
    MinStack *pNew = (MinStack *)malloc(sizeof(struct MinStack));
    if (pNew == NULL) {
        perror("malloc");
        return;
    }
    pNew->data = val;
    pNew->min = val;
    if ((top != NULL) && (val > top->min)) {
        pNew->min = top->min;
    }
    pNew->next = top;
    top = pNew;
}
void minStackPop(MinStack *obj) {
    MinStack *pHead = top;
    if (pHead == NULL) {
        return;
    }
    top = pHead->next;
    free(pHead);
}
int minStackTop(MinStack *obj) {
    int retVal = INT_MIN;

    MinStack *pHead = top;
    if (pHead == NULL) {
        return retVal;
    }
    retVal = pHead->data;

    return retVal;
}
int minStackGetMin(MinStack *obj) {
    int retVal = INT_MIN;

    MinStack *pHead = top;
    if (pHead == NULL) {
        return retVal;
    }
    retVal = pHead->min;

    return retVal;
}
void minStackFree(MinStack *obj) {
    MinStack *pFree = NULL;
    MinStack *pNext = top;
    while (pNext != NULL) {
        pFree = pNext;
        pNext = pNext->next;
        free(pFree);
        pFree = NULL;
    }
    free(obj);
    obj = NULL;
    top = NULL;
}
/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, val);
 * minStackPop(obj);
 * int param_3 = minStackTop(obj);
 * int param_4 = minStackGetMin(obj);
 * minStackFree(obj);
 */
```

</details>

<details><summary>C++</summary>

```c++
class MinStack {
   private:
    stack<int> generalStack;
    stack<int> minStack;

   public:
    MinStack() {
        //
    }
    void push(int val) {
        generalStack.push(val);
        if (minStack.empty() == true) {
            minStack.push(val);
        } else {
            int minValue = minStack.top();
            minStack.push(min(val, minValue));
        }
    }
    void pop() {
        generalStack.pop();
        minStack.pop();
    }
    int top() {
        int retVal = generalStack.top();

        return retVal;
    }
    int getMin() {
        int retVal = minStack.top();

        return retVal;
    }
};
/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
```

</details>

<details><summary>Python3</summary>

```python
class MinStack:
    def __init__(self):
        self.stack = []
        self.minStack = []

    def push(self, val: int) -> None:
        self.stack.append(val)
        if len(self.minStack) == 0:
            self.minStack.append(val)
        else:
            self.minStack.append(min(val, self.minStack[-1]))

    def pop(self) -> None:
        self.stack.pop()
        self.minStack.pop()

    def top(self) -> int:
        retVal = self.stack[-1]

        return retVal

    def getMin(self) -> int:
        retVal = retVal = self.minStack[-1]

        return retVal

# Your MinStack object will be instantiated and called as such:
# obj = MinStack()
# obj.push(val)
# obj.pop()
# param_3 = obj.top()
# param_4 = obj.getMin()
```

</details>

## [224. Basic Calculator](https://leetcode.com/problems/basic-calculator/)

- [Official](https://leetcode.cn/problems/basic-calculator/solutions/646369/ji-ben-ji-suan-qi-by-leetcode-solution-jvir/)

<details><summary>Description</summary>

```text
Given a string s representing a valid expression,
implement a basic calculator to evaluate it, and return the result of the evaluation.

Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

Example 1:
Input: s = "1 + 1"
Output: 2

Example 2:
Input: s = " 2-1 + 2 "
Output: 3

Example 3:
Input: s = "(1+(4+5+2)-3)+(6+8)"
Output: 23

Constraints:
1 <= s.length <= 3 * 10^5
s consists of digits, '+', '-', '(', ')', and ' '.
s represents a valid expression.
'+' is not used as a unary operation (i.e., "+1" and "+(2 + 3)" is invalid).
'-' could be used as a unary operation (i.e., "-1" and "-(2 + 3)" is valid).
There will be no two consecutive operators in the input.
Every number and running calculation will fit in a signed 32-bit integer.
```

</details>

<details><summary>C</summary>

```c
int calculate(char* s) {
    int retVal = 0;

    int sSize = strlen(s);

    int stack[sSize];
    int top = 0;
    int sign = 1;
    int num = 0;
    char ch;
    int i = 0;
    for (i = 0; i < sSize; ++i) {
        ch = s[i];

        if (isdigit(ch)) {
            num = num * 10 + (ch - '0');
        } else if ((ch == '+') || (ch == '-')) {
            retVal += (sign * num);
            num = 0;
            sign = (ch == '+') ? 1 : -1;
        } else if (ch == '(') {
            stack[top++] = retVal;
            stack[top++] = sign;
            retVal = 0;
            sign = 1;
        } else if (ch == ')') {
            retVal += (sign * num);
            num = 0;
            retVal *= stack[--top];
            retVal += stack[--top];
        }
    }
    retVal += (sign * num);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int calculate(string s) {
        int retVal = 0;

        vector<int> stack;
        int sign = 1;
        int num = 0;
        for (auto ch : s) {
            if (isdigit(ch)) {
                num = num * 10 + (ch - '0');
            } else if ((ch == '+') || (ch == '-')) {
                retVal += (sign * num);
                num = 0;
                sign = (ch == '+') ? 1 : -1;
            } else if (ch == '(') {
                stack.emplace_back(retVal);
                stack.emplace_back(sign);
                retVal = 0;
                sign = 1;
            } else if (ch == ')') {
                retVal += (sign * num);
                num = 0;
                retVal *= stack.back();
                stack.pop_back();
                retVal += stack.back();
                stack.pop_back();
            }
        }
        retVal += (sign * num);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def calculate(self, s: str) -> int:
        retVal = 0

        stack = []
        sign = 1
        num = 0
        for c in s:
            if c.isdigit():
                num = num * 10 + int(c)
            elif (c == '+') or (c == '-'):
                retVal += (sign * num)
                num = 0
                sign = -1
                if c == '+':
                    sign = 1
            elif (c == '('):
                stack.append(retVal)
                stack.append(sign)
                retVal = 0
                sign = 1
            elif (c == ')'):
                retVal += (sign * num)
                num = 0
                retVal *= stack[-1]
                stack.pop()
                retVal += stack[-1]
                stack.pop()
        retVal += (sign * num)

        return retVal
```

</details>

## [225. Implement Stack using Queues](https://leetcode.com/problems/implement-stack-using-queues/)

- [Official](https://leetcode.com/problems/implement-stack-using-queues/editorial/)
- [Official](https://leetcode.cn/problems/implement-stack-using-queues/solutions/432204/yong-dui-lie-shi-xian-zhan-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Implement a last-in-first-out (LIFO) stack using only two queues.
The implemented stack should support all the functions of a normal stack (push, top, pop, and empty).

Implement the MyStack class:
void push(int x) Pushes element x to the top of the stack.
int pop() Removes the element on the top of the stack and returns it.
int top() Returns the element on the top of the stack.
boolean empty() Returns true if the stack is empty, false otherwise.

Notes:
You must use only standard operations of a queue, which means that
only push to back, peek/pop from front, size and is empty operations are valid.
Depending on your language, the queue may not be supported natively.
You may simulate a queue using a list or deque (double-ended queue) as long as you use only a queue's standard operations.

Example 1:
Input
["MyStack", "push", "push", "top", "pop", "empty"]
[[], [1], [2], [], [], []]
Output
[null, null, null, 2, 2, false]
Explanation
MyStack myStack = new MyStack();
myStack.push(1);
myStack.push(2);
myStack.top(); // return 2
myStack.pop(); // return 2
myStack.empty(); // return False

Constraints:
1 <= x <= 9
At most 100 calls will be made to push, pop, top, and empty.
All the calls to pop and top are valid.

Follow-up: Can you implement the stack using only one queue?
```

</details>

<details><summary>C</summary>

```c
#define QUEUE (1)
#if (QUEUE)
typedef struct Node {
    int data;
    struct Node* next;
} Node;
void push(struct Node** pTop, int value) {
    Node* pNew = (Node*)malloc(sizeof(struct Node));
    if (pNew == NULL) {
        perror("malloc");
        return;
    }
    pNew->data = value;
    pNew->next = NULL;

    Node* pHead = (*pTop);
    if (pHead == NULL) {
        (*pTop) = pNew;
        return;
    }

    while (pHead->next != NULL) {
        pHead = pHead->next;
    }
    pHead->next = pNew;
}
int pop(struct Node** pTop) {
    int retVal = 0;

    Node* pHead = (*pTop);
    if (pHead == NULL) {
        printf("Queue is Empty");
        return retVal;
    }
    retVal = pHead->data;
    (*pTop) = pHead->next;
    free(pHead);

    return retVal;
}
int peek(struct Node** pTop) {
    int retVal = 0;

    Node* pHead = (*pTop);
    if (pHead == NULL) {
        return retVal;
    }
    retVal = pHead->data;

    return retVal;
}
#endif
typedef struct MyStack {
    struct Node* useQueue;
    struct Node* tempQueue;
} MyStack;
MyStack* myStackCreate() {
    MyStack* pRetVal = (MyStack*)malloc(sizeof(struct MyStack));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->useQueue = NULL;
    pRetVal->tempQueue = NULL;

    return pRetVal;
}
void myStackPush(MyStack* obj, int x) {
    //
    push(&obj->useQueue, x);
}
int myStackPop(MyStack* obj) {
    int retVal = 0;

    if (obj->useQueue == NULL) {
        return retVal;
    }

    while (obj->useQueue->next != NULL) {
        retVal = pop(&obj->useQueue);
        push(&obj->tempQueue, retVal);
    }
    retVal = pop(&obj->useQueue);

    struct Node* pTmp = obj->useQueue;
    obj->useQueue = obj->tempQueue;
    obj->tempQueue = pTmp;

    return retVal;
}
int myStackTop(MyStack* obj) {
    int retVal = 0;

    if (obj->useQueue == NULL) {
        return retVal;
    }

    while (obj->useQueue->next != NULL) {
        retVal = pop(&obj->useQueue);
        push(&obj->tempQueue, retVal);
    }
    retVal = pop(&obj->useQueue);
    push(&obj->tempQueue, retVal);

    struct Node* pTmp = obj->useQueue;
    obj->useQueue = obj->tempQueue;
    obj->tempQueue = pTmp;

    return retVal;
}
bool myStackEmpty(MyStack* obj) {
    bool retVal = false;

    if ((obj->useQueue == NULL) && (obj->tempQueue == NULL)) {
        retVal = true;
    }

    return retVal;
}
void myStackFree(MyStack* obj) {
    free(obj->useQueue);
    obj->useQueue = NULL;
    free(obj->tempQueue);
    obj->tempQueue = NULL;
    free(obj);
    obj = NULL;
}
/**
 * Your MyStack struct will be instantiated and called as such:
 * MyStack* obj = myStackCreate();
 * myStackPush(obj, x);
 * int param_2 = myStackPop(obj);
 * int param_3 = myStackTop(obj);
 * bool param_4 = myStackEmpty(obj);
 * myStackFree(obj);
 */
```

</details>

<details><summary>C++</summary>

```c++
class MyStack {
   public:
    queue<int> useQueue;
    queue<int> tempQueue;
    MyStack() {
        //
    }
    void push(int x) {
        tempQueue.push(x);
        while (useQueue.empty() == false) {
            tempQueue.push(useQueue.front());
            useQueue.pop();
        }
        swap(useQueue, tempQueue);
    }
    int pop() {
        int retVal = useQueue.front();

        useQueue.pop();

        return retVal;
    }
    int top() {
        int retVal = useQueue.front();

        return retVal;
    }
    bool empty() {
        bool retVal = false;

        if (useQueue.empty() == true) {
            retVal = true;
        }

        return retVal;
    }
};
/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
```

</details>

<details><summary>Python3</summary>

```python
class MyStack:
    def __init__(self):
        self.useQueue = deque()
        self.tempQueue = deque()

    def push(self, x: int) -> None:
        self.tempQueue.append(x)
        while self.useQueue:
            self.tempQueue.append(self.useQueue.popleft())

        self.useQueue, self.tempQueue = self.tempQueue, self.useQueue

    def pop(self) -> int:
        retVal = self.useQueue.popleft()

        return retVal

    def top(self) -> int:
        retVal = self.useQueue[0]

        return retVal

    def empty(self) -> bool:
        retVal = True
        if self.useQueue:
            retVal = False

        return retVal

# Your MyStack object will be instantiated and called as such:
# obj = MyStack()
# obj.push(x)
# param_2 = obj.pop()
# param_3 = obj.top()
# param_4 = obj.empty()
```

</details>

## [316. Remove Duplicate Letters](https://leetcode.com/problems/remove-duplicate-letters/)

- [Official](https://leetcode.cn/problems/remove-duplicate-letters/solutions/527359/qu-chu-zhong-fu-zi-mu-by-leetcode-soluti-vuso/)

<details><summary>Description</summary>

```text
Given a string s, remove duplicate letters so that every letter appears once and only once.
You must make sure your result is the smallest in lexicographical order among all possible results.

Example 1:
Input: s = "bcabc"
Output: "abc"

Example 2:
Input: s = "cbacdcbc"
Output: "acdb"

Constraints:
1 <= s.length <= 10^4
s consists of lowercase English letters.

Note: This question is the same as 1081: https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/
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
char *removeDuplicateLetters(char *s) {
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
    def removeDuplicateLetters(self, s: str) -> str:
        retVal = None

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

## [341. Flatten Nested List Iterator](https://leetcode.com/problems/flatten-nested-list-iterator/)

- [Official](https://leetcode.cn/problems/flatten-nested-list-iterator/solutions/674229/bian-ping-hua-qian-tao-lie-biao-die-dai-ipjzq/)

<details><summary>Description</summary>

```text
You are given a nested list of integers nestedList.
Each element is either an integer or a list whose elements may also be integers or other lists.
Implement an iterator to flatten it.

Implement the NestedIterator class:
- NestedIterator(List<NestedInteger> nestedList)
  - Initializes the iterator with the nested list nestedList.
- int next()
  - Returns the next integer in the nested list.
- boolean hasNext()
  - Returns true if there are still some integers in the nested list and false otherwise.

Your code will be tested with the following pseudocode:
  initialize iterator with nestedList
  res = []
  while iterator.hasNext()
      append iterator.next() to the end of res
  return res

If res matches the expected flattened list, then your code will be judged as correct.

Example 1:
Input: nestedList = [[1,1],2,[1,1]]
Output: [1,1,2,1,1]
Explanation: By calling next repeatedly until hasNext returns false,
the order of elements returned by next should be: [1,1,2,1,1].

Example 2:
Input: nestedList = [1,[4,[6]]]
Output: [1,4,6]
Explanation: By calling next repeatedly until hasNext returns false,
the order of elements returned by next should be: [1,4,6].

Constraints:
1 <= nestedList.length <= 500
The values of the integers in the nested list is in the range [-10^6, 10^6].
```

</details>

<details><summary>C</summary>

```c
/**
 * *********************************************************************
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * *********************************************************************
 *
 * // Return true if this NestedInteger holds a single integer, rather than a nested list.
 * bool NestedIntegerIsInteger(struct NestedInteger *);
 *
 * // Return the single integer that this NestedInteger holds, if it holds a single integer
 * // The result is undefined if this NestedInteger holds a nested list
 * int NestedIntegerGetInteger(struct NestedInteger *);
 *
 * // Return the nested list that this NestedInteger holds, if it holds a nested list
 * // The result is undefined if this NestedInteger holds a single integer
 * struct NestedInteger **NestedIntegerGetList(struct NestedInteger *);
 *
 * // Return the nested list's size that this NestedInteger holds, if it holds a nested list
 * // The result is undefined if this NestedInteger holds a single integer
 * int NestedIntegerGetListSize(struct NestedInteger *);
 * };
 */

#define MAX (12000)
struct NestedIterator {
    struct NestedInteger **stack;
    int top;
};
struct NestedIterator *nestedIterCreate(struct NestedInteger **nestedList, int nestedListSize) {
    struct NestedIterator *iter = (struct NestedIterator *)malloc(sizeof(struct NestedIterator));
    if (iter == NULL) {
        return NULL;
    }

    iter->stack = (struct NestedInteger **)malloc(sizeof(struct NestedInteger *) * MAX);
    if (iter->stack == NULL) {
        free(iter);
        return NULL;
    }
    iter->top = 0;

    for (int i = nestedListSize - 1; i >= 0; i--) {
        iter->stack[iter->top++] = nestedList[i];
    }

    return iter;
}
bool nestedIterHasNext(struct NestedIterator *iter) {
    bool retVal = false;

    if (iter->top <= 0) {
        return retVal;
    }

    if (NestedIntegerIsInteger(iter->stack[iter->top - 1])) {
        retVal = true;
        return retVal;
    }

    while (iter->top > 0 && (NestedIntegerIsInteger(iter->stack[iter->top - 1]) == false)) {
        struct NestedInteger *topNode = iter->stack[iter->top - 1];
        struct NestedInteger **nestedList = NestedIntegerGetList(topNode);
        int nestedListSize = NestedIntegerGetListSize(topNode);

        iter->top--;
        for (int i = nestedListSize - 1; i >= 0; i--) {
            iter->stack[iter->top++] = nestedList[i];
        }
    }

    if ((iter->top > 0) && (NestedIntegerIsInteger(iter->stack[iter->top - 1]) == true)) {
        retVal = true;
    }

    return retVal;
}
int nestedIterNext(struct NestedIterator *iter) {
    int retVal = 0;

    retVal = NestedIntegerGetInteger(iter->stack[--iter->top]);

    return retVal;
}
void nestedIterFree(struct NestedIterator *iter) {
    if (iter == NULL) {
        return;
    }

    if (iter->stack != NULL) {
        free(iter->stack);
        iter->stack = NULL;
    }
    free(iter);
    iter = NULL;
}

/**
 * Your NestedIterator will be called like this:
 * struct NestedIterator *i = nestedIterCreate(nestedList, nestedListSize);
 * while (nestedIterHasNext(i)) printf("%d\n", nestedIterNext(i));
 * nestedIterFree(i);
 */
```

</details>

<details><summary>C++</summary>

```c++
/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */

class NestedIterator {
   private:
    stack<vector<NestedInteger>::iterator> begins, ends;

   public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        begins.push(nestedList.begin());
        ends.push(nestedList.end());
    }
    int next() {
        int retVal = 0;

        hasNext();
        retVal = (begins.top()++)->getInteger();

        return retVal;
    }
    bool hasNext() {
        bool retVal = false;

        while (begins.size()) {
            if (begins.top() == ends.top()) {
                begins.pop();
                ends.pop();
                continue;
            }

            auto x = begins.top();
            if (x->isInteger()) {
                retVal = true;
                break;
            }

            begins.top()++;
            begins.push(x->getList().begin());
            ends.push(x->getList().end());
        }

        return retVal;
    }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
```

</details>

<details><summary>Python3</summary>

```python
# """
# This is the interface that allows for creating nested lists.
# You should not implement it, or speculate about its implementation
# """
# class NestedInteger:
#    def isInteger(self) -> bool:
#        """
#        @return True if this NestedInteger holds a single integer, rather than a nested list.
#        """
#
#    def getInteger(self) -> int:
#        """
#        @return the single integer that this NestedInteger holds, if it holds a single integer
#        Return None if this NestedInteger holds a nested list
#        """
#
#    def getList(self) -> [NestedInteger]:
#        """
#        @return the nested list that this NestedInteger holds, if it holds a nested list
#        Return None if this NestedInteger holds a single integer
#        """


class NestedIterator:
    def __init__(self, nestedList: [NestedInteger]):
        self.stack = [[nestedList, 0]]

    def next(self) -> int:
        retVal = 0

        self.hasNext()
        nestedList, i = self.stack[-1]
        self.stack[-1][1] += 1
        retVal = nestedList[i].getInteger()

        return retVal

    def hasNext(self) -> bool:
        retVal = False

        s = self.stack
        while s:
            nestedList, i = s[-1]
            if i == len(nestedList):
                s.pop()
                continue

            x = nestedList[i]
            if x.isInteger():
                retVal = True
                break
            s[-1][1] += 1
            s.append([x.getList(), 0])

        return retVal


# Your NestedIterator object will be instantiated and called as such:
# i, v = NestedIterator(nestedList), []
# while i.hasNext(): v.append(i.next())
```

</details>

## [394. Decode String](https://leetcode.com/problems/decode-string/)

- [Official](https://leetcode.cn/problems/decode-string/solutions/264391/zi-fu-chuan-jie-ma-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given an encoded string, return its decoded string.

The encoding rule is: k[encoded_string],
where the encoded_string inside the square brackets is being repeated exactly k times.
Note that k is guaranteed to be a positive integer.

You may assume that the input string is always valid;
there are no extra white spaces, square brackets are well-formed, etc.
Furthermore,
you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k.
For example, there will not be input like 3a or 2[4].

The test cases are generated so that the length of the output will never exceed 10^5.

Example 1:
Input: s = "3[a]2[bc]"
Output: "aaabcbc"

Example 2:
Input: s = "3[a2[c]]"
Output: "accaccacc"

Example 3:
Input: s = "2[abc]3[cd]ef"
Output: "abcabccdcdcdef"

Constraints:
1 <= s.length <= 30
s consists of lowercase English letters, digits, and square brackets '[]'.
s is guaranteed to be a valid input.
All the integers in s are in the range [1, 300].
```

</details>

<details><summary>C</summary>

```c
char* decodeString(char* s) {
    char* pRetVal = NULL;

// The test cases are generated so that the length of the output will never exceed 10^5.
#define MAX_OUTPUT_LENGTH (100000)
    pRetVal = (char*)malloc(MAX_OUTPUT_LENGTH * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, MAX_OUTPUT_LENGTH * sizeof(char));
    int returnSize = 0;

    char* pStack = (char*)malloc(MAX_OUTPUT_LENGTH * sizeof(char));
    if (pStack == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset(pStack, 0, MAX_OUTPUT_LENGTH * sizeof(char));
    int stackSize = 0;

    int len = strlen(s);
    char pNumber[len];
    int numberSize;
    int number;
    char tmp[len];

    int i, j;
    for (i = 0; i < len; ++i) {
        if (s[i] != ']') {
            pStack[stackSize++] = s[i];
            continue;
        }

        memset(pRetVal, 0, MAX_OUTPUT_LENGTH * sizeof(char));
        returnSize = 0;
        while (pStack[--stackSize] != '[') {
            pRetVal[returnSize++] = pStack[stackSize];
            pStack[stackSize] = 0;
        }
        pStack[stackSize] = 0;

        memset(pNumber, 0, sizeof(pNumber));
        numberSize = 0;
        while ((stackSize != 0) && (isdigit(pStack[stackSize - 1]))) {
            pNumber[numberSize++] = pStack[--stackSize];
            pStack[stackSize] = 0;
        }
        memset(tmp, 0, sizeof(tmp));
        snprintf(tmp, sizeof(tmp), "%s", pNumber);
        for (j = 0; j < numberSize; ++j) {
            pNumber[numberSize - 1 - j] = tmp[j];
        }
        number = atoi(pNumber);
        while (number--) {
            for (j = returnSize - 1; j >= 0; --j) {
                pStack[stackSize++] = pRetVal[j];
            }
        }
    }
    memset(pRetVal, 0, MAX_OUTPUT_LENGTH * sizeof(char));
    returnSize = stackSize;
    memcpy(pRetVal, pStack, stackSize);

    free(pStack);
    pStack = NULL;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string decodeString(string s) {
        string retVal = "";

        stack<char> record;
        int repeatTimes;
        for (char c : s) {
            if (c != ']') {
                record.push(c);
                continue;
            }

            string currentString = "";
            while (record.top() != '[') {
                currentString = record.top() + currentString;
                record.pop();
            }
            record.pop();

            string number = "";
            while ((record.empty() == false) && (isdigit(record.top()))) {
                number = record.top() + number;
                record.pop();
            }

            repeatTimes = stoi(number);
            while (repeatTimes--) {
                for (char currentChar : currentString) {
                    record.push(currentChar);
                }
            }
        }

        while (record.empty() == false) {
            retVal = record.top() + retVal;
            record.pop();
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def decodeString(self, s: str) -> str:
        retVal = ""

        stack = []
        for c in s:
            if c != ']':
                stack.append(c)
                continue

            currentString = ""
            while stack[-1] != '[':
                currentString = stack[-1] + currentString
                stack.pop()
            stack.pop()

            number = ""
            while stack and stack[-1].isdigit():
                number = stack[-1] + number
                stack.pop()

            repeatTimes = int(number)
            while repeatTimes > 0:
                for currentChar in currentString:
                    stack.append(currentChar)
                repeatTimes -= 1

        retVal = retVal.join(stack)

        return retVal
```

</details>

## [456. 132 Pattern](https://leetcode.com/problems/132-pattern/)

- [Official](https://leetcode.com/problems/132-pattern/editorial/)
- [Official](https://leetcode.cn/problems/132-pattern/solutions/676437/132mo-shi-by-leetcode-solution-ye89/)

<details><summary>Description</summary>

```text
Given an array of n integers nums, a 132 pattern is a subsequence of
three integers nums[i], nums[j] and nums[k] such that i < j < k and nums[i] < nums[k] < nums[j].

Return true if there is a 132 pattern in nums, otherwise, return false.

Example 1:
Input: nums = [1,2,3,4]
Output: false
Explanation: There is no 132 pattern in the sequence.

Example 2:
Input: nums = [3,1,4,2]
Output: true
Explanation: There is a 132 pattern in the sequence: [1, 4, 2].

Example 3:
Input: nums = [-1,3,2,0]
Output: true
Explanation: There are three 132 patterns in the sequence: [-1, 3, 2], [-1, 3, 0] and [-1, 2, 0].

Constraints:
n == nums.length
1 <= n <= 2 * 10^5
-10^9 <= nums[i] <= 10^9
```

</details>

<details><summary>C</summary>

```c
bool find132pattern(int* nums, int numsSize) {
    bool retVal = false;

    if (numsSize < 3) {
        return retVal;
    }

    int i;

    int minStack[numsSize];
    memset(minStack, 0, sizeof(minStack));
    minStack[0] = nums[0];
    for (i = 1; i < numsSize; ++i) {
        minStack[i] = fmin(minStack[i - 1], nums[i]);
    }

    int middleStack[numsSize];
    memset(middleStack, 0, sizeof(middleStack));
    int middleStackSize = 0;
    for (i = numsSize - 1; i > -1; --i) {
        if (nums[i] <= minStack[i]) {
            continue;
        }

        while ((middleStackSize > 0) && (middleStack[middleStackSize - 1] <= minStack[i])) {
            middleStack[middleStackSize - 1] = 0;
            --middleStackSize;
        }

        if ((middleStackSize > 0) && (middleStack[middleStackSize - 1] < nums[i])) {
            retVal = true;
            break;
        }

        middleStack[middleStackSize] = nums[i];
        ++middleStackSize;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    bool find132pattern(vector<int>& nums) {
        bool retVal = false;

        int numsSize = nums.size();
        if (numsSize < 3) {
            return retVal;
        }

        vector<int> minStack;
        minStack.emplace_back(nums[0]);
        for (int i = 1; i < numsSize; ++i) {
            minStack.emplace_back(min(minStack[i - 1], nums[i]));
        }

        vector<int> middleStack;
        int middleStackSize = 0;
        for (int i = numsSize - 1; i > -1; --i) {
            if (nums[i] <= minStack[i]) {
                continue;
            }

            while ((middleStackSize > 0) && (middleStack.back() <= minStack[i])) {
                middleStack.pop_back();
                --middleStackSize;
            }

            if ((middleStackSize > 0) && (middleStack.back() < nums[i])) {
                retVal = true;
                break;
            }

            middleStack.emplace_back(nums[i]);
            ++middleStackSize;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def find132pattern(self, nums: List[int]) -> bool:
        retVal = False

        numsSize = len(nums)
        if numsSize < 3:
            return retVal

        minStack = [nums[0]]
        for i in range(1, numsSize):
            minStack.append(min(minStack[i-1], nums[i]))

        middleStack = []
        for i in range(numsSize - 1, -1, -1):
            if nums[i] <= minStack[i]:
                continue

            while (middleStack) and (middleStack[-1] <= minStack[i]):
                middleStack.pop()

            if (middleStack) and (middleStack[-1] < nums[i]):
                retVal = True
                break

            middleStack.append(nums[i])

        return retVal
```

</details>

## [496. Next Greater Element I](https://leetcode.com/problems/next-greater-element-i/)

<details><summary>Description</summary>

```text
The next greater element of some element x in an array is the first greater element
that is to the right of x in the same array.

You are given two distinct 0-indexed integer arrays nums1 and nums2, where nums1 is a subset of nums2.

For each 0 <= i < nums1.length, find the index j such that nums1[i] == nums2[j]
and determine the next greater element of nums2[j] in nums2.
If there is no next greater element, then the answer for this query is -1.

Return an array ans of length nums1.length such that ans[i] is the next greater element as described above.

Example 1:
Input: nums1 = [4,1,2], nums2 = [1,3,4,2]
Output: [-1,3,-1]
Explanation: The next greater element for each value of nums1 is as follows:
- 4 is underlined in nums2 = [1,3,4,2]. There is no next greater element, so the answer is -1.
- 1 is underlined in nums2 = [1,3,4,2]. The next greater element is 3.
- 2 is underlined in nums2 = [1,3,4,2]. There is no next greater element, so the answer is -1.

Example 2:
Input: nums1 = [2,4], nums2 = [1,2,3,4]
Output: [3,-1]
Explanation: The next greater element for each value of nums1 is as follows:
- 2 is underlined in nums2 = [1,2,3,4]. The next greater element is 3.
- 4 is underlined in nums2 = [1,2,3,4]. There is no next greater element, so the answer is -1.

Constraints:
1 <= nums1.length <= nums2.length <= 1000
0 <= nums1[i], nums2[i] <= 10^4
All integers in nums1 and nums2 are unique.
All the integers of nums1 also appear in nums2.

Follow up: Could you find an O(nums1.length + nums2.length) solution?
```

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* nextGreaterElement(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    int* pRetVal = NULL;
    (*returnSize) = nums1Size;

    // prepare return array
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));

    // record the next greater element of nums2 array
#define RECORD_SIZE (10000)
    int Record[RECORD_SIZE];
    memset(Record, -1, sizeof(Record));
    int i, j;
    for (i = 0; i < nums2Size; ++i) {
        for (j = i; j < nums2Size; ++j) {
            if (nums2[i] < nums2[j]) {
                Record[nums2[i]] = nums2[j];
                break;
            }
        }
    }

    // nums1 array map to nums2 record of the next greater element
    for (i = 0; i < nums1Size; ++i) {
        pRetVal[i] = Record[nums1[i]];
    }

    return pRetVal;
}
```

</details>

## [726. Number of Atoms](https://leetcode.com/problems/number-of-atoms/)

- [Official](https://leetcode.com/problems/number-of-atoms/editorial/)
- [Official](https://leetcode.cn/problems/number-of-atoms/solutions/858790/yuan-zi-de-shu-liang-by-leetcode-solutio-54lv/)

<details><summary>Description</summary>

```text
Given a string formula representing a chemical formula, return the count of each atom.

The atomic element always starts with an uppercase character, then zero or more lowercase letters,
representing the name.

One or more digits representing that element's count may follow if the count is greater than 1.
If the count is 1, no digits will follow.
- For example, "H2O" and "H2O2" are possible, but "H1O2" is impossible.

Two formulas are concatenated together to produce another formula.
- For example, "H2O2He3Mg4" is also a formula.

A formula placed in parentheses, and a count (optionally added) is also a formula.
- For example, "(H2O2)" and "(H2O2)3" are formulas.

Return the count of all elements as a string in the following form: the first name (in sorted order),
followed by its count (if that count is more than 1), followed by the second name (in sorted order),
followed by its count (if that count is more than 1), and so on.

The test cases are generated so that all the values in the output fit in a 32-bit integer.

Example 1:
Input: formula = "H2O"
Output: "H2O"
Explanation: The count of elements are {'H': 2, 'O': 1}.

Example 2:
Input: formula = "Mg(OH)2"
Output: "H2MgO2"
Explanation: The count of elements are {'H': 2, 'Mg': 1, 'O': 2}.

Example 3:
Input: formula = "K4(ON(SO3)2)2"
Output: "K4N2O14S4"
Explanation: The count of elements are {'K': 4, 'N': 2, 'O': 14, 'S': 4}.

Constraints:
1 <= formula.length <= 1000
formula consists of English letters, digits, '(', and ')'.
formula is always valid.
```

<details><summary>Hint</summary>

```text
1. To parse formula[i:], when we see a `'('`, we will parse recursively
   whatever is inside the brackets (up to the correct closing ending bracket) and add it to our count,
   multiplying by the following multiplicity if there is one.
   Otherwise, we should see an uppercase character:
   we will parse the rest of the letters to get the name, and add that (plus the multiplicity if there is one.)
```

</details>

</details>

<details><summary>C</summary>

```c
// https://leetcode.cn/problems/number-of-atoms/solutions/95872/c-jian-dan-de-cong-you-xiang-zuo-bian-li-fen-qing-/
char* countOfAtoms(char* formula) {
    char* pRetVal = NULL;

    int returnSize = 1001;  // 1 <= formula.length <= 1000
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));

    int formulaSize = strlen(formula);
    int i, j;

#define LETTERS_SIZE (26)  // formula consists of English letters, digits, '(', and')'.
    int store[LETTERS_SIZE][LETTERS_SIZE + 1];
    memset(store, 0, sizeof(store));

    int stack[formulaSize + 1];
    memset(stack, 0, sizeof(stack));

    int digit = 1;
    int top = 0;
    int numTemp = 0;
    int coefficient = 1;
    for (i = formulaSize - 1; i >= 0;) {
        if (isdigit(formula[i])) {
            digit = 1;
            numTemp += ((formula[i] - '0') * digit);
            while (isdigit(formula[--i])) {
                digit *= 10;
                numTemp += ((formula[i] - '0') * digit);
            }
            coefficient *= numTemp;
            stack[top++] = numTemp;
        }

        if (formula[i] == ')') {
            numTemp = 0;
        } else if (formula[i] == '(') {
            if (top > 0) {
                coefficient /= stack[--top];
            }
        } else if (isupper(formula[i])) {
            store[formula[i] - 'A'][0] += 1 * coefficient;
            if (numTemp != 0) {
                coefficient /= stack[--top];
                numTemp = 0;
            }
        } else if (islower(formula[i])) {
            store[formula[i - 1] - 'A'][formula[i] - 'a' + 1] += (1 * coefficient);
            if (numTemp != 0) {
                coefficient /= stack[--top];
                numTemp = 0;
            }
            i--;
        }

        i--;
    }

    int tail = 0;
    for (i = 0; i < LETTERS_SIZE; i++) {
        if (store[i][0] == 1) {
            tail += sprintf(pRetVal + tail, "%c", i + 'A');
        } else if (store[i][0] > 1) {
            tail += sprintf(pRetVal + tail, "%c%d", i + 'A', store[i][0]);
        }

        for (j = 1; j <= LETTERS_SIZE; j++) {
            if (store[i][j] == 1) {
                tail += sprintf(pRetVal + tail, "%c%c", i + 'A', j - 1 + 'a');
            } else if (store[i][j] > 1) {
                tail += sprintf(pRetVal + tail, "%c%c%d", i + 'A', j - 1 + 'a', store[i][j]);
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
    string countOfAtoms(string formula) {
        string retVal = "";

        int formulaSize = formula.size();

        stack<unordered_map<string, int>> stack;
        stack.push(unordered_map<string, int>());

        int index = 0;
        while (index < formulaSize) {
            if (formula[index] == '(') {
                // If left parenthesis, insert a new hashmap to the stack.
                // It will keep track of the atoms and their counts in the nested formula
                stack.push(unordered_map<string, int>());
                index++;
            } else if (formula[index] == ')') {
                // If right parenthesis, pop the top element from the stack.
                // Multiply the count with the multiplicity of the nested formula
                unordered_map<string, int> currMap = stack.top();
                stack.pop();

                index++;
                string multiplier;
                while ((index < formulaSize) && (isdigit(formula[index]))) {
                    multiplier += formula[index];
                    index++;
                }
                if (multiplier.empty() == false) {
                    int mult = stoi(multiplier);
                    for (auto& [atom, count] : currMap) {
                        currMap[atom] = count * mult;
                    }
                }

                for (auto& [atom, count] : currMap) {
                    stack.top()[atom] += count;
                }
            } else {
                // Otherwise, it must be a UPPERCASE LETTER.
                // Extract the complete atom with frequency, and update the most recent hashmap
                string currAtom;
                currAtom += formula[index];
                index++;
                while ((index < formulaSize) && (islower(formula[index]))) {
                    currAtom += formula[index];
                    index++;
                }

                string currCount;
                while ((index < formulaSize) && (isdigit(formula[index]))) {
                    currCount += formula[index];
                    index++;
                }

                int count = currCount.empty() ? 1 : stoi(currCount);
                stack.top()[currAtom] += count;
            }
        }

        map<string, int> finalMap(stack.top().begin(), stack.top().end());
        string ans;
        for (auto& [atom, count] : finalMap) {
            retVal += atom;
            if (count > 1) {
                retVal += to_string(count);
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
    def countOfAtoms(self, formula: str) -> str:
        retVal = ""

        formulaSize = len(formula)

        stack = [defaultdict(int)]
        index = 0
        while index < formulaSize:
            if formula[index] == "(":
                # If left parenthesis, insert a new hashmap to the stack.
                # It will keep track of the atoms and their counts in the nested formula
                stack.append(defaultdict(int))
                index += 1
            elif formula[index] == ")":
                # If right parenthesis, pop the top element from the stack.
                # Multiply the count with the multiplicity of the nested formula
                currMap = stack.pop()

                index += 1
                multiplier = ""
                while (index < formulaSize) and (formula[index].isdigit()):
                    multiplier += formula[index]
                    index += 1
                if multiplier:
                    multiplier = int(multiplier)
                    for atom in currMap:
                        currMap[atom] *= multiplier

                for atom in currMap:
                    stack[-1][atom] += currMap[atom]
            else:
                # Otherwise, it must be a UPPERCASE LETTER. Extract the complete
                # atom with frequency, and update the most recent hashmap
                currAtom = formula[index]
                index += 1
                while (index < formulaSize) and (formula[index].islower()):
                    currAtom += formula[index]
                    index += 1

                currCount = ""
                while (index < formulaSize) and (formula[index].isdigit()):
                    currCount += formula[index]
                    index += 1

                if currCount == "":
                    stack[-1][currAtom] += 1
                else:
                    stack[-1][currAtom] += int(currCount)

        finalMap = dict(sorted(stack[0].items()))
        for atom in finalMap:
            retVal += atom
            if finalMap[atom] > 1:
                retVal += str(finalMap[atom])

        return retVal
```

</details>

## [735. Asteroid Collision](https://leetcode.com/problems/asteroid-collision/)

- [Official](https://leetcode.com/problems/asteroid-collision/editorial/)
- [Official](https://leetcode.cn/problems/asteroid-collision/solutions/1663442/xing-xing-peng-zhuang-by-leetcode-soluti-u3k0/)

<details><summary>Description</summary>

```text
We are given an array asteroids of integers representing asteroids in a row.

For each asteroid, the absolute value represents its size,
and the sign represents its direction (positive meaning right, negative meaning left).
Each asteroid moves at the same speed.

Find out the state of the asteroids after all collisions.
If two asteroids meet, the smaller one will explode. If both are the same size, both will explode.
Two asteroids moving in the same direction will never meet.

Example 1:
Input: asteroids = [5,10,-5]
Output: [5,10]
Explanation: The 10 and -5 collide resulting in 10. The 5 and 10 never collide.

Example 2:
Input: asteroids = [8,-8]
Output: []
Explanation: The 8 and -8 collide exploding each other.

Example 3:
Input: asteroids = [10,2,-5]
Output: [10]
Explanation: The 2 and -5 collide resulting in -5. The 10 and -5 collide resulting in 10.

Constraints:
2 <= asteroids.length <= 10^4
-1000 <= asteroids[i] <= 1000
asteroids[i] != 0
```

<details><summary>Hint</summary>

```text
1. Say a row of asteroids is stable. What happens when a new asteroid is added on the right?
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *asteroidCollision(int *asteroids, int asteroidsSize, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int *)malloc(asteroidsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (asteroidsSize * sizeof(int)));

    int currentAsteroidSize, previousAsteroidSize;
    int i;
    for (i = 0; i < asteroidsSize; ++i) {
        currentAsteroidSize = abs(asteroids[i]);
        while (((*returnSize) != 0) && (pRetVal[(*returnSize) - 1] > 0) && (asteroids[i] < 0)) {
            previousAsteroidSize = abs(pRetVal[(*returnSize) - 1]);
            if (previousAsteroidSize > currentAsteroidSize) {
                currentAsteroidSize = -1;
                break;
            } else if (previousAsteroidSize == currentAsteroidSize) {
                currentAsteroidSize = -1;
                (*returnSize)--;
                break;
            } else if (previousAsteroidSize < currentAsteroidSize) {
                (*returnSize)--;
            }
        }
        if (currentAsteroidSize != -1) {
            pRetVal[(*returnSize)++] = asteroids[i];
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
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> retVal;

        for (auto asteroid : asteroids) {
            int currentAsteroidSize = abs(asteroid);
            while ((retVal.empty() == false) && (retVal.back() > 0) && (asteroid < 0)) {
                int previousAsteroidSize = abs(retVal.back());
                if (previousAsteroidSize > currentAsteroidSize) {
                    currentAsteroidSize = -1;
                    break;
                } else if (previousAsteroidSize == currentAsteroidSize) {
                    currentAsteroidSize = -1;
                    retVal.pop_back();
                    break;
                } else if (previousAsteroidSize < currentAsteroidSize) {
                    retVal.pop_back();
                }
            }
            if (currentAsteroidSize != -1) {
                retVal.emplace_back(asteroid);
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
    def asteroidCollision(self, asteroids: List[int]) -> List[int]:
        retVal = []

        for asteroid in asteroids:
            currentAsteroidSize = abs(asteroid)
            while (retVal) and (retVal[-1] > 0) and (asteroid < 0):
                previousAsteroidSize = abs(retVal[-1])
                if previousAsteroidSize > currentAsteroidSize:
                    currentAsteroidSize = -1
                    break
                elif previousAsteroidSize == currentAsteroidSize:
                    currentAsteroidSize = -1
                    retVal.pop()
                    break
                elif previousAsteroidSize < currentAsteroidSize:
                    retVal.pop()

            if currentAsteroidSize != -1:
                retVal.append(asteroid)

        return retVal
```

</details>

## [739. Daily Temperatures](https://leetcode.com/problems/daily-temperatures/)

- [Official](https://leetcode.cn/problems/daily-temperatures/solutions/283196/mei-ri-wen-du-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given an array of integers temperatures represents the daily temperatures,
return an array answer such that answer[i] is the number of days
you have to wait after the ith day to get a warmer temperature.
If there is no future day for which this is possible, keep answer[i] == 0 instead.

Example 1:
Input: temperatures = [73,74,75,71,69,72,76,73]
Output: [1,1,4,2,1,1,0,0]

Example 2:
Input: temperatures = [30,40,50,60]
Output: [1,1,1,0]

Example 3:
Input: temperatures = [30,60,90]
Output: [1,1,0]

Constraints:
1 <= temperatures.length <= 10^5
30 <= temperatures[i] <= 100
```

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int*)malloc(temperaturesSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (temperaturesSize * sizeof(int)));

    int MonotonicStack[temperaturesSize];
    memset(MonotonicStack, 0, sizeof(MonotonicStack));
    int pTop = -1;

    int i;
    for (i = 0; i < temperaturesSize; ++i) {
        while ((pTop != -1) && (temperatures[i] > temperatures[MonotonicStack[pTop]])) {
            pRetVal[MonotonicStack[pTop]] = i - MonotonicStack[pTop];
            MonotonicStack[pTop] = 0;
            --pTop;
        }

        ++pTop;
        MonotonicStack[pTop] = i;
    }
    (*returnSize) = temperaturesSize;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> retVal;

        int temperaturesSize = temperatures.size();
        retVal.resize(temperaturesSize, 0);

        stack<int> monotonicStack;
        for (int i = 0; i < temperaturesSize; ++i) {
            while ((monotonicStack.empty() == false) && (temperatures[i] > temperatures[monotonicStack.top()])) {
                int previousIdx = monotonicStack.top();
                retVal[previousIdx] = i - previousIdx;
                monotonicStack.pop();
            }
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
    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
        retVal = []

        temperaturesSize = len(temperatures)
        retVal = [0] * temperaturesSize

        stack = []
        for idx, temperature in enumerate(temperatures):
            while stack and temperature > temperatures[stack[-1]]:
                previousIdx = stack.pop()
                retVal[previousIdx] = idx - previousIdx
            stack.append(idx)

        return retVal
```

</details>

## [844. Backspace String Compare](https://leetcode.com/problems/backspace-string-compare/)  1227

- [Official](https://leetcode.com/problems/backspace-string-compare/editorial/)
- [Official](https://leetcode.cn/problems/backspace-string-compare/solutions/451606/bi-jiao-han-tui-ge-de-zi-fu-chuan-by-leetcode-solu/)

<details><summary>Description</summary>

```text
Given two strings s and t, return true if they are equal when both are typed into empty text editors.
'#' means a backspace character.

Note that after backspacing an empty text, the text will continue empty.

Example 1:
Input: s = "ab#c", t = "ad#c"
Output: true
Explanation: Both s and t become "ac".

Example 2:
Input: s = "ab##", t = "c#d#"
Output: true
Explanation: Both s and t become "".

Example 3:
Input: s = "a#c", t = "b"
Output: false
Explanation: s becomes "c" while t becomes "b".

Constraints:
1 <= s.length, t.length <= 200
s and t only contain lowercase letters and '#' characters.

Follow up: Can you solve it in O(n) time and O(1) space?
```

</details>

<details><summary>C</summary>

```c
void methodStack(char* s, char* returnS) {
    int sSize = strlen(s);
    int idx = 0;
    int i;
    for (i = 0; i < sSize; ++i) {
        if (s[i] != '#') {
            returnS[idx++] = s[i];
        } else if (idx > 0) {
            returnS[--idx] = 0;
        }
    }
}
bool methodTwoPointer(char* s, char* t) {
    bool retVal = false;

    int skipS = 0;
    int skipT = 0;

    int i = strlen(s) - 1;
    int j = strlen(t) - 1;
    while ((i >= 0) || (j >= 0)) {
        while (i >= 0) {
            if (s[i] == '#') {
                skipS += 1;
                i--;
            } else if (skipS > 0) {
                skipS -= 1;
                i--;
            } else {
                break;
            }
        }

        while (j >= 0) {
            if (t[j] == '#') {
                skipT += 1;
                j--;
            } else if (skipT > 0) {
                skipT -= 1;
                j--;
            } else {
                break;
            }
        }

        if ((i >= 0) && (j >= 0)) {
            if (s[i] != t[j]) {
                return retVal;
            }
        } else if ((i >= 0) || (j >= 0)) {
            return retVal;
        }

        i--;
        j--;
    }
    retVal = true;

    return retVal;
}
bool backspaceCompare(char* s, char* t) {
    bool retVal = false;

#if (0)
    int sSize = strlen(s);
    char stackS[sSize + 1];
    memset(stackS, 0, sizeof(stackS));
    methodStack(s, stackS);

    int tSize = strlen(t);
    char stackT[tSize + 1];
    memset(stackT, 0, sizeof(stackT));
    methodStack(t, stackT);

    if (strcmp(stackS, stackT) == 0) {
        retVal = true;
    }
#else
    retVal = methodTwoPointer(s, t);
#endif

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string methodStack(string s) {
        string retVal;

        for (char c : s) {
            if (c != '#') {
                retVal.push_back(c);
            } else if (retVal.empty() == false) {
                retVal.pop_back();
            }
        }

        return retVal;
    }
    bool methodTwoPointer(string s, string t) {
        bool retVal = false;

        int skipS = 0;
        int skipT = 0;

        int i = s.size() - 1;
        int j = t.size() - 1;
        while ((i >= 0) || (j >= 0)) {
            while (i >= 0) {
                if (s[i] == '#') {
                    skipS += 1;
                    i--;
                } else if (skipS > 0) {
                    skipS -= 1;
                    i--;
                } else {
                    break;
                }
            }

            while (j >= 0) {
                if (t[j] == '#') {
                    skipT += 1;
                    j--;
                } else if (skipT > 0) {
                    skipT -= 1;
                    j--;
                } else {
                    break;
                }
            }

            if ((i >= 0) && (j >= 0)) {
                if (s[i] != t[j]) {
                    return retVal;
                }
            } else if ((i >= 0) || (j >= 0)) {
                return retVal;
            }

            i--;
            j--;
        }
        retVal = true;

        return retVal;
    }
    bool backspaceCompare(string s, string t) {
        bool retVal = false;

#if (0)
        if (methodStack(s) == methodStack(t)) {
            retVal = true;
        }
#else
        retVal = methodTwoPointer(s, t);
#endif

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def __init__(self) -> None:
        self.method = 2

    def method_stack(self, s: str) -> str:
        retVal = ""

        stack = []
        for c in s:
            if c != '#':
                stack.append(c)
            elif stack:
                stack.pop()
        retVal = retVal.join(stack)

        return retVal

    def method_twoPointer(self, s: str, t: str) -> bool:
        retVal = False

        skipS = 0
        skipT = 0
        i = len(s) - 1
        j = len(t) - 1
        while i >= 0 or j >= 0:
            while i >= 0:
                if s[i] == "#":
                    skipS += 1
                    i -= 1
                elif skipS > 0:
                    skipS -= 1
                    i -= 1
                else:
                    break

            while j >= 0:
                if t[j] == "#":
                    skipT += 1
                    j -= 1
                elif skipT > 0:
                    skipT -= 1
                    j -= 1
                else:
                    break

            if i >= 0 and j >= 0:
                if s[i] != t[j]:
                    return retVal
            elif i >= 0 or j >= 0:
                return retVal

            i -= 1
            j -= 1

        retVal = True

        return retVal

    def backspaceCompare(self, s: str, t: str) -> bool:
        retVal = False

        if self.method == 1:
            if self.method_stack(s) == self.method_stack(t):
                retVal = True
        elif self.method == 2:
            retVal = self.method_twoPointer(s, t)

        return retVal
```

</details>

## [880. Decoded String at Index](https://leetcode.com/problems/decoded-string-at-index/)  2010

- [Official](https://leetcode.cn/problems/decoded-string-at-index/solutions/3548/suo-yin-chu-de-jie-ma-zi-fu-chuan-by-leetcode/)

<details><summary>Description</summary>

```text
You are given an encoded string s.
To decode the string to a tape, the encoded string is read one character at a time and the following steps are taken:
- If the character read is a letter, that letter is written onto the tape.
- If the character read is a digit d, the entire current tape is repeatedly written d - 1 more times in total.

Given an integer k, return the kth letter (1-indexed) in the decoded string.

Example 1:
Input: s = "leet2code3", k = 10
Output: "o"
Explanation: The decoded string is "leetleetcodeleetleetcodeleetleetcode".
The 10th letter in the string is "o".

Example 2:
Input: s = "ha22", k = 5
Output: "h"
Explanation: The decoded string is "hahahaha".
The 5th letter is "h".

Example 3:
Input: s = "a2345678999999999999999", k = 1
Output: "a"
Explanation: The decoded string is "a" repeated 8301530446056247680 times.
The 1st letter is "a".

Constraints:
2 <= s.length <= 100
s consists of lowercase English letters and digits 2 through 9.
s starts with a letter.
1 <= k <= 109
It is guaranteed that k is less than or equal to the length of the decoded string.
The decoded string is guaranteed to have less than 2^63 letters.
```

</details>

<details><summary>C</summary>

```c
char* decodeAtIndex(char* s, int k) {
    char* pRetVal = NULL;

    pRetVal = (char*)malloc(2 * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (2 * sizeof(char)));

    int sSize = strlen(s);

    int i;
    long size = 0;
    for (i = 0; i < sSize; ++i) {
        if (isdigit(s[i]) != 0) {
            size *= (s[i] - '0');
        } else {
            size++;
        }
    }

    for (i = sSize - 1; i >= 0; --i) {
        k %= size;
        if ((k == 0) && (isalpha(s[i]) != 0)) {
            pRetVal[0] = s[i];
            break;
        }

        if (isdigit(s[i]) != 0) {
            size /= (s[i] - '0');
        } else {
            size--;
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
    string decodeAtIndex(string s, int k) {
        string retVal = "";

        int sSize = s.size();

        long size = 0;
        for (int i = 0; i < sSize; ++i) {
            if (isdigit(s[i]) != 0) {
                size *= (s[i] - '0');
            } else {
                size++;
            }
        }

        for (int i = sSize - 1; i >= 0; --i) {
            k %= size;
            if ((k == 0) && (isalpha(s[i]) != 0)) {
                retVal = s[i];
                break;
            }

            if (isdigit(s[i]) != 0) {
                size /= (s[i] - '0');
            } else {
                size--;
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
    def decodeAtIndex(self, s: str, k: int) -> str:
        retVal = ""

        size = 0
        for c in s:
            if c.isdigit():
                size *= int(c)
            else:
                size += 1

        for c in reversed(s):
            k %= size
            if k == 0 and c.isalpha():
                retVal = c
                break

            if c.isdigit():
                size /= int(c)
            else:
                size -= 1

        return retVal
```

</details>

## [901. Online Stock Span](https://leetcode.com/problems/online-stock-span/)  1708

- [Official](https://leetcode.cn/problems/online-stock-span/solutions/1906765/gu-piao-jie-ge-kua-du-by-leetcode-soluti-5cm7/)

<details><summary>Description</summary>

```text
Design an algorithm that collects daily price quotes for some stock
and returns the span of that stock's price for the current day.

The span of the stock's price today is defined as the maximum number of consecutive days
(starting from today and going backward) for which the stock price was less than or equal to today's price.
- For example, if the price of a stock over the next 7 days were [100,80,60,70,60,75,85],
  then the stock spans would be [1,1,1,2,1,4,6].

Implement the StockSpanner class:
- StockSpanner()
  Initializes the object of the class.
- int next(int price)
  Returns the span of the stock's price given that today's price is price.

Example 1:
Input
["StockSpanner", "next", "next", "next", "next", "next", "next", "next"]
[[], [100], [80], [60], [70], [60], [75], [85]]
Output
[null, 1, 1, 1, 2, 1, 4, 6]

Explanation
StockSpanner stockSpanner = new StockSpanner();
stockSpanner.next(100); // return 1
stockSpanner.next(80);  // return 1
stockSpanner.next(60);  // return 1
stockSpanner.next(70);  // return 2
stockSpanner.next(60);  // return 1
stockSpanner.next(75);  // return 4, because the last 4 prices (including today's price of 75)
                           were less than or equal to today's price.
stockSpanner.next(85);  // return 6

Constraints:
1 <= price <= 10^5
At most 10^4 calls will be made to next.
```

</details>

<details><summary>C</summary>

```c
typedef struct Node {
    int first;
    int second;
    struct Node *next;
} Node;
typedef struct {
    Node *stack;
    int idx;
} StockSpanner;
Node *nodeCreate(int first, int second) {
    Node *pRetVal = NULL;

    pRetVal = (Node *)malloc(sizeof(Node));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->first = first;
    pRetVal->second = second;
    pRetVal->next = NULL;

    return pRetVal;
}
StockSpanner *stockSpannerCreate() {
    StockSpanner *pRetVal = NULL;

    pRetVal = (StockSpanner *)malloc(sizeof(StockSpanner));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->idx = -1;
    pRetVal->stack = nodeCreate(-1, INT_MAX);

    return pRetVal;
}
int stockSpannerNext(StockSpanner *obj, int price) {
    int retVal = 0;

    obj->idx++;

    Node *pTmp = NULL;
    while (price >= obj->stack->second) {
        pTmp = obj->stack;
        obj->stack = obj->stack->next;
        free(pTmp);
        pTmp = NULL;
    }

    retVal = obj->idx - obj->stack->first;
    pTmp = nodeCreate(obj->idx, price);
    if (pTmp == NULL) {
        return retVal;
    }
    pTmp->next = obj->stack;
    obj->stack = pTmp;

    return retVal;
}
void stockSpannerFree(StockSpanner *obj) {
    Node *pFree = NULL;
    Node *pTmp = NULL;
    for (pTmp = obj->stack; pTmp != NULL;) {
        pFree = pTmp;
        pTmp = pTmp->next;
        free(pFree);
        pFree = NULL;
    }
    free(obj);
    obj = NULL;
}
/**
 * Your StockSpanner struct will be instantiated and called as such:
 * StockSpanner* obj = stockSpannerCreate();
 * int param_1 = stockSpannerNext(obj, price);
 * stockSpannerFree(obj);
 */
```

</details>

<details><summary>C++</summary>

```c++
class StockSpanner {
   public:
    stack<pair<int, int>> monotonicStack;

    StockSpanner() {
        //
    }
    int next(int price) {
        int retVal = 1;

        while ((monotonicStack.empty() == false) && (monotonicStack.top().first <= price)) {
            retVal += monotonicStack.top().second;
            monotonicStack.pop();
        }
        monotonicStack.push({price, retVal});

        return retVal;
    }
};
/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */
```

</details>

<details><summary>Python3</summary>

```python
class StockSpanner:
    def __init__(self):
        self.stack = [(-1, float("inf"))]
        self.idx = -1

    def next(self, price: int) -> int:
        retVal = 0

        self.idx += 1
        while price >= self.stack[-1][1]:
            self.stack.pop()
        self.stack.append((self.idx, price))
        retVal = self.idx - self.stack[-2][0]

        return retVal

# Your StockSpanner object will be instantiated and called as such:
# obj = StockSpanner()
# param_1 = obj.next(price)
```

</details>

## [907. Sum of Subarray Minimums](https://leetcode.com/problems/sum-of-subarray-minimums/)  1975

- [Official](https://leetcode.cn/problems/sum-of-subarray-minimums/solutions/1929461/zi-shu-zu-de-zui-xiao-zhi-zhi-he-by-leet-bp3k/)

<details><summary>Description</summary>

```text
Given an array of integers arr, find the sum of min(b), where b ranges over every (contiguous) subarray of arr.
Since the answer may be large, return the answer modulo 109 + 7.

Example 1:
Input: arr = [3,1,2,4]
Output: 17
Explanation:
Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4].
Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.
Sum is 17.

Example 2:
Input: arr = [11,81,94,43,3]
Output: 444

Constraints:
1 <= arr.length <= 3 * 10^4
1 <= arr[i] <= 3 * 10^4
```

</details>

<details><summary>C</summary>

```c
#define MODULO (int)(1e9 + 7)
int sumSubarrayMins(int* arr, int arrSize) {
    int retVal = 0;

    int dp[arrSize];
    memset(dp, 0, sizeof(dp));

    int monoStackTop = 0;
    int monoStack[arrSize];
    memset(monoStack, 0, sizeof(monoStack));

    int i, key, value;
    for (i = 0; i < arrSize; ++i) {
        value = arr[i];

        while ((monoStackTop > 0) && (arr[monoStack[monoStackTop - 1]] > value)) {
            monoStackTop--;
        }

        key = i + 1;
        if (monoStackTop != 0) {
            key = i - monoStack[monoStackTop - 1];
        }

        dp[i] = key * value;
        if (monoStackTop != 0) {
            dp[i] += dp[i - key];
        }

        monoStack[monoStackTop++] = i;

        retVal = (retVal + dp[i]) % MODULO;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    int MODULO = (int)(1e9 + 7);

   public:
    int sumSubarrayMins(vector<int>& arr) {
        int retVal = 0;

        int arrSize = arr.size();

        stack<int> monoStack;
        vector<int> dp(arrSize, 0);
        for (int i = 0; i < arrSize; ++i) {
            int value = arr[i];
            while ((monoStack.empty() == false) && (arr[monoStack.top()] > value)) {
                monoStack.pop();
            }

            int key = i + 1;
            if (monoStack.empty() == false) {
                key = i - monoStack.top();
            }

            dp[i] = key * value;
            if (monoStack.empty() == false) {
                dp[i] += dp[i - key];
            }

            monoStack.push(i);

            retVal = (retVal + dp[i]) % MODULO;
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

    def sumSubarrayMins(self, arr: List[int]) -> int:
        retVal = 0

        arrSize = len(arr)

        monoStack = []
        dp = [0] * arrSize
        for idx, value in enumerate(arr):
            while monoStack and arr[monoStack[-1]] > value:
                monoStack.pop()

            key = idx + 1
            if monoStack:
                key = idx - monoStack[-1]

            dp[idx] = key * value
            if monoStack:
                dp[idx] += dp[idx - key]

            monoStack.append(idx)

            retVal = (retVal + dp[idx]) % self.MODULO

        return retVal
```

</details>

## [921. Minimum Add to Make Parentheses Valid](https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/)  1242

- [Official](https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/editorial/)
- [Official](https://leetcode.cn/problems/minimum-add-to-make-parentheses-valid/solutions/1855025/shi-gua-hao-you-xiao-de-zui-shao-tian-ji-gcxu/)

<details><summary>Description</summary>

```text
A parentheses string is valid if and only if:
- It is the empty string,
- It can be written as AB (A concatenated with B), where A and B are valid strings, or
- It can be written as (A), where A is a valid string.

You are given a parentheses string s. In one move, you can insert a parenthesis at any position of the string.
- For example, if s = "()))",
  you can insert an opening parenthesis to be "(()))" or a closing parenthesis to be "())))".

Return the minimum number of moves required to make s valid.

Example 1:
Input: s = "())"
Output: 1

Example 2:
Input: s = "((("
Output: 3

Constraints:
1 <= s.length <= 1000
s[i] is either '(' or ')'.
```

</details>

<details><summary>C</summary>

```c
int minAddToMakeValid(char* s) {
    int retVal = 0;

    int sSize = strlen(s);
    int openBrackets = 0;
    int minAddsRequired = 0;
    int i;
    for (i = 0; i < sSize; ++i) {
        if (s[i] == '(') {
            openBrackets++;
        } else {
            // If open bracket exists, match it with the closing one. If not, we need to add a open bracket.
            (openBrackets > 0) ? (openBrackets--) : (minAddsRequired++);
        }
    }

    // Add the remaining open brackets as closing brackets would be required.
    retVal = minAddsRequired + openBrackets;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minAddToMakeValid(string s) {
        int retVal = 0;

        int openBrackets = 0;
        int minAddsRequired = 0;
        for (char c : s) {
            if (c == '(') {
                openBrackets++;
            } else {
                // If open bracket exists, match it with the closing one. If not, we need to add a open bracket.
                (openBrackets > 0) ? (openBrackets--) : (minAddsRequired++);
            }
        }

        // Add the remaining open brackets as closing brackets would be required.
        retVal = minAddsRequired + openBrackets;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minAddToMakeValid(self, s: str) -> int:
        retVal = 0

        openBrackets = 0
        minAddsRequired = 0
        for c in s:
            if c == '(':
                openBrackets += 1
            else:
                if openBrackets > 0:  # If open bracket exists, match it with the closing one.
                    openBrackets -= 1
                else:   # If not, we need to add a open bracket.
                    minAddsRequired += 1

        # Add the remaining open brackets as closing brackets would be required.
        retVal = minAddsRequired + openBrackets

        return retVal
```

</details>

## [946. Validate Stack Sequences](https://leetcode.com/problems/validate-stack-sequences/)  1461

- [Official](https://leetcode.cn/problems/validate-stack-sequences/solutions/1785639/yan-zheng-zhan-xu-lie-by-leetcode-soluti-cql0/)

<details><summary>Description</summary>

```text
Given two integer arrays pushed and popped each with distinct values,
return true if this could have been the result of a sequence of push and pop operations on an initially empty stack,
or false otherwise.

Example 1:
Input: pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
Output: true
Explanation: We might do the following sequence:
push(1), push(2), push(3), push(4),
pop() -> 4,
push(5),
pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1

Example 2:
Input: pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
Output: false
Explanation: 1 cannot be popped before 2.

Constraints:
1 <= pushed.length <= 1000
0 <= pushed[i] <= 1000
All the elements of pushed are unique.
popped.length == pushed.length
popped is a permutation of pushed.
```

</details>

<details><summary>C</summary>

```c
bool validateStackSequences(int* pushed, int pushedSize, int* popped, int poppedSize) {
    bool retVal = false;

    int stack[pushedSize];
    memset(stack, -1, sizeof(stack));  // 0 <= pushed[i] <= 1000
    int stackHead = 0;

    int poppedIdx = 0;
    int i;
    for (i = 0; i < pushedSize; ++i) {
        stack[stackHead++] = pushed[i];

        while (poppedIdx < poppedSize) {
            if ((stackHead > 0) && (stack[stackHead - 1] == popped[poppedIdx])) {
                stack[--stackHead] = -1;
                ++poppedIdx;
            } else {
                break;
            }
        }
    }

    if (stackHead == 0) {
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
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        bool retVal = false;

        int poppedSize = popped.size();
        int poppedIdx = 0;

        stack<int> stackRecord;
        for (auto value : pushed) {
            stackRecord.push(value);
            int i;
            for (i = poppedIdx; i < poppedSize; ++i) {
                if ((stackRecord.empty() == false) && (stackRecord.top() == popped[i])) {
                    stackRecord.pop();
                } else {
                    poppedIdx = i;
                    break;
                }
            }
        }

        if (stackRecord.empty() == true) {
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
    def validateStackSequences(self, pushed: List[int], popped: List[int]) -> bool:
        retVal = False

        poppedSize = len(popped)
        poppedIdx = 0

        stack = []
        for push in pushed:
            stack.append(push)

            for i in range(poppedIdx, poppedSize):
                if stack and popped[i] == stack[-1]:
                    stack.pop()
                else:
                    poppedIdx = i
                    break

        if not stack:
            retVal = True

        return retVal
```

</details>

## [962. Maximum Width Ramp](https://leetcode.com/problems/maximum-width-ramp/)  1607

- [Official](https://leetcode.com/problems/maximum-width-ramp/editorial/)
- [Official](https://leetcode.cn/problems/maximum-width-ramp/solutions/3610/zui-da-kuan-du-po-by-leetcode/)

<details><summary>Description</summary>

```text
A ramp in an integer array nums is a pair (i, j) for which i < j and nums[i] <= nums[j].
The width of such a ramp is j - i.

Given an integer array nums, return the maximum width of a ramp in nums. If there is no ramp in nums, return 0.

Example 1:
Input: nums = [6,0,8,2,1,5]
Output: 4
Explanation: The maximum width ramp is achieved at (i, j) = (1, 5): nums[1] = 0 and nums[5] = 5.

Example 2:
Input: nums = [9,8,1,0,1,9,4,0,4,1]
Output: 7
Explanation: The maximum width ramp is achieved at (i, j) = (2, 9): nums[2] = 1 and nums[9] = 1.

Constraints:
2 <= nums.length <= 5 * 10^4
0 <= nums[i] <= 5 * 10^4
```

</details>

<details><summary>C</summary>

```c
int maxWidthRamp(int* nums, int numsSize) {
    int retVal = 0;

    int indexStackTop = -1;
    int indexStack[numsSize];
    memset(indexStack, 0, sizeof(indexStack));
    indexStack[++indexStackTop] = 0;

    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[indexStack[indexStackTop]] > nums[i]) {
            indexStack[++indexStackTop] = i;
        }
    }

    for (i = numsSize - 1; i >= 0; --i) {
        while ((indexStackTop != -1) && (nums[indexStack[indexStackTop]] <= nums[i])) {
            retVal = fmax(retVal, i - indexStack[indexStackTop]);
            indexStack[indexStackTop--] = 0;
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
    int maxWidthRamp(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        vector<int> indexStack;
        indexStack.push_back(0);
        for (int i = 1; i < numsSize; ++i) {
            if (nums[indexStack.back()] > nums[i]) {
                indexStack.push_back(i);
            }
        }

        for (int i = numsSize - 1; i >= 0; --i) {
            while ((indexStack.empty() == false) && (nums[indexStack.back()] <= nums[i])) {
                retVal = max(retVal, i - indexStack.back());
                indexStack.pop_back();
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
    def maxWidthRamp(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        indexStack = [0]
        for i in range(1, numsSize):
            if nums[indexStack[-1]] > nums[i]:
                indexStack.append(i)

        for i in range(numsSize - 1, -1, -1):
            while indexStack and nums[indexStack[-1]] <= nums[i]:
                retVal = max(retVal, i - indexStack[-1])
                indexStack.pop()

        return retVal
```

</details>

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

## [2116. Check if a Parentheses String Can Be Valid](https://leetcode.com/problems/check-if-a-parentheses-string-can-be-valid/)  2037

- [Official](https://leetcode.com/problems/check-if-a-parentheses-string-can-be-valid/editorial/)
- [Official](https://leetcode.cn/problems/check-if-a-parentheses-string-can-be-valid/solutions/1179134/pan-duan-yi-ge-gua-hao-zi-fu-chuan-shi-f-0s47/)

<details><summary>Description</summary>

```text
A parentheses string is a non-empty string consisting only of '(' and ')'.
It is valid if any of the following conditions is true:
- It is ().
- It can be written as AB (A concatenated with B), where A and B are valid parentheses strings.
- It can be written as (A), where A is a valid parentheses string.

You are given a parentheses string s and a string locked, both of length n.
locked is a binary string consisting only of '0's and '1's. For each index i of locked,
- If locked[i] is '1', you cannot change s[i].
- But if locked[i] is '0', you can change s[i] to either '(' or ')'.

Return true if you can make s a valid parentheses string. Otherwise, return false.

Example 1:
Input: s = "))()))", locked = "010100"
Output: true
Explanation: locked[1] == '1' and locked[3] == '1', so we cannot change s[1] or s[3].
We change s[0] and s[4] to '(' while leaving s[2] and s[5] unchanged to make s valid.

Example 2:
Input: s = "()()", locked = "0000"
Output: true
Explanation: We do not need to make any changes because s is already valid.

Example 3:
Input: s = ")", locked = "0"
Output: false
Explanation: locked permits us to change s[0].
Changing s[0] to either '(' or ')' will not make s valid.

Constraints:
n == s.length == locked.length
1 <= n <= 10^5
s[i] is either '(' or ')'.
locked[i] is either '0' or '1'.
```

<details><summary>Hint</summary>

```text
1. Can an odd length string ever be valid?
2. From left to right, if a locked ')' is encountered,
   it must be balanced with either a locked '(' or an unlocked index on its left.
   If neither exist, what conclusion can be drawn? If both exist, which one is more preferable to use?
3. After the above, we may have locked indices of '(' and additional unlocked indices.
   How can you balance out the locked '(' now? What if you cannot balance any locked '('?
```

</details>

</details>

<details><summary>C</summary>

```c
bool canBeValid(char* s, char* locked) {
    bool retVal = false;

    int sSize = strlen(s);
    if (sSize % 2 == 1) {
        return retVal;
    }

    int openBracketsStackTop = -1;
    int openBracketsStack[sSize];
    memset(openBracketsStack, -1, sizeof(openBracketsStack));
    int unlockedStackTop = -1;
    int unlockedStack[sSize];
    memset(unlockedStack, -1, sizeof(unlockedStack));
    for (int i = 0; i < sSize; i++) {
        if (locked[i] == '0') {
            unlockedStack[++unlockedStackTop] = i;
        } else if (s[i] == '(') {
            openBracketsStack[++openBracketsStackTop] = i;
        } else if (s[i] == ')') {
            if (openBracketsStackTop != -1) {
                openBracketsStack[openBracketsStackTop--] = 0;
            } else if (unlockedStackTop != -1) {
                unlockedStack[unlockedStackTop--] = 0;
            } else {
                return retVal;
            }
        }
    }

    while ((openBracketsStackTop != -1) && (unlockedStackTop != -1) &&
           (openBracketsStack[openBracketsStackTop] < unlockedStack[unlockedStackTop])) {
        openBracketsStack[openBracketsStackTop--] = 0;
        unlockedStack[unlockedStackTop--] = 0;
    }
    if (openBracketsStackTop == -1) {
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
    bool canBeValid(string s, string locked) {
        bool retVal = false;

        int sSize = s.size();
        if (sSize % 2 == 1) {
            return retVal;
        }

        stack<int> openBrackets;
        stack<int> unlocked;
        for (int i = 0; i < sSize; i++) {
            if (locked[i] == '0') {
                unlocked.push(i);
            } else if (s[i] == '(') {
                openBrackets.push(i);
            } else if (s[i] == ')') {
                if (openBrackets.empty() == false) {
                    openBrackets.pop();
                } else if (unlocked.empty() == false) {
                    unlocked.pop();
                } else {
                    return retVal;
                }
            }
        }

        while ((openBrackets.empty() == false) && (unlocked.empty() == false) &&
               (openBrackets.top() < unlocked.top())) {
            openBrackets.pop();
            unlocked.pop();
        }
        if (openBrackets.empty() == true) {
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
    def canBeValid(self, s: str, locked: str) -> bool:
        retVal = False

        sSize = len(s)
        if sSize % 2 == 1:
            return retVal

        openBrackets = []
        unlocked = []
        for i in range(sSize):
            if locked[i] == "0":
                unlocked.append(i)
            elif s[i] == "(":
                openBrackets.append(i)
            elif s[i] == ")":
                if openBrackets:
                    openBrackets.pop()
                elif unlocked:
                    unlocked.pop()
                else:
                    return retVal

        while openBrackets and unlocked and openBrackets[-1] < unlocked[-1]:
            openBrackets.pop()
            unlocked.pop()
        if not openBrackets:
            retVal = True

        return retVal
```

</details>

## [2211. Count Collisions on a Road](https://leetcode.com/problems/count-collisions-on-a-road/)  1581

<details><summary>Description</summary>

```text
There are n cars on an infinitely long road.
The cars are numbered from 0 to n - 1 from left to right and each car is present at a unique point.

You are given a 0-indexed string directions of length n.
directions[i] can be either 'L', 'R', or 'S' denoting whether the ith car is moving towards the left,
towards the right, or staying at its current point respectively.
Each moving car has the same speed.

The number of collisions can be calculated as follows:
- When two cars moving in opposite directions collide with each other, the number of collisions increases by 2.
- When a moving car collides with a stationary car, the number of collisions increases by 1.

After a collision, the cars involved can no longer move and will stay at the point where they collided.
Other than that, cars cannot change their state or direction of motion.

Return the total number of collisions that will happen on the road.

Example 1:
Input: directions = "RLRSLL"
Output: 5
Explanation:
The collisions that will happen on the road are:
- Cars 0 and 1 will collide with each other.
  Since they are moving in opposite directions, the number of collisions becomes 0 + 2 = 2.
- Cars 2 and 3 will collide with each other.
  Since car 3 is stationary, the number of collisions becomes 2 + 1 = 3.
- Cars 3 and 4 will collide with each other.
  Since car 3 is stationary, the number of collisions becomes 3 + 1 = 4.
- Cars 4 and 5 will collide with each other.
  After car 4 collides with car 3, it will stay at the point of collision and get hit by car 5.
  The number of collisions becomes 4 + 1 = 5.
Thus, the total number of collisions that will happen on the road is 5.

Example 2:
Input: directions = "LLRR"
Output: 0
Explanation:
No cars will collide with each other. Thus, the total number of collisions that will happen on the road is 0.

Constraints:
1 <= directions.length <= 10^5
directions[i] is either 'L', 'R', or 'S'.
```

<details><summary>Hint</summary>

```text
1. In what circumstances does a moving car not collide with another car?
2. If we disregard the moving cars that do not collide with another car,
   what does each moving car contribute to the answer?
3. Will stationary cars contribute towards the answer?
```

</details>

</details>

<details><summary>C</summary>

```c
int countCollisions(char *directions) {
    int retVal = 0;

    // https://leetcode.cn/problems/count-collisions-on-a-road/solutions/1352569/da-an-hui-bei-zhuang-ting-de-che-liang-s-yyfl/

    int directionsSize = strlen(directions);
    char stack[directionsSize + 1];
    memset(stack, 0, sizeof(stack));
#define STACK_EMPTY (-1)
    int stackTop = -1;
    int i;
    for (i = 0; i < directionsSize; ++i) {
        if (directions[i] == 'L') {
            if (stackTop == STACK_EMPTY) {
                continue;
            }
            while ((stackTop != STACK_EMPTY) && (stack[stackTop] == 'R')) {
                retVal += 1;
                stack[stackTop--] = 0;
            }
            retVal += 1;
            stack[++stackTop] = 'S';
        } else if (directions[i] == 'R') {
            stack[++stackTop] = directions[i];
        } else if (directions[i] == 'S') {
            while ((stackTop != STACK_EMPTY) && (stack[stackTop] == 'R')) {
                retVal += 1;
                stack[stackTop--] = 0;
            }
            stack[++stackTop] = directions[i];
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
    int countCollisions(string directions) {
        int retVal = 0;

        // https://leetcode.cn/problems/count-collisions-on-a-road/solutions/1352569/da-an-hui-bei-zhuang-ting-de-che-liang-s-yyfl/
        vector<char> stack;
        for (auto direction : directions) {
            if (direction == 'L') {
                if (stack.empty() == true) {
                    continue;
                }
                while ((stack.empty() == false) && (stack.back() == 'R')) {
                    retVal += 1;
                    stack.pop_back();
                }
                retVal += 1;
                stack.emplace_back('S');
            } else if (direction == 'R') {
                stack.emplace_back(direction);
            } else if (direction == 'S') {
                while ((stack.empty() == false) && (stack.back() == 'R')) {
                    retVal += 1;
                    stack.pop_back();
                }
                stack.emplace_back(direction);
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
    def countCollisions(self, directions: str) -> int:
        retVal = 0

        # https://leetcode.cn/problems/count-collisions-on-a-road/solutions/1352569/da-an-hui-bei-zhuang-ting-de-che-liang-s-yyfl/
        stack = []
        for direction in directions:
            if direction == 'L':
                if not stack:
                    continue
                while stack and stack[-1] == 'R':
                    retVal += 1
                    stack.pop()
                retVal += 1
                stack.append('S')
            elif direction == 'R':
                stack.append(direction)
            elif direction == 'S':
                while stack and stack[-1] == 'R':
                    retVal += 1
                    stack.pop()
                stack.append(direction)

        return retVal
```

</details>

## [2390. Removing Stars From a String](https://leetcode.com/problems/removing-stars-from-a-string/)  1347

<details><summary>Description</summary>

```text
You are given a string s, which contains stars *.

In one operation, you can:
- Choose a star in s.
- Remove the closest non-star character to its left, as well as remove the star itself.

Return the string after all stars have been removed.

Note:
- The input will be generated such that the operation is always possible.
- It can be shown that the resulting string will always be unique.

Example 1:
Input: s = "leet**cod*e"
Output: "lecoe"
Explanation: Performing the removals from left to right:
- The closest character to the 1st star is 't' in "leet**cod*e". s becomes "lee*cod*e".
- The closest character to the 2nd star is 'e' in "lee*cod*e". s becomes "lecod*e".
- The closest character to the 3rd star is 'd' in "lecod*e". s becomes "lecoe".
There are no more stars, so we return "lecoe".

Example 2:
Input: s = "erase*****"
Output: ""
Explanation: The entire string is removed, so we return an empty string.

Constraints:
1 <= s.length <= 10^5
s consists of lowercase English letters and stars *.
The operation above can be performed on s.
```

<details><summary>Hint</summary>

```text
1. What data structure could we use to efficiently perform these removals?
2. Use a stack to store the characters.
   Pop one character off the stack at each star.
   Otherwise, we push the character onto the stack.
```

</details>

</details>

<details><summary>C</summary>

```c
char* removeStars(char* s) {
    char* pRetVal = s;

    int len = strlen(s);
    int idx = 0;
    int i;
    for (i = 0; i < len; ++i) {
        if (s[i] != '*') {
            s[idx++] = s[i];
            continue;
        }
        idx = ((idx > 0) ? (idx - 1) : idx);
    }
    s[idx] = 0;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string removeStars(string s) {
        string retVal = "";

        for (char c : s) {
            if (c != '*') {
                retVal.push_back(c);
            } else {
                retVal.pop_back();
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
    def removeStars(self, s: str) -> str:
        retVal = ""

        for c in s:
            if c != '*':
                retVal += c
            else:
                retVal = retVal[:-1]

        return retVal
```

</details>

## [2696. Minimum String Length After Removing Substrings](https://leetcode.com/problems/minimum-string-length-after-removing-substrings/)  1282

- [Official](https://leetcode.com/problems/minimum-string-length-after-removing-substrings/editorial/)
- [Official](https://leetcode.cn/problems/minimum-string-length-after-removing-substrings/solutions/2591242/shan-chu-zi-chuan-hou-de-zi-fu-chuan-zui-968c/)

<details><summary>Description</summary>

```text
You are given a string s consisting only of uppercase English letters.

You can apply some operations to this string where,
in one operation, you can remove any occurrence of one of the substrings "AB" or "CD" from s.

Return the minimum possible length of the resulting string that you can obtain.

Note that the string concatenates after removing the substring and could produce new "AB" or "CD" substrings.

Example 1:
Input: s = "ABFCACDB"
Output: 2
Explanation: We can do the following operations:
- Remove the substring "ABFCACDB", so s = "FCACDB".
- Remove the substring "FCACDB", so s = "FCAB".
- Remove the substring "FCAB", so s = "FC".
So the resulting length of the string is 2.
It can be shown that it is the minimum length that we can obtain.

Example 2:
Input: s = "ACBBD"
Output: 5
Explanation: We cannot do any operations on the string so the length remains the same.

Constraints:
1 <= s.length <= 100
s consists only of uppercase English letters.
```

<details><summary>Hint</summary>

```text
1. Can we use brute force to solve the problem?
2. Repeatedly traverse the string to find and remove the substrings “AB” and “CD” until no more occurrences exist.
```

</details>

</details>

<details><summary>C</summary>

```c
int minLength(char *s) {
    int retVal = 0;

    int sSize = strlen(s);

    int stackTop = -1;
    char stack[sSize];
    memset(stack, 0, sizeof(stack));

    int i;
    for (i = 0; i < sSize; ++i) {
        if (stackTop == -1) {
            stack[++stackTop] = s[i];
        } else if ((s[i] == 'B') && (stack[stackTop] == 'A')) {
            stack[stackTop--] = 0;
        } else if ((s[i] == 'D') && (stack[stackTop] == 'C')) {
            stack[stackTop--] = 0;
        } else {
            stack[++stackTop] = s[i];
        }
    }
    retVal = stackTop + 1;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minLength(string s) {
        int retVal = 0;

        vector<char> stack;
        for (char c : s) {
            if (stack.empty() == true) {
                stack.push_back(c);
            } else if ((c == 'B') && (stack.back() == 'A')) {
                stack.pop_back();
            } else if ((c == 'D') && (stack.back() == 'C')) {
                stack.pop_back();
            } else {
                stack.push_back(c);
            }
        }
        retVal = stack.size();

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minLength(self, s: str) -> int:
        retVal = 0

        stack = []
        for c in s:
            if not stack:
                stack.append(c)
            elif c == 'B' and stack[-1] == 'A':
                stack.pop(-1)
            elif c == 'D' and stack[-1] == 'C':
                stack.pop(-1)
            else:
                stack.append(c)
        retVal = len(stack)

        return retVal
```

</details>

## [2751. Robot Collisions](https://leetcode.com/problems/robot-collisions/)  2091

- [Official](https://leetcode.com/problems/robot-collisions/editorial/)

<details><summary>Description</summary>

```text
There are n 1-indexed robots, each having a position on a line, health, and movement direction.

You are given 0-indexed integer arrays positions, healths,
and a string directions (directions[i] is either 'L' for left or 'R' for right).
All integers in positions are unique.

All robots start moving on the line simultaneously at the same speed in their given directions.
If two robots ever share the same position while moving, they will collide.

If two robots collide, the robot with lower health is removed from the line,
and the health of the other robot decreases by one.
The surviving robot continues in the same direction it was going.
If both robots have the same health, they are both removed from the line.

Your task is to determine the health of the robots that survive the collisions,
in the same order that the robots were given,
i.e. final heath of robot 1 (if survived), final health of robot 2 (if survived), and so on.
If there are no survivors, return an empty array.

Return an array containing the health of the remaining robots (in the order they were given in the input),
after no further collisions can occur.

Note: The positions may be unsorted.

Example 1:
Input: positions = [5,4,3,2,1], healths = [2,17,9,15,10], directions = "RRRRR"
Output: [2,17,9,15,10]
Explanation: No collision occurs in this example, since all robots are moving in the same direction.
So, the health of the robots in order from the first robot is returned, [2, 17, 9, 15, 10].

Example 2:
Input: positions = [3,5,2,6], healths = [10,10,15,12], directions = "RLRL"
Output: [14]
Explanation: There are 2 collisions in this example.
Firstly, robot 1 and robot 2 will collide, and since both have the same health, they will be removed from the line.
Next, robot 3 and robot 4 will collide and since robot 4's health is smaller,
it gets removed, and robot 3's health becomes 15 - 1 = 14.
Only robot 3 remains, so we return [14].

Example 3:
Input: positions = [1,2,5,6], healths = [10,10,11,11], directions = "RLRL"
Output: []
Explanation: Robot 1 and robot 2 will collide and since both have the same health, they are both removed.
Robot 3 and 4 will collide and since both have the same health, they are both removed. So, we return an empty array, [].

Constraints:
1 <= positions.length == healths.length == directions.length == n <= 10^5
1 <= positions[i], healths[i] <= 10^9
directions[i] == 'L' or directions[i] == 'R'
All values in positions are distinct
```

<details><summary>Hint</summary>

```text
1. Process the robots in the order of their positions to ensure that we process the collisions correctly.
2. To optimize the solution, use a stack to keep track of the surviving robots as we iterate through the positions.
3. Instead of simulating each collision,
   check the current robot against the top of the stack (if it exists) to determine if a collision occurs.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareIntArray(const void* a1, const void* a2) {
    int* p1 = (int*)a1;
    int* p2 = (int*)a2;

    // ascending order
    return (p1[1] > p2[1]);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* survivedRobotsHealths(int* positions, int positionsSize, int* healths, int healthsSize, char* directions,
                           int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int*)malloc(positionsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (positionsSize * sizeof(int)));

    int i;

    // Sort indices based on their positions
    int indices[positionsSize][2];
    for (i = 0; i < positionsSize; ++i) {
        indices[i][0] = i;
        indices[i][1] = positions[i];
    }
    qsort(indices, positionsSize, sizeof(indices[0]), compareIntArray);

    int stackTop = -1;
    int stack[positionsSize];
    memset(stack, 0, sizeof(stack));
    int currentIndex, topIndex;
    for (i = 0; i < positionsSize; ++i) {
        currentIndex = indices[i][0];

        if (directions[currentIndex] == 'R') {
            stackTop++;
            stack[stackTop] = currentIndex;
            continue;
        }

        while ((stackTop > -1) && (healths[currentIndex] > 0)) {
            // Pop the top robot from the stack for collision check
            topIndex = stack[stackTop];
            stackTop--;

            if (healths[topIndex] > healths[currentIndex]) {
                // Top robot survives, current robot is destroyed
                healths[topIndex] -= 1;
                healths[currentIndex] = 0;
                stackTop++;
                stack[stackTop] = topIndex;
            } else if (healths[topIndex] < healths[currentIndex]) {
                // Current robot survives, top robot is destroyed
                healths[currentIndex] -= 1;
                healths[topIndex] = 0;
            } else {
                // Both robots are destroyed
                healths[currentIndex] = 0;
                healths[topIndex] = 0;
            }
        }
    }

    // Collect surviving robots
    for (i = 0; i < positionsSize; ++i) {
        if (healths[i] > 0) {
            pRetVal[(*returnSize)++] = healths[i];
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
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        vector<int> retVal;

        int positionsSize = positions.size();

        // Sort indices based on their positions
        vector<int> indices(positionsSize);
        for (int index = 0; index < positionsSize; ++index) {
            indices[index] = index;
        }
        sort(indices.begin(), indices.end(), [&](int lhs, int rhs) {
            // ascending order
            return positions[lhs] < positions[rhs];
        });

        stack<int> stack;
        for (int currentIndex : indices) {
            if (directions[currentIndex] == 'R') {
                stack.push(currentIndex);
                continue;
            }

            while (!stack.empty() && healths[currentIndex] > 0) {
                // Pop the top robot from the stack for collision check
                int topIndex = stack.top();
                stack.pop();

                if (healths[topIndex] > healths[currentIndex]) {
                    // Top robot survives, current robot is destroyed
                    healths[topIndex] -= 1;
                    healths[currentIndex] = 0;
                    stack.push(topIndex);
                } else if (healths[topIndex] < healths[currentIndex]) {
                    // Current robot survives, top robot is destroyed
                    healths[currentIndex] -= 1;
                    healths[topIndex] = 0;
                } else {
                    // Both robots are destroyed
                    healths[currentIndex] = 0;
                    healths[topIndex] = 0;
                }
            }
        }

        // Collect surviving robots
        for (int index = 0; index < positionsSize; ++index) {
            if (healths[index] > 0) {
                retVal.emplace_back(healths[index]);
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
    def survivedRobotsHealths(self, positions: List[int], healths: List[int], directions: str) -> List[int]:
        retVal = []

        positionsSize = len(positions)

        # Sort indices based on their positions
        indices = list(range(positionsSize))
        indices.sort(key=lambda x: positions[x])

        stack = deque()
        for currentIndex in indices:
            if directions[currentIndex] == "R":
                stack.append(currentIndex)
                continue

            while stack and healths[currentIndex] > 0:
                # Pop the top robot from the stack for collision check
                topIndex = stack.pop()

                if healths[topIndex] > healths[currentIndex]:
                    # Top robot survives, current robot is destroyed
                    healths[topIndex] -= 1
                    healths[currentIndex] = 0
                    stack.append(topIndex)
                elif healths[topIndex] < healths[currentIndex]:
                    # Current robot survives, top robot is destroyed
                    healths[currentIndex] -= 1
                    healths[topIndex] = 0
                else:
                    # Both robots are destroyed
                    healths[currentIndex] = 0
                    healths[topIndex] = 0

        # Collect surviving robots
        for index in range(positionsSize):
            if healths[index] > 0:
                retVal.append(healths[index])

        return retVal
```

</details>
