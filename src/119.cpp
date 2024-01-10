#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> getRow(int rowIndex) {
        vector<int> retVal(rowIndex + 1, 1);

        for (int row = 0; row < rowIndex; ++row) {
            for (int col = row; col > 0; --col) {
                retVal[col] += retVal[col - 1];
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int rowIndex;
    };
    vector<subject> testData{{3}, {0}, {1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: rowIndex = 3
     *  Output: [1,3,3,1]
     *
     *  Input: rowIndex = 0
     *  Output: [1]
     *
     *  Input: rowIndex = 1
     *  Output: [1,1]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: rowIndex = " << testData[i].rowIndex << "\n";

        answer = cSolution.getRow(testData[i].rowIndex);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
