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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* pRetVal = head;

        ListNode* pRemove = head;
        ListNode* pCurrent = head;
        for (int i = 0; i < n; ++i) {
            if (pCurrent == nullptr) {
                break;
            }
            pCurrent = pCurrent->next;
        }
        if (pCurrent == nullptr) {
            pRetVal = pRemove->next;
            delete pRemove;
            pRemove = nullptr;
            return pRetVal;
        }

        while (pCurrent->next != nullptr) {
            pRemove = pRemove->next;
            pCurrent = pCurrent->next;
        }
        pCurrent = pRemove;
        pRemove = pRemove->next;
        pCurrent->next = pRemove->next;
        delete pRemove;
        pRemove = nullptr;

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> node;
        int n;
    };
    vector<subject> testData{{{1, 2, 3, 4, 5}, 2}, {{1}, 1}, {{1, 2}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [1,2,3,4,5], n = 2
     *  Output: [1,2,3,5]
     *
     *  Input: head = [1], n = 1
     *  Output: []
     *
     *  Input: head = [1,2], n = 1
     *  Output: [1]
     */

    Solution cSolution;
    ListNode* pHead = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].node);
        cout << "Input: head = [";
        printList(pHead);
        cout << "], n = " << testData[i].n << "\n";

        pHead = cSolution.removeNthFromEnd(pHead, testData[i].n);
        cout << "Output: [";
        printList(pHead);
        cout << "]\n";

        cout << "\n";

        freeListNode(pHead);
        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}
