#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int findChampion(vector<vector<int>>& grid) {
        int retVal = 0;

        int gridSize = grid.size();
        for (int x = 0; x < gridSize; ++x) {
            int stronger = 0;
            int gridColSize = grid[x].size();
            for (int y = 0; y < gridColSize; ++y) {
                stronger += grid[x][y];
            }

            if (stronger == gridSize - 1) {
                retVal = x;
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
    };
    vector<subject> testData{{{{0, 1}, {0, 0}}}, {{{0, 0, 1}, {1, 0, 1}, {0, 0, 0}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[0,1],[0,0]]
     *  Output: 0
     *
     *  Input: grid = [[0,0,1],[1,0,1],[0,0,0]]
     *  Output: 1
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

        answer = cSolution.findChampion(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
