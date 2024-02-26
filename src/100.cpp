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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        bool retVal = false;

        if ((p == nullptr) && (q == nullptr)) {
            retVal = true;
            return retVal;
        } else if ((p == nullptr) && (q != nullptr)) {
            return retVal;
        } else if ((p != nullptr) && (q == nullptr)) {
            return retVal;
        }

        if (isSameTree(p->left, q->left) == false) {
            return retVal;
        }
        if (p->val != q->val) {
            return retVal;
        }
        if (isSameTree(p->right, q->right) == false) {
            return retVal;
        }
        retVal = true;

        return retVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> p;
        vector<int> q;
    };
    vector<subject> testData{{{1, 2, 3}, {1, 2, 3}}, {{1, 2}, {1, imin, 2}}, {{1, 2, 1}, {1, 1, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: p = [1,2,3], q = [1,2,3]
     *  Output: true
     *
     *  Input: p = [1,2], q = [1,null,2]
     *  Output: false
     *
     *  Input: p = [1,2,1], q = [1,1,2]
     *  Output: false
     */

    Solution cSolution;
    TreeNode* pRoot;
    TreeNode* qRoot;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: p = [";
        for (long unsigned int j = 0; j < testData[i].p.size(); ++j) {
            if (testData[i].p[j] == imin) {
                cout << (j == 0 ? "" : ",") << "null";
            } else if (testData[i].p[j] == imax) {
                continue;
            } else {
                cout << ((j == 0) ? "" : ",") << testData[i].p[j];
            }
        }
        cout << "], q = [";
        for (long unsigned int j = 0; j < testData[i].q.size(); ++j) {
            if (testData[i].q[j] == imin) {
                cout << (j == 0 ? "" : ",") << "null";
            } else if (testData[i].q[j] == imax) {
                continue;
            } else {
                cout << ((j == 0) ? "" : ",") << testData[i].q[j];
            }
        }
        cout << "]\n";
        pRoot = buildBinaryTree(testData[i].p, 0);
        qRoot = buildBinaryTree(testData[i].q, 0);

        answer = cSolution.isSameTree(pRoot, qRoot);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
        freeTreeNode(qRoot);
    }

    return EXIT_SUCCESS;
}
