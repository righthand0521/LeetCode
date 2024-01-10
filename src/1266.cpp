#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minTimeToVisitAllPoints(vector<vector<int>>& points) {
        int retVal = 0;

        int pointsSize = points.size();
        for (int i = 1; i < pointsSize; ++i) {
            int diffX = abs(points[i - 1][0] - points[i][0]);
            int diffY = abs(points[i - 1][1] - points[i][1]);
            retVal += max(diffX, diffY);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> points;
    };
    vector<subject> testData{{{{1, 1}, {3, 4}, {-1, 0}}}, {{{3, 2}, {-2, 2}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: points = [[1,1],[3,4],[-1,0]]
     *  Output: 7
     *
     *  Input: points = [[3,2],[-2,2]]
     *  Output: 5
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

        answer = cSolution.minTimeToVisitAllPoints(testData[i].points);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
