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
    void dfs(TreeNode* root, int level, vector<int>& sum) {
        int sumSize = sum.size();
        if (level == sumSize) {
            sum.emplace_back(root->val);
        } else {
            sum[level] += root->val;
        }

        if (root->left != nullptr) {
            dfs(root->left, level + 1, sum);
        }
        if (root->right != nullptr) {
            dfs(root->right, level + 1, sum);
        }
    }
    int bfs(TreeNode* root) {
        int retVal = 0;

        int maxSum = numeric_limits<int>::min();
        int level = 0;
        queue<TreeNode*> bfsQueue;
        bfsQueue.emplace(root);
        while (bfsQueue.empty() == false) {
            ++level;
            int sum = 0;
            int bfsQueueCount = bfsQueue.size();
            for (int i = 0; i < bfsQueueCount; ++i) {
                TreeNode* node = bfsQueue.front();
                bfsQueue.pop();
                sum += node->val;

                if (node->left != nullptr) {
                    bfsQueue.emplace(node->left);
                }
                if (node->right != nullptr) {
                    bfsQueue.emplace(node->right);
                }
            }

            if (maxSum < sum) {
                maxSum = sum;
                retVal = level;
            }
        }

        return retVal;
    }
    int maxLevelSum(TreeNode* root) {
        int retVal = 0;

        if (root == nullptr) {
            return retVal;
        }

#if (DFS)
        vector<int> sum;
        dfs(root, 0, sum);
        retVal = distance(sum.begin(), max_element(sum.begin(), sum.end())) + 1;
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
    vector<subject> testData{{{1, 7, 0, 7, -8, numeric_limits<int>::min(), numeric_limits<int>::min()}},
                             {{989, numeric_limits<int>::min(), 10250, 98693, -89388, numeric_limits<int>::min(),
                               numeric_limits<int>::min(), numeric_limits<int>::min(), -32127}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [1,7,0,7,-8,null,null]
     *  Output: 2
     *
     *  Input: root = [989,null,10250,98693,-89388,null,null,null,-32127]
     *  Output: 2
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

        answer = cSolution.maxLevelSum(pRoot);
        cout << "Output: " << answer << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
