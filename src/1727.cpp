#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int largestSubmatrix(vector<vector<int>>& matrix) {
        int retVal = 0;

        int rowSize = matrix.size();
        int colSize = matrix[0].size();

        for (int x = 1; x < rowSize; ++x) {
            for (int y = 0; y < colSize; ++y) {
                if (matrix[x][y] == 1) {
                    matrix[x][y] += matrix[x - 1][y];
                }
            }
        }

        for (int x = 0; x < rowSize; ++x) {
            sort(matrix[x].begin(), matrix[x].end(), greater());
            for (int y = 0; y < colSize; ++y) {
                retVal = max(retVal, matrix[x][y] * (y + 1));
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> matrix;
    };
    vector<subject> testData{{{{0, 0, 1}, {1, 1, 1}, {1, 0, 1}}}, {{{1, 0, 1, 0, 1}}}, {{{1, 1, 0}, {1, 0, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: matrix = [[0,0,1],[1,1,1],[1,0,1]]
     *  Output: 4
     *
     *  Input: matrix = [[1,0,1,0,1]]
     *  Output: 3
     *
     *  Input: matrix = [[1,1,0],[1,0,1]]
     *  Output: 2
     */

    Solution cSolution;
    int answer;
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

        answer = cSolution.largestSubmatrix(testData[i].matrix);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
