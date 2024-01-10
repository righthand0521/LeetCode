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
#define RECURSIVE (0)
#define ITERATIVE (1)
   public:
    Solution() {
#if (RECURSIVE)
        cout << "RECURSIVE\n\n";
#elif (ITERATIVE)
        cout << "ITERATIVE\n\n";
#endif
    }
    void inorder(TreeNode* root, vector<int>& retVal) {
#if (RECURSIVE)
        if (root == nullptr) {
            return;
        }
        inorder(root->left, retVal);
        retVal.push_back(root->val);
        inorder(root->right, retVal);
#elif (ITERATIVE)
        stack<TreeNode*> stackKeep;
        while ((root != nullptr) || (stackKeep.empty() == false)) {
            while (root != nullptr) {
                stackKeep.push(root);
                root = root->left;
            }
            root = stackKeep.top();
            stackKeep.pop();
            retVal.push_back(root->val);
            root = root->right;
        }
#endif
    }
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> retVal;

        inorder(root, retVal);

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
     *  Output: [1,3,2]
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

        answer = cSolution.inorderTraversal(pRoot);
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
