#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int getRect(const vector<vector<int>>& P, int x1, int y1, int x2, int y2) {
        int retVal = P[x2][y2] - P[x1 - 1][y2] - P[x2][y1 - 1] + P[x1 - 1][y1 - 1];

        return retVal;
    }

   public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        int retVal = 0;

        int rowSize = mat.size();
        int colSize = mat[0].size();

        vector<vector<int>> P(rowSize + 1, vector<int>(colSize + 1));
        for (int i = 1; i <= rowSize; ++i) {
            for (int j = 1; j <= colSize; ++j) {
                P[i][j] = P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1] + mat[i - 1][j - 1];
            }
        }

        int r = min(rowSize, colSize);
        for (int i = 1; i <= rowSize; ++i) {
            for (int j = 1; j <= colSize; ++j) {
                for (int c = retVal + 1; c <= r; ++c) {
                    if (i + c - 1 > rowSize) {
                        break;
                    } else if (j + c - 1 > colSize) {
                        break;
                    } else if (getRect(P, i, j, i + c - 1, j + c - 1) > threshold) {
                        break;
                    }

                    ++retVal;
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> mat;
        int threshold;
    };
    vector<subject> testData{
        {{{1, 1, 3, 2, 4, 3, 2}, {1, 1, 3, 2, 4, 3, 2}, {1, 1, 3, 2, 4, 3, 2}}, 4},
        {{{2, 2, 2, 2, 2}, {2, 2, 2, 2, 2}, {2, 2, 2, 2, 2}, {2, 2, 2, 2, 2}, {2, 2, 2, 2, 2}}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: mat = [[1,1,3,2,4,3,2],[1,1,3,2,4,3,2],[1,1,3,2,4,3,2]], threshold = 4
     *  Output: 2
     *
     *  Input: mat = [[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2]], threshold = 1
     *  Output: 0
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
        cout << "], threshold = " << testData[i].threshold << "\n";

        answer = cSolution.maxSideLength(testData[i].mat, testData[i].threshold);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
