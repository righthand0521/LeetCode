#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
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
#define DFS (0)
#define BFS (1)
   public:
    Solution() {
#if (DFS)
        cout << "Depth-First Search\n\n";
#elif (BFS)
        cout << "Breadth-First Search\n\n";
#endif
    }
#if (DFS)
    int dfsDepth(TreeNode* root) {
        int retVal = 0;

        if (root->left) {
            retVal = max(retVal, dfsDepth(root->left) + 1);
        }
        if (root->right) {
            retVal = max(retVal, dfsDepth(root->right) + 1);
        }

        return retVal;
    }
    void dfs(vector<vector<string>>& retVal, TreeNode* root, int row, int col, int& height) {
        retVal[row][col] = to_string(root->val);
        if (root->left) {
            dfs(retVal, root->left, row + 1, col - (1 << (height - row - 1)), height);
        }
        if (root->right) {
            dfs(retVal, root->right, row + 1, col + (1 << (height - row - 1)), height);
        }
    }
#elif (BFS)
    int bfsDepth(TreeNode* root) {
        int retVal = -1;

        queue<TreeNode*> record;
        record.push(root);
        while (record.empty() == false) {
            int recordSize = record.size();
            retVal++;
            while (recordSize) {
                recordSize--;

                auto node = record.front();
                record.pop();
                if (node->left) {
                    record.push(node->left);
                }
                if (node->right) {
                    record.push(node->right);
                }
            }
        }

        return retVal;
    }
    void bfs(vector<vector<string>>& retVal, TreeNode* root, int n, int height) {
        queue<tuple<TreeNode*, int, int>> bfsQueue;
        bfsQueue.push({root, 0, (n - 1) / 2});

        while (bfsQueue.empty() == false) {
            auto node = bfsQueue.front();
            bfsQueue.pop();

            int row = get<1>(node);
            int col = get<2>(node);
            retVal[row][col] = to_string(get<0>(node)->val);

            if (get<0>(node)->left) {
                bfsQueue.push({get<0>(node)->left, row + 1, col - (1 << (height - row - 1))});
            }
            if (get<0>(node)->right) {
                bfsQueue.push({get<0>(node)->right, row + 1, col + (1 << (height - row - 1))});
            }
        }
    }
#endif
    vector<vector<string>> printTree(TreeNode* root) {
#if (DFS)
        int height = dfsDepth(root);
        int m = height + 1;
        int n = (1 << (height + 1)) - 1;
        vector<vector<string>> retVal(m, vector<string>(n, ""));
        dfs(retVal, root, 0, (n - 1) / 2, height);
#elif (BFS)
        int height = bfsDepth(root);
        int m = height + 1;
        int n = (1 << (height + 1)) - 1;
        vector<vector<string>> retVal(m, vector<string>(n, ""));
        bfs(retVal, root, n, height);
#endif

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2}}, {{1, 2, 3, numeric_limits<int>::min(), 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [1,2]
     *  Output:
     *  [["","1",""],
     *   ["2","",""]]
     *
     *  Input: root = [1,2,3,null,4]
     *  Output:
     *  [["","","","1","","",""],
     *   ["","2","","","","3",""],
     *   ["","","4","","","",""]]
     */

    Solution cSolution;
    TreeNode* pRoot;
    vector<vector<string>> answer;
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

        answer = cSolution.printTree(pRoot);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < answer[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << "\"" << answer[j][k] << "\"";
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
