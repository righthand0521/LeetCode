# Greedy

## [1007. Minimum Domino Rotations For Equal Row](https://leetcode.com/problems/minimum-domino-rotations-for-equal-row/)  1541

- [Official](https://leetcode.cn/problems/minimum-domino-rotations-for-equal-row/solutions/3042120/xing-xiang-deng-de-zui-shao-duo-mi-nuo-x-l31w/)

<details><summary>Description</summary>

```text
In a row of dominoes, tops[i] and bottoms[i] represent the top and bottom halves of the ith domino.
(A domino is a tile with two numbers from 1 to 6 - one on each half of the tile.)

We may rotate the ith domino, so that tops[i] and bottoms[i] swap values.

Return the minimum number of rotations so that all the values in tops are the same,
or all the values in bottoms are the same.

If it cannot be done, return -1.

Example 1:
Input: tops = [2,1,2,4,2,2], bottoms = [5,2,6,2,3,2]
Output: 2
Explanation:
The first figure represents the dominoes as given by tops and bottoms: before we do any rotations.
If we rotate the second and fourth dominoes, we can make every value in the top row equal to 2,
as indicated by the second figure.

Example 2:
Input: tops = [3,5,1,2,3], bottoms = [3,6,3,3,4]
Output: -1
Explanation:
In this case, it is not possible to rotate the dominoes to make one row of values equal.

Constraints:
2 <= tops.length <= 2 * 10^4
bottoms.length == tops.length
1 <= tops[i], bottoms[i] <= 6
```

</details>

<details><summary>C</summary>

```c
int check(int* tops, int topsSize, int* bottoms, int bottomsSize, int x) {
    int retVal = -1;

    int rotationsTops = 0;
    int rotationsBottoms = 0;
    for (int i = 0; i < topsSize; i++) {
        if ((tops[i] != x) && (bottoms[i] != x)) {  // rotations couldn't be done
            return retVal;
        }

        if (tops[i] != x) {  // tops[i] != x and bottoms[i] == x
            rotationsTops++;
        } else if (bottoms[i] != x) {  // tops[i] == x and bottoms[i] != x
            rotationsBottoms++;
        }
    }
    // min number of rotations to have all elements equal to x in tops or bottoms
    retVal = fmin(rotationsTops, rotationsBottoms);

    return retVal;
}
int minDominoRotations(int* tops, int topsSize, int* bottoms, int bottomsSize) {
    int retVal = 0;

    int rotations = check(tops, topsSize, bottoms, bottomsSize, tops[0]);
    // If one could make all elements in tops or bottoms equal to tops[0]
    // Else one could make all elements in tops or bottoms equal to bottoms[0]
    if ((rotations != -1) || (tops[0] == bottoms[0])) {
        return rotations;
    } else {
        retVal = check(tops, topsSize, bottoms, bottomsSize, bottoms[0]);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    int check(vector<int>& tops, vector<int>& bottoms, int x) {
        int retVal = -1;

        int rotationsTops = 0;
        int rotationsBottoms = 0;
        int topsSize = tops.size();
        for (int i = 0; i < topsSize; i++) {
            if (tops[i] != x && bottoms[i] != x) {  // rotations couldn't be done
                return retVal;
            }

            if (tops[i] != x) {  // tops[i] != x and bottoms[i] == x
                rotationsTops++;
            } else if (bottoms[i] != x) {  // tops[i] == x and bottoms[i] != x
                rotationsBottoms++;
            }
        }
        // min number of rotations to have all elements equal to x in tops or bottoms
        retVal = min(rotationsTops, rotationsBottoms);

        return retVal;
    }

   public:
    int minDominoRotations(vector<int>& tops, vector<int>& bottoms) {
        int retVal = 0;

        int rotations = check(tops, bottoms, tops[0]);
        // If one could make all elements in tops or bottoms equal to tops[0]
        // Else one could make all elements in tops or bottoms equal to bottoms[0]
        if ((rotations != -1) || (tops[0] == bottoms[0])) {
            return rotations;
        } else {
            retVal = check(tops, bottoms, bottoms[0]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    # Return min number of swaps
    # if one could make all elements in tops or bottoms equal to x
    # else return -1.
    def check(self, tops: List[int], bottoms: List[int], x: int) -> int:
        retVal = -1

        # how many rotations should be done
        # to have all elements in tops equal to x and to have all elements in bottoms equal to x
        rotationsTops = 0
        rotationsBottoms = 0
        topsSize = len(tops)
        for i in range(topsSize):
            if (tops[i] != x) and (bottoms[i] != x):  # rotations coudn't be done
                return retVal

            if tops[i] != x:  # tops[i] != x and bottoms[i] == x
                rotationsTops += 1
            elif bottoms[i] != x:  # tops[i] == x and bottoms[i] != x
                rotationsBottoms += 1

        # min number of rotations to have all elements equal to x in tops or bottoms
        retVal = min(rotationsTops, rotationsBottoms)

        return retVal

    def minDominoRotations(self, tops: List[int], bottoms: List[int]) -> int:
        retVal = 0

        rotations = self.check(tops, bottoms, tops[0])
        # If one could make all elements in tops or bottoms equal to tops[0]
        if (rotations != -1) or (tops[0] == bottoms[0]):
            retVal = rotations
        else:   # If one could make all elements in tops or bottoms equal to bottoms[0]
            retVal = self.check(tops, bottoms, bottoms[0])

        return retVal
```

</details>

## [1296. Divide Array in Sets of K Consecutive Numbers](https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers/)  1490

- [Official](https://leetcode.cn/problems/divide-array-in-sets-of-k-consecutive-numbers/solutions/101809/hua-fen-shu-zu-wei-lian-xu-shu-zi-de-ji-he-by-le-2/)

<details><summary>Description</summary>

```text
Given an array of integers nums and a positive integer k,
check whether it is possible to divide this array into sets of k consecutive numbers.

Return true if it is possible. Otherwise, return false.

Example 1:
Input: nums = [1,2,3,3,4,4,5,6], k = 4
Output: true
Explanation: Array can be divided into [1,2,3,4] and [3,4,5,6].

Example 2:
Input: nums = [3,2,1,2,3,4,3,4,5,9,10,11], k = 3
Output: true
Explanation: Array can be divided into [1,2,3] , [2,3,4] , [3,4,5] and [9,10,11].

Example 3:
Input: nums = [1,2,3,4], k = 3
Output: false
Explanation: Each array should be divided in subarrays of size 3.

Constraints:
1 <= k <= nums.length <= 10^5
1 <= nums[i] <= 10^9

Note: This question is the same as 846: https://leetcode.com/problems/hand-of-straights/
```

<details><summary>Hint</summary>

```text
1. If the smallest number in the possible-to-split array is V,
   then numbers V+1, V+2, ... V+k-1 must contain there as well.
2. You can iteratively find k sets and remove them from array until it becomes empty.
3. Failure to do so would mean that array is unsplittable.
```

</details>

</details>

<details><summary>C</summary>

```c
typedef struct Node {
    int value;
    int frequency;
} Node;
int compareInteger(const void *n1, const void *n2) {
    // ascending order
    return (*(int *)n1 > *(int *)n2);
}
bool isPossibleDivide(int *nums, int numsSize, int k) {
    bool retVal = false;

    if (numsSize % k != 0) {
        return retVal;
    }

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int i, j;

    Node *pCount = (Node *)malloc(numsSize * sizeof(Node));
    if (pCount == NULL) {
        perror("malloc");
        return retVal;
    }
    memset(pCount, 0, sizeof(Node) * numsSize);
    pCount[0].value = nums[0];
    pCount[0].frequency = 1;
    int cardSize = 0;
    for (i = 1; i < numsSize; ++i) {
        if (nums[i] != pCount[cardSize].value) {
            cardSize++;
        }
        pCount[cardSize].value = nums[i];
        pCount[cardSize].frequency++;
    }

    int num;
    int pos = 0;
    for (i = 0; i < numsSize; ++i) {
        while ((pos < cardSize) && (pCount[pos].frequency == 0)) {
            pos++;
        }

        if ((pCount[pos].value == nums[i]) && (pCount[pos].frequency > 0)) {
            for (j = 0; j < k; ++j) {
                num = nums[i] + j;
                if ((pCount[pos + j].frequency > 0) && (pCount[pos + j].value == num)) {
                    pCount[pos + j].frequency--;
                } else {
                    goto exit;
                }
            }
        }
    }
    retVal = true;

exit:
    //
    free(pCount);
    pCount = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        bool retVal = false;

        int numsSize = nums.size();
        if (numsSize % k != 0) {
            return retVal;
        }

        sort(nums.begin(), nums.end());

        unordered_map<int, int> count;
        for (auto& num : nums) {
            count[num]++;
        }

        for (auto& x : nums) {
            if (count.count(x) == 0) {
                continue;
            }

            for (int i = 0; i < k; i++) {
                int num = x + i;
                if (count.count(num) == 0) {
                    return retVal;
                }

                count[num]--;
                if (count[num] == 0) {
                    count.erase(num);
                }
            }
        }
        retVal = true;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def isPossibleDivide(self, nums: List[int], k: int) -> bool:
        retVal = False

        handSize = len(nums)
        if handSize % k > 0:
            return retVal

        nums.sort()

        count = Counter(nums)
        for x in nums:
            if count[x] == 0:
                continue

            for num in range(x, x + k):
                if count[num] == 0:
                    return retVal
                count[num] -= 1
        retVal = True

        return retVal
```

</details>

## [1353. Maximum Number of Events That Can Be Attended](https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/)  2015

- [Official](https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/editorial/)
- [Official](https://leetcode.cn/problems/maximum-number-of-events-that-can-be-attended/solutions/101227/zui-duo-ke-yi-can-jia-de-hui-yi-shu-mu-by-leetcode/)

<details><summary>Description</summary>

```text
You are given an array of events where events[i] = [startDayi, endDayi].
Every event i starts at startDayi and ends at endDayi.

You can attend an event i at any day d where startTimei <= d <= endTimei.
You can only attend one event at any time d.

Return the maximum number of events you can attend.

Example 1:
Input: events = [[1,2],[2,3],[3,4]]
Output: 3
Explanation: You can attend all the three events.
One way to attend them all is as shown.
Attend the first event on day 1.
Attend the second event on day 2.
Attend the third event on day 3.

Example 2:
Input: events= [[1,2],[2,3],[3,4],[1,2]]
Output: 4

Constraints:
1 <= events.length <= 10^5
events[i].length == 2
1 <= startDayi <= endDayi <= 10^5
```

<details><summary>Hint</summary>

```text
1. Sort the events by the start time and in case of tie by the end time in ascending order.
2. Loop over the sorted events. Attend as much as you can and keep the last day occupied.
   When you try to attend new event keep in mind the first day you can attend a new event in.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareIntArray(const void* a1, const void* a2) {
    int* p1 = *(int**)a1;
    int* p2 = *(int**)a2;

    // ascending order
    return (p1[1] > p2[1]);
}
int maxEvents(int** events, int eventsSize, int* eventsColSize) {
    int retVal = 0;

    qsort(events, eventsSize, sizeof(int*), compareIntArray);

#define MAX_EVENTS_SIZE (100000 + 4)  // 1 <= events.length <= 10^5
    int* hash = (int*)calloc(MAX_EVENTS_SIZE, sizeof(int));
    if (hash == NULL) {
        perror("calloc");
        return retVal;
    }

    int temp = 0;
    int prev = 0;
    int i, j;
    for (i = 0; i < eventsSize; ++i) {
        j = (events[i][0] >= prev) ? (fmax(events[i][0], temp)) : (events[i][0]);
        while (j <= events[i][1]) {
            if (hash[j] == 0) {
                hash[j] = 1;
                temp = j + 1;
                prev = events[i][0];
                ++retVal;
                break;
            }

            ++j;
        }
    }

    free(hash);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxEvents(vector<vector<int>>& events) {
        int retVal = 0;

        sort(events.begin(), events.end());

        int eventsIndex = 0;
        int eventsSize = events.size();
        int startDay = 0;
        priority_queue<int, vector<int>, greater<int>> minHeap;
        while ((minHeap.size() > 0) || (eventsIndex < eventsSize)) {
            if (minHeap.size() == 0) {
                startDay = events[eventsIndex][0];
            }

            while ((eventsIndex < eventsSize) && (events[eventsIndex][0] <= startDay)) {
                minHeap.push(events[eventsIndex++][1]);
            }

            minHeap.pop();
            ++retVal;
            ++startDay;
            while ((minHeap.size() > 0) && (minHeap.top() < startDay)) {
                minHeap.pop();
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
    def maxEvents(self, events: List[List[int]]) -> int:
        retVal = 0

        events.sort(reverse=1)

        minHeap = []
        startDay = 0
        while events or minHeap:
            if not minHeap:
                startDay = events[-1][0]

            while events and events[-1][0] <= startDay:
                heappush(minHeap, events.pop()[1])

            heappop(minHeap)
            retVal += 1
            startDay += 1
            while minHeap and minHeap[0] < startDay:
                heappop(minHeap)

        return retVal
```

</details>

## [1402. Reducing Dishes](https://leetcode.com/problems/reducing-dishes/)  1679

- [Official](https://leetcode.cn/problems/reducing-dishes/solutions/198214/zuo-cai-shun-xu-by-leetcode-solution/)

<details><summary>Description</summary>

```text
A chef has collected data on the satisfaction level of his n dishes. Chef can cook any dish in 1 unit of time.

Like-time coefficient of a dish is defined as the time taken to cook
that dish including previous dishes multiplied by its satisfaction level i.e. time[i] * satisfaction[i].

Return the maximum sum of like-time coefficient that the chef can obtain after dishes preparation.

Dishes can be prepared in any order and the chef can discard some dishes to get this maximum value.

Example 1:
Input: satisfaction = [-1,-8,0,5,-9]
Output: 14
Explanation: After Removing the second and last dish,
the maximum total like-time coefficient will be equal to (-1*1 + 0*2 + 5*3 = 14).
Each dish is prepared in one unit of time.

Example 2:
Input: satisfaction = [4,3,2]
Output: 20
Explanation: Dishes can be prepared in any order, (2*1 + 3*2 + 4*3 = 20)

Example 3:
Input: satisfaction = [-1,-4,-5]
Output: 0
Explanation: People do not like the dishes. No dish is prepared.

Constraints:
n == satisfaction.length
1 <= n <= 500
-1000 <= satisfaction[i] <= 1000
```

<details><summary>Hint</summary>

```text
1. Use dynamic programming to find the optimal solution by saving the previous best like-time coefficient
   and its corresponding element sum.
2. If adding the current element to the previous best like-time coefficient
   and its corresponding element sum would increase the best like-time coefficient, then go ahead and add it.
   Otherwise, keep the previous best like-time coefficient.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
int maxSatisfaction(int* satisfaction, int satisfactionSize) {
    int retVal = 0;

    qsort(satisfaction, satisfactionSize, sizeof(int), compareInteger);

    int sum = 0;
    int i;
    for (i = 0; i < satisfactionSize; ++i) {
        sum += satisfaction[i];
        if (sum < 0) {
            break;
        }
        retVal += sum;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxSatisfaction(vector<int>& satisfaction) {
        int retVal = 0;

        sort(satisfaction.begin(), satisfaction.end(), [&](const int& x, const int& y) {
            // descending order
            return (x > y);
        });

        int sum = 0;
        for (auto iterator : satisfaction) {
            sum += iterator;
            if (sum <= 0) {
                break;
            }
            retVal += sum;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxSatisfaction(self, satisfaction: List[int]) -> int:
        retVal = 0

        satisfaction.sort(reverse=True)

        sum = 0
        for i in satisfaction:
            sum += i
            if sum >= 0:
                retVal += sum

        return retVal
```

</details>

## [1405. Longest Happy String](https://leetcode.com/problems/longest-happy-string/)  1820

- [Official](https://leetcode.com/problems/longest-happy-string/editorial/)
- [Official](https://leetcode.cn/problems/longest-happy-string/solutions/1245601/zui-chang-kuai-le-zi-fu-chuan-by-leetcod-5nde/)

<details><summary>Description</summary>

```text
A string s is called happy if it satisfies the following conditions:
- s only contains the letters 'a', 'b', and 'c'.
- s does not contain any of "aaa", "bbb", or "ccc" as a substring.
- s contains at most a occurrences of the letter 'a'.
- s contains at most b occurrences of the letter 'b'.
- s contains at most c occurrences of the letter 'c'.

Given three integers a, b, and c, return the longest possible happy string.
If there are multiple longest happy strings, return any of them.
If there is no such string, return the empty string "".

A substring is a contiguous sequence of characters within a string.

Example 1:
Input: a = 1, b = 1, c = 7
Output: "ccaccbcc"
Explanation: "ccbccacc" would also be a correct answer.

Example 2:
Input: a = 7, b = 1, c = 0
Output: "aabaa"
Explanation: It is the only correct answer in this case.

Constraints:
0 <= a, b, c <= 100
a + b + c > 0
```

<details><summary>Hint</summary>

```text
1. Use a greedy approach.
2. Use the letter with the maximum current limit that can be added without breaking the condition.
```

</details>

</details>

<details><summary>C</summary>

```c
char* longestDiverseString(int a, int b, int c) {
    char* pRetVal = NULL;

    int returnSize = a + b + c + 1;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));

    int idx = 0;
    int curra = 0;
    int currb = 0;
    int currc = 0;
    int totalIterations = a + b + c;
    int i;
    for (i = 0; i < totalIterations; i++) {
        if (a >= b && a >= c && curra != 2) {
            pRetVal[idx++] = 'a';
            a--;
            curra++;
            currb = 0;
            currc = 0;
        } else if (a > 0 && (currb == 2 || currc == 2)) {
            pRetVal[idx++] = 'a';
            a--;
            curra++;
            currb = 0;
            currc = 0;
        } else if (b >= a && b >= c && currb != 2) {
            pRetVal[idx++] = 'b';
            b--;
            currb++;
            curra = 0;
            currc = 0;
        } else if (b > 0 && (currc == 2 || curra == 2)) {
            pRetVal[idx++] = 'b';
            b--;
            currb++;
            curra = 0;
            currc = 0;
        } else if (c >= a && c >= b && currc != 2) {
            pRetVal[idx++] = 'c';
            c--;
            currc++;
            curra = 0;
            currb = 0;
        } else if (c > 0 && (curra == 2 || currb == 2)) {
            pRetVal[idx++] = 'c';
            c--;
            currc++;
            curra = 0;
            currb = 0;
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
    string longestDiverseString(int a, int b, int c) {
        string retVal;

        int curra = 0;
        int currb = 0;
        int currc = 0;
        int totalIterations = a + b + c;
        for (int i = 0; i < totalIterations; i++) {
            if (a >= b && a >= c && curra != 2) {
                retVal += 'a';
                a--;
                curra++;
                currb = 0;
                currc = 0;
            } else if (a > 0 && (currb == 2 || currc == 2)) {
                retVal += 'a';
                a--;
                curra++;
                currb = 0;
                currc = 0;
            } else if (b >= a && b >= c && currb != 2) {
                retVal += 'b';
                b--;
                currb++;
                curra = 0;
                currc = 0;
            } else if (b > 0 && (currc == 2 || curra == 2)) {
                retVal += 'b';
                b--;
                currb++;
                curra = 0;
                currc = 0;
            } else if (c >= a && c >= b && currc != 2) {
                retVal += 'c';
                c--;
                currc++;
                curra = 0;
                currb = 0;
            } else if (c > 0 && (curra == 2 || currb == 2)) {
                retVal += 'c';
                c--;
                currc++;
                curra = 0;
                currb = 0;
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
    def longestDiverseString(self, a: int, b: int, c: int) -> str:
        retVal = ""

        curra = 0
        currb = 0
        currc = 0
        totalIterations = a + b + c
        for _ in range(totalIterations):
            if (a >= b and a >= c and curra != 2):
                retVal += "a"
                a -= 1
                curra += 1
                currb = 0
                currc = 0
            elif (a > 0 and (currb == 2 or currc == 2)):
                retVal += "a"
                a -= 1
                curra += 1
                currb = 0
                currc = 0
            elif (b >= a and b >= c and currb != 2):
                retVal += "b"
                b -= 1
                currb += 1
                curra = 0
                currc = 0
            elif (b > 0 and (currc == 2 or curra == 2)):
                retVal += "b"
                b -= 1
                currb += 1
                curra = 0
                currc = 0
            elif (c >= a and c >= b and currc != 2):
                retVal += "c"
                c -= 1
                currc += 1
                curra = 0
                currb = 0
            elif (c > 0 and (curra == 2 or currb == 2)):
                retVal += "c"
                c -= 1
                currc += 1
                curra = 0
                currb = 0

        return retVal
```

</details>

## [1432. Max Difference You Can Get From Changing an Integer](https://leetcode.com/problems/max-difference-you-can-get-from-changing-an-integer/)  1426

- [Official](https://leetcode.com/problems/max-difference-you-can-get-from-changing-an-integer/editorial/)
- [Official](https://leetcode.cn/problems/max-difference-you-can-get-from-changing-an-integer/solutions/514358/gai-bian-yi-ge-zheng-shu-neng-de-dao-de-0byhw/)

<details><summary>Description</summary>

```text
You are given an integer num. You will apply the following steps to num two separate times:
- Pick a digit x (0 <= x <= 9).
- Pick another digit y (0 <= y <= 9). Note y can be equal to x.
- Replace all the occurrences of x in the decimal representation of num by y.

Let a and b be the two results from applying the operation to num independently.

Return the max difference between a and b.

Note that neither a nor b may have any leading zeros, and must not be 0.

Example 1:
Input: num = 555
Output: 888
Explanation: The first time pick x = 5 and y = 9 and store the new integer in a.
The second time pick x = 5 and y = 1 and store the new integer in b.
We have now a = 999 and b = 111 and max difference = 888

Example 2:
Input: num = 9
Output: 8
Explanation: The first time pick x = 9 and y = 9 and store the new integer in a.
The second time pick x = 9 and y = 1 and store the new integer in b.
We have now a = 9 and b = 1 and max difference = 8

Constraints:
1 <= num <= 10^8
```

<details><summary>Hint</summary>

```text
1. We need to get the max and min value after changing num and the answer is max - min.
2. Use brute force, try all possible changes and keep the minimum and maximum values.
```

</details>

</details>

<details><summary>C</summary>

```c
void replace(char* s, char x, char y) {
    for (int i = 0; s[i]; ++i) {
        if (s[i] == x) {
            s[i] = y;
        }
    }
}
int maxDiff(int num) {
    int retVal = 0;

#define MAX_NUMS_SIZE (16)  // 1 <= num <= 10^8

    // Find a high position and replace it with 9.
    char maxNum[MAX_NUMS_SIZE];
    snprintf(maxNum, sizeof(maxNum), "%d", num);
    for (int i = 0; maxNum[i]; ++i) {
        if (maxNum[i] != '9') {
            replace(maxNum, maxNum[i], '9');
            break;
        }
    }

    // Replace the most significant bit with 1
    // Or find a high-order digit that is not equal to the highest digit and replace it with 0.
    char minNum[MAX_NUMS_SIZE];
    snprintf(minNum, sizeof(minNum), "%d", num);
    for (int i = 0; minNum[i]; ++i) {
        char digit = minNum[i];
        if (i == 0) {
            if (digit != '1') {
                replace(minNum, digit, '1');
                break;
            }
        } else {
            if (digit != '0' && digit != minNum[0]) {
                replace(minNum, digit, '0');
                break;
            }
        }
    }

    retVal = atoi(maxNum) - atoi(minNum);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    static void replace(string& s, char x, char y) {
        for (char& digit : s) {
            if (digit == x) {
                digit = y;
            }
        }
    }

   public:
    int maxDiff(int num) {
        int retVal = 0;

        // Find a high position and replace it with 9.
        string maxNum = to_string(num);
        for (char digit : maxNum) {
            if (digit != '9') {
                replace(maxNum, digit, '9');
                break;
            }
        }

        // Replace the most significant bit with 1
        // Or find a high-order digit that is not equal to the highest digit and  replace it with 0.
        string minNum = to_string(num);
        int minNumSize = minNum.size();
        for (int i = 0; i < minNumSize; ++i) {
            char digit = minNum[i];
            if (i == 0) {
                if (digit != '1') {
                    replace(minNum, digit, '1');
                    break;
                }
            } else {
                if (digit != '0' && digit != minNum[0]) {
                    replace(minNum, digit, '0');
                    break;
                }
            }
        }

        retVal = stoi(maxNum) - stoi(minNum);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxDiff(self, num: int) -> int:
        retVal = 0

        # Find a high position and replace it with 9.
        maxNum = str(num)
        for digit in maxNum:
            if digit != "9":
                maxNum = maxNum.replace(digit, "9")
                break

        # Replace the most significant bit with 1
        # Or find a high-order digit that is not equal to the highest digit and replace it with 0.
        minNum = str(num)
        for i, digit in enumerate(minNum):
            if i == 0:
                if digit != "1":
                    minNum = minNum.replace(digit, "1")
                    break
            else:
                if (digit != "0") and (digit != minNum[0]):
                    minNum = minNum.replace(digit, "0")
                    break

        retVal = int(maxNum) - int(minNum)

        return retVal
```

</details>

## [1481. Least Number of Unique Integers after K Removals](https://leetcode.com/problems/least-number-of-unique-integers-after-k-removals/)  1284

- [Official](https://leetcode.com/problems/least-number-of-unique-integers-after-k-removals/editorial/)
- [Official](https://leetcode.cn/problems/least-number-of-unique-integers-after-k-removals/solutions/579291/bu-tong-zheng-shu-de-zui-shao-shu-mu-by-h6h4i/)

<details><summary>Description</summary>

```text
Given an array of integers arr and an integer k.
Find the least number of unique integers after removing exactly k elements.

Example 1:
Input: arr = [5,5,4], k = 1
Output: 1
Explanation: Remove the single 4, only 5 is left.

Example 2:
Input: arr = [4,3,1,1,3,3,2], k = 3
Output: 2
Explanation: Remove 4, 2 and either one of the two 1s or three 3s. 1 and 3 will be left.

Constraints:
1 <= arr.length <= 10^5
1 <= arr[i] <= 10^9
0 <= k <= arr.length
```

<details><summary>Hint</summary>

```text
1. Use a map to count the frequencies of the numbers in the array.
2. An optimal strategy is to remove the numbers with the smallest count first.
```

</details>

</details>

<details><summary>C</summary>

```c
typedef struct {
    int number;
    int times;
} pair;
int compareStruct(const void* a, const void* b) {
    int pa = ((pair*)a)->times;
    int pb = ((pair*)b)->times;

    // ascending order
    return (pa > pb);
}
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int findLeastNumOfUniqueInts(int* arr, int arrSize, int k) {
    int retVal = 0;

    int i;

    qsort(arr, arrSize, sizeof(int), compareInteger);
    int previous = arr[0];
    int occurrencesSize = 1;
    for (i = 1; i < arrSize; ++i) {
        if (previous != arr[i]) {
            previous = arr[i];
            occurrencesSize++;
        }
    }

    pair occurrences[occurrencesSize];
    memset(occurrences, 0, sizeof(occurrences));
    occurrencesSize = 0;
    occurrences[occurrencesSize].number = arr[0];
    occurrences[occurrencesSize].times += 1;
    for (i = 1; i < arrSize; ++i) {
        if (occurrences[occurrencesSize].number != arr[i]) {
            occurrencesSize++;
            occurrences[occurrencesSize].number = arr[i];
        }
        occurrences[occurrencesSize].times += 1;
    }
    occurrencesSize++;
    qsort(occurrences, occurrencesSize, sizeof(pair), compareStruct);

    for (i = 0; i < occurrencesSize; ++i) {
        k -= occurrences[i].times;
        if (k < 0) {
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
    int findLeastNumOfUniqueInts(vector<int>& arr, int k) {
        int retVal = 0;

        unordered_map<int, int> occurrences;
        for (auto iterator : arr) {
            occurrences[iterator]++;
        }

        vector<pair<int, int>> occurrencesSort(occurrences.begin(), occurrences.end());
        sort(occurrencesSort.begin(), occurrencesSort.end(), [&](auto x1, auto x2) {
            // ascending order
            return x1.second < x2.second;
        });

        for (auto iterator : occurrencesSort) {
            k -= iterator.second;
            if (k < 0) {
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
    def findLeastNumOfUniqueInts(self, arr: List[int], k: int) -> int:
        retVal = 0

        arrCount = Counter(arr).most_common()
        arrCount.reverse()
        for _, times in arrCount:
            k -= times
            if k < 0:
                retVal += 1

        return retVal
```

</details>

## [1488. Avoid Flood in The City](https://leetcode.com/problems/avoid-flood-in-the-city/)  1974

- [Official](https://leetcode.com/problems/avoid-flood-in-the-city/editorial/)
- [Official](https://leetcode.cn/problems/avoid-flood-in-the-city/solutions/2472026/bi-mian-hong-shui-fan-lan-by-leetcode-so-n5c9/)

<details><summary>Description</summary>

```text
Your country has an infinite number of lakes.
Initially, all the lakes are empty, but when it rains over the nth lake, the nth lake becomes full of water.
If it rains over a lake that is full of water, there will be a flood. Your goal is to avoid floods in any lake.

Given an integer array rains where:
- rains[i] > 0 means there will be rains over the rains[i] lake.
- rains[i] == 0 means there are no rains this day and you can choose one lake this day and dry it.

Return an array ans where:
- ans.length == rains.length
- ans[i] == -1 if rains[i] > 0.
- ans[i] is the lake you choose to dry in the ith day if rains[i] == 0.

If there are multiple valid answers return any of them. If it is impossible to avoid flood return an empty array.

Notice that if you chose to dry a full lake, it becomes empty, but if you chose to dry an empty lake, nothing changes.

Example 1:
Input: rains = [1,2,3,4]
Output: [-1,-1,-1,-1]
Explanation:
After the first day full lakes are [1]
After the second day full lakes are [1,2]
After the third day full lakes are [1,2,3]
After the fourth day full lakes are [1,2,3,4]
There's no day to dry any lake and there is no flood in any lake.

Example 2:
Input: rains = [1,2,0,0,2,1]
Output: [-1,-1,2,1,-1,-1]
Explanation:
After the first day full lakes are [1]
After the second day full lakes are [1,2]
After the third day, we dry lake 2. Full lakes are [1]
After the fourth day, we dry lake 1. There is no full lakes.
After the fifth day, full lakes are [2].
After the sixth day, full lakes are [1,2].
It is easy that this scenario is flood-free. [-1,-1,1,2,-1,-1] is another acceptable scenario.

Example 3:
Input: rains = [1,2,0,1,2]
Output: []
Explanation:
After the second day, full lakes are  [1,2]. We have to dry one lake in the third day.
After that, it will rain over lakes [1,2].
It's easy to prove that no matter which lake you choose to dry in the 3rd day, the other one will flood.

Constraints:
1 <= rains.length <= 10^5
0 <= rains[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Keep An array of the last day there was rains over each city.
2. Keep an array of the days you can dry a lake when you face one.
3. When it rains over a lake, check the first possible day you can dry this lake and assign this day to this lake.
```

</details>

</details>

<details><summary>C</summary>

```c
// https://leetcode.cn/problems/avoid-flood-in-the-city/solutions/590510/cyu-yan-uthashshi-xian-by-liu-xiang-3-vw7g/
struct hashTable {
    int pool;
    int day;
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->pool, pFree->day);
        HASH_DEL(pFree, current);
        free(current);
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* avoidFlood(int* rains, int rainsSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int*)malloc(rainsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, rainsSize * sizeof(int));

    struct hashTable* pPoolInfo = NULL;
    struct hashTable* pSunDay = NULL;
    struct hashTable *pTemp, *s1, *s2;
    int i, j, rain;
    for (i = 0; i < rainsSize; ++i) {
        rain = rains[i];

        pTemp = NULL;
        if (rain == 0) {
            pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                free(pRetVal);
                pRetVal = NULL;
                goto exit;
            }
            pTemp->pool = i;
            HASH_ADD_INT(pSunDay, pool, pTemp);
            pRetVal[i] = 1;
            continue;
        }

        pRetVal[i] = -1;

        s1 = NULL;
        HASH_FIND_INT(pPoolInfo, &rain, s1);
        if (s1 == NULL) {
            s1 = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (s1 == NULL) {
                perror("malloc");
                free(pRetVal);
                pRetVal = NULL;
                goto exit;
            }
            s1->pool = rain;
            s1->day = i;
            HASH_ADD_INT(pPoolInfo, pool, s1);
            continue;
        }

        pTemp = NULL;
        s2 = NULL;
        j = 0;
        HASH_ITER(hh, pSunDay, s2, pTemp) {
            if (s2->pool > s1->day) {
                break;
            }
            j++;
        }
        if (j == HASH_COUNT(pSunDay)) {
            free(pRetVal);
            pRetVal = NULL;
            goto exit;
        }

        s1->day = i;
        pRetVal[s2->pool] = s1->pool;
        HASH_DEL(pSunDay, s2);
        free(s2);
    }
    (*returnSize) = rainsSize;

exit:
    //
    freeAll(pPoolInfo);
    pPoolInfo = NULL;
    freeAll(pSunDay);
    pSunDay = NULL;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> avoidFlood(vector<int>& rains) {
        vector<int> retVal;

        int rainsSize = rains.size();
        retVal.resize(rainsSize, 1);

        set<int> st;
        unordered_map<int, int> mp;
        for (int i = 0; i < rainsSize; ++i) {
            if (rains[i] == 0) {
                st.insert(i);
                continue;
            }

            retVal[i] = -1;
            if (mp.count(rains[i])) {
                auto it = st.lower_bound(mp[rains[i]]);
                if (it == st.end()) {
                    retVal = {};
                    break;
                }
                retVal[*it] = rains[i];
                st.erase(it);
            }
            mp[rains[i]] = i;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def avoidFlood(self, rains: List[int]) -> List[int]:
        retVal = []

        rainsSize = len(rains)
        retVal = [1] * rainsSize

        st = SortedList()
        mp = {}
        for i, rain in enumerate(rains):
            if rain == 0:
                st.add(i)
                continue

            retVal[i] = -1
            if rain in mp:
                it = st.bisect(mp[rain])
                if it == len(st):
                    retVal = []
                    break
                retVal[st[it]] = rain
                st.discard(st[it])
            mp[rain] = i

        return retVal
```

</details>

## [1509. Minimum Difference Between Largest and Smallest Value in Three Moves](https://leetcode.com/problems/minimum-difference-between-largest-and-smallest-value-in-three-moves/)  1653

- [Official](https://leetcode.com/problems/minimum-difference-between-largest-and-smallest-value-in-three-moves/editorial/)
- [Official](https://leetcode.cn/problems/minimum-difference-between-largest-and-smallest-value-in-three-moves/solutions/336428/san-ci-cao-zuo-hou-zui-da-zhi-yu-zui-xiao-zhi-de-2/)

<details><summary>Description</summary>

```text
You are given an integer array nums.

In one move, you can choose one element of nums and change it to any value.

Return the minimum difference between the largest and smallest value of nums after performing at most three moves.

Example 1:
Input: nums = [5,3,2,4]
Output: 0
Explanation: We can make at most 3 moves.
In the first move, change 2 to 3. nums becomes [5,3,3,4].
In the second move, change 4 to 3. nums becomes [5,3,3,3].
In the third move, change 5 to 3. nums becomes [3,3,3,3].
After performing 3 moves, the difference between the minimum and maximum is 3 - 3 = 0.

Example 2:
Input: nums = [1,5,0,10,14]
Output: 1
Explanation: We can make at most 3 moves.
In the first move, change 5 to 0. nums becomes [1,0,0,10,14].
In the second move, change 10 to 0. nums becomes [1,0,0,0,14].
In the third move, change 14 to 1. nums becomes [1,0,0,0,1].
After performing 3 moves, the difference between the minimum and maximum is 1 - 0 = 1.
It can be shown that there is no way to make the difference 0 in 3 moves.

Example 3:
Input: nums = [3,100,20]
Output: 0
Explanation: We can make at most 3 moves.
In the first move, change 100 to 7. nums becomes [3,7,20].
In the second move, change 20 to 7. nums becomes [3,7,7].
In the third move, change 3 to 7. nums becomes [7,7,7].
After performing 3 moves, the difference between the minimum and maximum is 7 - 7 = 0.

Constraints:
1 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. The minimum difference possible is obtained by removing three elements
   between the three smallest and three largest values in the array.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int minDifference(int* nums, int numsSize) {
    int retVal = 0;

    if (numsSize <= 4) {  // If the array has 4 or fewer elements, return 0
        return retVal;
    }

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int minDiff = INT_MAX;
    int left, right;
    for (left = 0; left < 4; ++left) {
        right = numsSize - 4 + left;
        minDiff = fmin(minDiff, nums[right] - nums[left]);
    }
    retVal = minDiff;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minDifference(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        if (numsSize <= 4) {  // If the array has 4 or fewer elements, return 0
            return retVal;
        }

        sort(nums.begin(), nums.end());

        int minDiff = numeric_limits<int>::max();
        for (int left = 0; left < 4; ++left) {
            int right = numsSize - 4 + left;
            minDiff = min(minDiff, nums[right] - nums[left]);
        }
        retVal = minDiff;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minDifference(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)
        if numsSize <= 4:  # If the array has 4 or fewer elements, return 0
            return retVal

        nums.sort()
        minDiff = float("inf")

        # Four scenarios to compute the minimum difference
        for left in range(4):
            right = numsSize - 4 + left
            minDiff = min(minDiff, nums[right] - nums[left])
        retVal = minDiff

        return retVal
```

</details>

## [1561. Maximum Number of Coins You Can Get](https://leetcode.com/problems/maximum-number-of-coins-you-can-get/)  1405

- [Official](https://leetcode.com/problems/maximum-number-of-coins-you-can-get/editorial/)
- [Official](https://leetcode.cn/problems/maximum-number-of-coins-you-can-get/solutions/409109/ni-ke-yi-huo-de-de-zui-da-ying-bi-shu-mu-by-leetco/)

<details><summary>Description</summary>

```text
There are 3n piles of coins of varying size, you and your friends will take piles of coins as follows:
- In each step, you will choose any 3 piles of coins (not necessarily consecutive).
- Of your choice, Alice will pick the pile with the maximum number of coins.
- You will pick the next pile with the maximum number of coins.
- Your friend Bob will pick the last pile.
- Repeat until there are no more piles of coins.

Given an array of integers piles where piles[i] is the number of coins in the ith pile.
Return the maximum number of coins that you can have.

Example 1:
Input: piles = [2,4,1,2,7,8]
Output: 9
Explanation: Choose the triplet (2, 7, 8),
Alice Pick the pile with 8 coins, you the pile with 7 coins and Bob the last one.
Choose the triplet (1, 2, 4), Alice Pick the pile with 4 coins, you the pile with 2 coins and Bob the last one.
The maximum number of coins which you can have are: 7 + 2 = 9.
On the other hand if we choose this arrangement (1, 2, 8), (2, 4, 7) you only get 2 + 4 = 6 coins which is not optimal.

Example 2:
Input: piles = [2,4,5]
Output: 4

Example 3:
Input: piles = [9,8,7,6,5,1,2,3,4]
Output: 18

Constraints:
3 <= piles.length <= 10^5
piles.length % 3 == 0
1 <= piles[i] <= 10^4
```

<details><summary>Hint</summary>

```text
1. Which pile of coins will you never be able to pick up?
2. Bob is forced to take the last pile of coins, no matter what it is. Which pile should you give to him?
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int maxCoins(int* piles, int pilesSize) {
    int retVal = 0;

    qsort(piles, pilesSize, sizeof(int), compareInteger);

    int left = 0;
    int right = pilesSize - 1;
    while (left < right) {
        --right;
        retVal += piles[right];
        --right;
        ++left;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxCoins(vector<int>& piles) {
        int retVal = 0;

        int pilesSize = piles.size();
        sort(piles.begin(), piles.end());

        int left = 0;
        int right = pilesSize - 1;
        while (left < right) {
            --right;
            retVal += piles[right];
            --right;
            ++left;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxCoins(self, piles: List[int]) -> int:
        retVal = 0

        pilesSize = len(piles)
        piles.sort()

        left = 0
        right = pilesSize - 1
        while left < right:
            right -= 1
            retVal += piles[right]
            right -= 1
            left += 1

        return retVal
```

</details>

## [1578. Minimum Time to Make Rope Colorful](https://leetcode.com/problems/minimum-time-to-make-rope-colorful/)  1574

- [Official](https://leetcode.cn/problems/minimum-time-to-make-rope-colorful/solutions/440327/bi-mian-zhong-fu-zi-mu-de-zui-xiao-shan-chu-chen-4/)

<details><summary>Description</summary>

```text
Alice has n balloons arranged on a rope.
You are given a 0-indexed string colors where colors[i] is the color of the ith balloon.

Alice wants the rope to be colorful.
She does not want two consecutive balloons to be of the same color, so she asks Bob for help.
Bob can remove some balloons from the rope to make it colorful.
You are given a 0-indexed integer array neededTime where neededTime[i] is the time (in seconds)
that Bob needs to remove the ith balloon from the rope.

Return the minimum time Bob needs to make the rope colorful.

Example 1:
Input: colors = "abaac", neededTime = [1,2,3,4,5]
Output: 3
Explanation: In the above image, 'a' is blue, 'b' is red, and 'c' is green.
Bob can remove the blue balloon at index 2. This takes 3 seconds.
There are no longer two consecutive balloons of the same color. Total time = 3.

Example 2:
Input: colors = "abc", neededTime = [1,2,3]
Output: 0
Explanation: The rope is already colorful. Bob does not need to remove any balloons from the rope.

Example 3:
Input: colors = "aabaa", neededTime = [1,2,3,4,1]
Output: 2
Explanation: Bob will remove the ballons at indices 0 and 4. Each ballon takes 1 second to remove.
There are no longer two consecutive balloons of the same color. Total time = 1 + 1 = 2.

Constraints:
n == colors.length == neededTime.length
1 <= n <= 10^5
1 <= neededTime[i] <= 10^4
colors contains only lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Maintain the running sum and max value for repeated letters.
```

</details>

</details>

<details><summary>C</summary>

```c
int minCost(char* colors, int* neededTime, int neededTimeSize) {
    int retVal = 0;

    int colorsSize = strlen(colors);

    int maxNeededTime, cost;
    char previous;
    int i = 0;
    while (i < colorsSize) {
        previous = colors[i];
        maxNeededTime = 0;
        cost = 0;
        while ((i < colorsSize) && (colors[i] == previous)) {
            maxNeededTime = fmax(maxNeededTime, neededTime[i]);
            cost += neededTime[i];
            ++i;
        }
        retVal += (cost - maxNeededTime);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minCost(string colors, vector<int>& neededTime) {
        int retVal = 0;

        int colorsSize = colors.size();

        int i = 0;
        while (i < colorsSize) {
            char previous = colors[i];
            int maxNeededTime = 0;
            int cost = 0;
            while ((i < colorsSize) && (colors[i] == previous)) {
                maxNeededTime = max(maxNeededTime, neededTime[i]);
                cost += neededTime[i];
                ++i;
            }
            retVal += (cost - maxNeededTime);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minCost(self, colors: str, neededTime: List[int]) -> int:
        retVal = 0

        colorsSize = len(colors)

        i = 0
        while i < colorsSize:
            previous = colors[i]
            maxNeededTime = 0
            cost = 0
            while i < colorsSize and colors[i] == previous:
                maxNeededTime = max(maxNeededTime, neededTime[i])
                cost += neededTime[i]
                i += 1
            retVal += cost - maxNeededTime

        return retVal
```

</details>

## [1605. Find Valid Matrix Given Row and Column Sums](https://leetcode.com/problems/find-valid-matrix-given-row-and-column-sums/)  1867

- [Official](https://leetcode.com/problems/find-valid-matrix-given-row-and-column-sums/editorial/)
- [Official](https://leetcode.cn/problems/find-valid-matrix-given-row-and-column-sums/solutions/2165784/gei-ding-xing-he-lie-de-he-qiu-ke-xing-j-u8dj/)

<details><summary>Description</summary>

```text
You are given two arrays rowSum and colSum of non-negative integers
where rowSum[i] is the sum of the elements in the ith row
and colSum[j] is the sum of the elements of the jth column of a 2D matrix.
In other words, you do not know the elements of the matrix, but you do know the sums of each row and column.

Find any matrix of non-negative integers of size rowSum.length x colSum.length
that satisfies the rowSum and colSum requirements.

Return a 2D array representing any matrix that fulfills the requirements.
It's guaranteed that at least one matrix that fulfills the requirements exists.

Example 1:
Input: rowSum = [3,8], colSum = [4,7]
Output: [[3,0], [1,7]]
Explanation:
0th row: 3 + 0 = 3 == rowSum[0]
1st row: 1 + 7 = 8 == rowSum[1]
0th column: 3 + 1 = 4 == colSum[0]
1st column: 0 + 7 = 7 == colSum[1]
The row and column sums match, and all matrix elements are non-negative.
Another possible matrix is: [[1,2], [3,5]]

Example 2:
Input: rowSum = [5,7,10], colSum = [8,6,8]
Output: [[0,5,0], [6,1,0], [2,0,8]]

Constraints:
1 <= rowSum.length, colSum.length <= 500
0 <= rowSum[i], colSum[i] <= 10^8
sum(rowSum) == sum(colSum)
```

<details><summary>Hint</summary>

```text
1. Find the smallest rowSum or colSum, and let it be x.
   Place that number in the grid, and subtract x from rowSum and colSum.
   Continue until all the sums are satisfied.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** restoreMatrix(int* rowSum, int rowSumSize, int* colSum, int colSumSize, int* returnSize,
                    int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;

    //
    (*returnColumnSizes) = (int*)malloc(rowSumSize * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        return pRetVal;
    }
    //
    pRetVal = (int**)malloc(rowSumSize * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }
    for ((*returnSize) = 0; (*returnSize) < rowSumSize; ++(*returnSize)) {
        pRetVal[(*returnSize)] = (int*)malloc(colSumSize * sizeof(int));
        if (pRetVal[(*returnSize)] == NULL) {
            perror("malloc");
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            for (int i = 0; i < (*returnSize); ++i) {
                free(pRetVal[i]);
                pRetVal[i] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        memset(pRetVal[(*returnSize)], 0, (colSumSize * sizeof(int)));
        (*returnColumnSizes)[(*returnSize)] = colSumSize;
    }

    /* rowSum = [5,7,10], colSum = [8,6,8]
     *       8 6 8       3 6 8       0 6 8       0 2 8      0 0 8      0 0 0
     *   --+-------  --+-------  --+-------  --+-------  --+-------  --+-------
     *   5 | 0 0 0   0 | 5 0 0   0 | 5 0 0   0 | 5 0 0   0 | 5 0 0   0 | 5 0 0
     *   7 | 0 0 0   7 | 0 0 0   4 | 3 0 0   0 | 3 4 0   0 | 3 4 0   0 | 3 4 0
     *  10 | 0 0 0  10 | 0 0 0  10 | 0 0 0  10 | 0 0 0   8 | 0 2 0   0 | 0 2 8
     */
    int x = 0;
    int y = 0;
    while ((x < rowSumSize) && (y < colSumSize)) {
        pRetVal[x][y] = fmin(rowSum[x], colSum[y]);
        rowSum[x] -= pRetVal[x][y];
        colSum[y] -= pRetVal[x][y];
        if (rowSum[x] == 0) {
            x++;
        } else {
            y++;
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
    vector<vector<int>> restoreMatrix(vector<int>& rowSum, vector<int>& colSum) {
        vector<vector<int>> retVal;

        int rowSumSize = rowSum.size();
        int colSumSize = colSum.size();
        retVal.resize(rowSumSize, vector<int>(colSumSize, 0));

        /* rowSum = [5,7,10], colSum = [8,6,8]
         *       8 6 8       3 6 8       0 6 8       0 2 8      0 0 8      0 0 0
         *   --+-------  --+-------  --+-------  --+-------  --+-------  --+-------
         *   5 | 0 0 0   0 | 5 0 0   0 | 5 0 0   0 | 5 0 0   0 | 5 0 0   0 | 5 0 0
         *   7 | 0 0 0   7 | 0 0 0   4 | 3 0 0   0 | 3 4 0   0 | 3 4 0   0 | 3 4 0
         *  10 | 0 0 0  10 | 0 0 0  10 | 0 0 0  10 | 0 0 0   8 | 0 2 0   0 | 0 2 8
         */
        int x = 0;
        int y = 0;
        while ((x < rowSumSize) && (y < colSumSize)) {
            retVal[x][y] = min(rowSum[x], colSum[y]);
            rowSum[x] -= retVal[x][y];
            colSum[y] -= retVal[x][y];
            if (rowSum[x] == 0) {
                x++;
            } else {
                y++;
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
    def restoreMatrix(self, rowSum: List[int], colSum: List[int]) -> List[List[int]]:
        retVal = []

        rowSumSize = len(rowSum)
        colSumSize = len(colSum)
        retVal = [[0 for _ in range(colSumSize)] for _ in range(rowSumSize)]

        # rowSum = [5,7,10], colSum = [8,6,8]
        #      8 6 8       3 6 8       0 6 8       0 2 8      0 0 8      0 0 0
        #  --+-------  --+-------  --+-------  --+------  --+------- --+-------
        #  5 | 0 0 0   0 | 5 0 0   0 | 5 0 0   0 | 5 0 0  0 | 5 0 0  0 | 5 0 0
        #  7 | 0 0 0   7 | 0 0 0   4 | 3 0 0   0 | 3 4 0  0 | 3 4 0  0 | 3 4 0
        # 10 | 0 0 0  10 | 0 0 0  10 | 0 0 0  10 | 0 0 0  8 | 0 2 0  0 | 0 2 8
        x = 0
        y = 0
        while (x < rowSumSize) and (y < colSumSize):
            retVal[x][y] = min(rowSum[x], colSum[y])
            rowSum[x] -= retVal[x][y]
            colSum[y] -= retVal[x][y]
            if rowSum[x] == 0:
                x += 1
            else:
                y += 1

        return retVal
```

</details>

## [1642. Furthest Building You Can Reach](https://leetcode.com/problems/furthest-building-you-can-reach/)  1962

<details><summary>Description</summary>

```text
You are given an integer array heights representing the heights of buildings, some bricks, and some ladders.

You start your journey from building 0 and move to the next building by possibly using bricks or ladders.

While moving from building i to building i+1 (0-indexed),
- If the current building's height is greater than or equal to the next building's height,
  you do not need a ladder or bricks.
- If the current building's height is less than the next building's height,
  you can either use one ladder or (h[i+1] - h[i]) bricks.

Return the furthest building index (0-indexed) you can reach if you use the given ladders and bricks optimally.

Example 1:
Input: heights = [4,2,7,6,9,14,12], bricks = 5, ladders = 1
Output: 4
Explanation: Starting at building 0, you can follow these steps:
- Go to building 1 without using ladders nor bricks since 4 >= 2.
- Go to building 2 using 5 bricks. You must use either bricks or ladders because 2 < 7.
- Go to building 3 without using ladders nor bricks since 7 >= 6.
- Go to building 4 using your only ladder. You must use either bricks or ladders because 6 < 9.
It is impossible to go beyond building 4 because you do not have any more bricks or ladders.

Example 2:
Input: heights = [4,12,2,7,3,18,20,3,19], bricks = 10, ladders = 2
Output: 7

Example 3:
Input: heights = [14,3,19,3], bricks = 17, ladders = 0
Output: 3

Constraints:
1 <= heights.length <= 10^5
1 <= heights[i] <= 10^6
0 <= bricks <= 10^9
0 <= ladders <= heights.length
```

<details><summary>Hint</summary>

```text
1. Assume the problem is to check whether you can reach the last building or not.
2. You'll have to do a set of jumps, and choose for each one whether to do it using a ladder or bricks.
   It's always optimal to use ladders in the largest jumps.
3. Iterate on the buildings, maintaining the largest r jumps and the sum of the remaining ones so far,
   and stop whenever this sum exceeds b.
```

</details>

</details>

<details><summary>C</summary>

```c
#ifndef HEAP_H
#define HEAP_H

//
void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}
//
typedef struct {
    int* data;     // Array to store the heap elements
    int size;      // Current size of the heap
    int capacity;  // Maximum capacity of the heap
} MinHeap;
//
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = NULL;

    minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    if (minHeap == NULL) {
        perror("malloc");
        return minHeap;
    }

    minHeap->data = (int*)malloc(capacity * sizeof(int));
    if (minHeap == NULL) {
        perror("malloc");
        free(minHeap);
        minHeap = NULL;
        return minHeap;
    }
    minHeap->size = 0;
    minHeap->capacity = capacity;

    return minHeap;
}
void heapifyMinHeap(MinHeap* minHeap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    // Function to heapify the heap starting from the given index
    if ((left < minHeap->size) && (minHeap->data[left] < minHeap->data[smallest])) {
        smallest = left;
    }

    if ((right < minHeap->size) && (minHeap->data[right] < minHeap->data[smallest])) {
        smallest = right;
    }

    if (smallest != index) {
        swap(&minHeap->data[index], &minHeap->data[smallest]);
        heapifyMinHeap(minHeap, smallest);
    }
}
void pushMinHeap(MinHeap* minHeap, int value) {
    if (minHeap->size == minHeap->capacity) {
        printf("Heap is full. Cannot insert more elements.\n");
        return;
    }

    int index = minHeap->size++;
    minHeap->data[index] = value;

    // Fix the min heap property by comparing the value with its parent
    while ((index != 0) && (minHeap->data[(index - 1) / 2] > minHeap->data[index])) {
        swap(&minHeap->data[(index - 1) / 2], &minHeap->data[index]);
        index = (index - 1) / 2;
    }
}
int popMinHeap(MinHeap* minHeap) {
    int retVal = -1;

    if (minHeap->size == 0) {
        printf("Heap is empty. Cannot remove elements.\n");
        return retVal;
    }

    retVal = minHeap->data[0];
    minHeap->data[0] = minHeap->data[minHeap->size - 1];
    minHeap->size--;
    heapifyMinHeap(minHeap, 0);

    return retVal;
}
void printMinHeap(MinHeap* minHeap) {
    printf("Min Heap: ");
    for (int i = 0; i < minHeap->size; i++) {
        printf("%d ", minHeap->data[i]);
    }
    printf("\n");
}
void freeMinHeap(MinHeap* minHeap) {
    free(minHeap->data);
    minHeap->data = NULL;
    free(minHeap);
    minHeap = NULL;
}

#endif  // HEAP_H
int furthestBuilding(int* heights, int heightsSize, int bricks, int ladders) {
    int retVal = 0;

    int brickSum = 0;
    MinHeap* pLaddersHeap = createMinHeap(heightsSize);
    if (pLaddersHeap == NULL) {
        return retVal;
    }

    int diff;
    int i;
    for (i = 1; i < heightsSize; ++i) {
        diff = heights[i] - heights[i - 1];
        if (diff <= 0) {
            continue;
        }

        pushMinHeap(pLaddersHeap, diff);
        if (pLaddersHeap->size > ladders) {
            brickSum += popMinHeap(pLaddersHeap);
        }

        if (brickSum > bricks) {
            retVal = i - 1;
            goto exit;
        }
    }
    retVal = heightsSize - 1;

exit:
    //
    freeMinHeap(pLaddersHeap);
    pLaddersHeap = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
        int retVal = 0;

        int heightsSize = heights.size();

        int brickSum = 0;
        priority_queue<int, vector<int>, greater<int>> laddersHeap;
        for (int i = 1; i < heightsSize; ++i) {
            int diff = heights[i] - heights[i - 1];
            if (diff <= 0) {
                continue;
            }

            laddersHeap.push(diff);
            int laddersHeapSize = laddersHeap.size();
            if (laddersHeapSize > ladders) {
                brickSum += laddersHeap.top();
                laddersHeap.pop();
            }

            if (brickSum > bricks) {
                retVal = i - 1;
                return retVal;
            }
        }

        retVal = heightsSize - 1;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def furthestBuilding(self, heights: List[int], bricks: int, ladders: int) -> int:
        retVal = 0

        heightsSize = len(heights)

        bricksSum = 0
        laddersHeap = []
        for i in range(1, heightsSize):
            diff = heights[i] - heights[i-1]
            if diff <= 0:
                continue

            heappush(laddersHeap, diff)
            if len(laddersHeap) > ladders:
                bricksSum += heappop(laddersHeap)

            if bricksSum > bricks:
                retVal = i - 1
                return retVal

        retVal = heightsSize - 1

        return retVal
```

</details>

## [1717. Maximum Score From Removing Substrings](https://leetcode.com/problems/maximum-score-from-removing-substrings/)  1867

- [Official](https://leetcode.com/problems/maximum-score-from-removing-substrings/editorial/)

<details><summary>Description</summary>

```text
You are given a string s and two integers x and y. You can perform two types of operations any number of times.
- Remove substring "ab" and gain x points.
  - For example, when removing "ab" from "cabxbae" it becomes "cxbae".
- Remove substring "ba" and gain y points.
  - For example, when removing "ba" from "cabxbae" it becomes "cabxe".

Return the maximum points you can gain after applying the above operations on s.

Example 1:
Input: s = "cdbcbbaaabab", x = 4, y = 5
Output: 19
Explanation:
- Remove the "ba" underlined in "cdbcbbaaabab". Now, s = "cdbcbbaaab" and 5 points are added to the score.
- Remove the "ab" underlined in "cdbcbbaaab". Now, s = "cdbcbbaa" and 4 points are added to the score.
- Remove the "ba" underlined in "cdbcbbaa". Now, s = "cdbcba" and 5 points are added to the score.
- Remove the "ba" underlined in "cdbcba". Now, s = "cdbc" and 5 points are added to the score.
Total score = 5 + 4 + 5 + 5 = 19.

Example 2:
Input: s = "aabbaaxybbaabb", x = 5, y = 4
Output: 20

Constraints:
1 <= s.length <= 10^5
1 <= x, y <= 10^4
s consists of lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Note that it is always more optimal to take one type of substring before another
2. You can use a stack to handle erasures
```

</details>

</details>

<details><summary>C</summary>

```c
int maximumGain(char* s, int x, int y) {
    int retVal = 0;

    int sSize = strlen(s);

    // Ensure "ab" always has more points than "ba"
    int left = 0;
    int right = sSize - 1;
    int temp;
    if (x < y) {
        temp = x;
        x = y;
        y = temp;
        while (left < right) {
            temp = s[left];
            s[left++] = s[right];
            s[right--] = temp;
        }
    }

    int aCount = 0;
    int bCount = 0;
    int i;
    for (i = 0; i < sSize; ++i) {
        if (s[i] == 'a') {
            ++aCount;
        } else if (s[i] == 'b') {
            if (aCount > 0) {
                --aCount;
                retVal += x;
            } else {
                ++bCount;
            }
        } else {
            retVal += fmin(bCount, aCount) * y;
            aCount = 0;
            bCount = 0;
        }
    }
    retVal += fmin(bCount, aCount) * y;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maximumGain(string s, int x, int y) {
        int retVal = 0;

        // Ensure "ab" always has more points than "ba"
        if (x < y) {
            int temp = x;
            x = y;
            y = temp;
            reverse(s.begin(), s.end());
        }

        int aCount = 0;
        int bCount = 0;
        for (auto c : s) {
            if (c == 'a') {
                ++aCount;
            } else if (c == 'b') {
                if (aCount > 0) {
                    --aCount;
                    retVal += x;
                } else {
                    ++bCount;
                }
            } else {
                retVal += min(bCount, aCount) * y;
                aCount = 0;
                bCount = 0;
            }
        }
        retVal += min(bCount, aCount) * y;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maximumGain(self, s: str, x: int, y: int) -> int:
        retVal = 0

        # Ensure "ab" always has higher points than "ba"
        if x < y:
            s = s[::-1]
            x, y = y, x

        aCount = 0
        bCount = 0
        for c in s:
            if c == "a":
                aCount += 1
            elif c == "b":
                if aCount > 0:
                    aCount -= 1
                    retVal += x
                else:
                    bCount += 1
            else:
                retVal += min(bCount, aCount) * y
                aCount = 0
                bCount = 0
        retVal += min(bCount, aCount) * y

        return retVal
```

</details>

## [1727. Largest Submatrix With Rearrangements](https://leetcode.com/problems/largest-submatrix-with-rearrangements/)  1926

- [Official](https://leetcode.com/problems/largest-submatrix-with-rearrangements/editorial/)

<details><summary>Description</summary>

```text
You are given a binary matrix matrix of size m x n,
and you are allowed to rearrange the columns of the matrix in any order.

Return the area of the largest submatrix within matrix where every element of the submatrix is 1
after reordering the columns optimally.

Example 1:
Input: matrix = [[0,0,1],[1,1,1],[1,0,1]]
Output: 4
Explanation: You can rearrange the columns as shown above.
The largest submatrix of 1s, in bold, has an area of 4.

Example 2:
Input: matrix = [[1,0,1,0,1]]
Output: 3
Explanation: You can rearrange the columns as shown above.
The largest submatrix of 1s, in bold, has an area of 3.

Example 3:
Input: matrix = [[1,1,0],[1,0,1]]
Output: 2
Explanation: Notice that you must rearrange entire columns,
and there is no way to make a submatrix of 1s larger than an area of 2.

Constraints:
m == matrix.length
n == matrix[i].length
1 <= m * n <= 10^5
matrix[i][j] is either 0 or 1.
```

<details><summary>Hint</summary>

```text
1. For each column, find the number of consecutive ones ending at each position.
2. For each row, sort the cumulative ones in non-increasing order and "fit" the largest submatrix.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
int largestSubmatrix(int** matrix, int matrixSize, int* matrixColSize) {
    int retVal = 0;

    int rowSize = matrixSize;
    int colSize = matrixColSize[0];
    int x, y;

    for (x = 1; x < rowSize; ++x) {
        for (y = 0; y < colSize; ++y) {
            if (matrix[x][y] == 1) {
                matrix[x][y] += matrix[x - 1][y];
            }
        }
    }

    for (x = 0; x < rowSize; ++x) {
        qsort(matrix[x], colSize, sizeof(int), compareInteger);
        for (y = 0; y < colSize; ++y) {
            retVal = fmax(retVal, matrix[x][y] * (y + 1));
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
    int largestSubmatrix(vector<vector<int>>& matrix) {
        int retVal = 0;

        int rowSize = matrix.size();
        int colSize = matrix[0].size();

        for (int x = 1; x < rowSize; ++x) {
            for (int y = 0; y < colSize; ++y) {
                if (matrix[x][y] == 1) {
                    matrix[x][y] += matrix[x - 1][y];
                }
            }
        }

        for (int x = 0; x < rowSize; ++x) {
            sort(matrix[x].begin(), matrix[x].end(), greater());
            for (int y = 0; y < colSize; ++y) {
                retVal = max(retVal, matrix[x][y] * (y + 1));
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
    def largestSubmatrix(self, matrix: List[List[int]]) -> int:
        retVal = 0

        rowSize = len(matrix)
        colSize = len(matrix[0])

        for x in range(1, rowSize):
            for y in range(colSize):
                if matrix[x][y] == 1:
                    matrix[x][y] += matrix[x - 1][y]

        for x in range(rowSize):
            matrix[x].sort(reverse=True)
            for y in range(colSize):
                retVal = max(retVal, matrix[x][y] * (y + 1))

        return retVal
```

</details>

## [1733. Minimum Number of People to Teach](https://leetcode.com/problems/minimum-number-of-people-to-teach/)  1984

- [Official](https://leetcode.com/problems/minimum-number-of-people-to-teach/editorial/)
- [Official](https://leetcode.cn/problems/minimum-number-of-people-to-teach/solutions/3766885/xu-yao-jiao-yu-yan-de-zui-shao-ren-shu-b-jaf9/)

<details><summary>Description</summary>

```text
On a social network consisting of m users and some friendships between users,
two users can communicate with each other if they know a common language.

You are given an integer n, an array languages, and an array friendships where:
- There are n languages numbered 1 through n,
- languages[i] is the set of languages the i​​​​​​th​​​​ user knows, and
- friendships[i] = [u​​​​​​i​​​, v​​​​​​i] denotes a friendship between the users u​​​​​​​​​​​i​​​​​ and vi.

You can choose one language and teach it to some users so that all friends can communicate with each other.
Return the minimum number of users you need to teach.

Note that friendships are not transitive, meaning if x is a friend of y and y is a friend of z,
this doesn't guarantee that x is a friend of z.

Example 1:
Input: n = 2, languages = [[1],[2],[1,2]], friendships = [[1,2],[1,3],[2,3]]
Output: 1
Explanation: You can either teach user 1 the second language or user 2 the first language.

Example 2:
Input: n = 3, languages = [[2],[1,3],[1,2],[3]], friendships = [[1,4],[1,2],[3,4],[2,3]]
Output: 2
Explanation: Teach the third language to users 1 and 3, yielding two users to teach.

Constraints:
2 <= n <= 500
languages.length == m
1 <= m <= 500
1 <= languages[i].length <= n
1 <= languages[i][j] <= n
1 <= u​​​​​​i < v​​​​​​i <= languages.length
1 <= friendships.length <= 500
All tuples (u​​​​​i, v​​​​​​i) are unique
languages[i] contains only unique values
```

<details><summary>Hint</summary>

```text
1. You can just use brute force and find out for each language the number of users you need to teach
2. Note that a user can appear in multiple friendships but you need to teach that user only once
```

</details>

</details>

<details><summary>C</summary>

```c
struct hashTable {
    int key;
    UT_hash_handle hh;
};
bool hashAddItem(struct hashTable **obj, int key) {
    bool retVal = false;

    struct hashTable *pEntry = NULL;
    HASH_FIND_INT(*obj, &key, pEntry);
    if (pEntry != NULL) {
        return retVal;
    }
    pEntry = (struct hashTable *)malloc(sizeof(struct hashTable));
    if (pEntry == NULL) {
        perror("malloc");
        return retVal;
    }
    pEntry->key = key;
    HASH_ADD_INT(*obj, key, pEntry);
    retVal = true;

    return retVal;
}
void hashFree(struct hashTable **obj) {
    struct hashTable *current = NULL;
    struct hashTable *tmp = NULL;
    HASH_ITER(hh, *obj, current, tmp) {
        // printf("%d\n", pFree->key);
        HASH_DEL(*obj, current);
        free(current);
    }
}
int minimumTeachings(int n, int **languages, int languagesSize, int *languagesColSize, int **friendships,
                     int friendshipsSize, int *friendshipsColSize) {
    int retVal = 0;

    struct hashTable *cncon = NULL;
    struct hashTable *mp = NULL;
    struct hashTable *pEntry = NULL;
    int person1, person2, key;
    bool conm;
    for (int i = 0; i < friendshipsSize; i++) {
        person1 = friendships[i][0] - 1;
        person2 = friendships[i][1] - 1;
        for (int j = 0; j < languagesColSize[person1]; j++) {
            hashAddItem(&mp, languages[person1][j]);
        }

        conm = false;
        for (int j = 0; j < languagesColSize[person2]; j++) {
            pEntry = NULL;
            key = languages[person2][j];
            HASH_FIND_INT(mp, &key, pEntry);
            if (pEntry != NULL) {
                conm = true;
                break;
            }
        }
        if (conm == false) {
            hashAddItem(&cncon, person1);
            hashAddItem(&cncon, person2);
        }

        hashFree(&mp);
        mp = NULL;
    }

    int maxCnt = 0;
    int *cnt = (int *)calloc(n + 1, sizeof(int));
    if (cnt == NULL) {
        perror("calloc");
        hashFree(&cncon);
        return retVal;
    }
    int person, lan;
    for (struct hashTable *pEntry = cncon; pEntry; pEntry = pEntry->hh.next) {
        person = pEntry->key;
        for (int i = 0; i < languagesColSize[person]; i++) {
            lan = languages[person][i];
            cnt[lan]++;
            maxCnt = fmax(maxCnt, cnt[lan]);
        }
    }
    retVal = HASH_COUNT(cncon) - maxCnt;

    //
    free(cnt);
    cnt = NULL;
    hashFree(&cncon);
    cncon = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minimumTeachings(int n, vector<vector<int>>& languages, vector<vector<int>>& friendships) {
        int retVal = 0;

        unordered_set<int> cncon;
        for (auto friendship : friendships) {
            unordered_map<int, int> mp;
            for (int lan : languages[friendship[0] - 1]) {
                mp[lan] = 1;
            }

            bool conm = false;
            for (int lan : languages[friendship[1] - 1]) {
                if (mp[lan]) {
                    conm = true;
                    break;
                }
            }
            if (conm == false) {
                cncon.insert(friendship[0] - 1);
                cncon.insert(friendship[1] - 1);
            }
        }

        int maxCnt = 0;
        vector<int> cnt(n + 1, 0);
        for (auto friendship : cncon) {
            for (int lan : languages[friendship]) {
                cnt[lan]++;
                maxCnt = max(maxCnt, cnt[lan]);
            }
        }

        retVal = cncon.size() - maxCnt;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minimumTeachings(self, n: int, languages: List[List[int]], friendships: List[List[int]]) -> int:
        retVal = 0

        cncon = set()
        for friendship in friendships:
            mp = {}
            for lan in languages[friendship[0] - 1]:
                mp[lan] = 1

            conm = False
            for lan in languages[friendship[1] - 1]:
                if lan in mp:
                    conm = True
                    break
            if conm == False:
                cncon.add(friendship[0] - 1)
                cncon.add(friendship[1] - 1)

        maxCnt = 0
        cnt = [0] * (n + 1)
        for friendship in cncon:
            for lan in languages[friendship]:
                cnt[lan] += 1
                maxCnt = max(maxCnt, cnt[lan])

        retVal = len(cncon) - maxCnt

        return retVal
```

</details>

## [1764. Form Array by Concatenating Subarrays of Another Array](https://leetcode.com/problems/form-array-by-concatenating-subarrays-of-another-array/)  1588

- [Official](https://leetcode.cn/problems/form-array-by-concatenating-subarrays-of-another-array/solutions/2022689/tong-guo-lian-jie-ling-yi-ge-shu-zu-de-z-xsvx/)

<details><summary>Description</summary>

```text
You are given a 2D integer array groups of length n. You are also given an integer array nums.

You are asked if you can choose n disjoint subarrays from the array nums
such that the ith subarray is equal to groups[i] (0-indexed), and if i > 0,
the (i-1)th subarray appears before the ith subarray in nums (i.e. the subarrays must be in the same order as groups).

Return true if you can do this task, and false otherwise.

Note that the subarrays are disjoint if and only if there is no index k such that nums[k] belongs to more than one subarray.
A subarray is a contiguous sequence of elements within an array.

Example 1:
Input: groups = [[1,-1,-1],[3,-2,0]], nums = [1,-1,0,1,-1,-1,3,-2,0]
Output: true
Explanation: You can choose the 0th subarray as [1,-1,0,1,-1,-1,3,-2,0] and the 1st one as [1,-1,0,1,-1,-1,3,-2,0].
These subarrays are disjoint as they share no common nums[k] element.

Example 2:
Input: groups = [[10,-2],[1,2,3,4]], nums = [1,2,3,4,10,-2]
Output: false
Explanation: Note that choosing the subarrays [1,2,3,4,10,-2] and [1,2,3,4,10,-2] is incorrect
because they are not in the same order as in groups.
[10,-2] must come before [1,2,3,4].

Example 3:
Input: groups = [[1,2,3],[3,4]], nums = [7,7,1,2,3,4,7,7]
Output: false
Explanation: Note that choosing the subarrays [7,7,1,2,3,4,7,7] and [7,7,1,2,3,4,7,7] is invalid because they are not disjoint.
They share a common elements nums[4] (0-indexed).

Constraints:
groups.length == n
1 <= n <= 10^3
1 <= groups[i].length, sum(groups[i].length) <= 10^3
1 <= nums.length <= 10^3
-10^7 <= groups[i][j], nums[k] <= 10^7
```

</details>

<details><summary>C</summary>

```c
bool canChoose(int** groups, int groupsSize, int* groupsColSize, int* nums, int numsSize) {
    bool retVal = false;

    int i;
    int idx = 0;
    int row = 0;
    while ((idx < numsSize) && (row < groupsSize)) {
        if (idx + groupsColSize[row] > numsSize) {
            return retVal;
        }

        for (i = 0; i < groupsColSize[row]; ++i) {
            if (groups[row][i] != nums[idx + i]) {
                ++idx;
                break;
            }
        }
        if (i < groupsColSize[row]) {
            continue;
        }

        idx += groupsColSize[row];
        ++row;
    }

    if (row == groupsSize) {
        retVal = true;
    }

    return retVal;
}
```

</details>

## [1785. Minimum Elements to Add to Form a Given Sum](https://leetcode.com/problems/minimum-elements-to-add-to-form-a-given-sum/)  1432

- [Official](https://leetcode.cn/problems/minimum-elements-to-add-to-form-a-given-sum/solutions/2020959/gou-cheng-te-ding-he-xu-yao-tian-jia-de-m3gnt/)

<details><summary>Description</summary>

```text
You are given an integer array nums and two integers limit and goal.
The array nums has an interesting property that abs(nums[i]) <= limit.

Return the minimum number of elements you need to add to make the sum of the array equal to goal.
The array must maintain its property that abs(nums[i]) <= limit.

Note that abs(x) equals x if x >= 0, and -x otherwise.

Example 1:
Input: nums = [1,-1,1], limit = 3, goal = -4
Output: 2
Explanation: You can add -2 and -3, then the sum of the array will be 1 - 1 + 1 - 2 - 3 = -4.

Example 2:
Input: nums = [1,-10,9,1], limit = 100, goal = 0
Output: 1

Constraints:
1 <= nums.length <= 10^5
1 <= limit <= 10^6
-limit <= nums[i] <= limit
-10^9 <= goal <= 10^9
```

</details>

<details><summary>C</summary>

```c
int minElements(int* nums, int numsSize, int limit, int goal) {
    int retVal = 0;

    /* Boundary
     *  1 <= nums.length <= 10^5
     *  1 <= limit <= 10^6.
     */
    long long sum = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        sum += nums[i];
    }

    long long diff = llabs(sum - goal);
    /* divisible or not divisible
     *  diff = n * limit
     *  diff = n * limit + r
     */
    retVal = (diff + limit - 1) / limit;

    return retVal;
}
```

</details>

## [1827. Minimum Operations to Make the Array Increasing](https://leetcode.com/problems/minimum-operations-to-make-the-array-increasing/)  1314

- [Official](https://leetcode.cn/problems/minimum-operations-to-make-the-array-increasing/solutions/2014890/zui-shao-cao-zuo-shi-shu-zu-di-zeng-by-l-sjr6/)

<details><summary>Description</summary>

```text
You are given an integer array nums (0-indexed).
In one operation, you can choose an element of the array and increment it by 1.
- For example, if nums = [1,2,3], you can choose to increment nums[1] to make nums = [1,3,3].

Return the minimum number of operations needed to make nums strictly increasing.

An array nums is strictly increasing if nums[i] < nums[i+1] for all 0 <= i < nums.length - 1.
An array of length 1 is trivially strictly increasing.

Example 1:
Input: nums = [1,1,1]
Output: 3
Explanation: You can do the following operations:
1) Increment nums[2], so nums becomes [1,1,2].
2) Increment nums[1], so nums becomes [1,2,2].
3) Increment nums[2], so nums becomes [1,2,3].

Example 2:
Input: nums = [1,5,2,4,1]
Output: 14

Example 3:
Input: nums = [8]
Output: 0

Constraints:
1 <= nums.length <= 5000
1 <= nums[i] <= 10^4
```

<details><summary>Hint</summary>

```text
1. nums[i+1] must be at least equal to nums[i] + 1.
2. Think greedily. You don't have to increase nums[i+1] beyond nums[i]+1.
3. Iterate on i and set nums[i] = max(nums[i-1]+1, nums[i]) .
```

</details>

</details>

<details><summary>C</summary>

```c
int minOperations(int* nums, int numsSize) {
    int retVal = 0;

    int diff;
    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[i - 1] >= nums[i]) {
            diff = nums[i - 1] - nums[i] + 1;
            nums[i] += diff;
            retVal += diff;
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
    int minOperations(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        for (int i = 1; i < numsSize; ++i) {
            if (nums[i - 1] >= nums[i]) {
                int diff = nums[i - 1] - nums[i] + 1;
                nums[i] += diff;
                retVal += diff;
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

        numsSize = len(nums)
        for i in range(1,numsSize):
            if nums[i - 1] >= nums[i]:
                diff = nums[i - 1] - nums[i] + 1
                nums[i] += diff
                retVal += diff

        return retVal
```

</details>

## [1846. Maximum Element After Decreasing and Rearranging](https://leetcode.com/problems/maximum-element-after-decreasing-and-rearranging/)  1454

- [Official](https://leetcode.com/problems/maximum-element-after-decreasing-and-rearranging/editorial/)
- [Official](https://leetcode.cn/problems/maximum-element-after-decreasing-and-rearranging/solutions/754917/jian-xiao-he-zhong-xin-pai-lie-shu-zu-ho-mzee/)

<details><summary>Description</summary>

```text
You are given an array of positive integers arr.
Perform some operations (possibly none) on arr so that it satisfies these conditions:
- The value of the first element in arr must be 1.
- The absolute difference between any 2 adjacent elements must be less than or equal to 1.
  In other words, abs(arr[i] - arr[i - 1]) <= 1 for each i where 1 <= i < arr.length (0-indexed).
  abs(x) is the absolute value of x.

There are 2 types of operations that you can perform any number of times:
- Decrease the value of any element of arr to a smaller positive integer.
- Rearrange the elements of arr to be in any order.

Return the maximum possible value of an element in arr after performing the operations to satisfy the conditions.

Example 1:
Input: arr = [2,2,1,2,1]
Output: 2
Explanation:
We can satisfy the conditions by rearranging arr so it becomes [1,2,2,2,1].
The largest element in arr is 2.

Example 2:
Input: arr = [100,1,1000]
Output: 3
Explanation:
One possible way to satisfy the conditions is by doing the following:
1. Rearrange arr so it becomes [1,100,1000].
2. Decrease the value of the second element to 2.
3. Decrease the value of the third element to 3.
Now arr = [1,2,3], which satisfies the conditions.
The largest element in arr is 3.

Example 3:
Input: arr = [1,2,3,4,5]
Output: 5
Explanation: The array already satisfies the conditions, and the largest element is 5.

Constraints:
1 <= arr.length <= 10^5
1 <= arr[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Sort the Array.
2. Decrement each element to the largest integer that satisfies the conditions.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int maximumElementAfterDecrementingAndRearranging(int* arr, int arrSize) {
    int retVal = 1;

    qsort(arr, arrSize, sizeof(int), compareInteger);

    int i;
    for (i = 1; i < arrSize; ++i) {
        if (arr[i] - retVal >= 1) {
            retVal += 1;
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
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        int retVal = 1;

        sort(arr.begin(), arr.end());

        int arrSize = arr.size();
        for (int i = 1; i < arrSize; ++i) {
            if (arr[i] - retVal >= 1) {
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
    def maximumElementAfterDecrementingAndRearranging(self, arr: List[int]) -> int:
        retVal = 1

        arr.sort()

        arrSize = len(arr)
        for i in range(1, arrSize):
            if arr[i] - retVal >= 1:
                retVal += 1

        return retVal
```

</details>

## [1921. Eliminate Maximum Number of Monsters](https://leetcode.com/problems/eliminate-maximum-number-of-monsters/)  1527

- [Official](https://leetcode.com/problems/eliminate-maximum-number-of-monsters/editorial/)
- [Official](https://leetcode.cn/problems/eliminate-maximum-number-of-monsters/solutions/857961/xiao-mie-guai-wu-de-zui-da-shu-liang-by-0ou2p/)

<details><summary>Description</summary>

```text
You are playing a video game where you are defending your city from a group of n monsters.
You are given a 0-indexed integer array dist of size n,
where dist[i] is the initial distance in kilometers of the ith monster from the city.

The monsters walk toward the city at a constant speed.
The speed of each monster is given to you in an integer array speed of size n,
where speed[i] is the speed of the ith monster in kilometers per minute.

You have a weapon that, once fully charged, can eliminate a single monster.
However, the weapon takes one minute to charge. The weapon is fully charged at the very start.

You lose when any monster reaches your city.
If a monster reaches the city at the exact moment the weapon is fully charged,
it counts as a loss, and the game ends before you can use your weapon.

Return the maximum number of monsters that you can eliminate before you lose,
or n if you can eliminate all the monsters before they reach the city.

Example 1:
Input: dist = [1,3,4], speed = [1,1,1]
Output: 3
Explanation:
In the beginning, the distances of the monsters are [1,3,4]. You eliminate the first monster.
After a minute, the distances of the monsters are [X,2,3]. You eliminate the second monster.
After a minute, the distances of the monsters are [X,X,2]. You eliminate the thrid monster.
All 3 monsters can be eliminated.

Example 2:
Input: dist = [1,1,2,3], speed = [1,1,1,1]
Output: 1
Explanation:
In the beginning, the distances of the monsters are [1,1,2,3]. You eliminate the first monster.
After a minute, the distances of the monsters are [X,0,1,2], so you lose.
You can only eliminate 1 monster.

Example 3:
Input: dist = [3,2,4], speed = [5,3,2]
Output: 1
Explanation:
In the beginning, the distances of the monsters are [3,2,4]. You eliminate the first monster.
After a minute, the distances of the monsters are [X,0,2], so you lose.
You can only eliminate 1 monster.

Constraints:
n == dist.length == speed.length
1 <= n <= 10^5
1 <= dist[i], speed[i] <= 10^5
```

<details><summary>Hint</summary>

```text
1. Find the amount of time it takes each monster to arrive.
2. Find the order in which the monsters will arrive.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareDouble(const void* n1, const void* n2) {
    // ascending order
    return (*(double*)n1 > *(double*)n2);
}
int eliminateMaximum(int* dist, int distSize, int* speed, int speedSize) {
    int retVal = 0;

    double arrival[distSize];
    memset(arrival, 0, sizeof(arrival));

    int i;
    for (i = 0; i < distSize; ++i) {
        arrival[i] = (double)dist[i] / speed[i];
    }

    qsort(arrival, distSize, sizeof(double), compareDouble);

    for (i = 0; i < distSize; ++i) {
        if (arrival[i] <= i) {
            break;
        }
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
    int eliminateMaximum(vector<int>& dist, vector<int>& speed) {
        int retVal = 0;

        int distSize = dist.size();  // n == dist.length == speed.length

        vector<double> arrival;
        for (int i = 0; i < distSize; ++i) {
            arrival.emplace_back((double)dist[i] / speed[i]);
        }

        sort(arrival.begin(), arrival.end());

        for (int i = 0; i < distSize; ++i) {
            if (arrival[i] <= i) {
                break;
            }
            retVal += 1;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def eliminateMaximum(self, dist: List[int], speed: List[int]) -> int:
        retVal = 0

        arrival = []
        for d, s in zip(dist, speed):
            arrival.append(d / s)

        arrival.sort()

        for idx, value in enumerate(arrival):
            if value <= idx:
                break
            retVal += 1

        return retVal
```

</details>

## [1975. Maximum Matrix Sum](https://leetcode.com/problems/maximum-matrix-sum/)  1648

- [Official](https://leetcode.com/problems/maximum-matrix-sum/editorial/)
- [Official](https://leetcode.cn/problems/maximum-matrix-sum/solutions/951896/zui-da-fang-zhen-he-by-leetcode-solution-5xnx/)

<details><summary>Description</summary>

```text
You are given an n x n integer matrix. You can do the following operation any number of times:
- Choose any two adjacent elements of matrix and multiply each of them by -1.

Two elements are considered adjacent if and only if they share a border.

Your goal is to maximize the summation of the matrix's elements.
Return the maximum sum of the matrix's elements using the operation mentioned above.

Example 1:
Input: matrix = [[1,-1],[-1,1]]
Output: 4
Explanation: We can follow the following steps to reach sum equals 4:
- Multiply the 2 elements in the first row by -1.
- Multiply the 2 elements in the first column by -1.

Example 2:
Input: matrix = [[1,2,3],[-1,-2,-3],[1,2,3]]
Output: 16
Explanation: We can follow the following step to reach sum equals 16:
- Multiply the 2 last elements in the second row by -1.

Constraints:
n == matrix.length == matrix[i].length
2 <= n <= 250
-10^5 <= matrix[i][j] <= 10^5
```

<details><summary>Hint</summary>

```text
1. Try to use the operation so that each row has only one negative number.
2. If you have only one negative element you cannot convert it to positive.
```

</details>

</details>

<details><summary>C</summary>

```c
long long maxMatrixSum(int** matrix, int matrixSize, int* matrixColSize) {
    long long retVal = 0;

    int minAbsVal = INT_MAX;
    int negativeCount = 0;
    int row, col, value;
    for (row = 0; row < matrixSize; ++row) {
        for (col = 0; col < matrixColSize[row]; ++col) {
            value = matrix[row][col];
            retVal += abs(value);
            if (value < 0) {
                negativeCount++;
            }
            minAbsVal = fmin(minAbsVal, abs(value));
        }
    }

    if (negativeCount % 2 != 0) {
        retVal -= (2 * minAbsVal);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long maxMatrixSum(vector<vector<int>>& matrix) {
        long long retVal = 0;

        int minAbsVal = numeric_limits<int>::max();
        int negativeCount = 0;
        for (auto& rows : matrix) {
            for (int cell : rows) {
                retVal += abs(cell);
                if (cell < 0) {
                    negativeCount++;
                }
                minAbsVal = min(minAbsVal, abs(cell));
            }
        }

        if (negativeCount % 2 != 0) {
            retVal -= (2 * minAbsVal);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxMatrixSum(self, matrix: List[List[int]]) -> int:
        retVal = 0

        minAbsVal = float("inf")
        negativeCount = 0
        for rows in matrix:
            for cell in rows:
                retVal += abs(cell)
                if cell < 0:
                    negativeCount += 1
                minAbsVal = min(minAbsVal, abs(cell))

        if negativeCount % 2 != 0:
            retVal -= (2 * minAbsVal)

        return retVal
```

</details>
