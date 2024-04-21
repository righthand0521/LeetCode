#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        bool retVal = false;

        vector<vector<int>> adjacency(n);
        for (auto&& edge : edges) {
            int src = edge[0];
            int dst = edge[1];
            adjacency[src].emplace_back(dst);
            adjacency[dst].emplace_back(src);
        }

        queue<int> bfsQueue;
        bfsQueue.emplace(source);
        vector<bool> visited(n, false);
        visited[source] = true;
        while (bfsQueue.empty() == false) {
            int vertex = bfsQueue.front();
            bfsQueue.pop();
            if (vertex == destination) {
                break;
            }

            for (int next : adjacency[vertex]) {
                if (visited[next] == false) {
                    bfsQueue.emplace(next);
                    visited[next] = true;
                }
            }
        }
        retVal = visited[destination];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> edges;
        int source;
        int destination;
    };
    vector<subject> testData{{3, {{0, 1}, {1, 2}, {2, 0}}, 0, 2}, {6, {{0, 1}, {0, 2}, {3, 5}, {5, 4}, {4, 3}}, 0, 5}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 3, edges = [[0,1],[1,2],[2,0]], source = 0, destination = 2
     *  Output: true
     *
     *  Input: n = 6, edges = [[0,1],[0,2],[3,5],[5,4],[4,3]], source = 0, destination = 5
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", edges = [";
        for (long unsigned int j = 0; j < testData[i].edges.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].edges[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].edges[j][k];
            }
            cout << "]";
        }
        cout << "], source = " << testData[i].source << ", destination = " << testData[i].destination << "\n";

        answer = cSolution.validPath(testData[i].n, testData[i].edges, testData[i].source, testData[i].destination);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
