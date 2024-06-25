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
    int addValue = 0;
    void plusTraversal(TreeNode *root) {
        if (root == nullptr) {
            return;
        }

        plusTraversal(root->right);
        root->val += addValue;
        addValue = root->val;
        plusTraversal(root->left);
    }

   public:
    TreeNode *convertBST(TreeNode *root) {
        TreeNode *pRetVal = root;

        if (pRetVal == nullptr) {
            return pRetVal;
        }

        addValue = 0;
        plusTraversal(pRetVal);

        return pRetVal;
    }
};

int main(int argc, char **argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{4, 1, 6, 0, 2, 5, 7, imin, imin, imin, 3, imin, imin, imin, 8}}, {{0, imin, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
     *  Output: [30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]
     *
     *  Input: root = [0,null,1]
     *  Output: [1,null,1]
     */

    Solution cSolution;
    TreeNode *pRoot;
    vector<int> answer;
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

        pRoot = cSolution.convertBST(pRoot);
        int height = getTreeHeight(pRoot);
        cout << "Output: [";
        showTreeOutput(pRoot, height);
        cout << "]\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
