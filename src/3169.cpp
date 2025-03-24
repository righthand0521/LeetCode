#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int countDays(int days, vector<vector<int>>& meetings) {
        int retVal = 0;

        sort(meetings.begin(), meetings.end());

        int latestEnd = 0;
        for (auto& meeting : meetings) {
            int start = meeting[0];
            int end = meeting[1];

            // Add current range of days without a meeting
            if (start > latestEnd + 1) {
                retVal += start - latestEnd - 1;
            }

            // Update latest meeting end
            latestEnd = max(latestEnd, end);
        }

        // Add all days after the last day of meetings
        retVal += days - latestEnd;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int days;
        vector<vector<int>> meetings;
    };
    vector<subject> testData{{10, {{5, 7}, {1, 3}, {9, 10}}}, {5, {{2, 4}, {1, 3}}}, {6, {{1, 6}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: days = 10, meetings = [[5,7],[1,3],[9,10]]
     *  Output: 2
     *
     *  Input: days = 5, meetings = [[2,4],[1,3]]
     *  Output: 1
     *
     *  Input: days = 6, meetings = [[1,6]]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: days = " << testData[i].days << ", meetings = [";
        for (long unsigned int j = 0; j < testData[i].meetings.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].meetings[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].meetings[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.countDays(testData[i].days, testData[i].meetings);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
