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
   public:
    void preorder(TreeNode* root, int mask, int* returnCount) {
        if (root == nullptr) {
            return;
        }

        mask = mask ^ (1 << root->val);  // 1 <= Node.val <= 9
        if ((root->left == nullptr) && (root->right == nullptr)) {
            if ((mask & (mask - 1)) == 0) {
                (*returnCount)++;
            }
            return;
        }
        preorder(root->left, mask, returnCount);
        preorder(root->right, mask, returnCount);
    }
    int pseudoPalindromicPaths(TreeNode* root) {
        int retVal = 0;

        if (root == nullptr) {
            return retVal;
        }
        preorder(root, 0, &retVal);

        return retVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    // int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{2, 3, 1, 3, 1, imin, 1}}, {{2, 1, 1, 1, 3, imin, imin, imin, imin, imin, 1}}, {{9}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [2,3,1,3,1,null,1]
     *  Output: 2
     *
     *  Input: root = [2,1,1,1,3,null,null,null,null,null,1]
     *  Output: 1
     *
     *  Input: root = [9]
     *  Output: 1
     */

    Solution cSolution;
    TreeNode* pRoot;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: root = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            if (testData[i].nums[j] == numeric_limits<int>::min()) {
                cout << (j == 0 ? "" : ",") << "null";
            } else if (testData[i].nums[j] == numeric_limits<int>::max()) {
                continue;
            } else {
                cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
            }
        }
        cout << "]\n";
        pRoot = buildBinaryTree(testData[i].nums, 0);

        answer = cSolution.pseudoPalindromicPaths(pRoot);
        cout << "Output: " << answer << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
