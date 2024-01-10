#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int retVal = 0;

        if (obstacleGrid[0][0] == 1) {
            return retVal;
        }

        int row = obstacleGrid.size();
        int col = obstacleGrid[0].size();

        /* Example
         *    | 0 1 2 | 0 1 2
         *  --+-------+-------
         *  0 | 0 0 0 | 1 1 1
         *  1 | 0 1 0 | 1 0 1
         *  2 | 0 0 0 | 1 1 2
         */
        obstacleGrid[0][0] = 1;
        for (int i = 1; i < row; ++i) {
            obstacleGrid[i][0] = (((obstacleGrid[i][0] == 0) && (obstacleGrid[i - 1][0] == 1)) ? (1) : (0));
        }
        for (int i = 1; i < col; ++i) {
            obstacleGrid[0][i] = (((obstacleGrid[0][i] == 0) && (obstacleGrid[0][i - 1] == 1)) ? (1) : (0));
        }

        for (int i = 1; i < row; ++i) {
            for (int j = 1; j < col; ++j) {
                obstacleGrid[i][j] =
                    ((obstacleGrid[i][j] == 0) ? (obstacleGrid[i - 1][j] + obstacleGrid[i][j - 1]) : (0));
            }
        }
        retVal = obstacleGrid[row - 1][col - 1];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> obstacleGrid;
    };
    vector<subject> testData{{{{0, 0, 0}, {0, 1, 0}, {0, 0, 0}}}, {{{0, 1}, {0, 0}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
     *  Output: 2
     *
     *  Input: obstacleGrid = [[0,1],[0,0]]
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: obstacleGrid = [";
        for (long unsigned int j = 0; j < testData[i].obstacleGrid.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].obstacleGrid[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].obstacleGrid[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.uniquePathsWithObstacles(testData[i].obstacleGrid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
