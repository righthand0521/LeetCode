#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    void rotate(vector<vector<int>>& matrix) {
        int matrixSize = matrix.size();

        for (int i = 0; i < matrixSize; ++i) {
            int matrixColSize = matrix[i].size();
            for (int j = 0; j < (matrixColSize / 2); ++j) {
                swap(matrix[i][j], matrix[i][matrixColSize - j - 1]);
            }
        }

        for (int i = 0; i < matrixSize; ++i) {
            int matrixColSize = matrix[i].size();
            for (int j = 0; j < matrixColSize - i; ++j) {
                swap(matrix[i][j], matrix[matrixColSize - 1 - j][matrixSize - 1 - i]);
            }
        }
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> matrix;
    };
    vector<subject> testData{{{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}},
                             {{{5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
     *  Output: [[7,4,1],[8,5,2],[9,6,3]]
     *
     *  Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
     *  Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
     */

    Solution cSolution;
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

        cSolution.rotate(testData[i].matrix);
        cout << "Output: [";
        for (long unsigned int j = 0; j < testData[i].matrix.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].matrix[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].matrix[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
