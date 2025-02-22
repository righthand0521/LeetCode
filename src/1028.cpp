#include <algorithm>
#include <iostream>
#include <stack>
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
    TreeNode* recoverFromPreorder(string traversal) {
        TreeNode* pRetVal = nullptr;

        int traversalSize = traversal.size();
        stack<TreeNode*> stack;
        int index = 0;
        while (index < traversalSize) {
            // Count the number of dashes
            int depth = 0;
            while ((index < traversalSize) && (traversal[index] == '-')) {
                depth++;
                index++;
            }

            // Extract the node value
            int value = 0;
            while ((index < traversalSize) && (isdigit(traversal[index]))) {
                value = value * 10 + (traversal[index] - '0');
                index++;
            }

            // Create the current node
            TreeNode* node = new TreeNode(value);

            // Adjust the stack to the correct depth
            int stackSize = stack.size();
            while (stackSize > depth) {
                stack.pop();
                stackSize = stack.size();
            }

            // Attach the node to the parent
            if (stack.empty() == false) {
                if (stack.top()->left == nullptr) {
                    stack.top()->left = node;
                } else {
                    stack.top()->right = node;
                }
            }

            // Push the current node onto the stack
            stack.push(node);
        }

        // The root is the first node in the stack
        while (stack.size() > 1) {
            stack.pop();
        }
        pRetVal = stack.top();

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string traversal;
    };
    vector<subject> testData{{"1-2--3--4-5--6--7"}, {"1-2--3---4-5--6---7"}, {"1-401--349---90--88"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: traversal = "1-2--3--4-5--6--7"
     *  Output: [1,2,5,3,4,6,7]
     *
     *  Input: traversal = "1-2--3---4-5--6---7"
     *  Output: [1,2,5,3,null,6,null,4,null,7]
     *
     *  Input: traversal = "1-401--349---90--88"
     *  Output: [1,401,null,349,88,90]
     */

    Solution cSolution;
    TreeNode* pAnswer = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: traversal = \"" << testData[i].traversal << "\"\n";

        pAnswer = cSolution.recoverFromPreorder(testData[i].traversal);
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
