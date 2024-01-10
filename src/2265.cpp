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
    int answer = 0;

   public:
    pair<int, int> postorder(TreeNode* root) {
        pair<int, int> retval = {0, 0};
        if (root == nullptr) {
            return retval;
        }

        pair<int, int> left = postorder(root->left);
        pair<int, int> right = postorder(root->right);

        int subtreeSum = left.first + right.first + root->val;
        int subtreeNode = left.second + right.second + 1;
        if (root->val == subtreeSum / subtreeNode) {
            answer += 1;
        }
        retval = {subtreeSum, subtreeNode};

        return retval;
    }
    int averageOfSubtree(TreeNode* root) {
        int retVal = 0;

        if (root == nullptr) {
            return retVal;
        }

        answer = 0;
        postorder(root);
        retVal = answer;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{4, 8, 5, 0, 1, numeric_limits<int>::min(), 6}}, {{1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [4,8,5,0,1,null,6]
     *  Output: 5
     *
     *  Input: root = [1]
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

        answer = cSolution.averageOfSubtree(pRoot);
        cout << "Output: " << answer << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
