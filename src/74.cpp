#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define BINARY_SEARCH (0)
   public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        bool retVal = false;

        // m == matrix.length, n == matrix[i].length, 1 <= m, n <= 100
        int matrixRowSize = matrix.size();
        int matrixColSize = matrix[0].size();

#if (BINARY_SEARCH)
        int left = 0;
        int right = matrixRowSize * matrixColSize - 1;
        while (left <= right) {
            int middle = left + (right - left) / 2;

            int middleValue = matrix[middle / matrixColSize][middle % matrixColSize];
            if (middleValue == target) {
                retVal = true;
                break;
            } else if (middleValue < target) {
                left = middle + 1;
            } else if (middleValue > target) {
                right = middle - 1;
            }
        }
#else
        /* Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3; Output: true
         *      0  1  2   3  |  0  1  2   3  |  0  1   2  3
         *  0   1  3  5  [7] |  1  3 [5]  7  |  1 [3]  5  7
         *  1  10 11 16  20  | 10 11 16  20  | 10 11  16 20
         *  2  23 30 34  60  | 23 30 34  60  | 23 30  34 60
         *
         * Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13; Output: false
         *      0  1  2   3  |  0  1  2   3  |  0   1   2   3 |  0   1   2  3 |  0   1   2  3 |   0   1  2  3
         *  0   1  3  5  [7] |  1  3  5   7  |  1   3   5   7 |  1   3   5  7 |  1   3   5  7 |   1   3  5  7
         *  1  10 11 16  20  | 10 11 16 [20] | 10  11 [16] 20 | 10 [11] 16 20 | 10  11  16 20 |  10  11 16 20
         *  2  23 30 34  60  | 23 30 34  60  | 23  30  34  60 | 23  30  34 60 | 23 [30] 34 60 | [23] 30 34 60
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
#endif

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> matrix;
        int target;
    };
    vector<subject> testData{{{{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}}, 3},
                             {{{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}}, 13},
                             {{{1}}, 0}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
     *  Output: true
     *
     *  Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
     *  Output: false
     *
     *  Input: matrix = [[1]], target = 0
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
