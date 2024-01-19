#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    void setZeroes(vector<vector<int>>& matrix) {
        int matrixRow = matrix.size();
        int matrixCol = matrix[0].size();

        vector<int> rowHashTable(matrixRow, 0);
        vector<int> colHashTable(matrixCol, 0);
        for (int i = 0; i < matrixRow; ++i) {
            for (int j = 0; j < matrixCol; ++j) {
                if (matrix[i][j] == 0) {
                    rowHashTable[i] = 1;
                    colHashTable[j] = 1;
                }
            }
        }

        for (int i = 0; i < matrixRow; ++i) {
            for (int j = 0; j < matrixCol; ++j) {
                if ((rowHashTable[i] == 1) || (colHashTable[j] == 1)) {
                    matrix[i][j] = 0;
                }
            }
        }
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> matrix;
    };
    vector<subject> testData{{{{1, 1, 1}, {1, 0, 1}, {1, 1, 1}}}, {{{0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1, 5}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
     *  Output: [[1,0,1],[0,0,0],[1,0,1]]
     *
     *  Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
     *  Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
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

        cSolution.setZeroes(testData[i].matrix);
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
