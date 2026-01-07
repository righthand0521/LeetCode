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
    static constexpr int MODULO = 1e9 + 7;

    int postOrder(TreeNode* root, vector<int>& subTreeSum) {
        int retVal = 0;

        if (root == nullptr) {
            return retVal;
        }
        retVal = postOrder(root->left, subTreeSum) + postOrder(root->right, subTreeSum) + root->val;
        subTreeSum.emplace_back(retVal);

        return retVal;
    }

   public:
    int maxProduct(TreeNode* root) {
        int retVal = 0;

        vector<int> subTreeSum;
        int treeSum = postOrder(root, subTreeSum);
        int subTreeSumSize = subTreeSum.size();

        long long maxValue = 0;
        for (int i = 0; i < subTreeSumSize; ++i) {
            maxValue = max(maxValue, ((long long)subTreeSum[i] * (long long)(treeSum - subTreeSum[i])));
        }
        retVal = maxValue % MODULO;

        return retVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 3, 4, 5, 6}},
                             {{1, imin, 2, imax, imax, 3, 4, imax, imax, imax, imax, imin, imin, 5, 6}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [1,2,3,4,5,6]
     *  Output: 110
     *
     *  Input: root = [1,null,2,3,4,null,null,5,6]
     *  Output: 90
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

        answer = cSolution.maxProduct(pRoot);
        cout << "Output: " << answer << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
