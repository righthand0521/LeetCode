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
    TreeNode* removeLeafNodes(TreeNode* root, int target) {
        TreeNode* pRetVal = root;

        if (pRetVal == nullptr) {
            return pRetVal;
        }

        pRetVal->left = removeLeafNodes(pRetVal->left, target);
        pRetVal->right = removeLeafNodes(pRetVal->right, target);
        if ((pRetVal->left == nullptr) && (pRetVal->right == nullptr) && (pRetVal->val == target)) {
            delete pRetVal;
            pRetVal = nullptr;
        }

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> root;
        int target;
    };
    vector<subject> testData{
        {{1, 2, 3, 2, imin, 2, 4}, 2}, {{1, 3, 3, 3, 2}, 3}, {{1, 2, imin, 2, imin, imax, imax, 2}, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [1,2,3,2,null,2,4], target = 2
     *  Output: [1,null,3,null,4]
     *
     *  Input: root = [1,3,3,3,2], target = 3
     *  Output: [1,3,null,null,2]
     *
     *  Input: root = [1,2,null,2,null,2], target = 2
     *  Output: [1]
     */

    Solution cSolution;
    TreeNode* pRoot;
    TreeNode* pAnswer;
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
        cout << "], target = " << testData[i].target << "\n";
        pRoot = buildBinaryTree(testData[i].root, 0);

        pAnswer = cSolution.removeLeafNodes(pRoot, testData[i].target);
        int height = getTreeHeight(pAnswer);
        cout << "Output: [";
        showTreeOutput(pAnswer, height);
        cout << "]\n";

        cout << "\n";

        freeTreeNode(pAnswer);
        pAnswer = nullptr;
        pRoot = nullptr;
    }

    return EXIT_SUCCESS;
}
