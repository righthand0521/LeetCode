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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* pRetVal = nullptr;

        pRetVal = new ListNode(0);

        ListNode* pCurrent = pRetVal;
        int carry = 0;
        while ((l1 != nullptr) || (l2 != nullptr)) {
            int sum = 0;

            if (l1 != nullptr) {
                sum += l1->val;
                l1 = l1->next;
            }

            if (l2 != nullptr) {
                sum += l2->val;
                l2 = l2->next;
            }

            sum += carry;
            carry = 0;
            if (sum >= 10) {
                sum %= 10;
                carry = 1;
            }

            pCurrent->next = new ListNode(sum);
            pCurrent = pCurrent->next;
        }
        if (carry == 1) {
            pCurrent->next = new ListNode(carry);
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
    vector<subject> testData{{{2, 4, 3}, {5, 6, 4}},
                             {{0}, {0}},
                             {{9, 9, 9, 9, 9, 9, 9}, {9, 9, 9, 9}},
                             {{7, 1, 6}, {5, 9, 2}},
                             {{9, 7, 8}, {6, 8, 5}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: l1 = [2,4,3], l2 = [5,6,4]
     *  Output: [7,0,8]
     *
     *  Input: l1 = [0], l2 = [0]
     *  Output: [0]
     *
     *  Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
     *  Output: [8,9,9,9,0,0,0,1]
     *
     *  Input: l1 = [7,1,6], l2 = [5,9,2]
     *  Output: [2,1,9]
     *
     *  Input: l1 = [9,7,8], l2 = [6,8,5]
     *  Output: [5,6,4,1]
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
        cout << "], list2 = [";
        printList(list2);
        cout << "]\n";

        pAnswer = cSolution.addTwoNumbers(list1, list2);
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
