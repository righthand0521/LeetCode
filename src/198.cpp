#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int rob(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        if (numsSize == 0) {
            return retVal;
        } else if (numsSize == 1) {
            retVal = nums[0];
            return retVal;
        }

        int first = nums[0];
        int second = max(nums[0], nums[1]);
        for (int i = 2; i < numsSize; ++i) {
            int temp = second;
            second = max(first + nums[i], second);
            first = temp;
        }
        retVal = second;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 3, 1}}, {{2, 7, 9, 3, 1}}, {{2, 1}}, {{2, 1, 1, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,3,1]
     *  Output: 4
     *
     *  Input: nums = [2,7,9,3,1]
     *  Output: 12
     *
     *  Input: nums = [2, 1]
     *  Output: 2
     *
     *  Input: nums = [2, 1, 1, 2]
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.rob(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
