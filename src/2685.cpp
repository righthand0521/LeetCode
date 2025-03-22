#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        int retVal = 0;

        // Create adjacency list representation of the graph
        vector<vector<int>> adjacency(n);
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1];
            adjacency[u].push_back(v);
            adjacency[v].push_back(u);
        }

        vector<bool> visited(n, false);

        for (int vertex = 0; vertex < n; vertex++) {
            if (visited[vertex] == true) {
                continue;
            }
            visited[vertex] = true;

            // BFS to find all vertices in the current component
            vector<int> component;
            queue<int> bfsQueue;
            bfsQueue.push(vertex);
            while (bfsQueue.empty() == false) {
                int current = bfsQueue.front();
                bfsQueue.pop();
                component.push_back(current);

                // Process neighbors
                for (int neighbor : adjacency[current]) {
                    if (visited[neighbor] == true) {
                        continue;
                    }
                    bfsQueue.push(neighbor);
                    visited[neighbor] = true;
                }
            }

            // Check if component is complete (all vertices have the right number of edges)
            bool isComplete = true;
            for (int node : component) {
                int componentSize = component.size();
                int adjacencyNodeSize = adjacency[node].size();
                if (adjacencyNodeSize != componentSize - 1) {
                    isComplete = false;
                    break;
                }
            }
            if (isComplete) {
                retVal++;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> edges;
    };
    vector<subject> testData{{6, {{0, 1}, {0, 2}, {1, 2}, {3, 4}}}, {6, {{0, 1}, {0, 2}, {1, 2}, {3, 4}, {3, 5}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 6, edges = [[0,1],[0,2],[1,2],[3,4]]
     *  Output: 3
     *
     *  Input: n = 6, edges = [[0,1],[0,2],[1,2],[3,4],[3,5]]
     *  Output: 1
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", edges = [";
        for (long unsigned int j = 0; j < testData[i].edges.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].edges[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].edges[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.countCompleteComponents(testData[i].n, testData[i].edges);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
