#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        int retVal = 0;

        sort(intervals.begin(), intervals.end(), [&](const vector<int>& x, const vector<int>& y) {
            // ascending order
            if (x[1] == y[1]) {
                return (x[0] < y[0]);
            }
            return (x[1] < y[1]);
        });

        int overlapping = numeric_limits<int>::min();
        for (auto interval : intervals) {
            int start = interval[0];
            int end = interval[1];

            if (start < overlapping) {
                ++retVal;
            } else {
                overlapping = end;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> intervals;
    };
    vector<subject> testData{{{{1, 2}, {2, 3}, {3, 4}, {1, 3}}}, {{{1, 2}, {1, 2}, {1, 2}}}, {{{1, 2}, {2, 3}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
     *  Output: 1
     *
     *  Input: intervals = [[1,2],[1,2],[1,2]]
     *  Output: 2
     *
     *  Input: intervals = [[1,2],[2,3]]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: intervals = [";
        for (long unsigned int j = 0; j < testData[i].intervals.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].intervals[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].intervals[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.eraseOverlapIntervals(testData[i].intervals);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
