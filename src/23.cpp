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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* pRetVal = nullptr;

        if (list2 == nullptr) {
            pRetVal = list1;
            return pRetVal;
        }
        ListNode* pHead = new ListNode();
        pRetVal = pHead;

        ListNode* p1 = list1;
        ListNode* p2 = list2;
        while ((p1 != nullptr) && (p2 != nullptr)) {
            if (p1->val <= p2->val) {
                pRetVal->next = p1;
                p1 = p1->next;
            } else {
                pRetVal->next = p2;
                p2 = p2->next;
            }
            pRetVal = pRetVal->next;
        }
        pRetVal->next = (p1 != nullptr) ? p1 : p2;

        pRetVal = pHead->next;
        delete pHead;

        return pRetVal;
    }
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* pRetVal = nullptr;

        int listsSize = lists.size();
        if (listsSize == 0) {
            return pRetVal;
        }

        int interval = 1;
        while (interval < listsSize) {
            for (int i = 0; i < listsSize; i += (interval * 2)) {
                if (i + interval < listsSize) {
                    lists[i] = mergeTwoLists(lists[i], lists[i + interval]);
                }
            }
            interval *= 2;
        }
        pRetVal = lists[0];

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> node;
    };
    vector<subject> testData{{{{1, 4, 5}, {1, 3, 4}, {2, 6}}},        {{}}, {{{}}}, {{{}, {1}}}, {{{1}, {}}},
                             {{{1, 4, 5}, {1, 3, 4}, {2, 6}, {7, 8}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: lists = [[1,4,5],[1,3,4],[2,6]]
     *  Output: [1,1,2,3,4,4,5,6]
     *
     *  Input: lists = []
     *  Output: []
     *
     *  Input: lists = [[]]
     *  Output: []
     */

    Solution cSolution;
    ListNode* pAnswer = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: lists = [";
        vector<ListNode*> lists;
        for (long unsigned int j = 0; j < testData[i].node.size(); ++j) {
            ListNode* pList = buildList(testData[i].node[j]);
            cout << (j == 0 ? "" : ",") << "[";
            printList(pList);
            cout << "]";

            lists.emplace_back(pList);
        }
        cout << "]\n";

        pAnswer = cSolution.mergeKLists(lists);
        cout << "Output: [";
        printList(pAnswer);
        cout << "]\n";

        cout << "\n";

        freeListNode(pAnswer);
        pAnswer = nullptr;
    }

    return EXIT_SUCCESS;
}
