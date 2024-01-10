#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

#include "list.h"
#include "tree.h"

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
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
   public:
    TreeNode* buildBSTbyInorder(ListNode** pHead, int left, int right) {
        TreeNode* pRetVal = nullptr;

        if (left > right) {
            return pRetVal;
        }

        int middle = (left + right + 1) / 2;
        pRetVal = new TreeNode();
        pRetVal->left = buildBSTbyInorder(pHead, left, middle - 1);
        pRetVal->val = (*pHead)->val;
        (*pHead) = (*pHead)->next;
        pRetVal->right = buildBSTbyInorder(pHead, middle + 1, right);

        return pRetVal;
    }
    TreeNode* sortedListToBST(ListNode* head) {
        TreeNode* pRetVal = nullptr;

        int headCount = 0;
        ListNode* pNext = head;
        while (pNext != nullptr) {
            ++headCount;
            pNext = pNext->next;
        }
        pNext = head;
        pRetVal = buildBSTbyInorder(&pNext, 0, headCount - 1);

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> node;
    };
    vector<subject> testData{{{-10, -3, 0, 5, 9}}, {{}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [-10,-3,0,5,9]
     *  Output: [0,-3,9,-10,null,5]
     *
     *  Input: head = []
     *  Output: []
     */

    Solution cSolution;
    ListNode* pHead = nullptr;
    TreeNode* pAnswer = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].node);
        cout << "Input: head = [";
        printList(pHead);
        cout << "]\n";

        pAnswer = cSolution.sortedListToBST(pHead);
        int height = getTreeHeight(pAnswer);
        cout << "Output: [";
        showTreeOutput(pAnswer, height);
        cout << "]\n";

        cout << "\n";

        freeTreeNode(pAnswer);
        pAnswer = nullptr;
        freeListNode(pHead);
        pHead = nullptr;
    }

    return EXIT_SUCCESS;
}
