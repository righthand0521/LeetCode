#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int minSubarray(vector<int>& nums, int p) {
        int retVal = 0;

        int numsSize = nums.size();

        // Step 1: Calculate total sum and target remainder
        int totalSum = 0;
        for (int num : nums) {
            totalSum = (totalSum + num) % p;
        }
        int target = totalSum % p;
        if (target == 0) {  // The array is already divisible by p
            return retVal;
        }

        // Step 2: Use a hash map to track prefix sum mod p
        unordered_map<int, int> modMap;
        modMap[0] = -1;  // To handle the case where the whole prefix is the answer

        // Step 3: Iterate over the array
        retVal = numsSize;
        int currentSum = 0;
        for (int i = 0; i < numsSize; ++i) {
            currentSum = (currentSum + nums[i]) % p;

            int needed = (currentSum - target + p) % p;  // Calculate what we need to remove
            // If we have seen the needed remainder, we can consider this subarray
            if (modMap.find(needed) != modMap.end()) {
                retVal = min(retVal, i - modMap[needed]);
            }

            modMap[currentSum] = i;  // Store the current remainder and index
        }

        if (retVal == numsSize) {
            retVal = -1;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int p;
    };
    vector<subject> testData{{{3, 1, 4, 2}, 6}, {{6, 3, 5, 2}, 9}, {{1, 2, 3}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [3,1,4,2], p = 6
     *  Output: 1
     *
     *  Input: nums = [6,3,5,2], p = 9
     *  Output: 2
     *
     *  Input: nums = [1,2,3], p = 3
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], p = " << testData[i].p << "\n";

        answer = cSolution.minSubarray(testData[i].nums, testData[i].p);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
