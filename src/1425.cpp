#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int constrainedSubsetSum(vector<int>& nums, int k) {
        int retVal = 0;

        int numsSize = nums.size();

        deque<int> monotonicDeque;
        vector<int> dp(numsSize);

        for (int i = 0; i < numsSize; i++) {
            if ((monotonicDeque.empty() == false) && (i - monotonicDeque.front() > k)) {
                monotonicDeque.pop_front();
            }

            dp[i] = ((monotonicDeque.empty() == false) ? (dp[monotonicDeque.front()]) : (0)) + nums[i];
            while ((monotonicDeque.empty() == false) && (dp[monotonicDeque.back()] < dp[i])) {
                monotonicDeque.pop_back();
            }

            if (dp[i] > 0) {
                monotonicDeque.push_back(i);
            }
        }

        retVal = *max_element(dp.begin(), dp.end());

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{10, 2, -10, 5, 20}, 2}, {{-1, -2, -3}, 1}, {{10, -2, -10, -5, 20}, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [10,2,-10,5,20], k = 2
     *  Output: 37
     *
     *  Input: nums = [-1,-2,-3], k = 1
     *  Output: -1
     *
     *  Input: nums = [10,-2,-10,-5,20], k = 2
     *  Output: 23
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.constrainedSubsetSum(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
