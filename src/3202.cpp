#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maximumLength(vector<int>& nums, int k) {
        int retVal = 0;

        vector<vector<int>> dp(k, vector<int>(k, 0));
        for (int num : nums) {
            num %= k;
            for (int prev = 0; prev < k; ++prev) {
                dp[prev][num] = dp[num][prev] + 1;
                retVal = max(retVal, dp[prev][num]);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{1, 2, 3, 4, 5}, 2}, {{1, 4, 2, 3, 1, 4}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,3,4,5], k = 2
     *  Output: 5
     *
     *  Input: nums = [1,4,2,3,1,4], k = 3
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.maximumLength(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
