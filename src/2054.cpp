#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxTwoEvents(vector<vector<int>>& events) {
        int retVal = 0;

        vector<array<int, 3>> times;
        for (auto& event : events) {
            times.push_back({event[0], 1, event[2]});      // 1 denotes start time.
            times.push_back({event[1] + 1, 0, event[2]});  // 0 denotes end time.
        }
        sort(begin(times), end(times));

        int maxValue = 0;
        for (auto& timeValue : times) {
            // If current time is a start time, find maximum sum of maximum end time till now.
            if (timeValue[1]) {
                retVal = max(retVal, timeValue[2] + maxValue);
            } else {
                maxValue = max(maxValue, timeValue[2]);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> events;
    };
    vector<subject> testData{
        {{{1, 3, 2}, {4, 5, 2}, {2, 4, 3}}}, {{{1, 3, 2}, {4, 5, 2}, {1, 5, 5}}}, {{{1, 5, 3}, {1, 5, 1}, {6, 6, 5}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: events = [[1,3,2],[4,5,2],[2,4,3]]
     *  Output: 4
     *
     *  Input: events = [[1,3,2],[4,5,2],[1,5,5]]
     *  Output: 5
     *
     *  Input: events = [[1,5,3],[1,5,1],[6,6,5]]
     *  Output: 8
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: events = [";
        for (long unsigned int j = 0; j < testData[i].events.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].events[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].events[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.maxTwoEvents(testData[i].events);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
