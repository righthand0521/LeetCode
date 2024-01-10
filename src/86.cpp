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
    ListNode* partition(ListNode* head, int x) {
        ListNode* pRetVal = head;

        if (head == nullptr) {
            return pRetVal;
        }

        ListNode* pLessHead = new ListNode();
        ListNode* pLess = pLessHead;
        ListNode* pGreatHead = new ListNode();
        ListNode* pGreat = pGreatHead;
        while (pRetVal != nullptr) {
            if (pRetVal->val < x) {
                pLess->next = pRetVal;
                pLess = pLess->next;
            } else {
                pGreat->next = pRetVal;
                pGreat = pGreat->next;
            }
            pRetVal = pRetVal->next;
        }
        pLess->next = pGreatHead->next;
        pGreat->next = nullptr;
        pRetVal = pLessHead->next;

        delete pLessHead;
        delete pGreatHead;

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> node;
        int x;
    };
    vector<subject> testData{{{1, 4, 3, 2, 5, 2}, 3},    {{2, 1}, 2}, {{}, 0}, {{1}, 2}, {{1, 1}, 2}, {{1, 1}, 0},
                             {{3, 5, 8, 5, 10, 2, 1}, 5}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [1,4,3,2,5,2], x = 3
     *  Output: [1,2,2,4,3,5]
     *
     *  Input: head = [2,1], x = 2
     *  Output: [1,2]
     *
     *  Input: head = [], x = 0
     *  Output: []
     *
     *  Input: head = [1], x = 2
     *  Output: [1]
     *
     *  Input: head = [1,1], x = 2
     *  Output: [1,1]
     *
     *  Input: head = [1,1], x = 0
     *  Output: [1,1]
     *
     *  Input: head = [3,5,8,5,10,2,1], x = 5
     *  Output: [3,2,1,5,8,5,10]
     */

    Solution cSolution;
    ListNode* pHead = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].node);
        cout << "Input: head = [";
        printList(pHead);
        cout << "], x = " << testData[i].x << "\n";

        pHead = cSolution.partition(pHead, testData[i].x);
        cout << "Output: [";
        printList(pHead);
        cout << "]\n";

        cout << "\n";

        freeListNode(pHead);
        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}
