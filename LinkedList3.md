# [Linked List](https://en.wikipedia.org/wiki/Linked_list)

## [2058. Find the Minimum and Maximum Number of Nodes Between Critical Points](https://leetcode.com/problems/find-the-minimum-and-maximum-number-of-nodes-between-critical-points/)  1310

- [Official](https://leetcode.com/problems/find-the-minimum-and-maximum-number-of-nodes-between-critical-points/editorial/)
- [Official](https://leetcode.cn/problems/find-the-minimum-and-maximum-number-of-nodes-between-critical-points/solutions/1077097/zhao-chu-lin-jie-dian-zhi-jian-de-zui-xi-b08v/)

<details><summary>Description</summary>

```text
A critical point in a linked list is defined as either a local maxima or a local minima.

A node is a local maxima if the current node has a value strictly greater than the previous node and the next node.

A node is a local minima if the current node has a value strictly smaller than the previous node and the next node.

Note that a node can only be a local maxima/minima if there exists both a previous node and a next node.

Given a linked list head, return an array of length 2 containing [minDistance, maxDistance]
where minDistance is the minimum distance between any two distinct critical points
and maxDistance is the maximum distance between any two distinct critical points.
If there are fewer than two critical points, return [-1, -1].

Example 1:
Input: head = [3,1]
Output: [-1,-1]
Explanation: There are no critical points in [3,1].

Example 2:
Input: head = [5,3,1,2,5,1,2]
Output: [1,3]
Explanation: There are three critical points:
- [5,3,1,2,5,1,2]: The third node is a local minima because 1 is less than 3 and 2.
- [5,3,1,2,5,1,2]: The fifth node is a local maxima because 5 is greater than 2 and 1.
- [5,3,1,2,5,1,2]: The sixth node is a local minima because 1 is less than 5 and 2.
The minimum distance is between the fifth and the sixth node. minDistance = 6 - 5 = 1.
The maximum distance is between the third and the sixth node. maxDistance = 6 - 3 = 3.

Example 3:
Input: head = [1,3,2,2,3,2,2,2,7]
Output: [3,3]
Explanation: There are two critical points:
- [1,3,2,2,3,2,2,2,7]: The second node is a local maxima because 3 is greater than 1 and 2.
- [1,3,2,2,3,2,2,2,7]: The fifth node is a local maxima because 3 is greater than 2 and 2.
Both the minimum and maximum distances are between the second and the fifth node.
Thus, minDistance and maxDistance is 5 - 2 = 3.
Note that the last node is not considered a local maxima because it does not have a next node.

Constraints:
The number of nodes in the list is in the range [2, 10^5].
1 <= Node.val <= 10^5
```

<details><summary>Hint</summary>

```text
1. The maximum distance must be the distance between the first and last critical point.
2. For each adjacent critical point, calculate the difference and check if it is the minimum distance.
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
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* nodesBetweenCriticalPoints(struct ListNode* head, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int*)malloc(2 * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, -1, (2 * sizeof(int)));
    (*returnSize) = 2;

    // The number of nodes in the list is in the range [2, 10^5].
    int currentIndex = 1;
    struct ListNode* pCurrent = head->next;
    struct ListNode* pPrevious = head;

    int firstCriticalIndex = 0;
    int previousCriticalIndex = 0;
    int minDistance = INT_MAX;
    while (pCurrent->next != NULL) {
        if (((pCurrent->val < pPrevious->val) && (pCurrent->val < pCurrent->next->val)) ||
            ((pCurrent->val > pPrevious->val) && (pCurrent->val > pCurrent->next->val))) {
            if (previousCriticalIndex == 0) {
                previousCriticalIndex = currentIndex;
                firstCriticalIndex = currentIndex;
            } else {
                minDistance = fmin(minDistance, currentIndex - previousCriticalIndex);
                previousCriticalIndex = currentIndex;
            }
        }

        currentIndex += 1;
        pPrevious = pCurrent;
        pCurrent = pCurrent->next;
    }

    int maxDistance;
    if (minDistance != INT_MAX) {
        maxDistance = previousCriticalIndex - firstCriticalIndex;
        pRetVal[0] = minDistance;
        pRetVal[1] = maxDistance;
    }

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
    vector<int> nodesBetweenCriticalPoints(ListNode *head) {
        vector<int> retVal(2, -1);

        // The number of nodes in the list is in the range [2, 10^5].
        int currentIndex = 1;
        ListNode *pCurrent = head->next;
        ListNode *pPrevious = head;

        int firstCriticalIndex = 0;
        int previousCriticalIndex = 0;
        int minDistance = numeric_limits<int>::max();
        while (pCurrent->next != nullptr) {
            if (((pCurrent->val < pPrevious->val) && (pCurrent->val < pCurrent->next->val)) ||
                ((pCurrent->val > pPrevious->val) && (pCurrent->val > pCurrent->next->val))) {
                if (previousCriticalIndex == 0) {
                    previousCriticalIndex = currentIndex;
                    firstCriticalIndex = currentIndex;
                } else {
                    minDistance = min(minDistance, currentIndex - previousCriticalIndex);
                    previousCriticalIndex = currentIndex;
                }
            }

            currentIndex += 1;
            pPrevious = pCurrent;
            pCurrent = pCurrent->next;
        }

        if (minDistance != numeric_limits<int>::max()) {
            int maxDistance = previousCriticalIndex - firstCriticalIndex;
            retVal[0] = minDistance;
            retVal[1] = maxDistance;
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
    def nodesBetweenCriticalPoints(self, head: Optional[ListNode]) -> List[int]:
        retVal = [-1, -1]

        # The number of nodes in the list is in the range [2, 10^5].
        currentIndex = 1
        current = head.next
        previous = head

        firstCriticalIndex = 0
        previousCriticalIndex = 0
        minDistance = float("inf")
        while current.next is not None:
            if (((current.val < previous.val) and (current.val < current.next.val)) or
                    ((current.val > previous.val) and (current.val > current.next.val))):
                if previousCriticalIndex == 0:
                    previousCriticalIndex = currentIndex
                    firstCriticalIndex = currentIndex
                else:
                    minDistance = min(minDistance, currentIndex - previousCriticalIndex)
                    previousCriticalIndex = currentIndex

            currentIndex += 1
            previous = current
            current = current.next

        if minDistance != float("inf"):
            maxDistance = previousCriticalIndex - firstCriticalIndex
            retVal = [minDistance, maxDistance]

        return retVal
```

</details>

## [2074. Reverse Nodes in Even Length Groups](https://leetcode.com/problems/reverse-nodes-in-even-length-groups/)  1685

- [Official](https://leetcode.cn/problems/reverse-nodes-in-even-length-groups/solutions/1101822/fan-zhuan-ou-shu-chang-du-zu-de-jie-dian-owra/)

<details><summary>Description</summary>

```text
You are given the head of a linked list.

The nodes in the linked list are sequentially assigned to non-empty groups
whose lengths form the sequence of the natural numbers (1, 2, 3, 4, ...).
The length of a group is the number of nodes assigned to it. In other words,
- The 1st node is assigned to the first group.
- The 2nd and the 3rd nodes are assigned to the second group.
- The 4th, 5th, and 6th nodes are assigned to the third group, and so on.

Note that the length of the last group may be less than or equal to 1 + the length of the second to last group.

Reverse the nodes in each group with an even length, and return the head of the modified linked list.

Example 1:
Input: head = [5,2,6,3,9,1,7,3,8,4]
Output: [5,6,2,3,9,1,4,8,3,7]
Explanation:
- The length of the first group is 1, which is odd, hence no reversal occurs.
- The length of the second group is 2, which is even, hence the nodes are reversed.
- The length of the third group is 3, which is odd, hence no reversal occurs.
- The length of the last group is 4, which is even, hence the nodes are reversed.

Example 2:
Input: head = [1,1,0,6]
Output: [1,0,1,6]
Explanation:
- The length of the first group is 1. No reversal occurs.
- The length of the second group is 2. The nodes are reversed.
- The length of the last group is 1. No reversal occurs.

Example 3:
Input: head = [1,1,0,6,5]
Output: [1,0,1,5,6]
Explanation:
- The length of the first group is 1. No reversal occurs.
- The length of the second group is 2. The nodes are reversed.
- The length of the last group is 2. The nodes are reversed.

Constraints:
The number of nodes in the list is in the range [1, 10^5].
0 <= Node.val <= 10^5
```

<details><summary>Hint</summary>

```text
1. Consider the list structure ...A → (B → ... → C) → D..., where the nodes between B and C (inclusive) form a group,
   A is the last node of the previous group, and D is the first node of the next group.
   How can you utilize this structure?
2. Suppose you have B → ... → C reversed (because it was of even length) so that it is now C → ... → B.
   What references do you need to fix so that the transitions between the previous, current, and next groups are correct?
3. A.next should be set to C, and B.next should be set to D.
4. Once the current group is finished being modified, you need to find the new A, B, C, and D nodes for the next group.
   How can you use the old A, B, C, and D nodes to find the new ones?
5. The new A is either the old B or old C depending on if the group was of even or odd length.
   The new B is always the old D. The new C and D can be found based on the new B and the next group's length.
6. You can set the initial values of A, B, C, and D to A = null, B = head, C = head, D = head.next.
   Repeat the steps from the previous hints until D is null.
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
struct ListNode* reverseEvenLengthGroups(struct ListNode* head) {
    struct ListNode* pRetVal = head;

    int i;
    int count = 0;
    int length = 0;
    struct ListNode* pTmp = NULL;
    struct ListNode* pNext = NULL;
    struct ListNode* pPrevious = NULL;
    struct ListNode* pCurrent = head;
    while (pCurrent != NULL) {
        ++count;
        length = 0;
        pNext = pCurrent;
        while ((length < count) && (pNext != NULL)) {
            ++length;
            pNext = pNext->next;
        }

        if (length % 2 == 0) {
            for (i = 0; i < (length - 1); ++i) {
                pTmp = pCurrent->next;
                pCurrent->next = pCurrent->next->next;
                pTmp->next = pPrevious->next;
                pPrevious->next = pTmp;
            }
        } else {
            for (i = 0; i < (length - 1); ++i) {
                pPrevious = pCurrent;
                pCurrent = pCurrent->next;
            }
        }

        pPrevious = pCurrent;
        pCurrent = pCurrent->next;
    }

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
    ListNode* reverseEvenLengthGroups(ListNode* head) {
        ListNode* pRetVal = head;

        int i;
        int count = 0;
        int length = 0;
        ListNode* pTmp = nullptr;
        ListNode* pNext = nullptr;
        ListNode* pPrevious = nullptr;
        ListNode* pCurrent = head;
        while (pCurrent != nullptr) {
            ++count;
            length = 0;
            pNext = pCurrent;
            while ((length < count) && (pNext != nullptr)) {
                ++length;
                pNext = pNext->next;
            }

            if (length % 2 == 0) {
                for (i = 0; i < (length - 1); ++i) {
                    pTmp = pCurrent->next;
                    pCurrent->next = pCurrent->next->next;
                    pTmp->next = pPrevious->next;
                    pPrevious->next = pTmp;
                }
            } else {
                for (i = 0; i < (length - 1); ++i) {
                    pPrevious = pCurrent;
                    pCurrent = pCurrent->next;
                }
            }

            pPrevious = pCurrent;
            pCurrent = pCurrent->next;
        }

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
    def reverseEvenLengthGroups(self, head: Optional[ListNode]) -> Optional[ListNode]:
        retVal = head

        count = 0
        pPrevious = None
        pCurrent = head
        while pCurrent != None:
            count += 1
            length = 0
            pNext = pCurrent
            while (length < count) and (pNext != None):
                length += 1
                pNext = pNext.next

            if length % 2 == 0:
                for _ in range(length-1):
                    pTmp = pCurrent.next
                    pCurrent.next = pCurrent.next.next
                    pTmp.next = pPrevious.next
                    pPrevious.next = pTmp
            else:
                for _ in range(length-1):
                    pPrevious = pCurrent
                    pCurrent = pCurrent.next

            pPrevious = pCurrent
            pCurrent = pCurrent.next

        return retVal
```

</details>

## [2095. Delete the Middle Node of a Linked List](https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/)  1324

- [Official](https://leetcode.cn/problems/delete-the-middle-node-of-a-linked-list/solutions/1140770/shan-chu-lian-biao-de-zhong-jian-jie-dia-yvv7/)

<details><summary>Description</summary>

```text
You are given the head of a linked list. Delete the middle node, and return the head of the modified linked list.

The middle node of a linked list of size n is the ⌊n / 2⌋th node from the start using 0-based indexing,
where ⌊x⌋ denotes the largest integer less than or equal to x.
- For n = 1, 2, 3, 4, and 5, the middle nodes are 0, 1, 1, 2, and 2, respectively.

Example 1:
Input: head = [1,3,4,7,1,2,6]
Output: [1,3,4,1,2,6]
Explanation:
The above figure represents the given linked list. The indices of the nodes are written below.
Since n = 7, node 3 with value 7 is the middle node, which is marked in red.
We return the new list after removing this node.

Example 2:
Input: head = [1,2,3,4]
Output: [1,2,4]
Explanation:
The above figure represents the given linked list.
For n = 4, node 2 with value 3 is the middle node, which is marked in red.

Example 3:
Input: head = [2,1]
Output: [2]
Explanation:
The above figure represents the given linked list.
For n = 2, node 1 with value 1 is the middle node, which is marked in red.
Node 0 with value 2 is the only node remaining after removing node 1.

Constraints:
The number of nodes in the list is in the range [1, 10^5].
1 <= Node.val <= 10^5
```

<details><summary>Hint</summary>

```text
1. If a point with a speed s moves n units in a given time,
   a point with speed 2 * s will move 2 * n units at the same time.
   Can you use this to find the middle node of a linked list?
2. If you are given the middle node, the node before it, and the node after it, how can you modify the linked list?
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
struct ListNode* deleteMiddle(struct ListNode* head) {
    struct ListNode* pRetVal = head;

    // The number of nodes is 1
    if (pRetVal->next == NULL) {
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }

    // Middle of the Linked List: https://leetcode.com/problems/middle-of-the-linked-list/
    struct ListNode* pOne = pRetVal;
    struct ListNode* pTwo = pRetVal;
    while ((pTwo != NULL) && (pTwo->next != NULL)) {
        pOne = pOne->next;
        pTwo = pTwo->next;
        if (pTwo != NULL) {
            pTwo = pTwo->next;
        }
    }

    // The number of nodes is 2
    if (pOne->next == NULL) {
        pRetVal->next = NULL;
        free(pOne);
        pOne = NULL;
        return pRetVal;
    }

    // Delete Node in a Linked List: https://leetcode.com/problems/delete-node-in-a-linked-list/
    struct ListNode* pFree = pOne->next;
    *pOne = *pOne->next;
    free(pFree);

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
    ListNode* deleteMiddle(ListNode* head) {
        ListNode* pRetVal = head;

        // The number of nodes is 1
        if (pRetVal->next == nullptr) {
            delete pRetVal;
            pRetVal = nullptr;
            return pRetVal;
        }

        // Middle of the Linked List: https://leetcode.com/problems/middle-of-the-linked-list/
        ListNode* pOne = pRetVal;
        ListNode* pTwo = pRetVal;
        while ((pTwo != nullptr) && (pTwo->next != nullptr)) {
            pOne = pOne->next;
            pTwo = pTwo->next;
            if (pTwo != nullptr) {
                pTwo = pTwo->next;
            }
        }

        // The number of nodes is 2
        if (pOne->next == nullptr) {
            pRetVal->next = nullptr;
            delete pOne;
            pOne = nullptr;
            return pRetVal;
        }

        // Delete Node in a Linked List: https://leetcode.com/problems/delete-node-in-a-linked-list/
        ListNode* pFree = pOne->next;
        *pOne = *pOne->next;
        delete pFree;
        pFree = nullptr;

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
    def deleteMiddle(self, head: Optional[ListNode]) -> Optional[ListNode]:
        pRetVal = head

        # // The number of nodes is 1
        if head.next == None:
            pRetVal = None
            return pRetVal

        # // Middle of the Linked List: https://leetcode.com/problems/middle-of-the-linked-list/
        pOne = head
        pTwo = head
        while (pTwo != None) and (pTwo.next != None):
            pPrevious = pOne
            pOne = pOne.next
            pTwo = pTwo.next
            if pTwo != None:
                pTwo = pTwo.next

        # // The number of nodes is 2
        if pOne.next == None:
            pRetVal.next = None
            return pRetVal

        # // Delete Node in a Linked List: https://leetcode.com/problems/delete-node-in-a-linked-list/
        pPrevious.next = pOne.next
        pOne = None

        return pRetVal
```

</details>

## [2130. Maximum Twin Sum of a Linked List](https://leetcode.com/problems/maximum-twin-sum-of-a-linked-list/)  1317

- [Official](https://leetcode.cn/problems/maximum-twin-sum-of-a-linked-list/solutions/1202031/lian-biao-zui-da-luan-sheng-he-by-leetco-uoc7/)

<details><summary>Description</summary>

```text
In a linked list of size n, where n is even,
the ith node (0-indexed) of the linked list is known as the twin of the (n-1-i)th node, if 0 <= i <= (n / 2) - 1.

For example, if n = 4, then node 0 is the twin of node 3, and node 1 is the twin of node 2.
These are the only nodes with twins for n = 4.
The twin sum is defined as the sum of a node and its twin.

Given the head of a linked list with even length, return the maximum twin sum of the linked list.

Example 1:
Input: head = [5,4,2,1]
Output: 6
Explanation:
Nodes 0 and 1 are the twins of nodes 3 and 2, respectively. All have twin sum = 6.
There are no other nodes with twins in the linked list.
Thus, the maximum twin sum of the linked list is 6.

Example 2:
Input: head = [4,2,2,3]
Output: 7
Explanation:
The nodes with twins present in this linked list are:
- Node 0 is the twin of node 3 having a twin sum of 4 + 3 = 7.
- Node 1 is the twin of node 2 having a twin sum of 2 + 2 = 4.
Thus, the maximum twin sum of the linked list is max(7, 4) = 7.

Example 3:
Input: head = [1,100000]
Output: 100001
Explanation:
There is only one node with a twin in the linked list having twin sum of 1 + 100000 = 100001.

Constraints:
The number of nodes in the list is an even integer in the range [2, 10^5].
1 <= Node.val <= 10^5
```

<details><summary>Hint</summary>

```text
1. How can "reversing" a part of the linked list help find the answer?
2. We know that the nodes of the first half are twins of nodes in the second half,
   so try dividing the linked list in half and reverse the second half.
3. How can two pointers be used to find every twin sum optimally?
4. Use two different pointers pointing to the first nodes of the two halves of the linked list.
   The second pointer will point to the first node of the reversed half,
   which is the (n-1-i)th node in the original linked list.
   By moving both pointers forward at the same time, we find all twin sums.
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
int pairSum(struct ListNode* head) {
    int retVal = 0;

    struct ListNode* pReverse = NULL;
    int pReverseCount = 0;
    struct ListNode* pNew = NULL;
    struct ListNode* pFree = NULL;

    struct ListNode* pCurrent = head;
    while (pCurrent != NULL) {
        pNew = (struct ListNode*)malloc(sizeof(struct ListNode));
        if (pNew == NULL) {
            perror("malloc");
            pCurrent = pReverse;
            while (pCurrent != NULL) {
                pFree = pCurrent;
                pCurrent = pCurrent->next;
                free(pFree);
            }
            return retVal;
        }
        pNew->val = pCurrent->val;
        pNew->next = pReverse;
        pReverse = pNew;
        ++pReverseCount;

        pCurrent = pCurrent->next;
    }

    struct ListNode* p1 = head;
    struct ListNode* p2 = pReverse;
    int i;
    for (i = 0; i < pReverseCount / 2; ++i) {
        retVal = fmax(retVal, p1->val + p2->val);

        p1 = p1->next;
        p2 = p2->next;
    }

    pCurrent = pReverse;
    while (pCurrent != NULL) {
        pFree = pCurrent;
        pCurrent = pCurrent->next;
        free(pFree);
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
    int pairSum(ListNode* head) {
        int retVal = 0;

        vector<int> value;
        ListNode* pCurrent = head;
        while (pCurrent != nullptr) {
            value.emplace_back(pCurrent->val);
            pCurrent = pCurrent->next;
        }

        int i = 0;
        int j = value.size() - 1;
        while (i < j) {
            retVal = max(retVal, value[i++] + value[j--]);
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
    def pairSum(self, head: Optional[ListNode]) -> int:
        retVal = 0

        value = []
        pCurrent = head
        while pCurrent != None:
            value.append(pCurrent.val)
            pCurrent = pCurrent.next

        i = 0
        j = len(value) - 1
        while i < j:
            retVal = max(retVal, value[i] + value[j])
            i += 1
            j -= 1

        return retVal
```

</details>

## [2181. Merge Nodes in Between Zeros](https://leetcode.com/problems/merge-nodes-in-between-zeros/)  1333

- [Official](https://leetcode.com/problems/merge-nodes-in-between-zeros/editorial/)
- [Official](https://leetcode.cn/problems/merge-nodes-in-between-zeros/solutions/1301107/he-bing-ling-zhi-jian-de-jie-dian-by-lee-zo9b/)

<details><summary>Description</summary>

```text
You are given the head of a linked list, which contains a series of integers separated by 0's.
The beginning and end of the linked list will have Node.val == 0.

For every two consecutive 0's, merge all the nodes lying in between them into a single node
whose value is the sum of all the merged nodes.
The modified list should not contain any 0's.

Return the head of the modified linked list.

Example 1:
Input: head = [0,3,1,0,4,5,2,0]
Output: [4,11]
Explanation:
The above figure represents the given linked list. The modified list contains
- The sum of the nodes marked in green: 3 + 1 = 4.
- The sum of the nodes marked in red: 4 + 5 + 2 = 11.

Example 2:
Input: head = [0,1,0,3,0,2,2,0]
Output: [1,3,4]
Explanation:
The above figure represents the given linked list. The modified list contains
- The sum of the nodes marked in green: 1 = 1.
- The sum of the nodes marked in red: 3 = 3.
- The sum of the nodes marked in yellow: 2 + 2 = 4.

Constraints:
The number of nodes in the list is in the range [3, 2 * 10^5].
0 <= Node.val <= 1000
There are no two consecutive nodes with Node.val == 0.
The beginning and end of the linked list have Node.val == 0.
```

<details><summary>Hint</summary>

```text
1. How can you use two pointers to modify the original list into the new list?
2. Have a pointer traverse the entire linked list,
   while another pointer looks at a node that is currently being modified.
3. Keep on summing the values of the nodes between the traversal pointer and
   the modifying pointer until the former comes across a ‘0’.
   In that case, the modifying pointer is incremented to modify the next node.
4. Do not forget to have the next pointer of the final node of the modified list point to null.
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
struct ListNode* mergeNodes(struct ListNode* head) {
    struct ListNode* pRetVal = head;

    int sum = 0;
    struct ListNode* pFree = NULL;
    struct ListNode* pPrevious = head;
    struct ListNode* pCurrent = head->next;
    while (pCurrent != NULL) {
        if (pCurrent->val != 0) {
            sum += pCurrent->val;
            pPrevious->next = pCurrent->next;
            pFree = pCurrent;
            free(pFree);
            pFree = NULL;
        } else {
            pCurrent->val = sum;
            sum = 0;
            pPrevious = pCurrent;
        }

        pCurrent = pPrevious->next;
    }
    pRetVal = head->next;
    pFree = head;
    free(pFree);
    pFree = NULL;

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
    ListNode *mergeNodes(ListNode *head) {
        ListNode *pRetVal = head;

        int sum = 0;
        ListNode *pFree = nullptr;
        ListNode *pPrevious = head;
        ListNode *pCurrent = head->next;
        while (pCurrent != nullptr) {
            if (pCurrent->val != 0) {
                sum += pCurrent->val;
                pPrevious->next = pCurrent->next;
                pFree = pCurrent;
                delete pFree;
                pFree = nullptr;
            } else {
                pCurrent->val = sum;
                sum = 0;
                pPrevious = pCurrent;
            }

            pCurrent = pPrevious->next;
        }
        pRetVal = head->next;
        pFree = head;
        delete pFree;
        pFree = nullptr;

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
    def mergeNodes(self, head: Optional[ListNode]) -> Optional[ListNode]:
        retVal = head

        modify = head.next
        nextSum = modify
        while nextSum:
            sum = 0

            # Find the sum of all nodes until you encounter a 0.
            while nextSum.val != 0:
                sum += nextSum.val
                nextSum = nextSum.next

            # Assign the sum to the current node's value.
            modify.val = sum

            # Move nextSum to the first non-zero value of the next block.
            nextSum = nextSum.next

            # Move modify also to this node.
            modify.next = nextSum
            modify = modify.next

        retVal = head.next

        return retVal
```

</details>

## [2487. Remove Nodes From Linked List](https://leetcode.com/problems/remove-nodes-from-linked-list/)  1454

- [Official](https://leetcode.com/problems/remove-nodes-from-linked-list/editorial/)
- [Official](https://leetcode.cn/problems/remove-nodes-from-linked-list/solutions/2587737/cong-lian-biao-zhong-yi-chu-jie-dian-by-z53sr/)

<details><summary>Description</summary>

```text
You are given the head of a linked list.

Remove every node which has a node with a greater value anywhere to the right side of it.

Return the head of the modified linked list.

Example 1:
Input: head = [5,2,13,3,8]
Output: [13,8]
Explanation: The nodes that should be removed are 5, 2 and 3.
- Node 13 is to the right of node 5.
- Node 13 is to the right of node 2.
- Node 8 is to the right of node 3.

Example 2:
Input: head = [1,1,1,1]
Output: [1,1,1,1]
Explanation: Every node has value 1, so no nodes are removed.

Constraints:
The number of the nodes in the given list is in the range [1, 10^5].
1 <= Node.val <= 10^5
```

<details><summary>Hint</summary>

```text
1. Iterate on nodes in reversed order.
2. When iterating in reversed order, save the maximum value that was passed before.
```

</details>

</details>

<details><summary>C</summary>

```c
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* pRetVal = NULL;

    struct ListNode* pPrevious = NULL;
    struct ListNode* pCurrent = head;
    struct ListNode* pNext = NULL;
    while (pCurrent != NULL) {
        pNext = pCurrent->next;
        pCurrent->next = pPrevious;
        pPrevious = pCurrent;
        pCurrent = pNext;
    }
    pRetVal = pPrevious;

    return pRetVal;
}
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* removeNodes(struct ListNode* head) {
    struct ListNode* pRetVal = head;

    head = reverseList(head);

    struct ListNode* pDeleted = NULL;
    int maximum = 0;
    struct ListNode* pPrevious = NULL;
    struct ListNode* pCurrent = head;
    while (pCurrent != NULL) {
        maximum = fmax(maximum, pCurrent->val);
        if (pCurrent->val >= maximum) {
            pPrevious = pCurrent;
            pCurrent = pCurrent->next;
            continue;
        }

        if (pPrevious != NULL) {
            pPrevious->next = pCurrent->next;
        } else {
            head = pCurrent->next;
        }

        pDeleted = pCurrent;
        pCurrent = pCurrent->next;
        free(pDeleted);
        pDeleted = NULL;
    }

    pRetVal = reverseList(head);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    ListNode* reverseList(ListNode* head) {
        ListNode* pRetVal = nullptr;

        ListNode* pPrevious = nullptr;
        ListNode* pCurrent = head;
        ListNode* pNext = nullptr;
        while (pCurrent != nullptr) {
            pNext = pCurrent->next;
            pCurrent->next = pPrevious;
            pPrevious = pCurrent;
            pCurrent = pNext;
        }
        pRetVal = pPrevious;

        return pRetVal;
    }
    ListNode* removeNodes(ListNode* head) {
        ListNode* pRetVal = head;

        head = reverseList(head);

        int maximum = 0;
        ListNode* pPrevious = nullptr;
        ListNode* pCurrent = head;
        while (pCurrent != nullptr) {
            maximum = max(maximum, pCurrent->val);
            if (pCurrent->val >= maximum) {
                pPrevious = pCurrent;
                pCurrent = pCurrent->next;
                continue;
            }

            if (pPrevious != nullptr) {
                pPrevious->next = pCurrent->next;
            } else {
                head = pCurrent->next;
            }

            ListNode* pDeleted = pCurrent;
            pCurrent = pCurrent->next;
            delete pDeleted;
            pDeleted = nullptr;
        }

        pRetVal = reverseList(head);

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
    def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        retVal = None

        previous = None
        current = head
        next = None
        while current != None:
            next = current.next
            current.next = previous
            previous = current
            current = next
        retVal = previous

        return retVal

    def removeNodes(self, head: Optional[ListNode]) -> Optional[ListNode]:
        retVal = head

        head = self.reverseList(head)

        maximum = 0
        previous = None
        current = head
        while current != None:
            maximum = max(maximum, current.val)
            if current.val >= maximum:
                previous = current
                current = current.next
                continue

            if previous != None:
                previous.next = current.next
            else:
                head = current.next
            deleted = current
            current = current.next
            deleted.next = None

        retVal = self.reverseList(head)

        return retVal
```

</details>

## [2807. Insert Greatest Common Divisors in Linked List](https://leetcode.com/problems/insert-greatest-common-divisors-in-linked-list/)  1279

- [Official](https://leetcode.com/problems/insert-greatest-common-divisors-in-linked-list/editorial/)
- [Official](https://leetcode.cn/problems/insert-greatest-common-divisors-in-linked-list/solutions/2589529/zai-lian-biao-zhong-cha-ru-zui-da-gong-y-udrs/)

<details><summary>Description</summary>

```text
Given the head of a linked list head, in which each node contains an integer value.

Between every pair of adjacent nodes, insert a new node with a value equal to the greatest common divisor of them.

Return the linked list after insertion.

The greatest common divisor of two numbers is the largest positive integer that evenly divides both numbers.

Example 1:
Input: head = [18,6,10,3]
Output: [18,6,6,2,10,1,3]
Explanation: The 1st diagram denotes the initial linked list
and the 2nd diagram denotes the linked list after inserting the new nodes (nodes in blue are the inserted nodes).
- We insert the greatest common divisor of 18 and 6 = 6 between the 1st and the 2nd nodes.
- We insert the greatest common divisor of 6 and 10 = 2 between the 2nd and the 3rd nodes.
- We insert the greatest common divisor of 10 and 3 = 1 between the 3rd and the 4th nodes.
There are no more adjacent nodes, so we return the linked list.

Example 2:
Input: head = [7]
Output: [7]
Explanation: The 1st diagram denotes the initial linked list
and the 2nd diagram denotes the linked list after inserting the new nodes.
There are no pairs of adjacent nodes, so we return the initial linked list.

Constraints:
The number of nodes in the list is in the range [1, 5000].
1 <= Node.val <= 1000
```

</details>

<details><summary>C</summary>

```c
int gcd(int a, int b) {
    int retVal = 1;

    int tmp;
    while (b != 0) {
        tmp = a;
        a = b;
        b = tmp % b;
    }
    retVal = a;

    return retVal;
}
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* insertGreatestCommonDivisors(struct ListNode* head) {
    struct ListNode* pRetVal = head;

    if ((pRetVal == NULL) || (pRetVal->next == NULL)) {
        return pRetVal;
    }

    int gcdValue;
    struct ListNode* pGcdNode;
    struct ListNode* pNode1 = pRetVal;
    struct ListNode* pNode2 = pRetVal->next;
    while (pNode2 != NULL) {
        gcdValue = gcd(pNode1->val, pNode2->val);

        pGcdNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        if (pGcdNode == NULL) {
            perror("malloc");
            return pRetVal;
        }
        pGcdNode->val = gcdValue;
        pGcdNode->next = NULL;
        pNode1->next = pGcdNode;
        pGcdNode->next = pNode2;

        pNode1 = pNode2;
        pNode2 = pNode2->next;
    }

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
   private:
    int gcd(int a, int b) {
        int retVal = 1;

        while (b != 0) {
            int tmp = a;
            a = b;
            b = tmp % b;
        }
        retVal = a;

        return retVal;
    }

   public:
    ListNode *insertGreatestCommonDivisors(ListNode *head) {
        ListNode *pRetVal = head;

        if ((pRetVal == nullptr) || (pRetVal->next == nullptr)) {
            return pRetVal;
        }

        ListNode *pNode1 = pRetVal;
        ListNode *pNode2 = pRetVal->next;
        while (pNode2 != nullptr) {
            int gcdValue = gcd(pNode1->val, pNode2->val);

            ListNode *gcdNode = new ListNode(gcdValue);
            pNode1->next = gcdNode;
            gcdNode->next = pNode2;

            pNode1 = pNode2;
            pNode2 = pNode2->next;
        }

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
    def gcd(self, a: int, b: int) -> int:
        retVal = 1

        while b != 0:
            a, b = b, a % b
        retVal = a

        return retVal

    def insertGreatestCommonDivisors(self, head: Optional[ListNode]) -> Optional[ListNode]:
        retVal = head

        if (retVal is None) or (retVal.next is None):
            return retVal

        node1 = retVal
        node2 = retVal.next
        while node2 is not None:
            gcdValue = self.gcd(node1.val, node2.val)

            gcdNode = ListNode(gcdValue)
            node1.next = gcdNode
            gcdNode.next = node2

            node1 = node2
            node2 = node2.next

        return retVal
```

</details>

## [2816. Double a Number Represented as a Linked List](https://leetcode.com/problems/double-a-number-represented-as-a-linked-list/)  1393

- [Official](https://leetcode.com/problems/double-a-number-represented-as-a-linked-list/editorial/)

<details><summary>Description</summary>

```text
You are given the head of a non-empty linked list representing a non-negative integer without leading zeroes.

Return the head of the linked list after doubling it.

Example 1:
Input: head = [1,8,9]
Output: [3,7,8]
Explanation: The figure above corresponds to the given linked list which represents the number 189.
Hence, the returned linked list represents the number 189 * 2 = 378.

Example 2:
Input: head = [9,9,9]
Output: [1,9,9,8]
Explanation: The figure above corresponds to the given linked list which represents the number 999.
Hence, the returned linked list reprersents the number 999 * 2 = 1998.

Constraints:
The number of nodes in the list is in the range [1, 10^4]
0 <= Node.val <= 9
The input is generated such that the list represents a number that does not have leading zeros,
except the number 0 itself.
```

<details><summary>Hint</summary>

```text
1. Traverse the linked list from the least significant digit to the most significant digit and
   multiply each node's value by 2
2. Handle any carry-over digits that may arise during the doubling process.
3. If there is a carry-over digit on the most significant digit,
   create a new node with that value and point it to the start of the given linked list and return it.
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
struct ListNode* doubleIt(struct ListNode* head) {
    struct ListNode* pRetVal = head;

    int doubleValue;
    struct ListNode* pPrevious = NULL;
    struct ListNode* pCurrent = head;
    while (pCurrent != NULL) {
        doubleValue = pCurrent->val * 2;
        if (doubleValue < 10) {
            pCurrent->val = doubleValue;
        } else if (pPrevious != NULL) {
            pCurrent->val = doubleValue % 10;
            pPrevious->val += 1;
        } else {
            head = (struct ListNode*)malloc(sizeof(struct ListNode));
            if (head == NULL) {
                perror("malloc");
                return pRetVal;
            }
            head->val = 1;
            head->next = pCurrent;
            pCurrent->val = doubleValue % 10;
        }
        pPrevious = pCurrent;
        pCurrent = pCurrent->next;
    }
    pRetVal = head;

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
    ListNode* doubleIt(ListNode* head) {
        ListNode* pRetVal = head;

        ListNode* pPrevious = nullptr;
        ListNode* pCurrent = head;
        while (pCurrent != nullptr) {
            int doubleValue = pCurrent->val * 2;
            if (doubleValue < 10) {
                pCurrent->val = doubleValue;
            } else if (pPrevious != nullptr) {
                pCurrent->val = doubleValue % 10;
                pPrevious->val += 1;
            } else {
                head = new ListNode(1, pCurrent);
                pCurrent->val = doubleValue % 10;
            }
            pPrevious = pCurrent;
            pCurrent = pCurrent->next;
        }
        pRetVal = head;

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
    def doubleIt(self, head: Optional[ListNode]) -> Optional[ListNode]:
        retVal = head

        previous = None
        current = head
        while current != None:
            doubleValue = current.val * 2
            if doubleValue < 10:
                current.val = doubleValue
            elif previous != None:
                current.val = doubleValue % 10
                previous.val += 1
            else:
                head = ListNode(1, current)
                current.val = doubleValue % 10
            previous = current
            current = current.next
        retVal = head

        return retVal
```

</details>
