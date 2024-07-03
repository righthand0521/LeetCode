#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    int minDifference(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        if (numsSize <= 4) {  // If the array has 4 or fewer elements, return 0
            return retVal;
        }

        sort(nums.begin(), nums.end());

        int minDiff = numeric_limits<int>::max();
        for (int left = 0; left < 4; ++left) {
            int right = numsSize - 4 + left;
            minDiff = min(minDiff, nums[right] - nums[left]);
        }
        retVal = minDiff;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{5, 3, 2, 4}}, {{1, 5, 0, 10, 14}}, {{3, 100, 20}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [5,3,2,4]
     *  Output: 0
     *
     *  Input: nums = [1,5,0,10,14]
     *  Output: 1
     *
     *  Input: nums = [3,100,20]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.minDifference(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
