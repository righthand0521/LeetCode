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
    void dfs(TreeNode* root, bool dir, int len, int* retVal) {
        (*retVal) = max((*retVal), len);

        // bool dir: left is false, right is true.
        if (dir == false) {
            if (root->left) {
                dfs(root->left, true, len + 1, retVal);
            }
            if (root->right) {
                dfs(root->right, false, 1, retVal);
            }
        } else {
            if (root->right) {
                dfs(root->right, false, len + 1, retVal);
            }
            if (root->left) {
                dfs(root->left, true, 1, retVal);
            }
        }
    }
    int longestZigZag(TreeNode* root) {
        int retVal = 0;

        if (root == nullptr) {
            return retVal;
        }

        // bool dir: left is false, right is true.
        dfs(root, false, 0, &retVal);
        dfs(root, true, 0, &retVal);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1,
                               numeric_limits<int>::min(),
                               1,
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               1,
                               1,
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::min(),
                               numeric_limits<int>::min(),
                               1,
                               1,
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::min(),
                               1,
                               numeric_limits<int>::min(),
                               numeric_limits<int>::min(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::min(),
                               1,
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::min(),
                               1}},
                             {{1,
                               1,
                               1,
                               numeric_limits<int>::min(),
                               1,
                               numeric_limits<int>::min(),
                               numeric_limits<int>::min(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               1,
                               1,
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::min(),
                               1,
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max(),
                               numeric_limits<int>::max()}},
                             {{1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [1,null,1,1,1,null,null,1,1,null,1,null,null,null,1,null,1]
     *  Output: 3
     *
     *  Input: root = [1,1,1,null,1,null,null,1,1,null,1]
     *  Output: 4
     *
     *  Input: root = [1]
     *  Output: 0
     */

    Solution cSolution;
    TreeNode* pRoot;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: root = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            if (testData[i].nums[j] == numeric_limits<int>::min()) {
                cout << (j == 0 ? "" : ",") << "null";
            } else if (testData[i].nums[j] == numeric_limits<int>::max()) {
                continue;
            } else {
                cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
            }
        }
        cout << "]\n";
        pRoot = buildBinaryTree(testData[i].nums, 0);

        answer = cSolution.longestZigZag(pRoot);
        cout << "Output: " << answer << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
