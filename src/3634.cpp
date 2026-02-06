#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minRemoval(vector<int>& nums, int k) {
        int retVal = 0;

        int numsSize = nums.size();

        sort(nums.begin(), nums.end());

        retVal = numsSize;
        int right = 0;
        for (int left = 0; left < numsSize; ++left) {
            while ((right < numsSize) && (nums[right] <= static_cast<long long>(nums[left]) * k)) {
                ++right;
            }
            retVal = min(retVal, numsSize - (right - left));
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{2, 1, 5}, 2}, {{1, 6, 2, 9}, 3}, {{4, 6}, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,1,5], k = 2
     *  Output: 1
     *
     *  Input: nums = [1,6,2,9], k = 3
     *  Output: 2
     *
     *  Input: nums = [4,6], k = 2
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.minRemoval(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
