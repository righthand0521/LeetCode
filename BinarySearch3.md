# [Binary Search](https://en.wikipedia.org/wiki/Binary_search_algorithm)

## [2040. Kth Smallest Product of Two Sorted Arrays](https://leetcode.com/problems/kth-smallest-product-of-two-sorted-arrays/)  2040

- [Official](https://leetcode.cn/problems/kth-smallest-product-of-two-sorted-arrays/solutions/3698504/liang-ge-you-xu-shu-zu-de-di-k-xiao-chen-5qt9/)

<details><summary>Description</summary>

```text
Given two sorted 0-indexed integer arrays nums1 and nums2 as well as an integer k,
return the kth (1-based) smallest product of nums1[i] * nums2[j] where 0 <= i < nums1.length and 0 <= j < nums2.length.

Example 1:
Input: nums1 = [2,5], nums2 = [3,4], k = 2
Output: 8
Explanation: The 2 smallest products are:
- nums1[0] * nums2[0] = 2 * 3 = 6
- nums1[0] * nums2[1] = 2 * 4 = 8
The 2nd smallest product is 8.

Example 2:
Input: nums1 = [-4,-2,0,3], nums2 = [2,4], k = 6
Output: 0
Explanation: The 6 smallest products are:
- nums1[0] * nums2[1] = (-4) * 4 = -16
- nums1[0] * nums2[0] = (-4) * 2 = -8
- nums1[1] * nums2[1] = (-2) * 4 = -8
- nums1[1] * nums2[0] = (-2) * 2 = -4
- nums1[2] * nums2[0] = 0 * 2 = 0
- nums1[2] * nums2[1] = 0 * 4 = 0
The 6th smallest product is 0.

Example 3:
Input: nums1 = [-2,-1,0,1,2], nums2 = [-3,-1,2,4,5], k = 3
Output: -6
Explanation: The 3 smallest products are:
- nums1[0] * nums2[4] = (-2) * 5 = -10
- nums1[0] * nums2[3] = (-2) * 4 = -8
- nums1[4] * nums2[0] = 2 * (-3) = -6
The 3rd smallest product is -6.

Constraints:
1 <= nums1.length, nums2.length <= 5 * 10^4
-10^5 <= nums1[i], nums2[j] <= 10^5
1 <= k <= nums1.length * nums2.length
nums1 and nums2 are sorted.
```

<details><summary>Hint</summary>

```text
1. Can we split this problem into four cases depending on the sign of the numbers?
2. Can we binary search the value?
```

</details>

</details>

<details><summary>C</summary>

```c
long long kthSmallestProduct(int* nums1, int nums1Size, int* nums2, int nums2Size, long long k) {
    long long retVal = 0;

    int pos1 = 0;
    while ((pos1 < nums1Size) && (nums1[pos1] < 0)) {
        pos1++;
    }
    int pos2 = 0;
    while ((pos2 < nums2Size) && (nums2[pos2] < 0)) {
        pos2++;
    }

    long long count, i1, i2;
    long long middle;
    long long left = -1e10;
    long long right = 1e10;
    while (left <= right) {
        middle = (left + right) / 2;
        count = 0;

        i1 = 0, i2 = pos2 - 1;
        while ((i1 < pos1) && (i2 >= 0)) {
            if ((long long)nums1[i1] * nums2[i2] > middle) {
                i1++;
            } else {
                count += (pos1 - i1);
                i2--;
            }
        }

        i1 = pos1;
        i2 = nums2Size - 1;
        while ((i1 < nums1Size) && (i2 >= pos2)) {
            if ((long long)nums1[i1] * nums2[i2] > middle) {
                i2--;
            } else {
                count += (i2 - pos2 + 1);
                i1++;
            }
        }

        i1 = 0;
        i2 = pos2;
        while ((i1 < pos1) && (i2 < nums2Size)) {
            if ((long long)nums1[i1] * nums2[i2] > middle) {
                i2++;
            } else {
                count += (nums2Size - i2);
                i1++;
            }
        }

        i1 = pos1;
        i2 = 0;
        while ((i1 < nums1Size) && (i2 < pos2)) {
            if ((long long)nums1[i1] * nums2[i2] > middle) {
                i1++;
            } else {
                count += (nums1Size - i1);
                i2++;
            }
        }

        if (count < k) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }
    retVal = left;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long kthSmallestProduct(vector<int>& nums1, vector<int>& nums2, long long k) {
        long long retVal = 0;

        int nums1Size = nums1.size();
        int nums2Size = nums2.size();

        int pos1 = 0;
        while ((pos1 < nums1Size) && (nums1[pos1] < 0)) {
            pos1++;
        }
        int pos2 = 0;
        while ((pos2 < nums2Size) && (nums2[pos2] < 0)) {
            pos2++;
        }

        long long left = -1e10;
        long long right = 1e10;
        while (left <= right) {
            long long middle = (left + right) / 2;
            long long count = 0;

            for (int i1 = 0, i2 = pos2 - 1; i1 < pos1 && i2 >= 0;) {
                if (static_cast<long long>(nums1[i1]) * nums2[i2] > middle) {
                    i1++;
                } else {
                    count += (pos1 - i1);
                    i2--;
                }
            }

            for (int i1 = pos1, i2 = nums2Size - 1; i1 < nums1Size && i2 >= pos2;) {
                if (static_cast<long long>(nums1[i1]) * nums2[i2] > middle) {
                    i2--;
                } else {
                    count += (i2 - pos2 + 1);
                    i1++;
                }
            }

            for (int i1 = 0, i2 = pos2; i1 < pos1 && i2 < nums2Size;) {
                if (static_cast<long long>(nums1[i1]) * nums2[i2] > middle) {
                    i2++;
                } else {
                    count += (nums2Size - i2);
                    i1++;
                }
            }

            for (int i1 = pos1, i2 = 0; i1 < nums1Size && i2 < pos2;) {
                if (static_cast<long long>(nums1[i1]) * nums2[i2] > middle) {
                    i1++;
                } else {
                    count += (nums1Size - i1);
                    i2++;
                }
            }

            if (count < k) {
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }
        retVal = left;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def kthSmallestProduct(self, nums1: List[int], nums2: List[int], k: int) -> int:
        retVal = 0

        nums1Size = len(nums1)
        nums2Size = len(nums2)

        pos1 = 0
        while (pos1 < nums1Size) and (nums1[pos1] < 0):
            pos1 += 1
        pos2 = 0
        while (pos2 < nums2Size) and (nums2[pos2] < 0):
            pos2 += 1

        left = int(-1e10)
        right = int(1e10)
        while left <= right:
            middle = (left + right) // 2
            count = 0

            i1 = 0
            i2 = pos2 - 1
            while (i1 < pos1) and (i2 >= 0):
                if nums1[i1] * nums2[i2] > middle:
                    i1 += 1
                else:
                    count += (pos1 - i1)
                    i2 -= 1

            i1 = pos1
            i2 = nums2Size - 1
            while (i1 < nums1Size) and (i2 >= pos2):
                if nums1[i1] * nums2[i2] > middle:
                    i2 -= 1
                else:
                    count += (i2 - pos2 + 1)
                    i1 += 1

            i1 = 0
            i2 = pos2
            while (i1 < pos1) and (i2 < nums2Size):
                if nums1[i1] * nums2[i2] > middle:
                    i2 += 1
                else:
                    count += (nums2Size - i2)
                    i1 += 1

            i1 = pos1
            i2 = 0
            while (i1 < nums1Size) and (i2 < pos2):
                if nums1[i1] * nums2[i2] > middle:
                    i1 += 1
                else:
                    count += (nums1Size - i1)
                    i2 += 1

            if count < k:
                left = middle + 1
            else:
                right = middle - 1

        retVal = left

        return retVal
```

</details>

## [2064. Minimized Maximum of Products Distributed to Any Store](https://leetcode.com/problems/minimized-maximum-of-products-distributed-to-any-store/)  1885

- [Official](https://leetcode.com/problems/minimized-maximum-of-products-distributed-to-any-store/editorial/)
- [Official](https://leetcode.cn/problems/minimized-maximum-of-products-distributed-to-any-store/solutions/1101801/fen-pei-gei-shang-dian-de-zui-duo-shang-g0nc2/)

<details><summary>Description</summary>

```text
You are given an integer n indicating there are n specialty retail stores.
There are m product types of varying amounts, which are given as a 0-indexed integer array quantities,
where quantities[i] represents the number of products of the ith product type.

You need to distribute all products to the retail stores following these rules:
- A store can only be given at most one product type but can be given any amount of it.
- After distribution, each store will have been given some number of products (possibly 0).
  Let x represent the maximum number of products given to any store.
  You want x to be as small as possible,
  i.e., you want to minimize the maximum number of products that are given to any store.

Return the minimum possible x.

Example 1:
Input: n = 6, quantities = [11,6]
Output: 3
Explanation: One optimal way is:
- The 11 products of type 0 are distributed to the first four stores in these amounts: 2, 3, 3, 3
- The 6 products of type 1 are distributed to the other two stores in these amounts: 3, 3
The maximum number of products given to any store is max(2, 3, 3, 3, 3, 3) = 3.

Example 2:
Input: n = 7, quantities = [15,10,10]
Output: 5
Explanation: One optimal way is:
- The 15 products of type 0 are distributed to the first three stores in these amounts: 5, 5, 5
- The 10 products of type 1 are distributed to the next two stores in these amounts: 5, 5
- The 10 products of type 2 are distributed to the last two stores in these amounts: 5, 5
The maximum number of products given to any store is max(5, 5, 5, 5, 5, 5, 5) = 5.

Example 3:
Input: n = 1, quantities = [100000]
Output: 100000
Explanation: The only optimal way is:
- The 100000 products of type 0 are distributed to the only store.
The maximum number of products given to any store is max(100000) = 100000.

Constraints:
m == quantities.length
1 <= m <= n <= 10^5
1 <= quantities[i] <= 10^5
```

<details><summary>Hint</summary>

```text
1. There exists a monotonic nature such that when x is smaller than some number, there will be no way to distribute,
   and when x is not smaller than that number, there will always be a way to distribute.
2. If you are given a number k, where the number of products given to any store does not exceed k,
   could you determine if all products can be distributed?
3. Implement a function canDistribute(k), which returns true if you can distribute all products
   such that any store will not be given more than k products, and returns false if you cannot.
   Use this function to binary search for the smallest possible k.
```

</details>

</details>

<details><summary>C</summary>

```c
bool canDistribute(int x, int* quantities, int quantitiesSize, int n) {
    bool retVal = false;

    int j = 0;
    int remaining = quantities[j];
    int i;
    for (i = 0; i < n; i++) {
        if (remaining > x) {
            remaining -= x;
            continue;
        }

        j++;
        if (j == quantitiesSize) {
            retVal = true;
            break;
        }
        remaining = quantities[j];
    }

    return retVal;
}
int minimizedMaximum(int n, int* quantities, int quantitiesSize) {
    int retVal = 0;

    int maxElement = quantities[0];
    for (int i = 1; i < quantitiesSize; ++i) {
        if (maxElement < quantities[i]) {
            maxElement = quantities[i];
        }
    }

    int middle;
    int left = 0;
    int right = maxElement;
    while (left < right) {
        middle = (left + right) / 2;
        if (canDistribute(middle, quantities, quantitiesSize, n) == true) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }
    retVal = left;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    bool canDistribute(int x, vector<int>& quantities, int n) {
        bool retVal = false;

        int quantitiesSize = quantities.size();
        int j = 0;
        int remaining = quantities[j];
        for (int i = 0; i < n; i++) {
            if (remaining > x) {
                remaining -= x;
                continue;
            }

            j++;
            if (j == quantitiesSize) {
                retVal = true;
                break;
            }
            remaining = quantities[j];
        }

        return retVal;
    }

   public:
    int minimizedMaximum(int n, vector<int>& quantities) {
        int retVal = 0;

        int left = 0;
        int right = *max_element(quantities.begin(), quantities.end());
        while (left < right) {
            int middle = (left + right) / 2;
            if (canDistribute(middle, quantities, n) == true) {
                right = middle;
            } else {
                left = middle + 1;
            }
        }
        retVal = left;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def canDistribute(self, x: int, quantities: List[int], n: int) -> bool:
        retVal = False

        quantitiesSize = len(quantities)

        i = 0
        remaining = quantities[i]
        for _ in range(n):
            if remaining > x:
                remaining -= x
                continue

            i += 1
            if i == quantitiesSize:
                retVal = True
                break
            remaining = quantities[i]

        return retVal

    def minimizedMaximum(self, n: int, quantities: List[int]) -> int:
        retVal = 0

        left = 0
        right = max(quantities)
        while left < right:
            middle = (left + right) // 2
            if self.canDistribute(middle, quantities, n) == True:
                right = middle
            else:
                left = middle + 1
        retVal = left

        return retVal
```

</details>

## [2071. Maximum Number of Tasks You Can Assign](https://leetcode.com/problems/maximum-number-of-tasks-you-can-assign/)  2648

- [Official](https://leetcode.com/problems/maximum-number-of-tasks-you-can-assign/editorial/)
- [Official](https://leetcode.cn/problems/maximum-number-of-tasks-you-can-assign/solutions/1101831/ni-ke-yi-an-pai-de-zui-duo-ren-wu-shu-mu-p7dm/)

<details><summary>Description</summary>

```text
You have n tasks and m workers. Each task has a strength requirement stored in a 0-indexed integer array tasks,
with the ith task requiring tasks[i] strength to complete.
The strength of each worker is stored in a 0-indexed integer array workers,
with the jth worker having workers[j] strength.
Each worker can only be assigned to a single task and
must have a strength greater than or equal to the task's strength requirement (i.e., workers[j] >= tasks[i]).

Additionally, you have pills magical pills that will increase a worker's strength by strength.
You can decide which workers receive the magical pills, however, you may only give each worker at most one magical pill.

Given the 0-indexed integer arrays tasks and workers and the integers pills and strength,
return the maximum number of tasks that can be completed.

Example 1:
Input: tasks = [3,2,1], workers = [0,3,3], pills = 1, strength = 1
Output: 3
Explanation:
We can assign the magical pill and tasks as follows:
- Give the magical pill to worker 0.
- Assign worker 0 to task 2 (0 + 1 >= 1)
- Assign worker 1 to task 1 (3 >= 2)
- Assign worker 2 to task 0 (3 >= 3)

Example 2:
Input: tasks = [5,4], workers = [0,0,0], pills = 1, strength = 5
Output: 1
Explanation:
We can assign the magical pill and tasks as follows:
- Give the magical pill to worker 0.
- Assign worker 0 to task 0 (0 + 5 >= 5)

Example 3:
Input: tasks = [10,15,30], workers = [0,10,10,10,10], pills = 3, strength = 10
Output: 2
Explanation:
We can assign the magical pills and tasks as follows:
- Give the magical pill to worker 0 and worker 1.
- Assign worker 0 to task 0 (0 + 10 >= 10)
- Assign worker 1 to task 1 (10 + 10 >= 15)
The last pill is not given because it will not make any worker strong enough for the last task.

Constraints:
n == tasks.length
m == workers.length
1 <= n, m <= 5 * 10^4
0 <= pills <= m
0 <= tasks[i], workers[j], strength <= 10^9
```

<details><summary>Hint</summary>

```text
1. Is it possible to assign the first k smallest tasks to the workers?
2. How can you efficiently try every k?
```

</details>

</details>

<details><summary>C</summary>

```c
bool check(int* tasks, int* workers, int workersSize, int pills, int strength, int middle) {
    bool retVal = false;

    int workersIdx = workersSize - 1;
    int workersQueue[workersSize];
    int workersQueueHead = workersSize - 1;
    int workersQueueTail = workersSize - 1;
    for (int i = middle - 1; i >= 0; --i) {
        while ((workersIdx >= workersSize - middle) && (workers[workersIdx] + strength >= tasks[i])) {
            workersQueue[workersQueueHead] = workers[workersIdx];
            --workersQueueHead;
            --workersIdx;
        }

        if (workersQueueHead == workersQueueTail) {
            return retVal;
        }

        // If the largest element in the deque is greater than or equal to tasks[i]
        if (workersQueue[workersQueueTail] >= tasks[i]) {
            workersQueueTail--;
            continue;
        }

        if (pills == 0) {
            return retVal;
        }

        --pills;
        workersQueueHead++;
    }
    retVal = true;

    return retVal;
}
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int maxTaskAssign(int* tasks, int tasksSize, int* workers, int workersSize, int pills, int strength) {
    int retVal = 0;

    qsort(tasks, tasksSize, sizeof(int), compareInteger);
    qsort(workers, workersSize, sizeof(int), compareInteger);

    int middle;
    int left = 1;
    int right = (workersSize < tasksSize) ? workersSize : tasksSize;
    while (left <= right) {
        middle = (left + right) / 2;
        if (check(tasks, workers, workersSize, pills, strength, middle) == true) {
            left = middle + 1;
            retVal = middle;
        } else {
            right = middle - 1;
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
    bool check(vector<int>& tasks, vector<int>& workers, int pills, int strength, int middle) {
        bool retVal = false;

        int workersSize = workers.size();
        int workersIdx = workersSize - 1;
        deque<int> workersQueue;
        for (int i = middle - 1; i >= 0; --i) {
            while ((workersIdx >= workersSize - middle) && (workers[workersIdx] + strength >= tasks[i])) {
                workersQueue.push_front(workers[workersIdx]);
                --workersIdx;
            }

            if (workersQueue.empty() == true) {
                return retVal;
            }

            // If the largest element in the deque is greater than or equal to tasks[i]
            if (workersQueue.back() >= tasks[i]) {
                workersQueue.pop_back();
                continue;
            }

            if (pills == 0) {
                return retVal;
            }

            --pills;
            workersQueue.pop_front();
        }
        retVal = true;

        return retVal;
    }

   public:
    int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength) {
        int retVal = 0;

        int tasksSize = tasks.size();
        sort(tasks.begin(), tasks.end());

        int workersSize = workers.size();
        sort(workers.begin(), workers.end());

        int left = 1;
        int right = min(workersSize, tasksSize);
        while (left <= right) {
            int middle = (left + right) / 2;
            if (check(tasks, workers, pills, strength, middle) == true) {
                left = middle + 1;
                retVal = middle;
            } else {
                right = middle - 1;
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
    def check(self, tasks: List[int], workers: List[int], pills: int, strength: int, middle: int) -> bool:
        retVal = False

        workersSize = len(workers)
        workersIdx = workersSize - 1
        workersQueue = deque()
        for i in range(middle - 1, -1, -1):
            while (workersIdx >= workersSize - middle) and (workers[workersIdx] + strength >= tasks[i]):
                workersQueue.appendleft(workers[workersIdx])
                workersIdx -= 1
            if not workersQueue:
                return retVal

            # If the largest element in the deque is greater than or equal to tasks[i]
            if workersQueue[-1] >= tasks[i]:
                workersQueue.pop()
                continue

            if pills == 0:
                return retVal

            pills -= 1
            workersQueue.popleft()

        retVal = True

        return retVal

    def maxTaskAssign(self, tasks: List[int], workers: List[int], pills: int, strength: int) -> int:
        retVal = 0

        tasksSize = len(tasks)
        tasks.sort()

        workersSize = len(workers)
        workers.sort()

        left = 1
        right = min(workersSize, tasksSize)
        while left <= right:
            middle = (left + right) // 2
            if self.check(tasks, workers, pills, strength, middle) == True:
                left = middle + 1
                retVal = middle
            else:
                right = middle - 1

        return retVal
```

</details>

## [2141. Maximum Running Time of N Computers](https://leetcode.com/problems/maximum-running-time-of-n-computers/)  2265

- [Official](https://leetcode.com/problems/maximum-running-time-of-n-computers/editorial/)
- [Official](https://leetcode.cn/problems/maximum-running-time-of-n-computers/solutions/1216064/tong-shi-yun-xing-n-tai-dian-nao-de-zui-ozvvu/)

<details><summary>Description</summary>

```text
You have n computers. You are given the integer n and a 0-indexed integer array batteries
where the ith battery can run a computer for batteries[i] minutes.
You are interested in running all n computers simultaneously using the given batteries.

Initially, you can insert at most one battery into each computer. After that and at any integer time moment,
you can remove a battery from a computer and insert another battery any number of times.
The inserted battery can be a totally new battery or a battery from another computer.
You may assume that the removing and inserting processes take no time.

Note that the batteries cannot be recharged.

Return the maximum number of minutes you can run all the n computers simultaneously.

Example 1:
Input: n = 2, batteries = [3,3,3]
Output: 4
Explanation:
Initially, insert battery 0 into the first computer and battery 1 into the second computer.
After two minutes, remove battery 1 from the second computer and insert battery 2 instead.
Note that battery 1 can still run for one minute.
At the end of the third minute, battery 0 is drained,
and you need to remove it from the first computer and insert battery 1 instead.
By the end of the fourth minute, battery 1 is also drained, and the first computer is no longer running.
We can run the two computers simultaneously for at most 4 minutes, so we return 4.

Example 2:
Input: n = 2, batteries = [1,1,1,1]
Output: 2
Explanation:
Initially, insert battery 0 into the first computer and battery 2 into the second computer.
After one minute, battery 0 and battery 2 are drained
so you need to remove them and insert battery 1 into the first computer and battery 3 into the second computer.
After another minute, battery 1 and battery 3 are also drained so the first and second computers are no longer running.
We can run the two computers simultaneously for at most 2 minutes, so we return 2.

Constraints:
1 <= n <= batteries.length <= 10^5
1 <= batteries[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. For a given running time, can you determine if it is possible to run all n computers simultaneously?
2. Try to use Binary Search to find the maximal running time
```

</details>

</details>

<details><summary>C</summary>

```c
long long maxRunTime(int n, int* batteries, int batteriesSize) {
    long long retVal = 0;

    int i;

    long sumPower = 0;
    for (i = 0; i < batteriesSize; ++i) {
        sumPower += batteries[i];
    }

    long long middle;
    long long left = 1;
    long long right = sumPower / n;
    while (left < right) {
        middle = right - (right - left) / 2;

        long long total = 0;
        for (i = 0; i < batteriesSize; ++i) {
            total += fmin(batteries[i], middle);
        }
        if (total >= (long long)(n * middle)) {
            left = middle;
        } else {
            right = middle - 1;
        }
    }
    retVal = left;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long maxRunTime(int n, vector<int>& batteries) {
        long long retVal = 0;

        long sumPower = 0;
        for (auto battery : batteries) {
            sumPower += battery;
        }

        long long left = 1;
        long long right = sumPower / n;
        while (left < right) {
            long long middle = right - (right - left) / 2;

            long long total = 0;
            for (long long battery : batteries) {
                total += min(battery, middle);
            }
            if (total >= (long long)(n * middle)) {
                left = middle;
            } else {
                right = middle - 1;
            }
        }
        retVal = left;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxRunTime(self, n: int, batteries: List[int]) -> int:
        retVal = 0

        left = 1
        right = sum(batteries) // n
        while left < right:
            middle = right - (right - left) // 2

            total = 0
            for power in batteries:
                total += min(power, middle)
            if total // n >= middle:
                left = middle
            else:
                right = middle - 1

        retVal = left

        return retVal
```

</details>

## [2179. Count Good Triplets in an Array](https://leetcode.com/problems/count-good-triplets-in-an-array/)  2272

- [Official](https://leetcode.com/problems/count-good-triplets-in-an-array/editorial/)
- [Official](https://leetcode.cn/problems/count-good-triplets-in-an-array/solutions/3650507/tong-ji-shu-zu-zhong-hao-san-yuan-zu-shu-u13d/)

<details><summary>Description</summary>

```text
You are given two 0-indexed arrays nums1 and nums2 of length n, both of which are permutations of [0, 1, ..., n - 1].

A good triplet is a set of 3 distinct values which are present in increasing order by position both in nums1 and nums2.
In other words, if we consider pos1v as the index of the value v in nums1 and pos2v as the index of the value v in nums2,
then a good triplet will be a set (x, y, z) where 0 <= x, y, z <= n - 1,
such that pos1x < pos1y < pos1z and pos2x < pos2y < pos2z.

Return the total number of good triplets.

Example 1:
Input: nums1 = [2,0,1,3], nums2 = [0,1,2,3]
Output: 1
Explanation:
There are 4 triplets (x,y,z) such that pos1x < pos1y < pos1z. They are (2,0,1), (2,0,3), (2,1,3), and (0,1,3).
Out of those triplets, only the triplet (0,1,3) satisfies pos2x < pos2y < pos2z. Hence, there is only 1 good triplet.

Example 2:
Input: nums1 = [4,0,1,3,2], nums2 = [4,1,0,2,3]
Output: 4
Explanation: The 4 good triplets are (4,0,3), (4,0,2), (4,1,3), and (4,1,2).

Constraints:
n == nums1.length == nums2.length
3 <= n <= 10^5
0 <= nums1[i], nums2[i] <= n - 1
nums1 and nums2 are permutations of [0, 1, ..., n - 1].
```

<details><summary>Hint</summary>

```text
1. For every value y,
   how can you find the number of values x (0 ≤ x, y ≤ n - 1) such that x appears before y in both of the arrays?
2. Similarly, for every value y,
   try finding the number of values z (0 ≤ y, z ≤ n - 1) such that z appears after y in both of the arrays.
3. Now, for every value y, count the number of good triplets that can be formed if y is considered as the middle element.
```

</details>

</details>

<details><summary>C</summary>

```c
#ifndef FENWICKTREE_H
#define FENWICKTREE_H

typedef struct {
    int* tree;
    int size;
} FenwickTree;
FenwickTree* fenwickTreeCreate(int size) {
    FenwickTree* obj = NULL;

    obj = (FenwickTree*)malloc(sizeof(FenwickTree));
    if (obj == NULL) {
        perror("malloc");
        return obj;
    }

    obj->size = size;
    obj->tree = (int*)calloc(size + 1, sizeof(int));
    if (obj->tree == NULL) {
        perror("malloc");
        free(obj);
        obj = NULL;
        return obj;
    }

    return obj;
}
void fenwickTreeUpdate(FenwickTree* obj, int index, int delta) {
    index++;
    while (index <= obj->size) {
        obj->tree[index] += delta;
        index += (index & -index);
    }
}
int fenwickTreeQuery(FenwickTree* obj, int index) {
    int retVal = 0;

    index++;
    while (index > 0) {
        retVal += obj->tree[index];
        index -= (index & -index);
    }

    return retVal;
}
void fenwickTreeFree(FenwickTree* obj) {
    free(obj->tree);
    obj->tree = NULL;
    free(obj);
    obj = NULL;
}

#endif  // FENWICKTREE_H
long long goodTriplets(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    long long retVal = 0;

    int* pos2 = (int*)malloc(nums1Size * sizeof(int));
    if (pos2 == NULL) {
        perror("malloc");
        return retVal;
    }
    for (int i = 0; i < nums1Size; i++) {
        pos2[nums2[i]] = i;
    }

    int* reversedIndexMapping = (int*)malloc(nums1Size * sizeof(int));
    if (reversedIndexMapping == NULL) {
        perror("malloc");
        free(pos2);
        return retVal;
    }
    for (int i = 0; i < nums1Size; i++) {
        reversedIndexMapping[pos2[nums1[i]]] = i;
    }

    FenwickTree* tree = fenwickTreeCreate(nums1Size);
    if (tree == NULL) {
        perror("malloc");
        free(pos2);
        free(reversedIndexMapping);
        return retVal;
    }

    for (int value = 0; value < nums1Size; value++) {
        int pos = reversedIndexMapping[value];
        int left = fenwickTreeQuery(tree, pos);
        fenwickTreeUpdate(tree, pos, 1);

        int right = (nums1Size - 1 - pos) - (value - left);
        retVal += ((long long)left * right);
    }

    // Free allocated memory
    free(pos2);
    free(reversedIndexMapping);
    fenwickTreeFree(tree);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class FenwickTree {
   private:
    vector<int> tree;

   public:
    FenwickTree(int size) : tree(size + 1, 0) {}
    void update(int index, int delta) {
        index++;
        int treeSize = tree.size();
        while (index < treeSize) {
            tree[index] += delta;
            index += (index & -index);
        }
    }
    int query(int index) {
        int retVal = 0;

        index++;
        while (index > 0) {
            retVal += tree[index];
            index -= (index & -index);
        }

        return retVal;
    }
};

class Solution {
   public:
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
        long long retVal = 0;

        int nums1Size = nums1.size();

        vector<int> pos2(nums1Size);
        for (int i = 0; i < nums1Size; i++) {
            pos2[nums2[i]] = i;
        }

        vector<int> reversedIndexMapping(nums1Size);
        for (int i = 0; i < nums1Size; i++) {
            reversedIndexMapping[pos2[nums1[i]]] = i;
        }

        FenwickTree tree(nums1Size);

        for (int value = 0; value < nums1Size; value++) {
            int pos = reversedIndexMapping[value];
            int left = tree.query(pos);
            tree.update(pos, 1);

            int right = (nums1Size - 1 - pos) - (value - left);
            retVal += ((long long)left * right);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class FenwickTree:
    def __init__(self, size: int) -> None:
        self.tree = [0] * (size + 1)

    def update(self, index: int, delta: int) -> None:
        index += 1
        treeSize = len(self.tree)
        while index <= treeSize - 1:
            self.tree[index] += delta
            index += (index & -index)

    def query(self, index: int) -> int:
        retVal = 0

        index += 1
        while index > 0:
            retVal += self.tree[index]
            index -= (index & -index)

        return retVal


class Solution:
    def goodTriplets(self, nums1: List[int], nums2: List[int]) -> int:
        retVal = 0

        nums1Size = len(nums1)

        pos2 = [0] * nums1Size
        for i, num2 in enumerate(nums2):
            pos2[num2] = i

        reversedIndexMapping = [0] * nums1Size
        for i, num1 in enumerate(nums1):
            reversedIndexMapping[pos2[num1]] = i

        tree = FenwickTree(nums1Size)

        for value in range(nums1Size):
            pos = reversedIndexMapping[value]
            left = tree.query(pos)
            tree.update(pos, 1)
            right = (nums1Size - 1 - pos) - (value - left)
            retVal += (left * right)

        return retVal
```

</details>

## [2187. Minimum Time to Complete Trips](https://leetcode.com/problems/minimum-time-to-complete-trips/)  1640

- [Official](https://leetcode.cn/problems/minimum-time-to-complete-trips/solutions/1300957/wan-cheng-lu-tu-de-zui-shao-shi-jian-by-uxyrp/)

<details><summary>Description</summary>

```text
You are given an array time where time[i] denotes the time taken by the ith bus to complete one trip.

Each bus can make multiple trips successively;
that is, the next trip can start immediately after completing the current trip.
Also, each bus operates independently; that is, the trips of one bus do not influence the trips of any other bus.

You are also given an integer totalTrips, which denotes the number of trips all buses should make in total.
Return the minimum time required for all buses to complete at least totalTrips trips.

Example 1:
Input: time = [1,2,3], totalTrips = 5
Output: 3
Explanation:
- At time t = 1, the number of trips completed by each bus are [1,0,0].
  The total number of trips completed is 1 + 0 + 0 = 1.
- At time t = 2, the number of trips completed by each bus are [2,1,0].
  The total number of trips completed is 2 + 1 + 0 = 3.
- At time t = 3, the number of trips completed by each bus are [3,1,1].
  The total number of trips completed is 3 + 1 + 1 = 5.
So the minimum time needed for all buses to complete at least 5 trips is 3.

Example 2:
Input: time = [2], totalTrips = 1
Output: 2
Explanation:
There is only one bus, and it will complete its first trip at t = 2.
So the minimum time needed to complete 1 trip is 2.

Constraints:
1 <= time.length <= 10^5
1 <= time[i], totalTrips <= 10^7
```

<details><summary>Hint</summary>

```text
1. For a given amount of time, how can we count the total number of trips completed by all buses within that time?
2. Consider using binary search.
```

</details>

</details>

<details><summary>C</summary>

```c
long long minimumTime(int *time, int timeSize, int totalTrips) {
    long long retVal = 0;

    long long minTime = time[0];
    int i;
    for (i = 1; i < timeSize; ++i) {
        minTime = fmin(minTime, time[i]);
    }

    long long tmpTrip = 0;
    long long middle;
    long long left = 1;
    long long right = (long long)totalTrips * minTime;
    while (left < right) {
        middle = left + (right - left) / 2;

        tmpTrip = 0;
        for (i = 0; i < timeSize; ++i) {
            tmpTrip += (middle / time[i]);
        }

        if (tmpTrip < totalTrips) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    retVal = left;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long minimumTime(vector<int>& time, int totalTrips) {
        long long retVal = 0;

        long long left = 1;
        long long right = (long long)totalTrips * (*min_element(time.begin(), time.end()));
        while (left < right) {
            long long middle = left + (right - left) / 2;

            long long tmpTrip = 0;
            for (auto iter : time) {
                tmpTrip += (middle / iter);
            }

            if (tmpTrip < totalTrips) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }
        retVal = left;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minimumTime(self, time: List[int], totalTrips: int) -> int:
        retVal = 0

        left = 0
        right = min(time) * totalTrips
        while left < right:
            middle = left + (right - left) // 2

            tmpTrips = 0
            for iterator in time:
                tmpTrips += (middle//iterator)

            if tmpTrips < totalTrips:
                left = middle + 1
            else:
                right = middle
        retVal = left

        return retVal
```

</details>

## [2226. Maximum Candies Allocated to K Children](https://leetcode.com/problems/maximum-candies-allocated-to-k-children/)  1646

- [Official](https://leetcode.com/problems/maximum-candies-allocated-to-k-children/editorial/)
- [Official](https://leetcode.cn/problems/maximum-candies-allocated-to-k-children/solutions/1398462/mei-ge-xiao-hai-zui-duo-neng-fen-dao-duo-2717/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array candies.
Each element in the array denotes a pile of candies of size candies[i].
You can divide each pile into any number of sub piles, but you cannot merge two piles together.

You are also given an integer k.
You should allocate piles of candies to k children such that each child gets the same number of candies.
Each child can take at most one pile of candies and some piles of candies may go unused.

Return the maximum number of candies each child can get.

Example 1:
Input: candies = [5,8,6], k = 3
Output: 5
Explanation: We can divide candies[1] into 2 piles of size 5 and 3, and candies[2] into 2 piles of size 5 and 1.
We now have five piles of candies of sizes 5, 5, 3, 5, and 1.
We can allocate the 3 piles of size 5 to 3 children. It can be proven that each child cannot receive more than 5 candies.

Example 2:
Input: candies = [2,5], k = 11
Output: 0
Explanation: There are 11 children but only 7 candies in total,
so it is impossible to ensure each child receives at least one candy.
Thus, each child gets no candy and the answer is 0.

Constraints:
1 <= candies.length <= 10^5
1 <= candies[i] <= 10^7
1 <= k <= 10^12
```

<details><summary>Hint</summary>

```text
1. For a fixed number of candies c, how can you check if each child can get c candies?
2. Use binary search to find the maximum c as the answer.
```

</details>

</details>

<details><summary>C</summary>

```c
int maximumCandies(int *candies, int candiesSize, long long k) {
    int retVal = 0;

    int i;

    int maxCandies = candies[0];
    for (i = 1; i < candiesSize; ++i) {
        maxCandies = fmax(maxCandies, candies[i]);
    }

    long long tmpCandies;
    int middle;
    int left = 1;
    int right = 1 + maxCandies;
    while (left < right) {
        middle = left + (right - left) / 2;

        tmpCandies = 0;
        for (i = 0; i < candiesSize; ++i) {
            tmpCandies += (candies[i] / middle);
        }

        if (tmpCandies >= k) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    retVal = left - 1;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maximumCandies(vector<int>& candies, long long k) {
        int retVal = 0;

        int left = 1;
        int right = 1 + (*max_element(candies.begin(), candies.end()));
        while (left < right) {
            int middle = left + (right - left) / 2;

            long long tmpCandies = 0;
            for (auto candy : candies) {
                tmpCandies += (candy / middle);
            }

            if (tmpCandies >= k) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }
        retVal = left - 1;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maximumCandies(self, candies: List[int], k: int) -> int:
        retVal = 0

        left = 1
        right = 1 + max(candies)
        while left < right:
            middle = left + (right - left) // 2

            tmpCandies = 0
            for candy in candies:
                tmpCandies += candy // middle

            if tmpCandies >= k:
                left = middle + 1
            else:
                right = middle
        retVal = left - 1

        return retVal
```

</details>

## [2251. Number of Flowers in Full Bloom](https://leetcode.com/problems/number-of-flowers-in-full-bloom/)  2022

- [Official](https://leetcode.com/problems/number-of-flowers-in-full-bloom/editorial/)
- [Official](https://leetcode.cn/problems/number-of-flowers-in-full-bloom/solutions/2457828/hua-qi-nei-hua-de-shu-mu-by-leetcode-sol-j94l/)

<details><summary>Description</summary>

```text
You are given a 0-indexed 2D integer array flowers,
where flowers[i] = [starti, endi] means the ith flower will be in full bloom from starti to endi (inclusive).
You are also given a 0-indexed integer array people of size n,
where people[i] is the time that the ith person will arrive to see the flowers.

Return an integer array answer of size n,
where answer[i] is the number of flowers that are in full bloom when the ith person arrives.

Example 1:
Input: flowers = [[1,6],[3,7],[9,12],[4,13]], poeple = [2,3,7,11]
Output: [1,2,2,2]
Explanation: The figure above shows the times when the flowers are in full bloom and when the people arrive.
For each person, we return the number of flowers in full bloom during their arrival.

Example 2:
Input: flowers = [[1,10],[3,3]], poeple = [3,3,2]
Output: [2,2,1]
Explanation: The figure above shows the times when the flowers are in full bloom and when the people arrive.
For each person, we return the number of flowers in full bloom during their arrival.

Constraints:
1 <= flowers.length <= 5 * 10^4
flowers[i].length == 2
1 <= starti <= endi <= 10^9
1 <= people.length <= 5 * 10^4
1 <= people[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Notice that for any given time t, the number of flowers blooming at time t is equal to
   the number of flowers that have started blooming minus the number of flowers that have already stopped blooming.
2. We can obtain these values efficiently using binary search.
3. We can store the starting times in sorted order,
   which then allows us to binary search to find how many flowers have started blooming for a given time t.
4. We do the same for the ending times to find how many flowers have stopped blooming at time t.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int binarySearch(int* arr, int left, int right, int val) {
    int retVal = right + 1;

    int middle;
    while (left <= right) {
        middle = left + (right - left) / 2;

        if (arr[middle] > val) {
            retVal = middle;
            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }

    return retVal;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* fullBloomFlowers(int** flowers, int flowersSize, int* flowersColSize, int* people, int peopleSize,
                      int* returnSize) {
    int* pRetVal = NULL;

    int starts[flowersSize];
    memset(starts, 0, sizeof(starts));
    int ends[flowersSize];
    memset(ends, 0, sizeof(ends));
    int i;
    for (i = 0; i < flowersSize; ++i) {
        starts[i] = flowers[i][0];
        ends[i] = flowers[i][1] + 1;
    }
    qsort(starts, flowersSize, sizeof(int), compareInteger);
    qsort(ends, flowersSize, sizeof(int), compareInteger);

    (*returnSize) = 0;
    pRetVal = (int*)malloc(peopleSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    int x, y;
    for (i = 0; i < peopleSize; ++i) {
        x = binarySearch(starts, 0, flowersSize - 1, people[i]);
        y = binarySearch(ends, 0, flowersSize - 1, people[i]);
        pRetVal[i] = x - y;
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
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& people) {
        vector<int> retVal;

        vector<int> starts;
        vector<int> ends;
        for (vector<int>& flower : flowers) {
            starts.push_back(flower[0]);
            ends.push_back(flower[1] + 1);
        }
        sort(starts.begin(), starts.end());
        sort(ends.begin(), ends.end());

        for (int p : people) {
            int i = upper_bound(starts.begin(), starts.end(), p) - starts.begin();
            int j = upper_bound(ends.begin(), ends.end(), p) - ends.begin();
            retVal.push_back(i - j);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def fullBloomFlowers(self, flowers: List[List[int]], people: List[int]) -> List[int]:
        retVal = []

        starts = []
        ends = []
        for start, end in flowers:
            starts.append(start)
            ends.append(end + 1)
        starts.sort()
        ends.sort()

        for p in people:
            i = bisect_right(starts, p)
            j = bisect_right(ends, p)
            retVal.append(i - j)

        return retVal
```

</details>

## [2300. Successful Pairs of Spells and Potions](https://leetcode.com/problems/successful-pairs-of-spells-and-potions/)  1476

<details><summary>Description</summary>

```text
You are given two positive integer arrays spells and potions, of length n and m respectively,
where spells[i] represents the strength of the ith spell and potions[j] represents the strength of the jth potion.

You are also given an integer success.
A spell and potion pair is considered successful if the product of their strengths is at least success.

Return an integer array pairs of length n where pairs[i] is the number of potions
that will form a successful pair with the ith spell.

Example 1:
Input: spells = [5,1,3], potions = [1,2,3,4,5], success = 7
Output: [4,0,3]
Explanation:
- 0th spell: 5 * [1,2,3,4,5] = [5,10,15,20,25]. 4 pairs are successful.
- 1st spell: 1 * [1,2,3,4,5] = [1,2,3,4,5]. 0 pairs are successful.
- 2nd spell: 3 * [1,2,3,4,5] = [3,6,9,12,15]. 3 pairs are successful.
Thus, [4,0,3] is returned.

Example 2:
Input: spells = [3,1,2], potions = [8,5,8], success = 16
Output: [2,0,2]
Explanation:
- 0th spell: 3 * [8,5,8] = [24,15,24]. 2 pairs are successful.
- 1st spell: 1 * [8,5,8] = [8,5,8]. 0 pairs are successful.
- 2nd spell: 2 * [8,5,8] = [16,10,16]. 2 pairs are successful.
Thus, [2,0,2] is returned.

Constraints:
n == spells.length
m == potions.length
1 <= n, m <= 10^5
1 <= spells[i], potions[i] <= 10^5
1 <= success <= 10^10
```

<details><summary>Hint</summary>

```text
1. Notice that if a spell and potion pair is successful, then the spell and all stronger potions will be successful too.
2. Thus, for each spell, we need to find the potion with the least strength that will form a successful pair.
3. We can efficiently do this by sorting the potions based on strength and using binary search.
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
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* successfulPairs(int* spells, int spellsSize, int* potions, int potionsSize, long long success, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = spellsSize;
    pRetVal = (int*)calloc((*returnSize), sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        (*returnSize) = 0;
        return pRetVal;
    }

    qsort(potions, potionsSize, sizeof(int), compareInteger);
    long divisor;
    int left, right, middle;
    int i;
    for (i = 0; i < spellsSize; ++i) {
        divisor = (success + spells[i] - 1) / spells[i];

        left = 0;
        right = potionsSize;
        while (left < right) {
            middle = left + (right - left) / 2;
            if (potions[middle] < divisor) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }

        pRetVal[i] = potionsSize - left;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        vector<int> retVal;

        sort(potions.begin(), potions.end());
        for (auto spell : spells) {
            long divisor = (success + spell - 1) / spell;
            auto iterator = lower_bound(potions.begin(), potions.end(), divisor);
            retVal.emplace_back(potions.end() - iterator);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def successfulPairs(self, spells: List[int], potions: List[int], success: int) -> List[int]:
        retVal = []

        potions.sort()
        for spell in spells:
            divisor = (success + spell - 1) // spell
            iterator = bisect_left(potions, divisor)
            retVal.append(len(potions) - iterator)

        return retVal
```

</details>

## [2389. Longest Subsequence With Limited Sum](https://leetcode.com/problems/longest-subsequence-with-limited-sum/)  1387

- [Official](https://leetcode.com/problems/longest-subsequence-with-limited-sum/solutions/2644327/longest-subsequence-with-limited-sum/)

<details><summary>Description</summary>

```text
You are given an integer array nums of length n, and an integer array queries of length m.

Return an array answer of length m where answer[i] is the maximum size of a subsequence
that you can take from nums such that the sum of its elements is less than or equal to queries[i].

A subsequence is an array that can be derived from another array by deleting some
or no elements without changing the order of the remaining elements.

Example 1:
Input: nums = [4,5,2,1], queries = [3,10,21]
Output: [2,3,4]
Explanation: We answer the queries as follows:
- The subsequence [2,1] has a sum less than or equal to 3.
  It can be proven that 2 is the maximum size of such a subsequence, so answer[0] = 2.
- The subsequence [4,5,1] has a sum less than or equal to 10.
  It can be proven that 3 is the maximum size of such a subsequence, so answer[1] = 3.
- The subsequence [4,5,2,1] has a sum less than or equal to 21.
  It can be proven that 4 is the maximum size of such a subsequence, so answer[2] = 4.

Example 2:
Input: nums = [2,3,4,5], queries = [1]
Output: [0]
Explanation: The empty subsequence is the only subsequence that has a sum less than or equal to 1, so answer[0] = 0.

Constraints:
n == nums.length
m == queries.length
1 <= n, m <= 1000
1 <= nums[i], queries[i] <= 10^6
```

<details><summary>Hint</summary>

```text
1. Solve each query independently.
2. When solving a query, which elements of nums should you choose to make the subsequence as long as possible?
3. Choose the smallest elements in nums that add up to a sum less than the query.
```

</details>

</details>

<details><summary>C</summary>

```c
#define BINARY_SEARCH (1)
#define SORTING (1)
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* answerQueries(int* nums, int numsSize, int* queries, int queriesSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = queriesSize;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));

    qsort(nums, numsSize, sizeof(int), compareInteger);

#if (BINARY_SEARCH)
    printf("BINARY_SEARCH\n");

    int i;

    int prefixSum[numsSize];
    memset(prefixSum, 0, sizeof(prefixSum));
    prefixSum[0] = nums[0];
    for (i = 1; i < numsSize; ++i) {
        prefixSum[i] = nums[i] + prefixSum[i - 1];
    }

    int left, right, middle;
    for (i = 0; i < queriesSize; ++i) {
        left = 0;
        right = numsSize;
        while (left < right) {
            middle = left + (right - left) / 2;
            if (prefixSum[middle] <= queries[i]) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }

        pRetVal[i] = right;
    }

#elif (SORTING)
    printf("SORTING\n");

    int i, j;
    for (i = 0; i < queriesSize; ++i) {
        for (j = 0; j < numsSize; ++j) {
            if (queries[i] < nums[j]) {
                break;
            }
            queries[i] -= nums[j];
            ++pRetVal[i];
        }
    }
#endif

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define BINARY_SEARCH (1)
#define SORTING (1)
   public:
    vector<int> answerQueries(vector<int>& nums, vector<int>& queries) {
        vector<int> retVal;

        sort(nums.begin(), nums.end());
#if (BINARY_SEARCH)
        cout << "BINARY_SEARCH\n";

        int numsSize = nums.size();
        vector<int> prefixSum(numsSize, 0);
        prefixSum[0] = nums[0];
        for (int i = 1; i < numsSize; ++i) {
            prefixSum[i] = nums[i] + prefixSum[i - 1];
        }

        for (auto query : queries) {
            auto iterator = upper_bound(prefixSum.begin(), prefixSum.end(), query);
            retVal.emplace_back(iterator - prefixSum.begin());
        }
#elif (SORTING)
        cout << "SORTING\n";

        for (int query : queries) {
            int count = 0;
            for (int num : nums) {
                query -= num;
                if (query < 0) {
                    break;
                }
                ++count;
            }
            retVal.emplace_back(count);
        }
#endif

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def __init__(self):
        self.method = 1

    def answerQueries(self, nums: List[int], queries: List[int]) -> List[int]:
        retVal = []

        if self.method == 1:
            print("Binary Search")

            nums.sort()
            prefixSum = list(accumulate(nums))
            for query in queries:
                iterator = bisect_right(prefixSum, query)
                retVal.append(iterator)

        elif self.method == 2:
            print("Sorting")

            nums.sort()
            for query in queries:
                count = 0
                for num in nums:
                    query -= num
                    if query < 0:
                        break
                    count += 1
                retVal.append(count)

        return retVal
```

</details>

## [2411. Smallest Subarrays With Maximum Bitwise OR](https://leetcode.com/problems/smallest-subarrays-with-maximum-bitwise-or/)  1938

- [Official](https://leetcode.com/problems/smallest-subarrays-with-maximum-bitwise-or/editorial/)
- [Official](https://leetcode.cn/problems/smallest-subarrays-with-maximum-bitwise-or/solutions/3730081/an-wei-huo-zui-da-de-zui-xiao-zi-shu-zu-v5dt7/)

<details><summary>Description</summary>

```text
You are given a 0-indexed array nums of length n, consisting of non-negative integers.
For each index i from 0 to n - 1, you must determine the size of the minimum sized non-empty subarray of nums
starting at i (inclusive) that has the maximum possible bitwise OR.
- In other words, let Bij be the bitwise OR of the subarray nums[i...j].
  You need to find the smallest subarray starting at i,
  such that bitwise OR of this subarray is equal to max(Bik) where i <= k <= n - 1.

The bitwise OR of an array is the bitwise OR of all the numbers in it.

Return an integer array answer of size n where answer[i] is the length of the minimum sized subarray starting at i
with maximum bitwise OR.

A subarray is a contiguous non-empty sequence of elements within an array.

Example 1:
Input: nums = [1,0,2,1,3]
Output: [3,3,2,2,1]
Explanation:
The maximum possible bitwise OR starting at any index is 3.
- Starting at index 0, the shortest subarray that yields it is [1,0,2].
- Starting at index 1, the shortest subarray that yields the maximum bitwise OR is [0,2,1].
- Starting at index 2, the shortest subarray that yields the maximum bitwise OR is [2,1].
- Starting at index 3, the shortest subarray that yields the maximum bitwise OR is [1,3].
- Starting at index 4, the shortest subarray that yields the maximum bitwise OR is [3].
Therefore, we return [3,3,2,2,1].

Example 2:
Input: nums = [1,2]
Output: [2,1]
Explanation:
Starting at index 0, the shortest subarray that yields the maximum bitwise OR is of length 2.
Starting at index 1, the shortest subarray that yields the maximum bitwise OR is of length 1.
Therefore, we return [2,1].

Constraints:
n == nums.length
1 <= n <= 10^5
0 <= nums[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Consider trying to solve the problem for each bit position separately.
2. For each bit position, find the position of the next number that has a 1 in that position, if any.
3. Take the maximum distance to such a number, including the current number.
4. Iterate backwards to achieve a linear complexity.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MAX_BIT (31)  // 0 <= nums[i] <= 10^9
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* smallestSubarrays(int* nums, int numsSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int*)calloc(numsSize, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }

    int pos[MAX_BIT];
    memset(pos, -1, sizeof(pos));
    for (int i = numsSize - 1; i >= 0; --i) {
        int j = i;
        for (int bit = 0; bit < MAX_BIT; ++bit) {
            if (!(nums[i] & (1 << bit))) {
                if (pos[bit] != -1) {
                    j = fmax(j, pos[bit]);
                }
            } else {
                pos[bit] = i;
            }
        }
        pRetVal[i] = j - i + 1;
    }
    (*returnSize) = numsSize;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    int maxBit = 31;  // 0 <= nums[i] <= 10^9

   public:
    vector<int> smallestSubarrays(vector<int>& nums) {
        vector<int> retVal;

        int numsSize = nums.size();

        retVal.resize(numsSize, 0);
        vector<int> pos(maxBit, -1);
        for (int i = numsSize - 1; i >= 0; --i) {
            int j = i;
            for (int bit = 0; bit < maxBit; ++bit) {
                if (!(nums[i] & (1 << bit))) {
                    if (pos[bit] != -1) {
                        j = max(j, pos[bit]);
                    }
                } else {
                    pos[bit] = i;
                }
            }
            retVal[i] = j - i + 1;
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
        self.maxBit = 31  # 0 <= nums[i] <= 10^9

    def smallestSubarrays(self, nums: List[int]) -> List[int]:
        retVal = []

        numSize = len(nums)

        retVal = [0] * numSize
        pos = [-1] * self.maxBit
        for i in range(numSize - 1, -1, -1):
            j = i
            for bit in range(self.maxBit):
                if (nums[i] & (1 << bit)) == 0:
                    if pos[bit] != -1:
                        j = max(j, pos[bit])
                else:
                    pos[bit] = i
            retVal[i] = j - i + 1

        return retVal
```

</details>

## [2439. Minimize Maximum of Array](https://leetcode.com/problems/minimize-maximum-of-array/)  1965

<details><summary>Description</summary>

```text
You are given a 0-indexed array nums comprising of n non-negative integers.

In one operation, you must:
- Choose an integer i such that 1 <= i < n and nums[i] > 0.
- Decrease nums[i] by 1.
- Increase nums[i - 1] by 1.

Return the minimum possible value of the maximum integer of nums after performing any number of operations.

Example 1:
Input: nums = [3,7,1,6]
Output: 5
Explanation:
One set of optimal operations is as follows:
1. Choose i = 1, and nums becomes [4,6,1,6].
2. Choose i = 3, and nums becomes [4,6,2,5].
3. Choose i = 1, and nums becomes [5,5,2,5].
The maximum integer of nums is 5. It can be shown that the maximum number cannot be less than 5.
Therefore, we return 5.

Example 2:
Input: nums = [10,1]
Output: 10
Explanation:
It is optimal to leave nums as is, and since 10 is the maximum value, we return 10.

Constraints:
n == nums.length
2 <= n <= 10^5
0 <= nums[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Try a binary search approach.
2. Perform a binary search over the minimum value that can be achieved for the maximum number of the array.
3. In each binary search iteration, iterate through the array backwards,
   greedily decreasing the current element until it is within the limit.
```

</details>

</details>

<details><summary>C</summary>

```c
#define BINARY_SEARCH (1)
#define AVERAGE (1)
int minimizeArrayValue(int *nums, int numsSize) {
    int retVal = 0;

#if (BINARY_SEARCH)
    printf("BINARY_SEARCH\n");

    int i;

    int maxValue = 0;
    for (i = 0; i < numsSize; ++i) {
        maxValue = fmax(maxValue, nums[i]);
    }

    bool operationFlag;
    /* use long to avoid signed integer overflow
     *  n == nums.length
     *  2 <= n <= 10^5
     *  0 <= nums[i] <= 10^9
     */
    long operation;
    int left = 0;
    int right = maxValue;
    int middle;
    while (left < right) {
        middle = left + (right - left) / 2;

        operationFlag = true;
        operation = 0;
        for (i = 0; i < numsSize; ++i) {
            if (nums[i] <= middle) {
                operation += (middle - nums[i]);
                continue;
            }

            if (operation < (nums[i] - middle)) {
                operationFlag = false;
                break;
            }

            operation -= (nums[i] - middle);
        }

        if (operationFlag == false) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    retVal = left;

#elif (AVERAGE)
    printf("AVERAGE\n");

    // https://leetcode.com/problems/minimize-maximum-of-array/solutions/2706521/java-c-python-prefix-sum-average-o-n/
    int prefixSumSize = numsSize;
    /* use long to avoid signed integer overflow
     *  n == nums.length
     *  2 <= n <= 10^5
     *  0 <= nums[i] <= 10^9
     */
    long prefixSum[prefixSumSize];
    memset(prefixSum, 0, sizeof(prefixSum));
    prefixSum[0] = nums[0];

    int i;
    for (i = 1; i < prefixSumSize; ++i) {
        prefixSum[i] = nums[i] + prefixSum[i - 1];
    }

    for (i = 0; i < prefixSumSize; ++i) {
        retVal = fmax((long)retVal, ((prefixSum[i] + i) / (i + 1)));
    }
#endif

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define BINARY_SEARCH (1)
#define AVERAGE (1)
   public:
    int minimizeArrayValue(vector<int>& nums) {
        int retVal = 0;

#if (BINARY_SEARCH)
        cout << "BINARY_SEARCH\n";

        int left = 0;
        int right = *max_element(nums.begin(), nums.end());
        while (left < right) {
            int middle = left + (right - left) / 2;

            bool operationFlag = true;
            /* use long to avoid signed integer overflow
             *  n == nums.length
             *  2 <= n <= 10^5
             *  0 <= nums[i] <= 10^9
             */
            long operation = 0;
            for (auto num : nums) {
                if (num <= middle) {
                    operation += (middle - num);
                    continue;
                }

                if (operation < (num - middle)) {
                    operationFlag = false;
                    break;
                }

                operation -= (num - middle);
            }

            if (operationFlag == false) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }
        retVal = left;

#elif (AVERAGE)
        cout << "AVERAGE\n";

        // https://leetcode.com/problems/minimize-maximum-of-array/solutions/2706521/java-c-python-prefix-sum-average-o-n/
        int prefixSumSize = nums.size();
        /* use long to avoid signed integer overflow
         *  n == nums.length
         *  2 <= n <= 10^5
         *  0 <= nums[i] <= 10^9
         */
        vector<long> prefixSum(prefixSumSize, 0);

        prefixSum[0] = nums[0];
        for (int i = 1; i < prefixSumSize; ++i) {
            prefixSum[i] = nums[i] + prefixSum[i - 1];
        }

        for (int i = 0; i < prefixSumSize; ++i) {
            retVal = max((long)retVal, ((prefixSum[i] + i) / (i + 1)));
        }
#endif

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def __init__(self):
        self.method = 1

    def minimizeArrayValue(self, nums: List[int]) -> int:
        retVal = 0

        if self.method == 1:
            print("Binary Search")

            left = 0
            right = max(nums)
            while left < right:
                middle = left + (right - left) // 2

                operationFlag = True
                operation = 0
                for num in nums:
                    if num <= middle:
                        operation += (middle - num)
                        continue

                    if operation < (num - middle):
                        operationFlag = False
                        break
                    operation -= (num - middle)

                if operationFlag == False:
                    left = middle + 1
                else:
                    right = middle
            retVal = left
        elif self.method == 2:
            print("Average")

            # https://leetcode.com/problems/minimize-maximum-of-array/solutions/2706521/java-c-python-prefix-sum-average-o-n/
            prefixSum = list(accumulate(nums))
            prefixSumSize = len(prefixSum)
            for i in range(prefixSumSize):
                retVal = max(retVal, ((prefixSum[i] + i) // (i + 1)))

        return retVal
```

</details>

## [2448. Minimum Cost to Make Array Equal](https://leetcode.com/problems/minimum-cost-to-make-array-equal/)  2005

- [Official](https://leetcode.com/problems/minimum-cost-to-make-array-equal/editorial/)

<details><summary>Description</summary>

```text
You are given two 0-indexed arrays nums and cost consisting each of n positive integers.

You can do the following operation any number of times:
- Increase or decrease any element of the array nums by 1.

The cost of doing one operation on the ith element is cost[i].

Return the minimum total cost such that all the elements of the array nums become equal.

Example 1:
Input: nums = [1,3,5,2], cost = [2,3,1,14]
Output: 8
Explanation: We can make all the elements equal to 2 in the following way:
- Increase the 0th element one time. The cost is 2.
- Decrease the 1st element one time. The cost is 3.
- Decrease the 2nd element three times. The cost is 1 + 1 + 1 = 3.
The total cost is 2 + 3 + 3 = 8.
It can be shown that we cannot make the array equal with a smaller cost.

Example 2:
Input: nums = [2,2,2,2,2], cost = [4,2,8,1,3]
Output: 0
Explanation: All the elements are already equal, so no operations are needed.

Constraints:
n == nums.length == cost.length
1 <= n <= 10^5
1 <= nums[i], cost[i] <= 10^6
```

<details><summary>Hint</summary>

```text
1. Changing the elements into one of the numbers already existing in the array nums is optimal.
2. Try finding the cost of changing the array into each element, and return the minimum value.
```

</details>

</details>

<details><summary>C</summary>

```c
long long getCost(int base, int* nums, int numsSize, int* cost, int costSize) {
    long long retVal = 0;

    int i;
    for (i = 0; i < numsSize; ++i) {
        retVal += ((long long)(abs(base - nums[i])) * cost[i]);
    }

    return retVal;
}
long long minCost(int* nums, int numsSize, int* cost, int costSize) {
    long long retVal = 0;

    retVal = getCost(nums[0], nums, numsSize, cost, costSize);
    int left = nums[0];
    int right = nums[0];
    int i;
    for (i = 0; i < numsSize; ++i) {
        left = (left < nums[i]) ? (left) : (nums[i]);
        right = (right > nums[i]) ? (right) : (nums[i]);
    }

    int middle;
    long long costLeft, costRight;
    while (left < right) {
        middle = (left + right) / 2;

        costLeft = getCost(middle, nums, numsSize, cost, costSize);
        costRight = getCost((middle + 1), nums, numsSize, cost, costSize);
        retVal = fmin(costLeft, costRight);

        if (costLeft > costRight) {
            left = middle + 1;
        } else {
            right = middle;
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
    long long getCost(int base, vector<int>& nums, vector<int>& cost) {
        long long retVal = 0;

        int numsSize = nums.size();
        for (int i = 0; i < numsSize; ++i) {
            retVal += ((long long)(abs(base - nums[i])) * cost[i]);
        }

        return retVal;
    }
    long long minCost(vector<int>& nums, vector<int>& cost) {
        long long retVal = 0;

        retVal = getCost(nums[0], nums, cost);
        int left = *min_element(nums.begin(), nums.end());
        int right = *max_element(nums.begin(), nums.end());

        while (left < right) {
            int middle = (left + right) / 2;

            long long costLeft = getCost(middle, nums, cost);
            long long costRight = getCost((middle + 1), nums, cost);
            retVal = min(costLeft, costRight);

            if (costLeft > costRight) {
                left = middle + 1;
            } else {
                right = middle;
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
    def getCost(self, base: int, nums: List[int], cost: List[int]) -> int:
        retVal = 0

        retVal = sum(abs(base - num) * c for num, c in zip(nums, cost))

        return retVal

    def minCost(self, nums: List[int], cost: List[int]) -> int:
        retVal = 0

        retVal = self.getCost(nums[0], nums, cost)
        left = min(nums)
        right = max(nums)
        while left < right:
            middle = (left + right) // 2

            costLeft = self.getCost(middle, nums, cost)
            costRight = self.getCost((middle + 1), nums, cost)
            retVal = min(costLeft, costRight)

            if costLeft > costRight:
                left = middle + 1
            else:
                right = middle

        return retVal
```

</details>

## [2528. Maximize the Minimum Powered City](https://leetcode.com/problems/maximize-the-minimum-powered-city/)  2236

- [Official](https://leetcode.com/problems/maximize-the-minimum-powered-city/editorial/)
- [Official](https://leetcode.cn/problems/maximize-the-minimum-powered-city/solutions/3813498/zui-da-hua-cheng-shi-de-zui-xiao-dian-li-94lq/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array stations of length n,
where stations[i] represents the number of power stations in the ith city.

Each power station can provide power to every city in a fixed range.
In other words, if the range is denoted by r,
then a power station at city i can provide power to all cities j such that |i - j| <= r and 0 <= i, j <= n - 1.
- Note that |x| denotes absolute value. For example, |7 - 5| = 2 and |3 - 10| = 7.

The power of a city is the total number of power stations it is being provided power from.

The government has sanctioned building k more power stations, each of which can be built in any city,
and have the same range as the pre-existing ones.

Given the two integers r and k,
return the maximum possible minimum power of a city, if the additional power stations are built optimally.

Note that you can build the k power stations in multiple cities.

Example 1:
Input: stations = [1,2,4,5,0], r = 1, k = 2
Output: 5
Explanation:
One of the optimal ways is to install both the power stations at city 1.
So stations will become [1,4,4,5,0].
- City 0 is provided by 1 + 4 = 5 power stations.
- City 1 is provided by 1 + 4 + 4 = 9 power stations.
- City 2 is provided by 4 + 4 + 5 = 13 power stations.
- City 3 is provided by 5 + 4 = 9 power stations.
- City 4 is provided by 5 + 0 = 5 power stations.
So the minimum power of a city is 5.
Since it is not possible to obtain a larger power, we return 5.

Example 2:
Input: stations = [4,4,4,4], r = 0, k = 3
Output: 4
Explanation:
It can be proved that we cannot make the minimum power of a city greater than 4.

Constraints:
n == stations.length
1 <= n <= 10^5
0 <= stations[i] <= 10^5
0 <= r <= n - 1
0 <= k <= 10^9
```

<details><summary>Hint</summary>

```text
1. Pre calculate the number of stations on each city using Line Sweep.
2. Use binary search to maximize the minimum.
```

</details>

</details>

<details><summary>C</summary>

```c
bool check(int r, long long k, long long val, long long* cnt, int stationsSize) {
    bool retVal = true;

    long long* diff = (long long*)malloc((stationsSize + 1) * sizeof(long long));
    if (diff == NULL) {
        perror("malloc");
        retVal = false;
        return retVal;
    }
    memcpy(diff, cnt, (stationsSize + 1) * sizeof(long long));

    long long sum = 0;
    long long add;
    long long remaining = k;
    int end;
    for (int i = 0; i < stationsSize; i++) {
        sum += diff[i];
        if (sum >= val) {
            continue;
        }

        add = val - sum;
        if (remaining < add) {
            retVal = false;
            break;
        }

        remaining -= add;
        end = fmin(stationsSize, i + 2 * r + 1);
        diff[end] -= add;
        sum += add;
    }

    //
    free(diff);

    return retVal;
}
long long maxPower(int* stations, int stationsSize, int r, int k) {
    long long retVal = 0;

    long long* cnt = (long long*)calloc(stationsSize + 1, sizeof(long long));
    if (cnt == NULL) {
        perror("calloc");
        return retVal;
    }
    int left, right;
    for (int i = 0; i < stationsSize; i++) {
        left = fmax(0, i - r);
        right = fmin(stationsSize, i + r + 1);
        cnt[left] += stations[i];
        cnt[right] -= stations[i];
    }

    long long minVal = LLONG_MAX;
    long long sumTotal = 0;
    for (int i = 0; i < stationsSize; i++) {
        if (stations[i] < minVal) {
            minVal = stations[i];
        }
        sumTotal += stations[i];
    }
    long long middle;
    long long high = sumTotal + k;
    long long low = minVal;
    while (low <= high) {
        middle = low + (high - low) / 2;
        if (check(r, k, middle, cnt, stationsSize) == true) {
            retVal = middle;
            low = middle + 1;
        } else {
            high = middle - 1;
        }
    }

    //
    free(cnt);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    bool check(int r, int k, long long val, vector<long long>& cnt, int stationsSize) {
        bool retVal = true;

        vector<long long> diff = cnt;
        long long sum = 0;
        long long remaining = k;
        for (int i = 0; i < stationsSize; i++) {
            sum += diff[i];
            if (sum >= val) {
                continue;
            }

            long long add = val - sum;
            if (remaining < add) {
                retVal = false;
                break;
            }

            remaining -= add;
            int end = min(stationsSize, i + 2 * r + 1);
            diff[end] -= add;
            sum += add;
        }

        return retVal;
    };

   public:
    long long maxPower(vector<int>& stations, int r, int k) {
        long long retVal = 0;

        int stationsSize = stations.size();

        vector<long long> cnt(stationsSize + 1);
        for (int i = 0; i < stationsSize; i++) {
            int left = max(0, i - r);
            int right = min(stationsSize, i + r + 1);
            cnt[left] += stations[i];
            cnt[right] -= stations[i];
        }

        long long low = *min_element(cnt.begin(), cnt.end());
        long long high = accumulate(stations.begin(), stations.end(), 0LL) + k;
        while (low <= high) {
            long long middle = low + (high - low) / 2;
            if (check(r, k, middle, cnt, stationsSize) == true) {
                retVal = middle;
                low = middle + 1;
            } else {
                high = middle - 1;
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
    def check(self, r: int, k: int, val: int, cnt: List[int], stationsSize: int) -> bool:
        retVal = True

        diff = cnt.copy()
        total = 0
        remaining = k
        for i in range(stationsSize):
            total += diff[i]
            if total >= val:
                continue

            add = val - total
            if remaining < add:
                retVal = False
                break

            remaining -= add
            end = min(stationsSize, i + 2 * r + 1)
            diff[end] -= add
            total += add

        return retVal

    def maxPower(self, stations: List[int], r: int, k: int) -> int:
        retVal = 0

        stationsSize = len(stations)

        cnt = [0] * (stationsSize + 1)
        for i in range(stationsSize):
            left = max(0, i - r)
            right = min(stationsSize, i + r + 1)
            cnt[left] += stations[i]
            cnt[right] -= stations[i]

        low = min(stations)
        high = sum(stations) + k
        while low <= high:
            middle = (low + high) // 2
            if self.check(r, k, middle, cnt, stationsSize):
                retVal = middle
                low = middle + 1
            else:
                high = middle - 1

        return retVal
```

</details>

## [2560. House Robber IV](https://leetcode.com/problems/house-robber-iv/)  2081

- [Official](https://leetcode.com/problems/house-robber-iv/editorial/)
- [Official](https://leetcode.cn/problems/house-robber-iv/solutions/2441849/da-jia-jie-she-iv-by-leetcode-solution-n93j/)

<details><summary>Description</summary>

```text
There are several consecutive houses along a street, each of which has some money inside.
There is also a robber, who wants to steal money from the homes, but he refuses to steal from adjacent homes.

The capability of the robber is the maximum amount of money he steals from one house of all the houses he robbed.

You are given an integer array nums representing how much money is stashed in each house.
More formally, the ith house from the left has nums[i] dollars.

You are also given an integer k, representing the minimum number of houses the robber will steal from.
It is always possible to steal at least k houses.

Return the minimum capability of the robber out of all the possible ways to steal at least k houses.

Example 1:
Input: nums = [2,3,5,9], k = 2
Output: 5
Explanation:
There are three ways to rob at least 2 houses:
- Rob the houses at indices 0 and 2. Capability is max(nums[0], nums[2]) = 5.
- Rob the houses at indices 0 and 3. Capability is max(nums[0], nums[3]) = 9.
- Rob the houses at indices 1 and 3. Capability is max(nums[1], nums[3]) = 9.
Therefore, we return min(5, 9, 9) = 5.

Example 2:
Input: nums = [2,7,9,3,1], k = 2
Output: 2
Explanation:
There are 7 ways to rob the houses. The way which leads to minimum capability is to rob the house at index 0 and 4.
Return max(nums[0], nums[4]) = 2.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
1 <= k <= (nums.length + 1)/2
```

<details><summary>Hint</summary>

```text
1. Can we use binary search to find the minimum value of a non-contiguous subsequence of a given size k?
2. Initialize the search range with the minimum and maximum elements of the input array.
3. Use a check function to determine if it is possible to select k non-consecutive elements
   that are less than or equal to the current "guess" value.
4. Adjust the search range based on the outcome of the check function,
   until the range converges and the minimum value is found.
```

</details>

</details>

<details><summary>C</summary>

```c
int minCapability(int* nums, int numsSize, int k) {
    int retVal = 0;

    int maxNum = nums[0];
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i] > maxNum) {
            maxNum = nums[i];
        }
    }

    int possibleThefts;
    int totalHouses = numsSize;
    int middle;
    int left = 1;
    int right = maxNum;
    while (left < right) {
        middle = (left + right) / 2;
        possibleThefts = 0;

        for (int index = 0; index < totalHouses; ++index) {
            if (nums[index] <= middle) {
                possibleThefts += 1;
                index++;  // Skip the next house to maintain the non-adjacent condition
            }
        }

        if (possibleThefts >= k) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }
    retVal = left;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minCapability(vector<int>& nums, int k) {
        int retVal = 0;

        int totalHouses = nums.size();
        int left = 1;
        int right = *max_element(nums.begin(), nums.end());
        while (left < right) {
            int middle = (left + right) / 2;
            int possibleThefts = 0;

            for (int index = 0; index < totalHouses; ++index) {
                if (nums[index] <= middle) {
                    possibleThefts += 1;
                    index++;  // Skip the next house to maintain the non-adjacent condition
                }
            }

            if (possibleThefts >= k) {
                right = middle;
            } else {
                left = middle + 1;
            }
        }
        retVal = left;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minCapability(self, nums: List[int], k: int) -> int:
        retVal = 0

        totalHouses = len(nums)
        left = 1
        right = max(nums)
        while left < right:
            middle = (left + right) // 2
            possibleThefts = 0

            index = 0
            while index < totalHouses:
                if nums[index] <= middle:
                    possibleThefts += 1
                    index += 2  # Skip the next house to maintain the non-adjacent condition
                else:
                    index += 1

            if possibleThefts >= k:
                right = middle
            else:
                left = middle + 1
        retVal = left

        return retVal
```

</details>

## [2594. Minimum Time to Repair Cars](https://leetcode.com/problems/minimum-time-to-repair-cars/)  1915

- [Official](https://leetcode.com/problems/minimum-time-to-repair-cars/editorial/)
- [Official](https://leetcode.cn/problems/minimum-time-to-repair-cars/solutions/2425409/xiu-che-de-zui-shao-shi-jian-by-leetcode-if20/)

<details><summary>Description</summary>

```text
You are given an integer array ranks representing the ranks of some mechanics. ranksi is the rank of the ith mechanic.
A mechanic with a rank r can repair n cars in r * n^2 minutes.

You are also given an integer cars representing the total number of cars waiting in the garage to be repaired.

Return the minimum time taken to repair all the cars.

Note: All the mechanics can repair the cars simultaneously.

Example 1:
Input: ranks = [4,2,3,1], cars = 10
Output: 16
Explanation:
- The first mechanic will repair two cars. The time required is 4 * 2 * 2 = 16 minutes.
- The second mechanic will repair two cars. The time required is 2 * 2 * 2 = 8 minutes.
- The third mechanic will repair two cars. The time required is 3 * 2 * 2 = 12 minutes.
- The fourth mechanic will repair four cars. The time required is 1 * 4 * 4 = 16 minutes.
It can be proved that the cars cannot be repaired in less than 16 minutes.​​​​​

Example 2:
Input: ranks = [5,1,8], cars = 6
Output: 16
Explanation:
- The first mechanic will repair one car. The time required is 5 * 1 * 1 = 5 minutes.
- The second mechanic will repair four cars. The time required is 1 * 4 * 4 = 16 minutes.
- The third mechanic will repair one car. The time required is 8 * 1 * 1 = 8 minutes.
It can be proved that the cars cannot be repaired in less than 16 minutes.​​​​​

Constraints:
1 <= ranks.length <= 10^5
1 <= ranks[i] <= 100
1 <= cars <= 10^6
```

<details><summary>Hint</summary>

```text
1. For a predefined fixed time, can all the cars be repaired?
2. Try using binary search on the answer.
```

</details>

</details>

<details><summary>C</summary>

```c
long long repairCars(int* ranks, int ranksSize, int cars) {
    long long retVal = 0;

    // The minimum possible time is 1
    // The maximum possible time is when the slowest mechanic (highest rank) repairs all cars
    long long left = 1;
    long long right = 1LL * cars * cars * ranks[0];
    while (left < right) {
        long long middle = left + (right - left) / 2;

        // Calculate the number of cars that can be repaired in 'middle' time by all mechanics.
        long long carsRepaired = 0;
        for (int i = 0; i < ranksSize; ++i) {
            carsRepaired += sqrt(1.0 * middle / ranks[i]);
        }

        // If the total cars repaired is less than required, increase the time. Otherwise, try a smaller time.
        if (carsRepaired < cars) {
            left = middle + 1;

        } else {
            right = middle;
        }
    }
    retVal = left;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long repairCars(vector<int>& ranks, int cars) {
        long long retVal = 0;

        // The minimum possible time is 1
        // The maximum possible time is when the slowest mechanic (highest rank) repairs all cars
        long long left = 1;
        long long right = 1LL * cars * cars * ranks[0];
        while (left < right) {
            long long middle = left + (right - left) / 2;

            // Calculate the number of cars that can be repaired in 'middle' time by all mechanics.
            long long carsRepaired = 0;
            for (auto rank : ranks) {
                carsRepaired += sqrt(1.0 * middle / rank);
            }

            // If the total cars repaired is less than required, increase the time. Otherwise, try a smaller time.
            if (carsRepaired < cars) {
                left = middle + 1;

            } else {
                right = middle;
            }
        }
        retVal = left;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def repairCars(self, ranks: List[int], cars: int) -> int:
        retVal = 0

        # The minimum possible time is 1
        # The maximum possible time is when the slowest mechanic (highest rank) repairs all cars
        left = 1
        right = cars * cars * ranks[0]
        while left < right:
            middle = (left + right) // 2

            carsRepaired = sum(int((middle / rank) ** 0.5) for rank in ranks)

            # If the total cars repaired is less than required, increase the time.  Otherwise, try a smaller time.
            if carsRepaired < cars:
                left = middle + 1
            else:
                right = middle
        retVal = left

        return retVal
```

</details>

## [2616. Minimize the Maximum Difference of Pairs](https://leetcode.com/problems/minimize-the-maximum-difference-of-pairs/)  2155

- [Official](https://leetcode.com/problems/minimize-the-maximum-difference-of-pairs/editorial/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array nums and an integer p.
Find p pairs of indices of nums such that the maximum difference amongst all the pairs is minimized.
Also, ensure no index appears more than once amongst the p pairs.

Note that for a pair of elements at the index i and j,
the difference of this pair is |nums[i] - nums[j]|, where |x| represents the absolute value of x.

Return the minimum maximum difference among all p pairs. We define the maximum of an empty set to be zero.

Example 1:
Input: nums = [10,1,2,7,1,3], p = 2
Output: 1
Explanation: The first pair is formed from the indices 1 and 4, and the second pair is formed from the indices 2 and 5.
The maximum difference is max(|nums[1] - nums[4]|, |nums[2] - nums[5]|) = max(0, 1) = 1. Therefore, we return 1.

Example 2:
Input: nums = [4,2,1,2], p = 1
Output: 0
Explanation: Let the indices 1 and 3 form a pair.
The difference of that pair is |2 - 2| = 0, which is the minimum we can attain.

Constraints:
1 <= nums.length <= 10^5
0 <= nums[i] <= 10^9
0 <= p <= (nums.length)/2
```

<details><summary>Hint</summary>

```text
1. Can we use dynamic programming here?
2. To minimize the answer, the array should be sorted first.
3. The recurrence relation is fn(i, x) = min(fn(i+1, x), max(abs(nums[i]-nums[i+1]), fn(i+2, p-1)),
   and fn(0,p) gives the desired answer.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int countValidPairs(int* nums, int numsSize, int threshold) {
    int retVal = 0;

    int index = 0;
    while (index < numsSize - 1) {
        // If a valid pair is found, skip both numbers.
        if (nums[index + 1] - nums[index] <= threshold) {
            retVal += 1;
            index += 1;
        }
        index += 1;
    }

    return retVal;
}
int minimizeMax(int* nums, int numsSize, int p) {
    int retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int middle;
    int left = 0;
    int right = nums[numsSize - 1] - nums[0];
    while (left < right) {
        middle = left + (right - left) / 2;
        // If there are enough pairs, look for a smaller threshold.Otherwise, look for a larger threshold.
        if (countValidPairs(nums, numsSize, middle) >= p) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }
    retVal = left;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int countValidPairs(vector<int>& nums, int threshold) {
        int retVal = 0;

        int index = 0;
        int numsSize = nums.size();
        while (index < numsSize - 1) {
            // If a valid pair is found, skip both numbers.
            if (nums[index + 1] - nums[index] <= threshold) {
                retVal += 1;
                index += 1;
            }
            index += 1;
        }

        return retVal;
    }
    int minimizeMax(vector<int>& nums, int p) {
        int retVal = 0;

        sort(nums.begin(), nums.end());

        int numsSize = nums.size();
        int left = 0;
        int right = nums[numsSize - 1] - nums[0];
        while (left < right) {
            int middle = left + (right - left) / 2;
            // If there are enough pairs, look for a smaller threshold.Otherwise, look for a larger threshold.
            if (countValidPairs(nums, middle) >= p) {
                right = middle;
            } else {
                left = middle + 1;
            }
        }
        retVal = left;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def countValidPairs(self, nums: List[int], threshold) -> int:
        retVal = 0

        index = 0
        numsSize = len(nums)
        while index < numsSize - 1:
            # If a valid pair is found, skip both numbers.
            if nums[index + 1] - nums[index] <= threshold:
                retVal += 1
                index += 1
            index += 1

        return retVal

    def minimizeMax(self, nums: List[int], p: int) -> int:
        retVal = 0

        nums.sort()

        left = 0
        right = nums[-1] - nums[0]
        while left < right:
            middle = left + (right - left) // 2
            # If there are enough pairs, look for a smaller threshold. Otherwise, look for a larger threshold.
            if self.countValidPairs(nums, middle) >= p:
                right = middle
            else:
                left = middle + 1
        retVal = left

        return retVal
```

</details>

## [2940. Find Building Where Alice and Bob Can Meet](https://leetcode.com/problems/find-building-where-alice-and-bob-can-meet/)  2327

- [Official](https://leetcode.com/problems/find-building-where-alice-and-bob-can-meet/editorial/)
- [Official](https://leetcode.cn/problems/find-building-where-alice-and-bob-can-meet/solutions/2872957/zhao-dao-alice-he-bob-ke-yi-xiang-yu-de-x5i0t/)

<details><summary>Description</summary>

```text
You are given a 0-indexed array heights of positive integers,
where heights[i] represents the height of the ith building.

If a person is in building i, they can move to any other building j if and only if i < j and heights[i] < heights[j].

You are also given another array queries where queries[i] = [ai, bi].
On the ith query, Alice is in building ai while Bob is in building bi.

Return an array ans where ans[i] is the index of the leftmost building where Alice and Bob can meet on the ith query.
If Alice and Bob cannot move to a common building on query i, set ans[i] to -1.

Example 1:
Input: heights = [6,4,8,5,2,7], queries = [[0,1],[0,3],[2,4],[3,4],[2,2]]
Output: [2,5,-1,5,2]
Explanation:
In the first query, Alice and Bob can move to building 2 since heights[0] < heights[2] and heights[1] < heights[2].
In the second query, Alice and Bob can move to building 5 since heights[0] < heights[5] and heights[3] < heights[5].
In the third query, Alice cannot meet Bob since Alice cannot move to any other building.
In the fourth query, Alice and Bob can move to building 5 since heights[3] < heights[5] and heights[4] < heights[5].
In the fifth query, Alice and Bob are already in the same building.
For ans[i] != -1, It can be shown that ans[i] is the leftmost building where Alice and Bob can meet.
For ans[i] == -1, It can be shown that there is no building where Alice and Bob can meet.

Example 2:
Input: heights = [5,3,8,2,6,1,4,6], queries = [[0,7],[3,5],[5,2],[3,0],[1,6]]
Output: [7,6,-1,4,6]
Explanation:
In the first query, Alice can directly move to Bob's building since heights[0] < heights[7].
In the second query, Alice and Bob can move to building 6 since heights[3] < heights[6] and heights[5] < heights[6].
In the third query, Alice cannot meet Bob since Bob cannot move to any other building.
In the fourth query, Alice and Bob can move to building 4 since heights[3] < heights[4] and heights[0] < heights[4].
In the fifth query, Alice can directly move to Bob's building since heights[1] < heights[6].
For ans[i] != -1, It can be shown that ans[i] is the leftmost building where Alice and Bob can meet.
For ans[i] == -1, It can be shown that there is no building where Alice and Bob can meet.

Constraints:
1 <= heights.length <= 5 * 10^4
1 <= heights[i] <= 10^9
1 <= queries.length <= 5 * 10^4
queries[i] = [ai, bi]
0 <= ai, bi <= heights.length - 1
```

<details><summary>Hint</summary>

```text
1. For each query [x, y], if x > y, swap x and y. Now, we can assume that x <= y.
2. For each query [x, y], if x == y or heights[x] < heights[y], then the answer is y since x ≤ y.
3. Otherwise, we need to find the smallest index t such that y < t and heights[x] < heights[t].
   Note that heights[y] <= heights[x], so heights[x] < heights[t] is a sufficient condition.
4. To find index t for each query, sort the queries in descending order of y.
   Iterate over the queries while maintaining a monotonic stack which we can binary search over to find index t.
```

</details>

</details>

<details><summary>C</summary>

```c
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* leftmostBuildingQueries(int* heights, int heightsSize, int** queries, int queriesSize, int* queriesColSize,
                             int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    //
    pRetVal = (int*)malloc(queriesSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (queriesSize * sizeof(int)));
    (*returnSize) = queriesSize;

    //
    int querySize[heightsSize];
    memset(querySize, 0, sizeof(querySize));
    for (int i = 0; i < queriesSize; i++) {
        int a = queries[i][0];
        int b = queries[i][1];
        if (a > b) {
            swap(&a, &b);
        }

        if ((a == b) || (heights[a] < heights[b])) {
            pRetVal[i] = b;
            continue;
        }

        querySize[b]++;
    }

    //
    struct Pair {
        int first;
        int second;
    };
    struct Pair* newQueries[heightsSize];
    for (int i = 0; i < heightsSize; i++) {
        newQueries[i] = (struct Pair*)malloc(querySize[i] * sizeof(struct Pair));
    }
    int newQueriesIdx[heightsSize];
    memset(newQueriesIdx, 0, sizeof(newQueriesIdx));
    for (int i = 0; i < queriesSize; i++) {
        int a = queries[i][0];
        int b = queries[i][1];
        if (a > b) {
            swap(&a, &b);
        }

        if (!((a == b) || (heights[a] < heights[b]))) {
            newQueries[b][newQueriesIdx[b]].first = i;
            newQueries[b][newQueriesIdx[b]].second = heights[a];
            newQueriesIdx[b]++;
        }
    }

    //
    int monoStackTop = -1;
    int* monoStack = (int*)malloc(heightsSize * sizeof(int));
    for (int i = heightsSize - 1; i >= 0; i--) {
        for (int j = 0; j < querySize[i]; j++) {
            int q = newQueries[i][j].first;
            int val = newQueries[i][j].second;
            if ((monoStackTop == -1) || (heights[monoStack[0]] <= val)) {
                pRetVal[q] = -1;
                continue;
            }

            int left = 0;
            int right = monoStackTop;
            while (left <= right) {
                int middle = (left + right) / 2;
                if (heights[monoStack[middle]] > val) {
                    left = middle + 1;
                } else {
                    right = middle - 1;
                }
            }
            pRetVal[q] = monoStack[right];
        }

        while ((monoStackTop >= 0) && (heights[monoStack[monoStackTop]] <= heights[i])) {
            monoStackTop--;
        }

        monoStack[++monoStackTop] = i;
    }

    //
    free(monoStack);
    for (int i = 0; i < heightsSize; i++) {
        free(newQueries[i]);
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    int search(int height, vector<pair<int, int>>& monoStack) {
        int retVal = -1;

        int left = 0;
        int right = monoStack.size() - 1;
        while (left <= right) {
            int middle = (left + right) / 2;
            if (monoStack[middle].first > height) {
                retVal = max(retVal, middle);
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }

        return retVal;
    }

   public:
    vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries) {
        vector<int> retVal;

        int queriesSize = queries.size();
        retVal.assign(queriesSize, -1);

        int heightsSize = heights.size();
        vector<vector<pair<int, int>>> newQueries(heightsSize);

        for (int i = 0; i < queriesSize; i++) {
            int a = queries[i][0];
            int b = queries[i][1];
            if (a > b) {
                swap(a, b);
            }

            if ((heights[b] > heights[a]) || (a == b)) {
                retVal[i] = b;
            } else {
                newQueries[b].push_back({heights[a], i});
            }
        }

        vector<pair<int, int>> monoStack;
        for (int i = heightsSize - 1; i >= 0; i--) {
            int monoStackSize = monoStack.size();
            for (auto& [a, b] : newQueries[i]) {
                int position = search(a, monoStack);
                if ((position < monoStackSize) && (position >= 0)) {
                    retVal[b] = monoStack[position].second;
                }
            }

            while ((monoStack.empty() == false) && (monoStack.back().first <= heights[i])) {
                monoStack.pop_back();
            }
            monoStack.push_back({heights[i], i});
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def search(self, height, monoStack):
        retVal = -1

        left = 0
        right = len(monoStack) - 1
        while left <= right:
            middle = (left + right) // 2
            if monoStack[middle][0] > height:
                retVal = max(retVal, middle)
                left = middle + 1
            else:
                right = middle - 1

        return retVal

    def leftmostBuildingQueries(self, heights: List[int], queries: List[List[int]]) -> List[int]:
        retVal = []

        queriesSize = len(queries)
        retVal = [-1 for _ in range(queriesSize)]

        heightsSize = len(heights)
        newQueries = [[] for _ in range(heightsSize)]

        for i in range(queriesSize):
            a = queries[i][0]
            b = queries[i][1]
            if a > b:
                a, b = b, a

            if (heights[b] > heights[a]) or (a == b):
                retVal[i] = b
            else:
                newQueries[b].append((heights[a], i))

        monoStack = []
        for i in range(heightsSize - 1, -1, -1):
            monoStackSize = len(monoStack)
            for a, b in newQueries[i]:
                position = self.search(a, monoStack)
                if (position < monoStackSize) and (position >= 0):
                    retVal[b] = monoStack[position][1]

            while monoStack and (monoStack[-1][0] <= heights[i]):
                monoStack.pop()
            monoStack.append((heights[i], i))

        return retVal
```

</details>
