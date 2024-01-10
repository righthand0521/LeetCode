#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxWidthOfVerticalArea(vector<vector<int>>& points) {
        int retVal = 0;

        sort(points.begin(), points.end(), [&](const vector<int>& x, const vector<int>& y) {
            // ascending order
            if (x[0] == y[0]) {
                return (x[1] < y[1]);
            }
            return (x[0] < y[0]);
        });

        int pointsSize = points.size();
        for (int i = 1; i < pointsSize; ++i) {
            retVal = max(retVal, (points[i][0] - points[i - 1][0]));
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> points;
    };
    vector<subject> testData{{{{8, 7}, {9, 9}, {7, 4}, {9, 7}}}, {{{3, 1}, {9, 0}, {1, 0}, {5, 3}, {8, 8}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: points = [[8,7],[9,9],[7,4],[9,7]]
     *  Output: 1
     *
     *  Input: points = [[3,1],[9,0],[1,0],[1,4],[5,3],[8,8]]
     *  Output: 3
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

        answer = cSolution.maxWidthOfVerticalArea(testData[i].points);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
