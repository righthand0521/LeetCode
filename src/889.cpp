#include <algorithm>
#include <iostream>
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
   private:
    TreeNode* constructTree(int& preIndex, int& postIndex, vector<int>& preorder, vector<int>& postorder) {
        // Create a new node with the value at the current preorder index
        TreeNode* root = new TreeNode(preorder[preIndex]);
        // Mark this node as created
        preIndex++;
        // Recursively construct the left subtree if the root is not the last of its subtree
        if (root->val != postorder[postIndex]) {
            root->left = constructTree(preIndex, postIndex, preorder, postorder);
        }
        // Recursively construct the right subtree if the root is still not the last of its subtree
        if (root->val != postorder[postIndex]) {
            root->right = constructTree(preIndex, postIndex, preorder, postorder);
        }
        // Mark this node and its subtree as fully processed
        postIndex++;

        return root;
    }

   public:
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        TreeNode* pRetVal = nullptr;

        int preIndex = 0;
        int postIndex = 0;
        pRetVal = constructTree(preIndex, postIndex, preorder, postorder);

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
