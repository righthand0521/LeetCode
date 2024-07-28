#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    int secondMinimum(int n, vector<vector<int>>& edges, int time, int change) {
        int retVal = 0;

        //
        vector<vector<int>> adjacency(n + 1);
        for (auto& edge : edges) {
            adjacency[edge[0]].emplace_back(edge[1]);
            adjacency[edge[1]].emplace_back(edge[0]);
        }

        //
        queue<pair<int, int>> bfsQueue;
        bfsQueue.push({1, 1});

        vector<int> dist1(n + 1, -1);
        dist1[1] = 0;

        vector<int> dist2(n + 1, -1);

        //
        while (bfsQueue.empty() == false) {
            auto [node, frequency] = bfsQueue.front();
            bfsQueue.pop();

            // If the timeTaken falls under the red bracket, wait till the path turns green.
            int timeTaken = ((frequency == 1) ? (dist1[node]) : (dist2[node]));
            if ((timeTaken / change) % 2) {
                timeTaken = change * (timeTaken / change + 1) + time;
            } else {
                timeTaken = timeTaken + time;
            }

            for (auto& neighbor : adjacency[node]) {
                if (dist1[neighbor] == -1) {
                    dist1[neighbor] = timeTaken;
                    bfsQueue.push({neighbor, 1});
                } else if ((dist2[neighbor] == -1) && (dist1[neighbor] != timeTaken)) {
                    if (neighbor == n) {
                        retVal = timeTaken;
                        return retVal;
                    }
                    dist2[neighbor] = timeTaken;
                    bfsQueue.push({neighbor, 2});
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
        int time;
        int change;
    };
    vector<subject> testData{{5, {{1, 2}, {1, 3}, {1, 4}, {3, 4}, {4, 5}}, 3, 5}, {2, {{1, 2}}, 3, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 5, edges = [[1,2],[1,3],[1,4],[3,4],[4,5]], time = 3, change = 5
     *  Output: 13
     *
     *  Input: n = 2, edges = [[1,2]], time = 3, change = 2
     *  Output: 11
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
        cout << "]" << ", time = " << testData[i].time << ", change = " << testData[i].change << "\n";

        answer = cSolution.secondMinimum(testData[i].n, testData[i].edges, testData[i].time, testData[i].change);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
