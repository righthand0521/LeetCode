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
   public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        TreeNode* pRetVal = nullptr;

        unordered_map<int, TreeNode*> treeHashTable;
        unordered_map<int, int> childHashTable;
        for (auto& iter : descriptions) {
            int parent = iter[0];
            int child = iter[1];
            int isLeft = iter[2];

            if (treeHashTable.count(parent) == 0) {
                treeHashTable[parent] = new TreeNode(parent);
            }
            if (treeHashTable.count(child) == 0) {
                treeHashTable[child] = new TreeNode(child);
            }

            if (isLeft == 1) {
                treeHashTable[parent]->left = treeHashTable[child];
            } else {
                treeHashTable[parent]->right = treeHashTable[child];
            }

            ++childHashTable[child];
        }

        for (auto& [key, value] : treeHashTable) {
            if (childHashTable.count(key) == 0) {
                pRetVal = value;
                break;
            }
        }

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> descriptions;
    };
    vector<subject> testData{{{{20, 15, 1}, {20, 17, 0}, {50, 20, 1}, {50, 80, 0}, {80, 19, 1}}},
                             {{{1, 2, 1}, {2, 3, 0}, {3, 4, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: descriptions = [[20,15,1],[20,17,0],[50,20,1],[50,80,0],[80,19,1]]
     *  Output: [50,20,80,15,17,19]
     *
     *  Input: descriptions = [[1,2,1],[2,3,0],[3,4,1]]
     *  Output: [1,2,null,null,3,4]
     */

    Solution cSolution;
    TreeNode* pAnswer = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: descriptions = [";
        for (long unsigned int j = 0; j < testData[i].descriptions.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].descriptions[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].descriptions[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        pAnswer = cSolution.createBinaryTree(testData[i].descriptions);
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
