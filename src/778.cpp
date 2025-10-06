#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   private:
    bool bfs(vector<vector<int>>& grid, int threshold) {
        bool retVal = false;

        int gridSize = grid.size();
        if (grid[0][0] > threshold) {
            return retVal;
        }

        vector<vector<bool>> visited(gridSize, vector<bool>(gridSize, false));
        visited[0][0] = true;
        vector<vector<int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        queue<pair<int, int>> bfsQueue;
        bfsQueue.push({0, 0});
        while (bfsQueue.empty() == false) {
            auto [x, y] = bfsQueue.front();
            bfsQueue.pop();

            for (int i = 0; i < 4; i++) {
                int nextX = x + directions[i][0];
                int nextY = y + directions[i][1];
                if ((nextX < 0) || (nextX >= gridSize) || (nextY < 0) || (nextY >= gridSize)) {
                    continue;
                } else if (visited[nextX][nextY]) {
                    continue;
                } else if (grid[nextX][nextY] > threshold) {
                    continue;
                }

                if (nextX == gridSize - 1 && nextY == gridSize - 1) {
                    retVal = true;
                    return retVal;
                }
                visited[nextX][nextY] = true;
                bfsQueue.push({nextX, nextY});
            }
        }

        return retVal;
    }

   public:
    int swimInWater(vector<vector<int>>& grid) {
        int retVal = 0;

        int gridSize = grid.size();

        int left = 0;
        int right = gridSize * gridSize - 1;
        while (left < right) {
            int middle = (left + right) / 2;
            if ((grid[0][0] <= middle) && (bfs(grid, middle) == true)) {
                right = middle;
            } else {
                left = middle + 1;
            }
        }
        retVal = left;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
    };
    vector<subject> testData{
        {{{0, 2}, {1, 3}}},
        {{{0, 1, 2, 3, 4}, {24, 23, 22, 21, 5}, {12, 13, 14, 15, 16}, {11, 17, 18, 19, 20}, {10, 9, 8, 7, 6}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[0,2],[1,3]]
     *  Output: 3
     *
     *  Input: grid = [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
     *  Output: 16
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

        answer = cSolution.swimInWater(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
