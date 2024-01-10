#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxSubArray(vector<int>& nums) {
        int retVal = numeric_limits<int>::min();

        // Kadane’s Algorithm: https://en.wikipedia.org/wiki/Maximum_subarray_problem
        int numsSize = nums.size();
        int sum = 0;
        for (int i = 0; i < numsSize; ++i) {
            sum = max(nums[i], (sum + nums[i]));
            retVal = max(retVal, sum);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{-2, 1, -3, 4, -1, 2, 1, -5, 4}}, {{1}}, {{5, 4, -1, 7, 8}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
     *  Output: 6
     *
     *  Input: nums = [1]
     *  Output: 1
     *
     *  Input: nums = [5,4,-1,7,8]
     *  Output: 23
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.maxSubArray(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
