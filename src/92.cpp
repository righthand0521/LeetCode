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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode* pRetVal = head;

        ListNode* pTmp = new ListNode(-1);
        pTmp->next = head;

        ListNode* pPrevious = pTmp;
        for (int i = 0; i < left - 1; ++i) {
            pPrevious = pPrevious->next;
        }

        ListNode* pCurrent = pPrevious->next;

        ListNode* pNext;
        for (int i = left; i < right; ++i) {
            pNext = pCurrent->next;
            pCurrent->next = pNext->next;
            pNext->next = pPrevious->next;
            pPrevious->next = pNext;
        }

        pRetVal = pTmp->next;
        delete pTmp;

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> head;
        int left;
        int right;
    };
    vector<subject> testData{{{1, 2, 3, 4, 5}, 2, 4}, {{5}, 1, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [1,2,3,4,5], left = 2, right = 4
     *  Output: [1,4,3,2,5]
     *
     *  Input: head = [5], left = 1, right = 1
     *  Output: [5]
     */

    Solution cSolution;
    ListNode* pHead = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].head);
        cout << "Input: head = [";
        printList(pHead);
        cout << "], left = " << testData[i].left << ", right = " << testData[i].right << "\n";

        pHead = cSolution.reverseBetween(pHead, testData[i].left, testData[i].right);
        cout << "Output: [";
        printList(pHead);
        cout << "]\n";

        cout << "\n";

        freeListNode(pHead);
        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}
