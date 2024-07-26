#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    void dijkstra(int n, vector<vector<pair<int, int>>>& adjacencyList, vector<int>& shortestPathDistances,
                  int source) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> priorityQueue;
        priorityQueue.emplace(0, source);

        fill(shortestPathDistances.begin(), shortestPathDistances.end(), numeric_limits<int>::max());
        shortestPathDistances[source] = 0;

        while (priorityQueue.empty() == false) {
            auto [currentDistance, currentCity] = priorityQueue.top();
            priorityQueue.pop();
            if (currentDistance > shortestPathDistances[currentCity]) {
                continue;
            }

            for (auto& [neighborCity, edgeWeight] : adjacencyList[currentCity]) {
                if (shortestPathDistances[neighborCity] > currentDistance + edgeWeight) {
                    shortestPathDistances[neighborCity] = currentDistance + edgeWeight;
                    priorityQueue.emplace(shortestPathDistances[neighborCity], neighborCity);
                }
            }
        }
    }
    int getCityWithFewestReachable(int n, vector<vector<int>>& shortestPathMatrix, int distanceThreshold) {
        int retVal = 0;

        int cityWithFewestReachable = -1;
        int fewestReachableCount = n;
        for (int i = 0; i < n; i++) {
            int reachableCount = 0;
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    continue;
                }
                if (shortestPathMatrix[i][j] <= distanceThreshold) {
                    reachableCount++;
                }
            }
            if (reachableCount <= fewestReachableCount) {
                fewestReachableCount = reachableCount;
                cityWithFewestReachable = i;
            }
        }
        retVal = cityWithFewestReachable;

        return retVal;
    }
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        int retVal = 0;

        vector<vector<pair<int, int>>> adjacencyList(n);
        for (const auto& edge : edges) {
            int start = edge[0];
            int end = edge[1];
            int weight = edge[2];
            adjacencyList[start].emplace_back(end, weight);
            adjacencyList[end].emplace_back(start, weight);
        }

        vector<vector<int>> shortestPathMatrix(n, vector<int>(n, numeric_limits<int>::max()));
        for (int i = 0; i < n; i++) {
            shortestPathMatrix[i][i] = 0;
        }

        for (int i = 0; i < n; i++) {
            dijkstra(n, adjacencyList, shortestPathMatrix[i], i);
        }
        retVal = getCityWithFewestReachable(n, shortestPathMatrix, distanceThreshold);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> edges;
        int distanceThreshold;
    };
    vector<subject> testData{{4, {{0, 1, 3}, {1, 2, 1}, {1, 3, 4}, {2, 3, 1}}, 4},
                             {5, {{0, 1, 2}, {0, 4, 8}, {1, 2, 3}, {1, 4, 2}, {2, 3, 1}, {3, 4, 1}}, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 4, edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]], distanceThreshold = 4
     *  Output: 3
     *
     *  Input: n = 5, edges = [[0,1,2],[0,4,8],[1,2,3],[1,4,2],[2,3,1],[3,4,1]], distanceThreshold = 2
     *  Output: 0
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
        cout << "]" << ", distanceThreshold = " << testData[i].distanceThreshold << "\n";

        answer = cSolution.findTheCity(testData[i].n, testData[i].edges, testData[i].distanceThreshold);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
