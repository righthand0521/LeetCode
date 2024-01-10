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
    ListNode *oddEvenList(ListNode *head) {
        ListNode *pRetVal = head;

        if (head == nullptr) {
            return pRetVal;
        }

        ListNode *pOdd = pRetVal;
        ListNode *pEven = pRetVal->next;
        ListNode *pEvenHead = pRetVal->next;
        while ((pEven != NULL) && (pEven->next != NULL)) {
            pOdd->next = pOdd->next->next;
            pEven->next = pEven->next->next;
            pOdd = pOdd->next;
            pEven = pEven->next;
        }
        pOdd->next = pEvenHead;

        return pRetVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        vector<int> node;
    };
    vector<subject> testData{{{1, 2, 3, 4, 5}}, {{2, 1, 3, 5, 6, 4, 7}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [1,2,3,4,5]
     *  Output: [1,3,5,2,4]
     *
     *  Input: head = [2,1,3,5,6,4,7]
     *  Output: [2,3,6,7,1,5,4]
     */

    Solution cSolution;
    ListNode *pHead = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].node);
        cout << "Input: head = [";
        printList(pHead);
        cout << "]\n";

        pHead = cSolution.oddEvenList(pHead);
        cout << "Output: [";
        printList(pHead);
        cout << "]\n";

        cout << "\n";

        freeListNode(pHead);
        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}
