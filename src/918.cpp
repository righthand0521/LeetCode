#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int retVal = 0;

        /* Kadane’s Algorithm: https://en.wikipedia.org/wiki/Maximum_subarray_problem
         *  1. Maximum Subarray is not Circular: maxSum
         *  2. Maximum Subarray is Circular: sum - minSum
         */
        int curMax = 0;
        int sumMax = nums[0];
        int curMin = 0;
        int sumMin = nums[0];
        int sumTotal = 0;
        for (int num : nums) {
            curMax = max(curMax, 0) + num;
            sumMax = max(sumMax, curMax);

            curMin = min(curMin, 0) + num;
            sumMin = min(sumMin, curMin);

            sumTotal += num;
        }

        if (sumTotal == sumMin) {
            retVal = sumMax;
        } else {
            retVal = max(sumMax, sumTotal - sumMin);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, -2, 3, -2}}, {{5, -3, 5}}, {{-3, -2, -3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,-2,3,-2]
     *  Output: 3
     *
     *  Input: nums = [5,-3,5]
     *  Output: 10
     *
     *  Input: nums = [-3,-2,-3]
     *  Output: -2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.maxSubarraySumCircular(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
