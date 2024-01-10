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
    string tree2str(TreeNode* root) {
        string retVal = "";

        if (root == nullptr) {
            return retVal;
        }

        retVal += to_string(root->val);

        if (root->left != nullptr) {
            retVal += "(" + tree2str(root->left) + ")";
        }

        if (root->right != nullptr) {
            if (root->left == nullptr) {
                retVal += "()";
            }
            retVal += "(" + tree2str(root->right) + ")";
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 3, 4}}, {{1, 2, 3, numeric_limits<int>::min(), 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [1,2,3,4]
     *  Output: "1(2(4))(3)"
     *
     *  Input: root = [1,2,3,null,4]
     *  Output: "1(2()(4))(3)"
     */

    Solution cSolution;
    TreeNode* pRoot;
    string answer;
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

        answer = cSolution.tree2str(pRoot);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
