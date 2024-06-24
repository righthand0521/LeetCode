#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minKBitFlips(vector<int>& nums, int k) {
        int retVal = 0;

        int numsSize = nums.size();
        int revCnt = 0;
        for (int i = 0; i < numsSize; ++i) {
            if ((i >= k) && (nums[i - k] > 1)) {
                revCnt ^= 1;
                nums[i - k] -= 2;
            }

            if (nums[i] == revCnt) {
                if (i + k > numsSize) {
                    retVal = -1;
                    break;
                }
                ++retVal;
                revCnt ^= 1;
                nums[i] += 2;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{0, 1, 0}, 1}, {{1, 1, 0}, 2}, {{0, 0, 0, 1, 0, 1, 1, 0}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [0,1,0], k = 1
     *  Output: 2
     *
     *  Input: nums = [1,1,0], k = 2
     *  Output: -1
     *
     *  Input: nums = [0,0,0,1,0,1,1,0], k = 3
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.minKBitFlips(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
