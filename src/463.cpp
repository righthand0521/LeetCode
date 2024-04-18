#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int rowDirection[4] = {1, -1, 0, 0};
    int colDirection[4] = {0, 0, 1, -1};

   public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int retVal = 0;

        int gridSize = grid.size();
        int gridColSize = grid[0].size();

        for (int x = 0; x < gridSize; ++x) {
            for (int y = 0; y < gridColSize; ++y) {
                if (grid[x][y] == 0) {
                    continue;
                }

                int count = 0;
                for (int i = 0; i < 4; ++i) {
                    int row = x + rowDirection[i];
                    int col = y + colDirection[i];
                    if ((row < 0) || (row >= gridSize) || (col < 0) || (col >= gridColSize)) {
                        count++;
                    } else if (grid[row][col] == 0) {
                        count++;
                    }
                }
                retVal += count;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
    };
    vector<subject> testData{{{{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}}}, {{{1}}}, {{{1, 0}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
     *  Output: 16
     *
     *  Input: grid = [[1]]
     *  Output: 4
     *
     *  Input: grid = [[1,0]]
     *  Output: 4
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

        answer = cSolution.islandPerimeter(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
