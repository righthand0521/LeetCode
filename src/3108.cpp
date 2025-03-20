#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   private:
    int dfs(int node, vector<vector<pair<int, int>>>& adjList, vector<bool>& visited, vector<int>& components,
            int componentId) {
        // Initialize the cost to the number that has only 1s in its binary representation
        int retVal = numeric_limits<int>::max();

        components[node] = componentId;  // Mark the node as part of the current component
        visited[node] = true;
        for (auto& [neighbor, weight] : adjList[node]) {
            retVal &= weight;  // Update the cost by performing a bitwise AND of the edge weights
            if (visited[neighbor] == true) {
                continue;
            }
            // Recursively calculate the cost of the rest of the component and accumulate it into retVal
            retVal &= dfs(neighbor, adjList, visited, components, componentId);
        }

        return retVal;
    }

   public:
    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        vector<int> retVal;

        // Create the adjacency list of the graph
        vector<vector<pair<int, int>>> adjList(n);
        for (auto& edge : edges) {
            adjList[edge[0]].push_back({edge[1], edge[2]});
            adjList[edge[1]].push_back({edge[0], edge[2]});
        }

        vector<bool> visited(n, false);

        // Array to store the component ID of each node
        vector<int> components(n);
        vector<int> componentCost;
        int componentId = 0;
        // Perform DFS for each unvisited node to identify components and calculate their costs
        for (int node = 0; node < n; node++) {
            // If the node hasn't been visited, it's a new component
            if (visited[node] == true) {
                continue;
            }
            // Get the component cost and mark all nodes in the component
            componentCost.push_back(dfs(node, adjList, visited, components, componentId));
            // Increment the component ID for the next component
            componentId++;
        }

        for (auto& q : query) {
            int start = q[0];
            int end = q[1];
            // If they are in the same component, return the precomputed cost for the component
            if (components[start] == components[end]) {
                retVal.push_back(componentCost[components[start]]);
            } else {  // If they are in different components, return -1
                retVal.push_back(-1);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> edges;
        vector<vector<int>> query;
    };
    vector<subject> testData{{5, {{0, 1, 7}, {1, 3, 7}, {1, 2, 1}}, {{0, 3}, {3, 4}}},
                             {3, {{0, 2, 7}, {0, 1, 15}, {1, 2, 6}, {1, 2, 1}}, {{1, 2}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 5, edges = [[0,1,7],[1,3,7],[1,2,1]], query = [[0,3],[3,4]]
     *  Output: [1,-1]
     *
     *  Input: n = 3, edges = [[0,2,7],[0,1,15],[1,2,6],[1,2,1]], query = [[1,2]]
     *  Output: [0]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", edges = [";
        for (long unsigned int j = 0; j < testData[i].edges.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].edges[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].edges[j][k];
            }
            cout << "]";
        }
        cout << "], query = [";
        for (long unsigned int j = 0; j < testData[i].query.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].query[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].query[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.minimumCost(testData[i].n, testData[i].edges, testData[i].query);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
