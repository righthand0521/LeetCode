#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    // https://leetcode.cn/problems/tallest-billboard/solutions/368725/yi-quan-ji-ben-mei-shuo-ming-bai-de-zhe-pian-kan-l/
    int tallestBillboard(vector<int>& rods) {
        int retVal = 0;

        unordered_map<int, int> dp;
        dp[0] = 0;
        for (auto rod : rods) {
            unordered_map<int, int> tmp(dp);
            for (auto iterator : tmp) {
                int key = iterator.first;
                int value = iterator.second;
                dp[key + rod] = max(dp[key + rod], value + rod);
                dp[key - rod] = max(dp[key - rod], value);
            }
        }
        retVal = dp[0];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> rods;
    };
    vector<subject> testData{{{1, 2, 3, 6}}, {{1, 2, 3, 4, 5, 6}}, {{1, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: rods = [1,2,3,6]
     *  Output: 6
     *
     *  Input: rods = [1,2,3,4,5,6]
     *  Output: 10
     *
     *  Input: rods = [1,2]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: rods = [";
        for (long unsigned int j = 0; j < testData[i].rods.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].rods[j];
        }
        cout << "]\n";

        answer = cSolution.tallestBillboard(testData[i].rods);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
