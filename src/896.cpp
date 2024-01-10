#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isMonotonic(vector<int>& nums) {
        bool retVal = true;

        int numsSize = nums.size();
        if (numsSize == 1) {  // 1 <= nums.length <= 10^5
            return retVal;
        }

        int diff = 1;
        int previous = 0;
        for (int i = 1; i < numsSize; ++i) {
            if (nums[i] == nums[i - 1]) {
                continue;
            } else if (nums[i] > nums[i - 1]) {
                diff = 1;
            } else if (nums[i] < nums[i - 1]) {
                diff = -1;
            }

            if (previous != 0) {
                if (previous != diff) {
                    retVal = false;
                    break;
                }
            }
            previous = diff;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 2, 3}}, {{6, 5, 4, 4}}, {{1, 3, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,2,3]
     *  Output: true
     *
     *  Input: nums = [6,5,4,4]
     *  Output: true
     *
     *  Input: nums = [1,3,2]
     *  Output: false
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.isMonotonic(testData[i].nums);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
