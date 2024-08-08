#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart) {
        vector<vector<int>> retVal;

        // East, South, West, North
        vector<vector<int>> directions{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        int idx = 0;
        int retValSize = retVal.size();
        for (int step = 1; retValSize < rows * cols;) {
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < step; ++j) {
                    if ((rStart >= 0) && (rStart < rows) && (cStart >= 0) && (cStart < cols)) {
                        retVal.push_back({rStart, cStart});
                    }
                    rStart += directions[idx][0];
                    cStart += directions[idx][1];
                }
                idx = (idx + 1) % 4;
            }
            ++step;
            retValSize = retVal.size();
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int rows;
        int cols;
        int rStart;
        int cStart;
    };
    vector<subject> testData{{1, 4, 0, 0}, {5, 6, 1, 4}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: rows = 1, cols = 4, rStart = 0, cStart = 0
     *  Output: [[0,0],[0,1],[0,2],[0,3]]
     *
     *  Input: rows = 5, cols = 6, rStart = 1, cStart = 4
     *  Output: [[1,4],[1,5],[2,5],[2,4],[2,3],[1,3],[0,3],[0,4],[0,5],[3,5],[3,4],[3,3],[3,2],[2,2],[1,2],[0,2],
     *  [4,5],[4,4],[4,3],[4,2],[4,1],[3,1],[2,1],[1,1],[0,1],[4,0],[3,0],[2,0],[1,0],[0,0]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: rows = " << testData[i].rows << ", cols = " << testData[i].cols;
        cout << ", rStart = " << testData[i].rStart << ", cStart = " << testData[i].cStart << "\n";

        answer = cSolution.spiralMatrixIII(testData[i].rows, testData[i].cols, testData[i].rStart, testData[i].cStart);
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
