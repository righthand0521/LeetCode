#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> getMaximumXor(vector<int>& nums, int maximumBit) {
        vector<int> retVal;

        int numsSize = nums.size();

        int xorProduct = 0;
        for (int i = 0; i < numsSize; i++) {
            xorProduct = xorProduct ^ nums[i];
        }

        int mask = (1 << maximumBit) - 1;
        for (int i = 0; i < numsSize; i++) {
            retVal.emplace_back(xorProduct ^ mask);
            // remove last element
            xorProduct = xorProduct ^ nums[numsSize - 1 - i];
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int maximumBit;
    };
    vector<subject> testData{{{0, 1, 1, 3}, 2}, {{2, 3, 4, 7}, 3}, {{0, 1, 2, 2, 5, 7}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [0,1,1,3], maximumBit = 2
     *  Output: [0,3,2,3]
     *
     *  Input: nums = [2,3,4,7], maximumBit = 3
     *  Output: [5,2,6,5]
     *
     *  Input: nums = [0,1,2,2,5,7], maximumBit = 3
     *  Output: [4,3,6,4,6,7]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], maximumBit = " << testData[i].maximumBit << "\n";

        answer = cSolution.getMaximumXor(testData[i].nums, testData[i].maximumBit);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
