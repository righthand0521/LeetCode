#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    typedef vector<vector<vector<int>>> threeIntVector;
    typedef vector<vector<int>> twoIntVector;

    int shortestPathAllKeys(vector<string>& grid) {
        int retVal = -1;

        //
        int gridSize = grid.size();
        int gridColSize = grid[0].size();

        //
        int startX = 0;
        int startY = 0;
        unordered_map<char, int> keyToIdx;
        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridColSize; ++j) {
                if (grid[i][j] == '@') {
                    startX = i;
                    startY = j;
                } else if (islower(grid[i][j])) {
                    if (keyToIdx.count(grid[i][j]) == 0) {
                        int idx = keyToIdx.size();
                        keyToIdx[grid[i][j]] = idx;
                    }
                }
            }
        }

        //
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        queue<tuple<int, int, int>> bfsQueue;
        threeIntVector visited(gridSize, twoIntVector(gridColSize, vector<int>(1 << keyToIdx.size(), -1)));
        bfsQueue.emplace(startX, startY, 0);
        visited[startX][startY][0] = 0;
        while (bfsQueue.empty() == false) {
            auto [x, y, mask] = bfsQueue.front();
            bfsQueue.pop();

            for (int i = 0; i < 4; ++i) {
                int nextX = x + directions[i][0];
                int nextY = y + directions[i][1];

                if ((nextX < 0) || (nextX >= gridSize)) {
                    continue;
                } else if ((nextY < 0) || (nextY >= gridColSize)) {
                    continue;
                } else if (grid[nextX][nextY] == '#') {
                    continue;
                }

                if ((grid[nextX][nextY] == '.') || (grid[nextX][nextY] == '@')) {
                    if (visited[nextX][nextY][mask] == -1) {
                        visited[nextX][nextY][mask] = visited[x][y][mask] + 1;
                        bfsQueue.emplace(nextX, nextY, mask);
                    }
                } else if (islower(grid[nextX][nextY])) {
                    int idx = keyToIdx[grid[nextX][nextY]];
                    if (visited[nextX][nextY][mask | (1 << idx)] == -1) {
                        visited[nextX][nextY][mask | (1 << idx)] = visited[x][y][mask] + 1;
                        if ((mask | (1 << idx)) == (1 << keyToIdx.size()) - 1) {
                            retVal = visited[nextX][nextY][mask | (1 << idx)];
                            return retVal;
                        }
                        bfsQueue.emplace(nextX, nextY, mask | (1 << idx));
                    }
                } else {
                    int idx = keyToIdx[tolower(grid[nextX][nextY])];
                    if ((mask & (1 << idx)) && visited[nextX][nextY][mask] == -1) {
                        visited[nextX][nextY][mask] = visited[x][y][mask] + 1;
                        bfsQueue.emplace(nextX, nextY, mask);
                    }
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> grid;
    };
    vector<subject> testData{{{"@.a..", "###.#", "b.A.B"}}, {{"@..aA", "..B#.", "....b"}}, {{"@Aa"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = ["@.a..","###.#","b.A.B"]
     *  Output: 8
     *
     *  Input: grid = ["@..aA","..B#.","....b"]
     *  Output: 6
     *
     *  Input: grid = ["@Aa"]
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: grid = [";
        for (long unsigned int j = 0; j < testData[i].grid.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[\"";
            for (long unsigned int k = 0; k < testData[i].grid[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].grid[j][k];
            }
            cout << "\"]";
        }
        cout << "]\n";

        answer = cSolution.shortestPathAllKeys(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
