#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool check(vector<int>& nums) {
        bool retVal = true;

        int numsSize = nums.size();
        int idx = 0;
        for (int i = 1; i < numsSize; ++i) {
            if (nums[i - 1] > nums[i]) {
                idx = i;
                break;
            }
        }
        if (idx == 0) {
            return retVal;
        }

        for (int i = idx + 1; i < numsSize; ++i) {
            if (nums[i - 1] > nums[i]) {
                retVal = false;
                return retVal;
            }
        }

        if (nums[0] < nums[numsSize - 1]) {
            retVal = false;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{3, 4, 5, 1, 2}}, {{2, 1, 3, 4}}, {{1, 2, 3}}, {{2, 4, 1, 3}}, {{1, 3, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [3,4,5,1,2]
     *  Output: true
     *
     *  Input: nums = [2,1,3,4]
     *  Output: false
     *
     *  Input: nums = [1,2,3]
     *  Output: true
     *
     *  Input: nums = [2,4,1,3]
     *  Output: false
     *
     *  Input: nums = [1,3,2]
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.check(testData[i].nums);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
