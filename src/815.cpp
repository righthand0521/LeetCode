#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        int retVal = 0;

        if (source == target) {
            return retVal;
        }

        int routesSize = routes.size();
        vector<vector<int>> edge(routesSize, vector<int>(routesSize));
        unordered_map<int, vector<int>> rec;
        for (int i = 0; i < routesSize; i++) {
            for (int site : routes[i]) {
                for (int j : rec[site]) {
                    edge[i][j] = edge[j][i] = true;
                }
                rec[site].emplace_back(i);
            }
        }

        vector<int> dis(routesSize, -1);
        queue<int> que;
        for (int bus : rec[source]) {
            dis[bus] = 1;
            que.push(bus);
        }
        while (que.empty() == false) {
            int x = que.front();
            que.pop();
            for (int y = 0; y < routesSize; y++) {
                if (edge[x][y] && dis[y] == -1) {
                    dis[y] = dis[x] + 1;
                    que.push(y);
                }
            }
        }

        retVal = numeric_limits<int>::max();
        for (int bus : rec[target]) {
            if (dis[bus] != -1) {
                retVal = min(retVal, dis[bus]);
            }
        }
        if (retVal == numeric_limits<int>::max()) {
            retVal = -1;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> routes;
        int source;
        int target;
    };
    vector<subject> testData{{{{1, 2, 7}, {3, 6, 7}}, 1, 6},
                             {{{7, 12}, {4, 5, 15}, {6}, {15, 19}, {9, 12, 13}}, 15, 12}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: routes = [[1,2,7],[3,6,7]], source = 1, target = 6
     *  Output: 2
     *
     *  Input: routes = [[7,12],[4,5,15],[6],[15,19],[9,12,13]], source = 15, target = 12
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: routes = [";
        for (long unsigned int j = 0; j < testData[i].routes.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].routes[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].routes[j][k];
            }
            cout << "]";
        }
        cout << "], source = " << testData[i].source << ", target = " << testData[i].target << "\n";

        answer = cSolution.numBusesToDestination(testData[i].routes, testData[i].source, testData[i].target);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
