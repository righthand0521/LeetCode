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
    long long kthLargestLevelSum(TreeNode* root, int k) {
        long long retVal = -1;  // If there are fewer than k levels in the tree, return -1.

        vector<long long> traversal;

        queue<TreeNode*> q;
        q.push(root);
        while (q.empty() == false) {
            long long levelSum = 0;

            int currentLevelSize = q.size();
            for (int i = 1; i <= currentLevelSize; ++i) {
                auto node = q.front();
                q.pop();
                levelSum += (long long)node->val;
                if (node->left != NULL) {
                    q.push(node->left);
                }
                if (node->right != NULL) {
                    q.push(node->right);
                }
            }

            traversal.emplace_back(levelSum);
        }

        int traversalSize = traversal.size();
        if (k <= traversalSize) {
            sort(traversal.begin(), traversal.end(), greater());
            retVal = traversal[k - 1];
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{5, 8, 9, 2, 1, 3, 7, 4, 6}, 2}, {{1, 2, imin, 3}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [5,8,9,2,1,3,7,4,6], k = 2
     *  Output: 13
     *
     *  Input: root = [1,2,null,3], k = 1
     *  Output: 3
     */

    Solution cSolution;
    TreeNode* pRoot;
    long long answer;
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
        cout << "], k = " << testData[i].k << "\n";
        pRoot = buildBinaryTree(testData[i].nums, 0);

        answer = cSolution.kthLargestLevelSum(pRoot, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
