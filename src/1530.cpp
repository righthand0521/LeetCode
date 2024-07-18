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
   private:
    void traverseTree(TreeNode* currNode, TreeNode* prevNode, unordered_map<TreeNode*, vector<TreeNode*>>& graph,
                      unordered_set<TreeNode*>& leafNodes) {
        if (currNode == nullptr) {
            return;
        }

        if ((currNode->left == nullptr) && (currNode->right == nullptr)) {
            leafNodes.insert(currNode);
        }
        if (prevNode != nullptr) {
            graph[prevNode].push_back(currNode);
            graph[currNode].push_back(prevNode);
        }
        traverseTree(currNode->left, currNode, graph, leafNodes);
        traverseTree(currNode->right, currNode, graph, leafNodes);
    }

   public:
    int countPairs(TreeNode* root, int distance) {
        int retVal = 0;

        unordered_map<TreeNode*, vector<TreeNode*>> graph;
        unordered_set<TreeNode*> leafNodes;
        traverseTree(root, nullptr, graph, leafNodes);

        for (auto leaf : leafNodes) {
            queue<TreeNode*> bfsQueue;
            bfsQueue.push(leaf);

            unordered_set<TreeNode*> seen;
            seen.insert(leaf);

            // Go through all nodes that are within the given distance of the current leaf node
            for (int i = 0; i <= distance; i++) {
                int bfsQueueSize = bfsQueue.size();
                for (int j = 0; j < bfsQueueSize; j++) {
                    TreeNode* currNode = bfsQueue.front();
                    bfsQueue.pop();
                    if ((leafNodes.count(currNode) != 0) && (currNode != leaf)) {
                        retVal++;
                    }
                    if (graph.count(currNode) != 0) {
                        for (auto neighbor : graph[currNode]) {
                            if (seen.count(neighbor) == 0) {
                                bfsQueue.push(neighbor);
                                seen.insert(neighbor);
                            }
                        }
                    }
                }
            }
        }

        retVal /= 2;

        return retVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> nums;
        int distance;
    };
    vector<subject> testData{{{1, 2, 3, imin, 4}, 3},
                             {{1, 2, 3, 4, 5, 6, 7}, 3},
                             {{7, 1, 4, 6, imin, 5, 3, imin, imin, imax, imax, imin, imin, imin, 2}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [1,2,3,null,4], distance = 3
     *  Output: 1
     *
     *  Input: root = [1,2,3,4,5,6,7], distance = 3
     *  Output: 2
     *
     *  Input: root = [7,1,4,6,null,5,3,null,null,null,null,null,2], distance = 3
     *  Output: 1
     */

    Solution cSolution;
    TreeNode* pRoot;
    int answer;
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
        cout << "], distance = " << testData[i].distance << "\n";
        pRoot = buildBinaryTree(testData[i].nums, 0);

        answer = cSolution.countPairs(pRoot, testData[i].distance);
        cout << "Output: " << answer << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
