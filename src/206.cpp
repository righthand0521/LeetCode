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
    ListNode *reverseList(ListNode *head) {
        ListNode *pRetVal = head;

        if (pRetVal == nullptr) {
            return pRetVal;
        }

        ListNode *pPrevious = nullptr;
        ListNode *pNext = pRetVal->next;
        while (pNext != nullptr) {
            pPrevious = pRetVal;
            pRetVal = pNext;
            pNext = pNext->next;
            pRetVal->next = pPrevious;
        }
        head->next = nullptr;

        return pRetVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        vector<int> node;
    };
    vector<subject> testData{{{1, 2, 3, 4, 5}}, {{1, 2}}, {{}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [1,2,3,4,5]
     *  Output: [5,4,3,2,1]
     *
     *  Input: head = [1,2]
     *  Output: [2,1]
     *
     *  Input: head = []
     *  Output: []
     */

    Solution cSolution;
    ListNode *pHead = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].node);
        cout << "Input: head = [";
        printList(pHead);
        cout << "]\n";

        pHead = cSolution.reverseList(pHead);
        cout << "Output: [";
        printList(pHead);
        cout << "]\n";

        cout << "\n";

        freeListNode(pHead);
        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}
