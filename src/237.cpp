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
    void deleteNode(ListNode *node) {
        if ((node == nullptr) || (node->next == nullptr)) {
            return;
        }

        ListNode *p = node->next;
        *node = *node->next;
        delete p;
    }
};

int main(int argc, char **argv) {
    struct subject {
        vector<int> node;
        int deleteVal;
    };
    vector<subject> testData{{{4, 5, 1, 9}, 5}, {{4, 5, 1, 9}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [4,5,1,9], node = 5
     *  Output: [4,1,9]
     *
     *  Input: head = [4,5,1,9], node = 1
     *  Output: [4,5,9]
     */

    Solution cSolution;
    ListNode *pNode = nullptr;
    ListNode *pHead = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].node);
        cout << "Input: head = [";
        printList(pHead);
        cout << "]\n";

        pNode = pHead;
        while (pNode != nullptr) {
            if (pNode->val == testData[i].deleteVal) {
                break;
            }
            pNode = pNode->next;
        }
        cSolution.deleteNode(pNode);
        cout << "Output: [";
        printList(pHead);
        cout << "]\n";

        cout << "\n";

        freeListNode(pHead);
        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}
