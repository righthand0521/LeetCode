#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        bool retVal = false;

        // m == matrix.length, n == matrix[i].length, 1 <= n, m <= 300
        int matrixRowSize = matrix.size();
        int matrixColSize = matrix[0].size();

        /* Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
         *      0  1  2  3  4   |  0   1   2    3  4  |  0   1   2  3  4
         *  0   1  4  7 11 [15] |  1  [4] [7] [11] 15 |  1   4   7 11 15
         *  1   2  5  8 12  19  |  2   5   8   12  19 |  2  [5]  8 12 19
         *  2   3  6  9 16  22  |  3   6   9   16  22 |  3   6   9 16 22
         *  3  10 13 14 17  24  | 10  13  14   17  24 | 10  13  14 17 24
         *  4  18 21 23 26  30  | 18  21  23   26  30 | 18  21  23 26 30
         *
         * Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
         *      0  1  2  3  4   |  0  1  2  3   4  |  0  1  2   3   4 |  0   1    2   3  4 |   0   1  2  3  4
         *  0   1  4  7 11 [15] |  1  4  7 11  15  |  1  4  7  11  15 |  1   4    7  11 15 |   1   4  7 11 15
         *  1   2  5  8 12  19  |  2  5  8 12 [19] |  2  5  8  12  19 |  2   5    8  12 19 |   2   5  8 12 19
         *  2   3  6  9 16  22  |  3  6  9 16 [22] |  3  6  9 [16] 22 |  3   6    9  16 22 |   3   6  9 16 22
         *  3  10 13 14 17  24  | 10 13 14 17  24  | 10 13 14 [17] 24 | 10  13   14  17 24 |  10  13 14 17 24
         *  4  18 21 23 26  30  | 18 21 23 26  30  | 18 21 23 [26] 30 | 18 [21] [23] 26 30 | [18] 21 23 26 30
         */
        int row = 0;
        int col = matrixColSize - 1;
        while ((row < matrixRowSize) && (col >= 0)) {
            int value = matrix[row][col];
            if (value == target) {
                retVal = true;
                break;
            } else if (value < target) {
                row++;
            } else if (value > target) {
                col--;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> matrix;
        int target;
    };
    vector<subject> testData{
        {{{1, 4, 7, 11, 15}, {2, 5, 8, 12, 19}, {3, 6, 9, 16, 22}, {10, 13, 14, 17, 24}, {18, 21, 23, 26, 30}}, 5},
        {{{1, 4, 7, 11, 15}, {2, 5, 8, 12, 19}, {3, 6, 9, 16, 22}, {10, 13, 14, 17, 24}, {18, 21, 23, 26, 30}}, 20}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
     *  Output: true
     *
     *  Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: matrix = [";
        for (long unsigned int j = 0; j < testData[i].matrix.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].matrix[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].matrix[j][k];
            }
            cout << "]";
        }
        cout << "], target = " << testData[i].target << "\n";

        answer = cSolution.searchMatrix(testData[i].matrix, testData[i].target);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
