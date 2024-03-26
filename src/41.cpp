#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int firstMissingPositive(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        vector<bool> seen((numsSize + 1), false);
        for (int num : nums) {
            if ((0 < num) && (num <= numsSize)) {
                seen[num] = true;
            }
        }

        for (int i = 1; i <= numsSize; ++i) {
            if (seen[i] == false) {
                retVal = i;
                return retVal;
            }
        }
        retVal = numsSize + 1;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 0}}, {{3, 4, -1, 1}}, {{7, 8, 9, 11, 12}}, {{2, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,0]
     *  Output: 3
     *
     *  Input: nums = [3,4,-1,1]
     *  Output: 2
     *
     *  Input: nums = [7,8,9,11,12]
     *  Output: 1
     *
     *  Input: nums = [2, 1]
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

        answer = cSolution.firstMissingPositive(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
