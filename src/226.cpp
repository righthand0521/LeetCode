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
    TreeNode *invertTree(TreeNode *root) {
        TreeNode *pRetVal = root;

        if (pRetVal == NULL) {
            return pRetVal;
        }
        TreeNode *pTemp = pRetVal->left;
        pRetVal->left = pRetVal->right;
        pRetVal->right = pTemp;
        invertTree(pRetVal->left);
        invertTree(pRetVal->right);

        return pRetVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{4, 2, 7, 1, 3, 6, 9}}, {{2, 1, 3}}, {{}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [4,2,7,1,3,6,9]
     *  Output: [4,7,2,9,6,3,1]
     *
     *  Input: root = [2,1,3]
     *  Output: [2,3,1]
     *
     *  Input: root = []
     *  Output: []
     */

    Solution cSolution;
    TreeNode *pRoot;
    vector<int> answer;
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

        pRoot = cSolution.invertTree(pRoot);
        int height = getTreeHeight(pRoot);
        cout << "Output: [";
        showTreeOutput(pRoot, height);
        cout << "]\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
