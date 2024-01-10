#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> transpose(vector<vector<int>>& matrix) {
        vector<vector<int>> retVal;

        int rowSize = matrix[0].size();
        int colSize = matrix.size();
        retVal.resize(rowSize, vector<int>(colSize, 0));
        for (int i = 0; i < rowSize; ++i) {
            for (int j = 0; j < colSize; ++j) {
                retVal[i][j] = matrix[j][i];
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> matrix;
    };
    vector<subject> testData{{{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}}, {{{1, 2, 3}, {4, 5, 6}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
     *  Output: [[1,4,7],[2,5,8],[3,6,9]]
     *
     *  Input: matrix = [[1,2,3],[4,5,6]]
     *  Output: [[1,4],[2,5],[3,6]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
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

        answer = cSolution.transpose(testData[i].matrix);
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
