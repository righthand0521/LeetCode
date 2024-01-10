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
   public:
    vector<TreeNode*> generateTrees(int start, int end) {
        vector<TreeNode*> retVal;

        if (start > end) {
            retVal = {nullptr};
            return retVal;
        }

        for (int i = start; i <= end; i++) {
            vector<TreeNode*> leftTrees = generateTrees(start, i - 1);
            vector<TreeNode*> rightTrees = generateTrees(i + 1, end);

            for (auto& left : leftTrees) {
                for (auto& right : rightTrees) {
                    TreeNode* currTree = new TreeNode(i);
                    currTree->left = left;
                    currTree->right = right;
                    retVal.emplace_back(currTree);
                }
            }
        }

        return retVal;
    }
    vector<TreeNode*> generateTrees(int n) {
        vector<TreeNode*> retVal;

        if (n == 0) {
            return retVal;
        }
        retVal = generateTrees(1, n);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{3}, {1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 3
     *  Output: [[1,null,2,null,3],[1,null,3,2],[2,1,3],[3,1,null,null,2],[3,2,null,1]]
     *
     *  Input: n = 1
     *  Output: [[1]]
     */

    Solution cSolution;
    vector<TreeNode*> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.generateTrees(testData[i].n);
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
