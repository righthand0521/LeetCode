#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int subsetXORSum(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        // Capture each bit that is set in any of the elements
        for (int num : nums) {
            retVal |= num;
        }

        // Multiply by the number of subset XOR totals that will have each bit set
        retVal = retVal << (numsSize - 1);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 3}}, {{5, 1, 6}}, {{3, 4, 5, 6, 7, 8}}, {{2, 4, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,3]
     *  Output: 6
     *
     *  Input: nums = [5,1,6]
     *  Output: 28
     *
     *  Input: nums = [3,4,5,6,7,8]
     *  Output: 480
     *
     *  Input: nums = [2,4,4]
     *  Output: 24
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.subsetXORSum(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
