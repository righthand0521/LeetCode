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
    TreeNode *addOneRow(TreeNode *root, int val, int depth) {
        TreeNode *pRetVal = root;

        if (depth == 1) {
            pRetVal = new TreeNode(val, root, nullptr);
            return pRetVal;
        }

        vector<TreeNode *> currentLevel(1, root);
        for (int i = 1; i < (depth - 1); ++i) {
            vector<TreeNode *> tmp;
            for (auto &node : currentLevel) {
                if (node->left != nullptr) {
                    tmp.emplace_back(node->left);
                }
                if (node->right != nullptr) {
                    tmp.emplace_back(node->right);
                }
            }
            currentLevel = move(tmp);
        }

        for (auto &node : currentLevel) {
            node->left = new TreeNode(val, node->left, nullptr);
            node->right = new TreeNode(val, nullptr, node->right);
        }

        return pRetVal;
    }
};

int main(int argc, char **argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> nums;
        int val;
        int depth;
    };
    vector<subject> testData{{{4, 2, 6, 3, 1, 5}, 1, 2}, {{4, 2, imin, 3, 1}, 1, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [4,2,6,3,1,5], val = 1, depth = 2
     *  Output: [4,1,1,2,null,null,6,3,1,5]
     *
     *  Input: root = [4,2,null,3,1], val = 1, depth = 3
     *  Output: [4,2,null,1,1,3,null,null,1]
     */

    Solution cSolution;
    TreeNode *pRoot;
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
        cout << "], val = " << testData[i].val << ", depth = " << testData[i].depth << "\n";
        pRoot = buildBinaryTree(testData[i].nums, 0);

        pRoot = cSolution.addOneRow(pRoot, testData[i].val, testData[i].depth);
        int height = getTreeHeight(pRoot);
        cout << "Output: [";
        showTreeOutput(pRoot, height);
        cout << "]\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
