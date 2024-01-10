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
#define DEPTH_FIRST_SEARCH (1)
#define BREADTH_FIRST_SEARCH (1)
   public:
#if (DEPTH_FIRST_SEARCH)
    int dfs(TreeNode* pRoot, int sum) {
        int retVal = 0;

        if (pRoot == nullptr) {
            return retVal;
        }

        retVal = 10 * sum + pRoot->val;
        if ((pRoot->left == nullptr) && (pRoot->right == nullptr)) {
            return retVal;
        }
        retVal = dfs(pRoot->left, retVal) + dfs(pRoot->right, retVal);

        return retVal;
    }
#elif (BREADTH_FIRST_SEARCH)
    int bfs(TreeNode* pRoot) {
        int retVal = 0;

        queue<TreeNode*> bfsNodeQueue;
        bfsNodeQueue.push(pRoot);

        queue<int> bfsSumQueue;
        bfsSumQueue.push(pRoot->val);

        while (bfsNodeQueue.empty() == false) {
            TreeNode* pCurrent = bfsNodeQueue.front();
            bfsNodeQueue.pop();

            int sum = bfsSumQueue.front();
            bfsSumQueue.pop();

            if ((pCurrent->left == nullptr) && (pCurrent->right == nullptr)) {
                retVal += sum;
                continue;
            }

            if (pCurrent->left != nullptr) {
                bfsNodeQueue.push(pCurrent->left);
                bfsSumQueue.push(sum * 10 + pCurrent->left->val);
            }
            if (pCurrent->right != nullptr) {
                bfsNodeQueue.push(pCurrent->right);
                bfsSumQueue.push(sum * 10 + pCurrent->right->val);
            }
        }

        return retVal;
    }
#endif
    int sumNumbers(TreeNode* root) {
        int retVal = 0;

#if (DEPTH_FIRST_SEARCH)
        cout << "DEPTH_FIRST_SEARCH\n";
        retVal = dfs(root, 0);
#elif (BREADTH_FIRST_SEARCH)
        cout << "BREADTH_FIRST_SEARCH\n";
        retVal = bfs(root);
#endif

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 3}}, {{4, 9, 0, 5, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [1,2,3]
     *  Output: 25
     *
     *  Input: root = [4,9,0,5,1]
     *  Output: 1026
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

        answer = cSolution.sumNumbers(pRoot);
        cout << "Output: " << answer << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
