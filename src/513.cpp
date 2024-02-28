#include <algorithm>
#include <iostream>
#include <queue>
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
    int findBottomLeftValue(TreeNode* root) {
        int retVal = 0;

        queue<TreeNode*> bfsQueue;
        TreeNode* current = root;
        bfsQueue.push(current);
        while (bfsQueue.empty() == false) {
            current = bfsQueue.front();
            bfsQueue.pop();
            if (current->right != nullptr) {
                bfsQueue.push(current->right);
            }
            if (current->left != nullptr) {
                bfsQueue.push(current->left);
            }
        }
        retVal = current->val;

        return retVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{2, 1, 3}}, {{1, 2, 3, 4, imin, 5, 6, imin, imin, imax, imax, 7}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [2,1,3]
     *  Output: 1
     *
     *  Input: root = [1,2,3,4,null,5,6,null,null,7]
     *  Output: 7
     */

    Solution cSolution;
    TreeNode* pRoot;
    int answer;
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

        answer = cSolution.findBottomLeftValue(pRoot);
        cout << "Output: " << answer << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
