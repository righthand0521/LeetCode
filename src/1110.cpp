#include <algorithm>
#include <iostream>
#include <queue>
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
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        vector<TreeNode*> retVal;

        if (root == nullptr) {
            return retVal;
        }

        unordered_set<int> toDeleteSet(to_delete.begin(), to_delete.end());
        queue<TreeNode*> nodesQueue;
        nodesQueue.push(root);
        while (nodesQueue.empty() == false) {
            TreeNode* currentNode = nodesQueue.front();
            nodesQueue.pop();

            if (currentNode->left) {
                nodesQueue.push(currentNode->left);
                // Disconnect the left child if it needs to be deleted
                if (toDeleteSet.find(currentNode->left->val) != toDeleteSet.end()) {
                    currentNode->left = nullptr;
                }
            }

            if (currentNode->right) {
                nodesQueue.push(currentNode->right);
                // Disconnect the right child if it needs to be deleted
                if (toDeleteSet.find(currentNode->right->val) != toDeleteSet.end()) {
                    currentNode->right = nullptr;
                }
            }

            // If the current node needs to be deleted, add its non-null children to the forest
            if (toDeleteSet.find(currentNode->val) != toDeleteSet.end()) {
                if (currentNode->left) {
                    retVal.push_back(currentNode->left);
                }
                if (currentNode->right) {
                    retVal.push_back(currentNode->right);
                }

                if (currentNode != root) {
                    delete currentNode;
                }
            }
        }

        // Ensure the root is added to the forest if it is not to be deleted
        if (toDeleteSet.find(root->val) == toDeleteSet.end()) {
            retVal.push_back(root);
        } else {
            delete root;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> nums;
        vector<int> to_delete;
    };
    vector<subject> testData{
        {{1, 2, 3, 4, 5, 6, 7}, {3, 5}}, {{1, 2, 4, imin, 3}, {3}}, {{1, 2, 3, imin, imin, imin, 4}, {2, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [1,2,3,4,5,6,7], to_delete = [3,5]
     *  Output: [[1,2,null,4],[6],[7]]
     *
     *  Input: root = [1,2,4,null,3], to_delete = [3]
     *  Output: [[1,2,4]]
     *
     *  Input: root = [1,2,3,null,null,null,4], to_delete = [2,1]
     *  Output: [[3,null,4]]
     */

    TreeNode* pRoot;
    Solution cSolution;
    vector<TreeNode*> answer;
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
        cout << "], to_delete = [";
        for (long unsigned int j = 0; j < testData[i].to_delete.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].to_delete[j];
        }
        cout << "]\n";
        pRoot = buildBinaryTree(testData[i].nums, 0);

        answer = cSolution.delNodes(pRoot, testData[i].to_delete);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            int height = getTreeHeight(answer[j]);
            showTreeOutput(answer[j], height);
            freeTreeNode(answer[j]);
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
