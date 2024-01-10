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
#define DFS (0)
#define BFS (1)
    Solution() {
#if (DFS)
        cout << "Depth-First Search\n\n";
#elif (BFS)
        cout << "Breadth-First Search\n\n";
#endif
    }
    void dfs(TreeNode* root, int level, vector<int>& answer) {
        if (root == nullptr) {
            return;
        }

        int answerSize = answer.size();
        if (level == answerSize) {
            answer.emplace_back(root->val);
        } else {
            answer[level] = max(answer[level], root->val);
        }

        dfs(root->left, level + 1, answer);
        dfs(root->right, level + 1, answer);
    }
    vector<int> bfs(TreeNode* root) {
        vector<int> retVal;

        queue<TreeNode*> bfsQueue;
        bfsQueue.emplace(root);

        while (bfsQueue.empty() == false) {
            int maxValue = numeric_limits<int>::min();  // -2^31 <= Node.val <= 2^31 - 1

            int bfsQueueCount = bfsQueue.size();
            for (int i = 0; i < bfsQueueCount; ++i) {
                TreeNode* node = bfsQueue.front();
                bfsQueue.pop();

                maxValue = max(maxValue, node->val);

                if (node->left != nullptr) {
                    bfsQueue.emplace(node->left);
                }
                if (node->right != nullptr) {
                    bfsQueue.emplace(node->right);
                }
            }

            retVal.emplace_back(maxValue);
        }

        return retVal;
    }
    vector<int> largestValues(TreeNode* root) {
        vector<int> retVal;

        if (root == nullptr) {
            return retVal;
        }

#if (DFS)
        dfs(root, 0, retVal);
#elif (BFS)
        retVal = bfs(root);
#endif

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 3, 2, 5, 3, numeric_limits<int>::max(), 9}}, {{1, 2, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [1,3,2,5,3,null,9]
     *  Output: [1,3,9]
     *
     *  Input: root = [1,2,3]
     *  Output: [1,3]
     */

    Solution cSolution;
    TreeNode* pRoot;
    vector<int> answer;
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

        answer = cSolution.largestValues(pRoot);
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
