#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    long long lowerBound(vector<int>& nums, int value) {
        long long retVal = 0;

        int left = 0;
        int right = nums.size() - 1;
        while (left < right) {
            int sum = nums[left] + nums[right];
            // If sum is less than value, add the size of window to result and move to the next index.
            // Otherwise, shift the right pointer backwards, until we get a valid window.
            if (sum < value) {
                retVal += (right - left);
                left++;
            } else {
                right--;
            }
        }

        return retVal;
    }

   public:
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        long long retVal = 0;

        sort(nums.begin(), nums.end());
        retVal = lowerBound(nums, upper + 1) - lowerBound(nums, lower);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int lower;
        int upper;
    };
    vector<subject> testData{{{0, 1, 7, 4, 4, 5}, 3, 6}, {{1, 7, 9, 2, 5}, 11, 11}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [0,1,7,4,4,5], lower = 3, upper = 6
     *  Output: 6
     *
     *  Input: nums = [1,7,9,2,5], lower = 11, upper = 11
     *  Output: 1
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], lower = " << testData[i].lower << ", upper = " << testData[i].upper << "\n";

        answer = cSolution.countFairPairs(testData[i].nums, testData[i].lower, testData[i].upper);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
