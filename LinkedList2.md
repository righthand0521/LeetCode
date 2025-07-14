# [Linked List](https://en.wikipedia.org/wiki/Linked_list)

## [1171. Remove Zero Sum Consecutive Nodes from Linked List](https://leetcode.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list/)  1782

- [Official](https://leetcode.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list/editorial/)
- [Official](https://leetcode.cn/problems/remove-zero-sum-consecutive-nodes-from-linked-list/solutions/2297308/cong-lian-biao-zhong-shan-qu-zong-he-zhi-h18o/)

<details><summary>Description</summary>

```text
Given the head of a linked list,
we repeatedly delete consecutive sequences of nodes that sum to 0 until there are no such sequences.

After doing so, return the head of the final linked list.  You may return any such answer.

(Note that in the examples below, all sequences are serializations of ListNode objects.)

Example 1:
Input: head = [1,2,-3,3,1]
Output: [3,1]
Note: The answer [1,2,1] would also be accepted.

Example 2:
Input: head = [1,2,3,-3,4]
Output: [1,2,4]

Example 3:
Input: head = [1,2,3,-3,-2]
Output: [1]

Constraints:
The given linked list will contain between 1 and 1000 nodes.
Each node in the linked list has -1000 <= node.val <= 1000.
```

<details><summary>Hint</summary>

```text
1. Convert the linked list into an array.
2. While you can find a non-empty subarray with sum = 0, erase it.
3. Convert the array into a linked list.
```

</details>

</details>

<details><summary>C</summary>

```c
struct hashTable {
    int key;
    struct ListNode *val;
    UT_hash_handle hh;
};
struct hashTable *hashFindItem(struct hashTable **obj, int key) {
    struct hashTable *pRetVal = NULL;

    HASH_FIND_INT(*obj, &key, pRetVal);

    return pRetVal;
}
bool hashAddItem(struct hashTable **obj, int key, struct ListNode *val) {
    bool retVal = false;

    if (hashFindItem(obj, key)) {
        return retVal;
    }

    struct hashTable *pEntry = (struct hashTable *)malloc(sizeof(struct hashTable));
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
void hashSetItem(struct hashTable **obj, int key, struct ListNode *val) {
    struct hashTable *pEntry = hashFindItem(obj, key);
    if (pEntry == NULL) {
        hashAddItem(obj, key, val);
    } else {
        pEntry->val = val;
    }
}
struct ListNode *hashGetItem(struct hashTable **obj, int key) {
    struct ListNode *pRetVal = NULL;

    struct hashTable *pEntry = hashFindItem(obj, key);
    if (pEntry != NULL) {
        pRetVal = pEntry->val;
    }

    return pRetVal;
}
void hashFree(struct hashTable **pFree) {
    struct hashTable *current;
    struct hashTable *tmp;
    HASH_ITER(hh, *pFree, current, tmp) {
        HASH_DEL(*pFree, current);
        free(current);
    }
}
struct ListNode *createNode(int val) {
    struct ListNode *pRetVal = NULL;

    pRetVal = (struct ListNode *)malloc(sizeof(struct ListNode));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->val = val;
    pRetVal->next = NULL;

    return pRetVal;
}
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *removeZeroSumSublists(struct ListNode *head) {
    struct ListNode *pRetVal = NULL;

    pRetVal = createNode(0);
    if (pRetVal == NULL) {
        return pRetVal;
    }
    pRetVal->next = head;

    struct ListNode *pCurrent = NULL;
    struct hashTable *pHashTable = NULL;
    int prefixSum = 0;
    for (pCurrent = pRetVal; pCurrent; pCurrent = pCurrent->next) {
        prefixSum += pCurrent->val;
        hashSetItem(&pHashTable, prefixSum, pCurrent);
    }

    struct ListNode *pGet;
    prefixSum = 0;
    for (pCurrent = pRetVal; pCurrent; pCurrent = pCurrent->next) {
        prefixSum += pCurrent->val;
        pGet = hashGetItem(&pHashTable, prefixSum);
        /* valgrind -s --tool=memcheck --leak-check=full --max-stackframe=5000000 1171.c
            ==27242== HEAP SUMMARY:
            ==27242==     in use at exit: 96 bytes in 6 blocks
            ==27242==   total heap usage: 38 allocs, 32 frees, 3,976 bytes allocated
            ==27242==
            ==27242== 96 (32 direct, 64 indirect) bytes in 2 blocks are definitely lost in loss record 2 of 2
            ==27242==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
            ==27242==    by 0x1092AC: main (in /root/WorkingSpace/1171-c)
            ==27242==
            ==27242== LEAK SUMMARY:
            ==27242==    definitely lost: 32 bytes in 2 blocks
            ==27242==    indirectly lost: 64 bytes in 4 blocks
            ==27242==      possibly lost: 0 bytes in 0 blocks
            ==27242==    still reachable: 0 bytes in 0 blocks
            ==27242==         suppressed: 0 bytes in 0 blocks
            ==27242==
            ==27242== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
         */
        if (pGet != NULL) {
            pCurrent->next = pGet->next;
        }
    }

    hashFree(&pHashTable);
    pCurrent = pRetVal;
    pRetVal = pRetVal->next;
    free(pCurrent);
    pCurrent = NULL;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
   public:
    ListNode* removeZeroSumSublists(ListNode* head) {
        ListNode* pRetVal = nullptr;

        pRetVal = new ListNode(0);
        pRetVal->next = head;

        unordered_map<int, ListNode*> hashTable;
        hashTable[0] = pRetVal;

        ListNode* pCurrent = nullptr;
        int prefixSum = 0;
        for (pCurrent = pRetVal; pCurrent; pCurrent = pCurrent->next) {
            prefixSum += pCurrent->val;
            hashTable[prefixSum] = pCurrent;
        }

        prefixSum = 0;
        for (pCurrent = pRetVal; pCurrent; pCurrent = pCurrent->next) {
            prefixSum += pCurrent->val;
            /* valgrind -s --tool=memcheck --leak-check=full --max-stackframe=5000000 1171.cpp
                ==19012== HEAP SUMMARY:
                ==19012==     in use at exit: 96 bytes in 6 blocks
                ==19012==   total heap usage: 43 allocs, 37 frees, 74,832 bytes allocated
                ==19012==
                ==19012== 96 (32 direct, 64 indirect) bytes in 2 blocks are definitely lost in loss record 2 of 2
                ==19012==    at 0x4849013: operator new(unsigned long) (in
               /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
                ==19012==    by 0x109630: main (in /root/WorkingSpace/1171-cpp)
                ==19012==
                ==19012== LEAK SUMMARY:
                ==19012==    definitely lost: 32 bytes in 2 blocks
                ==19012==    indirectly lost: 64 bytes in 4 blocks
                ==19012==      possibly lost: 0 bytes in 0 blocks
                ==19012==    still reachable: 0 bytes in 0 blocks
                ==19012==         suppressed: 0 bytes in 0 blocks
                ==19012==
                ==19012== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
            */
            pCurrent->next = hashTable[prefixSum]->next;
        }

        pCurrent = pRetVal;
        pRetVal = pRetVal->next;
        delete pCurrent;

        return pRetVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def removeZeroSumSublists(self, head: Optional[ListNode]) -> Optional[ListNode]:
        retVal = ListNode(0)

        retVal.next = head

        hashTable = defaultdict(Optional[ListNode])
        hashTable[0] = retVal

        prefixSum = 0
        current = head
        while current:
            prefixSum += current.val
            hashTable[prefixSum] = current
            current = current.next

        current = retVal
        prefixSum = 0
        while current:
            prefixSum += current.val
            current.next = hashTable[prefixSum].next
            current = current.next
        retVal = retVal.next

        return retVal
```

</details>

## [1290. Convert Binary Number in a Linked List to Integer](https://leetcode.com/problems/convert-binary-number-in-a-linked-list-to-integer/)  1151

- [Official](https://leetcode.cn/problems/convert-binary-number-in-a-linked-list-to-integer/solutions/101732/er-jin-zhi-lian-biao-zhuan-zheng-shu-by-leetcode-s/)

<details><summary>Description</summary>

```text
Given head which is a reference node to a singly-linked list.
The value of each node in the linked list is either 0 or 1.
The linked list holds the binary representation of a number.

Return the decimal value of the number in the linked list.

The most significant bit is at the head of the linked list.

Example 1:
Input: head = [1,0,1]
Output: 5
Explanation: (101) in base 2 = (5) in base 10

Example 2:
Input: head = [0]
Output: 0

Constraints:
The Linked List is not empty.
Number of nodes will not exceed 30.
Each node's value is either 0 or 1.
```

<details><summary>Hint</summary>

```text
1. Traverse the linked list and store all values in a string or array. convert the values obtained to decimal value.
2. You can solve the problem in O(1) memory using bits operation.
   use shift left operation ( << ) and or operation ( | ) to get the decimal value in one operation.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
int getDecimalValue(struct ListNode* head) {
    int retVal = head->val;

    struct ListNode* pCurrent = head->next;
    while (pCurrent != NULL) {
        retVal = (retVal << 1) | pCurrent->val;
        pCurrent = pCurrent->next;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
   public:
    int getDecimalValue(ListNode* head) {
        int retVal = head->val;

        ListNode* pCurrent = head->next;
        while (pCurrent != nullptr) {
            retVal = (retVal << 1) | pCurrent->val;
            pCurrent = pCurrent->next;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def getDecimalValue(self, head: Optional[ListNode]) -> int:
        retVal = head.val

        current = head.next
        while current is not None:
            retVal = (retVal << 1) | current.val
            current = current.next

        return retVal
```

</details>

## [1669. Merge In Between Linked Lists](https://leetcode.com/problems/merge-in-between-linked-lists/)  1428

- [Official](https://leetcode.com/problems/merge-in-between-linked-lists/editorial/)
- [Official](https://leetcode.cn/problems/merge-in-between-linked-lists/solutions/2079499/he-bing-liang-ge-lian-biao-by-leetcode-s-alt8/)

<details><summary>Description</summary>

```text
You are given two linked lists: list1 and list2 of sizes n and m respectively.

Remove list1's nodes from the ath node to the bth node, and put list2 in their place.

The blue edges and nodes in the following figure indicate the result:
+------------------------------------------------------------------------------+
|                               +---------------------+                        |
| list1 -> (0) -> ... -> (a-1) -|> (a) -> ... -> (b) -|> (b+1) -> ... -> (n-1) |
|                          |    |        Remove       |    ^                   |
|                          v    +---------------------+    |                   |
|                list2 -> (0) -> .................... -> (m-1)                 |
+------------------------------------------------------------------------------+
Build the result list and return its head.

Example 1:
+---------------------------------------------------------+
|                              +---------------+          |
| list1 -> (0) -> (1) -> (2) --|-> (3) -> (4) -|-> (5)    |
|                         |    |     Remove    |    ^     |
|                         v    +---------------+    |     |
|            list2 -> (1000000) -> (1000001) -> (1000002) |
+---------------------------------------------------------+
Input: list1 = [0,1,2,3,4,5], a = 3, b = 4, list2 = [1000000,1000001,1000002]
Output: [0,1,2,1000000,1000001,1000002,5]
Explanation: We remove the nodes 3 and 4 and put the entire list2 in their place.
The blue edges and nodes in the above figure indicate the result.

Example 2:
+----------------------------------------------------------------------------+
|                        +--------------------------------------+            |
| list1 -> (0) -> (1) ---|--> (2) ---> (3) ---> (4) ---> (5) ---|--> (6)     |
|                  |     |                Remove                |     ^      |
|                  v     +--------------------------------------+     |      |
|     list2 -> (1000000) -> (1000001) -> (1000002) -> (1000003) -> (1000004) |
+----------------------------------------------------------------------------+
Input: list1 = [0,1,2,3,4,5,6], a = 2, b = 5, list2 = [1000000,1000001,1000002,1000003,1000004]
Output: [0,1,1000000,1000001,1000002,1000003,1000004,6]
Explanation: The blue edges and nodes in the above figure indicate the result.

Constraints:
3 <= list1.length <= 10^4
1 <= a <= b < list1.length - 1
1 <= list2.length <= 10^4
```

<details><summary>Hint</summary>

```text
1. Check which edges need to be changed.
2. Let the next node of the (a-1)th node of list1 be the 0-th node in list 2.
3. Let the next node of the last node of list2 be the (b+1)-th node in list 1.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* mergeInBetween(struct ListNode* list1, int a, int b, struct ListNode* list2) {
    struct ListNode* pRetVal = list1;

    int i;
    struct ListNode* pPrevious = NULL;
    struct ListNode* pNext1 = list1;
    struct ListNode* pNext2 = NULL;

    for (i = 0; i < a; ++i) {
        pPrevious = pNext1;
        pNext1 = pNext1->next;
    }
    pNext2 = pPrevious;

    for (i = a; i <= b; ++i) {
        pPrevious->next = pNext1->next;
        free(pNext1);
        pNext1 = pPrevious->next;
    }

    pNext2->next = list2;
    while (pNext2 != NULL) {
        pPrevious = pNext2;
        pNext2 = pNext2->next;
    }
    pPrevious->next = pNext1;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
   public:
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        ListNode* pRetVal = list1;

        struct ListNode* pPrevious = nullptr;
        struct ListNode* pNext1 = list1;
        for (int i = 0; i < a; ++i) {
            pPrevious = pNext1;
            pNext1 = pNext1->next;
        }
        struct ListNode* pNext2 = pPrevious;

        for (int i = a; i <= b; ++i) {
            pPrevious->next = pNext1->next;
            delete pNext1;
            pNext1 = pPrevious->next;
        }

        pNext2->next = list2;
        while (pNext2 != nullptr) {
            pPrevious = pNext2;
            pNext2 = pNext2->next;
        }
        pPrevious->next = pNext1;

        return pRetVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def mergeInBetween(self, list1: ListNode, a: int, b: int, list2: ListNode) -> ListNode:
        retVal = list1

        pPrevious = None
        pNext1 = list1
        for _ in range(a):
            pPrevious = pNext1
            pNext1 = pNext1.next
        pNext2 = pPrevious

        for _ in range(a, b+1):
            pPrevious.next = pNext1.next
            pNext1 = pPrevious.next

        pNext2.next = list2
        while pNext2 != None:
            pPrevious = pNext2
            pNext2 = pNext2.next
        pPrevious.next = pNext1

        return retVal
```

</details>

## [1721. Swapping Nodes in a Linked List](https://leetcode.com/problems/swapping-nodes-in-a-linked-list/)  1386

<details><summary>Description</summary>

```text
You are given the head of a linked list, and an integer k.

Return the head of the linked list
after swapping the values of the kth node from the beginning and the kth node from the end (the list is 1-indexed).

Example 1:
Input: head = [1,2,3,4,5], k = 2
Output: [1,4,3,2,5]

Example 2:
Input: head = [7,9,6,6,7,8,3,0,9,5], k = 5
Output: [7,9,6,6,8,7,3,0,9,5]

Constraints:
The number of nodes in the list is n.
1 <= k <= n <= 10^5
0 <= Node.val <= 100
```

<details><summary>Hint</summary>

```text
1. We can transform the linked list to an array this should ease things up
2. After transforming the linked list to an array
   it becomes as easy as swapping two integers in an array then rebuilding the linked list
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* swapNodes(struct ListNode* head, int k) {
    struct ListNode* pRetVal = head;

    struct ListNode* pCurrent = head;
    struct ListNode* pSwapHead = NULL;
    struct ListNode* pSwapTail = NULL;

    int idx = 0;
    while (pCurrent != NULL) {
        ++idx;
        if (idx >= k) {
            break;
        }

        pCurrent = pCurrent->next;
    }
    pSwapHead = pCurrent;

    pCurrent = pCurrent->next;
    pSwapTail = head;
    while (pCurrent != NULL) {
        pCurrent = pCurrent->next;
        pSwapTail = pSwapTail->next;
    }

    int tmp = pSwapHead->val;
    pSwapHead->val = pSwapTail->val;
    pSwapTail->val = tmp;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
   public:
    ListNode* swapNodes(ListNode* head, int k) {
        ListNode* pRetVal = head;

        ListNode* pCurrent = head;
        ListNode* pSwapHead = NULL;
        ListNode* pSwapTail = NULL;

        int idx = 0;
        while (pCurrent != NULL) {
            ++idx;
            if (idx >= k) {
                break;
            }

            pCurrent = pCurrent->next;
        }
        pSwapHead = pCurrent;

        pCurrent = pCurrent->next;
        pSwapTail = head;
        while (pCurrent != NULL) {
            pCurrent = pCurrent->next;
            pSwapTail = pSwapTail->next;
        }

        int tmp = pSwapHead->val;
        pSwapHead->val = pSwapTail->val;
        pSwapTail->val = tmp;

        return pRetVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def swapNodes(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        retVal = head

        pCurrent = head
        idx = 0
        while pCurrent != None:
            idx += 1
            if idx >= k:
                break
            pCurrent = pCurrent.next
        pSwapHead = pCurrent

        pCurrent = pCurrent.next
        pSwapTail = head
        while pCurrent != None:
            pCurrent = pCurrent.next
            pSwapTail = pSwapTail.next

        tmp = pSwapHead.val
        pSwapHead.val = pSwapTail.val
        pSwapTail.val = tmp

        return retVal
```

</details>

## [1836. Remove Duplicates From an Unsorted Linked List](https://leetcode.com/problems/remove-duplicates-from-an-unsorted-linked-list/)  unlock

- Subscribe to unlock
  - Goldman Sachs
  - Microsoft
  - VMware
- [1836. Remove Duplicates From an Unsorted Linked List](https://leetcode.ca/2021-06-27-1836-Remove-Duplicates-From-an-Unsorted-Linked-List/)

<details><summary>Description</summary>

```text
Given the head of a linked list,
find all the values that appear more than once in the list and delete the nodes that have any of those values.

Return the linked list after the deletions.

Example 1:
Input: head = [1,2,3,2]
Output: [1,3]
Explanation: 2 appears twice in the linked list, so all 2's should be deleted. After deleting all 2's, we are left with [1,3].

Example 2:
Input: head = [2,1,1,2]
Output: []
Explanation: 2 and 1 both appear twice. All the elements should be deleted.

Example 3:
Input: head = [3,2,2,1,3,2,4]
Output: [1,4]
Explanation: 3 appears twice and 2 appears three times. After deleting all 3's and 2's, we are left with [1,4].

Constraints:
The number of nodes in the list is in the range [1, 10^5]
1 <= Node.val <= 10^5
```

</details>

<details><summary>C</summary>

```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* deleteDuplicatesUnsorted(struct ListNode* head) {
    struct ListNode* pRetVal = head;

    if ((head == NULL) || (head->next == NULL)) {
        return pRetVal;
    }

#define MAX_HASH_SIZE (int)(1e5 + 1)
    int HashTable[MAX_HASH_SIZE];
    memset(HashTable, 0, sizeof(HashTable));
    while (pRetVal != NULL) {
        ++HashTable[pRetVal->val];
        pRetVal = pRetVal->next;
    }
    pRetVal = head;

    struct ListNode* pPrevious = head;
    while (pRetVal != NULL) {
        if (pRetVal == head) {
            if (HashTable[pRetVal->val] != 1) {
                head = head->next;
                pPrevious = head;
                free(pRetVal);
                pRetVal = head;
            } else {
                pRetVal = pRetVal->next;
            }
        } else {
            if (HashTable[pRetVal->val] != 1) {
                pPrevious->next = pRetVal->next;
                free(pRetVal);
                pRetVal = pPrevious->next;
            } else {
                pPrevious = pPrevious->next;
                pRetVal = pRetVal->next;
            }
        }
    }
    pRetVal = head;

    return pRetVal;
}
```

</details>
