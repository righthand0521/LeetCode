#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    int findLengthOfLCIS(vector<int>& nums) {
        int retVal = 0;

        int previousNum = numeric_limits<int>::min();  // - 10 ^ 9 <= nums[i] <= 10 ^ 9
        int count = 0;
        for (int num : nums) {
            if (num > previousNum) {
                ++count;
            } else {
                retVal = max(retVal, count);
                count = 1;
            }
            previousNum = num;
        }
        retVal = max(retVal, count);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 3, 5, 4, 7}}, {{2, 2, 2, 2, 2}}, {{1, 3, 5, 7}}, {{1, 3, 5, 4, 2, 3, 4, 5}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,3,5,4,7]
     *  Output: 3
     *
     *  Input: nums = [2,2,2,2,2]
     *  Output: 1
     *
     *  Input: nums = [1,3,5,7]
     *  Output: 4
     *
     *  Input: nums = [1,3,5,4,2,3,4,5]
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.findLengthOfLCIS(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
