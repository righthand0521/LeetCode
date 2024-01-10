#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maximalNetworkRank(int n, vector<vector<int>>& roads) {
        int retVal = 0;

        vector<vector<int>> connect(n, vector<int>(n, 0));
        vector<int> degree(n, 0);
        for (auto vertex : roads) {
            int a = vertex[0];
            int b = vertex[1];
            connect[a][b] = 1;
            connect[b][a] = 1;
            degree[a]++;
            degree[b]++;
        }

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int rank = degree[i] + degree[j] - connect[i][j];
                retVal = max(retVal, rank);
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
    vector<subject> testData{{4, {{0, 1}, {0, 3}, {1, 2}, {1, 3}}},
                             {5, {{0, 1}, {0, 3}, {1, 2}, {1, 3}, {2, 3}, {2, 4}}},
                             {8, {{0, 1}, {1, 2}, {2, 3}, {2, 4}, {5, 6}, {5, 7}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 4, roads = [[0,1],[0,3],[1,2],[1,3]]
     *  Output: 4
     *
     *  Input: n = 5, roads = [[0,1],[0,3],[1,2],[1,3],[2,3],[2,4]]
     *  Output: 5
     *
     *  Input: n = 8, roads = [[0,1],[1,2],[2,3],[2,4],[5,6],[5,7]]
     *  Output: 5
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

        answer = cSolution.maximalNetworkRank(testData[i].n, testData[i].roads);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
