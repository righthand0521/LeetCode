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
    string answer;

   public:
    void dfs(TreeNode* root, string currentStr) {
        if (root == nullptr) {
            return;
        }

        currentStr = char(root->val + 'a') + currentStr;

        if ((root->left == nullptr) && (root->right == nullptr)) {
            if ((answer == "") || (answer > currentStr)) {
                answer = currentStr;
            }
        }

        if (root->left) {
            dfs(root->left, currentStr);
        }

        if (root->right) {
            dfs(root->right, currentStr);
        }
    }
    string smallestFromLeaf(TreeNode* root) {
        string retVal;

        answer = "";
        dfs(root, "");
        retVal = answer;

        return retVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{
        {{0, 1, 2, 3, 4, 3, 4}}, {{25, 1, 3, 1, 3, 0, 2}}, {{2, 2, 1, imin, 1, 0, imin, imax, imax, 0}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [0,1,2,3,4,3,4]
     *  Output: "dba"
     *
     *  Input: root = [25,1,3,1,3,0,2]
     *  Output: "adz"
     *
     *  Input: root = [2,2,1,null,1,0,null,0]
     *  Output: "abc"
     */

    Solution cSolution;
    TreeNode* pRoot;
    string answer;
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

        answer = cSolution.smallestFromLeaf(pRoot);
        cout << "Output: " << answer << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
