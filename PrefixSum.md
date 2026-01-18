# [Prefix Sum](https://en.wikipedia.org/wiki/Prefix_sum)

## [303. Range Sum Query - Immutable](https://leetcode.com/problems/range-sum-query-immutable/)

<details><summary>Description</summary>

```text
Given an integer array nums, handle multiple queries of the following type:

Calculate the sum of the elements of nums between indices left and right inclusive where left <= right.

Implement the NumArray class:
- NumArray(int[] nums)
    Initializes the object with the integer array nums.
- int sumRange(int left, int right)
    Returns the sum of the elements of nums between indices left and right inclusive
    (i.e. nums[left] + nums[left + 1] + ... + nums[right]).

Example 1:
Input
["NumArray", "sumRange", "sumRange", "sumRange"]
[[[-2, 0, 3, -5, 2, -1]], [0, 2], [2, 5], [0, 5]]
Output
[null, 1, -1, -3]
Explanation
NumArray numArray = new NumArray([-2, 0, 3, -5, 2, -1]);
numArray.sumRange(0, 2); // return (-2) + 0 + 3 = 1
numArray.sumRange(2, 5); // return 3 + (-5) + 2 + (-1) = -1
numArray.sumRange(0, 5); // return (-2) + 0 + 3 + (-5) + 2 + (-1) = -3

Constraints:
1 <= nums.length <= 10^4
-10^5 <= nums[i] <= 10^5
0 <= left <= right < nums.length
At most 10^4 calls will be made to sumRange.
```

</details>

<details><summary>C</summary>

```c
typedef struct {
    int* pNums;
} NumArray;

NumArray* numArrayCreate(int* nums, int numsSize) {
    NumArray* pCreate = (NumArray*)malloc(sizeof(NumArray));
    if (pCreate == NULL) {
        perror("malloc");
        return pCreate;
    }
    pCreate->pNums = NULL;

    pCreate->pNums = (int*)malloc(numsSize*sizeof(int));
    if (pCreate->pNums == NULL) {
        perror("malloc");
        free(pCreate);
        pCreate = NULL;
        return pCreate;
    }
    memset(pCreate->pNums, 0, (numsSize*sizeof(int)));
    memcpy(pCreate->pNums, nums, (numsSize*sizeof(int)));

    return pCreate;
}

int numArraySumRange(NumArray* obj, int left, int right) {
    int retVal = 0;

    int i;
    for (i=left; i<=right; ++i) {
        retVal += obj->pNums[i];
    }

    return retVal;
}

void numArrayFree(NumArray* obj) {
    if (obj == NULL) {
        return;
    }

    if (obj->pNums) {
        free(obj->pNums);
        obj->pNums = NULL;
    }
    free(obj);
    obj = NULL;
}

/**
 * Your NumArray struct will be instantiated and called as such:
 * NumArray* obj = numArrayCreate(nums, numsSize);
 * int param_1 = numArraySumRange(obj, left, right);
 * numArrayFree(obj);
 */
```

</details>

## [304. Range Sum Query 2D - Immutable](https://leetcode.com/problems/range-sum-query-2d-immutable/)

