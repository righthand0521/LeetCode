# [Linked List](https://en.wikipedia.org/wiki/Linked_list)

## [3217. Delete Nodes From Linked List Present in Array](https://leetcode.com/problems/delete-nodes-from-linked-list-present-in-array/)  1341

- [Official](https://leetcode.com/problems/delete-nodes-from-linked-list-present-in-array/editorial/)

<details><summary>Description</summary>

```text
You are given an array of integers nums and the head of a linked list.
Return the head of the modified linked list after removing all nodes from the linked list
that have a value that exists in nums.

Example 1:
Input: nums = [1,2,3], head = [1,2,3,4,5]
Output: [4,5]
Explanation:
Remove the nodes with values 1, 2, and 3.

Example 2:
Input: nums = [1], head = [1,2,1,2,1,2]
Output: [2,2,2]
Explanation:
Remove the nodes with value 1.

Example 3:
Input: nums = [5], head = [1,2,3,4]
Output: [1,2,3,4]
Explanation:
No node has value 5.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^5
All elements in nums are unique.
The number of nodes in the given list is in the range [1, 10^5].
1 <= Node.val <= 10^5
The input is generated such that there is at least one node in the linked list that has a value not present in nums.
```

<details><summary>Hint</summary>

```text
1. Add all elements of nums into a Set.
2. Scan the list to check if the current element should be deleted by checking the Set.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MAX_NUMS_SIZE (int)(1e5 + 1)  // 1 <= nums[i] <= 10^5
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* modifiedList(int* nums, int numsSize, struct ListNode* head) {
    struct ListNode* pRetVal = head;

    int valuesToRemove[MAX_NUMS_SIZE];
    memset(valuesToRemove, 0, sizeof(valuesToRemove));
    int i;
    for (i = 0; i < numsSize; ++i) {
        valuesToRemove[nums[i]] += 1;
    }

    struct ListNode* pDelete = NULL;
    while ((pRetVal != NULL) && (valuesToRemove[pRetVal->val] > 0)) {
        pDelete = pRetVal;
        pRetVal = pRetVal->next;
        free(pDelete);
        pDelete = NULL;
    }
    if (pRetVal == NULL) {
        return pRetVal;
    }

    struct ListNode* pCurrent = pRetVal;
    while (pCurrent->next != NULL) {
        if (valuesToRemove[pCurrent->next->val] > 0) {
            pDelete = pCurrent->next;
            pCurrent->next = pCurrent->next->next;
            free(pDelete);
            pDelete = NULL;
        } else {
            pCurrent = pCurrent->next;
        }
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
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        ListNode* pRetVal = head;

        unordered_set<int> valuesToRemove(nums.begin(), nums.end());

        while ((pRetVal != nullptr) && (valuesToRemove.count(pRetVal->val) > 0)) {
            ListNode* pPrevious = pRetVal;
            pRetVal = pRetVal->next;
            delete pPrevious;
        }
        if (pRetVal == nullptr) {
            return pRetVal;
        }

        ListNode* pCurrent = pRetVal;
        while (pCurrent->next != nullptr) {
            if (valuesToRemove.count(pCurrent->next->val) > 0) {
                ListNode* pDelete = pCurrent->next;
                pCurrent->next = pCurrent->next->next;
                delete pDelete;
            } else {
                pCurrent = pCurrent->next;
            }
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
    def modifiedList(self, nums: List[int], head: Optional[ListNode]) -> Optional[ListNode]:
        retVal = head

        valuesToRemove = set(nums)

        while (retVal) and (retVal.val in valuesToRemove):
            retVal = retVal.next
        if not retVal:
            return retVal

        current = retVal
        while current.next:
            if current.next.val in valuesToRemove:
                current.next = current.next.next
            else:
                current = current.next

        return retVal
```

</details>
