#include <algorithm>
#include <iostream>
#include <queue>
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
   private:
    bool dfs(ListNode* head, TreeNode* root) {
        bool retVal = false;

        if (head == nullptr) {
            retVal = true;
        } else if (root == nullptr) {
            retVal = false;
        } else if (head->val != root->val) {
            retVal = false;
        } else {
            retVal = dfs(head->next, root->left) || dfs(head->next, root->right);
        }

        return retVal;
    }

   public:
    bool isSubPath(ListNode* head, TreeNode* root) {
        bool retVal = false;

        if (root == nullptr) {
            return retVal;
        }

        retVal = dfs(head, root) || isSubPath(head, root->left) || isSubPath(head, root->right);

        return retVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> head;
        vector<int> root;
    };
    vector<subject> testData{
        {{4, 2, 8}, {1,    4,    4,    imin, 2,    2,    imin, imax, imax, 1,    imin, 6, 8, imin,
                     imin, imax, imax, imax, imax, imax, imax, imax, imax, imin, imin, 1, 3}},
        {{1, 4, 2, 6}, {1,    4,    4,    imin, 2,    2,    imin, imax, imax, 1,    imin, 6, 8, imin,
                        imin, imax, imax, imax, imax, imax, imax, imax, imax, imin, imin, 1, 3}},
        {{1, 4, 2, 6, 8}, {1,    4,    4,    imin, 2,    2,    imin, imax, imax, 1,    imin, 6, 8, imin,
                           imin, imax, imax, imax, imax, imax, imax, imax, imax, imin, imin, 1, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: head = [4,2,8], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
     *  Output: true
     *
     *  Input: head = [1,4,2,6], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
     *  utput: true
     *
     *  Input: head = [1,4,2,6,8], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
     *  Output: false
     */

    Solution cSolution;
    ListNode* pHead = nullptr;
    TreeNode* pRoot = nullptr;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testData[i].head);
        cout << "Input: head = [";
        printList(pHead);
        cout << "], root = [";
        for (long unsigned int j = 0; j < testData[i].root.size(); ++j) {
            if (testData[i].root[j] == imin) {
                cout << (j == 0 ? "" : ",") << "null";
            } else if (testData[i].root[j] == imax) {
                continue;
            } else {
                cout << ((j == 0) ? "" : ",") << testData[i].root[j];
            }
        }
        cout << "]\n";
        pRoot = buildBinaryTree(testData[i].root, 0);

        answer = cSolution.isSubPath(pHead, pRoot);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";

        freeListNode(pHead);
        pHead = nullptr;
        freeTreeNode(pRoot);
        pRoot = nullptr;
    }

    return EXIT_SUCCESS;
}
