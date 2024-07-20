#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> restoreMatrix(vector<int>& rowSum, vector<int>& colSum) {
        vector<vector<int>> retVal;

        int rowSumSize = rowSum.size();
        int colSumSize = colSum.size();
        retVal.resize(rowSumSize, vector<int>(colSumSize, 0));

        /* rowSum = [5,7,10], colSum = [8,6,8]
         *       8 6 8       3 6 8       0 6 8       0 2 8      0 0 8      0 0 0
         *   --+-------  --+-------  --+-------  --+-------  --+-------  --+-------
         *   5 | 0 0 0   0 | 5 0 0   0 | 5 0 0   0 | 5 0 0   0 | 5 0 0   0 | 5 0 0
         *   7 | 0 0 0   7 | 0 0 0   4 | 3 0 0   0 | 3 4 0   0 | 3 4 0   0 | 3 4 0
         *  10 | 0 0 0  10 | 0 0 0  10 | 0 0 0  10 | 0 0 0   8 | 0 2 0   0 | 0 2 8
         */
        int x = 0;
        int y = 0;
        while ((x < rowSumSize) && (y < colSumSize)) {
            retVal[x][y] = min(rowSum[x], colSum[y]);
            rowSum[x] -= retVal[x][y];
            colSum[y] -= retVal[x][y];
            if (rowSum[x] == 0) {
                x++;
            } else {
                y++;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> rowSum;
        vector<int> colSum;
    };
    vector<subject> testData{{{3, 8}, {4, 7}}, {{5, 7, 10}, {8, 6, 8}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: rowSum = [3,8], colSum = [4,7]
     *  Output: [[3,0], [1,7]]
     *
     *  Input: rowSum = [5,7,10], colSum = [8,6,8]
     *  Output: [[0,5,0], [6,1,0], [2,0,8]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: rowSum = [";
        for (long unsigned int j = 0; j < testData[i].rowSum.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].rowSum[j];
        }
        cout << "], colSum = [";
        for (long unsigned int j = 0; j < testData[i].colSum.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].colSum[j];
        }
        cout << "]\n";

        answer = cSolution.restoreMatrix(testData[i].rowSum, testData[i].colSum);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < answer[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << answer[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
