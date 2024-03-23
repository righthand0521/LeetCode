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
    int maxPathValue = 0;

   public:
    int dfs(struct TreeNode* root) {
        int retVal = 0;

        if (root == nullptr) {
            return retVal;
        }

        int left = dfs(root->left);
        int right = dfs(root->right);
        retVal = max((left + root->val), (right + root->val));
        retVal = max(retVal, root->val);

        int maxValue = max(retVal, (left + right + root->val));
        maxPathValue = max(maxPathValue, maxValue);

        return retVal;
    }
    int maxPathSum(TreeNode* root) {
        int retVal = 0;

        if (root == nullptr) {
            return retVal;
        }

        maxPathValue = numeric_limits<int>::min();
        dfs(root);
        retVal = maxPathValue;

        return retVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 3}}, {{-10, 9, 20, imin, imin, 15, 7}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [1,2,3]
     *  Output: 6
     *
     *  Input: root = [-10,9,20,null,null,15,7]
     *  Output: 42
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

        answer = cSolution.maxPathSum(pRoot);
        cout << "Output: " << answer << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
