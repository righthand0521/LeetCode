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
    bool flipEquiv(TreeNode* root1, TreeNode* root2) {
        bool retVal = false;

        if ((root1 == nullptr) && (root2 == nullptr)) {  // Both trees are empty
            retVal = true;
            return retVal;
        } else if (root1 == nullptr || root2 == nullptr) {  // Just one of the trees is empty
            return retVal;
        } else if (root1->val != root2->val) {  // Corresponding values differ
            return retVal;
        }

        // Check if corresponding subtrees are flip equivalent
        bool noSwap = flipEquiv(root1->left, root2->left) && flipEquiv(root1->right, root2->right);
        // Check if opposite subtrees are flip equivalent
        bool swap = flipEquiv(root1->left, root2->right) && flipEquiv(root1->right, root2->left);

        retVal = swap || noSwap;

        return retVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> root1;
        vector<int> root2;
    };
    vector<subject> testData{{{1, 2, 3, 4, 5, 6, imin, imin, imin, 7, 8},
                              {1, 3, 2, imin, 6, 4, 5, imax, imax, imin, imin, imin, imin, 8, 7}},
                             {{}, {}},
                             {{}, {1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root1 = [1,2,3,4,5,6,null,null,null,7,8], root2 = [1,3,2,null,6,4,5,null,null,null,null,8,7]
     *  Output: true
     *
     *  Input: root1 = [], root2 = []
     *  Output: true
     *
     *  Input: root1 = [], root2 = [1]
     *  Output: false
     */

    Solution cSolution;
    TreeNode* pRoot1;
    TreeNode* pRoot2;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: root1 = [";
        for (long unsigned int j = 0; j < testData[i].root1.size(); ++j) {
            if (testData[i].root1[j] == imin) {
                cout << (j == 0 ? "" : ",") << "null";
            } else if (testData[i].root1[j] == imax) {
                continue;
            } else {
                cout << ((j == 0) ? "" : ",") << testData[i].root1[j];
            }
        }
        cout << "], root2 = [";
        for (long unsigned int j = 0; j < testData[i].root2.size(); ++j) {
            if (testData[i].root2[j] == imin) {
                cout << (j == 0 ? "" : ",") << "null";
            } else if (testData[i].root2[j] == imax) {
                continue;
            } else {
                cout << ((j == 0) ? "" : ",") << testData[i].root2[j];
            }
        }
        cout << "]\n";
        pRoot1 = buildBinaryTree(testData[i].root1, 0);
        pRoot2 = buildBinaryTree(testData[i].root2, 0);

        answer = cSolution.flipEquiv(pRoot1, pRoot2);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";

        freeTreeNode(pRoot1);
        freeTreeNode(pRoot2);
    }

    return EXIT_SUCCESS;
}
