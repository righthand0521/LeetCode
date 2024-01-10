#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxFrequency(vector<int>& nums, int k) {
        int retVal = 0;

        sort(nums.begin(), nums.end());

        int numsSize = nums.size();
        long current = 0;
        int left = 0;
        for (int right = 0; right < numsSize; right++) {
            long target = nums[right];
            current += target;

            if ((right - left + 1) * target - current > k) {
                current -= nums[left];
                left++;
            }
        }
        retVal = numsSize - left;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{1, 2, 4}, 5}, {{1, 4, 8, 13}, 5}, {{3, 9, 6}, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,4], k = 5
     *  Output: 3
     *
     *  Input: nums = [1,4,8,13], k = 5
     *  Output: 2
     *
     *  Input: nums = [3,9,6], k = 2
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.maxFrequency(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
