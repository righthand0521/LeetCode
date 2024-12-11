#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maximumBeauty(vector<int>& nums, int k) {
        int retVal = 0;

        int numsSize = nums.size();
        if (numsSize == 1) {  // If there's only one element, the maximum beauty is 1
            retVal = 1;
            return retVal;
        }

        int maxValue = 0;
        for (int num : nums) {
            maxValue = max(maxValue, num);
        }

        vector<int> count(maxValue + 1, 0);
        for (int num : nums) {
            count[max(num - k, 0)]++;  // Increment at the start of the range
            if (num + k + 1 <= maxValue) {
                count[num + k + 1]--;  // Decrement after the range
            }
        }

        // Calculate the prefix sum and find the maximum value
        int currentSum = 0;
        for (int value : count) {
            currentSum += value;
            retVal = max(retVal, currentSum);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{4, 6, 1, 2}, 2}, {{1, 1, 1, 1}, 10}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [4,6,1,2], k = 2
     *  Output: 3
     *
     *  Input: nums = [1,1,1,1], k = 10
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.maximumBeauty(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
