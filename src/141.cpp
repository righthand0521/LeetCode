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
    bool hasCycle(ListNode* head) {
        bool retVal = false;

        if ((head == nullptr) || (head->next == nullptr)) {
            return retVal;
        }

        ListNode* pOne = head;
        ListNode* pTwo = head->next;
        while (pOne != pTwo) {
            if ((pTwo == nullptr) || (pTwo->next == nullptr)) {
                return retVal;
            }
            pOne = pOne->next;
            pTwo = pTwo->next->next;
        }
        retVal = true;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> node;
        int pos;
    };
    vector<subject> testData{
        {{3, 2, 0, -4}, 1}, {{1, 2}, 0}, {{1}, LIST_VALID_CYCLE_INDEX}, {{1, 2}, LIST_VALID_CYCLE_INDEX}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [3,2,0,-4], pos = 1
     *  Output: true
     *
     *  Input: head = [1,2], pos = 0
     *  Output: true
     *
     *  Input: head = [1], pos = -1
     *  Output: false
     *
     *  Input: head = [1,2], pos = -1
     *  Output: false
     */

    Solution cSolution;
    ListNode* pHead = nullptr;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].node);
        cout << "Input: head = [";
        printList(pHead);
        cout << "], pos = " << testData[i].pos << "\n";
        if (testData[i].pos != LIST_VALID_CYCLE_INDEX) {
            pHead = addListNodeCycle(pHead, testData[i].pos);
        }

        answer = cSolution.hasCycle(pHead);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";

        if (testData[i].pos != LIST_VALID_CYCLE_INDEX) {
            pHead = removeListNodeCycle(pHead, testData[i].pos);
        }
        freeListNode(pHead);
        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}
