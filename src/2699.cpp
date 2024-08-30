#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<long long> fromDestination;
    int target;

    vector<long long> dijkstra(int op, int source, vector<vector<int>>& edges, const vector<vector<int>>& adjacency) {
        vector<long long> retVal;

        int n = adjacency.size();
        vector<long long> distance(n, numeric_limits<int>::max() / 2);
        distance[source] = 0;
        vector<int> visited(n);

        for (int round = 0; round < n - 1; ++round) {
            int u = -1;
            for (int i = 0; i < n; ++i) {
                if (visited[i] == true) {
                    continue;
                }

                if ((u == -1) || (distance[i] < distance[u])) {
                    u = i;
                }
            }
            visited[u] = true;

            for (int v = 0; v < n; ++v) {
                if (visited[v] == true) {
                    continue;
                } else if (adjacency[u][v] == -1) {
                    continue;
                }

                if (edges[adjacency[u][v]][2] != -1) {
                    distance[v] = min(distance[v], distance[u] + edges[adjacency[u][v]][2]);
                    continue;
                }

                if (op == 0) {
                    distance[v] = min(distance[v], distance[u] + 1);
                } else {
                    int modify = target - distance[u] - fromDestination[v];
                    if (modify > 0) {
                        distance[v] = min(distance[v], distance[u] + modify);
                        edges[adjacency[u][v]][2] = modify;
                    } else {
                        edges[adjacency[u][v]][2] = target;
                    }
                }
            }
        }
        retVal = distance;

        return retVal;
    }

   public:
    vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>>& edges, int source, int destination, int target) {
        vector<vector<int>> retVal;

        this->target = target;

        vector<vector<int>> adjacency(n, vector<int>(n, -1));
        int edgesSize = edges.size();
        for (int i = 0; i < edgesSize; ++i) {
            int u = edges[i][0];
            int v = edges[i][1];
            adjacency[u][v] = i;
            adjacency[v][u] = i;
        }

        fromDestination = dijkstra(0, destination, edges, adjacency);
        if (fromDestination[source] > target) {
            return retVal;
        }

        vector<long long> fromSource = dijkstra(1, source, edges, adjacency);
        if (fromSource[destination] != target) {
            return retVal;
        }

        retVal = edges;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> edges;
        int source;
        int destination;
        int target;
    };
    vector<subject> testData{{5, {{4, 1, -1}, {2, 0, -1}, {0, 3, -1}, {4, 3, -1}}, 0, 1, 5},
                             {3, {{0, 1, -1}, {0, 2, 5}}, 0, 2, 6},
                             {4, {{1, 0, 4}, {1, 2, 3}, {2, 3, 5}, {0, 3, -1}}, 0, 2, 6}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 5, edges = [[4,1,-1],[2,0,-1],[0,3,-1],[4,3,-1]], source = 0, destination = 1, target = 5
     *  Output: [[4,1,1],[2,0,1],[0,3,3],[4,3,1]]
     *
     *  Input: n = 3, edges = [[0,1,-1],[0,2,5]], source = 0, destination = 2, target = 6
     *  Output: []
     *
     *  Input: n = 4, edges = [[1,0,4],[1,2,3],[2,3,5],[0,3,-1]], source = 0, destination = 2, target = 6
     *  Output: [[1,0,4],[1,2,3],[2,3,5],[0,3,1]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", edges = [";
        for (long unsigned int j = 0; j < testData[i].edges.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].edges[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].edges[j][k];
            }
            cout << "]";
        }
        cout << "]";
        cout << ", source = " << testData[i].source;
        cout << ",destination = " << testData[i].destination;
        cout << ", target = " << testData[i].target << "\n";

        answer = cSolution.modifiedGraphEdges(testData[i].n, testData[i].edges, testData[i].source,
                                              testData[i].destination, testData[i].target);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < answer[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << answer[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
