#include <algorithm>
#include <iostream>
#include <limits>
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
#define DFS (1)
#define BFS (1)
   public:
    Solution() {
#if (DFS)
        cout << "Depth-First Search\n\n";
#elif (BFS)
        cout << "Breadth-First Search\n\n";
#endif
    }
#if (DFS)
    int dfs(TreeNode* root) {
        int retVal = 0;

        if (root == nullptr) {
            return retVal;
        }

        if ((root->left == nullptr) && (root->right == nullptr)) {
            retVal += 1;
            return retVal;
        }

        if (root->left == nullptr) {
            retVal = 1 + dfs(root->right);
        } else if (root->right == nullptr) {
            retVal = 1 + dfs(root->left);
        } else {
            retVal = 1 + min(dfs(root->left), dfs(root->right));
        }

        return retVal;
    }
#elif (BFS)
    int bfs(TreeNode* root) {
        int retVal = 0;

        queue<TreeNode*> bfsQueue;
        bfsQueue.emplace(root);
        retVal = 1;
        while (bfsQueue.empty() == false) {
            int bfsQueueSize = bfsQueue.size();
            for (int i = 0; i < bfsQueueSize; ++i) {
                TreeNode* pCurrent = bfsQueue.front();
                bfsQueue.pop();

                if ((pCurrent->left == nullptr) && (pCurrent->right == nullptr)) {
                    return retVal;
                }

                if (pCurrent->left != nullptr) {
                    bfsQueue.emplace(pCurrent->left);
                }
                if (pCurrent->right != nullptr) {
                    bfsQueue.emplace(pCurrent->right);
                }
            }
            ++retVal;
        }

        return retVal;
    }
#endif
    int minDepth(TreeNode* root) {
        int retVal = 0;

        if (root == nullptr) {
            return retVal;
        }

#if (DFS)
        retVal = dfs(root);
#elif (BFS)
        retVal = bfs(root);
#endif

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
        {{3, 9, 20, imin, imin, 15, 7}},
        {{2,    imin, 3,    imax, imax, imin, 4,    imax, imax, imax, imax, imax, imax, imin, 5, imax,
          imax, imax, imax, imax, imax, imax, imax, imax, imax, imax, imax, imax, imax, imin, 6}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [3,9,20,null,null,15,7]
     *  Output: 2
     *
     *  Input: root = [2,null,3,null,4,null,5,null,6]
     *  Output: 5
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

        answer = cSolution.minDepth(pRoot);
        cout << "Output: " << answer << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
