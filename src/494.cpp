#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
   public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int retVal = 0;

        int totalSum = accumulate(nums.begin(), nums.end(), 0);

        vector<int> dp(2 * totalSum + 1, 0);
        dp[nums[0] + totalSum] = 1;    // Adding nums[0]
        dp[-nums[0] + totalSum] += 1;  // Subtracting nums[0]

        int numsSize = nums.size();
        for (int index = 1; index < numsSize; index++) {
            vector<int> next(2 * totalSum + 1, 0);
            for (int sum = -totalSum; sum <= totalSum; sum++) {
                if (dp[sum + totalSum] <= 0) {
                    continue;
                }
                next[sum + nums[index] + totalSum] += dp[sum + totalSum];
                next[sum - nums[index] + totalSum] += dp[sum + totalSum];
            }
            dp = next;
        }

        // Return the result if the target is within the valid range
        if (abs(target) <= totalSum) {
            retVal = dp[target + totalSum];
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int target;
    };
    vector<subject> testData{{{1, 1, 1, 1, 1}, 3}, {{1}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,1,1,1,1], target = 3
     *  Output: 5
     *
     *  Input: nums = [1], target = 1
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], target = " << testData[i].target << "\n";

        answer = cSolution.findTargetSumWays(testData[i].nums, testData[i].target);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
