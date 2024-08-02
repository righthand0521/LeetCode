#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    // Helper function to calculate the minimum swaps required to group all value together
    int minSwapsHelper(vector<int>& nums, int value) {
        int retVal = 0;

        int numsSize = nums.size();

        // Count the total number of value in the array
        int totalValCount = 0;
        for (int i = numsSize - 1; i >= 0; i--) {
            if (nums[i] == value) {
                totalValCount++;
            }
        }
        // If there is no value or the array is full of value, no swaps are needed
        if ((totalValCount == 0) || (totalValCount == numsSize)) {
            return retVal;
        }

        int start = 0;
        int end = 0;
        int maxValInWindow = 0;
        int currentValInWindow = 0;

        // Initial window setup: count the number of value in the first window of size `totalValCount`
        while (end < totalValCount) {
            if (nums[end++] == value) {
                currentValInWindow++;
            }
        }
        maxValInWindow = max(maxValInWindow, currentValInWindow);

        // Slide the window across the array to find the maximum number of value in any window
        while (end < numsSize) {
            if (nums[start++] == value) {
                currentValInWindow--;
            }

            if (nums[end++] == value) {
                currentValInWindow++;
            }

            maxValInWindow = max(maxValInWindow, currentValInWindow);
        }

        // Minimum swaps are the total value minus the maximum found in any window
        retVal = totalValCount - maxValInWindow;

        return retVal;
    }

   public:
    int minSwaps(vector<int>& nums) {
        int retVal = 0;

        // Calculate the minimum swaps needed to group all 1s or all 0s together
        int op0 = minSwapsHelper(nums, 0);  // Grouping all 0s together
        int op1 = minSwapsHelper(nums, 1);  // Grouping all 1s together
        retVal = min(op0, op1);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{0, 1, 0, 1, 1, 0, 0}}, {{0, 1, 1, 1, 0, 0, 1, 1, 0}}, {{1, 1, 0, 0, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [0,1,0,1,1,0,0]
     *  Output: 1
     *
     *  Input: nums = [0,1,1,1,0,0,1,1,0]
     *  Output: 2
     *
     *  Input: nums = [1,1,0,0,1]
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

        answer = cSolution.minSwaps(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
