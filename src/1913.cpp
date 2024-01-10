#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxProductDifference(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        sort(nums.begin(), nums.end());
        retVal = (nums[numsSize - 1] * nums[numsSize - 2]) - (nums[0] * nums[1]);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{5, 6, 2, 7, 4}}, {{4, 2, 5, 9, 7, 4, 8}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [5,6,2,7,4]
     *  Output: 34
     *
     *  Input: nums = [4,2,5,9,7,4,8]
     *  Output: 64
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.maxProductDifference(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
