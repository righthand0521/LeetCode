#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxScore(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        int maxStates = 1 << numsSize;
        int finalMask = maxStates - 1;
        vector<int> dp(maxStates, 0);
        for (int state = finalMask; state >= 0; state -= 1) {
            if (state == finalMask) {
                dp[state] = 0;
                continue;
            }

            int numbersTaken = __builtin_popcount(state);
            int pairsFormed = numbersTaken / 2;
            if (numbersTaken % 2) {
                continue;
            }

            for (int firstIndex = 0; firstIndex < numsSize; firstIndex += 1) {
                for (int secondIndex = firstIndex + 1; secondIndex < numsSize; secondIndex += 1) {
                    if (((state >> firstIndex) & 1) == 1 || ((state >> secondIndex) & 1) == 1) {
                        continue;
                    }

                    int currentScore = (pairsFormed + 1) * __gcd(nums[firstIndex], nums[secondIndex]);
                    int stateAfterPickingCurrPair = state | (1 << firstIndex) | (1 << secondIndex);
                    int remainingScore = dp[stateAfterPickingCurrPair];
                    dp[state] = max(dp[state], currentScore + remainingScore);
                }
            }
        }
        retVal = dp[0];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2}}, {{3, 4, 6, 8}}, {{1, 2, 3, 4, 5, 6}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2]
     *  Output: 1
     *
     *  Input: nums = [3,4,6,8]
     *  Output: 11
     *
     *  Input: nums = [1,2,3,4,5,6]
     *  Output: 14
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.maxScore(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
