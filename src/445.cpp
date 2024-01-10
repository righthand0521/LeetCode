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

        pRetVal = l1;
        vector<int> list1;
        while (pRetVal != nullptr) {
            list1.emplace_back(pRetVal->val);
            pRetVal = pRetVal->next;
        }

        pRetVal = l2;
        vector<int> list2;
        while (pRetVal != nullptr) {
            list2.emplace_back(pRetVal->val);
            pRetVal = pRetVal->next;
        }

        pRetVal = new ListNode();
        int carry = 0;
        while ((list1.empty() == false) || (list2.empty() == false)) {
            int sum = carry;
            if (list1.empty() == false) {
                sum += list1.back();
                list1.pop_back();
            }
            if (list2.empty() == false) {
                sum += list2.back();
                list2.pop_back();
            }
            pRetVal->val = sum % 10;

            carry = sum / 10;
            ListNode* pNode = new ListNode(carry);
            pNode->next = pRetVal;
            pRetVal = pNode;
        }

        if (carry == 0) {
            ListNode* pFree = pRetVal;
            pRetVal = pRetVal->next;
            delete pFree;
        }

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> node1;
        vector<int> node2;
    };
    vector<subject> testData{{{7, 2, 4, 3}, {5, 6, 4}}, {{2, 4, 3}, {5, 6, 4}}, {{0}, {0}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: l1 = [7,2,4,3], l2 = [5,6,4]
     *  Output: [7,8,0,7]
     *
     *  Input: l1 = [2,4,3], l2 = [5,6,4]
     *  Output: [8,0,7]
     *
     *  Input: l1 = [0], l2 = [0]
     *  Output: [0]
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
