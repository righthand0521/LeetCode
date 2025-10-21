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
