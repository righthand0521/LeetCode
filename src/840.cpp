#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int isMagicSquare(vector<vector<int>>& grid, int row, int col) {
        int retVal = 0;

        vector<int> seen(10, 0);  // while a magic square can only contain numbers from 1 to 9
        for (int x = 0; x < 3; ++x) {
            for (int y = 0; y < 3; ++y) {
                int num = grid[row + x][col + y];
                if ((num < 1) || (num > 9)) {
                    return retVal;
                } else if (seen[num] != 0) {
                    return retVal;
                }
                seen[num] = 1;
            }
        }

        int diagonal1 = grid[row][col] + grid[row + 1][col + 1] + grid[row + 2][col + 2];
        int diagonal2 = grid[row + 2][col] + grid[row + 1][col + 1] + grid[row][col + 2];
        if (diagonal1 != diagonal2) {
            return retVal;
        }

        int row1 = grid[row][col] + grid[row][col + 1] + grid[row][col + 2];
        int row2 = grid[row + 1][col] + grid[row + 1][col + 1] + grid[row + 1][col + 2];
        int row3 = grid[row + 2][col] + grid[row + 2][col + 1] + grid[row + 2][col + 2];
        if ((row1 != diagonal1) || (row2 != diagonal1) || (row3 != diagonal1)) {
            return retVal;
        }

        int col1 = grid[row][col] + grid[row + 1][col] + grid[row + 2][col];
        int col2 = grid[row][col + 1] + grid[row + 1][col + 1] + grid[row + 2][col + 1];
        int col3 = grid[row][col + 2] + grid[row + 1][col + 2] + grid[row + 2][col + 2];
        if ((col1 != diagonal1) || (col2 != diagonal1) || (col3 != diagonal1)) {
            return retVal;
        }

        retVal = 1;

        return retVal;
    }

   public:
    int numMagicSquaresInside(vector<vector<int>>& grid) {
        int retVal = 0;

        int rowSize = grid.size();
        int colSize = grid[0].size();  // 1 <= row, col <= 10
        if ((rowSize < 3) || (colSize < 3)) {
            return retVal;
        }

        for (int x = 0; x < rowSize - 2; ++x) {
            for (int y = 0; y < colSize - 2; ++y) {
                retVal += isMagicSquare(grid, x, y);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
    };
    vector<subject> testData{{{{4, 3, 8, 4}, {9, 5, 1, 9}, {2, 7, 6, 2}}}, {{{8}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[4,3,8,4],[9,5,1,9],[2,7,6,2]]
     *  Output: 1
     *
     *  Input: grid = [[8]]
     *  Output: 0
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

        answer = cSolution.numMagicSquaresInside(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
