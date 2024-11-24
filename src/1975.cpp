#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    long long maxMatrixSum(vector<vector<int>>& matrix) {
        long long retVal = 0;

        int minAbsVal = numeric_limits<int>::max();
        int negativeCount = 0;
        for (auto& rows : matrix) {
            for (int cell : rows) {
                retVal += abs(cell);
                if (cell < 0) {
                    negativeCount++;
                }
                minAbsVal = min(minAbsVal, abs(cell));
            }
        }

        if (negativeCount % 2 != 0) {
            retVal -= (2 * minAbsVal);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> matrix;
    };
    vector<subject> testData{{{{1, -1}, {-1, 1}}}, {{{1, 2, 3}, {-1, -2, -3}, {1, 2, 3}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: matrix = [[1,-1],[-1,1]]
     *  Output: 4
     *
     *  Input: matrix = [[1,2,3],[-1,-2,-3],[1,2,3]]
     *  Output: 16
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: matrix = [";
        for (long unsigned int j = 0; j < testData[i].matrix.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].matrix[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].matrix[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.maxMatrixSum(testData[i].matrix);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
