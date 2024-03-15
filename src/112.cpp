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
    bool hasPathSum(TreeNode* root, int targetSum) {
        bool retVal = false;

        if (root == nullptr) {
            return retVal;
        }

        if ((root->left == nullptr) && (root->right == nullptr)) {
            if (root->val == targetSum) {
                retVal = true;
                return retVal;
            }
        }
        targetSum -= root->val;
        retVal = hasPathSum(root->left, targetSum) || hasPathSum(root->right, targetSum);

        return retVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> nums;
        int targetSum;
    };
    vector<subject> testData{
        {{5, 4, 8, 11, imin, 13, 4, 7, 2, imax, imax, imin, imin, imin, 1}, 22}, {{1, 2, 3}, 5}, {{}, 0}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
     *  Output: true
     *
     *  Input: root = [1,2,3], targetSum = 5
     *  Output: false
     *
     *  Input: root = [], targetSum = 0
     *  Output: false
     */

    Solution cSolution;
    TreeNode* pRoot;
    bool answer;
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
        cout << "], targetSum = " << testData[i].targetSum << "\n";
        pRoot = buildBinaryTree(testData[i].nums, 0);

        answer = cSolution.hasPathSum(pRoot, testData[i].targetSum);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}