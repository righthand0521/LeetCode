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
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        ListNode* pRetVal = list1;

        struct ListNode* pPrevious = nullptr;
        struct ListNode* pNext1 = list1;
        for (int i = 0; i < a; ++i) {
            pPrevious = pNext1;
            pNext1 = pNext1->next;
        }
        struct ListNode* pNext2 = pPrevious;

        for (int i = a; i <= b; ++i) {
            pPrevious->next = pNext1->next;
            delete pNext1;
            pNext1 = pPrevious->next;
        }

        pNext2->next = list2;
        while (pNext2 != nullptr) {
            pPrevious = pNext2;
            pNext2 = pNext2->next;
        }
        pPrevious->next = pNext1;

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> node1;
        int a;
        int b;
        vector<int> node2;
    };
    vector<subject> testData{{{0, 1, 2, 3, 4, 5}, 3, 4, {1000000, 1000001, 1000002}},
                             {{0, 1, 2, 3, 4, 5, 6}, 2, 5, {1000000, 1000001, 1000002, 1000003, 1000004}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: list1 = [0,1,2,3,4,5], a = 3, b = 4, list2 = [1000000,1000001,1000002]
     *  Output: [0,1,2,1000000,1000001,1000002,5]
     *
     *  Input: list1 = [0,1,2,3,4,5,6], a = 2, b = 5, list2 = [1000000,1000001,1000002,1000003,1000004]
     *  Output: [0,1,1000000,1000001,1000002,1000003,1000004,6]
     */

    Solution cSolution;
    ListNode* pAnswer = nullptr;
    ListNode* list1 = nullptr;
    ListNode* list2 = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        list1 = buildList(testData[i].node1);
        list2 = buildList(testData[i].node2);
        cout << "Input: list1 = [";
        printList(list1);
        cout << "], a = " << testData[i].a << ", b = " << testData[i].b << ", list2 = [";
        printList(list2);
        cout << "]\n";

        pAnswer = cSolution.mergeInBetween(list1, testData[i].a, testData[i].b, list2);
        cout << "Output: [";
        printList(pAnswer);
        cout << "]\n";

        cout << "\n";

        freeListNode(list1);
        list1 = nullptr;
        list2 = nullptr;
        pAnswer = nullptr;
    }

    return EXIT_SUCCESS;
}
