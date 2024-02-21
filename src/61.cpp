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
    ListNode* rotateRight(ListNode* head, int k) {
        ListNode* pRetVal = head;

        if ((pRetVal == nullptr) || (pRetVal->next == nullptr)) {
            return pRetVal;
        }

        ListNode* pCurrent = head;
        int headSize = 0;
        while (pCurrent->next != nullptr) {
            ++headSize;
            pCurrent = pCurrent->next;
        }
        k = headSize - (k % (headSize + 1));

        pCurrent->next = head;
        while (k--) {
            head = head->next;
        }
        pCurrent = head;
        head = head->next;
        pCurrent->next = nullptr;
        pRetVal = head;

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> node;
        int k;
    };
    vector<subject> testData{{{1, 2, 3, 4, 5}, 2}, {{0, 1, 2}, 4}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [1,2,3,4,5], k = 2
     *  Output: [4,5,1,2,3]
     *
     *  Input: head = [0,1,2], k = 4
     *  Output: [2,0,1]
     */

    Solution cSolution;
    ListNode* pAnswer = nullptr;
    ListNode* pHead = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].node);
        cout << "Input: head = [";
        printList(pHead);
        cout << "], k = " << testData[i].k << "\n";

        pAnswer = cSolution.rotateRight(pHead, testData[i].k);
        cout << "Output: [";
        printList(pAnswer);
        cout << "]\n";

        cout << "\n";

        freeListNode(pAnswer);
        pAnswer = nullptr;
        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}
