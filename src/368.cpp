#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        vector<int> retVal;

        int numsSize = nums.size();

        sort(nums.begin(), nums.end());

        vector<vector<int>> dp;
        for (int i = 0; i < numsSize; ++i) {
            vector<int> tmp = {nums[i]};
            dp.emplace_back(tmp);
        }

        for (int i = 0; i < numsSize; ++i) {
            for (int j = 0; j < i; ++j) {
                if ((nums[i] % nums[j] == 0) && (dp[j].size() >= dp[i].size())) {
                    dp[i] = dp[j];
                    dp[i].emplace_back(nums[i]);
                }
            }

            if (retVal.size() < dp[i].size()) {
                retVal = dp[i];
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 3}}, {{1, 2, 4, 8}}, {{4, 8, 10, 240}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,3]
     *  Output: [1,2]
     *
     *  Input: nums = [1,2,4,8]
     *  Output: [1,2,4,8]
     *
     *  Input: nums = [4, 8, 10, 240]
     *  Output: [4,8,240]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.largestDivisibleSubset(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
