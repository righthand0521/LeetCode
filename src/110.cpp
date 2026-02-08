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
    int height(struct TreeNode* root) {
        int retVal = 0;

        if (root == nullptr) {
            return retVal;
        }
        retVal = -1;

        int left = height(root->left);
        if (left == -1) {
            return retVal;
        }

        int right = height(root->right);
        if (right == -1) {
            return retVal;
        }

        if (abs(left - right) > 1) {
            return retVal;
        }

        if (left > right) {
            retVal = left + 1;
        } else {
            retVal = right + 1;
        }

        return retVal;
    }

   public:
    bool isBalanced(TreeNode* root) {
        bool retVal = true;

        if (root == nullptr) {
            return retVal;
        }
        retVal = (height(root) != -1);

        return retVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{3, 9, 20, imin, imin, 15, 7}}, {{1, 2, 2, 3, 3, imin, imin, 4, 4}}, {}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [3,9,20,null,null,15,7]
     *  Output: true
     *
     *  Input: root = [1,2,2,3,3,null,null,4,4]
     *  Output: false
     *
     *  Input: root = []
     *  Output: true
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

        answer = cSolution.isBalanced(pRoot);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
