﻿#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int waysToSplitArray(vector<int>& nums) {
        int retVal = 0;

        long long leftSum = 0;
        long long rightSum = 0;
        for (int num : nums) {
            rightSum += num;
        }

        int numsSize = nums.size();
        for (int i = 0; i < numsSize - 1; i++) {
            leftSum += nums[i];
            rightSum -= nums[i];
            if (leftSum >= rightSum) {
                retVal++;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{10, 4, -8, 7}}, {{2, 3, 1, 0}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [10,4,-8,7]
     *  Output: 2
     *
     *  Input: nums = [2,3,1,0]
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.waysToSplitArray(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
