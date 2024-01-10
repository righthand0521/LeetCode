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
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
   public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *pRetVal = nullptr;

        if (head == nullptr) {
            return pRetVal;
        }

        ListNode *pOne = head;
        ListNode *pTwo = head;
        while ((pOne->next != nullptr) && (pTwo->next != nullptr) && (pTwo->next->next != nullptr)) {
            pOne = pOne->next;
            pTwo = pTwo->next->next;
            if (pOne == pTwo) {
                pRetVal = head;
                break;
            }
        }
        if (pRetVal != head) {
            return pRetVal;
        }

        while (pRetVal != pOne) {
            pRetVal = pRetVal->next;
            pOne = pOne->next;
        }

        return pRetVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        vector<int> node;
        int pos;
    };
    vector<subject> testData{
        {{3, 2, 0, -4}, 1}, {{1, 2}, 0}, {{1}, LIST_VALID_CYCLE_INDEX}, {{1, 2}, LIST_VALID_CYCLE_INDEX}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [3,2,0,-4], pos = 1
     *  Output: tail connects to node index 1
     *
     *  Input: head = [1,2], pos = 0
     *  Output: tail connects to node index 0
     *
     *  Input: head = [1], pos = -1
     *  Output: no cycle
     */

    Solution cSolution;
    ListNode *pHead = nullptr;
    ListNode *pAnswer = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].node);
        cout << "Input: head = [";
        printList(pHead);
        cout << "], pos = " << testData[i].pos << "\n";
        if (testData[i].pos != LIST_VALID_CYCLE_INDEX) {
            pHead = addListNodeCycle(pHead, testData[i].pos);
        }

        pAnswer = cSolution.detectCycle(pHead);
        if (pAnswer == nullptr) {
            cout << "Output: no cycle\n";
        } else {
            cout << "Output: tail connects to node index " << testData[i].pos << "\n";
        }

        cout << "\n";

        if (testData[i].pos != LIST_VALID_CYCLE_INDEX) {
            pHead = removeListNodeCycle(pHead, testData[i].pos);
        }
        freeListNode(pHead);
        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}
