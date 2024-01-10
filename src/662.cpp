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
    int widthOfBinaryTree(TreeNode* root) {
        int retVal = 1;

        vector<pair<TreeNode*, unsigned long long>> level;
        level.emplace_back(root, 1L);
        while (level.empty() == false) {
            unsigned long long maxValue = retVal;
            retVal = max(maxValue, level.back().second - level[0].second + 1);

            vector<pair<TreeNode*, unsigned long long>> tmp;
            for (auto& [node, index] : level) {
                if (node->left) {
                    tmp.emplace_back(node->left, index * 2);
                }
                if (node->right) {
                    tmp.emplace_back(node->right, index * 2 + 1);
                }
            }
            level = move(tmp);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 3, 2, 5, 3, numeric_limits<int>::min(), 9}},
                             {{1, 3, 2, 5, numeric_limits<int>::min(), numeric_limits<int>::min(), 9, 6,
                               numeric_limits<int>::min(), numeric_limits<int>::max(), numeric_limits<int>::max(),
                               numeric_limits<int>::max(), numeric_limits<int>::max(), 7}},
                             {{1, 3, 2, 5}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [1,3,2,5,3,null,9]
     *  Output: 4
     *
     *  Input: root = [1,3,2,5,null,null,9,6,null,7]
     *  Output: 7
     *
     *  Input: root = [1,3,2,5]
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
        answer = cSolution.widthOfBinaryTree(pRoot);
        cout << "Output: " << answer << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
