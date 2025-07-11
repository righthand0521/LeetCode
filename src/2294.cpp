﻿#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int partitionArray(vector<int>& nums, int k) {
        int retVal = 1;

        sort(nums.begin(), nums.end());

        int minValue = nums[0];
        int numsSize = nums.size();
        for (int i = 0; i < numsSize; i++) {
            if (nums[i] - minValue > k) {
                retVal++;
                minValue = nums[i];
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{3, 6, 1, 2, 5}, 2}, {{1, 2, 3}, 1}, {{2, 2, 4, 5}, 0}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [3,6,1,2,5], k = 2
     *  Output: 2
     *
     *  Input: nums = [1,2,3], k = 1
     *  Output: 2
     *
     *  Input: nums = [2,2,4,5], k = 0
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n ";

        answer = cSolution.partitionArray(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
