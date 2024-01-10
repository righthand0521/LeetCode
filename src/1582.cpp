#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int numSpecial(vector<vector<int>>& mat) {
        int retVal = 0;

        // m == mat.length, n == mat[i].length, 1 <= m, n <= 100.
        int rowSize = mat.size();
        int colSize = mat[0].size();

        vector<int> rowSum(rowSize, 0);
        vector<int> colSum(colSize, 0);
        for (int i = 0; i < rowSize; ++i) {
            for (int j = 0; j < colSize; ++j) {
                // mat[i][j] is either 0 or 1.
                rowSum[i] += mat[i][j];
                colSum[j] += mat[i][j];
            }
        }

        for (int i = 0; i < rowSize; ++i) {
            for (int j = 0; j < colSize; ++j) {
                if (mat[i][j] != 1) {
                    continue;
                }
                if ((rowSum[i] == 1) && (colSum[j] == 1)) {
                    retVal += 1;
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> mat;
    };
    vector<subject> testData{{{{1, 0, 0}, {0, 0, 1}, {1, 0, 0}}}, {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: mat = [[1,0,0],[0,0,1],[1,0,0]]
     *  Output: 1
     *
     *  Input: mat = [[1,0,0],[0,1,0],[0,0,1]]
     *  Output: 3
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: mat = [";
        for (long unsigned int j = 0; j < testData[i].mat.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].mat[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].mat[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.numSpecial(testData[i].mat);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
