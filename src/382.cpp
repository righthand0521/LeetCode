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
    vector<int> nums;
    Solution(ListNode *head) {
        ListNode *pNext = head;
        while (pNext != nullptr) {
            nums.emplace_back(pNext->val);
            pNext = pNext->next;
        }
    }
    int getRandom() {
        int retVal = nums[rand() % nums.size()];

        return retVal;
    }
};
/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */

int main(int argc, char **argv) {
    struct subject {
        vector<string> method;
        vector<vector<int>> value;
    };
    vector<subject> testData{{{"Solution", "getRandom", "getRandom", "getRandom", "getRandom", "getRandom"},
                              {{1, 2, 3}, {}, {}, {}, {}, {}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["Solution", "getRandom", "getRandom", "getRandom", "getRandom", "getRandom"]
     *  [[[1, 2, 3]], [], [], [], [], []]
     *  Output
     *  [null, 1, 3, 2, 2, 3]
     */

    ListNode *pHead = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input\n[";
        for (long unsigned int j = 0; j < testData[i].method.size(); ++j) {
            cout << (j == 0 ? "" : ", ") << "\"" << testData[i].method[j] << "\"";
        }
        cout << "]\n[";
        for (long unsigned int j = 0; j < testData[i].method.size(); ++j) {
            if (testData[i].method[j] == "Solution") {
                cout << "[[";
                for (long unsigned int k = 0; k < testData[i].value[j].size(); ++k) {
                    cout << (k == 0 ? "" : ", ") << testData[i].value[j][k];
                }
                cout << "]]";
            } else if (testData[i].method[j] == "getRandom") {
                cout << (j == 0 ? "" : ", ") << "[]";
            }
        }
        cout << "]\n";

        cout << "Output\n[";
        pHead = buildList(testData[i].value[0]);
        Solution cSolution(pHead);
        cout << "null";
        for (long unsigned int j = 1; j < testData[i].method.size(); ++j) {
            srand(time(nullptr) + j);
            cSolution.getRandom();
            cout << (j == 0 ? "" : ", ") << cSolution.getRandom();
        }
        cout << "]\n";

        cout << "\n";

        freeListNode(pHead);
        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}
