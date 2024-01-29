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
#define SORT_LINK_LIST      (0)     // Time Limit Exceeded
#define SORT_ARRAY          (1)     // Time Limit Exceeded

#if (SORT_LINK_LIST)
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
void display(struct ListNode* pHead) {
    struct ListNode* pCurrent = pHead;
    while (pCurrent != NULL) {
        printf("%d%s", pCurrent->val, (pCurrent->next==NULL)?"":",");
        pCurrent = pCurrent->next;
    }
    printf("\n");
}
struct ListNode* createNode(int value) {
    struct ListNode* pNew = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (pNew == NULL) {
        perror("malloc");
        return pNew;
    }
    pNew->val = value;
    pNew->next = NULL;

    return pNew;
}
void freeNode(struct ListNode* pHead) {
    struct ListNode* pCurrent = pHead;
    struct ListNode* pFree = NULL;
    while (pCurrent != NULL) {
        pFree = pCurrent;
        pCurrent = pCurrent->next;
        free(pFree);
    }
}
struct ListNode* addValueToMiddle(struct ListNode* pHead, int value) {
    struct ListNode* pNew = createNode(value);
    if (pNew == NULL) {
        return pHead;
    }

    if (pHead == NULL) {
        pHead = pNew;
        return pHead;
    }

    struct ListNode* pPrevious = NULL;
    struct ListNode* pCurrent = pHead;
    while (pCurrent != NULL) {
        // from small to large
        if (pCurrent->val > value) {
            break;
        }
        pPrevious = pCurrent;
        pCurrent = pCurrent->next;
    }
    if (pPrevious == NULL) {
        pNew->next = pHead;
        pHead = pNew;
        return pHead;
    }
    pNew->next = pPrevious->next;
    pPrevious->next = pNew;

    return pHead;
}
#elif (SORT_ARRAY)
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
#endif

typedef struct {
    int count;
#if (SORT_LINK_LIST)
    struct ListNode* pNums;
#elif (SORT_ARRAY)
    int pNums[5*10000];
#endif
} MedianFinder;
MedianFinder* medianFinderCreate() {
    MedianFinder* pNew = (MedianFinder*)malloc(sizeof(MedianFinder));
    if (pNew == NULL) {
        perror("malloc");
        return pNew;
    }
    pNew->count = 0;
#if (SORT_LINK_LIST)
    pNew->pNums = NULL;
#elif (SORT_ARRAY)
    int i;
    for (i=0; i<(5*10000); ++i) {
        pNew->pNums[i] = 0;
    }
#endif

    return pNew;
}
void medianFinderAddNum(MedianFinder* obj, int num) {
    obj->count += 1;
#if (SORT_LINK_LIST)
    obj->pNums = addValueToMiddle(obj->pNums, num);
    display(obj->pNums);
#elif (SORT_ARRAY)
    obj->pNums[obj->count-1] = num;
    qsort(obj->pNums, obj->count, sizeof(int), compareInteger);
#endif
}
double medianFinderFindMedian(MedianFinder* obj) {
    double retVal = 0;

    if (obj->count == 0) {
        return retVal;
    }

#if (SORT_LINK_LIST)
    struct ListNode* pCurrent = obj->pNums;
    int i;
#elif (SORT_ARRAY)
#endif
    if (obj->count%2 == 0) {
#if (SORT_LINK_LIST)
        for (i=0; i<obj->count/2-1; ++i) {
            pCurrent = pCurrent->next;
        }
        retVal = pCurrent->val + pCurrent->next->val;
#elif (SORT_ARRAY)
        retVal = obj->pNums[obj->count/2] + obj->pNums[(obj->count/2-1)];
#endif
        retVal /= 2;
    }
    else if (obj->count%2 == 1) {
#if (SORT_LINK_LIST)
        for (i=0; i<obj->count/2; ++i) {
            pCurrent = pCurrent->next;
        }
        retVal = pCurrent->val;
#elif (SORT_ARRAY)
        retVal = obj->pNums[obj->count/2];
#endif
    }

    return retVal;
}
void medianFinderFree(MedianFinder* obj) {
#if (SORT_LINK_LIST)
    freeNode(obj->pNums);
    obj->pNums = NULL;
#elif (SORT_ARRAY)
#endif
    free(obj);
    obj = NULL;
}

/**
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

    MedianFinder() {

    }

    void addNum(int num) {
        maxHeap.push(num);
        minHeap.push(maxHeap.top());
        maxHeap.pop();
        if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

    double findMedian() {
        if (maxHeap.size() > minHeap.size()) return maxHeap.top();
        return (maxHeap.top() + minHeap.top()) / 2.0;
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
from sortedcontainers import SortedList

class MedianFinder:
    def __init__(self):
        # 1: MaxHeap and MinHeap
        # 2: SortedList
        self.method = 1

        if self.method == 1:
            print("MaxHeap and MinHeap")
            self.minHeap = []
            self.maxHeap = []
        elif self.method == 2:
            print("SortedList")
            self.arr = SortedList()

    def addNum(self, num: int) -> None:
        if self.method == 1:
            heappush(self.maxHeap, -num)
            heappush(self.minHeap, -heappop(self.maxHeap))
            if len(self.minHeap) > len(self.maxHeap):
                heappush(self.maxHeap, -heappop(self.minHeap))
        elif self.method == 2:
            self.arr.add(num)

    def findMedian(self) -> float:
        if self.method == 1:
            if len(self.maxHeap) > len(self.minHeap):
                return -self.maxHeap[0]
            return (-self.maxHeap[0] + self.minHeap[0]) / 2
        elif self.method == 2:
            n = len(self.arr)
            if n % 2 == 1:
                return self.arr[n//2]
            return (self.arr[n//2] + self.arr[n//2-1]) / 2

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

- [Official](https://leetcode.com/problems/ipo/solutions/2959870/ipo/)
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
int findMaximizedCapital(int k, int w, int* profits, int profitsSize, int* capital, int capitalSize) {

}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        int retVal = w;

        int n = profits.size();

        vector<pair<int, int>> projects;
        for (int i = 0; i < n; ++i) {
            projects.emplace_back(capital[i], profits[i]);
        }
        sort(projects.begin(), projects.end());

        priority_queue<int> priorityQueue;
        int ptr = 0;
        for (int i = 0; i < k; ++i) {
            while ((ptr < n) && (projects[ptr].first <= retVal)) {
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

## [1353. Maximum Number of Events That Can Be Attended](https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/)  2015

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
// https://leetcode.cn/problems/maximum-number-of-events-that-can-be-attended/solutions/732656/1353-zui-duo-ke-yi-can-jia-de-hui-yi-shu-zrks/
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
    // https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/solutions/510263/java-c-python-priority-queue/
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
    # https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/solutions/510263/java-c-python-priority-queue/
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

## [1845. Seat Reservation Manager](https://leetcode.com/problems/seat-reservation-manager/description/)  1428

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
