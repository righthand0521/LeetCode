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
        ListNode* pRetVal = head;

        if ((head == nullptr) || (head->next == nullptr)) {
            return pRetVal;
        }

        ListNode* pCurrent = head->next;
        ListNode* pPrevious = head;
        while (pCurrent != nullptr) {
            if (pCurrent->val == pPrevious->val) {
                pPrevious->next = pCurrent->next;
                delete pCurrent;
                pCurrent = pPrevious->next;
            } else {
                pPrevious = pCurrent;
                pCurrent = pCurrent->next;
            }
        }

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> node;
    };
    vector<subject> testData{{{1, 1, 2}}, {{1, 1, 2, 3, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [1,1,2]
     *  Output: [1,2]
     *
     *  Input: head = [1,1,2,3,3]
     *  Output: [1,2,3]
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
