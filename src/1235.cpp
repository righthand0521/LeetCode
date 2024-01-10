#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int retVal = 0;

        int startTimeSize = startTime.size();

        vector<vector<int>> jobs(startTimeSize);
        for (int i = 0; i < startTimeSize; i++) {
            jobs[i] = {startTime[i], endTime[i], profit[i]};
        }
        sort(jobs.begin(), jobs.end(),
             [](const vector<int>& job1, const vector<int>& job2) -> bool { return job1[1] < job2[1]; });

        vector<int> dp(startTimeSize + 1);
        for (int i = 1; i <= startTimeSize; i++) {
            int k = upper_bound(jobs.begin(), jobs.begin() + i - 1, jobs[i - 1][0],
                                [&](int st, const vector<int>& job) -> bool { return st < job[1]; }) -
                    jobs.begin();
            dp[i] = max(dp[i - 1], dp[k] + jobs[i - 1][2]);
        }
        retVal = dp[startTimeSize];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> startTime;
        vector<int> endTime;
        vector<int> profit;
    };
    vector<subject> testData{{{1, 2, 3, 3}, {3, 4, 5, 6}, {50, 10, 40, 70}},
                             {{1, 2, 3, 4, 6}, {3, 5, 10, 6, 9}, {20, 20, 100, 70, 60}},
                             {{1, 1, 1}, {2, 3, 4}, {5, 6, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
     *  Output: 120
     *
     *  Input: startTime = [1,2,3,4,6], endTime = [3,5,10,6,9], profit = [20,20,100,70,60]
     *  Output: 150
     *
     *  Input: startTime = [1,1,1], endTime = [2,3,4], profit = [5,6,4]
     *  Output: 6
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: startTime = [";
        for (long unsigned int j = 0; j < testData[i].startTime.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].startTime[j];
        }
        cout << "], endTime = [";
        for (long unsigned int j = 0; j < testData[i].endTime.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].endTime[j];
        }
        cout << "], profit = [";
        for (long unsigned int j = 0; j < testData[i].profit.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].profit[j];
        }
        cout << "]\n";

        answer = cSolution.jobScheduling(testData[i].startTime, testData[i].endTime, testData[i].profit);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
