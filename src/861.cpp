#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int matrixScore(vector<vector<int>>& grid) {
        int retVal = 0;

        int gridSize = grid.size();
        int gridColSize = grid[0].size();

        // Set score to summation of first column
        retVal = (1 << (gridColSize - 1)) * gridSize;

        for (int col = 1; col < gridColSize; col++) {
            int countSameBits = 0;
            for (int row = 0; row < gridSize; row++) {
                // Count elements matching first in row
                if (grid[row][col] == grid[row][0]) {
                    countSameBits++;
                }
            }

            // Calculate score based on the number of same bits in a column
            countSameBits = max(countSameBits, gridSize - countSameBits);

            // Calculate the score contribution for the current column
            int columnScore = (1 << (gridColSize - col - 1)) * countSameBits;

            // Add contribution to score
            retVal += columnScore;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
    };
    vector<subject> testData{{{{0, 0, 1, 1}, {1, 0, 1, 0}, {1, 1, 0, 0}}}, {{{1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[0,0,1,1],[1,0,1,0],[1,1,0,0]]
     *  Output: 39
     *
     *  Input: grid = [[0]]
     *  Output: 1
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

        answer = cSolution.matrixScore(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
