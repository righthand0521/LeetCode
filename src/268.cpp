#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
#define METHOD_SUM (0)
#define METHOD_XOR (1)
    int missingNumber(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

#if (METHOD_SUM)
        retVal = (numsSize * (numsSize + 1)) / 2;
#elif (METHOD_XOR)
        retVal = numsSize;
#endif

        for (int i = 0; i < numsSize; ++i) {
#if (METHOD_SUM)
            retVal -= nums[i];
#elif (METHOD_XOR)
            retVal ^= i;
            retVal ^= nums[i];
#endif
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{3, 0, 1}}, {{0, 1}}, {{9, 6, 4, 2, 3, 5, 7, 0, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [3,0,1]
     *  Output: 2
     *
     *  Input: nums = [0,1]
     *  Output: 2
     *
     *  Input: nums = [9,6,4,2,3,5,7,0,1]
     *  Output: 8
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.missingNumber(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
