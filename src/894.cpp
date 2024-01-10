#include <algorithm>
#include <iostream>
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
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
#define RECURSION (0)
#define ITERATIVE (1)
   public:
    unordered_map<int, vector<TreeNode*>> memo;

    Solution() {
#if (RECURSION)
        cout << "Recursion\n\n";
#elif (ITERATIVE)
        cout << "Iterative\n\n";
#endif
    }
    vector<TreeNode*> allPossibleFBT(int n) {
        vector<TreeNode*> retVal;

        if ((n % 2) == 0) {
            return retVal;
        }

#if (RECURSION)
        if (n == 1) {
            retVal.emplace_back(new TreeNode(0));
            return retVal;
        }

        if (memo.find(n) != memo.end()) {
            retVal = memo[n];
            return retVal;
        }

        for (int i = 1; i < n; i += 2) {
            vector<TreeNode*> left = allPossibleFBT(i);
            vector<TreeNode*> right = allPossibleFBT(n - i - 1);
            for (auto l : left) {
                for (auto r : right) {
                    TreeNode* root = new TreeNode(0, l, r);
                    retVal.emplace_back(root);
                }
            }
        }
        memo[n] = retVal;
#elif (ITERATIVE)
        vector<vector<TreeNode*>> dp(n + 1);

        dp[1].push_back(new TreeNode(0));
        for (int count = 3; count <= n; count += 2) {
            for (int i = 1; i < count - 1; i += 2) {
                int j = count - 1 - i;
                for (auto left : dp[i]) {
                    for (auto right : dp[j]) {
                        TreeNode* root = new TreeNode(0, left, right);
                        dp[count].push_back(root);
                    }
                }
            }
        }

        retVal = dp[n];
#endif

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{7}, {3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 7
     *  Output: [[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,0,0,0,0],
     *  [0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]
     *
     *  Input: n = 3
     *  Output: [[0,0,0]]
     */

    Solution cSolution;
    vector<TreeNode*> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.allPossibleFBT(testData[i].n);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            int height = getTreeHeight(answer[j]);
            cout << ((j == 0) ? "" : ",");
            cout << "[";
            showTreeOutput(answer[j], height);
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";

        // freeTreeNode(answer);
    }

    return EXIT_SUCCESS;
}
