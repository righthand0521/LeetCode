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
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* pRetVal = nullptr;

        pRetVal = new ListNode(0);
        if (pRetVal == nullptr) {
            perror("malloc");
            pRetVal = head;
            return pRetVal;
        }
        pRetVal->next = head;

        ListNode* pPrevious = pRetVal;
        ListNode* pCurrent = head;
        while (pCurrent != nullptr) {
            bool duplicate = false;
            if ((pCurrent != nullptr) && (pCurrent->next != nullptr)) {
                if (pCurrent->next->val == pCurrent->val) {
                    duplicate = true;
                }
            }

            if (duplicate == true) {
                int duplicateVal = pCurrent->val;
                while ((pCurrent != nullptr) && (pCurrent->val == duplicateVal)) {
                    ListNode* pDelete = pCurrent;
                    pCurrent = pCurrent->next;
                    delete pDelete;
                }
                pPrevious->next = pCurrent;
            } else {
                pPrevious = pCurrent;
                if (pCurrent != nullptr) {
                    pCurrent = pCurrent->next;
                }
            }
        }
        ListNode* pDelete = pRetVal;
        pRetVal = pRetVal->next;
        delete pDelete;

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> node;
    };
    vector<subject> testData{{{1, 2, 3, 3, 4, 4, 5}}, {{1, 1, 1, 2, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [1,2,3,3,4,4,5]
     *  Output: [1,2,5]
     *
     *  Input: head = [1,1,1,2,3]
     *  Output: [2,3]
     */

    Solution cSolution;
    ListNode* pAnswer = nullptr;
    ListNode* pHead = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].node);
        cout << "Input: head = [";
        printList(pHead);
        cout << "]\n";

        pAnswer = cSolution.deleteDuplicates(pHead);
        cout << "Output: [";
        printList(pAnswer);
        cout << "]\n";

        cout << "\n";

        freeListNode(pAnswer);
        pAnswer = nullptr;
        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}
