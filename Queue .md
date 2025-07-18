# [Queue](https://en.wikipedia.org/wiki/Queue_(abstract_data_type))

- [Heap](https://en.wikipedia.org/wiki/Heap_(data_structure))
- [Priority queue](https://en.wikipedia.org/wiki/Priority_queue)

## [215. Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/)

- [Official](https://leetcode.com/problems/kth-largest-element-in-an-array/editorial/)
- [Official](https://leetcode.cn/problems/kth-largest-element-in-an-array/solutions/307351/shu-zu-zhong-de-di-kge-zui-da-yuan-su-by-leetcode-/)

<details><summary>Description</summary>

```text
Given an integer array nums and an integer k, return the kth largest element in the array.

Note that it is the kth largest element in the sorted order, not the kth distinct element.

Can you solve it without sorting?

Example 1:
Input: nums = [3,2,1,5,6,4], k = 2
Output: 5

Example 2:
Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
Output: 4

Constraints:
1 <= k <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4
```

</details>

<details><summary>C</summary>

```c
#define HEAP (1)
#define QUICKSELECT (1)  // https://en.wikipedia.org/wiki/Quickselect
#if (HEAP)
void maxHeapify(int* a, int i, int heapSize) {
    int l = i * 2 + 1;
    int r = i * 2 + 2;
    int largest = i;

    if (l < heapSize && a[l] > a[largest]) {
        largest = l;
    }

    if (r < heapSize && a[r] > a[largest]) {
        largest = r;
    }

    if (largest != i) {
        int t = a[i];
        a[i] = a[largest], a[largest] = t;
        maxHeapify(a, largest, heapSize);
    }
}
void buildMaxHeap(int* a, int heapSize) {
    for (int i = heapSize / 2; i >= 0; --i) {
        maxHeapify(a, i, heapSize);
    }
}
#elif (QUICKSELECT)
inline int partition(int* a, int l, int r) {
    int x = a[r];
    int i = l - 1;
    int t;
    int j;
    for (j = l; j < r; ++j) {
        if (a[j] <= x) {
            t = a[++i];
            a[i] = a[j];
            a[j] = t;
        }
    }
    t = a[i + 1];
    a[i + 1] = a[r];
    a[r] = t;

    return i + 1;
}
inline int randomPartition(int* a, int l, int r) {
    int i = rand() % (r - l + 1) + l;
    int t = a[i];
    a[i] = a[r], a[r] = t;

    return partition(a, l, r);
}
int quickSelect(int* a, int l, int r, int index) {
    int q = randomPartition(a, l, r);

    if (q == index) {
        return a[q];
    } else {
        return q < index ? quickSelect(a, q + 1, r, index) : quickSelect(a, l, q - 1, index);
    }
}
#endif
int findKthLargest(int* nums, int numsSize, int k) {
    int retVal = 0;

#if (HEAP)
    printf("Heap\n\n");

    int heapSize = numsSize;
    buildMaxHeap(nums, heapSize);

    int t;
    int i;
    for (i = numsSize - 1; i >= numsSize - k + 1; --i) {
        t = nums[0];
        nums[0] = nums[i];
        nums[i] = t;
        --heapSize;
        maxHeapify(nums, 0, heapSize);
    }

    retVal = nums[0];
#elif (QUICKSELECT)
    printf("Quickselect\n\n");

    srand(time(0));
    retVal = quickSelect(nums, 0, numsSize - 1, numsSize - k);
#endif

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define HEAP (1)
#define QUICKSELECT (1)  // https://en.wikipedia.org/wiki/Quickselect
   public:
    Solution() {
#if (HEAP)
        cout << "Heap\n\n";
#elif (QUICKSELECT)
        cout << "Quickselect\n\n";
#endif
    }
#if (HEAP)
#elif (QUICKSELECT)
    int quickSelect(vector<int>& nums, int k) {
        int pivot = nums[rand() % nums.size()];

        vector<int> left;
        vector<int> middle;
        vector<int> right;
        for (int num : nums) {
            if (num > pivot) {
                left.push_back(num);
            } else if (num < pivot) {
                right.push_back(num);
            } else {
                middle.push_back(num);
            }
        }

        int leftSize = left.size();
        if (k <= leftSize) {
            return quickSelect(left, k);
        }

        int middleSize = middle.size();
        if (leftSize + middleSize < k) {
            return quickSelect(right, k - leftSize - middleSize);
        }

        return pivot;
    }
#endif
    int findKthLargest(vector<int>& nums, int k) {
        int retVal = 0;

#if (HEAP)
        priority_queue<int, vector<int>, greater<>> minHeap;
        for (int num : nums) {
            minHeap.push(num);
            int minHeapSize = minHeap.size();
            if (minHeapSize > k) {
                minHeap.pop();
            }
        }
        retVal = minHeap.top();
#elif (QUICKSELECT)
        retVal = quickSelect(nums, k);
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
        self.method = 1
        if self.method == 1:
            print("Heap")
        elif self.method == 2:
            print("Quickselect")    # https://en.wikipedia.org/wiki/Quickselect
        print()

    def findKthLargest(self, nums: List[int], k: int) -> int:
        retVal = 0

        if self.method == 1:      # Heap
            minHeap = []
            for num in nums:
                heappush(minHeap, num)
                if len(minHeap) > k:
                    heappop(minHeap)
            retVal = minHeap[0]
        elif self.method == 2:    # Quickselect
            def quick_select(nums, k):
                pivot = choice(nums)

                left = []
                middle = []
                right = []
                for num in nums:
                    if num > pivot:
                        left.append(num)
                    elif num < pivot:
                        right.append(num)
                    else:
                        middle.append(num)

                if k <= len(left):
                    return quick_select(left, k)

                if len(left) + len(middle) < k:
                    return quick_select(right, k - len(left) - len(middle))

                return pivot

            retVal = quick_select(nums, k)

        return retVal
```

</details>

## [232. Implement Queue using Stacks](https://leetcode.com/problems/implement-queue-using-stacks/)

- [Official](https://leetcode.com/problems/implement-queue-using-stacks/editorial/)
- [Official](https://leetcode.cn/problems/implement-queue-using-stacks/solutions/632369/yong-zhan-shi-xian-dui-lie-by-leetcode-s-xnb6/)

<details><summary>Description</summary>

```text
Implement a first in first out (FIFO) queue using only two stacks.
The implemented queue should support all the functions of a normal queue (push, peek, pop, and empty).

Implement the MyQueue class:
- void push(int x)
  Pushes element x to the back of the queue.
- int pop()
  Removes the element from the front of the queue and returns it.
- int peek()
  Returns the element at the front of the queue.
- boolean empty()
  Returns true if the queue is empty, false otherwise.

Notes:
- You must use only standard operations of a stack,
  which means only push to top, peek/pop from top, size, and is empty operations are valid.
- Depending on your language, the stack may not be supported natively.
  You may simulate a stack using a list or deque (double-ended queue)
  as long as you use only a stack's standard operations.

Example 1:
Input
["MyQueue", "push", "push", "peek", "pop", "empty"]
[[], [1], [2], [], [], []]
Output
[null, null, null, 1, 1, false]

Explanation
MyQueue myQueue = new MyQueue();
myQueue.push(1); // queue is: [1]
myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
myQueue.peek(); // return 1
myQueue.pop(); // return 1, queue is [2]
myQueue.empty(); // return false

Constraints:
1 <= x <= 9
At most 100 calls will be made to push, pop, peek, and empty.
All the calls to pop and peek are valid.

Follow-up:
Can you implement the queue such that each operation is amortized O(1) time complexity?
In other words, performing n operations will take overall O(n) time even if one of those operations may take longer.
```

</details>

<details><summary>C</summary>

```c
#ifndef STACK
#define STACK 1

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
    pNew->next = (*pTop);
    (*pTop) = pNew;
}
int pop(struct Node** pTop) {
    int retVal = INT_MIN;

    Node* pHead = (*pTop);
    if (pHead == NULL) {
        printf("Stack is Empty");
        return retVal;
    }
    retVal = pHead->data;
    (*pTop) = pHead->next;
    free(pHead);

    return retVal;
}
int peek(struct Node** pTop) {
    int retVal = INT_MIN;

    Node* pHead = (*pTop);
    if (pHead == NULL) {
        return retVal;
    }
    retVal = pHead->data;

    return retVal;
}
void stack_free(struct Node** pTop) {
    Node* pFree = (*pTop);
    while ((*pTop) != NULL) {
        (*pTop) = (*pTop)->next;
        free(pFree);
        pFree = (*pTop);
    }
}
#endif
typedef struct MyQueue {
    struct Node* inStack;
    struct Node* outStack;
} MyQueue;
MyQueue* myQueueCreate() {
    MyQueue* pRetVal = (MyQueue*)malloc(sizeof(struct MyQueue));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->inStack = NULL;
    pRetVal->outStack = NULL;

    return pRetVal;
}
void myQueuePush(MyQueue* obj, int x) {
    //
    push(&obj->inStack, x);
}
int myQueuePop(MyQueue* obj) {
    int retVal = INT_MIN;

    if ((obj->inStack == NULL) && (obj->outStack == NULL)) {
        return retVal;
    }

    if (obj->outStack == NULL) {
        while (obj->inStack != NULL) {
            retVal = pop(&obj->inStack);
            push(&obj->outStack, retVal);
        }
    }
    retVal = pop(&obj->outStack);

    return retVal;
}
int myQueuePeek(MyQueue* obj) {
    int retVal = INT_MIN;

    if ((obj->inStack == NULL) && (obj->outStack == NULL)) {
        return retVal;
    }

    if (obj->outStack == NULL) {
        while (obj->inStack != NULL) {
            retVal = pop(&obj->inStack);
            push(&obj->outStack, retVal);
        }
    }
    retVal = peek(&obj->outStack);

    return retVal;
}
bool myQueueEmpty(MyQueue* obj) {
    bool retVal = false;

    if ((obj->inStack == NULL) && (obj->outStack == NULL)) {
        retVal = true;
    }

    return retVal;
}
void myQueueFree(MyQueue* obj) {
    if (obj == NULL) {
        return;
    }
    stack_free(&obj->inStack);
    stack_free(&obj->outStack);
    free(obj);
}
/**
 * Your MyQueue struct will be instantiated and called as such:
 * MyQueue* obj = myQueueCreate();
 * myQueuePush(obj, x);
 * int param_2 = myQueuePop(obj);
 * int param_3 = myQueuePeek(obj);
 * bool param_4 = myQueueEmpty(obj);
 * myQueueFree(obj);
 */
```

</details>

<details><summary>C++</summary>

```c++
class MyQueue {
   private:
    stack<int> stackQueue;
    stack<int> stackTmp;

   public:
    MyQueue() {}
    void push(int x) {
        while (empty() == false) {
            stackTmp.push(pop());
        }

        stackQueue.push(x);

        while (stackTmp.empty() == false) {
            stackQueue.push(stackTmp.top());
            stackTmp.pop();
        }
    }
    int pop() {
        int retVal = 0;

        if (empty() == false) {
            retVal = stackQueue.top();
            stackQueue.pop();
        }

        return retVal;
    }
    int peek() {
        int retVal = stackQueue.top();

        return retVal;
    }
    bool empty() {
        bool retVal = stackQueue.empty();

        return retVal;
    }
};
/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
```

</details>

<details><summary>Python3</summary>

```python
class MyQueue:
    def __init__(self):
        self.stack = []
        self.stackTmp = []

    def push(self, x: int) -> None:
        while self.empty() == False:
            self.stackTmp.append(self.stack.pop())

        self.stack.append(x)

        while len(self.stackTmp) != 0:
            self.stack.append(self.stackTmp.pop())

    def pop(self) -> int:
        retVal = 0

        if self.empty() == False:
            retVal = self.stack.pop()

        return retVal

    def peek(self) -> int:
        retVal = self.stack[-1]

        return retVal

    def empty(self) -> bool:
        retVal = False

        if len(self.stack) == 0:
            retVal = True

        return retVal


# Your MyQueue object will be instantiated and called as such:
# obj = MyQueue()
# obj.push(x)
# param_2 = obj.pop()
# param_3 = obj.peek()
# param_4 = obj.empty()
```

</details>

## [239. Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum)

- [Official](https://leetcode.com/problems/sliding-window-maximum/editorial/)
- [Official](https://leetcode.cn/problems/sliding-window-maximum/solutions/543426/hua-dong-chuang-kou-zui-da-zhi-by-leetco-ki6m/)

<details><summary>Description</summary>

```text
You are given an array of integers nums,
there is a sliding window of size k which is moving from the very left of the array to the very right.
You can only see the k numbers in the window. Each time the sliding window moves right by one position.

Return the max sliding window.

Example 1:
Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Explanation:
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

Example 2:
Input: nums = [1], k = 1
Output: [1]

Constraints:
1 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4
1 <= k <= nums.length
```

<details><summary>Hint</summary>

```text
1. How about using a data structure such as deque (double-ended queue)?
2. The queue size need not be the same as the window’s size.
3. Remove redundant elements and the queue should store only elements that need to be considered.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *maxSlidingWindow(int *nums, int numsSize, int k, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int *)malloc((numsSize - k + 1) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, ((numsSize - k + 1) * sizeof(int)));

    int doubleEndedQueue[numsSize];
    memset(doubleEndedQueue, 0, sizeof(doubleEndedQueue));
    int doubleEndedQueueLeft = 0;
    int doubleEndedQueueRight = 0;

    int i;
    for (i = 0; i < k; ++i) {
        while ((doubleEndedQueueLeft < doubleEndedQueueRight) &&
               (nums[i] >= nums[doubleEndedQueue[doubleEndedQueueRight - 1]])) {
            doubleEndedQueueRight--;
        }
        doubleEndedQueue[doubleEndedQueueRight++] = i;
    }
    pRetVal[(*returnSize)++] = nums[doubleEndedQueue[doubleEndedQueueLeft]];

    for (i = k; i < numsSize; ++i) {
        while ((doubleEndedQueueLeft < doubleEndedQueueRight) &&
               (nums[i] >= nums[doubleEndedQueue[doubleEndedQueueRight - 1]])) {
            doubleEndedQueueRight--;
        }
        doubleEndedQueue[doubleEndedQueueRight++] = i;

        while (doubleEndedQueue[doubleEndedQueueLeft] <= i - k) {
            doubleEndedQueueLeft++;
        }
        pRetVal[(*returnSize)++] = nums[doubleEndedQueue[doubleEndedQueueLeft]];
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> retVal;

        deque<int> doubleEndedQueue;

        for (int i = 0; i < k; ++i) {
            while ((doubleEndedQueue.empty() == false) && (nums[i] >= nums[doubleEndedQueue.back()])) {
                doubleEndedQueue.pop_back();
            }
            doubleEndedQueue.push_back(i);
        }
        retVal.emplace_back(nums[doubleEndedQueue.front()]);

        int numsSize = nums.size();
        for (int i = k; i < numsSize; ++i) {
            while ((doubleEndedQueue.empty() == false) && (nums[i] >= nums[doubleEndedQueue.back()])) {
                doubleEndedQueue.pop_back();
            }
            doubleEndedQueue.push_back(i);

            while (doubleEndedQueue.front() <= i - k) {
                doubleEndedQueue.pop_front();
            }
            retVal.emplace_back(nums[doubleEndedQueue.front()]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        retVal = []

        doubleEndedQueue = deque()

        for i in range(k):
            while doubleEndedQueue and (nums[i] >= nums[doubleEndedQueue[-1]]):
                doubleEndedQueue.pop()
            doubleEndedQueue.append(i)
        retVal = [nums[doubleEndedQueue[0]]]

        numsSize = len(nums)
        for i in range(k, numsSize):
            while doubleEndedQueue and (nums[i] >= nums[doubleEndedQueue[-1]]):
                doubleEndedQueue.pop()
            doubleEndedQueue.append(i)

            while doubleEndedQueue[0] <= i - k:
                doubleEndedQueue.popleft()
            retVal.append(nums[doubleEndedQueue[0]])

        return retVal
```

</details>

## [295. Find Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/)

- [Official](https://leetcode.cn/problems/find-median-from-data-stream/solutions/961062/shu-ju-liu-de-zhong-wei-shu-by-leetcode-ktkst/)

<details><summary>Description</summary>

```text
The median is the middle value in an ordered integer list.
If the size of the list is even, there is no middle value, and the median is the mean of the two middle values.
- For example, for arr = [2,3,4], the median is 3.
- For example, for arr = [2,3], the median is (2 + 3) / 2 = 2.5.
- Implement the MedianFinder class:

MedianFinder() initializes the MedianFinder object.
- void addNum(int num) adds the integer num from the data stream to the data structure.
- double findMedian() returns the median of all elements so far. Answers within 10-5 of the actual answer will be accepted.

Example 1:
Input
["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
[[], [1], [2], [], [3], []]
Output
[null, null, null, 1.5, null, 2.0]
Explanation
MedianFinder medianFinder = new MedianFinder();
medianFinder.addNum(1);    // arr = [1]
medianFinder.addNum(2);    // arr = [1, 2]
medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
medianFinder.addNum(3);    // arr[1, 2, 3]
medianFinder.findMedian(); // return 2.0

Constraints:
-10^5 <= num <= 10^5
There will be at least one element in the data structure before calling findMedian.
At most 5 * 10^4 calls will be made to addNum and findMedian.

Follow up:
If all integer numbers from the stream are in the range [0, 100], how would you optimize your solution?
If 99% of all integer numbers from the stream are in the range [0, 100], how would you optimize your solution?
```

</details>

<details><summary>C</summary>

```c
// https://leetcode.cn/problems/find-median-from-data-stream/solutions/1429457/by-goodgoodday-rcen/
#ifndef HEAP_H
#define HEAP_H

typedef struct Heap {
    int* array;
    int capacity;
    int len;
} Heap;
int HeapLen(Heap* hp) {
    int retVal = hp->len;

    return retVal;
}
bool HeapEmpty(Heap* hp) {
    bool retVal = true;

    if (HeapLen(hp) == 1) {
        return retVal;
    }
    retVal = false;

    return retVal;
}
bool HeapFull(Heap* hp) {
    bool retVal = true;

    if (hp->capacity == hp->len) {
        return retVal;
    }
    retVal = false;

    return retVal;
}
void HeapSwap(int* pLeft, int* pRight) {
    int temp = *pLeft;
    *pLeft = *pRight;
    *pRight = temp;
}
int HeapGetTop(Heap* hp) {
    int retVal = hp->array[1];

    return retVal;
}
Heap* CreateHeap(int size) {
    Heap* heap = NULL;

    heap = (Heap*)malloc(sizeof(Heap));
    if (heap == NULL) {
        perror("malloc");
        return heap;
    }

    int heapLen = size + 1;
    heap->array = (int*)malloc(sizeof(int) * heapLen);
    if (heap->array == NULL) {
        perror("malloc");
        free(heap);
        heap = NULL;
        return heap;
    }
    heap->capacity = heapLen;
    heap->len = 1;

    return heap;
}
void HeapAdjustDown(Heap* hp, int parent, bool isMax) {
    int child = 2 * parent;
    int len = hp->len;
    while (child < len) {
        if (isMax == true) {
            if ((child + 1 < len) && hp->array[child] < hp->array[child + 1]) {
                child = child + 1;
            }

            if (hp->array[child] > hp->array[parent]) {
                HeapSwap(&hp->array[child], &hp->array[parent]);
                parent = child;
                child = parent << 1;
            } else {
                return;
            }
        } else {
            if ((child + 1 < len) && hp->array[child] > hp->array[child + 1]) {
                child = child + 1;
            }

            if (hp->array[child] < hp->array[parent]) {
                HeapSwap(&hp->array[child], &hp->array[parent]);
                parent = child;
                child = parent << 1;
            } else {
                return;
            }
        }
    }
}
void HeapAdjustUp(Heap* hp, int child, bool isMax) {
    int parent = child / 2;
    while (child > 1) {
        if (isMax == true) {
            if (hp->array[child] > hp->array[parent]) {
                HeapSwap(&hp->array[child], &hp->array[parent]);
                child = parent;
                parent = child / 2;
            } else {
                return;
            }
        } else {
            if (hp->array[child] < hp->array[parent]) {
                HeapSwap(&hp->array[child], &hp->array[parent]);
                child = parent;
                parent = child / 2;
            } else {
                return;
            }
        }
    }
}
void HeapDelete(Heap* hp, bool isMax) {
    if (HeapEmpty(hp) == true) {
        return;
    }

    hp->array[1] = hp->array[hp->len - 1];
    hp->len--;
    HeapAdjustDown(hp, 1, isMax);
}
void HeapInsert(Heap* hp, int dat, bool isMax) {
    if (HeapFull(hp) == true) {
        hp->capacity <<= 1;
        hp->array = (int*)realloc(hp->array, hp->capacity * sizeof(int));
    }
    hp->array[hp->len++] = dat;
    HeapAdjustUp(hp, hp->len - 1, isMax);
}
void heapFree(Heap* hp) {
    free(hp->array);
    hp->array = NULL;
    free(hp);
    hp = NULL;
}

#endif  // HEAP_H
typedef struct {
    Heap* maxLHeap;
    Heap* minRHeap;
} MedianFinder;
MedianFinder* medianFinderCreate() {
    MedianFinder* pRetVal = NULL;

    pRetVal = (MedianFinder*)malloc(sizeof(MedianFinder));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->maxLHeap = CreateHeap(128);
    pRetVal->minRHeap = CreateHeap(128);

    return pRetVal;
}
void medianFinderAddNum(MedianFinder* obj, int num) {
    int maxLHeapSize = obj->maxLHeap->len;
    int minRHeapSize = obj->minRHeap->len;

    int moveValue;

    if (maxLHeapSize <= minRHeapSize) {
        if (HeapEmpty(obj->minRHeap) == false) {
            if (num > obj->minRHeap->array[1]) {
                moveValue = obj->minRHeap->array[1];
                obj->minRHeap->array[1] = num;
                HeapAdjustDown(obj->minRHeap, 1, false);
                HeapInsert(obj->maxLHeap, moveValue, true);

                return;
            }
        }
        HeapInsert(obj->maxLHeap, num, true);

        return;
    }

    if (HeapEmpty(obj->maxLHeap) == false) {
        if (num < obj->maxLHeap->array[1]) {
            moveValue = obj->maxLHeap->array[1];
            obj->maxLHeap->array[1] = num;
            HeapAdjustDown(obj->maxLHeap, 1, true);
            HeapInsert(obj->minRHeap, moveValue, false);

            return;
        }
    }
    HeapInsert(obj->minRHeap, num, false);
}
double medianFinderFindMedian(MedianFinder* obj) {
    double retVal = 0;

    int maxLHeapSize = obj->maxLHeap->len;
    int minRHeapSize = obj->minRHeap->len;
    if (maxLHeapSize == minRHeapSize) {
        retVal = (double)(obj->minRHeap->array[1] + obj->maxLHeap->array[1]) / 2;
    } else {
        retVal = (double)(obj->maxLHeap->array[1]);
    }

    return retVal;
}
void medianFinderFree(MedianFinder* obj) {
    heapFree(obj->maxLHeap);
    obj->maxLHeap = NULL;
    heapFree(obj->minRHeap);
    obj->minRHeap = NULL;
    free(obj);
    obj = NULL;
}
/*
 * Your MedianFinder struct will be instantiated and called as such:
 * MedianFinder* obj = medianFinderCreate();
 * medianFinderAddNum(obj, num);
 * double param_2 = medianFinderFindMedian(obj);
 * medianFinderFree(obj);
 */
```

</details>

<details><summary>C++</summary>

```c++
class MedianFinder {
   public:
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;

    MedianFinder() {}
    void addNum(int num) {
        maxHeap.push(num);
        minHeap.push(maxHeap.top());
        maxHeap.pop();

        int maxHeapSize = maxHeap.size();
        int minHeapSize = minHeap.size();
        if (minHeapSize > maxHeapSize) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    double findMedian() {
        double retVal = maxHeap.top();

        int maxHeapSize = maxHeap.size();
        int minHeapSize = minHeap.size();
        if (maxHeapSize > minHeapSize) {
            return retVal;
        }
        retVal = (maxHeap.top() + minHeap.top()) / 2.0;

        return retVal;
    }
};
/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
```

</details>

<details><summary>Python3</summary>

```python
class MedianFinder:
    def __init__(self):
        self.minHeap = []
        self.maxHeap = []

    def addNum(self, num: int) -> None:
        heappush(self.maxHeap, -num)
        heappush(self.minHeap, -heappop(self.maxHeap))

        maxHeapSize = len(self.maxHeap)
        minHeapSize = len(self.minHeap)
        if minHeapSize > maxHeapSize:
            heappush(self.maxHeap, -heappop(self.minHeap))

    def findMedian(self) -> float:
        retVal = -self.maxHeap[0]

        maxHeapSize = len(self.maxHeap)
        minHeapSize = len(self.minHeap)
        if maxHeapSize > minHeapSize:
            return retVal
        retVal = (-self.maxHeap[0] + self.minHeap[0]) / 2

        return retVal


# Your MedianFinder object will be instantiated and called as such:
# obj = MedianFinder()
# obj.addNum(num)
# param_2 = obj.findMedian()
```

</details>

## [373. Find K Pairs with Smallest Sums](https://leetcode.com/problems/find-k-pairs-with-smallest-sums/)

- [Official](https://leetcode.com/problems/find-k-pairs-with-smallest-sums/editorial/)
- [Official](https://leetcode.cn/problems/find-k-pairs-with-smallest-sums/solutions/1208350/cha-zhao-he-zui-xiao-de-kdui-shu-zi-by-l-z526/)

<details><summary>Description</summary>

```text
You are given two integer arrays nums1 and nums2 sorted in ascending order and an integer k.

Define a pair (u, v) which consists of one element from the first array and one element from the second array.

Return the k pairs (u1, v1), (u2, v2), ..., (uk, vk) with the smallest sums.

Example 1:
Input: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
Output: [[1,2],[1,4],[1,6]]
Explanation: The first 3 pairs are returned from the sequence: [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]

Example 2:
Input: nums1 = [1,1,2], nums2 = [1,2,3], k = 2
Output: [[1,1],[1,1]]
Explanation: The first 2 pairs are returned from the sequence: [1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]

Example 3:
Input: nums1 = [1,2], nums2 = [3], k = 3
Output: [[1,3],[2,3]]
Explanation: All possible pairs are returned from the sequence: [1,3],[2,3]

Constraints:
1 <= nums1.length, nums2.length <= 10^5
-10^9 <= nums1[i], nums2[i] <= 10^9
nums1 and nums2 both are sorted in ascending order.
1 <= k <= 10^4
```

</details>

<details><summary>C</summary>

```c
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** kSmallestPairs(int* nums1, int nums1Size, int* nums2, int nums2Size, int k, int* returnSize,
                     int** returnColumnSizes) {
    int** pRetVal = NULL;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<vector<int>> retVal;

        int nums1Size = nums1.size();
        int nums2Size = nums2.size();

        set<pair<int, int>> visited;

        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>>
            minHeap;
        minHeap.push({nums1[0] + nums2[0], {0, 0}});
        visited.insert({0, 0});
        while ((k > 0) && (minHeap.empty() == false)) {
            auto top = minHeap.top();
            minHeap.pop();
            int i = top.second.first;
            int j = top.second.second;
            retVal.push_back({nums1[i], nums2[j]});

            if ((i + 1 < nums1Size) && (visited.find({i + 1, j}) == visited.end())) {
                minHeap.push({nums1[i + 1] + nums2[j], {i + 1, j}});
                visited.insert({i + 1, j});
            }

            if ((j + 1 < nums2Size && visited.find({i, j + 1}) == visited.end())) {
                minHeap.push({nums1[i] + nums2[j + 1], {i, j + 1}});
                visited.insert({i, j + 1});
            }

            --k;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def kSmallestPairs(self, nums1: List[int], nums2: List[int], k: int) -> List[List[int]]:
        retVal = []

        nums1Size = len(nums1)
        nums2Size = len(nums2)

        visited = set()

        minHeap = [(nums1[0] + nums2[0], (0, 0))]
        visited.add((0, 0))
        count = 0
        while k > 0 and minHeap:
            val, (i, j) = heappop(minHeap)
            retVal.append([nums1[i], nums2[j]])

            if i + 1 < nums1Size and (i + 1, j) not in visited:
                heappush(minHeap, (nums1[i + 1] + nums2[j], (i + 1, j)))
                visited.add((i + 1, j))

            if j + 1 < nums2Size and (i, j + 1) not in visited:
                heappush(minHeap, (nums1[i] + nums2[j + 1], (i, j + 1)))
                visited.add((i, j + 1))

            k = k - 1

        return retVal
```

</details>

## [502. IPO](https://leetcode.com/problems/ipo/)

- [Official](https://leetcode.cn/problems/ipo/solutions/984750/ipo-by-leetcode-solution-89zm/)

<details><summary>Description</summary>

```text
Suppose LeetCode will start its IPO soon.
In order to sell a good price of its shares to Venture Capital,
LeetCode would like to work on some projects to increase its capital before the IPO.
Since it has limited resources, it can only finish at most k distinct projects before the IPO.
Help LeetCode design the best way to maximize its total capital after finishing at most k distinct projects.

You are given n projects where the ith project has a pure profit profits[i]
and a minimum capital of capital[i] is needed to start it.

Initially, you have w capital. When you finish a project,
you will obtain its pure profit and the profit will be added to your total capital.

Pick a list of at most k distinct projects from given projects to maximize your final capital,
and return the final maximized capital.

The answer is guaranteed to fit in a 32-bit signed integer.

Example 1:
Input: k = 2, w = 0, profits = [1,2,3], capital = [0,1,1]
Output: 4
Explanation: Since your initial capital is 0, you can only start the project indexed 0.
After finishing it you will obtain profit 1 and your capital becomes 1.
With capital 1, you can either start the project indexed 1 or the project indexed 2.
Since you can choose at most 2 projects, you need to finish the project indexed 2 to get the maximum capital.
Therefore, output the final maximized capital, which is 0 + 1 + 3 = 4.

Example 2:
Input: k = 3, w = 0, profits = [1,2,3], capital = [0,1,2]
Output: 6

Constraints:
1 <= k <= 10^5
0 <= w <= 10^9
n == profits.length
n == capital.length
1 <= n <= 10^5
0 <= profits[i] <= 10^4
0 <= capital[i] <= 10^9
```

</details>

<details><summary>C</summary>

```c
// https://leetcode.cn/problems/ipo/solutions/269573/liang-ge-shu-lie-fen-bie-pai-xu-by-ni8fun/
typedef struct {
    int profit;
    int capital;
} projectsNode_t;
int compareStructCapital(const void* a, const void* b) {
    projectsNode_t* p1 = (projectsNode_t*)a;
    projectsNode_t* p2 = (projectsNode_t*)b;

    // ascending order
    return (p1->capital > p2->capital);
}
int compareStructProfit(const void* a, const void* b) {
    projectsNode_t* p1 = (projectsNode_t*)a;
    projectsNode_t* p2 = (projectsNode_t*)b;

    // ascending order
    return (p1->profit > p2->profit);
}
int findMaximizedCapital(int k, int w, int* profits, int profitsSize, int* capital, int capitalSize) {
    int retVal = 0;

    int idxProjects = 0;
    projectsNode_t projects[profitsSize];
    memset(projects, 0, sizeof(projects));
    int i;
    for (i = 0; i < profitsSize; i++) {
        projects[i].profit = profits[i];
        projects[i].capital = capital[i];
    }
    qsort(projects, profitsSize, sizeof(projectsNode_t), compareStructCapital);

    int idxCopyProjects = 0;
    projectsNode_t copyProjects[profitsSize];
    memset(copyProjects, 0, sizeof(copyProjects));
    bool inserted;
    while (k > 0) {
        inserted = false;
        while ((idxProjects < profitsSize) && (projects[idxProjects].capital <= w)) {
            inserted = true;
            copyProjects[idxCopyProjects] = projects[idxProjects];
            idxCopyProjects++;
            idxProjects++;
        }

        if (idxCopyProjects > 0) {
            if (inserted == true) {
                qsort(copyProjects, idxCopyProjects, sizeof(projectsNode_t), compareStructProfit);
            }
            w += copyProjects[idxCopyProjects - 1].profit;
            idxCopyProjects--;
        }

        k--;
    }
    retVal = w;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        int retVal = w;

        int profitsSize = profits.size();

        vector<pair<int, int>> projects;
        for (int i = 0; i < profitsSize; ++i) {
            projects.emplace_back(capital[i], profits[i]);
        }
        sort(projects.begin(), projects.end());

        priority_queue<int> priorityQueue;
        int ptr = 0;
        for (int i = 0; i < k; ++i) {
            while ((ptr < profitsSize) && (projects[ptr].first <= retVal)) {
                priorityQueue.push(projects[ptr++].second);
            }

            if (priorityQueue.empty()) {
                break;
            }

            retVal += priorityQueue.top();
            priorityQueue.pop();
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def findMaximizedCapital(self, k: int, w: int, profits: List[int], capital: List[int]) -> int:
        retVal = 0

        # https://leetcode.com/problems/ipo/solutions/3219987/day-54-c-priority-queue-easiest-beginner-friendly-sol
        profitsSize = len(profits)
        projects = [(capital[i], profits[i]) for i in range(profitsSize)]
        projects.sort()

        i = 0
        maximizeCapital = []
        while k > 0:
            while (i < profitsSize) and (projects[i][0] <= w):
                heappush(maximizeCapital, -projects[i][1])
                i += 1
            if not maximizeCapital:
                break
            w -= heappop(maximizeCapital)
            k -= 1
        retVal = w

        return retVal
```

</details>

## [622. Design Circular Queue](https://leetcode.com/problems/design-circular-queue/)

<details><summary>Description</summary>

```text
Design your implementation of the circular queue.
The circular queue is a linear data structure in which
the operations are performed based on FIFO (First In First Out) principle,
and the last position is connected back to the first position to make a circle. It is also called "Ring Buffer".

One of the benefits of the circular queue is that we can make use of the spaces in front of the queue.
In a normal queue, once the queue becomes full,
we cannot insert the next element even if there is a space in front of the queue.
But using the circular queue, we can use the space to store new values.

Implement the MyCircularQueue class:
- MyCircularQueue(k) Initializes the object with the size of the queue to be k.
- int Front() Gets the front item from the queue. If the queue is empty, return -1.
- int Rear() Gets the last item from the queue. If the queue is empty, return -1.
- boolean enQueue(int value) Inserts an element into the circular queue. Return true if the operation is successful.
- boolean deQueue() Deletes an element from the circular queue. Return true if the operation is successful.
- boolean isEmpty() Checks whether the circular queue is empty or not.
- boolean isFull() Checks whether the circular queue is full or not.

You must solve the problem without using the built-in queue data structure in your programming language.

Example 1:
Input
["MyCircularQueue", "enQueue", "enQueue", "enQueue", "enQueue", "Rear", "isFull", "deQueue", "enQueue", "Rear"]
[[3], [1], [2], [3], [4], [], [], [], [4], []]
Output
[null, true, true, true, false, 3, true, true, true, 4]
Explanation
MyCircularQueue myCircularQueue = new MyCircularQueue(3);
myCircularQueue.enQueue(1); // return True
myCircularQueue.enQueue(2); // return True
myCircularQueue.enQueue(3); // return True
myCircularQueue.enQueue(4); // return False
myCircularQueue.Rear();     // return 3
myCircularQueue.isFull();   // return True
myCircularQueue.deQueue();  // return True
myCircularQueue.enQueue(4); // return True
myCircularQueue.Rear();     // return 4

Constraints:
1 <= k <= 1000
0 <= value <= 1000
At most 3000 calls will be made to enQueue, deQueue, Front, Rear, isEmpty, and isFull.
```

</details>

<details><summary>C</summary>

```c
typedef struct {
    int size;
    int head;
    int tail;
    int count;
    int* value;
} MyCircularQueue;

MyCircularQueue* myCircularQueueCreate(int k) {
    MyCircularQueue* pNew = (MyCircularQueue*)malloc(sizeof(MyCircularQueue));
    if (pNew == NULL) {
        perror("malloc");
        return pNew;
    }
    pNew->size = k;
    pNew->head = 0;
    pNew->tail = 0;
    pNew->count = 0;
    pNew->value = (int*)malloc(pNew->size * sizeof(int));
    if (pNew->value == NULL) {
        perror("malloc");
        return pNew;
    }
    memset(pNew->value, 0, (pNew->size*sizeof(int)));

    return pNew;
}

bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
    if (obj->count == 0) {
        return true;
    }
    return false;
}

bool myCircularQueueIsFull(MyCircularQueue* obj) {
    if (obj->count == obj->size) {
        return true;
    }
    return false;
}

bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
    if (myCircularQueueIsFull(obj) == true) {
        return false;
    }
    obj->count++;
    obj->value[obj->tail] = value;
    obj->tail = (obj->tail + 1) % obj->size;
    return true;
}

bool myCircularQueueDeQueue(MyCircularQueue* obj) {
    if (myCircularQueueIsEmpty(obj) == true) {
        return false;
    }
    obj->count--;
    obj->value[obj->head] = 0;
    obj->head = (obj->head + 1) % obj->size;
    return true;
}

int myCircularQueueFront(MyCircularQueue* obj) {
    if (myCircularQueueIsEmpty(obj) == true) {
        return -1;
    }
    return obj->value[obj->head];
}

int myCircularQueueRear(MyCircularQueue* obj) {
    if (myCircularQueueIsEmpty(obj) == true) {
        return -1;
    }
    return obj->value[(obj->tail-1+obj->size)%obj->size];
}

void myCircularQueueFree(MyCircularQueue* obj) {
    free(obj->value);
    obj->value = NULL;
    free(obj);
    obj = NULL;
}

/**
 * Your MyCircularQueue struct will be instantiated and called as such:
 * MyCircularQueue* obj = myCircularQueueCreate(k);
 * bool param_1 = myCircularQueueEnQueue(obj, value);

 * bool param_2 = myCircularQueueDeQueue(obj);

 * int param_3 = myCircularQueueFront(obj);

 * int param_4 = myCircularQueueRear(obj);

 * bool param_5 = myCircularQueueIsEmpty(obj);

 * bool param_6 = myCircularQueueIsFull(obj);

 * myCircularQueueFree(obj);
*/
```

</details>

<details><summary>C++</summary>

```c++
class MyCircularQueue {
private:
    vector<int> data;
    int head;
    int tail;
    int size;
public:
    /** Initialize your data structure here. Set the size of the queue to be k. */
    MyCircularQueue(int k) {
        data.resize(k);
        head = -1;
        tail = -1;
        size = k;
    }

    /** Insert an element into the circular queue. Return true if the operation is successful. */
    bool enQueue(int value) {
        if (isFull()) {
            return false;
        }
        if (isEmpty()) {
            head = 0;
        }
        tail = (tail + 1) % size;
        data[tail] = value;
        return true;
    }

    /** Delete an element from the circular queue. Return true if the operation is successful. */
    bool deQueue() {
        if (isEmpty()) {
            return false;
        }
        if (head == tail) {
            head = -1;
            tail = -1;
            return true;
        }
        head = (head + 1) % size;
        return true;
    }

    /** Get the front item from the queue. */
    int Front() {
        if (isEmpty()) {
            return -1;
        }
        return data[head];
    }

    /** Get the last item from the queue. */
    int Rear() {
        if (isEmpty()) {
            return -1;
        }
        return data[tail];
    }

    /** Checks whether the circular queue is empty or not. */
    bool isEmpty() {
        return head == -1;
    }

    /** Checks whether the circular queue is full or not. */
    bool isFull() {
        return ((tail + 1) % size) == head;
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue obj = new MyCircularQueue(k);
 * bool param_1 = obj.enQueue(value);
 * bool param_2 = obj.deQueue();
 * int param_3 = obj.Front();
 * int param_4 = obj.Rear();
 * bool param_5 = obj.isEmpty();
 * bool param_6 = obj.isFull();
 */
```

</details>

## [641. Design Circular Deque](https://leetcode.com/problems/design-circular-deque/)

- [Official](https://leetcode.com/problems/design-circular-deque/editorial/)
- [Official](https://leetcode.cn/problems/design-circular-deque/solutions/1743694/she-ji-xun-huan-shuang-duan-dui-lie-by-l-97v0/)

<details><summary>Description</summary>

```text
Design your implementation of the circular double-ended queue (deque).

Implement the MyCircularDeque class:
- MyCircularDeque(int k)
  Initializes the deque with a maximum size of k.
- boolean insertFront()
  Adds an item at the front of Deque. Returns true if the operation is successful, or false otherwise.
- boolean insertLast()
  Adds an item at the rear of Deque. Returns true if the operation is successful, or false otherwise.
- boolean deleteFront()
  Deletes an item from the front of Deque. Returns true if the operation is successful, or false otherwise.
- boolean deleteLast()
  Deletes an item from the rear of Deque. Returns true if the operation is successful, or false otherwise.
- int getFront()
  Returns the front item from the Deque. Returns -1 if the deque is empty.
- int getRear()
  Returns the last item from Deque. Returns -1 if the deque is empty.
- boolean isEmpty()
  Returns true if the deque is empty, or false otherwise.
- boolean isFull()
  Returns true if the deque is full, or false otherwise.

Example 1:
Input
["MyCircularDeque", "insertLast", "insertLast", "insertFront", "insertFront",
"getRear", "isFull", "deleteLast", "insertFront", "getFront"]
[[3], [1], [2], [3], [4], [], [], [], [4], []]
Output
[null, true, true, true, false, 2, true, true, true, 4]

Explanation
MyCircularDeque myCircularDeque = new MyCircularDeque(3);
myCircularDeque.insertLast(1);  // return True
myCircularDeque.insertLast(2);  // return True
myCircularDeque.insertFront(3); // return True
myCircularDeque.insertFront(4); // return False, the queue is full.
myCircularDeque.getRear();      // return 2
myCircularDeque.isFull();       // return True
myCircularDeque.deleteLast();   // return True
myCircularDeque.insertFront(4); // return True
myCircularDeque.getFront();     // return 4

Constraints:
1 <= k <= 1000
0 <= value <= 1000
At most 2000 calls will be made to insertFront, insertLast, deleteFront, deleteLast, getFront, getRear, isEmpty, isFull.
```

</details>

<details><summary>C</summary>

```c
typedef struct DLinkListNode {
    int val;
    struct DLinkListNode* prev;
    struct DLinkListNode* next;
} DLinkListNode;
DLinkListNode* dLinkListNodeCreat(int val) {
    DLinkListNode* obj = NULL;

    obj = (DLinkListNode*)malloc(sizeof(DLinkListNode));
    if (obj == NULL) {
        perror("malloc");
        return obj;
    }
    obj->val = val;
    obj->prev = NULL;
    obj->next = NULL;

    return obj;
}
typedef struct {
    int capacity;
    DLinkListNode* head;
    DLinkListNode* tail;
    int size;
} MyCircularDeque;
MyCircularDeque* myCircularDequeCreate(int k) {
    MyCircularDeque* obj = NULL;

    obj = (MyCircularDeque*)malloc(sizeof(MyCircularDeque));
    if (obj == NULL) {
        perror("malloc");
        return obj;
    }
    obj->capacity = k;
    obj->head = NULL;
    obj->tail = NULL;
    obj->size = 0;

    return obj;
}
bool myCircularDequeIsEmpty(MyCircularDeque* obj) {
    bool retVal = false;

    if (obj->size == 0) {
        retVal = true;
    }

    return retVal;
}
bool myCircularDequeIsFull(MyCircularDeque* obj) {
    bool retVal = false;

    if (obj->size == obj->capacity) {
        retVal = true;
    }

    return retVal;
}
bool myCircularDequeInsertFront(MyCircularDeque* obj, int value) {
    bool retVal = false;

    if (myCircularDequeIsFull(obj) == true) {
        return retVal;
    }

    DLinkListNode* pNew = dLinkListNodeCreat(value);
    if (pNew == NULL) {
        return retVal;
    }

    if (obj->size == 0) {
        obj->head = pNew;
        obj->tail = pNew;
    } else {
        pNew->next = obj->head;
        obj->head->prev = pNew;
        obj->head = pNew;
    }
    obj->size++;
    retVal = true;

    return retVal;
}
bool myCircularDequeInsertLast(MyCircularDeque* obj, int value) {
    bool retVal = false;

    if (myCircularDequeIsFull(obj) == true) {
        return retVal;
    }

    DLinkListNode* pNew = dLinkListNodeCreat(value);
    if (pNew == NULL) {
        return retVal;
    }

    if (obj->size == 0) {
        obj->head = pNew;
        obj->tail = pNew;
    } else {
        obj->tail->next = pNew;
        pNew->prev = obj->tail;
        obj->tail = pNew;
    }
    obj->size++;
    retVal = true;

    return retVal;
}
bool myCircularDequeDeleteFront(MyCircularDeque* obj) {
    bool retVal = false;

    if (myCircularDequeIsEmpty(obj) == true) {
        return retVal;
    }

    DLinkListNode* pDelete = obj->head;
    obj->head = obj->head->next;
    if (obj->head != NULL) {
        obj->head->prev = NULL;
    }
    free(pDelete);
    pDelete = NULL;
    obj->size--;
    retVal = true;

    return retVal;
}
bool myCircularDequeDeleteLast(MyCircularDeque* obj) {
    bool retVal = false;

    if (myCircularDequeIsEmpty(obj) == true) {
        return retVal;
    }

    DLinkListNode* pDelete = obj->tail;
    obj->tail = obj->tail->prev;
    if (obj->tail != NULL) {
        obj->tail->next = NULL;
    }
    free(pDelete);
    pDelete = NULL;
    obj->size--;
    retVal = true;

    return retVal;
}
int myCircularDequeGetFront(MyCircularDeque* obj) {
    int retVal = -1;  // Returns -1 if the deque is empty.

    if (myCircularDequeIsEmpty(obj) == false) {
        retVal = obj->head->val;
    }

    return retVal;
}
int myCircularDequeGetRear(MyCircularDeque* obj) {
    int retVal = -1;  // Returns -1 if the deque is empty.

    if (myCircularDequeIsEmpty(obj) == false) {
        retVal = obj->tail->val;
    }

    return retVal;
}
void myCircularDequeFree(MyCircularDeque* obj) {
    DLinkListNode* pDelete = NULL;
    while (obj->head != obj->tail) {
        pDelete = obj->head;
        obj->head = obj->head->next;
        free(pDelete);
        pDelete = NULL;
    }
    free(obj->head);
    obj->head = NULL;

    free(obj);
    obj = NULL;
}
/**
 * Your MyCircularDeque struct will be instantiated and called as such:
 * MyCircularDeque* obj = myCircularDequeCreate(k);
 * bool param_1 = myCircularDequeInsertFront(obj, value);
 * bool param_2 = myCircularDequeInsertLast(obj, value);
 * bool param_3 = myCircularDequeDeleteFront(obj);
 * bool param_4 = myCircularDequeDeleteLast(obj);
 * int param_5 = myCircularDequeGetFront(obj);
 * int param_6 = myCircularDequeGetRear(obj);
 * bool param_7 = myCircularDequeIsEmpty(obj);
 * bool param_8 = myCircularDequeIsFull(obj);
 * myCircularDequeFree(obj);
 */
```

</details>

<details><summary>C++</summary>

```c++
struct Node {
    int val;
    Node* next;
    Node* prev;
    Node(int val, Node* next = NULL, Node* prev = NULL) : val(val), next(next), prev(prev) {}
};
class MyCircularDeque {
   private:
    int capacity;
    Node* head;
    Node* rear;
    int size;

   public:
    MyCircularDeque(int k) {
        capacity = k;
        head = nullptr;
        rear = nullptr;
        size = 0;
    }
    ~MyCircularDeque() {
        while (head != rear) {
            Node* pCurrent = head;
            head = head->next;
            delete pCurrent;
        }
        delete head;
    }
    bool insertFront(int value) {
        bool retVal = false;

        if (isFull() == true) {
            return retVal;
        }

        if (head == NULL) {
            head = new Node(value);
            rear = head;
        } else {
            Node* newHead = new Node(value);
            newHead->next = head;
            head->prev = newHead;
            head = newHead;
        }
        size++;
        retVal = true;

        return retVal;
    }
    bool insertLast(int value) {
        bool retVal = false;

        if (isFull() == true) {
            return retVal;
        }

        if (head == NULL) {
            head = new Node(value);
            rear = head;
        } else {
            Node* newNode = new Node(value, NULL, rear);
            rear->next = newNode;
            rear = newNode;
        }
        size++;
        retVal = true;

        return retVal;
    }
    bool deleteFront() {
        bool retVal = false;

        if (isEmpty() == true) {
            return retVal;
        }

        if (size == 1) {
            head = NULL;
            rear = NULL;
        } else {
            Node* nextNode = head->next;
            delete head;
            head = nextNode;
        }
        size--;
        retVal = true;

        return retVal;
    }
    bool deleteLast() {
        bool retVal = false;

        if (isEmpty() == true) {
            return retVal;
        }

        if (size == 1) {
            head = NULL;
            rear = NULL;
        } else {
            Node* prevNode = rear->prev;
            delete rear;
            rear = prevNode;
        }
        size--;
        retVal = true;

        return retVal;
    }
    int getFront() {
        int retVal = -1;  // Returns -1 if the deque is empty.

        if (isEmpty() == false) {
            retVal = head->val;
        }

        return retVal;
    }
    int getRear() {
        int retVal = -1;  // Returns -1 if the deque is empty.

        if (isEmpty() == false) {
            retVal = rear->val;
        }

        return retVal;
    }
    bool isEmpty() {
        bool retVal = false;

        if (size == 0) {
            retVal = true;
        }

        return retVal;
    }
    bool isFull() {
        bool retVal = false;

        if (size == capacity) {
            retVal = true;
        }

        return retVal;
    }
};
/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */
```

</details>

<details><summary>Python3</summary>

```python
class Node:
    def __init__(self, val, next=None, prev=None):
        self.val = val
        self.next = next
        self.prev = prev


class MyCircularDeque:
    def __init__(self, k: int):
        self.capacity = k
        self.head = None
        self.rear = None
        self.size = 0

    def insertFront(self, value: int) -> bool:
        retVal = False

        if self.isFull() == True:
            return retVal

        if self.head is None:
            self.head = Node(value, None, None)
            self.rear = self.head
        else:
            newHead = Node(value, self.head, None)
            self.head.prev = newHead
            self.head = newHead
        self.size += 1
        retVal = True

        return retVal

    def insertLast(self, value: int) -> bool:
        retVal = False

        if self.isFull() == True:
            return retVal

        if self.head is None:
            self.head = Node(value, None, None)
            self.rear = self.head
        else:
            self.rear.next = Node(value, None, self.rear)
            self.rear = self.rear.next
        self.size += 1
        retVal = True

        return retVal

    def deleteFront(self) -> bool:
        retVal = False

        if self.isEmpty() == True:
            return retVal

        if self.size == 1:
            self.head = None
            self.rear = None
        else:
            self.head = self.head.next
        self.size -= 1
        retVal = True

        return retVal

    def deleteLast(self) -> bool:
        retVal = False

        if self.isEmpty() == True:
            return retVal

        if self.size == 1:
            self.head = None
            self.rear = None
        else:
            self.rear = self.rear.prev
        self.size -= 1
        retVal = True

        return retVal

    def getFront(self) -> int:
        retVal = -1  # Returns -1 if the deque is empty.

        if self.isEmpty() == False:
            retVal = self.head.val

        return retVal

    def getRear(self) -> int:
        retVal = -1  # Returns -1 if the deque is empty.

        if self.isEmpty() == False:
            retVal = self.rear.val

        return retVal

    def isEmpty(self) -> bool:
        retVal = False

        if self.size == 0:
            retVal = True

        return retVal

    def isFull(self) -> bool:
        retVal = False

        if self.size == self.capacity:
            retVal = True

        return retVal

# Your MyCircularDeque object will be instantiated and called as such:
# obj = MyCircularDeque(k)
# param_1 = obj.insertFront(value)
# param_2 = obj.insertLast(value)
# param_3 = obj.deleteFront()
# param_4 = obj.deleteLast()
# param_5 = obj.getFront()
# param_6 = obj.getRear()
# param_7 = obj.isEmpty()
# param_8 = obj.isFull()
```

</details>

## [703. Kth Largest Element in a Stream](https://leetcode.com/problems/kth-largest-element-in-a-stream/)

- [Official](https://leetcode.com/problems/kth-largest-element-in-a-stream/editorial/)
- [Official](https://leetcode.cn/problems/kth-largest-element-in-a-stream/solutions/600598/shu-ju-liu-zhong-de-di-k-da-yuan-su-by-l-woz8/)

<details><summary>Description</summary>

```text
Design a class to find the kth largest element in a stream.
Note that it is the kth largest element in the sorted order, not the kth distinct element.

Implement KthLargest class:
- KthLargest(int k, int[] nums)
    Initializes the object with the integer k and the stream of integers nums.
- int add(int val)
    Appends the integer val to the stream and returns the element representing the kth largest element in the stream.

Example 1:
Input
["KthLargest", "add", "add", "add", "add", "add"]
[[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]
Output
[null, 4, 5, 5, 8, 8]
Explanation
KthLargest kthLargest = new KthLargest(3, [4, 5, 8, 2]);
kthLargest.add(3);   // return 4
kthLargest.add(5);   // return 5
kthLargest.add(10);  // return 5
kthLargest.add(9);   // return 8
kthLargest.add(4);   // return 8

Constraints:
1 <= k <= 10^4
0 <= nums.length <= 10^4
-10^4 <= nums[i] <= 10^4
-10^4 <= val <= 10^4
At most 10^4 calls will be made to add.
It is guaranteed that there will be at least k elements in the array when you search for the kth element.
```

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
typedef struct {
    int* heap;
    int heapSize;
} KthLargest;
KthLargest* kthLargestCreate(int k, int* nums, int numsSize) {
    KthLargest* pRetVal = NULL;

    pRetVal = (KthLargest*)malloc(sizeof(KthLargest));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->heap = (int*)malloc(k * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    pRetVal->heapSize = k;
    memset(pRetVal->heap, 0, (k * sizeof(int)));
    for (int i = 0; i < k; ++i) {
        pRetVal->heap[i] = INT_MIN;
    }

    qsort(nums, numsSize, sizeof(int), compareInteger);
    for (int i = 0; i < numsSize; ++i) {
        if (i >= k) {
            break;
        }
        pRetVal->heap[k - 1 - i] = nums[i];
    }

    return pRetVal;
}
int kthLargestAdd(KthLargest* obj, int val) {
    int retVal = obj->heap[0];

    if (val < obj->heap[0]) {
        return retVal;
    }

    for (int i = obj->heapSize - 1; i >= 0; --i) {
        if (obj->heap[i] > val) {
            continue;
        }
        int tmp = obj->heap[i];
        obj->heap[i] = val;
        val = tmp;
    }
    retVal = obj->heap[0];

    return retVal;
}
void kthLargestFree(KthLargest* obj) {
    free(obj->heap);
    obj->heap = NULL;
    free(obj);
    obj = NULL;
}
/**
 * Your KthLargest struct will be instantiated and called as such:
 * KthLargest* obj = kthLargestCreate(k, nums, numsSize);
 * int param_1 = kthLargestAdd(obj, val);
 * kthLargestFree(obj);
 */
```

</details>

<details><summary>C++</summary>

```c++
class KthLargest {
   public:
    priority_queue<int, vector<int>, greater<int>> priorityQueue;
    int k;

    KthLargest(int k, vector<int>& nums) {
        this->k = k;
        for (auto& num : nums) {
            add(num);
        }
    }
    int add(int val) {
        int retVal = 0;

        priorityQueue.push(val);
        int priorityQueueSize = priorityQueue.size();
        if (priorityQueueSize > k) {
            priorityQueue.pop();
        }
        retVal = priorityQueue.top();

        return retVal;
    }
};
/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
```

</details>

<details><summary>Python3</summary>

```python
class KthLargest:
    def __init__(self, k: int, nums: List[int]):
        self.k = k
        self.nums = nums
        heapq.heapify(self.nums)
        while len(self.nums) > k:
            heapq.heappop(self.nums)

    def add(self, val: int) -> int:
        retVal = 0

        heapq.heappush(self.nums, val)
        if len(self.nums) > self.k:
            heapq.heappop(self.nums)
        retVal = self.nums[0]

        return retVal

# Your SmallestInfiniteSet object will be instantiated and called as such:
# obj = SmallestInfiniteSet()
# param_1 = obj.popSmallest()
# obj.addBack(num)
```

</details>

## [857. Minimum Cost to Hire K Workers](https://leetcode.com/problems/minimum-cost-to-hire-k-workers/)  2259

- [Official](https://leetcode.com/problems/minimum-cost-to-hire-k-workers/editorial/)
- [Official](https://leetcode.cn/problems/minimum-cost-to-hire-k-workers/solutions/1815034/gu-yong-k-ming-gong-ren-de-zui-di-cheng-rsz3t/)

<details><summary>Description</summary>

```text
There are n workers.
You are given two integer arrays quality and wage where quality[i] is the quality of the ith worker
and wage[i] is the minimum wage expectation for the ith worker.

We want to hire exactly k workers to form a paid group.
To hire a group of k workers, we must pay them according to the following rules:
1. Every worker in the paid group must be paid at least their minimum wage expectation.
2. In the group, each worker's pay must be directly proportional to their quality.
   This means if a worker’s quality is double that of another worker in the group,
   then they must be paid twice as much as the other worker.

Given the integer k, return the least amount of money needed to form a paid group satisfying the above conditions.
Answers within 10-5 of the actual answer will be accepted.

Example 1:
Input: quality = [10,20,5], wage = [70,50,30], k = 2
Output: 105.00000
Explanation: We pay 70 to 0th worker and 35 to 2nd worker.

Example 2:
Input: quality = [3,1,10,10,1], wage = [4,8,2,2,7], k = 3
Output: 30.66667
Explanation: We pay 4 to 0th worker, 13.33333 to 2nd and 3rd workers separately.

Constraints:
n == quality.length == wage.length
1 <= k <= n <= 10^4
1 <= quality[i], wage[i] <= 10^4
```

</details>

<details><summary>C</summary>

```c
#include <float.h>

// https://leetcode.cn/problems/minimum-cost-to-hire-k-workers/solutions/1817466/by-heshan-5-ygtm/
#ifndef HEAP_H
#define HEAP_H

typedef struct heap {
    int capacity;
    int size;
    int *elements;
} priorityQueue;
priorityQueue *createQueue(int maxsize) {
    priorityQueue *pRetVal = NULL;

    pRetVal = (priorityQueue *)malloc(sizeof(priorityQueue));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->capacity = maxsize + 1;
    pRetVal->size = 0;
    pRetVal->elements = (int *)malloc(maxsize * sizeof(int));
    if (pRetVal->elements == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset(pRetVal->elements, 0, (maxsize * sizeof(int)));

    return pRetVal;
}
void pushQuee(int val, priorityQueue *obj) {
    int i;
    for (i = obj->size + 1; ((i > 1) && (val > obj->elements[i / 2])); i /= 2) {
        obj->elements[i] = obj->elements[i / 2];
    }
    obj->elements[i] = val;
    obj->size++;
}
int popQuee(priorityQueue *obj) {
    int retVal = obj->elements[1];

    int last = obj->elements[obj->size];

    obj->size--;
    if (obj->size == 0) {
        obj->elements[1] = 0;
        return retVal;
    }

    int maxChild = 0;
    int i;
    for (i = 1; i * 2 <= obj->size; i = maxChild) {
        maxChild = i * 2;
        if ((maxChild != obj->size) && (obj->elements[maxChild] < obj->elements[maxChild + 1])) {
            maxChild++;
        }
        if (last >= obj->elements[maxChild]) {
            break;
        }
        obj->elements[i] = obj->elements[maxChild];
    }
    obj->elements[i] = last;

    return retVal;
}
void freeQueue(priorityQueue *obj) {
    free(obj->elements);
    obj->elements = NULL;
    free(obj);
    obj = NULL;
}

#endif  // HEAP_H
struct node {
    double weight;
    int quality;
};
int compareStruct(const void *a, const void *b) {
    struct node c = *(struct node *)a;
    struct node d = *(struct node *)b;

    double tmp = c.weight - d.weight;
    if (tmp < -1e-7) {
        return -1;
    } else if (tmp > 1e-7) {
        return 1;
    } else {
        return 0;
    }
}
double mincostToHireWorkers(int *quality, int qualitySize, int *wage, int wageSize, int k) {
    double retVal = DBL_MAX;

    int i;

    //
    int minWage = wage[0];
    if (k == 1) {
        for (i = 0; i < wageSize; ++i) {
            if (wage[i] < minWage) {
                minWage = wage[i];
            }
        }
        retVal = 1.0 * minWage;

        return retVal;
    }

    //
    struct node member[qualitySize];
    for (i = 0; i < qualitySize; ++i) {
        member[i].quality = quality[i];
        member[i].weight = 1.0 * wage[i] / quality[i];
    }
    qsort(member, qualitySize, sizeof(member[0]), compareStruct);

    //
    priorityQueue *pObj = createQueue(qualitySize + 1);
    if (pObj == NULL) {
        return retVal;
    }

    int totalQuality = 0;
    for (i = 0; i < k - 1; i++) {
        totalQuality += member[i].quality;
        pushQuee(member[i].quality, pObj);
    }

    double tmp;
    for (i = k - 1; i < qualitySize; ++i) {
        totalQuality += member[i].quality;
        pushQuee(member[i].quality, pObj);
        tmp = member[i].weight * totalQuality;
        totalQuality -= popQuee(pObj);
        if (tmp - retVal < -1e-7) {
            retVal = tmp;
        }
    }

    //
    freeQueue(pObj);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
        double retVal = numeric_limits<double>::max();

        int qualitySize = quality.size();

        vector<pair<double, int>> wageToQualityRatio;
        for (int i = 0; i < qualitySize; i++) {
            wageToQualityRatio.push_back({static_cast<double>(wage[i]) / quality[i], quality[i]});
        }
        sort(wageToQualityRatio.begin(), wageToQualityRatio.end());

        int highestQualityWorkersSize;
        double currentTotalQuality = 0;
        priority_queue<int> highestQualityWorkers;
        for (int i = 0; i < qualitySize; i++) {
            highestQualityWorkers.push(wageToQualityRatio[i].second);
            currentTotalQuality += wageToQualityRatio[i].second;

            highestQualityWorkersSize = highestQualityWorkers.size();
            if (highestQualityWorkersSize > k) {
                currentTotalQuality -= highestQualityWorkers.top();
                highestQualityWorkers.pop();
            }

            highestQualityWorkersSize = highestQualityWorkers.size();
            if (highestQualityWorkersSize == k) {
                retVal = min(retVal, currentTotalQuality * wageToQualityRatio[i].first);
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
    def mincostToHireWorkers(self, quality: List[int], wage: List[int], k: int) -> float:
        retVal = float("inf")

        qualitySize = len(quality)

        wage_to_quality_ratio = []
        for i in range(qualitySize):
            wage_to_quality_ratio.append((wage[i] / quality[i], quality[i]))
        wage_to_quality_ratio.sort(key=lambda x: x[0])

        highest_quality_workers = []
        current_total_quality = 0
        for i in range(qualitySize):
            heappush(highest_quality_workers, -wage_to_quality_ratio[i][1])
            current_total_quality += wage_to_quality_ratio[i][1]

            if len(highest_quality_workers) > k:
                current_total_quality += heappop(highest_quality_workers)

            if len(highest_quality_workers) == k:
                retVal = min(retVal, current_total_quality * wage_to_quality_ratio[i][0])

        return retVal
```

</details>

## [862. Shortest Subarray with Sum at Least K](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/)  2306

- [Official](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/editorial/)
- [Official](https://leetcode.cn/problems/shortest-subarray-with-sum-at-least-k/solutions/1923445/he-zhi-shao-wei-k-de-zui-duan-zi-shu-zu-57ffq/)

<details><summary>Description</summary>

```text
Given an integer array nums and an integer k,
return the length of the shortest non-empty subarray of nums with a sum of at least k.
If there is no such subarray, return -1.

A subarray is a contiguous part of an array.

Example 1:
Input: nums = [1], k = 1
Output: 1

Example 2:
Input: nums = [1,2], k = 4
Output: -1

Example 3:
Input: nums = [2,-1,2], k = 3
Output: 3

Constraints:
1 <= nums.length <= 10^5
-10^5 <= nums[i] <= 10^5
1 <= k <= 10^9
```

</details>

<details><summary>C</summary>

```c
#ifndef DEQUE_H
#define DEQUE_H

typedef struct DLinkListNode {
    int val;
    struct DLinkListNode* prev;
    struct DLinkListNode* next;
} DLinkListNode;
DLinkListNode* dLinkListNodeCreat(int val) {
    DLinkListNode* obj = NULL;

    obj = (DLinkListNode*)malloc(sizeof(DLinkListNode));
    if (obj == NULL) {
        perror("malloc");
        return obj;
    }
    obj->val = val;
    obj->prev = NULL;
    obj->next = NULL;

    return obj;
}
typedef struct {
    int capacity;
    DLinkListNode* head;
    DLinkListNode* tail;
    int size;
} MyCircularDeque;
MyCircularDeque* myCircularDequeCreate(int k) {
    MyCircularDeque* obj = NULL;

    obj = (MyCircularDeque*)malloc(sizeof(MyCircularDeque));
    if (obj == NULL) {
        perror("malloc");
        return obj;
    }
    obj->capacity = k;
    obj->head = NULL;
    obj->tail = NULL;
    obj->size = 0;

    return obj;
}
bool myCircularDequeIsEmpty(MyCircularDeque* obj) {
    bool retVal = false;

    if (obj->size == 0) {
        retVal = true;
    }

    return retVal;
}
bool myCircularDequeIsFull(MyCircularDeque* obj) {
    bool retVal = false;

    if (obj->size == obj->capacity) {
        retVal = true;
    }

    return retVal;
}
bool myCircularDequeInsertFront(MyCircularDeque* obj, int value) {
    bool retVal = false;

    if (myCircularDequeIsFull(obj) == true) {
        return retVal;
    }

    DLinkListNode* pNew = dLinkListNodeCreat(value);
    if (pNew == NULL) {
        return retVal;
    }

    if (obj->size == 0) {
        obj->head = pNew;
        obj->tail = pNew;
    } else {
        pNew->next = obj->head;
        obj->head->prev = pNew;
        obj->head = pNew;
    }
    obj->size++;
    retVal = true;

    return retVal;
}
bool myCircularDequeInsertLast(MyCircularDeque* obj, int value) {
    bool retVal = false;

    if (myCircularDequeIsFull(obj) == true) {
        return retVal;
    }

    DLinkListNode* pNew = dLinkListNodeCreat(value);
    if (pNew == NULL) {
        return retVal;
    }

    if (obj->size == 0) {
        obj->head = pNew;
        obj->tail = pNew;
    } else {
        obj->tail->next = pNew;
        pNew->prev = obj->tail;
        obj->tail = pNew;
    }
    obj->size++;
    retVal = true;

    return retVal;
}
bool myCircularDequeDeleteFront(MyCircularDeque* obj) {
    bool retVal = false;

    if (myCircularDequeIsEmpty(obj) == true) {
        return retVal;
    }

    DLinkListNode* pDelete = obj->head;
    obj->head = obj->head->next;
    if (obj->head != NULL) {
        obj->head->prev = NULL;
    }
    free(pDelete);
    pDelete = NULL;
    obj->size--;
    retVal = true;

    return retVal;
}
bool myCircularDequeDeleteLast(MyCircularDeque* obj) {
    bool retVal = false;

    if (myCircularDequeIsEmpty(obj) == true) {
        return retVal;
    }

    DLinkListNode* pDelete = obj->tail;
    obj->tail = obj->tail->prev;
    if (obj->tail != NULL) {
        obj->tail->next = NULL;
    }
    free(pDelete);
    pDelete = NULL;
    obj->size--;
    retVal = true;

    return retVal;
}
int myCircularDequeGetFront(MyCircularDeque* obj) {
    int retVal = -1;  // Returns -1 if the deque is empty.

    if (myCircularDequeIsEmpty(obj) == false) {
        retVal = obj->head->val;
    }

    return retVal;
}
int myCircularDequeGetRear(MyCircularDeque* obj) {
    int retVal = -1;  // Returns -1 if the deque is empty.

    if (myCircularDequeIsEmpty(obj) == false) {
        retVal = obj->tail->val;
    }

    return retVal;
}
void myCircularDequeFree(MyCircularDeque* obj) {
    DLinkListNode* pDelete = NULL;
    while (obj->head != obj->tail) {
        pDelete = obj->head;
        obj->head = obj->head->next;
        free(pDelete);
        pDelete = NULL;
    }
    free(obj->head);
    obj->head = NULL;

    free(obj);
    obj = NULL;
}

#endif  // DEQUE_H
int shortestSubarray(int* nums, int numsSize, int k) {
    int retVal = -1;

    long long prefixSums[numsSize + 1];
    prefixSums[0] = 0;
    for (int i = 1; i <= numsSize; i++) {
        prefixSums[i] = prefixSums[i - 1] + nums[i - 1];
    }

    MyCircularDeque* candidateIndices = NULL;
    candidateIndices = myCircularDequeCreate(numsSize + 1);

    int shortestSubarrayLength = INT_MAX;
    for (int i = 0; i <= numsSize; i++) {
        // Remove candidates from front of deque where subarray sum meets target
        while ((myCircularDequeIsEmpty(candidateIndices) == false) &&
               (prefixSums[i] - prefixSums[myCircularDequeGetFront(candidateIndices)] >= k)) {
            shortestSubarrayLength = fmin(shortestSubarrayLength, i - myCircularDequeGetFront(candidateIndices));
            myCircularDequeDeleteFront(candidateIndices);
        }

        // Maintain monotonicity by removing indices with larger prefix sums
        while ((myCircularDequeIsEmpty(candidateIndices) == false) &&
               (prefixSums[i] <= prefixSums[myCircularDequeGetRear(candidateIndices)])) {
            myCircularDequeDeleteLast(candidateIndices);
        }

        // Add current index to candidates
        myCircularDequeInsertLast(candidateIndices, i);
    }
    if (shortestSubarrayLength != INT_MAX) {
        retVal = shortestSubarrayLength;
    }

    //
    myCircularDequeFree(candidateIndices);
    candidateIndices = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int shortestSubarray(vector<int>& nums, int k) {
        int retVal = -1;

        int numsSize = nums.size();

        vector<long long> prefixSums(numsSize + 1, 0);
        for (int i = 1; i <= numsSize; i++) {
            prefixSums[i] = prefixSums[i - 1] + nums[i - 1];
        }

        deque<int> candidateIndices;
        int shortestSubarrayLength = numeric_limits<int>::max();
        for (int i = 0; i <= numsSize; i++) {
            // Remove candidates from front of deque where subarray sum meets target
            while ((candidateIndices.empty() == false) && (prefixSums[i] - prefixSums[candidateIndices.front()] >= k)) {
                shortestSubarrayLength = min(shortestSubarrayLength, i - candidateIndices.front());
                candidateIndices.pop_front();
            }

            // Maintain monotonicity by removing indices with larger prefix sums
            while ((candidateIndices.empty() == false) && (prefixSums[i] <= prefixSums[candidateIndices.back()])) {
                candidateIndices.pop_back();
            }

            // Add current index to candidates
            candidateIndices.push_back(i);
        }

        if (shortestSubarrayLength != numeric_limits<int>::max()) {
            retVal = shortestSubarrayLength;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def shortestSubarray(self, nums: List[int], k: int) -> int:
        retVal = -1

        numsSize = len(nums)

        prefixSums = [0] * (numsSize + 1)
        for i in range(1, numsSize + 1):
            prefixSums[i] = prefixSums[i - 1] + nums[i - 1]

        candidateIndices = deque()
        shortestSubarrayLength = float("inf")
        for i in range(numsSize + 1):
            # Remove candidates from front of deque where subarray sum meets target
            while ((candidateIndices) and (prefixSums[i] - prefixSums[candidateIndices[0]] >= k)):
                shortestSubarrayLength = min(shortestSubarrayLength, i - candidateIndices.popleft())

            # Maintain monotonicity by removing indices with larger prefix sums
            while ((candidateIndices) and (prefixSums[i] <= prefixSums[candidateIndices[-1]])):
                candidateIndices.pop()

            # Add current index to candidates
            candidateIndices.append(i)

        if shortestSubarrayLength != float("inf"):
            retVal = shortestSubarrayLength

        return retVal
```

</details>

## [933. Number of Recent Calls](https://leetcode.com/problems/number-of-recent-calls/)  1337

- [Official](https://leetcode.cn/problems/number-of-recent-calls/solutions/1467662/zui-jin-de-qing-qiu-ci-shu-by-leetcode-s-ncm1/)

<details><summary>Description</summary>

```text
You have a RecentCounter class which counts the number of recent requests within a certain time frame.

Implement the RecentCounter class:
- RecentCounter()
  Initializes the counter with zero recent requests.
- int ping(int t)
  Adds a new request at time t, where t represents some time in milliseconds,
  and returns the number of requests that has happened in the past 3000 milliseconds (including the new request).
  Specifically, return the number of requests that have happened in the inclusive range [t - 3000, t].

It is guaranteed that every call to ping uses a strictly larger value of t than the previous call.

Example 1:
Input
["RecentCounter", "ping", "ping", "ping", "ping"]
[[], [1], [100], [3001], [3002]]
Output
[null, 1, 2, 3, 3]
Explanation
RecentCounter recentCounter = new RecentCounter();
recentCounter.ping(1);     // requests = [1], range is [-2999,1], return 1
recentCounter.ping(100);   // requests = [1, 100], range is [-2900,100], return 2
recentCounter.ping(3001);  // requests = [1, 100, 3001], range is [1,3001], return 3
recentCounter.ping(3002);  // requests = [1, 100, 3001, 3002], range is [2,3002], return 3

Constraints:
1 <= t <= 10^9
Each test case will call ping with strictly increasing values of t.
At most 10^4 calls will be made to ping.
```

</details>

<details><summary>C</summary>

```c
typedef struct {
    int* queue;
    int capability;
    int head;
    int tail;
} RecentCounter;
RecentCounter* recentCounterCreate() {
    RecentCounter* pObj = NULL;

    pObj = (RecentCounter*)malloc(sizeof(RecentCounter));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->capability = 10001;  // At most 10^4 calls will be made to ping.
    pObj->queue = (int*)malloc(sizeof(int) * pObj->capability);
    if (pObj->queue == NULL) {
        perror("malloc");
        free(pObj);
        pObj = NULL;
        return pObj;
    }
    pObj->head = 0;
    pObj->tail = 0;

    return pObj;
}
int recentCounterPing(RecentCounter* obj, int t) {
    int retVal = 0;

    obj->queue[obj->tail++] = t;
    while (obj->queue[obj->head] < t - 3000) {
        obj->head++;
    }
    retVal = obj->tail - obj->head;

    return retVal;
}
void recentCounterFree(RecentCounter* obj) {
    free(obj->queue);
    obj->queue = NULL;
    free(obj);
    obj = NULL;
}
/**
 * Your RecentCounter struct will be instantiated and called as such:
 * RecentCounter* obj = recentCounterCreate();
 * int param_1 = recentCounterPing(obj, t);
 * recentCounterFree(obj);
 */
```

</details>

<details><summary>C++</summary>

```c++
class RecentCounter {
    queue<int> requests;

   public:
    RecentCounter() {
        //
    }
    int ping(int t) {
        int retVal = 0;

        requests.emplace(t);
        while (requests.empty() == false) {
            int value = requests.front();
            if (value >= t - 3000) {
                break;
            }
            requests.pop();
        }
        retVal = requests.size();

        return retVal;
    }
};
/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */
```

</details>

<details><summary>Python3</summary>

```python
class RecentCounter:
    def __init__(self):
        self.requests = []
        heapify(self.requests)

    def ping(self, t: int) -> int:
        retVal = 0

        heappush(self.requests, t)
        for _ in range(len(self.requests)):
            if self.requests[0] < (t-3000):
                heappop(self.requests)
        retVal = len(self.requests)

        return retVal

# Your RecentCounter object will be instantiated and called as such:
# obj = RecentCounter()
# param_1 = obj.ping(t)
```

</details>

## [950. Reveal Cards In Increasing Order](https://leetcode.com/problems/reveal-cards-in-increasing-order/)  1686

- [Official](https://leetcode.com/problems/reveal-cards-in-increasing-order/editorial/)
- [Official](https://leetcode.cn/problems/reveal-cards-in-increasing-order/solutions/15988/an-di-zeng-shun-xu-xian-shi-qia-pai-by-leetcode/)

<details><summary>Description</summary>

```text
You are given an integer array deck. There is a deck of cards where every card has a unique integer.
The integer on the ith card is deck[i].

You can order the deck in any order you want. Initially, all the cards start face down (unrevealed) in one deck.

You will do the following steps repeatedly until all cards are revealed:
1. Take the top card of the deck, reveal it, and take it out of the deck.
2. If there are still cards in the deck then put the next top card of the deck at the bottom of the deck.
3. If there are still unrevealed cards, go back to step 1. Otherwise, stop.

Return an ordering of the deck that would reveal the cards in increasing order.

Note that the first entry in the answer is considered to be the top of the deck.

Example 1:
Input: deck = [17,13,11,2,3,5,7]
Output: [2,13,3,11,5,17,7]
Explanation:
We get the deck in the order [17,13,11,2,3,5,7] (this order does not matter), and reorder it.
After reordering, the deck starts as [2,13,3,11,5,17,7], where 2 is the top of the deck.
We reveal 2, and move 13 to the bottom.  The deck is now [3,11,5,17,7,13].
We reveal 3, and move 11 to the bottom.  The deck is now [5,17,7,13,11].
We reveal 5, and move 17 to the bottom.  The deck is now [7,13,11,17].
We reveal 7, and move 13 to the bottom.  The deck is now [11,17,13].
We reveal 11, and move 17 to the bottom.  The deck is now [13,17].
We reveal 13, and move 17 to the bottom.  The deck is now [17].
We reveal 17.
Since all the cards revealed are in increasing order, the answer is correct.

Example 2:
Input: deck = [1,1000]
Output: [1,1000]

Constraints:
1 <= deck.length <= 1000
1 <= deck[i] <= 10^6
All the values of deck are unique.
```

</details>

<details><summary>C</summary>

```c
int compareInteger(const void *n1, const void *n2) {
    // ascending order
    return (*(int *)n1 > *(int *)n2);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *deckRevealedIncreasing(int *deck, int deckSize, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int *)malloc(deckSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (deckSize * sizeof(int)));

    int indexQueueSize = deckSize * 2;
    int indexQueue[indexQueueSize];
    memset(indexQueue, 0, sizeof(indexQueue));
    int indexQueueHead = 0;
    int indexQueueTail = 0;
    for (indexQueueTail = 0; indexQueueTail < deckSize; ++indexQueueTail) {
        indexQueue[indexQueueTail] = indexQueueTail;
    }

    qsort(deck, deckSize, sizeof(int), compareInteger);
    int i;
    for (i = 0; i < deckSize; ++i) {
        pRetVal[indexQueue[indexQueueHead++]] = deck[i];
        (*returnSize)++;
        if (indexQueueHead < indexQueueTail) {
            indexQueue[indexQueueTail++] = indexQueue[indexQueueHead++];
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
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        vector<int> retVal;

        int deckSize = deck.size();
        queue<int> indexQueue;
        for (int i = 0; i < deckSize; ++i) {
            indexQueue.emplace(i);
        }

        sort(deck.begin(), deck.end());
        retVal.resize(deckSize, 0);
        for (int card : deck) {
            retVal[indexQueue.front()] = card;
            indexQueue.pop();
            if (indexQueue.empty() == false) {
                indexQueue.emplace(indexQueue.front());
                indexQueue.pop();
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
    def deckRevealedIncreasing(self, deck: List[int]) -> List[int]:
        retVal = []

        deckSize = len(deck)
        indexQueue = deque(range(deckSize))

        deck.sort()
        retVal = [None] * deckSize
        for card in deck:
            retVal[indexQueue.popleft()] = card
            if indexQueue:
                indexQueue.append(indexQueue.popleft())

        return retVal
```

</details>

## [1046. Last Stone Weight](https://leetcode.com/problems/last-stone-weight/)  1172

- [Official](https://leetcode.cn/problems/last-stone-weight/solutions/540130/zui-hou-yi-kuai-shi-tou-de-zhong-liang-b-xgsx/)

<details><summary>Description</summary>

```text
You are given an array of integers stones where stones[i] is the weight of the ith stone.

We are playing a game with the stones.
On each turn, we choose the heaviest two stones and smash them together.
Suppose the heaviest two stones have weights x and y with x <= y.
The result of this smash is:
- If x == y, both stones are destroyed, and
- If x != y, the stone of weight x is destroyed, and the stone of weight y has new weight y - x.

At the end of the game, there is at most one stone left.

Return the weight of the last remaining stone. If there are no stones left, return 0.

Example 1:
Input: stones = [2,7,4,1,8,1]
Output: 1
Explanation:
We combine 7 and 8 to get 1 so the array converts to [2,4,1,1,1] then,
we combine 2 and 4 to get 2 so the array converts to [2,1,1,1] then,
we combine 2 and 1 to get 1 so the array converts to [1,1,1] then,
we combine 1 and 1 to get 0 so the array converts to [1] then that's the value of the last stone.

Example 2:
Input: stones = [1]
Output: 1

Constraints:
1 <= stones.length <= 30
1 <= stones[i] <= 1000
```

<details><summary>Hint</summary>

```text
1. Simulate the process. We can do it with a heap, or by sorting some list of stones every time we take a turn.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int lastStoneWeight(int* stones, int stonesSize) {
    int retVal = 0;

    while (stonesSize > 1) {
        qsort(stones, stonesSize, sizeof(int), compareInteger);

        stones[stonesSize - 2] = stones[stonesSize - 1] - stones[stonesSize - 2];
        if (stones[stonesSize - 2] == 0) {
            stonesSize -= 2;
        } else {
            stonesSize -= 1;
        }
    }
    retVal = stones[0];

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int lastStoneWeight(vector<int>& stones) {
        int retVal = 0;

        priority_queue<int> priorityQueue;
        for (int stone : stones) {
            priorityQueue.push(stone);
        }

        while (priorityQueue.size() > 1) {
            int first = priorityQueue.top();
            priorityQueue.pop();
            int second = priorityQueue.top();
            priorityQueue.pop();
            if (first > second) {
                priorityQueue.push(first - second);
            }
        }
        if (priorityQueue.empty() == false) {
            retVal = priorityQueue.top();
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def lastStoneWeight(self, stones: List[int]) -> int:
        retVal = 0

        reverseStones = [-stone for stone in stones]
        heapify(reverseStones)
        while len(reverseStones) > 1 and reverseStones[0] != 0:
            heappush(reverseStones, heappop(reverseStones) - heappop(reverseStones))
        retVal = -reverseStones[0]

        return retVal
```

</details>

## [1424. Diagonal Traverse II](https://leetcode.com/problems/diagonal-traverse-ii/)  1779

- [Official](https://leetcode.com/problems/diagonal-traverse-ii/editorial/)

<details><summary>Description</summary>

```text
Given a 2D integer array nums, return all elements of nums in diagonal order as shown in the below images.

Example 1:
Input: nums = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,4,2,7,5,3,8,6,9]

Example 2:
Input: nums = [[1,2,3,4,5],[6,7],[8],[9,10,11],[12,13,14,15,16]]
Output: [1,6,2,8,7,3,9,4,12,10,5,13,11,14,15,16]

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i].length <= 10^5
1 <= sum(nums[i].length) <= 10^5
1 <= nums[i][j] <= 10^5
```

<details><summary>Hint</summary>

```text
1. Notice that numbers with equal sums of row and column indexes belong to the same diagonal.
2. Store them in tuples (sum, row, val), sort them, and then regroup the answer.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findDiagonalOrder(int** nums, int numsSize, int* numsColSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        (*returnSize) += numsColSize[i];
    }

    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));

    struct pairType {
        int row;
        int col;
    } queue[(*returnSize)];
    int queueHead = 0;
    int queueTail = 0;
    queue[queueTail].row = 0;
    queue[queueTail].col = 0;
    queueTail++;

    (*returnSize) = 0;
    int row, col;
    while (queueHead < queueTail) {
        row = queue[queueHead].row;
        col = queue[queueHead].col;
        queueHead++;
        pRetVal[(*returnSize)++] = nums[row][col];

        if ((col == 0) && (row + 1 < numsSize)) {
            queue[queueTail].row = row + 1;
            queue[queueTail].col = col;
            queueTail++;
        }

        if (col + 1 < numsColSize[row]) {
            queue[queueTail].row = row;
            queue[queueTail].col = col + 1;
            queueTail++;
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
    vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
        vector<int> retVal;

        int numsSize = nums.size();

        queue<pair<int, int>> queue;
        queue.push({0, 0});
        while (queue.empty() == false) {
            auto [row, col] = queue.front();
            queue.pop();
            retVal.emplace_back(nums[row][col]);

            if ((col == 0) && (row + 1 < numsSize)) {
                queue.push({row + 1, col});
            }

            int numsColSize = nums[row].size();
            if (col + 1 < numsColSize) {
                queue.push({row, col + 1});
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
    def findDiagonalOrder(self, nums: List[List[int]]) -> List[int]:
        retVal = []

        numsSize = len(nums)

        queue = deque([(0, 0)])
        while queue:
            row, col = queue.popleft()
            retVal.append(nums[row][col])

            if (col == 0) and (row + 1 < numsSize):
                queue.append((row + 1, col))

            numsColSize = len(nums[row])
            if col + 1 < numsColSize:
                queue.append((row, col + 1))

        return retVal
```

</details>

## [1438. Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit](https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/)  1672

- [Official](https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/editorial/)
- [Official](https://leetcode.cn/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/solutions/612688/jue-dui-chai-bu-chao-guo-xian-zhi-de-zui-5bki/)

<details><summary>Description</summary>

```text
Given an array of integers nums and an integer limit, return the size of the longest non-empty subarray
such that the absolute difference between any two elements of this subarray is less than or equal to limit.

Example 1:
Input: nums = [8,2,4,7], limit = 4
Output: 2
Explanation: All subarrays are:
[8] with maximum absolute diff |8-8| = 0 <= 4.
[8,2] with maximum absolute diff |8-2| = 6 > 4.
[8,2,4] with maximum absolute diff |8-2| = 6 > 4.
[8,2,4,7] with maximum absolute diff |8-2| = 6 > 4.
[2] with maximum absolute diff |2-2| = 0 <= 4.
[2,4] with maximum absolute diff |2-4| = 2 <= 4.
[2,4,7] with maximum absolute diff |2-7| = 5 > 4.
[4] with maximum absolute diff |4-4| = 0 <= 4.
[4,7] with maximum absolute diff |4-7| = 3 <= 4.
[7] with maximum absolute diff |7-7| = 0 <= 4.
Therefore, the size of the longest subarray is 2.

Example 2:
Input: nums = [10,1,2,4,7,2], limit = 5
Output: 4
Explanation: The subarray [2,4,7,2] is the longest since the maximum absolute diff is |2-7| = 5 <= 5.

Example 3:
Input: nums = [4,2,2,2,4,4,2,2], limit = 0
Output: 3

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
0 <= limit <= 10^9
```

<details><summary>Hint</summary>

```text
1. Use a sliding window approach keeping the maximum and minimum value
   using a data structure like a multiset from STL in C++.
2. More specifically, use the two pointer technique, moving the right pointer as far as possible to the right
   until the subarray is not valid (maxValue - minValue > limit), then moving the left pointer
   until the subarray is valid again (maxValue - minValue <= limit). Keep repeating this process.
```

</details>

</details>

<details><summary>C</summary>

```c
int longestSubarray(int* nums, int numsSize, int limit) {
    int retVal = 0;

    int maxDequeLeft = 0;
    int maxDequeRight = 0;
    int maxDeque[numsSize];
    memset(maxDeque, 0, sizeof(maxDeque));

    int minDequeLeft = 0;
    int minDequeRight = 0;
    int minDeque[numsSize];
    memset(minDeque, 0, sizeof(minDeque));

    int left = 0;
    int right = 0;
    for (right = 0; right < numsSize; right++) {
        // Maintain the maxDeque in decreasing order
        while ((maxDequeLeft < maxDequeRight) && (maxDeque[maxDequeRight - 1] < nums[right])) {
            maxDequeRight--;
        }
        maxDeque[maxDequeRight++] = nums[right];

        // Maintain the minDeque in increasing order
        while ((minDequeLeft < minDequeRight) && (minDeque[minDequeRight - 1] > nums[right])) {
            minDequeRight--;
        }
        minDeque[minDequeRight++] = nums[right];

        // Check if the current window exceeds the limit
        while ((maxDequeLeft < maxDequeRight) && (minDequeLeft < minDequeRight) &&
               (maxDeque[maxDequeLeft] - minDeque[minDequeLeft] > limit)) {
            // Remove the elements that are out of the current window
            if (maxDeque[maxDequeLeft] == nums[left]) {
                maxDequeLeft++;
            }
            if (minDeque[minDequeLeft] == nums[left]) {
                minDequeLeft++;
            }

            left++;
        }
        retVal = fmax(retVal, right - left + 1);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int longestSubarray(vector<int>& nums, int limit) {
        int retVal = 0;

        deque<int> maxDeque;
        deque<int> minDeque;
        int numsSize = nums.size();
        int left = 0;
        int right = 0;
        for (right = 0; right < numsSize; ++right) {
            // Maintain the maxDeque in decreasing order
            while ((maxDeque.empty() == false) && (maxDeque.back() < nums[right])) {
                maxDeque.pop_back();
            }
            maxDeque.push_back(nums[right]);

            // Maintain the minDeque in increasing order
            while ((minDeque.empty() == false) && (minDeque.back() > nums[right])) {
                minDeque.pop_back();
            }
            minDeque.push_back(nums[right]);

            // Check if the current window exceeds the limit
            while (maxDeque.front() - minDeque.front() > limit) {
                // Remove the elements that are out of the current window
                if (maxDeque.front() == nums[left]) {
                    maxDeque.pop_front();
                }
                if (minDeque.front() == nums[left]) {
                    minDeque.pop_front();
                }

                ++left;
            }

            retVal = max(retVal, right - left + 1);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def longestSubarray(self, nums: List[int], limit: int) -> int:
        retVal = 0

        maxDeque = deque()
        minDeque = deque()
        numsSize = len(nums)
        left = 0
        right = 0
        for right in range(numsSize):
            # Maintain the maxDeque in decreasing order
            while (maxDeque) and (maxDeque[-1] < nums[right]):
                maxDeque.pop()
            maxDeque.append(nums[right])

            # Maintain the minDeque in increasing order
            while (minDeque) and (minDeque[-1] > nums[right]):
                minDeque.pop()
            minDeque.append(nums[right])

            # Check if the current window exceeds the limit
            while maxDeque[0] - minDeque[0] > limit:
                # Remove the elements that are out of the current window
                if maxDeque[0] == nums[left]:
                    maxDeque.popleft()
                if minDeque[0] == nums[left]:
                    minDeque.popleft()

                left += 1

            retVal = max(retVal, right - left + 1)

        return retVal
```

</details>

## [1675. Minimize Deviation in Array](https://leetcode.com/problems/minimize-deviation-in-array/)  2533

<details><summary>Description</summary>

```text
You are given an array nums of n positive integers.

You can perform two types of operations on any element of the array any number of times:
- If the element is even, divide it by 2.
  For example, if the array is [1,2,3,4], then you can do this operation on the last element,
  and the array will be [1,2,3,2].
- If the element is odd, multiply it by 2.
  For example, if the array is [1,2,3,4], then you can do this operation on the first element,
  and the array will be [2,2,3,4].

The deviation of the array is the maximum difference between any two elements in the array.

Return the minimum deviation the array can have after performing some number of operations.

Example 1:
Input: nums = [1,2,3,4]
Output: 1
Explanation: You can transform the array to [1,2,3,2], then to [2,2,3,2], then the deviation will be 3 - 2 = 1.

Example 2:
Input: nums = [4,1,5,20,3]
Output: 3
Explanation: You can transform the array after two operations to [4,2,5,5,3], then the deviation will be 5 - 2 = 3.

Example 3:
Input: nums = [2,10,8]
Output: 3

Constraints:
n == nums.length
2 <= n <= 5 * 10^4
1 <= nums[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Assume you start with the minimum possible value for each number
   so you can only multiply a number by 2 till it reaches its maximum possible value.
2. If there is a better solution than the current one,
   then it must have either its maximum value less than the current maximum value,
   or the minimum value larger than the current minimum value.
3. Since that we only increase numbers (multiply them by 2),
   we cannot decrease the current maximum value, so we must multiply the current minimum number by 2
```

</details>

</details>

<details><summary>C</summary>

```c
int minimumDeviation(int *nums, int numsSize) {

}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minimumDeviation(vector<int>& nums) {
        int retVal = numeric_limits<int>::max();

        /* https://leetcode.com/problems/minimize-deviation-in-array/solutions/955262/c-intuitions-and-flip/
         *
         * Intuition 1
         *  we can divide even numbers multiple times - till we get an odd number,
         *  but we can only double odd numbers once.
         *  After that, it will become an even number.
         * Intuition 2
         *  Even numbers never increase.
         *
         * Flip
         *  we can double all odd numbers first, so we can get forget of the second operation.
         *  Now, we only need to decrease the largest number - while it's even, which results a very simple solution.
         *
         * Solution
         *  Double odd numbers and put all numbers into a max heap.
         *  Track the smallest number.
         *  Track the minimum difference between the top of the heap and the smallest number.
         *  While the top of the heap is even, remove it, divide, and put back to the heap.
         */
        int minNum = numeric_limits<int>::max();
        priority_queue<int> priorityQueue;
        for (auto num : nums) {
            num = (num % 2 == 1) ? num * 2 : num;
            priorityQueue.push(num);
            minNum = min(minNum, num);
        }

        while (priorityQueue.top() % 2 == 0) {
            retVal = min(retVal, priorityQueue.top() - minNum);
            minNum = min(minNum, priorityQueue.top() / 2);
            priorityQueue.push(priorityQueue.top() / 2);
            priorityQueue.pop();
        }
        retVal = min(retVal, priorityQueue.top() - minNum);

        return retVal;
    }
};
```

</details>

## [1792. Maximum Average Pass Ratio](https://leetcode.com/problems/maximum-average-pass-ratio/)  1817

- [Official](https://leetcode.com/problems/maximum-average-pass-ratio/editorial/)
- [Official](https://leetcode.cn/problems/maximum-average-pass-ratio/solutions/2118606/zui-da-ping-jun-tong-guo-lu-by-leetcode-dm7y3/)

<details><summary>Description</summary>

```text
There is a school that has classes of students and each class will be having a final exam.
You are given a 2D integer array classes, where classes[i] = [passi, totali].
You know beforehand that in the ith class, there are totali total students,
but only passi number of students will pass the exam.

You are also given an integer extraStudents.
There are another extraStudents brilliant students
that are guaranteed to pass the exam of any class they are assigned to.
You want to assign each of the extraStudents students to a class in a way
that maximizes the average pass ratio across all the classes.

The pass ratio of a class is equal to the number of students of the class
that will pass the exam divided by the total number of students of the class.
The average pass ratio is the sum of pass ratios of all the classes divided by the number of the classes.

Return the maximum possible average pass ratio after assigning the extraStudents students.
Answers within 10-5 of the actual answer will be accepted.

Example 1:
Input: classes = [[1,2],[3,5],[2,2]], extraStudents = 2
Output: 0.78333
Explanation: You can assign the two extra students to the first class.
The average pass ratio will be equal to (3/4 + 3/5 + 2/2) / 3 = 0.78333.

Example 2:
Input: classes = [[2,4],[3,9],[4,5],[2,10]], extraStudents = 4
Output: 0.53485

Constraints:
1 <= classes.length <= 10^5
classes[i].length == 2
1 <= passi <= totali <= 10^5
1 <= extraStudents <= 10^5
```

<details><summary>Hint</summary>

```text
1. Pay attention to how much the pass ratio changes when you add a student to the class.
   If you keep adding students, what happens to the change in pass ratio?
   The more students you add to a class, the smaller the change in pass ratio becomes.
2. Since the change in the pass ratio is always decreasing with the more students you add,
   then the very first student you add to each class is the one that makes the biggest change in the pass ratio.
3. Because each class's pass ratio is weighted equally, it's always optimal to
   put the student in the class that makes the biggest change among all the other classes.
4. Keep a max heap of the current class sizes and order them by the change in pass ratio.
   For each extra student, take the top of the heap, update the class size, and put it back in the heap.
```

</details>

</details>

<details><summary>C</summary>

```c
// https://leetcode.cn/problems/maximum-average-pass-ratio/solutions/1413598/by-goodgoodday-sl2o/
#ifndef HEAP_H
#define HEAP_H

//
void swapDouble(double* pLeft, double* pRight) {
    double temp = *pLeft;
    *pLeft = *pRight;
    *pRight = temp;
}
void swapInt(int* pLeft, int* pRight) {
    int temp = *pLeft;
    *pLeft = *pRight;
    *pRight = temp;
}
//
typedef struct {
    double* gain;
    int* classes;
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

    pObj->gain = (double*)malloc(sizeof(double) * capacity);
    if (pObj->gain == NULL) {
        perror("malloc");
        free(pObj);
        pObj = NULL;
        return pObj;
    }
    pObj->classes = (int*)malloc(sizeof(int) * capacity);
    if (pObj->classes == NULL) {
        perror("malloc");
        free(pObj->gain);
        pObj->gain = NULL;
        free(pObj);
        pObj = NULL;
        return pObj;
    }
    pObj->size = 1;
    pObj->capacity = capacity;

    return pObj;
}
void HeapAdjustDown(MaxHeap* pObj, int parent) {
    int child = 2 * parent;
    int size = pObj->size;
    while (child < size) {
        if ((child + 1 < size) && (pObj->gain[child] < pObj->gain[child + 1])) {
            child = child + 1;
        }

        if (pObj->gain[child] > pObj->gain[parent]) {
            swapDouble(&pObj->gain[child], &pObj->gain[parent]);
            swapInt(&pObj->classes[child], &pObj->classes[parent]);
            parent = child;
            child = parent << 1;
        } else {
            break;
        }
    }
}
void HeapAdjustUp(MaxHeap* pObj, int child) {
    int parent = child / 2;
    while (child > 1) {
        if (pObj->gain[child] > pObj->gain[parent]) {
            swapDouble(&pObj->gain[child], &pObj->gain[parent]);
            swapInt(&pObj->classes[child], &pObj->classes[parent]);
            child = parent;
            parent = child / 2;
        } else {
            break;
        }
    }
}
void pushMaxHeap(MaxHeap* pObj, double gain, int classes) {
    if (pObj->size == pObj->capacity) {
        printf("MaxHeap is full. Cannot insert more elements.\n");
        return;
    }

    int index = pObj->size++;
    pObj->gain[index] = gain;
    pObj->classes[index] = classes;

    HeapAdjustUp(pObj, pObj->size - 1);
}
void popMaxHeap(MaxHeap* pObj) {
    if (pObj->size == 1) {
        printf("MaxHeap is empty. Cannot remove elements.\n");
        return;
    }

    pObj->gain[1] = pObj->gain[pObj->size - 1];
    pObj->classes[1] = pObj->classes[pObj->size - 1];
    pObj->size--;

    HeapAdjustDown(pObj, 1);
}
void printMaxHeap(MaxHeap* pObj) {
    printf("Max Heap: ");
    for (int i = 1; i < pObj->size; i++) {
        printf("(%f,%d) ", pObj->gain[i], pObj->classes[i]);
    }
    printf("\n");
}
void freeMaxHeap(MaxHeap* pObj) {
    free(pObj->gain);
    pObj->gain = NULL;
    free(pObj->classes);
    pObj->classes = NULL;
    free(pObj);
    pObj = NULL;
}

#endif  // HEAP_H
double calculateGain(int passes, int totalStudents) {
    double retVal = 0;

    retVal = (double)(passes + 1) / (totalStudents + 1) - (double)passes / totalStudents;

    return retVal;
};
double maxAverageRatio(int** classes, int classesSize, int* classesColSize, int extraStudents) {
    double retVal = 0;

    // Max heap to store (-gain, passes, totalStudents)
    MaxHeap* pMaxHeap = createMaxHeap(classesSize + 1);
    if (pMaxHeap == NULL) {
        return retVal;
    }
    double gain = 0;
    for (int i = 0; i < classesSize; i++) {
        gain = calculateGain(classes[i][0], classes[i][1]);
        pushMaxHeap(pMaxHeap, gain, i);
    }
    // printMaxHeap(pMaxHeap);

    // Distribute extra students
    int topIndex;
    while (extraStudents--) {
        topIndex = pMaxHeap->classes[1];
        popMaxHeap(pMaxHeap);

        classes[topIndex][0]++;
        classes[topIndex][1]++;
        gain = calculateGain(classes[topIndex][0], classes[topIndex][1]);
        pushMaxHeap(pMaxHeap, gain, topIndex);
    }
    // printMaxHeap(pMaxHeap);

    // Calculate the final average pass ratio
    double totalPassRatio = 0;
    for (int i = 0; i < classesSize; i++) {
        totalPassRatio += ((double)classes[i][0] / classes[i][1]);
    }
    retVal = totalPassRatio / classesSize;

    //
    freeMaxHeap(pMaxHeap);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    double calculateGain(int passes, int totalStudents) {
        double retVal = 0;

        retVal = (double)(passes + 1) / (totalStudents + 1) - (double)passes / totalStudents;

        return retVal;
    };

   public:
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        double retVal = 0;

        // Max heap to store (-gain, passes, totalStudents)
        priority_queue<pair<double, pair<int, int>>> maxHeap;
        for (const auto& singleClass : classes) {
            maxHeap.push({calculateGain(singleClass[0], singleClass[1]), {singleClass[0], singleClass[1]}});
        }

        // Distribute extra students
        while (extraStudents--) {
            auto [currentGain, classInfo] = maxHeap.top();
            maxHeap.pop();
            int passes = classInfo.first;
            int totalStudents = classInfo.second;
            maxHeap.push({calculateGain(passes + 1, totalStudents + 1), {passes + 1, totalStudents + 1}});
        }

        // Calculate the final average pass ratio
        double totalPassRatio = 0;
        while (maxHeap.empty() == false) {
            auto [_, classInfo] = maxHeap.top();
            maxHeap.pop();
            totalPassRatio += (double)classInfo.first / classInfo.second;
        }
        int classesSize = classes.size();
        retVal = totalPassRatio / classesSize;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def calculateGain(self, passes, totalStudents) -> float:
        retVal = 0

        retVal = (passes + 1) / (totalStudents + 1) - passes / totalStudents

        return retVal

    def maxAverageRatio(self, classes: List[List[int]], extraStudents: int) -> float:
        retVal = 0

        # Max heap to store (-gain, passes, totalStudents)
        maxHeap = []
        for passes, totalStudents in classes:
            gain = self.calculateGain(passes, totalStudents)
            heappush(maxHeap, (-gain, passes, totalStudents))

        # Distribute extra students
        for _ in range(extraStudents):
            _, passes, totalStudents = heappop(maxHeap)
            gain = self.calculateGain(passes + 1, totalStudents + 1)
            heappush(maxHeap, (-gain, passes + 1, totalStudents + 1,))

        # Calculate the final average pass ratio
        totalPassRatio = 0
        while maxHeap:
            _, passes, totalStudents = heappop(maxHeap)
            totalPassRatio += (passes / totalStudents)
        retVal = totalPassRatio / len(classes)

        return retVal
```

</details>

## [1834. Single-Threaded CPU](https://leetcode.com/problems/single-threaded-cpu/)  1797

- [Official](https://leetcode.com/problems/single-threaded-cpu/solutions/2216661/single-threaded-cpu/)
- [Official](https://leetcode.cn/problems/single-threaded-cpu/solutions/728945/single-threaded-cpu-by-leetcode-solution-suki/)

<details><summary>Description</summary>

```text
You are given n​​​​​​ tasks labeled from 0 to n - 1 represented by a 2D integer array tasks,
where tasks[i] = [enqueueTimei, processingTimei] means
that the i​​​​​​th​​​​ task will be available to process at enqueueTimei and will take processingTimei to finish processing.

You have a single-threaded CPU that can process at most one task at a time and will act in the following way:
- If the CPU is idle and there are no available tasks to process, the CPU remains idle.
- If the CPU is idle and there are available tasks, the CPU will choose the one with the shortest processing time.
  If multiple tasks have the same shortest processing time, it will choose the task with the smallest index.
- Once a task is started, the CPU will process the entire task without stopping.
- The CPU can finish a task then start a new one instantly.

Return the order in which the CPU will process the tasks.

Example 1:
Input: tasks = [[1,2],[2,4],[3,2],[4,1]]
Output: [0,2,3,1]
Explanation: The events go as follows:
- At time = 1, task 0 is available to process. Available tasks = {0}.
- Also at time = 1, the idle CPU starts processing task 0. Available tasks = {}.
- At time = 2, task 1 is available to process. Available tasks = {1}.
- At time = 3, task 2 is available to process. Available tasks = {1, 2}.
- Also at time = 3, the CPU finishes task 0 and starts processing task 2 as it is the shortest. Available tasks = {1}.
- At time = 4, task 3 is available to process. Available tasks = {1, 3}.
- At time = 5, the CPU finishes task 2 and starts processing task 3 as it is the shortest. Available tasks = {1}.
- At time = 6, the CPU finishes task 3 and starts processing task 1. Available tasks = {}.
- At time = 10, the CPU finishes task 1 and becomes idle.

Example 2:
Input: tasks = [[7,10],[7,12],[7,5],[7,4],[7,2]]
Output: [4,3,2,0,1]
Explanation: The events go as follows:
- At time = 7, all the tasks become available. Available tasks = {0,1,2,3,4}.
- Also at time = 7, the idle CPU starts processing task 4. Available tasks = {0,1,2,3}.
- At time = 9, the CPU finishes task 4 and starts processing task 3. Available tasks = {0,1,2}.
- At time = 13, the CPU finishes task 3 and starts processing task 2. Available tasks = {0,1}.
- At time = 18, the CPU finishes task 2 and starts processing task 0. Available tasks = {1}.
- At time = 28, the CPU finishes task 0 and starts processing task 1. Available tasks = {}.
- At time = 40, the CPU finishes task 1 and becomes idle.

Constraints:
tasks.length == n
1 <= n <= 10^5
1 <= enqueueTimei, processingTimei <= 10^9
```

</details>

<details><summary>C</summary>

```c
typedef struct {
    int start;
    int time;
    int idx;
} Task;
typedef struct {
    Task *task;
    int idx;
} Heap;
int cmpTask1(const void *a, const void *b) {
    Task *pA = (Task *)a;
    Task *pB = (Task *)b;

    if (pA->start == pB->start) {
        return (pA->time > pB->time);
    }

    return (pA->start > pB->start);
}
int cmpTask2(Task *a, Task *b) {
    if (a->time == b->time) {
        return (a->idx > b->idx);
    }

    return (a->time > b->time);
}
void swap(Task *a, Task *b) {
    Task tmp = *a;
    *a = *b;
    *b = tmp;
}
void push(Heap *heap, Task *t) {
    heap->task[heap->idx++] = *t;

    int p;
    int x = heap->idx - 1;
    while (x > 0) {
        p = (x - 1) / 2;
        if (cmpTask2(&heap->task[p], &heap->task[x])) {
            swap(&heap->task[p], &heap->task[x]);
            x = p;
        } else {
            break;
        }
    }
}
Task pop(Heap *heap) {
    Task res = heap->task[0];
    heap->task[0] = heap->task[--heap->idx];

    int min, l, r;
    int i = 0;
    int n = heap->idx;
    while (i < n) {
        min = i;

        l = 2 * min + 1;
        r = 2 * min + 2;
        if (l < n && cmpTask2(&heap->task[min], &heap->task[l])) {
            min = l;
        }

        if (r < n && cmpTask2(&heap->task[min], &heap->task[r])) {
            min = r;
        }

        if (min != i) {
            swap(&heap->task[min], &heap->task[i]);
            i = min;
        } else {
            break;
        }
    }

    return res;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *getOrder(int **tasks, int tasksSize, int *tasksColSize, int *returnSize) {
    int *pRetVal = NULL;

    // malloc returned array
    (*returnSize) = tasksSize;
    pRetVal = (int *)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));

    // malloc Heap
    Heap *pHeap = (Heap *)malloc(sizeof(Heap));
    if (pHeap == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    pHeap->task = (Task *)malloc((*returnSize) * sizeof(Task));
    if (pHeap->task == NULL) {
        perror("malloc");
        free(pHeap);
        pHeap = NULL;
        (*returnSize) = 0;
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    pHeap->idx = 0;

    // malloc Task
    Task *pTask = (Task *)malloc((*returnSize) * sizeof(Task));
    if (pTask == NULL) {
        perror("malloc");
        free(pHeap->task);
        pHeap->task = NULL;
        free(pHeap);
        pHeap = NULL;
        (*returnSize) = 0;
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }

    int i, j;

    for (i = 0; i < (*returnSize); i++) {
        Task pTmp = {tasks[i][0], tasks[i][1], i};
        pTask[i] = pTmp;
    }
    qsort(pTask, (*returnSize), sizeof(pTask[0]), cmpTask1);

    long cur = 0;
    j = 0;
    for (i = 0; i < (*returnSize); i++) {
        if (pHeap->idx == 0) {
            cur = fmax(cur, pTask[i].start);
        }

        while (j < (*returnSize) && pTask[j].start <= cur) {
            push(pHeap, &pTask[j]);
            j++;
        }

        Task pTmp = pop(pHeap);
        pRetVal[i] = pTmp.idx;
        cur += pTmp.time;
    }

    free(pHeap->task);
    pHeap->task = NULL;
    free(pHeap);
    pHeap = NULL;
    free(pTask);
    pTask = NULL;

    return pRetVal;
}
```

</details>

## [1845. Seat Reservation Manager](https://leetcode.com/problems/seat-reservation-manager/)  1428

- [Official](https://leetcode.com/problems/seat-reservation-manager/editorial/)
- [Official](https://leetcode.cn/problems/seat-reservation-manager/solutions/754909/zuo-wei-yu-yue-guan-li-xi-tong-by-leetco-wj45/)

<details><summary>Description</summary>

```text
Design a system that manages the reservation state of n seats that are numbered from 1 to n.

Implement the SeatManager class:
- SeatManager(int n)
  Initializes a SeatManager object that will manage n seats numbered from 1 to n. All seats are initially available.
- int reserve()
  Fetches the smallest-numbered unreserved seat, reserves it, and returns its number.
- void unreserve(int seatNumber)
  Unreserves the seat with the given seatNumber.

Example 1:
Input
["SeatManager", "reserve", "reserve", "unreserve", "reserve", "reserve", "reserve", "reserve", "unreserve"]
[[5], [], [], [2], [], [], [], [], [5]]
Output
[null, 1, 2, null, 2, 3, 4, 5, null]

Explanation
SeatManager seatManager = new SeatManager(5); // Initializes a SeatManager with 5 seats.
seatManager.reserve();    // All seats are available, so return the lowest numbered seat, which is 1.
seatManager.reserve();    // The available seats are [2,3,4,5], so return the lowest of them, which is 2.
seatManager.unreserve(2); // Unreserve seat 2, so now the available seats are [2,3,4,5].
seatManager.reserve();    // The available seats are [2,3,4,5], so return the lowest of them, which is 2.
seatManager.reserve();    // The available seats are [3,4,5], so return the lowest of them, which is 3.
seatManager.reserve();    // The available seats are [4,5], so return the lowest of them, which is 4.
seatManager.reserve();    // The only available seat is seat 5, so return 5.
seatManager.unreserve(5); // Unreserve seat 5, so now the available seats are [5].

Constraints:
1 <= n <= 10^5
1 <= seatNumber <= n
For each call to reserve, it is guaranteed that there will be at least one unreserved seat.
For each call to unreserve, it is guaranteed that seatNumber will be reserved.
At most 105 calls in total will be made to reserve and unreserve.
```

<details><summary>Hint</summary>

```text
1. You need a data structure that maintains the states of the seats.
   This data structure should also allow you to get the first available seat
   and flip the state of a seat in a reasonable time.
2. You can let the data structure contain the available seats.
   Then you want to be able to get the lowest element and erase an element, in a reasonable time.
3. Ordered sets support these operations.
```

</details>

</details>

<details><summary>C</summary>

```c
// https://leetcode.cn/problems/seat-reservation-manager/solutions/1778519/by-letcode_q-ad4q/
typedef struct {
    int* heap;
    int heapSize;
} SeatManager;
SeatManager* seatManagerCreate(int n) {
    SeatManager* pRetVal = NULL;

    pRetVal = (SeatManager*)malloc(sizeof(SeatManager));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int* heap = (int*)malloc(sizeof(int) * n);
    if (pRetVal == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    int i;
    for (i = 0; i < n; i++) {
        heap[i] = i + 1;
    }
    pRetVal->heap = heap;
    pRetVal->heapSize = n;

    return pRetVal;
}
int seatManagerReserve(SeatManager* seatManager) {
    int retVal = 0;

    int* heap = seatManager->heap;
    retVal = heap[0];
    heap[0] = heap[seatManager->heapSize - 1];
    seatManager->heapSize--;

    int tmp;
    int dad = 0;
    int son = 2 * dad + 1;
    while (son < seatManager->heapSize) {
        if (son + 1 < seatManager->heapSize && heap[son + 1] < heap[son]) {
            son++;
        }

        if (heap[dad] < heap[son]) {
            break;
        }

        if (heap[dad] > heap[son]) {
            tmp = heap[dad];
            heap[dad] = heap[son];
            heap[son] = tmp;
        }
        dad = son;
        son = 2 * dad + 1;
    }

    return retVal;
}
void seatManagerUnreserve(SeatManager* seatManager, int seatNumber) {
    int* heap = seatManager->heap;
    heap[seatManager->heapSize++] = seatNumber;

    int tmp;
    int son = seatManager->heapSize - 1;
    int dad = (son + 1) / 2 - 1;
    while (dad >= 0) {
        if (son + 1 < seatManager->heapSize && heap[son + 1] < heap[son]) {
            son++;
        }

        if (heap[dad] < heap[son]) {
            break;
        }

        if (heap[dad] > heap[son]) {
            tmp = heap[dad];
            heap[dad] = heap[son];
            heap[son] = tmp;
        }
        son = dad;
        dad = (son + 1) / 2 - 1;
    }
}
void seatManagerFree(SeatManager* obj) {
    free(obj->heap);
    obj->heap = NULL;
    free(obj);
    obj = NULL;
}
/**
 * Your SeatManager struct will be instantiated and called as such:
 * SeatManager* obj = seatManagerCreate(n);
 * int param_1 = seatManagerReserve(obj);
 * seatManagerUnreserve(obj, seatNumber);
 * seatManagerFree(obj);
 */
```

</details>

<details><summary>C++</summary>

```c++
class SeatManager {
   private:
    priority_queue<int, vector<int>, greater<int>> seats;

   public:
    SeatManager(int n) {
        for (int seatNumber = 1; seatNumber <= n; ++seatNumber) {
            seats.push(seatNumber);
        }
    }
    int reserve() {
        int retVal = 0;

        retVal = seats.top();
        seats.pop();

        return retVal;
    }
    void unreserve(int seatNumber) {
        //
        seats.push(seatNumber);
    }
};
/**
 * Your SeatManager object will be instantiated and called as such:
 * SeatManager* obj = new SeatManager(n);
 * int param_1 = obj->reserve();
 * obj->unreserve(seatNumber);
 */
```

</details>

<details><summary>Python3</summary>

```python
class SeatManager:
    def __init__(self, n: int):
        self.seats = [i for i in range(1, n + 1)]

    def reserve(self) -> int:
        retVal = heappop(self.seats)

        return retVal

    def unreserve(self, seatNumber: int) -> None:
        heappush(self.seats, seatNumber)


# Your SeatManager object will be instantiated and called as such:
# obj = SeatManager(n)
# param_1 = obj.reserve()
# obj.unreserve(seatNumber)
```

</details>

## [1942. The Number of the Smallest Unoccupied Chair](https://leetcode.com/problems/the-number-of-the-smallest-unoccupied-chair/)  1695

- [Official](https://leetcode.com/problems/the-number-of-the-smallest-unoccupied-chair/editorial/)
- [Official](https://leetcode.cn/problems/the-number-of-the-smallest-unoccupied-chair/solutions/895434/zui-xiao-wei-bei-zhan-ju-yi-zi-de-bian-h-kz2d/)

<details><summary>Description</summary>

```text
There is a party where n friends numbered from 0 to n - 1 are attending.
There is an infinite number of chairs in this party that are numbered from 0 to infinity.
When a friend arrives at the party, they sit on the unoccupied chair with the smallest number.
- For example, if chairs 0, 1, and 5 are occupied when a friend comes, they will sit on chair number 2.

When a friend leaves the party, their chair becomes unoccupied at the moment they leave.
If another friend arrives at that same moment, they can sit in that chair.

You are given a 0-indexed 2D integer array times where times[i] = [arrivali, leavingi],
indicating the arrival and leaving times of the ith friend respectively, and an integer targetFriend.
All arrival times are distinct.

Return the chair number that the friend numbered targetFriend will sit on.

Example 1:
Input: times = [[1,4],[2,3],[4,6]], targetFriend = 1
Output: 1
Explanation:
- Friend 0 arrives at time 1 and sits on chair 0.
- Friend 1 arrives at time 2 and sits on chair 1.
- Friend 1 leaves at time 3 and chair 1 becomes empty.
- Friend 0 leaves at time 4 and chair 0 becomes empty.
- Friend 2 arrives at time 4 and sits on chair 0.
Since friend 1 sat on chair 1, we return 1.

Example 2:
Input: times = [[3,10],[1,5],[2,6]], targetFriend = 0
Output: 2
Explanation:
- Friend 1 arrives at time 1 and sits on chair 0.
- Friend 2 arrives at time 2 and sits on chair 1.
- Friend 0 arrives at time 3 and sits on chair 2.
- Friend 1 leaves at time 5 and chair 0 becomes empty.
- Friend 2 leaves at time 6 and chair 1 becomes empty.
- Friend 0 leaves at time 10 and chair 2 becomes empty.
Since friend 0 sat on chair 2, we return 2.

Constraints:
n == times.length
2 <= n <= 10^4
times[i].length == 2
1 <= arrivali < leavingi <= 10^5
0 <= targetFriend <= n - 1
Each arrivali time is distinct.
```

<details><summary>Hint</summary>

```text
1. Sort times by arrival time.
2. for each arrival_i find the smallest unoccupied chair and mark it as occupied until leaving_i.
```

</details>

</details>

<details><summary>C</summary>

```c
// https://leetcode.cn/problems/the-number-of-the-smallest-unoccupied-chair/solutions/1102966/zui-xiao-wei-bei-zhan-ju-yi-zi-de-bian-h-tjlc/
int compareIntArray(const void *a1, const void *a2) {
    int *p1 = *(int **)a1;
    int *p2 = *(int **)a2;

    // ascending order
    if (p1[0] == p2[0]) {
        return (p1[1] > p2[1]);
    }

    return (p1[0] > p2[0]);
}
int smallestChair(int **times, int timesSize, int *timesColSize, int targetFriend) {
    int retVal = 0;

    int arriveTime = times[targetFriend][0];

    qsort(times, timesSize, sizeof(int *), compareIntArray);

    int seat[arriveTime];
    memset(seat, 0, sizeof(seat));
    int i = 0;
    int j = 0;
    while ((timesSize > i) && (times[i][0] <= arriveTime)) {
        j = 0;
        while ((arriveTime > j) && (seat[j] > times[i][0])) {
            j++;
        }

        if (arriveTime > j) {
            seat[j] = times[i][1];
        }

        i++;
    }
    retVal = j;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int smallestChair(vector<vector<int>>& times, int targetFriend) {
        int retVal = 0;

        int targetArrival = times[targetFriend][0];

        sort(times.begin(), times.end());

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> leavingQueue;
        set<int> availableChairs;
        int nextChair = 0;
        for (auto time : times) {
            int arrival = time[0];
            int leave = time[1];

            while ((leavingQueue.empty() == false) && (leavingQueue.top().first <= arrival)) {
                availableChairs.insert(leavingQueue.top().second);
                leavingQueue.pop();
            }

            int currentChair;
            if (availableChairs.empty() == false) {
                currentChair = *availableChairs.begin();
                availableChairs.erase(availableChairs.begin());
            } else {
                currentChair = nextChair++;
            }

            leavingQueue.push({leave, currentChair});

            if (arrival == targetArrival) {
                retVal = currentChair;
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
    def smallestChair(self, times: List[List[int]], targetFriend: int) -> int:
        retVal = 0

        times = sorted([(arrival, leave, index) for index, (arrival, leave) in enumerate(times)])

        nextChair = 0
        availableChairs = []
        leavingQueue = []
        for time in times:
            arrival, leave, index = time

            while leavingQueue and leavingQueue[0][0] <= arrival:
                _, chair = heappop(leavingQueue)
                heappush(availableChairs, chair)

            if availableChairs:
                currentChair = heappop(availableChairs)
            else:
                currentChair = nextChair
                nextChair += 1

            heappush(leavingQueue, (leave, currentChair))

            if index == targetFriend:
                retVal = currentChair
                break

        return retVal
```

</details>

## [1962. Remove Stones to Minimize the Total](https://leetcode.com/problems/remove-stones-to-minimize-the-total/)  1418

- [Official](https://leetcode.com/problems/remove-stones-to-minimize-the-total/solutions/2636179/remove-stones-to-minimize-the-total/)
- [Official](https://leetcode.cn/problems/remove-stones-to-minimize-the-total/solutions/922700/yi-chu-shi-zi-shi-zong-shu-zui-xiao-by-l-9lsg/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array piles, where piles[i] represents the number of stones in the ith pile, and an integer k.
You should apply the following operation exactly k times:

Choose any piles[i] and remove floor(piles[i] / 2) stones from it.
Notice that you can apply the operation on the same pile more than once.

Return the minimum possible total number of stones remaining after applying the k operations.

floor(x) is the greatest integer that is smaller than or equal to x (i.e., rounds x down).

Example 1:
Input: piles = [5,4,9], k = 2
Output: 12
Explanation: Steps of a possible scenario are:
- Apply the operation on pile 2. The resulting piles are [5,4,5].
- Apply the operation on pile 0. The resulting piles are [3,4,5].
The total number of stones in [3,4,5] is 12.

Example 2:
Input: piles = [4,3,6,7], k = 3
Output: 12
Explanation: Steps of a possible scenario are:
- Apply the operation on pile 2. The resulting piles are [4,3,3,7].
- Apply the operation on pile 3. The resulting piles are [4,3,3,4].
- Apply the operation on pile 0. The resulting piles are [2,3,3,4].
The total number of stones in [2,3,3,4] is 12.

Constraints:
1 <= piles.length <= 10^5
1 <= piles[i] <= 10^4
1 <= k <= 10^5
```

</details>

<details><summary>C</summary>

```c
#define SPACE (1)
#if (SPACE)
#else
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
#endif
int minStoneSum(int* piles, int pilesSize, int k) {
    int retVal = 0;

#if (SPACE)
    printf("if\n");

#define MAX_OPERATION (10000)
    int Count[MAX_OPERATION + 1];
    memset(Count, 0, sizeof(Count));
    int idx = MAX_OPERATION;

    int i;
    for (i = 0; i < pilesSize; ++i) {
        Count[piles[i]] += piles[i];
    }

    int tmp;
    while (k > 0) {
        if (Count[idx] == 0) {
            --idx;
            continue;
        }
        Count[idx] -= idx;
        tmp = idx - idx / 2;
        Count[tmp] += tmp;

        k--;
    }

    for (i = 0; i <= MAX_OPERATION; ++i) {
        retVal += Count[i];
    }
#else
    printf("else\n");

    int i;
    for (i = 0; i < pilesSize; ++i) {
        retVal += piles[i];
    }
    qsort(piles, pilesSize, sizeof(int), compareInteger);

    i = 0;
    int remove;
    while (k > 0) {
        remove = piles[i] / 2;
        piles[i] -= remove;
        retVal -= remove;

        if ((i < (pilesSize - 1)) && (piles[i] < piles[i + 1]) && (piles[0] <= piles[i + 1])) {
            ++i;
        } else if ((i == (pilesSize - 1)) || (piles[0] > piles[i + 1])) {
            qsort(piles, pilesSize, sizeof(int), compareInteger);
            i = 0;
        }

        --k;
    }
#endif

    return retVal;
}
```

</details>

## [2073. Time Needed to Buy Tickets](https://leetcode.com/problems/time-needed-to-buy-tickets/)  1325

- [Official](https://leetcode.com/problems/time-needed-to-buy-tickets/editorial/)
- [Official](https://leetcode.cn/problems/time-needed-to-buy-tickets/solutions/1102684/mai-piao-xu-yao-de-shi-jian-by-leetcode-jnfxx/)

<details><summary>Description</summary>

```text
There are n people in a line queuing to buy tickets,
where the 0th person is at the front of the line and the (n - 1)th person is at the back of the line.

You are given a 0-indexed integer array tickets of length n
where the number of tickets that the ith person would like to buy is tickets[i].

Each person takes exactly 1 second to buy a ticket.
A person can only buy 1 ticket at a time and has to go back to the end of the line (which happens instantaneously)
in order to buy more tickets.
If a person does not have any tickets left to buy, the person will leave the line.

Return the time taken for the person at position k (0-indexed) to finish buying tickets.

Example 1:
Input: tickets = [2,3,2], k = 2
Output: 6
Explanation:
- In the first pass, everyone in the line buys a ticket and the line becomes [1, 2, 1].
- In the second pass, everyone in the line buys a ticket and the line becomes [0, 1, 0].
The person at position 2 has successfully bought 2 tickets and it took 3 + 3 = 6 seconds.

Example 2:
Input: tickets = [5,1,1,1], k = 0
Output: 8
Explanation:
- In the first pass, everyone in the line buys a ticket and the line becomes [4, 0, 0, 0].
- In the next 4 passes, only the person in position 0 is buying tickets.
The person at position 0 has successfully bought 5 tickets and it took 4 + 1 + 1 + 1 + 1 = 8 seconds.

Constraints:
n == tickets.length
1 <= n <= 100
1 <= tickets[i] <= 100
0 <= k < n
```

<details><summary>Hint</summary>

```text
1. Loop through the line of people and decrement the number of tickets for each
   to buy one at a time as if simulating the line moving forward.
   Keep track of how many tickets have been sold up until person k has no more tickets to buy.
2. Remember that those who have no more tickets to buy will leave the line.
```

</details>

</details>

<details><summary>C</summary>

```c
int timeRequiredToBuy(int* tickets, int ticketsSize, int k) {
    int retVal = 0;

    int i;
    for (i = 0; i < ticketsSize; ++i) {
        if (i <= k) {
            retVal += fmin(tickets[i], tickets[k]);
        } else {
            retVal += fmin(tickets[i], (tickets[k] - 1));
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
    int timeRequiredToBuy(vector<int>& tickets, int k) {
        int retVal = 0;

        int ticketsSize = tickets.size();
        for (int i = 0; i < ticketsSize; ++i) {
            if (i <= k) {
                retVal += min(tickets[i], tickets[k]);
            } else {
                retVal += min(tickets[i], (tickets[k] - 1));
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
    def timeRequiredToBuy(self, tickets: List[int], k: int) -> int:
        retVal = 0

        ticketsSize = len(tickets)
        for i in range(ticketsSize):
            if i <= k:
                retVal += min(tickets[i], tickets[k])
            else:
                retVal += min(tickets[i], (tickets[k]-1))

        return retVal
```

</details>

## [2163. Minimum Difference in Sums After Removal of Elements](https://leetcode.com/problems/minimum-difference-in-sums-after-removal-of-elements/)  2225

- [Official](https://leetcode.com/problems/minimum-difference-in-sums-after-removal-of-elements/editorial/)
- [Official](https://leetcode.cn/problems/minimum-difference-in-sums-after-removal-of-elements/solutions/1249409/shan-chu-yuan-su-hou-he-de-zui-xiao-chai-ah0j/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array nums consisting of 3 * n elements.

You are allowed to remove any subsequence of elements of size exactly n from nums.
The remaining 2 * n elements will be divided into two equal parts:
- The first n elements belonging to the first part and their sum is sumfirst.
- The next n elements belonging to the second part and their sum is sumsecond.

The difference in sums of the two parts is denoted as sumfirst - sumsecond.
- For example, if sumfirst = 3 and sumsecond = 2, their difference is 1.
- Similarly, if sumfirst = 2 and sumsecond = 3, their difference is -1.

Return the minimum difference possible between the sums of the two parts after the removal of n elements.

Example 1:
Input: nums = [3,1,2]
Output: -1
Explanation:
Here, nums has 3 elements, so n = 1.
Thus we have to remove 1 element from nums and divide the array into two equal parts.
- If we remove nums[0] = 3, the array will be [1,2]. The difference in sums of the two parts will be 1 - 2 = -1.
- If we remove nums[1] = 1, the array will be [3,2]. The difference in sums of the two parts will be 3 - 2 = 1.
- If we remove nums[2] = 2, the array will be [3,1]. The difference in sums of the two parts will be 3 - 1 = 2.
The minimum difference between sums of the two parts is min(-1,1,2) = -1.

Example 2:
Input: nums = [7,9,5,8,1,3]
Output: 1
Explanation:
Here n = 2. So we must remove 2 elements and divide the remaining array into two parts containing two elements each.
If we remove nums[2] = 5 and nums[3] = 8, the resultant array will be [7,9,1,3].
The difference in sums will be (7+9) - (1+3) = 12.
To obtain the minimum difference, we should remove nums[1] = 9 and nums[4] = 1.
The resultant array becomes [7,5,8,3]. The difference in sums of the two parts is (7+5) - (8+3) = 1.
It can be shown that it is not possible to obtain a difference smaller than 1.

Constraints:
nums.length == 3 * n
1 <= n <= 10^5
1 <= nums[i] <= 10^5
```

<details><summary>Hint</summary>

```text
1. The lowest possible difference can be obtained when the sum of the first n elements in the resultant array is minimum,
   and the sum of the next n elements is maximum.
2. For every index i,
   think about how you can find the minimum possible sum of n elements with indices lesser or equal to i, if possible.
3. Similarly, for every index i,
   try to find the maximum possible sum of n elements with indices greater or equal to i, if possible.
4. Now for all indices, check if we can consider it as the partitioning index and hence find the answer.
```

</details>

</details>

<details><summary>C</summary>

```c
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#define MIN_QUEUE_SIZE (64)

typedef struct Element {
    int data[1];
} Element;
typedef bool (*compare)(const void *, const void *);
typedef struct PriorityQueue {
    Element *arr;
    int capacity;
    int queueSize;
    compare lessFunc;
} PriorityQueue;

Element *createElement(int x, int y) {
    Element *pObj = NULL;

    pObj = (Element *)malloc(sizeof(Element));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->data[0] = x;
    pObj->data[1] = y;

    return pObj;
}
static bool less(const void *a, const void *b) {
    bool retVal = false;

    Element *e1 = (Element *)a;
    Element *e2 = (Element *)b;
    retVal = (e1->data[0] > e2->data[0]);

    return retVal;
}
static bool greater(const void *a, const void *b) {
    bool retVal = false;

    Element *e1 = (Element *)a;
    Element *e2 = (Element *)b;
    retVal = (e1->data[0] < e2->data[0]);

    return retVal;
}
static void memswap(void *m1, void *m2, size_t size) {
    unsigned char *a = (unsigned char *)m1;
    unsigned char *b = (unsigned char *)m2;
    while (size--) {
        *b = *b ^ *a;
        *a = *b ^ *a;
        *b = *b ^ *a;
        a++;
        b++;
    }
}
static void swap(Element *arr, int i, int j) {
    //
    memswap(&arr[i], &arr[j], sizeof(Element));
}
static void down(Element *arr, int size, int i, compare cmpFunc) {
    for (int k = 2 * i + 1; k < size; k = 2 * k + 1) {
        if (k + 1 < size && cmpFunc(&arr[k], &arr[k + 1])) {
            k++;
        }
        if (cmpFunc(&arr[k], &arr[(k - 1) / 2])) {
            break;
        }
        swap(arr, k, (k - 1) / 2);
    }
}
PriorityQueue *createPriorityQueue(compare cmpFunc) {
    PriorityQueue *pObj = NULL;

    pObj = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->capacity = MIN_QUEUE_SIZE;
    pObj->arr = (Element *)malloc(sizeof(Element) * pObj->capacity);
    if (pObj->arr == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->queueSize = 0;
    pObj->lessFunc = cmpFunc;

    return pObj;
}
void heapfiy(PriorityQueue *obj) {
    for (int i = obj->queueSize / 2 - 1; i >= 0; i--) {
        down(obj->arr, obj->queueSize, i, obj->lessFunc);
    }
}
void enQueue(PriorityQueue *obj, Element *e) {
    // we need to alloc more space, just twice space size
    if (obj->queueSize == obj->capacity) {
        obj->capacity *= 2;
        obj->arr = realloc(obj->arr, sizeof(Element) * obj->capacity);
    }
    memcpy(&obj->arr[obj->queueSize], e, sizeof(Element));
    for (int i = obj->queueSize; i > 0 && obj->lessFunc(&obj->arr[(i - 1) / 2], &obj->arr[i]); i = (i - 1) / 2) {
        swap(obj->arr, i, (i - 1) / 2);
    }
    obj->queueSize++;
}
Element *deQueue(PriorityQueue *obj) {
    Element *pRetVal = NULL;

    swap(obj->arr, 0, obj->queueSize - 1);
    down(obj->arr, obj->queueSize - 1, 0, obj->lessFunc);
    pRetVal = &obj->arr[obj->queueSize - 1];
    obj->queueSize--;

    return pRetVal;
}
bool isEmpty(const PriorityQueue *obj) {
    bool retVal = (obj->queueSize == 0);

    return retVal;
}
Element *front(const PriorityQueue *obj) {
    Element *pRetVal = NULL;

    if (obj->queueSize != 0) {
        pRetVal = &obj->arr[0];
    }

    return pRetVal;
}
void clear(PriorityQueue *obj) {
    //
    obj->queueSize = 0;
}
int size(const PriorityQueue *obj) {
    int retVal = obj->queueSize;

    return retVal;
}
void freeQueue(PriorityQueue *obj) {
    free(obj->arr);
    obj->arr = NULL;
    free(obj);
    obj = NULL;
}

#endif  // PRIORITY_QUEUE_H
long long minimumDifference(int *nums, int numsSize) {
    long long retVal = 0;

    int n = numsSize / 3;

    // max heap
    long long sum = 0;
    PriorityQueue *maxHeap = createPriorityQueue(greater);
    for (int i = 0; i < n; ++i) {
        sum += nums[i];
        Element e;
        e.data[0] = nums[i];
        enQueue(maxHeap, &e);
    }
    long long part1[n + 1];
    memset(part1, 0, sizeof(part1));
    part1[0] = sum;
    for (int i = n; i < n * 2; ++i) {
        sum += nums[i];
        Element e;
        e.data[0] = nums[i];
        enQueue(maxHeap, &e);
        sum -= front(maxHeap)->data[0];
        deQueue(maxHeap);
        part1[i - (n - 1)] = sum;
    }
    freeQueue(maxHeap);

    // min heap
    long long part2 = 0;
    PriorityQueue *minHeap = createPriorityQueue(less);
    for (int i = n * 3 - 1; i >= n * 2; --i) {
        part2 += nums[i];
        Element e;
        e.data[0] = nums[i];
        enQueue(minHeap, &e);
    }
    retVal = part1[n] - part2;
    for (int i = n * 2 - 1; i >= n; --i) {
        part2 += nums[i];
        Element e;
        e.data[0] = nums[i];
        enQueue(minHeap, &e);
        part2 -= front(minHeap)->data[0];
        deQueue(minHeap);
        retVal = fmin(retVal, part1[i - n] - part2);
    }
    freeQueue(minHeap);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long minimumDifference(vector<int>& nums) {
        long long retVal = 0;

        int n = nums.size() / 3;

        // max heap
        long long sum = 0;
        priority_queue<int> maxHeap;
        for (int i = 0; i < n; ++i) {
            sum += nums[i];
            maxHeap.push(nums[i]);
        }
        vector<long long> part1(n + 1);
        part1[0] = sum;
        for (int i = n; i < n * 2; ++i) {
            sum += nums[i];
            maxHeap.push(nums[i]);
            sum -= maxHeap.top();
            maxHeap.pop();
            part1[i - (n - 1)] = sum;
        }

        // min heap
        long long part2 = 0;
        priority_queue<int, vector<int>, greater<int>> minHeap;
        for (int i = n * 3 - 1; i >= n * 2; --i) {
            part2 += nums[i];
            minHeap.push(nums[i]);
        }
        retVal = part1[n] - part2;
        for (int i = n * 2 - 1; i >= n; --i) {
            part2 += nums[i];
            minHeap.push(nums[i]);
            part2 -= minHeap.top();
            minHeap.pop();
            retVal = min(retVal, part1[i - n] - part2);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minimumDifference(self, nums: List[int]) -> int:
        retVal = 0

        n = len(nums) // 3

        # max heap
        total = sum(nums[:n])
        part1 = [0] * (n + 1)
        part1[0] = total
        maxHeap = [-x for x in nums[:n]]
        heapify(maxHeap)
        for i in range(n, n * 2):
            total += nums[i]
            heappush(maxHeap, -nums[i])
            total -= -heappop(maxHeap)
            part1[i - (n - 1)] = total

        # min heap
        part2 = sum(nums[n * 2:])
        minHeap = nums[n * 2:]
        heapify(minHeap)
        retVal = part1[n] - part2
        for i in range(n * 2 - 1, n - 1, -1):
            part2 += nums[i]
            heappush(minHeap, nums[i])
            part2 -= heappop(minHeap)
            retVal = min(retVal, part1[i - n] - part2)

        return retVal
```

</details>

## [2336. Smallest Number in Infinite Set](https://leetcode.com/problems/smallest-number-in-infinite-set/)  1375

<details><summary>Description</summary>

```text
You have a set which contains all positive integers [1, 2, 3, 4, 5, ...].

Implement the SmallestInfiniteSet class:
- SmallestInfiniteSet()
  Initializes the SmallestInfiniteSet object to contain all positive integers.
- int popSmallest()
  Removes and returns the smallest integer contained in the infinite set.
- void addBack(int num)
  Adds a positive integer num back into the infinite set, if it is not already in the infinite set.

Example 1:
Input
["SmallestInfiniteSet", "addBack", "popSmallest", "popSmallest", "popSmallest",
"addBack", "popSmallest", "popSmallest", "popSmallest"]
[[], [2], [], [], [], [1], [], [], []]
Output
[null, null, 1, 2, 3, null, 1, 4, 5]
Explanation
SmallestInfiniteSet smallestInfiniteSet = new SmallestInfiniteSet();
smallestInfiniteSet.addBack(2);    // 2 is already in the set, so no change is made.
smallestInfiniteSet.popSmallest(); // return 1, since 1 is the smallest number, and remove it from the set.
smallestInfiniteSet.popSmallest(); // return 2, and remove it from the set.
smallestInfiniteSet.popSmallest(); // return 3, and remove it from the set.
smallestInfiniteSet.addBack(1);    // 1 is added back to the set.
smallestInfiniteSet.popSmallest(); // return 1, since 1 was added back to the set and
                                   // is the smallest number, and remove it from the set.
smallestInfiniteSet.popSmallest(); // return 4, and remove it from the set.
smallestInfiniteSet.popSmallest(); // return 5, and remove it from the set.

Constraints:
1 <= num <= 1000
At most 1000 calls will be made in total to popSmallest and addBack.
```

<details><summary>Hint</summary>

```text
1. Based on the constraints, what is the maximum element that can possibly be popped?
2. Maintain whether elements are in or not in the set. How many elements do we consider?
```

</details>

</details>

<details><summary>C</summary>

```c
#define MAX_NUM (1001)  // 1 <= num <= 1000
typedef struct {
    int record[MAX_NUM];
} SmallestInfiniteSet;
SmallestInfiniteSet* smallestInfiniteSetCreate() {
    SmallestInfiniteSet* pRetVal = (SmallestInfiniteSet*)malloc(sizeof(SmallestInfiniteSet));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    int i;
    for (i = 0; i < MAX_NUM; ++i) {
        pRetVal->record[i] = 1;
    }

    return pRetVal;
}
int smallestInfiniteSetPopSmallest(SmallestInfiniteSet* obj) {
    int retVal = 0;

    int i;
    for (i = 1; i < MAX_NUM; ++i) {
        if (obj->record[i] == 1) {
            retVal = i;
            obj->record[i] = 0;
            break;
        }
    }

    return retVal;
}
void smallestInfiniteSetAddBack(SmallestInfiniteSet* obj, int num) {
    if (num > MAX_NUM) {
        return;
    }
    obj->record[num] = 1;
}
void smallestInfiniteSetFree(SmallestInfiniteSet* obj) {
    free(obj);
    obj = NULL;
}
/**
 * Your SmallestInfiniteSet struct will be instantiated and called as such:
 * SmallestInfiniteSet* obj = smallestInfiniteSetCreate();
 * int param_1 = smallestInfiniteSetPopSmallest(obj);
 * smallestInfiniteSetAddBack(obj, num);
 * smallestInfiniteSetFree(obj);
 */
```

</details>

<details><summary>C++</summary>

```c++
class SmallestInfiniteSet {
   public:
    int current;
    set<int> record;

    SmallestInfiniteSet() {
        //
        current = 1;
    }
    int popSmallest() {
        int retVal = 0;

        if (record.size()) {
            retVal = *record.begin();
            record.erase(retVal);
        } else {
            ++current;
            retVal = current - 1;
        }

        return retVal;
    }
    void addBack(int num) {
        if (current > num) {
            record.insert(num);
        }
    }
};
/**
 * Your SmallestInfiniteSet object will be instantiated and called as such:
 * SmallestInfiniteSet* obj = new SmallestInfiniteSet();
 * int param_1 = obj->popSmallest();
 * obj->addBack(num);
 */
```

</details>

<details><summary>Python3</summary>

```python
class SmallestInfiniteSet:
    def __init__(self):
        self.current = 1
        self.record = set()

    def popSmallest(self) -> int:
        retVal = 0

        if self.record:
            retVal = min(self.record)
            self.record.remove(retVal)
        else:
            self.current += 1
            retVal = self.current - 1

        return retVal

    def addBack(self, num: int) -> None:
        if self.current > num:
            self.record.add(num)

# Your SmallestInfiniteSet object will be instantiated and called as such:
# obj = SmallestInfiniteSet()
# param_1 = obj.popSmallest()
# obj.addBack(num)
```

</details>

## [2406. Divide Intervals Into Minimum Number of Groups](https://leetcode.com/problems/divide-intervals-into-minimum-number-of-groups/)  1713

- [Official](https://leetcode.com/problems/divide-intervals-into-minimum-number-of-groups/editorial/)

<details><summary>Description</summary>

```text
You are given a 2D integer array intervals
where intervals[i] = [lefti, righti] represents the inclusive interval [lefti, righti].

You have to divide the intervals into one or more groups such that each interval is in exactly one group,
and no two intervals that are in the same group intersect each other.

Return the minimum number of groups you need to make.

Two intervals intersect if there is at least one common number between them.
For example, the intervals [1, 5] and [5, 8] intersect.

Example 1:
Input: intervals = [[5,10],[6,8],[1,5],[2,3],[1,10]]
Output: 3
Explanation: We can divide the intervals into the following groups:
- Group 1: [1, 5], [6, 8].
- Group 2: [2, 3], [5, 10].
- Group 3: [1, 10].
It can be proven that it is not possible to divide the intervals into fewer than 3 groups.

Example 2:
Input: intervals = [[1,3],[5,6],[8,10],[11,13]]
Output: 1
Explanation: None of the intervals overlap, so we can put all of them in one group.

Constraints:
1 <= intervals.length <= 10^5
intervals[i].length == 2
1 <= lefti <= righti <= 10^6
```

<details><summary>Hint</summary>

```text
1. Can you find a different way to describe the question?
2. The minimum number of groups we need is equivalent to the maximum number of intervals that overlap at some point.
   How can you find that?
```

</details>

</details>

<details><summary>C</summary>

```c
int compareIntArray(const void *a1, const void *a2) {
    int *p1 = (int *)a1;
    int *p2 = (int *)a2;

    // ascending order
    if (p1[0] == p2[0]) {
        return (p1[1] > p2[1]);
    }

    return (p1[0] > p2[0]);
}
int minGroups(int **intervals, int intervalsSize, int *intervalsColSize) {
    int retVal = 0;

    // Convert the intervals to two events start as {start, 1} and end as {end, -1}
    int intervalsWithEndSize = 2 * intervalsSize;
    int intervalsWithEnd[intervalsWithEndSize][2];
    memset(intervalsWithEnd, 0, sizeof(intervalsWithEnd));
    int i = 0;
    for (i = 0; i < intervalsSize; ++i) {
        intervalsWithEnd[2 * i][0] = intervals[i][0];
        intervalsWithEnd[2 * i][1] = 1;
        intervalsWithEnd[2 * i + 1][0] = intervals[i][1] + 1;
        intervalsWithEnd[2 * i + 1][1] = -1;
    }
    // Sort the events according to the number and then by the value (1/-1).
    qsort(intervalsWithEnd, intervalsWithEndSize, sizeof(intervalsWithEnd[0]), compareIntArray);

    int concurrentIntervals = 0;
    int maxConcurrentIntervals = 0;
    for (i = 0; i < intervalsWithEndSize; ++i) {
        concurrentIntervals += intervalsWithEnd[i][1];
        maxConcurrentIntervals = fmax(maxConcurrentIntervals, concurrentIntervals);
    }
    retVal = maxConcurrentIntervals;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minGroups(vector<vector<int>>& intervals) {
        int retVal = 0;

        // Convert the intervals to two events start as {start, 1} and end as {end, -1}
        vector<pair<int, int>> intervalsWithEnd;
        for (vector<int> interval : intervals) {
            intervalsWithEnd.push_back({interval[0], 1});
            intervalsWithEnd.push_back({interval[1] + 1, -1});
        }
        // Sort the events according to the number and then by the value (1/-1).
        sort(intervalsWithEnd.begin(), intervalsWithEnd.end());

        int concurrentIntervals = 0;
        int maxConcurrentIntervals = 0;
        for (auto p : intervalsWithEnd) {
            concurrentIntervals += p.second;
            maxConcurrentIntervals = max(maxConcurrentIntervals, concurrentIntervals);
        }
        retVal = maxConcurrentIntervals;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minGroups(self, intervals: List[List[int]]) -> int:
        retVal = 0

        # Convert the intervals to two events start as (start, 1) and end as (end + 1, -1)
        events = []
        for interval in intervals:
            events.append((interval[0], 1))
            events.append((interval[1] + 1, -1))
        # Sort the events first by time, and then by type (1 for start, -1 for end).
        events.sort(key=lambda x: (x[0], x[1]))

        concurrentIntervals = 0
        maxConcurrentIntervals = 0
        for event in events:
            concurrentIntervals += event[1]
            maxConcurrentIntervals = max(maxConcurrentIntervals, concurrentIntervals)
        retVal = maxConcurrentIntervals

        return retVal
```

</details>

## [2462. Total Cost to Hire K Workers](https://leetcode.com/problems/total-cost-to-hire-k-workers/)  1763

- [Official](https://leetcode.com/problems/total-cost-to-hire-k-workers/editorial/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array costs where costs[i] is the cost of hiring the ith worker.

You are also given two integers k and candidates. We want to hire exactly k workers according to the following rules:
- You will run k sessions and hire exactly one worker in each session.
- In each hiring session, choose the worker with the lowest cost from either the first candidates workers
  or the last candidates workers. Break the tie by the smallest index.
  - For example, if costs = [3,2,7,7,1,2] and candidates = 2, then in the first hiring session,
    we will choose the 4th worker because they have the lowest cost [3,2,7,7,1,2].
  - In the second hiring session, we will choose 1st worker because they have the same lowest cost as 4th worker
    but they have the smallest index [3,2,7,7,2]. Please note that the indexing may be changed in the process.
- If there are fewer than candidates workers remaining, choose the worker with the lowest cost among them.
Break the tie by the smallest index.
- A worker can only be chosen once.

Return the total cost to hire exactly k workers.

Example 1:
Input: costs = [17,12,10,2,7,2,11,20,8], k = 3, candidates = 4
Output: 11
Explanation: We hire 3 workers in total. The total cost is initially 0.
- In the first hiring round we choose the worker from [17,12,10,2,7,2,11,20,8].
  The lowest cost is 2, and we break the tie by the smallest index, which is 3.
  The total cost = 0 + 2 = 2.
- In the second hiring round we choose the worker from [17,12,10,7,2,11,20,8].
  The lowest cost is 2 (index 4). The total cost = 2 + 2 = 4.
- In the third hiring round we choose the worker from [17,12,10,7,11,20,8].
  The lowest cost is 7 (index 3). The total cost = 4 + 7 = 11.
  Notice that the worker with index 3 was common in the first and last four workers.
The total hiring cost is 11.

Example 2:
Input: costs = [1,2,4,1], k = 3, candidates = 3
Output: 4
Explanation: We hire 3 workers in total. The total cost is initially 0.
- In the first hiring round we choose the worker from [1,2,4,1].
  The lowest cost is 1, and we break the tie by the smallest index, which is 0.
  The total cost = 0 + 1 = 1.
  Notice that workers with index 1 and 2 are common in the first and last 3 workers.
- In the second hiring round we choose the worker from [2,4,1].
  The lowest cost is 1 (index 2).
  The total cost = 1 + 1 = 2.
- In the third hiring round there are less than three candidates.
  We choose the worker from the remaining workers [2,4].
  The lowest cost is 2 (index 0). The total cost = 2 + 2 = 4.
The total hiring cost is 4.

Constraints:
1 <= costs.length <= 10^5
1 <= costs[i] <= 10^5
1 <= k, candidates <= costs.length
```

<details><summary>Hint</summary>

```text
1. Maintain two minheaps: one for the left and one for the right.
2. Compare the top element from two heaps and remove the appropriate one.
3. Add a new element to the heap and maintain its size as k.
```

</details>

</details>

<details><summary>C</summary>

```c
// https://leetcode.cn/problems/total-cost-to-hire-k-workers/solutions/1954280/gu-yong-k-wei-gong-ren-de-zong-dai-jie-b-jj2g/
#define INVALID_INDEX (-1)
#define FATHER_NODE(x) ((0 == (x)) ? (INVALID_INDEX) : (((x)-1) >> 1))
#define LEFT_NODE(x) (((x) << 1) + 1)
#define RIGHT_NODE(x) (((x) << 1) + 2)
typedef struct {
    int *buffer;
    int bufferSize;
} HeapNode;
void heapPush(HeapNode *heap, int value) {
    int son = heap->bufferSize;
    int father = FATHER_NODE(son);

    heap->bufferSize++;
    while ((INVALID_INDEX != father) && (heap->buffer[father] > value)) {
        heap->buffer[son] = heap->buffer[father];
        son = father;
        father = FATHER_NODE(son);
    }
    heap->buffer[son] = value;
}
void heapPop(HeapNode *heap) {
    int father = 0;
    int left = LEFT_NODE(father);
    int right = RIGHT_NODE(father);
    int son = 0;
    int value = 0;

    heap->bufferSize--;
    value = heap->buffer[heap->bufferSize];
    while (((heap->bufferSize > left) && (heap->buffer[left] < value)) ||
           ((heap->bufferSize > right) && (heap->buffer[right] < value))) {
        son = ((heap->bufferSize > right) && (heap->buffer[right] < heap->buffer[left])) ? (right) : (left);
        heap->buffer[father] = heap->buffer[son];
        father = son;
        left = LEFT_NODE(father);
        right = RIGHT_NODE(father);
    }
    heap->buffer[father] = value;
}
long long totalCost(int *costs, int costsSize, int k, int candidates) {
    long long retVal = 0;

    int mostHeapSize = fmin(candidates << 1, costsSize);
    int buffer[mostHeapSize];
    memset(buffer, 0, sizeof(buffer));
    int x = 0;
    int value = 0;
    int leftCounter = 0;
    int rightCounter = 0;
    HeapNode heap;
    heap.bufferSize = 0;
    heap.buffer = buffer;
    x = fmin(candidates, costsSize);
    while (x > leftCounter) {
        value = costs[leftCounter] << 1;
        heapPush(&heap, value);
        leftCounter++;
    }
    x = fmin(candidates, costsSize - leftCounter);
    while (x > rightCounter) {
        value = (costs[costsSize - 1 - rightCounter] << 1) + 1;
        heapPush(&heap, value);
        rightCounter++;
    }

    x = 0;
    while ((k > x) && (0 < heap.bufferSize)) {
        value = heap.buffer[0];
        heapPop(&heap);
        retVal += (value >> 1);

        if (costsSize > leftCounter + rightCounter) {
            if (value & 1) {
                value = (costs[costsSize - 1 - rightCounter] << 1) + 1;
                heapPush(&heap, value);
                rightCounter++;
            } else {
                value = costs[leftCounter] << 1;
                heapPush(&heap, value);
                leftCounter++;
            }
        }

        x++;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long totalCost(vector<int>& costs, int k, int candidates) {
        long long retVal = 0;

        priority_queue<int, vector<int>, greater<>> leftHeap;
        priority_queue<int, vector<int>, greater<>> rightHeap;

        int left = 0;
        int right = costs.size() - 1;
        while (k--) {
            while (((int)leftHeap.size() < candidates) && (left <= right)) {
                leftHeap.push(costs[left++]);
            }
            while (((int)rightHeap.size() < candidates) && (left <= right)) {
                rightHeap.push(costs[right--]);
            }

            int leftValue = (leftHeap.size() > 0) ? leftHeap.top() : numeric_limits<int>::max();
            int rightValue = (rightHeap.size() > 0) ? rightHeap.top() : numeric_limits<int>::max();
            if (leftValue <= rightValue) {
                retVal += leftValue;
                leftHeap.pop();
            } else {
                retVal += rightValue;
                rightHeap.pop();
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
    def totalCost(self, costs: List[int], k: int, candidates: int) -> int:
        retVal = 0

        leftHeap = costs[:candidates]
        heapify(leftHeap)
        rightHeap = costs[max(candidates, len(costs) - candidates):]
        heapify(rightHeap)

        left = candidates
        right = len(costs) - 1 - candidates
        for _ in range(k):
            if (not rightHeap) or ((leftHeap) and (leftHeap[0] <= rightHeap[0])):
                retVal += heappop(leftHeap)
                if left <= right:
                    heappush(leftHeap, costs[left])
                    left += 1
            else:
                retVal += heappop(rightHeap)
                if left <= right:
                    heappush(rightHeap, costs[right])
                    right -= 1

        return retVal
```

</details>

## [2530. Maximal Score After Applying K Operations](https://leetcode.com/problems/maximal-score-after-applying-k-operations/)  1386

- [Official](https://leetcode.com/problems/maximal-score-after-applying-k-operations/editorial/)
- [Official](https://leetcode.cn/problems/maximal-score-after-applying-k-operations/solutions/2484596/zhi-xing-k-ci-cao-zuo-hou-de-zui-da-fen-a1jub/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array nums and an integer k. You have a starting score of 0.

In one operation:
1. choose an index i such that 0 <= i < nums.length,
2. increase your score by nums[i], and
3. replace nums[i] with ceil(nums[i] / 3).

Return the maximum possible score you can attain after applying exactly k operations.

The ceiling function ceil(val) is the least integer greater than or equal to val.

Example 1:
Input: nums = [10,10,10,10,10], k = 5
Output: 50
Explanation: Apply the operation to each array element exactly once. The final score is 10 + 10 + 10 + 10 + 10 = 50.

Example 2:
Input: nums = [1,10,3,3,3], k = 3
Output: 17
Explanation: You can do the following operations:
Operation 1: Select i = 1, so nums becomes [1,4,3,3,3]. Your score increases by 10.
Operation 2: Select i = 1, so nums becomes [1,2,3,3,3]. Your score increases by 4.
Operation 3: Select i = 2, so nums becomes [1,1,1,3,3]. Your score increases by 3.
The final score is 10 + 4 + 3 = 17.

Constraints:
1 <= nums.length, k <= 10^5
1 <= nums[i] <= 10^9
```

<details><summary>Hint</summary>

```text
1. It is always optimal to select the greatest element in the array.
2. Use a heap to query for the maximum in O(log n) time.
```

</details>

</details>

<details><summary>C</summary>

```c
#ifndef HEAP_H
#define HEAP_H

void swap(int *nums, int i, int j) {
    int x = nums[i];
    nums[i] = nums[j];
    nums[j] = x;
}
void down(int *nums, int size, int i) {
    int k;
    for (k = 2 * i + 1; k < size; k = 2 * k + 1) {
        if ((k + 1 < size) && (nums[k] < nums[k + 1])) {
            k++;
        }
        if (nums[k] < nums[(k - 1) / 2]) {
            break;
        }

        swap(nums, k, (k - 1) / 2);
    }
}
void Init(int *nums, int size) {
    int i;
    for (i = size / 2 - 1; i >= 0; i--) {
        down(nums, size, i);
    }
}
void Push(int *nums, int size, int x) {
    nums[size] = x;

    int i;
    for (i = size; ((i > 0) && (nums[(i - 1) / 2] < nums[i])); i = (i - 1) / 2) {
        swap(nums, i, (i - 1) / 2);
    }
}
int Pop(int *nums, int size) {
    int retVal = 0;

    swap(nums, 0, size - 1);
    down(nums, size - 1, 0);
    retVal = nums[size - 1];

    return retVal;
}

#endif  // HEAP_H
long long maxKelements(int *nums, int numsSize, int k) {
    long long retVal = 0;

    Init(nums, numsSize);

    int maxElement;
    int i;
    for (i = 0; i < k; i++) {
        maxElement = Pop(nums, numsSize);
        retVal += maxElement;
        Push(nums, numsSize - 1, (maxElement + 2) / 3);
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long maxKelements(vector<int>& nums, int k) {
        long long retVal = 0;

        // Create max-heap to store the elements.
        priority_queue<int> maxHeap;
        for (auto& i : nums) {
            maxHeap.push(i);
        }

        while (k--) {
            int maxElement = maxHeap.top();
            retVal += maxElement;
            maxHeap.pop();
            maxHeap.push(ceil(maxElement / 3.0));
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxKelements(self, nums: List[int], k: int) -> int:
        retVal = 0

        # Define a max-heap by using a min-heap with negative values
        maxHeap = [-i for i in nums]
        heapify(maxHeap)

        while k > 0:
            k -= 1
            # Retrieve the max element (invert the sign because it's stored as negative)
            maxElement = -heappop(maxHeap)
            retVal += maxElement

            heappush(maxHeap, -ceil(maxElement / 3))

        return retVal
```

</details>

## [2542. Maximum Subsequence Score](https://leetcode.com/problems/maximum-subsequence-score/)  2056

- [Official](https://leetcode.com/problems/maximum-subsequence-score/editorial/)

<details><summary>Description</summary>

```text
You are given two 0-indexed integer arrays nums1 and nums2 of equal length n and a positive integer k.
You must choose a subsequence of indices from nums1 of length k.

For chosen indices i0, i1, ..., ik - 1, your score is defined as:
- The sum of the selected elements from nums1 multiplied with the minimum of the selected elements from nums2.
- It can defined simply as: (nums1[i0] + nums1[i1] +...+ nums1[ik - 1]) * min(nums2[i0] , nums2[i1], ... ,nums2[ik - 1]).

Return the maximum possible score.

A subsequence of indices of an array is a set that can be derived from the set {0, 1, ..., n-1}
by deleting some or no elements.

Example 1:
Input: nums1 = [1,3,3,2], nums2 = [2,1,3,4], k = 3
Output: 12
Explanation:
The four possible subsequence scores are:
- We choose the indices 0, 1, and 2 with score = (1+3+3) * min(2,1,3) = 7.
- We choose the indices 0, 1, and 3 with score = (1+3+2) * min(2,1,4) = 6.
- We choose the indices 0, 2, and 3 with score = (1+3+2) * min(2,3,4) = 12.
- We choose the indices 1, 2, and 3 with score = (3+3+2) * min(1,3,4) = 8.
Therefore, we return the max score, which is 12.

Example 2:
Input: nums1 = [4,2,3,1,1], nums2 = [7,5,10,9,6], k = 1
Output: 30
Explanation:
Choosing index 2 is optimal: nums1[2] * nums2[2] = 3 * 10 = 30 is the maximum possible score.

Constraints:
n == nums1.length == nums2.length
1 <= n <= 10^5
0 <= nums1[i], nums2[j] <= 10^5
1 <= k <= n
```

<details><summary>Hint</summary>

```text
1. How can we use sorting here?
2. Try sorting the two arrays based on second array.
3. Loop through nums2 and compute the max product given the minimum is nums2[i]. Update the answer accordingly.
```

</details>

</details>

<details><summary>C</summary>

```c
#ifndef HEAP_H
#define HEAP_H  // Implementation of a priority queue using a min-heap.

//
#define LEFT(i) (2 * (i) + 1)
#define RIGHT(i) (2 * (i) + 2)
#define PARENT(i) (i > 0 ? (((i)-1) / 2) : 0)

//
typedef struct {
    int *arr;
    int capacity;  // number of memory allocated for elements
    int size;      // number of elements
} Min_heap;

//
void heapify(Min_heap *heap, int i) {
    int l = LEFT(i);
    int r = RIGHT(i);
    int min_i = i;

    if ((l < heap->size) && (heap->arr[l] < heap->arr[min_i])) {
        min_i = l;
    }
    if ((r < heap->size) && (heap->arr[r] < heap->arr[min_i])) {
        min_i = r;
    }

    if (min_i != i) {
        int temp = heap->arr[min_i];
        heap->arr[min_i] = heap->arr[i];
        heap->arr[i] = temp;

        heapify(heap, min_i);
    }
}
void build_heap(Min_heap *heap) {
    for (int i = PARENT(heap->size - 1); i >= 0; --i) {
        heapify(heap, i);
    }
}
int insert(Min_heap *heap, int elem) {
    if (heap->size == heap->capacity) {
        return 1;
    }

    heap->arr[heap->size] = elem;
    heap->size++;

    int i = heap->size - 1;

    while (i > 0) {
        i = PARENT(i);
        heapify(heap, i);
    }

    return 0;
}
int extract_min(Min_heap *heap, int *result) {
    if (heap->size == 0) {
        return 1;
    }

    *result = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    heapify(heap, 0);

    return 0;
}
int min_heap_init(Min_heap *heap, int capacity, int *inits, int n) {
    heap->arr = malloc(capacity * sizeof(int));

    if (heap->arr == NULL) {
        return 1;
    }

    heap->size = 0;
    heap->capacity = capacity;

    if (n > 0) {
        int i = 0;
        for (; i < n && i < capacity; ++i) {
            heap->arr[i] = inits[i];
        }
        heap->size = i;

        build_heap(heap);
    }

    return 0;
}
int min_heap_destroy(Min_heap *heap) {
    if (heap->arr == NULL) {
        return 1;
    }

    free(heap->arr);

    return 0;
}
long long min_heap_sum(Min_heap *heap) {
    long long result = 0;

    if (heap == NULL) {
        return result;
    }

    for (int i = 0; i < heap->size; ++i) {
        result += (long long)heap->arr[i];
    }

    return result;
}

#endif  // HEAP_H
typedef struct {
    int first;
    int second;
} pair;
int compareStruct(const void *lhs, const void *rhs) {
    const pair *lhs_pair = (const pair *)lhs;
    const pair *rhs_pair = (const pair *)rhs;

    if (lhs_pair->second < rhs_pair->second) {
        return 1;
    } else if (lhs_pair->second > rhs_pair->second) {
        return -1;
    } else {
        return 0;
    }
}
long long maxScore(int *nums1, int nums1Size, int *nums2, int nums2Size, int k) {
    long long retVal = 0;

    //
    pair *pairs = malloc(nums1Size * sizeof(pair));
    if (pairs == NULL) {
        perror("malloc");
        return retVal;
    }
    for (int i = 0; i < nums1Size; ++i) {
        pairs[i].first = nums1[i];
        pairs[i].second = nums2[i];
    }
    qsort(pairs, nums1Size, sizeof(pair), compareStruct);

    //
    int *topKNums1 = malloc(k * sizeof(pair));
    if (topKNums1 == NULL) {
        perror("malloc");
        free(pairs);
        pairs = NULL;
        return retVal;
    }
    for (int i = 0; i < k; ++i) {
        topKNums1[i] = pairs[i].first;
    }
    Min_heap topKNums1Heap;
    min_heap_init(&topKNums1Heap, k, topKNums1, k);

    //
    long long sumOfTopKNums1 = min_heap_sum(&topKNums1Heap);
    retVal = pairs[k - 1].second * sumOfTopKNums1;
    for (int i = k; i < nums1Size; ++i) {
        int popValue = 0;
        extract_min(&topKNums1Heap, &popValue);
        sumOfTopKNums1 -= popValue;
        sumOfTopKNums1 += pairs[i].first;
        insert(&topKNums1Heap, pairs[i].first);

        retVal = fmax(retVal, sumOfTopKNums1 * pairs[i].second);
    }

    //
    free(pairs);
    free(topKNums1);
    min_heap_destroy(&topKNums1Heap);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
        long long retVal = 0;

        vector<pair<int, int>> pairs;
        int nums1Size = nums1.size();
        for (int i = 0; i < nums1Size; i++) {
            pairs.push_back({nums1[i], nums2[i]});
        }
        sort(pairs.begin(), pairs.end(), [](pair<int, int>& a, pair<int, int>& b) { return a.second > b.second; });

        priority_queue<int, vector<int>, greater<int>> topKNums1;
        long long sumOfTopKNums1 = 0;
        for (int i = 0; i < k; i++) {
            sumOfTopKNums1 += (long long)pairs[i].first;
            topKNums1.push(pairs[i].first);
        }

        retVal = sumOfTopKNums1 * pairs[k - 1].second;
        for (int i = k; i < nums1Size; i++) {
            sumOfTopKNums1 += (pairs[i].first - topKNums1.top());
            topKNums1.pop();
            topKNums1.push(pairs[i].first);
            retVal = max(retVal, sumOfTopKNums1 * pairs[i].second);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxScore(self, nums1: List[int], nums2: List[int], k: int) -> int:
        retVal = 0

        pairs = [(num1, num2) for num1, num2 in zip(nums1, nums2)]
        pairs.sort(key=lambda x: -x[1])

        topKNums1 = [x[0] for x in pairs[:k]]
        sumOfTopKNums1 = sum(topKNums1)
        heapq.heapify(topKNums1)

        retVal = sumOfTopKNums1 * pairs[k - 1][1]
        nums1Size = len(nums1)
        for i in range(k, nums1Size):
            sumOfTopKNums1 -= heapq.heappop(topKNums1)
            sumOfTopKNums1 += pairs[i][0]
            heapq.heappush(topKNums1, pairs[i][0])
            retVal = max(retVal, sumOfTopKNums1 * pairs[i][1])

        return retVal
```

</details>

## [2558. Take Gifts From the Richest Pile](https://leetcode.com/problems/take-gifts-from-the-richest-pile/)  1276

- [Official](https://leetcode.com/problems/take-gifts-from-the-richest-pile/editorial/)
- [Official](https://leetcode.cn/problems/take-gifts-from-the-richest-pile/solutions/2477680/cong-shu-liang-zui-duo-de-dui-qu-zou-li-kt246/)

<details><summary>Description</summary>

```text
You are given an integer array gifts denoting the number of gifts in various piles. Every second, you do the following:
- Choose the pile with the maximum number of gifts.
- If there is more than one pile with the maximum number of gifts, choose any.
- Leave behind the floor of the square root of the number of gifts in the pile. Take the rest of the gifts.

Return the number of gifts remaining after k seconds.

Example 1:
Input: gifts = [25,64,9,4,100], k = 4
Output: 29
Explanation:
The gifts are taken in the following way:
- In the first second, the last pile is chosen and 10 gifts are left behind.
- Then the second pile is chosen and 8 gifts are left behind.
- After that the first pile is chosen and 5 gifts are left behind.
- Finally, the last pile is chosen again and 3 gifts are left behind.
The final remaining gifts are [5,8,9,4,3], so the total number of gifts remaining is 29.

Example 2:
Input: gifts = [1,1,1,1], k = 4
Output: 4
Explanation:
In this case, regardless which pile you choose, you have to leave behind 1 gift in each pile.
That is, you can't take any pile with you.
So, the total gifts remaining are 4.

Constraints:
1 <= gifts.length <= 10^3
1 <= gifts[i] <= 10^9
1 <= k <= 10^3
```

<details><summary>Hint</summary>

```text
1. How can you keep track of the largest gifts in the array
2. What is an efficient way to find the square root of a number?
3. Can you keep adding up the values of the gifts while ensuring they are in a certain order?
4. Can we use a priority queue or heap here?
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
long long pickGifts(int* gifts, int giftsSize, int k) {
    long long retVal = 0;

    MaxHeap* pGiftsHeap = createMaxHeap(giftsSize);
    if (pGiftsHeap == NULL) {
        return retVal;
    }
    for (int i = 0; i < giftsSize; ++i) {
        pushMaxHeap(pGiftsHeap, gifts[i]);
    }

    int maxElement;
    for (int i = 0; i < k; ++i) {
        maxElement = popMaxHeap(pGiftsHeap);
        pushMaxHeap(pGiftsHeap, sqrt(maxElement));
    }

    for (int i = 0; i < pGiftsHeap->size; ++i) {
        retVal += pGiftsHeap->data[i];
    }

    //
    freeMaxHeap(pGiftsHeap);
    pGiftsHeap = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    long long pickGifts(vector<int>& gifts, int k) {
        long long retVal = 0;

        priority_queue<int> giftsHeap(gifts.begin(), gifts.end());
        for (int i = 0; i < k; i++) {
            int maxElement = giftsHeap.top();
            giftsHeap.pop();
            giftsHeap.push(sqrt(maxElement));
        }

        while (giftsHeap.empty() == false) {
            retVal += giftsHeap.top();
            giftsHeap.pop();
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def pickGifts(self, gifts: List[int], k: int) -> int:
        retVal = 0

        giftsHeap = [-gift for gift in gifts]
        heapify(giftsHeap)
        for _ in range(k):
            maxElement = -heappop(giftsHeap)
            heappush(giftsHeap, -floor(sqrt(maxElement)))

        while giftsHeap:
            retVal -= heappop(giftsHeap)

        return retVal
```

</details>

## [2593. Find Score of an Array After Marking All Elements](https://leetcode.com/problems/find-score-of-an-array-after-marking-all-elements/)  1665

- [Official](https://leetcode.com/problems/find-score-of-an-array-after-marking-all-elements/editorial/)

<details><summary>Description</summary>

```text
You are given an array nums consisting of positive integers.

Starting with score = 0, apply the following algorithm:
- Choose the smallest integer of the array that is not marked.
  If there is a tie, choose the one with the smallest index.
- Add the value of the chosen integer to score.
- Mark the chosen element and its two adjacent elements if they exist.
- Repeat until all the array elements are marked.

Return the score you get after applying the above algorithm.

Example 1:
Input: nums = [2,1,3,4,5,2]
Output: 7
Explanation: We mark the elements as follows:
- 1 is the smallest unmarked element, so we mark it and its two adjacent elements: [2,1,3,4,5,2].
- 2 is the smallest unmarked element, so we mark it and its left adjacent element: [2,1,3,4,5,2].
- 4 is the only remaining unmarked element, so we mark it: [2,1,3,4,5,2].
Our score is 1 + 2 + 4 = 7.

Example 2:
Input: nums = [2,3,5,1,3,2]
Output: 5
Explanation: We mark the elements as follows:
- 1 is the smallest unmarked element, so we mark it and its two adjacent elements: [2,3,5,1,3,2].
- 2 is the smallest unmarked element, since there are two of them, we choose the left-most one,
  so we mark the one at index 0 and its right adjacent element: [2,3,5,1,3,2].
- 2 is the only remaining unmarked element, so we mark it: [2,3,5,1,3,2].
Our score is 1 + 2 + 2 = 5.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^6
```

<details><summary>Hint</summary>

```text
1. Try simulating the process of marking the elements and their adjacent.
2. If there is an element that was already marked, then you skip it.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareIntArray(const void* a1, const void* a2) {
    int* p1 = (int*)a1;
    int* p2 = (int*)a2;

    // ascending order
    if (p1[0] == p2[0]) {
        return (p1[1] > p2[1]);
    }

    return (p1[0] > p2[0]);
}
long long findScore(int* nums, int numsSize) {
    long long retVal = 0;

    int sorted[numsSize][2];
    memset(sorted, 0, sizeof(sorted));
    for (int i = 0; i < numsSize; ++i) {
        sorted[i][0] = nums[i];
        sorted[i][1] = i;
    }
    qsort(sorted, numsSize, sizeof(sorted[0]), compareIntArray);

    int marked[numsSize];
    memset(marked, false, sizeof(marked));
    int num, index;
    for (int i = 0; i < numsSize; i++) {
        num = sorted[i][0];
        index = sorted[i][1];

        if (marked[index] == true) {
            continue;
        }

        retVal += num;

        marked[index] = true;
        // mark adjacent elements if they exist
        if (index - 1 >= 0) {
            marked[index - 1] = true;
        }
        if (index + 1 < numsSize) {
            marked[index + 1] = true;
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
    long long findScore(vector<int>& nums) {
        long long retVal = 0;

        int numsSize = nums.size();

        auto cmp = [](pair<int, int>& pair1, pair<int, int>& pair2) {
            if (pair1.first != pair2.first) {
                return pair1.first > pair2.first;
            }
            return pair1.second > pair2.second;
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> heap(cmp);
        for (int i = 0; i < numsSize; ++i) {
            heap.push(make_pair(nums[i], i));
        }

        vector<bool> marked(numsSize);
        while (heap.empty() == false) {
            pair<int, int> element = heap.top();
            heap.pop();
            int num = element.first;
            int index = element.second;

            if (marked[index] == true) {
                continue;
            }

            retVal += num;

            marked[index] = true;
            // mark adjacent elements if they exist
            if (index - 1 >= 0) {
                marked[index - 1] = true;
            }
            if (index + 1 < numsSize) {
                marked[index + 1] = true;
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
    def findScore(self, nums):
        retVal = 0

        numsSize = len(nums)

        heap = []
        for index, num in enumerate(nums):
            heappush(heap, (num, index))

        marked = [False] * numsSize
        while heap:
            num, index = heappop(heap)

            if marked[index] == True:
                continue

            retVal += num
            marked[index] = True
            # mark adjacent elements if they exist
            if index - 1 >= 0:
                marked[index - 1] = True
            if index + 1 < numsSize:
                marked[index + 1] = True

        return retVal
```

</details>

## [3066. Minimum Operations to Exceed Threshold Value II](https://leetcode.com/problems/minimum-operations-to-exceed-threshold-value-ii/)  1399

- [Official](https://leetcode.com/problems/minimum-operations-to-exceed-threshold-value-ii/editorial/)
- [Official](https://leetcode.cn/problems/minimum-operations-to-exceed-threshold-value-ii/solutions/3040119/chao-guo-yu-zhi-de-zui-shao-cao-zuo-shu-y7tgx/)

<details><summary>Description</summary>

```text
You are given a 0-indexed integer array nums, and an integer k.

In one operation, you will:
- Take the two smallest integers x and y in nums.
- Remove x and y from nums.
- Add min(x, y) * 2 + max(x, y) anywhere in the array.

Note that you can only apply the described operation if nums contains at least two elements.

Return the minimum number of operations needed so that all elements of the array are greater than or equal to k.

Example 1:
Input: nums = [2,11,10,1,3], k = 10
Output: 2
Explanation:
In the first operation, we remove elements 1 and 2, then add 1 * 2 + 2 to nums. nums becomes equal to [4, 11, 10, 3].
In the second operation, we remove elements 3 and 4, then add 3 * 2 + 4 to nums. nums becomes equal to [10, 11, 10].
At this stage, all the elements of nums are greater than or equal to 10 so we can stop.
It can be shown that 2 is the minimum number of operations needed
so that all elements of the array are greater than or equal to 10.

Example 2:
Input: nums = [1,1,2,4,9], k = 20
Output: 4
Explanation:
After one operation, nums becomes equal to [2, 4, 9, 3].
After two operations, nums becomes equal to [7, 4, 9].
After three operations, nums becomes equal to [15, 9].
After four operations, nums becomes equal to [33].
At this stage, all the elements of nums are greater than 20 so we can stop.
It can be shown that 4 is the minimum number of operations needed
so that all elements of the array are greater than or equal to 20.

Constraints:
2 <= nums.length <= 2 * 10^5
1 <= nums[i] <= 10^9
1 <= k <= 10^9
The input is generated such that an answer always exists.
That is, there exists some sequence of operations after which all elements of the array are greater than or equal to k.
```

<details><summary>Hint</summary>

```text
1. Use priority queue to keep track of minimum elements.
2. Remove the minimum two elements, perform the operation, and insert the resulting number into the priority queue.
```

</details>

</details>

<details><summary>C</summary>

```c
#ifndef HEAP_H
#define HEAP_H

#define MIN_QUEUE_SIZE (64)

typedef struct Element {
    long long data[1];
} Element;
typedef bool (*compare)(const void *, const void *);

typedef struct PriorityQueue {
    Element *arr;
    int capacity;
    int queueSize;
    compare lessFunc;
} PriorityQueue;
Element *createElement(int x, int y) {
    Element *obj = (Element *)malloc(sizeof(Element));
    obj->data[0] = x;
    obj->data[1] = y;
    return obj;
}
static bool less(const void *a, const void *b) {
    Element *e1 = (Element *)a;
    Element *e2 = (Element *)b;
    return e1->data[0] > e2->data[0];
}
static void memswap(void *m1, void *m2, size_t size) {
    unsigned char *a = (unsigned char *)m1;
    unsigned char *b = (unsigned char *)m2;
    while (size--) {
        *b ^= *a ^= *b ^= *a;
        a++;
        b++;
    }
}
static void swap(Element *arr, int i, int j) {
    //
    memswap(&arr[i], &arr[j], sizeof(Element));
}
static void down(Element *arr, int size, int i, compare cmpFunc) {
    for (int k = 2 * i + 1; k < size; k = 2 * k + 1) {
        if (k + 1 < size && cmpFunc(&arr[k], &arr[k + 1])) {
            k++;
        }
        if (cmpFunc(&arr[k], &arr[(k - 1) / 2])) {
            break;
        }
        swap(arr, k, (k - 1) / 2);
    }
}
PriorityQueue *createPriorityQueue(compare cmpFunc) {
    PriorityQueue *obj = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    obj->capacity = MIN_QUEUE_SIZE;
    obj->arr = (Element *)malloc(sizeof(Element) * obj->capacity);
    obj->queueSize = 0;
    obj->lessFunc = cmpFunc;
    return obj;
}
void heapfiy(PriorityQueue *obj) {
    for (int i = obj->queueSize / 2 - 1; i >= 0; i--) {
        down(obj->arr, obj->queueSize, i, obj->lessFunc);
    }
}
void enQueue(PriorityQueue *obj, Element *e) {
    // we need to alloc more space, just twice space size
    if (obj->queueSize == obj->capacity) {
        obj->capacity *= 2;
        obj->arr = realloc(obj->arr, sizeof(Element) * obj->capacity);
    }
    memcpy(&obj->arr[obj->queueSize], e, sizeof(Element));
    for (int i = obj->queueSize; i > 0 && obj->lessFunc(&obj->arr[(i - 1) / 2], &obj->arr[i]); i = (i - 1) / 2) {
        swap(obj->arr, i, (i - 1) / 2);
    }
    obj->queueSize++;
}
Element *deQueue(PriorityQueue *obj) {
    swap(obj->arr, 0, obj->queueSize - 1);
    down(obj->arr, obj->queueSize - 1, 0, obj->lessFunc);
    Element *e = &obj->arr[obj->queueSize - 1];
    obj->queueSize--;
    return e;
}
bool isEmpty(const PriorityQueue *obj) {
    //
    return obj->queueSize == 0;
}
Element *front(const PriorityQueue *obj) {
    if (obj->queueSize == 0) {
        return NULL;
    } else {
        return &obj->arr[0];
    }
}
void clear(PriorityQueue *obj) {
    //
    obj->queueSize = 0;
}
int size(const PriorityQueue *obj) {
    //
    return obj->queueSize;
}
void freeQueue(PriorityQueue *obj) {
    free(obj->arr);
    free(obj);
}

#endif  // HEAP_H
int minOperations(int *nums, int numsSize, int k) {
    int retVal = 0;

    PriorityQueue *pMinHeap = createPriorityQueue(less);
    struct Element e;
    for (int i = 0; i < numsSize; i++) {
        e.data[0] = nums[i];
        enQueue(pMinHeap, &e);
    }

    long long x, y;
    while (front(pMinHeap)->data[0] < k) {
        x = front(pMinHeap)->data[0];
        deQueue(pMinHeap);
        y = front(pMinHeap)->data[0];
        deQueue(pMinHeap);
        e.data[0] = x + x + y;
        enQueue(pMinHeap, &e);

        retVal++;
    }

    //
    freeQueue(pMinHeap);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minOperations(vector<int>& nums, int k) {
        int retVal = 0;

        priority_queue<long, vector<long>, greater<long>> minHeap(nums.begin(), nums.end());
        while (minHeap.top() < k) {
            long x = minHeap.top();
            minHeap.pop();
            long y = minHeap.top();
            minHeap.pop();
            minHeap.push(min(x, y) * 2 + max(x, y));

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
    def minOperations(self, nums: List[int], k: int) -> int:
        retVal = 0

        heapify(nums)
        while nums[0] < k:
            x = heappop(nums)
            y = heappop(nums)
            heappush(nums, min(x, y) * 2 + max(x, y))
            retVal += 1

        return retVal
```

</details>

## [3264. Final Array State After K Multiplication Operations I](https://leetcode.com/problems/final-array-state-after-k-multiplication-operations-i/)  1177

- [Official](https://leetcode.com/problems/final-array-state-after-k-multiplication-operations-i/editorial/)
- [Official](https://leetcode.cn/problems/final-array-state-after-k-multiplication-operations-i/solutions/3014792/k-ci-cheng-yun-suan-hou-de-zui-zhong-shu-8i7p/)

<details><summary>Description</summary>

```text
You are given an integer array nums, an integer k, and an integer multiplier.

You need to perform k operations on nums. In each operation:
- Find the minimum value x in nums.
  If there are multiple occurrences of the minimum value, select the one that appears first.
- Replace the selected minimum value x with x * multiplier.

Return an integer array denoting the final state of nums after performing all k operations.

Example 1:
Input: nums = [2,1,3,5,6], k = 5, multiplier = 2
Output: [8,4,6,5,6]
Explanation:
Operation Result
After operation 1 [2, 2, 3, 5, 6]
After operation 2 [4, 2, 3, 5, 6]
After operation 3 [4, 4, 3, 5, 6]
After operation 4 [4, 4, 6, 5, 6]
After operation 5 [8, 4, 6, 5, 6]

Example 2:
Input: nums = [1,2], k = 3, multiplier = 4
Output: [16,8]
Explanation:
Operation Result
After operation 1 [4, 2]
After operation 2 [4, 8]
After operation 3 [16, 8]

Constraints:
1 <= nums.length <= 100
1 <= nums[i] <= 100
1 <= k <= 10
1 <= multiplier <= 5
```

<details><summary>Hint</summary>

```text
1. Maintain sorted pairs (nums[index], index) in a priority queue.
2. Simulate the operation k times.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getFinalState(int* nums, int numsSize, int k, int multiplier, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int*)malloc(numsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (numsSize * sizeof(int)));
    memcpy(pRetVal, nums, (numsSize * sizeof(int)));
    (*returnSize) = numsSize;

    int minIndex;
    while (k--) {
        minIndex = 0;
        for (int i = 0; i < numsSize; ++i) {
            if (pRetVal[i] < pRetVal[minIndex]) {
                minIndex = i;
            }
        }
        pRetVal[minIndex] *= multiplier;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {
        vector<int> retVal;

        retVal.assign(nums.begin(), nums.end());

        auto cmp = [](pair<int, int>& pair1, pair<int, int>& pair2) {
            if (pair1.first != pair2.first) {
                return pair1.first > pair2.first;
            }
            return pair1.second > pair2.second;
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> minHeap(cmp);
        int numsSize = retVal.size();
        for (int i = 0; i < numsSize; ++i) {
            minHeap.push(make_pair(retVal[i], i));
        }

        for (int i = 0; i < k; ++i) {
            pair<int, int> element = minHeap.top();
            minHeap.pop();
            int idx = element.second;
            retVal[idx] *= multiplier;
            minHeap.push(make_pair(retVal[idx], idx));
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def getFinalState(self, nums: List[int], k: int, multiplier: int) -> List[int]:
        retVal = nums

        minHeap = []
        for idx, num in enumerate(retVal):
            minHeap.append((num, idx))
        heapify(minHeap)

        for _ in range(k):
            num, idx = heappop(minHeap)
            retVal[idx] *= multiplier
            heappush(minHeap, (retVal[idx], idx))

        return retVal
```

</details>

## [3362. Zero Array Transformation III](https://leetcode.com/problems/zero-array-transformation-iii/)  2423

- [Official](https://leetcode.com/problems/zero-array-transformation-iii/editorial/)
- [Official](https://leetcode.cn/problems/zero-array-transformation-iii/solutions/3674726/ling-shu-zu-bian-huan-iii-by-leetcode-so-ptvl/)

<details><summary>Description</summary>

```text
You are given an integer array nums of length n and a 2D array queries where queries[i] = [li, ri].

Each queries[i] represents the following action on nums:
- Decrement the value at each index in the range [li, ri] in nums by at most 1.
- The amount by which the value is decremented can be chosen independently for each index.

A Zero Array is an array with all its elements equal to 0.

Return the maximum number of elements that can be removed from queries,
such that nums can still be converted to a zero array using the remaining queries.
If it is not possible to convert nums to a zero array, return -1.

Example 1:
Input: nums = [2,0,2], queries = [[0,2],[0,2],[1,1]]
Output: 1
Explanation:
After removing queries[2], nums can still be converted to a zero array.
Using queries[0], decrement nums[0] and nums[2] by 1 and nums[1] by 0.
Using queries[1], decrement nums[0] and nums[2] by 1 and nums[1] by 0.

Example 2:
Input: nums = [1,1,1,1], queries = [[1,3],[0,2],[1,3],[1,2]]
Output: 2
Explanation:
We can remove queries[2] and queries[3].

Example 3:
Input: nums = [1,2,3,4], queries = [[0,3]]
Output: -1
Explanation:
nums cannot be converted to a zero array even after using all the queries.

Constraints:
1 <= nums.length <= 10^5
0 <= nums[i] <= 10^5
1 <= queries.length <= 10^5
queries[i].length == 2
0 <= li <= ri < nums.length
```

<details><summary>Hint</summary>

```text
1, Sort the queries.
2. We need to greedily pick the queries with farthest ending point first.
```

</details>

</details>

<details><summary>C</summary>

```c
#ifndef HEAP_H
#define HEAP_H

#define MIN_QUEUE_SIZE (64)

typedef struct Element {
    int data;
} Element;
typedef bool (*compare)(const void *, const void *);
typedef struct PriorityQueue {
    Element *arr;
    int capacity;
    int queueSize;
    compare lessFunc;
} PriorityQueue;

#if (0)
static bool less(const void *a, const void *b) {
    bool retVal = false;

    Element *e1 = (Element *)a;
    Element *e2 = (Element *)b;
    retVal = (e1->data > e2->data);

    return retVal;
}
#endif
static bool greater(const void *a, const void *b) {
    bool retVal = false;

    Element *e1 = (Element *)a;
    Element *e2 = (Element *)b;
    retVal = (e1->data < e2->data);

    return retVal;
}
static void memswap(void *m1, void *m2, size_t size) {
    int tmp;
    unsigned char *a = (unsigned char *)m1;
    unsigned char *b = (unsigned char *)m2;
    while (size--) {
        tmp = *a;
        *a = *b;
        *b = tmp;

        a++;
        b++;
    }
}
static void swap(Element *arr, int i, int j) {
    //
    memswap(&arr[i], &arr[j], sizeof(Element));
}
static void down(Element *arr, int size, int i, compare cmpFunc) {
    for (int k = 2 * i + 1; k < size; k = 2 * k + 1) {
        if ((k + 1 < size) && (cmpFunc(&arr[k], &arr[k + 1]))) {
            k++;
        }

        if (cmpFunc(&arr[k], &arr[(k - 1) / 2])) {
            break;
        }

        swap(arr, k, (k - 1) / 2);
    }
}
PriorityQueue *createPriorityQueue(compare cmpFunc) {
    PriorityQueue *pObj = NULL;

    pObj = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->capacity = MIN_QUEUE_SIZE;
    pObj->arr = (Element *)malloc(sizeof(Element) * pObj->capacity);
    if (pObj->arr == NULL) {
        perror("malloc");
        free(pObj);
        pObj = NULL;
        return pObj;
    }
    pObj->queueSize = 0;
    pObj->lessFunc = cmpFunc;

    return pObj;
}
void heapfiy(PriorityQueue *obj) {
    for (int i = obj->queueSize / 2 - 1; i >= 0; i--) {
        down(obj->arr, obj->queueSize, i, obj->lessFunc);
    }
}
void enQueue(PriorityQueue *obj, Element *e) {
    // we need to alloc more space, just twice space size
    if (obj->queueSize == obj->capacity) {
        obj->capacity *= 2;
        obj->arr = realloc(obj->arr, sizeof(Element) * obj->capacity);
    }
    memcpy(&obj->arr[obj->queueSize], e, sizeof(Element));

    for (int i = obj->queueSize; i > 0 && obj->lessFunc(&obj->arr[(i - 1) / 2], &obj->arr[i]); i = (i - 1) / 2) {
        swap(obj->arr, i, (i - 1) / 2);
    }
    obj->queueSize++;
}
Element *deQueue(PriorityQueue *obj) {
    Element *pRetVal = NULL;

    swap(obj->arr, 0, obj->queueSize - 1);
    down(obj->arr, obj->queueSize - 1, 0, obj->lessFunc);
    pRetVal = &obj->arr[obj->queueSize - 1];
    obj->queueSize--;

    return pRetVal;
}
bool isEmpty(const PriorityQueue *obj) {
    bool retVal = false;

    retVal = (obj->queueSize == 0);

    return retVal;
}
Element *front(const PriorityQueue *obj) {
    Element *pRetVal = NULL;

    if (obj->queueSize != 0) {
        pRetVal = &obj->arr[0];
    }

    return pRetVal;
}
void clear(PriorityQueue *obj) {
    //
    obj->queueSize = 0;
}
int size(const PriorityQueue *obj) {
    int retVal = obj->queueSize;

    //
    return retVal;
}
void freeQueue(PriorityQueue *obj) {
    free(obj->arr);
    obj->arr = NULL;
    free(obj);
    obj = NULL;
}

#endif  // HEAP_H
int compareIntArray(const void *a, const void *b) {
    int *p1 = *(int **)a;
    int *p2 = *(int **)b;

    // ascending order
    return (p1[0] > p2[0]);
}
int maxRemoval(int *nums, int numsSize, int **queries, int queriesSize, int *queriesColSize) {
    int retVal = -1;

    qsort(queries, queriesSize, sizeof(int *), compareIntArray);

    PriorityQueue *heap = createPriorityQueue(greater);

    int deltaArray[numsSize + 1];
    memset(deltaArray, 0, sizeof(deltaArray));
    int operations = 0;

    Element e;
    int end;
    int j = 0;
    for (int i = 0; i < numsSize; i++) {
        operations += deltaArray[i];

        while ((j < queriesSize) && (queries[j][0] == i)) {
            e = (Element){queries[j][1]};
            enQueue(heap, &e);
            j++;
        }

        while ((operations < nums[i]) && (isEmpty(heap) == false) && (front(heap)->data >= i)) {
            operations += 1;
            end = front(heap)->data;
            deQueue(heap);
            deltaArray[end + 1] -= 1;
        }

        if (operations < nums[i]) {
            freeQueue(heap);
            return retVal;
        }
    }
    retVal = size(heap);

    //
    freeQueue(heap);
    heap = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxRemoval(vector<int>& nums, vector<vector<int>>& queries) {
        int retVal = -1;

        int queriesSize = queries.size();
        sort(queries.begin(), queries.end(), [](const vector<int>& a, const vector<int>& b) {
            // ascending order
            return a[0] < b[0];
        });

        priority_queue<int> heap;

        int numsSize = nums.size();
        vector<int> deltaArray(numsSize + 1, 0);
        int operations = 0;
        for (int i = 0, j = 0; i < numsSize; ++i) {
            operations += deltaArray[i];

            while ((j < queriesSize) && (queries[j][0] == i)) {
                heap.push(queries[j][1]);
                ++j;
            }

            while ((operations < nums[i]) && (heap.empty() == false) && (heap.top() >= i)) {
                operations += 1;
                deltaArray[heap.top() + 1] -= 1;
                heap.pop();
            }

            if (operations < nums[i]) {
                return retVal;
            }
        }
        retVal = heap.size();

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxRemoval(self, nums: List[int], queries: List[List[int]]) -> int:
        retVal = -1

        queries.sort(key=lambda x: x[0])
        queriesSize = len(queries)

        heap = []

        numsSize = len(nums)
        deltaArray = [0] * (numsSize + 1)
        operations = 0

        j = 0
        for i, num in enumerate(nums):
            operations += deltaArray[i]

            while (j < queriesSize) and (queries[j][0] == i):
                heappush(heap, -queries[j][1])
                j += 1

            while (operations < num) and heap and (-heap[0] >= i):
                operations += 1
                deltaArray[-heappop(heap) + 1] -= 1

            if operations < num:
                return retVal

        retVal = len(heap)

        return retVal
```

</details>
