#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int findMinArrowShots(vector<vector<int>>& points) {
        int retVal = 0;

        sort(points.begin(), points.end(), [&](const vector<int>& x, const vector<int>& y) {
            // ascending order
            if (x[1] == y[1]) {
                return (x[0] < y[0]);
            }
            return (x[1] < y[1]);
        });

        int pointsSize = points.size();
        int arrow = points[0][1];
        ++retVal;
        for (int i = 1; i < pointsSize; ++i) {
            int start = points[i][0];
            int end = points[i][1];
            if (start > arrow) {
                ++retVal;
                arrow = end;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> points;
    };
    vector<subject> testData{
        {{{10, 16}, {2, 8}, {1, 6}, {7, 12}}}, {{{1, 2}, {3, 4}, {5, 6}, {7, 8}}}, {{{1, 2}, {2, 3}, {3, 4}, {4, 5}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: points = [[10,16],[2,8],[1,6],[7,12]]
     *  Output: 2
     *
     *  Input: points = [[1,2],[3,4],[5,6],[7,8]]
     *  Output: 4
     *
     *  Input: points = [[1,2],[2,3],[3,4],[4,5]]
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

        answer = cSolution.findMinArrowShots(testData[i].points);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
