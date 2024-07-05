#include <algorithm>
#include <iostream>
#include <limits>
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
    vector<int> nodesBetweenCriticalPoints(ListNode *head) {
        vector<int> retVal(2, -1);

        // The number of nodes in the list is in the range [2, 10^5].
        int currentIndex = 1;
        ListNode *pCurrent = head->next;
        ListNode *pPrevious = head;

        int firstCriticalIndex = 0;
        int previousCriticalIndex = 0;
        int minDistance = numeric_limits<int>::max();
        while (pCurrent->next != nullptr) {
            if (((pCurrent->val < pPrevious->val) && (pCurrent->val < pCurrent->next->val)) ||
                ((pCurrent->val > pPrevious->val) && (pCurrent->val > pCurrent->next->val))) {
                if (previousCriticalIndex == 0) {
                    previousCriticalIndex = currentIndex;
                    firstCriticalIndex = currentIndex;
                } else {
                    minDistance = min(minDistance, currentIndex - previousCriticalIndex);
                    previousCriticalIndex = currentIndex;
                }
            }

            currentIndex += 1;
            pPrevious = pCurrent;
            pCurrent = pCurrent->next;
        }

        if (minDistance != numeric_limits<int>::max()) {
            int maxDistance = previousCriticalIndex - firstCriticalIndex;
            retVal[0] = minDistance;
            retVal[1] = maxDistance;
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{3, 1}}, {{5, 3, 1, 2, 5, 1, 2}}, {{1, 3, 2, 2, 3, 2, 2, 2, 7}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [3,1]
     *  Output: [-1,-1]
     *
     *  Input: head = [5,3,1,2,5,1,2]
     *  Output: [1,3]
     *
     *  Input: head = [1,3,2,2,3,2,2,2,7]
     *  Output: [3,3]
     */

    Solution cSolution;
    vector<int> answer;
    ListNode *pHead = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].nums);
        cout << "Input: head = [";
        printList(pHead);
        cout << "]\n";

        answer = cSolution.nodesBetweenCriticalPoints(pHead);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";

        freeListNode(pHead);
        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}
