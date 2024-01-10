#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> retVal(numRows);

        for (int row = 0; row < numRows; ++row) {
            for (int col = 0; col <= row; ++col) {
                if ((col == 0) || (col == row)) {
                    retVal[row].push_back(1);
                } else {
                    retVal[row].push_back(retVal[row - 1][col - 1] + retVal[row - 1][col]);
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int numRows;
    };
    vector<subject> testData{{5}, {1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: numRows = 5
     *  Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
     *
     *  Input: numRows = 1
     *  Output: [[1]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: numRows = " << testData[i].numRows << "\n";

        answer = cSolution.generate(testData[i].numRows);
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
