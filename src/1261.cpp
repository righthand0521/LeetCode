#include <algorithm>
#include <iostream>
#include <unordered_set>
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
class FindElements {
   private:
    unordered_set<int> seen;
    void dfs(TreeNode* currentNode, int currentValue) {
        if (currentNode == nullptr) {
            return;
        }

        // visit current node by adding its value to seen
        seen.insert(currentValue);
        dfs(currentNode->left, currentValue * 2 + 1);
        dfs(currentNode->right, currentValue * 2 + 2);
    }

   public:
    FindElements(TreeNode* root) {
        //
        dfs(root, 0);
    }
    bool find(int target) {
        bool retVal = (seen.count(target) > 0);

        return retVal;
    }
};
/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<string> methods;
        vector<vector<int>> val;
    };
    vector<subject> testData{
        {{"FindElements", "find", "find"}, {{-1, imin, -1}, {1}, {2}}},
        {{"FindElements", "find", "find", "find"}, {{-1, -1, -1, -1, -1}, {1}, {3}, {5}}},
        {{"FindElements", "find", "find", "find", "find"}, {{-1, imin, -1, -1, imin, -1}, {2}, {3}, {4}, {5}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["FindElements","find","find"]
     *  [[[-1,null,-1]],[1],[2]]
     *  Output
     *  [null,false,true]
     *
     *  Input
     *  ["FindElements","find","find","find"]
     *  [[[-1,-1,-1,-1,-1]],[1],[3],[5]]
     *  Output
     *  [null,true,true,false]
     *
     *  Input
     *  ["FindElements","find","find","find","find"]
     *  [[[-1,null,-1,-1,null,-1]],[2],[3],[4],[5]]
     *  Output
     *  [null,true,false,false,true]
     */

    TreeNode* pRoot;
    bool retBoolValue;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            cout << (j == 0 ? "" : ", ") << '"' << testData[i].methods[j] << '"';
        }
        cout << "]\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].val.size(); ++j) {
            cout << (j == 0 ? "" : ", ") << "[";
            if (testData[i].methods[j].compare("FindElements") == 0) {
                cout << "[";
                for (long unsigned int k = 0; k < testData[i].val[j].size(); ++k) {
                    if (testData[i].val[j][k] == imin) {
                        cout << (k == 0 ? "" : ",") << "null";
                    } else if (testData[i].val[j][k] == imax) {
                        continue;
                    } else {
                        cout << ((k == 0) ? "" : ",") << testData[i].val[j][k];
                    }
                }
                cout << "]";
            }
            cout << "]";
        }
        cout << "]\n";

        pRoot = buildBinaryTree(testData[i].val[0], 0);
        FindElements cFindElements(pRoot);
        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            if (testData[i].methods[j].compare("FindElements") == 0) {
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("find") == 0) {
                retBoolValue = cFindElements.find(testData[i].val[j][0]);
                cout << (j == 0 ? "" : ", ") << (retBoolValue == true ? "true" : "false");
            }
        }
        cout << "]\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
