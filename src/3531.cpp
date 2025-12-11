#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int countCoveredBuildings(int n, vector<vector<int>>& buildings) {
        int retVal = 0;

        vector<int> maxRow(n + 1);
        vector<int> minRow(n + 1, n + 1);
        vector<int> maxCol(n + 1);
        vector<int> minCol(n + 1, n + 1);
        for (auto& building : buildings) {
            int x = building[0];
            int y = building[1];
            maxRow[y] = max(maxRow[y], x);
            minRow[y] = min(minRow[y], x);
            maxCol[x] = max(maxCol[x], y);
            minCol[x] = min(minCol[x], y);
        }

        for (auto& building : buildings) {
            int x = building[0];
            int y = building[1];
            if ((x > minRow[y]) && (x < maxRow[y]) && (y > minCol[x]) && (y < maxCol[x])) {
                retVal++;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<vector<int>> buildings;
    };
    vector<subject> testData{{3, {{1, 2}, {2, 2}, {3, 2}, {2, 1}, {2, 3}}},
                             {3, {{1, 1}, {1, 2}, {2, 1}, {2, 2}}},
                             {5, {{1, 3}, {3, 2}, {3, 3}, {3, 5}, {5, 3}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 3, buildings = [[1,2],[2,2],[3,2],[2,1],[2,3]]
     *  Output: 1
     *
     *  Input: n = 3, buildings = [[1,1],[1,2],[2,1],[2,2]]
     *  Output: 0
     *
     *  Input: n = 5, buildings = [[1,3],[3,2],[3,3],[3,5],[5,3]]
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", buildings = [";
        for (long unsigned int j = 0; j < testData[i].buildings.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].buildings[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].buildings[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.countCoveredBuildings(testData[i].n, testData[i].buildings);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
