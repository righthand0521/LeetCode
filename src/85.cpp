#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int retVal = 0;

        int rowSize = matrix.size();
        if (rowSize == 0) {
            return retVal;
        }
        int colSize = matrix[0].size();

        vector<vector<int>> left(rowSize, vector<int>(colSize, 0));
        for (int i = 0; i < rowSize; i++) {
            for (int j = 0; j < colSize; j++) {
                if (matrix[i][j] == '1') {
                    left[i][j] = (j == 0 ? 0 : left[i][j - 1]) + 1;
                }
            }
        }

        for (int j = 0; j < colSize; j++) {
            vector<int> up(rowSize, 0);
            stack<int> upMmonotonicStack;
            for (int i = 0; i < rowSize; i++) {
                while ((upMmonotonicStack.empty() == false) && (left[upMmonotonicStack.top()][j] >= left[i][j])) {
                    upMmonotonicStack.pop();
                }
                up[i] = upMmonotonicStack.empty() ? -1 : upMmonotonicStack.top();
                upMmonotonicStack.push(i);
            }

            vector<int> down(rowSize, 0);
            stack<int> downMmonotonicStack;
            for (int i = rowSize - 1; i >= 0; i--) {
                while ((downMmonotonicStack.empty() == false) && (left[downMmonotonicStack.top()][j] >= left[i][j])) {
                    downMmonotonicStack.pop();
                }
                down[i] = downMmonotonicStack.empty() ? rowSize : downMmonotonicStack.top();
                downMmonotonicStack.push(i);
            }

            for (int i = 0; i < rowSize; i++) {
                int height = down[i] - up[i] - 1;
                int area = height * left[i][j];
                retVal = max(retVal, area);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<char>> matrix;
    };
    vector<subject> testData{
        {{{'1', '0', '1', '0', '0'}, {'1', '0', '1', '1', '1'}, {'1', '1', '1', '1', '1'}, {'1', '0', '0', '1', '0'}}},
        {{{'0'}}},
        {{{'1'}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
     *  Output: 6
     *
     *  Input: matrix = [["0"]]
     *  Output: 0
     *
     *  Input: matrix = [["1"]]
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: matrix = [";
        for (long unsigned int j = 0; j < testData[i].matrix.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].matrix[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << "\"" << testData[i].matrix[j][k] << "\"";
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.maximalRectangle(testData[i].matrix);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
