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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *pRetVal = nullptr;

        int lenA = 0;
        ListNode *pCurrentA = headA;
        while (pCurrentA->next != nullptr) {
            lenA++;
            pCurrentA = pCurrentA->next;
        }

        int lenB = 0;
        ListNode *pCurrentB = headB;
        while (pCurrentB->next != nullptr) {
            lenB++;
            pCurrentB = pCurrentB->next;
        }

        if (pCurrentA != pCurrentB) {
            return pRetVal;
        }

        int diff = (lenA > lenB) ? (lenA - lenB) : (lenB - lenA);

        pRetVal = (lenA > lenB) ? headA : headB;
        for (int i = 0; i < diff; ++i) {
            pRetVal = pRetVal->next;
        }

        pCurrentA = (lenA > lenB) ? pRetVal : headA;
        pCurrentB = (lenA > lenB) ? headB : pRetVal;
        while (pRetVal != nullptr) {
            if (pCurrentA == pCurrentB) {
                return pRetVal;
            }
            pRetVal = pRetVal->next;
            pCurrentA = pCurrentA->next;
            pCurrentB = pCurrentB->next;
        }

        return pRetVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        int intersectVal;
        vector<int> nodeA;
        vector<int> nodeB;
        int skipA;
        int skipB;
    };
    vector<subject> testData{{8, {4, 1, 8, 4, 5}, {5, 6, 1, 8, 4, 5}, 2, 3},
                             {2, {1, 9, 1, 2, 4}, {3, 2, 4}, 3, 1},
                             {0, {2, 6, 4}, {1, 5}, 3, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2, skipB = 3
     *  Output: Intersected at '8'
     *
     *  Input: intersectVal = 2, listA = [1,9,1,2,4], listB = [3,2,4], skipA = 3, skipB = 1
     *  Output: Intersected at '2'
     *
     *  Input: intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
     *  Output: No intersection
     */

    Solution cSolution;
    ListNode *pIntersect = nullptr;
    ListNode *pHeadA = nullptr;
    ListNode *pHeadB = nullptr;
    ListNode *pAnswer = nullptr;
    ListNode *pFree = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: intersectVal = " << testData[i].intersectVal << ", ";
        for (long unsigned int j = testData[i].skipA; j < testData[i].nodeA.size(); ++j) {
            pIntersect = addValueToEndListNode(pIntersect, testData[i].nodeA[j]);
        }
        for (int j = 0; j < testData[i].skipA; ++j) {
            pHeadA = addValueToEndListNode(pHeadA, testData[i].nodeA[j]);
        }
        pHeadA = mergeListNode(pHeadA, pIntersect);
        cout << "listA = [";
        printList(pHeadA);
        cout << "], ";
        for (int j = 0; j < testData[i].skipB; ++j) {
            pHeadB = addValueToEndListNode(pHeadB, testData[i].nodeB[j]);
        }
        pHeadB = mergeListNode(pHeadB, pIntersect);
        cout << "listB = [";
        printList(pHeadB);
        cout << "], ";
        cout << "skipA = " << testData[i].skipA << ", ";
        cout << "skipB = " << testData[i].skipB << "\n";

        cout << "Output: ";
        pAnswer = cSolution.getIntersectionNode(pHeadA, pHeadB);
        if (pAnswer == nullptr) {
            cout << "No intersection" << "\n";
        } else {
            cout << "Intersected at '" << pAnswer->val << "'\n";
        }

        cout << "\n";

        pFree = pHeadA;
        for (int j = 1; j < testData[i].skipA; ++j) {
            pFree = pFree->next;
        }
        pFree->next = nullptr;
        pFree = pHeadB;
        for (int j = 1; j < testData[i].skipB; ++j) {
            pFree = pFree->next;
        }
        pFree->next = nullptr;
        freeListNode(pIntersect);
        pIntersect = nullptr;
        freeListNode(pHeadA);
        pHeadA = nullptr;
        freeListNode(pHeadB);
        pHeadB = nullptr;
    }

    return EXIT_SUCCESS;
}
