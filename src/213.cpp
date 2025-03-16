#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int robHouse(vector<int>& nums, int start, int end) {
        int retVal = 0;

        int first = nums[start];
        int second = max(nums[start], nums[start + 1]);
        int temp;
        for (int i = start + 2; i < end; ++i) {
            temp = second;
            second = max(first + nums[i], second);
            first = temp;
        }
        retVal = second;

        return retVal;
    }

   public:
    int rob(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        if (numsSize == 1) {
            retVal = nums[0];
        } else if (numsSize == 2) {
            retVal = max(nums[0], nums[1]);
        } else {
            int robStartFirst = robHouse(nums, 0, numsSize - 1);
            int robStartSecond = robHouse(nums, 1, numsSize);
            retVal = max(robStartFirst, robStartSecond);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{2, 3, 2}}, {{1, 2, 3, 1}}, {{1, 2, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,3,2]
     *  Output: 3
     *
     *  Input: nums = [1,2,3,1]
     *  Output: 4
     *
     *  Input: nums = [1,2,3]
     *  Output: 3
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
