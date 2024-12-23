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
   private:
    const int SHIFT = 20;
    const int MASK = 0xFFFFF;

   public:
    int minimumOperations(TreeNode* root) {
        int retVal = 0;

        // Process tree level by level using BFS
        queue<TreeNode*> queue;
        queue.push(root);
        while (queue.empty() == false) {
            int levelSize = queue.size();
            vector<long long> nodes(levelSize);

            // Store node values with encoded positions
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = queue.front();
                queue.pop();
                // Encode value and index: high 20 bits = value, low 20 bits = index
                nodes[i] = (static_cast<long long>(node->val) << SHIFT) + i;

                if (node->left != nullptr) {
                    queue.push(node->left);
                }
                if (node->right != nullptr) {
                    queue.push(node->right);
                }
            }

            // Sort nodes by their values (high 20 bits)
            sort(nodes.begin(), nodes.end());

            // Count swaps needed to match indices with original positions
            for (int i = 0; i < levelSize; i++) {
                int origPos = static_cast<int>(nodes[i] & MASK);
                if (origPos != i) {
                    // Swap nodes and decrement i to recheck current position
                    swap(nodes[i], nodes[origPos]);
                    retVal++;
                    i--;
                }
            }
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
        {{1, 4, 3, 7, 6, 8, 5, imin, imin, imin, imin, 9, imin, 10}}, {{1, 3, 2, 7, 6, 5, 4}}, {{1, 2, 3, 4, 5, 6}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [1,4,3,7,6,8,5,null,null,null,null,9,null,10]
     *  Output: 3
     *
     *  Input: root = [1,3,2,7,6,5,4]
     *  Output: 3
     *
     *  Input: root = [1,2,3,4,5,6]
     *  Output: 0
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
        cout << "]\n";
        pRoot = buildBinaryTree(testData[i].nums, 0);

        answer = cSolution.minimumOperations(pRoot);
        cout << "Output: " << answer << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
