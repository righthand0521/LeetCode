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
    int moves = 0;
    int dfs(TreeNode* root) {
        int retVal = 0;

        if (root == nullptr) {
            return retVal;
        }
        int leftMoves = dfs(root->left);
        int rightMoves = dfs(root->right);
        moves += (abs(leftMoves) + abs(rightMoves));
        retVal = (root->val - 1) + leftMoves + rightMoves;

        return retVal;
    }

   public:
    int distributeCoins(TreeNode* root) {
        int retVal = 0;

        moves = 0;
        dfs(root);
        retVal = moves;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{3, 0, 0}}, {{0, 3, 0}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [3,0,0]
     *  Output: 2
     *
     *  Input: root = [0,3,0]
     *  Output: 3
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
        answer = cSolution.distributeCoins(pRoot);
        cout << "Output: " << answer << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
