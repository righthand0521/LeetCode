#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
   public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        bool retVal = false;

        int sumOfNums = accumulate(nums.begin(), nums.end(), 0);
        if (sumOfNums % k != 0) {
            return retVal;
        }
        int average = sumOfNums / k;

        int numsSize = nums.size();
        int dpSize = (1 << numsSize);
        vector<int> dp(dpSize, -1);
        dp[0] = 0;
        for (int i = 1; i < dpSize; ++i) {
            for (int key = 0; key < numsSize; ++key) {
                int value = nums[key];
                if ((i & (1 << key)) == 0) {
                    continue;
                }
                int j = i & ~(1 << key);

                if ((dp[j] >= 0) && (dp[j] + value <= average)) {
                    dp[i] = (dp[j] + value) % average;
                    break;
                }
            }
        }
        retVal = (dp[dpSize - 1] == 0);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{4, 3, 2, 3, 5, 2, 1}, 4}, {{1, 2, 3, 4}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [4,3,2,3,5,2,1], k = 4
     *  Output: true
     *
     *  Input: nums = [1,2,3,4], k = 3
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.canPartitionKSubsets(testData[i].nums, testData[i].k);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
