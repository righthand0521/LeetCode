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
    int dfs(TreeNode* root, long targetSum) {
        int retVal = 0;

        if (root == nullptr) {
            return retVal;
        }

        if (root->val == targetSum) {
            retVal += 1;
        }
        retVal += dfs(root->left, targetSum - root->val);
        retVal += dfs(root->right, targetSum - root->val);

        return retVal;
    }
    int pathSum(TreeNode* root, int targetSum) {
        int retVal = 0;

        if (root == nullptr) {
            return retVal;
        }

        retVal = dfs(root, targetSum);
        retVal += pathSum(root->left, targetSum);
        retVal += pathSum(root->right, targetSum);

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
    vector<subject> testData{{{10, 5, -3, 3, 2, imin, 11, 3, -2, imin, 1}, 8},
                             {{5, 4, 8, 11, imin, 13, 4, 7, 2, imin, imin, 5, 1}, 22}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
     *  Output: 3
     *
     *  Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
     *  Output: 3
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
        cout << "], targetSum = " << testData[i].targetSum << "\n";
        pRoot = buildBinaryTree(testData[i].nums, 0);

        answer = cSolution.pathSum(pRoot, testData[i].targetSum);
        cout << "Output: " << answer << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
