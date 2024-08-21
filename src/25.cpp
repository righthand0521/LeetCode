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
   private:
    pair<ListNode*, ListNode*> reverse(ListNode* head, ListNode* tail) {
        ListNode* pPrevious = tail->next;
        ListNode* pCurrent = head;
        while (pPrevious != tail) {
            ListNode* pNext = pCurrent->next;
            pCurrent->next = pPrevious;
            pPrevious = pCurrent;
            pCurrent = pNext;
        }

        return {tail, head};
    }

   public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* pRetVal = head;

        ListNode* pHair = new ListNode(0);
        pHair->next = head;
        ListNode* pPrevious = pHair;

        while (head != nullptr) {
            ListNode* pTail = pPrevious;

            for (int i = 0; i < k; ++i) {
                pTail = pTail->next;
                if (pTail == nullptr) {
                    pRetVal = pHair->next;
                    delete pHair;
                    pHair = nullptr;
                    return pRetVal;
                }
            }

            ListNode* pNext = pTail->next;
            tie(head, pTail) = reverse(head, pTail);
            pPrevious->next = head;
            pTail->next = pNext;
            pPrevious = pTail;

            head = pTail->next;
        }

        pRetVal = pHair->next;

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> node;
        int k;
    };
    vector<subject> testData{{{1, 2, 3, 4, 5}, 2}, {{1, 2, 3, 4, 5}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [1,2,3,4,5], k = 2
     *  Output: [2,1,4,3,5]
     *
     *  Input: head = [1,2,3,4,5], k = 3
     *  Output: [3,2,1,4,5]
     */

    Solution cSolution;
    ListNode* pHead = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].node);
        cout << "Input: head = [";
        printList(pHead);
        cout << "], k = " << testData[i].k << "\n";

        pHead = cSolution.reverseKGroup(pHead, testData[i].k);
        cout << "Output: [";
        printList(pHead);
        cout << "]\n";

        cout << "\n";

        freeListNode(pHead);
        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}
