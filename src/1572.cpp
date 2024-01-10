#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int diagonalSum(vector<vector<int>>& mat) {
        int retVal = 0;

        int row = mat.size();
        for (int i = 0; i < row; ++i) {
            retVal += mat[i][i];
            retVal += mat[i][mat[i].size() - 1 - i];
        }
        if (row % 2 == 1) {
            retVal -= mat[row / 2][row / 2];
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> mat;
    };
    vector<subject> testData{
        {{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}}, {{{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}}}, {{{5}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: mat = [[1,2,3],
                      [4,5,6],
                      [7,8,9]]
     *  Output: 25
     *
     *  Input: mat = [[1,1,1,1],
                      [1,1,1,1],
                      [1,1,1,1],
                      [1,1,1,1]]
     *  Output: 8
     *
     *  Input: mat = [[5]]
     *  Output: 5
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: mat = [";
        for (long unsigned int j = 0; j < testData[i].mat.size(); ++j) {
            cout << ((j == 0) ? "" : ",\n              ") << "[";
            for (long unsigned int k = 0; k < testData[i].mat[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].mat[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.diagonalSum(testData[i].mat);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
