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

int main(int argc, char **argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{0, 3, 1, 0, 4, 5, 2, 0}}, {{0, 1, 0, 3, 0, 2, 2, 0}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [0,3,1,0,4,5,2,0]
     *  Output: [4,11]
     *
     *  Input: head = [0,1,0,3,0,2,2,0]
     *  Output: [1,3,4]
     */

    Solution cSolution;
    ListNode *pHead = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].nums);
        cout << "Input: head = [";
        printList(pHead);
        cout << "]\n";

        pHead = cSolution.mergeNodes(pHead);
        cout << "Output: [";
        printList(pHead);
        cout << "]\n";

        cout << "\n";

        freeListNode(pHead);
        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}
