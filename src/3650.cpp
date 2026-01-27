#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    int minCost(int n, vector<vector<int>>& edges) {
        int retVal = -1;

        vector<vector<pair<int, int>>> adjacency(n);
        for (auto& e : edges) {
            int x = e[0];
            int y = e[1];
            int w = e[2];
            adjacency[x].emplace_back(y, w);
            adjacency[y].emplace_back(x, 2 * w);
        }

        vector<int> distance(n, numeric_limits<int>::max());
        distance[0] = 0;
        vector<bool> visited(n, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
        heap.emplace(0, 0);
        while (heap.empty() == false) {
            int x = heap.top().second;
            heap.pop();
            if (x == n - 1) {
                retVal = distance[x];
                break;
            }

            if (visited[x] == true) {
                continue;
            }
            visited[x] = true;

            for (auto& [y, w] : adjacency[x]) {
                if (distance[x] + w < distance[y]) {
                    distance[y] = distance[x] + w;
                    heap.emplace(distance[y], y);
                }
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
    vector<subject> testData{{4, {{0, 1, 3}, {3, 1, 1}, {2, 3, 4}, {0, 2, 2}}},
                             {4, {{0, 2, 1}, {2, 1, 1}, {1, 3, 1}, {2, 3, 3}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 4, edges = [[0,1,3],[3,1,1],[2,3,4],[0,2,2]]
     *  Output: 5
     *
     *  Input: n = 4, edges = [[0,2,1],[2,1,1],[1,3,1],[2,3,3]]
     *  Output: 3
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

        answer = cSolution.minCost(testData[i].n, testData[i].edges);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
