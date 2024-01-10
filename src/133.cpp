#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

// Definition for a Node.
class Node {
   public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution {
#define DFS (1)
#define BFS (1)
   public:
    Solution() {
#if (DFS)
        cout << "DFS\n";
#elif (BFS)
        cout << "BFS\n";
#endif
    }

    unordered_map<Node*, Node*> visited;

    Node* cloneGraph(Node* node) {
        Node* retVal = node;

        if (node == nullptr) {
            return retVal;
        }

#if (DFS)
        if (visited.find(node) != visited.end()) {
            retVal = visited[node];
            return retVal;
        }

        Node* cloneNode = new Node(node->val);
        visited[node] = cloneNode;
        for (auto& neighbor : node->neighbors) {
            cloneNode->neighbors.emplace_back(cloneGraph(neighbor));
        }

        retVal = cloneNode;
#elif (BFS)
        queue<Node*> bfsQueue;
        bfsQueue.push(node);

        visited[node] = new Node(node->val);

        while (bfsQueue.empty() == false) {
            auto n = bfsQueue.front();
            bfsQueue.pop();

            for (auto& neighbor : n->neighbors) {
                if (visited.find(neighbor) == visited.end()) {
                    visited[neighbor] = new Node(neighbor->val);
                    bfsQueue.push(neighbor);
                }
                visited[n]->neighbors.emplace_back(visited[neighbor]);
            }
        }

        retVal = visited[node];
#endif

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> adjList;
    };
    vector<subject> testData{{{{2, 4}, {1, 3}, {2, 4}, {1, 3}}}, {{{}}}, {{{}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: adjList = [[2, 4], [1, 3], [2, 4], [1, 3]]
     *  Output: [[2, 4], [1, 3], [2, 4], [1, 3]]
     *
     *  Input: adjList = [[]]
     *  Output: [[]]
     *
     *  Input: adjList = []
     *  Output: []
     */

    Solution cSolution;
    // Node* answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: adjList = [";
        for (long unsigned int j = 0; j < testData[i].adjList.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].adjList[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].adjList[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        // answer = cSolution.cloneGraph(testData[i].adjList);
        // cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
