#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int countHillValley(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        /* Example: Input: nums = [2,4,1,1,6,5]
         *  2   4   1   1   6   5
         *    2  -3   0   5  -1
         */
        int diff = 0;
        for (int i = 1; i < numsSize; ++i) {
            if (nums[i] > nums[i - 1]) {
                if (diff == -1) {
                    ++retVal;
                }
                diff = 1;
            } else if (nums[i] < nums[i - 1]) {
                if (diff == 1) {
                    ++retVal;
                }
                diff = -1;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{2, 4, 1, 1, 6, 5}}, {{6, 6, 5, 5, 4, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [2,4,1,1,6,5]
     *  Output: 3
     *
     *  Input: nums = [6,6,5,5,4,1]
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

        answer = cSolution.countHillValley(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
