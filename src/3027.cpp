#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    int numberOfPairs(vector<vector<int>>& points) {
        int retVal = 0;

        sort(points.begin(), points.end(), [](const vector<int>& x, const vector<int>& y) {
            // ascending order
            if (x[0] == y[0]) {
                return (x[1] > y[1]);
            }
            return (x[0] < y[0]);
        });

        int pointsSize = points.size();
        for (int i = 0; i < pointsSize - 1; i++) {
            const auto& pointA = points[i];
            int xMin = pointA[0] - 1;
            int xMax = numeric_limits<int>::max();
            int yMin = numeric_limits<int>::min();
            int yMax = pointA[1] + 1;

            for (int j = i + 1; j < pointsSize; j++) {
                const auto& pointB = points[j];
                if ((pointB[0] > xMin) && (pointB[0] < xMax) && (pointB[1] > yMin) && (pointB[1] < yMax)) {
                    retVal++;
                    xMin = pointB[0];
                    yMin = pointB[1];
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> points;
    };
    vector<subject> testData{{{{1, 1}, {2, 2}, {3, 3}}}, {{{6, 2}, {4, 4}, {2, 6}}}, {{{3, 1}, {1, 3}, {1, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: points = [[1,1],[2,2],[3,3]]
     *  Output: 0
     *
     *  Input: points = [[6,2],[4,4],[2,6]]
     *  Output: 2
     *
     *  Input: points = [[3,1],[1,3],[1,1]]
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: points = [";
        for (long unsigned int j = 0; j < testData[i].points.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].points[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].points[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.numberOfPairs(testData[i].points);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
