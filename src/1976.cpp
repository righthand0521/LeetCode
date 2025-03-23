#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   private:
    const int MODULO = 1e9 + 7;

   public:
    int countPaths(int n, vector<vector<int>>& roads) {
        int retVal = 0;

        // Build adjacency list
        vector<vector<pair<int, int>>> adjacency(n);
        for (auto& road : roads) {
            int startNode = road[0], endNode = road[1], travelTime = road[2];
            adjacency[startNode].emplace_back(endNode, travelTime);
            adjacency[endNode].emplace_back(startNode, travelTime);
        }

        // Min-Heap (priority queue) for Dijkstra
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> minHeap;
        minHeap.emplace(0, 0);  // {time, node}

        // Store shortest time to each node
        vector<long long> shortestTime(n, numeric_limits<long long>::max());
        shortestTime[0] = 0;  // Distance to source is 0

        // Number of ways to reach each node in shortest time
        vector<int> pathCount(n, 0);
        pathCount[0] = 1;  // 1 way to reach node 0

        while (minHeap.empty() == false) {
            long long currTime = minHeap.top().first;  // Current shortest time
            int currNode = minHeap.top().second;
            minHeap.pop();

            // Skip outdated distances
            if (currTime > shortestTime[currNode]) {
                continue;
            }

            for (auto& [neighborNode, roadTime] : adjacency[currNode]) {
                // Found a new shortest path → Update shortest time and reset path count
                if (currTime + roadTime < shortestTime[neighborNode]) {
                    shortestTime[neighborNode] = currTime + roadTime;
                    pathCount[neighborNode] = pathCount[currNode];
                    minHeap.emplace(shortestTime[neighborNode], neighborNode);
                }
                // Found another way with the same shortest time → Add to path count
                else if (currTime + roadTime == shortestTime[neighborNode]) {
                    pathCount[neighborNode] = (pathCount[neighborNode] + pathCount[currNode]) % MODULO;
                }
            }
        }
        retVal = pathCount[n - 1];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> roads;
    };
    vector<subject> testData{{7,
                              {{0, 6, 7},
                               {0, 1, 2},
                               {1, 2, 3},
                               {1, 3, 3},
                               {6, 3, 3},
                               {3, 5, 1},
                               {6, 5, 1},
                               {2, 5, 1},
                               {0, 4, 5},
                               {4, 6, 2}}},
                             {2, {{1, 0, 10}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 7, roads = [[0,6,7],[0,1,2],[1,2,3],[1,3,3],[6,3,3],[3,5,1],[6,5,1],[2,5,1],[0,4,5],[4,6,2]]
     *  Output: 4
     *
     *  Input: n = 2, roads = [[1,0,10]]
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", roads = [";
        for (long unsigned int j = 0; j < testData[i].roads.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].roads[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].roads[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.countPaths(testData[i].n, testData[i].roads);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
