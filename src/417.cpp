#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<vector<int>> heights;
    vector<vector<int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    void bfs(int row, int col, vector<vector<bool>>& ocean) {
        if (ocean[row][col] == true) {
            return;
        }
        ocean[row][col] = true;

        int heightsSize = heights.size();
        int heightsColSize = heights[0].size();

        queue<pair<int, int>> bfsQueue;
        bfsQueue.emplace(row, col);
        while (bfsQueue.empty() == false) {
            auto [row, col] = bfsQueue.front();
            bfsQueue.pop();
            for (int i = 0; i < 4; i++) {
                int nextRow = row + directions[i][0];
                int nextCol = col + directions[i][1];
                if ((nextRow < 0) || (nextRow >= heightsSize) || (nextCol < 0) || (nextCol >= heightsColSize)) {
                    continue;
                } else if (ocean[nextRow][nextCol] == true) {
                    continue;
                }

                if (heights[nextRow][nextCol] >= heights[row][col]) {
                    ocean[nextRow][nextCol] = true;
                    bfsQueue.emplace(nextRow, nextCol);
                }
            }
        }
    }

   public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        vector<vector<int>> retVal;

        this->heights = heights;
        int heightsSize = heights.size();
        int heightsColSize = heights[0].size();

        vector<vector<bool>> pacific(heightsSize, vector<bool>(heightsColSize, false));
        for (int i = 0; i < heightsSize; i++) {
            bfs(i, 0, pacific);
        }
        for (int j = 1; j < heightsColSize; j++) {
            bfs(0, j, pacific);
        }

        vector<vector<bool>> atlantic(heightsSize, vector<bool>(heightsColSize, false));
        for (int i = 0; i < heightsSize; i++) {
            bfs(i, heightsColSize - 1, atlantic);
        }
        for (int j = 0; j < heightsColSize - 1; j++) {
            bfs(heightsSize - 1, j, atlantic);
        }

        for (int i = 0; i < heightsSize; i++) {
            for (int j = 0; j < heightsColSize; j++) {
                if (pacific[i][j] && atlantic[i][j]) {
                    vector<int> cell;
                    cell.emplace_back(i);
                    cell.emplace_back(j);
                    retVal.emplace_back(cell);
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> heights;
    };
    vector<subject> testData{{{{1, 2, 2, 3, 5}, {3, 2, 3, 4, 4}, {2, 4, 5, 3, 1}, {6, 7, 1, 4, 5}, {5, 1, 1, 2, 4}}},
                             {{{1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
     *  Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
     *
     *  Input: heights = [[1]]
     *  Output: [[0,0]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: heights = [";
        for (long unsigned int j = 0; j < testData[i].heights.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].heights[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].heights[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.pacificAtlantic(testData[i].heights);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < answer[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << answer[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