- [Official](https://leetcode.com/problems/range-sum-query-2d-immutable/solutions/127813/range-sum-query-2d-immutable/)
- [Official](https://leetcode.cn/problems/range-sum-query-2d-immutable/solutions/627420/er-wei-qu-yu-he-jian-suo-ju-zhen-bu-ke-b-2z5n/)

<details><summary>Description</summary>

```text
Given a 2D matrix matrix, handle multiple queries of the following type:
- Calculate the sum of the elements of matrix inside the rectangle defined by its upper left corner (row1, col1)
and lower right corner (row2, col2).

Implement the NumMatrix class:
- NumMatrix(int[][] matrix)
  Initializes the object with the integer matrix matrix.
- int sumRegion(int row1, int col1, int row2, int col2)
  Returns the sum of the elements of matrix inside the rectangle defined by its upper left corner (row1, col1)
  and lower right corner (row2, col2).

You must design an algorithm where sumRegion works on O(1) time complexity.


Example 1:
+-------------------+
| 3 | 0 | 1 | 4 | 2 |
| 5 | 6 | 3 | 2 | 1 |
| 1 | 2 | 0 | 1 | 5 |
| 4 | 1 | 0 | 1 | 7 |
| 1 | 0 | 3 | 0 | 5 |
+-------------------+

Input
["NumMatrix", "sumRegion", "sumRegion", "sumRegion"]
[
    [[[3, 0, 1, 4, 2],[5, 6, 3, 2, 1],[1, 2, 0, 1, 5],[4, 1, 0, 1, 7],[1, 0, 3, 0, 5]]],
    [2, 1, 4, 3],
    [1, 1, 2, 2],
    [1, 2, 2, 4]
]
Output
[null, 8, 11, 12]
Explanation
NumMatrix numMatrix = new NumMatrix([[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]]);
numMatrix.sumRegion(2, 1, 4, 3); // return 8 (i.e sum of the red rectangle)
numMatrix.sumRegion(1, 1, 2, 2); // return 11 (i.e sum of the green rectangle)
numMatrix.sumRegion(1, 2, 2, 4); // return 12 (i.e sum of the blue rectangle)

Constraints:
m == matrix.length
n == matrix[i].length
1 <= m, n <= 200
-10^4 <= matrix[i][j] <= 10^4
0 <= row1 <= row2 < m
0 <= col1 <= col2 < n
At most 10^4 calls will be made to sumRegion.
```

</details>

<details><summary>C</summary>

```c
typedef struct {
    int** sums;
    int sumsSize;
} NumMatrix;
NumMatrix* numMatrixCreate(int** matrix, int matrixSize, int* matrixColSize) {
    NumMatrix* pCreate = (NumMatrix*)malloc(sizeof(NumMatrix));
    if (pCreate == NULL) {
        perror("malloc");
        return pCreate;
    }

    pCreate->sumsSize = matrixSize + 1;
    pCreate->sums = (int**)malloc((matrixSize + 1) * sizeof(int*));
    if (pCreate->sums == NULL) {
        perror("malloc");
        free(pCreate);
        pCreate = NULL;
        return pCreate;
    }

    int n = matrixSize ? matrixColSize[0] : 0;
    int i, j;
    for (i = 0; i <= matrixSize; i++) {
        pCreate->sums[i] = (int*)malloc((n + 1) * sizeof(int));
        if (pCreate->sums[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pCreate->sums[j]);
                pCreate->sums[j] = NULL;
            }
            free(pCreate->sums);
            pCreate->sums = NULL;
            free(pCreate);
            pCreate = NULL;
            return pCreate;
        }
        memset(pCreate->sums[i], 0, ((n + 1) * sizeof(int)));
    }

    for (i = 0; i < matrixSize; ++i) {
        for (j = 0; j < matrixColSize[i]; ++j) {
            pCreate->sums[i + 1][j + 1] =
                pCreate->sums[i][j + 1] + pCreate->sums[i + 1][j] - pCreate->sums[i][j] + matrix[i][j];
        }
    }

    return pCreate;
}
int numMatrixSumRegion(NumMatrix* obj, int row1, int col1, int row2, int col2) {
    int retVal = 0;

    if (obj == NULL) {
        return retVal;
    }
    retVal =
        obj->sums[row2 + 1][col2 + 1] - obj->sums[row1][col2 + 1] - obj->sums[row2 + 1][col1] + obj->sums[row1][col1];

    return retVal;
}
void numMatrixFree(NumMatrix* obj) {
    if (obj == NULL) {
        return;
    }

    int i;
    for (i = 0; i < obj->sumsSize; ++i) {
        free(obj->sums[i]);
        obj->sums[i] = NULL;
    }
    free(obj->sums);
    obj->sums = NULL;
    free(obj);
    obj = NULL;
}
/**
 * Your NumMatrix struct will be instantiated and called as such:
 * NumMatrix* obj = numMatrixCreate(matrix, matrixSize, matrixColSize);
 * int param_1 = numMatrixSumRegion(obj, row1, col1, row2, col2);

 * numMatrixFree(obj);
*/
```

</details>

## [724. Find Pivot Index](https://leetcode.com/problems/find-pivot-index/)

- [Official](https://leetcode.com/problems/find-pivot-index/editorial/)
- [Official](https://leetcode.cn/problems/find-pivot-index/solutions/579264/xun-zhao-shu-zu-de-zhong-xin-suo-yin-by-gzjle/)

<details><summary>Description</summary>

```text
Given an array of integers nums, calculate the pivot index of this array.

The pivot index is the index where the sum of all the numbers strictly to the left of the index
is equal to the sum of all the numbers strictly to the index's right.

If the index is on the left edge of the array, then the left sum is 0 because there are no elements to the left.
This also applies to the right edge of the array.

Return the leftmost pivot index. If no such index exists, return -1.

Example 1:
Input: nums = [1,7,3,6,5,6]
Output: 3
Explanation:
The pivot index is 3.
Left sum = nums[0] + nums[1] + nums[2] = 1 + 7 + 3 = 11
Right sum = nums[4] + nums[5] = 5 + 6 = 11

Example 2:
Input: nums = [1,2,3]
Output: -1
Explanation:
There is no index that satisfies the conditions in the problem statement.

Example 3:
Input: nums = [2,1,-1]
Output: 0
Explanation:
The pivot index is 0.
Left sum = 0 (no elements to the left of index 0)
Right sum = nums[1] + nums[2] = 1 + -1 = 0

Constraints:
1 <= nums.length <= 10^4
-1000 <= nums[i] <= 1000

Note: This question is the same as 1991: https://leetcode.com/problems/find-the-middle-index-in-array/
```

<details><summary>Hint</summary>

```text
1. Create an array sumLeft where sumLeft[i] is the sum of all the numbers to the left of index i.
2. Create an array sumRight where sumRight[i] is the sum of all the numbers to the right of index i.
3. For each index i, check if sumLeft[i] equals sumRight[i] return i. If no i found, return -1.
```

</details>

</details>

<details><summary>C</summary>

```c
int pivotIndex(int* nums, int numsSize) {
    int retVal = -1;

    int i;

    int sumLeft[numsSize];
    sumLeft[0] = nums[0];
    for (i = 1; i < numsSize; ++i) {
        sumLeft[i] = sumLeft[i - 1] + nums[i];
    }

    int sumRight[numsSize];
    sumRight[numsSize - 1] = nums[numsSize - 1];
    for (i = numsSize - 2; i >= 0; --i) {
        sumRight[i] = sumRight[i + 1] + nums[i];
    }

    for (i = 0; i < numsSize; ++i) {
        if (sumLeft[i] == sumRight[i]) {
            retVal = i;
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
    int pivotIndex(vector<int>& nums) {
        int retVal = -1;

        int numsSize = nums.size();

        vector<int> sumLeft(numsSize, 0);
        sumLeft[0] = nums[0];
        for (int i = 1; i < numsSize; ++i) {
            sumLeft[i] = sumLeft[i - 1] + nums[i];
        }

        vector<int> sumRight(numsSize, 0);
        sumRight[numsSize - 1] = nums[numsSize - 1];
        for (int i = numsSize - 2; i >= 0; --i) {
            sumRight[i] = sumRight[i + 1] + nums[i];
        }

        for (int i = 0; i < numsSize; ++i) {
            if (sumLeft[i] == sumRight[i]) {
                retVal = i;
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
    def pivotIndex(self, nums: List[int]) -> int:
        retVal = -1

        numsSize = len(nums)

        sumLeft = [0] * numsSize
        sumLeft[0] = nums[0]
        for i in range(1, numsSize):
            sumLeft[i] = sumLeft[i - 1] + nums[i]

        sumRight = [0] * numsSize
        sumRight[numsSize - 1] = nums[numsSize - 1]
        for i in range(numsSize - 2, -1, -1):
            sumRight[i] = sumRight[i + 1] + nums[i]

        for i in range(numsSize):
            if sumLeft[i] == sumRight[i]:
                retVal = i
                break

        return retVal
```

</details>

## [974. Subarray Sums Divisible by K](https://leetcode.com/problems/subarray-sums-divisible-by-k/)  1675

- [Official](https://leetcode.com/problems/subarray-sums-divisible-by-k/editorial/)
- [Official](https://leetcode.cn/problems/subarray-sums-divisible-by-k/solutions/187947/he-ke-bei-k-zheng-chu-de-zi-shu-zu-by-leetcode-sol/)

<details><summary>Description</summary>

```text
Given an integer array nums and an integer k, return the number of non-empty subarrays that have a sum divisible by k.

A subarray is a contiguous part of an array.

Example 1:
Input: nums = [4,5,0,-2,-3,1], k = 5
Output: 7
Explanation: There are 7 subarrays with a sum divisible by k = 5:
[4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]

Example 2:
Input: nums = [5], k = 9
Output: 0

Constraints:
1 <= nums.length <= 3 * 10^4
-10^4 <= nums[i] <= 10^4
2 <= k <= 10^4
```

</details>

<details><summary>C</summary>

```c
int subarraysDivByK(int* nums, int numsSize, int k) {
    int retVal = 0;

    int modRecord[k];
    memset(modRecord, 0, sizeof(modRecord));
    modRecord[0] = 1;

    int prefixSumMod = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        prefixSumMod = (prefixSumMod + nums[i] % k + k) % k;
        retVal += modRecord[prefixSumMod];
        modRecord[prefixSumMod]++;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int subarraysDivByK(vector<int>& nums, int k) {
        int retVal = 0;

        vector<int> modRecord(k, 0);
        modRecord[0] = 1;

        int prefixSumMod = 0;
        for (int num : nums) {
            prefixSumMod = (prefixSumMod + num % k + k) % k;
            retVal += modRecord[prefixSumMod];
            modRecord[prefixSumMod]++;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def subarraysDivByK(self, nums: List[int], k: int) -> int:
        retVal = 0

        modRecord = [0] * k
        modRecord[0] = 1

        prefixSumMod = 0
        for num in nums:
            prefixSumMod = (prefixSumMod + num % k + k) % k
            retVal += modRecord[prefixSumMod]
            modRecord[prefixSumMod] += 1

        return retVal
```

</details>

## [1310. XOR Queries of a Subarray](https://leetcode.com/problems/xor-queries-of-a-subarray/)  1459

- [Official](https://leetcode.com/problems/xor-queries-of-a-subarray/editorial/)
- [Official](https://leetcode.cn/problems/xor-queries-of-a-subarray/solutions/101717/zi-shu-zu-yi-huo-cha-xun-by-leetcode-solution/)

<details><summary>Description</summary>

```text
You are given an array arr of positive integers.
You are also given the array queries where queries[i] = [lefti, righti].

For each query i compute the XOR of elements from lefti to righti
(that is, arr[lefti] XOR arr[lefti + 1] XOR ... XOR arr[righti] ).

Return an array answer where answer[i] is the answer to the ith query.

Example 1:
Input: arr = [1,3,4,8], queries = [[0,1],[1,2],[0,3],[3,3]]
Output: [2,7,14,8]
Explanation:
The binary representation of the elements in the array are:
1 = 0001
3 = 0011
4 = 0100
8 = 1000
The XOR values for queries are:
[0,1] = 1 xor 3 = 2
[1,2] = 3 xor 4 = 7
[0,3] = 1 xor 3 xor 4 xor 8 = 14
[3,3] = 8

Example 2:
Input: arr = [4,8,2,10], queries = [[2,3],[1,3],[0,0],[0,3]]
Output: [8,0,4,4]

Constraints:
1 <= arr.length, queries.length <= 3 * 10^4
1 <= arr[i] <= 10^9
queries[i].length == 2
0 <= lefti <= righti < arr.length
```

<details><summary>Hint</summary>

```text
1. What is the result of x ^ y ^ x ?
2. Compute the prefix sum for XOR.
3. Process the queries with the prefix sum values.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* xorQueries(int* arr, int arrSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    int i;

    int prefixSum[arrSize + 1];
    memset(prefixSum, 0, sizeof(prefixSum));
    for (i = 0; i < arrSize; ++i) {
        prefixSum[i + 1] = prefixSum[i] ^ arr[i];
    }

    pRetVal = (int*)malloc(queriesSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (queriesSize * sizeof(int)));
    for (i = 0; i < queriesSize; ++i) {
        pRetVal[i] = prefixSum[queries[i][1] + 1] ^ prefixSum[queries[i][0]];
        (*returnSize) += 1;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
        vector<int> retVal;

        int arrSize = arr.size();
        int prefixSumSize = arrSize + 1;
        vector<int> prefixSum(prefixSumSize, 0);
        for (int i = 0; i < arrSize; ++i) {
            prefixSum[i + 1] = prefixSum[i] ^ arr[i];
        }

        int queriesSize = queries.size();
        for (int i = 0; i < queriesSize; ++i) {
            retVal.emplace_back(prefixSum[queries[i][1] + 1] ^ prefixSum[queries[i][0]]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def xorQueries(self, arr: List[int], queries: List[List[int]]) -> List[int]:
        retVal = []

        prefixSum = [0]
        for key, value in enumerate(arr):
            prefixSum.append(prefixSum[key] ^ arr[key])

        for query in queries:
            retVal.append(prefixSum[query[1]+1] ^ prefixSum[query[0]])

        return retVal
```

</details>

## [1352. Product of the Last K Numbers](https://leetcode.com/problems/product-of-the-last-k-numbers/)  1473

- [Official](https://leetcode.com/problems/product-of-the-last-k-numbers/editorial/)
- [Official](https://leetcode.cn/problems/product-of-the-last-k-numbers/solutions/101222/zui-hou-k-ge-shu-de-cheng-ji-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Design an algorithm that accepts a stream of integers and retrieves the product of the last k integers of the stream.

Implement the ProductOfNumbers class:
- ProductOfNumbers()
  Initializes the object with an empty stream.
- void add(int num)
  Appends the integer num to the stream.
- int getProduct(int k)
  Returns the product of the last k numbers in the current list.
  You can assume that always the current list has at least k numbers.

The test cases are generated so that, at any time,
the product of any contiguous sequence of numbers will fit into a single 32-bit integer without overflowing.

Example:
Input
["ProductOfNumbers","add","add","add","add","add","getProduct","getProduct","getProduct","add","getProduct"]
[[],[3],[0],[2],[5],[4],[2],[3],[4],[8],[2]]
Output
[null,null,null,null,null,null,20,40,0,null,32]
Explanation
ProductOfNumbers productOfNumbers = new ProductOfNumbers();
productOfNumbers.add(3);        // [3]
productOfNumbers.add(0);        // [3,0]
productOfNumbers.add(2);        // [3,0,2]
productOfNumbers.add(5);        // [3,0,2,5]
productOfNumbers.add(4);        // [3,0,2,5,4]
productOfNumbers.getProduct(2); // return 20. The product of the last 2 numbers is 5 * 4 = 20
productOfNumbers.getProduct(3); // return 40. The product of the last 3 numbers is 2 * 5 * 4 = 40
productOfNumbers.getProduct(4); // return 0. The product of the last 4 numbers is 0 * 2 * 5 * 4 = 0
productOfNumbers.add(8);        // [3,0,2,5,4,8]
productOfNumbers.getProduct(2); // return 32. The product of the last 2 numbers is 4 * 8 = 32

Constraints:
0 <= num <= 100
1 <= k <= 4 * 10^4
At most 4 * 10^4 calls will be made to add and getProduct.
The product of the stream at any point in time will fit in a 32-bit integer.

Follow-up: Can you implement both GetProduct and Add to work in O(1) time complexity instead of O(k) time complexity?
```

<details><summary>Hint</summary>

```text
1. Keep all prefix products of numbers in an array, then calculate the product of last K elements in O(1) complexity.
2. When a zero number is added, clean the array of prefix products.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MAX_PRODUCT_SIZE (int)(4 * 10000)
// Stores cumulative product of the stream
typedef struct {
    int prefixProduct[MAX_PRODUCT_SIZE];
    int index;
    int size;
} ProductOfNumbers;
ProductOfNumbers* productOfNumbersCreate() {
    ProductOfNumbers* pRetVal = (ProductOfNumbers*)malloc(sizeof(ProductOfNumbers));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal->prefixProduct, 0, (MAX_PRODUCT_SIZE * sizeof(int)));
    pRetVal->index = 0;
    pRetVal->size = 0;

    // Initialize the product list with 1 to handle multiplication logic
    pRetVal->prefixProduct[pRetVal->index] = 1;
    pRetVal->size += 1;

    return pRetVal;
}
void productOfNumbersAdd(ProductOfNumbers* obj, int num) {
    if (num == 0) {
        // If num is 0, reset the cumulative products since multiplication with 0 invalidates previous products
        obj->index = 0;
        obj->prefixProduct[obj->index] = 1;
        obj->size = 1;
    } else {
        // Append the cumulative product of the current number with the last product
        obj->prefixProduct[obj->size] = obj->prefixProduct[obj->index] * num;
        obj->index += 1;
        obj->size += 1;
    }
}
int productOfNumbersGetProduct(ProductOfNumbers* obj, int k) {
    int retVal = 0;

    // Check if the requested product length exceeds the size of the valid product list
    if (k > obj->index) {
        return retVal;
    }
    // Compute the product of the last k elements using division
    retVal = obj->prefixProduct[obj->index] / obj->prefixProduct[obj->index - k];

    return retVal;
}
void productOfNumbersFree(ProductOfNumbers* obj) {
    free(obj);
    obj = NULL;
}
/**
 * Your ProductOfNumbers struct will be instantiated and called as such:
 * ProductOfNumbers* obj = productOfNumbersCreate();
 * productOfNumbersAdd(obj, num);
 * int param_2 = productOfNumbersGetProduct(obj, k);
 * productOfNumbersFree(obj);
 */
```

</details>

<details><summary>C++</summary>

```c++
class ProductOfNumbers {
   private:
    // Stores cumulative product of the stream
    vector<int> prefixProduct;
    int size = 0;

   public:
    ProductOfNumbers() {
        // Initialize the product list with 1 to handle multiplication logic
        prefixProduct.push_back(1);
        size = 0;
    }
    void add(int num) {
        if (num == 0) {
            // If num is 0, reset the cumulative products since multiplication with 0 invalidates previous products
            prefixProduct = {1};
            size = 0;
        } else {
            // Append the cumulative product of the current number with the last product
            prefixProduct.push_back(prefixProduct[size] * num);
            size++;
        }
    }
    int getProduct(int k) {
        int retVal = 0;

        // Check if the requested product length exceeds the size of the valid product list
        if (k > size) {
            return retVal;
        }
        // Compute the product of the last k elements using division
        retVal = prefixProduct[size] / prefixProduct[size - k];

        return retVal;
    }
};
/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */
```

</details>

<details><summary>Python3</summary>

```python
class ProductOfNumbers:
    def __init__(self):
        # Stores cumulative product of the stream
        # Initialize the product list with 1 to handle multiplication logic
        self.prefixProduct = [1]
        self.size = 0

    def add(self, num: int) -> None:
        if num == 0:
            # If num is 0, reset the cumulative products since multiplication with 0 invalidates previous products
            self.prefixProduct = [1]
            self.size = 0
        else:
            # Append the cumulative product of the current number with the last product
            self.prefixProduct.append(self.prefixProduct[self.size] * num)
            self.size += 1

    def getProduct(self, k: int) -> int:
        retVal = 0

        # Check if the requested product length exceeds the size of the valid product list
        if k > self.size:
            return retVal
        # Compute the product of the last k elements using division
        retVal = self.prefixProduct[self.size] // self.prefixProduct[self.size - k]

        return retVal


# Your ProductOfNumbers object will be instantiated and called as such:
# obj = ProductOfNumbers()
# obj.add(num)
# param_2 = obj.getProduct(k)
```

</details>

## [1371. Find the Longest Substring Containing Vowels in Even Counts](https://leetcode.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/)  2040

- [Official](https://leetcode.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/editorial/)
- [Official](https://leetcode.cn/problems/find-the-longest-substring-containing-vowels-in-even-counts/solutions/238567/mei-ge-yuan-yin-bao-han-ou-shu-ci-de-zui-chang-z-2/)

<details><summary>Description</summary>

```text
Given the string s, return the size of the longest substring containing each vowel an even number of times.
That is, 'a', 'e', 'i', 'o', and 'u' must appear an even number of times.

Example 1:
Input: s = "eleetminicoworoep"
Output: 13
Explanation: The longest substring is "leetminicowor"
which contains two each of the vowels: e, i and o and zero of the vowels: a and u.

Example 2:
Input: s = "leetcodeisgreat"
Output: 5
Explanation: The longest substring is "leetc" which contains two e's.

Example 3:
Input: s = "bcbcbc"
Output: 6
Explanation: In this case,
the given string "bcbcbc" is the longest because all vowels: a, e, i, o and u appear zero times.

Constraints:
1 <= s.length <= 5 x 10^5
s contains only lowercase English letters.
```

<details><summary>Hint</summary>

```text
1. Represent the counts (odd or even) of vowels with a bitmask.
2. Precompute the prefix xor for the bitmask of vowels and then get the longest valid substring.
```

</details>

</details>

<details><summary>C</summary>

```c
int findTheLongestSubstring(char* s) {
    int retVal = 0;

    int characterMap[26];  // s contains only lowercase English letters.
    memset(characterMap, 0, sizeof(characterMap));
    characterMap['a' - 'a'] = 1;
    characterMap['e' - 'a'] = 2;
    characterMap['i' - 'a'] = 4;
    characterMap['o' - 'a'] = 8;
    characterMap['u' - 'a'] = 16;
    int mp[32];  // 1 + 2 + 4 + 8 + 16 = 31 < 32
    memset(mp, -1, sizeof(mp));

    int sSize = strlen(s);
    int prefixXOR = 0;
    int i;
    for (i = 0; i < sSize; ++i) {
        prefixXOR ^= characterMap[s[i] - 'a'];
        if ((mp[prefixXOR] == -1) && (prefixXOR != 0)) {
            mp[prefixXOR] = i;
        }
        retVal = fmax(retVal, i - mp[prefixXOR]);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int findTheLongestSubstring(string s) {
        int retVal = 0;

        vector<int> characterMap(26, 0);  // s contains only lowercase English letters.
        characterMap['a' - 'a'] = 1;
        characterMap['e' - 'a'] = 2;
        characterMap['i' - 'a'] = 4;
        characterMap['o' - 'a'] = 8;
        characterMap['u' - 'a'] = 16;
        vector<int> mp(32, -1);  // 1 + 2 + 4 + 8 + 16 = 31 < 32

        int sSize = s.size();
        int prefixXOR = 0;
        for (int i = 0; i < sSize; ++i) {
            prefixXOR ^= characterMap[s[i] - 'a'];
            if ((mp[prefixXOR] == -1) && (prefixXOR != 0)) {
                mp[prefixXOR] = i;
            }
            retVal = max(retVal, i - mp[prefixXOR]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def findTheLongestSubstring(self, s: str) -> int:
        retVal = 0

        characterMap = [0] * 26  # s contains only lowercase English letters.
        characterMap[ord("a") - ord("a")] = 1
        characterMap[ord("e") - ord("a")] = 2
        characterMap[ord("i") - ord("a")] = 4
        characterMap[ord("o") - ord("a")] = 8
        characterMap[ord("u") - ord("a")] = 16
        mp = [-1] * 32  # 1+2+4+8+16=31 < 32

        sSize = len(s)
        prefixXOR = 0
        for i in range(sSize):
            prefixXOR ^= characterMap[ord(s[i]) - ord("a")]
            if (mp[prefixXOR] == -1) and (prefixXOR != 0):
                mp[prefixXOR] = i
            retVal = max(retVal, i - mp[prefixXOR])

        return retVal
```

</details>

## [1480. Running Sum of 1d Array](https://leetcode.com/problems/running-sum-of-1d-array/)  1104

- [Official](https://leetcode.com/problems/running-sum-of-1d-array/editorial/)
- [Official](https://leetcode.cn/problems/running-sum-of-1d-array/solutions/962723/yi-wei-shu-zu-de-dong-tai-he-by-leetcode-flkm/)

<details><summary>Description</summary>

```text
Given an array nums. We define a running sum of an array as runningSum[i] = sum(nums[0]…nums[i]).

Return the running sum of nums.

Example 1:
Input: nums = [1,2,3,4]
Output: [1,3,6,10]
Explanation: Running sum is obtained as follows: [1, 1+2, 1+2+3, 1+2+3+4].

Example 2:
Input: nums = [1,1,1,1,1]
Output: [1,2,3,4,5]
Explanation: Running sum is obtained as follows: [1, 1+1, 1+1+1, 1+1+1+1, 1+1+1+1+1].

Example 3:
Input: nums = [3,1,2,10,1]
Output: [3,4,6,16,17]

Constraints:
1 <= nums.length <= 1000
-10^6 <= nums[i] <= 10^6
```

<details><summary>Hint</summary>

```text
1. Think about how we can calculate the i-th number in the running sum from the (i-1)-th number.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* runningSum(int* nums, int numsSize, int* returnSize) {
    int* pRetVal = NULL;

    *returnSize = numsSize;
    pRetVal = (int*)malloc(*returnSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int i = 0;
    pRetVal[i] = nums[i];
    for (i = 1; i < numsSize; ++i) {
        pRetVal[i] = pRetVal[i - 1] + nums[i];
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> runningSum(vector<int>& nums) {
        vector<int> retval;

        retval.push_back(nums[0]);
        for (long unsigned int i = 1; i < nums.size(); ++i) {
            retval.push_back(retval[i - 1] + nums[i]);
        }

        return retval;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def runningSum(self, nums: List[int]) -> List[int]:
        retVal = []

        retVal.append(nums[0])
        for i in range(1, len(nums)):
            retVal.append(retVal[i-1] + nums[i])

        return retVal
```

</details>

## [1524. Number of Sub-arrays With Odd Sum](https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum/)  1610

- [Official](https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum/editorial/)
- [Official](https://leetcode.cn/problems/number-of-sub-arrays-with-odd-sum/solutions/357914/he-wei-qi-shu-de-zi-shu-zu-shu-mu-by-leetcode-solu/)

<details><summary>Description</summary>

```text
Given an array of integers arr, return the number of subarrays with an odd sum.

Since the answer can be very large, return it modulo 10^9 + 7.

Example 1:
Input: arr = [1,3,5]
Output: 4
Explanation: All subarrays are [[1],[1,3],[1,3,5],[3],[3,5],[5]]
All sub-arrays sum are [1,4,9,3,8,5].
Odd sums are [1,9,3,5] so the answer is 4.

Example 2:
Input: arr = [2,4,6]
Output: 0
Explanation: All subarrays are [[2],[2,4],[2,4,6],[4],[4,6],[6]]
All sub-arrays sum are [2,6,12,4,10,6].
All sub-arrays have even sum and the answer is 0.

Example 3:
Input: arr = [1,2,3,4,5,6,7]
Output: 16

Constraints:
1 <= arr.length <= 10^5
1 <= arr[i] <= 100
```

<details><summary>Hint</summary>

```text
1. Can we use the accumulative sum to keep track of all the odd-sum sub-arrays ?
2. if the current accu sum is odd, we care only about previous even accu sums and vice versa.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MODULO (int)(1e9 + 7)  // Since the answer can be very large, return it modulo 10^9 + 7.
int numOfSubarrays(int* arr, int arrSize) {
    int retVal = 0;

    int prefixSum = 0;
    int oddCount = 0;
    int evenCount = 1;  // evenCount starts as 1 since the initial sum (0) is even
    for (int i = 0; i < arrSize; ++i) {
        prefixSum += arr[i];
        if (prefixSum % 2 == 0) {  // If current prefix sum is even, add the number of odd subarrays
            retVal += oddCount;
            evenCount++;
        } else {  // If current prefix sum is odd, add the number of even subarrays
            retVal += evenCount;
            oddCount++;
        }

        retVal %= MODULO;  // To handle large results
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define MODULO (int)(1e9 + 7)  // Since the answer can be very large, return it modulo 10^9 + 7.
   public:
    int numOfSubarrays(vector<int>& arr) {
        int retVal = 0;

        int prefixSum = 0;
        int oddCount = 0;
        int evenCount = 1;  // evenCount starts as 1 since the initial sum (0) is even
        for (int num : arr) {
            prefixSum += num;
            if (prefixSum % 2 == 0) {  // If current prefix sum is even, add the number of odd subarrays
                retVal += oddCount;
                evenCount++;
            } else {  // If current prefix sum is odd, add the number of even subarrays
                retVal += evenCount;
                oddCount++;
            }

            retVal %= MODULO;  // To handle large results
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
        self.MODULO = 10 ** 9 + 7   # Since the answer can be very large, return it modulo 10^9 + 7.

    def numOfSubarrays(self, arr: List[int]) -> int:
        retVal = 0

        prefixSum = 0
        oddCount = 0
        evenCount = 1  # evenCount starts as 1 since the initial sum (0) is even
        for num in arr:
            prefixSum += num
            if prefixSum % 2 == 0:  # If current prefix sum is even, add the number of odd subarrays
                retVal += oddCount
                evenCount += 1
            else:  # If current prefix sum is odd, add the number of even subarrays
                retVal += evenCount
                oddCount += 1

            retVal %= self.MODULO  # To handle large results

        return retVal
```

</details>

## [1590. Make Sum Divisible by P](https://leetcode.com/problems/make-sum-divisible-by-p/)  2038

- [Official](https://leetcode.com/problems/make-sum-divisible-by-p/editorial/)
- [Official](https://leetcode.cn/problems/make-sum-divisible-by-p/solutions/2157277/shi-shu-zu-he-neng-bei-p-zheng-chu-by-le-dob9/)

<details><summary>Description</summary>

```text
Given an array of positive integers nums, remove the smallest subarray (possibly empty)
such that the sum of the remaining elements is divisible by p.
It is not allowed to remove the whole array.

Return the length of the smallest subarray that you need to remove, or -1 if it's impossible.

A subarray is defined as a contiguous block of elements in the array.

Example 1:
Input: nums = [3,1,4,2], p = 6
Output: 1
Explanation: The sum of the elements in nums is 10, which is not divisible by 6.
We can remove the subarray [4], and the sum of the remaining elements is 6, which is divisible by 6.

Example 2:
Input: nums = [6,3,5,2], p = 9
Output: 2
Explanation: We cannot remove a single element to get a sum divisible by 9.
The best way is to remove the subarray [5,2], leaving us with [6,3] with sum 9.

Example 3:
Input: nums = [1,2,3], p = 3
Output: 0
Explanation: Here the sum is 6. which is already divisible by 3. Thus we do not need to remove anything.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
1 <= p <= 10^9
```

<details><summary>Hint</summary>

```text
1. Use prefix sums to calculate the subarray sums.
2. Suppose you know the remainder for the sum of the entire array. How does removing a subarray affect that remainder?
   What remainder does the subarray need to have in order to make the rest of the array sum up to be divisible by k?
3. Use a map to keep track of the rightmost index for every prefix sum % p.
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
void freeAll(struct hashTable *pFree) {
    struct hashTable *current;
    struct hashTable *tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int minSubarray(int *nums, int numsSize, int p) {
    int retVal = 0;

    // Step 1: Calculate total sum and target remainder
    int totalSum = 0;
    for (int i = 0; i < numsSize; ++i) {
        totalSum = (totalSum + nums[i]) % p;
    }
    int target = totalSum % p;
    if (target == 0) {  // The array is already divisible by p
        return retVal;
    }

    // Step 2: Use a hash map to track prefix sum mod p
    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp = NULL;
    pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
    if (pTemp == NULL) {
        perror("malloc");
        freeAll(pHashTable);
        return retVal;
    }
    pTemp->key = 0;
    pTemp->value = -1;
    HASH_ADD_INT(pHashTable, key, pTemp);

    // Step 3: Iterate over the array
    retVal = numsSize;
    int needed;
    int currentSum = 0;
    for (int i = 0; i < numsSize; ++i) {
        currentSum = (currentSum + nums[i]) % p;

        needed = (currentSum - target + p) % p;  // Calculate what we need to remove
        // If we have seen the needed remainder, we can consider this subarray
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &needed, pTemp);
        if (pTemp != NULL) {
            retVal = fmin(retVal, i - pTemp->value);
        }

        // Store the current remainder and index
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &currentSum, pTemp);
        if (pTemp == NULL) {
            pTemp = NULL;
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                return retVal;
            }
            pTemp->key = currentSum;
            pTemp->value = i;
            HASH_ADD_INT(pHashTable, key, pTemp);
        } else {
            pTemp->value = i;
        }
    }

    if (retVal == numsSize) {
        retVal = -1;
    }

    //
    freeAll(pHashTable);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minSubarray(vector<int>& nums, int p) {
        int retVal = 0;

        int numsSize = nums.size();

        // Step 1: Calculate total sum and target remainder
        int totalSum = 0;
        for (int num : nums) {
            totalSum = (totalSum + num) % p;
        }
        int target = totalSum % p;
        if (target == 0) {  // The array is already divisible by p
            return retVal;
        }

        // Step 2: Use a hash map to track prefix sum mod p
        unordered_map<int, int> modMap;
        modMap[0] = -1;  // To handle the case where the whole prefix is the answer

        // Step 3: Iterate over the array
        retVal = numsSize;
        int currentSum = 0;
        for (int i = 0; i < numsSize; ++i) {
            currentSum = (currentSum + nums[i]) % p;

            int needed = (currentSum - target + p) % p;  // Calculate what we need to remove
            // If we have seen the needed remainder, we can consider this subarray
            if (modMap.find(needed) != modMap.end()) {
                retVal = min(retVal, i - modMap[needed]);
            }

            modMap[currentSum] = i;  // Store the current remainder and index
        }

        if (retVal == numsSize) {
            retVal = -1;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minSubarray(self, nums: List[int], p: int) -> int:
        retVal = 0

        numsSize = len(nums)

        # Step 1: Calculate total sum and target remainder
        totalSum = 0
        for num in nums:
            totalSum = (totalSum + num) % p
        target = totalSum % p
        if target == 0:
            return retVal  # The array is already divisible by p

        # Step 2: Use a dict to track prefix sum mod p
        modMap = {0: -1}    # To handle the case where the whole prefix is the answer

        # Step 3: Iterate over the array
        retVal = numsSize
        currentSum = 0
        for i in range(numsSize):
            currentSum = (currentSum + nums[i]) % p

            needed = (currentSum - target + p) % p  # Calculate what we need to remove
            # If we have seen the needed remainder, we can consider this subarray
            if needed in modMap:
                retVal = min(retVal, i - modMap[needed])

            modMap[currentSum] = i  # Store the current remainder and index

        if retVal == numsSize:
            retVal = -1

        return retVal
```

</details>

## [1685. Sum of Absolute Differences in a Sorted Array](https://leetcode.com/problems/sum-of-absolute-differences-in-a-sorted-array/)  1495

- [Official](https://leetcode.com/problems/sum-of-absolute-differences-in-a-sorted-array/editorial/)

<details><summary>Description</summary>

```text
You are given an integer array nums sorted in non-decreasing order.

Build and return an integer array result with the same length as nums such that result[i] is equal to
the summation of absolute differences between nums[i] and all the other elements in the array.

In other words, result[i] is equal to sum(|nums[i]-nums[j]|) where 0 <= j < nums.length and j != i (0-indexed).

Example 1:
Input: nums = [2,3,5]
Output: [4,3,5]
Explanation: Assuming the arrays are 0-indexed, then
result[0] = |2-2| + |2-3| + |2-5| = 0 + 1 + 3 = 4,
result[1] = |3-2| + |3-3| + |3-5| = 1 + 0 + 2 = 3,
result[2] = |5-2| + |5-3| + |5-5| = 3 + 2 + 0 = 5.

Example 2:
Input: nums = [1,4,6,8,10]
Output: [24,15,13,15,21]

Constraints:
2 <= nums.length <= 10^5
1 <= nums[i] <= nums[i + 1] <= 10^4
```

<details><summary>Hint</summary>

```text
1. Absolute difference is the same as max(a, b) - min(a, b).
   How can you use this fact with the fact that the array is sorted?
2. For nums[i], the answer is (nums[i] - nums[0]) + (nums[i] - nums[1]) + ... + (nums[i] - nums[i-1])
   + (nums[i+1] - nums[i]) + (nums[i+2] - nums[i]) + ... + (nums[n-1] - nums[i]).
3. It can be simplified to (nums[i] * i - (nums[0] + nums[1] + ... + nums[i-1]))
   + ((nums[i+1] + nums[i+2] + ... + nums[n-1]) - nums[i] * (n-i-1)).
   One can build prefix and suffix sums to compute this quickly.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *getSumAbsoluteDifferences(int *nums, int numsSize, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;
    int i;

    pRetVal = (int *)malloc(numsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (numsSize * sizeof(int)));

    int prefixSum[numsSize];
    memset(prefixSum, 0, sizeof(prefixSum));
    prefixSum[0] = nums[0];
    for (i = 1; i < numsSize; ++i) {
        prefixSum[i] = prefixSum[i - 1] + nums[i];
    }

    int left, right;
    for (i = 0; i < numsSize; ++i) {
        left = (nums[i] * i) - (prefixSum[i] - nums[i]);
        right = (prefixSum[numsSize - 1] - prefixSum[i]) - (nums[i] * (numsSize - 1 - i));
        pRetVal[(*returnSize)++] = left + right;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> getSumAbsoluteDifferences(vector<int>& nums) {
        vector<int> retVal;

        int numsSize = nums.size();

        vector<int> prefixSum;
        prefixSum.emplace_back(nums[0]);
        for (int i = 1; i < numsSize; ++i) {
            prefixSum.emplace_back(prefixSum[i - 1] + nums[i]);
        }

        for (int i = 0; i < numsSize; ++i) {
            int left = (nums[i] * i) - (prefixSum[i] - nums[i]);
            int right = (prefixSum[numsSize - 1] - prefixSum[i]) - (nums[i] * (numsSize - 1 - i));
            retVal.emplace_back(left + right);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def getSumAbsoluteDifferences(self, nums: List[int]) -> List[int]:
        retVal = []

        numsSize = len(nums)

        prefixSum = [nums[0]]
        for i in range(1, numsSize):
            prefixSum.append(prefixSum[-1] + nums[i])

        for i in range(numsSize):
            left = (nums[i] * i) - (prefixSum[i] - nums[i])
            right = (prefixSum[-1] - prefixSum[i]) - (nums[i] * (numsSize - 1 - i))
            retVal.append(left + right)

        return retVal
```

</details>

## [1732. Find the Highest Altitude](https://leetcode.com/problems/find-the-highest-altitude/)  1256

- [Official](https://leetcode.com/problems/find-the-highest-altitude/editorial/)
- [Official](https://leetcode.cn/problems/find-the-highest-altitude/solutions/1977801/zhao-dao-zui-gao-hai-ba-by-leetcode-solu-l01c/)

<details><summary>Description</summary>

```text
There is a biker going on a road trip.
The road trip consists of n + 1 points at different altitudes.
The biker starts his trip on point 0 with altitude equal 0.

You are given an integer array gain of length n
where gain[i] is the net gain in altitude between points i​​​​​​ and i + 1 for all (0 <= i < n).
Return the highest altitude of a point.

Example 1:
Input: gain = [-5,1,5,0,-7]
Output: 1
Explanation: The altitudes are [0,-5,-4,1,1,-6]. The highest is 1.

Example 2:
Input: gain = [-4,-3,-2,-1,4,3,2]
Output: 0
Explanation: The altitudes are [0,-4,-7,-9,-10,-6,-3,-1]. The highest is 0.

Constraints:
n == gain.length
1 <= n <= 100
-100 <= gain[i] <= 100
```

<details><summary>Hint</summary>

```text
1. Let's note that the altitude of an element is the sum of gains of all the elements behind it
2. Getting the altitudes can be done by getting the prefix sum array of the given array
```

</details>

</details>

<details><summary>C</summary>

```c
int largestAltitude(int* gain, int gainSize) {
    int retVal = 0;

    int prefixSum = retVal;
    int i;
    for (i = 0; i < gainSize; ++i) {
        prefixSum += gain[i];
        retVal = fmax(retVal, prefixSum);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int largestAltitude(vector<int>& gain) {
        int retVal = 0;

        int prefixSum = retVal;
        for (auto iterator : gain) {
            prefixSum += iterator;
            retVal = max(retVal, prefixSum);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def largestAltitude(self, gain: List[int]) -> int:
        retVal = 0

        prefixSum = retVal
        for i in gain:
            prefixSum += i
            retVal = max(retVal, prefixSum)

        return retVal
```

</details>

## [1749. Maximum Absolute Sum of Any Subarray](https://leetcode.com/problems/maximum-absolute-sum-of-any-subarray/)  1541

- [Official](https://leetcode.com/problems/maximum-absolute-sum-of-any-subarray/editorial/)
- [Official](https://leetcode.cn/problems/maximum-absolute-sum-of-any-subarray/solutions/2372374/ren-yi-zi-shu-zu-he-de-jue-dui-zhi-de-zu-qerr/)

<details><summary>Description</summary>

```text
You are given an integer array nums.
The absolute sum of a subarray [numsl, numsl+1, ..., numsr-1, numsr] is abs(numsl + numsl+1 + ... + numsr-1 + numsr).

Return the maximum absolute sum of any (possibly empty) subarray of nums.

Note that abs(x) is defined as follows:
- If x is a negative integer, then abs(x) = -x.
- If x is a non-negative integer, then abs(x) = x.

Example 1:
Input: nums = [1,-3,2,3,-4]
Output: 5
Explanation: The subarray [2,3] has absolute sum = abs(2+3) = abs(5) = 5.

Example 2:
Input: nums = [2,-5,1,-4,3,-2]
Output: 8
Explanation: The subarray [-5,1,-4] has absolute sum = abs(-5+1-4) = abs(-8) = 8.

Constraints:
1 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4
```

<details><summary>Hint</summary>

```text
1. What if we asked for maximum sum, not absolute sum?
2. It's a standard problem that can be solved by Kadane's algorithm.
3. The key idea is the max absolute sum will be either the max sum or the min sum.
4. So just run kadane twice, once calculating the max sum and once calculating the min sum.
```

</details>

</details>

<details><summary>C</summary>

```c
int maxAbsoluteSum(int* nums, int numsSize) {
    int retVal = 0;

    int prefixSum = 0;
    int minPrefixSum = 0;
    int maxPrefixSum = 0;
    for (int i = 0; i < numsSize; ++i) {
        prefixSum += nums[i];
        minPrefixSum = fmin(minPrefixSum, prefixSum);
        maxPrefixSum = fmax(maxPrefixSum, prefixSum);
    }
    retVal = maxPrefixSum - minPrefixSum;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxAbsoluteSum(vector<int>& nums) {
        int retVal = 0;

        int prefixSum = 0;
        int minPrefixSum = 0;
        int maxPrefixSum = 0;
        for (int num : nums) {
            prefixSum += num;
            minPrefixSum = min(minPrefixSum, prefixSum);
            maxPrefixSum = max(maxPrefixSum, prefixSum);
        }
        retVal = maxPrefixSum - minPrefixSum;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxAbsoluteSum(self, nums: List[int]) -> int:
        retVal = 0

        prefixSum = 0
        minPrefixSum = 0
        maxPrefixSum = 0
        for num in nums:
            prefixSum += num
            minPrefixSum = min(minPrefixSum, prefixSum)
            maxPrefixSum = max(maxPrefixSum, prefixSum)
        retVal = maxPrefixSum - minPrefixSum

        return retVal
```

</details>

## [1894. Find the Student that Will Replace the Chalk](https://leetcode.com/problems/find-the-student-that-will-replace-the-chalk/)  1355

- [Official](https://leetcode.com/problems/find-the-student-that-will-replace-the-chalk/editorial/)
- [Official](https://leetcode.cn/problems/find-the-student-that-will-replace-the-chalk/solutions/825464/zhao-dao-xu-yao-bu-chong-fen-bi-de-xue-s-qrn1/)

<details><summary>Description</summary>

```text
There are n students in a class numbered from 0 to n - 1.
The teacher will give each student a problem starting with the student number 0, then the student number 1,
and so on until the teacher reaches the student number n - 1.
After that, the teacher will restart the process, starting with the student number 0 again.

You are given a 0-indexed integer array chalk and an integer k. There are initially k pieces of chalk.
When the student number i is given a problem to solve, they will use chalk[i] pieces of chalk to solve that problem.
However, if the current number of chalk pieces is strictly less than chalk[i],
then the student number i will be asked to replace the chalk.

Return the index of the student that will replace the chalk pieces.

Example 1:
Input: chalk = [5,1,5], k = 22
Output: 0
Explanation: The students go in turns as follows:
- Student number 0 uses 5 chalk, so k = 17.
- Student number 1 uses 1 chalk, so k = 16.
- Student number 2 uses 5 chalk, so k = 11.
- Student number 0 uses 5 chalk, so k = 6.
- Student number 1 uses 1 chalk, so k = 5.
- Student number 2 uses 5 chalk, so k = 0.
Student number 0 does not have enough chalk, so they will have to replace it.

Example 2:
Input: chalk = [3,4,1,2], k = 25
Output: 1
Explanation: The students go in turns as follows:
- Student number 0 uses 3 chalk so k = 22.
- Student number 1 uses 4 chalk so k = 18.
- Student number 2 uses 1 chalk so k = 17.
- Student number 3 uses 2 chalk so k = 15.
- Student number 0 uses 3 chalk so k = 12.
- Student number 1 uses 4 chalk so k = 8.
- Student number 2 uses 1 chalk so k = 7.
- Student number 3 uses 2 chalk so k = 5.
- Student number 0 uses 3 chalk so k = 2.
Student number 1 does not have enough chalk, so they will have to replace it.

Constraints:
chalk.length == n
1 <= n <= 10^5
1 <= chalk[i] <= 10^5
1 <= k <= 10^9
```

<details><summary>Hint</summary>

```text
1. Subtract the sum of chalk from k until k is less than the sum of chalk.
2. Now iterate over the array. If chalk[i] is less than k, this is the answer.
   Otherwise, subtract chalk[i] from k and continue.
```

</details>

</details>

<details><summary>C</summary>

```c
int chalkReplacer(int* chalk, int chalkSize, int k) {
    int retVal = 0;

    int i;

    long long total = 0;
    for (i = 0; i < chalkSize; ++i) {
        total += chalk[i];
    }
    k %= total;

    for (i = 0; i < chalkSize; ++i) {
        if (chalk[i] > k) {
            retVal = i;
            break;
        }
        k -= chalk[i];
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int chalkReplacer(vector<int>& chalk, int k) {
        int retVal = 0;

        long long total = accumulate(chalk.begin(), chalk.end(), 0LL);
        k %= total;

        int chalkSize = chalk.size();
        for (int i = 0; i < chalkSize; ++i) {
            if (chalk[i] > k) {
                retVal = i;
                break;
            }
            k -= chalk[i];
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def chalkReplacer(self, chalk: List[int], k: int) -> int:
        retVal = 0

        total = sum(chalk)
        k = k % total

        for key, value in enumerate(chalk):
            if value > k:
                retVal = key
                break
            k -= value

        return retVal
```

</details>

## [1895. Largest Magic Square](https://leetcode.com/problems/largest-magic-square/)  1781

- [Official](https://leetcode.com/problems/largest-magic-square/editorial/)
- [Official](https://leetcode.cn/problems/largest-magic-square/solutions/825471/zui-da-de-huan-fang-by-leetcode-solution-p8a1/)

<details><summary>Description</summary>

```text
A k x k magic square is a k x k grid filled with integers such that every row sum,
every column sum, and both diagonal sums are all equal.
The integers in the magic square do not have to be distinct. Every 1 x 1 grid is trivially a magic square.

Given an m x n integer grid,
return the size (i.e., the side length k) of the largest magic square that can be found within this grid.

Example 1:
Input: grid = [[7,1,4,5,6],[2,5,1,6,4],[1,5,4,3,2],[1,2,7,3,4]]
Output: 3
Explanation:
The largest magic square has a size of 3.
Every row sum, column sum, and diagonal sum of this magic square is equal to 12.
- Row sums: 5+1+6 = 5+4+3 = 2+7+3 = 12
- Column sums: 5+5+2 = 1+4+7 = 6+3+3 = 12
- Diagonal sums: 5+4+3 = 6+4+2 = 12

Example 2:
Input: grid = [[5,1,3,1],[9,3,3,1],[1,3,3,8]]
Output: 2

Constraints:
m == grid.length
n == grid[i].length
1 <= m, n <= 50
1 <= grid[i][j] <= 10^6
```

<details><summary>Hint</summary>

```text
1. Check all squares in the matrix and find the largest one.
```

</details>

</details>

<details><summary>C</summary>

```c
int largestMagicSquare(int** grid, int gridSize, int* gridColSize) {
    int retVal = 1;

    int rowSize = gridSize;
    int colSize = gridColSize[0];

    // prefix sum of each row
    int rowsum[rowSize][colSize];
    for (int i = 0; i < rowSize; ++i) {
        rowsum[i][0] = grid[i][0];
        for (int j = 1; j < colSize; ++j) {
            rowsum[i][j] = rowsum[i][j - 1] + grid[i][j];
        }
    }
    // prefix sum of each column
    int colsum[rowSize][colSize];
    for (int j = 0; j < colSize; ++j) {
        colsum[0][j] = grid[0][j];
        for (int i = 1; i < rowSize; ++i) {
            colsum[i][j] = colsum[i - 1][j] + grid[i][j];
        }
    }

    int min_edge = rowSize < colSize ? rowSize : colSize;
    // enumerate edge lengths from largest to smallest
    for (int edge = min_edge; edge >= 2; --edge) {
        // enumerate the top-left corner position (i,j) of the square
        for (int i = 0; i + edge <= rowSize; ++i) {
            for (int j = 0; j + edge <= colSize; ++j) {
                // calculate the standard value
                int stdsum = rowsum[i][j + edge - 1] - (j > 0 ? rowsum[i][j - 1] : 0);
                int check = 1;

                // check each row
                for (int ii = i + 1; ii < i + edge; ++ii) {
                    int sum = rowsum[ii][j + edge - 1] - (j > 0 ? rowsum[ii][j - 1] : 0);
                    if (sum != stdsum) {
                        check = 0;
                        break;
                    }
                }
                if (check == 0) {
                    continue;
                }

                // check each column
                for (int jj = j; jj < j + edge; ++jj) {
                    int sum = colsum[i + edge - 1][jj] - (i > 0 ? colsum[i - 1][jj] : 0);
                    if (sum != stdsum) {
                        check = 0;
                        break;
                    }
                }
                if (check == 0) {
                    continue;
                }

                // check the diagonal
                int d1 = 0;
                int d2 = 0;
                for (int k = 0; k < edge; ++k) {
                    d1 += grid[i + k][j + k];
                    d2 += grid[i + k][j + edge - 1 - k];
                }
                if ((d1 == stdsum) && (d2 == stdsum)) {
                    retVal = edge;
                    return retVal;
                }
            }
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
    int largestMagicSquare(vector<vector<int>>& grid) {
        int retVal = 1;

        int rowSize = grid.size();
        int colSize = grid[0].size();

        // prefix sum of each row
        vector<vector<int>> rowsum(rowSize, vector<int>(colSize));
        for (int i = 0; i < rowSize; ++i) {
            rowsum[i][0] = grid[i][0];
            for (int j = 1; j < colSize; ++j) {
                rowsum[i][j] = rowsum[i][j - 1] + grid[i][j];
            }
        }
        // prefix sum of each column
        vector<vector<int>> colsum(rowSize, vector<int>(colSize));
        for (int j = 0; j < colSize; ++j) {
            colsum[0][j] = grid[0][j];
            for (int i = 1; i < rowSize; ++i) {
                colsum[i][j] = colsum[i - 1][j] + grid[i][j];
            }
        }

        // enumerate edge lengths from largest to smallest
        for (int edge = min(rowSize, colSize); edge >= 2; --edge) {
            // enumerate the top-left corner position (i,j) of the square
            for (int i = 0; i + edge <= rowSize; ++i) {
                for (int j = 0; j + edge <= colSize; ++j) {
                    // the value for each row, column, and diagonal should be calculated (using the first row as a
                    // sample)
                    int stdsum = rowsum[i][j + edge - 1] - (j ? rowsum[i][j - 1] : 0);
                    bool check = true;

                    // enumerate each row and directly compute the sum using prefix sums since we have already used the
                    // first line as a sample, we can skip the first line here.
                    for (int ii = i + 1; ii < i + edge; ++ii) {
                        if (rowsum[ii][j + edge - 1] - (j ? rowsum[ii][j - 1] : 0) != stdsum) {
                            check = false;
                            break;
                        }
                    }
                    if (check == false) {
                        continue;
                    }

                    // enumerate each column and directly calculate the sum using prefix sums
                    for (int jj = j; jj < j + edge; ++jj) {
                        if (colsum[i + edge - 1][jj] - (i ? colsum[i - 1][jj] : 0) != stdsum) {
                            check = false;
                            break;
                        }
                    }
                    if (check == false) {
                        continue;
                    }

                    // d1 and d2 represent the sums of the two diagonals respectively. here d denotes diagonal
                    int d1 = 0;
                    int d2 = 0;
                    // sum directly by traversing without using the prefix sum.
                    for (int k = 0; k < edge; ++k) {
                        d1 += grid[i + k][j + k];
                        d2 += grid[i + k][j + edge - 1 - k];
                    }
                    if (d1 == stdsum && d2 == stdsum) {
                        retVal = edge;
                        return retVal;
                    }
                }
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
    def largestMagicSquare(self, grid: List[List[int]]) -> int:
        retVal = 1

        rowSize = len(grid)
        colSize = len(grid[0])

        # prefix sum of each row
        rowsum = [[0] * colSize for _ in range(rowSize)]
        for i in range(rowSize):
            rowsum[i][0] = grid[i][0]
            for j in range(1, colSize):
                rowsum[i][j] = rowsum[i][j - 1] + grid[i][j]
        # prefix sum of each column
        colsum = [[0] * colSize for _ in range(rowSize)]
        for j in range(colSize):
            colsum[0][j] = grid[0][j]
            for i in range(1, rowSize):
                colsum[i][j] = colsum[i - 1][j] + grid[i][j]

        # enumerate edge lengths from largest to smallest
        for edge in range(min(rowSize, colSize), 1, -1):
            # enumerate the top-left corner position (i,j) of the square
            for i in range(rowSize - edge + 1):
                for j in range(colSize - edge + 1):
                    # the value for each row, column, and diagonal should be calculated (using the first row as a sample)
                    stdsum = rowsum[i][j + edge - 1] - (0 if j == 0 else rowsum[i][j - 1])
                    check = True

                    # enumerate each row and directly compute the sum using prefix sums
                    # since we have already used the first line as a sample, we can skip the first line here.
                    for ii in range(i + 1, i + edge):
                        if (rowsum[ii][j + edge - 1] - (0 if j == 0 else rowsum[ii][j - 1]) != stdsum):
                            check = False
                            break
                    if not check:
                        continue

                    # enumerate each column and directly calculate the sum using prefix sums
                    for jj in range(j, j + edge):
                        if (colsum[i + edge - 1][jj] - (0 if i == 0 else colsum[i - 1][jj]) != stdsum):
                            check = False
                            break
                    if not check:
                        continue

                    # d1 and d2 represent the sums of the two diagonals respectively.
                    # here d denotes diagonal
                    d1 = 0
                    d2 = 0
                    # sum directly by traversing without using the prefix sum.
                    for k in range(edge):
                        d1 += grid[i + k][j + k]
                        d2 += grid[i + k][j + edge - 1 - k]
                    if (d1 == stdsum) and (d2 == stdsum):
                        retVal = edge
                        return retVal

        return retVal
```

</details>

## [1915. Number of Wonderful Substrings](https://leetcode.com/problems/number-of-wonderful-substrings)  2234

- [Official](https://leetcode.com/problems/number-of-wonderful-substrings/editorial/)
- [Official](https://leetcode.cn/problems/number-of-wonderful-substrings/solutions/847086/zui-mei-zi-zi-fu-chuan-de-shu-mu-by-leet-2j7g/)

<details><summary>Description</summary>

```text
A wonderful string is a string where at most one letter appears an odd number of times.
- For example, "ccjjc" and "abab" are wonderful, but "ab" is not.

Given a string word that consists of the first ten lowercase English letters ('a' through 'j'),
return the number of wonderful non-empty substrings in word.
If the same substring appears multiple times in word, then count each occurrence separately.

A substring is a contiguous sequence of characters in a string.

Example 1:
Input: word = "aba"
Output: 4
Explanation: The four wonderful substrings are underlined below:
- "aba" -> "a"
- "aba" -> "b"
- "aba" -> "a"
- "aba" -> "aba"

Example 2:
Input: word = "aabb"
Output: 9
Explanation: The nine wonderful substrings are underlined below:
- "aabb" -> "a"
- "aabb" -> "aa"
- "aabb" -> "aab"
- "aabb" -> "aabb"
- "aabb" -> "a"
- "aabb" -> "abb"
- "aabb" -> "b"
- "aabb" -> "bb"
- "aabb" -> "b"

Example 3:
Input: word = "he"
Output: 2
Explanation: The two wonderful substrings are underlined below:
- "he" -> "h"
- "he" -> "e"

Constraints:
1 <= word.length <= 10^5
word consists of lowercase English letters from 'a' to 'j'.
```

<details><summary>Hint</summary>

```text
1. For each prefix of the string,
   check which characters are of even frequency and which are not and represent it by a bitmask.
2. Find the other prefixes whose masks differs from the current prefix mask by at most one bit.
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
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
long long wonderfulSubstrings(char* word) {
    long long retVal = 0;

    struct hashTable* pFrequency = NULL;
    struct hashTable* pTemp = NULL;

    // Create the frequency map : Key = bitmask, Value = frequency of bitmask key
    pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
    if (pTemp == NULL) {
        perror("malloc");
        goto exit;
    }
    pTemp->key = 0;
    pTemp->value = 1;
    HASH_ADD_INT(pFrequency, key, pTemp);

    int bit, odd, bitmask;
    int mask = 0;
    int wordSize = strlen(word);
    int i;
    for (i = 0; i < wordSize; ++i) {
        // a string word that consists of the first ten lowercase English letters
        bit = word[i] - 'a';

        // Flip the parity of the c-th bit in the running prefix mask
        mask ^= (1 << bit);

        // Count smaller prefixes that create substrings with no odd occurring letters
        pTemp = NULL;
        HASH_FIND_INT(pFrequency, &mask, pTemp);
        if (pTemp != NULL) {
            retVal += pTemp->value;
            pTemp->value += 1;
        } else {
            pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                goto exit;
            }
            pTemp->key = mask;
            pTemp->value = 1;
            HASH_ADD_INT(pFrequency, key, pTemp);
        }

        // Loop through every possible letter that can appear an odd number of times in a substring
        for (odd = 0; odd < 10; ++odd) {
            bitmask = mask ^ (1 << odd);
            pTemp = NULL;
            HASH_FIND_INT(pFrequency, &bitmask, pTemp);
            if (pTemp != NULL) {
                retVal += pTemp->value;
            }
        }
    }

exit:
    freeAll(pFrequency);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long wonderfulSubstrings(string word) {
        long long retVal = 0;

        // Create the frequency map : Key = bitmask, Value = frequency of bitmask key
        unordered_map<int, int> frequency;
        frequency[0] = 1;

        int mask = 0;
        for (auto c : word) {
            // a string word that consists of the first ten lowercase English letters
            int bit = c - 'a';

            // Flip the parity of the c-th bit in the running prefix mask
            mask ^= (1 << bit);

            // Count smaller prefixes that create substrings with no odd occurring letters
            auto iterator = frequency.find(mask);
            if (iterator != frequency.end()) {
                retVal += frequency[mask];
                frequency[mask] += 1;
            } else {
                frequency[mask] = 1;
            }

            // Loop through every possible letter that can appear an odd number of times in a substring
            for (int odd = 0; odd < 10; ++odd) {
                int bitmask = mask ^ (1 << odd);
                auto iterator = frequency.find(bitmask);
                if (iterator != frequency.end()) {
                    retVal += frequency[bitmask];
                }
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
    def wonderfulSubstrings(self, word: str) -> int:
        retVal = 0

        # Create the frequency map: Key = bitmask, Value = frequency of bitmask key
        frequency = {}
        frequency[0] = 1

        mask = 0
        for c in word:
            # a string word that consists of the first ten lowercase English letters
            bit = ord(c) - ord('a')

            # Flip the parity of the c-th bit in the running prefix mask
            mask ^= (1 << bit)
            if mask in frequency:   # Count smaller prefixes that create substrings with no odd occurring letters
                retVal += frequency[mask]
                frequency[mask] += 1
            else:
                frequency[mask] = 1

            # Loop through every possible letter that can appear an odd number of times in a substring
            for odd in range(0, 10):
                bitmask = mask ^ (1 << odd)
                if bitmask in frequency:
                    retVal += frequency[bitmask]

        return retVal
```

</details>

## [1991. Find the Middle Index in Array](https://leetcode.com/problems/find-the-middle-index-in-array/)  1302

- [Official](https://leetcode.cn/problems/find-the-middle-index-in-array/solutions/1010005/zhao-dao-shu-zu-de-zhong-jian-wei-zhi-by-s8cy/)

<details><summary>Description</summary>

```text
Given a 0-indexed integer array nums, find the leftmost middleIndex (i.e., the smallest amongst all the possible ones).

A middleIndex is an index where
nums[0] + nums[1] + ... + nums[middleIndex-1] == nums[middleIndex+1] + nums[middleIndex+2] + ... + nums[nums.length-1].

If middleIndex == 0, the left side sum is considered to be 0.
Similarly, if middleIndex == nums.length - 1, the right side sum is considered to be 0.

Return the leftmost middleIndex that satisfies the condition, or -1 if there is no such index.

Example 1:
Input: nums = [2,3,-1,8,4]
Output: 3
Explanation: The sum of the numbers before index 3 is: 2 + 3 + -1 = 4
The sum of the numbers after index 3 is: 4 = 4

Example 2:
Input: nums = [1,-1,4]
Output: 2
Explanation: The sum of the numbers before index 2 is: 1 + -1 = 0
The sum of the numbers after index 2 is: 0

Example 3:
Input: nums = [2,5]
Output: -1
Explanation: There is no valid middleIndex.

Constraints:
1 <= nums.length <= 100
-1000 <= nums[i] <= 1000

Note: This question is the same as 724: https://leetcode.com/problems/find-pivot-index/
```

<details><summary>Hint</summary>

```text
1. Could we go from left to right and check to see if an index is a middle index?
2. Do we need to sum every number to the left and right of an index each time?
3. Use a prefix sum array where prefix[i] = nums[0] + nums[1] + ... + nums[i].
```

</details>

</details>

<details><summary>C</summary>

```c
int findMiddleIndex(int* nums, int numsSize) {
    int retVal = -1;

    int i;

    int sumLeft[numsSize];
    sumLeft[0] = nums[0];
    for (i = 1; i < numsSize; ++i) {
        sumLeft[i] = sumLeft[i - 1] + nums[i];
    }

    int sumRight[numsSize];
    sumRight[numsSize - 1] = nums[numsSize - 1];
    for (i = numsSize - 2; i >= 0; --i) {
        sumRight[i] = sumRight[i + 1] + nums[i];
    }

    for (i = 0; i < numsSize; ++i) {
        if (sumLeft[i] == sumRight[i]) {
            retVal = i;
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
    int findMiddleIndex(vector<int>& nums) {
        int retVal = -1;

        int numsSize = nums.size();

        vector<int> sumLeft(numsSize, 0);
        sumLeft[0] = nums[0];
        for (int i = 1; i < numsSize; ++i) {
            sumLeft[i] = sumLeft[i - 1] + nums[i];
        }

        vector<int> sumRight(numsSize, 0);
        sumRight[numsSize - 1] = nums[numsSize - 1];
        for (int i = numsSize - 2; i >= 0; --i) {
            sumRight[i] = sumRight[i + 1] + nums[i];
        }

        for (int i = 0; i < numsSize; ++i) {
            if (sumLeft[i] == sumRight[i]) {
                retVal = i;
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
    def findMiddleIndex(self, nums: List[int]) -> int:
        retVal = -1

        numsSize = len(nums)

        sumLeft = [0] * numsSize
        sumLeft[0] = nums[0]
        for i in range(1, numsSize):
            sumLeft[i] = sumLeft[i - 1] + nums[i]

        sumRight = [0] * numsSize
        sumRight[numsSize - 1] = nums[numsSize - 1]
        for i in range(numsSize - 2, -1, -1):
            sumRight[i] = sumRight[i + 1] + nums[i]

        for i in range(numsSize):
            if sumLeft[i] == sumRight[i]:
                retVal = i
                break

        return retVal
```

</details>

## [2017. Grid Game](https://leetcode.com/problems/grid-game/)  1718

- [Official](https://leetcode.com/problems/grid-game/editorial/)

<details><summary>Description</summary>

```text
You are given a 0-indexed 2D array grid of size 2 x n,
where grid[r][c] represents the number of points at position (r, c) on the matrix.
Two robots are playing a game on this matrix.

Both robots initially start at (0, 0) and want to reach (1, n-1).
Each robot may only move to the right ((r, c) to (r, c + 1)) or down ((r, c) to (r + 1, c)).

At the start of the game, the first robot moves from (0, 0) to (1, n-1),
collecting all the points from the cells on its path.
For all cells (r, c) traversed on the path, grid[r][c] is set to 0.
Then, the second robot moves from (0, 0) to (1, n-1), collecting the points on its path.
Note that their paths may intersect with one another.

The first robot wants to minimize the number of points collected by the second robot. In contrast,
the second robot wants to maximize the number of points it collects.
If both robots play optimally, return the number of points collected by the second robot.

Example 1:
Input: grid = [[2,5,4],[1,5,1]]
Output: 4
Explanation: The optimal path taken by the first robot is shown in red,
and the optimal path taken by the second robot is shown in blue.
The cells visited by the first robot are set to 0.
The second robot will collect 0 + 0 + 4 + 0 = 4 points.

Example 2:
Input: grid = [[3,3,1],[8,5,2]]
Output: 4
Explanation: The optimal path taken by the first robot is shown in red,
and the optimal path taken by the second robot is shown in blue.
The cells visited by the first robot are set to 0.
The second robot will collect 0 + 3 + 1 + 0 = 4 points.

Example 3:
Input: grid = [[1,3,1,15],[1,3,3,1]]
Output: 7
Explanation: The optimal path taken by the first robot is shown in red,
and the optimal path taken by the second robot is shown in blue.
The cells visited by the first robot are set to 0.
The second robot will collect 0 + 1 + 3 + 3 + 0 = 7 points.

Constraints:
grid.length == 2
n == grid[r].length
1 <= n <= 5 * 10^4
1 <= grid[r][c] <= 10^5
```

<details><summary>Hint</summary>

```text
1. There are n choices for when the first robot moves to the second row.
2. Can we use prefix sums to help solve this problem?
```

</details>

</details>

<details><summary>C</summary>

```c
long long gridGame(int** grid, int gridSize, int* gridColSize) {
    long long retVal = 0;

    long long firstRowSum = 0;
    for (int i = 0; i < gridColSize[0]; ++i) {
        firstRowSum += grid[0][i];
    }
    long long secondRowSum = 0;
    long long minimumSum = LLONG_MAX;
    for (int turnIndex = 0; turnIndex < gridColSize[0]; ++turnIndex) {
        firstRowSum -= grid[0][turnIndex];
        minimumSum = fmin(minimumSum, fmax(firstRowSum, secondRowSum));
        secondRowSum += grid[1][turnIndex];
    }
    retVal = minimumSum;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long gridGame(vector<vector<int>>& grid) {
        long long retVal = 0;

        int colSize = grid[0].size();
        long long firstRowSum = accumulate(begin(grid[0]), end(grid[0]), 0LL);
        long long secondRowSum = 0;
        long long minimumSum = numeric_limits<long long>::max();
        for (int turnIndex = 0; turnIndex < colSize; ++turnIndex) {
            firstRowSum -= grid[0][turnIndex];
            minimumSum = min(minimumSum, max(firstRowSum, secondRowSum));
            secondRowSum += grid[1][turnIndex];
        }
        retVal = minimumSum;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def gridGame(self, grid: List[List[int]]) -> int:
        retVal = 0

        colSize = len(grid[0])
        firstRowSum = sum(grid[0])
        secondRowSum = 0
        minimumSum = float("inf")
        for turnIndex in range(colSize):
            firstRowSum -= grid[0][turnIndex]
            minimumSum = min(minimumSum, max(firstRowSum, secondRowSum))
            secondRowSum += grid[1][turnIndex]
        retVal = minimumSum

        return retVal
```

</details>

## [2256. Minimum Average Difference](https://leetcode.com/problems/minimum-average-difference/)  1394

- [Official](https://leetcode.com/problems/minimum-average-difference/solutions/2709899/minimum-average-difference/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array nums of length n.

The average difference of the index i is the absolute difference between
the average of the first i + 1 elements of nums and the average of the last n - i - 1 elements.
Both averages should be rounded down to the nearest integer.

Return the index with the minimum average difference. If there are multiple such indices, return the smallest one.

Note:
- The absolute difference of two numbers is the absolute value of their difference.
- The average of n elements is the sum of the n elements divided (integer division) by n.
- The average of 0 elements is considered to be 0.

Example 1:
Input: nums = [2,5,3,9,5,3]
Output: 3
Explanation:
- The average difference of index 0 is: |2 / 1 - (5 + 3 + 9 + 5 + 3) / 5| = |2 / 1 - 25 / 5| = |2 - 5| = 3.
- The average difference of index 1 is: |(2 + 5) / 2 - (3 + 9 + 5 + 3) / 4| = |7 / 2 - 20 / 4| = |3 - 5| = 2.
- The average difference of index 2 is: |(2 + 5 + 3) / 3 - (9 + 5 + 3) / 3| = |10 / 3 - 17 / 3| = |3 - 5| = 2.
- The average difference of index 3 is: |(2 + 5 + 3 + 9) / 4 - (5 + 3) / 2| = |19 / 4 - 8 / 2| = |4 - 4| = 0.
- The average difference of index 4 is: |(2 + 5 + 3 + 9 + 5) / 5 - 3 / 1| = |24 / 5 - 3 / 1| = |4 - 3| = 1.
- The average difference of index 5 is: |(2 + 5 + 3 + 9 + 5 + 3) / 6 - 0| = |27 / 6 - 0| = |4 - 0| = 4.
The average difference of index 3 is the minimum average difference so return 3.

Example 2:
Input: nums = [0]
Output: 0
Explanation:
The only index is 0 so return 0.
The average difference of index 0 is: |0 / 1 - 0| = |0 - 0| = 0.

Constraints:
1 <= nums.length <= 10^5
0 <= nums[i] <= 10^5
```

</details>

<details><summary>C</summary>

```c
int minimumAverageDifference(int* nums, int numsSize) {
    int retVal = 0;

    // Boundary Conditions: numsSize is 1
    if (numsSize == 1) {
        return retVal;
    }

    // Prepare sum of all elements
    long long sum = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        sum += nums[i];
    }

    long long currentDiff;
    long long minDiff = LONG_MAX;
    long long prefixSum = 0;
    // avoid divide zero, so prefix range from 0 to (numsSize - 1).
    for (i = 0; i < (numsSize - 1); ++i) {
        prefixSum += nums[i];
        sum -= nums[i];
        currentDiff = abs((prefixSum / (i + 1)) - (sum / (numsSize - (i + 1))));
        if (minDiff > currentDiff) {
            minDiff = currentDiff;
            retVal = i;
        }
    }

    // Boundary Conditions: prefix has numsSize elements, others is zero.
    prefixSum += nums[i];
    currentDiff = (prefixSum / (i + 1));
    if (minDiff > currentDiff) {
        minDiff = currentDiff;
        retVal = i;
    }

    return retVal;
}
```

</details>

## [2270. Number of Ways to Split Array](https://leetcode.com/problems/number-of-ways-to-split-array/)  1334

- [Official](https://leetcode.com/problems/number-of-ways-to-split-array/editorial/)
- [Official](https://leetcode.cn/problems/number-of-ways-to-split-array/solutions/1501536/fen-ge-shu-zu-de-fang-an-shu-by-leetcode-3ygv/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array nums of length n.

nums contains a valid split at index i if the following are true:
- The sum of the first i + 1 elements is greater than or equal to the sum of the last n - i - 1 elements.
- There is at least one element to the right of i. That is, 0 <= i < n - 1.

Return the number of valid splits in nums.

Example 1:
Input: nums = [10,4,-8,7]
Output: 2
Explanation:
There are three ways of splitting nums into two non-empty parts:
- Split nums at index 0. Then, the first part is [10], and its sum is 10.
  The second part is [4,-8,7], and its sum is 3. Since 10 >= 3, i = 0 is a valid split.
- Split nums at index 1. Then, the first part is [10,4], and its sum is 14.
  The second part is [-8,7], and its sum is -1. Since 14 >= -1, i = 1 is a valid split.
- Split nums at index 2. Then, the first part is [10,4,-8], and its sum is 6.
  The second part is [7], and its sum is 7. Since 6 < 7, i = 2 is not a valid split.
Thus, the number of valid splits in nums is 2.

Example 2:
Input: nums = [2,3,1,0]
Output: 2
Explanation:
There are two valid splits in nums:
- Split nums at index 1. Then, the first part is [2,3], and its sum is 5.
  The second part is [1,0], and its sum is 1. Since 5 >= 1, i = 1 is a valid split.
- Split nums at index 2. Then, the first part is [2,3,1], and its sum is 6.
  The second part is [0], and its sum is 0. Since 6 >= 0, i = 2 is a valid split.

Constraints:
2 <= nums.length <= 10^5
-10^5 <= nums[i] <= 10^5
```

<details><summary>Hint</summary>

```text
1. For any index i, how can we find the sum of the first (i+1) elements from the sum of the first i elements?
2. If the total sum of the array is known,
   how can we check if the sum of the first (i+1) elements greater than or equal to the remaining elements?
```

</details>

</details>

<details><summary>C</summary>

```c
int waysToSplitArray(int* nums, int numsSize) {
    int retVal = 0;

    long long leftSum = 0;
    long long rightSum = 0;
    for (int i = 0; i < numsSize; ++i) {
        rightSum += nums[i];
    }

    for (int i = 0; i < numsSize - 1; ++i) {
        leftSum += nums[i];
        rightSum -= nums[i];
        if (leftSum >= rightSum) {
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
    int waysToSplitArray(vector<int>& nums) {
        int retVal = 0;

        long long leftSum = 0;
        long long rightSum = 0;
        for (int num : nums) {
            rightSum += num;
        }

        int numsSize = nums.size();
        for (int i = 0; i < numsSize - 1; i++) {
            leftSum += nums[i];
            rightSum -= nums[i];
            if (leftSum >= rightSum) {
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
    def waysToSplitArray(self, nums: list[int]) -> int:
        retVal = 0

        leftSum = 0
        rightSum = sum(nums)

        numsSize = len(nums)
        for i in range(numsSize - 1):
            leftSum += nums[i]
            rightSum -= nums[i]
            if leftSum >= rightSum:
                retVal += 1

        return retVal
```

</details>

## [2302. Count Subarrays With Score Less Than K](https://leetcode.com/problems/count-subarrays-with-score-less-than-k/)  1808

- [Official](https://leetcode.com/problems/count-subarrays-with-score-less-than-k/editorial/)
- [Official](https://leetcode.cn/problems/count-subarrays-with-score-less-than-k/solutions/3646778/tong-ji-de-fen-xiao-yu-k-de-zi-shu-zu-sh-guvj/)

<details><summary>Description</summary>

```text
The score of an array is defined as the product of its sum and its length.
- For example, the score of [1, 2, 3, 4, 5] is (1 + 2 + 3 + 4 + 5) * 5 = 75.

Given a positive integer array nums and an integer k,
return the number of non-empty subarrays of nums whose score is strictly less than k.

A subarray is a contiguous sequence of elements within an array.

Example 1:
Input: nums = [2,1,4,3,5], k = 10
Output: 6
Explanation:
The 6 subarrays having scores less than 10 are:
- [2] with score 2 * 1 = 2.
- [1] with score 1 * 1 = 1.
- [4] with score 4 * 1 = 4.
- [3] with score 3 * 1 = 3.
- [5] with score 5 * 1 = 5.
- [2,1] with score (2 + 1) * 2 = 6.
Note that subarrays such as [1,4] and [4,3,5] are not considered because their scores are 10 and 36 respectively,
while we need scores strictly less than 10.

Example 2:
Input: nums = [1,1,1], k = 5
Output: 5
Explanation:
Every subarray except [1,1,1] has a score less than 5.
[1,1,1] has a score (1 + 1 + 1) * 3 = 9, which is greater than 5.
Thus, there are 5 subarrays having scores less than 5.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^5
1 <= k <= 10^15
```

<details><summary>Hint</summary>

```text
1. If we add an element to a list of elements, how will the score change?
2. How can we use this to determine the number of subarrays with score less than k in a given range?
3. How can we use “Two Pointers” to generalize the solution, and thus count all possible subarrays?
```

</details>

</details>

<details><summary>C</summary>

```c
long long countSubarrays(int* nums, int numsSize, long long k) {
    long long retVal = 0;

    long long total = 0;
    int head = 0;
    for (int tail = 0; tail < numsSize; ++tail) {
        total += nums[tail];
        while ((head <= tail) && (total * (tail - head + 1) >= k)) {
            total -= nums[head];
            ++head;
        }
        retVal += (tail - head + 1);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long countSubarrays(vector<int>& nums, long long k) {
        long long retVal = 0;

        int numsSize = nums.size();
        long long total = 0;
        int head = 0;
        for (int tail = 0; tail < numsSize; ++tail) {
            total += nums[tail];
            while ((head <= tail) && (total * (tail - head + 1) >= k)) {
                total -= nums[head];
                ++head;
            }
            retVal += (tail - head + 1);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def countSubarrays(self, nums: List[int], k: int) -> int:
        retVal = 0

        numsSize = len(nums)
        total = 0
        head = 0
        for tail in range(numsSize):
            total += nums[tail]
            while (head <= tail) and (total * (tail - head + 1) >= k):
                total -= nums[head]
                head += 1
            retVal += (tail - head + 1)

        return retVal
```

</details>

## [2391. Minimum Amount of Time to Collect Garbage](https://leetcode.com/problems/minimum-amount-of-time-to-collect-garbage/)  1455

- [Official](https://leetcode.com/problems/minimum-amount-of-time-to-collect-garbage/editorial/)

<details><summary>Description</summary>

```text
You are given a 0-indexed array of strings garbage
where garbage[i] represents the assortment of garbage at the ith house.
garbage[i] consists only of the characters 'M', 'P' and 'G' representing one unit of metal,
paper and glass garbage respectively.
Picking up one unit of any type of garbage takes 1 minute.

You are also given a 0-indexed integer array travel
where travel[i] is the number of minutes needed to go from house i to house i + 1.

There are three garbage trucks in the city, each responsible for picking up one type of garbage.
Each garbage truck starts at house 0 and must visit each house in order; however, they do not need to visit every house.

Only one garbage truck may be used at any given moment.
While one truck is driving or picking up garbage, the other two trucks cannot do anything.

Return the minimum number of minutes needed to pick up all the garbage.

Example 1:
Input: garbage = ["G","P","GP","GG"], travel = [2,4,3]
Output: 21
Explanation:
The paper garbage truck:
1. Travels from house 0 to house 1
2. Collects the paper garbage at house 1
3. Travels from house 1 to house 2
4. Collects the paper garbage at house 2
Altogether, it takes 8 minutes to pick up all the paper garbage.
The glass garbage truck:
1. Collects the glass garbage at house 0
2. Travels from house 0 to house 1
3. Travels from house 1 to house 2
4. Collects the glass garbage at house 2
5. Travels from house 2 to house 3
6. Collects the glass garbage at house 3
Altogether, it takes 13 minutes to pick up all the glass garbage.
Since there is no metal garbage, we do not need to consider the metal garbage truck.
Therefore, it takes a total of 8 + 13 = 21 minutes to collect all the garbage.

Example 2:
Input: garbage = ["MMM","PGM","GP"], travel = [3,10]
Output: 37
Explanation:
The metal garbage truck takes 7 minutes to pick up all the metal garbage.
The paper garbage truck takes 15 minutes to pick up all the paper garbage.
The glass garbage truck takes 15 minutes to pick up all the glass garbage.
It takes a total of 7 + 15 + 15 = 37 minutes to collect all the garbage.

Constraints:
2 <= garbage.length <= 10^5
garbage[i] consists of only the letters 'M', 'P', and 'G'.
1 <= garbage[i].length <= 10
travel.length == garbage.length - 1
1 <= travel[i] <= 100
```

<details><summary>Hint</summary>

```text
1. Where can we save time? By not visiting all the houses.
2. For each type of garbage, find the house with the highest index that has at least 1 unit of this type of garbage.
```

</details>

</details>

<details><summary>C</summary>

```c
int garbageCollection(char** garbage, int garbageSize, int* travel, int travelSize) {
    int retVal = 0;

    int i, j;

    int travelPrefixSum[travelSize + 1];
    memset(travelPrefixSum, 0, sizeof(travelPrefixSum));
    for (i = 0; i < travelSize; ++i) {
        travelPrefixSum[i + 1] = travelPrefixSum[i] + travel[i];
    }

    // garbage[i] consists only of the characters 'M', 'P' and 'G'
    int garbageType = 4;
    int lastGarbage[garbageType];
    memset(lastGarbage, 0, sizeof(lastGarbage));

    int len;
    for (i = 0; i < garbageSize; ++i) {
        len = strlen(garbage[i]);
        for (j = 0; j < len; ++j) {
            if (garbage[i][j] == 'M') {
                lastGarbage[1] = i;
            } else if (garbage[i][j] == 'P') {
                lastGarbage[2] = i;
            } else if (garbage[i][j] == 'G') {
                lastGarbage[3] = i;
            }
            retVal += 1;
        }
    }

    for (i = 0; i < garbageType; ++i) {
        retVal += travelPrefixSum[lastGarbage[i]];
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int garbageCollection(vector<string>& garbage, vector<int>& travel) {
        int retVal = 0;

        int travelSize = travel.size();
        vector<int> travelPrefixSum((travelSize + 1), 0);
        for (int i = 0; i < travelSize; ++i) {
            travelPrefixSum[i + 1] = travelPrefixSum[i] + travel[i];
        }

        // garbage[i] consists only of the characters 'M', 'P' and 'G'
        int garbageType = 4;
        vector<int> lastGarbage(garbageType, 0);
        int garbageSize = garbage.size();
        for (int i = 0; i < garbageSize; ++i) {
            for (char c : garbage[i]) {
                if (c == 'M') {
                    lastGarbage[1] = i;
                } else if (c == 'P') {
                    lastGarbage[2] = i;
                } else if (c == 'G') {
                    lastGarbage[3] = i;
                }
                retVal += 1;
            }
        }

        for (int i = 0; i < garbageType; ++i) {
            retVal += travelPrefixSum[lastGarbage[i]];
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def garbageCollection(self, garbage: List[str], travel: List[int]) -> int:
        retVal = 0

        travelSize = len(travel)
        travelPrefixSum = [0] * (travelSize+1)
        for i in range(travelSize):
            travelPrefixSum[i+1] = travelPrefixSum[i] + travel[i]

        # garbage[i] consists only of the characters 'M', 'P' and 'G'
        garbageType = 4

        lastGarbage = [0] * garbageType
        for index, value in enumerate(garbage):
            for p in value:
                if p == 'M':
                    lastGarbage[1] = index
                elif p == 'P':
                    lastGarbage[2] = index
                elif p == 'G':
                    lastGarbage[3] = index

                retVal += 1

        for i in range(garbageType):
            retVal += travelPrefixSum[lastGarbage[i]]

        return retVal
```

</details>

## [2483. Minimum Penalty for a Shop](https://leetcode.com/problems/minimum-penalty-for-a-shop/)  1494

- [Official](https://leetcode.com/problems/minimum-penalty-for-a-shop/editorial/)

<details><summary>Description</summary>

```text
You are given the customer visit log of a shop represented by a 0-indexed string
customers consisting only of characters 'N' and 'Y':
- if the ith character is 'Y', it means that customers come at the ith hour
- whereas 'N' indicates that no customers come at the ith hour.

If the shop closes at the jth hour (0 <= j <= n), the penalty is calculated as follows:
- For every hour when the shop is open and no customers come, the penalty increases by 1.
- For every hour when the shop is closed and customers come, the penalty increases by 1.

Return the earliest hour at which the shop must be closed to incur a minimum penalty.

Note that if a shop closes at the jth hour, it means the shop is closed at the hour j.

Example 1:
Input: customers = "YYNY"
Output: 2
Explanation:
- Closing the shop at the 0th hour incurs in 1+1+0+1 = 3 penalty.
- Closing the shop at the 1st hour incurs in 0+1+0+1 = 2 penalty.
- Closing the shop at the 2nd hour incurs in 0+0+0+1 = 1 penalty.
- Closing the shop at the 3rd hour incurs in 0+0+1+1 = 2 penalty.
- Closing the shop at the 4th hour incurs in 0+0+1+0 = 1 penalty.
Closing the shop at 2nd or 4th hour gives a minimum penalty. Since 2 is earlier, the optimal closing time is 2.

Example 2:
Input: customers = "NNNNN"
Output: 0
Explanation: It is best to close the shop at the 0th hour as no customers arrive.

Example 3:
Input: customers = "YYYY"
Output: 4
Explanation: It is best to close the shop at the 4th hour as customers arrive at each hour.

Constraints:
1 <= customers.length <= 10^5
customers consists only of characters 'Y' and 'N'.
```

<details><summary>Hint</summary>

```text
1. At any index, the penalty is the sum of prefix count of 'N' and suffix count of 'Y'.
2. Enumerate all indices and find the minimum such value.
```

</details>

</details>

<details><summary>C</summary>

```c
int bestClosingTime(char *customers) {
    int retVal = 0;

    /* At any index, the penalty is the sum of prefix count of 'N' and suffix count of 'Y'.
     *  Y Y N Y     N N N N N     Y Y Y Y
     *  3 2 1 1 0   0 0 0 0 0 0   4 3 2 1 0
     *  0 0 0 1 1   0 1 2 3 4 5   0 0 0 0 0
     */
    int customersSize = strlen(customers);
    int penalty = 0;
    int i;
    for (i = 0; i < customersSize; ++i) {
        if (customers[i] == 'Y') {
            ++penalty;
        }
    }
    int minPenalty = penalty;
    for (i = 0; i < customersSize; ++i) {
        if (customers[i] == 'Y') {
            --penalty;
        } else if (customers[i] == 'N') {
            ++penalty;
        }

        if (minPenalty > penalty) {
            minPenalty = penalty;
            retVal = i + 1;
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
    int bestClosingTime(string customers) {
        int retVal = 0;

        /* At any index, the penalty is the sum of prefix count of 'N' and suffix count of 'Y'.
         *  Y Y N Y     N N N N N     Y Y Y Y
         *  3 2 1 1 0   0 0 0 0 0 0   4 3 2 1 0
         *  0 0 0 1 1   0 1 2 3 4 5   0 0 0 0 0
         */
        int penalty = count(customers.begin(), customers.end(), 'Y');
        int minPenalty = penalty;
        int customersSize = customers.size();
        for (int i = 0; i < customersSize; ++i) {
            if (customers[i] == 'Y') {
                --penalty;
            } else if (customers[i] == 'N') {
                ++penalty;
            }

            if (minPenalty > penalty) {
                minPenalty = penalty;
                retVal = i + 1;
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
    def bestClosingTime(self, customers: str) -> int:
        retVal = 0

        # /* At any index, the penalty is the sum of prefix count of 'N' and suffix count of 'Y'.
        #  *  Y Y N Y     N N N N N     Y Y Y Y
        #  *  3 2 1 1 0   0 0 0 0 0 0   4 3 2 1 0
        #  *  0 0 0 1 1   0 1 2 3 4 5   0 0 0 0 0
        #  */
        penalty = customers.count('Y')
        minPenalty = penalty
        customersSize = len(customers)
        for i in range(customersSize):
            if customers[i] == 'Y':
                penalty -= 1
            elif customers[i] == 'N':
                penalty += 1

            if minPenalty > penalty:
                minPenalty = penalty
                retVal = i + 1

        return retVal
```

</details>

## [2536. Increment Submatrices by One](https://leetcode.com/problems/increment-submatrices-by-one/)  1583

- [Official](https://leetcode.com/problems/increment-submatrices-by-one/editorial/)
- [Official](https://leetcode.cn/problems/increment-submatrices-by-one/solutions/3820749/zi-ju-zhen-yuan-su-jia-1-by-leetcode-sol-3iob/)

<details><summary>Description</summary>

```text
You are given a positive integer n,
indicating that we initially have an n x n 0-indexed integer matrix mat filled with zeroes.

You are also given a 2D integer array query.
For each query[i] = [row1i, col1i, row2i, col2i], you should do the following operation:
- Add 1 to every element in the submatrix with the top left corner (row1i, col1i)
  and the bottom right corner (row2i, col2i).
  That is, add 1 to mat[x][y] for all row1i <= x <= row2i and col1i <= y <= col2i.

Return the matrix mat after performing every query.

Example 1:
Input: n = 3, queries = [[1,1,2,2],[0,0,1,1]]
Output: [[1,1,0],[1,2,1],[0,1,1]]
Explanation:
The diagram above shows the initial matrix, the matrix after the first query, and the matrix after the second query.
- In the first query, we add 1 to every element in the submatrix with the top left corner (1, 1)
  and bottom right corner (2, 2).
- In the second query, we add 1 to every element in the submatrix with the top left corner (0, 0)
  and bottom right corner (1, 1).

Example 2:
Input: n = 2, queries = [[0,0,1,1]]
Output: [[1,1],[1,1]]
Explanation:
The diagram above shows the initial matrix and the matrix after the first query.
- In the first query we add 1 to every element in the matrix.

Constraints:
1 <= n <= 500
1 <= queries.length <= 10^4
0 <= row1i <= row2i < n
0 <= col1i <= col2i < n
```

<details><summary>Hint</summary>

```text
1. Imagine each row as a separate array.
   Instead of updating the whole submatrix together, we can use prefix sum to update each row separately.
2. For each query, iterate over the rows i in the range [row1, row2] and add 1 to prefix sum S[i][col1],
   and subtract 1 from S[i][col2 + 1].
3. After doing this operation for all the queries, update each row separately with S[i][j] = S[i][j] + S[i][j - 1].
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
int** rangeAddQueries(int n, int** queries, int queriesSize, int* queriesColSize, int* returnSize,
                      int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    int diff[n + 1][n + 1];
    memset(diff, 0, sizeof(diff));
    int row1, col1, row2, col2;
    for (int i = 0; i < queriesSize; ++i) {
        row1 = queries[i][0];
        col1 = queries[i][1];
        row2 = queries[i][2];
        col2 = queries[i][3];
        diff[row1][col1] += 1;
        diff[row2 + 1][col1] -= 1;
        diff[row1][col2 + 1] -= 1;
        diff[row2 + 1][col2 + 1] += 1;
    }

    (*returnColumnSizes) = (int*)malloc(n * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal = (int**)malloc(n * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }
    for (int i = 0; i < n; i++) {
        pRetVal[i] = (int*)calloc(n, sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("calloc");
            for (int j = 0; j < i; j++) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            return pRetVal;
        }
        (*returnColumnSizes)[i] = n;
    }
    (*returnSize) = n;

    int x1, x2, x3;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            x1 = (i == 0) ? (0) : (pRetVal[i - 1][j]);
            x2 = (j == 0) ? (0) : (pRetVal[i][j - 1]);
            x3 = ((i == 0) || (j == 0)) ? (0) : (pRetVal[i - 1][j - 1]);
            pRetVal[i][j] = diff[i][j] + x1 + x2 - x3;
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
    vector<vector<int>> rangeAddQueries(int n, vector<vector<int>>& queries) {
        vector<vector<int>> retVal;

        vector diff(n + 1, vector<int>(n + 1));
        for (const auto& query : queries) {
            int row1 = query[0];
            int col1 = query[1];
            int row2 = query[2];
            int col2 = query[3];
            diff[row1][col1] += 1;
            diff[row2 + 1][col1] -= 1;
            diff[row1][col2 + 1] -= 1;
            diff[row2 + 1][col2 + 1] += 1;
        }

        retVal = vector<vector<int>>(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int x1 = (i == 0) ? (0) : (retVal[i - 1][j]);
                int x2 = (j == 0) ? (0) : (retVal[i][j - 1]);
                int x3 = ((i == 0) || (j == 0)) ? (0) : (retVal[i - 1][j - 1]);
                retVal[i][j] = diff[i][j] + x1 + x2 - x3;
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
    def rangeAddQueries(self, n: int, queries: List[List[int]]) -> List[List[int]]:
        retVal = []

        diff = [[0] * (n + 1) for _ in range(n + 1)]
        for row1, col1, row2, col2 in queries:
            diff[row1][col1] += 1
            diff[row2 + 1][col1] -= 1
            diff[row1][col2 + 1] -= 1
            diff[row2 + 1][col2 + 1] += 1

        retVal = [[0] * n for _ in range(n)]
        for i in range(n):
            for j in range(n):
                x1 = 0
                if i != 0:
                    x1 = retVal[i - 1][j]

                x2 = 0
                if j != 0:
                    x2 = retVal[i][j - 1]

                x3 = 0
                if (i != 0) and (j != 0):
                    x3 = retVal[i - 1][j - 1]

                retVal[i][j] = diff[i][j] + x1 + x2 - x3

        return retVal
```

</details>

## [2559. Count Vowel Strings in Ranges](https://leetcode.com/problems/count-vowel-strings-in-ranges/description/)  1435

- [Official](https://leetcode.com/problems/count-vowel-strings-in-ranges/editorial/)
- [Official](https://leetcode.cn/problems/count-vowel-strings-in-ranges/solutions/2289469/tong-ji-fan-wei-nei-de-yuan-yin-zi-fu-ch-5k8q/)

<details><summary>Description</summary>

```text
You are given a 0-indexed array of strings words and a 2D array of integers queries.

Each query queries[i] = [li, ri] asks us to find the number of strings
present in the range li to ri (both inclusive) of words that start and end with a vowel.

Return an array ans of size queries.length, where ans[i] is the answer to the ith query.

Note that the vowel letters are 'a', 'e', 'i', 'o', and 'u'.

Example 1:
Input: words = ["aba","bcb","ece","aa","e"], queries = [[0,2],[1,4],[1,1]]
Output: [2,3,0]
Explanation: The strings starting and ending with a vowel are "aba", "ece", "aa" and "e".
The answer to the query [0,2] is 2 (strings "aba" and "ece").
to query [1,4] is 3 (strings "ece", "aa", "e").
to query [1,1] is 0.
We return [2,3,0].

Example 2:
Input: words = ["a","e","i"], queries = [[0,2],[0,1],[2,2]]
Output: [3,2,1]
Explanation: Every string satisfies the conditions, so we return [3,2,1].

Constraints:
1 <= words.length <= 10^5
1 <= words[i].length <= 40
words[i] consists only of lowercase English letters.
sum(words[i].length) <= 3 * 10^5
1 <= queries.length <= 10^5
0 <= li <= ri < words.length
```

<details><summary>Hint</summary>

```text
1. Precompute the prefix sum of strings that start and end with vowels.
2. Use unordered_set to store vowels.
3. Check if the first and last characters of the string are present in the vowels set.
4. Subtract prefix sum for range [l-1, r] to find the number of strings starting and ending with vowels.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* vowelStrings(char** words, int wordsSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int*)calloc(queriesSize, sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    (*returnSize) = queriesSize;

    int prefixSum[wordsSize];
    memset(prefixSum, 0, sizeof(prefixSum));

    char start, end;
    int vowelCount = 0;
    for (int i = 0; i < wordsSize; i++) {
        start = words[i][0];
        end = words[i][strlen(words[i]) - 1];
        if ((start == 'a') || (start == 'e') || (start == 'i') || (start == 'o') || (start == 'u')) {
            if ((end == 'a') || (end == 'e') || (end == 'i') || (end == 'o') || (end == 'u')) {
                vowelCount++;
            }
        }
        prefixSum[i] = vowelCount;
    }

    for (int i = 0; i < queriesSize; i++) {
        pRetVal[i] = prefixSum[queries[i][1]];
        if (queries[i][0] != 0) {
            pRetVal[i] -= prefixSum[queries[i][0] - 1];
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
    vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries) {
        vector<int> retVal;

        int queriesSize = queries.size();
        retVal.assign(queriesSize, 0);

        int wordsSize = words.size();
        vector<int> prefixSum(wordsSize, 0);

        unordered_set<char> vowels{'a', 'e', 'i', 'o', 'u'};
        int vowelCount = 0;
        for (int i = 0; i < wordsSize; i++) {
            string word = words[i];
            int wordSize = word.size();
            if ((vowels.count(word[0])) && (vowels.count(word[wordSize - 1]))) {
                vowelCount++;
            }
            prefixSum[i] = vowelCount;
        }

        for (int i = 0; i < queriesSize; i++) {
            vector<int> query = queries[i];
            retVal[i] = prefixSum[query[1]];
            if (query[0] != 0) {
                retVal[i] -= prefixSum[query[0] - 1];
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
    def vowelStrings(self, words: List[str], queries: List[List[int]]) -> List[int]:
        retVal = None

        queriesSize = len(queries)
        retVal = [0] * queriesSize

        wordsSize = len(words)
        prefixSum = [0] * wordsSize

        vowels = {"a", "e", "i", "o", "u"}
        vowelCount = 0
        for i in range(wordsSize):
            word = words[i]
            if (word[0] in vowels) and (word[-1] in vowels):
                vowelCount += 1
            prefixSum[i] = vowelCount

        for i in range(queriesSize):
            query = queries[i]
            retVal[i] = prefixSum[query[1]]
            if query[0] != 0:
                retVal[i] -= prefixSum[query[0] - 1]

        return retVal
```

</details>

## [2779. Maximum Beauty of an Array After Applying Operation](https://leetcode.com/problems/maximum-beauty-of-an-array-after-applying-operation/)  2779

- [Official](https://leetcode.com/problems/maximum-beauty-of-an-array-after-applying-operation/editorial/)
- [Official](https://leetcode.cn/problems/maximum-beauty-of-an-array-after-applying-operation/solutions/2806897/shu-zu-de-zui-da-mei-li-zhi-by-leetcode-9jgs0/)

<details><summary>Description</summary>

```text
You are given a 0-indexed array nums and a non-negative integer k.

In one operation, you can do the following:
- Choose an index i that hasn't been chosen before from the range [0, nums.length - 1].
- Replace nums[i] with any integer from the range [nums[i] - k, nums[i] + k].

The beauty of the array is the length of the longest subsequence consisting of equal elements.

Return the maximum possible beauty of the array nums after applying the operation any number of times.

Note that you can apply the operation to each index only once.

A subsequence of an array is a new array generated from the original array by deleting some elements (possibly none)
without changing the order of the remaining elements.

Example 1:
Input: nums = [4,6,1,2], k = 2
Output: 3
Explanation: In this example, we apply the following operations:
- Choose index 1, replace it with 4 (from range [4,8]), nums = [4,4,1,2].
- Choose index 3, replace it with 4 (from range [0,4]), nums = [4,4,1,4].
After the applied operations, the beauty of the array nums is 3 (subsequence consisting of indices 0, 1, and 3).
It can be proven that 3 is the maximum possible length we can achieve.

Example 2:
Input: nums = [1,1,1,1], k = 10
Output: 4
Explanation: In this example we don't have to apply any operations.
The beauty of the array nums is 4 (whole array).

Constraints:
1 <= nums.length <= 10^5
0 <= nums[i], k <= 10^5
```

<details><summary>Hint</summary>

```text
1. Sort the array.
2. The problem becomes the following: find maximum subarray A[i … j] such that A[j] - A[i] ≤ 2 * k.
```

</details>

</details>

<details><summary>C</summary>

```c
int maximumBeauty(int* nums, int numsSize, int k) {
    int retVal = 0;

    if (numsSize == 1) {  // If there's only one element, the maximum beauty is 1
        retVal = 1;
        return retVal;
    }

    int maxValue = 0;
    for (int i = 0; i < numsSize; ++i) {
        maxValue = fmax(maxValue, nums[i]);
    }

    int countSize = maxValue + 1;
    int count[maxValue + 1];
    memset(count, 0, sizeof(count));
    int idx;
    for (int i = 0; i < numsSize; ++i) {
        idx = fmax(nums[i] - k, 0);
        count[idx]++;  // Increment at the start of the range
        if (nums[i] + k + 1 <= maxValue) {
            count[nums[i] + k + 1]--;  // Decrement after the range
        }
    }

    // Calculate the prefix sum and find the maximum value
    int currentSum = 0;
    for (int i = 0; i < countSize; ++i) {
        currentSum += count[i];
        retVal = fmax(retVal, currentSum);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maximumBeauty(vector<int>& nums, int k) {
        int retVal = 0;

        int numsSize = nums.size();
        if (numsSize == 1) {  // If there's only one element, the maximum beauty is 1
            retVal = 1;
            return retVal;
        }

        int maxValue = 0;
        for (int num : nums) {
            maxValue = max(maxValue, num);
        }

        vector<int> count(maxValue + 1, 0);
        for (int num : nums) {
            count[max(num - k, 0)]++;  // Increment at the start of the range
            if (num + k + 1 <= maxValue) {
                count[num + k + 1]--;  // Decrement after the range
            }
        }

        // Calculate the prefix sum and find the maximum value
        int currentSum = 0;
        for (int value : count) {
            currentSum += value;
            retVal = max(retVal, currentSum);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maximumBeauty(self, nums: List[int], k: int) -> int:
        retVal = 0

        numsSize = len(nums)
        if numsSize == 1:  # If there's only one element, the maximum beauty is 1
            retVal = 1
            return retVal

        maxValue = max(nums)
        count = [0] * (maxValue + 1)
        for num in nums:
            count[max(num - k, 0)] += 1  # Increment at the start of the range
            if num + k + 1 <= maxValue:
                count[num + k + 1] -= 1  # Decrement after the range

        # Calculate the prefix sum and find the maximum beauty
        currentSum = 0
        for value in count:
            currentSum += value
            retVal = max(retVal, currentSum)

        return retVal
```

</details>

## [2845. Count of Interesting Subarrays](https://leetcode.com/problems/count-of-interesting-subarrays/)  2073

- [Official](https://leetcode.com/problems/count-of-interesting-subarrays/editorial/)
- [Official](https://leetcode.cn/problems/count-of-interesting-subarrays/solutions/3647292/tong-ji-qu-wei-zi-shu-zu-de-shu-mu-by-le-968z/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array nums, an integer modulo, and an integer k.

Your task is to find the count of subarrays that are interesting.

A subarray nums[l..r] is interesting if the following condition holds:
- Let cnt be the number of indices i in the range [l, r] such that nums[i] % modulo == k. Then, cnt % modulo == k.

Return an integer denoting the count of interesting subarrays.

Note: A subarray is a contiguous non-empty sequence of elements within an array.

Example 1:
Input: nums = [3,2,4], modulo = 2, k = 1
Output: 3
Explanation: In this example the interesting subarrays are:
The subarray nums[0..0] which is [3].
- There is only one index, i = 0, in the range [0, 0] that satisfies nums[i] % modulo == k.
- Hence, cnt = 1 and cnt % modulo == k.
The subarray nums[0..1] which is [3,2].
- There is only one index, i = 0, in the range [0, 1] that satisfies nums[i] % modulo == k.
- Hence, cnt = 1 and cnt % modulo == k.
The subarray nums[0..2] which is [3,2,4].
- There is only one index, i = 0, in the range [0, 2] that satisfies nums[i] % modulo == k.
- Hence, cnt = 1 and cnt % modulo == k.
It can be shown that there are no other interesting subarrays. So, the answer is 3.

Example 2:
Input: nums = [3,1,9,6], modulo = 3, k = 0
Output: 2
Explanation: In this example the interesting subarrays are:
The subarray nums[0..3] which is [3,1,9,6].
- There are three indices, i = 0, 2, 3, in the range [0, 3] that satisfy nums[i] % modulo == k.
- Hence, cnt = 3 and cnt % modulo == k.
The subarray nums[1..1] which is [1].
- There is no index, i, in the range [1, 1] that satisfies nums[i] % modulo == k.
- Hence, cnt = 0 and cnt % modulo == k.
It can be shown that there are no other interesting subarrays. So, the answer is 2.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
1 <= modulo <= 10^9
0 <= k < modulo
```

<details><summary>Hint</summary>

```text
1. The problem can be solved using prefix sums.
2. Let count[i] be the number of indices where nums[i] % modulo == k among the first i indices.
3. count[0] = 0 and count[i] = count[i - 1] + (nums[i - 1] % modulo == k ? 1 : 0) for i = 1, 2, ..., n.
4. Now we want to calculate for each i = 1, 2, ..., n,
   how many indices j < i such that (count[i] - count[j]) % modulo == k.
5. Rewriting (count[i] - count[j]) % modulo == k becomes count[j] = (count[i] + modulo - k) % modulo.
6. Using a map data structure, for each i = 0, 1, 2, ..., n,
   we just sum up all map[(count[i] + modulo - k) % modulo] before increasing map[count[i] % modulo],
   and the total sum is the final answer.
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
void freeAll(struct hashTable *pFree) {
    struct hashTable *current;
    struct hashTable *tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
long long countInterestingSubarrays(int *nums, int numsSize, int modulo, int k) {
    long long retVal = 0;

    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
    if (pTemp == NULL) {
        perror("malloc");
        freeAll(pHashTable);
        return retVal;
    }
    pTemp->key = 0;
    pTemp->value = 1;
    HASH_ADD_INT(pHashTable, key, pTemp);

    int key;
    int prefix = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] % modulo == k) {
            prefix++;
        }

        key = (prefix - k + modulo) % modulo;
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &key, pTemp);
        if (pTemp != NULL) {
            retVal += pTemp->value;
        }

        key = prefix % modulo;
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &key, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                return retVal;
            }
            pTemp->key = key;
            pTemp->value = 1;
            HASH_ADD_INT(pHashTable, key, pTemp);
        } else {
            pTemp->value += 1;
        }
    }

    //
    freeAll(pHashTable);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long countInterestingSubarrays(vector<int>& nums, int modulo, int k) {
        long long retVal = 0;

        unordered_map<int, int> hashTable;
        hashTable[0] = 1;

        int prefix = 0;
        int numsSize = nums.size();
        for (int i = 0; i < numsSize; i++) {
            if (nums[i] % modulo == k) {
                prefix++;
            }
            retVal += hashTable[(prefix - k + modulo) % modulo];
            hashTable[prefix % modulo]++;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def countInterestingSubarrays(self, nums: List[int], modulo: int, k: int) -> int:
        retVal = 0

        hashTable = Counter([0])

        prefix = 0
        numsSize = len(nums)
        for i in range(numsSize):
            if nums[i] % modulo == k:
                prefix += 1
            retVal += hashTable[(prefix - k + modulo) % modulo]
            hashTable[prefix % modulo] += 1

        return retVal
```

</details>

## [3147. Taking Maximum Energy From the Mystic Dungeon](https://leetcode.com/problems/taking-maximum-energy-from-the-mystic-dungeon/)  1460

- [Official](https://leetcode.com/problems/taking-maximum-energy-from-the-mystic-dungeon/editorial/)
- [Official](https://leetcode.cn/problems/taking-maximum-energy-from-the-mystic-dungeon/solutions/3796799/cong-mo-fa-shi-shen-shang-xi-qu-de-zui-d-xkjs/)

<details><summary>Description</summary>

```text
In a mystic dungeon, n magicians are standing in a line.
Each magician has an attribute that gives you energy.
Some magicians can give you negative energy, which means taking energy from you.

You have been cursed in such a way that after absorbing energy from magician i,
you will be instantly transported to magician (i + k).
This process will be repeated until you reach the magician where (i + k) does not exist.

In other words,
you will choose a starting point and then teleport with k jumps until you reach the end of the magicians' sequence,
absorbing all the energy during the journey.

You are given an array energy and an integer k. Return the maximum possible energy you can gain.

Note that when you are reach a magician, you must take energy from them, whether it is negative or positive energy.

Example 1:
Input: energy = [5,2,-10,-5,1], k = 3
Output: 3
Explanation: We can gain a total energy of 3 by starting from magician 1 absorbing 2 + 1 = 3.

Example 2:
Input: energy = [-2,-3,-1], k = 2
Output: -1
Explanation: We can gain a total energy of -1 by starting from magician 2.

Constraints:
1 <= energy.length <= 10^5
-1000 <= energy[i] <= 1000
1 <= k <= energy.length - 1
```

<details><summary>Hint</summary>

```text
1. Let dp[i] denote the energy we gain starting from index i.
2. We can notice, that  dp[i] = dp[i + k] + energy[i].
```

</details>

</details>

<details><summary>C</summary>

```c
int maximumEnergy(int* energy, int energySize, int k) {
    int retVal = INT_MIN;

    int sum;
    for (int i = energySize - k; i < energySize; i++) {
        sum = 0;
        for (int j = i; j >= 0; j -= k) {
            sum += energy[j];
            if (sum > retVal) {
                retVal = sum;
            }
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
    int maximumEnergy(vector<int>& energy, int k) {
        int retVal = numeric_limits<int>::min();

        int energySize = energy.size();
        for (int i = energySize - k; i < energySize; i++) {
            int sum = 0;
            for (int j = i; j >= 0; j -= k) {
                sum += energy[j];
                retVal = max(retVal, sum);
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
    def maximumEnergy(self, energy: List[int], k: int) -> int:
        retVal = float('-inf')

        energySize = len(energy)
        for i in range(energySize - k, energySize):
            total = 0
            j = i
            while j >= 0:
                total += energy[j]
                retVal = max(retVal, total)
                j -= k

        return retVal
```

</details>

## [3152. Special Array II](https://leetcode.com/problems/special-array-ii/)  1523

- [Official](https://leetcode.com/problems/special-array-ii/editorial/)
- [Official](https://leetcode.cn/problems/special-array-ii/solutions/2877223/te-shu-shu-zu-ii-by-leetcode-solution-ozu1/)

<details><summary>Description</summary>

```text
An array is considered special if every pair of its adjacent elements contains two numbers with different parity.

You are given an array of integer nums and a 2D integer matrix queries,
where for queries[i] = [fromi, toi] your task is to check that subarray nums[fromi..toi] is special or not.

Return an array of booleans answer such that answer[i] is true if nums[fromi..toi] is special.

Example 1:
Input: nums = [3,4,1,2,6], queries = [[0,4]]
Output: [false]
Explanation:
The subarray is [3,4,1,2,6]. 2 and 6 are both even.

Example 2:
Input: nums = [4,3,1,6], queries = [[0,2],[2,3]]
Output: [false,true]
Explanation:
The subarray is [4,3,1]. 3 and 1 are both odd. So the answer to this query is false.
The subarray is [1,6]. There is only one pair: (1,6) and it contains numbers with different parity.
So the answer to this query is true.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^5
1 <= queries.length <= 10^5
queries[i].length == 2
0 <= queries[i][0] <= queries[i][1] <= nums.length - 1
```

<details><summary>Hint</summary>

```text
1. Try to split the array into some non-intersected continuous special subarrays.
2. For each query check that the first and the last elements of that query are in the same subarray or not.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* isArraySpecial(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    bool* pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (bool*)malloc(queriesSize * sizeof(bool));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (queriesSize) * sizeof(bool));

    int prefix[numsSize];
    memset(prefix, 0, sizeof(prefix));
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i] % 2 == nums[i - 1] % 2) {
            prefix[i] = prefix[i - 1] + 1;  // new violative index found
        } else {
            prefix[i] = prefix[i - 1];
        }
    }

    bool value;
    int start, end;
    for (int i = 0; i < queriesSize; ++i) {
        start = queries[i][0];
        end = queries[i][1];
        value = (prefix[end] - prefix[start] == 0);
        pRetVal[(*returnSize)] = value;
        (*returnSize) += 1;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++

class Solution {
   public:
    vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries) {
        vector<bool> retVal;

        int numsSize = nums.size();
        vector<int> prefix(numsSize, 0);
        for (int i = 1; i < numsSize; ++i) {
            if (nums[i] % 2 == nums[i - 1] % 2) {
                prefix[i] = prefix[i - 1] + 1;  // new violative index found
            } else {
                prefix[i] = prefix[i - 1];
            }
        }

        for (auto& query : queries) {
            int start = query[0];
            int end = query[1];
            bool value = (prefix[end] - prefix[start] == 0);
            retVal.emplace_back(value);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def isArraySpecial(self, nums: List[int], queries: List[List[int]]) -> List[bool]:
        retVal = []

        numsSize = len(nums)
        prefix = [0] * numsSize
        for i in range(1, numsSize):
            if nums[i] % 2 == nums[i - 1] % 2:
                prefix[i] = prefix[i - 1] + 1  # new violative index found
            else:
                prefix[i] = prefix[i - 1]

        for start, end in queries:
            value = (prefix[end] - prefix[start] == 0)
            retVal.append(value)

        return retVal
```

</details>

## [3354. Make Array Elements Equal to Zero](https://leetcode.com/problems/make-array-elements-equal-to-zero/)  1397

- [Official](https://leetcode.com/problems/make-array-elements-equal-to-zero/editorial/)
- [Official](https://leetcode.cn/problems/make-array-elements-equal-to-zero/solutions/3810607/shi-shu-zu-yuan-su-deng-yu-ling-by-leetc-0cvo/)

<details><summary>Description</summary>

```text
You are given an integer array nums.

Start by selecting a starting position curr such that nums[curr] == 0,
and choose a movement direction of either left or right.

After that, you repeat the following process:
- If curr is out of the range [0, n - 1], this process ends.
- If nums[curr] == 0, move in the current direction by incrementing curr if you are moving right,
  or decrementing curr if you are moving left.
- Else if nums[curr] > 0:
  - Decrement nums[curr] by 1.
  - Reverse your movement direction (left becomes right and vice versa).
  - Take a step in your new direction.

A selection of the initial position curr and movement direction is considered valid
if every element in nums becomes 0 by the end of the process.

Return the number of possible valid selections.

Example 1:
Input: nums = [1,0,2,0,3]
Output: 2
Explanation:
The only possible valid selections are the following:
Choose curr = 3, and a movement direction to the left.
[1,0,2,0,3] -> [1,0,2,0,3] -> [1,0,1,0,3] -> [1,0,1,0,3] -> [1,0,1,0,2]
 -> [1,0,1,0,2] -> [1,0,0,0,2] -> [1,0,0,0,2] -> [1,0,0,0,1] -> [1,0,0,0,1]
 -> [1,0,0,0,1] -> [1,0,0,0,1] -> [0,0,0,0,1] -> [0,0,0,0,1] -> [0,0,0,0,1]
 -> [0,0,0,0,1] -> [0,0,0,0,0].
Choose curr = 3, and a movement direction to the right.
[1,0,2,0,3] -> [1,0,2,0,3] -> [1,0,2,0,2] -> [1,0,2,0,2] -> [1,0,1,0,2]
 -> [1,0,1,0,2] -> [1,0,1,0,1] -> [1,0,1,0,1] -> [1,0,0,0,1] -> [1,0,0,0,1]
 -> [1,0,0,0,0] -> [1,0,0,0,0] -> [1,0,0,0,0] -> [1,0,0,0,0] -> [0,0,0,0,0].

Example 2:
Input: nums = [2,3,4,0,4,1,0]
Output: 0
Explanation:
There are no possible valid selections.

Constraints:
1 <= nums.length <= 100
0 <= nums[i] <= 100
There is at least one element i where nums[i] == 0.
```

<details><summary>Hint</summary>

```text
1. Since the constraints are very small, you can simulate the process described.
```

</details>

</details>

<details><summary>C</summary>

```c
int countValidSelections(int* nums, int numsSize) {
    int retVal = 0;

    int left = 0;
    int right = 0;
    for (int i = 0; i < numsSize; i++) {
        right += nums[i];
    }

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == 0) {
            if ((left - right >= 0) && (left - right <= 1)) {
                retVal++;
            }
            if ((right - left) >= 0 && (right - left <= 1)) {
                retVal++;
            }
        } else {
            left += nums[i];
            right -= nums[i];
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
    int countValidSelections(vector<int>& nums) {
        int retVal = 0;

        int left = 0;
        int right = 0;
        for (int num : nums) {
            right += num;
        }

        for (int num : nums) {
            if (num == 0) {
                if ((left - right >= 0) && (left - right <= 1)) {
                    retVal++;
                }
                if ((right - left) >= 0 && (right - left <= 1)) {
                    retVal++;
                }
            } else {
                left += num;
                right -= num;
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
    def countValidSelections(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        left = 0
        right = sum(nums)
        for i in range(numsSize):
            if nums[i] == 0:
                if 0 <= (left - right) <= 1:
                    retVal += 1
                if 0 <= (right - left) <= 1:
                    retVal += 1
            else:
                left += nums[i]
                right -= nums[i]

        return retVal
```

</details>

## [3355. Zero Array Transformation I](https://leetcode.com/problems/zero-array-transformation-i/)  1591

- [Official](https://leetcode.com/problems/zero-array-transformation-i/editorial/)
- [Official](https://leetcode.cn/problems/zero-array-transformation-i/solutions/3674711/ling-shu-zu-bian-huan-i-by-leetcode-solu-7q94/)

<details><summary>Description</summary>

```text
You are given an integer array nums of length n and a 2D array queries, where queries[i] = [li, ri].

For each queries[i]:
- Select a subset of indices within the range [li, ri] in nums.
- Decrement the values at the selected indices by 1.

A Zero Array is an array where all elements are equal to 0.

Return true if it is possible to transform nums into a Zero Array after processing all the queries sequentially,
otherwise return false.

Example 1:
Input: nums = [1,0,1], queries = [[0,2]]
Output: true
Explanation:
For i = 0:
Select the subset of indices as [0, 2] and decrement the values at these indices by 1.
The array will become [0, 0, 0], which is a Zero Array.

Example 2:
Input: nums = [4,3,2,1], queries = [[1,3],[0,2]]
Output: false
Explanation:
For i = 0:
Select the subset of indices as [1, 2, 3] and decrement the values at these indices by 1.
The array will become [4, 2, 1, 0].
For i = 1:
Select the subset of indices as [0, 1, 2] and decrement the values at these indices by 1.
The array will become [3, 1, 0, 0], which is not a Zero Array.

Constraints:
1 <= nums.length <= 10^5
0 <= nums[i] <= 10^5
1 <= queries.length <= 10^5
queries[i].length == 2
0 <= li <= ri < nums.length
```

<details><summary>Hint</summary>

```text
1. Can we use difference array and prefix sum to check if an index can be made zero?
```

</details>

</details>

<details><summary>C</summary>

```c
bool isZeroArray(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize) {
    bool retVal = true;

    int deltaArray[numsSize + 1];
    memset(deltaArray, 0, sizeof(deltaArray));
    int left, right;
    for (int i = 0; i < queriesSize; i++) {
        left = queries[i][0];
        right = queries[i][1];
        deltaArray[left] += 1;
        deltaArray[right + 1] -= 1;
    }

    int operationCounts[numsSize + 1];
    memset(operationCounts, 0, sizeof(operationCounts));
    int currentOperations = 0;
    for (int i = 0; i < numsSize + 1; i++) {
        currentOperations += deltaArray[i];
        operationCounts[i] = currentOperations;
    }

    for (int i = 0; i < numsSize; i++) {
        if (operationCounts[i] < nums[i]) {
            retVal = false;
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
    bool isZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        bool retVal = true;

        int numsSize = nums.size();

        vector<int> deltaArray(numsSize + 1, 0);
        for (const auto& query : queries) {
            int left = query[0];
            int right = query[1];
            deltaArray[left] += 1;
            deltaArray[right + 1] -= 1;
        }

        vector<int> operationCounts;
        int currentOperations = 0;
        for (int delta : deltaArray) {
            currentOperations += delta;
            operationCounts.push_back(currentOperations);
        }

        for (int i = 0; i < numsSize; ++i) {
            if (operationCounts[i] < nums[i]) {
                retVal = false;
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
    def isZeroArray(self, nums: List[int], queries: List[List[int]]) -> bool:
        retVal = True

        numsSize = len(nums)

        deltaArray = [0] * (numsSize + 1)
        for left, right in queries:
            deltaArray[left] += 1
            deltaArray[right + 1] -= 1

        operationCounts = []
        currentOperations = 0
        for delta in deltaArray:
            currentOperations += delta
            operationCounts.append(currentOperations)

        for operations, target in zip(operationCounts, nums):
            if operations < target:
                retVal = False
                break

        return retVal
```

</details>

## [3381. Maximum Subarray Sum With Length Divisible by K](https://leetcode.com/problems/maximum-subarray-sum-with-length-divisible-by-k/)  1943

- [Official](https://leetcode.com/problems/maximum-subarray-sum-with-length-divisible-by-k/editorial/)
- [Official](https://leetcode.cn/problems/maximum-subarray-sum-with-length-divisible-by-k/solutions/3837035/chang-du-ke-bei-k-zheng-chu-de-zi-shu-zu-dzxb/)

<details><summary>Description</summary>

```text
You are given an array of integers nums and an integer k.

Return the maximum sum of a subarray of nums, such that the size of the subarray is divisible by k.

Example 1:
Input: nums = [1,2], k = 1
Output: 3
Explanation:
The subarray [1, 2] with sum 3 has length equal to 2 which is divisible by 1.

Example 2:
Input: nums = [-1,-2,-3,-4,-5], k = 4
Output: -10
Explanation:
The maximum sum subarray is [-1, -2, -3, -4] which has length equal to 4 which is divisible by 4.

Example 3:
Input: nums = [-5,1,2,-3,4], k = 2
Output: 4
Explanation:
The maximum sum subarray is [1, 2, -3, 4] which has length equal to 4 which is divisible by 2.

Constraints:
1 <= k <= nums.length <= 2 * 10^5
-10^9 <= nums[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Maintain minimum prefix sum ending at every possible index%k.
```

</details>

</details>

<details><summary>C</summary>

```c
long long maxSubarraySum(int* nums, int numsSize, int k) {
    long long retVal = 0;

    long long prefixSum = 0;
    long long maxSum = LONG_MIN;
    long long kSum[k];
    for (int i = 0; i < k; i++) {
        kSum[i] = LLONG_MAX / 2;
    }
    kSum[k - 1] = 0;

    for (int i = 0; i < numsSize; i++) {
        prefixSum += nums[i];
        if (prefixSum - kSum[i % k] > maxSum) {
            maxSum = prefixSum - kSum[i % k];
        }
        if (prefixSum < kSum[i % k]) {
            kSum[i % k] = prefixSum;
        }
    }
    retVal = maxSum;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long maxSubarraySum(vector<int>& nums, int k) {
        long long retVal = 0;

        int numsSize = nums.size();

        long long prefixSum = 0;
        long long maxSum = numeric_limits<long long>::min();
        vector<long long> kSum(k, numeric_limits<long long>::max() / 2);
        kSum[k - 1] = 0;
        for (int i = 0; i < numsSize; i++) {
            prefixSum += nums[i];
            maxSum = max(maxSum, prefixSum - kSum[i % k]);
            kSum[i % k] = min(kSum[i % k], prefixSum);
        }
        retVal = maxSum;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxSubarraySum(self, nums: List[int], k: int) -> int:
        retVal = 0

        numsSize = len(nums)

        prefixSum = 0
        maxSum = -sys.maxsize
        kSum = [sys.maxsize // 2] * k
        kSum[k - 1] = 0
        for i in range(numsSize):
            prefixSum += nums[i]
            maxSum = max(maxSum, prefixSum - kSum[i % k])
            kSum[i % k] = min(kSum[i % k], prefixSum)
        retVal = maxSum

        return retVal
```

</details>

## [3652. Best Time to Buy and Sell Stock using Strategy](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-using-strategy/)  1557

- [Official](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-using-strategy/editorial/)
- [Official](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-using-strategy/solutions/3852536/an-ce-lue-mai-mai-gu-piao-de-zui-jia-shi-9psd/)

<details><summary>Description</summary>

```text
You are given two integer arrays prices and strategy, where:
- prices[i] is the price of a given stock on the ith day.
- strategy[i] represents a trading action on the ith day, where:
  - -1 indicates buying one unit of the stock.
  - 0 indicates holding the stock.
  - 1 indicates selling one unit of the stock.

You are also given an even integer k, and may perform at most one modification to strategy. A modification consists of:
- Selecting exactly k consecutive elements in strategy.
- Set the first k / 2 elements to 0 (hold).
- Set the last k / 2 elements to 1 (sell).

The profit is defined as the sum of strategy[i] * prices[i] across all days.

Return the maximum possible profit you can achieve.

Note: There are no constraints on budget or stock ownership,
so all buy and sell operations are feasible regardless of past actions.

Example 1:
Input: prices = [4,2,8], strategy = [-1,0,1], k = 2
Output: 10
Explanation:
Modification Strategy Profit Calculation Profit
Original [-1, 0, 1] (-1 × 4) + (0 × 2) + (1 × 8) = -4 + 0 + 8 4
Modify [0, 1] [0, 1, 1] (0 × 4) + (1 × 2) + (1 × 8) = 0 + 2 + 8 10
Modify [1, 2] [-1, 0, 1] (-1 × 4) + (0 × 2) + (1 × 8) = -4 + 0 + 8 4
Thus, the maximum possible profit is 10, which is achieved by modifying the subarray [0, 1]​​​​​​​.

Example 2:
Input: prices = [5,4,3], strategy = [1,1,0], k = 2
Output: 9
Explanation:
Modification Strategy Profit Calculation Profit
Original [1, 1, 0] (1 × 5) + (1 × 4) + (0 × 3) = 5 + 4 + 0 9
Modify [0, 1] [0, 1, 0] (0 × 5) + (1 × 4) + (0 × 3) = 0 + 4 + 0 4
Modify [1, 2] [1, 0, 1] (1 × 5) + (0 × 4) + (1 × 3) = 5 + 0 + 3 8
Thus, the maximum possible profit is 9, which is achieved without any modification.

Constraints:
2 <= prices.length == strategy.length <= 10^5
1 <= prices[i] <= 10^5
-1 <= strategy[i] <= 1
2 <= k <= prices.length
k is even
```

<details><summary>Hint</summary>

```text
1. Use prefix sums to precompute the base profit and to get fast range queries
   (sums of prices and counts of each strategy value over any interval).
2. Try every segment of length k: compute the profit delta caused by replacing
   that segment (using the prefix queries) and take the maximum of base + delta.
```

</details>

</details>

<details><summary>C</summary>

```c
long long maxProfit(int* prices, int pricesSize, int* strategy, int strategySize, int k) {
    long long retVal = 0;

    long long profitSum[pricesSize + 1];
    memset(profitSum, 0, sizeof(profitSum));
    long long priceSum[pricesSize + 1];
    memset(priceSum, 0, sizeof(priceSum));

    for (int i = 0; i < pricesSize; i++) {
        profitSum[i + 1] = profitSum[i] + (long long)prices[i] * strategy[i];
        priceSum[i + 1] = priceSum[i] + prices[i];
    }
    retVal = profitSum[pricesSize];

    long long leftProfit, rightProfit, changeProfit, total;
    for (int i = k - 1; i < pricesSize; i++) {
        leftProfit = profitSum[i - k + 1];
        rightProfit = profitSum[pricesSize] - profitSum[i + 1];
        changeProfit = priceSum[i + 1] - priceSum[i - k / 2 + 1];
        total = leftProfit + changeProfit + rightProfit;
        if (total > retVal) {
            retVal = total;
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
    long long maxProfit(vector<int>& prices, vector<int>& strategy, int k) {
        long long retVal = 0;

        int pricesSize = prices.size();

        vector<long long> profitSum(pricesSize + 1);
        vector<long long> priceSum(pricesSize + 1);
        for (int i = 0; i < pricesSize; i++) {
            profitSum[i + 1] = profitSum[i] + prices[i] * strategy[i];
            priceSum[i + 1] = priceSum[i] + prices[i];
        }
        retVal = profitSum[pricesSize];

        for (int i = k - 1; i < pricesSize; i++) {
            long long leftProfit = profitSum[i - k + 1];
            long long rightProfit = profitSum[pricesSize] - profitSum[i + 1];
            long long changeProfit = priceSum[i + 1] - priceSum[i - k / 2 + 1];
            retVal = max(retVal, leftProfit + changeProfit + rightProfit);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxProfit(self, prices: List[int], strategy: List[int], k: int) -> int:
        retVal = 0

        pricesSize = len(prices)

        profitSum = [0] * (pricesSize + 1)
        priceSum = [0] * (pricesSize + 1)
        for i in range(pricesSize):
            profitSum[i + 1] = profitSum[i] + prices[i] * strategy[i]
            priceSum[i + 1] = priceSum[i] + prices[i]
        retVal = profitSum[pricesSize]

        for i in range(k - 1, pricesSize):
            leftProfit = profitSum[i - k + 1]
            rightProfit = profitSum[pricesSize] - profitSum[i + 1]
            changeProfit = priceSum[i + 1] - priceSum[i - k // 2 + 1]
            retVal = max(retVal, leftProfit + changeProfit + rightProfit)

        return retVal
```

</details>
