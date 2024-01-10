#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> onesMinusZeros(vector<vector<int>>& grid) {
        vector<vector<int>> retVal;

        // m == grid.length, n == grid[i].length, 1 <= m, n <= 10^5.
        int rowSize = grid.size();
        int colSize = grid[0].size();
        retVal.resize(rowSize, vector<int>(colSize, 0));

        vector<int> rowSum(rowSize, 0);
        vector<int> colSum(colSize, 0);
        for (int i = 0; i < rowSize; ++i) {
            for (int j = 0; j < colSize; ++j) {
                // grid[i][j] is either 0 or 1.
                rowSum[i] += grid[i][j];
                colSum[j] += grid[i][j];
            }
        }

        for (int i = 0; i < rowSize; ++i) {
            for (int j = 0; j < colSize; ++j) {
                retVal[i][j] = rowSum[i] + colSum[j];
                retVal[i][j] -= (rowSize - rowSum[i]);
                retVal[i][j] -= (colSize - colSum[j]);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
    };
    vector<subject> testData{{{{0, 1, 1}, {1, 0, 1}, {0, 0, 1}}}, {{{1, 1, 1}, {1, 1, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[0,1,1],[1,0,1],[0,0,1]]
     *  Output: [[0,0,4],[0,0,4],[-2,-2,2]]
     *
     *  Input: grid = [[1,1,1],[1,1,1]]
     *  Output: [[5,5,5],[5,5,5]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
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

        answer = cSolution.onesMinusZeros(testData[i].grid);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < answer[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << answer[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
