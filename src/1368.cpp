#include <algorithm>
#include <deque>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    int minCost(vector<vector<int>>& grid) {
        int retVal = 0;

        int gridSize = grid.size();
        int gridColSize = grid[0].size();

        // Track minimum cost to reach each cell
        vector<vector<int>> minCost(gridSize, vector<int>(gridColSize, numeric_limits<int>::max()));
        minCost[0][0] = 0;
        // Direction vectors: right, left, down, up (matching grid values 1,2,3,4)
        vector<vector<int>> direction = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        // Use deque for 0-1 BFS - add zero cost moves to front, cost=1 to back
        deque<pair<int, int>> bfsQueue;
        bfsQueue.push_front({0, 0});
        while (bfsQueue.empty() == false) {
            auto [row, col] = bfsQueue.front();
            bfsQueue.pop_front();

            for (int dir = 0; dir < 4; dir++) {
                int newRow = row + direction[dir][0];
                int newCol = col + direction[dir][1];
                if ((newRow < 0) || (newRow >= gridSize) || (newCol < 0) || (newCol >= gridColSize)) {
                    continue;
                }

                int cost = (grid[row][col] != (dir + 1)) ? (1) : (0);
                if (minCost[row][col] + cost >= minCost[newRow][newCol]) {
                    continue;
                }

                minCost[newRow][newCol] = minCost[row][col] + cost;

                // Add to back if cost=1, front if cost=0
                if (cost == 1) {
                    bfsQueue.push_back({newRow, newCol});
                } else {
                    bfsQueue.push_front({newRow, newCol});
                }
            }
        }
        retVal = minCost[gridSize - 1][gridColSize - 1];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
    };
    vector<subject> testData{{{{1, 1, 1, 1}, {2, 2, 2, 2}, {1, 1, 1, 1}, {2, 2, 2, 2}}},
                             {{{1, 1, 3}, {3, 2, 2}, {1, 1, 4}}},
                             {{{1, 2}, {4, 3}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[1,1,1,1],[2,2,2,2],[1,1,1,1],[2,2,2,2]]
     *  Output: 3
     *
     *  Input: grid = [[1,1,3],[3,2,2],[1,1,4]]
     *  Output: 0
     *
     *  Input: grid = [[1,2],[4,3]]
     *  Output: 1
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
        cout << "]\n";

        answer = cSolution.minCost(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
