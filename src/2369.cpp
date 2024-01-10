#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool validPartition(vector<int>& nums) {
        bool retVal = false;

        int numsSize = nums.size();
        vector<bool> dp(numsSize + 1, false);
        dp[0] = true;
        // dp[i] represents if the prefix of length i can form a valid partition
        //  dp[index] : dp[index - 2] && (nums[i - 1] == nums[i])
        //  dp[index] : dp[index - 3] && (nums[i - 2] == nums[i - 1] == nums[i])
        //  dp[index] : dp[index - 3] && (nums[i - 2] + 2 == nums[i - 1] + 1 == nums[i])
        for (int i = 0; i < numsSize; ++i) {
            int index = i + 1;
            if ((i > 0) && (nums[i - 1] == nums[i])) {
                dp[index] = dp[index] | dp[index - 2];
            }
            if ((i > 1) && (nums[i - 2] == nums[i]) && (nums[i - 1] == nums[i])) {
                dp[index] = dp[index] | dp[index - 3];
            }
            if ((i > 1) && (nums[i - 2] + 2 == nums[i]) && (nums[i - 1] + 1 == nums[i])) {
                dp[index] = dp[index] | dp[index - 3];
            }
        }
        retVal = dp[numsSize];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{4, 4, 4, 5, 6}}, {{1, 1, 1, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [4,4,4,5,6]
     *  Output: true
     *
     *  Input: nums = [1,1,1,2]
     *  Output: false
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.validPartition(testData[i].nums);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
