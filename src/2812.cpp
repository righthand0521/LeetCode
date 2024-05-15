#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<vector<int>> direction = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    bool isValidCell(vector<vector<int>>& grid, int i, int j) {
        bool retVal = false;

        int gridSize = grid.size();
        if ((i >= 0) && (i < gridSize) && (j >= 0) && (j < gridSize)) {
            retVal = true;
        }

        return retVal;
    }

   public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int retVal = -1;

        int gridSize = grid.size();

        // Mark thieves as 0 and empty cells as -1, and push thieves to the queue
        queue<pair<int, int>> multiSourceQueue;
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                if (grid[i][j] == 1) {
                    multiSourceQueue.push({i, j});
                    grid[i][j] = 0;
                } else {
                    grid[i][j] = -1;
                }
            }
        }

        // Calculate safeness factor for each cell using BFS
        while (multiSourceQueue.empty() == false) {
            int multiSourceQueueSize = multiSourceQueue.size();
            while (multiSourceQueueSize-- > 0) {
                auto curr = multiSourceQueue.front();
                multiSourceQueue.pop();

                // Check neighboring cells
                for (auto& d : direction) {
                    int di = curr.first + d[0];
                    int dj = curr.second + d[1];
                    int val = grid[curr.first][curr.second];

                    // Check if the neighboring cell is valid and unvisited
                    if ((isValidCell(grid, di, dj) == true) && (grid[di][dj] == -1)) {
                        grid[di][dj] = val + 1;
                        multiSourceQueue.push({di, dj});
                    }
                }
            }
        }

        // Priority queue to prioritize cells with higher safeness factor, Push starting cell to the priority queue.
        priority_queue<vector<int>> pq;
        pq.push(vector<int>{grid[0][0], 0, 0});  // [maximum_safeness_till_now, x-coordinate, y-coordinate]
        grid[0][0] = -1;                         // Mark the source cell as visited

        // BFS to find the path with maximum safeness factor
        while (pq.empty() == false) {
            auto curr = pq.top();
            pq.pop();

            // If reached the destination, return safeness factor
            if ((curr[1] == gridSize - 1) && (curr[2] == gridSize - 1)) {
                retVal = curr[0];
                break;
            }

            // Explore neighboring cells
            for (auto& d : direction) {
                int di = d[0] + curr[1];
                int dj = d[1] + curr[2];
                if (isValidCell(grid, di, dj) && grid[di][dj] != -1) {
                    // Update safeness factor for the path and mark the cell as visited
                    pq.push(vector<int>{min(curr[0], grid[di][dj]), di, dj});
                    grid[di][dj] = -1;
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
    };
    vector<subject> testData{{{{1, 0, 0}, {0, 0, 0}, {0, 0, 1}}},
                             {{{0, 0, 1}, {0, 0, 0}, {0, 0, 0}}},
                             {{{0, 0, 0, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 0, 0, 0}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[1,0,0],[0,0,0],[0,0,1]]
     *  Output: 0
     *
     *  Input: grid = [[0,0,1],[0,0,0],[0,0,0]]
     *  Output: 2
     *
     *  Input: grid = [[0,0,0,1],[0,0,0,0],[0,0,0,0],[1,0,0,0]]
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: grid = [";
        for (long unsigned int j = 0; j < testData[i].grid.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].grid[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].grid[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.maximumSafenessFactor(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
