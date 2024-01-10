#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool PredictTheWinner(vector<int>& nums) {
        bool retVal = false;

        /* https://leetcode.cn/problems/predict-the-winner/solutions/396343/shou-hua-tu-jie-san-chong-xie-fa-di-gui-ji-yi-hua-/
         *  i = j: dp[i][j] = nums[i]
         *  i < j: dp[i][j] = max(nums[i] - dp[i + 1][j], nums[j] - dp[i][j - 1]
         *
         *  Example: nums = [1,5,2]
         *    | 1 5 2 | 1 5 2 | 1 5 2 | 1 5  2
         *  --+-------+-------+-------+--------
         *  1 | 1     | 1     | 1 4   | 1 4 -2
         *  5 | 0 5   | 0 5 3 | 0 5 3 | 0 5  3
         *  2 | 0 0 2 | 0 0 2 | 0 0 2 | 0 0  2
         *
         *  Example: nums = [1,5,233,7]
         *      | 1 5 233 7 | 1  5 233  7  | 1 5 233   7  | 1 5 233   7
         *  ----+-----------+--------------+--------------+-------------
         *   1  | 1         | 1            | 1            | 1 4 229  222
         *   5  | 0 5       | 0  5         | 0 5 228 -221 | 0 5 229 -221
         *  233 | 0 0 233   | 0  0 233 226 | 0 0 233  226 | 0 0 233  226
         *   7  | 0 0  0  7 | 0  0  0   7  | 0 0  0    7  | 0 0  0    7
         */

        int numsSize = nums.size();
        vector<vector<int>> dp(numsSize, vector<int>(numsSize, 0));

        for (int i = 0; i < numsSize; ++i) {
            dp[i][i] = nums[i];
        }

        for (int i = numsSize - 2; i >= 0; --i) {
            for (int j = i + 1; j < numsSize; ++j) {
                dp[i][j] = max(nums[i] - dp[i + 1][j], nums[j] - dp[i][j - 1]);
            }
        }

        if (dp[0][numsSize - 1] >= 0) {
            retVal = true;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 5, 2}}, {{1, 5, 233, 7}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,5,2]
     *  Output: false
     *
     *  Input: nums = [1,5,233,7]
     *  Output: true
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.PredictTheWinner(testData[i].nums);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
