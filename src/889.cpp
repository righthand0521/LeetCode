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
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        TreeNode* pRetVal = nullptr;

        if ((preorder.size() == 0) || (postorder.size() == 0)) {
            return pRetVal;
        }

        /* Example
         *        (1)           pre: 1 2 4 5 3 6 7
         *    (2)     (3)    v   in: 4 2 5 1 6 3 7
         *  (4) (5) (6) (7)  v post: 4 5 2 6 7 3 1
         */

#if 0
        int postorderIndex = postorder.size() - 1;
        int inorderIndex = inorder.size() - 1;
        stack s = stack<TreeNode*>();


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
#endif

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> preorder;
        vector<int> postorder;
    };
    vector<subject> testData{{{1, 2, 4, 5, 3, 6, 7}, {4, 5, 2, 6, 7, 3, 1}}, {{1}, {1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: preorder = [1,2,4,5,3,6,7], postorder = [4,5,2,6,7,3,1]
     *  Output: [1,2,3,4,5,6,7]
     *
     *  Input: preorder = [1], postorder = [1]
     *  Output: [1]
     */

    Solution cSolution;
    TreeNode* pAnswer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: preorder = [";
        for (long unsigned int j = 0; j < testData[i].preorder.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].preorder[j];
        }
        cout << "], postorder = [";
        for (long unsigned int j = 0; j < testData[i].postorder.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].postorder[j];
        }
        cout << "]\n";

        pAnswer = cSolution.constructFromPrePost(testData[i].preorder, testData[i].postorder);
        int height = getTreeHeight(pAnswer);
        cout << "Output: [";
        showTreeOutput(pAnswer, height);
        cout << "]\n";

        cout << "\n";

        freeTreeNode(pAnswer);
    }

    return EXIT_SUCCESS;
}
