#include <algorithm>
#include <iostream>
#include <queue>
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
    Node* connect(Node* root) {
        Node* pRetVal = nullptr;

        if (root == nullptr) {
            return pRetVal;
        }

        queue<Node*> levelQueue;
        levelQueue.push(root);
        while (levelQueue.empty() == false) {
            Node* pLast = nullptr;
            int levelQueueSize = levelQueue.size();
            for (int i = 1; i <= levelQueueSize; ++i) {
                Node* node = levelQueue.front();
                levelQueue.pop();
                if (node->left) {
                    levelQueue.push(node->left);
                }
                if (node->right) {
                    levelQueue.push(node->right);
                }
                if (i != 1) {
                    pLast->next = node;
                }
                pLast = node;
            }
        }
        pRetVal = root;

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> root;
    };
    vector<subject> testData{{{1, 2, 3, 4, 5, imin, 7}}, {{}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [1,2,3,4,5,null,7]
     *  Output: [1,#,2,3,#,4,5,7,#]
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
