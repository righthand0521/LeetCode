#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minGroups(vector<vector<int>>& intervals) {
        int retVal = 0;

        // Convert the intervals to two events start as {start, 1} and end as {end, -1}
        vector<pair<int, int>> intervalsWithEnd;
        for (vector<int> interval : intervals) {
            intervalsWithEnd.push_back({interval[0], 1});
            intervalsWithEnd.push_back({interval[1] + 1, -1});
        }
        // Sort the events according to the number and then by the value (1/-1).
        sort(intervalsWithEnd.begin(), intervalsWithEnd.end());

        int concurrentIntervals = 0;
        int maxConcurrentIntervals = 0;
        for (auto p : intervalsWithEnd) {
            concurrentIntervals += p.second;
            maxConcurrentIntervals = max(maxConcurrentIntervals, concurrentIntervals);
        }
        retVal = maxConcurrentIntervals;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> intervals;
    };
    vector<subject> testData{{{{5, 10}, {6, 8}, {1, 5}, {2, 3}, {1, 10}}}, {{{1, 3}, {5, 6}, {8, 10}, {11, 13}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: intervals = [[5,10],[6,8],[1,5],[2,3],[1,10]]
     *  Output: 3
     *
     *  Input: intervals = [[1,3],[5,6],[8,10],[11,13]]
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: intervals = [";
        for (long unsigned int j = 0; j < testData[i].intervals.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].intervals[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].intervals[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.minGroups(testData[i].intervals);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
