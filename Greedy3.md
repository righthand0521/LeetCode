# Greedy

## [2027. Minimum Moves to Convert String](https://leetcode.com/problems/minimum-moves-to-convert-string/)  1346

- [Official](https://leetcode.cn/problems/minimum-moves-to-convert-string/solutions/2032769/zhuan-huan-zi-fu-chuan-de-zui-shao-cao-z-cji1/)

<details><summary>Description</summary>

```text
You are given a string s consisting of n characters which are either 'X' or 'O'.

A move is defined as selecting three consecutive characters of s and converting them to 'O'.
Note that if a move is applied to the character 'O', it will stay the same.

Return the minimum number of moves required so that all the characters of s are converted to 'O'.

Example 1:
Input: s = "XXX"
Output: 1
Explanation: XXX -> OOO
We select all the 3 characters and convert them in one move.

Example 2:
Input: s = "XXOX"
Output: 2
Explanation: XXOX -> OOOX -> OOOO
We select the first 3 characters in the first move, and convert them to 'O'.
Then we select the last 3 characters and convert them so that the final string contains all 'O's.

Example 3:
Input: s = "OOOO"
Output: 0
Explanation: There are no 'X's in s to convert.

Constraints:
3 <= s.length <= 1000
s[i] is either 'X' or 'O'.
```

</details>

<details><summary>C</summary>

```c
int minimumMoves(char* s) {
    int retVal = 0;

    int len = strlen(s);

#define CONTINUE_COUNT (3)
#define CONTINUE_CHAR 'X'
    int count = 0;
    int i;
    for (i = 0; i < len; ++i) {
        if (s[i] == CONTINUE_CHAR) {
            ++count;
        } else {
            if (count != 0) {
                ++count;
            }
        }

        if (count == CONTINUE_COUNT) {
            ++retVal;
            count = 0;
        }
    }
    if (count != 0) {
        ++retVal;
    }

    return retVal;
}
```

</details>

## [2037. Minimum Number of Moves to Seat Everyone](https://leetcode.com/problems/minimum-number-of-moves-to-seat-everyone/)  1356

- [Official](https://leetcode.com/problems/minimum-number-of-moves-to-seat-everyone/editorial/)
- [Official](https://leetcode.cn/problems/minimum-number-of-moves-to-seat-everyone/solutions/2037615/shi-mei-wei-xue-sheng-du-you-zuo-wei-de-oll4i/)

<details><summary>Description</summary>

```text
There are n seats and n students in a room.
You are given an array seats of length n, where seats[i] is the position of the ith seat.
You are also given the array students of length n, where students[j] is the position of the jth student.

You may perform the following move any number of times:
- Increase or decrease the position of the ith student by 1
 (i.e., moving the ith student from position x to x + 1 or x - 1)

Return the minimum number of moves required to
move each student to a seat such that no two students are in the same seat.

Note that there may be multiple seats or students in the same position at the beginning.

Example 1:
Input: seats = [3,1,5], students = [2,7,4]
Output: 4
Explanation: The students are moved as follows:
- The first student is moved from from position 2 to position 1 using 1 move.
- The second student is moved from from position 7 to position 5 using 2 moves.
- The third student is moved from from position 4 to position 3 using 1 move.
In total, 1 + 2 + 1 = 4 moves were used.

Example 2:
Input: seats = [4,1,5,9], students = [1,3,2,6]
Output: 7
Explanation: The students are moved as follows:
- The first student is not moved.
- The second student is moved from from position 3 to position 4 using 1 move.
- The third student is moved from from position 2 to position 5 using 3 moves.
- The fourth student is moved from from position 6 to position 9 using 3 moves.
In total, 0 + 1 + 3 + 3 = 7 moves were used.

Example 3:
Input: seats = [2,2,6,6], students = [1,3,2,6]
Output: 4
Explanation: Note that there are two seats at position 2 and two seats at position 6.
The students are moved as follows:
- The first student is moved from from position 1 to position 2 using 1 move.
- The second student is moved from from position 3 to position 6 using 3 moves.
- The third student is not moved.
- The fourth student is not moved.
In total, 1 + 3 + 0 + 0 = 4 moves were used.

Constraints:
n == seats.length == students.length
1 <= n <= 100
1 <= seats[i], students[j] <= 100
```

<details><summary>Hint</summary>

```text
1. Can we sort the arrays to help solve the problem?
2. Can we greedily match each student to a seat?
3. The smallest positioned student will go to the smallest positioned chair,
   and then the next smallest positioned student will go to the next smallest positioned chair, and so on.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int minMovesToSeat(int* seats, int seatsSize, int* students, int studentsSize) {
    int retVal = 0;

    qsort(seats, seatsSize, sizeof(int), compareInteger);
    qsort(students, studentsSize, sizeof(int), compareInteger);

    int i;
    for (i = 0; i < seatsSize; ++i) {
        retVal += abs(seats[i] - students[i]);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minMovesToSeat(vector<int>& seats, vector<int>& students) {
        int retVal = 0;

        sort(seats.begin(), seats.end());
        sort(students.begin(), students.end());

        int seatsSize = seats.size();
        for (int i = 0; i < seatsSize; ++i) {
            retVal += abs(seats[i] - students[i]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minMovesToSeat(self, seats: List[int], students: List[int]) -> int:
        retVal = 0

        seats.sort()
        students.sort()
        for x, y in zip(seats, students):
            retVal += abs(x-y)

        return retVal
```

</details>

## [2038. Remove Colored Pieces if Both Neighbors are the Same Color](https://leetcode.com/problems/remove-colored-pieces-if-both-neighbors-are-the-same-color/)  1467

- [Official](https://leetcode.com/problems/remove-colored-pieces-if-both-neighbors-are-the-same-color/editorial/)
- [Official](https://leetcode.cn/problems/remove-colored-pieces-if-both-neighbors-are-the-same-color/solutions/1355114/ru-guo-xiang-lin-liang-ge-yan-se-jun-xia-rfbk/)

<details><summary>Description</summary>

```text
There are n pieces arranged in a line, and each piece is colored either by 'A' or by 'B'.
You are given a string colors of length n where colors[i] is the color of the ith piece.

Alice and Bob are playing a game where they take alternating turns removing pieces from the line.
In this game, Alice moves first.
- Alice is only allowed to remove a piece colored 'A' if both its neighbors are also colored 'A'.
  She is not allowed to remove pieces that are colored 'B'.
- Bob is only allowed to remove a piece colored 'B' if both its neighbors are also colored 'B'.
  He is not allowed to remove pieces that are colored 'A'.
- Alice and Bob cannot remove pieces from the edge of the line.
- If a player cannot make a move on their turn, that player loses and the other player wins.

Assuming Alice and Bob play optimally, return true if Alice wins, or return false if Bob wins.

Example 1:
Input: colors = "AAABABB"
Output: true
Explanation:
AAABABB -> AABABB
Alice moves first.
She removes the second 'A' from the left since that is the only 'A' whose neighbors are both 'A'.
Now it's Bob's turn.
Bob cannot make a move on his turn since there are no 'B's whose neighbors are both 'B'.
Thus, Alice wins, so return true.

Example 2:
Input: colors = "AA"
Output: false
Explanation:
Alice has her turn first.
There are only two 'A's and both are on the edge of the line, so she cannot move on her turn.
Thus, Bob wins, so return false.

Example 3:
Input: colors = "ABBBBBBBAAA"
Output: false
Explanation:
ABBBBBBBAAA -> ABBBBBBBAA
Alice moves first.
Her only option is to remove the second to last 'A' from the right.
ABBBBBBBAA -> ABBBBBBAA
Next is Bob's turn.
He has many options for which 'B' piece to remove. He can pick any.
On Alice's second turn, she has no more pieces that she can remove.
Thus, Bob wins, so return false.

Constraints:
1 <= colors.length <= 10^5
colors consists of only the letters 'A' and 'B'
```

<details><summary>Hint</summary>

```text
1. Does the number of moves a player can make depend on what the other player does? No
2. How many moves can Alice make if colors == "AAAAAA"
3. If a group of n consecutive pieces has the same color,
   the player can take n - 2 of those pieces if n is greater than or equal to 3
```

</details>

</details>

<details><summary>C</summary>

```c
bool winnerOfGame(char *colors) {
    bool retVal = false;

    int colorsSize = strlen(colors);

    int Alice = 0;
    int Bob = 0;
    int i;
    for (i = 1; i < colorsSize - 1; ++i) {
        // The number of moves available to Alice is the number of times the substring "AAA" appears.
        // The number of moves available to Bob is the number of times the substring "BBB" appears.
        if ((colors[i] == colors[i - 1]) && (colors[i] == colors[i + 1])) {
            if (colors[i] == 'A') {
                Alice++;
            } else if (colors[i] == 'B') {
                Bob++;
            }
        }
    }
    if (Alice > Bob) {
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
    bool winnerOfGame(string colors) {
        bool retVal = false;

        int colorsSize = colors.size();

        int Alice = 0;
        int Bob = 0;
        for (int i = 1; i < colorsSize - 1; ++i) {
            // The number of moves available to Alice is the number of times the substring "AAA" appears.
            // The number of moves available to Bob is the number of times the substring "BBB" appears.
            if ((colors[i] == colors[i - 1]) && (colors[i] == colors[i + 1])) {
                if (colors[i] == 'A') {
                    Alice++;
                } else if (colors[i] == 'B') {
                    Bob++;
                }
            }
        }
        if (Alice > Bob) {
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
    def winnerOfGame(self, colors: str) -> bool:
        retVal = False

        colorsSize = len(colors)

        Alice = 0
        Bob = 0
        for i in range(1, colorsSize-1):
            # The number of moves available to Alice is the number of times the substring "AAA" appears.
            # The number of moves available to Bob is the number of times the substring "BBB" appears.
            if (colors[i] == colors[i-1]) and (colors[i] == colors[i+1]):
                if colors[i] == 'A':
                    Alice += 1
                elif colors[i] == 'B':
                    Bob += 1
        if Alice > Bob:
            retVal = True

        return retVal
```

</details>

## [2126. Destroying Asteroids](https://leetcode.com/problems/destroying-asteroids/)  1334

- [Official](https://leetcode.cn/problems/destroying-asteroids/solutions/1202026/cui-hui-xiao-xing-xing-by-leetcode-solut-ng2v/)

<details><summary>Description</summary>

```text
You are given an integer mass, which represents the original mass of a planet.
You are further given an integer array asteroids, where asteroids[i] is the mass of the ith asteroid.

You can arrange for the planet to collide with the asteroids in any arbitrary order.
If the mass of the planet is greater than or equal to the mass of the asteroid,
the asteroid is destroyed and the planet gains the mass of the asteroid.
Otherwise, the planet is destroyed.

Return true if all asteroids can be destroyed. Otherwise, return false.

Example 1:
Input: mass = 10, asteroids = [3,9,19,5,21]
Output: true
Explanation: One way to order the asteroids is [9,19,5,3,21]:
- The planet collides with the asteroid with a mass of 9. New planet mass: 10 + 9 = 19
- The planet collides with the asteroid with a mass of 19. New planet mass: 19 + 19 = 38
- The planet collides with the asteroid with a mass of 5. New planet mass: 38 + 5 = 43
- The planet collides with the asteroid with a mass of 3. New planet mass: 43 + 3 = 46
- The planet collides with the asteroid with a mass of 21. New planet mass: 46 + 21 = 67
All asteroids are destroyed.

Example 2:
Input: mass = 5, asteroids = [4,9,23,4]
Output: false
Explanation:
The planet cannot ever gain enough mass to destroy the asteroid with a mass of 23.
After the planet destroys the other asteroids, it will have a mass of 5 + 4 + 9 + 4 = 22.
This is less than 23, so a collision would not destroy the last asteroid.

Constraints:
1 <= mass <= 10^5
1 <= asteroids.length <= 10^5
1 <= asteroids[i] <= 10^5
```

<details><summary>Hint</summary>

```text
1. Choosing the asteroid to collide with can be done greedily.
2. If an asteroid will destroy the planet, then every bigger asteroid will also destroy the planet.
3. You only need to check the smallest asteroid at each collision.
   If it will destroy the planet, then every other asteroid will also destroy the planet.
4. Sort the asteroids in non-decreasing order by mass, then greedily try to collide with the asteroids in that order.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
bool asteroidsDestroyed(int mass, int* asteroids, int asteroidsSize) {
    bool retVal = true;

    qsort(asteroids, asteroidsSize, sizeof(int), compareInteger);
    long long sum = mass;  // 1 <= asteroids.length <= 10^5, 1 <= asteroids[i] <= 10^5.
    int i;
    for (i = 0; i < asteroidsSize; ++i) {
        if (sum < asteroids[i]) {
            retVal = false;
            break;
        }
        sum += asteroids[i];
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    bool asteroidsDestroyed(int mass, vector<int>& asteroids) {
        bool retVal = true;

        sort(asteroids.begin(), asteroids.end());
        long long sum = mass;  // 1 <= asteroids.length <= 10^5, 1 <= asteroids[i] <= 10^5.
        for (auto asteroid : asteroids) {
            if (sum < asteroid) {
                retVal = false;
                break;
            }
            sum += asteroid;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def asteroidsDestroyed(self, mass: int, asteroids: List[int]) -> bool:
        retVal = True

        asteroids.sort()
        sum = mass
        for asteroid in asteroids:
            if sum < asteroid:
                retVal = False
                break
            sum += asteroid

        return retVal
```

</details>

## [2182. Construct String With Repeat Limit](https://leetcode.com/problems/construct-string-with-repeat-limit/)  1680

- [Official](https://leetcode.com/problems/construct-string-with-repeat-limit/editorial/)
- [Official](https://leetcode.cn/problems/construct-string-with-repeat-limit/solutions/1300982/gou-zao-xian-zhi-zhong-fu-de-zi-fu-chuan-v02s/)

<details><summary>Description</summary>

```text
You are given a string s and an integer repeatLimit.
Construct a new string repeatLimitedString using the characters of s
such that no letter appears more than repeatLimit times in a row.
You do not have to use all characters from s.

Return the lexicographically largest repeatLimitedString possible.

A string a is lexicographically larger than a string b if in the first position where a and b differ,
string a has a letter that appears later in the alphabet than the corresponding letter in b.
If the first min(a.length, b.length) characters do not differ,
then the longer string is the lexicographically larger one.

Example 1:
Input: s = "cczazcc", repeatLimit = 3
Output: "zzcccac"
Explanation: We use all of the characters from s to construct the repeatLimitedString "zzcccac".
The letter 'a' appears at most 1 time in a row.
The letter 'c' appears at most 3 times in a row.
The letter 'z' appears at most 2 times in a row.
Hence, no letter appears more than repeatLimit times in a row and the string is a valid repeatLimitedString.
The string is the lexicographically largest repeatLimitedString possible so we return "zzcccac".
Note that the string "zzcccca" is lexicographically larger but the letter 'c' appears more than 3 times in a row,
so it is not a valid repeatLimitedString.

Example 2:
Input: s = "aababab", repeatLimit = 2
Output: "bbabaa"
Explanation: We use only some of the characters from s to construct the repeatLimitedString "bbabaa".
The letter 'a' appears at most 2 times in a row.
The letter 'b' appears at most 2 times in a row.
Hence, no letter appears more than repeatLimit times in a row and the string is a valid repeatLimitedString.
The string is the lexicographically largest repeatLimitedString possible so we return "bbabaa".
Note that the string "bbabaaa" is lexicographically larger but the letter 'a' appears more than 2 times in a row,
so it is not a valid repeatLimitedString.

Constraints:
1 <= repeatLimit <= s.length <= 10^5
s consists of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Start constructing the string in descending order of characters.
2. When repeatLimit is reached, pick the next largest character.
```

</details>

</details>

<details><summary>C</summary>

```c
#ifndef HEAP_H
#define HEAP_H

void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}
typedef struct {
    int* data;     // Array to store the heap elements
    int size;      // Current size of the heap
    int capacity;  // Maximum capacity of the heap
} MaxHeap;
MaxHeap* createMaxHeap(int capacity) {
    MaxHeap* pObj = NULL;

    pObj = (MaxHeap*)malloc(sizeof(MaxHeap));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }

    pObj->data = (int*)malloc(capacity * sizeof(int));
    if (pObj == NULL) {
        perror("malloc");
        free(pObj);
        pObj = NULL;
        return pObj;
    }
    pObj->size = 0;
    pObj->capacity = capacity;

    return pObj;
}
void heapifyMaxHeap(MaxHeap* pObj, int index) {
    int biggest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    // Function to heapify the heap starting from the given index
    if ((left < pObj->size) && (pObj->data[left] > pObj->data[biggest])) {
        biggest = left;
    }

    if ((right < pObj->size) && (pObj->data[right] > pObj->data[biggest])) {
        biggest = right;
    }

    if (biggest != index) {
        swap(&pObj->data[index], &pObj->data[biggest]);
        heapifyMaxHeap(pObj, biggest);
    }
}
void pushMaxHeap(MaxHeap* pObj, int value) {
    if (pObj->size == pObj->capacity) {
        printf("Heap is full. Cannot insert more elements.\n");
        return;
    }

    int index = pObj->size++;
    pObj->data[index] = value;

    // Fix the max heap property by comparing the value with its parent
    while ((index != 0) && (pObj->data[(index - 1) / 2] < pObj->data[index])) {
        swap(&pObj->data[(index - 1) / 2], &pObj->data[index]);
        index = (index - 1) / 2;
    }
}
int popMaxHeap(MaxHeap* pObj) {
    int retVal = -1;

    if (pObj->size == 0) {
        printf("Heap is empty. Cannot remove elements.\n");
        return retVal;
    }

    retVal = pObj->data[0];
    pObj->data[0] = pObj->data[pObj->size - 1];
    pObj->size--;
    heapifyMaxHeap(pObj, 0);

    return retVal;
}
void printMaxHeap(MaxHeap* pObj) {
    printf("Max Heap: ");
    for (int i = 0; i < pObj->size; i++) {
        printf("%d ", pObj->data[i]);
    }
    printf("\n");
}
void freeMaxHeap(MaxHeap* pObj) {
    free(pObj->data);
    pObj->data = NULL;
    free(pObj);
    pObj = NULL;
}

#endif  // HEAP_H
char* repeatLimitedString(char* s, int repeatLimit) {
    char* pRetVal = NULL;

    int sSize = strlen(s);
    int i;

    int returnSize = sSize + 1;
    pRetVal = (char*)calloc(returnSize, sizeof(char));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }

    int frequencySize = 26;  // s consists of lowercase English letters.
    int frequency[frequencySize];
    memset(frequency, 0, sizeof(frequency));
    for (i = 0; i < sSize; ++i) {
        frequency[s[i] - 'a']++;
    }

    MaxHeap* pMaxHeap = createMaxHeap(frequencySize);
    if (pMaxHeap == NULL) {
        return pRetVal;
    }
    for (i = 0; i < frequencySize; ++i) {
        if (frequency[i] != 0) {
            pushMaxHeap(pMaxHeap, i);
        }
    }

    returnSize = 0;
    int charInt, nextCharInt;
    int count, use;
    while (pMaxHeap->size > 0) {
        charInt = popMaxHeap(pMaxHeap);

        count = frequency[charInt];
        use = fmin(count, repeatLimit);
        for (i = 0; i < use; ++i) {
            pRetVal[returnSize++] = charInt + 'a';
        }
        frequency[charInt] -= use;
        if ((frequency[charInt] > 0) && (pMaxHeap->size > 0)) {
            nextCharInt = popMaxHeap(pMaxHeap);

            pRetVal[returnSize++] = nextCharInt + 'a';
            frequency[nextCharInt]--;
            if (frequency[nextCharInt] > 0) {
                pushMaxHeap(pMaxHeap, nextCharInt);
            }

            pushMaxHeap(pMaxHeap, charInt);
        }
    }

    //
    freeMaxHeap(pMaxHeap);
    pMaxHeap = NULL;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string repeatLimitedString(string s, int repeatLimit) {
        string retVal;

        unordered_map<char, int> frequency;
        for (char ch : s) {
            frequency[ch]++;
        }

        priority_queue<char> maxHeap;
        for (auto& [ch, count] : frequency) {
            maxHeap.push(ch);
        }

        while (maxHeap.empty() == false) {
            char ch = maxHeap.top();
            maxHeap.pop();

            int count = frequency[ch];
            int use = min(count, repeatLimit);
            retVal.append(use, ch);
            frequency[ch] -= use;
            if ((frequency[ch] > 0) && (maxHeap.empty() == false)) {
                char nextCh = maxHeap.top();
                maxHeap.pop();

                retVal.push_back(nextCh);
                frequency[nextCh]--;
                if (frequency[nextCh] > 0) {
                    maxHeap.push(nextCh);
                }

                maxHeap.push(ch);
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
    def repeatLimitedString(self, s: str, repeatLimit: int) -> str:
        retVal = ""

        frequency = Counter(s)
        maxHeap = []
        for char, count in frequency.items():
            maxHeap.append((-ord(char), count))
        heapify(maxHeap)

        while maxHeap:
            char, count = heappop(maxHeap)
            char = chr(-char)
            use = min(count, repeatLimit)
            retVal += (char * use)

            if (count > use) and maxHeap:
                nextChar, nextCount = heappop(maxHeap)
                retVal += chr(-nextChar)
                if nextCount > 1:
                    heappush(maxHeap, (nextChar, nextCount - 1))
                heappush(maxHeap, (-ord(char), count - use))

        return retVal
```

</details>

## [2244. Minimum Rounds to Complete All Tasks](https://leetcode.com/problems/minimum-rounds-to-complete-all-tasks/)  1371

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array tasks, where tasks[i] represents the difficulty level of a task.
In each round, you can complete either 2 or 3 tasks of the same difficulty level.

Return the minimum rounds required to complete all the tasks, or -1 if it is not possible to complete all the tasks.

Example 1:
Input: tasks = [2,2,3,3,2,4,4,4,4,4]
Output: 4
Explanation: To complete all the tasks, a possible plan is:
- In the first round, you complete 3 tasks of difficulty level 2.
- In the second round, you complete 2 tasks of difficulty level 3.
- In the third round, you complete 3 tasks of difficulty level 4.
- In the fourth round, you complete 2 tasks of difficulty level 4.
It can be shown that all the tasks cannot be completed in fewer than 4 rounds, so the answer is 4.

Example 2:
Input: tasks = [2,3,3]
Output: -1
Explanation: There is only 1 task of difficulty level 2,
but in each round, you can only complete either 2 or 3 tasks of the same difficulty level.
Hence, you cannot complete all the tasks, and the answer is -1.

Constraints:
1 <= tasks.length <= 10^5
1 <= tasks[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Which data structure can you use to store the number of tasks of each difficulty level?
2. For any particular difficulty level, what can be the optimal strategy to complete the tasks using minimum rounds?
3. When can we not complete all tasks of a difficulty level?
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int minimumRounds(int* tasks, int tasksSize) {
    int retVal = 0;

    qsort(tasks, tasksSize, sizeof(int), compareInteger);

    int count = 1;
    int i;
    for (i = 1; i < tasksSize; ++i) {
        if (tasks[i] == tasks[i - 1]) {
            ++count;
            continue;
        }

        if (count == 1) {
            retVal = -1;
            return retVal;
        }
        retVal += (count / 3);
        retVal += (count % 3 == 0 ? 0 : 1);

        count = 1;
    }
    if (count == 1) {
        retVal = -1;
        return retVal;
    }
    retVal += (count / 3);
    retVal += (count % 3 == 0 ? 0 : 1);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minimumRounds(vector<int>& tasks) {
        int retVal = 0;

        sort(tasks.begin(), tasks.end());

        int tasksSize = tasks.size();

        int count = 1;
        for (int i = 1; i < tasksSize; ++i) {
            if (tasks[i] == tasks[i - 1]) {
                ++count;
                continue;
            }

            if (count == 1) {
                retVal = -1;
                return retVal;
            }
            retVal += (count / 3);
            retVal += (count % 3 == 0 ? 0 : 1);

            count = 1;
        }
        if (count == 1) {
            retVal = -1;
            return retVal;
        }
        retVal += (count / 3);
        retVal += (count % 3 == 0 ? 0 : 1);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minimumRounds(self, tasks: List[int]) -> int:
        retVal = 0

        tasks.sort()

        tasksSize = len(tasks)
        count = 1
        for i in range(1, tasksSize):
            if tasks[i] == tasks[i-1]:
                count += 1
                continue

            if count == 1:
                retVal = -1
                return retVal
            retVal += (count // 3)
            retVal += 0 if count % 3 == 0 else 1

            count = 1

        if count == 1:
            retVal = -1
            return retVal
        retVal += (count // 3)
        retVal += 0 if count % 3 == 0 else 1

        return retVal
```

</details>

## [2279. Maximum Bags With Full Capacity of Rocks](https://leetcode.com/problems/maximum-bags-with-full-capacity-of-rocks/)  1249

- [Official](https://leetcode.com/problems/maximum-bags-with-full-capacity-of-rocks/solutions/2643763/maximum-bags-with-full-capacity-of-rocks/)

<details><summary>Description</summary>

```text
You have n bags numbered from 0 to n - 1.
You are given two 0-indexed integer arrays capacity and rocks.
The ith bag can hold a maximum of capacity[i] rocks and currently contains rocks[i] rocks.
You are also given an integer additionalRocks, the number of additional rocks you can place in any of the bags.

Return the maximum number of bags that could have full capacity after placing the additional rocks in some bags.

Example 1:
Input: capacity = [2,3,4,5], rocks = [1,2,4,4], additionalRocks = 2
Output: 3
Explanation:
Place 1 rock in bag 0 and 1 rock in bag 1.
The number of rocks in each bag are now [2,3,4,4].
Bags 0, 1, and 2 have full capacity.
There are 3 bags at full capacity, so we return 3.
It can be shown that it is not possible to have more than 3 bags at full capacity.
Note that there may be other ways of placing the rocks that result in an answer of 3.

Example 2:
Input: capacity = [10,2,2], rocks = [2,2,0], additionalRocks = 100
Output: 3
Explanation:
Place 8 rocks in bag 0 and 2 rocks in bag 2.
The number of rocks in each bag are now [10,2,2].
Bags 0, 1, and 2 have full capacity.
There are 3 bags at full capacity, so we return 3.
It can be shown that it is not possible to have more than 3 bags at full capacity.
Note that we did not use all of the additional rocks.

Constraints:
n == capacity.length == rocks.length
1 <= n <= 5 * 10^4
1 <= capacity[i] <= 10^9
0 <= rocks[i] <= capacity[i]
1 <= additionalRocks <= 10^9
```

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int maximumBags(int* capacity, int capacitySize, int* rocks, int rocksSize, int additionalRocks) {
    int retVal = 0;

    int space[capacitySize];
    memset(space, 0, sizeof(space));
    int i;
    for (i = 0; i < capacitySize; ++i) {
        space[i] = capacity[i] - rocks[i];
    }
    qsort(space, capacitySize, sizeof(int), compareInteger);

    for (i = 0; i < capacitySize; ++i) {
        additionalRocks -= space[i];
        if (additionalRocks >= 0) {
            ++retVal;
            continue;
        }
        break;
    }

    return retVal;
}
```

</details>

## [2294. Partition Array Such That Maximum Difference Is K](https://leetcode.com/problems/partition-array-such-that-maximum-difference-is-k/)  1416

- [Official](https://leetcode.com/problems/partition-array-such-that-maximum-difference-is-k/editorial/)
- [Official](https://leetcode.cn/problems/partition-array-such-that-maximum-difference-is-k/solutions/3703726/hua-fen-shu-zu-shi-zui-da-chai-wei-k-by-z4vb2/)

<details><summary>Description</summary>

```text
You are given an integer array nums and an integer k.
You may partition nums into one or more subsequences
such that each element in nums appears in exactly one of the subsequences.

Return the minimum number of subsequences needed
such that the difference between the maximum and minimum values in each subsequence is at most k.

A subsequence is a sequence that can be derived from another sequence
by deleting some or no elements without changing the order of the remaining elements.

Example 1:
Input: nums = [3,6,1,2,5], k = 2
Output: 2
Explanation:
We can partition nums into the two subsequences [3,1,2] and [6,5].
The difference between the maximum and minimum value in the first subsequence is 3 - 1 = 2.
The difference between the maximum and minimum value in the second subsequence is 6 - 5 = 1.
Since two subsequences were created, we return 2.
It can be shown that 2 is the minimum number of subsequences needed.

Example 2:
Input: nums = [1,2,3], k = 1
Output: 2
Explanation:
We can partition nums into the two subsequences [1,2] and [3].
The difference between the maximum and minimum value in the first subsequence is 2 - 1 = 1.
The difference between the maximum and minimum value in the second subsequence is 3 - 3 = 0.
Since two subsequences were created, we return 2.
Note that another optimal solution is to partition nums into the two subsequences [1] and [2,3].

Example 3:
Input: nums = [2,2,4,5], k = 0
Output: 3
Explanation:
We can partition nums into the three subsequences [2,2], [4], and [5].
The difference between the maximum and minimum value in the first subsequences is 2 - 2 = 0.
The difference between the maximum and minimum value in the second subsequences is 4 - 4 = 0.
The difference between the maximum and minimum value in the third subsequences is 5 - 5 = 0.
Since three subsequences were created, we return 3.
It can be shown that 3 is the minimum number of subsequences needed.

Constraints:
1 <= nums.length <= 10^5
0 <= nums[i] <= 10^5
0 <= k <= 10^5
```

<details><summary>Hint</summary>

```text
1. Which values in each subsequence matter? The only values that matter are the maximum and minimum values.
2. Let the maximum and minimum values of a subsequence be Max and Min.
   It is optimal to place all values in between Max and Min in the original array in the same subsequence as Max and Min.
3. Sort the array.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int partitionArray(int* nums, int numsSize, int k) {
    int retVal = 1;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int minValue = nums[0];
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] - minValue > k) {
            retVal++;
            minValue = nums[i];
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
    int partitionArray(vector<int>& nums, int k) {
        int retVal = 1;

        sort(nums.begin(), nums.end());

        int minValue = nums[0];
        int numsSize = nums.size();
        for (int i = 0; i < numsSize; i++) {
            if (nums[i] - minValue > k) {
                retVal++;
                minValue = nums[i];
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
    def partitionArray(self, nums: List[int], k: int) -> int:
        retVal = 1

        nums.sort()

        minValue = nums[0]
        for num in nums:
            if num - minValue > k:
                retVal += 1
                minValue = num

        return retVal
```

</details>

## [2311. Longest Binary Subsequence Less Than or Equal to K](https://leetcode.com/problems/longest-binary-subsequence-less-than-or-equal-to-k/)  1839

- [Official](https://leetcode.com/problems/longest-binary-subsequence-less-than-or-equal-to-k/editorial/)
- [Official](https://leetcode.cn/problems/longest-binary-subsequence-less-than-or-equal-to-k/solutions/3701151/xiao-yu-deng-yu-k-de-zui-chang-er-jin-zh-7vk8/)

<details><summary>Description</summary>

```text
You are given a binary string s and a positive integer k.

Return the length of the longest subsequence of s that makes up a binary number less than or equal to k.

Note:
- The subsequence can contain leading zeroes.
- The empty string is considered to be equal to 0.
- A subsequence is a string that can be derived from another string
  by deleting some or no characters without changing the order of the remaining characters.


Example 1:
Input: s = "1001010", k = 5
Output: 5
Explanation: The longest subsequence of s that makes up a binary number less than or equal to 5 is "00010",
as this number is equal to 2 in decimal.
Note that "00100" and "00101" are also possible, which are equal to 4 and 5 in decimal, respectively.
The length of this subsequence is 5, so 5 is returned.

Example 2:
Input: s = "00101001", k = 1
Output: 6
Explanation: "000001" is the longest subsequence of s that makes up a binary number less than or equal to 1,
as this number is equal to 1 in decimal.
The length of this subsequence is 6, so 6 is returned.

Constraints:
1 <= s.length <= 1000
s[i] is either '0' or '1'.
1 <= k <= 10^9
```

<details><summary>Hint</summary>

```text
1. Choosing a subsequence from the string is equivalent to deleting all the other digits.
2. If you were to remove a digit, which one should you remove to reduce the value of the string?
```

</details>

</details>

<details><summary>C</summary>

```c
int longestSubsequence(char* s, int k) {
    int retVal = 0;

    int sm = 0;
    int bits = (int)(log2(k)) + 1;
    int sSize = strlen(s);
    for (int i = 0; i < sSize; i++) {
        char ch = s[sSize - 1 - i];
        if (ch == '1') {
            if ((i < bits) && (sm + (1 << i) <= k)) {
                sm += (1 << i);
                retVal++;
            }
        } else {
            retVal++;
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
    int longestSubsequence(string s, int k) {
        int retVal = 0;

        int sm = 0;
        int bits = 32 - __builtin_clz(k);
        int sSize = s.size();
        for (int i = 0; i < sSize; ++i) {
            char ch = s[sSize - 1 - i];
            if (ch == '1') {
                if ((i < bits) && (sm + (1 << i) <= k)) {
                    sm += (1 << i);
                    retVal++;
                }
            } else {
                retVal++;
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
    def longestSubsequence(self, s: str, k: int) -> int:
        retVal = 0

        sm = 0
        bits = k.bit_length()
        for i, ch in enumerate(s[::-1]):
            if ch == "1":
                if (i < bits) and (sm + (1 << i) <= k):
                    sm += (1 << i)
                    retVal += 1
            else:
                retVal += 1

        return retVal
```

</details>

## [2335. Minimum Amount of Time to Fill Cups](https://leetcode.com/problems/minimum-amount-of-time-to-fill-cups/)  1360

- [Official](https://leetcode.cn/problems/minimum-amount-of-time-to-fill-cups/solutions/2103691/zhuang-man-bei-zi-xu-yao-de-zui-duan-zon-c7y4/)

<details><summary>Description</summary>

```text
ou have a water dispenser that can dispense cold, warm, and hot water.
Every second, you can either fill up 2 cups with different types of water, or 1 cup of any type of water.

You are given a 0-indexed integer array amount of length 3
where amount[0], amount[1], and amount[2] denote the number of cold, warm, and hot water cups you need to fill respectively.
Return the minimum number of seconds needed to fill up all the cups.

Example 1:
Input: amount = [1,4,2]
Output: 4
Explanation: One way to fill up the cups is:
Second 1: Fill up a cold cup and a warm cup.
Second 2: Fill up a warm cup and a hot cup.
Second 3: Fill up a warm cup and a hot cup.
Second 4: Fill up a warm cup.
It can be proven that 4 is the minimum number of seconds needed.

Example 2:
Input: amount = [5,4,4]
Output: 7
Explanation: One way to fill up the cups is:
Second 1: Fill up a cold cup, and a hot cup.
Second 2: Fill up a cold cup, and a warm cup.
Second 3: Fill up a cold cup, and a warm cup.
Second 4: Fill up a warm cup, and a hot cup.
Second 5: Fill up a cold cup, and a hot cup.
Second 6: Fill up a cold cup, and a warm cup.
Second 7: Fill up a hot cup.

Example 3:
Input: amount = [5,0,0]
Output: 5
Explanation: Every second, we fill up a cold cup.

Constraints:
amount.length == 3
0 <= amount[i] <= 100
```

<details><summary>Hint</summary>

```text
1. To minimize the amount of time needed, you want to fill up as many cups as possible in each second.
   This means that you want to maximize the number of seconds where you are filling up two cups.
2. You always want to fill up the two types of water with the most unfilled cups.
```

</details>

</details>

<details><summary>C</summary>

```c
#define BRUTE_FORCE (1)
#define MATH_1 (1)
#define MATH_2 (1)
int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
int fillCups(int* amount, int amountSize) {
    int retVal = 0;

#if (BRUTE_FORCE)
    printf("BRUTE_FORCE\n");

    /* Intuition
     *  142: 131, 021, 010, 000
     *  544: 434, 333, 223, 122, 111, 001, 000
     *  500: 400, 300, 200, 100, 000
     */
    qsort(amount, amountSize, sizeof(int), compareInteger);
    while (amount[0] > 0) {
        if (amount[0] > 0) {
            amount[0] -= 1;
        }

        if (amount[1] > 0) {
            amount[1] -= 1;
        }

        ++retVal;

        qsort(amount, amountSize, sizeof(int), compareInteger);
    }
#elif (MATH_1)
    printf("MATH_1\n");

    /* https://leetcode.cn/problems/minimum-amount-of-time-to-fill-cups/solutions/1658941/by-tsreaper-158c/
     *  Let amount[2] < amount[1] < amount[0]
     *  1. If amount[2] + amount[1] <= amount[0]
     *     => amount[0] is the minimum number of seconds needed
     *  2. If amount[2] + amount[1] > amount[0]
     *     Let Exceed = amount[2] + amount[1] - amount[0]
     *     if Exceed is even: (Exceed / 2) + amount[0] is the minimum number of seconds needed
     *     => (Exceed / 2) + amount[0]
     *        = (amount[2] + amount[1] - amount[0]) / 2 + amount[0]
     *        = (amount[2] + amount[1] + amount[0]) / 2
     *     if Exceed is odd: ((Exceed - 1) / 2) + amount[0] + 1 is the minimum number of seconds needed
     *     => ((Exceed - 1) / 2) + amount[0] + 1
     *        = (amount[2] + amount[1] - amount[0] - 1) / 2 + amount[0] + 1
     *        = (amount[2] + amount[1] + amount[0] + 1) / 2
     */
    qsort(amount, amountSize, sizeof(int), compareInteger);
    if ((amount[1] + amount[2]) <= amount[0]) {
        retVal = amount[0];
    } else {
        retVal = (amount[2] + amount[1] + amount[0] + 1) / 2;
    }
#elif (MATH_2)
    printf("MATH_2\n");

    /* https://leetcode.com/problems/minimum-amount-of-time-to-fill-cups/solutions/2261394/java-c-python-max-max-a-sum-a-1-2/
     *  Let amount[2] < amount[1] < amount[0]
     *  Max between amount[0] and (amount[2] + amount[1] + amount[0] + 1) / 2 is the minimum number of seconds needed
     */
    int maxAmount = 0;
    int i;
    for (i = 0; i < amountSize; ++i) {
        maxAmount = fmax(maxAmount, amount[i]);
        retVal += amount[i];
    }
    retVal = (retVal + 1) / 2;
    retVal = fmax(retVal, maxAmount);
#endif

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define BRUTE_FORCE (0)
#define MATH_1 (0)
#define MATH_2 (1)
   public:
    int fillCups(vector<int>& amount) {
        int retVal = 0;

#if (BRUTE_FORCE)
        cout << "BRUTE_FORCE\n";

        /* Intuition
         *  142: 131, 021, 010, 000
         *  544: 434, 333, 223, 122, 111, 001, 000
         *  500: 400, 300, 200, 100, 000
         */
        sort(amount.begin(), amount.end(), [](const int& n1, const int& n2) {
            // descending order
            return (n1 > n2);
        });
        while (amount[0] > 0) {
            if (amount[0] > 0) {
                amount[0] -= 1;
            }

            if (amount[1] > 0) {
                amount[1] -= 1;
            }

            ++retVal;

            sort(amount.begin(), amount.end(), [](const int& n1, const int& n2) {
                // descending order
                return (n1 > n2);
            });
        }
#elif (MATH_1)
        cout << "MATH_1\n";

        /* https://leetcode.cn/problems/minimum-amount-of-time-to-fill-cups/solutions/1658941/by-tsreaper-158c/
         *  Let amount[2] < amount[1] < amount[0]
         *  1. If amount[2] + amount[1] <= amount[0]
         *     => amount[0] is the minimum number of seconds needed
         *  2. If amount[2] + amount[1] > amount[0]
         *     Let Exceed = amount[2] + amount[1] - amount[0]
         *     if Exceed is even: (Exceed / 2) + amount[0] is the minimum number of seconds needed
         *     => (Exceed / 2) + amount[0]
         *        = (amount[2] + amount[1] - amount[0]) / 2 + amount[0]
         *        = (amount[2] + amount[1] + amount[0]) / 2
         *     if Exceed is odd: ((Exceed - 1) / 2) + amount[0] + 1 is the minimum number of seconds needed
         *     => ((Exceed - 1) / 2) + amount[0] + 1
         *        = (amount[2] + amount[1] - amount[0] - 1) / 2 + amount[0] + 1
         *        = (amount[2] + amount[1] + amount[0] + 1) / 2
         */
        sort(amount.begin(), amount.end());
        if (amount[0] + amount[1] <= amount[2]) {
            retVal = amount[2];
        } else {
            retVal = (amount[0] + amount[1] + amount[2] + 1) / 2;
        }
#elif (MATH_2)
        cout << "MATH_2\n";

        /* https://leetcode.com/problems/minimum-amount-of-time-to-fill-cups/solutions/2261394/java-c-python-max-max-a-sum-a-1-2/
         *  Let amount[2] < amount[1] < amount[0]
         *  Max between amount[0] and (amount[2] + amount[1] + amount[0] + 1) / 2 is the minimum number of seconds
         * needed
         */
        int maxAmount = 0;
        for (auto n : amount) {
            maxAmount = max(maxAmount, n);
            retVal += n;
        }
        retVal = (retVal + 1) / 2;
        retVal = max(retVal, maxAmount);
#endif

        return retVal;
    }
};
```

</details>

## [2366. Minimum Replacements to Sort the Array](https://leetcode.com/problems/minimum-replacements-to-sort-the-array/)  2060

- [Official](https://leetcode.com/problems/minimum-replacements-to-sort-the-array/editorial/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array nums.
In one operation you can replace any element of the array with any two elements that sum to it.
- For example, consider nums = [5,6,7].
  In one operation, we can replace nums[1] with 2 and 4 and convert nums to [5,2,4,7].

Return the minimum number of operations to make an array that is sorted in non-decreasing order.

Example 1:
Input: nums = [3,9,3]
Output: 2
Explanation: Here are the steps to sort the array in non-decreasing order:
- From [3,9,3], replace the 9 with 3 and 6 so the array becomes [3,3,6,3]
- From [3,3,6,3], replace the 6 with 3 and 3 so the array becomes [3,3,3,3,3]
There are 2 steps to sort the array in non-decreasing order. Therefore, we return 2.

Example 2:
Input: nums = [1,2,3,4,5]
Output: 0
Explanation: The array is already in non-decreasing order. Therefore, we return 0.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. It is optimal to never make an operation to the last element of the array.
2. You can iterate from the second last element to the first.
   If the current value is greater than the previous bound,
   we want to break it into pieces so that the smaller one is as large as possible but not larger than the previous one.
```

</details>

</details>

<details><summary>C</summary>

```c
long long minimumReplacement(int* nums, int numsSize) {
    long long retVal = 0;

    long long operations;
    int i;
    for (i = numsSize - 2; i >= 0; --i) {
        if (nums[i] <= nums[i + 1]) {
            continue;
        }

        operations = (nums[i] + nums[i + 1] - 1) / nums[i + 1];
        retVal += (operations - 1);
        nums[i] = nums[i] / operations;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long minimumReplacement(vector<int>& nums) {
        long long retVal = 0;

        int numsSize = nums.size();
        for (int i = numsSize - 2; i >= 0; i--) {
            if (nums[i] <= nums[i + 1]) {
                continue;
            }

            long long operations = (nums[i] + nums[i + 1] - 1LL) / nums[i + 1];
            retVal += (operations - 1);
            nums[i] = nums[i] / operations;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minimumReplacement(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)
        for i in range(numsSize - 2, -1, -1):
            if nums[i] <= nums[i + 1]:
                continue

            operations = (nums[i] + nums[i + 1] - 1) // nums[i + 1]
            retVal += (operations - 1)
            nums[i] = nums[i] // operations

        return retVal
```

</details>

## [2410. Maximum Matching of Players With Trainers](https://leetcode.com/problems/maximum-matching-of-players-with-trainers/)  1381

- [Official](https://leetcode.com/problems/maximum-matching-of-players-with-trainers/editorial/)
- [Official](https://leetcode.cn/problems/maximum-matching-of-players-with-trainers/solutions/1850596/yun-dong-yuan-he-xun-lian-shi-de-zui-da-3icgd/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array players, where players[i] represents the ability of the ith player.
You are also given a 0-indexed integer array trainers,
where trainers[j] represents the training capacity of the jth trainer.

The ith player can match with the jth trainer
if the player's ability is less than or equal to the trainer's training capacity.
Additionally, the ith player can be matched with at most one trainer,
and the jth trainer can be matched with at most one player.

Return the maximum number of matchings between players and trainers that satisfy these conditions.

Example 1:
Input: players = [4,7,9], trainers = [8,2,5,8]
Output: 2
Explanation:
One of the ways we can form two matchings is as follows:
- players[0] can be matched with trainers[0] since 4 <= 8.
- players[1] can be matched with trainers[3] since 7 <= 8.
It can be proven that 2 is the maximum number of matchings that can be formed.

Example 2:
Input: players = [1,1,1], trainers = [10]
Output: 1
Explanation:
The trainer can be matched with any of the 3 players.
Each player can only be matched with one trainer, so the maximum answer is 1.

Constraints:
1 <= players.length, trainers.length <= 10^5
1 <= players[i], trainers[j] <= 10^9

Note: This question is the same as 445: Assign Cookies.
```

<details><summary>Hint</summary>

```text
1. Sort both the arrays.
2. Construct the matching greedily.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int matchPlayersAndTrainers(int* players, int playersSize, int* trainers, int trainersSize) {
    int retVal = 0;

    qsort(players, playersSize, sizeof(int), compareInteger);
    qsort(trainers, trainersSize, sizeof(int), compareInteger);

    int playersIdx = 0;
    int trainersIdx = 0;
    while ((playersIdx < playersSize) && (trainersIdx < trainersSize)) {
        while ((trainersIdx < trainersSize) && (players[playersIdx] > trainers[trainersIdx])) {
            ++trainersIdx;
        }

        if (trainersIdx < trainersSize) {
            ++retVal;
        }

        ++playersIdx;
        ++trainersIdx;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers) {
        int retVal = 0;

        sort(players.begin(), players.end());
        int playersSize = players.size();
        int playersIdx = 0;

        sort(trainers.begin(), trainers.end());
        int trainersSize = trainers.size();
        int trainersIdx = 0;

        while ((playersIdx < playersSize) && (trainersIdx < trainersSize)) {
            while ((trainersIdx < trainersSize) && (players[playersIdx] > trainers[trainersIdx])) {
                ++trainersIdx;
            }

            if (trainersIdx < trainersSize) {
                ++retVal;
            }

            ++playersIdx;
            ++trainersIdx;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def matchPlayersAndTrainers(self, players: List[int], trainers: List[int]) -> int:
        retVal = 0

        players.sort()
        playersSize = len(players)
        playersIdx = 0

        trainers.sort()
        trainersSize = len(trainers)
        trainersIdx = 0

        while (playersIdx < playersSize) and (trainersIdx < trainersSize):
            while (trainersIdx < trainersSize) and (players[playersIdx] > trainers[trainersIdx]):
                trainersIdx += 1
            retVal += 1 if trainersIdx < trainersSize else 0
            playersIdx += 1
            trainersIdx += 1

        return retVal
```

</details>

## [2434. Using a Robot to Print the Lexicographically Smallest String](https://leetcode.com/problems/using-a-robot-to-print-the-lexicographically-smallest-string/)  1953

- [Official](https://leetcode.com/problems/using-a-robot-to-print-the-lexicographically-smallest-string/editorial/)
- [Official](https://leetcode.cn/problems/using-a-robot-to-print-the-lexicographically-smallest-string/solutions/3687053/shi-yong-ji-qi-ren-da-yin-zi-dian-xu-zui-hwvo/)

<details><summary>Description</summary>

```text
You are given a string s and a robot that currently holds an empty string t.
Apply one of the following operations until s and t are both empty:
- Remove the first character of a string s and give it to the robot.
  The robot will append this character to the string t.
- Remove the last character of a string t and give it to the robot.
  The robot will write this character on paper.

Return the lexicographically smallest string that can be written on the paper.

Example 1:
Input: s = "zza"
Output: "azz"
Explanation: Let p denote the written string.
Initially p="", s="zza", t="".
Perform first operation three times p="", s="", t="zza".
Perform second operation three times p="azz", s="", t="".

Example 2:
Input: s = "bac"
Output: "abc"
Explanation: Let p denote the written string.
Perform first operation twice p="", s="c", t="ba".
Perform second operation twice p="ab", s="c", t="".
Perform first operation p="ab", s="", t="c".
Perform second operation p="abc", s="", t="".

Example 3:
Input: s = "bdda"
Output: "addb"
Explanation: Let p denote the written string.
Initially p="", s="bdda", t="".
Perform first operation four times p="", s="", t="bdda".
Perform second operation four times p="addb", s="", t="".

Constraints:
1 <= s.length <= 10^5
s consists of only English lowercase letters.
```

<details><summary>Hint</summary>

```text
1. If there are some character “a” ’ s in the string, they can be written on paper before anything else.
2. Every character in the string before the last “a” should be written in reversed order.
3. After the robot writes every “a” on paper, the same holds for other characters “b”, ”c”, …etc.
```

</details>

</details>

<details><summary>C</summary>

```c
char* robotWithString(char* s) {
    char* pRetVal = NULL;

    int sSize = strlen(s);

    pRetVal = (char*)malloc((sSize + 1) * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, ((sSize + 1) * sizeof(char)));
    int returnSize = 0;

    int frequency[26] = {0};  // s consists of only English lowercase letters.
    memset(frequency, 0, sizeof(frequency));
    for (int i = 0; i < sSize; i++) {
        frequency[s[i] - 'a']++;
    }

    int characterStackTop = 0;
    char* characterStack = (char*)malloc(sSize * sizeof(char));
    if (characterStack == NULL) {
        perror("malloc");
        return pRetVal;
    }
    char minCharacter = 'a';
    for (int i = 0; i < sSize; i++) {
        characterStack[characterStackTop++] = s[i];
        frequency[s[i] - 'a']--;

        while ((minCharacter != 'z') && (frequency[minCharacter - 'a'] == 0)) {
            minCharacter++;
        }

        while ((characterStackTop > 0) && (characterStack[characterStackTop - 1] <= minCharacter)) {
            pRetVal[returnSize++] = characterStack[--characterStackTop];
        }
    }
    pRetVal[returnSize] = '\0';

    //
    free(characterStack);
    characterStack = NULL;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    string robotWithString(string s) {
        string retVal;

        unordered_map<char, int> frequency;
        for (char c : s) {
            frequency[c]++;
        }
        stack<char> characterStack;
        char minCharacter = 'a';
        for (char c : s) {
            characterStack.emplace(c);
            frequency[c]--;

            while ((minCharacter != 'z') && (frequency[minCharacter] == 0)) {
                minCharacter++;
            }

            while ((characterStack.empty() == false) && (characterStack.top() <= minCharacter)) {
                retVal += characterStack.top();
                characterStack.pop();
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
    def robotWithString(self, s: str) -> str:
        retVal = ""

        frequency = Counter(s)
        characterStack = []
        minCharacter = "a"
        for c in s:
            characterStack.append(c)
            frequency[c] -= 1

            while (minCharacter != "z") and (frequency[minCharacter] == 0):
                minCharacter = chr(ord(minCharacter) + 1)

            while (characterStack) and (characterStack[-1] <= minCharacter):
                retVal += characterStack.pop()

        return retVal
```

</details>

## [2486. Append Characters to String to Make Subsequence](https://leetcode.com/problems/append-characters-to-string-to-make-subsequence/)  1362

- [Official](https://leetcode.com/problems/append-characters-to-string-to-make-subsequence/editorial/)

<details><summary>Description</summary>

```text
You are given two strings s and t consisting of only lowercase English letters.

Return the minimum number of characters that need to be appended to the end of s so that t becomes a subsequence of s.

A subsequence is a string that can be derived from another string by deleting some
or no characters without changing the order of the remaining characters.

Example 1:
Input: s = "coaching", t = "coding"
Output: 4
Explanation: Append the characters "ding" to the end of s so that s = "coachingding".
Now, t is a subsequence of s ("coachingding").
It can be shown that appending any 3 characters to the end of s will never make t a subsequence.

Example 2:
Input: s = "abcde", t = "a"
Output: 0
Explanation: t is already a subsequence of s ("abcde").

Example 3:
Input: s = "z", t = "abcde"
Output: 5
Explanation: Append the characters "abcde" to the end of s so that s = "zabcde".
Now, t is a subsequence of s ("zabcde").
It can be shown that appending any 4 characters to the end of s will never make t a subsequence.

Constraints:
1 <= s.length, t.length <= 10^5
s and t consist only of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Find the longest prefix of t that is a subsequence of s.
2. Use two variables to keep track of your location in s and t.
   If the characters match, increment both variables. Otherwise, only increment the variable for s.
3. The remaining characters in t must be appended to the end of s.
```

</details>

</details>

<details><summary>C</summary>

```c
int appendCharacters(char* s, char* t) {
    int retVal = 0;

    int sSize = strlen(s);
    int tSize = strlen(t);

    int idxS = 0;
    int idxT = 0;
    while ((idxS < sSize) && (idxT < tSize)) {
        if (s[idxS] == t[idxT]) {
            idxT += 1;
        }
        idxS += 1;
    }
    retVal = tSize - idxT;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int appendCharacters(string s, string t) {
        int retVal = 0;

        int sSize = s.size();
        int tSize = t.size();

        int idxS = 0;
        int idxT = 0;
        while ((idxS < sSize) && (idxT < tSize)) {
            if (s[idxS] == t[idxT]) {
                idxT += 1;
            }
            idxS += 1;
        }
        retVal = tSize - idxT;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def appendCharacters(self, s: str, t: str) -> int:
        retVal = 0

        sSize = len(s)
        tSize = len(t)

        idxS = 0
        idxT = 0
        while (idxS < sSize) and (idxT < tSize):
            if s[idxS] == t[idxT]:
                idxT += 1
            idxS += 1
        retVal = tSize - idxT

        return retVal
```

</details>

## [2551. Put Marbles in Bags](https://leetcode.com/problems/put-marbles-in-bags/)  2042

- [Official](https://leetcode.com/problems/put-marbles-in-bags/editorial/)

<details><summary>Description</summary>

```text
You have k bags. You are given a 0-indexed integer array weights where weights[i] is the weight of the ith marble.
You are also given the integer k.

Divide the marbles into the k bags according to the following rules:
- No bag is empty.
- If the ith marble and jth marble are in a bag,
  then all marbles with an index between the ith and jth indices should also be in that same bag.
- If a bag consists of all the marbles with an index from i to j inclusively,
  then the cost of the bag is weights[i] + weights[j].

The score after distributing the marbles is the sum of the costs of all the k bags.

Return the difference between the maximum and minimum scores among marble distributions.

Example 1:
Input: weights = [1,3,5,1], k = 2
Output: 4
Explanation:
The distribution [1],[3,5,1] results in the minimal score of (1+1) + (3+1) = 6.
The distribution [1,3],[5,1], results in the maximal score of (1+3) + (5+1) = 10.
Thus, we return their difference 10 - 6 = 4.

Example 2:
Input: weights = [1, 3], k = 2
Output: 0
Explanation: The only distribution possible is [1],[3].
Since both the maximal and minimal score are the same, we return 0.

Constraints:
1 <= k <= weights.length <= 10^5
1 <= weights[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Each bag will contain a sub-array.
2. Only the endpoints of the sub-array matter.
3. Try to use a priority queue.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareLonglong(const void* n1, const void* n2) {
    // ascending order
    return (*(long long*)n1 > *(long long*)n2);
}
// https://leetcode.com/problems/put-marbles-in-bags/solutions/3111736/java-c-python-3-approachs-best-o-n/
// https://leetcode.cn/problems/put-marbles-in-bags/solutions/2080577/by-wan-shi-liang-de-mang-fu-mwjh/
long long putMarbles(int* weights, int weightsSize, int k) {
    long long retVal = 0;

    /* Example: weights = [1,3,5,1], k = 2. Return the difference between the maximum and minimum scores.
     *  [1] [3,5,1]: (1+1) + (3+1) = 6  ->  6 - (1+1) = 4
     *  [1,3] [5,1]: (1+3) + (5+1) = 10 -> 10 - (1+1) = 8
     *  [1,3 5] [1]: (1+5) + (1+1) = 8  ->  8 - (1+1) = 6
     *
     *  [1,3,5,1] => [(1+3),(3+5),(5+1)] = [4,8,6]
     *
     *  1. 對weights進行兩兩求和得到map
     *  2. map中挑k-1個值，並累和得到sum
     *  3. 求出sum的最大值和最小值並做差
     */
    int mapSize = weightsSize - 1;
    if (weightsSize == 1) {
        return retVal;
    }
    long long map[mapSize];
    memset(map, 0, sizeof(map));
    for (int i = 1; i < weightsSize; i++) {
        map[i - 1] = weights[i] + weights[i - 1];
    }
    qsort(map, mapSize, sizeof(long long), compareLonglong);

    long long minimumScores = 0;
    long long maximumScores = 0;
    for (int i = 0; i < k - 1; i++) {
        minimumScores += map[i];
        maximumScores += map[mapSize - 1 - i];
    }
    retVal = maximumScores - minimumScores;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    // https://leetcode.com/problems/put-marbles-in-bags/solutions/3111736/java-c-python-3-approachs-best-o-n/
    // https://leetcode.cn/problems/put-marbles-in-bags/solutions/2080577/by-wan-shi-liang-de-mang-fu-mwjh/
    long long putMarbles(vector<int>& weights, int k) {
        long long retVal = 0;

        /* Example: weights = [1,3,5,1], k = 2. Return the difference between the maximum and minimum scores.
         *  [1] [3,5,1]: (1+1) + (3+1) = 6  ->  6 - (1+1) = 4
         *  [1,3] [5,1]: (1+3) + (5+1) = 10 -> 10 - (1+1) = 8
         *  [1,3 5] [1]: (1+5) + (1+1) = 8  ->  8 - (1+1) = 6
         *
         *  [1,3,5,1] => [(1+3),(3+5),(5+1)] = [4,8,6]
         *
         *  1. 對weights進行兩兩求和得到map
         *  2. map中挑k-1個值，並累和得到sum
         *  3. 求出sum的最大值和最小值並做差
         */
        int weightsSize = weights.size();
        vector<long long> map;
        for (int i = 1; i < weightsSize; i++) {
            map.emplace_back(weights[i] + weights[i - 1]);
        }
        sort(map.begin(), map.end());
        int mapSize = map.size();

        long long minimumScores = 0;
        long long maximumScores = 0;
        for (int i = 0; i < k - 1; i++) {
            minimumScores += map[i];
            maximumScores += map[mapSize - 1 - i];
        }
        retVal = maximumScores - minimumScores;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    # https://leetcode.com/problems/put-marbles-in-bags/solutions/3111736/java-c-python-3-approachs-best-o-n/
    # https://leetcode.cn/problems/put-marbles-in-bags/solutions/2080577/by-wan-shi-liang-de-mang-fu-mwjh/
    def putMarbles(self, weights: List[int], k: int) -> int:
        retVal = 0

        # /* Example: weights = [1,3,5,1], k = 2. Return the difference between the maximum and minimum scores.
        #  *  [1] [3,5,1]: (1+1) + (3+1) = 6  ->  6 - (1+1) = 4
        #  *  [1,3] [5,1]: (1+3) + (5+1) = 10 -> 10 - (1+1) = 8
        #  *  [1,3 5] [1]: (1+5) + (1+1) = 8  ->  8 - (1+1) = 6
        #  *
        #  *  [1,3,5,1] => [(1+3),(3+5),(5+1)] = [4,8,6]
        #  *
        #  *  1. 對weights進行兩兩求和得到map
        #  *  2. map中挑k-1個值，並累和得到sum
        #  *  3. 求出sum的最大值和最小值並做差
        #  */
        weightsSize = len(weights)
        map = []
        for i in range(1, weightsSize):
            map.append(weights[i] + weights[i - 1])
        map.sort()
        mapSize = len(map)

        minimumScores = 0
        maximumScores = 0
        for i in range(k - 1):
            minimumScores += map[i]
            maximumScores += map[mapSize - 1 - i]
        retVal = maximumScores - minimumScores

        return retVal
```

</details>

## [2561. Rearranging Fruits](https://leetcode.com/problems/rearranging-fruits/)  2221

- [Official](https://leetcode.com/problems/rearranging-fruits/editorial/)
- [Official](https://leetcode.cn/problems/rearranging-fruits/solutions/3729209/zhong-pai-shui-guo-by-leetcode-solution-9z2g/)

<details><summary>Description</summary>

```text
You have two fruit baskets containing n fruits each.
You are given two 0-indexed integer arrays basket1 and basket2 representing the cost of fruit in each basket.
You want to make both baskets equal. To do so, you can use the following operation as many times as you want:
- Chose two indices i and j, and swap the ith fruit of basket1 with the jth fruit of basket2.
- The cost of the swap is min(basket1[i],basket2[j]).

Two baskets are considered equal if sorting them according to the fruit cost makes them exactly the same baskets.

Return the minimum cost to make both the baskets equal or -1 if impossible.

Example 1:
Input: basket1 = [4,2,2,2], basket2 = [1,4,1,2]
Output: 1
Explanation:
Swap index 1 of basket1 with index 0 of basket2, which has cost 1. Now basket1 = [4,1,2,2] and basket2 = [2,4,1,2].
Rearranging both the arrays makes them equal.

Example 2:
Input: basket1 = [2,3,4,1], basket2 = [3,2,5,1]
Output: -1
Explanation:
It can be shown that it is impossible to make both the baskets equal.

Constraints:
basket1.length == basket2.length
1 <= basket1.length <= 10^5
1 <= basket1[i],basket2[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Create two frequency maps for both arrays, and find the minimum element among all elements of both arrays.
2. Check if the sum of frequencies of an element in both arrays is odd, if so return -1
3. Store the elements that need to be swapped in a vector, and sort it.
4. Can we reduce swapping cost with the help of minimum element?
5. Calculate the minimum cost of swapping.
```

</details>

</details>

<details><summary>C</summary>

```c
struct hashTable {
    int key;
    int value;
    UT_hash_handle hh;
};
bool updateFrequency(struct hashTable **pObj, int key, int value) {
    bool retVal = true;

    struct hashTable *pTemp = NULL;
    HASH_FIND_INT(*pObj, &key, pTemp);
    if (pTemp == NULL) {
        pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
        if (pTemp == NULL) {
            perror("malloc");
            retVal = false;
        } else {
            pTemp->key = key;
            pTemp->value = value;
            HASH_ADD_INT(*pObj, key, pTemp);
        }
    } else {
        pTemp->value += value;
    }

    return retVal;
}
void freeAll(struct hashTable *pFree) {
    struct hashTable *current;
    struct hashTable *tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int compareInteger(const void *n1, const void *n2) {
    // ascending order
    return (*(int *)n1 > *(int *)n2);
}
long long minCost(int *basket1, int basket1Size, int *basket2, int basket2Size) {
    long long retVal = 0;

    struct hashTable *frequency = NULL;
    int minValue = INT_MAX;
    for (int i = 0; i < basket1Size; i++) {
        updateFrequency(&frequency, basket1[i], 1);
        minValue = fmin(minValue, basket1[i]);
    }
    for (int i = 0; i < basket2Size; i++) {
        updateFrequency(&frequency, basket2[i], -1);
        minValue = fmin(minValue, basket2[i]);
    }

    int merge[basket1Size + basket2Size];
    memset(merge, 0, sizeof(merge));
    int mergeSize = 0;
    struct hashTable *pCurrent;
    struct hashTable *pTmp;
    HASH_ITER(hh, frequency, pCurrent, pTmp) {
        int c = pCurrent->value;
        if (c % 2 != 0) {
            freeAll(frequency);
            retVal = -1;
            return retVal;
        }

        for (int i = 0; i < abs(c) / 2; i++) {
            merge[mergeSize++] = pCurrent->key;
        }
    }

    if (mergeSize == 0) {
        freeAll(frequency);
        return retVal;
    }
    qsort(merge, mergeSize, sizeof(int), compareInteger);

    for (int i = 0; i < mergeSize / 2; i++) {
        retVal += fmin(merge[i], minValue * 2);
    }

    //
    freeAll(frequency);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long minCost(vector<int>& basket1, vector<int>& basket2) {
        long long retVal = 0;

        unordered_map<int, int> frequency;
        int minValue = numeric_limits<int>::max();
        for (int b1 : basket1) {
            frequency[b1]++;
            minValue = min(minValue, b1);
        }
        for (int b2 : basket2) {
            frequency[b2]--;
            minValue = min(minValue, b2);
        }

        vector<int> merge;
        for (auto [key, value] : frequency) {
            if (value % 2 != 0) {
                retVal = -1;
                return retVal;
            }
            for (int i = 0; i < abs(value) / 2; ++i) {
                merge.emplace_back(key);
            }
        }

        if (merge.empty()) {
            return retVal;
        }
        sort(merge.begin(), merge.end());

        int mergeSize = merge.size();
        for (int i = 0; i < mergeSize / 2; i++) {
            retVal += min(merge[i], minValue * 2);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minCost(self, basket1: List[int], basket2: List[int]) -> int:
        retVal = -1

        frequency = Counter()

        minValue = float("inf")
        for b1 in basket1:
            frequency[b1] += 1
            minValue = min(minValue, b1)
        for b2 in basket2:
            frequency[b2] -= 1
            minValue = min(minValue, b2)

        merge = []
        for key, value in frequency.items():
            if value % 2 != 0:
                return retVal
            merge.extend([key] * (abs(value) // 2))

        if not merge:
            retVal = 0
            return retVal
        merge.sort()

        retVal = sum(min(2 * minValue, x) for x in merge[: len(merge) // 2])

        return retVal
```

</details>

## [2566. Maximum Difference by Remapping a Digit](https://leetcode.com/problems/maximum-difference-by-remapping-a-digit/)  1396

- [Official](https://leetcode.com/problems/maximum-difference-by-remapping-a-digit/editorial/)
- [Official](https://leetcode.cn/problems/maximum-difference-by-remapping-a-digit/solutions/3690212/ti-huan-yi-ge-shu-zi-hou-de-zui-da-chai-3oyg4/)

<details><summary>Description</summary>

```text
You are given an integer num.
You know that Bob will sneakily remap one of the 10 possible digits (0 to 9) to another digit.

Return the difference between the maximum and minimum values Bob can make by remapping exactly one digit in num.

Notes:
- When Bob remaps a digit d1 to another digit d2, Bob replaces all occurrences of d1 in num with d2.
- Bob can remap a digit to itself, in which case num does not change.
- Bob can remap different digits for obtaining minimum and maximum values respectively.
- The resulting number after remapping can contain leading zeroes.

Example 1:
Input: num = 11891
Output: 99009
Explanation:
To achieve the maximum value, Bob can remap the digit 1 to the digit 9 to yield 99899.
To achieve the minimum value, Bob can remap the digit 1 to the digit 0, yielding 890.
The difference between these two numbers is 99009.

Example 2:
Input: num = 90
Output: 99
Explanation:
The maximum value that can be returned by the function is 99 (if 0 is replaced by 9)
and the minimum value that can be returned by the function is 0 (if 9 is replaced by 0).
Thus, we return 99.

Constraints:
- 1 <= num <= 10^8
```

<details><summary>Hint</summary>

```text
1. Try to remap the first non-nine digit to 9 to obtain the maximum number.
2. Try to remap the first non-zero digit to 0 to obtain the minimum number.
```

</details>

</details>

<details><summary>C</summary>

```c
int minMaxDifference(int num) {
    int retVal = 0;

#define MAX_NUM_SIZE (16)  // - 1 <= num <= 10^8

    char numMaxStr[MAX_NUM_SIZE];
    memset(numMaxStr, 0, sizeof(numMaxStr));
    snprintf(numMaxStr, sizeof(numMaxStr), "%d", num);
    int idx = 0;
    while ((numMaxStr[idx] != '\0') && (numMaxStr[idx] == '9')) {
        idx++;
    }
    if (numMaxStr[idx] != '\0') {
        char a = numMaxStr[idx];
        for (int i = 0; numMaxStr[i] != '\0'; i++) {
            if (numMaxStr[i] == a) {
                numMaxStr[i] = '9';
            }
        }
    }

    char numMinStr[MAX_NUM_SIZE];
    memset(numMinStr, 0, sizeof(numMinStr));
    snprintf(numMinStr, sizeof(numMinStr), "%d", num);
    char b = numMinStr[0];
    for (int i = 0; numMinStr[i] != '\0'; i++) {
        if (numMinStr[i] == b) {
            numMinStr[i] = '0';
        }
    }

    retVal = atoi(numMaxStr) - atoi(numMinStr);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minMaxDifference(int num) {
        int retVal = 0;

        string numMaxStr = to_string(num);
        size_t idx = numMaxStr.find_first_not_of('9');
        if (idx != string::npos) {
            char a = numMaxStr[idx];
            replace(numMaxStr.begin(), numMaxStr.end(), a, '9');
        }

        string numMinStr = to_string(num);
        char b = numMinStr[0];
        replace(numMinStr.begin(), numMinStr.end(), b, '0');

        retVal = stoi(numMaxStr) - stoi(numMinStr);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minMaxDifference(self, num: int) -> int:
        retVal = 0

        numMaxStr = str(num)
        numMaxStrSize = len(numMaxStr)
        idx = 0
        while (idx < numMaxStrSize) and (numMaxStr[idx] == "9"):
            idx += 1
        if idx < numMaxStrSize:
            numMaxStr = numMaxStr.replace(numMaxStr[idx], "9")

        numMinStr = str(num)
        numMinStr = numMinStr.replace(numMinStr[0], "0")

        retVal = int(numMaxStr) - int(numMinStr)

        return retVal
```

</details>

## [2598. Smallest Missing Non-negative Integer After Operations](https://leetcode.com/problems/smallest-missing-non-negative-integer-after-operations/)  1846

- [Official](https://leetcode.com/problems/smallest-missing-non-negative-integer-after-operations/editorial/)
- [Official](https://leetcode.cn/problems/smallest-missing-non-negative-integer-after-operations/solutions/3801016/zhi-xing-cao-zuo-hou-de-zui-da-mex-by-le-dvbj/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array nums and an integer value.

In one operation, you can add or subtract value from any element of nums.
- For example, if nums = [1,2,3] and value = 2, you can choose to subtract value from nums[0] to make nums = [-1,2,3].

The MEX (minimum excluded) of an array is the smallest missing non-negative integer in it.
- For example, the MEX of [-1,2,3] is 0 while the MEX of [1,0,3] is 2.

Return the maximum MEX of nums after applying the mentioned operation any number of times.

Example 1:
Input: nums = [1,-10,7,13,6,8], value = 5
Output: 4
Explanation: One can achieve this result by applying the following operations:
- Add value to nums[1] twice to make nums = [1,0,7,13,6,8]
- Subtract value from nums[2] once to make nums = [1,0,2,13,6,8]
- Subtract value from nums[3] twice to make nums = [1,0,2,3,6,8]
The MEX of nums is 4. It can be shown that 4 is the maximum MEX we can achieve.

Example 2:
Input: nums = [1,-10,7,13,6,8], value = 7
Output: 2
Explanation: One can achieve this result by applying the following operation:
- subtract value from nums[2] once to make nums = [1,-10,0,13,6,8]
The MEX of nums is 2. It can be shown that 2 is the maximum MEX we can achieve.

Constraints:
1 <= nums.length, value <= 10^5
-10^9 <= nums[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Think about using modular arithmetic.
2. if x = nums[i] (mod value), then we can make nums[i] equal to x after some number of operations
3. How does finding the frequency of (nums[i] mod value) help?
```

</details>

</details>

<details><summary>C</summary>

```c
int findSmallestInteger(int* nums, int numsSize, int value) {
    int retVal = 0;

    int mp[value];
    memset(mp, 0, sizeof(mp));
    for (int i = 0; i < numsSize; i++) {
        int x = nums[i];
        int v = (x % value + value) % value;
        mp[v]++;
    }

    while (mp[retVal % value] > 0) {
        mp[retVal % value]--;
        retVal++;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int findSmallestInteger(vector<int>& nums, int value) {
        int retVal = 0;

        vector<int> mp(value);
        for (auto& x : nums) {
            int v = (x % value + value) % value;
            mp[v]++;
        }

        while (mp[retVal % value] > 0) {
            mp[retVal % value]--;
            retVal++;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def findSmallestInteger(self, nums: List[int], value: int) -> int:
        retVal = 0

        mp = Counter(x % value for x in nums)
        while mp[retVal % value] > 0:
            mp[retVal % value] -= 1
            retVal += 1

        return retVal
```

</details>

## [2654. Minimum Number of Operations to Make All Array Elements Equal to 1](https://leetcode.com/problems/minimum-number-of-operations-to-make-all-array-elements-equal-to-1/)  1929

- [Official](https://leetcode.com/problems/minimum-number-of-operations-to-make-all-array-elements-equal-to-1/editorial/)
- [Official](https://leetcode.cn/problems/minimum-number-of-operations-to-make-all-array-elements-equal-to-1/solutions/3823790/shi-shu-zu-suo-you-yuan-su-bian-cheng-1-v2rrc/)

<details><summary>Description</summary>

```text
You are given a 0-indexed array nums consisiting of positive integers.
You can do the following operation on the array any number of times:
- Select an index i such that 0 <= i < n - 1 and replace either of nums[i] or nums[i+1] with their gcd value.

Return the minimum number of operations to make all elements of nums equal to 1. If it is impossible, return -1.

The gcd of two integers is the greatest common divisor of the two integers.

Example 1:
Input: nums = [2,6,3,4]
Output: 4
Explanation: We can do the following operations:
- Choose index i = 2 and replace nums[2] with gcd(3,4) = 1. Now we have nums = [2,6,1,4].
- Choose index i = 1 and replace nums[1] with gcd(6,1) = 1. Now we have nums = [2,1,1,4].
- Choose index i = 0 and replace nums[0] with gcd(2,1) = 1. Now we have nums = [1,1,1,4].
- Choose index i = 2 and replace nums[3] with gcd(1,4) = 1. Now we have nums = [1,1,1,1].

Example 2:
Input: nums = [2,10,6,14]
Output: -1
Explanation: It can be shown that it is impossible to make all the elements equal to 1.

Constraints:
2 <= nums.length <= 50
1 <= nums[i] <= 10^6
```

<details><summary>Hint</summary>

```text
1. Note that if you have at least one occurrence of 1 in the array,
   then you can make all the other elements equal to 1 with one operation each.
2. Try finding the shortest subarray with a gcd equal to 1.
```

</details>

</details>

<details><summary>C</summary>

```c
int gcd(int a, int b) {
    int retVal = 0;

    int temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    retVal = a;

    return retVal;
}
int minOperations(int* nums, int numsSize) {
    int retVal = -1;

    int numberOfOne = 0;
    int greatestCommonDivisor = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == 1) {
            numberOfOne++;
        }
        greatestCommonDivisor = gcd(greatestCommonDivisor, nums[i]);
    }
    if (numberOfOne > 0) {
        retVal = numsSize - numberOfOne;
        return retVal;
    } else if (greatestCommonDivisor > 1) {
        return retVal;
    }

    int minNumsSize = numsSize;
    for (int i = 0; i < numsSize; i++) {
        greatestCommonDivisor = 0;
        for (int j = i; j < numsSize; j++) {
            greatestCommonDivisor = gcd(greatestCommonDivisor, nums[j]);
            if (greatestCommonDivisor == 1) {
                if (j - i + 1 < minNumsSize) {
                    minNumsSize = j - i + 1;
                }
                break;
            }
        }
    }
    retVal = minNumsSize + numsSize - 2;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minOperations(vector<int>& nums) {
        int retVal = -1;

        int numsSize = nums.size();

        int numberOfOne = 0;
        int greatestCommonDivisor = 0;
        for (int num : nums) {
            if (num == 1) {
                numberOfOne++;
            }
            greatestCommonDivisor = gcd(greatestCommonDivisor, num);
        }
        if (numberOfOne > 0) {
            retVal = numsSize - numberOfOne;
            return retVal;
        } else if (greatestCommonDivisor > 1) {
            return retVal;
        }

        int minNumsSize = numsSize;
        for (int i = 0; i < numsSize; i++) {
            greatestCommonDivisor = 0;
            for (int j = i; j < numsSize; j++) {
                greatestCommonDivisor = gcd(greatestCommonDivisor, nums[j]);
                if (greatestCommonDivisor == 1) {
                    minNumsSize = min(minNumsSize, j - i + 1);
                    break;
                }
            }
        }
        retVal = minNumsSize + numsSize - 2;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minOperations(self, nums: List[int]) -> int:
        retVal = -1

        numsSize = len(nums)

        numberOfOne = 0
        greatestCommonDivisor = 0
        for num in nums:
            if num == 1:
                numberOfOne += 1
            greatestCommonDivisor = gcd(greatestCommonDivisor, num)
        if numberOfOne > 0:
            retVal = numsSize - numberOfOne
            return retVal
        elif greatestCommonDivisor > 1:
            return retVal

        minNumsSize = numsSize
        for i in range(numsSize):
            greatestCommonDivisor = 0
            for j in range(i, numsSize):
                greatestCommonDivisor = gcd(greatestCommonDivisor, nums[j])
                if greatestCommonDivisor == 1:
                    minNumsSize = min(minNumsSize, j - i + 1)
                    break
        retVal = minNumsSize + numsSize - 2

        return retVal
```

</details>

## [2870. Minimum Number of Operations to Make Array Empty](https://leetcode.com/problems/minimum-number-of-operations-to-make-array-empty/)  1392

- [Official](https://leetcode.com/problems/minimum-number-of-operations-to-make-array-empty/editorial/)

<details><summary>Description</summary>

```text
You are given a 0-indexed array nums consisting of positive integers.

There are two types of operations that you can apply on the array any number of times:
- Choose two elements with equal values and delete them from the array.
- Choose three elements with equal values and delete them from the array.

Return the minimum number of operations required to make the array empty, or -1 if it is not possible.

Example 1:
Input: nums = [2,3,3,2,2,4,2,3,4]
Output: 4
Explanation: We can apply the following operations to make the array empty:
- Apply the first operation on the elements at indices 0 and 3. The resulting array is nums = [3,3,2,4,2,3,4].
- Apply the first operation on the elements at indices 2 and 4. The resulting array is nums = [3,3,4,3,4].
- Apply the second operation on the elements at indices 0, 1, and 3. The resulting array is nums = [4,4].
- Apply the first operation on the elements at indices 0 and 1. The resulting array is nums = [].
It can be shown that we cannot make the array empty in less than 4 operations.

Example 2:
Input: nums = [2,1,2,2,3,3]
Output: -1
Explanation: It is impossible to empty the array.

Constraints:
2 <= nums.length <= 10^5
1 <= nums[i] <= 10^6
```

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int minOperations(int* nums, int numsSize) {
    int retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int count = 1;
    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[i - 1] == nums[i]) {
            count++;
            continue;
        }

        if (count == 1) {
            retVal = -1;
            return retVal;
        }
        retVal += (count / 3);
        if (count % 3 != 0) {
            retVal += 1;
        }

        count = 1;
    }
    if (count == 1) {
        retVal = -1;
        return retVal;
    }
    retVal += (count / 3);
    if (count % 3 != 0) {
        retVal += 1;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minOperations(vector<int>& nums) {
        int retVal = 0;

        unordered_map<int, int> hashTable;
        for (int num : nums) {
            auto iterator = hashTable.find(num);
            if (iterator != hashTable.end()) {
                hashTable[num]++;
            } else {
                hashTable[num] = 1;
            }
        }

        for (auto iterator : hashTable) {
            int times = iterator.second;
            if (times == 1) {
                retVal = -1;
                break;
            }

            retVal += (times / 3);
            if (times % 3 != 0) {
                retVal += 1;
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
    def minOperations(self, nums: List[int]) -> int:
        retVal = 0

        count = Counter(nums)
        for times in count.values():
            if times == 1:
                retVal = -1
                break

            operations = times // 3
            if times % 3 == 0:
                retVal += operations
            else:
                retVal += (operations + 1)

        return retVal
```

</details>

## [2918. Minimum Equal Sum of Two Arrays After Replacing Zeros](https://leetcode.com/problems/minimum-equal-sum-of-two-arrays-after-replacing-zeros/)  1526

- [Official](https://leetcode.com/problems/minimum-equal-sum-of-two-arrays-after-replacing-zeros/editorial/)
- [Official](https://leetcode.cn/problems/minimum-equal-sum-of-two-arrays-after-replacing-zeros/solutions/3665133/shu-zu-de-zui-xiao-xiang-deng-he-by-leet-5cam/)

<details><summary>Description</summary>

```text
You are given two arrays nums1 and nums2 consisting of positive integers.

You have to replace all the 0's in both arrays with strictly positive integers
such that the sum of elements of both arrays becomes equal.

Return the minimum equal sum you can obtain, or -1 if it is impossible.

Example 1:
Input: nums1 = [3,2,0,1,0], nums2 = [6,5,0]
Output: 12
Explanation: We can replace 0's in the following way:
- Replace the two 0's in nums1 with the values 2 and 4. The resulting array is nums1 = [3,2,2,1,4].
- Replace the 0 in nums2 with the value 1. The resulting array is nums2 = [6,5,1].
Both arrays have an equal sum of 12. It can be shown that it is the minimum sum we can obtain.

Example 2:
Input: nums1 = [2,0,2,0], nums2 = [1,4]
Output: -1
Explanation: It is impossible to make the sum of both arrays equal.

Constraints:
1 <= nums1.length, nums2.length <= 10^5
0 <= nums1[i], nums2[i] <= 10^6
```

<details><summary>Hint</summary>

```text
1. Consider we replace all the 0’s with 1’s on both arrays,
   the answer will be -1 if there was no 0 in the array with the smaller sum of elements.
2. Otherwise, how can you update the value of exactly one of these 1’s to make the sum of the two arrays equal?
```

</details>

</details>

<details><summary>C</summary>

```c
long long minSum(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    long long retVal = -1;

    long long sum1 = 0;
    int zero1 = 0;
    for (int i = 0; i < nums1Size; ++i) {
        sum1 += nums1[i];
        if (nums1[i] == 0) {
            sum1 += 1;
            zero1 += 1;
        }
    }

    long long sum2 = 0;
    int zero2 = 0;
    for (int i = 0; i < nums2Size; ++i) {
        sum2 += nums2[i];
        if (nums2[i] == 0) {
            sum2++;
            zero2++;
        }
    }

    if (((zero1 == 0) && (sum2 > sum1)) || ((zero2 == 0) && (sum1 > sum2))) {
        return retVal;
    }
    retVal = fmax(sum1, sum2);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long minSum(vector<int>& nums1, vector<int>& nums2) {
        long long retVal = -1;

        long long sum1 = 0;
        int zero1 = 0;
        for (const int& num : nums1) {
            sum1 += num;
            if (num == 0) {
                sum1 += 1;
                zero1 += 1;
            }
        }

        long long sum2 = 0;
        int zero2 = 0;
        for (const int& num : nums2) {
            sum2 += num;
            if (num == 0) {
                sum2++;
                zero2++;
            }
        }

        if (((zero1 == 0) && (sum2 > sum1)) || ((zero2 == 0) && (sum1 > sum2))) {
            return retVal;
        }
        retVal = max(sum1, sum2);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minSum(self, nums1: List[int], nums2: List[int]) -> int:
        retVal = -1

        sum1 = 0
        zero1 = 0
        for num in nums1:
            sum1 += num
            if num == 0:
                sum1 += 1
                zero1 += 1

        sum2 = 0
        zero2 = 0
        for num in nums2:
            sum2 += num
            if num == 0:
                sum2 += 1
                zero2 += 1

        if (zero1 == 0 and sum2 > sum1) or (zero2 == 0 and sum1 > sum2):
            return retVal
        retVal = max(sum1, sum2)

        return retVal
```

</details>

## [2938. Separate Black and White Balls](https://leetcode.com/problems/separate-black-and-white-balls/)  1422

- [Official](https://leetcode.com/problems/separate-black-and-white-balls/editorial/)
- [Official](https://leetcode.cn/problems/separate-black-and-white-balls/solutions/2799043/qu-fen-hei-qiu-yu-bai-qiu-by-leetcode-so-f7jm/)

<details><summary>Description</summary>

```text
There are n balls on a table, each ball has a color black or white.

You are given a 0-indexed binary string s of length n, where 1 and 0 represent black and white balls, respectively.

In each step, you can choose two adjacent balls and swap them.

Return the minimum number of steps to group all the black balls to the right and all the white balls to the left.

Example 1:
Input: s = "101"
Output: 1
Explanation: We can group all the black balls to the right in the following way:
- Swap s[0] and s[1], s = "011".
Initially, 1s are not grouped together, requiring at least 1 step to group them to the right.

Example 2:
Input: s = "100"
Output: 2
Explanation: We can group all the black balls to the right in the following way:
- Swap s[0] and s[1], s = "010".
- Swap s[1] and s[2], s = "001".
It can be proven that the minimum number of steps needed is 2.

Example 3:
Input: s = "0111"
Output: 0
Explanation: All the black balls are already grouped to the right.

Constraints:
1 <= n == s.length <= 10^5
s[i] is either '0' or '1'.
```

<details><summary>Hint</summary>

```text
1. Every 1 in the string s should be swapped with every 0 on its right side.
2. Iterate right to left and count the number of 0 that have already occurred,
   whenever you iterate on 1 add that counter to the answer.
```

</details>

</details>

<details><summary>C</summary>

```c
long long minimumSteps(char* s) {
    long long retVal = 0;

    int sum = 0;
    int sSize = strlen(s);
    int i;
    for (i = 0; i < sSize; ++i) {
        if (s[i] == '1') {
            sum++;
        } else {
            retVal += sum;
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
    long long minimumSteps(string s) {
        long long retVal = 0;

        int sum = 0;
        for (char c : s) {
            if (c == '1') {
                sum++;
            } else {
                retVal += sum;
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
    def minimumSteps(self, s: str) -> int:
        retVal = 0

        sum = 0
        for c in s:
            if c == '1':
                sum += 1
            else:
                retVal += sum

        return retVal
```

</details>

## [2966. Divide Array Into Arrays With Max Difference](https://leetcode.com/problems/divide-array-into-arrays-with-max-difference/)  1395

- [Official](https://leetcode.com/problems/divide-array-into-arrays-with-max-difference/editorial/)

<details><summary>Description</summary>

```text
You are given an integer array nums of size n and a positive integer k.

Divide the array into one or more arrays of size 3 satisfying the following conditions:
- Each element of nums should be in exactly one array.
- The difference between any two elements in one array is less than or equal to k.

Return a 2D array containing all the arrays.
If it is impossible to satisfy the conditions, return an empty array.
And if there are multiple answers, return any of them.

Example 1:
Input: nums = [1,3,4,8,7,9,3,5,1], k = 2
Output: [[1,1,3],[3,4,5],[7,8,9]]
Explanation: We can divide the array into the following arrays: [1,1,3], [3,4,5] and [7,8,9].
The difference between any two elements in each array is less than or equal to 2.
Note that the order of elements is not important.

Example 2:
Input: nums = [1,3,3,2,7,3], k = 3
Output: []
Explanation: It is not possible to divide the array satisfying all the conditions.

Constraints:
n == nums.length
1 <= n <= 10^5
n is a multiple of 3.
1 <= nums[i] <= 10^5
1 <= k <= 10^5
```

<details><summary>Hint</summary>

```text
1. Try to use a greedy approach.
2. Sort the array and try to group each 3 consecutive elements.
```

</details>

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
int** divideArray(int* nums, int numsSize, int k, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    if (numsSize % 3 != 0) {
        return pRetVal;
    }
    (*returnSize) = numsSize / 3;

    pRetVal = (int**)malloc((*returnSize) * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        goto exit1;
    }
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        goto exit2;
    }
    memset((*returnColumnSizes), 0, ((*returnSize) * sizeof(int)));

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int i, j;
    for (i = 0; i < (*returnSize); ++i) {
        if (nums[3 * i + 2] - nums[3 * i] > k) {
            goto exit3;
        }

        pRetVal[i] = (int*)malloc(3 * sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            goto exit3;
        }
        memset(pRetVal[i], 0, (3 * sizeof(int)));
        (*returnColumnSizes)[i] = 3;
        pRetVal[i][0] = nums[3 * i];
        pRetVal[i][1] = nums[3 * i + 1];
        pRetVal[i][2] = nums[3 * i + 2];
    }

    return pRetVal;

exit3:
    for (j = 0; j < i; ++j) {
        free(pRetVal[j]);
        pRetVal[j] = NULL;
    }
    free((*returnColumnSizes));
    (*returnColumnSizes) = NULL;

exit2:
    free(pRetVal);
    pRetVal = NULL;

exit1:
    (*returnSize) = 0;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<vector<int>> divideArray(vector<int>& nums, int k) {
        vector<vector<int>> retVal;

        int numsSize = nums.size();
        if (numsSize % 3 != 0) {
            return retVal;
        }

        sort(nums.begin(), nums.end());
        for (int i = 0; i < numsSize; i += 3) {
            if (nums[i + 2] - nums[i] > k) {
                retVal = {};
                break;
            }

            retVal.push_back({nums[i], nums[i + 1], nums[i + 2]});
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def divideArray(self, nums: List[int], k: int) -> List[List[int]]:
        retVal = []

        numsSize = len(nums)
        if (numsSize % 3) != 0:
            return retVal

        nums.sort()
        for i in range(0, numsSize, 3):
            if (nums[i+2] - nums[i]) > k:
                retVal = []
                break
            retVal.append([nums[i], nums[i+1], nums[i+2]])

        return retVal
```

</details>

## [2971. Find Polygon With the Largest Perimeter](https://leetcode.com/problems/find-polygon-with-the-largest-perimeter/)  1521

- [Official](https://leetcode.com/problems/find-polygon-with-the-largest-perimeter/editorial/)

<details><summary>Description</summary>

```text
You are given an array of positive integers nums of length n.

A polygon is a closed plane figure that has at least 3 sides.
The longest side of a polygon is smaller than the sum of its other sides.

Conversely, if you have k (k >= 3) positive real numbers a1, a2, a3, ..., ak
where a1 <= a2 <= a3 <= ... <= ak and a1 + a2 + a3 + ... + ak-1 > ak,
then there always exists a polygon with k sides whose lengths are a1, a2, a3, ..., ak.

The perimeter of a polygon is the sum of lengths of its sides.

Return the largest possible perimeter of a polygon whose sides can be formed from nums,
or -1 if it is not possible to create a polygon.

Example 1:
Input: nums = [5,5,5]
Output: 15
Explanation: The only possible polygon that can be made from nums has 3 sides: 5, 5, and 5.
The perimeter is 5 + 5 + 5 = 15.

Example 2:
Input: nums = [1,12,1,2,5,50,3]
Output: 12
Explanation: The polygon with the largest perimeter which can be made from nums has 5 sides: 1, 1, 2, 3, and 5.
The perimeter is 1 + 1 + 2 + 3 + 5 = 12.
We cannot have a polygon with either 12 or 50 as the longest side
because it is not possible to include 2 or more smaller sides that have a greater sum than either of them.
It can be shown that the largest possible perimeter is 12.

Example 3:
Input: nums = [5,5,50]
Output: -1
Explanation: There is no possible way to form a polygon from nums, as a polygon has at least 3 sides and 50 > 5 + 5.

Constraints:
3 <= n <= 10^5
1 <= nums[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Sort the array.
2. Use greedy algorithm. If we select an edge as the longest side,
   it is always better to pick up all the edges with length no longer than this longest edge.
3. Note that the number of edges should not be less than 3.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
long long largestPerimeter(int* nums, int numsSize) {
    long long retVal = -1;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    long long sum = nums[0] + nums[1];
    int i;
    for (i = 2; i < numsSize; ++i) {
        if (sum > nums[i]) {
            retVal = sum + nums[i];
        }
        sum += nums[i];
    }
    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long largestPerimeter(vector<int>& nums) {
        long long retVal = -1;

        int numsSize = nums.size();

        sort(nums.begin(), nums.end());
        long long sum = nums[0] + nums[1];
        for (int i = 2; i < numsSize; ++i) {
            if (sum > nums[i]) {
                retVal = sum + nums[i];
            }
            sum += nums[i];
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def largestPerimeter(self, nums: List[int]) -> int:
        retVal = -1

        numsSize = len(nums)

        nums.sort()
        sum = nums[0] + nums[1]
        for i in range(2, numsSize):
            if sum > nums[i]:
                retVal = sum + nums[i]
            sum += nums[i]

        return retVal
```

</details>
