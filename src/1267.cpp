#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int countServers(vector<vector<int>>& grid) {
        int retVal = 0;

        int rowSize = grid.size();
        int colSize = grid[0].size();

        vector<int> rowCounts(colSize, 0);
        vector<int> colCounts(rowSize, 0);
        for (int row = 0; row < rowSize; ++row)
            for (int col = 0; col < colSize; ++col)
                if (grid[row][col] == 1) {  // grid[i][j] == 0 or 1
                    rowCounts[col]++;
                    colCounts[row]++;
                }

        for (int row = 0; row < rowSize; ++row) {
            for (int col = 0; col < colSize; ++col) {
                if (grid[row][col] == 1) {  // grid[i][j] == 0 or 1
                    retVal += ((rowCounts[col] > 1) || (colCounts[row] > 1));
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
    vector<subject> testData{
        {{{1, 0}, {0, 1}}}, {{{1, 0}, {1, 1}}}, {{{1, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[1,0],[0,1]]
     *  Output: 0
     *
     *  Input: grid = [[1,0],[1,1]]
     *  Output: 3
     *
     *  Input: grid = [[1,1,0,0],[0,0,1,0],[0,0,1,0],[0,0,0,1]]
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

        answer = cSolution.countServers(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
