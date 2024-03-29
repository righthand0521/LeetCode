#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long countSubarrays(vector<int>& nums, int k) {
        long long retVal = 0;

        int numsSize = nums.size();
        int maxNum = *max_element(nums.begin(), nums.end());
        int maxNumWindow = 0;
        int start = 0;
        int end = 0;
        for (end = 0; end < numsSize; ++end) {
            if (nums[end] == maxNum) {
                maxNumWindow++;
            }

            while (maxNumWindow == k) {
                if (nums[start] == maxNum) {
                    maxNumWindow--;
                }
                start++;
            }

            retVal += start;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
        int k;
    };
    vector<subject> testData{{{1, 3, 2, 3, 3}, 2}, {{1, 4, 2, 1}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: nums = [1,3,2,3,3], k = 2
     *  Output: 6
     *
     *  Input: nums = [1,4,2,1], k = 3
     *  Output: 0
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: nums = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.countSubarrays(testData[i].nums, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
