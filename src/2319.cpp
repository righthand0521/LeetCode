#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool checkXMatrix(vector<vector<int>>& grid) {
        bool retVal = false;

        for (long unsigned int i = 0; i < grid.size(); ++i) {
            for (long unsigned int j = 0; j < grid[i].size(); ++j) {
                if ((j == i) || (j == grid[i].size() - 1 - i)) {
                    if (grid[i][j] == 0) {
                        return retVal;
                    }
                } else {
                    if (grid[i][j] != 0) {
                        return retVal;
                    }
                }
            }
        }
        retVal = true;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
    };
    vector<subject> testData{{{{2, 0, 0, 1}, {0, 3, 1, 0}, {0, 5, 2, 0}, {4, 0, 0, 2}}},
                             {{{5, 7, 0}, {0, 3, 1}, {0, 5, 0}}},
                             {{{5, 0, 0, 1}, {0, 4, 1, 5}, {0, 5, 2, 0}, {4, 1, 0, 2}}}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    bool answer;
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

        answer = cSolution.checkXMatrix(testData[i].grid);
        cout << "Output: " << ((answer == true) ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
