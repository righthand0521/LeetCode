#include <algorithm>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxPoints(vector<vector<int>>& points) {
        int retVal = 1;

        int pointsSize = points.size();
        if (pointsSize == 1) {
            return retVal;
        }

        retVal = 2;
        for (int i = 0; i < pointsSize; ++i) {
            unordered_map<double, int> hashTable;
            for (int j = 0; j < pointsSize; ++j) {
                if (i == j) {
                    continue;
                }
                int x = points[j][0] - points[i][0];
                int y = points[j][1] - points[i][1];
                hashTable[atan2(y, x)]++;
            }

            for (auto [arctangent, count] : hashTable) {
                retVal = max(retVal, count + 1);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> points;
    };
    vector<subject> testData{{{{1, 1}, {2, 2}, {3, 3}}}, {{{1, 1}, {3, 2}, {5, 3}, {4, 1}, {2, 3}, {1, 4}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: points = [[1,1],[2,2],[3,3]]
     *  Output: 3
     *
     *  Input: points = [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
     *  Output: 4
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: points = [";
        for (long unsigned int j = 0; j < testData[i].points.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].points[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].points[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.maxPoints(testData[i].points);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
