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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* pRetVal = nullptr;
        pRetVal = new ListNode();

        ListNode* pCurrent = pRetVal;
        ListNode* pNew = nullptr;
        ListNode* pNext1 = list1;
        ListNode* pNext2 = list2;
        while ((pNext1 != nullptr) && (pNext2 != nullptr)) {
            if (pNext1->val < pNext2->val) {
                pNew = new ListNode(pNext1->val);
                pNext1 = pNext1->next;
            } else {
                pNew = new ListNode(pNext2->val);
                pNext2 = pNext2->next;
            }
            pCurrent->next = pNew;
            pCurrent = pCurrent->next;
        }
        while (pNext1 != nullptr) {
            pNew = new ListNode(pNext1->val);
            pNext1 = pNext1->next;
            pCurrent->next = pNew;
            pCurrent = pCurrent->next;
        }
        while (pNext2 != nullptr) {
            pNew = new ListNode(pNext2->val);
            pNext2 = pNext2->next;
            pCurrent->next = pNew;
            pCurrent = pCurrent->next;
        }

        pCurrent = pRetVal;
        pRetVal = pRetVal->next;
        delete pCurrent;

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> node1;
        vector<int> node2;
    };
    vector<subject> testData{{{{1, 2, 4}, {1, 3, 4}}, {{}, {}}, {{}, {0}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: list1 = [1,2,4], list2 = [1,3,4]
     *  Output: [1,1,2,3,4,4]
     *
     *  Input: list1 = [], list2 = []
     *  Output: []
     *
     *  Input: list1 = [], list2 = [0]
     *  Output: [0]
     */

    Solution cSolution;
    ListNode* list1 = nullptr;
    ListNode* list2 = nullptr;
    ListNode* pAnswer = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        list1 = buildList(testData[i].node1);
        list2 = buildList(testData[i].node2);
        cout << "Input: list1 = [";
        printList(list1);
        cout << "], list2 = [";
        printList(list2);
        cout << "]\n";

        pAnswer = cSolution.mergeTwoLists(list1, list2);
        cout << "Output: [";
        printList(pAnswer);
        cout << "]\n";

        cout << "\n";

        freeListNode(list1);
        list1 = nullptr;
        freeListNode(list2);
        list2 = nullptr;
        freeListNode(pAnswer);
        pAnswer = nullptr;
    }

    return EXIT_SUCCESS;
}
