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
    void dfs(TreeNode* root, vector<int>& sequence) {
        if (root == nullptr) {
            return;
        }

        if ((root->left == nullptr) && (root->right == nullptr)) {
            sequence.emplace_back(root->val);
            return;
        }
        dfs(root->left, sequence);
        dfs(root->right, sequence);
    }
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        bool retVal = false;

        vector<int> sequence1;
        dfs(root1, sequence1);

        vector<int> sequence2;
        dfs(root2, sequence2);

        if (sequence1 == sequence2) {
            retVal = true;
        }

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
    vector<subject> testData{
        {{3, 5, 1, 6, 2, 9, 8, imin, imin, 7, 4}, {3, 5, 1, 6, 7, 4, 2, imin, imin, imin, imin, imin, imin, 9, 8}},
        {{1, 2, 3}, {1, 3, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root1 = [3,5,1,6,2,9,8,null,null,7,4], root2 = [3,5,1,6,7,4,2,null,null,null,null,null,null,9,8]
     *  Output: true
     *
     *  Input: root1 = [1,2,3], root2 = [1,3,2]
     *  Output: false
     */

    Solution cSolution;
    TreeNode* pRoot1;
    TreeNode* pRoot2;
    bool answer;
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

        answer = cSolution.leafSimilar(pRoot1, pRoot2);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";

        freeTreeNode(pRoot1);
        freeTreeNode(pRoot2);
    }

    return EXIT_SUCCESS;
}
