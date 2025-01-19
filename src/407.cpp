#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int retVal = 0;

        int heightMapSize = heightMap.size();
        int heightMapColSize = heightMap[0].size();

        int maxHeight = 0;
        for (int i = 0; i < heightMapSize; ++i) {
            maxHeight = max(maxHeight, *max_element(heightMap[i].begin(), heightMap[i].end()));
        }
        vector<vector<int>> water(heightMapSize, vector<int>(heightMapColSize, maxHeight));
        queue<pair<int, int>> bfsQueue;
        for (int i = 0; i < heightMapSize; ++i) {
            for (int j = 0; j < heightMapColSize; ++j) {
                if ((i != 0) && (i != heightMapSize - 1) && (j != 0) && (j != heightMapColSize - 1)) {
                    continue;
                }

                if (water[i][j] > heightMap[i][j]) {
                    water[i][j] = heightMap[i][j];
                    bfsQueue.push(make_pair(i, j));
                }
            }
        }

        vector<vector<int>> direction = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        while (bfsQueue.empty() == false) {
            int x = bfsQueue.front().first;
            int y = bfsQueue.front().second;
            bfsQueue.pop();

            for (int dir = 0; dir < 4; dir++) {
                int nx = x + direction[dir][0];
                int ny = y + direction[dir][1];
                if ((nx < 0) || (nx >= heightMapSize) || (ny < 0) || (ny >= heightMapColSize)) {
                    continue;
                }

                if ((water[x][y] < water[nx][ny]) && (water[nx][ny] > heightMap[nx][ny])) {
                    water[nx][ny] = max(water[x][y], heightMap[nx][ny]);
                    bfsQueue.push(make_pair(nx, ny));
                }
            }
        }

        for (int i = 0; i < heightMapSize; ++i) {
            for (int j = 0; j < heightMapColSize; ++j) {
                retVal = retVal + water[i][j] - heightMap[i][j];
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> heightMap;
    };
    vector<subject> testData{{{{1, 4, 3, 1, 3, 2}, {3, 2, 1, 3, 2, 4}, {2, 3, 3, 2, 3, 1}}},
                             {{{3, 3, 3, 3, 3}, {3, 2, 2, 2, 3}, {3, 2, 1, 2, 3}, {3, 2, 2, 2, 3}, {3, 3, 3, 3, 3}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: heightMap = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]
     *  Output: 4
     *
     *  Input: heightMap = [[3,3,3,3,3],[3,2,2,2,3],[3,2,1,2,3],[3,2,2,2,3],[3,3,3,3,3]]
     *  Output: 10
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: heightMap = [";
        for (long unsigned int j = 0; j < testData[i].heightMap.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].heightMap[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].heightMap[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.trapRainWater(testData[i].heightMap);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
