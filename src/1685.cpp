#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> getSumAbsoluteDifferences(vector<int>& nums) {
        vector<int> retVal;

        int numsSize = nums.size();

        vector<int> prefixSum;
        prefixSum.emplace_back(nums[0]);
        for (int i = 1; i < numsSize; ++i) {
            prefixSum.emplace_back(prefixSum[i - 1] + nums[i]);
        }

        for (int i = 0; i < numsSize; ++i) {
            int left = (nums[i] * i) - (prefixSum[i] - nums[i]);
            int right = (prefixSum[numsSize - 1] - prefixSum[i]) - (nums[i] * (numsSize - 1 - i));
            retVal.emplace_back(left + right);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int target;
    };
    vector<subject> testData{{{2, 3, 5}}, {{1, 4, 6, 8, 10}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,3,5]
     *  Output: [4,3,5]
     *
     *  Input: nums = [1,4,6,8,10]
     *  Output: [24,15,13,15,21]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.getSumAbsoluteDifferences(testData[i].nums);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
