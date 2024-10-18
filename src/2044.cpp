#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int countMaxOrSubsets(vector<int>& nums) {
        int retVal = 0;

        vector<int> dp(1 << 17, 0);
        dp[0] = 1;

        int max = 0;
        for (int num : nums) {
            for (int i = max; i >= 0; i--) {
                dp[i | num] += dp[i];
            }
            max |= num;
        }
        retVal = dp[max];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{3, 1}}, {{2, 2, 2}}, {{3, 2, 1, 5}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [3,1]
     *  Output: 2
     *
     *  Input: nums = [2,2,2]
     *  Output: 7
     *
     *  Input: nums = [3,2,1,5]
     *  Output: 6
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.countMaxOrSubsets(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
