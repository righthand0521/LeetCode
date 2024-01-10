#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int longestArithSeqLength(vector<int>& nums) {
        int retVal = 1;

        int minNum = *min_element(nums.begin(), nums.end());
        int maxNum = *max_element(nums.begin(), nums.end());
        int diff = maxNum - minNum;
        for (int interval = (-diff); interval <= diff; ++interval) {
            vector<int> dp(maxNum + 1, -1);

            for (int num : nums) {
                int idx = num - interval;

                if ((idx >= minNum) && (idx <= maxNum) && (dp[idx] != -1)) {
                    dp[num] = max(dp[num], dp[idx] + 1);
                    retVal = max(retVal, dp[num]);
                }
                dp[num] = max(dp[num], 1);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{3, 6, 9, 12}}, {{9, 4, 7, 2, 10}}, {{20, 1, 15, 3, 10, 5, 8}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [3,6,9,12]
     *  Output: 4
     *
     *  Input: nums = [9,4,7,2,10]
     *  Output: 3
     *
     *  Input: nums = [20,1,15,3,10,5,8]
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.longestArithSeqLength(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
