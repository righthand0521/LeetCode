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
    long minVal = 0;

   public:
    bool inOrder(TreeNode* root) {
        bool retVal = true;

        if (root == nullptr) {
            return retVal;
        }

        bool left = inOrder(root->left);
        if (root->val <= minVal) {
            retVal = false;
            return retVal;
        }
        minVal = root->val;
        bool right = inOrder(root->right);

        retVal = (left && right);

        return retVal;
    }
    bool isValidBST(TreeNode* root) {
        bool retVal = true;

        minVal = numeric_limits<long>::min();
        retVal = inOrder(root);

        return retVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{2, 1, 3}}, {{5, 1, 4, imin, imin, 3, 6}}, {{1, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [2,1,3]
     *  Output: true
     *
     *  Input: root = [5,1,4,null,null,3,6]
     *  Output: false
     *
     *  Input: root = [1,1]
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

        answer = cSolution.isValidBST(pRoot);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}