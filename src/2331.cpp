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
    bool evaluateTree(TreeNode* root) {
        bool retVal = false;

        if ((root->left == nullptr) && (root->right == nullptr)) {
            if (root->val == 0) {
                retVal = false;
            } else if (root->val == 1) {
                retVal = true;
            }

            return retVal;
        }

        if (root->val == 2) {
            retVal = (evaluateTree(root->left) | evaluateTree(root->right));
        } else if (root->val == 3) {
            retVal = (evaluateTree(root->left) & evaluateTree(root->right));
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{2, 1, 3, imin, imin, 0, 1}}, {{0}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [2,1,3,null,null,0,1]
     *  Output: true
     *
     *  Input: root = [0]
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
        cout << "]\n";
        pRoot = buildBinaryTree(testData[i].nums, 0);

        answer = cSolution.evaluateTree(pRoot);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
