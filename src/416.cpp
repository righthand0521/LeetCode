#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool canPartition(vector<int>& nums) {
        bool retVal = false;

        int numsSize = nums.size();

        int sum = 0;
        for (int i = 0; i < numsSize; ++i) {
            sum += nums[i];
        }
        if (sum % 2 != 0) {
            return retVal;
        }
        sum /= 2;

        vector<bool> dp(sum + 1, false);
        dp[0] = true;
        for (int i = 0; i < numsSize; ++i) {
            for (int j = sum; j >= nums[i]; --j) {
                dp[j] = dp[j] | dp[j - nums[i]];
            }
        }
        retVal = dp[sum];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 5, 11, 5}}, {{1, 2, 3, 5}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,5,11,5]
     *  Output: true
     *
     *  Input: nums = [1,2,3,5]
     *  Output: false
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.canPartition(testData[i].nums);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
