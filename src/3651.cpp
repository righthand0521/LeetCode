#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    int minCost(vector<vector<int>>& grid, int k) {
        int retVal = 0;

        int rowSize = grid.size();
        int colSize = grid[0].size();

        vector<pair<int, int>> points;
        for (int i = 0; i < rowSize; i++) {
            for (int j = 0; j < colSize; j++) {
                points.push_back({i, j});
            }
        }
        sort(points.begin(), points.end(), [&](const auto& p1, const auto& p2) -> bool {
            return grid[p1.first][p1.second] < grid[p2.first][p2.second];
        });
        int pointsSize = points.size();

        vector<vector<int>> costs(rowSize, vector<int>(colSize, numeric_limits<int>::max()));
        for (int t = 0; t <= k; t++) {
            int minCost = numeric_limits<int>::max();

            for (int i = 0, j = 0; i < pointsSize; i++) {
                int x = points[i].first;
                int y = points[i].second;

                minCost = min(minCost, costs[x][y]);

                if ((i + 1 < pointsSize) && (grid[x][y] == grid[points[i + 1].first][points[i + 1].second])) {
                    continue;
                }

                for (int r = j; r <= i; r++) {
                    costs[points[r].first][points[r].second] = minCost;
                }

                j = i + 1;
            }

            for (int i = rowSize - 1; i >= 0; i--) {
                for (int j = colSize - 1; j >= 0; j--) {
                    if ((i == rowSize - 1) && (j == colSize - 1)) {
                        costs[i][j] = 0;
                        continue;
                    }

                    if (i != rowSize - 1) {
                        costs[i][j] = min(costs[i][j], costs[i + 1][j] + grid[i + 1][j]);
                    }

                    if (j != colSize - 1) {
                        costs[i][j] = min(costs[i][j], costs[i][j + 1] + grid[i][j + 1]);
                    }
                }
            }
        }
        retVal = costs[0][0];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
        int k;
    };
    vector<subject> testData{{{{1, 3, 3}, {2, 5, 4}, {4, 3, 5}}, 2}, {{{1, 2}, {2, 3}, {3, 4}}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[1,3,3],[2,5,4],[4,3,5]], k = 2
     *  Output: 7
     *
     *  Input: grid = [[1,2],[2,3],[3,4]], k = 1
     *  Output: 9
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: grid = [";
        for (long unsigned int j = 0; j < testData[i].grid.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].grid[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].grid[j][k];
            }
            cout << "]";
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.minCost(testData[i].grid, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
