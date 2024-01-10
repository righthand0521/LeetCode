#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int smallestRangeI(vector<int>& nums, int k) {
        int retVal = 0;

        /* https://leetcode.com/problems/smallest-range-i/solutions/173367/c-java-python-check-max-min/
         *  If min(nums) + k < max(nums) - k, then return max(nums) - min(nums) - 2 * k.
         *  If min(nums) + k >= max(nums) - k, then return 0.
         */
        int max = *max_element(nums.begin(), nums.end());
        int min = *min_element(nums.begin(), nums.end());
        if ((min + k) < (max - k)) {
            retVal = max - min - 2 * k;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{1}, 0}, {{0, 10}, 2}, {{1, 3, 6}, 3}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.smallestRangeI(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
