#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> allCellsDistOrder(int rows, int cols, int rCenter, int cCenter) {
        vector<vector<int>> retVal;

        for (int x = 0; x < rows; ++x) {
            for (int y = 0; y < cols; ++y) {
                retVal.push_back({x, y});
            }
        }
        sort(retVal.begin(), retVal.end(), [=](vector<int>& a, vector<int>& b) {
            return abs(a[0] - rCenter) + abs(a[1] - cCenter) < abs(b[0] - rCenter) + abs(b[1] - cCenter);
        });

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int rows;
        int cols;
        int rCenter;
        int cCenter;
    };
    vector<subject> testData{{1, 2, 0, 0}, {2, 2, 0, 1}, {2, 3, 1, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: rows = 1, cols = 2, rCenter = 0, cCenter = 0
     *  Output: [[0,0],[0,1]]
     *
     *  Input: rows = 2, cols = 2, rCenter = 0, cCenter = 1
     *  Output: [[0,1],[0,0],[1,1],[1,0]]
     *
     *  Input: rows = 2, cols = 3, rCenter = 1, cCenter = 2
     *  Output: [[1,2],[0,2],[1,1],[0,1],[1,0],[0,0]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: rows = " << testData[i].rows << ", cols = " << testData[i].cols
             << ", rCenter = " << testData[i].rCenter << ", cCenter = " << testData[i].cCenter << "\n";

        answer =
            cSolution.allCellsDistOrder(testData[i].rows, testData[i].cols, testData[i].rCenter, testData[i].cCenter);
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
