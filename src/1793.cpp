#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maximumScore(vector<int>& nums, int k) {
        int retVal = 0;

        int numsSize = nums.size();

        retVal = nums[k];
        int minValue = nums[k];
        int left = k;
        int right = k;
        while ((left > 0) || (right < numsSize - 1)) {
            // 1 <= nums[i] <= 2 * 10^4, 0 <= k < nums.length
            int leftValue = ((left > 0) ? nums[left - 1] : 0);
            int rightValue = ((right < numsSize - 1) ? nums[right + 1] : 0);
            if (leftValue < rightValue) {
                right++;
                minValue = min(minValue, nums[right]);
            } else {
                left--;
                minValue = min(minValue, nums[left]);
            }

            retVal = max(retVal, minValue * (right - left + 1));
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{1, 4, 3, 7, 4, 5}, 3}, {{5, 5, 4, 5, 4, 1, 1, 1}, 0}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,4,3,7,4,5], k = 3
     *  Output: 15
     *
     *  Input: nums = [5,5,4,5,4,1,1,1], k = 0
     *  Output: 20
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.maximumScore(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
