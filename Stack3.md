# [Stack](https://en.wikipedia.org/wiki/Stack_(abstract_data_type))

- Monotonic Stack

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

## [2197. Replace Non-Coprime Numbers in Array](https://leetcode.com/problems/replace-non-coprime-numbers-in-array/)  2057

- [Official](https://leetcode.cn/problems/replace-non-coprime-numbers-in-array/solutions/1328577/ti-huan-shu-zu-zhong-de-fei-hu-zhi-shu-b-mnml/)

<details><summary>Description</summary>

```text
You are given an array of integers nums. Perform the following steps:
1. Find any two adjacent numbers in nums that are non-coprime.
2. If no such numbers are found, stop the process.
3. Otherwise, delete the two numbers and replace them with their LCM (Least Common Multiple).
4. Repeat this process as long as you keep finding two adjacent non-coprime numbers.

Return the final modified array.
It can be shown that replacing adjacent non-coprime numbers in any arbitrary order will lead to the same result.

The test cases are generated such that the values in the final array are less than or equal to 10^8.

Two values x and y are non-coprime if GCD(x, y) > 1 where GCD(x, y) is the Greatest Common Divisor of x and y.

Example 1:
Input: nums = [6,4,3,2,7,6,2]
Output: [12,7,6]
Explanation:
- (6, 4) are non-coprime with LCM(6, 4) = 12. Now, nums = [12,3,2,7,6,2].
- (12, 3) are non-coprime with LCM(12, 3) = 12. Now, nums = [12,2,7,6,2].
- (12, 2) are non-coprime with LCM(12, 2) = 12. Now, nums = [12,7,6,2].
- (6, 2) are non-coprime with LCM(6, 2) = 6. Now, nums = [12,7,6].
There are no more adjacent non-coprime numbers in nums.
Thus, the final modified array is [12,7,6].
Note that there are other ways to obtain the same resultant array.

Example 2:
Input: nums = [2,2,1,1,3,3,3]
Output: [2,1,1,3]
Explanation:
- (3, 3) are non-coprime with LCM(3, 3) = 3. Now, nums = [2,2,1,1,3,3].
- (3, 3) are non-coprime with LCM(3, 3) = 3. Now, nums = [2,2,1,1,3].
- (2, 2) are non-coprime with LCM(2, 2) = 2. Now, nums = [2,1,1,3].
There are no more adjacent non-coprime numbers in nums.
Thus, the final modified array is [2,1,1,3].
Note that there are other ways to obtain the same resultant array.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^5
The test cases are generated such that the values in the final array are less than or equal to 10^8.
```

<details><summary>Hint</summary>

```text
1. Notice that the order of merging two numbers into their LCM does not matter
   so we can greedily merge elements to its left if possible.
2. If a new value is formed, we should recursively check if it can be merged with the value to its left.
3. To simulate the merge efficiently, we can maintain a stack that stores processed elements.
   When we iterate through the array, we only compare with the top of the stack (which is the value to its left).
```

</details>

</details>

<details><summary>C</summary>

```c
int gcd(int a, int b) {
    int retVal = a;

    if (b != 0) {
        retVal = gcd(b, a % b);
    }

    return retVal;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* replaceNonCoprimes(int* nums, int numsSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int*)malloc(numsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, numsSize * sizeof(int));

    int num, last, g;
    for (int i = 0; i < numsSize; i++) {
        num = nums[i];
        while ((*returnSize) > 0) {
            last = pRetVal[(*returnSize) - 1];
            g = gcd(last, num);
            if (g > 1) {
                num = last / g * num;
                (*returnSize)--;
            } else {
                break;
            }
        }
        pRetVal[(*returnSize)++] = num;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> replaceNonCoprimes(vector<int>& nums) {
        vector<int> retVal;

        for (int num : nums) {
            while (retVal.empty() == false) {
                int g = gcd(retVal.back(), num);
                if (g > 1) {
                    num = retVal.back() / g * num;
                    retVal.pop_back();
                } else {
                    break;
                }
            }
            retVal.push_back(num);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def replaceNonCoprimes(self, nums: List[int]) -> List[int]:
        retVal = []

        for num in nums:
            while retVal:
                g = gcd(retVal[-1], num)
                if g > 1:
                    num = retVal[-1] // g * num
                    retVal.pop()
                else:
                    break
            retVal.append(num)

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

## [2818. Apply Operations to Maximize Score](https://leetcode.com/problems/apply-operations-to-maximize-score/)  2396

- [Official](https://leetcode.com/problems/apply-operations-to-maximize-score/editorial/)

<details><summary>Description</summary>

```text
You are given an array nums of n positive integers and an integer k.

Initially, you start with a score of 1.
You have to maximize your score by applying the following operation at most k times:
- Choose any non-empty subarray nums[l, ..., r] that you haven't chosen previously.
- Choose an element x of nums[l, ..., r] with the highest prime score.
  If multiple such elements exist, choose the one with the smallest index.
- Multiply your score by x.

Here, nums[l, ..., r] denotes the subarray of nums starting at index l and ending at the index r,
both ends being inclusive.

The prime score of an integer x is equal to the number of distinct prime factors of x.
For example, the prime score of 300 is 3 since 300 = 2 * 2 * 3 * 5 * 5.

Return the maximum possible score after applying at most k operations.

Since the answer may be large, return it modulo 10^9 + 7.

Example 1:
Input: nums = [8,3,9,3,8], k = 2
Output: 81
Explanation: To get a score of 81, we can apply the following operations:
- Choose subarray nums[2, ..., 2]. nums[2] is the only element in this subarray.
  Hence, we multiply the score by nums[2]. The score becomes 1 * 9 = 9.
- Choose subarray nums[2, ..., 3]. Both nums[2] and nums[3] have a prime score of 1, but nums[2] has the smaller index.
  Hence, we multiply the score by nums[2]. The score becomes 9 * 9 = 81.
It can be proven that 81 is the highest score one can obtain.

Example 2:
Input: nums = [19,12,14,6,10,18], k = 3
Output: 4788
Explanation: To get a score of 4788, we can apply the following operations:
- Choose subarray nums[0, ..., 0]. nums[0] is the only element in this subarray.
  Hence, we multiply the score by nums[0]. The score becomes 1 * 19 = 19.
- Choose subarray nums[5, ..., 5]. nums[5] is the only element in this subarray.
  Hence, we multiply the score by nums[5]. The score becomes 19 * 18 = 342.
- Choose subarray nums[2, ..., 3]. Both nums[2] and nums[3] have a prime score of 2, but nums[2] has the smaller index.
  Hence, we multipy the score by nums[2]. The score becomes 342 * 14 = 4788.
It can be proven that 4788 is the highest score one can obtain.

Constraints:
1 <= nums.length == n <= 10^5
1 <= nums[i] <= 10^5
1 <= k <= min(n * (n + 1) / 2, 10^9)
```

<details><summary>Hint</summary>

```text
1. Calculate nums[i]'s prime score s[i] by factoring in O(sqrt(nums[i])) time.
2. For each nums[i], find the nearest index left[i] on the left (if any) such that s[left[i]] >= s[i].
   if none is found, set left[i] to -1.
   Similarly, find the nearest index right[i] on the right (if any) such that s[right[i]] > s[i].
   If none is found, set right[i] to n.
3. Use a monotonic stack to compute right[i] and left[i].
4. For each index i, if left[i] + 1 <= l <= i <= r <= right[i] - 1, then s[i] is the maximum value in the range [l, r].
   For this particular i, there are ranges[i] = (i - left[i]) * (right[i] - i) ranges where index i will be chosen.
5. Loop over all elements of nums by non-increasing prime score,
   each element will be chosen min(ranges[i], remainingK) times,
   where reaminingK denotes the number of remaining operations.
   Therefore, the score will be multiplied by s[i]^min(ranges[i],remainingK).
6. Use fast exponentiation to quickly calculate A^B mod C.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MODULO (int)(1e9 + 7)
typedef struct {
    int value;
    int index;
} pair;
int compareStruct(const void* a, const void* b) {
    int pa = ((pair*)a)->value;
    int pb = ((pair*)b)->value;

    // ascending order
    return (pa > pb);
}
long long powerOfModulo(long long base, long long exponent) {
    long long retVal = 1;

    // Calculate the exponentiation using binary exponentiation
    while (exponent > 0) {
        // If the exponent is odd, multiply the result by the base
        if (exponent % 2 == 1) {
            retVal = ((retVal * base) % MODULO);
        }

        // Square the base and halve the exponent
        base = (base * base) % MODULO;
        exponent /= 2;
    }

    return retVal;
}
int maximumScore(int* nums, int numsSize, int k) {
    int retVal = 0;

    // Calculate the prime score for each number in nums
    int primeScores[numsSize];
    memset(primeScores, 0, sizeof(primeScores));
    for (int index = 0; index < numsSize; index++) {
        int num = nums[index];
        // Check for prime factors from 2 to sqrt(n)
        for (int factor = 2; factor <= sqrt(num); factor++) {
            if (num % factor != 0) {
                continue;
            }
            // Increment prime score for each prime factor
            primeScores[index]++;
            // Remove all occurrences of the prime factor from num
            while (num % factor == 0) {
                num /= factor;
            }
        }
        // If num is still greater than or equal to 2, it's a prime factor
        if (num >= 2) {
            primeScores[index]++;
        }
    }

    // Initialize next and previous dominant index arrays
    int nextDominant[numsSize];
    memset(nextDominant, 0, sizeof(nextDominant));
    int prevDominant[numsSize];
    memset(prevDominant, 0, sizeof(prevDominant));
    for (int i = 0; i < numsSize; i++) {
        nextDominant[i] = numsSize;
        prevDominant[i] = -1;
    }
    // Stack to store indices for monotonic decreasing prime score
    int decreasingPrimeScoreStack[numsSize];
    int decreasingPrimeScoreStackTop = -1;
    // Calculate the next and previous dominant indices for each number
    for (int index = 0; index < numsSize; index++) {
        // While the stack is not empty and the current prime score is greater than the stack's top
        while ((decreasingPrimeScoreStackTop >= 0) &&
               (primeScores[decreasingPrimeScoreStack[decreasingPrimeScoreStackTop]] < primeScores[index])) {
            int topIndex = decreasingPrimeScoreStack[decreasingPrimeScoreStackTop];
            decreasingPrimeScoreStackTop--;
            // Set the next dominant element for the popped index
            nextDominant[topIndex] = index;
        }
        // If the stack is not empty, set the previous dominant element for the current index
        if (decreasingPrimeScoreStackTop >= 0) {
            prevDominant[index] = decreasingPrimeScoreStack[decreasingPrimeScoreStackTop];
        }
        // Push the current index onto the stack
        decreasingPrimeScoreStack[++decreasingPrimeScoreStackTop] = index;
    }

    // Calculate the number of subarrays in which each element is dominant
    long long numOfSubarrays[numsSize];
    memset(numOfSubarrays, 0, sizeof(numOfSubarrays));
    for (int index = 0; index < numsSize; index++) {
        numOfSubarrays[index] = (long long)(nextDominant[index] - index) * (index - prevDominant[index]);
    }

    // Priority queue to process elements in decreasing order of their value
    pair processingQueue[numsSize];
    memset(processingQueue, 0, sizeof(processingQueue));
    int processingQueueIndex = 0;
    // Push each number and its index onto the priority queue
    for (int index = 0; index < numsSize; index++) {
        processingQueue[index].value = nums[index];
        processingQueue[index].index = index;
        processingQueueIndex++;
    }
    qsort(processingQueue, numsSize, sizeof(pair), compareStruct);

    // Process elements while there are operations left
    long long score = 1;
    while (k > 0) {
        // Get the element with the maximum value from the queue
        processingQueueIndex--;
        long long num = processingQueue[processingQueueIndex].value;
        int index = processingQueue[processingQueueIndex].index;
        // Calculate the number of operations to apply on the current element
        long long operations = fmin((long long)k, numOfSubarrays[index]);
        // Update the score by raising the element to the power of operations
        score = (score * powerOfModulo(num, operations)) % MODULO;
        // Reduce the remaining operations count
        k -= operations;
    }
    retVal = score;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    int MODULO = 1e9 + 7;

    long long powerOfModulo(long long base, long long exponent) {
        long long retVal = 1;

        // Calculate the exponentiation using binary exponentiation
        while (exponent > 0) {
            // If the exponent is odd, multiply the result by the base
            if (exponent % 2 == 1) {
                retVal = ((retVal * base) % MODULO);
            }

            // Square the base and halve the exponent
            base = (base * base) % MODULO;
            exponent /= 2;
        }

        return retVal;
    }

   public:
    int maximumScore(vector<int>& nums, int k) {
        int retVal = 0;

        int numsSize = nums.size();

        // Calculate the prime score for each number in nums
        vector<int> primeScores(numsSize);
        for (int index = 0; index < numsSize; index++) {
            int num = nums[index];
            // Check for prime factors from 2 to sqrt(n)
            for (int factor = 2; factor <= sqrt(num); factor++) {
                if (num % factor != 0) {
                    continue;
                }
                // Increment prime score for each prime factor
                primeScores[index]++;
                // Remove all occurrences of the prime factor from num
                while (num % factor == 0) {
                    num /= factor;
                }
            }
            // If num is still greater than or equal to 2, it's a prime factor
            if (num >= 2) {
                primeScores[index]++;
            }
        }

        // Initialize next and previous dominant index arrays
        vector<int> nextDominant(numsSize, numsSize);
        vector<int> prevDominant(numsSize, -1);
        // Stack to store indices for monotonic decreasing prime score
        stack<int> decreasingPrimeScoreStack;
        // Calculate the next and previous dominant indices for each number
        for (int index = 0; index < numsSize; index++) {
            // While the stack is not empty and the current prime score is greater than the stack's top
            while ((decreasingPrimeScoreStack.empty() == false) &&
                   (primeScores[decreasingPrimeScoreStack.top()] < primeScores[index])) {
                int topIndex = decreasingPrimeScoreStack.top();
                decreasingPrimeScoreStack.pop();
                // Set the next dominant element for the popped index
                nextDominant[topIndex] = index;
            }
            // If the stack is not empty, set the previous dominant element for the current index
            if (decreasingPrimeScoreStack.empty() == false) {
                prevDominant[index] = decreasingPrimeScoreStack.top();
            }
            // Push the current index onto the stack
            decreasingPrimeScoreStack.push(index);
        }

        // Calculate the number of subarrays in which each element is dominant
        vector<long long> numOfSubarrays(numsSize);
        for (int index = 0; index < numsSize; index++) {
            numOfSubarrays[index] = (long long)(nextDominant[index] - index) * (index - prevDominant[index]);
        }

        // Priority queue to process elements in decreasing order of their value
        priority_queue<pair<int, int>> processingQueue;
        // Push each number and its index onto the priority queue
        for (int index = 0; index < numsSize; index++) {
            processingQueue.push({nums[index], index});
        }

        // Process elements while there are operations left
        long long score = 1;
        while (k > 0) {
            // Get the element with the maximum value from the queue
            auto [num, index] = processingQueue.top();
            processingQueue.pop();
            // Calculate the number of operations to apply on the current element
            long long operations = min((long long)k, numOfSubarrays[index]);
            // Update the score by raising the element to the power of operations
            score = (score * powerOfModulo(num, operations)) % MODULO;
            // Reduce the remaining operations count
            k -= operations;
        }
        retVal = score;

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

    def powerOfModulo(self, base: int, exponent: int) -> int:
        retVal = 1

        # Calculate the exponentiation using binary exponentiation
        while exponent > 0:
            # If the exponent is odd, multiply the result by the base
            if exponent % 2 == 1:
                retVal = (retVal * base) % self.MODULO

            # Square the base and halve the exponent
            base = (base * base) % self.MODULO
            exponent //= 2

        return retVal

    def maximumScore(self, nums: List[int], k: int) -> int:
        retVal = 1

        numsSize = len(nums)

        primeScores = [0] * numsSize
        # Calculate the prime score for each number in nums
        for index in range(numsSize):
            num = nums[index]
            # Check for prime factors from 2 to sqrt(n)
            for factor in range(2, int(sqrt(num)) + 1):
                if num % factor != 0:
                    continue
                # Increment prime score for each prime factor
                primeScores[index] += 1
                # Remove all occurrences of the prime factor from num
                while num % factor == 0:
                    num //= factor

            # If num is still greater than or equal to 2, it's a prime factor
            if num >= 2:
                primeScores[index] += 1

        # Initialize next and previous dominant index arrays
        nextDominant = [numsSize] * numsSize
        prevDominant = [-1] * numsSize
        # Stack to store indices for monotonic decreasing prime score
        decreasingPrimeScoreStack = []
        # Calculate the next and previous dominant indices for each number
        for index in range(numsSize):
            # While the stack is not empty and the current prime score is greater than the stack's top
            while (decreasingPrimeScoreStack) and (primeScores[decreasingPrimeScoreStack[-1]] < primeScores[index]):
                topIndex = decreasingPrimeScoreStack.pop()
                # Set the next dominant element for the popped index
                nextDominant[topIndex] = index

            # If the stack is not empty, set the previous dominant element for the current index
            if decreasingPrimeScoreStack:
                prevDominant[index] = decreasingPrimeScoreStack[-1]

            # Push the current index onto the stack
            decreasingPrimeScoreStack.append(index)

        # Calculate the number of subarrays in which each element is dominant
        numOfSubarrays = [0] * numsSize
        for index in range(numsSize):
            numOfSubarrays[index] = (nextDominant[index] - index) * (index - prevDominant[index])

        # Priority queue to process elements in decreasing order of their value
        processingQueue = []
        # Push each number and its index onto the priority queue
        for index in range(numsSize):
            heappush(processingQueue, (-nums[index], index))

        # Process elements while there are operations left
        while k > 0:
            # Get the element with the maximum value from the queue
            num, index = heappop(processingQueue)
            num = -num  # Negate back to positive

            # Calculate the number of operations to apply on the current element
            operations = min(k, numOfSubarrays[index])

            # Update the score by raising the element to the power of operations
            retVal = (retVal * self.powerOfModulo(num, operations)) % self.MODULO

            # Reduce the remaining operations count
            k -= operations

        return retVal
```

</details>
