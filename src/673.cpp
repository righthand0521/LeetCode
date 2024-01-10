#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int findNumberOfLIS(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        vector<int> dpLength(numsSize, 1);
        vector<int> dpCount(numsSize, 1);
        for (int i = 0; i < numsSize; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[j] >= nums[i]) {
                    continue;
                }

                if (dpLength[j] + 1 > dpLength[i]) {
                    dpLength[i] = dpLength[j] + 1;
                    dpCount[i] = 0;
                }
                if (dpLength[j] + 1 == dpLength[i]) {
                    dpCount[i] += dpCount[j];
                }
            }
        }

        int longestLength = *max_element(dpLength.begin(), dpLength.end());
        for (int i = 0; i < numsSize; ++i) {
            if (dpLength[i] == longestLength) {
                retVal += dpCount[i];
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 3, 5, 4, 7}}, {{2, 2, 2, 2, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,3,5,4,7]
     *  Output: 2
     *
     *  Input: nums = [2,2,2,2,2]
     *  Output: 5
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "]\n";

        answer = cSolution.findNumberOfLIS(testData[i].nums);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
