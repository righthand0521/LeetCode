#include <algorithm>
#include <iostream>
#include <limits>
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
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
   public:
    void binaryTreeToGraph(TreeNode* root, unordered_map<int, vector<int>>& graph) {
        if (root == nullptr) {
            return;
        }

        if (root->left != nullptr) {
            graph[root->val].emplace_back(root->left->val);
            graph[root->left->val].emplace_back(root->val);
            binaryTreeToGraph(root->left, graph);
        }
        if (root->right != nullptr) {
            graph[root->val].emplace_back(root->right->val);
            graph[root->right->val].emplace_back(root->val);
            binaryTreeToGraph(root->right, graph);
        }
    }
    vector<int> bfs(TreeNode* root, TreeNode* target, int k, unordered_map<int, vector<int>>& graph) {
        vector<int> retVal;

        queue<pair<int, int>> bfsQueue;
        bfsQueue.emplace(target->val, 0);

        vector<int> visited;
        visited.emplace_back(target->val);

        while (bfsQueue.empty() == false) {
            auto [current, distance] = bfsQueue.front();
            bfsQueue.pop();
            if (distance == k) {
                retVal.emplace_back(current);
            }

            for (auto neighbor : graph[current]) {
                if (find(visited.begin(), visited.end(), neighbor) != visited.end()) {
                    continue;
                }
                bfsQueue.emplace(neighbor, distance + 1);
                visited.emplace_back(neighbor);
            }
        }

        return retVal;
    }
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        vector<int> retVal;

        unordered_map<int, vector<int>> graph;
        binaryTreeToGraph(root, graph);
        retVal = bfs(root, target, k, graph);

        return retVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> nums;
        int target;
        int k;
    };
    vector<subject> testData{{{3, 5, 1, 6, 2, 0, 8, imin, imin, 7, 4}, 5, 2}, {{1}, 1, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
     *  Output: [7,4,1]
     *
     *  Input: root = [1], target = 1, k = 3
     *  Output: []
     */

    Solution cSolution;
    TreeNode* pRoot;
    TreeNode* pTarget;
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
        cout << "], target = " << testData[i].target << ", k = " << testData[i].k << "\n";
        pRoot = buildBinaryTree(testData[i].nums, 0);

        if (testData[i].target == 5) {
            pTarget = pRoot->left;
        } else {
            pTarget = pRoot;
        }
        answer = cSolution.distanceK(pRoot, pTarget, testData[i].k);
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
