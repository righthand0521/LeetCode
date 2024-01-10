#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> retVal;

        int rowSize = matrix.size();
        int colSize = matrix[0].size();
        int maxReturnSize = rowSize * colSize;

        int returnSize = 0;
        int i, j;
        for (i = 0; i <= rowSize / 2; ++i) {
            /* first row: x1, last column: x2, last row: x3, first column: x4.
             *
             *  (top,left)               (top,right)
             *      +------------------------+
             *      | 11 | 11 | 11 | 11 | 11 |
             *      | 14 | 21 | 21 | 21 | 12 |
             *      | 14 | 24 | 31 | 22 | 12 |
             *      | 14 | 23 | 23 | 22 | 12 |
             *      | 13 | 13 | 13 | 13 | 12 |
             *      +------------------------+
             * (down,left)              (down,right)
             */

            // first row
            for (j = i; j < colSize - i; ++j) {
                retVal.push_back(matrix[i][j]);
                ++returnSize;
                if (returnSize == maxReturnSize) {
                    return retVal;
                }
            }
            if (i + 1 == rowSize - i) {
                continue;
            }

            // last column
            for (j = i + 1; j < rowSize - i; ++j) {
                retVal.push_back(matrix[j][colSize - 1 - i]);
                ++returnSize;
                if (returnSize == maxReturnSize) {
                    return retVal;
                }
            }
            if (i + 1 == colSize) {
                continue;
            }

            // last row
            for (j = colSize - 1 - (i + 1); j >= i; --j) {
                retVal.push_back(matrix[rowSize - 1 - i][j]);
                ++returnSize;
                if (returnSize == maxReturnSize) {
                    return retVal;
                }
            }

            // first column
            for (j = rowSize - 1 - (i + 1); j > i; --j) {
                retVal.push_back(matrix[j][i]);
                ++returnSize;
                if (returnSize == maxReturnSize) {
                    return retVal;
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> matrix;
    };
    vector<subject> testData{{{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}},
                             {{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}},
                             {{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}}},
                             {{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}}},
                             {{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}}},
                             {{{1, 2, 3, 4, 5, 6, 7, 8, 9}}},
                             {{{1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}}},
                             {{{1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
     *  Output: [1,2,3,6,9,8,7,4,5]
     *
     *  Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
     *  Output: [1,2,3,4,8,12,11,10,9,5,6,7]
     *
     *  Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]]
     *  Output: [1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10]
     *
     *  Input: matrix = [[1,2,3],[4,5,6],[7,8,9],[10,11,12]]
     *  Output: [1,2,3,6,9,12,11,10,7,4,5,8]
     *
     *  Input: matrix = [[1,2,3,4,5,6,7,8,9,10]]
     *  Output: [1,2,3,4,5,6,7,8,9,10]
     *
     *  Input: matrix = [[1,2,3,4,5,6,7,8,9]]
     *  Output: [1,2,3,4,5,6,7,8,9]
     *
     *  Input: matrix = [[1],[2],[3],[4],[5],[6],[7],[8],[9],[10]]
     *  Output: [1,2,3,4,5,6,7,8,9,10]
     *
     *  Input: matrix = [[1],[2],[3],[4],[5],[6],[7],[8],[9]]
     *  Output: [1,2,3,4,5,6,7,8,9]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: matrix = [";
        for (long unsigned int j = 0; j < testData[i].matrix.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].matrix[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].matrix[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.spiralOrder(testData[i].matrix);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
