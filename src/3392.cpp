#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int countSubarrays(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        for (int i = 0; i < numsSize - 2; ++i) {
            if (2 * (nums[i] + nums[i + 2]) == nums[i + 1]) {
                retVal++;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 1, 4, 1}}, {{1, 1, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,2,1,4,1]
     *  Output: 1
     *
     *  Input: nums = [1,1,1]
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

        answer = cSolution.countSubarrays(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
