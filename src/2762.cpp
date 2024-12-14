#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long continuousSubarrays(vector<int>& nums) {
        long long retVal = 0;

        int numsSize = nums.size();

        int right = 0;
        int left = 0;
        int curMin = nums[right];
        int curMax = nums[right];
        long long windowLen = 0;
        for (right = 0; right < numsSize; right++) {
            curMin = min(curMin, nums[right]);
            curMax = max(curMax, nums[right]);
            if (curMax - curMin <= 2) {
                continue;
            }

            // Add subarrays from the previous valid window
            windowLen = (right - left);
            retVal += (windowLen * (windowLen + 1) / 2);
            // Start a new window at the current position
            left = right;
            curMin = curMax = nums[right];
            // Expand left boundary while maintaining the condition
            while ((left > 0) && (abs(nums[right] - nums[left - 1]) <= 2)) {
                left--;
                curMin = min(curMin, nums[left]);
                curMax = max(curMax, nums[left]);
            }
            // Remove overcounted subarrays if left boundary expanded
            if (left < right) {
                windowLen = right - left;
                retVal -= (windowLen * (windowLen + 1) / 2);
            }
        }

        // Add subarrays from the final window
        windowLen = right - left;
        retVal += (windowLen * (windowLen + 1) / 2);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{5, 4, 2, 4}}, {{1, 2, 3}}, {{65, 66, 67, 66, 66, 65, 64, 65, 65, 64}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [5,4,2,4]
     *  Output: 8
     *
     *  Input: nums = [1,2,3]
     *  Output: 6
     *
     *  Input: nums = [65,66,67,66,66,65,64,65,65,64]
     *  Output: 43
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.continuousSubarrays(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
