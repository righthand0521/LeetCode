#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int findMinDifference(vector<string>& timePoints) {
        int retVal = 0;

        vector<int> minutes;
        for (string timePoint : timePoints) {
            int minute = stoi(timePoint.substr(0, 2)) * 60 + stoi(timePoint.substr(3, 5));
            minutes.emplace_back(minute);
        }
        sort(minutes.begin(), minutes.end());

        int minutesSize = minutes.size();
        retVal = 24 * 60 - minutes[minutesSize - 1] + minutes[0];
        for (int i = 0; i < (minutesSize - 1); ++i) {
            retVal = min(retVal, minutes[i + 1] - minutes[i]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> timePoints;
    };
    vector<subject> testData{{{"23:59", "00:00"}}, {{"00:00", "23:59", "00:00"}}, {{"01:01", "02:01"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: timePoints = ["23:59","00:00"]
     *  Output: 1
     *
     *  Input: timePoints = ["00:00","23:59","00:00"]
     *  Output: 0
     *
     *  Input: timePoints = ["01:01","02:01"]
     *  Output: 60
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: timePoints = [";
        for (long unsigned int j = 0; j < testData[i].timePoints.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "\"" << testData[i].timePoints[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.findMinDifference(testData[i].timePoints);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
