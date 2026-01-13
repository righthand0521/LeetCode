# [Binary Search](https://en.wikipedia.org/wiki/Binary_search_algorithm)

## [3346. Maximum Frequency of an Element After Performing Operations I](https://leetcode.com/problems/maximum-frequency-of-an-element-after-performing-operations-i/)  1865

- [Official](https://leetcode.com/problems/maximum-frequency-of-an-element-after-performing-operations-i/editorial/)
- [Official](https://leetcode.cn/problems/maximum-frequency-of-an-element-after-performing-operations-i/solutions/3803630/zhi-xing-cao-zuo-hou-yuan-su-de-zui-gao-lk58w/)

<details><summary>Description</summary>

```text
You are given an integer array nums and two integers k and numOperations.

You must perform an operation numOperations times on nums, where in each operation you:
- Select an index i that was not selected in any previous operations.
- Add an integer in the range [-k, k] to nums[i].

Return the maximum possible frequency of any element in nums after performing the operations.

Example 1:
Input: nums = [1,4,5], k = 1, numOperations = 2
Output: 2
Explanation:
We can achieve a maximum frequency of two by:
Adding 0 to nums[1]. nums becomes [1, 4, 5].
Adding -1 to nums[2]. nums becomes [1, 4, 4].

Example 2:
Input: nums = [5,11,20,20], k = 5, numOperations = 1
Output: 2
Explanation:
We can achieve a maximum frequency of two by:
Adding 0 to nums[1].

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^5
0 <= k <= 10^5
0 <= numOperations <= nums.length
```

<details><summary>Hint</summary>

```text
1. Sort the array and try each value in range as a candidate.
```

</details>

</details>

<details><summary>C</summary>

```c
#ifndef HASH_H
#define HASH_H

typedef struct {
    int key;
    int val;
    UT_hash_handle hh;
} HashItem;
HashItem* hashFindItem(HashItem** obj, int key) {
    HashItem* pEntry = NULL;

    HASH_FIND_INT(*obj, &key, pEntry);

    return pEntry;
}
bool hashAddItem(HashItem** obj, int key, int val) {
    bool retVal = false;

    if (hashFindItem(obj, key)) {
        return retVal;
    }

    HashItem* pEntry = (HashItem*)malloc(sizeof(HashItem));
    if (pEntry == NULL) {
        perror("malloc");
        return retVal;
    }
    pEntry->key = key;
    pEntry->val = val;
    HASH_ADD_INT(*obj, key, pEntry);
    retVal = true;

    return retVal;
}
bool hashSetItem(HashItem** obj, int key, int val) {
    HashItem* pEntry = hashFindItem(obj, key);
    if (!pEntry) {
        hashAddItem(obj, key, val);
    } else {
        pEntry->val = val;
    }
    return true;
}
int hashGetItem(HashItem** obj, int key, int defaultVal) {
    int retVal = defaultVal;

    HashItem* pEntry = hashFindItem(obj, key);
    if (pEntry != NULL) {
        retVal = pEntry->val;
    }

    return retVal;
}
void hashFree(HashItem** obj) {
    HashItem* curr = NULL;
    HashItem* tmp = NULL;
    HASH_ITER(hh, *obj, curr, tmp) {
        HASH_DEL(*obj, curr);
        free(curr);
    }
}
void addMode(int* nums, int numsSize, int k, HashItem** modes, int value) {
    hashAddItem(modes, value, 1);
    if (value - k >= nums[0]) {
        hashAddItem(modes, value - k, 1);
    }
    if (value + k <= nums[numsSize - 1]) {
        hashAddItem(modes, value + k, 1);
    }
}

#endif  // HASH_H
int leftBound(int* nums, int numsSize, int value) {
    int retVal = 0;

    int left = 0;
    int right = numsSize - 1;
    int middle;
    while (left < right) {
        middle = (left + right) / 2;
        if (nums[middle] < value) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    retVal = left;

    return retVal;
}
int rightBound(int* nums, int numsSize, int value) {
    int retVal = 0;

    int left = 0;
    int right = numsSize - 1;
    int middle;
    while (left < right) {
        middle = (left + right + 1) / 2;
        if (nums[middle] > value) {
            right = middle - 1;
        } else {
            left = middle;
        }
    }
    retVal = left;

    return retVal;
}
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int maxFrequency(int* nums, int numsSize, int k, int numOperations) {
    int retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    HashItem* numCount = NULL;
    HashItem* modes = NULL;

    int lastNumIndex = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] == nums[lastNumIndex]) {
            continue;
        }

        hashSetItem(&numCount, nums[lastNumIndex], i - lastNumIndex);
        if (i - lastNumIndex > retVal) {
            retVal = i - lastNumIndex;
        }
        addMode(nums, numsSize, k, &modes, nums[lastNumIndex]);
        lastNumIndex = i;
    }

    hashSetItem(&numCount, nums[lastNumIndex], numsSize - lastNumIndex);
    if (numsSize - lastNumIndex > retVal) {
        retVal = numsSize - lastNumIndex;
    }
    addMode(nums, numsSize, k, &modes, nums[lastNumIndex]);

    int modesSize = HASH_COUNT(modes);
    int sortModes[modesSize];
    int pos = 0;
    for (HashItem* pEntry = modes; pEntry; pEntry = pEntry->hh.next) {
        sortModes[pos++] = pEntry->key;
    }
    qsort(sortModes, modesSize, sizeof(int), compareInteger);

    int mode, left, right, count, tempAns;
    for (int i = 0; i < modesSize; i++) {
        mode = sortModes[i];
        left = leftBound(nums, numsSize, mode - k);
        right = rightBound(nums, numsSize, mode + k);

        if (hashFindItem(&numCount, mode)) {
            count = hashGetItem(&numCount, mode, 0);
            tempAns = fmin(right - left + 1, count + numOperations);
        } else {
            tempAns = fmin(right - left + 1, numOperations);
        }

        if (tempAns > retVal) {
            retVal = tempAns;
        }
    }

    //
    hashFree(&numCount);
    hashFree(&modes);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    void addMode(vector<int>& nums, int k, set<int>& modes, int value) {
        modes.insert(value);
        if (value - k >= nums.front()) {
            modes.insert(value - k);
        }
        if (value + k <= nums.back()) {
            modes.insert(value + k);
        }
    }
    int leftBound(vector<int>& nums, int value) {
        int retVal = 0;

        int left = 0;
        int right = nums.size() - 1;
        while (left < right) {
            int middle = (left + right) / 2;
            if (nums[middle] < value) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }
        retVal = left;

        return retVal;
    }
    int rightBound(vector<int>& nums, int value) {
        int retVal = 0;

        int left = 0;
        int right = nums.size() - 1;
        while (left < right) {
            int middle = (left + right + 1) / 2;
            if (nums[middle] > value) {
                right = middle - 1;
            } else {
                left = middle;
            }
        }
        retVal = left;

        return retVal;
    }

   public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        int retVal = 0;

        int numsSize = nums.size();
        sort(nums.begin(), nums.end());

        unordered_map<int, int> numCount;
        set<int> modes;

        int lastNumIndex = 0;
        for (int i = 0; i < numsSize; ++i) {
            if (nums[i] == nums[lastNumIndex]) {
                continue;
            }
            numCount[nums[lastNumIndex]] = i - lastNumIndex;
            retVal = max(retVal, i - lastNumIndex);
            addMode(nums, k, modes, nums[lastNumIndex]);
            lastNumIndex = i;
        }

        numCount[nums[lastNumIndex]] = numsSize - lastNumIndex;
        retVal = max(retVal, numsSize - lastNumIndex);
        addMode(nums, k, modes, nums[lastNumIndex]);

        for (int mode : modes) {
            int left = leftBound(nums, mode - k);
            int right = rightBound(nums, mode + k);

            int tempAns;
            if (numCount.count(mode)) {
                tempAns = min(right - left + 1, numCount[mode] + numOperations);
            } else {
                tempAns = min(right - left + 1, numOperations);
            }
            retVal = max(retVal, tempAns);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def addMode(self, nums: List[int], k: int, modes: set, value: int) -> None:
        modes.add(value)
        if value - k >= nums[0]:
            modes.add(value - k)
        if value + k <= nums[-1]:
            modes.add(value + k)

    def maxFrequency(self, nums: List[int], k: int, numOperations: int) -> int:
        retVal = 0

        nums.sort()

        numCount = defaultdict(int)
        modes = set()

        lastIndex = 0
        for i in range(len(nums)):
            if nums[i] == nums[lastIndex]:
                continue
            numCount[nums[lastIndex]] = i - lastIndex
            retVal = max(retVal, i - lastIndex)
            self.addMode(nums, k, modes, nums[lastIndex])
            lastIndex = i

        numCount[nums[lastIndex]] = len(nums) - lastIndex
        retVal = max(retVal, len(nums) - lastIndex)
        self.addMode(nums, k, modes, nums[lastIndex])

        for mode in sorted(modes):
            l = bisect_left(nums, mode - k)
            r = bisect_right(nums, mode + k) - 1
            if mode in numCount:
                temp = min(r - l + 1, numCount[mode] + numOperations)
            else:
                temp = min(r - l + 1, numOperations)
            retVal = max(retVal, temp)

        return retVal
```

</details>

## [3347. Maximum Frequency of an Element After Performing Operations II](https://leetcode.com/problems/maximum-frequency-of-an-element-after-performing-operations-ii/description/)  2156

- [Official](https://leetcode.com/problems/maximum-frequency-of-an-element-after-performing-operations-ii/description/)
- [Official](https://leetcode.cn/problems/maximum-frequency-of-an-element-after-performing-operations-ii/solutions/3803631/zhi-xing-cao-zuo-hou-yuan-su-de-zui-gao-n4uko/)

<details><summary>Description</summary>

```text
You are given an integer array nums and two integers k and numOperations.

You must perform an operation numOperations times on nums, where in each operation you:
- Select an index i that was not selected in any previous operations.
- Add an integer in the range [-k, k] to nums[i].

Return the maximum possible frequency of any element in nums after performing the operations.

Example 1:
Input: nums = [1,4,5], k = 1, numOperations = 2
Output: 2
Explanation:
We can achieve a maximum frequency of two by:
Adding 0 to nums[1]. nums becomes [1, 4, 5].
Adding -1 to nums[2]. nums becomes [1, 4, 4].

Example 2:
Input: nums = [5,11,20,20], k = 5, numOperations = 1
Output: 2
Explanation:
We can achieve a maximum frequency of two by:
Adding 0 to nums[1].

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
0 <= k <= 10^5
0 <= numOperations <= nums.length
```

<details><summary>Hint</summary>

```text
1. The optimal values to check are nums[i] - k, nums[i], and nums[i] + k.
```

</details>

</details>

<details><summary>C</summary>

```c
#ifndef HASH_H
#define HASH_H

typedef struct {
    int key;
    int val;
    UT_hash_handle hh;
} HashItem;
HashItem* hashFindItem(HashItem** obj, int key) {
    HashItem* pEntry = NULL;

    HASH_FIND_INT(*obj, &key, pEntry);

    return pEntry;
}
bool hashAddItem(HashItem** obj, int key, int val) {
    bool retVal = false;

    if (hashFindItem(obj, key)) {
        return retVal;
    }

    HashItem* pEntry = (HashItem*)malloc(sizeof(HashItem));
    if (pEntry == NULL) {
        perror("malloc");
        return retVal;
    }
    pEntry->key = key;
    pEntry->val = val;
    HASH_ADD_INT(*obj, key, pEntry);
    retVal = true;

    return retVal;
}
bool hashSetItem(HashItem** obj, int key, int val) {
    HashItem* pEntry = hashFindItem(obj, key);
    if (!pEntry) {
        hashAddItem(obj, key, val);
    } else {
        pEntry->val = val;
    }
    return true;
}
int hashGetItem(HashItem** obj, int key, int defaultVal) {
    int retVal = defaultVal;

    HashItem* pEntry = hashFindItem(obj, key);
    if (pEntry != NULL) {
        retVal = pEntry->val;
    }

    return retVal;
}
void hashFree(HashItem** obj) {
    HashItem* curr = NULL;
    HashItem* tmp = NULL;
    HASH_ITER(hh, *obj, curr, tmp) {
        HASH_DEL(*obj, curr);
        free(curr);
    }
}
void addMode(int* nums, int numsSize, int k, HashItem** modes, int value) {
    hashAddItem(modes, value, 1);
    if (value - k >= nums[0]) {
        hashAddItem(modes, value - k, 1);
    }
    if (value + k <= nums[numsSize - 1]) {
        hashAddItem(modes, value + k, 1);
    }
}

#endif  // HASH_H
int leftBound(int* nums, int numsSize, int value) {
    int retVal = 0;

    int left = 0;
    int right = numsSize - 1;
    int middle;
    while (left < right) {
        middle = (left + right) / 2;
        if (nums[middle] < value) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    retVal = left;

    return retVal;
}
int rightBound(int* nums, int numsSize, int value) {
    int retVal = 0;

    int left = 0;
    int right = numsSize - 1;
    int middle;
    while (left < right) {
        middle = (left + right + 1) / 2;
        if (nums[middle] > value) {
            right = middle - 1;
        } else {
            left = middle;
        }
    }
    retVal = left;

    return retVal;
}
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int maxFrequency(int* nums, int numsSize, int k, int numOperations) {
    int retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    HashItem* numCount = NULL;
    HashItem* modes = NULL;

    int lastNumIndex = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] == nums[lastNumIndex]) {
            continue;
        }

        hashSetItem(&numCount, nums[lastNumIndex], i - lastNumIndex);
        if (i - lastNumIndex > retVal) {
            retVal = i - lastNumIndex;
        }
        addMode(nums, numsSize, k, &modes, nums[lastNumIndex]);
        lastNumIndex = i;
    }

    hashSetItem(&numCount, nums[lastNumIndex], numsSize - lastNumIndex);
    if (numsSize - lastNumIndex > retVal) {
        retVal = numsSize - lastNumIndex;
    }
    addMode(nums, numsSize, k, &modes, nums[lastNumIndex]);

    int modesSize = HASH_COUNT(modes);
    int sortModes[modesSize];
    int pos = 0;
    for (HashItem* pEntry = modes; pEntry; pEntry = pEntry->hh.next) {
        sortModes[pos++] = pEntry->key;
    }
    qsort(sortModes, modesSize, sizeof(int), compareInteger);

    int mode, left, right, count, tempAns;
    for (int i = 0; i < modesSize; i++) {
        mode = sortModes[i];
        left = leftBound(nums, numsSize, mode - k);
        right = rightBound(nums, numsSize, mode + k);

        if (hashFindItem(&numCount, mode)) {
            count = hashGetItem(&numCount, mode, 0);
            tempAns = fmin(right - left + 1, count + numOperations);
        } else {
            tempAns = fmin(right - left + 1, numOperations);
        }

        if (tempAns > retVal) {
            retVal = tempAns;
        }
    }

    //
    hashFree(&numCount);
    hashFree(&modes);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    void addMode(vector<int>& nums, int k, set<int>& modes, int value) {
        modes.insert(value);
        if (value - k >= nums.front()) {
            modes.insert(value - k);
        }
        if (value + k <= nums.back()) {
            modes.insert(value + k);
        }
    }
    int leftBound(vector<int>& nums, int value) {
        int retVal = 0;

        int left = 0;
        int right = nums.size() - 1;
        while (left < right) {
            int middle = (left + right) / 2;
            if (nums[middle] < value) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }
        retVal = left;

        return retVal;
    }
    int rightBound(vector<int>& nums, int value) {
        int retVal = 0;

        int left = 0;
        int right = nums.size() - 1;
        while (left < right) {
            int middle = (left + right + 1) / 2;
            if (nums[middle] > value) {
                right = middle - 1;
            } else {
                left = middle;
            }
        }
        retVal = left;

        return retVal;
    }

   public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        int retVal = 0;

        int numsSize = nums.size();
        sort(nums.begin(), nums.end());

        unordered_map<int, int> numCount;
        set<int> modes;

        int lastNumIndex = 0;
        for (int i = 0; i < numsSize; ++i) {
            if (nums[i] == nums[lastNumIndex]) {
                continue;
            }
            numCount[nums[lastNumIndex]] = i - lastNumIndex;
            retVal = max(retVal, i - lastNumIndex);
            addMode(nums, k, modes, nums[lastNumIndex]);
            lastNumIndex = i;
        }

        numCount[nums[lastNumIndex]] = numsSize - lastNumIndex;
        retVal = max(retVal, numsSize - lastNumIndex);
        addMode(nums, k, modes, nums[lastNumIndex]);

        for (int mode : modes) {
            int left = leftBound(nums, mode - k);
            int right = rightBound(nums, mode + k);

            int tempAns;
            if (numCount.count(mode)) {
                tempAns = min(right - left + 1, numCount[mode] + numOperations);
            } else {
                tempAns = min(right - left + 1, numOperations);
            }
            retVal = max(retVal, tempAns);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def addMode(self, nums: List[int], k: int, modes: set, value: int) -> None:
        modes.add(value)
        if value - k >= nums[0]:
            modes.add(value - k)
        if value + k <= nums[-1]:
            modes.add(value + k)

    def maxFrequency(self, nums: List[int], k: int, numOperations: int) -> int:
        retVal = 0

        nums.sort()

        numCount = defaultdict(int)
        modes = set()

        lastIndex = 0
        for i in range(len(nums)):
            if nums[i] == nums[lastIndex]:
                continue
            numCount[nums[lastIndex]] = i - lastIndex
            retVal = max(retVal, i - lastIndex)
            self.addMode(nums, k, modes, nums[lastIndex])
            lastIndex = i

        numCount[nums[lastIndex]] = len(nums) - lastIndex
        retVal = max(retVal, len(nums) - lastIndex)
        self.addMode(nums, k, modes, nums[lastIndex])

        for mode in sorted(modes):
            l = bisect_left(nums, mode - k)
            r = bisect_right(nums, mode + k) - 1
            if mode in numCount:
                temp = min(r - l + 1, numCount[mode] + numOperations)
            else:
                temp = min(r - l + 1, numOperations)
            retVal = max(retVal, temp)

        return retVal
```

</details>

## [3356. Zero Array Transformation II](https://leetcode.com/problems/zero-array-transformation-ii/)  1913

- [Official](https://leetcode.com/problems/zero-array-transformation-ii/editorial/)

<details><summary>Description</summary>

```text
You are given an integer array nums of length n and a 2D array queries where queries[i] = [li, ri, vali].

Each queries[i] represents the following action on nums:
- Decrement the value at each index in the range [li, ri] in nums by at most vali.
- The amount by which each value is decremented can be chosen independently for each index.

A Zero Array is an array with all its elements equal to 0.

Return the minimum possible non-negative value of k, such that after processing the first k queries in sequence,
nums becomes a Zero Array. If no such k exists, return -1.

Example 1:
Input: nums = [2,0,2], queries = [[0,2,1],[0,2,1],[1,1,3]]
Output: 2
Explanation:
For i = 0 (l = 0, r = 2, val = 1):
Decrement values at indices [0, 1, 2] by [1, 0, 1] respectively.
The array will become [1, 0, 1].
For i = 1 (l = 0, r = 2, val = 1):
Decrement values at indices [0, 1, 2] by [1, 0, 1] respectively.
The array will become [0, 0, 0], which is a Zero Array. Therefore, the minimum value of k is 2.

Example 2:
Input: nums = [4,3,2,1], queries = [[1,3,2],[0,2,1]]
Output: -1
Explanation:
For i = 0 (l = 1, r = 3, val = 2):
Decrement values at indices [1, 2, 3] by [2, 2, 1] respectively.
The array will become [4, 1, 0, 0].
For i = 1 (l = 0, r = 2, val = 1):
Decrement values at indices [0, 1, 2] by [1, 1, 0] respectively.
The array will become [3, 0, 0, 0], which is not a Zero Array.

Constraints:
1 <= nums.length <= 10^5
0 <= nums[i] <= 5 * 10^5
1 <= queries.length <= 10^5
queries[i].length == 3
0 <= li <= ri < nums.length
1 <= vali <= 5
```

<details><summary>Hint</summary>

```text
1. Can we apply binary search here?
2. Utilize a difference array to optimize the processing of queries.
```

</details>

</details>

<details><summary>C</summary>

```c
int minZeroArray(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize) {
    int retVal = 0;

    int sum = 0;
    int differenceArray[numsSize + 1];
    memset(differenceArray, 0, sizeof(differenceArray));
    int differenceArrayIdx;
    int left, right, val;
    for (int index = 0; index < numsSize; index++) {
        // Iterate through queries while current index of nums cannot equal zero
        while (sum + differenceArray[index] < nums[index]) {
            retVal++;
            // Zero array isn't formed after all queries are processed
            if (retVal > queriesSize) {
                retVal = -1;
                return retVal;
            }

            // Process start and end of range
            left = queries[retVal - 1][0];
            right = queries[retVal - 1][1];
            val = queries[retVal - 1][2];
            if (right >= index) {
                differenceArrayIdx = fmax(left, index);
                differenceArray[differenceArrayIdx] += val;
                differenceArray[right + 1] -= val;
            }
        }

        sum += differenceArray[index];  // Update prefix sum at current index
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int retVal = 0;

        int numsSize = nums.size();
        int queriesSize = queries.size();

        int sum = 0;
        vector<int> differenceArray(numsSize + 1);
        for (int index = 0; index < numsSize; index++) {
            // Iterate through queries while current index of nums cannot equal zero
            while (sum + differenceArray[index] < nums[index]) {
                retVal++;
                // Zero array isn't formed after all queries are processed
                if (retVal > queriesSize) {
                    retVal = -1;
                    return retVal;
                }

                // Process start and end of range
                int left = queries[retVal - 1][0];
                int right = queries[retVal - 1][1];
                int val = queries[retVal - 1][2];
                if (right >= index) {
                    differenceArray[max(left, index)] += val;
                    differenceArray[right + 1] -= val;
                }
            }

            sum += differenceArray[index];  // Update prefix sum at current index
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minZeroArray(self, nums: List[int], queries: List[List[int]]) -> int:
        retVal = 0

        numsSize = len(nums)
        queriesSize = len(queries)

        sum = 0
        differenceArray = [0] * (numsSize + 1)
        for index in range(numsSize):
            # Iterate through queries while current index of nums cannot equal zero
            while sum + differenceArray[index] < nums[index]:
                retVal += 1
                # Zero array isn't formed after all queries are processed
                if retVal > queriesSize:
                    retVal = -1
                    return retVal

                # Process start and end of range
                left, right, val = queries[retVal - 1]
                if right >= index:
                    differenceArray[max(left, index)] += val
                    differenceArray[right + 1] -= val

            # Update prefix sum at current index
            sum += differenceArray[index]

        return retVal
```

</details>

## [3453. Separate Squares I](https://leetcode.com/problems/separate-squares-i/)  1735

- [Official](https://leetcode.com/problems/separate-squares-i/editorial/)
- [Official](https://leetcode.cn/problems/separate-squares-i/solutions/3875568/fen-ge-zheng-fang-xing-i-by-leetcode-sol-aq2x/)

<details><summary>Description</summary>

```text
You are given a 2D integer array squares.
Each squares[i] = [xi, yi, li] represents the coordinates of the bottom-left point
and the side length of a square parallel to the x-axis.

Find the minimum y-coordinate value of a horizontal line
such that the total area of the squares above the line equals the total area of the squares below the line.

Answers within 10-5 of the actual answer will be accepted.

Note: Squares may overlap. Overlapping areas should be counted multiple times.

Example 1:
Input: squares = [[0,0,1],[2,2,1]]
Output: 1.00000
Explanation:
Any horizontal line between y = 1 and y = 2 will have 1 square unit above it and 1 square unit below it.
The lowest option is 1.

Example 2:
Input: squares = [[0,0,2],[1,1,1]]
Output: 1.16667
Explanation:
The areas are:
Below the line: 7/6 * 2 (Red) + 1/6 (Blue) = 15/6 = 2.5.
Above the line: 5/6 * 2 (Red) + 5/6 (Blue) = 15/6 = 2.5.
Since the areas above and below the line are equal, the output is 7/6 = 1.16667.

Constraints:
1 <= squares.length <= 5 * 10^4
squares[i] = [xi, yi, li]
squares[i].length == 3
0 <= xi, yi <= 10^9
1 <= li <= 10^9
The total area of all the squares will not exceed 10^12.
```

<details><summary>Hint</summary>

```text
1. Binary search on the answer.
```

</details>

</details>

<details><summary>C</summary>

```c
bool check(double limit_y, int** squares, int squaresSize, double totalArea) {
    bool retVal = false;

    double area = 0.0;
    int y, l;
    for (int i = 0; i < squaresSize; i++) {
        y = squares[i][1];
        l = squares[i][2];
        if (y < limit_y) {
            area += ((double)l * fmin(l, limit_y - y));
        }
    }
    retVal = (area >= totalArea / 2.0);

    return retVal;
}
double separateSquares(int** squares, int squaresSize, int* squaresColSize) {
    double retVal = 0;

    double maxY = 0.0;
    double totalArea = 0.0;
    double y, l;
    for (int i = 0; i < squaresSize; i++) {
        y = squares[i][1];
        l = squares[i][2];
        totalArea += (double)l * l;
        if (y + l > maxY) {
            maxY = y + l;
        }
    }

    double eps = 1e-5;
    double left = 0.0;
    double right = maxY;
    double middle;
    while (fabs(right - left) > eps) {
        middle = (right + left) / 2.0;
        if (check(middle, squares, squaresSize, totalArea)) {
            right = middle;
        } else {
            left = middle;
        }
    }
    retVal = right;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    bool check(vector<vector<int>>& squares, double totalArea, double limitY) {
        bool retVal = false;

        double area = 0;
        for (auto& sq : squares) {
            int y = sq[1];
            int l = sq[2];
            if (y < limitY) {
                area += (l * min(limitY - y, (double)l));
            }
        }
        retVal = area >= totalArea / 2;

        return retVal;
    };

   public:
    double separateSquares(vector<vector<int>>& squares) {
        double retVal = 0;

        double maxY = 0;
        double totalArea = 0;
        for (auto& sq : squares) {
            double y = sq[1];
            double l = sq[2];
            totalArea += (l * l);
            maxY = max(maxY, y + l);
        }

        double left = 0;
        double right = maxY;
        double eps = 1e-5;
        while (abs(right - left) > eps) {
            double middle = (right + left) / 2;
            if (check(squares, totalArea, middle) == true) {
                right = middle;
            } else {
                left = middle;
            }
        }
        retVal = right;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def check(self, squares: List[List[int]], totalArea: int, limitY: int) -> bool:
        retVal = False

        area = 0
        for x, y, l in squares:
            if y < limitY:
                area += (l * min(limitY - y, l))
        retVal = area >= totalArea / 2

        return retVal

    def separateSquares(self, squares: List[List[int]]) -> float:
        retVal = 0

        maxY = 0
        totalArea = 0
        for x, y, l in squares:
            totalArea += (l**2)
            maxY = max(maxY, y + l)

        left = 0
        right = maxY
        eps = 1e-5
        while abs(right - left) > eps:
            middle = (right + left) / 2
            if self.check(squares, totalArea, middle):
                right = middle
            else:
                left = middle
        retVal = right

        return retVal
```

</details>

## [3454. Separate Squares II](https://leetcode.com/problems/separate-squares-ii/)  2671

- [Official](https://leetcode.com/problems/separate-squares-ii/editorial/)
- [Official](https://leetcode.cn/problems/separate-squares-ii/solutions/3878861/fen-ge-zheng-fang-xing-ii-by-leetcode-so-baas/)

<details><summary>Description</summary>

```text
You are given a 2D integer array squares.
Each squares[i] = [xi, yi, li] represents the coordinates of the bottom-left point
and the side length of a square parallel to the x-axis.

Find the minimum y-coordinate value of a horizontal line such that
the total area covered by squares above the line equals the total area covered by squares below the line.

Answers within 10-5 of the actual answer will be accepted.

Note: Squares may overlap. Overlapping areas should be counted only once in this version.

Example 1:
Input: squares = [[0,0,1],[2,2,1]]
Output: 1.00000
Explanation:
Any horizontal line between y = 1 and y = 2 results in an equal split,
with 1 square unit above and 1 square unit below. The minimum y-value is 1.

Example 2:
Input: squares = [[0,0,2],[1,1,1]]
Output: 1.00000
Explanation:
Since the blue square overlaps with the red square, it will not be counted again.
Thus, the line y = 1 splits the squares into two equal parts.

Constraints:
1 <= squares.length <= 5 * 10^4
squares[i] = [xi, yi, li]
squares[i].length == 3
0 <= xi, yi <= 10^9
1 <= li <= 10^9
The total area of all the squares will not exceed 10^15.
```

<details><summary>Hint</summary>

```text
1. Use a line sweep and a segment tree.
2. The line must lie in one of the squares.
```

</details>

</details>

<details><summary>C</summary>

```c
typedef struct {
    int* count;
    int* covered;
    int* xs;
    int n;
} SegmentTree;
typedef struct {
    int y;
    int delta;
    int xl;
    int xr;
} Event;
SegmentTree* createSegmentTree(int* xs, int xsSize) {
    SegmentTree* pObj = NULL;

    pObj = (SegmentTree*)malloc(sizeof(SegmentTree));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    memset(pObj, 0, sizeof(SegmentTree));

    pObj->xs = (int*)malloc(sizeof(int) * xsSize);
    if (pObj->xs == NULL) {
        perror("malloc");
        free(pObj);
        pObj = NULL;
        return pObj;
    }
    memcpy(pObj->xs, xs, sizeof(int) * xsSize);

    pObj->n = xsSize - 1;
    int size = 4 * pObj->n;

    pObj->count = (int*)calloc(size, sizeof(int));
    if (pObj->count == NULL) {
        perror("calloc");
        free(pObj->xs);
        pObj->xs = NULL;
        free(pObj);
        pObj = NULL;
        return pObj;
    }

    pObj->covered = (int*)calloc(size, sizeof(int));
    if (pObj->covered == NULL) {
        perror("calloc");
        free(pObj->count);
        pObj->count = NULL;
        free(pObj->xs);
        pObj->xs = NULL;
        free(pObj);
        pObj = NULL;
        return pObj;
    }

    return pObj;
}
void freeSegmentTree(SegmentTree* st) {
    free(st->count);
    st->count = NULL;
    free(st->covered);
    st->covered = NULL;
    free(st->xs);
    st->xs = NULL;
    free(st);
    st = NULL;
}
void modify(SegmentTree* st, int qleft, int qright, int qval, int left, int right, int pos) {
    if ((st->xs[right + 1] <= qleft) || (st->xs[left] >= qright)) {
        return;
    }

    int middle;
    if ((qleft <= st->xs[left]) && (st->xs[right + 1] <= qright)) {
        st->count[pos] += qval;
    } else {
        middle = (left + right) / 2;
        modify(st, qleft, qright, qval, left, middle, pos * 2 + 1);
        modify(st, qleft, qright, qval, middle + 1, right, pos * 2 + 2);
    }

    if (st->count[pos] > 0) {
        st->covered[pos] = st->xs[right + 1] - st->xs[left];
    } else {
        if (left == right) {
            st->covered[pos] = 0;
        } else {
            st->covered[pos] = st->covered[pos * 2 + 1] + st->covered[pos * 2 + 2];
        }
    }
}
void updateSegmentTree(SegmentTree* st, int qleft, int qright, int qval) {
    modify(st, qleft, qright, qval, 0, st->n - 1, 0);
}
int querySegmentTree(SegmentTree* st) {
    int retVal = st->covered[0];

    return retVal;
}
int compareEvents(const void* a, const void* b) {
    int retVal = 0;

    Event* e1 = (Event*)a;
    Event* e2 = (Event*)b;
    retVal = e1->y - e2->y;

    return retVal;
}
int compareInts(const void* a, const void* b) {
    int retVal = *(int*)a - *(int*)b;

    return retVal;
}
int binarySearch(long long* arr, int size, long long target) {
    int retVal = 0;

    int middle;
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        middle = left + (right - left) / 2;
        if (arr[middle] < target) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }
    retVal = left - 1;  // return the last position less than targe

    return retVal;
}
int unique(int* arr, int arrSize) {
    int retVal = 0;

    if (arrSize <= 1) {
        retVal = arrSize;
        return retVal;
    }

    int j = 0;
    for (int i = 1; i < arrSize; i++) {
        if (arr[i] != arr[j]) {
            j++;
            arr[j] = arr[i];
        }
    }
    retVal = j + 1;

    return retVal;
}
double separateSquares(int** squares, int squaresSize, int* squaresColSize) {
    double retVal = 0;

    Event* events = (Event*)malloc(sizeof(Event) * squaresSize * 2);
    if (events == NULL) {
        perror("malloc");
        return retVal;
    }
    memset(events, 0, sizeof(Event) * squaresSize * 2);

    int* xs = (int*)malloc(sizeof(int) * squaresSize * 4);
    if (xs == NULL) {
        perror("malloc");
        free(events);
        events = NULL;
        return retVal;
    }
    memset(xs, 0, sizeof(int) * squaresSize * 4);

    int eventsSize = 0;
    int xsSize = 0;

    // collect all events and x coordinates
    int x, y, l, xr;
    for (int i = 0; i < squaresSize; i++) {
        x = squares[i][0];
        y = squares[i][1];
        l = squares[i][2];
        xr = x + l;

        xs[xsSize++] = x;
        xs[xsSize++] = xr;
        events[eventsSize++] = (Event){y, 1, x, xr};
        events[eventsSize++] = (Event){y + l, -1, x, xr};
    }

    // sort events by y-coordinate
    qsort(events, eventsSize, sizeof(Event), compareEvents);
    // sort and remove duplicates x-coordinate
    qsort(xs, xsSize, sizeof(int), compareInts);

    xsSize = unique(xs, xsSize);

    // create a segment tree
    SegmentTree* segTree = createSegmentTree(xs, xsSize);
    if (segTree == NULL) {
        free(events);
        events = NULL;
        free(xs);
        xs = NULL;
        return retVal;
    }

    // save prefix sums and widths
    long long* psum = (long long*)malloc(sizeof(long long) * eventsSize);
    if (psum == NULL) {
        perror("malloc");
        free(events);
        events = NULL;
        free(xs);
        xs = NULL;
        freeSegmentTree(segTree);
        segTree = NULL;
        return retVal;
    }
    memset(psum, 0, sizeof(long long) * eventsSize);

    int* widths = (int*)malloc(sizeof(int) * eventsSize);
    if (widths == NULL) {
        perror("malloc");
        free(events);
        events = NULL;
        free(xs);
        xs = NULL;
        free(psum);
        psum = NULL;
        freeSegmentTree(segTree);
        segTree = NULL;
        return retVal;
    }
    memset(widths, 0, sizeof(int) * eventsSize);

    long long totalArea = 0LL;
    int prev = events[0].y;

    // scan: calculate total area and record intermediate states
    int eventY, eventDelta, eventXl, eventXr;
    for (int i = 0; i < eventsSize; i++) {
        eventY = events[i].y;
        eventDelta = events[i].delta;
        eventXl = events[i].xl;
        eventXr = events[i].xr;

        totalArea += (double)querySegmentTree(segTree) * (eventY - prev);
        updateSegmentTree(segTree, eventXl, eventXr, eventDelta);

        // record prefix sums and widths
        psum[i] = totalArea;
        widths[i] = querySegmentTree(segTree);
        prev = eventY;
    }

    // calculate the target area (half rounded up)
    long long target = (long long)(totalArea + 1) / 2;
    // find the first position greater than or equal to target using binary search
    int idx = binarySearch(psum, eventsSize, (double)target);
    // get the corresponding area, width, and height
    double area = psum[idx];
    int width = widths[idx];
    int height = events[idx].y;

    retVal = height + (totalArea - area * 2) / (width * 2.0);

    //
    free(events);
    events = NULL;
    free(xs);
    xs = NULL;
    free(psum);
    psum = NULL;
    free(widths);
    widths = NULL;
    freeSegmentTree(segTree);
    segTree = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class SegmentTree {
   private:
    vector<int> count;
    vector<int> covered;
    vector<int> xs;
    int n;

    void modify(int qleft, int qright, int qval, int left, int right, int pos) {
        if (xs[right + 1] <= qleft || xs[left] >= qright) {
            return;
        }

        if ((qleft <= xs[left]) && (xs[right + 1] <= qright)) {
            count[pos] += qval;
        } else {
            int middle = (left + right) / 2;
            modify(qleft, qright, qval, left, middle, pos * 2 + 1);
            modify(qleft, qright, qval, middle + 1, right, pos * 2 + 2);
        }

        if (count[pos] > 0) {
            covered[pos] = xs[right + 1] - xs[left];
        } else {
            if (left == right) {
                covered[pos] = 0;
            } else {
                covered[pos] = covered[pos * 2 + 1] + covered[pos * 2 + 2];
            }
        }
    }

   public:
    SegmentTree(vector<int>& xs_) : xs(xs_) {
        n = xs.size() - 1;
        count.resize(4 * n, 0);
        covered.resize(4 * n, 0);
    }
    void update(int qleft, int qright, int qval) {
        //
        modify(qleft, qright, qval, 0, n - 1, 0);
    }
    int query() {
        int retVal = covered[0];

        return retVal;
    }
};
class Solution {
   public:
    double separateSquares(vector<vector<int>>& squares) {
        double retVal = 0;

        vector<tuple<int, int, int, int>> events;
        set<int> xsSet;
        for (auto& sq : squares) {
            int x = sq[0];
            int y = sq[1];
            int l = sq[2];
            int xr = x + l;
            events.emplace_back(y, 1, x, xr);
            events.emplace_back(y + l, -1, x, xr);
            xsSet.insert(x);
            xsSet.insert(xr);
        }
        // sort events by y-coordinate
        sort(events.begin(), events.end());
        // discrete coordinates
        vector<int> xs(xsSet.begin(), xsSet.end());
        // initialize the segment tree
        SegmentTree segTree(xs);

        vector<double> psum;
        vector<int> widths;
        double totalarea = 0.0;
        int prev = get<0>(events[0]);

        // scan: calculate total area and record intermediate states
        for (auto& [y, delta, xl, xr] : events) {
            int len = segTree.query();
            totalarea += (1LL * len * (y - prev));
            segTree.update(xl, xr, delta);
            // record prefix sums and widths
            psum.push_back(totalarea);
            widths.push_back(segTree.query());
            prev = y;
        }

        // calculate the target area (half rounded up)
        long long target = (long long)(totalarea + 1) / 2;
        // find the first position greater than or equal to target using binary search
        int i = lower_bound(psum.begin(), psum.end(), target) - psum.begin() - 1;
        // get the corresponding area, width, and height
        double area = psum[i];
        int width = widths[i];
        int height = get<0>(events[i]);

        retVal = height + (totalarea - area * 2) / (width * 2.0);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class SegmentTree:
    def __init__(self, xs: List[int]):
        self.xs = xs
        self.n = len(xs) - 1
        self.count = [0] * (4 * self.n)
        self.covered = [0] * (4 * self.n)

    def update(self, qleft, qright, qval, left, right, pos) -> None:
        if (self.xs[right + 1] <= qleft) or (self.xs[left] >= qright):
            return

        if (qleft <= self.xs[left]) and (self.xs[right + 1] <= qright):
            self.count[pos] += qval
        else:
            middle = (left + right) // 2
            self.update(qleft, qright, qval, left, middle, pos * 2 + 1)
            self.update(qleft, qright, qval, middle + 1, right, pos * 2 + 2)

        if self.count[pos] > 0:
            self.covered[pos] = self.xs[right + 1] - self.xs[left]
        else:
            if left == right:
                self.covered[pos] = 0
            else:
                self.covered[pos] = (self.covered[pos * 2 + 1] + self.covered[pos * 2 + 2])

    def query(self) -> int:
        retVal = self.covered[0]

        return retVal


class Solution:
    def separateSquares(self, squares: List[List[int]]) -> float:
        retVal = 0

        events = []
        xs = set()
        for x, y, l in squares:
            events.append((y, 1, x, x + l))
            events.append((y + l, -1, x, x + l))
            xs.update([x, x + l])
        xs = sorted(xs)
        psegmenttree = SegmentTree(xs)
        events.sort()

        psum = []
        widths = []
        totalarea = 0.0
        previousy = events[0][0]

        # scan: calculate total area and record intermediate states
        for y, delta, xl, xr in events:
            length = psegmenttree.query()
            totalarea += (length * (y - previousy))
            psegmenttree.update(xl, xr, delta, 0, psegmenttree.n - 1, 0)
            # record prefix sums and widths
            psum.append(totalarea)
            widths.append(psegmenttree.query())
            previousy = y

        # calculate the target area (half rounded up)
        target = (totalarea + 1) // 2

        # find the first position greater than or equal to target using binary search
        i = bisect_left(psum, target) - 1

        # get the corresponding area, width, and height
        area = psum[i]
        width = widths[i]
        height = events[i][0]

        retVal = height + (totalarea - area * 2) / (width * 2.0)

        return retVal
```

</details>

## [3477. Fruits Into Baskets II](https://leetcode.com/problems/fruits-into-baskets-ii/description/)  1296

- [Official](https://leetcode.com/problems/fruits-into-baskets-ii/editorial/)
- [Official](https://leetcode.cn/problems/fruits-into-baskets-ii/solutions/3737060/shui-guo-cheng-lan-ii-by-leetcode-soluti-f92n/)

<details><summary>Description</summary>

```text
You are given two arrays of integers, fruits and baskets, each of length n,
where fruits[i] represents the quantity of the ith type of fruit,
and baskets[j] represents the capacity of the jth basket.

From left to right, place the fruits according to these rules:
- Each fruit type must be placed in the leftmost available basket
  with a capacity greater than or equal to the quantity of that fruit type.
- Each basket can hold only one type of fruit.
- If a fruit type cannot be placed in any basket, it remains unplaced.

Return the number of fruit types that remain unplaced after all possible allocations are made.

Example 1:
Input: fruits = [4,2,5], baskets = [3,5,4]
Output: 1
Explanation:
fruits[0] = 4 is placed in baskets[1] = 5.
fruits[1] = 2 is placed in baskets[0] = 3.
fruits[2] = 5 cannot be placed in baskets[2] = 4.
Since one fruit type remains unplaced, we return 1.

Example 2:
Input: fruits = [3,6,1], baskets = [6,4,7]
Output: 0
Explanation:
fruits[0] = 3 is placed in baskets[0] = 6.
fruits[1] = 6 cannot be placed in baskets[1] = 4 (insufficient capacity)
but can be placed in the next available basket, baskets[2] = 7.
fruits[2] = 1 is placed in baskets[1] = 4.
Since all fruits are successfully placed, we return 0.

Constraints:
n == fruits.length == baskets.length
1 <= n <= 100
1 <= fruits[i], baskets[i] <= 1000
```

<details><summary>Hint</summary>

```text
1. Simulate the operations for each fruit as described
```

</details>

</details>

<details><summary>C</summary>

```c
int numOfUnplacedFruits(int* fruits, int fruitsSize, int* baskets, int basketsSize) {
    int retVal = 0;

    int unset;
    for (int i = 0; i < fruitsSize; ++i) {
        unset = 1;
        for (int j = 0; j < basketsSize; ++j) {
            if (fruits[i] <= baskets[j]) {
                baskets[j] = 0;
                unset = 0;
                break;
            }
        }
        retVal += unset;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        int retVal = 0;

        int basketsSize = baskets.size();
        for (auto fruit : fruits) {
            int unset = 1;
            for (int i = 0; i < basketsSize; i++) {
                if (fruit <= baskets[i]) {
                    baskets[i] = 0;
                    unset = 0;
                    break;
                }
            }
            retVal += unset;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def numOfUnplacedFruits(self, fruits: List[int], baskets: List[int]) -> int:
        retVal = 0

        basketsSize = len(baskets)
        for fruit in fruits:
            unset = 1
            for i in range(basketsSize):
                if fruit <= baskets[i]:
                    baskets[i] = 0
                    unset = 0
                    break
            retVal += unset

        return retVal
```

</details>

## [3479. Fruits Into Baskets III](https://leetcode.com/problems/fruits-into-baskets-iii/)  2178

- [Official](https://leetcode.com/problems/fruits-into-baskets-iii/editorial/)
- [Official](https://leetcode.cn/problems/fruits-into-baskets-iii/solutions/3737092/shui-guo-cheng-lan-iii-by-leetcode-solut-zlvd/)

<details><summary>Description</summary>

```text
You are given two arrays of integers, fruits and baskets, each of length n,
where fruits[i] represents the quantity of the ith type of fruit,
and baskets[j] represents the capacity of the jth basket.

From left to right, place the fruits according to these rules:
- Each fruit type must be placed in the leftmost available basket
  with a capacity greater than or equal to the quantity of that fruit type.
- Each basket can hold only one type of fruit.
- If a fruit type cannot be placed in any basket, it remains unplaced.

Return the number of fruit types that remain unplaced after all possible allocations are made.

Example 1:
Input: fruits = [4,2,5], baskets = [3,5,4]
Output: 1
Explanation:
fruits[0] = 4 is placed in baskets[1] = 5.
fruits[1] = 2 is placed in baskets[0] = 3.
fruits[2] = 5 cannot be placed in baskets[2] = 4.
Since one fruit type remains unplaced, we return 1.

Example 2:
Input: fruits = [3,6,1], baskets = [6,4,7]
Output: 0
Explanation:
fruits[0] = 3 is placed in baskets[0] = 6.
fruits[1] = 6 cannot be placed in baskets[1] = 4 (insufficient capacity)
but can be placed in the next available basket, baskets[2] = 7.
fruits[2] = 1 is placed in baskets[1] = 4.
Since all fruits are successfully placed, we return 0.

Constraints:
n == fruits.length == baskets.length
1 <= n <= 10^5
1 <= fruits[i], baskets[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Sort the baskets by the pair of (basket[i], i) in the array.
2. For each fruit from left to right,
   use binary search to find the first index in the sorted array such that basket[i] >= fruit.
3. Use a segment tree to maintain the smallest original indices where basket[i] >= fruit.
4. When a valid index is found, set the corresponding point to infinity to mark it as used.
```

</details>

</details>

<details><summary>C</summary>

```c
#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H

#define MAX_SEGTREE_SIZE (400007)  // n == fruits.length == baskets.length, 1 <= n <= 10 ^ 5 .

int segmentTree[MAX_SEGTREE_SIZE];
int* basketsBuffer;

void build(int p, int left, int right) {
    if (left == right) {
        segmentTree[p] = basketsBuffer[left];
        return;
    }

    int middle = (left + right) >> 1;
    build((p << 1), left, middle);
    build((p << 1) | 1, middle + 1, right);
    segmentTree[p] = fmax(segmentTree[(p << 1)], segmentTree[(p << 1) | 1]);
}
int query(int p, int left, int right, int ql, int qr) {
    int retVal = 0;

    if ((ql > right) || (qr < left)) {
        retVal = INT_MIN;
    } else if ((ql <= left) && (right <= qr)) {
        retVal = segmentTree[p];
    } else {
        int middle = (left + right) >> 1;
        retVal = fmax(query((p << 1), left, middle, ql, qr), query((p << 1) | 1, middle + 1, right, ql, qr));
    }

    return retVal;
}
void update(int p, int left, int right, int pos, int val) {
    if (left == right) {
        segmentTree[p] = val;
        return;
    }

    int middle = (left + right) >> 1;
    if (pos <= middle) {
        update((p << 1), left, middle, pos, val);
    } else {
        update((p << 1) | 1, middle + 1, right, pos, val);
    }
    segmentTree[p] = fmax(segmentTree[(p << 1)], segmentTree[(p << 1) | 1]);
}

#endif  // SEGMENT_TREE_H
int numOfUnplacedFruits(int* fruits, int fruitsSize, int* baskets, int basketsSize) {
    int retVal = 0;

    basketsBuffer = baskets;

    if (basketsSize == 0) {
        retVal = fruitsSize;
        return retVal;
    }

    for (int i = 0; i < MAX_SEGTREE_SIZE; i++) {
        segmentTree[i] = INT_MIN;
    }

    build(1, 0, basketsSize - 1);

    int middle, left, right, res;
    for (int i = 0; i < fruitsSize; i++) {
        res = -1;

        left = 0;
        right = basketsSize - 1;
        while (left <= right) {
            middle = (left + right) >> 1;
            if (query(1, 0, basketsSize - 1, 0, middle) >= fruits[i]) {
                res = middle;
                right = middle - 1;
            } else {
                left = middle + 1;
            }
        }

        if ((res != -1) && (baskets[res] >= fruits[i])) {
            update(1, 0, basketsSize - 1, res, INT_MIN);
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
   private:
    int segmentTree[400007];  // n == fruits.length == baskets.length, 1 <= n <= 10 ^ 5 .
    vector<int> baskets;

    void build(int p, int left, int right) {
        if (left == right) {
            segmentTree[p] = baskets[left];
            return;
        }

        int middle = (left + right) >> 1;
        build((p << 1), left, middle);
        build((p << 1) | 1, middle + 1, right);
        segmentTree[p] = max(segmentTree[(p << 1)], segmentTree[(p << 1) | 1]);
    }
    int query(int p, int left, int right, int ql, int qr) {
        int retVal = 0;

        if ((ql > right) || (qr < left)) {
            retVal = numeric_limits<int>::min();
        } else if ((ql <= left) && (right <= qr)) {
            retVal = segmentTree[p];
        } else {
            int middle = (left + right) >> 1;
            retVal = max(query(p << 1, left, middle, ql, qr), query(p << 1 | 1, middle + 1, right, ql, qr));
        }

        return retVal;
    }
    void update(int p, int left, int right, int pos, int val) {
        if (left == right) {
            segmentTree[p] = val;
            return;
        }

        int middle = (left + right) >> 1;
        if (pos <= middle) {
            update((p << 1), left, middle, pos, val);
        } else {
            update((p << 1) | 1, middle + 1, right, pos, val);
        }
        segmentTree[p] = max(segmentTree[(p << 1)], segmentTree[(p << 1) | 1]);
    }

   public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        int retVal = 0;

        this->baskets = baskets;
        int fruitsSize = fruits.size();
        int basketsSize = baskets.size();
        if (basketsSize == 0) {
            retVal = fruitsSize;
            return retVal;
        }

        build(1, 0, basketsSize - 1);

        for (int i = 0; i < fruitsSize; i++) {
            int res = -1;
            int left = 0;
            int right = basketsSize - 1;
            while (left <= right) {
                int middle = (left + right) >> 1;

                if (query(1, 0, basketsSize - 1, 0, middle) >= fruits[i]) {
                    res = middle;
                    right = middle - 1;
                } else {
                    left = middle + 1;
                }
            }

            if ((res != -1) && (baskets[res] >= fruits[i])) {
                update(1, 0, basketsSize - 1, res, numeric_limits<int>::min());
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
class SegmentTree:
    def __init__(self, baskets: List[int]):
        self.n = len(baskets)
        size = 2 << (self.n - 1).bit_length()
        self.segmentTree = [0] * size
        self._build(baskets, 1, 0, self.n - 1)

    def _maintain(self, o: int):
        self.segmentTree[o] = max(self.segmentTree[o * 2], self.segmentTree[o * 2 + 1])

    def _build(self, baskets: List[int], o: int, left: int, right: int):
        if left == right:
            self.segmentTree[o] = baskets[left]
            return

        middle = (left + right) // 2
        self._build(baskets, o * 2, left, middle)
        self._build(baskets, o * 2 + 1, middle + 1, right)
        self._maintain(o)

    def find_first_and_update(self, o: int, left: int, right: int, fruit: int) -> int:
        retVal = -1

        if self.segmentTree[o] < fruit:
            return retVal

        if left == right:
            self.segmentTree[o] = -1
            retVal = left
            return retVal

        middle = (left + right) // 2
        i = self.find_first_and_update(o * 2, left, middle, fruit)
        if i == -1:
            i = self.find_first_and_update(o * 2 + 1, middle + 1, right, fruit)
        self._maintain(o)
        retVal = i

        return retVal


class Solution:
    def numOfUnplacedFruits(self, fruits: List[int], baskets: List[int]) -> int:
        retVal = 0

        basketsSize = len(baskets)
        if basketsSize == 0:
            retVal = len(fruits)
            return retVal

        tree = SegmentTree(baskets)
        for fruit in fruits:
            if tree.find_first_and_update(1, 0, basketsSize - 1, fruit) == -1:
                retVal += 1

        return retVal
```

</details>
