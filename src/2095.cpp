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
    ListNode* deleteMiddle(ListNode* head) {
        ListNode* pRetVal = head;

        // The number of nodes is 1
        if (pRetVal->next == nullptr) {
            delete pRetVal;
            pRetVal = nullptr;
            return pRetVal;
        }

        // Middle of the Linked List: https://leetcode.com/problems/middle-of-the-linked-list/
        ListNode* pOne = pRetVal;
        ListNode* pTwo = pRetVal;
        while ((pTwo != nullptr) && (pTwo->next != nullptr)) {
            pOne = pOne->next;
            pTwo = pTwo->next;
            if (pTwo != nullptr) {
                pTwo = pTwo->next;
            }
        }

        // The number of nodes is 2
        if (pOne->next == nullptr) {
            pRetVal->next = nullptr;
            delete pOne;
            pOne = nullptr;
            return pRetVal;
        }

        // Delete Node in a Linked List: https://leetcode.com/problems/delete-node-in-a-linked-list/
        ListNode* pFree = pOne->next;
        *pOne = *pOne->next;
        delete pFree;
        pFree = nullptr;

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> node;
    };
    vector<subject> testData{{{1, 3, 4, 7, 1, 2, 6}}, {{1, 2, 3, 4}}, {{2, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [1,3,4,7,1,2,6]
     *  Output: [1,3,4,1,2,6]
     *
     *  Input: head = [1,2,3,4]
     *  Output: [1,2,4]
     *
     *  Input: head = [2,1]
     *  Output: [2]
     */

    Solution cSolution;
    ListNode* pHead = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].node);
        cout << "Input: head = [";
        printList(pHead);
        cout << "]\n";

        pHead = cSolution.deleteMiddle(pHead);
        cout << "Output: [";
        printList(pHead);
        cout << "]\n";

        cout << "\n";

        freeListNode(pHead);
        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}
