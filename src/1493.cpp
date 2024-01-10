#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int longestSubarray(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        int start = 0;
        int zeroCount = 0;
        for (int i = 0; i < numsSize; ++i) {
            if (nums[i] == 0) {
                ++zeroCount;
            }

            while (zeroCount > 1) {
                if (nums[start] == 0) {
                    --zeroCount;
                }
                ++start;
            }

            retVal = max(retVal, i - start);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 1, 0, 1}}, {{0, 1, 1, 1, 0, 1, 1, 0, 1}}, {{1, 1, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,1,0,1]
     *  Output: 3
     *
     *  Input: nums = [0,1,1,1,0,1,1,0,1]
     *  Output: 5
     *
     *  Input: nums = [1,1,1]
     *  Output: 2
     */

    Solution cSolution;
    double answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.longestSubarray(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
