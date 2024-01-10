#include <algorithm>
#include <iostream>
#include <stack>
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
    void preorder(TreeNode* root, vector<int>& retVal) {
        if (root == nullptr) {
            return;
        }
        retVal.push_back(root->val);
        preorder(root->left, retVal);
        preorder(root->right, retVal);
    }
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> retVal;

        preorder(root, retVal);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{
        {{1, numeric_limits<int>::min(), 2, numeric_limits<int>::max(), numeric_limits<int>::max(), 3}}, {{}}, {{1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [1,null,2,3]
     *  Output: [1,2,3]
     *
     *  Input: root = []
     *  Output: []
     *
     *  Input: root = [1]
     *  Output: [1]
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

        answer = cSolution.preorderTraversal(pRoot);
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
