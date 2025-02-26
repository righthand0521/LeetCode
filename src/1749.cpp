#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxAbsoluteSum(vector<int>& nums) {
        int retVal = 0;

        int prefixSum = 0;
        int minPrefixSum = 0;
        int maxPrefixSum = 0;
        for (int num : nums) {
            prefixSum += num;
            minPrefixSum = min(minPrefixSum, prefixSum);
            maxPrefixSum = max(maxPrefixSum, prefixSum);
        }
        retVal = maxPrefixSum - minPrefixSum;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, -3, 2, 3, -4}}, {{2, -5, 1, -4, 3, -2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,-3,2,3,-4]
     *  Output: 5
     *
     *  Input: nums = [2,-5,1,-4,3,-2]
     *  Output: 8
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.maxAbsoluteSum(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
