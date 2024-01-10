#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int combinationSum4(vector<int>& nums, int target) {
        int retVal = 0;

        vector<unsigned long> dp(target + 1, 0);
        dp[0] = 1;
        for (int i = 0; i <= target; ++i) {
            for (auto num : nums) {
                if (i >= num) {
                    dp[i] += dp[i - num];
                }
            }
        }
        retVal = dp[target];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int target;
    };
    vector<subject> testData{{{1, 2, 3}, 4}, {{9}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,3], target = 4
     *  Output: 7
     *
     *  Input: nums = [9], target = 3
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], target = " << testData[i].target << "\n";

        answer = cSolution.combinationSum4(testData[i].nums, testData[i].target);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
