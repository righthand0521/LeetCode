#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#include "treeNode.h"

/**
 * Definition for a Node.
 * class Node {
 *  public:
 *      int val;
 *      Node* left;
 *      Node* right;
 *      Node* next;
 *      Node() : val(0), left(NULL), right(NULL), next(NULL) {}
 *      Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}
 *      Node(int _val, Node* _left, Node* _right, Node* _next): val(_val), left(_left), right(_right), next(_next) {}
 * };
 * */
class Solution {
   public:
    void dfs(Node* pRoot) {
        if (pRoot == nullptr) {
            return;
        }

        /* Example
         *                                          (01)
         *
         *                    (02) ------------------01-----------------> (03)
         *
         *         (04) -------04------> (05) -------02------> (06) -------08------> (07)
         *
         *    (08) -06-> (09) -05-> (10) -07-> (11) -03-> (12) -10-> (13) -09-> (14) -11-> (15)
         */
        Node* pLeft = pRoot->left;
        Node* pRight = pRoot->right;
        while (pLeft != NULL) {
            pLeft->next = pRight;
            pLeft = pLeft->right;
            pRight = pRight->left;
        }
        dfs(pRoot->left);
        dfs(pRoot->right);
    }
    Node* connect(Node* root) {
        Node* pRetVal = root;

        dfs(pRetVal);

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> root;
    };
    vector<subject> testData{{{1, 2, 3, 4, 5, 6, 7}}, {{}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [1,2,3,4,5,6,7]
     *  Output: [1,#,2,3,#,4,5,6,7,#]
     *
     *  Input: root = []
     *  Output: []
     */

    Solution cSolution;
    Node* pRoot = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: root = [";
        for (long unsigned int j = 0; j < testData[i].root.size(); ++j) {
            if (testData[i].root[j] == imin) {
                cout << (j == 0 ? "" : ",") << "null";
            } else if (testData[i].root[j] == imax) {
                continue;
            } else {
                cout << ((j == 0) ? "" : ",") << testData[i].root[j];
            }
        }
        cout << "]\n";
        pRoot = buildNodeTree(testData[i].root, 0);

        pRoot = cSolution.connect(pRoot);
        cout << "Output: [";
        displayNodeTreeByNext(pRoot);
        cout << "]\n";

        cout << "\n";

        freeNodeTree(pRoot);
        pRoot = nullptr;
    }

    return EXIT_SUCCESS;
}
