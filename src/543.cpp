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
    int diameter = 0;

   public:
    int maxDepth(TreeNode* root) {
        int retVal = 0;

        if (root == NULL) {
            return retVal;
        }
        int left = maxDepth(root->left);
        int right = maxDepth(root->right);
        diameter = max(diameter, left + right);
        retVal = max(left, right) + 1;

        return retVal;
    }
    int diameterOfBinaryTree(TreeNode* root) {
        int retVal = 0;

        diameter = 0;

        if (root == nullptr) {
            return retVal;
        }
        maxDepth(root);
        retVal = diameter;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 3, 4, 5}}, {{1, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [1,2,3,4,5]
     *  Output: 3
     *
     *  Input: root = [1,2]
     *  Output: 1
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

        answer = cSolution.diameterOfBinaryTree(pRoot);
        cout << "Output: " << answer << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
