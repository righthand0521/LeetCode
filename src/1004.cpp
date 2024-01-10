#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int longestOnes(vector<int>& nums, int k) {
        int retVal = 0;

        int numsSize = nums.size();

        int flip = 0;
        int left = 0;
        int right = 0;
        for (right = 0; right < numsSize; ++right) {
            flip += (1 - nums[right]);
            while (flip > k) {
                flip -= (1 - nums[left]);
                left += 1;
            }

            retVal = max(retVal, right - left + 1);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0}, 2},
                             {{0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1}, 3},
                             {{0, 0, 0, 0}, 0}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
     *  Output: 6
     *
     *  Input: nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
     *  Output: 10
     *
     *  Input: nums = [0,0,0,0], k = 0
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.longestOnes(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
