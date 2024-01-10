#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int equalPairs(vector<vector<int>>& grid) {
        int retVal = 0;

        int gridSize = grid.size();
        for (int row = 0; row < gridSize; ++row) {
            for (int col = 0; col < gridSize; ++col) {
                bool match = true;

                for (int idx = 0; idx < gridSize; ++idx) {
                    if (grid[row][idx] != grid[idx][col]) {
                        match = false;
                        break;
                    }
                }

                if (match == true) {
                    ++retVal;
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
    };
    vector<subject> testData{{{{3, 2, 1}, {1, 7, 6}, {2, 7, 7}}},
                             {{{3, 1, 2, 2}, {1, 4, 4, 5}, {2, 4, 2, 2}, {2, 4, 2, 2}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[3,2,1],[1,7,6],[2,7,7]]
     *  Output: 1
     *
     *  Input: grid = [[3,1,2,2],[1,4,4,5],[2,4,2,2],[2,4,2,2]]
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: grid = [";
        for (long unsigned int j = 0; j < testData[i].grid.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].grid[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].grid[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.equalPairs(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
