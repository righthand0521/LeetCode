#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minOperations(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        for (int i = 0; i < numsSize - 2; ++i) {
            if (nums[i] == 1) {
                continue;
            }
            nums[i] = 1;
            nums[i + 1] = (nums[i + 1] == 0) ? 1 : 0;
            nums[i + 2] = (nums[i + 2] == 0) ? 1 : 0;
            retVal++;
        }
        if ((nums[numsSize - 2] == 0) || (nums[numsSize - 1] == 0)) {
            retVal = -1;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{0, 1, 1, 1, 0, 0}}, {{0, 1, 1, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [0,1,1,1,0,0]
     *  Output: 3
     *
     *  Input: nums = [0,1,1,1]
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.minOperations(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
