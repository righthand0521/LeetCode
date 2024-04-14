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
    int preorder(TreeNode* root, bool isLeft) {
        int retVal = 0;

        if (root == nullptr) {
            return retVal;
        }

        if ((root->left == nullptr) && (root->right == nullptr) & (isLeft == true)) {
            retVal += root->val;
        }
        retVal += preorder(root->left, true);
        retVal += preorder(root->right, false);

        return retVal;
    }
    int sumOfLeftLeaves(TreeNode* root) {
        int retVal = 0;

        if (root == nullptr) {
            return retVal;
        }
        retVal = preorder(root, false);

        return retVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{3, 9, 20, imin, imin, 15, 7}}, {{1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [3,9,20,null,null,15,7]
     *  Output: 24
     *
     *  Input: root = [1]
     *  Output: 0
     */

    Solution cSolution;
    TreeNode* pRoot;
    int answer;
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

        answer = cSolution.sumOfLeftLeaves(pRoot);
        cout << "Output: " << answer << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
