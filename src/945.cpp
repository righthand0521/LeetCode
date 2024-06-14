#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minIncrementForUnique(vector<int>& nums) {
        int retVal = 0;

        sort(nums.begin(), nums.end());

        int numsSize = nums.size();
        for (int i = 1; i < numsSize; ++i) {
            if (nums[i] <= nums[i - 1]) {
                int increment = nums[i - 1] + 1 - nums[i];
                retVal += increment;
                nums[i] = nums[i - 1] + 1;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 2}}, {{3, 2, 1, 2, 1, 7}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,2]
     *  Output: 1
     *
     *  Input: nums = [3,2,1,2,1,7]
     *  Output: 6
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.minIncrementForUnique(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
