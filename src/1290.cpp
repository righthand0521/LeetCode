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
    int getDecimalValue(ListNode* head) {
        int retVal = head->val;

        ListNode* pCurrent = head->next;
        while (pCurrent != nullptr) {
            retVal = (retVal << 1) | pCurrent->val;
            pCurrent = pCurrent->next;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> node;
    };
    vector<subject> testData{{{1, 0, 1}}, {{0}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [1,0,1]
     *  Output: 5
     *
     *  Input: head = [0]
     *  Output: 0
     */

    Solution cSolution;
    ListNode* pHead = nullptr;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].node);
        cout << "Input: head = [";
        printList(pHead);
        cout << "]\n";

        answer = cSolution.getDecimalValue(pHead);
        cout << "Output: " << answer << "\n";

        cout << "\n";

        freeListNode(pHead);
        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}
