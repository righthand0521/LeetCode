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
    ListNode *swapPairs(ListNode *head) {
        ListNode *pRetVal = head;

        if ((pRetVal == NULL) || (pRetVal->next == NULL)) {
            return pRetVal;
        }

        pRetVal = head->next;
        ListNode *p1 = head;
        ListNode *p2 = head->next;
        ListNode *pPrevious = NULL;
        while (p2 != NULL) {
            if (pPrevious != NULL) {
                pPrevious->next = p2;
            }
            p1->next = p2->next;
            p2->next = p1;

            pPrevious = p1;
            p1 = p1->next;
            if (p1 == NULL) {
                break;
            }
            p2 = p1->next;
        }

        return pRetVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        vector<int> node;
        int k;
    };
    vector<subject> testData{{{1, 2, 3, 4}}, {{}}, {{1}}, {{1, 2, 3, 4, 5}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [1,2,3,4]
     *  Output: [2,1,4,3]
     *
     *  Input: head = []
     *  Output: []
     *
     *  Input: head = [1]
     *  Output: [1]
     */

    Solution cSolution;
    ListNode *pHead = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].node);
        cout << "Input: head = [";
        printList(pHead);
        cout << "]\n";

        pHead = cSolution.swapPairs(pHead);
        cout << "Output: [";
        printList(pHead);
        cout << "]\n";

        cout << "\n";

        freeListNode(pHead);
        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}
