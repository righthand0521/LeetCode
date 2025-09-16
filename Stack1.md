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
