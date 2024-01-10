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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        TreeNode* pRetVal = nullptr;

        if (postorder.size() == 0) {
            return pRetVal;
        }

        int postorderIndex = postorder.size() - 1;
        int inorderIndex = inorder.size() - 1;
        stack s = stack<TreeNode*>();

        /* Example
         *      (3)           pre: 3  9 20 15  7
         *   (9)   (20)    v   in: 9  3 15 20  7
         *      (15)  (7)  v post: 9 15  7 20  3
         */
        pRetVal = new TreeNode(postorder[postorderIndex]);
        s.push(pRetVal);
        for (int i = postorderIndex - 1; i >= 0; --i) {
            int postorderVal = postorder[i];
            auto node = s.top();
            if (node->val != inorder[inorderIndex]) {
                node->right = new TreeNode(postorderVal);
                s.push(node->right);
            } else {
                while ((s.empty() == false) && (s.top()->val == inorder[inorderIndex])) {
                    node = s.top();
                    s.pop();
                    --inorderIndex;
                }
                node->left = new TreeNode(postorderVal);
                s.push(node->left);
            }
        }

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> inorder;
        vector<int> postorder;
    };
    vector<subject> testData{{{9, 3, 15, 20, 7}, {9, 15, 7, 20, 3}}, {{-1}, {-1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
     *  Output: [3,9,20,null,null,15,7]
     *
     *  Input: inorder = [-1], postorder = [-1]
     *  Output: [-1]
     */

    Solution cSolution;
    TreeNode* pAnswer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: inorder = [";
        for (long unsigned int j = 0; j < testData[i].inorder.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].inorder[j];
        }
        cout << "], postorder = [";
        for (long unsigned int j = 0; j < testData[i].postorder.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].postorder[j];
        }
        cout << "]\n";

        pAnswer = cSolution.buildTree(testData[i].inorder, testData[i].postorder);
        int height = getTreeHeight(pAnswer);
        cout << "Output: [";
        showTreeOutput(pAnswer, height);
        cout << "]\n";

        cout << "\n";

        freeTreeNode(pAnswer);
    }

    return EXIT_SUCCESS;
}
