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
    ListNode *sortList(ListNode *head) {
        struct ListNode *pRetVal = head;

        if (head == nullptr) {
            return pRetVal;
        }

        vector<ListNode *> address;
        while (pRetVal != nullptr) {
            address.emplace_back(pRetVal);
            pRetVal = pRetVal->next;
        }
        sort(address.begin(), address.end(), [](auto n1, auto n2) {
            // ascending order
            return (n1->val < n2->val);
        });

        int len = address.size();
        for (int i = 1; i < len; ++i) {
            address[i - 1]->next = address[i];
        }
        address[len - 1]->next = nullptr;
        pRetVal = address[0];

        return pRetVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        vector<int> node;
    };
    vector<subject> testData{{{4, 2, 1, 3}}, {{-1, 5, 3, 4, 0}}, {{}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [4,2,1,3]
     *  Output: [1,2,3,4]
     *
     *  Input: head = [-1,5,3,4,0]
     *  Output: [-1,0,3,4,5]
     *
     *  Input: head = []
     *  Output: []
     */

    Solution cSolution;
    ListNode *pHead = nullptr;
    ListNode *pAnswer = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].node);
        cout << "Input: head = [";
        printList(pHead);
        cout << "]\n";

        pAnswer = cSolution.sortList(pHead);
        cout << "Output: [";
        printList(pAnswer);
        cout << "]\n";

        cout << "\n";

        freeListNode(pHead);
        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}
