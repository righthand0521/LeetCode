#include <algorithm>
#include <iostream>
#include <unordered_map>
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
    string serialize(TreeNode* node, unordered_map<string, vector<TreeNode*>>& map) {
        if (node == nullptr) {
            return "";
        }

        string s = "(" + serialize(node->left, map) + to_string(node->val) + serialize(node->right, map) + ")";
        map[s].push_back(node);

        return s;
    }

   public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        vector<TreeNode*> retVal;

        // https://leetcode.com/problems/find-duplicate-subtrees/solutions/106055/c-java-clean-code-with-explanation/
        unordered_map<string, vector<TreeNode*>> map;
        serialize(root, map);
        for (auto it = map.begin(); it != map.end(); it++) {
            if (it->second.size() > 1) {
                retVal.push_back(it->second[0]);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{
        {{1, 2, 3, 4, numeric_limits<int>::min(), 2, 4, numeric_limits<int>::min(), numeric_limits<int>::min(), 4}},
        {{2, 1, 1}},
        {{2, 2, 2, 3, numeric_limits<int>::min(), 3, numeric_limits<int>::min()}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [1,2,3,4,null,2,4,null,null,4]
     *  Output: [[2,4],[4]]
     *
     *  Input: root = [2,1,1]
     *  Output: [[1]]
     *
     *  Input: root = [2,2,2,3,null,3,null]
     *  Output: [[2,3],[3]]
     */

    Solution cSolution;
    TreeNode* pRoot;
    vector<TreeNode*> answer;
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
#if 0  // fix
        int height = getTreeHeight(pRoot);
        showTreeOutput(pRoot, height);
        cout << "\n";
#endif

        answer = cSolution.findDuplicateSubtrees(pRoot);
        cout << "Output: [";
#if 1  // fix
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            int height = getTreeHeight(answer[j]);
            showTreeOutput(answer[j], height);
            cout << "]";
        }
#endif
        cout << "]\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
