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
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> retVal;

        if (root == nullptr) {
            return retVal;
        }

        queue<TreeNode*> bfsQueue;
        bfsQueue.push(root);
        while (bfsQueue.empty() == false) {
            double sum = 0;
            int currentLevelSize = bfsQueue.size();
            for (int i = 1; i <= currentLevelSize; ++i) {
                auto node = bfsQueue.front();
                bfsQueue.pop();
                sum += node->val;

                if (node->left != nullptr) {
                    bfsQueue.push(node->left);
                }
                if (node->right != nullptr) {
                    bfsQueue.push(node->right);
                }
            }

            retVal.emplace_back(sum / currentLevelSize);
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
    vector<subject> testData{{{3, 9, 20, imin, imin, 15, 7}}, {{3, 9, 20, 15, 7}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [3,9,20,null,null,15,7]
     *  Output: [3.00000,14.50000,11.00000]
     *
     *  Input: root = [3,9,20,15,7]
     *  Output: [3.00000,14.50000,11.00000]
     */

    Solution cSolution;
    TreeNode* pRoot;
    vector<double> answer;
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

        answer = cSolution.averageOfLevels(pRoot);
        cout.setf(ios::fixed);
        cout.precision(5);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
