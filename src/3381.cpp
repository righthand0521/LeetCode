#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    long long maxSubarraySum(vector<int>& nums, int k) {
        long long retVal = 0;

        int numsSize = nums.size();

        long long prefixSum = 0;
        long long maxSum = numeric_limits<long long>::min();
        vector<long long> kSum(k, numeric_limits<long long>::max() / 2);
        kSum[k - 1] = 0;
        for (int i = 0; i < numsSize; i++) {
            prefixSum += nums[i];
            maxSum = max(maxSum, prefixSum - kSum[i % k]);
            kSum[i % k] = min(kSum[i % k], prefixSum);
        }
        retVal = maxSum;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{1, 2}, 1}, {{-1, -2, -3, -4, -5}, 4}, {{-5, 1, 2, -3, 4}, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2], k = 1
     *  Output: 3
     *
     *  Input: nums = [-1,-2,-3,-4,-5], k = 4
     *  Output: -10
     *
     *  Input: nums = [-5,1,2,-3,4], k = 2
     *  Output: 4
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.maxSubarraySum(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
