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
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        TreeNode* pRetVal = NULL;

        if ((root == NULL) || (p == NULL)) {
            return pRetVal;
        }

        while (root != NULL) {
            if (root->val <= p->val) {
                root = root->right;
            } else {
                pRetVal = root;
                root = root->left;
            }
        }

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> root;
        vector<int> p;
    };
    vector<subject> testData{{{2, 1, 3}, {1}},
                             {{5, 3, 6, 2, 4, numeric_limits<int>::min(), numeric_limits<int>::min(), 1}, {6}},
                             {{2, 1, 3}, {2}},
                             {{2, 1}, {1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [2,1,3], p = 1
     *  Output: 2
     *
     *  Input: root = [5,3,6,2,4,null,null,1], p = 6
     *  Output: null
     */

    Solution cSolution;
    TreeNode* pRoot = nullptr;
    TreeNode* pP = nullptr;
    TreeNode* pAnswer = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: root = [";
        for (long unsigned int j = 0; j < testData[i].root.size(); ++j) {
            if (testData[i].root[j] == numeric_limits<int>::min()) {
                cout << (j == 0 ? "" : ",") << "null";
            } else if (testData[i].root[j] == numeric_limits<int>::max()) {
                continue;
            } else {
                cout << ((j == 0) ? "" : ",") << testData[i].root[j];
            }
        }
        cout << "], p = " << testData[i].p[0] << "\n";
        pRoot = buildBinaryTree(testData[i].root, 0);
        pP = buildBinaryTree(testData[i].p, 0);

        pAnswer = cSolution.inorderSuccessor(pRoot, pP);
        if (pAnswer == NULL) {
            cout << "Output: null\n";
        } else {
            cout << "Output: " << pAnswer->val << "\n";
        }

        cout << "\n";

        freeTreeNode(pRoot);
        pRoot = nullptr;
        freeTreeNode(pP);
        pP = nullptr;
        pAnswer = nullptr;
    }

    return EXIT_SUCCESS;
}
