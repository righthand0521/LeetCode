#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxAdjacentDistance(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        retVal = max(retVal, abs(nums[0] - nums[numsSize - 1]));
        for (int i = 1; i < numsSize; ++i) {
            retVal = max(retVal, abs(nums[i] - nums[i - 1]));
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 4}}, {{-5, -10, -5}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,4]
     *  Output: 3
     *
     *  Input: nums = [-5,-10,-5]
     *  Output: 5
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.maxAdjacentDistance(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
