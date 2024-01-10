#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

#include "list.h"
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
    TreeNode* buildBSTbyPreorder(vector<int>& nums, int left, int right) {
        TreeNode* pRetVal = nullptr;

        if (left > right) {
            return pRetVal;
        }

        int middle = (left + right + 1) / 2;
        pRetVal = new TreeNode(nums[middle]);
        pRetVal->left = buildBSTbyPreorder(nums, left, middle - 1);
        pRetVal->right = buildBSTbyPreorder(nums, middle + 1, right);

        return pRetVal;
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        TreeNode* pRetVal = nullptr;

        pRetVal = buildBSTbyPreorder(nums, 0, nums.size() - 1);

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{-10, -3, 0, 5, 9}}, {{1, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [-10,-3,0,5,9]
     *  Output: [0,-3,9,-10,null,5]
     *
     *  Input: nums = [1,3]
     *  Output: [3,1]
     */

    Solution cSolution;
    TreeNode* pAnswer = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        pAnswer = cSolution.sortedArrayToBST(testData[i].nums);
        int height = getTreeHeight(pAnswer);
        cout << "Output: [";
        showTreeOutput(pAnswer, height);
        cout << "]\n";

        cout << "\n";

        freeTreeNode(pAnswer);
        pAnswer = nullptr;
    }

    return EXIT_SUCCESS;
}
