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
    int retVal = 0;

   public:
    void inorder(TreeNode* root, int* k) {
        if (root == nullptr) {
            return;
        }

        inorder(root->left, k);
        (*k)--;
        if ((*k) == 0) {
            retVal = root->val;
        }
        inorder(root->right, k);
    }
    int kthSmallest(TreeNode* root, int k) {
        retVal = 0;

        inorder(root, &k);

        return retVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{3, 1, 4, imin, 2}, 1}, {{5, 3, 6, 2, 4, imin, imin, 1}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [3,1,4,null,2], k = 1
     *  Output: 1
     *
     *  Input: root = [5,3,6,2,4,null,null,1], k = 3
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
        cout << "], k = " << testData[i].k << "\n";
        pRoot = buildBinaryTree(testData[i].nums, 0);

        answer = cSolution.kthSmallest(pRoot, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
