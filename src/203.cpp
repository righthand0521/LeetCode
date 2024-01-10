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
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* pRetVal = head;

        if (pRetVal == nullptr) {
            return pRetVal;
        }

        ListNode* pPrevious = nullptr;
        ListNode* pFree = head;
        while (pFree != nullptr) {
            if (pFree->val != val) {
                pPrevious = pFree;
                pFree = pFree->next;
                continue;
            }

            if (pPrevious != nullptr) {
                pPrevious->next = pFree->next;
                delete pFree;
                pFree = pPrevious->next;
            } else {
                pRetVal = pRetVal->next;
                delete pFree;
                pFree = pRetVal;
            }
        }

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> head;
        int val;
    };
    vector<subject> testData{{{1, 2, 6, 3, 4, 5, 6}, 6}, {{}, 1}, {{7, 7, 7, 7}, 7}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [1,2,6,3,4,5,6], val = 6
     *  Output: [1,2,3,4,5]
     *
     *  Input: head = [], val = 1
     *  Output: []
     *
     *  Input: head = [7,7,7,7], val = 7
     *  Output: []
     */

    Solution cSolution;
    ListNode* pHead = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].head);
        cout << "Input: head = [";
        printList(pHead);
        cout << "], val = " << testData[i].val << "\n";

        pHead = cSolution.removeElements(pHead, testData[i].val);
        cout << "Output: [";
        printList(pHead);
        cout << "]\n";

        cout << "\n";

        freeListNode(pHead);
        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}
