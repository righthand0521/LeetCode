#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    int minimumDifference(vector<int>& nums, int k) {
        int retVal = 0;

        sort(nums.begin(), nums.end());

        retVal = numeric_limits<int>::max();
        int numsSize = nums.size();
        for (int i = 0; i <= numsSize - k; ++i) {
            retVal = min(retVal, nums[i + k - 1] - nums[i]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{90}, 1}, {{9, 4, 1, 7}, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [90], k = 1
     *  Output: 0
     *
     *  Input: nums = [9,4,1,7], k = 2
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.minimumDifference(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
