#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

#include "tree.h"

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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        TreeNode* pRetVal = nullptr;

        if (preorder.size() == 0) {
            return pRetVal;
        }

        int preorderIndex = preorder.size();
        int inorderIndex = 0;
        stack s = stack<TreeNode*>();

        /* Example
         *      (3)        v  pre: 3  9 20 15  7
         *   (9)   (20)    v   in: 9  3 15 20  7
         *      (15)  (7)    post: 9 15  7 20  3
         */
        pRetVal = new TreeNode(preorder[0]);
        s.push(pRetVal);
        for (int i = 1; i < preorderIndex; ++i) {
            int preorderVal = preorder[i];
            auto node = s.top();
            if (node->val != inorder[inorderIndex]) {
                node->left = new TreeNode(preorderVal);
                s.push(node->left);
            } else {
                while ((s.empty() == false) && (s.top()->val == inorder[inorderIndex])) {
                    node = s.top();
                    s.pop();
                    ++inorderIndex;
                }
                node->right = new TreeNode(preorderVal);
                s.push(node->right);
            }
        }

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> preorder;
        vector<int> inorder;
    };
    vector<subject> testData{{{3, 9, 20, 15, 7}, {9, 3, 15, 20, 7}}, {{-1}, {-1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
     *  Output: [3,9,20,null,null,15,7]
     *
     *  Input: preorder = [-1], inorder = [-1]
     *  Output: [-1]
     */

    Solution cSolution;
    TreeNode* pAnswer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: preorder = [";
        for (long unsigned int j = 0; j < testData[i].preorder.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].preorder[j];
        }
        cout << "], inorder = [";
        for (long unsigned int j = 0; j < testData[i].inorder.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].inorder[j];
        }
        cout << "]\n";

        pAnswer = cSolution.buildTree(testData[i].preorder, testData[i].inorder);
        int height = getTreeHeight(pAnswer);
        cout << "Output: [";
        showTreeOutput(pAnswer, height);
        cout << "]\n";

        cout << "\n";

        freeTreeNode(pAnswer);
    }

    return EXIT_SUCCESS;
}
