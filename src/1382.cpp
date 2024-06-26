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
    void inorderTraversal(TreeNode* root, vector<int>& inorder) {
        if (root == nullptr) {
            return;
        }

        inorderTraversal(root->left, inorder);
        inorder.push_back(root->val);
        inorderTraversal(root->right, inorder);
    }
    TreeNode* createBalancedBST(const vector<int>& inorder, int start, int end) {
        TreeNode* pRetVal = nullptr;

        // Base case: if the start index is greater than the end index, return nullptr
        if (start > end) {
            return pRetVal;
        }

        // Find the middle element of the current range
        int mid = start + (end - start) / 2;
        // Recursively construct the left and right subtrees
        TreeNode* leftSubtree = createBalancedBST(inorder, start, mid - 1);
        TreeNode* rightSubtree = createBalancedBST(inorder, mid + 1, end);
        // Create a new node with the middle element and attach the subtrees
        pRetVal = new TreeNode(inorder[mid], leftSubtree, rightSubtree);

        return pRetVal;
    }

   public:
    TreeNode* balanceBST(TreeNode* root) {
        TreeNode* pRetVal = root;

        if (pRetVal == nullptr) {
            return pRetVal;
        }

        // Create a vector to store the inorder traversal of the BST
        vector<int> inorder;
        inorderTraversal(root, inorder);
        int inorderSize = inorder.size();

        // Construct and return the balanced BST
        pRetVal = createBalancedBST(inorder, 0, inorderSize - 1);

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{
        {{1, imin, 2, imax, imax, imin, 3, imax, imax, imax, imax, imax, imax, imin, 4, imin, imin}}, {{2, 1, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [1,null,2,null,3,null,4,null,null]
     *  Output: [2,1,3,null,null,null,4]
     *
     *  Input: root = [2,1,3]
     *  Output: [2,1,3]
     */

    Solution cSolution;
    TreeNode* pRoot;
    TreeNode* pAnswer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: root = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            if (testData[i].nums[j] == imin) {
                cout << (j == 0 ? "" : ",") << "null";
            } else if (testData[i].nums[j] == imax) {
                continue;
            } else {
                cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
            }
        }
        cout << "]\n";
        pRoot = buildBinaryTree(testData[i].nums, 0);

        pAnswer = cSolution.balanceBST(pRoot);
        int height = getTreeHeight(pAnswer);
        cout << "Output: [";
        showTreeOutput(pAnswer, height);
        cout << "]\n";

        cout << "\n";

        freeTreeNode(pRoot);
        freeTreeNode(pAnswer);
    }

    return EXIT_SUCCESS;
}
