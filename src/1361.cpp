#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    bool validateBinaryTreeNodes(int n, vector<int>& leftChild, vector<int>& rightChild) {
        bool retVal = false;

        int root = -1;
        unordered_set<int> children;
        children.insert(leftChild.begin(), leftChild.end());
        children.insert(rightChild.begin(), rightChild.end());
        for (int i = 0; i < n; i++) {
            if (children.find(i) == children.end()) {
                root = i;
                break;
            }
        }
        if (root == -1) {
            return retVal;
        }

        unordered_set<int> visited;
        visited.insert(root);
        queue<int> bfsQueue;
        bfsQueue.push(root);
        while (bfsQueue.empty() == false) {
            int node = bfsQueue.front();
            bfsQueue.pop();

            int allChild[] = {leftChild[node], rightChild[node]};
            for (int child : allChild) {
                if (child == -1) {
                    continue;
                }

                if (visited.find(child) != visited.end()) {
                    return retVal;
                }
                bfsQueue.push(child);
                visited.insert(child);
            }
        }
        int visitedSize = visited.size();
        if (visitedSize == n) {
            retVal = true;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<int> leftChild;
        vector<int> rightChild;
    };
    vector<subject> testData{
        {4, {1, -1, 3, -1}, {2, -1, -1, -1}}, {4, {1, -1, 3, -1}, {2, 3, -1, -1}}, {2, {1, 0}, {-1, -1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 4, leftChild = [1,-1,3,-1], rightChild = [2,-1,-1,-1]
     *  Output: true
     *
     *  Input: n = 4, leftChild = [1,-1,3,-1], rightChild = [2,3,-1,-1]
     *  Output: false
     *
     *  Input: n = 2, leftChild = [1,0], rightChild = [-1,-1]
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: leftChild = [";
        for (long unsigned int j = 0; j < testData[i].leftChild.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].leftChild[j];
        }
        cout << "], rightChild = [";
        for (long unsigned int j = 0; j < testData[i].rightChild.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].rightChild[j];
        }
        cout << "]\n";

        answer = cSolution.validateBinaryTreeNodes(testData[i].n, testData[i].leftChild, testData[i].rightChild);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
