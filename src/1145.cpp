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
    int nodeCount(TreeNode* root, int* leftCount, int* rightCount, int nodeValue) {
        if (root == nullptr) {
            return 0;
        }

        int left = nodeCount(root->left, leftCount, rightCount, nodeValue);
        int right = nodeCount(root->right, leftCount, rightCount, nodeValue);
        if (root->val == nodeValue) {
            (*leftCount) = left;
            (*rightCount) = right;
        }

        return (left + right + 1);
    }
    bool btreeGameWinningMove(TreeNode* root, int n, int x) {
        bool retVal = false;

        int left = 0;
        int right = 0;
        nodeCount(root, &left, &right, x);
        if (left > (n / 2)) {
            retVal = true;
        } else if (right > (n / 2)) {
            retVal = true;
        } else if ((n - 1 - left - right) > (n / 2)) {
            retVal = true;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int n;
        int x;
    };
    vector<subject> testData{{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, 11, 3}, {{1, 2, 3}, 3, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [1,2,3,4,5,6,7,8,9,10,11], n = 11, x = 3
     *  Output: true
     *
     *  Input: root = [1,2,3], n = 3, x = 1
     *  Output: false
     */

    Solution cSolution;
    TreeNode* pRoot;
    bool answer = false;
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
        cout << "], n = " << testData[i].n << ", x = " << testData[i].x << "\n";

        pRoot = buildBinaryTree(testData[i].nums, 0);
        answer = cSolution.btreeGameWinningMove(pRoot, testData[i].n, testData[i].x);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
