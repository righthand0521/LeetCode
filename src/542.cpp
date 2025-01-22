#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        vector<vector<int>> retVal;

        int matSize = mat.size();
        int matColSize = mat[0].size();

        int maxValue = (int)(1e5);  // 1 <= m, n <= 10^4, 1 <= m * n <= 10^4
        retVal.resize(matSize, vector<int>(matColSize, maxValue));
        for (int i = 0; i < matSize; ++i) {
            for (int j = 0; j < matColSize; ++j) {
                if (mat[i][j] == 0) {
                    retVal[i][j] = 0;
                }
            }
        }
        for (int i = 0; i < matSize; ++i) {
            for (int j = 0; j < matColSize; ++j) {
                if (i - 1 >= 0) {
                    retVal[i][j] = min(retVal[i][j], retVal[i - 1][j] + 1);
                }
                if (j - 1 >= 0) {
                    retVal[i][j] = min(retVal[i][j], retVal[i][j - 1] + 1);
                }
            }
        }
        for (int i = matSize - 1; i >= 0; --i) {
            for (int j = matColSize - 1; j >= 0; --j) {
                if (i + 1 < matSize) {
                    retVal[i][j] = min(retVal[i][j], retVal[i + 1][j] + 1);
                }
                if (j + 1 < matColSize) {
                    retVal[i][j] = min(retVal[i][j], retVal[i][j + 1] + 1);
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
    vector<subject> testData{{{{0, 0, 0}, {0, 1, 0}, {0, 0, 0}}}, {{{0, 0, 0}, {0, 1, 0}, {1, 1, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: mat = [[0,0,0],[0,1,0],[0,0,0]]
     *  Output: [[0,0,0],[0,1,0],[0,0,0]]
     *
     *  Input: mat = [[0,0,0],[0,1,0],[1,1,1]]
     *  Output: [[0,0,0],[0,1,0],[1,2,1]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
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

        answer = cSolution.updateMatrix(testData[i].mat);
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
