#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> retVal;

        int left = newInterval[0];
        int right = newInterval[1];
        bool placed = false;
        for (const auto& interval : intervals) {
            if (interval[0] > right) {
                if (placed == false) {
                    retVal.push_back({left, right});
                    placed = true;
                }

                retVal.push_back(interval);
            } else if (interval[1] < left) {
                retVal.push_back(interval);
            } else {
                left = min(left, interval[0]);
                right = max(right, interval[1]);
            }
        }

        if (placed == false) {
            retVal.push_back({left, right});
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> intervals;
        vector<int> newInterval;
    };
    vector<subject> testData{
        {{{1, 3}, {6, 9}}, {2, 5}}, {{{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}}, {4, 8}}, {{}, {5, 7}}};
    int numberOfTestCase = testData.size();

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
        cout << "], newInterval = [";
        for (long unsigned int j = 0; j < testData[i].newInterval.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].newInterval[j];
        }
        cout << "]\n";

        answer = cSolution.insert(testData[i].intervals, testData[i].newInterval);
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
