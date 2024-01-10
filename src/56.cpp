#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> retVal;

        sort(intervals.begin(), intervals.end(), [&](const vector<int>& x, const vector<int>& y) {
            // ascending order
            if (x[0] == y[0]) {
                return (x[1] < y[1]);
            }
            return (x[0] < y[0]);
        });

        int intervalsSize = intervals.size();
        retVal.emplace_back(intervals[0]);
        for (int i = 1; i < intervalsSize; ++i) {
            if (retVal.back()[1] >= intervals[i][0]) {
                retVal.back()[1] = max(retVal.back()[1], intervals[i][1]);
            } else {
                retVal.emplace_back(intervals[i]);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> intervals;
    };
    vector<subject> testData{{{{1, 3}, {2, 6}, {8, 10}, {15, 18}}}, {{{1, 4}, {4, 5}}}, {{{1, 4}, {2, 3}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
     *  Output: [[1,6],[8,10],[15,18]]
     *
     *  Input: intervals = [[1,4],[4,5]]
     *  Output: [[1,5]]
     *
     *  Input: intervals = [[1,4],[2,3]]
     *  Output: [[1,4]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
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

        answer = cSolution.merge(testData[i].intervals);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < answer[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << answer[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
