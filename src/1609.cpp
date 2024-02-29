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
    bool isEvenOddTree(TreeNode* root) {
        bool retVal = false;

        int level = 0;
        queue<TreeNode*> bfsQueue;
        bfsQueue.push(root);
        while (bfsQueue.empty() == false) {
            int previous;
            if (level % 2 == 0) {
                previous = numeric_limits<int>::min();
            } else {
                previous = numeric_limits<int>::max();
            }

            int bfsQueueSize = bfsQueue.size();
            for (int i = 0; i < bfsQueueSize; ++i) {
                TreeNode* current = bfsQueue.front();
                bfsQueue.pop();
                int value = current->val;
                if (level % 2 == 0) {
                    if (value % 2 == 0) {
                        return retVal;
                    } else if (value <= previous) {
                        return retVal;
                    } else {
                        previous = value;
                    }
                } else {
                    if (value % 2 != 0) {
                        return retVal;
                    } else if (value >= previous) {
                        return retVal;
                    } else {
                        previous = value;
                    }
                }

                if (current->left != nullptr) {
                    bfsQueue.push(current->left);
                }
                if (current->right != nullptr) {
                    bfsQueue.push(current->right);
                }
            }
            level++;
        }
        retVal = true;

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
        {{1, 10, 4, 3, imin, 7, 9, 12, 8, imax, imax, 6, imin, imin, 2}}, {{5, 4, 2, 3, 3, 7}}, {{5, 9, 1, 3, 5, 7}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [1,10,4,3,null,7,9,12,8,6,null,null,2]
     *  Output: true
     *
     *  Input: root = [5,4,2,3,3,7]
     *  Output: false
     *
     *  Input: root = [5,9,1,3,5,7]
     *  Output: false
     */

    Solution cSolution;
    TreeNode* pRoot;
    bool answer;
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

        answer = cSolution.isEvenOddTree(pRoot);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
