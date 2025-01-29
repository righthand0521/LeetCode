#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    int cycleStart = -1;

    void dfs(int src, vector<bool>& visited, vector<int> adjList[], vector<int>& parent) {
        visited[src] = true;
        for (int adj : adjList[src]) {
            if (visited[adj] == false) {
                parent[adj] = src;
                dfs(adj, visited, adjList, parent);
            } else if ((adj != parent[src]) && (cycleStart == -1)) {
                // If the node is visited and the parent is different then the node is part of the cycle.
                cycleStart = adj;
                parent[adj] = src;
            }
        }
    }

   public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        vector<int> retVal;

        cycleStart = -1;

        int edgesSize = edges.size();

        vector<int> adjList[edgesSize];
        for (auto edge : edges) {
            adjList[edge[0] - 1].push_back(edge[1] - 1);
            adjList[edge[1] - 1].push_back(edge[0] - 1);
        }

        vector<bool> visited(edgesSize, false);
        vector<int> parent(edgesSize, -1);
        dfs(0, visited, adjList, parent);  // Peform the DFS and store a node in the cycle as cycleStart.

        // Start from the cycleStart node and backtrack to get all the nodes in the cycle. Mark them all in the map.
        unordered_map<int, int> cycleNodes;
        int node = cycleStart;
        do {
            cycleNodes[node] = 1;
            node = parent[node];
        } while (node != cycleStart);

        // If both nodes of the edge were marked as cycle nodes then this edge can be removed.
        for (int i = edgesSize - 1; i >= 0; i--) {
            if ((cycleNodes[edges[i][0] - 1]) && (cycleNodes[edges[i][1] - 1])) {
                retVal = edges[i];
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> edges;
    };
    vector<subject> testData{{{{1, 2}, {1, 3}, {2, 3}}}, {{{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: edges = [[1,2],[1,3],[2,3]]
     *  Output: [2,3]
     *
     *  Input: edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]
     *  Output: [1,4]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: edges = [";
        for (long unsigned int j = 0; j < testData[i].edges.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].edges[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].edges[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.findRedundantConnection(testData[i].edges);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
