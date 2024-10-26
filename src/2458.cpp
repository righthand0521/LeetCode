#include <algorithm>
#include <iostream>
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
    void traverseLeftToRight(TreeNode* node, int currentHeight) {
        if (node == nullptr) {
            return;
        }

        // Store the maximum height if this node were removed
        maxHeightAfterRemoval[node->val] = currentMaxHeight;

        // Update the current maximum height
        currentMaxHeight = max(currentMaxHeight, currentHeight);

        // Traverse left subtree first, then right
        traverseLeftToRight(node->left, currentHeight + 1);
        traverseLeftToRight(node->right, currentHeight + 1);
    }
    void traverseRightToLeft(TreeNode* node, int currentHeight) {
        if (node == nullptr) {
            return;
        }

        // Update the maximum height if this node were removed
        maxHeightAfterRemoval[node->val] = max(maxHeightAfterRemoval[node->val], currentMaxHeight);

        // Update the current maximum height
        currentMaxHeight = max(currentHeight, currentMaxHeight);

        // Traverse right subtree first, then left
        traverseRightToLeft(node->right, currentHeight + 1);
        traverseRightToLeft(node->left, currentHeight + 1);
    }

   public:
    int maxHeightAfterRemoval[100001];  // Array to store the maximum height of the tree after removing each node
    int currentMaxHeight = 0;

    vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
        vector<int> retVal;

        currentMaxHeight = 0;
        traverseLeftToRight(root, 0);
        currentMaxHeight = 0;
        traverseRightToLeft(root, 0);

        for (int querie : queries) {
            retVal.emplace_back(maxHeightAfterRemoval[querie]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> nums;
        vector<int> queries;
    };
    vector<subject> testData{{{1, 3, 4, 2, imin, 6, 5, imin, imin, imax, imax, imin, imin, imin, 7}, {4}},
                             {{5, 8, 9, 2, 1, 3, 7, 4, 6}, {3, 2, 4, 8}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [1,3,4,2,null,6,5,null,null,null,null,null,7], queries = [4]
     *  Output: [2]
     *
     *  Input: root = [5,8,9,2,1,3,7,4,6], queries = [3,2,4,8]
     *  Output: [3,2,3,2]
     */

    Solution cSolution;
    TreeNode* pRoot;
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
        cout << "], queries = [";
        for (long unsigned int j = 0; j < testData[i].queries.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].queries[j];
        }
        cout << "]\n";

        pRoot = buildBinaryTree(testData[i].nums, 0);

        answer = cSolution.treeQueries(pRoot, testData[i].queries);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";

        freeTreeNode(pRoot);
        pRoot = nullptr;
    }

    return EXIT_SUCCESS;
}
