# Design

- [Binary Search](https://en.wikipedia.org/wiki/Binary_search_algorithm)
  - [729. My Calendar I](https://leetcode.com/problems/my-calendar-i/)
  - [731. My Calendar II](https://leetcode.com/problems/my-calendar-ii/)
- [Graph](https://en.wikipedia.org/wiki/Graph_(discrete_mathematics))
  - [2642. Design Graph With Shortest Path Calculator](https://leetcode.com/problems/design-graph-with-shortest-path-calculator/)
- [Hash Table](https://en.wikipedia.org/wiki/Hash_table)
  - [380. Insert Delete GetRandom O(1)](https://leetcode.com/problems/insert-delete-getrandom-o1/)
  - [705. Design HashSet](https://leetcode.com/problems/design-hashset/)
  - [706. Design HashMap](https://leetcode.com/problems/design-hashmap/)
  - [1396. Design Underground System](https://leetcode.com/problems/design-underground-system/)
  - [1865. Finding Pairs With a Certain Sum](https://leetcode.com/problems/finding-pairs-with-a-certain-sum/)
  - [1912. Design Movie Rental System](https://leetcode.com/problems/design-movie-rental-system/)
  - [2349. Design a Number Container System](https://leetcode.com/problems/design-a-number-container-system/)
  - [2353. Design a Food Rating System](https://leetcode.com/problems/design-a-food-rating-system/)
  - [3408. Design Task Manager](https://leetcode.com/problems/design-task-manager/)
  - [3484. Design Spreadsheet](https://leetcode.com/problems/design-spreadsheet/)
- [Linked List](https://en.wikipedia.org/wiki/Linked_list)
  - [382. Linked List Random Node](https://leetcode.com/problems/linked-list-random-node/)
  - [432. All O`one Data Structure](https://leetcode.com/problems/all-oone-data-structure/)
  - [707. Design Linked List](https://leetcode.com/problems/design-linked-list/)
- [Prefix Sum](https://en.wikipedia.org/wiki/Prefix_sum)
  - [303. Range Sum Query - Immutable](https://leetcode.com/problems/range-sum-query-immutable/)
  - [304. Range Sum Query 2D - Immutable](https://leetcode.com/problems/range-sum-query-2d-immutable/)
  - [1352. Product of the Last K Numbers](https://leetcode.com/problems/product-of-the-last-k-numbers/)
- [Queue](https://en.wikipedia.org/wiki/Queue_(abstract_data_type))
  - [232. Implement Queue using Stacks](https://leetcode.com/problems/implement-queue-using-stacks/)
  - [295. Find Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/)
  - [622. Design Circular Queue](https://leetcode.com/problems/design-circular-queue/)
  - [641. Design Circular Deque](https://leetcode.com/problems/design-circular-deque/)
  - [703. Kth Largest Element in a Stream](https://leetcode.com/problems/kth-largest-element-in-a-stream/)
  - [933. Number of Recent Calls](https://leetcode.com/problems/number-of-recent-calls/)
  - [1845. Seat Reservation Manager](https://leetcode.com/problems/seat-reservation-manager/)
  - [2336. Smallest Number in Infinite Set](https://leetcode.com/problems/smallest-number-in-infinite-set/)
- [Stack](https://en.wikipedia.org/wiki/Stack_(abstract_data_type))
  - [155. Min Stack](https://leetcode.com/problems/min-stack/)
  - [225. Implement Stack using Queues](https://leetcode.com/problems/implement-stack-using-queues/)
  - [341. Flatten Nested List Iterator](https://leetcode.com/problems/flatten-nested-list-iterator/)
  - [901. Online Stock Span](https://leetcode.com/problems/online-stock-span/)
  - [1381. Design a Stack With Increment Operation](https://leetcode.com/problems/design-a-stack-with-increment-operation/)
- [Tree](https://en.wikipedia.org/wiki/Tree_(data_structure))
  - [173. Binary Search Tree Iterator](https://leetcode.com/problems/binary-search-tree-iterator/)
  - [297. Serialize and Deserialize Binary Tree](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/)
  - [449. Serialize and Deserialize BST](https://leetcode.com/problems/serialize-and-deserialize-bst/)
  - [1261. Find Elements in a Contaminated Binary Tree](https://leetcode.com/problems/find-elements-in-a-contaminated-binary-tree/)
- [Trie](https://en.wikipedia.org/wiki/Trie)
  - [208. Implement Trie (Prefix Tree)](https://leetcode.com/problems/implement-trie-prefix-tree/)
  - [211. Design Add and Search Words Data Structure](https://leetcode.com/problems/design-add-and-search-words-data-structure/)

## [146. LRU Cache](https://leetcode.com/problems/lru-cache/)

- [Official](https://leetcode.cn/problems/lru-cache/solutions/259678/lruhuan-cun-ji-zhi-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:
- LRUCache(int capacity)
  Initialize the LRU cache with positive size capacity.
- int get(int key)
  Return the value of the key if the key exists, otherwise return -1.
- void put(int key, int value)
  Update the value of the key if the key exists.
  Otherwise, add the key-value pair to the cache.
  If the number of keys exceeds the capacity from this operation, evict the least recently used key.

The functions get and put must each run in O(1) average time complexity.

Example 1:
Input
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, null, -1, 3, 4]
Explanation
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // cache is {1=1}
lRUCache.put(2, 2); // cache is {1=1, 2=2}
lRUCache.get(1);    // return 1
lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);    // returns -1 (not found)
lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);    // return -1 (not found)
lRUCache.get(3);    // return 3
lRUCache.get(4);    // return 4

Constraints:
1 <= capacity <= 3000
0 <= key <= 10^4
0 <= value <= 10^5
At most 2 * 10^5 calls will be made to get and put.
```

</details>

<details><summary>C</summary>

```c
// https://leetcode.cn/problems/lru-cache/solutions/727484/c-uthash-uthashdi-ceng-shi-xian-de-shu-j-wbpw/
typedef struct {
    int key;
    int value;
    UT_hash_handle hh;
} LRUCache;

LRUCache* globalCache = NULL;
int globalCapacity;

LRUCache* lRUCacheCreate(int capacity) {
    globalCapacity = capacity;

    return globalCache;
}
int lRUCacheGet(LRUCache* obj, int key) {
    int retVal = -1;

    LRUCache* pTemp = NULL;
    HASH_FIND_INT(globalCache, &key, pTemp);
    if (pTemp == NULL) {
        return retVal;
    }
    HASH_DEL(globalCache, pTemp);
    HASH_ADD_INT(globalCache, key, pTemp);
    retVal = pTemp->value;

    return retVal;
}
void lRUCachePut(LRUCache* obj, int key, int value) {
    LRUCache* pCurrent = NULL;
    LRUCache* pNext = NULL;

    HASH_FIND_INT(globalCache, &key, pCurrent);
    if (pCurrent != NULL) {
        HASH_DEL(globalCache, pCurrent);
        pCurrent->key = key;
        pCurrent->value = value;
        HASH_ADD_INT(globalCache, key, pCurrent);
        return;
    }

    int globalCacheSize = HASH_COUNT(globalCache);
    if (globalCacheSize == globalCapacity) {
        HASH_ITER(hh, globalCache, pCurrent, pNext) {
            HASH_DEL(globalCache, pCurrent);
            free(pCurrent);
            break;
        }
    }
    LRUCache* pNew = (LRUCache*)malloc(sizeof(LRUCache));
    if (pNew == NULL) {
        perror("malloc");
        return;
    }
    pNew->key = key;
    pNew->value = value;
    HASH_ADD_INT(globalCache, key, pNew);
}
void lRUCacheFree(LRUCache* obj) {
    LRUCache* pCurrent = NULL;
    LRUCache* pNext = NULL;
    HASH_ITER(hh, globalCache, pCurrent, pNext) {
        // printf("%d: %d\n", globalCache->key, globalCache->value);
        HASH_DEL(globalCache, pCurrent);
        free(pCurrent);
    }
}
/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 * lRUCachePut(obj, key, value);
 * lRUCacheFree(obj);
 */
```

</details>

<details><summary>C++</summary>

```c++
struct DoublyLinkedNode {
    int key;
    int value;
    DoublyLinkedNode* prev;
    DoublyLinkedNode* next;
    DoublyLinkedNode() : key(0), value(0), prev(nullptr), next(nullptr) {}
    DoublyLinkedNode(int _key, int _value) : key(_key), value(_value), prev(nullptr), next(nullptr) {}
};
class LRUCache {
   private:
    int capacity;
    unordered_map<int, DoublyLinkedNode*> cache;
    int size;

    DoublyLinkedNode* head;
    DoublyLinkedNode* tail;

   public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        this->size = 0;

        head = new DoublyLinkedNode();
        tail = new DoublyLinkedNode();
        head->next = tail;
        tail->prev = head;
    }
    ~LRUCache() {
        DoublyLinkedNode* node = head;
        while (node != tail) {
            DoublyLinkedNode* current = node;
            node = node->next;
            delete current;
        }
        delete node;
    }
    void addToHead(DoublyLinkedNode* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }
    void removeNode(DoublyLinkedNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    void moveToHead(DoublyLinkedNode* node) {
        removeNode(node);
        addToHead(node);
    }
    DoublyLinkedNode* removeTail() {
        DoublyLinkedNode* node = tail->prev;
        removeNode(node);
        return node;
    }
    int get(int key) {
        int retVal = -1;

        if (cache.count(key) == 0) {
            return retVal;
        }

        DoublyLinkedNode* node = cache[key];
        moveToHead(node);
        retVal = node->value;

        return retVal;
    }
    void put(int key, int value) {
        if (cache.count(key) == 0) {
            DoublyLinkedNode* node = new DoublyLinkedNode(key, value);
            cache[key] = node;
            addToHead(node);
            ++size;
            if (size > capacity) {
                DoublyLinkedNode* removed = removeTail();
                cache.erase(removed->key);
                delete removed;
                --size;
            }
        } else {
            DoublyLinkedNode* node = cache[key];
            node->value = value;
            moveToHead(node);
        }
    }
};
/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
```

</details>

<details><summary>Python3</summary>

```python
class DoublyLinkedNode:
    def __init__(self, key=0, value=0):
        self.key = key
        self.value = value
        self.prev = None
        self.next = None


class LRUCache:
    def __init__(self, capacity: int):
        self.capacity = capacity
        self.cache = defaultdict()
        self.size = 0

        self.head = DoublyLinkedNode()
        self.tail = DoublyLinkedNode()
        self.head.next = self.tail
        self.tail.prev = self.head

    def addToHead(self, node):
        node.prev = self.head
        node.next = self.head.next
        self.head.next.prev = node
        self.head.next = node

    def removeNode(self, node):
        node.prev.next = node.next
        node.next.prev = node.prev

    def moveToHead(self, node):
        self.removeNode(node)
        self.addToHead(node)

    def removeTail(self):
        node = self.tail.prev
        self.removeNode(node)
        return node

    def get(self, key: int) -> int:
        retVal = -1

        if key not in self.cache:
            return retVal

        node = self.cache[key]
        self.moveToHead(node)
        retVal = node.value

        return retVal

    def put(self, key: int, value: int) -> None:
        if key not in self.cache:
            node = DoublyLinkedNode(key, value)
            self.cache[key] = node
            self.addToHead(node)
            self.size += 1
            if self.size > self.capacity:
                removed = self.removeTail()
                self.cache.pop(removed.key)
                self.size -= 1
        else:
            node = self.cache[key]
            node.value = value
            self.moveToHead(node)

# Your LRUCache object will be instantiated and called as such:
# obj = LRUCache(capacity)
# param_1 = obj.get(key)
# obj.put(key,value)
```

</details>

## [352. Data Stream as Disjoint Intervals](https://leetcode.com/problems/data-stream-as-disjoint-intervals/)

- [Official](https://leetcode.com/problems/data-stream-as-disjoint-intervals/solutions/2866931/data-stream-as-disjoint-intervals/)
- [Official](https://leetcode.cn/problems/data-stream-as-disjoint-intervals/solutions/1037200/jiang-shu-ju-liu-bian-wei-duo-ge-bu-xian-hm1r/)

<details><summary>Description</summary>

```text
Given a data stream input of non-negative integers a1, a2, ..., an,
summarize the numbers seen so far as a list of disjoint intervals.

Implement the SummaryRanges class:
- SummaryRanges()
    Initializes the object with an empty stream.
- void addNum(int value)
    Adds the integer value to the stream.
- int[][] getIntervals()
    Returns a summary of the integers in the stream currently as a list of disjoint intervals [starti, endi].
    The answer should be sorted by starti.

Example 1:
Input
["SummaryRanges", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals",
"addNum", "getIntervals", "addNum", "getIntervals"]
[[], [1], [], [3], [], [7], [], [2], [], [6], []]
Output
[null, null, [[1, 1]], null, [[1, 1], [3, 3]], null, [[1, 1], [3, 3], [7, 7]],
null, [[1, 3], [7, 7]], null, [[1, 3], [6, 7]]]
Explanation
SummaryRanges summaryRanges = new SummaryRanges();
summaryRanges.addNum(1);      // arr = [1]
summaryRanges.getIntervals(); // return [[1, 1]]
summaryRanges.addNum(3);      // arr = [1, 3]
summaryRanges.getIntervals(); // return [[1, 1], [3, 3]]
summaryRanges.addNum(7);      // arr = [1, 3, 7]
summaryRanges.getIntervals(); // return [[1, 1], [3, 3], [7, 7]]
summaryRanges.addNum(2);      // arr = [1, 2, 3, 7]
summaryRanges.getIntervals(); // return [[1, 3], [7, 7]]
summaryRanges.addNum(6);      // arr = [1, 2, 3, 6, 7]
summaryRanges.getIntervals(); // return [[1, 3], [6, 7]]

Constraints:
0 <= value <= 10^4
At most 3 * 10^4 calls will be made to addNum and getIntervals.
```

</details>

<details><summary>C</summary>

```c
// https://leetcode.cn/problems/data-stream-as-disjoint-intervals/solutions/815374/shuang-xiang-lian-biao-by-chun-geng-0umq/
typedef struct SummaryRanges {
    int left;
    int right;
    struct SummaryRanges *pre;
    struct SummaryRanges *next;
} SummaryRanges;
SummaryRanges *summaryRangesCreate() {
    SummaryRanges *pRetVal = NULL;

    pRetVal = (SummaryRanges *)malloc(sizeof(SummaryRanges));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    SummaryRanges *pRear = (SummaryRanges *)malloc(sizeof(SummaryRanges));
    if (pRear == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }

    pRetVal->next = pRear;
    pRetVal->pre = pRear;
    pRetVal->left = 0;
    pRear->next = pRetVal;
    pRear->pre = pRetVal;

    return pRetVal;
}
SummaryRanges *insert(SummaryRanges *head, SummaryRanges *rear, int val) {
    SummaryRanges *pRetVal = NULL;

    SummaryRanges *pCurrent = head->next;
    while (pCurrent != rear) {
        if ((pCurrent->left <= val) && (val <= pCurrent->right)) {
            return pRetVal;
        } else if (pCurrent->right < val) {
            pCurrent = pCurrent->next;
        } else {
            break;
        }
    }

    pRetVal = (SummaryRanges *)malloc(sizeof(SummaryRanges));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->left = val;
    pRetVal->right = val;
    pRetVal->next = pCurrent;
    pRetVal->pre = pCurrent->pre;
    pCurrent->pre->next = pRetVal;
    pCurrent->pre = pRetVal;
    ++(head->left);

    return pRetVal;
}
void summaryRangesAddNum(SummaryRanges *obj, int val) {
    SummaryRanges *pHead = obj;
    SummaryRanges *pRear = obj->pre;

    SummaryRanges *p = insert(pHead, pRear, val);
    if (p == NULL) {
        return;
    }

    int f1 = ((p->pre != pHead) && (p->pre->right + 1 == p->left));
    int f2 = ((p->next != pRear) && (p->next->left - 1 == p->right));
    if (f1 && f2) {
        p->pre->right = p->next->right;
        p->pre->next = p->next->next;
        p->next->next->pre = p->pre;
        pHead->left -= 2;

        free(p->next);
        free(p);
    } else if (f1) {
        p->pre->right = p->right;
        p->pre->next = p->next;
        p->next->pre = p->pre;
        (pHead->left)--;
        free(p);
    } else if (f2) {
        p->next->left = p->left;
        p->next->pre = p->pre;
        p->pre->next = p->next;
        (pHead->left)--;
        free(p);
    }
}
int **summaryRangesGetIntervals(SummaryRanges *obj, int *retSize, int **retColSize) {
    int **pRetVal = NULL;

    (*retSize) = 0;

    SummaryRanges *pCurrent = obj->next;
    SummaryRanges *pRear = obj->pre;

    pRetVal = (int **)malloc((obj->left) * sizeof(int *));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int i;
    while (pCurrent != pRear) {
        pRetVal[(*retSize)] = (int *)malloc(2 * sizeof(int));
        if (pRetVal[(*retSize)] == NULL) {
            perror("malloc");
            for (i = 0; i < (*retSize); ++i) {
                free(pRetVal[i]);
                pRetVal[i] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            (*retSize) = 0;
            return pRetVal;
        }
        pRetVal[(*retSize)][0] = pCurrent->left;
        pRetVal[(*retSize)][1] = pCurrent->right;
        (*retSize)++;

        pCurrent = pCurrent->next;
    }

    (*retColSize) = (int *)malloc((*retSize) * sizeof(int));
    if ((*retColSize) == NULL) {
        perror("malloc");
        for (i = 0; i < (*retSize); ++i) {
            free(pRetVal[i]);
            pRetVal[i] = NULL;
        }
        free(pRetVal);
        pRetVal = NULL;
        (*retSize) = 0;
        return pRetVal;
    }
    for (i = 0; i < (*retSize); ++i) {
        (*retColSize)[i] = 2;
    }

    return pRetVal;
}
void summaryRangesFree(SummaryRanges *obj) {
    SummaryRanges *pCurrent = obj->next;
    SummaryRanges *pRear = obj->pre;
    SummaryRanges *pTemp = NULL;
    while (pCurrent != pRear) {
        pTemp = pCurrent->next;
        free(pCurrent);
        pCurrent = pTemp;
    }
    free(pRear);
    free(obj);
}
/**
 * Your SummaryRanges struct will be instantiated and called as such:
 * SummaryRanges* obj = summaryRangesCreate();
 * summaryRangesAddNum(obj, value);
 * int** param_2 = summaryRangesGetIntervals(obj, retSize, retColSize);
 * summaryRangesFree(obj);
 */
```

</details>

<details><summary>C++</summary>

```c++
class SummaryRanges {
   private:
    map<int, int> intervals;

   public:
    SummaryRanges() {}
    void addNum(int value) {
        int left = value;
        int right = value;

        auto small_entry = intervals.upper_bound(value);
        if (small_entry != intervals.begin()) {
            auto max_entry = small_entry;
            --max_entry;
            if (max_entry->second >= value) {
                return;
            }

            if (max_entry->second == value - 1) {
                left = max_entry->first;
            }
        }
        if ((small_entry != intervals.end()) && (small_entry->first == value + 1)) {
            right = small_entry->second;
            intervals.erase(small_entry);
        }

        intervals[left] = right;
    }
    vector<vector<int>> getIntervals() {
        vector<vector<int>> retVal;

        for (const auto& p : intervals) {
            retVal.push_back({p.first, p.second});
        }

        return retVal;
    }
};
/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(value);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */
```

</details>

## [460. LFU Cache](https://leetcode.com/problems/lfu-cache/)

- [Official](https://leetcode.com/problems/lfu-cache/solutions/2815229/lfu-cache/?orderBy=most_votes)
- [Official](https://leetcode.cn/problems/lfu-cache/solutions/186348/lfuhuan-cun-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Design and implement a data structure for a Least Frequently Used (LFU) cache.

Implement the LFUCache class:
- LFUCache(int capacity)
  Initializes the object with the capacity of the data structure.
- int get(int key)
  Gets the value of the key if the key exists in the cache. Otherwise, returns -1.
- void put(int key, int value)
  Update the value of the key if present, or inserts the key if not already present.
  When the cache reaches its capacity,
  it should invalidate and remove the least frequently used key before inserting a new item.
  For this problem, when there is a tie (i.e., two or more keys with the same frequency),
  the least recently used key would be invalidated.

To determine the least frequently used key, a use counter is maintained for each key in the cache.
The key with the smallest use counter is the least frequently used key.

When a key is first inserted into the cache, its use counter is set to 1 (due to the put operation).
The use counter for a key in the cache is incremented either a get or put operation is called on it.

The functions get and put must each run in O(1) average time complexity.

Example 1:
Input
["LFUCache", "put", "put", "get", "put", "get", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [3], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, 3, null, -1, 3, 4]
Explanation
// cnt(x) = the use counter for key x
// cache=[] will show the last used order for tiebreakers (leftmost element is  most recent)
LFUCache lfu = new LFUCache(2);
lfu.put(1, 1);   // cache=[1,_], cnt(1)=1
lfu.put(2, 2);   // cache=[2,1], cnt(2)=1, cnt(1)=1
lfu.get(1);      // return 1
                 // cache=[1,2], cnt(2)=1, cnt(1)=2
lfu.put(3, 3);   // 2 is the LFU key because cnt(2)=1 is the smallest, invalidate 2.
                 // cache=[3,1], cnt(3)=1, cnt(1)=2
lfu.get(2);      // return -1 (not found)
lfu.get(3);      // return 3
                 // cache=[3,1], cnt(3)=2, cnt(1)=2
lfu.put(4, 4);   // Both 1 and 3 have the same cnt, but 1 is LRU, invalidate 1.
                 // cache=[4,3], cnt(4)=1, cnt(3)=2
lfu.get(1);      // return -1 (not found)
lfu.get(3);      // return 3
                 // cache=[3,4], cnt(4)=1, cnt(3)=3
lfu.get(4);      // return 4
                 // cache=[4,3], cnt(4)=2, cnt(3)=3

Constraints:
0 <= capacity <= 10^4
0 <= key <= 10^5
0 <= value <= 10^9
At most 2 * 10^5 calls will be made to get and put.
```

</details>

<details><summary>C</summary>

```c
// https://leetcode.cn/problems/lfu-cache/solutions/1810523/by-heng-deng-shi-2ojp/
#if 1
typedef struct ValueListNode_s {
    int key;
    int value;
    int counter;
    struct ValueListNode_s *prev;
    struct ValueListNode_s *next;
} ValueListNode;
typedef struct CounterListNode_s {
    ValueListNode *head;
    struct CounterListNode_s *prev;
    struct CounterListNode_s *next;
} CounterListNode;
#endif
typedef struct {
    int capacity;
    int currentCounter;
    ValueListNode **keyHash;
    CounterListNode **counterHash;
    CounterListNode *head;
} LFUCache;
#if 1
void removeValueNode(CounterListNode *counterNode, ValueListNode *valueNode) {
    if (valueNode->next == valueNode) {
        counterNode->head = NULL;
        return;
    }

    valueNode->prev->next = valueNode->next;
    valueNode->next->prev = valueNode->prev;
    if (counterNode->head == valueNode) {
        counterNode->head = valueNode->next;
    }
}
void insertValueNode(CounterListNode *counterNode, ValueListNode *valueNode) {
    ValueListNode *tail = NULL;

    if (NULL == counterNode->head) {
        valueNode->prev = valueNode;
        valueNode->next = valueNode;
    } else {
        tail = counterNode->head->prev;
        valueNode->prev = tail;
        valueNode->next = counterNode->head;
        counterNode->head->prev = valueNode;
        tail->next = valueNode;
    }

    counterNode->head = valueNode;
}
void removeCounterNode(LFUCache *obj, CounterListNode *counterNode) {
    if (obj->head == counterNode) {
        obj->head = counterNode->next;
        if (NULL != obj->head) {
            obj->head->prev = NULL;
        }

        return;
    }

    counterNode->prev->next = counterNode->next;
    if (NULL != counterNode->next) {
        counterNode->next->prev = counterNode->prev;
    }
}
void insertCounterNode(LFUCache *obj, CounterListNode *counterPrev, CounterListNode *counterNode) {
    if (NULL == counterPrev) {
        counterNode->prev = NULL;
        counterNode->next = obj->head;
        if (NULL != obj->head) {
            obj->head->prev = counterNode;
        }
        obj->head = counterNode;

        return;
    }

    counterNode->prev = counterPrev;
    counterNode->next = counterPrev->next;
    if (NULL != counterPrev->next) {
        counterPrev->next->prev = counterNode;
    }
    counterPrev->next = counterNode;
}
#endif
LFUCache *lFUCacheCreate(int capacity) {
    LFUCache *pRetVal = NULL;

    pRetVal = (LFUCache *)malloc(sizeof(LFUCache));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    pRetVal->capacity = capacity;

    pRetVal->currentCounter = 0;

    // 0 <= key <= 10^5
    pRetVal->keyHash = (ValueListNode **)calloc(100001, sizeof(ValueListNode *));
    if (pRetVal->keyHash == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }

    // At most 2 * 10 ^ 5 calls will be made to get and put.
    pRetVal->counterHash = (CounterListNode **)calloc(200001, sizeof(CounterListNode *));
    if (pRetVal->counterHash == NULL) {
        perror("malloc");
        free(pRetVal->keyHash);
        pRetVal->keyHash = NULL;
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }

    pRetVal->head = NULL;

    return pRetVal;
}
int lFUCacheGet(LFUCache *obj, int key) {
    int retVal = -1;

    CounterListNode *counterNode = NULL;
    CounterListNode *counterNew = NULL;
    ValueListNode *valueNode = obj->keyHash[key];
    if (NULL != valueNode) {
        retVal = valueNode->value;

        counterNode = obj->counterHash[valueNode->counter];

        valueNode->counter++;
        counterNew = obj->counterHash[valueNode->counter];

        removeValueNode(counterNode, valueNode);

        if (NULL == counterNew) {
            counterNew = (CounterListNode *)calloc(1, sizeof(CounterListNode));
            if (counterNew == NULL) {
                perror("malloc");
                retVal = -1;
                return retVal;
            }
            obj->counterHash[valueNode->counter] = counterNew;
            insertCounterNode(obj, counterNode, counterNew);
        }

        if (NULL == counterNode->head) {
            removeCounterNode(obj, counterNode);
            free(counterNode);
            obj->counterHash[valueNode->counter - 1] = NULL;
        }

        insertValueNode(counterNew, valueNode);
    }

    return retVal;
}
void lFUCachePut(LFUCache *obj, int key, int value) {
    if (0 == obj->capacity) {
        return;
    }

    CounterListNode *counterNode = NULL;
    CounterListNode *counterNew = NULL;
    ValueListNode *valueNode = obj->keyHash[key];
    if (NULL != valueNode) {
        valueNode->value = value;

        counterNode = obj->counterHash[valueNode->counter];

        valueNode->counter++;
        counterNew = obj->counterHash[valueNode->counter];

        removeValueNode(counterNode, valueNode);

        if (NULL == counterNew) {
            counterNew = (CounterListNode *)calloc(1, sizeof(CounterListNode));
            if (counterNew == NULL) {
                perror("malloc");
                return;
            }
            obj->counterHash[valueNode->counter] = counterNew;
            insertCounterNode(obj, counterNode, counterNew);
        }

        if (NULL == counterNode->head) {
            removeCounterNode(obj, counterNode);
            free(counterNode);
            obj->counterHash[valueNode->counter - 1] = NULL;
        }

        insertValueNode(counterNew, valueNode);

        return;
    }

    int keyRemove = 0;
    ValueListNode *valueRemove = NULL;
    if (obj->capacity > obj->currentCounter) {
        obj->currentCounter++;
    } else {
        counterNode = obj->head;

        valueRemove = counterNode->head->prev;
        keyRemove = valueRemove->key;

        removeValueNode(counterNode, valueRemove);

        if (NULL == counterNode->head) {
            removeCounterNode(obj, counterNode);
            free(counterNode);
            obj->counterHash[valueRemove->counter] = NULL;
        }
        free(valueRemove);
        obj->keyHash[keyRemove] = NULL;
    }

    valueNode = (ValueListNode *)calloc(1, sizeof(ValueListNode));
    if (valueNode == NULL) {
        perror("malloc");
        return;
    }
    valueNode->key = key;
    valueNode->value = value;
    valueNode->counter = 1;
    obj->keyHash[key] = valueNode;

    counterNew = obj->counterHash[1];

    if (NULL == counterNew) {
        counterNew = (CounterListNode *)calloc(1, sizeof(CounterListNode));
        if (counterNew == NULL) {
            perror("malloc");
            return;
        }
        obj->counterHash[1] = counterNew;

        insertCounterNode(obj, NULL, counterNew);
    }

    insertValueNode(counterNew, valueNode);
}
void lFUCacheFree(LFUCache *obj) {
    ValueListNode *valueNode = NULL;
    ValueListNode *valueNext = NULL;
    CounterListNode *counterNext = NULL;
    CounterListNode *counterNode = obj->head;
    while (NULL != counterNode) {
        counterNext = counterNode->next;

        valueNode = counterNode->head;
        do {
            valueNext = valueNode->next;
            free(valueNode);
            valueNode = valueNext;
        } while (counterNode->head != valueNode);
        free(counterNode);

        counterNode = counterNext;
    }

    free(obj->keyHash);
    free(obj->counterHash);
    free(obj);
}
/**
 * Your LFUCache struct will be instantiated and called as such:
 * LFUCache* obj = lFUCacheCreate(capacity);
 * int param_1 = lFUCacheGet(obj, key);
 * lFUCachePut(obj, key, value);
 * lFUCacheFree(obj);
 */
```

</details>

<details><summary>C++</summary>

```c++
class LFUCache {
    // (frequency, list of original key-value pairs that have the same frequency)
    unordered_map<int, list<pair<int, int>>> frequencyTable;
    // (key, pair of frequency and the iterator corresponding key int the frequencies map's list)
    unordered_map<int, pair<int, list<pair<int, int>>::iterator>> keyTable;
    int cacheSize;
    int leastFrequently;

    void insert(int key, int frequency, int value) {
        frequencyTable[frequency].push_back({key, value});
        keyTable[key] = {frequency, --frequencyTable[frequency].end()};
    }

   public:
    LFUCache(int capacity) {
        cacheSize = capacity;
        leastFrequently = 0;
    }
    int get(int key) {
        int retVal = -1;

        auto it = keyTable.find(key);
        if (it == keyTable.end()) {
            return retVal;
        }

        int frequency = it->second.first;
        auto iter = it->second.second;
        pair<int, int> keyValue = *iter;
        frequencyTable[frequency].erase(iter);
        if ((frequencyTable[frequency].empty()) && (leastFrequently == frequency)) {
            ++leastFrequently;
        }
        insert(key, frequency + 1, keyValue.second);
        retVal = keyValue.second;

        return retVal;
    }
    void put(int key, int value) {
        if (cacheSize <= 0) {
            return;
        }

        auto it = keyTable.find(key);
        if (it != keyTable.end()) {
            it->second.second->second = value;
            get(key);
            return;
        }

        if (cacheSize == (int)keyTable.size()) {
            keyTable.erase(frequencyTable[leastFrequently].front().first);
            frequencyTable[leastFrequently].pop_front();
        }
        leastFrequently = 1;
        insert(key, 1, value);
    }
};
/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(cacheSize);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
```

</details>

## [1146. Snapshot Array](https://leetcode.com/problems/snapshot-array/)  1770

- [Official](https://leetcode.com/problems/snapshot-array/editorial/)

<details><summary>Description</summary>

```text
Implement a SnapshotArray that supports the following interface:
- SnapshotArray(int length)
  initializes an array-like data structure with the given length. Initially, each element equals 0.
- void set(index, val)
  sets the element at the given index to be equal to val.
- int snap()
  takes a snapshot of the array and returns the snap_id: the total number of times we called snap() minus 1.
- int get(index, snap_id)
  returns the value at the given index, at the time we took the snapshot with the given snap_id

Example 1:
Input: ["SnapshotArray","set","snap","set","get"]
[[3],[0,5],[],[0,6],[0,0]]
Output: [null,null,0,null,5]
Explanation:
SnapshotArray snapshotArr = new SnapshotArray(3); // set the length to be 3
snapshotArr.set(0,5);  // Set array[0] = 5
snapshotArr.snap();  // Take a snapshot, return snap_id = 0
snapshotArr.set(0,6);
snapshotArr.get(0,0);  // Get the value of array[0] with snap_id = 0, return 5

Constraints:
1 <= length <= 5 * 10^4
0 <= index < length
0 <= val <= 10^9
0 <= snap_id < (the total number of times we call snap())
At most 5 * 10^4 calls will be made to set, snap, and get.
```

<details><summary>Hint</summary>

```text
1. Use a list of lists, adding both the element and the snap_id to each index.
```

</details>

</details>

<details><summary>C</summary>

```c
// https://leetcode.cn/problems/snapshot-array/solutions/2302755/cyu-yan-1146-kuai-zhao-shu-zu-by-shua-le-uyw9/

#define MAX_CALLS (50000)  // At most 5 * 10^4 calls will be made to set, snap, and get.
typedef struct {
    int nums[MAX_CALLS];
    int index[MAX_CALLS];
    int idx;
    int snaps[MAX_CALLS];
    int snapId;
} SnapshotArray;
SnapshotArray* snapshotArrayCreate(int length) {
    SnapshotArray* pObj = (SnapshotArray*)malloc(sizeof(SnapshotArray));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    memset(pObj, 0, sizeof(SnapshotArray));

    return pObj;
}
void snapshotArraySet(SnapshotArray* obj, int index, int val) {
    obj->nums[obj->idx] = val;
    obj->index[obj->idx] = index;
    obj->idx += 1;
}
int snapshotArraySnap(SnapshotArray* obj) {
    int retVal = obj->snapId;

    obj->snaps[obj->snapId] = obj->idx;
    obj->snapId += 1;

    return retVal;
}
int snapshotArrayGet(SnapshotArray* obj, int index, int snap_id) {
    int retVal = 0;

    int i;
    for (i = obj->snaps[snap_id] - 1; i >= 0; --i) {
        if (obj->index[i] == index) {
            retVal = obj->nums[i];
            break;
        }
    }

    return retVal;
}
void snapshotArrayFree(SnapshotArray* obj) {
    free(obj);
    obj = NULL;
}
/**
 * Your SnapshotArray struct will be instantiated and called as such:
 * SnapshotArray* obj = snapshotArrayCreate(length);
 * snapshotArraySet(obj, index, val);
 * int param_2 = snapshotArraySnap(obj);
 * int param_3 = snapshotArrayGet(obj, index, snap_id);
 * snapshotArrayFree(obj);
 */
```

</details>

<details><summary>C++</summary>

```c++
class SnapshotArray {
    int snapId;
    vector<vector<pair<int, int>>> historyRecords;

   public:
    SnapshotArray(int length) {
        snapId = 0;
        historyRecords.resize(length);
        for (int i = 0; i < length; ++i) {
            historyRecords[i].push_back(make_pair(0, 0));
        }
    }
    void set(int index, int val) {
        //
        historyRecords[index].push_back(make_pair(snapId, val));
    }
    int snap() {
        int retVal = snapId;

        ++snapId;

        return retVal;
    }
    int get(int index, int snap_id) {
        int retVal = 0;

        auto it = upper_bound(historyRecords[index].begin(), historyRecords[index].end(),
                              make_pair(snap_id, numeric_limits<int>::max()));
        retVal = prev(it)->second;

        return retVal;
    }
};
/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
 */
```

</details>

<details><summary>Python3</summary>

```python
class SnapshotArray:
    def __init__(self, length: int):
        self.id = 0
        self.history_records = [[[0, 0]] for _ in range(length)]

    def set(self, index: int, val: int) -> None:
        self.history_records[index].append([self.id, val])

    def snap(self) -> int:
        retVal = self.id

        self.id += 1

        return retVal

    def get(self, index: int, snap_id: int) -> int:
        retVal = 0

        snap_index = bisect_right(self.history_records[index], [snap_id, 10 ** 9])
        retVal = self.history_records[index][snap_index - 1][1]

        return retVal

# Your SnapshotArray object will be instantiated and called as such:
# obj = SnapshotArray(length)
# obj.set(index,val)
# param_2 = obj.snap()
# param_3 = obj.get(index,snap_id)
```

</details>

## [1472. Design Browser History](https://leetcode.com/problems/design-browser-history/)  1453

<details><summary>Description</summary>

```text
 a browser of one tab where you start on the homepage and you can visit another url,
 get back in the history number of steps or move forward in the history number of steps.

Implement the BrowserHistory class:
- BrowserHistory(string homepage)
  Initializes the object with the homepage of the browser.
- void visit(string url)
  Visits url from the current page. It clears up all the forward history.
- string back(int steps)
  Move steps back in history.
  If you can only return x steps in the history and steps > x, you will return only x steps.
  Return the current url after moving back in history at most steps.
- string forward(int steps)
  Move steps forward in history.
  If you can only forward x steps in the history and steps > x, you will forward only x steps.
  Return the current url after forwarding in history at most steps.

Input:
["BrowserHistory","visit","visit","visit","back","back","forward","visit","forward","back","back"]
[["leetcode.com"],["google.com"],["facebook.com"],["youtube.com"],[1],[1],[1],["linkedin.com"],[2],[2],[7]]
Output:
[null,null,null,null,"facebook.com","google.com","facebook.com",null,"linkedin.com","google.com","leetcode.com"]
Explanation:
BrowserHistory browserHistory = new BrowserHistory("leetcode.com");
browserHistory.visit("google.com");       // You are in "leetcode.com". Visit "google.com"
browserHistory.visit("facebook.com");     // You are in "google.com". Visit "facebook.com"
browserHistory.visit("youtube.com");      // You are in "facebook.com". Visit "youtube.com"
browserHistory.back(1);                   // You are in "youtube.com", move back to "facebook.com" return "facebook.com"
browserHistory.back(1);                   // You are in "facebook.com", move back to "google.com" return "google.com"
browserHistory.forward(1);                // You are in "google.com", move forward to "facebook.com" return "facebook.com"
browserHistory.visit("linkedin.com");     // You are in "facebook.com". Visit "linkedin.com"
browserHistory.forward(2);                // You are in "linkedin.com", you cannot move forward any steps.
browserHistory.back(2);                   // You are in "linkedin.com", move back two steps to "facebook.com"
                                             then to "google.com". return "google.com"
browserHistory.back(7);                   // You are in "google.com", you can move back only one step to "leetcode.com".
                                             return "leetcode.com"

Constraints:
1 <= homepage.length <= 20
1 <= url.length <= 20
1 <= steps <= 100
homepage and url consist of  '.' or lower case English letters.
At most 5000 calls will be made to visit, back, and forward.
```

<details><summary>Hint</summary>

```text
1. Use two stack one for back history and one for forward history and simulate the functions.
2. Can you do faster by using different data structure ?
```

</details>

</details>

<details><summary>C</summary>

```c
#define MAX_URL (20 + 4)  // 1 <= url.length <= 20
#define MAX_CALL (5000)   // At most 5000 calls will be made to visit, back, and forward.
typedef struct {
    char url[MAX_URL];
} DataType;
typedef struct {
    DataType pageStack[MAX_CALL];
    int top;
    int current;
} BrowserHistory;
BrowserHistory* browserHistoryCreate(char* homepage) {
    BrowserHistory* obj = NULL;

    obj = malloc(sizeof(BrowserHistory));
    if (obj == NULL) {
        perror("malloc");
        return obj;
    }
    memset(obj, 0, sizeof(BrowserHistory));

    strcpy(obj->pageStack[obj->top].url, homepage);
    (obj->top)++;

    return obj;
}
void browserHistoryVisit(BrowserHistory* obj, char* url) {
    if ((obj == NULL) || (url == NULL)) {
        return;
    }

    obj->top = obj->current + 1;
    strcpy(obj->pageStack[obj->top].url, url);
    (obj->top)++;
    (obj->current)++;
}
char* browserHistoryBack(BrowserHistory* obj, int steps) {
    char* retVal = NULL;

    if (obj == NULL) {
        return retVal;
    }

    if (steps > obj->current) {
        steps = obj->current;
    }
    obj->current = obj->current - steps;
    retVal = obj->pageStack[obj->current].url;

    return retVal;
}
char* browserHistoryForward(BrowserHistory* obj, int steps) {
    char* retVal = NULL;

    if (obj == NULL) {
        return retVal;
    }

    if (steps > obj->top - obj->current - 1) {
        steps = obj->top - obj->current - 1;
    }
    obj->current = obj->current + steps;
    retVal = obj->pageStack[obj->current].url;

    return retVal;
}
void browserHistoryFree(BrowserHistory* obj) {
    if (obj == NULL) {
        return;
    }

    free(obj);
}
/**
 * Your BrowserHistory struct will be instantiated and called as such:
 * BrowserHistory* obj = browserHistoryCreate(homepage);
 * browserHistoryVisit(obj, url);
 * char * param_2 = browserHistoryBack(obj, steps);
 * char * param_3 = browserHistoryForward(obj, steps);
 * browserHistoryFree(obj);
 */
```

</details>

<details><summary>C++</summary>

```c++
class BrowserHistory {
   private:
    vector<string> pageList;
    int index;

   public:
    BrowserHistory(string homepage) {
        pageList.push_back(homepage);
        index = 0;
    }
    void visit(string url) {
        pageList.erase(pageList.begin() + index + 1, pageList.end());
        pageList.push_back(url);

        ++index;
    }
    string back(int steps) {
        index = max(0, index - steps);

        return pageList[index];
    }
    string forward(int steps) {
        index = min(index + steps, (int)pageList.size() - 1);

        return pageList[index];
    }
};
/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */
```

</details>

## [1603. Design Parking System](https://leetcode.com/problems/design-parking-system/)  1324

- [Official](https://leetcode.com/problems/design-parking-system/editorial/)
- [Official](https://leetcode.cn/problems/design-parking-system/solutions/664493/she-ji-ting-che-xi-tong-by-leetcode-solu-p52h/)

<details><summary>Description</summary>

```text
Design a parking system for a parking lot.
The parking lot has three kinds of parking spaces: big, medium, and small, with a fixed number of slots for each size.

Implement the ParkingSystem class:
- ParkingSystem(int big, int medium, int small)
    Initializes object of the ParkingSystem class.
    The number of slots for each parking space are given as part of the constructor.
- bool addCar(int carType)
    Checks whether there is a parking space of carType for the car that wants to get into the parking lot.
    carType can be of three kinds: big, medium, or small, which are represented by 1, 2, and 3 respectively.
    A car can only park in a parking space of its carType.
    If there is no space available, return false, else park the car in that size space and return true.

Example 1:
Input
["ParkingSystem", "addCar", "addCar", "addCar", "addCar"]
[[1, 1, 0], [1], [2], [3], [1]]
Output
[null, true, true, false, false]
Explanation
ParkingSystem parkingSystem = new ParkingSystem(1, 1, 0);
parkingSystem.addCar(1); // return true because there is 1 available slot for a big car
parkingSystem.addCar(2); // return true because there is 1 available slot for a medium car
parkingSystem.addCar(3); // return false because there is no available slot for a small car
parkingSystem.addCar(1); // return false because there is no available slot for a big car. It is already occupied.

Constraints:
0 <= big, medium, small <= 1000
carType is 1, 2, or 3
At most 1000 calls will be made to addCar
```

<details><summary>Hint</summary>

```text
1. Record number of parking slots still available for each car type.
```

</details>

</details>

<details><summary>C</summary>

```c
typedef struct {
    int big;
    int medium;
    int small;
} ParkingSystem;
ParkingSystem* parkingSystemCreate(int big, int medium, int small) {
    ParkingSystem* pCreate = (ParkingSystem*)malloc(sizeof(ParkingSystem));
    if (pCreate == NULL) {
        perror("malloc");
        return pCreate;
    }
    pCreate->big = big;
    pCreate->medium = medium;
    pCreate->small = small;

    return pCreate;
}
bool parkingSystemAddCar(ParkingSystem* obj, int carType) {
    bool retVal = false;

    switch (carType) {
        case 1:
            if (obj->big > 0) {
                obj->big--;
                retVal = true;
            }
            break;
        case 2:
            if (obj->medium > 0) {
                obj->medium--;
                retVal = true;
            }
            break;
        case 3:
            if (obj->small > 0) {
                obj->small--;
                retVal = true;
            }
            break;
        default:
            break;
    }

    return retVal;
}
void parkingSystemFree(ParkingSystem* obj) {
    free(obj);
    obj = NULL;
}
/**
 * Your ParkingSystem struct will be instantiated and called as such:
 * ParkingSystem* obj = parkingSystemCreate(big, medium, small);
 * bool param_1 = parkingSystemAddCar(obj, carType);
 * parkingSystemFree(obj);
 */
```

</details>

<details><summary>C++</summary>

```c++
class ParkingSystem {
   public:
    int big;
    int medium;
    int small;
    ParkingSystem(int big, int medium, int small) {
        this->big = big;
        this->medium = medium;
        this->small = small;
    }
    bool addCar(int carType) {
        bool retVal = false;

        switch (carType) {
            case 1:
                if (this->big > 0) {
                    this->big -= 1;
                    retVal = true;
                }
                break;
            case 2:
                if (this->medium > 0) {
                    this->medium -= 1;
                    retVal = true;
                }
                break;
            case 3:
                if (this->small > 0) {
                    this->small -= 1;
                    retVal = true;
                }
                break;
            default:
                break;
        }

        return retVal;
    }
};
/**
 * Your ParkingSystem object will be instantiated and called as such:
 * ParkingSystem* obj = new ParkingSystem(big, medium, small);
 * bool param_1 = obj->addCar(carType);
 */
```

</details>

<details><summary>Python3</summary>

```python
class ParkingSystem:
    def __init__(self, big: int, medium: int, small: int):
        self.big = big
        self.medium = medium
        self.small = small

    def addCar(self, carType: int) -> bool:
        retVal = False

        if carType == 1:
            if self.big > 0:
                self.big -= 1
                retVal = True
        elif carType == 2:
            if self.medium > 0:
                self.medium -= 1
                retVal = True
        elif carType == 3:
            if self.small > 0:
                self.small -= 1
                retVal = True

        return retVal

# Your ParkingSystem object will be instantiated and called as such:
# obj = ParkingSystem(big, medium, small)
# param_1 = obj.addCar(carType)
```

</details>

## [3508. Implement Router](https://leetcode.com/problems/implement-router/)  1851

- [Official](https://leetcode.cn/problems/implement-router/solutions/3772883/she-ji-lu-you-qi-by-leetcode-solution-hgxc/)

<details><summary>Description</summary>

```text
Design a data structure that can efficiently manage data packets in a network router.
Each data packet consists of the following attributes:
- source: A unique identifier for the machine that generated the packet.
- destination: A unique identifier for the target machine.
- timestamp: The time at which the packet arrived at the router.

Implement the Router class:
- Router(int memoryLimit): Initializes the Router object with a fixed memory limit.
  - memoryLimit is the maximum number of packets the router can store at any given time.
  - If adding a new packet would exceed this limit, the oldest packet must be removed to free up space.
- bool addPacket(int source, int destination, int timestamp): Adds a packet with the given attributes to the router.
  - A packet is considered a duplicate if another packet with the same source, destination,
    and timestamp already exists in the router.
  - Return true if the packet is successfully added (i.e., it is not a duplicate); otherwise return false.
- int[] forwardPacket(): Forwards the next packet in FIFO (First In First Out) order.
  - Remove the packet from storage.
  - Return the packet as an array [source, destination, timestamp].
  - If there are no packets to forward, return an empty array.
- int getCount(int destination, int startTime, int endTime):
  - Returns the number of packets currently stored in the router (i.e., not yet forwarded)
    that have the specified destination and have timestamps in the inclusive range [startTime, endTime].

Note that queries for addPacket will be made in increasing order of timestamp.

Example 1:
Input:
["Router", "addPacket", "addPacket", "addPacket", "addPacket", "addPacket", "forwardPacket", "addPacket", "getCount"]
[[3], [1, 4, 90], [2, 5, 90], [1, 4, 90], [3, 5, 95], [4, 5, 105], [], [5, 2, 110], [5, 100, 110]]
Output:
[null, true, true, false, true, true, [2, 5, 90], true, 1]
Explanation
// Initialize Router with memoryLimit of 3.
Router router = new Router(3);
// Packet is added. Return True.
router.addPacket(1, 4, 90);
// Packet is added. Return True.
router.addPacket(2, 5, 90);
// This is a duplicate packet. Return False.
router.addPacket(1, 4, 90);
// Packet is added. Return True
router.addPacket(3, 5, 95);
// Packet is added, [1, 4, 90] is removed as number of packets exceeds memoryLimit. Return True.
router.addPacket(4, 5, 105);
// Return [2, 5, 90] and remove it from router.
router.forwardPacket();
// Packet is added. Return True.
router.addPacket(5, 2, 110);
// The only packet with destination 5 and timestamp in the inclusive range [100, 110] is [4, 5, 105]. Return 1.
router.getCount(5, 100, 110);

Example 2:
Input:
["Router", "addPacket", "forwardPacket", "forwardPacket"]
[[2], [7, 4, 90], [], []]
Output:
[null, true, [7, 4, 90], []]
Explanation
// Initialize Router with memoryLimit of 2.
Router router = new Router(2);
// Return True.
router.addPacket(7, 4, 90);
// Return [7, 4, 90].
router.forwardPacket();
// There are no packets left, return [].
router.forwardPacket();

Constraints:
2 <= memoryLimit <= 10^5
1 <= source, destination <= 2 * 10^5
1 <= timestamp <= 10^9
1 <= startTime <= endTime <= 10^9
At most 105 calls will be made to addPacket, forwardPacket, and getCount methods altogether.
queries for addPacket will be made in increasing order of timestamp.
```

<details><summary>Hint</summary>

```text
1. A deque can simulate the adding and forwarding of packets efficiently.
2. Use binary search for counting packets within a timestamp range.
```

</details>

</details>

<details><summary>C</summary>

```c
#if (1)
#define PACKET_HASH_SIZE (4096)
#define DEST_HASH_SIZE (4096)

typedef struct {
    int source;
    int destination;
    int timestamp;
} Packet;
typedef struct PacketSetNode {
    Packet packet;
    struct PacketSetNode* next;
} PacketSetNode;
typedef struct {
    PacketSetNode** table;
    int size;
} PacketSet;
unsigned int hashPacket(Packet* p, int mod) {
    unsigned int h = 17;
    h = h * 31 + p->source;
    h = h * 31 + p->destination;
    h = h * 31 + p->timestamp;
    return h % mod;
}
PacketSet* packetSetCreate(int size) {
    PacketSet* set = malloc(sizeof(PacketSet));
    set->size = size;
    set->table = calloc(size, sizeof(PacketSetNode*));
    return set;
}
bool packetSetContains(PacketSet* set, Packet* p) {
    unsigned int idx = hashPacket(p, set->size);
    PacketSetNode* node = set->table[idx];
    while (node) {
        if (node->packet.source == p->source && node->packet.destination == p->destination &&
            node->packet.timestamp == p->timestamp)
            return true;
        node = node->next;
    }
    return false;
}
void packetSetAdd(PacketSet* set, Packet* p) {
    unsigned int idx = hashPacket(p, set->size);
    PacketSetNode* node = malloc(sizeof(PacketSetNode));
    node->packet = *p;
    node->next = set->table[idx];
    set->table[idx] = node;
}
void packetSetRemove(PacketSet* set, Packet* p) {
    unsigned int idx = hashPacket(p, set->size);
    PacketSetNode* node = set->table[idx];
    PacketSetNode* prev = NULL;
    while (node) {
        if (node->packet.source == p->source && node->packet.destination == p->destination &&
            node->packet.timestamp == p->timestamp) {
            if (prev)
                prev->next = node->next;
            else
                set->table[idx] = node->next;
            free(node);
            return;
        }
        prev = node;
        node = node->next;
    }
}
void packetSetFree(PacketSet* set) {
    for (int i = 0; i < set->size; i++) {
        PacketSetNode* node = set->table[i];
        while (node) {
            PacketSetNode* tmp = node;
            node = node->next;
            free(tmp);
        }
    }
    free(set->table);
    free(set);
}
#endif
#if (1)
typedef struct Pair {
    int* timestamps;
    int size;
    int capacity;
    int head;
} Pair;
typedef struct DestNode {
    int destination;
    Pair pair;
    struct DestNode* next;
} DestNode;
#endif
typedef struct {
    int memoryLimit;
    int packetCount;
    Packet* queue;
    int head;
    int tail;
    PacketSet* packetSet;
    DestNode** destTable;
} Router;
#if (1)
unsigned int hashDest(int destination) {
    //
    return destination % DEST_HASH_SIZE;
}
Pair* getPair(Router* obj, int destination) {
    unsigned int idx = hashDest(destination);
    DestNode* node = obj->destTable[idx];
    while (node) {
        if (node->destination == destination) {
            return &node->pair;
        }
        node = node->next;
    }
    node = malloc(sizeof(DestNode));
    node->destination = destination;
    node->pair.timestamps = NULL;
    node->pair.size = 0;
    node->pair.capacity = 0;
    node->pair.head = 0;
    node->next = obj->destTable[idx];
    obj->destTable[idx] = node;

    return &node->pair;
}
int lowerBound(int* nums, int size, int target, int left) {
    int right = size;

    while (left < right) {
        int mid = (left + right) / 2;
        if (nums[mid] >= target) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return right;
}
#endif
Router* routerCreate(int memoryLimit) {
    Router* pObj = NULL;

    pObj = (Router*)malloc(sizeof(Router));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->memoryLimit = memoryLimit;
    pObj->packetCount = 0;
    pObj->queue = malloc(sizeof(Packet) * memoryLimit);
    pObj->head = pObj->tail = 0;
    pObj->packetSet = packetSetCreate(PACKET_HASH_SIZE);
    pObj->destTable = calloc(DEST_HASH_SIZE, sizeof(DestNode*));

    return pObj;
}
int* routerForwardPacket(Router* obj, int* retSize) {
    int* pRetVal = NULL;

    (*retSize) = 0;
    if (obj->packetCount == 0) {
        return pRetVal;
    }

    Packet packet = obj->queue[obj->head];
    obj->head = (obj->head + 1) % obj->memoryLimit;
    obj->packetCount--;

    packetSetRemove(obj->packetSet, &packet);

    Pair* pair = getPair(obj, packet.destination);
    pair->head++;

    pRetVal = malloc(sizeof(int) * 3);
    pRetVal[0] = packet.source;
    pRetVal[1] = packet.destination;
    pRetVal[2] = packet.timestamp;
    (*retSize) = 3;

    return pRetVal;
}
bool routerAddPacket(Router* obj, int source, int destination, int timestamp) {
    bool retVal = false;

    Packet p = {source, destination, timestamp};

    if (packetSetContains(obj->packetSet, &p)) {
        return retVal;
    }

    if (obj->packetCount == obj->memoryLimit) {
        int retSize;
        int* ret = routerForwardPacket(obj, &retSize);
        free(ret);
        ret = NULL;
    }

    obj->queue[obj->tail] = p;
    obj->tail = (obj->tail + 1) % obj->memoryLimit;
    obj->packetCount++;

    packetSetAdd(obj->packetSet, &p);

    Pair* pair = getPair(obj, destination);
    if (pair->size == pair->capacity) {
        pair->capacity = pair->capacity == 0 ? 4 : pair->capacity * 2;
        pair->timestamps = realloc(pair->timestamps, sizeof(int) * pair->capacity);
    }
    pair->timestamps[pair->size++] = timestamp;

    retVal = true;

    return retVal;
}
int routerGetCount(Router* obj, int destination, int startTime, int endTime) {
    int retVal = 0;

    Pair* pair = getPair(obj, destination);
    if ((pair == NULL) || (pair->size == 0)) {
        return retVal;
    }
    int left = lowerBound(pair->timestamps, pair->size, startTime, pair->head);
    int right = lowerBound(pair->timestamps, pair->size, endTime + 1, pair->head);
    retVal = right - left;

    return retVal;
}
void routerFree(Router* obj) {
    free(obj->queue);
    packetSetFree(obj->packetSet);
    for (int i = 0; i < DEST_HASH_SIZE; i++) {
        DestNode* node = obj->destTable[i];
        while (node) {
            free(node->pair.timestamps);
            DestNode* tmp = node;
            node = node->next;
            free(tmp);
        }
    }
    free(obj->destTable);
    free(obj);
}
/**
 * Your Router struct will be instantiated and called as such:
 * Router* obj = routerCreate(memoryLimit);
 * bool param_1 = routerAddPacket(obj, source, destination, timestamp);
 * int* param_2 = routerForwardPacket(obj, retSize);
 * int param_3 = routerGetCount(obj, destination, startTime, endTime);
 * routerFree(obj);
 */
```

</details>

<details><summary>C++</summary>

```c++
class Router {
   public:
    int memLimit = 0;
    int length = 0;
    set<tuple<int, int, int>> isExist;
    unordered_map<int, deque<int>> sameDestQue;
    deque<tuple<int, int, int>> que;

    Router(int memoryLimit) {
        //
        memLimit = memoryLimit;
    }
    bool addPacket(int source, int destination, int timestamp) {
        bool retVal = false;

        tuple<int, int, int> packet = make_tuple(source, destination, timestamp);
        if (isExist.find(packet) != isExist.end()) {
            return retVal;
        }

        if (length == memLimit) {
            forwardPacket();
        }
        length++;
        que.push_back(packet);
        sameDestQue[destination].push_back(timestamp);
        isExist.insert(packet);
        retVal = true;

        return retVal;
    }
    vector<int> forwardPacket() {
        vector<int> retVal;

        if (que.empty() == false) {
            tuple<int, int, int> packet = que.front();
            que.pop_front();
            retVal = vector<int>{get<0>(packet), get<1>(packet), get<2>(packet)};
            isExist.erase(packet);
            sameDestQue[retVal[1]].pop_front();
            length--;
        }

        return retVal;
    }
    int getCount(int destination, int startTime, int endTime) {
        int retVal = 0;

        auto pos1 = lower_bound(sameDestQue[destination].begin(), sameDestQue[destination].end(), startTime);
        auto pos2 = upper_bound(sameDestQue[destination].begin(), sameDestQue[destination].end(), endTime);
        retVal = pos2 - pos1;

        return retVal;
    }
};
/**
 * Your Router object will be instantiated and called as such:
 * Router* obj = new Router(memoryLimit);
 * bool param_1 = obj->addPacket(source,destination,timestamp);
 * vector<int> param_2 = obj->forwardPacket();
 * int param_3 = obj->getCount(destination,startTime,endTime);
 */
```

</details>

<details><summary>Python3</summary>

```python
class Router:
    def __init__(self, memoryLimit: int):
        self.memLimit = memoryLimit
        self.length = 0
        self.isExist = set()
        self.sameDestQue = {}
        self.que = []

    def addPacket(self, source: int, destination: int, timestamp: int) -> bool:
        retVal = False

        packet = (source, destination, timestamp)
        if packet in self.isExist:
            return retVal

        if self.length == self.memLimit:
            self.forwardPacket()
        self.length += 1
        self.que.append(packet)

        if destination not in self.sameDestQue:
            self.sameDestQue[destination] = SortedList()
        self.sameDestQue[destination].add(timestamp)
        self.isExist.add(packet)

        retVal = True

        return retVal

    def forwardPacket(self) -> List[int]:
        retVal = []

        if self.que:
            packet = self.que.pop(0)
            retVal = list(packet)
            self.isExist.remove(packet)
            self.sameDestQue[retVal[1]].remove(retVal[2])
            self.length -= 1

        return retVal

    def getCount(self, destination: int, startTime: int, endTime: int) -> int:
        retVal = 0

        if destination not in self.sameDestQue:
            return retVal
        sl = self.sameDestQue[destination]
        retVal = sl.bisect_right(endTime) - sl.bisect_left(startTime)

        return retVal

# Your Router object will be instantiated and called as such:
# obj = Router(memoryLimit)
# param_1 = obj.addPacket(source,destination,timestamp)
# param_2 = obj.forwardPacket()
# param_3 = obj.getCount(destination,startTime,endTime)
```

</details>
