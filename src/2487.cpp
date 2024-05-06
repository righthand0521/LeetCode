#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#include "list.h"

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

int main(int argc, char** argv) {
    struct subject {
        vector<int> node;
    };
    vector<subject> testData{{{5, 2, 13, 3, 8}}, {{1, 1, 1, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [5,2,13,3,8]
     *  Output: [13,8]
     *
     *  Input: head = [1,1,1,1]
     *  Output: [1,1,1,1]
     */

    Solution cSolution;
    ListNode* pHead = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].node);
        cout << "Input: head = [";
        printList(pHead);
        cout << "]\n";

        pHead = cSolution.removeNodes(pHead);
        cout << "Output: [";
        printList(pHead);
        cout << "]\n";

        cout << "\n";

        freeListNode(pHead);
        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}
