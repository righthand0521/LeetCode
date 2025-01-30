#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

class UnionFind {
   public:
    int n;
    vector<int> parent;
    vector<int> depth;

    UnionFind(int _n) : n(_n), parent(_n, -1), depth(_n, 0) {}
    int find(int node) {
        int retVal = 0;

        while (parent[node] != -1) {
            node = parent[node];
        }
        retVal = node;

        return retVal;
    }
    void Union(int node1, int node2) {
        node1 = find(node1);
        node2 = find(node2);

        // If both nodes already belong to the same set, no action needed
        if (node1 == node2) {
            return;
        }

        // Union by rank (depth) to keep the tree balanced
        if (depth[node1] < depth[node2]) {
            swap(node1, node2);
        }
        parent[node2] = node1;

        // If the depths are equal, increment the depth of the new root
        if (depth[node1] == depth[node2]) {
            depth[node1]++;
        }
    }
};
class Solution {
   private:
    int getNumberOfGroups(vector<vector<int>> &adjacencyList, int srcNode, int n) {
        int retVal = 0;

        // Perform BFS to calculate the number of layers (groups)
        queue<int> bfsQueue;
        bfsQueue.push(srcNode);
        vector<int> layerSeen(n, -1);
        layerSeen[srcNode] = 0;
        while (bfsQueue.empty() == false) {
            int bfsQueueSize = bfsQueue.size();
            for (int i = 0; i < bfsQueueSize; i++) {
                int currentNode = bfsQueue.front();
                bfsQueue.pop();
                for (int neighbor : adjacencyList[currentNode]) {
                    // If neighbor hasn't been visited, assign it to the next layer
                    if (layerSeen[neighbor] == -1) {
                        layerSeen[neighbor] = retVal + 1;
                        bfsQueue.push(neighbor);
                        continue;
                    }

                    // If the neighbor is already in the same layer, return -1 (invalid partition)
                    if (layerSeen[neighbor] == retVal) {
                        retVal = -1;
                        return retVal;
                    }
                }
            }
            retVal++;
        }

        return retVal;
    }

   public:
    int magnificentSets(int n, vector<vector<int>> &edges) {
        int retVal = 0;

        // Build the adjacency list and apply Union-Find for each edge
        vector<vector<int>> adjacencyList(n);
        UnionFind uf(n);
        for (auto edge : edges) {
            adjacencyList[edge[0] - 1].push_back(edge[1] - 1);
            adjacencyList[edge[1] - 1].push_back(edge[0] - 1);
            uf.Union(edge[0] - 1, edge[1] - 1);
        }

        // For each node, calculate the maximum number of groups for its component
        unordered_map<int, int> numOfGroupsForComponent;
        for (int node = 0; node < n; node++) {
            int numberOfGroups = getNumberOfGroups(adjacencyList, node, n);
            if (numberOfGroups == -1) {
                retVal = -1;  // If invalid split, return -1
                return retVal;
            }

            int rootNode = uf.find(node);
            numOfGroupsForComponent[rootNode] = max(numOfGroupsForComponent[rootNode], numberOfGroups);
        }

        // Calculate the total number of groups across all components
        for (auto [rootNode, numberOfGroups] : numOfGroupsForComponent) {
            retVal += numberOfGroups;
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        int n;
        vector<vector<int>> edges;
    };
    vector<subject> testData{{6, {{1, 2}, {1, 4}, {1, 5}, {2, 6}, {2, 3}, {4, 6}}}, {3, {{1, 2}, {2, 3}, {3, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 6, edges = [[1,2],[1,4],[1,5],[2,6],[2,3],[4,6]]
     *  Output: 4
     *
     *  Input: n = 3, edges = [[1,2],[2,3],[3,1]]
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", edges = [";
        for (long unsigned int j = 0; j < testData[i].edges.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].edges[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].edges[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.magnificentSets(testData[i].n, testData[i].edges);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
