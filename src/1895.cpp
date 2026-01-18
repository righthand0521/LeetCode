#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        int retVal = 1;

        int rowSize = grid.size();
        int colSize = grid[0].size();

        // prefix sum of each row
        vector<vector<int>> rowsum(rowSize, vector<int>(colSize));
        for (int i = 0; i < rowSize; ++i) {
            rowsum[i][0] = grid[i][0];
            for (int j = 1; j < colSize; ++j) {
                rowsum[i][j] = rowsum[i][j - 1] + grid[i][j];
            }
        }
        // prefix sum of each column
        vector<vector<int>> colsum(rowSize, vector<int>(colSize));
        for (int j = 0; j < colSize; ++j) {
            colsum[0][j] = grid[0][j];
            for (int i = 1; i < rowSize; ++i) {
                colsum[i][j] = colsum[i - 1][j] + grid[i][j];
            }
        }

        // enumerate edge lengths from largest to smallest
        for (int edge = min(rowSize, colSize); edge >= 2; --edge) {
            // enumerate the top-left corner position (i,j) of the square
            for (int i = 0; i + edge <= rowSize; ++i) {
                for (int j = 0; j + edge <= colSize; ++j) {
                    // the value for each row, column, and diagonal should be calculated (using the first row as a
                    // sample)
                    int stdsum = rowsum[i][j + edge - 1] - (j ? rowsum[i][j - 1] : 0);
                    bool check = true;

                    // enumerate each row and directly compute the sum using prefix sums since we have already used the
                    // first line as a sample, we can skip the first line here.
                    for (int ii = i + 1; ii < i + edge; ++ii) {
                        if (rowsum[ii][j + edge - 1] - (j ? rowsum[ii][j - 1] : 0) != stdsum) {
                            check = false;
                            break;
                        }
                    }
                    if (check == false) {
                        continue;
                    }

                    // enumerate each column and directly calculate the sum using prefix sums
                    for (int jj = j; jj < j + edge; ++jj) {
                        if (colsum[i + edge - 1][jj] - (i ? colsum[i - 1][jj] : 0) != stdsum) {
                            check = false;
                            break;
                        }
                    }
                    if (check == false) {
                        continue;
                    }

                    // d1 and d2 represent the sums of the two diagonals respectively. here d denotes diagonal
                    int d1 = 0;
                    int d2 = 0;
                    // sum directly by traversing without using the prefix sum.
                    for (int k = 0; k < edge; ++k) {
                        d1 += grid[i + k][j + k];
                        d2 += grid[i + k][j + edge - 1 - k];
                    }
                    if (d1 == stdsum && d2 == stdsum) {
                        retVal = edge;
                        return retVal;
                    }
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
    vector<subject> testData{{{{7, 1, 4, 5, 6}, {2, 5, 1, 6, 4}, {1, 5, 4, 3, 2}, {1, 2, 7, 3, 4}}},
                             {{{5, 1, 3, 1}, {9, 3, 3, 1}, {1, 3, 3, 8}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[7,1,4,5,6],[2,5,1,6,4],[1,5,4,3,2],[1,2,7,3,4]]
     *  Output: 3
     *
     *  Input: grid = [[5,1,3,1],[9,3,3,1],[1,3,3,8]]
     *  Output: 2
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

        answer = cSolution.largestMagicSquare(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
