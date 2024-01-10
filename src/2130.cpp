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
    int pairSum(ListNode* head) {
        int retVal = 0;

        vector<int> value;
        ListNode* pCurrent = head;
        while (pCurrent != nullptr) {
            value.emplace_back(pCurrent->val);
            pCurrent = pCurrent->next;
        }

        int i = 0;
        int j = value.size() - 1;
        while (i < j) {
            retVal = max(retVal, value[i++] + value[j--]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> node;
        int k;
    };
    vector<subject> testData{{{5, 4, 2, 1}}, {{4, 2, 2, 3}}, {{1, 100000}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [5,4,2,1]
     *  Output: 6
     *
     *  Input: head = [4,2,2,3]
     *  Output: 7
     *
     *  Input: head = [1,100000]
     *  Output: 100001
     */

    Solution cSolution;
    ListNode* pHead = nullptr;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].node);
        cout << "Input: head = [";
        printList(pHead);
        cout << "]\n";

        answer = cSolution.pairSum(pHead);
        cout << "Output: " << answer << "\n";

        cout << "\n";

        freeListNode(pHead);
        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}
