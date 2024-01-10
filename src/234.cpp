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
    bool isPalindrome(ListNode *head) {
        bool retVal = false;

        vector<int> value;
        ListNode *pCurrent = head;
        while (pCurrent != nullptr) {
            value.emplace_back(pCurrent->val);
            pCurrent = pCurrent->next;
        }

        int left = 0;
        int right = value.size() - 1;
        while (left <= right) {
            if (value[left++] != value[right--]) {
                return retVal;
            }
        }
        retVal = true;

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        vector<int> node;
    };
    vector<subject> testData{{{1, 2, 2, 1}}, {{1, 2}}, {{1, 2, 1}}, {{1, 2, 3}}, {{1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [1,2,2,1]
     *  Output: true
     *
     *  Input: head = [1,2]
     *  Output: false
     */

    Solution cSolution;
    ListNode *pHead = nullptr;
    bool answer = true;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].node);
        cout << "Input: head = [";
        printList(pHead);
        cout << "]\n";

        answer = cSolution.isPalindrome(pHead);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";

        freeListNode(pHead);
        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}
