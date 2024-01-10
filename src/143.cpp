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
    void reorderList(ListNode* head) {
        if (head == NULL) {
            return;
        }

        vector<ListNode*> address;
        ListNode* pNext = head;
        while (pNext != NULL) {
            address.emplace_back(pNext);
            pNext = pNext->next;
        }

        int left = 0;
        int right = address.size() - 1;
        while (left < right) {
            address[left]->next = address[right];
            ++left;
            if (left == right) {
                break;
            }

            address[right]->next = address[left];
            --right;
        }
        address[left]->next = NULL;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> head;
    };
    vector<subject> testData{{{1, 2, 3, 4}}, {{1, 2, 3, 4, 5}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [1,2,3,4]
     *  Output: [1,4,2,3]
     *
     *  Input: head = [1,2,3,4,5]
     *  Output: [1,5,2,4,3]
     */

    Solution cSolution;
    ListNode* pHead = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].head);
        cout << "Input: head = [";
        printList(pHead);
        cout << "]\n";

        cSolution.reorderList(pHead);
        cout << "Output: [";
        printList(pHead);
        cout << "]\n";

        cout << "\n";

        freeListNode(pHead);
        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}
