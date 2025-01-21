#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
   public:
    long long gridGame(vector<vector<int>>& grid) {
        long long retVal = 0;

        int colSize = grid[0].size();
        long long firstRowSum = accumulate(begin(grid[0]), end(grid[0]), 0LL);
        long long secondRowSum = 0;
        long long minimumSum = numeric_limits<long long>::max();
        for (int turnIndex = 0; turnIndex < colSize; ++turnIndex) {
            firstRowSum -= grid[0][turnIndex];
            minimumSum = min(minimumSum, max(firstRowSum, secondRowSum));
            secondRowSum += grid[1][turnIndex];
        }
        retVal = minimumSum;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
    };
    vector<subject> testData{{{{2, 5, 4}, {1, 5, 1}}}, {{{3, 3, 1}, {8, 5, 2}}}, {{{1, 3, 1, 15}, {1, 3, 3, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[2,5,4],[1,5,1]]
     *  Output: 4
     *
     *  Input: grid = [[3,3,1],[8,5,2]]
     *  Output: 4
     *
     *  Input: grid = [[1,3,1,15],[1,3,3,1]]
     *  Output: 7
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: grid = [";
        for (long unsigned int j = 0; j < testData[i].grid.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].grid[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].grid[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.gridGame(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
