#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        int retVal = 0;

        vector<pair<int, int>> job;
        int jobIdx = 0;
        int jobSize = difficulty.size();
        for (int i = 0; i < jobSize; ++i) {
            job.emplace_back(difficulty[i], profit[i]);
        }
        sort(job.begin(), job.end());

        int maxProfit = 0;
        sort(worker.begin(), worker.end());
        for (auto pWork : worker) {
            while ((jobIdx < jobSize) && (pWork >= job[jobIdx].first)) {
                maxProfit = max(maxProfit, job[jobIdx].second);
                ++jobIdx;
            }
            retVal += maxProfit;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> difficulty;
        vector<int> profit;
        vector<int> worker;
    };
    vector<subject> testData{{{2, 4, 6, 8, 10}, {10, 20, 30, 40, 50}, {4, 5, 6, 7}},
                             {{85, 47, 57}, {24, 66, 99}, {40, 25, 25}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: difficulty = [2,4,6,8,10], profit = [10,20,30,40,50], worker = [4,5,6,7]
     *  Output: 100
     *
     *  Input: difficulty = [85,47,57], profit = [24,66,99], worker = [40,25,25]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: difficulty = [";
        for (long unsigned int j = 0; j < testData[i].difficulty.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].difficulty[j];
        }
        cout << "], profit = [";
        for (long unsigned int j = 0; j < testData[i].profit.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].profit[j];
        }
        cout << "], worker = [";
        for (long unsigned int j = 0; j < testData[i].worker.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].worker[j];
        }
        cout << "]\n";

        answer = cSolution.maxProfitAssignment(testData[i].difficulty, testData[i].profit, testData[i].worker);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
