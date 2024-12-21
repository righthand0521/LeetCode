#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k) {
        int retVal = 1;

        // Base case: if there are less than 2 nodes, return 1
        if (n < 2) {
            return retVal;
        }

        // Step 1: Build the graph
        unordered_map<int, unordered_set<int>> graph;
        for (const auto& edge : edges) {
            int node1 = edge[0];
            int node2 = edge[1];
            graph[node1].insert(node2);
            graph[node2].insert(node1);
        }

        // Convert values to long long to prevent overflow
        vector<long long> longValues(values.begin(), values.end());

        // Step 2: Initialize the BFS queue with leaf nodes (nodes with only one connection)
        queue<int> bfsQueue;
        for (const auto& [node, neighbors] : graph) {
            if (neighbors.size() == 1) {
                bfsQueue.push(node);
            }
        }

        // Step 3: Process nodes in BFS order
        int componentCount = 0;
        while (bfsQueue.empty() == false) {
            int currentNode = bfsQueue.front();
            bfsQueue.pop();

            // Find the neighbor node
            int neighborNode = -1;
            if (graph[currentNode].empty() == false) {
                neighborNode = *graph[currentNode].begin();
            }

            // Remove the edge between current and neighbor
            if (neighborNode >= 0) {
                graph[neighborNode].erase(currentNode);
                graph[currentNode].erase(neighborNode);
            }

            // Check divisibility of the current node's value
            if (longValues[currentNode] % k == 0) {
                componentCount++;
            } else if (neighborNode >= 0) {
                // Add current node's value to the neighbor
                longValues[neighborNode] += longValues[currentNode];
            }

            // If the neighbor becomes a leaf node, add it to the BFS queue
            int graphNeighborNodeSize = graph[neighborNode].size();
            if ((neighborNode >= 0) && (graphNeighborNodeSize == 1)) {
                bfsQueue.push(neighborNode);
            }
        }

        retVal = componentCount;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> edges;
        vector<int> values;
        int k;
    };
    vector<subject> testData{{5, {{0, 2}, {1, 2}, {1, 3}, {2, 4}}, {1, 8, 1, 4, 4}, 6},
                             {7, {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}}, {3, 0, 6, 1, 5, 2, 1}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 5, edges = [[0,2],[1,2],[1,3],[2,4]], values = [1,8,1,4,4], k = 6
     *  Output: 2
     *
     *  Input: n = 7, edges = [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]], values = [3,0,6,1,5,2,1], k = 3
     *  Output: 3
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", edges = [";
        for (long unsigned int j = 0; j < testData[i].edges.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].edges[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].edges[j][k];
            }
            cout << "]";
        }
        cout << "], values = [";
        for (long unsigned int j = 0; j < testData[i].values.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].values[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.maxKDivisibleComponents(testData[i].n, testData[i].edges, testData[i].values, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
