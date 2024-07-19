#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> luckyNumbers(vector<vector<int>>& matrix) {
        vector<int> retVal;

        int rowSize = matrix.size();
        for (int row = 0; row < rowSize; ++row) {
            int luckyIndex = 0;
            int luckyValue = matrix[row][luckyIndex];

            int colSize = matrix[row].size();
            for (int col = 0; col < colSize; ++col) {
                int value = matrix[row][col];
                if (value < luckyValue) {
                    luckyIndex = col;
                    luckyValue = value;
                }
            }

            for (int x = 0; x < rowSize; ++x) {
                if (matrix[x][luckyIndex] > luckyValue) {
                    luckyIndex = -1;
                    break;
                }
            }

            if (luckyIndex != -1) {
                retVal.emplace_back(luckyValue);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> matrix;
    };
    vector<subject> testData{{{{3, 7, 8}, {9, 11, 13}, {15, 16, 17}}},
                             {{{1, 10, 4, 2}, {9, 3, 8, 7}, {15, 16, 17, 12}}},
                             {{{7, 8}, {1, 2}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: matrix = [[3,7,8],[9,11,13],[15,16,17]]
     *  Output: [15]
     *
     *  Input: matrix = [[1,10,4,2],[9,3,8,7],[15,16,17,12]]
     *  Output: [12]
     *
     *  Input: matrix = [[7,8],[1,2]]
     *  Output: [7]
     */

    Solution cSolution;
    vector<int> answer;
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

        answer = cSolution.luckyNumbers(testData[i].matrix);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
