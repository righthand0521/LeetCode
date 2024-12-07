#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    bool isPossible(int maxBallsInBag, vector<int>& nums, int maxOperations) {
        bool retVal = true;  // We can split the balls within the allowed operations, return true

        int totalOperations = 0;
        for (int num : nums) {
            // Calculate the number of operations needed to split this bag
            int operations = ceil(num / (double)maxBallsInBag) - 1;
            totalOperations += operations;

            // Total operations exceed maxOperations, return false
            if (totalOperations > maxOperations) {
                retVal = false;
                break;
            }
        }

        return retVal;
    }

   public:
    int minimumSize(vector<int>& nums, int maxOperations) {
        int retVal = 0;

        // Perform binary search to find the optimal maxBallsInBag
        int left = 1;
        int right = 0;
        for (auto num : nums) {
            right = max(right, num);
        }
        while (left < right) {
            int middle = (left + right) / 2;

            // Check if a valid distribution is possible with the current middle value
            if (isPossible(middle, nums, maxOperations)) {
                right = middle;  // If possible, try a smaller value (shift right to middle)
            } else {
                left = middle + 1;  // If not possible, try a larger value (shift left to middle + 1)
            }
        }
        retVal = left;  // Return the smallest possible value for maxBallsInBag

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int maxOperations;
    };
    vector<subject> testData{{{9}, 2}, {{2, 4, 8, 2}, 4}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [9], maxOperations = 2
     *  Output: 3
     *
     *  Input: nums = [2,4,8,2], maxOperations = 4
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], maxOperations = " << testData[i].maxOperations << "\n";

        answer = cSolution.minimumSize(testData[i].nums, testData[i].maxOperations);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
