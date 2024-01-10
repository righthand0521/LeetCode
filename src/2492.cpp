#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    int minScore(int n, vector<vector<int>>& roads) {
        int retVal = 0;

        int roadsSize = roads.size();

        //
        vector<pair<int, int>> adjacent[n + 1];
        for (int i = 0; i < roadsSize; ++i) {
            adjacent[roads[i][0]].push_back({roads[i][1], roads[i][2]});
            adjacent[roads[i][1]].push_back({roads[i][0], roads[i][2]});
        }

        // Breadth-First Search
        queue<int> bfsQueue;
        bfsQueue.push(1);

        vector<bool> visit(n + 1);
        visit[1] = true;

        retVal = numeric_limits<int>::max();
        while (bfsQueue.empty() == false) {
            int src = bfsQueue.front();
            bfsQueue.pop();

            for (auto& iterator : adjacent[src]) {
                int dest = iterator.first;
                if (visit[dest] == false) {
                    bfsQueue.push(dest);
                    visit[dest] = true;
                }

                int distance = iterator.second;
                retVal = (distance < retVal ? distance : retVal);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> roads;
    };
    vector<subject> testData{{4, {{1, 2, 9}, {2, 3, 6}, {2, 4, 5}, {1, 4, 7}}}, {4, {{1, 2, 2}, {1, 3, 4}, {3, 4, 7}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 4, roads = [[1,2,9],[2,3,6],[2,4,5],[1,4,7]]
     *  Output: 5
     *
     *  Input: n = 4, roads = [[1,2,2],[1,3,4],[3,4,7]]
     *  Output: 2
     */

    Solution cSolution;
    int answer = 0;
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

        answer = cSolution.minScore(testData[i].n, testData[i].roads);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
