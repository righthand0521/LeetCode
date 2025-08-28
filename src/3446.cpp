#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
        vector<vector<int>> retVal = grid;

        int gridSize = grid.size();

        for (int i = 0; i < gridSize; i++) {
            vector<int> tmp;
            for (int j = 0; i + j < gridSize; j++) {
                tmp.emplace_back(grid[i + j][j]);
            }
            sort(tmp.begin(), tmp.end(), greater<int>());

            for (int j = 0; i + j < gridSize; j++) {
                retVal[i + j][j] = tmp[j];
            }
        }

        for (int j = 1; j < gridSize; j++) {
            vector<int> tmp;
            for (int i = 0; j + i < gridSize; i++) {
                tmp.emplace_back(retVal[i][j + i]);
            }

            sort(tmp.begin(), tmp.end());
            for (int i = 0; j + i < gridSize; i++) {
                retVal[i][j + i] = tmp[i];
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
    };
    vector<subject> testData{{{{1, 7, 3}, {9, 8, 2}, {4, 5, 6}}}, {{{0, 1}, {1, 2}}}, {{{1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[1,7,3],[9,8,2],[4,5,6]]
     *  Output: [[8,2,3],[9,6,7],[4,5,1]]
     *
     *  Input: grid = [[0,1],[1,2]]
     *  Output: [[2,1],[1,0]]
     *
     *  Input: grid = [[1]]
     *  Output: [[1]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
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

        answer = cSolution.sortMatrix(testData[i].grid);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < answer[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << answer[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
