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

int main(int argc, char** argv) {
    struct subject {
        vector<int> head;
    };
    vector<subject> testData{{{5, 2, 6, 3, 9, 1, 7, 3, 8, 4}}, {{1, 1, 0, 6}}, {{1, 1, 0, 6, 5}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [5,2,6,3,9,1,7,3,8,4]
     *  Output: [5,6,2,3,9,1,4,8,3,7]
     *
     *  Input: head = [1,1,0,6]
     *  Output: [1,0,1,6]
     *
     *  Input: head = [1,1,0,6,5]
     *  Output: [1,0,1,5,6]
     */

    Solution cSolution;
    ListNode* pHead = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].head);
        cout << "Input: head = [";
        printList(pHead);
        cout << "]\n";

        pHead = cSolution.reverseEvenLengthGroups(pHead);
        cout << "Output: [";
        printList(pHead);
        cout << "]\n";

        cout << "\n";

        freeListNode(pHead);
        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}
