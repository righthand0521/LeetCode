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
    void inorderTraversal(struct TreeNode *root, int *previous, int *miniDiff) {
        if (root == NULL) {
            return;
        }
        inorderTraversal(root->left, previous, miniDiff);
        if ((*previous) != -1) {
            (*miniDiff) = min((*miniDiff), root->val - (*previous));
        }
        (*previous) = root->val;
        inorderTraversal(root->right, previous, miniDiff);
    }
    int getMinimumDifference(TreeNode *root) {
        int retVal = numeric_limits<int>::max();

        // 0 <= Node.val <= 10^5
        int previous = -1;
        inorderTraversal(root, &previous, &retVal);

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        vector<int> root;
    };
    vector<subject> testData{{{4, 2, 6, 1, 3}},
                             {{1, 0, 48, numeric_limits<int>::min(), numeric_limits<int>::min(), 12, 49}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [4,2,6,1,3]
     *  Output: 1
     *
     *  Input: root = [1,0,48,null,null,12,49]
     *  Output: 1
     */

    Solution cSolution;
    TreeNode *pRoot;
    int answer = 0;
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
        cout << "]\n";
        pRoot = buildBinaryTree(testData[i].root, 0);

        answer = cSolution.getMinimumDifference(pRoot);
        cout << "Output: " << answer << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
