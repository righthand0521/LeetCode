#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   private:
    bool isValid(vector<vector<bool>>& visited, int row, int col) {
        bool retVal = true;

        int visitedSize = visited.size();
        int visitedColSize = visited[0].size();
        if (row < 0) {
            retVal = false;
        } else if (row >= visitedSize) {
            retVal = false;
        } else if (col < 0) {
            retVal = false;
        } else if (col >= visitedColSize) {
            retVal = false;
        } else if (visited[row][col] == true) {
            retVal = false;
        }

        return retVal;
    }

   public:
    int minimumTime(vector<vector<int>>& grid) {
        int retVal = -1;

        // If both initial moves require more than 1 second, impossible to proceed
        if ((grid[0][1] > 1) && (grid[1][0] > 1)) {
            return retVal;
        }

        vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int gridSize = grid.size();
        int gridColSize = grid[0].size();

        // Possible movements: down, up, right, left
        vector<vector<bool>> visited(gridSize, vector<bool>(gridColSize, false));

        // Priority queue stores {time, row, col}, Ordered by minimum time to reach each cell.
        priority_queue<vector<int>, vector<vector<int>>, greater<>> priorityQueue;
        priorityQueue.push({grid[0][0], 0, 0});

        while (priorityQueue.empty() == false) {
            auto curr = priorityQueue.top();
            priorityQueue.pop();

            int time = curr[0];
            int row = curr[1];
            int col = curr[2];
            if ((row == gridSize - 1) && (col == gridColSize - 1)) {  // Check if reached target
                retVal = time;
                return retVal;
            }

            // Skip if cell already visited
            if (visited[row][col]) {
                continue;
            }
            visited[row][col] = true;

            // Try all four directions
            for (auto& d : directions) {
                int nextRow = row + d[0];
                int nextCol = col + d[1];
                if (isValid(visited, nextRow, nextCol) == false) {
                    continue;
                }

                // Calculate the wait time needed to move to next cell
                int waitTime = ((grid[nextRow][nextCol] - time) % 2 == 0) ? 1 : 0;
                int nextTime = max(grid[nextRow][nextCol] + waitTime, time + 1);
                priorityQueue.push({nextTime, nextRow, nextCol});
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
    };
    vector<subject> testData{{{{0, 1, 3, 2}, {5, 1, 2, 5}, {4, 3, 8, 6}}}, {{{0, 2, 4}, {3, 2, 1}, {1, 0, 4}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[0,1,3,2],[5,1,2,5],[4,3,8,6]]
     *  Output: 7
     *
     *  Input: grid = [[0,2,4],[3,2,1],[1,0,4]]
     *  Output: -1
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

        answer = cSolution.minimumTime(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
