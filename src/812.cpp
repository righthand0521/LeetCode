#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    double triangleArea(int x1, int y1, int x2, int y2, int x3, int y3) {
        double retVal = 0.5 * abs((x1 * y2) + (x2 * y3) + (x3 * y1) - (x1 * y3) - (x2 * y1) - (x3 * y2));

        return retVal;
    }

   public:
    double largestTriangleArea(vector<vector<int>>& points) {
        double retVal = 0;

        int pointsSize = points.size();
        for (int i = 0; i < pointsSize; i++) {
            for (int j = i + 1; j < pointsSize; j++) {
                for (int k = j + 1; k < pointsSize; k++) {
                    retVal = max(retVal, triangleArea(points[i][0], points[i][1], points[j][0], points[j][1],
                                                      points[k][0], points[k][1]));
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
    vector<subject> testData{{{{0, 0}, {0, 1}, {1, 0}, {0, 2}, {2, 0}}}, {{{1, 0}, {0, 0}, {0, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: points = [[0,0],[0,1],[1,0],[0,2],[2,0]]
     *  Output: 2.00000
     *
     *  Input: points = [[1,0],[0,0],[0,1]]
     *  Output: 0.50000
     */

    Solution cSolution;
    double answer = 0;
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

        answer = cSolution.largestTriangleArea(testData[i].points);
        cout.setf(ios::fixed);
        cout.precision(5);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
