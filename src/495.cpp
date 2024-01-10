#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {
        int retVal = 0;

        int expired = 0;
        for (auto timeSerie : timeSeries) {
            if (timeSerie >= expired) {
                retVal += duration;
            } else {
                retVal += (timeSerie + duration - expired);
            }
            expired = timeSerie + duration;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> timeSeries;
        int duration;
    };
    vector<subject> testData{{{1, 4}, 2}, {{1, 2}, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: timeSeries = [1,4], duration = 2
     *  Output: 4
     *
     *  Input: timeSeries = [1,2], duration = 2
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: timeSeries = [";
        for (long unsigned int j = 0; j < testData[i].timeSeries.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].timeSeries[j];
        }
        cout << "], duration = " << testData[i].duration << "\n";

        answer = cSolution.findPoisonedDuration(testData[i].timeSeries, testData[i].duration);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
