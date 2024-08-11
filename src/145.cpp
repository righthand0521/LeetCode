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
    void postorder(TreeNode *root, vector<int> &retVal) {
        if (root == nullptr) {
            return;
        }
        postorder(root->left, retVal);
        postorder(root->right, retVal);
        retVal.push_back(root->val);
    }
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> retVal;

        postorder(root, retVal);

        return retVal;
    }
};

int main(int argc, char **argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, imin, 2, imax, imax, 3}}, {{}}, {{1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [1,null,2,3]
     *  Output: [3,2,1]
     *
     *  Input: root = []
     *  Output: []
     *
     *  Input: root = [1]
     *  Output: [1]
     */

    Solution cSolution;
    TreeNode *pRoot;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: root = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            if (testData[i].nums[j] == imin) {
                cout << (j == 0 ? "" : ",") << "null";
            } else if (testData[i].nums[j] == imax) {
                continue;
            } else {
                cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
            }
        }
        cout << "]\n";
        pRoot = buildBinaryTree(testData[i].nums, 0);

        answer = cSolution.postorderTraversal(pRoot);
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
