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
class BSTIterator {
   private:
    vector<int> returnValue;
    int index;

    void inorder(TreeNode* root, vector<int>& returnValue) {
        if (root == nullptr) {
            return;
        }
        inorder(root->left, returnValue);
        returnValue.emplace_back(root->val);
        inorder(root->right, returnValue);
    }
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> retVal;

        inorder(root, retVal);

        return retVal;
    }

   public:
    BSTIterator(TreeNode* root) {
        index = 0;
        returnValue = inorderTraversal(root);
    }
    int next() {
        int retVal = returnValue[index];
        index++;

        return retVal;
    }
    bool hasNext() {
        bool retVal = false;

        int returnValueSize = returnValue.size();
        if (index < returnValueSize) {
            retVal = true;
        }

        return retVal;
    }
};
/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<string> methods;
        vector<vector<int>> val;
    };
    vector<subject> testData{
        {{"BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext", "next", "hasNext"},
         {{7, 3, 15, imin, imin, 9, 20}, {}, {}, {}, {}, {}, {}, {}, {}, {}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input
     *  ["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext", "next", "hasNext"]
     *  [[[7, 3, 15, null, null, 9, 20]], [], [], [], [], [], [], [], [], []]
     *  Output
     *  [null, 3, 7, true, 9, true, 15, true, 20, false]
     */

    TreeNode* pRoot;
    int retIntValue;
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
            if (testData[i].methods[j].compare("BSTIterator") == 0) {
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
        BSTIterator cBSTIterator(pRoot);
        cout << "Output\n";
        cout << "[";
        for (long unsigned int j = 0; j < testData[i].methods.size(); ++j) {
            if (testData[i].methods[j].compare("BSTIterator") == 0) {
                cout << (j == 0 ? "" : ", ") << "null";
            } else if (testData[i].methods[j].compare("next") == 0) {
                retIntValue = cBSTIterator.next();
                cout << (j == 0 ? "" : ", ") << retIntValue;
            } else if (testData[i].methods[j].compare("hasNext") == 0) {
                retBoolValue = cBSTIterator.hasNext();
                cout << (j == 0 ? "" : ", ") << (retBoolValue == true ? "true" : "false");
            }
        }
        cout << "]\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
