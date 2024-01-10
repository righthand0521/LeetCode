#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
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
    void toUndirectedGraph(TreeNode* root, unordered_map<int, vector<int>>& adjacency) {
        if (root->left != nullptr) {
            adjacency[root->val].emplace_back(root->left->val);
            adjacency[root->left->val].emplace_back(root->val);
            toUndirectedGraph(root->left, adjacency);
        }

        if (root->right != nullptr) {
            adjacency[root->val].emplace_back(root->right->val);
            adjacency[root->right->val].emplace_back(root->val);
            toUndirectedGraph(root->right, adjacency);
        }
    }
    int amountOfTime(TreeNode* root, int start) {
        int retVal = 0;

        unordered_map<int, vector<int>> adjacency;
        toUndirectedGraph(root, adjacency);

        queue<int> bfsQueue;
        bfsQueue.push(start);
        unordered_set<int> visited;
        visited.insert(start);

        retVal = -1;
        while (bfsQueue.empty() == false) {
            int bfsQueueSize = bfsQueue.size();
            for (int i = 0; i < bfsQueueSize; ++i) {
                int leaf = bfsQueue.front();
                bfsQueue.pop();
                for (int neighbor : adjacency[leaf]) {
                    if (visited.find(neighbor) == visited.end()) {
                        visited.insert(neighbor);
                        bfsQueue.push(neighbor);
                    }
                }
            }
            retVal++;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> nums;
        int start;
    };
    vector<subject> testData{{{1, 5, 3, imin, 4, 10, 6, imax, imax, 9, 2}, 3}, {{1}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [1,5,3,null,4,10,6,9,2], start = 3
     *  Output: 4
     *
     *  Input: root = [1], start = 1
     *  Output: 0
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
        cout << "], start = " << testData[i].start << "\n";
        pRoot = buildBinaryTree(testData[i].nums, 0);

        answer = cSolution.amountOfTime(pRoot, testData[i].start);
        cout << "Output: " << answer << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
