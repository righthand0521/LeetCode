#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// Definition for a QuadTree node.
class Node {
   public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};

/*
// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};
*/
class Solution {
   public:
    void printNode(Node* pRoot, string fmt) {
        if (pRoot == nullptr) {
            return;
        }
        cout << fmt << "[" << pRoot->isLeaf << "," << pRoot->val << "]";
        printNode(pRoot->topLeft, ",");
        printNode(pRoot->topRight, ",");
        printNode(pRoot->bottomLeft, ",");
        printNode(pRoot->bottomRight, ",");
    }
    void freeNode(Node* pRoot) {
        if (pRoot == nullptr) {
            return;
        }
        freeNode(pRoot->topLeft);
        freeNode(pRoot->topRight);
        freeNode(pRoot->bottomLeft);
        freeNode(pRoot->bottomRight);
        delete pRoot;
        pRoot = nullptr;
    }

    // https://leetcode.cn/problems/construct-quad-tree/solutions/1457070/c-di-gui-qie-fen-by-lchaok-vus6/
    bool checkLeaf(int top, int left, int bottom, int right, vector<vector<int>>& grid) {
        int retVal = false;

        int same = grid[top][left];
        for (int i = top; i <= bottom; ++i) {
            for (int j = left; j <= right; ++j) {
                if (grid[i][j] != same) {
                    return retVal;
                }
            }
        }
        retVal = true;

        return retVal;
    }
    Node* recursion(int top, int left, int bottom, int right, vector<vector<int>>& grid) {
        Node* pRetVal = new Node();

        if (checkLeaf(top, left, bottom, right, grid)) {
            pRetVal->val = grid[top][left];
            pRetVal->isLeaf = true;
            return pRetVal;
        }
        pRetVal->isLeaf = false;
        pRetVal->val = 1;
        pRetVal->topLeft = recursion(top, left, top + (bottom - top) / 2, left + (right - left) / 2, grid);
        pRetVal->topRight = recursion(top, right - (right - left) / 2, top + (bottom - top) / 2, right, grid);
        pRetVal->bottomLeft = recursion(bottom - (bottom - top) / 2, left, bottom, left + (right - left) / 2, grid);
        pRetVal->bottomRight = recursion(bottom - (bottom - top) / 2, right - (right - left) / 2, bottom, right, grid);

        return pRetVal;
    }
    Node* construct(vector<vector<int>>& grid) {
        Node* pRetVal = NULL;

        pRetVal = recursion(0, 0, grid.size() - 1, grid.size() - 1, grid);

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
    };
    vector<subject> testData{{{{0, 1}, {1, 0}}},
                             {{{1, 1, 1, 1, 0, 0, 0, 0},
                               {1, 1, 1, 1, 0, 0, 0, 0},
                               {1, 1, 1, 1, 1, 1, 1, 1},
                               {1, 1, 1, 1, 1, 1, 1, 1},
                               {1, 1, 1, 1, 0, 0, 0, 0},
                               {1, 1, 1, 1, 0, 0, 0, 0},
                               {1, 1, 1, 1, 0, 0, 0, 0},
                               {1, 1, 1, 1, 0, 0, 0, 0}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[0,1],[1,0]]
     *  Output: [[0,1],[1,0],[1,1],[1,1],[1,0]]
     *
     *  Input: grid = [[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,1,1,1,1],[1,1,1,1,1,1,1,1],[1,1,1,1,0,0,0,0],
     *                  [1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0]]
     *  Output: [[0,1],[1,1],[0,1],[1,1],[1,0],null,null,null,null,[1,0],[1,0],[1,1],[1,1]]
     */

    Solution cSolution;
    Node* pAnswer = nullptr;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: grid = [";
        for (long unsigned int j = 0; j < testData[i].grid.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].grid[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].grid[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        pAnswer = cSolution.construct(testData[i].grid);
        cout << "Output: [";
        cSolution.printNode(pAnswer, "");
        cout << "]\n";

        cout << "\n";

        cSolution.freeNode(pAnswer);
        pAnswer = nullptr;
    }

    return EXIT_SUCCESS;
}
