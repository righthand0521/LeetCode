#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
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
#define DFS (1)
#define BFS (1)
    Solution() {
#if (DFS)
        cout << "Depth-First Search\n\n";
#elif (BFS)
        cout << "Breadth-First Search\n\n";
#endif
    }
    void dfs(TreeNode* root, int targetSum, vector<int>& path, vector<vector<int>>& retVal) {
        if (root == nullptr) {
            return;
        }

        path.emplace_back(root->val);
        targetSum -= root->val;

        if ((root->left == nullptr) && (root->right == nullptr) && (targetSum == 0)) {
            retVal.emplace_back(path);
        }
        dfs(root->left, targetSum, path, retVal);
        dfs(root->right, targetSum, path, retVal);

        path.pop_back();
    }
    void bfs(TreeNode* root, int targetSum, vector<vector<int>>& retVal) {
        if (root == nullptr) {
            return;
        }

        unordered_map<TreeNode*, TreeNode*> parent;

        queue<TreeNode*> bfsQueue;
        bfsQueue.emplace(root);

        queue<int> targetSumQueue;
        targetSumQueue.emplace(0);

        while (bfsQueue.empty() == false) {
            TreeNode* node = bfsQueue.front();
            bfsQueue.pop();

            int sum = targetSumQueue.front() + node->val;
            targetSumQueue.pop();

            if ((node->left == nullptr) && (node->right == nullptr)) {
                if (sum == targetSum) {
                    vector<int> tmp;
                    while (node != nullptr) {
                        tmp.emplace_back(node->val);
                        node = parent[node];
                    }
                    reverse(tmp.begin(), tmp.end());
                    retVal.emplace_back(tmp);
                }
            } else {
                if (node->left != nullptr) {
                    parent[node->left] = node;
                    bfsQueue.emplace(node->left);
                    targetSumQueue.emplace(sum);
                }
                if (node->right != nullptr) {
                    parent[node->right] = node;
                    bfsQueue.emplace(node->right);
                    targetSumQueue.emplace(sum);
                }
            }
        }
    }
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> retVal;

#if (DFS)
        vector<int> path;
        dfs(root, targetSum, path, retVal);
#elif (BFS)
        bfs(root, targetSum, retVal);
#endif

        return retVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> nums;
        int targetSum;
    };
    vector<subject> testData{
        {{5, 4, 8, 11, imin, 13, 4, 7, 2, imax, imax, imin, imin, 5, 1}, 22}, {{1, 2, 3}, 5}, {{1, 2}, 0}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
     *  Output: [[5,4,11,2],[5,8,4,5]]
     *
     *  Input: root = [1,2,3], targetSum = 5
     *  Output: []
     *
     *  Input: root = [1,2], targetSum = 0
     *  Output: []
     */

    Solution cSolution;
    TreeNode* pRoot;
    vector<vector<int>> answer;
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
        cout << "], targetSum = " << testData[i].targetSum << "\n";
        pRoot = buildBinaryTree(testData[i].nums, 0);

        answer = cSolution.pathSum(pRoot, testData[i].targetSum);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < answer[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << answer[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}