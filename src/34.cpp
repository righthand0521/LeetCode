#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> retVal(2, -1);

        int numsSize = nums.size();
        if (numsSize == 0) {
            return retVal;
        }
        int left, right, middle;

        left = 0;
        right = numsSize - 1;
        while (left < right) {
            middle = left + (right - left) / 2;
            if (nums[middle] >= target) {
                right = middle;
            } else {
                left = middle + 1;
            }
        }
        if (nums[right] != target) {
            return retVal;
        }
        retVal[0] = right;

        left = 0;
        right = numsSize - 1;
        while (left < right) {
            middle = right - (right - left) / 2;
            if (nums[middle] <= target) {
                left = middle;
            } else {
                right = middle - 1;
            }
        }
        if (nums[right] != target) {
            retVal[0] = -1;
            return retVal;
        }
        retVal[1] = left;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int target;
    };
    vector<subject> testData{{{5, 7, 7, 8, 8, 10}, 8}, {{5, 7, 7, 8, 8, 10}, 6}, {{}, 0}, {{1}, 1}, {{2, 2}, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [5,7,7,8,8,10], target = 8
     *  Output: [3,4]
     *
     *  Input: nums = [5,7,7,8,8,10], target = 6
     *  Output: [-1,-1]
     *
     *  Input: nums = [], target = 0
     *  Output: [-1,-1]
     *
     *  Input: nums = [1], target = 1
     *  Output: [0,0]
     *
     *  Input: nums = [2,2], target = 2
     *  Output: [0,1]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], target = " << testData[i].target << "\n";

        answer = cSolution.searchRange(testData[i].nums, testData[i].target);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
