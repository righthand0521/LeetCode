#include <algorithm>
#include <iostream>
#include <unordered_set>
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
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        ListNode* pRetVal = head;

        unordered_set<int> valuesToRemove(nums.begin(), nums.end());

        while ((pRetVal != nullptr) && (valuesToRemove.count(pRetVal->val) > 0)) {
            ListNode* pPrevious = pRetVal;
            pRetVal = pRetVal->next;
            delete pPrevious;
        }
        if (pRetVal == nullptr) {
            return pRetVal;
        }

        ListNode* pCurrent = pRetVal;
        while (pCurrent->next != nullptr) {
            if (valuesToRemove.count(pCurrent->next->val) > 0) {
                ListNode* pDelete = pCurrent->next;
                pCurrent->next = pCurrent->next->next;
                delete pDelete;
            } else {
                pCurrent = pCurrent->next;
            }
        }

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        vector<int> node;
    };
    vector<subject> testData{{{1, 2, 3}, {1, 2, 3, 4, 5}}, {{1}, {1, 2, 1, 2, 1, 2}}, {{5}, {1, 2, 3, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,3], head = [1,2,3,4,5]
     *  Output: [4,5]
     *
     *  Input: nums = [1], head = [1,2,1,2,1,2]
     *  Output: [2,2,2]
     *
     *  Input: nums = [5], head = [1,2,3,4]
     *  Output: [1,2,3,4]
     */

    Solution cSolution;
    ListNode* pAnswer = nullptr;
    ListNode* pHead = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].node);
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], head = [";
        printList(pHead);
        cout << "]\n";

        pAnswer = cSolution.modifiedList(testData[i].nums, pHead);
        cout << "Output: [";
        printList(pAnswer);
        cout << "]\n";

        cout << "\n";

        freeListNode(pAnswer);
        pAnswer = nullptr;
        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}
