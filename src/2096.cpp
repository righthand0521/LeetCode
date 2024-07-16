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
    bool findPath(TreeNode* node, int target, string& path) {
        bool retVal = false;

        if (node == nullptr) {
            return retVal;
        }

        if (node->val == target) {
            retVal = true;
            return retVal;
        }

        // Try left subtree
        path += "L";
        if (findPath(node->left, target, path)) {
            retVal = true;
            return retVal;
        }

        // Remove last character
        path.pop_back();

        // Try right subtree
        path += "R";
        if (findPath(node->right, target, path)) {
            return true;
        }

        // Remove last character
        path.pop_back();

        return retVal;
    }

   public:
    string getDirections(TreeNode* root, int startValue, int destValue) {
        string retVal = "";

        // Find paths from root to start and destination nodes
        string startPath;
        findPath(root, startValue, startPath);
        int startPathSize = startPath.length();
        string destPath;
        findPath(root, destValue, destPath);
        int destPathSize = destPath.length();

        // Find the length of the common path
        int commonPathLength = 0;
        while ((commonPathLength < startPathSize) && (commonPathLength < destPathSize) &&
               (startPath[commonPathLength] == destPath[commonPathLength])) {
            commonPathLength++;
        }

        // Add "U" for each step to go up from start to common ancestor
        for (int i = 0; i < startPathSize - commonPathLength; i++) {
            retVal += "U";
        }

        // Add directions from common ancestor to destination
        for (int i = commonPathLength; i < destPathSize; i++) {
            retVal += destPath[i];
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> nums;
        int startValue;
        int destValue;
    };
    vector<subject> testData{{{5, 1, 2, 3, imin, 6, 4}, 3, 6}, {{2, 1}, 2, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [5,1,2,3,null,6,4], startValue = 3, destValue = 6
     *  Output: "UURL"
     *
     *  Input: root = [2,1], startValue = 2, destValue = 1
     *  Output: "L"
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
        cout << "], startValue = " << testData[i].startValue << ", destValue = " << testData[i].destValue << "\n";
        pRoot = buildBinaryTree(testData[i].nums, 0);

        answer = cSolution.getDirections(pRoot, testData[i].startValue, testData[i].destValue);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
