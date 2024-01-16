#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int retVal = -1;

        int gasSize = gas.size();

        /* https://leetcode.cn/problems/gas-station/solutions/488498/shou-hua-tu-jie-liang-ge-guan-jian-jie-lun-de-jian/
         *  1. if sum(gas) < sum(cost), then it has no solution(-1).
         *  2. if sum(gas) >= sum(cost), then it has solution(i).
         *
         *      sum(gas) < sum(cost)     sum(gas) >= sum(cost)
         *     /                    \   /                     \
         *  [0]----------------------[i]-----------------------[n]
         */
        int tank = 0;
        int totalSum = 0;
        int start = 0;
        for (int i = 0; i < gasSize; ++i) {
            totalSum += (gas[i] - cost[i]);

            tank += (gas[i] - cost[i]);
            if (tank < 0) {
                start = i + 1;
                tank = 0;
            }
        }

        if (totalSum >= 0) {
            retVal = start;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> gas;
        vector<int> cost;
    };
    vector<subject> testData{{{1, 2, 3, 4, 5}, {3, 4, 5, 1, 2}}, {{2, 3, 4}, {3, 4, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
     *  Output: 3
     *
     *  Input: gas = [2,3,4], cost = [3,4,3]
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: gas = [";
        for (long unsigned int j = 0; j < testData[i].gas.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].gas[j];
        }
        cout << "], cost = [";
        for (long unsigned int j = 0; j < testData[i].cost.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].cost[j];
        }
        cout << "]\n";

        answer = cSolution.canCompleteCircuit(testData[i].gas, testData[i].cost);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
