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
    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        vector<ListNode*> retVal(k, nullptr);

        int nodeCount = 0;
        ListNode* pCurrent = head;
        while (pCurrent != nullptr) {
            ++nodeCount;
            pCurrent = pCurrent->next;
        }
        int quotient = nodeCount / k;
        int remainder = nodeCount % k;

        pCurrent = head;
        for (int i = 0; i < k; ++i) {
            if (pCurrent == nullptr) {
                break;
            }

            retVal[i] = pCurrent;
            int partsCount = quotient + ((remainder > i) ? (1) : (0));
            for (int j = 0; j < partsCount - 1; ++j) {
                if (pCurrent != nullptr) {
                    pCurrent = pCurrent->next;
                }
            }
            ListNode* pNext = pCurrent->next;
            pCurrent->next = nullptr;
            pCurrent = pNext;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> node;
        int k;
    };
    vector<subject> testData{{{1, 2, 3}, 5}, {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [1,2,3], k = 5
     *  Output: [[1],[2],[3],[],[]]
     *
     *  Input: head = [1,2,3,4,5,6,7,8,9,10], k = 3
     *  Output: [[1,2,3,4],[5,6,7],[8,9,10]]
     */

    Solution cSolution;
    ListNode* pHead = nullptr;
    vector<ListNode*> pAnswer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].node);
        cout << "Input: head = [";
        printList(pHead);
        cout << "], k = " << testData[i].k << "\n";

        pAnswer = cSolution.splitListToParts(pHead, testData[i].k);

        cout << "Output: [";
        for (long unsigned int j = 0; j < pAnswer.size(); ++j) {
            cout << (j != 0 ? "," : "") << "[";
            printList(pAnswer[j]);
            cout << "]";
            freeListNode(pAnswer[j]);
            pAnswer[j] = nullptr;
        }
        cout << "]\n";

        cout << "\n";

        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}
