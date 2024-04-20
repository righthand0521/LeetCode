#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> findFarmland(vector<vector<int>>& land) {
        vector<vector<int>> retVal;

        int landSize = land.size();
        int landColSize = land[0].size();
        for (int row = 0; row < landSize; ++row) {
            for (int col = 0; col < landColSize; ++col) {
                if (land[row][col] == 0) {
                    continue;
                }

                int x = row;
                int y = col;
                for (x = row; x < landSize; ++x) {
                    if (land[x][col] == 0) {
                        break;
                    }

                    for (y = col; y < landColSize; ++y) {
                        if (land[x][y] == 0) {
                            break;
                        }
                        land[x][y] = 0;
                    }
                }

                retVal.push_back({row, col, x - 1, y - 1});
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> land;
    };
    vector<subject> testData{
        {{{1, 0, 0}, {0, 1, 1}, {0, 1, 1}}}, {{{1, 1}, {1, 1}}}, {{{0}}}, {{{1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: land = [[1,0,0],[0,1,1],[0,1,1]]
     *  Output: [[0,0,0,0],[1,1,2,2]]
     *
     *  Input: land = [[1,1],[1,1]]
     *  Output: [[0,0,1,1]]
     *
     *  Input: land = [[0]]
     *  Output: []
     *
     *  Input: land = [[1,0,0,1,0,1,1,0,0,1,0,1,1]]
     *  Output: [[0,0,0,0],[0,3,0,3],[0,5,0,6],[0,9,0,9],[0,11,0,12]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: land = [";
        for (long unsigned int j = 0; j < testData[i].land.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].land[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].land[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.findFarmland(testData[i].land);
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
