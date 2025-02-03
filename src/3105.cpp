#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int longestMonotonicSubarray(vector<int>& nums) {
        int retVal = 1;

        int numsSize = nums.size();

        int increasing = 1;
        int decreasing = 1;
        for (int i = 1; i < numsSize; ++i) {
            if (nums[i - 1] < nums[i]) {
                increasing += 1;
                decreasing = 1;
            } else if (nums[i - 1] > nums[i]) {
                decreasing += 1;
                increasing = 1;
            } else {
                increasing = 1;
                decreasing = 1;
            }
            retVal = max(retVal, max(increasing, decreasing));
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 4, 3, 3, 2}}, {{3, 3, 3, 3}}, {{3, 2, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,4,3,3,2]
     *  Output: 2
     *
     *  Input: nums = [3,3,3,3]
     *  Output: 1
     *
     *  Input: nums = [3,2,1]
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.longestMonotonicSubarray(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
