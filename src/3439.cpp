#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxFreeTime(int eventTime, int k, vector<int>& startTime, vector<int>& endTime) {
        int retVal = 0;

        int startTimeSize = startTime.size();
        int t = 0;
        for (int i = 0; i < startTimeSize; i++) {
            t += (endTime[i] - startTime[i]);
            int left = (i <= k - 1) ? (0) : (endTime[i - k]);
            int right = (i == startTimeSize - 1) ? (eventTime) : (startTime[i + 1]);
            retVal = max(retVal, right - left - t);
            if (i >= k - 1) {
                t -= (endTime[i - k + 1] - startTime[i - k + 1]);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int eventTime;
        int k;
        vector<int> startTime;
        vector<int> endTime;
    };
    vector<subject> testData{
        {5, 1, {1, 3}, {2, 5}}, {10, 1, {0, 2, 9}, {1, 4, 10}}, {5, 2, {0, 1, 2, 3, 4}, {1, 2, 3, 4, 5}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: eventTime = 5, k = 1, startTime = [1,3], endTime = [2,5]
     *  Output: 2
     *
     *  Input: eventTime = 10, k = 1, startTime = [0,2,9], endTime = [1,4,10]
     *  Output: 6
     *
     *  Input: eventTime = 5, k = 2, startTime = [0,1,2,3,4], endTime = [1,2,3,4,5]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: eventTime = " << testData[i].eventTime << ", k = " << testData[i].k << ", startTime = [";
        for (long unsigned int j = 0; j < testData[i].startTime.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].startTime[j];
        }
        cout << "], endTime = [";
        for (long unsigned int j = 0; j < testData[i].endTime.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].endTime[j];
        }
        cout << "]\n";

        answer =
            cSolution.maxFreeTime(testData[i].eventTime, testData[i].k, testData[i].startTime, testData[i].endTime);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
