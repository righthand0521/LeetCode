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
    int sum = 0;

   public:
    void inorder(TreeNode* root, int low, int high) {
        if (root == nullptr) {
            return;
        }
        inorder(root->left, low, high);
        if ((low <= root->val) && (root->val <= high)) {
            sum += root->val;
        }
        inorder(root->right, low, high);
    }
    int rangeSumBST(TreeNode* root, int low, int high) {
        int retVal = 0;

        if (root == nullptr) {
            return retVal;
        }

        sum = 0;
        inorder(root, low, high);
        retVal = sum;

        return retVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> root;
        int low;
        int high;
    };
    vector<subject> testData{{{10, 5, 15, 3, 7, imin, 18}, 7, 15}, {{10, 5, 15, 3, 7, 13, 18, 1, imin, 6}, 6, 10}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [10,5,15,3,7,null,18], low = 7, high = 15
     *  Output: 32
     *
     *  Input: root = [10,5,15,3,7,13,18,1,null,6], low = 6, high = 10
     *  Output: 23
     */

    Solution cSolution;
    TreeNode* pRoot;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: root = [";
        for (long unsigned int j = 0; j < testData[i].root.size(); ++j) {
            if (testData[i].root[j] == imin) {
                cout << (j == 0 ? "" : ",") << "null";
            } else if (testData[i].root[j] == imax) {
                continue;
            } else {
                cout << ((j == 0) ? "" : ",") << testData[i].root[j];
            }
        }
        cout << "], low = " << testData[i].low << ", high = " << testData[i].high << "\n";
        pRoot = buildBinaryTree(testData[i].root, 0);

        answer = cSolution.rangeSumBST(pRoot, testData[i].low, testData[i].high);
        cout << "Output: " << answer << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
