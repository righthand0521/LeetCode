#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool checkStraightLine(vector<vector<int>>& coordinates) {
        bool retVal = true;

        int coordinatesSize = coordinates.size();
        if (coordinatesSize == 2) {
            return retVal;
        }

        // https://en.wikipedia.org/wiki/Cross_product
        for (int i = 2; i < coordinatesSize; ++i) {
            int v1x = coordinates[i - 1][0] - coordinates[i - 2][0];
            int v1y = coordinates[i - 1][1] - coordinates[i - 2][1];
            int v2x = coordinates[i][0] - coordinates[i - 1][0];
            int v2y = coordinates[i][1] - coordinates[i - 1][1];
            if ((v1x * v2y) != (v1y * v2x)) {
                retVal = false;
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> coordinates;
    };
    vector<subject> testData{{{{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}}},
                             {{{1, 1}, {2, 2}, {3, 4}, {4, 5}, {5, 6}, {7, 7}}},
                             {{{1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {6, 7}}},
                             {{{2, 1}, {4, 2}, {6, 3}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: coordinates = [[1,2],[2,3],[3,4],[4,5],[5,6],[6,7]]
     *  Output: true
     *
     *  Input: coordinates = [[1,1],[2,2],[3,4],[4,5],[5,6],[7,7]]
     *  Output: false
     *
     *  Input: coordinates = [[1, 2],[1, 3],[1, 4],[1, 5],[1, 6],[6, 7]]
     *  Output: false
     *
     *  Input: coordinates = [[2, 1],[4, 2],[6, 3]]
     *  Output: true
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: coordinates = [";
        for (long unsigned int j = 0; j < testData[i].coordinates.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].coordinates[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].coordinates[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.checkStraightLine(testData[i].coordinates);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
