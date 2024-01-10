#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        bool retVal = false;

        for (long unsigned int i = 1; i < matrix.size(); ++i) {
            for (long unsigned int j = 1; j < matrix[i].size(); ++j) {
                if (matrix[i - 1][j - 1] != matrix[i][j]) {
                    return retVal;
                }
            }
        }
        retVal = true;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> matrix;
    };
    vector<subject> testData{{{{1, 2, 3, 4}, {5, 1, 2, 3}, {9, 5, 1, 2}}}, {{{-1}}}, {{{1, 2}, {2, 2}}}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    bool answer = false;
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

        answer = cSolution.isToeplitzMatrix(testData[i].matrix);
        cout << "Output: " << ((answer == true) ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
