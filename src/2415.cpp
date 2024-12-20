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
    TreeNode* reverseOddLevels(TreeNode* root) {
        TreeNode* retVal = root;

        if (retVal == nullptr) {
            return retVal;
        }

        queue<TreeNode*> bfsQueue;
        bfsQueue.push(retVal);

        int level = 0;
        while (bfsQueue.empty() == false) {
            vector<TreeNode*> currentLevelNodes;
            int bfsQueueSize = bfsQueue.size();
            for (int i = 0; i < bfsQueueSize; i++) {
                TreeNode* node = bfsQueue.front();
                bfsQueue.pop();

                currentLevelNodes.push_back(node);
                if (node->left) {
                    bfsQueue.push(node->left);
                }
                if (node->right) {
                    bfsQueue.push(node->right);
                }
            }

            if (level % 2 == 1) {
                int left = 0;
                int right = currentLevelNodes.size() - 1;
                while (left < right) {
                    int temp = currentLevelNodes[left]->val;
                    currentLevelNodes[left]->val = currentLevelNodes[right]->val;
                    currentLevelNodes[right]->val = temp;
                    left++;
                    right--;
                }
            }

            level++;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{
        {{2, 3, 5, 8, 13, 21, 34}}, {{7, 13, 11}}, {{0, 1, 2, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [2,3,5,8,13,21,34]
     *  Output: [2,5,3,8,13,21,34]
     *
     *  Input: root = [7,13,11]
     *  Output: [7,11,13]
     *
     *  Input: root = [0,1,2,0,0,0,0,1,1,1,1,2,2,2,2]
     *  Output: [0,2,1,0,0,0,0,2,2,2,2,1,1,1,1]
     */

    Solution cSolution;
    TreeNode* pRoot;
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
        cout << "]\n";
        pRoot = buildBinaryTree(testData[i].nums, 0);

        pRoot = cSolution.reverseOddLevels(pRoot);
        int height = getTreeHeight(pRoot);
        cout << "Output: [";
        showTreeOutput(pRoot, height);
        cout << "]\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
