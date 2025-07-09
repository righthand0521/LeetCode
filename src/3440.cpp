#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxFreeTime(int eventTime, vector<int>& startTime, vector<int>& endTime) {
        int retVal = 0;

        int startTimeSize = startTime.size();
        vector<bool> q(startTimeSize);
        for (int i = 0, t1 = 0, t2 = 0; i < startTimeSize; i++) {
            if (endTime[i] - startTime[i] <= t1) {
                q[i] = true;
            }
            t1 = max(t1, startTime[i] - ((i == 0) ? (0) : (endTime[i - 1])));

            if (endTime[startTimeSize - i - 1] - startTime[startTimeSize - i - 1] <= t2) {
                q[startTimeSize - i - 1] = true;
            }
            t2 = max(t2, ((i == 0) ? (eventTime) : (startTime[startTimeSize - i])) - endTime[startTimeSize - i - 1]);
        }

        for (int i = 0; i < startTimeSize; i++) {
            int left = i == 0 ? 0 : endTime[i - 1];
            int right = (i == startTimeSize - 1) ? (eventTime) : (startTime[i + 1]);
            if (q[i] == true) {
                retVal = max(retVal, right - left);
            } else {
                retVal = max(retVal, right - left - (endTime[i] - startTime[i]));
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int eventTime;
        vector<int> startTime;
        vector<int> endTime;
    };
    vector<subject> testData{{5, {1, 3}, {2, 5}},
                             {10, {0, 7, 9}, {1, 8, 10}},
                             {10, {0, 3, 7, 9}, {1, 4, 8, 10}},
                             {5, {0, 1, 2, 3, 4}, {1, 2, 3, 4, 5}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: eventTime = 5, startTime = [1,3], endTime = [2,5]
     *  Output: 2
     *
     *  Input: eventTime = 10, startTime = [0,7,9], endTime = [1,8,10]
     *  Output: 7
     *
     *  Input: eventTime = 10, startTime = [0,3,7,9], endTime = [1,4,8,10]
     *  Output: 6
     *
     *  Input: eventTime = 5, startTime = [0, 1, 2, 3, 4], endTime = [1, 2, 3, 4, 5]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: eventTime = " << testData[i].eventTime << ", startTime = [";
        for (long unsigned int j = 0; j < testData[i].startTime.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].startTime[j];
        }
        cout << "], endTime = [";
        for (long unsigned int j = 0; j < testData[i].endTime.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].endTime[j];
        }
        cout << "]\n";

        answer = cSolution.maxFreeTime(testData[i].eventTime, testData[i].startTime, testData[i].endTime);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
