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
    TreeNode *replaceValueInTree(TreeNode *root) {
        TreeNode *pRetVal = root;

        if (pRetVal == nullptr) {
            return pRetVal;
        }

        queue<TreeNode *> nodeQueue;
        nodeQueue.push(pRetVal);

        vector<int> levelSums;
        while (nodeQueue.empty() == false) {
            int levelSum = 0;

            int levelSize = nodeQueue.size();
            for (int i = 0; i < levelSize; ++i) {
                TreeNode *currentNode = nodeQueue.front();
                nodeQueue.pop();

                levelSum += currentNode->val;
                if (currentNode->left) {
                    nodeQueue.push(currentNode->left);
                }
                if (currentNode->right) {
                    nodeQueue.push(currentNode->right);
                }
            }

            levelSums.push_back(levelSum);
        }

        nodeQueue.push(pRetVal);
        int levelIndex = 1;
        pRetVal->val = 0;
        while (nodeQueue.empty() == false) {
            int levelSize = nodeQueue.size();
            for (int i = 0; i < levelSize; ++i) {
                TreeNode *currentNode = nodeQueue.front();
                nodeQueue.pop();

                int siblingSum = 0;
                siblingSum += ((currentNode->left != nullptr) ? (currentNode->left->val) : (0));
                siblingSum += ((currentNode->right != nullptr) ? (currentNode->right->val) : (0));

                if (currentNode->left) {
                    currentNode->left->val = levelSums[levelIndex] - siblingSum;
                    nodeQueue.push(currentNode->left);
                }
                if (currentNode->right) {
                    currentNode->right->val = levelSums[levelIndex] - siblingSum;
                    nodeQueue.push(currentNode->right);
                }
            }

            ++levelIndex;
        }

        return pRetVal;
    }
};

int main(int argc, char **argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{5, 4, 9, 1, 10, imin, 7}}, {{3, 1, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [5,4,9,1,10,null,7]
     *  Output: [0,0,0,7,7,null,11]
     *
     *  Input: root = [3,1,2]
     *  Output: [0,0,0]
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
        cout << "]\n";
        pRoot = buildBinaryTree(testData[i].nums, 0);

        pRoot = cSolution.replaceValueInTree(pRoot);
        int height = getTreeHeight(pRoot);
        cout << "Output: [";
        showTreeOutput(pRoot, height);
        cout << "]\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
