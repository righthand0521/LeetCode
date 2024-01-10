#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int nearestValidPoint(int x, int y, vector<vector<int>>& points) {
        int retVal = -1;

        int distanceMin = INT_MAX;
        int distanceRow;
        int distanceCol;
        for (int i = (points.size() - 1); i >= 0; --i) {
            distanceRow = abs(x - points[i][0]);
            distanceCol = abs(y - points[i][1]);
            if ((distanceRow != 0) && (distanceCol != 0)) {
                continue;
            } else if (distanceMin >= max(distanceRow, distanceCol)) {
                distanceMin = max(distanceRow, distanceCol);
                retVal = i;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int x;
        int y;
        vector<vector<int>> points;
    };
    vector<subject> testData{{3, 4, {{1, 2}, {3, 1}, {2, 4}, {2, 3}, {4, 4}}}, {3, 4, {{3, 4}}}, {3, 4, {{2, 3}}}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: x = " << testData[i].x << ", y = " << testData[i].y << ", points = [";
        for (long unsigned int j = 0; j < testData[i].points.size(); ++j) {
            cout << ((j == 0) ? "[" : ",[");
            for (long unsigned int k = 0; k < testData[i].points[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].points[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.nearestValidPoint(testData[i].x, testData[i].y, testData[i].points);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
