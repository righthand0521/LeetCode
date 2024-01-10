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
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
   public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* pRetVal = root;

        if ((root == nullptr) || (root == p) || (root == q)) {
            return pRetVal;
        }

        TreeNode* pLeft = lowestCommonAncestor(root->left, p, q);
        TreeNode* pRight = lowestCommonAncestor(root->right, p, q);
        if ((pLeft == nullptr) && (pRight == nullptr)) {
            pRetVal = nullptr;
        } else if (pLeft == nullptr) {
            pRetVal = pRight;
        } else if (pRight == nullptr) {
            pRetVal = pLeft;
        }

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> root;
        int p;
        int q;
    };
    vector<subject> testData{{{3, 5, 1, 6, 2, 0, 8, imin, imin, 7, 4}, 5, 1},
                             {{3, 5, 1, 6, 2, 0, 8, imin, imin, 7, 4}, 5, 4},
                             {{1, 2}, 1, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
     *  Output: 3
     *
     *  Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
     *  Output: 5
     *
     *  Input: root = [1,2], p = 1, q = 2
     *  Output: 1
     */

    Solution cSolution;
    TreeNode* pRoot;
    TreeNode* pTree;
    TreeNode* qTree;
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
        cout << "], p = " << testData[i].p << ", q = " << testData[i].q << "\n";
        pRoot = buildBinaryTree(testData[i].root, 0);
        pTree = findSubTree(pRoot, testData[i].p);
        qTree = findSubTree(pRoot, testData[i].q);

        pAnswer = cSolution.lowestCommonAncestor(pRoot, pTree, qTree);
        cout << "Output: " << pAnswer->val << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
        pRoot = nullptr;
        pTree = nullptr;
        qTree = nullptr;
        pAnswer = nullptr;
    }

    return EXIT_SUCCESS;
}
