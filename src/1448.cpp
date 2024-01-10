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
    int dfs(struct TreeNode* root, int maxValue) {
        int retVal = 0;

        if (root == nullptr) {
            return retVal;
        }

        if (root->val >= maxValue) {
            retVal++;
            maxValue = root->val;
        }
        int left = dfs(root->left, maxValue);
        int right = dfs(root->right, maxValue);
        retVal += (left + right);

        return retVal;
    }
    int goodNodes(TreeNode* root) {
        int retVal = 0;

        int maxValue = numeric_limits<int>::min();  // Each node's value is between [-10^4, 10^4].
        retVal += dfs(root, maxValue);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{3, 1, 4, 3, numeric_limits<int>::min(), numeric_limits<int>::min(), 1, 5}},
                             {{3, 3, numeric_limits<int>::min(), 4, 2}},
                             {{1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [3,1,4,3,null,1,5]
     *  Output: 4
     *
     *  Input: root = [3,3,null,4,2]
     *  Output: 3
     *
     *  Input: root = [1]
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

        answer = cSolution.goodNodes(pRoot);
        cout << "Output: " << answer << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
