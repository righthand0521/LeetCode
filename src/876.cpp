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
    ListNode *middleNode(ListNode *head) {
        ListNode *pRetVal = head;

        if ((head == nullptr) || (head->next == nullptr)) {
            return pRetVal;
        }

        ListNode *pOne = head;
        ListNode *pTwo = head;
        while ((pTwo != nullptr) && (pTwo->next != nullptr)) {
            pOne = pOne->next;
            pTwo = pTwo->next;
            if (pTwo != nullptr) {
                pTwo = pTwo->next;
            }
        }
        pRetVal = pOne;

        return pRetVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        vector<int> node;
    };
    vector<subject> testData{{{1, 2, 3, 4, 5}}, {{1, 2, 3, 4, 5, 6}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [1,2,3,4,5]
     *  Output: [3,4,5]
     *
     *  Input: head = [1,2,3,4,5,6]
     *  Output: [4,5,6]
     */

    Solution cSolution;
    ListNode *pHead = nullptr;
    ListNode *pAnswer = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].node);
        cout << "Input: head = [";
        printList(pHead);
        cout << "]\n";

        pAnswer = cSolution.middleNode(pHead);
        cout << "Output: [";
        printList(pAnswer);
        cout << "]\n";

        cout << "\n";

        freeListNode(pHead);
        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}
