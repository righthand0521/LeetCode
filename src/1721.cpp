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
    ListNode* swapNodes(ListNode* head, int k) {
        ListNode* pRetVal = head;

        ListNode* pCurrent = head;
        ListNode* pSwapHead = NULL;
        ListNode* pSwapTail = NULL;

        int idx = 0;
        while (pCurrent != NULL) {
            ++idx;
            if (idx >= k) {
                break;
            }

            pCurrent = pCurrent->next;
        }
        pSwapHead = pCurrent;

        pCurrent = pCurrent->next;
        pSwapTail = head;
        while (pCurrent != NULL) {
            pCurrent = pCurrent->next;
            pSwapTail = pSwapTail->next;
        }

        int tmp = pSwapHead->val;
        pSwapHead->val = pSwapTail->val;
        pSwapTail->val = tmp;

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> node;
        int k;
    };
    vector<subject> testData{{{1, 2, 3, 4, 5}, 2}, {{7, 9, 6, 6, 7, 8, 3, 0, 9, 5}, 5}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [1,2,3,4,5], k = 2
     *  Output: [1,4,3,2,5]
     *
     *  Input: head = [7,9,6,6,7,8,3,0,9,5], k = 5
     *  Output: [7,9,6,6,8,7,3,0,9,5]
     */

    Solution cSolution;
    ListNode* pAnswer = nullptr;
    ListNode* pHead = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].node);
        cout << "Input: head = [";
        printList(pHead);
        cout << "], k = " << testData[i].k << "\n";

        pAnswer = cSolution.swapNodes(pHead, testData[i].k);
        cout << "Output: [";
        printList(pAnswer);
        cout << "]\n";

        cout << "\n";

        freeListNode(pAnswer);
        pAnswer = nullptr;
    }

    return EXIT_SUCCESS;
}
