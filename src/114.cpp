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
    void flatten(TreeNode* root) {
        TreeNode* pCurrent = root;
        while (pCurrent != nullptr) {
            if (pCurrent->left != nullptr) {
                TreeNode* pNext = pCurrent->left;
                TreeNode* pPrevious = pCurrent->left;
                while (pPrevious->right != nullptr) {
                    pPrevious = pPrevious->right;
                }
                pPrevious->right = pCurrent->right;
                pCurrent->left = nullptr;
                pCurrent->right = pNext;
            }
            pCurrent = pCurrent->right;
        }
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 5, 3, 4, imin, 6}}, {{}}, {{0}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [1,2,5,3,4,null,6]
     *  Output: [1,null,2,null,3,null,4,null,5,null,6]
     *
     *  Input: root = []
     *  Output: []
     *
     *  Input: root = [0]
     *  Output: [0]
     */

    Solution cSolution;
    TreeNode* pRoot;
    vector<int> answer;
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

        cSolution.flatten(pRoot);
        int height = getTreeHeight(pRoot);
        cout << "Output: [";
        showTreeOutput(pRoot, height);
        cout << "]\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
