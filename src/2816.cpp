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

int main(int argc, char** argv) {
    struct subject {
        vector<int> node;
    };
    vector<subject> testData{{{1, 8, 9}}, {{9, 9, 9}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [1,8,9]
     *  Output: [3,7,8]
     *
     *  Input: head = [9,9,9]
     *  Output: [1,9,9,8]
     */

    Solution cSolution;
    ListNode* pHead = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].node);
        cout << "Input: head = [";
        printList(pHead);
        cout << "]\n";

        pHead = cSolution.doubleIt(pHead);
        cout << "Output: [";
        printList(pHead);
        cout << "]\n";

        cout << "\n";

        freeListNode(pHead);
        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}
